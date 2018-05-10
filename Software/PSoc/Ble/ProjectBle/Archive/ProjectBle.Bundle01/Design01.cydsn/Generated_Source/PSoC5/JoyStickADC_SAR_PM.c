/*******************************************************************************
* File Name: JoyStickADC_SAR_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "JoyStickADC_SAR.h"


/***************************************
* Local data allocation
***************************************/

static JoyStickADC_SAR_BACKUP_STRUCT  JoyStickADC_SAR_backup =
{
    JoyStickADC_SAR_DISABLED
};


/*******************************************************************************
* Function Name: JoyStickADC_SAR_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void JoyStickADC_SAR_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: JoyStickADC_SAR_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void JoyStickADC_SAR_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: JoyStickADC_SAR_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The JoyStickADC_SAR_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  JoyStickADC_SAR_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void JoyStickADC_SAR_Sleep(void)
{
    if((JoyStickADC_SAR_PWRMGR_SAR_REG  & JoyStickADC_SAR_ACT_PWR_SAR_EN) != 0u)
    {
        if((JoyStickADC_SAR_SAR_CSR0_REG & JoyStickADC_SAR_SAR_SOF_START_CONV) != 0u)
        {
            JoyStickADC_SAR_backup.enableState = JoyStickADC_SAR_ENABLED | JoyStickADC_SAR_STARTED;
        }
        else
        {
            JoyStickADC_SAR_backup.enableState = JoyStickADC_SAR_ENABLED;
        }
        JoyStickADC_SAR_Stop();
    }
    else
    {
        JoyStickADC_SAR_backup.enableState = JoyStickADC_SAR_DISABLED;
    }
}


/*******************************************************************************
* Function Name: JoyStickADC_SAR_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  JoyStickADC_SAR_Sleep() was called. If the component was enabled before the
*  JoyStickADC_SAR_Sleep() function was called, the
*  JoyStickADC_SAR_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  JoyStickADC_SAR_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void JoyStickADC_SAR_Wakeup(void)
{
    if(JoyStickADC_SAR_backup.enableState != JoyStickADC_SAR_DISABLED)
    {
        JoyStickADC_SAR_Enable();
        #if(JoyStickADC_SAR_DEFAULT_CONV_MODE != JoyStickADC_SAR__HARDWARE_TRIGGER)
            if((JoyStickADC_SAR_backup.enableState & JoyStickADC_SAR_STARTED) != 0u)
            {
                JoyStickADC_SAR_StartConvert();
            }
        #endif /* End JoyStickADC_SAR_DEFAULT_CONV_MODE != JoyStickADC_SAR__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
