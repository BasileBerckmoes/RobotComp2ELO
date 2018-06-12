/*******************************************************************************
* File Name: txBleISR.h
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
#if !defined(CY_ISR_txBleISR_H)
#define CY_ISR_txBleISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void txBleISR_Start(void);
void txBleISR_StartEx(cyisraddress address);
void txBleISR_Stop(void);

CY_ISR_PROTO(txBleISR_Interrupt);

void txBleISR_SetVector(cyisraddress address);
cyisraddress txBleISR_GetVector(void);

void txBleISR_SetPriority(uint8 priority);
uint8 txBleISR_GetPriority(void);

void txBleISR_Enable(void);
uint8 txBleISR_GetState(void);
void txBleISR_Disable(void);

void txBleISR_SetPending(void);
void txBleISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the txBleISR ISR. */
#define txBleISR_INTC_VECTOR            ((reg32 *) txBleISR__INTC_VECT)

/* Address of the txBleISR ISR priority. */
#define txBleISR_INTC_PRIOR             ((reg8 *) txBleISR__INTC_PRIOR_REG)

/* Priority of the txBleISR interrupt. */
#define txBleISR_INTC_PRIOR_NUMBER      txBleISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable txBleISR interrupt. */
#define txBleISR_INTC_SET_EN            ((reg32 *) txBleISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the txBleISR interrupt. */
#define txBleISR_INTC_CLR_EN            ((reg32 *) txBleISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the txBleISR interrupt state to pending. */
#define txBleISR_INTC_SET_PD            ((reg32 *) txBleISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the txBleISR interrupt. */
#define txBleISR_INTC_CLR_PD            ((reg32 *) txBleISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_txBleISR_H */


/* [] END OF FILE */
