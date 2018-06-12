/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;

namespace SegLCD_v3_40
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        public const string PAGE_PARAM_BASIC = "BasicConfiguration";
        private const string PAGE_PARAM_BUILTIN = "Built-in";

        #region ICyParamEditHook_v1 Members

        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
                                                    ICyExpressMgr_v1 mgr)
        {
            CyLCDParameters parameters = new CyLCDParameters(edit, termQuery);
            CyParamExprDelegate ParamCommitted = delegate { parameters.GetExprViewParams(); };
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_BASIC, new CyBasicConfiguration(parameters),
                                    ParamCommitted, PAGE_PARAM_BASIC);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_POWERSETTINGS,
                                    new CyDriverParams(parameters), ParamCommitted, "");
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_HELPERS, new CyHelpers(parameters),
                                    ParamCommitted, "");
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_CUSTOMCHARS, new CyCustomCharsEditor(parameters),
                                    ParamCommitted, "");
            editor.AddDefaultPage(Properties.Resources.PAGE_TITLE_BUILTIN, PAGE_PARAM_BUILTIN);
            parameters.m_globalEditMode = true;
            edit.NotifyWhenDesignUpdates(parameters.UpdateDesign);

            DialogResult result = editor.ShowDialog();
            return result;
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        public static List<CyCustErr> GetErrors(ICyInstEdit_v1 edit, string tabName)
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            if (edit != null)
                foreach (string paramName in edit.GetParamNames())
                {
                    CyCompDevParam param = edit.GetCommittedParam(paramName);
                    if (param.IsVisible && param.TabName == tabName)
                    {
                        if (param.ErrorCount > 0)
                        {
                            foreach (string errMsg in param.Errors)
                            {
                                errs.Add(new CyCustErr(errMsg));
                            }
                        }
                    }
                }

            return errs;
        }

        #region ICyDRCProvider_v1 Members

        IEnumerable<CyDRCInfo_v1> ICyDRCProvider_v1.GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            
            ICyInstQuery_v1 instQuery = args.InstQueryV1;
            byte m_driverPowerMode =
                Convert.ToByte(instQuery.GetCommittedParam(CyLCDParameters.PARAM_DRIVERPOWERMODE).Value);

            // Check if XTAL 32kHz clock is enabled in "Low Power using Ext 32 kHz crystal" mode
            if ((m_driverPowerMode == (byte)CyBasicConfiguration.CyMode.LOW_POWER_32K) && 
                instQuery.DesignQuery.DesignInfoAvailable)
            {
                foreach (string item in instQuery.DesignQuery.ClockIDs)
                {
                    if (instQuery.DesignQuery.GetClockName(item) == "XTAL 32kHz")
                    {
                        bool isXTALClockEnabled = instQuery.DesignQuery.IsClockStartedOnReset(item);
                        if (isXTALClockEnabled == false)
                            yield return
                                new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                                Properties.Resources.CLOCK_XTAL_ERROR);
                    }
                }
            }
            // Check if ILO clock frequency equals 1 kHz in "Low Power using ILO" mode
            if (m_driverPowerMode == (byte)CyBasicConfiguration.CyMode.LOW_POWER_ILO)
            {
                double iloClockFreq = CyLCDParameters.GetClockInHz(args.TermQueryV1, "or_ilo_clk", true);
                if (Math.Abs(iloClockFreq - 1000) > 1)
                {
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                                    Properties.Resources.CLOCK_ILO_ERROR_1KHZ);
                }
            }
        }

        #endregion
    }
}
