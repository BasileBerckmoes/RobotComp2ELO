/*******************************************************************************
* File Name: TriggerReg_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TriggerReg.h"

/* Check for removal by optimization */
#if !defined(TriggerReg_Sync_ctrl_reg__REMOVED)

static TriggerReg_BACKUP_STRUCT  TriggerReg_backup = {0u};

    
/*******************************************************************************
* Function Name: TriggerReg_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TriggerReg_SaveConfig(void) 
{
    TriggerReg_backup.controlState = TriggerReg_Control;
}


/*******************************************************************************
* Function Name: TriggerReg_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void TriggerReg_RestoreConfig(void) 
{
     TriggerReg_Control = TriggerReg_backup.controlState;
}


/*******************************************************************************
* Function Name: TriggerReg_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TriggerReg_Sleep(void) 
{
    TriggerReg_SaveConfig();
}


/*******************************************************************************
* Function Name: TriggerReg_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TriggerReg_Wakeup(void)  
{
    TriggerReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
