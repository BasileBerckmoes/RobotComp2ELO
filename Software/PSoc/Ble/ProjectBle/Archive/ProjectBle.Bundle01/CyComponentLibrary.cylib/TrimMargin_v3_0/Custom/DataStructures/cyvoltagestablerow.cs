/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using System.Xml.Serialization;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using TrimMargin_v3_0.Utils;

namespace TrimMargin_v3_0.DataStructures
{
    [Serializable]
    [XmlType("CyVoltagesTableRow")]
    public class CyVoltagesTableRow
    {
        #region Serializable members
        [XmlElement("m_converterName")]
        public string m_converterName;
        [XmlElement("m_nominalVoltage")]
        public double? m_nominalVoltage;
        [XmlElement("m_minVoltage")]
        public double? m_minVoltage;
        [XmlElement("m_maxVoltage")]
        public double? m_maxVoltage;
        [XmlElement("m_startupVoltage")]
        public double? m_startupVoltage;
        [XmlElement("m_marginLow")]
        public double? m_marginLow;
        [XmlElement("m_marginHigh")]
        public double? m_marginHigh;
        [XmlElement("ControlSampleTime")]
        public double? ControlSampleTime { get; set; }
        [XmlElement("Feedback")]
        public CyEFeedback Feedback { get; set; }
        #endregion

        #region Constructor(s)
        public CyVoltagesTableRow()
        {
            this.m_converterName = String.Empty;
            this.m_nominalVoltage = CyConstants.NOMINAL_VOLTAGE_DEFAULT;
            this.m_maxVoltage = CyConstants.MAX_VOLTAGE_DEFAULT;
            this.m_minVoltage = CyConstants.MIN_VOLTAGE_DEFAULT;
            this.m_startupVoltage = null; // should be null to be set after deserialization by migration method
            this.ControlSampleTime = CyConstants.CONTROL_SAMPLE_TIME_DEFAULT;
            this.Feedback = CyConstants.FEEDBACK_DEFAULT;
            this.MarginHighPercentage = null; // should be null to be set after deserialization based on m_marginHigh
            this.MarginLowPercentage = null; // should be null to be set after deserialization based on m_marginLow
        }

        public CyVoltagesTableRow(CyVoltagesTableRow row)
        {
            this.m_converterName = row.m_converterName;
            this.m_nominalVoltage = row.m_nominalVoltage;
            this.MarginHighPercentage = row.MarginHighPercentage;
            this.MarginLowPercentage = row.MarginLowPercentage;
            this.MarginHigh = row.MarginHigh;
            this.MarginLow = row.MarginLow;
            this.m_maxVoltage = row.m_maxVoltage;
            this.m_minVoltage = row.m_minVoltage;
            this.m_startupVoltage = row.m_startupVoltage;
            this.ControlSampleTime = row.ControlSampleTime;
            this.Feedback = row.Feedback;
        }

        public static CyVoltagesTableRow CreateDefaultRow()
        {
            CyVoltagesTableRow row = new CyVoltagesTableRow();
            row.m_startupVoltage = CyConstants.STARTUP_VOLTAGE_DEFAULT;
            row.MarginHighPercentage = CyConstants.MARGIN_HIGH_PERCENTAGE_DEFAULT;
            row.MarginLowPercentage = CyConstants.MARGIN_LOW_PERCENTAGE_DEFAULT;
            return row;
        }
        #endregion

        #region Non-serializable members
        [XmlIgnore]
        private double? m_marginLowPercentage;
        [XmlIgnore]
        private double? m_marginHighPercentage;
        [XmlIgnore]
        public double? MarginLow
        {
            get
            {
                if (m_marginLow == null)
                    m_marginLow = MarginPercentageToVoltage(this.m_nominalVoltage, this.m_marginLowPercentage);
                return m_marginLow;
            }
            set { m_marginLow = value; }
        }
        [XmlIgnore]
        public double? MarginHigh
        {
            get
            {
                if (m_marginHigh == null)
                    m_marginHigh = MarginPercentageToVoltage(this.m_nominalVoltage, this.m_marginHighPercentage);
                return m_marginHigh;
            }
            set { m_marginHigh = value; }
        }
        [XmlIgnore]
        public double? MarginLowPercentage
        {
            get
            {
                if (m_marginLowPercentage == null)
                    m_marginLowPercentage = GetMarginPercentage(this.m_nominalVoltage, this.m_marginLow);
                return m_marginLowPercentage;
            }
            set { m_marginLowPercentage = value; }
        }
        [XmlIgnore]
        public double? MarginHighPercentage
        {
            get
            {
                if (m_marginHighPercentage == null)
                    m_marginHighPercentage = GetMarginPercentage(this.m_nominalVoltage, this.m_marginHigh);
                return m_marginHighPercentage;
            }
            set { m_marginHighPercentage = value; }
        }
        #endregion

