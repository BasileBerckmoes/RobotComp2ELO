/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using I2S_PDL_v2_0.Utils;
using System.Windows.Forms;
namespace I2S_PDL_v2_0.Tabs
{
    internal partial class CyBasicTab : CyTabBase
    {
        #region Constructor(s)
        public CyBasicTab() : 
            base(null, Resources.BasicTabDisplayName, Resources.BasicTabDisplayName)
        {
            InitializeComponent();
        }

        public CyBasicTab(CyParameters parameters) : 
            base(parameters, Resources.BasicTabDisplayName, Resources.BasicTabDisplayName)
        {
            InitializeComponent();

            //
            // Initialize TX group comboboxes
            //
            m_cbTxChannels.DataSource = Enum.GetValues(typeof(CyChannels));
            m_cbTxChannelLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbTxWordLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbTxOverheadValue.DataSource = Enum.GetValues(typeof(CyOverheadValue));
            m_cbTxMode.DataSource = Enum.GetValues(typeof(CyMode));
            m_cbTxAlignment.DataSource = Enum.GetValues(typeof(CyAlignment));
            m_cbTxWsPulseWidth.DataSource = Enum.GetValues(typeof(CyWsPulseWidth));
            m_cbTxSdo.DataSource = Enum.GetValues(typeof(CySdoLatchingTime));
            m_cbTxInputClockPolarity.DataSource = Enum.GetValues(typeof(CySckPolarity));
            m_cbTxOutputClockPolarity.DataSource = Enum.GetValues(typeof(CySckPolarity));

            //
            // Initialize RX group comboboxes
            //
            m_cbRxChannels.DataSource = Enum.GetValues(typeof(CyChannels));
            m_cbRxChannelLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbRxWordLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbRxSignExtension.DataSource = Enum.GetValues(typeof(CySignExtension));
            m_cbRxMode.DataSource = Enum.GetValues(typeof(CyMode));
            m_cbRxAlignment.DataSource = Enum.GetValues(typeof(CyAlignment));
            m_cbRxWsPulseWidth.DataSource = Enum.GetValues(typeof(CyWsPulseWidth));
            m_cbRxSdi.DataSource = Enum.GetValues(typeof(CySdiLatchingTime));
            m_cbRxInputClockPolarity.DataSource = Enum.GetValues(typeof(CySckPolarity));
            m_cbRxOutputClockPolarity.DataSource = Enum.GetValues(typeof(CySckPolarity));

            //
            // Initialize numeric controls
            //
            CyUtils.SetNumericMinMax(m_numClockDivider, CyConstants.CLOCK_DIVIDER_MIN, 
                                                        CyConstants.CLOCK_DIVIDER_MAX);
            CyUtils.SetNumericMinMax(m_numTxFifoTriggerLevel, CyConstants.FIFO_TRIGGER_LEVEL_MIN,
                                                              CyConstants.FIFO_TRIGGER_LEVEL_MAX);
            CyUtils.SetNumericMinMax(m_numTxWatchdogValue, CyConstants.WATCHDOG_VALUE_MIN, 
                                                           CyConstants.WATCHDOG_VALUE_MAX);
            CyUtils.SetNumericMinMax(m_numRxFifoTriggerLevel, CyConstants.FIFO_TRIGGER_LEVEL_MIN, 
                                                              CyConstants.FIFO_TRIGGER_LEVEL_MAX);
            CyUtils.SetNumericMinMax(m_numRxWatchdogValue, CyConstants.WATCHDOG_VALUE_MIN, 
                                                           CyConstants.WATCHDOG_VALUE_MAX);

            SubscribeEvents();
        }
        #endregion

        #region Init / Update

