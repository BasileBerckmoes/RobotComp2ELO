/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Xml.Serialization;
using System.Xml;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Diagnostics;

namespace ScanComp_v1_10
{
    #region Component Parameters Names
    public class CyParamNames
    {
        // Commpon parameters
        public const string INSTANCE_NAME = "INSTANCE_NAME";
        // General tab parameters
        public const string CLOCK_SOURCE = "ClockSource";
        public const string TIMING_RATE = "TimingRate";
        public const string NEGATIVE_INPUT = "InternalModeExist";
        public const string TIMING_FREQUENCY = "TimingFrequency";
        public const string HW_OUTPUTS_ENABLED = "OutputsEnable";
        public const string SPEED_POWER = "SpeedPower";
        public const string TIMING_TYPE = "TimingType";
        public const string VDAC_RANGE = "VDACRange";
        public const string VOLTAGE_MODE = "VoltageMode";
        public const string FIXED_VOLTAGE_MV = "FixedVoltageMv";
        // Channels tab parameters
        public const string SEQUENCED_CHANNEL = "SequencedChannels";
        public const string CHANNELS_CONFIG_TABLE = "SeqChannelsConfigTable";
    }
    #endregion

    #region Parameters Enums
    // General tab enums
    public enum CyEClockSource { INTERNAL, EXTERNAL }
    public enum CyEScanTimingType { SCAN_RATE, CLOCK_FREQ }
    public enum CyENegativeInput { COMMON, UNIQUE, INTERN }
    public enum CyEVdacRange { VDAC8__Range_1_Volt = 0, VDAC8__Range_4_Volt = 4 }
    public enum CyEVdacVoltageMode { FIXED, PER_CHANNEL }
    public enum CyEScanSpeedType { MEDSPEED, HIGHSPEED, SLOWSPEED, NONE }
    // Channels tab enums
    public enum CyEChannelIntMode
    {
        // If you change/add/remove enum values make sure to change the enum in 
        // the customizer of the base component (primitive)
        [Description("Rising Edge")]
        INTR_RISING,
        [Description("Falling Edge")]
        INTR_FALLING,
        [Description("Both Edges")]
        INTR_BOTH,
        [Description("Disabled")]
        INTR_DISABLE,
        [Description("Level")]
        INTR_LEVEL
    }
    #endregion

    #region Parameters ranges
    public class CyParamRanges
    {
        public const byte NUM_CHANNELS_MIN = 1;
        public const byte NUM_CHANNELS_MAX = 64;

        public const UInt16 UNIT_KILO = 1000;
        public const UInt32 UNIT_MEGA = UNIT_KILO * UNIT_KILO;
        public const UInt32 UNIT_GIGA = UNIT_MEGA * UNIT_KILO;

        public const byte CLOCK_FREQ_KHZ_MIN = 1;
        public const byte CLOCK_FREQ_MHZ_MAX = 10;
        public const byte CLOCK_FREQ_MHZ_1V_MAX = 2;
        public const double CLOCK_FREQ_MHZ_4V_MAX = 0.5;
        public const UInt16 CLOCK_FREQ_HZ_MIN = CLOCK_FREQ_KHZ_MIN * UNIT_KILO;                  // 1 KHz
        public const UInt32 CLOCK_FREQ_HZ_MAX = CLOCK_FREQ_MHZ_MAX * UNIT_MEGA;                  // 10 MHz
        public const UInt32 CLOCK_FREQ_HZ_1V_MAX = CLOCK_FREQ_MHZ_1V_MAX * UNIT_MEGA;            // 2 MHz
        public const UInt32 CLOCK_FREQ_HZ_4V_MAX = (UInt32)(CLOCK_FREQ_MHZ_4V_MAX * UNIT_MEGA);  // 0.5 MHz

        public const UInt16 MEDIUM_SPEED_TIME = 155;    // ns
        public const UInt16 SLOW_SPEED_TIME = 55000;    // ns (55 ms)
        public const UInt16 MEDIUM_SPEED_TIME_P4 = 400; // ns
        public const UInt16 SLOW_SPEED_TIME_P4 = 1000;  // ns

        public const byte VDAC_VOLTAGE_MIN = 0;
        public const UInt16 VDAC_VOLTAGE_1V_MAX = 1020; // mV (1.020 V)
        public const UInt16 VDAC_VOLTAGE_4V_MAX = 4080; // mV (4.080 V)

