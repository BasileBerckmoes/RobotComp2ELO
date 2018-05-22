/***************************************************************************//**
* \file `$INSTANCE_NAME`_PM.c  
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the power manager source code to the API for PGA 
*  Component.
*
********************************************************************************
* \copyright
* (c) 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h" /* Need VDAC's .h */
#include "`$INSTANCE_NAME`_UAB.h" /* Need sub-component's functions */
#include "`$INSTANCE_NAME`_OUTBUFFER.h" 
/**
* \addtogroup group_globals
* @{
*/
/** Contains configuration of `$INSTANCE_NAME` before sleep. Enable state is the
*   only data required to be preserved. */
static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;
/** @} globals */


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* \brief
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup (W)
*
* \sideeffect
*  None.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_`$INSTANCE_NAME`_Sleep
*
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) 
{
    /* Save UAB_VDAC enable state */
    if( 0UL != (`$INSTANCE_NAME`_UAB_SRAM_CTRL_REG & `$INSTANCE_NAME`_UAB_RUN_MASK)  )
    {
        /* Component is enabled */
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_BACKUP_BLOCKENABLED;
        if (`$INSTANCE_NAME`_OUTBUFFER_CHECK_PWR_MODE_OFF)
        {
            /* Output is not HiZ */
            `$INSTANCE_NAME`_backup.enableState |= `$INSTANCE_NAME`_BACKUP_OUTPUTDRIVEN;
        }
        /* Stop the configuration */
        `$INSTANCE_NAME`_Stop();
    }
    else
    {
        /* Component is disabled */
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
* \brief
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup (R)
*
* \sideeffect
*  None.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_`$INSTANCE_NAME`_Wakeup
*
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
     /* Enables the component operation */
    if((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_BACKUP_BLOCKENABLED)
        == `$INSTANCE_NAME`_BACKUP_BLOCKENABLED) /* If block was enabled... */
    {
        /* Then enable rest of block */
        `$INSTANCE_NAME`_Enable();
        /* Set up output buffer first */
        if ((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_BACKUP_OUTPUTDRIVEN) 
             == `$INSTANCE_NAME`_BACKUP_OUTPUTDRIVEN) /* If output was not HiZ */
        {
            `$INSTANCE_NAME`_SetHiZ(`$INSTANCE_NAME`_OUTSTATE_DRIVEN);
        }
        else
        {
            `$INSTANCE_NAME`_SetHiZ(`$INSTANCE_NAME`_OUTSTATE_HIZ);
        }
    } /* Do nothing if component was disable before */
}

/* [] END OF FILE */
