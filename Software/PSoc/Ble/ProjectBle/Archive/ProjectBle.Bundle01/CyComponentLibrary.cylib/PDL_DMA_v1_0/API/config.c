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

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_dma_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bCompleteIrq */          `=$bCompleteIrq ? "TRUE" : "FALSE"`,
    /* bErrorIrq */             `=$bErrorIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback functions structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_dma_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnDmaCompletionIrqCb */ `=($pfnDmaCompletionIrqCb eq "") || !$bCompleteIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnDmaCompletionIrqCb`, /* User-supplied callback function */
    /* pfnDmaErrorIrqCb */      `=($pfnDmaErrorIrqCb eq "") || !$bErrorIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnDmaErrorIrqCb`, /* User-supplied callback function */
};

/* Configuration structure */
stc_dma_config_t `$INSTANCE_NAME`_Config =
{
    /* enDmaIdrq */             `=GetNameForEnum("en_dma_idreq_t", $enDmaIdrq)`,
    /* u8BlockCount */          `$u8BlockCount`u,
    /* u16TransferCount */      `$u16TransferCount`u,
    /* enTransferMode */        `=GetNameForEnum("en_dma_transfermode_t", $enTransferMode)`,
    /* enTransferWidth */       `=GetNameForEnum("en_dma_transferwidth_t", $enTransferWidth)`,
    /* u32SourceAddress */      0u, /* `$u32SourceAddress` */
    /* u32DestinationAddress */ 0u, /* `$u32DestinationAddress` */
    /* bFixedSource */          `=$bFixedSource ? "TRUE" : "FALSE"`,
    /* bFixedDestination */     `=$bFixedDestination ? "TRUE" : "FALSE"`,
    /* bReloadCount */          `=$bReloadCount ? "TRUE" : "FALSE"`,
    /* bReloadSource */         `=$bReloadSource ? "TRUE" : "FALSE"`,
    /* bReloadDestination */    `=$bReloadDestination ? "TRUE" : "FALSE"`,
    /* bEnableBitMask */        `=$bEnableBitMask ? "TRUE" : "FALSE"`,
#if (PDL_INTERRUPT_ENABLE_DMA0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_DMA1 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_DMA2 == PDL_ON) || (PDL_INTERRUPT_ENABLE_DMA3 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_DMA4 == PDL_ON) || (PDL_INTERRUPT_ENABLE_DMA5 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_DMA6 == PDL_ON) || (PDL_INTERRUPT_ENABLE_DMA7 == PDL_ON)   
    /* pstcIrqEn */             `=$CY_CONST_CONFIG ? "(stc_dma_irq_en_t*)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */             `=$CY_CONST_CONFIG ? "(stc_dma_irq_cb_t*)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};


/* [] END OF FILE */
