/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    /// <summary>
    /// This static class provides some generic untility functions that can be used by anyone
    /// </summary>
    public static class Utils
    {
        public static int GetIndex<T>(ComboBox cbo, T key)
        {
            for (int i = 0; i < cbo.Items.Count; i++)
            {
                if (((CyComboItem<T>)cbo.Items[i]).Item.Equals(key))
                    return i;
            }
            return -1;
        }

        public static int Max(int arg, params int[] args)
        {
            int max = arg;
            for (int i = 0; i < args.Length; i++)
                max = Math.Max(max, args[i]);
            return max;
        }

        public static int Min(IEnumerable<int> nums)
        {
            int min = int.MaxValue;
            foreach (int i in nums)
            {
                if (min > i)
                    min = i;
            }
            Debug.Assert(min != int.MaxValue);
            return min;
        }
    }

    public static partial class CyParameters
    {
        #region Setting Values
        internal const string ParamValue_FALSE = "0";
        internal const string ParamValue_TRUE = "1";

        internal const string ParamValue_DISABLED = "0";
        internal const string ParamValue_ENABLED = "1";
        #endregion

        #region Locals
        internal const string Local_ParamName_InputBuffersEnabled = "ibuf_enabled";
        internal const string Local_ParamName_SIOGroupCnt = "sio_group_cnt";
        internal const string Local_ParamName_SlewRate = "slew_rate";
        internal const string Local_ParamName_InterruptMode = "intr_mode";
        internal const string Local_ParamName_DriveMode = "drive_mode";
        internal const string Local_ParamName_SIOHysteresis = "sio_hyst";
        internal const string Local_ParamName_PinAlisases = "pin_aliases";
        internal const string Local_ParamName_InitialDriveStates = "init_dr_st";
        internal const string Local_ParamName_InputsSynchronized = "input_sync";
        internal const string Local_ParamName_InputsSyncMode = "input_sync_mode";
        internal const string Local_ParamName_IOVoltages = "io_voltage";
        internal const string Local_ParamName_InvertInClock = "invert_in_clock";
        internal const string Local_ParamName_InvertInClockEn = "invert_in_clock_en";
        internal const string Local_ParamName_InvertInReset = "invert_in_reset";
        internal const string Local_ParamName_InvertOutClock = "invert_out_clock";
        internal const string Local_ParamName_InvertOutClockEn = "invert_out_clock_en";
        internal const string Local_ParamName_InvertOutReset = "invert_out_reset";
        internal const string Local_ParamName_OutputsSynchronized = "output_sync";
        internal const string Local_ParamName_SIOInfo = "sio_info";
        internal const string Local_ParamName_VTrip = "vtrip";
        internal const string Local_ParamName_SIORefSels = "sio_refsel";
        internal const string Local_ParamName_OutputModes = "output_mode";
        internal const string Local_ParamName_OutputClockModes = "output_clock_mode";
        internal const string Local_ParamName_OESyncs = "oe_sync";
        internal const string Local_ParamName_OEResets = "oe_reset";
        internal const string Local_ParamName_OutputResets = "output_reset";

        internal const string Local_ParamName_InClkEn = "input_clk_en";
        internal const string Local_ParamName_LayoutMode = "layout_mode";
        internal const string Local_ParamName_OeConn = "oe_conn";
        internal const string Local_ParamName_OutClkEn = "output_clk_en";
        internal const string Local_ParamName_OutConn = "output_conn";
        internal const string Local_ParamName_PaInClk = "pa_in_clock";
        internal const string Local_ParamName_PaInClkEn = "pa_in_clock_en";
        internal const string Local_ParamName_PaInReset = "pa_in_reset";
        internal const string Local_ParamName_PaOutClk = "pa_out_clock";
        internal const string Local_ParamName_PaOutClkEn = "pa_out_clock_en";
        internal const string Local_ParamName_PaOutReset = "pa_out_reset";
        internal const string Local_ParamName_PinMode = "pin_mode";
        internal const string Local_ParamName_PorState = "por_state";
        internal const string Local_ParamName_SioIBuf = "sio_ibuf";
        internal const string Local_ParamName_SioOBuf = "sio_obuf";
        internal const string Local_ParamName_SioVtrip = "sio_vtrip";
        internal const string Local_ParamName_Spanning = "spanning";
        internal const string Local_ParamName_Width = "width";

        internal const string Local_ParamName_UseAnnotation = "use_annotation";
        #endregion

        #region PerPinSettings
        private class HwPerPinSettings
        {
            public string[] DriveMode, InputBufferEn, DrState, InputSync, InputSyncMode, IntrMode, IoVoltage,
                OeConn, OeSync, OutputClockMode, OutputConn, OutputMode, OutputSync, PinAlias, PinMode,
                SioHist, SioIBuf, SioInfo, SioOBuf, SioRefSel, SioVtrip, SioSlewRate, UseAnnotation, Vtrip;

            public HwPerPinSettings(int width)
            {
                DriveMode = new string[width];
                InputBufferEn = new string[width];
                DrState = new string[width];
                InputSync = new string[width];
                InputSyncMode = new string[width];
                IntrMode = new string[width];
                IoVoltage = new string[width];
                OeConn = new string[width];
                OeSync = new string[width];
                OutputClockMode = new string[width];
                OutputConn = new string[width];
                OutputMode = new string[width];
                OutputSync = new string[width];
                PinAlias = new string[width];
                PinMode = new string[width];
                SioHist = new string[width];
                SioIBuf = new string[width];
                SioInfo = new string[width];
                SioOBuf = new string[width];
                SioRefSel = new string[width];
                SioVtrip = new string[width];
                SioSlewRate = new string[width];
                UseAnnotation = new string[width];
                Vtrip = new string[width];
            }
        }
        #endregion

        public static IDictionary<string, string> GenerateVerilogGenerics(CyPinData pins, ICyDeviceQuery_v1 deviceQuery)
        {
            HwPerPinSettings perPinSettings = CreatePerPinSetting(pins, deviceQuery);
            Dictionary<string, string> verilogItems = new Dictionary<string, string>();

            verilogItems.Add(Local_ParamName_DriveMode, HwGetVerilogBitVector(perPinSettings.DriveMode));
            verilogItems.Add(Local_ParamName_InputBuffersEnabled, HwGetVerilogBitVector(perPinSettings.InputBufferEn));
            verilogItems.Add(Local_ParamName_InitialDriveStates, HwGetVerilogBitVector(perPinSettings.DrState));
            verilogItems.Add(Local_ParamName_InClkEn, (pins.ClockInputEnableOn == CyPinClockEnable.LEVEL) ? "1" : "0");
            verilogItems.Add(Local_ParamName_InputsSynchronized, HwGetVerilogBitVector(perPinSettings.InputSync));
            verilogItems.Add(Local_ParamName_InputsSyncMode, HwGetVerilogBitVector(perPinSettings.InputSyncMode));
            verilogItems.Add(Local_ParamName_InterruptMode, HwGetVerilogBitVector(perPinSettings.IntrMode));
            verilogItems.Add(Local_ParamName_InvertInClock, HwCreateIsInvertedClock(pins.ClockInput));
            verilogItems.Add(Local_ParamName_InvertInClockEn, HwCreateIsInvertedClock(pins.ClockInputEnable));
            verilogItems.Add(Local_ParamName_InvertInReset, HwCreateIsInvertedClock(pins.ClockInputReset));
            verilogItems.Add(Local_ParamName_InvertOutClock, HwCreateIsInvertedClock(pins.ClockOutput));
            verilogItems.Add(Local_ParamName_InvertOutClockEn, HwCreateIsInvertedClock(pins.ClockOutputEnable));
            verilogItems.Add(Local_ParamName_InvertOutReset, HwCreateIsInvertedClock(pins.ClockOutputReset));
            verilogItems.Add(Local_ParamName_IOVoltages, HwGetVerilogCsvString(perPinSettings.IoVoltage));
            verilogItems.Add(Local_ParamName_LayoutMode, 
                pins.MappingContigious ? "\"CONTIGUOUS\"" : "\"NONCONTIGUOUS\"");
            verilogItems.Add(Local_ParamName_OeConn, HwGetVerilogBitVector(perPinSettings.OeConn));
            verilogItems.Add(Local_ParamName_OEResets, pins.ClockOutputOeResetEnable ? "1" : "0");
            verilogItems.Add(Local_ParamName_OESyncs, HwGetVerilogBitVector(perPinSettings.OeSync));
            verilogItems.Add(Local_ParamName_OutClkEn, 
                (pins.ClockOutputEnableOn == CyPinClockEnable.LEVEL) ? "1" : "0");
            verilogItems.Add(Local_ParamName_OutputClockModes, HwGetVerilogBitVector(perPinSettings.OutputClockMode));
            verilogItems.Add(Local_ParamName_OutConn, 
                HwCreateHwTerminal(perPinSettings.OutputConn, pins, CyPinType.DIGITAL_OUT));
            verilogItems.Add(Local_ParamName_OutputModes, HwGetVerilogBitVector(perPinSettings.OutputMode));
            verilogItems.Add(Local_ParamName_OutputResets, pins.ClockOutputResetEnable ? "1" : "0");
            verilogItems.Add(Local_ParamName_OutputsSynchronized, HwGetVerilogBitVector(perPinSettings.OutputSync));
            verilogItems.Add(Local_ParamName_PaInClk, HwCreatePaUseClock(pins.ClockInput, pins.ClockPAPin));
            verilogItems.Add(Local_ParamName_PaInClkEn, 
                HwCreatePaResetEnableSignal(pins.ClockInputEnable, pins.ClockPAPin));
            verilogItems.Add(Local_ParamName_PaInReset, 
                HwCreatePaResetEnableSignal(pins.ClockInputReset, pins.ClockPAPin));
            verilogItems.Add(Local_ParamName_PaOutClk, HwCreatePaUseClock(pins.ClockOutput, pins.ClockPAPin));
            verilogItems.Add(Local_ParamName_PaOutClkEn, 
                HwCreatePaResetEnableSignal(pins.ClockOutputEnable, pins.ClockPAPin));
            verilogItems.Add(Local_ParamName_PaOutReset, 
                HwCreatePaResetEnableSignal(pins.ClockOutputReset, pins.ClockPAPin));
            verilogItems.Add(Local_ParamName_PinAlisases, HwGetVerilogCsvString(perPinSettings.PinAlias));
            verilogItems.Add(Local_ParamName_PinMode, HwGetVerilogString(perPinSettings.PinMode));
            verilogItems.Add(Local_ParamName_PorState, HwCreatePorState(pins.PowerOnReset));
            verilogItems.Add(Local_ParamName_SIOGroupCnt, pins.GetSioGroupCnt().ToString());
            verilogItems.Add(Local_ParamName_SIOHysteresis, HwGetVerilogBitVector(perPinSettings.SioHist));
            verilogItems.Add(Local_ParamName_SioIBuf, HwGetVerilogBitVector(perPinSettings.SioIBuf));
            verilogItems.Add(Local_ParamName_SIOInfo, HwGetVerilogBitVector(perPinSettings.SioInfo));
            verilogItems.Add(Local_ParamName_SioOBuf, HwGetVerilogBitVector(perPinSettings.SioOBuf));
            verilogItems.Add(Local_ParamName_SIORefSels, HwGetVerilogBitVector(perPinSettings.SioRefSel));
            verilogItems.Add(Local_ParamName_SioVtrip, HwGetVerilogBitVector(perPinSettings.SioVtrip));
            verilogItems.Add(Local_ParamName_SlewRate, HwGetVerilogBitVector(perPinSettings.SioSlewRate));
            verilogItems.Add(Local_ParamName_Spanning, pins.MappingSpanning ? "1" : "0");
            verilogItems.Add("use_annotation", HwGetVerilogBitVector(perPinSettings.UseAnnotation));
            verilogItems.Add(Local_ParamName_VTrip, HwGetVerilogBitVector(perPinSettings.Vtrip));
            verilogItems.Add(Local_ParamName_Width, pins.PinCount.ToString());

            return verilogItems;
        }

        private static string HwCreateHwTerminal(string[] values, CyPinData pins, CyPinType pinType)
        {
            Debug.Assert(values.Length == pins.PinCount);
            string[] newValues = new string[values.Length];
            for (int i = 0; i < values.Length; i++)
            {
                newValues[i] = (values[i] == ParamValue_TRUE && ((pins[i].Type & pinType) == pinType))
                    ? ParamValue_TRUE
                    : ParamValue_FALSE;
            }
            return HwGetVerilogBitVector(newValues);
        }

        #region Hw (Verilog) Generation specific helper methods
        private static HwPerPinSettings CreatePerPinSetting(CyPinData pins, ICyDeviceQuery_v1 deviceQuery)
        {
            HwPerPinSettings perPinSettings = new HwPerPinSettings(pins.PinCount);
            CyDeviceSupport devSupport = new CyDeviceSupport(deviceQuery);
            bool hasInputSync = !devSupport.HasData | devSupport.IsPSoC3 | devSupport.IsPSoC5 | devSupport.HasPortAdapter;

            for (int i = 0; i < pins.PinCount; i++)
            {
                CyPinData.PerPin pin = pins[i];

                perPinSettings.DriveMode[i] = CyPinData.PerPin.ConvertDriveMode(pin.GeneralDriveMode);
                perPinSettings.InputBufferEn[i] = HwCreateInputBufferEnabled(pin);
                perPinSettings.DrState[i] = pin.GeneralInitialState ? ParamValue_TRUE : ParamValue_FALSE;
                perPinSettings.InputSync[i] = HwCreateInputSync(pin, hasInputSync);
                perPinSettings.InputSyncMode[i] = (pin.InputSyncMode == CyInputSyncMode.SINGLE_SYNC)
                    ? CyPinData.InputsSyncModeValue_SINGLE
                    : CyPinData.InputsSyncModeValue_DOUBLE;
                perPinSettings.IntrMode[i] = ((pin.Type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_IN)) > 0)
                    ? CyPinData.PerPin.ConvertInputInterrupt(pin.InputInterrupt)
                    : CyPinData.InterruptModeValue_NONE;
                perPinSettings.IoVoltage[i] = 
                    String.Equals("None", pin.GeneralMinimumSupply, StringComparison.InvariantCultureIgnoreCase) 
                    ? "" 
                    : pin.GeneralMinimumSupply;
                perPinSettings.OeConn[i] = ((pin.Type & CyPinType.OE) == CyPinType.OE) 
                    ? ParamValue_TRUE 
                    : ParamValue_FALSE;
                perPinSettings.OeSync[i] = ((pin.Type & (CyPinType.DIGITAL_OUT | CyPinType.BIDIRECTIONAL)) > 0)
                    ? pin.OutputEnableSynchronized ? ParamValue_TRUE : ParamValue_FALSE
                    : ParamValue_FALSE;
                perPinSettings.OutputClockMode[i] = (CyOutputMode.CLOCK_INV == pin.OutputMode)
                    ? CyPinData.OutputClockModesValue_INVERTED
                    : CyPinData.OutputClockModesValue_NORMAL;
                perPinSettings.OutputConn[i] = pin.TypeIsDigitalOutputHw ? ParamValue_TRUE : ParamValue_FALSE;
                perPinSettings.OutputMode[i] = 
                    (CyOutputMode.TRANSPARENT == pin.OutputMode || CyOutputMode.SINGLE_SYNC == pin.OutputMode)
                    ? CyPinData.OutputModesValue_DATA
                    : CyPinData.OutputModesValue_CLOCK;
                perPinSettings.OutputSync[i] = (CyOutputMode.TRANSPARENT == pin.OutputMode) 
                    ? ParamValue_DISABLED 
                    : ParamValue_ENABLED;
                perPinSettings.PinAlias[i] = pin.Alias;
                perPinSettings.PinMode[i] = HwCreatePinMode(pin);
                perPinSettings.SioHist[i] = pin.InputHysteresis ? ParamValue_TRUE : ParamValue_FALSE;
                perPinSettings.SioIBuf[i] = pin.IsFirstSIO() ? HwConvertSioInputBuffer(pin.InputThreshold) : "";
                perPinSettings.SioInfo[i] = HwConvertSioInfo(pin);
                perPinSettings.SioOBuf[i] = 
                    pin.IsFirstSIO() ? CyPinData.PerPin.ConvertOutputDriveLevel(pin.OutputDriveLevel) : "";
                perPinSettings.SioRefSel[i] = (pin.IsFirstSIO()) ? HwConvertSioVref(pin.InputThreshold) : "";
                perPinSettings.SioVtrip[i] = pin.IsFirstSIO() ? HwConvertSioVtrip(pin.InputThreshold) : "";
                perPinSettings.SioSlewRate[i] = ((pin.Type & (CyPinType.DIGITAL_OUT | CyPinType.BIDIRECTIONAL)) > 0)
                    ? CyPinData.PerPin.ConvertSlewRate(pin.OutputSlewRate)
                    : CyPinData.DefaultSlewRateValue;
                perPinSettings.UseAnnotation[i] = pin.TypeShowExternalTerm ? ParamValue_TRUE : ParamValue_FALSE;
                perPinSettings.Vtrip[i] = ConvertInputThreshold(pin.InputThreshold);
            }

            return perPinSettings;
        }

        private static string ConvertInputThreshold(CyInputThreshold threshold)
        {
            if (threshold == CyInputThreshold.CMOS_LVTTL)
                return CyPinData.VTripValue_CMOS_OR_LVTTL;
            else if (threshold == CyInputThreshold.LVTTL)
                return CyPinData.VTripValue_LVTTL;
            else
                return CyPinData.VTripValue_CMOS;
        }

        private static string HwCreateInputBufferEnabled(CyPinData.PerPin pin)
        {
            if ((pin.Type & (CyPinType.DIGITAL_IN | CyPinType.BIDIRECTIONAL)) > 0)
                return pin.InputBufferEnabled ? ParamValue_TRUE : ParamValue_FALSE;
            else if ((pin.Type & CyPinType.DIGITAL_OUT) == CyPinType.DIGITAL_OUT)
                return ParamValue_TRUE;
            return ParamValue_FALSE;
        }

        private static string HwCreateInputSync(CyPinData.PerPin pin, bool supportsSync)
        {
            if ((pin.Type & (CyPinType.DIGITAL_IN | CyPinType.BIDIRECTIONAL)) > 0)
                return (pin.InputSyncMode == CyInputSyncMode.TRANSPARENT) ? ParamValue_DISABLED : ParamValue_ENABLED;
            return supportsSync ? ParamValue_TRUE : ParamValue_FALSE;
        }

        private static string HwCreatePinMode(CyPinData.PerPin pin)
        {
            if (((pin.Type & CyPinType.BIDIRECTIONAL) == CyPinType.BIDIRECTIONAL) ||
                ((pin.Type & (CyPinType.DIGITAL_IN | CyPinType.DIGITAL_OUT)) == (CyPinType.DIGITAL_IN | CyPinType.DIGITAL_OUT)))
                return "B";
            else if ((pin.Type & CyPinType.DIGITAL_OUT) == CyPinType.DIGITAL_OUT)
                return "O";
            else if ((pin.Type & CyPinType.DIGITAL_IN) == CyPinType.DIGITAL_IN)
                return "I";
            else if ((pin.Type & CyPinType.ANALOG) == CyPinType.ANALOG)
                return "A";
            else
                Debug.Fail("No pin mode set");

            return "I";
        }

        private static string HwCreatePorState(CyPowerOnRestMode por)
        {
            switch (por)
            {
                case CyPowerOnRestMode.UNSPECIFIED:
                    return "4";
                case CyPowerOnRestMode.HIZ_ANALOG:
                    return "0";
                case CyPowerOnRestMode.PULLED_UP:
                    return "3";
                case CyPowerOnRestMode.PULLED_DOWN:
                    return "2";
                default:
                    Debug.Fail("Unhandled POR state: " + por);
                    return "4";
            }
        }

        private static string HwConvertSioInfo(CyPinData.PerPin pin)
        {
            if (pin.IsSIO())
            {
                if (pin.SIOPairID == 0)
                    return CyPinData.SIOInfoValue_FIRST_IN_SIO_PAIR;
                if (pin.SIOPairID == 1)
                    return CyPinData.SIOInfoValue_SECOND_IN_SIO_PAIR;
                else
                    return CyPinData.SIOInfoValue_SINGLE_SIO;
            }
            else
                return CyPinData.SIOInfoValue_NOT_SIO;
        }

        private static string HwConvertSioVref(CyInputThreshold threshold)
        {
            if (CyInputThreshold.VREF == threshold || CyInputThreshold.PT5_VREF == threshold)
                return CyPinData.SIORefSelValue_VOHREF;
            return CyPinData.SIORefSelValue_VCC_IO;
        }

        private static string HwConvertSioVtrip(CyInputThreshold threshold)
        {
            switch (threshold)
            {
                case CyInputThreshold.CMOS:
                case CyInputThreshold.CMOS_LVTTL:
                case CyInputThreshold.LVTTL:
                case CyInputThreshold.PT4_VDDIO:
                case CyInputThreshold.VREF:
                    return CyPinData.SIOVTripValue_PT4_OR_ONE;
                case CyInputThreshold.PT5_VDDIO:
                case CyInputThreshold.PT5_VREF:
                    return CyPinData.SIOVTripValue_PT5;
                default:
                    Debug.Fail("unhandled threshold: " + threshold);
                    return CyPinData.SIOVTripValue_PT4_OR_ONE;
            }
        }

        private static string HwConvertSioInputBuffer(CyInputThreshold threshold)
        {
            switch (threshold)
            {
                case CyInputThreshold.CMOS:
                case CyInputThreshold.CMOS_LVTTL:
                case CyInputThreshold.LVTTL:
                    return CyPinData.SIOInputBufferValue_SINGLE_ENDED;
                case CyInputThreshold.PT4_VDDIO:
                case CyInputThreshold.PT5_VDDIO:
                case CyInputThreshold.PT5_VREF:
                case CyInputThreshold.VREF:
                    return CyPinData.SIOInputBufferValue_DIFFERENTIAL;
                default:
                    Debug.Fail("unhandled threshold: " + threshold);
                    return CyPinData.SIOInputBufferValue_SINGLE_ENDED;
            }
        }

        private static string HwCreateIsInvertedClock(CyPinClock setting)
        {
            bool isInverted = (CyPinClock.EXTERNAL_INV == setting) ||
                (CyPinClock.HFCLK_INV == setting) ||
                (CyPinClock.PIN_INV == setting);
            return isInverted ? "1" : "0";
        }

        private static string HwCreateIsInvertedClock(CyPinClockEnRst setting)
        {
            return (CyPinClockEnRst.EXTERNAL_INV == setting) || (CyPinClockEnRst.PIN_INV == setting) 
                ? "1" : "0";
        }

        private static string HwCreatePaUseClock(CyPinClock setting, int paPin)
        {
            return (((CyPinClock.PIN == setting) || (CyPinClock.PIN_INV == setting)) ? paPin : -1).ToString();
        }

        private static string HwCreatePaResetEnableSignal(CyPinClockEnRst setting, int paPin)
        {
            return ((CyPinClockEnRst.NONE != setting) ? paPin : -1).ToString();
        }

        private static string HwGetVerilogBitVector(string[] value)
        {
            int size;
            string val = JoinFilterEmpty("_", value, out size);
            return (size == 0) ? "\"\"" : string.Format("{0}'b{1}", val.Length - (size - 1), val);
        }

        private static string HwGetVerilogCsvString(string[] value)
        {
            return "\"" + string.Join(",", value) + "\"";
        }

        private static string HwGetVerilogString(string[] value)
        {
            return "\"" + string.Join("", value) + "\"";
        }

        private static string JoinFilterEmpty(string seperator, string[] values, out int size)
        {
            size = 0;
            StringBuilder sb = new StringBuilder();
            int i = 0;
            while (i < values.Length && "" == values[i]) i++;

            if (i < values.Length)
            {
                sb.Append(values[i++]);
                size++;
            }
            while (i < values.Length)
            {
                if ("" != values[i])
                {
                    sb.Append(seperator).Append(values[i]);
                    size++;
                }
                i++;
            }
            return sb.ToString();
        }
        #endregion
    }

    public class CyComboItem<T>
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

    public class CyDeviceSupport
    {
        private const string IO_BLOCK = "m0s8ioss";
        private const string PARAM_PORT_CNT = "HSIOM.HSIOM_PORT_NR";
        private const string PARAM_IS_SIO_PORT = "GPIO_PRT.SIO[{0}]";
        private const string UDB_BLOCK = "m0s8udbif";

        public readonly bool HasData;

        public readonly bool IsPSoC3;
        public readonly bool IsPSoC4;
        public readonly bool IsPSoC5;
        public readonly bool IsTSG4;

        public readonly bool HasSIO;
        public readonly bool HasPortAdapter;

        public CyDeviceSupport(ICyDeviceQuery_v1 deviceQuery)
        {
            HasData = deviceQuery.DeviceFamilyAvailable;

            IsPSoC3 = deviceQuery.IsPSoC3;
            IsPSoC4 = deviceQuery.IsPSoC4;
            IsPSoC5 = deviceQuery.IsPSoC5;
            IsTSG4 = deviceQuery.IsTSG4;

            HasSIO = GetHasSIO(deviceQuery);
            HasPortAdapter = GetHasPortAdapter(deviceQuery);
        }

        public static bool GetHasSIO(ICyDeviceQuery_v1 deviceQuery)
        {
            if (deviceQuery.IsPSoC4 && !deviceQuery.IsTSG4)
            {
                bool hasSIO = false;
                int portCount = deviceQuery.GetFeatureParameter(IO_BLOCK, PARAM_PORT_CNT);
                for (int i = 0; i < portCount; i++)
                    hasSIO |= (deviceQuery.GetFeatureParameter(IO_BLOCK, string.Format(PARAM_IS_SIO_PORT, i)) == 1);

                return hasSIO;
            }
            else
                return true;
        }

        public static bool GetHasPortAdapter(ICyDeviceQuery_v1 deviceQuery)
        {
            return (deviceQuery.IsPSoC4 || deviceQuery.IsTSG4)
                ? (deviceQuery.GetFeatureCountDie(UDB_BLOCK) > 0)
                : false;
        }
    }

    public class Touple<T, U>
    {
        public readonly T First;
        public readonly U Second;

        public Touple(T first, U second)
        {
            First = first;
            Second = second;
        }
    }

    /// <summary>
    /// This class provides a means of tracking which element is repsonsible for which Pin setting.
    /// This provides a central location to report errors to and have them appear on in the proper
    /// location in the UI.
    /// </summary>
    public class CyErrorManager
    {
        private Dictionary<CyPinData.Key, Touple<ErrorProvider, Control>> m_settingOwners = 
            new Dictionary<CyPinData.Key, Touple<ErrorProvider, Control>>();

        public CyErrorManager()
        {
        }

        public void RegisterSettingOwner(CyPinData.Key key, ErrorProvider errProvider, Control ctrl)
        {
            m_settingOwners.Add(key, new Touple<ErrorProvider, Control>(errProvider, ctrl));
        }

        public void ClearErrors()
        {
            foreach (Touple<ErrorProvider, Control> item in m_settingOwners.Values)
                item.First.SetError(item.Second, string.Empty);
        }

        public void SetError(CyPinData.Key key, string msg)
        {
            Touple<ErrorProvider, Control> owner = m_settingOwners[key];
            string err = owner.First.GetError(owner.Second);
            if (string.IsNullOrEmpty(err))
                owner.First.SetError(owner.Second, msg);
            else
                owner.First.SetError(owner.Second, err + Environment.NewLine + msg);
        }

        public IEnumerable<string> GetErrors(IEnumerable<CyPinData.Key> keys)
        {
            foreach (CyPinData.Key key in keys)
            {
                Touple<ErrorProvider, Control> item = m_settingOwners[key];
                string err = item.First.GetError(item.Second);
                if (!string.IsNullOrEmpty(err))
                {
                    foreach (string msg in err.Split(new string[] { Environment.NewLine }, StringSplitOptions.None))
                        yield return msg;
                }
            }
        }

        public bool HasError(IEnumerable<CyPinData.Key> keys)
        {
            foreach (CyPinData.Key key in keys)
            {
                Touple<ErrorProvider, Control> item = m_settingOwners[key];
                if (!string.IsNullOrEmpty(item.First.GetError(item.Second)))
                    return true;
            }
            return false;
        }
    }
}
