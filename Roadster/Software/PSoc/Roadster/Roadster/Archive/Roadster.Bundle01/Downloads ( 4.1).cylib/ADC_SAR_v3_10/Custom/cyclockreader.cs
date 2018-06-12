/*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ADC_SAR_v3_10
{
    public static class CyClockReader
    {
        public const string EXTERNAL_CLK = "aclk";
        public const string INTERNAL_CLK = "_theACLK";
        public const string INTERNAL_CLK_OR_GATE = "or_internalClock";

        public static double GetInternalClockInKHz(ICyDesignQuery_v1 designQuery, string instanceName)
        {
            double freq = GetInternalClockInHz(designQuery, instanceName);
            if (freq > 0)
                freq /= 1000;
            return freq;
        }

        // Returns internal clock value in Hz
        public static double GetInternalClockInHz(ICyDesignQuery_v1 designQuery, string instanceName)
        {
            string clockName = instanceName + INTERNAL_CLK;
            double result = -1;
            try
            {
                if (designQuery.ClockIDs != null)
                {
                    double clockfr;
                    byte out_b;
                    string clockID = GetClockID(designQuery, clockName);
                    if (string.IsNullOrEmpty(clockID) == false)
                    {
                        designQuery.GetClockActualFreq(clockID, out clockfr, out out_b);
                        result = Math.Round(clockfr * Math.Pow(10, out_b), 3);
                    }
                }
            }
            catch
            {
                result = -1;
            }
            return result;
        }

        public static double GetExternalClockInHz(ICyTerminalQuery_v1 termQuery)
        {
            return GetExternalClockInKHz(termQuery) * 1000;
        }

        // Returns external clock value in kHz
        public static double GetExternalClockInKHz(ICyTerminalQuery_v1 termQuery)
        {
            double freq = -1;
            List<CyClockData> clkdata = termQuery.GetClockData(EXTERNAL_CLK, 0);
            if (clkdata.Count == 1)
            {
                freq = GetClockFrequencyKHz(clkdata[0]);
            }
            return freq;
        }

        public static double GetClockFrequencyMHz(CyClockData clockData)
        {
            return Math.Round(GetClockFrequencyKHz(clockData) / 1000, 3);
        }

        public static double GetClockFrequencyKHz(CyClockData clockData)
        {
            double freq = -1;
            if (clockData.IsFrequencyKnown)
            {
                freq = clockData.Frequency * Math.Pow(10, clockData.UnitAsExponent - 3);
                freq = Math.Round(freq, 3);
            }
            return freq;
        }

        public static string GetClockID(ICyDesignQuery_v1 designQuery, string clockName)
        {
            string clockID = string.Empty;
            try
            {
                List<string> clockIDs = new List<string>(designQuery.ClockIDs);

                for (int i = 0; i < clockIDs.Count; i++)
                {
                    if (designQuery.GetClockName(clockIDs[i]) == clockName)
                    {
                        clockID = clockIDs[i];
                        break;
                    }
                }
            }
            catch (Exception)
            {
                clockID = string.Empty;
            }
            return clockID;
        }
    }
}
