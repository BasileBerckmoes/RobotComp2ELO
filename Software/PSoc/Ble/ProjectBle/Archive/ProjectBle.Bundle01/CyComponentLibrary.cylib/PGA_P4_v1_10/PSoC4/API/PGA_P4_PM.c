/***************************************************************************//**
* \file     `$INSTANCE_NAME`_PM.c  
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the power management source code to the API for PGA_P4 
*  Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void)
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: `$INSTANCE_NAME`_RestoreConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void)
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function disables 
*  component's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Deep Sleep state.
*
*  \internal
*   The `$INSTANCE_NAME`_backup.enableState is modified 
*   depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    #if(!`$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT)
        if((`$INSTANCE_NAME`_OA_RES_CTRL_REG & `$INSTANCE_NAME`_OA_PWR_MODE_MASK) != 0u)
        {
            `$INSTANCE_NAME`_internalGainPower |= `$INSTANCE_NAME`_ENABLED;
            `$INSTANCE_NAME`_Stop();
        }
        else /* The component is disabled */
        {
            `$INSTANCE_NAME`_internalGainPower &= (uint32) ~`$INSTANCE_NAME`_ENABLED;
        }
        /* Save the configuration */
        `$INSTANCE_NAME`_SaveConfig();
    #endif /* (`$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function enables
*  block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Active state.
*
*  \internal
*   The `$INSTANCE_NAME`_backup.enableState is used to 
*   restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    #if(!`$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT)
        /* Restore the configurations */
        `$INSTANCE_NAME`_RestoreConfig();
        /* Enables the component operation */
        if((`$INSTANCE_NAME`_internalGainPower & `$INSTANCE_NAME`_ENABLED) != 0u)
        {
            `$INSTANCE_NAME`_Enable();
        } /* Do nothing if component was disabled before */
    #endif /* (`$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
