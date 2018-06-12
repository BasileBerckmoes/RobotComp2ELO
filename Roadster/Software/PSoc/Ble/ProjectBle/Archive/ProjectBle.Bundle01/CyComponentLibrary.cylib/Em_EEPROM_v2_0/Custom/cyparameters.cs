/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;

namespace Em_EEPROM_v2_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        public const string ACTUAL_SIZE = "ActualSize";
    }
    #endregion

    public class CyParameters
    {
        #region Private fields
        private readonly ICyInstQuery_v1 m_instQuery;
        #endregion

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 instQuery)
        {
            m_instQuery = instQuery;
        }
        #endregion

        #region Properties
        /// <summary>
        /// Indicates whether it is allowed to edit the parameters.
        /// </summary>
        public bool EditMode { get; set; }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        #region Basic tab parameters
        public int ActualSize
        {
            get { return GetValue<UInt16>(CyParamNames.ACTUAL_SIZE); }
        }
        #endregion
        #endregion

        #region Getting Parameters
        public T GetValue<T>(string paramName)
        {
            return CyParamUtils.GetValue<T>(m_instQuery, paramName);
        }
        #endregion
    }
}
