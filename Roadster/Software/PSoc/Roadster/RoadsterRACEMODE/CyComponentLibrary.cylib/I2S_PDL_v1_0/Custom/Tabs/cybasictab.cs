/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using I2S_PDL_v1_0.Utils;
using System.Windows.Forms;
namespace I2S_PDL_v1_0.Tabs
{
    internal partial class CyBasicTab : CyTabBase
    {
        /// <summary>
        /// Indicates whether update parameters during linking Rx to Tx.
        /// </summary>
        private bool m_clockDividerError = false;
        private bool m_TxFifoTriggerLevelError = false;
        private bool m_RxFifoTriggerLevelError = false;

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
            m_cbTxChannelLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbTxWordLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbTxOverheadValue.DataSource = Enum.GetValues(typeof(CyOverheadValue));

            //
            // Initialize RX group comboboxes
            //
            m_cbRxChannelLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbRxWordLength.DataSource = Enum.GetValues(typeof(CyDataLength));
            m_cbRxBitExtension.DataSource = Enum.GetValues(typeof(CyBitExtension));

            //
            // Initialize numeric controls
            //
            m_numClockDivider.Minimum = CyConstants.CLOCK_DIVIDER_MIN;
            m_numClockDivider.Maximum = CyConstants.CLOCK_DIVIDER_MAX;
            m_numClockDivider.UserMinimum = CyConstants.CLOCK_DIVIDER_MIN;
            m_numClockDivider.UserMaximum = CyConstants.CLOCK_DIVIDER_MAX;
            m_numTxFifoTriggerLevel.Minimum = CyConstants.FIFO_TRIGGER_LEVEL_MIN;
            m_numTxFifoTriggerLevel.Maximum = CyConstants.FIFO_TRIGGER_LEVEL_MAX;
            m_numTxFifoTriggerLevel.UserMinimum = CyConstants.FIFO_TRIGGER_LEVEL_MIN;
            m_numTxFifoTriggerLevel.UserMaximum = CyConstants.FIFO_TRIGGER_LEVEL_MAX;
            m_numRxFifoTriggerLevel.Minimum = CyConstants.FIFO_TRIGGER_LEVEL_MIN;
            m_numRxFifoTriggerLevel.Maximum = CyConstants.FIFO_TRIGGER_LEVEL_RX_MAX;
            m_numRxFifoTriggerLevel.UserMinimum = CyConstants.FIFO_TRIGGER_LEVEL_MIN;
            m_numRxFifoTriggerLevel.UserMaximum = CyConstants.FIFO_TRIGGER_LEVEL_RX_MAX;

            //
            // Comboboxes event subscription
            // TX comboboxes
            m_cbTxChannelLength.Format += ComboBox_Format;
            m_cbTxWordLength.Format += ComboBox_Format;
            m_cbTxOverheadValue.Format += ComboBox_Format;
            m_cbTxChannelLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxWordLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbTxOverheadValue.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            // RX comboboxes
            m_cbRxChannelLength.Format += ComboBox_Format;
            m_cbRxWordLength.Format += ComboBox_Format;
            m_cbRxBitExtension.Format += ComboBox_Format;
            m_cbRxChannelLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxWordLength.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
            m_cbRxBitExtension.SelectedIndexChanged += ComboBox_SelectedIndexChanged;

            //
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
            // Rx checkboxes
            m_chbEnableRx.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxDmaTrigger.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxTriggerInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxNotEmptyInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxFullInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxOverflowInt.CheckedChanged += CheckBox_CheckedChanged;
            m_chbRxUnderflowInt.CheckedChanged += CheckBox_CheckedChanged;

            //
            // Numeric event subscription
            //
            m_numClockDivider.TextChanged += NumericUpDown_TextChanged;
            m_numTxFifoTriggerLevel.TextChanged += NumericUpDown_TextChanged;
            m_numRxFifoTriggerLevel.TextChanged += NumericUpDown_TextChanged;

            m_params.DesignUpdates += DesignUpdates;
        }
        #endregion

