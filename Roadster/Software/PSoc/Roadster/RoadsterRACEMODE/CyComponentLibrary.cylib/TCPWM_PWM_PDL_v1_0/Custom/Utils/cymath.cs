/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;

namespace TCPWM_PWM_PDL_v1_0.Utils
{
    internal static class CyMath
    {
        public const double EPS = 10E-8; 
        public static double GetDutyCyclePercentage(CyEnums.CyAlignment alignment, uint period, uint compare)
        {
            double result = 0;

            switch (alignment)
            {
                case CyEnums.CyAlignment.LEFT:
                    result = Math.Round((double)compare / (period + 1) * 100, 2);
                    break;
                case CyEnums.CyAlignment.RIGHT:
                    result = (compare > period) ? 0 : Math.Round(((double)compare + 1) / (period + 1) * 100, 2);
                    break;
                case CyEnums.CyAlignment.CENTER:
                case CyEnums.CyAlignment.ASYMMETRIC:
                    result = (compare == period) ? 0 : Math.Round((1 - (double)compare / period) * 100, 2);
                    break;
                default:
                    Debug.Fail("Unhandled enum item " + alignment);
                    break;
            }
            if (Double.IsNaN(result))
                result = 0;
            if (result > 100)
                result = 100;
            return result;
        }

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