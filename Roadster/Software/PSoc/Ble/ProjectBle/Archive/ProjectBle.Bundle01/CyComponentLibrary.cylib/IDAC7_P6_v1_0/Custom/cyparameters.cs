/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;
using System.Diagnostics;

namespace IDAC7_P6_v1_0
{
    #region Component parameters names
    public class CyParamName
    {
        public const string PARAMNAME_POLARITY = "Polarity";
        public const string PARAMNAME_VALUE = "Value";
        public const string PARAMNAME_RANGE = "IDACRange";
    }
    #endregion

    #region Parameters ranges
    public class CyParamRange
    {
        public const double RANGE_4_96_COEFF = 0.0390625;
        public const double RANGE_9_92_COEFF = 0.078125;
        public const double RANGE_39_69_COEFF = 0.3125;
        public const double RANGE_79_38_COEFF = 0.625;
        public const double RANGE_317_5_COEFF = 2.5;
        public const double RANGE_635_0_COEFF = 5.0;

        public const UInt16 IDAC_CURR_MIN = 0;
        public const double IDAC_CURR_4_96_MAX = 4.96;
        public const double IDAC_CURR_9_92_MAX = 9.922;
        public const double IDAC_CURR_39_69_MAX = 39.69;
        public const double IDAC_CURR_79_38_MAX = 79.38;
        public const double IDAC_CURR_317_5_MAX = 317.5;
        public const double IDAC_CURR_635_0_MAX = 635.0;

        public const UInt16 IDAC_CONV_MIN = 0;
        public const UInt16 IDAC_CONV_7_BIT_MAX = 127;

        public const byte MAX_7BIT_VALUE = 127;
    }
    #endregion

    #region Component enums
    public enum CyEPolarityType
    {
        [Description("Positive (Source)")]
        POL_SOURCE,
        [Description("Negative (Sink)")]
        POL_SINK
    }

    public enum CyEIDACRangeType
    {
        [Description("0-4.96uA (39.06nA/bit)")]
        RNG_4_96UA = 4,
        [Description("0-9.922uA (78.125 nA/bit)")]
        RNG_9_92UA = 12,
        [Description("0-39.69uA (312.5nA/bit)")]
        RNG_39_69UA = 5,
        [Description("0-79.38uA (625nA/bit)")]
        RNG_79_38UA = 13,
        [Description("0-317.5uA (2.5uA/bit)")]
        RNG_317_5UA = 6,
        [Description("0-635.0uA (5.0uA/bit)")]
        RNG_635_0UA = 14
    }
    #endregion

    public class CyParameters
    {
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }
        #endregion

        #region Class properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public CyEPolarityType Polarity
        {
            get
            {
                return GetValue<CyEPolarityType>(CyParamName.PARAMNAME_POLARITY);
            }
            set
            {
                SetValue(CyParamName.PARAMNAME_POLARITY, value);
            }
        }

        public byte IDACValue
        {
            get
            {
                return GetValue<byte>(CyParamName.PARAMNAME_VALUE);
            }
            set
            {
                SetValue(CyParamName.PARAMNAME_VALUE, value);
            }
        }

        public CyEIDACRangeType IDACRange
        {
            get
            {
                return GetValue<CyEIDACRangeType>(CyParamName.PARAMNAME_RANGE);
            }
            set
            {
                SetValue(CyParamName.PARAMNAME_RANGE, value);
            }
        }
        #endregion

        #region Getting parameters
        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null) return default(T);
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        public double GetMaxCurrentValue()
        {
            switch (IDACRange)
            {
                case CyEIDACRangeType.RNG_4_96UA:
                    return CyParamRange.IDAC_CURR_4_96_MAX;
                case CyEIDACRangeType.RNG_9_92UA:
                    return CyParamRange.IDAC_CURR_9_92_MAX;
                case CyEIDACRangeType.RNG_39_69UA:
                    return CyParamRange.IDAC_CURR_39_69_MAX;
                case CyEIDACRangeType.RNG_79_38UA:
                    return CyParamRange.IDAC_CURR_79_38_MAX;
                case CyEIDACRangeType.RNG_317_5UA:
                    return CyParamRange.IDAC_CURR_317_5_MAX;
                case CyEIDACRangeType.RNG_635_0UA:
                    return CyParamRange.IDAC_CURR_635_0_MAX;

                default:
                    Debug.Fail("GetMaxCurrentValue() not handled.");
                    return 0;
            }
        }

        public double GetRangeCoeff()
        {
            if (IDACRange == CyEIDACRangeType.RNG_4_96UA)
                return CyParamRange.RANGE_4_96_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_9_92UA)
                return CyParamRange.RANGE_9_92_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_39_69UA)
                return CyParamRange.RANGE_39_69_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_79_38UA)
                return CyParamRange.RANGE_79_38_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_317_5UA)
                return CyParamRange.RANGE_317_5_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_635_0UA)
                return CyParamRange.RANGE_635_0_COEFF;
            else
            {
                Debug.Fail("GetRangeCoeff() not handled.");
                return CyParamRange.RANGE_635_0_COEFF;
            }
        }

        private UInt16 GetConvertedValue(double value)
        {
            double dRes = value / GetRangeCoeff();

            if (dRes > CyParamRange.IDAC_CONV_7_BIT_MAX)
                return CyParamRange.IDAC_CONV_7_BIT_MAX;
            else
                return (UInt16)Math.Round(dRes);
        }

        public string GetConvertedValue(string text)
        {
            double value;
            double.TryParse(text, out value);
            return GetConvertedValue(value).ToString("X2");
        }

        public string GetCurrentValue(string text)
        {
            int value = 0;

            try
            {
                value = Convert.ToInt32(text, 16);
            }
            catch
            {
            }

            return (value * GetRangeCoeff()).ToString();
        }
        #endregion

        #region Setting parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_instEdit != null && m_globalEditMode)
            {
                string valueToSet = (value == null) ? String.Empty : value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }
        #endregion
    }
}
