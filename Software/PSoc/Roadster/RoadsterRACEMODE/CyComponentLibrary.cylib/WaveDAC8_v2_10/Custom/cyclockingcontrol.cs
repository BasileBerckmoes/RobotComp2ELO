/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;
using CyDesigner.Extensions.Common;

namespace WaveDAC8_v2_10
{
    public partial class CyClockingControl : UserControl
    {
        private CyParameters m_parameters;
        private CyClocking m_clockParams;

        public event EventHandler<CySampleRateChangedEventArgs> SampleRateChanged;

        public CyClockingControl()
        {
            InitializeComponent();
        }

        public CyClockingControl(CyParameters parameters)
        {
            InitializeComponent();
            m_parameters = parameters;
            m_clockParams = new CyClocking(parameters);
            
            m_nudSampleRate.TextChanged += nudSampleRate_TextChanged;
        }

        public void UpdateUIFromParams()
        {
            m_rbInternal.Checked = m_clockParams.ClockSourceInternal;
            m_rbExternal.Checked = !m_clockParams.ClockSourceInternal;
            m_nudSampleRate.Value = CyClocking.ConvertToKSPS(m_parameters.SampleRate);
            UpdateClockSourceDependencies(false);
        }

        public void UpdateVoltageRange()
        {
            UpdateClockSourceDependencies(true);
        }

        /// <summary>
        /// Is called on NotifyWhenDesignUpdates
        /// </summary>
        public void UpdateDesign()
        {
            if (m_clockParams.ClockSourceInternal == false)
            {
                UpdateClockSourceDependencies(false);
            }
            m_clockParams.ClockNeedsUpdate = false;
            UpdateActualSampleRate();
        }

        private void rbClockSource_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            m_clockParams.ClockSourceInternal = (rb == m_rbInternal);
            UpdateClockSourceDependencies(true);
        }

        void nudSampleRate_TextChanged(object sender, EventArgs e)
        {
            double value;
            bool parsed = double.TryParse(m_nudSampleRate.Text, out value);

            if (parsed && (value * CyParamConst.THOUSAND > UInt32.MaxValue))
            {
                parsed = false;
            }

            if (parsed)
            {
                m_parameters.SampleRate = CyClocking.ConvertToSPS((decimal)value);

                if (m_parameters.GlobalEditMode)
                {
                    m_clockParams.ClockNeedsUpdate = true;
                }
                UpdateClockSourceDependencies(false);
                UpdateSampleRateErrorProvider(m_parameters.SampleRate);
            }
            else
            {
                errorProvider.SetError(m_nudSampleRate, m_clockParams.GetSampleRateOutOfRangeMsg());
            }
        }



        private void UpdateSampleRateErrorProvider(uint value)
        {
            if ((value > m_clockParams.GetMaxSampleRateSPS()) || (value < CyParamConst.MIN_SAMPLE_RATE))
            {
                if (m_clockParams.ClockSourceInternal)
                {
                    errorProvider.SetError(m_nudSampleRate, m_clockParams.GetSampleRateOutOfRangeMsg());
                    errorProvider.SetError(m_tbActualSampleRate, string.Empty);
                }
                else
                {
                    errorProvider.SetError(m_tbActualSampleRate, m_clockParams.GetSampleRateOutOfRangeMsg());
                    errorProvider.SetError(m_nudSampleRate, string.Empty);
                }
            }
            else
            {
                errorProvider.SetError(m_nudSampleRate, string.Empty);
                errorProvider.SetError(m_tbActualSampleRate, string.Empty);
            }
        }

