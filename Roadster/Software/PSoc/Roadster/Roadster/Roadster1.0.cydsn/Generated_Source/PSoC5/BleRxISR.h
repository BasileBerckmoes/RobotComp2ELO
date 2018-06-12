/*******************************************************************************
* File Name: BleRxISR.h
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
#if !defined(CY_ISR_BleRxISR_H)
#define CY_ISR_BleRxISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void BleRxISR_Start(void);
void BleRxISR_StartEx(cyisraddress address);
void BleRxISR_Stop(void);

CY_ISR_PROTO(BleRxISR_Interrupt);

void BleRxISR_SetVector(cyisraddress address);
cyisraddress BleRxISR_GetVector(void);

void BleRxISR_SetPriority(uint8 priority);
uint8 BleRxISR_GetPriority(void);

void BleRxISR_Enable(void);
uint8 BleRxISR_GetState(void);
void BleRxISR_Disable(void);

void BleRxISR_SetPending(void);
void BleRxISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the BleRxISR ISR. */
#define BleRxISR_INTC_VECTOR            ((reg32 *) BleRxISR__INTC_VECT)

/* Address of the BleRxISR ISR priority. */
#define BleRxISR_INTC_PRIOR             ((reg8 *) BleRxISR__INTC_PRIOR_REG)

/* Priority of the BleRxISR interrupt. */
#define BleRxISR_INTC_PRIOR_NUMBER      BleRxISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable BleRxISR interrupt. */
#define BleRxISR_INTC_SET_EN            ((reg32 *) BleRxISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the BleRxISR interrupt. */
#define BleRxISR_INTC_CLR_EN            ((reg32 *) BleRxISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the BleRxISR interrupt state to pending. */
#define BleRxISR_INTC_SET_PD            ((reg32 *) BleRxISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the BleRxISR interrupt. */
#define BleRxISR_INTC_CLR_PD            ((reg32 *) BleRxISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_BleRxISR_H */


/* [] END OF FILE */
