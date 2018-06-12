/*******************************************************************************
* File Name: BleBuffer_PM.c
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

#include "BleBuffer.h"

static BleBuffer_BACKUP_STRUCT  BleBuffer_backup;


/*******************************************************************************  
* Function Name: BleBuffer_SaveConfig
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
void BleBuffer_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: BleBuffer_RestoreConfig
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
void BleBuffer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: BleBuffer_Sleep
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
*  BleBuffer_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void BleBuffer_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((BleBuffer_PM_ACT_CFG_REG & BleBuffer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        BleBuffer_backup.enableState = 1u;
         /* Stops the component */
         BleBuffer_Stop();
    }
    else
    {
        /* Component is disabled */
        BleBuffer_backup.enableState = 0u;
    }
    /* Saves the configuration */
    BleBuffer_SaveConfig();
}


/*******************************************************************************  
* Function Name: BleBuffer_Wakeup
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
*  BleBuffer_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void BleBuffer_Wakeup(void) 
{
    /* Restore the user configuration */
    BleBuffer_RestoreConfig();

    /* Enables the component operation */
    if(BleBuffer_backup.enableState == 1u)
    {
        BleBuffer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
