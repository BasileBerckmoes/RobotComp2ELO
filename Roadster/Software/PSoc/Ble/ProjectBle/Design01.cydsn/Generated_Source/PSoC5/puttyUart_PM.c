/*******************************************************************************
* File Name: puttyUart_PM.c
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

#include "puttyUart.h"


/***************************************
* Local data allocation
***************************************/

static puttyUart_BACKUP_STRUCT  puttyUart_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: puttyUart_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the puttyUart_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  puttyUart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void puttyUart_SaveConfig(void)
{
    #if(puttyUart_CONTROL_REG_REMOVED == 0u)
        puttyUart_backup.cr = puttyUart_CONTROL_REG;
    #endif /* End puttyUart_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: puttyUart_RestoreConfig
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
*  puttyUart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling puttyUart_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void puttyUart_RestoreConfig(void)
{
    #if(puttyUart_CONTROL_REG_REMOVED == 0u)
        puttyUart_CONTROL_REG = puttyUart_backup.cr;
    #endif /* End puttyUart_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: puttyUart_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The puttyUart_Sleep() API saves the current component state. Then it
*  calls the puttyUart_Stop() function and calls 
*  puttyUart_SaveConfig() to save the hardware configuration.
*  Call the puttyUart_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  puttyUart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void puttyUart_Sleep(void)
{
    #if(puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)
        if((puttyUart_RXSTATUS_ACTL_REG  & puttyUart_INT_ENABLE) != 0u)
        {
            puttyUart_backup.enableState = 1u;
        }
        else
        {
            puttyUart_backup.enableState = 0u;
        }
    #else
        if((puttyUart_TXSTATUS_ACTL_REG  & puttyUart_INT_ENABLE) !=0u)
        {
            puttyUart_backup.enableState = 1u;
        }
        else
        {
            puttyUart_backup.enableState = 0u;
        }
    #endif /* End puttyUart_RX_ENABLED || puttyUart_HD_ENABLED*/

    puttyUart_Stop();
    puttyUart_SaveConfig();
}


/*******************************************************************************
* Function Name: puttyUart_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  puttyUart_Sleep() was called. The puttyUart_Wakeup() function
*  calls the puttyUart_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  puttyUart_Sleep() function was called, the puttyUart_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  puttyUart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void puttyUart_Wakeup(void)
{
    puttyUart_RestoreConfig();
    #if( (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) )
        puttyUart_ClearRxBuffer();
    #endif /* End (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) */
    #if(puttyUart_TX_ENABLED || puttyUart_HD_ENABLED)
        puttyUart_ClearTxBuffer();
    #endif /* End puttyUart_TX_ENABLED || puttyUart_HD_ENABLED */

    if(puttyUart_backup.enableState != 0u)
    {
        puttyUart_Enable();
    }
}


/* [] END OF FILE */
