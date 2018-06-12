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

#include "dt/dt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_CHANNEL0 (0u)
#define `$INSTANCE_NAME`_CHANNEL1 (1u)

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_dt_channel_config_t `$INSTANCE_NAME`_Ch0_Config;
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_dt_channel_config_t `$INSTANCE_NAME`_Ch1_Config;

/* Interrupt callback function */
`=($pfnCh0IrqCallback eq "") || !$bCh0IrqEnable ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnCh0IrqCallback . "(void);"`
`=($pfnCh1IrqCallback eq "") || !$bCh1IrqEnable ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnCh1IrqCallback . "(void);"`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
