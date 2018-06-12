/*******************************************************************************
* File Name: LCD1_PM.c
* Version 2.20
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD1.h"


static LCD1_BACKUP_STRUCT LCD1_backup;


/*******************************************************************************
* Function Name: LCD1_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD1_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD1_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD1_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD1_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD1_Sleep(void) 
{
    LCD1_backup.enableState = LCD1_enableState;
    LCD1_SaveConfig();
    LCD1_Stop();
}


/*******************************************************************************
* Function Name: LCD1_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  LCD1_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD1_Wakeup(void) 
{
    LCD1_RestoreConfig();

    if(LCD1_backup.enableState == 1u)
    {
        LCD1_Enable();
    }
}


/* [] END OF FILE */
