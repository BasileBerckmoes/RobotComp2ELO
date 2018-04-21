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
*                      MFS Common Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG != `$INSTANCE_NAME`_MFS_UNCONFIGURED)

/* FIFO configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_fifo_config_t `$INSTANCE_NAME`_FifoConfig =
{
    /* enFifoSel */             `=GetNameForEnum("en_mfs_fifo_sel_t", $enFifoSel)`,
    /* u8ByteCount1 */          `$u8ByteCount1`u,
    /* u8ByteCount2 */          `$u8ByteCount2`u
};

#endif /* `$INSTANCE_NAME`_MFS_CONFIG != `$INSTANCE_NAME`_MFS_UNCONFIGURED */


/*******************************************************************************
*                      UART Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_UART)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_uart_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bTxIrq */                `=$bTxIrq ? "TRUE" : "FALSE"`,
    /* bRxIrq */                `=$bRxIrq ? "TRUE" : "FALSE"`,
    /* bTxIdleIrq */            `=$bTxIdleIrq ? "TRUE" : "FALSE"`,
    /* bTxFifoIrq */            `=$bTxFifoIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_uart_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnTxIrqCb */            `=($pfnTxIrqCb eq "") || !$bTxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIrqCb`, /* User-supplied callback function */
    /* pfnRxIrqCb */            `=($pfnRxIrqCb eq "") || !$bRxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRxIrqCb`, /* User-supplied callback function */
    /* pfnTxIdleIrqCb */        `=($pfnTxIdleIrqCb eq "") || !$bTxIdleIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIdleIrqCb`, /* User-supplied callback function */
    /* pfnTxFifoIrqCb */        `=($pfnTxFifoIrqCb eq "") || !$bTxFifoIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxFifoIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_uart_config_t `$INSTANCE_NAME`_Config =
{
    /* enMode */                `=GetNameForEnum("en_uart_mode_t", $enMode)`,
    /* u32BaudRate */           `$u32UartBaudRate`u,
    /* enParity */              `=GetNameForEnum("en_uart_parity_t", $enParity)`,
    /* enStopBit */             `=GetNameForEnum("en_uart_stop_bit_t", $enStopBit)`,
    /* enDataLength */          `=GetNameForEnum("en_uart_data_len_t", $enUartDataLength)`,
    /* enBitDirection */        `=GetNameForEnum("en_uart_data_dir_t", $enUartBitDirection)`,
    /* bInvertData */           `=$bInvertData ? "TRUE" : "FALSE"`,
    /* bHwFlow */               `=$bHwFlow ? "TRUE" : "FALSE"`,
    /* bUseExtClk */            `=$bUseExtClk ? "TRUE" : "FALSE"`,
    /* pstcFifoConfig */        `=$CY_CONST_CONFIG ? "(stc_mfs_fifo_config_t *)" : ""`&`$INSTANCE_NAME`_FifoConfig,
#if (PDL_INTERRUPT_ENABLE_MFS0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS8  == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS1 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS9  == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS2 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS10 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS3 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS11 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS4 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS12 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS5 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS13 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS6 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS14 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS7 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS15 == PDL_ON)
    /* pstcIrqEn */             `=$CY_CONST_CONFIG ? "(stc_uart_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */             `=$CY_CONST_CONFIG ? "(stc_uart_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_UART */


/*******************************************************************************
*                      I2C Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_I2C)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_i2c_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bTxIrq */                `=$bTxIrq ? "TRUE" : "FALSE"`,
    /* bRxIrq */                `=$bRxIrq ? "TRUE" : "FALSE"`,
    /* bTxIdleIrq */            `=$bTxIdleIrq ? "TRUE" : "FALSE"`,
    /* bTxFifoIrq */            `=$bTxFifoIrq ? "TRUE" : "FALSE"`,
    /* bTxRxIrq */              `=$bTxRxIrq ? "TRUE" : "FALSE"`,
    /* bStopDetectIrq */        `=$bStopDetectIrq ? "TRUE" : "FALSE"`
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_i2c_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnTxIrqCb */            `=($pfnTxIrqCb eq "") || !$bTxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIrqCb`, /* User-supplied callback function */
    /* pfnRxIrqCb */            `=($pfnRxIrqCb eq "") || !$bRxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRxIrqCb`, /* User-supplied callback function */
    /* pfnTxIdleIrqCb */        `=($pfnTxIdleIrqCb eq "") || !$bTxIdleIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIdleIrqCb`, /* User-supplied callback function */
    /* pfnTxFifoIrqCb */        `=($pfnTxFifoIrqCb eq "") || !$bTxFifoIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxFifoIrqCb`, /* User-supplied callback function */
    /* pfnTxRxIrqCb */          `=($pfnTxRxIrqCb eq "") || !$bTxRxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxRxIrqCb`, /* User-supplied callback function */
    /* pfnStopDetectIrqCb */    `=($pfnStopDetectIrqCb eq "") || !$bStopDetectIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnStopDetectIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_i2c_config_t `$INSTANCE_NAME`_Config =
{
    /* enMsMode */              `=GetNameForEnum("en_i2c_mode_t", $enI2cMsMode)`,
    /* u32BaudRate */           `$u32I2cBaudRate`u,
    /* u8SlaveAddr */           `$u8SlaveAddress`u,
    /* u8SlaveMaskAddr */       `$u8SlaveMaskAddr`u,
    /* bWaitSelection */        `=$bWaitSelection ? "TRUE" : "FALSE"`,
    /* bDmaEnable */            `=$bDmaEnable ? "TRUE" : "FALSE"`,
    /* pstcFifoConfig */        `=$CY_CONST_CONFIG ? "(stc_mfs_fifo_config_t *)" : ""`&`$INSTANCE_NAME`_FifoConfig,
#if (PDL_INTERRUPT_ENABLE_MFS0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS8  == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS1 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS9  == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS2 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS10 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS3 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS11 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS4 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS12 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS5 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS13 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS6 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS14 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS7 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS15 == PDL_ON)   
    /* pstcIrqEn */             `=$CY_CONST_CONFIG ? "(stc_i2c_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */             `=$CY_CONST_CONFIG ? "(stc_i2c_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_I2C */


/*******************************************************************************
*                      CSIO Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_CSIO)

/* Serial timer configuration */
`=$CY_CONST_CONFIG ? "const " : ""`stc_csio_serial_timer_t `$INSTANCE_NAME`_SerialTimer =
{
    /* enClkDiv */              `=GetNameForEnum("en_csio_timer_clk_t", $enStClkDiv)`,
    /* u8TransferByteCnt */     `$u8TransferByteCnt`u,
    /* u16CompareVal */         `$u16CompareVal`u
};

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_csio_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bTxIrq */                `=$bTxIrq ? "TRUE" : "FALSE"`,
    /* bRxIrq */                `=$bRxIrq ? "TRUE" : "FALSE"`,
    /* bTxIdleIrq */            `=$bTxIdleIrq ? "TRUE" : "FALSE"`,
    /* bTxFifoIrq */            `=$bTxFifoIrq ? "TRUE" : "FALSE"`,
#if (PDL_MCU_CORE == PDL_FM4_CORE) || (PDL_MCU_CORE == PDL_FM0P_CORE)
    /* bCsErrIrq */             `=$bCsErrIrq ? "TRUE" : "FALSE"`,
    /* bSerialTimerIrq */       `=$bSerialTimerIrq ? "TRUE" : "FALSE"`
#endif
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_csio_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnTxIrqCb */            `=($pfnTxIrqCb eq "") || !$bTxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIrqCb`, /* User-supplied callback function */
    /* pfnRxIrqCb */            `=($pfnRxIrqCb eq "") || !$bRxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRxIrqCb`, /* User-supplied callback function */
    /* pfnTxIdleIrqCb */        `=($pfnTxIdleIrqCb eq "") || !$bTxIdleIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIdleIrqCb`, /* User-supplied callback function */
    /* pfnTxFifoIrqCb */        `=($pfnTxFifoIrqCb eq "") || !$bTxFifoIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxFifoIrqCb`, /* User-supplied callback function */
#if (PDL_MCU_CORE == PDL_FM4_CORE) || (PDL_MCU_CORE == PDL_FM0P_CORE)    
    /* pfnCsErrIrqCb */         `=($pfnCsErrIrqCb eq "") || !$bCsErrIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnCsErrIrqCb`, /* User-supplied callback function */
    /* pfnSerialTimerIrqCb */   `=($pfnSerialTimerIrqCb eq "") || !$bSerialTimerIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnSerialTimerIrqCb` /* User-supplied callback function */
#endif 
};

/* Chip selection configuration */
`=$CY_CONST_CONFIG ? "const " : ""`stc_csio_cs_t `$INSTANCE_NAME`_CsConfig =
{
    /* enCsStartPin */          `=GetNameForEnum("en_cs_pin_sel_t", $enCsStartPin)`,
    /* enCsEndPin */            `=GetNameForEnum("en_cs_pin_sel_t", $enCsEndPin)`,
    /* enLevel */               `=GetNameForEnum("en_cs_pin_level_t", $enLevel)`,
    /* bActiveHold */           `=$bActiveHold ? "TRUE" : "FALSE"`,
    /* enCsClkDiv */            `=GetNameForEnum("en_cs_timing_clk_t", $enCsClkDiv)`,
    /* u8CsSetupDelayTime */    `$u8CsSetupDelayTime`u,
    /* u8CsHoldDelayTime */     `$u8CsHoldDelayTime`u,
    /* u16CsDeselectTime */     `$u16CsDeselectTime`u,
    /* u8Scs0TransferByteCnt */ `$u8Scs0TransferByteCnt`u,
    /* u8Scs1TransferByteCnt */ `$u8Scs1TransferByteCnt`u,
    /* u8Scs2TransferByteCnt */ `$u8Scs2TransferByteCnt`u,
    /* u8Scs3TransferByteCnt */ `$u8Scs3TransferByteCnt`u,
    /* bScs0En */               `=$bScs0En ? "TRUE" : "FALSE"`,
    /* bScs1En */               `=$bScs1En ? "TRUE" : "FALSE"`,
    /* bScs2En */               `=$bScs2En ? "TRUE" : "FALSE"`,
    /* bScs3En */               `=$bScs3En ? "TRUE" : "FALSE"`, 
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_csio_config_t `$INSTANCE_NAME`_Config =
{
    /* enMsMode */              `=GetNameForEnum("en_csio_ms_mode_t", $enCsioMsMode)`,
    /* u32BaudRate */           `$u32CsioBaudRate`u,
    /* enActMode */             `=GetNameForEnum("en_csio_act_mode_t", $enActMode)`,
    /* enSyncWaitTime */        `=GetNameForEnum("en_csio_sync_wait_time_t", $enSyncWaitTime)`,
    /* enDataLength */          `=GetNameForEnum("en_csio_data_len_t", $enCsioDataLength)`,
    /* enBitDirection */        `=GetNameForEnum("en_csio_data_dir_t", $enCsioBitDirection)`,
    /* bInvertClk */            `=$bInvertClk ? "TRUE" : "FALSE"`,
#if (PDL_MCU_CORE == PDL_FM0P_CORE) || (PDL_MCU_CORE == PDL_FM4_CORE)    
    /* pstcSerialTimer */       `=$CY_CONST_CONFIG ? "(stc_csio_serial_timer_t *)" : ""`&`$INSTANCE_NAME`_SerialTimer,
    /* pstcCsConfig */          `=$CY_CONST_CONFIG ? "(stc_csio_cs_t *)" : ""`&`$INSTANCE_NAME`_CsConfig,
#endif
    /* pstcFifoConfig */        `=$CY_CONST_CONFIG ? "(stc_mfs_fifo_config_t *)" : ""`&`$INSTANCE_NAME`_FifoConfig,
#if (PDL_INTERRUPT_ENABLE_MFS0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS8 == PDL_ON)  || \
    (PDL_INTERRUPT_ENABLE_MFS1 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS9 == PDL_ON)  || \
    (PDL_INTERRUPT_ENABLE_MFS2 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS10 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS3 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS11 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS4 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS12 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS5 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS13 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS6 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS14 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS7 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS15 == PDL_ON)   
    /* pstcIrqEn */             `=$CY_CONST_CONFIG ? "(stc_csio_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */             `=$CY_CONST_CONFIG ? "(stc_csio_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_CSIO */


/*******************************************************************************
*                      LIN Config Definitions
*******************************************************************************/

#if (`$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_LIN)

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_lin_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bTxIrq */                `=$bTxIrq ? "TRUE" : "FALSE"`,
    /* bRxIrq */                `=$bRxIrq ? "TRUE" : "FALSE"`,
    /* bLinBreakIrq */          `=$bLinBreakIrq ? "TRUE" : "FALSE"`,
    /* bTxIdleIrq */            `=$bTxIdleIrq ? "TRUE" : "FALSE"`,
    /* bTxFifoIrq */            `=$bTxFifoIrq ? "TRUE" : "FALSE"`,
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const " : ""`stc_lin_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnTxIrqCb */            `=($pfnTxIrqCb eq "") || !$bTxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIrqCb`, /* User-supplied callback function */
    /* pfnRxIrqCb */            `=($pfnRxIrqCb eq "") || !$bRxIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRxIrqCb`, /* User-supplied callback function */
    /* pfnLinBreakIrqCb */      `=($pfnLinBreakIrqCb eq "") || !$bLinBreakIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnLinBreakIrqCb`,
    /* pfnTxIdleIrqCb */        `=($pfnTxIdleIrqCb eq "") || !$bTxIdleIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxIdleIrqCb`, /* User-supplied callback function */
    /* pfnTxFifoIrqCb */        `=($pfnTxFifoIrqCb eq "") || !$bTxFifoIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnTxFifoIrqCb` /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_mfs_lin_config_t `$INSTANCE_NAME`_Config =
{
    /* enMsMode */              `=GetNameForEnum("en_lin_ms_mode_t", $enLinMsMode)`,
    /* u32BaudRate */           `$u32LinBaudRate`u,
    /* enStopBits */            `=GetNameForEnum("en_lin_stop_bit_t", $enStopBits)`,
    /* enBreakLength */         `=GetNameForEnum("en_lin_break_len_t", $enBreakLength)`,
    /* enDelimiterLength */     `=GetNameForEnum("en_lin_delimiter_len_t", $enDelimiterLength)`,
    /* bUseExtClk */            `=$bUseExtClk ? "TRUE" : "FALSE"`,
    /* pstcFifoConfig */        `=$CY_CONST_CONFIG ? "(stc_mfs_fifo_config_t *)" : ""`&`$INSTANCE_NAME`_FifoConfig,
#if (PDL_INTERRUPT_ENABLE_MFS0 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS8  == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS1 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS9  == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS2 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS10 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS3 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS11 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS4 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS12 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS5 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS13 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS6 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS14 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_MFS7 == PDL_ON) || (PDL_INTERRUPT_ENABLE_MFS15 == PDL_ON)   
    /* pstcIrqEn */             `=$CY_CONST_CONFIG ? "(stc_lin_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */             `=$CY_CONST_CONFIG ? "(stc_lin_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif
};

#endif /* `$INSTANCE_NAME`_MFS_CONFIG == `$INSTANCE_NAME`_MFS_LIN */
    
/* [] END OF FILE */
