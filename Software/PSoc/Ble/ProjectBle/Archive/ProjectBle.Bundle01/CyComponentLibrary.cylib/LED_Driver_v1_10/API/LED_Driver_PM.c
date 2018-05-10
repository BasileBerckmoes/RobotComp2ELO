/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the power management source code to API for the
*  LED_Driver component.
*
* Note:
*  None
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"
static `$INSTANCE_NAME`_backupStruct `$INSTANCE_NAME`_backup;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
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
    uint8 i;
    
    /* Store the component enable state */
    `$INSTANCE_NAME`_backup.ledEnableState = `$INSTANCE_NAME`_enableVar;
    
    /* Save the segment buffers */
    for(i = 0u; i < `$INSTANCE_NAME`_NUM_COM; i++)
    {
        `$INSTANCE_NAME`_backup.segLBackup[i] = `$INSTANCE_NAME`_segLBuffer[i];
        #if (`$INSTANCE_NAME`_NUM_SEG > 8u) 
            `$INSTANCE_NAME`_backup.segMBackup[i] = `$INSTANCE_NAME`_segMBuffer[i];
        #endif /* (`$INSTANCE_NAME`_NUM_SEG > 8u) */
        #if (`$INSTANCE_NAME`_NUM_SEG > 16u) 
            `$INSTANCE_NAME`_backup.segHBackup[i] = `$INSTANCE_NAME`_segHBuffer[i];
        #endif /* (`$INSTANCE_NAME`_NUM_SEG > 16u) */
    }
    
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
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
    uint8 i;
    
    /* Restore the segment buffers */
    for(i = 0u; i < `$INSTANCE_NAME`_NUM_COM; i++)
    {
        `$INSTANCE_NAME`_segLBuffer[i] = `$INSTANCE_NAME`_backup.segLBackup[i];
        #if (`$INSTANCE_NAME`_NUM_SEG > 8u) 
            `$INSTANCE_NAME`_segMBuffer[i] = `$INSTANCE_NAME`_backup.segMBackup[i];
        #endif /* (`$INSTANCE_NAME`_NUM_SEG > 8u) */
        #if (`$INSTANCE_NAME`_NUM_SEG > 16u) 
            `$INSTANCE_NAME`_segHBuffer[i] = `$INSTANCE_NAME`_backup.segHBackup[i];
        #endif /* (`$INSTANCE_NAME`_NUM_SEG > 16u) */
    }
    
    if(`$INSTANCE_NAME`_backup.ledEnableState == `$INSTANCE_NAME`_ENABLED)
    {
        /* Enable the component */
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */

