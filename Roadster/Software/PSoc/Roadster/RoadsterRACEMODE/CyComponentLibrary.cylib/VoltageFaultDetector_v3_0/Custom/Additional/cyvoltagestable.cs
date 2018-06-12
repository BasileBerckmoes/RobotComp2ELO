/*******************************************************************************
* Copyright 2012 - 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Reflection;
using System.Xml.Serialization;

namespace VoltageFaultDetector_v3_0
{
    public interface ICyTable
    {
        void InitializeTable(int count);
    }

    [Serializable]
    public class CyVoltagesTableRow
    {
        private const string PREFIX = "V";
        public const int COL_COUNT = 8;
        public const int UV_FAULT_ACTUAL_THRESHOLD_TABLE_INDEX = 4;
        public const int OV_FAULT_ACTUAL_THRESHOLD_TABLE_INDEX = 6;

        private string m_voltageName;
        private double? m_nominalVoltage;
        private double? m_uvFaultThreshold;
        private double? m_uvFaultActualThreshold;
        private double? m_ovFaultThreshold;
        private double? m_ovFaultActualThreshold;
        private double? m_inputScalingFactor;

        [XmlElement("m_voltageName")]
        public string VoltageName
        {
            get { return m_voltageName; }
            set { m_voltageName = value; }
        }


        [XmlElement("m_nominalVoltage")]
        public double? NominalVoltage
        {
            get { return m_nominalVoltage; }
            set { m_nominalVoltage = value; }
        }

        [XmlElement("m_uvFaultThreshold")]
        public double? UvFaultThreshold
        {
            get { return m_uvFaultThreshold; }
            set { m_uvFaultThreshold = value; }
        }

        [XmlElement("m_uvFaultActualThreshold")]
        public double? UvFaultActualThreshold
        {
            get { return m_uvFaultActualThreshold; }
            set { m_uvFaultActualThreshold = value; }
        }

        [XmlElement("m_ovFaultThreshold")]
        public double? OvFaultThreshold
        {
            get { return m_ovFaultThreshold; }
            set { m_ovFaultThreshold = value; }
        }

        [XmlElement("m_ovFaultActualThreshold")]
        public double? OvFaultActualThreshold
        {
            get { return m_ovFaultActualThreshold; }
            set { m_ovFaultActualThreshold = value; }
        }

        [XmlElement("m_inputScalingFactor")]
        public double? InputScalingFactor
        {
            get { return m_inputScalingFactor; }
            set { m_inputScalingFactor = value; }
        }

        public CyVoltagesTableRow() 
        {
            this.m_voltageName = string.Empty;
        }

        public static CyVoltagesTableRow CreateDefaultRow(int index)
        {
            CyVoltagesTableRow row = new CyVoltagesTableRow();
            row.m_voltageName = "";
            row.m_nominalVoltage = null;
            row.m_uvFaultThreshold = null;
            row.m_ovFaultActualThreshold = null;
            row.m_ovFaultThreshold = null;            
            row.m_uvFaultActualThreshold = null;
            row.m_inputScalingFactor = 1;

            return row;
        }

        public static string GetVoltageIndexStr(int i)
        {
            return PREFIX + i.ToString();
        }
    }

    [Serializable]
    public class CyVoltagesTable : ICyTable
    {
        public List<CyVoltagesTableRow> m_voltagesTable;

        public CyVoltagesTable() { }

        public void InitializeTable(int count)
        {
            m_voltagesTable = new List<CyVoltagesTableRow>();
            for (int i = 0; i < count; i++)
            {
                m_voltagesTable.Add(CyVoltagesTableRow.CreateDefaultRow(i+1));
            }
            for (int i = 0; i < m_voltagesTable.Count; i++)
            {
                m_voltagesTable[i].NominalVoltage = 0.05;
                m_voltagesTable[i].UvFaultThreshold = 0.05;
                m_voltagesTable[i].UvFaultActualThreshold = 0.05;
                m_voltagesTable[i].OvFaultThreshold = 0.05;                
                m_voltagesTable[i].OvFaultActualThreshold = 0.05;
            }
        }
    }
}
