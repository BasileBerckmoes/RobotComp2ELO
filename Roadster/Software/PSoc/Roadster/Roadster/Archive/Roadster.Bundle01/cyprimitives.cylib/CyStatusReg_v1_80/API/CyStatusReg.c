/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if !defined(`$INSTANCE_NAME`_`$stsRegReplcStr`_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`
{ 
    return `$INSTANCE_NAME`_Status;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InterruptEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_InterruptEnable")`
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_Status_Aux_Ctrl |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InterruptDisable(void) `=ReentrantKeil($INSTANCE_NAME . "_InterruptDisable")`
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_Status_Aux_Ctrl &= (uint8)(~`$INSTANCE_NAME`_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteMask(uint8 mask) `=ReentrantKeil($INSTANCE_NAME . "_WriteMask")`
{
    #if(`$INSTANCE_NAME`_INPUTS < 8u)
    	mask &= (uint8)((((uint8)1u) << `$INSTANCE_NAME`_INPUTS) - 1u);
	#endif /* End `$INSTANCE_NAME`_INPUTS < 8u */
    `$INSTANCE_NAME`_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadMask(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadMask")`
{
    return `$INSTANCE_NAME`_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
