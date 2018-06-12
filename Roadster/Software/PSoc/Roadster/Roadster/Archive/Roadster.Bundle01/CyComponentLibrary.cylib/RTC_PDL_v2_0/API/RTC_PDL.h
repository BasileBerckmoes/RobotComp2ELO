/*******************************************************************************
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* This file provides the constants and parameter values for the RTC Component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_RTC_PDL_H)
#define `$INSTANCE_NAME`_RTC_PDL_H

#include "cyfitter.h"
#include "rtc/cy_rtc.h"

/* Initial interrupt state definition */
#define `$INSTANCE_NAME`_INITIAL_IRQ_STATUS        (`$EnableRtcInterrupt`u)


/*******************************************************************************
*       Additional includes
*******************************************************************************/
#if (0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS)
    #include "sysint/cy_sysint.h"
    #include "cyfitter_sysint.h"
    #include "cyfitter_sysint_cfg.h"
#endif /* (0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS) */


/*******************************************************************************
*    Parameters definitions
*******************************************************************************/
/* Date Format setting constants */
#define `$INSTANCE_NAME`_MM_DD_YYYY                (0u)
#define `$INSTANCE_NAME`_DD_MM_YYYY                (1u)
#define `$INSTANCE_NAME`_YYYY_MM_DD                (2u)

/* Initial Date format definition */
#define `$INSTANCE_NAME`_INITIAL_DATA_FORMAT       (`$DateFormat`u)

/* Time reset on start constant */
#define `$INSTANCE_NAME`_TIME_RESET_ON_START       (`$TimeResetOnStart`u)

/* Initial Time and Date definitions */
#define `$INSTANCE_NAME`_INITIAL_DATE_SEC          (0u)
#define `$INSTANCE_NAME`_INITIAL_DATE_MIN          (0u)
#define `$INSTANCE_NAME`_INITIAL_DATE_HOUR         (`$Hour`u)
#define `$INSTANCE_NAME`_INITIAL_DATE_HOUR_FORMAT  (CY_RTC_24_HOURS)
#define `$INSTANCE_NAME`_INITIAL_DATE_DOW          (`$DayOfWeek`u)
#define `$INSTANCE_NAME`_INITIAL_DATE_DOM          (`$DayOfMonth`u)
#define `$INSTANCE_NAME`_INITIAL_DATE_MONTH        (`$Month`u)
#define `$INSTANCE_NAME`_INITIAL_DATE_YEAR         (`$Year`u)

/* Initial DST definitions */
#define `$INSTANCE_NAME`_INITIAL_DST_STATUS        (`$DaylightSavingsTimeEn`u)

#if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
    
    #if(0u != `$INSTANCE_NAME`_TIME_RESET_ON_START)

        /* Definition of delay time which is required in Start function */
        #define `$INSTANCE_NAME`_DELAY_BEFORE_DST          (500u)
    #endif /* (0u != `$INSTANCE_NAME`_TIME_RESET_ON_START) */
    
    #define `$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE     (`$DstDateType`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_START_MONTH   (`$MonthDstStart`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_START_WOM     (`$WeekOfMonthDstStart`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_START_DOM     (`$DayOfMonthDstStart`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_START_DOW     (`$DayOfWeekDstStart`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_START_HRS     (`$HoursDstStart`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_STOP_MONTH    (`$MonthDstStop`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_STOP_DOM      (`$DayOfMonthDstStop`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_STOP_DOW      (`$DayOfWeekDstStop`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_STOP_WOM      (`$WeekOfMonthDstStop`u)
    #define `$INSTANCE_NAME`_INITIAL_DST_STOP_HRS      (`$HoursDstStop`u)
#endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */

/*
* Definition of the date register fields. These macros are for creating a date
* value in a single word with the required date elements sequence.
*/
#if(`$INSTANCE_NAME`_INITIAL_DATA_FORMAT == `$INSTANCE_NAME`_MM_DD_YYYY)
    #define `$INSTANCE_NAME`_10_MONTH_OFFSET   (28u)
    #define `$INSTANCE_NAME`_MONTH_OFFSET      (24u)
    #define `$INSTANCE_NAME`_10_DAY_OFFSET     (20u)
    #define `$INSTANCE_NAME`_DAY_OFFSET        (16u)
    #define `$INSTANCE_NAME`_1000_YEAR_OFFSET  (12u)
    #define `$INSTANCE_NAME`_100_YEAR_OFFSET   (8u)
    #define `$INSTANCE_NAME`_10_YEAR_OFFSET    (4u)
    #define `$INSTANCE_NAME`_YEAR_OFFSET       (0u)
