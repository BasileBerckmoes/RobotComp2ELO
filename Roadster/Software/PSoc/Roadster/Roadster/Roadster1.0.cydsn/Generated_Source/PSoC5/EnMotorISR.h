/*******************************************************************************
* File Name: EnMotorISR.h
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
#if !defined(CY_ISR_EnMotorISR_H)
#define CY_ISR_EnMotorISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void EnMotorISR_Start(void);
void EnMotorISR_StartEx(cyisraddress address);
void EnMotorISR_Stop(void);

CY_ISR_PROTO(EnMotorISR_Interrupt);

void EnMotorISR_SetVector(cyisraddress address);
cyisraddress EnMotorISR_GetVector(void);

void EnMotorISR_SetPriority(uint8 priority);
uint8 EnMotorISR_GetPriority(void);

void EnMotorISR_Enable(void);
uint8 EnMotorISR_GetState(void);
void EnMotorISR_Disable(void);

void EnMotorISR_SetPending(void);
void EnMotorISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the EnMotorISR ISR. */
#define EnMotorISR_INTC_VECTOR            ((reg32 *) EnMotorISR__INTC_VECT)

/* Address of the EnMotorISR ISR priority. */
#define EnMotorISR_INTC_PRIOR             ((reg8 *) EnMotorISR__INTC_PRIOR_REG)

/* Priority of the EnMotorISR interrupt. */
#define EnMotorISR_INTC_PRIOR_NUMBER      EnMotorISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable EnMotorISR interrupt. */
#define EnMotorISR_INTC_SET_EN            ((reg32 *) EnMotorISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the EnMotorISR interrupt. */
#define EnMotorISR_INTC_CLR_EN            ((reg32 *) EnMotorISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the EnMotorISR interrupt state to pending. */
#define EnMotorISR_INTC_SET_PD            ((reg32 *) EnMotorISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the EnMotorISR interrupt. */
#define EnMotorISR_INTC_CLR_PD            ((reg32 *) EnMotorISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_EnMotorISR_H */


/* [] END OF FILE */
