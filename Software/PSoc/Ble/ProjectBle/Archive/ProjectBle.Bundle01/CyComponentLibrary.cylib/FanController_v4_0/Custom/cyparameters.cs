/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
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


namespace FanController_v4_0
{
    public enum CyPWMResType
    {
        [Description("8 bit")]
        EIGHT_BIT = 0,
        [Description("10 bit")]
        TEN_BIT = 1
    }
    public enum CyFanModeType
    {
        FIRMWARE = 0,
        HARDWARE = 1
    }
    public enum CyFanModeDisplayType
    {
        MANUAL,
        AUTO_FIRMWARE,
        AUTO_HARDWARE
    }
    public enum CyPWMFreqType
    {
        [Description("25 kHz")]
        TWENTYFIVE_KHZ = 0,
        [Description("50 kHz")]
        FIFTY_KHZ = 1
    }
    public enum CyConnectinType
    {
        WIRED = 1,
        BUSSED = 0
    }

    public enum CyMotorType
    {
        FOUR_POLE = 0,
        SIX_POLE = 1
    }

    public class CyParamConst
    {
        public const byte MAX_FANS = 16;
        public const byte MAX_FANS_CLOSED_8B = 12;
        public const byte MAX_FANS_CLOSED_10B = 8;

        public const byte ALERT_FAN_STALL = 1;
        public const byte ALERT_SPEED_FAIL = 2;

        public const int VSPC_DEF = 25;

        public const int XPOS_NUD = 19;
        public const int YPOS_NUD = 4;

        public const int XPOS_FAN_NUM_LBL = 35;
        public const int YPOS_FAN_NUM_LBL = 6;

        public const UInt16 MIN_RPM_NUD = 500;
        public const UInt16 MAX_RPM_NUD = 25000;

        public const UInt16 MIN_DUTY_NUD = 0;
        public const UInt16 MAX_DUTY_NUD = 100;

        public const decimal MIN_CONTROL_LOOP_PERIOD = 0;
        public const decimal MAX_CONTROL_LOOP_PERIOD = 2.55M;
        public const int CONTROL_LOOP_PERIOD_MULT = 100;

        public const int MIN_TOLERANCE_PERCENT = 1;
        public const int MAX_TOLERANCE_PERCENT = 10;

        public const int MAX_PWM_PSOC4 = 4;
        public const int MAX_FAN_PSOC4 = 8;

        public const int MIN_ATTENUATION = -23;
        public const int MAX_ATTENUATION = -8;

        public const decimal EPS = 10e-5M;
    }

    public class CyParameters
    {
        #region Parameter names in symbol
        public const string P_NUMBER_OF_FANS = "NumberOfFans";
        public const string P_NUMBER_OF_BANKS = "NumberOfBanks";
        const string P_FAN_MODE = "FanMode";
        const string P_FAN_MODE_MANUAL = "FanModeManual";
        const string P_ALERT_ENABLE = "AlertEnable";
        const string P_CONNECTION = "Connection";
        const string P_FAN_PWM_FREQ = "FanPWMFreq";
        const string P_FAN_PWM_RES = "FanPWMRes";
        const string P_DAMPING_FACTOR = "DampingFactor";
        const string P_ACOUSTIC_NOISE_REDUCTION = "AcousticNoiseReduction";
        const string P_FAN_TOLERANCE = "FanTolerance";
        const string P_EXTERNAL_CLOCK = "ExternalClock";
        const string P_MOTOR_TYPE = "MotorType";
        public const string P_MIN_RPM = "MinRPM";
        public const string P_MAX_RPM = "MaxRPM";
        public const string P_MIN_DUTY = "MinDuty";
        public const string P_MAX_DUTY = "MaxDuty";
        public const string P_INITIAL_RPM = "InitialRPM";
        public const string P_INITIAL_DUTY_CYCLE = "InitialDutyCycle";
        const string P_COEF_PROPORTIONAL = "CoefProportional";
        const string P_COEF_INTEGRAL = "CoefIntegral";
        const string P_COEF_DERIVATIVE = "CoefDerivative";
        const string P_COEF_UPPER_OUTPUT_LIMIT = "CoefUpperOutputLimit";
        const string P_COEF_LOWER_OUTPUT_LIMIT = "CoefLowerOutputLimit";
        const string P_COEF_OUTPUT_ATTENUATION = "CoefOutputAttenuation";
        const string P_CONTROL_LOOP_PERIOD_PID = "ControlLoopPeriodPid";
        #endregion Parameter names in symbol

        #region Fields
        private readonly ICyInstEdit_v1 m_instEdit;
        public readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstValidate_v1 m_instValidate;
        public ICyTabbedParamEditor m_editor;

        public CyFansTab m_fansTab = null;
        public CyPidTab m_pidTab = null;

