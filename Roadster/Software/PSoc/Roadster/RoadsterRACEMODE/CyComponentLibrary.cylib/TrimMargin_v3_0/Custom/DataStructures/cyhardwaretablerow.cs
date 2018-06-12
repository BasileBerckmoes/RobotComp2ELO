/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Xml;
using System.Diagnostics;
using System.Xml.Serialization;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using TrimMargin_v3_0.Utils;

namespace TrimMargin_v3_0.DataStructures
{
    [Serializable]
    [XmlType("CyHardwareTableRow")]
    public class CyHardwareTableRow
    {
        #region Serializable members
        [XmlElement("m_vddio")]          // for compatibility with previous versions (1_30 or lower)
        public double? m_vOh;
        [XmlElement("m_controlVoltage")] // for compatibility with previous versions (1_30 or lower)
        public double? m_vAdj;
        [XmlElement("m_r1")]
        public double? m_r1;
        [XmlElement("m_r2")]
        public double? m_r2;
        [XmlElement("m_r3")]
        public double? m_r3;
        [XmlElement("m_calculatedR4")]   // for compatibility with previous versions (1_10 or lower)
        public double? m_r4;
        [XmlElement("m_maxRipple")]
        public double? m_maxRipple;
        [XmlElement("m_c1")]
        public double? m_c1;
        [XmlElement("m_r2En")]
        public bool? m_r2En = true;
        [XmlElement("m_r3En")]
        public bool? m_r3En = true;
        [XmlElement("m_r4En")]
        public bool? m_r4En = true;
        [XmlElement("m_c1En")]
        public bool? m_c1En = true;
        [XmlElement("m_resistorESeries")]
        public CyESeriesType? m_resistorESeries;
        [XmlElement("m_capacitorESeries")]
        public CyESeriesType? m_capacitorESeries;
        #endregion

        #region Non-serializable members
        [XmlIgnore]
        public double? m_calcR2;
        [XmlIgnore]
        public double? m_calcR3;
        [XmlIgnore]
        public double? m_calcR4;
        [XmlIgnore]
        public double? m_calcVRipple;
        [XmlIgnore]
        public double? m_calcC1;
        [XmlIgnore]
        public double? m_nominalPWM;
        #endregion

        #region Constructor(s)
        public CyHardwareTableRow()
        {
            this.m_vOh = CyConstants.VOH_DEFAULT;
            this.m_vAdj = CyConstants.VADJ_DEFAULT;
            this.m_maxRipple = CyConstants.MAXRIPPLE_DEFAULT;
            this.m_r1 = CyConstants.R1_DEFAULT;
            this.m_r2 = CyConstants.R2_DEFAULT;
            this.m_r3 = CyConstants.R3_DEFAULT;
            this.m_r4 = CyConstants.R4_DEFAULT;
            this.m_c1 = CyConstants.C1_DEFAULT;
            this.m_r2En = CyConstants.R2EN_DEFAULT;
            this.m_r3En = CyConstants.R3EN_DEFAULT;
            this.m_r4En = CyConstants.R4EN_DEFAULT;
            this.m_c1En = CyConstants.C1EN_DEFAULT;
            this.m_resistorESeries = CyConstants.RESISTORESERIES_DEFAULT;
            this.m_capacitorESeries = CyConstants.CAPACITORESERIES_DEFAULT;
        }

        public CyHardwareTableRow(CyHardwareTableRow row)
        {
            this.m_vOh = row.m_vOh;
            this.m_vAdj = row.m_vAdj;
            this.m_maxRipple = row.m_maxRipple;
            this.m_r1 = row.m_r1;
            this.m_r2 = row.m_r2;
            this.m_r3 = row.m_r3;
            this.m_r4 = row.m_r4;
            this.m_c1 = row.m_c1;
            this.m_r2En = row.m_r2En;
            this.m_r3En = row.m_r3En;
            this.m_r4En = row.m_r4En;
            this.m_c1En = row.m_c1En;
            this.m_resistorESeries = row.m_resistorESeries;
            this.m_capacitorESeries = row.m_capacitorESeries;
            this.m_calcR2 = row.m_calcR2;
            this.m_calcR3 = row.m_calcR3;
            this.m_calcR4 = row.m_calcR4;
            this.m_calcVRipple = row.m_calcVRipple;
            this.m_calcC1 = row.m_calcC1;
            this.m_nominalPWM = row.m_nominalPWM;
        }

        public static CyHardwareTableRow CreateDefaultRow()
        {
            return new CyHardwareTableRow();
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
            // Ignore voltages table fields
            if (IsFieldOwner(field) == false)
                return CyCustErr.Ok;

            CyRange range = CyEnumExtensions.GetRange(field);
            double? value = GetValueByField(field);
            if (value.HasValue == false || CyHelper.IsValueInRange(value.Value, range.Min, range.Max) == false)
            {
                string fmt = CyEnumExtensions.GetRangeErrorFmt(field);
                return new CyCustErr(String.Format(fmt, range.Min, range.Max));
            }
            return CyCustErr.Ok;
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
                    CyEFields.VhPwmOutput,
                    CyEFields.Vadj,
                    CyEFields.R1,
                    CyEFields.R2,
                    CyEFields.R3,
                    CyEFields.R4,
                    CyEFields.DesiredVoutRipple,
                    CyEFields.C1
                };
            }
        }

        /// <summary>
        /// Gets row field value by field type.
        /// </summary>
        private double? GetValueByField(CyEFields field)
        {
            switch (field)
            {
                case CyEFields.VhPwmOutput:
                    return m_vOh;
                case CyEFields.Vadj:
                    return m_vAdj;
                case CyEFields.R1:
                    return m_r1;
                case CyEFields.R2:
                    return m_r2;
                case CyEFields.R3:
                    return m_r3;
                case CyEFields.R4:
                    return m_r4;
                case CyEFields.DesiredVoutRipple:
                    return m_maxRipple;
                case CyEFields.C1:
                    return m_c1;
                default:
                    Debug.Fail(String.Format("Unhandled field {0}.", field));
                    return 0;
            }
        }
        #endregion
    }
}