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
using System.Windows.Forms;

namespace ADC_SAR_SEQ_v2_10
{
    public partial class CyConfigTab : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;

        public string TabName
        {
            get { return "Basic"; }
        }

        #region Constructor(s)
        public CyConfigTab(CyParameters param)
        {
            m_params = param;

            #region Initialize UI

            InitializeComponent();

            #region Initialize combobox items
            m_cbResolution.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.RESOLUTION));
            m_cbInputRange.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.INPUT_RANGE));
            m_cbReference.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.REFERENCE));
            #endregion

            #region Initialize numericUpDown
            m_numSampleRate.Minimum = decimal.MinValue;
            m_numSampleRate.Maximum = decimal.MaxValue;

            m_numClockFreq.Minimum = decimal.MinValue;
            m_numClockFreq.Maximum = decimal.MaxValue;
            m_numClockFreq.DecimalPlaces = 3;
            m_numClockFreq.Increment = CyParamRanges.FREQ_KHZ_INCREMENT;

            m_numVrefValue.Minimum = decimal.MinValue;
            m_numVrefValue.Maximum = decimal.MaxValue;
            m_numVrefValue.DecimalPlaces = 3;
            m_numVrefValue.Increment = 0.1M;

            m_numChannels.Minimum = decimal.MinValue;
            m_numChannels.Maximum = decimal.MaxValue;
            #endregion

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            #region Set event handlers
            m_cbResolution.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbInputRange.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbReference.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);

            m_rbSampleRate.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbClockFreq.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbFreeRunning.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbSoftwareTrigger.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbHardwareTrigger.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbInternal.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbExternal.CheckedChanged += new EventHandler(m_rb_CheckedChanged);

            m_numSampleRate.TextChanged += new EventHandler(m_num_TextChanged);
            m_numClockFreq.TextChanged += new EventHandler(m_num_TextChanged);
            m_numVrefValue.TextChanged += new EventHandler(m_num_TextChanged);
            m_numChannels.TextChanged += new EventHandler(m_num_TextChanged);
            #endregion

            #endregion

            this.Load += delegate(object sender, EventArgs e)
            {
                this.Dock = DockStyle.Fill;
                this.AutoScroll = true;

                UpdateClockData(m_params.m_inst, m_params.m_term);
            };
        }
        #endregion

        #region User interface
        private const double EPS = 0.00001;

        /// <summary>
        /// This method provides updating UI from data stored
        /// </summary>
        public void UpdateUI()
        {
            m_cbResolution.SelectedItem = m_params.GetValueDescription(CyParamNames.RESOLUTION, m_params.Resolution);
            m_cbInputRange.SelectedItem = m_params.GetValueDescription(CyParamNames.INPUT_RANGE, m_params.InputRange);
            UpdateReference();

            switch (m_params.Adjustment)
            {
                case CyEAdjustType.SAMPLE_RATE:
                    m_rbSampleRate.Checked = true;
                    break;
                case CyEAdjustType.CLOCK_FREQ:
                    m_rbClockFreq.Checked = true;
                    break;
            }

            switch (m_params.SampleMode)
            {
                case CyESampleMode.FREE_RUN:
                    m_rbFreeRunning.Checked = true;
                    break;
                case CyESampleMode.SOFT_TRIG:
                    m_rbSoftwareTrigger.Checked = true;
                    break;
                case CyESampleMode.HARD_TRIG:
                    m_rbHardwareTrigger.Checked = true;
                    break;
            }

            switch (m_params.ClockSource)
            {
                case CyEClockSource.EXTERNAL:
                    m_rbExternal.Checked = true;
                    break;
                case CyEClockSource.INTERNAL:
                    m_rbInternal.Checked = true;
                    break;
            }

            m_numSampleRate.Text = ((UInt32)(m_params.ChannelSampleRate / m_params.NumChannels)).ToString();
            m_numClockFreq.Text = m_params.ClockFrequencyKHz.ToString();
            m_numVrefValue.Text = m_params.VrefValue.ToString();
            m_numChannels.Text = m_params.NumChannels.ToString();

            UpdateTimingControlsVisibility();
            UpdateChannelSampleRate();
            UpdateVrefVisibility();
        }

        /// <summary>
        /// This method changes state of controls whose appearance depends on clock source type.
        /// </summary>
        private void UpdateTimingControlsVisibility()
        {
            if (m_params.ClockSource == CyEClockSource.EXTERNAL)
            {
                double clkFreq = m_params.GetExternalClockInKHz(CyParameters.EXTERNAL_CLOCK_TERM_NAME);

                m_numSampleRate.Enabled = false;
                m_rbSampleRate.Enabled = false;
                m_numClockFreq.Enabled = false;
                m_rbClockFreq.Enabled = false;

                m_numSampleRate.Visible = clkFreq > 0.0;
                m_numClockFreq.Visible = clkFreq > 0.0;
                m_lblUnknownRate.Visible = clkFreq <= 0.0;
                m_lblUnknownFreq.Visible = clkFreq <= 0.0;

                m_lblActualSampleRate.Visible = false;
            }
            else
            {
                double clkFreq = CyParameters.GetInternalClockInKHz(m_params.m_term);

                m_numSampleRate.Visible = true;
                m_numClockFreq.Visible = true;
                m_lblUnknownRate.Visible = false;
                m_lblUnknownFreq.Visible = false;

                m_numSampleRate.Enabled = m_params.Adjustment == CyEAdjustType.SAMPLE_RATE;
                m_rbSampleRate.Enabled = true;
                m_numClockFreq.Enabled = m_params.Adjustment == CyEAdjustType.CLOCK_FREQ;
                m_rbClockFreq.Enabled = true;

                m_lblActualSampleRate.Visible = clkFreq > 0.0;
            }
        }

        private void UpdateVrefVisibility()
        {
            m_numVrefValue.Enabled = (m_params.Reference == CyEReference.EXTERNAL_VREF) ||
                (m_params.InputRange == CyEInputRange.RANGE_2) || (m_params.InputRange == CyEInputRange.RANGE_6);
        }

        private void UpdateVrefValue()
        {
            UpdateVrefVisibility();

            switch (m_params.InputRange)
            {
                case CyEInputRange.RANGE_0: // 0.0 to 2.048 (Single Ended) 0 to Vref*2
                case CyEInputRange.RANGE_3: // 0.0 +/- 1.024 (Differential) -Input +/- Vref
                    m_numVrefValue.Text = CyParameters.INTERNAL_VREF.ToString();
                    break;

                case CyEInputRange.RANGE_1: // Vssa to Vdda (Single Ended)
                case CyEInputRange.RANGE_5: // 0.0 +/- Vdda/2 (Differential) -Input +/- Vdda/2
                    m_numVrefValue.Text = (m_params.VDDA / 2.0).ToString();
                    break;

                case CyEInputRange.RANGE_2: // Vssa to VDAC*2 (Single Ended)
                case CyEInputRange.RANGE_6: // 0.0 +/- VDAC (Differential) -Input +/- VDAC
                    m_numVrefValue.Text = m_params.VrefValue.ToString();
                    break;

                case CyEInputRange.RANGE_4: // 0.0 +/- Vdda (Differential) -Input +/- Vdda
                    m_numVrefValue.Text = m_params.VDDA.ToString();
                    break;
            }
        }

        private void UpdateReference()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = true;

            m_cbReference.Items.Clear();

            string refDescr = m_params.GetValueDescription(CyParamNames.REFERENCE, m_params.Reference);
            List<string> descrList = new List<string>(m_params.GetEnumDescriptions(CyParamNames.REFERENCE));

            if (m_params.InputRange == CyEInputRange.RANGE_4 ||
                m_params.InputRange == CyEInputRange.RANGE_2 || m_params.InputRange == CyEInputRange.RANGE_6)
            {
                string exclDescr = string.Empty;

                if (m_params.InputRange == CyEInputRange.RANGE_4)
                {
                    exclDescr = m_params.GetValueDescription(CyParamNames.REFERENCE,
                        CyEReference.INTERNAL_VREF_BYPASSED);
                    if (exclDescr == refDescr)
                    {
                        refDescr = m_params.GetValueDescription(CyParamNames.REFERENCE, CyEReference.INTERNAL_VREF);
                    }
                }
                else
                {
                    exclDescr = m_params.GetValueDescription(CyParamNames.REFERENCE, CyEReference.EXTERNAL_VREF);
                    if (exclDescr == refDescr)
                    {
                        refDescr = m_params.GetValueDescription(CyParamNames.REFERENCE,
                            CyEReference.INTERNAL_VREF_BYPASSED);
                    }
                }

                // Remove prohibited references
                while (descrList.Contains(exclDescr))
                {
                    descrList.Remove(exclDescr);
                }
            }

            m_cbReference.Items.AddRange(descrList.ToArray());

            m_params.GlobalEditMode = prevGEM;

            m_cbReference.SelectedItem = refDescr;
        }

        private void UpdateChannelSampleRate()
        {
            string value = IsClockFrequencyUnknown() ? "Unknown" : m_params.ChannelSampleRate.ToString();
            m_lblChannelsSampleRate.Text = string.Format(Resources.SampleRatePerChannelLabelFormat, value);
            CheckMaxChannelSampleRate();
        }

        private void CheckMaxChannelSampleRate()
        {
            if (m_params.Reference == CyEReference.INTERNAL_VREF &&
                m_params.ChannelSampleRate > CyParamRanges.MAX_CHANNEL_SAMPLE_RATE &&
                m_params.InputRange != CyEInputRange.RANGE_4 &&
                (IsClockFrequencyUnknown() == false))
            {
                m_errorProvider.SetError(m_cbReference, Resources.ChannelSampleRateLimitError);
            }
            else if (m_params.Reference == CyEReference.INTERNAL_VREF &&
                     m_params.ChannelSampleRate > CyParamRanges.MAX_CHANNEL_SAMPLE_RATE_VDDA &&
                     m_params.InputRange == CyEInputRange.RANGE_4 &&
                    (IsClockFrequencyUnknown() == false))
            {
                m_errorProvider.SetError(m_cbReference, Resources.ChannelSampleRateVddaLimitError);
            }
            else
            {
                m_errorProvider.SetError(m_cbReference, String.Empty);
            }
        }

        private bool IsClockFrequencyUnknown()
        {
            if (m_params.ClockSource == CyEClockSource.EXTERNAL)
            {
                double clkFreq = m_params.GetExternalClockInKHz(CyParameters.EXTERNAL_CLOCK_TERM_NAME);
                return (clkFreq <= 0.0);
            }
            return false;
        }

        private bool GetClockFrequency(out double clockFreq)
        {
            return double.TryParse(m_numClockFreq.Text, out clockFreq);
        }

        private void UpdateSamplePrechargeDependencies()
        {
            // Recalculate clock frequency or sample rate when Sample Prechange was changed
            if (m_params.ClockSource == CyEClockSource.INTERNAL)
            {
                if (m_params.Adjustment == CyEAdjustType.SAMPLE_RATE)
                {
                    m_num_TextChanged(m_numSampleRate, EventArgs.Empty);
                }
                else
                {
                    m_num_TextChanged(m_numClockFreq, EventArgs.Empty);
                }
            }

        }
        #endregion

        #region Event handlers
        /// <summary>
        /// The event handler that invokes on SelectedIndexChanged event for ComboBox controls.
        /// The following RadioButton controls are handled: m_cbResolution, m_cbInputRange and m_cbReference.
        /// </summary>
        /// <param name="sender">Object that sent an event</param>
        /// <param name="e">Object argument of the event</param>
        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbResolution)
                {
                    m_params.Resolution = m_params.GetEnumValue<CyEResolution>(CyParamNames.RESOLUTION,
                        m_cbResolution.Text);

                    double clockFreq;
                    if (GetClockFrequency(out clockFreq) == true)
                    {
                        m_params.ChannelSampleRate = m_params.GetChannelSampleRate(clockFreq);
                        UpdateChannelSampleRate();
                        m_params.GlobalEditMode = false;
                        m_numSampleRate.Text = m_params.SampleRate.ToString();
                        m_params.GlobalEditMode = true;
                    }
                }
                else if (sender == m_cbInputRange)
                {
                    m_params.InputRange = m_params.GetEnumValue<CyEInputRange>(CyParamNames.INPUT_RANGE,
                        m_cbInputRange.Text);
                    m_num_TextChanged(m_numChannels, new EventArgs());
                    m_num_TextChanged(m_numVrefValue, new EventArgs());
                    UpdateVrefValue();
                    UpdateReference();
                }
                else if (sender == m_cbReference)
                {
                    m_params.Reference = m_params.GetEnumValue<CyEReference>(CyParamNames.REFERENCE,
                        m_cbReference.Text);
                    UpdateVrefValue();
                    CheckMaxChannelSampleRate();
                    UpdateSamplePrechargeDependencies();
                }
            }
        }

        /// <summary>
        /// The event handler that invokes on CheckedChanged event for RadioButton controls.
        /// The following RadioButton controls are handled: m_rbSampleRate and m_rbClockFreq,
        /// m_rbFreeRunning and m_rbTriggered, m_rbInternal and m_rbExternal.
        /// </summary>
        /// <param name="sender">Object that sent an event</param>
        /// <param name="e">Object argument of the event</param>
        void m_rb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                RadioButton rb = (sender as RadioButton);

                if (rb != null && rb.Checked)
                {
                    if (sender == m_rbSampleRate || sender == m_rbClockFreq)
                    {
                        m_params.Adjustment = m_rbSampleRate.Checked ? CyEAdjustType.SAMPLE_RATE :
                            CyEAdjustType.CLOCK_FREQ;
                        m_numSampleRate.Enabled = m_rbSampleRate.Checked;
                        m_numClockFreq.Enabled = m_rbClockFreq.Checked;
                    }
                    else if (sender == m_rbFreeRunning || sender == m_rbSoftwareTrigger ||
                             sender == m_rbHardwareTrigger)
                    {
                        m_params.SampleMode = m_rbFreeRunning.Checked ? CyESampleMode.FREE_RUN :
                                             (m_rbSoftwareTrigger.Checked ? CyESampleMode.SOFT_TRIG :
                                                                            CyESampleMode.HARD_TRIG);
                    }
                    else if (sender == m_rbInternal || sender == m_rbExternal)
                    {
                        m_params.ClockSource = m_rbInternal.Checked ? CyEClockSource.INTERNAL : CyEClockSource.EXTERNAL;
                        UpdateClockData(m_params.m_inst, m_params.m_term);
                    }
                }
            }
        }

        /// <summary>
        /// The event handler that invokes on TextChanged event for NumericUpDown controls.
        /// The following NumericUpDown controls are handled: m_numSampleRate, m_numClockFreq, m_numVrefValue and
        /// m_numChannels.
        /// </summary>
        /// <param name="sender">Object that sent an event</param>
        /// <param name="e">Object argument of the event</param>
        void m_num_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown numControl = sender as NumericUpDown;

            if (numControl != null)
            {
                if (numControl == m_numSampleRate && m_params.Adjustment == CyEAdjustType.SAMPLE_RATE &&
                    m_params.ClockSource == CyEClockSource.INTERNAL)
                {
                    UInt32 value;

                    bool parsed = UInt32.TryParse(numControl.Text, out value);

                    if (parsed == true && m_params.GlobalEditMode)
                    {
                        m_params.ChannelSampleRate = m_params.NumChannels * value;
                        UpdateChannelSampleRate();
                        m_numClockFreq.Text = m_params.ClockFrequencyKHz.ToString();
                    }

                    if (parsed == true)
                    {
                        m_errorProvider.SetError(m_numSampleRate, string.Empty);
                    }
                    else
                    {
                        m_errorProvider.SetError(m_numSampleRate, Resources.SampleRateValueErrorDescription);
                    }
                }
                else if (numControl == m_numClockFreq)
                {
                    double value;

                    bool parsed = GetClockFrequency(out value);

                    if (parsed == true && value >= CyParamRanges.MIN_CLOCK_FREQ_KHZ &&
                        value <= m_params.MaxClockFrequencyKHz)
                    {
                        m_errorProvider.SetError(m_numClockFreq, string.Empty);

                        if ((m_params.ClockSource == CyEClockSource.EXTERNAL ||
                            m_params.Adjustment == CyEAdjustType.CLOCK_FREQ)
                            && m_params.GlobalEditMode)
                        {
                            m_params.ChannelSampleRate = m_params.GetChannelSampleRate(value);
                            UpdateChannelSampleRate();
                            m_numSampleRate.Text = m_params.SampleRate.ToString();
                        }
                    }
                    else
                    {
                        m_errorProvider.SetError(m_numClockFreq,
                            string.Format(Resources.ClockFrequencyValueErrorDescription,
                            CyParamRanges.MIN_CLOCK_FREQ_MHZ, m_params.MaxClockFrequencyMHz));
                    }
                }
                else if (numControl == m_numVrefValue)
                {
                    double maxValue;
                    double value;
                    string errorMsgFormat;

                    // External voltage reference should be limited to Vdda/2 for "Vssa to Vdda(Single)"
                    // and "0.0 +/- Vdda/2(Differential)" input ranges
                    if (m_params.Reference == CyEReference.EXTERNAL_VREF &&
                        (m_params.InputRange == CyEInputRange.RANGE_1 ||
                        m_params.InputRange == CyEInputRange.RANGE_5))
                    {
                        maxValue = m_params.VDDA / 2;
                        errorMsgFormat = Resources.VrefValueValueVddaDiv2ErrorDescription;
                    }
                    else
                    {
                        maxValue = m_params.VDDA;
                        errorMsgFormat = Resources.VrefValueValueVddaErrorDescription;
                    }

                    bool parsed = double.TryParse(numControl.Text, out value);

                    if (parsed == true && m_params.GlobalEditMode)
                    {
                        m_params.VrefValue = value;
                    }

                    if (parsed == true && value >= CyParamRanges.VREF_MIN_VALUE &&
                        value <= maxValue)
                    {
                        m_errorProvider.SetError(m_numVrefValue, string.Empty);
                    }
                    else
                    {
                        m_errorProvider.SetError(m_numVrefValue, string.Format(errorMsgFormat,
                            CyParamRanges.VREF_MIN_VALUE, maxValue));
                    }
                }
                else if (numControl == m_numChannels)
                {
                    byte value;

                    bool parsed = byte.TryParse(numControl.Text, out value);

                    if ((parsed == true) && (value > 0) && m_params.GlobalEditMode)
                    {
                        m_params.NumChannels = value;

                        double clockFreq;
                        if (GetClockFrequency(out clockFreq) == true)
                        {
                            m_params.ChannelSampleRate = m_params.GetChannelSampleRate(clockFreq);
                            UpdateChannelSampleRate();
                            m_params.GlobalEditMode = false;
                            m_numSampleRate.Text = m_params.SampleRate.ToString();
                            m_params.GlobalEditMode = true;
                        }
                    }

                    if (parsed == true && value >= CyParamRanges.NUM_MIN_CHANNELS &&
                        value <= m_params.NumMaxChannels)
                    {
                        m_errorProvider.SetError(m_numChannels, string.Empty);
                    }
                    else
                    {
                        m_errorProvider.SetError(m_numChannels,
                            string.Format(Resources.NumChannelsValueErrorDescription,
                            CyParamRanges.NUM_MIN_CHANNELS, m_params.NumMaxChannels, m_params.IsDifferentialMode ?
                            "differential" : "single ended"));
                    }
                }
            }

        }

        /// <summary>
        /// This method updates UI depending on external clock changes
        /// </summary>
        /// <param name="query">Reference to ICyInstQuery_v1 instance</param>
        /// <param name="termQuery">Reference to ICyTerminalQuery_v1 instance</param>
        public void UpdateClockData(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            UpdateTimingControlsVisibility();

            if (m_params.ClockSource == CyEClockSource.EXTERNAL)
            {
                double clkFreq = m_params.GetExternalClockInKHz(CyParameters.EXTERNAL_CLOCK_TERM_NAME);
                if (clkFreq > 0.0)
                {
                    m_numClockFreq.Text = clkFreq.ToString();
                    m_numSampleRate.Text = m_params.GetSampleRate(m_params.GetChannelSampleRate(clkFreq)).ToString();
                }

                m_lblActualSampleRate.Text = string.Empty;
            }
            else
            {
                string actualSampleRateStr = "UNKNOWN";
                double clkFreq = CyParameters.GetInternalClockInKHz(termQuery);

                if (clkFreq > 0.0)
                {
                    UInt32 actualSampleRate = m_params.GetSampleRate(m_params.GetChannelSampleRate(clkFreq));
                    actualSampleRateStr = actualSampleRate.ToString() + " SPS";
                }

                m_lblActualSampleRate.Text = actualSampleRateStr;
            }

            UpdateChannelSampleRate();
        }
        #endregion

        #region ICyParamEditingControl members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            string errorMessage = string.Empty;

            if (m_errorProvider != null)
            {
                // Check controls for errors
                foreach (Control control in this.Controls)
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (control.Visible && (string.IsNullOrEmpty(errorMessage) == false))
                        errs.Add(new CyCustErr(errorMessage));

                    // Check controls inside groupbox
                    foreach (Control internalControl in control.Controls)
                    {
                        errorMessage = m_errorProvider.GetError(internalControl);
                        if (internalControl.Visible && (string.IsNullOrEmpty(errorMessage) == false))
                            errs.Add(new CyCustErr(errorMessage));
                    }
                }
            }

            foreach (string paramName in m_params.m_inst.GetParamNames())
            {
                CyCompDevParam param = m_params.m_inst.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            errs.Add(new CyCustErr(errMsg));
                        }
                    }
                }
            }

            return errs;
        }
        #endregion
    }
}
