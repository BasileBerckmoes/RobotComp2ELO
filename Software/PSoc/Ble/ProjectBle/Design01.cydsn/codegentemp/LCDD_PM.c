/*******************************************************************************
* File Name: LCDD_PM.c
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

#include "LCDD.h"


static LCDD_BACKUP_STRUCT LCDD_backup;


/*******************************************************************************
* Function Name: LCDD_SaveConfig
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
void LCDD_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCDD_RestoreConfig
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
void LCDD_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCDD_Sleep
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
void LCDD_Sleep(void) 
{
    LCDD_backup.enableState = LCDD_enableState;
    LCDD_SaveConfig();
    LCDD_Stop();
}


/*******************************************************************************
* Function Name: LCDD_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  LCDD_enableState - Global variable.
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
void LCDD_Wakeup(void) 
{
    LCDD_RestoreConfig();

    if(LCDD_backup.enableState == 1u)
    {
        LCDD_Enable();
    }
}


/* [] END OF FILE */
