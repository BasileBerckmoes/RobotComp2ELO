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

#include "mfs/mfs.h"
#include "cyfitter.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_MFS_UNCONFIGURED    0u
#define `$INSTANCE_NAME`_MFS_UART            1u
#define `$INSTANCE_NAME`_MFS_I2C             2u
#define `$INSTANCE_NAME`_MFS_CSIO            3u
#define `$INSTANCE_NAME`_MFS_LIN             4u
#define `$INSTANCE_NAME`_MFS_CONFIG          `$MFSConfig`u


/*******************************************************************************
*                      MFS Common Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG != `$INSTANCE_NAME`_MFS_UNCONFIGURED)

/* FIFO configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_fifo_config_t `$INSTANCE_NAME`_FifoConfig;

/* TX interrupt callback function */
`=($pfnTxIrqCb eq "") || !$bTxIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnTxIrqCb . "(void);"`

/* RX interrupt callback function */
`=($pfnRxIrqCb eq "") || !$bRxIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRxIrqCb . "(void);"`

/* TX idle interrupt callback function */
`=($pfnTxIdleIrqCb eq "") || !$bTxIdleIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnTxIdleIrqCb . "(void);"`

/* TX FIFO interrupt callback function */
`=($pfnTxFifoIrqCb eq "") || !$bTxFifoIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnTxFifoIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_MFS_CONFIG != `$INSTANCE_NAME`_MFS_UNCONFIGURED */

    
/*******************************************************************************
*                      UART Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_UART)

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_mfs_UART_HW

/* Pin function macros */
#define `$INSTANCE_NAME`_SetPinFunc_SIN() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SIN()
#define `$INSTANCE_NAME`_SetPinFunc_SOT() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SOT()
#ifdef CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_CTS
#define `$INSTANCE_NAME`_SetPinFunc_CTS() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_CTS()
#define `$INSTANCE_NAME`_SetPinFunc_RTS() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_RTS()
#endif /* CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_CTS */

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_uart_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_uart_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_uart_config_t `$INSTANCE_NAME`_Config;

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_UART */


/*******************************************************************************
*                      I2C Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_I2C)

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_mfs_I2C_HW

/* Pin function macros */
#define `$INSTANCE_NAME`_SetPinFunc_SCL() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SCK()
#define `$INSTANCE_NAME`_SetPinFunc_SDA() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SOT()

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_i2c_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_i2c_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_i2c_config_t `$INSTANCE_NAME`_Config;

/* TX and RX completion interrupt callback function */
`=($pfnTxRxIrqCb eq "") || !$bTxRxIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnTxRxIrqCb . "(void);"`

/* Stop condition interrupt callback function */
`=($pfnStopDetectIrqCb eq "") || !$bStopDetectIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnStopDetectIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_I2C */


/*******************************************************************************
*                      CSIO Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_CSIO)

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_mfs_CSIO_HW

/* Pin function macros */
#define `$INSTANCE_NAME`_SetPinFunc_SIN()  CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SIN()
#define `$INSTANCE_NAME`_SetPinFunc_SOT()  CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SOT()
#define `$INSTANCE_NAME`_SetPinFunc_SCK()  CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SCK()
`=$bScs0En ? "#define `$INSTANCE_NAME`_SetPinFunc_SCS0() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SCS0()" : "/* SCS0 unused */"`
`=$bScs1En ? "#define `$INSTANCE_NAME`_SetPinFunc_SCS1() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SCS1()" : "/* SCS1 unused */"`
`=$bScs2En ? "#define `$INSTANCE_NAME`_SetPinFunc_SCS2() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SCS2()" : "/* SCS2 unused */"`

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_csio_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_csio_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Chip selection configuration*/
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_csio_cs_t `$INSTANCE_NAME`_CsConfig;

/* Serial timer configuration */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_csio_serial_timer_t `$INSTANCE_NAME`_SerialTimer;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_csio_config_t `$INSTANCE_NAME`_Config;

/* Chip selection interrupt callback function */
`=($pfnCsErrIrqCb eq "") || !$bCsErrIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnCsErrIrqCb . "(void);"`

/* Serial timer interrupt callback function */
`=($pfnSerialTimerIrqCb eq "") || !$bSerialTimerIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnSerialTimerIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_CSIO */


/*******************************************************************************
*                      LIN Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_LIN)

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_mfs_LIN_HW

/* Pin function macros */
#define `$INSTANCE_NAME`_SetPinFunc_SIN() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SIN()
#define `$INSTANCE_NAME`_SetPinFunc_SOT() CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_mfs__`$INSTANCE_NAME`_SOT()

/* Interrupt enable structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_lin_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_lin_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_lin_config_t `$INSTANCE_NAME`_Config;

/* Chip selection interrupt callback function */
`=($pfnLinBreakIrqCb eq "") || !$bLinBreakIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnLinBreakIrqCb . "(void);"`

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_LIN */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_Config_H */

/* [] END OF FILE */
