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

/* NMI configuration structure */
#if (`$INSTANCE_NAME`_NMI_ENABLED == PDL_ON)
`=$CY_CONST_CONFIG ? "const " : ""`stc_exint_nmi_config_t `$INSTANCE_NAME`_Config = 
{
    /* pfnNmiCallback */        `=$pfnExintCallback eq "" ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnExintCallback`
};
#endif /* `$INSTANCE_NAME`_NMI_ENABLED == PDL_ON */

/* [] END OF FILE */
