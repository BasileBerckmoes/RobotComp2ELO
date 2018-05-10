/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the Emulated EEPROM
*  component.
*
********************************************************************************
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_EM_EEPROM_`$INSTANCE_NAME`_H
#define CY_EM_EEPROM_`$INSTANCE_NAME`_H

#include "cyfitter.h"

#if (CYDEV_CHIP_FAMILY_USED != CYDEV_CHIP_FAMILY_PSOC6)
    #include "CyFlash.h"
    #include "cytypes.h"
    #include "cy_em_eeprom.h"
#else
    #include "syslib/cy_syslib.h"
    #include "em_eeprom/cy_em_eeprom.h"
#endif /* (CYDEV_CHIP_FAMILY_USED != CYDEV_CHIP_FAMILY_PSOC6) */

#if defined(__cplusplus)
extern "C" {
#endif


/***************************************
* Conditional Compilation Parameters
***************************************/
#define `$INSTANCE_NAME`_STORAGE_EM_EEPROM          (0U != `$INSTANCE_NAME`_USE_EMULATED_EEEPROM)

#if !defined(CY_PSOC6)
    #define CY_PSOC6                                    (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC6)
#endif /* !defined(CY_PSOC6) */


/***************************************
*        Function Prototypes
***************************************/

cy_en_em_eeprom_status_t `$INSTANCE_NAME`_Init(uint32 startAddress);

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Write
****************************************************************************//**
*
* Invokes the Cy_Em_EEPROM_Write() function. In case of PSoC 6 the function 
* is located in Cy_Em_EEPROM middleware library which is part of PDL. In case if
* it is utilized in the design based on non-PSOC 6 device the function is 
* located in internal design wide resource component - Em_EEPROM_Dynamic.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_Write(addr, eepromData, size) \
                                            Cy_Em_EEPROM_Write(addr, eepromData, size, &`$INSTANCE_NAME`_context)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read
****************************************************************************//**
*
* Invokes the Cy_Em_EEPROM_Read() function. In case of PSoC 6 the function 
* is located in Cy_Em_EEPROM middleware library which is part of PDL. In case if
* it is utilized in the design based on non-PSOC 6 device the function is 
* located in internal design wide resource component - Em_EEPROM_Dynamic.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_Read(addr, eepromData, size) \
                                            Cy_Em_EEPROM_Read(addr, eepromData, size, &`$INSTANCE_NAME`_context)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Erase
****************************************************************************//**
*
* Invokes the Cy_Em_EEPROM_Erase() function. In case of PSoC 6 the function 
* is located in Cy_Em_EEPROM middleware library which is part of PDL. In case if
* it is utilized in the design based on non-PSOC 6 device the function is 
* located in internal design wide resource component - Em_EEPROM_Dynamic.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_Erase()                Cy_Em_EEPROM_Erase(&`$INSTANCE_NAME`_context)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_NumWrites
****************************************************************************//**
*
* Invokes the Cy_Em_EEPROM_NumWrites() function. In case of PSoC 6 the function 
* is located in Cy_Em_EEPROM middleware library which is part of PDL. In case if
* it is utilized in the design based on non-PSOC 6 device the function is 
* located in internal design wide resource component - Em_EEPROM_Dynamic.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_NumWrites()            Cy_Em_EEPROM_NumWrites(&`$INSTANCE_NAME`_context)


/***************************************
*   Initial Parameter Constants
****************************************/

/* Defines the location of the EEPROM storage (User flash or Emulated EEPROM flash area) */
#define `$INSTANCE_NAME`_USE_EMULATED_EEEPROM       (`$UseEmEeprom`U)
/* Defines if blocking or non-blocking writes will be used for writing flash */
#define `$INSTANCE_NAME`_USE_BLOCKING_WRITE         (`$UseBlockingWrite`U)
/* The EEPROM size required by the user */
#define `$INSTANCE_NAME`_EEPROM_SIZE                (`$EepromSize`U)
/* The actual size of flash used to implement the EEPROM with the
* configuration entered by the user.
*/
#define `$INSTANCE_NAME`_ACTUAL_SIZE                (`$ActualSize`U)
#define `$INSTANCE_NAME`_PHYSICAL_SIZE              (`$INSTANCE_NAME`_ACTUAL_SIZE)
/* Holds the value of Wear Leveling option enter by user */
#define `$INSTANCE_NAME`_WEAR_LEVEL_FACTOR          (`$WearLevelFactor`U)
/* Holds the value of Redundant Copy option enter by user */
#define `$INSTANCE_NAME`_REDUNDANT_COPY             (`$RedundantCopy`U)


/***************************************
*       Global Variables
***************************************/
extern cy_stc_eeprom_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config;
extern cy_stc_eeprom_context_t `$INSTANCE_NAME`_context;
extern const `$U8ReplacementString` `$INSTANCE_NAME`_em_EepromStorage[`$INSTANCE_NAME`_ACTUAL_SIZE];

#if defined(__cplusplus)
}
#endif

#endif /* CY_EM_EEPROM_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
