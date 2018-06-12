/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Reflection;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;


namespace Scan_ADC_v1_30
{

    public delegate void NumConfigsChangeHandler(object sender, EventArgs e);
    public delegate void SideEffectHandler();
    public delegate void AdcClockSourceHandler();


    /// <summary>
    /// Component symbol parameter names.
    /// Used to access parameter data in component instances.
    /// </summary>
    public class CyParamNames
    {
        /* Common tab*/
        public const string NUM_CONFIGS = "NumConfigs";
        public const string EXTERNAL_SOC = "ExternalSoc";
        public const string EXTERNAL_CLK = "ExternalClk";
        public const string DEBUG = "Debug";

        /* Config tabs */
        public const string CONFIG_TAB_NAME_BASE = "Config";

        /* Dummy tab - Dummy variables used to contain CyEnum types*/
        public const string DEFAULT_ALTERNATE_RESOLUTION = "DefaultAlternateResolution";
        public const string DEFAULT_AVERAGING_MODE = "DefaultAveragingMode";
        public const string DEFAULT_INPUT_MODE = "DefaultInputMode";
        public const string DEFAULT_FILTER_TYPE = "DefaultFilterType";
        public const string DEFAULT_LIMIT_COMPARISON_MODE = "DefaultLimitComparisonMode";
        public const string DEFAULT_NUMBER_FORMAT = "DefaultNumberFormat";
        public const string DEFAULT_SAMPLES_AVERAGED = "DefaultSamplesAveraged";
        public const string DEFAULT_VNEG_SOURCE = "DefaultVnegSource";
        public const string DEFAULT_VREF_SOURCE = "DefaultVrefSource";

        /* Test parameters. Also on Common tab */
        public const string TEST_CONFIGSPACE = "Test_ConfigSpacing";
        public const string TEST_EXPOSETESTTERMINALS = "Test_ExposeTestTerminals";
    }

    /// <summary>
    /// Component parameter range limits.
    /// Minimum and maximum (inclusive) numbes of configs and channels.
    /// </summary>
    public class CyParamRanges
    {
        public const int NUM_CONFIG_MIN = 1;
        public const int NUM_CONFIG_MAX = 4;
        public const int NUM_CHANNEL_MIN = 1;
        public const int NUM_CHANNEL_MAX = 16;
        public const double FREQUENCY_EPSILON = 1e-6;
        public const int APERTURE_TIMER_COUNT = 4;
        public const int APERTURE_TIMER_MIN = 2;
        public const int APERTURE_TIMER_MAX = 1024;
        public const double APERTURE_MIN_NS = 194;
        public const double APERTURE_FILTER_MIN_NS = 194;   // CDT 230992, KVCP
        public const double MIN_VREF = 1.0;                 // CDT 246998

        public const int SAR_FREQ_MAX_HZ = 18000000;
        public const int SAR_SCAN_DURATION_MIN_CLKADC = 14;
        public const decimal DEFAULT_HP_CUTOFF_KHZ = 10;
        public const decimal DEFAULT_HP_NOTCH_KHZ = 0;
        public const decimal DEFAULT_LP_CUTOFF_KHZ = 10;
        public const decimal DEFAULT_LP_NOTCH_KHZ = 50;
        public const decimal DEFAULT_BP_LOW3DB_KHZ = 8;
        public const decimal DEFAULT_BP_HIGH3DB_KHZ = 11;
        public const decimal DEFAULT_BS_CENTER_KHZ = 10;
        public const decimal DEFAULT_BS_3DB_KHZ = 12;
    }

    #region Enums

    /// <summary>
    /// Types of channel inputs.
    /// </summary>
    [CyEnumCName("input_mode_enum")]
    public enum CyEInputMode
    {
        [Description("Differential")]
        DIFFERENTIAL_CHAN = 0,
        [Description("Single ended")]
        SINGLE_ENDED_CHAN = 1,
        [Description("Apply filter")]
        FILTER_CHAN = 2,
    }

    /// <summary>
    /// Comparison selection for compare interrupt generation.
    /// </summary>
    [CyEnumCName("limit_compare_enum")]
    public enum CyELimitComparisonMode
    {
        [Description("Result < Low")]
        LESS_THAN = 0,
        [Description("Low <= Result < High")]
        BETWEEN = 1,
        [Description("High <= Result")]
        GREATER_THAN = 2,
        [Description("(Result < Low) or (High <= Result)")]
        OUTSIDE = 3,
    }

