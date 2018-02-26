/*******************************************************************************
* File Name: CharLCD_1_LCDPort.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CharLCD_1_LCDPort_ALIASES_H) /* Pins CharLCD_1_LCDPort_ALIASES_H */
#define CY_PINS_CharLCD_1_LCDPort_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define CharLCD_1_LCDPort_0			(CharLCD_1_LCDPort__0__PC)
#define CharLCD_1_LCDPort_0_INTR	((uint16)((uint16)0x0001u << CharLCD_1_LCDPort__0__SHIFT))

#define CharLCD_1_LCDPort_1			(CharLCD_1_LCDPort__1__PC)
#define CharLCD_1_LCDPort_1_INTR	((uint16)((uint16)0x0001u << CharLCD_1_LCDPort__1__SHIFT))

#define CharLCD_1_LCDPort_2			(CharLCD_1_LCDPort__2__PC)
#define CharLCD_1_LCDPort_2_INTR	((uint16)((uint16)0x0001u << CharLCD_1_LCDPort__2__SHIFT))

#define CharLCD_1_LCDPort_3			(CharLCD_1_LCDPort__3__PC)
#define CharLCD_1_LCDPort_3_INTR	((uint16)((uint16)0x0001u << CharLCD_1_LCDPort__3__SHIFT))

#define CharLCD_1_LCDPort_4			(CharLCD_1_LCDPort__4__PC)
#define CharLCD_1_LCDPort_4_INTR	((uint16)((uint16)0x0001u << CharLCD_1_LCDPort__4__SHIFT))

#define CharLCD_1_LCDPort_5			(CharLCD_1_LCDPort__5__PC)
#define CharLCD_1_LCDPort_5_INTR	((uint16)((uint16)0x0001u << CharLCD_1_LCDPort__5__SHIFT))

#define CharLCD_1_LCDPort_6			(CharLCD_1_LCDPort__6__PC)
#define CharLCD_1_LCDPort_6_INTR	((uint16)((uint16)0x0001u << CharLCD_1_LCDPort__6__SHIFT))

#define CharLCD_1_LCDPort_INTR_ALL	 ((uint16)(CharLCD_1_LCDPort_0_INTR| CharLCD_1_LCDPort_1_INTR| CharLCD_1_LCDPort_2_INTR| CharLCD_1_LCDPort_3_INTR| CharLCD_1_LCDPort_4_INTR| CharLCD_1_LCDPort_5_INTR| CharLCD_1_LCDPort_6_INTR))

#endif /* End Pins CharLCD_1_LCDPort_ALIASES_H */


/* [] END OF FILE */
