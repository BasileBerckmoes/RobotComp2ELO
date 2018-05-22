/***************************************************************************//**
* \file Name: `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides the source code to the API for the RTC_P4 Component.
*
********************************************************************************
* \copyright
* Copyright 2015-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8  `$INSTANCE_NAME`_initVar;

volatile uint64 `$INSTANCE_NAME`_unixTime;
`$INSTANCE_NAME`_DATE_TIME `$INSTANCE_NAME`_currentTimeDate;

static uint32 `$INSTANCE_NAME`_updateTimePeriod;
static uint32 `$INSTANCE_NAME`_tickRefOneSec;

uint8  `$INSTANCE_NAME`_dstStatus;
static uint32 `$INSTANCE_NAME`_dstTimeOffset;
#if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
    static volatile uint64 `$INSTANCE_NAME`_unixTimeDstStart;
    static volatile uint64 `$INSTANCE_NAME`_unixTimeDstStop;
    `$INSTANCE_NAME`_DST_TIME `$INSTANCE_NAME`_dstStartTime;
    `$INSTANCE_NAME`_DST_TIME `$INSTANCE_NAME`_dstStopTime;
#endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */

uint32 `$INSTANCE_NAME`_alarmCurStatus;
#if(0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS)
    uint32  `$INSTANCE_NAME`_alarmCfgMask = 0xFFu;
    static volatile uint64 `$INSTANCE_NAME`_unixTimeAlarm;
    `$INSTANCE_NAME`_DATE_TIME `$INSTANCE_NAME`_alarmCfgTimeDate;
    void (*`$INSTANCE_NAME`_alarmCallbackPtr)(void) = (void *)0;
#endif /* (0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS) */

const uint16 `$INSTANCE_NAME`_daysBeforeMonthTbl[`$INSTANCE_NAME`_MONTHS_PER_YEAR] = {
                                                 (0u), /* JANUARY */
                                                 (0u + 31u), /* FEBRUARY */
                                                 (0u + 31u + 28u), /* MARCH */
                                                 (0u + 31u + 28u + 31u), /* APRIL */
                                                 (0u + 31u + 28u + 31u + 30u), /* MAY */
                                                 (0u + 31u + 28u + 31u + 30u + 31u), /* JUNE */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u), /* JULY */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u), /* AUGUST */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u), /* SEPTEMBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u), /* OCTOBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u + 31u), /* NOVEMBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u + 31u + 30u)}; /* DECEMBER */

const uint8 `$INSTANCE_NAME`_daysInMonthTbl[`$INSTANCE_NAME`_MONTHS_PER_YEAR] = {`$INSTANCE_NAME`_DAYS_IN_JANUARY,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_FEBRUARY,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_MARCH,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_APRIL,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_MAY,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_JUNE,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_JULY,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_AUGUST,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_SEPTEMBER,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_OCTOBER,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_NOVEMBER,
                                                                                 `$INSTANCE_NAME`_DAYS_IN_DECEMBER};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Performs all the required calculations for the time and date registers and
* initializes the component along with the date and time selected in the
* customizer. 
*
* If "Implement RTC update manually" is disabled in the customizer
* and if WDT or DeepSleep timer is selected as a source in the clocks 
* configuration window (low frequency clocks tab), attaches RTC_Update API to a
* corresponding ISR callback of WDT or DeepSleep Timer.
*
* \note "Implement RTC update manually" checkbox is available for PSoC 4200L / 
* PSoC 4100M / PSoC 4200M / PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4000S / PSoC 
* 4100S and Analog Coprocessor.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
    }

    #if defined(CYDEV_RTC_SOURCE_WDT)
        #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE))
            `$INSTANCE_NAME`_CySysRtcSetCallback(CYDEV_RTC_SOURCE_WDT);
        #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE)) */
    #endif /* (CYDEV_RTC_SOURCE_WDT) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Stops the time and date updates.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    #if defined(CYDEV_RTC_SOURCE_WDT)
        #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE))
            `$INSTANCE_NAME`_CySysRtcResetCallback(CYDEV_RTC_SOURCE_WDT);
        #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == `$INSTANCE_NAME`_INITIAL_UPDATE_MODE)) */
    #endif /* (CYDEV_RTC_SOURCE_WDT) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Initializes or restores the component according to the customizer Configure
* dialogue settings.
*
* It is not necessary to call RTC_Init() because RTC_Start() API calls this 
* function and is the preferred method to begin component operation.
*
* All registers are set to values according to the customizer Configure
* dialogue. The default date value, if not set by the user before this function
* call, is 12:00:00 AM January 1, 2000.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32 tmpDate;
    uint32 tmpTime;

    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
        `$INSTANCE_NAME`_DST_TIME dstTimeTmp;
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */

    `$INSTANCE_NAME`_initVar = 1u;
    `$INSTANCE_NAME`_dstTimeOffset = 0uL;
    `$INSTANCE_NAME`_currentTimeDate.status = 0uL;

    `$INSTANCE_NAME`_dstStatus      = `$INSTANCE_NAME`_INITIAL_DST_STATUS;
    `$INSTANCE_NAME`_alarmCurStatus = `$INSTANCE_NAME`_INITIAL_ALARM_STATUS;

    tmpDate = `$INSTANCE_NAME`_ConstructDate(`$INSTANCE_NAME`_INITIAL_MONTH,
                                             `$INSTANCE_NAME`_INITIAL_DAY,
                                             `$INSTANCE_NAME`_INITIAL_YEAR);

    tmpTime = `$INSTANCE_NAME`_ConstructTime(`$INSTANCE_NAME`_INITIAL_TIME_FORMAT,
                                             0u,
                                            `$INSTANCE_NAME`_INITIAL_HOUR,
                                            `$INSTANCE_NAME`_INITIAL_MINUTE,
                                            `$INSTANCE_NAME`_INITIAL_SECOND);

    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
        `$INSTANCE_NAME`_dstStatus = 0u;
        `$INSTANCE_NAME`_currentTimeDate.status = (1uL << `$INSTANCE_NAME`_STATUS_DST_OFFSET);

        dstTimeTmp.timeFormat    = `$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE;
        dstTimeTmp.hour          = `$INSTANCE_NAME`_INITIAL_DST_START_HRS;
        dstTimeTmp.dayOfWeek     = `$INSTANCE_NAME`_INITIAL_DST_START_DOW;
        dstTimeTmp.weekOfMonth   = `$INSTANCE_NAME`_INITIAL_DST_START_WOM;
        dstTimeTmp.dayOfMonth    = `$INSTANCE_NAME`_INITIAL_DST_START_DOM;
        dstTimeTmp.month         = `$INSTANCE_NAME`_INITIAL_DST_START_MONTH;
        `$INSTANCE_NAME`_SetDSTStartTime(&dstTimeTmp, 
                                        (`$INSTANCE_NAME`_DST_DATETYPE_ENUM)`$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE);

        dstTimeTmp.timeFormat    = `$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE;
        dstTimeTmp.hour          = `$INSTANCE_NAME`_INITIAL_DST_STOP_HRS;
        dstTimeTmp.dayOfWeek     = `$INSTANCE_NAME`_INITIAL_DST_STOP_DOW;
        dstTimeTmp.weekOfMonth   = `$INSTANCE_NAME`_INITIAL_DST_STOP_WOM;
        dstTimeTmp.dayOfMonth    = `$INSTANCE_NAME`_INITIAL_DST_STOP_DOM;
        dstTimeTmp.month         = `$INSTANCE_NAME`_INITIAL_DST_STOP_MONTH;
        `$INSTANCE_NAME`_SetDSTStopTime(&dstTimeTmp, 
                                       (`$INSTANCE_NAME`_DST_DATETYPE_ENUM)`$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE);

        `$INSTANCE_NAME`_unixTimeDstStart = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStartTime);
        `$INSTANCE_NAME`_unixTimeDstStop  = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStopTime);

        if((`$INSTANCE_NAME`_unixTime >= `$INSTANCE_NAME`_unixTimeDstStart) &&
           (`$INSTANCE_NAME`_unixTime <= `$INSTANCE_NAME`_unixTimeDstStop))
        {
            `$INSTANCE_NAME`_dstStatus = 1u;
            `$INSTANCE_NAME`_dstTimeOffset = `$INSTANCE_NAME`_SECONDS_PER_HOUR;
        }
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */

    `$INSTANCE_NAME`_SetDateAndTime(tmpTime, tmpDate);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDateAndTime
