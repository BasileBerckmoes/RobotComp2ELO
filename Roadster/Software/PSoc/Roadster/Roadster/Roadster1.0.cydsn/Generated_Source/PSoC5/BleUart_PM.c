/*******************************************************************************
* File Name: BleUart_PM.c
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

#include "BleUart.h"


/***************************************
* Local data allocation
***************************************/

static BleUart_BACKUP_STRUCT  BleUart_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: BleUart_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the BleUart_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BleUart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BleUart_SaveConfig(void)
{
    #if(BleUart_CONTROL_REG_REMOVED == 0u)
        BleUart_backup.cr = BleUart_CONTROL_REG;
    #endif /* End BleUart_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BleUart_RestoreConfig
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
*  BleUart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling BleUart_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void BleUart_RestoreConfig(void)
{
    #if(BleUart_CONTROL_REG_REMOVED == 0u)
        BleUart_CONTROL_REG = BleUart_backup.cr;
    #endif /* End BleUart_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BleUart_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The BleUart_Sleep() API saves the current component state. Then it
*  calls the BleUart_Stop() function and calls 
*  BleUart_SaveConfig() to save the hardware configuration.
*  Call the BleUart_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BleUart_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BleUart_Sleep(void)
{
    #if(BleUart_RX_ENABLED || BleUart_HD_ENABLED)
        if((BleUart_RXSTATUS_ACTL_REG  & BleUart_INT_ENABLE) != 0u)
        {
            BleUart_backup.enableState = 1u;
        }
        else
        {
            BleUart_backup.enableState = 0u;
        }
    #else
        if((BleUart_TXSTATUS_ACTL_REG  & BleUart_INT_ENABLE) !=0u)
        {
            BleUart_backup.enableState = 1u;
        }
        else
        {
            BleUart_backup.enableState = 0u;
        }
    #endif /* End BleUart_RX_ENABLED || BleUart_HD_ENABLED*/

    BleUart_Stop();
    BleUart_SaveConfig();
}


/*******************************************************************************
* Function Name: BleUart_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  BleUart_Sleep() was called. The BleUart_Wakeup() function
*  calls the BleUart_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  BleUart_Sleep() function was called, the BleUart_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BleUart_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BleUart_Wakeup(void)
{
    BleUart_RestoreConfig();
    #if( (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) )
        BleUart_ClearRxBuffer();
    #endif /* End (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) */
    #if(BleUart_TX_ENABLED || BleUart_HD_ENABLED)
        BleUart_ClearTxBuffer();
    #endif /* End BleUart_TX_ENABLED || BleUart_HD_ENABLED */

    if(BleUart_backup.enableState != 0u)
    {
        BleUart_Enable();
    }
}


/* [] END OF FILE */
