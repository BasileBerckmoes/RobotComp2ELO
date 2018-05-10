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

#include "qprc/qprc.h"
#include "cyfitter.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_qprc__HW
#define `$INSTANCE_NAME`_Idx    `$INSTANCE_NAME`_fm_qprc__HW_IDX
#define `$INSTANCE_NAME`_SetPinFunc_AIN     CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_qprc__`$INSTANCE_NAME`_AIN
#define `$INSTANCE_NAME`_SetPinFunc_BIN     CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_qprc__`$INSTANCE_NAME`_BIN
#define `$INSTANCE_NAME`_SetPinFunc_ZIN     CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_qprc__`$INSTANCE_NAME`_ZIN

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_qprc_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback functions structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_qprc_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_qprc_config_t `$INSTANCE_NAME`_Config;

/* Overflow, underflow, zero match interrupt callback function of position counter */
`=($pfnPcOfUfZeroIrqCb eq "") || !$bQprcPcOfUfZeroIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPcOfUfZeroIrqCb . "(uint8_t u8Argument);"`

/* PC match interrupt callback function of position counter */
`=($pfnPcMatchIrqCb eq "") || !$bQprcPcMatchIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPcMatchIrqCb . "(void);"`

/* PC and RC match interrupt callback function */
`=($pfnPcRcMatchIrqCb eq "") || !$bQprcPcRcMatchIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPcRcMatchIrqCb . "(void);"`

/* PC match and RC match interrupt callback function */
`=($pfnPcMatchRcMatchIrqCb eq "") || !$bQprcPcMatchRcMatchIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPcMatchRcMatchIrqCb . "(void);"`

/* PC invert interrupt callback function */
`=($pfnPcCountInvertIrqCb eq "") || !$bQprcPcCountInvertIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPcCountInvertIrqCb . "(void);"`

/* RC outrange interrupt callback function */
`=($pfnRcOutrangeIrqCb eq "") || !$bQprcRcOutrangeIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRcOutrangeIrqCb . "(void);"`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