        override public void UpdateUI()
        {
            // Common parameters
            try
            {
                m_numClockDivider.Value = m_params.ClockDivider;
                m_errorProvider.SetError(m_numClockDivider, "");
            }
            catch (ArgumentOutOfRangeException)
            {
                m_clockDividerError = true;
                m_numClockDivider.Text = "";
                m_errorProvider.SetError(
                    m_numClockDivider,
                    string.Format(
                        Resources.ClockDividerError,
                        CyConstants.CLOCK_DIVIDER_MIN,
                        CyConstants.CLOCK_DIVIDER_MAX));
            }

            m_chbClockFromTerminal.Checked = m_params.ClockFromTerminal;

            // Tx
            m_chbEnableTx.Checked = m_params.TxEnabled;
            m_cbTxChannelLength.SelectedItem = m_params.TxChannelLength;
            m_cbTxWordLength.SelectedItem = m_params.TxWordLength;
            m_cbTxOverheadValue.SelectedItem = (CyOverheadValue)m_params.TxOverheadValue;

            try
            {
                m_numTxFifoTriggerLevel.Value = m_params.TxFifoTriggerLevel;
                m_errorProvider.SetError(m_numTxFifoTriggerLevel, "");
            }
            catch (ArgumentOutOfRangeException)
            {
                m_TxFifoTriggerLevelError = true;
                m_numTxFifoTriggerLevel.Text = "";
                m_errorProvider.SetError(
                    m_numTxFifoTriggerLevel,
                    string.Format(Resources.FifoTriggerError,
                    CyConstants.FIFO_TRIGGER_LEVEL_MIN,
                    CyConstants.FIFO_TRIGGER_LEVEL_MAX));
            }

            m_chbTxDmaTrigger.Checked = m_params.TxDmaTrigger;
            m_chbTxTriggerInt.Checked = m_params.TxTriggerInt;
            m_chbTxNotFullInt.Checked = m_params.TxNotFullInt;
            m_chbTxEmptyInt.Checked = m_params.TxEmptyInt;
            m_chbTxOverflowInt.Checked = m_params.TxOverflowInt;
            m_chbTxUnderflowInt.Checked = m_params.TxUnderflowInt;

            // Rx
            m_chbEnableRx.Checked = m_params.RxEnabled;
            m_cbRxChannelLength.SelectedItem = m_params.RxChannelLength;
            m_cbRxWordLength.SelectedItem = m_params.RxWordLength;
            m_cbRxBitExtension.SelectedItem = m_params.RxBitExtension;

            try
            {
                m_numRxFifoTriggerLevel.Value = m_params.RxFifoTriggerLevel;
                m_errorProvider.SetError(m_numRxFifoTriggerLevel, "");
            }
            catch (ArgumentOutOfRangeException)
            {
                m_RxFifoTriggerLevelError = true;
                m_numRxFifoTriggerLevel.Text = "";
                m_errorProvider.SetError(
                    m_numRxFifoTriggerLevel,
                    string.Format(Resources.FifoTriggerError,
                    CyConstants.FIFO_TRIGGER_LEVEL_MIN,
                    CyConstants.FIFO_TRIGGER_LEVEL_RX_MAX));
            }

            m_chbRxDmaTrigger.Checked = m_params.RxDmaTrigger;
            m_chbRxTriggerInt.Checked = m_params.RxTriggerInt;
            m_chbRxNotEmptyInt.Checked = m_params.RxNotEmptyInt;
            m_chbRxFullInt.Checked = m_params.RxFullInt;
            m_chbRxOverflowInt.Checked = m_params.RxOverflowInt;
            m_chbRxUnderflowInt.Checked = m_params.RxUnderflowInt;

            // Update controls availability/visibility
            UpdateClock();
            UpdateFrameRate();
            SetTxAvaiability(m_params.TxEnabled);
            SetRxAvaiability(m_params.RxEnabled);
            ToggleChannelLength();
            ToggleWordLength();
            ToggleOverheadValue();
            ToggleBitExtension();
        }

