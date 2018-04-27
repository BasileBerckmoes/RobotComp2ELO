/*******************************************************************************
* File Name: DraaiRichtingISR.h
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
#if !defined(CY_ISR_DraaiRichtingISR_H)
#define CY_ISR_DraaiRichtingISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void DraaiRichtingISR_Start(void);
void DraaiRichtingISR_StartEx(cyisraddress address);
void DraaiRichtingISR_Stop(void);

CY_ISR_PROTO(DraaiRichtingISR_Interrupt);

void DraaiRichtingISR_SetVector(cyisraddress address);
cyisraddress DraaiRichtingISR_GetVector(void);

void DraaiRichtingISR_SetPriority(uint8 priority);
uint8 DraaiRichtingISR_GetPriority(void);

void DraaiRichtingISR_Enable(void);
uint8 DraaiRichtingISR_GetState(void);
void DraaiRichtingISR_Disable(void);

void DraaiRichtingISR_SetPending(void);
void DraaiRichtingISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the DraaiRichtingISR ISR. */
#define DraaiRichtingISR_INTC_VECTOR            ((reg32 *) DraaiRichtingISR__INTC_VECT)

/* Address of the DraaiRichtingISR ISR priority. */
#define DraaiRichtingISR_INTC_PRIOR             ((reg8 *) DraaiRichtingISR__INTC_PRIOR_REG)

/* Priority of the DraaiRichtingISR interrupt. */
#define DraaiRichtingISR_INTC_PRIOR_NUMBER      DraaiRichtingISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable DraaiRichtingISR interrupt. */
#define DraaiRichtingISR_INTC_SET_EN            ((reg32 *) DraaiRichtingISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the DraaiRichtingISR interrupt. */
#define DraaiRichtingISR_INTC_CLR_EN            ((reg32 *) DraaiRichtingISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the DraaiRichtingISR interrupt state to pending. */
#define DraaiRichtingISR_INTC_SET_PD            ((reg32 *) DraaiRichtingISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the DraaiRichtingISR interrupt. */
#define DraaiRichtingISR_INTC_CLR_PD            ((reg32 *) DraaiRichtingISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_DraaiRichtingISR_H */


/* [] END OF FILE */
