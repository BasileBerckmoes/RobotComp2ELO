/*******************************************************************************
* File Name: isr_UltraSoon.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_UltraSoon_H)
#define CY_ISR_isr_UltraSoon_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_UltraSoon_Start(void);
void isr_UltraSoon_StartEx(cyisraddress address);
void isr_UltraSoon_Stop(void);

CY_ISR_PROTO(isr_UltraSoon_Interrupt);

void isr_UltraSoon_SetVector(cyisraddress address);
cyisraddress isr_UltraSoon_GetVector(void);

void isr_UltraSoon_SetPriority(uint8 priority);
uint8 isr_UltraSoon_GetPriority(void);

void isr_UltraSoon_Enable(void);
uint8 isr_UltraSoon_GetState(void);
void isr_UltraSoon_Disable(void);

void isr_UltraSoon_SetPending(void);
void isr_UltraSoon_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_UltraSoon ISR. */
#define isr_UltraSoon_INTC_VECTOR            ((reg32 *) isr_UltraSoon__INTC_VECT)

/* Address of the isr_UltraSoon ISR priority. */
#define isr_UltraSoon_INTC_PRIOR             ((reg8 *) isr_UltraSoon__INTC_PRIOR_REG)

/* Priority of the isr_UltraSoon interrupt. */
#define isr_UltraSoon_INTC_PRIOR_NUMBER      isr_UltraSoon__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_UltraSoon interrupt. */
#define isr_UltraSoon_INTC_SET_EN            ((reg32 *) isr_UltraSoon__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_UltraSoon interrupt. */
#define isr_UltraSoon_INTC_CLR_EN            ((reg32 *) isr_UltraSoon__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_UltraSoon interrupt state to pending. */
#define isr_UltraSoon_INTC_SET_PD            ((reg32 *) isr_UltraSoon__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_UltraSoon interrupt. */
#define isr_UltraSoon_INTC_CLR_PD            ((reg32 *) isr_UltraSoon__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_UltraSoon_H */


/* [] END OF FILE */
