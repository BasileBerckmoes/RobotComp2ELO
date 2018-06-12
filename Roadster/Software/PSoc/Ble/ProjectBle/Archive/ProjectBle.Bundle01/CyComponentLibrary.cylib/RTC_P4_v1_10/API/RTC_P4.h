/***************************************************************************//**
* \file Name: `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the RTC_P4 Component.
*
********************************************************************************
* Copyright 2015-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_RTC_P4_`$INSTANCE_NAME`_H)
#define CY_RTC_P4_`$INSTANCE_NAME`_H

#include <cytypes.h>
#include <CyLib.h>


/*******************************************************************************
*    Data types definition
*******************************************************************************/

typedef enum
{
    `$INSTANCE_NAME`_DST_DATE_RELATIVE = 0u,
    `$INSTANCE_NAME`_DST_DATE_FIXED = 1u
}`$INSTANCE_NAME`_DST_DATETYPE_ENUM;

/**
* \addtogroup group_structures
* @{
*/

/**
* This is the data structure that is used to save the current time and date 
* (RTC_currentTimeDate), and Alarm time and date (RTC_alarmCfgTimeDate).
*/
typedef struct
{
    uint32 time;
    uint32 date;
    uint32 dayOfWeek;
    uint32 status;
}`$INSTANCE_NAME`_DATE_TIME;

/**
* This is the data structure that is used to save time and date values for 
* Daylight Savings Time Start and Stop (RTC_dstTimeDateStart and 
* RTC_dstTimeDateStop).
*/
typedef struct
{
    uint32 hour;
    uint32 dayOfWeek;
    uint32 dayOfMonth;
    uint32 weekOfMonth;
    uint32 month;
    uint8  timeFormat;
}`$INSTANCE_NAME`_DST_TIME;

/** @} structures */

/*******************************************************************************
*    Enumerated Types and Parameters
*******************************************************************************/
/* Time Format setting constants */
`#cy_declare_enum TimeFormatEnum`
/*  Date Format setting constants */
`#cy_declare_enum DateFormatEnum`
/* Date Type setting constants */
`#cy_declare_enum DateTypeEnum`
/* DST Hour setting constants */
`#cy_declare_enum HoursEnum`
/* DST DayOfWeek setting constants */
`#cy_declare_enum DayOfWeekEnum`
/* DST Month setting constants */
`#cy_declare_enum MonthEnum`
/* DST WeekOfMonth setting constants */
`#cy_declare_enum WeekOfMonthEnum`

#define `$INSTANCE_NAME`_INITIAL_DATA_FORMAT     (`$DateFormat`u)
#define `$INSTANCE_NAME`_INITIAL_TIME_FORMAT     (`$TimeFormat`u)
#define `$INSTANCE_NAME`_INITIAL_UPDATE_MODE     (`$UpdateManually`u)
#define `$INSTANCE_NAME`_INITIAL_SECOND          (`$InitialSecond`u)
#define `$INSTANCE_NAME`_INITIAL_MINUTE          (`$InitialMinute`u)
#define `$INSTANCE_NAME`_INITIAL_HOUR            (`$InitialHour`u)
#define `$INSTANCE_NAME`_INITIAL_DAY             (`$InitialDay`u)
#define `$INSTANCE_NAME`_INITIAL_MONTH           (`$InitialMonth`u)
#define `$INSTANCE_NAME`_INITIAL_YEAR            (`$InitialYear`u)

#define `$INSTANCE_NAME`_INITIAL_ALARM_STATUS    (`$AlarmFunctionalityEn`u)

#define `$INSTANCE_NAME`_INITIAL_DST_STATUS      (`$DaylightSavingsTimeEn`u)
#define `$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE   (`$DstDateType`u)
#define `$INSTANCE_NAME`_INITIAL_DST_START_MONTH (`$MonthDstStart`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_START_WOM   (`$WeekOfMonthDstStart`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_START_DOM   (`$DayOfMonthDstStart`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_START_DOW   (`$DayOfWeekDstStart`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_START_HRS   (`$HoursDstStart`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_STOP_MONTH  (`$MonthDstStop`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_STOP_DOM    (`$DayOfMonthDstStop`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_STOP_DOW    (`$DayOfWeekDstStop`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_STOP_WOM    (`$WeekOfMonthDstStop`uL)
#define `$INSTANCE_NAME`_INITIAL_DST_STOP_HRS    (`$HoursDstStop`uL)

/* Day of week definitions */
#define `$INSTANCE_NAME`_SUNDAY     (`$INSTANCE_NAME`__SUNDAY)
#define `$INSTANCE_NAME`_MONDAY     (`$INSTANCE_NAME`__MONDAY)
#define `$INSTANCE_NAME`_TUESDAY    (`$INSTANCE_NAME`__TUESDAY)
#define `$INSTANCE_NAME`_WEDNESDAY  (`$INSTANCE_NAME`__WEDNESDAY)
#define `$INSTANCE_NAME`_THURSDAY   (`$INSTANCE_NAME`__THURSDAY)
#define `$INSTANCE_NAME`_FRIDAY     (`$INSTANCE_NAME`__FRIDAY)
#define `$INSTANCE_NAME`_SATURDAY   (`$INSTANCE_NAME`__SATURDAY)

/* DST WeekOfMonth setting constants definitions */
#define `$INSTANCE_NAME`_FIRST      (`$INSTANCE_NAME`__FIRST)
#define `$INSTANCE_NAME`_SECOND     (`$INSTANCE_NAME`__SECOND)
#define `$INSTANCE_NAME`_THIRD      (`$INSTANCE_NAME`__THIRD)
#define `$INSTANCE_NAME`_FOURTH     (`$INSTANCE_NAME`__FOURTH)
#define `$INSTANCE_NAME`_FIFTH      (`$INSTANCE_NAME`__FIFTH)
#define `$INSTANCE_NAME`_LAST       (`$INSTANCE_NAME`__LAST)

