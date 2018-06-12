/*******************************************************************************
* File Name: Echo3.h  
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

#if !defined(CY_PINS_Echo3_H) /* Pins Echo3_H */
#define CY_PINS_Echo3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Echo3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Echo3__PORT == 15 && ((Echo3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Echo3_Write(uint8 value);
void    Echo3_SetDriveMode(uint8 mode);
uint8   Echo3_ReadDataReg(void);
uint8   Echo3_Read(void);
void    Echo3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Echo3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Echo3_SetDriveMode() function.
     *  @{
     */
        #define Echo3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Echo3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Echo3_DM_RES_UP          PIN_DM_RES_UP
        #define Echo3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Echo3_DM_OD_LO           PIN_DM_OD_LO
        #define Echo3_DM_OD_HI           PIN_DM_OD_HI
        #define Echo3_DM_STRONG          PIN_DM_STRONG
        #define Echo3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Echo3_MASK               Echo3__MASK
#define Echo3_SHIFT              Echo3__SHIFT
#define Echo3_WIDTH              1u

/* Interrupt constants */
#if defined(Echo3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Echo3_SetInterruptMode() function.
     *  @{
     */
        #define Echo3_INTR_NONE      (uint16)(0x0000u)
        #define Echo3_INTR_RISING    (uint16)(0x0001u)
        #define Echo3_INTR_FALLING   (uint16)(0x0002u)
        #define Echo3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Echo3_INTR_MASK      (0x01u) 
#endif /* (Echo3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Echo3_PS                     (* (reg8 *) Echo3__PS)
/* Data Register */
#define Echo3_DR                     (* (reg8 *) Echo3__DR)
/* Port Number */
#define Echo3_PRT_NUM                (* (reg8 *) Echo3__PRT) 
/* Connect to Analog Globals */                                                  
#define Echo3_AG                     (* (reg8 *) Echo3__AG)                       
/* Analog MUX bux enable */
#define Echo3_AMUX                   (* (reg8 *) Echo3__AMUX) 
/* Bidirectional Enable */                                                        
#define Echo3_BIE                    (* (reg8 *) Echo3__BIE)
/* Bit-mask for Aliased Register Access */
#define Echo3_BIT_MASK               (* (reg8 *) Echo3__BIT_MASK)
/* Bypass Enable */
#define Echo3_BYP                    (* (reg8 *) Echo3__BYP)
/* Port wide control signals */                                                   
#define Echo3_CTL                    (* (reg8 *) Echo3__CTL)
/* Drive Modes */
#define Echo3_DM0                    (* (reg8 *) Echo3__DM0) 
#define Echo3_DM1                    (* (reg8 *) Echo3__DM1)
#define Echo3_DM2                    (* (reg8 *) Echo3__DM2) 
/* Input Buffer Disable Override */
#define Echo3_INP_DIS                (* (reg8 *) Echo3__INP_DIS)
/* LCD Common or Segment Drive */
#define Echo3_LCD_COM_SEG            (* (reg8 *) Echo3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Echo3_LCD_EN                 (* (reg8 *) Echo3__LCD_EN)
/* Slew Rate Control */
#define Echo3_SLW                    (* (reg8 *) Echo3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Echo3_PRTDSI__CAPS_SEL       (* (reg8 *) Echo3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Echo3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Echo3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Echo3_PRTDSI__OE_SEL0        (* (reg8 *) Echo3__PRTDSI__OE_SEL0) 
#define Echo3_PRTDSI__OE_SEL1        (* (reg8 *) Echo3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Echo3_PRTDSI__OUT_SEL0       (* (reg8 *) Echo3__PRTDSI__OUT_SEL0) 
#define Echo3_PRTDSI__OUT_SEL1       (* (reg8 *) Echo3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Echo3_PRTDSI__SYNC_OUT       (* (reg8 *) Echo3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Echo3__SIO_CFG)
    #define Echo3_SIO_HYST_EN        (* (reg8 *) Echo3__SIO_HYST_EN)
    #define Echo3_SIO_REG_HIFREQ     (* (reg8 *) Echo3__SIO_REG_HIFREQ)
    #define Echo3_SIO_CFG            (* (reg8 *) Echo3__SIO_CFG)
    #define Echo3_SIO_DIFF           (* (reg8 *) Echo3__SIO_DIFF)
#endif /* (Echo3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Echo3__INTSTAT)
    #define Echo3_INTSTAT            (* (reg8 *) Echo3__INTSTAT)
    #define Echo3_SNAP               (* (reg8 *) Echo3__SNAP)
    
	#define Echo3_0_INTTYPE_REG 		(* (reg8 *) Echo3__0__INTTYPE)
#endif /* (Echo3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Echo3_H */


/* [] END OF FILE */
