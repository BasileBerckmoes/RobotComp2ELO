/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
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

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup = {0u};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Left to preserve backward compatibility.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    /* Nothing to save. All registers are retention. */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Left to preserve backward compatibility.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    /* Nothing to restore. All registers are retention. */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Prepares I2S for entering sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to store component state prior entering 
*    sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    /* Get component state */
    `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_CONTROL_REG;

    /* Stop component */
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Prepares I2S for exit from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to restore component state after exit from
*    sleep mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    #if (`$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION)
        `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_BIT_RESOLUTION_MODE_MASK;
    #endif /* `$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION */

    if(0u != (`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_EN))
    {
        /* Enable component's operation */
        `$INSTANCE_NAME`_Enable();

        /* Enable Tx/Rx direction if they were enabled before sleep */
        #if(`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
            if(0u != (`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_TX_EN))
            {
                `$INSTANCE_NAME`_EnableTx();
            }
        #endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */
        
        #if(`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
            if(0u != (`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_RX_EN))
            {
                `$INSTANCE_NAME`_EnableRx();
            }
        #endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */
    }
}


/* [] END OF FILE */
