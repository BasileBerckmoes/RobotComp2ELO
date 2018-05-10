/*******************************************************************************
* File Name: MotorEN.h  
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

#if !defined(CY_PINS_MotorEN_H) /* Pins MotorEN_H */
#define CY_PINS_MotorEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorEN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotorEN__PORT == 15 && ((MotorEN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotorEN_Write(uint8 value);
void    MotorEN_SetDriveMode(uint8 mode);
uint8   MotorEN_ReadDataReg(void);
uint8   MotorEN_Read(void);
void    MotorEN_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotorEN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotorEN_SetDriveMode() function.
     *  @{
     */
        #define MotorEN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotorEN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotorEN_DM_RES_UP          PIN_DM_RES_UP
        #define MotorEN_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotorEN_DM_OD_LO           PIN_DM_OD_LO
        #define MotorEN_DM_OD_HI           PIN_DM_OD_HI
        #define MotorEN_DM_STRONG          PIN_DM_STRONG
        #define MotorEN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotorEN_MASK               MotorEN__MASK
#define MotorEN_SHIFT              MotorEN__SHIFT
#define MotorEN_WIDTH              1u

/* Interrupt constants */
#if defined(MotorEN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotorEN_SetInterruptMode() function.
     *  @{
     */
        #define MotorEN_INTR_NONE      (uint16)(0x0000u)
        #define MotorEN_INTR_RISING    (uint16)(0x0001u)
        #define MotorEN_INTR_FALLING   (uint16)(0x0002u)
        #define MotorEN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotorEN_INTR_MASK      (0x01u) 
#endif /* (MotorEN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorEN_PS                     (* (reg8 *) MotorEN__PS)
/* Data Register */
#define MotorEN_DR                     (* (reg8 *) MotorEN__DR)
/* Port Number */
#define MotorEN_PRT_NUM                (* (reg8 *) MotorEN__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorEN_AG                     (* (reg8 *) MotorEN__AG)                       
/* Analog MUX bux enable */
#define MotorEN_AMUX                   (* (reg8 *) MotorEN__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorEN_BIE                    (* (reg8 *) MotorEN__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorEN_BIT_MASK               (* (reg8 *) MotorEN__BIT_MASK)
/* Bypass Enable */
#define MotorEN_BYP                    (* (reg8 *) MotorEN__BYP)
/* Port wide control signals */                                                   
#define MotorEN_CTL                    (* (reg8 *) MotorEN__CTL)
/* Drive Modes */
#define MotorEN_DM0                    (* (reg8 *) MotorEN__DM0) 
#define MotorEN_DM1                    (* (reg8 *) MotorEN__DM1)
#define MotorEN_DM2                    (* (reg8 *) MotorEN__DM2) 
/* Input Buffer Disable Override */
#define MotorEN_INP_DIS                (* (reg8 *) MotorEN__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorEN_LCD_COM_SEG            (* (reg8 *) MotorEN__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorEN_LCD_EN                 (* (reg8 *) MotorEN__LCD_EN)
/* Slew Rate Control */
#define MotorEN_SLW                    (* (reg8 *) MotorEN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorEN_PRTDSI__CAPS_SEL       (* (reg8 *) MotorEN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorEN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorEN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorEN_PRTDSI__OE_SEL0        (* (reg8 *) MotorEN__PRTDSI__OE_SEL0) 
#define MotorEN_PRTDSI__OE_SEL1        (* (reg8 *) MotorEN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorEN_PRTDSI__OUT_SEL0       (* (reg8 *) MotorEN__PRTDSI__OUT_SEL0) 
#define MotorEN_PRTDSI__OUT_SEL1       (* (reg8 *) MotorEN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorEN_PRTDSI__SYNC_OUT       (* (reg8 *) MotorEN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotorEN__SIO_CFG)
    #define MotorEN_SIO_HYST_EN        (* (reg8 *) MotorEN__SIO_HYST_EN)
    #define MotorEN_SIO_REG_HIFREQ     (* (reg8 *) MotorEN__SIO_REG_HIFREQ)
    #define MotorEN_SIO_CFG            (* (reg8 *) MotorEN__SIO_CFG)
    #define MotorEN_SIO_DIFF           (* (reg8 *) MotorEN__SIO_DIFF)
#endif /* (MotorEN__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotorEN__INTSTAT)
    #define MotorEN_INTSTAT            (* (reg8 *) MotorEN__INTSTAT)
    #define MotorEN_SNAP               (* (reg8 *) MotorEN__SNAP)
    
	#define MotorEN_0_INTTYPE_REG 		(* (reg8 *) MotorEN__0__INTTYPE)
#endif /* (MotorEN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotorEN_H */


/* [] END OF FILE */
