/*******************************************************************************
* Copyright 2012 - 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;
using System.Reflection;
using System.Diagnostics;

namespace VoltageFaultDetector_v3_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        public const string NUM_VOLTAGES = "NumVoltages";
        public const string COMPARE_TYPE = "CompareType";
        public const string GF_LENGTH = "GfLength";
        public const string SETTLING_DELAY = "SettlingDelay";
        public const string EXTERNAL_REF = "ExternalRef";
        public const string VIN_MUX_OUTPUT_ENABLE = "VinMuxOutput";
        public const string DAC_RANGE = "DacRange";
        public const string PHYSICAL_PLACEMENT = "PhysicalPlacement";
        public const string ANALOG_BUS = "AnalogBus";
        public const string SPEED_MODE = "SpeedMode";
        public const string VOLTAGES_TABLE = "VoltagesTable";

        public const string API_UV_FAULT_THRESHOLD = "UVFaultThreshold";
        public const string API_OV_FAULT_THRESHOLD = "OVFaultThreshold";
        public const string API_UV_FAULT_THRESHOLD_INIT = "initUVFaultThreshold";
        public const string API_OV_FAULT_THRESHOLD_INIT = "initOVFaultThreshold";
        public const string API_VOLTAGE_SCALE = "VoltageScale";
        public const string API_STATUS_MASK = "StatusMask";
        public const string API_COMP_TYPE_REPL_STR = "CompTypeReplStr";
        public const string API_DAC_CM_V_PER_LSB = "DACmVperLSb";
        public const string API_DAC_SHIFTS_LSB = "DACshiftsLSb";
        public const string API_FILT_COUNT_TYPE = "filtCountType";

        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Parameters Ranges
    public class CyParamRanges
    {
        // Basic tab parameters
        public const byte NUM_VOLTAGES_MIN = 1;
        public const byte NUM_VOLTAGES_MAX = 32;
        public const byte GFLENGTH_MIN = 1;
        public const byte GFLENGTH_MAX = 255;
        public const byte SETTLING_DELAY_MIN = 3;
        public const byte SETTLING_DELAY_MAX = 128;

        // Voltages tab parameters
        public const double NOMINAL_VOLTAGE_MIN = 0.01;
        public const double NOMINAL_VOLTAGE_MAX = 65.535;
        public const double UV_FAULT_THRESHOLD_MIN = 0.01;
        public const double UV_FAULT_THRESHOLD_MAX = 65.535;
        public const double OV_FAULT_THRESHOLD_MIN = 0.01;
        public const double OV_FAULT_THRESHOLD_MAX = 65.535;
        public const double INPUT_SCALING_FACTOR_MIN = 0.001;
        public const double INPUT_SCALING_FACTOR_MAX = 1.000;
        public const double OV_FAULT_MULT_SCALE_MAX = 4;
        public const double UV_FAULT_MULT_SCALE_MIN = 0.05;
        public const byte NUM_CYCLE = 16;

        public const double DAC_1V_VOLTAGE = 1.020;
        public const double DAC_4V_VOLTAGE = 4.080;

        public const double DAC_1V_MV_LSB = 4;
        public const double DAC_4V_MV_LSB = 16;
    }
    #endregion

    #region Component Enums
    public enum CyCompareType
    {
        [Description("OV/UV")]
        OV_UV,
        [Description("OV only")]
        OV,
        [Description("UV only")]
        UV
    }
    public enum CyDACRangeType
    {
        [Description("1V")]
        V1,
        [Description("4V")]
        V4
    }
    public enum CyPhysicalPlacementType
    {
        [Description("Comp0")]
        Comp0,
        [Description("Comp1")]
        Comp1,
        [Description("Comp2")]
        Comp2,
        [Description("Comp3")]
        Comp3,
        [Description("Comp0+2")]
        Comp02,
        [Description("Comp1+3")]
        Comp13
    }
    public enum CyAnalogBusType
    {
        [Description("AMUXBUSR")]
        AMUXBUSR = 0,
        [Description("AMUXBUSL")]
        AMUXBUSL = 1,
        [Description("Unconstrained")]
        Unconstrained = 2,
        [Description("AMUXBUS")]
        AMUXBUS = 3
    }
    public enum CySpeedType
    {
        [Description("Low speed")]
        LOW,
        [Description("High speed")]
        HIGH
    }
    #endregion

    public class CyParameters
    {
        public const double EPSILON = 1e-8;

        public const double MAX_CLOCK_FREQ_V1 = 32;
        public const double MAX_CLOCK_FREQ_V4 = 24;

        public const double MIN_SCAN_PER_VOLTAGE_V1 = 1;
        public const double MIN_SCAN_PER_VOLTAGE_V4 = 1.6;

        public const double DAC_RANGE_1V = 1;
        public const double DAC_RANGE_4V = 4;

        // List contains display names of type taken from symbol. It is used to fill combobox.
        
        private List<string> m_filterTypeList;

        // Dictionary is used to keep display names of types taken from symbol,
        // and associate them with the enum fields to simplify access to diaplay names
        private Dictionary<object, string> m_displayNameDict = new Dictionary<object, string>();        
        private Dictionary<string, object> m_restoredParameters = new Dictionary<string, object>();
        private ICyInstQuery_v1 m_inst;                
        private ICyTerminalQuery_v1 m_termQuery;        
        private CyBasicTab m_basicTab;        
        private CyVoltagesTab m_voltagesTab;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        private List<CyVoltagesTableRow> m_voltagesTable;
        private bool m_isVoltagesTableDefault = false;
        private byte m_numOfDefaultRows = 0;

        // Xml serialization parameters
        [XmlIgnore]
        public XmlSerializer m_voltagesTableSerializer;
        [XmlIgnore]
        public XmlSerializer m_parametersSerializer;
        [XmlIgnore]
        public XmlSerializerNamespaces m_customSerNamespace;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;

            // Create XML Serializer
            m_voltagesTableSerializer = new XmlSerializer(typeof(CyVoltagesTable));
            m_parametersSerializer = new XmlSerializer(typeof(CyParameters));
            m_customSerNamespace = new XmlSerializerNamespaces();
            Type classType = typeof(CyParameters);
            string curNamespace = classType.Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);

            GetVoltagesTable();
        }

        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 termQuery)
            : this(inst)
        {
            m_termQuery = termQuery;
        }

        public CyParameters() { }

        #endregion

        #region Class properties
        [XmlIgnore]
        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        public string InstanceName
        {
            get { return GetValue<string>(CyParamNames.INSTANCE_NAME); }
        }

        [XmlIgnore]
        public List<string> FilterTypeList
        {
            get { return m_filterTypeList; }
            set { m_filterTypeList = value; }
        }

        [XmlIgnore]
        public Dictionary<object, string> DisplayNameDict
        {
            get { return m_displayNameDict; }
            set { m_displayNameDict = value; }
        }

        [XmlIgnore]
        public ICyInstQuery_v1 Inst
        {
            get { return m_inst; }
            set { m_inst = value; }
        }

        [XmlIgnore]
        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
            set { m_termQuery = value; }
        }

        [XmlIgnore]
        public CyBasicTab BasicTab
        {
            get { return m_basicTab; }
            set { m_basicTab = value; }
        }

        [XmlIgnore]
        public CyVoltagesTab VoltagesTab
        {
            get { return m_voltagesTab; }
            set { m_voltagesTab = value; }
        }

        public byte NumVoltages
        {
            get { return GetValue<byte>(CyParamNames.NUM_VOLTAGES); }
            set { SetValue(CyParamNames.NUM_VOLTAGES, value); }
        }

        public CyCompareType CompareType
        {
            get { return GetValue<CyCompareType>(CyParamNames.COMPARE_TYPE); }
            set { SetValue(CyParamNames.COMPARE_TYPE, value); }
        }

        public byte GFLength
        {
            get { return GetValue<byte>(CyParamNames.GF_LENGTH); }
            set { SetValue(CyParamNames.GF_LENGTH, value); }
        }

        public bool ExternalRef
        {
            get { return GetValue<bool>(CyParamNames.EXTERNAL_REF); }
            set { SetValue(CyParamNames.EXTERNAL_REF, value); }
        }

        public bool VinMuxEnabled
        {
            get { return GetValue<bool>(CyParamNames.VIN_MUX_OUTPUT_ENABLE); }
            set { SetValue(CyParamNames.VIN_MUX_OUTPUT_ENABLE, value); }
        }

        public CyDACRangeType DACRange
        {
            get { return GetValue<CyDACRangeType>(CyParamNames.DAC_RANGE); }
            set { SetValue(CyParamNames.DAC_RANGE, value); }
        }

        public CyPhysicalPlacementType PhysicalPlacement
        {
            get { return GetValue<CyPhysicalPlacementType>(CyParamNames.PHYSICAL_PLACEMENT); }
            set { SetValue(CyParamNames.PHYSICAL_PLACEMENT, value); }
        }

        public CyAnalogBusType AnalogBus
        {
            get { return GetValue<CyAnalogBusType>(CyParamNames.ANALOG_BUS); }
            set { SetValue(CyParamNames.ANALOG_BUS, value); }
        }

        public CySpeedType SpeedMode
        {
            get { return GetValue<CySpeedType>(CyParamNames.SPEED_MODE); }
            set { SetValue(CyParamNames.SPEED_MODE, value); }
        }

        public List<CyVoltagesTableRow> VoltagesTable
        {
            get { return m_voltagesTable; }
            set { m_voltagesTable = value; }
        }

        public bool IsVoltagesTableDefault
        {
            get { return m_isVoltagesTableDefault; }
            set { m_isVoltagesTableDefault = value; }
        }

        public byte SettlingDelay
        {
            get { return GetValue<byte>(CyParamNames.SETTLING_DELAY); }
            set { SetValue(CyParamNames.SETTLING_DELAY, value); }
        }
        #endregion

        public double CalculateScanPerVoltage(double freq)
        {
            const int NUMBER_OF_VFD_FSM_STATES = 8;

            return (Math.Round((1 / freq) * (NUMBER_OF_VFD_FSM_STATES +
                SettlingDelay - CyParamRanges.SETTLING_DELAY_MIN) * 1000000 + CyParameters.EPSILON, 3));
        }  

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }

        public void GetVoltagesTable()
        {
            string xmlData = GetValue<string>(CyParamNames.VOLTAGES_TABLE);
            m_numOfDefaultRows = this.NumVoltages;
            CyVoltagesTable package = (CyVoltagesTable)Deserialize(xmlData, typeof(CyVoltagesTable));
            m_voltagesTable = package.m_voltagesTable;
        }
        #endregion

        #region Import or paste rows
        public bool Import(Control parent, string fileContent, bool pasteMode)
        {
            List<CyVoltagesTableRow> importedTable = CyImportExport.ImportVoltagesTable(NumVoltages,
                CyVoltagesTableRow.COL_COUNT, fileContent, pasteMode);

            if (importedTable != null)
            {
                if (pasteMode)
                {
                    int lastPasteRow = GetLastPasteRow(importedTable.Count, m_voltagesTab.DataGridActiveRowIndex,
                        NumVoltages);

                    int j = 0;
                    for (int i = m_voltagesTab.DataGridActiveRowIndex; i < lastPasteRow; i++)
                    {
                        VoltagesTable[i] = importedTable[j];
                        j++;
                    }
                    m_voltagesTab.UpdateUIFromTable();
                    m_voltagesTab.SelectRow(lastPasteRow-1);
                }
                else
                {
                    VoltagesTable = new List<CyVoltagesTableRow>(importedTable);
                    m_voltagesTab.UpdateUIFromTable();
                }
                SetVoltagesTable();
            }
            else return false;

            return true;
        }

        private int GetLastPasteRow(int importRowCount, int datagridActiveRowIndex, int gridRowsCount)
        {
            int lastPasteRow;
            if (importRowCount > (gridRowsCount - datagridActiveRowIndex))
            {
                lastPasteRow = datagridActiveRowIndex + (gridRowsCount - datagridActiveRowIndex);
            }
            else
            {
                lastPasteRow = datagridActiveRowIndex + importRowCount;
            }
            return lastPasteRow;
        }
        #endregion

        #region Nullable double operations
        public static double? ParseNullableDouble(string val)
        {
            double? res = null;
            double parsed = 0;
            if (double.TryParse(val, out parsed))
            {
                res = parsed;
            }
            return res;
        }
        public static string NullableDoubleToString(double? val, string format)
        {
            string res = "";
            if (val.HasValue)
                res = val.Value.ToString(format);
            return res;
        }
        public static string CellToString(object cellValue)
        {
            string res = "";
            if (cellValue != null)
                res = cellValue.ToString();
            return res;
        }

        public static double? TrimToMilliVolts(double? value)
        {
            if (value.HasValue)
            {
                return (Math.Round(value.Value * 1000 + CyParameters.EPSILON, MidpointRounding.AwayFromZero) / 1000);
            }
            else
            {
                return null;
            }
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_bGlobalEditMode)
            {
                if ((m_inst is ICyInstEdit_v1) == false) return;

                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet.ToString()))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
            // Saving data after deserialization
            if ((m_bGlobalEditMode == false) && (m_inst == null))
            {
                if (m_restoredParameters.ContainsKey(paramName))
                {
                    Debug.Assert(false);
                    return;
                }
                m_restoredParameters.Add(paramName, value);
            }
        }

        public void SetVoltagesTable()
        {            
            CyVoltagesTable package = new CyVoltagesTable();
            package.m_voltagesTable = new List<CyVoltagesTableRow>(m_voltagesTable);
            package.m_voltagesTable.RemoveRange(NumVoltages, package.m_voltagesTable.Count - NumVoltages);
            SetValue(CyParamNames.VOLTAGES_TABLE, Serialize(package));
        }

        public void RestoreParameters(Dictionary<string, object> restoreList)
        {
            bool prevGlobalEditMode = m_bGlobalEditMode;
            m_bGlobalEditMode = true;
            foreach (string param_name in restoreList.Keys)
            {
                SetValue<object>(param_name, restoreList[param_name]);
            }
            m_bGlobalEditMode = prevGlobalEditMode;
        }

        #endregion

        #region XML Serialization
        public string Serialize(object obj)
        {
            StringBuilder sb = new StringBuilder();

            System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb);
            GetSerializer(obj.GetType()).Serialize(tw, obj, m_customSerNamespace);

            string res = sb.ToString();
            res = res.Replace("\r\n", " ");
            return res;
        }

        public object Deserialize(string serializedXml, Type t)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml)) throw new Exception();

                //Read version information
                XmlReader tr = XmlReader.Create(new StringReader(serializedXml));
                //Remove header <?xml version="1.0" encoding="utf-16" ?> 
                tr.Read();
                tr.Read();
                //Go to first Node with attributes
                while (tr.HasAttributes == false)
                {
                    tr.Read();
                }
                //This version information will be used in future versions of Voltage Fault Detector component.
                string ver_info = tr.GetAttribute(0);

                res = GetSerializer(t).Deserialize(tr);
                SetTableDefault(t, false);
            }
            catch
            {
                res = Activator.CreateInstance(t);

                if (res is ICyTable)
                {
                    if (String.IsNullOrEmpty(serializedXml))
                    {
                        ((ICyTable)res).InitializeTable(m_numOfDefaultRows);
                        SetTableDefault(t, true);
                    }
                    else
                    {
                        MessageBox.Show(Resources.SettingsIncorrectValues,
                            Resources.MsgWarningTitle, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
                else
                    res = null;
            }
            return res;
        }

        XmlSerializer GetSerializer(Type t)
        {
            if (t == typeof(CyVoltagesTable))
            {
                return m_voltagesTableSerializer;
            }
            if (t == typeof(CyParameters))
            {
                return m_parametersSerializer;
            }

            return null;
        }

        void SetTableDefault(Type t, bool isDefault)
        {
            if (t == typeof(CyVoltagesTable))
                m_isVoltagesTableDefault = isDefault;
        }

        public void LoadAllParametersFromFile(string fileContent)
        {
            CyParameters imported = (CyParameters)Deserialize(fileContent, typeof(CyParameters));
            if (imported == null)
            {
                MessageBox.Show(Resources.LoadCondigErrorMsg,
                            Resources.MsgErrorTitle, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                try
                {
                    bool prevGlobalEditMode = m_bGlobalEditMode;
                    m_bGlobalEditMode = true;

                    RestoreParameters(imported.m_restoredParameters);

                    VoltagesTable = imported.VoltagesTable;

                    m_bGlobalEditMode = false;

                    //Update tabs
                    m_basicTab.UpdateUI();
                    m_voltagesTab.UpdateUIFromTable();

                    m_bGlobalEditMode = true;

                    //Commit Tables
                    SetVoltagesTable();
                    GetVoltagesTable();

                    m_bGlobalEditMode = prevGlobalEditMode;
                }
                catch
                {
                    m_bGlobalEditMode = true;
                    MessageBox.Show(Resources.LoadCondigParamsErrorMsg,
                          Resources.MsgErrorTitle, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
        #endregion

        #region DRCs
        public bool CheckTableNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < NumVoltages; i++)
            {
                if (((VoltagesTable[i].UvFaultThreshold == null) && (CompareType != CyCompareType.OV)) ||
                    ((VoltagesTable[i].OvFaultThreshold == null) && (CompareType != CyCompareType.UV)) ||
                    ((VoltagesTable[i].InputScalingFactor == null) && ExternalRef == false))
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }

        public bool CheckSiliconRevision(ICyDeviceQuery_v1 deviceQuery)
        {
            const int CHIP_REV_PSOC5A = 1;
            bool res = true;
            if (deviceQuery.IsPSoC5 && deviceQuery.SiliconRevisionAvailable && 
                deviceQuery.SiliconRevision == CHIP_REV_PSOC5A)
            {
                res = false;
            }
            return res;
        }
        #endregion

        #region Clock functions
        // Returns connected to component pin external clock value
        public static CyClockData GetExternalClock(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = new List<CyClockData>();
            clkdata = termQuery.GetClockData("clock", 0);
            if (clkdata.Count == 1)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0];
                }
            }
            return null;
        }

        public static double ConvertFreqToHz(CyClockData clock)
        {
            double frequency = clock.Frequency;
            switch (clock.Unit)
            {
                case CyClockUnit.kHz:
                    frequency *= 1000;
                    break;
                case CyClockUnit.MHz:
                    frequency *= 1000000;
                    break;
                case CyClockUnit.GHz:
                    frequency *= 1000000000;
                    break;
                case CyClockUnit.THz:
                    frequency *= 1000000000000;
                    break;
                default:
                    break;
            }
            return frequency;
        }

        public void UpdateClock(ICyInstQuery_v1 edit, ICyTerminalQuery_v1 termQuery)
        {
            CyClockData clkData = CyParameters.GetExternalClock(termQuery);
            if (clkData != null)
            {
                double freq = ConvertFreqToHz(clkData);
                m_basicTab.UpdateScanPerVoltageLabel(freq);
                m_basicTab.UpdateTotalScanRateLabel(freq);
            }
            else
            {
                m_basicTab.UpdateScanPerVoltageLabel(null);
                m_basicTab.UpdateTotalScanRateLabel(null);                
            }
            m_basicTab.SetMaxClockValueWarning(CheckMinScanPerVoltageValueDRC(termQuery, DACRange, ExternalRef), DACRange);
        }

        public bool CheckMinScanPerVoltageValueDRC(ICyTerminalQuery_v1 termQuery, CyDACRangeType dacRange, bool extRef)
        {
            bool res = true;
            CyClockData clkData = CyParameters.GetExternalClock(termQuery);
            if (clkData != null)
            {
                double scanPerVoltage = CalculateScanPerVoltage(ConvertFreqToHz(clkData));

                if ((((DACRange == CyDACRangeType.V1) && (scanPerVoltage < MIN_SCAN_PER_VOLTAGE_V1)) ||
                    ((DACRange == CyDACRangeType.V4) && (scanPerVoltage < MIN_SCAN_PER_VOLTAGE_V4))) && !extRef)
                {
                    res = false;
                }
            }
            return res;
        }

        public static string GetWarningMaxClockMsg(bool isOk, CyDACRangeType dacRange)
        {
            string msg = "";
            if (!isOk)
            {
                if (dacRange == CyDACRangeType.V1)
                    msg = String.Format(Resources.ScanPerVoltageError, MIN_SCAN_PER_VOLTAGE_V1, DAC_RANGE_1V);
                else
                    msg = String.Format(Resources.ScanPerVoltageError, MIN_SCAN_PER_VOLTAGE_V4, DAC_RANGE_4V);
            }
            return msg;
        }
        #endregion
    }
}
