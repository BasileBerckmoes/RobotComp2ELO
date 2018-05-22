/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;

namespace ADC_SAR_v3_0
{
    #region Symbol Parameter Names
    public class CyParamNames
    {
        // Formal parameters
        public const string ADC_RESOLUTION = "ADC_Resolution";
        public const string ADC_CLOCK = "ADC_Clock";
        public const string ADC_SAMPLE_MODE = "ADC_SampleMode";
        public const string ADC_INPUT_RANGE = "ADC_Input_Range";
        public const string ADC_REFERENCE = "ADC_Reference";
        public const string SAMPLE_RATE = "Sample_Rate";
        public const string REF_VOLTAGE = "Ref_Voltage";
        public const string ENABLE_NEXT_OUT = "Enable_next_out";

        // Local parameters
        public const string ADC_CLOCK_FREQUENCY = "ADC_Clock_Frequency";
        public const string SAMPLE_RATE_DEFAULT = "Sample_Rate_def";
        public const string SAMPLE_PRECHARGE = "Sample_Precharge";
        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Symbol Types
    public enum CyEAdcSampleModeType { Free_Running, Software_Trigger, Hardware_Trigger };
    public enum CyEAdcClockSrcType { External, Internal };
    public enum CyEAdcResolution { Bits_8 = 8, Bits_10 = 10, Bits_12 = 12 };
    public enum CyEAdcInputRangeType
    {
        Vss_to_Vref,
        Vssa_to_Vdda,
        Vssa_to_VDAC,
        Vneg_Vref_Diff,
        Vneg_Vdda_Diff,
        Vneg_Vdda_2_Diff,
        Vneg_VDAC_Diff
    };
    public enum CyEAdcRefType { Int_Ref_Not_Bypassed, Int_Ref_Bypass, Ext_Ref };
    #endregion

    #region Parameter Ranges
    public class CyParamRange
    {
        public const uint MIN_FREQ_MHZ = 1;
        public const uint MIN_FREQ_KHZ = MIN_FREQ_MHZ * 1000;
        public const uint MIN_FREQ_HZ = MIN_FREQ_KHZ * 1000;

        public const uint MAX_FREQ_MHZ = 18;
        public const uint MAX_FREQ_NOT_BYPASSED_MHZ = 16;

        public const byte UNDIVIDED_CLOCK_SOURCE_MAX_MHZ = 15;

        // minimum pulse width value = 1/18Mhz = 55.55ns / 2 = 27.77ns - some margin (~+-4% CDT 91247) = 25.5ns.
        public const double MIN_PULSE_WIDTH = 25.5;
        public const double HIGH_POWER_PULSE_WIDTH = 50;

        public const double REF_VOLTAGE_MIN = 0.8;
        public const double REF_VOLTAGE_MAX = 5.5;
    }
    #endregion

    public class CyParameters
    {
        private ICyInstQuery_v1 m_instQuery;
        private ICyInstEdit_v1 m_instEdit;
        private ICyInstValidate_v1 m_instValidate;
        /// <summary>
        /// During first getting of parameters this variable is false, what means that assigning
        /// values to form controls will not immediatly overwrite parameters with the same values.
        /// </summary>
        private bool m_globalEditMode = false;
        public CyConfigureTab m_configureTab = null;
        public double m_externalClockInKHz;
        public double m_systemVdda;

        // Lists contain display names of types taken from symbol,
        // lists are used to fill comboboxes
        public List<string> m_resolutionList;
        public List<string> m_inputRangeList;
        public List<string> m_referenceList;
        // Dictionary is used to keep display names of types taken from symbol,
        // and associate them with the enum fields to simplify access to diaplay names
        public Dictionary<object, string> m_dnDict = new Dictionary<object, string>();

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;

            m_resolutionList = new List<string>(instQuery.GetPossibleEnumValues(CyParamNames.ADC_RESOLUTION));
            m_inputRangeList = new List<string>(instQuery.GetPossibleEnumValues(CyParamNames.ADC_INPUT_RANGE));
            m_referenceList = new List<string>(instQuery.GetPossibleEnumValues(CyParamNames.ADC_REFERENCE));
            m_externalClockInKHz = CyClockReader.GetExternalClockInKHz(termQuery);

            try
            {
                m_systemVdda = Math.Round(instQuery.VoltageQuery.VDDA, 4);
            }
            catch
            {
                m_systemVdda = 5;
            }

            // Adding display names to the dictionary to easily operate with enums
            CyDictParser.FillDictionary(ref m_dnDict, typeof(CyEAdcInputRangeType), m_inputRangeList);
            CyDictParser.FillDictionary(ref m_dnDict, typeof(CyEAdcRefType), m_referenceList);
        }

        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
            : this(instQuery, null, termQuery)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit, instEdit, termQuery)
        {
        }

        public CyParameters(ICyInstValidate_v1 instVal)
        {
            m_instValidate = instVal;
        }
        #endregion

        #region Class properties

        #region Common properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public bool IsArchMemberAvailable
        {
            get
            {
                if (m_instQuery != null)
                    return String.IsNullOrEmpty(m_instQuery.DeviceQuery.ArchFamilyMember) == false;
                else if (m_instValidate != null)
                    return String.IsNullOrEmpty(m_instValidate.ArchFamilyMember) == false;
                else
                    return false;
            }
        }

        public int SamplePrecharge
        {
            get { return GetValue<int>(CyParamNames.SAMPLE_PRECHARGE); }
        }

