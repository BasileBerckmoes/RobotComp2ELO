/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/



using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;


namespace FanController_v4_0
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyShapeCustomize_v1, ICyAPICustomize_v2, ICyInstValidateHook_v1, 
                                ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 Members

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            parameters.m_editor = editor;

            CyFansTab fanTab = new CyFansTab(parameters);
            parameters.m_fansTab = fanTab;
            CyBasicTab basicTab = new CyBasicTab(parameters);
            CyPidTab pidTab = new CyPidTab(parameters);
            parameters.m_pidTab = pidTab;

            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                if (param.TabName == basicTab.TabName)
                    basicTab.UpdateFormFromParams();
                if (param.TabName == fanTab.TabName)
                    fanTab.UpdateFormFromParams();
                if (param.TabName == pidTab.TabName)
                    pidTab.UpdateFormFromParams();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Resources.BasicTab, basicTab, new CyParamExprDelegate(ExprDelegate), basicTab.TabName);
            editor.AddCustomPage(Resources.PidTab, pidTab, new CyParamExprDelegate(ExprDelegate), pidTab.TabName);
            editor.AddCustomPage(Resources.FansTab, fanTab, new CyParamExprDelegate(ExprDelegate), fanTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTab, "Built-in");

            parameters.UpdateTabVisibility();

            parameters.GlobalEditMode = true;
            DialogResult result = editor.ShowDialog();
            return result;
        }


        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        #region ICyShapeCustomize_v1

        /// <summary>
        /// Shape customizer renames terminals to set a proper bus width depending on the number of fans or banks
        /// </summary>

        const string TACH_BUS = "tach";
        const string FAN_BUS = "fan";
        const string BANK_BUS = "bank";
        const string TERM_PATERN = "{0}[{1}:1]";

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
                                         ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;

            // Read parameters
            CyParameters parameters = new CyParameters(instQuery);
            byte numFans = parameters.NumberOfFans;
            byte numBanks = parameters.NumberOfBanks;

            string tach_bus = termEdit.GetTermName(TACH_BUS);
            string fan_bus = termEdit.GetTermName(FAN_BUS);
			string bank_bus = termEdit.GetTermName(BANK_BUS);

            // Rename terminals that are visible in the current mode
            uint maxBitIndex = numFans;
            err = termEdit.TerminalRename(tach_bus, string.Format(TERM_PATERN, TACH_BUS, maxBitIndex));
            if (err.IsNotOK) return err;
            if (numBanks == 0)
                err = termEdit.TerminalRename(fan_bus, string.Format(TERM_PATERN, FAN_BUS, maxBitIndex));
            else
                err = termEdit.TerminalRename(bank_bus, string.Format(TERM_PATERN, BANK_BUS, numBanks));
            if (err.IsNotOK) return err;

            return CyCustErr.OK;
        }
        #endregion

        #region ICyAPICustomize_v2
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args,
            IEnumerable<CyAPICustomizer> apis)
        {
            // dict is used to set API parameters.
            // Key: parameter name
            // Value: parameter value
            Dictionary<string, string> dict = new Dictionary<string, string>();
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            
            if (customizers.Count == 0) return customizers;
            
            dict = customizers[0].MacroDictionary;
            CyParameters prm = new CyParameters(args.InstQuery);

            //Calculate and add INITIAL_DUTY_CYCLE parameter
            for (int ii = 0; ii < CyParamConst.MAX_FANS; ii++)
            {
                double dutyRPMSlope = ((double)(prm.GetMaxDuty(ii) - prm.GetMinDuty(ii))) / (prm.GetMaxRPM(ii)
                    - prm.GetMinRPM(ii));

                int diff = Math.Abs(prm.GetInitialRPM(ii) - prm.GetMinRPM(ii));

                double diffDuty = diff * dutyRPMSlope;

                int initDuty = 0;
                if (prm.GetInitialRPM(ii) > prm.GetMinRPM(ii))
                    initDuty = Convert.ToInt32(prm.GetMinDuty(ii) + diffDuty);
                else
                    initDuty = Convert.ToInt32(prm.GetMinDuty(ii) - diffDuty);

                if (initDuty < 0)
                    initDuty = 0;

                dict.Add(CyParameters.GetParamNameByIndex(CyParameters.P_INITIAL_DUTY_CYCLE, ii), initDuty.ToString());
            }

            foreach (CyAPICustomizer cust in customizers)
            {
                cust.MacroDictionary = dict;
            }

            return customizers;
        }
        #endregion

        #region ICyInstValidateHook_v1
        public void ValidateParams(ICyInstValidate_v1 instVal)
        {
            try
            {
                CyParameters prms = new CyParameters(instVal);

                Byte fanCount = prms.BankMode ? prms.NumberOfBanks : prms.NumberOfFans;
                for (int i = 0; i < fanCount; i++)
                {
                    InstValidateFanValueRange(prms.GetMinRPM(i), CyParamConst.MIN_RPM_NUD, CyParamConst.MAX_RPM_NUD, 
                                             CyParameters.P_MIN_RPM, i, instVal);
                    InstValidateFanValueRange(prms.GetMaxRPM(i), CyParamConst.MIN_RPM_NUD, CyParamConst.MAX_RPM_NUD,
                                              CyParameters.P_MAX_RPM, i, instVal);
                    InstValidateFanValueRange(prms.GetMinDuty(i), CyParamConst.MIN_DUTY_NUD, CyParamConst.MAX_DUTY_NUD,
                                              CyParameters.P_MIN_DUTY, i, instVal);
                    InstValidateFanValueRange(prms.GetMaxDuty(i), CyParamConst.MIN_DUTY_NUD, CyParamConst.MAX_DUTY_NUD,
                                              CyParameters.P_MAX_DUTY, i, instVal);
                    InstValidateFanValueRange(prms.GetInitialRPM(i), CyParamConst.MIN_RPM_NUD, CyParamConst.MAX_RPM_NUD,
                                             CyParameters.P_INITIAL_RPM, i, instVal);

                    string formattedIndex = (i + 1).ToString().PadLeft(2, '0');
                    if (prms.GetMaxRPM(i) <= prms.GetMinRPM(i))
                    {
                        CyCustErr err = new CyCustErr(string.Format(Resources.ErrorRPMVal, formattedIndex));
                        instVal.AddError(CyParameters.GetParamNameByIndex(CyParameters.P_MAX_RPM, i), err);
                    }

                    if (prms.GetMaxDuty(i) <= prms.GetMinDuty(i))
                    {
                        CyCustErr err = new CyCustErr(string.Format(Resources.ErrorDutyVal, formattedIndex));
                        instVal.AddError(CyParameters.GetParamNameByIndex(CyParameters.P_MAX_DUTY, i), err);
                    }
                }
            }
            catch
            {
                Debug.Assert(false);
            }
        }

        private void InstValidateFanValueRange(int value, int min, int max, string paramName, int i, 
                                              ICyInstValidate_v1 instVal)
        {
            if ((value < min) || (value > max))
            {
                string pName = CyParameters.GetParamNameByIndex(paramName, i);
                string msg = String.Format(Resources.ErrorDrcValueRange, pName, min, max);
                instVal.AddError(pName, new CyCustErr(msg));
            }
        }
        #endregion

        #region ICyDRCProvider_v1
        /// <summary>
        /// DRC validates device dependent settings 
        /// </summary>
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);

            List<CyCustErr> errorList = new List<CyCustErr>();

            // Validate PSoC 4 limitations 
            errorList.AddRange(CyAuxFunctions.VerifyPSoC4Settings(parameters));

            for (int i = 0; i < errorList.Count; i++)
            {
                if (errorList[i] != CyCustErr.OK)
                {
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, errorList[i].Message);
                }
            }
        }
        #endregion
    }
}
