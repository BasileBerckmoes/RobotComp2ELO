/*******************************************************************************
* File Name: LCD1_LCDPort.h  
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

#if !defined(CY_PINS_LCD1_LCDPort_H) /* Pins LCD1_LCDPort_H */
#define CY_PINS_LCD1_LCDPort_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LCD1_LCDPort_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LCD1_LCDPort__PORT == 15 && ((LCD1_LCDPort__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LCD1_LCDPort_Write(uint8 value);
void    LCD1_LCDPort_SetDriveMode(uint8 mode);
uint8   LCD1_LCDPort_ReadDataReg(void);
uint8   LCD1_LCDPort_Read(void);
void    LCD1_LCDPort_SetInterruptMode(uint16 position, uint16 mode);
uint8   LCD1_LCDPort_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LCD1_LCDPort_SetDriveMode() function.
     *  @{
     */
        #define LCD1_LCDPort_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LCD1_LCDPort_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LCD1_LCDPort_DM_RES_UP          PIN_DM_RES_UP
        #define LCD1_LCDPort_DM_RES_DWN         PIN_DM_RES_DWN
        #define LCD1_LCDPort_DM_OD_LO           PIN_DM_OD_LO
        #define LCD1_LCDPort_DM_OD_HI           PIN_DM_OD_HI
        #define LCD1_LCDPort_DM_STRONG          PIN_DM_STRONG
        #define LCD1_LCDPort_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LCD1_LCDPort_MASK               LCD1_LCDPort__MASK
#define LCD1_LCDPort_SHIFT              LCD1_LCDPort__SHIFT
#define LCD1_LCDPort_WIDTH              7u

/* Interrupt constants */
#if defined(LCD1_LCDPort__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LCD1_LCDPort_SetInterruptMode() function.
     *  @{
     */
        #define LCD1_LCDPort_INTR_NONE      (uint16)(0x0000u)
        #define LCD1_LCDPort_INTR_RISING    (uint16)(0x0001u)
        #define LCD1_LCDPort_INTR_FALLING   (uint16)(0x0002u)
        #define LCD1_LCDPort_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LCD1_LCDPort_INTR_MASK      (0x01u) 
#endif /* (LCD1_LCDPort__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LCD1_LCDPort_PS                     (* (reg8 *) LCD1_LCDPort__PS)
/* Data Register */
#define LCD1_LCDPort_DR                     (* (reg8 *) LCD1_LCDPort__DR)
/* Port Number */
#define LCD1_LCDPort_PRT_NUM                (* (reg8 *) LCD1_LCDPort__PRT) 
/* Connect to Analog Globals */                                                  
#define LCD1_LCDPort_AG                     (* (reg8 *) LCD1_LCDPort__AG)                       
/* Analog MUX bux enable */
#define LCD1_LCDPort_AMUX                   (* (reg8 *) LCD1_LCDPort__AMUX) 
/* Bidirectional Enable */                                                        
#define LCD1_LCDPort_BIE                    (* (reg8 *) LCD1_LCDPort__BIE)
/* Bit-mask for Aliased Register Access */
#define LCD1_LCDPort_BIT_MASK               (* (reg8 *) LCD1_LCDPort__BIT_MASK)
/* Bypass Enable */
#define LCD1_LCDPort_BYP                    (* (reg8 *) LCD1_LCDPort__BYP)
/* Port wide control signals */                                                   
#define LCD1_LCDPort_CTL                    (* (reg8 *) LCD1_LCDPort__CTL)
/* Drive Modes */
#define LCD1_LCDPort_DM0                    (* (reg8 *) LCD1_LCDPort__DM0) 
#define LCD1_LCDPort_DM1                    (* (reg8 *) LCD1_LCDPort__DM1)
#define LCD1_LCDPort_DM2                    (* (reg8 *) LCD1_LCDPort__DM2) 
/* Input Buffer Disable Override */
#define LCD1_LCDPort_INP_DIS                (* (reg8 *) LCD1_LCDPort__INP_DIS)
/* LCD Common or Segment Drive */
#define LCD1_LCDPort_LCD_COM_SEG            (* (reg8 *) LCD1_LCDPort__LCD_COM_SEG)
/* Enable Segment LCD */
#define LCD1_LCDPort_LCD_EN                 (* (reg8 *) LCD1_LCDPort__LCD_EN)
/* Slew Rate Control */
#define LCD1_LCDPort_SLW                    (* (reg8 *) LCD1_LCDPort__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LCD1_LCDPort_PRTDSI__CAPS_SEL       (* (reg8 *) LCD1_LCDPort__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LCD1_LCDPort_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LCD1_LCDPort__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LCD1_LCDPort_PRTDSI__OE_SEL0        (* (reg8 *) LCD1_LCDPort__PRTDSI__OE_SEL0) 
#define LCD1_LCDPort_PRTDSI__OE_SEL1        (* (reg8 *) LCD1_LCDPort__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LCD1_LCDPort_PRTDSI__OUT_SEL0       (* (reg8 *) LCD1_LCDPort__PRTDSI__OUT_SEL0) 
#define LCD1_LCDPort_PRTDSI__OUT_SEL1       (* (reg8 *) LCD1_LCDPort__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LCD1_LCDPort_PRTDSI__SYNC_OUT       (* (reg8 *) LCD1_LCDPort__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LCD1_LCDPort__SIO_CFG)
    #define LCD1_LCDPort_SIO_HYST_EN        (* (reg8 *) LCD1_LCDPort__SIO_HYST_EN)
    #define LCD1_LCDPort_SIO_REG_HIFREQ     (* (reg8 *) LCD1_LCDPort__SIO_REG_HIFREQ)
    #define LCD1_LCDPort_SIO_CFG            (* (reg8 *) LCD1_LCDPort__SIO_CFG)
    #define LCD1_LCDPort_SIO_DIFF           (* (reg8 *) LCD1_LCDPort__SIO_DIFF)
#endif /* (LCD1_LCDPort__SIO_CFG) */

/* Interrupt Registers */
#if defined(LCD1_LCDPort__INTSTAT)
    #define LCD1_LCDPort_INTSTAT            (* (reg8 *) LCD1_LCDPort__INTSTAT)
    #define LCD1_LCDPort_SNAP               (* (reg8 *) LCD1_LCDPort__SNAP)
    
	#define LCD1_LCDPort_0_INTTYPE_REG 		(* (reg8 *) LCD1_LCDPort__0__INTTYPE)
	#define LCD1_LCDPort_1_INTTYPE_REG 		(* (reg8 *) LCD1_LCDPort__1__INTTYPE)
	#define LCD1_LCDPort_2_INTTYPE_REG 		(* (reg8 *) LCD1_LCDPort__2__INTTYPE)
	#define LCD1_LCDPort_3_INTTYPE_REG 		(* (reg8 *) LCD1_LCDPort__3__INTTYPE)
	#define LCD1_LCDPort_4_INTTYPE_REG 		(* (reg8 *) LCD1_LCDPort__4__INTTYPE)
	#define LCD1_LCDPort_5_INTTYPE_REG 		(* (reg8 *) LCD1_LCDPort__5__INTTYPE)
	#define LCD1_LCDPort_6_INTTYPE_REG 		(* (reg8 *) LCD1_LCDPort__6__INTTYPE)
#endif /* (LCD1_LCDPort__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LCD1_LCDPort_H */


/* [] END OF FILE */