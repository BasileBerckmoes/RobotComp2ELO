/*******************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

namespace SCB_P4_v4_0
{
    public partial class CySPIBasicTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get { return "SPI Basic"; }
        }

        public override string TabDisplayName
        {
            get { return Resources.SPIBasicTabDisplayName; }
        }
        #endregion

        #region Auxiliary properties
        public bool SimultionesTXRXMode
        {
            get
            {
                //When National Semicomductor Sub Mode is selected, the TX data bits and RX data bits 
                //values can be differ. In the rest sub modes they must change simultionesly. 
                //So, if press increase or decrease buttons for TX data bits, the RX data bits value must be changed 
                //the same and vise versa. If value is inputed manualy, the same value must be copied in other field.

                return m_params.SpiSubMode.Value != CyESPISubModeType.NS;
            }
        }
        public ushort HertzMultiplier
        {
            get { return ((m_cbBitRateUnits.SelectedIndex == 0) ? (ushort)1 : CyParameters.POW6); }
        }
        #endregion

        #region Constructor(s)
        public CySPIBasicTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            m_params.SpiBasicTab = this;

            InitializeComponent();

            // Add comboboxes' ranges
            m_cbMode.Items.AddRange(m_params.SpiMode.EnumDescriptionsList);
            m_cbSubMode.Items.AddRange(m_params.SpiSubMode.EnumDescriptionsList);
            m_cbSCLKMode.Items.AddRange(m_params.SpiSCLKMode.EnumDescriptionsList);
            m_cbBitOrder.Items.AddRange(m_params.SpiBitsOrder.EnumDescriptionsList);
            m_cbSS0Polarity.Items.AddRange(m_params.SpiSs0Polarity.EnumDescriptionsList);
            m_cbSS1Polarity.Items.AddRange(m_params.SpiSs1Polarity.EnumDescriptionsList);
            m_cbSS2Polarity.Items.AddRange(m_params.SpiSs2Polarity.EnumDescriptionsList);
            m_cbSS3Polarity.Items.AddRange(m_params.SpiSs3Polarity.EnumDescriptionsList);
            m_cbSSNumber.Items.Clear();
            for (uint i = CyParameters.SPI_MIN_SS_NUMBER; i <= CyParameters.SPI_MAX_SS_NUMBER; i++)
            {
                m_cbSSNumber.Items.Add(i.ToString());
            }

            #region Set event handlers
            m_numOversamplingFactor.TextChanged += m_num_TextChanged;
            m_numOversamplingFactor.Maximum = UInt32.MaxValue;

            m_numTXDataBits.TextChanged += m_num_TextChanged;
            m_numTXDataBits.Maximum = UInt32.MaxValue;

            m_numRXDataBits.TextChanged += m_num_TextChanged;
            m_numRXDataBits.Maximum = UInt32.MaxValue;

            m_chbClockFromTerminal.CheckedChanged += m_chb_CheckedChanged;
            m_chbEnableLateMISOSample.CheckedChanged += m_chb_CheckedChanged;
            m_chbEnableMedianFilter.CheckedChanged += m_chb_CheckedChanged;
            m_chbEnableWakeup.CheckedChanged += m_chb_CheckedChanged;

            m_cbMode.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSubMode.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSCLKMode.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbBitOrder.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbBitRateUnits.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSSNumber.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSS0Polarity.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSS1Polarity.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSS2Polarity.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbSS3Polarity.SelectedIndexChanged += m_cb_SelectedIndexChanged;

            m_cbBitRate.TextChanged += m_cb_TextChanged;
            m_params.ScbModeChanged += m_params_ScbModeChanged;
            m_params.DesignUpdates += m_params_DesignUpdates;

            m_params.SpiPinsStateChanged += delegate
            {
                UpdateDrawing();
                m_num_Validating(m_numOversamplingFactor, null); // Validate Oversampling factor
            };

            #endregion
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            if (m_params == null) return;

            m_chbEnableMedianFilter.Checked = m_params.SPI_EnableMedianFilter;
            m_chbEnableSclkFreeRunning.Checked = m_params.SPI_EnableSclkFreeRunning;
            m_chbEnableLateMISOSample.Checked = m_params.SPI_EnableLateMISOSample;
            m_chbEnableWakeup.Checked = m_params.SPI_EnableWakeupFromSleepMode;

            SetBitrateValue((double)m_params.SPI_BitsRateInKHz, true);

            //Clock from terminal
            m_chbClockFromTerminal.Checked = m_params.SPI_ClockFromTerminal;

            m_numOversamplingFactor.Text = CyParameters.GetTextFromNullableValue<byte?>(m_params.SPI_OvsFactor);
            UpdateOversamplingState();

            switch (m_params.SPI_TransferSeparation)
            {
                case CyESPITransferSeparationType.SEPARATED:
                    m_rbTransferSeparated.Checked = true;
                    break;
                case CyESPITransferSeparationType.CONTINUOUS:
                    m_rbTransferContinuous.Checked = true;
                    break;
                default:
                    break;
            }

            m_cbMode.SelectedItem = m_params.SpiMode.Description;
            m_cbSubMode.SelectedItem = m_params.SpiSubMode.Description;
            m_cbSCLKMode.SelectedItem = m_params.SpiSCLKMode.Description;
            m_cbBitOrder.SelectedItem = m_params.SpiBitsOrder.Description;
            m_cbSSNumber.SelectedItem = m_params.SPI_NumberOfSSLines.ToString();
            m_cbSS0Polarity.SelectedItem = m_params.SpiSs0Polarity.Description;
            m_cbSS1Polarity.SelectedItem = m_params.SpiSs1Polarity.Description;
            m_cbSS2Polarity.SelectedItem = m_params.SpiSs2Polarity.Description;
            m_cbSS3Polarity.SelectedItem = m_params.SpiSs3Polarity.Description;

            m_numTXDataBits.Text = CyParameters.GetTextFromNullableValue<byte?>(m_params.SPI_NumberOfTXDataBits);
            m_numRXDataBits.Text = CyParameters.GetTextFromNullableValue<byte?>(m_params.SPI_NumberOfRXDataBits);
        }

        public void UpdateCheckBoxesStates()
        {
            // Update wakeup enable
            if ((m_params.SpiMode.Value == CyESPIModeType.SPI_SLAVE) &&
                (m_params.SpiSubMode.Value == CyESPISubModeType.MOTOROLA) &&
                (m_params.SPI_InterruptMode == CyEInterruptModeType.INTERNAL))
            {
                if (m_params.IsScbIPV0)
                {
                    if (m_params.SpiSCLKMode.Value == CyESPISCLKModeType.MODE_00)
                    {
                        m_chbEnableWakeup.Enabled = true;
                    }
                    else
                    {
                        m_chbEnableWakeup.Enabled = false;
                        m_chbEnableWakeup.Checked = false;
                    }
                }
                else
                {
                    m_chbEnableWakeup.Enabled = true;
                }
            }
            else
            {
                m_chbEnableWakeup.Enabled = false;
                m_chbEnableWakeup.Checked = false;
            }

            // Update SCLK free running checkbox state
            if (!m_params.IsScbIPV2)
            {
                if (m_chbEnableSclkFreeRunning.Checked)
                {
                    m_chbEnableSclkFreeRunning.Enabled = true;
                    m_errorProvider.SetError(m_chbEnableSclkFreeRunning, Resources.SpiSclkFreeRunning);
                }
                else
                {
                    m_chbEnableSclkFreeRunning.Enabled = false;
                    m_errorProvider.SetError(m_chbEnableSclkFreeRunning, String.Empty);
                }
            }
            else //PSoC 4200-BL
            {
                m_chbEnableSclkFreeRunning.Enabled = m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER;
            }
        }

        private void UpdatePinConfig(Control control, int comboPrevIndex)
        {
            if (m_params.GlobalEditMode) // do not run the method when in expression view
            {
                if (m_params.SPI_RemoveMiso && m_params.SPI_RemoveMosi &&
                    m_params.SPI_RemoveSclk && m_cbSSNumber.SelectedIndex == 0)
                {
                    MessageBox.Show(Resources.SpiRemoveAllPinsNote, Resources.OperationNotAllowedTitle,
                         MessageBoxButtons.OK, MessageBoxIcon.Information, MessageBoxDefaultButton.Button1);

                    if (control is ComboBox)
                    {
                        if (comboPrevIndex >= CyParameters.SPI_MIN_SS_NUMBER &&
                            comboPrevIndex <= CyParameters.SPI_MAX_SS_NUMBER)
                            (control as ComboBox).SelectedIndex = comboPrevIndex;
                        else
                            Debug.Fail("Number of SS is out of range.");
                    }
                    else
                    {
                        Debug.Fail("The control is neither CheckBox nor ComboBox.");
                    }
                }
            }
        }

        public void SetBitrateValue(double bitrate, bool detectUnits)
        {
            //When changed the value in Bit Rate drop-down list or value inputed by hand must be 
            //immediately converted from kbps to Mbps and vise versa.

            if (detectUnits)
                m_cbBitRateUnits.SelectedIndex = bitrate < CyParameters.POW6 ? 0 : 1;

            bitrate = bitrate / HertzMultiplier;

            object[] list = new object[CyParameters.SPI_DATA_RATE_LIST.Length];
            for (int i = 0; i < list.Length; i++)
            {
                list[i] = (double)CyParameters.SPI_DATA_RATE_LIST[i] / HertzMultiplier;
            }

            m_cbBitRate.Items.Clear();
            m_cbBitRate.Items.AddRange(list);

            m_cbBitRate.Text = bitrate.ToString();
        }

        public bool ValidateTxRxDataBits()
        {
            bool res = ValidateDataBits(m_numRXDataBits);
            res &= ValidateDataBits(m_numTXDataBits);
            return res;
        }

        private bool ValidateDataBits(NumericUpDown num)
        {
            bool error = false;
            bool valueCompatibleByteMode = true;
            string message = String.Empty;

            uint min = CyParameters.SPI_MIN_DATA_BITS;
            uint max = m_params.SPI_EnableByteMode ? CyParameters.SPI_MAX_DATA_BITS_BYTEMODE :
                CyParameters.SPI_MAX_DATA_BITS;

            UInt32 val;
            bool parsed = UInt32.TryParse(num.Text, out val);
            if (parsed == false || val < min || val > max)
            {
                message = string.Format(Resources.ErrorDataBitsLimit, min, max);
                if (val > max && m_params.SPI_EnableByteMode)
                {
                    message = Resources.ByteModeDataBitsError;
                    valueCompatibleByteMode = false;
                }

                error = true;
            }

            m_errorProvider.SetError(num, error ? string.Format(message) : string.Empty);
            return valueCompatibleByteMode;
        }
        #endregion

        #region Event handlers
        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.SPI)
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

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == m_chbEnableMedianFilter)
            {
                m_params.SPI_EnableMedianFilter = m_chbEnableMedianFilter.Checked;
                m_num_Validating(m_numOversamplingFactor, null);
                UpdateClock();
            }
            else if (sender == m_chbEnableSclkFreeRunning)
            {
                m_params.SPI_EnableSclkFreeRunning = m_chbEnableSclkFreeRunning.Checked;
                UpdateDrawing();
            }
            else if (sender == m_chbEnableLateMISOSample)
            {
                m_params.SPI_EnableLateMISOSample = m_chbEnableLateMISOSample.Checked;
                m_num_Validating(m_numOversamplingFactor, null);
                UpdateDrawing();
            }
            else if (sender == m_chbEnableWakeup)
            {
                m_params.SPI_EnableWakeupFromSleepMode = m_chbEnableWakeup.Checked;
            }
            else if (sender == m_chbClockFromTerminal)
            {
                m_params.SPI_ClockFromTerminal = m_chbClockFromTerminal.Checked;
                UpdateOversamplingState();
                m_num_Validating(m_numOversamplingFactor, null);
                UpdateClock();
            }
          
            UpdateCheckBoxesStates();
        }

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (sender == m_cbMode)
            {
                CyESPIModeType prevSpiMode = m_params.SpiMode.Value;

                m_params.SpiMode.Description = m_cbMode.Text;

                bool isMaster = m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER;

                m_gbTransferSeparation.Enabled = isMaster;
                if (isMaster == false)
                {
                    // Set number of slave select lines to 1 (min is 0, so 1 is a second item)
                    m_cbSSNumber.SelectedIndex = 1;
                }

                if (!isMaster)
                {
                    m_params.SPI_EnableLateMISOSample = false;
                    m_chbEnableLateMISOSample.Checked = false;
                    m_chbEnableSclkFreeRunning.Checked = false;
                }
                m_chbEnableLateMISOSample.Enabled = isMaster;

                UpdateSSPolarityComboBoxesState();
                UpdateCheckBoxesStates();
                UpdateOversamplingState();
                m_num_Validating(m_numOversamplingFactor, null);
                UpdateClock((prevSpiMode == CyESPIModeType.SPI_SLAVE && isMaster) ||
                            (prevSpiMode != CyESPIModeType.SPI_SLAVE && isMaster == false));

                if (m_params.SpiAdvancedTab != null)
                {
                    m_params.SpiAdvancedTab.UpdateInterruptsVisibility();
                    m_params.SpiAdvancedTab.UpdateInterruptSources();
                }
                UpdateDrawing();

                m_params.OnSpiModeChanged(sender, e);
            }
            else if (sender == m_cbSubMode)
            {
                m_params.SpiSubMode.Description = m_cbSubMode.Text;

                //Control should be not editable. It's value can be selected from drop-down list only when 
                //Sub Mode is "Motorola".

                //For  "TI (Start coincides)" and "TI (Start precedes)" must be automatically selected 
                //to "Mode 2 (CPHA = 1, CPOL = 0)" and cannot be changed.

                //For  "National Semiconductor)" must be automatically selected to 
                //"Mode 0 (CPHA = 0, CPOL = 0)" and cannot be changed.

                m_cbSCLKMode.Enabled = m_params.SpiSubMode.Value == CyESPISubModeType.MOTOROLA;
                switch (m_params.SpiSubMode.Value)
                {
                    case CyESPISubModeType.TI_COINCIDES:
                    case CyESPISubModeType.TI_PRECEDES:
                        m_params.SpiSCLKMode.Value = CyESPISCLKModeType.MODE_10;
                        m_cbSCLKMode.SelectedItem = m_params.SpiSCLKMode.Description;
                        break;
                    case CyESPISubModeType.NS:
                        m_params.SpiSCLKMode.Value = CyESPISCLKModeType.MODE_00;
                        m_cbSCLKMode.SelectedItem = m_params.SpiSCLKMode.Description;
                        break;
                    default:
                        break;
                }

                UpdateCheckBoxesStates();

                if (SimultionesTXRXMode)
                    m_numRXDataBits.Text = m_numTXDataBits.Text;

                UpdateDrawing();
            }
            else if (sender == m_cbSCLKMode)
            {
                m_params.SpiSCLKMode.Description = m_cbSCLKMode.Text;
                UpdateDrawing();
                UpdateCheckBoxesStates();
            }
            else if (sender == m_cbBitRateUnits)
            {
                SetBitrateValue((double)m_params.SPI_BitsRateInKHz, false);
            }
            else if (sender == m_cbBitOrder)
            {
                m_params.SpiBitsOrder.Description = m_cbBitOrder.Text;
                UpdateDrawing();
            }
            else if (sender == m_cbSSNumber)
            {
                UpdatePinConfig(sender as Control, m_params.SPI_NumberOfSSLines);
                m_params.SPI_NumberOfSSLines = (byte)(m_cbSSNumber.SelectedIndex);
                UpdateSSPolarityComboBoxesState();
                UpdateDrawing();
            }
            else if (sender == m_cbSS0Polarity)
            {
                m_params.SpiSs0Polarity.Description = m_cbSS0Polarity.Text;
                UpdateSSPolarityComboBoxesState();
                UpdateDrawing();
            }
            else if (sender == m_cbSS1Polarity)
            {
                m_params.SpiSs1Polarity.Description = m_cbSS1Polarity.Text;
                UpdateSSPolarityComboBoxesState();
            }
            else if (sender == m_cbSS2Polarity)
            {
                m_params.SpiSs2Polarity.Description = m_cbSS2Polarity.Text;
                UpdateSSPolarityComboBoxesState();
            }
            else if (sender == m_cbSS3Polarity)
            {
                m_params.SpiSs3Polarity.Description = m_cbSS3Polarity.Text;
                UpdateSSPolarityComboBoxesState();
            }
        }

        private void UpdateOversamplingState()
        {
            m_numOversamplingFactor.Enabled =
                ((m_params.SpiMode.Value == CyESPIModeType.SPI_SLAVE && m_params.SPI_ClockFromTerminal) == false);
            m_lblOversample.Enabled = m_numOversamplingFactor.Enabled;
        }

        private void UpdateSSPolarityComboBoxesState()
        {
            m_cbSSNumber.Enabled = (m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER);

            bool ss0Enabled = m_params.SPI_NumberOfSSLines > CyParameters.SPI_MIN_SS_NUMBER;
            bool ss1Enabled = m_params.SPI_NumberOfSSLines > CyParameters.SPI_MIN_SS_NUMBER + 1;
            bool ss2Enabled = m_params.SPI_NumberOfSSLines > CyParameters.SPI_MIN_SS_NUMBER + 2;
            bool ss3Enabled = m_params.SPI_NumberOfSSLines > CyParameters.SPI_MIN_SS_NUMBER + 3;

            if (m_params.IsScbIPV2)
            {
                m_cbSS0Polarity.Enabled = ss0Enabled;
                m_cbSS1Polarity.Enabled = ss1Enabled;
                m_cbSS2Polarity.Enabled = ss2Enabled;
                m_cbSS3Polarity.Enabled = ss3Enabled;
                m_lblSS0Polarity.Enabled = m_cbSS0Polarity.Enabled;
                m_lblSS1Polarity.Enabled = m_cbSS1Polarity.Enabled;
                m_lblSS2Polarity.Enabled = m_cbSS2Polarity.Enabled;
                m_lblSS3Polarity.Enabled = m_cbSS3Polarity.Enabled;
            }
            else
            {
                if (m_params.SpiSs0Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss0Enabled)
                {
                    m_cbSS0Polarity.Enabled = true;
                    m_lblSS0Polarity.Enabled = true;
                    m_errorProvider.SetError(m_cbSS0Polarity, Resources.SpiSSPolarityError);
                }
                else
                {
                    m_cbSS0Polarity.Enabled = false;
                    m_lblSS0Polarity.Enabled = false;
                    m_errorProvider.SetError(m_cbSS0Polarity, String.Empty);
                }

                if (m_params.SpiSs1Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss1Enabled)
                {
                    m_cbSS1Polarity.Enabled = true;
                    m_lblSS1Polarity.Enabled = true;
                    m_errorProvider.SetError(m_cbSS1Polarity, Resources.SpiSSPolarityError);
                }
                else
                {
                    m_cbSS1Polarity.Enabled = false;
                    m_lblSS1Polarity.Enabled = false;
                    m_errorProvider.SetError(m_cbSS1Polarity, String.Empty);
                }

                if (m_params.SpiSs2Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss2Enabled)
                {
                    m_cbSS2Polarity.Enabled = true;
                    m_lblSS2Polarity.Enabled = true;
                    m_errorProvider.SetError(m_cbSS2Polarity, Resources.SpiSSPolarityError);
                }
                else
                {
                    m_cbSS2Polarity.Enabled = false;
                    m_lblSS2Polarity.Enabled = false;
                    m_errorProvider.SetError(m_cbSS2Polarity, String.Empty);
                }

                if (m_params.SpiSs3Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss3Enabled)
                {
                    m_cbSS3Polarity.Enabled = true;
                    m_lblSS3Polarity.Enabled = true;
                    m_errorProvider.SetError(m_cbSS3Polarity, Resources.SpiSSPolarityError);
                }
                else
                {
                    m_cbSS3Polarity.Enabled = false;
                    m_lblSS3Polarity.Enabled = false;
                    m_errorProvider.SetError(m_cbSS3Polarity, String.Empty);
                }
            }
        }

        void m_rbTransfer_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbTransferContinuous.Checked)
                m_params.SPI_TransferSeparation = CyESPITransferSeparationType.CONTINUOUS;
            else
                m_params.SPI_TransferSeparation = CyESPITransferSeparationType.SEPARATED;
        }

        #region Text Changed
        void m_num_TextChanged(object sender, EventArgs e)
        {
            CancelEventArgs ce = new CancelEventArgs();
            m_num_Validating(sender, ce);
            NumericUpDown num = sender as NumericUpDown;

            byte? value = null;

            byte val;
            if (byte.TryParse(num.Text, out val))
                value = val;

            if (sender == m_numOversamplingFactor)
            {
                if (m_params.SPI_OvsFactor != value)
                {
                    m_params.SPI_OvsFactor = value;
                    m_params.InternalClockNeedUpdate = true;
                    UpdateClock();
                }
            }

            if (sender == m_numRXDataBits)
            {
                m_params.SPI_NumberOfRXDataBits = value;

                if (SimultionesTXRXMode)
                    m_numTXDataBits.Text = m_numRXDataBits.Text;

                if (string.IsNullOrEmpty(m_errorProvider.GetError(num)))
                {
                    UpdateDrawing();
                }

                if (m_params.SpiAdvancedTab != null)
                    m_params.SpiAdvancedTab.UpdateByteModeCheckBoxState();
            }

            if (sender == m_numTXDataBits)
            {
                m_params.SPI_NumberOfTXDataBits = value;

                if (SimultionesTXRXMode)
                    m_numRXDataBits.Text = m_numTXDataBits.Text;

                if (string.IsNullOrEmpty(m_errorProvider.GetError(num)))
                {
                    UpdateDrawing();
                }

                if (m_params.SpiAdvancedTab != null)
                    m_params.SpiAdvancedTab.UpdateByteModeCheckBoxState();
            }
        }

        void m_num_Validating(object sender, CancelEventArgs e)
        {
            if (sender == m_numOversamplingFactor)
            {
                bool error = false;
                string message = String.Empty;

                uint min = m_params.SpiGetMinOversampling(ref message);
                uint max = CyParameters.SPI_MAX_OVERSAMPLING_FACTOR;

                UInt32 val;
                bool parsed = uint.TryParse(m_numOversamplingFactor.Text, out val);
                if (parsed == false || val < min || val > max)
                    error = true;

                m_errorProvider.SetError(m_numOversamplingFactor, (error && m_numOversamplingFactor.Enabled) ?
                    string.Format(message) : string.Empty);
            }
            else if (sender == m_numRXDataBits || sender == m_numTXDataBits)
            {
                ValidateDataBits((NumericUpDown)sender);
            }
        }

        void m_cb_TextChanged(object sender, EventArgs e)
        {
            if (sender == m_cbBitRate)
            {
                double value;
                bool parsed = double.TryParse(m_cbBitRate.Text, out value);

                if (parsed)
                {
                    value *= HertzMultiplier;
                    if (m_params.SPI_BitsRateInKHz != (UInt32)value)
                    {
                        m_params.SPI_BitsRateInKHz = (UInt32)value;
                        m_params.InternalClockNeedUpdate = true;
                    }
                }

                if (parsed && value <= CyParameters.SPI_MAX_DATA_RATE && value >= CyParameters.SPI_MIN_DATA_RATE)
                {
                    m_errorProvider.SetError(m_cbBitRate, string.Empty);
                    UpdateClock();
                }
                else
                {
                    m_errorProvider.SetError(m_cbBitRate, string.Format(Resources.DataRateValueError,
                        CyParameters.SPI_MIN_DATA_RATE, CyParameters.SPI_MAX_DATA_RATE));
                }
            }
        }
        #endregion
        #endregion

        #region Form Drawing
        // Image constants
        public const int PB_SPIMTEXT_WIDTH = 40;
        public const int PB_EXTENTS_BORDER = 5;
        public const int PB_POLYGON_WIDTH = 4;
        public const int NUM_WAVEFORMS = 5;

        public void UpdateDrawing()
        {
            if ((m_pictDrawing.Width == 0) || (m_pictDrawing.Height == 0))
                return;

            const int SS_LINE_INDEX = 0;
            const int SCLK_LINE_INDEX = 1;
            const int MOSI_LINE_INDEX = 2;
            const int MISO_LINE_INDEX = 3;
            const int SAMPLE_LINE_INDEX = 4;

            bool normal_mode = ((m_params.SpiSCLKMode.Value == CyESPISCLKModeType.MODE_00) ||
                  (m_params.SpiSCLKMode.Value == CyESPISCLKModeType.MODE_01));
            bool starthigh = (m_params.SpiSCLKMode.Value == CyESPISCLKModeType.MODE_01) ||
                (m_params.SpiSCLKMode.Value == CyESPISCLKModeType.MODE_11);
            bool shiftDir = m_params.SpiBitsOrder.Value != CyESPIBitOrderType.MSB_FIRST;

            bool nsMode = m_params.SpiSubMode.Value == CyESPISubModeType.NS;
            int numberOfBits = nsMode ? 7 : (int)m_params.SPI_NumberOfTXDataBits;
            int numberOfTXBits = (int)m_params.SPI_NumberOfTXDataBits;
            int numberOfRXBits = (int)m_params.SPI_NumberOfRXDataBits;

            int misoStart = nsMode ? 6 : 0;
            int mosiEnd = nsMode ? 6 : numberOfBits * 2;

            int misoSt = 2 + Convert.ToInt32(normal_mode == false) +
               Convert.ToInt32(m_params.SPI_EnableLateMISOSample);

            bool hideMiso = m_params.SPI_RemoveMiso;
            bool hideMosi = m_params.SPI_RemoveMosi;
            bool hideSclk = m_params.SPI_RemoveSclk;
            bool hideSample = (hideMiso && m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER) ||
                              (hideMosi && m_params.SpiMode.Value == CyESPIModeType.SPI_SLAVE);
            bool hideSS = m_params.SPI_NumberOfSSLines == 0;

            Image waveform = new Bitmap(m_pictDrawing.Width, m_pictDrawing.Height);

            using (Graphics wfg = Graphics.FromImage(waveform))
            using (SolidBrush blkbrush = new SolidBrush(Color.Black))
            using (Pen extentspen = new Pen(blkbrush))
            {
                wfg.Clear(Color.White);

                // Display No Signal label when no signals were selected
                if (hideMiso && hideMosi && hideSclk && hideSample && hideSS)
                {
                    using (Font labelFnt = new Font(m_lblMode.Font.Name, 16, FontStyle.Regular, GraphicsUnit.Pixel))
                    using (Font descFnt = new Font(m_lblMode.Font.Name, 12, FontStyle.Regular, GraphicsUnit.Pixel))
                    {
                        SizeF labelSize = wfg.MeasureString(Resources.NoSignalLabel, labelFnt);
                        SizeF descSize = wfg.MeasureString(Resources.NoSignalDescription, descFnt);
                        wfg.DrawString(Resources.NoSignalLabel, labelFnt, Brushes.Black,
                            m_pictDrawing.Width / 2 - labelSize.Width / 2,
                            m_pictDrawing.Height / 2 - labelSize.Height / 2);
                        wfg.DrawString(Resources.NoSignalDescription, descFnt, Brushes.Black,
                            m_pictDrawing.Width / 2 - descSize.Width / 2,
                            m_pictDrawing.Height / 2 - descSize.Height / 2 + labelSize.Height);
                    }
                }
                else
                {
                    float extentsleft = PB_EXTENTS_BORDER + PB_SPIMTEXT_WIDTH;
                    float extentsright = m_pictDrawing.Width - PB_EXTENTS_BORDER;
                    float padding = (extentsright - extentsleft) / 70;
                    float startleft = extentsleft + padding;
                    float endright = extentsright - padding;

                    // Setup the right, left and center indicators
                    extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                    // Draw the Left Extents Line
                    wfg.DrawLine(extentspen, extentsleft, PB_EXTENTS_BORDER,
                        extentsleft, m_pictDrawing.Height - PB_EXTENTS_BORDER);

                    // Setup and draw all of the waveforms
                    int numwaveforms = NUM_WAVEFORMS;
                    string[] wfnames = new string[NUM_WAVEFORMS];

                    wfnames[SS_LINE_INDEX] = "SS";
                    wfnames[SCLK_LINE_INDEX] = "SCLK";
                    wfnames[MOSI_LINE_INDEX] = "MOSI";
                    wfnames[MISO_LINE_INDEX] = "MISO";
                    wfnames[SAMPLE_LINE_INDEX] = "Sample";

                    Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);

                    // Each waveform's height is dependent upon the drawing size minus a top and bottom border 
                    // and the top period waveform which is the size of two polygon widths, and an bottom 
                    // ticker tape of 2 polygon widths
                    float wfheight = (m_pictDrawing.Height - (2 * PB_EXTENTS_BORDER) - (4 * PB_POLYGON_WIDTH)) /
                        numwaveforms;
                    // Fill in All Waveform Names
                    for (int i = 0; i < numwaveforms; i++)
                    {
                        if ((hideMiso && i == MISO_LINE_INDEX) ||
                            (hideMosi && i == MOSI_LINE_INDEX) ||
                            (hideSclk && i == SCLK_LINE_INDEX) ||
                            (hideSample && i == SAMPLE_LINE_INDEX) ||
                            (hideSS && i == SS_LINE_INDEX))
                            continue;

                        PointF pt = new PointF(extentsleft - wfg.MeasureString(wfnames[i], perfont).Width -
                            PB_EXTENTS_BORDER, PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) +
                            (wfheight / 2) - (wfg.MeasureString(wfnames[i], perfont).Height / 2));
                        wfg.DrawString(wfnames[i], perfont, blkbrush, pt);
                    }

                    // Draw Waveforms
                    float lastXPoint = extentsright; // point that indicates the end of timeline
                    int numsegments = 2 + (Convert.ToInt16(numberOfBits) * 2) + 3;
                    for (int i = 0; i < numwaveforms; i++)
                    {
                        float highY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) + (wfheight / 8);
                        float lowY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * (i + 1));
                        float middle = (lowY + highY) / 2;
                        float segwidth = (extentsright - extentsleft) / numsegments;

                        List<float> segs = new List<float>();
                        for (int x = 0; x < numsegments; x++)
                        {
                            segs.Add(extentsleft + (x * segwidth));
                        }
                        using (SolidBrush wfbrush = new SolidBrush(Color.Blue))
                        using (Pen pen = new Pen(wfbrush))
                        {
                            string val = null;
                            int j = 0;

                            switch (wfnames[i])
                            {
                                case "SS":
                                    if (hideSS)
                                        break;

                                    float lineHighY = highY;
                                    float lineLowY = lowY;
                                    if (m_params.SpiSs0Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH)
                                    {
                                        // Inverse diagram
                                        lineHighY = lowY;
                                        lineLowY = highY;
                                    }

                                    switch (m_params.SpiSubMode.Value)
                                    {
                                        case CyESPISubModeType.MOTOROLA:
                                            wfg.DrawLine(pen, segs[0], lineHighY, segs[2], lineHighY);
                                            wfg.DrawLine(pen, segs[2], lineHighY, segs[2], lineLowY);
                                            wfg.DrawLine(pen, segs[2], lineLowY, segs[numsegments - 2], lineLowY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineLowY, segs[numsegments - 2], lineHighY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineHighY, segs[numsegments - 1], lineHighY);
                                            break;
                                        case CyESPISubModeType.TI_COINCIDES:
                                            wfg.DrawLine(pen, segs[0], lineLowY, segs[3], lineLowY);
                                            wfg.DrawLine(pen, segs[3], lineHighY, segs[3], lineLowY);

                                            wfg.DrawLine(pen, segs[3], lineHighY, segs[5], lineHighY);
                                            wfg.DrawLine(pen, segs[5], lineHighY, segs[5], lineLowY);
                                            wfg.DrawLine(pen, segs[5], lineLowY, segs[numsegments - 1], lineLowY);
                                            break;
                                        case CyESPISubModeType.TI_PRECEDES:
                                            wfg.DrawLine(pen, segs[0], lineLowY, segs[1], lineLowY);
                                            wfg.DrawLine(pen, segs[1], lineHighY, segs[1], lineLowY);

                                            wfg.DrawLine(pen, segs[1], lineHighY, segs[3], lineHighY);
                                            wfg.DrawLine(pen, segs[3], lineHighY, segs[3], lineLowY);
                                            wfg.DrawLine(pen, segs[3], lineLowY, segs[numsegments - 1], lineLowY);
                                            break;
                                        case CyESPISubModeType.NS:
                                            wfg.DrawLine(pen, segs[0], lineHighY, segs[1], lineHighY);
                                            wfg.DrawLine(pen, segs[1], lineHighY, segs[1], lineLowY);
                                            wfg.DrawLine(pen, segs[1], lineLowY, segs[numsegments - 2], lineLowY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineLowY, segs[numsegments - 2], lineHighY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineHighY, segs[numsegments - 1], lineHighY);
                                            break;
                                        default:
                                            break;
                                    }
                                    break;

                                case "MOSI":
                                    if (hideMosi)
                                        break;

                                    bool no_shift = normal_mode;
                                    int mosiSt = no_shift ? 2 : 3;

                                    // Draw Bus to First Transition Point
                                    wfg.DrawLine(pen, segs[0], highY, segs[mosiSt] - 2, highY);
                                    wfg.DrawLine(pen, segs[0], lowY, segs[mosiSt] - 2, lowY);
                                    // Draw Transition
                                    wfg.DrawLine(pen, segs[mosiSt] - 2, highY, segs[mosiSt] + 2, lowY);
                                    wfg.DrawLine(pen, segs[mosiSt] - 2, lowY, segs[mosiSt] + 2, highY);

                                    for (j = 0; j < (mosiEnd); )
                                    {
                                        bool nsEndNode = (j + 2 >= mosiEnd) && nsMode;
                                        // Draw Bus to Transition Point
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, highY, segs[mosiSt + (j + 2)] - 2, highY);
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, lowY, segs[mosiSt + (j + 2)] - 2, lowY);

                                        if (nsEndNode == false)
                                        {
                                            // Draw Transition line
                                            wfg.DrawLine(pen, segs[mosiSt + (j + 2)] - 2, highY,
                                                segs[mosiSt + (j + 2)] + 2, lowY);
                                            wfg.DrawLine(pen, segs[mosiSt + (j + 2)] - 2, lowY, segs[mosiSt + (j + 2)] + 2,
                                                highY);
                                        }

                                        #region label text
                                        val = String.Format("D{0}", shiftDir ? j / 2 : numberOfBits - (j / 2) - 1);
                                        if (nsMode)
                                        {
                                            int numBits = (m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER) ? 
                                                numberOfTXBits : numberOfRXBits;
                                            if (j == 0)
                                                val = String.Format("D{0}", shiftDir ? 0 : numBits - 1);
                                            else if (nsEndNode)
                                                val = String.Format("D{0}", shiftDir ? numBits - 1 : 0);
                                            else
                                                val = "...";
                                        }
                                        #endregion

                                        SizeF strsize = wfg.MeasureString(val, perfont);
                                        float centerx = segs[mosiSt + j] + segwidth;
                                        using (SolidBrush strBrush = new SolidBrush(Color.Black))
                                        {
                                            wfg.DrawString(val, perfont, strBrush,
                                                new RectangleF(centerx - (strsize.Width / 2f), highY + ((wfheight) / 2f) -
                                                    (strsize.Height / 2f), strsize.Width, strsize.Height));
                                        }

                                        j += 2;
                                    }

                                    if (nsMode)
                                    {
                                        // Draw Transition line
                                        wfg.DrawLine(pen, segs[mosiSt + j] - 2, highY, segs[mosiSt + j] + 1, middle);
                                        wfg.DrawLine(pen, segs[mosiSt + j] - 2, lowY, segs[mosiSt + j] + 1, middle);

                                        //Draw end line
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 1, middle, segs[segs.Count - 1], middle);
                                    }
                                    else
                                    {
                                        // Draw Bus to Transition Point
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, lowY, segs[mosiSt + (j + 1 +
                                            Convert.ToInt32(no_shift))], lowY);
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, highY, segs[mosiSt + (j + 1 +
                                            Convert.ToInt32(no_shift))], highY);
                                    }
                                    break;

                                case "MISO":
                                    if (hideMiso)
                                        break;

                                    if (nsMode)
                                    {
                                        // Draw Bus to First Transition Point
                                        wfg.DrawLine(pen, segs[0], middle, segs[misoSt + (misoStart)], middle);
                                        // Draw Transition for idle
                                        wfg.DrawLine(pen, segs[misoSt + (misoStart)], middle, segs[misoSt + misoStart] + 2,
                                            lowY);
                                    }
                                    else
                                    {
                                        // Draw Bus to First Transition Point
                                        wfg.DrawLine(pen, segs[0], highY, segs[misoSt] - 2, highY);
                                        wfg.DrawLine(pen, segs[0], lowY, segs[misoSt] - 2, lowY);
                                        // Draw Transition
                                        wfg.DrawLine(pen, segs[misoSt] - 2, highY, segs[misoSt] + 2, lowY);
                                        wfg.DrawLine(pen, segs[misoSt] - 2, lowY, segs[misoSt] + 2, highY);
                                    }
                                    for (j = misoStart; j < (numberOfBits * 2); )
                                    {
                                        bool idle = (j == misoStart) && nsMode;

                                        // Draw Bus to Transition Point. For idle node only bottom line
                                        if (idle == false)
                                            wfg.DrawLine(pen, segs[misoSt + j] + 2, highY, segs[misoSt + (j + 2)] - 2,
                                                highY);
                                        wfg.DrawLine(pen, segs[misoSt + j] + 2, lowY, segs[misoSt + (j + 2)] - 2, lowY);

                                        // Draw Transition. For idle node oly bottom line
                                        if (idle)
                                            wfg.DrawLine(pen, segs[misoSt + (j + 2)], middle, segs[misoSt + (j + 2)] + 2,
                                                lowY);
                                        else
                                            wfg.DrawLine(pen, segs[misoSt + (j + 2)] - 2, highY, segs[misoSt + (j + 2)] + 2,
                                                lowY);
                                        wfg.DrawLine(pen, segs[misoSt + (j + 2)] - 2, lowY, segs[misoSt + (j + 2)] + 2,
                                            highY);

                                        #region label text
                                        val = String.Format("D{0}", shiftDir ? j / 2 : numberOfBits - (j / 2) - 1);
                                        if (nsMode)
                                        {
                                            int numBits = (m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER) ?
                                               numberOfRXBits : numberOfTXBits;
                                            if (idle)
                                                val = "idle";
                                            else if (j == misoStart + 2)
                                                val = String.Format("D{0}", shiftDir ? 0 : numBits - 1);
                                            else if (j + 2 >= (numberOfBits * 2))
                                                val = String.Format("D{0}", shiftDir ? numBits - 1 : 0);
                                            else
                                                val = "...";
                                        }
                                        #endregion

                                        SizeF strsize = wfg.MeasureString(val, perfont);
                                        float centerx = segs[misoSt + j] + segwidth;
                                        using (SolidBrush strBrush = new SolidBrush(Color.Black))
                                        {
                                            wfg.DrawString(val, perfont, strBrush,
                                                            new RectangleF(centerx - (strsize.Width / 2f), highY +
                                                                ((wfheight) / 2f) - (strsize.Height / 2f), strsize.Width,
                                                                strsize.Height));
                                        }
                                        j += 2;
                                    }

                                    // Draw Bus to Transition Point
                                    wfg.DrawLine(pen, segs[misoSt + j] + 2, lowY, segs[segs.Count - 1], lowY);
                                    wfg.DrawLine(pen, segs[misoSt + j] + 2, highY, segs[segs.Count - 1], highY);
                                    break;

                                case "SCLK":
                                    if (hideSclk)
                                        break;

                                    int goHighSeg;
                                    int addSegments;

                                    if (m_params.SPI_EnableSclkFreeRunning)
                                    {
                                        goHighSeg = 1;
                                        addSegments = 2;
                                    }
                                    else
                                    {
                                        goHighSeg = m_params.SpiSubMode.Value == CyESPISubModeType.TI_PRECEDES ? 1 : 3;
                                        addSegments = m_params.SpiSubMode.Value == CyESPISubModeType.TI_PRECEDES ? 1 : 0;
                                    }

                                    wfg.DrawLine(pen, segs[0], starthigh ? highY : lowY, segs[goHighSeg], starthigh ?
                                        highY : lowY);
                                    wfg.DrawLine(pen, segs[goHighSeg], starthigh ? highY : lowY, segs[goHighSeg],
                                        starthigh ? highY : lowY);

                                    for (j = 0; j < (numberOfBits * 2) + addSegments; )
                                    {
                                        wfg.DrawLine(pen, segs[goHighSeg + j], starthigh ? highY : lowY,
                                            segs[goHighSeg + j], starthigh ? lowY : highY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? lowY : highY,
                                            segs[goHighSeg + j], starthigh ? lowY : highY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j], starthigh ? lowY : highY,
                                            segs[goHighSeg + j], starthigh ? highY : lowY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? highY : lowY,
                                            segs[goHighSeg + j], starthigh ? highY : lowY);
                                    }

                                    if (m_params.SPI_EnableSclkFreeRunning)
                                    {
                                        wfg.DrawLine(pen, segs[goHighSeg + j], starthigh ? lowY : highY,
                                                segs[goHighSeg + j], starthigh ? highY : lowY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? lowY : highY,
                                            segs[goHighSeg + j], starthigh ? lowY : highY);
                                    }
                                    else
                                    {
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? highY : lowY,
                                        segs[goHighSeg + j], starthigh ? highY : lowY);
                                    }
                                    break;

                                case "Sample":
                                    if (hideSample)
                                        break;

                                    wfg.DrawLine(pen, segs[0], lowY, segs[misoSt + 1] - 2, lowY); // go to first edge
                                    for (j = 0; j < (numberOfBits * 2); )
                                    {
                                        wfg.DrawLine(pen, segs[misoSt + 1 + j] - 2, lowY, segs[misoSt + 1 + j] - 2, highY);
                                        wfg.DrawLine(pen, segs[misoSt + 1 + j] - 2, highY, segs[misoSt + 1 + j] + 2, highY);
                                        wfg.DrawLine(pen, segs[misoSt + 1 + j] + 2, highY, segs[misoSt + 1 + j] + 2, lowY);

                                        if (j + 2 < numberOfBits * 2)
                                            wfg.DrawLine(pen, segs[misoSt + 1 + j] + 2, lowY,
                                                segs[misoSt + 1 + (j + 2)] - 2, lowY);
                                        else
                                            wfg.DrawLine(pen, segs[misoSt + 1 + j] + 2, lowY, segs[segs.Count - 1], lowY);

                                        j += 2;
                                    }
                                    break;

                                case "Interrupt":
                                    break;

                                default:
                                    Debug.Fail("Unhandled waveform name.");
                                    break;
                            }
                        }
                        lastXPoint = segs[segs.Count - 1];
                    }
                    // Draw the Right Extents Line
                    wfg.DrawLine(extentspen, lastXPoint, PB_EXTENTS_BORDER,
                        lastXPoint, m_pictDrawing.Height - PB_EXTENTS_BORDER);
                }
            }
            m_pictDrawing.Image = waveform;
        }
        #endregion

        #region Overrides
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            UpdateDrawing();
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            UpdateDrawing();
        }
        #endregion

        #region Actual data rate
        private void UpdateClock()
        {
            UpdateClock(false);
        }

        private void UpdateClock(bool displayAsUnknown)
        {
            string dataRateStr = Resources.ClockDisplayUnknown;

            m_cbBitRate.Enabled = !m_params.SPI_ClockFromTerminal;
            m_cbBitRateUnits.Enabled = !m_params.SPI_ClockFromTerminal;
            m_lblDataRate.Enabled = !m_params.SPI_ClockFromTerminal;

            ClearNotifications(m_lblActualBitRate);

            if (m_params.SCBMode == CyESCBMode.SPI && displayAsUnknown == false)
            {
                double actualDataRate = m_params.GetActualDataRate(CyESCBMode.SPI);
                if (actualDataRate > 0 && (m_params.SPI_ClockFromTerminal ||
                    (m_params.InternalClockNeedUpdate == false && m_params.SCBMode == CyESCBMode.SPI)))
                {
                    dataRateStr = Math.Round(actualDataRate).ToString();

                    if ((m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER) &&
                        (m_params.SPI_ClockFromTerminal == false) &&
                        (actualDataRate > m_params.SPI_BitsRateInKHz.Value + CyParamRanges.EPS))
                    {
                        m_warningProvider.SetError(m_lblActualBitRate, Resources.ActualDataRateMaster);
                    }
                    else if (m_params.SpiMode.Value == CyESPIModeType.SPI_SLAVE)
                    {
                        m_noteProvider.SetError(m_lblActualBitRate, Resources.SPISeeDatasheet);
                    }
                }
            }

            // Update Actual Data Rate label
            m_lblActualBitRate.Text = string.Format(Resources.ActualDataRateDisplayFormat, dataRateStr);
            m_lblPressApply.Visible = (dataRateStr == Resources.ClockDisplayUnknown) &&
                                      (m_params.SPI_ClockFromTerminal == false);
        }
        #endregion
    }
}
