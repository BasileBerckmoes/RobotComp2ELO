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

#include "exint/exint.h"
#include "cyfitter.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_NMI_ENABLED    `=$NMI ? "PDL_ON" : "PDL_OFF"`

#if (`$INSTANCE_NAME`_NMI_ENABLED == PDL_ON)
    extern `=$CY_CONST_CONFIG ? "const " : ""`stc_exint_nmi_config_t `$INSTANCE_NAME`_Config;
#else /* EXINT */
    #define `$INSTANCE_NAME`_Index `=GetNameForEnum("en_exint_instance_index_t", LookupFitterDefine($Index))`
    #define `$INSTANCE_NAME`_Level `=GetNameForEnum("en_exint_level_t", $enLevel)`
#endif /* `$INSTANCE_NAME`_NMI_ENABLED == PDL_ON */

/* Callback function */
`=$pfnExintCallback eq "" ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnExintCallback . "(void);"`

/* Pin function macro */
`=$NMI ?("#define `$INSTANCE_NAME`_SetPinFunc_NMIX()   CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_exnmi__`$INSTANCE_NAME`_NMIX()"):("#define `$INSTANCE_NAME`_SetPinFunc_INT()   CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_exint__`$INSTANCE_NAME`_INT0()")`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
