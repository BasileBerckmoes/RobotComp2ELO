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

/* Initialize compPower to the customizer selection. */
cy_en_ctb_power_t `$INSTANCE_NAME`_compPower = `=GetNameForEnum("PowerType", $Power)`;

`=$CY_CONST_CONFIG ? "const " : ""`cy_stc_ctb_opamp_config_t `$INSTANCE_NAME`_compConfig =
{
    .deepSleep      = `=$DeepSleepSupport == 0 ? "CY_CTB_DEEPSLEEP_DISABLE" : "CY_CTB_DEEPSLEEP_ENABLE"`,
    .oaPower        = `=GetNameForEnum("PowerType", $Power)`,
    .oaMode         = CY_CTB_MODE_COMP,
    .oaPump         = `$INSTANCE_NAME`_COMP_CHARGEPUMP,
    .oaCompEdge     = `=GetNameForEnum("InterruptType", $Interrupt)`,
    .oaCompLevel    = CY_CTB_COMP_DSI_TRIGGER_OUT_LEVEL,
    .oaCompBypass   = CY_CTB_COMP_BYPASS_SYNC,
    .oaCompHyst     = `=$Hysteresis == 0 ? "CY_CTB_COMP_HYST_DISABLE" : "CY_CTB_COMP_HYST_10MV"`,
    .oaCompIntrEn   = true,
};

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Initialize the `$INSTANCE_NAME` with default customizer
* values when called the first time and enables the `$INSTANCE_NAME`.
* For subsequent calls the configuration is left unchanged and the comparator is
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

    /* Turn on the CTB block and the comparator by setting the power level. */
    `$INSTANCE_NAME`_Enable();
}


/* [] END OF FILE */
