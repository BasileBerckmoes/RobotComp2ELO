/*******************************************************************************
* File Name: BleUart1_PM.c
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

#include "BleUart1.h"


/***************************************
* Local data allocation
***************************************/

static BleUart1_BACKUP_STRUCT  BleUart1_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: BleUart1_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the BleUart1_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BleUart1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BleUart1_SaveConfig(void)
{
    #if(BleUart1_CONTROL_REG_REMOVED == 0u)
        BleUart1_backup.cr = BleUart1_CONTROL_REG;
    #endif /* End BleUart1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BleUart1_RestoreConfig
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
*  BleUart1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling BleUart1_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void BleUart1_RestoreConfig(void)
{
    #if(BleUart1_CONTROL_REG_REMOVED == 0u)
        BleUart1_CONTROL_REG = BleUart1_backup.cr;
    #endif /* End BleUart1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BleUart1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The BleUart1_Sleep() API saves the current component state. Then it
*  calls the BleUart1_Stop() function and calls 
*  BleUart1_SaveConfig() to save the hardware configuration.
*  Call the BleUart1_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BleUart1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BleUart1_Sleep(void)
{
    #if(BleUart1_RX_ENABLED || BleUart1_HD_ENABLED)
        if((BleUart1_RXSTATUS_ACTL_REG  & BleUart1_INT_ENABLE) != 0u)
        {
            BleUart1_backup.enableState = 1u;
        }
        else
        {
            BleUart1_backup.enableState = 0u;
        }
    #else
        if((BleUart1_TXSTATUS_ACTL_REG  & BleUart1_INT_ENABLE) !=0u)
        {
            BleUart1_backup.enableState = 1u;
        }
        else
        {
            BleUart1_backup.enableState = 0u;
        }
    #endif /* End BleUart1_RX_ENABLED || BleUart1_HD_ENABLED*/

    BleUart1_Stop();
    BleUart1_SaveConfig();
}


/*******************************************************************************
* Function Name: BleUart1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  BleUart1_Sleep() was called. The BleUart1_Wakeup() function
*  calls the BleUart1_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  BleUart1_Sleep() function was called, the BleUart1_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BleUart1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BleUart1_Wakeup(void)
{
    BleUart1_RestoreConfig();
    #if( (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) )
        BleUart1_ClearRxBuffer();
    #endif /* End (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) */
    #if(BleUart1_TX_ENABLED || BleUart1_HD_ENABLED)
        BleUart1_ClearTxBuffer();
    #endif /* End BleUart1_TX_ENABLED || BleUart1_HD_ENABLED */

    if(BleUart1_backup.enableState != 0u)
    {
        BleUart1_Enable();
    }
}


/* [] END OF FILE */
