/*******************************************************************************
* File Name: RijRichting_PM.c
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

#include "RijRichting.h"

/* Check for removal by optimization */
#if !defined(RijRichting_Sync_ctrl_reg__REMOVED)

static RijRichting_BACKUP_STRUCT  RijRichting_backup = {0u};

    
/*******************************************************************************
* Function Name: RijRichting_SaveConfig
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
void RijRichting_SaveConfig(void) 
{
    RijRichting_backup.controlState = RijRichting_Control;
}


/*******************************************************************************
* Function Name: RijRichting_RestoreConfig
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
void RijRichting_RestoreConfig(void) 
{
     RijRichting_Control = RijRichting_backup.controlState;
}


/*******************************************************************************
* Function Name: RijRichting_Sleep
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
void RijRichting_Sleep(void) 
{
    RijRichting_SaveConfig();
}


/*******************************************************************************
* Function Name: RijRichting_Wakeup
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
void RijRichting_Wakeup(void)  
{
    RijRichting_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