        private void SubscribeEvents()
        {
            // Comboboxes event subscription
            // TX comboboxes
            m_cbTxChannels.Format += ComboBox_Format;
            m_cbTxChannelLength.Format += ComboBox_Format;
            m_cbTxWordLength.Format += ComboBox_Format;
            m_cbTxOverheadValue.Format += ComboBox_Format;
            m_cbTxMode.Format += ComboBox_Format;
            m_cbTxAlignment.Format += ComboBox_Format;
            m_cbTxWsPulseWidth.Format += ComboBox_Format;
            m_cbTxSdo.Format += ComboBox_Format;
            m_cbTxInputClockPolarity.Format += ComboBox_Format;
            m_cbTxOutputClockPolarity.Format += ComboBox_Format;
            m_cbTxChannels.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxChannelLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxWordLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxOverheadValue.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxMode.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxAlignment.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxWsPulseWidth.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxSdo.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxInputClockPolarity.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxOutputClockPolarity.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            // RX comboboxes
            m_cbRxChannels.Format += ComboBox_Format;
            m_cbRxChannelLength.Format += ComboBox_Format;
            m_cbRxWordLength.Format += ComboBox_Format;
            m_cbRxSignExtension.Format += ComboBox_Format;
            m_cbRxMode.Format += ComboBox_Format;
            m_cbRxAlignment.Format += ComboBox_Format;
            m_cbRxWsPulseWidth.Format += ComboBox_Format;
            m_cbRxSdi.Format += ComboBox_Format;
            m_cbRxInputClockPolarity.Format += ComboBox_Format;
            m_cbRxOutputClockPolarity.Format += ComboBox_Format;
            m_cbRxChannels.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxChannelLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxWordLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxSignExtension.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxMode.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxAlignment.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxWsPulseWidth.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxSdi.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxInputClockPolarity.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxOutputClockPolarity.SelectedIndexChanged += ComboBox_SelectedIndexChanged;

            // Checkboxes event subscription
            // Common checkboxes
            m_chbClockFromTerminal.CheckedChanged += CheckBox_CheckedChanged;
            // Tx checkboxes
            m_chbEnableTx.CheckedChanged += CheckBox_CheckedChanged;
            m_chbTxDmaTrigger.CheckedChanged += CheckBox_CheckedChanged;
            m_chbTxTriggerInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbTxNotFullInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbTxEmptyInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbTxOverflowInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbTxUnderflowInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbTxWatchdogInt.CheckedChanged += CheckBox_CheckedChanged;
            // Rx checkboxes
            m_chbEnableRx.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxDmaTrigger.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxTriggerInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxNotEmptyInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxFullInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxOverflowInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxUnderflowInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxWatchdogInt.CheckedChanged += CheckBox_CheckedChanged;

            //
            // Numeric event subscription
            //
            m_numClockDivider.TextChanged += NumericUpDown_TextChanged;
            m_numTxFifoTriggerLevel.TextChanged += NumericUpDown_TextChanged;
            m_numTxWatchdogValue.TextChanged += NumericUpDown_TextChanged;
            m_numRxFifoTriggerLevel.TextChanged += NumericUpDown_TextChanged;
            m_numRxWatchdogValue.TextChanged += NumericUpDown_TextChanged;

            m_params.DesignUpdates += DesignUpdates;
        }

