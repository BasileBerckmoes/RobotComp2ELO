/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the power manager source code to the API for SCCT
*  Comparator Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the `$INSTANCE_NAME` for low power mode
*  operation (disable for this case). If the `$INSTANCE_NAME` is enabled, it
*  configures the `$INSTANCE_NAME` for low power operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_backup: The structure field 'enableState' is modified
*  depending on the enable state of the `$INSTANCE_NAME` before entering to
*  sleep mode.
*
* Reentrant:
*  No.
*
* Side Effect:
*  In the inverting mode of `$INSTANCE_NAME`, the output is implemented using
*  UDB. Hence, the `$INSTANCE_NAME` output level is high when this sleep API is
*  called and it does not go to sleep.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    /* Save `$INSTANCE_NAME` enable state */
    if (0u != (`$INSTANCE_NAME`_PM_ACT_CFG_REG & `$INSTANCE_NAME`_ACT_PWR_EN))
    {
        /* `$INSTANCE_NAME` is enabled */
        `$INSTANCE_NAME`_backup.enableState = 1u;

        /* Stop the configuration */
        `$INSTANCE_NAME`_Stop();
    }
    else
    {
        /* `$INSTANCE_NAME` is disabled */
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the `$INSTANCE_NAME` to the state when
*  `$INSTANCE_NAME`_Sleep() was called.
*
* Parameters:
*  None
*
* Return:
*  void
*
* Global variables:
*  `$INSTANCE_NAME`_backup: The structure field 'enableState' is used to
*  restore the enable state of `$INSTANCE_NAME` after wakeup from sleep mode.
*
* Side Effect:
*  Calling the `$INSTANCE_NAME`_Wakeup() function without first calling the
*  `$INSTANCE_NAME`_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    /* Enables the `$INSTANCE_NAME` operation */
    if (1u == `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Enable();
    } /* Do nothing if `$INSTANCE_NAME` was disable before */
}


/* [] END OF FILE */
