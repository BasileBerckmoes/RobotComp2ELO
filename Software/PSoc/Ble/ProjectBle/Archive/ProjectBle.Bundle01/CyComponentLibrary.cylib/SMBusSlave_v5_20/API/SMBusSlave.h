/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  SM/PM Bus Component.
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_SMBusSlave_`$INSTANCE_NAME`_H)
#define CY_SMBusSlave_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "`$INSTANCE_NAME`_`$I2cName`.h"

/*`#START ADDITIONAL_SMBUS_SLAVE_H_INCLUDE`*/

/*`#END`*/


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_MODE                       (`$Mode`u)
#define `$INSTANCE_NAME`_RECEIVE_BYTE_PROTOCOL      (`$EnableRecieveByteProtocol`u)
#define `$INSTANCE_NAME`_SMB_ALERT_PIN_ENABLED      (`$EnableSmbAlertPin`u)
#define `$INSTANCE_NAME`_ENABLE_PEC                 (`$EnablePec`u)

/* AlertReg_Sync_ctrl_reg__REMOVED is defined if SMBALERT# pin is enabled and
* left floating.
*/
#ifndef `$INSTANCE_NAME`_AlertReg_Sync_ctrl_reg__REMOVED
    #define `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS    (`$INSTANCE_NAME`_SMB_ALERT_PIN_ENABLED != 0u)
#else
    #define `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS    (0u != 0u)
#endif /* `$INSTANCE_NAME`_AlertReg_Sync_ctrl_reg__REMOVED */

#define `$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED  (`$INSTANCE_NAME`_RECEIVE_BYTE_PROTOCOL != 0u)
#define `$INSTANCE_NAME`_SUPPORT_PEC                (`$INSTANCE_NAME`_ENABLE_PEC != 0u)

#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_SW_ADDR_DECODE         (`$INSTANCE_NAME`_I2C_CHECK_I2C_ACCEPT_ADDRESS_CONST)
#else
    #define `$INSTANCE_NAME`_SW_ADDR_DECODE         (`$INSTANCE_NAME`_I2C_SW_ADRR_DECODE)
#endif /* CY_PSOC4 */


/***************************************
*     Data Struct Definitions
***************************************/

typedef struct
{
    uint8 read;          /* r/w flag - 1=read 0=write */
    uint8 commandCode;   /* SMBus/PMBus command code */
    uint8 page;          /* PMBus page (if applicable) */
    uint8 length;        /* bytes transferred */
    uint8 payload[65u];  /* payload for the transaction */
} `$INSTANCE_NAME`_TRANSACTION_STRUCT;


/* Define each command based on the inputs from the customizer. */
`$RegsStructElements`


/***************************************
*        Function Prototypes
***************************************/

/* General APIs */
void  `$INSTANCE_NAME`_Init(void)                          `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void  `$INSTANCE_NAME`_Enable(void)                        `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void  `$INSTANCE_NAME`_Start(void)                         `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Stop(void)                          `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;

/* Transaction Specific APIs */
void  `$INSTANCE_NAME`_CompleteTransaction(void)           `=ReentrantKeil($INSTANCE_NAME . "_CompleteTransaction")`;
`$INSTANCE_NAME`_TRANSACTION_STRUCT * `$INSTANCE_NAME`_GetNextTransaction(void)
                                                           `=ReentrantKeil($INSTANCE_NAME . "_GetNextTransaction")`;
/* Protocol Specific APIs */
#if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)
    void  `$INSTANCE_NAME`_HandleSmbAlertResponse(void)    `=ReentrantKeil($INSTANCE_NAME . "_HandleSmbAlertResponse")`;
    #if (CY_PSOC4)
        void `$INSTANCE_NAME`_SetSmbAlert(uint8 state)     `=ReentrantKeil($INSTANCE_NAME . "_SetSmbAlert")`;
    #endif /* CY_PSOC4 */
#endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */

