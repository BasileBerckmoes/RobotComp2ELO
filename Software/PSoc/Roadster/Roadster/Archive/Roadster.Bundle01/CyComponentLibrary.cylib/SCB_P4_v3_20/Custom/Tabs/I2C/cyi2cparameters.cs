/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCB_P4_v3_20
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string I2C_ACCEPT_ADDRESS = "I2cAcceptAddress";
        public const string I2C_ACCEPT_GENERAL_CALL = "I2cAcceptGeneralCall";
        public const string I2C_DATA_RATE = "I2cDataRate";
        public const string I2C_ENABLE_BYTE_MODE = "I2cByteModeEnable";
        public const string I2C_ENABLE_WAKEUP = "I2cWakeEnable";
        public const string I2C_MODE = "I2cMode";
        public const string I2C_OVS_FACTOR = "I2cOvsFactor";
        public const string I2C_OVS_FACTOR_HIGH = "I2cOvsFactorHigh";
        public const string I2C_OVS_FACTOR_LOW = "I2cOvsFactorLow";
        public const string I2C_SLAVE_ADDRESS = "I2cSlaveAddress";
        public const string I2C_SLAVE_ADDRESS_MASK = "I2cSlaveAddressMask";
        public const string I2C_SLEW_RATE = "I2cSlewRate";
        public const string I2C_BUS_VOLTAGE = "I2cBusVoltage";
        public const string I2C_MANUAL_OVERSAMPLE_CONTROL = "I2cManualOversampleControl";

        public const string I2C_CLOCK_FROM_TERM = "I2cClockFromTerm";

        // Parameters for internal use
        public const string I2C_IS_SLAVE_ADDRESS_HEX = "I2cIsSlaveAddressMaskHex";
        public const string I2C_IS_SLAVE_ADDRESS_MASK_HEX = "I2cIsSlaveAddressMaskHex";
    }
    #endregion

    #region Component Parameters Ranges
    public partial class CyParamRanges
    {
        public const UInt16 I2C_DATA_RATE_MIN = 1;
        public const UInt16 I2C_DATA_RATE_SCBIPV1_MAX = 400;
        public const UInt16 I2C_DATA_RATE_MAX = 1000;
        public const UInt16 I2C_DATA_RATE_NON_ClOCK_STRETCHING_MAX = 400;

        public const int I2C_DATA_RATE_100 = 100;
        public const int I2C_DATA_RATE_400 = 400;
        public const int I2C_DATA_RATE_1000 = 1000;

        public const int I2C_MASTER_FSCB_MIN_100KBPS = 1550;
        public const int I2C_MASTER_FSCB_MAX_100KBPS = 3200;
        public const int I2C_MASTER_FSCB_MIN_400KBPS = 7820;
        public const int I2C_MASTER_FSCB_MAX_400KBPS = 10000;
        public const int I2C_MASTER_FSCB_MIN_1000KBPS = 14320;
        public const int I2C_MASTER_FSCB_MAX_1000KBPS = 25800;

        public const double I2C_SLAVE_FSCB_MIN_100KBPS_MHZ = (double)I2C_SLAVE_FSCB_MIN_100KBPS / 1000;
        public const int I2C_SLAVE_FSCB_MIN_100KBPS = 1550;
        public const int I2C_SLAVE_FSCB_MAX_100KBPS = 12800;
        public const int I2C_SLAVE_FSCB_MIN_400KBPS = 7820;
        public const int I2C_SLAVE_FSCB_MAX_400KBPS = 15380;
        public const int I2C_SLAVE_FSCB_MIN_1000KBPS = 15840;
        public const int I2C_SLAVE_FSCB_MAX_1000KBPS = 48000;

        public const byte I2C_OVS_FACTOR_DEF = 16;
        public const byte I2C_OVS_FACTOR_MIN = 12;
        public const byte I2C_OVS_FACTOR_MAX = 32;
        private const byte I2C_OVS_LOW_MAX = 16;
        private const byte I2C_OVS_LOW_MIN = 7;
        private const byte I2C_OVS_HIGH_MIN = 5;
        private const byte I2C_OVS_HIGH_MAX = 16;

        public const int I2C_OVS_LOW_MIN_100KBPS = 8;
        public const int I2C_OVS_HIGH_MIN_100KBPS = 8;
        public const int I2C_OVS_LOW_MIN_400KBPS = 13;
        public const int I2C_OVS_HIGH_MIN_400KBPS = 8;
        public const int I2C_OVS_LOW_MIN_1000KBPS = 9;
        public const int I2C_OVS_HIGH_MIN_1000KBPS = 6;

        public const int I2C_T_LOW_IDEAL_100KBPS = 5000;  // tLOW  + tF = 4700 + 300;
        public const int I2C_T_HIGH_IDEAL_100KBPS = 5000; // tHIGH + tR = 4000 + 1000;
        public const int I2C_T_LOW_IDEAL_400KBPS = 1600;  // tLOW  + tF = 1300 + 300;
        public const int I2C_T_HIGH_IDEAL_400KBPS = 900;  // tHIGH + tR = 600  + 300;
        public const int I2C_T_LOW_IDEAL_1000KBPS = 620;  // tLOW  + tF = 500  + 120;
        public const int I2C_T_HIGH_IDEAL_1000KBPS = 380; // tHIGH + tR = 260  + 120;

        public const byte I2C_SLAVE_ADDRESS_MIN = 8;
        public const byte I2C_SLAVE_ADDRESS_MAX = 120;
        public const byte I2C_SLAVE_ADDRESS_MASK_MIN = 0;
        public const byte I2C_SLAVE_ADDRESS_MASK_MAX = 254;

        public const double EPS = 1E-5;

        public static byte GetI2COvsLowMaximum()
        {
            return I2C_OVS_LOW_MAX;
        }

        public static byte GetI2COvsHighMaximum()
        {
            return I2C_OVS_HIGH_MAX;
        }

        public static byte GetI2COvsLowMinimum()
        {
            return I2C_OVS_LOW_MIN;
        }

        public static byte GetI2COvsHighMinimum()
        {
            return I2C_OVS_HIGH_MIN;
        }

        public static UInt16 GetI2cDataRateMaximum(bool isScbIPv1, out string message)
        {
            return GetI2cDataRateMaximum(isScbIPv1, true, out message);
        }

        public static UInt16 GetI2cDataRateMaximum(bool isScbIPv1, bool isStretchClock, out string message)
        {
            if (isScbIPv1)
            {
                message = String.Format(Resources.DataRateDeviceError, I2C_DATA_RATE_MIN, I2C_DATA_RATE_SCBIPV1_MAX);
                return I2C_DATA_RATE_SCBIPV1_MAX;
            }
            else
            {
                if (isStretchClock)
                {
                    message = String.Format(Resources.DataRateValueError, I2C_DATA_RATE_MIN, I2C_DATA_RATE_MAX);
                    return I2C_DATA_RATE_MAX;
                }
                else
                {
                    message = String.Format(Resources.DataRateValueErrorNonClockStretching, I2C_DATA_RATE_MIN,
                        I2C_DATA_RATE_NON_ClOCK_STRETCHING_MAX);
                    return I2C_DATA_RATE_NON_ClOCK_STRETCHING_MAX;
                }
            }
        }
    }
    #endregion

    #region Component Enums
    public enum CyEI2CModeType { I2C_SLAVE = 1, I2C_MASTER = 2, I2C_MULTI_MASTER = 6, I2C_MULTI_MASTER_SLAVE = 7 }
    public enum CyEI2CPostWakeupOperationType { ADDRESS_ACK, ADDRESS_NACK }
    #endregion

    public partial class CyParameters
    {
        #region Basic tab properties

        public UInt16 I2C_DataRate
        {
            get { return GetValue<UInt16>(CyParamNames.I2C_DATA_RATE); }
            set { SetValue(CyParamNames.I2C_DATA_RATE, value); }
        }

        public bool I2C_ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.I2C_CLOCK_FROM_TERM); }
            set { SetValue(CyParamNames.I2C_CLOCK_FROM_TERM, value); }
        }

        public byte I2C_OvsFactor
        {
            get { return GetValue<byte>(CyParamNames.I2C_OVS_FACTOR); }
            set { SetValue(CyParamNames.I2C_OVS_FACTOR, value); }
        }

        public byte I2C_OvsFactorLow
        {
            get { return GetValue<byte>(CyParamNames.I2C_OVS_FACTOR_LOW); }
            set { SetValue(CyParamNames.I2C_OVS_FACTOR_LOW, value); }
        }

        public byte I2C_OvsFactorHigh
        {
            get { return GetValue<byte>(CyParamNames.I2C_OVS_FACTOR_HIGH); }
            set { SetValue(CyParamNames.I2C_OVS_FACTOR_HIGH, value); }
        }

        public bool I2C_EnableByteMode
        {
            get { return GetValue<bool>(CyParamNames.I2C_ENABLE_BYTE_MODE); }
            set { SetValue(CyParamNames.I2C_ENABLE_BYTE_MODE, value); }
        }

        public byte I2C_SlaveAddress
        {
            get { return GetValue<byte>(CyParamNames.I2C_SLAVE_ADDRESS); }
            set { SetValue(CyParamNames.I2C_SLAVE_ADDRESS, value); }
        }

        public byte I2C_SlaveAddressMask
        {
            get { return GetValue<byte>(CyParamNames.I2C_SLAVE_ADDRESS_MASK); }
            set { SetValue(CyParamNames.I2C_SLAVE_ADDRESS_MASK, value); }
        }

        public bool I2C_AcceptAddress
        {
            get { return GetValue<bool>(CyParamNames.I2C_ACCEPT_ADDRESS); }
            set { SetValue(CyParamNames.I2C_ACCEPT_ADDRESS, value); }
        }

        public bool I2C_AcceptGeneralCallAddress
        {
            get { return GetValue<bool>(CyParamNames.I2C_ACCEPT_GENERAL_CALL); }
            set { SetValue(CyParamNames.I2C_ACCEPT_GENERAL_CALL, value); }
        }

        public bool I2C_EnableWakeup
        {
            get { return GetValue<bool>(CyParamNames.I2C_ENABLE_WAKEUP); }
            set { SetValue(CyParamNames.I2C_ENABLE_WAKEUP, value); }
        }

        public bool I2C_ManualOversampleControl
        {
            get { return GetValue<bool>(CyParamNames.I2C_MANUAL_OVERSAMPLE_CONTROL); }
            set { SetValue(CyParamNames.I2C_MANUAL_OVERSAMPLE_CONTROL, value); }
        }

        #endregion

        #region Advanced tab properties

        public string I2C_BusVoltage
        {
            get { return GetValue<string>(CyParamNames.I2C_BUS_VOLTAGE); }
            set { SetValue(CyParamNames.I2C_BUS_VOLTAGE, value); }
        }

        #endregion

        #region Internal use properties

        public bool I2C_IsSlaveAddressHex
        {
            get { return GetValue<bool>(CyParamNames.I2C_IS_SLAVE_ADDRESS_HEX); }
            set { SetValue(CyParamNames.I2C_IS_SLAVE_ADDRESS_HEX, value); }
        }

        public bool I2C_IsSlaveAddressMaskHex
        {
            get { return GetValue<bool>(CyParamNames.I2C_IS_SLAVE_ADDRESS_MASK_HEX); }
            set { SetValue(CyParamNames.I2C_IS_SLAVE_ADDRESS_MASK_HEX, value); }
        }

        #endregion

        #region Oversampling calculation

        /// <summary>
        /// Calculates auto oversampling.
        /// </summary>
        /// <param name="ovsLow">Calculated oversampling low value.</param>
        /// <param name="ovsHigh">Calculated oversampling high value.</param>
        /// <returns>Indicated whether clock was read successfully.</returns>
        public bool GetAutoOversamplingLowHigh(out byte ovsLow, out byte ovsHigh)
        {
            double newDataRate;
            return GetAutoOversamplingLowHigh(out newDataRate, out ovsLow, out ovsHigh);
        }

        /// <summary>
        /// Calculates auto oversampling and actual data rate for new oversampling value.
        /// </summary>
        /// <param name="newDataRate">Actual data rate for new oversampling.</param>
        /// <param name="ovsLow">Calculated oversampling low value.</param>
        /// <param name="ovsHigh">Calculated oversampling high value.</param>
        /// <returns>Indicated whether clock was read successfully.</returns>
        public bool GetAutoOversamplingLowHigh(out double newDataRate, out byte ovsLow, out byte ovsHigh)
        {
            const byte I2C_OVS_FACTOR_HALF = CyParamRanges.I2C_OVS_FACTOR_MAX / 2;

            double accuracyCoeff = 1;
            // Get clock accuracy
            CyClockData sclkData = UART_ClockFromTerminal
                        ? CyParameters.GetExternalClockData(TermQuery)
                        : CyParameters.GetInternalClockData(TermQuery);


            ushort dataRate = I2C_DataRate;
            int lowIdeal = 0;
            int highIdeal = 0;
            byte lowMin = 0;
            byte highMin = 0;
            double period = 0;

            ovsLow = 0;
            ovsHigh = 0;

            double sclk = I2C_ClockFromTerminal
                        ? CyParameters.GetExternalClock(TermQuery)
                        : CyParameters.GetInternalClock(TermQuery);

            double sclkPlusAccuracy = Math.Round(sclk * accuracyCoeff);

            if (dataRate >= 0 && dataRate <= CyParamRanges.I2C_DATA_RATE_100)
            {
                lowIdeal = CyParamRanges.I2C_T_LOW_IDEAL_100KBPS;
                highIdeal = CyParamRanges.I2C_T_HIGH_IDEAL_100KBPS;
                lowMin = CyParamRanges.I2C_OVS_LOW_MIN_100KBPS;
                highMin = CyParamRanges.I2C_OVS_HIGH_MIN_100KBPS;
            }
            else if (dataRate > CyParamRanges.I2C_DATA_RATE_100 && dataRate <= CyParamRanges.I2C_DATA_RATE_400)
            {
                lowIdeal = CyParamRanges.I2C_T_LOW_IDEAL_400KBPS;
                highIdeal = CyParamRanges.I2C_T_HIGH_IDEAL_400KBPS;
                lowMin = CyParamRanges.I2C_OVS_LOW_MIN_400KBPS;
                highMin = CyParamRanges.I2C_OVS_HIGH_MIN_400KBPS;
            }
            else if (dataRate > CyParamRanges.I2C_DATA_RATE_400 && dataRate <= CyParamRanges.I2C_DATA_RATE_1000)
            {
                lowIdeal = CyParamRanges.I2C_T_LOW_IDEAL_1000KBPS;
                highIdeal = CyParamRanges.I2C_T_HIGH_IDEAL_1000KBPS;
                lowMin = CyParamRanges.I2C_OVS_LOW_MIN_1000KBPS;
                highMin = CyParamRanges.I2C_OVS_HIGH_MIN_1000KBPS;
            }

            if (sclkPlusAccuracy > 0)
                period = 1000000 / sclkPlusAccuracy;

            if (period > 0)
            {
                ovsLow = (byte)Math.Ceiling(lowIdeal / period);
                ovsHigh = (byte)Math.Ceiling(highIdeal / period);
            }

            if (ovsLow > I2C_OVS_FACTOR_HALF)
                ovsLow = I2C_OVS_FACTOR_HALF;
            if (ovsHigh > I2C_OVS_FACTOR_HALF)
                ovsHigh = I2C_OVS_FACTOR_HALF;
            if (ovsLow < lowMin)
                ovsLow = lowMin;
            if (ovsHigh < highMin)
                ovsHigh = highMin;

            int counter = 0;
            do
            {
                if (counter > 0)
                {
                    if (counter % 2 == 0 || ovsLow == I2C_OVS_FACTOR_HALF)
                        ovsHigh++;
                    else
                        ovsLow++; // ovsLow is always greater than ovsHigh since it increments first
                }
                counter++;

                newDataRate = sclk / (ovsLow + ovsHigh);

                if (ovsLow == I2C_OVS_FACTOR_HALF && ovsHigh == I2C_OVS_FACTOR_HALF)
                    break;
            }
            while (newDataRate > dataRate);

            newDataRate = Math.Round(newDataRate, 3);

            return (sclk > 0);
        }

        #endregion

        #region DRC

        public List<CyCustErr> GetI2cDrcErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            string errorMessage;

            if (IsScbIPV0 || IsScbIPV1)
            {
                // Check Byte mode
                if (I2C_EnableByteMode)
                {
                    errorList.Add(new CyCustErr(String.Format("{0}: {1}", CyESCBMode.I2C, Resources.ByteModeError)));
                }

                if (IsScbIPV0)
                {
                    // Slave address
                    errorMessage = CyI2CBasicTab.GetSlaveAddressError(I2C_SlaveAddress, this);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                    {
                        errorList.Add(new CyCustErr(errorMessage));
                    }
                    // Slave address mask
                    errorMessage = CyI2CBasicTab.GetSlaveAddressMaskError(I2C_SlaveAddressMask,
                        I2C_IsSlaveAddressMaskHex, this);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                    {
                        errorList.Add(new CyCustErr(errorMessage));
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
            errorMessage = GetI2CSlewRateError(true);
            if (String.IsNullOrEmpty(errorMessage) == false)
                errorList.Add(new CyCustErr(errorMessage));

            // Actual data rate
            if (m_i2cMode.Value == CyEI2CModeType.I2C_MULTI_MASTER_SLAVE && I2C_EnableWakeup)
            {
                double actualSampleRate = GetActualDataRate(SCBMode);
                if (actualSampleRate > CyParamRanges.I2C_DATA_RATE_400 + CyParamRanges.EPS)
                {
                    errorList.Add(new CyCustErr(Resources.ActualDataRateMultiMasterError));
                }
            }

            // Check if Actual data rate is not greater than requested for Master mode
            if (m_i2cMode.Value != CyEI2CModeType.I2C_SLAVE)
            {
                double actualDataRate;
                if (I2C_ManualOversampleControl)
                {
                    actualDataRate = GetActualDataRate(CyESCBMode.I2C);
                }
                else
                {
                    byte ovsLow;
                    byte ovsHigh;
                    GetAutoOversamplingLowHigh(out actualDataRate, out ovsLow, out ovsHigh);
                }

                if (I2C_ClockFromTerminal)
                {
                    double dataRateMax = CyParamRanges.GetI2cDataRateMaximum(IsScbIPV1, out errorMessage);
                    if (actualDataRate > dataRateMax)
                    {
                        errorList.Add(new CyCustErr(errorMessage));
                    }
                }
                else
                {
                    if (actualDataRate > I2C_DataRate + CyParamRanges.EPS)
                    {
                        errorList.Add(new CyCustErr(WARNING_CODE, Resources.ActualDataRateMaster));
                    }
                }
            }

            // External clock in the Slave mode
            if (m_i2cMode.Value == CyEI2CModeType.I2C_SLAVE && I2C_ClockFromTerminal)
            {
                double clkFreq = GetExternalClock(TermQuery);
                if (IsFrequencyKnown(clkFreq) &&
                    (clkFreq < CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS - CyParamRanges.EPS))
                {
                    errorList.Add(new CyCustErr(String.Format(Resources.I2cExternalClockLowError,
                        CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS_MHZ)));
                }
            }
            return errorList;
        }

        /// <summary>
        /// Gets error message for slew rate if exists any.
        /// </summary>
        /// <returns>Error message if exists any, otherwise empty string.</returns>
        public string GetI2CSlewRateError()
        {
            return GetI2CSlewRateError(false);
        }

        /// <summary>
        /// Gets error message for slew rate if exists any.
        /// </summary>
        /// <param name="isDRC">Indicates whenther generate message for DRC or GUI.</param>
        /// <returns>Error message if exists any, otherwise empty string.</returns>
        private string GetI2CSlewRateError(bool isDRC)
        {
            string errorMessage = String.Empty;

            if (m_i2cSlewRate.Value == CyESlewRateType.I2C_FM_PLUS)
            {
                double dataRate = I2C_ClockFromTerminal ? Math.Round(GetActualDataRate(CyESCBMode.I2C)) : I2C_DataRate;

                if (IsGpioOvtCapable() == false)
                {
                    errorMessage = Resources.OvtNotSupportedError;
                    if (isDRC)
                        errorMessage = String.Format("{0}: {1}", CyESCBMode.I2C, errorMessage);
                }
                else if (IsGpioOvtCapable() && dataRate <= CyParamRanges.I2C_DATA_RATE_400)
                {
                    errorMessage = String.Format(Resources.SlewRateDataRateError, CyParamRanges.I2C_DATA_RATE_400);
                    if (isDRC)
                        errorMessage = String.Format("{0}: {1}", CyESCBMode.I2C, errorMessage);
                }
            }

            return errorMessage;
        }

        #endregion
    }
}
