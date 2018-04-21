/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;

namespace TCPWM_Counter_PDL_v1_0.Utils
{
    internal static class CyMath
    {
        public static double GetPeriodFreq(double clockFreqKHz, byte clockPrescaler, uint period)
        {
            double counterClock = GetCounterClock(clockFreqKHz, clockPrescaler);
            return Math.Round(counterClock / (period + 1), 3);
        }

        public static double GetCounterClock(double clockFreqKHz, byte clockPrescaler)
        {
            Debug.Assert(clockPrescaler > 0);
            return (clockPrescaler > 0) ? clockFreqKHz / clockPrescaler : 1;
        }
    }
}