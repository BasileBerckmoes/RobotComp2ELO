/*******************************************************************************
* File Name: IR1.h  
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

#if !defined(CY_PINS_IR1_H) /* Pins IR1_H */
#define CY_PINS_IR1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IR1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IR1__PORT == 15 && ((IR1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IR1_Write(uint8 value);
void    IR1_SetDriveMode(uint8 mode);
uint8   IR1_ReadDataReg(void);
uint8   IR1_Read(void);
void    IR1_SetInterruptMode(uint16 position, uint16 mode);
uint8   IR1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IR1_SetDriveMode() function.
     *  @{
     */
        #define IR1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IR1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IR1_DM_RES_UP          PIN_DM_RES_UP
        #define IR1_DM_RES_DWN         PIN_DM_RES_DWN
        #define IR1_DM_OD_LO           PIN_DM_OD_LO
        #define IR1_DM_OD_HI           PIN_DM_OD_HI
        #define IR1_DM_STRONG          PIN_DM_STRONG
        #define IR1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IR1_MASK               IR1__MASK
#define IR1_SHIFT              IR1__SHIFT
#define IR1_WIDTH              1u

/* Interrupt constants */
#if defined(IR1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IR1_SetInterruptMode() function.
     *  @{
     */
        #define IR1_INTR_NONE      (uint16)(0x0000u)
        #define IR1_INTR_RISING    (uint16)(0x0001u)
        #define IR1_INTR_FALLING   (uint16)(0x0002u)
        #define IR1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IR1_INTR_MASK      (0x01u) 
#endif /* (IR1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IR1_PS                     (* (reg8 *) IR1__PS)
/* Data Register */
#define IR1_DR                     (* (reg8 *) IR1__DR)
/* Port Number */
#define IR1_PRT_NUM                (* (reg8 *) IR1__PRT) 
/* Connect to Analog Globals */                                                  
#define IR1_AG                     (* (reg8 *) IR1__AG)                       
/* Analog MUX bux enable */
#define IR1_AMUX                   (* (reg8 *) IR1__AMUX) 
/* Bidirectional Enable */                                                        
#define IR1_BIE                    (* (reg8 *) IR1__BIE)
/* Bit-mask for Aliased Register Access */
#define IR1_BIT_MASK               (* (reg8 *) IR1__BIT_MASK)
/* Bypass Enable */
#define IR1_BYP                    (* (reg8 *) IR1__BYP)
/* Port wide control signals */                                                   
#define IR1_CTL                    (* (reg8 *) IR1__CTL)
/* Drive Modes */
#define IR1_DM0                    (* (reg8 *) IR1__DM0) 
#define IR1_DM1                    (* (reg8 *) IR1__DM1)
#define IR1_DM2                    (* (reg8 *) IR1__DM2) 
/* Input Buffer Disable Override */
#define IR1_INP_DIS                (* (reg8 *) IR1__INP_DIS)
/* LCD Common or Segment Drive */
#define IR1_LCD_COM_SEG            (* (reg8 *) IR1__LCD_COM_SEG)
/* Enable Segment LCD */
#define IR1_LCD_EN                 (* (reg8 *) IR1__LCD_EN)
/* Slew Rate Control */
#define IR1_SLW                    (* (reg8 *) IR1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IR1_PRTDSI__CAPS_SEL       (* (reg8 *) IR1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IR1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IR1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IR1_PRTDSI__OE_SEL0        (* (reg8 *) IR1__PRTDSI__OE_SEL0) 
#define IR1_PRTDSI__OE_SEL1        (* (reg8 *) IR1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IR1_PRTDSI__OUT_SEL0       (* (reg8 *) IR1__PRTDSI__OUT_SEL0) 
#define IR1_PRTDSI__OUT_SEL1       (* (reg8 *) IR1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IR1_PRTDSI__SYNC_OUT       (* (reg8 *) IR1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IR1__SIO_CFG)
    #define IR1_SIO_HYST_EN        (* (reg8 *) IR1__SIO_HYST_EN)
    #define IR1_SIO_REG_HIFREQ     (* (reg8 *) IR1__SIO_REG_HIFREQ)
    #define IR1_SIO_CFG            (* (reg8 *) IR1__SIO_CFG)
    #define IR1_SIO_DIFF           (* (reg8 *) IR1__SIO_DIFF)
#endif /* (IR1__SIO_CFG) */

/* Interrupt Registers */
#if defined(IR1__INTSTAT)
    #define IR1_INTSTAT            (* (reg8 *) IR1__INTSTAT)
    #define IR1_SNAP               (* (reg8 *) IR1__SNAP)
    
	#define IR1_0_INTTYPE_REG 		(* (reg8 *) IR1__0__INTTYPE)
#endif /* (IR1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IR1_H */


/* [] END OF FILE */
