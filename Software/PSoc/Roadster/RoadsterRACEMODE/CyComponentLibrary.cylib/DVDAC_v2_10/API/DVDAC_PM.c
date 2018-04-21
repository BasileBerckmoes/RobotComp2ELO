/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the power management source code to the API for the
*  DVDAC component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_VDAC8.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The
*  `$INSTANCE_NAME`_Sleep() API saves the current component state. Then it
*  calls the `$INSTANCE_NAME`_Stop() function and calls
*  `$INSTANCE_NAME`_SaveConfig() to save the hardware configuration. Call the
*  `$INSTANCE_NAME`_Sleep() function before calling the CyPmSleep() or the
*  CyPmHibernate() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    /* Save VDAC8's enable state */
    if(0u != (`$INSTANCE_NAME`_VDAC8_PWRMGR & `$INSTANCE_NAME`_VDAC8_ACT_PWR_EN))
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }

    `$INSTANCE_NAME`_Stop();
    `$INSTANCE_NAME`_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  `$INSTANCE_NAME`_Sleep() was called. The `$INSTANCE_NAME`_Wakeup() function
*  calls the `$INSTANCE_NAME`_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  `$INSTANCE_NAME`_Sleep() function was called, the DVDAC_Wakeup() function
*  will also re-enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_RestoreConfig();

    if(`$INSTANCE_NAME`_backup.enableState == 1u)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the `$INSTANCE_NAME`_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    `$INSTANCE_NAME`_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the `$INSTANCE_NAME`_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    `$INSTANCE_NAME`_VDAC8_RestoreConfig();
}


/* [] END OF FILE */
