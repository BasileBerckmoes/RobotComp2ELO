/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Xml.Serialization;

namespace TrimMargin_v3_0.DataStructures
{
    [Serializable]
    [XmlType("CyColumnsVisibility")]
    public struct CyColumnsVisibility
    {
        #region Private fields
        private string m_columnName;
        private bool m_visible;
        #endregion

        #region Constructor(s)
        public CyColumnsVisibility(string colname, bool visible)
        {
            m_columnName = colname;
            m_visible = visible;
        }
        #endregion

        #region Properties
        [XmlElement("ColName")]
        public string ColumnName
        {
            get { return m_columnName; }
            set { m_columnName = value; }
        }

        [XmlElement("Visible")]
        public bool Visible
        {
            get { return m_visible; }
            set { m_visible = value; }
        }
        #endregion
    }
}