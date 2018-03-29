/*******************************************************************************
* File Name: bleUart_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_bleUart_IntClock_H)
#define CY_CLOCK_bleUart_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void bleUart_IntClock_Start(void) ;
void bleUart_IntClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void bleUart_IntClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void bleUart_IntClock_StandbyPower(uint8 state) ;
void bleUart_IntClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 bleUart_IntClock_GetDividerRegister(void) ;
void bleUart_IntClock_SetModeRegister(uint8 modeBitMask) ;
void bleUart_IntClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 bleUart_IntClock_GetModeRegister(void) ;
void bleUart_IntClock_SetSourceRegister(uint8 clkSource) ;
uint8 bleUart_IntClock_GetSourceRegister(void) ;
#if defined(bleUart_IntClock__CFG3)
void bleUart_IntClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 bleUart_IntClock_GetPhaseRegister(void) ;
#endif /* defined(bleUart_IntClock__CFG3) */

#define bleUart_IntClock_Enable()                       bleUart_IntClock_Start()
#define bleUart_IntClock_Disable()                      bleUart_IntClock_Stop()
#define bleUart_IntClock_SetDivider(clkDivider)         bleUart_IntClock_SetDividerRegister(clkDivider, 1u)
#define bleUart_IntClock_SetDividerValue(clkDivider)    bleUart_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define bleUart_IntClock_SetMode(clkMode)               bleUart_IntClock_SetModeRegister(clkMode)
#define bleUart_IntClock_SetSource(clkSource)           bleUart_IntClock_SetSourceRegister(clkSource)
#if defined(bleUart_IntClock__CFG3)
#define bleUart_IntClock_SetPhase(clkPhase)             bleUart_IntClock_SetPhaseRegister(clkPhase)
#define bleUart_IntClock_SetPhaseValue(clkPhase)        bleUart_IntClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(bleUart_IntClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define bleUart_IntClock_CLKEN              (* (reg8 *) bleUart_IntClock__PM_ACT_CFG)
#define bleUart_IntClock_CLKEN_PTR          ((reg8 *) bleUart_IntClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define bleUart_IntClock_CLKSTBY            (* (reg8 *) bleUart_IntClock__PM_STBY_CFG)
#define bleUart_IntClock_CLKSTBY_PTR        ((reg8 *) bleUart_IntClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define bleUart_IntClock_DIV_LSB            (* (reg8 *) bleUart_IntClock__CFG0)
#define bleUart_IntClock_DIV_LSB_PTR        ((reg8 *) bleUart_IntClock__CFG0)
#define bleUart_IntClock_DIV_PTR            ((reg16 *) bleUart_IntClock__CFG0)

/* Clock MSB divider configuration register. */
#define bleUart_IntClock_DIV_MSB            (* (reg8 *) bleUart_IntClock__CFG1)
#define bleUart_IntClock_DIV_MSB_PTR        ((reg8 *) bleUart_IntClock__CFG1)

/* Mode and source configuration register */
#define bleUart_IntClock_MOD_SRC            (* (reg8 *) bleUart_IntClock__CFG2)
#define bleUart_IntClock_MOD_SRC_PTR        ((reg8 *) bleUart_IntClock__CFG2)

#if defined(bleUart_IntClock__CFG3)
/* Analog clock phase configuration register */
#define bleUart_IntClock_PHASE              (* (reg8 *) bleUart_IntClock__CFG3)
#define bleUart_IntClock_PHASE_PTR          ((reg8 *) bleUart_IntClock__CFG3)
#endif /* defined(bleUart_IntClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define bleUart_IntClock_CLKEN_MASK         bleUart_IntClock__PM_ACT_MSK
#define bleUart_IntClock_CLKSTBY_MASK       bleUart_IntClock__PM_STBY_MSK

/* CFG2 field masks */
#define bleUart_IntClock_SRC_SEL_MSK        bleUart_IntClock__CFG2_SRC_SEL_MASK
#define bleUart_IntClock_MODE_MASK          (~(bleUart_IntClock_SRC_SEL_MSK))

#if defined(bleUart_IntClock__CFG3)
/* CFG3 phase mask */
#define bleUart_IntClock_PHASE_MASK         bleUart_IntClock__CFG3_PHASE_DLY_MASK
#endif /* defined(bleUart_IntClock__CFG3) */

#endif /* CY_CLOCK_bleUart_IntClock_H */


/* [] END OF FILE */