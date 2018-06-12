/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System.Diagnostics;
using CyDesigner.Extensions.Gde;
using System;

namespace SMBusSlave_v5_20
{
    public static class CyDividerCalculator
    {
        private const int OVS_FACTOR = 16;
        private const int OVS_FACTOR_FF_BELOW_THRESHOLD = 32;

        private static byte GetOversampleRate(ushort dataRate)
        {
            return (byte)((dataRate <= CyParamRange.DATA_RATE_THRESHOLD) ? OVS_FACTOR_FF_BELOW_THRESHOLD : OVS_FACTOR);
        }

        public static byte GetDivider(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyParameters parameters = new CyParameters(query);

            byte divider = 0;
            double busClockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation, 
                                                                       parameters.IsPSoC4);
            byte oversampleRate = GetOversampleRate(parameters.DataRate);
            if (CyClockReader.IsFrequencyknown(busClockInKHz) && (oversampleRate > 0) && (parameters.DataRate > 0))
            {
                divider = (byte)(busClockInKHz / (parameters.DataRate * oversampleRate));
            }

            return divider;
        }
                
        public static string GetActualDataRateCalculatorLabel(CyParameters parameters, ICyTerminalQuery_v1 termQuery)
        {
            string labelText = Resources.UnknownActualDataRate;
            double actualDataRate;

            // This clock depends on implementation - BusClock in FF and Internal in UDB
            double clockInKHz = parameters.IsClockExternal ? CyClockReader.GetExternalClockInKHz(termQuery) :
                CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation, parameters.IsPSoC4);

            if (parameters.IsPSoC4)
            {
                if (CyClockReader.IsFrequencyknown(clockInKHz))
                {
                    if (parameters.IsClockExternal)
                    {
                        if (clockInKHz < CyParamRange.I2C_SLAVE_FSCB_MIN_100KBPS - CyParamRange.EPS)
                        {
                            // Clock is too low
                            actualDataRate = 0;
                        }
                        else if (clockInKHz < CyParamRange.I2C_SLAVE_FSCB_MIN_400KBPS - CyParamRange.EPS)
                        {
                            actualDataRate = CyParamRange.DATA_RATE_100;
                        }
                        else
                        {
                            actualDataRate = CyParamRange.DATA_RATE_400;
                        }
                    }
                    else
                    {
                        actualDataRate = Math.Max((int)parameters.DataRate, CyParamRange.DATA_RATE_100);
                    }

                    labelText = FormatActualDataRate(actualDataRate);
                }
            }
            else if (parameters.Implementation == CyEImplementationType.I2C__UDB)
            {
                labelText = CyClockReader.IsFrequencyknown(clockInKHz) ? FormatActualDataRate(clockInKHz / OVS_FACTOR) : 
                    Resources.UnknownActualDataRate;
            }
            else
            {
                if (CyClockReader.IsFrequencyknown(clockInKHz))
                {
                    // Actual Data Rate Calculation
                    try
                    {
                        byte divider = GetDivider(parameters.InstQuery, termQuery);
                        double oversampleRate = GetOversampleRate(parameters.DataRate);
                        if (divider > 0 && oversampleRate > 0)
                        {
                            actualDataRate = clockInKHz / (divider * oversampleRate);
                            labelText = FormatActualDataRate(actualDataRate);
                        }
                    }
                    catch (Exception)
                    {
                       Debug.Fail("Divider calculation failed");
                    }
                }
            }
            return labelText;
        }

        public static int CalculateTimeout(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            if (instEdit == null || termQuery == null)
                return -1;

            const ushort MAX_PRESCALER_PERIOD = 128;
            int countMax = (int)Math.Pow(2, 16);

            CyParameters parameters = new CyParameters(instEdit, termQuery);

            parameters.GlobalEditMode = true;

            double clockInKHz = parameters.IsClockExternal ? CyClockReader.GetExternalClockInKHz(termQuery) :
               CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation, parameters.IsPSoC4);

            // FF calculation
            if (CyClockReader.IsFrequencyknown(clockInKHz) && parameters.IsPSoC4 == false &&
                parameters.Implementation == CyEImplementationType.I2C__FixedFunction)
            {
                double tclk = 1 / (clockInKHz / 1000);
                UInt16 div = Convert.ToUInt16(Math.Ceiling(parameters.TimeOutMs / tclk));
                parameters.TimeoutPeriodFF = (div > CyParamRange.FF_DIVIDER_MAX) ? CyParamRange.FF_DIVIDER_MAX : div;
            }

            // UDB calculation && PSoC 4
            if (CyClockReader.IsFrequencyknown(clockInKHz) &&
                (parameters.Implementation == CyEImplementationType.I2C__UDB || parameters.IsPSoC4))
            {
                double count = parameters.TimeOutMs * clockInKHz;
                if (count <= countMax)
                {
                    count--;
                    parameters.TimeoutPeriodUDB = Convert.ToUInt16(Math.Ceiling(count));
                    parameters.PrescalerEnabled = false;
                    parameters.PrescalerPeriod = 0;
                }
                else
                {
                    parameters.PrescalerEnabled = true;
                    UInt16 prescalerPeriod = 1;
                    while ((count / prescalerPeriod) >= countMax)
                    {
                        prescalerPeriod *= 2;
                        if (prescalerPeriod == MAX_PRESCALER_PERIOD)
                            break;
                    }
                    parameters.TimeoutPeriodUDB = Convert.ToUInt16(Math.Ceiling(count / prescalerPeriod));
                    parameters.TimeoutPeriodUDB--;
                    if (parameters.IsPSoC4)
                    {
                        prescalerPeriod = (ushort)Math.Log(prescalerPeriod, 2);
                    }
                    else
                    {
                        prescalerPeriod--;
                    }
                    parameters.PrescalerPeriod = Convert.ToByte(prescalerPeriod);
                }
            }
            return parameters.PrescalerPeriod;
        }

        private static string FormatActualDataRate(double dataRateValue)
        {
            const string DATA_RATE_UNITS = "kbps";

            return (dataRateValue > 0) ? 
                string.Format("{0} {1}", Math.Round(dataRateValue, 2), DATA_RATE_UNITS) : 
                Resources.ErrorActualDataRate;
        }
    }
}
