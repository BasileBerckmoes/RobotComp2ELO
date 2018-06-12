/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace DVDAC_v2_10
{
    #region Component parameters names
    public class CyParamName
    {
        public const string VDAC_VALUE = "Initial_Value";
        public const string RESOLUTION = "Resolution";
        public const string VDAC_RANGE = "DAC_Range";
        public const string VDAC_CLOCK = "InternalClockFreqHz";
        public const string CLOCK_SOURCE = "InternalClock";
    }
    #endregion

    #region Parameters ranges
    public static class CyParamRange
    {
        public const byte MIN_RESOLUTION = 9;

        public const UInt16 MAX_VOLTAGE_1V_VALUE = 1020;
        public const UInt16 MAX_VOLTAGE_4V_VALUE = 4080;

        public const UInt16 MIN_CLOCK_FREQUENCY = 1;
        public const UInt16 MAX_CLOCK_FREQUENCY_1V = 1000;
        public const UInt16 MAX_CLOCK_FREQUENCY_4V = 250;

        public const UInt16 RESISTANCE_1V_VALUE = 4;
        public const UInt16 RESISTANCE_4V_VALUE = 16;

        public const byte BUS_CLK_DIVIDER = 12;

        public const double FREQUENCY_UNKNOWN = -1.0;
        public const double EPS = 0.001;

        public const UInt16 THOUSAND = 1000;

        public const UInt16 MIN_HEX_VALUE = 0x00;
        public static readonly UInt16[] MAX_HEX_VALUES = { 0x1FE, 0x3FC, 0x7F8, 0xFF0 };

        public static readonly UInt16[] DEFAULT_HEX_VALUES = { 0x100, 0x200, 0x400, 0x800 };

        public static readonly int[] ATTENUATION_VALUES = { 6, 12, 18, 24 };
        public static readonly string[] CAPACITOR_UNITS = { "uF", "nF", "pF" };
    }
    #endregion

    #region Component enums
    public enum CyEVDACRangeType { Range_1_Volt, Range_4_Volt = 4 }
    public enum CyEResolutionType { Resolution_9 = 9, Resolution_10, Resolution_11, Resolution_12 };
    #endregion

    public class CyParameters
    {
        public ICyInstQuery_v1 m_inst;
        public ICyTerminalQuery_v1 m_term;
        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        public bool m_globalEditMode = false;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 term)
        {
            m_inst = inst;
            m_term = term;
        }
        #endregion

        #region Class properties
        public UInt16 VDACValue
        {
            get { return GetValue<UInt16>(CyParamName.VDAC_VALUE); }
            set { SetValue(CyParamName.VDAC_VALUE, value); }
        }

        public CyEResolutionType Resolution
        {
            get { return GetValue<CyEResolutionType>(CyParamName.RESOLUTION); }
            set { SetValue(CyParamName.RESOLUTION, value); }
        }

        public CyEVDACRangeType VDACRange
        {
            get { return GetValue<CyEVDACRangeType>(CyParamName.VDAC_RANGE); }
            set { SetValue(CyParamName.VDAC_RANGE, value); }
        }

        public UInt32 ClockFrequency
        {
            get { return GetValue<UInt32>(CyParamName.VDAC_CLOCK); }
            set { SetValue(CyParamName.VDAC_CLOCK, value); }
        }

        public double ClockFrequencykHz
        {
            get { return ClockFrequency / (double)CyParamRange.THOUSAND; }
            set { ClockFrequency = (UInt32)Math.Round(value * CyParamRange.THOUSAND); }
        }

        public bool ClockSourceInternal
        {
            get { return GetValue<bool>(CyParamName.CLOCK_SOURCE); }
            set { SetValue(CyParamName.CLOCK_SOURCE, value); }
        }
        #endregion

        #region Getting parameters
        private T GetValue<T>(string paramName)
        {
            CyCompDevParam prm = m_inst.GetCommittedParam(paramName);
            T value = default(T);
            CyCustErr err = CyCustErr.OK;
            if (typeof(T).BaseType == typeof(Enum))
            {
                err = prm.TryGetValueAs<T>(out value);
                if ((err == null) || (err.IsOK == false) || (Enum.IsDefined(typeof(T), value) == false))
                {
                    value = (T)Enum.GetValues(typeof(T)).GetValue(0);
                    err = CyCustErr.OK;
                }
            }
            else
                err = prm.TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }

        public UInt16 GetMaxVoltageValue()
        {
            UInt16 result = (VDACRange == CyEVDACRangeType.Range_1_Volt) ? 
                             CyParamRange.MAX_VOLTAGE_1V_VALUE : CyParamRange.MAX_VOLTAGE_4V_VALUE;
            return result;
        }

        public UInt16 GetMaxFrequency()
        {
            UInt16 result = (VDACRange == CyEVDACRangeType.Range_1_Volt) ?
                             CyParamRange.MAX_CLOCK_FREQUENCY_1V : CyParamRange.MAX_CLOCK_FREQUENCY_4V;
            return result;
        }

        public UInt16 GetMaxHexValue()
        {
            return CyParamRange.MAX_HEX_VALUES[(byte)Resolution - CyParamRange.MIN_RESOLUTION];
        }

        public double GetRangeCoef()
        {
            return GetRangeCoef(GetMaxVoltageValue());
        }

        public double GetRangeCoef(double maxVoltage)
        {
            UInt16 maxActualHex = (UInt16)(255 * Math.Pow(2, (byte)Resolution - CyParamRange.MIN_RESOLUTION + 1));
            double coef = maxVoltage / maxActualHex;

            if (Math.Abs(coef) < CyParamRange.EPS)
            {
                coef = 1;
            }
            return coef;
        }

        public UInt16 GetMaxClockFrequency()
        {
            UInt16 result = (VDACRange == CyEVDACRangeType.Range_1_Volt) ?
                             CyParamRange.MAX_CLOCK_FREQUENCY_1V : CyParamRange.MAX_CLOCK_FREQUENCY_4V;
            return result;
        }

        public bool CheckFrequencyVsBusClock(double frequency)
        {
            bool inRange = true;
            double freqComparedToBusClk = GetMaxFreqComparedBusClk();
            if (frequency > freqComparedToBusClk + CyParamRange.EPS)
            {
                inRange = false;
            }
            return inRange;
        }

        public UInt16 ConvertVoltageToHex(double value)
        {
            return ((UInt16)Math.Round((double)value / GetRangeCoef()));
        }
        public double ConvertHexToVoltage(UInt16 value)
        {
            return (value * GetRangeCoef());
        }

        public UInt16? ConvertStrToUInt16(string text, bool isHex)
        {
            UInt16? result = null;
            UInt16 value = 0;
            try
            {
                if (isHex)
                {
                    value = Convert.ToUInt16(text, 16);
                }
                else
                {
                    value = Convert.ToUInt16(text);
                }
                result = value;
            }
            catch { }
           
            return result;
        }

        public double? ConvertStrToDouble(string text)
        {
            double? result = null;
            double value = 0;
          
            if (double.TryParse(text, out value))
                result = value;
           
            return result;
        }

        #endregion

        #region Setting parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
                if (m_inst != null && m_inst is ICyInstEdit_v1)
                {
                    ICyInstEdit_v1 inst = m_inst as ICyInstEdit_v1;
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                        valueToSet += "u";
                    if (inst.SetParamExpr(paramName, valueToSet))
                    {
                        inst.CommitParamExprs();
                    }
                }
        }
        #endregion

        #region Clock
        /// <summary>
        /// Returns external clock value in kHz
        /// </summary>
        public double GetExternalClockInkHz()
        {
            const string EXTERNAL_CLOCK = "clock";
            return GetClockInkHz(EXTERNAL_CLOCK, false);
        }

        public double GetBusClockInkHz()
        {
            const string BUS_CLOCK = "or_internal";
            return GetClockInkHz(BUS_CLOCK, true);
        }

        public double GetMaxFreqComparedBusClk()
        {
            double maxfreq = GetMaxFrequency();
            double busClockFrequency = GetBusClockInkHz();
            if (IsFrequencyKnown(busClockFrequency))
            {
                maxfreq = busClockFrequency / CyParamRange.BUS_CLK_DIVIDER;
            }
            return maxfreq;
        }

        public double GetClockInkHz(string clockName, bool internalClock)
        {
            if (m_term != null)
            {
                List<CyClockData> clkdata = internalClock ?
                    m_term.GetClockData(clockName, "term1", 0) : m_term.GetClockData(clockName, 0);
                if (clkdata.Count > 0)
                {
                    if (clkdata[0].IsFrequencyKnown)
                    {
                        return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                    }
                }
            }
            return CyParamRange.FREQUENCY_UNKNOWN;
        }

        public static string FormatFrequencyKHz(double frequency)
        {
            return frequency.ToString("0.000");
        }

        public static bool IsFrequencyKnown(double freq)
        {
            return freq >= 0;
        }
        #endregion Clock

        #region DRC
        public CyCustErr VerifyExternalClock()
        {
            if (ClockSourceInternal)
                return CyCustErr.OK;

            double freq = GetExternalClockInkHz();

            if ((IsFrequencyKnown(freq)) && ((freq > GetMaxClockFrequency() + CyParamRange.EPS)))
            {
                return new CyCustErr(String.Format(Resources.ClockFrequencyError, CyParamRange.MIN_CLOCK_FREQUENCY,
                                     FormatFrequencyKHz(GetMaxClockFrequency())));
            }
            return CyCustErr.OK;
        }

        public CyCustErr VerifyBusClock()
        {
            double freq = ClockSourceInternal ? ClockFrequencykHz : GetExternalClockInkHz();

            if (CheckFrequencyVsBusClock(freq) == false)
            {
                return new CyCustErr(String.Format(Resources.BusClockCompareError,
                    FormatFrequencyKHz(GetMaxFreqComparedBusClk())));
            }
            return CyCustErr.OK;
        }
        #endregion DRC
    }
}