#if (`$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED)
    uint8  `$INSTANCE_NAME`_GetReceiveByteResponse(void)   `=ReentrantKeil($INSTANCE_NAME . "_GetReceiveByteResponse")`;
#endif /* `$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED */

void  `$INSTANCE_NAME`_HandleBusError(uint8 errorCode)     `=ReentrantKeil($INSTANCE_NAME . "_HandleBusError")`;

/* Register Save/Restore APIs */
uint8 `$INSTANCE_NAME`_StoreUserAll(const uint8 * flashRegs)  `=ReentrantKeil($INSTANCE_NAME . "_StoreUserAll")`;
uint8 `$INSTANCE_NAME`_RestoreUserAll(const uint8 * flashRegs)`=ReentrantKeil($INSTANCE_NAME . "_RestoreUserAll")`;
uint8 `$INSTANCE_NAME`_EraseUserAll(void)                     `=ReentrantKeil($INSTANCE_NAME . "_EraseUserAll")`;
uint8 `$INSTANCE_NAME`_RestoreDefaultAll(void)                `=ReentrantKeil($INSTANCE_NAME . "_RestoreDefaultAll")`;
uint8 `$INSTANCE_NAME`_StoreComponentAll(void)                `=ReentrantKeil($INSTANCE_NAME . "_StoreComponentAll")`;
uint8 `$INSTANCE_NAME`_RestoreComponentAll(void)              `=ReentrantKeil($INSTANCE_NAME . "_RestoreComponentAll")`;

/* Unit Conversion Helper APIs */
float32 `$INSTANCE_NAME`_Lin11ToFloat(uint16 linear11)        `=ReentrantKeil($INSTANCE_NAME . "_Lin11ToFloat")`;
uint16  `$INSTANCE_NAME`_FloatToLin11(float32 floatvar)       `=ReentrantKeil($INSTANCE_NAME . "_FloatToLin11")`;
float32 `$INSTANCE_NAME`_Lin16ToFloat(uint16 linear16, int8 inExponent)   
                                                              `=ReentrantKeil($INSTANCE_NAME . "_Lin16ToFloat")`;
uint16  `$INSTANCE_NAME`_FloatToLin16(float32 floatvar, int8 outExponent)
                                                              `=ReentrantKeil($INSTANCE_NAME . "_FloatToLin16")`;

/* Interrupt handlers */
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR);
CY_ISR_PROTO(`$INSTANCE_NAME`_TIMEOUT_ISR);


/***************************************
*   Variables with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;

/* Operating Memory Register Store (RAM) */
extern `$INSTANCE_NAME`_REGS `$INSTANCE_NAME`_regs;

/* Default Memory Register Store (Flash) */
extern const `$INSTANCE_NAME`_REGS CYCODE `$INSTANCE_NAME`_regsDefault;


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_SMBUS_MODE                 (`$INSTANCE_NAME`_MODE == 0u)
#define `$INSTANCE_NAME`_PMBUS_MODE                 (`$INSTANCE_NAME`_MODE != 0u)
#define `$INSTANCE_NAME`_SIGNATURE                  (0x000055AAu)
#define `$INSTANCE_NAME`_REGS_SIZE                  (sizeof(`$INSTANCE_NAME`_REGS))
#define `$INSTANCE_NAME`_ADDR_POS                   (0x01u)
#define `$INSTANCE_NAME`_ADDR_MASK                  (0xFEu)
#define `$INSTANCE_NAME`_READ_FLAG                  (0x01u)

/* Default return value for `$INSTANCE_NAME`_GetReceiveByteResponse() */
#define `$INSTANCE_NAME`_RET_UNDEFINED              (0xFFu)

/* Constants for `$INSTANCE_NAME`_SetSmbAlertMode() */
#if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)   
    #define `$INSTANCE_NAME`_AUTO_MODE              (0x01u)
    #define `$INSTANCE_NAME`_MANUAL_MODE            (0x02u)
    #define `$INSTANCE_NAME`_DO_NOTHING             (0x00u)
#endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */

