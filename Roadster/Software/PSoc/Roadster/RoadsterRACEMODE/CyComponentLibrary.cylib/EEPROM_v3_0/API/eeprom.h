/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   Provides the function definitions for the EEPROM APIs.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EEPROM_`$INSTANCE_NAME`_H)
#define CY_EEPROM_`$INSTANCE_NAME`_H

#include "cydevice_trm.h"
#include "CyFlash.h"

#if !defined(CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop (void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
cystatus `$INSTANCE_NAME`_WriteByte(uint8 dataByte, uint16 address) \
                                            `=ReentrantKeil($INSTANCE_NAME . "_WriteByte")`;
uint8 `$INSTANCE_NAME`_ReadByte(uint16 address) `=ReentrantKeil($INSTANCE_NAME . "_ReadByte")`;
uint8 `$INSTANCE_NAME`_UpdateTemperature(void) `=ReentrantKeil($INSTANCE_NAME . "_UpdateTemperature")`;
cystatus `$INSTANCE_NAME`_EraseSector(uint8 sectorNumber) `=ReentrantKeil($INSTANCE_NAME . "_EraseSector")`;
cystatus `$INSTANCE_NAME`_Write(const uint8 * rowData, uint8 rowNumber) `=ReentrantKeil($INSTANCE_NAME . "_Write")`;
cystatus `$INSTANCE_NAME`_StartWrite(const uint8 * rowData, uint8 rowNumber) \
                                                `=ReentrantKeil($INSTANCE_NAME . "_StartWrite")`;
cystatus `$INSTANCE_NAME`_StartErase(uint8 sectorNumber) `=ReentrantKeil($INSTANCE_NAME . "_StartErase")`;
cystatus `$INSTANCE_NAME`_Query(void) `=ReentrantKeil($INSTANCE_NAME . "_Query")`;
cystatus `$INSTANCE_NAME`_ByteWritePos(uint8 dataByte, uint8 rowNumber, uint8 byteNumber) \
                                                `=ReentrantKeil($INSTANCE_NAME . "_ByteWritePos")`;


/****************************************
*           API Constants
****************************************/

#define `$INSTANCE_NAME`_EEPROM_SIZE            CYDEV_EE_SIZE
#define `$INSTANCE_NAME`_SPC_BYTE_WRITE_SIZE    (0x01u)

#define `$INSTANCE_NAME`_SECTORS_NUMBER         (CYDEV_EE_SIZE / CYDEV_EEPROM_SECTOR_SIZE)

#define `$INSTANCE_NAME`_AHB_REQ_SHIFT          (0x00u)
#define `$INSTANCE_NAME`_AHB_REQ                ((uint8)(0x01u << `$INSTANCE_NAME`_AHB_REQ_SHIFT))
#define `$INSTANCE_NAME`_AHB_ACK_SHIFT          (0x01u)
#define `$INSTANCE_NAME`_AHB_ACK_MASK           ((uint8)(0x01u << `$INSTANCE_NAME`_AHB_ACK_SHIFT))


/***************************************
* Registers
***************************************/
#define `$INSTANCE_NAME`_SPC_EE_SCR_REG                 (*(reg8 *) CYREG_SPC_EE_SCR)
#define `$INSTANCE_NAME`_SPC_EE_SCR_PTR                 ( (reg8 *) CYREG_SPC_EE_SCR)



/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/
#define `$INSTANCE_NAME`_ByteWrite                  `$INSTANCE_NAME`_ByteWritePos
#define `$INSTANCE_NAME`_QueryWrite                 `$INSTANCE_NAME`_Query

#endif /* CY_EEPROM_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
