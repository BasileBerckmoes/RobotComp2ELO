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
    [Serializable]
    public class CyCustomTableRow : ICyRow
    {
        public bool m_enable;
        public string m_name;
        public byte? m_code;
        public CyECmdType m_type;
        public CyEFormatType m_format;
        public byte? m_size;
        public bool m_paged;
        public byte? m_numPages;

        [XmlIgnore]
        public bool m_specific;

        public CyEReadWriteConfigType m_readConfig;
        public CyEReadWriteConfigType m_writeConfig;

        public CyCustomTableRow() { }

        public CyCustomTableRow(CyPMBusTableRow row)
        {
            this.m_enable = row.m_enable;
            this.m_name = row.Name;
            this.m_code = row.m_code;
            this.m_type = row.Type;
            this.m_format = row.m_format;
            this.m_paged = row.m_paged;
            this.m_size = row.Size;
            this.m_readConfig = row.ReadConfig;
            this.m_writeConfig = row.WriteConfig;
            this.m_specific = row.m_specific;
        }

        public CyCustomTableRow(CyCustomTableRow row)
        {
            this.m_enable = row.m_enable;
            this.m_name = row.m_name;
            this.m_code = row.m_code;
            this.m_type = row.m_type;
            this.m_format = row.m_format;
            this.m_size = row.m_size;
            this.m_paged = row.m_paged;
            this.m_numPages = row.m_numPages;
            this.m_specific = row.m_specific;
            this.m_readConfig = row.m_readConfig;
            this.m_writeConfig = row.m_writeConfig;
        }

        public CyCustomTableRow(bool enable, string name, byte? code, CyECmdType type, CyEFormatType format, 
            byte? size, bool paged, byte? numPages, bool specific, 
            CyEReadWriteConfigType readConfig, CyEReadWriteConfigType writeConfig)
        {
            this.m_enable = enable;
            this.m_name = name;
            this.m_code = code;
            this.m_type = type;
            this.m_format = format;
            this.m_size = size;
            this.m_paged = paged;
            this.m_numPages = numPages;
            this.m_specific = specific;
            this.m_readConfig = readConfig;
            this.m_writeConfig = writeConfig;
        }

        public static CyCustomTableRow CreateDefaultRow(int index)
        {
            CyCustomTableRow row = new CyCustomTableRow();
            row.m_enable = true;
            row.m_name = string.Empty;
            row.m_code = null;
            row.m_type = CyECmdType.ReadWriteByte;
            row.m_format = CyEFormatType.NonNumeric;
            row.m_size = 1;
            row.m_paged = false;
            row.m_numPages = null;
            row.m_specific = false;
            row.m_readConfig = CyEReadWriteConfigType.Manual;
            row.m_writeConfig = CyEReadWriteConfigType.Manual;

            return row;
        }
    }

    [Serializable]
    public class CyCustomTable : ICyTable
    {
        public const string BOOTLOAD_WRITE = "BOOTLOAD_WRITE";
        public const string BOOTLOAD_READ = "BOOTLOAD_READ";
        public const string PAGE = "PAGE";
        public const string QUERY = "QUERY";

        public const int PAGE_INDEX = 0;
        public const int QUERY_INDEX = 1;

        private const byte BOOTLOAD_WRITE_CMD_DEFAULT_CODE = 0xFC;
        private const byte BOOTLOAD_READ_CMD_DEFAULT_CODE = 0xFD;
        private const byte PAGE_CMD_DEFAULT_CODE = 0x00;
        private const byte QUERY_CMD_DEFAULT_CODE = 0x1A;

        public List<CyCustomTableRow> m_customTable;

        public CyCustomTable() { }

        public void InitializeTable(int count)
        {
            m_customTable = new List<CyCustomTableRow>();
            for (int i = 0; i < count; i++)
            {
                m_customTable.Add(CyCustomTableRow.CreateDefaultRow(i));
            }

            m_customTable.InsertRange(0, CreateReservedRows());
        }

        public static void SetReservedRowsFlag(List<CyCustomTableRow> customTable)
        {
            if (customTable != null)
                for (int i = 0; i < customTable.Count; i++)
                    if (IsCmdSpecific(customTable[i].m_name))
                        customTable[i].m_specific = true;
        }

        public static List<CyCustomTableRow> CreateReservedRows()
        {
            List<CyCustomTableRow> reservedRows = new List<CyCustomTableRow>();

            reservedRows.Add(new CyCustomTableRow(true, BOOTLOAD_WRITE, BOOTLOAD_WRITE_CMD_DEFAULT_CODE,
                CyECmdType.ReadWriteBlock, CyEFormatType.NonNumeric, CyParamRange.BOOTLOADER_SIZE, false, null, true,
                CyEReadWriteConfigType.None, CyEReadWriteConfigType.Auto));

            reservedRows.Add(new CyCustomTableRow(true, BOOTLOAD_READ, BOOTLOAD_READ_CMD_DEFAULT_CODE,
                CyECmdType.ReadWriteBlock, CyEFormatType.NonNumeric, CyParamRange.BOOTLOADER_SIZE, false, null, true,
                CyEReadWriteConfigType.Auto, CyEReadWriteConfigType.None));

            return reservedRows;
        }

        public static CyCustomTableRow GetDefaultPageRow()
        {
            return new CyCustomTableRow(true, PAGE, PAGE_CMD_DEFAULT_CODE, CyECmdType.ReadWriteByte,
                CyEFormatType.NonNumeric, 1, false, null, true, CyEReadWriteConfigType.Auto, 
                CyEReadWriteConfigType.Auto);
        }

        public static CyCustomTableRow GetDefaultQueryRow()
        {
            return new CyCustomTableRow(true, QUERY, QUERY_CMD_DEFAULT_CODE, CyECmdType.BlockProcessCall,
                CyEFormatType.NonNumeric, 1, false, null, true, CyEReadWriteConfigType.Auto, 
                CyEReadWriteConfigType.None);
        }

        public static bool IsCmdSpecific(string name)
        {
            return (name == PAGE || name == QUERY ||
                name == BOOTLOAD_READ || name == BOOTLOAD_WRITE);
        }

        public static bool IsCmdPageOrQuery(string name)
        {
            return (name == PAGE || name == QUERY);
        }

        public static bool IsCmdBootloader(string name)
        {
            return (name == BOOTLOAD_WRITE || name == BOOTLOAD_READ);
        }

        public static string GetString()
        {
            return Convert.ToString(new CyCustomTable());
        }
    }
}
