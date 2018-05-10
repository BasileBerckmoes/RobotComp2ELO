/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the power management source code to API for the
*  ILO Trim component.
*
* Note:
*  None
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"
static `$INSTANCE_NAME`_backupStruct `$INSTANCE_NAME`_backup;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    #if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
		/* Backup non retention registers, interrupt mask and capture counter */
        `$INSTANCE_NAME`_backup.timerCapture = CY_GET_REG8(`$INSTANCE_NAME`_CAPTURE_PTR);
		/* Backup the enable state of the Timer component */
        `$INSTANCE_NAME`_backup.timerControlRegister = (uint8)`$INSTANCE_NAME`_CONTROL_REG;
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{   
    #if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
        /* Restore the UDB non-rentention registers for PSoC5A */
        CY_SET_REG8(`$INSTANCE_NAME`_CAPTURE_PTR, `$INSTANCE_NAME`_backup.timerCapture);
		/* Restore the enable state of the Timer component */
        `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_backup.timerControlRegister;
    #endif /* Restore non retention registers in the UDB implementation only */
}


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
* Global variables:
*  `$INSTANCE_NAME`_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
	uint8 enState;
	
	/* Back up enable state from the Timer control register */
	#if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
		enState = (uint8)(`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_CTRL_ENABLE);
	#else
		#if (CY_PSOC4)
			enState = (uint8)(`$INSTANCE_NAME`_TCPWM_BLOCK_CONTROL_REG & `$INSTANCE_NAME`_TCPWM_MASK);
		#else
			enState = (uint8)(`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_CTRL_ENABLE);
		#endif /* End of PSoC 3 and PSOC 5LP code*/
	#endif /* End of Fixed Function code */
    /* Save Counter's enable state */
    if(enState == `$INSTANCE_NAME`_CTRL_ENABLE)
    {
        /* Timer is enabled */
        `$INSTANCE_NAME`_backup.timerEnableState = 1u;
    }
    else
    {
        /* Timer is disabled */
        `$INSTANCE_NAME`_backup.timerEnableState = 0u;
    }
    `$INSTANCE_NAME`_Stop();
    `$INSTANCE_NAME`_SaveConfig();
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
* Global variables:
*  `$INSTANCE_NAME`_backup.TimerEnableState:  Is used to restore the enable 
*  state of block on wakeup from sleep mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_RestoreConfig();
	
    if(`$INSTANCE_NAME`_backup.timerEnableState == 1u)
    {     /* Enable Timer's operation */
        #if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
			/* Enable UDB Timer */
			`$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_ENABLE;
		#else
			#if (CY_PSOC4)
				`$INSTANCE_NAME`_TCPWM_Enable();
			#else
				/* Enable FF Timer */
				/* Clear all bits but the enable bit (if it's already set) for Timer operation */
			    `$INSTANCE_NAME`_CONTROL_REG &= `$INSTANCE_NAME`_CTRL_ENABLE;
				
				/* CONTROL3 register exists only in PSoC3 OR PSoC5LP */
			    `$INSTANCE_NAME`_CONTROL3_REG &= (uint8)(~`$INSTANCE_NAME`_CTRL_MODE_MASK);
				
				`$INSTANCE_NAME`_GLOBAL_ENABLE |= `$INSTANCE_NAME`_BLOCK_EN_MASK;
		        `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE |= `$INSTANCE_NAME`_BLOCK_STBY_EN_MASK;

				`$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_ENABLE;
			#endif /* End of PSoC 3 and PSOC 5LP code*/
		#endif /* End of Fixed Function code */
    } /* Do nothing if Timer was disabled before */
}


/* [] END OF FILE */