/* Month definitions */
#define `$INSTANCE_NAME`_JANUARY    (`$INSTANCE_NAME`__JAN)
#define `$INSTANCE_NAME`_FEBRUARY   (`$INSTANCE_NAME`__FEB)
#define `$INSTANCE_NAME`_MARCH      (`$INSTANCE_NAME`__MAR)
#define `$INSTANCE_NAME`_APRIL      (`$INSTANCE_NAME`__APR)
#define `$INSTANCE_NAME`_MAY        (`$INSTANCE_NAME`__MAY)
#define `$INSTANCE_NAME`_JUNE       (`$INSTANCE_NAME`__JUN)
#define `$INSTANCE_NAME`_JULY       (`$INSTANCE_NAME`__JUL)
#define `$INSTANCE_NAME`_AUGUST     (`$INSTANCE_NAME`__AUG)
#define `$INSTANCE_NAME`_SEPTEMBER  (`$INSTANCE_NAME`__SEP)
#define `$INSTANCE_NAME`_OCTOBER    (`$INSTANCE_NAME`__OCT)
#define `$INSTANCE_NAME`_NOVEMBER   (`$INSTANCE_NAME`__NOV)
#define `$INSTANCE_NAME`_DECEMBER   (`$INSTANCE_NAME`__DEC)

#define `$INSTANCE_NAME`_DAYS_PER_WEEK       (7u)

/* Number of days in month definitions */
#define `$INSTANCE_NAME`_DAYS_IN_JANUARY     (31u)
#define `$INSTANCE_NAME`_DAYS_IN_FEBRUARY    (28u)
#define `$INSTANCE_NAME`_DAYS_IN_MARCH       (31u)
#define `$INSTANCE_NAME`_DAYS_IN_APRIL       (30u)
#define `$INSTANCE_NAME`_DAYS_IN_MAY         (31u)
#define `$INSTANCE_NAME`_DAYS_IN_JUNE        (30u)
#define `$INSTANCE_NAME`_DAYS_IN_JULY        (31u)
#define `$INSTANCE_NAME`_DAYS_IN_AUGUST      (31u)
#define `$INSTANCE_NAME`_DAYS_IN_SEPTEMBER   (30u)
#define `$INSTANCE_NAME`_DAYS_IN_OCTOBER     (31u)
#define `$INSTANCE_NAME`_DAYS_IN_NOVEMBER    (30u)
#define `$INSTANCE_NAME`_DAYS_IN_DECEMBER    (31u)

#define `$INSTANCE_NAME`_MONTHS_PER_YEAR     (12uL)

#define `$INSTANCE_NAME`_HOURS_PER_DAY       (24uL)
#define `$INSTANCE_NAME`_HOURS_PER_HALF_DAY  (12uL)

#define `$INSTANCE_NAME`_SECONDS_PER_MINUTE  (60uL)
#define `$INSTANCE_NAME`_SECONDS_PER_HOUR    (3600uL)
#define `$INSTANCE_NAME`_SECONDS_PER_DAY     (24uL * 3600uL)

#define `$INSTANCE_NAME`_SECONDS_PER_LEAP_YEAR    (366uL * 24uL * 3600uL)
#define `$INSTANCE_NAME`_SECONDS_PER_NONLEAP_YEAR (365uL * 24uL * 3600uL)

#define `$INSTANCE_NAME`_UNIX_TIME_PM   ((12uL * 3600uL) + 1uL)

/* AM/PM status definitions */
#define `$INSTANCE_NAME`_AM                 (0u)
#define `$INSTANCE_NAME`_PM                 (1u)

/* Time format definitions */
#define `$INSTANCE_NAME`_12_HOURS_FORMAT    (`$INSTANCE_NAME`__HOUR_12)
#define `$INSTANCE_NAME`_24_HOURS_FORMAT    (`$INSTANCE_NAME`__HOUR_24)

/* UNIX time begins in 1970 year.  */
#define `$INSTANCE_NAME`_YEAR_0             (1970u)

/* Definition of date register fields */
#if(`$INSTANCE_NAME`_INITIAL_DATA_FORMAT == `$INSTANCE_NAME`__MM_DD_YYYY)
    #define `$INSTANCE_NAME`_10_MONTH_OFFSET   (28u)
    #define `$INSTANCE_NAME`_MONTH_OFFSET      (24u)
    #define `$INSTANCE_NAME`_10_DAY_OFFSET     (20u)
    #define `$INSTANCE_NAME`_DAY_OFFSET        (16u)
    #define `$INSTANCE_NAME`_1000_YEAR_OFFSET  (12u)
    #define `$INSTANCE_NAME`_100_YEAR_OFFSET   (8u)
    #define `$INSTANCE_NAME`_10_YEAR_OFFSET    (4u)
    #define `$INSTANCE_NAME`_YEAR_OFFSET       (0u)
#elif(`$INSTANCE_NAME`_INITIAL_DATA_FORMAT == `$INSTANCE_NAME`__DD_MM_YYYY)
    #define `$INSTANCE_NAME`_10_MONTH_OFFSET   (20u)
    #define `$INSTANCE_NAME`_MONTH_OFFSET      (16u)
    #define `$INSTANCE_NAME`_10_DAY_OFFSET     (28u)
    #define `$INSTANCE_NAME`_DAY_OFFSET        (24u)
    #define `$INSTANCE_NAME`_1000_YEAR_OFFSET  (12u)
    #define `$INSTANCE_NAME`_100_YEAR_OFFSET   (8u)
    #define `$INSTANCE_NAME`_10_YEAR_OFFSET    (4u)
    #define `$INSTANCE_NAME`_YEAR_OFFSET       (0u)
#else
    #define `$INSTANCE_NAME`_10_MONTH_OFFSET   (12u)
    #define `$INSTANCE_NAME`_MONTH_OFFSET      (8u)
    #define `$INSTANCE_NAME`_10_DAY_OFFSET     (4u)
    #define `$INSTANCE_NAME`_DAY_OFFSET        (0u)
    #define `$INSTANCE_NAME`_1000_YEAR_OFFSET  (28u)
    #define `$INSTANCE_NAME`_100_YEAR_OFFSET   (24u)
    #define `$INSTANCE_NAME`_10_YEAR_OFFSET    (20u)
    #define `$INSTANCE_NAME`_YEAR_OFFSET       (16u)
#endif /* (`$INSTANCE_NAME`_INITIAL_DATA_FORMAT == `$INSTANCE_NAME`__MM_DD_YYYY) */

