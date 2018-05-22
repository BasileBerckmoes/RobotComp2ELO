/*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit;

using VDAC12_PDL_v1_0.Utils;

// The namespace is required to have the same name as the component for a customizer.
namespace VDAC12_PDL_v1_0
{
     internal class CyParamNames
    {
        internal const string VREF_SOURCE = "VrefSource";
        internal const string VREF_VOLTAGE = "VrefVoltage";
        internal const string OUTPUT_BUFFER = "OutputBuffer";
        internal const string DAC_CODE_MODE = "DacCodeMode";
        internal const string INITIAL_CODE = "InitialCode";
        internal const string SHOW_STROBE = "ShowStrobe";
        internal const string SHOW_INT   = "ShowInt";
        internal const string DEBUG_ENABLE = "DebugEnable";
        internal const string UPDATE_MODE = "UpdateMode";
        internal const string DEEP_SLEEP = "DeepSleep";
        internal const string DWR_VREF_EXT = "DwrExtAfterCustomized";
        internal const string REFERENCE_CURRENT_HIGH = "ReferenceCurrentHigh";
    }

    internal class CyParameters
    {
        #region Parameters getters
        public static CyEnums.CyESignMode GetCodeMode(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyESignMode>(query, CyParamNames.DAC_CODE_MODE, out error);
        }

        public static CyEnums.CyEVrefSource GetVrefSource(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyEVrefSource>(query, CyParamNames.VREF_SOURCE, out error);
        }

        public static CyEnums.CyEUpdateType GetUpdateMode(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyEUpdateType>(query, CyParamNames.UPDATE_MODE, out error);
        }

        public static CyEnums.CyEStrobeTerminalType GetStrobeType(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyEStrobeTerminalType>(query, CyParamNames.SHOW_STROBE, out error);
        }

        public static CyEnums.CyEOutputType GetOutputBuffer(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<CyEnums.CyEOutputType>(query, CyParamNames.OUTPUT_BUFFER, out error);
        }

        // Wrapper to prevent null reference when querying VDDA
        public static double GetVddaVoltage(ICyInstQuery_v1 query)
        {
            if (query.VoltageQuery != null)
            {
                return (query.VoltageQuery.VDDA);
            }
            else
            {
                return -1.0;
            }
        }

        // Wrapper to prevent null reference when querying System Voltage
        public static double GetSysRefVoltage(ICyInstQuery_v1 query)
        {
            if (query.VoltageQuery != null)
            {
                return (query.VoltageQuery.SystemReference);
            }
            else
            {
                return -1.0;
            }
        }

        public static double GetVrefVoltage(ICyInstQuery_v1 query)
        {
            CyCustErr error;

            if (GetVrefSource(query).Equals(CyEnums.CyEVrefSource.VrefVdda))
            {
                return GetVddaVoltage(query);
            }
            else if (GetVrefSource(query).Equals(CyEnums.CyEVrefSource.VrefDWR))
            {
                double vref = GetSysRefVoltage(query);
                if(double.IsNaN(vref))
                {
                    return GetValue<double>(query, CyParamNames.VREF_VOLTAGE, out error);
                }
                else
                {
                    return vref;
                }                
            }
            else
            {
                return GetValue<double>(query, CyParamNames.VREF_VOLTAGE, out error);
            }
        }

        public static bool GetDeepSleep(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<bool>(query, CyParamNames.DEEP_SLEEP, out error);
        }

        public static Int16 GetInitialCode(ICyInstQuery_v1 query)
        {
            CyCustErr error;
            return GetValue<Int16>(query, CyParamNames.INITIAL_CODE, out error);
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

        #region Setting parameters
        /// <summary>
        /// Sets parameter value from the symbol.
        /// </summary>
        public static void SetValue<T>(ICyInstEdit_v1 instEdit, string paramName, T value, out CyCustErr error)
        {            
            if (instEdit == null)
            {
                error = new CyCustErr("InstQuery object is null.");
                return;
            }

            string valueToSet = value.ToString();
            if (value is bool)
                valueToSet = valueToSet.ToLower();
            if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                valueToSet += "u";

            if (instEdit.SetParamExpr(paramName, valueToSet) && instEdit.CommitParamExprs())
            {
                error = CyCustErr.OK;
                return;
            }


            CyCompDevParam param = instEdit.GetCommittedParam(paramName);
            error = param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }
        #endregion

        #region Parameter setters
        public static void SetDwrExtVref(ICyInstEdit_v1 edit, bool value)
        {
            CyCustErr error;
            SetValue<bool>(edit, CyParamNames.DWR_VREF_EXT, value, out error);
        }

        public static void SetReferenceCurrentHigh(ICyInstEdit_v1 edit, bool value)
        {
            CyCustErr error;
            SetValue<bool>(edit, CyParamNames.REFERENCE_CURRENT_HIGH, value, out error);
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

//[] END OF FILE
