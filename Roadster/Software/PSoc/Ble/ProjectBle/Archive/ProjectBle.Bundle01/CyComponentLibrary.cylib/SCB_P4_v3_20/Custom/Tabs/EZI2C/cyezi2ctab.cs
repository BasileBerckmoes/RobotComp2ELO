/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;
using System.Windows.Forms;

namespace SCB_P4_v3_20.Tabs.EZI2C
{
    public partial class CyEZI2CTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "EZI2C Basic";
            }
        }

        public override string TabDisplayName
        {
            get { return Resources.EZI2CBasicTabDisplayName; }
        }
        #endregion

        #region Constructor(s)
        public CyEZI2CTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            m_params = parameters;

            InitializeComponent();

            m_lblSlaveAddressInfoIcon.Image = Resources.InformationIconPng;

            m_cbSubAddressSize.Items.Clear();
            m_cbSubAddressSize.Items.AddRange(m_params.EzI2CSubAddressSize.EnumDescriptionsList);

            #region Assigning event handlers
            m_chbClockStretching.CheckedChanged += m_chbCheckedChanged;
            m_chbClockFromTerminal.Enabled = m_params.InstQuery.IsInSystemBuilder ? false : true;
            m_chbClockFromTerminal.CheckedChanged += m_chbCheckedChanged;
            m_chbByteMode.CheckedChanged += m_chbCheckedChanged;
            m_chbEnableWakeup.CheckedChanged += m_chbCheckedChanged;

            m_cbDataRate.TextChanged += m_cbDataRate_TextChanged;
            m_cbDataRate.EnabledChanged += m_cbDataRate_TextChanged;
            m_cbNumberOfAddresses.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSubAddressSize.SelectedIndexChanged += m_cb_SelectedIndexChanged;

            m_txtPrimarySlaveAddress.TextChanged += m_txtSlaveAddressTextChanged;
            m_txtSecondarySlaveAddress.TextChanged += m_txtSlaveAddressTextChanged;
            m_params.ScbModeChanged += m_params_ScbModeChanged;
            m_params.DesignUpdates += m_params_DesignUpdates;
            #endregion

            if (m_params.InstQuery.IsInSystemBuilder)
            {
                HideClockFromTerminal();
            }
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            m_chbClockFromTerminal.Checked = m_params.EZI2C_ClockFromTerminal;
            m_chbClockStretching.Checked = m_params.EZI2C_StretchClock;
            m_chbByteMode.Checked = m_params.EZI2C_EnableByteMode;
            m_chbEnableWakeup.Checked = m_params.EZI2C_EnableWakeupFromSleep;

            m_cbDataRate.Text = m_params.EZI2C_DataRate.ToString();

            m_txtPrimarySlaveAddress.Text = m_params.EZI2C_PrimarySlaveAddressStr;
            m_txtSecondarySlaveAddress.Text = m_params.EZI2C_SecondarySlaveAddressStr;
            m_cbNumberOfAddresses.SelectedItem = m_params.EzI2CNumberOfAddresses.Description;
            m_cbSubAddressSize.SelectedItem = m_params.EzI2CSubAddressSize.Description;

            UpdateSlaveAddressesConfig();
            UpdateClock();
            UpdateEnableWakeUpEnable();
            UpdateByteModeCheckBoxState();
            UpdateLabelAddressInfoVisibility();

            //To update error provider for m_cbDataRate
            m_cbDataRate_TextChanged(m_cbDataRate, new EventArgs());
        }

        private void UpdateSlaveAddressesConfig()
        {
            if (m_params.EZI2C_StretchClock == false)
            {
                m_cbNumberOfAddresses.Text = "1";
                m_cbNumberOfAddresses.Enabled = false;
                m_lblNumberOfAddresses.Enabled = false;
            }
            else
            {
                m_cbNumberOfAddresses.Enabled = true;
                m_lblNumberOfAddresses.Enabled = true;
            }

            m_lblSecondarySlaveAddress.Enabled = m_params.EZI2C_StretchClock &&
                (m_params.EzI2CNumberOfAddresses.Value != CyEEZI2CNumberOfAddressesType.ONE_ADDRESS);
            m_txtSecondarySlaveAddress.Enabled = m_params.EZI2C_StretchClock &&
                (m_params.EzI2CNumberOfAddresses.Value != CyEEZI2CNumberOfAddressesType.ONE_ADDRESS);
            m_txtSlaveAddressTextChanged(m_txtSecondarySlaveAddress, null);
        }
        #endregion

        #region Event handlers
        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.EZI2C)
            {
                ShowTab();
                SelectTab();
            }
            else
            {
                HideTab();
            }
        }

        void m_params_DesignUpdates(object sender, EventArgs e)
        {
            UpdateClock();
        }

        private void m_chbCheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_chbClockStretching)
                {
                    m_params.EZI2C_StretchClock = m_chbClockStretching.Checked;

                    UpdateSlaveAddressesConfig();
                    UpdateEnableWakeUpEnable();
                    UpdateByteModeCheckBoxState();

                    //To update error provider for m_cbDataRate
                    m_cbDataRate_TextChanged(m_cbDataRate, new EventArgs());
                }
                else if (sender == m_chbClockFromTerminal)
                {
                    m_params.EZI2C_ClockFromTerminal = m_chbClockFromTerminal.Checked;
                    UpdateClock();
                }
                else if (sender == m_chbByteMode)
                {
                    m_params.EZI2C_EnableByteMode = m_chbByteMode.Checked;
                    UpdateByteModeCheckBoxState();
                }
                else if (sender == m_chbEnableWakeup)
                {
                    m_params.EZI2C_EnableWakeupFromSleep = m_chbEnableWakeup.Checked;
                    UpdateEnableWakeUpEnable();
                    m_txtSlaveAddressTextChanged(m_txtPrimarySlaveAddress, new EventArgs());
                    UpdateLabelAddressInfoVisibility();
                }
            }
        }

        private void m_cbDataRate_TextChanged(object sender, EventArgs e)
        {
            double dataRateValue = 0;
            bool parsed = double.TryParse(m_cbDataRate.Text, out dataRateValue);

            if (parsed && m_params.GlobalEditMode && m_params.EZI2C_DataRate != (UInt16)dataRateValue)
            {
                m_params.EZI2C_DataRate = (UInt16)dataRateValue;
                m_params.InternalClockNeedUpdate = true;
            }
            int max = (m_params.EZI2C_StretchClock && !m_params.IsScbIPV1) ? CyParamRanges.I2C_DATA_RATE_MAX :
                CyParamRanges.I2C_DATA_RATE_NON_ClOCK_STRETCHING_MAX;
            string error = (m_params.EZI2C_StretchClock == false) ? Resources.DataRateValueError : m_params.IsScbIPV1 ?
                Resources.DataRateDeviceError : Resources.DataRateValueErrorNonClockStretching;

            if ((m_cbDataRate.Enabled == false) || (parsed && dataRateValue >= CyParamRanges.I2C_DATA_RATE_MIN &&
                dataRateValue <= max))
            {
                m_errorProvider.SetError(m_cbDataRate, string.Empty);
                UpdateClock();
            }
            else
            {
                m_errorProvider.SetError(m_cbDataRate, string.Format(error, CyParamRanges.I2C_DATA_RATE_MIN, max));
            }

            // Advanced tab has controls that depend on data rate and actual data rate, 
            // so they need to be re-validated
            m_params.Ezi2cAdvancedTab.UpdateDependentControls();
        }

        private void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbSubAddressSize)
                {
                    m_params.EzI2CSubAddressSize.Description = m_cbSubAddressSize.Text;
                }
                else if (sender == m_cbNumberOfAddresses)
                {
                    m_params.EzI2CNumberOfAddresses.Description = m_cbNumberOfAddresses.Text;
                    UpdateSlaveAddressesConfig();
                    UpdateLabelAddressInfoVisibility();
                }
            }
        }

        private void m_txtSlaveAddressTextChanged(object sender, EventArgs e)
        {
            if (sender == m_txtPrimarySlaveAddress || sender == m_txtSecondarySlaveAddress)
            {
                Control currentControl = sender as Control;
                Control otherControl = (currentControl == m_txtPrimarySlaveAddress) ?
                    m_txtSecondarySlaveAddress : m_txtPrimarySlaveAddress;
                string currErrorStr = GetSlaveAddressValue(currentControl);
                string otherErrorStr = GetSlaveAddressValue(otherControl);
                string oddValueErrorStr1 = GetSlaveAddressError(m_params.EZI2C_PrimarySlaveAddress, m_params);
                string oddValueErrorStr2 = GetSlaveAddressError(m_params.EZI2C_SecondarySlaveAddress, m_params);

                if (m_txtSecondarySlaveAddress.Enabled && string.IsNullOrEmpty(currErrorStr) &&
                    string.IsNullOrEmpty(otherErrorStr) &&
                    (m_params.EZI2C_PrimarySlaveAddress == m_params.EZI2C_SecondarySlaveAddress))
                {
                    m_errorProvider.SetError(currentControl, Resources.EZI2CSlaveAddressesEqualError);
                    m_errorProvider.SetError(otherControl, Resources.EZI2CSlaveAddressesEqualError);
                }
                else
                {
                    m_errorProvider.SetError(currentControl, currErrorStr);
                    m_errorProvider.SetError(otherControl, otherErrorStr);
                }

                if (String.IsNullOrEmpty(m_errorProvider.GetError(m_txtPrimarySlaveAddress)))
                {
                    m_errorProvider.SetError(m_txtPrimarySlaveAddress, oddValueErrorStr1);
                }
                if (m_txtSecondarySlaveAddress.Enabled &&
                    String.IsNullOrEmpty(m_errorProvider.GetError(m_txtSecondarySlaveAddress)))
                {
                    m_errorProvider.SetError(m_txtSecondarySlaveAddress, oddValueErrorStr2);
                }
            }
        }
        #endregion

        #region Auxiliary methods
        /// <summary>
        /// Parse slave address value from the Text property of the control. If the value is successfully parsed, it is
        /// stored in symbol.
        /// </summary>
        /// <param name="control">Control to parse value from.</param>
        /// <returns>Error string on parsing error, or empty string if parsed successfully.</returns>
        private string GetSlaveAddressValue(Control control)
        {
            // Don't check Secondary Slave Address if its control is disabled
            if ((control == m_txtSecondarySlaveAddress) && (control.Enabled == false))
            {
                return string.Empty;
            }

            byte value = 0;
            bool isValueHex = control.Text.ToLower().StartsWith(CyParameters.HEX_PREFIX);

            string stringToParse = control.Text;
            if (isValueHex)
            {
                // Cut off the hexadecimal display prefix ("0x")
                stringToParse = control.Text.Remove(0, CyParameters.HEX_PREFIX.Length);
            }

            // Parse value with 10 or 16 base
            bool parsed = true;
            try
            {
                value = Convert.ToByte(stringToParse, isValueHex ? 16 : 10);
            }
            catch
            {
                parsed = false;
            }

            // If value's parsed then set the value to the symbol
            if (parsed)
            {
                if (control == m_txtPrimarySlaveAddress)
                {
                    m_params.EZI2C_PrimarySlaveAddress = value;
                    m_params.EZI2C_IsPrimarySlaveAddressHex = isValueHex;
                }
                else if (control == m_txtSecondarySlaveAddress)
                {
                    m_params.EZI2C_SecondarySlaveAddress = value;
                    m_params.EZI2C_IsSecondarySlaveAddressHex = isValueHex;
                }
            }

            byte min = CyParamRanges.I2C_SLAVE_ADDRESS_MIN;
            byte max = CyParamRanges.I2C_SLAVE_ADDRESS_MAX;

            return ((parsed == false) || (value < min) || (value > max)) ?
                string.Format(Resources.EZI2CSlaveAddressError, min, max) : string.Empty;
        }

        public static string GetSlaveAddressError(byte slaveAddressValue, CyParameters parameters)
        {
            if (!parameters.IsScbIPV0)
                return string.Empty;

            string res = string.Empty;
            if ((parameters.EZI2C_EnableWakeupFromSleep == true) && ((slaveAddressValue & 1) != 0))
            {
                res = Resources.SlaveAddressOddError;
            }

            return res;
        }

        private void UpdateEnableWakeUpEnable()
        {
            if (m_params.IsScbIPV0)
            {
                if (m_params.EZI2C_StretchClock == false)
                {
                    if (m_chbEnableWakeup.Checked)
                    {
                        m_chbEnableWakeup.Enabled = true;
                        m_errorProvider.SetError(m_chbEnableWakeup, String.Format(Resources.ErrMsgWakeUpFromSleep));
                    }
                    else
                    {
                        m_chbEnableWakeup.Enabled = false;
                        m_errorProvider.SetError(m_chbEnableWakeup, String.Empty);
                    }
                }
                else
                {
                    m_chbEnableWakeup.Enabled = true;
                    m_errorProvider.SetError(m_chbEnableWakeup, String.Empty);
                }
            }
        }

        private void UpdateByteModeCheckBoxState()
        {
            // Update Byte mode checkbox state
            m_chbByteMode.Enabled = (m_params.IsScbIPV2 && m_params.EZI2C_StretchClock) || m_params.EZI2C_EnableByteMode;
            string errMsg = String.Empty;
            if (m_chbByteMode.Enabled && m_params.EZI2C_EnableByteMode)
            {
                if (m_params.IsScbIPV0 || m_params.IsScbIPV1)
                {
                    errMsg = Resources.ByteModeError;
                }
                else if (m_params.EZI2C_StretchClock == false)
                {
                    errMsg = Resources.ByteModeVsClockStreching;
                }
            }
            m_errorProvider.SetError(m_chbByteMode, errMsg);
        }

        private void HideClockFromTerminal()
        {
            m_chbClockFromTerminal.Visible = false;
            m_backPanel.Top = m_chbClockFromTerminal.Top;
        }

        private void UpdateLabelAddressInfoVisibility()
        {
            bool showLblSlaveAddressInfo =
                m_params.EzI2CNumberOfAddresses.Value == CyEEZI2CNumberOfAddressesType.TWO_ADDRESSES &&
                m_params.EZI2C_EnableWakeupFromSleep;

            m_lblSlaveAddressInfo.Visible = showLblSlaveAddressInfo;
            m_lblSlaveAddressInfoIcon.Visible = showLblSlaveAddressInfo;

            m_backPanel.Height = showLblSlaveAddressInfo
                ? (m_lblSlaveAddressInfo.Top + m_lblSlaveAddressInfo.Height)
                : (m_chbEnableWakeup.Top + m_chbEnableWakeup.Height);
        }

        #endregion

        #region Actual data rate
        private void UpdateClock()
        {
            string dataRateStr = m_params.EZI2C_ClockFromTerminal ?
                Resources.ClockDisplayUnknown : Resources.ClockDisplayUnknownPressApply;

            m_cbDataRate.Enabled = !m_params.EZI2C_ClockFromTerminal;
            m_lblDataRate.Enabled = !m_params.EZI2C_ClockFromTerminal;

            ClearNotifications(m_lblActualDataRate);

            if (m_params.SCBMode == CyESCBMode.EZI2C)
            {
                double actualDataRate = m_params.GetActualDataRate(CyESCBMode.EZI2C);

                if (actualDataRate >= 0 && (m_params.EZI2C_ClockFromTerminal ||
                    (m_params.InternalClockNeedUpdate == false && m_params.SCBMode == CyESCBMode.EZI2C)))
                {
                    if (actualDataRate > 0)
                        dataRateStr = Math.Round(actualDataRate).ToString();

                    if (m_params.EZI2C_ClockFromTerminal)
                    {
                        double clkFreq = CyParameters.GetExternalClock(m_params.TermQuery);
                        if (CyParameters.IsFrequencyKnown(clkFreq) &&
                            clkFreq < CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS - CyParamRanges.EPS)
                        {
                            dataRateStr = Resources.ClockDisplayError;
                            m_errorProvider.SetError(m_lblActualDataRate, String.Format(
                                Resources.EZI2cExternalClockLowError, CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS_MHZ));
                        }
                    }
                }
            }
            // Update Actual Data Rate label
            m_lblActualDataRate.Text = string.Format(Resources.ActualDataRateDisplayFormat, dataRateStr);

            // Advanced tab has controls that depend on data rate and actual data rate, 
            // so they need to be re-validated
            m_params.Ezi2cAdvancedTab.UpdateDependentControls();
        }
        #endregion
    }
}
