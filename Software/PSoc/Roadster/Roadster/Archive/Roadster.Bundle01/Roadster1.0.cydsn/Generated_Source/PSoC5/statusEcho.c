/*******************************************************************************
* File Name: statusEcho.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "statusEcho.h"

#if !defined(statusEcho_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: statusEcho_Read
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
uint8 statusEcho_Read(void) 
{ 
    return statusEcho_Status;
}


/*******************************************************************************
* Function Name: statusEcho_InterruptEnable
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
void statusEcho_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    statusEcho_Status_Aux_Ctrl |= statusEcho_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: statusEcho_InterruptDisable
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
void statusEcho_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    statusEcho_Status_Aux_Ctrl &= (uint8)(~statusEcho_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: statusEcho_WriteMask
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
void statusEcho_WriteMask(uint8 mask) 
{
    #if(statusEcho_INPUTS < 8u)
    	mask &= ((uint8)(1u << statusEcho_INPUTS) - 1u);
	#endif /* End statusEcho_INPUTS < 8u */
    statusEcho_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: statusEcho_ReadMask
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
uint8 statusEcho_ReadMask(void) 
{
    return statusEcho_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
