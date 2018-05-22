/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;

namespace SMBusSlave_v5_20
{
    public interface ICyTable
    {
        void InitializeTable(int count);
    }

    public interface ICyRow
    {
    }

    [Serializable]
    public class CyPMBusTableRow : ICyRow
    {
        public byte m_code;
        public bool m_enable;
        public CyEFormatType m_format;
        private byte? m_size;
        public bool m_paged;

        [XmlIgnore]
        public bool m_specific;

        private CyEReadWriteConfigType m_readConfig;
        private CyEReadWriteConfigType m_writeConfig;

        public string Name
        {
            get
            {
                return CyCmdData.GetSpecDataByCode(m_code).m_cmdName;
            }
        }

        public CyECmdType Type
        {
            get
            {
                return CyCmdData.GetSpecDataByCode(m_code).m_type;
            }
        }

        public byte? Size
        {
            get
            {
                CyCommand cmd = new CyCommand();
                cmd = CyCmdData.GetSpecDataByCode(m_code);

                if (cmd.m_sizeUnlocked)
                {
                    return this.m_size;
                }
                else
                {
                    return cmd.m_size;
                }
            }
            set { this.m_size = value; }
        }

        [XmlElement("m_readConfig")]
        public CyEReadWriteConfigType ReadConfig
        {
            get
            {
                CyCommand cmd = new CyCommand();
                cmd = CyCmdData.GetSpecDataByCode(m_code);

                //For this group should be constant values
                if (cmd.m_cmdGroup == CyECmdGroup.GROUP7)
                    return CyEReadWriteConfigType.Auto;

                return m_readConfig;
            }
            set { m_readConfig = value; }
        }

        [XmlElement("m_writeConfig")]
        public CyEReadWriteConfigType WriteConfig
        {
            get
            {
                CyCommand cmd = new CyCommand();
                cmd = CyCmdData.GetSpecDataByCode(m_code);

                //For the QUERY command should be constant values
                if (cmd.m_cmdName == CyCustomTable.QUERY)
                    return CyEReadWriteConfigType.None;
                return m_writeConfig;
            }
            set { m_writeConfig = value; }
        }

        public CyPMBusTableRow() { }

        public void AssignValues(CyPMBusTableRow el)
        {
            m_enable = el.m_enable;
            m_format = el.m_format;
            m_paged = el.m_paged;
            m_readConfig = el.m_readConfig;
            m_writeConfig = el.m_writeConfig;
            m_size = el.Size;
        }

        public static CyPMBusTableRow CreateDefaultRow(int index)
        {
            CyPMBusTableRow row = new CyPMBusTableRow();
            row.m_code = CyCmdData.PMBusCmdList[index].m_cmdCode;
            // Commands are disabled by default except PAGE and QUERY
            row.m_enable = CyCustomTable.IsCmdPageOrQuery(CyCmdData.PMBusCmdList[index].m_cmdName);
            row.m_format = CyEFormatType.NonNumeric;
            row.m_size = CyCmdData.PMBusCmdList[index].m_size;
            row.m_paged = false;
            row.m_specific = CyCmdData.PMBusCmdList[index].m_specific;

            switch (CyCmdData.PMBusCmdList[index].m_cmdGroup)
            {
                case CyECmdGroup.GROUP0:
                    row.m_writeConfig = CyEReadWriteConfigType.Auto;
                    row.m_readConfig = CyEReadWriteConfigType.None;
                    break;
                case CyECmdGroup.GROUP1:
                    row.m_writeConfig = CyEReadWriteConfigType.Auto;
                    row.m_readConfig = CyEReadWriteConfigType.Auto;
                    break;
                case CyECmdGroup.GROUP2:
                    row.m_writeConfig = CyEReadWriteConfigType.Manual;
                    row.m_readConfig = CyEReadWriteConfigType.None;
                    break;
                case CyECmdGroup.GROUP3:
                    row.m_writeConfig = CyEReadWriteConfigType.None;
                    row.m_readConfig = CyEReadWriteConfigType.Auto;
                    break;
                case CyECmdGroup.GROUP4:
                    row.m_writeConfig = CyEReadWriteConfigType.Auto;
                    row.m_readConfig = CyEReadWriteConfigType.Manual;
                    break;
                case CyECmdGroup.GROUP5:
                    row.m_writeConfig = CyEReadWriteConfigType.None;
                    row.m_readConfig = CyEReadWriteConfigType.Manual;
                    break;
                case CyECmdGroup.GROUP6:
                    row.m_writeConfig = CyEReadWriteConfigType.Auto;
                    row.m_readConfig = CyEReadWriteConfigType.Auto;
                    break;
                //For this group default values are handled in corrended properties.
                case CyECmdGroup.GROUP7:
                    row.m_writeConfig = CyEReadWriteConfigType.None;
                    row.m_readConfig = CyEReadWriteConfigType.Auto;
                    break;
                default:
                    break;
            }

            return row;
        }
    }

    [Serializable]
    public class CyPMBusTable : ICyTable
    {
        public const string SMBALERT_MASK = "SMBALERT_MASK";

        public List<CyPMBusTableRow> m_pmBusTable;

        public CyPMBusTable() { }

        public void InitializeTable(int count)
        {
            m_pmBusTable = new List<CyPMBusTableRow>();
            for (int i = 0; i < count; i++)
            {
                m_pmBusTable.Add(CyPMBusTableRow.CreateDefaultRow(i));
            }
        }
    }
}
