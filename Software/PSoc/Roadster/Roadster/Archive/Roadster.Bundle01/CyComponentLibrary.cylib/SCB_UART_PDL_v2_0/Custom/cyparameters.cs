/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace SCB_UART_PDL_v2_0
{
    #region Component parameters names
    public class CyParamNames
    {
        public const string BAUD_RATE = "BaudRate";
        public const string BITS_ORDER = "BitsOrder";
        public const string BREAK_SIGNAL_BITS = "BreakSignalBits";
        public const string CLOCK_FROM_TERM = "ClockFromTerm";
        public const string CTS_POLARITY = "CtsPolarity";
        public const string DATA_WIDTH = "DataWidth";
        public const string DIRECTION = "Direction";
        public const string DROP_ON_FRAME_ERROR = "DropOnFrameErr";
        public const string DROP_ON_PARITY_ERROR = "DropOnParityErr";
        public const string ENABLE_CTS = "EnableCts";
        public const string ENABLE_INPUT_FILTER = "EnableInputFilter";
        public const string ENABLE_MULTI_PROC = "EnableMultiProc";
        public const string ENABLE_RTS = "EnableRts";
        public const string ENABLE_RX_OUTPUT = "EnableRxOutput";
        public const string ENABLE_TX_OUTPUT = "EnableTxOutput";
        public const string INTERRUPT_MODE = "InterruptMode";
        public const string INTR_RX_BREAK_DETECTED = "IntrRxBreakDetected";
        public const string INTR_RX_FRAME_ERR = "IntrRxFrameErr";
        public const string INTR_RX_FULL = "IntrRxFull";
        public const string INTR_RX_NOT_EMPTY = "IntrRxNotEmpty";
        public const string INTR_RX_OVERFLOW = "IntrRxOverflow";
        public const string INTR_RX_PARITY_ERR = "IntrRxParityErr";
        public const string INTR_RX_TRIGGER = "IntrRxTrigger";
        public const string INTR_RX_UNDERFLOW = "IntrRxUnderflow";
        public const string INTR_TX_EMPTY = "IntrTxEmpty";
        public const string INTR_TX_NOT_FULL = "IntrTxNotFull";
        public const string INTR_TX_OVERFLOW = "IntrTxOverflow";
        public const string INTR_TX_TRIGGER = "IntrTxTrigger";
        public const string INTR_TX_UART_DONE = "IntrTxUartDone";
        public const string INTR_TX_UART_LOST_ARB = "IntrTxUartLostArb";
        public const string INTR_TX_UART_NACK = "IntrTxUartNack";
        public const string INTR_TX_UNDERFLOW = "IntrTxUnderflow";
        public const string IRDA_LOW_POWER = "IrdaLowPower";
        public const string IRDA_POLARITY = "IrdaPolarity";
        public const string MP_RX_ACCEPT_ADDRESS = "MpRxAcceptAddress";
        public const string MP_RX_ADDRESS = "MpRxAddress";
        public const string MP_RX_ADDRESS_MASK = "MpRxAddressMask";
        public const string STOP_BITS = "StopBits";
        public const string OVS_FACTOR = "OvsFactor";
        public const string PARITY_TYPE = "ParityType";
        public const string RTS_POLARITY = "RtsPolarity";
        public const string RTS_TRIGGER_LEVEL = "RtsTriggerLevel";
        public const string RX_TRIGGER_LEVEL = "RxTriggerLevel";
        public const string SHOW_TERMINALS = "ShowTerminals";
        public const string SM_CARD_RETRY_ON_NACK = "SmCardRetryOnNack";
        public const string COM_MODE = "ComMode";
        public const string TX_TRIGGER_LEVEL = "TxTriggerLevel";

        // Local parameters
        public const string IS_DMA_CAPABLE = "IsDmaCapable";
        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Component parameters ranges
    public class CyParamRanges
    {
        public const byte OVS_FACTOR_MAX = 16;
        public const byte WORD_WIDTH_BYTE_MODE_MAX = 8;

        public static readonly Dictionary<uint, ushort> IRDA_DATA_RATES_LIST = new Dictionary<uint, ushort>()
        {
            { 1200, 1536 },
            { 2400,  768 },
            { 9600,  192 },
            { 19200,  96 },
            { 38400,  48 },
            { 57600,  32 },
            { 115200, 16 }
        };
    }
    #endregion

    #region Enums
    public enum CyESubModeType { STANDARD, SMART_CARD, IRDA }
    public enum CyEDirectionType { TX_RX = 3, RX = 1, TX = 2 }
    public enum CyEDataWidthType { FIVE = 5, SIX, SEVEN, EIGHT, NINE }
    public enum CyEParityType { EVEN = 2, ODD = 3, NONE = 0 }
    public enum CyEPolarityType { NON_INVERTING, INVERTING }
    public enum CyETransferMode { FIFO, CIRCULAR_BUFFER, LINEAR_BUFFER }
    public enum CyEStopBitsType { ONE_BIT = 2, ONE_H_BITS, TWO_BITS, TWO_H_BITS, THREE_BITS, THREE_H_BITS, FOUR_BITS }
    public enum CyEInterruptModeType { INTERNAL = 1, EXTERNAL = 2 }
    public enum CyEActivePolarityType { ACTIVE_LOW, ACTIVE_HIGH }
    public enum CyETolerance { MINUS_MAX = 100, IMO_ACCURACY = 2, PLUS_MAX = 1000, DEFAULT = 5, ZERO_ACCURACY = 0 }
    public enum CyEBitsOrder { LSB_FIRST, MSB_FIRST }
    #endregion

    public class CyParameters
    {
        #region Constants
        // Clock names
        public const string SCB_CLOCK_SCBCLK = "or_sclk";
        public const string SCB_CLOCK_TERM = "clock";
        #endregion

        #region Private fields
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        #endregion

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit, instEdit, termQuery)
        {
        }

        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
            : this(instQuery, null, termQuery)
        {
        }
        #endregion

        #region Properties
        //
        // Common properties
        //
        /// <summary>
        /// Indicates whether it is allowed to edit the parameters.
        /// </summary>
        public bool EditMode { get; set; }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        //
        // Parameters getters/setters
        //
        public CyESubModeType ComMode
        {
            get { return GetValue<CyESubModeType>(CyParamNames.COM_MODE); }
            set { SetValue(CyParamNames.COM_MODE, value); }
        }

        public CyEDirectionType Direction
        {
            get { return GetValue<CyEDirectionType>(CyParamNames.DIRECTION); }
            set { SetValue(CyParamNames.DIRECTION, value); }
        }

        public CyEDataWidthType DataWidth
        {
            get { return GetValue<CyEDataWidthType>(CyParamNames.DATA_WIDTH); }
            set { SetValue(CyParamNames.DATA_WIDTH, value); }
        }

        public CyEParityType ParityType
        {
            get { return GetValue<CyEParityType>(CyParamNames.PARITY_TYPE); }
            set { SetValue(CyParamNames.PARITY_TYPE, value); }
        }

        public CyEStopBitsType StopBits
        {
            get { return GetValue<CyEStopBitsType>(CyParamNames.STOP_BITS); }
            set { SetValue(CyParamNames.STOP_BITS, value); }
        }

        public CyEBitsOrder BitsOrder
        {
            get { return GetValue<CyEBitsOrder>(CyParamNames.BITS_ORDER); }
            set { SetValue(CyParamNames.BITS_ORDER, value); }
        }

        public CyEActivePolarityType RtsPolarity
        {
            get { return GetValue<CyEActivePolarityType>(CyParamNames.RTS_POLARITY); }
            set { SetValue(CyParamNames.RTS_POLARITY, value); }
        }

        public CyEActivePolarityType CtsPolarity
        {
            get { return GetValue<CyEActivePolarityType>(CyParamNames.CTS_POLARITY); }
            set { SetValue(CyParamNames.CTS_POLARITY, value); }
        }

        public uint BaudRate
        {
            get { return GetValue<UInt32>(CyParamNames.BAUD_RATE); }
            set { SetValue(CyParamNames.BAUD_RATE, value); }
        }

        public bool ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.CLOCK_FROM_TERM); }
            set { SetValue(CyParamNames.CLOCK_FROM_TERM, value); }
        }

        public ushort OvsFactor
        {
            get { return GetValue<UInt16>(CyParamNames.OVS_FACTOR); }
            set { SetValue(CyParamNames.OVS_FACTOR, value); }
        }

        public bool InputFilterEnabled
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_INPUT_FILTER); }
            set { SetValue(CyParamNames.ENABLE_INPUT_FILTER, value); }
        }

        public bool ByteMode
        {
            get { return (byte)(DataWidth) <= CyParamRanges.WORD_WIDTH_BYTE_MODE_MAX; }
        }

        public bool RetryOnNACK
        {
            get { return GetValue<bool>(CyParamNames.SM_CARD_RETRY_ON_NACK); }
            set { SetValue(CyParamNames.SM_CARD_RETRY_ON_NACK, value); }
        }

        public bool InvertRXProperty
        {
            get { return GetValue<CyEPolarityType>(CyParamNames.IRDA_POLARITY) == CyEPolarityType.INVERTING; }
            set { SetValue(CyParamNames.IRDA_POLARITY, value ? CyEPolarityType.INVERTING : CyEPolarityType.NON_INVERTING); }
        }

        public bool LowPowerReceive
        {
            get { return GetValue<bool>(CyParamNames.IRDA_LOW_POWER); }
            set { SetValue(CyParamNames.IRDA_LOW_POWER, value); }
        }

        public CyEInterruptModeType InterruptMode
        {
            get { return GetValue<CyEInterruptModeType>(CyParamNames.INTERRUPT_MODE); }
            set { SetValue(CyParamNames.INTERRUPT_MODE, value); }
        }

        public bool InterruptOnUARTDone
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_UART_DONE); }
            set { SetValue(CyParamNames.INTR_TX_UART_DONE, value); }
        }

        public bool InterruptOnTXFIFONotFull
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_NOT_FULL); }
            set { SetValue(CyParamNames.INTR_TX_NOT_FULL, value); }
        }

        public bool InterruptOnTXFIFOEmpty
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_EMPTY); }
            set { SetValue(CyParamNames.INTR_TX_EMPTY, value); }
        }

        public bool InterruptOnTXFIFOOverflow
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_OVERFLOW); }
            set { SetValue(CyParamNames.INTR_TX_OVERFLOW, value); }
        }

        public bool InterruptOnTXFIFOUnderflow
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_UNDERFLOW); }
            set { SetValue(CyParamNames.INTR_TX_UNDERFLOW, value); }
        }

        public bool InterruptOnTXLostArbitration
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_UART_LOST_ARB); }
            set { SetValue(CyParamNames.INTR_TX_UART_LOST_ARB, value); }
        }

        public bool InterruptOnTXNACK
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_UART_NACK); }
            set { SetValue(CyParamNames.INTR_TX_UART_NACK, value); }
        }

        public bool InterruptOnTxFifoBelowLevel
        {
            get { return GetValue<bool>(CyParamNames.INTR_TX_TRIGGER); }
            set { SetValue(CyParamNames.INTR_TX_TRIGGER, value); }
        }

        public byte TxFifoLevel
        {
            get { return GetValue<byte>(CyParamNames.TX_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.TX_TRIGGER_LEVEL, value); }
        }

        public bool InterruptOnRXFIFOFull
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_FULL); }
            set { SetValue(CyParamNames.INTR_RX_FULL, value); }
        }

        public bool InterruptOnRXFIFONotEmpty
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_NOT_EMPTY); }
            set { SetValue(CyParamNames.INTR_RX_NOT_EMPTY, value); }
        }

        public bool InterruptOnRXFIFOOverflow
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_OVERFLOW); }
            set { SetValue(CyParamNames.INTR_RX_OVERFLOW, value); }
        }

        public bool InterruptOnRXFIFOUnderflow
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_UNDERFLOW); }
            set { SetValue(CyParamNames.INTR_RX_UNDERFLOW, value); }
        }

        public bool InterruptOnRXFrameError
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_FRAME_ERR); }
            set { SetValue(CyParamNames.INTR_RX_FRAME_ERR, value); }
        }

        public bool InterruptOnRXParityError
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_PARITY_ERR); }
            set { SetValue(CyParamNames.INTR_RX_PARITY_ERR, value); }
        }

        public bool InterruptOnRXBreakDetected
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_BREAK_DETECTED); }
            set { SetValue(CyParamNames.INTR_RX_BREAK_DETECTED, value); }
        }

        public bool InterruptOnRxFifoAboveLevel
        {
            get { return GetValue<bool>(CyParamNames.INTR_RX_TRIGGER); }
            set { SetValue(CyParamNames.INTR_RX_TRIGGER, value); }
        }

        public byte RxFifoLevel
        {
            get { return GetValue<byte>(CyParamNames.RX_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.RX_TRIGGER_LEVEL, value); }
        }

        public bool MultiProcessorModeEnabled
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_MULTI_PROC); }
            set { SetValue(CyParamNames.ENABLE_MULTI_PROC, value); }
        }

        public bool RxFifoDropOnParityError
        {
            get { return GetValue<bool>(CyParamNames.DROP_ON_PARITY_ERROR); }
            set { SetValue(CyParamNames.DROP_ON_PARITY_ERROR, value); }
        }

        public bool RxFifoDropOnFrameError
        {
            get { return GetValue<bool>(CyParamNames.DROP_ON_FRAME_ERROR); }
            set { SetValue(CyParamNames.DROP_ON_FRAME_ERROR, value); }
        }

        public byte MultiProcessorAddress
        {
            get { return GetValue<byte>(CyParamNames.MP_RX_ADDRESS); }
            set { SetValue(CyParamNames.MP_RX_ADDRESS, value); }
        }

        public bool MultiProcessorAcceptAddress
        {
            get { return GetValue<bool>(CyParamNames.MP_RX_ACCEPT_ADDRESS); }
            set { SetValue(CyParamNames.MP_RX_ACCEPT_ADDRESS, value); }
        }

        public byte MultiProcessorAddressMask
        {
            get { return GetValue<byte>(CyParamNames.MP_RX_ADDRESS_MASK); }
            set { SetValue(CyParamNames.MP_RX_ADDRESS_MASK, value); }
        }

        public bool EnableRtsPin
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_RTS); }
            set { SetValue(CyParamNames.ENABLE_RTS, value); }
        }

        public bool EnableCtsPin
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_CTS); }
            set { SetValue(CyParamNames.ENABLE_CTS, value); }
        }

        public byte RtsTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.RTS_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.RTS_TRIGGER_LEVEL, value); }
        }

        public bool RxOutput
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_RX_OUTPUT); }
            set { SetValue(CyParamNames.ENABLE_RX_OUTPUT, value); }
        }

        public bool TxOutput
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_TX_OUTPUT); }
            set { SetValue(CyParamNames.ENABLE_TX_OUTPUT, value); }
        }

        public bool ShowTerminals
        {
            get { return GetValue<bool>(CyParamNames.SHOW_TERMINALS); }
            set { SetValue(CyParamNames.SHOW_TERMINALS, value); }
        }

        public byte BreakSignalBits
        {
            get { return GetValue<byte>(CyParamNames.BREAK_SIGNAL_BITS); }
            set { SetValue(CyParamNames.BREAK_SIGNAL_BITS, value); }
        }

        //
        // Other properties
        //
        public bool IsDmaCapable
        {
            get { return GetValue<bool>(CyParamNames.IS_DMA_CAPABLE); }
        }
        #endregion

        #region Getting Parameters
        public T GetValue<T>(string paramName)
        {
            return GetValue<T>(paramName, m_instQuery);
        }

        public static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            T value = default(T);
            if (instQuery == null) return default(T);
            CyCompDevParam param = instQuery.GetCommittedParam(paramName);
            System.Diagnostics.Debug.Assert(param != null);
            CyCustErr err = (param != null) ? param.TryGetValueAs<T>(out value) : CyCustErr.OK;
            return (err != null && err.IsOK && value != null) ? value : default(T);
        }

        public bool IsParamFormalAndHidden(string paramName)
        {
            bool result = false;
            if (m_instQuery != null)
            {
                CyCompDevParam param = m_instQuery.GetCommittedParam(paramName);
                result = param != null && param.IsFormal && param.IsVisible == false;
            }
            return result;
        }
        #endregion

        #region Setting Parameters
        public void SetValue<T>(string paramName, T value)
        {
            if (EditMode)
            {
                SetValue(m_instEdit, paramName, value);
            }
        }

        public static CyCustErr SetValue<T>(ICyInstEdit_v1 instEdit, string paramName, T value)
        {
            if (instEdit == null)
            {
                return CyCustErr.OK;
            }

            string valueToSet = value.ToString();
            if (value != null)
            {
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                    valueToSet += "u";
            }
            if (instEdit.SetParamExpr(paramName, valueToSet) && instEdit.CommitParamExprs())
            {
                return CyCustErr.OK;
            }

            CyCompDevParam param = instEdit.GetCommittedParam(paramName);
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }
        #endregion

        #region Events
        /// <summary>
        /// An event that clients can use to be notified whenever the PSoC Creator design updates.
        /// </summary>
        public event EventHandler DesignUpdated;

        public void OnDesignUpdated(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            OnDesignUpdated(EventArgs.Empty);
        }

        // Invoke the DesignUpdates event; called whenever PSoC Creator design updates.
        protected virtual void OnDesignUpdated(EventArgs e)
        {
            if (DesignUpdated != null)
                DesignUpdated(this, e);
        }
        #endregion

        #region Clock
        /// <summary>
        /// Gets external or internal clock frequency depending whether clock from terminal is selected.
        /// </summary>
        /// <returns>External or internal clock frequency in kHz.</returns>
        public double GetClockKhz()
        {
            return ClockFromTerminal ? GetExternalClockKhz(TermQuery) : GetInternalClockKhz(TermQuery);
        }

        /// <summary>
        /// Returns internal clock value.
        /// </summary>
        public static double GetInternalClockKhz(ICyTerminalQuery_v1 termQuery)
        {
            return CyClock.GetInternalClockKhz(termQuery, SCB_CLOCK_SCBCLK);
        }

        /// <summary>
        /// Returns external (from terminal) clock value.
        /// </summary>
        public static double GetExternalClockKhz(ICyTerminalQuery_v1 termQuery)
        {
            return CyClock.GetExternalClockKhz(termQuery, SCB_CLOCK_TERM);
        }

        private static CyClockData GetClockData(ICyTerminalQuery_v1 termQuery, string termName, bool internalClock)
        {
            List<CyClockData> clkdata = internalClock ? termQuery.GetClockData(termName, "term1", 0) :
                                                        termQuery.GetClockData(termName, 0);
            return (clkdata.Count > 0) ? clkdata[0] : null;
        }

        public static CyClockData GetInternalClockData(ICyTerminalQuery_v1 termQuery)
        {
            return GetClockData(termQuery, SCB_CLOCK_SCBCLK, true);
        }

        public static CyClockData GetExternalClockData(ICyTerminalQuery_v1 termQuery)
        {
            return GetClockData(termQuery, SCB_CLOCK_TERM, false);
        }
        #endregion

        #region Data rate
        public double GetActualDataRate(uint customOvsFactor)
        {
            double actualDataRate = CyClock.UNKNOWN_FREQUENCY;
            uint ovsFactor = customOvsFactor > 0 ? customOvsFactor : OvsFactor;
            double clkFreq = GetClockKhz();

            if (CyClock.IsFrequencyKnown(clkFreq))
            {
                if (ovsFactor > 0)
                {
                    actualDataRate = Math.Round(clkFreq / ovsFactor, 3);
                }
            }

            return actualDataRate;
        }

        public double GetActualDataRate()
        {
            return GetActualDataRate(0);
        }
        #endregion
    }
}
