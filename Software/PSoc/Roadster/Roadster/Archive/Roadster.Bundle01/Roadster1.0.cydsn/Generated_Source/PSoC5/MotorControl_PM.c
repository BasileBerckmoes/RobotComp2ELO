/*******************************************************************************
* File Name: MotorControl_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MotorControl.h"

static MotorControl_backupStruct MotorControl_backup;


/*******************************************************************************
* Function Name: MotorControl_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorControl_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MotorControl_SaveConfig(void) 
{

    #if(!MotorControl_UsingFixedFunction)
        #if(!MotorControl_PWMModeIsCenterAligned)
            MotorControl_backup.PWMPeriod = MotorControl_ReadPeriod();
        #endif /* (!MotorControl_PWMModeIsCenterAligned) */
        MotorControl_backup.PWMUdb = MotorControl_ReadCounter();
        #if (MotorControl_UseStatus)
            MotorControl_backup.InterruptMaskValue = MotorControl_STATUS_MASK;
        #endif /* (MotorControl_UseStatus) */

        #if(MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_256_CLOCKS || \
            MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_2_4_CLOCKS)
            MotorControl_backup.PWMdeadBandValue = MotorControl_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MotorControl_KillModeMinTime)
             MotorControl_backup.PWMKillCounterPeriod = MotorControl_ReadKillTime();
        #endif /* (MotorControl_KillModeMinTime) */

        #if(MotorControl_UseControl)
            MotorControl_backup.PWMControlRegister = MotorControl_ReadControlRegister();
        #endif /* (MotorControl_UseControl) */
    #endif  /* (!MotorControl_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorControl_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorControl_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorControl_RestoreConfig(void) 
{
        #if(!MotorControl_UsingFixedFunction)
            #if(!MotorControl_PWMModeIsCenterAligned)
                MotorControl_WritePeriod(MotorControl_backup.PWMPeriod);
            #endif /* (!MotorControl_PWMModeIsCenterAligned) */

            MotorControl_WriteCounter(MotorControl_backup.PWMUdb);

            #if (MotorControl_UseStatus)
                MotorControl_STATUS_MASK = MotorControl_backup.InterruptMaskValue;
            #endif /* (MotorControl_UseStatus) */

            #if(MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_256_CLOCKS || \
                MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_2_4_CLOCKS)
                MotorControl_WriteDeadTime(MotorControl_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MotorControl_KillModeMinTime)
                MotorControl_WriteKillTime(MotorControl_backup.PWMKillCounterPeriod);
            #endif /* (MotorControl_KillModeMinTime) */

            #if(MotorControl_UseControl)
                MotorControl_WriteControlRegister(MotorControl_backup.PWMControlRegister);
            #endif /* (MotorControl_UseControl) */
        #endif  /* (!MotorControl_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MotorControl_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorControl_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorControl_Sleep(void) 
{
    #if(MotorControl_UseControl)
        if(MotorControl_CTRL_ENABLE == (MotorControl_CONTROL & MotorControl_CTRL_ENABLE))
        {
            /*Component is enabled */
            MotorControl_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MotorControl_backup.PWMEnableState = 0u;
        }
    #endif /* (MotorControl_UseControl) */

    /* Stop component */
    MotorControl_Stop();

    /* Save registers configuration */
    MotorControl_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorControl_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorControl_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorControl_Wakeup(void) 
{
     /* Restore registers values */
    MotorControl_RestoreConfig();

    if(MotorControl_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MotorControl_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
