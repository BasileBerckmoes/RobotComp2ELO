/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit;
using I2S_PDL_v2_0.Utils;

namespace I2S_PDL_v2_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        // common parameters
        public const string CLOCK_FROM_TERM = "ExtClk";
        public const string CLOCK_DIV = "ClockDiv";
        public const string LINK_RX_TO_TX = "LinkRxToTx";

        // RX parameters
        public const string RX_ALIGNMENT = "RxAlignment";
        public const string RX_CHANNEL_LENGTH = "RxChannelLength";
        public const string RX_CHANNELS = "RxChannels";
        public const string RX_DMA_TRIGGER = "RxDmaTrigger";
        public const string RX_ENABLED = "RxEnabled";
        public const string RX_MODE = "RxMasterMode";
        public const string RX_WORD_LENGTH = "RxWordLength";
        public const string RX_WS_PULSE_WIDTH = "RxWsPulseWidth";
        public const string RX_SIGN_EXTENSION = "RxSignExtension";
        public const string RX_FIFO_TRIGGER_LEVEL = "RxFifoTriggerLevel";
        public const string RX_SDI_RISING_EDGE = "RxSdiLatchingTime";
        public const string RX_WATCHDOG_ENABLE = "RxWatchdogEnable";
        public const string RX_WATCHDOG_VALUE = "RxWatchdogValue";
        public const string RX_INPUT_CLOCK_POLARITY = "RxSckiPolarity";
        public const string RX_OUTPUT_CLOCK_POLARITY = "RxSckoPolarity";
        // RX interrupts
        public const string RX_FULL_INT = "RxFull";
        public const string RX_NOT_EMPTY_INT = "RxNotEmpty";
        public const string RX_OVERFLOW_INT = "RxOverflow";
        public const string RX_TRIGGER_INT = "RxTrig";
        public const string RX_UNDERFLOW_INT = "RxUnderflow";
        public const string RX_WATCHDOG_INT = "RxWd";

        // TX parameters
        public const string TX_ALIGNMENT = "TxAlignment";
        public const string TX_CHANNEL_LENGTH = "TxChannelLength";
        public const string TX_CHANNELS = "TxChannels";
        public const string TX_DMA_TRIGGER = "TxDmaTrigger";
        public const string TX_ENABLED = "TxEnabled";
        public const string TX_MODE = "TxMasterMode";
        public const string TX_WORD_LENGTH = "TxWordLength";
        public const string TX_WS_PULSE_WIDTH = "TxWsPulseWidth";
        public const string TX_FIFO_TRIGGER_LEVEL = "TxFifoTriggerLevel";
        public const string TX_OVERHEAD_VALUE = "TxOverheadValue";
        public const string TX_SDO_RISING_EDGE = "TxSdoLatchingTime";
        public const string TX_WATCHDOG_ENABLE = "TxWatchdogEnable";
        public const string TX_WATCHDOG_VALUE = "TxWatchdogValue";
        public const string TX_INPUT_CLOCK_POLARITY = "TxSckiPolarity";
        public const string TX_OUTPUT_CLOCK_POLARITY = "TxSckoPolarity";
        // TX interrupts
        public const string TX_EMPTY_INT = "TxEmpty";
        public const string TX_NOT_FULL_INT = "TxNotFull";
        public const string TX_OVERFLOW_INT = "TxOverflow";
        public const string TX_TRIGGER_INT = "TxTrig";
        public const string TX_UNDERFLOW_INT = "TxUnderflow";
        public const string TX_WATCHDOG_INT = "TxWd";
    }
    #endregion

    public class CyParameters
    {
        #region Private fields
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        #endregion

        #region Events declaration
        /// <summary>
        /// An event that clients can use to be notified whenever the PSoC Creator design updates.
        /// </summary>
        public event EventHandler DesignUpdates;
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
        /// During first getting of parameters this variable is false, what means that assigning
        /// values to form controls will not immediately overwrite parameters with the same values.
        /// </summary>
        public bool GlobalEditMode { get; set; }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        //
        // Common parameters properties
        //
        public bool ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.CLOCK_FROM_TERM); }
            set { SetValue(CyParamNames.CLOCK_FROM_TERM, value); }
        }

        public int ClockDivider
        {
            get { return GetValue<int>(CyParamNames.CLOCK_DIV); }
            set { SetValue(CyParamNames.CLOCK_DIV, value); }
        }

        //
        // TX parameters properties
        //
        public bool TxEnabled
        {
            get { return GetValue<bool>(CyParamNames.TX_ENABLED); }
            set { SetValue(CyParamNames.TX_ENABLED, value); }
        }

        public int TxChannels
        {
            get { return GetValue<int>(CyParamNames.TX_CHANNELS); }
            set { SetValue(CyParamNames.TX_CHANNELS, value); }
        }

        public CyDataLength TxChannelLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.TX_CHANNEL_LENGTH); }
            set { SetValue(CyParamNames.TX_CHANNEL_LENGTH, value); }
        }

        public CyDataLength TxWordLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.TX_WORD_LENGTH); }
            set { SetValue(CyParamNames.TX_WORD_LENGTH, value); }
        }

        public CyMode TxMode
        {
            get { return GetValue<CyMode>(CyParamNames.TX_MODE); }
            set { SetValue(CyParamNames.TX_MODE, value); }
        }

        public CyAlignment TxAlignment
        {
            get { return GetValue<CyAlignment>(CyParamNames.TX_ALIGNMENT); }
            set { SetValue(CyParamNames.TX_ALIGNMENT, value); }
        }

        public CyWsPulseWidth TxWsPulseWidth
        {
            get { return GetValue<CyWsPulseWidth>(CyParamNames.TX_WS_PULSE_WIDTH); }
            set { SetValue(CyParamNames.TX_WS_PULSE_WIDTH, value); }
        }

        public CySdoLatchingTime TxSdo
        {
            get { return GetValue<CySdoLatchingTime>(CyParamNames.TX_SDO_RISING_EDGE); }
            set { SetValue(CyParamNames.TX_SDO_RISING_EDGE, value); }
        }

        public int TxOverheadValue
        {
            get { return GetValue<int>(CyParamNames.TX_OVERHEAD_VALUE); }
            set { SetValue(CyParamNames.TX_OVERHEAD_VALUE, value); }
        }

        public byte TxFifoTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.TX_FIFO_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.TX_FIFO_TRIGGER_LEVEL, value); }
        }

        public bool TxDmaTrigger
        {
            get { return GetValue<bool>(CyParamNames.TX_DMA_TRIGGER); }
            set { SetValue(CyParamNames.TX_DMA_TRIGGER, value); }
        }

        public bool TxTriggerInt
        {
            get { return GetValue<bool>(CyParamNames.TX_TRIGGER_INT); }
            set { SetValue(CyParamNames.TX_TRIGGER_INT, value); }
        }

        public bool TxNotFullInt
        {
            get { return GetValue<bool>(CyParamNames.TX_NOT_FULL_INT); }
            set { SetValue(CyParamNames.TX_NOT_FULL_INT, value); }
        }

        public bool TxEmptyInt
        {
            get { return GetValue<bool>(CyParamNames.TX_EMPTY_INT); }
            set { SetValue(CyParamNames.TX_EMPTY_INT, value); }
        }

        public bool TxOverflowInt
        {
            get { return GetValue<bool>(CyParamNames.TX_OVERFLOW_INT); }
            set { SetValue(CyParamNames.TX_OVERFLOW_INT, value); }
        }

        public bool TxUnderflowInt
        {
            get { return GetValue<bool>(CyParamNames.TX_UNDERFLOW_INT); }
            set { SetValue(CyParamNames.TX_UNDERFLOW_INT, value); }
        }

        public bool TxWatchdogInt
        {
            get { return GetValue<bool>(CyParamNames.TX_WATCHDOG_INT); }
            set { SetValue(CyParamNames.TX_WATCHDOG_INT, value); }
        }

        public bool TxWatchdogEnable
        {
            get { return GetValue<bool>(CyParamNames.TX_WATCHDOG_ENABLE); }
            set { SetValue(CyParamNames.TX_WATCHDOG_ENABLE, value); }
        }

        public uint TxWatchdogValue
        {
            get { return GetValue<uint>(CyParamNames.TX_WATCHDOG_VALUE); }
            set { SetValue(CyParamNames.TX_WATCHDOG_VALUE, value); }
        }

        public CySckPolarity TxInputClockPolarity
        {
            get { return GetValue<CySckPolarity>(CyParamNames.TX_INPUT_CLOCK_POLARITY); }
            set { SetValue(CyParamNames.TX_INPUT_CLOCK_POLARITY, value); }
        }

        public CySckPolarity TxOutputClockPolarity
        {
            get { return GetValue<CySckPolarity>(CyParamNames.TX_OUTPUT_CLOCK_POLARITY); }
            set { SetValue(CyParamNames.TX_OUTPUT_CLOCK_POLARITY, value); }
        }

        //
        // RX parameters properties
        //
        public bool RxEnabled
        {
            get { return GetValue<bool>(CyParamNames.RX_ENABLED); }
            set { SetValue(CyParamNames.RX_ENABLED, value); }
        }

        public int RxChannels
        {
            get { return GetValue<int>(CyParamNames.RX_CHANNELS); }
            set { SetValue(CyParamNames.RX_CHANNELS, value); }
        }

        public CyDataLength RxChannelLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.RX_CHANNEL_LENGTH); }
            set { SetValue(CyParamNames.RX_CHANNEL_LENGTH, value); }
        }

        public CyDataLength RxWordLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.RX_WORD_LENGTH); }
            set { SetValue(CyParamNames.RX_WORD_LENGTH, value); }
        }

        public CyMode RxMode
        {
            get { return GetValue<CyMode>(CyParamNames.RX_MODE); }
            set { SetValue(CyParamNames.RX_MODE, value); }
        }

        public CyAlignment RxAlignment
        {
            get { return GetValue<CyAlignment>(CyParamNames.RX_ALIGNMENT); }
            set { SetValue(CyParamNames.RX_ALIGNMENT, value); }
        }

        public CyWsPulseWidth RxWsPulseWidth
        {
            get { return GetValue<CyWsPulseWidth>(CyParamNames.RX_WS_PULSE_WIDTH); }
            set { SetValue(CyParamNames.RX_WS_PULSE_WIDTH, value); }
        }

        public CySdiLatchingTime RxSdi
        {
            get { return GetValue<CySdiLatchingTime>(CyParamNames.RX_SDI_RISING_EDGE); }
            set { SetValue(CyParamNames.RX_SDI_RISING_EDGE, value); }
        }

        public CySignExtension RxSignExtension
        {
            get { return GetValue<CySignExtension>(CyParamNames.RX_SIGN_EXTENSION); }
            set { SetValue(CyParamNames.RX_SIGN_EXTENSION, value); }
        }

        public byte RxFifoTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.RX_FIFO_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.RX_FIFO_TRIGGER_LEVEL, value); }
        }

        public bool RxDmaTrigger
        {
            get { return GetValue<bool>(CyParamNames.RX_DMA_TRIGGER); }
            set { SetValue(CyParamNames.RX_DMA_TRIGGER, value); }
        }

        public bool RxTriggerInt
        {
            get { return GetValue<bool>(CyParamNames.RX_TRIGGER_INT); }
            set { SetValue(CyParamNames.RX_TRIGGER_INT, value); }
        }

        public bool RxNotEmptyInt
        {
            get { return GetValue<bool>(CyParamNames.RX_NOT_EMPTY_INT); }
            set { SetValue(CyParamNames.RX_NOT_EMPTY_INT, value); }
        }

        public bool RxFullInt
        {
            get { return GetValue<bool>(CyParamNames.RX_FULL_INT); }
            set { SetValue(CyParamNames.RX_FULL_INT, value); }
        }

        public bool RxOverflowInt
        {
            get { return GetValue<bool>(CyParamNames.RX_OVERFLOW_INT); }
            set { SetValue(CyParamNames.RX_OVERFLOW_INT, value); }
        }

        public bool RxUnderflowInt
        {
            get { return GetValue<bool>(CyParamNames.RX_UNDERFLOW_INT); }
            set { SetValue(CyParamNames.RX_UNDERFLOW_INT, value); }
        }

        public bool RxWatchdogInt
        {
            get { return GetValue<bool>(CyParamNames.RX_WATCHDOG_INT); }
            set { SetValue(CyParamNames.RX_WATCHDOG_INT, value); }
        }

        public bool RxWatchdogEnable
        {
            get { return GetValue<bool>(CyParamNames.RX_WATCHDOG_ENABLE); }
            set { SetValue(CyParamNames.RX_WATCHDOG_ENABLE, value); }
        }

        public uint RxWatchdogValue
        {
            get { return GetValue<uint>(CyParamNames.RX_WATCHDOG_VALUE); }
            set { SetValue(CyParamNames.RX_WATCHDOG_VALUE, value); }
        }

        public CySckPolarity RxInputClockPolarity
        {
            get { return GetValue<CySckPolarity>(CyParamNames.RX_INPUT_CLOCK_POLARITY); }
            set { SetValue(CyParamNames.RX_INPUT_CLOCK_POLARITY, value); }
        }

        public CySckPolarity RxOutputClockPolarity
        {
            get { return GetValue<CySckPolarity>(CyParamNames.RX_OUTPUT_CLOCK_POLARITY); }
            set { SetValue(CyParamNames.RX_OUTPUT_CLOCK_POLARITY, value); }
        }

        // Calculated properties
        public byte MaxRxFifoTriggerLevel
        {
            get { return (byte)(CyConstants.FIFO_TRIGGER_LEVEL_MAX - RxChannels); }
        }
        #endregion

        #region Events
        // Invoke the DesignUpdates event; called whenever PSoC Creator design updates.
        protected virtual void OnDesignUpdates(EventArgs e)
        {
            if (DesignUpdates != null)
                DesignUpdates(this, e);
        }

        public void UpdateDesigns(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            OnDesignUpdates(EventArgs.Empty);
        }
        #endregion

        #region Getting / Setting Parameters
        public T GetValue<T>(string paramName)
        {
            return CyParamUtils.GetValue<T>(m_instQuery, paramName);
        }

        public void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode)
            {
                CyParamUtils.SetValue(m_instEdit, paramName, value);
            }
        }
        #endregion
    }
}
