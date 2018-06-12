/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Diagnostics.CodeAnalysis;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    // The formal parameters are used for the UI.
    // No data here, just names and to/from conversion functions for clarity
    internal static class Formal
    {
        internal static class Param
        {
            internal const string Builtin_InstName = "INSTANCE_NAME";

            // Global values
            internal const string NumPins = "NumPins";
            internal const string DisplayAsBus = "DisplayAsBus";
            // Per pin values
            internal const string SIOGroups = "SIOGroups";
            internal const string PinAliases = "PinAliases";
            internal const string PinTypes = "PinTypes";
            internal const string DisplayInputHWConnections = "DisplayInputHWConnections";
            internal const string DisplayOutputHWConnections = "DisplayOutputHWConnections";
            internal const string DisplayOutputEnable = "DisplayOutputEnable";
            internal const string ShowAnnotationTerm = "ShowAnnotationTerm";
            internal const string MaxFrequency = "MaxFrequency";
            internal const string I2CMode = "I2CModes";
            internal const string DriveMode = "DriveModes";
            internal const string InitialDriveStates = "InitialDriveStates";
            internal const string IOVoltages = "IOVoltages";
            internal const string InputMultiplier = "InputMultipliers";
            internal const string InterruptMode = "InterruptModes";
            internal const string HotSwaps = "HotSwaps";
            internal const string InputBuffersEnabled = "InputBuffersEnabled";
            internal const string InputSyncMode = "InputSyncMode";
            internal const string ThresholdLevels = "ThresholdLevels";
            internal const string SlewRate = "SlewRates";
            internal const string OutputDriveLevels = "OutputDriveLevels";
            internal const string OutputMultiplier = "OutputMultipliers";
            internal const string DriveStrength = "DriveStrength";
            internal const string OutputCurrentCaps = "OutputCurrentCaps";
            internal const string OutputSyncMode = "OutputSyncMode";
            internal const string OESyncs = "OESyncs";
        }

        #region Error handling

        internal enum ErrorKey
        {
            INST_NAME, //Builtin_InstName
            NUM_PINS, //NumPins
            DISPLAY_AS_BUS, //DisplayAsBus
            //SioGroups
            PIN_ALIAS, //PinAliases
            TYPE_IS_ANALOG, //PinTypes
            TYPE_IS_DIGITAL_IN, //PinTypes
            TYPE_IS_DIGITAL_IN_HW, //PinTypes
            TYPE_IS_DIGITAL_OUT, //PinTypes
            TYPE_IS_DIGITAL_OUT_HW, //PinTypes
            TYPE_IS_DIGITAL_OUT_OE, //PinTypes
            TYPE_IS_BIDIRECTIONAL, //PinTypes
            TYPE_SHOW_EXTERNAL_TERM, //PinTypes
            GENERAL_TYPE, //PinTypes
            //DisplayInputHWConnections
            //DisplayOutputHWConnections
            //DisplayOutputEnable
            //ShowAnnotationTerm
            GENERAL_MAX_FREQUENCY, //MaxFrequency
            GENERAL_DRIVE_MODE, //DriveMode
            GENERAL_INITIAL_STATE, //InitialDriveStates
            GENERAL_MINIMUM_SUPPLY, //IOVoltages

            INPUT_MULTIPLIER, //InputMultiplier
            INPUT_INTERRUPT, //InterruptMode
            INPUT_HOT_SWAP, //HotSwaps
            //InputBuffersEnabled
            INPUT_SYNC_MODE, //InputSyncMode
            INPUT_THRESHOLD, //ThresholdLevels

            OUTPUT_SLEW_RATE, //SlewRate
            OUTPUT_DRIVE_LEVEL, //OutputDriveLevels
            OUTPUT_MULTIPLIER, //OutputMultiplier
            OUTPUT_DRIVE_STRENGTH, //DriveStrength
            OUTPUT_CURR_CAP, //OutputCurrentCaps
            OUTPUT_SYNC_MODE, //OutputSyncMode
            OUTPUT_ENABLE_SYNCHRONIZED  //OeSyncs
        }

        private static Dictionary<ErrorKey, string> m_keyParam = new Dictionary<ErrorKey, string>()
        {
            { ErrorKey.INST_NAME, Param.Builtin_InstName },
            { ErrorKey.NUM_PINS, Param.NumPins },
            { ErrorKey.DISPLAY_AS_BUS, Param.DisplayAsBus },
            { ErrorKey.PIN_ALIAS, Param.PinAliases },

            { ErrorKey.TYPE_IS_ANALOG, Param.PinTypes },
            { ErrorKey.TYPE_IS_DIGITAL_IN, Param.PinTypes },
            { ErrorKey.TYPE_IS_DIGITAL_IN_HW, Param.PinTypes },
            { ErrorKey.TYPE_IS_DIGITAL_OUT, Param.PinTypes },
            { ErrorKey.TYPE_IS_DIGITAL_OUT_HW, Param.PinTypes },
            { ErrorKey.TYPE_IS_DIGITAL_OUT_OE, Param.PinTypes },
            { ErrorKey.TYPE_IS_BIDIRECTIONAL, Param.PinTypes },
            { ErrorKey.TYPE_SHOW_EXTERNAL_TERM, Param.DisplayOutputEnable },

            { ErrorKey.GENERAL_DRIVE_MODE, Param.DriveMode },
            { ErrorKey.GENERAL_INITIAL_STATE, Param.InitialDriveStates },
            { ErrorKey.GENERAL_MINIMUM_SUPPLY, Param.IOVoltages },
            { ErrorKey.GENERAL_TYPE, Param.PinTypes },
            { ErrorKey.GENERAL_MAX_FREQUENCY, Param.MaxFrequency },

            { ErrorKey.INPUT_THRESHOLD, Param.ThresholdLevels },
            { ErrorKey.INPUT_INTERRUPT, Param.InterruptMode },
            { ErrorKey.INPUT_HOT_SWAP, Param.HotSwaps },
            { ErrorKey.INPUT_SYNC_MODE, Param.InputSyncMode },
            { ErrorKey.INPUT_MULTIPLIER, Param.InputMultiplier },

            { ErrorKey.OUTPUT_SLEW_RATE, Param.SlewRate},
            { ErrorKey.OUTPUT_DRIVE_LEVEL, Param.OutputDriveLevels },
            { ErrorKey.OUTPUT_MULTIPLIER, Param.OutputMultiplier },
            { ErrorKey.OUTPUT_CURR_CAP, Param.OutputCurrentCaps },
            { ErrorKey.OUTPUT_DRIVE_STRENGTH, Param.DriveStrength },
            { ErrorKey.OUTPUT_SYNC_MODE, Param.OutputSyncMode },
            { ErrorKey.OUTPUT_ENABLE_SYNCHRONIZED, Param.OESyncs }
        };

        private static Dictionary<string, string> m_paramFriendlyName = new Dictionary<string, string>()
        {
            { Param.MaxFrequency, Resource1.MaxFrequency },
            { Param.ThresholdLevels, Resource1.ThresholdLevels },
            { Param.HotSwaps, Resource1.HotSwaps },
            { Param.OutputDriveLevels, Resource1.OutputDriveLevels },
            { Param.OutputCurrentCaps, Resource1.OutputCurrentCaps }
        };

        internal static IEnumerable<ErrorKey> Keys { get { return m_keyParam.Keys; } }
        internal static string KeyParam(ErrorKey key)
        {
            return m_keyParam[key];
        }

        internal static string KeyFriendlyName(ErrorKey key)
        {
            return m_paramFriendlyName[KeyParam(key)];
        }

        #endregion

        #region Boolean values
        internal const string True = "1";
        internal const string False = "0";
        internal const string Enabled = True;
        internal const string Disabled = False;
        internal const string High = True;
        internal const string Low = False;
        internal const string Grouped = True;
        internal const string Not_grouped = False;
        internal static string AsString(bool b) { return b ? True : False; }
        #endregion

        internal static class PinTypes
        {
            internal const string None = "X";
            internal const string Analog = "A";
            internal const string Bidirectional = "B";
            internal const string DigIn = "I";
            internal const string DigOut = "O";
            internal const string OE = "E";
            internal const string Default = DigIn;
        }

        internal const string SIOGroup_Default = Not_grouped;
        internal const string Display_Default = True;
        internal const string OESyncs_Default = False;
        internal const string HotSwap_Default = False;
        internal const string IOVoltage_Default = "None";
        internal const string IOVoltage_Multiple = "Multiple";
        internal const string ShowAnnotDefault = False;

        internal static class VrefMultipliers
        {
            internal const int Index_Default = 0;
            internal const double Default = 1.0; // Multiplier for non-vref based modes

            private static readonly double[] m_vref = 
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

            internal static IEnumerable<double> Values { get { return m_vref; } }

            internal static string AsString(double val)
            {
                int index = Array.IndexOf(m_vref, val);
                if (index < 0) index = Index_Default;
                return index.ToString();
            }

            internal static int IndexOf(double val)
            {
                int index = Array.IndexOf(m_vref, val);
                Debug.Assert(index >= 0, "Could not find multiplier");
                return index;
            }

            internal static double At(int index)
            {
                return m_vref[index];
            }

            internal static double Vref(string val)
            {
                int index;
                if (int.TryParse(val, out index))
                    return m_vref[index];

                return m_vref[Index_Default];
            }
        }

        internal static class VddioMultipliers
        {
            internal const int Index_Default = 0;
            internal const double Default = 1.0; // Multiplier for non-vddio based modes

            // Not stored in a separate formal parameter, Vddio values index this array rather than VrefMultiplierValues
            private static readonly double[] m_vddio = 
            {
                0.4,
                0.5
            };

            internal static IEnumerable<double> Values { get { return m_vddio; } }

            internal static string AsString(double val)
            {
                int index = Array.IndexOf(m_vddio, val);
                if (index < 0) index = Index_Default;
                return index.ToString();
            }

            internal static int IndexOf(double val)
            {
                int index = Array.IndexOf(m_vddio, val);
                Debug.Assert(index >= 0, "Could not find multiplier");
                return index;
            }

            internal static double At(int index)
            {
                return m_vddio[index];
            }

            internal static double Vddio(string val)
            {
                int index;
                if (int.TryParse(val, out index))
                    return m_vddio[index];

                return m_vddio[Index_Default];
            }
        }

        #region Conversion functions

        /// <summary>
        /// Each enum value should have an associated string value. These values are not localized.
        /// </summary>
        /// <typeparam name="T">An enum type.</typeparam>
        /// <param name="item">An enum value.</param>
        /// <returns>The string value.</returns>
        private static string GetEnumValueAsString<T>(T item)
        {
            Debug.Assert(typeof(T).BaseType == typeof(Enum));

            FieldInfo fi = typeof(T).GetField(item.ToString());

            CyValueAttribute[] attributes =
                (CyValueAttribute[])fi.GetCustomAttributes(typeof(CyValueAttribute), false);

            return (attributes.Length > 0) ? attributes[0].Value : item.ToString();
        }

        /// <summary>
        /// Each enum value should have an associated string value. These values are not localized.
        /// </summary>
        /// <typeparam name="T">An enum type.</typeparam>
        /// <param name="item">An enum string.</param>
        /// <returns>The enum value.</returns>
        private static T GetEnumStringAsValue<T>(string item)
        {
            Debug.Assert(typeof(T).IsEnum);
            foreach (var field in typeof(T).GetFields())
            {
                var attribute = Attribute.GetCustomAttribute(field, typeof(CyValueAttribute)) as CyValueAttribute;
                if (null != attribute)
                {
                    if (attribute.Value == item)
                        return (T)field.GetValue(null);
                }
                else if (field.Name == item)
                    return (T)field.GetValue(null);
            }
            Debug.Fail(string.Format("Enum value not found ({0}).", item));
            return default(T);
        }

        internal static string AsString<T>(T value)
        {
            return GetEnumValueAsString(value);
        }

        [ExcludeFromCodeCoverage]
        internal static string PrettyString<T>(T value)
        {
            Debug.Assert(typeof(T).BaseType == typeof(Enum));

            FieldInfo fi = typeof(T).GetField(value.ToString());

            CyValueAttribute[] attributes =
                (CyValueAttribute[])fi.GetCustomAttributes(typeof(CyValueAttribute), false);

            return (attributes.Length > 0) ? (attributes[0].PrettyName ?? value.ToString()) : value.ToString();
        }

        internal static T GetValue<T>(string value)
        {
            return GetEnumStringAsValue<T>(value);
        }

        internal static string AsString(CyPinType pinType)
        {
            string val = string.Empty;
            if (pinType.Is(CyPinType.Bidirectional))
                val += PinTypes.Bidirectional;
            if (pinType.Is(CyPinType.Digital_In))
                val += PinTypes.DigIn;
            if (pinType.Is(CyPinType.Digital_Out))
                val += PinTypes.DigOut;
            if (pinType.Is(CyPinType.OE))
                val += PinTypes.OE;
            if (pinType.Is(CyPinType.Analog))
                val += PinTypes.Analog;
            if (string.IsNullOrEmpty(val))
                val = PinTypes.None;
            return val;
        }

        internal static CyPinType GetPinType(string pinType)
        {
            CyPinType result = CyPinType.None;

            #if !V0_5_PHASEDOUT
            if (pinType == "ANALOG")
                return CyPinType.Analog;
            if (pinType == "DIG_IN")
                return CyPinType.Digital_In;
            if (pinType == "DIG_OUT")
                return CyPinType.Digital_Out;
            if (pinType == "DIG_INOUT")
                return CyPinType.Bidirectional;
            #endif

            if (pinType.Contains(PinTypes.None))
                return CyPinType.None;

            if (pinType.Contains(PinTypes.Bidirectional))
                result |= CyPinType.Bidirectional;
            if (pinType.Contains(PinTypes.DigIn))
                result |= CyPinType.Digital_In;
            if (pinType.Contains(PinTypes.DigOut))
                result |= CyPinType.Digital_Out;
            if (pinType.Contains(PinTypes.OE))
                result |= CyPinType.OE;
            if (pinType.Contains(PinTypes.Analog))
                result |= CyPinType.Analog;
            if (result == CyPinType.None)
            {
                Debug.Fail("Unsupported pin type");
                return CyPinType.Digital_In;
            }
            return result;
        }

        internal static CySyncMode GetOutputSyncMode(string mode)
        {
            #if !V0_5_PHASEDOUT
            if (mode == "SINGLE_SYNC")
                return CySyncMode.Single;
            if (mode == "NO_SYNC")
                return CySyncMode.Transparent;
            #endif

            if (AsString(CySyncMode.Single) == mode)
                return CySyncMode.Single;
            return CySyncMode.Transparent;
        }

        #endregion
    }
}
