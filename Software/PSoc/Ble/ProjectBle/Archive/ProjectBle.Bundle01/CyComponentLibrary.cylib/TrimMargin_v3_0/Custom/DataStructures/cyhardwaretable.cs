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
    public class CyHardwareTable : ICyIntTable
    {
        public List<CyHardwareTableRow> m_hardwareTable;

        public CyHardwareTable() { }

        public void CreateTable(int count)
        {
            m_hardwareTable = new List<CyHardwareTableRow>();
            for (int i = 0; i < count; i++)
            {
                CyHardwareTableRow row = CyHardwareTableRow.CreateDefaultRow();
                m_hardwareTable.Add(row);
            }
        }

        public void MigrateFrom_v1_20()
        {
            for (int i = 0; i < this.m_hardwareTable.Count; i++)
            {
                CyHardwareTableRow row = this.m_hardwareTable[i];
                if (row.m_c1 == null)
                {
                    row.m_c1 = CyConstants.C1_DEFAULT;
                }
            }
        }
    }
}