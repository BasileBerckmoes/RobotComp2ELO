/*******************************************************************************
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace SCB_P4_v3_20
{
    public partial class CyUARTAdvancedTab : CyTabControlWrapper
    {
        private readonly CheckBox[] m_txSources;
        private readonly CheckBox[] m_rxSources;
        private bool m_triggerLevelUpdateLocked = false;

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get { return "UART Advanced"; }
        }

        public override string TabDisplayName
        {
            get { return Resources.UARTAdvancedTabDisplayName; }
        }
        #endregion

        #region Constructor(s)
        public CyUARTAdvancedTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            m_params = parameters;
            m_params.UartAdvancedTab = this;

            InitializeComponent();

            m_txSources = new CheckBox[] { m_chbInterruptUARTDone, m_chbInterruptTXEmpty, m_chbInterruptTXOverflow,
                m_chbInterruptTXUnderflow, m_chbInterruptTXTrigger };
            m_rxSources = new CheckBox[] { m_chbInterruptRXFull, m_chbInterruptRXOverflow, m_chbInterruptRXUnderflow,
                m_chbInterruptRXFrameErr, m_chbInterruptRXParityErr, m_chbInterruptRXTrigger };

            #region Add combobox ranges
            UpdateTriggerLevelRange(m_cbRXTriggerLevel);
            UpdateTriggerLevelRange(m_cbTXTriggerLevel);

            m_cbRtsPolarity.Items.AddRange(m_params.UartRtsPolarity.EnumDescriptionsList);
            m_cbCtsPolarity.Items.AddRange(m_params.UartCtsPolarity.EnumDescriptionsList);
            #endregion

            #region Add event handlers
            m_numRXBufferSize.TextChanged += m_numBufferSize_TextChanged;
            m_numTXBufferSize.TextChanged += m_numBufferSize_TextChanged;
            m_chbByteMode.CheckedChanged += m_chb_CheckedChanged;
            m_chbRxOutput.CheckedChanged += m_chb_CheckedChanged;
            m_chbTxOutput.CheckedChanged += m_chb_CheckedChanged;

            m_chbInterruptUARTDone.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXNotFull.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXEmpty.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXOverflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXUnderflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXLostArb.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTxNack.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptTXTrigger.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXFull.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXNotEmpty.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXOverflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXUnderflow.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXFrameErr.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXParityErr.CheckedChanged += m_chb_CheckedChanged;
            m_chbInterruptRXTrigger.CheckedChanged += m_chb_CheckedChanged;
            m_chbEnMultiProcMode.CheckedChanged += m_chb_CheckedChanged;
            m_chbAcceptAddress.CheckedChanged += m_chb_CheckedChanged;
            m_chbDropOnParityError.CheckedChanged += m_chb_CheckedChanged;
            m_chbDropOnFrameError.CheckedChanged += m_chb_CheckedChanged;

            m_cbRXTriggerLevel.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbTXTriggerLevel.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbRXTriggerLevel.Validating += m_cbTriggerLevel_Validating;
            m_cbTXTriggerLevel.Validating += m_cbTriggerLevel_Validating;

            m_rbNone.CheckedChanged += m_rbIntrMode_CheckedChanged;
            m_rbExternal.CheckedChanged += m_rbIntrMode_CheckedChanged;
            m_rbInternal.CheckedChanged += m_rbIntrMode_CheckedChanged;

            m_numAddress.TextChanged += m_numAddress_TextChanged;
            m_numAddressMask.TextChanged += m_numAddress_TextChanged;
            // Flow Control events
            m_chbRts.CheckedChanged += m_chb_CheckedChanged;
            m_chbCts.CheckedChanged += m_chb_CheckedChanged;
            m_cbRtsPolarity.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbCtsPolarity.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_numRtsRxFifoTrigger.TextChanged += m_numRtsRxFifoTrigger_TextChanged;
            m_params.ScbModeChanged += m_params_ScbModeChanged;

            m_chbSmartioEnable.CheckedChanged += m_chb_CheckedChanged;
            #endregion

            #region Initialize numerics
            m_numRXBufferSize.Maximum = decimal.MaxValue;
            m_numRXBufferSize.Minimum = 0;

            m_numTXBufferSize.Maximum = decimal.MaxValue;
            m_numTXBufferSize.Minimum = 0;

            m_numAddress.Maximum = decimal.MaxValue;
            m_numAddress.Minimum = 0;

            m_numAddressMask.Maximum = decimal.MaxValue;
            m_numAddressMask.Minimum = 0;
            #endregion

            m_params.UartModeChanged += delegate
            {
                UpdateSmartIoSupportVisibility();
            }; 
            m_params.UartWakeupChanged += delegate
            {
                UpdateSmartIoSupportVisibility();
            };
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            // Buffer sizes
            m_numRXBufferSize.Text = m_params.UART_RxBufferSize.ToString();
            m_numTXBufferSize.Text = m_params.UART_TxBufferSize.ToString();
            m_chbByteMode.Checked = m_params.UART_EnableByteMode;

            // DMA
            m_chbRxOutput.Checked = m_params.UART_RxOutput;
            m_chbTxOutput.Checked = m_params.UART_TxOutput;

            // SmartIO
            m_chbSmartioEnable.Checked = m_params.UART_SmartioEnable;

            // Interrupt sources
            m_chbInterruptUARTDone.Checked = m_params.UART_InterruptOnUARTDone;
            m_chbInterruptTXNotFull.Checked = m_params.UART_InterruptOnTXFIFONotFull;
            m_chbInterruptTXEmpty.Checked = m_params.UART_InterruptOnTXFIFOEmpty;
            m_chbInterruptTXOverflow.Checked = m_params.UART_InterruptOnTXFIFOOverflow;
            m_chbInterruptTXUnderflow.Checked = m_params.UART_InterruptOnTXFIFOUnderflow;
            m_chbInterruptTXLostArb.Checked = m_params.UART_InterruptOnTXLostArbitration;
            m_chbInterruptTxNack.Checked = m_params.UART_InterruptOnTXNACK;
            m_chbInterruptTXTrigger.Checked = m_params.UART_InterruptOnTXFIFOTrigger;

            m_cbTXTriggerLevel.SelectedIndex = m_params.UART_TXTriggerLevel;

            m_chbInterruptRXFull.Checked = m_params.UART_InterruptOnRXFIFOFull;
            m_chbInterruptRXNotEmpty.Checked = m_params.UART_InterruptOnRXFIFONotEmpty;
            m_chbInterruptRXOverflow.Checked = m_params.UART_InterruptOnRXFIFOOverflow;
            m_chbInterruptRXUnderflow.Checked = m_params.UART_InterruptOnRXFIFOUnderflow;
            m_chbInterruptRXFrameErr.Checked = m_params.UART_InterruptOnRXFrameError;
            m_chbInterruptRXParityErr.Checked = m_params.UART_InterruptOnRXParityError;
            m_chbInterruptRXTrigger.Checked = m_params.UART_InterruptOnRXFIFOTrigger;

            m_cbRXTriggerLevel.SelectedIndex = m_params.UART_RXTriggerLevel;

            // Interrupt connections
            switch (m_params.UART_InterruptMode)
            {
                case CyEInterruptModeType.INTERRUPT_NONE:
                    m_rbNone.Checked = true;
                    break;
                case CyEInterruptModeType.EXTERNAL:
                    m_rbExternal.Checked = true;
                    break;
                case CyEInterruptModeType.INTERNAL:
                    m_rbInternal.Checked = true;
                    break;
            }

            // Flow Control
            m_chbRts.Checked = m_params.UART_EnableRtsPin;
            m_chbCts.Checked = m_params.UART_EnableCtsPin;
            m_cbRtsPolarity.SelectedItem = m_params.UartRtsPolarity.Description;
            m_cbCtsPolarity.SelectedItem = m_params.UartCtsPolarity.Description;
            m_numRtsRxFifoTrigger.Text = m_params.UART_RtsTriggerLevel.ToString();

            // Multiprocessor mode
            m_chbEnMultiProcMode.Checked = m_params.UART_MultiProcessorModeEnabled;
            m_numAddress.Text = m_params.UART_MultiProcessorAddress.ToString("X2");
            m_numAddressMask.Text = m_params.UART_MultiProcessorAddressMask.ToString("X2");
            m_chbAcceptAddress.Checked = m_params.UART_MultiProcessorAcceptAddress;

            // RX FIFO Drop
            m_chbDropOnParityError.Checked = m_params.UART_RXFIFODropOnParityError;
            m_chbDropOnFrameError.Checked = m_params.UART_RXFIFODropOnFrameError;

            // Update controls' state
            UpdateSmartIoSupportVisibility();
            UpdateBuffersSize();
            UpdateByteModeCheckboxState();
            UpdateRXFrameErrorIntr();
            UpdateInterruptConnection();
            UpdateInterruptSources();
            UpdateMultiprocessorMode();
            UpdateRXFIFODrop();
            UpdateControlFlowState();
            UpdateDmaSettingsState();

            // Validate RX TX buffers values, because for CCG3 the default values are wrong
            UpdateRxTxBuffersValidations();
        }

        public void ValidateTab()
        {
            m_numBufferSize_TextChanged(m_numRXBufferSize, null);
            m_numBufferSize_TextChanged(m_numTXBufferSize, null);
            UpdateInterruptSources();
            UpdateInterruptConnection();
            UpdateTriggerLevelRange(m_cbRXTriggerLevel);
            UpdateTriggerLevelRange(m_cbTXTriggerLevel);
            m_cbTriggerLevel_Validating(m_cbRXTriggerLevel, null);
            m_cbTriggerLevel_Validating(m_cbTXTriggerLevel, null);
            UpdateControlFlowState();
        }

        private void UpdateSmartIoSupportVisibility()
        {
            if (!m_params.IsSmartioCapable)
            {
                if (m_chbSmartioEnable.Checked)
                {
                    m_errorProvider.SetError(m_chbSmartioEnable, Resources.SmartioSupportError);
                    m_chbSmartioEnable.Enabled = true;
                }
                else
                {
                    m_errorProvider.SetError(m_chbSmartioEnable, string.Empty);
                    m_chbSmartioEnable.Enabled = false;
                }
            }
            else
            {
                if (m_params.UART_SmartioEnable && m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD)
                {
                    m_errorProvider.SetError(m_chbSmartioEnable, Resources.SmartioSupportSmartCardError);
                }
                else
                {
                    m_errorProvider.SetError(m_chbSmartioEnable, string.Empty);
                }

                if (String.IsNullOrEmpty(m_errorProvider.GetError(m_chbSmartioEnable)))
                {
                    if(m_params.UART_SmartioEnable && m_params.UART_WakeupFromSleepEnabled)
                    {
                        m_errorProvider.SetError(m_chbSmartioEnable, Resources.SmartIoWakeUpError);
                    }
                    else
                    {
                        m_errorProvider.SetError(m_chbSmartioEnable, string.Empty);
                    }
                }
            }
        }

        private void UpdateTriggerLevelRange(object sender)
        {
            ComboBox currentComboBox = sender as ComboBox;
            byte currentTriggerLevel = 0;
            byte maxTriggerLevel = m_params.UartMaxTriggerLevel;

            if (currentComboBox == m_cbRXTriggerLevel)
            {
                currentTriggerLevel = m_params.UART_RXTriggerLevel;
            }
            if (currentComboBox == m_cbTXTriggerLevel)
            {
                currentTriggerLevel = m_params.UART_TXTriggerLevel;
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

        private void UpdateBuffersSize()
        {
            m_numTXBufferSize.Enabled = m_params.UartDirection.Value != CyEUARTDirectionType.RX;
            m_lblTXBufferSize.Enabled = m_params.UartDirection.Value != CyEUARTDirectionType.RX;

            m_numRXBufferSize.Enabled = m_params.UartDirection.Value != CyEUARTDirectionType.TX;
            m_lblRXBufferSize.Enabled = m_params.UartDirection.Value != CyEUARTDirectionType.TX;
        }

        private void UpdateByteModeCheckboxState()
        {
            m_chbByteMode.Enabled = m_params.IsScbIPV2 || m_params.UART_EnableByteMode;

            if (!m_params.IsScbIPV2 && m_params.UART_EnableByteMode)
            {
                m_errorProvider.SetError(m_chbByteMode, Resources.ByteModeError);
            }
            else if (m_params.IsScbIPV2 && m_params.UART_EnableByteMode)
            {
                if (m_params.UartConfigTab != null)
                {
                    bool validByteModeValue = m_params.UartConfigTab.ValidateDataBitsVsByteMode();
                    m_errorProvider.SetError(m_chbByteMode, validByteModeValue ?
                        String.Empty : Resources.ByteModeDataBitsErrorAdv);
                }
            }
            else
            {
                m_errorProvider.SetError(m_chbByteMode, String.Empty);
            }
        }

        private void UpdateRXFrameErrorIntr()
        {
            m_chbInterruptRXFrameErr.Enabled = (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.TX);
        }

        private void UpdateInterruptConnection()
        {
            bool bufSizeOverflow = (m_params.UART_RxBufferSize > m_params.UartRxBufferMinSize) ||
                (m_params.UART_TxBufferSize > m_params.UartTxBufferMinSize);

            m_rbNone.Enabled = bufSizeOverflow == false;

            m_rbExternal.Visible = !m_params.InstQuery.IsInSystemBuilder;
            m_rbExternal.Enabled = bufSizeOverflow == false;
        }

        private void UpdateMultiprocessorMode()
        {
            bool enabled = (m_params.UartNumberDataBits.Value == CyEUARTNumberDataBitsType.NINE) &&
                (m_params.UartSubMode.Value == CyEUARTSubModeType.STANDARD) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.TX);
            bool multiprocModeEnabled = enabled && m_params.UART_MultiProcessorModeEnabled;

            m_chbEnMultiProcMode.Enabled = enabled;

            m_lblAddress.Enabled = multiprocModeEnabled;
            m_numAddress.Enabled = multiprocModeEnabled;
            m_lblMask.Enabled = multiprocModeEnabled;
            m_numAddressMask.Enabled = multiprocModeEnabled;
            m_chbAcceptAddress.Enabled = multiprocModeEnabled;
        }

        private void UpdateRXFIFODrop()
        {
            bool dropOnParityEnable = m_params.UartParityType.Value != CyEUARTParityType.PARITY_NONE &&
                                      m_params.UartDirection.Value != CyEUARTDirectionType.TX;
            bool dropOnFrameEnable = m_params.UartDirection.Value != CyEUARTDirectionType.TX;

            m_grpRxFifoDrop.Enabled = (dropOnParityEnable || dropOnFrameEnable);

            m_chbDropOnParityError.Enabled = dropOnParityEnable;
            m_chbDropOnFrameError.Enabled = dropOnFrameEnable;

            UpdateRXParityFrameInterrupts();
        }

        private void UpdateRXParityFrameInterrupts()
        {
            bool dropOnParityEnable = (m_params.UartParityType.Value != CyEUARTParityType.PARITY_NONE) &&
                                      (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                                      (m_params.UartDirection.Value != CyEUARTDirectionType.TX);

            m_chbInterruptRXParityErr.Enabled = dropOnParityEnable;
        }

        private void UpdateInterruptSources()
        {
            bool interruptEnabled = m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE;
            bool txIntrEnabled = interruptEnabled && m_params.UartDirection.Value != CyEUARTDirectionType.RX;
            bool rxIntrEnabled = interruptEnabled && m_params.UartDirection.Value != CyEUARTDirectionType.TX;

            m_grpIntrSources.Enabled = interruptEnabled;

            foreach (CheckBox txSource in m_txSources)
            {
                txSource.Enabled = txIntrEnabled;
            }

            foreach (CheckBox rxSource in m_rxSources)
            {
                rxSource.Enabled = rxIntrEnabled;
            }

            UpdateTXSmartCardInterrupts();
            UpdateRXNotEmptyInterrupt();
            UpdateTXNotFullInterrupt();
            UpdateRXParityFrameInterrupts();
        }

        private void UpdateRXNotEmptyInterrupt()
        {
            if (m_params.UART_EnableByteMode && m_params.UART_RxBufferSize == m_params.UartRxBufferMinSize)
            {
                m_chbInterruptRXNotEmpty.Checked = false;
            }

            m_chbInterruptRXNotEmpty.Enabled =
                (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.TX) &&
                (m_params.UART_RxBufferSize <= m_params.UartRxBufferMinSize);
        }

        private void UpdateTXNotFullInterrupt()
        {
            m_chbInterruptTXNotFull.Enabled =
                (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.RX) &&
                (m_params.UART_TxBufferSize <= m_params.UartTxBufferMinSize);
        }

        private void UpdateTXSmartCardInterrupts()
        {
            if ((m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.RX) &&
                (m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD))
            {
                m_chbInterruptTXLostArb.Enabled = true;
                m_chbInterruptTxNack.Enabled = true;
            }
            else
            {
                m_chbInterruptTXLostArb.Enabled = false;
                m_chbInterruptTxNack.Enabled = false;
            }
        }

        public void UpdateDmaSettingsState()
        {
            CyEUARTDirectionType direction = m_params.UartDirection.Value;

            // Turn off RX TX outputs if they are not selected by direction parameter
            if (m_params.UART_RxOutput && direction == CyEUARTDirectionType.TX)
                m_chbRxOutput.Checked = false;
            if (m_params.UART_TxOutput && direction == CyEUARTDirectionType.RX)
                m_chbTxOutput.Checked = false;

            // Handle error provider
            bool isRxFifoUsed = m_params.UART_RxBufferSize <= m_params.UartRxBufferMinSize;
            bool isTxFifoUsed = m_params.UART_TxBufferSize <= m_params.UartTxBufferMinSize;
            ClearNotifications(m_chbRxOutput);
            ClearNotifications(m_chbTxOutput);
            if (m_params.UART_RxOutput && isRxFifoUsed == false)
                m_errorProvider.SetError(m_chbRxOutput, Resources.DMAFifoNotUsedError);
            if (m_params.UART_TxOutput && isTxFifoUsed == false)
                m_errorProvider.SetError(m_chbTxOutput, Resources.DMAFifoNotUsedError);

            // Enable/Disable controls
            bool isRxOutputEnabled = direction != CyEUARTDirectionType.TX && isRxFifoUsed || m_params.UART_RxOutput;
            bool isTxOutputEnabled = direction != CyEUARTDirectionType.RX && isTxFifoUsed || m_params.UART_TxOutput;

            if (m_params.IsDmaCapable == false)
            {
                isRxOutputEnabled = false;
                isTxOutputEnabled = false;

                if (m_params.UART_RxOutput)
                {
                    m_errorProvider.SetError(m_chbRxOutput, Resources.DMASupportError);
                    isRxOutputEnabled = true;
                }

                if (m_params.UART_TxOutput)
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
            bool rxEnabled = m_params.UartDirection.Value != CyEUARTDirectionType.TX &&
                             ((m_params.UART_RxOutput && m_params.UartIsRxFifoUsed) ||
                              (m_params.UART_InterruptOnRXFIFOTrigger || m_params.UART_RxOutput));
            bool txEnabled = m_params.UartDirection.Value != CyEUARTDirectionType.RX &&
                             ((m_params.UART_TxOutput && m_params.UartIsTxFifoUsed) ||
                              (m_params.UART_InterruptOnTXFIFOTrigger || m_params.UART_TxOutput));

            m_panelRxFifoLevel.Enabled = rxEnabled;
            m_panelTxFifoLevel.Enabled = txEnabled;
            m_gbFifoLevels.Enabled = rxEnabled || txEnabled;
        }

        private void UpdateControlFlowState()
        {
            if (m_params.IsRtsPinAllowed)
            {
                m_panelRtsControlFlow.Enabled = m_params.UART_EnableRtsPin;
                m_chbRts.Enabled = true;
                m_errorProvider.SetError(m_chbRts, String.Empty);
            }
            else
            {
                m_panelRtsControlFlow.Enabled = false;
                m_chbRts.Enabled = false;

                if (m_params.UART_EnableRtsPin)
                {
                    m_chbRts.Checked = false;
                    m_params.UART_EnableRtsPin = false;
                }

                m_errorProvider.SetError(m_chbRts, String.Empty);
            }

            if (m_params.IsCtsPinAllowed)
            {
                m_panelCtsControlFlow.Enabled = m_params.UART_EnableCtsPin;
                m_chbCts.Enabled = true;
                m_errorProvider.SetError(m_chbCts, String.Empty);
            }
            else
            {
                m_panelCtsControlFlow.Enabled = false;
                m_chbCts.Enabled = false;

                if (m_params.UART_EnableCtsPin)
                {
                    m_chbCts.Checked = false;
                    m_params.UART_EnableCtsPin = false;
                }

                m_errorProvider.SetError(m_chbCts, String.Empty);
            }

            m_grpControlFlow.Enabled = (m_params.IsRtsPinAllowed || m_params.IsCtsPinAllowed) ||
                (m_params.UART_EnableRtsPin || m_params.UART_EnableCtsPin);

            m_numRtsRxFifoTrigger_TextChanged(m_numRtsRxFifoTrigger, null);
        }

        private void ResetTXBufferSize()
        {
            if (m_params.UartDirection.Value == CyEUARTDirectionType.RX)
            {
                m_numTXBufferSize.Text = m_params.UartTxBufferMinSize.ToString();
            }
            UpdateBuffersSize();
        }

        private void ResetRXBufferSize()
        {
            if (m_params.UartDirection.Value == CyEUARTDirectionType.TX)
            {
                m_numRXBufferSize.Text = m_params.UartRxBufferMinSize.ToString();
            }
            UpdateBuffersSize();
        }

        private void ResetInterruptConnection()
        {
            if ((m_params.UART_RxBufferSize > m_params.UartRxBufferMinSize) ||
                (m_params.UART_TxBufferSize > m_params.UartTxBufferMinSize) ||
                (m_params.UART_InterruptMode == CyEInterruptModeType.INTERNAL))
            {
                m_rbInternal.Checked = true;
            }

            UpdateInterruptConnection();
        }

        private void ResetMultiprocessorMode()
        {
            if ((m_params.UartNumberDataBits.Value != CyEUARTNumberDataBitsType.NINE) ||
                (m_params.UartSubMode.Value != CyEUARTSubModeType.STANDARD) ||
                (m_params.UartDirection.Value == CyEUARTDirectionType.TX))
            {
                m_chbEnMultiProcMode.Checked = false;
            }
            if (m_params.UART_MultiProcessorModeEnabled == false)
            {
                m_chbAcceptAddress.Checked = false;
            }

            UpdateMultiprocessorMode();
        }

        private void ResetRXFIFODrop()
        {
            if (m_params.UartParityType.Value == CyEUARTParityType.PARITY_NONE ||
                m_params.UartDirection.Value == CyEUARTDirectionType.TX)
            {
                m_chbDropOnParityError.Checked = false;
                m_chbInterruptRXParityErr.Checked = false;
            }

            if (m_params.UartNumberStopBits.Value == CyEUARTNumberStopBitsType.ONE_BIT ||
                m_params.UartDirection.Value == CyEUARTDirectionType.TX)
            {
                m_chbDropOnFrameError.Checked = false;
                m_chbInterruptRXFrameErr.Checked = false;
            }

            UpdateRXFIFODrop();
        }

        private void ResetInterruptSources()
        {
            if (m_params.GlobalEditMode)
            {
                if ((m_params.UART_InterruptMode == CyEInterruptModeType.INTERRUPT_NONE) ||
                    (m_params.UartDirection.Value == CyEUARTDirectionType.RX))
                {
                    foreach (CheckBox txSource in m_txSources)
                    {
                        txSource.Checked = false;
                    }
                }
                if ((m_params.UART_InterruptMode == CyEInterruptModeType.INTERRUPT_NONE) ||
                    (m_params.UartDirection.Value == CyEUARTDirectionType.TX))
                {
                    foreach (CheckBox rxSource in m_rxSources)
                    {
                        rxSource.Checked = false;
                    }
                }

                ResetRXNotEmptyInterrupt();
                ResetTXNotFullInterrupt();
                ResetTXSmartCardInterrupts();
            }

            UpdateInterruptSources();
        }

        private void ResetRXNotEmptyInterrupt()
        {
            if ((m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
               (m_params.UartDirection.Value != CyEUARTDirectionType.TX) &&
               (m_params.UART_RxBufferSize > m_params.UartRxBufferMinSize))
            {
                m_chbInterruptRXNotEmpty.Checked = true;
            }
            else if ((m_params.UART_InterruptMode == CyEInterruptModeType.INTERRUPT_NONE) ||
                     (m_params.UartDirection.Value == CyEUARTDirectionType.TX))
            {
                m_chbInterruptRXNotEmpty.Checked = false;
            }

            UpdateRXNotEmptyInterrupt();
        }

        private void ResetTXNotFullInterrupt()
        {
            if ((m_params.UART_InterruptMode == CyEInterruptModeType.INTERRUPT_NONE) ||
                (m_params.UartDirection.Value == CyEUARTDirectionType.RX) ||
                (m_params.UART_TxBufferSize > m_params.UartTxBufferMinSize))
            {
                m_chbInterruptTXNotFull.Checked = false;
            }

            UpdateTXNotFullInterrupt();
        }

        private void ResetTXSmartCardInterrupts()
        {
            if ((m_params.UART_InterruptMode == CyEInterruptModeType.INTERRUPT_NONE) ||
                (m_params.UartDirection.Value == CyEUARTDirectionType.RX) ||
                (m_params.UartSubMode.Value != CyEUARTSubModeType.SMART_CARD))
            {
                m_chbInterruptTXLostArb.Checked = false;
                m_chbInterruptTxNack.Checked = false;
            }

            UpdateTXSmartCardInterrupts();
        }

        public void OnModeChanged()
        {
            ResetTXSmartCardInterrupts();
            ResetMultiprocessorMode();
            UpdateControlFlowState();
        }

        public void OnDirectionChanged()
        {
            ResetTXBufferSize();
            ResetRXBufferSize();

            UpdateDmaSettingsState();

            ResetInterruptSources();
            UpdateRXFrameErrorIntr();

            UpdateFifoLevelState();

            ResetMultiprocessorMode();

            UpdateControlFlowState();
            ResetRXFIFODrop();
        }

        public void OnParityTypeChanged()
        {
            ResetRXFIFODrop();
        }

        public void OnDataBitsChanged()
        {
            ResetMultiprocessorMode();
            UpdateByteModeCheckboxState();
        }

        public void OnStopBitsChanged()
        {
            UpdateRXFrameErrorIntr();
            ResetRXFIFODrop();
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
            UpdateBufferValidation(m_numRXBufferSize, m_params.UART_RxBufferSize, m_params.UartRxBufferMinSize);
            UpdateBufferValidation(m_numTXBufferSize, m_params.UART_TxBufferSize, m_params.UartTxBufferMinSize);
        }
        #endregion

        #region Event handlers
        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.UART)
                ShowTab();
            else
                HideTab();
        }

        void m_numBufferSize_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                byte rxBufferMinSize = m_params.UartRxBufferMinSize;
                byte txBufferMinSize = m_params.UartTxBufferMinSize;

                if (sender == m_numRXBufferSize || sender == m_numTXBufferSize)
                {
                    m_errorProvider.SetError(sender as NumericUpDown, string.Empty);

                    UInt32 value;

                    if (UInt32.TryParse((sender as NumericUpDown).Text, out value))
                    {
                        UInt32 minValue = 1;
                        string errorMsg = string.Empty;

                        if (sender == m_numRXBufferSize)
                        {
                            if (value == rxBufferMinSize && m_params.UART_RxBufferSize > value)
                            {
                                m_chbInterruptRXNotEmpty.Checked = false;
                            }

                            m_params.UART_RxBufferSize = value;

                            minValue = rxBufferMinSize;
                            if (value < minValue)
                            {
                                errorMsg = string.Format(Resources.ErrorValueLimitBufferSize, minValue);
                            }
                        }
                        else if (sender == m_numTXBufferSize)
                        {
                            m_params.UART_TxBufferSize = value;

                            minValue = txBufferMinSize;
                            if (value < minValue)
                            {
                                errorMsg = string.Format(Resources.ErrorValueLimitBufferSize, minValue);
                            }
                        }

                        ResetInterruptConnection();
                        ResetInterruptSources();

                        m_errorProvider.SetError(sender as Control, errorMsg);
                    }
                    else
                    {
                        m_errorProvider.SetError(sender as Control, Resources.UARTBufferSizeValueFormatError);
                    }
                }
            }
            UpdateDmaSettingsState();
        }

        void m_numAddress_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_numAddress || sender == m_numAddressMask)
                {
                    try
                    {
                        UInt16 value = Convert.ToUInt16((sender as NumericUpDown).Text, 16);

                        if (sender == m_numAddress)
                        {
                            m_params.UART_MultiProcessorAddress = (byte)value;
                        }
                        else
                        {
                            m_params.UART_MultiProcessorAddressMask = (byte)value;
                        }

                        if (value >= byte.MinValue && value <= byte.MaxValue)
                        {
                            m_errorProvider.SetError(sender as Control, string.Empty);
                        }
                        else
                        {
                            throw new Exception();
                        }
                    }
                    catch
                    {
                        m_errorProvider.SetError(sender as Control, string.Format(Resources.UARTAddressFormatError,
                            byte.MinValue, byte.MaxValue));
                    }
                }
            }
        }

        void m_numRtsRxFifoTrigger_TextChanged(object sender, EventArgs e)
        {
            if (sender == m_numRtsRxFifoTrigger)
            {
                byte rtsRxFifoTrigger;
                byte maxTriggerLevel = m_params.UartMaxTriggerLevel;
                string errorMessage = String.Format(Resources.RtsRxFifoTriggerOutOfRangeError,
                    CyParamRanges.UART_MIN_TRIGGER_LEVEL, maxTriggerLevel);

                if (Byte.TryParse(m_numRtsRxFifoTrigger.Text, out rtsRxFifoTrigger))
                {
                    if (rtsRxFifoTrigger >= CyParamRanges.UART_MIN_TRIGGER_LEVEL &&
                        rtsRxFifoTrigger <= maxTriggerLevel)
                    {
                        errorMessage = String.Empty; // input value is valid
                    }

                    m_params.UART_RtsTriggerLevel = rtsRxFifoTrigger;
                }

                // Don't show error message if control is disabled
                if (m_numRtsRxFifoTrigger.Enabled == false)
                    errorMessage = String.Empty;

                m_errorProvider.SetError(m_numRtsRxFifoTrigger, errorMessage);
            }
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                // Interrupts
                if (sender == m_chbInterruptUARTDone)
                {
                    m_params.UART_InterruptOnUARTDone = m_chbInterruptUARTDone.Checked;
                }
                else if (sender == m_chbInterruptTXNotFull)
                {
                    m_params.UART_InterruptOnTXFIFONotFull = m_chbInterruptTXNotFull.Checked;
                }
                else if (sender == m_chbInterruptTXEmpty)
                {
                    m_params.UART_InterruptOnTXFIFOEmpty = m_chbInterruptTXEmpty.Checked;
                }
                else if (sender == m_chbInterruptTXOverflow)
                {
                    m_params.UART_InterruptOnTXFIFOOverflow = m_chbInterruptTXOverflow.Checked;
                }
                else if (sender == m_chbInterruptTXUnderflow)
                {
                    m_params.UART_InterruptOnTXFIFOUnderflow = m_chbInterruptTXUnderflow.Checked;
                }
                else if (sender == m_chbInterruptTXLostArb)
                {
                    m_params.UART_InterruptOnTXLostArbitration = m_chbInterruptTXLostArb.Checked;
                }
                else if (sender == m_chbInterruptTxNack)
                {
                    m_params.UART_InterruptOnTXNACK = m_chbInterruptTxNack.Checked;
                }
                else if (sender == m_chbInterruptTXTrigger)
                {
                    m_params.UART_InterruptOnTXFIFOTrigger = m_chbInterruptTXTrigger.Checked;
                    m_cbTriggerLevel_Validating(m_cbTXTriggerLevel, null);
                    UpdateFifoLevelState();
                }
                else if (sender == m_chbInterruptRXFull)
                {
                    m_params.UART_InterruptOnRXFIFOFull = m_chbInterruptRXFull.Checked;
                }
                else if (sender == m_chbInterruptRXNotEmpty)
                {
                    m_params.UART_InterruptOnRXFIFONotEmpty = m_chbInterruptRXNotEmpty.Checked;
                }
                else if (sender == m_chbInterruptRXOverflow)
                {
                    m_params.UART_InterruptOnRXFIFOOverflow = m_chbInterruptRXOverflow.Checked;
                }
                else if (sender == m_chbInterruptRXUnderflow)
                {
                    m_params.UART_InterruptOnRXFIFOUnderflow = m_chbInterruptRXUnderflow.Checked;
                }
                else if (sender == m_chbInterruptRXFrameErr)
                {
                    m_params.UART_InterruptOnRXFrameError = m_chbInterruptRXFrameErr.Checked;
                }
                else if (sender == m_chbInterruptRXParityErr)
                {
                    m_params.UART_InterruptOnRXParityError = m_chbInterruptRXParityErr.Checked;
                }
                else if (sender == m_chbInterruptRXTrigger)
                {
                    m_params.UART_InterruptOnRXFIFOTrigger = m_chbInterruptRXTrigger.Checked;
                    m_cbTriggerLevel_Validating(m_cbRXTriggerLevel, null);
                    UpdateFifoLevelState();
                }
                // Multi processor mode
                else if (sender == m_chbEnMultiProcMode)
                {
                    m_params.UART_MultiProcessorModeEnabled = m_chbEnMultiProcMode.Checked;
                    ResetMultiprocessorMode();
                }
                // RX FIFO Drop
                else if (sender == m_chbDropOnFrameError)
                {
                    m_params.UART_RXFIFODropOnFrameError = m_chbDropOnFrameError.Checked;
                }
                else if (sender == m_chbDropOnParityError)
                {
                    m_params.UART_RXFIFODropOnParityError = m_chbDropOnParityError.Checked;
                }
                else if (sender == m_chbAcceptAddress)
                {
                    m_params.UART_MultiProcessorAcceptAddress = m_chbAcceptAddress.Checked;
                }
                // Control flow
                else if (sender == m_chbRts)
                {
                    m_params.UART_EnableRtsPin = m_chbRts.Checked;

                    // Reset RX FIFO trigger to default
                    if (m_params.UART_EnableRtsPin == false)
                        m_numRtsRxFifoTrigger.Text = CyParamRanges.UART_TRIGGER_LEVEL_DEFAULT.ToString();

                    UpdateControlFlowState();
                }
                else if (sender == m_chbCts)
                {
                    m_params.UART_EnableCtsPin = m_chbCts.Checked;
                    UpdateControlFlowState();
                }
                else if (sender == m_chbByteMode)
                {
                    m_params.UART_EnableByteMode = m_chbByteMode.Checked;

                    UpdateByteModeCheckboxState();
                    ResetRXBufferSize();
                    ResetTXBufferSize();

                    if (m_params.UartConfigTab != null)
                        m_params.UartConfigTab.ValidateDataBitsVsByteMode();
                    ValidateTab();
                }
                else if (sender == m_chbRxOutput)
                {
                    m_params.UART_RxOutput = m_chbRxOutput.Checked;
                    m_cbTriggerLevel_Validating(m_cbRXTriggerLevel, null);
                    UpdateDmaSettingsState();
                }
                else if (sender == m_chbTxOutput)
                {
                    m_params.UART_TxOutput = m_chbTxOutput.Checked;
                    m_cbTriggerLevel_Validating(m_cbTXTriggerLevel, null);
                    UpdateDmaSettingsState();
                }
                else if (sender == m_chbSmartioEnable)
                {
                    m_params.UART_SmartioEnable = m_chbSmartioEnable.Checked;
                    UpdateSmartIoSupportVisibility();
                    m_params.OnUartSmartIoSupportChanged(sender, e);
                }
            }
        }

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbRXTriggerLevel)
                {
                    m_params.UART_RXTriggerLevel = (byte)m_cbRXTriggerLevel.SelectedIndex;
                }
                else if (sender == m_cbTXTriggerLevel)
                {
                    m_params.UART_TXTriggerLevel = (byte)m_cbTXTriggerLevel.SelectedIndex;
                }
                else if (sender == m_cbRtsPolarity)
                {
                    m_params.UartRtsPolarity.Description = m_cbRtsPolarity.Text;
                }
                else if (sender == m_cbCtsPolarity)
                {
                    m_params.UartCtsPolarity.Description = m_cbCtsPolarity.Text;
                }

                if (sender == m_cbRXTriggerLevel || sender == m_cbTXTriggerLevel)
                {
                    if (String.IsNullOrEmpty(m_errorProvider.GetError(sender as Control)) == false)
                    {
                        if (m_triggerLevelUpdateLocked == false)
                            UpdateTriggerLevelRange(sender);
                    }

                    m_cbTriggerLevel_Validating(sender, null);
                }
            }
        }

        void m_rbIntrMode_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (m_rbNone.Checked)
                {
                    m_params.UART_InterruptMode = CyEInterruptModeType.INTERRUPT_NONE;
                }
                else if (m_rbExternal.Checked)
                {
                    m_params.UART_InterruptMode = CyEInterruptModeType.EXTERNAL;
                }
                else if (m_rbInternal.Checked)
                {
                    m_params.UART_InterruptMode = CyEInterruptModeType.INTERNAL;
                }
            }

            ResetInterruptSources();

            if (m_params.UartConfigTab != null)
            {
                m_params.UartConfigTab.UpdateEnableWakeup();
            }
        }

        void m_cbTriggerLevel_Validating(object sender, CancelEventArgs e)
        {
            ComboBox currentComboBox = sender as ComboBox;
            byte currentTriggerLevel = 0;
            byte maxTriggerLevel = m_params.UartMaxTriggerLevel;
            bool fifoLevelEnabled = false;

            if (sender == m_cbRXTriggerLevel)
            {
                currentTriggerLevel = m_params.UART_RXTriggerLevel;
                fifoLevelEnabled = m_params.UART_InterruptOnRXFIFOTrigger || m_params.UART_RxOutput;
            }
            else if (sender == m_cbTXTriggerLevel)
            {
                currentTriggerLevel = m_params.UART_TXTriggerLevel;
                fifoLevelEnabled = m_params.UART_InterruptOnTXFIFOTrigger || m_params.UART_TxOutput;
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
