/*******************************************************************************
* File Name: BleOpamp_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "BleOpamp.h"

static BleOpamp_BACKUP_STRUCT  BleOpamp_backup;


/*******************************************************************************  
* Function Name: BleOpamp_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void BleOpamp_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: BleOpamp_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void BleOpamp_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: BleOpamp_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BleOpamp_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void BleOpamp_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((BleOpamp_PM_ACT_CFG_REG & BleOpamp_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        BleOpamp_backup.enableState = 1u;
         /* Stops the component */
         BleOpamp_Stop();
    }
    else
    {
        /* Component is disabled */
        BleOpamp_backup.enableState = 0u;
    }
    /* Saves the configuration */
    BleOpamp_SaveConfig();
}


/*******************************************************************************  
* Function Name: BleOpamp_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BleOpamp_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void BleOpamp_Wakeup(void) 
{
    /* Restore the user configuration */
    BleOpamp_RestoreConfig();

    /* Enables the component operation */
    if(BleOpamp_backup.enableState == 1u)
    {
        BleOpamp_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */