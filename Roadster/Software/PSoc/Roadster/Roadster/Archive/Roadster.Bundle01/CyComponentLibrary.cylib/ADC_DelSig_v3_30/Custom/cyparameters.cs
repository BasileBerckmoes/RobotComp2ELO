/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Reflection;
using System.ComponentModel;
using System.Windows.Forms;

namespace ADC_DelSig_v3_30
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        #region Common tab parameters names
        public const string NUM_CONFIGURATIONS = "Configs";
        public const string USE_TRIGGERED_SAMPLING = "Start_of_Conversion";
        public const string LOW_POWER_CHARGE_PUMP = "ADC_Charge_Pump_Clock";
        public const string ENABLE_VREF_VSSA = "Enable_Vref_Vss";
        public const string ENABLE_MODULATOR_INPUT = "EnableModulatorInput";
        public const string CLOCK_SOURCE = "ADC_Clock";
        public const string INPUT_MODE = "ADC_Input_Mode";
        public const string INPUT_MODE_API = "Input_Mode";
        #endregion

        #region Config tab
        #region Enumeration types names
        public const string CONVERSION_MODE_TYPE_NAME = "ADC_Conv_Method_Type";
        public const string INPUT_RANGE_TYPE_NAME = "ADC_Input_Range_Type";
        public const string BUFFER_GAIN_TYPE_NAME = "ADC_Buffer_Gain_Type";
        public const string BUFFER_MODE_TYPE_NAME = "ADC_Input_Buffer_Mode";
        public const string VREF_TYPE_NAME = "ADC_Ref_Type";
        #endregion

        private const string PARAM_NAME_FORMAT = "{0}_Config{1}";

        private const string COMMENT_FORMAT = "Comment_Config{0}";
        private const string CONFIG_NAME_FORMAT = "Config{0}_Name";
        private const string CONVERSION_MODE_NAME = "Conversion_Mode";
        private const string RESOLUTION_NAME = "ADC_Resolution";
        private const string CONVERSION_RATE_NAME = "Sample_Rate";
        private const string INPUT_RANGE_NAME = "ADC_Input_Range";
        private const string BUFFER_GAIN_NAME = "Input_Buffer_Gain";
        private const string BUFFER_MODE_NAME = "Input_Buffer_Mode";
        private const string ALIGNMENT_NAME = "ADC_Alignment";
        private const string REFERENCE_NAME = "ADC_Reference";
        private const string VREF_VALUE_NAME = "Ref_Voltage";
        private const string INPUT_RANGE_API_NAME = "ADC_Input_RangeValue";

        private static string BuildParamName(string prefix, byte configId)
        {
            return (configId > 1 ? string.Format(PARAM_NAME_FORMAT, prefix, configId) : prefix);
        }

        public static string CommentName(byte configId)
        {
            return string.Format(COMMENT_FORMAT, configId);
        }
        public static string ConfigName(byte configId)
        {
            return string.Format(CONFIG_NAME_FORMAT, configId);
        }
        public static string ConversionModeName(byte configId)
        {
            return BuildParamName(CONVERSION_MODE_NAME, configId);
        }
        public static string ResolutionName(byte configId)
        {
            return BuildParamName(RESOLUTION_NAME, configId);
        }
        public static string ConversionRateName(byte configId)
        {
            return BuildParamName(CONVERSION_RATE_NAME, configId);
        }
        public static string InputRangeName(byte configId)
        {
            return BuildParamName(INPUT_RANGE_NAME, configId);
        }
        public static string BufferGainName(byte configId)
        {
            return BuildParamName(BUFFER_GAIN_NAME, configId);
        }
        public static string BufferModeName(byte configId)
        {
            return BuildParamName(BUFFER_MODE_NAME, configId);
        }
        public static string ReferenceName(byte configId)
        {
            return BuildParamName(REFERENCE_NAME, configId);
        }
        public static string VRefValueName(byte configId)
        {
            return BuildParamName(VREF_VALUE_NAME, configId);
        }
        public static string AlignmentName(byte configId)
        {
            return BuildParamName(ALIGNMENT_NAME, configId);
        }
        // These parameters are used in API
        public static string InputModeName(byte configId)
        {
            return (configId == 1) ? INPUT_MODE_API : BuildParamName(INPUT_MODE, configId);
        }
        public static string InputRangeValueName(byte configId)
        {
            return BuildParamName(INPUT_RANGE_API_NAME, configId);
        }
        #endregion
    }
    #endregion

    #region Component Parameters Ranges
    public static class CyParamRanges
    {
        public const byte NUM_MIN_CONFIG = 1;
        public const byte NUM_MAX_CONFIG = 4;

        public const byte NUM_MIN_RESOLUTION = 8;
        public const byte NUM_MAX_RESOLUTION = 20;

        public const int MIN_CLOCK_FREQ = 128000;
        public const int MAX_8_15_CLOCK_FREQ = 6144000;
        public const int MAX_16_20_CLOCK_FREQ = 3072000;
        public const double FREQUENCY_UNKNOWN = -1.0;
        public const double CLOCK_EPS = 0.1;

        public const int MIN_CONV_RATE = 2;
        public const int MAX_CONV_RATE = 1000000;

        public const byte MIN_RESOLUTION = 8;
        public const byte MAX_RESOLUTION = 20;

        public const double MIN_VREF_VALUE = 0.9;
        public const double MAX_VREF_VALUE = 1.3;
        public const double DEFAULT_REFERENCE_VOLTAGE = 1.024;

        public const double MAX_VDDA3_VALUE = 3.75;
        public const double DEFAULT_VDDA_VALUE = 5.0;

        public const byte ALIGN_RESOLUTION_RANGE_1 = 15;
        public const byte ALIGN_RESOLUTION_RANGE_2 = 16;
        public const byte ALIGN_RESOLUTION_RANGE_3 = 20;
    }
    #endregion

    #region Component Parameters Enumerations
    public enum CyEClockSource 
    { 
        [Description("External")] External,
        [Description("Internal")] Internal 
    }
    public enum CyEInputMode
    {
        [Description("Differential")] Differential_Mode,
        [Description("Single")] Single_Mode
    }
    public enum CyESamplingMode 
    {
        [Description("Software")] Software,
        [Description("Hardware")] Hardware 
    }

    public enum CyEConversionMode 
    {
        [Description("0 - Single Sample")] Single_Sample,
        [Description("1 - Multi Sample")] Fast_Filter,
        [Description("2 - Continuous")] Continuous,
        [Description("3 - Multi Sample (Turbo)")] Fast_FIR 
    }
    public enum CyEResolution 
    {
        [Description("8")]  Bits_8 = 8,
        [Description("9")]  Bits_9 = 9,
        [Description("10")] Bits_10 = 10,
        [Description("11")] Bits_11 = 11,
        [Description("12")] Bits_12 = 12,
        [Description("13")] Bits_13 = 13,
        [Description("14")] Bits_14 = 14,
        [Description("15")] Bits_15 = 15,
        [Description("16")] Bits_16 = 16,
        [Description("17")] Bits_17 = 17,
        [Description("18")] Bits_18 = 18,
        [Description("19")] Bits_19 = 19,
        [Description("20")] Bits_20 = 20 
    }
    public enum CyEInputRange 
    {
        [Description("0.0 to Vref")] Vssa_to_Vref,
        [Description("0.0 to 2*Vref")] Vssa_to_2Vref,
        [Description("Vssa to Vdda")] Vssa_to_Vdda,
        [Description("0.0 to 6*Vref")] Vssa_to_6Vref,
        [Description("-Input +/- Vref")] Vneg_Vref_Diff,
        [Description("-Input +/- 2*Vref")] Vneg_2Vref_Diff,
        [Description("-Input +/- 6*Vref")] Vneg_6Vref_Diff,
        [Description("-Input +/- Vref/2")] Vneg_Vref2_Diff,
        [Description("-Input +/- Vref/4")] Vneg_Vref4_Diff,
        [Description("-Input +/- Vref/8")] Vneg_Vref8_Diff,
        [Description("-Input +/- Vref/16")] Vneg_Vref16_Diff 
    }
    public enum CyEBufferGain 
    {
        [Description("1")] Gain_1X = 1,
        [Description("2")] Gain_2X = 2,
        [Description("4")] Gain_4X = 4,
        [Description("8")] Gain_8X = 8 
    }
    public enum CyEBufferMode 
    {
        [Description("Bypass Buffer")] Bypass_Buffer,
        [Description("Rail to Rail")] Rail_to_Rail,
        [Description("Level Shift")] Level_Shift 
    }
    public enum CyEReference 
    {
        [Description("Internal 1.024 Volts")] Int_Ref_Not_Bypassed,
        [Description("Internal Bypassed on P0.3")] Int_Ref_Bypass_On_P03,
        [Description("Internal Bypassed on P3.2")] Int_Ref_Bypass_On_P32,
        [Description("External Vref on P0.3")] Ext_Ref_On_P03,
        [Description("External Vref on P3.2")] Ext_Ref_On_P32,
        [Description("Internal Vdda/4")] Internal_Vdda_4_Ref,
        [Description("Internal Vdda/4 Bypassed on P0.3")] Internal_Vdda_4_Ref_Bypassed_On_P03,
        [Description("Internal Vdda/4 Bypassed on P3.2")] Internal_Vdda_4_Ref_Bypassed_On_P32,
        [Description("Internal Vdda/3")] Internal_Vdda_3_Ref,
        [Description("Internal Vdda/3 Bypassed on P0.3")] Internal_Vdda_3_Ref_Bypassed_On_P03,
        [Description("Internal Vdda/3 Bypassed on P3.2")] Internal_Vdda_3_Ref_Bypassed_On_P32 
    }
    public enum CyEAlignment 
    {
        [Description("Right")] Right,
        [Description("Left OVF Protected")] Left_OVF_Protected,
        [Description("Left Not OVF Protected")] Left_Not_OVF_Protected 
    }

    #endregion

    public class CyParameters
    {
        #region Fields
        public ICyInstQuery_v1 m_inst;
        public ICyTerminalQuery_v1 m_term;
        public ICyTabbedParamEditor m_editor = null;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public CyCommonTab m_commonTab;
        public CyConfigurationTab[] m_configTabs = new CyConfigurationTab[CyParamRanges.NUM_MAX_CONFIG];
        #endregion Fields

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;
            m_term = null;
        }

        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 term)
        {
            m_inst = inst;
            m_term = term;
        }
        #endregion

        #region Getting Parameters
        public T GetValue<T>(string paramName)
        {
            return GetValue<T>(m_inst.GetCommittedParam(paramName));
        }

        private T GetValue<T>(CyCompDevParam prm)
        {
            T value = default(T);
            CyCustErr err = CyCustErr.OK;
            if (typeof(T).BaseType == typeof(Enum))
            {
                err = prm.TryGetValueAs<T>(out value);
                if ((err == null) || (err.IsOK == false) || (Enum.IsDefined(typeof(T), value) == false))
                {
                    value = (T)Enum.GetValues(typeof(T)).GetValue(0);
                    err = CyCustErr.OK;
                }
            }
            else
                err = prm.TryGetValueAs<T>(out value);
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

        #region Setting Parameters
        public void SetValue<T>(string paramName, T value)
        {
            if (m_bGlobalEditMode)
                if (m_inst != null && m_inst is ICyInstEdit_v1)
                {
                    ICyInstEdit_v1 edit = m_inst as ICyInstEdit_v1;
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                        valueToSet += "u";
                    if (edit.SetParamExpr(paramName, valueToSet))
                    {
                        edit.CommitParamExprs();
                    }
                }
        }
        #endregion

        #region Class properties
        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        public double VDDA
        {
            get
            {
                double vdda = CyParamRanges.DEFAULT_VDDA_VALUE;
                try
                {
                    if (m_inst.VoltageQuery != null)
                    {
                        vdda = m_inst.VoltageQuery.VDDA;
                    }
                }
                catch
                {
                    Debug.Fail(Resource.DebugMsgVddaFail);
                }
                return vdda;
            }
        }

        #region Common tab properties
        public byte NumConfigurations
        {
            get { return GetValue<byte>(CyParamNames.NUM_CONFIGURATIONS); }
            set { SetValue(CyParamNames.NUM_CONFIGURATIONS, value); }
        }

        public bool UseTriggeredSamplingMode
        {
            get
            {
                return (GetValue<CyESamplingMode>(CyParamNames.USE_TRIGGERED_SAMPLING) == CyESamplingMode.Hardware);
            }
            set
            {
                SetValue(CyParamNames.USE_TRIGGERED_SAMPLING, (value ?
                    CyESamplingMode.Hardware : CyESamplingMode.Software));
            }
        }

        public bool LowPowerChargePump
        {
            get { return GetValue<bool>(CyParamNames.LOW_POWER_CHARGE_PUMP); }
            set { SetValue(CyParamNames.LOW_POWER_CHARGE_PUMP, value); }
        }

        public bool EnableVrefVssa
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_VREF_VSSA); }
            set { SetValue(CyParamNames.ENABLE_VREF_VSSA, value); }
        }

        public bool EnableModulatorInput
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_MODULATOR_INPUT); }
            set { SetValue(CyParamNames.ENABLE_MODULATOR_INPUT, value); }
        }

        public CyEClockSource ClockSourceType
        {
            get { return GetValue<CyEClockSource>(CyParamNames.CLOCK_SOURCE); }
            set { SetValue(CyParamNames.CLOCK_SOURCE, value); }
        }

        public CyEInputMode InputModeType
        {
            get { return GetValue<CyEInputMode>(CyParamNames.INPUT_MODE); }
            set { SetValue(CyParamNames.INPUT_MODE, value); }
        }
        #endregion

        #region Config tab properties
        public string GetComment(byte configId)
        {
            return GetValue<string>(CyParamNames.CommentName(configId));
        }
        public void SetComment(byte configId, string value)
        {
            SetValue(CyParamNames.CommentName(configId), value);
        }

        public string GetConfigName(byte configId)
        {
            return GetValue<string>(CyParamNames.ConfigName(configId));
        }
        public void SetConfigName(byte configId, string value)
        {
            SetValue(CyParamNames.ConfigName(configId), value);
        }

        public CyEConversionMode GetConversionMode(byte configId)
        {
            return GetValue<CyEConversionMode>(CyParamNames.ConversionModeName(configId));
        }
        public void SetConversionMode(byte configId, CyEConversionMode value)
        {
            SetValue(CyParamNames.ConversionModeName(configId), value);
        }

        public byte GetResolution(byte configId)
        {
            CyEResolution res = GetValue<CyEResolution>(CyParamNames.ResolutionName(configId));
            return Convert.ToByte(res);
        }
        public void SetResolution(byte configId, byte value)
        {
            CyEResolution resolution = (CyEResolution)value;
            SetValue(CyParamNames.ResolutionName(configId), resolution);
        }

        public UInt32 GetScanRate(byte configId)
        {
            return GetValue<UInt32>(CyParamNames.ConversionRateName(configId));
        }
        public void SetScanRate(byte configId, UInt32 value)
        {
            SetValue(CyParamNames.ConversionRateName(configId), value);
        }

        public CyEInputRange GetInputRange(byte configId)
        {
            return GetValue<CyEInputRange>(CyParamNames.InputRangeName(configId));
        }
        public void SetInputRange(byte configId, CyEInputRange value)
        {
            SetValue(CyParamNames.InputRangeName(configId), value);
        }

        public CyEBufferGain GetBufferGain(byte configId)
        {
            return GetValue<CyEBufferGain>(CyParamNames.BufferGainName(configId));
        }
        public void SetBufferGain(byte configId, CyEBufferGain value)
        {
            SetValue(CyParamNames.BufferGainName(configId), value);
        }

        public CyEBufferMode GetBufferMode(byte configId)
        {
            return GetValue<CyEBufferMode>(CyParamNames.BufferModeName(configId));
        }
        public void SetBufferMode(byte configId, CyEBufferMode value)
        {
            SetValue(CyParamNames.BufferModeName(configId), value);
        }

        public CyEAlignment GetAlignment(byte configId)
        {
            return GetValue<CyEAlignment>(CyParamNames.AlignmentName(configId));
        }
        public void SetAlignment(byte configId, CyEAlignment value)
        {
            SetValue(CyParamNames.AlignmentName(configId), value);
        }

        public CyEReference GetReference(byte configId)
        {
            return GetValue<CyEReference>(CyParamNames.ReferenceName(configId));
        }
        public void SetReference(byte configId, CyEReference value)
        {
            SetValue(CyParamNames.ReferenceName(configId), value);
        }

        public double GetVrefValue(byte configId)
        {
            return GetValue<double>(CyParamNames.VRefValueName(configId));
        }
        public void SetVrefValue(byte configId, double value)
        {
            SetValue(CyParamNames.VRefValueName(configId), value);
        }
        #endregion
        #endregion

        #region Service functions
        /// <summary>
        /// Show/hide tabs depending on the configuration
        /// </summary>
        public void UpdateTabVisibility()
        {
            for (int i = 1; i <= CyParamRanges.NUM_MAX_CONFIG; i++)
            {
                m_editor.ShowCustomPage(Resource.ConfigTabBaseDisplayName + i.ToString());
            }
            for (int i = NumConfigurations + 1; i <= CyParamRanges.NUM_MAX_CONFIG; i++)
            {
                m_editor.HideCustomPage(Resource.ConfigTabBaseDisplayName + i.ToString());
            }
        }

        public void UpdateDesign(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            foreach (CyConfigurationTab configTab in m_configTabs)
            {
                configTab.UpdateConfigName();
                configTab.UpdateClockSourceDependencies();
            }
        }

        public void UpdateInputModeDependencies()
        {
            foreach (CyConfigurationTab configTab in m_configTabs)
            {
                configTab.UpdateInputOptionsGroupBoxName();
                configTab.UpdateInputRangeList();
            }
        }

        public void UpdateClockSourceDependencies()
        {
            foreach (CyConfigurationTab configTab in m_configTabs)
            {
                configTab.UpdateClockSourceDependencies();
            }
        }

        public string GetConfigurationTabName(int index)
        {
            return "Config" + index;
        }

        public string GetConfigurationTabNameWithColons(int index)
        {
            return String.Format("{0}: ", GetConfigurationTabName(index));
        }

        public static uint GetCoherency(uint resolution, CyEAlignment alignment)
        {
            uint coherencyRegValue = Cyrc.DEC_SAMP_KEY_LOW;
            switch (alignment)
            {
                case CyEAlignment.Right:
                    coherencyRegValue = Cyrc.DEC_SAMP_KEY_LOW;
                    break;
                case CyEAlignment.Left_Not_OVF_Protected:
                    coherencyRegValue = Cyrc.DEC_SAMP_KEY_MID;
                    break;
                case CyEAlignment.Left_OVF_Protected:
                    if (resolution < 16)
                    {
                        coherencyRegValue = Cyrc.DEC_SAMP_KEY_MID;
                    }
                    else
                    {
                        coherencyRegValue = Cyrc.DEC_SAMP_KEY_HIGH;
                    }
                    break;
                default:
                    coherencyRegValue = Cyrc.DEC_SAMP_KEY_LOW;
                    break;
            }
            return coherencyRegValue;
        }

        #region Enums
        // combobox
        public static void FillComboFromEnum(ComboBox cb, Type enumType)
        {
            cb.Items.Clear();
            cb.Items.AddRange(GetDescriptionList(enumType));
        }
        public static void SetComboValue(ComboBox cb, object value)
        {
            string descr = GetDescription(value);
            if (cb.Items.Contains(descr))
                cb.SelectedItem = descr;
        }
 
        public static string[] GetDescriptionList(Type _enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(_enumType))
            {
                res.Add(GetDescription(item));
            }
            return res.ToArray();
        }
        public static string GetDescription(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
        }
        public static T GetEnum<T>(string value)
        {
            return (T)GetEnum(value, typeof(T));
        }
        /// <summary>
        /// Convert enum description string to enum value
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        static object GetEnum(string value, Type _enumType)
        {
            foreach (FieldInfo fi in _enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value == dna.Description))
                {
                    object res = Enum.Parse(_enumType, fi.Name);
                    return res;
                }

            }

            return Enum.Parse(_enumType, value);
        }
        #endregion

        public void SetDefaultConfigParams(byte configId)
        {
            SetAlignment(configId, CyEAlignment.Right);
            SetInputRange(configId, CyEInputRange.Vneg_Vref_Diff);
            SetResolution(configId, 16);
            SetConfigName(configId, "CFG" + configId);
            SetConversionMode(configId, CyEConversionMode.Continuous);
            SetScanRate(configId, 10000);
            SetReference(configId, CyEReference.Int_Ref_Not_Bypassed);
            SetBufferGain(configId, CyEBufferGain.Gain_1X);
            SetBufferMode(configId, CyEBufferMode.Rail_to_Rail);
            SetVrefValue(configId, 1.024);

            string commentStr = "";
            switch (configId)
            {
                case 1:
                    commentStr = "Default Config";
                    break;
                case 2:
                    commentStr = "Second Config";
                    break;
                case 3:
                    commentStr = "Third Config";
                    break;
                case 4:
                    commentStr = "Fourth Config";
                    break;
                default:
                    break;
            }
            SetComment(configId, commentStr);

            if (GlobalEditMode)
            {
                GlobalEditMode = false;
                m_configTabs[configId - 1].UpdateUI();
                GlobalEditMode = true;
            }
        }
        #endregion

        #region Clock
        /// <summary>
        /// Returns external clock value in kHz
        /// </summary>
        public double GetExternalClockInHz()
        {
            const string EXTERNAL_CLOCK = "aclk";
            return GetClockInHz(EXTERNAL_CLOCK, false);
        }

        public double GetMasterClockInHz()
        {
            const string MASTER_CLOCK = "or_internal";
            return GetClockInHz(MASTER_CLOCK, true);
        }

        public double GetClockInHz(string clockName, bool internalClock)
        {
            if (m_term != null)
            {
                List<CyClockData> clkdata = internalClock ?
                    m_term.GetClockData(clockName, "term1", 0) : m_term.GetClockData(clockName, 0);
                if (clkdata.Count > 0)
                {
                    if (clkdata[0].IsFrequencyKnown)
                    {
                        return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
                    }
                }
            }
            return CyParamRanges.FREQUENCY_UNKNOWN;
        }

        public static string FormatFrequencyKHz(double frequency)
        {
            return (frequency / 1000).ToString("0.000");
        }

        public static bool IsFrequencyKnown(double freq)
        {
            return freq >= 0;
        }

        public static CyCustErr GetClockDivider(float masterClockFreq, float clockFreq, float minFreq, float maxFreq, 
                                                out UInt16 divider)
        {
            // Check arguments
            if ((masterClockFreq < 1) || (clockFreq < 1) || (masterClockFreq + CyParamRanges.CLOCK_EPS < clockFreq))
            {
                divider = 1;
                return new CyCustErr(Resource.DRCErrorMasterClockFrequency);
            }

            clockFreq = Math.Max(clockFreq, minFreq);
            clockFreq = Math.Min(clockFreq, maxFreq);

            divider = (UInt16)Math.Round(masterClockFreq / clockFreq);

            // Adjust divider if the resulting clock exceeds limits
            if (masterClockFreq / divider < minFreq - CyParamRanges.CLOCK_EPS)
            {
                divider--;
            }
            else if (masterClockFreq / divider > maxFreq + CyParamRanges.CLOCK_EPS)
            {
                divider++;
            }

            return CyCustErr.OK;
        }
        #endregion Clock

        #region DRC Validation
         
        public CyCustErr VerifyExternalClock(byte configId)
        {
            if (ClockSourceType != CyEClockSource.External)
                return CyCustErr.OK;

            double freq = GetExternalClockInHz();
            uint minRate, maxRate;
            double maxFreq, minFreq;
            GetMinMaxClockFreqSampleRate(configId, out minFreq, out maxFreq, out minRate, out maxRate);

            if ((freq >= 0) && ((freq > maxFreq) || (freq < minFreq)))
            {
                return new CyCustErr(GetConfigurationTabNameWithColons(configId) +
                                        String.Format(Resource.DRCErrorExternalClockRange,
                                        FormatFrequencyKHz(minFreq), FormatFrequencyKHz(maxFreq)));
            }
            return CyCustErr.OK;
        }

        public CyCustErr VerifySampleRate(byte configId)
        {
            if (ClockSourceType == CyEClockSource.External)
                return CyCustErr.OK;

            uint minRate, maxRate;
            double maxFreq, minFreq;
            uint sampleRate = GetScanRate(configId);

            GetMinMaxClockFreqSampleRate(configId, out minFreq, out maxFreq, out minRate, out maxRate);

            if ((sampleRate > maxRate) || (sampleRate < minRate))
            {
                return new CyCustErr(GetConfigurationTabNameWithColons(configId) +
                                            Resource.DRCErrorSampleRateRange);
            }
            return CyCustErr.OK;
        }

        public CyCustErr VerifyBufferGain(byte configId)
        {
            if ((GetBufferGain(configId) != CyEBufferGain.Gain_1X) &&
                ((GetInputRange(configId) == CyEInputRange.Vssa_to_Vdda) ||
                 (GetInputRange(configId) == CyEInputRange.Vssa_to_2Vref)))
            {
                return new CyCustErr(GetConfigurationTabNameWithColons(configId) +
                                            Resource.DRCErrorBufferGain);
            }
            return CyCustErr.OK;
        }
               
        public CyCustErr VerifyVrefValue(byte configId)
        {
            double vRef;
            CyCustErr err = CalcVddaVRef(out vRef, configId);
            if (err != CyCustErr.OK)
            {
                return new CyCustErr(GetConfigurationTabNameWithColons(configId) + err.Message);
            }
            return CyCustErr.OK;
        }

        public CyCustErr VerifyMasterClockFrequency(byte configId)
        {
            if (ClockSourceType == CyEClockSource.External)
                return CyCustErr.OK;

            CyCustErr err = CyCustErr.OK;

            uint resolution = GetResolution(configId);
            uint convRate = GetScanRate(configId);
            CyEConversionMode conversionMode = GetConversionMode(configId);

            uint clockFrequency = CyCustomizer.SetClock(resolution, convRate, conversionMode);
            uint cpClockFrequency = CyCustomizer.GetChargePumpClock(clockFrequency);
            double masterClockFreq = GetMasterClockInHz();
            bool isMasterClockFrequencyKnown = IsFrequencyKnown(masterClockFreq);
            
            if (IsFrequencyKnown(clockFrequency) && isMasterClockFrequencyKnown)
            {
                if (masterClockFreq + CyParamRanges.CLOCK_EPS < clockFrequency)
                {
                    err = new CyCustErr(Resource.DRCErrorMasterClockFrequency);
                }
                else if (masterClockFreq + CyParamRanges.CLOCK_EPS < cpClockFrequency)
                {
                    err = new CyCustErr(Resource.DRCErrorMasterClockFrequencyCp);
                }
            }
            return err;
        }

        public CyCustErr CalcVddaVRef(out double vRef, byte configId)
        {
            CyCustErr error = CyCustErr.OK;

            vRef = GetVrefValue(configId);

            CyEInputRange inputRange = GetInputRange(configId);
            CyEReference reference = GetReference(configId);

            if (inputRange == CyEInputRange.Vssa_to_Vdda)
            {
                // Ranges [2.7; 3.75) and [3.75; 5.2) for VDDA are taken from EROS
                // (section 7.8.10 "Input Range" Parameter)
                if (VDDA < CyParamRanges.MAX_VDDA3_VALUE)
                {
                    reference = CyEReference.Internal_Vdda_3_Ref;
                }
                else
                {
                    reference = CyEReference.Internal_Vdda_4_Ref;
                }
                error = new CyCustErr(Resource.DRCErrorVssaVddaVrefValue);
            }

            switch (reference)
            {
                case CyEReference.Int_Ref_Not_Bypassed:
                case CyEReference.Int_Ref_Bypass_On_P03:
                case CyEReference.Int_Ref_Bypass_On_P32:
                    vRef = CyParamRanges.DEFAULT_REFERENCE_VOLTAGE;
                    break;
                case CyEReference.Ext_Ref_On_P03:
                case CyEReference.Ext_Ref_On_P32:
                    error = new CyCustErr(Resource.ErrorVrefRange);
                    break;
                case CyEReference.Internal_Vdda_4_Ref:
                case CyEReference.Internal_Vdda_4_Ref_Bypassed_On_P03:
                case CyEReference.Internal_Vdda_4_Ref_Bypassed_On_P32:
                    vRef = VDDA / 4.0;
                    error = new CyCustErr(Resource.DRCErrorReferenceVrefValue);
                    break;
                case CyEReference.Internal_Vdda_3_Ref:
                case CyEReference.Internal_Vdda_3_Ref_Bypassed_On_P03:
                case CyEReference.Internal_Vdda_3_Ref_Bypassed_On_P32:
                    vRef = VDDA / 3.0;
                    error = new CyCustErr(Resource.DRCErrorReferenceVrefValue);
                    break;
                default:
                    break;
            }

            if (vRef >= CyParamRanges.MIN_VREF_VALUE && vRef <= CyParamRanges.MAX_VREF_VALUE)
                error = CyCustErr.OK;

            return error;
        }

        public void GetMinMaxClockFreqSampleRate(byte configId, out double minClockFreq, out double maxClockFreq,
            out uint minSampleRate, out uint maxSampleRate)
        {
            uint resolution = GetResolution(configId);
            int gain = (int)GetBufferGain(configId);
            CyEConversionMode conversionMode = GetConversionMode(configId);
            int inputRange = (int)GetInputRange(configId);
            CyEBufferMode bufferMode = GetBufferMode(configId);

            // Get maximum and minimum frequency
            if (resolution > 15)
            {
                // If buffer is enabled, for 2x,4x,8x gain, the frequency is halved and 
                // halved and halved respectively

                // Unbuffered Input
                if (bufferMode == CyEBufferMode.Bypass_Buffer)
                    maxClockFreq = Cyrc.MAX_FREQ_16_20_BITS[inputRange];
                else // Buffered
                    maxClockFreq = Cyrc.MAX_FREQ_16_20_BITS[inputRange] / gain;

                minClockFreq = Cyrc.MIN_FREQ_15_20_BITS;
            }
            else
            {
                // Unbuffered Input
                if (bufferMode == CyEBufferMode.Bypass_Buffer)
                    maxClockFreq = Cyrc.MAX_FREQ_8_15_BITS[inputRange];
                else // Buffered
                    maxClockFreq = Cyrc.MAX_FREQ_8_15_BITS[inputRange] / gain;

                // Minimum frequency is equal to that for 8-14 bit resolution
                minClockFreq = Cyrc.MIN_FREQ_8_14_BITS;
            }

            // Get minimum and maximum sample rate
            maxSampleRate = CyCustomizer.GetSampleRate(resolution, (float)maxClockFreq, conversionMode, true);
            minSampleRate = CyCustomizer.GetSampleRate(resolution, (float)minClockFreq, conversionMode, false);

            // Do correction for Gain=8
            if (maxSampleRate < minSampleRate)
            {
                if (gain == 8)
                {
                    // 192KHz. And lower limit will be 128KHz.
                    maxClockFreq = Cyrc.MAX_FREQ_GAIN_8;
                    minClockFreq = Cyrc.MIN_FREQ_GAIN_8;
                }
                maxSampleRate = CyCustomizer.GetSampleRate(resolution, (float)maxClockFreq, conversionMode, true);
                minSampleRate = CyCustomizer.GetSampleRate(resolution, (float)minClockFreq, conversionMode,false);
            }
        }
        #endregion DRC Validation
    }
}
