/*******************************************************************************
* File Name: rxPuttyISR.h
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
#if !defined(CY_ISR_rxPuttyISR_H)
#define CY_ISR_rxPuttyISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void rxPuttyISR_Start(void);
void rxPuttyISR_StartEx(cyisraddress address);
void rxPuttyISR_Stop(void);

CY_ISR_PROTO(rxPuttyISR_Interrupt);

void rxPuttyISR_SetVector(cyisraddress address);
cyisraddress rxPuttyISR_GetVector(void);

void rxPuttyISR_SetPriority(uint8 priority);
uint8 rxPuttyISR_GetPriority(void);

void rxPuttyISR_Enable(void);
uint8 rxPuttyISR_GetState(void);
void rxPuttyISR_Disable(void);

void rxPuttyISR_SetPending(void);
void rxPuttyISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the rxPuttyISR ISR. */
#define rxPuttyISR_INTC_VECTOR            ((reg32 *) rxPuttyISR__INTC_VECT)

/* Address of the rxPuttyISR ISR priority. */
#define rxPuttyISR_INTC_PRIOR             ((reg8 *) rxPuttyISR__INTC_PRIOR_REG)

/* Priority of the rxPuttyISR interrupt. */
#define rxPuttyISR_INTC_PRIOR_NUMBER      rxPuttyISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable rxPuttyISR interrupt. */
#define rxPuttyISR_INTC_SET_EN            ((reg32 *) rxPuttyISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the rxPuttyISR interrupt. */
#define rxPuttyISR_INTC_CLR_EN            ((reg32 *) rxPuttyISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the rxPuttyISR interrupt state to pending. */
#define rxPuttyISR_INTC_SET_PD            ((reg32 *) rxPuttyISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the rxPuttyISR interrupt. */
#define rxPuttyISR_INTC_CLR_PD            ((reg32 *) rxPuttyISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_rxPuttyISR_H */


/* [] END OF FILE */
