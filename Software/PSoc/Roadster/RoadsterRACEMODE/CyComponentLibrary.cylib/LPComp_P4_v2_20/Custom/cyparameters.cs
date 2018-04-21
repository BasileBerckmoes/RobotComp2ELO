/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;
using System.Reflection;

namespace LPComp_P4_v2_20
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string P_HYSTERESIS = "Hysteresis";
        public const string P_SPEED = "Speed";
        public const string P_INTERRUPT = "Interrupt";
        public const string P_OUTPUTMODE = "OutputMode";
        public const string P_INTERRUPTENABLED = "InterruptEnabled";
        public const string P_OUTPOSITION = "LegacyOutputPosition";
    }
    #endregion

    #region Component terminals names
    public class CyTermName
    {
        public const string V_PLUS = "Vplus";
        public const string V_MINUS = "Vminus";
        public const string INTR = "intr";
    }
    #endregion

    #region Component Enums
    public enum CyEOutputModeType
    {
        [Description("Pulse")]
        OUT_MODE_PULSE,
        [Description("Synchronized")]
        OUT_MODE_SYNC,
        [Description("Direct")]
        OUT_MODE_DIRECT
    }
    public enum CyEHysteresisType
    {
        [Description("Enable")]
        LPC_ENABLE_HYST,
        [Description("Disable")]
        LPC_DISABLE_HYST
    }
    public enum CyEInterruptType
    {
        [Description("Disabled")]
        LPC_INT_DISABLE,
        [Description("Rising edge")]
        LPC_INT_RISING,
        [Description("Falling edge")]
        LPC_INT_FALLING,
        [Description("Both edges")]
        LPC_INT_BOTH
    }
    public enum CyESpeedType
    {
        [Description("Low Power")]
        LPC_LOW_SPEED = 2,
        [Description("Medium Power")]
        LPC_MED_SPEED = 0,
        [Description("High Power")]
        LPC_HIGH_SPEED = 1
    }
    #endregion

    public class CyParameters
    {
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private CyBasicTab m_basicTab;
        private CyAdvancedTab m_advancedTab;

        // During the first getting of parameters this variable is false which means that assigning
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

        public CyEHysteresisType Hysteresis
        {
            get { return GetValue<CyEHysteresisType>(CyParamNames.P_HYSTERESIS); }
            set { SetValue(CyParamNames.P_HYSTERESIS, value); }
        }
        public CyESpeedType Speed
        {
            get { return GetValue<CyESpeedType>(CyParamNames.P_SPEED); }
            set { SetValue(CyParamNames.P_SPEED, value); }
        }
        public CyEOutputModeType OutputMode
        {
            get { return GetValue<CyEOutputModeType>(CyParamNames.P_OUTPUTMODE); }
            set { SetValue(CyParamNames.P_OUTPUTMODE, value); }
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

        public bool LegacyOutputPosition
        {
            get { return GetValue<bool>(CyParamNames.P_OUTPOSITION); }
            set { SetValue(CyParamNames.P_OUTPOSITION, value); }
        }

        public bool IsLPCompIPV0 // PSoC 4100/4200
        {
            get { return InstQuery.DeviceQuery.GetFeatureVersion("m0s8lpcomp") == 0; }
        }

        public bool IsLPCompIPV2 // PSoC 4200-BL
        {
            get { return InstQuery.DeviceQuery.GetFeatureVersion("m0s8lpcomp") == 2; }
        }
        
        public CyBasicTab BasicTab
        {
            get { return m_basicTab; }
            set { m_basicTab = value; }
        }

        public CyAdvancedTab AdvancedTab
        {
            get { return m_advancedTab; }
            set { m_advancedTab = value; }
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
