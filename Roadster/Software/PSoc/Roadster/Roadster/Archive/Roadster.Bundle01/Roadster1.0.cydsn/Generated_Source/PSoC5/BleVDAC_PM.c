/*******************************************************************************
* File Name: BleVDAC_PM.c  
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

#include "BleVDAC.h"

static BleVDAC_backupStruct BleVDAC_backup;


/*******************************************************************************
* Function Name: BleVDAC_SaveConfig
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
void BleVDAC_SaveConfig(void) 
{
    if (!((BleVDAC_CR1 & BleVDAC_SRC_MASK) == BleVDAC_SRC_UDB))
    {
        BleVDAC_backup.data_value = BleVDAC_Data;
    }
}


/*******************************************************************************
* Function Name: BleVDAC_RestoreConfig
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
void BleVDAC_RestoreConfig(void) 
{
    if (!((BleVDAC_CR1 & BleVDAC_SRC_MASK) == BleVDAC_SRC_UDB))
    {
        if((BleVDAC_Strobe & BleVDAC_STRB_MASK) == BleVDAC_STRB_EN)
        {
            BleVDAC_Strobe &= (uint8)(~BleVDAC_STRB_MASK);
            BleVDAC_Data = BleVDAC_backup.data_value;
            BleVDAC_Strobe |= BleVDAC_STRB_EN;
        }
        else
        {
            BleVDAC_Data = BleVDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: BleVDAC_Sleep
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
*  BleVDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void BleVDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(BleVDAC_ACT_PWR_EN == (BleVDAC_PWRMGR & BleVDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        BleVDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        BleVDAC_backup.enableState = 0u;
    }
    
    BleVDAC_Stop();
    BleVDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: BleVDAC_Wakeup
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
*  BleVDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BleVDAC_Wakeup(void) 
{
    BleVDAC_RestoreConfig();
    
    if(BleVDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        BleVDAC_Enable();

        /* Restore the data register */
        BleVDAC_SetValue(BleVDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
