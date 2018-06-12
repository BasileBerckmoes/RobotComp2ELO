/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Drawing;
using System.Xml.Serialization;
using System.Xml;
using System.IO;
using System.Diagnostics;

namespace SMBusSlave_v5_20
{
    #region Component Parameters Names
    public class CyParamName
    {
        public const string MODE = "Mode";
        public const string DATA_RATE = "DataRate";
        public const string SLAVE_ADDRESS = "SlaveAddress";
        public const string HEX = "Hex";
        public const string ENABLE_PEC = "EnablePec";
        public const string ENABLE_SMB_ALERT_PIN = "EnableSmbAlertPin";
        public const string SMB_ALERT_MODE = "SmbAlertMode";
        public const string PAGED_COMMANDS_SIZE = "PagedCommandsSize";
        public const string ENABLE_RECIEVE_BYTE_PROTOCOL = "EnableRecieveByteProtocol";
        public const string SUPPORT_PAGE_CMD = "SupportPageCmd";
        public const string SUPPORT_QUERY_CMD = "SupportQueryCmd";

        public const string PM_BUS_TABLE = "PmBusTable";
        public const string CUSTOM_TABLE = "CustomTable";

        public const string IMPLEMENTATION = "I2cImplementation";
        public const string ADDRESS_DECODE = "I2cAddressDecode";
        public const string PINS = "I2cPins";
        public const string UDB_INTERNAL_CLOCK = "I2cUdbInternalClock";
        public const string FIXED_PLACEMENT = "I2cUdbSlaveFixedPlacementEnable";
        public const string MINUS_TOLERANCE = "I2cClockMinusTolerance";
        public const string PLUS_TOLERANCE = "I2cClockPlusTolerance";
        public const string EXTERNAL_IO_BUFFER = "ExternalBuffer";
        public const string PM_BUS_HIDE_DISABLED_COMMANDS = "PmBusTableHideDisabledCommands";

        public const string I2C_PRESCALER_ENABLED = "I2cPrescalerEnabled";
        public const string I2C_PRESCALER_PERIOD = "I2cPrescalerPeriod";
        public const string I2C_SCL_TIMEOUT_ENABLED = "I2cSclTimeoutEnabled";
        public const string I2C_SDA_TIMEOUT_ENABLED = "I2cSdaTimeoutEnabled";
        public const string I2C_TIME_OUT_MS = "I2cTimeOutms";
        public const string I2C_TIMEOUT_PERIOD_FF = "I2cTimeoutPeriodff";
        public const string I2C_TIMEOUT_PERIOD_UDB = "I2cTimeoutPeriodUdb";

        public const string I2C_CLOCK_FROM_TERMINAL = "ClockFromTerm";

        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Component Enums
    public enum CyEModeSelType
    {
        [Description("SMBus Slave")]
        SMBUS_SLAVE,
        [Description("PMBus Slave")]
        PMBUS_SLAVE
    }

    public enum CyESmbAlertModeType
    {
        [Description("Auto Mode")]
        MODE_AUTO = 1,
        [Description("Manual Mode")]
        MODE_MANUAL = 2
    }

    public enum CyECmdType
    {
        [Description("Send Byte")]
        SendByte,
        [Description("Read/Write Byte")]
        ReadWriteByte,
        [Description("Read/Write Word")]
        ReadWriteWord,
        [Description("Read/Write Block")]
        ReadWriteBlock,
        [Description("Process Call")]
        ProcessCall,
        [Description("Block Process Call")]
        BlockProcessCall
    }

    public enum CyEReadWriteConfigType
    {
        [Description("Auto")]
        Auto,
        [Description("Manual")]
        Manual,
        [Description("None")]
        None
    }

    public enum CyEFormatType
    {
        [Description("Non-numeric")]
        NonNumeric,
        [Description("Linear")]
        Linear,
        [Description("Signed")]
        Signed,
        [Description("Direct")]
        Direct,
        [Description("Unsigned")]
        Unsigned,
        [Description("VID Mode")]
        VidMode,
        [Description("Manufacturer")]
        Manufacturer
    }

    public enum CyECmdGroup
    {           //  WRITE                READ
        GROUP0, // (Auto,Manual,None  /  None)
        GROUP1, // (Auto,Manual,None  /  Auto,Manual,None)
        GROUP2, // (Manual,None       /  None)
        GROUP3, // (None              /  Auto,Manual,None)
        GROUP4, // (Auto,Manual,None  /  Manual,None)
        GROUP5, // (None              /  Manual,None)
        GROUP6, // (Auto,Manual       /  Auto,Manual)
        GROUP7  // SPECIFIC (None / Auto,Manual,None)
    }

    public enum CyEImplementationType { I2C__UDB, I2C__FixedFunction }
    public enum CyEAddressDecodeType { I2C__Software, I2C__Hardware }
    public enum CyEBusPortType { I2C__Any, I2C__I2C0, I2C__I2C1 }
    #endregion

    #region Constants For Parameters Range
    public class CyParamRange
    {
        public const int DATA_RATE_MIN = 1;
        public const int DATA_RATE_MAX = 400;
        public const byte DATA_RATE_THRESHOLD = 50;
        public const int DATA_RATE_100 = 100;
        public const int DATA_RATE_400 = 400;
        
        public const int I2C_SLAVE_FSCB_MIN_100KBPS = 1550;
        public const int I2C_SLAVE_FSCB_MIN_400KBPS = 7820;

        public const int SLAVE_ADDRESS_MIN = 0;
        public const int SLAVE_ADDRESS_MAX = 127;
        public const int CMD_CODE_MIN = 0;
        public const int CMD_CODE_MAX = 255;
        public const int PAGED_CMDS_MIN = 1;
        public const int PAGED_CMDS_MAX = 64;
        public const int CMD_SIZE_MAX = 64;

        public const int TOLERANCE_MIN = -5;
        public const int TOLERANCE_MAX = 50;

        public const byte SEND_BYTE_SIZE = 0;
        public const byte READ_WRITE_BYTE_SIZE = 1;
        public const byte READ_WRITE_WORD_SIZE = 2;
        public const byte BLOCK_PROCESS_CALL_SIZE = 16;
        public const byte BOOTLOADER_SIZE = 64;
        
        public const UInt16 FF_DIVIDER_MAX = 4095;

        public const double EPS = 1E-5;
    }
    #endregion

    [XmlType("SMBusSlave")]
    public class CyParameters
    {
        private const int TABLE_FORMAT_VERSION = 2;

        #region Declaring member variables

        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        [XmlIgnore]
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        [XmlIgnore]
        public ICyInstEdit_v1 InstEdit
        {
            get { return m_instEdit; }
        }

        [XmlIgnore]
        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }
        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;
        [XmlIgnore]
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        [XmlIgnore]
        public CyCustomTableRow m_pageRow;
        [XmlIgnore]
        public CyCustomTableRow m_queryRow;
        [XmlIgnore]
        public CyCustomTableRow m_bootloadWriteRow;
        [XmlIgnore]
        public CyCustomTableRow m_bootloadReadRow;

        // Tabs references
        private CyGeneralTab m_generalTab;
        [XmlIgnore]
        public CyGeneralTab GeneralTab
        {
            get { return m_generalTab; }
            set { m_generalTab = value; }
        }

        private CyCustomCmdsTab m_customCmdsTab;
        [XmlIgnore]
        public CyCustomCmdsTab CustomCmdsTab
        {
            get { return m_customCmdsTab; }
            set { m_customCmdsTab = value; }
        }

