/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.ComponentModel;
using System.Diagnostics;

namespace CSD_Comp_P4_v1_0
{
    #region Component Parameters Names

    public static class CyParamNames
    {
        public const string TAP = "Tap";
        public const string INPUT_REF_VOLTAGE = "InputRefVoltage";
        public const string VOLTAGE_REF_TYPE = "VoltageRefType";
        public const string VOLTAGE_REF_RANGE = "VoltageRefRange";
        public const string VOLTAGE_REF_SOURCE = "VoltageRefSource";
    }

    #endregion

    #region Component Enums

    public enum CyEnumRefSourceType
    {
        [Description("Internal Bandgap")]
        INTERNAL_BANDGAP = 0,
        [Description("External Reference")]
        EXTERNAL_REFERENCE = 1
    }

    public enum CyEnumRefType
    {
        [Description("Fixed")]
        FIXED = 0,
        [Description("Adjustable")]
        ADJUSTABLE = 1
    }

    public enum CyEnumSpeedType
    {
        [Description("Fast Speed")]
        FAST_SPEED = 0,
        [Description("Slow Speed")]
        SLOW_SPEED = 1
    }

    #endregion Component Enums

    public class CyParameters
    {
        #region Class Consts
        public const int MAX_TAP_NUMBER = 32;
        public const int MAX_AMPLIFIER_GAIN = 31;

        public const double EPS = 0.005;
        public const double MIN_TAP_VOLTAGE = 0.6;
        public const double MIN_VINREF_VOLTAGE = 0.6;
        public const double MAX_VINREF_VOLTAGE = 4.4;
        public const double MAX_VRANGE_VOLTAGE = 4.4;
        public const double MAX_VINREF_VDDA_OFFSET = 0.6;
        public const double MAX_VRANGE_VDDA_OFFSET = 0.6;

        public const string SRSSV2_IP_NAME = "m0s8srssv2";
        public const double SRSSV2_VBGR_VALUE = 1.024;
        public const double SRSSLT_VBGR_VALUE = 1.2;

        public const string VBGR_NAME = "Vbgr";
        public const string VINREF_NAME = "Vinref";

        /* Parameter to distinguish CSDv2 IP block typeouts  */
        internal const string M0S8_CSDv2_REF9P6UA_EN = "REF9P6UA_EN";
        internal const string M0S8_CSDv2 = "m0s8csdv2";
        #endregion Class Consts

        #region Class members

        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private ICyTabbedParamEditor m_editor;

        // When parameters are first obtained, this variable is false, which means that assigned
        // values to form the controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        private readonly double m_bandgap;
        private readonly double m_vdda;

        #endregion Class members

        #region Constructor(s)

        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;

            if (instQuery.DeviceQuery.GetFeatureCount(SRSSV2_IP_NAME) > 0)
                m_bandgap = SRSSV2_VBGR_VALUE;
            else
                m_bandgap = SRSSLT_VBGR_VALUE;

            m_vdda = instQuery.VoltageQuery.VDDA;
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }

        #endregion Constructor(s)

        #region Class properties

        public ICyTabbedParamEditor Editor
        {
            get { return m_editor; }
            set { m_editor = value; }
        }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public CyEnumRefSourceType RefSource
        {
            get { return GetValue<CyEnumRefSourceType>(CyParamNames.VOLTAGE_REF_SOURCE); }
            set { SetValue(CyParamNames.VOLTAGE_REF_SOURCE, value); }
        }

        public CyEnumRefType RefType
        {
            get { return GetValue<CyEnumRefType>(CyParamNames.VOLTAGE_REF_TYPE); }
            set { SetValue(CyParamNames.VOLTAGE_REF_TYPE, value); }
        }

        public string InstName
        {
            get { return GetValue<string>("INSTANCE_NAME"); }
        }

        public byte Tap
        {
            get { return GetValue<byte>(CyParamNames.TAP); }
            set { SetValue(CyParamNames.TAP, value); }
        }

        public double Vdda
        {
            get { return m_vdda; }
        } 

        public double Bandgap
        {
            get { return m_bandgap; }
        }

        public double Vinref
        {
            get { return GetValue<double>(CyParamNames.INPUT_REF_VOLTAGE); }
            set { SetValue(CyParamNames.INPUT_REF_VOLTAGE, value); }
        }

        public double VrangeDesired
        {
            get { return GetValue<double>(CyParamNames.VOLTAGE_REF_RANGE); }
            set { SetValue(CyParamNames.VOLTAGE_REF_RANGE, value); }
        }

        public double VrangeActual
        {
            get
            {
                int gain = AmplifierGain;
                double amplifierVin = AmplifierVin;

                if (gain < 0 || amplifierVin < 0)
                    return 0;
                else
                    return (MAX_TAP_NUMBER * amplifierVin) / (1 + gain);
            }
        }

        public double AmplifierVin
        {
            get
            {
                switch (RefSource)
                {
                    case CyEnumRefSourceType.INTERNAL_BANDGAP:
                        if (Bandgap < 0 + EPS)
                            return 0;

                        return Bandgap;

                    case CyEnumRefSourceType.EXTERNAL_REFERENCE:
                        if (Vinref < 0 + EPS)
                            return 0;

                        return Vinref;

                    default: 
                        Debug.Assert(false);
                        return 0;
                }
            }
        }

        public int AmplifierGain
        {
            get
            {
                if (VrangeDesired <= 0 + EPS)
                    return 0;

                double amplifierVin = AmplifierVin;

                try
                {
                    return Convert.ToInt32((MAX_TAP_NUMBER * amplifierVin) / VrangeDesired - 1);
                }
                catch (System.OverflowException ex)
                {
                    Debug.Fail(ex.Message);
                    return 0;
                }
            }
        }

        public Int32 AdjVrefStep_mV
        {
            get
            {
                return Convert.ToInt32(VrangeActual / MAX_TAP_NUMBER * 1000);
            }
        }

        public double Vsource
        {
            get 
            {
                switch (RefSource)
                {
                    case CyEnumRefSourceType.EXTERNAL_REFERENCE:
                        return Vinref;
                    case CyEnumRefSourceType.INTERNAL_BANDGAP:
                        return Bandgap;

                    default:
                        Debug.Assert(false);
                        return 0;
                }
            }
        }

        public string VsourceName
        {
            get
            {
                switch (RefSource)
                {
                    case CyEnumRefSourceType.EXTERNAL_REFERENCE:
                        return VINREF_NAME;
                    case CyEnumRefSourceType.INTERNAL_BANDGAP:
                        return VBGR_NAME;

                    default:
                        Debug.Assert(false);
                        return string.Empty;
                }
            }
        }

        #endregion Class properties

        #region Getting Parameter

        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null) return default(T);
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        #endregion Getting Parameter

        #region Setting Parameter

        private void SetValue<T>(string paramName, T value)
        {
            if (m_instEdit != null && m_globalEditMode)
            {
                string valueToSet = (value == null) ? String.Empty : value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((value is byte) || (value is UInt16) || (value is UInt32) || (value is UInt64))
                    valueToSet += "u";
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }

        #endregion Setting Parameter
    }
}