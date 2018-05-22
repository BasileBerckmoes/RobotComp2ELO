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

#include "wdg/swwdg.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_swwdg_config_t `$INSTANCE_NAME`_Config;

/* Interrupt callback function */
`=$pfnSwwdgIrqCb eq "" ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnSwwdgIrqCb . "(void);"`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
