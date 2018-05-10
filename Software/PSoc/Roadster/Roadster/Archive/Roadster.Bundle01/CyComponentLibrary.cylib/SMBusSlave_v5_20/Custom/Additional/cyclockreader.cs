/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SMBusSlave_v5_20
{
    public class CyClockReader
    {
        public const string EXTERNAL_CLOCK_TERMINAL_NAME = "clock";
        private const string INTERNAL_CLOCK_OR_GATE_FF_NAME = "or_ff";
        private const string INTERNAL_CLOCK_OR_GATE_UDB_NAME = "or_udb";

        /// <summary>
        /// Returns internal clock value in KHz based on implementation
        /// </summary>
        public static double GetInternalClockInKHz(ICyTerminalQuery_v1 termQuery, CyEImplementationType implementation, 
                                                   bool isPSoC4)
        {
            double clkData;
            if ((implementation == CyEImplementationType.I2C__FixedFunction) || isPSoC4)
                clkData = GetInternalClockInKHz(termQuery, INTERNAL_CLOCK_OR_GATE_FF_NAME);
            else
                clkData = GetInternalClockInKHz(termQuery, INTERNAL_CLOCK_OR_GATE_UDB_NAME);
            return clkData;
        }

        /// <summary>
        /// Returns internal clock value in KHz based on OR gate name
        /// </summary>
        private static double GetInternalClockInKHz(ICyTerminalQuery_v1 termQuery, string orGateName)
        {
            List<CyClockData> clkdata = new List<CyClockData>();
            clkdata = termQuery.GetClockData(orGateName, "term1", 0);
            if (clkdata.Count == 1)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                }
            }
            return -1;
        }

        /// <summary>
        /// Returns connected to component pin clock value in KHz
        /// </summary>
        public static double GetExternalClockInKHz(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = termQuery.GetClockData(EXTERNAL_CLOCK_TERMINAL_NAME, 0);
            if (clkdata.Count == 1)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                }
            }
            return -1;
        }

        public static bool IsFrequencyknown(double frequency)
        {
            return frequency > 0;
        }
    }
}
