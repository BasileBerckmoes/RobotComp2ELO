/*******************************************************************************
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* This file provides the source code to the API for the RTC Component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

/** Indicates whether or not the `$INSTANCE_NAME` has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  `$INSTANCE_NAME`_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the `$INSTANCE_NAME`_Start() routine.
*/
uint8_t `$INSTANCE_NAME`_initVar = 0u;

/** The instance-specific configuration structure. This should be used in the 
*  associated `$INSTANCE_NAME`_Init() function.
*/
cy_stc_rtc_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config =
{
    /* Initiate time and date */
    .sec       = `$INSTANCE_NAME`_INITIAL_DATE_SEC,
    .min       = `$INSTANCE_NAME`_INITIAL_DATE_MIN,
    .hour      = `$INSTANCE_NAME`_INITIAL_DATE_HOUR,
    .hrFormat  = `$INSTANCE_NAME`_INITIAL_DATE_HOUR_FORMAT,
    .dayOfWeek = `$INSTANCE_NAME`_INITIAL_DATE_DOW,
    .date      = `$INSTANCE_NAME`_INITIAL_DATE_DOM,
    .month     = `$INSTANCE_NAME`_INITIAL_DATE_MONTH,
    .year      = `$INSTANCE_NAME`_INITIAL_DATE_YEAR,
};

    /** `$INSTANCE_NAME`_rtcDstStatus variable which is for DST feature and is 
    *  called in Cy_RTC_Interrupt() PDL driver function. This variable is 
    *  defined as true if DST is enabled and as false if DST is disabled
    */
    bool `$INSTANCE_NAME`_rtcDstStatus = `= $DaylightSavingsTimeEn ? "true" : "false"`;

#if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)

    /** The instance-specific daylight saving time structure. This should be 
    * used in the associated DTS functions.
    */
    cy_stc_rtc_dst_t const `$INSTANCE_NAME`_dstConfig =
    {
        /* DST Start time */
        .startDst.format      = (cy_en_rtc_dst_format_t) `$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE,
        .startDst.hour        = `$INSTANCE_NAME`_INITIAL_DST_START_HRS,
        .startDst.dayOfMonth  = `$INSTANCE_NAME`_INITIAL_DST_START_DOM,
        .startDst.weekOfMonth = `$INSTANCE_NAME`_INITIAL_DST_START_WOM,
        .startDst.dayOfWeek   = `$INSTANCE_NAME`_INITIAL_DST_START_DOW,
        .startDst.month       = `$INSTANCE_NAME`_INITIAL_DST_START_MONTH,

        /* DST Stop time */
        .stopDst.format      = (cy_en_rtc_dst_format_t) `$INSTANCE_NAME`_INITIAL_DST_DATE_TYPE,
        .stopDst.hour        = `$INSTANCE_NAME`_INITIAL_DST_STOP_HRS,
        .stopDst.dayOfMonth  = `$INSTANCE_NAME`_INITIAL_DST_STOP_DOM,
        .stopDst.weekOfMonth = `$INSTANCE_NAME`_INITIAL_DST_STOP_WOM,
        .stopDst.dayOfWeek   = `$INSTANCE_NAME`_INITIAL_DST_STOP_DOW,
        .stopDst.month       = `$INSTANCE_NAME`_INITIAL_DST_STOP_MONTH,
    };
#else

    /* Default DST structure in condition that DST is disabled */
    cy_stc_rtc_dst_t const `$INSTANCE_NAME`_dstConfig;
#endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Optionally calls the `$INSTANCE_NAME`_Init() when called the first time and 
* configure the `$INSTANCE_NAME` as it is set in the customizer. For subsequent 
* calls the configuration is left unchanged and the component is just 
* configured. Invokes `$INSTANCE_NAME`_EnableDstTime() if the DST is enabled.
*
* \globalvars
* \ref `$INSTANCE_NAME`_initVar
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
        cy_stc_rtc_config_t curTimeAndDate;
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */
    
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        #if(0u != `$INSTANCE_NAME`_TIME_RESET_ON_START)

            /* Configure the component if power cycle and the external 
            *  reset occurred
            */
            if(Cy_RTC_IsExternalResetOccurred())
            {
                (void) Cy_RTC_Init(&`$INSTANCE_NAME`_config);
            }
        #endif /* (0u != `$INSTANCE_NAME`_TIME_RESET_ON_START) */

        #if(0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS)

            /* Hook the interrupt service routine */
            #if defined(`$INSTANCE_NAME`_RTC_IRQ__INTC_ASSIGNED)
                (void) Cy_SysInt_Init(&`$INSTANCE_NAME`_RTC_IRQ_cfg, &`$INSTANCE_NAME`_Interrupt);
            #endif /* defined(`$INSTANCE_NAME`_RTC_IRQ__INTC_ASSIGNED) */
        #endif /* (0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS) */

        /* The component is configured */
        `$INSTANCE_NAME`_initVar = 1u;
    }

    #if(0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS)
        #if defined(`$INSTANCE_NAME`_RTC_IRQ__INTC_ASSIGNED)
            NVIC_EnableIRQ(`$INSTANCE_NAME`_RTC_IRQ_cfg.intrSrc);
        #endif /* defined(`$INSTANCE_NAME`_RTC_IRQ__INTC_ASSIGNED) */

        #if(0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS)
            #if(0u != `$INSTANCE_NAME`_TIME_RESET_ON_START)
                
                /* Wait for previous RTC update */
                Cy_SysLib_Delay(`$INSTANCE_NAME`_DELAY_BEFORE_DST);
            #endif /* (0u != `$INSTANCE_NAME`_TIME_RESET_ON_START) */
                
            Cy_RTC_GetDateAndTime(&curTimeAndDate);
            
            /* Set the DST configuration */
            if(Cy_RTC_EnableDstTime(&`$INSTANCE_NAME`_dstConfig, &curTimeAndDate) != CY_RTC_SUCCESS)
            {
                /* DST Setting failed */
                CY_ASSERT(0u != 0u);
            }
        #endif /* (0u != `$INSTANCE_NAME`_INITIAL_DST_STATUS) */
    #endif /* (0u != `$INSTANCE_NAME`_INITIAL_IRQ_STATUS) */
}


/* [] END OF FILE */
