/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using SCB_P4_v3_20.Tabs.EZI2C;

namespace SCB_P4_v3_20
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string EZI2C_CLOCK_FROM_TERMINAL = "EzI2cClockFromTerm";
        public const string EZI2C_CLOCK_STRETCHING = "EzI2cClockStretching";
        public const string EZI2C_DATA_RATE = "EzI2cDataRate";
        public const string EZI2C_IS_PRIMARY_SLAVE_ADDRESS_HEX = "EzI2cIsPrimarySlaveAddressHex";
        public const string EZI2C_IS_SECONDRY_SLAVE_ADDRESS_HEX = "EzI2cIsSecondarySlaveAddressHex";
        public const string EZI2C_ENABLE_BYTE_MODE = "EzI2cByteModeEnable";
        public const string EZI2C_OVERSAMPLING = "EzI2cOvsFactor";
        public const string EZI2C_PRIMARY_SLAVE_ADDRESS = "EzI2cPrimarySlaveAddress";
        public const string EZI2C_SECONDARY_SLAVE_ADDRESS = "EzI2cSecondarySlaveAddress";
        public const string EZI2C_SUBADDRESS_SIZE = "EzI2cSubAddressSize";
        public const string EZI2C_ENABLE_WAKEUP = "EzI2cWakeEnable";
        public const string EZI2C_NUMBER_OF_ADDRESSES = "EzI2cNumberOfAddresses";
        public const string EZI2C_SLEW_RATE = "EzI2cSlewRate";
        public const string EZI2C_BUS_VOLTAGE = "EzI2cBusVoltage";
    }
    #endregion

    #region Component Parameters Ranges
    public partial class CyParamRanges
    {
        public const int EZI2C_DATA_RATE_400 = 400;
    }
    #endregion

    #region Component Enums
    public enum CyEEZI2CSubAddressSizeType { SUB_ADDR8, SUB_ADDR16 }
    public enum CyEEZI2CNumberOfAddressesType { ONE_ADDRESS = 0, TWO_ADDRESSES = 1 }
    #endregion

    public partial class CyParameters
    {
        #region Class properties

        #region Basic tab properties

        public bool EZI2C_ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_CLOCK_FROM_TERMINAL); }
            set { SetValue(CyParamNames.EZI2C_CLOCK_FROM_TERMINAL, value); }
        }

        public bool EZI2C_StretchClock
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_CLOCK_STRETCHING); }
            set { SetValue(CyParamNames.EZI2C_CLOCK_STRETCHING, value); }
        }

        public UInt16 EZI2C_DataRate
        {
            get { return GetValue<UInt16>(CyParamNames.EZI2C_DATA_RATE); }
            set { SetValue(CyParamNames.EZI2C_DATA_RATE, value); }
        }

        public bool EZI2C_IsPrimarySlaveAddressHex
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_IS_PRIMARY_SLAVE_ADDRESS_HEX); }
            set { SetValue(CyParamNames.EZI2C_IS_PRIMARY_SLAVE_ADDRESS_HEX, value); }
        }

        public bool EZI2C_IsSecondarySlaveAddressHex
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_IS_SECONDRY_SLAVE_ADDRESS_HEX); }
            set { SetValue(CyParamNames.EZI2C_IS_SECONDRY_SLAVE_ADDRESS_HEX, value); }
        }

        public bool EZI2C_EnableByteMode
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_ENABLE_BYTE_MODE); }
            set { SetValue(CyParamNames.EZI2C_ENABLE_BYTE_MODE, value); }
        }

        public byte EZI2C_OvsFactor
        {
            get { return GetValue<byte>(CyParamNames.EZI2C_OVERSAMPLING); }
            set { SetValue(CyParamNames.EZI2C_OVERSAMPLING, value); }
        }

        public byte EZI2C_PrimarySlaveAddress
        {
            get { return GetValue<byte>(CyParamNames.EZI2C_PRIMARY_SLAVE_ADDRESS); }
            set { SetValue(CyParamNames.EZI2C_PRIMARY_SLAVE_ADDRESS, value); }
        }

        public byte EZI2C_SecondarySlaveAddress
        {
            get { return GetValue<byte>(CyParamNames.EZI2C_SECONDARY_SLAVE_ADDRESS); }
            set { SetValue(CyParamNames.EZI2C_SECONDARY_SLAVE_ADDRESS, value); }
        }

        public bool EZI2C_EnableWakeupFromSleep
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_ENABLE_WAKEUP); }
            set { SetValue(CyParamNames.EZI2C_ENABLE_WAKEUP, value); }
        }

        public string EZI2C_PrimarySlaveAddressStr
        {
            get
            {
                return EZI2C_IsPrimarySlaveAddressHex ? HEX_PREFIX + EZI2C_PrimarySlaveAddress.ToString("X2") :
                    EZI2C_PrimarySlaveAddress.ToString();
            }
        }

        public string EZI2C_SecondarySlaveAddressStr
        {
            get
            {
                return EZI2C_IsSecondarySlaveAddressHex ? HEX_PREFIX + EZI2C_SecondarySlaveAddress.ToString("X2") :
                    EZI2C_SecondarySlaveAddress.ToString();
            }
        }

        #endregion

        #region Advanced tab properties

        public string EZI2C_BusVoltage
        {
            get { return GetValue<string>(CyParamNames.EZI2C_BUS_VOLTAGE); }
            set { SetValue(CyParamNames.EZI2C_BUS_VOLTAGE, value); }
        }

        #endregion

        #endregion

        public List<CyCustErr> GetEzI2cDrcErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            string errorMessage;

            if (IsScbIPV0 || IsScbIPV1)
            {
                // Check Byte mode
                if (EZI2C_EnableByteMode)
                {
                    errorList.Add(new CyCustErr(String.Format("{0}: {1}", CyESCBMode.EZI2C, Resources.ByteModeError)));
                }

                if (IsScbIPV0)
                {
                    // Primary slave address
                    errorMessage = CyEZI2CTab.GetSlaveAddressError(EZI2C_PrimarySlaveAddress, this);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                    {
                        errorList.Add(new CyCustErr(errorMessage));
                    }

                    // Secondary slave address
                    if (m_ezI2CNumberOfAddresses.Value == CyEEZI2CNumberOfAddressesType.TWO_ADDRESSES)
                    {
                        errorMessage = CyEZI2CTab.GetSlaveAddressError(EZI2C_SecondarySlaveAddress, this);
                        if (string.IsNullOrEmpty(errorMessage) == false)
                        {
                            errorList.Add(new CyCustErr(errorMessage));
                        }
                    }

                    // Clock stretching vs wakeup enable
                    if (EZI2C_EnableWakeupFromSleep && EZI2C_StretchClock == false)
                    {
                        errorList.Add(new CyCustErr(Resources.ErrMsgWakeUpFromSleep));
                    }
                }
                else if (IsScbIPV1)
                {
                    // Data rate maximum
                    if (CyParamRanges.GetI2cDataRateMaximum(IsScbIPV1, out errorMessage) < I2C_DataRate)
                    {
                        errorList.Add(new CyCustErr(errorMessage));
                    }
                }
            }

            // Slew rate validation
            errorMessage = GetEZI2CSlewRateError(true);
            if (String.IsNullOrEmpty(errorMessage) == false)
                errorList.Add(new CyCustErr(errorMessage));

            // External clock
            if (EZI2C_ClockFromTerminal)
            {
                double clkFreq = GetExternalClock(TermQuery);
                if (IsFrequencyKnown(clkFreq) &&
                    (clkFreq < CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS - CyParamRanges.EPS))
                {
                    errorList.Add(new CyCustErr(String.Format(Resources.EZI2cExternalClockLowError, CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS_MHZ)));
                }
            }

            return errorList;
        }

        /// <summary>
        /// Gets error message for slew rate if exists any.
        /// </summary>
        /// <returns>Error message if exists any, otherwise empty string.</returns>
        public string GetEZI2CSlewRateError()
        {
            return GetEZI2CSlewRateError(false);
        }

        /// <summary>
        /// Gets error message for slew rate if exists any.
        /// </summary>
        /// <param name="isDRC">Indicates whenther generate message for DRC or GUI.</param>
        /// <returns>Error message if exists any, otherwise empty string.</returns>
        private string GetEZI2CSlewRateError(bool isDRC)
        {
            string errorMessage = String.Empty;

            if (m_ezi2cSlewRate.Value == CyESlewRateType.I2C_FM_PLUS)
            {
                double dataRate = EZI2C_ClockFromTerminal
                    ? Math.Round(GetActualDataRate(CyESCBMode.EZI2C))
                    : EZI2C_DataRate;

                if (IsGpioOvtCapable() == false)
                {
                    errorMessage = Resources.OvtNotSupportedError;
                    if (isDRC)
                        errorMessage = String.Format("{0}: {1}", CyESCBMode.EZI2C, errorMessage);
                }
                else if (IsGpioOvtCapable() && dataRate <= CyParamRanges.EZI2C_DATA_RATE_400)
                {
                    errorMessage = String.Format(Resources.SlewRateDataRateError, CyParamRanges.EZI2C_DATA_RATE_400);
                    if (isDRC)
                        errorMessage = String.Format("{0}: {1}", CyESCBMode.EZI2C, errorMessage);
                }
            }

            return errorMessage;
        }
    }
}
