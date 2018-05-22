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
    
#include "dma/dma.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_dma_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback functions structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_dma_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern stc_dma_config_t `$INSTANCE_NAME`_Config;

/* Transfer completion interrupt callback function */
`=($pfnDmaCompletionIrqCb eq "") || !$bCompleteIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnDmaCompletionIrqCb . "(void);"`

/* Transfer error interrupt callback function */
`=($pfnDmaErrorIrqCb eq "") || !$bErrorIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnDmaErrorIrqCb . "(uint8_t u8Argument);"`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