        #region Public methods
        public static double? MarginPercentageToVoltage(double? nominalVoltage, double? marginPercent)
        {
            return nominalVoltage + nominalVoltage * marginPercent / 100;
        }

        public static string GetVoltageIndexStr(int i)
        {
            return "V" + i.ToString();
        }
        #endregion

        #region Calculation methods
        private static double? GetMarginPercentage(double? nominalVoltage, double? margin)
        {
            double? percentage = null;
            try
            {
                percentage = margin * 100 / nominalVoltage - 100;
                percentage = Math.Round(percentage.Value, 3);
            }
            catch
            {
                percentage = null;
            }
            finally
            {
                // In case of dividing by zero returns Infinity, the resulting value should be null
                if (CyHelper.IsNullOrInfinity(percentage))
                    percentage = null;
            }
            return percentage;
        }
        #endregion

        #region Validation
        /// <summary>
        /// Validates all fields whether their value is in range.
        /// </summary>
        internal IEnumerable<CyCustErr> ValidateRange()
        {
            for (int i = 0; i < Fields.Length; i++)
            {
                if (Fields[i] == CyEFields.ConverterName)
                    continue;

                CyCustErr error = ValidateRange(Fields[i]);
                if (error.IsNotOk)
                    yield return error;
            }
        }

        /// <summary>
        /// Validates the specified field whether its value is in range.
        /// </summary>
        internal CyCustErr ValidateRange(CyEFields field)
        {
            return ValidateRange(field, null);
        }

        /// <summary>
        /// Validates the specified field whether its value is in range. 
        /// This method intended for the real-time calculated parameters.
        /// </summary>
        internal CyCustErr ValidateRange(CyEFields field, double? value)
        {
            // Ignore hardware table fields
            if (IsFieldOwner(field) == false)
                return CyCustErr.Ok;

            CyRange range = CyEnumExtensions.GetRange(field);
            if (value == null)
            {
                value = (double?)GetValueByField(field);
            }

            if (value.HasValue == false || CyHelper.IsValueInRange(value.Value, range.Min, range.Max) == false)
            {
                string fmt = CyEnumExtensions.GetRangeErrorFmt(field);
                return new CyCustErr(String.Format(fmt, range.Min, range.Max));
            }

            return CyCustErr.Ok;
        }

        /// <summary>
        /// Does all types sanity check.
        /// </summary>
        internal Dictionary<CyESanityCheck, CyCustErr> SanityCheck(double? calcMinVoltage, double? calcMaxVoltage)
        {
            Dictionary<CyESanityCheck, CyCustErr> err = new Dictionary<CyESanityCheck, CyCustErr>();
            foreach (CyESanityCheck item in Enum.GetValues(typeof(CyESanityCheck)))
            {
                // VStartupToMaxVoltage check should be done only if MinVoltageToVStartup succeeds
                if (item == CyESanityCheck.VStartupToMaxVoltage && err[CyESanityCheck.MinVoltageToVStartup].IsNotOk)
                    continue;

                err.Add(item, SanityCheck(item, calcMinVoltage, calcMaxVoltage));
            }
            return err;
        }

