/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Windows.Forms;

namespace Counter_v3_0
{
    public class CyCounterParameters
    {
        public CyCompDevParam m_captureMode = null;
        public CyCompDevParam m_clockMode = null;
        public CyCompDevParam m_compareMode = null;
        public CyCompDevParam m_compareValue = null;
        public CyCompDevParam m_enableMode = null;
        public CyCompDevParam m_runMode = null;
        public CyCompDevParam m_fixedFunction = null;
        public CyCompDevParam m_interruptOnCapture = null;
        public CyCompDevParam m_interruptOnCompare = null;
        public CyCompDevParam m_interruptOnOverUnderFlow = null;
        public CyCompDevParam m_interruptOnTC = null;
        public CyCompDevParam m_period = null;
        public CyCompDevParam m_reloadOnCapture = null;
        public CyCompDevParam m_reloadOnCompare = null;
        public CyCompDevParam m_reloadOnOverUnder = null;
        public CyCompDevParam m_reloadOnReset = null;
        public CyCompDevParam m_resolution = null;

        public const string CONFIGURE = "Configure";
        public const string ADVANCED = "Advanced";
        public const string BUILT_IN = "Built-in";
        public const string BASIC = "Basic";

        public const string CAL_PERIOD = "Period:";
        public const string BIT_RESOLUTION = "Bit Resolution:";
        public const string CLOCKMODE = "ClockMode";
        public const string COMPAREMODE = "CompareMode";
        public const string INTERRUPT_ON_CAPTURE = "InterruptOnCapture";
        public const string PERIOD = "Period";
        public const string UNIT = "u";
        public const string RESOLUTION = "Resolution";
        public const string EIGHT_BIT = "8";
        public const string SIXTEEN_BIT = "16";
        public const string TWENTYFOUR_BIT = "24";
        public const string THIRTYTWO_BIT = "32";
        public const string FIXEDFUNCTION = "FixedFunction";
        public const string TRUE = "true";
        public const string FALSE = "false";
        public const string COMPAREVALUE = "CompareValue";
        public const string ENABLEMODE = "EnableMode";
        public const string RUNMODE = "RunMode";
        public const string SOFTWARE = "Software";
        public const string ONLY = "Only";
        public const string INTERRUPT_ON_COMPARE = "InterruptOnCompare";
        public const string RELOAD_ON_CAPTURE = "ReloadOnCapture";
        public const string RELOAD_ON_COMPARE = "ReloadOnCompare";
        public const string RELOAD_ON_RESET = "ReloadOnReset";
        public const string RELOAD_ON_OVERUNDER = "ReloadOnOverUnder";
        public const string INTERRUPT_ON_TC = "InterruptOnTC";
        public const string CAPTUREMODE = "CaptureMode";
        public const string INTERRUPT_ON_OVER_UNDERFLOW = "InterruptOnOverUnderFlow";
        public const string UNHANDLED_CASE = "unhandled case";
        public const string MAX_PERIOD = "Max. Period:";

        public const uint CONST_2_8 = 255;
        public const uint CONST_2_16 = 65535;
        public const uint CONST_2_24 = 16777215;
        public const uint CONST_2_32 = 4294967295;

        public const string ClockModeEnumID_DownCounter = "Down Counter";
        public const string CompareModeEnumID_LessThan = "Less Than";

        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private bool m_globalEditMode = false;

        private CyCounterParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            GetParams();
        }

