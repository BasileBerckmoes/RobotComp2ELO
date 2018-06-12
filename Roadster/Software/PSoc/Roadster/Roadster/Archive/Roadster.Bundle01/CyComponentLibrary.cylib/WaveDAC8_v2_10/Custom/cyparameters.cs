/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.ComponentModel;
using System.Windows.Forms;
using System.Reflection;
using System.Diagnostics;


namespace WaveDAC8_v2_10
{
    public enum CyEClockSourceType
    {
        External_Clk,
        Internal_Clk
    }

    public enum CyEWaveRangeType
    {
        [Description("VDAC 0 - 1.020 V")]
        Range_1_Volt = 0,
        [Description("VDAC 0 - 1.020 V (Buffered)")]
        Range_1_Volt_Buffered = 16,
        [Description("VDAC 0 - 4.080 V")]
        Range_4_Volt = 1,
        [Description("VDAC 0 - 4.080 V (Buffered)")]
        Range_4_Volt_Buffered = 17,
        [Description("ISink 0 - 2.040 mA")]
        ISink_2040_uA = 14,
        [Description("ISink 0 - 255 uA")]
        ISink_256_uA = 13,
        [Description("ISink 0 - 32 uA")]
        ISink_32_uA = 12,
        [Description("ISource 0 - 2.040 mA")]
        ISource_2040_uA = 6,
        [Description("ISource 0 - 255 uA")]
        ISource_256_uA = 5,
        [Description("ISource 0 - 32 uA")]
        ISource_32_uA = 4
    }

    public enum CyEWaveFormType
    {
        [Description("Sine")]
        Sine = 0,
        [Description("Square")]
        Square = 1,
        [Description("Triangle")]
        Triangle = 2,
        [Description("Sawtooth")]
        Sawtooth = 3,
        [Description("Arbitrary (draw)")]
        ArbitraryDraw = 10,
        [Description("Arbitrary (from file)")]
        ArbitraryFromFile = 11
    }

    public class CyParamConst
    {
        public const int MIN_DEGREE_SHIFT = 0;
        public const int MAX_DEGREE_SHIFT = 360;

        public const int MIN_NUM_SAMPLES = 4;
        public const int MAX_NUM_SAMPLES = 4000;

        public const double MAX_1_V = 1.020;
        public const double MAX_4_V = 4.080;
        public const double MAX_2040_uA = 2.040;
        public const double MAX_255_uA = 255; 
        public const double MAX_32_uA = 32;

        public const double DEF_1_V = 1.000;
        public const double DEF_4_V = 4.000;
        public const double DEF_2040_uA = 2.000;
        public const double DEF_255_uA = 250;
        public const double DEF_32_uA = 30;
        
        public const UInt32 MAX_FREQ_VDAC_1V = 1000000;
        public const UInt32 MAX_FREQ_VDAC_4V = 250000;
        public const UInt32 MAX_FREQ_IDAC = 6000000;

        public const UInt32 MIN_SAMPLE_RATE = 0;

        public const byte MAX_DATA_VALUE = 255;

        public const double EPS = 10e-5;
        public const double FREQUENCY_UNKNOWN = -1.0;
        public const UInt16 THOUSAND = 1000;
    }

    public class CyParameters
    {
        public const string P_CLOCK_SRC = "Clock_SRC";
        public const string P_DAC_RANGE = "DAC_Range";
        public const string P_SAMPLE_CLOCK_FREQ = "Sample_Clock_Freq";
        public const string P_ENABLE_BUFFER = "Enable_buffer";
        public const string P_WAVE_AMPLITUDE = "Wave{0}_Amplitude";
        public const string P_WAVE_DATA = "Wave{0}_Data";
        public const string P_WAVE_DC_OFFSET = "Wave{0}_DCOffset";
        public const string P_WAVE_LENGTH = "Wave{0}_Length";
        public const string P_WAVE_TYPE = "Wave{0}_Type";
        public const string P_WAVE_DEGREE_SHIFT= "Wave{0}_PhaseShift";

        public const string UNSIGNED_PREFIX = "u";
        public const char DATA_SEPARATOR = ',';

        private readonly ICyInstEdit_v1 m_instEdit;
        public readonly ICyInstQuery_v1 m_instQuery;
        public readonly ICyTerminalQuery_v1 m_termQuery;

