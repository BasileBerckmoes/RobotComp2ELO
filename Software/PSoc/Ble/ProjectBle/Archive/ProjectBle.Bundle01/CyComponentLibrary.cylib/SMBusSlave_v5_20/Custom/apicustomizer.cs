/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SMBusSlave_v5_20
{
    public partial class CyCustomizer : ICyAPICustomize_v1
    {
        #region ICyAPICustomize_v1 Members

        #region Defining constants
        private const string UINT8_TYPE = "uint8";
        private const string UINT16_TYPE = "uint16";
        private const string SPACE = " ";
        private const string TAB = "    ";
        private const string TAB_2 = TAB + TAB;
        private const string TAB_3 = TAB + TAB + TAB;
        private const string LOGIC_OR = " | ";
        private const string UINT8_TYPE_SPACE = UINT8_TYPE + SPACE;
        private const string UINT16_TYPE_SPACE = UINT16_TYPE + SPACE;
        private const string STRUCT_NAME = "REGS";
        private static readonly string NEW_LINE = Environment.NewLine;
        private static readonly string SLASH_NEW_LINE = " \\" + Environment.NewLine;
        #endregion

        #region Private types
        private enum CyEFieldType
        {
            UInt8Type,
            UInt16Type
        }

        private struct CyStructField
        {
            public CyEFieldType m_fieldType;
            public int m_dim1;
            public int m_dim2;
        }
        #endregion

        #region Declaring private variables
        private string m_instName;
        // These arrays store information about structure elements size. Arrays are used to ensure 
        // that initializing is consistent with the sizes.
        // If element is not array [index, 0] && [index, 1] equal to 0
        // If element is one dimentional array [index, 0] equals to its size && [index, 1] equal to 0
        // If element is two dimentional array [index, 0] && [index, 1] equal to the array size respectively
        private CyStructField[] m_pmBusStructFields;
        private CyStructField[] m_smBusStructFields;
        private enum CyArrayType { NotArray, OneDimArray, TwoDimArray };

        #endregion

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
                IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            List<CyAPICustomizer> outputCustomizers = new List<CyAPICustomizer>(customizers);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;

            m_parameters = new CyParameters(query);
            m_instName = m_parameters.InstanceName;
            m_pmBusStructFields = new CyStructField[m_parameters.PmBusTable.Count];
            m_smBusStructFields = new CyStructField[m_parameters.CustomTable.Count];

            FilterApi(outputCustomizers);

            List<CyArrayType> pmBusGenerateAsArray = new List<CyArrayType>();
            List<CyArrayType> customGenerateAsArray = new List<CyArrayType>();
            List<CyArrayType> tempArray = new List<CyArrayType>();

            // Generate structure
            StringBuilder regStructure = new StringBuilder();
            if (query.DeviceQuery.IsPSoC3)
            {
                regStructure.AppendLine("typedef struct");
            }
            else
            {
                regStructure.AppendLine("#if defined (__GNUC__)");
                regStructure.AppendLine("    typedef struct __attribute__ ((packed))");
                regStructure.AppendLine("#else");
                regStructure.AppendLine("    typedef __packed struct");
                regStructure.AppendLine("#endif /* (__GNUC__) */");
            }

            regStructure.AppendLine("{");
            regStructure.AppendLine("    uint32 SMBUS_REGS_SIG;");

            string varStructure = string.Empty;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    string structureField = GetStructureField(null, m_parameters.PagedCommands,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].m_paged, m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Type, i, ref pmBusGenerateAsArray, ref m_pmBusStructFields);

                    string varStructureField = GetStructureField(m_instName, m_parameters.PagedCommands,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].m_paged, m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Type, i, ref tempArray, ref m_pmBusStructFields);

                    if (CyCustomTable.IsCmdBootloader(m_parameters.PmBusTable[i].Name))
                        continue;

                    regStructure.Append(structureField);
                    varStructure += varStructureField;
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                string structureField = GetStructureField(null,
                    m_parameters.CustomTable[i].m_numPages.HasValue ?
                        m_parameters.CustomTable[i].m_numPages.Value : m_parameters.PagedCommands,
                    m_parameters.CustomTable[i].m_name,
                    m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_paged,
                    m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_type,
                    i, ref customGenerateAsArray, ref m_smBusStructFields);

                string varStructureField = GetStructureField(m_instName,
                    m_parameters.CustomTable[i].m_numPages.HasValue ?
                        m_parameters.CustomTable[i].m_numPages.Value : m_parameters.PagedCommands,
                    m_parameters.CustomTable[i].m_name,
                    m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_paged,
                    m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_type,
                    i, ref tempArray, ref m_smBusStructFields);

                if (CyCustomTable.IsCmdBootloader(m_parameters.CustomTable[i].m_name) == false)
                {
                    regStructure.Append(structureField);
                    varStructure += varStructureField;
                }
            }
            regStructure.AppendLine("    uint16 FLASH_CRC;");
            regStructure.Append("} " + m_instName + "_" + STRUCT_NAME + ";");

            // Generate NUM_COMMANDS
            int numCommands = 0;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    if (m_parameters.PmBusTable[i].m_enable)
                        numCommands++;
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                if (m_parameters.CustomTable[i].m_enable)
                    numCommands++;
            }

            // Generate command codes defines
            string strCmdsDefines = string.Empty;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    if (m_parameters.PmBusTable[i].m_enable)
                        strCmdsDefines += GetCmdDefine(m_instName, m_parameters.PmBusTable[i].Name,
                            m_parameters.PmBusTable[i].m_code);
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                if (m_parameters.CustomTable[i].m_enable)
                    strCmdsDefines += GetCmdDefine(m_instName, m_parameters.CustomTable[i].m_name,
                        m_parameters.CustomTable[i].m_code);
            }

            // Generate CMD_TABLE_ENTRY array
            string strCmdTableEntryArray = "static const " + m_instName + "_CMD_TABLE_ENTRY CYCODE " + m_instName +
                "_commands[] = {" + NEW_LINE;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    string cmdPropStr = GetCmdTableEntryElement(m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].Type, m_parameters.PmBusTable[i].WriteConfig,
                        m_parameters.PmBusTable[i].ReadConfig, m_parameters.PmBusTable[i].m_paged,
                        m_parameters.PmBusTable[i].m_format, pmBusGenerateAsArray[i]);

                    strCmdTableEntryArray += cmdPropStr;
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                string cmdPropStr = GetCmdTableEntryElement(m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_name, m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_type, m_parameters.CustomTable[i].m_writeConfig,
                    m_parameters.CustomTable[i].m_readConfig, m_parameters.CustomTable[i].m_paged,
                    m_parameters.CustomTable[i].m_format, customGenerateAsArray[i]);
                strCmdTableEntryArray += cmdPropStr;
            }
            if (strCmdTableEntryArray.LastIndexOf(",") > 0)
                strCmdTableEntryArray = strCmdTableEntryArray.Remove(strCmdTableEntryArray.LastIndexOf(",")) + NEW_LINE;
            strCmdTableEntryArray += "};";

            // Generate Read/Write Handler cases
            string strWriteCases = string.Empty;
            string strReadCases = string.Empty;

            GenerateReadWriteHandlerCases(ref strWriteCases, ref strReadCases);

            // Generate NULL struct
            string strNullStructure = "#define PMBus_DEFAULT_REGISTER_STORE = {" + SLASH_NEW_LINE +
                "    /* SMBUS_REGS_SIG (Do not change!) */" + SLASH_NEW_LINE +
                TAB + "0x000055AAu,";
                     
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    if (CyCustomTable.IsCmdBootloader(m_parameters.PmBusTable[i].Name))
                        continue;

                    strNullStructure += GetNullStructureField(i, m_parameters.PagedCommands,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].m_paged, m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Type, m_pmBusStructFields);
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                if (CyCustomTable.IsCmdBootloader(m_parameters.CustomTable[i].m_name))
                    continue;

                strNullStructure += GetNullStructureField(i,
                    m_parameters.CustomTable[i].m_numPages.HasValue ?
                        m_parameters.CustomTable[i].m_numPages.Value : m_parameters.PagedCommands,
                    m_parameters.CustomTable[i].m_name, m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_paged, m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_type, m_smBusStructFields);
            }
            strNullStructure += SLASH_NEW_LINE + TAB + "/* FLASH_CRC */" + SLASH_NEW_LINE + TAB + "0x0000u" +
                SLASH_NEW_LINE + "}";

            paramDict.Add("RegsStructElements", regStructure.ToString());
            paramDict.Add("StoreComponentAllVar", varStructure);
            paramDict.Add("NullStructure", strNullStructure);
            paramDict.Add("NumCommands", CyParameters.CellConvertHex(numCommands));
            paramDict.Add("CommandsDefines", strCmdsDefines);
            paramDict.Add("CmdTableEntry", strCmdTableEntryArray);
            paramDict.Add("WriteHandlerCases", strWriteCases);
            paramDict.Add("ReadHandlerCases", strReadCases);

            for (int i = 0; i < outputCustomizers.Count; i++)
            {
                outputCustomizers[i].MacroDictionary = paramDict;
            }

            return outputCustomizers;
        }

        private void GenerateReadWriteHandlerCases(ref string writeCases, ref string readCases)
        {
            // Write handler generation
            const string WRITE_TAB_SHIFT = TAB_3;
            const string READ_TAB_SHIFT = TAB_2;
            string caseHeader = string.Empty;
            string caseFooter = TAB + "break;" + NEW_LINE + NEW_LINE;

            List<List<CyCustomTableRow>> groupedCommands = GetGroupedCommandsForSwitch();
            List<List<CyCustomTableRow>> readCommands = GetReadCommands(groupedCommands);
            List<List<CyCustomTableRow>> writeCommands = GetWriteCommands(groupedCommands);

            for (int i = 0; i < writeCommands.Count; i++)
            {
                List<CyCustomTableRow> list = new List<CyCustomTableRow>(writeCommands[i]);
                for (int j = 0; j < list.Count; j++)
                {
                    CyCustomTableRow item = list[j];
                    caseHeader = GetCaseHeader(item.m_name, String.IsNullOrEmpty(writeCases), "");
                    if (item.m_specific)
                    {
                        if (item.m_name == CyCustomTable.PAGE)
                        {
                            if (item.m_writeConfig != CyEReadWriteConfigType.Manual)
                            {
                                writeCases += caseHeader + GetWriteHandlerCaseBody_PageCmd() + caseFooter;
                            }
                        }
                        if (item.m_name == CyCustomTable.BOOTLOAD_WRITE)
                        {
                            writeCases +=
                                GetBootloaderCmdCaseHeader(item.m_name, String.IsNullOrEmpty(writeCases), false, "") +
                                GetWriteHandlerCaseBody_BootloadWriteCmd() +
                                GetBootloaderCmdCaseFooter(false, TAB);
                        }
                    }
                    else
                    {
                        switch (item.m_type)
                        {
                            case CyECmdType.ReadWriteByte:
                                writeCases = String.Concat(writeCases, caseHeader);
                                if (j == list.Count - 1)
                                    writeCases = String.Concat(writeCases, GetWriteByteCall(item));
                                break;
                            case CyECmdType.ReadWriteWord:
                                writeCases = String.Concat(writeCases, caseHeader);
                                if (j == list.Count - 1)
                                    writeCases = String.Concat(writeCases, GetWriteWordCall(item));
                                break;
                            case CyECmdType.ReadWriteBlock:
                                writeCases = String.Concat(writeCases, caseHeader);
                                if (j == list.Count - 1)
                                    writeCases = String.Concat(writeCases, GetWriteBlockCall(item));
                                break;
                            case CyECmdType.BlockProcessCall:
                                if (item.m_name == CyPMBusTable.SMBALERT_MASK)
                                {
                                    writeCases = String.Concat(writeCases, caseHeader);
                                    if (j == list.Count - 1)
                                        writeCases = String.Concat(writeCases,
                                            GetWriteHandlerCaseBody_BlockProcessCall(item));
                                }
                                break;
                            default:
                                // Do nothing
                                break;
                        }
                    }
                }
            }

            // Read handler generation
            for (int i = 0; i < readCommands.Count; i++)
            {
                List<CyCustomTableRow> list = new List<CyCustomTableRow>(readCommands[i]);
                for (int j = 0; j < list.Count; j++)
                {
                    CyCustomTableRow item = list[j];
                    caseHeader = GetCaseHeader(item.m_name, String.IsNullOrEmpty(readCases), "");
                    if (item.m_specific)
                    {
                        if (item.m_name == CyCustomTable.BOOTLOAD_READ)
                        {
                            readCases +=
                                GetBootloaderCmdCaseHeader(item.m_name, String.IsNullOrEmpty(readCases), true, "") +
                                GetReadHandlerCaseBody_BootloadReadCmd() +
                                GetBootloaderCmdCaseFooter(true, TAB);
                        }
                        if (item.m_name == CyCustomTable.QUERY)
                        {
                            readCases += caseHeader + GetReadHandlerCaseBody_QueryCmd() + caseFooter;
                        }
                        if (item.m_name == CyCustomTable.PAGE)
                        {
                            readCases += caseHeader + GetReadHandlerCaseBody_PageCmd() + caseFooter;
                        }
                    }
                    else
                    {
                        switch (item.m_type)
                        {
                            case CyECmdType.ReadWriteByte:
                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases, GetReadByteCall(item));
                                break;
                            case CyECmdType.ReadWriteWord:
                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases, GetReadWordCall(item));
                                break;
                            case CyECmdType.ReadWriteBlock:
                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases, GetReadBlockCall(item));
                                break;
                            case CyECmdType.BlockProcessCall:
                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases, GetReadBlockProcessCall(item));
                                break;
                            case CyECmdType.ProcessCall:
                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases, GetReadHandlerCaseBody_ProcessCall(item));
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            // Remove last new lines
            writeCases = RemoveLastNewLines(writeCases);
            readCases = RemoveLastNewLines(readCases);
            // Insert tabs
            writeCases = InsertTabs(writeCases, WRITE_TAB_SHIFT);
            readCases = InsertTabs(readCases, READ_TAB_SHIFT);
        }

        private bool IsNumPagesCustom(CyCustomTableRow item)
        {
            return ((item.m_paged) && (item.m_numPages.HasValue) &&
                    (item.m_numPages.Value != m_parameters.PagedCommands));
        }

        private static string RemoveLastNewLines(string text)
        {
            while (text.LastIndexOf(NEW_LINE) == text.Length - NEW_LINE.Length)
            {
                text = text.Remove(text.LastIndexOf(NEW_LINE), NEW_LINE.Length);
            }
            return text;
        }

        private static string InsertTabs(string text, string tabs)
        {
            return text.Replace(Environment.NewLine, Environment.NewLine + tabs);
        }


        private List<List<CyCustomTableRow>> GetGroupedCommandsForSwitch()
        {
            List<List<CyCustomTableRow>> groupedCommandsList = new List<List<CyCustomTableRow>>();

            // Separate arrays to paged and not paged
            List<CyCustomTableRow> pagedArrays = new List<CyCustomTableRow>();
            List<CyCustomTableRow> notPagedArrays = new List<CyCustomTableRow>();

            // Separate PMBus commands
            // Consider PMBus commands are not paged
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    notPagedArrays.Add(new CyCustomTableRow(m_parameters.PmBusTable[i]));
                }
            }

            // Separate custom commands
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                if (m_parameters.CustomTable[i].m_paged)
                {
                    pagedArrays.Add(m_parameters.CustomTable[i]);
                }
                else
                {
                    notPagedArrays.Add(m_parameters.CustomTable[i]);
                }
            }

            // Group paged commands
            while (pagedArrays.Count > 0)
            {
                List<CyCustomTableRow> tmp = new List<CyCustomTableRow>();
                for (int i = pagedArrays.Count - 1; i >= 0; i--)
                {
                    if (pagedArrays[i].m_type == pagedArrays[0].m_type &&
                        pagedArrays[i].m_paged == pagedArrays[0].m_paged &&
                        pagedArrays[i].m_numPages == pagedArrays[0].m_numPages)
                    {
                        tmp.Add(pagedArrays[i]);
                        pagedArrays.RemoveAt(i);
                    }
                }
                groupedCommandsList.Add(tmp);
            }

            // Group not paged commands
            while (notPagedArrays.Count > 0)
            {
                List<CyCustomTableRow> tmp = new List<CyCustomTableRow>();
                for (int i = notPagedArrays.Count - 1; i >= 0; i--)
                {
                    if (notPagedArrays[i].m_type == notPagedArrays[0].m_type)
                    {
                        tmp.Add(notPagedArrays[i]);
                        notPagedArrays.RemoveAt(i);
                    }
                }
                groupedCommandsList.Add(tmp);
            }

            // Find specific commands and move them to different group
            List<CyCustomTableRow> specificCommands = new List<CyCustomTableRow>();

            for (int i = groupedCommandsList.Count - 1; i >= 0; i--)
            {
                for (int j = groupedCommandsList[i].Count - 1; j >= 0; j--)
                {
                    CyCustomTableRow item = groupedCommandsList[i][j];
                    if (item.m_specific)
                    {
                        specificCommands.Add(item);
                        groupedCommandsList[i].RemoveAt(j);
                        if (groupedCommandsList[i].Count == 0)
                        {
                            groupedCommandsList.RemoveAt(i);
                        }
                    }
                }
            }
            // Insert group with specific commands at the begginning
            if (specificCommands.Count > 0)
            {
                groupedCommandsList.Insert(0, specificCommands);
            }

            //Erase disabled commands from groups
            int ii = 0;
            while (groupedCommandsList.Count > ii)
            {
                int jj = 0;
                while (groupedCommandsList[ii].Count > jj)
                {
                    if (groupedCommandsList[ii][jj].m_enable == false)
                    {
                        groupedCommandsList[ii].RemoveAt(jj);
                    }
                    else
                        jj++;
                }

                if (groupedCommandsList[ii].Count == 0)
                    groupedCommandsList.RemoveAt(ii);
                else
                    ii++;
            }

            return groupedCommandsList;
        }

        private List<List<CyCustomTableRow>> GetDeepCopy(List<List<CyCustomTableRow>> groupedCommands)
        {
            List<List<CyCustomTableRow>> copy = new List<List<CyCustomTableRow>>();
            int copyIndex = 0;
            for (int i = 0; i < groupedCommands.Count; i++)
            {
                copy.Add(new List<CyCustomTableRow>());

                for (int j = 0; j < groupedCommands[i].Count; j++)
                {
                    copy[copyIndex].Add(groupedCommands[i][j]);
                }
                copyIndex++;
            }
            return copy;
        }

        private List<List<CyCustomTableRow>> GetReadCommands(List<List<CyCustomTableRow>> groupedCommands)
        {
            List<List<CyCustomTableRow>> readCommands = GetDeepCopy(groupedCommands);
            int ii = 0;
            while (readCommands.Count > ii)
            {
                int jj = 0;
                while (readCommands[ii].Count > jj)
                {
                    if (readCommands[ii][jj].m_readConfig == CyEReadWriteConfigType.None)
                    {
                        readCommands[ii].RemoveAt(jj);
                    }
                    else
                        jj++;
                }

                if (readCommands[ii].Count == 0)
                    readCommands.RemoveAt(ii);
                else
                    ii++;
            }

            return readCommands;
        }

        private List<List<CyCustomTableRow>> GetWriteCommands(List<List<CyCustomTableRow>> groupedCommands)
        {
            List<List<CyCustomTableRow>> writeCommands = GetDeepCopy(groupedCommands);
            int ii = 0;
            while (writeCommands.Count > ii)
            {
                int jj = 0;
                while (writeCommands[ii].Count > jj)
                {
                    if ((writeCommands[ii][jj].m_writeConfig == CyEReadWriteConfigType.None) ||
                          ((writeCommands[ii][jj].m_writeConfig == CyEReadWriteConfigType.Manual) &&
                           (m_parameters.CustomTable.Contains(writeCommands[ii][jj]))))
                    {
                        writeCommands[ii].RemoveAt(jj);
                    }
                    else
                        jj++;
                }

                if (writeCommands[ii].Count == 0)
                    writeCommands.RemoveAt(ii);
                else
                    ii++;
            }

            return writeCommands;
        }

        #region Write handler functions
        private string GetCaseHeader(string name, bool isFirstLine, string tabShift)
        {
            string caseLine = String.Concat("case ", m_instName, "_", name, ":", NEW_LINE);
            if (isFirstLine == false)
                caseLine = String.Concat(tabShift, caseLine);
            return caseLine;
        }
        private string GetBootloaderCmdCaseHeader(string name, bool isFirstLine, bool isRead, string tabs)
        {
            StringBuilder sb = new StringBuilder();
            string readWrite = isRead ? "READ" : "WRITE";
            sb.AppendFormat("{0}#ifdef {1}_BTLDR_{2}_EN{3}", isFirstLine ? "" : tabs, m_instName, readWrite, NEW_LINE);
            sb.AppendFormat("{0}case {1}_{2}:{3}", tabs, m_instName, name, NEW_LINE);
            return sb.ToString();
        }

        private string GetBootloaderCmdCaseFooter(bool isRead, string tabs)
        {
            string readWrite = isRead ? "READ" : "WRITE";
            return String.Format("{0}break;{2}{3}{3}#endif /* {1}_BTLDR_{4}_EN */{2}{2}", tabs, m_instName,
                NEW_LINE, tabs.Remove(0, TAB.Length), readWrite);
        }

        private string GetWriteHandlerCaseBody_PageCmd()
        {
            StringBuilder sb = new StringBuilder();
            string tabs = TAB;
            sb.AppendFormat("/* PAGE should only be stored if it is not greater then MAX PAGES{0}", NEW_LINE);
            sb.AppendFormat("* or equal to ALL PAGES.{0}", NEW_LINE);
            sb.AppendFormat("*/{0}",  NEW_LINE);
            sb.AppendFormat("if(({1}_buffer[0u] < {1}_MAX_PAGES) ||{0}", NEW_LINE, m_instName);
            sb.AppendFormat("{0}    ({2}_CMD_ALL_PAGES == {2}_buffer[0u])){1}", tabs, NEW_LINE, m_instName);
            sb.AppendFormat("{{{0}", NEW_LINE);
            sb.AppendFormat("{0}/* First byte in the buffer is a new page value */{1}", tabs, NEW_LINE);
            sb.AppendFormat("{0}{2}_regs.PAGE = {2}_buffer[0u];{1}", tabs, NEW_LINE, m_instName);
            sb.AppendFormat("}}{0}", NEW_LINE);
            return sb.ToString();
        }

        private string GetWriteHandlerCaseBody_BootloadWriteCmd()
        {
            string dstType = m_parameters.IsPSoC3 ? "(void *)" : "(const void *)";
            string lenType = m_parameters.IsPSoC3 ? "(int16)" : "(uint32)";
            return
                TAB + "/* One is added to include a byte count to the number of bytes to copy */" + NEW_LINE +
                TAB + m_instName + "_bufferSize = " + m_instName + "_buffer[0u] + 1u;" + NEW_LINE +
                TAB + "(void) memcpy((void *)" + m_instName + "_btldrWriteBuf, " + 
                dstType + m_instName + "_buffer, " + NEW_LINE +
                TAB_2 + lenType + m_instName + "_bufferSize);" + NEW_LINE +
                TAB + m_instName + "_btldrStatus |= " + m_instName + "_BTLDR_WR_CMPT;" + NEW_LINE;
        }

        private string GetWriteByteCall(CyCustomTableRow row)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("if({0}_BYTE_CMD_LEN_VALID){1}{2}{{{1}", m_instName, NEW_LINE, TAB);
            sb.AppendFormat("{2}    *{0}_cmdDataPtr = {0}_buffer[0u];{1}{2}}}", m_instName, NEW_LINE, TAB);
            return GetRWCall(row, sb.ToString(), TAB);
        }

        private string GetWriteWordCall(CyCustomTableRow row)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("if({0}_WORD_CMD_LEN_VALID){1}{2}{{{1}{2}", m_instName, NEW_LINE, TAB);
            if (m_parameters.IsPSoC3)
            {
                sb.AppendFormat("{2}{0}_cmdDataPtr[0u] = {0}_buffer[1u];{1}{2}", m_instName, NEW_LINE, TAB);
                sb.AppendFormat("{2}{0}_cmdDataPtr[1u] = {0}_buffer[0u];{1}{2}}}", m_instName, NEW_LINE, TAB);
            }
            else
            {
                sb.AppendFormat("{2}{0}_cmdDataPtr[0u] = {0}_buffer[0u];{1}{2}", m_instName, NEW_LINE, TAB);
                sb.AppendFormat("{2}{0}_cmdDataPtr[1u] = {0}_buffer[1u];{1}{2}}}", m_instName, NEW_LINE, TAB);
            }
            return GetRWCall(row, sb.ToString(), TAB);
        }

        private string GetWriteHandlerCaseBody_BlockProcessCall(CyCustomTableRow row)
        {
            return GetWriteWordCall(row);
        }

        private string GetWriteBlockCall(CyCustomTableRow row)
        {
            string dstType = m_parameters.IsPSoC3 ? "(void *)" : "(const void *)";
            string lenType = m_parameters.IsPSoC3 ? "(int16)" : "(uint32)";
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("if({0}_CMD_LEN_VALID){1}{2}{{{1}{2}", m_instName, NEW_LINE, TAB);
            sb.AppendFormat("{3}(void)memcpy((void *){0}_cmdDataPtr, {1}{0}_buffer, {2}{0}_bufferSize);", m_instName, dstType, lenType, TAB);
            sb.AppendLine();
            sb.Append("    }");
            return GetRWCall(row, sb.ToString(), TAB);
        }
        #endregion

        #region Read handler functions
        private string GetReadHandlerCaseBody_PageCmd()
        {
            return TAB + "/* Read back page value from Operating Memory Register Store */" + NEW_LINE +
                TAB + m_instName + "_buffer[0u] = " + m_instName + "_regs.PAGE;" + NEW_LINE;
        }

        private string GetReadHandlerCaseBody_QueryCmd()
        {
            return "{" + NEW_LINE +
                TAB + "uint8 cmdIdx;" + NEW_LINE +
                NEW_LINE +
                TAB + "/* Look for a command in the array of supported commands */" + NEW_LINE +
                TAB + "for(cmdIdx = 0u; cmdIdx < " + m_instName + "_NUM_COMMANDS; cmdIdx++)" + NEW_LINE +
                TAB + "{" + NEW_LINE +
                TAB_2 + "if(" + m_instName + "_buffer[1u] == " + m_instName + "_commands[cmdIdx].command)" + NEW_LINE +
                TAB_2 + "{" + NEW_LINE +
                TAB_3 + "break; /* Command found - no need to continue */" + NEW_LINE +
                TAB_2 + "}" + NEW_LINE +
                TAB + "}" + NEW_LINE +
                TAB + "if(" + m_instName + "_NUM_COMMANDS != cmdIdx)" + NEW_LINE +
                TAB + "{" + NEW_LINE +
                TAB_2 + "/* Copy command code investigated into Operating Memory Register Store. */" + NEW_LINE +
                TAB_2 + "" + m_instName + "_regs.QUERY[0u] = " + m_instName + "_buffer[0u];" + NEW_LINE +
                TAB_2 + "" + m_instName + "_regs.QUERY[1u] = " + m_instName + "_buffer[1u];" + NEW_LINE +
                NEW_LINE + TAB_2 + "/* Put the information about the command into I2C buffer */" + NEW_LINE +
                TAB_2 + "" + m_instName + "_buffer[1u] = " + m_instName + "_commands[cmdIdx].cmdProp | " + m_instName + "_CMD_SUPPORTED;" + NEW_LINE +
                TAB_2 + "/* Clear bits [1:0]. The bits are reserved for future use. */" + NEW_LINE +
                TAB_2 + m_instName + "_buffer[1u] &= (uint8)~(" + m_instName + "_CMD_WR_AUTO | " + m_instName + "_CMD_RD_AUTO);" + NEW_LINE +
                TAB + "}" + NEW_LINE +
                TAB + "else" + NEW_LINE +
                TAB + "{" + NEW_LINE +
                TAB_2 + "/* Send zero if a command is not supported. */" + NEW_LINE +
                TAB_2 + m_instName + "_buffer[1u] = 0u;" + NEW_LINE +
                TAB + "}" + NEW_LINE +
                TAB + "/* Set the read byte count for the QUERY command */" + NEW_LINE +
                TAB + m_instName + "_buffer[0u] = 1u;" + NEW_LINE +
                "}" + NEW_LINE;
        }

        private string GetReadHandlerCaseBody_BootloadReadCmd()
        {
            string dstType = m_parameters.IsPSoC3 ? "(void *)" : "(const void *)";
            string lenType = m_parameters.IsPSoC3 ? "(int16)" : "(uint32)";
            return
                TAB + "/* Buffer size includes the byte count field */" + NEW_LINE +
                TAB + m_instName + "_bufferSize = " + m_instName + "_btldrReadBuf[0u] + 1u;" + NEW_LINE +
                TAB + "(void)memcpy((void *)" + m_instName + "_buffer, " + dstType + m_instName + "_btldrReadBuf," + NEW_LINE +
                TAB_2 + lenType + m_instName + "_bufferSize);" + NEW_LINE;
        }

        private string GetReadByteCall(CyCustomTableRow row)
        {
            StringBuilder sb = new StringBuilder(); 
            sb.AppendFormat("{0}_buffer[0u] = *{0}_cmdDataPtr;", m_instName);
            return GetRWCall(row, sb.ToString(), TAB);
        }

        private string GetReadWordCall(CyCustomTableRow row)
        {
            StringBuilder sb = new StringBuilder();
            if (m_parameters.IsPSoC3)
            {
                sb.AppendFormat("{0}_buffer[1u] = {0}_cmdDataPtr[0u];{1}", m_instName, NEW_LINE);
                sb.AppendFormat("{1}{0}_buffer[0u] = {0}_cmdDataPtr[1u];", m_instName, TAB);
            }
            else
            {
                sb.AppendFormat("{0}_buffer[0u] = {0}_cmdDataPtr[0u];{1}", m_instName, NEW_LINE);
                sb.AppendFormat("{1}{0}_buffer[1u] = {0}_cmdDataPtr[1u];", m_instName, TAB);
            }
            return GetRWCall(row, sb.ToString(), TAB);
        }

        private string GetReadBlockCall(CyCustomTableRow row)
        {
            string dstType = m_parameters.IsPSoC3 ? "(void *)" : "(const void *)";
            string lenType = m_parameters.IsPSoC3 ? "(int16)" : "(uint32)";
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("(void)memcpy((void *){0}_buffer, {1}{0}_cmdDataPtr, {2}{0}_bufferSize);", m_instName, dstType, lenType);
            return GetRWCall(row,  sb.ToString(), TAB);
        }

        private string GetRWCall(CyCustomTableRow row, string functionName, string tabs)
        {
            StringBuilder caseBody = new StringBuilder();
            if (IsNumPagesCustom(row))
            {
                caseBody.AppendFormat("{0}if({1}u > {2}_cmdPage)", tabs, row.m_numPages.Value, m_instName).AppendLine();
                caseBody.AppendFormat("{0}{{", tabs).AppendLine();
                caseBody.AppendFormat("{0}    {1}", tabs, functionName).AppendLine();
                caseBody.AppendFormat("{0}}}", tabs).AppendLine();
                caseBody.AppendFormat("{0}else", tabs).AppendLine();
                caseBody.AppendFormat("{0}{{", tabs).AppendLine();
                caseBody.AppendFormat("{0}    /* Halt CPU in debug mode if an accessed page is out of valid range */", tabs).AppendLine();
                caseBody.AppendFormat("{0}    CYASSERT(0u != 0u);", tabs).AppendLine();
                caseBody.AppendFormat("{0}}}", tabs).AppendLine();
                caseBody.AppendFormat("{0}break;", tabs).AppendLine();
            }
            else
            {
                caseBody.AppendFormat("{0}{1}", tabs, functionName).AppendLine();
                caseBody.AppendFormat("{0}break;", tabs).AppendLine();
            }
            return caseBody.ToString();
        }

        private string GetReadBlockProcessCall(CyCustomTableRow row)
        {
            return GetReadBlockCall(row);
        }

        private string GetReadHandlerCaseBody_ProcessCall(CyCustomTableRow row)
        {
            return GetReadWordCall(row);
        }
        #endregion

        private string GetCmdTableEntryElement(bool enable, string name, byte? size, CyECmdType type,
            CyEReadWriteConfigType writeConfig, CyEReadWriteConfigType readConfig, bool paged, CyEFormatType format,
            CyArrayType generateAsArray)
        {
            string result = string.Empty;
            if (enable)
            {
                if (type == CyECmdType.BlockProcessCall || type == CyECmdType.ReadWriteBlock)
                    size++;

                string cast = (type == CyECmdType.ReadWriteWord || type == CyECmdType.ProcessCall) ? "(uint8*) " : string.Empty;
                string arrayZeroElement = string.Empty;
                switch (generateAsArray)
                {
                    case CyArrayType.OneDimArray:
                        arrayZeroElement = "[0u]";
                        break;
                    case CyArrayType.TwoDimArray:
                        arrayZeroElement = "[0u][0u]";
                        break;
                    default:
                        break;
                }

                string sizeStr = CyParameters.CellConvertHex(size);
                string refStr = "_regs" + "." + name + arrayZeroElement;
                if (name == CyCustomTable.BOOTLOAD_WRITE)
                {
                    sizeStr = "0x41";
                    refStr = "_btldrWriteBuf[0u]";
                }
                else if (name == CyCustomTable.BOOTLOAD_READ)
                {
                    sizeStr = "0x41";
                    refStr = "_btldrReadBuf[0u]";
                }

                result += TAB + "{" + NEW_LINE + TAB_2 + m_instName + "_" + name + "," +
                    NEW_LINE + TAB_2 + sizeStr + "u," +
                    NEW_LINE + TAB_2 + ((size == 0) ? "NULL" : (cast + "&" + m_instName +
                    refStr)) + "," + NEW_LINE;

                string cmdPropStr = string.Empty;
                byte cmdPropValue = 0;
                switch (writeConfig)
                {
                    case CyEReadWriteConfigType.None:
                        cmdPropValue += 0x00;
                        break;
                    case CyEReadWriteConfigType.Manual:
                        cmdPropStr += m_instName + "_CMD_WR_SUPPORT" + LOGIC_OR + m_instName + "_CMD_WR_MANUAL" + LOGIC_OR;
                        cmdPropValue += 0x40;
                        break;
                    case CyEReadWriteConfigType.Auto:
                        cmdPropStr += m_instName + "_CMD_WR_SUPPORT" + LOGIC_OR + m_instName + "_CMD_WR_AUTO" + LOGIC_OR;
                        cmdPropValue += 0x42;
                        break;
                    default:
                        break;
                }
                switch (readConfig)
                {
                    case CyEReadWriteConfigType.None:
                        cmdPropValue += 0x00;
                        break;
                    case CyEReadWriteConfigType.Manual:
                        cmdPropStr += m_instName + "_CMD_RD_SUPPORT" + LOGIC_OR + m_instName + "_CMD_RD_MANUAL" + LOGIC_OR;
                        cmdPropValue += 0x20;
                        break;
                    case CyEReadWriteConfigType.Auto:
                        cmdPropStr += m_instName + "_CMD_RD_SUPPORT" + LOGIC_OR + m_instName + "_CMD_RD_AUTO" + LOGIC_OR;
                        cmdPropValue += 0x21;
                        break;
                    default:
                        break;
                }
                if (paged)
                {
                    cmdPropStr += m_instName + "_CMD_PAGED" + LOGIC_OR;
                    cmdPropValue += 0x80;
                }
                else
                {
                    cmdPropValue += 0x00;
                }
                switch (format)
                {
                    case CyEFormatType.NonNumeric:
                        cmdPropStr += m_instName + "_CMD_FMT_NON_NUMERIC" + LOGIC_OR;
                        cmdPropValue += 0x1C;
                        break;
                    case CyEFormatType.Linear:
                        cmdPropStr += m_instName + "_CMD_FMT_LINEAR" + LOGIC_OR;
                        cmdPropValue += 0x00;
                        break;
                    case CyEFormatType.Signed:
                        cmdPropStr += m_instName + "_CMD_FMT_SIGNED" + LOGIC_OR;
                        cmdPropValue += 0x04;
                        break;
                    case CyEFormatType.Direct:
                        cmdPropStr += m_instName + "_CMD_FMT_DIRECT" + LOGIC_OR;
                        cmdPropValue += 0x0C;
                        break;
                    case CyEFormatType.Unsigned:
                        cmdPropStr += m_instName + "_CMD_FMT_UNSIGNED" + LOGIC_OR;
                        cmdPropValue += 0x10;
                        break;
                    case CyEFormatType.VidMode:
                        cmdPropStr += m_instName + "_CMD_FMT_VID_MODE" + LOGIC_OR;
                        cmdPropValue += 0x14;
                        break;
                   case CyEFormatType.Manufacturer:
                        cmdPropStr += m_instName + "_CMD_FMT_MANUFACTURER" + LOGIC_OR;
                        cmdPropValue += 0x18;
                        break;
                    default:
                        break;
                }

                if (cmdPropStr.EndsWith(LOGIC_OR))
                {
                    if (cmdPropStr.LastIndexOf(LOGIC_OR) > 0)
                        cmdPropStr = cmdPropStr.Remove(cmdPropStr.LastIndexOf(LOGIC_OR));
                }
                cmdPropStr = TAB_2 + cmdPropStr + NEW_LINE + TAB + "}," + NEW_LINE;
                result += cmdPropStr;
            }
            return result;
        }

        private static string GetCmdDefine(string instanceName, string name, byte? code)
        {
            return "#define " + instanceName + "_" + name + "    (" + CyParameters.CellConvertHex(code) + "u)" +
                NEW_LINE;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="instName">Should be null for generation Reg structure and Instance name for 
        /// generation variable</param>
        /// <param name="pagedCommands"></param>
        /// <param name="name"></param>
        /// <param name="size"></param>
        /// <param name="paged"></param>
        /// <param name="enable"></param>
        /// <param name="index"></param>
        /// <param name="generateAsArray"></param>
        /// <returns></returns>
        private static string GetStructureField(string instName, byte pagedCommands, string name, byte? size,
            bool paged, bool enable, CyECmdType cmdType, int index, ref List<CyArrayType> generateAsArray,
            ref CyStructField[] structFields)
        {
            string result = string.Empty;

            string prefix8 = UINT8_TYPE_SPACE;
            string prefix16 = UINT16_TYPE_SPACE;
            string suffix = ";";
            if (instName != null)
            {
                prefix8 = string.Format("{0}_regs.", instName);
                prefix16 = prefix8;
                suffix = string.Empty;
            }

            generateAsArray.Add(new CyArrayType());
            if (enable && size != null)
            {

                switch (size)
                {
                    case 0:
                        SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, -1, -1);
                        break;
                    case 1:
                        if (name == CyCustomTable.QUERY)
                        {
                            result += prefix8 + name + "[" + (size + 1) + "]" + suffix + NEW_LINE;
                            generateAsArray[index] = CyArrayType.OneDimArray;
                            SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                        }
                        else if (cmdType == CyECmdType.ReadWriteByte)
                        {
                            if (paged)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, 0);
                            }
                            else
                            {
                                result += prefix8 + name + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.NotArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, 0, 0);
                            }
                        }
                        else
                        {
                            if (paged)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1) +
                                    "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.TwoDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                            }
                            else
                            {
                                result += prefix8 + name + "[" + (size + 1) + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                            }
                        }
                        result = TAB + result;
                        break;
                    case 2:
                        if (name == CyPMBusTable.SMBALERT_MASK) // SMBALERT_MASK is exception.
                        {
                            if (paged && pagedCommands > CyParamRange.PAGED_CMDS_MIN)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1) +
                                    "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.TwoDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                            }
                            else
                            {
                                result += prefix8 + name + "[" + (size + 1) + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                            }
                        }
                        else if (cmdType == CyECmdType.ReadWriteWord || cmdType == CyECmdType.ProcessCall)
                        {
                            if (paged)
                            {
                                result += prefix16 + name + "[" + pagedCommands + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt16Type, pagedCommands, 0);
                            }
                            else
                            {
                                result += prefix16 + name + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.NotArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt16Type, 0, 0);
                            }
                        }
                        else
                        {
                            if (paged)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1) +
                                    "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.TwoDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                            }
                            else
                            {
                                result += prefix8 + name + "[" + (size + 1) + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                            }
                        }
                        result = TAB + result;
                        break;
                    default:
                        if (paged)
                        {
                            result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1) +
                                "];" + NEW_LINE;
                            generateAsArray[index] = CyArrayType.TwoDimArray;
                            SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                        }
                        else
                        {
                            result += prefix8 + name + "[" + (size + 1).ToString() + "]" + suffix + NEW_LINE;
                            generateAsArray[index] = CyArrayType.OneDimArray;
                            SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                        }
                        result = TAB + result;
                        break;
                }
            }
            return result;
        }

        private static void SaveStructElementSize(ref CyStructField[] structFields, int index, CyEFieldType fieldType,
            int dim1, int dim2)
        {
            structFields[index].m_fieldType = fieldType;
            structFields[index].m_dim1 = dim1;
            structFields[index].m_dim2 = dim2;
        }

        private static string GetNullStructureField(int index, byte pagedCommands, string name, byte? size, bool paged,
            bool enable, CyECmdType cmdType, CyStructField[] structField)
        {
            string result = string.Empty;
            if (enable && size != null)
            {
                if (structField[index].m_dim1 == 0)
                {
                    result += SLASH_NEW_LINE + TAB + "/* " + name + " */" + SLASH_NEW_LINE +
                        TAB + ((cmdType == CyECmdType.ReadWriteByte) ? "0x00u," : "0x0000u,");
                }
                else if (structField[index].m_dim2 == 0)
                {
                    result += SLASH_NEW_LINE + TAB + "/* " + name + " */" + SLASH_NEW_LINE +
                              TAB + "{";
                    for (int i = 0; i < structField[index].m_dim1; i++)
                    {
                        result += ((structField[index].m_fieldType == CyEFieldType.UInt8Type) ? "0x00u, " : "0x0000u, ");
                    }
                    result = result.TrimEnd(new char[] { ',', ' ' });
                    result += "},";
                }
                else if (structField[index].m_dim1 > 0)
                {
                    result += SLASH_NEW_LINE + TAB + "/* " + name + " */" + SLASH_NEW_LINE;
                    for (int i = 0; i < structField[index].m_dim1; i++)
                    {
                        result += ((i == 0) ? TAB + "{" : SPACE) + "{";
                        for (int j = 0; j < (structField[index].m_dim2); j++)
                        {
                            result += ((structField[index].m_fieldType == CyEFieldType.UInt8Type) ? "0x00u, " : "0x0000u, ");
                        }
                        result = result.TrimEnd(new char[] { ',', ' ' });
                        result += (i < pagedCommands - 1) ? "}," : "}},";
                    }
                }
            }
            return result;
        }

        private void FilterApi(List<CyAPICustomizer> customizers)
        {
            const string INT_C_FILE = "SMBusSlave_INT.c";
            const string INT_P4_C_FILE = "SMBusSlave_INT_P4.c";
            const string BOOT_FILE = "SMBusSlave_BOOT.c";
            const string CRC_FILE = "SMBusSlave_CRC.c";

            for (int i = 0; i < customizers.Count; i++)
            {
                string fileName = Path.GetFileName(customizers[i].OriginalName);
                switch (fileName)
                {
                    case INT_C_FILE:
                        if (m_parameters.IsPSoC4)
                        {
                            customizers.RemoveAt(i--);
                        }
                        break;
                    case INT_P4_C_FILE:
                        if (m_parameters.IsPSoC4)
                        {
                            customizers[i].OutputName = customizers[i].OutputName.Replace("INT_P4", "INT");
                        }
                        else
                        {
                            customizers.RemoveAt(i--);
                        }
                        break;
                    case BOOT_FILE:
                        if (m_parameters.m_isBootloader == false)
                            customizers.RemoveAt(i--);
                        break;
                    case CRC_FILE:
                        if (m_parameters.EnablePec == false)
                            customizers.RemoveAt(i--);
                        break;
                    default:
                        // Do nothing
                        break;
                }
            }
        }
        #endregion
    }

}
