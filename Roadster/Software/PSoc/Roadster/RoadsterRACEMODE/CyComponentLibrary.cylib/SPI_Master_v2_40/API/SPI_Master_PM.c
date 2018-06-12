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
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    `$INSTANCE_NAME`_DISABLED,
    `$INSTANCE_NAME`_BITCTR_INIT,
    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_TX_INIT_INTERRUPTS_MASK,
        `$INSTANCE_NAME`_RX_INIT_INTERRUPTS_MASK
    #endif /* CY_UDB_V0 */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    /* Store Status Mask registers */
    #if(CY_UDB_V0)
       `$INSTANCE_NAME`_backup.cntrPeriod      = `$INSTANCE_NAME`_COUNTER_PERIOD_REG;
       `$INSTANCE_NAME`_backup.saveSrTxIntMask = `$INSTANCE_NAME`_TX_STATUS_MASK_REG;
       `$INSTANCE_NAME`_backup.saveSrRxIntMask = `$INSTANCE_NAME`_RX_STATUS_MASK_REG;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then in the following
*  registers will be default values from Customizer:
*  `$INSTANCE_NAME`_STATUS_MASK_REG and `$INSTANCE_NAME`_COUNTER_PERIOD_REG.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    /* Restore the data, saved by SaveConfig() function */
    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_COUNTER_PERIOD_REG = `$INSTANCE_NAME`_backup.cntrPeriod;
        `$INSTANCE_NAME`_TX_STATUS_MASK_REG = ((uint8) `$INSTANCE_NAME`_backup.saveSrTxIntMask);
        `$INSTANCE_NAME`_RX_STATUS_MASK_REG = ((uint8) `$INSTANCE_NAME`_backup.saveSrRxIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    /* Save components enable state */
    `$INSTANCE_NAME`_backup.enableState = ((uint8) `$INSTANCE_NAME`_IS_ENABLED);

    `$INSTANCE_NAME`_Stop();
    `$INSTANCE_NAME`_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used when non-retention registers are restored.
*  `$INSTANCE_NAME`_txBufferWrite - modified every function call - resets to
*  zero.
*  `$INSTANCE_NAME`_txBufferRead - modified every function call - resets to
*  zero.
*  `$INSTANCE_NAME`_rxBufferWrite - modified every function call - resets to
*  zero.
*  `$INSTANCE_NAME`_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_RestoreConfig();

    #if(`$INSTANCE_NAME`_RX_SOFTWARE_BUF_ENABLED)
        `$INSTANCE_NAME`_rxBufferFull  = 0u;
        `$INSTANCE_NAME`_rxBufferRead  = 0u;
        `$INSTANCE_NAME`_rxBufferWrite = 0u;
    #endif /* (`$INSTANCE_NAME`_RX_SOFTWARE_BUF_ENABLED) */

    #if(`$INSTANCE_NAME`_TX_SOFTWARE_BUF_ENABLED)
        `$INSTANCE_NAME`_txBufferFull  = 0u;
        `$INSTANCE_NAME`_txBufferRead  = 0u;
        `$INSTANCE_NAME`_txBufferWrite = 0u;
    #endif /* (`$INSTANCE_NAME`_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    `$INSTANCE_NAME`_ClearFIFO();

    /* Restore components block enable state */
    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
