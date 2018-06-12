/***************************************************************************//**
* \file `$INSTANCE_NAME_EZI2C_PVT`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in _EZI2C mode.
*  Do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_EZI2C_PVT_`$INSTANCE_NAME`_H)
#define CY_SCB_EZI2C_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_EZI2C.h"


/***************************************
*      EZI2C Private Vars
***************************************/

extern volatile uint8 `$INSTANCE_NAME`_curStatus;
extern uint8 `$INSTANCE_NAME`_fsmState;

/* Variables intended to be used with Buffer 1: Primary slave address */
extern volatile uint8 * `$INSTANCE_NAME`_dataBuffer1;
extern uint16 `$INSTANCE_NAME`_bufSizeBuf1;
extern uint16 `$INSTANCE_NAME`_protectBuf1;
extern `$EzI2cBitWidthReplacementString` `$INSTANCE_NAME`_offsetBuf1;
extern uint16 `$INSTANCE_NAME`_indexBuf1;

#if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
    extern uint8 `$INSTANCE_NAME`_addrBuf1;
    extern uint8 `$INSTANCE_NAME`_addrBuf2;

    /* Variables intended to be used with Buffer 2: Primary slave address */
    extern volatile uint8 * `$INSTANCE_NAME`_dataBuffer2;
    extern uint16 `$INSTANCE_NAME`_bufSizeBuf2;
    extern uint16 `$INSTANCE_NAME`_protectBuf2;
    extern `$EzI2cBitWidthReplacementString` `$INSTANCE_NAME`_offsetBuf2;
    extern uint16 `$INSTANCE_NAME`_indexBuf2;
#endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
    void `$INSTANCE_NAME`_EzI2CInit(void);
#endif /* (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG) */

void `$INSTANCE_NAME`_EzI2CStop(void);
#if(`$INSTANCE_NAME`_EZI2C_WAKE_ENABLE_CONST)
    void `$INSTANCE_NAME`_EzI2CSaveConfig(void);
    void `$INSTANCE_NAME`_EzI2CRestoreConfig(void);
#endif /* (`$INSTANCE_NAME`_EZI2C_WAKE_ENABLE_CONST) */

#endif /* (CY_SCB__EZI2C_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
