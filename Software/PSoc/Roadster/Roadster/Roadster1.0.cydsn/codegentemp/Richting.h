/*******************************************************************************
* File Name: Richting.h  
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

#if !defined(CY_PINS_Richting_H) /* Pins Richting_H */
#define CY_PINS_Richting_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Richting_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Richting__PORT == 15 && ((Richting__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Richting_Write(uint8 value);
void    Richting_SetDriveMode(uint8 mode);
uint8   Richting_ReadDataReg(void);
uint8   Richting_Read(void);
void    Richting_SetInterruptMode(uint16 position, uint16 mode);
uint8   Richting_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Richting_SetDriveMode() function.
     *  @{
     */
        #define Richting_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Richting_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Richting_DM_RES_UP          PIN_DM_RES_UP
        #define Richting_DM_RES_DWN         PIN_DM_RES_DWN
        #define Richting_DM_OD_LO           PIN_DM_OD_LO
        #define Richting_DM_OD_HI           PIN_DM_OD_HI
        #define Richting_DM_STRONG          PIN_DM_STRONG
        #define Richting_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Richting_MASK               Richting__MASK
#define Richting_SHIFT              Richting__SHIFT
#define Richting_WIDTH              1u

/* Interrupt constants */
#if defined(Richting__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Richting_SetInterruptMode() function.
     *  @{
     */
        #define Richting_INTR_NONE      (uint16)(0x0000u)
        #define Richting_INTR_RISING    (uint16)(0x0001u)
        #define Richting_INTR_FALLING   (uint16)(0x0002u)
        #define Richting_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Richting_INTR_MASK      (0x01u) 
#endif /* (Richting__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Richting_PS                     (* (reg8 *) Richting__PS)
/* Data Register */
#define Richting_DR                     (* (reg8 *) Richting__DR)
/* Port Number */
#define Richting_PRT_NUM                (* (reg8 *) Richting__PRT) 
/* Connect to Analog Globals */                                                  
#define Richting_AG                     (* (reg8 *) Richting__AG)                       
/* Analog MUX bux enable */
#define Richting_AMUX                   (* (reg8 *) Richting__AMUX) 
/* Bidirectional Enable */                                                        
#define Richting_BIE                    (* (reg8 *) Richting__BIE)
/* Bit-mask for Aliased Register Access */
#define Richting_BIT_MASK               (* (reg8 *) Richting__BIT_MASK)
/* Bypass Enable */
#define Richting_BYP                    (* (reg8 *) Richting__BYP)
/* Port wide control signals */                                                   
#define Richting_CTL                    (* (reg8 *) Richting__CTL)
/* Drive Modes */
#define Richting_DM0                    (* (reg8 *) Richting__DM0) 
#define Richting_DM1                    (* (reg8 *) Richting__DM1)
#define Richting_DM2                    (* (reg8 *) Richting__DM2) 
/* Input Buffer Disable Override */
#define Richting_INP_DIS                (* (reg8 *) Richting__INP_DIS)
/* LCD Common or Segment Drive */
#define Richting_LCD_COM_SEG            (* (reg8 *) Richting__LCD_COM_SEG)
/* Enable Segment LCD */
#define Richting_LCD_EN                 (* (reg8 *) Richting__LCD_EN)
/* Slew Rate Control */
#define Richting_SLW                    (* (reg8 *) Richting__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Richting_PRTDSI__CAPS_SEL       (* (reg8 *) Richting__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Richting_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Richting__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Richting_PRTDSI__OE_SEL0        (* (reg8 *) Richting__PRTDSI__OE_SEL0) 
#define Richting_PRTDSI__OE_SEL1        (* (reg8 *) Richting__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Richting_PRTDSI__OUT_SEL0       (* (reg8 *) Richting__PRTDSI__OUT_SEL0) 
#define Richting_PRTDSI__OUT_SEL1       (* (reg8 *) Richting__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Richting_PRTDSI__SYNC_OUT       (* (reg8 *) Richting__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Richting__SIO_CFG)
    #define Richting_SIO_HYST_EN        (* (reg8 *) Richting__SIO_HYST_EN)
    #define Richting_SIO_REG_HIFREQ     (* (reg8 *) Richting__SIO_REG_HIFREQ)
    #define Richting_SIO_CFG            (* (reg8 *) Richting__SIO_CFG)
    #define Richting_SIO_DIFF           (* (reg8 *) Richting__SIO_DIFF)
#endif /* (Richting__SIO_CFG) */

/* Interrupt Registers */
#if defined(Richting__INTSTAT)
    #define Richting_INTSTAT            (* (reg8 *) Richting__INTSTAT)
    #define Richting_SNAP               (* (reg8 *) Richting__SNAP)
    
	#define Richting_0_INTTYPE_REG 		(* (reg8 *) Richting__0__INTTYPE)
#endif /* (Richting__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Richting_H */


/* [] END OF FILE */
