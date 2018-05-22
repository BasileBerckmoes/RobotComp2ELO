/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    [Flags]
    public enum CyPinType
    {
        ANALOG = 0x01,
        DIGITAL_IN = 0x02,
        DIGITAL_OUT = 0x04,
        OE = 0x08,
        BIDIRECTIONAL = 0x10,
    }

    public enum CyDriveMode
    {
        STRONG_DRIVE,
        OPEN_DRAIN_DRIVE_LOW,
        OPEN_DRAIN_DRIVE_HIGH,
        RESISTIVE_PULL_UP,
        RESISTIVE_PULL_DOWN,
        RESISTIVE_PULL_UP_DOWN,
        HIGH_IMPEDANCE_ANALOG,
        HIGH_IMPEDANCE_DIGITAL,
    }

    public enum CyInputThreshold
    {
        CMOS,
        CMOS_LVTTL,
        LVTTL,
        PT4_VDDIO,
        PT5_VDDIO,
        PT5_VREF,
        VREF,
    }

    public enum CyInputInterruptTrigger
    {
        NONE,
        RISING_EDGE,
        FALLING_EDGE,
        BOTH_EDGES,
    }

    public enum CyInputSyncMode
    {
        TRANSPARENT,
        SINGLE_SYNC,
        DOUBLE_SYNC,
    }

    public enum CyOutputSlewRate
    {
        FAST,
        SLOW,
    }

    public enum CyOutputDriveLevel
    {
        VDDIO,
        VREF,
    }

    public enum CyOutputCurrent
    {
        SOURCE_4MA_SINK_8MA,
        SOURCE_4MA_SINK_25MA,
    }

    public enum CyOutputMode
    {
        TRANSPARENT,
        SINGLE_SYNC,
        CLOCK,
        CLOCK_INV,
    }

    public enum CyPowerOnRestMode
    {
        UNSPECIFIED, 
        HIZ_ANALOG, 
        PULLED_UP, 
        PULLED_DOWN,
    }

    public enum CyPinClock
    {
        HFCLK,
        HFCLK_INV,
        EXTERNAL,
        EXTERNAL_INV,
        PIN,
        PIN_INV,
    }

    public enum CyPinClockEnable
    {
        LEVEL,
        RISING_EDGE,
    }

    public enum CyPinClockEnRst
    {
        NONE,
        EXTERNAL,
        EXTERNAL_INV,
        PIN,
        PIN_INV,
    }
}
