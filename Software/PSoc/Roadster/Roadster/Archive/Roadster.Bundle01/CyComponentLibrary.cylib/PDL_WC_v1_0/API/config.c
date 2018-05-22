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

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_wc_config_t `$INSTANCE_NAME`_Config =
{
    /* enCntClk */              `=GetNameForEnum("en_wc_cnt_clk_t", $enCntClk)`,  
    /* u8ReloadValue */         `$u8ReloadValue`u, 
#if (PDL_INTERRUPT_ENABLE_WC0 == PDL_ON)    
    /* bIrqEnable */            `=$bIrqEnable ? "TRUE" : "FALSE"`,
    /* pfnIrqCallback */        `=($pfnIrqCallback eq "") || !$bIrqEnable ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnIrqCallback`, /* User-supplied callback function */
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif  
};

/* [] END OF FILE */
