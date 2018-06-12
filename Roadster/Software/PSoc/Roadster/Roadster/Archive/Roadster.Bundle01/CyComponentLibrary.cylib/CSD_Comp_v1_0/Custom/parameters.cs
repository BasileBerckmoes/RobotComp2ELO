/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace CSD_Comp_v1_0
{
    #region Symbol parameters names

    internal static class CyParamNames
    {
        internal const string SPEED = "Speed";
    }

    #endregion

    #region Enumeration(s)

    public enum CyECompSpeedType { SLOW_SPEED, FAST_SPEED }

    #endregion

    public class CyParameters
    {
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        // Indicator whether allow setting parameters.
        // Parameters cannot be set when the flag is equal to false. On customizer load, this parameter equals
        // to false, what means that controls event hadlers will not overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        #region Constructor(s)

        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        #endregion

        #region Properties

        // Common properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        // Properties for parameters
        public CyECompSpeedType Speed
        {
            get { return GetValue<CyECompSpeedType>(CyParamNames.SPEED); }
            set { SetValue(CyParamNames.SPEED, value); }
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
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }

        #endregion
    }
}
