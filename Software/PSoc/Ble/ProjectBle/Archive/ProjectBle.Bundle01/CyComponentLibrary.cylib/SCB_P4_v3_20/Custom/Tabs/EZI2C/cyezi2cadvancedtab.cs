/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;

namespace SCB_P4_v3_20
{
    public partial class CyEZI2CAdvancedTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members

        public override string TabName
        {
            get
            {
                return "EZI2C Advanced";
            }
        }

        public override string TabDisplayName
        {
            get { return Resources.EZI2CAdvancedTabDisplayName; }
        }

        #endregion

        public CyEZI2CAdvancedTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            m_params.Ezi2cAdvancedTab = this;

            InitializeComponent();

            m_cbSlewRate.Items.AddRange(m_params.Ezi2cSlewRate.EnumDescriptionsList);

            m_numBusVoltage.DecimalPlaces = 1;
            m_numBusVoltage.Increment = 0.1M;

            m_cbSlewRate.SelectedIndexChanged += m_cbSlewRate_SelectedIndexChanged;
            m_numBusVoltage.TextChanged += m_numBusVoltage_TextChanged;
            m_params.ScbModeChanged += m_params_ScbModeChanged;
        }

        #region Assigning parameters values to controls

        public override void UpdateUI()
        {
            m_cbSlewRate.SelectedItem = m_params.Ezi2cSlewRate.Description;
            m_numBusVoltage.Text = m_params.EZI2C_BusVoltage;

            UpdateBusVoltageState();
        }

        #endregion

        #region Event handlers

        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.EZI2C)
                ShowTab();
            else
                HideTab();
        }

        void m_cbSlewRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.Ezi2cSlewRate.Description = m_cbSlewRate.Text;

            ValidateSlewRateControl();

            UpdateBusVoltageState();
        }

        void m_numBusVoltage_TextChanged(object sender, EventArgs e)
        {
            double value = 0;
            if (m_numBusVoltage.Text != String.Empty &&
                double.TryParse(m_numBusVoltage.Text, out value) == false ||
                value < 0)
                m_errorProvider.SetError(m_numBusVoltage, Resources.InvalidBusVoltageError);
            else
                m_errorProvider.SetError(m_numBusVoltage, String.Empty);

            m_params.EZI2C_BusVoltage = m_numBusVoltage.Text;
        }

        #endregion

        #region Update controls state

        private void UpdateBusVoltageState()
        {
            double dataRate = m_params.EZI2C_ClockFromTerminal
                ? Math.Round(m_params.GetActualDataRate(CyESCBMode.EZI2C))
                : m_params.EZI2C_DataRate;

            bool showBusVoltage = m_params.IsGpioOvtCapable() &&
                                  m_params.Ezi2cSlewRate.Value == CyESlewRateType.I2C_FM_PLUS &&
                                  (dataRate > CyParamRanges.EZI2C_DATA_RATE_400);

            m_lblBusVoltage.Enabled = showBusVoltage;
            m_numBusVoltage.Enabled = showBusVoltage;
        }

        private void ValidateSlewRateControl()
        {
            double dataRate = m_params.EZI2C_ClockFromTerminal
                ? Math.Round(m_params.GetActualDataRate(CyESCBMode.EZI2C))
                : m_params.EZI2C_DataRate;

            ClearNotifications(m_cbSlewRate);

            if (dataRate > 0)
            {
                string errorMessage = m_params.GetEZI2CSlewRateError();
                if (String.IsNullOrEmpty(errorMessage) == false)
                    m_errorProvider.SetError(m_cbSlewRate, errorMessage);
            }
        }

        public void UpdateDependentControls()
        {
            ValidateSlewRateControl();
        }

        #endregion

        #region Overrides

        protected override void OnVisibleChanged(EventArgs e)
        {
            base.OnVisibleChanged(e);
            ValidateSlewRateControl();
            UpdateBusVoltageState();
        }

        #endregion
    }
}
