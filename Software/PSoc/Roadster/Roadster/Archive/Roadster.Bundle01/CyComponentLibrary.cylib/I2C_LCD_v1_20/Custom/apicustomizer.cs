/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Collections;
using System.Text;
using System.Diagnostics;

namespace I2C_LCD_v1_20
{
    partial class CyCustomizer : ICyAPICustomize_v1
    {
        private const string INDX_POSTFIX = "IDX";
        private const string DATA_LEN_POSTFIX = "DATA_LEN";

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(
            ICyInstQuery_v1 query,
            ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;
            CyParameters parameters = new CyParameters(query);

            if (parameters.UseCmdPattern == false)
            {
                parameters.RequiredCommands.Insert(0, new CyRequiredCommandRow(0, 0, true, 0x00, 0x00, 0x00, 0x00,
                    CyParameters.WRITE_DATA_NAME, Resources.CmdDescWritingDataPattern));
            }

            #region Generate CmdPatt array
            StringBuilder sb = new StringBuilder();
            int rowCount = parameters.RequiredCommands.Count + GetEnabledCustomCommandsCount(parameters);
            int colCount = GetMaxCommandSize(parameters) + 1;
            string rowFormat = string.Empty;
            switch (colCount)
            {
                case 2:
                    rowFormat = "    {{{0}u, {1}u}},";
                    break;
                case 3:
                    rowFormat = "    {{{0}u, {1}u, {2}u}},";
                    break;
                case 4:
                    rowFormat = "    {{{0}u, {1}u, {2}u, {3}u}},";
                    break;
                case 5:
                    rowFormat = "    {{{0}u, {1}u, {2}u, {3}u, {4}u}},";
                    break;
                default:
                    Debug.Fail("Col count is out of range.");
                    break;
            }
            sb.AppendLine(string.Format("static const uint8 CYCODE {0}_cmdPatt[{1}u][{2}u] =",
                                        query.InstanceName, rowCount, colCount));
            sb.AppendLine("{");
            for (int i = 0; i < parameters.RequiredCommands.Count; i++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[i];
                sb.AppendLine(string.Format("    /* {0} */", command.CmdDescription));
                sb.AppendLine(string.Format(rowFormat,
                    CyParameters.ConvertDecToHex(command.CmdSize.Value),
                    (command.CmdByte1.HasValue) ? CyParameters.ConvertDecToHex(command.CmdByte1.Value) : "0x00",
                    (command.CmdByte2.HasValue) ? CyParameters.ConvertDecToHex(command.CmdByte2.Value) : "0x00",
                    (command.CmdByte3.HasValue) ? CyParameters.ConvertDecToHex(command.CmdByte3.Value) : "0x00",
                    (command.CmdByte4.HasValue) ? CyParameters.ConvertDecToHex(command.CmdByte4.Value) : "0x00"));
            }
            if (parameters.CustomCommands.Count == 0)
            {
                sb.Remove(sb.Length - 3, 1); // Remove last separator if Custom Commands table is empty
            }

            for (int i = 0; i < parameters.CustomCommands.Count; i++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[i];
                bool rowAdded = false;
                if (command.Enable)
                {
                    sb.AppendLine("    /* Custom command */");
                    sb.AppendLine(string.Format(rowFormat,
                        CyParameters.ConvertDecToHex(command.CmdSize.Value),
                        (command.CmdByte1.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.CmdByte1.Value) : "0x00",
                        (command.CmdByte2.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.CmdByte2.Value) : "0x00",
                        (command.CmdByte3.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.CmdByte3.Value) : "0x00",
                        (command.CmdByte4.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.CmdByte4.Value) : "0x00"));
                    rowAdded = true;
                }
                if (i == (parameters.CustomCommands.Count - 1) && rowAdded)
                {
                    sb.Remove(sb.Length - 3, 1); // Remove last separator in array
                }
            }
            sb.Append("};");
            paramDict.Add("CmdPattArray", sb.ToString());
            #endregion Generate CmdPatt array

            #region Generate LEN defines
            sb.Length = 0;
            const string LEN_DEFINE_TEMPLATE = "#define {0}_{1}_{2} ({3}u)";
            for (int cmdIndex = 0; cmdIndex < parameters.RequiredCommands.Count; cmdIndex++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[cmdIndex];
                if (command.CmdDescription == Resources.CmdDescSetCursorPosition ||
                    command.CmdDescription == Resources.CmdDescLoadCustomCharacter)
                {
                    sb.AppendLine(String.Format(LEN_DEFINE_TEMPLATE,
                        query.InstanceName,
                        command.CmdName.ToUpper(),
                        DATA_LEN_POSTFIX,
                        CyParameters.ConvertDecToHex(command.DataSize.Value)));
                }
            }
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.Enable && command.DataSize > 0)
                {
                    sb.AppendLine(String.Format(LEN_DEFINE_TEMPLATE,
                        query.InstanceName,
                        command.ApiName.ToUpper(),
                        DATA_LEN_POSTFIX,
                        CyParameters.ConvertDecToHex(command.DataSize.Value)));
                }
            }
            RemoveLastCharacter(sb);
            paramDict.Add("LenDefines", sb.ToString());
            #endregion Generate LEN defines

