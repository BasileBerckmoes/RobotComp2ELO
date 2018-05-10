/*******************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace OpAmp_P4_v1_20
{

    #region Component parameters names
    public class CyParamName
    {
        public const string MODE = "Mode";
        public const string OUTPUT_CURRENT = "OutputCurrent";
        public const string POWER = "Power";
        public const string COMPENSATION = "Compensation";
        public const string P_DEEPSLEEP = "DeepSleepSupport";
    }

    #endregion

    #region Component terminal names
    public class CyTermName
    {
        public const string V_PLUS = "Vplus";
        public const string V_MINUS = "Vminus";
        public const string V_OUT = "Vout";
    }
    #endregion

    #region Component enums
    public enum CyEModeType
    {
        OPAMP,
        FOLLOWER
    }

    public enum CyEPowerType
    {
        OPAMP_LOW_POWER = 1,
        OPAMP_MED_POWER = 2,
        OPAMP_HIGH_POWER = 3
    }

    public enum CyEOutputType
    {
        OPAMP_STANDARD_1MA,
        OPAMP_HIGH_10MA
    }

    public enum CyECompensationType
    {
        HighSpeed = 1,
        Balanced = 2,
        HighStability = 3
    }
    #endregion

    public class CyParameters
    {
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
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

        public CyEModeType Mode
        {
            get
            {
                return GetValue<CyEModeType>(CyParamName.MODE);
            }
            set
            {
                SetValue(CyParamName.MODE, value);
            }
        }

        public CyEPowerType Power
        {
            get
            {
                return GetValue<CyEPowerType>(CyParamName.POWER);
            }
            set
            {
                SetValue(CyParamName.POWER, value);
            }
        }

        public CyEOutputType OutputCurrent
        {
            get
            {
                return GetValue<CyEOutputType>(CyParamName.OUTPUT_CURRENT);
            }
            set
            {
                SetValue(CyParamName.OUTPUT_CURRENT, value);
            }
        }

        public CyECompensationType Compensation
        {
            get
            {
                return GetValue<CyECompensationType>(CyParamName.COMPENSATION);
            }
            set
            {
                SetValue(CyParamName.COMPENSATION, value);
            }
        }

        public bool DeepSleep
        {
            get { return GetValue<bool>(CyParamName.P_DEEPSLEEP); }
            set { SetValue(CyParamName.P_DEEPSLEEP, value); }
        }

        public bool IsCTBmIPV0
        {
            get { return InstQuery.DeviceQuery.GetFeatureVersion("M0S8_CTBM") == 0; }
        }

        public bool IpPass4bPresent
        {
            get
            {
                return InstQuery.DeviceQuery.GetFeatureCount("m0s8pass4b") > 0;
            }
        }
        #endregion

        #region Getting parameters
        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null) return default(T);
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }
        #endregion

        #region Setting parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_instEdit != null && m_globalEditMode)
            {
                string valueToSet = (value == null) ? String.Empty : value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }
        #endregion
    }
}
