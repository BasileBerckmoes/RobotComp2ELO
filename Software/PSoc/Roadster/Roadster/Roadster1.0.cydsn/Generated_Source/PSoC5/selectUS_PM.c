/*******************************************************************************
* File Name: selectUS_PM.c
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

#include "selectUS.h"

/* Check for removal by optimization */
#if !defined(selectUS_Sync_ctrl_reg__REMOVED)

static selectUS_BACKUP_STRUCT  selectUS_backup = {0u};

    
/*******************************************************************************
* Function Name: selectUS_SaveConfig
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
void selectUS_SaveConfig(void) 
{
    selectUS_backup.controlState = selectUS_Control;
}


/*******************************************************************************
* Function Name: selectUS_RestoreConfig
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
void selectUS_RestoreConfig(void) 
{
     selectUS_Control = selectUS_backup.controlState;
}


/*******************************************************************************
* Function Name: selectUS_Sleep
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
void selectUS_Sleep(void) 
{
    selectUS_SaveConfig();
}


/*******************************************************************************
* Function Name: selectUS_Wakeup
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
void selectUS_Wakeup(void)  
{
    selectUS_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
