/*******************************************************************************
* File Name: TimerUS_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TimerUS.h"

static TimerUS_backupStruct TimerUS_backup;


/*******************************************************************************
* Function Name: TimerUS_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerUS_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerUS_SaveConfig(void) 
{
    #if (!TimerUS_UsingFixedFunction)
        TimerUS_backup.TimerUdb = TimerUS_ReadCounter();
        TimerUS_backup.InterruptMaskValue = TimerUS_STATUS_MASK;
        #if (TimerUS_UsingHWCaptureCounter)
            TimerUS_backup.TimerCaptureCounter = TimerUS_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimerUS_UDB_CONTROL_REG_REMOVED)
            TimerUS_backup.TimerControlRegister = TimerUS_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerUS_RestoreConfig
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
* Global variables:
*  TimerUS_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerUS_RestoreConfig(void) 
{   
    #if (!TimerUS_UsingFixedFunction)

        TimerUS_WriteCounter(TimerUS_backup.TimerUdb);
        TimerUS_STATUS_MASK =TimerUS_backup.InterruptMaskValue;
        #if (TimerUS_UsingHWCaptureCounter)
            TimerUS_SetCaptureCount(TimerUS_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimerUS_UDB_CONTROL_REG_REMOVED)
            TimerUS_WriteControlRegister(TimerUS_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerUS_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerUS_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerUS_Sleep(void) 
{
    #if(!TimerUS_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimerUS_CTRL_ENABLE == (TimerUS_CONTROL & TimerUS_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerUS_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerUS_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerUS_Stop();
    TimerUS_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerUS_Wakeup
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
*  TimerUS_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerUS_Wakeup(void) 
{
    TimerUS_RestoreConfig();
    #if(!TimerUS_UDB_CONTROL_REG_REMOVED)
        if(TimerUS_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerUS_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