    /// <summary>
    /// Configuration averaging mode.
    /// </summary>
    [CyEnumCName("averaging_mode_enum")]
    public enum CyEAveragingMode
    {
        [Description("Sequential, Fixed")]
        SEQUENTIAL_AVG = 1,
        [Description("Sequential, Sum")]
        ACCUMULATE_AVG = 0,
        [Description("Interleaved, Sum")]
        INTERLEAVED_AVG = 2,
    }

    /// <summary>
    /// Number of samples to use for averaged channels.
    /// </summary>
    [CyEnumCName("sample_averaged_enum")]
    public enum CyESamplesAveraged
    {
        [Description("2")]
        TWO_SAMPLES = 0,
        [Description("4")]
        FOUR_SAMPLES = 1,
        [Description("8")]
        EIGHT_SAMPLES = 2,
        [Description("16")]
        SIXTEEN_SAMPLES = 3,
        [Description("32")]
        THIRTYTWO_SAMPLES = 4,
        [Description("64")]
        SIXTYFOUR_SAMPLES = 5,
        [Description("128")]
        ONETWENTYEIGHT_SAMPLES = 6,
        [Description("256")]
        TWOFIFTYSIX_SAMPLES = 7,
    }

    /// <summary>
    /// Signed or unsigned result format.
    /// </summary>
    [CyEnumCName("number_format_enum")]
    public enum CyENumberFormat 
    {
        [Description("Signed")]
        SIGNED_FORMAT = 1,
        [Description("Unsigned")]
        UNSIGNED_FORMAT = 0,
    }

    /// <summary>
    /// Vneg selection for single-ended channels.
    /// </summary>
    [CyEnumCName("vneg_source_enum")]
    public enum CyEVnegSource
    {
        [Description("Vssa")]
        VNEGSOURCE_VSSA_K = 0,
        [Description("External")]
        VNEGSOURCE_EXTERNAL = 2,
        [Description("Vref")]
        VNEGSOURCE_VREFSHORT = 7,
    }

    /// <summary>
    /// Vref selection.
    /// </summary>
    [CyEnumCName("vref_source_enum")]
    public enum CyEVrefSource
    {
        [Description("Design-wide reference")]
        VREFSOURCE_PVREF = 0,
        [Description("System bandgap")]
        VREFSOURCE_VBGR = 1,
        [Description("Symbol terminal")]
        VREFSOURCE_EXTERNAL = 2,
        [Description("Vdda/2")]
        VREFSOURCE_HALFVDDA = 3,
        [Description("Vdda")]
        VREFSOURCE_VDDA = 4,
        [Description("External device pin")]
        VREFSOURCE_DEVPIN = 5,
    }

    /// <summary>
    /// Supported two-pole filter types.
    /// </summary>
    [CyEnumCName("filter_type_enum")]
    public enum CyEFilterType
    {
        [Description("Low pass")]
        LOW_PASS = 0,
        [Description("High pass")]
        HIGH_PASS = 1,
        [Description("Band pass")]
        BAND_PASS = 2,
        [Description("Notch")]
        BAND_STOP = 3,
    }

    /// <summary>
    /// Filter topology enum.
    /// 
    /// Used to select filter algorithms and to generate API parameters.
    /// </summary>
    public enum CyEFilterTopology
    {
        HIGH_Q = 0,
        LOW_Q = 1,
    }

    /// <summary>
    /// Alternate resolution selection.
    /// </summary>
    [CyEnumCName("alterate_resolution_enum")]
    public enum CyEAlternateResolution
    {
        [Description("10-bit")]
        TEN_BIT = 1,
        [Description("8-bit")]
        EIGHT_BIT = 0,
    }

    /// <summary>
    /// All SCan_ADC resolutions.
    /// 
    /// Only some of these will be available at a time,
    /// based on the alternate resolution selection and
    /// the current device.
    /// </summary>
    [CyEnumCName("all_res_enum")]
    public enum CyEAllResolution
    {
        [Description("10-bit (alt)")]
        TEN_BIT = 0,
        [Description("8-bit (alt)")]
        EIGHT_BIT = 1,
        [Description("12-bit")]
        TWELVE_BIT = 2,
    }

    #endregion Enums

    /// <summary>
    /// Component instance symbol parameter values.
    /// </summary>
    public class CyParameters
    {
        private ICyInstQuery_v1 m_instQuery;
        private ICyInstEdit_v1 m_instEdit;
        private ICyTerminalQuery_v1 m_termQuery;

        List<CyConfigModel> m_configs;

