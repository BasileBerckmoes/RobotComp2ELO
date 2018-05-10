/*******************************************************************************
* \file `$INSTANCE_NAME`_config.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable declarations for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_CONFIG_H
#define `$INSTANCE_NAME`_CONFIG_H

#include "lvd/lvd.h"
#include "cyfitter.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if (PDL_MCU_TYPE == PDL_FM0P_TYPE2)
    #define `$INSTANCE_NAME`_SetPinFunc_LVDI CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lvd__`$INSTANCE_NAME`_LVDI
#endif 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
