/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v2_0
{
    /// <summary>
    /// Core functions for customizer parameter expression evaluation functions.
    /// </summary>
    public static class CyExprEval
    {
        /// <summary>
        /// Caclulate the last stage filter input mux select values.
        /// 
        /// There is one of these muxes per configuration.  They select
        /// between a no-connect and 0, 1, 2, or 3 first stage muxes
        /// depending on the configuration number.  These muxes are on
        /// the Scan_ADC "filterVin[3:0]" schematic page.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="configNum">configuration number</param>
        /// <returns>filterConfigMux input select value</returns>
        public static int FilterConfigMuxSelect(CyParameters parameters, int configNum)
        {
            Debug.Assert((0 <= configNum) && (configNum < CyParamRanges.NUM_CONFIG_MAX),
                string.Format("Config mux number {0} out of range", configNum));

            if (parameters == null)
            {
                return 0;
            }

            uint filterMask = CyModelUtils.ConfigFilterMasks(parameters);
            bool useFilter = ((filterMask & (1u << configNum)) != 0) ? true : false;
            int rawConfigChannel0 = CyModelUtils.ConfigChannelToRawChannel(
                parameters, configNum, 0);

            if (configNum == 0)
            {
                return (useFilter == false) ? 1 : 0;
            }
            else if (configNum == 1)
            {
                return (useFilter == false) ? 1 : 0;
            }
            else if (configNum == 2)
            {
                if (useFilter == false)
                {
                    return 2;
                }
                else if (rawConfigChannel0 >= CyFilterVinMuxLimits.MUX_2_1_BASE)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (configNum == 3)
            {
                if (useFilter == false)
                {
                    return 3;
                }
                else if (rawConfigChannel0 >= CyFilterVinMuxLimits.MUX_3_2_BASE)
                {
                    return 2;
                }
                else if (rawConfigChannel0 >= CyFilterVinMuxLimits.MUX_3_1_BASE)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

            return 0;
        }

        /// <summary>
        /// Calculate the first stage filter input mux select values.
        /// 
        /// These muxes are used to select each configuration's channel 0
        /// vinPlus signal.  Configuration 0's channel 0 is always at
        /// raw channel 0, but other configuration's channel 0s position
        /// will depend on the number of channels in the lower configurations.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="configNum">Configuration number</param>
        /// <param name="muxNum">Configuration mux number</param>
        /// <returns>filterVinMux input select value.</returns>
        public static int FilterVinMuxSelect(CyParameters parameters,
            int configNum, int muxNum)
        {
            Debug.Assert(1 <= configNum
                && (configNum < CyParamRanges.NUM_CONFIG_MAX),
                string.Format("Configuration number {0} out of range", configNum));

            if (parameters == null)
            {
                return 0;
            }

            // Get the raw channel number for the specified configuration's
            // channel 0.
            int rawChan0 = CyModelUtils.ConfigChannelToRawChannel(
                parameters, configNum, 0);

            // The default mux input selection is 0.
            int select = 0;

            // If the configuration's raw channel 0 is in the
            // specified first stage filter Vin mux's input range
            // convert the raw channel number into a mux select value.
            // If not, leave the selection at 0.
            if (configNum == 1 && muxNum == 0)
            {
                if ((CyFilterVinMuxLimits.MUX_1_0_BASE <= rawChan0)
                    && (rawChan0 < CyFilterVinMuxLimits.MUX_1_MAX))
                {
                    select = rawChan0 - CyFilterVinMuxLimits.MUX_1_0_BASE;
                }
            }
            else if (configNum == 2 && muxNum == 0)
            {
                if ((CyFilterVinMuxLimits.MUX_2_0_BASE <= rawChan0)
                    && (rawChan0 < CyFilterVinMuxLimits.MUX_2_1_BASE))
                {
                    select = rawChan0 - CyFilterVinMuxLimits.MUX_2_0_BASE;
                }
            }
            else if (configNum == 2 && muxNum == 1)
            {
                if ((CyFilterVinMuxLimits.MUX_2_1_BASE <= rawChan0)
                    && (rawChan0 < CyFilterVinMuxLimits.MUX_2_MAX))
                {
                    select = rawChan0 - CyFilterVinMuxLimits.MUX_2_1_BASE;
                }
            }
            else if (configNum == 3 && muxNum == 0)
            {
                if ((CyFilterVinMuxLimits.MUX_3_0_BASE <= rawChan0)
                    && (rawChan0 < CyFilterVinMuxLimits.MUX_3_1_BASE))
                {
                    select = rawChan0 - CyFilterVinMuxLimits.MUX_3_0_BASE;
                }
            }
            else if (configNum == 3 && muxNum == 1)
            {
                if ((CyFilterVinMuxLimits.MUX_3_1_BASE <= rawChan0)
                    && (rawChan0 < CyFilterVinMuxLimits.MUX_3_2_BASE))
                {
                    select = rawChan0 - CyFilterVinMuxLimits.MUX_3_1_BASE;
                }
            }
            else if (configNum == 3 && muxNum == 2)
            {
                if ((CyFilterVinMuxLimits.MUX_3_2_BASE <= rawChan0)
                    && (rawChan0 < CyFilterVinMuxLimits.MUX_3_MAX))
                {
                    select = rawChan0 - CyFilterVinMuxLimits.MUX_3_2_BASE;
                }
            }

            return select;
        }

        /// <summary>
        /// Determine if UAB filter is used by any configuration.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>true if a UAB filter is used, false if not</returns>
        public static bool IsFilterPresent(CyParameters parameters)
        {
            if (parameters == null)
            {
                return false;
            }

            uint filterMask = CyModelUtils.ConfigFilterMasks(parameters);

            return (filterMask != 0) ? true : false;
        }

        /// <summary>
        /// Calculate sarmux VinPlus mux select value.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="muxNum">Sarmux vin plus mux channel number.</param>
        /// <returns>Sarmux vin plus mux select value</returns>
        public static int SarmuxVinPlusMuxSelect(CyParameters parameters, int muxNum)
        {
            if (parameters == null)
            {
                return 0;
            }

            // Select VinPlus ADC input for unused channels.
            int totalChannels = CyModelUtils.TotalChannelCount(parameters);
            if (muxNum >= totalChannels)
            {
                return (int)CyESarmuxVinPlusMuxSelect.VIN_PLUS;
            }

            // Select filter output for configuration channel 0's
            // that use a filter.
            int configNum;
            int configChanNum;
            CyModelUtils.RawChannelToConfigChannel(
                parameters, muxNum, out configNum, out configChanNum);
            uint filterMask = CyModelUtils.ConfigFilterMasks(parameters);
            if ((filterMask & (1u << configNum)) != 0 && configChanNum == 0)
            {
                return (int)CyESarmuxVinPlusMuxSelect.FILTER_VOUT;
            }

            // Otherwise select VinPlus ADC input.
            return (int)CyESarmuxVinPlusMuxSelect.VIN_PLUS;
        }

        /// <summary>
        /// Look up mux select value for specified VinMinus mux
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="muxNumber">VinMinus mux input select value</param>
        /// <returns>VinMinus mux select value</returns>
        public static int VinMinusMuxSelect(CyParameters parameters, int muxNumber)
        {
            // If there are no symbol instance parameters, select no-connect.
            if (parameters == null)
            {
                return (int)CyEVinMinusMuxSelect.NO_CONNECT;
            }

            // If a differential channel, select VinMinus terminal.
            if (CyModelUtils.IsRawChannelDifferential(parameters, muxNumber))
            {
                return (int)CyEVinMinusMuxSelect.TERMINAL;
            }

            // If not differential channel, select no-connect.
            return (int)CyEVinMinusMuxSelect.NO_CONNECT;
        }

        /// <summary>
        /// Look up mux select value for specified VinPlus mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="muxNumber">VinPlus mux index number</param>
        /// <returns>VinPlus mux input select value</returns>
        public static int VinPlusMuxSelect(CyParameters parameters, int muxNumber)
        {
            // If there are no symbol instance parameters, select no-connect.
            if (parameters == null)
            {
                return (int)CyEVinPlusMuxSelect.NO_CONNECT;
            }

            int channelCount = CyModelUtils.TotalChannelCount(parameters);

            // Select no-connect if mux is not used.
            if (muxNumber >= channelCount)
            {
                return (int)CyEVinPlusMuxSelect.NO_CONNECT;
            }

            // Otherwise select VinPlus terminal.
            return (int)CyEVinPlusMuxSelect.TERMINAL;
        }

        /// <summary>
        /// Look up mux select value for specified VinNeg mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="muxNumber">VinNeg mux index number</param>
        /// <returns>VinNeg mux input select value</returns>
        public static int VinNegMuxSelect(CyParameters parameters, int muxNumber)
        {
            // If there are no symbol instance parameters, select no-connect.
            if (parameters == null)
            {
                return (int)CyEVinNegMuxSelect.NO_CONNECT;
            }

            // If mux number out of range, select no-connect.
            int configCount = parameters.NumberOfConfigs;
            if (muxNumber >= configCount)
            {
                return (int)CyEVinNegMuxSelect.NO_CONNECT;;
            }

            if (CyModelUtils.ConfigUsesVnegVssaKelvin(parameters, muxNumber))
            {
                return (int)CyEVinNegMuxSelect.VSSA_KELVIN;
            }

            // The VinNegMux number is the config number.
            if (CyModelUtils.ConfigUsesVnegTerminal(parameters, muxNumber))
            {
                // Select Vneg terminal.
                return (int)CyEVinNegMuxSelect.TERMINAL;
            }

            // Otherwise select no-connect.
            return (int)CyEVinNegMuxSelect.NO_CONNECT;
        }

        /// <summary>
        /// Look up mux select value for specified Vref mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <param name="muxNumber">Vref mux index number</param>
        /// <returns>Vref mux input select value</returns>
        public static int VrefMuxSelect(CyParameters parameters, int muxNumber)
        {
            // If there are no symbol instance parameters, select no-connect.
            if (parameters == null)
            {
                return (int)CyEVrefMuxSelect.NO_CONNECT;
            }

            if (CyModelUtils.ConfigUsesVrefTerminal(parameters, muxNumber))
            {
                // Select Vref terminal.
                return (int)CyEVrefMuxSelect.TERMINAL;
            }
            else if (CyModelUtils.ConfigUsesDWVref(parameters, muxNumber))
            {
                // Select Vref terminal.
                return (int)CyEVrefMuxSelect.DW_VREF;
            }

            // Otherwise select no-connect.
            return (int)CyEVrefMuxSelect.NO_CONNECT;
        }

        /// <summary>
        /// Look up mux select value for SARMUX Vplus mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>SARMUX Vplus mux input select value</returns>
        public static int VplusMuxSelect(CyParameters parameters)
        {
            // If there are no symbol instance parameters, select vinPlus_0.
            if (parameters == null)
            {
                return (int)CyEVplusMuxSelect.SARMUX_VPLUS_OUT;
            }

            List<int> chanCounts = CyModelUtils.ChannelCounts(parameters);

            // If the configs have not yet been populated, select sarmux vplus.
            if (chanCounts.Count == 0)
            {
                return (int)CyEVplusMuxSelect.SARMUX_VPLUS_OUT;
            }

            // If there is more than one channel, use the sarmux.
            if (chanCounts.Count > 1 || chanCounts[0] > 1)
            {
                return (int)CyEVplusMuxSelect.SARMUX_VPLUS_OUT;
            }

            // Otherwise use channel 0's vinPlus directly.
            return (int)CyEVplusMuxSelect.VIN_PLUS_0;
        }

        /// <summary>
        /// Look up mux select value for SARMUX Vminus mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>SARMUX Vminus mux input select value</returns>
        public static int VminusMuxSelect(CyParameters parameters)
        {
            // If there are no symbol instance parameters, select sarmux vminus.
            if (parameters == null)
            {
                return (int)CyEVminusMuxSelect.SARMUX_VMINUS_OUT;
            }

            List<int> chanCounts = CyModelUtils.ChannelCounts(parameters);

            // If the configs have not yet been populated, select vinMinus_0.
            if (chanCounts.Count == 0)
            {
                return (int)CyEVminusMuxSelect.SARMUX_VMINUS_OUT;
            }

            // If there is more than one channel, use the sarmux.
            if (chanCounts.Count > 1 || chanCounts[0] > 1)
            {
                return (int)CyEVminusMuxSelect.SARMUX_VMINUS_OUT;
            }

            List<uint> diffMasks = CyModelUtils.ChannelDiffMasks(parameters);
            List<uint> filterMasks = CyModelUtils.ChannelFilterMasks(parameters);

            // If the only channel is differential or a filter, use its vinMinus directly.
            if (diffMasks[0] == 1 || filterMasks[0] == 1)
            {
                return (int)CyEVminusMuxSelect.VIN_MINUS_0;
            }

            // Otherwise use the only config's Vneg selection.
            // TODO: Do internal Vneg selections need to be handled differently?
            return (int)CyEVminusMuxSelect.VIN_NEG_0;
        }

        /// <summary>
        /// Look up number of SARMUX primitive's input channels
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>Number of SARMUX primitive's input channels</returns>
        public static byte SarmuxVinDiffWidth(CyParameters parameters)
        {
            // If there are no symbol instance parameters,
            // return a non-zero value so that validation of the
            // Schematic implementation's SARMUX BusConnects
            // does not trigger a build error.
            if (parameters == null)
            {
                return 1;
            }

            byte channelCount = (byte)CyModelUtils.TotalChannelCount(parameters);

            // TODO: Find out how non-null parameters can result in zero channels.
            if (channelCount < 1)
            {
                channelCount = 1;
            }

            return channelCount;
        }

        /// <summary>
        /// Look up number of SARMUX primitive's Vneg inputs.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>Number of SARMUX primitive's Vneg inputs</returns>
        public static byte SarmuxVinNegWidth(CyParameters parameters)
        {
            // If there are no symbol instance parameters,
            // return a non-zero value so that validation of the
            // Schematic implementation's SARMUX BusConnects
            // does not trigger a build error.
            if (parameters == null)
            {
                return 1;
            }

            byte configCount = (byte)parameters.NumberOfConfigs;

            // TODO: Find out how non-null parameters can result in zero configs.
            if (configCount < 1)
            {
                configCount = 1;
            }

            return configCount;
        }

        /// <summary>
        /// Return bitmask of SARMUX primitive's differential channels.
        /// 
        /// The bitmask is a string representation of a binary number.
        /// A "1" in the string marks a differential channel.
        /// A "0" in the string marks a single-ended channel.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>String repesentation of bitmask</returns>
        public static string SarmuxDiffMask(CyParameters parameters)
        {
            // If there are no symbol instance parameters,
            // return a string with 1 differential channel.
            if (parameters == null)
            {
                return "1";
            }

            List<int> chanCounts = CyModelUtils.ChannelCounts(parameters);
            List<uint> diffMasks = CyModelUtils.ChannelDiffMasks(parameters);
            List<uint> filterMasks = CyModelUtils.ChannelFilterMasks(parameters);

            StringBuilder builder = new StringBuilder();
            for (int configNum = 0; configNum < chanCounts.Count; configNum++)
            {
                uint mask = diffMasks[configNum] | filterMasks[configNum];
                for (int chanNum = 0; chanNum < chanCounts[configNum]; chanNum++)
                {
                    char isDiff = ((mask & (1u << chanNum)) != 0) ? '1' : '0';
                    builder.Append(isDiff);
                }
            }

            return builder.ToString();
        }

        /// <summary>
        /// Look up mux select value for SAR ExtVref mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>ExtVref mux input select value</returns>
        public static int ExtVrefMuxSelect(CyParameters parameters)
        {
            // If there are no symbol instance parameters, select no-connect.
            if (parameters == null)
            {
                return (int)CyEExtVrefMuxSelect.NO_CONNECT;
            }
            
            // Determine if the part has a dedicated Vref/Bypass pin or if it can be a GPIO
            var instQuery = parameters.InstQuery;
            var deviceQuery = instQuery.DeviceQuery;
            bool isDedicatedVref = false;
            CySarExtVrefType_v1 extVrefType_p6 = CySarExtVrefType_v1.NONE;

            if (deviceQuery.IsPSoC4)
            {
                var psoc4Query = deviceQuery.PSoC4DeviceInfoQueryV1;
                if (psoc4Query != null)
                {
                    psoc4Query.IsSarAdcExtVrefDedicated(out isDedicatedVref);
                }
            }
            else if (deviceQuery.IsPSoC6)
            {
                var psoc6Query = deviceQuery.PSoC6DeviceInfoQueryV1;
                if (psoc6Query != null)
                {
                    psoc6Query.GetSarAdcExtVrefType(out extVrefType_p6);
                }

            }

            if (CyModelUtils.AnyConfigHasDevicePinVref(parameters))
            {
                if (parameters.SarType == CyESarType.SAR_MXS40PASS)
                {
                    switch(extVrefType_p6)
                    {
                        case CySarExtVrefType_v1.DEDICATED:
                            return (int)CyEExtVrefMuxSelect.DEDICATED_VREF;
                        case CySarExtVrefType_v1.GPIO:
                            return (int)CyEExtVrefMuxSelect.BYPASS;
                        default:
                            return (int)CyEExtVrefMuxSelect.NO_CONNECT;
                    }
                }
                else
                {
                    // If the devices doesn't have a dedicated Vref pin, use a GPIO for the external Vref
                    if (isDedicatedVref == false)
                    {
                        return (int)CyEExtVrefMuxSelect.EXT_VREF;
                    }
                }                
            }

            if (CyModelUtils.AnyConfigHasVrefBypass(parameters))
            {
                if (parameters.SarType == CyESarType.SAR_MXS40PASS)
                {
                    switch (extVrefType_p6)
                    {
                        case CySarExtVrefType_v1.DEDICATED:
                            return (int)CyEExtVrefMuxSelect.DEDICATED_VREF;
                        case CySarExtVrefType_v1.GPIO:
                            return (int)CyEExtVrefMuxSelect.EXT_VREF;
                        default:
                            return (int)CyEExtVrefMuxSelect.NO_CONNECT;
                    }
                }
                else
                {
                    // If the devices doesn't have a dedicated Vref pin, use a GPIO for the external Vref
                    if (isDedicatedVref == false)
                    {
                        return (int)CyEExtVrefMuxSelect.BYPASS;
                    }
                    else
                    {
                        if (parameters.SarType == CyESarType.SAR_MXS40PASS)
                        {
                            return (int)CyEExtVrefMuxSelect.DEDICATED_VREF;
                        }
                    }
                }
            }

            return (int)CyEExtVrefMuxSelect.NO_CONNECT;
        }

        /// <summary>
        /// Look up mux select value for the SAR soc mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameters</param>
        /// <returns>Soc mux input select value</returns>
        public static int SocMuxSelect(CyParameters parameters)
        {
            // If there are no symbol instance parameters, select no-connect.
            if (parameters == null)
            {
                return (int)CyESocMuxSelect.LOGIC_ZERO;
            }

            // If configured for external soc, select soc terminal.
            if (parameters.ExternalSoc)
            {
                return (int)CyESocMuxSelect.TERMINAL;
            }

            // Otherwise select no-connect.
            return (int)CyESocMuxSelect.LOGIC_ZERO;
        }

        /// <summary>
        /// Look up mux select value for the SAR aclk mux.
        /// </summary>
        /// <param name="parameters">Scan_ADC symbol parameter</param>
        /// <returns>Aclk mux input select value</returns>
        public static int AclkMuxSelect(CyParameters parameters)
        {
            // If there are no symbol instance parameters, select internal clock.
            if (parameters == null)
            {
                return (int)CyEAclkMuxSelect.INTERNAL_CLOCK;
            }

            // If configured for external clock, select clock terminal.
            if (parameters.ExternalClk)
            {
                return (int)CyEAclkMuxSelect.TERMINAL;
            }

            // Otherwise select internal clock.
            return (int)CyEAclkMuxSelect.INTERNAL_CLOCK;
        }
    }
}

