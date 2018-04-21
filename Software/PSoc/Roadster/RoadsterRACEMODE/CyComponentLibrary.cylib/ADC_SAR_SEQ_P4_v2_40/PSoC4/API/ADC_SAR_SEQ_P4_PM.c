/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
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

#include "`$INSTANCE_NAME`.h"


/***************************************
* Local data allocation
***************************************/

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup =
{
    `$INSTANCE_NAME`_DISABLED
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
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
void `$INSTANCE_NAME`_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
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
void `$INSTANCE_NAME`_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    `$INSTANCE_NAME`_SAR_DFT_CTRL_REG |= `$INSTANCE_NAME`_ADFT_OVERRIDE;
    if((`$INSTANCE_NAME`_SAR_CTRL_REG  & `$INSTANCE_NAME`_ENABLE) != 0u)
    {
        if((`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_REG & `$INSTANCE_NAME`_CONTINUOUS_EN) != 0u)
        {
            `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED | `$INSTANCE_NAME`_STARTED;
        }
        else
        {
            `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED;
        }
        `$INSTANCE_NAME`_StopConvert();
        `$INSTANCE_NAME`_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((`$INSTANCE_NAME`_SAR_CTRL_REG & `$INSTANCE_NAME`_BOOSTPUMP_EN) != 0u)
        {
            `$INSTANCE_NAME`_SAR_CTRL_REG &= (uint32)~`$INSTANCE_NAME`_BOOSTPUMP_EN;
            `$INSTANCE_NAME`_backup.enableState |= `$INSTANCE_NAME`_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_DISABLED;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    `$INSTANCE_NAME`_SAR_DFT_CTRL_REG &= (uint32)~`$INSTANCE_NAME`_ADFT_OVERRIDE;
    if(`$INSTANCE_NAME`_backup.enableState != `$INSTANCE_NAME`_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_BOOSTPUMP_ENABLED) != 0u)
        {
            `$INSTANCE_NAME`_SAR_CTRL_REG |= `$INSTANCE_NAME`_BOOSTPUMP_EN;
        }
        `$INSTANCE_NAME`_Enable();
        if((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_STARTED) != 0u)
        {
            `$INSTANCE_NAME`_StartConvert();
        }
    }
}
/* [] END OF FILE */
