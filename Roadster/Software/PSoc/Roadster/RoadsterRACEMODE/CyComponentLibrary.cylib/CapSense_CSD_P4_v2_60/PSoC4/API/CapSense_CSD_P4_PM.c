/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides Sleep APIs for CapSense CSD Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    0x00u, /* enableState; */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the customer configuration of CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save the component state before entering the  sleep
*  mode and none-retention registers.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void)
{
    if ((`$INSTANCE_NAME`_CSD_CFG_REG & `$INSTANCE_NAME`_CSD_CFG_ENABLE) != 0u)
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Disables the Active mode power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save the component state before entering the sleep
*  mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    `$INSTANCE_NAME`_SaveConfig();

    /* Disable interrupt */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    `$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN | `$INSTANCE_NAME`_CSD_CFG_SENSE_EN);

    #if(`$INSTANCE_NAME`_IDAC_CNT == 2u)
        `$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_ENABLE);
    #endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */

    /* Disable Clocks */
    `$INSTANCE_NAME`_SenseClk_Stop();
    `$INSTANCE_NAME`_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Must be called only after `$INSTANCE_NAME`_SaveConfig() routine. Otherwise
*  the component configuration will be overwritten with its initial setting.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration and non-retention register values.
*  Restores the enabled state of the component by setting the Active mode power template
*  bits for a number of components used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    /* Enable the Clocks */
    `$INSTANCE_NAME`_SenseClk_Start();
    `$INSTANCE_NAME`_SampleClk_Start();

    /* Restore CapSense Enable state */
    if (`$INSTANCE_NAME`_backup.enableState != 0u)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
