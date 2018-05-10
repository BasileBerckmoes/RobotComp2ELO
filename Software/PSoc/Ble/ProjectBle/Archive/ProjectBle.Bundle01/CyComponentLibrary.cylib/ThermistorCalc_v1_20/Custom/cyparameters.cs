/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace ThermistorCalc_v1_20
{
    public class CyParamRanges
    {
        public const uint MIN_REFERENCE_RESISTANCE = 1;
        public const uint MAX_REFERENCE_RESISTANCE = 1000000000;

        public const int MIN_TEMPERATURE = -80;
        public const int MAX_TEMPERATURE = 325;

        public const uint MIN_RESISTANCE = 1;
        public const uint MAX_RESISTANCE = 1000000;

        public const int MAX_LUT_SIZE = 3300;
    }

    public class CyParamNames
    {
        public const string IMPLEMENTATION = "Implementation";
        public const string REFERENCE_RESISTANCE = "ReferenceResistor";
        public const string REFERENCE_RESISTANCE_SCALED = "RefResistor";
        public const string REF_RES_SHIFT = "RefResShift";
        public const string CALCULATION_RESOLUTION = "Accuracy";

        public const string MIN_RESISTANCE = "MinRes";
        public const string MID_RESISTANCE = "MidRes";
        public const string MAX_RESISTANCE = "MaxRes";

        public const string MIN_TEMPERATURE = "MinTemp";
        public const string MID_TEMPERATURE = "MidTemp";
        public const string MAX_TEMPERATURE = "MaxTemp";

        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }

    public enum CyEImplementation { Equation = 0, LUT = 1 };
    public enum CyECalcResolution { Resolution_0_01 = 1, Resolution_0_05 = 5, Resolution_0_1 = 10, Resolution_0_5 = 50,
        Resolution_1 = 100, Resolution_2 = 200 };

    public class CyParameters
    {
        public ICyInstQuery_v1 m_inst;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        private CyResolution m_calcResolution;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;

            m_calcResolution = new CyResolution(this, CyParamNames.CALCULATION_RESOLUTION);
        }
        #endregion

        public static double ToKelvin(double celsius)
        {
            const double ZERO_CELSIUS_TO_KELVIN = 273.15;
            return celsius + ZERO_CELSIUS_TO_KELVIN;
        }

        #region Getting Parameters
        public T GetValue<T>(string paramName)
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
        public void SetValue<T>(string paramName, T value)
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

        #region Steinhart-Hart equation
        public double CubeRoot(double val)
        {
            double pow = 1.0 / 3.0;
            return (val < 0.0) ? - Math.Pow(Math.Abs(val), pow) : Math.Pow(val, pow);
        }

        public void CalculateSteinhartHartCoefficients(out double a, out double b, out double c)
        {
            double x1 = 1 / MinTemperatureK;
            double x2 = 1 / MidTemperatureK;
            double x3 = 1 / MaxTemperatureK;

            double y1 = Math.Log(MinResistance);
            double y2 = Math.Log(MidResistance);
            double y3 = Math.Log(MaxResistance);

            c = (x3 * (y1 - y2) - x1 * (y1 - y2) + y1 * x1 - y1 * x2 - y3 * x1 + y3 * x2) /
                (Math.Pow(y3, 3) * (y1 - y2) - y1 * Math.Pow(y2, 3) + Math.Pow(y1, 4) - Math.Pow(y1, 3) * (y1 - y2) +
                y3 * Math.Pow(y2, 3) - y3 * Math.Pow(y1, 3));

            b = (x1 - x2 + c * Math.Pow(y2, 3) - c * Math.Pow(y1, 3)) / (y1 - y2);

            a = x2 - b * y2 - c * Math.Pow(y2, 3);
        }

        public double[,] GenerateLUT()
        {
            const double EPS = 1e-10;

            double a, b, c;
            CalculateSteinhartHartCoefficients(out a, out b, out c);

            int n = LUTSize;
            double[,] lookUpTable = new double[n, 2];

            double t = MinTemperature;
            double resolution = CalculationResolution.Value;
            for (int i = 0; i < n; i++)
            {
                lookUpTable[i, 1] = t;
                double val = 0.0;
                if (Math.Abs(c) > EPS)
                {
                    double y = (a - 1 / CyParameters.ToKelvin(t)) / c;
                    double tmp = Math.Pow(b / (3 * c), 3) + Math.Pow(y, 2) / 4;
                    if (tmp >= 0.0)
                    {
                        double x = Math.Sqrt(tmp);
                        val = Math.Exp(CubeRoot(x - y / 2.0) - CubeRoot(x + y / 2.0));
                    }
                }
                lookUpTable[i, 0] = val;

                t += resolution;
            }

            return lookUpTable;
        }
        #endregion

        #region Class Properties
        public string InstanceName
        {
            get { return GetValue<string>(CyParamNames.INSTANCE_NAME); }
        }

        public CyEImplementation Implementation
        {
            get { return GetValue<CyEImplementation>(CyParamNames.IMPLEMENTATION); }
            set { SetValue(CyParamNames.IMPLEMENTATION, value); }
        }

        public UInt32 ReferenceResistance
        {
            get { return GetValue<UInt32>(CyParamNames.REFERENCE_RESISTANCE); }
            set 
            { 
                SetValue(CyParamNames.REFERENCE_RESISTANCE, value);
                UInt32 refResScaled = value;
                byte refResShift = 0;
                while (refResScaled > UInt16.MaxValue)
                {
                    refResScaled /= 2;
                    refResShift++;
                }
                SetValue(CyParamNames.REFERENCE_RESISTANCE_SCALED, (UInt16)refResScaled);
                SetValue(CyParamNames.REF_RES_SHIFT, refResShift);
            }
        }

        public CyResolution CalculationResolution
        {
            get { return m_calcResolution; }
        }

        public UInt32 MinResistance
        {
            get { return GetValue<UInt32>(CyParamNames.MIN_RESISTANCE); }
            set { SetValue(CyParamNames.MIN_RESISTANCE, value); }
        }

        public UInt32 MidResistance
        {
            get { return GetValue<UInt32>(CyParamNames.MID_RESISTANCE); }
            set { SetValue(CyParamNames.MID_RESISTANCE, value); }
        }

        public UInt32 MaxResistance
        {
            get { return GetValue<UInt32>(CyParamNames.MAX_RESISTANCE); }
            set { SetValue(CyParamNames.MAX_RESISTANCE, value); }
        }

        public short MinTemperature
        {
            get { return GetValue<short>(CyParamNames.MIN_TEMPERATURE); }
            set { SetValue(CyParamNames.MIN_TEMPERATURE, value); }
        }

        public short MidTemperature
        {
            get { return GetValue<short>(CyParamNames.MID_TEMPERATURE); }
            set { SetValue(CyParamNames.MID_TEMPERATURE, value); }
        }

        public short MaxTemperature
        {
            get { return GetValue<short>(CyParamNames.MAX_TEMPERATURE); }
            set { SetValue(CyParamNames.MAX_TEMPERATURE, value); }
        }

        // Additional properties
        public double MinTemperatureK
        {
            get { return ToKelvin(MinTemperature); }
        }

        public double MidTemperatureK
        {
            get { return ToKelvin(MidTemperature); }
        }

        public double MaxTemperatureK
        {
            get { return ToKelvin(MaxTemperature); }
        }

        public int LUTSize
        {
            get { return (int)(Math.Abs(MaxTemperature - MinTemperature) / CalculationResolution.Value + 1); }
        }
        #endregion
    }

    public class CyEnum<T>
    {
        CyParameters m_prm;
        string m_paramName;

        public CyEnum(CyParameters prm, string paramName)
        {
            m_prm = prm;
            m_paramName = paramName;
        }

        public T Value
        {
            get
            {
                return m_prm.GetValue<T>(m_paramName);
            }
            set
            {
                m_prm.SetValue<T>(m_paramName, value);
            }
        }

        /// <summary>
        /// Get the enum item value by parameter name and enum item description.
        /// </summary>
        /// <returns>Enum item value that has specified description in symbol</returns>
        public string Description
        {
            get
            {
                string res = string.Empty;

                CyCompDevParam param = m_prm.m_inst.GetCommittedParam(m_paramName);
                if (param != null)
                {
                    m_prm.m_inst.ResolveEnumParamToDisplay(param, out res);
                }

                return res;
            }
            set
            {
                string enumItemName = m_prm.m_inst.ResolveEnumDisplayToId(m_paramName, value);

                try
                {
                    Value = (T)Enum.Parse(typeof(T), enumItemName);
                }
                catch { }
            }
        }

        /// <summary>
        /// This method returns array of strings - descriptions of the enumeration that is a type of the parameter with
        /// name specified in paramName.
        /// </summary>
        /// <returns>List of the enumeration descriptions</returns>
        public string[] EnumDescriptionsList
        {
            get
            {
                return new List<string>(m_prm.m_inst.GetPossibleEnumValues(m_paramName)).ToArray();
            }
        }
    }

    public class CyResolution : CyEnum<CyECalcResolution>
    {
        private const double CALC_RESOLUTION_MULTPLIER = 100.0;

        public CyResolution(CyParameters parameters, string paramName)
            : base(parameters, paramName)
        { }

        new public double Value
        {
            get
            {
                return ((int)base.Value) / CALC_RESOLUTION_MULTPLIER;
            }
        }
    }
}
