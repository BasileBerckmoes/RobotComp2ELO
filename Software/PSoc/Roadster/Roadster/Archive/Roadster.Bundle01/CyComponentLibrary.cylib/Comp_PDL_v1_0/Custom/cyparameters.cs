/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.ComponentModel;

namespace Comp_PDL_v1_0
{

    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string P_HYSTERESIS = "Hysteresis";
        public const string P_INTERRUPT = "Interrupt";
        public const string P_POLARITY = "Polarity";
        public const string P_POWER = "Power";
        public const string P_DEEPSLEEP = "DeepSleepSupport";
        public const string P_INTERRUPTENABLED = "InterruptEnabled";
    }

    #endregion

    #region Component terminals names
    public class CyTermName
    {
        public const string V_PLUS = "Vplus";
        public const string V_MINUS = "Vminus";
        public const string CMP_OUT = "CmpOut";
    }
    #endregion

    #region Component Enums
    public enum CyEPolarityType
    {
        [Description("Non-inverting")]
        CMP_NON_INVERTING,

        [Description("Inverting")]
        CMP_INVERTING
    }

    public enum CyEHysteresisType
    {
        [Description("Disable")]
        CMP_DISABLE_HYST,

        [Description("Enable")]
        CMP_ENABLE_HYST
    }

    public enum CyEInterruptType
    {
        [Description("Disabled")]
        INTR_DISABLE,
        [Description("Rising edge")]
        INTR_RISING,
        [Description("Falling edge")]
        INTR_FALLING,
        [Description("Both edges")]
        INTR_BOTH
    }
    
    public enum CyEPowerType
    {
        [Description("None")]
        NONE = 0, // This value is not used and was added according to the best practices.

        [Description("Low Power")]
        CMP_LOW_POWER = 1,

        [Description("Medium Power")]
        CMP_MED_POWER = 2,

        [Description("High Power")]
        CMP_HIGH_POWER = 3
    }

    #endregion

    public class CyParameters
    {
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;

        // When parameters are first obtained, this variable is false, which means that assigned
        // values to form the controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }
        #endregion

        #region Class properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public bool Hysteresis
        {
            get { return GetValue<bool>(CyParamNames.P_HYSTERESIS); }
            set { SetValue(CyParamNames.P_HYSTERESIS, value); }
        }

        public CyEPowerType Power
        {
            get { return GetValue<CyEPowerType>(CyParamNames.P_POWER); }
            set { SetValue(CyParamNames.P_POWER, value); }
        }

        public CyEPolarityType Polarity
        {
            get { return GetValue<CyEPolarityType>(CyParamNames.P_POLARITY); }
            set { SetValue(CyParamNames.P_POLARITY, value); }
        }

        public CyEInterruptType Interrupt
        {
            get { return GetValue<CyEInterruptType>(CyParamNames.P_INTERRUPT); }
            set { SetValue(CyParamNames.P_INTERRUPT, value); }
        }

        public bool InterruptEnabled
        {
            get { return GetValue<bool>(CyParamNames.P_INTERRUPTENABLED); }
            set { SetValue(CyParamNames.P_INTERRUPTENABLED, value); }
        }

        public bool DeepSleep
        {
            get { return GetValue<bool>(CyParamNames.P_DEEPSLEEP); }
            set { SetValue(CyParamNames.P_DEEPSLEEP, value); }
        }

        public bool IsCTBmIPV0
        {
            // CTBm is a separate IP block.
            get { return InstQuery.DeviceQuery.GetFeatureVersion("M0S8_CTBM") == 0; }
        }

        public bool IsCTBIpBlock
        {
            // CTBm_ver2 and CTB are not separate IP blocks, they are part of "pass" IP blocks.
            get { return InstQuery.DeviceQuery.GetFeatureCount("m0s8pass4b") > 0; }
        }

        public bool IsUDB
        {
            get
            {
                return InstQuery.DeviceQuery.GetFeatureCount("m0s8udb") > 0 ||
                    InstQuery.DeviceQuery.GetFeatureCount("m0s8udbif") > 0;
            }
        }

        public double Vdda
        {
            get 
            {
                if (m_instQuery.VoltageQuery != null)
                {
                    return m_instQuery.VoltageQuery.VDDA;
                }
                else
                {
                    return -1;
                }
            }
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null) return default(T);
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }
        #endregion

        #region Setting Parameters
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
        #endregion
    }
}
