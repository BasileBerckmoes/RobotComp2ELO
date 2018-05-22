/*******************************************************************************
* File Name: eocJoystickISR.h
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
#if !defined(CY_ISR_eocJoystickISR_H)
#define CY_ISR_eocJoystickISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void eocJoystickISR_Start(void);
void eocJoystickISR_StartEx(cyisraddress address);
void eocJoystickISR_Stop(void);

CY_ISR_PROTO(eocJoystickISR_Interrupt);

void eocJoystickISR_SetVector(cyisraddress address);
cyisraddress eocJoystickISR_GetVector(void);

void eocJoystickISR_SetPriority(uint8 priority);
uint8 eocJoystickISR_GetPriority(void);

void eocJoystickISR_Enable(void);
uint8 eocJoystickISR_GetState(void);
void eocJoystickISR_Disable(void);

void eocJoystickISR_SetPending(void);
void eocJoystickISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the eocJoystickISR ISR. */
#define eocJoystickISR_INTC_VECTOR            ((reg32 *) eocJoystickISR__INTC_VECT)

/* Address of the eocJoystickISR ISR priority. */
#define eocJoystickISR_INTC_PRIOR             ((reg8 *) eocJoystickISR__INTC_PRIOR_REG)

/* Priority of the eocJoystickISR interrupt. */
#define eocJoystickISR_INTC_PRIOR_NUMBER      eocJoystickISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable eocJoystickISR interrupt. */
#define eocJoystickISR_INTC_SET_EN            ((reg32 *) eocJoystickISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the eocJoystickISR interrupt. */
#define eocJoystickISR_INTC_CLR_EN            ((reg32 *) eocJoystickISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the eocJoystickISR interrupt state to pending. */
#define eocJoystickISR_INTC_SET_PD            ((reg32 *) eocJoystickISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the eocJoystickISR interrupt. */
#define eocJoystickISR_INTC_CLR_PD            ((reg32 *) eocJoystickISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_eocJoystickISR_H */


/* [] END OF FILE */