        private void UnsubscribeEvents()
        {
            // Comboboxes event subscription
            // TX comboboxes
            m_cbTxChannels.Format -= ComboBox_Format;
            m_cbTxChannelLength.Format -= ComboBox_Format;
            m_cbTxWordLength.Format -= ComboBox_Format;
            m_cbTxOverheadValue.Format -= ComboBox_Format;
            m_cbTxMode.Format -= ComboBox_Format;
            m_cbTxAlignment.Format -= ComboBox_Format;
            m_cbTxWsPulseWidth.Format -= ComboBox_Format;
            m_cbTxSdo.Format -= ComboBox_Format;
            m_cbTxInputClockPolarity.Format -= ComboBox_Format;
            m_cbTxOutputClockPolarity.Format -= ComboBox_Format;
            m_cbTxChannels.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxChannelLength.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxWordLength.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxOverheadValue.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxMode.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxAlignment.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxWsPulseWidth.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxSdo.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxInputClockPolarity.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbTxOutputClockPolarity.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            // RX comboboxes
            m_cbRxChannels.Format -= ComboBox_Format;
            m_cbRxChannelLength.Format -= ComboBox_Format;
            m_cbRxWordLength.Format -= ComboBox_Format;
            m_cbRxSignExtension.Format -= ComboBox_Format;
            m_cbRxMode.Format -= ComboBox_Format;
            m_cbRxAlignment.Format -= ComboBox_Format;
            m_cbRxWsPulseWidth.Format -= ComboBox_Format;
            m_cbRxSdi.Format -= ComboBox_Format;
            m_cbRxInputClockPolarity.Format -= ComboBox_Format;
            m_cbRxOutputClockPolarity.Format -= ComboBox_Format;
            m_cbRxChannels.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxChannelLength.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxWordLength.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxSignExtension.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxMode.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxAlignment.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxWsPulseWidth.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxSdi.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxInputClockPolarity.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;
            m_cbRxOutputClockPolarity.SelectedIndexChanged -= ComboBox_SelectedIndexChanged;

            // Checkboxes event subscription
            // Common checkboxes
            m_chbClockFromTerminal.CheckedChanged -= CheckBox_CheckedChanged;
            // Tx checkboxes
            m_chbEnableTx.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbTxDmaTrigger.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbTxTriggerInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbTxNotFullInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbTxEmptyInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbTxOverflowInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbTxUnderflowInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbTxWatchdogInt.CheckedChanged -= CheckBox_CheckedChanged;
            // Rx checkboxes
            m_chbEnableRx.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbRxDmaTrigger.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbRxTriggerInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbRxNotEmptyInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbRxFullInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbRxOverflowInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbRxUnderflowInt.CheckedChanged -= CheckBox_CheckedChanged;
            m_chbRxWatchdogInt.CheckedChanged -= CheckBox_CheckedChanged;

            //
            // Numeric event subscription
            //
            m_numClockDivider.TextChanged -= NumericUpDown_TextChanged;
            m_numTxFifoTriggerLevel.TextChanged -= NumericUpDown_TextChanged;
            m_numTxWatchdogValue.TextChanged -= NumericUpDown_TextChanged;
            m_numRxFifoTriggerLevel.TextChanged -= NumericUpDown_TextChanged;
            m_numRxWatchdogValue.TextChanged -= NumericUpDown_TextChanged;

            m_params.DesignUpdates -= DesignUpdates;
        }

        override public void UpdateUI()
        {
            // Common parameters
            m_numClockDivider.SetValue(m_params.ClockDivider);
            m_chbClockFromTerminal.Checked = m_params.ClockFromTerminal;

            // Tx
            m_chbEnableTx.Checked = m_params.TxEnabled;
            m_cbTxChannels.SelectedItem = (CyChannels)m_params.TxChannels;
            m_cbTxChannelLength.SelectedItem = m_params.TxChannelLength;
            m_cbTxWordLength.SelectedItem = m_params.TxWordLength;
            m_cbTxMode.SelectedItem = m_params.TxMode;
            m_cbTxAlignment.SelectedItem = m_params.TxAlignment;
            m_cbTxWsPulseWidth.SelectedItem = m_params.TxWsPulseWidth;
            m_cbTxSdo.SelectedItem = m_params.TxSdo;
            m_cbTxOverheadValue.SelectedItem = (CyOverheadValue)m_params.TxOverheadValue;
            m_cbTxInputClockPolarity.SelectedItem = m_params.TxInputClockPolarity;
            m_cbTxOutputClockPolarity.SelectedItem = m_params.TxOutputClockPolarity;
            m_numTxFifoTriggerLevel.SetValue(m_params.TxFifoTriggerLevel);
            m_chbTxDmaTrigger.Checked = m_params.TxDmaTrigger;
            m_chbTxTriggerInt.Checked = m_params.TxTriggerInt;
            m_chbTxNotFullInt.Checked = m_params.TxNotFullInt;
            m_chbTxEmptyInt.Checked = m_params.TxEmptyInt;
            m_chbTxOverflowInt.Checked = m_params.TxOverflowInt;
            m_chbTxUnderflowInt.Checked = m_params.TxUnderflowInt;
            m_chbTxWatchdogInt.Checked = m_params.TxWatchdogInt;
            m_numTxWatchdogValue.SetValue(m_params.TxWatchdogValue);

            // Rx
            m_chbEnableRx.Checked = m_params.RxEnabled;
            m_cbRxChannels.SelectedItem = (CyChannels)m_params.RxChannels;
            m_cbRxChannelLength.SelectedItem = m_params.RxChannelLength;
            m_cbRxWordLength.SelectedItem = m_params.RxWordLength;
            m_cbRxMode.SelectedItem = m_params.RxMode;
            m_cbRxAlignment.SelectedItem = m_params.RxAlignment;
            m_cbRxWsPulseWidth.SelectedItem = m_params.RxWsPulseWidth;
            m_cbRxSdi.SelectedItem = m_params.RxSdi;
            m_cbRxSignExtension.SelectedItem = m_params.RxSignExtension;
            m_cbRxInputClockPolarity.SelectedItem = m_params.RxInputClockPolarity;
            m_cbRxOutputClockPolarity.SelectedItem = m_params.RxOutputClockPolarity;
            m_numRxFifoTriggerLevel.SetValue(m_params.RxFifoTriggerLevel);
            m_chbRxDmaTrigger.Checked = m_params.RxDmaTrigger;
            m_chbRxTriggerInt.Checked = m_params.RxTriggerInt;
            m_chbRxNotEmptyInt.Checked = m_params.RxNotEmptyInt;
            m_chbRxFullInt.Checked = m_params.RxFullInt;
            m_chbRxOverflowInt.Checked = m_params.RxOverflowInt;
            m_chbRxUnderflowInt.Checked = m_params.RxUnderflowInt;
            m_chbRxWatchdogInt.Checked = m_params.RxWatchdogInt;
            m_numRxWatchdogValue.SetValue(m_params.RxWatchdogValue);

            UpdateClock();
            // Update controls availability/visibility
            UpdateEnableState();

            // Validation
            ValidateAll();
        }
        #endregion Init / Update

