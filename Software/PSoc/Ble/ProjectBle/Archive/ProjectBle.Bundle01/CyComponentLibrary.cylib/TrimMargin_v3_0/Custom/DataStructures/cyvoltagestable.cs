/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;

namespace TrimMargin_v3_0.DataStructures
{
    [Serializable]
    public class CyVoltagesTable : ICyIntTable
    {
        public List<CyVoltagesTableRow> m_voltagesTable;

        public CyVoltagesTable() { }

        public void CreateTable(int count)
        {
            m_voltagesTable = new List<CyVoltagesTableRow>();
            for (int i = 0; i < count; i++)
            {
                CyVoltagesTableRow row = CyVoltagesTableRow.CreateDefaultRow();
                m_voltagesTable.Add(row);

                row.m_converterName = String.Format("Converter {0}", i + 1);
                row.MarginLow = row.m_nominalVoltage * 0.9;
                row.MarginHigh = row.m_nominalVoltage * 1.1;
            }
        }

        public void MigrateFrom_v1_20()
        {
            for (int i = 0; i < this.m_voltagesTable.Count; i++)
            {
                CyVoltagesTableRow row = this.m_voltagesTable[i];
                if (row.m_startupVoltage == null)
                {
                    row.m_startupVoltage = row.m_nominalVoltage;
                }
            }
        }
    }
}