        /// <summary>
        /// Updates sample rate and clock frequency controls, updates error providers for these controls
        /// </summary>
        /// <param name="adjustSampleRate">If automatically adjust Sample rate if it is out of range</param>
        private void UpdateClockSourceDependencies(bool adjustSampleRate)
        {
            double frequency;
            bool freqUnknown = false;
            if (m_clockParams.ClockSourceInternal)
            {
                if (adjustSampleRate && (m_parameters.SampleRate > m_clockParams.GetMaxSampleRateSPS()) &&
                    m_parameters.GlobalEditMode)
                {
                    m_parameters.SampleRate = m_clockParams.GetMaxSampleRateSPS();
                    m_nudSampleRate.Value = CyClocking.ConvertToKSPS(m_parameters.SampleRate);
                }
                UpdateSampleRateErrorProvider(m_parameters.SampleRate);
            }
            else
            {
                frequency = m_clockParams.GetExternalClockInHz();
                freqUnknown = !CyClocking.IsFrequencyKnown(frequency);
                if (freqUnknown == false)
                {
                    UpdateSampleRateErrorProvider(CyClocking.GetSampleRateByFrequency(frequency));
                }
                if (freqUnknown)
                {
                    errorProvider.SetError(m_nudSampleRate, string.Empty);
                }
            }

            m_nudSampleRate.Enabled = m_clockParams.ClockSourceInternal;

            UpdateActualSampleRate();
        }

        private void nudSampleRate_ValueChanged(object sender, EventArgs e)
        {
            const byte DECIMAL_PLACES_EXTENDED = 3;
            const byte DECIMAL_PLACES_COMPACT = 0;
            if ((double)m_nudSampleRate.Value - Math.Floor((double)m_nudSampleRate.Value) >= CyParamConst.EPS)
            {
                m_nudSampleRate.DecimalPlaces = DECIMAL_PLACES_EXTENDED;
            }
            else
            {
                m_nudSampleRate.DecimalPlaces = DECIMAL_PLACES_COMPACT;
            }
        }

        private void UpdateActualSampleRate()
        {
            UInt32 actualsampleRate = m_clockParams.ActualSampleRate;

            if (actualsampleRate > 0)
            {
                m_tbActualSampleRate.Text = CyClocking.ConvertToKSPS(actualsampleRate).ToString();
            }
            else
            {
                m_tbActualSampleRate.Text = cywavedacresource.UnknownStr.ToUpper();
            }
            OnSampleRateChanged();
        }