        #region Clock
        private void UpdateClock()
        {
            double clockKhz = GetClock();

            m_lblInputClockValue.Text = CyClock.IsFrequencyKnown(clockKhz)
                ? Math.Round(clockKhz, 3).ToString()
                : Resources.UnknownClock;

            UpdateBitFrameRate();
        }

        private void UpdateBitFrameRate()
        {
            double clockKhz = GetClock();

            if (CyClock.IsFrequencyKnown(clockKhz))
            {
                string bitRateStr = GetBitRate(clockKhz, m_params.ClockDivider, CyConstants.MASTER_CLOCK_DIVIDER).
                    ToString();
                string frameRateTxStr = GetFrameRate(m_params.TxAlignment, clockKhz, m_params.ClockDivider, 
                    CyConstants.MASTER_CLOCK_DIVIDER, m_params.TxChannels, 
                    CyEnums.ToDisplayValue(m_params.TxChannelLength)).ToString();
                string frameRateRxStr = GetFrameRate(m_params.RxAlignment, clockKhz, m_params.ClockDivider, 
                    CyConstants.MASTER_CLOCK_DIVIDER, m_params.RxChannels, 
                    CyEnums.ToDisplayValue(m_params.RxChannelLength)).ToString();

                m_lblTxBitRateValue.Text = bitRateStr;
                m_lblRxBitRateValue.Text = bitRateStr;
                m_lblTxFrameRateValue.Text = frameRateTxStr;
                m_lblRxFrameRateValue.Text = frameRateRxStr;
            }
            else
            {
                m_lblTxFrameRateValue.Text = Resources.UnknownClock;
                m_lblRxFrameRateValue.Text = Resources.UnknownClock;
                m_lblTxBitRateValue.Text = Resources.UnknownClock;
                m_lblRxBitRateValue.Text = Resources.UnknownClock;
            }
        }

        private static double GetFrameRate(CyAlignment alignment, double clock, int clockDiv, int mClockDiv, 
            int channels, int channelLength)
        {
            if (alignment == CyAlignment.CY_I2S_I2S_MODE || alignment == CyAlignment.CY_I2S_LEFT_JUSTIFIED)
            {
                // The Frame Rate value = [Input clock frequency] / [Clock divider] / [Master clock divider] / 
                //                        [Channels] / [Channel length] 
                return Math.Round(clock / clockDiv / mClockDiv / channels / channelLength, 3);
            }
            else
            {
                // The Frame Rate value = [Input clock frequency] / [Clock divider] / [Master clock divider] /  
                //                        [TDM Frame Length] 
                return Math.Round(clock / clockDiv / mClockDiv / CyConstants.TDM_FRAME_LENGTH, 3);
            }
        }

        private static double GetBitRate(double clock, int clockDiv, int mClockDiv)
        {
            // The Bit Rate value = [Input clock frequency] / [Clock divider] / [Master clock divider]
            return Math.Round(clock / clockDiv / mClockDiv, 3);
        }

        private double GetClock()
        {
            return m_params.ClockFromTerminal
                ? CyClock.GetExternalClockKhz(m_params.TermQuery)
                : CyClock.GetInternalClockKhz(m_params.TermQuery);
        }

