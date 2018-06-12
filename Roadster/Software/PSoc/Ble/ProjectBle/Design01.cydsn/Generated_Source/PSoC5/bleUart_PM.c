/*******************************************************************************
* File Name: bleUart_PM.c
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

#include "bleUart.h"


/***************************************
* Local data allocation
***************************************/

static bleUart_BACKUP_STRUCT  bleUart_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: bleUart_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the bleUart_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart_SaveConfig(void)
{
    #if(bleUart_CONTROL_REG_REMOVED == 0u)
        bleUart_backup.cr = bleUart_CONTROL_REG;
    #endif /* End bleUart_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: bleUart_RestoreConfig
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
*  bleUart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling bleUart_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void bleUart_RestoreConfig(void)
{
    #if(bleUart_CONTROL_REG_REMOVED == 0u)
        bleUart_CONTROL_REG = bleUart_backup.cr;
    #endif /* End bleUart_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: bleUart_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The bleUart_Sleep() API saves the current component state. Then it
*  calls the bleUart_Stop() function and calls 
*  bleUart_SaveConfig() to save the hardware configuration.
*  Call the bleUart_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart_Sleep(void)
{
    #if(bleUart_RX_ENABLED || bleUart_HD_ENABLED)
        if((bleUart_RXSTATUS_ACTL_REG  & bleUart_INT_ENABLE) != 0u)
        {
            bleUart_backup.enableState = 1u;
        }
        else
        {
            bleUart_backup.enableState = 0u;
        }
    #else
        if((bleUart_TXSTATUS_ACTL_REG  & bleUart_INT_ENABLE) !=0u)
        {
            bleUart_backup.enableState = 1u;
        }
        else
        {
            bleUart_backup.enableState = 0u;
        }
    #endif /* End bleUart_RX_ENABLED || bleUart_HD_ENABLED*/

    bleUart_Stop();
    bleUart_SaveConfig();
}


/*******************************************************************************
* Function Name: bleUart_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  bleUart_Sleep() was called. The bleUart_Wakeup() function
*  calls the bleUart_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  bleUart_Sleep() function was called, the bleUart_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart_Wakeup(void)
{
    bleUart_RestoreConfig();
    #if( (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) )
        bleUart_ClearRxBuffer();
    #endif /* End (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) */
    #if(bleUart_TX_ENABLED || bleUart_HD_ENABLED)
        bleUart_ClearTxBuffer();
    #endif /* End bleUart_TX_ENABLED || bleUart_HD_ENABLED */

    if(bleUart_backup.enableState != 0u)
    {
        bleUart_Enable();
    }
}


/* [] END OF FILE */
