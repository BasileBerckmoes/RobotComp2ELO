/*******************************************************************************
* File Name: pinY.h  
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

#if !defined(CY_PINS_pinY_H) /* Pins pinY_H */
#define CY_PINS_pinY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinY_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinY__PORT == 15 && ((pinY__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinY_Write(uint8 value);
void    pinY_SetDriveMode(uint8 mode);
uint8   pinY_ReadDataReg(void);
uint8   pinY_Read(void);
void    pinY_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinY_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinY_SetDriveMode() function.
     *  @{
     */
        #define pinY_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinY_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinY_DM_RES_UP          PIN_DM_RES_UP
        #define pinY_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinY_DM_OD_LO           PIN_DM_OD_LO
        #define pinY_DM_OD_HI           PIN_DM_OD_HI
        #define pinY_DM_STRONG          PIN_DM_STRONG
        #define pinY_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinY_MASK               pinY__MASK
#define pinY_SHIFT              pinY__SHIFT
#define pinY_WIDTH              1u

/* Interrupt constants */
#if defined(pinY__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinY_SetInterruptMode() function.
     *  @{
     */
        #define pinY_INTR_NONE      (uint16)(0x0000u)
        #define pinY_INTR_RISING    (uint16)(0x0001u)
        #define pinY_INTR_FALLING   (uint16)(0x0002u)
        #define pinY_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinY_INTR_MASK      (0x01u) 
#endif /* (pinY__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinY_PS                     (* (reg8 *) pinY__PS)
/* Data Register */
#define pinY_DR                     (* (reg8 *) pinY__DR)
/* Port Number */
#define pinY_PRT_NUM                (* (reg8 *) pinY__PRT) 
/* Connect to Analog Globals */                                                  
#define pinY_AG                     (* (reg8 *) pinY__AG)                       
/* Analog MUX bux enable */
#define pinY_AMUX                   (* (reg8 *) pinY__AMUX) 
/* Bidirectional Enable */                                                        
#define pinY_BIE                    (* (reg8 *) pinY__BIE)
/* Bit-mask for Aliased Register Access */
#define pinY_BIT_MASK               (* (reg8 *) pinY__BIT_MASK)
/* Bypass Enable */
#define pinY_BYP                    (* (reg8 *) pinY__BYP)
/* Port wide control signals */                                                   
#define pinY_CTL                    (* (reg8 *) pinY__CTL)
/* Drive Modes */
#define pinY_DM0                    (* (reg8 *) pinY__DM0) 
#define pinY_DM1                    (* (reg8 *) pinY__DM1)
#define pinY_DM2                    (* (reg8 *) pinY__DM2) 
/* Input Buffer Disable Override */
#define pinY_INP_DIS                (* (reg8 *) pinY__INP_DIS)
/* LCD Common or Segment Drive */
#define pinY_LCD_COM_SEG            (* (reg8 *) pinY__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinY_LCD_EN                 (* (reg8 *) pinY__LCD_EN)
/* Slew Rate Control */
#define pinY_SLW                    (* (reg8 *) pinY__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinY_PRTDSI__CAPS_SEL       (* (reg8 *) pinY__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinY_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinY__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinY_PRTDSI__OE_SEL0        (* (reg8 *) pinY__PRTDSI__OE_SEL0) 
#define pinY_PRTDSI__OE_SEL1        (* (reg8 *) pinY__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinY_PRTDSI__OUT_SEL0       (* (reg8 *) pinY__PRTDSI__OUT_SEL0) 
#define pinY_PRTDSI__OUT_SEL1       (* (reg8 *) pinY__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinY_PRTDSI__SYNC_OUT       (* (reg8 *) pinY__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinY__SIO_CFG)
    #define pinY_SIO_HYST_EN        (* (reg8 *) pinY__SIO_HYST_EN)
    #define pinY_SIO_REG_HIFREQ     (* (reg8 *) pinY__SIO_REG_HIFREQ)
    #define pinY_SIO_CFG            (* (reg8 *) pinY__SIO_CFG)
    #define pinY_SIO_DIFF           (* (reg8 *) pinY__SIO_DIFF)
#endif /* (pinY__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinY__INTSTAT)
    #define pinY_INTSTAT            (* (reg8 *) pinY__INTSTAT)
    #define pinY_SNAP               (* (reg8 *) pinY__SNAP)
    
	#define pinY_0_INTTYPE_REG 		(* (reg8 *) pinY__0__INTTYPE)
#endif /* (pinY__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinY_H */


/* [] END OF FILE */
