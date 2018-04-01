/*******************************************************************************
* File Name: bleRxISR1.h
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
#if !defined(CY_ISR_bleRxISR1_H)
#define CY_ISR_bleRxISR1_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void bleRxISR1_Start(void);
void bleRxISR1_StartEx(cyisraddress address);
void bleRxISR1_Stop(void);

CY_ISR_PROTO(bleRxISR1_Interrupt);

void bleRxISR1_SetVector(cyisraddress address);
cyisraddress bleRxISR1_GetVector(void);

void bleRxISR1_SetPriority(uint8 priority);
uint8 bleRxISR1_GetPriority(void);

void bleRxISR1_Enable(void);
uint8 bleRxISR1_GetState(void);
void bleRxISR1_Disable(void);

void bleRxISR1_SetPending(void);
void bleRxISR1_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the bleRxISR1 ISR. */
#define bleRxISR1_INTC_VECTOR            ((reg32 *) bleRxISR1__INTC_VECT)

/* Address of the bleRxISR1 ISR priority. */
#define bleRxISR1_INTC_PRIOR             ((reg8 *) bleRxISR1__INTC_PRIOR_REG)

/* Priority of the bleRxISR1 interrupt. */
#define bleRxISR1_INTC_PRIOR_NUMBER      bleRxISR1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable bleRxISR1 interrupt. */
#define bleRxISR1_INTC_SET_EN            ((reg32 *) bleRxISR1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the bleRxISR1 interrupt. */
#define bleRxISR1_INTC_CLR_EN            ((reg32 *) bleRxISR1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the bleRxISR1 interrupt state to pending. */
#define bleRxISR1_INTC_SET_PD            ((reg32 *) bleRxISR1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the bleRxISR1 interrupt. */
#define bleRxISR1_INTC_CLR_PD            ((reg32 *) bleRxISR1__INTC_CLR_PD_REG)


#endif /* CY_ISR_bleRxISR1_H */


/* [] END OF FILE */
