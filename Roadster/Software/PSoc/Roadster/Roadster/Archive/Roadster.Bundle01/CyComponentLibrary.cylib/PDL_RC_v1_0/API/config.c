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
*                      RC Common Receiver Config Definitions
*******************************************************************************/

#if ((`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_UNCONFIGURED) || \
     (`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_CEC_TX))

/* FIFO configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_addr_t `$INSTANCE_NAME`_RxAddr =
{
    /* u8Addr1 */          `$u8Addr1`u,
    /* u8Addr2 */          `$u8Addr2`u
};

#endif /* ((`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_UNCONFIGURED) ||
          (`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_CEC_TX)) */


/*******************************************************************************
*                      SIRCS Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_SIRCS)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_sircs_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bRcRxSircsStartIrq */        `=$bRcRxSircsStartIrq ? "TRUE" : "FALSE"`,
    /* bRcRxSircsAckIrq */          `=$bRcRxSircsAckIrq ? "TRUE" : "FALSE"`,
    /* bRcRxSircsCntOvfIrq */       `=$bRcRxSircsCntOvfIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_sircs_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnRcRxSircsStartIrqCb */    `=($pfnRcRxSircsStartIrqCb eq "") || !$bRcRxSircsStartIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxSircsStartIrqCb`, /* User-supplied callback function */
    /* pfnRcRxSircsAckIrqCb */      `=($pfnRcRxSircsAckIrqCb eq "") || !$bRcRxSircsAckIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxSircsAckIrqCb`, /* User-supplied callback function */
    /* pfnRcRxSircsCntOvfIrqCb */   `=($pfnRcRxSircsCntOvfIrqCb eq "") || !$bRcRxSircsCntOvfIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxSircsCntOvfIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_sircs_config_t `$INSTANCE_NAME`_Config =
{
    /* enSrcClk */                  `=GetNameForEnum("en_rc_src_clk_t", $enSrcClk)`,
    /* u16DivVal */                 `$u16DivVal`u,
    /* enThresholdType */           `=GetNameForEnum("en_rc_threshold_type_t", $enThresholdType)`,
    /* bAddrCmpEn */                `=$bAddrCmpEn ? "TRUE" : "FALSE"`,
    /* enOverflowCycle */           `=GetNameForEnum("en_rc_overflow_t", $enOverflowCycle)`,
    /* u8StartBitWidth */           `$u8StartBitWidth`u,
    /* u8MinPulseWidth */           `$u8MinPulseWidth`u,
    /* u8ThresholdWidth */          `$u8ThresholdWidth`u,
    /* stcAddr */                   
    {
        /* u8Addr1 */               `$u8Addr1`u,
        /* u8Addr2 */               `$u8Addr2`u
    },
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
    /* pstcIrqEn */                 `=$CY_CONST_CONFIG ? "(stc_rc_rx_sircs_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */                 `=$CY_CONST_CONFIG ? "(stc_rc_rx_sircs_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */                `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_SIRCS */


/*******************************************************************************
*                      NEC Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_NEC)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_nec_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bRcRxNecStartIrq */          `=$bRcRxNecStartIrq ? "TRUE" : "FALSE"`,
    /* bRcRxNecAckIrq */            `=$bRcRxNecAckIrq ? "TRUE" : "FALSE"`,
    /* bRcRxNecCntOvfIrq */         `=$bRcRxNecCntOvfIrq ? "TRUE" : "FALSE"`,
    /* bRcRxNecRepeatCodeIrq */     `=$bRcRxNecRepeatCodeIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_nec_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnRcRxNecStartIrqCb */      `=($pfnRcRxNecStartIrqCb eq "") || !$bRcRxNecStartIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxNecStartIrqCb`, /* User-supplied callback function */
    /* pfnRcRxNecAckIrqCb */        `=($pfnRcRxNecAckIrqCb eq "") || !$bRcRxNecAckIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxNecAckIrqCb`, /* User-supplied callback function */
    /* pfnRcRxNecCntOvfIrqCb */     `=($pfnRcRxNecCntOvfIrqCb eq "") || !$bRcRxNecCntOvfIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxNecCntOvfIrqCb`, /* User-supplied callback function */
    /* pfnRcRxNecRepeatCodeIrqCb */ `=($pfnRcRxNecRepeatCodeIrqCb eq "") || !$bRcRxNecRepeatCodeIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxNecRepeatCodeIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_nec_config_t `$INSTANCE_NAME`_Config =
{
    /* enSrcClk */                  `=GetNameForEnum("en_rc_src_clk_t", $enSrcClk)`,
    /* u16DivVal */                 `$u16DivVal`u,
    /* enThresholdType */           `=GetNameForEnum("en_rc_threshold_type_t", $enThresholdType)`,
    /* bAddrCmpEn */                `=$bAddrCmpEn ? "TRUE" : "FALSE"`,
    /* enOverflowCycle */           `=GetNameForEnum("en_rc_overflow_t", $enOverflowCycle)`,
    /* u8StartBitWidth */           `$u8StartBitWidth`u,
    /* u8MinPulseWidth */           `$u8MinPulseWidth`u,
    /* u8ThresholdWidth */          `$u8ThresholdWidth`u,
    /* u8RepeatWidth */             `$u8RepeatWidth`u,
    /* stcAddr */                   
    {
        /* u8Addr1 */               `$u8Addr1`u,
        /* u8Addr2 */               `$u8Addr2`u
    },
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
    /* pstcIrqEn */                 `=$CY_CONST_CONFIG ? "(stc_rc_rx_nec_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */                 `=$CY_CONST_CONFIG ? "(stc_rc_rx_nec_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */                `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_NEC */


/*******************************************************************************
*                      CEC Rx Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_RX)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_cec_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bRcRxCecStartIrq */          `=$bRcRxCecStartIrq ? "TRUE" : "FALSE"`,
    /* bRcRxCecAckIrq */            `=$bRcRxCecAckIrq ? "TRUE" : "FALSE"`,
    /* bRcRxCecCntOvfIrq */         `=$bRcRxCecCntOvfIrq ? "TRUE" : "FALSE"`,
    /* bRcRxCecMinDataIrq */        `=$bRcRxCecMinDataIrq ? "TRUE" : "FALSE"`,
    /* bRcRxCecMaxDataIrq */        `=$bRcRxCecMaxDataIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_cec_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnRcRxCecStartIrqCb */      `=($pfnRcRxCecStartIrqCb eq "") || !$bRcRxCecStartIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxCecStartIrqCb`, /* User-supplied callback function */
    /* pfnRcRxCecAckIrqCb */        `=($pfnRcRxCecAckIrqCb eq "") || !$bRcRxCecAckIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxCecAckIrqCb`, /* User-supplied callback function */
    /* pfnRcRxCecCntOvfIrqCb */     `=($pfnRcRxCecCntOvfIrqCb eq "") || !$bRcRxCecCntOvfIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxCecCntOvfIrqCb`, /* User-supplied callback function */
    /* pfnRcRxCecMinDataIrqCb */    `=($pfnRcRxCecMinDataIrqCb eq "") || !$bRcRxCecMinDataIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxCecMinDataIrqCb`, /* User-supplied callback function */
    /* pfnRcRxCecMaxDataIrqCb */    `=($pfnRcRxCecMaxDataIrqCb eq "") || !$bRcRxCecMaxDataIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcRxCecMaxDataIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_cec_config_t `$INSTANCE_NAME`_Config =
{
    /* enSrcClk */                  `=GetNameForEnum("en_rc_src_clk_t", $enSrcClk)`,
    /* u16DivVal */                 `$u16DivVal`u,
    /* enThresholdType */           `=GetNameForEnum("en_rc_threshold_type_t", $enThresholdType)`,
    /* enOverflowCycle */           `=GetNameForEnum("en_rc_overflow_t", $enOverflowCycle)`,
    /* bAddrCmpEn */                `=$bAddrCmpEn ? "TRUE" : "FALSE"`,
    /* bMinDataBitDetect */         `=$bMinDataBitDetect ? "TRUE" : "FALSE"`,
    /* bMaxDataBitDetect */         `=$bMaxDataBitDetect ? "TRUE" : "FALSE"`,
    /* bBusErrorPulseOutput */      `=$bBusErrorPulseOutput ? "TRUE" : "FALSE"`,
    /* u8StartBitWidth */           `$u8StartBitWidth`u,
    /* u8MinPulseWidth */           `$u8MinPulseWidth`u,
    /* u8ThresholdWidth */          `$u8ThresholdWidth`u,
    /* u8MinDataWidth */            `$u8MinDataWidth`u,
    /* u8MaxDataWidth */            `$u8MaxDataWidth`u,
    /* stcAddr */                   
    {
        /* u8Addr1 */               `$u8Addr1`u,
        /* u8Addr2 */               `$u8Addr2`u
    },
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
    /* pstcIrqEn */                 `=$CY_CONST_CONFIG ? "(stc_rc_rx_cec_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */                 `=$CY_CONST_CONFIG ? "(stc_rc_rx_cec_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */                `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_RX */


/*******************************************************************************
*                      CEC Tx Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_TX)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_tx_cec_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bRcTxCecBusErrorIrq */       `=$bRcTxCecBusErrorIrq ? "TRUE" : "FALSE"`,
    /* bRcTxCecStatusIrq */         `=$bRcTxCecStatusIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_tx_cec_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnRcTxIrqBusErrorCb */      `=($pfnRcTxIrqBusErrorCb eq "") || !$bRcTxCecBusErrorIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcTxIrqBusErrorCb`, /* User-supplied callback function */
    /* pfnRcTxIrqTxStatusCb */      `=($pfnRcTxIrqTxStatusCb eq "") || !$bRcTxCecStatusIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcTxIrqTxStatusCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_rc_tx_cec_config_t `$INSTANCE_NAME`_Config =
{
    /* enSrcClk */                  `=GetNameForEnum("en_rc_src_clk_t", $enSrcClk)`,
    /* u16DivVal */                 `$u16DivVal`u,
    /* u8FreeCycle */               `$u8FreeCycle`u,
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
    /* pstcIrqEn */                 `=$CY_CONST_CONFIG ? "(stc_rc_tx_cec_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */                 `=$CY_CONST_CONFIG ? "(stc_rc_tx_cec_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */                `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_TX */


/* [] END OF FILE */
