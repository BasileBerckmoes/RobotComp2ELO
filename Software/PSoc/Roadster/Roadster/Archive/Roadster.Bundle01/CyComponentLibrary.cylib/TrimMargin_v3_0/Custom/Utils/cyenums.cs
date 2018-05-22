/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.ComponentModel;

namespace TrimMargin_v3_0
{
    public enum CyESeriesType
    {
        E24,
        E48,
        E96,
        E192
    }

    public enum CyEControllerMethod
    {
        Incremental,
        Integral
    }

    public enum CyEImplementation
    {
        UDB,
        FixedFunction
    }

    public enum CyEFeedback
    {
        Positive,
        Negative
    }

    internal enum CyEFields
    {
        // Voltages table fields
        ConverterName,
        NominalVoltage,
        MinVoltage,
        MaxVoltage,
        StartupVoltage,
        MarginLowPercent,
        MarginHighPercent,
        MarginLow,
        MarginHigh,
        ControlSampleTime,

        // Hardware table fields
        VhPwmOutput,
        Vadj,
        R1,
        R2,
        R3,
        R4,
        DesiredVoutRipple,
        C1
    }

    internal enum CyESanityCheck
    {
        /// <summary>
        /// VMin[x] < VMax[x]
        /// </summary>
        MinMaxVoltageSanity,

        /// <summary>
        /// VMin[x] calc <= VMarginLow[x]
        /// </summary>
        MinVoltageSanity,

        /// <summary>
        /// VMarginLow[x] <= VNom[x]
        /// </summary>
        MarginLowVoltage,

        /// <summary>
        /// VNom[x] <= VMarginHi[x]
        /// </summary>
        NominalOutputVoltage,

        /// <summary>
        /// VMarginHi[x] <= VMax[x] calc
        /// </summary>
        MarginHighVoltage,

        /// <summary>
        /// Vmin[x] calc <= VStartup[x]
        /// </summary>
        MinVoltageToVStartup,

        /// <summary>
        /// VStartup[x] <= VMax[x] calc
        /// </summary>
        VStartupToMaxVoltage
    }
}