        public const byte DEFAULT_VDAC_RANGE = 125;
        public const byte VDAC_RANGE_4MV_BIT = 4;
        public const byte VDAC_RANGE_16MV_BIT = 16;
    }
    #endregion

    public class CyParameters
    {
        public const double EPS = 1E-6;
        private const byte HARDWARE_MUX_DELAY = 2;

        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyTerminalQuery_v1 m_termQuery;

        private CyChannelsTab m_channelsTab;

        public static readonly Color DISABLED_COLUMN_COLOR = SystemColors.ControlLight;
        public static readonly Color ENABLED_COLUMN_COLOR = SystemColors.Window;

        // During first getting of parameters this variable is false, what means that assigning
        // values to the form controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        // Table(s) used by the customizer
        private CyChannelsTable m_channelsTable = null;

        // Xml serialization parameters
        public XmlSerializer m_serializerCyChannelsTable;
        public XmlSerializerNamespaces m_customSerializerNamespace;

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;

            m_channelsTable = new CyChannelsTable();

            // Create XML Serializer
            m_serializerCyChannelsTable = new XmlSerializer(typeof(CyChannelsTable));
            m_customSerializerNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(CyParameters).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerializerNamespace.Add("Version", version);

            //Get table
            GetChannelsConfigTable();
        }

        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
            : this(instQuery, null, termQuery)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit, instEdit, termQuery)
        {
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null, null)
        {
        }
        #endregion

        #region Class properties
        // Common properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        public CyChannelsTab ChannelsTab
        {
            get { return m_channelsTab; }
            set { m_channelsTab = value; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public string InstanceName
        {
            get { return GetValue<string>(CyParamNames.INSTANCE_NAME); }
        }

        public bool IsPSoC4
        {
            get { return m_instQuery.DeviceQuery.IsPSoC4; }
        }

        // Properties for Basic tab parameters
        public CyEClockSource ClockSource
        {
            get { return GetValue<CyEClockSource>(CyParamNames.CLOCK_SOURCE); }
            set { SetValue(CyParamNames.CLOCK_SOURCE, value); }
        }

        public CyEScanTimingType ScanTimingType
        {
            get { return GetValue<CyEScanTimingType>(CyParamNames.TIMING_TYPE); }
            set { SetValue(CyParamNames.TIMING_TYPE, value); }
        }

        public double ScanRate
        {
            get { return (double)GetValue<UInt32>(CyParamNames.TIMING_RATE) / (double)CyParamRanges.UNIT_KILO; }
            set { SetValue(CyParamNames.TIMING_RATE, (UInt32)(value * CyParamRanges.UNIT_KILO)); }
        }

        public UInt32 ClockFrequencyHz
        {
            get { return GetValue<UInt32>(CyParamNames.TIMING_FREQUENCY); }
            protected set { SetValue(CyParamNames.TIMING_FREQUENCY, value); } // ensures we set frequency in KHz only
        }

        public double ClockFrequencyKHz
        {
            get { return (double)this.ClockFrequencyHz / (double)CyParamRanges.UNIT_KILO; }
            set { this.ClockFrequencyHz = (UInt32)Math.Round(value * CyParamRanges.UNIT_KILO, 3); }
        }

        public CyENegativeInput NegativeInput
        {
            get { return GetValue<CyENegativeInput>(CyParamNames.NEGATIVE_INPUT); }
            set { SetValue(CyParamNames.NEGATIVE_INPUT, value); }
        }

        public bool OutputsEnable
        {
            get { return GetValue<bool>(CyParamNames.HW_OUTPUTS_ENABLED); }
            set { SetValue(CyParamNames.HW_OUTPUTS_ENABLED, value); }
        }

        public CyEVdacRange VdacRange
        {
            get { return GetValue<CyEVdacRange>(CyParamNames.VDAC_RANGE); }
            set { SetValue(CyParamNames.VDAC_RANGE, value); }
        }

        public CyEVdacVoltageMode VdacVoltageMode
        {
            get { return GetValue<CyEVdacVoltageMode>(CyParamNames.VOLTAGE_MODE); }
            set { SetValue(CyParamNames.VOLTAGE_MODE, value); }
        }

        public UInt16 VdacVoltageMv
        {
            get { return GetValue<UInt16>(CyParamNames.FIXED_VOLTAGE_MV); }
            set { SetValue(CyParamNames.FIXED_VOLTAGE_MV, value); }
        }

        public CyEScanSpeedType ScanSpeed
        {
            get { return GetValue<CyEScanSpeedType>(CyParamNames.SPEED_POWER); }
            set
            {
                if (value != CyEScanSpeedType.NONE)
                    SetValue(CyParamNames.SPEED_POWER, value);
            }
        }

        // Properties for Advanced tab parameters
        public byte SequencedChannels
        {
            get { return GetValue<byte>(CyParamNames.SEQUENCED_CHANNEL); }
            set { SetValue(CyParamNames.SEQUENCED_CHANNEL, value); }
        }

        public CyChannelsTable ChannelsTable
        {
            get { return m_channelsTable; }
            set { m_channelsTable = value; }
        }
        #endregion

        #region Getting/Setting parameters with XML Data
        /// <summary>
        /// Get channels table from component
        /// </summary>
        public void GetChannelsConfigTable()
        {
            string xmlData = GetValue<string>(CyParamNames.CHANNELS_CONFIG_TABLE);
            CyChannelsTable package =
                (CyChannelsTable)Deserialize(xmlData, typeof(CyChannelsTable), this.SequencedChannels);
            ChannelsTable = new CyChannelsTable(package.ChannelsList);
        }

        /// <summary>
        /// Set channels XML to component
        /// </summary>
        public void SetChannelsConfigTable()
        {
            if (m_globalEditMode)
            {
                byte sequencedChannels = this.SequencedChannels;
                CyChannelsTable package = new CyChannelsTable();
                package.ChannelsList = new List<CyChannelsTableRow>(ChannelsTable.ToArray());
                if (sequencedChannels <= package.ChannelsList.Count)
                {
                    package.ChannelsList.RemoveRange(sequencedChannels, package.ChannelsList.Count -
                        sequencedChannels);
                    SetValue(CyParamNames.CHANNELS_CONFIG_TABLE, Serialize(package));
                }
            }
        }
        #endregion

        #region XML Serialization
        public string Serialize(object obj)
        {
            string serializedXml = String.Empty;
            XmlSerializer serializer = (obj is CyChannelsTable) ? m_serializerCyChannelsTable :
                                                                        new XmlSerializer(obj.GetType());
            using (StringWriter sw = new StringWriter(CultureInfo.InvariantCulture))
            {
                serializer.Serialize(sw, obj, m_customSerializerNamespace);
                serializedXml = sw.ToString().Replace(Environment.NewLine, " ");
            }

            return serializedXml;
        }

        public object Deserialize(string serializedXml, Type t, int numOfDefaultRows)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml)) throw new Exception();

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
                    string ver_info = tr.GetAttribute(0);

                    res = m_serializerCyChannelsTable.Deserialize(tr);
                }
            }
            catch
            {
                try
                {
                    res = Activator.CreateInstance(t);
                    ((ICyTable)res).InitializeTable(numOfDefaultRows);
                }
                catch (Exception ex)
                {
                    Debug.Fail(ex.Message);
                }

                if (String.IsNullOrEmpty(serializedXml) == false)
                {
                    Debug.Fail(Resources.SettingsIncorrectValues);
                }
            }
            return res;
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }
        #endregion

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

        #region Service
        /// <summary>
        /// Calculates scan rate basing on clock frequency
        /// </summary>
        /// <param name="clockFrequencyHz"></param>
        /// <returns>Scan rate in kHz</returns>
        public double GetScanRateKHz(double clockFrequencyHz)
        {
            byte sequencedChannels = this.SequencedChannels;
            if (sequencedChannels > 0)
                return ((clockFrequencyHz / HARDWARE_MUX_DELAY / sequencedChannels) / CyParamRanges.UNIT_KILO);
            else
                return 0;
        }

        /// <summary>
        /// Calculates clock frequency basing on scan rate
        /// </summary>
        /// <param name="clockFrequencyHz"></param>
        /// <returns>Clock frequency in KHz</returns>
        public double GetClockFrequencyKHz(double scanRateKHz)
        {
            return (double)(scanRateKHz * HARDWARE_MUX_DELAY * this.SequencedChannels);
        }

        /// <summary>
        /// Gets scan speed mode
        /// </summary>
        /// <param name="clockFrequencyHz">Clock frequency in Hz</param>
        /// <returns>Scan speed mode</returns>
        public CyEScanSpeedType GetScanSpeedMode(double clockFrequencyHz)
        {
            double comparatorFreqHz = clockFrequencyHz / 2;
            double comparatorFreqGHz = comparatorFreqHz / CyParamRanges.UNIT_GIGA;
            double scanTimeNs = (comparatorFreqGHz > 0) ? (1 / comparatorFreqGHz) : 0;

            UInt16 medSpeedTime = CyParamRanges.MEDIUM_SPEED_TIME;
            UInt16 slowSpeedTime = CyParamRanges.SLOW_SPEED_TIME;

            if (this.IsPSoC4)
            {
                medSpeedTime = CyParamRanges.MEDIUM_SPEED_TIME_P4;
                slowSpeedTime = CyParamRanges.SLOW_SPEED_TIME_P4;
            }

            if (scanTimeNs < medSpeedTime)
            {
                return CyEScanSpeedType.HIGHSPEED;
            }
            else if (scanTimeNs >= medSpeedTime && scanTimeNs < slowSpeedTime)
            {
                return CyEScanSpeedType.MEDSPEED;
            }
            else
            {
                return CyEScanSpeedType.SLOWSPEED;
            }
        }

        public UInt16 GetDefaultDACVoltage()
        {
            return (UInt16)(CyParamRanges.DEFAULT_VDAC_RANGE * GetVdacRangeCoeff());
        }

        public UInt16 GetMaxDACVoltage()
        {
            return (this.VdacRange == CyEVdacRange.VDAC8__Range_1_Volt) ?
                CyParamRanges.VDAC_VOLTAGE_1V_MAX : CyParamRanges.VDAC_VOLTAGE_4V_MAX;
        }

        public byte GetDACByteValue(UInt16 vdacVoltage)
        {
            double dacByteValue = (double)(vdacVoltage + GetVdacRangeCoeff() / 2) / GetVdacRangeCoeff();
            return (byte)(dacByteValue > Byte.MaxValue ? Byte.MaxValue : dacByteValue);
        }

        public byte GetVdacRangeCoeff()
        {
            return (byte)(this.VdacRange == CyEVdacRange.VDAC8__Range_1_Volt ?
                CyParamRanges.VDAC_RANGE_4MV_BIT : CyParamRanges.VDAC_RANGE_16MV_BIT);
        }

        /// <summary>
        /// Get clock frequency error 
        /// </summary>
        /// <param name="frequencyInHz"></param>
        /// <returns></returns>
        public string GetClockFrequencyError(double frequencyInHz)
        {
            string errMsg = String.Empty;
            if (CyClock.IsFrequencyKnown(frequencyInHz) == false)
                return errMsg;

            UInt16 minHz = CyParamRanges.CLOCK_FREQ_HZ_MIN;
            byte minKHz = CyParamRanges.CLOCK_FREQ_KHZ_MIN;
            UInt32 maxHz = CyParamRanges.CLOCK_FREQ_HZ_MAX;
            double maxMHz = CyParamRanges.CLOCK_FREQ_MHZ_MAX;

            if (this.NegativeInput == CyENegativeInput.INTERN)
            {
                if (this.VdacRange == CyEVdacRange.VDAC8__Range_1_Volt)
                {
                    maxHz = CyParamRanges.CLOCK_FREQ_HZ_1V_MAX;
                    maxMHz = CyParamRanges.CLOCK_FREQ_MHZ_1V_MAX;
                }
                else
                {
                    maxHz = CyParamRanges.CLOCK_FREQ_HZ_4V_MAX;
                    maxMHz = CyParamRanges.CLOCK_FREQ_MHZ_4V_MAX;
                }
            }

            if (frequencyInHz + CyParameters.EPS <= minHz ||
                frequencyInHz - CyParameters.EPS >= maxHz)
            {
                errMsg = string.Format(Resources.ClockFrequencyErrorMsg, minKHz, maxMHz);
            }
            return errMsg;
        }

        public void UpdateScanSpeed()
        {
            this.ScanSpeed = this.GetScanSpeedMode(this.ClockFrequencyHz);
        }

        public static void SetReadOnlyState(DataGridViewColumn dgvColumn, bool readOnly)
        {
            dgvColumn.DefaultCellStyle.BackColor = readOnly ? DISABLED_COLUMN_COLOR : ENABLED_COLUMN_COLOR;
            dgvColumn.ReadOnly = readOnly;
        }

        public static UInt16 ConvertToUInt16(object value)
        {
            UInt16 result = 0;
            if (value != null)
            {
                if (UInt16.TryParse(value.ToString(), out result))
                    return result;
            }
            return result;
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
        #endregion Service
    }
}
