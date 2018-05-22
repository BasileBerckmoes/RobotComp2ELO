/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit.TerminalControl_v1;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;
using ADC_SAR_SEQ_P4_v2_50.Tabs;

namespace ADC_SAR_SEQ_P4_v2_50
{
    public class CyCustomizer : 
        ICyParamEditHook_v1,
        ICyShapeCustomize_v1,
        ICyAPICustomize_v1,
        ICyDRCProvider_v1,        
        ICyDesignClient_v2,
        ICyExprEval_v2
    {
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            parameters.GlobalEditMode = false;            

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            
            CyTerminalControl_v1 interconnectTab = null;
            
            // Create tab pages
            CyGeneralTab generalTab = new CyGeneralTab(parameters);
            CyChannelsTab channelsTab = new CyChannelsTab(parameters);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.UpdateUI();
                channelsTab.UpdateUI();
                if (interconnectTab != null)
                {
                    UpdateInterconnectDisplay(parameters, interconnectTab);
                }
                parameters.GlobalEditMode = true;
            };

            // This code will be executed every time when any parameter is changed.
            CyParamExprDelegate onParamChangeDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;                
                if (interconnectTab != null)
                {
                    UpdateInterconnectDisplay(parameters, interconnectTab);
                }
                parameters.GlobalEditMode = true;
            };

            editor.ParamExprCommittedDelegate = onParamChangeDelegate;

            // Add tabs to the customizer
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, exprDelegate, generalTab.TabName);
            editor.AddCustomPage(Resources.ChannelsTabDisplayName, channelsTab, exprDelegate, channelsTab.TabName);

            // System Builder support
            if (parameters.InstQuery.DeviceQuery.IsPSoC4 && edit.IsInSystemBuilder)
            {
                interconnectTab = new CyTerminalControl_v1(edit);
                UpdateInterconnectDisplay(parameters, interconnectTab);
                editor.AddCustomPage(Resources.InterconnectTabDisplayName, interconnectTab, exprDelegate, "Interconnect");
            }

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            generalTab.UpdateUI();
            channelsTab.UpdateUI();

            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(generalTab.UpdateClockData);

            return editor.ShowDialog();
        }

        void UpdateInterconnectDisplay(CyParameters param, CyTerminalControl_v1 termControl)
        {
            CyTermControlRow_v1[] clocks = new CyTermControlRow_v1[1];
            clocks[0] = new CyTermControlRow_v1(CyTermName.ACLK, CyTermName.ACLK,
                        new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.ClockTermDescription);
            termControl.Clocks = clocks;

            CyTermControlRow_v1[] interrupts = new CyTermControlRow_v1[2];
            interrupts[0] = new CyTermControlRow_v1(CyTermName.EOC, CyTermName.EOC,
                            new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                            Resources.EOCTermDescription);
            interrupts[1] = new CyTermControlRow_v1(CyTermName.SDONE, CyTermName.SDONE,
                            new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                            Resources.SDONETermDescription);
            termControl.Interrupts = interrupts;

            List<CyTermControlRow_v1> otherTerminals = new List<CyTermControlRow_v1>();

            List<CyChannelsConfigTableRow> configTable = param.m_channelsConfTable.m_channelsConfigTable;
            for (int i = 0; i < param.SequencedChannels; i++)
            {                
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.VINPLUS + i, CyTermName.VINPLUS + i,
                    new CyTermMode_v1[] {CyTermMode_v1.Internal }, 
                    Resources.PlusInputTermDescription + i.ToString() + "."));

                bool singleEnded = param.TableRowIndex(i) < configTable.Count &&
                    configTable[param.TableRowIndex(i)].m_mode == CyEMode.Single;

                if (!singleEnded)
                {
                    otherTerminals.Add(new CyTermControlRow_v1(CyTermName.VINMINUS + i, CyTermName.VINMINUS + i,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal },
                    Resources.MinusInputTermDescription + i.ToString() + "."));
                }
            }

            if (param.InjectionChannelEnabled)
            {                
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.VINPLUSINJ, CyTermName.VINPLUSINJ,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.PlusINJTermDescription));

                int injIdx = param.SequencedChannels;
                bool singleEnded = configTable[param.TableRowIndex(injIdx)].m_mode == CyEMode.Single;

                if (!singleEnded)
                {                    
                    otherTerminals.Add(new CyTermControlRow_v1(CyTermName.VINMINUSINJ, CyTermName.VINMINUSINJ,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.MinusINJTermDescription));
                }
            }

            if (param.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Other)
            {                
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.VINNEG, CyTermName.VINNEG,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.VINNEGTermDescription));
            }

            if (param.SampleModeType == CyESampleMode.HardwareSOC)
            {                
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.SOC, CyTermName.SOC,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.SOCTermDescription));
            }

            if (param.VrefSelect == CyEVRefSelect.InternalVref ||
                param.VrefSelect == CyEVRefSelect.InternalVrefBypassed)
            {
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.VREF, CyTermName.VREF,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.VREFTermDescription));
            }

            termControl.Other = otherTerminals;
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

        #region ICyShapeCustomize_v1 Members
        public CyCustErr CustomizeShapes(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyParameters shapeParameter = new CyParameters(query, termEdit);

            // Create shape builer
            CyShapesBuilder builder = new CyShapesBuilder(shapeParameter, shapeEdit, termEdit);
            builder.DrawSymbol();

            return CyCustErr.OK;
        }
        #endregion

        #region ICyAPICustomize_v1 Members
        private const char SEPARATOR = ',';
        private const string UNSIGNED = "u";
        private const byte MAX_LINE_LENGTH = 120;
        private const uint LIMIT_DETECT_ON = 0x00000002;
        private const uint SATURATION_ON = 0x00000001;
        private const uint DIFFERENTIAL_EN = 0x00000100;
        private const uint ALT_RESOLUTION_ON = 0x00000200;
        private const uint AVG_ON = 0x00000400;
        private const uint ACQ_TIME_A = 0x00000000;
        private const uint ACQ_TIME_B = 0x00001000;
        private const uint ACQ_TIME_C = 0x00002000;
        private const uint ACQ_TIME_D = 0x00003000;

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0)
            {
                paramDict = customizers[0].MacroDictionary;
            }

            CyParameters parameters = new CyParameters(query, termQuery);
            string instanceName = parameters.InstanceName;

            int numChannels = parameters.SequencedChannels + 1;

            StringBuilder channelsConfigStr = new StringBuilder();
            channelsConfigStr.Append("const uint32 CYCODE ");
            channelsConfigStr.Append(instanceName);
            channelsConfigStr.Append("_channelsConfig[] = { ");

            for (int i = 0; i < numChannels; i++)
            {
                // Skip Injection channel
                if (i == CyChannelsConfigTable.INJ_CHANNEL_INDEX)
                {
                    continue;
                }

                uint channelConf = GetChannelConfiguration(parameters.ChannelsConfigTable[i]);
                channelsConfigStr.Append(ToUInt32HexStr(channelConf));
                if (i < parameters.SequencedChannels)
                {
                    channelsConfigStr.Append(", ");
                }
            }

            // Add Injection channel if it's enabled to the array's end
            if (parameters.ChannelsConfigTable[CyChannelsConfigTable.INJ_CHANNEL_INDEX].m_enabled == true)
            {
                channelsConfigStr.Append(", ");
                uint channelConf =
                    GetChannelConfiguration(parameters.ChannelsConfigTable[CyChannelsConfigTable.INJ_CHANNEL_INDEX]);
                channelsConfigStr.Append(ToUInt32HexStr(channelConf));
            }

            channelsConfigStr.Append(" };");
            paramDict.Add("channelsConfig", WordWrap(channelsConfigStr.ToString()));

            paramDict.Add("NominalClockFrequency", Convert.ToInt32(parameters.NominalClockFrequencyHz).ToString());
            paramDict[CyParamNames.VREF_VALUE] = Convert.ToInt32(parameters.ReferenceVoltageValue * 1000.0).ToString();

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }

        private UInt32 GetChannelConfiguration(CyChannelsConfigTableRow channel)
        {
            uint channelConf = 0;

            // Resolution
            if (channel.m_resolution == CyEResolution.Alternative)
            {
                channelConf |= ALT_RESOLUTION_ON;
            }

            // AVG
            if (channel.m_averaged)
            {
                channelConf |= AVG_ON;
            }

            // Acquisition time
            switch (channel.m_acqTime)
            {
                case CyEAcquisionTime.AClocks:
                    channelConf |= ACQ_TIME_A;
                    break;
                case CyEAcquisionTime.BClocks:
                    channelConf |= ACQ_TIME_B;
                    break;
                case CyEAcquisionTime.CClocks:
                    channelConf |= ACQ_TIME_C;
                    break;
                case CyEAcquisionTime.DClocks:
                    channelConf |= ACQ_TIME_D;
                    break;
            }

            // Limit detect
            if (channel.m_limitsDetectIntrEnabled)
            {
                channelConf |= LIMIT_DETECT_ON;
            }

            // Saturation
            if (channel.m_saturationIntrEnabled)
            {
                channelConf |= SATURATION_ON;
            }

            if (channel.m_mode == CyEMode.Diff)
            {
                channelConf |= DIFFERENTIAL_EN;
            }

            return channelConf;
        }

        private string ToUInt32HexStr(UInt32 value)
        {
            string hexValue = value.ToString("X");
            hexValue = hexValue.PadLeft(8, '0');
            
            return "0x" + hexValue + UNSIGNED;
        }

        private string WordWrap(string str)
        {
            string result = string.Empty;
            string line = string.Empty;
            string[] splitted = str.Split(SEPARATOR);
            for (int i = 0; i < splitted.Length; i++)
            {
                if ((line.Length + splitted[i].Length + 1) <= MAX_LINE_LENGTH)
                {
                    line += splitted[i] + SEPARATOR;
                }
                else
                {
                    line += Environment.NewLine;
                    result += line;
                    line = string.Empty;
                    line += splitted[i] + SEPARATOR;
                }
            }
            result += line.Remove(line.Length - 1);

            return result;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            #region Verify channels enabling configuration
            if (parameters.CheckChannelsEnabled() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DRCAllChannelsDisabledError);
            }
            #endregion

            #region Verify VRef Select value
            string errMsg = parameters.GetVRefSelectError();
            if (!string.IsNullOrEmpty(errMsg))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, errMsg);
            }
            #endregion

            #region Verify reference voltage value
            errMsg = parameters.GetRefVoltageValueError();
            if (!string.IsNullOrEmpty(errMsg))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, errMsg);
            }
            #endregion

            #region Verify clock frequency
            errMsg = parameters.GetClockFrequencyError(parameters.NominalClockFrequencyHz);
            if (string.IsNullOrEmpty(errMsg) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, errMsg);
            }
            #endregion

            #region Compare actual sample rate to sample rate
            if (parameters.ClockSourceType == CyESarAdcClockSrc.Internal)
            {
                double clkFreq = CyClock.GetClockFrequencyHz(parameters.TermQuery, true, CyClock.INTERNAL_CLOCK_OR_GATE_NAME);
                if (CyClock.IsFrequencyKnown(clkFreq))
                {
                    UInt32 sampleRate = parameters.GetSampleRate(parameters.ClockFrequency);
                    UInt32 actualSampleRate = parameters.GetSampleRate(clkFreq);

                    if (sampleRate != actualSampleRate)
                    {
                        yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                            string.Format(Resources.DRCSampleRateInfo, actualSampleRate, sampleRate));
                    }
                }
            }
            #endregion
        }
        #endregion

        #region ICyExprEval_v2
        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "IsSarAdcExtVrefDedicated":
                    return new CyExprEvalFuncEx(IsSarAdcExtVrefDedicated);

                default:
                    return null;
            }
        }

        object IsSarAdcExtVrefDedicated(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (custArgs.InstQuery == null)
                return false;

            bool isExtVrefDedicated;
            CyCustErr err = custArgs.InstQuery.DeviceQuery.PSoC4DeviceInfoQueryV1.IsSarAdcExtVrefDedicated(
                out isExtVrefDedicated);

            if (err.IsNotOK)
                isExtVrefDedicated = false;

            return isExtVrefDedicated;
        }
        #endregion
    }
}
