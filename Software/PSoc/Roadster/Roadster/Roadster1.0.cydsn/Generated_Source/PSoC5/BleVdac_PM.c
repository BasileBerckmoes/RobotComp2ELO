/*******************************************************************************
* File Name: BleVdac_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "BleVdac.h"

static BleVdac_backupStruct BleVdac_backup;


/*******************************************************************************
* Function Name: BleVdac_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void BleVdac_SaveConfig(void) 
{
    if (!((BleVdac_CR1 & BleVdac_SRC_MASK) == BleVdac_SRC_UDB))
    {
        BleVdac_backup.data_value = BleVdac_Data;
    }
}


/*******************************************************************************
* Function Name: BleVdac_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void BleVdac_RestoreConfig(void) 
{
    if (!((BleVdac_CR1 & BleVdac_SRC_MASK) == BleVdac_SRC_UDB))
    {
        if((BleVdac_Strobe & BleVdac_STRB_MASK) == BleVdac_STRB_EN)
        {
            BleVdac_Strobe &= (uint8)(~BleVdac_STRB_MASK);
            BleVdac_Data = BleVdac_backup.data_value;
            BleVdac_Strobe |= BleVdac_STRB_EN;
        }
        else
        {
            BleVdac_Data = BleVdac_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: BleVdac_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  BleVdac_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void BleVdac_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(BleVdac_ACT_PWR_EN == (BleVdac_PWRMGR & BleVdac_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        BleVdac_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        BleVdac_backup.enableState = 0u;
    }
    
    BleVdac_Stop();
    BleVdac_SaveConfig();
}


/*******************************************************************************
* Function Name: BleVdac_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  BleVdac_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BleVdac_Wakeup(void) 
{
    BleVdac_RestoreConfig();
    
    if(BleVdac_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        BleVdac_Enable();

        /* Restore the data register */
        BleVdac_SetValue(BleVdac_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
