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

#include "lpm/lpm.h"
#include "cyfitter.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

`=$WKUP00 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP00 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP00" : "/* WKUP00 unused */"`
`=$WKUP01 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP01 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP01" : "/* WKUP01 unused */"`
`=$WKUP02 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP02 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP02" : "/* WKUP02 unused */"`
`=$WKUP03 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP03 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP03" : "/* WKUP03 unused */"`
`=$WKUP04 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP04 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP04" : "/* WKUP04 unused */"`
`=$WKUP05 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP05 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP05" : "/* WKUP05 unused */"`
`=$WKUP06 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP06 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP06" : "/* WKUP06 unused */"`
`=$WKUP07 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP07 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP07" : "/* WKUP07 unused */"`
`=$WKUP08 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP08 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP08" : "/* WKUP08 unused */"`
`=$WKUP09 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP09 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP09" : "/* WKUP09 unused */"`
`=$WKUP10 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP10 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP10" : "/* WKUP10 unused */"`
`=$WKUP11 ? "#define `$INSTANCE_NAME`_SetPinFunc_WKUP11 CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_lpm__`$INSTANCE_NAME`_WKUP11" : "/* WKUP11 unused */"`

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
