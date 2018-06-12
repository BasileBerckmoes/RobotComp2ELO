/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Serialization;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace I2C_LCD_v1_20
{
    #region Component Parameters Names
    public class CyParamNames
    {
        // General tab
        public const string CUSTOM = "Custom";
        public const string CUSTOM_CHARACTER_SET = "CustomCharacterSet";
        public const string DEFAULT_I2C_ADDRESS = "DefaultI2cAddress";
        public const string I2C_MASTER_INSTANCE_NAME = "I2cMasterInstanceName";
        public const string IS_I2C_ADDRESS_HEX = "IsI2cAddressHex";
        // Custom commands tab
        public const string COMMAND_FORMAT = "CommandFormat";
        public const string REQUIRED_COMMANDS = "RequiredCommands";
        public const string CUSTOM_COMMANDS = "CustomCommands";
        public const string USE_CMD_PATTERN = "UseCmdPattern";
    }
    #endregion

    #region Constants for parameters range
    public class CyParamRanges
    {
        public const byte DEFAULT_I2C_ADDRESS_MIN = 0x00;
        public const byte DEFAULT_I2C_ADDRESS_MAX = 0xFF;
        public const byte CMD_SIZE_MIN = 1;
        public const byte CMD_SIZE_MAX = 4;
        public const int CUSTOM_CHAR_NUM = 8;
        public const int DATA_SIZE_MIN = 0;
        public const int DATA_SIZE_MAX = Byte.MaxValue;
    }
    #endregion

    #region Component Enum(s)
    public enum CyECustomCharacterSet
    {
        [Description("None")]
        None,
        [Description("Horizontal bargraph")]
        Horizontal,
        [Description("Vertical bargraph")]
        Vertical,
        [Description("User defined")]
        UserDefined
    }

    public enum CyECommandFormat
    {
        [Description("NXP PCF2119x + Custom Format")]
        NxpPlusCustom,
        [Description("Custom format")]
        Custom
    }
    #endregion

    public class CyParameters
    {
        public const string WRITE_DATA_NAME = "WRITE_DATA";
        private ICyInstQuery_v1 m_instQuery;
        private ICyInstEdit_v1 m_instEdit;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;
        // Xml serialization parameters
        private XmlSerializer m_requiredCommandsSerializer;
        private XmlSerializer m_customCommandsSerializer;
        private XmlSerializerNamespaces m_customSerNamespace;

        private static readonly Color DISABLED_COLUMN_COLOR = SystemColors.ControlLight;
        private static readonly Color ENABLED_COLUMN_COLOR = SystemColors.Window;

        private List<CyRequiredCommandRow> m_requiredCommandsTable;
        private List<CyCustomCommandRow> m_customCommandsTable;

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;

            // Create XML Serializer(s)
            m_requiredCommandsSerializer = new XmlSerializer(typeof(List<CyRequiredCommandRow>));
            m_customCommandsSerializer = new XmlSerializer(typeof(List<CyCustomCommandRow>));
            m_customSerNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(CyParameters).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);

            m_requiredCommandsTable = new List<CyRequiredCommandRow>(GetRequiredCommands());
            m_customCommandsTable = new List<CyCustomCommandRow>(GetCustomCommands());
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }
        #endregion

        #region Getters/Setters
        // Common properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
            set { m_instQuery = value; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        // General tab properties
        public CyECustomCharacterSet CustomCharacterSet
        {
            get { return GetValue<CyECustomCharacterSet>(CyParamNames.CUSTOM_CHARACTER_SET); }
            set { SetValue(CyParamNames.CUSTOM_CHARACTER_SET, value); }
        }

        public byte Address
        {
            get { return GetValue<byte>(CyParamNames.DEFAULT_I2C_ADDRESS); }
            set { SetValue(CyParamNames.DEFAULT_I2C_ADDRESS, value); }
        }

        public bool IsAddressHex
        {
            get { return GetValue<bool>(CyParamNames.IS_I2C_ADDRESS_HEX); }
            set { SetValue(CyParamNames.IS_I2C_ADDRESS_HEX, value); }
        }

        public string I2cInstanceName
        {
            get { return GetValue<string>(CyParamNames.I2C_MASTER_INSTANCE_NAME); }
            set { SetValue(CyParamNames.I2C_MASTER_INSTANCE_NAME, value); }
        }

        public string GetCustomChar(int index)
        {
            return GetValue<string>(string.Format("{0}{1}", CyParamNames.CUSTOM, index));
        }

        public void SetCustomChar(int index, string value)
        {
            SetValue(string.Format("{0}{1}", CyParamNames.CUSTOM, index), string.Format("{0}", value));
        }

        // Custom commands tab properties
        public CyECommandFormat CommandFormat
        {
            get { return GetValue<CyECommandFormat>(CyParamNames.COMMAND_FORMAT); }
            set { SetValue(CyParamNames.COMMAND_FORMAT, value); }
        }

        public List<CyRequiredCommandRow> RequiredCommands
        {
            get { return m_requiredCommandsTable; }
            set { m_requiredCommandsTable = value; }
        }

        public List<CyCustomCommandRow> CustomCommands
        {
            get { return m_customCommandsTable; }
            set { m_customCommandsTable = value; }
        }

        public bool UseCmdPattern
        {
            get { return GetValue<bool>(CyParamNames.USE_CMD_PATTERN); }
            set { SetValue(CyParamNames.USE_CMD_PATTERN, value); }
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null) return default(T);
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        public static CyRequiredCommandRow GetWritingDataCmdPattern()
        {
            return new CyRequiredCommandRow(1, 0, true, 0x40, null, null, null, WRITE_DATA_NAME,
                                                                        Resources.CmdDescWritingDataPattern);
        }

        public List<CyRequiredCommandRow> GetDefaultRequiredCommands()
        {
            List<CyRequiredCommandRow> cmdList = new List<CyRequiredCommandRow>();

            if (this.UseCmdPattern)
            {
                cmdList.Add(GetWritingDataCmdPattern());
            }

            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x0C, null, null, "DISPLAY_ON_CURSOR_OFF",
                                                                             Resources.CmdDescDisplayOn));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x08, null, null, "DISPLAY_CURSOR_OFF",
                                                                             Resources.CmdDescDisplayOff));
            cmdList.Add(new CyRequiredCommandRow(1, 1, false, 0x00, 0x80, null, null, "DDRAM_0",
                                                                             Resources.CmdDescSetCursorPosition));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x02, null, null, "CURSOR_HOME",
                                                                             Resources.CmdDescCursorHome));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x03, null, null, "RESET_CURSOR_POSITION",
                                                                             Resources.CmdDescResetCursorPosition));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x10, null, null, "CURSOR_SH_LEFT",
                                                                             Resources.CmdDescCursorLeftOnePlace));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x14, null, null, "CURSOR_SH_RIGHT",
                                                                             Resources.CmdDescCursorRightOnePlace));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x0E, null, null, "DISPLAY_CURSOR_ON",
                                                                             Resources.CmdDescUnderlineCursorOn));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x0D, null, null, "CURSOR_WINK",
                                                                             Resources.CmdDescCursorWink));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x0F, null, null, "CURSOR_BLINK",
                                                                             Resources.CmdDescCursorBlink));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x01, null, null, "CLEAR_DISPLAY",
                                                                             Resources.CmdDescClearScreen));
            cmdList.Add(new CyRequiredCommandRow(2, 9, true, 0x00, 0x40, null, null, "CGRAM_0",
                                                                             Resources.CmdDescLoadCustomCharacter));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x24, null, null, "DISPLAY_2_LINES_5x10",
                                                                             Resources.CmdDesc2Lines16Characters));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x06, null, null, "CURSOR_RIGHT",
                                                                             Resources.CmdDescCursorAutoIncrement));
            cmdList.Add(new CyRequiredCommandRow(2, 0, true, 0x00, 0x04, null, null, "CURSOR_LEFT",
                                                                             Resources.CmdDescAutoDecrement));
            return cmdList;
        }

        private void AssignDefaultValues(ref List<CyRequiredCommandRow> list)
        {
            List<CyRequiredCommandRow> defaultReqCmds = GetDefaultRequiredCommands();
            if (defaultReqCmds.Count == list.Count)
            {
                for (int cmdIndex = 0; cmdIndex < defaultReqCmds.Count; cmdIndex++)
                {
                    list[cmdIndex].IsDataSizeReadOnly = defaultReqCmds[cmdIndex].IsDataSizeReadOnly;
                    list[cmdIndex].CmdDescription = defaultReqCmds[cmdIndex].CmdDescription;
                    list[cmdIndex].CmdName = defaultReqCmds[cmdIndex].CmdName;
                    if (list[cmdIndex].IsDataSizeReadOnly)
                    {
                        list[cmdIndex].DataSize = defaultReqCmds[cmdIndex].DataSize;
                    }
                }
            }
            else
            {
                list = defaultReqCmds;
            }
        }
        #endregion

        public bool IsAPINameReserved(string name)
        {
            bool isNameReserved = false;
            for (int i = 0; i < RequiredCommands.Count; i++)
            {
                if (RequiredCommands[i].CmdName.ToUpper() == name.ToUpper())
                {
                    isNameReserved = true;
                    break;
                }
            }
            return isNameReserved;
        }

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_instEdit != null && m_globalEditMode)
            {
                string valueToSet = (value == null) ? String.Empty : value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (m_instEdit.SetParamExpr(paramName, valueToSet.ToString()))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }
        #endregion

        #region Getting/Setting parameters with XML Data
        public List<CyRequiredCommandRow> GetRequiredCommands()
        {
            string xmlData = GetValue<string>(CyParamNames.REQUIRED_COMMANDS);
            List<CyRequiredCommandRow> requiredCommands =
                                (List<CyRequiredCommandRow>)Deserialize(xmlData, typeof(List<CyRequiredCommandRow>));
            AssignDefaultValues(ref requiredCommands);
            return requiredCommands;
        }

        public List<CyCustomCommandRow> GetCustomCommands()
        {
            string xmlData = GetValue<string>(CyParamNames.CUSTOM_COMMANDS);
            return (List<CyCustomCommandRow>)Deserialize(xmlData, typeof(List<CyCustomCommandRow>));
        }

        public void SetRequiredCommands()
        {
            if (m_globalEditMode)
            {
                SetValue(CyParamNames.REQUIRED_COMMANDS, Serialize(m_requiredCommandsTable));
            }
        }

        public void SetCustomCommands()
        {
            if (m_globalEditMode)
            {
                SetValue(CyParamNames.CUSTOM_COMMANDS, Serialize(m_customCommandsTable));
            }
        }
        #endregion

        #region XML Serialization
        private XmlSerializer GetSerializer(Type type)
        {
            if (type == typeof(List<CyRequiredCommandRow>))
            {
                return m_requiredCommandsSerializer;
            }
            else if (type == typeof(List<CyCustomCommandRow>))
            {
                return m_customCommandsSerializer;
            }
            else
            {
                return new XmlSerializer(type);
            }
        }

        public string Serialize(object obj)
        {
            StringBuilder sb = new StringBuilder();
            string res;
            try
            {
                using (System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb))
                {
                    GetSerializer(obj.GetType()).Serialize(tw, obj, m_customSerNamespace);
                }
                res = sb.ToString();
                res = res.Replace(Environment.NewLine, " ");
            }
            catch
            {
                res = "";
            }
            return res;
        }

        public object Deserialize(string serializedXml, Type t)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml)) throw new Exception();

                // Read version information
                using (XmlReader tr = XmlReader.Create(new StringReader(serializedXml)))
                {
                    // Remove header <?xml version="1.0" encoding="utf-16" ?> 
                    tr.Read();
                    tr.Read();
                    // Go to first Node with attributes
                    while (tr.HasAttributes == false)
                    {
                        tr.Read();
                    }

                    // This version information will be used in future versions of component.
                    string ver_info = tr.GetAttribute(0);
                    res = GetSerializer(t).Deserialize(tr);
                }
            }
            catch
            {
                res = Activator.CreateInstance(t);
                if (String.IsNullOrEmpty(serializedXml))
                {
                    if (t == typeof(List<CyRequiredCommandRow>))
                    {
                        res = GetDefaultRequiredCommands();
                    }
                }
                else
                {
                    MessageBox.Show(Resources.SettingsIncorrectValues,
                        MessageBoxIcon.Warning.ToString(), MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            return res;
        }
        #endregion

        #region Static methods for columns and cells appearance
        public static void SetColumnReadOnlyState(DataGridViewColumn dgvColumn, bool readOnly)
        {
            dgvColumn.ReadOnly = readOnly;
            dgvColumn.CellTemplate.Style.BackColor = readOnly ? DISABLED_COLUMN_COLOR : ENABLED_COLUMN_COLOR;
        }
        public static void SetCellReadOnlyState(DataGridViewCell cell, bool readOnly, bool setToNull)
        {
            SetCellReadOnlyState(cell, readOnly);
            if (setToNull)
            {
                cell.Value = null;
                cell.ErrorText = "";
            }
        }
        public static void SetCellReadOnlyState(DataGridViewCell cell, bool readOnly)
        {
            cell.ReadOnly = readOnly;
            cell.Style.BackColor = readOnly ? DISABLED_COLUMN_COLOR : ENABLED_COLUMN_COLOR;
        }
        #endregion

        #region Converters
        /// <summary>
        /// Converts hexadecimal string to the nullable byte
        /// </summary>
        /// <param name="value">Cell value that contains Hexadecimal string</param>
        /// <returns>Either byte value of successfully parsed string or null</returns>
        public static byte? ParseHexByte(object value)
        {
            try { return Convert.ToByte(value.ToString(), 16); }
            catch { return null; }
        }

        /// <summary>
        /// Converts decimal value to hex with "0x" prefix
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string ConvertCellToHex(object value)
        {
            byte byteValue;
            try { byteValue = Convert.ToByte(value); }
            catch { byteValue = 0; }
            return string.Format("0x{0:X2}", byteValue);
        }
        /// <summary>
        /// Converts byte to hex string of 0xFF format
        /// </summary>
        /// <param name="value">Value to convert</param>
        /// <returns>String of 0xFF format</returns>
        public static string ConvertDecToHex(byte value)
        {
            return string.Format("0x{0:X2}", value);
        }
        /// <summary>
        /// Converts byte to hex string of 0xFFFF format
        /// </summary>
        /// <param name="value">Value to convert</param>
        /// <returns>String of 0xFFFF format</returns>
        public static string ConvertDecToHex(UInt16 value)
        {
            return string.Format("0x{0:X4}", value);
        }

        /// <summary>
        /// Adds "0x" prefix only (used for formatting)
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string CellFormatHex(object value)
        {
            UInt32 intValue = 0;
            string result = string.Empty;
            try
            {
                intValue = Convert.ToUInt32(value.ToString(), 16);
                result = string.Concat("0x", intValue.ToString("X2"));
            }
            catch (Exception)
            {
                result = value.ToString();
            }
            return result;
        }

        /// <summary>
        /// Converts value to hex string of 0xFF format
        /// </summary>
        /// <param name="value">Value to convert</param>
        /// <returns>String of 0xFF format if argument is byte, otherwise empty string</returns>
        public static string NullableByteToHex(object value)
        {
            string res = string.Empty;
            byte? convertedValue = CyParameters.ParseNullableByte(value);
            if (convertedValue.HasValue)
                res = convertedValue.Value.ToString("X2");
            return res;
        }

        /// <summary>
        /// Converts object to nullable byte
        /// </summary>
        /// <param name="val">Value to convert</param>
        /// <returns>Nullable byte value which has value if object is of Byte type, otherwise null</returns>
        public static byte? ParseNullableByte(object val)
        {
            string strVal = CellToString(val);
            byte? res = null;
            byte parsed = 0;
            if (byte.TryParse(strVal, out parsed))
            {
                res = parsed;
            }
            return res;
        }

        /// <summary>
        /// Converts object to string
        /// </summary>
        /// <param name="cellValue">Value to convert</param>
        /// <returns>Argument converted to string. If argument is null, returns empty string</returns>
        public static string CellToString(object cellValue)
        {
            string res = string.Empty;
            if (cellValue != null)
                res = cellValue.ToString();
            return res;
        }

        /// <summary>
        /// Converts object to boolean
        /// </summary>
        /// <param name="cellValue">Value to convert</param>
        /// <returns>Argument converted to Bool if succeed, otherwise false</returns>
        public static bool CellToBool(object val)
        {
            bool res = false;
            try
            {
                res = Convert.ToBoolean(Convert.ToInt32(val));
            }
            catch { }
            return res;
        }
        #endregion

        #region Check tables for null values
        public bool CheckCustomCommandsNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < CustomCommands.Count; i++)
            {
                if ((CustomCommands[i].CmdSize == null) ||
                    (CustomCommands[i].DataSize == null) ||
                    (CustomCommands[i].CmdByte1 == null) ||
                    (CustomCommands[i].CmdSize != null &&
                               CustomCommands[i].CmdSize > 1 && CustomCommands[i].CmdByte2 == null) ||
                    (CustomCommands[i].CmdSize != null &&
                               CustomCommands[i].CmdSize > 2 && CustomCommands[i].CmdByte3 == null) ||
                    (CustomCommands[i].CmdSize != null &&
                               CustomCommands[i].CmdSize > 3 && CustomCommands[i].CmdByte4 == null) ||
                    (CustomCommands[i].ApiName == null))
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }

        public bool CheckRequiredCommandsNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < RequiredCommands.Count; i++)
            {
                if ((RequiredCommands[i].CmdByte1 == null) ||
                    (RequiredCommands[i].CmdSize != null &&
                                 RequiredCommands[i].CmdSize > 1 && RequiredCommands[i].CmdByte2 == null) ||
                    (RequiredCommands[i].CmdSize != null &&
                                 RequiredCommands[i].CmdSize > 2 && RequiredCommands[i].CmdByte3 == null) ||
                    (RequiredCommands[i].CmdSize != null &&
                                 RequiredCommands[i].CmdSize > 3 && RequiredCommands[i].CmdByte4 == null))
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }
        #endregion
    }
}
