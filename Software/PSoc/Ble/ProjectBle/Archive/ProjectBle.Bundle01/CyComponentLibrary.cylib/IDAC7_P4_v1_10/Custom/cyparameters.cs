/*******************************************************************************
* Copyright 2015-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;
using System.Diagnostics;

namespace IDAC7_P4_v1_10
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
        public const double RANGE_4_76_COEFF = 0.0375;
        // RANGE_9_52_COEFF = 0.07496 because of 0.07496 * 127 = 9.51992. This is more precise than 0.075 * 127 = 9.525
        public const double RANGE_9_52_COEFF = 0.07496;
        public const double RANGE_38_1_COEFF = 0.3;
        public const double RANGE_76_2_COEFF = 0.6;
        public const double RANGE_152_4_COEFF = 1.2;
        public const double RANGE_304_8_COEFF = 2.4;
        public const double RANGE_609_6_COEFF = 4.8;

        public const UInt16 IDAC_CURR_MIN = 0;
        public const double IDAC_CURR_4_76_MAX = 4.76;
        public const double IDAC_CURR_9_52_MAX = 9.52;
        public const double IDAC_CURR_38_1_MAX = 38.1;
        public const double IDAC_CURR_76_2_MAX = 76.2;
        public const double IDAC_CURR_152_4_MAX = 152.4;
        public const double IDAC_CURR_304_8_MAX = 304.8;
        public const double IDAC_CURR_609_6_MAX = 609.6;

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
        [Description("0-4.76uA (37.5nA/bit)")]
        RNG_4_76UA = 4,
        [Description("0-9.52uA (75 nA/bit)")]
        RNG_9_52UA = 12,
        [Description("0-38.1uA (300nA/bit)")]
        RNG_38_1UA = 5,
        [Description("0-76.2uA (600nA/bit)")]
        RNG_76_2UA = 13,
        [Description("0-152.4uA (1.2 uA/bit)")]
        RNG_152_4UA = 7,
        [Description("0-304.8uA (2.4uA/bit)")]
        RNG_304_8UA = 6,
        [Description("0-609.6uA (4.8uA/bit)")]
        RNG_609_6UA = 14
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
        
        public bool IsS8CSDV2_Ver2
        {
            get { return InstQuery.DeviceQuery.GetFeatureVersion("m0s8csdv2") > 1; }
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
                case CyEIDACRangeType.RNG_4_76UA:
                    return CyParamRange.IDAC_CURR_4_76_MAX;
                case CyEIDACRangeType.RNG_9_52UA:
                    return CyParamRange.IDAC_CURR_9_52_MAX;
                case CyEIDACRangeType.RNG_38_1UA:
                    return CyParamRange.IDAC_CURR_38_1_MAX;
                case CyEIDACRangeType.RNG_76_2UA:
                    return CyParamRange.IDAC_CURR_76_2_MAX;
                case CyEIDACRangeType.RNG_152_4UA:
                    return CyParamRange.IDAC_CURR_152_4_MAX;
                case CyEIDACRangeType.RNG_304_8UA:
                    return CyParamRange.IDAC_CURR_304_8_MAX;
                case CyEIDACRangeType.RNG_609_6UA:
                    return CyParamRange.IDAC_CURR_609_6_MAX;

                default:
                    Debug.Fail("GetMaxCurrentValue() not handled.");
                    return 0;
            }
        }

        public double GetRangeCoeff()
        {
            if (IDACRange == CyEIDACRangeType.RNG_4_76UA)
                return CyParamRange.RANGE_4_76_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_9_52UA)
                return CyParamRange.RANGE_9_52_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_38_1UA)
                return CyParamRange.RANGE_38_1_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_76_2UA)
                return CyParamRange.RANGE_76_2_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_152_4UA)
                return CyParamRange.RANGE_152_4_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_304_8UA)
                return CyParamRange.RANGE_304_8_COEFF;
            else if (IDACRange == CyEIDACRangeType.RNG_609_6UA)
                return CyParamRange.RANGE_609_6_COEFF;
            else
            {
                Debug.Fail("GetRangeCoeff() not handled.");
                return CyParamRange.RANGE_609_6_COEFF;
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
