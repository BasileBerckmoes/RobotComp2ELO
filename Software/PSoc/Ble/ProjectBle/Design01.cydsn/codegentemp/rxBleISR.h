/*******************************************************************************
* File Name: rxBleISR.h
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
#if !defined(CY_ISR_rxBleISR_H)
#define CY_ISR_rxBleISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void rxBleISR_Start(void);
void rxBleISR_StartEx(cyisraddress address);
void rxBleISR_Stop(void);

CY_ISR_PROTO(rxBleISR_Interrupt);

void rxBleISR_SetVector(cyisraddress address);
cyisraddress rxBleISR_GetVector(void);

void rxBleISR_SetPriority(uint8 priority);
uint8 rxBleISR_GetPriority(void);

void rxBleISR_Enable(void);
uint8 rxBleISR_GetState(void);
void rxBleISR_Disable(void);

void rxBleISR_SetPending(void);
void rxBleISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the rxBleISR ISR. */
#define rxBleISR_INTC_VECTOR            ((reg32 *) rxBleISR__INTC_VECT)

/* Address of the rxBleISR ISR priority. */
#define rxBleISR_INTC_PRIOR             ((reg8 *) rxBleISR__INTC_PRIOR_REG)

/* Priority of the rxBleISR interrupt. */
#define rxBleISR_INTC_PRIOR_NUMBER      rxBleISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable rxBleISR interrupt. */
#define rxBleISR_INTC_SET_EN            ((reg32 *) rxBleISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the rxBleISR interrupt. */
#define rxBleISR_INTC_CLR_EN            ((reg32 *) rxBleISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the rxBleISR interrupt state to pending. */
#define rxBleISR_INTC_SET_PD            ((reg32 *) rxBleISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the rxBleISR interrupt. */
#define rxBleISR_INTC_CLR_PD            ((reg32 *) rxBleISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_rxBleISR_H */


/* [] END OF FILE */
