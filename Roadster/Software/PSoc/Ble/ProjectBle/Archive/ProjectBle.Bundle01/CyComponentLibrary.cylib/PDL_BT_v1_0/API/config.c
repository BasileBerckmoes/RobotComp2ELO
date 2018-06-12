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


/*******************************************************************************
*                      PWM Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWM)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_pwm_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bPwmTrigIrq */           `=$bPwmTrigIrq ? "TRUE" : "FALSE"`,
    /* bPwmDutyMatchIrq */      `=$bPwmDutyMatchIrq ? "TRUE" : "FALSE"`,
    /* bPwmUnderflowIrq */      `=$bPwmUnderflowIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_pwm_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnPwmTrigIrqCb */       `=($pfnPwmTrigIrqCb eq "") || !$bPwmTrigIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPwmTrigIrqCb`, /* User-supplied callback function */
    /* pfnPwmDutyMatchIrqCb */  `=($pfnPwmDutyMatchIrqCb eq "") || !$bPwmDutyMatchIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPwmDutyMatchIrqCb`, /* User-supplied callback function */
    /* pfnPwmUnderflowIrqCb */  `=($pfnPwmUnderflowIrqCb eq "") || !$bPwmUnderflowIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPwmUnderflowIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_bt_pwm_config_t `$INSTANCE_NAME`_Config =
{
    /* enPres */                `=GetNameForEnum("en_pwm_clock_pres_t", $enPwmPres)`,
    /* enRestartEn */           `=GetNameForEnum("en_pwm_restart_enable_t", $enPwmRestartEn)`,
    /* enOutputMask */          `=GetNameForEnum("en_pwm_output_mask_t", $enPwmOutputMask)`,
    /* enExtTrig */             `=GetNameForEnum("en_pwm_ext_trig_t", $enPwmExtTrig)`,
    /* enOutputPolarity */      `=GetNameForEnum("en_pwm_output_polarity_t", $enPwmOutputPolarity)`,
    /* enMode */                `=GetNameForEnum("en_pwm_mode_t", $enPwmMode)`,
#if defined(PDL_INTERRUPT_BT_ACTIVE)    
    /* pstcPwmIrqEn */          `=$CY_CONST_CONFIG ? "(stc_pwm_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcPwmIrqCb */          `=$CY_CONST_CONFIG ? "(stc_pwm_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWM */


/*******************************************************************************
*                      PPG Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PPG)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_ppg_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bPpgTrigIrq */           `=$bPpgTrigIrq ? "TRUE" : "FALSE"`,
    /* bPpgUnderflowIrq */      `=$bPpgUnderflowIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_ppg_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnPpgTrigIrqCb */       `=($pfnPpgTrigIrqCb eq "") || !$bPpgTrigIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPpgTrigIrqCb`, /* User-supplied callback function */
    /* pfnPpgUnderflowIrqCb */  `=($pfnPpgUnderflowIrqCb eq "") || !$bPpgUnderflowIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPpgUnderflowIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_bt_ppg_config_t `$INSTANCE_NAME`_Config =
{
    /* enPres */                `=GetNameForEnum("en_ppg_clock_pres_t", $enPpgPres)`,
    /* enRestartEn */           `=GetNameForEnum("en_ppg_restart_enable_t", $enPpgRestartEn)`,
    /* enOutputMask */          `=GetNameForEnum("en_ppg_output_mask_t", $enPpgOutputMask)`,
    /* enExtTrig */             `=GetNameForEnum("en_ppg_ext_trig_t", $enPpgExtTrig)`,
    /* enOutputPolarity */      `=GetNameForEnum("en_ppg_output_polarity_t", $enPpgOutputPolarity)`,
    /* enMode */                `=GetNameForEnum("en_ppg_mode_t", $enPpgMode)`,
#if defined(PDL_INTERRUPT_BT_ACTIVE)    
    /* pstcPpgIrqEn */          `=$CY_CONST_CONFIG ? "(stc_ppg_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcPpgIrqCb */          `=$CY_CONST_CONFIG ? "(stc_ppg_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PPG */


/*******************************************************************************
*                     PWC Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWC)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_pwc_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bPwcMeasureCompleteIrq */    `=$bPwcMeasureCompleteIrq ? "TRUE" : "FALSE"`,
    /* bPwcMeasureOverflowIrq */    `=$bPwcMeasureOverflowIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_pwc_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnPwcMeasureCompleteIrqCb */ `=($pfnPwcMeasureCompleteIrqCb eq "") || !$bPwcMeasureCompleteIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPwcMeasureCompleteIrqCb`, /* User-supplied callback function */
    /* pfnPwcMeasureOverflowIrqCb */ `=($pfnPwcMeasureOverflowIrqCb eq "") || !$bPwcMeasureOverflowIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPwcMeasureOverflowIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_bt_pwc_config_t `$INSTANCE_NAME`_Config =
{
    /* enPres */                `=GetNameForEnum("en_pwc_clock_pres_t", $enPwcPres)`,
    /* enSize */                `=GetNameForEnum("en_pwc_timer_size_t", $enPwcSize)`,
    /* enMeasureEdge */         `=GetNameForEnum("en_pwc_measure_edge_t", $enPwcMeasureEdge)`,
    /* enMode */                `=GetNameForEnum("en_pwc_mode_t", $enPwcMode)`,
#if defined(PDL_INTERRUPT_BT_ACTIVE)    
    /* pstcPwcIrqEn */          `=$CY_CONST_CONFIG ? "(stc_pwc_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcPwcIrqCb */          `=$CY_CONST_CONFIG ? "(stc_pwc_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_PWC */


/*******************************************************************************
*                      RT Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_RT)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rt_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bRtTrigIrq */           `=$bRtTrigIrq ? "TRUE" : "FALSE"`,
    /* bRtUnderflowIrq */      `=$bRtUnderflowIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rt_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnRtTrigIrqCb */        `=($pfnRtTrigIrqCb eq "") || !$bRtTrigIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRtTrigIrqCb`, /* User-supplied callback function */
    /* pfnRtUnderflowIrqCb */   `=($pfnRtUnderflowIrqCb eq "") || !$bRtUnderflowIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRtUnderflowIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_bt_rt_config_t `$INSTANCE_NAME`_Config =
{
    /* enPres */                `=GetNameForEnum("en_rt_clock_pres_t", $enRtPres)`,
    /* enSize */                `=GetNameForEnum("en_rt_timer_size_t", $enRtSize)`,
    /* enExtTrig */             `=GetNameForEnum("en_rt_ext_trigger_t", $enRtExtTrig)`,
    /* enOutputPolarity */      `=GetNameForEnum("en_rt_output_polarity_t", $enRtOutputPolarity)`,
    /* enMode */                `=GetNameForEnum("en_rt_mode_t", $enRtMode)`,
#if defined(PDL_INTERRUPT_BT_ACTIVE)    
    /* pstcRtIrqEn */           `=$CY_CONST_CONFIG ? "(stc_rt_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcRtIrqCb */           `=$CY_CONST_CONFIG ? "(stc_rt_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_BT_CONFIG == `$INSTANCE_NAME`_BT_RT */


/* [] END OF FILE */
