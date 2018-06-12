/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Drawing;

namespace PowerMonitor_P4_v2_10
{
    public partial class CyCustomizer :
        ICyParamEditHook_v1,
        ICyAPICustomize_v1,
        ICyDRCProvider_v1,
        ICyExprEval_v2
    {
        private CyParameters m_params;
        private ICyTabbedParamEditor m_editor;

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_params = new CyParameters(edit, termQuery);

            m_params.GlobalEditMode = false;

            m_editor = edit.CreateTabbedParamEditor();
            CyGeneralTab basicTab = new CyGeneralTab(m_params);
            CyVoltagesTab voltagesTab = new CyVoltagesTab(m_params);

            edit.NotifyWhenDesignUpdates(basicTab.UpdateClockData);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_params.GlobalEditMode = false;
                basicTab.UpdateUI(true);
                m_params.GlobalEditMode = true;
            };

            m_editor.AddCustomPage(Resources.BasicTabDisplayName, basicTab, exprDelegate, basicTab.TabName);
            m_editor.AddCustomPage(Resources.VoltagesTabDisplayName, voltagesTab, exprDelegate, voltagesTab.TabName);

            m_editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            m_editor.UseBigEditor = true;

            basicTab.UpdateUI(false);
            basicTab.VisibleChanged += UpdateVref;
            m_params.GlobalEditMode = true;

            CyEditingWrapperControl.m_runMode = true;

