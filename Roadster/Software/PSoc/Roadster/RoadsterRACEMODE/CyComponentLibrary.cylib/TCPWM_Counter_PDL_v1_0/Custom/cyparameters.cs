/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_Counter_PDL_v1_0.Utils;

namespace TCPWM_Counter_PDL_v1_0
{
    internal class CyParamNames
    {
        internal const string CAPTURE_INPUT = "CaptureInput";
        internal const string CLOCK_PRESCALER = "ClockPrescaler";
        internal const string COMPARE_0 = "Compare0";
        internal const string COMPARE_1 = "Compare1";
        internal const string COMPARE_OR_CAPTURE = "CompareOrCapture";
        internal const string COUNT_DIRECTION = "CountDirection";
        internal const string COUNT_INPUT = "CountInput";
        internal const string ENABLE_COMPARE_SWAP = "EnableCompareSwap";
        internal const string INTERRUPT_SOURCE = "InterruptSource";
        internal const string PERIOD = "Period";
        internal const string RELOAD_INPUT = "ReloadInput";
        internal const string COUNTER_RESOLUTION = "Resolution";
        internal const string RUN_MODE = "RunMode";
        internal const string START_INPUT = "StartInput";
        internal const string STOP_INPUT = "StopInput";
    }

    internal class CyParameters
    {
        #region Parameter getters
        public static uint GetPeriod(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetPeriod(query, out error);
        }

        public static uint GetPeriod(ICyInstQuery_v1 query, out CyCustErr error)
        {
            return GetValue<uint>(query, CyParamNames.PERIOD, out error);
        }

        public static uint GetCompare0(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetCompare0(query, out error);
        }

        public static uint GetCompare0(ICyInstQuery_v1 query, out CyCustErr error)
        {
            return GetValue<uint>(query, CyParamNames.COMPARE_0, out error);
        }

        public static uint GetCompare1(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetCompare1(query, out error);
        }

        public static uint GetCompare1(ICyInstQuery_v1 query, out CyCustErr error)
        {
            return GetValue<uint>(query, CyParamNames.COMPARE_1, out error);
        }

        public static CyEnums.CyClockPrescaler GetClockPrescaler(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyClockPrescaler>(query, CyParamNames.CLOCK_PRESCALER, out error);
        }

        public static CyEnums.CyCompareOrCapture GetCompareOrCapture(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyCompareOrCapture>(query, CyParamNames.COMPARE_OR_CAPTURE, out error);
        }

        public static CyEnums.CyCountDirection GetCountDirection(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyCountDirection>(query, CyParamNames.COUNT_DIRECTION, out error);
        }

        public static CyEnums.CyInterruptSources GetInterruptSource(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyInterruptSources>(query, CyParamNames.INTERRUPT_SOURCE, out error);
        }

        public static bool GetCompareSwap(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<bool>(query, CyParamNames.ENABLE_COMPARE_SWAP, out error);
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