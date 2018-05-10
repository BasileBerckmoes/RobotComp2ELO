/*******************************************************************************
* File Name: sendBleDataTimer_PM.c
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

#include "sendBleDataTimer.h"

static sendBleDataTimer_backupStruct sendBleDataTimer_backup;


/*******************************************************************************
* Function Name: sendBleDataTimer_SaveConfig
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
*  sendBleDataTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void sendBleDataTimer_SaveConfig(void) 
{
    #if (!sendBleDataTimer_UsingFixedFunction)
        sendBleDataTimer_backup.TimerUdb = sendBleDataTimer_ReadCounter();
        sendBleDataTimer_backup.InterruptMaskValue = sendBleDataTimer_STATUS_MASK;
        #if (sendBleDataTimer_UsingHWCaptureCounter)
            sendBleDataTimer_backup.TimerCaptureCounter = sendBleDataTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!sendBleDataTimer_UDB_CONTROL_REG_REMOVED)
            sendBleDataTimer_backup.TimerControlRegister = sendBleDataTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: sendBleDataTimer_RestoreConfig
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
*  sendBleDataTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void sendBleDataTimer_RestoreConfig(void) 
{   
    #if (!sendBleDataTimer_UsingFixedFunction)

        sendBleDataTimer_WriteCounter(sendBleDataTimer_backup.TimerUdb);
        sendBleDataTimer_STATUS_MASK =sendBleDataTimer_backup.InterruptMaskValue;
        #if (sendBleDataTimer_UsingHWCaptureCounter)
            sendBleDataTimer_SetCaptureCount(sendBleDataTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!sendBleDataTimer_UDB_CONTROL_REG_REMOVED)
            sendBleDataTimer_WriteControlRegister(sendBleDataTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: sendBleDataTimer_Sleep
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
*  sendBleDataTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void sendBleDataTimer_Sleep(void) 
{
    #if(!sendBleDataTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(sendBleDataTimer_CTRL_ENABLE == (sendBleDataTimer_CONTROL & sendBleDataTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            sendBleDataTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            sendBleDataTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    sendBleDataTimer_Stop();
    sendBleDataTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: sendBleDataTimer_Wakeup
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
*  sendBleDataTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void sendBleDataTimer_Wakeup(void) 
{
    sendBleDataTimer_RestoreConfig();
    #if(!sendBleDataTimer_UDB_CONTROL_REG_REMOVED)
        if(sendBleDataTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                sendBleDataTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
