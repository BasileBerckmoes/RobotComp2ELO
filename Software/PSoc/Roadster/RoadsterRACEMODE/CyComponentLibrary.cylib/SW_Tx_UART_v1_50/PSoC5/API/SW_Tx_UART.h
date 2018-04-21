/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_`$INSTANCE_NAME`_H
#define CY_SW_TX_UART_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define `$INSTANCE_NAME`_BAUD_RATE                      (`$BaudRate`u)
#define `$INSTANCE_NAME`_PIN_STATIC_MODE                (`$PinAssignmentMethod`u)


/***************************************
*        Function Prototypes
***************************************/
#if(`$INSTANCE_NAME`_PIN_STATIC_MODE == 1u)
    void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil("`$INSTANCE_NAME`_Start")`;
#else
    void `$INSTANCE_NAME`_StartEx(uint8 port, uint8 pin) `=ReentrantKeil("`$INSTANCE_NAME`_StartEx")`;
#endif /* (`$INSTANCE_NAME`_PIN_STATIC_MODE == 1u) */

void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil("`$INSTANCE_NAME`_Stop")`;
void `$INSTANCE_NAME`_PutChar(uint8 txDataByte) `=ReentrantKeil("`$INSTANCE_NAME`_PutChar")`;
void `$INSTANCE_NAME`_PutString(const char8 string[]) `=ReentrantKeil("`$INSTANCE_NAME`_PutString")`;
void `$INSTANCE_NAME`_PutArray(const uint8 array[], uint32 byteCount) `=ReentrantKeil("`$INSTANCE_NAME`_PutArray")`;
void `$INSTANCE_NAME`_PutHexByte(uint8 txHexByte) `=ReentrantKeil("`$INSTANCE_NAME`_PutHexByte")`;
void `$INSTANCE_NAME`_PutHexInt(uint16 txHexInt) `=ReentrantKeil("`$INSTANCE_NAME`_PutHexInt")`;
void `$INSTANCE_NAME`_PutCRLF(void) `=ReentrantKeil("`$INSTANCE_NAME`_PutCRLF")`;

#endif /* CY_SW_TX_UART_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
