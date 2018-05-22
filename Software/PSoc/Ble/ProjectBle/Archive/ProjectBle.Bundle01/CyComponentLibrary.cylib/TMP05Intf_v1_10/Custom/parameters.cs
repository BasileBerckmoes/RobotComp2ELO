/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace TMP05Intf_v1_10
{
    #region Component Parameters Names
    public class CyParamName
    {
        public const string CONTINUOUS_MODE = "ContinuousMode";
        public const string NUM_SENSORS = "NumSensors";
    }
    #endregion

    public class CyParameters
    {
        public const double CLOCK_FREQ_MIN = 100;
        public const double CLOCK_FREQ_MAX = 500;
        public static byte[] NumSensorsValues = new byte[] { 1, 2, 3, 4 };

        public ICyInstQuery_v1 m_inst;
        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        public bool m_globalEditMode = false;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;
        }
        #endregion

        #region Class properties
        public bool? ContinuousMode
        {
            get { return GetValue<bool>(CyParamName.CONTINUOUS_MODE); }
            set { SetValue(CyParamName.CONTINUOUS_MODE, value); }
        }

        public byte? NumSensors
        {
            get { return GetValue<byte>(CyParamName.NUM_SENSORS); }
            set { SetValue(CyParamName.NUM_SENSORS, value); }
        }
        #endregion

        #region Getting Parameters
        private Nullable<T> GetValue<T>(string paramName) where T : struct
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return null;
            }
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
            {
                if ((m_inst is ICyInstEdit_v1) == false) return;

                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet.ToString()))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
        }
        #endregion
    }
}
