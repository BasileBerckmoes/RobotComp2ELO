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
`=$CY_CONST_CONFIG ? "const " : ""`stc_clk_config_t `$INSTANCE_NAME`_Config =
{   
    /* enBaseClkDiv */          `=GetNameForEnum("en_clk_baseclkdiv_t", $enBaseClkDiv)`,
    /* enAPB0Div */             `=GetNameForEnum("en_clk_apb0div_t", $enAPB0Div)`,
    /* enAPB1Div */             `=GetNameForEnum("en_clk_apb1div_t", $enAPB1Div)`,
#if (PDL_MCU_CORE == PDL_FM3_CORE) || (PDL_MCU_CORE == PDL_FM4_CORE)  
    /* enAPB2Div */             `=GetNameForEnum("en_clk_apb2div_t", $enAPB2Div)`,
#endif    
    /* bAPB1Disable */          `=$bAPB1Disable ? "TRUE" : "FALSE"`,
#if (PDL_MCU_CORE == PDL_FM3_CORE) || (PDL_MCU_CORE == PDL_FM4_CORE)      
    /* bAPB2Disable */          `=$bAPB2Disable ? "TRUE" : "FALSE"`,
#endif       
    /* enMCOWaitTime */         `=GetNameForEnum("en_clk_mcowaittime_t", $enMCOWaitTime)`,
    /* enSCOWaitTime */         `=GetNameForEnum("en_clk_scowaittime_t", $enSCOWaitTime)`,
    /* enPLLOWaitTime */        `=GetNameForEnum("en_clk_pllowaittime_t", $enPLLOWaitTime)`,
    /* u8PllK */                `$u8PllK`u,
    /* u8PllM */                `$u8PllM`u,
    /* u8PllN */                `$u8PllN`u,
#if (PDL_INTERRUPT_ENABLE_CLK == PDL_ON)
    /* bPllIrq */               `=$bPllIrq ? "TRUE" : "FALSE"`,
    /* bMcoIrq */               `=$bMcoIrq ? "TRUE" : "FALSE"`,
    /* bScoIrq */               `=$bScoIrq ? "TRUE" : "FALSE"`,
    /* pfnPllStabCb */          `=($pfnPllStabCb eq "") || !$bPllIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPllStabCb`, /* User-supplied callback function */
    /* pfnMcoStabCb */          `=($pfnMcoStabCb eq "") || !$bMcoIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnMcoStabCb`, /* User-supplied callback function */
    /* pfnScoStabCb */          `=($pfnScoStabCb eq "") || !$bScoIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnScoStabCb` /* User-supplied callback function */
#endif   
};

/* [] END OF FILE */
