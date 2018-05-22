/*******************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace SCB_P4_v4_0
{
    public partial class CyI2CBasicTab : CyTabControlWrapper
    {
        #region Class private members
        private byte m_previousOvsFactor;
        private byte m_previousOvsFactorLow;
        private byte m_previousOvsFactorHigh;
        private bool m_numericLocked = false; // Used for locking numericUpDown control to prevent infinite loop
        private double m_sclk;
        private double m_actualDataRate;
        #endregion

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "I2C Basic";
            }
        }

        public override string TabDisplayName
        {
            get { return Resources.I2CBasicTabDisplayName; }
        }
        #endregion

        #region Constructor(s)
        public CyI2CBasicTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            InitializeComponent();

            // Assigning ModeType possible values to ComboBox
            m_cbMode.Items.AddRange(m_params.I2cMode.EnumDescriptionsList);

            #region Assigning event handlers
            m_chbAcceptAddress.CheckedChanged += m_chb_CheckedChanged;
            m_chbAcceptGeneralCallAddress.CheckedChanged += m_chb_CheckedChanged;
            m_chbClockFromTerminal.CheckedChanged += m_chb_CheckedChanged;
            m_chbByteMode.CheckedChanged += m_chb_CheckedChanged;
            m_chbEnableWakeup.CheckedChanged += m_chb_CheckedChanged;
            m_chbManualOversampleControl.CheckedChanged += m_chb_CheckedChanged;

            m_numOversamplingFactor.TextChanged += numOversamplingFactor_TextChanged;
            m_numOversamplingFactorHigh.Validating += numOversamplingFactorLowHigh_Validating;
            m_numOversamplingFactorHigh.ValueChanged += numOversamplingFactorLow_ValueChanged;
            m_numOversamplingFactorLow.Validating += numOversamplingFactorLowHigh_Validating;
            m_numOversamplingFactorLow.ValueChanged += numOversamplingFactorLow_ValueChanged;

            m_cbMode.SelectedIndexChanged += m_cbMode_SelectedIndexChanged;
            m_cbDataRate.TextChanged += m_cbDataRate_TextChanged;

            m_txtSlaveAddress.TextChanged += tbSlaveAddress_TextChanged;
            m_txtSlaveAddressMask.TextChanged += tbSlaveAddressMask_TextChanged;

            m_binaryGridSlaveAddress.BitChanged += new CyBinaryGrid.BitChangedEventHandler(
                binaryGridSlaveAddress_BitChanged);
            m_binaryGridSlaveAddressMask.BitChanged += new CyBinaryGrid.BitChangedEventHandler(
                binaryGridSlaveAddressMask_BitChanged);
            m_params.ScbModeChanged += m_params_ScbModeChanged;
            m_params.DesignUpdates += m_params_DesignUpdates;

            m_binaryGridSlaveAddressMask.SetErrorListItem(7, CyBinaryGrid.OneSign);
            #endregion
        }
        #endregion

        #region Assigning parameters values to controls
        public override void UpdateUI()
        {
            if (m_params.GlobalEditMode == false)
            {
                // This code runs on customizer load or when something was changed in Expression view
                if ((m_params.I2C_OvsFactorLow + m_params.I2C_OvsFactorHigh) != m_params.I2C_OvsFactor)
                {
                    m_numOversamplingFactorLow.Minimum = 0;
                    m_numOversamplingFactorLow.Maximum = decimal.MaxValue;
                    m_numOversamplingFactorHigh.Minimum = 0;
                    m_numOversamplingFactorHigh.Maximum = decimal.MaxValue;
                }
                numOversamplingFactorLowHigh_Validating(m_numOversamplingFactorLow, new CancelEventArgs());
            }

            // I2CMode
            m_cbMode.SelectedItem = m_params.I2cMode.Description;

            // I2CDataRate
            m_cbDataRate.Text = m_params.I2C_DataRate.ToString();

            //Clock from terminal
            m_chbClockFromTerminal.Checked = m_params.I2C_ClockFromTerminal;

            // I2COvsFactor
            m_numOversamplingFactor.Text = m_params.I2C_OvsFactor.ToString();

            // OvsFactorLow
            m_numOversamplingFactorLow.Text = m_params.I2C_OvsFactorLow.ToString();

            // OvsFactorHigh
            m_numOversamplingFactorHigh.Text = m_params.I2C_OvsFactorHigh.ToString();

            // I2cByteMode
            m_chbByteMode.Checked = m_params.I2C_EnableByteMode;

            // SlaveAddressMask
            if (m_params.I2C_IsSlaveAddressMaskHex)
                m_txtSlaveAddressMask.Text = CyConvert.IntToHex(m_params.I2C_SlaveAddressMask);
            else
                m_txtSlaveAddressMask.Text = m_params.I2C_SlaveAddressMask.ToString();

            // SlaveAddress
            if (m_params.I2C_IsSlaveAddressHex)
                m_txtSlaveAddress.Text = CyConvert.IntToHex(m_params.I2C_SlaveAddress);
            else
                m_txtSlaveAddress.Text = m_params.I2C_SlaveAddress.ToString();

            // AccepAddress
            m_chbAcceptAddress.Checked = m_params.I2C_AcceptAddress;

            // AcceptGeneralCall
            m_chbAcceptGeneralCallAddress.Checked = m_params.I2C_AcceptGeneralCallAddress;

            // EnableWakeup
            m_chbEnableWakeup.Checked = m_params.I2C_EnableWakeup;

            // ManualOversampleControl
            m_chbManualOversampleControl.Checked = m_params.I2C_ManualOversampleControl;

            // Save current values to know if the value of numeric controls was changed next time
            m_previousOvsFactor = m_params.I2C_OvsFactor;
            m_previousOvsFactorLow = (byte)m_numOversamplingFactorLow.Value;
            m_previousOvsFactorHigh = (byte)m_numOversamplingFactorHigh.Value;
            numOversamplingFactorLowHigh_Validating(m_numOversamplingFactorLow, new CancelEventArgs());

            UpdateClock();
            UpdateByteModeCheckBoxState();
            UpdateOversamplingState();
            UpdateManualOversampleControlState();
            UpdateValidators();
        }

        private void UpdateValidators()
        {
            m_binaryGridSlaveAddress.SetErrorListItem(6, (m_params.I2C_EnableWakeup && m_params.IsScbIPV0) ?
                CyBinaryGrid.OneSign : string.Empty);
            m_binaryGridSlaveAddressMask.SetErrorListItem(6, (m_params.I2C_EnableWakeup && m_params.IsScbIPV0) ?
                CyBinaryGrid.ZeroSign : string.Empty);
        }
        #endregion

        #region Actual data rate
        private void UpdateClock()
        {
            UpdateClock(false);
        }

        private void UpdateClock(bool displayAsUnknown)
        {
            string dataRateStr = m_params.I2C_ClockFromTerminal ?
                Resources.ClockDisplayUnknown : Resources.ClockDisplayUnknownPressApply;

            m_cbDataRate.Enabled = !m_params.I2C_ClockFromTerminal;
            m_lblDataRate.Enabled = !m_params.I2C_ClockFromTerminal;

            ClearNotifications(m_lblActualDataRate);

            if (m_params.SCBMode == CyESCBMode.I2C && displayAsUnknown == false)
            {
                m_sclk = m_params.I2C_ClockFromTerminal
                    ? CyParameters.GetExternalClock(m_params.TermQuery)
                    : CyParameters.GetInternalClock(m_params.TermQuery);

                uint customOvsFactor = (m_params.I2C_ManualOversampleControl == false)
                    ? (uint)m_numOversamplingFactor.Value : 0;
                m_actualDataRate = Math.Round(m_params.GetActualDataRate(CyESCBMode.I2C, customOvsFactor));

                if (m_actualDataRate >= 0 && (m_params.I2C_ClockFromTerminal ||
                    (m_params.InternalClockNeedUpdate == false && m_params.SCBMode == CyESCBMode.I2C)))
                {
                    if (m_actualDataRate > 0)
                        dataRateStr = m_actualDataRate.ToString();

                    string errorMessage;
                    double dataRateMax = CyParamRanges.GetI2cDataRateMaximum(m_params.IsScbIPV1, out errorMessage);

                    if (m_params.I2cMode.Value == CyEI2CModeType.I2C_MULTI_MASTER_SLAVE && m_params.I2C_EnableWakeup
                         && m_actualDataRate > CyParamRanges.I2C_DATA_RATE_400 + CyParamRanges.EPS)
                    {
                        m_errorProvider.SetError(m_lblActualDataRate, Resources.ActualDataRateMultiMasterError);
                    }
                    else if ((m_params.I2cMode.Value != CyEI2CModeType.I2C_SLAVE) &&
                             (m_params.I2C_ClockFromTerminal == false) &&
                             (m_actualDataRate > m_params.I2C_DataRate + CyParamRanges.EPS))
                    {
                        m_warningProvider.SetError(m_lblActualDataRate, Resources.ActualDataRateMaster);
                    }
                    else if (m_params.I2C_ClockFromTerminal &&
                            (m_params.I2cMode.Value != CyEI2CModeType.I2C_SLAVE) &&
                             m_actualDataRate > dataRateMax)
                    {
                        m_errorProvider.SetError(m_lblActualDataRate, errorMessage);
                    }
                    else if (m_params.I2cMode.Value == CyEI2CModeType.I2C_SLAVE && m_params.I2C_ClockFromTerminal &&
                        (m_sclk < CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS - CyParamRanges.EPS))
                    {
                        dataRateStr = Resources.ClockDisplayError;
                        m_errorProvider.SetError(m_lblActualDataRate, String.Format(
                            Resources.I2cExternalClockLowError, CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS_MHZ));
                    }
                    else if (m_params.I2cMode.Value != CyEI2CModeType.I2C_SLAVE)
                    {
                        double dataRate = m_params.I2C_ClockFromTerminal ? m_actualDataRate : m_params.I2C_DataRate;

                        // Check ranges decribed in the "Clock from terminal" section of the 
                        // component BROS (see Table 2. I2C Master modes clock frequency ranges)
                        if ((m_sclk > 0) &&

                            // clock is out of allowed fSCB range in Standard-mode
                            ((dataRate >= 0 && dataRate <= CyParamRanges.I2C_DATA_RATE_100 &&
                             (m_sclk < CyParamRanges.I2C_MASTER_FSCB_MIN_100KBPS - CyParamRanges.EPS ||
                              m_sclk > CyParamRanges.I2C_MASTER_FSCB_MAX_100KBPS - CyParamRanges.EPS)) ||

                            // clock is out of allowed fSCB range in Fast-mode
                             (dataRate > CyParamRanges.I2C_DATA_RATE_100 &&
                              dataRate <= CyParamRanges.I2C_DATA_RATE_400 &&
                             (m_sclk < CyParamRanges.I2C_MASTER_FSCB_MIN_400KBPS - CyParamRanges.EPS ||
                              m_sclk > CyParamRanges.I2C_MASTER_FSCB_MAX_400KBPS - CyParamRanges.EPS)) ||

                            // clock is out of allowed fSCB range in Fast-mode Plus
                             (dataRate > CyParamRanges.I2C_DATA_RATE_400 &&
                              dataRate <= CyParamRanges.I2C_DATA_RATE_1000 &&
                             (m_sclk < CyParamRanges.I2C_MASTER_FSCB_MIN_1000KBPS - CyParamRanges.EPS ||
                              m_sclk > CyParamRanges.I2C_MASTER_FSCB_MAX_1000KBPS - CyParamRanges.EPS))))
                        {
                            m_noteProvider.SetError(m_lblActualDataRate, Resources.I2CConsultDatasheet);
                        }
                    }
                }
            }

            // Update Actual Data Rate label
            m_lblActualDataRate.Text = string.Format(Resources.ActualDataRateDisplayFormat, dataRateStr);

            // Advanced tab has controls that depend on data rate and actual data rate, 
            // so they need to be re-validated
            m_params.I2cAdvancedTab.UpdateDependentControls();
        }

        #endregion

        #region Event Handlers
        #region Slave Address configuration
        private void binaryGridSlaveAddress_BitChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode) // avoid this on customizer load
            {
                CyBinaryGrid currentBinaryGrid = (CyBinaryGrid)sender;

                if (currentBinaryGrid.Locked == false)
                {
                    currentBinaryGrid.Locked = true; // lock binary box from updating after textbox update

                    if (m_txtSlaveAddress.Text.StartsWith(CyConvert.HEX_PREFIX))
                    {
                        // Hexadecimal value handling
                        m_txtSlaveAddress.Text = CyConvert.Bin7ToHex(currentBinaryGrid.Bits);
                    }
                    else
                    {
                        // Decimal value handling
                        m_txtSlaveAddress.Text = CyConvert.Bin7ToInt(currentBinaryGrid.Bits).ToString();
                    }
                    currentBinaryGrid.Locked = false; // release lock
                }
            }
        }

        private void tbSlaveAddress_TextChanged(object sender, EventArgs e)
        {
            TextBox currentTextBox = (TextBox)sender;

            #region Communication between textbox and binary grid
            if (m_binaryGridSlaveAddress.Locked == false)
            {
                m_binaryGridSlaveAddress.Locked = true; // lock textbox from updating after binary box update

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Hexadecimal value handling
                    int value = CyConvert.HexToInt(currentTextBox.Text);
                    if (value >= CyParamRanges.I2C_SLAVE_ADDRESS_MIN && value <= CyParamRanges.I2C_SLAVE_ADDRESS_MAX)
                    {
                        m_binaryGridSlaveAddress.Bits = CyConvert.HexToBin7(currentTextBox.Text);
                    }
                }
                else
                {
                    // Decimal value handling
                    int value = 0;
                    if (int.TryParse(currentTextBox.Text, out value))
                    {
                        if (value < CyParamRanges.I2C_SLAVE_ADDRESS_MIN || value > CyParamRanges.I2C_SLAVE_ADDRESS_MAX)
                            value = 0;
                    }
                    m_binaryGridSlaveAddress.Bits = CyConvert.IntToBin7(value);
                }

                string[] tmpBits = new string[m_binaryGridSlaveAddress.Bits.Length];

                // Restore X signs if zero
                for (int i = 0; i < tmpBits.Length; i++)
                {
                    tmpBits[i] = (m_binaryGridSlaveAddressMask.Bits[i] == CyBinaryGrid.ZeroSign) ? CyBinaryGrid.XSign :
                        m_binaryGridSlaveAddress.Bits[i];
                }

                // Change view only here
                m_binaryGridSlaveAddress.UpdateGridViewOnly(tmpBits);

                m_binaryGridSlaveAddress.Locked = false; // release lock
            }
            #endregion

            #region Set control value to appropriate parameter
            try
            {
                byte textboxValue = 0;
                string min, max;
                bool isHex = false;

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Value was input as hexadecimal
                    textboxValue = (byte)CyConvert.HexToInt(currentTextBox.Text);
                    min = CyConvert.IntToHex(CyParamRanges.I2C_SLAVE_ADDRESS_MIN);
                    max = CyConvert.IntToHex(CyParamRanges.I2C_SLAVE_ADDRESS_MAX);
                    isHex = true;
                }
                else
                {
                    // Value was input as decimal
                    textboxValue = byte.Parse(currentTextBox.Text);
                    min = CyParamRanges.I2C_SLAVE_ADDRESS_MIN.ToString();
                    max = CyParamRanges.I2C_SLAVE_ADDRESS_MAX.ToString();
                    isHex = false;
                }

                if (textboxValue >= CyParamRanges.I2C_SLAVE_ADDRESS_MIN && textboxValue <=
                    CyParamRanges.I2C_SLAVE_ADDRESS_MAX)
                {
                    string errorMessage = GetSlaveAddressError(textboxValue, m_params);
                    if (string.IsNullOrEmpty(errorMessage) == false) throw new Exception(errorMessage);

                    m_params.I2C_SlaveAddress = textboxValue;
                    m_params.I2C_IsSlaveAddressHex = isHex;
                }
                else
                    throw new Exception(string.Format(Resources.I2CSlaveAddressError, min, max));

                m_errorProvider.SetError(currentTextBox, string.Empty);
            }
            catch (Exception ex)
            {
                m_errorProvider.SetError(currentTextBox, ex.Message);
            }
            #endregion
        }

        public static string GetSlaveAddressError(byte slaveAddressValue, CyParameters parameters)
        {
            if (!parameters.IsScbIPV0)
                return string.Empty;

            string res = string.Empty;
            if ((parameters.I2C_EnableWakeup) && ((slaveAddressValue & 1) != 0))
            {
                res = Resources.SlaveAddressOddError;
            }

            return res;
        }

        public static string GetSlaveAddressMaskError(byte slaveAddressMaskValue, bool isHex, CyParameters parameters)
        {
            string errorMsg = string.Empty;
            byte min = CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MIN;
            byte max = CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MAX;

            if ((slaveAddressMaskValue < min) || (slaveAddressMaskValue > max))
            {
                string minStr = isHex ? CyConvert.IntToHex(min) : min.ToString();
                string maxStr = isHex ? CyConvert.IntToHex(max) : max.ToString();
                errorMsg = string.Format(Resources.I2CSlaveAddressMaskError, minStr, maxStr);
            }
            else if ((slaveAddressMaskValue & 1) != 0) // even value only accepted
            {
                errorMsg = Resources.SlaveAddressMaskOddError;
            }
            else if ((parameters.I2C_EnableWakeup) && ((slaveAddressMaskValue & 2) == 0) &&
                      parameters.IsScbIPV0)
            {
                errorMsg = Resources.SlaveAddressMaskBitOneError;
            }

            return errorMsg;
        }

        private void UpdateOversamplingState()
        {
            bool hasMaster = m_params.I2cMode.Value != CyEI2CModeType.I2C_SLAVE;

            m_numOversamplingFactor.Enabled = (hasMaster && m_params.I2C_ManualOversampleControl);
            m_lblOversamplingFactor.Enabled = m_numOversamplingFactor.Enabled;

            m_numOversamplingFactorHigh.Enabled = m_numOversamplingFactor.Enabled;
            m_numOversamplingFactorLow.Enabled = m_numOversamplingFactor.Enabled;

            m_lblOversamplingFactorLow.Enabled = m_numOversamplingFactor.Enabled;
            m_lblOversamplingFactorHigh.Enabled = m_numOversamplingFactor.Enabled;
        }

        private void UpdateManualOversampleControlState()
        {
            m_chbManualOversampleControl.Enabled =
                (m_params.I2cMode.Value != CyEI2CModeType.I2C_SLAVE && m_params.I2C_ClockFromTerminal == false);
            if (m_params.I2C_ClockFromTerminal)
                m_chbManualOversampleControl.Checked = true;
            SetAutoOversampling();
        }
        #endregion

        #region Slave Address Mask configuration
        private void binaryGridSlaveAddressMask_BitChanged(object sender, EventArgs e)
        {
            CyBinaryGrid currentBinaryGrid = (CyBinaryGrid)sender;

            if (currentBinaryGrid.Locked == false)
            {
                currentBinaryGrid.Locked = true; // lock binary box from updating after textbox update

                if (m_txtSlaveAddressMask.Text.StartsWith(CyConvert.HEX_PREFIX))
                {
                    // Hexadecimal value handling
                    m_txtSlaveAddressMask.Text = CyConvert.BinToHex(currentBinaryGrid.Bits);
                }
                else
                {
                    // Decimal value handling
                    m_txtSlaveAddressMask.Text = CyConvert.BinToInt(currentBinaryGrid.Bits).ToString();
                }
                currentBinaryGrid.Locked = false; // release lock
            }
            UpdateAddressAccordingToAddressMask();
        }

        private void UpdateAddressAccordingToAddressMask()
        {
            // Show X as a bit of slave address when appropriate mask bit equal to 0
            // Create value in temporrary array
            string[] tmpBits = new string[m_binaryGridSlaveAddress.Bits.Length];

            for (int i = 0; i < tmpBits.Length; i++)
            {
                tmpBits[i] = m_binaryGridSlaveAddress.Bits[i];
            }

            for (int i = 0; i < tmpBits.Length; i++)
            {
                tmpBits[i] = (m_binaryGridSlaveAddressMask.Bits[i] == CyBinaryGrid.ZeroSign) ? CyBinaryGrid.XSign :
                    (m_binaryGridSlaveAddress.Bits[i] != CyBinaryGrid.XSign ? m_binaryGridSlaveAddress.Bits[i] :
                    CyBinaryGrid.ZeroSign);
            }
            // In 7-bit value LSB is always X
            if (m_binaryGridSlaveAddress.NumberOfBits == 7)
                tmpBits[m_binaryGridSlaveAddress.NumberOfBits] = CyBinaryGrid.XSign;

            // Do not update slave address value according to slave address mask,
            // only view of control should be changed
            m_binaryGridSlaveAddress.UpdateGridViewOnly(tmpBits);
        }

        private void tbSlaveAddressMask_TextChanged(object sender, EventArgs e)
        {
            TextBox currentTextBox = (TextBox)sender;

            #region Communications between textbox and binary grid
            if (m_binaryGridSlaveAddressMask.Locked == false)
            {
                m_binaryGridSlaveAddressMask.Locked = true; // lock textbox from updating after binary box update

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Hexadecimal value handling
                    int value = CyConvert.HexToInt(currentTextBox.Text);
                    if (value >= CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MIN && value <=
                        CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MAX)
                    {
                        m_binaryGridSlaveAddressMask.Bits = CyConvert.HexToBin(currentTextBox.Text);
                    }
                }
                else
                {
                    // Decimal value handling
                    int value = 0;
                    if (int.TryParse(currentTextBox.Text, out value))
                    {
                        if (value < CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MIN ||
                            value > CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MAX)
                            value = 0;
                    }
                    m_binaryGridSlaveAddressMask.Bits = CyConvert.IntToBin(value);
                }
                m_binaryGridSlaveAddressMask.Locked = false; // release lock

                UpdateAddressAccordingToAddressMask();
            }
            #endregion

            #region Set control value to appropriate parameter
            try
            {
                byte textboxValue = 0;
                string min, max;
                bool isHex = false;

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Value was input as hexadecimal
                    textboxValue = (byte)CyConvert.HexToInt(currentTextBox.Text);
                    min = CyConvert.IntToHex(CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MIN);
                    max = CyConvert.IntToHex(CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MAX);
                    isHex = true;
                }
                else
                {
                    // Value was input as decimal
                    textboxValue = byte.Parse(currentTextBox.Text);
                    min = CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MIN.ToString();
                    max = CyParamRanges.I2C_SLAVE_ADDRESS_MASK_MAX.ToString();
                    isHex = false;
                }

                string errorMessage = GetSlaveAddressMaskError(textboxValue, isHex, m_params);
                if (string.IsNullOrEmpty(errorMessage) == false) throw new Exception(errorMessage);

                m_params.I2C_SlaveAddressMask = textboxValue;
                m_params.I2C_IsSlaveAddressMaskHex = isHex;

                m_errorProvider.SetError(currentTextBox, string.Empty);

            }
            catch (Exception ex)
            {
                m_errorProvider.SetError(currentTextBox, ex.Message);
            }
            #endregion
        }
        #endregion

        #region Other controls configuration
        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.I2C)
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
            SetAutoOversampling();
            UpdateClock();
        }

        private void CyI2CTab_Load(object sender, EventArgs e)
        {
            UpdateAddressAccordingToAddressMask();
            UpdateClock();
        }

        private void m_cbMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyEI2CModeType prevI2cMode = m_params.I2cMode.Value;

            if (m_params.GlobalEditMode)
            {
                m_params.I2cMode.Description = m_cbMode.Text;
            }

            bool hasMaster = m_params.I2cMode.Value != CyEI2CModeType.I2C_SLAVE;
            bool isSlave = m_params.I2cMode.Value == CyEI2CModeType.I2C_SLAVE ||
                m_params.I2cMode.Value == CyEI2CModeType.I2C_MULTI_MASTER_SLAVE;

            m_panelSlaveConf.Enabled = isSlave;

            UpdateOversamplingState();
            numOversamplingFactor_TextChanged(m_numOversamplingFactor, EventArgs.Empty);
            numOversamplingFactorLowHigh_Validating(m_numOversamplingFactorLow, new CancelEventArgs());
            numOversamplingFactorLowHigh_Validating(m_numOversamplingFactorHigh, new CancelEventArgs());

            if (isSlave == false)
            {
                m_chbAcceptAddress.Checked = false;
                m_chbEnableWakeup.Checked = false;
            }

            UpdateManualOversampleControlState();
            UpdateAcceptGeneralCallAddressState();

            UpdateClock((prevI2cMode == CyEI2CModeType.I2C_SLAVE && hasMaster) ||
                        (prevI2cMode != CyEI2CModeType.I2C_SLAVE && hasMaster == false));

            // Advanced tab has controls that depend on the I2C mode
            m_params.I2cAdvancedTab.UpdateDependentControls();
        }

        private void m_cbDataRate_TextChanged(object sender, EventArgs e)
        {
            double dataRateValue = 0;
            bool parsed = double.TryParse(m_cbDataRate.Text, out dataRateValue);

            if (m_params.GlobalEditMode && parsed && m_params.I2C_DataRate != (UInt16)dataRateValue)
            {
                m_params.I2C_DataRate = (UInt16)dataRateValue;
                m_params.InternalClockNeedUpdate = true;
            }

            // Check range
            string errorMessage;
            UInt16 dataRateMax = CyParamRanges.GetI2cDataRateMaximum(m_params.IsScbIPV1, out errorMessage);

            if (parsed && dataRateValue >= CyParamRanges.I2C_DATA_RATE_MIN && dataRateValue <= dataRateMax)
            {
                m_errorProvider.SetError(m_cbDataRate, string.Empty);
                UpdateClock();
            }
            else
            {
                m_errorProvider.SetError(m_cbDataRate, errorMessage);
            }

            // Advanced tab has controls that depend on data rate and actual data rate, 
            // so they need to be re-validated
            m_params.I2cAdvancedTab.UpdateDependentControls();
        }

        private void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == m_chbAcceptAddress)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.I2C_AcceptAddress = m_chbAcceptAddress.Checked;
                }
            }
            else if (sender == m_chbClockFromTerminal)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.I2C_ClockFromTerminal = m_chbClockFromTerminal.Checked;
                }
                UpdateClock();
                UpdateOversamplingState();
                UpdateManualOversampleControlState();
                numOversamplingFactor_TextChanged(m_numOversamplingFactor, EventArgs.Empty);
            }
            else if (sender == m_chbByteMode)
            {
                m_params.I2C_EnableByteMode = m_chbByteMode.Checked;
                UpdateByteModeCheckBoxState();
            }
            else if (sender == m_chbEnableWakeup)
            {
                m_params.I2C_EnableWakeup = m_chbEnableWakeup.Checked;

                UpdateValidators();

                numOversamplingFactor_TextChanged(m_numOversamplingFactor, new EventArgs());
                tbSlaveAddress_TextChanged(m_txtSlaveAddress, null);
                tbSlaveAddressMask_TextChanged(m_txtSlaveAddressMask, null);
            }
            else if (sender == m_chbManualOversampleControl)
            {
                m_params.I2C_ManualOversampleControl = m_chbManualOversampleControl.Checked;

                UpdateClock(true);
                UpdateOversamplingState();
            }
            else if (sender == m_chbAcceptGeneralCallAddress)
            {
                m_params.I2C_AcceptGeneralCallAddress = m_chbAcceptGeneralCallAddress.Checked;
            }
        }

        private void SetAutoOversampling()
        {
            if (m_params.I2C_ManualOversampleControl == false)
            {
                byte low;
                byte high;
                if (m_params.GetAutoOversamplingLowHigh(out low, out high))
                {
                    bool prevEditMode = m_params.GlobalEditMode;
                    m_params.GlobalEditMode = false;
                    m_numOversamplingFactor.Text = (low + high).ToString();
                    m_numOversamplingFactorLow.Text = low.ToString();
                    m_numOversamplingFactorHigh.Text = high.ToString();
                    m_params.GlobalEditMode = prevEditMode;
                }
            }
        }

        private void UpdateByteModeCheckBoxState()
        {
            // Update Byte mode checkbox state
            m_chbByteMode.Enabled = m_params.IsScbIPV2 || m_params.I2C_EnableByteMode;
            m_errorProvider.SetError(m_chbByteMode, m_params.IsScbIPV2
                ? String.Empty
                : m_params.I2C_EnableByteMode ? Resources.ByteModeError : String.Empty);
        }

        private void UpdateAcceptGeneralCallAddressState()
        {
            bool isSlave = m_params.I2cMode.Value != CyEI2CModeType.I2C_MASTER &&
                m_params.I2cMode.Value != CyEI2CModeType.I2C_MULTI_MASTER;
            if (m_params.I2C_AcceptGeneralCallAddress && isSlave == false)
                m_chbAcceptGeneralCallAddress.Checked = false;
        }

        private void numOversamplingFactor_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentTextBox = ((NumericUpDown)sender);
            byte ovsFactorValue = 0;
            byte.TryParse(currentTextBox.Text, out ovsFactorValue);

            if (m_params.GlobalEditMode)
            {
                if (ovsFactorValue < CyParamRanges.I2C_OVS_FACTOR_MIN ||
                    ovsFactorValue > CyParamRanges.I2C_OVS_FACTOR_MAX)
                {
                    if (m_numOversamplingFactor.Enabled)
                        m_errorProvider.SetError(currentTextBox, GetOvsFactorErrorMessage());
                    else
                        m_numOversamplingFactor.Value = CyParamRanges.I2C_OVS_FACTOR_DEF;
                }
                else
                {
                    if (m_params.I2C_OvsFactor != ovsFactorValue)
                    {
                        m_params.I2C_OvsFactor = ovsFactorValue;
                        m_params.InternalClockNeedUpdate = true;
                    }
                    UpdateClock();
                    m_errorProvider.SetError(currentTextBox, string.Empty);

                    if (ovsFactorValue != m_previousOvsFactor) // check if I2COvsFactor was changed
                    {
                        m_previousOvsFactor = ovsFactorValue;
                        // Oversampling Factor sets the value of Oversampling Low and High dividing by two equal parts.  
                        // In case of odd value the Oversampling Low is greater by 1.
                        m_numericLocked = true; // lock numeric update to avoid infinity loop
                        if ((ovsFactorValue % 2) == 0 && ovsFactorValue != CyParamRanges.I2C_OVS_FACTOR_MAX)
                        {
                            m_numOversamplingFactorLow.Value = ovsFactorValue / 2 + 1;
                            m_numOversamplingFactorHigh.Value = ovsFactorValue / 2 - 1;
                        }
                        else
                        {
                            m_numOversamplingFactorLow.Value = Math.Ceiling((decimal)ovsFactorValue / 2);
                            m_numOversamplingFactorHigh.Value = Math.Floor((decimal)ovsFactorValue / 2);
                        }
                        m_numericLocked = false; // release lock

                        // Set numeric controls values that were changed in consequence of I2COvsFactor change
                        m_params.I2C_OvsFactorLow = (byte)m_numOversamplingFactorLow.Value;
                        m_params.I2C_OvsFactorHigh = (byte)m_numOversamplingFactorHigh.Value;
                    }
                }
            }

            // Call this to update OvsFactorLow and OvsFactorHigh error providers
            numOversamplingFactorLowHigh_Validating(m_numOversamplingFactorLow, new CancelEventArgs());
        }

        private void numOversamplingFactorLow_ValueChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (m_numericLocked == false)
                {
                    m_numericLocked = true;

                    NumericUpDown master = (NumericUpDown)sender;
                    NumericUpDown slave = (master == m_numOversamplingFactorHigh) ? m_numOversamplingFactorLow :
                        m_numOversamplingFactorHigh;

                    if ((m_params.I2C_OvsFactorLow + m_params.I2C_OvsFactorHigh) == m_params.I2C_OvsFactor)
                    {
                        byte previousValue = (master == m_numOversamplingFactorHigh) ? m_previousOvsFactorHigh :
                            m_previousOvsFactorLow;

                        if (master.Value > previousValue)
                        {
                            if (slave.Value - 1 >= slave.Minimum)
                            {
                                slave.Value--;
                            }
                        }
                        if (master.Value < previousValue)
                        {
                            if (slave.Value + 1 <= slave.Maximum)
                            {
                                slave.Value++;
                            }
                        }
                    }
                    m_params.I2C_OvsFactorLow = (byte)m_numOversamplingFactorLow.Value;
                    m_params.I2C_OvsFactorHigh = (byte)m_numOversamplingFactorHigh.Value;
                    m_numericLocked = false;
                }

                // Save current values to know if the value of numeric controls was changed next time
                m_previousOvsFactorLow = (byte)m_numOversamplingFactorLow.Value;
                m_previousOvsFactorHigh = (byte)m_numOversamplingFactorHigh.Value;

                // Call this to update OvsFactorLow and OvsFactorHigh error providers
                numOversamplingFactorLowHigh_Validating(m_numOversamplingFactorLow, new CancelEventArgs());
            }
        }

        private void numOversamplingFactorLowHigh_Validating(object sender, CancelEventArgs e)
        {
            if (m_params.I2cMode.Value == CyEI2CModeType.I2C_SLAVE)
            {
                m_errorProvider.SetError(m_numOversamplingFactorLow, string.Empty);
                m_errorProvider.SetError(m_numOversamplingFactorHigh, string.Empty);
            }
            else
            {
                if (m_numOversamplingFactorLow.Value < CyParamRanges.GetI2COvsLowMinimum() ||
                    m_numOversamplingFactorLow.Value > CyParamRanges.GetI2COvsLowMaximum())
                {
                    m_errorProvider.SetError(m_numOversamplingFactorLow, GetOvsLowErrorMessage());
                }
                else
                    m_errorProvider.SetError(m_numOversamplingFactorLow, string.Empty);

                if (m_numOversamplingFactorHigh.Value < CyParamRanges.GetI2COvsHighMinimum() ||
                    m_numOversamplingFactorHigh.Value > CyParamRanges.GetI2COvsHighMaximum())
                {
                    m_errorProvider.SetError(m_numOversamplingFactorHigh, GetOvsHighErrorMessage());
                }
                else
                    m_errorProvider.SetError(m_numOversamplingFactorHigh, string.Empty);
            }

            // Check if value was changed from Expression view
            if ((m_params.I2C_OvsFactorLow + m_params.I2C_OvsFactorHigh) != m_params.I2C_OvsFactor)
            {
                m_errorProvider.SetError(m_numOversamplingFactorLow, Resources.OvsHighLowOutOfRangeError);
                m_errorProvider.SetError(m_numOversamplingFactorHigh, Resources.OvsHighLowOutOfRangeError);
            }
        }
        #endregion
        #endregion

        #region Overrides
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            m_lblSeparator.Left = m_binaryGridSlaveAddress.Left + m_binaryGridSlaveAddress.Width -
                m_binaryGridSlaveAddress.CellWidth - m_binaryGridSlaveAddress.DistanceBetweenCells / 2;
        }
        #endregion

        #region Building error messages
        private string GetOvsFactorErrorMessage()
        {
            return String.Format(Resources.OvsFactorError,
                                 CyParamRanges.I2C_OVS_FACTOR_MIN, CyParamRanges.I2C_OVS_FACTOR_MAX);
        }

        private string GetOvsLowErrorMessage()
        {
            byte min = CyParamRanges.GetI2COvsLowMinimum();

            return string.Format(Resources.OvsLowError, min, CyParamRanges.GetI2COvsLowMaximum());
        }

        private string GetOvsHighErrorMessage()
        {
            byte min = CyParamRanges.GetI2COvsHighMinimum();

            return string.Format(Resources.OvsHighError, min, CyParamRanges.GetI2COvsHighMaximum());
        }
        #endregion
    }
}