        /// <summary>
        /// Does sanity check of specified type.
        /// </summary>
        private CyCustErr SanityCheck(CyESanityCheck sanityCheckType, double? calcMinVoltage, double? calcMaxVoltage)
        {
            CyCustErr error = CyCustErr.Ok;
            switch (sanityCheckType)
            {
                case CyESanityCheck.MinMaxVoltageSanity:
                    if (CyHelper.LessThan(m_minVoltage, m_maxVoltage))
                    {
                        error = new CyCustErr(Resources.MinMaxVoltageSanityCheck);
                    }
                    break;

                case CyESanityCheck.MinVoltageSanity:
                    if (CyHelper.GreaterThan(calcMinVoltage, MarginLow))
                    {
                        error = new CyCustErr(Resources.MinVoltageSanityCheck);
                    }
                    break;

                case CyESanityCheck.MarginLowVoltage:
                    if (CyHelper.GreaterThan(MarginLow, m_nominalVoltage))
                    {
                        error = new CyCustErr(Resources.MarginLowVoltageSanityCheck);
                    }
                    break;

                case CyESanityCheck.NominalOutputVoltage:
                    if (CyHelper.GreaterThan(m_nominalVoltage, MarginHigh))
                    {
                        error = new CyCustErr(Resources.NominalOutputVoltageSanityCheck);
                    }
                    break;

                case CyESanityCheck.MarginHighVoltage:
                    if (CyHelper.GreaterThan(MarginHigh, calcMaxVoltage))
                    {
                        error = new CyCustErr(Resources.MarginHighVoltageSanityCheck);
                    }
                    break;

                case CyESanityCheck.MinVoltageToVStartup:
                    if (CyHelper.GreaterThan(calcMinVoltage, m_startupVoltage))
                    {
                        error = new CyCustErr(Resources.MinVoltageToVStartupSanityCheck);
                    }
                    break;

                case CyESanityCheck.VStartupToMaxVoltage:
                    if (CyHelper.GreaterThan(m_startupVoltage, calcMaxVoltage))
                    {
                        error = new CyCustErr(Resources.VStartupToMaxVoltageSanityCheck);
                    }
                    break;

                default:
                    break;
            }

            return error;
        }

        /// <summary>
        /// Gets a value that indicates whether any field in the row contains a null.
        /// </summary>
        internal bool ContainsNull
        {
            get
            {
                foreach (CyEFields item in Fields)
                {
                    if (GetValueByField(item) == null)
                        return true;
                }
                return false;
            }
        }
        #endregion

        #region Maps
        /// <summary>
        /// Gets the value indicating whether the specified field belongs to the row.
        /// </summary>
        internal static bool IsFieldOwner(CyEFields field)
        {
            for (int i = 0; i < Fields.Length; i++)
            {
                if (Fields[i] == field)
                    return true;
            }
            return false;
        }

        /// <summary>
        /// Gets fields array that belongs to the row.
        /// </summary>
        internal static CyEFields[] Fields
        {
            get
            {
                return new CyEFields[] 
                {
                    CyEFields.ConverterName,
                    CyEFields.NominalVoltage,
                    CyEFields.MinVoltage,
                    CyEFields.MaxVoltage,
                    CyEFields.StartupVoltage,
                    CyEFields.MarginLowPercent,
                    CyEFields.MarginHighPercent,
                    CyEFields.MarginLow,
                    CyEFields.MarginHigh,
                    CyEFields.ControlSampleTime
                };
            }
        }

        /// <summary>
        /// Gets row field value by field type.
        /// </summary>
        private object GetValueByField(CyEFields field)
        {
            switch (field)
            {
                case CyEFields.ConverterName:
                    return m_converterName;
                case CyEFields.NominalVoltage:
                    return m_nominalVoltage;
                case CyEFields.MinVoltage:
                    return m_minVoltage;
                case CyEFields.MaxVoltage:
                    return m_maxVoltage;
                case CyEFields.StartupVoltage:
                    return m_startupVoltage;
                case CyEFields.MarginLowPercent:
                    return MarginLowPercentage;
                case CyEFields.MarginHighPercent:
                    return MarginHighPercentage;
                case CyEFields.MarginLow:
                    return MarginLow;
                case CyEFields.MarginHigh:
                    return MarginHigh;
                case CyEFields.ControlSampleTime:
                    return ControlSampleTime;
                default:
                    Debug.Fail(String.Format("Unhandled field {0}.", field));
                    return 0;
            }
        }
        #endregion
    }
}