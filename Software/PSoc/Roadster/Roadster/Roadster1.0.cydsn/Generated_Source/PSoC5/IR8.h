/*******************************************************************************
* File Name: IR8.h  
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

#if !defined(CY_PINS_IR8_H) /* Pins IR8_H */
#define CY_PINS_IR8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IR8_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IR8__PORT == 15 && ((IR8__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IR8_Write(uint8 value);
void    IR8_SetDriveMode(uint8 mode);
uint8   IR8_ReadDataReg(void);
uint8   IR8_Read(void);
void    IR8_SetInterruptMode(uint16 position, uint16 mode);
uint8   IR8_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IR8_SetDriveMode() function.
     *  @{
     */
        #define IR8_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IR8_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IR8_DM_RES_UP          PIN_DM_RES_UP
        #define IR8_DM_RES_DWN         PIN_DM_RES_DWN
        #define IR8_DM_OD_LO           PIN_DM_OD_LO
        #define IR8_DM_OD_HI           PIN_DM_OD_HI
        #define IR8_DM_STRONG          PIN_DM_STRONG
        #define IR8_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IR8_MASK               IR8__MASK
#define IR8_SHIFT              IR8__SHIFT
#define IR8_WIDTH              1u

/* Interrupt constants */
#if defined(IR8__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IR8_SetInterruptMode() function.
     *  @{
     */
        #define IR8_INTR_NONE      (uint16)(0x0000u)
        #define IR8_INTR_RISING    (uint16)(0x0001u)
        #define IR8_INTR_FALLING   (uint16)(0x0002u)
        #define IR8_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IR8_INTR_MASK      (0x01u) 
#endif /* (IR8__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IR8_PS                     (* (reg8 *) IR8__PS)
/* Data Register */
#define IR8_DR                     (* (reg8 *) IR8__DR)
/* Port Number */
#define IR8_PRT_NUM                (* (reg8 *) IR8__PRT) 
/* Connect to Analog Globals */                                                  
#define IR8_AG                     (* (reg8 *) IR8__AG)                       
/* Analog MUX bux enable */
#define IR8_AMUX                   (* (reg8 *) IR8__AMUX) 
/* Bidirectional Enable */                                                        
#define IR8_BIE                    (* (reg8 *) IR8__BIE)
/* Bit-mask for Aliased Register Access */
#define IR8_BIT_MASK               (* (reg8 *) IR8__BIT_MASK)
/* Bypass Enable */
#define IR8_BYP                    (* (reg8 *) IR8__BYP)
/* Port wide control signals */                                                   
#define IR8_CTL                    (* (reg8 *) IR8__CTL)
/* Drive Modes */
#define IR8_DM0                    (* (reg8 *) IR8__DM0) 
#define IR8_DM1                    (* (reg8 *) IR8__DM1)
#define IR8_DM2                    (* (reg8 *) IR8__DM2) 
/* Input Buffer Disable Override */
#define IR8_INP_DIS                (* (reg8 *) IR8__INP_DIS)
/* LCD Common or Segment Drive */
#define IR8_LCD_COM_SEG            (* (reg8 *) IR8__LCD_COM_SEG)
/* Enable Segment LCD */
#define IR8_LCD_EN                 (* (reg8 *) IR8__LCD_EN)
/* Slew Rate Control */
#define IR8_SLW                    (* (reg8 *) IR8__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IR8_PRTDSI__CAPS_SEL       (* (reg8 *) IR8__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IR8_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IR8__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IR8_PRTDSI__OE_SEL0        (* (reg8 *) IR8__PRTDSI__OE_SEL0) 
#define IR8_PRTDSI__OE_SEL1        (* (reg8 *) IR8__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IR8_PRTDSI__OUT_SEL0       (* (reg8 *) IR8__PRTDSI__OUT_SEL0) 
#define IR8_PRTDSI__OUT_SEL1       (* (reg8 *) IR8__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IR8_PRTDSI__SYNC_OUT       (* (reg8 *) IR8__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IR8__SIO_CFG)
    #define IR8_SIO_HYST_EN        (* (reg8 *) IR8__SIO_HYST_EN)
    #define IR8_SIO_REG_HIFREQ     (* (reg8 *) IR8__SIO_REG_HIFREQ)
    #define IR8_SIO_CFG            (* (reg8 *) IR8__SIO_CFG)
    #define IR8_SIO_DIFF           (* (reg8 *) IR8__SIO_DIFF)
#endif /* (IR8__SIO_CFG) */

/* Interrupt Registers */
#if defined(IR8__INTSTAT)
    #define IR8_INTSTAT            (* (reg8 *) IR8__INTSTAT)
    #define IR8_SNAP               (* (reg8 *) IR8__SNAP)
    
	#define IR8_0_INTTYPE_REG 		(* (reg8 *) IR8__0__INTTYPE)
#endif /* (IR8__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IR8_H */


/* [] END OF FILE */
