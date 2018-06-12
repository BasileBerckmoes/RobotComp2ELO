/*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit;

namespace LUT_v1_60
{
    #region Component Parameters Names

    public class CyParamNames
    {
        public const string INSTANCE_NAME = "INSTANCE_NAME";
        public const string NUM_INPUTS = "NumInputs";
        public const string NUM_OUTPUTS = "NumOutputs";
        public const string REGISTER_OUTPUTS = "RegisterOutputs";
        public const string BIT_FIELD = "BitField";
        public const string IN_NAME = "in{0}Name";
        public const string OUT_NAME = "out{0}Name";
    }
    #endregion

    class CyParameters
    {
        #region Fields
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;

        public CyLutTable LutTable;
        #endregion

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;

            LoadLutTable();
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }
        #endregion

        #region Properties
        //
        // Common properties
        //
        /// <summary>
        /// Indicates whether it is allowed to edit the parameters.
        /// During first getting of parameters this variable is false, what means that assigning
        /// values to form controls will not immediately overwrite parameters with the same values.
        /// </summary>
        public bool GlobalEditMode { get; set; }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        //
        // Parameters from the symbol
        //
        public int NumInputs
        {
            get { return GetValue<int>(CyParamNames.NUM_INPUTS); }
            set { SetValue(CyParamNames.NUM_INPUTS, value); }
        }

        public int NumOutputs
        {
            get { return GetValue<int>(CyParamNames.NUM_OUTPUTS); }
            set { SetValue(CyParamNames.NUM_OUTPUTS, value); }
        }

        public bool RegisterOutputs
        {
            get { return GetValue<bool>(CyParamNames.REGISTER_OUTPUTS); }
            set { SetValue(CyParamNames.REGISTER_OUTPUTS, value); }
        }

        public string BitField
        {
            get { return GetValue<string>(CyParamNames.BIT_FIELD); }
            set { SetValue(CyParamNames.BIT_FIELD, value); }
        }

        public string GetInName(int index)
        {
            return GetValue<string>(String.Format(CyParamNames.IN_NAME, index)); 
        }
        public void SetInName(int index, string value)
        {
            SetValue(String.Format(CyParamNames.IN_NAME, index), value);
        }

        public string GetOutName(int index)
        {
            return GetValue<string>(String.Format(CyParamNames.OUT_NAME, index));
        }
        public void SetOutName(int index, string value)
        {
            SetValue(String.Format(CyParamNames.OUT_NAME, index), value);
        }

        #endregion

        #region Getting / Setting Parameters
        public T GetValue<T>(string paramName)
        {
            return CyParamUtils.GetValue<T>(m_instQuery, paramName);
        }

        public void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode && m_instEdit != null)
            {
                CyParamUtils.SetValue(m_instEdit, paramName, value);
            }
        }

        public void LoadLutTable()
        {
            LutTable = new CyLutTable(NumInputs, NumOutputs, BitField);
        }

        public void SaveLutTable()
        {
            BitField = LutTable.GetOutputString();
        }
        #endregion
    }

    
}
