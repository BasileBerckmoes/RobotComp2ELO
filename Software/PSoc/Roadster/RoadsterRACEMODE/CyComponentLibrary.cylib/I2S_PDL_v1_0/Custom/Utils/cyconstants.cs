/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace I2S_PDL_v1_0.Utils
{
    internal class CyConstants
    {
        public const byte CLOCK_DIVIDER_MIN = 1;
        public const byte CLOCK_DIVIDER_MAX = 64;
        public const byte FIFO_TRIGGER_LEVEL_MIN = byte.MinValue;
        public const byte FIFO_TRIGGER_LEVEL_MAX = byte.MaxValue;
        public const byte FIFO_TRIGGER_LEVEL_RX_MAX = 253; // Per TRM
        public const uint WATCHDOG_VALUE_MIN = uint.MinValue;
        public const uint WATCHDOG_VALUE_MAX = uint.MaxValue;
        public const byte MASTER_CLOCK_DIVIDER = 8;
        public const byte CHANNELS = 2;
    }
}