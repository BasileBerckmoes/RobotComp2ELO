/*******************************************************************************
* File Name: isrUltraSonen.h
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
#if !defined(CY_ISR_isrUltraSonen_H)
#define CY_ISR_isrUltraSonen_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrUltraSonen_Start(void);
void isrUltraSonen_StartEx(cyisraddress address);
void isrUltraSonen_Stop(void);

CY_ISR_PROTO(isrUltraSonen_Interrupt);

void isrUltraSonen_SetVector(cyisraddress address);
cyisraddress isrUltraSonen_GetVector(void);

void isrUltraSonen_SetPriority(uint8 priority);
uint8 isrUltraSonen_GetPriority(void);

void isrUltraSonen_Enable(void);
uint8 isrUltraSonen_GetState(void);
void isrUltraSonen_Disable(void);

void isrUltraSonen_SetPending(void);
void isrUltraSonen_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrUltraSonen ISR. */
#define isrUltraSonen_INTC_VECTOR            ((reg32 *) isrUltraSonen__INTC_VECT)

/* Address of the isrUltraSonen ISR priority. */
#define isrUltraSonen_INTC_PRIOR             ((reg8 *) isrUltraSonen__INTC_PRIOR_REG)

/* Priority of the isrUltraSonen interrupt. */
#define isrUltraSonen_INTC_PRIOR_NUMBER      isrUltraSonen__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrUltraSonen interrupt. */
#define isrUltraSonen_INTC_SET_EN            ((reg32 *) isrUltraSonen__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrUltraSonen interrupt. */
#define isrUltraSonen_INTC_CLR_EN            ((reg32 *) isrUltraSonen__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrUltraSonen interrupt state to pending. */
#define isrUltraSonen_INTC_SET_PD            ((reg32 *) isrUltraSonen__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrUltraSonen interrupt. */
#define isrUltraSonen_INTC_CLR_PD            ((reg32 *) isrUltraSonen__INTC_CLR_PD_REG)


#endif /* CY_ISR_isrUltraSonen_H */


/* [] END OF FILE */
