/*******************************************************************************
* File Name: SendBleDataISR.h
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
#if !defined(CY_ISR_SendBleDataISR_H)
#define CY_ISR_SendBleDataISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SendBleDataISR_Start(void);
void SendBleDataISR_StartEx(cyisraddress address);
void SendBleDataISR_Stop(void);

CY_ISR_PROTO(SendBleDataISR_Interrupt);

void SendBleDataISR_SetVector(cyisraddress address);
cyisraddress SendBleDataISR_GetVector(void);

void SendBleDataISR_SetPriority(uint8 priority);
uint8 SendBleDataISR_GetPriority(void);

void SendBleDataISR_Enable(void);
uint8 SendBleDataISR_GetState(void);
void SendBleDataISR_Disable(void);

void SendBleDataISR_SetPending(void);
void SendBleDataISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SendBleDataISR ISR. */
#define SendBleDataISR_INTC_VECTOR            ((reg32 *) SendBleDataISR__INTC_VECT)

/* Address of the SendBleDataISR ISR priority. */
#define SendBleDataISR_INTC_PRIOR             ((reg8 *) SendBleDataISR__INTC_PRIOR_REG)

/* Priority of the SendBleDataISR interrupt. */
#define SendBleDataISR_INTC_PRIOR_NUMBER      SendBleDataISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SendBleDataISR interrupt. */
#define SendBleDataISR_INTC_SET_EN            ((reg32 *) SendBleDataISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SendBleDataISR interrupt. */
#define SendBleDataISR_INTC_CLR_EN            ((reg32 *) SendBleDataISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SendBleDataISR interrupt state to pending. */
#define SendBleDataISR_INTC_SET_PD            ((reg32 *) SendBleDataISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SendBleDataISR interrupt. */
#define SendBleDataISR_INTC_CLR_PD            ((reg32 *) SendBleDataISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_SendBleDataISR_H */


/* [] END OF FILE */
