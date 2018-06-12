/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace MCWDT_PDL_v1_0
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string CASCADE_C0C1      = "CascadeC0C1";
        public const string CASCADE_C1C2      = "CascadeC1C2";
        public const string C0_MODE           = "C0Mode";
        public const string C1_MODE           = "C1Mode";
        public const string C2_MODE           = "C2Mode";
        public const string C0_MATCH          = "C0Match";
        public const string C1_MATCH          = "C1Match";
        public const string C0_CLEAR_ON_MATCH = "C0ClearOnMatch";
        public const string C1_CLEAR_ON_MATCH = "C1ClearOnMatch";
        public const string C2_PERIOD         = "C2Period";
    }
    #endregion

    #region Component Enums
    public enum CyEModeType
    {
        FREE_RUNNING             = 0,
        INTERRUPT                = 1,
        WDT_RESET                = 2,
        THREE_INT_THEN_WDT_RESET = 3
    }

    public enum CyEC2ModeType
    {
        FREE_RUNNING = 0,
        INTERRUPT    = 1
    }

    public enum CyEClearOnMatchType
    {
        FREE_RUNNING   = 0,
        CLEAR_ON_MATCH = 1
    }

    public enum CyEPeriodType
    {
        TOGGLE_BIT_0  = 0,
        TOGGLE_BIT_1  = 1,
        TOGGLE_BIT_2  = 2,
        TOGGLE_BIT_3  = 3,
        TOGGLE_BIT_4  = 4,
        TOGGLE_BIT_5  = 5,
        TOGGLE_BIT_6  = 6,
        TOGGLE_BIT_7  = 7,
        TOGGLE_BIT_8  = 8,
        TOGGLE_BIT_9  = 9,
        TOGGLE_BIT_10 = 10,
        TOGGLE_BIT_11 = 11,
        TOGGLE_BIT_12 = 12,
        TOGGLE_BIT_13 = 13,
        TOGGLE_BIT_14 = 14,
        TOGGLE_BIT_15 = 15,
        TOGGLE_BIT_16 = 16,
        TOGGLE_BIT_17 = 17,
        TOGGLE_BIT_18 = 18,
        TOGGLE_BIT_19 = 19,
        TOGGLE_BIT_20 = 20,
        TOGGLE_BIT_21 = 21,
        TOGGLE_BIT_22 = 22,
        TOGGLE_BIT_23 = 23,
        TOGGLE_BIT_24 = 24,
        TOGGLE_BIT_25 = 25,
        TOGGLE_BIT_26 = 26,
        TOGGLE_BIT_27 = 27,
        TOGGLE_BIT_28 = 28,
        TOGGLE_BIT_29 = 29,
        TOGGLE_BIT_30 = 30,
        TOGGLE_BIT_31 = 31
    }
    #endregion

    public static class CyClockUtils
    {
        public const double LF_CLK_FREQ = 32000;
        public const double EPS = 1E-5;

        public const double MIN = 60;
        public const double HOURS = 60 * MIN;
        public const double DAYS = 24 * HOURS;
        public const double YEARS = 365 * DAYS;
        public const double KYEARS = 1000 * YEARS;
        public const double MYEARS = 1000 * KYEARS;

        public static string FormatFrequency(double divider)
        {
            double freq = (System.Math.Abs(divider) < EPS) ? LF_CLK_FREQ : (LF_CLK_FREQ / divider);

            string retFreq = ((freq + EPS) >= 1000) ? string.Format("Freq (KHz): {0:F2}", freq / 1000) :
                                                      string.Format("Freq (Hz): {0:F2}" , freq);
            return (retFreq);
        }

        public static string FormatPeriod(double divider)
        {
            double period = divider / LF_CLK_FREQ;
            double periodEps = period + EPS;
            string retPeriod;

            retPeriod = (periodEps >= MYEARS) ? string.Format("Period (MYear): {0:F2}", period / MYEARS ) :
                        (periodEps >= KYEARS) ? string.Format("Period (KYear): {0:F2}", period / KYEARS ) :
                        (periodEps >= YEARS ) ? string.Format("Period (year): {0:F2}" , period / YEARS  ) :
                        (periodEps >= DAYS  ) ? string.Format("Period (day): {0:F2}"  , period / DAYS   ) :
                        (periodEps >= HOURS ) ? string.Format("Period (hr): {0:F2}"   , period / HOURS  ) :
                        (periodEps >= MIN   ) ? string.Format("Period (min): {0:F2}"  , period / MIN    ) :
                        (periodEps >= 1     ) ? string.Format("Period (s): {0:F2}"    , period          ) :
                        (periodEps >= 1E-3  ) ? string.Format("Period (ms): {0:F2}"   , period * 1000   ) :
                                                string.Format("Period (us): {0:F2}"   , period * 1000000);

            return (retPeriod);
        }
    }

    public static class CyParameters
    {
        public static T GetValue<T>(ICyInstQuery_v1 instQuery, string paramName)
        {
            if (instQuery == null) return default(T);
            T value;
            CyCustErr err = instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }
    }
}
