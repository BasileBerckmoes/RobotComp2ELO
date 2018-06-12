/*******************************************************************************
* File Name: pinX.h  
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

#if !defined(CY_PINS_pinX_H) /* Pins pinX_H */
#define CY_PINS_pinX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinX__PORT == 15 && ((pinX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinX_Write(uint8 value);
void    pinX_SetDriveMode(uint8 mode);
uint8   pinX_ReadDataReg(void);
uint8   pinX_Read(void);
void    pinX_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinX_SetDriveMode() function.
     *  @{
     */
        #define pinX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinX_DM_RES_UP          PIN_DM_RES_UP
        #define pinX_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinX_DM_OD_LO           PIN_DM_OD_LO
        #define pinX_DM_OD_HI           PIN_DM_OD_HI
        #define pinX_DM_STRONG          PIN_DM_STRONG
        #define pinX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinX_MASK               pinX__MASK
#define pinX_SHIFT              pinX__SHIFT
#define pinX_WIDTH              1u

/* Interrupt constants */
#if defined(pinX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinX_SetInterruptMode() function.
     *  @{
     */
        #define pinX_INTR_NONE      (uint16)(0x0000u)
        #define pinX_INTR_RISING    (uint16)(0x0001u)
        #define pinX_INTR_FALLING   (uint16)(0x0002u)
        #define pinX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinX_INTR_MASK      (0x01u) 
#endif /* (pinX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinX_PS                     (* (reg8 *) pinX__PS)
/* Data Register */
#define pinX_DR                     (* (reg8 *) pinX__DR)
/* Port Number */
#define pinX_PRT_NUM                (* (reg8 *) pinX__PRT) 
/* Connect to Analog Globals */                                                  
#define pinX_AG                     (* (reg8 *) pinX__AG)                       
/* Analog MUX bux enable */
#define pinX_AMUX                   (* (reg8 *) pinX__AMUX) 
/* Bidirectional Enable */                                                        
#define pinX_BIE                    (* (reg8 *) pinX__BIE)
/* Bit-mask for Aliased Register Access */
#define pinX_BIT_MASK               (* (reg8 *) pinX__BIT_MASK)
/* Bypass Enable */
#define pinX_BYP                    (* (reg8 *) pinX__BYP)
/* Port wide control signals */                                                   
#define pinX_CTL                    (* (reg8 *) pinX__CTL)
/* Drive Modes */
#define pinX_DM0                    (* (reg8 *) pinX__DM0) 
#define pinX_DM1                    (* (reg8 *) pinX__DM1)
#define pinX_DM2                    (* (reg8 *) pinX__DM2) 
/* Input Buffer Disable Override */
#define pinX_INP_DIS                (* (reg8 *) pinX__INP_DIS)
/* LCD Common or Segment Drive */
#define pinX_LCD_COM_SEG            (* (reg8 *) pinX__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinX_LCD_EN                 (* (reg8 *) pinX__LCD_EN)
/* Slew Rate Control */
#define pinX_SLW                    (* (reg8 *) pinX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinX_PRTDSI__CAPS_SEL       (* (reg8 *) pinX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinX_PRTDSI__OE_SEL0        (* (reg8 *) pinX__PRTDSI__OE_SEL0) 
#define pinX_PRTDSI__OE_SEL1        (* (reg8 *) pinX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinX_PRTDSI__OUT_SEL0       (* (reg8 *) pinX__PRTDSI__OUT_SEL0) 
#define pinX_PRTDSI__OUT_SEL1       (* (reg8 *) pinX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinX_PRTDSI__SYNC_OUT       (* (reg8 *) pinX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinX__SIO_CFG)
    #define pinX_SIO_HYST_EN        (* (reg8 *) pinX__SIO_HYST_EN)
    #define pinX_SIO_REG_HIFREQ     (* (reg8 *) pinX__SIO_REG_HIFREQ)
    #define pinX_SIO_CFG            (* (reg8 *) pinX__SIO_CFG)
    #define pinX_SIO_DIFF           (* (reg8 *) pinX__SIO_DIFF)
#endif /* (pinX__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinX__INTSTAT)
    #define pinX_INTSTAT            (* (reg8 *) pinX__INTSTAT)
    #define pinX_SNAP               (* (reg8 *) pinX__SNAP)
    
	#define pinX_0_INTTYPE_REG 		(* (reg8 *) pinX__0__INTTYPE)
#endif /* (pinX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinX_H */


/* [] END OF FILE */
