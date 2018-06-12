/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace LPComp_PDL_v1_0
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string HYSTERESIS = "Hysteresis";
        public const string OUTPUT_CONFIGURATION = "OutputConfiguration";
        public const string POWER_SPEED = "PowerSpeed";
        public const string PULSE_INTERRUPT_CONFIGURATION = "PulseInterruptConfiguration";
        public const string LOCAL_VREF_INPUT = "LocalVrefInput";
    }
    #endregion

    #region Component Enums
    public enum CyEOutputModeType
    {
        LPCOMP_OUT_PULSE = 0,
        LPCOMP_OUT_DIRECT = 1,
        LPCOMP_OUT_SYNC = 2
    }
    public enum CyEHysteresisType
    {
        LPCOMP_DISABLE_HYST = 0,
        LPCOMP_ENABLE_HYST = 1
    }
    public enum CyEInterruptType
    {
        LPCOMP_INTR_DISABLE = 0,
        LPCOMP_INTR_RISING = 1,
        LPCOMP_INTR_FALLING = 2,
        LPCOMP_INTR_BOTH = 3
    }
    public enum CyESpeedType
    {
        LPCOMP_MODE_ULP = 1,
        LPCOMP_MODE_LP = 2,
        LPCOMP_MODE_NORMAL = 3
    }
    #endregion

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
