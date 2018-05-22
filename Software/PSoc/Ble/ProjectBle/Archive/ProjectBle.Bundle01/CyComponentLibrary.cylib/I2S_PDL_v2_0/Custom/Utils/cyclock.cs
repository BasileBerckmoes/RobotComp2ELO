/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;

namespace I2S_PDL_v2_0.Utils
{
    public class CyClock
    {
        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public static double GetInternalClockKhz(ICyTerminalQuery_v1 termQuery)
        {
            return GetClockKhz(termQuery, "cy_mxs40_i2s", true);
        }

        public static double GetExternalClockKhz(ICyTerminalQuery_v1 termQuery)
        {
            return GetClockKhz(termQuery, "clock", false);
        }

        private static double GetClockKhz(ICyTerminalQuery_v1 termQuery, string termName, bool internalClock)
        {
            List<CyClockData> clkdata = internalClock ? termQuery.GetClockData(termName, "clock", 0) :
                                                        termQuery.GetClockData(termName, 0);
            if (clkdata.Count > 0)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                }
            }
            return -1;
        }

        public static bool IsFrequencyKnown(double frequency)
        {
            return frequency > 0;
        }
    }
}