#define `$INSTANCE_NAME`_10_MONTH_MASK          (0x00000001uL << `$INSTANCE_NAME`_10_MONTH_OFFSET)
#define `$INSTANCE_NAME`_MONTH_MASK             (0x0000000FuL << `$INSTANCE_NAME`_MONTH_OFFSET)
#define `$INSTANCE_NAME`_10_DAY_MASK            (0x00000003uL << `$INSTANCE_NAME`_10_DAY_OFFSET)
#define `$INSTANCE_NAME`_DAY_MASK               (0x0000000FuL << `$INSTANCE_NAME`_DAY_OFFSET)
#define `$INSTANCE_NAME`_1000_YEAR_MASK         (0x00000003uL << `$INSTANCE_NAME`_1000_YEAR_OFFSET)
#define `$INSTANCE_NAME`_100_YEAR_MASK          (0x0000000FuL << `$INSTANCE_NAME`_100_YEAR_OFFSET)
#define `$INSTANCE_NAME`_10_YEAR_MASK           (0x0000000FuL << `$INSTANCE_NAME`_10_YEAR_OFFSET)
#define `$INSTANCE_NAME`_YEAR_MASK              (0x0000000FuL << `$INSTANCE_NAME`_YEAR_OFFSET)

#define  `$INSTANCE_NAME`_MONTH_FULL_MASK       (`$INSTANCE_NAME`_10_MONTH_MASK  | `$INSTANCE_NAME`_MONTH_MASK)
#define  `$INSTANCE_NAME`_DAY_FULL_MASK         (`$INSTANCE_NAME`_10_DAY_MASK    | `$INSTANCE_NAME`_DAY_MASK)
#define  `$INSTANCE_NAME`_YEAR_FULL_MASK        (`$INSTANCE_NAME`_1000_YEAR_MASK | `$INSTANCE_NAME`_100_YEAR_MASK |\
                                                 `$INSTANCE_NAME`_10_YEAR_MASK   | `$INSTANCE_NAME`_YEAR_MASK)


/* Definition of time register fields */
#define `$INSTANCE_NAME`_TIME_FORMAT_OFFSET     (23u)
#define `$INSTANCE_NAME`_PERIOD_OF_DAY_OFFSET   (22u)
#define `$INSTANCE_NAME`_10_HOURS_OFFSET        (20u)
#define `$INSTANCE_NAME`_HOURS_OFFSET           (16u)
#define `$INSTANCE_NAME`_10_MINUTES_OFFSET      (12u)
#define `$INSTANCE_NAME`_MINUTES_OFFSET         (8u)
#define `$INSTANCE_NAME`_10_SECONDS_OFFSET      (4u)
#define `$INSTANCE_NAME`_SECONDS_OFFSET         (0u)

#define `$INSTANCE_NAME`_TIME_FORMAT_MASK       (0x00000001uL << `$INSTANCE_NAME`_TIME_FORMAT_OFFSET)
#define `$INSTANCE_NAME`_PERIOD_OF_DAY_MASK     (0x00000001uL << `$INSTANCE_NAME`_PERIOD_OF_DAY_OFFSET)
#define `$INSTANCE_NAME`_10_HOURS_MASK          (0x00000003uL << `$INSTANCE_NAME`_10_HOURS_OFFSET)
#define `$INSTANCE_NAME`_HOURS_MASK             (0x0000000FuL << `$INSTANCE_NAME`_HOURS_OFFSET)
#define `$INSTANCE_NAME`_10_MINUTES_MASK        (0x00000007uL << `$INSTANCE_NAME`_10_MINUTES_OFFSET)
#define `$INSTANCE_NAME`_MINUTES_MASK           (0x0000000FuL << `$INSTANCE_NAME`_MINUTES_OFFSET)
#define `$INSTANCE_NAME`_10_SECONDS_MASK        (0x00000007uL << `$INSTANCE_NAME`_10_SECONDS_OFFSET)
#define `$INSTANCE_NAME`_SECONDS_MASK           (0x0000000FuL << `$INSTANCE_NAME`_SECONDS_OFFSET)

#define `$INSTANCE_NAME`_HOURS_FULL_MASK        (`$INSTANCE_NAME`_10_HOURS_MASK   | `$INSTANCE_NAME`_HOURS_MASK)
#define `$INSTANCE_NAME`_MINUTES_FULL_MASK      (`$INSTANCE_NAME`_10_MINUTES_MASK | `$INSTANCE_NAME`_MINUTES_MASK)
#define `$INSTANCE_NAME`_SECONDS_FULL_MASK      (`$INSTANCE_NAME`_10_SECONDS_MASK | `$INSTANCE_NAME`_SECONDS_MASK)

#define `$INSTANCE_NAME`_ALARM_SEC_MASK         (0x00000001uL)
#define `$INSTANCE_NAME`_ALARM_MIN_MASK         (0x00000002uL)
#define `$INSTANCE_NAME`_ALARM_HOUR_MASK        (0x00000004uL)
#define `$INSTANCE_NAME`_ALARM_DAYOFWEEK_MASK   (0x00000008uL)
#define `$INSTANCE_NAME`_ALARM_DAYOFMONTH_MASK  (0x00000010uL)
#define `$INSTANCE_NAME`_ALARM_MONTH_MASK       (0x00000020uL)
#define `$INSTANCE_NAME`_ALARM_YEAR_MASK        (0x00000040uL)

#define `$INSTANCE_NAME`_STATUS_DST_OFFSET      (1u)
#define `$INSTANCE_NAME`_STATUS_ALARM_OFFSET    (2u)
#define `$INSTANCE_NAME`_STATUS_LY_OFFSET       (3u)
#define `$INSTANCE_NAME`_STATUS_AM_PM_OFFSET    (4u)

/* Definition of the RTC status values. */
#define `$INSTANCE_NAME`_STATUS_DST             (1uL << `$INSTANCE_NAME`_STATUS_DST_OFFSET)
#define `$INSTANCE_NAME`_STATUS_LY              (1uL << `$INSTANCE_NAME`_STATUS_LY_OFFSET)
#define `$INSTANCE_NAME`_STATUS_AM_PM           (1uL << `$INSTANCE_NAME`_STATUS_AM_PM_OFFSET)

