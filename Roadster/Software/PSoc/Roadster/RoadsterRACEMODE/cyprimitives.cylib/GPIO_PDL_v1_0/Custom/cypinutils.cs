/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Windows.Forms;

using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    // The Warp parameters represent the data in Verilog.
    internal static class Warp
    {
        internal static class Param
        {
            // These constant values match those in the primitive's XML file and should not be changed arbitrarily

            internal const string Id = "id";
            internal const string Width = "width";
            internal const string SIOGroupCnt = "sio_grp_cnt";
            // Per pin
            internal const string DriveMode = "drive_mode";
            internal const string InputBuffersEnabled = "ibuf_enabled";
            internal const string InitialDriveStates = "init_dr_st";
            internal const string InputSyncMode = "input_sync";
            internal const string InterruptMode = "intr_mode";
            internal const string IOVoltages = "io_voltage";
            internal const string OutConn = "output_conn";
            internal const string OeConn = "oe_conn";
            internal const string OESyncs = "oe_sync";
            internal const string OutputSyncMode = "output_sync";
            internal const string DriveStrength = "drive_strength";
            internal const string MaxFrequency = "max_frequency";
            internal const string I2CMode = "i2c_mode";
            internal const string OutputCurrentCap = "output_current_cap";
            internal const string PinAliases = "pin_aliases";
            internal const string PinMode = "pin_mode";
            internal const string SlewRate = "slew_rate";
            internal const string VTrip = "vtrip";
            internal const string UseAnnotation = "use_annotation";
            internal const string HotswapNeeded = "hotswap_needed";
        }

        internal static class Vtrip
        {
            internal const string CMOS = "0";
            internal const string LVTTL = "1";
            internal const string CMOS_OR_LVTTL = "3";
            internal const string Default = CMOS;
        }

        #region PerPinSettings
        private class HwPerPinSettings
        {
            public string[] PinAlias, DriveMode, MaxFrequency, I2C, DrState, IoVoltage, IntrMode, InputSyncMode,
                            InputBufferEn, OutputConn, OeConn, OutputSyncMode, OeSync, DriveStrength, OutputCurrCap,
                            PinMode, SlewRate, Vtrip, UseAnnotation, HotNeeded;

            public HwPerPinSettings(int width)
            {
                DriveMode = new string[width];
                InputBufferEn = new string[width];
                DrState = new string[width];
                InputSyncMode = new string[width];
                IntrMode = new string[width];
                IoVoltage = new string[width];
                OutputConn = new string[width];
                OeConn = new string[width];
                OutputSyncMode = new string[width];
                OeSync = new string[width];
                DriveStrength = new string[width];
                MaxFrequency = new string[width];
                I2C = new string[width];
                OutputCurrCap = new string[width];
                PinAlias = new string[width];
                PinMode = new string[width];
                SlewRate = new string[width];
                Vtrip = new string[width];
                UseAnnotation = new string[width];
                HotNeeded = new string[width];
            }
        }
        #endregion

        public static IDictionary<string, string> GenerateVerilogGenerics(CyPinData pins, ICyDeviceQuery_v1 deviceQuery)
        {
            HwPerPinSettings perPinSettings = CreatePerPinSetting(pins, deviceQuery);
            Dictionary<string, string> verilogItems = new Dictionary<string, string>();

            verilogItems.Add(Warp.Param.Width, pins.PinCount.ToString());
            verilogItems.Add(Warp.Param.SIOGroupCnt, "0"); // Placeholder in case SIO restored
            verilogItems.Add(Warp.Param.DriveMode, HwGetVerilogCsvString(perPinSettings.DriveMode));
            verilogItems.Add(Warp.Param.InputBuffersEnabled, HwGetVerilogCsvString(perPinSettings.InputBufferEn));
            verilogItems.Add(Warp.Param.InitialDriveStates, HwGetVerilogCsvString(perPinSettings.DrState));
            verilogItems.Add(Warp.Param.InputSyncMode, HwGetVerilogCsvString(perPinSettings.InputSyncMode));
            verilogItems.Add(Warp.Param.InterruptMode, HwGetVerilogCsvString(perPinSettings.IntrMode));
            verilogItems.Add(Warp.Param.IOVoltages, HwGetVerilogCsvString(perPinSettings.IoVoltage));
            verilogItems.Add(Warp.Param.OutConn,
                HwCreateHwTerminal(perPinSettings.OutputConn, pins, CyPinType.Digital_Out));
            verilogItems.Add(Warp.Param.OeConn, HwGetVerilogCsvString(perPinSettings.OeConn));
            verilogItems.Add(Warp.Param.OutputSyncMode, HwGetVerilogCsvString(perPinSettings.OutputSyncMode));
            verilogItems.Add(Warp.Param.OESyncs, HwGetVerilogCsvString(perPinSettings.OeSync));
            verilogItems.Add(Warp.Param.DriveStrength, HwGetVerilogCsvString(perPinSettings.DriveStrength));
            verilogItems.Add(Warp.Param.MaxFrequency, HwGetVerilogCsvString(perPinSettings.MaxFrequency));
            verilogItems.Add(Warp.Param.I2CMode, HwGetVerilogCsvString(perPinSettings.I2C));
            verilogItems.Add(Warp.Param.OutputCurrentCap, HwGetVerilogCsvString(perPinSettings.OutputCurrCap));
            verilogItems.Add(Warp.Param.PinAliases, HwGetVerilogCsvString(perPinSettings.PinAlias));
            verilogItems.Add(Warp.Param.PinMode, HwGetVerilogCsvString(perPinSettings.PinMode));
            verilogItems.Add(Warp.Param.SlewRate, HwGetVerilogCsvString(perPinSettings.SlewRate));
            verilogItems.Add(Warp.Param.VTrip, HwGetVerilogCsvString(perPinSettings.Vtrip));
            verilogItems.Add(Warp.Param.UseAnnotation, HwGetVerilogCsvString(perPinSettings.UseAnnotation));
            verilogItems.Add(Warp.Param.HotswapNeeded, HwGetVerilogCsvString(perPinSettings.HotNeeded));

            return verilogItems;
        }

        private static string HwCreateHwTerminal(string[] values, CyPinData pins, CyPinType pinType)
        {
            Debug.Assert(values.Length == pins.PinCount);
            string[] newValues = new string[values.Length];
            for (int i = 0; i < values.Length; i++)
            {
                newValues[i] = Formal.AsString(Formal.True == values[i] && pins[i].Type.Is(pinType));
            }
            return HwGetVerilogCsvString(newValues);
        }

        #region Hw (Verilog) Generation specific helper methods
        private static HwPerPinSettings CreatePerPinSetting(CyPinData pins, ICyDeviceQuery_v1 deviceQuery)
        {
            HwPerPinSettings perPinSettings = new HwPerPinSettings(pins.PinCount);

            for (int i = 0; i < pins.PinCount; i++)
            {
                CyPinData.PerPin pin = pins[i];

                perPinSettings.DriveMode[i] = HwConvertDriveMode(pin);
                perPinSettings.InputBufferEn[i] = Formal.AsString(pin.InputBufferEnabled);
                perPinSettings.DrState[i] = Formal.AsString(pin.GeneralInitialState);
                perPinSettings.InputSyncMode[i] = Formal.AsString(pin.InputSyncMode);
                perPinSettings.IntrMode[i] = Formal.AsString(pin.InputInterrupt);
                perPinSettings.IoVoltage[i] = pin.GeneralMinimumSupply;
                perPinSettings.OutputConn[i] = Formal.AsString(pin.TypeIsDigitalOutputHw);
                perPinSettings.OeConn[i] = Formal.AsString(pin.Type.Is(CyPinType.OE));
                perPinSettings.OutputSyncMode[i] = Formal.AsString(pin.OutputSyncMode);
                perPinSettings.OeSync[i] = Formal.AsString(
                    pin.Type.IsOneOf(CyPinType.Digital_Out | CyPinType.Bidirectional) && pin.OutputEnableSynchronized);
                perPinSettings.DriveStrength[i] = Formal.AsString(pin.DriveStrength);
                perPinSettings.MaxFrequency[i] = Formal.AsString(pin.MaxFrequency);
                perPinSettings.I2C[i] = Formal.AsString(pin.I2CMode);
                perPinSettings.OutputCurrCap[i] = Formal.AsString(pin.OutputCurrentCap);
                perPinSettings.PinAlias[i] = pin.Alias;
                perPinSettings.PinMode[i] = HwCreatePinMode(pin);
                perPinSettings.SlewRate[i] = Formal.AsString(
                    pin.Type.IsOneOf(CyPinType.Digital_Out | CyPinType.Bidirectional)
                    ? pin.OutputSlewRate
                    : CyOutputSlewRate.Default);
                perPinSettings.Vtrip[i] = HwConvertInputThreshold(pin.InputThreshold);
                perPinSettings.UseAnnotation[i] = Formal.AsString(pin.TypeShowExternalTerm);
                perPinSettings.HotNeeded[i] = Formal.AsString(pin.GeneralHotSwap);
            }

            return perPinSettings;
        }

        private static string HwConvertDriveMode(CyPinData.PerPin pin)
        {
            CyDriveMode mode = pin.GeneralDriveMode;
            if (mode == CyDriveMode.High_impedance_digital) mode = CyDriveMode.High_impedance_analog;
            return Formal.AsString(mode);
        }

        private static string HwConvertInputThreshold(CyInputThreshold threshold)
        {
            if (threshold == CyInputThreshold.CMOS)
                return Warp.Vtrip.CMOS;
            if (threshold == CyInputThreshold.LVTTL)
                return Warp.Vtrip.LVTTL;
            if (threshold == CyInputThreshold.CMOS_LVTTL)
                return Warp.Vtrip.CMOS_OR_LVTTL;
            return Warp.Vtrip.Default;
        }

        private static string HwCreatePinMode(CyPinData.PerPin pin)
        {
            string mode = string.Empty;
            if (pin.Type.Is(CyPinType.Bidirectional))
                mode += Formal.PinTypes.Bidirectional;
            if (pin.Type.Is(CyPinType.Digital_In))
                mode += Formal.PinTypes.DigIn;
            if (pin.Type.Is(CyPinType.Digital_Out))
                mode += Formal.PinTypes.DigOut;
            if (pin.Type.Is(CyPinType.Analog))
                mode += Formal.PinTypes.Analog;
            // OE is handled separately when writing Verilog

            if (mode == string.Empty)
            {
                Debug.Fail("No pin mode set");
                return Formal.PinTypes.DigIn;
            }

            return mode;
        }

        private static string HwGetVerilogCsvString(string[] value)
        {
            return "\"" + string.Join(",", value) + "\"";
        }
        #endregion
    }

    /// <summary>
    /// Extract type-safe data from a ComboBox.
    /// </summary>
    /// <typeparam name="T">The data type.</typeparam>
    /// <remarks>Use Utils.AddItem to place the items in the ComboBox.</remarks>
    [ExcludeFromCodeCoverage]
    internal class CyComboItem<T> where T : struct
    {
        public readonly T Item;
        public readonly string DisplayString;

        public CyComboItem(T item, string displayString)
        {
            Item = item;
            DisplayString = displayString;
        }

        public override string ToString()
        {
            return DisplayString;
        }
    }

    /// <summary>
    /// This static class provides some generic utility functions that can be used by anyone
    /// </summary>
    [ExcludeFromCodeCoverage]
    public static class ComboUtils
    {
        internal static void AddItem<T>(this ComboBox combo, T item, string description) where T : struct
        {
            combo.Items.Add(new CyComboItem<T>(item, description));
        }

        public static int GetIndex<T>(this ComboBox cbo, T key) where T : struct
        {
            for (int i = 0; i < cbo.Items.Count; i++)
            {
                if (((CyComboItem<T>)cbo.Items[i]).Item.Equals(key))
                    return i;
            }
            return -1;
        }
    }

    /// <summary>
    /// This class provides a means of tracking which element is responsible for which Pin setting.
    /// This provides a central location to report errors to and have them appear on in the proper
    /// location in the UI.
    /// </summary>
    public class CyErrorManager
    {
        private struct ErrorControl
        {
            internal ErrorProvider Provider { get { return m_provider; } }
            internal Control Control { get { return m_control; } }

            internal ErrorControl(ErrorProvider provider, Control ctrl)
            {
                m_provider = provider;
                m_control = ctrl;
            }

            private ErrorProvider m_provider;
            private Control m_control;
        }

        private Dictionary<Formal.ErrorKey, ErrorControl> m_settingOwners =
            new Dictionary<Formal.ErrorKey, ErrorControl>();

        public CyErrorManager()
        {
        }

        internal void RegisterKeyOwner(Formal.ErrorKey key, ErrorProvider errProvider, Control ctrl)
        {
            m_settingOwners.Add(key, new ErrorControl(errProvider, ctrl));
        }

        internal void ClearErrors()
        {
            foreach (ErrorControl item in m_settingOwners.Values)
                item.Provider.SetError(item.Control, string.Empty);
        }

        internal void SetError(Formal.ErrorKey key, string msg)
        {
            ErrorControl owner = m_settingOwners[key];
            string err = owner.Provider.GetError(owner.Control);
            if (!string.IsNullOrEmpty(err))
                msg = err + Environment.NewLine + msg;
            owner.Provider.SetError(owner.Control, msg);
        }

        internal IEnumerable<string> GetErrors(IEnumerable<Formal.ErrorKey> keys)
        {
            foreach (Formal.ErrorKey key in keys)
            {
                ErrorControl item = m_settingOwners[key];
                string err = item.Provider.GetError(item.Control);
                if (!string.IsNullOrEmpty(err))
                {
                    foreach (string msg in err.Split(new string[] { Environment.NewLine }, StringSplitOptions.None))
                        yield return msg;
                }
            }
        }

        internal bool HasError(IEnumerable<Formal.ErrorKey> keys)
        {
            foreach (Formal.ErrorKey key in keys)
            {
                ErrorControl item = m_settingOwners[key];
                if (!string.IsNullOrEmpty(item.Provider.GetError(item.Control)))
                    return true;
            }
            return false;
        }
    }
}
