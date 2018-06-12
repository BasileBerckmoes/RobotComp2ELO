/*******************************************************************************
* Copyright 2015-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;

namespace SCB_P4_v4_0
{
    /// <summary>
    /// The tab display name is I2C Pins starting from SCB_P4_v4_0
    /// </summary>
    public partial class CyI2CAdvancedTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members

        public override string TabName
        {
            get
            {
                return "I2C Pins";
            }
        }

        public override string TabDisplayName
        {
            get { return Resources.I2CAdvancedTabDisplayName; }
        }

        #endregion

        public CyI2CAdvancedTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            m_params.I2cAdvancedTab = this;

            InitializeComponent();

            m_cbSlewRate.Items.AddRange(m_params.I2cSlewRate.EnumDescriptionsList);

            m_numBusVoltage.DecimalPlaces = 1;
            m_numBusVoltage.Increment = 0.1M;

            m_cbSlewRate.SelectedIndexChanged += m_cbSlewRate_SelectedIndexChanged;
            m_numBusVoltage.TextChanged += m_numBusVoltage_TextChanged;
            m_params.ScbModeChanged += m_params_ScbModeChanged;
        }

        #region Assigning parameters values to controls

        public override void UpdateUI()
        {
            m_chbShowTerminals.Checked = m_params.I2C_ShowTerminals;

            m_cbSlewRate.SelectedItem = m_params.I2cSlewRate.Description;
            m_numBusVoltage.Text = m_params.I2C_BusVoltage;

            UpdateControlsEnableState();

            ValidateShowTerminalsControl();
            ValidateSlewRateControl();
        }

        #endregion

        #region Event handlers

        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.I2C)
                ShowTab();
            else
                HideTab();
        }

        void m_cbSlewRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.I2cSlewRate.Description = m_cbSlewRate.Text;

            ValidateSlewRateControl();

            UpdateControlsEnableState();
        }

        void m_numBusVoltage_TextChanged(object sender, EventArgs e)
        {
            double value = 0;

            if (m_numBusVoltage.Text != String.Empty &&
                double.TryParse(m_numBusVoltage.Text, out value) == false || value < 0)
            {
                m_errorProvider.SetError(m_numBusVoltage, Resources.InvalidBusVoltageError);
            }
            else
            {
                m_errorProvider.SetError(m_numBusVoltage, String.Empty);
            }

            m_params.I2C_BusVoltage = m_numBusVoltage.Text;
        }

        private void m_chbShowTerminals_CheckedChanged(object sender, EventArgs e)
        {
            m_params.I2C_ShowTerminals = m_chbShowTerminals.Checked;
            UpdateControlsEnableState();
            ValidateShowTerminalsControl();
        }
        #endregion

        #region Update controls state

        private void UpdateControlsEnableState()
        {
            m_panelSlewRate.Enabled = (m_params.I2C_ShowTerminals == false);
            UpdateBusVoltageState();
        }

        private void UpdateBusVoltageState()
        {
            double dataRate = m_params.I2C_ClockFromTerminal
                ? Math.Round(m_params.GetActualDataRate(CyESCBMode.I2C))
                : m_params.I2C_DataRate;

            bool showBusVoltage = m_params.IsGpioOvtCapable() &&
                                  m_params.I2cSlewRate.Value == CyESlewRateType.I2C_FM_PLUS &&
                                  (dataRate > CyParamRanges.I2C_DATA_RATE_400);

            m_lblBusVoltage.Enabled = showBusVoltage;
            m_numBusVoltage.Enabled = showBusVoltage;
        }

        private void ValidateSlewRateControl()
        {
            double dataRate = m_params.I2C_ClockFromTerminal
                ? Math.Round(m_params.GetActualDataRate(CyESCBMode.I2C))
                : m_params.I2C_DataRate;

            ClearNotifications(m_cbSlewRate);

            if (dataRate > 0)
            {
                string errorMessage = m_params.GetI2CSlewRateError();
                if (String.IsNullOrEmpty(errorMessage) == false)
                    m_errorProvider.SetError(m_cbSlewRate, errorMessage);
            }
        }

        private void ValidateShowTerminalsControl()
        {
            m_errorProvider.SetError(m_chbShowTerminals, CyParameters.GetShowTerminalsError(m_params));
        }

        public void UpdateDependentControls()
        {
            ValidateSlewRateControl();
            ValidateShowTerminalsControl();
            UpdateControlsEnableState();
        }
        #endregion

        #region Overrides

        protected override void OnVisibleChanged(EventArgs e)
        {
            base.OnVisibleChanged(e);
            UpdateDependentControls();
        }
        #endregion
    }
}
