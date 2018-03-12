/*******************************************************************************
* File Name: CharLCD_1_LCDPort.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CharLCD_1_LCDPort_H) /* Pins CharLCD_1_LCDPort_H */
#define CY_PINS_CharLCD_1_LCDPort_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CharLCD_1_LCDPort_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CharLCD_1_LCDPort__PORT == 15 && ((CharLCD_1_LCDPort__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CharLCD_1_LCDPort_Write(uint8 value);
void    CharLCD_1_LCDPort_SetDriveMode(uint8 mode);
uint8   CharLCD_1_LCDPort_ReadDataReg(void);
uint8   CharLCD_1_LCDPort_Read(void);
void    CharLCD_1_LCDPort_SetInterruptMode(uint16 position, uint16 mode);
uint8   CharLCD_1_LCDPort_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CharLCD_1_LCDPort_SetDriveMode() function.
     *  @{
     */
        #define CharLCD_1_LCDPort_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CharLCD_1_LCDPort_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CharLCD_1_LCDPort_DM_RES_UP          PIN_DM_RES_UP
        #define CharLCD_1_LCDPort_DM_RES_DWN         PIN_DM_RES_DWN
        #define CharLCD_1_LCDPort_DM_OD_LO           PIN_DM_OD_LO
        #define CharLCD_1_LCDPort_DM_OD_HI           PIN_DM_OD_HI
        #define CharLCD_1_LCDPort_DM_STRONG          PIN_DM_STRONG
        #define CharLCD_1_LCDPort_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CharLCD_1_LCDPort_MASK               CharLCD_1_LCDPort__MASK
#define CharLCD_1_LCDPort_SHIFT              CharLCD_1_LCDPort__SHIFT
#define CharLCD_1_LCDPort_WIDTH              7u

/* Interrupt constants */
#if defined(CharLCD_1_LCDPort__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CharLCD_1_LCDPort_SetInterruptMode() function.
     *  @{
     */
        #define CharLCD_1_LCDPort_INTR_NONE      (uint16)(0x0000u)
        #define CharLCD_1_LCDPort_INTR_RISING    (uint16)(0x0001u)
        #define CharLCD_1_LCDPort_INTR_FALLING   (uint16)(0x0002u)
        #define CharLCD_1_LCDPort_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CharLCD_1_LCDPort_INTR_MASK      (0x01u) 
#endif /* (CharLCD_1_LCDPort__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CharLCD_1_LCDPort_PS                     (* (reg8 *) CharLCD_1_LCDPort__PS)
/* Data Register */
#define CharLCD_1_LCDPort_DR                     (* (reg8 *) CharLCD_1_LCDPort__DR)
/* Port Number */
#define CharLCD_1_LCDPort_PRT_NUM                (* (reg8 *) CharLCD_1_LCDPort__PRT) 
/* Connect to Analog Globals */                                                  
#define CharLCD_1_LCDPort_AG                     (* (reg8 *) CharLCD_1_LCDPort__AG)                       
/* Analog MUX bux enable */
#define CharLCD_1_LCDPort_AMUX                   (* (reg8 *) CharLCD_1_LCDPort__AMUX) 
/* Bidirectional Enable */                                                        
#define CharLCD_1_LCDPort_BIE                    (* (reg8 *) CharLCD_1_LCDPort__BIE)
/* Bit-mask for Aliased Register Access */
#define CharLCD_1_LCDPort_BIT_MASK               (* (reg8 *) CharLCD_1_LCDPort__BIT_MASK)
/* Bypass Enable */
#define CharLCD_1_LCDPort_BYP                    (* (reg8 *) CharLCD_1_LCDPort__BYP)
/* Port wide control signals */                                                   
#define CharLCD_1_LCDPort_CTL                    (* (reg8 *) CharLCD_1_LCDPort__CTL)
/* Drive Modes */
#define CharLCD_1_LCDPort_DM0                    (* (reg8 *) CharLCD_1_LCDPort__DM0) 
#define CharLCD_1_LCDPort_DM1                    (* (reg8 *) CharLCD_1_LCDPort__DM1)
#define CharLCD_1_LCDPort_DM2                    (* (reg8 *) CharLCD_1_LCDPort__DM2) 
/* Input Buffer Disable Override */
#define CharLCD_1_LCDPort_INP_DIS                (* (reg8 *) CharLCD_1_LCDPort__INP_DIS)
/* LCD Common or Segment Drive */
#define CharLCD_1_LCDPort_LCD_COM_SEG            (* (reg8 *) CharLCD_1_LCDPort__LCD_COM_SEG)
/* Enable Segment LCD */
#define CharLCD_1_LCDPort_LCD_EN                 (* (reg8 *) CharLCD_1_LCDPort__LCD_EN)
/* Slew Rate Control */
#define CharLCD_1_LCDPort_SLW                    (* (reg8 *) CharLCD_1_LCDPort__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CharLCD_1_LCDPort_PRTDSI__CAPS_SEL       (* (reg8 *) CharLCD_1_LCDPort__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CharLCD_1_LCDPort_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CharLCD_1_LCDPort__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CharLCD_1_LCDPort_PRTDSI__OE_SEL0        (* (reg8 *) CharLCD_1_LCDPort__PRTDSI__OE_SEL0) 
#define CharLCD_1_LCDPort_PRTDSI__OE_SEL1        (* (reg8 *) CharLCD_1_LCDPort__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CharLCD_1_LCDPort_PRTDSI__OUT_SEL0       (* (reg8 *) CharLCD_1_LCDPort__PRTDSI__OUT_SEL0) 
#define CharLCD_1_LCDPort_PRTDSI__OUT_SEL1       (* (reg8 *) CharLCD_1_LCDPort__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CharLCD_1_LCDPort_PRTDSI__SYNC_OUT       (* (reg8 *) CharLCD_1_LCDPort__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CharLCD_1_LCDPort__SIO_CFG)
    #define CharLCD_1_LCDPort_SIO_HYST_EN        (* (reg8 *) CharLCD_1_LCDPort__SIO_HYST_EN)
    #define CharLCD_1_LCDPort_SIO_REG_HIFREQ     (* (reg8 *) CharLCD_1_LCDPort__SIO_REG_HIFREQ)
    #define CharLCD_1_LCDPort_SIO_CFG            (* (reg8 *) CharLCD_1_LCDPort__SIO_CFG)
    #define CharLCD_1_LCDPort_SIO_DIFF           (* (reg8 *) CharLCD_1_LCDPort__SIO_DIFF)
#endif /* (CharLCD_1_LCDPort__SIO_CFG) */

/* Interrupt Registers */
#if defined(CharLCD_1_LCDPort__INTSTAT)
    #define CharLCD_1_LCDPort_INTSTAT            (* (reg8 *) CharLCD_1_LCDPort__INTSTAT)
    #define CharLCD_1_LCDPort_SNAP               (* (reg8 *) CharLCD_1_LCDPort__SNAP)
    
	#define CharLCD_1_LCDPort_0_INTTYPE_REG 		(* (reg8 *) CharLCD_1_LCDPort__0__INTTYPE)
	#define CharLCD_1_LCDPort_1_INTTYPE_REG 		(* (reg8 *) CharLCD_1_LCDPort__1__INTTYPE)
	#define CharLCD_1_LCDPort_2_INTTYPE_REG 		(* (reg8 *) CharLCD_1_LCDPort__2__INTTYPE)
	#define CharLCD_1_LCDPort_3_INTTYPE_REG 		(* (reg8 *) CharLCD_1_LCDPort__3__INTTYPE)
	#define CharLCD_1_LCDPort_4_INTTYPE_REG 		(* (reg8 *) CharLCD_1_LCDPort__4__INTTYPE)
	#define CharLCD_1_LCDPort_5_INTTYPE_REG 		(* (reg8 *) CharLCD_1_LCDPort__5__INTTYPE)
	#define CharLCD_1_LCDPort_6_INTTYPE_REG 		(* (reg8 *) CharLCD_1_LCDPort__6__INTTYPE)
#endif /* (CharLCD_1_LCDPort__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CharLCD_1_LCDPort_H */


/* [] END OF FILE */