/* Number of bits per one BCD digit. */
#define `$INSTANCE_NAME`_BCD_NUMBER_SIZE        (4u)
#define `$INSTANCE_NAME`_BCD_ONE_DIGIT_MASK     (0x0000000FuL)

/*******************************************************************************
*    Function Prototypes
*******************************************************************************/
/**
* \addtogroup group_api
* @{
*/
void   `$INSTANCE_NAME`_Start(void);
void   `$INSTANCE_NAME`_Stop(void);
void   `$INSTANCE_NAME`_Init(void);
void   `$INSTANCE_NAME`_SetUnixTime(uint64 unixTime);
uint64 `$INSTANCE_NAME`_GetUnixTime(void);
void   `$INSTANCE_NAME`_SetPeriod(uint32 ticks, uint32 refOneSecTicks);
uint32 `$INSTANCE_NAME`_GetPeriod(void);
uint32 `$INSTANCE_NAME`_GetRefOneSec(void);
void   `$INSTANCE_NAME`_SetDateAndTime(uint32 inputTime, uint32 inputDate);
void   `$INSTANCE_NAME`_GetDateAndTime(`$INSTANCE_NAME`_DATE_TIME* dateTime);
uint32 `$INSTANCE_NAME`_GetTime(void);
uint32 `$INSTANCE_NAME`_GetDate(void);
void   `$INSTANCE_NAME`_SetAlarmDateAndTime(const `$INSTANCE_NAME`_DATE_TIME* alarmTime);
void   `$INSTANCE_NAME`_GetAlarmDateAndTime(`$INSTANCE_NAME`_DATE_TIME* alarmTimeDate);
void   `$INSTANCE_NAME`_SetAlarmMask(uint32 mask);
uint32 `$INSTANCE_NAME`_GetAlarmMask(void);
uint32 `$INSTANCE_NAME`_ReadStatus(void);
uint32 `$INSTANCE_NAME`_GetAlarmStatus(void);
void   `$INSTANCE_NAME`_ClearAlarmStatus(void);
void   `$INSTANCE_NAME`_SetDSTStartTime(const `$INSTANCE_NAME`_DST_TIME* dstStartTime,
                                              `$INSTANCE_NAME`_DST_DATETYPE_ENUM type);
void   `$INSTANCE_NAME`_SetDSTStopTime(const `$INSTANCE_NAME`_DST_TIME* dstStopTime,
                                             `$INSTANCE_NAME`_DST_DATETYPE_ENUM type);
uint32 `$INSTANCE_NAME`_ConvertBCDToDec(uint32 bcdNum);
uint32 `$INSTANCE_NAME`_ConvertDecToBCD(uint32 decNum);
void   `$INSTANCE_NAME`_Update(void);
void*  `$INSTANCE_NAME`_SetAlarmHandler(void (*CallbackFunction)(void));

static uint32 `$INSTANCE_NAME`_ConstructDate(uint32 month, uint32 day, uint32 year);
static uint32 `$INSTANCE_NAME`_ConstructTime(uint32 timeFormat, uint32 stateAmPm, uint32 hour, uint32 min, uint32 sec);
/** @} api */

static uint32 `$INSTANCE_NAME`_GetTimeFormat(uint32 inputTime);
static uint32 `$INSTANCE_NAME`_SetTimeFormat(uint32 inputTime, uint32 timeFormat);

/**
* \addtogroup group_api
* @{
*/
static uint32 `$INSTANCE_NAME`_LeapYear(uint32 year);
static uint32 `$INSTANCE_NAME`_IsBitSet(uint32 var, uint32 mask);
static uint32 `$INSTANCE_NAME`_GetSecond(uint32 inputTime);
static uint32 `$INSTANCE_NAME`_GetMinutes(uint32 inputTime);
static uint32 `$INSTANCE_NAME`_GetHours(uint32 inputTime);
static uint32 `$INSTANCE_NAME`_GetAmPm(uint32 inputTime);
static uint32 `$INSTANCE_NAME`_GetDay(uint32 date);
static uint32 `$INSTANCE_NAME`_GetMonth(uint32 date);
static uint32 `$INSTANCE_NAME`_GetYear(uint32 date);
/** @} api */

static uint32 `$INSTANCE_NAME`_SetSecond(uint32 inputTime, uint32 inputSecond);
static uint32 `$INSTANCE_NAME`_SetMinutes(uint32 inputTime, uint32 inputMinute);
static uint32 `$INSTANCE_NAME`_SetHours(uint32 inputTime, uint32 inputHours);
static uint32 `$INSTANCE_NAME`_SetAmPm(uint32 inputTime, uint32 periodOfDay);
static uint32 `$INSTANCE_NAME`_SetDay(uint32 inputDate, uint32 inputDay);
static uint32 `$INSTANCE_NAME`_SetMonth(uint32 inputDate, uint32 inputMonth);
static uint32 `$INSTANCE_NAME`_SetYear(uint32 inputDate, uint32 inputYear);

uint64 `$INSTANCE_NAME`_ConstructUnixAlarmTime(const `$INSTANCE_NAME`_DATE_TIME* alarmTime, uint8 alarmCfgMask);
uint64 `$INSTANCE_NAME`_GetDstUnixTime(const `$INSTANCE_NAME`_DST_TIME* dstTime);
uint64 `$INSTANCE_NAME`_GetNexAlarmTime(uint64 curUnixTime, uint8 alarmCfgMask);

static uint32 `$INSTANCE_NAME`_GetNextMinSec(uint32 curVal);
static uint32 `$INSTANCE_NAME`_GetNextHour(uint32 curVal);
static uint32 `$INSTANCE_NAME`_GetNextDay(uint32 curYear, uint32 curMonth, uint32 curDay, uint32 alarmCfgMask);
static uint32 `$INSTANCE_NAME`_GetNextMonth(uint32 curMonth);
static uint32 `$INSTANCE_NAME`_GetNextYear(uint32 curYear);
static uint32 `$INSTANCE_NAME`_GetDayOfWeek(uint32 day, uint32 month, uint32 year);

uint32 `$INSTANCE_NAME`_DaysInMonth(uint32 month, uint32 year);
uint32 `$INSTANCE_NAME`_DaysBeforeMonth(uint32 month, uint32 year);

