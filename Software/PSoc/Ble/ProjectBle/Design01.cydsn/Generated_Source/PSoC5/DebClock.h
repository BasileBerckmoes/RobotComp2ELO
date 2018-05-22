/*******************************************************************************
* File Name: DebClock.h
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

#if !defined(CY_CLOCK_DebClock_H)
#define CY_CLOCK_DebClock_H

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

void DebClock_Start(void) ;
void DebClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DebClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DebClock_StandbyPower(uint8 state) ;
void DebClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DebClock_GetDividerRegister(void) ;
void DebClock_SetModeRegister(uint8 modeBitMask) ;
void DebClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 DebClock_GetModeRegister(void) ;
void DebClock_SetSourceRegister(uint8 clkSource) ;
uint8 DebClock_GetSourceRegister(void) ;
#if defined(DebClock__CFG3)
void DebClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 DebClock_GetPhaseRegister(void) ;
#endif /* defined(DebClock__CFG3) */

#define DebClock_Enable()                       DebClock_Start()
#define DebClock_Disable()                      DebClock_Stop()
#define DebClock_SetDivider(clkDivider)         DebClock_SetDividerRegister(clkDivider, 1u)
#define DebClock_SetDividerValue(clkDivider)    DebClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define DebClock_SetMode(clkMode)               DebClock_SetModeRegister(clkMode)
#define DebClock_SetSource(clkSource)           DebClock_SetSourceRegister(clkSource)
#if defined(DebClock__CFG3)
#define DebClock_SetPhase(clkPhase)             DebClock_SetPhaseRegister(clkPhase)
#define DebClock_SetPhaseValue(clkPhase)        DebClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(DebClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DebClock_CLKEN              (* (reg8 *) DebClock__PM_ACT_CFG)
#define DebClock_CLKEN_PTR          ((reg8 *) DebClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DebClock_CLKSTBY            (* (reg8 *) DebClock__PM_STBY_CFG)
#define DebClock_CLKSTBY_PTR        ((reg8 *) DebClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DebClock_DIV_LSB            (* (reg8 *) DebClock__CFG0)
#define DebClock_DIV_LSB_PTR        ((reg8 *) DebClock__CFG0)
#define DebClock_DIV_PTR            ((reg16 *) DebClock__CFG0)

/* Clock MSB divider configuration register. */
#define DebClock_DIV_MSB            (* (reg8 *) DebClock__CFG1)
#define DebClock_DIV_MSB_PTR        ((reg8 *) DebClock__CFG1)

/* Mode and source configuration register */
#define DebClock_MOD_SRC            (* (reg8 *) DebClock__CFG2)
#define DebClock_MOD_SRC_PTR        ((reg8 *) DebClock__CFG2)

#if defined(DebClock__CFG3)
/* Analog clock phase configuration register */
#define DebClock_PHASE              (* (reg8 *) DebClock__CFG3)
#define DebClock_PHASE_PTR          ((reg8 *) DebClock__CFG3)
#endif /* defined(DebClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DebClock_CLKEN_MASK         DebClock__PM_ACT_MSK
#define DebClock_CLKSTBY_MASK       DebClock__PM_STBY_MSK

/* CFG2 field masks */
#define DebClock_SRC_SEL_MSK        DebClock__CFG2_SRC_SEL_MASK
#define DebClock_MODE_MASK          (~(DebClock_SRC_SEL_MSK))

#if defined(DebClock__CFG3)
/* CFG3 phase mask */
#define DebClock_PHASE_MASK         DebClock__CFG3_PHASE_DLY_MASK
#endif /* defined(DebClock__CFG3) */

#endif /* CY_CLOCK_DebClock_H */


/* [] END OF FILE */
