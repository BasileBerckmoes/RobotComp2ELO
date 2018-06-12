/*******************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.ComponentModel;
using System.Reflection;
using SCB_P4_v4_0.Tabs.EZI2C;

namespace SCB_P4_v4_0
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string SCB_MODE = "ScbMode";
        public const string SCB_MOSI_SCL_RX_ENABLED = "ScbMosiSclRxEnable";
        public const string SCB_SCLK_ENABLED = "ScbSclkEnable";
        public const string SCB_RX_WAKE = "ScbRxWakeIrqEnable";
        public const string SCB_SS0_ENABLED = "ScbSs0Enable";
        public const string SCB_SS1_ENABLED = "ScbSs1Enable";
        public const string SCB_SS2_ENABLED = "ScbSs2Enable";
        public const string SCB_SS3_ENABLED = "ScbSs3Enable";
        public const string SCB_MISO_SDA_TX_ENABLED = "ScbMisoSdaTxEnable";
        public const string SCB_CLOCK_SELECT = "ScbClockSelect";
        public const string SCB_CLOCK_DIVIDER = "ScbClockDivider";
    }
    #endregion

    #region Component Parameters Ranges
    public partial class CyParamRanges
    {
        public const byte MIN_TRIGGER_LEVEL = 0;
        public const byte MAX_TRIGGER_LEVEL = 7;
        public const byte MAX_TRIGGER_LEVEL_BYTE_MODE = 15;
        public const byte RX_TRIGGER_LEVEL_DEFAULT = 7;
        public const byte TX_TRIGGER_LEVEL_DEFAULT = 0;

        public const byte BYTE_MODE_MAX_DATA_BITS = 8;

        public const ushort MAX_IMO_FREQ = 48000;
    }
    #endregion

    #region Enums
    public enum CyESCBMode
    {
        I2C = 1,
        SPI = 2,
        UART = 4,
        EZI2C = 8,
        UNCONFIG = 255
    }

    public enum CyEInterruptModeType { INTERNAL = 1, EXTERNAL = 2, INTERRUPT_NONE = 0 }
    public enum CyEActivePolarityType { ACTIVE_LOW, ACTIVE_HIGH }
    public enum CyESlewRateType { SLOW, FAST, I2C_FM_PLUS }
    public enum CyETolerance : 
        ushort { MINUS_MAX = 100, IMO_ACCURACY = 2, PLUS_MAX = 1000, DEFAULT = 5, ZERO_ACCURACY = 0 }
    public enum CyEToleranceMode { MINUS_TOLERANCE, PLUS_TOLERANCE };
    #endregion

    public partial class CyParameters
    {
        public const string SCB_IP_BLOCK_NAME = "m0s8scb";

        public const string EZ_DATA_NR_FEATURE_NAME = "EZ_DATA_NR";
        public const string FF_DATA_NR_LOG2_FEATURE_NAME = "FF_DATA_NR_LOG2";
        public const string FF_DATA_NR_LOG2_PLUS1_FEATURE_NAME = "FF_DATA_NR_LOG2_PLUS1";

        private const string PIN_IP_BLOCK_NAME = "m0s8ioss";
        private const string SSV2_IP_BLOCK_NAME = "m0s8cpussv2";
        private const string SSV3_IP_BLOCK_NAME = "m0s8cpussv3";
        private const string BLESS_IP_BLOCK_NAME = "m0s8bless";
        private const string DMA_PRESENT_ATTRIBUTE = "CPUMEMSS.DMAC_PRESENT";
        private const string PRGIO_NR_ATTRIBUTE = "PRGIO.PRGIO_NR";

        public const byte DEFAULT_EZDATANR = 32;
        public const byte DEFAULT_BUFFER_MIN_SIZE = 8;
        public const byte DEFAULT_FF_DATA_NR_LOG2 = 3;
        public const byte DEFAULT_FF_DATA_NR_LOG2_PLUS1 = 4;

        public const string HEX_PREFIX = "0x";
        public const int WARNING_CODE = 100;

        #region Clock data
        public const string SCB_CLOCK_SCBCLK = "or_sclk";
        public const string SCB_CLOCK_HFCLK = "or_hfclk";
        public const string SCB_CLOCK_TERM = "clock";
        public const double UNKNOWN_FREQUENCY = -1;
        #endregion

        // A delegate type for hooking up SCB mode change notifications.
        public delegate void ScbModeChangedEventHandler(object sender, CyScbModeChangedEventArgs e);

        /// <summary>
        /// An event that clients can use to be notified whenever the mode changes.
        /// </summary>
        public event ScbModeChangedEventHandler ScbModeChanged;
        /// <summary>
        /// An event that clients can use to be notified whenever the PSoC Creator design updates.
        /// </summary>
        public event EventHandler DesignUpdates;

        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyTerminalQuery_v1 m_termQuery;

        private readonly int m_scbIpVersion;

        public ICyTabbedParamEditor m_editor = null;

        private bool m_internalClockNeedUpdate = false;

        // References to tabs used in the customizer
        private CyI2CAdvancedTab m_i2cAdvancedTab;
        private CyEZI2CAdvancedTab m_ezi2cAdvancedTab;
        private CyUARTConfigureTab m_uartConfigTab;
        private CyUARTAdvancedTab m_uartAdvancedTab;
        private CySPIBasicTab m_spiBasicTab;
        private CySPIAdvancedTab m_spiAdvancedTab;

        // Enumeration fields
        private CyEnum<CyEI2CModeType> m_i2cMode;
        private CyEnum<CyESlewRateType> m_i2cSlewRate;
        private CyEnum<CyESlewRateType> m_ezi2cSlewRate;
        private CyEnum<CyESPIModeType> m_spiMode;
        private CyEnum<CyESPISubModeType> m_spiSubMode;
        private CyEnum<CyESPISCLKModeType> m_spiSCLKMode;
        private CyEnum<CyESPIBitOrderType> m_spiBitsOrder;
        private CyEnum<CyEActivePolarityType> m_spiSs0Polarity;
        private CyEnum<CyEActivePolarityType> m_spiSs1Polarity;
        private CyEnum<CyEActivePolarityType> m_spiSs2Polarity;
        private CyEnum<CyEActivePolarityType> m_spiSs3Polarity;
        private CyEnum<CyEUARTSubModeType> m_uartSubMode;
        private CyEnum<CyEUARTDirectionType> m_uartDirection;
        private CyEnum<CyEUARTNumberDataBitsType> m_uartNumberDataBits;
        private CyEnum<CyEUARTParityType> m_uartParityType;
        private CyEnum<CyEActivePolarityType> m_uartRtsPolarity;
        private CyEnum<CyEActivePolarityType> m_uartCtsPolarity;
        private CyEnum<CyEUARTNumberStopBitsType> m_uartNumberStopBits;
        private CyEnum<CyEEZI2CSubAddressSizeType> m_ezI2CSubAddressSize;
        private CyEnum<CyEEZI2CNumberOfAddressesType> m_ezI2CNumberOfAddresses;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        #region Tab properties

        public CyI2CAdvancedTab I2cAdvancedTab
        {
            get { return m_i2cAdvancedTab; }
            set { m_i2cAdvancedTab = value; }
        }

        public CyEZI2CAdvancedTab Ezi2cAdvancedTab
        {
            get { return m_ezi2cAdvancedTab; }
            set { m_ezi2cAdvancedTab = value; }
        }

        public CyUARTConfigureTab UartConfigTab
        {
            get { return m_uartConfigTab; }
            set { m_uartConfigTab = value; }
        }

        public CyUARTAdvancedTab UartAdvancedTab
        {
            get { return m_uartAdvancedTab; }
            set { m_uartAdvancedTab = value; }
        }

        public CySPIBasicTab SpiBasicTab
        {
            get { return m_spiBasicTab; }
            set { m_spiBasicTab = value; }
        }


        public CySPIAdvancedTab SpiAdvancedTab
        {
            get { return m_spiAdvancedTab; }
            set { m_spiAdvancedTab = value; }
        }

        #endregion

        #region Enumerations properties

        public CyEnum<CyEI2CModeType> I2cMode
        {
            get { return m_i2cMode; }
            set { m_i2cMode = value; }
        }

        public CyEnum<CyESlewRateType> I2cSlewRate
        {
            get { return m_i2cSlewRate; }
            set { m_i2cSlewRate = value; }
        }

        public CyEnum<CyESlewRateType> Ezi2cSlewRate
        {
            get { return m_ezi2cSlewRate; }
            set { m_ezi2cSlewRate = value; }
        }

        public CyEnum<CyESPIModeType> SpiMode
        {
            get { return m_spiMode; }
            set { m_spiMode = value; }
        }

        public CyEnum<CyESPISubModeType> SpiSubMode
        {
            get { return m_spiSubMode; }
            set { m_spiSubMode = value; }
        }

        public CyEnum<CyESPISCLKModeType> SpiSCLKMode
        {
            get { return m_spiSCLKMode; }
            set { m_spiSCLKMode = value; }
        }

        public CyEnum<CyESPIBitOrderType> SpiBitsOrder
        {
            get { return m_spiBitsOrder; }
            set { m_spiBitsOrder = value; }
        }

        public CyEnum<CyEActivePolarityType> SpiSs0Polarity
        {
            get { return m_spiSs0Polarity; }
            set { m_spiSs0Polarity = value; }
        }

        public CyEnum<CyEActivePolarityType> SpiSs1Polarity
        {
            get { return m_spiSs1Polarity; }
            set { m_spiSs1Polarity = value; }
        }

        public CyEnum<CyEActivePolarityType> SpiSs2Polarity
        {
            get { return m_spiSs2Polarity; }
            set { m_spiSs2Polarity = value; }
        }

        public CyEnum<CyEActivePolarityType> SpiSs3Polarity
        {
            get { return m_spiSs3Polarity; }
            set { m_spiSs3Polarity = value; }
        }

        public CyEnum<CyEUARTSubModeType> UartSubMode
        {
            get { return m_uartSubMode; }
            set { m_uartSubMode = value; }
        }

        public CyEnum<CyEUARTDirectionType> UartDirection
        {
            get { return m_uartDirection; }
            set { m_uartDirection = value; }
        }

        public CyEnum<CyEUARTNumberDataBitsType> UartNumberDataBits
        {
            get { return m_uartNumberDataBits; }
            set { m_uartNumberDataBits = value; }
        }

        public CyEnum<CyEUARTParityType> UartParityType
        {
            get { return m_uartParityType; }
            set { m_uartParityType = value; }
        }

        public CyEnum<CyEActivePolarityType> UartRtsPolarity
        {
            get { return m_uartRtsPolarity; }
            set { m_uartRtsPolarity = value; }
        }

        public CyEnum<CyEActivePolarityType> UartCtsPolarity
        {
            get { return m_uartCtsPolarity; }
            set { m_uartCtsPolarity = value; }
        }

        public CyEnum<CyEUARTNumberStopBitsType> UartNumberStopBits
        {
            get { return m_uartNumberStopBits; }
            set { m_uartNumberStopBits = value; }
        }

        public CyEnum<CyEEZI2CSubAddressSizeType> EzI2CSubAddressSize
        {
            get { return m_ezI2CSubAddressSize; }
            set { m_ezI2CSubAddressSize = value; }
        }

        public CyEnum<CyEEZI2CNumberOfAddressesType> EzI2CNumberOfAddresses
        {
            get { return m_ezI2CNumberOfAddresses; }
            set { m_ezI2CNumberOfAddresses = value; }
        }
        #endregion

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;

            m_i2cMode = new CyEnum<CyEI2CModeType>(this, CyParamNames.I2C_MODE);
            m_i2cSlewRate = new CyEnum<CyESlewRateType>(this, CyParamNames.I2C_SLEW_RATE);
            m_ezi2cSlewRate = new CyEnum<CyESlewRateType>(this, CyParamNames.EZI2C_SLEW_RATE);
            m_spiMode = new CyEnum<CyESPIModeType>(this, CyParamNames.SPI_MODE);
            m_spiSubMode = new CyEnum<CyESPISubModeType>(this, CyParamNames.SPI_SUB_MODE);
            m_spiSCLKMode = new CyEnum<CyESPISCLKModeType>(this, CyParamNames.SPI_SCLK_MODE);
            m_spiBitsOrder = new CyEnum<CyESPIBitOrderType>(this, CyParamNames.SPI_BITS_ORDER);
            m_spiSs0Polarity = new CyEnum<CyEActivePolarityType>(this, CyParamNames.SPI_SS0_POLARITY);
            m_spiSs1Polarity = new CyEnum<CyEActivePolarityType>(this, CyParamNames.SPI_SS1_POLARITY);
            m_spiSs2Polarity = new CyEnum<CyEActivePolarityType>(this, CyParamNames.SPI_SS2_POLARITY);
            m_spiSs3Polarity = new CyEnum<CyEActivePolarityType>(this, CyParamNames.SPI_SS3_POLARITY);
            m_uartSubMode = new CyEnum<CyEUARTSubModeType>(this, CyParamNames.UART_SUB_MODE);
            m_uartDirection = new CyEnum<CyEUARTDirectionType>(this, CyParamNames.UART_DIRECTION);
            m_uartParityType = new CyEnum<CyEUARTParityType>(this, CyParamNames.UART_PARITY_TYPE);
            m_uartNumberStopBits = new CyEnum<CyEUARTNumberStopBitsType>(this, CyParamNames.UART_NUMBER_OF_STOP_BITS);
            m_uartNumberDataBits = new CyEnum<CyEUARTNumberDataBitsType>(this, CyParamNames.UART_NUMBER_OF_DATA_BITS);
            m_uartRtsPolarity = new CyEnum<CyEActivePolarityType>(this, CyParamNames.UART_RTS_POLARITY);
            m_uartCtsPolarity = new CyEnum<CyEActivePolarityType>(this, CyParamNames.UART_CTS_POLARITY);
            m_ezI2CSubAddressSize = new CyEnum<CyEEZI2CSubAddressSizeType>(this, CyParamNames.EZI2C_SUBADDRESS_SIZE);
            m_ezI2CNumberOfAddresses = new CyEnum<CyEEZI2CNumberOfAddressesType>(this,
                CyParamNames.EZI2C_NUMBER_OF_ADDRESSES);

            m_scbIpVersion = InstQuery.DeviceQuery.GetFeatureVersion(SCB_IP_BLOCK_NAME);
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
        // Invoke the ScbModeChanged event; called whenever scb mode changes.
        protected virtual void OnScbModeChanged(CyScbModeChangedEventArgs e)
        {
            if (ScbModeChanged != null)
                ScbModeChanged(this, e);
        }

        // Invoke the DesignUpdates event; called whenever PSoC Creator design updates.
        protected virtual void OnDesignUpdates(EventArgs e)
        {
            if (DesignUpdates != null)
                DesignUpdates(this, e);
        }

        public void TriggerScbModeChanged()
        {
            OnScbModeChanged(new CyScbModeChangedEventArgs(this.SCBMode));
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
        #endregion

        #region Setting Parameters
        public void SetValue<T>(string paramName, T value)
        {
            if (m_bGlobalEditMode)
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
        
        #region Class methods

        public int EzDataNr
        {
            get
            {
                //The m0s8scb IP (IP version is 0) does not have EZ_DATA_NR in the parameter list.
                //For the m0s8scb_hobto (IP version is 1) the byte mode option was not verified therefore not exposed to the user.
                //Therefore for these two IP blocks the FIFO size is fixed to 8 entries.
                if (m_scbIpVersion > 1)
                {
                    return InstQuery.DeviceQuery.GetFeatureParameter(CyParameters.SCB_IP_BLOCK_NAME, 
                        CyParameters.EZ_DATA_NR_FEATURE_NAME);
                }
                else
                {
                    return CyParameters.DEFAULT_EZDATANR;
                }
            }
        }

        public byte GetBufferMinSize()
        {
            //The m0s8scb IP (IP version is 0) does not have F_DATA_NR_LOG2_PLUS1 in the parameter list.
            //For the m0s8scb_hobto (IP version is 1) the byte mode option was not verified therefore not exposed to the user.
            //Therefore for these two IP blocks the FIFO size is fixed to 8 entries.
            if (m_scbIpVersion > 1)
            {
                int var = InstQuery.DeviceQuery.GetFeatureParameter(CyParameters.SCB_IP_BLOCK_NAME,
                    CyParameters.FF_DATA_NR_LOG2_PLUS1_FEATURE_NAME);
                return (byte)(Math.Pow(2, var) / 4);
            }
            else
            {
                return CyParameters.DEFAULT_BUFFER_MIN_SIZE;
            }
        }

        public byte GetByteModeBufferMinSize()
        {
            return (byte)(GetBufferMinSize() * 2);
        }

        #endregion Class methods

        #region Class properties

        public int FfDataNrLog2Plus1
        {
            get
            {
                //The m0s8scb IP (IP version is 0) does not have FF_DATA_NR_LOG2_PLUS1 in the parameter list.
                //For the m0s8scb_hobto (IP version is 1) the byte mode option was not verified therefore not exposed to the user.
                //Therefore for these two IP blocks the FIFO size is fixed to 8 entries.
                if (m_scbIpVersion > 1)
                {
                    return InstQuery.DeviceQuery.GetFeatureParameter(SCB_IP_BLOCK_NAME, 
                        FF_DATA_NR_LOG2_PLUS1_FEATURE_NAME);
                }
                else
                {
                    return DEFAULT_FF_DATA_NR_LOG2_PLUS1;
                } 
            }
        }

        public int FfDataNrLog2Plus1Mask
        {
            get 
            {
                return (int)Math.Pow(2, FfDataNrLog2Plus1) - 1;
            }
        }

        public int FfDataNrLog2
        {
            get
            {
                //The m0s8scb IP (IP version is 0) does not have FF_DATA_NR_LOG2 in the parameter list.
                //For the m0s8scb_hobto (IP version is 1) the byte mode option was not verified therefore not exposed to the user.
                //Therefore for these two IP blocks the FIFO size is fixed to 8 entries.
                if (m_scbIpVersion > 1)
                {
                    return InstQuery.DeviceQuery.GetFeatureParameter(SCB_IP_BLOCK_NAME, FF_DATA_NR_LOG2_FEATURE_NAME);
                }
                else
                {
                    return DEFAULT_FF_DATA_NR_LOG2;
                }
            }
        }

        public int FfDataNrLog2Mask
        {
            get
            {
                return (int)Math.Pow(2, FfDataNrLog2) - 1;
            }
        }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        public CyESCBMode SCBMode
        {
            get { return GetValue<CyESCBMode>(CyParamNames.SCB_MODE); }
            set
            {
                SetValue(CyParamNames.SCB_MODE, value);
                OnScbModeChanged(new CyScbModeChangedEventArgs(value));
            }
        }

        public string InstName
        {
            get { return GetValue<string>("INSTANCE_NAME"); }
        }

        public bool SCB_MosiSclRxEnabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_MOSI_SCL_RX_ENABLED); }
            set { SetValue(CyParamNames.SCB_MOSI_SCL_RX_ENABLED, value); }
        }

        public bool SCB_SclkEnabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SCLK_ENABLED); }
            set { SetValue(CyParamNames.SCB_SCLK_ENABLED, value); }
        }

        public bool SCB_RxWake
        {
            get { return GetValue<bool>(CyParamNames.SCB_RX_WAKE); }
            set { SetValue(CyParamNames.SCB_RX_WAKE, value); }
        }

        public bool SCB_Ss0Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS0_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS0_ENABLED, value); }
        }

        public bool SCB_Ss1Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS1_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS1_ENABLED, value); }
        }

        public bool SCB_Ss2Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS2_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS2_ENABLED, value); }
        }

        public bool SCB_Ss3Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS3_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS3_ENABLED, value); }
        }

        public bool SCB_MisoSdaTxEnabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_MISO_SDA_TX_ENABLED); }
            set { SetValue(CyParamNames.SCB_MISO_SDA_TX_ENABLED, value); }
        }

        public bool IsScbIPV0 //PSoC4100/4200
        {
            get { return m_scbIpVersion == 0; }
        }

        public bool IsScbIPV1 //PSoC4000 
        {
            get { return m_scbIpVersion == 1; }
        }

        public bool IsScbIPV2 //PSoC4200 BLE
        {
            get { return m_scbIpVersion >= 2; }
        }

        public bool IsBleCapable
        {
            get
            {
                return InstQuery.DeviceQuery.GetFeatureCount(BLESS_IP_BLOCK_NAME) > 0;
            }
        }

        public bool IsDmaCapable
        {
            get
            {
                return IsScbIPV2 &&
                       (InstQuery.DeviceQuery.GetFeatureParameter(SSV2_IP_BLOCK_NAME, DMA_PRESENT_ATTRIBUTE) > 0 ||
                       InstQuery.DeviceQuery.GetFeatureParameter(SSV3_IP_BLOCK_NAME, DMA_PRESENT_ATTRIBUTE) > 0);
            }
        }

        public static bool IsGpioOvtCapable(ICyDeviceQuery_v1 deviceQuery) //PSoC4200 BLE
        {
            int portCapability = 0;
            int pinVersion = deviceQuery.GetFeatureVersion(PIN_IP_BLOCK_NAME);

            if (pinVersion >= 0)
            {
                int numPorts = deviceQuery.GetFeatureParameter(PIN_IP_BLOCK_NAME, "GPIO.GPIO_PORT_NR");

                for (int portIndex = 0; portIndex < numPorts; portIndex++)
                {
                    portCapability |= deviceQuery.GetFeatureParameter(PIN_IP_BLOCK_NAME,
                        String.Format("GPIO_PRT.GPIO_OVT[{0}]", portIndex));
                }
            }

            return portCapability > 0;
        }

        public bool IsGpioOvtCapable()
        {
            return IsGpioOvtCapable(InstQuery.DeviceQuery);
        }

        public byte SCBClockSelect
        {
            get { return GetValue<byte>(CyParamNames.SCB_CLOCK_SELECT); }
        }

        public bool InternalClockNeedUpdate
        {
            get { return m_internalClockNeedUpdate; }
            set { m_internalClockNeedUpdate = value; }
        }
        #endregion

        #region Service functions

        public void UpdateDesigns(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            InternalClockNeedUpdate = false;
            OnDesignUpdates(EventArgs.Empty);
        }

        public List<CyCustErr> VerifySettingsIPV1()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            List<string> wrongParamList = new List<string>();

            if (IsScbIPV1 && (SCBMode == CyESCBMode.UNCONFIG))
            {
                if (SCB_SclkEnabled)
                    wrongParamList.Add(CyParamNames.SCB_SCLK_ENABLED);
                if (SCB_RxWake)
                    wrongParamList.Add(CyParamNames.SCB_RX_WAKE);
                if (SCB_Ss0Enabled)
                    wrongParamList.Add(CyParamNames.SCB_SS0_ENABLED);
                if (SCB_Ss1Enabled)
                    wrongParamList.Add(CyParamNames.SCB_SS1_ENABLED);
                if (SCB_Ss2Enabled)
                    wrongParamList.Add(CyParamNames.SCB_SS2_ENABLED);
                if (SCB_Ss3Enabled)
                    wrongParamList.Add(CyParamNames.SCB_SS3_ENABLED);

                for (int i = 0; i < wrongParamList.Count; i++)
                {
                    errorList.Add(new CyCustErr(String.Format(Resources.SFSettingsDRCError, wrongParamList[i])));
                }
            }
            return errorList;
        }

        public List<CyCustErr> GetUnconfiguredDrcErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();

            errorList.AddRange(VerifySettingsIPV1());

            return errorList;
        }

        public List<CyCustErr> GetGeneralDrcErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();

            if (IsScbIPV1)
            {
                if (SCBMode == CyESCBMode.SPI || SCBMode == CyESCBMode.UART)
                {
                    errorList.Add(new CyCustErr(String.Format(Resources.SFModeError, SCBMode)));
                }
            }
            return errorList;
        }

        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public static double GetInternalClock(ICyTerminalQuery_v1 termQuery)
        {
            return GetClock(termQuery, SCB_CLOCK_SCBCLK, true);
        }

        public static double GetHfclkClock(ICyTerminalQuery_v1 termQuery)
        {
            return GetClock(termQuery, SCB_CLOCK_HFCLK, true);
        }

        public static double GetExternalClock(ICyTerminalQuery_v1 termQuery)
        {
            return GetClock(termQuery, SCB_CLOCK_TERM, false);
        }

        private static double GetClock(ICyTerminalQuery_v1 termQuery, string termName, bool internalClock)
        {
            List<CyClockData> clkdata = internalClock ? termQuery.GetClockData(termName, "term1", 0) :
                                                        termQuery.GetClockData(termName, 0);
            if (clkdata.Count > 0)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                }
            }
            return UNKNOWN_FREQUENCY;
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

        public static bool IsFrequencyKnown(double frequency)
        {
            return frequency > 0;
        }

        public static string GetDescription(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
        }

        #region Data rate

        public double GetActualDataRate(CyESCBMode scbMode, uint customOvsFactor)
        {
            const byte OUTPUT_DELAY = 42;

            Debug.Assert(scbMode == CyESCBMode.I2C || scbMode == CyESCBMode.EZI2C || scbMode == CyESCBMode.SPI ||
                         scbMode == CyESCBMode.UART);

            double actualDataRate = UNKNOWN_FREQUENCY;

            bool clockFromTerminal = GetClockFromTerminalByMode(scbMode);
            uint? ovsFactor = customOvsFactor > 0 ? customOvsFactor : GetOvsFactorByMode(scbMode);

            double clkFreq = clockFromTerminal ? GetExternalClock(TermQuery) : GetInternalClock(TermQuery);

            if (IsFrequencyKnown(clkFreq))
            {
                // I2C Slave and EZI2C
                if ((scbMode == CyESCBMode.I2C && m_i2cMode.Value == CyEI2CModeType.I2C_SLAVE) ||
                    (scbMode == CyESCBMode.EZI2C))
                {
                    if (clkFreq < CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS - CyParamRanges.EPS)
                    {
                        // Clock is too low
                        actualDataRate = 0;
                    }
                    else if (clkFreq < CyParamRanges.I2C_SLAVE_FSCB_MIN_400KBPS - CyParamRanges.EPS)
                    {
                        actualDataRate = CyParamRanges.I2C_DATA_RATE_100;
                    }
                    else if (clkFreq < CyParamRanges.I2C_SLAVE_FSCB_MIN_1000KBPS - CyParamRanges.EPS)
                    {
                        actualDataRate = CyParamRanges.I2C_DATA_RATE_400;
                    }
                    else
                    {
                        actualDataRate = CyParamRanges.I2C_DATA_RATE_1000;
                    }
                }
                // SPI Slave
                else if (scbMode == CyESCBMode.SPI && m_spiMode.Value == CyESPIModeType.SPI_SLAVE)
                {
                    actualDataRate = Math.Round(
                        1000000 / (2 * ((1000000 * SpiClockCyclesToOutput / clkFreq) + OUTPUT_DELAY)), 3);
                }
                // I2C Master, SPI Master and UART
                else
                {
                    if (ovsFactor.HasValue && ovsFactor.Value > 0)
                    {
                        actualDataRate = Math.Round(clkFreq / ovsFactor.Value, 3);
                    }
                }
            }

            return actualDataRate;
        }

        public double GetActualDataRate(CyESCBMode scbMode)
        {
            return GetActualDataRate(scbMode, 0);
        }

        private double GetDataRateByMode(CyESCBMode scbMode)
        {
            double? dataRate = 0;
            switch (scbMode)
            {
                case CyESCBMode.I2C:
                    dataRate = I2C_DataRate;
                    break;
                case CyESCBMode.SPI:
                    dataRate = SPI_BitsRateInKHz;
                    break;
                case CyESCBMode.UART:
                    dataRate = UART_DataRate / 1000.0;
                    break;
                case CyESCBMode.EZI2C:
                    dataRate = EZI2C_DataRate;
                    break;
                case CyESCBMode.UNCONFIG:
                    break;
                default:
                    break;
            }
            return dataRate.HasValue ? dataRate.Value : 0;
        }


        private uint GetOvsFactorByMode(CyESCBMode scbMode)
        {
            uint? ovsFactor = 0;
            switch (scbMode)
            {
                case CyESCBMode.I2C:
                    ovsFactor = I2C_OvsFactor;
                    break;
                case CyESCBMode.SPI:
                    ovsFactor = SPI_OvsFactor;
                    break;
                case CyESCBMode.UART:
                    ovsFactor = UART_OvsFactor;
                    break;
                case CyESCBMode.EZI2C:
                    ovsFactor = EZI2C_OvsFactor;
                    break;
                case CyESCBMode.UNCONFIG:
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            return ovsFactor.HasValue ? ovsFactor.Value : 0;
        }

        private bool GetClockFromTerminalByMode(CyESCBMode scbMode)
        {
            bool clockFromTerminal = false;
            switch (scbMode)
            {
                case CyESCBMode.I2C:
                    clockFromTerminal = I2C_ClockFromTerminal;
                    break;
                case CyESCBMode.SPI:
                    clockFromTerminal = SPI_ClockFromTerminal;
                    break;
                case CyESCBMode.UART:
                    clockFromTerminal = UART_ClockFromTerminal;
                    break;
                case CyESCBMode.EZI2C:
                    clockFromTerminal = EZI2C_ClockFromTerminal;
                    break;
                case CyESCBMode.UNCONFIG:
                    break;
                default:
                    break;
            }
            return clockFromTerminal;
        }
        #endregion Data rate
        #endregion Service functions
    }

    public class CyEnum<T>
    {
        CyParameters m_prm;
        string m_paramName;

        public CyEnum(CyParameters prm, string paramName)
        {
            m_prm = prm;
            m_paramName = paramName;
        }

        /// <summary>
        /// Gets and sets the parameter's value
        /// </summary>
        public T Value
        {
            get
            {
                return m_prm.GetValue<T>(m_paramName);
            }
            set
            {
                m_prm.SetValue<T>(m_paramName, value);
            }
        }

        /// <summary>
        /// Gets the enum item description or sets the parameter's value by enum item description.
        /// </summary>
        public string Description
        {
            get
            {
                string res = string.Empty;

                CyCompDevParam param = m_prm.InstQuery.GetCommittedParam(m_paramName);
                if (param != null)
                {
                    m_prm.InstQuery.ResolveEnumParamToDisplay(param, out res);
                }

                return res;
            }
            set
            {
                string enumItemName = m_prm.InstQuery.ResolveEnumDisplayToId(m_paramName, value);

                try
                {
                    Value = (T)Enum.Parse(typeof(T), enumItemName);
                }
                catch { }
            }
        }

        /// <summary>
        /// Gets the array of strings - descriptions of the enumeration that is a type of the parameter.
        /// </summary>
        public string[] EnumDescriptionsList
        {
            get
            {
                return new List<string>(m_prm.InstQuery.GetPossibleEnumValues(m_paramName)).ToArray();
            }
        }

        /// <summary>
        /// Get the enum item description by the specified enum item value.
        /// </summary>
        /// <param name="value">Enum item value</param>
        /// <returns>Enum item description</returns>
        public string GetDescription(T value)
        {
            string res = string.Empty;

            CyCompDevParam prm = m_prm.InstQuery.GetCommittedParam(m_paramName);

            if (prm != null)
            {
                CyCompDevParam newParam = new CyCompDevParam(prm.Name, prm.Expr, prm.ExprType, value.ToString(),
                    prm.TypeName, prm.DefaultExpr, prm.TabName, prm.CategoryName, prm.Description, prm.IsVisible,
                    prm.IsReadOnly, prm.IsHardware, prm.IsFormal, prm.IsDisplayEvaluated, prm.ErrorCount, value,
                    prm.Errors);

                if (newParam != null)
                {
                    m_prm.InstQuery.ResolveEnumParamToDisplay(newParam, out res);
                }
            }

            return res;
        }
    }

    public class CyScbModeChangedEventArgs : EventArgs
    {
        private CyESCBMode m_mode;

        public CyScbModeChangedEventArgs(CyESCBMode mode)
        {
            Mode = mode;
        }

        public CyESCBMode Mode
        {
            get { return m_mode; }
            private set { m_mode = value; }
        }
    }
}