        // Xml serialization parameters
        public XmlSerializer m_configModelSerializer;
        public XmlSerializerNamespaces m_customSerNamespace;

        // Flags used by rest of customizer.
        private bool m_globalEditMode = false;
        private bool m_isFilterAllowed = true;

        // Events
        public event NumConfigsChangeHandler NumConfigsChange;
        public event SideEffectHandler SideEffectChange;
        public event AdcClockSourceHandler AdcClockSourceChange;

        #region Constructors

        /// <summary>
        /// Set up symbol parameter object with only instance query access to symbol.
        /// </summary>
        /// <param name="instQuery">Instance query interface</param>
        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null, null)
        {
        }

        /// <summary>
        /// Set up symbol parameter object with only instance and terminal queries.
        /// </summary>
        /// <param name="instQuery">Instance query interface</param>
        /// <param name="termQuery">Terminal query interface</param>
        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
            : this(instQuery, null, termQuery)
        {
        }

        /// <summary>
        /// Set up symbol parameter obect with full access to symbol.
        /// </summary>
        /// <param name="instQuery">Instance query interface</param>
        /// <param name="instEdit">Instance edit interface</param>
        /// <param name="termQuery">Terminal query interface</param>
        public CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;

            m_configs = new List<CyConfigModel>();
            for (int configNum = 0; configNum < CyParamRanges.NUM_CONFIG_MAX; configNum++)
            {
                m_configs.Add(null);
            }

