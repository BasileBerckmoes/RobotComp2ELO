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
using System.Collections.Generic;

namespace PVref_P4_v1_0
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string REF_SOURCE = "RefSource";
        public const string SEL_OUTPUT_VOLTAGE = "SelOutputVoltage";
    }
    #endregion

    #region Component Enums
    public enum CyEnumRefSourceType
    {
        [Description("Bandgap")]
        Bandgap = 0,
        [Description("Vdda")]
        Vdda = 1
    }
    #endregion Component Enums

    public class CyParameters
    {
        #region Class Consts

        public const int BANDGAP_KEY = 0;
        public const int MAX_DIVIDER_VALUE = 16;
        public const double SRSSLT_VBGR_VALUE = 1.2;

        public const string REFSOURCE_BANDGAP_NAME = "Bandgap";
        public const string REFSOURCE_VDDA_NAME = "Vdda";
        public const string VREF_NAME = "Vref";
        #endregion Class Consts

        #region Class members
        private readonly double m_bandgap = SRSSLT_VBGR_VALUE;

        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private ICyTabbedParamEditor m_editor;

        // When parameters are first obtained, this variable is false, which means that assigned
        // values to form the controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        #endregion Class members

        #region Constructor(s)

        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;

            try
            {
                IEnumerable<System.Tuple<int, string>> tapPointsList = instQuery.DesignQuery.
                    GetProgrammableReferenceTapPoints(BANDGAP_KEY);

                foreach (System.Tuple<int, string> tap in tapPointsList)
                {
                    // remove 'V'
                    string sTapValue = tap.Item2.Substring(0, tap.Item2.Length - 1);

                    // Bandgap equals last tap point value
                    m_bandgap = Convert.ToDouble(sTapValue);
                }
            }
            catch
            {
                Debug.Assert(false);
                m_bandgap = SRSSLT_VBGR_VALUE;
            }
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

        public double Vdda
        {
            get { return m_instQuery.VoltageQuery.VDDA; }
        }

        public double Bandgap
        {
            get { return m_bandgap; }
        } 

        public CyEnumRefSourceType RefSource
        {
            get { return GetValue<CyEnumRefSourceType>(CyParamNames.REF_SOURCE); }
            set { SetValue(CyParamNames.REF_SOURCE, value); }
        }

        public byte SelOutputVoltage
        {
            get { return GetValue<byte>(CyParamNames.SEL_OUTPUT_VOLTAGE); }
            set { SetValue(CyParamNames.SEL_OUTPUT_VOLTAGE, value); }
        }
        #endregion Class properties

        #region Public Methods

        public double GetVref()
        {
            return GetSelectedRefSourceValue() / CyParameters.MAX_DIVIDER_VALUE * SelOutputVoltage;
        }

        public string GetSelectedRefSourceName()
        {
            string refSourceName = string.Empty;

            if (RefSource == CyEnumRefSourceType.Bandgap)
            {
                refSourceName = CyParameters.REFSOURCE_BANDGAP_NAME;
            }
            else if (RefSource == CyEnumRefSourceType.Vdda)
            {
                refSourceName = CyParameters.REFSOURCE_VDDA_NAME;
            }
            else
            {
                Debug.Assert(false);
            }

            return refSourceName;
        }

        public double GetSelectedRefSourceValue()
        {
            double refSourceValue = 0;

            if (RefSource == CyEnumRefSourceType.Bandgap)
            {
                refSourceValue = Bandgap;
            }
            else if (RefSource == CyEnumRefSourceType.Vdda)
            {
                refSourceValue = Vdda;
            }
            else
            {
                Debug.Assert(false);
            }

            return refSourceValue;
        }

        #endregion Private Methods

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