        private void OnSampleRateChanged()
        {
            EventHandler<CySampleRateChangedEventArgs> handler = SampleRateChanged;
            if (handler != null)
            {
                CySampleRateChangedEventArgs args = new CySampleRateChangedEventArgs();
                args.SampleRate = m_clockParams.ActualSampleRate;
                handler(this, args);
            }
        }
    }

    public class CySampleRateChangedEventArgs : EventArgs
    {
        private UInt32 m_sampleRate;
        public UInt32 SampleRate
        {
            get { return m_sampleRate; }
            set { m_sampleRate = value; }
        }
    }

    public class CyClocking
    {
        private CyParameters m_parameters;

        private bool m_clockNeedsUpdate = false;
        public bool ClockNeedsUpdate
        {
            get { return (ClockSourceInternal && m_clockNeedsUpdate); }
            set { m_clockNeedsUpdate = value; }
        }

        public bool ClockSourceInternal
        {
            get { return m_parameters.ClockSource == CyEClockSourceType.Internal_Clk; }
            set { m_parameters.ClockSource = value ? CyEClockSourceType.Internal_Clk : CyEClockSourceType.External_Clk;}
        }

        public UInt32 ActualSampleRate
        {
            get
            {
                UInt32 rate = 0;
                double frequency = ClockSourceInternal ? GetInternalClockInHz() : GetExternalClockInHz();

                if (IsFrequencyKnown(frequency) && (ClockNeedsUpdate == false))
                {
                    rate = GetSampleRateByFrequency(frequency);
                }

                return rate;
            }
        }

        public CyClocking(CyParameters parameters)
        {
            m_parameters = parameters;
        }

        public UInt32 GetMaxFrequencyHz()
        {
            UInt32 maxFreq = 0;
            switch (m_parameters.DACRange)
            {
                case CyEWaveRangeType.Range_1_Volt:
                case CyEWaveRangeType.Range_1_Volt_Buffered:
                    maxFreq = CyParamConst.MAX_FREQ_VDAC_1V;
                    break;
                case CyEWaveRangeType.Range_4_Volt:
                case CyEWaveRangeType.Range_4_Volt_Buffered:
                    maxFreq = CyParamConst.MAX_FREQ_VDAC_4V;
                    break;
                case CyEWaveRangeType.ISink_2040_uA:
                case CyEWaveRangeType.ISource_2040_uA:
                case CyEWaveRangeType.ISink_256_uA:
                case CyEWaveRangeType.ISource_256_uA:
                case CyEWaveRangeType.ISink_32_uA:
                case CyEWaveRangeType.ISource_32_uA:
                    maxFreq = CyParamConst.MAX_FREQ_IDAC;
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }
            return maxFreq;
        }

        public UInt32 GetMaxSampleRateSPS()
        {
            UInt32 maxSampleRate = GetSampleRateByFrequency(GetMaxFrequencyHz());
            return maxSampleRate;
        }

        public static double GetFrequencyBySampleRate(UInt32 sampleRate)
        {
            return sampleRate;
        }

        public static UInt32 GetSampleRateByFrequency(double freq)
        {
            return (UInt32)Math.Round(freq);
        }

        /// <summary>
        /// Returns external clock value in Hz
        /// </summary>
        public double GetExternalClockInHz()
        {
            const string EXTERNAL_CLOCK = "clock";
            return GetClockInHz(EXTERNAL_CLOCK, false);
        }

        public double GetInternalClockInHz()
        {
            const string INTERNAL_CLOCK = "or_intern_clk";
            return GetClockInHz(INTERNAL_CLOCK, true);
        }

        /// <summary>
        /// Reads clock value
        /// </summary>
        /// <param name="clockName">Clock name</param>
        /// <param name="internalClock">Internal or External</param>
        /// <returns>Clock frequency in Hz</returns>
        public double GetClockInHz(string clockName, bool internalClock)
        {
            if (m_parameters.m_termQuery != null)
            {
                List<CyClockData> clkdata = internalClock ?
                    m_parameters.m_termQuery.GetClockData(clockName, "term1", 0) :
                    m_parameters.m_termQuery.GetClockData(clockName, 0);
                if (clkdata.Count > 0)
                {
                    if (clkdata[0].IsFrequencyKnown)
                    {
                        return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
                    }
                }
            }
            return CyParamConst.FREQUENCY_UNKNOWN;
        }

        /// <summary>
        /// Formats frequency to string
        /// </summary>
        /// <param name="frequency">Clock frequency in Hz</param>
        /// <returns>String to diplay (in kHz)</returns>
        public static string FormatFrequencyKHz(double frequency)
        {
            return (frequency / CyParamConst.THOUSAND).ToString("0.000");
        }

        /// <summary>
        /// Converts Sample rate from SPS to kSPS
        /// </summary>
        /// <param name="value">Value in SPS</param>
        /// <returns>Value in kSPS</returns>
        public static decimal ConvertToKSPS(uint sampleRate)
        {
            return sampleRate / (decimal)CyParamConst.THOUSAND;
        }

        /// <summary>
        /// Converts Sample rate from kSPS to SPS
        /// </summary>
        /// <param name="value">Value in kSPS</param>
        /// <returns>Value in SPS</returns>
        public static uint ConvertToSPS(decimal value)
        {
            value *= CyParamConst.THOUSAND;
            if (value > UInt32.MaxValue)
            {
                value = UInt32.MaxValue;
            }
            return (uint)Math.Round(value);
        }

        public static bool IsFrequencyKnown(double freq)
        {
            return freq >= 0;
        }

        public string GetSampleRateOutOfRangeMsg()
        {
            return String.Format(cywavedacresource.MsgOutOfRange,
                                 (CyParamConst.MIN_SAMPLE_RATE / CyParamConst.THOUSAND),
                                 (GetMaxSampleRateSPS() / (double)CyParamConst.THOUSAND));
        }

        public CyCustErr VerifyExternalClock()
        {
            if (ClockSourceInternal)
                return CyCustErr.OK;

            double freq = GetExternalClockInHz();

            if ((IsFrequencyKnown(freq)) && ((freq > GetMaxFrequencyHz() + CyParamConst.EPS)))
            {
                return new CyCustErr(String.Format(cywavedacresource.ClockFrequencyError,
                    GetFrequencyBySampleRate(CyParamConst.MIN_SAMPLE_RATE), FormatFrequencyKHz(GetMaxFrequencyHz())));
            }
            return CyCustErr.OK;
        }
    }
}
