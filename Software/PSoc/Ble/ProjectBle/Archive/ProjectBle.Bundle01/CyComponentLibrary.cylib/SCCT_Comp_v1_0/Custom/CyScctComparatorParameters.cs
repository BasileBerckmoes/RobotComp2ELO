/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCCT_Comp_v1_0 
{
    #region Component Parameters Names
    public class CyParamName
    {
        public const string POLARITY = "Polarity";
        public const string SYNC = "Sync";
    }
    #endregion

    #region Parameters Enums 
    //General Tab
    public enum CyEPolarity { Non_Inverting=0, Inverting=1 }
    public enum CyESync { Bypass=0, Normal=1 }
    #endregion

    public class CyScctCompParameters
    {
        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        public bool m_globalEditMode = false;
        public ICyInstEdit_v1 m_inst;

        public CyScctCompParameters(ICyInstEdit_v1 inst)
        {
            m_inst = inst;
        }

        #region Class properties
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }
        public CyEPolarity Polarity
        {
            get { return GetValue<CyEPolarity>(CyParamName.POLARITY); }
            set { SetValue(CyParamName.POLARITY, value); }
        }

        public CyESync Sync
        {
            get { return GetValue<CyESync>(CyParamName.SYNC); }
            set { SetValue(CyParamName.SYNC, value); }
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_inst != null && value != null)
            {
                if (m_globalEditMode)
                {
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if (m_inst.SetParamExpr(paramName, valueToSet))
                    {
                        m_inst.CommitParamExprs();
                    }
                }
            }
            else Debug.Assert(false);
        }
        #endregion

    }
}
