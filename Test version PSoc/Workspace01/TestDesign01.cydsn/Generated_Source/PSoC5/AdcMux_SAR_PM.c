/*******************************************************************************
* File Name: AdcMux_SAR_PM.c
* Version 3.0
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

#include "AdcMux_SAR.h"


/***************************************
* Local data allocation
***************************************/

static AdcMux_SAR_BACKUP_STRUCT  AdcMux_SAR_backup =
{
    AdcMux_SAR_DISABLED
};


/*******************************************************************************
* Function Name: AdcMux_SAR_SaveConfig
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
void AdcMux_SAR_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: AdcMux_SAR_RestoreConfig
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
void AdcMux_SAR_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: AdcMux_SAR_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The AdcMux_SAR_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  AdcMux_SAR_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void AdcMux_SAR_Sleep(void)
{
    if((AdcMux_SAR_PWRMGR_SAR_REG  & AdcMux_SAR_ACT_PWR_SAR_EN) != 0u)
    {
        if((AdcMux_SAR_SAR_CSR0_REG & AdcMux_SAR_SAR_SOF_START_CONV) != 0u)
        {
            AdcMux_SAR_backup.enableState = AdcMux_SAR_ENABLED | AdcMux_SAR_STARTED;
        }
        else
        {
            AdcMux_SAR_backup.enableState = AdcMux_SAR_ENABLED;
        }
        AdcMux_SAR_Stop();
    }
    else
    {
        AdcMux_SAR_backup.enableState = AdcMux_SAR_DISABLED;
    }
}


/*******************************************************************************
* Function Name: AdcMux_SAR_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  AdcMux_SAR_Sleep() was called. If the component was enabled before the
*  AdcMux_SAR_Sleep() function was called, the
*  AdcMux_SAR_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  AdcMux_SAR_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void AdcMux_SAR_Wakeup(void)
{
    if(AdcMux_SAR_backup.enableState != AdcMux_SAR_DISABLED)
    {
        AdcMux_SAR_Enable();
        #if(AdcMux_SAR_DEFAULT_CONV_MODE != AdcMux_SAR__HARDWARE_TRIGGER)
            if((AdcMux_SAR_backup.enableState & AdcMux_SAR_STARTED) != 0u)
            {
                AdcMux_SAR_StartConvert();
            }
        #endif /* End AdcMux_SAR_DEFAULT_CONV_MODE != AdcMux_SAR__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
