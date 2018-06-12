/*******************************************************************************
* File Name: IR4.h  
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

#if !defined(CY_PINS_IR4_H) /* Pins IR4_H */
#define CY_PINS_IR4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IR4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IR4__PORT == 15 && ((IR4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IR4_Write(uint8 value);
void    IR4_SetDriveMode(uint8 mode);
uint8   IR4_ReadDataReg(void);
uint8   IR4_Read(void);
void    IR4_SetInterruptMode(uint16 position, uint16 mode);
uint8   IR4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IR4_SetDriveMode() function.
     *  @{
     */
        #define IR4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IR4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IR4_DM_RES_UP          PIN_DM_RES_UP
        #define IR4_DM_RES_DWN         PIN_DM_RES_DWN
        #define IR4_DM_OD_LO           PIN_DM_OD_LO
        #define IR4_DM_OD_HI           PIN_DM_OD_HI
        #define IR4_DM_STRONG          PIN_DM_STRONG
        #define IR4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IR4_MASK               IR4__MASK
#define IR4_SHIFT              IR4__SHIFT
#define IR4_WIDTH              1u

/* Interrupt constants */
#if defined(IR4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IR4_SetInterruptMode() function.
     *  @{
     */
        #define IR4_INTR_NONE      (uint16)(0x0000u)
        #define IR4_INTR_RISING    (uint16)(0x0001u)
        #define IR4_INTR_FALLING   (uint16)(0x0002u)
        #define IR4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IR4_INTR_MASK      (0x01u) 
#endif /* (IR4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IR4_PS                     (* (reg8 *) IR4__PS)
/* Data Register */
#define IR4_DR                     (* (reg8 *) IR4__DR)
/* Port Number */
#define IR4_PRT_NUM                (* (reg8 *) IR4__PRT) 
/* Connect to Analog Globals */                                                  
#define IR4_AG                     (* (reg8 *) IR4__AG)                       
/* Analog MUX bux enable */
#define IR4_AMUX                   (* (reg8 *) IR4__AMUX) 
/* Bidirectional Enable */                                                        
#define IR4_BIE                    (* (reg8 *) IR4__BIE)
/* Bit-mask for Aliased Register Access */
#define IR4_BIT_MASK               (* (reg8 *) IR4__BIT_MASK)
/* Bypass Enable */
#define IR4_BYP                    (* (reg8 *) IR4__BYP)
/* Port wide control signals */                                                   
#define IR4_CTL                    (* (reg8 *) IR4__CTL)
/* Drive Modes */
#define IR4_DM0                    (* (reg8 *) IR4__DM0) 
#define IR4_DM1                    (* (reg8 *) IR4__DM1)
#define IR4_DM2                    (* (reg8 *) IR4__DM2) 
/* Input Buffer Disable Override */
#define IR4_INP_DIS                (* (reg8 *) IR4__INP_DIS)
/* LCD Common or Segment Drive */
#define IR4_LCD_COM_SEG            (* (reg8 *) IR4__LCD_COM_SEG)
/* Enable Segment LCD */
#define IR4_LCD_EN                 (* (reg8 *) IR4__LCD_EN)
/* Slew Rate Control */
#define IR4_SLW                    (* (reg8 *) IR4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IR4_PRTDSI__CAPS_SEL       (* (reg8 *) IR4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IR4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IR4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IR4_PRTDSI__OE_SEL0        (* (reg8 *) IR4__PRTDSI__OE_SEL0) 
#define IR4_PRTDSI__OE_SEL1        (* (reg8 *) IR4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IR4_PRTDSI__OUT_SEL0       (* (reg8 *) IR4__PRTDSI__OUT_SEL0) 
#define IR4_PRTDSI__OUT_SEL1       (* (reg8 *) IR4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IR4_PRTDSI__SYNC_OUT       (* (reg8 *) IR4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IR4__SIO_CFG)
    #define IR4_SIO_HYST_EN        (* (reg8 *) IR4__SIO_HYST_EN)
    #define IR4_SIO_REG_HIFREQ     (* (reg8 *) IR4__SIO_REG_HIFREQ)
    #define IR4_SIO_CFG            (* (reg8 *) IR4__SIO_CFG)
    #define IR4_SIO_DIFF           (* (reg8 *) IR4__SIO_DIFF)
#endif /* (IR4__SIO_CFG) */

/* Interrupt Registers */
#if defined(IR4__INTSTAT)
    #define IR4_INTSTAT            (* (reg8 *) IR4__INTSTAT)
    #define IR4_SNAP               (* (reg8 *) IR4__SNAP)
    
	#define IR4_0_INTTYPE_REG 		(* (reg8 *) IR4__0__INTTYPE)
#endif /* (IR4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IR4_H */


/* [] END OF FILE */
