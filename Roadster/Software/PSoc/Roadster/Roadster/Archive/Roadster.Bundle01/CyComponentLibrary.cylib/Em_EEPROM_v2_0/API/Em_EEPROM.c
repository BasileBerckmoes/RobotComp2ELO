/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides source code of the API for the Emulated EEPROM
*  Component.
*
********************************************************************************
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

/** The instance-specific configuration structure. This should be used in the
*  associated `$INSTANCE_NAME`_Init() function.
*/
cy_stc_eeprom_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config =
{
    `$EepromSize`U,
    `$WearLevelFactor`U,
    `$RedundantCopy`U,
    `$UseBlockingWrite`U,
    0U
};

/** The instance-specific context structure that holds all required information
* about an EEPROM instance. This structure is filled by the Em_EEPROM
* library Init() function and used by EEPROM library functions.
*/
cy_stc_eeprom_context_t `$INSTANCE_NAME`_context;

/* For PSoC 6 place EEPROM into Emulated EEPROM flash area */
#if ((CY_PSOC6) && (`$INSTANCE_NAME`_STORAGE_EM_EEPROM))

    CY_SECTION(".cy_em_eeprom") CY_ALIGN(CY_FLASH_SIZEOF_ROW)
    const `$U8ReplacementString` `$INSTANCE_NAME`_em_EepromStorage[`$INSTANCE_NAME`_ACTUAL_SIZE] = {0u};

#endif /* ((CY_PSOC6) && (`$INSTANCE_NAME`_STORAGE_EM_EEPROM)) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Fills the start address of the EEPROM to the component configuration structure
* and invokes Cy_Em_EEPROM_Init() function. In case of PSoC 6 the function 
* is located in Cy_Em_EEPROM middleware library which is part of PDL. In case if
* it is utilized in the design based on non-PSOC 6 device the function is 
* located in internal design wide resource component - Em_EEPROM_Dynamic.
*
* \param startAddress
* Start address of the EEPROM storage. For PSoC 6, if Emulated EEPROM is 
* selected for EEPROM storage, the start address will be overwritten to some 
* address from Emulated EEPROM flash area.
*
* \return
* A result of function execution of type cy_en_em_eeprom_status_t.
*
*******************************************************************************/
cy_en_em_eeprom_status_t `$INSTANCE_NAME`_Init(uint32 startAddress)
{
    cy_en_em_eeprom_status_t ret;
    cy_stc_eeprom_config_t config;

    config.blockingWrite =      `$INSTANCE_NAME`_config.blockingWrite;
    config.eepromSize =         `$INSTANCE_NAME`_config.eepromSize;
    config.redundantCopy =      `$INSTANCE_NAME`_config.redundantCopy;
    config.wearLevelingFactor = `$INSTANCE_NAME`_config.wearLevelingFactor;
    
#if ((CY_PSOC6) && (`$INSTANCE_NAME`_STORAGE_EM_EEPROM))
    /* For PSoC 6, if Emulated EEPROM is selected - override the eeprom start 
    * address.
    */
    config.userFlashStartAddr = (`$U32ReplacementString`)`$INSTANCE_NAME`_em_EepromStorage;
#else
    config.userFlashStartAddr = startAddress;
#endif /* ((CY_PSOC6) && (`$INSTANCE_NAME`_STORAGE_EM_EEPROM)) */
        
    ret = Cy_Em_EEPROM_Init(&config, &`$INSTANCE_NAME`_context);

    return(ret);
}


/* [] END OF FILE */
