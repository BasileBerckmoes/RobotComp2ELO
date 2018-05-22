/*******************************************************************************
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections.Generic;

namespace SCB_P4_v3_20
{
    public partial class CyUARTConfigureTab : CyTabControlWrapper
    {
        #region Auxiliary data
        readonly UInt32[] IRDA_DATA_RATES_LIST = new UInt32[]
        {
            1200,
            2400,
            9600,
            19200,
            38400,
            57600,
            115200
        };

        readonly UInt16[] IRDA_OVS_FACTOR_LIST = new UInt16[]
        {
            1536,
            768,
            192,
            96,
            48,
            32,
            16
        };

        readonly UInt32[] DATA_RATES_LIST = new UInt32[]
        {
            110,
            300,
            1200,
            2400,
            4800,
            9600,
            19200,
            38400,
            57600,
            115200,
            230400,
            460800,
            921600
        };
        #endregion

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get { return "UART Basic"; }
        }

        public override string TabDisplayName
        {
            get { return Resources.UARTConfigTabDisplayName; }
        }
        #endregion

        #region Constructor(s)
        public CyUARTConfigureTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            m_params = parameters;
            m_params.UartConfigTab = this;

            InitializeComponent();

            #region Add items to comboboxes
            m_cbMode.Items.AddRange(m_params.UartSubMode.EnumDescriptionsList);
            m_cbDirection.Items.AddRange(m_params.UartDirection.EnumDescriptionsList);
            m_cbDataBits.Items.AddRange(m_params.UartNumberDataBits.EnumDescriptionsList);
            m_cbParityType.Items.AddRange(m_params.UartParityType.EnumDescriptionsList);
            m_cbStopBits.Items.AddRange(m_params.UartNumberStopBits.EnumDescriptionsList);
            UpdateBaudRateList();
            #endregion

            #region Add event handlers
            m_cbMode.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbDirection.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbDataBits.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbParityType.SelectedIndexChanged += m_cb_SelectedIndexChanged;
            m_cbStopBits.SelectedIndexChanged += m_cb_SelectedIndexChanged;

            m_cbBaudRate.TextChanged += m_cb_TextChanged;

            m_numOversamplingFactor.TextChanged += m_num_TextChanged;

            m_chbEnableMedianFilter.CheckedChanged += m_chb_CheckedChanged;
            m_chbRetryOnNack.CheckedChanged += m_chb_CheckedChanged;
            m_chbInvertRx.CheckedChanged += m_chb_CheckedChanged;
            m_chbEnableWakeup.CheckedChanged += m_chb_CheckedChanged;
            m_chbLowPowerReceive.CheckedChanged += m_chb_CheckedChanged;
            m_chbClockFromTerminal.Enabled = !m_params.InstQuery.IsInSystemBuilder;
            m_chbClockFromTerminal.CheckedChanged += m_chb_CheckedChanged;
            m_params.ScbModeChanged += m_params_ScbModeChanged;
            m_params.DesignUpdates += m_params_DesignUpdates;
            #endregion

            if (m_params.InstQuery.IsInSystemBuilder)
            {
                HideClockFromTerminal();
            }

            m_params.UartSmartIoSupportChanged += delegate
            {
                UpdateWakeupValidation();
                UpdateModeValidation();
            };
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            m_cbMode.SelectedItem = m_params.UartSubMode.Description;
            m_cbDirection.SelectedItem = m_params.UartDirection.Description;
            m_cbBaudRate.Text = m_params.UART_DataRate.ToString();
            m_cbDataBits.SelectedItem = m_params.UartNumberDataBits.Description;
            m_cbParityType.SelectedItem = m_params.UartParityType.Description;
            m_cbStopBits.SelectedItem = m_params.UartNumberStopBits.Description;

            m_numOversamplingFactor.Text = m_params.UART_OvsFactor.ToString();

            m_chbClockFromTerminal.Checked = m_params.UART_ClockFromTerminal;
            m_chbRetryOnNack.Checked = m_params.UART_RetryOnNACK;
            m_chbEnableMedianFilter.Checked = m_params.UART_MedianFilterEnabled;
            m_chbInvertRx.Checked = m_params.UART_InvertRXProperty;
            m_chbEnableWakeup.Checked = m_params.UART_WakeupFromSleepEnabled;
            m_chbLowPowerReceive.Checked = m_params.UART_LowPowerReceive;

            UpdateMedianFilter();
            UpdateRetryOnNACK();
            UpdateInvertRX();
            UpdateEnableWakeup();
            UpdateLowPowerEnable();

            UpdateOvsFactor();

            UpdateDirection();
            UpdateParityType();
            UpdateStopBitEnable();

            UpdateClock();
        }

        #region Updating comboboxes' state
        private void UpdateDirection()
        {
            if ((m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD) ||
                (m_params.UART_LowPowerReceive == true))
            {
                m_cbDirection.Enabled = false;
            }
            else
            {
                m_cbDirection.Enabled = true;
            }
        }

        private void ResetDirection()
        {
            if (m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD)
            {
                m_cbDirection.SelectedItem = m_params.UartDirection.GetDescription(CyEUARTDirectionType.TX_RX);
            }
            else if (m_params.UART_LowPowerReceive == true)
            {
                m_cbDirection.SelectedItem = m_params.UartDirection.GetDescription(CyEUARTDirectionType.RX);
            }

            UpdateDirection();
        }

        // Baud rate
        private void UpdateBaudRateList()
        {
            m_cbBaudRate.Items.Clear();

            uint[] baudRates = (m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA) ? IRDA_DATA_RATES_LIST :
                DATA_RATES_LIST;

            foreach (UInt32 rate in baudRates)
            {
                m_cbBaudRate.Items.Add(rate);
            }
            m_cbBaudRate.Text = m_params.UART_DataRate.ToString();

            m_cb_TextChanged(m_cbBaudRate, null);
        }

        // Data bits
        private void ResetDataBits()
        {
            string nineBits = m_params.UartNumberDataBits.GetDescription(CyEUARTNumberDataBitsType.NINE);

            if (m_params.UartSubMode.Value != CyEUARTSubModeType.STANDARD)
            {
                if (m_params.UartNumberDataBits.Value == CyEUARTNumberDataBitsType.NINE)
                {
                    m_errorProvider.SetError(m_cbDataBits, string.Format(Resources.UARTDataBitsValueError, nineBits));
                }
                else
                {
                    m_errorProvider.SetError(m_cbDataBits, string.Empty);
                    if (m_cbDataBits.Items.Contains(nineBits))
                    {
                        m_cbDataBits.Items.Remove(nineBits);
                    }
                }
            }
            else
            {
                if (!m_cbDataBits.Items.Contains(nineBits))
                {
                    m_cbDataBits.Items.Add(nineBits);
                }
                else
                {
                    m_errorProvider.SetError(m_cbDataBits, string.Empty);
                }
            }
        }

        // Parity
        private void UpdateParityType()
        {
            m_cbParityType.Enabled = (m_params.UartSubMode.Value == CyEUARTSubModeType.STANDARD) &&
                (m_params.UartNumberDataBits.Value != CyEUARTNumberDataBitsType.NINE);

            if (m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD)
            {
                m_cbParityType.SelectedItem = m_params.UartParityType.GetDescription(CyEUARTParityType.EVEN);
            }
            else if ((m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA) ||
                     (m_params.UartNumberDataBits.Value == CyEUARTNumberDataBitsType.NINE))
            {
                m_cbParityType.SelectedItem = m_params.UartParityType.GetDescription(CyEUARTParityType.PARITY_NONE);
            }
        }

        // StopBit enable/disable
        private void UpdateStopBitEnable()
        {
            // In SmartCard mode StopBits should be equal 2.
            if (m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD)
            {
                if (m_params.GlobalEditMode ||
                    m_params.UartNumberStopBits.Value == CyEUARTNumberStopBitsType.TWO_BITS)
                {
                    m_cbStopBits.Enabled = false;
                    m_params.UartNumberStopBits.Value = CyEUARTNumberStopBitsType.TWO_BITS;
                    m_cbStopBits.SelectedItem = m_params.UartNumberStopBits.
                        GetDescription(CyEUARTNumberStopBitsType.TWO_BITS);
                }
            }
            else
            {
                m_cbStopBits.Enabled = true;
            }

            // Error provider
            if ((m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD) &&
                (m_params.UartNumberStopBits.Value != CyEUARTNumberStopBitsType.TWO_BITS))
            {
                m_errorProvider.SetError(m_cbStopBits, Resources.UARTStopBitsSmartCardError);
                m_cbStopBits.Enabled = true;
            }
            else
            {
                m_errorProvider.SetError(m_cbStopBits, string.Empty);
            }
        }
        #endregion

        #region Updating checkboxes' state
        // Clock from terminal - no need

        // Median filter
        private void UpdateMedianFilter()
        {
            // Enabled
            m_chbEnableMedianFilter.Enabled = (m_params.UartSubMode.Value != CyEUARTSubModeType.IRDA) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.TX);

            // Checked
            if (m_params.UartDirection.Value == CyEUARTDirectionType.TX)
            {
                m_chbEnableMedianFilter.Checked = false;
            }
            else if (m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA)
            {
                m_chbEnableMedianFilter.Checked = true;
            }
        }

        // Retry on NACK
        private void UpdateRetryOnNACK()
        {
            if (m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD)
            {
                m_chbRetryOnNack.Enabled = true;
            }
            else
            {
                m_chbRetryOnNack.Enabled = false;
                m_chbRetryOnNack.Checked = false;
            }
        }

        // Inverting RX
        private void UpdateInvertRX()
        {
            if ((m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.TX))
            {
                m_chbInvertRx.Enabled = true;
            }
            else
            {
                m_chbInvertRx.Enabled = false;
                m_chbInvertRx.Checked = false;
            }
        }

        // Enable wakeup from Sleep Mode
        public void UpdateEnableWakeup()
        {
            if ((m_params.UartSubMode.Value == CyEUARTSubModeType.STANDARD) &&
                (m_params.UartDirection.Value != CyEUARTDirectionType.TX))
            {
                m_chbEnableWakeup.Enabled = true;
            }
            else
            {
                m_chbEnableWakeup.Enabled = false;
                m_chbEnableWakeup.Checked = false;
            }
        }

        // Low power receiving
        private void UpdateLowPowerEnable()
        {
            if ((m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA) &&
                (m_params.UartDirection.Value == CyEUARTDirectionType.RX))
            {
                m_chbLowPowerReceive.Enabled = true;
            }
            else
            {
                m_chbLowPowerReceive.Enabled = false;
                m_chbLowPowerReceive.Checked = false;
            }
        }
        #endregion

        private void UpdateOvsFactor()
        {
            bool isIrDAMode = m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA;

            if (isIrDAMode)
            {
                m_numOversamplingFactor.Value = CyParamRanges.UART_OVS_FACTOR_MAX;

                if (m_params.UART_LowPowerReceive == true)
                {
                    for (int i = 0; i < IRDA_DATA_RATES_LIST.GetLength(0); i++)
                    {
                        if (IRDA_DATA_RATES_LIST[i] == m_params.UART_DataRate)
                        {
                            m_numOversamplingFactor.Value = IRDA_OVS_FACTOR_LIST[i];
                        }
                    }
                }
            }
            m_numOversamplingFactor.Enabled = !isIrDAMode;

            m_num_TextChanged(m_numOversamplingFactor, null);
        }

        private void HideClockFromTerminal()
        {
            m_chbClockFromTerminal.Visible = false;
            m_backPanel.Top = m_chbClockFromTerminal.Top;
        }

        private void UpdateModeValidation()
        {
            if (m_params.UART_SmartioEnable && m_params.UartSubMode.Value == CyEUARTSubModeType.SMART_CARD)
            {
                m_errorProvider.SetError(m_cbMode, Resources.SmartCardSupportSmartioError);
            }
            else
            {
                m_errorProvider.SetError(m_cbMode, string.Empty);
            }
        }

        private void UpdateWakeupValidation()
        {
            if (m_params.UART_SmartioEnable && m_params.UART_WakeupFromSleepEnabled)
            {
                m_errorProvider.SetError(m_chbEnableWakeup, Resources.WakeUpSmartIoError);
            }
            else
            {
                m_errorProvider.SetError(m_chbEnableWakeup, string.Empty);
            }
        }
        #endregion

        #region Event handlers
        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.UART)
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

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbMode)
                {
                    m_params.UartSubMode.Description = m_cbMode.Text;
                    m_params.OnUartModeChanged(sender, e);

                    UpdateBaudRateList();
                    UpdateOvsFactor();

                    UpdateMedianFilter();
                    UpdateRetryOnNACK();
                    UpdateInvertRX();
                    UpdateEnableWakeup();
                    UpdateLowPowerEnable();
                    UpdateParityType();
                    UpdateStopBitEnable();
                    ResetDataBits();
                    ResetDirection();

                    if (m_params.UartAdvancedTab != null)
                    {
                        m_params.UartAdvancedTab.OnModeChanged();
                    }

                    UpdateModeValidation();
                }
                else if (sender == m_cbDirection)
                {
                    m_params.UartDirection.Description = m_cbDirection.Text;

                    UpdateMedianFilter();
                    UpdateInvertRX();
                    UpdateEnableWakeup();
                    UpdateLowPowerEnable();

                    if (m_params.UartAdvancedTab != null)
                    {
                        m_params.UartAdvancedTab.OnDirectionChanged();
                    }
                }
                else if (sender == m_cbDataBits)
                {
                    m_params.UartNumberDataBits.Description = m_cbDataBits.Text;

                    UpdateParityType();
                    ResetDataBits();
                    ValidateDataBitsVsByteMode();

                    if (m_params.UartAdvancedTab != null)
                    {
                        m_params.UartAdvancedTab.OnDataBitsChanged();
                    }
                }
                else if (sender == m_cbParityType)
                {
                    m_params.UartParityType.Description = m_cbParityType.Text;

                    if (m_params.UartAdvancedTab != null)
                    {
                        m_params.UartAdvancedTab.OnParityTypeChanged();
                    }
                }
                else if (sender == m_cbStopBits)
                {
                    m_params.UartNumberStopBits.Description = m_cbStopBits.Text;
                    UpdateStopBitEnable();

                    if (m_params.UartAdvancedTab != null)
                    {
                        m_params.UartAdvancedTab.OnStopBitsChanged();
                    }
                }
            }
        }

        public bool ValidateDataBitsVsByteMode()
        {
            string message = String.Empty;
            if (m_params.IsScbIPV2 && m_params.UART_EnableByteMode)
            {
                if (m_params.UartNumberDataBits.Value == CyEUARTNumberDataBitsType.NINE)
                {
                    message = String.Format(Resources.ByteModeDataBitsError, CyParamRanges.BYTE_MODE_MAX_DATA_BITS);
                }
            }
            m_errorProvider.SetError(m_cbDataBits, message);
            return String.IsNullOrEmpty(message);
        }

        void m_num_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_numOversamplingFactor)
                {
                    bool skipCheckRange = (m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA &&
                        m_params.UART_LowPowerReceive);

                    UInt16 value;
                    bool parseSuccess = UInt16.TryParse(m_numOversamplingFactor.Text, out value);

                    if (parseSuccess)
                    {
                        m_params.UART_OvsFactor = value;
                        m_params.InternalClockNeedUpdate = true;
                        UpdateClock();
                    }

                    if (parseSuccess && (skipCheckRange ||
                        (value >= CyParamRanges.UART_OVS_FACTOR_MIN && value <= CyParamRanges.UART_OVS_FACTOR_MAX)))
                    {
                        m_errorProvider.SetError(m_numOversamplingFactor, string.Empty);
                    }
                    else
                    {
                        m_errorProvider.SetError(m_numOversamplingFactor, string.Format(Resources.UARTOvsFactorError,
                                CyParamRanges.UART_OVS_FACTOR_MIN, CyParamRanges.UART_OVS_FACTOR_MAX));
                    }
                }
            }
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_chbEnableMedianFilter)
                {
                    m_params.UART_MedianFilterEnabled = m_chbEnableMedianFilter.Checked;
                }
                else if (sender == m_chbRetryOnNack)
                {
                    m_params.UART_RetryOnNACK = m_chbRetryOnNack.Checked;
                }
                else if (sender == m_chbInvertRx)
                {
                    m_params.UART_InvertRXProperty = m_chbInvertRx.Checked;
                }
                else if (sender == m_chbEnableWakeup)
                {
                    m_params.UART_WakeupFromSleepEnabled = m_chbEnableWakeup.Checked;
                    m_params.OnUartWakeupChanged(sender, e);
                    UpdateWakeupValidation();
                }
                else if (sender == m_chbLowPowerReceive)
                {
                    m_params.UART_LowPowerReceive = m_chbLowPowerReceive.Checked;
                    ResetDirection();
                    UpdateOvsFactor();
                }
                else if (sender == m_chbClockFromTerminal)
                {
                    m_params.UART_ClockFromTerminal = m_chbClockFromTerminal.Checked;
                    UpdateClock();
                }
            }
        }

        void m_cb_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbBaudRate)
                {
                    UInt32 value;
                    bool parseSuccess = UInt32.TryParse(m_cbBaudRate.Text, out value);

                    if (parseSuccess && m_params.UART_DataRate != value)
                    {
                        m_params.UART_DataRate = value;
                        m_params.InternalClockNeedUpdate = true;
                        UpdateClock();
                    }

                    if (m_params.UartSubMode.Value == CyEUARTSubModeType.IRDA)
                    {
                        List<uint> rates = new List<uint>(IRDA_DATA_RATES_LIST);
                        if (parseSuccess && rates.Contains(value))
                        {
                            m_errorProvider.SetError(m_cbBaudRate, string.Empty);
                            UpdateOvsFactor();
                        }
                        else
                        {
                            m_errorProvider.SetError(m_cbBaudRate, Resources.BaudRateIrDAValueError);
                        }
                    }
                    else
                    {
                        if (parseSuccess && value >= CyParamRanges.UART_DATA_RATE_MIN_VALUE &&
                            value <= CyParamRanges.UART_DATA_RATE_MAX_VALUE)
                        {
                            m_errorProvider.SetError(m_cbBaudRate, string.Empty);
                        }
                        else
                        {
                            m_errorProvider.SetError(m_cbBaudRate, string.Format(Resources.BaudRateValueError,
                                CyParamRanges.UART_DATA_RATE_MIN_VALUE, CyParamRanges.UART_DATA_RATE_MAX_VALUE));
                        }
                    }
                }
            }
        }
        #endregion

        #region Actual baud rate
        private void UpdateClock()
        {
            const double MAX_RECOMMENDED_TOLERANCE_PCT = 2.5;

            string dataRateStr = m_params.UART_ClockFromTerminal ?
                Resources.ClockDisplayUnknown : Resources.ClockDisplayUnknownPressApply;

            m_lblBaudRate.Enabled = !m_params.UART_ClockFromTerminal;
            m_cbBaudRate.Enabled = !m_params.UART_ClockFromTerminal;

            ClearNotifications(m_lblActualBaudRate);

            if (m_params.SCBMode == CyESCBMode.UART)
            {
                double actualDataRate = m_params.GetActualDataRate(CyESCBMode.UART);
                actualDataRate *= 1000;

                if (actualDataRate > 0 && (m_params.UART_ClockFromTerminal ||
                    (m_params.InternalClockNeedUpdate == false && m_params.SCBMode == CyESCBMode.UART)))
                {
                    dataRateStr = actualDataRate.ToString();

                    if (m_params.UART_ClockFromTerminal == false)
                    {
                        CyClockData sclkData = m_params.UART_ClockFromTerminal
                            ? CyParameters.GetExternalClockData(m_params.TermQuery)
                            : CyParameters.GetInternalClockData(m_params.TermQuery);

                        if (sclkData != null)
                        {
                            double minusAccuracyPct = sclkData.MinusAccuracyPct;
                            double plusAccuracyPct = sclkData.PlusAccuracyPct;

                            double minusDelta = ((MAX_RECOMMENDED_TOLERANCE_PCT - minusAccuracyPct) / 100);
                            double plusDelta = ((MAX_RECOMMENDED_TOLERANCE_PCT - plusAccuracyPct) / 100);

                            if (actualDataRate < (m_params.UART_DataRate - m_params.UART_DataRate * minusDelta) ||
                                actualDataRate > (m_params.UART_DataRate + m_params.UART_DataRate * plusDelta))
                            {
                                m_noteProvider.SetError(m_lblActualBaudRate, Resources.UARTToleranceNote);
                            }
                        }
                    }
                }
            }

            // Update Actual Data Rate label
            m_lblActualBaudRate.Text = string.Format(Resources.ActualBaudRateDisplayFormat, dataRateStr);
        }
        #endregion
    }
}
