/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using CyDesigner.Common.Base;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit.TerminalControl_v1;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_20
{
    public class CyPinData
    {
        public enum ErrorMgrKey
        {
            TYPE_IS_ANALOG,
            TYPE_IS_DIGITAL_IN,
            TYPE_IS_DIGITAL_IN_HW,
            TYPE_IS_DIGITAL_OUT,
            TYPE_IS_DIGITAL_OUT_HW,
            TYPE_IS_DIGITAL_OUT_OE,
            TYPE_IS_BIDIRECTIONAL,
            TYPE_SHOW_EXTERNAL_TERM,

            GENERAL_DRIVE_MODE,
            GENERAL_INITIAL_STATE,
            GENERAL_MINIMUM_SUPPLY,
            GENERAL_TYPE,

            INPUT_THRESHOLD,
            INPUT_HYSTERESIS,
            INPUT_INTERRUPT,
            INPUT_HOT_SWAP,
            INPUT_BUFFER_ENABLED,
            INPUT_SYNC_MODE,
            INPUT_MULTIPLIER,

            OUTPUT_SLEW_RATE,
            OUTPUT_DRIVE_LEVEL,
            OUTPUT_CURRENT,
            OUTPUT_MODE,
            OUTPUT_ENABLE_SYNCHRONIZED,
            OUTPUT_MULTIPLIER,

            MAPPING_DISPLAY_AS_BUS,
            MAPPING_CONTIGIOUS,
            MAPPING_SPANNING,

            POWER_ON_RESET,

            CLOCK_INPUT,
            CLOCK_INPUT_ENABLE,
            CLOCK_INPUT_ENABLE_ON,
            CLOCK_INPUT_RESET,
            CLOCK_OUTPUT,
            CLOCK_OUTPUT_ENABLE,
            CLOCK_OUTPUT_ENABLE_ON,
            CLOCK_OUTPUT_RESET,
            CLOCK_OUTPUT_RESET_ENABLE,
            CLOCK_OE_RESET_ENABLE,
        }

        #region Setting Values (Formal parameters)
        internal const string ParamValue_FALSE = "0";
        internal const string ParamValue_TRUE = "1";

        internal const string ParamValue_DISABLED = "0";
        internal const string ParamValue_ENABLED = "1";

        internal const int PORValue_Unspecified = 4;
        internal const int PORValue_HiZAnalog = 0;
        internal const int PORValue_PulledUp = 2;
        internal const int PORValue_PulledDown = 3;
        internal const int DefaultPORValue = PORValue_Unspecified;

        internal const string DefaultDisplay = ParamValue_TRUE;

        internal const string VTripValue_CMOS = "00";
        internal const string VTripValue_LVTTL = "01";
        internal const string VTripValue_CMOS_OR_LVTTL = "10";
        internal const string DefaultVTripValue = VTripValue_CMOS;

        internal const string DefaultInputBufferValue = ParamValue_TRUE;

        internal const string InputsSyncModeValue_DOUBLE = "0";
        internal const string InputsSyncModeValue_SINGLE = "1";
        internal const string DefaultInputsSyncModeValue = InputsSyncModeValue_DOUBLE;

        internal const string ClkEnableModeValue_EDGE = "0";
        internal const string ClkEnableModeValue_LEVEL = "1";
        internal const string DefaultClkEnableModeValue = ClkEnableModeValue_EDGE;

        internal const string DefaultOutputsSynchronizedValue = ParamValue_DISABLED;

        internal const string DefaultOESyncsValue = ParamValue_FALSE;

        internal const string OutputModesValue_DATA = "0";
        internal const string OutputModesValue_CLOCK = "1";
        internal const string DefaultOutputModesValue = OutputModesValue_DATA;

        internal const string OutputClockModesValue_NORMAL = "0";
        internal const string OutputClockModesValue_INVERTED = "1";
        internal const string DefaultOutputClockModesValue = OutputClockModesValue_NORMAL;

        internal const string OutputComboMode_DATA_TRANSPARENT = "00";
        internal const string OutputComboMode_DATA_SINGLESYNC = "01";
        internal const string OutputComboMode_CLOCK_NORMAL = "10";
        internal const string OutputComboMode_CLOCK_INVERTED = "11";
        internal const string DefaultOutputModeValue = OutputComboMode_DATA_TRANSPARENT;

        internal const string DefaultOEResetsValue = ParamValue_DISABLED;

        internal const string DefaultOutputResetsValue = ParamValue_DISABLED;

        //The default value us dependant on the DriveMode. (ResPullUp or ResPullUpDown = 1, others = 0).
        internal const string InitialDriveStateValue_LOW = "0";
        internal const string InitialDriveStateValue_HIGH = "1";

        internal const string DriveCurrentValue_4SOURCE_8SINK = "0";
        internal const string DriveCurrentValue_4SOURCE_25SINK = "1";
        internal const string DriveCurrentValue_4SOURCE_10SINK = "2";
        internal const string DefaultDriveCurrentValue = DriveCurrentValue_4SOURCE_8SINK;

        internal const string OutputDriveLevelValue_VDDIO = "0";
        internal const string OutputDriveLevelValue_VREF = "1";
        internal const string OutputDriveLevelValue_VREF_INTERNAL = "2";
        internal const string DefaultOutputDriveLevelValue = OutputDriveLevelValue_VDDIO;

        internal const string DefaultHotSwapValue = ParamValue_FALSE;

        internal const string SIOInfoValue_NOT_SIO = "00";
        internal const string SIOInfoValue_SINGLE_SIO = "01";
        internal const string SIOInfoValue_FIRST_IN_SIO_PAIR = "10";
        internal const string SIOInfoValue_SECOND_IN_SIO_PAIR = "11";
        internal const string DefaultSIOInfoValue = SIOInfoValue_NOT_SIO;

        internal const string SIOGroupValue_NOT_GROUPED = "0";
        internal const string SIOGroupValue_GROUPED = "1";
        internal const string DefaultSIOGroupValue = SIOGroupValue_NOT_GROUPED;

        internal const string SlewRateValue_FAST = "0";
        internal const string SlewRateValue_SLOW = "1";
        internal const string SlewRateValue_I2C_FM = "2";
        internal const string SlewRateValue_I2C_HS_SLOW = "3";
        internal const string SlewRateValue_I2C_HS_FAST = "4";
        internal const string DefaultSlewRateValue = SlewRateValue_FAST;

        internal const string InterruptModeValue_NONE = "00";
        internal const string InterruptModeValue_RISING_EDGE = "01";
        internal const string InterruptModeValue_FALLING_EDGE = "10";
        internal const string InterruptModeValue_ON_CHANGE = "11";
        internal const string DefaultInterruptModeValue = InterruptModeValue_NONE;

        // Default to true for BWC. For new pins we want to default to false; we'll handle that in the schematic macro
        internal const string DefaultDedicatedInterrupt = ParamValue_ENABLED;

        internal const string InputSyncModeValue_TRANSPARENT = "00";
        internal const string InputSyncModeValue_SINGLESYNC = "01";
        internal const string InputSyncModeValue_DOUBLESYNC = "10";

        internal const string ThresholdLevelValue_CMOS = "0000";
        internal const string ThresholdLevelValue_LVTTL = "0001";
        internal const string ThresholdLevelValue_CMOS_LVTTL = "0010";
        internal const string ThresholdLevelValue_PT5_VDDIO = "0011";
        internal const string ThresholdLevelValue_PT4_VDDIO = "0100";
        internal const string ThresholdLevelValue_PT5_VREF = "0101";
        internal const string ThresholdLevelValue_VREF = "0110";
        internal const string ThresholdLevelValue_PT5_VDDIO_HYST = "0111";
        internal const string ThresholdLevelValue_PT4_VDDIO_HYST = "1000";
        internal const string ThresholdLevelValue_PT5_VREF_HYST = "1001";
        internal const string ThresholdLevelValue_VREF_HYST = "1010";
        internal const string ThresholdLevelValue_CMOS_1PT8V = "1011";
        internal const string ThresholdLevelValue_VREF_INTERNAL = "1100";
        internal const string ThresholdLevelValue_VREF_INTERNAL_HYST = "1101";
        internal const string ThresholdLevelValue_PT5_VREF_INTERNAL = "1110";
        internal const string ThresholdLevelValue_PT5_VREF_INTERNAL_HYST = "1111";
        internal const string DefaultThresholdLevelValue = ThresholdLevelValue_CMOS;

        internal const string HysteresisModeValue_OFF = "00";
        internal const string HysteresisModeValue_STANDARD = "01";
        internal const string HysteresisModeValue_IMPROVED = "10";
        internal const string DefaultHysteresisModeValue = HysteresisModeValue_STANDARD;

        //The default value is dependant on the PinType.
        internal const string DriveModeValue_ANALOG_HI_Z = "000"; //High Impedance Analog
        internal const string DriveModeValue_DIGITAL_HI_Z = "001"; //High Impedance Digital
        internal const string DriveModeValue_RES_PULL_UP = "010";
        internal const string DriveModeValue_RES_PULL_DOWN = "011";
        internal const string DriveModeValue_OPEN_DRAIN_LO = "100";
        internal const string DriveModeValue_OPEN_DRAIN_HI = "101";
        internal const string DriveModeValue_CMOS_OUT = "110"; //Strong Drive
        internal const string DriveModeValue_RES_PULL_UP_DOWN = "111";
        internal const string DefaultDriveModeValue = DriveModeValue_CMOS_OUT;

        internal const string DefaultLCDComSegValue = ParamValue_FALSE;

        //The default value is dependant on the PinType. (Input or BiDir used = 1, others = 0).

        internal const string DefaultEnableShieldingValue = ParamValue_FALSE;

        internal const string DefaultSIOHysteresisValue = ParamValue_FALSE;

        internal const string LayoutModeValue_CONT_SPANNING = "1";
        internal const string LayoutModeValue_CONT_NONSPANNING = "2";
        internal const string LayoutModeValue_NONCONT_SPANNING = "3";
        internal const string LayoutModeValue_NONCONT_NONSPANNING = "4";

        internal const string PinTypesValue_DIGIN = "0000";
        internal const string PinTypesValue_DIGOUT = "0001";
        internal const string PinTypesValue_ANALOG = "0010";
        internal const string PinTypesValue_BIDIRECTIONAL = "0011";
        internal const string PinTypesValue_DIGIN_ANALOG = "0100";
        internal const string PinTypesValue_DIGOUT_DIGIN = "0101";
        internal const string PinTypesValue_DIGOUT_OE = "0110";
        internal const string PinTypesValue_DIGOUT_DIGIN_OE = "0111";
        internal const string PinTypesValue_DIGOUT_ANALOG = "1000";
        internal const string PinTypesValue_BIDIRECTIONAL_ANALOG = "1001";
        internal const string PinTypesValue_DIGOUT_DIGIN_ANALOG = "1010";
        internal const string PinTypesValue_DIGOUT_OE_ANALOG = "1011";
        internal const string PinTypesValue_DIGOUT_OE_DIGIN_ANALOG = "1100";
        internal const string PinTypesValue_NONE = "1101";
        internal const string DefaultPinTypesValue = PinTypesValue_DIGIN;

        internal const string DefaultIOVoltageValue = "None";
        internal const string MultipleIOVoltageValue = "Multiple";

        internal const string DefaultShowAnnotValue = ParamValue_FALSE;
        #endregion

        #region Settings Values (HW Params)

        internal const string SIOVTripValue_PT5 = "0";
        internal const string SIOVTripValue_PT4_OR_ONE = "1";

        internal const string OVTVTripValue_CMOS_LVTTL = "00";
        internal const string OVTVTripValue_CMOS_1PT8V = "01";

        internal const string SIORefSelValue_VCC_IO = "0";
        internal const string SIORefSelValue_VOHREF = "1";
        internal const string DefaultSIORefSelValue = SIORefSelValue_VCC_IO;

        internal const string SIOInputBufferValue_SINGLE_ENDED = "0";
        internal const string SIOInputBufferValue_DIFFERENTIAL = "1";

        public const string SIOOutputBufferValue_UNREGULATED = "0";
        public const string SIOOutputBufferValue_REGULATED = "1";

        // Note that the values of the following eight variables are not all unique.
        // This is intentional; there are eight possible configurations which map into four register values, so
        // by the pidgeonhole principle there will be some overlap, but we keep them separate to align with
        // the configuration combinations which the user will create
        internal const string OVTSlewRate_Fast = "00"; // Fast and Slow are differentiated by the "normal" 
        internal const string OVTSlewRate_Slow = "00"; // fast/slow selection passed via slew_rate
        internal const string OVTSlewRate_FMLowVDDIO = "11"; // FM+ <= 2.8V
        internal const string OVTSlewRate_FMHighVDDIO = "01"; // FM+ > 2.8V
        internal const string OVTSlewRate_HSSlowLowVDDIO =  "11"; // HS <= 1.7Mbps, vddio <= 2.8V
        internal const string OVTSlewRate_HSSlowHighVDDIO = "01"; // HS <= 1.7Mbps, vddio > 2.8V
        internal const string OVTSlewRate_HSFastLowVDDIO =  "10"; // HS > 1.7Mbps, vddio <= 3V
        internal const string OVTSlewRate_HSFastHighVDDIO = "00"; // HS > 1.7Mbps, vddio > 3V
        #endregion

        public const string Builtin_ParamName_InstName = "INSTANCE_NAME";

        public const int PINS_PER_PORT = 8;

        public static readonly double[] VrefMultiplierValues = 
        {
            1,
            1.25,
            1.49,
            1.67,
            2.08,
            2.5,
            2.78,
            4.16
        };

        internal const int DefaultMultiplierIdx = 0;
        internal const double DefaultMultiplier = 1; // Multiplier for non-vddio or -vref based modes

        // These values are not stored in a separate formal parameter; for BWC purposes 0.4*vddio and 0.5*vddio
        // are still stored as separate threshold entries, but we break them out into the dropdown for consistency.
        public static readonly double[] VddioMultiplierValues = 
        {
            0.4,
            0.5
        };


        #region Formals
        internal const string Formal_ParamName_NumPins = "NumPins";
        internal const string Formal_ParamName_PinTypes = "PinTypes";
        internal const string Formal_ParamName_DisplayAsBus = "DisplayAsBus";
        internal const string Formal_ParamName_SIOGroups = "SIOGroups";
        internal const string Formal_ParamName_HotSwaps = "HotSwaps";
        internal const string Formal_ParamName_ThresholdLevels = "ThresholdLevels";
        internal const string Formal_ParamName_HysteresisModes = "HysteresisModes";
        internal const string Formal_ParamName_OutputDriveLevels = "OutputDriveLevels";
        internal const string Formal_ParamName_DriveCurrents = "DriveCurrents";
        internal const string Formal_ParamName_DisplayInputHWConnections = "DisplayInputHWConnections";
        internal const string Formal_ParamName_DisplayOutputHWConnections = "DisplayOutputHWConnections";
        internal const string Formal_ParamName_InputBuffersEnabled = "InputBuffersEnabled";
        internal const string Formal_ParamName_LayoutMode = "LayoutMode";
        internal const string Formal_ParamName_SlewRate = "SlewRates";
        internal const string Formal_ParamName_InterruptMode = "InterruptModes";
        internal const string Formal_ParamName_DedicatedInterrupt = "DedicatedInterrupts";
        internal const string Formal_ParamName_DriveMode = "DriveModes";
        internal const string Formal_ParamName_PinAlisases = "PinAliases";
        internal const string Formal_ParamName_InitialDriveStates = "InitialDriveStates";
        internal const string Formal_ParamName_InputsSynchronized = "InputSyncs";
        internal const string Formal_ParamName_InputsSyncMode = "InputSyncModes";
        internal const string Formal_ParamName_IOVoltages = "IOVoltages";
        internal const string Formal_ParamName_OutputsSynchronized = "OutputSyncs";
        internal const string Formal_ParamName_PowerOnReset = "PowerOnResetState";
        internal const string Formal_ParamName_ShowAnnotationTerm = "ShowAnnotationTerm";
        internal const string Formal_ParamName_ShowInClkTerm = "ShowInClkTerm";
        internal const string Formal_ParamName_ShowInClkEnTerm = "ShowInClkEnTerm";
        internal const string Formal_ParamName_ShowInRstTerm = "ShowInRstTerm";
        internal const string Formal_ParamName_ShowOutClkTerm = "ShowOutClkTerm";
        internal const string Formal_ParamName_ShowOutClkEnTerm = "ShowOutClkEnTerm";
        internal const string Formal_ParamName_ShowOutRstTerm = "ShowOutRstTerm";
        internal const string Formal_ParamName_OutputModes = "OutputModes";
        internal const string Formal_ParamName_OutputClockModes = "OutputClockModes";
        internal const string Formal_ParamName_OESyncs = "OESyncs";
        internal const string Formal_ParamName_OutClkEnableMode = "OutClkEnableMode";
        internal const string Formal_ParamName_InClkEnableMode = "InClkEnableMode";
        internal const string Formal_ParamName_InvertInClock = "InvertInClock";
        internal const string Formal_ParamName_InvertInClockEn = "InvertInClockEn";
        internal const string Formal_ParamName_InvertInReset = "InvertInReset";
        internal const string Formal_ParamName_InvertOutClock = "InvertOutClock";
        internal const string Formal_ParamName_InvertOutClockEn = "InvertOutClockEn";
        internal const string Formal_ParamName_InvertOutReset = "InvertOutReset";
        internal const string Formal_ParamName_OEResetEnabled = "OEResetEnabled";
        internal const string Formal_ParamName_OutputResetEnabled = "OutputResetEnabled";
        internal const string Formal_ParamName_PaPin = "PaPin";
        internal const string Formal_ParamName_UsePaInClk = "UsePaInClk";
        internal const string Formal_ParamName_UsePaInClkEn = "UsePaInClkEn";
        internal const string Formal_ParamName_UsePaInRst = "UsePaInRst";
        internal const string Formal_ParamName_UsePaOutClk = "UsePaOutClk";
        internal const string Formal_ParamName_UsePaOutClkEn = "UsePaOutClkEn";
        internal const string Formal_ParamName_UsePaOutRst = "UsePaOutRst";
        internal const string Formal_ParamName_TermModeInterrupt = "TermMode_interrupt";
        internal const string Formal_ParamName_OutputMultiplier = "OutputMultipliers";
        internal const string Formal_ParamName_InputMultiplier = "InputMultipliers";

        #endregion

        public class PerPin
        {
            #region Member Variables
            private readonly GetPinSettingDelegate m_getPinSetting;
            private readonly SetPinSettingDelegate m_setPinSetting;
            private readonly ValidateSettingsDelegate m_validatePinSetting;
            private readonly CyDeviceSupport m_deviceSupport;
            private int m_index;
            #endregion

            #region Constructors
            public PerPin(GetPinSettingDelegate getPinSetting, ValidateSettingsDelegate validatePinSetting, CyDeviceSupport deviceSupport, int index)
                : this(getPinSetting, null, validatePinSetting, deviceSupport, index)
            {
            }

            public PerPin(GetPinSettingDelegate getPinSetting, SetPinSettingDelegate setPinSetting, ValidateSettingsDelegate validatePinSetting, CyDeviceSupport deviceSupport, int index)
            {
                m_getPinSetting = getPinSetting;
                m_setPinSetting = setPinSetting;
                m_validatePinSetting = validatePinSetting;
                m_deviceSupport = deviceSupport;
                m_index = index; // Don't use the setter - want to bypass PropogateNewIndex
            }
            #endregion

            internal void DriveModeChanged()
            {
                m_generalDriveMode = null;
            }

            internal void InputSyncChanged()
            {
                m_inputSyncMode = null;
            }

            internal void InitialDriveStateChanged()
            {
                m_generalInitialState = null;
            }

            internal void IsInHwChanged()
            {
                m_typeIsDigitalInputHw = null;
            }

            internal void IsOutHwChanged()
            {
                m_typeIsDigitalOutputHw = null;
            }

            #region Pins-Global
            public int Index
            {
                get { return m_index; }
                set 
                {
                    int oldIndex = m_index;
                    m_index = value;
                    PropogateNewIndex(oldIndex);
                }
            }

            public int SIOPairID
            {
                get
                {
                    // Deliberately not cached, as this can change if pins preceding us are
                    // grouped/ungrouped/changed between being an SIO or not
                    string grouped = m_getPinSetting(Formal_ParamName_SIOGroups, Index, Type);
                    if (grouped == SIOGroupValue_GROUPED)
                    {
                        // If there are an odd number of grouped SIOs preceding us, then we 
                        // are the second SIO in a pair. Otherwise, we're the first
                        int numPrecedingGrouped = 0;
                        for (int i = Index - 1; i >= 0; i--)
                        {
                            grouped = m_getPinSetting(Formal_ParamName_SIOGroups, i, Type);
                            if (grouped != SIOGroupValue_GROUPED)
                            {
                                break;
                            }
                            else
                                ++numPrecedingGrouped;
                        }
                        return (numPrecedingGrouped % 2);
                    }
                    else
                        return -1;
                }
                set
                {
                    string val = (value >= 0) ? SIOGroupValue_GROUPED : SIOGroupValue_NOT_GROUPED;
                    if (m_setPinSetting(Formal_ParamName_SIOGroups, val, Index))
                    {
                        m_validatePinSetting();
                    }
                }
            }

            private string m_alias = null;
            public string Alias
            {
                get
                {
                    if (null == m_alias)
                        m_alias = m_getPinSetting(Formal_ParamName_PinAlisases, Index, Type);
                    return m_alias;
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_PinAlisases, value, Index))
                    {
                        m_alias = value;
                        m_validatePinSetting();
                    }
                }
            }
            #endregion

            #region Pins-Type
            private CyPinType? m_type = null;
            public CyPinType Type
            {
                get
                {
                    if (null == m_type)
                        m_type = ConvertPinType(m_getPinSetting(Formal_ParamName_PinTypes, Index, CyPinType.OE));
                    return m_type.Value;
                }
                set
                {
                    //Set before saving to enable event trigger, ugly but less ugly then passing delegates
                    //throughout
                    CyPinType? oldType = m_type;
                    m_type = value;
                    if (!m_setPinSetting(Formal_ParamName_PinTypes, ConvertPinType(value), Index))
                    {
                        m_type = oldType;
                    }
                    m_validatePinSetting();
                }
            }

            private bool? m_typeIsDigitalInputHw = null;
            public bool TypeIsDigitalInputHw
            {
                get
                {
                    if (null == m_typeIsDigitalInputHw)
                        m_typeIsDigitalInputHw = (ParamValue_TRUE == m_getPinSetting(Formal_ParamName_DisplayInputHWConnections, Index, Type));
                    return m_typeIsDigitalInputHw.Value;
                }
                set
                {
                    string val = value ? ParamValue_TRUE : ParamValue_FALSE;
                    if (m_setPinSetting(Formal_ParamName_DisplayInputHWConnections, val, Index))
                    {
                        m_typeIsDigitalInputHw = value;
                        m_validatePinSetting();
                    }
                }
            }

            private bool? m_typeIsDigitalOutputHw = null;
            public bool TypeIsDigitalOutputHw
            {
                get
                {
                    if (null == m_typeIsDigitalOutputHw)
                        m_typeIsDigitalOutputHw = (ParamValue_TRUE == m_getPinSetting(Formal_ParamName_DisplayOutputHWConnections, Index, Type));
                    return m_typeIsDigitalOutputHw.Value;
                }
                set
                {
                    string val = value ? ParamValue_TRUE : ParamValue_FALSE;
                    if (m_setPinSetting(Formal_ParamName_DisplayOutputHWConnections, val, Index))
                    {
                        m_typeIsDigitalOutputHw = value;
                        m_validatePinSetting();
                    }
                }
            }

            private bool? m_typeShowExternalTerm = null;
            public bool TypeShowExternalTerm
            {
                get
                {
                    if (null == m_typeShowExternalTerm)
                        m_typeShowExternalTerm = (ParamValue_TRUE == m_getPinSetting(Formal_ParamName_ShowAnnotationTerm, Index, Type));
                    return m_typeShowExternalTerm.Value;
                }
                set
                {
                    string val = value ? ParamValue_TRUE : ParamValue_FALSE;
                    if (m_setPinSetting(Formal_ParamName_ShowAnnotationTerm, val, Index))
                    {
                        m_typeShowExternalTerm = value;
                        m_validatePinSetting();
                    }
                }
            }
            internal static CyPinType ConvertPinType(string pinType)
            {
                switch (pinType)
                {
                    case PinTypesValue_DIGIN:
                        return CyPinType.DIGITAL_IN;
                    case PinTypesValue_DIGOUT:
                        return CyPinType.DIGITAL_OUT;
                    case PinTypesValue_ANALOG:
                        return CyPinType.ANALOG;
                    case PinTypesValue_BIDIRECTIONAL:
                        return CyPinType.BIDIRECTIONAL;
                    case PinTypesValue_DIGIN_ANALOG:
                        return CyPinType.ANALOG | CyPinType.DIGITAL_IN;
                    case PinTypesValue_DIGOUT_DIGIN:
                        return CyPinType.DIGITAL_IN | CyPinType.DIGITAL_OUT;
                    case PinTypesValue_DIGOUT_OE:
                        return CyPinType.DIGITAL_OUT | CyPinType.OE;
                    case PinTypesValue_DIGOUT_DIGIN_OE:
                        return CyPinType.DIGITAL_IN | CyPinType.DIGITAL_OUT | CyPinType.OE;
                    case PinTypesValue_DIGOUT_ANALOG:
                        return CyPinType.ANALOG | CyPinType.DIGITAL_OUT;
                    case PinTypesValue_BIDIRECTIONAL_ANALOG:
                        return CyPinType.ANALOG | CyPinType.BIDIRECTIONAL;
                    case PinTypesValue_DIGOUT_DIGIN_ANALOG:
                        return CyPinType.ANALOG | CyPinType.DIGITAL_IN | CyPinType.DIGITAL_OUT;
                    case PinTypesValue_DIGOUT_OE_ANALOG:
                        return CyPinType.ANALOG | CyPinType.DIGITAL_OUT | CyPinType.OE;
                    case PinTypesValue_DIGOUT_OE_DIGIN_ANALOG:
                        return CyPinType.ANALOG | CyPinType.DIGITAL_IN | CyPinType.DIGITAL_OUT | CyPinType.OE;
                    case PinTypesValue_NONE:
                        return CyPinType.NONE;
                    default:
                        Debug.Fail("Unsupported pin type");
                        return CyPinType.DIGITAL_IN;
                }
            }

            private static string ConvertPinType(CyPinType pinType)
            {
                bool isAnalog = ((pinType & CyPinType.ANALOG) > 0);
                bool isBiDir = ((pinType & CyPinType.BIDIRECTIONAL) > 0);
                bool isDigIn = ((pinType & CyPinType.DIGITAL_IN) > 0);
                bool isDigOut = ((pinType & CyPinType.DIGITAL_OUT) > 0);
                bool isOe = ((pinType & CyPinType.OE) > 0);

                string val;
                if (isBiDir)
                    val = isAnalog ? PinTypesValue_BIDIRECTIONAL_ANALOG : PinTypesValue_BIDIRECTIONAL;
                else if (isDigIn)
                {
                    if (isDigOut)
                    {
                        if (isOe)
                            val = isAnalog ? PinTypesValue_DIGOUT_OE_DIGIN_ANALOG : PinTypesValue_DIGOUT_DIGIN_OE;
                        else
                            val = isAnalog ? PinTypesValue_DIGOUT_DIGIN_ANALOG : PinTypesValue_DIGOUT_DIGIN;
                    }
                    else
                        val = (isAnalog) ? PinTypesValue_DIGIN_ANALOG : PinTypesValue_DIGIN;
                }
                else if (isDigOut)
                {
                    if (isOe)
                        val = (isAnalog) ? PinTypesValue_DIGOUT_OE_ANALOG : PinTypesValue_DIGOUT_OE;
                    else
                        val = (isAnalog) ? PinTypesValue_DIGOUT_ANALOG : PinTypesValue_DIGOUT;
                }
                else if (isAnalog)
                    val = PinTypesValue_ANALOG;
                else
                {
                    val = PinTypesValue_NONE;
                }
                return val;
            }
            #endregion

            #region Pins-General
            internal int MultiplierIndex
            {
                get
                {
                    int multiplier = 0;
                    // Multiplier must match for input and output, so only check the output multiplier if we're bidirectional
                    if ((((Type & CyPinType.DIGITAL_OUT) != 0) || ((Type & CyPinType.BIDIRECTIONAL) != 0)) &&
                        OutputDriveLevel != CyOutputDriveLevel.VDDIO) // Only vref-based drive levels impact this setting
                    {
                        multiplier = Array.IndexOf(VrefMultiplierValues, OutputMultiplier);
                        Debug.Assert(multiplier >= 0, "Could not find multipler");
                    }
                    else if((Type & CyPinType.DIGITAL_IN) != 0)
                    {
                        // Multiplier is only set if input threshold is vref-based
                        switch (InputThreshold)
                        {
                            case CyInputThreshold.PT5_VREF:
                            case CyInputThreshold.PT5_VREF_INTERNAL:
                            case CyInputThreshold.VREF:
                            case CyInputThreshold.VREF_INTERNAL:
                                multiplier = Array.IndexOf(VrefMultiplierValues, InputMultiplier);
                                Debug.Assert(multiplier >= 0, "Could not find multipler");
                                break;
                            default:
                                multiplier = 0;
                                break;
                        }
                    }
                    return multiplier;
                }
            }

            internal CyVrefSource VRefSource
            {
                get
                {
                    CyVrefSource result = CyVrefSource.DONTCARE;
                    if ((Type & CyPinType.DIGITAL_IN) != 0 || (Type & CyPinType.BIDIRECTIONAL) != 0)
                    {
                        result = CyPinData.GetVrefSource(InputThreshold);
                    }
                    // This is required to match between input and output, so only check output if input was don't care
                    // Input could have used a non-vref threshold, so check bidirectional here as well
                    if (result == CyVrefSource.DONTCARE &&  
                        (((Type & CyPinType.DIGITAL_OUT) != 0) || (Type & CyPinType.BIDIRECTIONAL) != 0))
                    {
                        result = CyPinData.GetVrefSource(OutputDriveLevel);
                    }
                    return result;
                }
            }

            private CyDriveMode? m_generalDriveMode = null;
            public CyDriveMode GeneralDriveMode
            {
                get
                {
                    if (null == m_generalDriveMode)
                        m_generalDriveMode = ConvertDriveMode(m_getPinSetting(Formal_ParamName_DriveMode, Index, Type));
                    return m_generalDriveMode.Value;
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_DriveMode, ConvertDriveMode(value), Index))
                    {
                        m_generalDriveMode = value;
                        m_validatePinSetting();
                    }
                }
            }

            private bool? m_generalInitialState = null;
            public bool GeneralInitialState
            {
                get
                {
                    // If we're an output pin with a hw connection, initial state won't behave how the user expects
                    // it to, so always force it to high on PSoC 4 devices
                    if (m_deviceSupport.IsPSoC4 && 
                         ((((Type & CyPinType.DIGITAL_OUT) != 0) && TypeIsDigitalOutputHw) || 
                         (Type & CyPinType.OE) != 0))
                        return true; // Don't update the cache since this is just a temporary override
                    else if (null == m_generalInitialState)
                        m_generalInitialState = (InitialDriveStateValue_HIGH == m_getPinSetting(Formal_ParamName_InitialDriveStates, Index, Type));
                    return m_generalInitialState.Value;
                }
                set
                {
                    string val = value ? InitialDriveStateValue_HIGH : InitialDriveStateValue_LOW;
                    if (m_setPinSetting(Formal_ParamName_InitialDriveStates, val, Index))
                    {
                        m_generalInitialState = value;
                        m_validatePinSetting();
                    }
                }
            }

            private string m_generalMinimumSupply = null;
            public string GeneralMinimumSupply
            {
                get
                {
                    if (null == m_generalMinimumSupply)
                        m_generalMinimumSupply = m_getPinSetting(Formal_ParamName_IOVoltages, Index, Type);
                    return (m_generalMinimumSupply != DefaultIOVoltageValue) ? m_generalMinimumSupply : String.Empty;
                }
                set
                {
                    string newSupply = String.IsNullOrEmpty(value) ? DefaultIOVoltageValue : value;
                    if (m_setPinSetting(Formal_ParamName_IOVoltages, newSupply, Index))
                    {
                        m_generalMinimumSupply = newSupply;
                        m_validatePinSetting();
                    }
                }
            }

            private static CyDriveMode ConvertDriveMode(string driveMode)
            {
                switch (driveMode)
                {
                    case DriveModeValue_CMOS_OUT:
                        return CyDriveMode.STRONG_DRIVE;
                    case DriveModeValue_OPEN_DRAIN_LO:
                        return CyDriveMode.OPEN_DRAIN_DRIVE_LOW;
                    case DriveModeValue_OPEN_DRAIN_HI:
                        return CyDriveMode.OPEN_DRAIN_DRIVE_HIGH;
                    case DriveModeValue_RES_PULL_UP:
                        return CyDriveMode.RESISTIVE_PULL_UP;
                    case DriveModeValue_RES_PULL_DOWN:
                        return CyDriveMode.RESISTIVE_PULL_DOWN;
                    case DriveModeValue_RES_PULL_UP_DOWN:
                        return CyDriveMode.RESISTIVE_PULL_UP_DOWN;
                    case DriveModeValue_ANALOG_HI_Z:
                        return CyDriveMode.HIGH_IMPEDANCE_ANALOG;
                    case DriveModeValue_DIGITAL_HI_Z:
                        return CyDriveMode.HIGH_IMPEDANCE_DIGITAL;
                    default:
                        Debug.Fail("Unhandled drive mode: " + driveMode);
                        return CyDriveMode.STRONG_DRIVE;
                }
            }

            internal static string ConvertDriveMode(CyDriveMode driveMode)
            {
                switch (driveMode)
                {
                    case CyDriveMode.STRONG_DRIVE:
                        return DriveModeValue_CMOS_OUT;
                    case CyDriveMode.OPEN_DRAIN_DRIVE_LOW:
                        return DriveModeValue_OPEN_DRAIN_LO;
                    case CyDriveMode.OPEN_DRAIN_DRIVE_HIGH:
                        return DriveModeValue_OPEN_DRAIN_HI;
                    case CyDriveMode.RESISTIVE_PULL_UP:
                        return DriveModeValue_RES_PULL_UP;
                    case CyDriveMode.RESISTIVE_PULL_DOWN:
                        return DriveModeValue_RES_PULL_DOWN;
                    case CyDriveMode.RESISTIVE_PULL_UP_DOWN:
                        return DriveModeValue_RES_PULL_UP_DOWN;
                    case CyDriveMode.HIGH_IMPEDANCE_ANALOG:
                        return DriveModeValue_ANALOG_HI_Z;
                    case CyDriveMode.HIGH_IMPEDANCE_DIGITAL:
                        return DriveModeValue_DIGITAL_HI_Z;
                    default:
                        Debug.Fail("unhandled drive mode: " + driveMode);
                        return DefaultDriveModeValue;
                }
            }
            #endregion

            #region Pins-Input
            private CyInputThreshold? m_inputThreshold = null;
            public CyInputThreshold InputThreshold
            {
                get
                {
                    return GetSharedSIOSetting(Formal_ParamName_ThresholdLevels, CyInputThreshold.CMOS_LVTTL,
                        GetInputThreshold, ref m_inputThreshold, CyPinType.DIGITAL_IN, CyPinType.BIDIRECTIONAL);
                }
                set
                {
                    if (SetInputThreshold(value, InputHysteresis))
                    {
                        m_inputThreshold = value;
                        // The choice of threshold can impact the multiplier, so clear that as well
                        m_inputMultiplier = null;
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_validatePinSetting();
                    }
                }
            }

            private double? m_inputMultiplier = null;
            public double InputMultiplier
            {
                get
                {
                    switch (InputThreshold)
                    {
                        case CyInputThreshold.VDDIO:
                            return GetVddioMultiplierFromThreshold();
                        case CyInputThreshold.PT5_VREF:
                        case CyInputThreshold.PT5_VREF_INTERNAL:
                        case CyInputThreshold.VREF:
                        case CyInputThreshold.VREF_INTERNAL:
                            return GetSharedSIOSetting(Formal_ParamName_InputMultiplier, VrefMultiplierValues[DefaultMultiplierIdx],
                                ConvertVrefMultiplier, ref m_inputMultiplier, CyPinType.DIGITAL_IN, CyPinType.BIDIRECTIONAL);
                        default:
                            return DefaultMultiplier;
                    }
                }
                set
                {
                    string valStr;
                    string paramName;
                    switch (InputThreshold)
                    {
                        // Multiplier value is embedded in threshold selection
                        case CyInputThreshold.VDDIO:
                            valStr = ConvertInputThreshold(InputThreshold, value, InputHysteresis);
                            paramName = Formal_ParamName_ThresholdLevels;
                            break;
                        case CyInputThreshold.PT5_VREF:
                        case CyInputThreshold.PT5_VREF_INTERNAL:
                        case CyInputThreshold.VREF:
                        case CyInputThreshold.VREF_INTERNAL:
                            valStr = ConvertMultiplier(VrefMultiplierValues, value);
                            paramName = Formal_ParamName_InputMultiplier;
                            break;
                        default:
                            // Other modes are always at 1
                            Debug.Assert(value == 1, "Multiplier " + value + " is not valid for this threshold");
                            valStr = DefaultMultiplierIdx.ToString();
                            paramName = Formal_ParamName_InputMultiplier;
                            break;
                    }

                    if (m_setPinSetting(paramName, valStr, Index))
                    {
                        m_inputMultiplier = value;
                        m_validatePinSetting();
                    }

                }
            }

            private bool? m_inputHysteresis = null;
            public bool InputHysteresis
            {
                get
                {
                    if (null == m_inputHysteresis)
                    {
                        if ((Type & (CyPinType.DIGITAL_IN | CyPinType.BIDIRECTIONAL)) > 0)
                            m_inputHysteresis = GetInputHysteresis();
                        else // Hysteresis has no meaning for non-input; return default to not limit placement
                            return true;
                    }
                    return m_inputHysteresis.Value;
                }
                set
                {
                    if (SetInputHysteresis(InputThreshold, value))
                    {
                        m_inputHysteresis = value;
                        m_validatePinSetting();
                    }
                }
            }

            private CyInputInterruptTrigger? m_inputInterrupt = null;
            public CyInputInterruptTrigger InputInterrupt
            {
                get
                {
                    if (null == m_inputInterrupt)
                        m_inputInterrupt = ConvertInputInterrupt(m_getPinSetting(Formal_ParamName_InterruptMode, Index, Type));

                    // Ignore leftover interrupt settings if the pin is no longer an input
                    if (((Type & CyPinType.DIGITAL_IN) != 0) || ((Type & CyPinType.BIDIRECTIONAL) != 0))
                        return m_inputInterrupt.Value;
                    else
                        return CyInputInterruptTrigger.NONE;
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_InterruptMode, ConvertInputInterrupt(value), Index))
                    {
                        m_inputInterrupt = value;
                        m_validatePinSetting();
                    }
                }
            }

            private bool? m_dedicatedInterrupt = null;
            public bool DedicatedInterrupt
            {
                get
                {
                    if (!m_deviceSupport.HasAllPortsInterrupt)
                        return true; // All interrupts are dedicated by definition
                    if (null == m_dedicatedInterrupt)
                    {
                        string paramVal = m_getPinSetting(Formal_ParamName_DedicatedInterrupt, Index, Type);
                        if(paramVal == ParamValue_ENABLED)
                            m_dedicatedInterrupt = true;
                        else if(paramVal == ParamValue_DISABLED)
                            m_dedicatedInterrupt = false;
                        else
                        {
                            m_dedicatedInterrupt = false;
                            Debug.Fail("Unknown dedicated interrupt value " + paramVal);
                        }
                    }
                    return m_dedicatedInterrupt.Value;
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_DedicatedInterrupt, value ? ParamValue_ENABLED : ParamValue_DISABLED, Index))
                    {
                        m_dedicatedInterrupt = value;
                        m_validatePinSetting();
                    }
                }
            }

            private bool? m_generalHotSwap = null;
            public bool GeneralHotSwap
            {
                get
                {
                    CyPinType type = Type;
                    if (null == m_generalHotSwap)
                        m_generalHotSwap = (ParamValue_TRUE == m_getPinSetting(Formal_ParamName_HotSwaps, Index, type));
                    // If pure analog and no OVT on the part, hotswap is false (and the checkbox is disabled)
                    // If there is a mix of analog and digital on this pin, the user will get an error if they try
                    // to use HotSwap, so we check type against analog directly
                    if (type == CyPinType.ANALOG && !m_deviceSupport.HasOVT)
                        return false;
                    return m_generalHotSwap.Value;
                }
                set
                {
                    string val = value ? ParamValue_TRUE : ParamValue_FALSE;
                    if (m_setPinSetting(Formal_ParamName_HotSwaps, val, Index))
                    {
                        m_generalHotSwap = value;
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_validatePinSetting();
                    }
                }
            }

            private bool? m_inputBufferEnabled = null;
            public bool InputBufferEnabled
            {
                get
                {
                    if (null == m_inputBufferEnabled)
                        m_inputBufferEnabled = (ParamValue_TRUE == m_getPinSetting(Formal_ParamName_InputBuffersEnabled, Index, Type));
                    return m_inputBufferEnabled.Value;
                }
                set
                {
                    string val = value ? ParamValue_TRUE : ParamValue_FALSE;
                    if (m_setPinSetting(Formal_ParamName_InputBuffersEnabled, val, Index))
                    {
                        m_inputBufferEnabled = value;
                        m_validatePinSetting();
                    }
                }
            }

            private CyInputSyncMode? m_inputSyncMode = null;
            public CyInputSyncMode InputSyncMode
            {
                get
                {
                    if (null == m_inputSyncMode)
                    {
                        string sync = m_getPinSetting(Formal_ParamName_InputsSynchronized, Index, Type);
                        string mode = m_getPinSetting(Formal_ParamName_InputsSyncMode, Index, Type);

                        if (ParamValue_DISABLED == sync)
                            m_inputSyncMode = CyInputSyncMode.TRANSPARENT;
                        else
                        {
                            m_inputSyncMode = (InputsSyncModeValue_DOUBLE == mode)
                                ? CyInputSyncMode.DOUBLE_SYNC
                                : CyInputSyncMode.SINGLE_SYNC;
                        }
                    }
                    return m_inputSyncMode.Value;
                }
                set
                {
                    string sync = (CyInputSyncMode.TRANSPARENT == value)
                        ? ParamValue_DISABLED
                        : ParamValue_ENABLED;
                    string mode = (CyInputSyncMode.SINGLE_SYNC == value)
                        ? InputsSyncModeValue_SINGLE
                        : InputsSyncModeValue_DOUBLE;

                    if (m_setPinSetting(Formal_ParamName_InputsSynchronized, sync, Index) &&
                        m_setPinSetting(Formal_ParamName_InputsSyncMode, mode, Index))
                    {
                        m_inputSyncMode = value;
                        m_validatePinSetting();
                    }
                }
            }

            private CyInputThreshold GetInputThreshold(string threshold)
            {
                Touple<CyInputThreshold, bool> vals = ConvertInputThreshold(threshold);
                m_inputThreshold = vals.First;
                m_inputHysteresis = vals.Second;
                return m_inputThreshold.Value;
            }

            private bool SetInputThreshold(CyInputThreshold threshold, bool hysteresis)
            {
                string value = ConvertInputThreshold(threshold, InputMultiplier, hysteresis);
                return m_setPinSetting(Formal_ParamName_ThresholdLevels, value, Index);
            }

            private static Touple<CyInputThreshold, bool> ConvertInputThreshold(string threshold)
            {
                switch (threshold)
                {
                    case ThresholdLevelValue_CMOS:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.CMOS, true);
                    case ThresholdLevelValue_CMOS_LVTTL:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.CMOS_LVTTL, true);
                    case ThresholdLevelValue_LVTTL:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.LVTTL, true);
                    case ThresholdLevelValue_PT4_VDDIO_HYST:
                    case ThresholdLevelValue_PT5_VDDIO_HYST:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.VDDIO, true);
                    case ThresholdLevelValue_PT4_VDDIO:
                    case ThresholdLevelValue_PT5_VDDIO:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.VDDIO, false);
                    case ThresholdLevelValue_PT5_VREF_HYST:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.PT5_VREF, true);
                    case ThresholdLevelValue_PT5_VREF:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.PT5_VREF, false);
                    case ThresholdLevelValue_VREF_HYST:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.VREF, true);
                    case ThresholdLevelValue_VREF:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.VREF, false);
                    case ThresholdLevelValue_CMOS_1PT8V:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.CMOS_1PT8V, true);
                    case ThresholdLevelValue_VREF_INTERNAL:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.VREF_INTERNAL, false);
                    case ThresholdLevelValue_VREF_INTERNAL_HYST:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.VREF_INTERNAL, true);
                    case ThresholdLevelValue_PT5_VREF_INTERNAL:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.PT5_VREF_INTERNAL, false);
                    case ThresholdLevelValue_PT5_VREF_INTERNAL_HYST:
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.PT5_VREF_INTERNAL, true);
                    default:
                        Debug.Fail("Unhandled input threshold");
                        return new Touple<CyInputThreshold, bool>(CyInputThreshold.CMOS, true);
                }
            }
            private static string ConvertInputThreshold(CyInputThreshold threshold, double multiplier, bool hysteresis)
            {
                switch (threshold)
                {
                    case CyInputThreshold.CMOS:
                        return ThresholdLevelValue_CMOS;
                    case CyInputThreshold.CMOS_LVTTL:
                        return ThresholdLevelValue_CMOS_LVTTL;
                    case CyInputThreshold.LVTTL:
                        return ThresholdLevelValue_LVTTL;
                    case CyInputThreshold.VDDIO:
                        switch(ConvertMultiplier(VddioMultiplierValues, multiplier))
                        {
                            case "0": // 0.4x
                                return hysteresis
                                    ? ThresholdLevelValue_PT4_VDDIO_HYST
                                    : ThresholdLevelValue_PT4_VDDIO;
                            case "1": // 0.5x
                                return hysteresis
                                    ? ThresholdLevelValue_PT5_VDDIO_HYST
                                    : ThresholdLevelValue_PT5_VDDIO;
                            default:
                                Debug.Fail("Unknown index");
                                return ThresholdLevelValue_PT4_VDDIO;
                        }
                   case CyInputThreshold.PT5_VREF:
                        return hysteresis
                            ? ThresholdLevelValue_PT5_VREF_HYST
                            : ThresholdLevelValue_PT5_VREF;
                    case CyInputThreshold.VREF:
                        return hysteresis
                            ? ThresholdLevelValue_VREF_HYST
                            : ThresholdLevelValue_VREF;
                    case CyInputThreshold.PT5_VREF_INTERNAL:
                        return hysteresis
                            ? ThresholdLevelValue_PT5_VREF_INTERNAL_HYST
                            : ThresholdLevelValue_PT5_VREF_INTERNAL;
                    case CyInputThreshold.VREF_INTERNAL:
                        return hysteresis
                            ? ThresholdLevelValue_VREF_INTERNAL_HYST
                            : ThresholdLevelValue_VREF_INTERNAL;
                    case CyInputThreshold.CMOS_1PT8V:
                        return ThresholdLevelValue_CMOS_1PT8V;
                    default:
                        Debug.Fail("unhandled threshold: " + threshold);
                        return DefaultThresholdLevelValue;
                }
            }

            private bool GetInputHysteresis()
            {
                string threshold = m_getPinSetting(Formal_ParamName_ThresholdLevels, Index, Type);
                Touple<CyInputThreshold, bool> vals = ConvertInputThreshold(threshold);
                return vals.Second;
            }

            private bool SetInputHysteresis(CyInputThreshold threshold, bool hysteresis)
            {
                string thresholdValue = ConvertInputThreshold(threshold, InputMultiplier, hysteresis);
                return m_setPinSetting(Formal_ParamName_ThresholdLevels, thresholdValue, Index);
            }

            internal static string ConvertInputInterrupt(CyInputInterruptTrigger inputInterrupt)
            {
                switch (inputInterrupt)
                {
                    case CyInputInterruptTrigger.NONE:
                        return InterruptModeValue_NONE;
                    case CyInputInterruptTrigger.FALLING_EDGE:
                        return InterruptModeValue_FALLING_EDGE;
                    case CyInputInterruptTrigger.RISING_EDGE:
                        return InterruptModeValue_RISING_EDGE;
                    case CyInputInterruptTrigger.BOTH_EDGES:
                        return InterruptModeValue_ON_CHANGE;
                    default:
                        Debug.Fail("unhandled input interrupt: " + inputInterrupt);
                        return DefaultInterruptModeValue;
                }
            }
            private static CyInputInterruptTrigger ConvertInputInterrupt(string inputInterrupt)
            {
                switch (inputInterrupt)
                {
                    case InterruptModeValue_NONE:
                        return CyInputInterruptTrigger.NONE;
                    case InterruptModeValue_FALLING_EDGE:
                        return CyInputInterruptTrigger.FALLING_EDGE;
                    case InterruptModeValue_RISING_EDGE:
                        return CyInputInterruptTrigger.RISING_EDGE;
                    case InterruptModeValue_ON_CHANGE:
                        return CyInputInterruptTrigger.BOTH_EDGES;
                    default:
                        Debug.Fail("Unhandled input threshold");
                        return CyInputInterruptTrigger.NONE;
                }
            }
            #endregion

            #region Pins-Output
            private CyOutputSlewRate? m_outputSlewRate = null;
            public CyOutputSlewRate OutputSlewRate
            {
                get
                {
                    if (null == m_outputSlewRate)
                        m_outputSlewRate = ConvertSlewRate(m_getPinSetting(Formal_ParamName_SlewRate, Index, Type));
                    return m_outputSlewRate.Value;
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_SlewRate, ConvertSlewRate(value), Index))
                    {
                        m_outputSlewRate = value;
                        m_validatePinSetting();
                    }
                }
            }

            private CyOutputDriveLevel? m_outputDriveLevel = null;
            public CyOutputDriveLevel OutputDriveLevel
            {
                get
                {
                    return GetSharedSIOSetting(Formal_ParamName_OutputDriveLevels, CyOutputDriveLevel.VDDIO,
                        ConvertOutputDriveLevel, ref m_outputDriveLevel, CyPinType.DIGITAL_OUT, CyPinType.BIDIRECTIONAL);
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_OutputDriveLevels, ConvertOutputDriveLevel(value), Index))
                    {
                        m_outputDriveLevel = value;
                        m_outputMultiplier = null; // Drive level impacts the valid multipliers
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_validatePinSetting();
                    }
                }
            }

            private double? m_outputMultiplier = null;
            public double OutputMultiplier
            {
                get
                {
                    if (OutputDriveLevel == CyOutputDriveLevel.VDDIO)
                        return DefaultMultiplier; // VDDIO output only supports 1x
                    else
                        return GetSharedSIOSetting(Formal_ParamName_OutputMultiplier, VrefMultiplierValues[DefaultMultiplierIdx],
                            ConvertVrefMultiplier, ref m_outputMultiplier, CyPinType.DIGITAL_OUT, CyPinType.BIDIRECTIONAL);
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_OutputMultiplier, ConvertMultiplier(VrefMultiplierValues, value), Index))
                    {
                        m_outputMultiplier = value;
                        m_validatePinSetting();
                    }
                }
            }

            /// <summary>
            /// Gets the value for a setting which is shared between paired SIOs, but which is only valid for a 
            /// particular pin type
            /// </summary>
            /// <typeparam name="T">Type of the setting to be retrieved</typeparam>
            /// <param name="paramName">Formal parameter for the setting</param>
            /// <param name="convertValue">Delegate to convert a string into the desired value</param>
            /// <param name="cacheVar">Member variable which caches the value for this setting</param>
            /// <param name="applicableTypes">Pin types to which the setting applies</param>
            /// <returns>The value for the desired type</returns>
            private T GetSharedSIOSetting<T>(string paramName, T defaultVal, CyFunc<string, T> convertValue,
                ref T? cacheVar, params CyPinType[] applicableTypes) where T : struct
            {
                if (null == cacheVar)
                {
                    cacheVar = convertValue(m_getPinSetting(paramName, Index, Type));
                }
                // If we're an output, return the value directly. Otherwise, choose a default if we are not an SIO.
                // If we are an SIO, check the other item in our pair to see if it has a more meaningful value
                foreach (CyPinType pinType in applicableTypes)
                {
                    if ((Type & pinType) > 0)
                    {
                        // SIO pairs must have the same value for this, so we dont' need to look at the other pin
                        return cacheVar.Value;
                    }
                }
                if (SIOPairID >= 0) // SIO and paired - check the other half
                {
                    string otherPinTypeStr = m_getPinSetting(Formal_ParamName_PinTypes, GetOtherSIOIndex(this),
                                                CyPinType.DIGITAL_OUT /* not used when getting type */);
                    CyPinType otherType = ConvertPinType(otherPinTypeStr);
                    foreach (CyPinType pinType in applicableTypes)
                    {
                        if ((otherType & pinType) > 0)
                        {
                            return convertValue(m_getPinSetting(paramName, GetOtherSIOIndex(this), otherType));
                        }
                    }
                }

                return defaultVal;
            }

            private double TryParseDouble(string val)
            {
                double result;
                bool success = double.TryParse(val, out result);
                Debug.Assert(success);
                return result;
            }

            private CyOutputCurrent? m_outputCurrent = null;
            public CyOutputCurrent OutputCurrent
            {
                get
                {
                    CyPinType type = Type;
                    if (null == m_outputCurrent)
                        m_outputCurrent = ConvertOutputCurrent(m_getPinSetting(Formal_ParamName_DriveCurrents, Index, type));
                    return ((type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_OUT)) > 0)
                        ? m_outputCurrent.Value
                        : CyOutputCurrent.SOURCE_4MA_SINK_8MA;
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_DriveCurrents, ConvertOutputCurrent(value), Index))
                    {
                        m_outputCurrent = value;
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_validatePinSetting();
                    }
                }
            }

            private CyOutputMode? m_outputMode = null;
            public CyOutputMode OutputMode
            {
                get
                {
                    CyPinType type = Type;
                    if (null == m_outputMode)
                    {
                        string sync = m_getPinSetting(Formal_ParamName_OutputsSynchronized, Index, type);
                        string mode = m_getPinSetting(Formal_ParamName_OutputModes, Index, type);
                        string clk = m_getPinSetting(Formal_ParamName_OutputClockModes, Index, type);

                        if (ParamValue_DISABLED == sync)
                            m_outputMode = CyOutputMode.TRANSPARENT;
                        else if (OutputModesValue_CLOCK == mode)
                        {
                            m_outputMode = (OutputClockModesValue_NORMAL == clk)
                                ? CyOutputMode.CLOCK
                                : CyOutputMode.CLOCK_INV;
                        }
                        else
                            m_outputMode = CyOutputMode.SINGLE_SYNC;
                    }
                    return ((type & (CyPinType.DIGITAL_OUT | CyPinType.BIDIRECTIONAL)) > 0)
                        ? m_outputMode.Value
                        : CyOutputMode.TRANSPARENT;
                }
                set
                {
                    string sync = (CyOutputMode.TRANSPARENT == value) ? ParamValue_DISABLED : ParamValue_ENABLED;
                    string mode = (CyOutputMode.TRANSPARENT == value || CyOutputMode.SINGLE_SYNC == value)
                        ? OutputModesValue_DATA
                        : OutputModesValue_CLOCK;
                    string clk = (CyOutputMode.CLOCK_INV == value)
                        ? OutputClockModesValue_INVERTED
                        : OutputClockModesValue_NORMAL;

                    if (m_setPinSetting(Formal_ParamName_OutputsSynchronized, sync, Index) &&
                        m_setPinSetting(Formal_ParamName_OutputModes, mode, Index) &&
                        m_setPinSetting(Formal_ParamName_OutputClockModes, clk, Index))
                    {
                        m_outputMode = value;
                        m_validatePinSetting();
                    }
                }
            }

            private bool? m_outputEnableSynchronized = null;
            public bool OutputEnableSynchronized
            {
                get
                {
                    if (null == m_outputEnableSynchronized)
                        m_outputEnableSynchronized = (m_getPinSetting(Formal_ParamName_OESyncs, Index, Type) == ParamValue_TRUE);
                    return m_outputEnableSynchronized.Value;
                }
                set
                {
                    if (m_setPinSetting(Formal_ParamName_OESyncs, value ? ParamValue_TRUE : ParamValue_FALSE, Index))
                    {
                        m_outputEnableSynchronized = value;
                        m_validatePinSetting();
                    }
                }
            }

            private static CyOutputSlewRate ConvertSlewRate(string slewRate)
            {
                switch (slewRate)
                {
                    case SlewRateValue_FAST:
                        return CyOutputSlewRate.FAST;
                    case SlewRateValue_SLOW:
                        return CyOutputSlewRate.SLOW;
                    case SlewRateValue_I2C_FM:
                        return CyOutputSlewRate.I2CFM;
                    case SlewRateValue_I2C_HS_FAST:
                        return CyOutputSlewRate.I2CHS_FAST;
                    case SlewRateValue_I2C_HS_SLOW:
                        return CyOutputSlewRate.I2CHS_SLOW;
                    default:
                        Debug.Fail("Unhandled slew rate: " + slewRate);
                        return CyOutputSlewRate.FAST;
                }
            }
            internal static string ConvertSlewRate(CyOutputSlewRate slewRate)
            {
                switch (slewRate)
                {
                    case CyOutputSlewRate.FAST:
                        return SlewRateValue_FAST;
                    case CyOutputSlewRate.SLOW:
                        return SlewRateValue_SLOW;
                    case CyOutputSlewRate.I2CFM:
                        return SlewRateValue_I2C_FM;
                    case CyOutputSlewRate.I2CHS_SLOW:
                        return SlewRateValue_I2C_HS_SLOW;
                    case CyOutputSlewRate.I2CHS_FAST:
                        return SlewRateValue_I2C_HS_FAST;
                    default:
                        Debug.Fail("unhandled output slew rate: " + slewRate);
                        return DefaultSlewRateValue;
                }
            }

            private static CyOutputDriveLevel ConvertOutputDriveLevel(string driveLevel)
            {
                switch (driveLevel)
                {
                    case OutputDriveLevelValue_VDDIO:
                        return CyOutputDriveLevel.VDDIO;
                    case OutputDriveLevelValue_VREF:
                        return CyOutputDriveLevel.VREF;
                    case OutputDriveLevelValue_VREF_INTERNAL:
                        return CyOutputDriveLevel.VREF_INTERNAL;
                    default:
                        Debug.Fail("Unhandled output drive level: " + driveLevel);
                        return CyOutputDriveLevel.VDDIO;
                }
            }

            private double GetVddioMultiplierFromThreshold()
            {
                switch(m_getPinSetting(Formal_ParamName_ThresholdLevels, Index, Type))
                {
                    case ThresholdLevelValue_PT4_VDDIO:
                    case ThresholdLevelValue_PT4_VDDIO_HYST:
                        return VddioMultiplierValues[0]; // 0.4
                    case ThresholdLevelValue_PT5_VDDIO:
                    case ThresholdLevelValue_PT5_VDDIO_HYST:
                        return VddioMultiplierValues[1]; // 0.5
                    default:
                        Debug.Fail("Only valid to call this when threshold is vddio-based");
                        return 1;
                }
            }

            // Convenience wrapper, because the C# compiler we use for customizers doesn't support anonymous delegates
            private static double ConvertVrefMultiplier(string val)
            {
                return ConvertMultiplier(VrefMultiplierValues, val);
            }

            private static double ConvertMultiplier(double[] values, string val)
            {
                int idx;
                if (int.TryParse(val, out idx))
                    return values[idx];
                else
                    return values[DefaultMultiplierIdx];
            }

            private static string ConvertMultiplier(double[] values, double val)
            {
                int index = Array.IndexOf(values, val);
                if (index < 0) index = DefaultMultiplierIdx;
                return index.ToString();
            }

            internal static string ConvertOutputDriveLevel(CyOutputDriveLevel driveLevel)
            {
                switch (driveLevel)
                {
                    case CyOutputDriveLevel.VDDIO:
                        return OutputDriveLevelValue_VDDIO;
                    case CyOutputDriveLevel.VREF:
                        return OutputDriveLevelValue_VREF; 
                    case CyOutputDriveLevel.VREF_INTERNAL:
                        return OutputDriveLevelValue_VREF_INTERNAL;
                    default:
                        Debug.Fail("unhandled output drive level: " + driveLevel);
                        return DefaultOutputDriveLevelValue;
                }
            }

            private static CyOutputCurrent ConvertOutputCurrent(string outputCurrent)
            {
                switch (outputCurrent)
                {
                    case DriveCurrentValue_4SOURCE_25SINK:
                        return CyOutputCurrent.SOURCE_4MA_SINK_25MA;
                    case DriveCurrentValue_4SOURCE_8SINK:
                        return CyOutputCurrent.SOURCE_4MA_SINK_8MA;
                    case DriveCurrentValue_4SOURCE_10SINK:
                        return CyOutputCurrent.SOURCE_4MA_SINK_10MA;
                    default:
                        Debug.Fail("Unhandled output current: " + outputCurrent);
                        return CyOutputCurrent.SOURCE_4MA_SINK_8MA;
                }
            }
            private static string ConvertOutputCurrent(CyOutputCurrent outputCurrent)
            {
                switch (outputCurrent)
                {
                    case CyOutputCurrent.SOURCE_4MA_SINK_25MA:
                        return DriveCurrentValue_4SOURCE_25SINK;
                    case CyOutputCurrent.SOURCE_4MA_SINK_8MA:
                        return DriveCurrentValue_4SOURCE_8SINK;
                    case CyOutputCurrent.SOURCE_4MA_SINK_10MA:
                        return DriveCurrentValue_4SOURCE_10SINK;
                    default:
                        Debug.Fail("unhandled output current: " + outputCurrent);
                        return String.Empty;
                }
            }
            #endregion

            #region Functions

            #region SIO
            /// <summary>
            /// Is this pin the first SIO in a pair, or a lone unpaired SIO
            /// </summary>
            /// <returns>
            /// True if one of the following is true:
            /// * We are an unpaired SIO
            /// * We are a the first SIO in a pair
            /// False otherwise.
            /// </returns>
            public bool IsFirstSIO()
            {
                return RequiresSIO() && SIOPairID < 1; // Either first in pair, or not paired (PairID == -1)
            }

            public bool RequiresSIO()
            {
                return GetSIOCauses().Count > 0;
            }
            
            /// <summary>
            /// Determines whether this pin requires SIO, and if so for which reasons
            /// </summary>
            /// <param name="cause">
            /// A list of touples indicating all settings which required that this pin must be an SIO. 
            /// Fields are as follows:
            /// * First: FormalParam where the setting is stored
            /// * Second: ErrorMgr Key for the setting
            /// * Third: "User-Friendly" name for the setting
            /// </param>
            /// <returns>True if this pin requires SIO, false otherwise (including if it can be SIO or OVT)</returns>
            public List<CyErrorCause> GetSIOCauses()
            {
                /* 
                 * A pin is SIO if any one of the following is true:
                 * 1. HotSwaps(index) is used and we don't have OVT
                 * 2. ThresholdLevels(index) is one of the following (i.e. not CMOS or LVTTL):
                 *    0.5 * Vddio
                 *    0.4 * Vddio
                 *    0.5 * Vref
                 *    Vref
                 *    0.5 * Vddio with hysteresis
                 *    0.4 * Vddio with hysteresis
                 *    0.5 * Vref with hysteresis
                 *    Vref with hysteresis
                 * 3. OutputDriveLevels(index) is Vref
                 * 4. DriveCurrents(index) is 4mA source, 25mA sink
                 * 
                 */

                List<CyErrorCause> cause = new List<CyErrorCause>();
                if (HotswapRequiresSio())
                    cause.Add(new CyErrorCause(Formal_ParamName_HotSwaps, ErrorMgrKey.INPUT_HOT_SWAP, "Hot Swap"));
                if (RequiresSio(InputThreshold))
                    cause.Add(new CyErrorCause(Formal_ParamName_ThresholdLevels, ErrorMgrKey.INPUT_THRESHOLD, "Input Threshold"));
                if (RequiresSio(OutputDriveLevel))
                    cause.Add(new CyErrorCause(Formal_ParamName_OutputDriveLevels, ErrorMgrKey.OUTPUT_DRIVE_LEVEL, "Output Drive Level"));
                if (RequiresSio(OutputCurrent))
                    cause.Add(new CyErrorCause(Formal_ParamName_DriveCurrents, ErrorMgrKey.OUTPUT_CURRENT, "Output Current"));

                return cause;
            }

            private bool HotswapRequiresSio()
            {
                // Hotswap only requires SIO if we don't have OVT. To avoid duplicate errors, if we have neither
                // OVT nor SIO, consider HotSwap to require OVT since it is expected to be on more chips in the future,
                // and considering it to require both will generate redundant "missing feature" errors
                return GeneralHotSwap && !m_deviceSupport.HasOVT && m_deviceSupport.HasSIO;
            }

            public static bool RequiresSio(CyInputThreshold threshold)
            {
                return (threshold != CyInputThreshold.CMOS &&
                        threshold != CyInputThreshold.LVTTL &&
                        threshold != CyInputThreshold.CMOS_LVTTL &&
                        threshold != CyInputThreshold.CMOS_1PT8V);
            }

            public static bool RequiresSio(CyOutputDriveLevel driveLevel)
            {
                return (driveLevel == CyOutputDriveLevel.VREF || driveLevel == CyOutputDriveLevel.VREF_INTERNAL);
            }

            public bool RequiresSio(CyOutputCurrent outputCurrent)
            {
                // 10MA only requires SIO if we don't have OVT, so we handle this similarly to hotswap
                return (outputCurrent == CyOutputCurrent.SOURCE_4MA_SINK_25MA) ||
                       (outputCurrent == CyOutputCurrent.SOURCE_4MA_SINK_10MA && !m_deviceSupport.HasOVT && m_deviceSupport.HasSIO);
            }

            public static int GetOtherSIOIndex(PerPin pin)
            {
                Debug.Assert(pin.SIOPairID >= 0, "SIO Not Paired");
                int otherIdx = (pin.SIOPairID == 0) ? pin.Index + 1 : pin.Index - 1;
                return otherIdx;
            }


            #endregion

            #region OVT

            /// <summary>
            /// Determines whether this pin requires OVT, and if so for which reasons
            /// </summary>
            /// <param name="cause">
            /// A list of touples indicating all settings which required that this pin must be an SIO. 
            /// Fields are as follows:
            /// * First: FormalParam where the setting is stored
            /// * Second: ErrorMgr Key for the setting
            /// * Third: "User-Friendly" name for the setting
            /// </param>
            /// <returns>True if this pin requires OVT, false otherwise (including if it can be either SIO or OVT)</returns>
            public List<CyErrorCause> GetOVTCauses()
            {
                /* 
                 * A pin is OVT if any one of the following is true:
                 * 1. HotSwaps(index) is used and we don't have SIO
                 * 2. ThresholdLevels(index) is one of the following (i.e. not CMOS or LVTTL):
                 *    CMOS 1.8 V
                 * 3. Either of the I2C Slew rates is used
                 */

                List<CyErrorCause> cause = new List<CyErrorCause>();
                if (HotswapRequiresOvt())
                    cause.Add(new CyErrorCause(Formal_ParamName_HotSwaps, ErrorMgrKey.INPUT_HOT_SWAP, "Hot Swap"));
                if (RequiresOvt(OutputSlewRate))
                    cause.Add(new CyErrorCause(Formal_ParamName_SlewRate, ErrorMgrKey.OUTPUT_SLEW_RATE, "Slew Rate"));
                if (RequiresOvt(OutputCurrent))
                    cause.Add(new CyErrorCause(Formal_ParamName_DriveCurrents, ErrorMgrKey.OUTPUT_CURRENT, "Output Current"));

                return cause;
            }

            public bool RequiresOVT()
            {
                return GetOVTCauses().Count > 0;
            }

            private bool HotswapRequiresOvt()
            {
                // Hotswap only requires OVT if we don't have SIO
                return GeneralHotSwap && !m_deviceSupport.HasSIO;
            }

            public static bool RequiresOvt(CyOutputSlewRate slewRate)
            {
                switch (slewRate)
                {
                    case CyOutputSlewRate.I2CHS_FAST:
                    case CyOutputSlewRate.I2CHS_SLOW:
                    case CyOutputSlewRate.I2CFM:
                        return true;
                    default:
                        return false;
                }
            }

            public bool RequiresOvt(CyOutputCurrent outputCurrent)
            {
                // 10 MA only requires OVT if we don't have SIO
                // Hotswap only requires OVT if we don't have SIO
                return (outputCurrent == CyOutputCurrent.SOURCE_4MA_SINK_10MA && !m_deviceSupport.HasSIO);
            }
            #endregion

            /// <summary>
            /// List of all formal parameters that are stored on a per-pin basis (and which therefore
            /// need to be moved around in the expressions storage when the index changes). 
            /// This corresponds to the list of member variables stored in this object
            /// </summary>
            private string[] AllFormals = new string[] 
            {
                Formal_ParamName_PinAlisases,           // m_alias
                Formal_ParamName_DriveMode,             // m_generalDriveMode
                Formal_ParamName_InitialDriveStates,    // m_generalInitialState
                Formal_ParamName_IOVoltages,            // m_generalMinimumSupply
                // No expression storage for m_getPinSetting or m_index
                Formal_ParamName_InputBuffersEnabled,   // m_inputBufferEnabled
                Formal_ParamName_HotSwaps,              // m_inputHotSwap
                Formal_ParamName_ThresholdLevels,       // m_inputHysterisis, m_inputThreshold
                Formal_ParamName_InputsSyncMode,        // m_inputSyncMode
                // m_inputThreshold handled by ThresholdLevels above
                Formal_ParamName_DriveCurrents,         // m_outputCurrent
                Formal_ParamName_OutputDriveLevels,     // m_outputDriveLevel
                Formal_ParamName_OESyncs,               // m_outputEnableSynchronized
                Formal_ParamName_OutputModes,           // m_outputMode
                Formal_ParamName_SlewRate,              // m_outputSlewRate
                Formal_ParamName_SIOGroups,             // m_sioPairId
                Formal_ParamName_PinTypes,              // m_type
                Formal_ParamName_DisplayInputHWConnections, // m_typeIsDigitalInputHw
                Formal_ParamName_DisplayOutputHWConnections,// m_typeIsDigitalOutputHw
                Formal_ParamName_ShowAnnotationTerm,    // m_typeShowExternalTerm
            };

            private void PropogateNewIndex(int oldIndex)
            {
                // Doesn't make sense to propogate when we're in a preview context
                if (m_setPinSetting != null)
                {
                    foreach (string formal in AllFormals)
                    {
                        // Move the old setting to our new position.
                        string oldSetting = m_getPinSetting(formal, oldIndex, Type);
                        m_setPinSetting(formal, oldSetting, Index);
                        // Clear the old data to avoid problems with "leftovers" later
                        m_setPinSetting(formal, "", oldIndex);
                    }
                    m_validatePinSetting(); // Also commits changes
                }
            }

            public void UpdateSIOPaired()
            {
                // If we changed a setting which impacts "sio-ness" in such a way that
                // we are no longer an SIO, we need to also make sure that we are no
                // longer listed as part of an SIO pair. To avoid regrouping, we also
                // need to update the other pin in our pair as well.
                if (SIOPairID >= 0 && !RequiresSIO())
                {
                    int otherIdx = GetOtherSIOIndex(this); // Can't compute after we mark unpaired in the next line
                    m_setPinSetting(Formal_ParamName_SIOGroups, SIOGroupValue_NOT_GROUPED, Index);
                    m_setPinSetting(Formal_ParamName_SIOGroups, SIOGroupValue_NOT_GROUPED, otherIdx);
                    // SIOPairID is not cached, so it is sufficient to update the parameters
                }
            }

            internal List<KeyValuePair<string, string>> ExportFormals()
            {
                List<KeyValuePair<string, string>> result = new List<KeyValuePair<string, string>>();
                foreach (string formal in AllFormals)
                {
                    result.Add(new KeyValuePair<string, string>(formal, m_getPinSetting(formal, Index, Type)));
                }
                return result;
            }

            internal void RestoreFormals(List<KeyValuePair<string, string>> exprs)
            {
                if (m_setPinSetting != null) // Can happen in "preview context"
                    foreach (KeyValuePair<string, string> kvp in exprs)
                    {
                        string formal = kvp.Key;
                        string value = kvp.Value;
                        m_setPinSetting(formal, value, Index);
                    }
                m_validatePinSetting();
            }

            #endregion
        }

        #region Delegates
        public delegate string GetPinSettingDelegate(string key, int index, CyPinType type);
        public delegate bool SetPinSettingDelegate(string key, string value, int index);
        public delegate void ValidateSettingsDelegate();
        public delegate CyCompDevParam ParamLookupDelegate(string name);
        #endregion

        #region Member Variables
        private readonly ParamLookupDelegate m_query;
        private readonly ICyDesignQuery_v1 m_designQuery;
        private readonly CyDeviceSupport m_deviceSupport;
        private readonly ICyInstEdit_v1 m_edit;
        private readonly CyErrorManager m_errMgr;
        #endregion

        #region Constructors
        public CyPinData(ICyInstEdit_v1 edit, CyErrorManager errMgr)
            : this(edit)
        {
            m_edit = edit;
            m_errMgr = errMgr;
        }

        public CyPinData(ICyInstQuery_v1 query)
            : this(query.GetCommittedParam, query.DeviceQuery)
        {
            m_designQuery = query.DesignQuery;
        }
        public CyPinData(ICyInstValidate_v1 query)
            : this(query.GetCommittedParam, query)
        {
        }
        private CyPinData(ParamLookupDelegate query, ICyDeviceQuery_v1 deviceQuery)
        {
            m_query = query;
            m_deviceSupport = new CyDeviceSupport(deviceQuery);
        }
        #endregion

        #region Pins
        private byte? m_pinCount = null;
        public byte PinCount
        {
            get
            {
                if (null == m_pinCount)
                {
                    m_pinCount = m_query(Formal_ParamName_NumPins).GetValueAs<byte>();
                    while (m_pins.Count < m_pinCount)
                    {
                        PerPin pin = null == m_edit
                            ? new PerPin(GetPinSetting, Validate, m_deviceSupport, m_pins.Count)
                            : new PerPin(GetPinSetting, SetPinSetting, Validate, m_deviceSupport, m_pins.Count);

                        m_pins.Add(pin);
                    }
                }
                return m_pinCount.Value;
            }
            set
            {
                if (!m_pinCount.HasValue || m_pinCount.Value != value)
                {
                    if (m_edit.SetParamExpr(Formal_ParamName_NumPins, value.ToString()))
                    {
                        m_pinCount = value;
                        while (m_pins.Count < value)
                        {
                            PerPin pin = new PerPin(GetPinSetting, SetPinSetting, Validate, m_deviceSupport, m_pins.Count);

                            m_pins.Add(pin);
                        }
                        OnPinCountOrTypeChanged();
                        Validate();
                    }
                }
            }
        }

        public bool UsesInterrupts
        {
            get
            {
                return m_pins.Exists(delegate(PerPin pin) { return pin.InputInterrupt != CyInputInterruptTrigger.NONE; });
            }
        }

        public bool UsesDedicatedInterrupts
        {
            get
            {
                return m_pins.Exists(delegate(PerPin pin)
                            { return pin.InputInterrupt != CyInputInterruptTrigger.NONE && pin.DedicatedInterrupt; });
            }
        }

        public PerPin this[int idx]
        {
            get { return m_pins[idx]; }
        }

        private List<PerPin> m_pins = new List<PerPin>();
        public IList<PerPin> Pins
        {
            get
            {
                //We potentially have more pins in memory than are actually shown to the user,
                //We only want to return info for those that can be configured
                if (PinCount != m_pins.Count)
                {
                    PerPin[] pins = new PerPin[PinCount];
                    for (int i = 0; i < pins.Length; i++)
                        pins[i] = m_pins[i];
                    return new ReadOnlyCollection<PerPin>(pins);
                }
                else
                    return new ReadOnlyCollection<PerPin>(m_pins);
            }
        }

        #region Per-Pin Settings
        string[] m_sioPaired = null, m_pinAlias = null, m_pinType = null, m_dispInHw = null, m_dispOutHw = null,
            m_showAnnotation = null, m_driveMode = null, m_driveState = null, m_ioVoltage = null, m_iothreshold = null,
            m_hysteresisMode = null, m_isrMode = null, m_dedicatedIsr = null, m_generalHotSwap = null, m_inputBuffer = null, m_inputSync = null, 
            m_inputSyncMode = null, m_inputMultiplier = null, m_slewRate = null, m_driveLevel = null, m_driveCurrent = null, m_outputSync = null, 
            m_outputMode = null, m_outputClockMode = null, m_outputMultiplier = null, m_oeSync = null;

        private string GetDefaultInputSync(int pinNum)
        {
            string inputSync;
            if (m_deviceSupport.IsPSoC4)
            {
                // Default to transparent for sw-only input, or on devices which don't support sync
                PerPin pin = Pins[pinNum];
                if (!m_deviceSupport.HasPortAdapter || !pin.TypeIsDigitalInputHw)
                    inputSync = ParamValue_DISABLED;
                else
                    inputSync = ParamValue_ENABLED;
            }
            else // Default to double-sync for all PSoC4 devices
            {
                inputSync = ParamValue_ENABLED;
            }
            return inputSync;
        }

        private static string GetDefaultDriveMode(CyPinType pinType)
        {
            if ((pinType & CyPinType.DIGITAL_OUT) == CyPinType.DIGITAL_OUT)
                return DriveModeValue_CMOS_OUT;
            else if ((pinType & CyPinType.BIDIRECTIONAL) == CyPinType.BIDIRECTIONAL)
                return DriveModeValue_OPEN_DRAIN_LO;
            else if ((pinType & CyPinType.DIGITAL_IN) == CyPinType.DIGITAL_IN)
                return DriveModeValue_DIGITAL_HI_Z;
            else if (pinType == CyPinType.ANALOG)
                return DriveModeValue_ANALOG_HI_Z;
            else
            {
                Debug.Fail("Unhandled pin type: " + pinType);
                return DefaultDriveModeValue;
            }
        }
        private static string GetDefaultInputBuffersEnabled(CyPinType pinType)
        {
            return (pinType == CyPinType.ANALOG) ? ParamValue_FALSE : ParamValue_TRUE;
        }
        private string GetDefaultDriveState(int index)
        {
            bool isM0S8 = (null != m_deviceSupport) && (m_deviceSupport.IsPSoC4 || m_deviceSupport.IsTSG4);
            PerPin pin = m_pins[index];
            bool isAnalog = ((pin.Type & CyPinType.ANALOG) > 0);
            bool isHwOutput = ((pin.Type & CyPinType.BIDIRECTIONAL) > 0) ||
                (((pin.Type & CyPinType.DIGITAL_OUT) > 0) && pin.TypeIsDigitalOutputHw);
            bool isClkOut = pin.OutputMode == CyOutputMode.CLOCK || pin.OutputMode == CyOutputMode.CLOCK_INV;

            // On PSoC4, default initial value for DSI driven pin w/o a HW OE should be '1'
            if (isM0S8 && ((isHwOutput && (pin.Type & CyPinType.OE) == 0) || isClkOut || isAnalog))
                return InitialDriveStateValue_HIGH;

            switch (pin.GeneralDriveMode)
            {
                case CyDriveMode.HIGH_IMPEDANCE_ANALOG:
                case CyDriveMode.STRONG_DRIVE:
                case CyDriveMode.HIGH_IMPEDANCE_DIGITAL:
                case CyDriveMode.OPEN_DRAIN_DRIVE_HIGH:
                case CyDriveMode.OPEN_DRAIN_DRIVE_LOW:
                case CyDriveMode.RESISTIVE_PULL_DOWN:
                    return InitialDriveStateValue_LOW;
                case CyDriveMode.RESISTIVE_PULL_UP:
                case CyDriveMode.RESISTIVE_PULL_UP_DOWN:
                    return InitialDriveStateValue_HIGH;
                default:
                    Debug.Fail(String.Format(Resource1.UnhandledDriveMode, pin.GeneralDriveMode));
                    return InitialDriveStateValue_LOW;
            }
        }

        private string GetPinSetting(string key, int index, CyPinType pinType)
        {
            int priorIdx = (null != m_pinType) ? (Math.Min(m_pinType.Length, index) - 1) : -1;
            bool pinTypeMatch = (priorIdx >= 0) && (PerPin.ConvertPinType(m_pinType[priorIdx]) == pinType);

            switch (key)
            {
                case Formal_ParamName_SIOGroups:
                    return ProcessPinSettingRequest(ref m_sioPaired, key, index, false, DefaultSIOGroupValue);
                case Formal_ParamName_PinAlisases:
                    return ProcessPinSettingRequest(ref m_pinAlias, key, index, false, String.Empty);
                //Type
                case Formal_ParamName_PinTypes:
                    return ProcessPinSettingRequest(ref m_pinType, key, index, true, DefaultPinTypesValue);
                case Formal_ParamName_DisplayInputHWConnections:
                    return ProcessPinSettingRequest(ref m_dispInHw, key, index, pinTypeMatch, DefaultDisplay);
                case Formal_ParamName_DisplayOutputHWConnections:
                    return ProcessPinSettingRequest(ref m_dispOutHw, key, index, pinTypeMatch, DefaultDisplay);
                case Formal_ParamName_ShowAnnotationTerm:
                    return ProcessPinSettingRequest(ref m_showAnnotation, key, index, pinTypeMatch, DefaultShowAnnotValue);
                //General
                case Formal_ParamName_DriveMode:
                    return ProcessPinSettingRequest(ref m_driveMode, key, index, pinTypeMatch, GetDefaultDriveMode(pinType));
                case Formal_ParamName_InitialDriveStates:
                    return ProcessPinSettingRequest(ref m_driveState, key, index, false, GetDefaultDriveState(index));
                case Formal_ParamName_IOVoltages:
                    return ProcessPinSettingRequest(ref m_ioVoltage, key, index, pinTypeMatch, DefaultIOVoltageValue);
                //Input
                case Formal_ParamName_ThresholdLevels:
                    return ProcessPinSettingRequest(ref m_iothreshold, key, index, pinTypeMatch, DefaultThresholdLevelValue);
                case Formal_ParamName_HysteresisModes:
                    return ProcessPinSettingRequest(ref m_hysteresisMode, key, index, pinTypeMatch, DefaultHysteresisModeValue);
                case Formal_ParamName_InterruptMode:
                    return ProcessPinSettingRequest(ref m_isrMode, key, index, pinTypeMatch, DefaultInterruptModeValue);
                case Formal_ParamName_DedicatedInterrupt:
                    return ProcessPinSettingRequest(ref m_dedicatedIsr, key, index, pinTypeMatch, DefaultDedicatedInterrupt);
                case Formal_ParamName_HotSwaps:
                    return ProcessPinSettingRequest(ref m_generalHotSwap, key, index, pinTypeMatch, DefaultHotSwapValue);
                case Formal_ParamName_InputBuffersEnabled:
                    return ProcessPinSettingRequest(ref m_inputBuffer, key, index, pinTypeMatch, GetDefaultInputBuffersEnabled(pinType));
                case Formal_ParamName_InputsSynchronized:
                    string inputSync = GetDefaultInputSync(index);
                    return ProcessPinSettingRequest(ref m_inputSync, key, index, pinTypeMatch, inputSync);
                case Formal_ParamName_InputsSyncMode:
                    return ProcessPinSettingRequest(ref m_inputSyncMode, key, index, pinTypeMatch, DefaultInputsSyncModeValue);
                case Formal_ParamName_InputMultiplier:
                    return ProcessPinSettingRequest(ref m_inputMultiplier, key, index, pinTypeMatch, DefaultMultiplierIdx.ToString());
                //Output
                case Formal_ParamName_SlewRate:
                    return ProcessPinSettingRequest(ref m_slewRate, key, index, pinTypeMatch, DefaultSlewRateValue);
                case Formal_ParamName_OutputDriveLevels:
                    return ProcessPinSettingRequest(ref m_driveLevel, key, index, pinTypeMatch, DefaultOutputDriveLevelValue);
                case Formal_ParamName_DriveCurrents:
                    return ProcessPinSettingRequest(ref m_driveCurrent, key, index, pinTypeMatch, DefaultDriveCurrentValue);
                case Formal_ParamName_OutputsSynchronized:
                    return ProcessPinSettingRequest(ref m_outputSync, key, index, pinTypeMatch, DefaultOutputsSynchronizedValue);
                case Formal_ParamName_OutputModes:
                    return ProcessPinSettingRequest(ref m_outputMode, key, index, pinTypeMatch, DefaultOutputModeValue);
                case Formal_ParamName_OutputClockModes:
                    return ProcessPinSettingRequest(ref m_outputClockMode, key, index, pinTypeMatch, DefaultOutputClockModesValue);
                case Formal_ParamName_OESyncs:
                    return ProcessPinSettingRequest(ref m_oeSync, key, index, pinTypeMatch, DefaultOESyncsValue);
                case Formal_ParamName_OutputMultiplier:
                    return ProcessPinSettingRequest(ref m_outputMultiplier, key, index, pinTypeMatch, DefaultMultiplierIdx.ToString());
                default:
                    Debug.Fail("Unhandled parameter: " + key);
                    return String.Empty;
            }
        }

        private static void EnsureValidIndex(ref string[] settings, int index, bool usePrevious, string defaultVal)
        {
            int requiredSize = index + 1;
            if (requiredSize > settings.Length)
            {
                int oldSize = settings.Length;
                Array.Resize(ref settings, requiredSize);

                //Pick the previous pin to copy or use default
                for (int i = oldSize; i < settings.Length; i++)
                    settings[i] = (usePrevious && i > 0) ? settings[i - 1] : defaultVal;
            }
            // Always use default here - for some settings (like minimum supply) the default value is the empty
            // string, and we don't want to end up copying previous here
            if (String.IsNullOrEmpty(settings[index]))
                settings[index] = defaultVal; 
        }

        private string ProcessPinSettingRequest(
            ref string[] settings, string key, int index, bool usePrevious, string defaultValue)
        {
            if (null == settings)
            {
                string value = m_query(key).Value;
                settings = String.IsNullOrEmpty(value) ? new string[0] : value.Split(',');
            }
            EnsureValidIndex(ref settings, index, usePrevious, defaultValue);
            return settings[index].Trim();
        }

        private void UpdatePinSettingIfNotSetByUser(ref string[] settings, int index, string key, string newValue)
        {
            // Update our cached value if both of the following are true:
            // * We have a cached value in the first place
            // * There is no value saved to the parameter (meaning the user never explicitly set it)
            if (settings != null && settings.Length > index)
            {
                string v = m_query(key).Value;
                if (String.IsNullOrEmpty(v))
                    settings[index] = newValue;
            }
        }

        private bool SetPinSetting(string key, string value, int index)
        {
            string[] values;
            switch (key)
            {
                case Formal_ParamName_SIOGroups:
                    values = m_sioPaired;
                    break;
                case Formal_ParamName_PinAlisases:
                    values = m_pinAlias;
                    break;
                //Type
                case Formal_ParamName_PinTypes:
                    values = m_pinType;
                    // Changing the pin type changes the defaults for drive mode and initial state - clear those caches
                    string newDriveMode = GetDefaultDriveMode(PerPin.ConvertPinType(value));
                    UpdatePinSettingIfNotSetByUser(ref m_driveMode, index, Formal_ParamName_DriveMode, newDriveMode);
                    m_pins[index].DriveModeChanged();
                    string newDriveState = GetDefaultDriveState(index);
                    UpdatePinSettingIfNotSetByUser(ref m_driveState, index, Formal_ParamName_InitialDriveStates, newDriveState);
                    m_pins[index].InitialDriveStateChanged();

                    OnPinCountOrTypeChanged();
                    break;
                case Formal_ParamName_DisplayInputHWConnections:
                    // SW vs. HW for input can change default input sync
                    values = m_dispInHw;
                    values[index] = value; // Need to set before GetDefaultInputSync checks it to determine the default
                    m_pins[index].IsInHwChanged();
                    string newSync = GetDefaultInputSync(index);
                    UpdatePinSettingIfNotSetByUser(ref m_inputSync, index, Formal_ParamName_InputsSynchronized, newSync);
                    m_pins[index].InputSyncChanged();
                    break;
                case Formal_ParamName_DisplayOutputHWConnections:
                    // SW vs. HW for output can change initial drive state
                    values = m_dispOutHw;
                    values[index] = value; // Need to set before GetDefaultDriveState checks it to determine the default
                    m_pins[index].IsOutHwChanged();
                    string newInitState = GetDefaultDriveState(index);
                    UpdatePinSettingIfNotSetByUser(ref m_driveState, index, Formal_ParamName_InitialDriveStates, newInitState);
                    m_pins[index].InitialDriveStateChanged();
                    break;
                case Formal_ParamName_ShowAnnotationTerm:
                    values = m_showAnnotation;
                    break;
                //General
                case Formal_ParamName_DriveMode:
                    values = m_driveMode;
                    // Changing the drive mode changes the defaults initial state - clear that cache
                    values[index] = value;
                    m_pins[index].DriveModeChanged();
                    string newDriveState2 = GetDefaultDriveState(index);
                    UpdatePinSettingIfNotSetByUser(ref m_driveState, index, Formal_ParamName_InitialDriveStates, newDriveState2);
                    m_pins[index].InitialDriveStateChanged();

                    break;
                case Formal_ParamName_InitialDriveStates:
                    values = m_driveState;
                    break;
                case Formal_ParamName_IOVoltages:
                    values = m_ioVoltage;
                    break;
                //Input
                case Formal_ParamName_ThresholdLevels:
                    values = m_iothreshold;
                    break;
                case Formal_ParamName_HysteresisModes:
                    values = m_hysteresisMode;
                    break;
                case Formal_ParamName_InterruptMode:
                    values = m_isrMode;
                    break;
                case Formal_ParamName_DedicatedInterrupt:
                    values = m_dedicatedIsr;
                    break;
                case Formal_ParamName_HotSwaps:
                    values = m_generalHotSwap;
                    break;
                case Formal_ParamName_InputBuffersEnabled:
                    values = m_inputBuffer;
                    break;
                case Formal_ParamName_InputsSynchronized:
                    values = m_inputSync;
                    break;
                case Formal_ParamName_InputMultiplier:
                    values = m_inputMultiplier;
                    break;
                case Formal_ParamName_InputsSyncMode:
                    values = m_inputSyncMode;
                    break;
                //Output
                case Formal_ParamName_SlewRate:
                    values = m_slewRate;
                    break;
                case Formal_ParamName_OutputDriveLevels:
                    values = m_driveLevel;
                    break;
                case Formal_ParamName_DriveCurrents:
                    values = m_driveCurrent;
                    break;
                case Formal_ParamName_OutputsSynchronized:
                    values = m_outputSync;
                    break;
                case Formal_ParamName_OutputModes:
                    values = m_outputMode;
                    break;
                case Formal_ParamName_OutputClockModes:
                    values = m_outputClockMode;
                    break;
                case Formal_ParamName_OESyncs:
                    values = m_oeSync;
                    break;
                case Formal_ParamName_OutputMultiplier:
                    values = m_outputMultiplier;
                    break;
                default:
                    Debug.Fail("Unhandled parameter: " + key);
                    return false;
            }

            values[index] = value;
            string toSave = String.Join(",", values);
            return m_edit.SetParamExpr(key, toSave);
        }
        #endregion
        #endregion

        #region Mapping
        private bool? m_mappingDisplayAsBus = null;
        public bool MappingDisplayAsBus
        {
            get
            {
                if (null == m_mappingDisplayAsBus)
                {
                    bool val;
                    m_query(Formal_ParamName_DisplayAsBus).TryGetValueAs(out val);
                    m_mappingDisplayAsBus = val;
                }
                return m_mappingDisplayAsBus.Value;
            }
            set
            {
                if (!m_mappingDisplayAsBus.HasValue || m_mappingDisplayAsBus.Value != value)
                {
                    if (m_edit.SetParamExpr(Formal_ParamName_DisplayAsBus, value.ToString()))
                    {
                        m_mappingDisplayAsBus = value;
                        Validate();
                    }
                }
            }
        }

        private bool? m_mappingContigious = null;
        public bool MappingContigious
        {
            get
            {
                if (null == m_mappingContigious)
                    GetContigiousSpanning();
                return m_mappingContigious.Value;
            }
            set
            {
                if (!m_mappingContigious.HasValue || m_mappingContigious.Value != value)
                    SetContigiousSpanning(value, !value);
            }
        }

        private bool? m_mappingSpanning = null;
        public bool MappingSpanning
        {
            get
            {
                if (null == m_mappingSpanning)
                    GetContigiousSpanning();
                return m_mappingSpanning.Value;
            }
            set
            {
                if (!m_mappingSpanning.HasValue || m_mappingSpanning.Value != value)
                    SetContigiousSpanning(!value, value);
            }
        }

        private void GetContigiousSpanning()
        {
            string valStr = m_query(Formal_ParamName_LayoutMode).Value;
            switch (valStr)
            {
                case LayoutModeValue_CONT_SPANNING:
                    m_mappingContigious = true;
                    m_mappingSpanning = true;
                    break;
                case LayoutModeValue_CONT_NONSPANNING:
                    m_mappingContigious = true;
                    m_mappingSpanning = false;
                    break;
                case LayoutModeValue_NONCONT_SPANNING:
                    m_mappingContigious = false;
                    m_mappingSpanning = true;
                    break;
                case LayoutModeValue_NONCONT_NONSPANNING:
                    m_mappingContigious = false;
                    m_mappingSpanning = false;
                    break;
                default:
                    Debug.Fail("Unhandled layout value: " + valStr);
                    m_mappingContigious = true;
                    m_mappingSpanning = false;
                    break;
            }
        }
        private void SetContigiousSpanning(bool contigious, bool spanning)
        {
            Debug.Assert(contigious = !spanning, "Contigious & Spanning are currently mutually exclusive");
            string layout = contigious
                ? LayoutModeValue_CONT_NONSPANNING
                : LayoutModeValue_NONCONT_SPANNING;
            if (m_edit.SetParamExpr(Formal_ParamName_LayoutMode, layout))
            {
                m_mappingContigious = contigious;
                m_mappingSpanning = spanning;
                Validate();
            }
        }
        #endregion

        #region Reset
        private CyPowerOnRestMode? m_powerOnReset = null;
        public CyPowerOnRestMode PowerOnReset
        {
            get
            {
                if (null == m_powerOnReset)
                {
                    int valInt;
                    m_query(Formal_ParamName_PowerOnReset).TryGetValueAs(out valInt);
                    switch (valInt)
                    {
                        case PORValue_Unspecified:
                            m_powerOnReset = CyPowerOnRestMode.UNSPECIFIED;
                            break;
                        case PORValue_HiZAnalog:
                            m_powerOnReset = CyPowerOnRestMode.HIZ_ANALOG;
                            break;
                        case PORValue_PulledUp:
                            m_powerOnReset = CyPowerOnRestMode.PULLED_UP;
                            break;
                        case PORValue_PulledDown:
                            m_powerOnReset = CyPowerOnRestMode.PULLED_DOWN;
                            break;
                        default:
                            Debug.Fail("Unhandled POR val: " + valInt);
                            m_powerOnReset = CyPowerOnRestMode.UNSPECIFIED;
                            break;
                    }
                }
                return m_powerOnReset.Value;
            }
            set
            {
                if (!m_powerOnReset.HasValue || m_powerOnReset.Value != value)
                {
                    string val;
                    switch (value)
                    {
                        case CyPowerOnRestMode.UNSPECIFIED:
                            val = PORValue_Unspecified.ToString();
                            break;
                        case CyPowerOnRestMode.HIZ_ANALOG:
                            val = PORValue_HiZAnalog.ToString();
                            break;
                        case CyPowerOnRestMode.PULLED_UP:
                            val = PORValue_PulledUp.ToString();
                            break;
                        case CyPowerOnRestMode.PULLED_DOWN:
                            val = PORValue_PulledDown.ToString();
                            break;
                        default:
                            Debug.Fail("unhandled POR mode: " + PowerOnReset);
                            val = PORValue_Unspecified.ToString();
                            break;
                    }
                    if (m_edit.SetParamExpr(Formal_ParamName_PowerOnReset, val))
                    {
                        m_powerOnReset = value;
                        Validate();
                    }
                }
            }
        }
        #endregion

        #region Clocking
        private int? m_clockPaPin = null;
        public int ClockPAPin
        {
            get
            {
                if (null == m_clockPaPin)
                {
                    int val;
                    m_query(Formal_ParamName_PaPin).TryGetValueAs(out val);
                    m_clockPaPin = val;
                }
                return m_clockPaPin.Value;
            }
            set
            {
                if (!m_clockPaPin.HasValue || m_clockPaPin.Value != value)
                {
                    if (m_edit.SetParamExpr(Formal_ParamName_PaPin, m_clockPaPin.ToString()))
                    {
                        m_clockPaPin = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClock? m_clockInput = null;
        public CyPinClock ClockInput
        {
            get
            {
                if (null == m_clockInput)
                {
                    m_clockInput = GetPinClock(Formal_ParamName_ShowInClkTerm, Formal_ParamName_UsePaInClk, Formal_ParamName_InvertInClock);
                }
                return m_clockInput.Value;
            }
            set
            {
                if (!m_clockInput.HasValue || m_clockInput.Value != value)
                {
                    if (SetPinClock(Formal_ParamName_ShowInClkTerm, Formal_ParamName_UsePaInClk, Formal_ParamName_InvertInClock, value))
                    {
                        m_clockInput = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClockEnRst? m_clockInputEnable = null;
        public CyPinClockEnRst ClockInputEnable
        {
            get
            {
                if (null == m_clockInputEnable)
                {
                    m_clockInputEnable = GetPinClockEnableReset(Formal_ParamName_ShowInClkEnTerm, Formal_ParamName_UsePaInClkEn, Formal_ParamName_InvertInClockEn);
                }
                return m_clockInputEnable.Value;
            }
            set
            {
                if (!m_clockInputEnable.HasValue || m_clockInputEnable.Value != value)
                {
                    if (SetPinClockEnableReset(Formal_ParamName_ShowInClkEnTerm, Formal_ParamName_UsePaInClkEn, Formal_ParamName_InvertInClockEn, value))
                    {
                        m_clockInputEnable = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClockEnable? m_clockInputEnableOn = null;
        public CyPinClockEnable ClockInputEnableOn
        {
            get
            {
                if (null == m_clockInputEnableOn)
                {
                    m_clockInputEnableOn = GetPinClockEnableMode(Formal_ParamName_InClkEnableMode);
                }
                return m_clockInputEnableOn.Value;
            }
            set
            {
                if (!m_clockInputEnableOn.HasValue || m_clockInputEnableOn.Value != value)
                {
                    if (SetPinClockEnableMode(Formal_ParamName_InClkEnableMode, value))
                    {
                        m_clockInputEnableOn = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClockEnRst? m_clockInputReset = null;
        public CyPinClockEnRst ClockInputReset
        {
            get
            {
                if (null == m_clockInputReset)
                {
                    m_clockInputReset = GetPinClockEnableReset(Formal_ParamName_ShowInRstTerm, Formal_ParamName_UsePaInRst, Formal_ParamName_InvertInReset);
                }
                return m_clockInputReset.Value;
            }
            set
            {
                if (!m_clockInputReset.HasValue || m_clockInputReset.Value != value)
                {
                    if (SetPinClockEnableReset(Formal_ParamName_ShowInRstTerm, Formal_ParamName_UsePaInRst, Formal_ParamName_InvertInReset, value))
                    {
                        m_clockInputReset = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClock? m_clockOutput = null;
        public CyPinClock ClockOutput
        {
            get
            {
                if (null == m_clockOutput)
                {
                    m_clockOutput = GetPinClock(Formal_ParamName_ShowOutClkTerm, Formal_ParamName_UsePaOutClk, Formal_ParamName_InvertOutClock);
                }
                return m_clockOutput.Value;
            }
            set
            {
                if (!m_clockOutput.HasValue || m_clockOutput.Value != value)
                {
                    if (SetPinClock(Formal_ParamName_ShowOutClkTerm, Formal_ParamName_UsePaOutClk, Formal_ParamName_InvertOutClock, value))
                    {
                        m_clockOutput = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClockEnRst? m_clockOutputEnable = null;
        public CyPinClockEnRst ClockOutputEnable
        {
            get
            {
                if (null == m_clockOutputEnable)
                {
                    m_clockOutputEnable = GetPinClockEnableReset(Formal_ParamName_ShowOutClkEnTerm, Formal_ParamName_UsePaOutClkEn, Formal_ParamName_InvertOutClockEn);
                }
                return m_clockOutputEnable.Value;
            }
            set
            {
                if (!m_clockOutputEnable.HasValue || m_clockOutputEnable.Value != value)
                {
                    if (SetPinClockEnableReset(Formal_ParamName_ShowOutClkEnTerm, Formal_ParamName_UsePaOutClkEn, Formal_ParamName_InvertOutClockEn, value))
                    {
                        m_clockOutputEnable = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClockEnable? m_clockOutputEnableOn = null;
        public CyPinClockEnable ClockOutputEnableOn
        {
            get
            {
                if (null == m_clockOutputEnableOn)
                {
                    m_clockOutputEnableOn = GetPinClockEnableMode(Formal_ParamName_OutClkEnableMode);
                }
                return m_clockOutputEnableOn.Value;
            }
            set
            {
                if (!m_clockOutputEnableOn.HasValue || m_clockOutputEnableOn.Value != value)
                {
                    if (SetPinClockEnableMode(Formal_ParamName_OutClkEnableMode, value))
                    {
                        m_clockOutputEnableOn = value;
                        Validate();
                    }
                }
            }
        }

        private bool? m_clockOutputResetEnable = null;
        public bool ClockOutputResetEnable
        {
            get
            {
                if (null == m_clockOutputResetEnable)
                {
                    bool val;
                    m_query(Formal_ParamName_OutputResetEnabled).TryGetValueAs(out val);
                    m_clockOutputResetEnable = val;
                }
                return m_clockOutputResetEnable.Value;
            }
            set
            {
                if (!m_clockOutputResetEnable.HasValue || m_clockOutputResetEnable.Value != value)
                {
                    if (m_edit.SetParamExpr(Formal_ParamName_OutputResetEnabled, value.ToString()))
                    {
                        m_clockOutputResetEnable = value;
                        Validate();
                    }
                }
            }
        }

        private bool? m_clockOutputOeResetEnable = null;
        public bool ClockOutputOeResetEnable
        {
            get
            {
                if (null == m_clockOutputOeResetEnable)
                {
                    bool val;
                    m_query(Formal_ParamName_OEResetEnabled).TryGetValueAs(out val);
                    m_clockOutputOeResetEnable = val;
                }
                return m_clockOutputOeResetEnable.Value;
            }
            set
            {
                if (!m_clockOutputOeResetEnable.HasValue || m_clockOutputOeResetEnable.Value != value)
                {
                    if (m_edit.SetParamExpr(Formal_ParamName_OEResetEnabled, value.ToString()))
                    {
                        m_clockOutputOeResetEnable = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClockEnRst? m_clockOutputReset = null;
        public CyPinClockEnRst ClockOutputReset
        {
            get
            {
                if (null == m_clockOutputReset)
                {
                    m_clockOutputReset = GetPinClockEnableReset(Formal_ParamName_ShowOutRstTerm, Formal_ParamName_UsePaOutRst, Formal_ParamName_InvertOutReset);
                }
                return m_clockOutputReset.Value;
            }
            set
            {
                if (!m_clockOutputReset.HasValue || m_clockOutputReset.Value != value)
                {
                    if (SetPinClockEnableReset(Formal_ParamName_ShowOutRstTerm, Formal_ParamName_UsePaOutRst, Formal_ParamName_InvertOutReset, value))
                    {
                        m_clockOutputReset = value;
                        Validate();
                    }
                }
            }
        }

        private CyPinClock GetPinClock(string showClkTerm, string usePaClk, string invertClk)
        {
            CyPinClock clk;
            bool term, usePa, invert;
            m_query(showClkTerm).TryGetValueAs(out term);
            m_query(usePaClk).TryGetValueAs(out usePa);
            m_query(invertClk).TryGetValueAs(out invert);

            if (term)
                clk = invert ? CyPinClock.EXTERNAL_INV : CyPinClock.EXTERNAL;
            else if (usePa)
                clk = invert ? CyPinClock.PIN_INV : CyPinClock.PIN;
            else
                clk = invert ? CyPinClock.HFCLK_INV : CyPinClock.HFCLK;

            return clk;
        }

        private bool SetPinClock(string showClkTerm, string usePaClk, string invertClk, CyPinClock clk)
        {
            bool success = true;

            bool term = (CyPinClock.EXTERNAL == clk || CyPinClock.EXTERNAL_INV == clk);
            bool usePa = (CyPinClock.PIN == clk || CyPinClock.PIN_INV == clk);
            bool invert = (CyPinClock.EXTERNAL_INV == clk || CyPinClock.HFCLK_INV == clk || CyPinClock.PIN_INV == clk);

            success &= m_edit.SetParamExpr(showClkTerm, term.ToString());
            success &= m_edit.SetParamExpr(usePaClk, usePa.ToString());
            success &= m_edit.SetParamExpr(invertClk, invert.ToString());

            return success;
        }

        private CyPinClockEnRst GetPinClockEnableReset(string showClkTerm, string usePaClk, string invertClk)
        {
            CyPinClockEnRst clk;
            bool term, usePa, invert;
            m_query(showClkTerm).TryGetValueAs(out term);
            m_query(usePaClk).TryGetValueAs(out usePa);
            m_query(invertClk).TryGetValueAs(out invert);

            if (term)
                clk = invert ? CyPinClockEnRst.EXTERNAL_INV : CyPinClockEnRst.EXTERNAL;
            else if (usePa)
                clk = invert ? CyPinClockEnRst.PIN_INV : CyPinClockEnRst.PIN;
            else
                clk = CyPinClockEnRst.NONE;
            return clk;
        }

        private bool SetPinClockEnableReset(string showClkTerm, string usePaClk, string invertClk, CyPinClockEnRst clk)
        {
            bool success = true;

            bool term = (CyPinClockEnRst.EXTERNAL == clk || CyPinClockEnRst.EXTERNAL_INV == clk);
            bool usePa = (CyPinClockEnRst.PIN == clk || CyPinClockEnRst.PIN_INV == clk);
            bool invert = (CyPinClockEnRst.EXTERNAL_INV == clk || CyPinClockEnRst.PIN_INV == clk);

            success &= m_edit.SetParamExpr(showClkTerm, term.ToString());
            success &= m_edit.SetParamExpr(usePaClk, usePa.ToString());
            success &= m_edit.SetParamExpr(invertClk, invert.ToString());

            return success;
        }

        private CyPinClockEnable GetPinClockEnableMode(string enableMode)
        {
            string val = m_query(enableMode).Value;
            return (ClkEnableModeValue_LEVEL == val)
                ? CyPinClockEnable.LEVEL
                : CyPinClockEnable.RISING_EDGE;
        }
        private bool SetPinClockEnableMode(string enableMode, CyPinClockEnable enable)
        {
            string val = (CyPinClockEnable.LEVEL == enable)
                ? ClkEnableModeValue_LEVEL
                : ClkEnableModeValue_EDGE;
            return m_edit.SetParamExpr(enableMode, val);
        }
        #endregion

        #region Events
        internal delegate void PinCountOrTypeChangedDelegate();
        internal event PinCountOrTypeChangedDelegate PinCountOrTypeChanged;

        private void OnPinCountOrTypeChanged()
        {
            PinCountOrTypeChangedDelegate evt = PinCountOrTypeChanged;
            if (null != evt)
                evt();
        }
        #endregion

        #region Functions
        public void DeletePin(int idx)
        {
            if (m_pins[idx].SIOPairID >= 0)
            {
                // If paired, unpair both this and the other pin in the pair to avoid regrouping pairs
                int otherIdx = PerPin.GetOtherSIOIndex(m_pins[idx]); // Can't calculate after the next step
                m_pins[idx].SIOPairID = -1;
                m_pins[otherIdx ].SIOPairID = -1;
            }
            if (0 <= idx && idx < m_pins.Count)
            {
                for (int i = idx + 1; i < m_pinCount; i++)
                    m_pins[i].Index--;

                m_pins.RemoveAt(idx);
                PinCount--;
            }
            else
                Debug.Fail("Invalid item to delete");
        }

        public void MoveUp(int idx)
        {
            if (idx > 0 && m_pins.Count > idx)
            {
                SwapPins(idx, idx - 1);
            }
            else
                Debug.Fail("Invalid item to move up");
        }

        public void MoveDown(int idx)
        {
            if (idx < m_pins.Count - 1)
            {
                SwapPins(idx, idx + 1);
            }
            else
                Debug.Fail("Invalid item to move down");
        }

        private void SwapPins(int first, int second)
        {
            PerPin firstPin = m_pins[first];
            PerPin secondPin = m_pins[second];
            List<KeyValuePair<string, string>> formalsFirst = firstPin.ExportFormals();
            List<KeyValuePair<string, string>> formalsSecond = secondPin.ExportFormals();
            // Move the pins, update their indices, then restore their formals. Changing the index
            // updates the formals, so we need to perform the restoration last.
            m_pins[first] = secondPin;
            m_pins[second] = firstPin;

            secondPin.Index = first;
            firstPin.Index = second;

            firstPin.RestoreFormals(formalsFirst);
            secondPin.RestoreFormals(formalsSecond);
        }

        internal byte GetSioGroupCnt()
        {
            byte cnt = 0;
            for (int i = 0; i < PinCount; i++)
            {
                if (m_pins[i].RequiresSIO() && (m_pins[i].SIOPairID == -1 || m_pins[i].SIOPairID == 0))
                    cnt++;
            }
            return cnt;
        }

        public string GetPinPoundDefineName(int index)
        {
            if (null != m_query)
            {
                string instName = m_query(Builtin_ParamName_InstName).Value;

                string alias = m_pins[index].Alias;
                return String.IsNullOrEmpty(alias)
                    ? String.Format("{0}_{1}", instName, index)
                    : String.Format("{0}_{1}", instName, alias);
            }
            return String.Empty;
        }

        public CyPinAssignmentInfo_v1 GetAssignment(int index)
        {
            if (null != m_designQuery)
            {
                if (m_designQuery.DesignInfoAvailable)
                {
                    List<CyPinAssignmentInfo_v1> assignmentInfo = m_designQuery.GetPinAssignmentInfo_v1(index);
                    if (assignmentInfo.Count == 1 && assignmentInfo[0].IsAssigned)
                    {
                        return assignmentInfo[0];
                    }
                }
            }

            return null;
        }

        #region Validators
        private interface ICyErrorHandler
        {
            void AddError(string msg, ErrorMgrKey settingOwner, string paramName);
        }
        private class CyInstValidateErrorHandler : ICyErrorHandler
        {
            private ICyInstValidate_v1 m_instValidate;

            public CyInstValidateErrorHandler(ICyInstValidate_v1 instValidate)
            {
                m_instValidate = instValidate;
            }

            void ICyErrorHandler.AddError(string msg, ErrorMgrKey owner, string paramName)
            {
                m_instValidate.AddError(paramName, new CyCustErr(msg));
            }
        }
        private class CyErrorMgrErrorHandler : ICyErrorHandler
        {
            private CyErrorManager m_errMgr;

            public CyErrorMgrErrorHandler(CyErrorManager instValidate)
            {
                m_errMgr = instValidate;
            }

            void ICyErrorHandler.AddError(string msg, ErrorMgrKey owner, string paramName)
            {
                m_errMgr.SetError(owner, msg);
            }
        }

        public static CyCustErr ValidateAlias(int index, string name)
        {
            string msg;
            return (!String.IsNullOrEmpty(name) && !CyBasic.IsValidCCppIdentifierName(name, out msg))
                ? new CyCustErr(String.Format(Resource1.Err_NotValidCIdentifier, index, name, msg))
                : CyCustErr.Ok;
        }

        internal void Validate()
        {
            m_edit.CommitParamExprs();
            m_errMgr.ClearErrors();
            Validate(m_deviceSupport, new CyErrorMgrErrorHandler(m_errMgr));
        }

        public void Validate(ICyInstValidate_v1 instVal)
        {
            Validate(new CyDeviceSupport(instVal), new CyInstValidateErrorHandler(instVal));
        }

        private void Validate(CyDeviceSupport devSupport, ICyErrorHandler errHandler)
        {
            //Per pin data needs to be validated here. Make sure to validate the GUI visible param not the 
            //corresponding verilog one as that is the only way for the param to have an error show up on it when the 
            //user is entering values.
            CheckAtLeastOneTypeSelected(errHandler);
            CheckModesRequiringPortAdapter(errHandler);
            CheckCannotUseAnalogIfSIO(errHandler);
            CheckCannotEnableInputBufferIfAnalogHiZ(errHandler);
            CheckSIOLayoutRestrictions(errHandler);
            CheckCannotBeContiguousAndAnalog(errHandler);
            CheckSIOPairSettingsMatch(errHandler);
            CheckCannotSpanAndUseInterrupts(errHandler);
            CheckMaxCountIfNotSpanning(errHandler);
            CheckDisplayAsBusRequiresHomogenous(errHandler);

            CheckInputThresholdSameIfContiguous(errHandler);
            CheckSIOHysteresisSameIfContiguous(errHandler);
            CheckCannotBeResistivePullAndVrefOut(errHandler);
            CheckInputSync(devSupport, errHandler);

            if (devSupport.HasData && !devSupport.HasSIO)
                CheckCannotUsePinTypeOnDevice(errHandler, "SIO", delegate(PerPin pin) { return pin.GetSIOCauses(); }); 
            if (devSupport.HasData && !devSupport.HasOVT)
                CheckCannotUsePinTypeOnDevice(errHandler, "OVT", delegate(PerPin pin) { return pin.GetOVTCauses(); });
            CheckCannotRequireSIOAndOVT(errHandler);
            if (devSupport.HasData && !devSupport.HasPortAdapter)
                CheckCannotUsePAOnDevice(errHandler);

            CheckCannotUseGPIOv2Features(errHandler);
            CheckCannotUseVrefMultipliers(errHandler);

            if (devSupport.IsPSoC4)
            {
                CheckPORM0S8(errHandler);
                CheckSlewRateSameIfContiguousM0S8(errHandler);
                CheckI2CSlewRequirements(errHandler);
                CheckSIOVrefSettingsMatch(errHandler);
                CheckVrefMultiplierRequirements(errHandler);

                if (devSupport.IsTSG4)
                {
                    CheckNotAnalogGen4(errHandler);
                }
            }
        }

        private void CheckInputSync(CyDeviceSupport devSupport, ICyErrorHandler errHandler)
        {
            bool hasSingleSync = !devSupport.HasData || devSupport.HasPortAdapter;
            bool hasDblSync = (!devSupport.HasData || devSupport.IsPSoC3 || devSupport.IsPSoC5 || devSupport.HasPortAdapter);

            for (int i = 0; i < PinCount; i++)
            {
                if (m_pins[i].InputSyncMode == CyInputSyncMode.DOUBLE_SYNC && !hasDblSync)
                {
                    errHandler.AddError(
                        String.Format(Resource1.Err_InputSyncInvalid, i, Resource1.InputSyncMode_DoubleSync),
                        ErrorMgrKey.INPUT_SYNC_MODE, Formal_ParamName_InputsSyncMode);
                }
                else if (m_pins[i].InputSyncMode == CyInputSyncMode.SINGLE_SYNC && !hasSingleSync)
                {
                    errHandler.AddError(
                        String.Format(Resource1.Err_InputSyncInvalid, i, Resource1.InputSyncMode_SingleSync),
                        ErrorMgrKey.INPUT_SYNC_MODE, Formal_ParamName_InputsSyncMode);
                }
            }
        }

        private void CheckCannotSpanAndUseInterrupts(ICyErrorHandler errHandler)
        {
            if (PinCount > 1) // Contiguous vs. spanning has no meaning for a single pin
            {
                if (MappingSpanning && UsesInterrupts)
                {
                    errHandler.AddError(Resource1.Err_CannotUseInterruptsAndSpan, ErrorMgrKey.INPUT_INTERRUPT, Formal_ParamName_InterruptMode);
                    errHandler.AddError(Resource1.Err_CannotUseInterruptsAndSpan, ErrorMgrKey.MAPPING_SPANNING, Formal_ParamName_LayoutMode);
                }
            }
        }

        private void CheckDisplayAsBusRequiresHomogenous(ICyErrorHandler errHandler)
        {
            if (MappingDisplayAsBus && !IsHomogeneous)
            {
                errHandler.AddError(Resource1.Err_DisplayAsBusRequiresHomogenous, ErrorMgrKey.MAPPING_DISPLAY_AS_BUS, Formal_ParamName_DisplayAsBus);
            }
        }

        private void CheckCannotBeResistivePullAndVrefOut(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; i++)
            {
                if (CyOutputDriveLevel.VREF == m_pins[i].OutputDriveLevel)
                {
                    if (m_pins[i].GeneralDriveMode == CyDriveMode.RESISTIVE_PULL_UP ||
                        m_pins[i].GeneralDriveMode == CyDriveMode.RESISTIVE_PULL_DOWN ||
                        m_pins[i].GeneralDriveMode == CyDriveMode.RESISTIVE_PULL_UP_DOWN)
                    {
                        errHandler.AddError(Resource1.Err_P35_ResistivePullAndVrefOut,
                            ErrorMgrKey.GENERAL_DRIVE_MODE, Formal_ParamName_DriveMode);
                        errHandler.AddError(Resource1.Err_P35_ResistivePullAndVrefOut,
                            ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels);
                    }
                }
            }
        }

        private void CheckNotAnalogGen4(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; i++)
            {
                if ((m_pins[i].Type & CyPinType.ANALOG) == CyPinType.ANALOG)
                {
                    errHandler.AddError(String.Format(Resource1.Err_Gen4_Analog, i),
                        ErrorMgrKey.TYPE_IS_ANALOG, Formal_ParamName_PinTypes);
                }
            }
        }

        private void CheckPORM0S8(ICyErrorHandler errHandler)
        {
            if (PowerOnReset != CyPowerOnRestMode.UNSPECIFIED && PowerOnReset != CyPowerOnRestMode.HIZ_ANALOG)
            {
                errHandler.AddError(Resource1.Err_M0S8_Invalid_POR, ErrorMgrKey.POWER_ON_RESET, Formal_ParamName_PowerOnReset);
            }
        }

        private void CheckSlewRateSameIfContiguousM0S8(ICyErrorHandler errHandler)
        {
            if (PinCount > 1 && MappingContigious)
            {
                CyOutputSlewRate? slewRate = null;
                for (int i = 0; i < PinCount; i++)
                {
                    if ((m_pins[i].Type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_OUT)) > 0)
                    {
                        if (null == slewRate)
                            slewRate = m_pins[i].OutputSlewRate;
                        else if (slewRate != m_pins[i].OutputSlewRate)
                        {
                            errHandler.AddError(Resource1.Err_M0S8_SlewRateContiguousMismatch,
                                ErrorMgrKey.OUTPUT_SLEW_RATE, Formal_ParamName_SlewRate);
                            errHandler.AddError(Resource1.Err_M0S8_SlewRateContiguousMismatch,
                                ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_LayoutMode);
                            break;
                        }
                    }
                }
            }
        }

        private void CheckSIOHysteresisSameIfContiguous(ICyErrorHandler errHandler)
        {
            if (PinCount > 1 && MappingContigious && m_deviceSupport.IsPSoC4)
            {
                bool? hysteresis = null;
                for (int i = 0; i < PinCount; i++)
                {
                    if ((m_pins[i].Type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_IN)) > 0)
                    {
                        if (null == hysteresis)
                            hysteresis = m_pins[i].InputHysteresis;
                        else if (hysteresis != m_pins[i].InputHysteresis)
                        {
                            errHandler.AddError(Resource1.Err_HysteresisMismatchContiguous,
                                ErrorMgrKey.INPUT_HYSTERESIS, Formal_ParamName_HysteresisModes);
                            errHandler.AddError(Resource1.Err_HysteresisMismatchContiguous,
                                ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_LayoutMode);
                            break;
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Ensures that if a pin uses the OVT I2C output slew modes, the minimum supply voltage is specified 
        /// and the drive mode is set to open drain, drives low
        /// </summary>
        /// <param name="errHandler"></param>
        private void CheckI2CSlewRequirements(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < m_pins.Count; ++i)
            {
                PerPin pin = m_pins[i];
                if (pin.OutputSlewRate == CyOutputSlewRate.I2CHS_SLOW || pin.OutputSlewRate == CyOutputSlewRate.I2CHS_FAST 
                    || pin.OutputSlewRate == CyOutputSlewRate.I2CFM)
                {
                    if (String.IsNullOrEmpty(pin.GeneralMinimumSupply))
                    {
                        string error = String.Format(Resource1.Err_M0S8_SlewRateI2CNeedsMinimumSupply, i);
                        errHandler.AddError(error, ErrorMgrKey.OUTPUT_SLEW_RATE, Formal_ParamName_SlewRate);
                        errHandler.AddError(error, ErrorMgrKey.GENERAL_MINIMUM_SUPPLY, Formal_ParamName_IOVoltages);
                    }
                    if (pin.GeneralDriveMode != CyDriveMode.OPEN_DRAIN_DRIVE_LOW)
                    {
                        string error = String.Format(Resource1.Err_M0S8_SlewRateI2CNeedsOpenDrain, i);
                        errHandler.AddError(error, ErrorMgrKey.OUTPUT_SLEW_RATE, Formal_ParamName_SlewRate);
                        errHandler.AddError(error, ErrorMgrKey.GENERAL_DRIVE_MODE, Formal_ParamName_DriveMode);
                    }
                }
            }
        }

        /// <summary>
        /// Ensures that, if a pin uses an sio internal vref, the following rules are met:
        /// * The minimum supply voltage is set
        /// * The multiplier output is less than VDDIO - 400 mV
        /// </summary>
        /// <param name="errHandler"></param>
        private void CheckVrefMultiplierRequirements(ICyErrorHandler errHandler)
        {
            const double INTERNAL_VREF_VALUE = 1.2;
            for (int i = 0; i < m_pins.Count; ++i)
            {
                PerPin pin = m_pins[i];
                bool isOutput = (pin.Type & CyPinType.DIGITAL_OUT) != 0 || ((pin.Type & CyPinType.BIDIRECTIONAL) != 0 );
                bool isInput = (pin.Type & CyPinType.DIGITAL_IN) != 0 || ((pin.Type & CyPinType.BIDIRECTIONAL) != 0 );
                bool hasMinimumSupply = !String.IsNullOrEmpty(pin.GeneralMinimumSupply);
                double minimumSupply = 0;
                if(hasMinimumSupply)
                {
                    hasMinimumSupply = double.TryParse(pin.GeneralMinimumSupply, out minimumSupply);
                }
                if (isOutput && pin.OutputDriveLevel == CyOutputDriveLevel.VREF_INTERNAL)
                {
                    if (!hasMinimumSupply)
                    {
                        string error = string.Format(Resource1.Err_M0S8_VrefDriveLevelRequiresMinimumSupply, i);
                        errHandler.AddError(error, ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels);
                        errHandler.AddError(error, ErrorMgrKey.GENERAL_MINIMUM_SUPPLY, Formal_ParamName_IOVoltages);
                    }
                    else
                    {
                        double multiplierOutput = INTERNAL_VREF_VALUE * pin.OutputMultiplier;
                        double maxMultiplierOutput = minimumSupply - .4;
                        if (multiplierOutput > maxMultiplierOutput)
                        {
                            string error = string.Format(Resource1.Err_M0S8_MultiplierOutputTooHigh, i);
                            errHandler.AddError(error, ErrorMgrKey.OUTPUT_MULTIPLIER, Formal_ParamName_OutputMultiplier);
                            errHandler.AddError(error, ErrorMgrKey.GENERAL_MINIMUM_SUPPLY, Formal_ParamName_IOVoltages);
                        }
                    }
                }
                if (isInput &&
                   (pin.InputThreshold == CyInputThreshold.VREF_INTERNAL || pin.InputThreshold == CyInputThreshold.PT5_VREF_INTERNAL))
                {
                    if (!hasMinimumSupply)
                    {
                        string error = string.Format(Resource1.Err_M0S8_VrefThresholdRequiresMinimumSupply, i);
                        errHandler.AddError(error, ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                        errHandler.AddError(error, ErrorMgrKey.GENERAL_MINIMUM_SUPPLY, Formal_ParamName_IOVoltages);
                    }
                    else
                    {
                        double vrefVal = (pin.InputThreshold == CyInputThreshold.PT5_VREF_INTERNAL) ?
                            INTERNAL_VREF_VALUE * 0.5 : INTERNAL_VREF_VALUE;
                        double multiplierOutput = vrefVal * pin.InputMultiplier;
                        double maxMultiplierOutput = minimumSupply - .4;
                        if (multiplierOutput > maxMultiplierOutput)
                        {
                            string error = string.Format(Resource1.Err_M0S8_MultiplierOutputTooHigh, i);
                            errHandler.AddError(error, ErrorMgrKey.INPUT_MULTIPLIER, Formal_ParamName_InputMultiplier);
                            errHandler.AddError(error, ErrorMgrKey.GENERAL_MINIMUM_SUPPLY, Formal_ParamName_IOVoltages);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// If a pin is both an input and an output, ensure that:
        /// * Vref sources match if both input and output use them
        /// * Multipliers match, if both input and output use vref
        /// </summary>
        /// <param name="errHandler"></param>
        private void CheckSIOVrefSettingsMatch(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; ++i)
            {
                CyPinData.PerPin pin = Pins[i];
                if(((pin.Type & CyPinType.BIDIRECTIONAL) != 0) ||
                   (((pin.Type & CyPinType.DIGITAL_IN) != 0) && ((pin.Type & CyPinType.DIGITAL_OUT) != 0)))
                {
                    CyVrefSource inputSource = GetVrefSource(pin.InputThreshold);
                    CyVrefSource outputSource = GetVrefSource(pin.OutputDriveLevel);
                    if (inputSource != CyVrefSource.DONTCARE && outputSource != CyVrefSource.DONTCARE)
                    {
                        if (inputSource != outputSource)
                        {
                            string message = string.Format(Resource1.Err_M0S8_SioRefSelMustMatch, i);
                            errHandler.AddError(message, ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                            errHandler.AddError(message, ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels);
                        }

                        if (pin.InputMultiplier != pin.OutputMultiplier)
                        {
                            string message = string.Format(Resource1.Err_M0S8_MultipliersMustMatch, i);
                            errHandler.AddError(message, ErrorMgrKey.INPUT_MULTIPLIER, Formal_ParamName_InputMultiplier);
                            errHandler.AddError(message, ErrorMgrKey.OUTPUT_MULTIPLIER, Formal_ParamName_OutputMultiplier);
                        }
                    }
                }
                   
            }
        }

        private static CyVrefSource GetVrefSource(CyInputThreshold threshold)
        {
            switch (threshold)
            {
                case CyInputThreshold.PT5_VREF:
                case CyInputThreshold.VREF:
                    return CyVrefSource.ROUTED;
                case CyInputThreshold.PT5_VREF_INTERNAL:
                case CyInputThreshold.VREF_INTERNAL:
                    return CyVrefSource.INTERNAL;
                default:
                    return CyVrefSource.DONTCARE;
            }
        }

        private static CyVrefSource GetVrefSource(CyOutputDriveLevel driveLevel)
        {
            switch (driveLevel)
            {
                case CyOutputDriveLevel.VREF:
                    return CyVrefSource.ROUTED;
                case CyOutputDriveLevel.VREF_INTERNAL:
                    return CyVrefSource.INTERNAL;
                default:
                    return CyVrefSource.DONTCARE;
            }
        }

        private void CheckMaxCountIfNotSpanning(ICyErrorHandler errHandler)
        {
            if (PinCount > PINS_PER_PORT && !MappingSpanning)
            {
                errHandler.AddError(Resource1.Err_PinCountRequiresSpanning, ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_LayoutMode);
            }
        }

        private void CheckInputThresholdSameIfContiguous(ICyErrorHandler errHandler)
        {
            if (PinCount > 1 && MappingContigious)
            {
                CyInputThreshold? threshold = null;
                bool err = false;
                for (int i = 0; i < PinCount; i++)
                {
                    if ((m_pins[i].Type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_IN)) > 0)
                    {
                        if (null == threshold)
                            threshold = m_pins[i].InputThreshold;
                        else if (threshold == CyInputThreshold.CMOS &&
                            (m_pins[i].InputThreshold != CyInputThreshold.CMOS &&
                            m_pins[i].InputThreshold != CyInputThreshold.CMOS_LVTTL))
                        {
                            err = true;
                            break;
                        }
                        else if (threshold == CyInputThreshold.LVTTL &&
                            (m_pins[i].InputThreshold != CyInputThreshold.LVTTL &&
                            m_pins[i].InputThreshold != CyInputThreshold.CMOS_LVTTL))
                        {
                            err = true;
                            break;
                        }
                        else if (threshold == CyInputThreshold.CMOS_LVTTL &&
                            (m_pins[i].InputThreshold != CyInputThreshold.LVTTL &&
                            m_pins[i].InputThreshold != CyInputThreshold.CMOS_LVTTL &&
                            m_pins[i].InputThreshold != CyInputThreshold.CMOS))
                        {
                            err = true;
                            break;
                        }
                    }
                }
                if (err)
                {
                    errHandler.AddError(Resource1.Err_ThresholdContiguousMismatch,
                        ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_LayoutMode);
                    errHandler.AddError(Resource1.Err_ThresholdContiguousMismatch,
                        ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                }
            }
        }

        private bool SIOVrefSourcesCompatible(CyVrefSource source0, CyVrefSource source1)
        {
            return source0 != CyVrefSource.DONTCARE ||
                   source1 != CyVrefSource.DONTCARE ||
                   source0 == source1;
        }

        private void CheckSIOPairSettingsMatch(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount - 1; i++)
            {
                if (m_pins[i].SIOPairID == 0)
                {
                    PerPin pin1 = m_pins[i];
                    PerPin pin2 = m_pins[i + 1];
                    if(!SIOVrefSourcesCompatible(pin1.VRefSource, pin2.VRefSource))
                    {
                            errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i),
                                ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                            errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i),
                                ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels);
                            errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i + 1),
                                ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                            errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i + 1),
                                ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels);
                    }

                    if (((pin1.Type & pin2.Type) & CyPinType.DIGITAL_IN) != 0)
                    {
                        if (pin1.InputThreshold != pin2.InputThreshold)
                        {
                            errHandler.AddError(String.Format(Resource1.Err_SIOPairInputsDontMatch, i),
                                ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                            errHandler.AddError(String.Format(Resource1.Err_SIOPairInputsDontMatch, i + 1),
                                ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                        }
                        if (m_deviceSupport.IsPSoC4)
                        {
                            if (pin1.InputHysteresis != pin2.InputHysteresis)
                            {
                                errHandler.AddError(String.Format(Resource1.Err_SIOPairHysteresisDoesntMatch, i),
                                    ErrorMgrKey.INPUT_HYSTERESIS, Formal_ParamName_HysteresisModes);
                                errHandler.AddError(String.Format(Resource1.Err_SIOPairHysteresisDoesntMatch, i + 1),
                                    ErrorMgrKey.INPUT_HYSTERESIS, Formal_ParamName_HysteresisModes);
                            }
                        }
                    }
                    else if (((pin1.Type & pin2.Type) & CyPinType.DIGITAL_OUT) != 0)
                    {
                        if (pin1.OutputDriveLevel != pin2.OutputDriveLevel)
                        {
                            errHandler.AddError(String.Format(Resource1.Err_SIOPairOutputsDontMatch, i),
                                ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels);
                            errHandler.AddError(String.Format(Resource1.Err_SIOPairOutputsDontMatch, i + 1),
                                ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels);
                        }
                    }
                    if (pin1.MultiplierIndex != pin2.MultiplierIndex)
                    {
                        errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i),
                            ErrorMgrKey.OUTPUT_MULTIPLIER, Formal_ParamName_OutputMultiplier);
                        errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i),
                            ErrorMgrKey.INPUT_MULTIPLIER, Formal_ParamName_InputMultiplier);
                        errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i + 1),
                            ErrorMgrKey.OUTPUT_MULTIPLIER, Formal_ParamName_OutputMultiplier);
                        errHandler.AddError(String.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i + 1),
                            ErrorMgrKey.INPUT_MULTIPLIER, Formal_ParamName_InputMultiplier);
                    }
                }
            }
        }

        private void CheckCannotBeContiguousAndAnalog(ICyErrorHandler errHandler)
        {
            if (PinCount > 1 && MappingContigious)
            {
                for (int i = 0; i < PinCount; i++)
                {
                    if ((m_pins[i].Type & CyPinType.ANALOG) == CyPinType.ANALOG)
                    {
                        errHandler.AddError(String.Format(Resource1.Err_CannotBeContiguousAndAnalogMsg1, i),
                            ErrorMgrKey.TYPE_IS_ANALOG, Formal_ParamName_PinTypes);
                        errHandler.AddError(String.Format(Resource1.Err_CannotBeContiguousAndAnalogMsg2, i),
                            ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_LayoutMode);
                    }
                }
            }
        }

        private void CheckSIOLayoutRestrictions(ICyErrorHandler errHandler)
        {
            //If Contiguous, cannot have more than 2 SIO singles in a row and cannot have more than 1 if next
            //to an SIO group.
            if (PinCount > 1 && MappingContigious)
            {
                bool foundPair = false;
                int runOfSingleSIOs = 0;
                for (int i = 0; i < PinCount; i++)
                {
                    if (m_pins[i].SIOPairID >= 0)
                        foundPair = true;
                    else if (m_pins[i].RequiresSIO())
                        runOfSingleSIOs++;
                    else
                        foundPair = false;

                    if (runOfSingleSIOs == 2 && foundPair)
                    {
                        errHandler.AddError(Resource1.Err_TooManySingleSIONextToSIOPair,
                            ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_SIOGroups);
                        errHandler.AddError(Resource1.Err_TooManySingleSIONextToSIOPair,
                            ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_LayoutMode);
                    }
                    if (runOfSingleSIOs > 2)
                    {
                        errHandler.AddError(Resource1.Err_TooManySingleSIOInARow,
                            ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_SIOGroups);
                        errHandler.AddError(Resource1.Err_TooManySingleSIOInARow,
                            ErrorMgrKey.MAPPING_CONTIGIOUS, Formal_ParamName_SIOGroups);
                        break;
                    }
                }
            }
        }

        private void CheckCannotEnableInputBufferIfAnalogHiZ(ICyErrorHandler errHandler)
        {
            //Cannot set InputBufferEnabled to true if DriveMode is Analog HiZ (onnly check if pin is input).
            for (int i = 0; i < PinCount; i++)
            {
                if (m_pins[i].GeneralDriveMode == CyDriveMode.HIGH_IMPEDANCE_ANALOG &&
                    m_pins[i].InputBufferEnabled &&
                    ((m_pins[i].Type & (CyPinType.DIGITAL_IN | CyPinType.BIDIRECTIONAL)) > 0))
                {
                    errHandler.AddError(String.Format(Resource1.Err_CannotEnableIBufAndAnalogHiZ, i),
                        ErrorMgrKey.GENERAL_DRIVE_MODE, Formal_ParamName_DriveMode);
                    errHandler.AddError(String.Format(Resource1.Err_CannotEnableIBufAndAnalogHiZ, i),
                        ErrorMgrKey.INPUT_BUFFER_ENABLED, Formal_ParamName_InputBuffersEnabled);
                }
            }
        }

        private void CheckCannotUseAnalogIfSIO(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; i++)
            {
                if (((m_pins[i].Type & CyPinType.ANALOG) == CyPinType.ANALOG) && m_pins[i].RequiresSIO())
                {
                    List<Touple<ErrorMgrKey, string>> errors = new List<Touple<ErrorMgrKey, string>>();
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.TYPE_IS_ANALOG, Formal_ParamName_PinTypes));

                    if (m_pins[i].GeneralHotSwap)
                        errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.INPUT_HOT_SWAP, Formal_ParamName_HotSwaps));
                    if (m_pins[i].OutputDriveLevel == CyOutputDriveLevel.VREF)
                        errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.OUTPUT_DRIVE_LEVEL, Formal_ParamName_OutputDriveLevels));
                    if (m_pins[i].OutputCurrent == CyOutputCurrent.SOURCE_4MA_SINK_25MA)
                        errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.OUTPUT_CURRENT, Formal_ParamName_DriveCurrents));
                    if (m_pins[i].InputThreshold != CyInputThreshold.CMOS &&
                        m_pins[i].InputThreshold != CyInputThreshold.CMOS_LVTTL &&
                        m_pins[i].InputThreshold != CyInputThreshold.LVTTL)
                    {
                        errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels));
                    }

                    if (errors.Count > 1)
                    {
                        string msg = String.Format(Resource1.Err_CannotUseAnalogAndSIO, i);
                        foreach (Touple<ErrorMgrKey, string> err in errors)
                            errHandler.AddError(msg, err.First, err.Second);
                    }
                }
            }
        }

        private void CheckModesRequiringPortAdapter(ICyErrorHandler errHandler)
        {
            // HSIOM-routed inputs only reliably work in high-z mode. So disallow other modes for hw routed 
            // inputs on parts without a port adapter
            if (!m_deviceSupport.HasPortAdapter && m_deviceSupport.IsPSoC4)
            {
                for(int i = 0; i < m_pins.Count; ++i)
                {
                    PerPin pin = m_pins[i];
                    // We are looking for pins that are a.)an input, b.)hw routed and 
                    // c.)not an output of any kind (standard output, output w/oe, bidir)
                    bool isHwInputOnly = ((pin.Type & CyPinType.DIGITAL_IN) != 0) &&
                                         ((pin.Type & CyPinType.BIDIRECTIONAL) == 0) &&
                                         ((pin.Type & CyPinType.DIGITAL_OUT) == 0) &&
                                         ((pin.Type & CyPinType.OE) == 0) &&
                                          (pin.TypeIsDigitalInputHw);
                    if (isHwInputOnly)
                    {
                        if (pin.GeneralDriveMode != CyDriveMode.HIGH_IMPEDANCE_DIGITAL &&
                            pin.GeneralDriveMode != CyDriveMode.HIGH_IMPEDANCE_ANALOG)
                        {
                            string error = String.Format(Resource1.Err_DriveModeRequiresPA, i);
                            errHandler.AddError(error, ErrorMgrKey.GENERAL_DRIVE_MODE, Formal_ParamName_DriveMode);
                        }
                    }
                }
            }

        }

        private delegate List<CyErrorCause> GetCauses(PerPin pin);
        private void CheckCannotUsePinTypeOnDevice(ICyErrorHandler errHandler, string pinType, GetCauses getCauses)
        {
            for (int i = 0; i < m_pins.Count; ++i)
            {
                List<CyErrorCause> causes = getCauses(m_pins[i]);
                foreach (CyErrorCause cause in causes)
                {
                    // Third entry is friendly name, not used here
                    string error = String.Format(Resource1.Err_CannotUsePinTypeonDevice, i, pinType);
                    errHandler.AddError(error, cause.Key, cause.FormalParam);
                }
            }
        }

        private void CheckCannotRequireSIOAndOVT(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < m_pins.Count; ++i)
            {
                PerPin pin = m_pins[i];
                List<CyErrorCause> ovtCauses = pin.GetOVTCauses();
                List<CyErrorCause> sioCauses = pin.GetSIOCauses();
                if (ovtCauses.Count > 0 && sioCauses.Count > 0)
                {
                    // Flag each field which requires OVT, mentioning the first field which requires SIO. 
                    // Do the same for each field which requires SIO
                    foreach (CyErrorCause cause in ovtCauses)
                    {
                        // Only look at the first SIO cause to avoid an overwhelming cascade of errors
                        string error = String.Format(Resource1.Err_OvtAndSioFeaturesUsed, i, "OVT", sioCauses[0].FriendlyName, "SIO");
                        errHandler.AddError(error, cause.Key, cause.FormalParam);
                    }
                    foreach (CyErrorCause cause in sioCauses)
                    {
                        // Only look at the first OVT cause to avoid an overwhelming cascade of errors
                        string error = String.Format(Resource1.Err_OvtAndSioFeaturesUsed, i, "SIO", ovtCauses[0].FriendlyName, "OVT");
                        errHandler.AddError(error, cause.Key, cause.FormalParam);
                    }
                }
            }
        }

        private void CheckCannotUsePAOnDevice(ICyErrorHandler errHandler)
        {
            List<Touple<ErrorMgrKey, string>> errors = new List<Touple<ErrorMgrKey, string>>();

            if (ClockInput != CyPinClock.HFCLK)
            {
                if (ClockInput == CyPinClock.EXTERNAL || ClockInput == CyPinClock.EXTERNAL_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT, Formal_ParamName_ShowInClkTerm));
                else if (ClockInput == CyPinClock.PIN || ClockInput == CyPinClock.PIN_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT, Formal_ParamName_UsePaInClk));
                else
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT, Formal_ParamName_InvertInClock));
            }
            if (ClockInputEnable != CyPinClockEnRst.NONE)
            {
                if (ClockInputEnable == CyPinClockEnRst.EXTERNAL || ClockInputEnable == CyPinClockEnRst.EXTERNAL_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT_ENABLE, Formal_ParamName_ShowInClkEnTerm));
                else if (ClockInputEnable == CyPinClockEnRst.PIN || ClockInputEnable == CyPinClockEnRst.PIN_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT_ENABLE, Formal_ParamName_UsePaInClkEn));
                else
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT_ENABLE, Formal_ParamName_InvertInClockEn));
            }
            if (ClockInputReset != CyPinClockEnRst.NONE)
            {
                if (ClockInputReset == CyPinClockEnRst.EXTERNAL || ClockInputReset == CyPinClockEnRst.EXTERNAL_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT_RESET, Formal_ParamName_ShowInRstTerm));
                else if (ClockInputReset == CyPinClockEnRst.PIN || ClockInputReset == CyPinClockEnRst.PIN_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT_RESET, Formal_ParamName_UsePaInRst));
                else
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_INPUT_RESET, Formal_ParamName_InvertInReset));
            }
            if (ClockOutput != CyPinClock.HFCLK)
            {
                if (ClockOutput == CyPinClock.EXTERNAL || ClockOutput == CyPinClock.EXTERNAL_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT, Formal_ParamName_ShowOutClkTerm));
                else if (ClockOutput == CyPinClock.PIN || ClockOutput == CyPinClock.PIN_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT, Formal_ParamName_UsePaOutClk));
                else
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT, Formal_ParamName_InvertOutClock));
            }
            if (ClockOutputEnable != CyPinClockEnRst.NONE)
            {
                if (ClockOutputEnable == CyPinClockEnRst.EXTERNAL || ClockOutputEnable == CyPinClockEnRst.EXTERNAL_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_ENABLE, Formal_ParamName_ShowOutClkEnTerm));
                else if (ClockOutputEnable == CyPinClockEnRst.PIN || ClockOutputEnable == CyPinClockEnRst.PIN_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_ENABLE, Formal_ParamName_UsePaOutClkEn));
                else
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_ENABLE, Formal_ParamName_InvertOutClockEn));
            }
            if (ClockOutputReset != CyPinClockEnRst.NONE)
            {
                if (ClockOutputReset == CyPinClockEnRst.EXTERNAL || ClockOutputReset == CyPinClockEnRst.EXTERNAL_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_RESET, Formal_ParamName_ShowOutRstTerm));
                else if (ClockOutputReset == CyPinClockEnRst.PIN || ClockOutputReset == CyPinClockEnRst.PIN_INV)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_RESET, Formal_ParamName_UsePaOutRst));
                else
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_RESET, Formal_ParamName_InvertOutReset));
            }
            if (ClockOutputResetEnable)
                errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_ENABLE, Formal_ParamName_OutputResetEnabled));
            if (ClockOutputOeResetEnable)
                errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.CLOCK_OUTPUT_RESET_ENABLE, Formal_ParamName_OEResetEnabled));

            foreach (PerPin pin in m_pins)
            {
                if(pin.OutputMode != CyOutputMode.TRANSPARENT && pin.OutputMode != CyOutputMode.SINGLE_SYNC)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.OUTPUT_MODE, Formal_ParamName_OutputModes));
                if(pin.OutputEnableSynchronized)
                    errors.Add(new Touple<ErrorMgrKey, string>(ErrorMgrKey.OUTPUT_ENABLE_SYNCHRONIZED, Formal_ParamName_OESyncs));
            }

            foreach (Touple<ErrorMgrKey, string> err in errors)
                errHandler.AddError(Resource1.Err_CannotUsePAonDevice, err.First, err.Second);
        }

        private void CheckCannotUseGPIOv2Features(ICyErrorHandler errHandler)
        {
            if (m_deviceSupport.GPIOVersion < 2)
            {
                for(int i = 0; i < m_pins.Count; ++i)
                {
                    if (m_pins[i].InputThreshold == CyInputThreshold.CMOS_1PT8V)
                    {
                        string err = String.Format(Resource1.Err_NotSupportedOnOldGPIO, i);
                        errHandler.AddError(err, ErrorMgrKey.INPUT_THRESHOLD, Formal_ParamName_ThresholdLevels);
                    }
                }
            }
        }

        private void CheckCannotUseVrefMultipliers(ICyErrorHandler errHandler)
        {
            if (m_deviceSupport.IsPSoC3 || m_deviceSupport.IsPSoC5)
            {
                for(int i = 0; i < m_pins.Count; ++i)
                {
                    CyInputThreshold threshold = m_pins[i].InputThreshold;
                    if ((threshold == CyInputThreshold.VREF || threshold == CyInputThreshold.PT5_VREF) &&
                        m_pins[i].InputMultiplier != CyPinData.VrefMultiplierValues[0])
                    {
                        string err = String.Format(Resource1.Err_P35VrefMultipliersNotSupported, i);
                        errHandler.AddError(err, ErrorMgrKey.INPUT_MULTIPLIER, Formal_ParamName_InputMultiplier);
                    }
                    CyOutputDriveLevel driveLevel = m_pins[i].OutputDriveLevel;
                    if (driveLevel == CyOutputDriveLevel.VREF && m_pins[i].OutputMultiplier != CyPinData.VrefMultiplierValues[0])
                    {
                        string err = String.Format(Resource1.Err_P35VrefMultipliersNotSupported, i);
                        errHandler.AddError(err, ErrorMgrKey.OUTPUT_MULTIPLIER, Formal_ParamName_OutputMultiplier);
                    }
                }
            }
        }

        private void CheckAtLeastOneTypeSelected(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < Pins.Count; ++i)
            {
                if(Pins[i].Type == CyPinType.NONE)
                {
                    string err = String.Format(Resource1.Err_CannotUncheckAllTypes, i);
                    errHandler.AddError(err, ErrorMgrKey.GENERAL_TYPE, Formal_ParamName_PinTypes);
                }
            }
        }
        #endregion
        #endregion

        public bool IsHomogeneous
        {
            get
            {
                for (int i = 0; i < PinCount; i++)
                {
                    if (m_pins[0].Type != m_pins[i].Type ||
                        m_pins[0].TypeIsDigitalInputHw != m_pins[i].TypeIsDigitalInputHw ||
                        m_pins[0].TypeIsDigitalOutputHw != m_pins[i].TypeIsDigitalOutputHw ||
                        m_pins[0].TypeShowExternalTerm != m_pins[i].TypeShowExternalTerm ||
                        m_pins[0].RequiresOVT() != m_pins[i].RequiresOVT() ||
                        m_pins[0].RequiresSIO() != m_pins[i].RequiresSIO())
                        return false;
                }
                return true;
            }
        }
    }
}
