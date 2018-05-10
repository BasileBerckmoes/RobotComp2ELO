/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace IDAC7_P6_v1_0
{
    public partial class CyConfigureTab : UserControl, ICyParamEditingControl
    {
        private const double EPS = 0.0001;

        public string TabName
        {
            get { return CyCustomizer.CONFIGURE_TAB_NAME; }
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
            numConvertedValue.Maximum = CyParamRange.IDAC_CONV_7_BIT_MAX;
            numCurrentValue.TextChanged += numCurrentValue_TextChanged;
            numCurrentValue.ValueChanged += numCurrentValue_ValueChanged;
            numConvertedValue.TextChanged += numConvertedValue_TextChanged;

            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
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
            if (m_params.Polarity == CyEPolarityType.POL_SOURCE)
                rbPositive.Checked = true;
            else
                rbNegative.Checked = true;

            // Value controls
            numCurrentValue.Increment = (decimal)m_params.GetRangeCoeff();
            numConvertedValue.Text = m_params.IDACValue.ToString("X");
            numCurrentValue.Text = m_params.GetCurrentValue(numConvertedValue.Text);

            // Range
            if (m_params.IDACRange == CyEIDACRangeType.RNG_4_96UA)
                rbRange_4_96.Checked = true;
            else if (m_params.IDACRange == CyEIDACRangeType.RNG_9_92UA)
                rbRange_9_92.Checked = true;
            else if (m_params.IDACRange == CyEIDACRangeType.RNG_39_69UA)
                rbRange_39_69.Checked = true;
            else if (m_params.IDACRange == CyEIDACRangeType.RNG_79_38UA)
                rbRange_79_38.Checked = true;
            else if (m_params.IDACRange == CyEIDACRangeType.RNG_317_5UA)
                rbRange_317_5.Checked = true;
            else if (m_params.IDACRange == CyEIDACRangeType.RNG_635_0UA)
                rbRange_635_0.Checked = true;

        }
        #endregion

        #region Error provider update
        private bool UpdateErrorProvider(object sender, double value, int min, double max, string message,
            bool hexFormat = false)
        {
            bool isValid;
            string displayMin;
            string displayMax;

            if (hexFormat)
            {
                displayMin = string.Concat("0x", min.ToString("X"));
                displayMax = string.Concat("0x", ((int)max).ToString("X"));
            }
            else
            {
                displayMin = min.ToString();
                displayMax = max.ToString();
            }

            if (value < min - EPS || value > max + EPS)
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
                convertedValue = Convert.ToInt32(numConvertedValue.Text, 16);
            }
            catch (Exception)
            {
            }

            // Update error provider
            if (UpdateErrorProvider(sender, convertedValue, CyParamRange.IDAC_CONV_MIN, 
                CyParamRange.IDAC_CONV_7_BIT_MAX, Resources.ConvertedValueError, true))
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
            m_params.Polarity = rbPositive.Checked ? CyEPolarityType.POL_SOURCE : CyEPolarityType.POL_SINK;
        }

        private void rbRange_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rbSender = (RadioButton)sender;

            if (rbSender.Checked == false)
                return;

            if (rbSender == rbRange_4_96)
            {
                m_params.IDACRange = CyEIDACRangeType.RNG_4_96UA;
            }
            else if (rbSender == rbRange_9_92)
            {
                m_params.IDACRange = CyEIDACRangeType.RNG_9_92UA;
            }
            else if (rbSender == rbRange_39_69)
            {
                m_params.IDACRange = CyEIDACRangeType.RNG_39_69UA;
            }
            else if (rbSender == rbRange_79_38)
            {
                m_params.IDACRange = CyEIDACRangeType.RNG_79_38UA;
            }
            else if (rbSender == rbRange_317_5)
            {
                m_params.IDACRange = CyEIDACRangeType.RNG_317_5UA;
            }
            else if (rbSender == rbRange_635_0)
            {
                m_params.IDACRange = CyEIDACRangeType.RNG_635_0UA;
            }
            else
            {
                Debug.Fail("rbPositive_CheckedChanged() not handled.");
            }

            // Update IDAC values
            numCurrentValue.Increment = (decimal)m_params.GetRangeCoeff();
            numCurrentValue.Text = m_params.GetCurrentValue(numConvertedValue.Text);
        }
        #endregion

    }
}
