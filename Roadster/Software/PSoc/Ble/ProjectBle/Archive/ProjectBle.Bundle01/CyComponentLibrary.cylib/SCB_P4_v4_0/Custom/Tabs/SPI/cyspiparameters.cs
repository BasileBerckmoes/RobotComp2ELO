/*******************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using System.ComponentModel;

namespace SCB_P4_v4_0
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string SPI_BITS_ORDER = "SpiBitsOrder";
        public const string SPI_BIT_RATE = "SpiBitRate";
        public const string SPI_ENABLE_MEDIAN_FILTER = "SpiMedianFilterEnable";
        public const string SPI_ENABLE_BYTE_MODE = "SpiByteModeEnable";
        public const string SPI_FREE_RUNNING_SCLK = "SpiFreeRunningSclk";
        public const string SPI_ENABLE_LATE_MISO_SAMPLE = "SpiLateMisoSampleEnable";
        public const string SPI_ENABLE_WAKEUP_FROM_SLEEP_MODE = "SpiWakeEnable";
        public const string SPI_CLOCK_FROM_TERM = "SpiClockFromTerm";

        public const string SPI_INTERRUPT_MODE = "SpiInterruptMode";
        public const string SPI_INTERRUPT_ON_RX_FULL = "SpiIntrRxFull";
        public const string SPI_INTERRUPT_ON_RX_NOT_EMPTY = "SpiIntrRxNotEmpty";
        public const string SPI_INTERRUPT_ON_RX_OVER_FLOW = "SpiIntrRxOverflow";

        public const string SPI_INTERRUPT_ON_RX_TRIGGER = "SpiIntrRxTrigger";
        public const string SPI_INTERRUPT_ON_RX_UNDER_FLOW = "SpiIntrRxUnderflow";
        public const string SPI_INTERRUPT_ON_SPI_DONE = "SpiIntrMasterSpiDone";
        public const string SPI_INTERRUPT_ON_SPI_BUS_ERROR = "SpiIntrSlaveBusError";
        public const string SPI_INTERRUPT_ON_TX_EMPTY = "SpiIntrTxEmpty";

        public const string SPI_INTERRUPT_ON_TX_NOT_FULL = "SpiIntrTxNotFull";

        public const string SPI_INTERRUPT_ON_TX_OVER_FLOW = "SpiIntrTxOverflow";
        public const string SPI_INTERRUPT_ON_TX_TRIGGER = "SpiIntrTxTrigger";
        public const string SPI_INTERRUPT_ON_TX_UNDER_FLOW = "SpiIntrTxUnderflow";
        public const string SPI_NUMBER_OF_RX_DATA_BITS = "SpiNumberOfRxDataBits";

        public const string SPI_NUMBER_OF_SS_LINES = "SpiNumberOfSelectLines";
        public const string SPI_SS0_POLARITY = "SpiSs0Polarity";
        public const string SPI_SS1_POLARITY = "SpiSs1Polarity";
        public const string SPI_SS2_POLARITY = "SpiSs2Polarity";
        public const string SPI_SS3_POLARITY = "SpiSs3Polarity";

        public const string SPI_NUMBER_OF_TX_DATA_BITS = "SpiNumberOfTxDataBits";
        public const string SPI_OVS_FACTOR = "SpiOvsFactor";
        public const string SPI_RX_BUFFER_SIZE = "SpiRxBufferSize";
        public const string SPI_RX_BUFFER_TRIGGER_LEVEL = "SpiRxTriggerLevel";
        public const string SPI_MODE = "SpiMode";
        public const string SPI_SCLK_MODE = "SpiSclkMode";
        public const string SPI_SUB_MODE = "SpiSubMode";
        public const string SPI_TRANSFER_SEPARATION = "SpiTransferSeparation";
        public const string SPI_TX_BUFFER_SIZE = "SpiTxBufferSize";
        public const string SPI_TX_BUFFER_TRIGGER_LEVEL = "SpiTxTriggerLevel";

        public const string SPI_DMA_TX_OUTPUT = "SpiTxOutputEnable";
        public const string SPI_DMA_RX_OUTPUT = "SpiRxOutputEnable";

        public const string SPI_SMARTIO_ENABLE = "SpiSmartioEnable";

        public const string SPI_REMOVE_SCLK = "SpiRemoveSclk";
        public const string SPI_REMOVE_MISO = "SpiRemoveMiso";
        public const string SPI_REMOVE_MOSI = "SpiRemoveMosi";
    }
    #endregion


    #region Component Parameters Ranges
    public partial class CyParamRanges
    {
        public const byte SPI_OVS_SLAVE_NOMEDFILTER_MIN = 6;
        public const byte SPI_OVS_SLAVE_MEDFILTER_MIN = 8;
        public const byte SPI_OVS_MASTER_MISO_MIN = 6;
        public const byte SPI_OVS_MASTER_NO_MISO_MIN = 2;
        public const byte SPI_OVS_MASTER_MAX = 16;

        public const byte CLOCK_CYCLES_TO_OUTPUT_NOMEDFILTER = 3;
        public const byte CLOCK_CYCLES_TO_OUTPUT_MEDFILTER = 4;

        public const byte SPI_BTLDR_DEFAULT_NUMBER_OF_BITS = 8;
        public const byte SPI_BTLDR_DEFAULT_BIT_RATE_KBPS = 100;
    }
    #endregion

    #region Enums
    public enum CyESPISCLKModeType
    {
        [Description("CPHA = 0, CPOL = 0")]
        MODE_00 = 0,
        [Description("CPHA = 0, CPOL = 1")]
        MODE_01 = 2,
        [Description("CPHA = 1, CPOL = 0")]
        MODE_10 = 1,
        [Description("CPHA = 1, CPOL = 1")]
        MODE_11 = 3
    }

    public enum CyESPIModeType
    {
        [Description("Slave")]
        SPI_SLAVE,
        [Description("Master")]
        SPI_MASTER
    }

    public enum CyESPISubModeType
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
    public enum CyESPITransferSeparationType { SEPARATED, CONTINUOUS }

    public enum CyESPIBitOrderType
    {
        [Description("MSB first")]
        MSB_FIRST = 1,
        [Description("LSB first")]
        LSB_FIRST = 0
    }
    #endregion

    public partial class CyParameters
    {
        #region Fields

        public static ushort[] SPI_DATA_RATE_LIST = new ushort[]
        {
            500,
            1000,
            2000,
            4000,
            6000,
            8000
        };

        public const uint SPI_BOOTLOADER_SUPPORTED_DATA_BITS = 8;
        public const uint SPI_MIN_SS_NUMBER = 0;
        public const uint SPI_MAX_SS_NUMBER = 4;

        public const uint SPI_MIN_DATA_BITS = 4;
        public const uint SPI_MAX_DATA_BITS = 16;
        public const uint SPI_MAX_DATA_BITS_BYTEMODE = 8;

        public const UInt16 SPI_MIN_DATA_RATE = 1;
        public const UInt16 SPI_MAX_DATA_RATE = 8000;

        // Unit constants
        public const UInt16 POW6 = 1000;

        public const uint SPI_MAX_OVERSAMPLING_FACTOR = 16;

        #endregion

        #region Properties
        public bool SPI_ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.SPI_CLOCK_FROM_TERM); }
            set { SetValue(CyParamNames.SPI_CLOCK_FROM_TERM, value); }
        }

        public UInt32? SPI_BitsRateInKHz
        {
            get { return GetValue<UInt32>(CyParamNames.SPI_BIT_RATE); }
            set { SetValue(CyParamNames.SPI_BIT_RATE, value); }
        }

        public CyEInterruptModeType SPI_InterruptMode
        {
            get { return GetValue<CyEInterruptModeType>(CyParamNames.SPI_INTERRUPT_MODE); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_MODE, value); }
        }

        public bool SPI_EnableMedianFilter
        {
            get { return GetValue<bool>(CyParamNames.SPI_ENABLE_MEDIAN_FILTER); }
            set { SetValue(CyParamNames.SPI_ENABLE_MEDIAN_FILTER, value); }
        }

        public bool SPI_EnableByteMode
        {
            get { return GetValue<bool>(CyParamNames.SPI_ENABLE_BYTE_MODE); }
            set { SetValue(CyParamNames.SPI_ENABLE_BYTE_MODE, value); }
        }

        public bool SPI_EnableSclkFreeRunning
        {
            get { return GetValue<bool>(CyParamNames.SPI_FREE_RUNNING_SCLK); }
            set { SetValue(CyParamNames.SPI_FREE_RUNNING_SCLK, value); }
        }

        public bool SPI_EnableLateMISOSample
        {
            get { return GetValue<bool>(CyParamNames.SPI_ENABLE_LATE_MISO_SAMPLE); }
            set { SetValue(CyParamNames.SPI_ENABLE_LATE_MISO_SAMPLE, value); }
        }

        public bool SPI_EnableWakeupFromSleepMode
        {
            get { return GetValue<bool>(CyParamNames.SPI_ENABLE_WAKEUP_FROM_SLEEP_MODE); }
            set { SetValue(CyParamNames.SPI_ENABLE_WAKEUP_FROM_SLEEP_MODE, value); }
        }

        public bool SPI_InterruptOnRXFull
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_RX_FULL); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_RX_FULL, value); }
        }
        public bool SPI_InterruptOnRXNotEmpty
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_RX_NOT_EMPTY); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_RX_NOT_EMPTY, value); }
        }
        public bool SPI_InterruptOnRXOverflow
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_RX_OVER_FLOW); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_RX_OVER_FLOW, value); }
        }
        public bool SPI_InterruptOnRXTrigger
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_RX_TRIGGER); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_RX_TRIGGER, value); }
        }
        public bool SPI_InterruptOnRXUnderflow
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_RX_UNDER_FLOW); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_RX_UNDER_FLOW, value); }
        }
        public bool SPI_InterruptOnSPIDone
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_SPI_DONE); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_SPI_DONE, value); }
        }
        public bool SPI_InterruptOnSPIBusError
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_SPI_BUS_ERROR); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_SPI_BUS_ERROR, value); }
        }
        public bool SPI_InterruptOnTXEmpty
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_TX_EMPTY); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_TX_EMPTY, value); }
        }
        public bool SPI_InterruptOnTXNotFull
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_TX_NOT_FULL); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_TX_NOT_FULL, value); }
        }
        public bool SPI_InterruptOnTXOverflow
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_TX_OVER_FLOW); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_TX_OVER_FLOW, value); }
        }
        public bool SPI_InterruptOnTXTrigger
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_TX_TRIGGER); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_TX_TRIGGER, value); }
        }
        public bool SPI_InterruptOnTXUnderflow
        {
            get { return GetValue<bool>(CyParamNames.SPI_INTERRUPT_ON_TX_UNDER_FLOW); }
            set { SetValue(CyParamNames.SPI_INTERRUPT_ON_TX_UNDER_FLOW, value); }
        }
        public byte? SPI_NumberOfRXDataBits
        {
            get { return GetValue<byte>(CyParamNames.SPI_NUMBER_OF_RX_DATA_BITS); }
            set { SetValue(CyParamNames.SPI_NUMBER_OF_RX_DATA_BITS, value); }
        }
        public byte SPI_NumberOfSSLines
        {
            get { return GetValue<byte>(CyParamNames.SPI_NUMBER_OF_SS_LINES); }
            set { SetValue(CyParamNames.SPI_NUMBER_OF_SS_LINES, value); }
        }
        public byte? SPI_NumberOfTXDataBits
        {
            get { return GetValue<byte>(CyParamNames.SPI_NUMBER_OF_TX_DATA_BITS); }
            set { SetValue(CyParamNames.SPI_NUMBER_OF_TX_DATA_BITS, value); }
        }
        public byte? SPI_OvsFactor
        {
            get { return GetValue<byte>(CyParamNames.SPI_OVS_FACTOR); }
            set { SetValue(CyParamNames.SPI_OVS_FACTOR, value); }
        }
        public UInt32 SPI_RxBufferSize
        {
            get { return GetValue<UInt32>(CyParamNames.SPI_RX_BUFFER_SIZE); }
            set { SetValue(CyParamNames.SPI_RX_BUFFER_SIZE, value); }
        }
        public byte SPI_RxBufferTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.SPI_RX_BUFFER_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.SPI_RX_BUFFER_TRIGGER_LEVEL, value); }
        }
        public CyESPITransferSeparationType SPI_TransferSeparation
        {
            get { return GetValue<CyESPITransferSeparationType>(CyParamNames.SPI_TRANSFER_SEPARATION); }
            set { SetValue(CyParamNames.SPI_TRANSFER_SEPARATION, value); }
        }
        public UInt32 SPI_TxBufferSize
        {
            get { return GetValue<UInt32>(CyParamNames.SPI_TX_BUFFER_SIZE); }
            set { SetValue(CyParamNames.SPI_TX_BUFFER_SIZE, value); }
        }
        public byte SPI_TxBufferTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.SPI_TX_BUFFER_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.SPI_TX_BUFFER_TRIGGER_LEVEL, value); }
        }
        public bool SPI_RxOutput
        {
            get { return GetValue<bool>(CyParamNames.SPI_DMA_RX_OUTPUT); }
            set { SetValue(CyParamNames.SPI_DMA_RX_OUTPUT, value); }
        }
        public bool SPI_TxOutput
        {
            get { return GetValue<bool>(CyParamNames.SPI_DMA_TX_OUTPUT); }
            set { SetValue(CyParamNames.SPI_DMA_TX_OUTPUT, value); }
        }
        public bool SPI_SmartioEnable
        {
            get { return GetValue<bool>(CyParamNames.SPI_SMARTIO_ENABLE); }
            set { SetValue(CyParamNames.SPI_SMARTIO_ENABLE, value); }
        }
        public bool SPI_RemoveSclk
        {
            get { return GetValue<bool>(CyParamNames.SPI_REMOVE_SCLK); }
            set { SetValue(CyParamNames.SPI_REMOVE_SCLK, value); }
        }
        public bool SPI_RemoveMiso
        {
            get { return GetValue<bool>(CyParamNames.SPI_REMOVE_MISO); }
            set { SetValue(CyParamNames.SPI_REMOVE_MISO, value); }
        }
        public bool SPI_RemoveMosi
        {
            get { return GetValue<bool>(CyParamNames.SPI_REMOVE_MOSI); }
            set { SetValue(CyParamNames.SPI_REMOVE_MOSI, value); }
        }

        public bool IsSclkFreeRunningAllowed
        {
            get { return this.IsScbIPV2 && this.m_spiMode.Value == CyESPIModeType.SPI_SLAVE; }
        }

        public byte SpiRxBufferMinSize
        {
            get
            {
                return IsScbIPV2 && SPI_EnableByteMode
                    ? GetByteModeBufferMinSize()
                    : GetBufferMinSize();
            }
        }

        public byte SpiTxBufferMinSize
        {
            get
            {
                return IsScbIPV2 && SPI_EnableByteMode
                    ? GetByteModeBufferMinSize()
                    : GetBufferMinSize();
            }
        }

        public byte SpiMaxTriggerLevel
        {
            get
            {
                return IsScbIPV2 && SPI_EnableByteMode
                    ? CyParamRanges.MAX_TRIGGER_LEVEL_BYTE_MODE
                    : CyParamRanges.MAX_TRIGGER_LEVEL;
            }
        }

        public byte SpiClockCyclesToOutput
        {
            get
            {
                return SPI_EnableMedianFilter
                    ? CyParamRanges.CLOCK_CYCLES_TO_OUTPUT_MEDFILTER
                    : CyParamRanges.CLOCK_CYCLES_TO_OUTPUT_NOMEDFILTER;
            }
        }

        public bool SpiIsRxFifoUsed
        {
            get { return SPI_RxBufferSize <= SpiRxBufferMinSize; }
        }

        public bool SpiIsTxFifoUsed
        {
            get { return SPI_TxBufferSize <= SpiTxBufferMinSize; }
        }
        #endregion

        #region Class Events
        /// <summary>
        /// Event fired when SPI mode is changed.
        /// </summary>
        public event EventHandler<EventArgs> SpiModeChanged;

        /// <summary>
        /// Event fired when SPI pins state on the Pins tab is changed.
        /// </summary>
        public event EventHandler<EventArgs> SpiPinsStateChanged;

        #endregion Class Events

        #region Event Handlers
        /// <summary>
        /// Called when SPI mode is changed.
        /// </summary>
        public void OnSpiModeChanged(object sender, EventArgs e)
        {
            EventHandler<EventArgs> handler = SpiModeChanged;
            if (handler != null)
                handler(sender, e);
        }

        /// <summary>
        /// Called when SPI pins state on the Pins tab is changed.
        /// </summary>
        public void OnSpiPinsStateChanged(object sender, EventArgs e)
        {
            EventHandler<EventArgs> handler = SpiPinsStateChanged;
            if (handler != null)
                handler(sender, e);
        }
        #endregion Event Handlers

        #region Functions
        public uint SpiGetMinOversampling(ref string message)
        {
            if (m_spiMode.Value == CyESPIModeType.SPI_SLAVE)
            {
                if (SPI_EnableMedianFilter == false)
                {
                    message = String.Format(Resources.ErrorMsgMedDisMisoDis,
                        CyParamRanges.SPI_OVS_SLAVE_NOMEDFILTER_MIN, CyParamRanges.SPI_OVS_MASTER_MAX);
                    return CyParamRanges.SPI_OVS_SLAVE_NOMEDFILTER_MIN;
                }
                else
                {
                    message = String.Format(Resources.ErrorMsgMedMisoDis,
                        CyParamRanges.SPI_OVS_SLAVE_MEDFILTER_MIN, CyParamRanges.SPI_OVS_MASTER_MAX);
                    return CyParamRanges.SPI_OVS_SLAVE_MEDFILTER_MIN;
                }
            }
            else
            {
                uint ovsMin = SPI_RemoveMiso
                    ? CyParamRanges.SPI_OVS_MASTER_NO_MISO_MIN
                    : CyParamRanges.SPI_OVS_MASTER_MISO_MIN;

                message = String.Format(SPI_RemoveMiso ? Resources.MsgOvsMasterNoMosiError : Resources.MsgOvsMasterError, 
                    ovsMin, CyParamRanges.SPI_OVS_MASTER_MAX);
                return ovsMin;
            }
        }

        public static string GetTextFromNullableValue<T>(T val)
        {
            return (val == null) ? String.Empty : val.ToString();
        }

        public List<CyCustErr> GetSpiDrcErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();

            if (IsScbIPV0)
            {
                // Check SPI SCLK free running
                if (SPI_EnableSclkFreeRunning && IsSclkFreeRunningAllowed == false)
                {
                    errorList.Add(new CyCustErr(Resources.SpiSclkFreeRunning));
                }
                // Check SPI SS polarity
                bool ss0Selected = SPI_NumberOfSSLines >= SPI_MIN_SS_NUMBER;
                bool ss1Selected = SPI_NumberOfSSLines >= SPI_MIN_SS_NUMBER + 1;
                bool ss2Selected = SPI_NumberOfSSLines >= SPI_MIN_SS_NUMBER + 2;
                bool ss3Selected = SPI_NumberOfSSLines >= SPI_MIN_SS_NUMBER + 3;

                if ((m_spiSs0Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss0Selected) ||
                    (m_spiSs1Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss1Selected) ||
                    (m_spiSs2Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss2Selected) ||
                    (m_spiSs3Polarity.Value == CyEActivePolarityType.ACTIVE_HIGH && ss3Selected))
                {
                    errorList.Add(new CyCustErr(String.Format("{0}: {1}", CyESCBMode.SPI,
                        Resources.SpiSSPolarityError)));
                }

                // Check Byte mode
                if (SPI_EnableByteMode)
                {
                    errorList.Add(new CyCustErr(String.Format("{0}: {1}", CyESCBMode.SPI, Resources.ByteModeError)));
                }

                // Slave && Wakeup enable -> CPHA = 0, CPOL = 0 
                if ((m_spiMode.Value == CyESPIModeType.SPI_SLAVE) && (m_spiSubMode.Value == CyESPISubModeType.MOTOROLA)
                     && (SPI_InterruptMode == CyEInterruptModeType.INTERNAL) && (SPI_EnableWakeupFromSleepMode)
                     && (m_spiSCLKMode.Value != CyESPISCLKModeType.MODE_00))
                {
                    errorList.Add(new CyCustErr(Resources.SpiSclkMode));
                }

                if (SPI_EnableSclkFreeRunning)
                {
                    errorList.Add(new CyCustErr(Resources.SpiSclkFreeRunning));
                }
            }

            // Check if Actual data rate is not greater than requested for Master mode
            if (m_spiMode.Value == CyESPIModeType.SPI_MASTER && (SPI_ClockFromTerminal == false))
            {
                double actualSampleRate = GetActualDataRate(CyESCBMode.SPI);
                if (actualSampleRate > SPI_BitsRateInKHz.Value + CyParamRanges.EPS)
                {
                    errorList.Add(new CyCustErr(WARNING_CODE, Resources.ActualDataRateMaster));
                }
            }

            // Check DMA Rx Tx outputs
            if (IsDmaCapable == false)
            {
                if (SPI_RxOutput || SPI_TxOutput)
                    errorList.Add(new CyCustErr(String.Format("{0}: {1}", CyESCBMode.SPI, Resources.DMASupportError)));
            }

            // Validate RX TX buffers values, because for CCG3 the default values are wrong
            if (SPI_RxBufferSize < SpiRxBufferMinSize)
            {
                errorList.Add(new CyCustErr(String.Format(Resources.ErrorValueLimitBufferSize, SpiRxBufferMinSize)));
            }
            if (SPI_TxBufferSize < SpiTxBufferMinSize)
            {
                errorList.Add(new CyCustErr(String.Format(Resources.ErrorValueLimitBufferSize, SpiTxBufferMinSize)));
            }

            return errorList;
        }
        #endregion
    }
}
