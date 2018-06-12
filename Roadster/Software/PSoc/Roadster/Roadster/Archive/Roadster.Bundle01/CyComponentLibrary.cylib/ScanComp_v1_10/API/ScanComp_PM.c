/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides Sleep APIs for Scanning Comparator component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for low power mode operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    if(0u != (`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_CONTROL_ENABLE))
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
        `$INSTANCE_NAME`_Stop();
    }
    else /* The component is disabled */
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }

    `$INSTANCE_NAME`_Comp_Sleep();

    #if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
        `$INSTANCE_NAME`_VDAC_Sleep();
    #endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component to the state when `$INSTANCE_NAME`_Sleep() was called.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_Comp_Wakeup();
    
    #if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
        `$INSTANCE_NAME`_VDAC_Start();

        #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)
            `$INSTANCE_NAME`_Init();
        #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */
    #endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */

    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