        public CyCounterParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyCounterParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public void GetParams()
        {
            m_captureMode = m_instQuery.GetCommittedParam(CAPTUREMODE);
            m_clockMode = m_instQuery.GetCommittedParam(CLOCKMODE);
            m_compareMode = m_instQuery.GetCommittedParam(COMPAREMODE);
            m_compareValue = m_instQuery.GetCommittedParam(COMPAREVALUE);
            m_enableMode = m_instQuery.GetCommittedParam(ENABLEMODE);
            m_runMode = m_instQuery.GetCommittedParam(RUNMODE);
            m_fixedFunction = m_instQuery.GetCommittedParam(FIXEDFUNCTION);
            m_interruptOnCapture = m_instQuery.GetCommittedParam(INTERRUPT_ON_CAPTURE);
            m_interruptOnCompare = m_instQuery.GetCommittedParam(INTERRUPT_ON_COMPARE);
            m_interruptOnOverUnderFlow = m_instQuery.GetCommittedParam(INTERRUPT_ON_OVER_UNDERFLOW);
            m_interruptOnTC = m_instQuery.GetCommittedParam(INTERRUPT_ON_TC);
            m_period = m_instQuery.GetCommittedParam(PERIOD);
            m_reloadOnCapture = m_instQuery.GetCommittedParam(RELOAD_ON_CAPTURE);
            m_reloadOnCompare = m_instQuery.GetCommittedParam(RELOAD_ON_COMPARE);
            m_reloadOnOverUnder = m_instQuery.GetCommittedParam(RELOAD_ON_OVERUNDER);
            m_reloadOnReset = m_instQuery.GetCommittedParam(RELOAD_ON_RESET);
            m_resolution = m_instQuery.GetCommittedParam(RESOLUTION);
        }

        static CyCustErr GetParamValue<T>(ICyInstQuery_v1 query, string paramName, out T value)
        {
            CyCustErr err = CyCustErr.Ok;
            value = default(T);

            CyCompDevParam param = query.GetCommittedParam(paramName);
            if (param == null)
            {
                return new CyCustErr(string.Format("Unknown Parameter '{0}'", paramName));
            }

            err = param.TryGetValueAs<T>(out value);
            if (err.IsNotOk)
            {
                value = default(T);
                return err;
            }

            if (param.ErrorCount != 0)
            {
                err = new CyCustErr(param.ErrorMsgs);
            }

            return err;
        }

        public void SetAParameter(string paramName, string value)
        {
            if (GlobalEditMode && m_instEdit != null && value != null && paramName != null)
            {
                m_instEdit.SetParamExpr(paramName, value);
                m_instEdit.CommitParamExprs();

                if (m_instEdit.GetCommittedParam(paramName).ErrorCount != 0)
                {
                    string errors = null;
                    foreach (string err in m_instEdit.GetCommittedParam(paramName).Errors)
                    {
                        errors = errors + err + "\n";
                    }
                    MessageBox.Show(String.Format("Error Setting Parameter {0} with value {1}\n\nErrors:\n{2}",
                        paramName, value, errors), "Error Setting Parameter",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        static CyCustErr GetEnumParamValues(ICyInstQuery_v1 query, string paramName, out int value,
        out string displayName, out string idName)
        {
            CyCustErr err = GetParamValue<int>(query, paramName, out value);
            CyCompDevParam param = query.GetCommittedParam(paramName);
            query.ResolveEnumParamToDisplay(param, out displayName);
            idName = query.ResolveEnumDisplayToId(paramName, displayName);
            return err;
        }

        public static CyCustErr GetFixedFunctionValue(ICyInstQuery_v1 query, out bool value)
        {
            return GetParamValue<bool>(query, FIXEDFUNCTION, out value);
        }

        public static CyCustErr GetClockModeValue(ICyInstQuery_v1 query, out string displayName)
        {
            int value;
            string idName;

            return GetEnumParamValues(query, CLOCKMODE, out value, out displayName, out idName);
        }

        public static CyCustErr GetCompareModeValue(ICyInstQuery_v1 query, out string displayName)
        {
            int value;
            string idName;

            return GetEnumParamValues(query, COMPAREMODE, out value, out displayName, out idName);
        }

        public static CyCustErr GetCaptureModeValue(ICyInstQuery_v1 query, out string displayName)
        {
            int value;
            string idName;

            return GetEnumParamValues(query, CAPTUREMODE, out value, out displayName, out idName);
        }

        public static CyCustErr GetEnableModeValue(ICyInstQuery_v1 query, out string displayName)
        {
            int value;
            string idName;

            return GetEnumParamValues(query, ENABLEMODE, out value, out displayName, out idName);
        }

        public static CyCustErr GetRunModeValue(ICyInstQuery_v1 query, out string displayName)
        {
            int value;
            string idName;

            return GetEnumParamValues(query, RUNMODE, out value, out displayName, out idName);
        }
    }
}
