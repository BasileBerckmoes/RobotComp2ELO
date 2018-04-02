/*******************************************************************************
* File Name: sendBleDataISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <sendBleDataISR.h>
#include "cyapicallbacks.h"

#if !defined(sendBleDataISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START sendBleDataISR_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: sendBleDataISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_Start(void)
{
    /* For all we know the interrupt is active. */
    sendBleDataISR_Disable();

    /* Set the ISR to point to the sendBleDataISR Interrupt. */
    sendBleDataISR_SetVector(&sendBleDataISR_Interrupt);

    /* Set the priority. */
    sendBleDataISR_SetPriority((uint8)sendBleDataISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    sendBleDataISR_Enable();
}


/*******************************************************************************
* Function Name: sendBleDataISR_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    sendBleDataISR_Disable();

    /* Set the ISR to point to the sendBleDataISR Interrupt. */
    sendBleDataISR_SetVector(address);

    /* Set the priority. */
    sendBleDataISR_SetPriority((uint8)sendBleDataISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    sendBleDataISR_Enable();
}


/*******************************************************************************
* Function Name: sendBleDataISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_Stop(void)
{
    /* Disable this interrupt. */
    sendBleDataISR_Disable();

    /* Set the ISR to point to the passive one. */
    sendBleDataISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: sendBleDataISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for sendBleDataISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(sendBleDataISR_Interrupt)
{
    #ifdef sendBleDataISR_INTERRUPT_INTERRUPT_CALLBACK
        sendBleDataISR_Interrupt_InterruptCallback();
    #endif /* sendBleDataISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START sendBleDataISR_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: sendBleDataISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling sendBleDataISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use sendBleDataISR_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)sendBleDataISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: sendBleDataISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress sendBleDataISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)sendBleDataISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: sendBleDataISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling sendBleDataISR_Start or sendBleDataISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after sendBleDataISR_Start or sendBleDataISR_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_SetPriority(uint8 priority)
{
    *sendBleDataISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: sendBleDataISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 sendBleDataISR_GetPriority(void)
{
    uint8 priority;


    priority = *sendBleDataISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: sendBleDataISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_Enable(void)
{
    /* Enable the general interrupt. */
    *sendBleDataISR_INTC_SET_EN = sendBleDataISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: sendBleDataISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 sendBleDataISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*sendBleDataISR_INTC_SET_EN & (uint32)sendBleDataISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: sendBleDataISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_Disable(void)
{
    /* Disable the general interrupt. */
    *sendBleDataISR_INTC_CLR_EN = sendBleDataISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: sendBleDataISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void sendBleDataISR_SetPending(void)
{
    *sendBleDataISR_INTC_SET_PD = sendBleDataISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: sendBleDataISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void sendBleDataISR_ClearPending(void)
{
    *sendBleDataISR_INTC_CLR_PD = sendBleDataISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
