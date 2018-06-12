/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    `$INSTANCE_NAME`_DISABLED,

    ((`$RegSizeReplacementString`) `$INSTANCE_NAME`_DEFAULT_A0),
    ((`$RegSizeReplacementString`) `$INSTANCE_NAME`_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((`$RegSizeReplacementString`) `$INSTANCE_NAME`_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    /* Store working registers A0 and A1 */
    `$INSTANCE_NAME`_backup.saveSrA0Reg   = `$CyGetRegReplacementString`(`$INSTANCE_NAME`_SHIFT_REG_LSB_PTR);
    `$INSTANCE_NAME`_backup.saveSrA1Reg   = `$CyGetRegReplacementString`(`$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_backup.saveSrIntMask = `$INSTANCE_NAME`_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
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
    /* Restore working registers A0 and A1 */
    `$CySetRegReplacementString`(`$INSTANCE_NAME`_SHIFT_REG_LSB_PTR, `$INSTANCE_NAME`_backup.saveSrA0Reg);
    `$CySetRegReplacementString`(`$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR, `$INSTANCE_NAME`_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_SR_STATUS_MASK = ((uint8) `$INSTANCE_NAME`_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    `$INSTANCE_NAME`_backup.enableState = ((uint8) `$INSTANCE_NAME`_IS_ENABLED);

    `$INSTANCE_NAME`_Stop();
    `$INSTANCE_NAME`_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_RestoreConfig();

    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
