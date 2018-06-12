/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Reflection;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace PWM_v3_30
{
    #region Parameter names
    public class CyParamNames
    {
        public const string PWM_MODE = "PWMMode";
        public const string DEAD_BAND = "DeadBand";
        public const string DITHER_OFFSET = "DitherOffset";
        public const string FIXED_FUNCTION = "FixedFunction";
        public const string RESOLUTION = "Resolution";
        public const string PERIOD = "Period";
        public const string COMPARE_VALUE_1 = "CompareValue1";
        public const string COMPARE_VALUE_2 = "CompareValue2";
        public const string COMPARE_TYPE_1 = "CompareType1";
        public const string COMPARE_TYPE_2 = "CompareType2";
        public const string DEAD_TIME = "DeadTime";
        public const string ENABLE_MODE = "EnableMode";
        public const string RUN_MODE = "RunMode";
        public const string TRIGGER_MODE = "TriggerMode";
        public const string KILL_MODE = "KillMode";
        public const string CAPTURE_MODE = "CaptureMode";
        public const string USE_INTERRUPT = "UseInterrupt";
        public const string INTERRUPT_ON_KILL = "InterruptOnKill";
        public const string INTERRUPT_ON_CMP_1 = "InterruptOnCMP1";
        public const string INTERRUPT_ON_CMP_2 = "InterruptOnCMP2";
        public const string INTERRUPT_ON_TC = "InterruptOnTC";
        public const string MINIMUM_KILL_TIME = "MinimumKillTime";
    }
    #endregion

    #region Parameter ranges
    public class CyParamRanges
    {
        public const UInt16 PERIODMIN = 0;
        public const UInt16 PERIODMAX8CA = 254;
        public const UInt16 PERIODMAX8 = 255;
        public const UInt16 PERIODMAX16CA = 65534;
        public const UInt16 PERIODMAX16 = 65535;

        public const int DEADBANDFFCOUNTS_MIN = 0;
        public const int DEADBANDFFCOUNTS_MAX = 3;
        public const int DEADBANDCOUNTS_MIN = 2;
        public const int DEADBANDCOUNTS_4MAX = 4;
        public const int DEADBANDCOUNTS_256MAX = 256;

        public const byte MINKILLTIME_MIN = 1;
        public const byte MINKILLTIME_MAX = 255;
    }
    #endregion

    #region Parameter types
    public enum CyECaptureMode
    {
        [Description("None")]
        B_PWM__None,
        [Description("Rising Edge")]
        B_PWM__RisingEdge,
        [Description("Falling Edge")]
        B_PWM__FallingEdge,
        [Description("Either Edge")]
        B_PWM__EitherEdge
    }
    public enum CyECompareType
    {
        [Description("Equal")]
        B_PWM__Equal,
        [Description("Less")]
        B_PWM__Less_Than,
        [Description("Less or Equal")]
        B_PWM__Less_Than_Or_Equal,
        [Description("Greater")]
        B_PWM__Greater_Than,
        [Description("Greater or Equal")]
        B_PWM__Greater_Than_Or_Equal_To,
        [Description("Firmware Control")]
        B_PWM__Firmware
    }
    public enum CyEEnableMode
    {
        [Description("Software Only")]
        B_PWM__Software_Only,
        [Description("Hardware Only")]
        B_PWM__Hardware_Only,
        [Description("Software and Hardware")]
        B_PWM__Software_And_Hardware
    }
    public enum CyEPwmMode
    {
        [Description("One Output")]
        B_PWM__One_Output,
        [Description("Two Outputs")]
        B_PWM__Two_Outputs,
        [Description("Dual Edge")]
        B_PWM__Dual_Edge,
        [Description("Center Align")]
        B_PWM__Center_Align,
        [Description("Hardware Select")]
        B_PWM__HardwareSelect,
        [Description("Dither")]
        B_PWM__Dither
    }
    public enum CyERunMode
    {
        [Description("Continuous")]
        B_PWM__Continous,
        [Description("One Shot with Single Trigger")]
        B_PWM__OneShot_SingleTrigger,
        [Description("One Shot with Multi Trigger")]
        B_PWM__OneShot_MultiTrigger
    }
    public enum CyEKillMode
    {
        [Description("Disabled")]
        B_PWM__Disabled,
        [Description("Asynchronous")]
        B_PWM__Asynchronous,
        [Description("Single Cycle")]
        B_PWM__SingleCycle,
        [Description("Latched")]
        B_PWM__Latched,
        [Description("Minimum Time")]
        B_PWM__MinTime
    }
    public enum CyETriggerMode
    {
        [Description("None")]
        B_PWM__TMNone,
        [Description("Rising Edge")]
        B_PWM__TMRisingEdge,
        [Description("Falling Edge")]
        B_PWM__TMFallingEdge,
        [Description("Either Edge")]
        B_PWM__TMEitherEdge
    }
    public enum CyEDeadBandMode
    {
        [Description("Disabled")]
        B_PWM__DBMDisabled,
        [Description("2-4 Clock Cycles")]
        B_PWM__DBM_2_4_Clocks,
        [Description("2-256 Clock Cycles")]
        B_PWM__DBM_256_Clocks
    }
    public enum CyEDitherOffset
    {
        [Description("0.00")]
        B_PWM__DO0,
        [Description("0.25")]
        B_PWM__DO25,
        [Description("0.50")]
        B_PWM__DO50,
        [Description("0.75")]
        B_PWM__DO75
    }
    public enum CyEDitherAlign
    {
        [Description("Left Aligned")]
        LeftAligned,
        [Description("Right Aligned")]
        RightAligned
    }
    public enum CyEResolution
    {
        [Description("8")]
        B_PWM__R8 = 8,
        [Description("16")]
        B_PWM__R16 = 16
    }
    public enum CyETerminalMode
    {
        Schematic,
        Internal,
        Unused
    }
    #endregion Parameters types

    #region Parameters necessary to control the cy_clock component and clock terminal
    internal class CyClockParamName
    {
        internal const string IS_DESIRED_FREQ = "Clock_is_freq";
        internal const string DESIRED_FREQ = "Clock_desired_freq";
        internal const string DESIRED_FREQ_UNIT = "Clock_desired_freq_unit";
        internal const string IS_DIVIDER = "Clock_is_divider";
        internal const string DIVISOR = "Clock_divisor";

        internal const string SOURCE_CLOCK_ID = "Clock_source_clock_id";
        internal const string SOURCE_CLOCK_NAME = "Clock_source_clock_name";

        internal const string IS_DIRECT = "Clock_is_direct";
        internal const string MINUS_TOLERANCE = "Clock_minus_tolerance";
        internal const string PLUS_TOLERANCE = "Clock_plus_tolerance";
        internal const string CHECK_TOLERANCE = "Clock_CheckTolerance";

        internal const string FRACT_DIVIDER_USED = "Clock_FractDividerUsed";
        internal const string FRACT_DIVIDER_NUMERATOR = "Clock_FractDividerNumerator";
        internal const string FRACT_DIVIDER_DENOMINATOR = "Clock_FractDividerDenominator";
    }
    #endregion

    #region Component terminals names
    internal class CyTermName
    {
        //Inputs
        internal const string CLOCK = "clock";
        internal const string RESET = "reset";
        internal const string TRIGGER = "trigger";
        internal const string ENABLE = "enable";
        internal const string KILL = "kill";
        internal const string CAPTURE = "capture";
        internal const string CMP_SEL = "cmp_sel";        
        //Outputs
        internal const string PH1 = "ph1";
        internal const string PH2 = "ph2";
        internal const string TC = "tc";
        internal const string PWM1 = "pwm1";
        internal const string PWM2 = "pwm2";
        internal const string INTERRUPT = "interrupt";
        internal const string PWM = "pwm";
    }
    #endregion

    public class CyParameters
    {
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyDeviceQuery_v1 m_deviceQuery = null;
        private readonly ICyTerminalQuery_v1 m_termQuery = null;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        private CyEnum<CyEPwmMode> m_pwmMode;
        private CyEnum<CyECompareType> m_compareType1;
        private CyEnum<CyECompareType> m_compareType2;
        private CyEnum<CyEDitherOffset> m_ditherOffset;
        private CyEnum<CyEDeadBandMode> m_deadBand;
        private CyEnum<CyEEnableMode> m_enableMode;
        private CyEnum<CyERunMode> m_runMode;
        private CyEnum<CyETriggerMode> m_triggerMode;
        private CyEnum<CyEKillMode> m_killMode;
        private CyEnum<CyECaptureMode> m_captureMode;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;
            m_deviceQuery = instQuery.DeviceQuery;            

            m_pwmMode = new CyEnum<CyEPwmMode>(this, CyParamNames.PWM_MODE);
            m_compareType1 = new CyEnum<CyECompareType>(this, CyParamNames.COMPARE_TYPE_1);
            m_compareType2 = new CyEnum<CyECompareType>(this, CyParamNames.COMPARE_TYPE_2);
            m_ditherOffset = new CyEnum<CyEDitherOffset>(this, CyParamNames.DITHER_OFFSET);
            m_deadBand = new CyEnum<CyEDeadBandMode>(this, CyParamNames.DEAD_BAND);
            m_enableMode = new CyEnum<CyEEnableMode>(this, CyParamNames.ENABLE_MODE);
            m_runMode = new CyEnum<CyERunMode>(this, CyParamNames.RUN_MODE);
            m_triggerMode = new CyEnum<CyETriggerMode>(this, CyParamNames.TRIGGER_MODE);
            m_killMode = new CyEnum<CyEKillMode>(this, CyParamNames.KILL_MODE);
            m_captureMode = new CyEnum<CyECaptureMode>(this, CyParamNames.CAPTURE_MODE);
        }
        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit, instEdit, termQuery)
        {
        }
        #endregion

        #region Properties

        #region Common class properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }
        public ICyDeviceQuery_v1 DeviceQuery
        {
            get { return m_deviceQuery; }
        }
        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }
        #endregion

        #region Properties for enumeration parameters
        public CyEnum<CyEPwmMode> PwmMode
        {
            get { return m_pwmMode; }
            set { m_pwmMode = value; }
        }
        public CyEnum<CyECompareType> CompareType1
        {
            get { return m_compareType1; }
            set { m_compareType1 = value; }
        }
        public CyEnum<CyECompareType> CompareType2
        {
            get { return m_compareType2; }
            set { m_compareType2 = value; }
        }
        public CyEnum<CyEDitherOffset> DitherOffset
        {
            get { return m_ditherOffset; }
            set { m_ditherOffset = value; }
        }
        public CyEnum<CyEDeadBandMode> DeadBand
        {
            get { return m_deadBand; }
            set { m_deadBand = value; }
        }
        public CyEnum<CyEEnableMode> EnableMode
        {
            get { return m_enableMode; }
            set { m_enableMode = value; }
        }
        public CyEnum<CyERunMode> RunMode
        {
            get { return m_runMode; }
            set { m_runMode = value; }
        }
        public CyEnum<CyETriggerMode> TriggerMode
        {
            get { return m_triggerMode; }
            set { m_triggerMode = value; }
        }
        public CyEnum<CyEKillMode> KillMode
        {
            get { return m_killMode; }
            set { m_killMode = value; }
        }
        public CyEnum<CyECaptureMode> CaptureMode
        {
            get { return m_captureMode; }
            set { m_captureMode = value; }
        }
        public CyEResolution Resolution
        {
            // This parameter represented as an integer in the symbol.
            get { return (CyEResolution)GetValue<int>(CyParamNames.RESOLUTION); }
            set { SetValue(CyParamNames.RESOLUTION, (int)value); }
        }
        public CyEDitherAlign DitherAlign
        {
            get
            {
                return (this.m_compareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ?
                    CyEDitherAlign.LeftAligned : CyEDitherAlign.RightAligned; ;
            }
        }
        #endregion

        #region Properties for simple type parameters
        public bool FixedFunction
        {
            get { return GetValue<bool>(CyParamNames.FIXED_FUNCTION); }
            set { SetValue(CyParamNames.FIXED_FUNCTION, value); }
        }
        public UInt16? Period
        {
            get
            {
                CyCustErr error;
                UInt16? value = GetValue<UInt16>(CyParamNames.PERIOD, out error);
                return (error.IsOK) ? value : null;
            }
            set { SetValue(CyParamNames.PERIOD, value); }
        }
        public UInt16? CompareValue1
        {
            get
            {
                CyCustErr error;
                UInt16? value = GetValue<UInt16>(CyParamNames.COMPARE_VALUE_1, out error);
                return (error.IsOK) ? value : null;
            }
            set { SetValue(CyParamNames.COMPARE_VALUE_1, value); }
        }
        public UInt16? CompareValue2
        {
            get
            {
                CyCustErr error;
                UInt16? value = GetValue<UInt16>(CyParamNames.COMPARE_VALUE_2, out error);
                return (error.IsOK) ? value : null;
            }
            set { SetValue(CyParamNames.COMPARE_VALUE_2, value); }
        }
        public byte? DeadTime
        {
            get
            {
                CyCustErr error;
                byte? value = GetValue<byte>(CyParamNames.DEAD_TIME, out error);
                return (error.IsOK) ? value : null;
            }
            set { SetValue(CyParamNames.DEAD_TIME, value); }
        }
        public bool UseInterrupt
        {
            get { return GetValue<bool>(CyParamNames.USE_INTERRUPT); }
            set { SetValue(CyParamNames.USE_INTERRUPT, value); }
        }
        public bool InterruptOnKill
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_KILL); }
            set { SetValue(CyParamNames.INTERRUPT_ON_KILL, value); }
        }
        public bool InterruptOnCMP1
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_CMP_1); }
            set { SetValue(CyParamNames.INTERRUPT_ON_CMP_1, value); }
        }
        public bool InterruptOnCMP2
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_CMP_2); }
            set { SetValue(CyParamNames.INTERRUPT_ON_CMP_2, value); }
        }
        public bool InterruptOnTC
        {
            get { return GetValue<bool>(CyParamNames.INTERRUPT_ON_TC); }
            set { SetValue(CyParamNames.INTERRUPT_ON_TC, value); }
        }
        public byte KillTime
        {
            get { return GetValue<byte>(CyParamNames.MINIMUM_KILL_TIME); }
            set { SetValue(CyParamNames.MINIMUM_KILL_TIME, value); }
        }
        #endregion

        #endregion

        #region Getting Parameters

        private static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery, out CyCustErr err)
        {
            err = CyCustErr.OK;
            if (instQuery == null) return default(T);
            T value;
            err = instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        public static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            CyCustErr err;
            return GetValue<T>(paramName, instQuery, out err);
        }

        private T GetValue<T>(string paramName, out CyCustErr err)
        {
            err = CyCustErr.OK;
            return GetValue<T>(paramName, this.m_instQuery, out err);
        }

        public T GetValue<T>(string paramName)
        {
            CyCustErr err;
            return GetValue<T>(paramName, this.m_instQuery, out err);
        }

        public ushort GetPeriodMaxValue()
        {
            UInt16 max = 0;
            switch (this.Resolution)
            {
                case CyEResolution.B_PWM__R8:
                    max = (this.m_pwmMode.Value == CyEPwmMode.B_PWM__Center_Align) ?
                        CyParamRanges.PERIODMAX8CA : CyParamRanges.PERIODMAX8;
                    break;
                case CyEResolution.B_PWM__R16:
                    max = (this.m_pwmMode.Value == CyEPwmMode.B_PWM__Center_Align) ?
                        CyParamRanges.PERIODMAX16CA : CyParamRanges.PERIODMAX16;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            return max;
        }
        #endregion

        #region Setting Parameters
        public static CyCustErr SetValue<T>(ICyInstEdit_v1 instEdit, string paramName, T value)
        {            
            if (instEdit == null)
            {
                return CyCustErr.OK;
            }

            string valueToSet = String.Empty;
            if (value != null)
            {
                valueToSet = value.ToString();
            }
            if (value is bool)
                valueToSet = valueToSet.ToLower();
            if (instEdit.SetParamExpr(paramName, valueToSet))
            {
                instEdit.CommitParamExprs();
            }

            CyCompDevParam param = instEdit.GetCommittedParam(paramName);
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }

        public void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
            {
                SetValue<T>(m_instEdit, paramName, value);
            }
        }

        #endregion

        #region Enum conversions
        /// <summary>
        /// Converts enum value to description
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string GetEnumDesc(object value)
        {
            try
            {
                Type enumType = value.GetType();
                FieldInfo fi = enumType.GetField(Enum.GetName(enumType, value));
                DescriptionAttribute dna = (DescriptionAttribute)Attribute.GetCustomAttribute(fi,
                                                                                 typeof(DescriptionAttribute));
                return dna.Description;
            }
            catch (Exception)
            {
                return null;
            }
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

                CyCompDevParam param = m_prm.InstQuery.GetCommittedParam(m_paramName);
                if (param != null)
                {
                    m_prm.InstQuery.ResolveEnumParamToDisplay(param, out res);
                }

                return res;
            }
            set
            {
                string enumItemName = m_prm.InstQuery.ResolveEnumDisplayToId(m_paramName, value);
                try
                {
                    this.Value = (T)Enum.Parse(typeof(T), enumItemName);
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
                return new List<string>(m_prm.InstQuery.GetPossibleEnumValues(m_paramName)).ToArray();
            }
        }

        public override string ToString()
        {
            return this.Value.ToString();
        }
    }
}
