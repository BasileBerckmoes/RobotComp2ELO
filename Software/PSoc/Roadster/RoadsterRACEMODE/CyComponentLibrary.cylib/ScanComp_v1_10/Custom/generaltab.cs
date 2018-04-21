/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace ScanComp_v1_10
{
    public partial class CyGeneralTab : CyTabWrapper
    {
        public override string TabName
        {
            get { return "General"; }
        }

        #region Constructor(s)
        public CyGeneralTab(CyParameters parameters)
            : base(parameters)
        {
            m_params = parameters;

            InitializeComponent();

            #region Subscribe events
            numClockFreq.TextChanged += numUpDown_TextChanged;
            numScanRate.TextChanged += numUpDown_TextChanged;
            numVdacVoltage.TextChanged += numUpDown_TextChanged;
            #endregion

            #region Initialize all NumericUpDown ranges
            numScanRate.Minimum = 0;
            numScanRate.Maximum = Decimal.MaxValue;
            numClockFreq.Minimum = 0;
            numClockFreq.Maximum = Decimal.MaxValue;
            numVdacVoltage.Minimum = 0;
            numVdacVoltage.Maximum = Decimal.MaxValue;
            #endregion
        }
        #endregion

        #region Overrides
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            UpdateClockData(m_params.InstQuery, m_params.TermQuery);

            // Disable Internal VDAC for PSoC 4 device
            if (m_params.IsPSoC4)
            {
                rbInternalVdac.Enabled = false;
                if (m_params.NegativeInput == CyENegativeInput.INTERN)
                    rbCommon.Checked = true;
            }
        }
        #endregion

        #region Update tab controls from parameters
        /// <summary>
        /// Updates tab controls from parameters
        /// </summary>
        public void UpdateUI()
        {
            // Clock Source radio buttons
            switch (m_params.ClockSource)
            {
                case CyEClockSource.INTERNAL:
                    rbInternal.Checked = true;
                    break;
                case CyEClockSource.EXTERNAL:
                    rbExternal.Checked = true;
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }

            // Scan Timing radio buttons
            switch (m_params.ScanTimingType)
            {
                case CyEScanTimingType.SCAN_RATE:
                    rbScanRate.Checked = true;
                    break;
                case CyEScanTimingType.CLOCK_FREQ:
                    rbClockFreq.Checked = true;
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }

            // Nagetive Input radio buttons
            switch (m_params.NegativeInput)
            {
                case CyENegativeInput.COMMON:
                    rbCommon.Checked = true;
                    break;
                case CyENegativeInput.UNIQUE:
                    rbUnique.Checked = true;
                    break;
                case CyENegativeInput.INTERN:
                    rbInternalVdac.Checked = true;
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }

            // Scan Rate numeric box
            numScanRate.Text = m_params.GetScanRateKHz(m_params.ClockFrequencyHz).ToString();

            // Clock Frequency numeric box
            numClockFreq.Text = m_params.ClockFrequencyKHz.ToString();

            // HW Output Enabled check box
            chbHwOutEnabled.Checked = m_params.OutputsEnable;

            // VDAC Range radio buttons
            switch (m_params.VdacRange)
            {
                case CyEVdacRange.VDAC8__Range_1_Volt:
                    rbRange1_20V.Checked = true;
                    break;
                case CyEVdacRange.VDAC8__Range_4_Volt:
                    rbRange4_80V.Checked = true;
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }

            // VDAC Voltage radio buttons
            switch (m_params.VdacVoltageMode)
            {
                case CyEVdacVoltageMode.FIXED:
                    rbFixed.Checked = true;
                    break;
                case CyEVdacVoltageMode.PER_CHANNEL:
                    rbPerChannel.Checked = true;
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }

            // VDAC Voltage numeric box
            numVdacVoltage.Text = m_params.VdacVoltageMv.ToString();

            UpdateClockData(m_params.InstQuery, m_params.TermQuery);
        }
        #endregion

        #region Event Handlers
        private void chbHwOutEnabled_CheckedChanged(object sender, EventArgs e)
        {
            m_params.OutputsEnable = chbHwOutEnabled.Checked;
        }

        private void rbClockSource_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb == null || rb.Checked == false) return;

            m_params.ClockSource = (rb == rbExternal) ? CyEClockSource.EXTERNAL : CyEClockSource.INTERNAL;
            UpdateClockData(m_params.InstQuery, m_params.TermQuery);
        }

        private void rbTiming_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb == null || rb.Checked == false) return;

            m_params.ScanTimingType = (rb == rbScanRate) ? CyEScanTimingType.SCAN_RATE : CyEScanTimingType.CLOCK_FREQ;
            UpdateTimingControlsAccessibility();
        }

        private void numUpDown_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown numeric = sender as NumericUpDown;
            if (numeric == null || m_params.GlobalEditMode == false) return;

            bool isValueParsed;
            if (sender == numScanRate) // scan rate
            {
                double inputValue;
                isValueParsed = double.TryParse(numScanRate.Text, out inputValue);
                m_params.ScanRate = inputValue;

                if (isValueParsed &&
                    m_params.ClockSource == CyEClockSource.INTERNAL &&
                    m_params.ScanTimingType == CyEScanTimingType.SCAN_RATE)
                {
                    numClockFreq.Text = m_params.GetClockFrequencyKHz(inputValue).ToString();
                    m_params.UpdateScanSpeed(); // update Scan Speed when clock is updated
                }
            }
            else if (sender == numClockFreq) // clock frequency
            {
                double inputValue;
                isValueParsed = double.TryParse(numClockFreq.Text, out inputValue);
                m_params.ClockFrequencyKHz = inputValue;

                if (isValueParsed &&
                    m_params.ClockSource == CyEClockSource.INTERNAL &&
                    m_params.ScanTimingType == CyEScanTimingType.CLOCK_FREQ)
                {
                    numScanRate.Text = m_params.GetScanRateKHz(m_params.ClockFrequencyHz).ToString();
                    m_params.UpdateScanSpeed(); // update Scan Speed when clock is updated
                }
                ValidateClockFrequency(true);
            }
            else if (sender == numVdacVoltage) // VDAC voltage
            {
                UInt16 inputValue;
                UInt16.TryParse(numVdacVoltage.Text, out inputValue);
                m_params.VdacVoltageMv = inputValue;
                ValidateVdacVoltage(inputValue);
                m_params.ChannelsTab.UpdateDacVoltageColumn();
            }
        }

        private void rbNegativeInput_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb == null || rb.Checked == false) return;

            if (sender == rbUnique)
                m_params.NegativeInput = CyENegativeInput.UNIQUE;
            else if (sender == rbCommon)
                m_params.NegativeInput = CyENegativeInput.COMMON;
            else if (sender == rbInternalVdac)
                m_params.NegativeInput = CyENegativeInput.INTERN;

            UpdateVdacControlsAccessibility();
            ValidateClockFrequency(m_params.ClockSource == CyEClockSource.INTERNAL);
        }

        private void rbVdacRange_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb == null || rb.Checked == false) return;

            if (sender == rbRange1_20V)
                m_params.VdacRange = CyEVdacRange.VDAC8__Range_1_Volt;
            else if (sender == rbRange4_80V)
                m_params.VdacRange = CyEVdacRange.VDAC8__Range_4_Volt;

            numVdacVoltage.Increment = m_params.GetVdacRangeCoeff();

            ValidateClockFrequency(m_params.ClockSource == CyEClockSource.INTERNAL);
            ValidateVdacVoltage(m_params.VdacVoltageMv);
            m_params.ChannelsTab.UpdateDacVoltageColumn();
        }

        private void rbVdacVoltageMode_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb == null || rb.Checked == false) return;

            if (sender == rbFixed)
                m_params.VdacVoltageMode = CyEVdacVoltageMode.FIXED;
            else if (sender == rbPerChannel)
                m_params.VdacVoltageMode = CyEVdacVoltageMode.PER_CHANNEL;

            m_params.ChannelsTab.UpdateDacVoltageColumn();
            UpdateVdacControlsAccessibility();
            numUpDown_TextChanged(numVdacVoltage, new EventArgs());
        }

        private void numVdacVoltage_UpButtonClicked(object sender, EventArgs e)
        {
            // Assign smallest multiple to 4 or 16 greater than or equal to the current value
            byte mult = m_params.GetVdacRangeCoeff();
            if ((numVdacVoltage.Value % mult) != 0)
                numVdacVoltage.Value = Math.Ceiling(numVdacVoltage.Value / mult) * mult - numVdacVoltage.Increment;
        }

        private void numVdacVoltage_DownButtonClicked(object sender, EventArgs e)
        {
            // Assign largest multiple to 4 or 16 less than or equal to the current value
            byte mult = m_params.GetVdacRangeCoeff();
            if ((numVdacVoltage.Value % mult) != 0)
                numVdacVoltage.Value = Math.Floor(numVdacVoltage.Value / mult) * mult + numVdacVoltage.Increment;
        }

        private void CyGeneralTab_VisibleChanged(object sender, EventArgs e)
        {
            UpdateTimimgParams(); // update timing data since number of channels could be changed
        }
        #endregion

        #region Validation
        private void ValidateClockFrequency(bool isErrorShow)
        {
            if (isErrorShow)
            {
                m_errorProvider.SetError(numClockFreq, m_params.GetClockFrequencyError(m_params.ClockFrequencyHz));
            }
            else
            {
                m_errorProvider.SetError(numClockFreq, String.Empty);
            }
        }

        private void ValidateVdacVoltage(UInt16 inputValue)
        {
            bool isParsed = UInt16.TryParse(numVdacVoltage.Text, out inputValue);
            if (numVdacVoltage.Enabled && m_params.VdacVoltageMode == CyEVdacVoltageMode.FIXED &&
                (isParsed == false ||
                (inputValue < CyParamRanges.VDAC_VOLTAGE_MIN || inputValue > m_params.GetMaxDACVoltage())))
            {
                m_errorProvider.SetError(numVdacVoltage, String.Format(Resources.ValueOutOfRange,
                    CyParamRanges.VDAC_VOLTAGE_MIN, m_params.GetMaxDACVoltage()));
            }
            else
            {
                m_errorProvider.SetError(numVdacVoltage, String.Empty);
            }
        }
        #endregion

        #region Update dependent parameters
        /// <summary>
        /// Updates UI depending on external clock changes.
        /// </summary>
        /// <param name="query">Reference to ICyInstQuery_v1 instance</param>
        /// <param name="termQuery">Reference to ICyTerminalQuery_v1 instance</param>
        public void UpdateClockData(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            bool isErrorShow = false;
            if (m_params.ClockSource == CyEClockSource.EXTERNAL)
            {
                double clkFreqHz = CyClock.GetClockFrequencyHz(m_params.TermQuery, false);
                if (CyClock.IsFrequencyKnown(clkFreqHz))
                {
                    numClockFreq.Text = (clkFreqHz / CyParamRanges.UNIT_KILO).ToString(); // KHz
                    numScanRate.Text = m_params.GetScanRateKHz(clkFreqHz).ToString();
                }
                m_params.ScanSpeed = CyEScanSpeedType.HIGHSPEED;
                // External clock is validated using its own error provider so it will not pervent 
                // customizer from pressing Apply button, what is necessary to display clock terminal
                epExtClock.SetError(numClockFreq, m_params.GetClockFrequencyError(m_params.ClockFrequencyHz));
            }
            else
            {
                epExtClock.SetError(numClockFreq, String.Empty);
                isErrorShow = true;
                m_params.UpdateScanSpeed(); // update Scan Speed when clock is updated
            }

            UpdateTimingControlsAccessibility();
            ValidateClockFrequency(isErrorShow);
        }

        /// <summary>
        /// Updates value of ScanRate or Clock Frequency
        /// </summary>
        public void UpdateTimimgParams()
        {
            if (m_params.ClockSource == CyEClockSource.EXTERNAL ||
                m_params.ScanTimingType == CyEScanTimingType.CLOCK_FREQ)
            {
                numScanRate.Text = m_params.GetScanRateKHz(m_params.ClockFrequencyHz).ToString();
            }
            else
            {
                try
                {
                    numClockFreq.Text = m_params.GetClockFrequencyKHz(Double.Parse(numScanRate.Text)).ToString();
                }
                catch { }
            }
            UpdateTimingControlsAccessibility();
        }
        #endregion

        #region Change controls accessibility methods
        /// <summary>
        /// Manage accessibility the controls inside Scan Timing groupbox. 
        /// NOTE: always update accessibility before the validation since validation may check whether control is 
        /// enabled or disabled.
        /// </summary>
        private void UpdateTimingControlsAccessibility()
        {
            if (m_params.ClockSource == CyEClockSource.EXTERNAL)
            {
                rbScanRate.Enabled = false;
                rbClockFreq.Enabled = false;
                numClockFreq.Enabled = false;
                numScanRate.Enabled = false;
            }
            else // if Clock Source is Internal
            {
                // Enable Timing when Clock Source is Internal
                rbScanRate.Enabled = true;
                rbClockFreq.Enabled = true;
                numScanRate.Enabled = (m_params.ScanTimingType == CyEScanTimingType.SCAN_RATE);
                numClockFreq.Enabled = (m_params.ScanTimingType == CyEScanTimingType.CLOCK_FREQ);
            }
        }

        /// <summary>
        /// Manage accessibility of the controls inside VDAC Voltage groupbox. 
        /// NOTE: always update accessibility before the validation since validation may check whether control is 
        /// enabled or disabled.
        /// </summary>
        private void UpdateVdacControlsAccessibility()
        {
            bool isVdacVoltageEnabled = false;
            bool isFixedVdacVoltageEnabled = isVdacVoltageEnabled;

            if (m_params.NegativeInput == CyENegativeInput.INTERN)
            {
                isVdacVoltageEnabled = true;
                if (m_params.VdacVoltageMode == CyEVdacVoltageMode.FIXED)
                    isFixedVdacVoltageEnabled = true;
            }

            rbRange1_20V.Enabled = isVdacVoltageEnabled;
            rbRange4_80V.Enabled = isVdacVoltageEnabled;

            rbFixed.Enabled = isVdacVoltageEnabled;
            rbPerChannel.Enabled = isVdacVoltageEnabled;
            numVdacVoltage.Enabled = isFixedVdacVoltageEnabled;
        }
        #endregion
    }

    public class CyNumericUpDown : NumericUpDown
    {
        public event EventHandler UpButtonClicked = null;
        public event EventHandler DownButtonClicked = null;

        public CyNumericUpDown() { }

        public void OnUpButtonClicked(EventArgs e)
        {
            EventHandler eventCopy = UpButtonClicked;

            if (eventCopy != null)
                eventCopy(this, e);
        }

        public void OnDownButtonClicked(EventArgs e)
        {
            EventHandler eventCopy = DownButtonClicked;

            if (eventCopy != null)
                eventCopy(this, e);
        }

        public override void DownButton()
        {
            try
            {
                OnDownButtonClicked(new EventArgs());
            }
            catch (Exception ex)
            {
                Debug.Fail(ex.Message);
            }
            base.DownButton();
        }

        public override void UpButton()
        {
            try
            {
                OnUpButtonClicked(new EventArgs());
            }
            catch (Exception ex)
            {
                Debug.Fail(ex.Message);
            }
            base.UpButton();
        }
    }
}
