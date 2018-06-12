/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;

namespace TMP05Intf_v1_10
{
    public class CyClockReader
    {
        /// <summary>
        /// Returns connected to component terminal clock value in KHz
        /// </summary>
        public static double GetExternalClockInKHz(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = new List<CyClockData>();
            clkdata = termQuery.GetClockData("clock", 0);
            if (clkdata.Count == 1)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return Math.Round(clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3), 3);
                }
            }
            return -1;
        }
    }
}