        private void DesignUpdates(object sender, EventArgs e)
        {
            UpdateClock();
        }
        #endregion

        #region Controls toggling
        private void UpdateEnableState()
        {
            // TX, RX panels
            m_panelTx.Enabled = m_params.TxEnabled;
            m_panelRx.Enabled = m_params.RxEnabled;

            // TX Overhead Value
            m_lblTxOverheadValue.Enabled = m_params.TxChannelLength > m_params.TxWordLength;
            m_cbTxOverheadValue.Enabled = m_params.TxChannelLength > m_params.TxWordLength;

            // RX Sign Extension
            m_lblRxSignExtension.Enabled = m_params.RxWordLength < CyDataLength.CY_I2S_LEN32;
            m_cbRxSignExtension.Enabled = m_params.RxWordLength < CyDataLength.CY_I2S_LEN32;

            // Input/output clock polarity
            m_lblTxInputClockPolarity.Visible = m_params.TxMode == CyMode.slave;
            m_cbTxInputClockPolarity.Visible = m_params.TxMode == CyMode.slave;
            m_lblTxOutputClockPolarity.Visible = m_params.TxMode == CyMode.master;
            m_cbTxOutputClockPolarity.Visible = m_params.TxMode == CyMode.master;
            m_lblRxInputClockPolarity.Visible = m_params.RxMode == CyMode.slave;
            m_cbRxInputClockPolarity.Visible = m_params.RxMode == CyMode.slave;
            m_lblRxOutputClockPolarity.Visible = m_params.RxMode == CyMode.master;
            m_cbRxOutputClockPolarity.Visible = m_params.RxMode == CyMode.master;

            // Watchdog
            m_chbTxWatchdogInt.Enabled = m_params.TxMode == CyMode.slave;
            m_numTxWatchdogValue.Enabled = m_params.TxMode == CyMode.slave && m_params.TxWatchdogInt;
            m_chbRxWatchdogInt.Enabled = m_params.RxMode == CyMode.slave;
            m_numRxWatchdogValue.Enabled = m_params.RxMode == CyMode.slave && m_params.RxWatchdogInt;
        }
        #endregion

        #region Validation

        private void ValidateAll()
        {
            ValidateWordLength(m_params.TxWordLength, m_params.TxChannelLength, m_cbTxWordLength);
            ValidateWordLength(m_params.RxWordLength, m_params.RxChannelLength, m_cbRxWordLength);

            ValidateChannels(m_params.TxAlignment, (CyChannels)m_params.TxChannels, m_cbTxChannels);
            ValidateChannels(m_params.RxAlignment, (CyChannels)m_params.RxChannels, m_cbRxChannels);

            ValidateChannelLength(m_params.TxAlignment, m_params.TxChannelLength, m_cbTxChannelLength);
            ValidateChannelLength(m_params.RxAlignment, m_params.RxChannelLength, m_cbRxChannelLength);

            ValidatePulseWidth(m_params.TxAlignment, m_params.TxWsPulseWidth, m_cbTxWsPulseWidth);
            ValidatePulseWidth(m_params.RxAlignment, m_params.RxWsPulseWidth, m_cbRxWsPulseWidth);

            ValidateSdoLatchingTime(m_params.TxMode, m_params.TxSdo, m_cbTxSdo);
            ValidateSdiLatchingTime(m_params.RxMode, m_params.RxSdi, m_cbRxSdi);

            ValidateRxFifoTriggerLevel();
        }

        /// <summary>
        /// Validates Word Length combobox value.
        /// Word length should be less than or equal Channel length 
        /// </summary>
        private void ValidateWordLength(CyDataLength wordLengthValue, CyDataLength channelLengthValue, 
            ComboBox cbWordLength)
        {
            if ((int)wordLengthValue > (int)channelLengthValue)
            {
                CyUtils.SetError(m_errorProvider, cbWordLength, Resources.ErrorMsgWordLength);
            }
            else
            {
                CyUtils.SetError(m_errorProvider, cbWordLength, "");
            }
        }

