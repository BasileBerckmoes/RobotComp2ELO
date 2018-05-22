/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_QuadDec_PDL_v1_0.Utils;

namespace TCPWM_QuadDec_PDL_v1_0
{
    internal class CyParamNames
    {
        internal const string COUNTER_RESOLUTION = "Resolution";
        internal const string COUNTER_SIZE = "CounterSize";
        internal const string INDEX_INPUT = "IndexInput";
        internal const string INTERRUPT_SOURCE = "InterruptSource";
        internal const string STOP_INPUT = "StopInput";
    }

    internal class CyParameters
    {
        public static CyEnums.CyCounterResolution GetCounterResolution(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyCounterResolution>(query, CyParamNames.COUNTER_RESOLUTION, out error);
        }

        public static CyEnums.CyInputMode GetIndexInput(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyInputMode>(query, CyParamNames.INDEX_INPUT, out error);
        }

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
    }
}