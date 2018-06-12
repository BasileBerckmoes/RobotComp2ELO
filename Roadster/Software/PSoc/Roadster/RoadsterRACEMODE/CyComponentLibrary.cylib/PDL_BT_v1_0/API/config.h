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

#include "bt/bt.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_BT_UNCONFIGURED    0U
#define `$INSTANCE_NAME`_BT_PWM             1U
#define `$INSTANCE_NAME`_BT_PPG             2U
#define `$INSTANCE_NAME`_BT_RT              3U
#define `$INSTANCE_NAME`_BT_PWC             4U
#define `$INSTANCE_NAME`_BT_CONFIG          `$BTConfig`U

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW                 `=LookupFitterDefine("`$INSTANCE_NAME`_fm_bt_BT_HW")`
#define `$INSTANCE_NAME`_IDX                `=LookupFitterDefine("`$INSTANCE_NAME`_fm_bt_BT_HW_IDX")`U

/* Pin function macros */
`=$ConnectTIOA ? "#define `$INSTANCE_NAME`_SetPinFunc_TIOA_OUT()" . LookupFitterDefine("CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_bt__`$INSTANCE_NAME`_TIOA") . "_OUT()" : "/* TIOA unused */"`

/* On odd timer channels TIOA can be additionaly used as an input signal */
#if ((`$INSTANCE_NAME`_IDX & 0x1U) != 0U)
    `=$ConnectTIOA ? "#define `$INSTANCE_NAME`_SetPinFunc_TIOA_IN()" . LookupFitterDefine("CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_bt__`$INSTANCE_NAME`_TIOA") . "_IN()" : "/* TIOA unused */"`
#endif

`=$ConnectTIOB ? "#define `$INSTANCE_NAME`_SetPinFunc_TIOB_IN()" . LookupFitterDefine("CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_bt__`$INSTANCE_NAME`_TIOB") . "_IN()" : "/* TIOB unused */"`

/*******************************************************************************
*                      PWM Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWM)
    
/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_pwm_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_pwm_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_bt_pwm_config_t `$INSTANCE_NAME`_Config;

/* Trigger interrupt callback function */
`=($pfnPwmTrigIrqCb eq "") || !$bPwmTrigIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPwmTrigIrqCb . "(void);"`

/* Duty match interrupt callback function */
`=($pfnPwmDutyMatchIrqCb eq "") || !$bPwmDutyMatchIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPwmDutyMatchIrqCb . "(void);"`

/* Underflow interrupt callback function */
`=($pfnPwmUnderflowIrqCb eq "") || !$bPwmUnderflowIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPwmUnderflowIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWM */


/*******************************************************************************
*                      PPG Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PPG)
    
/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_ppg_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_ppg_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_bt_ppg_config_t `$INSTANCE_NAME`_Config;

/* Trigger interrupt callback function */
`=($pfnPpgTrigIrqCb eq "") || !$bPpgTrigIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPpgTrigIrqCb . "(void);"`

/* Duty match interrupt callback function */
`=($pfnPpgUnderflowIrqCb eq "") || !$bPpgUnderflowIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPpgUnderflowIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PPG */


/*******************************************************************************
*                      PWC Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWC)
    
/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_pwc_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_pwc_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_bt_pwc_config_t `$INSTANCE_NAME`_Config;

/* Measure completion interrupt callback function */
`=($pfnPwcMeasureCompleteIrqCb eq "") || !$bPwcMeasureCompleteIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPwcMeasureCompleteIrqCb . "(void);"`

/* Measure overflow interrupt callback function */
`=($pfnPwcMeasureOverflowIrqCb eq "") || !$bPwcMeasureOverflowIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPwcMeasureOverflowIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWC */


/*******************************************************************************
*                      RT Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_RT)
    
/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rt_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rt_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_bt_rt_config_t `$INSTANCE_NAME`_Config;

/* Trigger interrupt callback function */
`=($pfnRtTrigIrqCb eq "") || !$bRtTrigIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRtTrigIrqCb . "(void);"`

/* Duty match interrupt callback function */
`=($pfnRtUnderflowIrqCb eq "") || !$bRtUnderflowIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRtUnderflowIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_RT */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
