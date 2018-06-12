/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;
using CyDesigner.Extensions.Common;

namespace RTC_P4_v1_10
{

    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string P_ALARM_FUNCTIONALITY = "AlarmFunctionalityEn";
        public const string P_DATE_FORMAT = "DateFormat";
        public const string P_DATE_TYPE = "DstDateType";
        public const string P_DAYLIGHT_SAVINGS_TIME = "DaylightSavingsTimeEn";
        public const string P_DAY_OF_MONTH_START = "DayOfMonthDstStart";
        public const string P_DAY_OF_MONTH_STOP = "DayOfMonthDstStop";
        public const string P_DAY_OF_WEEK_START = "DayOfWeekDstStart";
        public const string P_DAY_OF_WEEK_STOP = "DayOfWeekDstStop";
        public const string P_HOURS_START = "HoursDstStart";
        public const string P_HOURS_STOP = "HoursDstStop";
        public const string P_MONTH_START = "MonthDstStart";
        public const string P_MONTH_STOP = "MonthDstStop";
        public const string P_TIME_FORMAT = "TimeFormat";
        public const string P_UPDATE_MANUALLY = "UpdateManually";
        public const string P_WEEK_OF_MONTH_START = "WeekOfMonthDstStart";
        public const string P_WEEK_OF_MONTH_STOP = "WeekOfMonthDstStop";
        public const string P_INITIAL_HOUR = "InitialHour";
        public const string P_INITIAL_MINUTE = "InitialMinute";
        public const string P_INITIAL_SECOND = "InitialSecond";
        public const string P_INITIAL_YEAR = "InitialYear";
        public const string P_INITIAL_MONTH = "InitialMonth";
        public const string P_INITIAL_DAY = "InitialDay";
    }
    #endregion

    #region Component Enums
    public enum CyETimeFormat
    {
        [Description("12-Hour")]    
        HOUR_12 = 1,
        [Description("24-Hour")]    
        HOUR_24 = 0
    }

    public enum CyEDateFormat
    {
        [Description("MM/DD/YYYY")]    
        MM_DD_YYYY,
        [Description("DD/MM/YYYY")]    
        DD_MM_YYYY,
        [Description("YYYY/MM/DD")]    
        YYYY_MM_DD
    }

    public enum CyEDateType
    {
        [Description("Relative")]    
        RELATIVE,
        [Description("Fixed")]       
        FIXED
    }


    public enum CyEHours
    {
        [Description("0000")]    
        H0000,
        [Description("0100")]    
        H0100,
        [Description("0200")]    
        H0200,
        [Description("0300")]    
        H0300,
        [Description("0400")]    
        H0400,
        [Description("0500")]    
        H0500,
        [Description("0600")]    
        H0600,
        [Description("0700")]    
        H0700,
        [Description("0800")]    
        H0800,
        [Description("0900")]    
        H0900,
        [Description("1000")]    
        H1000,
        [Description("1100")]    
        H1100,
        [Description("1200")]    
        H1200,
        [Description("1300")]    
        H1300,
        [Description("1400")]    
        H1400,
        [Description("1500")]    
        H1500,
        [Description("1600")]    
        H1600,
        [Description("1700")]    
        H1700,
        [Description("1800")]    
        H1800,
        [Description("1900")]    
        H1900,
        [Description("2000")]    
        H2000,
        [Description("2100")]    
        H2100,
        [Description("2200")]    
        H2200,
        [Description("2300")]    
        H2300
    }


    public enum CyEDayOfWeek
    {
        [Description("Sunday")]        
        SUNDAY = 1,
        [Description("Monday")]        
        MONDAY,
        [Description("Tuesday")]       
        TUESDAY,
        [Description("Wednesday")]     
        WEDNESDAY,
        [Description("Thursday")]      
        THURSDAY,
        [Description("Friday")]        
        FRIDAY,
        [Description("Saturday")]      
        SATURDAY
    }

    public enum CyEMonth
    {
        [Description("Jan")]     
        JAN = 1,
        [Description("Feb")]     
        FEB,
        [Description("Mar")]    
        MAR,
        [Description("Apr")]
        APR,
        [Description("May")]
        MAY,
        [Description("Jun")]
        JUN,
        [Description("Jul")]
        JUL,
        [Description("Aug")]
        AUG,
        [Description("Sep")]
        SEP,
        [Description("Oct")]
        OCT,
        [Description("Nov")]
        NOV,
        [Description("Dec")]
        DEC
    }

    public enum CyEWeekOfMonth
    {
        [Description("FirstWeekOfMonth")]
        FIRST = 1,
        [Description("SecondWeekOfMonth")]
        SECOND,
        [Description("ThirdWeekOfMonth")]
        THIRD,
        [Description("FourthWeekOfMonth")]
        FOURTH,
        [Description("FifthWeekOfMonth")]
        FIFTH,
        [Description("LastWeekOfMonth")]
        LAST
    }
    #endregion

    public class CyParameters
    {
        #region Class members
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private ICyTabbedParamEditor m_editor;

        // When parameters are first obtained, this variable is false, which means that assigned
        // values to form the controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        private bool? m_wcoClockExists = null;

        #endregion

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
        public ICyTabbedParamEditor Editor
        {
            get { return m_editor; }
            set { m_editor = value; }
        }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public bool WcoClockExists
        {
            get
            {
                // In order not to recalculate the parameter every time, cache its value. 
                if (m_wcoClockExists == null)
                {
                    bool ipHobtoDevice = InstQuery.DeviceQuery.GetFeatureCount("m0s8cpuss") != 1;
                    bool ipBless = InstQuery.DeviceQuery.GetFeatureCount("m0s8bless") != 0;
                    bool ipWco = InstQuery.DeviceQuery.GetFeatureCount("m0s8wco") == 1;
                    bool ipSrssv2 = InstQuery.DeviceQuery.GetFeatureParameter("m0s8srssv2", "EXCO.WCO_PRESENT") == 1;

                    m_wcoClockExists = ipHobtoDevice && (ipBless || ipWco || ipSrssv2);
                }
                return m_wcoClockExists.Value;
            }
        }

        public bool AlarmFunctionality
        {
            get { return GetValue<bool>(CyParamNames.P_ALARM_FUNCTIONALITY); }
            set { SetValue(CyParamNames.P_ALARM_FUNCTIONALITY, value); }
        }
        
        public bool DaylightSavingsTime
        {
            get { return GetValue<bool>(CyParamNames.P_DAYLIGHT_SAVINGS_TIME); }
            set { SetValue(CyParamNames.P_DAYLIGHT_SAVINGS_TIME, value); }
        }

        public bool UpdateManually
        {
            get { return GetValue<bool>(CyParamNames.P_UPDATE_MANUALLY); }
            set { SetValue(CyParamNames.P_UPDATE_MANUALLY, value); }
        }
        
        public CyEDateFormat DateFormat
        {
            get { return GetValue<CyEDateFormat>(CyParamNames.P_DATE_FORMAT); }
            set { SetValue(CyParamNames.P_DATE_FORMAT, value); }
        }

        public CyEDateType DateType
        {
            get { return GetValue<CyEDateType>(CyParamNames.P_DATE_TYPE); }
            set { SetValue(CyParamNames.P_DATE_TYPE, value); }
        }

        public byte DayOfMonthStart
        {
            get { return GetValue<byte>(CyParamNames.P_DAY_OF_MONTH_START); }
            set { SetValue(CyParamNames.P_DAY_OF_MONTH_START, value); }
        }

        public byte DayOfMonthStop
        {
            get { return GetValue<byte>(CyParamNames.P_DAY_OF_MONTH_STOP); }
            set { SetValue(CyParamNames.P_DAY_OF_MONTH_STOP, value); }
        }

        public CyEDayOfWeek DayOfWeekStart
        {
            get { return GetValue<CyEDayOfWeek>(CyParamNames.P_DAY_OF_WEEK_START); }
            set { SetValue(CyParamNames.P_DAY_OF_WEEK_START, value); }
        }

        public CyEDayOfWeek DayOfWeekStop
        {
            get { return GetValue<CyEDayOfWeek>(CyParamNames.P_DAY_OF_WEEK_STOP); }
            set { SetValue(CyParamNames.P_DAY_OF_WEEK_START, value); }
        }

        public CyEHours HoursStart
        {
            get { return GetValue<CyEHours>(CyParamNames.P_HOURS_START); }
            set { SetValue(CyParamNames.P_HOURS_START, value); }
        }

        public CyEHours HoursStop
        {
            get { return GetValue<CyEHours>(CyParamNames.P_HOURS_STOP); }
            set { SetValue(CyParamNames.P_HOURS_STOP, value); }
        }

        public CyEMonth MonthStart
        {
            get { return GetValue<CyEMonth>(CyParamNames.P_MONTH_START); }
            set { SetValue(CyParamNames.P_MONTH_START, value); }
        }

        public CyEMonth MonthStop
        {
            get { return GetValue<CyEMonth>(CyParamNames.P_MONTH_STOP); }
            set { SetValue(CyParamNames.P_MONTH_STOP, value); }
        }

        public CyETimeFormat TimeFormat
        {
            get { return GetValue<CyETimeFormat>(CyParamNames.P_TIME_FORMAT); }
            set { SetValue(CyParamNames.P_TIME_FORMAT, value); }
        }

        public CyEWeekOfMonth WeekOfMonthStart
        {
            get { return GetValue<CyEWeekOfMonth>(CyParamNames.P_WEEK_OF_MONTH_START); }
            set { SetValue(CyParamNames.P_WEEK_OF_MONTH_START, value); }
        }

        public CyEWeekOfMonth WeekOfMonthStop
        {
            get { return GetValue<CyEWeekOfMonth>(CyParamNames.P_WEEK_OF_MONTH_STOP); }
            set { SetValue(CyParamNames.P_WEEK_OF_MONTH_STOP, value); }
        }
                
        public UInt16 InitialHour
        {
            get { return GetValue<UInt16>(CyParamNames.P_INITIAL_HOUR); }
            set { SetValue(CyParamNames.P_INITIAL_HOUR, value); }
        }

        public UInt16 InitialMinute
        {
            get { return GetValue<UInt16>(CyParamNames.P_INITIAL_MINUTE); }
            set { SetValue(CyParamNames.P_INITIAL_MINUTE, value); }
        }

        public UInt16 InitialSecond
        {
            get { return GetValue<UInt16>(CyParamNames.P_INITIAL_SECOND); }
            set { SetValue(CyParamNames.P_INITIAL_SECOND, value); }
        }

        public UInt16 InitialYear
        {
            get { return GetValue<UInt16>(CyParamNames.P_INITIAL_YEAR); }
            set { SetValue(CyParamNames.P_INITIAL_YEAR, value); }
        }

        public UInt16 InitialMonth
        {
            get { return GetValue<UInt16>(CyParamNames.P_INITIAL_MONTH); }
            set { SetValue(CyParamNames.P_INITIAL_MONTH, value); }
        }
        
        public UInt16 InitialDay
        {
            get { return GetValue<UInt16>(CyParamNames.P_INITIAL_DAY); }
            set { SetValue(CyParamNames.P_INITIAL_DAY, value); }
        }
        
        #endregion

        #region Getting Parameter
        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null) return default(T);
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }
        #endregion

        #region Setting Parameter
        private void SetValue<T>(string paramName, T value)
        {
            if (m_instEdit != null && m_globalEditMode)
            {
                string valueToSet = (value == null) ? String.Empty : value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((value is byte) || (value is UInt16) || (value is UInt32) || (value is UInt64))
                    valueToSet += "u";
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }
        #endregion
        
        #region Get descriptions list
        public string[] GetEnumDescriptions(string paramName)
        {
            return new List<string>(m_instQuery.GetPossibleEnumValues(paramName)).ToArray();
        }
        #endregion

    }
}
