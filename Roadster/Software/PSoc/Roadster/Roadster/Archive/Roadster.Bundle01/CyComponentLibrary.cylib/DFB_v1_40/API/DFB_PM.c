/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup = { 0u };


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the user configuration of the DFB non-retention registers. This routine
*  is called by DFB_Sleep() to save the component configuration before entering
*  sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    uint8 count;
    uint8 i = 0u;
	
    `$INSTANCE_NAME`_backup.sr = `$INSTANCE_NAME`_SR_REG;
    `$INSTANCE_NAME`_backup.sem = `$INSTANCE_NAME`_SEM_REG;

    /* ACU RAM */
    count = `$INSTANCE_NAME`_ACU_RAM_SIZE_CUR;
    while (count > 0u)
    {
        `$INSTANCE_NAME`_backup.acu[i] = CY_GET_REG32(& `$INSTANCE_NAME`_ACU_RAM_PTR[i]);
        count--;
        i++;
    }
	
    /* Take DFB RAM off the bus */
    `$INSTANCE_NAME`_RAM_DIR_REG = `$INSTANCE_NAME`_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of the DFB non-retention registers. This
*  routine is called by DFB_Wakeup() to restore the component configuration when
*  exiting sleep.
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
    uint8 count;
    uint8 i = 0u;

    `$INSTANCE_NAME`_SR_REG = `$INSTANCE_NAME`_backup.sr;
    `$INSTANCE_NAME`_SEM_REG = `$INSTANCE_NAME`_backup.sem;
    
    /* Power on DFB before initializing the RAMs */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_PM_ACT_MSK;
    /* Enables DFB block in Alternate Active (Standby) mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_PM_STBY_MSK;
    
    /* Put DFB RAM on the bus */
    `$INSTANCE_NAME`_RAM_DIR_REG = `$INSTANCE_NAME`_RAM_DIR_BUS;

    /* ACU RAM */
    count = `$INSTANCE_NAME`_ACU_RAM_SIZE_CUR;
    while (count > 0u)
    {
        CY_SET_REG32(& `$INSTANCE_NAME`_ACU_RAM_PTR[i], `$INSTANCE_NAME`_backup.acu[i]);
        count--;
        i++;
    }

    /* Take DFB RAM off the bus */
    `$INSTANCE_NAME`_RAM_DIR_REG = `$INSTANCE_NAME`_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep. The
*  `$INSTANCE_NAME`_Sleep() routine saves the current component state. Then it
*  calls the DFB_Stop() function and calls `$INSTANCE_NAME`_SaveConfig() to save
*  the hardware configuration. Call the `$INSTANCE_NAME`_Sleep() function before
*  calling the CyPmSleep() or the CyPmHibernate() function. Refer to the PSoC
*  Creator System Reference Guide for more information about power management
*  functions.
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
    if (0u != (`$INSTANCE_NAME`_CR_REG & `$INSTANCE_NAME`_RUN_MASK))
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
    }
    else /* The DFB block is disabled */
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }

    /* Turn off the run bit, and put the DFB RAM on the bus */
    `$INSTANCE_NAME`_Pause();
    
    /* Save the configuration */
    `$INSTANCE_NAME`_SaveConfig();
    
    /* Disables the clock to the entire core of the block */
    `$INSTANCE_NAME`_CR_REG |= `$INSTANCE_NAME`_CORECLK_DISABLE;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  `$INSTANCE_NAME`_Sleep() was called. The `$INSTANCE_NAME`_Wakeup() function
*  calls the `$INSTANCE_NAME`_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  `$INSTANCE_NAME`_Sleep() function was called, the `$INSTANCE_NAME`_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Calling the `$INSTANCE_NAME`_Wakeup() function without first calling the
*  `$INSTANCE_NAME`_Sleep() or `$INSTANCE_NAME`_SaveConfig() function may
*  produce unexpected behavior.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_RestoreConfig();

    if (`$INSTANCE_NAME`_backup.enableState != 0u)
    {
        /* Enables component's operation */
        `$INSTANCE_NAME`_Resume();
    } /* Left Run Bit in off state if component's block was disabled before */
    else
    {
        /* Clears any pending interrupts */
        `$INSTANCE_NAME`_SR_REG = 0xFFu;
    }
    /* Enables the clock to the entire core of the block */
    `$INSTANCE_NAME`_CR_REG &= (uint8) (~`$INSTANCE_NAME`_CORECLK_DISABLE);
}


/* [] END OF FILE */
