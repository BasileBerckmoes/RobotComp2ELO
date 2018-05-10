/*******************************************************************************
* \file `$INSTANCE_NAME`_config.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable declarations for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_CONFIG_H
#define `$INSTANCE_NAME`_CONFIG_H

#include "rc/rc.h"
#include "cyfitter.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_RC_UNCONFIGURED    0u
#define `$INSTANCE_NAME`_RC_SIRCS           1u
#define `$INSTANCE_NAME`_RC_NEC             2u
#define `$INSTANCE_NAME`_RC_CEC_RX          3u
#define `$INSTANCE_NAME`_RC_CEC_TX          4u
#define `$INSTANCE_NAME`_RC_CONFIG          `$RCConfig`u

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_rc_RC_HW

/* SetPinFunc macro */
#define `$INSTANCE_NAME`_SetPinFunc_CEC    CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_rc__`$INSTANCE_NAME`_CEC

/*******************************************************************************
*                      RC Common Receiver Config Definitions
*******************************************************************************/

#if ((`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_UNCONFIGURED) || \
     (`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_CEC_TX))

/* Remoter control receiver address structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_addr_t `$INSTANCE_NAME`_RxAddr;

#endif /* ((`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_UNCONFIGURED) || \
           (`$INSTANCE_NAME`_RC_CONFIG != `$INSTANCE_NAME`_RC_CEC_TX)) */

    
/*******************************************************************************
*                     SIRCS Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_SIRCS)
    
/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_sircs_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_sircs_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_sircs_config_t `$INSTANCE_NAME`_Config;

/* Start interrupt callback function */
`=($pfnRcRxSircsStartIrqCb eq "") || !$bRcRxSircsStartIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxSircsStartIrqCb . "(void);"`

/* ACK interrupt callback function */
`=($pfnRcRxSircsAckIrqCb eq "") || !$bRcRxSircsAckIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxSircsAckIrqCb . "(void);"`

/* Counter overflow interrupt callback function */
`=($pfnRcRxSircsCntOvfIrqCb eq "") || !$bRcRxSircsCntOvfIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxSircsCntOvfIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_SIRCS */


/*******************************************************************************
*                      NEC Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_NEC)

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_nec_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_nec_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_nec_config_t `$INSTANCE_NAME`_Config;

/* Start interrupt callback function */
`=($pfnRcRxNecStartIrqCb eq "") || !$bRcRxNecStartIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxNecStartIrqCb . "(void);"`

/* ACK interrupt callback function */
`=($pfnRcRxNecAckIrqCb eq "") || !$bRcRxNecAckIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxNecAckIrqCb . "(void);"`

/* Counter overflow interrupt callback function */
`=($pfnRcRxNecCntOvfIrqCb eq "") || !$bRcRxNecCntOvfIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxNecCntOvfIrqCb . "(void);"`

/* Repeat code interrupt callback function */
`=($pfnRcRxNecRepeatCodeIrqCb eq "") || !$bRcRxNecRepeatCodeIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxNecRepeatCodeIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_NEC */


/*******************************************************************************
*                      CEC Rx Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_RX)

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_cec_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_cec_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_rx_cec_config_t `$INSTANCE_NAME`_Config;

/* Start interrupt callback function */
`=($pfnRcRxCecStartIrqCb eq "") || !$bRcRxCecStartIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxCecStartIrqCb . "(void);"`

/* ACK interrupt callback function */
`=($pfnRcRxCecAckIrqCb eq "") || !$bRcRxCecAckIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxCecAckIrqCb . "(void);"`

/* Counter overflow interrupt callback function */
`=($pfnRcRxCecCntOvfIrqCb eq "") || !$bRcRxCecCntOvfIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxCecCntOvfIrqCb . "(void);"`

/* Minimum data interrupt callback function */
`=($pfnRcRxCecMinDataIrqCb eq "") || !$bRcRxCecMinDataIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxCecMinDataIrqCb . "(void);"`

/* Maximum data interrupt callback function */
`=($pfnRcRxCecMaxDataIrqCb eq "") || !$bRcRxCecMaxDataIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcRxCecMaxDataIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_RX */


/*******************************************************************************
*                      CEC Tx Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_TX)

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_tx_cec_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_tx_cec_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_rc_tx_cec_config_t `$INSTANCE_NAME`_Config;

/* Bus error interrupt callback function */
`=($pfnRcTxIrqBusErrorCb eq "") || !$bRcTxCecBusErrorIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcTxIrqBusErrorCb . "(void);"`

/* Transfer status interrupt callback function */
`=($pfnRcTxIrqTxStatusCb eq "") || !$bRcTxCecStatusIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcTxIrqTxStatusCb . "(void);"`

#endif /* `$INSTANCE_NAME`_RC_CONFIG == `$INSTANCE_NAME`_RC_CEC_TX */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_Config_H */

/* [] END OF FILE */
