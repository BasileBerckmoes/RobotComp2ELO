/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Drawing;
using System.Diagnostics;

namespace PowerMonitor_P4_v2_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        public const string NUM_CONVERTERS = "NumConverters";
        public const string ADCCLOCKDIVIDER = "AdcClockDivider";
        public const string ADCCLOCKSELECT = "AdcClockSelect";
        public const string ADC_RANGE = "AdcVoltageRange";
        public const string ADCACLOCK = "AdcAClock";
        public const string ADCBCLOCK = "AdcBClock";
        public const string ADCCCLOCK = "AdcCClock";
        public const string ADCDCLOCK = "AdcDClock";
        public const string PGOOD_CONFIG = "PgoodConfig";

        public const string FAULT_SOURCES_OV = "FaultSources_OV";
        public const string FAULT_SOURCES_UV = "FaultSources_UV";
        public const string WARN_SOURCES_OV = "WarnSources_OV";
        public const string WARN_SOURCES_UV = "WarnSources_UV";

        public const string VOLTAGES_TABLE = "VoltagesTable";
        
        public static readonly string[] V_SINGLE_ENDED = new string[CyParamRanges.NUM_CONVERTERS_MAX] 
        { 
            "V1SingleEnded", "V2SingleEnded", "V3SingleEnded", "V4SingleEnded",
            "V5SingleEnded", "V6SingleEnded", "V7SingleEnded", "V8SingleEnded"//,
            //"V9SingleEnded", "V10SingleEnded", "V11SingleEnded", "V12SingleEnded",
            //"V13SingleEnded", "V14SingleEnded", "V15SingleEnded", "V16SingleEnded",
            //"V17SingleEnded", "V18SingleEnded", "V19SingleEnded", "V20SingleEnded",
            //"V21SingleEnded", "V22SingleEnded", "V23SingleEnded", "V24SingleEnded",
            //"V25SingleEnded", "V26SingleEnded", "V27SingleEnded", "V28SingleEnded",
            //"V29SingleEnded", "V30SingleEnded", "V31SingleEnded", "V32SingleEnded"
        };

        public const string INSTANCE_NAME = "INSTANCE_NAME";

        public const string ENABLE_DMA = "EnableDma";
        public const string EXPOSE_SOC = "ExposeSoc";
        public const string SAMPLES_AVERAGED = "SamplesAveraged";

        public const string VOLTAGE_INPUT_RANGE = "VoltageInputRange";
        public const string VREF_SELECT = "VrefSelect";
        public const string VREF_VALUE = "VrefValue_mV";

        public const string DMA_PRESENT = "DmacPresent";
        public const string UDB_PRESENT = "UdbPresent";

        public const string ADC_CLK_LOCAL = "AdcClockSelectLocal";
        public const string ADC_SCAN_TIME = "AdcScanTime";
        public const string RSP_TIME = "RspTime";

        public const string PART_NUMBER_CY8C41 = "CY8C41";
        public const string PSOC4AS2_ARCH_FAMILY = "PSoC4_10";

        #region Param names v1.0 unused 
        public const string CURRENTS_TABLE = "CurrentsTable";
        public const string AUXILIARY_TABLE = "AuxiliaryTable";

        public const string FAULT_SOURCES_OC = "FaultSources_OC";
        public const string WARN_SOURCES_OC = "WarnSources_OC";

        public const string AUX_FILTER_TYPE = "AuxFilterType";
        public const string CURRENT_FILTER_TYPE = "CurrentFilterType";
        public const string NUM_AUX_CHANNELS = "NumAuxChannels";
        public const string DIFF_CURRENT_RANGE = "DiffCurrentRange";
        public const string EXPOSE_CAL_PIN = "ExposeCalPin";
        public const string INPUT_BUFFER_MODE = "Voltage_Input_Buffer_Mode";
        public const string SYMBOL_B_VISIBLE = "SymbolBVisible";
        public const string VOLTAGE_FILTER_TYPE = "VoltageFilterType";
        public const string LOW_VOLTAGE_MODE = "SEVoltageRange";

        public static readonly string[] I_CSA = new string[CyParamRanges.NUM_CONVERTERS_MAX] 
        { 
            "I1CSA", "I2CSA", "I3CSA", "I4CSA",
            "I5CSA", "I6CSA", "I7CSA", "I8CSA",
            //"I9CSA", "I10CSA", "I11CSA", "I12CSA",
            //"I13CSA", "I14CSA", "I15CSA", "I16CSA",
            //"I17CSA", "I18CSA", "I19CSA", "I20CSA",
            //"I21CSA", "I22CSA", "I23CSA", "I24CSA",
           // "I25CSA", "I26CSA", "I27CSA", "I28CSA",
            //"I29CSA", "I30CSA", "I31CSA", "I32CSA"
        };

        public static readonly string[] AUX_SINGLE_ENDED = new string[CyParamRanges.NUM_AUX_CHANNELS_MAX]
        { 
            "Aux1SingleEnded", "Aux2SingleEnded", "Aux3SingleEnded", "Aux4SingleEnded"
        };
        #endregion
    }
    #endregion

    #region Parameters Ranges
    public class CyParamRanges
    {
        public const byte MAX_PINS_IN_SYSTEM = 48;

        // Basic tab parameters
        public const byte NUM_CONVERTERS_MIN = 1;
        public const byte NUM_CONVERTERS_MAX = 8;
        public const byte NUM_AUX_CHANNELS_MIN = 0;
        public const byte NUM_AUX_CHANNELS_MAX = 4;

        // Voltages tab parameters
        public const double NOMINAL_OUTPUT_VOLTAGE_MIN = 0.001;
        public const double NOMINAL_OUTPUT_VOLTAGE_MAX = 65.535;
        public const double UV_FAULT_TRESHOLD_MIN = 0.001;
        public const double UV_FAULT_TRESHOLD_MAX = 65.535;
        public const double UV_WARNING_TRESHOLD_MIN = 0.001;
        public const double UV_WARNING_TRESHOLD_MAX = 65.535;
        public const double OV_FAULT_TRESHOLD_MIN = 0.001;
        public const double OV_FAULT_TRESHOLD_MAX = 65.535;
        public const double OV_WARNING_TRESHOLD_MIN = 0.001;
        public const double OV_WARNING_TRESHOLD_MAX = 65.535;
        public const double INPUT_SCALING_FACTOR_MIN = 0.001;
        public const double INPUT_SCALING_FACTOR_MAX = 1.000;
        public const double OV_FAULT_MULT_SCALE_2048 = 2.048;
        public const double OV_FAULT_MULT_SCALE_4096 = 4.096;
        public const double UV_FAULT_MULT_SCALE_MIN = 0.05;
        public const double DIRECT_MODE_LIMIT = 1;
        public const int ADC_VREF_MIN_MV = 1000;
        public const int ADC_VREF_MAX_MV = 5500;
        public const decimal ADC_VREF_MIN_V = 1.000m;
        public const decimal ADC_VREF_MAX_V = 5.500m;
        public const double DEFAULT_SETTLING_TIME_NS = 2000; // Rounded version of 9 * T where T = (10k ohm resistive divider + 2k ohm input resistance) * (8uF SAR cap + 10uF trace+input cap)



        // Currents tab parameters
        public const double OC_FAULT_TRESHOLD_MIN = 0.001;
        public const double OC_FAULT_TRESHOLD_MAX = 655.35;
        public const double OC_WARNING_TRESHOLD_MIN = 0.001;
        public const double OC_WARNING_TRESHOLD_MAX = 655.35;
        public const double SHUNT_RESISTOR_MIN = 0.01;
        public const double SHUNT_RESISTOR_MAX = 2500;
        public const double CSA_GAIN_MIN = 1;
        public const double CSA_GAIN_MAX = 500;
        public const double ADC_RANGE_64 = 64;
        public const double ADC_RANGE_128 = 128;

        public const double ADC_RANGE_CSA_CHECK_4V = 4096;
        public const double ADC_RANGE_CSA_CHECK_2V = 2048;

        public const double ADC_COUNT_MAX = 4096;
    }
    #endregion

    #region Component Enums
    public enum CyEPgoodType
    {
        [Description("Global")] global,
        [Description("Individual")] individual,
        [Description("None")] pgood_hidden,
    } 

    public enum CyEEOCConfiguration
    {
        [Description("Per Sample")] Per_Sample,
        [Description("Complete Cycle")] Complete_Cycle
    }

    public enum CyESamples 
    {
        [Description("None")] SampAverage_1 = 1,
        [Description("2 samples")] SampAverage_2 = 2,
        [Description("4 samples")] SampAverage_4 = 4,
        [Description("8 samples")] SampAverage_8 = 8,
        [Description("16 samples")] SampAverage_16 = 16,
        [Description("32 samples")] SampAverage_32 = 32,
        [Description("64 samples")] SampAverage_64 = 64,
        [Description("128 samples")] SampAverage_128 = 128,
        [Description("256 samples")] SampAverage_256 = 256 
    }

    public enum CyEVoltageInputRange
    {
        [Description("0-1.024 V")] VinRange_1024mV,
        [Description("0-2.048 V")] VinRange_2048mV
    }

    public enum CyEVrefDisplay
    {
        [Description("Internal vref")]
        Vref_Internal = 4,
        [Description("Internal vref, bypassed")]
        Vref_InternalBypass = 5,
        [Description("External vref")]
        Vref_External = 7
    }

    public enum CyEVrefSelect
    {
        [Description("Internal 1.024V")] Vref_1024mV = 2,
        [Description("Internal 1.024V, bypassed")] Vref_1024mVBypass = 3,
        [Description("Internal vref")] Vref_Internal = 4,
        [Description("Internal vref, bypassed")] Vref_InternalBypass = 5,
        [Description("External vref")] Vref_External = 7
    }

    #region Unused v1.0 Enums 
    public enum CyEFilterType { None, Average_4, Average_8, Average_16, Average_32 }
    
    public enum CyEVType { SingleEnded, Differential }
    public enum CyEVInternalType
    {
        [Description("Single Ended")]
        SingleEnded,
        //[Description("Differential")]
        //Differential
    }
    public enum CyECurrentMeasurementInternalType
    {
        [Description("None")]
        None,
        [Description("Direct")]
        Direct,
        [Description("CSA")]
        CSA
    }
    public enum CyEAdcRangeInternalType
    {
        [Description("Single Ended: 0-4.096 V")]
        SignleEnded_4V,
        [Description("Single Ended: 0-2.048 V")]
        SignleEnded_2V,
        [Description("Differential: +/- 64 mV")]
        Differential_64mV,
        [Description("Differential: +/- 2.048 V")]
        Differential_2048mV,
        [Description("Differential: +/- 128 mV")]
        Differential_128mV
    }
    public enum CyEDiffCurrentRangeType
    {
        [Description("+/- 64 mV Range")]
        Range_64mV,
        [Description("+/- 128 mV Range")]
        Range_128mV
    }

    public enum CyELowVoltageMode
    {
        [Description("0-2.048 V Range")]
        Range_2048mV,
        [Description("0-4.096 V Range")]
        Range_4096mV
    }

    public enum CyEInputBufferMode
    {
        [Description("Bypass Buffer")]
        ADC_DelSig__Bypass_Buffer,
        [Description("Rail to Rail")]
        ADC_DelSig__Rail_to_Rail,
        [Description("Level Shift")]
        ADC_DelSig__Level_Shift
    }
    #endregion
    #endregion

    public class CyParameters
    {
        [XmlIgnore]
        public static DataGridViewCellStyle DGDisabledStyle;
        [XmlIgnore]
        public static DataGridViewCellStyle DGDisabledCenteredStyle;
        [XmlIgnore]
        public static DataGridViewCellStyle DGEnabledStyle;

        // List contains display names of type taken from symbol. It is used to fill combobox.
        [XmlIgnore]
        public List<string> m_filterTypeList;
        [XmlIgnore]
        public List<string> m_diffCurrentRangeList;

        // Dictionary is used to keep display names of types taken from symbol,
        // and associate them with the enum fields to simplify access to diaplay names
        [XmlIgnore]
        public Dictionary<object, string> m_displayNameDict = new Dictionary<object, string>();

        [XmlIgnore]
        private Dictionary<string, object> m_restoredParameters = new Dictionary<string, object>();

        [XmlIgnore]
        public ICyInstQuery_v1 m_inst;
        [XmlIgnore]
        public ICyTerminalQuery_v1 m_term;
        [XmlIgnore]
        public CyGeneralTab m_generalTab;
        [XmlIgnore]
        public CyVoltagesTab m_voltagesTab;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        private List<CyVoltagesTableRow> m_voltagesTable;
        private bool m_isVoltagesTableDefault = false;
        private byte m_numOfDefaultRows = 0;
        private uint? m_vrefValue = null;

        public string ADC_PATH = "ADC";
        public string DATAPATH_COMP_PATH = "HwComp";
        public string ADC_CLK = "aclk";
        public string DATAPATH_COMP_CLK = "clock";

        public double ChipVdda = 5.5;

        XmlSerializerNamespaces m_customNamespace;
        XmlSerializer m_voltagesSerializer = new XmlSerializer(typeof(CyVoltagesTable));
        XmlSerializer m_parametersSerializer = new XmlSerializer(typeof(CyParameters));

        #region Constructor(s)
        public CyParameters() { }
        public CyParameters(ICyInstQuery_v1 inst)
            : this(inst, null)
        {
        }
        
        /// <summary>
        /// Set up symbol parameter object with only instance and terminal queries.
        /// </summary>
        /// <param name="instQuery">Instance query interface</param>
        /// <param name="termQuery">Terminal query interface</param>
        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 term)
        {
        
            m_inst = inst;
            m_term = term;

            //Custom namespaces for serialization
            m_customNamespace = new XmlSerializerNamespaces();
            m_customNamespace.Add("version", "v1.0");

            m_filterTypeList = new List<string>(inst.GetPossibleEnumValues(CyParamNames.VOLTAGE_FILTER_TYPE));
            m_diffCurrentRangeList = new List<string>(inst.GetPossibleEnumValues(CyParamNames.DIFF_CURRENT_RANGE));
            CyDictParser.FillDictionary(ref m_displayNameDict, typeof(CyEFilterType), m_filterTypeList);
            CyDictParser.FillDictionary(ref m_displayNameDict, typeof(CyEDiffCurrentRangeType), m_diffCurrentRangeList);
            GetVoltagesTable();

            if(inst.VoltageQuery == null)
            {
                ChipVdda = 3.3;
            }
            else
            {
                ChipVdda = inst.VoltageQuery.VDDA;
            }
        }

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

        public double CyVersion
        {
            get {
                double version;
                version = Convert.ToDouble(GetValue<string>("CY_MAJOR_VERSION")) +
                    Convert.ToDouble(GetValue<string>("CY_MINOR_VERSION"))/100.0;
                return version;
            }
        }

        public byte NumConverters
        {
            get
            {
                return GetValue<byte>(CyParamNames.NUM_CONVERTERS);
            }
            set
            {
                SetValue(CyParamNames.NUM_CONVERTERS, value);
            }
        }

        public CyEPgoodType PgoodConfig
        {
            get
            {
                return GetValue<CyEPgoodType>(CyParamNames.PGOOD_CONFIG);
            }
            set
            {
                SetValue(CyParamNames.PGOOD_CONFIG, value);
            }
        }

        public bool FaultSourcesOV
        {
            get
            {
                return GetValue<bool>(CyParamNames.FAULT_SOURCES_OV);
            }
            set
            {
                SetValue(CyParamNames.FAULT_SOURCES_OV, value);
            }
        }

        public bool FaultSourcesUV
        {
            get
            {
                return GetValue<bool>(CyParamNames.FAULT_SOURCES_UV);
            }
            set
            {
                SetValue(CyParamNames.FAULT_SOURCES_UV, value);
            }
        }

        public bool WarningSourcesOV
        {
            get
            {
                return GetValue<bool>(CyParamNames.WARN_SOURCES_OV);
            }
            set
            {
                SetValue(CyParamNames.WARN_SOURCES_OV, value);
            }
        }

        public bool WarningSourcesUV
        {
            get
            {
                return GetValue<bool>(CyParamNames.WARN_SOURCES_UV);
            }
            set
            {
                SetValue(CyParamNames.WARN_SOURCES_UV, value);
            }
        }

        public List<CyVoltagesTableRow> VoltagesTable
        {
            get { return m_voltagesTable; }
            set { m_voltagesTable = value; }
        }

        [XmlIgnore]
        public bool IsVoltagesTableDefault
        {
            get { return m_isVoltagesTableDefault; }
            set { m_isVoltagesTableDefault = value; }
        }

        public bool EnableDMA
        {
            get
            {
                return GetValue<bool>(CyParamNames.ENABLE_DMA);
            }
            set
            {
                SetValue(CyParamNames.ENABLE_DMA, value);
            }
        }

        public bool DmacPresent
        {
            get
            {
                return GetValue<bool>(CyParamNames.DMA_PRESENT);
            }
        }

        public bool UdbPresent
        {
            get
            {
                return GetValue<bool>(CyParamNames.UDB_PRESENT);
            }
        }

        public bool ExposeSOC
        {
            get
            {
                return GetValue<bool>(CyParamNames.EXPOSE_SOC);
            }
            set
            {
                SetValue(CyParamNames.EXPOSE_SOC, value);
            }
        }

        public CyESamples SamplesAveraged
        {
            get
            {
                return GetValue<CyESamples>(CyParamNames.SAMPLES_AVERAGED);
            }
            set
            {
                SetValue(CyParamNames.SAMPLES_AVERAGED, value);
            }
        }

        public CyEVoltageInputRange VoltageInputRange
        {
            get
            {
                return GetValue<CyEVoltageInputRange>(CyParamNames.VOLTAGE_INPUT_RANGE);
            }
            set
            {
                SetValue(CyParamNames.VOLTAGE_INPUT_RANGE, value);
            }
        }

        public CyEVrefSelect VrefSelect
        {
            get
            {
                return GetValue<CyEVrefSelect>(CyParamNames.VREF_SELECT);
            }
            set
            {
                SetValue(CyParamNames.VREF_SELECT, value);
            }
        }

        public Decimal VrefValue
        {
            get
            {
                switch (VrefSelect)
                {
                    case CyEVrefSelect.Vref_1024mV:
                    case CyEVrefSelect.Vref_1024mVBypass:
                        VrefValue = 1.024m;
                        break;
                    case CyEVrefSelect.Vref_Internal:
                    case CyEVrefSelect.Vref_InternalBypass:
                        VrefValue = 1.200m;
                        break;
                    default:
                        m_vrefValue = GetValue<uint>(CyParamNames.VREF_VALUE);
                        if (m_vrefValue < CyParamRanges.ADC_VREF_MIN_MV) VrefValue =
                            CyParamRanges.ADC_VREF_MIN_V;
                        if (m_vrefValue > CyParamRanges.ADC_VREF_MAX_MV) VrefValue =
                            CyParamRanges.ADC_VREF_MAX_V;
                        break;
                }
                return Convert.ToDecimal(m_vrefValue / 1000.0);
            }
            set
            {
                m_vrefValue = (uint)(value * 1000);
                SetValue(CyParamNames.VREF_VALUE, m_vrefValue);
            }
        }

        public int AdcClockDivider
        {
            get
            {
                return GetValue<byte>(CyParamNames.ADCCLOCKDIVIDER);
            }
            set
            {
                SetValue(CyParamNames.ADCCLOCKDIVIDER, value);
            }
        }

        public int AdcAClock
        {
            get
            {
                return GetValue<int>(CyParamNames.ADCACLOCK);
            }
            set
            {
                SetValue(CyParamNames.ADCACLOCK, value);
            }
        }

        public int AdcBClock
        {
            get
            {
                return GetValue<int>(CyParamNames.ADCBCLOCK);
            }
            set
            {
                SetValue(CyParamNames.ADCBCLOCK, value);
            }
        }

        public int AdcCClock
        {
            get
            {
                return GetValue<int>(CyParamNames.ADCCCLOCK);
            }
            set
            {
                SetValue(CyParamNames.ADCCCLOCK, value);
            }
        }

        public int AdcDClock
        {
            get
            {
                return GetValue<int>(CyParamNames.ADCDCLOCK);
            }
            set
            {
                SetValue(CyParamNames.ADCDCLOCK, value);
            }
        }

        public string AdcClockSelect
        {
            get
            {
                return GetValue<string>(CyParamNames.ADCCLOCKSELECT);
            }
            set
            {
                SetValue(CyParamNames.ADCCLOCKSELECT, value);
            }
        }

        public Decimal AdcVoltageRange
        {
            get
            {
                return Convert.ToDecimal(GetValue<uint>(CyParamNames.ADC_RANGE) / 1000.0);
            }
            set
            {
                SetValue(CyParamNames.ADC_RANGE, (uint)(value * 1000));
            }
        }

        public int AdcScanTime
        {
            /* In ns */
            get
            {
                return Convert.ToInt32(GetValue<int>(CyParamNames.ADC_SCAN_TIME));
            }
            set
            {
                SetValue(CyParamNames.ADC_SCAN_TIME, value);
            }
        }

        public int RspTime
        {
            /* In ns */
            get
            {
                return Convert.ToInt32(GetValue<int>(CyParamNames.RSP_TIME));
            }
            set
            {
                SetValue(CyParamNames.RSP_TIME, value);
            }
        }

        public string AdcClockSelectLocal
        {
            get { return GetValue<string>(CyParamNames.ADC_CLK_LOCAL); } 
        }

        #region Unused v1.0 Parameter Class Properties 
        public byte NumAuxChannels
        {
            get
            {
                return GetValue<byte>(CyParamNames.NUM_AUX_CHANNELS);
            }
            set
            {
                SetValue(CyParamNames.NUM_AUX_CHANNELS, value);
            }
        }

        public CyEFilterType VoltageFilterType
        {
            get
            {
                return GetValue<CyEFilterType>(CyParamNames.VOLTAGE_FILTER_TYPE);
            }
            set
            {
                SetValue(CyParamNames.VOLTAGE_FILTER_TYPE, value);
            }
        }

        public CyEFilterType CurrentFilterType
        {
            get
            {
                return GetValue<CyEFilterType>(CyParamNames.CURRENT_FILTER_TYPE);
            }
            set
            {
                SetValue(CyParamNames.CURRENT_FILTER_TYPE, value);
            }
        }

        public CyEFilterType AuxFilterType
        {
            get
            {
                return GetValue<CyEFilterType>(CyParamNames.AUX_FILTER_TYPE);
            }
            set
            {
                SetValue(CyParamNames.AUX_FILTER_TYPE, value);
            }
        }

        public CyEDiffCurrentRangeType DiffCurrentRange
        {
            get
            {
                CyEDiffCurrentRangeType result = GetValue<CyEDiffCurrentRangeType>(CyParamNames.DIFF_CURRENT_RANGE);
                return result;
            }
            set
            {
                SetValue(CyParamNames.DIFF_CURRENT_RANGE, value);
            }
        }

        public double GetCurrentRange()
        {
            return DiffCurrentRange == CyEDiffCurrentRangeType.Range_64mV ? CyParamRanges.ADC_RANGE_64 :
                CyParamRanges.ADC_RANGE_128;
        }

        public CyELowVoltageMode LowVoltageMode
        {
            get
            {
                return GetValue<CyELowVoltageMode>(CyParamNames.LOW_VOLTAGE_MODE);
            }
            set
            {
                SetValue(CyParamNames.LOW_VOLTAGE_MODE, value);
            }
        }

        public bool FaultSourcesOC
        {
            get
            {
                return GetValue<bool>(CyParamNames.FAULT_SOURCES_OC);
            }
            set
            {
                SetValue(CyParamNames.FAULT_SOURCES_OC, value);
            }
        }

        public bool WarningSourcesOC
        {
            get
            {
                return GetValue<bool>(CyParamNames.WARN_SOURCES_OC);
            }
            set
            {
                SetValue(CyParamNames.WARN_SOURCES_OC, value);
            }
        }

        public CyEInputBufferMode InputBufferMode
        {
            get { return GetValue<CyEInputBufferMode>(CyParamNames.INPUT_BUFFER_MODE); }
            set { SetValue(CyParamNames.INPUT_BUFFER_MODE, value); }
        }
        
        #endregion
        #endregion

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
        #endregion

        #region Getting/Setting parameters with XML Data
        public void GetVoltagesTable()
        {
            string xmlData = GetValue<string>(CyParamNames.VOLTAGES_TABLE);
            m_numOfDefaultRows = this.NumConverters;
            CyVoltagesTable package = (CyVoltagesTable)Deserialize(xmlData, typeof(CyVoltagesTable));
            m_voltagesTable = package.m_voltagesTable;
        }

        public void SetVoltagesTable() { SetVoltagesTable(true); }
        public void SetVoltagesTable(bool termVisibilityUpdate)
        {
            if (m_bGlobalEditMode)
            {
                CyVoltagesTable package = new CyVoltagesTable();
                package.m_voltagesTable = new List<CyVoltagesTableRow>(m_voltagesTable.ToArray());
                package.m_voltagesTable.RemoveRange(NumConverters, package.m_voltagesTable.Count - NumConverters);

                SetValue(CyParamNames.VOLTAGES_TABLE, Serialize(package));
                //if (termVisibilityUpdate)
                 //   SetVoltagesTerminalsVisibility(package.m_voltagesTable.Count);
            }
        }
        #endregion

        #region Import or paste rows
        public bool Import(Control parent, string fileContent, bool pasteMode)
        {
            if (parent is CyVoltagesTab)
            {
                List<CyVoltagesTableRow> importedTable = CyImportExport.ImportVoltagesTable(NumConverters,
                    CyVoltagesTableRow.COL_COUNT, fileContent, pasteMode);

                if (importedTable != null)
                {
                    int firstPasteRow = -1;
                    int lastPasteRow = -1;
                    if (pasteMode)
                    {
                        firstPasteRow = m_voltagesTab.DataGridFirstSelectedRow;
                        lastPasteRow = GetLastPasteRow(importedTable.Count, firstPasteRow, NumConverters);

                        int j = 0;
                        for (int i = firstPasteRow; i < lastPasteRow; i++)
                        {
                            VoltagesTable[i] = importedTable[j];
                            j++;
                        }
                    }
                    else
                    {
                        VoltagesTable = importedTable;
                    }
                    m_generalTab.SyncTables();
                    m_voltagesTab.UpdateUIFromTable();
                    SetVoltagesTable(false);
                    m_voltagesTab.ValidateAllCells();
                    m_voltagesTab.SelectDataGridViewRows(firstPasteRow, lastPasteRow - 1);
                }
                else return false;
            }
            
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
            GetSerializer(obj.GetType()).Serialize(tw, obj, m_customNamespace);

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
                //This version information will be used in future version of Power Monitor component.
                string ver_info = tr.GetAttribute(0);

                res = GetSerializer(t).Deserialize(tr);
                SetTableDefault(t, false);
            }
            catch
            {
                res = Activator.CreateInstance(t);

                if (res is ICyTable)
                {
                    ((ICyTable)res).InitializeTable(m_numOfDefaultRows);
                    SetTableDefault(t, true);

                    if (String.IsNullOrEmpty(serializedXml) == false)
                    {
                        MessageBox.Show(Resources.SettingsIncorrectValues,
                            typeof(CyCustomizer).Namespace, MessageBoxButtons.OK, MessageBoxIcon.Warning);
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
                return m_voltagesSerializer;
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
                            typeof(CyCustomizer).Namespace, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                try
                {
                    bool prevGlobalEditMode = m_bGlobalEditMode;
                    m_bGlobalEditMode = true;

                    RestoreParameters(imported.m_restoredParameters);

                    VoltagesTable = imported.VoltagesTable;

                    //Commit Tables
                    SetVoltagesTable();

                    GetVoltagesTable();

                    m_bGlobalEditMode = false;

                    //Update tabs
                    m_voltagesTab.UpdateUIFromTable();
                    m_voltagesTab.ValidateAllCells();
                    m_voltagesTab.UpdateColumnsVisibility();

                    m_generalTab.UpdateUI(false);

                    m_bGlobalEditMode = prevGlobalEditMode;
                }
                catch
                {
                    m_bGlobalEditMode = true;
                    MessageBox.Show(Resources.LoadCondigParamsErrorMsg,
                          typeof(CyCustomizer).Namespace, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
        #endregion

        public static bool IsCellValueValid(DataGridView dgv, int rowIndex, int colIndex, double min, double max, string errorMessage)
        {
            bool isCellValid = false;
            string message = string.Format(errorMessage, min, max);
            try
            {
                object cell = dgv[colIndex, rowIndex].Value;
                if (cell == null)
                {
                    throw new Exception();
                }
                if ((dgv[colIndex, rowIndex].ReadOnly == false) && (cell.ToString() != string.Empty))
                {
                    double currCellValue = double.Parse(dgv[colIndex, rowIndex].Value.ToString());

                    if (currCellValue < min || currCellValue > max) throw new Exception();
                }

                dgv[colIndex, rowIndex].ErrorText = string.Empty;
                isCellValid = true;
            }
            catch (Exception)
            {
                dgv[colIndex, rowIndex].ErrorText = message;
            }
            return isCellValid;
        }

        public static void SetCellReadOnlyState(DataGridView dgv, int row, int col, bool readOnly)
        {
            dgv[col, row].Style = readOnly ? DGDisabledStyle : DGEnabledStyle;
            dgv[col, row].ReadOnly = readOnly;
        }

        public static void SetColumnReadOnlyState(DataGridView dgv, int col, bool readOnly)
        {
            dgv.Columns[col].DefaultCellStyle = readOnly ? DGDisabledStyle : DGEnabledStyle;
            dgv.Columns[col].ReadOnly = readOnly;
            foreach (DataGridViewRow row in dgv.Rows)
            {
                row.Cells[col].Style = readOnly ? DGDisabledStyle : DGEnabledStyle;
            }
        }

        public static bool VoltageTableRowHasEmptyCells(CyParameters prms, CyVoltagesTableRow row)
        {
            return row.m_inputScalingFactor == null ||
                row.m_nominalOutputVoltage == null ||
                row.m_minAcqTime_ns == null ||
                (row.m_ovFaultTreshold == null && prms.FaultSourcesOV) ||
                (row.m_ovWarningTreshold == null && prms.WarningSourcesOV) ||
                (row.m_uvFaultTreshold == null && prms.FaultSourcesUV) ||
                (row.m_uvWarningTreshold == null && prms.WarningSourcesUV);
        }

        public static double? ParseNullableDouble(object val)
        {
            return ParseNullableDouble(CellToString(val));
        }
        private static char charsTrim = '\"';
        public static double? ParseNullableDouble(string val)
        {
            val = val.Replace(charsTrim, ' ');
            val = val.Trim();
            double? res = null;
            double parsed = 0;
            if (double.TryParse(val, out parsed))
            {
                res = parsed;
            }
            return res;
        }
        public static double NullableDoubleToDouble(double? val)
        {
            double res = 0;
            if (val.HasValue)
                res = val.Value;
            return res;
        }
        public static int NullableIntToInt(int? val)
        {
            int res = 0;
            if (val.HasValue)
                res = val.Value;
            return res;
        }
        public static string NullableDoubleToString(double? val)
        {
            string res = string.Empty;
            if (val.HasValue)
                res = val.Value.ToString();
            return res;
        }
        public static string CellToString(object cellValue)
        {
            string res = "";
            if (cellValue != null)
                res = cellValue.ToString();
            return res;
        }
    }
}