        private CyPmBusCmdsTab m_pmBusCmdsTab;
        [XmlIgnore]
        public CyPmBusCmdsTab PmBusCmdsTab
        {
            get { return m_pmBusCmdsTab; }
            set { m_pmBusCmdsTab = value; }
        }

        private CyI2cConfigTab m_i2cConfigTab;
        [XmlIgnore]
        public CyI2cConfigTab I2cConfigTab
        {
            get { return m_i2cConfigTab; }
            set { m_i2cConfigTab = value; }
        }

        private CyI2cConfigP4Tab m_i2cConfigP4Tab;
        [XmlIgnore]
        public CyI2cConfigP4Tab I2cConfigP4Tab
        {
            get { return m_i2cConfigP4Tab; }
            set { m_i2cConfigP4Tab = value; }
        }

        // List contains display names of types taken from symbol for filling comboboxes
        [XmlIgnore]
        public List<string> m_modeList;

        // Dictionary is used to keep display names of types taken from symbol,
        // and associate them with the enum fields to simplify access to diaplay names
        [XmlIgnore]
        public Dictionary<object, string> m_dnDict = new Dictionary<object, string>();

        public static readonly Color DISABLED_COLUMN_COLOR = SystemColors.ControlLight;
        public static readonly Color ENABLED_COLUMN_COLOR = Color.White;

        public static List<string> CustomTableHeader_v2 = new List<string>();

        public static List<string> CustomTableHeader_v1 = new List<string>(new string[]{
        "Enable","Command name","Code","Type","Format","Size","Paged","Read config","Write config"}
            );
        public static List<string> PMBusCmdsTableHeader = new List<string>();

        // Tables used by the customizer
        private CyPMBusTable m_pmBusTable = new CyPMBusTable();
        private CyCustomTable m_customTable = new CyCustomTable();

        // Xml serialization parameters
        private XmlSerializer m_serializerCyPmBusTable;
        private XmlSerializer m_serializerCyCustomTable;
        private XmlSerializerNamespaces m_customSerNamespace;

        public static readonly List<byte> ReservedCmdCodes = new List<byte>(new byte[] { 255 });
        public static readonly List<string> ReservedCmdNames = new List<string>(new string[] { 
            CyCustomTable.PAGE, CyCustomTable.QUERY, CyCustomTable.BOOTLOAD_READ, CyCustomTable.BOOTLOAD_WRITE 
        });

        public static readonly List<UInt16> smBusDataRateList = new List<UInt16>(new UInt16[] { 10, 50, 100, 400 });
        public static readonly List<UInt16> pmBusDataRateList = new List<UInt16>(new UInt16[] { 100, 400 });
        public static readonly List<byte> reservedSMBusAddresses = new List<byte>(new byte[] { 
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x28, 0x37, 
            0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x0C, 0x61
        });

        private Dictionary<string, object> m_restoredParameters = new Dictionary<string, object>();

        [XmlIgnore]
        public bool m_isBootloader;
        [XmlIgnore]
        private bool m_customTableIsDefault = false;
        #endregion

        #region Constructor(s)
        public CyParameters() { }
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_instQuery = inst;
            m_instEdit = null;
            m_isBootloader = IsBootloader(InstQuery.DesignQuery.ApplicationType);

            // Create XML Serializer
            m_serializerCyPmBusTable = new XmlSerializer(typeof(CyPMBusTable));
            m_serializerCyCustomTable = new XmlSerializer(typeof(CyCustomTable));

            m_modeList = new List<string>(inst.GetPossibleEnumValues(CyParamName.MODE));

            CyDictParser.FillDictionary(ref m_dnDict, typeof(CyEModeSelType), m_modeList);

            m_customSerNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(CyParameters).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);

