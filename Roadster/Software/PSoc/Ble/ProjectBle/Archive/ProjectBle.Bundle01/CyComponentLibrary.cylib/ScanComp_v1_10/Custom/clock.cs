/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ScanComp_v1_10
{
    public static class CyClock
    {
        private const double FREQUENCY_UNKNOWN = -1.0;
        private const string EXTERNAL_CLOCK = "clock";
        private const string INTERNAL_CLOCK_OR_GATE_NAME = "or_internal";

        public static double GetClockFrequencyHz(ICyTerminalQuery_v1 termQuery, bool isInternalClock)
        {
            List<CyClockData> clkdata = isInternalClock ?
                termQuery.GetClockData(INTERNAL_CLOCK_OR_GATE_NAME, "term0", 0) :
                termQuery.GetClockData(EXTERNAL_CLOCK, 0);

            if (clkdata.Count > 0 && clkdata[0].IsFrequencyKnown)
            {
                return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
            }
            return FREQUENCY_UNKNOWN;
        }

        public static bool IsFrequencyKnown(double frequency)
        {
            return Math.Abs(frequency - FREQUENCY_UNKNOWN) > CyParameters.EPS;
        }
    }
}
