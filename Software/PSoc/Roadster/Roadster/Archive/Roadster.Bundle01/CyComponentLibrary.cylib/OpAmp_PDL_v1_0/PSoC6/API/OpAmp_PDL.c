/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the `$INSTANCE_NAME`
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "`$INSTANCE_NAME`.h"

uint8_t `$INSTANCE_NAME`_initVar = 0u;

/* Initialize opampPower to customizer selection. */
cy_en_ctb_power_t `$INSTANCE_NAME`_opampPower = `=GetNameForEnum("OpampPowerType", $Power)`;

`=$CY_CONST_CONFIG ? "const " : ""`cy_stc_ctb_opamp_config_t `$INSTANCE_NAME`_opampConfig =
{
    .deepSleep      = `=$DeepSleepSupport == 0 ? "CY_CTB_DEEPSLEEP_DISABLE" : "CY_CTB_DEEPSLEEP_ENABLE"`,
    .oaPower        = `=GetNameForEnum("OpampPowerType", $Power)`,
    .oaMode         = `=GetNameForEnum("OpampOutputType", $OutputCurrent)`,
    .oaPump         = `$INSTANCE_NAME`_OPAMP_CHARGEPUMP,
    .oaCompEdge     = CY_CTB_COMP_EDGE_DISABLE,
    .oaCompLevel    = CY_CTB_COMP_DSI_TRIGGER_OUT_PULSE,
    .oaCompBypass   = CY_CTB_COMP_BYPASS_SYNC,
    .oaCompHyst     = CY_CTB_COMP_HYST_DISABLE,
    .oaCompIntrEn   = false,
};

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Initialize the `$INSTANCE_NAME` with default customizer
* values when called the first time and enables the `$INSTANCE_NAME`.
* For subsequent calls the configuration is left unchanged and the opamp is
* just enabled.
*
* `$INSTANCE_NAME`_initVar: this global variable is used to indicate the initial
* configuration of this component. The variable is initialized to zero and set
* to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows
* enabling/disabling a component without re-initialization in all subsequent
* calls to the `$INSTANCE_NAME`_Start() routine.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
       `$INSTANCE_NAME`_Init();         /* Initialize and turn on the hardware block. */
       `$INSTANCE_NAME`_initVar = 1u;
    }

    /* Turn on the CTB and the opamp by setting the power level. */
    `$INSTANCE_NAME`_Enable();
}


/* [] END OF FILE */

