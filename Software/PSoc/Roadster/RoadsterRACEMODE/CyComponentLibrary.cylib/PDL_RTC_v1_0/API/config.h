/*******************************************************************************
* \file `$INSTANCE_NAME`_config.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable declarations for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_CONFIG_H
#define `$INSTANCE_NAME`_CONFIG_H

#include "rtc/rtc.h"
#include "cyfitter.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_rtc__HW

#define `$INSTANCE_NAME`_RTCCO_EN   `=$bEnableRtcco ? "1u" : "0u"`
#define `$INSTANCE_NAME`_SUBOUT_EN  `=$bEnableSubout ? "1u" : "0u"`

#if (`$INSTANCE_NAME`_RTCCO_EN)
    #define `$INSTANCE_NAME`_SetPinFunc_RTCCO CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_rtc__`$INSTANCE_NAME`_RTCCO
#endif

#if (`$INSTANCE_NAME`_SUBOUT_EN)
    #define `$INSTANCE_NAME`_SetPinFunc_SUBOUT CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_rtc__`$INSTANCE_NAME`_SUBOUT
#endif

/* Frequency correction structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_freq_corr_t `$INSTANCE_NAME`_FreqCorrConfig;

/* Date and time structure */
extern stc_rtc_time_t `$INSTANCE_NAME`_TimeDate;

/* Alarm structure */
extern stc_rtc_alarm_t `$INSTANCE_NAME`_Alarm;

/* Timer configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_timer_t `$INSTANCE_NAME`_Timer;

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback functions structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rtc_config_t `$INSTANCE_NAME`_Config;

/* Time rewrite error interrupt callback function */
`=($pfnTimeWrtErrIrqCb eq "") || !$bTimeRewriteErrorIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnTimeWrtErrIrqCb . "(void);"`

/* Alarm interrupt callback function */
`=($pfnAlarmIrqCb eq "") || !$bAlarmIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnAlarmIrqCb . "(void);"`

/* Timer interrupt callback function */
`=($pfnTimerIrqCb eq "") || !$bTimerIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnTimerIrqCb . "(void);"`

/* 0.5-second interrupt callback function */
`=($pfnHalfSecondIrqCb eq "") || !$bHalfSecondIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnHalfSecondIrqCb . "(void);"`

/* 1-second interrupt callback function */
`=($pfnOneSecondIrqCb eq "") || !$bOneSecondIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnOneSecondIrqCb . "(void);"`

/* 1-minute interrupt callback function */
`=($pfnOneMinuteIrqCb eq "") || !$bOneMinuteIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnOneMinuteIrqCb . "(void);"`

/* 1-hour interrupt callback function */
`=($pfnOneHourIrqCb eq "") || !$bOneHourIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnOneHourIrqCb . "(void);"`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