****************************************************************************//**
*
* Sets the time and date values as the current time and date.
*
* \param inputTime
* The time value in the HH:MM:SS format. <br>
* "HH"- The 2nd 8-bit MSB that denotes the hour value.
* (0-23 for the 24-hour format and 1-12 for the 12-hour format. The MSB bit of 
* the value denotes AM/PM for the 12-hour format (0-AM and 1-PM). <br>
* "MM" - The 3nd 8-bit MSB denotes the minutes value, the valid 
* entries -> 0-59.<br>
* "SS" - The 8-bit LSB denotes the seconds value, the valid entries -> 0-59.
* Each byte is in the BCD format. Invalid time entries retain the
* previously set values.
*
* \param inputDate
* The date value in the format selected in the customizer.
* For the MM/DD/YYYY format: <br>
* "MM" - The 8-bit MSB denotes the month value in BCD, the valid 
* entries -> 1-12<br>
* "DD" - The 2nd 8-bit MSB denotes a day of the month value in BCD, the valid
* entries -> 1-31.<br>
* "YYYY" - The 16-bit LSB denotes a year in BCD, the valid entries -> 1900-2200.
* Each byte is in the BCD format. Invalid date entries retain the
* previously set values.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetDateAndTime(uint32 inputTime, uint32 inputDate)
{
    uint32 tmpDay;
    uint32 tmpMonth;
    uint32 tmpYear;

    tmpDay   = `$INSTANCE_NAME`_GetDay(inputDate);
    tmpMonth = `$INSTANCE_NAME`_GetMonth(inputDate);
    tmpYear  = `$INSTANCE_NAME`_GetYear(inputDate);

    `$INSTANCE_NAME`_unixTime = `$INSTANCE_NAME`_DateTimeToUnix(inputDate, inputTime);
    `$INSTANCE_NAME`_currentTimeDate.date = inputDate;
    `$INSTANCE_NAME`_currentTimeDate.time = inputTime;
    `$INSTANCE_NAME`_currentTimeDate.dayOfWeek = `$INSTANCE_NAME`_GetDayOfWeek(tmpDay, tmpMonth, tmpYear);

    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
        `$INSTANCE_NAME`_unixTimeDstStart = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStartTime);
        `$INSTANCE_NAME`_unixTimeDstStop  = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStopTime);

        if((`$INSTANCE_NAME`_unixTime >= `$INSTANCE_NAME`_unixTimeDstStart) &&
           (`$INSTANCE_NAME`_unixTime <= `$INSTANCE_NAME`_unixTimeDstStop))
        {
            `$INSTANCE_NAME`_dstStatus = 1u;
            `$INSTANCE_NAME`_dstTimeOffset = `$INSTANCE_NAME`_SECONDS_PER_HOUR;
            `$INSTANCE_NAME`_unixTime -= `$INSTANCE_NAME`_dstTimeOffset;
        }
        else
        {
            `$INSTANCE_NAME`_dstStatus = 0u;
            `$INSTANCE_NAME`_dstTimeOffset = 0uL;
        }
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */

    #if(0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS)
        `$INSTANCE_NAME`_unixTimeAlarm = `$INSTANCE_NAME`_ConstructUnixAlarmTime(&`$INSTANCE_NAME`_alarmCfgTimeDate,
                                                                                 (uint8)`$INSTANCE_NAME`_alarmCfgMask);
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUnixTime
****************************************************************************//**
*
* Sets the time in the Unix/Epoch time format - the number of seconds elapsed
* from January 1, 1970 UTC 00:00 hrs.
*
* \param time
* The time value in the Unix time/Epoch time format.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetUnixTime(uint64 unixTime)
{
    `$INSTANCE_NAME`_DATE_TIME tmpDateTime;

    `$INSTANCE_NAME`_unixTime = unixTime;
    `$INSTANCE_NAME`_UnixToDateTime(&tmpDateTime, unixTime, (uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT);

    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
        `$INSTANCE_NAME`_unixTimeDstStart = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStartTime);
        `$INSTANCE_NAME`_unixTimeDstStop  = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStopTime);

        if((`$INSTANCE_NAME`_unixTime >= `$INSTANCE_NAME`_unixTimeDstStart) &&
           (`$INSTANCE_NAME`_unixTime <= `$INSTANCE_NAME`_unixTimeDstStop))
        {
            `$INSTANCE_NAME`_dstStatus = 1u;
            `$INSTANCE_NAME`_dstTimeOffset = `$INSTANCE_NAME`_SECONDS_PER_HOUR;
        }
        else
        {
            `$INSTANCE_NAME`_dstStatus = 0u;
            `$INSTANCE_NAME`_dstTimeOffset = 0uL;
        }
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUnixTime
****************************************************************************//**
*
* Returns the time in the Unix/Epoch time format - the number of seconds 
* elapsed from January 1, 1970 UTC 00:00 hrs.
*
* \return
* Time The time value in the Unix time/Epoch time format.
*
*******************************************************************************/
uint64 `$INSTANCE_NAME`_GetUnixTime(void)
{
    return (`$INSTANCE_NAME`_unixTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPeriod
****************************************************************************//**
*
* Sets the RTC time update API period.
*
* The user needs to pass the period as
* a number of ticks and also a reference number of ticks taken by the same 
* clock source for one second. For instance, for a 32 kHz clock source and RTC
* period of 100 ms, the "ticks" value is 3200 and the "refOneSecTicks" value
* is 32000. This value is used to increment the time every time
* `$INSTANCE_NAME`_Update() API is called.
*
* \param ticks
* The clock period taken as a number of ticks.
*
* \param refOneSecTicks
* The reference number of ticks taken by the same clock source
* for one second (the input clock frequency in Hz).
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPeriod(uint32 ticks, uint32 refOneSecTicks)
{
    `$INSTANCE_NAME`_updateTimePeriod = ticks;
    `$INSTANCE_NAME`_tickRefOneSec    = refOneSecTicks;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPeriod
****************************************************************************//**
*
* Gets the RTC time update API period.
*
* \return
* Period The clock period taken as a number of ticks.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetPeriod(void)
{
    return(`$INSTANCE_NAME`_updateTimePeriod);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRefOneSec
****************************************************************************//**
*
* Gets the RTC time update API period.
*
* \return
* Period The reference number of ticks taken by the RTC clock source for one
* second.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetRefOneSec(void)
{
    return(`$INSTANCE_NAME`_tickRefOneSec);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDateAndTime
****************************************************************************//**
*
* Reads the current time and date.
*
* \param dateTime
* The pointer to the RTC_date_time structure to which time and date is returned.
*
*******************************************************************************/
void `$INSTANCE_NAME`_GetDateAndTime(`$INSTANCE_NAME`_DATE_TIME* dateTime)
{
    `$INSTANCE_NAME`_UnixToDateTime(dateTime, (`$INSTANCE_NAME`_unixTime  + `$INSTANCE_NAME`_dstTimeOffset),
                                                                            `$INSTANCE_NAME`_INITIAL_TIME_FORMAT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTime
****************************************************************************//**
*
* Reads the current time.
*
* \return
* date The value of date in the user selected format. The date value is 
* available in the BCD format.
*
* \warning
* Using `$INSTANCE_NAME`_GetTime and RTC_GetDate API separately might result
* in errors when the time wraps around the end of the day. To avoid this,
* use `$INSTANCE_NAME`_GetDateAndTime API.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetTime(void)
{
    `$INSTANCE_NAME`_UnixToDateTime(&`$INSTANCE_NAME`_currentTimeDate,
                                    (`$INSTANCE_NAME`_unixTime  + `$INSTANCE_NAME`_dstTimeOffset),
                                     `$INSTANCE_NAME`_INITIAL_TIME_FORMAT);

    return(`$INSTANCE_NAME`_currentTimeDate.time);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDate
****************************************************************************//**
*
* Reads the current time.
*
* \return
* time The time value in the format selected by the user (12/24 hr);
* The time value is available in the BCD format.
*
* \note
* Using `$INSTANCE_NAME`_GetTime and `$INSTANCE_NAME`_GetDate API separately
* might result in errors when the time wraps around the end of the day. To
* avoid this, use `$INSTANCE_NAME`_GetDateAndTime API.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetDate(void)
{
    `$INSTANCE_NAME`_UnixToDateTime(&`$INSTANCE_NAME`_currentTimeDate,
                                    (`$INSTANCE_NAME`_unixTime  + `$INSTANCE_NAME`_dstTimeOffset),
                                     `$INSTANCE_NAME`_INITIAL_TIME_FORMAT);

    return(`$INSTANCE_NAME`_currentTimeDate.date);
}


#if(0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetAlarmDateAndTime
    ****************************************************************************//**
    *
    * Writes the time and date values as the current alarm time and date.
    *
    * \param alarmTime
    * The pointer to the `$INSTANCE_NAME`_date_time global structure 
    * where new values of the alarm time and date are stored, 
    * see \ref `$INSTANCE_NAME`_DATE_TIME.
    *
    * \note
    * Invalid time entries are written with "00:00:00:00" for the 24-hour format 
    * and "AM 12:00:00:00" for the 12-hour format. Invalid date entries are 
    * written with a date equivalent to 01-JAN-2000.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetAlarmDateAndTime(const `$INSTANCE_NAME`_DATE_TIME* alarmTime)
    {
        `$INSTANCE_NAME`_alarmCfgTimeDate = *alarmTime;
        `$INSTANCE_NAME`_unixTimeAlarm = 
        `$INSTANCE_NAME`_ConstructUnixAlarmTime(alarmTime, (uint8)`$INSTANCE_NAME`_alarmCfgMask);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetAlarmDateAndTime
    ****************************************************************************//**
    *
    * Reads the current alarm time and date.
    *
    * \param alarmTimeDate
    * The pointer to the `$INSTANCE_NAME`_date_time structure to which the alarm 
    * date and time are returned, see \ref `$INSTANCE_NAME`_DATE_TIME.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_GetAlarmDateAndTime(`$INSTANCE_NAME`_DATE_TIME* alarmTimeDate)
    {
        *alarmTimeDate = `$INSTANCE_NAME`_alarmCfgTimeDate;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetAlarmMask
    ****************************************************************************//**
    *
    * Writes the Alarm Mask software register with one bit per time/date entry.
    * The alarm is true when all masked time/date values match the Alarm values.
    * Generated only if the alarm functionality is enabled.
    *
    * \param mask
    * The Alarm Mask software register value. The values shown below can be
    * OR'ed and passed as an argument as well, see \ref group_rtc_alarm_mask.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetAlarmMask(uint32 mask)
    {
        `$INSTANCE_NAME`_alarmCfgMask = (uint8)mask;
        `$INSTANCE_NAME`_unixTimeAlarm = 
        `$INSTANCE_NAME`_ConstructUnixAlarmTime(&`$INSTANCE_NAME`_alarmCfgTimeDate, (uint8)mask);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetAlarmMask
    ****************************************************************************//**
    *
    * Reads the Alarm Mask software register. Generated only if the alarm 
    * functionality is enabled, see \ref group_rtc_alarm_mask.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetAlarmMask(void)
    {
        return((uint32)`$INSTANCE_NAME`_alarmCfgMask);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetAlarmStatus
    ****************************************************************************//**
    *
    *  Returns the alarm status of RTC.
    *
    * \return
    * The Alarm active status. This bit is high when the current time and date 
    * match the alarm time and date. <br>
    * 0 - The Alarm status is not active <br>
    * 1 - The Alarm status is active.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetAlarmStatus(void)
    {
        return((0uL != (`$INSTANCE_NAME`_currentTimeDate.status & (1uL << `$INSTANCE_NAME`_STATUS_ALARM_OFFSET))) ?
                1uL : 
                0uL);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ClearAlarmStatus
    ****************************************************************************//**
    *
    *  Clears the alarm status of RTC.
    *
    * \note
    * The Alarm active (AA) flag clears after read. This bit will be set in the next
    * alarm match event only. If Alarm is set on only minutes and the alarm
    * minutes is 20 minutes - the alarm triggers once every 20th minute of
    * every hour.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ClearAlarmStatus(void)
    {
        `$INSTANCE_NAME`_currentTimeDate.status &= (~(1uL << `$INSTANCE_NAME`_STATUS_ALARM_OFFSET));
        `$INSTANCE_NAME`_alarmCurStatus = 0u;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetAlarmHandler
    ****************************************************************************//**
    *
    *  This API sets the function to be called when the alarm goes off / triggers.
    *  This API is generated only if the alarm functionality is enabled in the
    *  customizer.
    *
    * \param CallbackFunction
    * The callback function address.
    *
    * \return
    * A previous callback function address.
    *
    *******************************************************************************/
    void* `$INSTANCE_NAME`_SetAlarmHandler(void (*CallbackFunction)(void))
    {
        void (*tmpCallbackPtr)(void);

        tmpCallbackPtr = `$INSTANCE_NAME`_alarmCallbackPtr;
        `$INSTANCE_NAME`_alarmCallbackPtr = CallbackFunction;

        return((void*)tmpCallbackPtr);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetNexAlarmTime
    ****************************************************************************//**
    *
    *  This is an internal function that calculates the time of the next alarm
    *  in the UNIX format taking into account the current "Alarm Config Mask".
    *
    * \param curUnixTime
    * The current time value in the UNIX format.
    *
    * \param alarmCfgMask
    * The current Alarm Config Mask.
    *
    * \return
    * Returns time of the next alarm in the UNIX format.
    *
    *******************************************************************************/
    uint64 `$INSTANCE_NAME`_GetNexAlarmTime(uint64 curUnixTime, uint8 alarmCfgMask)
    {
        uint32 prevVal;
        uint32 nextVal;
        uint32 carryFlag;
        uint32 daysInMonth;
        `$INSTANCE_NAME`_DATE_TIME curDateTime;

        carryFlag = 1u;
        `$INSTANCE_NAME`_UnixToDateTime(&curDateTime, curUnixTime, (uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT);

        /* Calculates Second value of next alarm time based on current time and Alarm Config Mask */
        if(0uL != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_SEC_MASK))
        {
            prevVal = `$INSTANCE_NAME`_GetSecond(curDateTime.time);
            nextVal = `$INSTANCE_NAME`_GetNextMinSec(prevVal);
            curDateTime.time = `$INSTANCE_NAME`_SetSecond(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Minute value of next alarm time based on current time and Alarm Config Mask */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_MIN_MASK)))
        {
            prevVal = `$INSTANCE_NAME`_GetMinutes(curDateTime.time);
            nextVal = `$INSTANCE_NAME`_GetNextMinSec(prevVal);
            curDateTime.time = `$INSTANCE_NAME`_SetMinutes(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Hour value of next alarm time based on current time and Alarm Config Mask */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_HOUR_MASK)))
        {
            prevVal = `$INSTANCE_NAME`_GetHours(curDateTime.time);
            nextVal = `$INSTANCE_NAME`_GetNextHour(prevVal);
            curDateTime.time = `$INSTANCE_NAME`_SetHours(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Day value of next alarm time based on current time and Alarm Config Mask */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_DAYOFMONTH_MASK)))
        {
            prevVal = `$INSTANCE_NAME`_GetDay(curDateTime.date);
            if(0u != (alarmCfgMask & `$INSTANCE_NAME`_ALARM_DAYOFWEEK_MASK))
            {
                daysInMonth = `$INSTANCE_NAME`_DaysInMonth(`$INSTANCE_NAME`_GetMonth(curDateTime.date),
                                                           `$INSTANCE_NAME`_GetYear(curDateTime.date));
                nextVal = prevVal + `$INSTANCE_NAME`_DAYS_PER_WEEK;
                nextVal = (nextVal > daysInMonth) ? (nextVal - daysInMonth) : nextVal;
            }
            else
            {
                nextVal = `$INSTANCE_NAME`_GetNextDay(`$INSTANCE_NAME`_GetYear(curDateTime.date),
                                                      `$INSTANCE_NAME`_GetMonth(curDateTime.date),
                                                      `$INSTANCE_NAME`_GetDay(curDateTime.date),
                                                      (~((uint32)alarmCfgMask)));
            }
            curDateTime.date = `$INSTANCE_NAME`_SetDay(curDateTime.date, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Month value of next alarm time based on current time and Alarm Config Mask */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_MONTH_MASK)))
        {
            prevVal = `$INSTANCE_NAME`_GetMonth(curDateTime.date);
            nextVal = `$INSTANCE_NAME`_GetNextMonth(prevVal);
            curDateTime.date = `$INSTANCE_NAME`_SetMonth(curDateTime.date, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Year value of next alarm time based on current time and Alarm Config Mask */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_YEAR_MASK)))
        {
            prevVal = `$INSTANCE_NAME`_GetYear(curDateTime.date);
            nextVal = `$INSTANCE_NAME`_GetNextYear(prevVal);
            curDateTime.date = `$INSTANCE_NAME`_SetYear(curDateTime.date, nextVal);
        }

        return(`$INSTANCE_NAME`_DateTimeToUnix(curDateTime.date, curDateTime.time));
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ConstructUnixAlarmTime
    ****************************************************************************//**
    *
    * This is an internal function that calculates the time of the first alarm
    * in the UNIX format taking into account the current "Alarm Config Mask".
    *
    * \param alarmTime
    * Desired alarm time in the regular time format, 
    * see \ref `$INSTANCE_NAME`_DATE_TIME
    *
    * \param alarmCfgMask
    * The current Alarm Config Mask.
    *
    * \return
    * time of the first alarm in the UNIX format.
    *
    *******************************************************************************/
    uint64 `$INSTANCE_NAME`_ConstructUnixAlarmTime(const `$INSTANCE_NAME`_DATE_TIME* alarmTime, uint8 alarmCfgMask)
    {
        uint32 tmpCurVal;
        uint32 tmpNextVal;
        uint32 carryFlag;
        uint32 tmpAlarmDate;
        uint32 tmpAlarmTime;
        uint32 daysInMonth;
        `$INSTANCE_NAME`_DATE_TIME curDateTime;

        tmpAlarmDate = 0u;
        tmpAlarmTime = 0u;
        `$INSTANCE_NAME`_UnixToDateTime(&curDateTime, `$INSTANCE_NAME`_unixTime, 
                                       (uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT);

        /* Calculates Seconds value of first Alarm based on current time and Alarm Config Mask */
        tmpCurVal =  `$INSTANCE_NAME`_GetSecond(curDateTime.time);
        tmpNextVal = `$INSTANCE_NAME`_GetSecond(alarmTime->time);
        carryFlag = (tmpCurVal > tmpNextVal) ? 1u : 0u;
        if(0u != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_SEC_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? 0u : tmpCurVal;
        }
        tmpAlarmTime = `$INSTANCE_NAME`_SetSecond(tmpAlarmTime, tmpNextVal);

        /* Calculates Minutes value of first Alarm based on current time and Alarm Config Mask */
        tmpCurVal  = `$INSTANCE_NAME`_GetMinutes(curDateTime.time);
        if(0u != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_MIN_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? `$INSTANCE_NAME`_GetNextMinSec(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = `$INSTANCE_NAME`_GetMinutes(alarmTime->time);
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmTime =  `$INSTANCE_NAME`_SetMinutes(tmpAlarmTime, tmpNextVal);

        /* Calculates Hours value of first Alarm based on current time and Alarm Config Mask */
        tmpCurVal  = `$INSTANCE_NAME`_GetHours(curDateTime.time);
        if(0u != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_HOUR_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? `$INSTANCE_NAME`_GetNextHour(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = `$INSTANCE_NAME`_GetHours(alarmTime->time);
            if((uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT != `$INSTANCE_NAME`_GetTimeFormat(alarmTime->time))
            {
                if((uint32)`$INSTANCE_NAME`_AM != `$INSTANCE_NAME`_GetAmPm(alarmTime->time))
                {
                    tmpNextVal += `$INSTANCE_NAME`_HOURS_PER_HALF_DAY;
                }
            }
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmTime =  `$INSTANCE_NAME`_SetHours(tmpAlarmTime, tmpNextVal);

        /* Calculates Day value of first Alarm based on current time and Alarm Config Mask */
        tmpCurVal  = `$INSTANCE_NAME`_GetDay(curDateTime.date);
        tmpNextVal = `$INSTANCE_NAME`_GetDay(alarmTime->date);
        if(0u != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_DAYOFMONTH_MASK))
        {
            if(0u != (alarmCfgMask & `$INSTANCE_NAME`_ALARM_DAYOFWEEK_MASK))
            {
                daysInMonth = `$INSTANCE_NAME`_DaysInMonth(`$INSTANCE_NAME`_GetMonth(curDateTime.date),
                                                           `$INSTANCE_NAME`_GetYear(curDateTime.date));
                tmpNextVal = 
                (curDateTime.dayOfWeek <= alarmTime->dayOfWeek) ? (alarmTime->dayOfWeek - curDateTime.dayOfWeek) :
                                ((`$INSTANCE_NAME`_DAYS_PER_WEEK - curDateTime.dayOfWeek) + alarmTime->dayOfWeek);
                tmpNextVal = tmpCurVal + tmpNextVal;
                tmpNextVal = (tmpNextVal > daysInMonth) ? (tmpNextVal - daysInMonth) : tmpNextVal;
            }
            else
            {
                tmpNextVal = 
                (0u == carryFlag) ? tmpCurVal : `$INSTANCE_NAME`_GetNextDay(`$INSTANCE_NAME`_GetYear(curDateTime.date),
                                                `$INSTANCE_NAME`_GetMonth(curDateTime.date),
                                                tmpCurVal,
                                                `$INSTANCE_NAME`_ALARM_DAYOFMONTH_MASK);
            }
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmDate =  `$INSTANCE_NAME`_SetDay(tmpAlarmDate, tmpNextVal);

        /* Calculates Month value of first Alarm based on current time and Alarm Config Mask */
        tmpCurVal  = `$INSTANCE_NAME`_GetMonth(curDateTime.date);
        if(0u != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_MONTH_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? `$INSTANCE_NAME`_GetNextMonth(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = `$INSTANCE_NAME`_GetMonth(alarmTime->date);
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmDate =  `$INSTANCE_NAME`_SetMonth(tmpAlarmDate, tmpNextVal);

        /* Calculates Year value of first Alarm based on current time and Alarm Config Mask */
        tmpCurVal  = `$INSTANCE_NAME`_GetYear(curDateTime.date);
        if(0u != ((~((uint32)alarmCfgMask)) & `$INSTANCE_NAME`_ALARM_MONTH_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? `$INSTANCE_NAME`_GetNextYear(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = `$INSTANCE_NAME`_GetYear(alarmTime->date);
        }
        tmpAlarmDate =  `$INSTANCE_NAME`_SetYear(tmpAlarmDate, tmpNextVal);

        return(`$INSTANCE_NAME`_DateTimeToUnix(tmpAlarmDate, tmpAlarmTime));
    }
#endif/* (0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadStatus
****************************************************************************//**
*
* Reads the Status software register, which has flags for DST (DST),
* Leap Year (LY), AM/PM (AM_PM).
*
* \return
* The values shown below are OR'ed and returned if more than one status
* bits are set, see \ref group_rtc_status.
*
* \note
* Reading the status without sync with the date and time read may cause an
* error due to a roll-over at AM/PM, the end of a year, the end of a day;
* `$INSTANCE_NAME`_GetDateAndTime() API is used to obtain the status and
* the status member of the returned structure can be checked with the masks.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadStatus(void)
{
    uint32 tmpYear;
    `$INSTANCE_NAME`_DATE_TIME tmpTimeDate;

    `$INSTANCE_NAME`_GetDateAndTime(&tmpTimeDate);
    tmpYear = `$INSTANCE_NAME`_GetYear(tmpTimeDate.date);

    if(0uL != `$INSTANCE_NAME`_LeapYear(tmpYear))
    {
        `$INSTANCE_NAME`_currentTimeDate.status |= (1uL << `$INSTANCE_NAME`_STATUS_LY_OFFSET);
    }
    else
    {
        `$INSTANCE_NAME`_currentTimeDate.status &= ~(1uL << `$INSTANCE_NAME`_STATUS_LY_OFFSET);
    }


    if(0uL != `$INSTANCE_NAME`_GetAmPm(tmpTimeDate.time))
    {
        `$INSTANCE_NAME`_currentTimeDate.status |= (1uL << `$INSTANCE_NAME`_STATUS_AM_PM_OFFSET);
    }
    else
    {
        `$INSTANCE_NAME`_currentTimeDate.status &= ~(1uL << `$INSTANCE_NAME`_STATUS_AM_PM_OFFSET);
    }

    return(`$INSTANCE_NAME`_currentTimeDate.status);
}


#if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetDSTStartTime
    ****************************************************************************//**
    *
    * Stores the DST Start time.
    *
    * Only generated if DST is enabled. The date passed can be relative or fixed. 
    * For a relative date, the user needs to provide a valid day of a week, a 
    * week of a month and a month in the dstStartTime structure.
    * For a fixed date, the user needs to enter a valid day of a month and a month 
    * in the dstStartTime structure. The hour value is optional and if invalid
    * taken as 00 hrs. Invalid entries are not stored and the DST start date
    * retains a previous value or no value at all.
    *
    * \param dstStartTime
    * The DST Start time register value, see \ref `$INSTANCE_NAME`_DST_TIME
    *
    * \param type
    * Defines the DST operation mode, see \ref `$INSTANCE_NAME`_DST_DATETYPE_ENUM.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetDSTStartTime(const `$INSTANCE_NAME`_DST_TIME* dstStartTime,
                                                `$INSTANCE_NAME`_DST_DATETYPE_ENUM type)
    {
        `$INSTANCE_NAME`_dstStartTime.timeFormat    = (uint8)type;
        `$INSTANCE_NAME`_dstStartTime.hour          = dstStartTime->hour;
        `$INSTANCE_NAME`_dstStartTime.dayOfWeek     = dstStartTime->dayOfWeek;
        `$INSTANCE_NAME`_dstStartTime.weekOfMonth   = dstStartTime->weekOfMonth;
        `$INSTANCE_NAME`_dstStartTime.dayOfMonth    = dstStartTime->dayOfMonth;
        `$INSTANCE_NAME`_dstStartTime.month         = dstStartTime->month;

        `$INSTANCE_NAME`_unixTimeDstStart = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStartTime);

        if((`$INSTANCE_NAME`_unixTime >= `$INSTANCE_NAME`_unixTimeDstStart) &&
           (`$INSTANCE_NAME`_unixTime <= `$INSTANCE_NAME`_unixTimeDstStop))
        {
            `$INSTANCE_NAME`_dstStatus = 1u;
            `$INSTANCE_NAME`_dstTimeOffset = `$INSTANCE_NAME`_SECONDS_PER_HOUR;
        }
        else
        {
            `$INSTANCE_NAME`_dstStatus = 0u;
            `$INSTANCE_NAME`_dstTimeOffset = 0uL;
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetDSTStopTime
    ****************************************************************************//**
    *
    * Stores the DST Stop time.
    * 
    * Only generated if DST is enabled. The date passed can be relative or fixed. 
    * For a relative date, the user needs to provide a valid day of a week, a week 
    * of a month and a month in the dstStopTime structure.
    * For a fixed date, the user needs to enter a valid day of a month and a month
    * in the dstSoptTime structure. The hour value is optional and if invalid 
    * taken as 00 hrs. Invalid entries are not stored and the DST start date 
    * retains a previous value or no value at all.
    *
    * \param dstStopTime
    * DST Stop time register values, see \ref `$INSTANCE_NAME`_DST_TIME
    *
    * \param type
    * Defines the DST operation mode, see \ref `$INSTANCE_NAME`_DST_DATETYPE_ENUM.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetDSTStopTime(const `$INSTANCE_NAME`_DST_TIME* dstStopTime,
                                               `$INSTANCE_NAME`_DST_DATETYPE_ENUM type)
    {

        `$INSTANCE_NAME`_dstStopTime.timeFormat  = (uint8)type;
        `$INSTANCE_NAME`_dstStopTime.hour           = dstStopTime->hour;
        `$INSTANCE_NAME`_dstStopTime.dayOfWeek      = dstStopTime->dayOfWeek;
        `$INSTANCE_NAME`_dstStopTime.weekOfMonth = dstStopTime->weekOfMonth;
        `$INSTANCE_NAME`_dstStopTime.dayOfMonth     = dstStopTime->dayOfMonth;
        `$INSTANCE_NAME`_dstStopTime.month         = dstStopTime->month;

        `$INSTANCE_NAME`_unixTimeDstStop  = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStopTime);

        if((`$INSTANCE_NAME`_unixTime >= `$INSTANCE_NAME`_unixTimeDstStart) &&
           (`$INSTANCE_NAME`_unixTime <= `$INSTANCE_NAME`_unixTimeDstStop))
        {
            `$INSTANCE_NAME`_dstStatus = 1u;
            `$INSTANCE_NAME`_dstTimeOffset = `$INSTANCE_NAME`_SECONDS_PER_HOUR;
        }
        else
        {
            `$INSTANCE_NAME`_dstStatus = 0u;
            `$INSTANCE_NAME`_dstTimeOffset = 0uL;
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetDstUnixTime
    ****************************************************************************//**
    *
    * Calculates the DST Start/Stop time in the UNIX format.
    *
    * \param dstTime
    * The DST Start/Stop time in the regular time format,
    * see \ref `$INSTANCE_NAME`_DST_TIME
    *
    * \return
    * The DST Start/Stop time in the UNIX format.
    *
    *******************************************************************************/
    uint64 `$INSTANCE_NAME`_GetDstUnixTime(const `$INSTANCE_NAME`_DST_TIME* dstTime)
    {
        uint32 tmpYear;
        uint32 tmpDate;
        uint64 dstUnixTime;

        `$INSTANCE_NAME`_DATE_TIME tmpTimeDate;

        `$INSTANCE_NAME`_UnixToDateTime(&tmpTimeDate, `$INSTANCE_NAME`_unixTime, `$INSTANCE_NAME`_INITIAL_TIME_FORMAT);
        tmpYear = `$INSTANCE_NAME`_GetYear(tmpTimeDate.date);

        if(dstTime->timeFormat == (uint8)`$INSTANCE_NAME`_DST_DATE_FIXED)
        {
            tmpDate =  `$INSTANCE_NAME`_ConstructDate(dstTime->month, dstTime->dayOfMonth, tmpYear);
        }
        else
        {
            tmpDate = 
            `$INSTANCE_NAME`_RelativeToFixed(dstTime->dayOfWeek, dstTime->weekOfMonth, dstTime->month, tmpYear);
        }

        tmpTimeDate.time = 
        `$INSTANCE_NAME`_ConstructTime((uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT, 0u, dstTime->hour, 0u, 0u);
        dstUnixTime = `$INSTANCE_NAME`_DateTimeToUnix(tmpDate, tmpTimeDate.time);

        return(dstUnixTime);
    }

#endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConvertBCDToDec
****************************************************************************//**
*
* Converts a 4-byte BCD number into a 4-byte hexadecimal number. Each byte is
* converted individually and returned as an individual byte in the 32-bit
* variable.
*
* \param bcdNum
* A 4-byte BCD number. Each byte represents BCD.
* 0x11223344 -> 4 bytes 0x11, 0x22, 0x33 and 0x44 the in BCD format.
*
* \return
* decNum A 4-byte hexadecimal equivalent number of the BCD number.
* BCD number 0x11223344 -> returned hexadecimal number 0x0B16212C.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ConvertBCDToDec(uint32 bcdNum)
{
    uint32 i;
    uint32 mult;
    uint32 retVal;

    mult   = 1u;
    retVal = 0u;

    for(i = 0u; i < 16u; i++)
    {
        retVal += (bcdNum & `$INSTANCE_NAME`_BCD_ONE_DIGIT_MASK) * mult;
        bcdNum >>= `$INSTANCE_NAME`_BCD_NUMBER_SIZE;
        mult *= 10u;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConvertDecToBCD
****************************************************************************//**
*
* Converts a 4-byte hexadecimal number into a 4-byte BCD number. Each byte
* is converted individually and returned as an individual byte in the 32-bit
* variable.
*
* \param decNum
* A 4-byte hexadecimal number. Each byte is represented in hex.
* 0x11223344 -> 4 bytes 0x11, 0x22, 0x33 and 0x44 in the hex format.
*
* \return
* bcdNum - A 4-byte BCD equivalent of the passed hexadecimal number. 
* Hexadecimal number 0x11223344 -> returned BCD number 0x17345168.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ConvertDecToBCD(uint32 decNum)
{
    uint32 shift;
    uint32 tmpVal;
    uint32 retVal;

    shift  = 0u;
    retVal = 0u;
    tmpVal = decNum;

    do
    {
        retVal |= ((tmpVal % 10u) << shift);
        tmpVal /= 10u;
        shift  += `$INSTANCE_NAME`_BCD_NUMBER_SIZE;
    }
    while(tmpVal >= 10u);

    retVal |= (tmpVal << shift);

    return(retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Update
****************************************************************************//**
*
* This API updates the time registers and performs alarm/DST check.
*
* This function increments the time/date registers by an input clock period.
* The period is set by `$INSTANCE_NAME`_SetPeriod() API or WDT period selected 
* for RTC in the clocks configuration window (low frequency clocks tab) 
* interface every time it is called.
*
* API is automatically mapped to the callback slot of WDT or DeepSleep Timer 
* and period, if the configuration is as follows:
* 1) Option "Implement RTC update manually" in the customizer is unchecked
* 2) One of WDTs or DeeSleep Timers is selected in the "Use for RTC" panel of 
* the low frequency clocks tab
* 3) Option "Implementation by IDE" is selected in the "Timer (WDT) ISR" panel.
*
* If option "Implement RTC update manually" is checked in the customizer or
* option "None" is selected in the "Use for RTC" panel, it is the user's
* responsibility:
* 1) to call this API from the clock ISR to be used as the RTC's input
* 2) set the period of the RTC through `$INSTANCE_NAME`_SetPeriod() API.
*
* \note Updates the Unix time register, updates the alarm and DST status.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Update(void)
{
    static uint32 `$INSTANCE_NAME`_currentTickNumber = 0u;
    `$INSTANCE_NAME`_currentTickNumber += `$INSTANCE_NAME`_updateTimePeriod;

    if(`$INSTANCE_NAME`_currentTickNumber >= `$INSTANCE_NAME`_tickRefOneSec)
    {
        `$INSTANCE_NAME`_unixTime++;
        `$INSTANCE_NAME`_currentTickNumber = 
        (uint32) `$INSTANCE_NAME`_currentTickNumber - `$INSTANCE_NAME`_tickRefOneSec;

    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
        if(`$INSTANCE_NAME`_unixTime == `$INSTANCE_NAME`_unixTimeDstStart)
        {
            `$INSTANCE_NAME`_dstStatus = 1u;
            `$INSTANCE_NAME`_dstTimeOffset = `$INSTANCE_NAME`_SECONDS_PER_HOUR;
        }

        if(`$INSTANCE_NAME`_unixTime == (`$INSTANCE_NAME`_unixTimeDstStop - `$INSTANCE_NAME`_dstTimeOffset))
        {
            `$INSTANCE_NAME`_dstStatus = 0u;
            `$INSTANCE_NAME`_dstTimeOffset = 0u;
            `$INSTANCE_NAME`_unixTimeDstStart = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStartTime);
            `$INSTANCE_NAME`_unixTimeDstStop  = `$INSTANCE_NAME`_GetDstUnixTime(&`$INSTANCE_NAME`_dstStopTime);
        }
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */

    #if(0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS)
        if((`$INSTANCE_NAME`_unixTime + `$INSTANCE_NAME`_dstTimeOffset) == `$INSTANCE_NAME`_unixTimeAlarm)
        {
            `$INSTANCE_NAME`_currentTimeDate.status |= (1uL << `$INSTANCE_NAME`_STATUS_ALARM_OFFSET);
            `$INSTANCE_NAME`_alarmCurStatus = `$INSTANCE_NAME`_alarmCfgMask;

            `$INSTANCE_NAME`_unixTimeAlarm = 
            `$INSTANCE_NAME`_GetNexAlarmTime(`$INSTANCE_NAME`_unixTime + `$INSTANCE_NAME`_dstTimeOffset,
                                                                   (uint8)`$INSTANCE_NAME`_alarmCfgMask);

            /* Call callback function only after new alarm time is obtained.
            * Cypress ticket #264756
            */
            if (`$INSTANCE_NAME`_alarmCallbackPtr != NULL)
            {
                `$INSTANCE_NAME`_alarmCallbackPtr();
            }
        }
    #endif/* (0u != `$INSTANCE_NAME`_INITIAL_ALARM_STATUS) */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DateTimeToUnix
****************************************************************************//**
*
* This is an internal function to convert the date and time from the regular 
* time format into the UNIX time format.
*
* \param inputDate
* The date in the selected in the customizer "date format"
*
* \param inputTime
* The time in the defined "time format"
*
* \return
* Returns the date and time in the UNIX format
*
*******************************************************************************/
uint64 `$INSTANCE_NAME`_DateTimeToUnix(uint32 inputDate, uint32 inputTime)
{
    uint32 i;
    uint32 tmpYear;
    uint32 tmpMonth;
    uint32 tmpVal;
    uint64 unixTime;

    unixTime = 0u;
    tmpYear = `$INSTANCE_NAME`_GetYear(inputDate);

    /* Calculate seconds from epoch start up to (but not including) current year */
    for(i = `$INSTANCE_NAME`_YEAR_0; i < tmpYear; i++)
    {
        if(0u != `$INSTANCE_NAME`_LeapYear(i))
        {
            unixTime += `$INSTANCE_NAME`_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            unixTime += `$INSTANCE_NAME`_SECONDS_PER_NONLEAP_YEAR;
        }
    }

    /* Calculates how many seconds had elapsed in this year prior to the current month */
    tmpMonth = `$INSTANCE_NAME`_GetMonth(inputDate);
    tmpVal = `$INSTANCE_NAME`_DaysBeforeMonth(tmpMonth, tmpYear);

    /* Calculates how many seconds are in current month days prior to today */
    unixTime += (uint64) tmpVal * `$INSTANCE_NAME`_SECONDS_PER_DAY;
    unixTime += ((uint64) `$INSTANCE_NAME`_GetDay(inputDate) - 1u) * `$INSTANCE_NAME`_SECONDS_PER_DAY;

    /* Calculates how many seconds have elapsed today up to the current hour */
    tmpVal = `$INSTANCE_NAME`_GetHours(inputTime);
    if(((uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT != `$INSTANCE_NAME`_GetTimeFormat(inputTime)) &&
       ((uint32)`$INSTANCE_NAME`_AM != `$INSTANCE_NAME`_GetAmPm(inputTime)) && (tmpVal < 12u))
    {
        tmpVal += `$INSTANCE_NAME`_HOURS_PER_HALF_DAY;
    }
    unixTime += (uint64)tmpVal * `$INSTANCE_NAME`_SECONDS_PER_HOUR;

    /* Calculates how many seconds have elapsed today up to the current minute */
    unixTime += ((uint64) `$INSTANCE_NAME`_GetMinutes(inputTime)) * `$INSTANCE_NAME`_SECONDS_PER_MINUTE;

    /* Add remaining seconds of current minute */
    unixTime += `$INSTANCE_NAME`_GetSecond(inputTime);

    return(unixTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UnixToDateTime
****************************************************************************//**
*
* This is an internal function to convert the date and time from the UNIX time 
* format into the regular time format
*
* \param `$INSTANCE_NAME`_DATE_TIME* dateTime
* The time and date structure which will be updated time from unixTime value
*
* \param unixTime
* time in unix format
*
* \param timeFormat
* dst format of time, see \ref `$INSTANCE_NAME`_DST_DATETYPE_ENUM
*
*******************************************************************************/
void `$INSTANCE_NAME`_UnixToDateTime(`$INSTANCE_NAME`_DATE_TIME* dateTime, uint64 unixTime, uint32 timeFormat)
{
    uint32 tmpMinute;
    uint32 tmpHour;
    uint32 tmpAmPmState;

    uint32 tmpDay;
    uint32 tmpMonth;
    uint32 tmpYear;

    uint32 tmpVar;

    tmpAmPmState = 0u;
    tmpYear = `$INSTANCE_NAME`_YEAR_0;
    tmpVar = `$INSTANCE_NAME`_SECONDS_PER_NONLEAP_YEAR;

    /* Calculates current year value. Variable tmpYear
    *  increments while it contains value greater than number
    *  of seconds in current year.
    */
    while(unixTime >= tmpVar)
    {
        unixTime -= tmpVar;
        tmpYear++;

        if(0u != `$INSTANCE_NAME`_LeapYear(tmpYear))
        {
            tmpVar = `$INSTANCE_NAME`_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            tmpVar = `$INSTANCE_NAME`_SECONDS_PER_NONLEAP_YEAR;
        }
    }

    /* Calculates current month value. The tmpMonth variable increments while 
    *  unixTime variable value is greater than time interval from beginning 
    *  of current year to beginning of current month
    */
    tmpMonth = (uint32)`$INSTANCE_NAME`_JANUARY;
    tmpVar = `$INSTANCE_NAME`_DaysInMonth(tmpMonth, tmpYear) * `$INSTANCE_NAME`_SECONDS_PER_DAY;

    while(unixTime >= tmpVar)
    {
        unixTime -= tmpVar;
        tmpMonth++;
        tmpVar = `$INSTANCE_NAME`_DaysInMonth(tmpMonth, tmpYear) * `$INSTANCE_NAME`_SECONDS_PER_DAY;
    }

    /* Calculates current day value */
    tmpDay = (uint32) (unixTime / `$INSTANCE_NAME`_SECONDS_PER_DAY);
    tmpVar = tmpDay * `$INSTANCE_NAME`_SECONDS_PER_DAY;
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;
    tmpDay += 1u;

    /* Calculates current hour value. If function works in 12-Hour mode,
     * it converts time to 12-Hours mode and calculates AmPm status */
    tmpHour = (uint32) (unixTime / `$INSTANCE_NAME`_SECONDS_PER_HOUR);
    tmpVar  = tmpHour * `$INSTANCE_NAME`_SECONDS_PER_HOUR;
    if((uint32)`$INSTANCE_NAME`_24_HOURS_FORMAT != timeFormat)
    {
        if(unixTime > `$INSTANCE_NAME`_UNIX_TIME_PM)
        {
            tmpAmPmState = `$INSTANCE_NAME`_PM;
            tmpHour = (tmpHour > 12u) ? (tmpHour - 12u) : tmpHour;
        }
        else
        {
            tmpAmPmState = `$INSTANCE_NAME`_AM;
            tmpHour = (0u != tmpHour) ? tmpHour : 12u;
        }
    }
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;

    /* Calculates current minute */
    tmpMinute = (uint32) (unixTime / `$INSTANCE_NAME`_SECONDS_PER_MINUTE);
    tmpVar = tmpMinute * `$INSTANCE_NAME`_SECONDS_PER_MINUTE;

    /* Calculates current second */
    unixTime -= (unixTime >= (uint64) tmpVar) ? (uint64) tmpVar : 0ul;

    dateTime->date = `$INSTANCE_NAME`_ConstructDate(tmpMonth, tmpDay, tmpYear);
    dateTime->time = `$INSTANCE_NAME`_ConstructTime(timeFormat, tmpAmPmState, tmpHour, tmpMinute, (uint32) unixTime);
    dateTime->dayOfWeek = `$INSTANCE_NAME`_GetDayOfWeek(tmpDay, tmpMonth, tmpYear);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RelativeToFixed
****************************************************************************//**
*
* This is an internal function to convert a relative date into a fixed date.
*
* \param dayOfWeek
* A day of a week, see \ref group_rtc_day_of_the_week
*
* \param weekOfMonth
* A week of a month, see \ref group_rtc_dst_week_of_month
*
* \param month
* A month of a year, see \ref group_rtc_month
*
* \param year
* A year value
*
* \return A date in the "date format"
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_RelativeToFixed(uint32 dayOfWeek, uint32 weekOfMonth, uint32 month, uint32 year)
{
    uint32 curDay;
    uint32 curWeek;
    uint32 daysInMonth;
    uint32 dayOfMonthTmp;

    uint32 retVal;

    curDay      = 1u;
    curWeek     = (uint32)`$INSTANCE_NAME`_FIRST;
    daysInMonth = `$INSTANCE_NAME`_DaysInMonth(month, year);
    dayOfMonthTmp = curDay;

    while((curWeek <= weekOfMonth) && (curDay <= daysInMonth))
    {
        if(dayOfWeek == `$INSTANCE_NAME`_GetDayOfWeek(curDay, month, year))
        {
            dayOfMonthTmp = curDay;
            curWeek++;
        }
        curDay++;
    }

    retVal = `$INSTANCE_NAME`_ConstructDate(month, dayOfMonthTmp, year);

    return(retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DaysInMonth
****************************************************************************//**
*
* Returns a number of days in a month passed through the parameters.
*
* \param month
* A month of a year, see \ref group_rtc_month.
*
* \param year
* A year value.
*
* \return
* A number of days in a month in the year passed through the parameters
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_DaysInMonth(uint32 month, uint32 year)
{
    uint32 retVal;

    retVal = `$INSTANCE_NAME`_daysInMonthTbl[month - 1u];
    if((uint32)`$INSTANCE_NAME`_FEBRUARY == month)
    {
        if(0u != `$INSTANCE_NAME`_LeapYear(year))
        {
            retVal++;
        }
    }

    return(retVal);
}


/* [] END OF FILE */
