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
    
#include "clk/clk.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""`stc_clk_config_t `$INSTANCE_NAME`_Config;

/* PLL stabilization callback function */
`=($pfnPllStabCb eq "") || !$bPllIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPllStabCb . "(void);"`

/* Main clock stabilization callback function */
`=($pfnMcoStabCb eq "") || !$bMcoIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnMcoStabCb . "(void);"`

/* Sub-clock stabilization callback function pointer */
`=($pfnScoStabCb eq "") || !$bScoIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnScoStabCb . "(void);"`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
