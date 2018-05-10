/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace Scan_ADC_v2_0
{
    /// <summary>
    /// Functions to add new parameters to API macro dictionary.
    /// </summary>
    public static class CyApiMacros
    {
        /// <summary>
        /// Add parameters to API macro dictionary.
        /// </summary>
        /// <param name="paramDict">API macro dictionary</param>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        public static void ExtendDictionary(Dictionary<string, string> paramDict,
            CyParameters parameters)
        {
            paramDict["AdcTotalChannels"] = CyModelUtils.TotalChannelCount(parameters).ToString();
            paramDict["AdcTotalConfigs"] = parameters.NumberOfConfigs.ToString();
            paramDict["channelsConfig"] = BuildChannelConfigString(paramDict, parameters);
            paramDict["AdcRoutedVref"] = Convert.ToByte(CyModelUtils.AnyConfigHasRoutedVref(parameters)).ToString();
            AddChannelConfigArrayStrings(paramDict, parameters);
            AddAPIChannelIndexes(paramDict, parameters);
            AddAPIChannelTotals(paramDict, parameters);
            AddAPIVrefSelMasks(paramDict, parameters);
            AddAPINomClocks(paramDict, parameters);
            AddAPIChanEn(paramDict, parameters);
            AddAPISatRangeMasks(paramDict, parameters);
            AddAPIVnegSel(paramDict, parameters);
            AddAPISinglePresent(paramDict, parameters);
            AddAPIHasFilterParams(paramDict, parameters);
            AddAPIUseSoc(paramDict, parameters);
            AddAPIFilterCapParams(paramDict, parameters);
            AddAPIFilterTopologyParams(paramDict, parameters);
            AddAPIFilterBiquadParams(paramDict, parameters);
            AddAPISampleCtrlParams(paramDict, parameters);
            AddAPIApetureTimers(paramDict, parameters);
            AddAPIFreeRunning(paramDict, parameters);
            AddAPIRangeParams(paramDict, parameters);
            AddAPISampleRate(paramDict, parameters);
            AddAPIPwrCtrlVref(paramDict, parameters);
            AddAPICompPower(paramDict, parameters);
            AddAPICompDelay(paramDict, parameters);

            AddAPIFilterDivider(paramDict, parameters);
            AddAPIFilterDelay(paramDict, parameters);

            AddAPIEnumDefinition<CyEInputMode>(paramDict);
            AddAPIEnumDefinition<CyELimitComparisonMode>(paramDict);
            AddAPIEnumDefinition<CyEAveragingMode>(paramDict);
            AddAPIEnumDefinition<CyESamplesAveraged>(paramDict);
            AddAPIEnumDefinition<CyENumberFormat>(paramDict);
            AddAPIEnumDefinition<CyEVnegSource>(paramDict);
            AddAPIEnumDefinition<CyEVrefSource>(paramDict);
            AddAPIEnumDefinition<CyEFilterType>(paramDict);
            AddAPIEnumDefinition<CyEAlternateResolution>(paramDict);

            paramDict["ConfigDescriptionDefines"] = ConfigDescParamsDefines(paramDict, parameters);
        }

        /// <summary>
        /// Checks if a given capacitor value is fractional. 
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static bool IsFractional(double capVal)
        {
            int truncateCap = (Int32)capVal;
            if (truncateCap != capVal)
            {
                return true;
            }
            return false;
        }
        /// <summary>
        /// Adds a parameter for all possible configurations to if the soc pin is used
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIUseSoc(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < CyParamRanges.NUM_CONFIG_MAX; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                if(configModel.UseSoc)
                {
                    AddAPICfgDecimalParam(paramDict, i, "UseSoc", 1);
                }
                else
                {
                    AddAPICfgDecimalParam(paramDict, i, "UseSoc", 0);
                }
            }
        }

        /// <summary>
        /// Adds a parameter for all possible configurations to indicate whether or not
        /// the given configuration uses a UAB Filter.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIHasFilterParams(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int configNum = 0; configNum < CyParamRanges.NUM_CONFIG_MAX; configNum++)
            {
                CyConfigModel config = parameters.GetConfig(configNum);
                if (configNum < parameters.NumberOfConfigs
                    && config.ChannelList[0].InputMode.Equals(CyEInputMode.FILTER_CHAN))
                {
                    AddAPICfgDecimalParam(paramDict, configNum, "HasFilter", 1);
                }
                else
                {
                    AddAPICfgDecimalParam(paramDict, configNum, "HasFilter", 0);
                }
            }
        }

        /// <summary>
        /// Add the Scan Rate for each configuration. This is for documentation in the API
        /// firmware. It is not used in the firmware.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPISampleRate(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                string paramName = "Cfg" + i.ToString() + "SampleRate";
                paramDict[paramName] = configModel.SampleRate.ToString();
            }
        }

        /// <summary>
        /// Add the Filter's clock divider each configuration. This is used in the firmware.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIFilterDivider(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                string paramName = "Cfg" + i.ToString() + "FilterClockDivider";
                paramDict[paramName] = configModel.FilterUabClockDivider.ToString();
            }
        }

        /// <summary>
        /// Add the Filter's delay for each configuration. This is used in the firmware.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIFilterDelay(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                string paramName = "Cfg" + i.ToString() + "FilterStartDelay";
                paramDict[paramName] = configModel.FilterUabStartDelay.ToString();
            }
        }

        /// <summary>
        /// Add the UAB Filter Capacitor parameters for each configuration. Format is:
        /// "Cfg" + {config number } + {UABPRIM Bitfield Name} + {UAB Half designation}
        /// UAB half designation is either 'A' for primary or 'B' for secondary.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIFilterCapParams(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                if(configModel.ChannelList[0].InputMode.Equals(CyEInputMode.FILTER_CHAN))
                {
                    //Set all of the capacitor parameters
                    if(IsFractional(configModel.UabCaps.C1))    //C1 caps are part of the secondary  or 'B' UAB half.
                    {
                        AddAPICfgDecimalParam(paramDict, i, "HalfBCcVal", (int) Math.Round(configModel.UabCaps.C1 * 64));
                        AddAPICfgHexParam(paramDict, i, "HalfBSwTc", 0x2);
                        AddAPICfgHexParam(paramDict, i, "HalfBCcGnd", 1);
                    }
                    else 
                    {
                        AddAPICfgDecimalParam(paramDict, i, "HalfBCcVal", (int)configModel.UabCaps.C1);
                        AddAPICfgHexParam(paramDict, i, "HalfBSwTc", 0xF);
                        AddAPICfgHexParam(paramDict, i, "HalfBCcGnd", 0);
                    }

                    if (IsFractional(configModel.UabCaps.C2))   //C2 caps are part of the secondary or 'B' UAB half.
                    {
                        AddAPICfgDecimalParam(paramDict, i, "HalfACbVal", (int)Math.Round(configModel.UabCaps.C2 * 64));
                        AddAPICfgHexParam(paramDict, i, "HalfASwTb", 0x2);
                        AddAPICfgHexParam(paramDict, i, "HalfACbGnd", 1);
                    }
                    else
                    {
                        AddAPICfgDecimalParam(paramDict, i, "HalfACbVal", (int)configModel.UabCaps.C2);
                        AddAPICfgHexParam(paramDict, i, "HalfASwTb", 0xF);
                        AddAPICfgHexParam(paramDict, i, "HalfACbGnd", 0);
                    }

                    if (IsFractional(configModel.UabCaps.CPP))   //CPP caps are part of the primary or 'A' UAB half.
                    {
                        AddAPICfgDecimalParam(paramDict, i, "HalfBCbVal", (int)Math.Round(configModel.UabCaps.CPP * 64));
                        AddAPICfgHexParam(paramDict, i, "HalfBSwTb", 0x0);
                        AddAPICfgHexParam(paramDict, i, "HalfBCbGnd", 1);
                    }
                    else
                    {
                        AddAPICfgDecimalParam(paramDict, i, "HalfBCbVal", (int)configModel.UabCaps.CPP);
                        AddAPICfgHexParam(paramDict, i, "HalfBSwTb", 0xF);
                        AddAPICfgHexParam(paramDict, i, "HalfBCbGnd", 0);
                    }
                    //Always integral (never fractional) caps
                    AddAPICfgDecimalParam(paramDict, i, "HalfACaVal", (int)configModel.UabCaps.C4);
                    AddAPICfgDecimalParam(paramDict, i, "HalfACcVal", (int)configModel.UabCaps.CP);
                    AddAPICfgDecimalParam(paramDict, i, "HalfACfVal", (int)configModel.UabCaps.CA);
                    AddAPICfgDecimalParam(paramDict, i, "HalfBCfVal", (int)configModel.UabCaps.CB);
                    AddAPICfgDecimalParam(paramDict, i, "HalfBCaVal", (int)configModel.UabCaps.C3);
                }              
            }
        }

        /// <summary>
        /// Adds filter topology and GT capacitor parameters to the API parameter dictionary.
        /// </summary>
        /// <param name="paramDict">API parameter replacement dictionary</param>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        private static void AddAPIFilterTopologyParams(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                var idealBiquad = CyFilterUtils.GetIdealFilterBiquad(configModel);
                string topologyName = configModel.FilterTopology(idealBiquad).ToString();
                string transferType = configModel.FilterType.ToString();
                AddAPICfgStringParam(paramDict, i, "FilterTopology", topologyName);
                AddAPICfgStringParam(paramDict, i, "TransferType", transferType);
                AddAPICfgUabCapParam(paramDict, i, "GtC1", configModel.UabCaps.C1);
                AddAPICfgUabCapParam(paramDict, i, "GtC2", configModel.UabCaps.C2);
                AddAPICfgUabCapParam(paramDict, i, "GtC3", configModel.UabCaps.C3);
                AddAPICfgUabCapParam(paramDict, i, "GtC4", configModel.UabCaps.C4);
                AddAPICfgUabCapParam(paramDict, i, "GtCA", configModel.UabCaps.CA);
                AddAPICfgUabCapParam(paramDict, i, "GtCB", configModel.UabCaps.CB);
                AddAPICfgUabCapParam(paramDict, i, "GtCp", configModel.UabCaps.CP);
                AddAPICfgUabCapParam(paramDict, i, "GtCpp", configModel.UabCaps.CPP);
                AddAPICfgUabCapParam(paramDict, i, "GtCppp", configModel.UabCaps.CPPP);
            }
        }

        private static void AddAPIFilterBiquadParams(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel config = parameters.GetConfig(i);
                var idealBiquad = CyFilterUtils.GetIdealFilterBiquad(config);
                var uabBiquad = new Biquad();
                try
                {
                    var uabCaps = config.GetUabFilterCaps(idealBiquad);
                    uabBiquad = config.GetUabFilterBiquad(uabCaps, idealBiquad);
                }
                catch (CapacitorMapperException)
                {
                    // Ignore capacitor mapping exceptions here.
                }
                AddAPICfgBiquadParam(paramDict, i, "IdealBiquad", idealBiquad);
                AddAPICfgBiquadParam(paramDict, i, "UabBiquad", uabBiquad);
            }
        }


        private static void AddAPICfgBiquadParam(
            Dictionary<string, string> paramDict, int configNum, string label, Biquad value)
        {
            AddAPICfgDoubleParam(paramDict, configNum, label + "Num0", value.Num0);
            AddAPICfgDoubleParam(paramDict, configNum, label + "Num1", value.Num1);
            AddAPICfgDoubleParam(paramDict, configNum, label + "Num2", value.Num2);
            AddAPICfgDoubleParam(paramDict, configNum, label + "Den0", value.Den0);
            AddAPICfgDoubleParam(paramDict, configNum, label + "Den1", value.Den1);
            AddAPICfgDoubleParam(paramDict, configNum, label + "Den2", value.Den2);
        }


        /// <summary>
        /// Adds a configuration specific parameter of size double in decimal format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>void</returns>
        private static void AddAPICfgDoubleParam(
            Dictionary<string, string> paramDict, int configNum, string baseName, double value)
        {
            string paramName = "Cfg" + configNum.ToString() + baseName;
            AddAPIDoubleParam(paramDict, paramName, value);
        }


        private static void AddAPIDoubleParam(Dictionary<string, string> paramDict, string paramName, double value)
        {
            paramDict[paramName] = value.ToString();
        }

        /// <summary>
        /// Adds a configuration specific parameter in decimal format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>void</returns>
        private static void AddAPICfgDecimalParam(Dictionary<string, string> paramDict, int configNum, string baseName, int value)
        {
            string paramName = "Cfg" + configNum.ToString() + baseName;
            AddAPIDecimalParam(paramDict, paramName, value);
        }

        /// <summary>
        /// Adds a configuration specific parameter in decimal format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIDecimalParam(Dictionary<string, string> paramDict, string paramName, int value)
        {
            paramDict[paramName] = value.ToString();
        }

        /// <summary>
        /// Adds a configuration specific parameter in hex format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPICfgHexParam(Dictionary<string, string> paramDict, int configNum, string baseName, int value)
        {
            string paramName = "Cfg" + configNum.ToString() + baseName;
            AddAPIHexParam(paramDict, paramName, value);
        }

        /// <summary>
        /// Adds a parameter to the API dictionary in hex format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIHexParam(Dictionary<string, string> paramDict, string paramName, int value)
        {
            paramDict[paramName] = String.Format("0x{0:x}", value);
        }

        /// <summary>
        /// Adds a parameter to the API dictionary in string format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIStringParam(Dictionary<string, string> paramDict, string paramName, string value)
        {
            paramDict[paramName] = value;
        }

        /// <summary>
        /// Adds a configuration specific parameter in UAB capacitance format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPICfgUabCapParam(Dictionary<string, string> paramDict, int configNum, string baseName, double cap)
        {
            string paramName = "Cfg" + configNum.ToString() + baseName;

            // Fractional UAB cap values are less than 1 and at least 1/64.
            int capDenominator = (cap >= 1 || Math.Round(cap, 3) == 0) ? 1 : 64;

            cap *= capDenominator;
            int capNumerator = (int)Math.Round(cap, 0);

            AddAPIDecimalParam(paramDict, paramName + "Numerator", capNumerator);
            AddAPIDecimalParam(paramDict, paramName + "Denominator", capDenominator);
        }

        /// <summary>
        /// Adds a configuration specific parameter in string format
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPICfgStringParam(Dictionary<string, string> paramDict, int configNum, string baseName, string value)
        {
            string paramName = "Cfg" + configNum.ToString() + baseName;
            AddAPIStringParam(paramDict, paramName, value);
        }

        /// <summary>
        /// Add the Freerunning or Single shot parameters for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIFreeRunning(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "AdcFreeRunning", (configModel.FreeRunning ? 1: 0));
            }
        }

        /// <summary>
        /// Add the Apterture Timer parameters for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIApetureTimers(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            List<int> configApertures = new List<int>();
            
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                configApertures = configModel.ApertureTimers;
                for(int j = 0; j < configApertures.Count; j++)
                {
                    AddAPICfgDecimalParam(paramDict, i, "AdcApertureTime" + j.ToString(), configApertures[j]);
                }
            }
        }
        /// <summary>
        /// Add the High/Low Range threshold and condition parameters for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIRangeParams(Dictionary<string, string> paramDict, CyParameters parameters)
        {

            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "AdcRangeLowLimit", (int)configModel.LowLimit);
                AddAPICfgDecimalParam(paramDict, i, "AdcRangeHighLimit", (int)configModel.HighLimit);
                AddAPICfgDecimalParam(paramDict, i, "AdcRangeCondition", (int)configModel.CompareMode);
            }
        }

        /// <summary>
        /// Add the VNEG_SEL parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIVnegSel(Dictionary<string, string> paramDict, CyParameters parameters)
        {
 
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "AdcCtrlVnegSel", (int) configModel.VnegSource);
                AddAPICfgDecimalParam(paramDict, i, "AdcVrefVoltageMv", (int)Math.Round(configModel.VrefVoltage * 1000));
            }
        }

        /// <summary>
        /// Add the saturation and range interrupt masks for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPISatRangeMasks(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            List<uint> satMasks = new List<uint>();
            List<uint> rangeMasks = new List<uint>();
            satMasks = CyModelUtils.ChannelSatInterruptMasks(parameters);
            rangeMasks = CyModelUtils.ChannelLimitInterruptMasks(parameters);

            for (int i = 0; i < satMasks.Count; i++)
            {
                AddAPICfgHexParam(paramDict, i, "AdcSaturateMask", (int) satMasks[i]);
                AddAPICfgHexParam(paramDict, i, "AdcRangeMask", (int)satMasks[i]);
            }
        }

        /// <summary>
        /// Add the channel enable parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIChanEn(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            List<uint> channelIdx = new List<uint>();
            channelIdx = CyModelUtils.ChannelEnableMasks(parameters);

            for (int i = 0; i < channelIdx.Count; i++)
            {
                AddAPICfgHexParam(paramDict, i, "AdcChannelEnable", (int) channelIdx[i]);
            }
        }
        /// <summary>
        /// Add the parameter to indicate if each configuration has a single ended channel.
        /// Used to determine if NEG_SEL is routed by Creator.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPISinglePresent(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                if (CyModelUtils.ConfigHasSingleEndedChan(parameters, i))
                {
                    AddAPICfgDecimalParam(paramDict, i, "AdcSingleEndedPresent", 1);
                }
                else
                {
                    AddAPICfgDecimalParam(paramDict, i, "AdcSingleEndedPresent", 0);
                }

            }
        }

        /// <summary>
        /// Add the result justification parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPISampleCtrlParams(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "AdcAltResolution", (int) configModel.AlternateResolution);
                AddAPICfgDecimalParam(paramDict, i, "AdcSingleEndedFormat", (int)configModel.SingleEndedResultFormat);
                AddAPICfgDecimalParam(paramDict, i, "AdcDifferentialFormat", (int)configModel.DiffResultFormat);
                AddAPICfgDecimalParam(paramDict, i, "AdcSamplesAveraged", (int)configModel.SamplesAveraged);
                AddAPICfgDecimalParam(paramDict, i, "AdcAveragingMode", (int)configModel.AveragingMode);  
            }
        }

        /// <summary>
        /// Add the Vref buffer power setting parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIPwrCtrlVref(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "PwrCtrlVref", configModel.Sar.GetPwrCtrlVref(configModel.ActualAdcClockHz));
            }
        }

        /// <summary>
        /// Add the comparator power setting parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPICompPower(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "CompPower", configModel.Sar.GetCompPower(configModel.ActualAdcClockHz));
            }
        }

        /// <summary>
        /// Add the comparator delay parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPICompDelay(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "CompDelay", configModel.Sar.GetCompDelay(configModel.ActualAdcClockHz));
            }
        }

        /// <summary>
        /// Add the nominal SAR clock parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPINomClocks(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            for (int i = 0; i < parameters.NumberOfConfigs; i++)
            {
                CyConfigModel configModel = parameters.GetConfig(i);
                AddAPICfgDecimalParam(paramDict, i, "NominalClockFreq", (int)(configModel.ActualAdcClockHz));
            }
        }


        /// <summary>
        /// Add the VREF_SEL and VREF_BYP_CAP_EN parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIVrefSelMasks(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            List<uint> channelIdx = new List<uint>();
            channelIdx = CyModelUtils.ConfigCtrlVrefSelMasks(parameters);

            for (int i = 0; i < channelIdx.Count; i++)
            {
                AddAPICfgHexParam(paramDict, i, "AdcVrefSelMask", (int)channelIdx[i]);
            }

        }
        /// <summary>
        /// Add the channel index parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIChannelIndexes(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            List<int> channelIdx = new List<int>();
            channelIdx = CyModelUtils.ChannelIndexes(parameters);
            
            for(int i = 0; i < channelIdx.Count; i++)
            {
                AddAPICfgDecimalParam(paramDict, i, "AdcChannelIndex", channelIdx[i]);
            }

        }

        /// <summary>
        /// Add the channel total parameter for each configuration
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters and param dictionary</param>
        /// <returns>API macro dictionary</returns>
        private static void AddAPIChannelTotals(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            List<int> channelIdx = new List<int>();
            channelIdx = CyModelUtils.ChannelCounts(parameters);

            for (int i = 0; i < channelIdx.Count; i++)
            {
                AddAPICfgDecimalParam(paramDict, i, "AdcChannelCount", channelIdx[i]);
            }

        }

        /// <summary>
        /// Return a string for a channel configuration.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>String representing an array of channel configuration</returns>
        private static void AddChannelConfigArrayStrings(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            var instanceName = paramDict["INSTANCE_NAME"];
            List<uint> masks = CyModelUtils.AllChannelMasks(parameters);
            List<int> chanCounts = CyModelUtils.ChannelCounts(parameters);
            StringBuilder inputPlacementStr = new StringBuilder();
            int absoluteChanNum = 0;
            int lastChannel = CySarRanges.NUM_CHANNEL_MAX - 1;

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                CyConfigModel configModel = parameters.GetConfig(configNum);
                inputPlacementStr.Clear();
                inputPlacementStr.Append("{");

                // For single channel, single config designs the SARMUX isn't used
                if ((parameters.NumberOfConfigs == 1) && (chanCounts[0] == 1))
                {
                    inputPlacementStr.AppendFormat("((uint32_t) ({0}", configModel.ChannelList[0].ApertureTimer);
                    inputPlacementStr.Append(" << SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos)");

                    if (CyModelUtils.IsRawChannelDifferential(parameters, absoluteChanNum))
                    {
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.Append("        | SAR_CHAN_CONFIG_DIFFERENTIAL_EN_Msk");
                    }

                    if (configModel.ChannelList[0].UseAveraging)
                    {
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.Append("        | SAR_CHAN_CONFIG_AVG_EN_Msk");
                    }

                    inputPlacementStr.Append("),");
                    inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                }
                else
                {
                    //Channel pin placement
                    for (int i = 0; i < chanCounts[configNum]; i++)
                    {
                        /* Don't indent the first channel */
                        if(i == 0)
                        {
                            inputPlacementStr.AppendFormat("(uint32_t) ({0}_SARMUX__CH_{1}_PORT << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos) |", instanceName, absoluteChanNum);
                        }
                        else
                        {
                            inputPlacementStr.AppendFormat("        (uint32_t) ({0}_SARMUX__CH_{1}_PORT << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos) |", instanceName, absoluteChanNum);
                        }
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.AppendFormat("        (uint32_t) {0}_SARMUX__CH_{1}_PIN", instanceName, absoluteChanNum);
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.Append("        #ifdef ");
                        inputPlacementStr.AppendFormat("{0}_SARMUX__CH_{1}_MINUS_PIN", instanceName, absoluteChanNum);
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.Append("            | (uint32_t) (");
                        inputPlacementStr.AppendFormat("{0}_SARMUX__CH_{1}_MINUS_PIN << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos", instanceName, absoluteChanNum);
                        inputPlacementStr.Append(") ");
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.Append("            | (uint32_t) (");
                        inputPlacementStr.AppendFormat("{0}_SARMUX__CH_{1}_MINUS_PORT ", instanceName, absoluteChanNum);
                        inputPlacementStr.Append(" << SAR_CHAN_CONFIG_NEG_PORT_ADDR_Pos)");
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.Append("            | SAR_CHAN_CONFIG_NEG_ADDR_EN_Msk");
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        inputPlacementStr.Append("        #else");
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);

                        // If differential but not using MINUS PIN, set the differential bit
                        if (CyModelUtils.IsRawChannelDifferential(parameters, absoluteChanNum))
                        {
                            inputPlacementStr.Append("            | SAR_CHAN_CONFIG_DIFFERENTIAL_EN_Msk");
                            inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        }
                        inputPlacementStr.Append("        #endif");
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);

                        if (configModel.ChannelList[i].UseAveraging)
                        {
                            inputPlacementStr.Append("        | SAR_CHAN_CONFIG_AVG_EN_Msk");
                            inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                        }

                        inputPlacementStr.Append("        | (uint32_t) (");
                        inputPlacementStr.AppendFormat("{0}", configModel.ChannelList[i].ApertureTimer);

                        //Close curly brace for the end of the array
                        if (i == lastChannel)
                        {
                            inputPlacementStr.Append(" << SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos)},"); 
                        }
                        else
                        {
                            inputPlacementStr.Append(" << SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos),");
                        }
                        inputPlacementStr.AppendFormat("{0}", Environment.NewLine);

                        absoluteChanNum++;
                    }
                }
                //Fill remaining array with zeros
                for (int emptyChan = chanCounts[configNum]; emptyChan < CySarRanges.NUM_CHANNEL_MAX; emptyChan++)
                {
                    //Close curly brace for the end of the array
                    if (emptyChan == lastChannel)
                    {
                        inputPlacementStr.Append("        CY_SAR_DEINIT},");
                    }
                    else
                    {
                        inputPlacementStr.Append("        CY_SAR_DEINIT,");
                    }
                    inputPlacementStr.AppendFormat("{0}", Environment.NewLine);
                }

                string paramName = "channelConfig" + configNum.ToString();
                paramDict[paramName] = inputPlacementStr.ToString();
            }
        }

        /// <summary>
        /// Return a string for the channel configurations.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>String representing the array of channel configurations</returns>
        private static string BuildChannelConfigString(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            var instanceName = paramDict["INSTANCE_NAME"];
            List<uint> masks = CyModelUtils.AllChannelMasks(parameters);
            StringBuilder channelsConfigStr = new StringBuilder();
            string cycode = (parameters.SarType == CyESarType.SAR_M0S8PASS4B) ? "CYCODE " : "";

            channelsConfigStr.AppendFormat("static const uint32 {0}", cycode);
            channelsConfigStr.AppendFormat("{0}", instanceName);
            channelsConfigStr.Append("_channelsConfig[] = { ");
            for(int chanCount = 0; chanCount < masks.Count; chanCount++)
            {
                channelsConfigStr.AppendFormat("0x{0:x8}", masks[chanCount]);
                channelsConfigStr.Append("UL, ");
                /*TODO: Format these so it's not one long string*/
            }
            channelsConfigStr.Append(" };");
            return channelsConfigStr.ToString();
        }

        /// <summary>
        /// Add C enum definition for API macro dictionary,
        /// </summary>
        /// <typeparam name="T">C# enum type</typeparam>
        /// <param name="paramDict">API macro dictionary</param>
        private static void AddAPIEnumDefinition<T>(Dictionary<string, string> paramDict)
            where T : IConvertible
        {
            var instanceName = paramDict["INSTANCE_NAME"];
            string enumParamName;
            string enumCodeSnippet;

            MakeEnumCodeSnippet<T>(instanceName, out enumParamName, out enumCodeSnippet);
            paramDict[enumParamName] = enumCodeSnippet;
        }

        /// <summary>
        /// Generate C enum definition from C# enum.
        /// </summary>
        /// <typeparam name="T">C# enum type</typeparam>
        /// <param name="instanceName">Symbol instance name</param>
        /// <param name="enumParamName">Receives macro name for code snippet</param>
        /// <param name="codeSnippet">Receives code snippet</param>
        private static void MakeEnumCodeSnippet<T>(
            string instanceName, out string enumParamName, out string codeSnippet)
            where T : IConvertible
        {
            // Get root C enum name from C# enum type.
            var enumName = CyEnumUtils.GetEnumCName<T>();

            // Build macro name.
            enumParamName = enumName.ToUpper() + "_DEF";

            // Build C enum type name.
            var enumCName = instanceName + "_" + enumName;

            // Get C# enum value names and descriptions.
            var valNames = CyEnumUtils.GetEnumValueNames<T>();
            var valDescs = CyEnumUtils.GetEnumValueDescriptions<T>();

            // Generate code snippet.
            var builder = new StringBuilder();
            var formatter = new NumberFormatInfo();
            builder.AppendFormat("typedef enum");
            builder.AppendLine();
            builder.AppendLine("{");
            var keys = new List<T>(valNames.Keys);
            keys.Sort();
            for (int keyIdx = 0; keyIdx < keys.Count; keyIdx++)
            {
                var key = keys[keyIdx];
                builder.Append("    ");
                builder.Append(valNames[key]);
                builder.Append(" = ");
                builder.Append(key.ToInt32(formatter));
                if (keyIdx != keys.Count - 1)
                {
                    builder.Append(",");
                }
                builder.Append(" /**< ");
                builder.Append(valDescs[key]);
                builder.Append(" */");
                builder.AppendLine();
            }
            builder.Append("} ");
            builder.AppendFormat("{0};", enumCName);
            builder.AppendLine();
            codeSnippet = builder.ToString();
        }

        private static string ConfigDescParamsDefines(
            Dictionary<string, string> paramDict, CyParameters parameters)
        {
            var builder = new StringBuilder();
            var instanceName = paramDict["INSTANCE_NAME"];

            for (int configNum = 0; configNum < parameters.NumberOfConfigs; configNum++)
            {
                var config = parameters.GetConfig(configNum);
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "TARGET_SPS", config.SampleRate.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "ACHIEVED_SPS", config.ActualSampleRate.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "ADC_CLOCK_FREQ_HZ", config.ActualAdcClockHz.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "VREF_SOURCE", config.Sar.VrefSource.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "VREF_BYPASS", config.Sar.VrefBypass.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "VNEG_SOURCE", config.VnegSource.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "NUM_SAMPLES_AVERAGED", config.SamplesAveraged.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "AVERAGING_MODE", config.AveragingMode.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "ALT_RES", config.AlternateResolution.ToString()));

                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "FILTER_TYPE", config.FilterType.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "FILTER_F1_KHZ", config.FilterDown3OrCenter.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "FILTER_F2_KHZ", config.FilterWidthOrNotch.ToString()));
                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "FILTER_SAMPLE_FREQ_KHZ", config.FilterSample.ToString()));

                builder.Append(ConfigParamDefString(configNum,
                    instanceName, "NUM_CHANNELS", config.NumChannels.ToString()));
                for (int chanNum = 0; chanNum < config.ChannelList.Count; chanNum++)
                {
                    var chan = config.ChannelList[chanNum];
                    builder.Append(ConfigChanParamDefString(configNum, chanNum,
                        instanceName, "ENABLED", chan.Enabled.ToString()));
                    builder.Append(ConfigChanParamDefString(configNum, chanNum,
                        instanceName, "USE_ALT_RES", chan.UseAltResolution.ToString()));
                    builder.Append(ConfigChanParamDefString(configNum, chanNum,
                        instanceName, "INPUT_MODE", chan.InputMode.ToString()));
                    builder.Append(ConfigChanParamDefString(configNum, chanNum,
                        instanceName, "USE_AVERAGING", chan.UseAveraging.ToString()));
                    builder.Append(ConfigChanParamDefString(configNum, chanNum,
                        instanceName, "MIN_ACQ_TIME_NS", chan.MinimumAcqTime.ToString()));
                    builder.Append(ConfigChanParamDefString(configNum, chanNum,
                        instanceName, "ACHIEVED_ACQ_TIME_NS", chan.ActualAcqTime.ToString()));
                }

                builder.Append("\r\n");
            }

            return builder.ToString();
        }

        private static string ConfigParamDefString(int configNum, string instanceName, string name, string value)
        {
            var builder = new StringBuilder();

            builder.Append("#define ");
            builder.Append(instanceName);
            builder.Append("_");
            builder.Append("CFG");
            builder.Append(configNum.ToString());
            builder.Append("_");
            builder.Append(name);
            builder.Append(" ");
            builder.Append(value);
            builder.Append("\r\n");

            return builder.ToString();
        }

        private static string ConfigChanParamDefString(
            int configNum, int chanNum, string instanceName, string name, string value)
        {
            var builder = new StringBuilder();

            builder.Append("#define ");
            builder.Append(instanceName);
            builder.Append("_");
            builder.Append("CFG");
            builder.Append(configNum.ToString());
            builder.Append("_");
            builder.Append("CHAN");
            builder.Append(chanNum.ToString());
            builder.Append("_");
            builder.Append(name);
            builder.Append(" ");
            builder.Append(value);
            builder.Append("\r\n");

            return builder.ToString();
        }
    }
}