        #region Clock
        private void UpdateClock()
        {
            double clockKhz = GetClock();

            m_lblInputClockValue.Text = CyClock.IsFrequencyKnown(clockKhz)
                ? Math.Round(clockKhz, 3).ToString()
                : Resources.UnknownClock;
        }

        private void UpdateFrameRate()
        {
            double clockKhz = GetClock();

            m_lblTxFrameRateValue.Text = CyClock.IsFrequencyKnown(clockKhz)
                ? GetFrameRate(clockKhz, m_params.ClockDivider, CyConstants.MASTER_CLOCK_DIVIDER,
                               CyConstants.CHANNELS, CyEnums.ToDisplayValue(m_params.TxChannelLength)).ToString()
                : Resources.UnknownClock;

            m_lblRxFrameRateValue.Text = CyClock.IsFrequencyKnown(clockKhz)
                ? GetFrameRate(clockKhz, m_params.ClockDivider, CyConstants.MASTER_CLOCK_DIVIDER,
                               CyConstants.CHANNELS, CyEnums.ToDisplayValue(m_params.RxChannelLength)).ToString()
                : Resources.UnknownClock;

            m_lblBitRateValue.Text = CyClock.IsFrequencyKnown(clockKhz)
                ? GetBitRate(clockKhz, m_params.ClockDivider, CyConstants.MASTER_CLOCK_DIVIDER).ToString()
                : Resources.UnknownClock;

        }

        private static double GetFrameRate(double clock, int clockDiv, int mClockDiv, int channels, int channelLength)
        {
            return Math.Round(clock / clockDiv / mClockDiv / channels / channelLength, 3);
        }

        private static double GetBitRate(double clock, int clockDiv, int mClockDiv)
        {
            //The Bit Rate value = [Input clock frequency] / [Clock divider] / [Master clock divider]
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
            UpdateFrameRate();
        }
        #endregion

        #region Controls toggling

        private void SetTxAvaiability(bool isEnabled)
        {
            m_panelTx.Enabled = isEnabled;
        }

        private void SetRxAvaiability(bool isEnabled)
        {
            m_panelRx.Enabled = isEnabled;
        }

        private void ToggleChannelLength()
        {
            m_cbRxChannelLength.Enabled = true;
        }

        private void ToggleWordLength()
        {
            m_cbRxWordLength.Enabled = true;
        }

        private void ToggleOverheadValue()
        {
            m_lblTxOverheadValue.Enabled = m_params.TxChannelLength > m_params.TxWordLength;
            m_cbTxOverheadValue.Enabled = m_params.TxChannelLength > m_params.TxWordLength;
        }

        private void ToggleBitExtension()
        {
            m_lblRxBitExtension.Enabled = m_params.RxWordLength < CyDataLength.CY_I2S_LEN32;
            m_cbRxBitExtension.Enabled = m_params.RxWordLength < CyDataLength.CY_I2S_LEN32;
        }

        #endregion

        #region Event handlers
        private void NumericUpDown_TextChanged(object sender, EventArgs e)
        {
            // Common numeric controls
            if (sender == m_numClockDivider)
            {
                m_params.ClockDivider = (int)m_numClockDivider.Value;
                UpdateFrameRate();
                if (!m_clockDividerError)
                {
                    m_errorProvider.SetError(m_numClockDivider, "");
                }
                else
                {
                    m_clockDividerError = false;
                }

            }
            // Tx numeric controls
            else if (sender == m_numTxFifoTriggerLevel)
            {
                m_params.TxFifoTriggerLevel = (byte)m_numTxFifoTriggerLevel.Value;
                if (!m_TxFifoTriggerLevelError)
                {
                    m_errorProvider.SetError(m_numTxFifoTriggerLevel, "");
                }
                else
                {
                    m_TxFifoTriggerLevelError = false;
                }
            }
            // Rx numeric controls
            else if (sender == m_numRxFifoTriggerLevel)
            {
                m_params.RxFifoTriggerLevel = (byte)m_numRxFifoTriggerLevel.Value;

                if (!m_RxFifoTriggerLevelError)
                {
                    m_errorProvider.SetError(m_numRxFifoTriggerLevel, "");
                }
                else
                {
                    m_RxFifoTriggerLevelError = false;
                }
            }
        }

