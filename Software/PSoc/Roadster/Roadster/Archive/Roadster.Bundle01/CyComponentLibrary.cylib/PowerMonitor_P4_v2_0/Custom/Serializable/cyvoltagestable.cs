/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Reflection;

namespace PowerMonitor_P4_v2_0
{
    public interface ICyTable
    {
        void InitializeTable(int count);
    }

    [Serializable]
    public class CyVoltagesTableRow
    {
        public const string PREFIX = "V";
        public const int COL_COUNT = 9;        
        public string m_converterName;
        public double? m_nominalOutputVoltage = 1.2;
        public double? m_minAcqTime_ns = CyParamRanges.DEFAULT_SETTLING_TIME_NS;
        public double? m_uvFaultTreshold = 0.8;
        public double? m_uvWarningTreshold = 1.0;
        public double? m_ovFaultTreshold = 1.5;
        public double? m_ovWarningTreshold = 1.3;
        public double? m_inputScalingFactor = 1;
        public static string GetConverterNumber(int index)
        {
            return PREFIX + (index + 1).ToString();
        }

        public CyVoltagesTableRow()
        {
            this.m_converterName = String.Empty;
        }

        public CyVoltagesTableRow(int converterNumber)
        {
            this.m_converterName = String.Format("Converter {0}", converterNumber);
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
            for (int i = 1; i <= count; i++)
            {
                CyVoltagesTableRow row = new CyVoltagesTableRow();
                row.m_converterName = "Converter " + i.ToString();
                row.m_nominalOutputVoltage = 1.2;
                row.m_uvFaultTreshold = 0.8;
                row.m_ovFaultTreshold = 1.5;
                row.m_uvWarningTreshold = 1.0;
                row.m_ovWarningTreshold = 1.3;
                row.m_inputScalingFactor = 1;
                row.m_minAcqTime_ns = CyParamRanges.DEFAULT_SETTLING_TIME_NS;
                m_voltagesTable.Add(row);
            }
        }
    }
}
