/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections.Generic;

namespace ADC_SAR_SEQ_v2_10
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string ADJUSTMENT = "Adjust";
        public const string CLOCK_SOURCE = "ClockSource";
        public const string INPUT_RANGE = "InputRange";
        public const string NUM_CHANNELS = "NumChannels";
        public const string REFERENCE = "Reference";
        public const string RESOLUTION = "Resolution";
        public const string SAMPLE_MODE = "SampleMode";
        public const string CHANNEL_SAMPLE_RATE = "SampleRate";
        public const string VREF_VALUE = "VrefValue";
        public const string SAMPLE_PRECHARGE = "SamplePrecharge";
    }
    #endregion

    #region Parameters ranges
    public static class CyParamRanges
    {
        public const UInt32 CLOCKS_PER_SAMPLE = 18;

        public const double MIN_CLOCK_FREQ_MHZ = 1;
        public const double MAX_CLOCK_FREQ_MHZ = 18;
        public const double MAX_FREQ_NOT_BYPASSED_MHZ = 1.6;
        public const double MIN_CLOCK_FREQ_KHZ = MIN_CLOCK_FREQ_MHZ * 1000;
        public const decimal FREQ_KHZ_INCREMENT = CLOCKS_PER_SAMPLE / 1000M;

        public const byte UNDIVIDED_CLOCK_SOURCE_MAX_MHZ = 15;

        public const double VREF_MIN_VALUE = 0.8;
        public const byte NUM_MIN_CHANNELS = 1;
        public const byte NUM_MAX_SINGLE_CHANNELS = 64;
        public const byte NUM_MAX_DIFFERENTIAL_CHANNELS = 32;

        public const int MAX_CHANNEL_SAMPLE_RATE = 100000; // Max Channel sample rate for internal Vref
        public const int MAX_CHANNEL_SAMPLE_RATE_VDDA = 500000; // Max Channel sample rate for internal Vref
    }
    #endregion

    #region Component Enums
    public enum CyEClockSource { INTERNAL, EXTERNAL }
    public enum CyEAdjustType { SAMPLE_RATE, CLOCK_FREQ }
    public enum CyESampleMode { FREE_RUN, SOFT_TRIG, HARD_TRIG }
    public enum CyEResolution { RES8 = 8, RES10 = 10, RES12 = 12 }
    public enum CyEInputRange { RANGE_0, RANGE_1, RANGE_2, RANGE_3, RANGE_4, RANGE_5, RANGE_6 }
    public enum CyEReference { INTERNAL_VREF, INTERNAL_VREF_BYPASSED, EXTERNAL_VREF }
    #endregion

    public class CyParameters
    {
        const double DEFAULT_VDDA = 5.0;

        public const string EXTERNAL_CLOCK_TERM_NAME = "aclk";
        public const string INTERNAL_CLOCK_TERM_NAME = "or_internal";
        public const double INTERNAL_VREF = 1.024;
        public const double EPS = 0.00001;


        public ICyInstQuery_v1 m_inst;
        public ICyTerminalQuery_v1 m_term;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;
        }

        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 term) 
            : this(inst)
        {
            m_term = term;
        }
        #endregion

        #region Class Properties
        public CyEAdjustType Adjustment
        {
            get { return GetValue<CyEAdjustType>(CyParamNames.ADJUSTMENT); }
            set { SetValue(CyParamNames.ADJUSTMENT, value); }
        }

        public CyEClockSource ClockSource
        {
            get { return GetValue<CyEClockSource>(CyParamNames.CLOCK_SOURCE); }
            set { SetValue(CyParamNames.CLOCK_SOURCE, value); }
        }

        public CyEInputRange InputRange
        {
            get { return GetValue<CyEInputRange>(CyParamNames.INPUT_RANGE); }
            set { SetValue(CyParamNames.INPUT_RANGE, value); }
        }

        public byte NumChannels
        {
            get { return GetValue<byte>(CyParamNames.NUM_CHANNELS); }
            set { SetValue(CyParamNames.NUM_CHANNELS, value); }
        }

        public CyEReference Reference
        {
            get { return GetValue<CyEReference>(CyParamNames.REFERENCE); }
            set { SetValue(CyParamNames.REFERENCE, value); }
        }

        public CyEResolution Resolution
        {
            get { return GetValue<CyEResolution>(CyParamNames.RESOLUTION); }
            set { SetValue(CyParamNames.RESOLUTION, value); }
        }

        public CyESampleMode SampleMode
        {
            get { return GetValue<CyESampleMode>(CyParamNames.SAMPLE_MODE); }
            set { SetValue(CyParamNames.SAMPLE_MODE, value); }
        }

        public double VrefValue
        {
            get { return GetValue<double>(CyParamNames.VREF_VALUE); }
            set { SetValue(CyParamNames.VREF_VALUE, (float)value); }
        }

        public UInt32 ChannelSampleRate
        {
            get { return GetValue<UInt32>(CyParamNames.CHANNEL_SAMPLE_RATE); }
            set { SetValue(CyParamNames.CHANNEL_SAMPLE_RATE, value); }
        }

        private UInt32 SamplePrecharge
        {
            get { return GetValue<byte>(CyParamNames.SAMPLE_PRECHARGE); }
        }

        public UInt32 ClocksPerSample
        {
            get
            {
                return (UInt32)Resolution + SamplePrecharge;
            }
        }

        public bool IsDifferentialMode
        {
            get
            {
                return (InputRange != CyEInputRange.RANGE_0)
                    && (InputRange != CyEInputRange.RANGE_1)
                    && (InputRange != CyEInputRange.RANGE_2);
            }
        }

        public byte NumMaxChannels
        {
            get
            {
                return IsDifferentialMode ? CyParamRanges.NUM_MAX_DIFFERENTIAL_CHANNELS :
                    CyParamRanges.NUM_MAX_SINGLE_CHANNELS;
            }
        }

        public double VDDA
        {
            get
            {
                double vdda = DEFAULT_VDDA;

                try
                {
                    vdda = m_inst.VoltageQuery.VDDA;
                }
                catch
                {}

                return vdda;
            }
        }

        public bool IsArchMemberAvailable
        {
            get
            {
                if (m_inst != null)
                    return String.IsNullOrEmpty(m_inst.DeviceQuery.ArchFamilyMember) == false;
                else
                    return false;
            }
        }
        #endregion

        public uint MaxClockFrequencyKHz
        {
            get
            {
                return (this.SamplePrecharge > 4)
                  ? (uint)(CyParamRanges.MAX_CLOCK_FREQ_MHZ * 1000)
                  : (uint)(CyParamRanges.MAX_FREQ_NOT_BYPASSED_MHZ * 1000);
            }
        }

        public double MaxClockFrequencyMHz
        {
            get { return MaxClockFrequencyKHz / 1000.0; }
        }

        public UInt32 GetChannelSampleRate(double clockFrequencyKHz)
        {
            return (UInt32)(clockFrequencyKHz * 1000.0 / ClocksPerSample);
        }

        public UInt32 GetSampleRate(UInt32 channelSampleRate)
        {
            return (NumChannels > 0) ? channelSampleRate / NumChannels : 0;
        }

        public UInt32 SampleRate
        {
            get
            {
                return GetSampleRate(ChannelSampleRate);
            }
        }

        public double ClockFrequencyKHz
        {
            get
            {
                return ChannelSampleRate * ClocksPerSample / 1000.0;
            }
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
        }
        #endregion

        #region Get descriptions list
        /// <summary>
        /// This method returns array of strings - descriptions of the enumeration that is a type of the parameter with
        /// name specified in paramName.
        /// </summary>
        /// <param name="paramName">Name of the parameter. The parameters should be enum type</param>
        /// <returns>List of the enumeration descriptions</returns>
        public string[] GetEnumDescriptions(string paramName)
        {
            return new List<string>(m_inst.GetPossibleEnumValues(paramName)).ToArray();
        }

        /// <summary>
        /// Get the description for the parameter with name <b><i>paramName</i></b> and <b><i>value</i></b>.
        /// </summary>
        /// <param name="paramName">Parameter name</param>
        /// <param name="value">Value. It should be enumeration type item ID</param>
        /// <returns>The description of the item. If the item ID cannot be resolved, returns string representation of
        /// the <b><i>value</i></b></returns>
        public string GetValueDescription(string paramName, object value)
        {
            return m_inst.ResolveEnumIdToDisplay(paramName, value.ToString());
        }

        /// <summary>
        /// Get the enum item value by parameter name and enum item description.
        /// </summary>
        /// <typeparam name="T">Type of the enumeration, that is a C# type equivalent to the symbol's enumeration.
        /// </typeparam>
        /// <param name="paramName">Name of the parameter</param>
        /// <param name="displayText">Description of the enumeration item</param>
        /// <returns>Enum item value that has specified description in symbol</returns>
        public T GetEnumValue<T>(string paramName, string displayText)
        {
            T enumValue;
            string enumItemName = m_inst.ResolveEnumDisplayToId(paramName, displayText);

            try
            {
                enumValue = (T)Enum.Parse(typeof(T), enumItemName);
            }
            catch
            {
                enumValue = default(T);
            }

            return enumValue;
        }
        #endregion

        #region Service functions
        public double CalculateClockFrequency(UInt32 sampleRate)
        {
            return (double)(sampleRate * CyParamRanges.FREQ_KHZ_INCREMENT);
        }

        /// <summary>
        /// Returns external clock value in kHz
        /// </summary>
        public double GetExternalClockInKHz(string clockName)
        {
            if (m_term != null)
            {
                List<CyClockData> clkdata = m_term.GetClockData(clockName, 0);

                if (clkdata.Count > 0)
                {
                    if (clkdata[0].IsFrequencyKnown)
                    {
                        return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                    }
                }
            }

            return (-1);
        }

        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public static double GetInternalClockInKHz(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = termQuery.GetClockData(INTERNAL_CLOCK_TERM_NAME, "term1", 0);

            if (clkdata.Count > 0)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                }
            }
            return (-1);
        }

        public static double GetClockFrequencyMHz(CyClockData clockData)
        {
            return Math.Round(GetClockFrequencyKHz(clockData) / 1000, 3);
        }

        public static double GetClockFrequencyKHz(CyClockData clockData)
        {
            double freq = -1;
            if (clockData.IsFrequencyKnown)
            {
                freq = clockData.Frequency * Math.Pow(10, clockData.UnitAsExponent - 3);
                freq = Math.Round(freq, 3);
            }
            return freq;
        }
        #endregion
    }
}