        private void ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Tx comboboxes
            if (sender == m_cbTxChannelLength)
            {
                WordLengthValidating(m_cbTxWordLength, m_cbTxChannelLength);
                m_params.TxChannelLength = (CyDataLength)m_cbTxChannelLength.SelectedItem;
                ToggleOverheadValue();
                UpdateFrameRate();
            }
            else if (sender == m_cbTxWordLength)
            {
                WordLengthValidating(m_cbTxWordLength, m_cbTxChannelLength);
                m_params.TxWordLength = (CyDataLength)m_cbTxWordLength.SelectedItem;
                ToggleOverheadValue();

            }
            else if (sender == m_cbTxOverheadValue)
            {
                m_params.TxOverheadValue = (int)(CyOverheadValue)m_cbTxOverheadValue.SelectedItem;
            }

            // Rx comboboxes
            else if (sender == m_cbRxChannelLength)
            {
                WordLengthValidating(m_cbRxWordLength, m_cbRxChannelLength);
                m_params.RxChannelLength = (CyDataLength)m_cbRxChannelLength.SelectedItem;
                ToggleBitExtension();
                UpdateFrameRate();
            }
            else if (sender == m_cbRxWordLength)
            {
                WordLengthValidating(m_cbRxWordLength, m_cbRxChannelLength);
                m_params.RxWordLength = (CyDataLength)m_cbRxWordLength.SelectedItem;
                ToggleBitExtension();
            }
            else if (sender == m_cbRxBitExtension)
            {
                m_params.RxBitExtension = (CyBitExtension)m_cbRxBitExtension.SelectedItem;
            }
        }

        private void CheckBox_CheckedChanged(object sender, EventArgs e)
        {
            // Common checkboxes
            if (sender == m_chbClockFromTerminal)
            {
                m_params.ClockFromTerminal = m_chbClockFromTerminal.Checked;
                if (m_params.ClockFromTerminal == false)
                {
                    UpdateClock();
                }
                else
                {
                    if (CyClock.IsFrequencyKnown(CyClock.GetExternalClockKhz(m_params.TermQuery)))
                    {
                        UpdateClock();
                    }
                    else
                    {
                        m_lblInputClockValue.Text = Resources.UnknownClock;
                    }
                }
                UpdateFrameRate();
            }
            else if (sender == m_chbEnableTx)
            {
                m_params.TxEnabled = m_chbEnableTx.Checked;
                SetTxAvaiability(m_params.TxEnabled);
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

            // Rx checkboxes
            else if (sender == m_chbEnableRx)
            {
                m_params.RxEnabled = m_chbEnableRx.Checked;
                SetRxAvaiability(m_params.RxEnabled);
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
            else if (sender == m_cbTxWordLength)
            {

            }
        }

        private void ComboBox_Format(object sender, System.Windows.Forms.ListControlConvertEventArgs e)
        {
            if (sender == m_cbTxChannelLength || sender == m_cbRxChannelLength)
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
            else if (sender == m_cbRxBitExtension)
            {
                CyBitExtension item = (CyBitExtension)e.ListItem;
                e.Value = CyEnums.ToDisplayName(item);
            }
        }
        #endregion

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
        }

        private bool WordLengthValidating(ComboBox cbWordLength, ComboBox cbChannelLength)
        {
            if (cbWordLength.SelectedIndex > cbChannelLength.SelectedIndex)
            {
                m_errorProvider.SetError(
                        cbWordLength,
                        "Word length value must be less or equal Channel length.");
                return false;
            }
            else
            {
                m_errorProvider.SetError(
                        cbWordLength,
                        "");
                return true;
            }
        }
    }
}
