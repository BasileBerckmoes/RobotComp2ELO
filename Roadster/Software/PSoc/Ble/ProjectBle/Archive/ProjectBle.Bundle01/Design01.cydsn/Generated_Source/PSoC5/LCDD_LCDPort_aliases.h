/*******************************************************************************
* File Name: LCDD_LCDPort.h  
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

#if !defined(CY_PINS_LCDD_LCDPort_ALIASES_H) /* Pins LCDD_LCDPort_ALIASES_H */
#define CY_PINS_LCDD_LCDPort_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define LCDD_LCDPort_0			(LCDD_LCDPort__0__PC)
#define LCDD_LCDPort_0_INTR	((uint16)((uint16)0x0001u << LCDD_LCDPort__0__SHIFT))

#define LCDD_LCDPort_1			(LCDD_LCDPort__1__PC)
#define LCDD_LCDPort_1_INTR	((uint16)((uint16)0x0001u << LCDD_LCDPort__1__SHIFT))

#define LCDD_LCDPort_2			(LCDD_LCDPort__2__PC)
#define LCDD_LCDPort_2_INTR	((uint16)((uint16)0x0001u << LCDD_LCDPort__2__SHIFT))

#define LCDD_LCDPort_3			(LCDD_LCDPort__3__PC)
#define LCDD_LCDPort_3_INTR	((uint16)((uint16)0x0001u << LCDD_LCDPort__3__SHIFT))

#define LCDD_LCDPort_4			(LCDD_LCDPort__4__PC)
#define LCDD_LCDPort_4_INTR	((uint16)((uint16)0x0001u << LCDD_LCDPort__4__SHIFT))

#define LCDD_LCDPort_5			(LCDD_LCDPort__5__PC)
#define LCDD_LCDPort_5_INTR	((uint16)((uint16)0x0001u << LCDD_LCDPort__5__SHIFT))

#define LCDD_LCDPort_6			(LCDD_LCDPort__6__PC)
#define LCDD_LCDPort_6_INTR	((uint16)((uint16)0x0001u << LCDD_LCDPort__6__SHIFT))

#define LCDD_LCDPort_INTR_ALL	 ((uint16)(LCDD_LCDPort_0_INTR| LCDD_LCDPort_1_INTR| LCDD_LCDPort_2_INTR| LCDD_LCDPort_3_INTR| LCDD_LCDPort_4_INTR| LCDD_LCDPort_5_INTR| LCDD_LCDPort_6_INTR))

#endif /* End Pins LCDD_LCDPort_ALIASES_H */


/* [] END OF FILE */
