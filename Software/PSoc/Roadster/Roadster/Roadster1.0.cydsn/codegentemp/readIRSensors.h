/*******************************************************************************
* File Name: readIRSensors.h
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
#if !defined(CY_ISR_readIRSensors_H)
#define CY_ISR_readIRSensors_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void readIRSensors_Start(void);
void readIRSensors_StartEx(cyisraddress address);
void readIRSensors_Stop(void);

CY_ISR_PROTO(readIRSensors_Interrupt);

void readIRSensors_SetVector(cyisraddress address);
cyisraddress readIRSensors_GetVector(void);

void readIRSensors_SetPriority(uint8 priority);
uint8 readIRSensors_GetPriority(void);

void readIRSensors_Enable(void);
uint8 readIRSensors_GetState(void);
void readIRSensors_Disable(void);

void readIRSensors_SetPending(void);
void readIRSensors_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the readIRSensors ISR. */
#define readIRSensors_INTC_VECTOR            ((reg32 *) readIRSensors__INTC_VECT)

/* Address of the readIRSensors ISR priority. */
#define readIRSensors_INTC_PRIOR             ((reg8 *) readIRSensors__INTC_PRIOR_REG)

/* Priority of the readIRSensors interrupt. */
#define readIRSensors_INTC_PRIOR_NUMBER      readIRSensors__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable readIRSensors interrupt. */
#define readIRSensors_INTC_SET_EN            ((reg32 *) readIRSensors__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the readIRSensors interrupt. */
#define readIRSensors_INTC_CLR_EN            ((reg32 *) readIRSensors__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the readIRSensors interrupt state to pending. */
#define readIRSensors_INTC_SET_PD            ((reg32 *) readIRSensors__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the readIRSensors interrupt. */
#define readIRSensors_INTC_CLR_PD            ((reg32 *) readIRSensors__INTC_CLR_PD_REG)


#endif /* CY_ISR_readIRSensors_H */


/* [] END OF FILE */
