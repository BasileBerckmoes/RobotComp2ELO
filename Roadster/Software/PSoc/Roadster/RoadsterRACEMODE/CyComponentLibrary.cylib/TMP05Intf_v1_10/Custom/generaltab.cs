/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Windows.Forms;

namespace TMP05Intf_v1_10
{
    public partial class CyGeneralTab : CyTabWrapper
    {
        public override string TabName
        {
            get { return "General"; }
        }

        ErrorProvider m_errorProvider;

        public CyGeneralTab(CyParameters parameters)
            : base(parameters)
        {
            m_params = parameters;
            InitializeComponent();
            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            foreach (byte item in CyParameters.NumSensorsValues)
                cbNumSensors.Items.Add(item);
        }

        public void UpdateUI()
        {
            UpdateMode();
            UpdateNumSensors();
        }

        private void UpdateMode()
        {
            string errorMessage = string.Empty;
            if (m_params.ContinuousMode.HasValue)
            {
                if (m_params.ContinuousMode.Value)
                    rbContinuousMode.Checked = true;
                else
                    rbOneShotMode.Checked = true;
            }
            else
            {
                errorMessage = string.Format(Resources.UnrecognizableFormat, CyParamName.CONTINUOUS_MODE);
                rbContinuousMode.Checked = false;
                rbOneShotMode.Checked = false;
            }
            m_errorProvider.SetError(rbContinuousMode, errorMessage);
        }

        private void UpdateNumSensors()
        {
            byte numSensorsMin = CyParameters.NumSensorsValues[0];
            byte numSensorsMax = CyParameters.NumSensorsValues[CyParameters.NumSensorsValues.Length - 1];
            string errorMessage = string.Empty;

            if (m_params.NumSensors == null)
            {
                errorMessage = string.Format(Resources.UnrecognizableFormat, CyParamName.NUM_SENSORS);
                SetEmptyItem(cbNumSensors);
            }
            else if (m_params.NumSensors.Value < numSensorsMin || m_params.NumSensors.Value > numSensorsMax)
            {
                errorMessage = string.Format(Resources.NumSensorsValifator, numSensorsMin, numSensorsMax);
                SetEmptyItem(cbNumSensors);
            }
            else
            {
                cbNumSensors.SelectedItem = m_params.NumSensors;
                RemoveEmptyItem(cbNumSensors);
            }
            m_errorProvider.SetError(cbNumSensors, errorMessage);
        }

        private void SetEmptyItem(ComboBox comboBox)
        {
            if (comboBox.Items.Contains(string.Empty) == false)
            {
                comboBox.Items.Insert(0, string.Empty);
                bool currentGEM = m_params.m_globalEditMode;
                m_params.m_globalEditMode = false;
                comboBox.SelectedIndex = 0;
                m_params.m_globalEditMode = currentGEM;
            }
        }

        private void RemoveEmptyItem(ComboBox comboBox)
        {
            if (comboBox.Items.Contains(string.Empty))
                comboBox.Items.Remove(string.Empty);
        }

        private void cbNumSensors_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.m_globalEditMode)
            {
                try
                {
                    m_params.NumSensors = Convert.ToByte(((ComboBox)sender).SelectedItem);
                    UpdateNumSensors();
                }
                catch { }
            }
        }

        private void rbMode_Click(object sender, EventArgs e)
        {
            m_params.ContinuousMode = (sender == rbContinuousMode);
            UpdateMode();
        }
    }
}