        /// <summary>
        /// Validates Channels combobox value.
        /// In the I2S and LJ alignment modes only 2 channels are allowed.
        /// </summary>
        private void ValidateChannels(CyAlignment alignmentValue, CyChannels channelsValue, ComboBox cbChannels)
        {
            if (((alignmentValue == CyAlignment.CY_I2S_I2S_MODE) || 
                 (alignmentValue == CyAlignment.CY_I2S_LEFT_JUSTIFIED)) &&
                (channelsValue != CyChannels.Channel2))
            {
                CyUtils.SetError(m_errorProvider, cbChannels, Resources.ErrorMsgChannels);
            }
            else
            {
                CyUtils.SetError(m_errorProvider, cbChannels, "");
            }
        }

        /// <summary>
        /// Validates Channel Length combobox value.
        /// In the TDM Mode A and B channel length 32 bits is required.
        /// </summary>
        private void ValidateChannelLength(CyAlignment alignmentValue, CyDataLength channelLengthValue, 
            ComboBox cbChannelLength)
        {
            if (((alignmentValue == CyAlignment.CY_I2S_TDM_MODE_A) ||
                 (alignmentValue == CyAlignment.CY_I2S_TDM_MODE_B)) &&
                (channelLengthValue != CyDataLength.CY_I2S_LEN32))
            {
                CyUtils.SetError(m_errorProvider, cbChannelLength, Resources.ErrorMsgChannelLength);
            }
            else
            {
                CyUtils.SetError(m_errorProvider, cbChannelLength, "");
            }
        }

        private void ValidatePulseWidth(CyAlignment alignmentValue, CyWsPulseWidth pulseWidthValue, 
            ComboBox cbPulseWidth)
        {
            if (((alignmentValue == CyAlignment.CY_I2S_I2S_MODE) ||
                 (alignmentValue == CyAlignment.CY_I2S_LEFT_JUSTIFIED)) &&
                (pulseWidthValue != CyWsPulseWidth.CY_I2S_WS_ONE_CHANNEL_LENGTH))
            {
                CyUtils.SetError(m_errorProvider, cbPulseWidth, Resources.ErrorMsgPulseWidth);
            }
            else
            {
                CyUtils.SetError(m_errorProvider, cbPulseWidth, "");
            }
        }

        private void ValidateSdoLatchingTime(CyMode modeValue, CySdoLatchingTime latchingTimeValue,
          ComboBox cbLatchingTime)
        {
            if ((modeValue == CyMode.master) &&
                (latchingTimeValue != CySdoLatchingTime.SDO_NORMAL))
            {
                CyUtils.SetError(m_errorProvider, cbLatchingTime, Resources.ErrorTxSdoLatchingTime);
            }
            else
            {
                CyUtils.SetError(m_errorProvider, cbLatchingTime, "");
            }
        }

        private void ValidateSdiLatchingTime(CyMode modeValue, CySdiLatchingTime latchingTimeValue,
          ComboBox cbLatchingTime)
        {
            if ((modeValue == CyMode.slave) &&
                (latchingTimeValue != CySdiLatchingTime.SDI_NORMAL))
            {
                CyUtils.SetError(m_errorProvider, cbLatchingTime, Resources.ErrorRxSdiLatchingTime);
            }
            else
            {
                CyUtils.SetError(m_errorProvider, cbLatchingTime, "");
            }
        }

        /// <summary>
        /// Validates RxFifoTriggerLevel numericupdown value. The value depends on the Rx channels number.
        /// </summary>
        private void ValidateRxFifoTriggerLevel()
        {
            if (m_params.RxFifoTriggerLevel > m_params.MaxRxFifoTriggerLevel)
            {
                CyUtils.SetError(m_errorProvider, m_numRxFifoTriggerLevel, String.Format(
                    Resources.ErrorMsgRxFifoTriggerLevel, m_params.MaxRxFifoTriggerLevel, m_params.RxChannels));
            }
            else
            {
                CyUtils.SetError(m_errorProvider, m_numRxFifoTriggerLevel, "");
            }
        }
        #endregion Validation

        #region Event handlers
        private void NumericUpDown_TextChanged(object sender, EventArgs e)
        {
            // Common numeric controls
            if (sender == m_numClockDivider)
            {
                m_params.ClockDivider = (int)m_numClockDivider.Value;
                UpdateBitFrameRate();
            }
            // Tx numeric controls
            else if (sender == m_numTxFifoTriggerLevel)
            {
                m_params.TxFifoTriggerLevel = (byte)m_numTxFifoTriggerLevel.Value;
            }
            else if (sender == m_numTxWatchdogValue)
            {
                m_params.TxWatchdogValue = (uint)m_numTxWatchdogValue.Value;
            }
            // Rx numeric controls
            else if (sender == m_numRxFifoTriggerLevel)
            {
                m_params.RxFifoTriggerLevel = (byte)m_numRxFifoTriggerLevel.Value;
            }
            else if (sender == m_numRxWatchdogValue)
            {
                m_params.RxWatchdogValue = (uint)m_numRxWatchdogValue.Value;
            }

            // Validation
            ValidateAll();
        }

