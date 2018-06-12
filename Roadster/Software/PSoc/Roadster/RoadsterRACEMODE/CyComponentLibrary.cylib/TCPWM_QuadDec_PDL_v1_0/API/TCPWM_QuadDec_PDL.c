/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the `$INSTANCE_NAME`
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/** Indicates whether or not the `$INSTANCE_NAME` has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  `$INSTANCE_NAME`_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the `$INSTANCE_NAME`_Start() routine.
*/
uint8_t `$INSTANCE_NAME`_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated `$INSTANCE_NAME`_Init() function.
*/ 
cy_stc_tcpwm_quaddec_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config =
{
	.resolution = `$Resolution`UL,
	.interruptSources = `$InterruptSource`UL,
	.indexInputMode = `$IndexInputMasked`UL,
	.indexInput = CY_TCPWM_INPUT_CREATOR,
	.stopInputMode = `$StopInputMasked`UL,
	.stopInput = CY_TCPWM_INPUT_CREATOR,
    .phiAInput = CY_TCPWM_INPUT_CREATOR,
    .phiBInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  Calls the `$INSTANCE_NAME`_Init() when called the first time and enables 
*  the `$INSTANCE_NAME`. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_initVar
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (0U == `$INSTANCE_NAME`_initVar)
    {
        (void)Cy_TCPWM_QuadDec_Init(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, &`$INSTANCE_NAME`_config);

        `$INSTANCE_NAME`_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
    
    Cy_TCPWM_TriggerReloadOrIndex(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
}


/* [] END OF FILE */
