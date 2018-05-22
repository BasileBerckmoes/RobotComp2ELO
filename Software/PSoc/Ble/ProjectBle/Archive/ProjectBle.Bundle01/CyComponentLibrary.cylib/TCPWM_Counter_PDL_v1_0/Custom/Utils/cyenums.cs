/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System.Diagnostics;

namespace TCPWM_Counter_PDL_v1_0.Utils
{
    internal class CyEnums
    {
        public enum CyClockPrescaler
        {
            PRESCALER_DIVBY_1,
            PRESCALER_DIVBY_2,
            PRESCALER_DIVBY_4,
            PRESCALER_DIVBY_8,
            PRESCALER_DIVBY_16,
            PRESCALER_DIVBY_32,
            PRESCALER_DIVBY_64,
            PRESCALER_DIVBY_128
        }

        public enum CyRunMode
        {
            CONTINUOUS,
            ONE_SHOT
        }

        public enum CyCountDirection
        {
            COUNT_UP,
            COUNT_DOWN,
            COUNT_UPDOWN0,
            COUNT_UPDOWN1
        }

        public enum CyCompareOrCapture
        {
            MODE_COMPARE = 0,
            MODE_CAPTURE = 2
        }

        public enum CyInputMode
        {
            INPUT_RISINGEDGE,
            INPUT_FALLINGEDGE,
            INPUT_EITHEREDGE,
            INPUT_LEVEL,
            INPUT_DISABLED = 7
        }

        public enum CyInputParameter
        {
            Capture,
            Reload,
            Stop,
            Start,
            Count
        }

        public enum CyCounterResolution
        {
            WIDTH_16_BITS = 16,
            WIDTH_32_BITS = 32
        }

        public enum CyInterruptSources
        {
            INT_NONE,
            INT_ON_TC,
            INT_ON_CC,
            INT_ON_TC_CC
        }

        public static byte ToDisplayValue(CyClockPrescaler enumItem)
        {
            switch (enumItem)
            {
                case CyClockPrescaler.PRESCALER_DIVBY_1:
                    return 1;
                case CyClockPrescaler.PRESCALER_DIVBY_2:
                    return 2;
                case CyClockPrescaler.PRESCALER_DIVBY_4:
                    return 4;
                case CyClockPrescaler.PRESCALER_DIVBY_8:
                    return 8;
                case CyClockPrescaler.PRESCALER_DIVBY_16:
                    return 16;
                case CyClockPrescaler.PRESCALER_DIVBY_32:
                    return 32;
                case CyClockPrescaler.PRESCALER_DIVBY_64:
                    return 64;
                case CyClockPrescaler.PRESCALER_DIVBY_128:
                    return 128;
                default:
                    Debug.Fail("unhandled enum item.");
                    return 1;
            }
        }
    }
}
