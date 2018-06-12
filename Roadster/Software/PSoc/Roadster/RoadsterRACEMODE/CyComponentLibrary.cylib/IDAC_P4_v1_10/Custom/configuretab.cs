/*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace IDAC_P4_v1_10
{
    public partial class CyConfigureTab : UserControl, ICyParamEditingControl
    {
        private const double EPS = 0.0001;

        public string TabName
        {
            get { return "Configure"; }
        }

        private readonly CyParameters m_params;
        private readonly ErrorProvider m_errorProvider;
        private bool m_controlUpdateLocked = false;

        #region Constructor(s)
        public CyConfigureTab(CyParameters parameters)
        {
            m_params = parameters;
            InitializeComponent();
            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            numCurrentValue.Minimum = 0;
            numCurrentValue.Maximum = int.MaxValue;
            numConvertedValue.Minimum = 0;
            numConvertedValue.Maximum = int.MaxValue;
            numCurrentValue.TextChanged += numCurrentValue_TextChanged;
            numCurrentValue.ValueChanged += numCurrentValue_ValueChanged;
            numConvertedValue.TextChanged += numConvertedValue_TextChanged;
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

            foreach (string paramName in m_params.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_params.InstQuery.GetCommittedParam(paramName);
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
            string errorMessage;
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
            // Polarity controls
            if (m_params.Polarity == CyEPolarityType.Source)
                rbPositive.Checked = true;
            else
                rbNegative.Checked = true;

            // Value controls
            numCurrentValue.Increment = (decimal)m_params.GetRangeCoeff();
            numConvertedValue.Text = m_params.IDACValue.ToString("X");
            numCurrentValue.Text = m_params.GetCurrentValue(numConvertedValue.Text);

            // Resolution
            switch (m_params.Resolution)
            {
                case CyParamRange.RESOLUTION_7:
                    rb7Bit.Checked = true;
                    break;
                case CyParamRange.RESOLUTION_8:
                    rb8Bit.Checked = true;
                    break;
                default:
                    rb8Bit.Checked = true;
                    break;
            }

            // Range
            if (m_params.IDACRange == CyEIDACRangeType.LowRange)
                rbLowRange.Checked = true;
            else
                rbHighRange.Checked = true;

            UpdateRangesDescription();
        }

        private void UpdateRangesDescription()
        {
            if (m_params.Resolution == CyParamRange.RESOLUTION_7)
            {
                rbLowRange.Text = Resources.LowRange7Bit;
                rbHighRange.Text = Resources.HighRange7Bit;
            }
            else if (m_params.Resolution == CyParamRange.RESOLUTION_8)
            {
                rbLowRange.Text = Resources.LowRange8Bit;
                rbHighRange.Text = Resources.HighRange8Bit;
            }
        }
        #endregion

        #region Error provider update
        private bool UpdateErrorProvider(object sender, double value, int min, double max, string message)
        {
            return UpdateErrorProvider(sender, value, min, max, message, false);
        }

        private bool UpdateErrorProvider(object sender, double value, int min, double max, string message,
            bool hexFormat)
        {
            bool isValid;
            string displayMin;
            string displayMax;

            if (hexFormat)
            {
                displayMin = string.Concat("0x", min.ToString("X2"));
                displayMax = string.Concat("0x", ((int)max).ToString("X2"));
            }
            else
            {
                displayMin = min.ToString();
                displayMax = max.ToString();
            }

            if (value < min || value > max + EPS)
            {
                m_errorProvider.SetError((NumericUpDown)sender, string.Format(message, displayMin, displayMax));
                isValid = false;
            }
            else
            {
                m_errorProvider.SetError((NumericUpDown)sender, string.Empty);
                isValid = true;
            }
            return isValid;
        }
        #endregion

        #region Event handlers
        private void numCurrentValue_ValueChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode == false)
                return;

            if (String.IsNullOrEmpty(m_errorProvider.GetError(numCurrentValue)))
            {
                double d = (double)numCurrentValue.Value / m_params.GetRangeCoeff();
                if (Math.Abs(d - Math.Round(d)) > EPS)
                {
                    double newCurrentValue = m_params.GetRangeCoeff() * Math.Round(d);
                    numCurrentValue.Text = newCurrentValue.ToString();
                }
            }
        }

        private void numCurrentValue_TextChanged(object sender, EventArgs e)
        {
            // Get value from control
            double currentValue = -1;
            double.TryParse(((NumericUpDown)sender).Text, out currentValue);

            // Update error provider
            UpdateErrorProvider(sender, currentValue, CyParamRange.IDAC_CURR_MIN,
                m_params.GetMaxCurrentValue(), Resources.CurrentValueError);

            // Update IDAC converted (hex) value
            if (m_controlUpdateLocked == false)
            {
                m_controlUpdateLocked = true;
                numConvertedValue.Text = m_params.GetConvertedValue(numCurrentValue.Text);
                m_controlUpdateLocked = false;
            }
        }

        private void numConvertedValue_TextChanged(object sender, EventArgs e)
        {
            // Get value from control
            int convertedValue = -1;
            try
            {
                convertedValue = Convert.ToInt32(((NumericUpDown)sender).Text, 16);
            }
            catch (Exception)
            {
            }

            // Update error provider
            if (UpdateErrorProvider(sender, convertedValue, CyParamRange.IDAC_CONV_MIN, m_params.GetMaxConvertedValue(),
                Resources.ConvertedValueError, true))
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.IDACValue = Convert.ToByte(convertedValue);
                }
            }

            // Update IDAC current value
            if (m_controlUpdateLocked == false)
            {
                m_controlUpdateLocked = true;
                numCurrentValue.Text = m_params.GetCurrentValue(numConvertedValue.Text);
                m_controlUpdateLocked = false;
            }
        }

        private void rbPositive_CheckedChanged(object sender, EventArgs e)
        {
            m_params.Polarity = (((RadioButton)sender).Checked) ? CyEPolarityType.Source : CyEPolarityType.Sink;
        }

        private void rb8Bit_CheckedChanged(object sender, EventArgs e)
        {
            bool choise = ((RadioButton)sender).Checked;
            m_params.Resolution = (choise ? CyParamRange.RESOLUTION_8 : CyParamRange.RESOLUTION_7);
            numConvertedValue.Maximum = choise ? CyParamRange.MAX_8BIT_VALUE : CyParamRange.MAX_7BIT_VALUE;
            // Update hex value error provider
            m_controlUpdateLocked = true;
            numConvertedValue_TextChanged(numConvertedValue, new EventArgs());
            numCurrentValue_TextChanged(numCurrentValue, new EventArgs());
            m_controlUpdateLocked = false;

            UpdateRangesDescription();
        }

        private void rbLowRange_CheckedChanged(object sender, EventArgs e)
        {
            m_params.IDACRange = (((RadioButton)sender).Checked)
                ? CyEIDACRangeType.LowRange
                : CyEIDACRangeType.HighRange;

            // Update IDAC values
            numCurrentValue.Increment = (decimal)m_params.GetRangeCoeff();
            numCurrentValue.Text = m_params.GetCurrentValue(numConvertedValue.Text);
        }
        #endregion
    }
}