        private bool m_globalEditMode = false;
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public CyParameters() { }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this()
        {
            m_instQuery = instQuery;
            m_instEdit = null;
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this()
        {
            m_instQuery = instEdit;
            m_instEdit = instEdit;
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit)
        {
            m_termQuery = termQuery;
        }

        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
            : this(instQuery)
        {
            m_termQuery = termQuery;
        }


        public CyEClockSourceType ClockSource
        {
            get { return GetValue<CyEClockSourceType>(P_CLOCK_SRC); }
            set { SetValue(P_CLOCK_SRC, value); }
        }

        public CyEWaveRangeType DACRange
        {
            get { return GetValue<CyEWaveRangeType>(P_DAC_RANGE); }
            set { SetValue(P_DAC_RANGE, value); }
        }

        public uint SampleRate
        {
            get { return GetValue<uint>(P_SAMPLE_CLOCK_FREQ); }
            set { SetValue(P_SAMPLE_CLOCK_FREQ, value); }
        }

        public bool EnableBuffer
        {
            get { return GetValue<bool>(P_ENABLE_BUFFER); }
            set { SetValue(P_ENABLE_BUFFER, value); }
        }

        public CyEWaveFormType GetWaveType(int waveNumber)
        {
            return GetValue<CyEWaveFormType>(GetParamNameByIndex(P_WAVE_TYPE, waveNumber));
        }
        public void SetWaveType(int waveNumber, CyEWaveFormType value)
        {
            SetValue(GetParamNameByIndex(P_WAVE_TYPE, waveNumber), value);
        }

        public double GetWaveAmplitude(int waveNumber)
        {
            return GetValue<double>(GetParamNameByIndex(P_WAVE_AMPLITUDE, waveNumber));
        }
        public void SetWaveAmplitude(int waveNumber, double value)
        {
            SetValue(GetParamNameByIndex(P_WAVE_AMPLITUDE, waveNumber), value);
        }

        public double GetWaveDCOffset(int waveNumber)
        {
            return GetValue<double>(GetParamNameByIndex(P_WAVE_DC_OFFSET, waveNumber));
        }
        public void SetWaveDCOffset(int waveNumber, double value)
        {
            SetValue(GetParamNameByIndex(P_WAVE_DC_OFFSET, waveNumber), value);
        }

        public uint GetWaveNumSamples(int waveNumber)
        {
            return GetValue<uint>(GetParamNameByIndex(P_WAVE_LENGTH, waveNumber));
        }
        public void SetWaveNumSamples(int waveNumber, uint value)
        {
            SetValue(GetParamNameByIndex(P_WAVE_LENGTH, waveNumber), value);
        }

        public ushort GetWaveDegreeShift(int waveNumber)
        {
            return (ushort)GetValue<uint>(GetParamNameByIndex(P_WAVE_DEGREE_SHIFT, waveNumber));
        }
        public void SetWaveDegreeShift(int waveNumber, ushort value)
        {
            SetValue(GetParamNameByIndex(P_WAVE_DEGREE_SHIFT, waveNumber), value);
        }

        public List<byte> GetWaveData(int waveNumber)
        {
            return GetDataValues(GetValue<string>(GetParamNameByIndex(P_WAVE_DATA, waveNumber)));
        }
        public void SetWaveData(int waveNumber, List<byte> value)
        {
            SetValue(GetParamNameByIndex(P_WAVE_DATA, waveNumber), DataToString(value));
        }

        public static string GetParamNameByIndex(string name, int index)
        {
            return String.Format(name, index);
        }

        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null)
                return default(T);

            if (m_instQuery.ContainsParam(paramName) == false)
            {
                Debug.Fail(String.Empty);
                return default(T);
            }

            CyCompDevParam prm = m_instQuery.GetCommittedParam(paramName);
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

        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode && (m_instEdit != null))
            {
                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                    valueToSet += UNSIGNED_PREFIX;
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }

        private string DataToString(List<byte> data)
        {
            StringBuilder dataString = new StringBuilder();
            for (int i = 0; i < data.Count; i++)
            {
                dataString.Append(data[i].ToString());
                dataString.Append(UNSIGNED_PREFIX);
                dataString.Append(DATA_SEPARATOR);
            }
            return dataString.ToString().TrimEnd(DATA_SEPARATOR);
        }

        private List<byte> GetDataValues(string datastring)
        {
            List<byte> data = new List<byte>();
            if (String.IsNullOrEmpty(datastring))
                return data;

            string[] split = datastring.Split(DATA_SEPARATOR);
            foreach (string str in split)
            {
                try
                {
                    data.Add(Convert.ToByte(str.Replace(UNSIGNED_PREFIX, String.Empty)));
                }
                catch 
                {
                    Debug.Fail(String.Empty);
                }
            }
            return data;
        }

        public CyWaveRange GetMaxVolage()
        {
            CyEWaveRangeType dacRange = DACRange;
            CyWaveRange range = new CyWaveRange();
            switch (dacRange)
            {
                case CyEWaveRangeType.Range_1_Volt:
                case CyEWaveRangeType.Range_1_Volt_Buffered:
                    range.MaxRange = CyParamConst.MAX_1_V;
                    range.DefaultValue = CyParamConst.DEF_1_V;
                    range.Units = CyWaveRange.UNITS_VOLT;
                    break;
                case CyEWaveRangeType.Range_4_Volt:
                case CyEWaveRangeType.Range_4_Volt_Buffered:
                    range.MaxRange = CyParamConst.MAX_4_V;
                    range.DefaultValue = CyParamConst.DEF_4_V;
                    range.Units = CyWaveRange.UNITS_VOLT;
                    break;
                case CyEWaveRangeType.ISink_2040_uA:
                case CyEWaveRangeType.ISource_2040_uA:
                    range.MaxRange = CyParamConst.MAX_2040_uA;
                    range.DefaultValue = CyParamConst.DEF_2040_uA;
                    range.Units = CyWaveRange.UNITS_mA;
                    break;
                case CyEWaveRangeType.ISink_256_uA:
                case CyEWaveRangeType.ISource_256_uA:
                    range.MaxRange = CyParamConst.MAX_255_uA;
                    range.DefaultValue = CyParamConst.DEF_255_uA;
                    range.Units = CyWaveRange.UNITS_uA;
                    break;
                case CyEWaveRangeType.ISink_32_uA:
                case CyEWaveRangeType.ISource_32_uA:
                    range.MaxRange = CyParamConst.MAX_32_uA;
                    range.DefaultValue = CyParamConst.DEF_32_uA;
                    range.Units = CyWaveRange.UNITS_uA;
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }
            return range;
        }
    }
}
