/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Scc;
using System.Reflection;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Diagnostics;


namespace TCPWM_P4_v2_10
{
    #region Enums
    public enum CyETriggerMode
    {
        [Description("Rising edge")]
        TRIG_RISING = 0,
        [Description("Falling edge")]
        TRIG_FALLING = 1,
        [Description("Either edge")]
        TRIG_BOTH = 2,
        [Description("Level")]
        TRIG_LEVEL = 3
    }
    public enum CyESwapEnable
    {
        SWAP_DISABLE = 0,
        SWAP_ENABLE = 1
    }
    public enum CyETriggerMask
    {
        CMD_CAPTURE = 0,
        CMD_RELOAD = 1,
        CMD_STOP = 2,
        CMD_START = 3
    }
    public enum CyECounterMode
    {
        [Description("Up")]
        COUNT_UP = 0,
        [Description("Down")]
        COUNT_DOWN = 1,
        [Description("Up/Down 0")]
        COUNT_UPDOWN0 = 2,
        [Description("Up/Down 1")]
        COUNT_UPDOWN1 = 3
    }
    public enum CyEInterruptMask
    {
        INTR_MASK_NONE = 0,
        INTR_MASK_TC = 1,
        INTR_MASK_CC_MATCH = 2,
        INTR_MASK_TC_CC = 3

    }
    public enum CyECompCapMode
    {
        [Description("Capture")]
        Capture = 2,
        [Description("Compare")]
        Compare = 0
    }
    public enum CyERunMode
    {
        [Description("Continuous")]
        Continuous = 0,
        [Description("One shot")]
        OneShot = 1
    }
    public enum CyETCPWMConfig
    {
        [Description("Unconfigured")]
        UNCONFIG = 8,
        [Description("Timer / Counter")]
        TIMER = 1,
        [Description("QuadDec")]
        QUAD = 3,
        [Description("PWM")]
        PWM_SEL = 7
    }
    public enum CyEPWMMode
    {
        [Description("PWM")]
        PWM = 4,
        [Description("PWM with dead time insertion")]
        PWM_DT = 5,
        [Description("Pseudo random PWM")]
        PWM_PR = 6
    }
    public enum CyEPWMEvent
    {
        [Description("Asynchronous")]
        ASYNCH = 0,
        [Description("Synchronous")]
        SYNCH = 1
    }
    public enum CyPWMInvert
    {
        [Description("Direct output")]
        DIRECT = 0,
        [Description("Inverse output")]
        INVERSE = 1
    }
    public enum CyEPWMAlign
    {
        [Description("Left align")]
        LEFT = 0,
        [Description("Right align")]
        RIGHT = 1,
        [Description("Center align")]
        CENTER = 2,
        [Description("Asymmetric align")]
        ASYMMETRIC = 3
    }
    public enum CyEPWMStop
    {
        [Description("Don't stop on kill")]
        DONT_STOP = 0,
        [Description("Stop on kill")]
        STOP = 1
    }
    public enum CyEQuadMode
    {
        [Description("1x")]
        X1 = 0,
        [Description("2x")]
        X2 = 1,
        [Description("4x")]
        X4 = 2
    }
    public enum CyETerminalMode
    {
        Schematic,
        Internal,
        Unused
    }
    #endregion Enums

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
        internal const string RELOAD = "reload";
        internal const string COUNT = "count";
        internal const string START = "start";
        internal const string STOP = "stop";
        internal const string CAPTURE = "capture";
        //Outputs
        internal const string OV = "ov";
        internal const string UN = "un";
        internal const string CC = "cc";
        internal const string LINE = "line";
        internal const string LINE_N = "line_n";
        internal const string INTERRUPT = "interrupt";
        //Alternative names for different modes
        internal const string INDEX = "index";
        internal const string PHI_A = "phiA";
        internal const string PHI_B = "phiB";
        internal const string KILL = "kill";
        internal const string SWITCH = "switch";
    }
    #endregion

    #region Component terminals states
    internal class CyTermParamName
    {
        //Inputs
        internal const string TERM_MODE_CLOCK = "TermMode_clock";
        internal const string TERM_MODE_RELOAD = "TermMode_reload";
        internal const string TERM_MODE_COUNT = "TermMode_count";
        internal const string TERM_MODE_START = "TermMode_start";
        internal const string TERM_MODE_STOP = "TermMode_stop";
        internal const string TERM_MODE_CAPTURE = "TermMode_capture";
        //Outputs
        internal const string TERM_MODE_OV = "TermMode_ov";
        internal const string TERM_MODE_UN = "TermMode_un";
        internal const string TERM_MODE_CC = "TermMode_cc";
        internal const string TERM_MODE_LINE = "TermMode_line";
        internal const string TERM_MODE_LINE_N = "TermMode_line_n";
        internal const string TERM_MODE_INTERRUPT = "TermMode_interrupt";
    }
    #endregion

    public class CyParameters
    {
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private ICyTabbedParamEditor m_editor;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        private bool m_globalEditMode = false;        
        public CyTCPWMTab m_tcpwmTab;
        public CyTimerCounterTab m_tcTab;
        public CyPWMTab m_pwmTab;
        public CyQuadDecTab m_quaddecTab;

        // Xml serialization parameters
        private XmlSerializer m_terminalsModesSerializer;
        private XmlSerializerNamespaces m_customSerNamespace;
        private List<CyTerminalsModes> m_terminalsModes;

        #region Param names
        //General
        const string P_TCPWMCONFIG = "TCPWMConfig";
        const string P_CAPTUREMODE = "TCCaptureMode";
        const string P_CAPTUREPRESENT = "CapturePresent";
        const string P_COUNTMODE = "CountMode";
        const string P_COUNTPRESENT = "CountPresent";
        const string P_RELOADMODE = "ReloadMode";
        const string P_RELOADPRESENT = "ReloadPresent";
        const string P_STARTMODE = "StartMode";
        const string P_STARTPRESENT = "StartPresent";
        const string P_STOPMODE = "StopMode";
        const string P_STOPPRESENT = "StopPresent";
        const string P_COMPARE1 = "Compare";
        const string P_COMPARE2 = "CompareBuf";
        const string P_COMPARE_SWAP = "CompareSwap";
        const string P_PERIOD1 = "Period";
        const string P_PERIOD2 = "PWMPeriodBuf";
        const string P_PERIOD_SWAP = "PWMPeriodSwap";
        const string P_INTERRUPT_MASK = "InterruptMask";
        const string P_PRESCALER = "Prescaler";
        const string P_RUNMODE = "RunMode";

        // TimerCounter
        const string P_COMPCAPMODE = "TCCompCapMode";
        const string P_COUNTINGMODES = "TCCountingModes";        

        // PWM
        const string P_PWMMODE = "PWMMode";
        const string P_PWMDEADTIMECYCLE = "PWMDeadTimeCycle";
        const string P_PWMKILLEVENT = "PWMKillEvent";
        const string P_PWMSTOPEVENT = "PWMStopEvent";
        const string P_PWMOUTINVERT = "PWMLineSignal";
        const string P_PWMOUTCCINVERT = "PWMLinenSignal";
        const string P_PWMSETALIGN = "PWMSetAlign";
        const string P_SWITCHMODE = "PWMSwitchMode";
        const string P_SWITCHPRESENT = "PWMSwitchPresent";

        // QuadDec
        const string P_QUADENCODINGMODES = "QuadEncodingModes";
        const string P_INDEXMODE = "QuadIndexMode";
        const string P_INDEXPRESENT = "QuadIndexPresent";
        const string P_PHIAMODE = "QuadPhiAMode";
        const string P_PHIBMODE = "QuadPhiBMode";

        // Prefixes
        const string PREFIX_TCPWM = "TCPWM";
        const string PREFIX_TC = "TC";
        const string PREFIX_PWM = "PWM";
        const string PREFIX_QUADDEC = "Quad";

        // Terminals States data for Different TCPWM modes.
        const string TERM_MODE_STATES = "TermModeStates";
        #endregion Param names

        public const string HEX_PREFIX = "0x";
        public static object[] PRESCALER_ITEMS_LIST = new object[] {
            "1x", "2x", "4x", "8x", "16x", "32x", "64x", "128x" };

        public static UInt16[] COMPARE_RANGE = new UInt16[2] { 0, 65535 };
        public static UInt16[] DEADTIME_RANGE = new UInt16[2] { 0, 255 };

        #region Properties

        #region General
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        } 

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        public ICyTabbedParamEditor Editor
        {
            get { return m_editor; }
            set { m_editor = value; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public CyETCPWMConfig TCPWMConfig
        {
            get { return GetValue<CyETCPWMConfig>(P_TCPWMCONFIG); }
            set { SetValue(P_TCPWMCONFIG, value); }
        }

        public List<CyTerminalsModes> TerminalsModes
        {
            get { return m_terminalsModes; }
            set { m_terminalsModes = value; }
        }

        public bool IsTcpwmIpV2BLE // PSoC4200 BLE (IP Block ver. 2, exept PSoC4000)
        {
            get { return ((InstQuery.DeviceQuery.GetFeatureVersion("m0s8tcpwm") >= 2) &&
                          (InstQuery.DeviceQuery.ArchFamilyMember != "PSoC4_1"));
            }
        }

        #region Terminal Modes
        public CyETerminalMode TermMode_clk
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_CLOCK); }            
        }

        public CyETerminalMode TermMode_reload
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_RELOAD); }
            set { SetValue(CyTermParamName.TERM_MODE_RELOAD, (int)value); }
        }

        public CyETerminalMode TermMode_count
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_COUNT); }
            set { SetValue(CyTermParamName.TERM_MODE_COUNT, (int)value); }
        }

        public CyETerminalMode TermMode_start
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_START); }
            set { SetValue(CyTermParamName.TERM_MODE_START, (int)value); }
        }

        public CyETerminalMode TermMode_stop
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_STOP); }
            set { SetValue(CyTermParamName.TERM_MODE_STOP, (int)value); }
        }

        public CyETerminalMode TermMode_capture
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_CAPTURE); }
            set { SetValue(CyTermParamName.TERM_MODE_CAPTURE, (int)value); }
        }

        public CyETerminalMode TermMode_ov
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_OV); }
            set { SetValue(CyTermParamName.TERM_MODE_OV, (int)value); }
        }

        public CyETerminalMode TermMode_un
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_UN); }
            set { SetValue(CyTermParamName.TERM_MODE_UN, (int)value); }
        }

        public CyETerminalMode TermMode_cc
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_CC); }
            set { SetValue(CyTermParamName.TERM_MODE_CC, (int)value); }
        }

        public CyETerminalMode TermMode_line
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_LINE); }
            set { SetValue(CyTermParamName.TERM_MODE_LINE, (int)value); }
        }

        public CyETerminalMode TermMode_line_n
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_LINE_N); }
            set { SetValue(CyTermParamName.TERM_MODE_LINE_N, (int)value); }
        }

        public CyETerminalMode TermMode_interrupt
        {
            get { return GetValue<CyETerminalMode>(CyTermParamName.TERM_MODE_INTERRUPT); }
            set { SetValue(CyTermParamName.TERM_MODE_INTERRUPT, (int)value); }
        }
        #endregion

        #region Table
        public CyETriggerMode CaptureMode
        {
            get { return GetValue<CyETriggerMode>(P_CAPTUREMODE); }
            set { SetValue(P_CAPTUREMODE, value); }
        }

        public bool CapturePresent
        {
            get { return GetValue<bool>(GetPrefix() + P_CAPTUREPRESENT); }
            set { SetValue(GetPrefix() + P_CAPTUREPRESENT, value); }
        }

        public CyETriggerMode CountMode
        {
            get { return GetValue<CyETriggerMode>(GetPrefix() + P_COUNTMODE); }
            set { SetValue(GetPrefix() + P_COUNTMODE, value);}
        }

        public bool CountPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_COUNTPRESENT); }
            set { SetValue(GetPrefix() + P_COUNTPRESENT, value); }
        }

        public CyETriggerMode ReloadMode
        {
            get { return GetValue<CyETriggerMode>(GetPrefix() + P_RELOADMODE); }
            set { SetValue(GetPrefix() + P_RELOADMODE, value); }
        }

        public bool ReloadPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_RELOADPRESENT); }
            set { SetValue(GetPrefix() + P_RELOADPRESENT, value); }
        }

        public CyETriggerMode StartMode
        {
            get { return GetValue<CyETriggerMode>(GetPrefix() + P_STARTMODE); }
            set { SetValue(GetPrefix() + P_STARTMODE, value); }
        }

        public bool StartPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_STARTPRESENT); }
            set { SetValue(GetPrefix() + P_STARTPRESENT, value); }
        }

        public CyETriggerMode StopMode
        {
            get { return GetValue<CyETriggerMode>(GetPrefix() + P_STOPMODE); }
            set { SetValue(GetPrefix() + P_STOPMODE, value); }
        }

        public bool StopPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_STOPPRESENT); }
            set { SetValue(GetPrefix() + P_STOPPRESENT, value); }
        }
        #endregion Table

        #region Compare / Period
        public uint Compare1
        {
            get { return GetValue<uint>(GetPrefix() + P_COMPARE1); }
            set
            {
                SetValue(GetPrefix() + P_COMPARE1, value);
            }
        }

        public uint Compare2
        {
            get { return GetValue<uint>(GetPrefix() + P_COMPARE2); }
            set { SetValue(GetPrefix() + P_COMPARE2, value); }
        }

        public CyESwapEnable CompareSwap
        {
            get { return GetValue<CyESwapEnable>(GetPrefix() + P_COMPARE_SWAP); }
            set { SetValue(GetPrefix() + P_COMPARE_SWAP, value); }
        }

        public uint Period1
        {
            get { return GetValue<uint>(GetPrefix() + P_PERIOD1); }
            set { SetValue(GetPrefix() + P_PERIOD1, value); }
        }

        public uint Period2
        {
            get { return GetValue<uint>(P_PERIOD2); }
            set { SetValue(P_PERIOD2, value); }
        }

        public CyESwapEnable PeriodSwap
        {
            get { return GetValue<CyESwapEnable>(P_PERIOD_SWAP); }
            set { SetValue(P_PERIOD_SWAP, value); }
        }
        #endregion Compare / Period

        public CyEInterruptMask InterruptMask
        {
            get { return GetValue<CyEInterruptMask>(GetPrefix() + P_INTERRUPT_MASK); }
            set  { SetValue(GetPrefix() + P_INTERRUPT_MASK, value); }
        }

        public uint Prescaler
        {
            get { return GetValue<uint>(GetPrefix() + P_PRESCALER); }
            set { SetValue(GetPrefix() + P_PRESCALER, value); }
        }
        #endregion General

        #region TC
        // TimerCounter
        public CyECompCapMode CompCapMode
        {
            get { return GetValue<CyECompCapMode>(P_COMPCAPMODE); }
            set { SetValue(P_COMPCAPMODE, value); }
        }

        public CyECounterMode CountingModes
        {
            get { return GetValue<CyECounterMode>(P_COUNTINGMODES); }
            set { SetValue(P_COUNTINGMODES, value); }
        }

        public CyERunMode RunMode
        {
            get { return GetValue<CyERunMode>(GetPrefix() + P_RUNMODE); }
            set { SetValue(GetPrefix() + P_RUNMODE, value); }
        }
        #endregion TC

        #region PWM
        // PWM
        public CyEPWMMode PWMMode
        {
            get { return GetValue<CyEPWMMode>(P_PWMMODE); }
            set { SetValue(P_PWMMODE, value); }
        }

        public uint PWMDeadTimeCycle
        {
            get { return GetValue<uint>(P_PWMDEADTIMECYCLE); }
            set { SetValue(P_PWMDEADTIMECYCLE, value); }
        }

        public CyEPWMEvent PWMKillEvent
        {
            get { return GetValue<CyEPWMEvent>(P_PWMKILLEVENT); }
            set { SetValue(P_PWMKILLEVENT, value); }
        }

        public CyEPWMStop PWMStopEvent
        {
            get { return GetValue<CyEPWMStop>(P_PWMSTOPEVENT); }
            set { SetValue(P_PWMSTOPEVENT, value); }
        }

        public CyPWMInvert PWMOutInvert
        {
            get { return GetValue<CyPWMInvert>(P_PWMOUTINVERT); }
            set { SetValue(P_PWMOUTINVERT, value); }
        }

        public CyPWMInvert PWMOutCCInvert
        {
            get { return GetValue<CyPWMInvert>(P_PWMOUTCCINVERT); }
            set { SetValue(P_PWMOUTCCINVERT, value); }
        }

        public CyEPWMAlign PWMSetAlign
        {
            get { return GetValue<CyEPWMAlign>(P_PWMSETALIGN); }
            set { SetValue(P_PWMSETALIGN, value); }
        }

        public CyETriggerMode SwitchMode
        {
            get { return GetValue<CyETriggerMode>(P_SWITCHMODE); }
            set { SetValue(P_SWITCHMODE, value); }
        }

        public bool SwitchPresent
        {
            get { return GetValue<bool>(P_SWITCHPRESENT); }
            set { SetValue(P_SWITCHPRESENT, value); }
        }
        #endregion PWM

        #region QuadDec
        public CyEQuadMode QuadEncodingModes
        {
            get { return GetValue<CyEQuadMode>(P_QUADENCODINGMODES); }
            set { SetValue(P_QUADENCODINGMODES, value); }
        }

        public CyETriggerMode IndexMode
        {
            get { return GetValue<CyETriggerMode>(P_INDEXMODE); }
            set { SetValue(P_INDEXMODE, value); }
        }

        public bool IndexPresent
        {
            get { return GetValue<bool>(P_INDEXPRESENT); }
            set { SetValue(P_INDEXPRESENT, value); }
        }

        public CyETriggerMode PhiAMode
        {
            get { return GetValue<CyETriggerMode>(P_PHIAMODE); }
            set { SetValue(P_PHIAMODE, value); }
        }

        public CyETriggerMode PhiBMode
        {
            get { return GetValue<CyETriggerMode>(P_PHIBMODE); }
            set { SetValue(P_PHIBMODE, value); }
        }
        #endregion QuadDec

        #endregion Properties

        #region Constructor
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;

            // Create XML Serializer(s)
            m_terminalsModesSerializer = new XmlSerializer(typeof(List<CyTerminalsModes>));
            m_customSerNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(CyParameters).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);            
            m_terminalsModes = new List<CyTerminalsModes>(GetTermModesXml());            
        }
        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit, instEdit, termQuery)
        {
        }
        #endregion Constructor

        #region Common
        private T GetValue<T>(string paramName)
        {
            return GetValue<T>(paramName, m_instQuery);
        }

        public static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            if (instQuery == null) return default(T);
            T value;
            CyCustErr err = instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        public static CyCustErr SetValue<T>(ICyInstEdit_v1 instEdit, string paramName, T value)
        {
            if (instEdit == null)
            {
                return CyCustErr.OK;
            }
            
            string valueToSet = value.ToString();         
            if (value is bool)
                valueToSet = valueToSet.ToLower();
            if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                valueToSet += "u";

            if (instEdit.SetParamExpr(paramName, valueToSet) && instEdit.CommitParamExprs())
            {
                return CyCustErr.OK;
            }

            CyCompDevParam param = instEdit.GetCommittedParam(paramName);
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;            
        }

        private void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
            {
                SetValue(m_instEdit, paramName, value);
            }
        }

        public List<CyTerminalsModes> GetDefaultTerminalsModes()
        {
            List<CyTerminalsModes> modesList = new List<CyTerminalsModes>();

            modesList.Add(new CyTerminalsModes(CyETCPWMConfig.UNCONFIG,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Unused,   CyETerminalMode.Unused,   CyETerminalMode.Unused,
                CyETerminalMode.Unused,   CyETerminalMode.Unused,   CyETerminalMode.Unused));
            modesList.Add(new CyTerminalsModes(CyETCPWMConfig.TIMER,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Unused, CyETerminalMode.Unused, CyETerminalMode.Unused,
                CyETerminalMode.Unused, CyETerminalMode.Unused, CyETerminalMode.Unused));
            modesList.Add(new CyTerminalsModes(CyETCPWMConfig.PWM_SEL,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Unused, CyETerminalMode.Unused, CyETerminalMode.Unused,
                CyETerminalMode.Internal, CyETerminalMode.Unused, CyETerminalMode.Unused));
            modesList.Add(new CyTerminalsModes(CyETCPWMConfig.QUAD,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Internal, CyETerminalMode.Internal, CyETerminalMode.Internal,
                CyETerminalMode.Unused, CyETerminalMode.Unused, CyETerminalMode.Unused,
                CyETerminalMode.Unused, CyETerminalMode.Unused, CyETerminalMode.Unused));

            return modesList;
        }

        #endregion Common

        #region Service functions
        /// <summary>
        /// Returns a prefix of parameters names for each TCPWM mode
        /// </summary>
        /// <returns></returns>
        private string GetPrefix()
        {
            string prefix = "";
            switch (TCPWMConfig)
            {
                case CyETCPWMConfig.UNCONFIG:
                    prefix = PREFIX_TCPWM;
                    break;
                case CyETCPWMConfig.TIMER:
                    prefix = PREFIX_TC;
                    break;
                case CyETCPWMConfig.QUAD:
                    prefix = PREFIX_QUADDEC;
                    break;
                case CyETCPWMConfig.PWM_SEL:
                    prefix = PREFIX_PWM;
                    break;
                default:
                    break;
            }
            return prefix;
        }

        // combobox
        public static void FillComboFromEnum(ComboBox cb, Type enumType)
        {
            cb.Items.Clear();
            cb.Items.AddRange(GetDescriptionList(enumType));
        }
        public static void SetComboValue(ComboBox cb, object value)
        {
            string descr = GetDescription(value);
            if (cb.Items.Contains(descr))
                cb.SelectedItem = descr;
        }
        // datagridview
        public static void SetComboCellValue(DataGridViewComboBoxCell comboCell, object value)
        {
            string descr = GetDescription(value);
            if (comboCell.Items.Contains(descr))
                comboCell.Value = descr;
        }

        public void DisableRow(DataGridViewRow row, bool disable)
        {
            row.ReadOnly = disable;
            if (disable)
            {
                DataGridViewCellStyle style = new DataGridViewCellStyle();
                style.ForeColor = SystemColors.GrayText;
                style.BackColor = SystemColors.Control;
                row.DefaultCellStyle = style;
            }
            else
            {
                row.DefaultCellStyle = null;
            }
        }
        // Enumerations
        public static string[] GetDescriptionList(Type _enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(_enumType))
            {
                res.Add(GetDescription(item));
            }
            return res.ToArray();
        }
        public static string GetDescription(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
        }
        public static T GetEnum<T>(string value)
        {
            return (T)GetEnum(value, typeof(T));
        }
        /// <summary>
        /// Convert enum description string to enum value
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        static object GetEnum(string value, Type _enumType)
        {
            foreach (FieldInfo fi in _enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value == dna.Description))
                {
                    object res = Enum.Parse(_enumType, fi.Name);
                    return res;
                }

            }

            return Enum.Parse(_enumType, value);
        }
        // Hexadecimal convertations
        public static int HexToInt(string hexString)
        {
            int result = -1;
            try
            {
                result = Convert.ToInt32(hexString, 16);
            }
            catch (Exception) { }
            return result;
        }

        public static string IntToHex(int intValue)
        {
            return (HEX_PREFIX + intValue.ToString("X"));
        }

        public static bool IsHex(string inputValue)
        {
            // Check if string starts with "0x"
            bool isHex = inputValue.StartsWith(CyParameters.HEX_PREFIX);
            // Try to convert hex string to int 
            isHex &= (HexToInt(inputValue) >= 0);
            return isHex;
        }

        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public static string GetInternalClock(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = new List<CyClockData>();

            clkdata = termQuery.GetClockData("or_1", "term1", 0);

            if (clkdata.Count > 0)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return string.Format(Resources.ClockDisplay, clkdata[0].Frequency, clkdata[0].Unit);
                }
            }
            return Resources.ClockUnknown;
        }

        /// <summary>
        /// Show/hide tabs depending on the TCPWM Mode
        /// </summary>
        public void UpdateTabVisibility()
        {
            if ((m_instQuery == null) || (m_tcTab == null) || (m_pwmTab == null) || (m_quaddecTab == null))
                return;

            m_editor.ShowCustomPage(Resources.TabNameTCPWM);
            m_editor.ShowCustomPage(Resources.TabNameTC);
            m_editor.ShowCustomPage(Resources.TabNamePWM);
            m_editor.ShowCustomPage(Resources.TabNameQuadDec);

            switch (TCPWMConfig)
            {
                case CyETCPWMConfig.UNCONFIG:
                    m_editor.HideCustomPage(Resources.TabNameTC);
                    m_editor.HideCustomPage(Resources.TabNamePWM);
                    m_editor.HideCustomPage(Resources.TabNameQuadDec);
                    m_tcpwmTab.UpdateFormFromParams();
                    break;
                case CyETCPWMConfig.TIMER:
                    m_editor.HideCustomPage(Resources.TabNameTCPWM);
                    m_editor.HideCustomPage(Resources.TabNamePWM);
                    m_editor.HideCustomPage(Resources.TabNameQuadDec);
                    m_tcTab.UpdateFormFromParams();
                    break;
                case CyETCPWMConfig.QUAD:
                    m_editor.HideCustomPage(Resources.TabNameTCPWM);
                    m_editor.HideCustomPage(Resources.TabNameTC);
                    m_editor.HideCustomPage(Resources.TabNamePWM);
                    m_quaddecTab.UpdateFormFromParams();
                    break;
                case CyETCPWMConfig.PWM_SEL:
                    m_editor.HideCustomPage(Resources.TabNameTCPWM);
                    m_editor.HideCustomPage(Resources.TabNameTC);
                    m_editor.HideCustomPage(Resources.TabNameQuadDec);
                    m_pwmTab.UpdateFormFromParams();
                    break;
                default:
                    break;
            }                        
        }

        #region Getting/Setting parameters with XML Data
        /// <summary>
        /// Get Terminal Modes from xml
        /// </summary>
        public List<CyTerminalsModes> GetTermModesXml()
        {
            string xmlData = GetValue<string>(CyParameters.TERM_MODE_STATES, m_instQuery);
            return (List<CyTerminalsModes>)Deserialize(xmlData, typeof(List<CyTerminalsModes>));
        }

        /// <summary>
        /// Set Terminal Modes to xml
        /// </summary>
        public void SetTermModesXml(CyETCPWMConfig TCPWMMode)
        {
            byte index = 0;

            while (TerminalsModes[index].TCPWM_Mode != TCPWMMode)
            {
                index++;
            }
            TerminalsModes[index].TermMode_reload = TermMode_reload;
            TerminalsModes[index].TermMode_count = TermMode_count;
            TerminalsModes[index].TermMode_start = TermMode_start;
            TerminalsModes[index].TermMode_stop = TermMode_stop;
            TerminalsModes[index].TermMode_capture = TermMode_capture;
            TerminalsModes[index].TermMode_ov = TermMode_ov;
            TerminalsModes[index].TermMode_un = TermMode_un;
            TerminalsModes[index].TermMode_cc = TermMode_cc;
            TerminalsModes[index].TermMode_line = TermMode_line;
            TerminalsModes[index].TermMode_line_n = TermMode_line_n;
            TerminalsModes[index].TermMode_interrupt = TermMode_interrupt;

            SetValue(CyParameters.TERM_MODE_STATES, Serialize(m_terminalsModes));
        }

        /// <summary>
        /// Set Terminal Modes parameters from xml
        /// </summary>
        public void SetTermModesParams(CyETCPWMConfig TCPWMMode)
        {
            List<CyTerminalsModes> modesList = GetTermModesXml();
            byte index = 0;

            while (modesList[index].TCPWM_Mode != TCPWMMode)            
            {
                index++;
            }

            TermMode_reload = modesList[index].TermMode_reload;
            TermMode_count = modesList[index].TermMode_count;
            TermMode_start = modesList[index].TermMode_start;
            TermMode_stop = modesList[index].TermMode_stop;
            TermMode_capture = modesList[index].TermMode_capture;
            TermMode_ov = modesList[index].TermMode_ov;
            TermMode_un = modesList[index].TermMode_un;
            TermMode_cc = modesList[index].TermMode_cc;
            TermMode_line = modesList[index].TermMode_line;
            TermMode_line_n = modesList[index].TermMode_line_n;
            TermMode_interrupt = modesList[index].TermMode_interrupt;
        }

        #endregion

        #region XML Serialization

        private XmlSerializer GetSerializer(Type type)
        {
            if (type == typeof(List<CyTerminalsModes>))
            {
                return m_terminalsModesSerializer;
            }
            else
            {
                return new XmlSerializer(type);
            }
        }

        public string Serialize(object obj)
        {
            StringBuilder sb = new StringBuilder();

            System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb);
            GetSerializer(obj.GetType()).Serialize(tw, obj, m_customSerNamespace);

            string res = sb.ToString();
            res = res.Replace(Environment.NewLine, " ");
            return res;
        }

        public object Deserialize(string serializedXml, Type t)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml)) throw new Exception();

                // Read version information
                XmlReader tr = XmlReader.Create(new StringReader(serializedXml));
                // Remove header <?xml version="1.0" encoding="utf-16" ?> 
                tr.Read();
                tr.Read();
                // Go to first Node with attributes
                while (tr.HasAttributes == false)
                {
                    tr.Read();
                }
                // This version information will be used in future versions of component.
                string ver_info = tr.GetAttribute(0);
                res = GetSerializer(t).Deserialize(tr);
            }
            catch
            {
                res = Activator.CreateInstance(t);
                if (String.IsNullOrEmpty(serializedXml))
                {
                    if (t == typeof(List<CyTerminalsModes>))
                    {
                        res = GetDefaultTerminalsModes();
                    }
                }
                else
                {
                    MessageBox.Show(Resources.SettingsIncorrectValues,
                        MessageBoxIcon.Warning.ToString(), MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            return res;
        }

        #endregion

        #endregion Service functions
    }
}