            GetPmBusTable();
            GetCustomTable();
        }
        public CyParameters(ICyInstEdit_v1 inst, ICyTerminalQuery_v1 termQuery)
            : this(inst)
        {
            m_instEdit = inst;
            m_termQuery = termQuery;
        }
        #endregion

        #region Class properties

        #region General Tab
        public CyEModeSelType Mode
        {
            get { return GetValue<CyEModeSelType>(CyParamName.MODE); }
            set { SetValue(CyParamName.MODE, value); }
        }

        public UInt16 DataRate
        {
            get { return GetValue<UInt16>(CyParamName.DATA_RATE); }
            set { SetValue(CyParamName.DATA_RATE, value); }
        }

        public UInt16 SlaveAddress
        {
            get { return GetValue<UInt16>(CyParamName.SLAVE_ADDRESS); }
            set { SetValue(CyParamName.SLAVE_ADDRESS, value); }
        }

        public bool EnablePec
        {
            get { return GetValue<bool>(CyParamName.ENABLE_PEC); }
            set { SetValue(CyParamName.ENABLE_PEC, value); }
        }

        public bool EnableSmbAlertPin
        {
            get { return GetValue<bool>(CyParamName.ENABLE_SMB_ALERT_PIN); }
            set { SetValue(CyParamName.ENABLE_SMB_ALERT_PIN, value); }
        }

        public CyESmbAlertModeType SmbAlertMode
        {
            get { return GetValue<CyESmbAlertModeType>(CyParamName.SMB_ALERT_MODE); }
            set { SetValue(CyParamName.SMB_ALERT_MODE, value); }
        }

        public byte PagedCommands
        {
            get { return GetValue<byte>(CyParamName.PAGED_COMMANDS_SIZE); }
            set { SetValue(CyParamName.PAGED_COMMANDS_SIZE, value); }
        }

        public bool EnableRecieveByteProtocol
        {
            get { return GetValue<bool>(CyParamName.ENABLE_RECIEVE_BYTE_PROTOCOL); }
            set { SetValue(CyParamName.ENABLE_RECIEVE_BYTE_PROTOCOL, value); }
        }

        public bool SupportPageCmd
        {
            get { return GetValue<bool>(CyParamName.SUPPORT_PAGE_CMD); }
            set { SetValue(CyParamName.SUPPORT_PAGE_CMD, value); }
        }

        public bool SupportQueryCmd
        {
            get { return GetValue<bool>(CyParamName.SUPPORT_QUERY_CMD); }
            set { SetValue(CyParamName.SUPPORT_QUERY_CMD, value); }
        }
        // Parameters for internal use
        public bool Hex
        {
            get { return GetValue<bool>(CyParamName.HEX); }
            set { SetValue(CyParamName.HEX, value); }
        }
        #endregion

        #region Tables properties
        public List<CyPMBusTableRow> PmBusTable
        {
            get { return m_pmBusTable.m_pmBusTable; }
            set { m_pmBusTable.m_pmBusTable = value; }
        }

        public List<CyCustomTableRow> CustomTable
        {
            get { return m_customTable.m_customTable; }
            set { m_customTable.m_customTable = value; }
        }
        #endregion

        #region I2C Configuration Tab
        public CyEImplementationType Implementation
        {
            get
            {
                return GetValue<CyEImplementationType>(CyParamName.IMPLEMENTATION);
            }
            set
            {
                SetValue(CyParamName.IMPLEMENTATION, value);
            }
        }

        public CyEAddressDecodeType AddressDecode
        {
            get
            {
                return GetValue<CyEAddressDecodeType>(CyParamName.ADDRESS_DECODE);
            }
            set
            {
                SetValue(CyParamName.ADDRESS_DECODE, value);
            }
        }

        public CyEBusPortType Pins
        {
            get
            {
                return GetValue<CyEBusPortType>(CyParamName.PINS);
            }
            set
            {
                SetValue(CyParamName.PINS, value);
            }
        }

        public bool UdbInternalClock
        {
            get
            {
                return GetValue<bool>(CyParamName.UDB_INTERNAL_CLOCK);
            }
            set
            {
                SetValue(CyParamName.UDB_INTERNAL_CLOCK, value);
            }
        }

        public double MinusTolerance
        {
            get
            {
                return GetValue<double>(CyParamName.MINUS_TOLERANCE);
            }
            set
            {
                SetValue(CyParamName.MINUS_TOLERANCE, value);
            }
        }

        public double PlusTolerance
        {
            get
            {
                return GetValue<double>(CyParamName.PLUS_TOLERANCE);
            }
            set
            {
                SetValue(CyParamName.PLUS_TOLERANCE, value);
            }
        }

        public bool UdbSlaveFixedPlacementEnable
        {
            get
            {
                return GetValue<bool>(CyParamName.FIXED_PLACEMENT);
            }
            set
            {
                SetValue(CyParamName.FIXED_PLACEMENT, value);
            }
        }

        public bool ExternalIOBuffer
        {
            get
            {
                return GetValue<bool>(CyParamName.EXTERNAL_IO_BUFFER);
            }
            set
            {
                SetValue(CyParamName.EXTERNAL_IO_BUFFER, value);
            }
        }

        // Timeout properties

        public bool PrescalerEnabled
        {
            get
            {
                return GetValue<bool>(CyParamName.I2C_PRESCALER_ENABLED);
            }
            set
            {
                SetValue(CyParamName.I2C_PRESCALER_ENABLED, value);
            }
        }

        public byte PrescalerPeriod
        {
            get
            {
                return GetValue<byte>(CyParamName.I2C_PRESCALER_PERIOD);
            }
            set
            {
                SetValue(CyParamName.I2C_PRESCALER_PERIOD, value);
            }
        }

        public bool I2cSclTimeoutEnabled
        {
            get
            {
                return GetValue<bool>(CyParamName.I2C_SCL_TIMEOUT_ENABLED);
            }
            set
            {
                SetValue(CyParamName.I2C_SCL_TIMEOUT_ENABLED, value);
            }
        }

        public bool I2cSdaTimeoutEnabled
        {
            get
            {
                return GetValue<bool>(CyParamName.I2C_SDA_TIMEOUT_ENABLED);
            }
            set
            {
                SetValue(CyParamName.I2C_SDA_TIMEOUT_ENABLED, value);
            }
        }

        public byte TimeOutMs
        {
            get
            {
                return GetValue<byte>(CyParamName.I2C_TIME_OUT_MS);
            }
            set
            {
                SetValue(CyParamName.I2C_TIME_OUT_MS, value);
            }
        }

        public UInt16 TimeoutPeriodFF
        {
            get
            {
                return GetValue<UInt16>(CyParamName.I2C_TIMEOUT_PERIOD_FF);
            }
            set
            {
                SetValue(CyParamName.I2C_TIMEOUT_PERIOD_FF, value);
            }
        }

        public UInt16 TimeoutPeriodUDB
        {
            get
            {
                return GetValue<UInt16>(CyParamName.I2C_TIMEOUT_PERIOD_UDB);
            }
            set
            {
                SetValue(CyParamName.I2C_TIMEOUT_PERIOD_UDB, value);
            }
        }
        #endregion

        #region I2C P4 Configuration Tab
        public bool ClockFromTerm
        {
            get { return GetValue<bool>(CyParamName.I2C_CLOCK_FROM_TERMINAL); }
            set { SetValue(CyParamName.I2C_CLOCK_FROM_TERMINAL, value); }
        }
        #endregion I2C P4 Configuration Tab

        #region Others
        public bool PageVisible
        {
            get { return ((Mode == CyEModeSelType.SMBUS_SLAVE) && SupportPageCmd); }
        }

        public bool QueryVisible
        {
            get { return ((Mode == CyEModeSelType.SMBUS_SLAVE) && SupportQueryCmd); }
        }

        public bool IsPSoC3
        {
            get { return InstQuery.DeviceQuery.IsPSoC3; }
        }
        public bool IsPSoC4
        {
            get { return InstQuery.DeviceQuery.IsPSoC4; }
        }

        public bool HideDisabledPMBusCommands
        {
            get
            {
                return GetValue<bool>(CyParamName.PM_BUS_HIDE_DISABLED_COMMANDS);
            }
            set
            {
                SetValue(CyParamName.PM_BUS_HIDE_DISABLED_COMMANDS, value);
            }
        }

        public static bool IsBootloader(CyApplicationType_v1 applicationType)
        {
            return (applicationType == CyApplicationType_v1.Bootloader ||
                    applicationType == CyApplicationType_v1.MultiAppBootloader ||
                    applicationType == CyApplicationType_v1.Bootloadable);
        }

        public bool IsClockExternal
        {
            get
            {
                bool result = false;
                result |= IsPSoC4 && ClockFromTerm;
                result |= !IsPSoC4 && !UdbInternalClock && (Implementation == CyEImplementationType.I2C__UDB);
                return result;
            }
        }

        public string InstanceName
        {
            get { return GetValue<string>(CyParamName.INSTANCE_NAME); }
        }
        #endregion

        #endregion

        #region Getting Parameters
        public static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            if (instQuery == null) return default(T);
            T value;
            CyCustErr err = instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = InstQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }

        public int GetCustomTableIndexByReference(CyCustomTableRow row)
        {
            for (int i = 0; i < CustomTable.Count; i++)
            {
                if (CustomTable[i] == row)
                {
                    return i;
                }
            }
            return -1;
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode && (InstEdit != null))
            {
                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                    valueToSet += "u";
                if (InstEdit.SetParamExpr(paramName, valueToSet))
                {
                    InstEdit.CommitParamExprs();
                }
            }

            // Saving data after deserialization
            if ((GlobalEditMode == false) && (m_instQuery == null))
            {
                if (m_restoredParameters.ContainsKey(paramName))
                {
                    Debug.Assert(false);
                    return;
                }
                m_restoredParameters.Add(paramName, value);
            }
        }

        public void RestoreParameters(Dictionary<string, object> restoreList)
        {
            bool prevGlobalEditMode = GlobalEditMode;
            GlobalEditMode = true;
            foreach (string param_name in restoreList.Keys)
            {
                SetValue<object>(param_name, restoreList[param_name]);
            }
            GlobalEditMode = prevGlobalEditMode;
        }
        #endregion

        #region Getting/Setting parameters with XML Data
        public void GetPmBusTable()
        {
            string xmlData = GetValue<string>(CyParamName.PM_BUS_TABLE);
            CyPMBusTable package = (CyPMBusTable)Deserialize(xmlData, typeof(CyPMBusTable),
                CyCmdData.PMBusCmdList.Length);
            // Mark specific commands
            for (int i = 0; i < package.m_pmBusTable.Count; i++)
            {
                if (CyCustomTable.IsCmdSpecific(package.m_pmBusTable[i].Name))
                    package.m_pmBusTable[i].m_specific = true;
            }
            PmBusTable = package.m_pmBusTable;
        }

        public void SetPmBusTable()
        {
            if (GlobalEditMode)
            {
                CyPMBusTable package = new CyPMBusTable();
                package.m_pmBusTable = new List<CyPMBusTableRow>(PmBusTable.ToArray());
                SetValue(CyParamName.PM_BUS_TABLE, Serialize(package));
            }
        }

        public void GetCustomTable()
        {
            string xmlData = GetValue<string>(CyParamName.CUSTOM_TABLE);
            CyCustomTable package = (CyCustomTable)Deserialize(xmlData, typeof(CyCustomTable), 0);
            CustomTable = package.m_customTable;
            // Check if PAGE and QUERY commands have to be added and add if necessary.
            // This applyes for default table only.
            if (m_customTableIsDefault)
            {
                if (PageVisible)
                    CustomTable.Insert(0, CyCustomTable.GetDefaultPageRow());
                if (QueryVisible)
                    CustomTable.Insert((PageVisible ? 1 : 0), CyCustomTable.GetDefaultQueryRow());
            }
            FilterCustomTable();
        }

        public void SetCustomTable()
        {
            if (GlobalEditMode)
            {
                CyCustomTable package = new CyCustomTable();
                // Add bootloader rows to the object before serialization. They are currently
                // not there because of non-bootloader project. They should be serialized to save 
                // user settings from previous change.
                if (m_isBootloader == false)
                {
                    CustomTable.Add(m_bootloadReadRow);
                    CustomTable.Add(m_bootloadWriteRow);
                }
                package.m_customTable = new List<CyCustomTableRow>(CustomTable.ToArray());
                SetValue(CyParamName.CUSTOM_TABLE, Serialize(package));

                // There were saved invisible rows to the table to save user specific commands
                // Remove them again after save to avoid their appearence in the datagrid
                FilterCustomTable();
            }
        }

        private void FilterCustomTable()
        {
            // Remove specific extra rows from table according to user settings
            List<int> indexesToRemove = new List<int>();
            for (int i = 0; i < CustomTable.Count; i++)
            {
                if (CustomTable[i].m_specific && CustomTable[i].m_name == CyCustomTable.BOOTLOAD_READ)
                {
                    m_bootloadReadRow = new CyCustomTableRow(CustomTable[i]);

                    if (m_isBootloader == false)
                        indexesToRemove.Add(i);
                }
                if (CustomTable[i].m_specific && CustomTable[i].m_name == CyCustomTable.BOOTLOAD_WRITE)
                {
                    m_bootloadWriteRow = new CyCustomTableRow(CustomTable[i]);

                    if (m_isBootloader == false)
                        indexesToRemove.Add(i);
                }
            }

            if (CustomTable.Contains(null))
            {
                // Custom table may contain null elements if there is no 
                // BOOTLOAD_READ or BOOTLOAD_WRITE command in table
                bool containsBootloadReadCmd = false;
                bool containsBootloadWriteCmd = false;
                foreach (CyCustomTableRow item in CustomTable)
                {
                    if (item.m_name == CyCustomTable.BOOTLOAD_READ)
                        containsBootloadReadCmd = true;
                    if (item.m_name == CyCustomTable.BOOTLOAD_WRITE)
                        containsBootloadWriteCmd = true;
                }
                if (containsBootloadReadCmd == false)
                {
                    Debug.Assert(false, string.Format("Custom commands table does not contain {0} command. {0} " +
                        "command will be created with default values.", CyCustomTable.BOOTLOAD_READ));
                }
                if (containsBootloadWriteCmd == false)
                {
                    Debug.Assert(false, string.Format("Custom commands table does not contain {0} command. {0} " +
                        "command will be created with default values.", CyCustomTable.BOOTLOAD_WRITE));
                }
            }

            for (int i = indexesToRemove.Count - 1; i >= 0; i--)
            {
                CustomTable.RemoveAt(indexesToRemove[i]);
            }
        }
        #endregion

        #region DataGridView
        public static void InitializeDataGrid(DataGridView dgv)
        {
            // Initialize data grid view
            dgv.EditMode = DataGridViewEditMode.EditOnEnter;

            // Prevent data grid from sorting
            foreach (DataGridViewColumn item in dgv.Columns)
                item.SortMode = DataGridViewColumnSortMode.NotSortable;
            dgv.AllowUserToOrderColumns = false;
            dgv.AllowUserToDeleteRows = false;
            dgv.AllowUserToAddRows = false;
            dgv.AllowUserToResizeColumns = false;
            dgv.AllowUserToResizeRows = false;
            dgv.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(246, 246, 249);
            dgv.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.DisableResizing;
        }

        public static string IsValueInRange(double? currCellValue, object cellValue, double min, double max,
            string errorMessage, bool displayHex)
        {
            string res = string.Empty;
            string message = string.Empty;
            try
            {
                if (displayHex)
                    message = string.Format(errorMessage, CyParameters.CellConvertHex(min),
                        CyParameters.CellConvertHex(max));
                else
                    message = string.Format(errorMessage, min, max);

                if ((currCellValue.HasValue) && (currCellValue < min || currCellValue > max))
                    throw new Exception();
                else if ((currCellValue == null) && (IsCellEmpty(cellValue) == false))
                    throw new Exception();
            }
            catch (Exception)
            {
                res = message;
            }
            return res;
        }

        public static List<string> GetColNames(DataGridView dgv)
        {
            List<string> colNames = new List<string>();
            for (int i = 0; i < dgv.ColumnCount; i++)
                if (dgv.Columns[i].Visible)
                {
                    colNames.Add(dgv.Columns[i].HeaderText);
                }
            return colNames;
        }

        private static bool IsCellEmpty(object val)
        {
            return (val == null) || ((val != null) && (val.ToString().Trim() == string.Empty));
        }

        public static void SetReadOnlyState(DataGridViewColumn dgvColumn, bool readOnly)
        {
            dgvColumn.ReadOnly = readOnly;
            dgvColumn.CellTemplate.Style.BackColor = readOnly ? DISABLED_COLUMN_COLOR : ENABLED_COLUMN_COLOR;
        }
        public static void SetCellReadOnlyState(DataGridView dgv, int columnIndex, int rowIndex, bool readOnly)
        {
            SetCellReadOnlyState(dgv[columnIndex, rowIndex], readOnly);
        }

        public static void SetCellReadOnlyState(DataGridViewCell cell, bool readOnly)
        {
            cell.ReadOnly = readOnly;
            cell.Style.BackColor = readOnly ? DISABLED_COLUMN_COLOR : ENABLED_COLUMN_COLOR;
        }
        #endregion

        #region Nullable operations
        public static string CellToString(object cellValue)
        {
            string res = string.Empty;
            if (cellValue != null)
                res = cellValue.ToString();
            return res;
        }

        public static byte? ParseNullableHexByte(object val)
        {
            string strVal = CellToString(val);
            byte? res = 0;
            try
            {
                res = Convert.ToByte(strVal, 16);
            }
            catch { res = null; }

            return res;
        }

        public static string NullableByteToHex(object value)
        {
            string res = string.Empty;
            byte? convertedValue = ParseNullableByte(value);
            if (convertedValue.HasValue)
                res = convertedValue.Value.ToString("X2");

            return res;
        }

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

        /// <summary>
        /// Converts decimal value to hex with "0x" prefix
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string CellConvertHex(object value)
        {
            byte byteValue;
            try
            {
                byteValue = Convert.ToByte(value);
            }
            catch (Exception)
            {
                byteValue = 0;
            }

            return string.Concat("0x", byteValue.ToString("X2"));
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

        public static bool IsHex(string text)
        {
            text = text.Trim();
            return text.StartsWith("0x");
        }
        #endregion

        #region XML Serialization
        public void LoadFromObject(string fileContent)
        {
            CyParameters imported = (CyParameters)Deserialize(fileContent, typeof(CyParameters), 0);
            if (imported == null)
            {
                MessageBox.Show(Resources.FileFormatInvalid, GetNamespace(), MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            else
            {
                RestoreParameters(imported.m_restoredParameters);

                CustomTable = imported.CustomTable;
                PmBusTable = imported.PmBusTable;

                //Commit Tables
                SetCustomTable();
                SetPmBusTable();

                //Update mode
                m_pmBusCmdsTab.SetPMBusCmdsTabVisibility(Mode);

                //Update tabs
                GeneralTab.UpdateUI();
                if (I2cConfigTab != null)
                    I2cConfigTab.UpdateUI();
                if (I2cConfigP4Tab != null)
                    I2cConfigP4Tab.UpdateUI();
                PmBusCmdsTab.UpdateUIFromTable();
                CustomCmdsTab.UpdateUIFromTable();

                m_pmBusCmdsTab.ValidateAllTable();
                m_customCmdsTab.ValidateAllTable();
            }
        }

        private XmlSerializer GetSerializer(Type type)
        {
            if (type == typeof(CyPMBusTable))
                return m_serializerCyPmBusTable;
            else if (type == typeof(CyCustomTable))
                return m_serializerCyCustomTable;
            else
                return new XmlSerializer(type);
        }

        public string Serialize(object obj)
        {
            StringBuilder sb = new StringBuilder();

            using (System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb))
            {
                GetSerializer(obj.GetType()).Serialize(tw, obj, m_customSerNamespace);
            }
            string res = sb.ToString();
            res = res.Replace(Environment.NewLine, " ");
            return res;
        }

        public object Deserialize(string serializedXml, Type t, int numOfDefaultRows)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml) == false)
                {
                    //Read version information
                    using (XmlReader tr = XmlReader.Create(new StringReader(serializedXml)))
                    {
                        //Remove header <?xml version="1.0" encoding="utf-16" ?> 
                        tr.Read();
                        tr.Read();
                        //Go to first Node with attributes
                        while (tr.HasAttributes == false)
                        {
                            tr.Read();
                        }
                        // There was column NumPages added in version 2.0, so the column has to be initialized
                        // This code runs only when version of deserialized table is less than 2.0
                        double verInfo = -1;
                        bool versionAvailable = double.TryParse(tr.GetAttribute(0).Replace("_", "."), out verInfo);
                        res = GetSerializer(t).Deserialize(tr);
                        if (versionAvailable && verInfo < TABLE_FORMAT_VERSION)
                        {
                            if (res is CyCustomTable)
                            {
                                InitializeNumberOfPagesColumn((res as CyCustomTable).m_customTable);
                            }
                        }
                    }
                }
            }
            catch
            {
                if (String.IsNullOrEmpty(serializedXml) == false)
                {
                    MessageBox.Show(Resources.SettingsIncorrectValues,
                        MessageBoxIcon.Warning.ToString(), MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }

            if (res == null)
            {
                try
                {
                    res = Activator.CreateInstance(t);
                }
                catch (Exception)
                {
                    return null;
                }

                if (res is ICyTable)
                {
                    ((ICyTable)res).InitializeTable(numOfDefaultRows);
                    if (t.FullName == CyCustomTable.GetString())
                    {
                        m_customTableIsDefault = true; // the flag indicates whether Custom table has default values
                    }
                }
                else
                    return null;
            }

            // Mark reserved rows as specific
            if (res != null && t == typeof(CyCustomTable))
                CyCustomTable.SetReservedRowsFlag((res as CyCustomTable).m_customTable);
            else if (res != null && t == typeof(CyParameters))
                CyCustomTable.SetReservedRowsFlag((res as CyParameters).CustomTable);

            return res;
        }

        private void InitializeNumberOfPagesColumn(List<CyCustomTableRow> customTable)
        {
            for (int rowIndex = 0; rowIndex < customTable.Count; rowIndex++)
            {
                if (CyCustomTable.IsCmdSpecific(customTable[rowIndex].m_name) == false)
                    if (customTable[rowIndex].m_numPages == null)
                        customTable[rowIndex].m_numPages = this.PagedCommands;
            }
        }

        public static string GetNamespace()
        {
            Type type = typeof(CyParameters);
            return type.Namespace;
        }
        #endregion

        #region DRC Verification
        public bool CheckPmBusTableNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < PmBusTable.Count; i++)
            {
                if (PmBusTable[i].m_enable && PmBusTable[i].Size == null)
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }

        public bool CheckCustomTableNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < CustomTable.Count; i++)
            {
                if (CustomTable[i].m_enable &&
                    ((CustomTable[i].m_name == null) ||
                    (CustomTable[i].m_code == null) ||
                    (CustomTable[i].m_size == null) ||
                    (CustomTable[i].m_paged && CustomTable[i].m_numPages == null)))
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }

        public bool CheckBootloaderCommands()
        {
            bool result = true;
            if (this.InstQuery.DesignQuery.ApplicationType != CyApplicationType_v1.Bootloadable)
            {
                for (int i = 0; i < this.CustomTable.Count; i++)
                {
                    if (this.CustomTable[i].m_specific && CyCustomTable.IsCmdBootloader(this.CustomTable[i].m_name) &&
                        this.CustomTable[i].m_enable == false)
                    {
                        result = false;
                        break;
                    }
                }
            }
            return result;
        }
        #endregion

        #region Save/Load file
        public static void SaveToFile(string fileName, string fileContent)
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(fileName))
                {
                    writer.Write(fileContent);
                }
            }
            catch
            {
                MessageBox.Show(String.Format(Resources.FileWriteError, fileName), GetNamespace(),
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public static string GetFileText(string fileName)
        {
            string result = string.Empty;
            try
            {
                using (FileStream fileStream = new FileStream(fileName, FileMode.Open, FileAccess.Read,
                    FileShare.ReadWrite))
                {
                    using (StreamReader sr = new StreamReader(fileStream))
                    {
                        result = sr.ReadToEnd();
                    }
                }
            }
            catch
            {
                MessageBox.Show(String.Format(Resources.FileReadError, fileName), GetNamespace(),
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            return result;
        }
        #endregion

        #region Clock and calculator
        public void UpdateClock(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
        {
            GeneralTab.UpdateClockDependencies();
            UpdateTimeout();
        }

        public void UpdateTimeout()
        {
            CyDividerCalculator.CalculateTimeout(InstEdit, TermQuery);
        }
        #endregion
    }

    #region Specification commands
    public class CyCommand
    {
        public byte m_cmdCode;
        public string m_cmdName;
        public CyECmdType m_type;
        public byte? m_size;
        public bool m_sizeUnlocked;
        public CyECmdGroup m_cmdGroup;
        public bool m_specific;

        #region Constructor(s)
        public CyCommand()
        {
        }
        public CyCommand(byte cmdCode, string cmdName, CyECmdType type, byte? size, CyECmdGroup cmdRwType)
            : this(cmdCode, cmdName, type, size, cmdRwType, false, false)
        {
        }
        public CyCommand(byte cmdCode, string cmdName, CyECmdType type, byte? size, CyECmdGroup cmdRwType,
            bool sizeUnlocked)
            : this(cmdCode, cmdName, type, size, cmdRwType, sizeUnlocked, false)
        {
        }
        public CyCommand(byte cmdCode, string cmdName, CyECmdType type, byte? size, CyECmdGroup cmdRwType,
            bool sizeUnlocked, bool specific)
        {
            m_cmdCode = cmdCode;
            m_cmdName = cmdName;
            m_type = type;
            m_size = size;
            m_sizeUnlocked = sizeUnlocked;
            m_cmdGroup = cmdRwType;
            m_specific = specific;
        }
        #endregion
    }

    public static class CyCmdData
    {
        private const byte DEFAULT_BLOCK_SIZE = 16;

        #region Command Summary from PMBus Power System Mgt Protocol Specification
        public readonly static CyCommand[] PMBusCmdList = new CyCommand[]
        { 
            new CyCommand(0x00, "PAGE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP6, false, true),
            new CyCommand(0x01, "OPERATION", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x02, "ON_OFF_CONFIG", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x03, "CLEAR_FAULTS", CyECmdType.SendByte, 0, CyECmdGroup.GROUP2),
            new CyCommand(0x04, "PHASE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            // PAGE_PLUS_WRITE and PAGE_PLUS_READ commands are not supported
            new CyCommand(0x10, "WRITE_PROTECT", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x11, "STORE_DEFAULT_ALL", CyECmdType.SendByte, 0, CyECmdGroup.GROUP2),
            new CyCommand(0x12, "RESTORE_DEFAULT_ALL", CyECmdType.SendByte, 0, CyECmdGroup.GROUP2),
            new CyCommand(0x13, "STORE_DEFAULT_CODE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP0),
            new CyCommand(0x14, "RESTORE_DEFAULT_CODE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP0),
            new CyCommand(0x15, "STORE_USER_ALL", CyECmdType.SendByte, 0, CyECmdGroup.GROUP2),
            new CyCommand(0x16, "RESTORE_USER_ALL", CyECmdType.SendByte, 0, CyECmdGroup.GROUP2),
            new CyCommand(0x17, "STORE_USER_CODE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP0),
            new CyCommand(0x18, "RESTORE_USER_CODE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP0),
            new CyCommand(0x19, "CAPABILITY", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP3),
            new CyCommand(0x1A, "QUERY", CyECmdType.BlockProcessCall, 1, CyECmdGroup.GROUP7, false, true),
            new CyCommand(0x1B, "SMBALERT_MASK", CyECmdType.BlockProcessCall, 1, CyECmdGroup.GROUP4),
            new CyCommand(0x20, "VOUT_MODE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x21, "VOUT_COMMAND", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x22, "VOUT_TRIM", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x23, "VOUT_CAL_OFFSET", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x24, "VOUT_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x25, "VOUT_MARGIN_HIGH", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x26, "VOUT_MARGIN_LOW", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x27, "VOUT_TRANSITION_RATE", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x28, "VOUT_DROOP", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x29, "VOUT_SCALE_LOOP", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x2A, "VOUT_SCALE_MONITOR", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x30, "COEFFICIENTS", CyECmdType.BlockProcessCall, 5, CyECmdGroup.GROUP5),
            new CyCommand(0x31, "POUT_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x32, "MAX_DUTY", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x33, "FREQUENCY_SWITCH", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x35, "VIN_ON", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x36, "VIN_OFF", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x37, "INTERLEAVE", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x38, "IOUT_CAL_GAIN", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x39, "IOUT_CAL_OFFSET", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x3A, "FAN_CONFIG_1_2", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x3B, "FAN_COMMAND_1", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x3C, "FAN_COMMAND_2", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x3D, "FAN_CONFIG_3_4", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x3E, "FAN_COMMAND_3", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x3F, "FAN_COMMAND_4", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x40, "VOUT_OV_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x41, "VOUT_OV_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x42, "VOUT_OV_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x43, "VOUT_UV_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x44, "VOUT_UV_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x45, "VOUT_UV_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x46, "IOUT_OC_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x47, "IOUT_OC_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x48, "IOUT_OC_LV_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x49, "IOUT_OC_LV_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x4A, "IOUT_OC_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x4B, "IOUT_UC_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x4C, "IOUT_UC_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x4F, "OT_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x50, "OT_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x51, "OT_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x52, "UT_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x53, "UT_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x54, "UT_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x55, "VIN_OV_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x56, "VIN_OV_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x57, "VIN_OV_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x58, "VIN_UV_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x59, "VIN_UV_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x5A, "VIN_UV_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x5B, "IIN_OC_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x5C, "IIN_OC_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x5D, "IIN_OC_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x5E, "POWER_GOOD_ON", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x5F, "POWER_GOOD_OFF", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x60, "TON_DELAY", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x61, "TON_RISE", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x62, "TON_MAX_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x63, "TON_MAX_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x64, "TOFF_DELAY", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x65, "TOFF_FALL", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x66, "TOFF_MAX_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x68, "POUT_OP_FAULT_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x69, "POUT_OP_FAULT_RESPONSE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x6A, "POUT_OP_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x6B, "PIN_OP_WARN_LIMIT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x78, "STATUS_BYTE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x79, "STATUS_WORD", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0x7A, "STATUS_VOUT", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x7B, "STATUS_IOUT", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x7C, "STATUS_INPUT", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x7D, "STATUS_TEMPERATURE", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x7E, "STATUS_CML", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x7F, "STATUS_OTHER", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x80, "STATUS_MFR_SPECIFIC", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x81, "STATUS_FANS_1_2", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x82, "STATUS_FANS_3_4", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP1),
            new CyCommand(0x86, "READ_EIN", CyECmdType.ReadWriteBlock, 5, CyECmdGroup.GROUP5),
            new CyCommand(0x87, "READ_EOUT", CyECmdType.ReadWriteBlock, 5, CyECmdGroup.GROUP5),
            new CyCommand(0x88, "READ_VIN", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x89, "READ_IIN", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x8A, "READ_VCAP", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x8B, "READ_VOUT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x8C, "READ_IOUT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x8D, "READ_TEMPERATURE_1", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x8E, "READ_TEMPERATURE_2", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x8F, "READ_TEMPERATURE_3", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x90, "READ_FAN_SPEED_1", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x91, "READ_FAN_SPEED_2", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x92, "READ_FAN_SPEED_3", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x93, "READ_FAN_SPEED_4", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x94, "READ_DUTY_CYCLE", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x95, "READ_FREQUENCY", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x96, "READ_POUT", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x97, "READ_PIN", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0x98, "PMBUS_REVISION", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP3),
            new CyCommand(0x99, "MFR_ID", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, true),
            new CyCommand(0x9A, "MFR_MODEL", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, true),
            new CyCommand(0x9B, "MFR_REVISION", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0x9C, "MFR_LOCATION", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0x9D, "MFR_DATE", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, true),
            new CyCommand(0x9E, "MFR_SERIAL", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, true),
            new CyCommand(0x9F, "APP_PROFILE_SUPPORT", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, 
                CyECmdGroup.GROUP3, true),
            new CyCommand(0xA0, "MFR_VIN_MIN", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA1, "MFR_VIN_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA2, "MFR_IIN_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA3, "MFR_PIN_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA4, "MFR_VOUT_MIN", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA5, "MFR_VOUT_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA6, "MFR_IOUT_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA7, "MFR_POUT_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA8, "MFR_TAMBIENT_MAX", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xA9, "MFR_TAMBIENT_MIN", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP3),
            new CyCommand(0xAA, "MFR_EFFICIENCY_LL", CyECmdType.ReadWriteBlock, 14, CyECmdGroup.GROUP3),
            new CyCommand(0xAB, "MFR_EFFICIENCY_HL", CyECmdType.ReadWriteBlock, 14, CyECmdGroup.GROUP3),
            new CyCommand(0xAC, "MFR_PIN_ACCURACY", CyECmdType.ReadWriteByte, 1, CyECmdGroup.GROUP3),
            new CyCommand(0xAD, "IC_DEVICE_ID", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP3, 
                true),
            new CyCommand(0xAE, "IC_DEVICE_REV", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP3, 
                true),
            new CyCommand(0xB0, "USER_DATA_00", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB1, "USER_DATA_01", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB2, "USER_DATA_02", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB3, "USER_DATA_03", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB4, "USER_DATA_04", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB5, "USER_DATA_05", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB6, "USER_DATA_06", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB7, "USER_DATA_07", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB8, "USER_DATA_08", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xB9, "USER_DATA_09", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xBA, "USER_DATA_10", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xBB, "USER_DATA_11", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xBC, "USER_DATA_12", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xBD, "USER_DATA_13", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xBE, "USER_DATA_14", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xBF, "USER_DATA_15", CyECmdType.ReadWriteBlock, DEFAULT_BLOCK_SIZE, CyECmdGroup.GROUP1, 
                true),
            new CyCommand(0xC0, "MFR_MAX_TEMP_1", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0xC1, "MFR_MAX_TEMP_2", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1),
            new CyCommand(0xC2, "MFR_MAX_TEMP_3", CyECmdType.ReadWriteWord, 2, CyECmdGroup.GROUP1)
        };
        #endregion

        public static CyCommand GetSpecDataByCode(int code)
        {
            for (int i = 0; i < PMBusCmdList.Length; i++)
            {
                if (PMBusCmdList[i].m_cmdCode == code)
                    return PMBusCmdList[i];
            }

            return new CyCommand();
        }

        public static int GetIndexByCode(int code)
        {
            for (int i = 0; i < PMBusCmdList.Length; i++)
            {
                if (PMBusCmdList[i].m_cmdCode == code)
                    return i;
            }

            return -1;
        }

        public static object GetCmdGroupByCode(int code)
        {
            for (int i = 0; i < PMBusCmdList.Length; i++)
            {
                if (PMBusCmdList[i].m_cmdCode == code)
                    return PMBusCmdList[i].m_cmdGroup;
            }

            return null;
        }
    }
    #endregion

    public class CyImportExport
    {
        public static char Separator = ',';
        private static string Pattern = "{0}" + Separator + " ";

        #region Export functions
        public static string Export(CyParameters prms, List<object> exportTable, List<string> colHeaders)
        {
            StringBuilder sb = new StringBuilder();
            if (exportTable == null || exportTable.Count == 0) return string.Empty;

            sb.AppendLine(GetHeaders(colHeaders));

            for (int i = 0; i < exportTable.Count; i++)
            {
                if (exportTable[i] is CyCustomTableRow)
                {
                    CyCustomTableRow row = (exportTable[i] as CyCustomTableRow);

                    sb.AppendFormat(Pattern, Convert.ToByte(row.m_enable));
                    sb.AppendFormat(Pattern, row.m_name);
                    sb.AppendFormat(Pattern, CyParameters.CellConvertHex(row.m_code));
                    sb.AppendFormat(Pattern, row.m_type);
                    sb.AppendFormat(Pattern, row.m_format);
                    sb.AppendFormat(Pattern, CyParameters.CellToString(row.m_size));
                    sb.AppendFormat(Pattern, Convert.ToByte(row.m_paged));
                    sb.AppendFormat(Pattern, row.m_numPages);
                    sb.AppendFormat(Pattern, row.m_readConfig);
                    sb.AppendFormat(row.m_writeConfig.ToString());
                }
                else if (exportTable[i] is CyPMBusTableRow)
                {
                    CyPMBusTableRow row = (exportTable[i] as CyPMBusTableRow);

                    sb.AppendFormat(Pattern, Convert.ToByte(row.m_enable));
                    sb.AppendFormat(Pattern, row.Name);
                    sb.AppendFormat(Pattern, CyParameters.CellConvertHex(row.m_code));
                    sb.AppendFormat(Pattern, row.Type);
                    sb.AppendFormat(Pattern, row.m_format);
                    sb.AppendFormat(Pattern, CyParameters.CellToString(row.Size));
                    sb.AppendFormat(Pattern, Convert.ToByte(row.m_paged));
                    sb.AppendFormat(Pattern, row.ReadConfig);
                    sb.AppendFormat(row.WriteConfig.ToString());
                }

                sb.AppendLine();
            }

            return sb.ToString();
        }

        static string GetHeaders(List<string> colHeaders)
        {
            string header = "";
            for (int i = 0; i < colHeaders.Count; i++)
            {
                header += colHeaders[i] + Separator;
            }
            header = header.TrimEnd(Separator);

            return header;
        }
        #endregion

        #region Import functions
        public static bool Import(CyTabWrapper parent, CyParameters prms, string fileContent, bool pasteMode)
        {
            List<object> importedTable = new List<object>();
            List<ICyRow> elements = new List<ICyRow>();

            if (parent is CyCustomCmdsTab)
            {
                importedTable = CyImportExport.ImportTable<CyCustomTableRow>(
                    CyParameters.CustomTableHeader_v2, fileContent, pasteMode, prms);
            }
            else if (parent is CyPmBusCmdsTab)
            {
                importedTable = CyImportExport.ImportTable<CyPMBusTableRow>(
                    CyParameters.PMBusCmdsTableHeader, fileContent, pasteMode, prms);
            }

            if (importedTable != null && importedTable.Count > 0)
            {
                if (importedTable[0].GetType() == typeof(CyCustomTableRow))
                {
                    ICyRow firstSelectedRow = null;
                    if (pasteMode == false)
                    {
                        CyCustomTable table = new CyCustomTable();
                        table.InitializeTable(0);
                        prms.CustomTable = table.m_customTable;
                    }
                    else
                    {
                        firstSelectedRow = parent.DataGridFirstSelectedRow;
                        List<ICyRow> list = new List<ICyRow>(parent.GetObjectsFromDataGrid());
                        if (list != null && list.Count == prms.CustomTable.Count)
                            for (int i = 0; i < list.Count; i++)
                                prms.CustomTable[i] = (CyCustomTableRow)list[i];
                    }

                    // Avoid bootloader commands duplicating. If bootloader commands exist in the import file,
                    // than use them, otherwise use default
                    int bootloaderCmdIndex = 0;
                    for (int currTableIndex = prms.CustomTable.Count - 1; currTableIndex >= 0; currTableIndex--)
                    {
                        CyCustomTableRow currentTableItem = (CyCustomTableRow)prms.CustomTable[currTableIndex];
                        if (CyCustomTable.IsCmdBootloader(currentTableItem.m_name))
                        {
                            for (int j = 0; j < importedTable.Count; j++)
                            {
                                CyCustomTableRow importTableIndex = (CyCustomTableRow)importedTable[j];
                                if (currentTableItem.m_name == importTableIndex.m_name)
                                {
                                    prms.CustomTable.RemoveAt(currTableIndex);
                                    bootloaderCmdIndex = currTableIndex;
                                    break;
                                }
                            }
                        }
                    }

                    for (int i = 0; i < importedTable.Count; i++)
                    {
                        CyCustomTableRow importedRow = ((CyCustomTableRow)importedTable[i]);

                        if (CyCustomTable.IsCmdSpecific(importedRow.m_name) && (pasteMode == false))
                        {
                            // Handle specific commands
                            for (int j = 0; j < prms.CustomTable.Count; j++)
                            {
                                CyCustomTableRow row = prms.CustomTable[j];
                                if (row.m_name == importedRow.m_name)
                                {
                                    row.m_code = importedRow.m_code;
                                    continue;
                                }
                            }
                        }

                        if (pasteMode)
                        {
                            if (firstSelectedRow != null)
                            {
                                int pos = prms.CustomTable.IndexOf((CyCustomTableRow)firstSelectedRow);

                                if (pos < 0)
                                    pos = bootloaderCmdIndex;

                                prms.CustomTable.Insert(pos, importedRow);

                                firstSelectedRow = null;
                                pos++;
                                if (pos < prms.CustomTable.Count)
                                    firstSelectedRow = prms.CustomTable[pos];
                            }
                            else
                                prms.CustomTable.Add(importedRow);

                            // Add to list of rows which will be selected
                            elements.Add(importedRow);

                        }
                        else
                            prms.CustomTable.Add(importedRow);

                    }

                    // Commit Tables
                    prms.SetCustomTable();
                }
                else if (importedTable[0].GetType() == typeof(CyPMBusTableRow))
                {
                    if (pasteMode == false)
                        if (importedTable.Count != prms.PmBusTable.Count)
                        {
                            MessageBox.Show(Resources.ImportRowCountWarning, Resources.DlgWarning,
                                MessageBoxButtons.YesNo);
                        }

                    for (int i = 0; i < importedTable.Count; i++)
                    {
                        foreach (CyPMBusTableRow row in prms.PmBusTable)
                            if (row.m_code == ((CyPMBusTableRow)importedTable[i]).m_code)
                            {
                                row.AssignValues(((CyPMBusTableRow)importedTable[i]));

                                // Add to list of rows which will be selected
                                elements.Add(row);
                            }

                    }

                    // Commit Tables
                    prms.SetPmBusTable();
                }

                parent.UpdateUIFromTable();
                parent.ValidateAllTable();

                // Select paste rows
                if (pasteMode)
                    parent.SelectRows(elements);
            }
            else
                return false;

            return true;
        }

        public static List<object> ImportTable<T>(List<string> columnHeader, string fileContent, bool pasteMode,
            CyParameters parameters) where T : class
        {
            bool oldCustomTableFormat;
            List<string> rows = ValidateTextData(columnHeader, fileContent, out oldCustomTableFormat);

            if (rows.Count == 0) return null;

            List<T> importTable = new List<T>();

            int id = 1;
            while (id < rows.Count)
            {
                T el = (T)Activator.CreateInstance(typeof(T));
                try
                {
                    string[] cells = rows[id].Split(new char[] { Separator }, StringSplitOptions.None);

                    if (typeof(T) == typeof(CyCustomTableRow))
                    {
                        int inc = 0;
                        CyCustomTableRow row = (el as CyCustomTableRow);

                        row.m_enable = CyParameters.CellToBool(cells[inc++].Trim());
                        row.m_name = cells[inc++].Trim();
                        row.m_code = CyParameters.ParseNullableHexByte(cells[inc++].Trim());
                        row.m_type = (CyECmdType)CyEnumConverter.GetEnumValue(
                                cells[inc++].Trim(), typeof(CyECmdType));
                        row.m_format = (CyEFormatType)CyEnumConverter.GetEnumValue(
                                cells[inc++].Trim(), typeof(CyEFormatType));
                        row.m_size = CyParameters.ParseNullableByte(cells[inc++].Trim());
                        row.m_paged = CyParameters.CellToBool(cells[inc++].Trim());
                        // This column was added in version 2.0
                        row.m_numPages = oldCustomTableFormat ? parameters.PagedCommands :
                                                                CyParameters.ParseNullableByte(cells[inc++].Trim());
                        row.m_readConfig = (CyEReadWriteConfigType)CyEnumConverter.GetEnumValue(
                                cells[inc++].Trim(), typeof(CyEReadWriteConfigType));
                        row.m_writeConfig = (CyEReadWriteConfigType)CyEnumConverter.GetEnumValue(
                                cells[inc++].Trim(), typeof(CyEReadWriteConfigType));

                        // Do not mark PAGE and QUERY commands as specific when they are not supported
                        if (CyParameters.ReservedCmdNames.Contains(row.m_name))
                        {
                            row.m_specific = true;

                            if (row.m_name == CyCustomTable.PAGE && parameters.SupportPageCmd == false)
                                row.m_specific = false;

                            if (row.m_name == CyCustomTable.QUERY && parameters.SupportQueryCmd == false)
                                row.m_specific = false;

                            if (CyCustomTable.IsCmdBootloader(row.m_name) && parameters.m_isBootloader == false)
                                row.m_specific = false;
                        }
                    }
                    else if (typeof(T) == typeof(CyPMBusTableRow))
                    {
                        int inc = 0;
                        CyPMBusTableRow row = (el as CyPMBusTableRow);

                        row.m_enable = CyParameters.CellToBool(cells[inc++].Trim());
                        string name = cells[inc++].Trim();
                        byte? code = CyParameters.ParseNullableHexByte(cells[inc++].Trim());
                        if (code == null)
                            continue;

                        row.m_code = (byte)code;

                        inc++;//m_type
                        row.m_format = (CyEFormatType)CyEnumConverter.GetEnumValue(
                                cells[inc++].Trim(), typeof(CyEFormatType));
                        row.Size = CyParameters.ParseNullableByte(cells[inc++].Trim());
                        row.m_paged = CyParameters.CellToBool(cells[inc++].Trim());
                        row.ReadConfig = (CyEReadWriteConfigType)CyEnumConverter.GetEnumValue(
                                cells[inc++].Trim(), typeof(CyEReadWriteConfigType));
                        row.WriteConfig = (CyEReadWriteConfigType)CyEnumConverter.GetEnumValue(
                                cells[inc++].Trim(), typeof(CyEReadWriteConfigType));
                    }
                }
                catch (Exception)
                {
                    return null;
                }

                importTable.Add(el);
                id++;
            }

            if (importTable == null) return null;
            return new List<object>(importTable.ToArray());

        }

        private static List<string> ValidateTextData(List<string> columnHeader, string content,
            out bool oldCustomTableFormat)
        {
            List<string> result = new List<string>();
            oldCustomTableFormat = false;
            try
            {
                string[] rows = content.Split(new string[] { System.Environment.NewLine }, StringSplitOptions.None);

                string[] cells;
                for (int i = 0; i < rows.Length; i++)
                {
                    cells = rows[i].Split(new char[] { Separator }, StringSplitOptions.None);

                    //Stop if empty line occurs
                    if (cells.Length == 1 && cells[0].Trim() == String.Empty)
                        break;

                    if (columnHeader == CyParameters.CustomTableHeader_v2)
                    {
                        if (cells.Length != columnHeader.Count)
                        {
                            if (cells.Length == CyParameters.CustomTableHeader_v1.Count)
                            {
                                oldCustomTableFormat = true;
                            }
                            else
                                throw new Exception(Resources.InvalidDataFormat);
                        }
                    }
                    else
                    {
                        //Validate columns count
                        if (cells.Length != columnHeader.Count)
                            throw new Exception(Resources.InvalidDataFormat);
                    }

                    //Add to results list
                    result.Add(rows[i]);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, CyParameters.GetNamespace(), MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            return result;
        }
        #endregion
    }
}
