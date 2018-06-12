/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_PWM_PDL_v1_0.Utils;

namespace TCPWM_PWM_PDL_v1_0
{
    internal class CyParamNames
    {
        internal const string PWM_ALIGNMENT = "PwmAlignment";
        internal const string CLOCK_PRESCALER = "ClockPrescaler";
        internal const string COMPARE0 = "Compare0";
        internal const string COMPARE1 = "Compare1";
        internal const string COUNT_INPUT = "CountInput";
        internal const string DEAD_CLOCKS = "DeadClocks";
        internal const string ENABLE_COMPARE_SWAP = "EnableCompareSwap";
        internal const string ENABLE_PERIOD_SWAP = "EnablePeriodSwap";
        internal const string INTERRUPT_SOURCE = "InterruptSource";
        internal const string INVERT_PWM = "InvertPwm";
        internal const string INVERT_PWM_N = "InvertPwm_n";
        internal const string KILL_INPUT = "KillInput";
        internal const string KILL_MODE = "KillMode";
        internal const string PWM_MODE = "PwmMode";
        internal const string PERIOD0 = "Period0";
        internal const string PERIOD1 = "Period1";
        internal const string RELOAD_INPUT = "ReloadInput";
        internal const string RESOLUTION = "Resolution";
        internal const string RUN_MODE = "RunMode";
        internal const string START_INPUT = "StartInput";
        internal const string SWAP_INPUT = "SwapInput";
    }

    internal class CyParameters
    {
        #region Parameters getters
        public static CyEnums.CyMode GetMode(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyMode>(query, CyParamNames.PWM_MODE, out error);
        }

        public static CyEnums.CyAlignment GetAlignment(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyAlignment>(query, CyParamNames.PWM_ALIGNMENT, out error);
        }

        public static CyEnums.CyRunMode GetRunMode(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyRunMode>(query, CyParamNames.RUN_MODE, out error);
        }

        public static CyEnums.CyClockPrescaler GetClockPrescaler(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyClockPrescaler>(query, CyParamNames.CLOCK_PRESCALER, out error);
        }

        public static byte GetDeadTimeClocks(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<byte>(query, CyParamNames.DEAD_CLOCKS, out error);
        }

        public static CyEnums.CyResolution GetResolution(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyResolution>(query, CyParamNames.RESOLUTION, out error);
        }

        public static uint GetPeriod0(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetPeriod0(query, out error);
        }

        public static uint GetPeriod0(ICyInstQuery_v1 query, out CyCustErr error)
        {
            return GetValue<uint>(query, CyParamNames.PERIOD0, out error);
        }

        public static uint GetPeriod1(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetPeriod1(query, out error);
        }

        public static uint GetPeriod1(ICyInstQuery_v1 query, out CyCustErr error)
        {
            return GetValue<uint>(query, CyParamNames.PERIOD1, out error);
        }

        public static bool GetPeriodSwap(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<bool>(query, CyParamNames.ENABLE_PERIOD_SWAP, out error);
        }

        public static uint GetCompare0(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetCompare0(query, out error);
        }

        public static uint GetCompare0(ICyInstQuery_v1 query, out CyCustErr error)
        {
            return GetValue<uint>(query, CyParamNames.COMPARE0, out error);
        }

        public static uint GetCompare1(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetCompare1(query, out error);
        }

        public static uint GetCompare1(ICyInstQuery_v1 query, out CyCustErr error)
        {
            return GetValue<uint>(query, CyParamNames.COMPARE1, out error);
        }

        public static bool GetCompareSwap(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<bool>(query, CyParamNames.ENABLE_COMPARE_SWAP, out error);
        }

        public static CyEnums.CyKillMode GetKillMode(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyKillMode>(query, CyParamNames.KILL_MODE, out error);
        }
        #endregion

        #region Getting parameters
        /// <summary>
        /// Gets parameter value from the symbol.
        /// </summary>
        public static T GetValue<T>(ICyInstQuery_v1 instQuery, string paramName, out CyCustErr error)
        {
            T value = default(T);
            if (instQuery == null)
            {
                error = new CyCustErr("InstQuery object is null.");
                return value;
            }

            CyCompDevParam param = instQuery.GetCommittedParam(paramName);
            if (param != null)
            {
                if (param.ErrorCount == 0)
                {
                    error = param.TryGetValueAs<T>(out value);
                }
                else
                {
                    error = new CyCustErr(param.ErrorMsgs);
                    param.TryGetValueAs<T>(out value);
                }
            }
            else
            {
                error = new CyCustErr("CyCompDevParam object is null.");
            }

            return value;
        }
        #endregion

        #region Clock
        public static double GetExternalClockKhz(ICyTerminalQuery_v1 termQuery)
        {
            return CyClock.GetExternalClockKhz(termQuery, "clock");
        }
        #endregion
    }
}