        private void ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Tx comboboxes
            if (sender == m_cbTxChannels)
            {
                m_params.TxChannels = (int)((CyChannels)m_cbTxChannels.SelectedItem);
                UpdateBitFrameRate();
            }
            else if (sender == m_cbTxChannelLength)
            {
                m_params.TxChannelLength = (CyDataLength)m_cbTxChannelLength.SelectedItem;
                UpdateBitFrameRate();
            }
            else if (sender == m_cbTxWordLength)
            {
                m_params.TxWordLength = (CyDataLength)m_cbTxWordLength.SelectedItem;
            }
            else if (sender == m_cbTxOverheadValue)
            {
                m_params.TxOverheadValue = (int)(CyOverheadValue)m_cbTxOverheadValue.SelectedItem;
            }
            else if (sender == m_cbTxMode)
            {
                m_params.TxMode = (CyMode)m_cbTxMode.SelectedItem;
            }
            else if (sender == m_cbTxAlignment)
            {
                m_params.TxAlignment = (CyAlignment)m_cbTxAlignment.SelectedItem;
                UpdateBitFrameRate();
            }
            else if (sender == m_cbTxWsPulseWidth)
            {
                m_params.TxWsPulseWidth = (CyWsPulseWidth)m_cbTxWsPulseWidth.SelectedItem;
            }
            else if (sender == m_cbTxSdo)
            {
                m_params.TxSdo = (CySdoLatchingTime)m_cbTxSdo.SelectedItem;
            }
            else if (sender == m_cbTxInputClockPolarity)
            {
                m_params.TxInputClockPolarity = (CySckPolarity)m_cbTxInputClockPolarity.SelectedItem;
            }
            else if (sender == m_cbTxOutputClockPolarity)
            {
                m_params.TxOutputClockPolarity = (CySckPolarity)m_cbTxOutputClockPolarity.SelectedItem;
            }

            // Rx comboboxes
            else if (sender == m_cbRxChannels)
            {
                m_params.RxChannels = (int)((CyChannels)m_cbRxChannels.SelectedItem);
                UpdateBitFrameRate();
            }
            else if (sender == m_cbRxChannelLength)
            {
                m_params.RxChannelLength = (CyDataLength)m_cbRxChannelLength.SelectedItem;
                UpdateBitFrameRate();
            }
            else if (sender == m_cbRxWordLength)
            {
                m_params.RxWordLength = (CyDataLength)m_cbRxWordLength.SelectedItem;
            }
            else if (sender == m_cbRxSignExtension)
            {
                m_params.RxSignExtension = (CySignExtension)m_cbRxSignExtension.SelectedItem;
            }
            else if (sender == m_cbRxMode)
            {
                m_params.RxMode = (CyMode)m_cbRxMode.SelectedItem;
            }
            else if (sender == m_cbRxAlignment)
            {
                m_params.RxAlignment = (CyAlignment)m_cbRxAlignment.SelectedItem;
                UpdateBitFrameRate();
            }
            else if (sender == m_cbRxWsPulseWidth)
            {
                m_params.RxWsPulseWidth = (CyWsPulseWidth)m_cbRxWsPulseWidth.SelectedItem;
            }
            else if (sender == m_cbRxSdi)
            {
                m_params.RxSdi = (CySdiLatchingTime)m_cbRxSdi.SelectedItem;
            }
            else if (sender == m_cbRxInputClockPolarity)
            {
                m_params.RxInputClockPolarity = (CySckPolarity)m_cbRxInputClockPolarity.SelectedItem;
            }
            else if (sender == m_cbRxOutputClockPolarity)
            {
                m_params.RxOutputClockPolarity = (CySckPolarity)m_cbRxOutputClockPolarity.SelectedItem;
            }
            
            // Update Enable state
            UpdateEnableState();
            // Validation
            ValidateAll();
        }

