/*******************************************************************************
* File Name: puttyUart1_PM.c
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

#include "puttyUart1.h"


/***************************************
* Local data allocation
***************************************/

static puttyUart1_BACKUP_STRUCT  puttyUart1_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: puttyUart1_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the puttyUart1_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  puttyUart1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void puttyUart1_SaveConfig(void)
{
    #if(puttyUart1_CONTROL_REG_REMOVED == 0u)
        puttyUart1_backup.cr = puttyUart1_CONTROL_REG;
    #endif /* End puttyUart1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: puttyUart1_RestoreConfig
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
*  puttyUart1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling puttyUart1_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void puttyUart1_RestoreConfig(void)
{
    #if(puttyUart1_CONTROL_REG_REMOVED == 0u)
        puttyUart1_CONTROL_REG = puttyUart1_backup.cr;
    #endif /* End puttyUart1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: puttyUart1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The puttyUart1_Sleep() API saves the current component state. Then it
*  calls the puttyUart1_Stop() function and calls 
*  puttyUart1_SaveConfig() to save the hardware configuration.
*  Call the puttyUart1_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  puttyUart1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void puttyUart1_Sleep(void)
{
    #if(puttyUart1_RX_ENABLED || puttyUart1_HD_ENABLED)
        if((puttyUart1_RXSTATUS_ACTL_REG  & puttyUart1_INT_ENABLE) != 0u)
        {
            puttyUart1_backup.enableState = 1u;
        }
        else
        {
            puttyUart1_backup.enableState = 0u;
        }
    #else
        if((puttyUart1_TXSTATUS_ACTL_REG  & puttyUart1_INT_ENABLE) !=0u)
        {
            puttyUart1_backup.enableState = 1u;
        }
        else
        {
            puttyUart1_backup.enableState = 0u;
        }
    #endif /* End puttyUart1_RX_ENABLED || puttyUart1_HD_ENABLED*/

    puttyUart1_Stop();
    puttyUart1_SaveConfig();
}


/*******************************************************************************
* Function Name: puttyUart1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  puttyUart1_Sleep() was called. The puttyUart1_Wakeup() function
*  calls the puttyUart1_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  puttyUart1_Sleep() function was called, the puttyUart1_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  puttyUart1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void puttyUart1_Wakeup(void)
{
    puttyUart1_RestoreConfig();
    #if( (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) )
        puttyUart1_ClearRxBuffer();
    #endif /* End (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) */
    #if(puttyUart1_TX_ENABLED || puttyUart1_HD_ENABLED)
        puttyUart1_ClearTxBuffer();
    #endif /* End puttyUart1_TX_ENABLED || puttyUart1_HD_ENABLED */

    if(puttyUart1_backup.enableState != 0u)
    {
        puttyUart1_Enable();
    }
}


/* [] END OF FILE */
