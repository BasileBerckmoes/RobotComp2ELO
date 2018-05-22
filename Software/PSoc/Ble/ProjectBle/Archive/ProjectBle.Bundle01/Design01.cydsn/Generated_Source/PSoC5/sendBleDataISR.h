/*******************************************************************************
* File Name: sendBleDataISR.h
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
#if !defined(CY_ISR_sendBleDataISR_H)
#define CY_ISR_sendBleDataISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void sendBleDataISR_Start(void);
void sendBleDataISR_StartEx(cyisraddress address);
void sendBleDataISR_Stop(void);

CY_ISR_PROTO(sendBleDataISR_Interrupt);

void sendBleDataISR_SetVector(cyisraddress address);
cyisraddress sendBleDataISR_GetVector(void);

void sendBleDataISR_SetPriority(uint8 priority);
uint8 sendBleDataISR_GetPriority(void);

void sendBleDataISR_Enable(void);
uint8 sendBleDataISR_GetState(void);
void sendBleDataISR_Disable(void);

void sendBleDataISR_SetPending(void);
void sendBleDataISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the sendBleDataISR ISR. */
#define sendBleDataISR_INTC_VECTOR            ((reg32 *) sendBleDataISR__INTC_VECT)

/* Address of the sendBleDataISR ISR priority. */
#define sendBleDataISR_INTC_PRIOR             ((reg8 *) sendBleDataISR__INTC_PRIOR_REG)

/* Priority of the sendBleDataISR interrupt. */
#define sendBleDataISR_INTC_PRIOR_NUMBER      sendBleDataISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable sendBleDataISR interrupt. */
#define sendBleDataISR_INTC_SET_EN            ((reg32 *) sendBleDataISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the sendBleDataISR interrupt. */
#define sendBleDataISR_INTC_CLR_EN            ((reg32 *) sendBleDataISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the sendBleDataISR interrupt state to pending. */
#define sendBleDataISR_INTC_SET_PD            ((reg32 *) sendBleDataISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the sendBleDataISR interrupt. */
#define sendBleDataISR_INTC_CLR_PD            ((reg32 *) sendBleDataISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_sendBleDataISR_H */


/* [] END OF FILE */
