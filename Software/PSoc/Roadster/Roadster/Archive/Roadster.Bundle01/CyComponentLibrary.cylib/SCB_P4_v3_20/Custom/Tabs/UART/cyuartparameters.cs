/*******************************************************************************
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;

namespace SCB_P4_v3_20
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string UART_CLOCK_FROM_TERM = "UartClockFromTerm";
        public const string UART_DATA_RATE = "UartDataRate";
        public const string UART_DROP_ON_FRAME_ERR = "UartDropOnFrameErr";
        public const string UART_DROP_ON_PARITY_ERR = "UartDropOnParityErr";
        public const string UART_HFCLK_KHZ = "UartHFclkKhz";
        public const string UART_WAKEUP_FROM_SLEEP_ENABLED = "UartWakeEnable";
        public const string UART_LOW_POWER = "UartIrdaLowPower";
        public const string UART_INTERRUPT_MODE = "UartInterruptMode";
        public const string UART_INTR_RX_FRAME_ERR = "UartIntrRxFrameErr";
        public const string UART_INTR_RX_FULL = "UartIntrRxFull";
        public const string UART_INTR_RX_NOT_EMPTY = "UartIntrRxNotEmpty";
        public const string UART_INTR_RX_OVERFLOW = "UartIntrRxOverflow";
        public const string UART_INTR_RX_PARITY_ERR = "UartIntrRxParityErr";
        public const string UART_INTR_RX_TRIGGER = "UartIntrRxTrigger";
        public const string UART_INTR_RX_UNDERFLOW = "UartIntrRxUnderflow";
        public const string UART_INTR_TX_EMPTY = "UartIntrTxEmpty";
        public const string UART_INTR_TX_NOT_FULL = "UartIntrTxNotFull";
        public const string UART_INTR_TX_OVERFLOW = "UartIntrTxOverflow";
        public const string UART_INTR_TX_TRIGGER = "UartIntrTxTrigger";
        public const string UART_INTR_TX_UART_DONE = "UartIntrTxUartDone";
        public const string UART_INTR_TX_UART_LOST_ARB = "UartIntrTxUartLostArb";
        public const string UART_INTR_TX_UART_NACK = "UartIntrTxUartNack";
        public const string UART_INTR_TX_UNDERFLOW = "UartIntrTxUnderflow";
        public const string UART_IRDA_POLARITY = "UartIrdaPolarity";
        public const string UART_MEDIAN_FILTER_ENABLED = "UartMedianFilterEnable";
        public const string UART_ENABLE_BYTE_MODE = "UartByteModeEnable";
        public const string UART_MP_ENABLED = "UartMpEnable";
        public const string UART_DROP_ON_PARITY_ERROR = "UartDropOnParityErr";
        public const string UART_DROP_ON_FRAME_ERROR = "UartDropOnFrameErr";
        public const string UART_MP_RX_ACCEPT_ADDRESS = "UartMpRxAcceptAddress";
        public const string UART_MP_RX_ADDRESS = "UartMpRxAddress";
        public const string UART_MP_RX_ADDRESS_MASK = "UartMpRxAddressMask";
        public const string UART_NUMBER_OF_DATA_BITS = "UartNumberOfDataBits";
        public const string UART_NUMBER_OF_STOP_BITS = "UartNumberOfStopBits";
        public const string UART_OVS_FACTOR = "UartOvsFactor";
        public const string UART_PARITY_TYPE = "UartParityType";
        public const string UART_RX_BUFFER_SIZE = "UartRxBufferSize";
        public const string UART_RX_ENABLED = "UartRxEnable";
        public const string UART_RX_TRIGGER_LEVEL = "UartRxTriggerLevel";
        public const string UART_SM_CARD_RETRY_ON_NACK = "UartSmCardRetryOnNack";
        public const string UART_SUB_MODE = "UartSubMode";
        public const string UART_DIRECTION = "UartDirection";
        public const string UART_TX_BUFFER_SIZE = "UartTxBufferSize";
        public const string UART_TX_ENABLED = "UartTxEnable";
        public const string UART_TX_TRIGGER_LEVEL = "UartTxTriggerLevel";
        public const string UART_DMA_RX_OUTPUT = "UartRxOutputEnable";
        public const string UART_DMA_TX_OUTPUT = "UartTxOutputEnable";
        public const string UART_SMARTIO_ENABLE = "UartSmartioEnable";
        // Control flow parameters
        public const string UART_RTS_ENABLE = "UartRtsEnable";
        public const string UART_CTS_ENABLE = "UartCtsEnable";
        public const string UART_RTS_POLARITY = "UartRtsPolarity";
        public const string UART_CTS_POLARITY = "UartCtsPolarity";
        public const string UART_RTS_TRIGGER_LEVEL = "UartRtsTriggerLevel";
    }
    #endregion

    #region Component Parameters Ranges
    public partial class CyParamRanges
    {
        public const byte UART_OVS_FACTOR_MIN = 8;
        public const byte UART_OVS_FACTOR_MAX = 16;

        public const int UART_MIN_TRIGGER_LEVEL = 0;
        public const int UART_MAX_TRIGGER_LEVEL = 7;
        public const int UART_TRIGGER_LEVEL_DEFAULT = 4;

        public const UInt32 UART_DATA_RATE_MIN_VALUE = 1;
        public const UInt32 UART_DATA_RATE_MAX_VALUE = 1000000;

        public const byte UART_BTLDR_DEFAULT_NUMBER_OF_BITS = 12;   // 12 bits = Start bit (1) + data bits (8) + Parity (1) + Stop bits (2)
        public const double UART_BTLDR_DEFAULT_BIT_RATE_KBPS = 9.6; // Baud rate = 9600 (entered in kbps)
    }
    #endregion

    #region Component Enums
    public enum CyEUARTSubModeType { STANDARD, SMART_CARD, IRDA }
    public enum CyEUARTDirectionType { TX_RX = 3, RX = 1, TX = 2 }
    public enum CyEUARTNumberDataBitsType { FIVE = 5, SIX, SEVEN, EIGHT, NINE }
    public enum CyEUARTParityType { EVEN, ODD, PARITY_NONE }
    public enum CyEUARTPolarityType { NON_INVERTING, INVERTING }
    public enum CyEUARTNumberStopBitsType { ONE_H_BITS = 3, TWO_BITS = 4, ONE_BIT = 2 }
    #endregion

    public partial class CyParameters
    {
        #region Class properties
        public UInt32 UART_DataRate
        {
            get { return GetValue<UInt32>(CyParamNames.UART_DATA_RATE); }
            set { SetValue(CyParamNames.UART_DATA_RATE, value); }
        }

        public bool UART_ClockFromTerminal
        {
            get
            {
                return GetValue<bool>(CyParamNames.UART_CLOCK_FROM_TERM);
            }
            set
            {
                SetValue(CyParamNames.UART_CLOCK_FROM_TERM, value);
            }
        }

        public UInt16 UART_OvsFactor
        {
            get { return GetValue<UInt16>(CyParamNames.UART_OVS_FACTOR); }
            set { SetValue(CyParamNames.UART_OVS_FACTOR, value); }
        }

        public bool UART_MedianFilterEnabled
        {
            get { return GetValue<bool>(CyParamNames.UART_MEDIAN_FILTER_ENABLED); }
            set { SetValue(CyParamNames.UART_MEDIAN_FILTER_ENABLED, value); }
        }

        public bool UART_EnableByteMode
        {
            get { return GetValue<bool>(CyParamNames.UART_ENABLE_BYTE_MODE); }
            set { SetValue(CyParamNames.UART_ENABLE_BYTE_MODE, value); }
        }

        public bool UART_RetryOnNACK
        {
            get { return GetValue<bool>(CyParamNames.UART_SM_CARD_RETRY_ON_NACK); }
            set { SetValue(CyParamNames.UART_SM_CARD_RETRY_ON_NACK, value); }
        }

        public bool UART_InvertRXProperty
        {
            get
            {
                return GetValue<CyEUARTPolarityType>(CyParamNames.UART_IRDA_POLARITY) == CyEUARTPolarityType.INVERTING;
            }
            set
            {
                SetValue(CyParamNames.UART_IRDA_POLARITY,
                    value ? CyEUARTPolarityType.INVERTING : CyEUARTPolarityType.NON_INVERTING);
            }
        }

        public bool UART_WakeupFromSleepEnabled
        {
            get { return GetValue<bool>(CyParamNames.UART_WAKEUP_FROM_SLEEP_ENABLED); }
            set { SetValue(CyParamNames.UART_WAKEUP_FROM_SLEEP_ENABLED, value); }
        }

        public bool UART_LowPowerReceive
        {
            get { return GetValue<bool>(CyParamNames.UART_LOW_POWER); }
            set { SetValue(CyParamNames.UART_LOW_POWER, value); }
        }

        public UInt32 UART_RxBufferSize
        {
            get { return GetValue<UInt32>(CyParamNames.UART_RX_BUFFER_SIZE); }
            set { SetValue(CyParamNames.UART_RX_BUFFER_SIZE, value); }
        }

        public UInt32 UART_TxBufferSize
        {
            get { return GetValue<UInt32>(CyParamNames.UART_TX_BUFFER_SIZE); }
            set { SetValue(CyParamNames.UART_TX_BUFFER_SIZE, value); }
        }

        public CyEInterruptModeType UART_InterruptMode
        {
            get { return GetValue<CyEInterruptModeType>(CyParamNames.UART_INTERRUPT_MODE); }
            set { SetValue(CyParamNames.UART_INTERRUPT_MODE, value); }
        }

        public bool UART_InterruptOnUARTDone
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_UART_DONE); }
            set { SetValue(CyParamNames.UART_INTR_TX_UART_DONE, value); }
        }

        public bool UART_InterruptOnTXFIFONotFull
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_NOT_FULL); }
            set { SetValue(CyParamNames.UART_INTR_TX_NOT_FULL, value); }
        }

        public bool UART_InterruptOnTXFIFOEmpty
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_EMPTY); }
            set { SetValue(CyParamNames.UART_INTR_TX_EMPTY, value); }
        }

        public bool UART_InterruptOnTXFIFOOverflow
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_OVERFLOW); }
            set { SetValue(CyParamNames.UART_INTR_TX_OVERFLOW, value); }
        }

        public bool UART_InterruptOnTXFIFOUnderflow
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_UNDERFLOW); }
            set { SetValue(CyParamNames.UART_INTR_TX_UNDERFLOW, value); }
        }

        public bool UART_InterruptOnTXLostArbitration
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_UART_LOST_ARB); }
            set { SetValue(CyParamNames.UART_INTR_TX_UART_LOST_ARB, value); }
        }

        public bool UART_InterruptOnTXNACK
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_UART_NACK); }
            set { SetValue(CyParamNames.UART_INTR_TX_UART_NACK, value); }
        }

        public bool UART_InterruptOnTXFIFOTrigger
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_TX_TRIGGER); }
            set { SetValue(CyParamNames.UART_INTR_TX_TRIGGER, value); }
        }

        public byte UART_TXTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.UART_TX_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.UART_TX_TRIGGER_LEVEL, value); }
        }

        public bool UART_InterruptOnRXFIFOFull
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_RX_FULL); }
            set { SetValue(CyParamNames.UART_INTR_RX_FULL, value); }
        }

        public bool UART_InterruptOnRXFIFONotEmpty
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_RX_NOT_EMPTY); }
            set { SetValue(CyParamNames.UART_INTR_RX_NOT_EMPTY, value); }
        }

        public bool UART_InterruptOnRXFIFOOverflow
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_RX_OVERFLOW); }
            set { SetValue(CyParamNames.UART_INTR_RX_OVERFLOW, value); }
        }

        public bool UART_InterruptOnRXFIFOUnderflow
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_RX_UNDERFLOW); }
            set { SetValue(CyParamNames.UART_INTR_RX_UNDERFLOW, value); }
        }

        public bool UART_InterruptOnRXFrameError
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_RX_FRAME_ERR); }
            set { SetValue(CyParamNames.UART_INTR_RX_FRAME_ERR, value); }
        }

        public bool UART_InterruptOnRXParityError
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_RX_PARITY_ERR); }
            set { SetValue(CyParamNames.UART_INTR_RX_PARITY_ERR, value); }
        }

        public bool UART_InterruptOnRXFIFOTrigger
        {
            get { return GetValue<bool>(CyParamNames.UART_INTR_RX_TRIGGER); }
            set { SetValue(CyParamNames.UART_INTR_RX_TRIGGER, value); }
        }

        public byte UART_RXTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.UART_RX_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.UART_RX_TRIGGER_LEVEL, value); }
        }

        public bool UART_MultiProcessorModeEnabled
        {
            get { return GetValue<bool>(CyParamNames.UART_MP_ENABLED); }
            set { SetValue(CyParamNames.UART_MP_ENABLED, value); }
        }

        public bool UART_RXFIFODropOnParityError
        {
            get { return GetValue<bool>(CyParamNames.UART_DROP_ON_PARITY_ERROR); }
            set { SetValue(CyParamNames.UART_DROP_ON_PARITY_ERROR, value); }
        }

        public bool UART_RXFIFODropOnFrameError
        {
            get { return GetValue<bool>(CyParamNames.UART_DROP_ON_FRAME_ERROR); }
            set { SetValue(CyParamNames.UART_DROP_ON_FRAME_ERROR, value); }
        }

        public byte UART_MultiProcessorAddress
        {
            get { return GetValue<byte>(CyParamNames.UART_MP_RX_ADDRESS); }
            set { SetValue(CyParamNames.UART_MP_RX_ADDRESS, value); }
        }

        public bool UART_MultiProcessorAcceptAddress
        {
            get { return GetValue<bool>(CyParamNames.UART_MP_RX_ACCEPT_ADDRESS); }
            set { SetValue(CyParamNames.UART_MP_RX_ACCEPT_ADDRESS, value); }
        }

        public byte UART_MultiProcessorAddressMask
        {
            get { return GetValue<byte>(CyParamNames.UART_MP_RX_ADDRESS_MASK); }
            set { SetValue(CyParamNames.UART_MP_RX_ADDRESS_MASK, value); }
        }

        public bool UART_EnableRtsPin
        {
            get { return GetValue<bool>(CyParamNames.UART_RTS_ENABLE); }
            set { SetValue(CyParamNames.UART_RTS_ENABLE, value); }
        }

        public bool UART_EnableCtsPin
        {
            get { return GetValue<bool>(CyParamNames.UART_CTS_ENABLE); }
            set { SetValue(CyParamNames.UART_CTS_ENABLE, value); }
        }

        public byte UART_RtsTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.UART_RTS_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.UART_RTS_TRIGGER_LEVEL, value); }
        }

        public bool UART_RxOutput
        {
            get { return GetValue<bool>(CyParamNames.UART_DMA_RX_OUTPUT); }
            set { SetValue(CyParamNames.UART_DMA_RX_OUTPUT, value); }
        }
        public bool UART_TxOutput
        {
            get { return GetValue<bool>(CyParamNames.UART_DMA_TX_OUTPUT); }
            set { SetValue(CyParamNames.UART_DMA_TX_OUTPUT, value); }
        }
        public bool UART_SmartioEnable
        {
            get { return GetValue<bool>(CyParamNames.UART_SMARTIO_ENABLE); }
            set { SetValue(CyParamNames.UART_SMARTIO_ENABLE, value); }
        }

        public bool IsRtsPinAllowed
        {
            get
            {
                return (this.IsScbIPV2 &&
                       (this.m_uartSubMode.Value == CyEUARTSubModeType.STANDARD) &&
                       ((this.m_uartDirection.Value == CyEUARTDirectionType.RX) ||
                        (this.m_uartDirection.Value == CyEUARTDirectionType.TX_RX)));
            }
        }

        public bool IsCtsPinAllowed
        {
            get
            {
                return (this.IsScbIPV2 &&
                       (this.m_uartSubMode.Value == CyEUARTSubModeType.STANDARD) &&
                       ((this.m_uartDirection.Value == CyEUARTDirectionType.TX) ||
                        (this.m_uartDirection.Value == CyEUARTDirectionType.TX_RX)));
            }
        }

        public byte UartRxBufferMinSize
        {
            get
            {
                return IsScbIPV2 && UART_EnableByteMode
                    ? GetByteModeBufferMinSize()
                    : GetBufferMinSize();
            }
        }

        public byte UartTxBufferMinSize
        {
            get
            {
                return IsScbIPV2 && UART_EnableByteMode
                    ? GetByteModeBufferMinSize()
                    : GetBufferMinSize();
            }
        }

        public byte UartMaxTriggerLevel
        {
            get
            {
                return IsScbIPV2 && UART_EnableByteMode
                    ? CyParamRanges.MAX_TRIGGER_LEVEL_BYTE_MODE
                    : CyParamRanges.MAX_TRIGGER_LEVEL;
            }
        }

        public bool UartIsRxFifoUsed
        {
            get { return UART_RxBufferSize <= UartRxBufferMinSize; }
        }

        public bool UartIsTxFifoUsed
        {
            get { return UART_TxBufferSize <= UartTxBufferMinSize; }
        }
        #endregion

        public List<CyCustErr> GetUartDrcErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            if (IsScbIPV0)
            {
                // Check UART control flow
                if ((IsRtsPinAllowed == false && UART_EnableRtsPin) ||
                    (IsCtsPinAllowed == false && UART_EnableCtsPin))
                {
                    errorList.Add(new CyCustErr(Resources.UARTControlFlowDeviceError));
                }

                // Check Byte mode
                if (UART_EnableByteMode)
                {
                    errorList.Add(new CyCustErr(String.Format("{0}: {1}", CyESCBMode.UART, Resources.ByteModeError)));
                }
            }

            // Check DMA Rx Tx outputs
            if (IsDmaCapable == false)
            {
                if (UART_RxOutput || UART_TxOutput)
                    errorList.Add(new CyCustErr(String.Format("{0}: {1}", CyESCBMode.UART,
                        Resources.DMASupportError)));
            }

            // SmartIO support
            if (UART_SmartioEnable && !IsSmartioCapable)
            {
                errorList.Add(new CyCustErr(Resources.SmartioSupportError));
            }

            // Validate RX TX buffers values, because for CCG3 the default values are wrong
            if (UART_RxBufferSize < UartRxBufferMinSize)
            {
               errorList.Add(new CyCustErr(string.Format(Resources.ErrorValueLimitBufferSize, UartRxBufferMinSize)));
            }
            if (UART_TxBufferSize < UartTxBufferMinSize)
            {
                errorList.Add(new CyCustErr(string.Format(Resources.ErrorValueLimitBufferSize, UartTxBufferMinSize)));
            }

            return errorList;
        }

        #region Class Events
        /// <summary>
        /// Event fired when UART mode is changed.
        /// </summary>
        public event EventHandler<EventArgs> UartModeChanged;

        /// <summary>
        /// Event fired when UART Wakeup is changed.
        /// </summary>
        public event EventHandler<EventArgs> UartWakeupChanged;

        /// <summary>
        /// Event fired when UART SmartIo Support is changed.
        /// </summary>
        public event EventHandler<EventArgs> UartSmartIoSupportChanged;

        #endregion Class Events

        #region Event Handlers
        /// <summary>
        /// Called when UART mode is changed.
        /// </summary>
        public void OnUartModeChanged(object sender, EventArgs e)
        {
            EventHandler<EventArgs> handler = UartModeChanged;
            if (handler != null)
                handler(sender, e);
        }

        /// <summary>
        /// Called when UART Wakeup is changed.
        /// </summary>
        public void OnUartWakeupChanged(object sender, EventArgs e)
        {
            EventHandler<EventArgs> handler = UartWakeupChanged;
            if (handler != null)
                handler(sender, e);
        }

        /// <summary>
        /// Called when UART SmartIo Support is changed.
        /// </summary>
        public void OnUartSmartIoSupportChanged(object sender, EventArgs e)
        {
            EventHandler<EventArgs> handler = UartSmartIoSupportChanged;
            if (handler != null)
                handler(sender, e);
        }
        #endregion Event Handlers
    }
}