#define `$INSTANCE_NAME`_NEG_EXP_MIN                (-16)

/* Defines related to CRC calculation */
#define `$INSTANCE_NAME`_CRC_SEED                   (0xFFFFu)
#define `$INSTANCE_NAME`_CRC_BYTE_SHIFT             (0x8u)
#define `$INSTANCE_NAME`_CRC_BYTE_MASK              (0xFFu)

/* Error codes for `$INSTANCE_NAME`_HandleBusError() */
#define `$INSTANCE_NAME`_ERR_READ_FLAG              (0x01u)
#define `$INSTANCE_NAME`_ERR_RD_TOO_MANY_BYTES      (0x02u)
#define `$INSTANCE_NAME`_ERR_WR_TOO_MANY_BYTES      (0x04u)
#define `$INSTANCE_NAME`_ERR_UNSUPPORTED_CMD        (0x08u)
#define `$INSTANCE_NAME`_ERR_INVALID_DATA           (0x10u)
#define `$INSTANCE_NAME`_ERR_TIMEOUT                (0x20u)
#define `$INSTANCE_NAME`_ERR_WR_TOO_FEW_BYTES       (0x40u)
#define `$INSTANCE_NAME`_ERR_CORRUPTED_DATA         (0x80u)

/* Constants dedicated for work with FLASH */
#define `$INSTANCE_NAME`_FLASH_ROW_SIZE             (CYDEV_FLS_ROW_SIZE)
#define `$INSTANCE_NAME`_FLASH_END_ADDR             (CYDEV_FLS_SIZE - 1u)
#define `$INSTANCE_NAME`_FLASH_ROW_MASK             (0x0000FF00u)
#define `$INSTANCE_NAME`_FLASH_ARRYID_MASK          (0x00FF0000u)
#define `$INSTANCE_NAME`_BYTE_SHIFT                 (8u)
#define `$INSTANCE_NAME`_TWO_BYTES_SHIFT            (16u)


/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_NUM_COMMANDS               (`$NumCommands`u)
#define `$INSTANCE_NAME`_MAX_PAGES                  (`$PagedCommandsSize`u)
#define `$INSTANCE_NAME`_SMB_ALERT_MODE_INIT        (`$SmbAlertMode`u)
#define `$INSTANCE_NAME`_DEFAULT_ADDRESS            (`$SlaveAddress`u)
#define `$INSTANCE_NAME`_ALERT_RESPONSE_ADDR        (0x0Cu)
#define `$INSTANCE_NAME`_GENERAL_CALL_ADDR          (0x00u)


/***************************************
*              Registers
***************************************/

#if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)
    #if(CY_PSOC4)
        #define `$INSTANCE_NAME`_SMBALERT_PIN_REG   (* (reg32 *) `$INSTANCE_NAME`_smbalert_pin__DR)
        #define `$INSTANCE_NAME`_SMBALERT_PIN_MASK     (uint32)  `$INSTANCE_NAME`_smbalert_pin__MASK
    #else
        #define `$INSTANCE_NAME`_SMBALERT_PIN_REG   (* (reg8  *) `$INSTANCE_NAME`_AlertReg_Sync_ctrl_reg__CONTROL_REG)
    #endif /* CY_PSOC4 */
#endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */


/***************************************
*              Macros
***************************************/

/* Enables I2C interrupt. Interrupts are required for most operations. */
#define `$INSTANCE_NAME`_EnableInt()                `$INSTANCE_NAME`_I2C_EnableInt()

/* Disables the I2C interrupts. Normally calling this is not required since the
* Stop() function disables the interrupt.
* Side Effects: If the I2C interrupt is disabled and the master is addressing
* the current slave, the bus will be locked until the interrupt is re-enabled.
*/
#define `$INSTANCE_NAME`_DisableInt()               `$INSTANCE_NAME`_I2C_DisableInt()

