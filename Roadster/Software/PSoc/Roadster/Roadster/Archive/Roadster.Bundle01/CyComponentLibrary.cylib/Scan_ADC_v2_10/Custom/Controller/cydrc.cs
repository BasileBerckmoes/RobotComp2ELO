/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v2_10
{
    /// <summary>
    /// Core functions for customizer parameter build DRC functions.
    /// </summary>
    public static class CyDrc
    {
        /// <summary>
        /// Check that each active configuration has at least one channel enabled.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if each config has an enabled channel, false if not</returns>
        public static bool CheckChannelsEnabled(CyParameters parameters)
        {
            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                CyConfigModel config = parameters.GetConfig(num);
                bool isEnabled = false;
                foreach (CyChannelModel channel in config.ChannelList)
                {
                    if (channel.Enabled)
                    {
                        isEnabled = true;
                        break;
                    }
                }
                if (isEnabled == false)
                {
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Check that each active configuration has a valid VrefSource and 
        /// bypass combination.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if each config has a valid combination of Vrefsource
        /// and bypass, false otherwise.</returns>
        public static bool CheckVrefBypassNotice(CyParameters parameters)
        {
            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                CyConfigModel config = parameters.GetConfig(num);

                if (config.Sar.VrefSource == CyEVrefSource.VREFSOURCE_VDDA
                    && config.Sar.VrefBypass)
                {
                    return false;
                }
            }
            return true;
        }

        /// <summary>
        /// Check that each active configuration is not using the external
        /// device pin if that pin is not available.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if each config has a valid combination of Vrefsource
        /// and available external vref connection, false otherwise.</returns>
        public static bool CheckVrefExternalNotice(CyParameters parameters)
        {
            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                CyConfigModel config = parameters.GetConfig(num);

                if (config.Sar.VrefSource == CyEVrefSource.VREFSOURCE_DEVPIN
                    && !config.Sar.HasExtVrefConnection)
                {
                    return false;
                }
            }
            return true;
        }

        /// <summary>
        /// Check that all configurations have Vref not exceeding Vdda
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="maxVref">Assigned Vdda value</param>
        /// <returns>False if any config's Vref exceeds Vdda, otherwise true.</returns>
        public static bool CheckVrefNotTooHigh(CyParameters parameters, out double maxVref)
        {
            maxVref = CyVoltage.GetDesignVrefValue(parameters, CyEVrefSource.VREFSOURCE_VDDA);

            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                var configVref = CyModelUtils.GetConfigVrefValue(parameters, num);

                if (configVref > maxVref)
                {
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Check that all configurations have Vref not below min value.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="minVref">Assigned minimum Vref value.</param>
        /// <returns>False if any config's Vref below minimum, otherwise true.</returns>
        public static bool CheckVrefNotTooLow(CyParameters parameters, out double minVref)
        {
            minVref = CySarRanges.MIN_VREF;

            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                var configVref = CyModelUtils.GetConfigVrefValue(parameters, num);

                if (configVref < minVref)
                {
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Check that each active configuration has a valid combination of
        /// VnegSource and SE Result format.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if each config has SE format Unsigned if it uses
        /// a VnegSource that is reasonable to expect could result in negative
        /// results.</returns>
        public static bool CheckVnegResultNotice(CyParameters parameters)
        {
            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                CyConfigModel config = parameters.GetConfig(num);

                if (config.VnegSource != CyEVnegSource.VNEGSOURCE_VREFSHORT
                    && config.SingleEndedResultFormat == CyENumberFormat.UNSIGNED_FORMAT)
                {
                    for (int i = 0; i < config.NumChannels; i++)
                    {
                        if (config.ChannelList[i].InputMode == CyEInputMode.SINGLE_ENDED_CHAN)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        /// <summary>
        /// Check that each active configuration has valid ranges for its limit
        /// interrupts.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if each config has a range for interrupt limits that
        /// makes sense for the selected mode (Low limit less than High limit). .</returns>
        public static bool CheckLimitNotice(CyParameters parameters)
        {
            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                CyConfigModel config = parameters.GetConfig(num);

                if (config.LowLimit >= config.HighLimit
                    && (config.CompareMode == CyELimitComparisonMode.OUTSIDE
                        || config.CompareMode == CyELimitComparisonMode.BETWEEN))
                {
                    return false;
                }
            }
            return true;
        }

        /// <summary>
        /// Check that each active configuration's ADC clock is in it's valid range.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of ADC clock error messages, if any</returns>
        public static List<string> AdcClockDrcMessages(CyParameters parameters)
        {
            var messages = new List<string>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                if (CyModelUtils.AdcClockOutOfRange(parameters, configNum))
                {
                    CyConfigModel config = parameters.GetConfig(configNum);
                    string text;
                    
                    if(parameters.ExternalClk == false)
                    {
                        text = string.Format(Scan_ADC_v2_10.Controller.cydrcerrors.AdcInternalClockOutOfRange,
                            CyModelUtils.ClockRangeMHzText(config.Sar.MinSarFrequency, config.Sar.MaxSarFrequency));
                    }
                    else
                    {
                        text = string.Format(
                        Scan_ADC_v2_10.Controller.cydrcerrors.AdcClockOutOfRange,
                        configNum,
                         CyModelUtils.ClockFreqMHzText(config.ActualAdcClockHz),
                        CyModelUtils.ClockRangeMHzText(config.Sar.MinSarFrequency, config.Sar.MaxSarFrequency));
                    }
                    
                    messages.Add(text);
                }
            }

            return messages;
        }

        /// <summary>
        /// Check that each active configuration can't overflow if interleaved
        /// averaging is used.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if each config has a small enough number of averages
        /// if interleaved averaging is used, and at least one channel uses
        /// averaging.</returns>
        public static bool CheckAverageOverflow(CyParameters parameters)
        {
            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                CyConfigModel config = parameters.GetConfig(num);

                if (config.SamplesAveraged > CyESamplesAveraged.SIXTEEN_SAMPLES
                    && (config.AveragingMode == CyEAveragingMode.INTERLEAVED_AVG))
                {
                    for (int i = 0; i < config.NumChannels; i++)
                    {
                        if (config.ChannelList[i].UseAveraging)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        /// <summary>
        /// Check that no channel uses averaging and alternate resolution
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if no averaged channel uses alt res, otherwise false</returns>
        public static bool CheckAverageAltRes(CyParameters parameters)
        {
            for (int num = 0; num < parameters.NumberOfConfigs; num++)
            {
                CyConfigModel config = parameters.GetConfig(num);

                for (int i = 0; i < config.NumChannels; i++)
                {
                    if (CyGuiChecks.IsAltResAverage(config, i))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        /// <summary>
        /// Check that all configurations use the same Sample Mode
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True if all configs use the same sample mode type, otherwise false</returns>
        public static bool CheckSameSampleMode(CyParameters parameters)
        {
            return CyModelUtils.ConfigSampleModeMismatched(parameters);           
        }
    }
}