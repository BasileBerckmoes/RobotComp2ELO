/*******************************************************************************
* File Name: `$INSTANCE_NAME_PVT`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the SPDIF_Tx
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPDIFTX_PVT_`$INSTANCE_NAME`_H)
#define CY_SPDIFTX_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"

#if(0u != `$INSTANCE_NAME`_MANAGED_DMA)

    extern volatile uint8 `$INSTANCE_NAME`_cst0BufOffset;
    extern volatile uint8 `$INSTANCE_NAME`_cst1BufOffset;

    /* Channel status streams used for DMA transfer */
    extern volatile uint8 `$INSTANCE_NAME`_cstStream0[`$INSTANCE_NAME`_CST_LENGTH];
    extern volatile uint8 `$INSTANCE_NAME`_cstStream1[`$INSTANCE_NAME`_CST_LENGTH];

#endif /* (0u != `$INSTANCE_NAME`_MANAGED_DMA) */

#endif /* (CY_SPDIFTX_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
