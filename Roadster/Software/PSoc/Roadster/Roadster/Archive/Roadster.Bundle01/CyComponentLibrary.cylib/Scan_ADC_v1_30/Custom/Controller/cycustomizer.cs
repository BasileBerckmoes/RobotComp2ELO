/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================//
*/
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v1_30
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer :
        ICyAPICustomize_v2,
        ICyDesignClient_v2,
        ICyDRCProvider_v1, 
        ICyExprEval_v2,
        ICyParamEditHook_v1,
        ICyShapeCustomize_v2
    {
        private const bool m_editParamsOnDrop = false;
        private const CyCompDevParamEditorMode m_mode = CyCompDevParamEditorMode.COMPLETE;
        private CyParameters m_params;
        private ICyTabbedParamEditor m_editor;

        public CyCommonTab m_commonTab;
        public CyConfigTab m_configTab0;
        public CyConfigTab m_configTab1;
        public CyConfigTab m_configTab2;
        public CyConfigTab m_configTab3;

        #region ICyParamEditHook_v1 method(s)

        DialogResult ICyParamEditHook_v1.EditParams(
            ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            LoadEditableParameters(edit, termQuery);

            m_editor = edit.CreateTabbedParamEditor();

            CyCommonTab m_commonTab = new CyCommonTab(m_params);
            CyConfigTab[] configTabArray = new CyConfigTab[CyParamRanges.NUM_CONFIG_MAX];
            
            CyParamExprDelegate paramChange = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                bool savedGlobalEditMode = m_params.GlobalEditMode;
                m_params.GlobalEditMode = false;
                try
                {
                    if (param.TabName == m_commonTab.TabName)
                    {
                        m_commonTab.UpdateUI();
                    }
                    else
                    {
                        for (int i = 0; i < CyParamRanges.NUM_CONFIG_MAX; )
                        {
                            if (param.TabName == configTabArray[i].TabName)
                            {
                                configTabArray[i].UpdateUI();
                            }
                        }
                    }
                }
                catch
                {
                    Debug.Assert(false);
                }
                m_params.GlobalEditMode = savedGlobalEditMode;
            };

            for (int i = 0; i < CyParamRanges.NUM_CONFIG_MAX; i++)
            {
                CyConfigTab configTab = new CyConfigTab(m_params, i);
                configTabArray[i] = configTab;
                m_editor.AddCustomPage(configTab.TabDisplayName, configTab, paramChange, configTab.TabName);
            }           


            //UseBigEditor is:
            //      true  = 640x480 (~595x330 useable) 
            //      false = 515x390 (~475x230 useable)
            m_editor.UseBigEditor = true;

            // Tab names should use resources, not hard-coded values
            m_editor.AddCustomPage("Common", m_commonTab, paramChange, "Common");            

            m_editor.AddDefaultPage("Built-in", "Built-in");

            UpdateTabVisibility();
            m_params.GlobalEditMode = true;

            m_params.NumConfigsChange += NumConfigsChanged;

            // Get initial ADC clock data.
            DesignUpdated(m_params.InstQuery, m_params.TermQuery);
            // SEY TODO: Get Design Wide Reference value

            edit.NotifyWhenDesignUpdates(DesignUpdated);
            var result = m_editor.ShowDialog();
            edit.NotifyWhenDesignUpdates(null);

            return result;
        }

        public void NumConfigsChanged(object sender, EventArgs e)
        {
            UpdateTabVisibility();
        }

        /// <summary>
        /// Update config tab visibility.
        /// </summary>
        public void UpdateTabVisibility()
        {
            int numConfigs = m_params.NumberOfConfigs;
            for (int i = 0; i < CyParamRanges.NUM_CONFIG_MAX; i++)
            {
                if (i < numConfigs)
                {
                    m_editor.ShowCustomPage("Config" + i.ToString());
                }
                else
                {
                    m_editor.HideCustomPage("Config" + i.ToString());
                }
            }
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return m_editParamsOnDrop;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return m_mode;
        }

        void DesignUpdated(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
        {
            if (m_params != null)
            {
                // Get clock information.
                m_params.ExternalAdcClockData
                    = CyClock.GetExternalSarClockData(termQuery);
                m_params.InternalAdcClockData
                    = CyClock.GetInternalSarClockData(termQuery);
                m_params.OnAdcClockSourceHandler();
            }
        }

        #endregion

        #region ICyExprEval_v2

        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "AclkMuxSelect":
                    return new CyExprEvalFuncEx(AclkMuxSelect);
                case "ExtVrefMuxSelect":
                    return new CyExprEvalFuncEx(ExtVrefMuxSelect);
                case "FilterVinMuxSelect":
                    return new CyExprEvalFuncEx(FilterVinMuxSelect);
                case "FilterConfigMuxSelect":
                    return new CyExprEvalFuncEx(FilterConfigMuxSelect);
                case "IsFilterPresent":
                    return new CyExprEvalFuncEx(IsFilterPresent);
                case "SarmuxDiffMask":
                    return new CyExprEvalFuncEx(SarmuxDiffMask);
                case "SarmuxVinDiffWidth":
                    return new CyExprEvalFuncEx(SarmuxVinDiffWidth);
                case "SarmuxVinNegWidth":
                    return new CyExprEvalFuncEx(SarmuxVinNegWidth);
                case "SarmuxVinPlusMuxSelect":
                    return new CyExprEvalFuncEx(SarmuxVinPlusMuxSelect);
                case "SocMuxSelect":
                    return new CyExprEvalFuncEx(SocMuxSelect);
                case "VinMinusMuxSelect":
                    return new CyExprEvalFuncEx(VinMinusMuxSelect);
                case "VminusMuxSelect":
                    return new CyExprEvalFuncEx(VminusMuxSelect);
                case "VinNegMuxSelect":
                    return new CyExprEvalFuncEx(VinNegMuxSelect);
                case "VinPlusMuxSelect":
                    return new CyExprEvalFuncEx(VinPlusMuxSelect);
                case "VplusMuxSelect":
                    return new CyExprEvalFuncEx(VplusMuxSelect);
                case "VrefMuxSelect":
                    return new CyExprEvalFuncEx(VrefMuxSelect);
                default:
                    return null;
            }
        }

        object SarmuxVinPlusMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 1)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (one argument expected).",
                    exprFuncName));
            }

            int muxNumber = typeConverter.GetAsInt(callingArgs[0]);

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.SarmuxVinPlusMuxSelect(m_params, muxNumber);

            return result;
        }

        object IsFilterPresent(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            bool result = CyExprEval.IsFilterPresent(m_params);

            return result;
        }

        object FilterConfigMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 1)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (one argument expected).",
                    exprFuncName));
            }

            int muxNumber = typeConverter.GetAsInt(callingArgs[0]);

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.FilterConfigMuxSelect(m_params, muxNumber);

            return result;
        }

        object FilterVinMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 2)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (two arguments expected).",
                    exprFuncName));
            }

            int configNumber = typeConverter.GetAsInt(callingArgs[0]);
            int muxNumber = typeConverter.GetAsInt(callingArgs[1]);

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.FilterVinMuxSelect(m_params, configNumber, muxNumber);

            return result;
        }

        object VinMinusMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 1)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (one argument expected).",
                    exprFuncName));
            }

            int muxNumber = typeConverter.GetAsInt(callingArgs[0]);

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.VinMinusMuxSelect(m_params, muxNumber);

            return result;
        }

        object VinPlusMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 1)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (one argument expected).",
                    exprFuncName));
            }

            int muxNumber = typeConverter.GetAsInt(callingArgs[0]);

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.VinPlusMuxSelect(m_params, muxNumber);

            return result;
        }

        object VinNegMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 1)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (one argument expected).",
                    exprFuncName));
            }

            int muxNumber = typeConverter.GetAsInt(callingArgs[0]);

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.VinNegMuxSelect(m_params, muxNumber);

            return result;
        }

        object VplusMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.VplusMuxSelect(m_params);

            return result;
        }

        object VminusMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.VminusMuxSelect(m_params);

            return result;
        }

        object SarmuxVinDiffWidth(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            byte result = CyExprEval.SarmuxVinDiffWidth(m_params);

            return result;
        }

        object SarmuxVinNegWidth(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            byte result = CyExprEval.SarmuxVinNegWidth(m_params);

            return result;
        }

        object SarmuxDiffMask(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            string result = CyExprEval.SarmuxDiffMask(m_params);

            return result;
        }

        object VrefMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 1)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (one argument expected).",
                    exprFuncName));
            }

            int muxNumber = typeConverter.GetAsInt(callingArgs[0]);

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.VrefMuxSelect(m_params, muxNumber);

            return result;
        }

        object ExtVrefMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.ExtVrefMuxSelect(m_params);

            return result;
        }

        object SocMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.SocMuxSelect(m_params);

            return result;
        }

        object AclkMuxSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            if ((m_params == null) && (creatorArgs.InstQuery != null))
            {
                LoadReadOnlyParameters(creatorArgs.InstQuery);
            }

            int result = CyExprEval.AclkMuxSelect(m_params);

            return result;
        }

        #endregion ICyExprEval_v2

        #region ICyDesignClient_v2  members

        public string GetDesignClientState(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return string.Empty;
        }

        public bool RequiresTooltipUpdate(string designClientState, ICyInstQuery_v1 query,
            ICyTerminalQuery_v1 termQuery)
        {
            return false;
        }

        public bool RequiresShapeUpdate(string designClientState, ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return true;
        }

        #endregion

        #region ICyShapeCustomize_v2 Members

        public CyCustErr CustomizeShapes(ICyShapeCustomizeArgs_v1 args)
        {
            ICyInstQuery_v1 query = args.InstQuery;
            ICySymbolShapeEdit_v2 shapeEdit = args.ShapeEdit;
            ICyTerminalEdit_v2 termEdit = args.TermEdit;

            if (query == null)
            {
                // If there is no symbol instance, do not generate symbol shapes.
                return CyCustErr.OK;
            }

            if (m_params == null)
            {
                LoadReadOnlyParameters(query);
            }

            CyShapesInfo shapesInfo = GetSymbolShapeInfo();

            // Create shape builder
            CyShapesBuilder builder = new CyShapesBuilder(m_params, shapeEdit, termEdit, shapesInfo);
            builder.DrawSymbol();

            return CyCustErr.OK;
        }

        private CyShapesInfo GetSymbolShapeInfo()
        {
            // Set up symbol shape information.
            CyShapesInfo shapesInfo = new CyShapesInfo();

            shapesInfo.ShowSocTerm = m_params.ExternalSoc;
            shapesInfo.ShowClkTerm = m_params.ExternalClk;
            shapesInfo.ConfigFilterMask = CyModelUtils.ConfigFilterMasks(m_params);
            shapesInfo.ConfigFilterAliases = CyModelUtils.ConfigFilterAliases(m_params);
            shapesInfo.ConfigCount = m_params.NumberOfConfigs;
            shapesInfo.ConfigVnegTerms = CyModelUtils.ConfigVnegTerms(m_params);
            shapesInfo.ConfigVnegSource = CyModelUtils.ConfigVnegSource(m_params);
            shapesInfo.ConfigVrefSource = CyModelUtils.ConfigVrefSource(m_params);
            shapesInfo.ConfigVrefTerms = CyModelUtils.ConfigVrefTerms(m_params);
            shapesInfo.ChannelCounts = CyModelUtils.ChannelCounts(m_params);
            shapesInfo.ChannelDiffMasks = CyModelUtils.ChannelDiffMasks(m_params);
            shapesInfo.ChannelSingleMasks = CyModelUtils.ChannelSingleMasks(m_params);
            shapesInfo.ChannelFilterMasks = CyModelUtils.ChannelFilterMasks(m_params);
            shapesInfo.ConfigSpace = CyModelUtils.ConfigSpace(m_params);
            shapesInfo.ExposeTestTerminals = CyModelUtils.ExposeTestTerminals(m_params);
            return shapesInfo;
        }

        private CyShapesInfo GetBattleWagonShapeInfo()
        {
            // Set up symbol shape information for a maximal symbol.
            CyShapesInfo shapesInfo = new CyShapesInfo();

            shapesInfo.ShowSocTerm = true;
            shapesInfo.ShowClkTerm = true;

            shapesInfo.ConfigCount = 4;
            shapesInfo.ConfigVnegTerms = new List<bool> { false, false, true, true};
            shapesInfo.ConfigVrefTerms = new List<bool> { false, true, false, true};
            shapesInfo.ChannelCounts = new List<int> { 16, 16, 16, 16, };
            shapesInfo.ChannelDiffMasks = new List<uint>
            {
                0xffff,
                0x0000,
                0xf0f0,
                0x5555,
            };

            return shapesInfo;
        }

        #endregion ICyShapeCustomize_v1 Members

        #region ICyAPICustomize_v2 members

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args,
            IEnumerable<CyAPICustomizer> apis)
        {
            if (m_params == null)
            {
                LoadReadOnlyParameters(args.InstQuery);

                // Get clock information.
                m_params.ExternalAdcClockData
                    = CyClock.GetExternalSarClockData(args.TermQuery);
                m_params.InternalAdcClockData
                    = CyClock.GetInternalSarClockData(args.TermQuery);

                // Reschedule with data from current schematic elaboration.
                m_params.UpdateScanSchedules();

                //If the Vref value is queriable, query Creator in case it has after Vref is set in the customizer.
                for (int i = 0; i < m_params.NumberOfConfigs; i++)
                {
                    CyConfigModel config = m_params.GetConfig(i);
                    if (config.VrefSource != CyEVrefSource.VREFSOURCE_EXTERNAL
                    && config.VrefSource != CyEVrefSource.VREFSOURCE_DEVPIN)
                    {
                        config.VrefVoltage = CyVoltage.GetDesignVrefValue(m_params, config.VrefSource);
                        m_params.SetConfig(i, config);
                    }
                }
            }

            Dictionary<string, string> paramDict = null;
            foreach (CyAPICustomizer api in apis)
            {
                if (paramDict == null)
                {
                    paramDict = api.MacroDictionary;
                    CyApiMacros.ExtendDictionary(paramDict, m_params);
                }
                api.MacroDictionary = paramDict;
            }

            return apis;
        }

        #endregion ICyAPICustomize_v2 members

        #region ICyDRCProvider_v1 members

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            if (m_params == null)
            {
                LoadReadTermParameters(args.InstQueryV1, args.TermQueryV1);
            }
            // Get clock information.
            m_params.ExternalAdcClockData
                = CyClock.GetExternalSarClockData(args.TermQueryV1);
            m_params.InternalAdcClockData
                = CyClock.GetInternalSarClockData(args.TermQueryV1);
            // Get filter information.
            var isFilterAllowed = DeviceAllowsFilter(args.InstQueryV1);
            m_params.IsFilterAllowed = isFilterAllowed;


            //Get initial schedule signature
            var sig0 = m_params.ScanSignature();

            // Reschedule with data from current schematic elaboration.
            var schedErrs = m_params.UpdateScanSchedules();

            // Get part number.
            var partNumber = ProjectPartNumber(args.InstQueryV1);

            //Return DRCs encountered during scheduling
            foreach (CyDRCInfo_v1 singleSchedErr in schedErrs)
            {
                yield return singleSchedErr;
            }

            if (CyDrc.CheckChannelsEnabled(m_params) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    global::Scan_ADC_v1_30.Controller.cydrcerrors.AllChannelsDisabled);
            }
            if (CyDrc.CheckVrefBypassNotice(m_params) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                    global::Scan_ADC_v1_30.Controller.cydrcerrors.VrefBypassNotice);
            }
            double maxVref = 0;
            if (CyDrc.CheckVrefNotTooHigh(m_params, out maxVref) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                    string.Format(global::Scan_ADC_v1_30.View.cyguierrors.VrefTooHigh,
                                  maxVref.ToString("N3")));
            }
            double minVref = 0;
            if (CyDrc.CheckVrefNotTooLow(m_params, out minVref) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                    string.Format(global::Scan_ADC_v1_30.View.cyguierrors.VrefTooLow,
                                  minVref.ToString("N3")));
            }
            if (CyDrc.CheckVnegResultNotice(m_params) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                    global::Scan_ADC_v1_30.Controller.cydrcerrors.VnegResultNotice);
            }
            if (CyDrc.CheckAverageOverflow(m_params) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    global::Scan_ADC_v1_30.Controller.cydrcerrors.AverageOverflowNotice);
            }
            if (CyDrc.CheckAverageAltRes(m_params) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                    global::Scan_ADC_v1_30.Controller.cydrcerrors.AltResolutionAverageNotice);
            }
            if (CyModelUtils.AnyConfigUsesFilter(m_params) == true
                && m_params.IsFilterAllowed == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    string.Format(
                    global::Scan_ADC_v1_30.Controller.cydrcerrors.FilterNotSupportedNotice,
                    ProjectPartNumber(args.InstQueryV1)));
            }

            var adcDrcMessages = CyDrc.AdcClockDrcMessages(m_params);
            foreach (var message in adcDrcMessages)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    message);
            }
        }

        #endregion ICyDRCProvider_v1 members

        #region Parameter loading methods

        private void LoadEditableParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_params = new CyParameters(instEdit, instEdit, termQuery);
            var isFilterAllowed = DeviceAllowsFilter(instEdit);
            m_params.IsFilterAllowed = isFilterAllowed;
        }

        private void LoadReadOnlyParameters(ICyInstQuery_v1 instQuery)
        {
            m_params = new CyParameters(instQuery);
            var isFilterAllowed = DeviceAllowsFilter(instQuery);
            m_params.IsFilterAllowed = isFilterAllowed;
        }

        private void LoadReadTermParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
        {
            m_params = new CyParameters(instQuery, termQuery);
            var isFilterAllowed = DeviceAllowsFilter(instQuery);
            m_params.IsFilterAllowed = isFilterAllowed;
        }

        #endregion Parameter loading methods

        #region Design queries

        // Filter is allowed if device has UABs.
        static private bool DeviceAllowsFilter(ICyInstQuery_v1 instQuery)
        {
            var deviceQuery = instQuery.DeviceQuery;
            var uabCount = deviceQuery.GetFeatureParameter("m0s8pass4b", "NR_UABS");
            var filterOK = (uabCount > 0) ? true : false;

            return filterOK;
        }

        // Return project part number.
        static public string ProjectPartNumber(ICyInstQuery_v1 instQuery)
        {
            var deviceQuery = instQuery.DeviceQuery;
            string partNumber = deviceQuery.PartNumber;
            return partNumber;
        }

        #endregion Design queries
    }
}
