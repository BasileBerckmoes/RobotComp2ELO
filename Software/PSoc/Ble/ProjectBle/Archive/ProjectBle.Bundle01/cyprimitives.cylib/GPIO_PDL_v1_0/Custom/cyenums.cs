/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    public sealed class CyValueAttribute : Attribute
    {
        public CyValueAttribute(string name, string prettyName = "")
        {
            Value = name;
            PrettyName = prettyName;
        }

        public string Value { get; private set; }
        public string PrettyName { get; private set; }
    }

    [Flags]
    public enum CyPinType
    {
        None = 0x00,
        Analog = 0x01,
        Digital_In = 0x02,
        Digital_Out = 0x04,
        OE = 0x08,
        Bidirectional = 0x10
    }

    /// <summary>
    /// Make checks for type flags more readable
    /// </summary>
    internal static class CyPinTypeChecks
    {
        internal static bool Is(this CyPinType type, CyPinType bit)
        {
            return (type & bit) == bit;
        }
        internal static bool IsOneOf(this CyPinType type, CyPinType bits)
        {
            Debug.Assert(bits != CyPinType.None);
            return (type & bits) > 0;
        }
    }

    public enum CyDriveMode
    {
        [CyValue("0")]
        High_impedance_analog,
        [CyValue("1")]
        High_impedance_digital,
        [CyValue("2")]
        Resistive_pull_up,
        [CyValue("3")]
        Resistive_pull_down,
        [CyValue("4")]
        Open_drain_Drive_low,
        [CyValue("5")]
        Open_drain_Drive_high,
        [CyValue("6")]
        Strong_Drive,
        [CyValue("7")]
        Resistive_pull_up_down,
        [CyValue("6")]
        Default = Strong_Drive
        //The default value depends on the PinType.
    }

    public enum CyInputThreshold
    {
        [CyValue("C")]
        CMOS,
        [CyValue("CT")]
        CMOS_LVTTL,
        [CyValue("T")]
        LVTTL,
        [CyValue("D")]
        Vddio,
        [CyValue("5R")]
        Pt5_Vref, 
        [CyValue("R")]
        Vref, // Routed vref
        [CyValue("RI")]
        Vref_internal, // Internal 1.2V, PSoC 4 only
        [CyValue("5RI")]
        Pt5_Vref_internal,
        [CyValue("C")]
        Default = CMOS
    }

    public enum CyInputInterruptTrigger
    {
        [CyValue("0")]
        None,
        [CyValue("1")]
        Rising_edge,
        [CyValue("2")]
        Falling_edge,
        [CyValue("3")]
        Both_edges,
        [CyValue("0")]
        Default = None
    }

    public enum CySyncMode
    {
        [CyValue("0")]
        Transparent,
        [CyValue("1")]
        Single,
        [CyValue("2")]
        Double,
        [CyValue("0")]
        Default = Transparent
    }

    public enum CyOutputSlewRate
    {
        [CyValue("0")]
        Fast,
        [CyValue("1")]
        Slow,
        [CyValue("0")]
        Default = Fast
    }

    public enum CyOutputDriveLevel
    {
        [CyValue("0")]
        Vddio,
        [CyValue("1")]
        Vref, // Routed Vref
        [CyValue("2")]
        Vref_Internal,
        [CyValue("0")]
        Default = Vddio
    }

    /// <summary>
    /// Not written out; used to determine SIOVref compatibility.
    /// </summary>
    public enum CyVrefSource
    {
        DontCare,
        Internal,
        Routed,
        Default = DontCare
    }

    public enum CyOutputCurrentCap
    {
        [CyValue("5")]
        Source_5ma_Sink_5ma,
        [CyValue("8")]
        Source_8ma_Sink_8ma,
        [CyValue("16")]
        Source_16ma_Sink_16ma,
        [CyValue("40")]
        Source_40ma_Sink_40ma,
        [CyValue("8")]
        Default = Source_8ma_Sink_8ma
    }

    public enum CyDriveStrength
    {
        [CyValue("0")]
        Full,
        [CyValue("1")]
        Half,
        [CyValue("2")]
        Quarter,
        [CyValue("3")]
        Eighth,
        [CyValue("0")]
        Default = Full
    }

    public enum CyMaxFrequency
    {
        [CyValue("0", "N/A")] // I2C mode used
        MHz_NA,
        [CyValue("1", "1 MHz")]
        MHz_1,
        [CyValue("50", "50 MHz")]
        MHz_50,
        [CyValue("80", "80 MHz")]
        MHz_80,
        [CyValue("100", "100 MHz")]
        MHz_100,
        [CyValue("200", "200 MHz")]
        MHz_200,
        [CyValue("100", "100 MHz")]
        Default = MHz_100
    }

    public enum CyI2CMode
    {
        [CyValue("0", "N/A")] // Max Frequency used
        I2C_NA,
        [CyValue("1", "I2C SM (100 kbps)")]
        I2C_SM,
        [CyValue("2", "I2C FM (400 kbps)")]
        I2C_FM,
        [CyValue("3", "I2C FM+ (1.0 Mbps)")]
        I2C_FM_plus,
        [CyValue("4", "I2C HS (3.4 Mbps)")]
        I2C_HS,
        [CyValue("0", "N/A")]
        Default = I2C_NA
    }
}