            m_configModelSerializer = new XmlSerializer(typeof(CyConfigModel));
            /* Add version information to xml namespace */
            m_customSerNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(CyParameters).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);
        }

        #endregion Constructors

        #region Properties

        /// <summary>
        /// Enable or disable symbol parameter writes from parameter object.
        /// </summary>
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        /// <summary>
        /// Is UAB filter supported by current project's device?
        /// </summary>
        public bool IsFilterAllowed
        {
            get { return m_isFilterAllowed; }
            set { m_isFilterAllowed = value;  }
        }

        #region Query members

        /// <summary>
        /// Return parameter object's instance query interface.
        /// 
        /// Used to retrieve parameter enum descriptions and committed parameter errors.
        /// </summary>
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        /// <summary>
        /// Return parameter object's terminal query interface.
        /// 
        /// Not currently used, may be used to retrieve clock information.
        /// </summary>
        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        #endregion Query members

        #region Common Tab Properties

        /// <summary>
        /// Selected number of configurations.
        /// </summary>
        public int NumberOfConfigs
        {
            get
            {
                int value = GetValue<int>(CyParamNames.NUM_CONFIGS);
                return value;
            }
            set
            {
                if (m_globalEditMode)
                {
                    SetValue<int>(CyParamNames.NUM_CONFIGS, value);
                    OnNumConfigsChange(EventArgs.Empty);
                }
            }
        }

        /// <summary>
        /// Sets the width between configs.
        /// </summary>
        public long Test_ConfigSpacing
        {
            get
            {
                long value = GetValue<UInt32>(CyParamNames.TEST_CONFIGSPACE);
                return value;
            }
            set
            {
                if (m_globalEditMode)
                {
                    SetValue<UInt32>(CyParamNames.TEST_CONFIGSPACE, (UInt32)value);
                    OnNumConfigsChange(EventArgs.Empty);
                }
            }
        }

        /// <summary>
        /// Exposes SAR data output and UAB terminals.
        /// </summary>
        public bool Test_ExposeTestTerminals
        {
            get
            {
                bool value = GetValue<bool>(CyParamNames.TEST_EXPOSETESTTERMINALS);
                return value;
            }
            set
            {
                if (m_globalEditMode)
                {
                    SetValue<bool>(CyParamNames.TEST_EXPOSETESTTERMINALS, (bool)value);
                    OnNumConfigsChange(EventArgs.Empty);
                }
            }
        }

        /// <summary>
        /// True iff component symbol uses an SOC terminal.
        /// </summary>
        public bool ExternalSoc
        {
            get { return GetValue<bool>(CyParamNames.EXTERNAL_SOC); }
            set
            {
                if (m_globalEditMode)
                {
                    SetValue<bool>(CyParamNames.EXTERNAL_SOC, value);
                }
            }
        }

        /// <summary>
        /// True iff component symbol uses an external clock terminal.
        /// </summary>
        public bool ExternalClk
        {
            get { return GetValue<bool>(CyParamNames.EXTERNAL_CLK); }
            set
            {
                if (m_globalEditMode)
                {
                    SetValue<bool>(CyParamNames.EXTERNAL_CLK, value);
                }
            }
        }


        /// <summary>
        /// True iff debug features are to be enabled.
        /// </summary>
        public bool Debug
        {
            get { return GetValue<bool>(CyParamNames.DEBUG); }
            set
            {
                if (m_globalEditMode)
                {
                    SetValue<bool>(CyParamNames.DEBUG, value);
                }
            }
        }

        #endregion Common Tab Properties

        #region Config Tab Methods

        /// <summary>
        /// Get config parameters from deserialized component string parameter.
        /// </summary>
        /// <param name="i">Configuration index</param>
        /// <returns>Configuration parameter object</returns>
        public CyConfigModel GetConfig(int i)
        {
            // If the config has not yet been loaded, retrieve it from the symbol instance.
            if (m_configs[i] == null)
            {
                string name = GetConfigName(i);
                string value = GetValue<string>(name, m_instQuery);
                CyConfigModel config = (CyConfigModel)Deserialize(value, typeof(CyConfigModel));
                
                // If the configuration has no channels, add two default channels.
                if (config.ChannelList.Count == 0)
                {
                    var channels = new List<CyChannelModel>();
                    channels.Add(new CyChannelModel());
                    channels.Add(new CyChannelModel());
                    config.ChannelList = channels;
                    config.NumChannels = 2;
                }

                // If aperture timers were not loaded, add defaults.
                while (config.ApertureTimers.Count < CyParamRanges.APERTURE_TIMER_COUNT)
                {
                    config.ApertureTimers.Add(CyParamRanges.APERTURE_TIMER_MIN);
                }

                // If UAB cap values were not loaded, add defaults.
                if (config.UabCaps == null)
                {
                    config.UabCaps = new GTCaps();
                }

                // Defect cleanup - if there are too many timers, trim them.
                if (config.ApertureTimers.Count > CyParamRanges.APERTURE_TIMER_COUNT)
                {
                    config.ApertureTimers.RemoveRange(
                        CyParamRanges.APERTURE_TIMER_COUNT,
                        config.ApertureTimers.Count - CyParamRanges.APERTURE_TIMER_COUNT);
                }

                m_configs[i] = config;
            }
            
            return m_configs[i];
        }

        /// <summary>
        /// Store serialized config parameters in a component string parameter.
        /// 
        /// This invalidates any existing references to the configuration.
        /// </summary>
        /// <param name="i">Configuration index</param>
        /// <param name="config">Configuration parameter object</param>
        public void SetConfig(int i, CyConfigModel config)
        {
            // TODO: Is it worth testing for config changes before serializing???
            // Save the config.
            string name = GetConfigName(i);
            string value = Serialize(config);
            SetValue(name, value);

            // TODO: Determine why this code loses config FilterSample updates.
            // Retrieve the config stored in the symbol instance.
            // m_configs[i] = null;
            // GetConfig(i);

            m_configs[i] = config;
        }

        /// <summary>
        /// Return internal name for configuration.
        /// </summary>
        /// <param name="i">Configuration index</param>
        /// <returns>Internal name</returns>
        private string GetConfigName(int i)
        {
            return CyParamNames.CONFIG_TAB_NAME_BASE + i.ToString();
        }

        #endregion Config Tab Properties

        #region Local GUI Properties

        [XmlIgnore]
        public CyClockData ExternalAdcClockData { get; set; }

        [XmlIgnore]
        public CyClockData InternalAdcClockData { get; set; }

        #endregion Local GUI properties

        #endregion Properties

        #region Event functions

        /// <summary>
        /// Raise a NumConfigsChange event.
        /// </summary>
        /// <param name="e">Expecting empty arguments.</param>
        protected virtual void OnNumConfigsChange(EventArgs e)
        {
            NumConfigsChangeHandler handler = NumConfigsChange;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raise a parameter side effects event.
        /// </summary>
        public virtual void OnSideEffectChange()
        {
            SideEffectHandler handler = SideEffectChange;
            if (handler != null)
            {
                handler();
            }
        }

        public virtual void OnAdcClockSourceHandler()
        {
            AdcClockSourceHandler handler = AdcClockSourceChange;
            if (handler != null)
            {
                handler();
            }
        }

        #endregion Event functions

        #region Scan scheduling

        public List<CyDRCInfo_v1> UpdateScanSchedules()
        {
            List<CyDRCInfo_v1> drcList = new List<CyDRCInfo_v1>();
            for (int configNum = 0; configNum < NumberOfConfigs; configNum++)
            {
                var config = GetConfig(configNum);
                var tmpClkData = ExternalClk ?
                    ExternalAdcClockData :
                    InternalAdcClockData;
                var schedErrs = config.UpdateScanSchedule(tmpClkData, ExternalClk, Debug);
                drcList.AddRange(schedErrs);
                SetConfig(configNum, config);
            }
            return drcList;
        }

        public List<List<double>> ScanSignature()
        {
            var signature = new List<List<double>>();

            for (int configNum = 0; configNum < NumberOfConfigs; configNum++)
            {
                var config = GetConfig(configNum);
                signature.Add(config.ScanSignature());
            }

            return signature;
        }

        public bool SignaturesDiffer(List<List<double>> sig0, List<List<double>> sig1)
        {
            if (sig0.Count != sig1.Count)
            {
                return true;
            }

            for (int listNum = 0; listNum < sig0.Count; listNum++)
            {
                var listA = sig0[listNum];
                var listB = sig1[listNum];
                if (listA.Count != listB.Count)
                {
                    return true;
                }
                for (int index = 0; index < listA.Count; index++)
                {
                    if (listA[index] != listB[index])
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        #endregion Scan scheduling

        #region Getting Parameters

        /// <summary>
        /// Get symbol parameter.
        /// </summary>
        /// <typeparam name="T">C# parameter type.</typeparam>
        /// <param name="paramName">Parameter name.</param>
        /// <returns></returns>
        public T GetValue<T>(string paramName)
        {
            return GetValue<T>(paramName, m_instQuery);
        }

        /// <summary>
        /// Helper function for getting symbol parameters.
        /// </summary>
        /// <typeparam name="T">C# parameter type.</typeparam>
        /// <param name="paramName">Parameter name.</param>
        /// <param name="instQuery">Symbol instance query interface.</param>
        /// <returns></returns>
        private static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            if (instQuery == null) return default(T);
            T value;
            CyCompDevParam devParam = instQuery.GetCommittedParam(paramName);
            CyCustErr err = devParam.TryGetValueAs<T>(out value);

            return (err != null && err.IsOK) ? value : default(T);
        }

        #endregion Getting Parameters

        #region Setting Parameters

        /// <summary>
        /// Set symbol parameter.
        /// </summary>
        /// <typeparam name="T">C# parameter type.</typeparam>
        /// <param name="paramName">Parameter name.</param>
        /// <param name="value">New parameter value.</param>
        public void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
            {
                SetValue(m_instEdit, paramName, value);
            }
        }

        /// <summary>
        /// Helper function for setting symbol parameters.
        /// </summary>
        /// <typeparam name="T">C# parameter type.</typeparam>
        /// <param name="instEdit">Symbol instance edit interface.</param>
        /// <param name="paramName">Parameter name.</param>
        /// <param name="value">New parameter value.</param>
        /// <returns></returns>
        private static CyCustErr SetValue<T>(ICyInstEdit_v1 instEdit, string paramName, T value)
        {
            if (instEdit == null)
            {
                return CyCustErr.OK;
            }

            string valueToSet = value.ToString();
            if (value is bool)
                valueToSet = valueToSet.ToLower();
            if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                valueToSet += "u";

            if (instEdit.SetParamExpr(paramName, valueToSet) && instEdit.CommitParamExprs())
            {
                return CyCustErr.OK;
            }

            CyCompDevParam param = instEdit.GetCommittedParam(paramName);
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }

        #endregion

        #region XML Serialization

        /// <summary>
        /// Serialize an object to an XML string.
        /// </summary>
        /// <param name="obj">Object to serialize.</param>
        /// <returns>Serialized XML string.</returns>
        public string Serialize(object obj)
        {
            StringBuilder sb = new StringBuilder();

            System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb);
            m_configModelSerializer.Serialize(tw, obj, m_customSerNamespace);

            string res = sb.ToString();
            res = res.Replace("\r\n", " ");
            return res;
        }

        /// <summary>
        /// Deserialize XML string to an object.
        /// </summary>
        /// <param name="serializedXml">Serialized XML string.</param>
        /// <param name="t">Object type</param>
        /// <returns>Object of specified type.</returns>
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
                string ver_info = tr.GetAttribute(0);

                res = m_configModelSerializer.Deserialize(tr);
            }
            catch
            {
                res = Activator.CreateInstance(t);
            }
            return res;
        }

        #endregion
    }
}

//[] END OF FILE