            #region Generate INDX defines
            sb.Length = 0;
            int usedCommandCount = parameters.RequiredCommands.Count;
            for (int cmdIndex = 0; cmdIndex < parameters.RequiredCommands.Count; cmdIndex++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[cmdIndex];
                sb.AppendLine(string.Format("#define {0}_{1}_{2} ({3}u)",
                        query.InstanceName,
                        command.CmdName.ToUpper(),
                        INDX_POSTFIX,
                        CyParameters.ConvertDecToHex((byte)(cmdIndex))));
            }
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.Enable)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}_{2} ({3}u)",
                        query.InstanceName,
                        command.ApiName.ToUpper(),
                        INDX_POSTFIX,
                        CyParameters.ConvertDecToHex((UInt16)(parameters.RequiredCommands.Count + cmdIndex))));
                    usedCommandCount++;
                }
            }
            RemoveLastCharacter(sb);
            paramDict.Add("IndexDefines", sb.ToString());
            paramDict.Add("UsedCommandCount", String.Format("{0}u", usedCommandCount));
            #endregion Generate INDX defines

            #region Generate Command defines
            sb.Length = 0;
            for (int cmdIndex = 0; cmdIndex < parameters.RequiredCommands.Count; cmdIndex++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[cmdIndex];
                if (command.CmdByte2.HasValue == false)
                    command.CmdByte2 = 0;
                sb.AppendLine(string.Format("#define {0}_{1} ({2}u)",
                        query.InstanceName,
                        command.CmdName.ToUpper(),
                        CyParameters.ConvertDecToHex(command.CmdByte2.Value)));
            }
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.CmdByte2.HasValue == false)
                    command.CmdByte2 = 0;
                sb.AppendLine(string.Format("#define {0}_{1} ({2}u)",
                        query.InstanceName,
                        command.ApiName.ToUpper(),
                        CyParameters.ConvertDecToHex(command.CmdByte2.Value)));
            }
            RemoveLastCharacter(sb);
            paramDict.Add("CommandDefines", sb.ToString());
            #endregion Generate Command defines

            #region Generate Handle Custom Command defines
            sb.Length = 0;
            // Generate commands with size 0
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.Enable && command.DataSize == 0)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}() {0}_WriteControl({0}_{2})",
                    query.InstanceName,
                    command.ApiName,
                    command.ApiName.ToUpper()));
                    sb.AppendLine(string.Format("#define {0}_Addr{1}(addr) {0}_AddrWriteControl(addr, {0}_{2})",
                    query.InstanceName,
                    command.ApiName,
                    command.ApiName.ToUpper()));
                }
            }
            // Generate commands with size 1
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.Enable && command.DataSize == 1)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}(cmdByte) \\{3}        {0}_HandleOneByteCommand({0}_{2}, cmdByte)",
                    query.InstanceName,
                    command.ApiName,
                    command.ApiName.ToUpper(),
                    Environment.NewLine));
                    sb.AppendLine(string.Format("#define {0}_Addr{1}(addr, cmdByte) \\{3}        {0}_AddrHandleOneByteCommand(addr, {0}_{2}, cmdByte)",
                    query.InstanceName,
                    command.ApiName,
                    command.ApiName.ToUpper(),
                    Environment.NewLine));
                }
            }
            // Generate commands with size > 1
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.Enable && command.DataSize > 1)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}(cmdData) \\{3}        {0}_HandleCustomCommand({0}_{2}, {0}_{2}_{4}, cmdData)",
                    query.InstanceName,
                    command.ApiName,
                    command.ApiName.ToUpper(),
                    Environment.NewLine,
                    DATA_LEN_POSTFIX));
                    sb.AppendLine(string.Format("#define {0}_Addr{1}(addr, cmdData) \\{3}        {0}_AddrHandleCustomCommand(addr, {0}_{2}, {0}_{2}_{4}, cmdData)",
                    query.InstanceName,
                    command.ApiName,
                    command.ApiName.ToUpper(),
                    Environment.NewLine,
                    DATA_LEN_POSTFIX));
                }
            }
            RemoveLastCharacter(sb);
            paramDict.Add("HandleCustomCmdDefines", sb.ToString());
            #endregion

            #region Generate Custom Font array
            sb.Length = 0;
            sb.AppendLine(String.Format("uint8 const CYCODE {0}_customFonts[64u] =", query.InstanceName));
            sb.AppendLine("{");
            switch (parameters.CustomCharacterSet)
            {
                case CyECustomCharacterSet.Horizontal:
                    sb.Append(GetHorizontalBargraph());
                    break;
                case CyECustomCharacterSet.Vertical:
                    sb.Append(GetVerticalBargraph());
                    break;
                case CyECustomCharacterSet.UserDefined:
                    for (int i = 0; i < CyParamRanges.CUSTOM_CHAR_NUM; i++)
                    {
                        string[] charColumns = new string[CyParamRanges.CUSTOM_CHAR_NUM];
                        charColumns = parameters.GetCustomChar(i).Split(',');
                        for (int j = 0; j < charColumns.Length; j++)
                        {
                            if ((j % 8) == 0)
                            {
                                if (i > 0) // do not insert new line before first line
                                {
                                    sb.AppendLine();
                                }
                                sb.Append("    ");
                            }
                            sb.Append(String.Format("0x0{0}u{1}",
                                      charColumns[j],
                                      ((i == CyParamRanges.CUSTOM_CHAR_NUM - 1) &&  // add comma for not last elements
                                      (j == charColumns.Length - 1)) ? "" : ", "));
                        }
                    }
                    break;
                default:
                    sb.Length = 0;
                    break;
            }
            if (sb.Length > 0)
            {
                sb.AppendLine();
                sb.Append("};");
            }
            paramDict.Add("CustomFontsArray", sb.ToString());
            #endregion

            paramDict.Add("CharSetValue", string.Concat(CyParameters.ConvertDecToHex(
                (byte)parameters.CustomCharacterSet), "u"));

            // Replace macro dictionaries with paramDict
            for (int i = 0; i < customizers.Count; i++)
            {
                CyAPICustomizer api = customizers[i];
                api.MacroDictionary = paramDict;
            }

            return customizers;
        }

        private static void RemoveLastCharacter(StringBuilder sb)
        {
            if (sb.Length > 0) sb.Length = sb.Length - 2;
        }

        private static int GetMaxCommandSize(CyParameters parameters)
        {
            int maxCommandSize = 0;
            for (int i = 0; i < parameters.RequiredCommands.Count; i++)
            {
                if (parameters.RequiredCommands[i].CmdSize > maxCommandSize)
                    maxCommandSize = parameters.RequiredCommands[i].CmdSize.Value;
            }
            for (int i = 0; i < parameters.CustomCommands.Count; i++)
            {
                if (parameters.CustomCommands[i].Enable && (parameters.CustomCommands[i].CmdSize > maxCommandSize))
                    maxCommandSize = parameters.CustomCommands[i].CmdSize.Value;
            }
            return maxCommandSize;
        }

        private static int GetEnabledCustomCommandsCount(CyParameters parameters)
        {
            int custCmdCount = 0;
            for (int i = 0; i < parameters.CustomCommands.Count; i++)
            {
                if (parameters.CustomCommands[i].Enable)
                {
                    custCmdCount++;
                }
            }
            return custCmdCount;
        }

        #region Hard Coded Bargraph Character Values
        private string GetVerticalBargraph()
        {
            // Each line of the string builder represents single character, which has 8 rows and 5 columns. 
            // Each element of the line represents one row. Row cells can be either white (0) or black (1), 
            // that are add up to a five-bit sequence. Single element is a hexadecimal representation of 
            // binary value which represents 5 cells of the row.
            StringBuilder sb = new StringBuilder();
            // Character LCD_1_CUSTOM_0   
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu,");
            // Character LCD_1_CUSTOM_1   
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_2    
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_3   
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_4    
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_5    
            sb.AppendLine("    0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_6    
            sb.AppendLine("    0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_7    
            sb.Append("    0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu");
            return sb.ToString();
        }

        private string GetHorizontalBargraph()
        {
            // Each line of the string builder represents single character, which has 8 rows and 5 columns. 
            // Each element of the line represents one row. Row cells can be either white (0) or black (1), 
            // that are add up to a five-bit sequence. Single element is a hexadecimal representation of 
            // binary value which represents 5 cells of the row.
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,");
            // Character LCD_1_CUSTOM_1     
            sb.AppendLine("    0x10u, 0x10u, 0x10u, 0x10u, 0x10u, 0x10u, 0x10u, 0x10u,");
            // Character LCD_1_CUSTOM_2     
            sb.AppendLine("    0x18u, 0x18u, 0x18u, 0x18u, 0x18u, 0x18u, 0x18u, 0x18u,");
            // Character LCD_1_CUSTOM_3     
            sb.AppendLine("    0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu,");
            // Character LCD_1_CUSTOM_4     
            sb.AppendLine("    0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu,");
            // Character LCD_1_CUSTOM_5     
            sb.AppendLine("    0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_6     
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,");
            // Character LCD_1_CUSTOM_7     
            sb.Append("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u");
            return sb.ToString();
        }
        #endregion
    }
}