#elif(`$INSTANCE_NAME`_INITIAL_DATA_FORMAT == `$INSTANCE_NAME`_DD_MM_YYYY)
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
#endif /* (`$INSTANCE_NAME`_INITIAL_DATA_FORMAT == `$INSTANCE_NAME`_MM_DD_YYYY) */


/*******************************************************************************
*    Global Variables
*******************************************************************************/
extern uint8_t `$INSTANCE_NAME`_initVar;
/**
* \addtogroup group_globals
* \{
*/
extern bool `$INSTANCE_NAME`_rtcDstStatus;
extern cy_stc_rtc_dst_t const `$INSTANCE_NAME`_dstConfig;
extern cy_stc_rtc_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config;
/** \} group_globals */


/*******************************************************************************
*    Function Prototypes
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void);

__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_Init(cy_stc_rtc_config_t const *config);
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetDateAndTime(cy_stc_rtc_config_t const *dateTime);
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetDateAndTimeDirect(uint32_t sec, uint32_t min, uint32_t hour, 
                                                                  uint32_t date, uint32_t month, uint32_t year);
__STATIC_INLINE void `$INSTANCE_NAME`_GetDateAndTime(cy_stc_rtc_config_t *dateTime);

__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetAlarmDateAndTime(cy_stc_rtc_alarm_t const *alarmDateTime,
                                                                        cy_en_rtc_alarm_t alarmIndex);
__STATIC_INLINE void `$INSTANCE_NAME`_GetAlarmDateAndTime(cy_stc_rtc_alarm_t *alarmDateTime,
                                                               cy_en_rtc_alarm_t alarmIndex);
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetAlarmDateAndTimeDirect(uint32_t sec, uint32_t min, 
                                                                              uint32_t hour, uint32_t date, 
                                                                              uint32_t month, cy_en_rtc_alarm_t alarmIndex);

__STATIC_INLINE cy_en_rtc_hours_format_t `$INSTANCE_NAME`_GetHoursFormat(void);
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetHoursFormat(cy_en_rtc_hours_format_t hourMode);
__STATIC_INLINE void `$INSTANCE_NAME`_SelectFrequencyPrescaler(cy_en_rtc_clock_freq_t clkSel);

__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t interruptMask);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t interruptMask);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t interruptMask);

#if(0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS)

    __STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void);
    __STATIC_INLINE void `$INSTANCE_NAME`_DstInterrupt(cy_stc_rtc_dst_t const *dstTime);

    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)

        __STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_EnableDstTime(cy_stc_rtc_dst_t const *dstTime, 
                                                                          cy_stc_rtc_config_t const *timeDate);
        __STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetNextDstTime(cy_stc_rtc_dst_format_t const *nextDst);
        __STATIC_INLINE bool `$INSTANCE_NAME`_GetDstStatus(cy_stc_rtc_dst_t const *dstTime, 
                                                           cy_stc_rtc_config_t const *timeDate);
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */
#endif /* (0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Invokes the Cy_RTC_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_Init(cy_stc_rtc_config_t const *config)
{
    return(Cy_RTC_Init(config));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetHoursFormat
****************************************************************************//**
*
* Invokes the Cy_RTC_GetHoursFormat() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_hours_format_t `$INSTANCE_NAME`_GetHoursFormat(void)
{
    return(Cy_RTC_GetHoursFormat());
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetHoursFormat
****************************************************************************//**
*
* Invokes the Cy_RTC_SetHoursFormat() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetHoursFormat(cy_en_rtc_hours_format_t hourMode)
{
    return(Cy_RTC_SetHoursFormat(hourMode));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SelectFrequencyPrescaler()
****************************************************************************//**
*
* Invokes the Cy_RTC_SelectFrequencyPrescaler() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SelectFrequencyPrescaler(cy_en_rtc_clock_freq_t clkSel)
{
    Cy_RTC_SelectFrequencyPrescaler(clkSel);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_SetDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetDateAndTime(cy_stc_rtc_config_t const *dateTime)
{
    return(Cy_RTC_SetDateAndTime(dateTime));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_GetDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_GetDateAndTime(cy_stc_rtc_config_t *dateTime)
{
    Cy_RTC_GetDateAndTime(dateTime);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAlarmDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_SetAlarmDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetAlarmDateAndTime(cy_stc_rtc_alarm_t const *alarmDateTime,
                                                                        cy_en_rtc_alarm_t alarmIndex)
{
    return(Cy_RTC_SetAlarmDateAndTime(alarmDateTime, alarmIndex));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAlarmDateAndTime
****************************************************************************//**
*
* Invokes the Cy_RTC_GetAlarmDateAndTime() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_GetAlarmDateAndTime(cy_stc_rtc_alarm_t *alarmDateTime, 
                                                          cy_en_rtc_alarm_t alarmIndex)
{
    Cy_RTC_GetAlarmDateAndTime(alarmDateTime, alarmIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDateAndTimeDirect
****************************************************************************//**
*
* Invokes the Cy_RTC_SetDateAndTimeDirect() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetDateAndTimeDirect(uint32_t sec, uint32_t min, uint32_t hour, 
                                                                         uint32_t date, uint32_t month, uint32_t year)
{
    return(Cy_RTC_SetDateAndTimeDirect(sec, min, hour, date, month, year));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAlarmDateAndTimeDirect
****************************************************************************//**
*
* Invokes the Cy_RTC_SetAlarmDateAndTimeDirect() PDL driver function.
*
*******************************************************************************/

__STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetAlarmDateAndTimeDirect(uint32_t sec, uint32_t min, 
                                                                              uint32_t hour, uint32_t date,
                                                                              uint32_t month, 
                                                                              cy_en_rtc_alarm_t alarmIndex)
{
    return(Cy_RTC_SetAlarmDateAndTimeDirect(sec, min, hour, date, month, alarmIndex));
}

#if(0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_Interrupt
    ****************************************************************************//**
    *
    * RTC interrupt handler function. 
    * Invokes the Cy_RTC_Interrupt() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void)
    {
        Cy_RTC_Interrupt(&`$INSTANCE_NAME`_dstConfig, `$INSTANCE_NAME`_rtcDstStatus);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DstInterrupt
    ****************************************************************************//**
    * 
    * Invokes the RTC_DstInterrupt() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void `$INSTANCE_NAME`_DstInterrupt(cy_stc_rtc_dst_t const *dstTime)
    {
        Cy_RTC_DstInterrupt(dstTime);
    }


    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EnableDstTime
        ****************************************************************************//**
        * 
        * Invokes the Cy_RTC_EnableDstTime() PDL driver function.
        *
        *******************************************************************************/
        __STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_EnableDstTime(cy_stc_rtc_dst_t const *dstTime, 
                                                                          cy_stc_rtc_config_t const *timeDate)
        {
            return(Cy_RTC_EnableDstTime(dstTime, timeDate));
        }


        /*******************************************************************************
        * Function Name: Cy_RTC_SetNextDstTime
        ****************************************************************************//**
        *
        * Invokes the Cy_RTC_SetNextDstTime() PDL driver function.
        *
        *******************************************************************************/
        __STATIC_INLINE cy_en_rtc_status_t `$INSTANCE_NAME`_SetNextDstTime(cy_stc_rtc_dst_format_t const *nextDst)
        {
            return(Cy_RTC_SetNextDstTime(nextDst));
        }

        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_GetDstStatus
        ****************************************************************************//**
        *
        * Invokes the Cy_RTC_GetDstStatus() PDL driver function.
        *
        *******************************************************************************/
        __STATIC_INLINE bool `$INSTANCE_NAME`_GetDstStatus(cy_stc_rtc_dst_t const *dstTime, 
                                                           cy_stc_rtc_config_t const *timeDate)
        {
            return(Cy_RTC_GetDstStatus(dstTime, timeDate));
        }
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */

#endif /* (0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS) */



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_RTC_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return(Cy_RTC_GetInterruptStatus());
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_RTC_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t interruptMask)
{
    Cy_RTC_ClearInterrupt(interruptMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_RTC_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t interruptMask)
{
    Cy_RTC_SetInterrupt(interruptMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_RTC_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return(Cy_RTC_GetInterruptMask());
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_RTC_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t interruptMask)
{
    Cy_RTC_SetInterruptMask(interruptMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsExternalResetOccurred
****************************************************************************//**
*
* Invokes the Cy_RTC_IsExternalResetOccurred() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool `$INSTANCE_NAME`_IsExternalResetOccurred(void)
{
    return(Cy_RTC_IsExternalResetOccurred());
}

#endif /* `$INSTANCE_NAME`_RTC_PDL_H */


/* [] END OF FILE */
