/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
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
    public partial class CySPIAdvancedTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "SPI Advanced";
            }
        }

        public override string TabDisplayName
        {
            get { return Resources.SPIAdvancedTabDisplayName; }
        }
        #endregion

        private bool m_triggerLevelUpdateLocked = false;

        #region Constructor(s)
        public CySPIAdvancedTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            m_params.SpiAdvancedTab = this;

            InitializeComponent();

            UpdateTriggerLevelRange(m_cbRXTriggerLevel);
            UpdateTriggerLevelRange(m_cbTXTriggerLevel);

            #region Event handler assigning
            m_chbInterruptSPIDone.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXNotFull.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXEmpty.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXOverflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXUnderflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXTrigger.CheckedChanged += m_chb_CheckedChanged;
            m_chbByteMode.CheckedChanged += m_chb_CheckedChanged;
            m_chbRxOutput.CheckedChanged += m_chb_CheckedChanged;
            m_chbTxOutput.CheckedChanged += m_chb_CheckedChanged;

            m_chbInterruptSPIBusError.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXNotEmpty.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXFull.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXOverflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXUnderflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXTrigger.CheckedChanged += m_chb_CheckedChanged;

            m_cbRXTriggerLevel.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbTXTriggerLevel.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbRXTriggerLevel.Validating += m_cbTriggerLevel_Validating;
            m_cbTXTriggerLevel.Validating += m_cbTriggerLevel_Validating;

            m_rbNone.CheckedChanged += m_rb_CheckedChanged;
            m_rbInternal.CheckedChanged += m_rb_CheckedChanged;
            m_rbExternal.CheckedChanged += m_rb_CheckedChanged;

            m_numRXBufferSize.Validating += m_numBufferSize_Validating;
            m_numTXBufferSize.TextChanged += m_numBufferSize_TextChanged;
            m_numRXBufferSize.TextChanged += m_numBufferSize_TextChanged;
            m_numTXBufferSize.Validating += m_numBufferSize_Validating;
            m_params.ScbModeChanged += m_params_ScbModeChanged;
            #endregion

            m_numRXBufferSize.Maximum = decimal.MaxValue;
            m_numRXBufferSize.Minimum = 0;

            m_numTXBufferSize.Maximum = decimal.MaxValue;
            m_numTXBufferSize.Minimum = 0;
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            if (m_params == null)
                return;

            m_numRXBufferSize.Text = m_params.SPI_RxBufferSize.ToString();
            m_numTXBufferSize.Text = m_params.SPI_TxBufferSize.ToString();
            m_chbByteMode.Checked = m_params.SPI_EnableByteMode;

            m_chbRxOutput.Checked = m_params.SPI_RxOutput;
            m_chbTxOutput.Checked = m_params.SPI_TxOutput;

            m_chbInterruptSPIBusError.Checked = m_params.SPI_InterruptOnSPIBusError;
            m_chbInterruptRXFull.Checked = m_params.SPI_InterruptOnRXFull;
            m_chbInterruptRXNotEmpty.Checked = m_params.SPI_InterruptOnRXNotEmpty;
            m_chbInterruptRXOverflow.Checked = m_params.SPI_InterruptOnRXOverflow;
            m_chbInterruptRXTrigger.Checked = m_params.SPI_InterruptOnRXTrigger;
            m_chbInterruptRXUnderflow.Checked = m_params.SPI_InterruptOnRXUnderflow;

            m_chbInterruptSPIDone.Checked = m_params.SPI_InterruptOnSPIDone;
            m_chbInterruptTXEmpty.Checked = m_params.SPI_InterruptOnTXEmpty;
            m_chbInterruptTXNotFull.Checked = m_params.SPI_InterruptOnTXNotFull;
            m_chbInterruptTXOverflow.Checked = m_params.SPI_InterruptOnTXOverflow;
            m_chbInterruptTXTrigger.Checked = m_params.SPI_InterruptOnTXTrigger;
            m_chbInterruptTXUnderflow.Checked = m_params.SPI_InterruptOnTXUnderflow;

            m_cbRXTriggerLevel.SelectedIndex = m_params.SPI_RxBufferTriggerLevel;
            m_cbTXTriggerLevel.SelectedIndex = m_params.SPI_TxBufferTriggerLevel;

            switch (m_params.SPI_InterruptMode)
            {
                case CyEInterruptModeType.INTERRUPT_NONE:
                    m_rbNone.Checked = true;
                    break;
                case CyEInterruptModeType.INTERNAL:
                    m_rbInternal.Checked = true;
                    break;
                case CyEInterruptModeType.EXTERNAL:
                    m_rbExternal.Checked = true;
                    break;
                default:
                    break;
            }

            UpdateInterruptsVisibility();
            UpdateInterruptSources();
            UpdateByteModeCheckBoxState();
            UpdateDmaSettingsState();

            // Validate RX TX buffers values, because for CCG3 the default values are wrong
            UpdateRxTxBuffersValidations();
        }
        
        public void ValidateTab()
        {
            m_numBufferSize_Validating(m_numRXBufferSize, null);
            m_numBufferSize_Validating(m_numTXBufferSize, null);
            UpdateInterruptsVisibility();
            UpdateInterruptSources();
            UpdateTriggerLevelRange(m_cbRXTriggerLevel);
            UpdateTriggerLevelRange(m_cbTXTriggerLevel);
            m_cbTriggerLevel_Validating(m_cbRXTriggerLevel, null);
            m_cbTriggerLevel_Validating(m_cbTXTriggerLevel, null);
        }

        public void UpdateInterruptSources()
        {
            m_chbInterruptSPIBusError.Checked = m_params.SpiMode.Value == CyESPIModeType.SPI_SLAVE &&
                m_params.SPI_InterruptOnSPIBusError;
            m_chbInterruptSPIDone.Checked = m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER &&
                m_params.SPI_InterruptOnSPIDone;
        }

        public void UpdateInterruptsVisibility()
        {
            byte rxBufferMinSize = m_params.SpiRxBufferMinSize;
            byte txBufferMinSize = m_params.SpiTxBufferMinSize;

            bool bufSizeOverflow = (m_params.SPI_RxBufferSize > rxBufferMinSize) ||
                 (m_params.SPI_TxBufferSize > txBufferMinSize);

            m_rbNone.Enabled = !bufSizeOverflow;
            m_rbExternal.Enabled = !bufSizeOverflow;

            m_rbInternal.Checked = bufSizeOverflow || m_params.SPI_InterruptMode == CyEInterruptModeType.INTERNAL;

            bool interruptEnabled = m_params.SPI_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE;

            groupBox1.Enabled = interruptEnabled;

            m_chbInterruptSPIDone.Enabled = interruptEnabled &&
                (m_params.SpiMode.Value == CyESPIModeType.SPI_MASTER);
            m_chbInterruptSPIBusError.Enabled = interruptEnabled &&
                (m_params.SpiMode.Value == CyESPIModeType.SPI_SLAVE);
            m_chbInterruptTXNotFull.Enabled = interruptEnabled &&
                (m_params.SPI_TxBufferSize == txBufferMinSize);
            m_chbInterruptTXEmpty.Enabled = interruptEnabled;
            m_chbInterruptTXOverflow.Enabled = interruptEnabled;
            m_chbInterruptTXUnderflow.Enabled = interruptEnabled;
            m_chbInterruptTXTrigger.Enabled = interruptEnabled;

            m_chbInterruptRXNotEmpty.Enabled = interruptEnabled && (m_params.SPI_RxBufferSize == rxBufferMinSize);
            m_chbInterruptRXFull.Enabled = interruptEnabled;
            m_chbInterruptRXOverflow.Enabled = interruptEnabled;
            m_chbInterruptRXUnderflow.Enabled = interruptEnabled;
            m_chbInterruptRXTrigger.Enabled = interruptEnabled;

            UpdateFifoLevelState();
            UpdateRXInterruptNotEmpty();

            if (m_params.SPI_TxBufferSize > txBufferMinSize)
            {
                m_chbInterruptTXNotFull.Enabled = false;
            }
        }

        public void UpdateRXInterruptNotEmpty()
        {
            bool isByteMode = m_params.IsScbIPV2 && m_params.SPI_EnableByteMode;
            bool interruptEnabled = m_params.SPI_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE;
            if (m_params.SPI_RxBufferSize == m_params.GetByteModeBufferMinSize())
            {
                if (isByteMode) // uncheck RX FIFO not empty interrupt in byte mode
                {
                    if (interruptEnabled && m_chbInterruptRXNotEmpty.Enabled == false)
                    {
                        m_chbInterruptRXNotEmpty.Checked = false;
                        m_chbInterruptRXNotEmpty.Enabled = true;
                    }
                }
                else
                {
                    if (interruptEnabled)
                    {
                        m_chbInterruptRXNotEmpty.Checked = true;
                        m_chbInterruptRXNotEmpty.Enabled = false;
                    }
                }
            }
            else if (m_params.SPI_RxBufferSize > m_params.SpiRxBufferMinSize)
            {
                m_chbInterruptRXNotEmpty.Enabled = false;

                if (isByteMode)
                {
                    m_chbInterruptRXNotEmpty.Checked = true;
                }
            }
        }

        private void UpdateTriggerLevelRange(object sender)
        {
            ComboBox currentComboBox = sender as ComboBox;
            byte currentTriggerLevel = 0;
            byte maxTriggerLevel = m_params.SpiMaxTriggerLevel;

            if (currentComboBox == m_cbRXTriggerLevel)
            {
                currentTriggerLevel = m_params.SPI_RxBufferTriggerLevel;
            }
            else if (currentComboBox == m_cbTXTriggerLevel)
            {
                currentTriggerLevel = m_params.SPI_TxBufferTriggerLevel;
            }

            if (currentTriggerLevel > maxTriggerLevel)
            {
                maxTriggerLevel = CyParamRanges.MAX_TRIGGER_LEVEL_BYTE_MODE;
            }

            m_triggerLevelUpdateLocked = true;
            currentComboBox.Items.Clear();
            for (byte i = CyParamRanges.MIN_TRIGGER_LEVEL; i <= maxTriggerLevel; i++)
            {
                currentComboBox.Items.Add(i);
            }
            currentComboBox.SelectedIndex = currentTriggerLevel;
            m_triggerLevelUpdateLocked = false;
        }

        public void UpdateByteModeCheckBoxState()
        {
            m_chbByteMode.Enabled = m_params.IsScbIPV2 || m_params.SPI_EnableByteMode;
            m_errorProvider.SetError(m_chbByteMode, m_params.IsScbIPV2
                ? String.Empty
                : m_params.SPI_EnableByteMode ? Resources.ByteModeError : String.Empty);

            if (m_params.SpiBasicTab != null && String.IsNullOrEmpty(m_errorProvider.GetError(m_chbByteMode)))
            {
                bool validByteModeValue = m_params.SpiBasicTab.ValidateTxRxDataBits();
                m_errorProvider.SetError(m_chbByteMode, validByteModeValue ?
                    String.Empty : Resources.ByteModeDataBitsErrorAdv);
            }
        }

        public void UpdateDmaSettingsState()
        {
            // Handle error provider
            ClearNotifications(m_chbRxOutput);
            ClearNotifications(m_chbTxOutput);
            if (m_params.SPI_RxOutput && m_params.SpiIsRxFifoUsed == false)
                m_errorProvider.SetError(m_chbRxOutput, Resources.DMAFifoNotUsedError);
            if (m_params.SPI_TxOutput && m_params.SpiIsTxFifoUsed == false)
                m_errorProvider.SetError(m_chbTxOutput, Resources.DMAFifoNotUsedError);

            // Enable/Disable controls
            bool isRxOutputEnabled = m_params.SpiIsRxFifoUsed || m_params.SPI_RxOutput;
            bool isTxOutputEnabled = m_params.SpiIsTxFifoUsed || m_params.SPI_TxOutput;

            if (m_params.IsDmaCapable == false)
            {
                isRxOutputEnabled = false;
                isTxOutputEnabled = false;

                if (m_params.SPI_RxOutput)
                {
                    m_errorProvider.SetError(m_chbRxOutput, Resources.DMASupportError);
                    isRxOutputEnabled = true;
                }

                if (m_params.SPI_TxOutput)
                {
                    m_errorProvider.SetError(m_chbTxOutput, Resources.DMASupportError);
                    isTxOutputEnabled = true;
                }
            }

            m_chbRxOutput.Enabled = isRxOutputEnabled;
            m_chbTxOutput.Enabled = isTxOutputEnabled;
            m_gbDma.Enabled = isRxOutputEnabled || isTxOutputEnabled;

            UpdateFifoLevelState();
        }

        public void UpdateFifoLevelState()
        {
            bool rxEnabled = (m_params.SPI_RxOutput && m_params.SpiIsRxFifoUsed) ||
                             (m_params.SPI_InterruptOnRXTrigger || m_params.SPI_RxOutput);
            bool txEnabled = (m_params.SPI_TxOutput && m_params.SpiIsTxFifoUsed) ||
                             (m_params.SPI_InterruptOnTXTrigger || m_params.SPI_TxOutput);

            m_panelRxFifoLevel.Enabled = rxEnabled;
            m_panelTxFifoLevel.Enabled = txEnabled;
            m_gbFifoLevels.Enabled = rxEnabled || txEnabled;
        }

        private void UpdateBufferValidation(NumericUpDown numUpDown, UInt32 value, byte minValue)
        {
            if (value < minValue)
            {
                string errorMsg = string.Format(Resources.ErrorValueLimitBufferSize, minValue);
                m_errorProvider.SetError(numUpDown, errorMsg);
            }
        }

        private void UpdateRxTxBuffersValidations()
        {
            UpdateBufferValidation(m_numRXBufferSize, m_params.SPI_RxBufferSize, m_params.SpiRxBufferMinSize);
            UpdateBufferValidation(m_numTXBufferSize, m_params.SPI_TxBufferSize, m_params.SpiTxBufferMinSize);
        }
        #endregion

        #region Event handlers
        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.SPI)
                ShowTab();
            else
                HideTab();
        }

        void m_numBufferSize_TextChanged(object sender, EventArgs e)
        {
            CancelEventArgs ce = new CancelEventArgs();
            m_numBufferSize_Validating(sender, ce);
            if (!ce.Cancel)
            {
                UInt32 val;
                UInt32.TryParse((sender as NumericUpDown).Text, out val);

                byte rxBufferMinSize = m_params.SpiRxBufferMinSize;
                byte txBufferMinSize = m_params.SpiTxBufferMinSize;

                if (sender == m_numRXBufferSize)
                {
                    if (val == rxBufferMinSize && m_params.SPI_RxBufferSize > val)
                    {
                        m_chbInterruptRXNotEmpty.Checked = false;
                    }

                    m_params.SPI_RxBufferSize = val;

                    if (m_params.SPI_RxBufferSize > rxBufferMinSize)
                    {
                        m_chbInterruptRXNotEmpty.Checked = true;
                    }
                }
                if (sender == m_numTXBufferSize)
                {
                    m_params.SPI_TxBufferSize = val;

                    if (m_params.SPI_TxBufferSize > txBufferMinSize)
                    {
                        m_chbInterruptTXNotFull.Checked = false;
                    }
                }
            }
            UpdateInterruptsVisibility();
            UpdateDmaSettingsState();
        }

        void m_numBufferSize_Validating(object sender, CancelEventArgs e)
        {
            bool error = false;
            string message = String.Empty;
            if (sender is NumericUpDown == false) return;
            NumericUpDown cnt = sender as NumericUpDown;

            UInt32 min = m_params.SpiTxBufferMinSize;
            UInt32 max = UInt32.MaxValue;

            try
            {
                UInt32 val = Convert.ToUInt32(cnt.Text);

                if (val < min || val > max) throw new Exception();
            }
            catch
            {
                message = (m_params.IsScbIPV2 && m_params.SPI_EnableByteMode)
                    ? Resources.ByteModeBufferSizeError
                    : String.Format(Resources.ErrorValueLimitBufferSize, min);
                error = true;
            }

            m_errorProvider.SetError((Control)sender, error ? message : String.Empty);
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == m_chbInterruptSPIDone)
            {
                m_params.SPI_InterruptOnSPIDone = m_chbInterruptSPIDone.Checked;
            }
            else if (sender == m_chbInterruptTXNotFull)
            {
                m_params.SPI_InterruptOnTXNotFull = m_chbInterruptTXNotFull.Checked;
            }
            else if (sender == m_chbInterruptTXEmpty)
            {
                m_params.SPI_InterruptOnTXEmpty = m_chbInterruptTXEmpty.Checked;
            }
            else if (sender == m_chbInterruptTXOverflow)
            {
                m_params.SPI_InterruptOnTXOverflow = m_chbInterruptTXOverflow.Checked;
            }
            else if (sender == m_chbInterruptTXUnderflow)
            {
                m_params.SPI_InterruptOnTXUnderflow = m_chbInterruptTXUnderflow.Checked;
            }
            else if (sender == m_chbInterruptTXTrigger)
            {
                m_params.SPI_InterruptOnTXTrigger = m_chbInterruptTXTrigger.Checked;
                m_cbTriggerLevel_Validating(m_cbTXTriggerLevel, null);
                UpdateFifoLevelState();
            }
            else if (sender == m_chbInterruptSPIBusError)
            {
                m_params.SPI_InterruptOnSPIBusError = m_chbInterruptSPIBusError.Checked;
            }
            else if (sender == m_chbInterruptRXNotEmpty)
            {
                m_params.SPI_InterruptOnRXNotEmpty = m_chbInterruptRXNotEmpty.Checked;
            }
            else if (sender == m_chbInterruptRXFull)
            {
                m_params.SPI_InterruptOnRXFull = m_chbInterruptRXFull.Checked;
            }
            else if (sender == m_chbInterruptRXOverflow)
            {
                m_params.SPI_InterruptOnRXOverflow = m_chbInterruptRXOverflow.Checked;
            }
            else if (sender == m_chbInterruptRXUnderflow)
            {
                m_params.SPI_InterruptOnRXUnderflow = m_chbInterruptRXUnderflow.Checked;
            }
            else if (sender == m_chbInterruptRXTrigger)
            {
                m_params.SPI_InterruptOnRXTrigger = m_chbInterruptRXTrigger.Checked;
                m_cbTriggerLevel_Validating(m_cbRXTriggerLevel, null);
                UpdateFifoLevelState();
            }
            else if (sender == m_chbByteMode)
            {
                m_params.SPI_EnableByteMode = m_chbByteMode.Checked;

                UpdateByteModeCheckBoxState();
                UpdateRXInterruptNotEmpty();
                UpdateDmaSettingsState();
                ValidateTab();
            }
            else if (sender == m_chbRxOutput)
            {
                m_params.SPI_RxOutput = m_chbRxOutput.Checked;
                m_cbTriggerLevel_Validating(m_cbRXTriggerLevel, null);
                UpdateDmaSettingsState();
            }
            else if (sender == m_chbTxOutput)
            {
                m_params.SPI_TxOutput = m_chbTxOutput.Checked;
                m_cbTriggerLevel_Validating(m_cbTXTriggerLevel, null);
                UpdateDmaSettingsState();
            }
        }

        void m_rb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbNone.Checked)
            {
                m_params.SPI_InterruptMode = CyEInterruptModeType.INTERRUPT_NONE;

                #region Clear all interrupts
                m_chbInterruptSPIDone.Checked = false;
                m_chbInterruptTXNotFull.Checked = false;
                m_chbInterruptTXEmpty.Checked = false;
                m_chbInterruptTXOverflow.Checked = false;
                m_chbInterruptTXUnderflow.Checked = false;
                m_chbInterruptTXTrigger.Checked = false;

                m_chbInterruptSPIBusError.Checked = false;
                m_chbInterruptRXNotEmpty.Checked = false;
                m_chbInterruptRXFull.Checked = false;
                m_chbInterruptRXOverflow.Checked = false;
                m_chbInterruptRXUnderflow.Checked = false;
                m_chbInterruptRXTrigger.Checked = false;
                #endregion
            }
            else if (m_rbInternal.Checked)
            {
                m_params.SPI_InterruptMode = CyEInterruptModeType.INTERNAL;
            }
            else
            {
                m_params.SPI_InterruptMode = CyEInterruptModeType.EXTERNAL;
            }

            UpdateInterruptsVisibility();
            if (m_params.SpiBasicTab != null)
            {
                m_params.SpiBasicTab.UpdateCheckBoxesStates();
            }
        }

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (sender == m_cbRXTriggerLevel)
            {
                m_params.SPI_RxBufferTriggerLevel = (byte)m_cbRXTriggerLevel.SelectedIndex;
            }
            else if (sender == m_cbTXTriggerLevel)
            {
                m_params.SPI_TxBufferTriggerLevel = (byte)m_cbTXTriggerLevel.SelectedIndex;
            }

            if (String.IsNullOrEmpty(m_errorProvider.GetError(sender as Control)) == false)
            {
                if (m_triggerLevelUpdateLocked == false)
                    UpdateTriggerLevelRange(sender);
            }

            m_cbTriggerLevel_Validating(sender, null);
        }

        void m_cbTriggerLevel_Validating(object sender, CancelEventArgs e)
        {
            ComboBox currentComboBox = sender as ComboBox;
            byte currentTriggerLevel = 0;
            byte maxTriggerLevel = m_params.SpiMaxTriggerLevel;
            bool fifoLevelEnabled = false;

            if (sender == m_cbRXTriggerLevel)
            {
                currentTriggerLevel = m_params.SPI_RxBufferTriggerLevel;
                fifoLevelEnabled = m_params.SPI_InterruptOnRXTrigger || m_params.SPI_RxOutput;
            }
            else if (sender == m_cbTXTriggerLevel)
            {
                currentTriggerLevel = m_params.SPI_TxBufferTriggerLevel;
                fifoLevelEnabled = m_params.SPI_InterruptOnTXTrigger || m_params.SPI_TxOutput;
            }

            if (currentTriggerLevel > maxTriggerLevel && fifoLevelEnabled)
            {
                m_errorProvider.SetError(currentComboBox,
                    String.Format(Resources.TriggerLevelError, CyParamRanges.MIN_TRIGGER_LEVEL, maxTriggerLevel));
            }
            else
            {
                m_errorProvider.SetError(currentComboBox, String.Empty);
            }
        }
        #endregion
    }
}
