/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.ComponentModel;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace SCB_SPI_PDL_v2_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        public const string DATA_RATE = "DataRate";
        public const string BITS_ORDER = "BitsOrder";
        public const string CLOCK_FROM_TERM = "ClockFromTerm";
        public const string DEASSERT_SS = "DeassertSelectLine";
        public const string ENABLE_FREE_RUN_SCLK = "EnableFreeRunSclk";
        public const string ENABLE_INPUT_FILTER = "EnableInputFilter";
        public const string ENABLE_LATE_MISO_SAMPLE = "EnableLateMisoSample";
        public const string ENABLE_RX_OUTPUT = "EnableRxOutput";
        public const string ENABLE_TX_OUTPUT = "EnableTxOutput";
        public const string ENABLE_WAKEUP = "EnableWakeup";
        public const string INTERRUPT_MODE = "InterruptMode";
        public const string INTERRUPT_ON_SPI_DONE = "IntrMasterSpiDone";
        public const string INTERRUPT_ON_RX_FULL = "IntrRxFull";
        public const string INTERRUPT_ON_RX_NOT_EMPTY = "IntrRxNotEmpty";
        public const string INTERRUPT_ON_RX_OVERFLOW = "IntrRxOverflow";
        public const string INTERRUPT_ON_RX_TRIGGER = "IntrRxTrigger";
        public const string INTERRUPT_ON_RX_UNDERFLOW = "IntrRxUnderflow";
        public const string INTERRUPT_ON_SPI_BUS_ERROR = "IntrSlaveBusError";
        public const string INTERRUPT_ON_TX_EMPTY = "IntrTxEmpty";
        public const string INTERRUPT_ON_TX_NOT_FULL = "IntrTxNotFull";
        public const string INTERRUPT_ON_TX_OVER_FLOW = "IntrTxOverflow";
        public const string INTERRUPT_ON_TX_TRIGGER = "IntrTxTrigger";
        public const string INTERRUPT_ON_TX_WAKEUP = "IntrWakeup";
        public const string INTERRUPT_ON_TX_UNDER_FLOW = "IntrTxUnderflow";
        public const string MODE = "Mode";
        public const string RX_DATA_WIDTH = "RxDataWidth";
        public const string SELECT_LINES_NUMBER = "SelectLinesNumber";
        public const string TX_DATA_WIDTH = "TxDataWidth";
        public const string OVS_FACTOR = "OvsFactor";
        public const string REMOVE_MISO = "RemoveMiso";
        public const string REMOVE_MOSI = "RemoveMosi";
        public const string REMOVE_SCLK = "RemoveSclk";
        public const string RX_BUFFER_TRIGGER_LEVEL = "RxTriggerLevel";
        public const string SCLK_MODE = "SclkMode";
        public const string SHOW_TERMINALS = "ShowTerminals";
        public const string SS0_POLARITY = "Ss0Polarity";
        public const string SS1_POLARITY = "Ss1Polarity";
        public const string SS2_POLARITY = "Ss2Polarity";
        public const string SS3_POLARITY = "Ss3Polarity";
        public const string SPI_SUB_MODE = "SubMode";
        public const string TX_BUFFER_TRIGGER_LEVEL = "TxTriggerLevel";

        // Local parameters
        public const string IS_DMA_CAPABLE = "IsDmaCapable";
        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Component Parameters Ranges
    public class CyParamRanges
    {
        public const double EPS = 1E-5;

        public const byte CLOCK_CYCLES_TO_OUTPUT_NOMEDFILTER = 3;
        public const byte CLOCK_CYCLES_TO_OUTPUT_MEDFILTER = 4;
        
        // Maximum PERICLK Frequency
        public const uint PERICLK_MAX_FREQ = 100000;

        // 002-10490 Rev. *C: SID166A (units MHz)
        public const uint F_SPI_SLAVE_IC = 15;

        // 002-10490 Rev. *C: SID171 (units ns)
        public const uint TDSO = 50;

        // Tdso = Tdso_internal + (3 * Tscbclk), where Tscbclk = 10ns (units ns)
        public const uint T_DSO_INTERNAL = TDSO - 3 * 10;

        // Calculate time left for master delays to meet SID166A FSPI_IC
        public const double T_MASTER_DELAYS = (1000.0 / F_SPI_SLAVE_IC) - TDSO;
    }
    #endregion

    #region Enums
    public enum CyESCLKModeType
    {
        [Description("CPHA = 0, CPOL = 0")]
        MODE_00 = 0,
        [Description("CPHA = 1, CPOL = 0")]
        MODE_10 = 1,
        [Description("CPHA = 0, CPOL = 1")]
        MODE_01 = 2,
        [Description("CPHA = 1, CPOL = 1")]
        MODE_11 = 3
    }

    public enum CyEModeType
    {
        [Description("Slave")]
        SPI_SLAVE,
        [Description("Master")]
        SPI_MASTER
    }

    public enum CyESubModeType
    {
        [Description("National Semiconductor (Microware)")]
        NS = 2,
        [Description("Motorola")]
        MOTOROLA = 0,
        [Description("TI (Start coincides)")]
        TI_COINCIDES = 1,
        [Description("TI (Start precedes)")]
        TI_PRECEDES = 17
    }

    public enum CyEBitOrderType
    {
        [Description("MSB first")]
        MSB_FIRST = 1,
        [Description("LSB first")]
        LSB_FIRST = 0
    }

    public enum CyEInterruptModeType { INTERNAL = 1, EXTERNAL = 2 }
    public enum CyEActivePolarityType { ACTIVE_LOW, ACTIVE_HIGH }
    public enum CyETolerance : ushort
    {
        DEFAULT = 5, 
        ZERO_ACCURACY = 0,
        MINUS_MAX = 100, 
        PLUS_MAX = 1000 
    }
    #endregion

    public class CyParameters
    {
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

        #region Events
        /// <summary>
        /// An event that clients can use to be notified whenever the PSoC Creator design updates.
        /// </summary>
        public event EventHandler DesignUpdated;

        // Invoke the DesignUpdates event; called whenever PSoC Creator design updates.
        protected virtual void OnDesignUpdates(EventArgs e)
        {
            EventHandler handler = DesignUpdated;
            if (handler != null)
                handler(this, e);
        }

        public void UpdateDesigns(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            OnDesignUpdates(EventArgs.Empty);
        }
        #endregion

        #region Properties
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

        #region Basic tab parameters
        public CyEModeType Mode
        {
            get { return GetValue<CyEModeType>(CyParamNames.MODE); }
            set { SetValue(CyParamNames.MODE, value); }
        }

        public CyESubModeType SubMode
        {
            get { return GetValue<CyESubModeType>(CyParamNames.SPI_SUB_MODE); }
            set { SetValue(CyParamNames.SPI_SUB_MODE, value); }
        }

        public CyESCLKModeType SclkMode
        {
            get { return GetValue<CyESCLKModeType>(CyParamNames.SCLK_MODE); }
            set { SetValue(CyParamNames.SCLK_MODE, value); }
        }

        public CyEBitOrderType BitsOrder
        {
            get { return GetValue<CyEBitOrderType>(CyParamNames.BITS_ORDER); }
            set { SetValue(CyParamNames.BITS_ORDER, value); }
        }

        public CyEActivePolarityType Ss0Polarity
        {
            get { return GetValue<CyEActivePolarityType>(CyParamNames.SS0_POLARITY); }
            set { SetValue(CyParamNames.SS0_POLARITY, value); }
        }

        public CyEActivePolarityType Ss1Polarity
        {
            get { return GetValue<CyEActivePolarityType>(CyParamNames.SS1_POLARITY); }
            set { SetValue(CyParamNames.SS1_POLARITY, value); }
        }

        public CyEActivePolarityType Ss2Polarity
        {
            get { return GetValue<CyEActivePolarityType>(CyParamNames.SS2_POLARITY); }
            set { SetValue(CyParamNames.SS2_POLARITY, value); }
        }

        public CyEActivePolarityType Ss3Polarity
        {
            get { return GetValue<CyEActivePolarityType>(CyParamNames.SS3_POLARITY); }
            set { SetValue(CyParamNames.SS3_POLARITY, value); }
        }

        public byte RxWordWidth
        {
            get { return GetValue<byte>(CyParamNames.RX_DATA_WIDTH); }
            set { SetValue(CyParamNames.RX_DATA_WIDTH, value); }
        }

        public byte NumberOfSSLines
        {
            get { return GetValue<byte>(CyParamNames.SELECT_LINES_NUMBER); }
            set { SetValue(CyParamNames.SELECT_LINES_NUMBER, value); }
        }
        public byte TxWordWidth
        {
            get { return GetValue<byte>(CyParamNames.TX_DATA_WIDTH); }
            set { SetValue(CyParamNames.TX_DATA_WIDTH, value); }
        }

        public byte OvsFactor
        {
            get { return GetValue<byte>(CyParamNames.OVS_FACTOR); }
            set { SetValue(CyParamNames.OVS_FACTOR, value); }
        }

        public bool ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.CLOCK_FROM_TERM); }
            set { SetValue(CyParamNames.CLOCK_FROM_TERM, value); }
        }

        public uint DataRateKhz
        {
            get { return GetValue<uint>(CyParamNames.DATA_RATE); }
            set { SetValue(CyParamNames.DATA_RATE, value); }
        }

        public bool EnableInputGlitchFilter
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_INPUT_FILTER); }
            set { SetValue(CyParamNames.ENABLE_INPUT_FILTER, value); }
        }

        public bool DeassertSs
        {
            get { return GetValue<bool>(CyParamNames.DEASSERT_SS); }
            set { SetValue(CyParamNames.DEASSERT_SS, value); }
        }

        public bool EnableSclkFreeRunning
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_FREE_RUN_SCLK); }
            set { SetValue(CyParamNames.ENABLE_FREE_RUN_SCLK, value); }
        }

        public bool EnableLateMisoSample
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_LATE_MISO_SAMPLE); }
            set { SetValue(CyParamNames.ENABLE_LATE_MISO_SAMPLE, value); }
        }

        public bool EnableWakeupFromSleepMode
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_WAKEUP); }
            set { SetValue(CyParamNames.ENABLE_WAKEUP, value); }
        }
        #endregion

        #region Advanced tab parameters
        public CyEInterruptModeType InterruptMode
        {
            get { return GetValue<CyEInterruptModeType>(CyParamNames.INTERRUPT_MODE); }
            set { SetValue(CyParamNames.INTERRUPT_MODE, value); }
        }

        public byte RxFifoLevel
        {
            get { return GetValue<byte>(CyParamNames.RX_BUFFER_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.RX_BUFFER_TRIGGER_LEVEL, value); }
        }

        public byte TxFifoLevel
        {
            get { return GetValue<byte>(CyParamNames.TX_BUFFER_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.TX_BUFFER_TRIGGER_LEVEL, value); }
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

        // RX interrupts
        public bool InterruptOnSPIBusError
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_SPI_BUS_ERROR); }
            set { SetValue(CyParamNames.INTERRUPT_ON_SPI_BUS_ERROR, value); }
        }
        public bool InterruptOnRXFull
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_RX_FULL); }
            set { SetValue(CyParamNames.INTERRUPT_ON_RX_FULL, value); }
        }
        public bool InterruptOnRXNotEmpty
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_RX_NOT_EMPTY); }
            set { SetValue(CyParamNames.INTERRUPT_ON_RX_NOT_EMPTY, value); }
        }
        public bool InterruptOnRXOverflow
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_RX_OVERFLOW); }
            set { SetValue(CyParamNames.INTERRUPT_ON_RX_OVERFLOW, value); }
        }
        public bool InterruptOnRxFifoAboveLevel
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_RX_TRIGGER); }
            set { SetValue(CyParamNames.INTERRUPT_ON_RX_TRIGGER, value); }
        }
        public bool InterruptOnRXUnderflow
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_RX_UNDERFLOW); }
            set { SetValue(CyParamNames.INTERRUPT_ON_RX_UNDERFLOW, value); }
        }

        // TX interrupts
        public bool InterruptOnSPIDone
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_SPI_DONE); }
            set { SetValue(CyParamNames.INTERRUPT_ON_SPI_DONE, value); }
        }

        public bool InterruptOnTXEmpty
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_TX_EMPTY); }
            set { SetValue(CyParamNames.INTERRUPT_ON_TX_EMPTY, value); }
        }

        public bool InterruptOnTXNotFull
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_TX_NOT_FULL); }
            set { SetValue(CyParamNames.INTERRUPT_ON_TX_NOT_FULL, value); }
        }

        public bool InterruptOnTXOverflow
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_TX_OVER_FLOW); }
            set { SetValue(CyParamNames.INTERRUPT_ON_TX_OVER_FLOW, value); }
        }

        public bool InterruptOnTxFifoBelowLevel
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_TX_TRIGGER); }
            set { SetValue(CyParamNames.INTERRUPT_ON_TX_TRIGGER, value); }
        }

        public bool InterruptOnWakeup
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_TX_WAKEUP); }
            set { SetValue(CyParamNames.INTERRUPT_ON_TX_WAKEUP, value); }
        }

        public bool InterruptOnTXUnderflow
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_TX_UNDER_FLOW); }
            set { SetValue(CyParamNames.INTERRUPT_ON_TX_UNDER_FLOW, value); }
        }
        #endregion

        #region Pin tab parameters
        public bool ShowTerm
        {
            get { return GetValue<bool>(CyParamNames.SHOW_TERMINALS); }
            set { SetValue(CyParamNames.SHOW_TERMINALS, value); }
        }

        public bool RemoveSclk
        {
            get { return GetValue<bool>(CyParamNames.REMOVE_SCLK); }
            set { SetValue(CyParamNames.REMOVE_SCLK, value); }
        }

        public bool RemoveMiso
        {
            get { return GetValue<bool>(CyParamNames.REMOVE_MISO); }
            set { SetValue(CyParamNames.REMOVE_MISO, value); }
        }

        public bool RemoveMosi
        {
            get { return GetValue<bool>(CyParamNames.REMOVE_MOSI); }
            set { SetValue(CyParamNames.REMOVE_MOSI, value); }
        }
        #endregion

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
            if (instQuery == null) return default(T);
            T value;
            CyCustErr err = instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
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

            string valueToSet = "";
            if (value != null)
            {
                valueToSet = value.ToString();

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

        #region Clock
        /// <summary>
        /// Gets external or internal clock frequency depending whether clock from terminal is selected.
        /// </summary>
        /// <returns>External or internal clock frequency in kHz.</returns>
        public double GetClockKHz()
        {
            return ClockFromTerminal ? GetExternalClockKHz(TermQuery) : GetInternalClockKHz(TermQuery);
        }

        /// <summary>
        /// Gets internal clock value.
        /// </summary>
        public static double GetInternalClockKHz(ICyTerminalQuery_v1 termQuery)
        {
            return CyClock.GetInternalClockKhz(termQuery, "or_sclk");
        }

        public static double GetExternalClockKHz(ICyTerminalQuery_v1 termQuery)
        {
            return CyClock.GetExternalClockKhz(termQuery, "clock");
        }
        #endregion

        #region Data rate
        public double GetActualDataRate()
        {
            double actualDataRate = CyClock.UNKNOWN_FREQUENCY;
            double clkFreq = GetClockKHz();

            try
            {
                if (CyClock.IsFrequencyKnown(clkFreq))
                {
                    // SPI Slave
                    if (Mode == CyEModeType.SPI_SLAVE)
                    {
                        byte scbClocksToOutput = GetClockCyclesToOutput(EnableInputGlitchFilter);

                        // Get tDSO based on SCB clock (units ns)
                        double tDSO = (scbClocksToOutput * (1000000 / clkFreq));

                        // Get SCL to MISO round trip delay (units ns)
                        double spiRoundTripDelay = tDSO + CyParamRanges.T_DSO_INTERNAL + CyParamRanges.T_MASTER_DELAYS;

                        // Get actual data rate (units kHz)
                        actualDataRate = Math.Round(1000000 / (2 * spiRoundTripDelay), 3);

                    }
                    // SPI Master
                    else
                    {
                        if (OvsFactor > 0)
                        {
                            actualDataRate = Math.Round(clkFreq / OvsFactor, 3);
                        }
                    }
                }
            }
            catch (DivideByZeroException)
            {
                actualDataRate = CyClock.UNKNOWN_FREQUENCY;
            }

            return actualDataRate;
        }

        public double GetActualTdso()
        {
            double actualTdso = CyClock.UNKNOWN_FREQUENCY;
            double clkFreq = GetClockKHz();

            try
            {
                if (CyClock.IsFrequencyKnown(clkFreq))
                {
                    // SPI Slave
                    if (Mode == CyEModeType.SPI_SLAVE)
                    {
                        byte scbClocksToOutput = GetClockCyclesToOutput(EnableInputGlitchFilter);

                        // Get tDSO based on SCB clock (units ns)
                        actualTdso = Math.Ceiling(CyParamRanges.T_DSO_INTERNAL + (scbClocksToOutput * (1000000 / clkFreq)));
                    }
                }
            }
            catch (DivideByZeroException)
            {
                actualTdso = CyClock.UNKNOWN_FREQUENCY;
            }

            return actualTdso;
        }

        public static byte GetClockCyclesToOutput(bool inputGlitchFilter)
        {
            return inputGlitchFilter
                ? CyParamRanges.CLOCK_CYCLES_TO_OUTPUT_MEDFILTER
                : CyParamRanges.CLOCK_CYCLES_TO_OUTPUT_NOMEDFILTER;
        }
        #endregion
    }
}
