/*******************************************************************************
* \file `$INSTANCE_NAME`_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable definitions for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_config.h"

/* Frequency correction structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_freq_corr_t `$INSTANCE_NAME`_FreqCorrConfig =
{ 
    /* u16FreqCorrValue */      `$u16FreqCorrValue`u, 
#if (PDL_RTC_TYPE != PDL_RTC_WITHOUT_VBAT_TYPEA) 
    /* u16FreqCorrCycle */      `$u16FreqCorrCycle`u
#endif
};

/* Date and time structure */
stc_rtc_time_t `$INSTANCE_NAME`_TimeDate =
{
    /* u8Second */              `$u8Second`u,
    /* u8Minute */              `$u8Minute`u,
    /* u8Hour */                `$u8Hour`u,
    /* u8Day */                 `$u8Day`u,
    /* u8DayOfWeek */           `$u8DayOfWeek`u,
    /* u8Month */               `$u8Month`u,
    /* u16Year */               `$u16Year`u
};

/* Alarm structure */
stc_rtc_alarm_t `$INSTANCE_NAME`_Alarm =
{
    /* u8AlarmMinute */         `$u8AlarmMinute`u,
    /* u8AlarmHour */           `$u8AlarmHour`u,
    /* u8AlarmDay */            `$u8AlarmDay`u,
    /* u8AlarmMonth */          `$u8AlarmMonth`u,
    /* u16AlarmYear */          `$u16AlarmYear`u
};

/* Timer configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_timer_t `$INSTANCE_NAME`_Timer =
{
    /* enMode */                `=GetNameForEnum("en_rtc_time_mode_t", $enMode)`,
    /* u32TimerCycle */         `$u32TimerCycle`u
};

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bHalfSecondIrq */        `=$bHalfSecondIrq ? "TRUE" : "FALSE"`,
    /* bOneSecondIrq */         `=$bOneSecondIrq ? "TRUE" : "FALSE"`,
    /* bOneMinuteIrq */         `=$bOneMinuteIrq ? "TRUE" : "FALSE"`,
    /* bOneHourIrq */           `=$bOneHourIrq ? "TRUE" : "FALSE"`,
    /* bTimerIrq */             `=$bTimerIrq ? "TRUE" : "FALSE"`,
    /* bAlarmIrq */             `=$bAlarmIrq ? "TRUE" : "FALSE"`,
    /* bTimeRewriteErrorIrq */  `=$bTimeRewriteErrorIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback functions structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnTimeWrtErrIrqCb */    `=($pfnTimeWrtErrIrqCb eq "") || !$bTimeRewriteErrorIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTimeWrtErrIrqCb`, /* User-supplied callback function */
    /* pfnAlarmIrqCb */         `=($pfnAlarmIrqCb eq "") || !$bAlarmIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnAlarmIrqCb`, /* User-supplied callback function */
    /* pfnTimerIrqCb */         `=($pfnTimerIrqCb eq "") || !$bTimerIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTimerIrqCb`, /* User-supplied callback function */
    /* pfnHalfSecondIrqCb */    `=($pfnHalfSecondIrqCb eq "") || !$bHalfSecondIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnHalfSecondIrqCb`, /* User-supplied callback function */
    /* pfnOneSecondIrqCb */     `=($pfnOneSecondIrqCb eq "") || !$bOneSecondIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnOneSecondIrqCb`, /* User-supplied callback function */
    /* pfnOneMinuteIrqCb */     `=($pfnOneMinuteIrqCb eq "") || !$bOneMinuteIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnOneMinuteIrqCb`, /* User-supplied callback function */
    /* pfnOneHourIrqCb */       `=($pfnOneHourIrqCb eq "") || !$bOneHourIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnOneHourIrqCb`, /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_config_t `$INSTANCE_NAME`_Config =
{
#if (PDL_RTC_TYPE == PDL_RTC_WITHOUT_VBAT_TYPEA) || (PDL_RTC_TYPE == PDL_RTC_WITHOUT_VBAT_TYPEB)    
    /* enClkSel */              `=GetNameForEnum("en_rtc_clk_sel_t", $enClkSel)`,
    /* u32ClkPrescaler */       `$u32ClkPrescaler`u,
#endif    
    /* bEnSuboutDivider */      `=$bEnSuboutDivider ? "TRUE" : "FALSE"`,
                                             
    /* enDividerRatio */        `=GetNameForEnum("en_rtc_div_ratio_t", $enDividerRatio)`,
    /* enRtccoSel */            `=GetNameForEnum("en_rtc_rtcco_sel_t", $enRtccoSel)`,
        
    /* pstcFreqCorrConfig */    `=$bFrequencyCorrection ? 
                                 $CY_CONST_CONFIG ? "(stc_rtc_freq_corr_t *)&" . $INSTANCE_NAME . "_FreqCorrConfig" : 
                                                "&" . $INSTANCE_NAME . "_FreqCorrConfig" : "NULL"`,
    /* pstcTimeDate */          &`$INSTANCE_NAME`_TimeDate,
    /* pstcAlarm */             &`$INSTANCE_NAME`_Alarm,
    /* pstcTimer */             `=$CY_CONST_CONFIG ? "(stc_rtc_timer_t *)" : ""`&`$INSTANCE_NAME`_Timer,
#if (PDL_INTERRUPT_ENABLE_RTC0 == PDL_ON)        
    /* pstcIrqEn */             `=$CY_CONST_CONFIG ? "(stc_rtc_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */             `=$CY_CONST_CONFIG ? "(stc_rtc_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`,
#endif    
    /* bRunNotInit */           `=$bRunNotInit ? "TRUE" : "FALSE"`
};

/* [] END OF FILE */
