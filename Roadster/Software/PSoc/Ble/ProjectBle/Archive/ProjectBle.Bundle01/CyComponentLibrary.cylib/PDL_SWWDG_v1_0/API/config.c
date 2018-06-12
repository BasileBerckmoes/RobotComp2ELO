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
`=$CY_CONST_CONFIG ? "const " : ""`stc_swwdg_config_t `$INSTANCE_NAME`_Config =
{
    /* u32LoadValue */          `=IntToHexString($u32LoadValue)`u,
    /* bResetEnable */          `=$bResetEnable ? "TRUE" : "FALSE"`,
#if (PDL_MCU_CORE == PDL_FM4_CORE) || (PDL_MCU_CORE == PDL_FM0P_CORE)
    /* bWinWdgEnable */         `=$bWinWdgEnable ? "TRUE" : "FALSE"`,
    /* bWinWdgResetEnable */    `=$bWinWdgResetEnable ? "TRUE" : "FALSE"`,  
    /* u8TimingWindow */        `=GetNameForEnum("en_swwdg_timing_window_t", $u8TimingWindow)`,
#endif    
    /* pfnSwwdgIrqCb */         `=$pfnSwwdgIrqCb eq "" ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnSwwdgIrqCb` /* User-supplied callback function */
};

/* [] END OF FILE */