/* Sets the SM/PM Bus slave address. The address is the 7-bit right-justified
* address for the primary device. Does not include the R/W bit.
*/
#if (`$INSTANCE_NAME`_SW_ADDR_DECODE)
    /* When software address detection is enabled, the address is converted to an 8-bit
    * address with the R/W bit set to 0.
    */
    #define `$INSTANCE_NAME`_SetAddress(address)    \
        (`$INSTANCE_NAME`_address = (uint8)((address) << `$INSTANCE_NAME`_ADDR_POS))
#else
    #if (CY_PSOC4)
        #define `$INSTANCE_NAME`_SetAddress(address)    `$INSTANCE_NAME`_`$I2cName`SlaveSetAddress(address)
    #else
        #define `$INSTANCE_NAME`_SetAddress(address)    `$INSTANCE_NAME`_`$I2cName`_SlaveSetAddress(address)
    #endif /* CY_PSOC4 */
#endif

/* Returns the number of transaction records in the transaction queue */
#define `$INSTANCE_NAME`_GetTransactionCount()      `$INSTANCE_NAME`_trActiveCount

#if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)

    /* Sets the the Alert Response Address (ARA). The address is the 7-bit
    * right-justified address. Does not include the R/W bit.
    * The address is converted to 8-bit address witgh the R/W bit set to 1.
    */
    #define `$INSTANCE_NAME`_SetAlertResponseAddress(address)   (`$INSTANCE_NAME`_alertResponseAddress = \
        (uint8)((address) << `$INSTANCE_NAME`_ADDR_POS) | `$INSTANCE_NAME`_READ_FLAG)
    
    /* Sets the SMBALERT# signal to the specified state. If the device pulled
    * SMBALERT# low, it will acknowledge the ARA with the primary address of 
    * the device. On PSoC 4 this implemented as a function with critical section
    * protection of the read-modify-write to a port data register.
    */
    #if (!CY_PSOC4)
        #define `$INSTANCE_NAME`_SetSmbAlert(state)             (`$INSTANCE_NAME`_SMBALERT_PIN_REG = (state))
    #endif /* CY_PSOC4 */
    
    /* Determines how the component responds to a SMBus master read at the ARA.
    *  alertMode (uint8): A byte that defines SMBALERT pin mode.
    *   `$INSTANCE_NAME`_DO_NOTHING (0x00u) - no action will be taken
    *   `$INSTANCE_NAME`_AUTO_MODE  (0x01u) - SMBALERT# pin will be 
    *   de-asserted once the device responds to the ARA.
    *   `$INSTANCE_NAME`_MANUAL_MODE (0x02u) - the HandleSmbAlertResponse()
    *   API will be called allowing the user to implement its own algorithm
    *   in the custom user code section.
    */
    #define `$INSTANCE_NAME`_SetSmbAlertMode(alertMode)         (`$INSTANCE_NAME`_smbAlertMode = (alertMode))

#endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */

/* Converts the Flash address to Flash row */
#define `$INSTANCE_NAME`_FL_ADDR_TO_ROW(addr) \
    ((uint8)(((addr) & `$INSTANCE_NAME`_FLASH_ROW_MASK) >> `$INSTANCE_NAME`_BYTE_SHIFT))

/* Converts Flash row to Flash Array ID */
#define `$INSTANCE_NAME`_FL_ADDR_TO_ARRAYID(addr) \
    ((uint8)(((addr) & `$INSTANCE_NAME`_FLASH_ARRYID_MASK) >> `$INSTANCE_NAME`_TWO_BYTES_SHIFT))

#define `$INSTANCE_NAME`_SIZE_TO_ROW(size)  ((uint8)((size) >> `$INSTANCE_NAME`_BYTE_SHIFT) + 1u)

#define `$INSTANCE_NAME`_MAKE_FLASH_ADDR(arrayId, row) \
    (((uint32)(arrayId) << `$INSTANCE_NAME`_TWO_BYTES_SHIFT) | ((uint32)(row) << `$INSTANCE_NAME`_BYTE_SHIFT))

#endif /* CY_SMBusSlave_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
