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
`=$CY_CONST_CONFIG ? "const " : ""`stc_vbat_config_t `$INSTANCE_NAME`_Config =
{
    /* u8ClkDiv */              `$u8ClkDiv`u,
    /* bLinkSubClk */           `=$bLinkSubClk ? "TRUE" : "FALSE"`,
    /* bVbatClkEn */            `=$bVbatClkEn ? "TRUE" : "FALSE"`,              
    /* enSustainCurrent */      `=GetNameForEnum("en_clk_current_t", $enSustainCurrent)`,
    /* enBoostCurrent */        `=GetNameForEnum("en_clk_current_t", $enBoostCurrent)`,
    /* enClkBoostTime */        `=GetNameForEnum("en_clk_boost_time_t", $enClkBoostTime)`
};

/* [] END OF FILE */
