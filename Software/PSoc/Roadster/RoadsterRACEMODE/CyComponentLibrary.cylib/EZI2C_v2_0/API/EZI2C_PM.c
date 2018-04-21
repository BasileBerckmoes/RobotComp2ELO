/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the API for the proper switching to/from the low power
*  modes.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

`$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    `$INSTANCE_NAME`_DISABLED,
    `$INSTANCE_NAME`_DEFAULT_XCFG,
    `$INSTANCE_NAME`_DEFAULT_ADDR,
    `$INSTANCE_NAME`_DEFAULT_CFG,
    `$INSTANCE_NAME`_DEFAULT_CLKDIV1,
    `$INSTANCE_NAME`_DEFAULT_CLKDIV2
};

#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    volatile uint8 `$INSTANCE_NAME`_wakeupSource;
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  The Enable wakeup from Sleep Mode selection influences this function
*  implementation:
*   Unchecked: Stores the component non-retention configuration registers.
*   Checked:   Enables backup regulator of the I2C hardware. If a transaction
*              intended for component executes during this function call,
*              it waits until the current transaction is completed and
*              I2C hardware is ready to go to sleep mode. All subsequent
*              I2C traffic is NAKed until the device is put to sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_backup - The non-retention registers are saved to.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    uint8 interruptState;
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

    /* Store component configuration into backup structure */
    `$INSTANCE_NAME`_backup.cfg     = `$INSTANCE_NAME`_CFG_REG;
    `$INSTANCE_NAME`_backup.xcfg    = `$INSTANCE_NAME`_XCFG_REG;
    `$INSTANCE_NAME`_backup.adr     = `$INSTANCE_NAME`_ADDR_REG;
    `$INSTANCE_NAME`_backup.clkDiv1 = `$INSTANCE_NAME`_CLKDIV1_REG;
    `$INSTANCE_NAME`_backup.clkDiv2 = `$INSTANCE_NAME`_CLKDIV2_REG;

#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    /* Enable I2C backup regulator */
    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_PWRSYS_CR1_REG |= `$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP;
    CyExitCriticalSection(interruptState);

    /* Wait for completion of the current transaction. The following
    * transactions have to be NACKed until the device enters the low power mode.
    * After a wakeup, the force NACK bit is cleared automatically.
    */
    `$INSTANCE_NAME`_XCFG_REG |= `$INSTANCE_NAME`_XCFG_FORCE_NACK;
    while (0u == (`$INSTANCE_NAME`_XCFG_REG & `$INSTANCE_NAME`_XCFG_SLEEP_READY))
    {
    }

     /* Setup wakeup interrupt */
    `$INSTANCE_NAME`_DisableInt();
    `$INSTANCE_NAME`_wakeupSource = 0u; /* Clear wakeup event */
    (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_WAKEUP_ISR);
    `$INSTANCE_NAME`_EnableInt();
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  The Enable wakeup from Sleep Mode selection influences this function
*  implementation:
*   Unchecked: Restores the component non-retention configuration registers
*              to the state they were in before I2C_Sleep() or I2C_SaveConfig()
*              was called.
*   Checked:   Disables the backup regulator of the I2C hardware. Sets up the
*              regular component interrupt handler and generates the component
*              interrupt if it was wake up source to release the bus and
*              continue in-coming I2C transaction.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_backup - the non-retention registers are restored from.
*
* Reentrant:
*  No.
*
* Side Effects:
*  Calling this function before `$INSTANCE_NAME`_SaveConfig() or
*  `$INSTANCE_NAME`_Sleep() may produce unexpected behavior.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    uint8 intState;

    if (0u != (`$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP & `$INSTANCE_NAME`_PWRSYS_CR1_REG))
    /* Exit from Sleep */
    {
        /* Disable I2C backup regulator */
        intState = CyEnterCriticalSection();
        `$INSTANCE_NAME`_PWRSYS_CR1_REG &= (uint8) ~`$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP;
        CyExitCriticalSection(intState);
    }
    else /* Exit from Hibernate (bit is cleared) or wakeup disabled */
    {
    #if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
        /* Disable power to I2C block before register restore */
        intState = CyEnterCriticalSection();
        `$INSTANCE_NAME`_PM_ACT_CFG_REG  &= (uint8) ~`$INSTANCE_NAME`_ACT_PWR_EN;
        `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8) ~`$INSTANCE_NAME`_STBY_PWR_EN;
        CyExitCriticalSection(intState);

        /* Enable component after restore complete */
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED;
    #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

        /* Restore component registers: Hibernate disable power */
        `$INSTANCE_NAME`_CFG_REG     = `$INSTANCE_NAME`_backup.cfg;
        `$INSTANCE_NAME`_XCFG_REG    = `$INSTANCE_NAME`_backup.xcfg;
        `$INSTANCE_NAME`_ADDR_REG    = `$INSTANCE_NAME`_backup.adr;
        `$INSTANCE_NAME`_CLKDIV1_REG = `$INSTANCE_NAME`_backup.clkDiv1;
        `$INSTANCE_NAME`_CLKDIV2_REG = `$INSTANCE_NAME`_backup.clkDiv2;
    }

#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    /* Set I2C interrupt to be pending if component is source of wake up */
    `$INSTANCE_NAME`_DisableInt();
    (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_ISR);
    if (0u != `$INSTANCE_NAME`_wakeupSource)
    {
        /* Generate interrupt to release I2C bus */
        (void) CyIntSetPending(`$INSTANCE_NAME`_ISR_NUMBER);
    }
    `$INSTANCE_NAME`_EnableInt();
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred method to prepare the component before device enters
*  sleep mode.
*  The Enable wakeup from Sleep Mode selection influences this function
*  implementation:
*   Unchecked: Checks current EZI2C component state, saves it, and disables the
*              component by calling EZI2C_Stop() if it is currently enabled.
*              EZI2C_SaveConfig() is then called to save the component
*              non-retention configuration registers.
*   Checked:   If a transaction intended for component is in progress during
*              this function call, it waits until the current transaction is
*              completed. All subsequent I2C traffic intended for component is
*              NAKed until the device is put to sleep mode. The address match
*              event wakes up the device.
*
*  Call the EZI2C_Sleep() function before calling the CyPmSleep() or the
*  CyPmHibernate() function. Refer to the PSoC Creator System Reference Guide
*  for more information about power-management functions.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_backup - The non retention registers are saved to. Changed
*  by `$INSTANCE_NAME`_SaveConfig() function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    /* Do not re-enable component in `$INSTANCE_NAME`_Wakeup(). It remains enabled as it is wakeup source */
    `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_DISABLED;
#else
    /* Store component state enabled or disable to restore after wakeup */
    `$INSTANCE_NAME`_backup.enableState = (`$INSTANCE_NAME`_PM_ACT_CFG_REG & `$INSTANCE_NAME`_ACT_PWR_EN);

    if (0u != `$INSTANCE_NAME`_backup.enableState)
    {
        /* Disable component before enter Sleep */
        `$INSTANCE_NAME`_Stop();
    }
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

    `$INSTANCE_NAME`_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred method to prepare the component for active mode
*  operation (when device exits sleep mode).
*  The Enable wakeup from Sleep Mode selection influences this function
*  implementation:
*   Unchecked: Restores the component non-retention configuration registers
*              by calling EZI2C_RestoreConfig(). If the component was enabled
*              before the EZI2C_Sleep() function was called, EZI2C_Wakeup()
*              re-enables it.
*   Checked:   Disables the backup regulator of I2C hardware. The incoming
*              transaction continues as soon as the regular EZI2C interrupt
*              handler is set up (global interrupts has to be  enabled to
*              service EZI2C component interrupt).
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_backup - The non retention registers are restored from.
*
* Reentrant:
*  No.
*
* Side Effects:
*  Calling this function before `$INSTANCE_NAME`_SaveConfig() or
*  `$INSTANCE_NAME`_Sleep() will lead to unpredictable results.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_RestoreConfig();

    if (0u != `$INSTANCE_NAME`_backup.enableState)
    {
        /* Enable component as it was enabled before Sleep */
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
