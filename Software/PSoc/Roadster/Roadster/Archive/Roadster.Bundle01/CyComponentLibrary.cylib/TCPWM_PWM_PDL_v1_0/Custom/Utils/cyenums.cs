/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System.Diagnostics;

namespace TCPWM_PWM_PDL_v1_0.Utils
{
    internal class CyEnums
    {
        public const string ENUM_VALUE_INPUT_LEVEL = "Level";
        public const string ENUM_VALUE_INPUT_RISING_EDGE = "Rising Edge";
        public const string ENUM_VALUE_KILLMODE_SYNCHRONOUS = "Synchronous Kill";

        #region Enums
        public enum CyMode { MODE_PWM = 4, MODE_DEADTIME = 5, MODE_PSEUDORANDOM = 6 }

        public enum CyAlignment { LEFT, RIGHT, CENTER, ASYMMETRIC }

        public enum CyRunMode { CONTINUOUS, ONE_SHOT }

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

        public enum CyResolution
        {
            WIDTH_16_BITS = 16,
            WIDTH_32_BITS = 32
        }

        public enum CyKillMode
        {
            ASYNC_KILL,
            SYNCH_KILL,
            STOP_ON_KILL
        }
        #endregion

        #region Enum convertation
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
        #endregion
    }
}
