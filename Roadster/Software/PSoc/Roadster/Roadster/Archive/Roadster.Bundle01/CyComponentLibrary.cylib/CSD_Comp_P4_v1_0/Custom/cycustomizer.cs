/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Collections.Generic;
using CSD_Comp_P4_v1_0.Tabs;

namespace CSD_Comp_P4_v1_0
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICyAPICustomize_v2, ICyToolTipCustomize_v1
    {
        #region Class Consts

        // ParamEditHook
        public const string BUILTIN_SYMBOL_TAB_NAME = "Built-in";
        public const string GENERAL_SYMBOL_TAB_NAME = "Basic";

        // APICustomize
        public const string API_PARAMNAME_VREFSTEP = "VRefStep";
        public const string API_PARAMNAME_REFGENGAIN = "RefGenGain";
        public const string API_PARAMNAME_VREFRANGE = "VRefRange";
        #endregion Class Consts

        #region ICyParamEditHook_v1 Members

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            parameters.Editor = editor;

            CyConfigTab configTab = new CyConfigTab(parameters);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                configTab.UpdateUiFromTable();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Properties.Resources.TAB_NAME_GENERAL, configTab, exprDelegate, 
                GENERAL_SYMBOL_TAB_NAME);
            editor.AddDefaultPage(Properties.Resources.TAB_NAME_BUILTIN, BUILTIN_SYMBOL_TAB_NAME);

            parameters.GlobalEditMode = true;
            editor.UseBigEditor = true;
            return editor.ShowDialog();
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion ICyParamEditHook_v1 Members

        #region ICyDRCProvider_v1 Members

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);

            #region Validate Vref source

            double maxVrefSource =  parameters.Vdda - CyParameters.MAX_VINREF_VDDA_OFFSET;

            // Vinref
            if (parameters.RefSource == CyEnumRefSourceType.EXTERNAL_REFERENCE &&
                (parameters.Vinref < CyParameters.MIN_VINREF_VOLTAGE - CyParameters.EPS ||
                parameters.Vinref > maxVrefSource + CyParameters.EPS))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    String.Format(Properties.Resources.ERR_VINREF_VDDA_FORMATSTR2,
                    CyParameters.MIN_VINREF_VOLTAGE.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG),
                    maxVrefSource.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG)));
            }

            // Bandgap
            if (parameters.RefSource == CyEnumRefSourceType.INTERNAL_BANDGAP &&
                parameters.Bandgap > maxVrefSource + CyParameters.EPS)
            {
                double maxRange = parameters.Bandgap + CyParameters.MAX_VINREF_VDDA_OFFSET;

                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    String.Format(Properties.Resources.ERR_DRC_VBGR_FORMATSTR2,
                    maxRange.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG), 
                    CyParameters.MAX_VINREF_VDDA_OFFSET.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG)));
            }

            #endregion Validate Vref source

            #region Validate Actual Vrange

            if (parameters.RefType == CyEnumRefType.ADJUSTABLE)
            {
                double minRange = parameters.Vsource;
                double maxRange = parameters.Vdda - CyParameters.MAX_VRANGE_VDDA_OFFSET;

                if (minRange < maxRange + CyParameters.EPS)
                {
                    if (parameters.VrangeActual < minRange - CyParameters.EPS ||
                        parameters.VrangeActual > maxRange + CyParameters.EPS)
                    {
                        string sMinRange = minRange.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG);
                        string sMaxRange = maxRange.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG);

                        yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                            String.Format(Properties.Resources.ERR_VRANGE_VDDA_FORMATSTR3, sMinRange, sMaxRange,
                            parameters.VsourceName));
                    }
                }
            }

            #endregion Validate Actual Vrange
        }

        #endregion ICyDRCProvider_v1 Members

        #region ICyAPICustomize_v2 Members

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args, IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            CyParameters prms = new CyParameters(args.InstQuery);

            Dictionary<string, string> paramDict;
            if (customizers.Count > 0)
            {
                paramDict = customizers[0].MacroDictionary;
            }
            else
            {
                paramDict = new Dictionary<string, string>();
            }

            int gain = prms.AmplifierGain;

            if (gain > CyParameters.MAX_AMPLIFIER_GAIN)
                gain = CyParameters.MAX_AMPLIFIER_GAIN;
            else if (gain < 0)
                gain = 0;

            paramDict.Add(API_PARAMNAME_VREFSTEP, prms.AdjVrefStep_mV.ToString());
            paramDict.Add(API_PARAMNAME_REFGENGAIN, gain.ToString());

            if (prms.RefType == CyEnumRefType.ADJUSTABLE)
            {
                paramDict.Add(API_PARAMNAME_VREFRANGE, String.Format(
                    "{0}#define {1}_VREF_RANGE_MVOLTS          ({2}u){0}",  Environment.NewLine, prms.InstName, 
                    (int)(prms.VrangeDesired * 1000)));
            }

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
                yield return customizers[i];
            }
        }

        #endregion ICyAPICustomize_v2 Members

        #region ICyToolTipCustomize_v1 Members

        public string CustomizeToolTip(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyParameters prms = new CyParameters(query);

            string toolTip = query.DefaultToolTipText;
            string tapLine = String.Format("\t{0} = {1}\n", CyParamNames.TAP, prms.Tap);
            string vinrefLine = String.Format("\t{0} = {1}\n", CyParamNames.INPUT_REF_VOLTAGE, prms.Vinref);
            string voltageRefRangeLine = String.Format("\t{0} = {1}\n", CyParamNames.VOLTAGE_REF_RANGE, 
                prms.VrangeDesired);

            if (prms.RefType == CyEnumRefType.FIXED)
            {
                if (toolTip.Contains(tapLine))
                    toolTip = toolTip.Replace(tapLine, string.Empty);

                if (toolTip.Contains(voltageRefRangeLine))
                    toolTip = toolTip.Replace(voltageRefRangeLine, string.Empty);
            }

            if (prms.RefSource != CyEnumRefSourceType.EXTERNAL_REFERENCE && toolTip.Contains(vinrefLine))
                toolTip = toolTip.Replace(vinrefLine, string.Empty);

            return toolTip;
        }

        #endregion ICyToolTipCustomize_v1 Members
    }
}
