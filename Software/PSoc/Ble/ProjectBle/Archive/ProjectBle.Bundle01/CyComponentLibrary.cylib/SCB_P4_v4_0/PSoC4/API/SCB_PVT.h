/***************************************************************************//**
* \file `$INSTANCE_NAME_PVT`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_`$INSTANCE_NAME`_H)
#define CY_SCB_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(interruptMask) `$INSTANCE_NAME`_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(interruptMask) `$INSTANCE_NAME`_CLEAR_INTR_I2C_EC(interruptMask)
#define `$INSTANCE_NAME`_GetI2CExtClkInterruptSource()                (`$INSTANCE_NAME`_INTR_I2C_EC_REG)
#define `$INSTANCE_NAME`_GetI2CExtClkInterruptMode()                  (`$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG)
#define `$INSTANCE_NAME`_GetI2CExtClkInterruptSourceMasked()          (`$INSTANCE_NAME`_INTR_I2C_EC_MASKED_REG)

#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define `$INSTANCE_NAME`_SetSpiExtClkInterruptMode(interruptMask) \
                                                                `$INSTANCE_NAME`_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                `$INSTANCE_NAME`_CLEAR_INTR_SPI_EC(interruptMask)
    #define `$INSTANCE_NAME`_GetExtSpiClkInterruptSource()                 (`$INSTANCE_NAME`_INTR_SPI_EC_REG)
    #define `$INSTANCE_NAME`_GetExtSpiClkInterruptMode()                   (`$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG)
    #define `$INSTANCE_NAME`_GetExtSpiClkInterruptSourceMasked()           (`$INSTANCE_NAME`_INTR_SPI_EC_MASKED_REG)
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void `$INSTANCE_NAME`_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER)
    extern cyisraddress `$INSTANCE_NAME`_customIntrHandler;
#endif /* !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER) */
#endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */

extern `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup;

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 `$INSTANCE_NAME`_scbMode;
    extern uint8 `$INSTANCE_NAME`_scbEnableWake;
    extern uint8 `$INSTANCE_NAME`_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 `$INSTANCE_NAME`_mode;
    extern uint8 `$INSTANCE_NAME`_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * `$INSTANCE_NAME`_rxBuffer;
    extern uint8   `$INSTANCE_NAME`_rxDataBits;
    extern uint32  `$INSTANCE_NAME`_rxBufferSize;

    extern volatile uint8 * `$INSTANCE_NAME`_txBuffer;
    extern uint8   `$INSTANCE_NAME`_txDataBits;
    extern uint32  `$INSTANCE_NAME`_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 `$INSTANCE_NAME`_numberOfAddr;
    extern uint8 `$INSTANCE_NAME`_subAddrSize;
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG || \
        `$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 `$INSTANCE_NAME`_IntrTxMask;
#endif /* (! (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG || \
              `$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define `$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG     (`$INSTANCE_NAME`_SCB_MODE_I2C      == `$INSTANCE_NAME`_scbMode)
    #define `$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG     (`$INSTANCE_NAME`_SCB_MODE_SPI      == `$INSTANCE_NAME`_scbMode)
    #define `$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG    (`$INSTANCE_NAME`_SCB_MODE_UART     == `$INSTANCE_NAME`_scbMode)
    #define `$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG   (`$INSTANCE_NAME`_SCB_MODE_EZI2C    == `$INSTANCE_NAME`_scbMode)
    #define `$INSTANCE_NAME`_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG == `$INSTANCE_NAME`_scbMode)

    /* Defines wakeup enable */
    #define `$INSTANCE_NAME`_SCB_WAKE_ENABLE_CHECK       (0u != `$INSTANCE_NAME`_scbEnableWake)
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    #define `$INSTANCE_NAME`_SCB_PINS_NUMBER    (7u)
#else
    #define `$INSTANCE_NAME`_SCB_PINS_NUMBER    (2u)
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
