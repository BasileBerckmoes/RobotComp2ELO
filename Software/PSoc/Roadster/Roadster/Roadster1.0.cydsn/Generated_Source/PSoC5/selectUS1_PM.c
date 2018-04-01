/*******************************************************************************
* File Name: selectUS1_PM.c
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

#include "selectUS1.h"

/* Check for removal by optimization */
#if !defined(selectUS1_Sync_ctrl_reg__REMOVED)

static selectUS1_BACKUP_STRUCT  selectUS1_backup = {0u};

    
/*******************************************************************************
* Function Name: selectUS1_SaveConfig
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
void selectUS1_SaveConfig(void) 
{
    selectUS1_backup.controlState = selectUS1_Control;
}


/*******************************************************************************
* Function Name: selectUS1_RestoreConfig
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
void selectUS1_RestoreConfig(void) 
{
     selectUS1_Control = selectUS1_backup.controlState;
}


/*******************************************************************************
* Function Name: selectUS1_Sleep
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
void selectUS1_Sleep(void) 
{
    selectUS1_SaveConfig();
}


/*******************************************************************************
* Function Name: selectUS1_Wakeup
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
void selectUS1_Wakeup(void)  
{
    selectUS1_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