            var result = m_editor.ShowDialog();
            return result;
        }

        private void UpdateVref(object sender, EventArgs e)
        {
            CyGeneralTab basicTab = sender as CyGeneralTab;
            if (basicTab != null && basicTab.Visible)
                basicTab.UpdateVref();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return false;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        #region ICyAPICustomize_v1 Members
        private const string DEFAULT_VALUE = "0";
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;

            string element = string.Empty;
            
            if (m_params == null)
            {
                m_params = new CyParameters(query);
            }
            string instanceName = m_params.InstanceName;

            // Voltages declarations
            string minAcqTime = "{ ";
            string uvWarnThreshold = "{ ";
            string ovWarnThreshold = "{ ";
            string uvFaultThreshold = "{ ";
            string ovFaultThreshold = "{ ";
            string voltageScale = "{ ";
            string countScale = "{ ";

            string defaultFaultMode = "{ ";

            // Scaling factor calculations
            decimal vrefRead_mV = Additional.cyutils.GetVrefValue(query, m_params) * 1000;
            double maxVoltage = (double) vrefRead_mV * 2; // Maximum voltage in millivolts
            double countsPerMv = CyParamRanges.ADC_COUNT_MAX / maxVoltage;
            double mvPerCount = maxVoltage / CyParamRanges.ADC_COUNT_MAX;

            for (int i = 0; i < m_params.VoltagesTable.Count; i++)
            {
                element = CyParameters.NullableDoubleToDouble(m_params.VoltagesTable[i].m_minAcqTime_ns).ToString();
                minAcqTime += (i < m_params.VoltagesTable.Count - 1) ? element + "ul, " : element + "ul }";

                element = ((UInt16)(CyParameters.NullableDoubleToDouble(m_params.VoltagesTable[i].m_uvWarningTreshold) * 1000)).ToString();
                uvWarnThreshold += (i < m_params.VoltagesTable.Count - 1) ? element + "ul, " : element + "ul }";

                element = ((UInt16)(CyParameters.NullableDoubleToDouble(m_params.VoltagesTable[i].m_ovWarningTreshold) * 1000)).ToString();
                ovWarnThreshold += (i < m_params.VoltagesTable.Count - 1) ? element + "ul, " : element + "ul }";

                element = ((UInt16)(CyParameters.NullableDoubleToDouble(m_params.VoltagesTable[i].m_uvFaultTreshold) * 1000)).ToString();
                uvFaultThreshold += (i < m_params.VoltagesTable.Count - 1) ? element + "ul, " : element + "ul }";

                element = ((UInt16)(CyParameters.NullableDoubleToDouble(m_params.VoltagesTable[i].m_ovFaultTreshold) * 1000)).ToString();
                ovFaultThreshold += (i < m_params.VoltagesTable.Count - 1) ? element + "ul, " : element + "ul }";

                //Voltage scaling factor is floating point value from .001 to 1. Multiply by 2^16 to make the firmware faster with >> 16.
                element = ((UInt32)(CyParameters.NullableDoubleToDouble((m_params.VoltagesTable[i].m_inputScalingFactor) * 0x10000 * (countsPerMv)))).ToString();
                voltageScale += (i < m_params.VoltagesTable.Count - 1) ? element + "ul, " : element + "ul }";

                element = ((UInt32)(CyParameters.NullableDoubleToDouble(((0x10000 / m_params.VoltagesTable[i].m_inputScalingFactor)) * mvPerCount))).ToString();
                countScale += (i < m_params.VoltagesTable.Count - 1) ? element + "ul, " : element + "ul }";
                
                // Create an initalization value for the fault modes from the customerizer
                element = Convert.ToString(Convert.ToByte(m_params.FaultSourcesOV) + (Convert.ToByte(m_params.FaultSourcesUV) << 1));
                defaultFaultMode += (i < m_params.VoltagesTable.Count - 1) ? element + "u, " : element + "u }";
              
            }

            /* Voltages table arrays */
            paramDict.Add("MinAcqTimeInit", minAcqTime);
            paramDict.Add("UVWarnThresholdInit", uvWarnThreshold);
            paramDict.Add("OVWarnThresholdInit", ovWarnThreshold);
            paramDict.Add("UVFaultThresholdInit", uvFaultThreshold);
            paramDict.Add("OVFaultThresholdInit", ovFaultThreshold);
            paramDict.Add("VoltageScaleInit", voltageScale);
            paramDict.Add("CountScaleInit", countScale);

            /* ADC settings */
            Int32 adcRange = Additional.cyutils.GetAdcRange_mV(query, m_params);
            Int32 vrefApiParam = (Int32)vrefRead_mV;
            paramDict.Add("AdcVrefValue_mV", vrefApiParam.ToString());
            paramDict.Add("AdcRange_mV", adcRange.ToString());

            /* Default fault mode value */
            paramDict.Add("FaultModeDefault", defaultFaultMode);

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            if (m_params == null)
            {
                m_params = new CyParameters(args.InstQueryV1, args.TermQueryV1);
            }

            /* Check for Empty Voltage Table rows */
            for (int i = 0; i < m_params.VoltagesTable.Count; i++)
            {
                if (CyParameters.VoltageTableRowHasEmptyCells(m_params, m_params.VoltagesTable[i])) // this means that empty row was saved
                {
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.VoltagesTableEmptyRowsDRC);
                    break;
                }
            }

            /* Check that the number of pins does not exceed the available in the system */
            #region Calculate pins count
            int pinsCount = m_params.NumConverters + m_params.NumAuxChannels;
            for (int i = 0; i < m_params.NumConverters; i++)
                //if (m_params.VoltagesTable[i].m_voltageMeasurementType == CyEVInternalType.Differential) pinsCount++;
            #endregion

            if (pinsCount > CyParamRanges.MAX_PINS_IN_SYSTEM)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.PinsCountLimitation);

            /* Throw an error if clocking the ADC outside of the limits */
            double roundedAdcClock = Math.Round(CyClock.GetClockRate_Hz(m_params.m_term, m_params.ADC_PATH, m_params.ADC_CLK)/10.0) * 10;
            if(roundedAdcClock > CyClock.GetMaxAdcClock_Hz(m_params) || roundedAdcClock < CyClock.ADC_CLOCK_MINIMUM)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.AdcClockDividerError);
            }
            else
            {
                /* Warn if the clock divider is not optimal */
                if (!CyClock.IsAdcClockOptimal(m_params))
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info, Resources.AdcClockDividerOptimization);   
            }    
        }
        #endregion

        #region ICyExprEval_v2

        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "DefaultVrefSelect":
                    return new CyExprEvalFuncEx(DefaultVrefSelect);
                case "DefaultVrefVoltage":
                    return new CyExprEvalFuncEx(DefaultVrefVoltage);
                case "GetVrefVoltageMv":
                    return new CyExprEvalFuncEx(GetVrefVoltageMv);
                case "GetVrefSelect":
                    return new CyExprEvalFuncEx(GetVrefSelect);
                case "DefaultAdcRange":
                    return new CyExprEvalFuncEx(DefaultAdcRange);
                default:
                    return null;
            }
        }

        object DefaultVrefSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            var result = (int) CyEVrefSelect.Vref_1024mVBypass;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null))
            {
                if (Additional.cyutils.IsSrssLite(creatorArgs.InstQuery))
                {
                    result = (int) CyEVrefSelect.Vref_InternalBypass;
                }
                else
                {
                    result = (int) CyEVrefSelect.Vref_1024mVBypass;
                }
            }   
            
            return result;
        }

        object DefaultVrefVoltage(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            int result = 1024;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null))
            {
                if (Additional.cyutils.IsSrssLite(creatorArgs.InstQuery))
                {
                    result = 1200;
                }
                else
                {
                    result = 1024;
                }
            }

            return result;
        }

        object GetVrefVoltageMv(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            uint result = 1024;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null))
            {
                CyParameters my_params = new CyParameters(creatorArgs.InstQuery);
                if(my_params != null)
                {

                    result = (uint) (Additional.cyutils.GetVrefValue(creatorArgs.InstQuery, my_params) * 1000);
                }
            }

            return result;
        }

        object GetVrefSelect(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            CyEVrefSelect result = CyEVrefSelect.Vref_1024mV;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null))
            {
                CyParameters my_params = new CyParameters(creatorArgs.InstQuery);
                if (my_params != null)
                {
                    if(my_params.VrefSelect != CyEVrefSelect.Vref_External)
                    {
                        if (Additional.cyutils.IsSrssLite(creatorArgs.InstQuery))
                        {
                            if(my_params.VrefSelect == CyEVrefSelect.Vref_1024mV)
                            {
                                result = CyEVrefSelect.Vref_Internal;
                            }
                            else if (my_params.VrefSelect == CyEVrefSelect.Vref_1024mVBypass)
                            {
                                result = CyEVrefSelect.Vref_InternalBypass;
                            }
                            else
                            {
                                result = my_params.VrefSelect;
                            }
                        }
                        else
                        {
                            if (my_params.VrefSelect == CyEVrefSelect.Vref_Internal)
                            {
                                result = CyEVrefSelect.Vref_1024mV;
                            }
                            else if (my_params.VrefSelect == CyEVrefSelect.Vref_InternalBypass)
                            {
                                result = CyEVrefSelect.Vref_1024mVBypass;
                            }
                            else
                            {
                                result = my_params.VrefSelect;
                            }
                        }
                    }
                    else
                    {
                        result = CyEVrefSelect.Vref_External;
                    }
                }
            }

            return (uint) result;
        }

        object DefaultAdcRange(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
    ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            int result = 2048;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null))
            {
                if (Additional.cyutils.IsSrssLite(creatorArgs.InstQuery))
                {
                    result = 2400;
                }
                else
                {
                    result = 2048;
                }
            }
            return result;
        }
        #endregion

        
    }
}