/**
* \addtogroup group_api
* @{
*/
void   `$INSTANCE_NAME`_UnixToDateTime(`$INSTANCE_NAME`_DATE_TIME* dateTime, uint64 unixTime, uint32 timeFormat);
uint64 `$INSTANCE_NAME`_DateTimeToUnix(uint32 inputDate, uint32 inputTime);
/** @} api */

uint32 `$INSTANCE_NAME`_RelativeToFixed(uint32 dayOfWeek, uint32 weekOfMonth, uint32 month, uint32 year);


#if defined(CYDEV_RTC_SOURCE_WDT)
    #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE))
        static void `$INSTANCE_NAME`_CySysRtcSetCallback(uint32 wdtNumber);
        static void `$INSTANCE_NAME`_CySysRtcResetCallback(uint32 wdtNumber);
    #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE)) */
#endif /* (CYDEV_RTC_SOURCE_WDT) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBitSet
****************************************************************************//**
*
* \brief
*  Checks the state of a bit passed through parameter.
*
* \param
*  var The variable to be checked.
* \param
*  mask The mask for a bit to be checked.
*
* \return
*  0u - Bit is not set.
* \return
*  1u - Bit is set.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_IsBitSet(uint32 var, uint32 mask)
{
    return ((mask == (var & mask)) ? 1Lu : 0Lu);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LeapYear
****************************************************************************//**
*
* \brief
* Checks whether the year passed through the parameter is
* leap or no.
*
* \param
*  year The year to be checked.
*
*
* \return
*  0u - The year is not leap.
* \return
*  1u - The year is leap.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_LeapYear(uint32 year)
{
    uint32 retVal;

    if(((0u == (year % 4Lu)) && (0u != (year % 100Lu))) || (0u == (year % 400Lu)))
    {
        retVal = 1uL;
    }
    else
    {
        retVal = 0uL;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSecond
****************************************************************************//**
*
* \brief
*  Returns the seconds value from the time value that is passed as a/the parameter.
*
* \param
*  time The time value.
*
* \return
*  The seconds value.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetSecond(uint32 inputTime)
{
    uint32 retVal;

    retVal  = ((inputTime & `$INSTANCE_NAME`_10_SECONDS_MASK) >> `$INSTANCE_NAME`_10_SECONDS_OFFSET) * 10u;
    retVal += (inputTime & `$INSTANCE_NAME`_SECONDS_MASK) >> `$INSTANCE_NAME`_SECONDS_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMinutes
****************************************************************************//**
*
* \brief
*  Returns the minutes value from the time value that is passed as a/the 
* parameter.
*
* \param
*  time The time value.
*
* \return
*  The minutes value.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetMinutes(uint32 inputTime)
{
    uint32 retVal;

    retVal  = ((inputTime & `$INSTANCE_NAME`_10_MINUTES_MASK) >> `$INSTANCE_NAME`_10_MINUTES_OFFSET) * 10u;
    retVal += (inputTime & `$INSTANCE_NAME`_MINUTES_MASK) >> `$INSTANCE_NAME`_MINUTES_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetHours
****************************************************************************//**
*
* \brief
*  Returns the hours value from the time value that is passed as a/the parameter.
*
* \param
*  time The time value.
*
* \return
*  The hours value.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetHours(uint32 inputTime)
{
    uint32 retVal;

    retVal  = ((inputTime & `$INSTANCE_NAME`_10_HOURS_MASK) >> `$INSTANCE_NAME`_10_HOURS_OFFSET) * 10u;
    retVal += (inputTime & `$INSTANCE_NAME`_HOURS_MASK) >> `$INSTANCE_NAME`_HOURS_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAmPm
****************************************************************************//**
*
* \brief
*  Returns the AM/PM status from the time value that is passed as parameter.
*
* \param
*  time The time value.
*
* \return
*  `$INSTANCE_NAME`_AM - AM.
* \return
*  `$INSTANCE_NAME`_PM - PM.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetAmPm(uint32 inputTime)
{
    return (`$INSTANCE_NAME`_IsBitSet(inputTime, `$INSTANCE_NAME`_PERIOD_OF_DAY_MASK));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDay
****************************************************************************//**
*
* \brief
*  Returns the day value from the date value that is passed as parameter.
*
* \param
*  date The date value.
*
* \return
*  The day value.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetDay(uint32 date)
{
    uint32 retVal;

    retVal  = ((date & `$INSTANCE_NAME`_10_DAY_MASK) >> `$INSTANCE_NAME`_10_DAY_OFFSET) * 10u;
    retVal += (date & `$INSTANCE_NAME`_DAY_MASK) >> `$INSTANCE_NAME`_DAY_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMonth
****************************************************************************//**
*
* \brief
*  Returns the month value from the date value that is passed as parameter.
*
* \param
*  date The date value.
*
* \return
*  The month value.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetMonth(uint32 date)
{
    uint32 retVal;

    retVal  = ((date & `$INSTANCE_NAME`_10_MONTH_MASK) >> `$INSTANCE_NAME`_10_MONTH_OFFSET) * 10u;
    retVal += (date & `$INSTANCE_NAME`_MONTH_MASK) >> `$INSTANCE_NAME`_MONTH_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetYear
****************************************************************************//**
*
* \brief
*  Returns the year value from the date value that is passed as parameter.
*
* \param
*  date The date value.
*
* \return
*  The year value.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetYear(uint32 date)
{
    uint32 retVal;

    retVal  = ((date & `$INSTANCE_NAME`_1000_YEAR_MASK) >> `$INSTANCE_NAME`_1000_YEAR_OFFSET) * 1000u;
    retVal += ((date & `$INSTANCE_NAME`_100_YEAR_MASK) >> `$INSTANCE_NAME`_100_YEAR_OFFSET) * 100u;
    retVal += ((date & `$INSTANCE_NAME`_10_YEAR_MASK) >> `$INSTANCE_NAME`_10_YEAR_OFFSET) * 10u;
    retVal += (date & `$INSTANCE_NAME`_YEAR_MASK) >> `$INSTANCE_NAME`_YEAR_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSecond
****************************************************************************//**
*\internal
* \brief
*  Updates the time with the new second value.
*
* \param
* time The current date.
* \param
* second The seconds value to be set to the time variable.
*
* \return
*  The updated time variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetSecond(uint32 inputTime, uint32 inputSecond)
{
    inputTime &= ~(`$INSTANCE_NAME`_SECONDS_FULL_MASK);

    inputTime |= (inputSecond / 10u) << `$INSTANCE_NAME`_10_SECONDS_OFFSET;
    inputTime |= (inputSecond % 10u) << `$INSTANCE_NAME`_SECONDS_OFFSET;

    return(inputTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMinutes
****************************************************************************//**
*\internal
* \brief
*  Updates the time with the new minute value.
*
* \param
*  time The current date.
* \param
*  minutes The minutes value to be set to the time variable.
*
* \return
*  The updated time variable.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetMinutes(uint32 inputTime, uint32 inputMinute)
{
    inputTime &= ~(`$INSTANCE_NAME`_MINUTES_FULL_MASK);

    inputTime |= (inputMinute / 10u) << `$INSTANCE_NAME`_10_MINUTES_OFFSET;
    inputTime |= (inputMinute % 10u) << `$INSTANCE_NAME`_MINUTES_OFFSET;

    return(inputTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetHours
****************************************************************************//**
*\internal
* \brief
*  Updates the time with the new hour value.
*
* \param
* time The current date.
* \param
* hours The hours value to be set to the time variable.
*
* \return
*  The updated time variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetHours(uint32 inputTime, uint32 inputHours)
{
    inputTime &= ~(`$INSTANCE_NAME`_HOURS_FULL_MASK);

    inputTime |= (inputHours / 10u) << `$INSTANCE_NAME`_10_HOURS_OFFSET;
    inputTime |= (inputHours % 10u) << `$INSTANCE_NAME`_HOURS_OFFSET;

    return(inputTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAmPm
****************************************************************************//**
*\internal
* \brief
*  Updates the time variable with the AmPm status.
*
* \param
* time The current date.
* \param
* periodOfDay The AmPm status to be set to the time variable.
*
* \return
*  The updated time variable.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetAmPm(uint32 inputTime, uint32 periodOfDay)
{
    if(0u != periodOfDay)
    {
        inputTime &= ~(`$INSTANCE_NAME`_PERIOD_OF_DAY_MASK);
    }
    else
    {
        inputTime |= `$INSTANCE_NAME`_PERIOD_OF_DAY_MASK;
    }

    return(inputTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDay
****************************************************************************//**
*\internal
* \brief
*  Updates the date variable with the new day value.
*
* \param
* date The current date.
* \param
* day The month to be set to the date variable.
*
* \return
*  The updated date variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetDay(uint32 inputDate, uint32 inputDay)
{
    inputDate &= ~(`$INSTANCE_NAME`_DAY_FULL_MASK);

    inputDate |= (inputDay / 10u) << `$INSTANCE_NAME`_10_DAY_OFFSET;
    inputDate |= (inputDay % 10u) << `$INSTANCE_NAME`_DAY_OFFSET;

    return(inputDate);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMonth
****************************************************************************//**
*\internal
* \brief
*  Updates the date variable with the new month value.
*
* \param
* date The current date.
* \param
* month The month that to be set to the date variable.
*
* \return
*  The updated date variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetMonth(uint32 inputDate, uint32 inputMonth)
{
    inputDate &= ~(`$INSTANCE_NAME`_MONTH_FULL_MASK);

    inputDate |= (inputMonth / 10u) << `$INSTANCE_NAME`_10_MONTH_OFFSET;
    inputDate |= (inputMonth % 10u) << `$INSTANCE_NAME`_MONTH_OFFSET;

    return(inputDate);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetYear
****************************************************************************//**
*\internal
* \brief
*  Updates the date variable with the new year value.
*
* \param
* date The current date.
* \param
* year The year to be set to the date variable.
*
* \return
* The updated date variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetYear(uint32 inputDate, uint32 inputYear)
{
    inputDate  &= ~(`$INSTANCE_NAME`_YEAR_FULL_MASK);

    inputDate |= (inputYear / 1000u) << `$INSTANCE_NAME`_1000_YEAR_OFFSET;
    inputYear %= 1000u;

    inputDate |= (inputYear / 100u) << `$INSTANCE_NAME`_100_YEAR_OFFSET;
    inputYear %= 100u;

    inputDate |= (inputYear / 10u) << `$INSTANCE_NAME`_10_YEAR_OFFSET;
    inputDate |= (inputYear % 10u) << `$INSTANCE_NAME`_YEAR_OFFSET;

    return(inputDate);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextMinSec
****************************************************************************//**
*\internal
* \brief
* This is an internal function that calculates the value of the next Second/Minute
* that follows after the current Minute/Second.
*
* \param
* curVal The current Second/Minute value.
*
* \return
* Returns the Second/Minute which follows after the current Second/Minute.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetNextMinSec(uint32 curVal)
{
    return((curVal < 59u) ? (curVal + 1u) : 0u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextHour
****************************************************************************//**
*\internal
* \brief
*  This is an internal function that calculates the value of the next Hour
*  that follows after the current Hour.
*
* \param
* curVal The current Hour value.
*
* \return
*  Returns the Hour which follows after the current Hour.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetNextHour(uint32 curVal)
{
    return((curVal < 23u) ? (curVal + 1u) : 0u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextDay
****************************************************************************//**
* \internal
* \brief
*  This is an internal function that calculates the value of the next Day
*  that follows after the current Day.
*
* \param
*  curYear The current year.
* \param
*  curMonth The current month.
* \param
*  curDay The current day.
* \param
*  alarmCfgMask Alarm Config Mask.
*
* \return
*  Returns the day which follows after the current Day.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetNextDay(uint32 curYear, uint32 curMonth, uint32 curDay, uint32 alarmCfgMask)
{
    uint32 daysInMonth;
    uint32 tmpVal;

    daysInMonth = `$INSTANCE_NAME`_DaysInMonth(curMonth, curYear);

    if(0u != (alarmCfgMask & `$INSTANCE_NAME`_ALARM_DAYOFWEEK_MASK))
    {
        tmpVal = curDay + `$INSTANCE_NAME`_DAYS_PER_WEEK;
        tmpVal = (tmpVal > daysInMonth) ? (tmpVal - daysInMonth) : tmpVal;
    }
    else
    {
        tmpVal = (curDay < daysInMonth) ? (curDay + 1u) : 1u;
    }

    return(tmpVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextMonth
****************************************************************************//**
* \internal
* \brief
*  This is an internal function that calculates the value of the next month
*  that follows after the current month.
*
* \param
*  curMonth The current month.
*
* \return
*  Returns the month which follows after the current month.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetNextMonth(uint32 curMonth)
{
    return((curMonth < 12u) ? (curMonth + 1u) : 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextYear
****************************************************************************//**
* \internal
* \brief
*  This is an internal function that calculates the value of the next year
*  that follows after the current year.
*
* \param
*  curYear The current year.
*
* \return
*  Returns the year which follows after the current year.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetNextYear(uint32 curYear)
{
    return(curYear + 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTimeFormat
****************************************************************************//**
* \internal
* \brief
*  Updates the "Time Format" value in the variable that contains time in the
*  "HH:MM:SS" format.
*
* \param
*  inputTime The current value of the time in the "HH:MM:SS" format.
*
* \return
*  Returns the updated value of the time in the "HH:MM:SS" format.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_SetTimeFormat(uint32 inputTime, uint32 timeFormat)
{
    inputTime &= ~(`$INSTANCE_NAME`_TIME_FORMAT_MASK);

    if((uint32)`$INSTANCE_NAME`_12_HOURS_FORMAT != timeFormat)
    {
        inputTime |= `$INSTANCE_NAME`_TIME_FORMAT_MASK;
    }

    return(inputTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTimeFormat
****************************************************************************//**
* \internal
* \brief
*  Reads the time format from the variable that contains time in the
*  "HH:MM:SS" format.
*
* \param
*  inputTime The current value of the time in the "HH:MM:SS" format.
*
* \return
*  Returns the time format that is stored in the variable that contains time
*  in the "HH:MM:SS" format.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetTimeFormat(uint32 inputTime)
{
    return ((0uL != (inputTime & (1uL << `$INSTANCE_NAME`_TIME_FORMAT_OFFSET))) ? (uint32)`$INSTANCE_NAME`_12_HOURS_FORMAT :
                                                                                  (uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConstructTime
****************************************************************************//**
*
* \brief
*  Returns the time in the format used in APIs from individual elements
*  passed (hour, min, sec etc)
*
* \param
* timeFormat The 12/24 hours time format <br>
* `$INSTANCE_NAME`_24_HOURS_FORMAT - The 24 hours format. <br>
* `$INSTANCE_NAME`_12_HOURS_FORMAT - The 12 hours format.
*
* \param
* stateAmPm  The AM/PM status <br>
* `$INSTANCE_NAME`_AM - AM. <br>
* `$INSTANCE_NAME`_PM - PM.
*
* \param
*  hour The hour.
*
* \param
*  min The minute.
*
* \param
*  sec The second.
*
* \return
*  Time in the format used in API.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_ConstructTime(uint32 timeFormat, uint32 stateAmPm, uint32 hour, uint32 min, uint32 sec)
{
    uint32 retVal;

    retVal  = timeFormat << `$INSTANCE_NAME`_TIME_FORMAT_OFFSET;
    retVal |= stateAmPm << `$INSTANCE_NAME`_PERIOD_OF_DAY_OFFSET;

    retVal |= (hour / 10u) << `$INSTANCE_NAME`_10_HOURS_OFFSET;
    retVal |= (hour % 10u) << `$INSTANCE_NAME`_HOURS_OFFSET;

    retVal |= (min / 10u) << `$INSTANCE_NAME`_10_MINUTES_OFFSET;
    retVal |= (min % 10u) << `$INSTANCE_NAME`_MINUTES_OFFSET;

    retVal |= (sec / 10u) << `$INSTANCE_NAME`_10_SECONDS_OFFSET;
    retVal |= (sec % 10u) << `$INSTANCE_NAME`_SECONDS_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConstructDate
****************************************************************************//**
*
* \brief
*  Returns the date in the format used in APIs from individual elements
*  passed (day. Month and year)
*
* \param
*  month The month.
*
* \param
*  day The day.
*
* \param
*  year The year.
*
* \return
*  The date in the format used in API.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_ConstructDate(uint32 month, uint32 day, uint32 year)
{
    uint32 retVal;
    uint32 tmpVal = year;

    retVal  = (month / 10u) << `$INSTANCE_NAME`_10_MONTH_OFFSET;
    retVal |= (month % 10u) << `$INSTANCE_NAME`_MONTH_OFFSET;

    retVal |= (day / 10u) << `$INSTANCE_NAME`_10_DAY_OFFSET;
    retVal |= (day % 10u) << `$INSTANCE_NAME`_DAY_OFFSET;

    retVal |= (year / 1000u) << `$INSTANCE_NAME`_1000_YEAR_OFFSET;
    tmpVal %= 1000u;

    retVal |= (tmpVal / 100u) << `$INSTANCE_NAME`_100_YEAR_OFFSET;
    tmpVal %= 100u;

    retVal |= (tmpVal / 10u) << `$INSTANCE_NAME`_10_YEAR_OFFSET;
    retVal |= (tmpVal % 10u) << `$INSTANCE_NAME`_YEAR_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDayOfWeek
****************************************************************************//**
* \internal
*
* \brief
*  Returns a day of the week for a year, month, and day of month that are passed
*  through parameters. Zeller's congruence is used to calculate the day of
*  the week.
*
*  For the Georgian calendar, Zeller's congruence is:
*  h = (q + [13 * (m + 1)] + K + [K/4] + [J/4] - 2J) mod 7
*
*  h - The day of the week (0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday).
*  q - The day of the month.
*  m - The month (3 = March, 4 = April, 5 = May, ..., 14 = February)
*  K - The year of the century (year \mod 100).
*  J - The zero-based century (actually [year/100]) For example, the zero-based
*  centuries for 1995 and 2000 are 19 and 20 respectively (not to be
*  confused with the common ordinal century enumeration which indicates
*  20th for both cases).
*
* \note In this algorithm January and February are counted as months 13 and 14
* of the previous year.
*
* \param
*  day The day of the month(1..31)
*
* \param
*  month The month of the year
* `$INSTANCE_NAME`_JANUARY <br>
* `$INSTANCE_NAME`_FEBRUARY <br>
* `$INSTANCE_NAME`_MARCH <br>
* `$INSTANCE_NAME`_APRIL <br>
* `$INSTANCE_NAME`_MAY <br>
* `$INSTANCE_NAME`_JUNE <br>
* `$INSTANCE_NAME`_JULY <br>
* `$INSTANCE_NAME`_AUGUST <br>
* `$INSTANCE_NAME`_SEPTEMBER <br>
* `$INSTANCE_NAME`_OCTOBER <br>
* `$INSTANCE_NAME`_NOVEMBER <br>
* `$INSTANCE_NAME`_DECEMBER <br>
*
* \param
*  year The year value.
*
* \return
* Returns a day of the week
* `$INSTANCE_NAME`_SUNDAY <br>
* `$INSTANCE_NAME`_MONDAY <br>
* `$INSTANCE_NAME`_TUESDAY <br>
* `$INSTANCE_NAME`_WEDNESDAY <br>
* `$INSTANCE_NAME`_THURSDAY <br>
* `$INSTANCE_NAME`_FRIDAY <br>
* `$INSTANCE_NAME`_SATURDAY <br>
*
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetDayOfWeek(uint32 day, uint32 month, uint32 year)
{
    uint32 retVal;

    /* Converts month number from regular convention
     * (1=January,..., 12=December) to convention required for this
     * algorithm(January and February are counted as months 13 and 14 of
     * previous year).
    */
    if(month < (uint32)`$INSTANCE_NAME`_MARCH)
    {
        month = 12u + month;
        year--;
    }

    /* Calculates Day of Week using Zeller's congruence algorithms.
    */
    retVal = (day + (((month + 1u) * 26u) / 10u) + year + (year / 4u) + (6u * (year / 100u)) + (year / 400u)) % 7u;

    /* Makes correction for Saturday. Saturday number should be 7 instead of 0. */
    if(0u == retVal)
    {
        retVal = (uint32)`$INSTANCE_NAME`_SATURDAY;
    }

    return(retVal);
}


#if defined(CYDEV_RTC_SOURCE_WDT)
    #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE))

        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_CySysRtcSetCallback
        ****************************************************************************//**
        * \internal
        * \brief
        *  This is an internal function that registers a callback for the
        *  `$INSTANCE_NAME`_Update() function by address "0".
        *
        * \param
        *  wdtNumber The number of the WDT or WCO timer to be used to pull the
        *  `$INSTANCE_NAME`_Update() function.
        *
        *  The callback registered before by address "0" is replaced
        *  by the `$INSTANCE_NAME`_Update() function.
        * \endinternal
        *******************************************************************************/
        static CY_INLINE void `$INSTANCE_NAME`_CySysRtcSetCallback(uint32 wdtNumber)
        {
            #if((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT))
                (void)CySysTimerSetInterruptCallback(wdtNumber, `$INSTANCE_NAME`_Update);
            #else
                (void)CySysWdtSetIsrCallback(wdtNumber, `$INSTANCE_NAME`_Update);
            #endif /* ((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT)) */
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_CySysRtcResetCallback
        ****************************************************************************//**
        * \internal
        * \brief
        *  This is an internal function that clears a callback by address "0".
        *
        * \param
        *  wdtNumber The number of the WDT or WCO timer to be cleared callback for.
        *
        *  The callback registered before by address "0" is replaced
        *  by the NULL pointer.
        * \endinternal
        *******************************************************************************/
        static CY_INLINE void `$INSTANCE_NAME`_CySysRtcResetCallback(uint32 wdtNumber)
        {
            #if((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT))
                (void)CySysTimerSetInterruptCallback(wdtNumber, (void *)0);
            #else
                (void)CySysWdtSetIsrCallback(wdtNumber, (void *)0);
            #endif /* ((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT)) */
        }

    #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE)) */
#endif /* (CYDEV_RTC_SOURCE_WDT) */

/*******************************************************************************
*    External Variables
*******************************************************************************/

/**
* \addtogroup group_globals
* @{
*/

/**
* Indicates whether the RTC has been initialized; The variable is initialized to
* 0 and set to 1 the first time RTC_Start() is called. This allows the component
* to restart without reinitialization after the first call to the RTC_Start() 
* routine.
*/
extern uint8  `$INSTANCE_NAME`_initVar;

/** The DST start/stop status */
extern uint8  `$INSTANCE_NAME`_dstStatus;

/**
* The uint64 variable represents the standard Unix time (number of seconds 
* elapsed from January 1, 1970 00:00 hours UTC) in 64-bit 
*/
extern volatile uint64 `$INSTANCE_NAME`_unixTime;

/** The values for the time and date of the DST start */
extern `$INSTANCE_NAME`_DST_TIME `$INSTANCE_NAME`_dstStartTime;

/** The values for the time and date of the DST stop */
extern `$INSTANCE_NAME`_DST_TIME `$INSTANCE_NAME`_dstStopTime;

/**
* The last updated time and date values are stored in this structure (update 
* happens in Get time/date APIs)
*/
extern `$INSTANCE_NAME`_DATE_TIME `$INSTANCE_NAME`_currentTimeDate;

/** The alarm time and date values are stored in this variable */
extern `$INSTANCE_NAME`_DATE_TIME `$INSTANCE_NAME`_alarmCfgTimeDate;

/**
* This variable is used to mask alarm events; mask seconds alarm, mask minutes 
* alarm, and so on. It will have bit masks for each time item masking that item 
* for alarm generation
*/
extern uint32  `$INSTANCE_NAME`_alarmCfgMask;

/**
* This variable is used to indicate current active alarm status per time item 
* used in the alarm; whether seconds alarm is active, minute's alarm is active, 
* and so on. It will have bit masks for each time item (seconds, minutes, hours,
* day, and so on) showing the status
*/
extern uint32 `$INSTANCE_NAME`_alarmCurStatus;

/** @} globals */

extern void (*`$INSTANCE_NAME`_alarmCallbackPtr)(void);

extern const uint16 `$INSTANCE_NAME`_daysBeforeMonthTbl[`$INSTANCE_NAME`_MONTHS_PER_YEAR];
extern const uint8  `$INSTANCE_NAME`_daysInMonthTbl[`$INSTANCE_NAME`_MONTHS_PER_YEAR];


#endif /* CY_RTC_P4_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
