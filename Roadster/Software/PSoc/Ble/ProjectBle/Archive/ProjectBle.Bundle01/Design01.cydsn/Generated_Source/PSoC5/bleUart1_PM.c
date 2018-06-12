/*******************************************************************************
* File Name: bleUart1_PM.c
* Version 2.50
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

#include "bleUart1.h"


/***************************************
* Local data allocation
***************************************/

static bleUart1_BACKUP_STRUCT  bleUart1_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: bleUart1_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the bleUart1_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart1_SaveConfig(void)
{
    #if(bleUart1_CONTROL_REG_REMOVED == 0u)
        bleUart1_backup.cr = bleUart1_CONTROL_REG;
    #endif /* End bleUart1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: bleUart1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling bleUart1_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void bleUart1_RestoreConfig(void)
{
    #if(bleUart1_CONTROL_REG_REMOVED == 0u)
        bleUart1_CONTROL_REG = bleUart1_backup.cr;
    #endif /* End bleUart1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: bleUart1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The bleUart1_Sleep() API saves the current component state. Then it
*  calls the bleUart1_Stop() function and calls 
*  bleUart1_SaveConfig() to save the hardware configuration.
*  Call the bleUart1_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart1_Sleep(void)
{
    #if(bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)
        if((bleUart1_RXSTATUS_ACTL_REG  & bleUart1_INT_ENABLE) != 0u)
        {
            bleUart1_backup.enableState = 1u;
        }
        else
        {
            bleUart1_backup.enableState = 0u;
        }
    #else
        if((bleUart1_TXSTATUS_ACTL_REG  & bleUart1_INT_ENABLE) !=0u)
        {
            bleUart1_backup.enableState = 1u;
        }
        else
        {
            bleUart1_backup.enableState = 0u;
        }
    #endif /* End bleUart1_RX_ENABLED || bleUart1_HD_ENABLED*/

    bleUart1_Stop();
    bleUart1_SaveConfig();
}


/*******************************************************************************
* Function Name: bleUart1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  bleUart1_Sleep() was called. The bleUart1_Wakeup() function
*  calls the bleUart1_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  bleUart1_Sleep() function was called, the bleUart1_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart1_Wakeup(void)
{
    bleUart1_RestoreConfig();
    #if( (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) )
        bleUart1_ClearRxBuffer();
    #endif /* End (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) */
    #if(bleUart1_TX_ENABLED || bleUart1_HD_ENABLED)
        bleUart1_ClearTxBuffer();
    #endif /* End bleUart1_TX_ENABLED || bleUart1_HD_ENABLED */

    if(bleUart1_backup.enableState != 0u)
    {
        bleUart1_Enable();
    }
}


/* [] END OF FILE */
