/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in the low power mode.
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

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    0u,
    #if (CY_PSOC3 || CY_PSOC5)
        0u,
        `$INSTANCE_NAME`_INIT_INTERRUPT_MASK,
        `$INSTANCE_NAME`_MODE_MASK,
        (((uint32) ((uint32) `$INSTANCE_NAME`_SYNC_EDGE    << `$INSTANCE_NAME`_EDGE_MODE_SHIFT))     |
        ((uint32) ((uint32) `$INSTANCE_NAME`_SAMPLING_MODE << `$INSTANCE_NAME`_SAMPLE_MODE_SHIFT))   |
        ((uint32) ((uint32) `$INSTANCE_NAME`_CFG_REG_SJW   << `$INSTANCE_NAME`_CFG_REG_SJW_SHIFT))   |
        ((uint32) ((uint32) `$INSTANCE_NAME`_RESET_TYPE    << `$INSTANCE_NAME`_RESET_SHIFT))         |
        ((uint32) ((uint32) `$INSTANCE_NAME`_CFG_REG_TSEG2 << `$INSTANCE_NAME`_CFG_REG_TSEG2_SHIFT)) |
        ((uint32) ((uint32) `$INSTANCE_NAME`_CFG_REG_TSEG1 << `$INSTANCE_NAME`_CFG_REG_TSEG1_SHIFT)) |
        ((uint32) ((uint32) `$INSTANCE_NAME`_ARBITER       << `$INSTANCE_NAME`_ARBITER_SHIFT))       |
        ((uint32) ((uint32) `$INSTANCE_NAME`_BITRATE       << `$INSTANCE_NAME`_BITRATE_SHIFT)))
    #endif /* CY_PSOC3 || CY_PSOC5 */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Save the CAN configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        `$INSTANCE_NAME`_backup.intSr = (CY_GET_REG32(`$INSTANCE_NAME`_INT_SR_PTR));
        `$INSTANCE_NAME`_backup.intEn = (CY_GET_REG32(`$INSTANCE_NAME`_INT_EN_PTR));
        `$INSTANCE_NAME`_backup.cmd = (CY_GET_REG32(`$INSTANCE_NAME`_CMD_PTR));
        `$INSTANCE_NAME`_backup.cfg = (CY_GET_REG32(`$INSTANCE_NAME`_CFG_PTR));
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the CAN configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - Used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then default values
*  from Customizer will be in the following registers: `$INSTANCE_NAME`_INT_SR,
*  `$INSTANCE_NAME`_INT_EN, `$INSTANCE_NAME`_CMD, `$INSTANCE_NAME`_CFG.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        CY_SET_REG32(`$INSTANCE_NAME`_INT_SR_PTR, `$INSTANCE_NAME`_backup.intSr);
        CY_SET_REG32(`$INSTANCE_NAME`_INT_EN_PTR, `$INSTANCE_NAME`_backup.intEn);
        CY_SET_REG32(`$INSTANCE_NAME`_CMD_PTR, `$INSTANCE_NAME`_backup.cmd);
        CY_SET_REG32(`$INSTANCE_NAME`_CFG_PTR, `$INSTANCE_NAME`_backup.cfg);
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Prepares CAN Component to go to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 i;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */

    if (0u != (CY_GET_REG32(`$INSTANCE_NAME`_CMD_PTR) & `$INSTANCE_NAME`_MODE_MASK))
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
    }
    else /* CAN block is disabled */
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }

    #if (CY_PSOC3 || CY_PSOC5)
        `$INSTANCE_NAME`_SaveConfig();
        (void) `$INSTANCE_NAME`_Stop();
    #else /* CY_PSOC4 */
        /* Abort respective pending TX message requests */
        for (i = 0u; i < `$INSTANCE_NAME`_NUMBER_OF_TX_MAILBOXES; i++)
        {
            `$INSTANCE_NAME`_TX_ABORT_MESSAGE(i);
        }

        /* Sets CAN controller to Stop mode */
        (void) `$INSTANCE_NAME`_Stop();

        /* Clear Global Interrupt enable Flag */
        (void) `$INSTANCE_NAME`_GlobalIntDisable();
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Prepares CAN Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - Used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Enable CAN block in Active mode */
        `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;
        /* Enable CAN block in Alternate Active (Standby) mode */
        `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;

        `$INSTANCE_NAME`_RestoreConfig();

        /* Reconfigure Rx and Tx Buffers control registers */
        (void) `$INSTANCE_NAME`_RxTxBuffersConfig();

        if (`$INSTANCE_NAME`_backup.enableState != 0u)
        {
            /* Enable component's operation */
            (void) `$INSTANCE_NAME`_Enable();
        } /* Do nothing if component's block was disabled before */
    #else /* CY_PSOC4 */
        /* Clear all INT_STATUS bits */
        `$INSTANCE_NAME`_INT_SR_REG = `$INSTANCE_NAME`_INT_STATUS_MASK;

        /* Set Global Interrupt enable Flag */
        (void) `$INSTANCE_NAME`_GlobalIntEnable();

        if (`$INSTANCE_NAME`_backup.enableState != 0u)
        {
            (void) `$INSTANCE_NAME`_Enable();
        } /* Do nothing if component's block was disabled before */
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/* [] END OF FILE */
