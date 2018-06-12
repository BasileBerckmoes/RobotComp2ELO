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
cy_stc_tcpwm_pwm_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config =
{
    .pwmMode = `$PwmMode`UL,
    .clockPrescaler = `$ClockPrescaler`UL,
    .pwmAlignment = `$PwmAlignment`UL,
    .deadTimeClocks = `$DeadClocks`UL,
    .runMode = `$RunMode`UL,
    .period0 = `$Period0`UL,
    .period1 = `$Period1`UL,
    .enablePeriodSwap = `= $EnablePeriodSwap ? "true" : "false"`,
    .compare0 = `$Compare0`UL,
    .compare1 = `$Compare1`UL,
    .enableCompareSwap = `= $EnableCompareSwap ? "true" : "false"`,
    .interruptSources = `$InterruptSource`UL,
    .invertPWMOut = `$InvertPwm`UL,
    .invertPWMOutN = `$InvertPwm_n`UL,
    .killMode = `$KillMode`UL,
    .swapInputMode = `$SwapInputMasked`UL,
    .swapInput = CY_TCPWM_INPUT_CREATOR,
    .reloadInputMode = `$ReloadInputMasked`UL,
    .reloadInput = CY_TCPWM_INPUT_CREATOR,
    .startInputMode = `$StartInputMasked`UL,
    .startInput = CY_TCPWM_INPUT_CREATOR,
    .killInputMode = `$KillInputMasked`UL,
    .killInput = CY_TCPWM_INPUT_CREATOR,
    .countInputMode = `$CountInputMasked`UL,
    .countInput = CY_TCPWM_INPUT_CREATOR,
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
        (void) Cy_TCPWM_PWM_Init(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, &`$INSTANCE_NAME`_config);

        `$INSTANCE_NAME`_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
    
    #if (`$INSTANCE_NAME`_INPUT_DISABLED == `$StartInput`UL)
        Cy_TCPWM_TriggerStart(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
    #endif /* (`$INSTANCE_NAME`_INPUT_DISABLED == `$StartInput`UL) */    
}


/* [] END OF FILE */