        private void CheckBox_CheckedChanged(object sender, EventArgs e)
        {
            // Common checkboxes
            if (sender == m_chbClockFromTerminal)
            {
                m_params.ClockFromTerminal = m_chbClockFromTerminal.Checked;
                UpdateClock();
            }
            else if (sender == m_chbEnableTx)
            {
                m_params.TxEnabled = m_chbEnableTx.Checked;
            }
            else if (sender == m_chbTxDmaTrigger)
            {
                m_params.TxDmaTrigger = m_chbTxDmaTrigger.Checked;
            }
            else if (sender == m_chbTxTriggerInt)
            {
                m_params.TxTriggerInt = m_chbTxTriggerInt.Checked;
            }
            else if (sender == m_chbTxNotFullInt)
            {
                m_params.TxNotFullInt = m_chbTxNotFullInt.Checked;
            }
            else if (sender == m_chbTxEmptyInt)
            {
                m_params.TxEmptyInt = m_chbTxEmptyInt.Checked;
            }
            else if (sender == m_chbTxOverflowInt)
            {
                m_params.TxOverflowInt = m_chbTxOverflowInt.Checked;
            }
            else if (sender == m_chbTxUnderflowInt)
            {
                m_params.TxUnderflowInt = m_chbTxUnderflowInt.Checked;
            }
            else if (sender == m_chbTxWatchdogInt)
            {
                m_params.TxWatchdogInt = m_chbTxWatchdogInt.Checked;
                m_params.TxWatchdogEnable = m_chbTxWatchdogInt.Checked;
            }

            // Rx checkboxes
            else if (sender == m_chbEnableRx)
            {
                m_params.RxEnabled = m_chbEnableRx.Checked;
            }
            else if (sender == m_chbRxDmaTrigger)
            {
                m_params.RxDmaTrigger = m_chbRxDmaTrigger.Checked;
            }
            else if (sender == m_chbRxTriggerInt)
            {
                m_params.RxTriggerInt = m_chbRxTriggerInt.Checked;
            }
            else if (sender == m_chbRxNotEmptyInt)
            {
                m_params.RxNotEmptyInt = m_chbRxNotEmptyInt.Checked;
            }
            else if (sender == m_chbRxFullInt)
            {
                m_params.RxFullInt = m_chbRxFullInt.Checked;
            }
            else if (sender == m_chbRxOverflowInt)
            {
                m_params.RxOverflowInt = m_chbRxOverflowInt.Checked;
            }
            else if (sender == m_chbRxUnderflowInt)
            {
                m_params.RxUnderflowInt = m_chbRxUnderflowInt.Checked;
            }
            else if (sender == m_chbRxWatchdogInt)
            {
                m_params.RxWatchdogInt = m_chbRxWatchdogInt.Checked;
                m_params.RxWatchdogEnable = m_chbRxWatchdogInt.Checked;
            }

            // Update Enable state
            UpdateEnableState();
            // Validation
            ValidateAll();
        }

        private void ComboBox_Format(object sender, System.Windows.Forms.ListControlConvertEventArgs e)
        {
            if (sender == m_cbTxChannels || sender == m_cbRxChannels)
            {
                CyChannels item = (CyChannels)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxChannelLength || sender == m_cbRxChannelLength)
            {
                CyDataLength item = (CyDataLength)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxWordLength || sender == m_cbRxWordLength)
            {
                CyDataLength item = (CyDataLength)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxOverheadValue)
            {
                CyOverheadValue item = (CyOverheadValue)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbRxSignExtension)
            {
                CySignExtension item = (CySignExtension)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxMode || sender == m_cbRxMode)
            {
                CyMode item = (CyMode)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxAlignment || sender == m_cbRxAlignment)
            {
                CyAlignment item = (CyAlignment)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxWsPulseWidth || sender == m_cbRxWsPulseWidth)
            {
                CyWsPulseWidth item = (CyWsPulseWidth)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxSdo)
            {
                CySdoLatchingTime item = (CySdoLatchingTime)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbRxSdi)
            {
                CySdiLatchingTime item = (CySdiLatchingTime)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
            else if (sender == m_cbTxInputClockPolarity  || sender == m_cbRxInputClockPolarity ||
                     sender == m_cbTxOutputClockPolarity || sender == m_cbRxOutputClockPolarity)
            {
                CySckPolarity item = (CySckPolarity)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
        }
        #endregion
    }
}
