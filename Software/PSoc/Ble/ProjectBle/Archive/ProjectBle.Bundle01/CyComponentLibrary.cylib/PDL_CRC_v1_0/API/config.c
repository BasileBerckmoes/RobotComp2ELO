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

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_crc_config_t `$INSTANCE_NAME`_Config =
{
    /* enMode */                `=GetNameForEnum("en_crc_mode_t", $enMode)`,
    /* bUseDma */               `=$bUseDma ? "TRUE" : "FALSE"`,
    /* bFinalXor */             `=$bFinalXor ? "TRUE" : "FALSE"`,
    /* bResultLsbFirst */       `=$bResultLsbFirst ? "TRUE" : "FALSE"`,
    /* bResultLittleEndian */   `=$bResultLittleEndian ? "TRUE" : "FALSE"`,
    /* bDataLsbFirst */         `=$bDataLsbFirst ? "TRUE" : "FALSE"`,
    /* bDataLittleEndian */     `=$bDataLittleEndian ? "TRUE" : "FALSE"`,
    /* u32CrcInitValue */       `$u32CrcInitValue`u
};

/* [] END OF FILE */
