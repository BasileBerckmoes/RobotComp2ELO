/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace Scan_ADC_v2_10
{
    /// <summary>
    /// Utility functions for Scan_ADC model parameters.
    /// </summary>
    public static class CyModelUtils
    {
        const int HZ_PER_MHZ = 1000000;

        public static long AverageEnum2Long(CyESamplesAveraged sampsAvgd)
        {
            var retval = 1;
            switch (sampsAvgd)
            {
                case CyESamplesAveraged.TWO_SAMPLES:
                    retval = 2;
                    break;
                case CyESamplesAveraged.FOUR_SAMPLES:
                    retval = 4;
                    break;
                case CyESamplesAveraged.EIGHT_SAMPLES:
                    retval = 8;
                    break;
                case CyESamplesAveraged.SIXTEEN_SAMPLES:
                    retval = 16;
                    break;
                case CyESamplesAveraged.THIRTYTWO_SAMPLES:
                    retval = 32;
                    break;
                case CyESamplesAveraged.SIXTYFOUR_SAMPLES:
                    retval = 64;
                    break;
                case CyESamplesAveraged.ONETWENTYEIGHT_SAMPLES:
                    retval = 128;
                    break;
                case CyESamplesAveraged.TWOFIFTYSIX_SAMPLES:
                    retval = 256;
                    break;
                default:
                    retval = 1;
                    break;
            }
            return retval;
        }
        /// <summary>
        /// Return bitmasks of the CTRL.VREF_SEL and VREF_BYP_CAP_EN bits for each configuration.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration</returns>
        public static List<uint> ConfigCtrlVrefSelMasks(CyParameters parameters)
        {
            List<uint> allMasks = new List<uint>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                uint mask = 0;
                switch(configModel.VrefSource)
                {
                    case CyEVrefSource.VREFSOURCE_VBGR:
                        {
                            mask = 0x4;
                            break;
                        }
                    case CyEVrefSource.VREFSOURCE_DEVPIN:
                        {
                            mask = 0x5;
                            break;
                        }
                    case CyEVrefSource.VREFSOURCE_HALFVDDA:
                        {
                            mask = 0x6;
                            break;
                        }
                    case CyEVrefSource.VREFSOURCE_VDDA:
                        {
                            mask = 0x7;
                            break;
                        }
                    default:
                        {
                            mask = 0x0;
                            break;
                        }
                }
                mask = mask << 0x4;
                if (configModel.Sar.VrefBypass && ((mask != 0x60) || (mask != 0x70)))    
                {
                    mask |= 0x80;   //Set bypass cap enable but never for Vdda or Vdda/2
                }
                allMasks.Add(mask);
            }
            return allMasks;
        }

        /// <summary>
        /// Return a list of channel index information.
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of channel indexes for each configurations</returns>
        public static List<int> ChannelIndexes(CyParameters parameters)
        {
            List<int> channelIdx = new List<int>();
            int channelSum = 0;
            //Config zero channel index is always zero
            channelIdx.Add(0);
            for (int cfgIndex = 0; cfgIndex < (parameters.NumberOfConfigs-1); cfgIndex++)
            {
                CyConfigModel configModel = parameters.GetConfig(cfgIndex);
                channelSum += (int)configModel.NumChannels;
                channelIdx.Add(channelSum);
            }

            return channelIdx;
        }

        /// <summary>
        /// Return a list of masks for each channel configuration.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of masks for all channel configurations</returns>
        public static List<uint> AllChannelMasks(CyParameters parameters)
        {
            List<uint> allMasks = new List<uint>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                for (int chanNum = 0; chanNum < configModel.NumChannels; chanNum++)
                {
                    CyEInputMode mode = configModel.ChannelList[chanNum].InputMode;
                    uint mask = 0;

                    if (IsChannelDifferential(mode) || IsChannelFilter(mode))
                    {
                        mask |= (1u << 8);
                    }

                    if (configModel.ChannelList[chanNum].UseAltResolution)
                    { 
                        mask |= (1u << 9);
                    }
                    if (configModel.ChannelList[chanNum].UseAveraging)
                    {
                        mask |= (1u << 10);
                    }
                    mask |= (uint) configModel.ChannelList[chanNum].ApertureTimer << 12;
                    
                    /*TODO: DSI_OUT_EN is not available in 4B-S0. E-mailed MEH to determine if we should add it for parts with DSI  */
                    allMasks.Add(mask);
                }
            }
            return allMasks;
        }

        /// <summary>
        /// Return number of channels in each active configuration.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of channel numbers for active configurations</returns>
        public static List<int> ChannelCounts(CyParameters parameters)
        {
            List<int> counts = new List<int>();

            for (int cfgIndex = 0; cfgIndex < parameters.NumberOfConfigs; cfgIndex++)
            {
                CyConfigModel configModel = parameters.GetConfig(cfgIndex);
                counts.Add((int)configModel.NumChannels);
            }

            return counts;
        }
        
        /// <summary>
        /// Return bitmasks of each channels range interrupt mask.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration's range interrupt</returns>
        public static List<uint> ChannelLimitInterruptMasks(CyParameters parameters)
        {
            List<uint> enableMasks = new List<uint>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                uint mask = 0;
                for (int chanNum = 0; chanNum < configModel.NumChannels; chanNum++)
                {

                    if (configModel.ChannelList[chanNum].UseLimitInterrupt)
                    {
                        mask |= (1u << chanNum);
                    }
                }
                enableMasks.Add(mask);
            }

            return enableMasks;
        }

        /// <summary>
        /// Return bitmasks of each channels saturate interrupt mask.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration's saturate interrupt</returns>
        public static List<uint> ChannelSatInterruptMasks(CyParameters parameters)
        {
            List<uint> enableMasks = new List<uint>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                uint mask = 0;
                for (int chanNum = 0; chanNum < configModel.NumChannels; chanNum++)
                {

                    if (configModel.ChannelList[chanNum].UseSaturationInterrupt)
                    {
                        mask |= (1u << chanNum);
                    }
                }
                enableMasks.Add(mask);
            }

            return enableMasks;
        }

        /// <summary>
        /// Return bitmasks of enabled channels in each active configuration.
        /// Enabled channels are 1 bits, disabled channels are 0 bits.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration</returns>
        public static List<uint> ChannelEnableMasks(CyParameters parameters)
        {
            List<uint> enableMasks = new List<uint>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                uint mask = 0;
                for (int chanNum = 0; chanNum < configModel.NumChannels; chanNum++)
                {

                    if (configModel.ChannelList[chanNum].Enabled)
                    {
                        mask |= (1u << chanNum);
                    }
                }
                enableMasks.Add(mask);
            }

            return enableMasks;
        }

        public delegate bool IsChannelModeDelegate(CyEInputMode mode);

        /// <summary>
        /// Return bitmasks of differential channels in each active configuration.
        /// Differential channels are 1 bits, single ended channels are 0 bits.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration</returns>
        public static List<uint> ChannelDiffMasks(CyParameters parameters)
        {
            var diffMasks = ChannelModeMasks(parameters, IsChannelDifferential);

            return diffMasks;
        }

        /// <summary>
        /// Return bitmasks of single-ended channels in each active configuration.
        /// Single-ended channels are 1 bits, single ended channels are 0 bits.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration</returns>
        public static List<uint> ChannelSingleMasks(CyParameters parameters)
        {
            var singleMasks = ChannelModeMasks(parameters, IsChannelSingleEnded);

            return singleMasks;
        }

        /// <summary>
        /// Return bitmasks of filter channels in each active configuration.
        /// Filter channels are 1 bits, single ended channels are 0 bits.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration</returns>
        public static List<uint> ChannelFilterMasks(CyParameters parameters)
        {
            var filterMasks = ChannelModeMasks(parameters, IsChannelFilter);

            return filterMasks;
        }

        /// <summary>
        /// Return bitmasks of channels in each active configuration.
        /// Channels passing the mode filter are 1 bits, channels not matching are 0.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>List of bitmasks for each active configuration</returns>
        public static List<uint> ChannelModeMasks(
            CyParameters parameters, IsChannelModeDelegate IsTargetMode)
        {
            List<uint> modeMasks = new List<uint>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                uint mask = 0;
                for (int chanNum = 0; chanNum < configModel.ChannelList.Count; chanNum++)
                {
                    CyEInputMode mode = configModel.ChannelList[chanNum].InputMode;

                    if (IsTargetMode(mode))
                    {
                        mask |= (1u << chanNum);
                    }
                }
                modeMasks.Add(mask);
            }

            return modeMasks;
        }

        /// <summary>
        /// Return true if different configs use different sample modes
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>true if multiple configs have different sample modes</returns>
        public static bool ConfigSampleModeMismatched(CyParameters parameters)
        {
            uint sampleModeMask = 0;
            uint allOnes = 0;

            for (int index = 0; index < parameters.NumberOfConfigs; index++)
            {
                var config = parameters.GetConfig(index);
                if (config.ChannelList.Count > 0)
                {
                    if (config.FreeRunning == true)
                    {
                        sampleModeMask |= (1u << index);
                    }
                    allOnes |= (1u << index);
                }
            }

            if ((sampleModeMask != allOnes) && (sampleModeMask != 0))
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        /// <summary>
        /// Return true if configuration zero is Single-Shot sample mode.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>true, Single-shot, false: Continuous</returns>
        public static bool IsConfigZeroSingleShot(CyParameters parameters)
        {
            var config = parameters.GetConfig(0);
            return !config.FreeRunning;
        }

        /// <summary>
        /// Return bit mask showing which configurations use a UAB filter.
        /// Configurations using a filter are 1 bits, others are 0 bits.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>Bitmask of configs with filters</returns>
        public static uint ConfigFilterMasks(CyParameters parameters)
        {
            uint filterMask = 0;

            for (int index = 0; index < parameters.NumberOfConfigs; index++)
            {
                var config = parameters.GetConfig(index);
                if (config.ChannelList.Count > 0)
                {
                    var chan0 = config.ChannelList[0];
                    if (chan0.InputMode == CyEInputMode.FILTER_CHAN)
                    {
                        filterMask |= (1u << index);
                    }
                }
            }

            return filterMask;
        }

        /// <summary>
        /// Return an array of short aliases to be used for each filter, or an
        /// empty string if no filter for that channel.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>Array of strings for filter labels.</returns>
        public static string [] ConfigFilterAliases(CyParameters parameters)
        {
            string [] filterList;
            filterList = new string[parameters.NumberOfConfigs];
            for (int index = 0; index < parameters.NumberOfConfigs; index++)
            {
                var config = parameters.GetConfig(index);
                if (config.ChannelList.Count > 0)
                {
                    var chan0 = config.ChannelList[0];
                    if (chan0.InputMode == CyEInputMode.FILTER_CHAN)
                    {
                        switch(config.FilterType)
                        {
                            case CyEFilterType.BAND_PASS:
                                filterList[index] = "bp";
                                break;
                            case CyEFilterType.BAND_STOP:
                                
                                filterList[index] = "bs";
                                break;
                            case CyEFilterType.HIGH_PASS:
                                
                                filterList[index] = "hp";
                                break;
                            case CyEFilterType.LOW_PASS:
                                
                                filterList[index] = "lp";
                                break;
                            default:
                                break;
                        }
                    } else {
                        filterList[index] = "";
                    }
                }
            }

            return filterList;
        }
        /// <summary>
        /// Determine which configurations use Vneg terminals.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>For each config, true iff config uses a Vneg terminal</returns>
        public static List<bool> ConfigVnegTerms(CyParameters parameters)
        {
            List<bool> vnegTerms = new List<bool>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                vnegTerms.Add(ConfigUsesVnegTerminal(parameters, configNum));
            }

            return vnegTerms;
        }

        /// <summary>
        /// Returns an array of all Vneg sources.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>For each config, returns selected vneg source.</returns>
        public static List<CyEVnegSource> ConfigVnegSource(CyParameters parameters)
        {
            List<CyEVnegSource> vnegSource = new List<CyEVnegSource>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                vnegSource.Add(parameters.GetConfig(configNum).VnegSource);
            }

            return vnegSource;
        }
        /// <summary>
        /// Returns an array of all Vref sources.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>For each config, returns selected vref source.</returns>
        public static List<CyEVrefSource> ConfigVrefSource(CyParameters parameters)
        {
            List<CyEVrefSource> vrefSource = new List<CyEVrefSource>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                vrefSource.Add(parameters.GetConfig(configNum).VrefSource);
            }

            return vrefSource;
        }

        /// <summary>
        /// Determine which configurations use Vref terminals.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>For each config, true iff config uses a Vref terminal</returns>
        public static List<bool> ConfigVrefTerms(CyParameters parameters)
        {
            List<bool> vrefTerms = new List<bool>();

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                vrefTerms.Add(ConfigUsesVrefTerminal(parameters, configNum));
            }

            return vrefTerms;
        }

        /// <summary>
        /// Return total number of channels in all active configurations.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>Total number of channels</returns>
        public static int TotalChannelCount(CyParameters parameters)
        {
            List<int> counts = ChannelCounts(parameters);

            int total = 0;
            foreach (int chanCount in counts)
            {
                total += chanCount;
            }

            return total;
        }

        /// <summary>
        /// Convert raw channel number to a configuration and config channel number.
        /// 
        /// Raw channel numbers range from 0 up to the total number of channels in all
        /// configurations.  Config channel numbers range from 0 up to the number of
        /// channels in the configuration.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="rawChanNum">Raw channel number</param>
        /// <param name="configNum">returned configuration number</param>
        /// <param name="configChanNum">Returned configuration channel number</param>
        public static void RawChannelToConfigChannel(CyParameters parameters,
            int rawChanNum, out int configNum, out int configChanNum)
        {
            List<int> counts = ChannelCounts(parameters);

            configNum = 0;
            configChanNum = rawChanNum;
            foreach (int chanCount in counts)
            {
                if (configChanNum < chanCount)
                {
                    break;
                }
                configChanNum -= chanCount;
                configNum++;
            }

            Debug.Assert(configNum < counts.Count,
                string.Format("Raw channel number out of range {0} {1}",
                rawChanNum.ToString(), counts.Count.ToString()));
        }

        /// <summary>
        /// Convert a configuration and config channel number to a raw channel number.
        /// 
        /// Config channel numbers range from 0 up to the number of channels
        /// in the configurastion.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <param name="configChanNum">Configuration channel number</param>
        /// <returns>Raw channel number.</returns>
        public static int ConfigChannelToRawChannel(CyParameters parameters,
            int configNum, int configChanNum)
        {
            List<int> counts = ChannelCounts(parameters);

            int rawChanNum = 0;
            for (int index = 0; index < counts.Count; index++)
            {
                if (index < configNum)
                {
                    rawChanNum += counts[index];
                }
                else
                {
                    rawChanNum += Math.Min(configChanNum, counts[index] - 1);
                    break;
                }
            }

            return rawChanNum;
        }

        /// <summary>
        /// Determine a raw channel is differential or single-ended.
        /// 
        /// Raw channel numbers range from 0 up to the total number of channels in all
        /// configurations.  Config channel numbers range from 0 up to the number of
        /// channels in the configuration.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="chanIndex">Raw channel number</param>
        /// <returns>True if channel is differential, false if single-ended</returns>
        public static bool IsRawChannelDifferential(CyParameters parameters, int chanIndex)
        {
            int channelCount = TotalChannelCount(parameters);

            // If channel not used, return false.
            if (chanIndex >= channelCount)
            {
                return false;
            }

            // Otherwise check channel's input mode.
            int configNum;
            int chanNum;
            RawChannelToConfigChannel(parameters,
                chanIndex, out configNum, out chanNum);
            CyConfigModel configModel = parameters.GetConfig(configNum);
            CyEInputMode mode = configModel.ChannelList[chanNum].InputMode;

            return IsChannelDifferential(mode);
        }

        /// <summary>
        /// Return true if the specified configuration uses a Vneg terminal or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <returns>True iff configuration uses a Vneg terminal</returns>
        public static bool ConfigUsesVnegTerminal(CyParameters parameters, int configNum)
        {
            List<int> chanCounts = ChannelCounts(parameters);

            // If config not active, it doesn't use a Vneg.
            if (configNum >= chanCounts.Count)
            {
                return false;
            }

            // If no config channels are single ended, it doesn't use Vneg.
            var singleMasks = ChannelSingleMasks(parameters);
            if (singleMasks[configNum] == 0)
            {
                return false;
            }

            // Config uses a Vneg terminal iff the selected Vneg source is external.
            CyConfigModel configModel = parameters.GetConfig(configNum);
            return IsVnegSourceExternal(configModel.VnegSource);
        }

        /// <summary>
        /// Return true if the specified configuration uses a Vref terminal or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <returns>True iff configuration uses a Vref terminal</returns>
        public static bool ConfigUsesVrefTerminal(CyParameters parameters, int configNum)
        {
            List<int> chanCounts = ChannelCounts(parameters);

            // If config not active, it doesn't use Vref
            if (configNum >= chanCounts.Count)
            {
                return false;
            }

            // Config uses a Vref terminal iff the selected Vneg source is external.
            CyConfigModel configModel = parameters.GetConfig(configNum);
            return IsVrefSourceExternal(configModel.VrefSource);
        }

        /// <summary>
        /// Return true if the specified configuration's Vneg source is vssa_kelvin
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <returns>True if vneg source is vssa_kelvin, otherwise false</returns>
        public static bool ConfigUsesVnegVssaKelvin(CyParameters parameters, int configNum)
        {
            List<int> chanCounts = ChannelCounts(parameters);

            // If config not active, it doesn't use Vref
            if (configNum >= chanCounts.Count)
            {
                return false;
            }

            var config = parameters.GetConfig(configNum);
            return config.VnegSource == CyEVnegSource.VNEGSOURCE_VSSA_K;
        }

        /// <summary>
        /// Return true if the specified configuration uses a Design-wide Vref or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <returns>True iff configuration uses a Design-wide Vref</returns>
        public static bool ConfigUsesDWVref(CyParameters parameters, int configNum)
        {
            List<int> chanCounts = ChannelCounts(parameters);

            // If config not active, it doesn't use Vref
            if (configNum >= chanCounts.Count)
            {
                return false;
            }

            CyConfigModel configModel = parameters.GetConfig(configNum);
            return (configModel.VrefSource == CyEVrefSource.VREFSOURCE_PVREF);
        }

        /// <summary>
        /// Return true if channel mode is differential or false if not.
        /// </summary>
        /// <param name="mode">Channel mode description from symbol enum</param>
        /// <returns>True iff channel mode is differential</returns>
        public static bool IsChannelDifferential(CyEInputMode mode)
        {
            return mode == CyEInputMode.DIFFERENTIAL_CHAN;
        }

        /// <summary>
        /// Return true if channel mode is single-ended or false if not.
        /// </summary>
        /// <param name="mode">Channel mode description from symbol enum</param>
        /// <returns>True iff channel mode is single-ended</returns>
        public static bool IsChannelSingleEnded(CyEInputMode mode)
        {
            return mode == CyEInputMode.SINGLE_ENDED_CHAN;
        }

        /// <summary>
        /// Return true if channel mode is filter or false if not.
        /// </summary>
        /// <param name="mode">Channel mode description from symbol enum</param>
        /// <returns>True iff channel mode is filter</returns>
        public static bool IsChannelFilter(CyEInputMode mode)
        {
            return mode == CyEInputMode.FILTER_CHAN;
        }

        /// <summary>
        /// Return true if Vneg source is external of false if not.
        /// 
        /// An external Vneg source is connected through a symbol terminal.
        /// </summary>
        /// <param name="source">Vneg source description from symbol enum</param>
        /// <returns>True iff Vneg source is external</returns>
        public static bool IsVnegSourceExternal(CyEVnegSource source)
        {
            if (source == CyEVnegSource.VNEGSOURCE_EXTERNAL)
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// Return true if Vref source is external or false if not.
        /// 
        /// An external Vref source is connected through a symbol terminal.
        /// </summary>
        /// <param name="source">Vref source description from symbol enum</param>
        /// <returns>True iff Vref source is external</returns>
        public static bool IsVrefSourceExternal(CyEVrefSource source)
        {
            return source == CyEVrefSource.VREFSOURCE_EXTERNAL;
        }

        /// <summary>
        /// Return true if Vref source is a device pin or false if not.
        /// 
        /// An external Vref source is connected through a symbol terminal.
        /// </summary>
        /// <param name="source">Vref source description from symbol enum</param>
        /// <returns>True iff Vref source is external</returns>
        public static bool IsVrefSourceDevicePin(CyEVrefSource source)
        {
            return source == CyEVrefSource.VREFSOURCE_DEVPIN;
        }

        /// <summary>
        /// Return true if any active configuration uses a Vref bypass or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True iff any active configuration uses a Vref bypass</returns>
        public static bool AnyConfigHasVrefBypass(CyParameters parameters)
        {
            // If any active config uses a Vref bypass, return true.
            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                if (configModel.Sar.VrefBypass)
                {
                    return true;
                }
            }

            // Otherwise return false.
            return false;
        }

        /// <summary>
        /// Return true if any configuration uses an routed Vref or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True iff any active configuration uses a routed Vref</returns>
        public static bool AnyConfigHasRoutedVref(CyParameters parameters)
        {
            // If any active config uses a routed Vref, return true.
            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                if (ConfigUsesDWVref(parameters,configNum) || ConfigUsesVrefTerminal(parameters,configNum))
                {
                    return true;
                }
            }

            // Otherwise return false.
            return false;
        }

        /// <summary>
        /// Return true if any configuration uses a device pin Vref or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True iff any active configuration uses a device pin Vref</returns>
        public static bool AnyConfigHasDevicePinVref(CyParameters parameters)
        {
            // If any active config uses an external Vref, return true.
            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                if (IsVrefSourceDevicePin(configModel.VrefSource))
                {
                    return true;
                }
            }

            // Otherwise return false.
            return false;
        }

        /// <summary>
        /// Return true if any configuration uses a filter, or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True iff any active configuration uses a filter</returns>
        public static bool AnyConfigUsesFilter(CyParameters parameters)
        {
            var filterMasks = ChannelFilterMasks(parameters);

            for (var configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                if (filterMasks[configNum] != 0)
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Return true if the provided configuration has a single ended channel or false if not.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>True iff the configuration has a single ended channel</returns>
        public static bool ConfigHasSingleEndedChan(CyParameters parameters, int configNum)
        {
             List<int> chanCounts = ChannelCounts(parameters);

            // If config not active, it doesn't have a single-ended channel.
            if (configNum >= chanCounts.Count)
            {
                return false;
            }

            CyConfigModel configModel = parameters.GetConfig(configNum);
            
            // If any channel in the config is single-ended, return true.
            for (int i = 0; i < configModel.NumChannels; i++)
            {
                CyEInputMode mode = configModel.ChannelList[i].InputMode;
                if (IsChannelSingleEnded(mode))
                { 
                    return true;
                }
            }

            // Otherwise return false.
            return false;
        }

        /// <summary>
        /// Returns the number of spaces to put between config symbols.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>The number of spaces to put between config symbols</returns>
        public static long ConfigSpace(CyParameters parameters)
        {
            return parameters.Test_ConfigSpacing;
        }

        /// <summary>
        /// Returns whether to expose test terminals.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>Whether to expose test terminals.</returns>
        public static bool ExposeTestTerminals(CyParameters parameters)
        {
            return parameters.Test_ExposeTestTerminals;
        }

        /// <summary>
        /// Returns the code and input range labels for single-ended and differential channels.
        /// </summary>
        /// <param name="configModel">Scan_ADC config model</param>
        /// <returns>The code and input range labels for sigle-ended and differential channels
        /// in a dictionary</returns>
        public static Dictionary<string, string> ChannelRangeLabels(CyConfigModel configModel)
        {
            Dictionary<string, string> rangeLabels = new Dictionary<string, string>();

            // The differential voltage range is always the same
            rangeLabels.Add("diffVoltRange", "Vn-Vref to Vn+Vref");

            // The differential code range depends on the differential result format
            if (configModel.DiffResultFormat == CyENumberFormat.SIGNED_FORMAT)
            {
                rangeLabels.Add("diffCodeRange", "-2048 to 2047");
            }
            else //CyENumberFormat.UNSIGNED_FORMAT
            {
                rangeLabels.Add("diffCodeRange", "0 to 4095");
            }

            // The single-ended code range depends on the single-ended result format
            if (configModel.SingleEndedResultFormat == CyENumberFormat.SIGNED_FORMAT)
            {
                rangeLabels.Add("seCodeRange", "-2048 to 2047");
            }
            else //CyENumberFormat.UNSIGNED_FORMAT
            {
                rangeLabels.Add("seCodeRange", "0 to 4095");
            }

            // The single-ended voltage range depends on the Vneg selection
            if (configModel.VnegSource == CyEVnegSource.VNEGSOURCE_VSSA_K)
            {
                rangeLabels.Add("seVoltRange", "0 to Vref");
            }
            else if (configModel.VnegSource == CyEVnegSource.VNEGSOURCE_VREFSHORT)
            {
                rangeLabels.Add("seVoltRange", "0 to 2*Vref");
            }
            else // CyEVnegSource.VNEGSOURCE_EXTERNAL
            {
                rangeLabels.Add("seVoltRange", "Vneg-Vref to Vneg+Vref");
            }

            return rangeLabels;
        }

        /// <summary>
        /// Checks to see if external ADC clock is selected but not valid.
        /// 
        /// The external ADC clock could be invalid if its selection has not been
        /// applied to the design or if the design has not yet been elaborated, or
        /// if there is no external clock source connected.
        /// </summary>
        /// <param name="parameters">Scan_ADC parameters</param>
        /// <returns>True if external ADC clock is invalid, otherwise false.</returns>
        public static bool InvalidExternalAdcClock(CyParameters parameters)
        {
            return parameters.ExternalClk == true && parameters.ExternalAdcClockData == null;
        }

        /// <summary>
        /// Checks to see if internal ADC clock is selected but not valid.
        /// 
        /// The internal ADC clock could be invalid if its selection had not been
        /// applied to the design or if the design has not yet been elaborated.
        /// </summary>
        /// <param name="parameters">Scan ADC parameters</param>
        /// <returns>True if the internal ADC clock is selected, otherwise false.</returns>
        public static bool InvalidInternalAdcClock(CyParameters parameters)
        {
            return parameters.ExternalClk == false && parameters.InternalAdcClockData == null;
        }

        /// <summary>
        /// Check to see if external ADC clock is out of range for specified configuration.
        /// </summary>
        /// <param name="parameters">Scan ADC parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <returns></returns>
        public static bool AdcClockOutOfRange(CyParameters parameters, int configNum)
        {
            // Only check external clocks for 4B because hfclk cannot be lower than the minimum.
            if (parameters.ExternalClk == false && parameters.SarType == CyESarType.SAR_M0S8PASS4B)
            {                
                return false;
            }

            // Only check active configurations.
            if (configNum >= parameters.NumberOfConfigs)
            {
                return false;
            }

            // Check ADC clock against SAR clock frequency range.
            var config = parameters.GetConfig(configNum);
            if ((config.ActualAdcClockHz < config.Sar.MinSarFrequency)
                || (config.ActualAdcClockHz > config.Sar.MaxSarFrequency))
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// Generate string describing a clock rate range in MHz.
        /// </summary>
        /// <param name="lowFreq">Low clock frquency</param>
        /// <param name="highFreq">High clock frequency</param>
        /// <returns>string describing range</returns>
        public static string ClockRangeMHzText(int lowFreq, int highFreq)
        {
            var text = string.Format("{0:0.###} to {1:0.####} MHz",
                (double)lowFreq / HZ_PER_MHZ,
                (double)highFreq / HZ_PER_MHZ);

            return text;
        }

        /// <summary>
        /// Generate string describing a clock rate in MHz.
        /// </summary>
        /// <param name="freq">Clock rate</param>
        /// <returns>string describing clock range</returns>
        public static string ClockFreqMHzText(long freq)
        {
            var text = string.Format("{0:0.###} MHz", (double)freq / HZ_PER_MHZ);
            return text;
        }

        /// <summary>
        /// Checks to see if the selected ADC clock is invalid.
        /// </summary>
        /// <param name="parameters">Scan ADC parameters</param>
        /// <returns>True is the selected ADC clock is invalid, otherwisr false.</returns>
        public static bool InvalidAdcClock(CyParameters parameters)
        {
            if (InvalidExternalAdcClock(parameters))
            {
                return true;
            }
            else if (InvalidInternalAdcClock(parameters))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Find Vref value used by  specified configuration.
        /// </summary>
        /// <param name="parameters">Scan ADC parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <returns>Vref value for configuration</returns>
        public static double GetConfigVrefValue(CyParameters parameters, int configNum)
        {
            double vref = 0.0;

            var config = parameters.GetConfig(configNum);
            if (config.VrefSource == CyEVrefSource.VREFSOURCE_EXTERNAL
                || config.VrefSource == CyEVrefSource.VREFSOURCE_DEVPIN)
            {
                vref = config.VrefVoltage;
            }
            else
            {
                vref = CyVoltage.GetDesignVrefValue(parameters, config.VrefSource);
            }

            return vref;
        }
    }
}
