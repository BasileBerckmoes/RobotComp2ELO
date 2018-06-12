/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
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
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace DVDAC_v2_10
{
    public partial class CyConfigureTab : UserControl, ICyParamEditingControl
    {
        public string TabName
        {
            get { return "Basic"; }
        }

        private CyParameters m_params;
        private ErrorProvider m_errorProvider;
        private bool m_controlUpdateLocked = false;
        private List<RadioButton> m_rbResolutionList;

        #region Constructor(s)
        public CyConfigureTab(CyParameters parameters)
        {
            InitializeComponent();

            m_params = parameters;
            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            this.Dock = DockStyle.Fill;

            m_rbResolutionList = new List<RadioButton>();
            m_rbResolutionList.Add(rb9Bit);
            m_rbResolutionList.Add(rb10Bit);
            m_rbResolutionList.Add(rb11Bit);
            m_rbResolutionList.Add(rb12Bit);

            pbSymbol.BackgroundImage = Resources.Graph;

            numClock.Maximum = UInt32.MaxValue;
            numVoltageValue.Minimum = 0;
            numVoltageValue.Maximum = UInt32.MaxValue;
            numHexValue.Minimum = 0;
            numHexValue.Maximum = UInt16.MaxValue;
            numVoltageValue.TextChanged += new EventHandler(numVoltageValue_TextChanged);
            numHexValue.TextChanged += new EventHandler(numHexValue_TextChanged);
            numClock.TextChanged += new EventHandler(numClock_TextChanged);
        }

        private void CyConfigureTab_Load(object sender, EventArgs e)
        {
            // Align labels
            labelCapacity.Left = pbSymbol.Left + 133;
            labelCapacity.Top = pbSymbol.Top + 88;
            labelC.Left = pbSymbol.Left + 138;
            labelC.Top = pbSymbol.Top + 73;
            // Decrease font if label is too long
            const int DEFAULT_LABEL_C_WIDTH = 14;
            if (labelC.Width > DEFAULT_LABEL_C_WIDTH)
            {
                labelCapacity.Font = new Font(labelCapacity.Font.FontFamily, 6);
                labelC.Font = new Font(labelCapacity.Font.FontFamily, 6);
            }
        }
        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            if (m_errorProvider != null)
                errs = CheckControlForErrors(this.Controls);

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

        private List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = string.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();

            foreach (Control control in controls)
            {
                errorMessage = m_errorProvider.GetError(control);
                if (string.IsNullOrEmpty(errorMessage) == false)
                    errs.Add(new CyCustErr(errorMessage));

                if (control.Controls.Count > 0)
                    errs.AddRange(CheckControlForErrors(control.Controls));
            }
            return errs;
        }
        #endregion

        #region Assigning parameters values to controls
        public void UpdateUI()
        {
            // Value controls
            UpdateVoltageIncrement();
            numHexValue.Value = m_params.VDACValue;
            numVoltageValue.Value = (decimal)m_params.ConvertHexToVoltage(m_params.VDACValue);

            // Resolution
            m_rbResolutionList[(byte)m_params.Resolution - CyParamRange.MIN_RESOLUTION].Checked = true;

            // Range
            if (m_params.VDACRange == CyEVDACRangeType.Range_1_Volt)
                rb1VRange.Checked = true;
            else
                rb4VRange.Checked = true;

            // Clock frequency
            rbInternal.Checked = m_params.ClockSourceInternal;
            rbExternal.Checked = !rbInternal.Checked;
            numClock.Value = Math.Min((decimal)m_params.ClockFrequencykHz, numClock.Maximum);
            UpdateClockSourceDependencies();

            UpdateRangeLabels();
        }
        #endregion

        #region Private functions
        private void UpdateValueErrorProvider(object sender, double? value, UInt16 min, UInt16 max, string message, 
                                         bool hexFormat)
        {
            const double EPS = 0.01;
            string displayMin;
            string displayMax;

            if (hexFormat)
            {
                displayMin = string.Concat("0x", min.ToString("X"));
                displayMax = string.Concat("0x", max.ToString("X"));
            }
            else
            {
                displayMin = min.ToString();
                displayMax = max.ToString();
            }

            if ((value == null) || (value < min - EPS) || (value > max + EPS))
            {
                m_errorProvider.SetError((NumericUpDown)sender, string.Format(message, displayMin, displayMax));
            }
            else
            {
                m_errorProvider.SetError((NumericUpDown)sender, string.Empty);
            }
        }

        private void UpdateClockErrorProvider(double? value)
        {
            if ((value == null) || (value > m_params.GetMaxClockFrequency() + CyParamRange.EPS))
            {
                m_errorProvider.SetError(numClock, string.Format(Resources.ClockFrequencyError, 
                    CyParamRange.MIN_CLOCK_FREQUENCY, m_params.GetMaxClockFrequency()));
            }
            else
            {
                m_errorProvider.SetError(numClock, string.Empty);
            }

            if (String.IsNullOrEmpty(m_errorProvider.GetError(numClock)) && 
                (m_params.CheckFrequencyVsBusClock(value.Value) == false))
            {
                warningProvider.SetError(numClock, String.Format(Resources.BusClockCompareError, 
                    CyParameters.FormatFrequencyKHz(m_params.GetMaxFreqComparedBusClk())));
            }
            else
            {
                warningProvider.SetError(numClock, string.Empty);
            }
        }

        private void UpdateCapacityLabel()
        {
            // Calculate capacity
            double? capacity = CalculateCapacity();
            int unitsIndex = 0;

            if (capacity.HasValue)
            {
                while ((capacity < 1) && (unitsIndex < CyParamRange.CAPACITOR_UNITS.Length - 1))
                {
                    capacity *= CyParamRange.THOUSAND;
                    unitsIndex++;
                }

                if (capacity < 10) // If the number is only one digit, show 1 more digit after period.
                {
                    capacity = Math.Round(capacity.Value, 1);
                }
                else
                {
                    capacity = Math.Round(capacity.Value);
                }
                labelCapacity.Text = String.Format("{0} {1}", capacity, CyParamRange.CAPACITOR_UNITS[unitsIndex]);
            }
            labelCapacity.Visible = capacity.HasValue;
        }

        private double? CalculateCapacity()
        {
            double? capacity = null;
            double frequency = m_params.ClockFrequencykHz;

            if (frequency < CyParamRange.EPS / 2) // EPS equals 1 Hz, compare with 1/2 Hz
                return null;

            if (m_params.ClockSourceInternal == false)
            {
                frequency = m_params.GetExternalClockInkHz();
                if (CyParameters.IsFrequencyKnown(frequency) == false)
                {
                    return null;
                }
            }
            if (frequency > m_params.GetMaxClockFrequency() + CyParamRange.EPS)
            {
                return null;
            }

            double fc = frequency / Math.Pow(10, 
                CyParamRange.ATTENUATION_VALUES[(byte)m_params.Resolution - CyParamRange.MIN_RESOLUTION] / 20.0);
            double fdither = fc / (Math.Pow(2, (byte)m_params.Resolution - CyParamRange.MIN_RESOLUTION + 1));
            int resistance = (m_params.VDACRange == CyEVDACRangeType.Range_1_Volt) ? CyParamRange.RESISTANCE_1V_VALUE :
                                                                                     CyParamRange.RESISTANCE_4V_VALUE;
            capacity = 1 / (2 * Math.PI * fdither * resistance);
            return capacity;
        }

        private void UpdateRangeLabels()
        {
            rb1VRange.Text = String.Format(Resources.RangeLabelText, "1.020", 
                                           m_params.GetRangeCoef(CyParamRange.MAX_VOLTAGE_1V_VALUE));
            rb4VRange.Text = String.Format(Resources.RangeLabelText, "4.080", 
                                           m_params.GetRangeCoef(CyParamRange.MAX_VOLTAGE_4V_VALUE));
        }

        private void RecalculateValueFields()
        {
            UpdateVoltageIncrement();
            numVoltageValue.Value = (decimal)m_params.ConvertHexToVoltage((UInt16)numHexValue.Value);

            if (numVoltageValue.Value > m_params.GetMaxVoltageValue())
            {
                numVoltageValue.Value = m_params.GetMaxVoltageValue();
                numHexValue.Value = m_params.ConvertVoltageToHex((double)numVoltageValue.Value);
            }
           
        }

        private void UpdateVoltageIncrement()
        {
            numVoltageValue.Increment = (decimal)m_params.GetRangeCoef();
            if ((double)numVoltageValue.Increment > 0.99) // e.g. int
            {
                numVoltageValue.DecimalPlaces = 0;
            }
            else if ((double)numVoltageValue.Increment > 0.49) // e.g. 0.5
            {
                numVoltageValue.DecimalPlaces = 1;
            }
            else // e.g. 0.25
            {
                numVoltageValue.DecimalPlaces = 2;
            }
        }
        #endregion

        #region Event handlers
        private void numVoltageValue_ValueChanged(object sender, EventArgs e)
        {
            if (m_controlUpdateLocked == false)
            {
                // Round voltage value to the nearest possible
                double step = m_params.GetRangeCoef();
                numVoltageValue.Value = (decimal)(Math.Round((double)numVoltageValue.Value / step) * step);
            }
        }

        void numVoltageValue_TextChanged(object sender, EventArgs e)
        {
            // Get value from control
            double? voltageValue = m_params.ConvertStrToDouble(numVoltageValue.Text);

            // Update error provider
            UpdateValueErrorProvider(sender, voltageValue, 0, m_params.GetMaxVoltageValue(),
                                        Resources.VoltageValueError, false);

            // Update VDAC hex value
            if (m_controlUpdateLocked == false)
            {
                m_controlUpdateLocked = true;
                if (voltageValue.HasValue)
                    numHexValue.Value = m_params.ConvertVoltageToHex(voltageValue.Value);
                m_controlUpdateLocked = false;
            }
        }

        void numHexValue_TextChanged(object sender, EventArgs e)
        {
            // Get value from control
            UInt16? hexValue = m_params.ConvertStrToUInt16(numHexValue.Text, true);

            // Update error provider
            UpdateValueErrorProvider(sender, hexValue, CyParamRange.MIN_HEX_VALUE, m_params.GetMaxHexValue(),
                    Resources.HexValueError, true);

            if (m_params.m_globalEditMode && hexValue.HasValue)
            {
                m_params.VDACValue = hexValue.Value;
            }

            // Update VDAC voltage value
            if (m_controlUpdateLocked == false)
            {
                m_controlUpdateLocked = true;
                if (hexValue.HasValue)
                    numVoltageValue.Value = (decimal)m_params.ConvertHexToVoltage(hexValue.Value);
                m_controlUpdateLocked = false;
            }
        }

        private void rbResolution_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked == false)
                return;

            m_params.Resolution = (CyEResolutionType)(CyParamRange.MIN_RESOLUTION + 
                                                      m_rbResolutionList.IndexOf((RadioButton)sender));

            if (m_params.m_globalEditMode)
            {
                numHexValue.Value = CyParamRange.DEFAULT_HEX_VALUES[(byte)m_params.Resolution - 
                                                                    CyParamRange.MIN_RESOLUTION];
            }

            RecalculateValueFields();
            UpdateRangeLabels();
            UpdateCapacityLabel();
        }

        private void rbRange_CheckedChanged(object sender, EventArgs e)
        {
            if ((((RadioButton)sender).Checked) == false)
                return;

            m_params.VDACRange = (rb1VRange.Checked) ? CyEVDACRangeType.Range_1_Volt : CyEVDACRangeType.Range_4_Volt;
            
            RecalculateValueFields();
            UpdateCapacityLabel();

            // Clock frequency update
            if ((numClock.Value > m_params.GetMaxClockFrequency()) && m_params.ClockSourceInternal)
            {
                numClock.Value = m_params.GetMaxClockFrequency();
            }
            UpdateClockErrorProvider((double)numClock.Value);
        }
        #endregion

        #region Clock related functions
        public void UpdateDesign(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            if (m_params.ClockSourceInternal == false)
            {
                UpdateClockSourceDependencies();
            }
        }

        private void rbClockSource_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            m_params.ClockSourceInternal = (rb == rbInternal);
            UpdateClockSourceDependencies();
        }

        private void numClock_TextChanged(object sender, EventArgs e)
        {
            double? clockValue = m_params.ConvertStrToDouble(numClock.Text);

            // Update error provider
            UpdateClockErrorProvider(clockValue);

            if (m_params.m_globalEditMode && clockValue.HasValue)
            {
                m_params.ClockFrequencykHz = clockValue.Value;
            }
            UpdateCapacityLabel();
        }

        private void UpdateClockSourceDependencies()
        {
            double frequency;
            bool freqUnknown = false;
            if (m_params.ClockSourceInternal == false)
            {
                frequency = m_params.GetExternalClockInkHz();
                freqUnknown = !CyParameters.IsFrequencyKnown(frequency);
                if (freqUnknown == false)
                {
                    if (numClock.Maximum < (decimal)frequency)
                    {
                        numClock.Maximum = (decimal)frequency;
                    }
                    else
                    {
                        numClock.Maximum = UInt16.MaxValue;
                    }
                    numClock.Value = (uint)frequency;
                }
            }

            UpdateClockErrorProvider((double)numClock.Value);

            numClock.Enabled = m_params.ClockSourceInternal;

            lblUnknownFreq.Visible = freqUnknown;
            numClock.Visible = !freqUnknown;

            UpdateCapacityLabel();
        }
        #endregion Clock related functions
    }
}
