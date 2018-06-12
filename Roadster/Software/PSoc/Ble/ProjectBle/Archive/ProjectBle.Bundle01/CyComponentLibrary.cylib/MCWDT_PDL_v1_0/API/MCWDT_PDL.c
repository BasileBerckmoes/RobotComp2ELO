/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the `$INSTANCE_NAME`
*  component.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PDL.h"


/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME`  component
*  has been initialized. The variable is initialized to 0 and set to 1 the first
*  time `$INSTANCE_NAME`_Start() is called.
*  This allows the component to restart without reinitialization after the first 
*  call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  `$INSTANCE_NAME`_Init() function can be called before the 
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_Enable() function.
*/
uint8 `$INSTANCE_NAME`_initVar = 0u;

/** The instance-specific configuration structure. This should be used in the 
*  associated `$INSTANCE_NAME`_Init() function.
*/ 
`=$CY_CONST_CONFIG ? "const " : ""`cy_stc_mcwdt_config_t `$INSTANCE_NAME`_config =
{
    .c0Match     = `$INSTANCE_NAME`_C0_MATCH,
    .c1Match     = `$INSTANCE_NAME`_C1_MATCH,
    .c0Mode      = `$INSTANCE_NAME`_C0_MODE,
    .c1Mode      = `$INSTANCE_NAME`_C1_MODE,
    .c2ToggleBit = `$INSTANCE_NAME`_C2_PERIOD,
    .c2Mode      = `$INSTANCE_NAME`_C2_MODE,
    .c0ClearOnMatch = (bool)`$INSTANCE_NAME`_C0_CLEAR_ON_MATCH,
    .c1ClearOnMatch = (bool)`$INSTANCE_NAME`_C1_CLEAR_ON_MATCH,
    .c0c1Cascade = (bool)`$INSTANCE_NAME`_CASCADE_C0C1,
    .c1c2Cascade = (bool)`$INSTANCE_NAME`_CASCADE_C1C2
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  Sets the initVar variable, calls the Init() function, unmasks the 
*  corresponding counter interrupts and then calls the Enable() function 
*  to enable the counters.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_initVar
*
*  \note
*  When this API is called, the counter starts counting after two lf_clk cycles 
*  pass. It is the user's responsibility to check whether the selected counters
*  were enabled immediately after the function call. This can be done by the 
*  `$INSTANCE_NAME`_GetEnabledStatus() API.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (0u == `$INSTANCE_NAME`_initVar)
    {
        (void)`$INSTANCE_NAME`_Init(&`$INSTANCE_NAME`_config);
        `$INSTANCE_NAME`_initVar = 1u; /* Component was initialized */
    }

	/* Set interrupt masks for the counters */
	`$INSTANCE_NAME`_SetInterruptMask(`$INSTANCE_NAME`_CTRS_INT_MASK);

	/* Enable the counters that are enabled in the customizer */
    `$INSTANCE_NAME`_Enable(`$INSTANCE_NAME`_ENABLED_CTRS_MASK, 0u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
*  Calls the Disable() function to disable all counters.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_Disable(CY_MCWDT_CTR_Msk, `$INSTANCE_NAME`_TWO_LF_CLK_CYCLES_DELAY);
    `$INSTANCE_NAME`_DeInit();
}


/* [] END OF FILE */