        private bool m_globalEditMode = false;
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }
        #endregion Fields

        #region Constructors
        public CyParameters() { }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this()
        {
            m_instQuery = instQuery;
            m_instEdit = null;
            m_instValidate = null;
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this()
        {
            m_instQuery = instEdit;
            m_instEdit = instEdit;
            m_instValidate = null;
        }

        public CyParameters(ICyInstValidate_v1 instVal)
            : this()
        {
            m_instQuery = null;
            m_instEdit = null;
            m_instValidate = instVal;
        }
        #endregion Constructors

        #region Basic tab parameters
        public byte NumberOfFans
        {
            get { return GetValue<byte>(P_NUMBER_OF_FANS); }
            set { SetValue(P_NUMBER_OF_FANS, value); }
        }
        public byte NumberOfBanks
        {
            get { return GetValue<byte>(P_NUMBER_OF_BANKS); }
            set { SetValue(P_NUMBER_OF_BANKS, value); }
        }

        private CyFanModeType FanMode
        {
            get { return GetValue<CyFanModeType>(P_FAN_MODE); }
            set { SetValue(P_FAN_MODE, value); }
        }
        private bool FanModeManual
        {
            get { return GetValue<bool>(P_FAN_MODE_MANUAL); }
            set { SetValue(P_FAN_MODE_MANUAL, value); }
        }

        /// <summary>
        /// There are two parameters for Fan Mode in symbol (FanMode and FanModeManual). This was done for backward 
        /// compatibility. Customizer has one parameter. That is why additional manipulations are required.
        /// </summary>
        public CyFanModeDisplayType GetFanMode()
        {
            CyFanModeDisplayType result = CyFanModeDisplayType.MANUAL;
            if (FanMode == CyFanModeType.HARDWARE)
            {
                result = CyFanModeDisplayType.AUTO_HARDWARE;
            }
            else if ((FanMode == CyFanModeType.FIRMWARE) && (FanModeManual == false))
            {
                result = CyFanModeDisplayType.AUTO_FIRMWARE;
            }
            return result;
        }
        public void SetFanMode(CyFanModeDisplayType value)
        {
            switch (value)
            {
                case CyFanModeDisplayType.MANUAL:
                    FanModeManual = true;
                    FanMode = CyFanModeType.FIRMWARE;
                    break;
                case CyFanModeDisplayType.AUTO_FIRMWARE:
                    FanModeManual = false;
                    FanMode = CyFanModeType.FIRMWARE;
                    break;
                case CyFanModeDisplayType.AUTO_HARDWARE:
                    FanModeManual = false;
                    FanMode = CyFanModeType.HARDWARE;
                    break;
            }
        }

        public byte AlertEnable
        {
            get { return GetValue<byte>(P_ALERT_ENABLE); }
            set { SetValue(P_ALERT_ENABLE, value); }
        }
        public CyPWMFreqType FanPWMFreq
        {
            get { return GetValue<CyPWMFreqType>(P_FAN_PWM_FREQ); }
            set { SetValue(P_FAN_PWM_FREQ, value); }
        }
        public CyPWMResType FanPWMRes
        {
            get { return GetValue<CyPWMResType>(P_FAN_PWM_RES); }
            set { SetValue(P_FAN_PWM_RES, value); }
        }
        /// <summary>
        /// ControlLoopPeriod is commited to symbol as byte and multiplied by 100
        /// </summary>
        public decimal ControlLoopPeriod
        {
            get { return (decimal)GetValue<byte>(P_DAMPING_FACTOR) / CyParamConst.CONTROL_LOOP_PERIOD_MULT; }
            set
            {
                byte val = (byte)Math.Round(value * CyParamConst.CONTROL_LOOP_PERIOD_MULT);
                SetValue(P_DAMPING_FACTOR, val);
            }
        }
        public byte AcousticNoiseReduction
        {
            get { return GetValue<byte>(P_ACOUSTIC_NOISE_REDUCTION); }
            set { SetValue(P_ACOUSTIC_NOISE_REDUCTION, value); }
        }
        public byte FanTolerance
        {
            get { return GetValue<byte>(P_FAN_TOLERANCE); }
            set { SetValue(P_FAN_TOLERANCE, value); }
        }
        public CyConnectinType Connection
        {
            get { return GetValue<CyConnectinType>(P_CONNECTION); }
            set { SetValue(P_CONNECTION, value); }
        }
        public bool ExternalClock
        {
            // External clock in the symbol is uint8 parameter (0=false, 1=true)
            get { return (GetValue<byte>(P_EXTERNAL_CLOCK) != 0); }
            set { SetValue(P_EXTERNAL_CLOCK, value ? (byte)1 : (byte)0); }
        }
        #endregion

        #region Fans tab parameters
        public CyMotorType MotorType
        {
            get { return GetValue<CyMotorType>(P_MOTOR_TYPE); }
            set { SetValue(P_MOTOR_TYPE, value); }
        }

        public int GetMinRPM(int i)
        {
            return GetValue<UInt16>(GetParamNameByIndex(P_MIN_RPM, i));
        }
        public void SetMinRPM(int i, UInt16 value)
        {
            SetValue(GetParamNameByIndex(P_MIN_RPM, i), value);
        }
        public int GetMaxRPM(int i)
        {
            return GetValue<UInt16>(GetParamNameByIndex(P_MAX_RPM, i));
        }
        public void SetMaxRPM(int i, UInt16 value)
        {
            SetValue(GetParamNameByIndex(P_MAX_RPM, i), value);
        }
        public int GetMinDuty(int i)
        {
            return GetValue<UInt16>(GetParamNameByIndex(P_MIN_DUTY, i));
        }
        public void SetMinDuty(int i, UInt16 value)
        {
            SetValue(GetParamNameByIndex(P_MIN_DUTY, i), value);
        }
        public int GetMaxDuty(int i)
        {
            return GetValue<UInt16>(GetParamNameByIndex(P_MAX_DUTY, i));
        }
        public void SetMaxDuty(int i, UInt16 value)
        {
            SetValue(GetParamNameByIndex(P_MAX_DUTY, i), value);
        }
        public UInt16 GetInitialRPM(int i)
        {
            return GetValue<UInt16>(GetParamNameByIndex(P_INITIAL_RPM, i));
        }
        public void SetInitialRPM(int i, UInt16 value)
        {
            SetValue(GetParamNameByIndex(P_INITIAL_RPM, i), value);
        }

        public bool BankMode
        {
            get { return (NumberOfBanks > 0) && BankAvailable; }
        }
        public bool BankAvailable
        {
            get { return GetFanMode() == CyFanModeDisplayType.MANUAL; }
        }
        #endregion

        #region PID tab parameters
        public double CoefProportional
        {
            get { return GetValue<double>(P_COEF_PROPORTIONAL); }
            set { SetValue(P_COEF_PROPORTIONAL, value); }
        }
        public double CoefIntegral
        {
            get { return GetValue<double>(P_COEF_INTEGRAL); }
            set { SetValue(P_COEF_INTEGRAL, value); }
        }
        public double CoefDerivative
        {
            get { return GetValue<double>(P_COEF_DERIVATIVE); }
            set { SetValue(P_COEF_DERIVATIVE, value); }
        }
        public double CoefUpperOutputLimit
        {
            get { return GetValue<double>(P_COEF_UPPER_OUTPUT_LIMIT); }
            set { SetValue(P_COEF_UPPER_OUTPUT_LIMIT, value); }
        }
        public double CoefLowerOutputLimit
        {
            get { return GetValue<double>(P_COEF_LOWER_OUTPUT_LIMIT); }
            set { SetValue(P_COEF_LOWER_OUTPUT_LIMIT, value); }
        }
        public sbyte CoefOutputAttenuation
        {
            get { return GetValue<sbyte>(P_COEF_OUTPUT_ATTENUATION); }
            set { SetValue(P_COEF_OUTPUT_ATTENUATION, value); }
        }
        #endregion 

        public bool IsPSoC4
        {
            get 
            {
                if (m_instQuery != null)
                    return m_instQuery.DeviceQuery.IsPSoC4;
                if (m_instValidate != null)
                    return m_instValidate.IsPSoC4;

                Debug.Assert(false);
                return false;
            }
        }

        /// <summary>
        /// Return parameter name in the symbol. Is used for parameters which name differs only by index.
        /// </summary>
        /// <param name="name">Common part of parameter's name</param>
        /// <param name="index">Parameter index</param>
        /// <returns>Full name</returns>
        public static string GetParamNameByIndex(string name, int index)
        {
            return name + (index+1).ToString().PadLeft(2,'0');
        }

        private T GetValue<T>(string paramName)
        {
            if (m_instQuery != null)
                return GetValue<T>(m_instQuery.GetCommittedParam(paramName));
            else if (m_instValidate != null)
                return GetValue<T>(m_instValidate.GetCommittedParam(paramName));
            else
            {
                Debug.Assert(false);
                return default(T);
            }
        }

        private T GetValue<T>(CyCompDevParam prm)
        {
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
                    valueToSet += "u";
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }

        /// <summary>
        /// Show/hide tabs depending on the Fan Mode
        /// </summary>
        public void UpdateTabVisibility()
        {
            if ((m_editor == null) || (m_pidTab == null))
                return;

            if (GetFanMode() == CyFanModeDisplayType.AUTO_FIRMWARE)
                m_editor.ShowCustomPage(Resources.PidTab);
            else 
                m_editor.HideCustomPage(Resources.PidTab);
        }
    }
}
