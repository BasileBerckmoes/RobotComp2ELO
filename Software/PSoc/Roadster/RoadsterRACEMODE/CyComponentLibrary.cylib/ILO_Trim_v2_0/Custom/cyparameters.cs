using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ILO_Trim_v2_0
{
    public class CyParamNames
    {
        public const string INSTANCE_NAME = "INSTANCE_NAME";
        public const string IS_FIXED_FUNCTION = "FixedFunction";
    }

    public class CyParamRanges
    {
        public const UInt16 MIN_RATIO_FF = 50;
        public const UInt16 MAX_RATIO_FF = 32768;
        public const UInt16 MIN_RATIO_UDB = 50;
        public const UInt16 MAX_RATIO_UDB = 128;
    }

    public class CyParameters
    {
        public ICyInstQuery_v1 m_inst;
        public ICyTerminalQuery_v1 m_term;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 term)
        {
            m_inst = inst;
            m_term = term;
        }
        #endregion

        #region Class Properties
        public string InstanceName
        {
            get { return GetValue<string>(CyParamNames.INSTANCE_NAME); }
        }

        public bool IsFixedFunction
        {
            get { return GetValue<bool>(CyParamNames.IS_FIXED_FUNCTION); }
            set { SetValue(CyParamNames.IS_FIXED_FUNCTION, value); }
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_bGlobalEditMode)
            {
                if ((m_inst is ICyInstEdit_v1) == false) return;

                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet.ToString()))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
        }
        #endregion

        #region Auxiliary operations
        private const string REFERENCE_CLOCK = "ref_clk";
        private const string ILO_CLOCK = "_ILO_Clk";
        private const double FREQUENCY_UNKNOWN = -1.0;
        private const double EPS = 1E-6;

        public static bool IsFrequencyKnown(double frequency)
        {
            return Math.Abs(frequency - FREQUENCY_UNKNOWN) > EPS;
        }

        public double ReferenceClockKHz
        {
            get
            {
                List<CyClockData> clkdata = m_term.GetClockData(REFERENCE_CLOCK, 0);

                if (clkdata.Count > 0 && clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                }
                return FREQUENCY_UNKNOWN;
            }
        }

        public double ILOClockKHz
        {
            get
            {
                string clockName = InstanceName + ILO_CLOCK;
                double result = FREQUENCY_UNKNOWN;
                try
                {
                    ICyDesignQuery_v1 designQuery = m_inst.DesignQuery;
                    if (designQuery.ClockIDs != null)
                    {
                        double frequency;
                        byte exp;
                        string clockID = GetClockID(clockName);
                        if (string.IsNullOrEmpty(clockID) == false)
                        {
                            designQuery.GetClockActualFreq(clockID, out frequency, out exp);
                            result = (double)(frequency * Math.Pow(10, exp - 3));
                        }
                    }
                }
                catch { }
                return result;
            }
        }

        private string GetClockID(string clockName)
        {
            string clockID = string.Empty;
            try
            {
                ICyDesignQuery_v1 designQuery = m_inst.DesignQuery;
                List<string> clockIDs = new List<string>(designQuery.ClockIDs);

                for (int i = 0; i < clockIDs.Count; i++)
                {
                    if (designQuery.GetClockName(clockIDs[i]) == clockName)
                    {
                        clockID = clockIDs[i];
                        break;
                    }
                }
            }
            catch { }
            return clockID;
        }

        public static UInt32 GetRatio(double refFrequency, double iloFrequency)
        {
            UInt32 ratio = 0;
            if (IsFrequencyKnown(refFrequency) && IsFrequencyKnown(iloFrequency) && (iloFrequency > EPS))
            {
                ratio = (UInt32)(refFrequency / iloFrequency);
            }

            return ratio;
        }

        public static string GetFrequencyStr(double frequencyInKHz)
        {
            double frequencyInMHz = frequencyInKHz / 1000.0;

            return (frequencyInMHz >= 1.0) ? string.Format("{0:0.###} MHz", frequencyInMHz) :
                    string.Format("{0:0.###} kHz", frequencyInKHz);
        }
        #endregion

        public string RatioErrorDescription
        {
            get
            {
                double refFrequency = ReferenceClockKHz;
                double iloFrequency = ILOClockKHz;
                UInt32 ratio = GetRatio(refFrequency, iloFrequency);
                string errorMsg = string.Empty;
                UInt16 min = IsFixedFunction ? CyParamRanges.MIN_RATIO_FF : CyParamRanges.MIN_RATIO_UDB;
                UInt16 max = IsFixedFunction ? CyParamRanges.MAX_RATIO_FF : CyParamRanges.MAX_RATIO_UDB;

                if (IsFrequencyKnown(refFrequency) == false)
                {
                    errorMsg = Resources.RefClkDRCErrorMsg;
                }
                else if (IsFrequencyKnown(iloFrequency) && (ratio < min || ratio > max))
                {
                    double minRefFreq = min * iloFrequency;
                    double maxRefFreq = max * iloFrequency;

                    if (Math.Abs(1.0 - iloFrequency) < EPS || IsFixedFunction == false)
                    {
                        errorMsg = string.Format(Resources.RefClockRangeErrorMessage, GetFrequencyStr(iloFrequency),
                            GetFrequencyStr(minRefFreq), GetFrequencyStr(maxRefFreq));
                    }
                    else
                    {
                        errorMsg = string.Format(Resources.RefClockMinErrorMessage, GetFrequencyStr(iloFrequency),
                            GetFrequencyStr(minRefFreq));
                    }
                }

                return errorMsg;
            }
        }

        public string ILOFrequencyErrorDescription
        {
            get
            {
                bool isPSoC4 = m_inst.DeviceQuery.IsPSoC4;
                double iloFrequency = ILOClockKHz;
                if (IsFrequencyKnown(iloFrequency) == false)
                {
                    return string.Empty;
                }

                double[] supportedFrequencies = isPSoC4 ?
                    new double[] { 32.0 } :
                    new double[] { 1.0, 33.0, 100.0 };

                foreach (double frequency in supportedFrequencies)
                {
                    if (Math.Abs(frequency - iloFrequency) < EPS)
                    {
                        return string.Empty;
                    }
                }

                return isPSoC4 ? Resources.ILOFrequencyPSoC4ErrorMsg : Resources.ILOFrequencyPSoC3_5ErrorMsg;
            }
        }
    }
}
