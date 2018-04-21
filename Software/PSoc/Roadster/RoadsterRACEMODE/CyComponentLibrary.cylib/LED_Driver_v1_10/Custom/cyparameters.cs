/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace LED_Driver_v1_10
{
    public class CyParamNames
    {
        public const string BRIGHTNESS_CTL = "BrightnessCtrl";
        public const string CLOCK_SOURCE   = "ClkSource";
        public const string COMMON_DRIVE   = "CommonDrive";
        public const string NUM_COMMONS    = "NumCom";
        public const string NUM_SEGMENTS   = "NumSeg";
        public const string SEGMENT_DRIVE  = "SegmentDrive";
        public const string REFRESH_RATE = "RefreshRate";
    }

    public class CyParamRanges
    {
        public const byte MIN_COMMONS = 1;
        public const byte MAX_COMMONS = 8;
        public const byte MIN_SEGMENTS = 1;
        public const byte MAX_SEGMENTS = 24;

        public const byte MIN_REFRESH_RATE = 1;

        public const UInt16 BRIGHTNESS_DIV = 256;
        public const byte BUS_CLK_DIV = 100;

        public const double EPS = 1E-6;
    }

    public enum CyEDriveMode { ActiveLow = 0, ActiveHigh = 1 }
    public enum CyEClockSource { Internal = 0, External = 1 }
    public enum CyEBrightness { Disabled = 0, Enabled = 1 }

    public class CyParameters
    {
        public ICyInstQuery_v1 m_instQuery;
        public ICyTerminalQuery_v1 m_termQuery;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        private bool m_clockNeedsUpdate = false;
        public bool ClockNeedsUpdate
        {
            get { return (ClockSource == CyEClockSource.Internal) &&
                    m_clockNeedsUpdate && (LatestDesiredClkFreq != ConvertRefreshRateToFrequency(DisplayRefreshRate));
            }
            set { m_clockNeedsUpdate = value; }
        }

        private UInt32 m_latestDesiredClkFreq = 0;
        public UInt32 LatestDesiredClkFreq
        {
            get { return m_latestDesiredClkFreq; }
            set { m_latestDesiredClkFreq = value; }
        }

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_termQuery = termQuery;
        }
        #endregion

        #region Getting Parameters
        public T GetValue<T>(string paramName)
        {
            T value;
            CyCompDevParam param = m_instQuery.GetCommittedParam(paramName);
            if (param != null)
            {
                CyCustErr err = param.TryGetValueAs<T>(out value);
                if (err != null && err.IsOK)
                {
                    return value;
                }
            }

            return default(T);
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode)
                if (m_instQuery != null && m_instQuery is ICyInstEdit_v1)
                {
                    ICyInstEdit_v1 inst = m_instQuery as ICyInstEdit_v1;
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

        #region Class properties
        public bool BrightnessEnabled
        {
            get { return (GetValue<CyEBrightness>(CyParamNames.BRIGHTNESS_CTL) == CyEBrightness.Enabled); }
            set { SetValue(CyParamNames.BRIGHTNESS_CTL, value ? CyEBrightness.Enabled : CyEBrightness.Disabled); }
        }
        public CyEClockSource ClockSource
        {
            get { return GetValue<CyEClockSource>(CyParamNames.CLOCK_SOURCE); }
            set { SetValue(CyParamNames.CLOCK_SOURCE, value); }
        }
        public CyEDriveMode CommonDriveMode
        {
            get { return GetValue<CyEDriveMode>(CyParamNames.COMMON_DRIVE); }
            set { SetValue(CyParamNames.COMMON_DRIVE, value); }
        }
        public CyEDriveMode SegmentDriveMode
        {
            get { return GetValue<CyEDriveMode>(CyParamNames.SEGMENT_DRIVE); }
            set { SetValue(CyParamNames.SEGMENT_DRIVE, value); }
        }
        public byte NumberOfCommons
        {
            get { return GetValue<byte>(CyParamNames.NUM_COMMONS); }
            set { SetValue(CyParamNames.NUM_COMMONS, value); }
        }
        public byte NumberOfSegments
        {
            get { return GetValue<byte>(CyParamNames.NUM_SEGMENTS); }
            set { SetValue(CyParamNames.NUM_SEGMENTS, value); }
        }
        public UInt32 DisplayRefreshRate
        {
            get { return GetValue<UInt32>(CyParamNames.REFRESH_RATE); }
            set { SetValue(CyParamNames.REFRESH_RATE, value); }
        }
        #endregion

        #region Clock frequency
        private const double FREQUENCY_UNKNOWN = -1.0;
        
        private const string CLOCK_TEMINAL_NAME = "clock";
        private const string INTERNAL_CLOCK_NAME = "or_internal";
        private const string BUS_CLOCK_NAME = "or_bus";
        public const string UNITS_HZ = "Hz";
        public const string UNKNOWN_FREQUENCY_STR = "UNKNOWN";

        public static bool IsFrequencyKnown(double frequency)
        {
            return frequency > CyParamRanges.EPS;
        }

        public double ExternalClockFrequency
        {
            get { return GetClockFrequency(CLOCK_TEMINAL_NAME, false); }
        }

        public double InternalClockFrequency
        {
            get { return GetClockFrequency(INTERNAL_CLOCK_NAME, true); }
        }

        public double BusClockFrequency
        {
            get { return GetClockFrequency(BUS_CLOCK_NAME, true); }
        }

        public double GetClockFrequency(string clockName, bool internalClock)
        {
            if (m_termQuery != null)
            {
                List<CyClockData> clkdata = internalClock ?
                    m_termQuery.GetClockData(clockName, "term1", 0) : m_termQuery.GetClockData(clockName, 0);
                if (clkdata.Count > 0)
                {
                    if (clkdata[0].IsFrequencyKnown)
                    {
                        return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
                    }
                }
            }
            return FREQUENCY_UNKNOWN;
        }

        public UInt32 CalculatedRefreshRate
        {
            get
            {
                UInt32 rate = 0;
                double frequency = (ClockSource == CyEClockSource.External) ? ExternalClockFrequency :
                    InternalClockFrequency;

                if (IsFrequencyKnown(frequency))
                {
                    rate = ConvertFrequencyToRefreshRate(frequency);
                }

                return rate;
            }
        }

        private UInt16 GetFrequencyVsRefreshRateCoef()
        {
            return (UInt16)(NumberOfCommons * (BrightnessEnabled ? CyParamRanges.BRIGHTNESS_DIV : (ushort)1));
        }

        private UInt32 ConvertFrequencyToRefreshRate(double frequency)
        {
            return (UInt32)Math.Round(frequency / GetFrequencyVsRefreshRateCoef());
        }

        public UInt32 ConvertRefreshRateToFrequency(UInt32 refreshRate)
        {
            return refreshRate * GetFrequencyVsRefreshRateCoef();
        }

        #region BUS_CLK
        public bool CheckFrequencyVsBusClock(double frequency)
        {
            bool inRange = true;
            double freqComparedToBusClk = GetMaxFreqComparedBusClk();
            if (frequency > freqComparedToBusClk + CyParamRanges.EPS)
            {
                inRange = false;
            }
            return inRange;
        }

        public double GetMaxFreqComparedBusClk()
        {
            double maxfreq = UInt32.MaxValue;
            if (IsFrequencyKnown(BusClockFrequency))
            {
                maxfreq = (double)ConvertFrequencyToRefreshRate(BusClockFrequency) / CyParamRanges.BUS_CLK_DIV;
            }
            return maxfreq;
        }
        #endregion BUS_CLK

        #endregion

        #region DRC
        public CyCustErr VerifyBusClock()
        {
            double refreshRate = CalculatedRefreshRate;

            if (IsFrequencyKnown(refreshRate) && (CheckFrequencyVsBusClock(refreshRate) == false))
            {
                return new CyCustErr(String.Format(Resources.BusClockCompareError, GetMaxFreqComparedBusClk()));
            }
            return CyCustErr.OK;
        }
        #endregion DRC
    }
}
