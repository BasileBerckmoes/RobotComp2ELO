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

/* Channel 0 configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_dt_channel_config_t `$INSTANCE_NAME`_Ch0_Config =
{
    /* u8Mode */                `=GetNameForEnum("en_dt_mode_t", $u8Ch0Mode)`,
    /* u8PrescalerDiv */        `=GetNameForEnum("en_dt_prescaler_t", $u8Ch0PrescalerDiv)`,
    /* u8CounterSize */         `=GetNameForEnum("en_dt_countersize_t", $u8Ch0CounterSize)`,
#if (PDL_INTERRUPT_ENABLE_DT0 == PDL_ON)    
    /* bIrqEnable */            `=$bCh0IrqEnable ? "TRUE" : "FALSE"`,
    /* pfnIrqCallback */        `=($pfnCh0IrqCallback eq "") || !$bCh0IrqEnable ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnCh0IrqCallback`, /* User-supplied callback function */
    /* bTouchNvic */            `=$bCh0TouchNvic ? "TRUE" : "FALSE"`
#endif    
};

/* Channel 1 configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_dt_channel_config_t `$INSTANCE_NAME`_Ch1_Config =
{
    /* u8Mode */                `=GetNameForEnum("en_dt_mode_t", $u8Ch1Mode)`,
    /* u8PrescalerDiv */        `=GetNameForEnum("en_dt_prescaler_t", $u8Ch1PrescalerDiv)`,
    /* u8CounterSize */         `=GetNameForEnum("en_dt_countersize_t", $u8Ch1CounterSize)`,
#if (PDL_INTERRUPT_ENABLE_DT0 == PDL_ON)    
    /* bIrqEnable */            `=$bCh1IrqEnable ? "TRUE" : "FALSE"`,
    /* pfnIrqCallback */        `=($pfnCh1IrqCallback eq "") || !$bCh1IrqEnable ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnCh1IrqCallback`, /* User-supplied callback function */
    /* bTouchNvic */            `=$bCh1TouchNvic ? "TRUE" : "FALSE"`
#endif    
};

/* [] END OF FILE */
