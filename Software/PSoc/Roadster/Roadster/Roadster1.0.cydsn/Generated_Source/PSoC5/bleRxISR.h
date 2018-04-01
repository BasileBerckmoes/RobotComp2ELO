/*******************************************************************************
* File Name: bleRxISR.h
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
#if !defined(CY_ISR_bleRxISR_H)
#define CY_ISR_bleRxISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void bleRxISR_Start(void);
void bleRxISR_StartEx(cyisraddress address);
void bleRxISR_Stop(void);

CY_ISR_PROTO(bleRxISR_Interrupt);

void bleRxISR_SetVector(cyisraddress address);
cyisraddress bleRxISR_GetVector(void);

void bleRxISR_SetPriority(uint8 priority);
uint8 bleRxISR_GetPriority(void);

void bleRxISR_Enable(void);
uint8 bleRxISR_GetState(void);
void bleRxISR_Disable(void);

void bleRxISR_SetPending(void);
void bleRxISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the bleRxISR ISR. */
#define bleRxISR_INTC_VECTOR            ((reg32 *) bleRxISR__INTC_VECT)

/* Address of the bleRxISR ISR priority. */
#define bleRxISR_INTC_PRIOR             ((reg8 *) bleRxISR__INTC_PRIOR_REG)

/* Priority of the bleRxISR interrupt. */
#define bleRxISR_INTC_PRIOR_NUMBER      bleRxISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable bleRxISR interrupt. */
#define bleRxISR_INTC_SET_EN            ((reg32 *) bleRxISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the bleRxISR interrupt. */
#define bleRxISR_INTC_CLR_EN            ((reg32 *) bleRxISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the bleRxISR interrupt state to pending. */
#define bleRxISR_INTC_SET_PD            ((reg32 *) bleRxISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the bleRxISR interrupt. */
#define bleRxISR_INTC_CLR_PD            ((reg32 *) bleRxISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_bleRxISR_H */


/* [] END OF FILE */
