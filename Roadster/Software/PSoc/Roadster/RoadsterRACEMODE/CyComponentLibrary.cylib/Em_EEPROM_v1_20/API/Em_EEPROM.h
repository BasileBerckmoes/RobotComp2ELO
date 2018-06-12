/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the Emulated EEPROM
*  Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#ifndef CY_EM_EEPROM_`$INSTANCE_NAME`_H
#define CY_EM_EEPROM_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "CyFlash.h"

#if !defined(CYDEV_FLASH_BASE)
    #define CYDEV_FLASH_BASE                    (CYDEV_FLS_BASE)
#endif  /* !defined(CYDEV_FLS_BASE) */

#define `$INSTANCE_NAME`_FLASH_BASE_ADDR        (CYDEV_FLASH_BASE)
#define `$INSTANCE_NAME`_FLASH_SIZE             (CYDEV_FLASH_SIZE)
#define `$INSTANCE_NAME`_FLASH_END_ADDR         (`$INSTANCE_NAME`_FLASH_BASE_ADDR + `$INSTANCE_NAME`_FLASH_SIZE)

#if (CY_PSOC3)
    #define `$INSTANCE_NAME`_CODE_ADDR_OFFSET   (0xff0000u)
    #define `$INSTANCE_NAME`_CODE_ADDR_END      (`$INSTANCE_NAME`_CODE_ADDR_OFFSET + (`$INSTANCE_NAME`_FLASH_SIZE - 1u))
    #define `$INSTANCE_NAME`_CODE_ADDR_MASK     (0xffffu)
#endif /* (CY_PSOC3) */

#define `$INSTANCE_NAME`_ROWS_IN_ARRAY          (CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW)


/***************************************
*        Function Prototypes
***************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil("`$INSTANCE_NAME`_Start")`;
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil("`$INSTANCE_NAME`_Stop")`;
#if (CY_PSOC3)
    cystatus `$INSTANCE_NAME`_Write(const uint8 srcBuf[], const uint8 eepromPtr[],
                                                uint16 byteCount) `=ReentrantKeil("`$INSTANCE_NAME`_Write")`;
#else
    cystatus `$INSTANCE_NAME`_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount);
#endif /* (CY_PSOC3) */

#endif /* CY_EM_EEPROM_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