        public string InstanceName
        {
            get { return GetValue<string>(CyParamNames.INSTANCE_NAME); }
        }
        #endregion

        #region Clock properties
        public uint MaxClockFrequencyMHz
        {
            get
            {
                return (this.SamplePrecharge > 4)
                    ? CyParamRange.MAX_FREQ_MHZ
                    : CyParamRange.MAX_FREQ_NOT_BYPASSED_MHZ;
            }
        }

        public uint MaxClockFrequencyKHz
        {
            get { return MaxClockFrequencyMHz * 1000; }
        }

        public uint MaxClockFrequencyHz
        {
            get { return MaxClockFrequencyKHz * 1000; }
        }
        #endregion

        #region Properties for parameters
        public CyEAdcResolution AdcResolution
        {
            get { return GetValue<CyEAdcResolution>(CyParamNames.ADC_RESOLUTION); }
            set { SetValue(CyParamNames.ADC_RESOLUTION, value); }
        }

        public CyEAdcClockSrcType AdcClockSource
        {
            get { return GetValue<CyEAdcClockSrcType>(CyParamNames.ADC_CLOCK); }
            set { SetValue(CyParamNames.ADC_CLOCK, value); }
        }

        public CyEAdcSampleModeType AdcSampleMode
        {
            get { return GetValue<CyEAdcSampleModeType>(CyParamNames.ADC_SAMPLE_MODE); }
            set { SetValue(CyParamNames.ADC_SAMPLE_MODE, value); }
        }

        public CyEAdcInputRangeType AdcInputRange
        {
            get { return GetValue<CyEAdcInputRangeType>(CyParamNames.ADC_INPUT_RANGE); }
            set { SetValue(CyParamNames.ADC_INPUT_RANGE, value); }
        }

        public CyEAdcRefType AdcReference
        {
            get { return GetValue<CyEAdcRefType>(CyParamNames.ADC_REFERENCE); }
            set { SetValue(CyParamNames.ADC_REFERENCE, value); }
        }

        public uint AdcSampleRate
        {
            get { return GetValue<uint>(CyParamNames.SAMPLE_RATE); }
            set { SetValue(CyParamNames.SAMPLE_RATE, value); }
        }

        public double RefVoltage
        {
            get { return GetValue<double>(CyParamNames.REF_VOLTAGE); }
            set { SetValue(CyParamNames.REF_VOLTAGE, value); }
        }

        public uint SampleRateDefault
        {
            get { return GetValue<uint>(CyParamNames.SAMPLE_RATE_DEFAULT); }
        }

        public bool EnableNextOut
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_NEXT_OUT); }
            set { SetValue(CyParamNames.ENABLE_NEXT_OUT, value); }
        }
        #endregion

        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            CyCompDevParam param = null;
            T value;

            if (m_instQuery != null)
                param = m_instQuery.GetCommittedParam(paramName);
            else if (m_instValidate != null)
                param = m_instValidate.GetCommittedParam(paramName);

            if (param != null)
            {
                CyCustErr err = param.TryGetValueAs<T>(out value);
                if (err != null && err.IsOK)
                {
                    return value;
                }
                else
                {
                    if (m_configureTab != null)
                        m_configureTab.ShowError(paramName, err);
                    return default(T);
                }
            }
            return default(T);
        }

        public void LoadParameters()
        {
            m_globalEditMode = false;
            m_configureTab.UpdateUI();
            m_globalEditMode = true;
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

        #region Getting Internal Frequency and External Sample Rate
        // Get the ADC clock frequency for the current settings in kHz.
        public double GetInternalFreq()
        {
            return (double)(AdcSampleRate * ((double)this.AdcResolution + this.SamplePrecharge)) / 1000;
        }

        public uint GetExternalSampleRate()
        {
            if (m_externalClockInKHz >= 0)
                return GetSampleRate(m_externalClockInKHz);
            else
                return 0;
        }

        public uint GetSampleRate(double clockFrequencyInKHz)
        {
            if (clockFrequencyInKHz >= 0)
                return (uint)Math.Round((clockFrequencyInKHz * 1000) / ((double)this.AdcResolution +
                    this.SamplePrecharge));
            else return 0;
        }

        public uint GetMaxSampleRate()
        {
            return (uint)Math.Round((double)this.MaxClockFrequencyHz / ((double)this.AdcResolution +
                this.SamplePrecharge));
        }

        public uint GetMaxSampleRateForInternalVref()
        {
            return (this.AdcInputRange == CyEAdcInputRangeType.Vneg_Vdda_Diff)
                ? GetMaxSampleRate() / 2
                : GetMaxSampleRate() / 10;
        }

        public uint GetMinSampleRate()
        {
            return (uint)Math.Round((double)CyParamRange.MIN_FREQ_HZ / ((double)this.AdcResolution +
                this.SamplePrecharge));
        }
        #endregion

        #region External Clock Updating
        public void UpdateClock(ICyInstQuery_v1 edit, ICyTerminalQuery_v1 termQuery)
        {
            m_externalClockInKHz = CyClockReader.GetExternalClockInKHz(termQuery);
            m_configureTab.UpdateClockData();
            m_configureTab.UpdateSampleRateData();
        }
        #endregion

        #region Message(s)
        internal string GetInvalidConvRateIntVrefMessage()
        {
            return (this.AdcInputRange == CyEAdcInputRangeType.Vneg_Vdda_Diff)
                ? Resources.InvalidConvRateInternalVref
                : Resources.InvalidConvRateInternalVrefUseBypassed;
        }
        #endregion
    }
}
