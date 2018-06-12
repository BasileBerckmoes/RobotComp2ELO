/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace Scan_ADC_v2_10
{

    public class CySchematicNames
    {
        public const string EXTERNAL_SAR_CLOCK_TERM = "aclk";
        public const string INTERNAL_SAR_CLOCK_GATE = "or_1"; // "or_internal";
        public const string INTERNAL_SAR_CLOCK_TERM = "term1";
    }

    /// <summary>
    /// VinMinus mux input select values.
    /// 
    /// VinMinus muxes are used on the Scan_ADC "vinMinus[31:0]" and
    /// "vinMinus[63:32]" schematic pages.
    /// </summary>
    public enum CyEVinMinusMuxSelect
    {
        TERMINAL = 0,
        NO_CONNECT = 1,
    }

    /// <summary>
    /// VinPlus mux input select values.
    /// 
    /// VinPlus muxes are used on the Scan_ADC "vinPlus[31:0]" and
    /// "vinPlus[63:32]" schematic pages.
    /// </summary>
    public enum CyEVinPlusMuxSelect
    {
        TERMINAL = 0,
        NO_CONNECT = 1,
    }

    /// <summary>
    /// VinNeg mux input select values.
    /// 
    /// Vneg muxes are used on the Scan_ADC "vinNeg[3:0]" schematic page.
    /// </summary>
    public enum CyEVinNegMuxSelect
    {
        TERMINAL = 0,
        NO_CONNECT = 1,
        VSSA_KELVIN = 2,
    }

    /// <summary>
    /// Vref mux input select values.
    /// 
    /// Vref muxes are used on the Scan_ADC "vref" schematic page.
    /// </summary>
    public enum CyEVrefMuxSelect
    {
        TERMINAL = 0,
        NO_CONNECT = 1,
        DW_VREF = 2,
    }

    /// <summary>
    /// Vplus mux input select values.
    /// 
    /// The vplus mux is used on the Scan_ADC "SARMUX" schematic page.
    /// </summary>
    public enum CyEVplusMuxSelect
    {
        SARMUX_VPLUS_OUT = 0,
        VIN_PLUS_0 = 1,
    }

    /// <summary>
    /// Vminus mux input select values.
    /// 
    /// The vminus mux is used on the Scan_ADC "SARMUX" schematic page.
    /// </summary>
    public enum CyEVminusMuxSelect
    {
        SARMUX_VMINUS_OUT = 0,
        VIN_MINUS_0 = 1,
        VIN_NEG_0 = 2,
    }

    /// <summary>
    /// ExtVref mux input select values.
    /// 
    /// The extVref mux is used on the Scan_ADC "SAR" schematic page.
    /// </summary>
    public enum CyEExtVrefMuxSelect
    {
        BYPASS = 0,
        EXT_VREF = 1,
        NO_CONNECT = 2,
        DEDICATED_VREF = 3,
    }

    /// <summary>
    /// Soc mux input select values.
    /// 
    /// The soc mux is used on the Scan_ADC "SAR" schematic page.
    /// </summary>
    public enum CyESocMuxSelect
    {
        TERMINAL = 0,
        LOGIC_ZERO = 1,
    }

    /// <summary>
    /// SAR clock mux select values.
    /// 
    /// The SAR clock mux is used on the Scan_ADC "SAR" schematic page.
    /// </summary>
    public enum CyEAclkMuxSelect
    {
        TERMINAL = 0,
        INTERNAL_CLOCK = 1,
    }

    /// <summary>
    /// Filter Vin mux channel number limits.
    /// 
    /// The filter Vin muxes are used on the Scan_ADC "filterVin[3:0]"
    /// schematic page.
    /// </summary>
    public static class CyFilterVinMuxLimits
    {
        public const int MUX_0_0_BASE = 0;
        public const int MUX_0_MAX = 1;
        public const int MUX_1_0_BASE = 1;
        public const int MUX_1_MAX = 17;
        public const int MUX_2_0_BASE = 2;
        public const int MUX_2_1_BASE = 18;
        public const int MUX_2_MAX = 33;
        public const int MUX_3_0_BASE = 3;
        public const int MUX_3_1_BASE = 19;
        public const int MUX_3_2_BASE = 35;
        public const int MUX_3_MAX = 49;
    }

    /// <summary>
    /// Sarmux VinPlus mux select values.
    /// 
    /// Sarmux VinPlus muxes are used on the Scan_ADC "sarmuxVinPlus[31:0]"
    /// and "sarmuxVinPlus[63:32]" schematic pages.
    /// </summary>
    public enum CyESarmuxVinPlusMuxSelect
    {
        VIN_PLUS = 0,
        FILTER_VOUT = 1,
    }
}
