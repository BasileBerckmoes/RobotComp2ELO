/*******************************************************************************
* File Name: Echo1.h  
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

#if !defined(CY_PINS_Echo1_H) /* Pins Echo1_H */
#define CY_PINS_Echo1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Echo1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Echo1__PORT == 15 && ((Echo1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Echo1_Write(uint8 value);
void    Echo1_SetDriveMode(uint8 mode);
uint8   Echo1_ReadDataReg(void);
uint8   Echo1_Read(void);
void    Echo1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Echo1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Echo1_SetDriveMode() function.
     *  @{
     */
        #define Echo1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Echo1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Echo1_DM_RES_UP          PIN_DM_RES_UP
        #define Echo1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Echo1_DM_OD_LO           PIN_DM_OD_LO
        #define Echo1_DM_OD_HI           PIN_DM_OD_HI
        #define Echo1_DM_STRONG          PIN_DM_STRONG
        #define Echo1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Echo1_MASK               Echo1__MASK
#define Echo1_SHIFT              Echo1__SHIFT
#define Echo1_WIDTH              1u

/* Interrupt constants */
#if defined(Echo1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Echo1_SetInterruptMode() function.
     *  @{
     */
        #define Echo1_INTR_NONE      (uint16)(0x0000u)
        #define Echo1_INTR_RISING    (uint16)(0x0001u)
        #define Echo1_INTR_FALLING   (uint16)(0x0002u)
        #define Echo1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Echo1_INTR_MASK      (0x01u) 
#endif /* (Echo1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Echo1_PS                     (* (reg8 *) Echo1__PS)
/* Data Register */
#define Echo1_DR                     (* (reg8 *) Echo1__DR)
/* Port Number */
#define Echo1_PRT_NUM                (* (reg8 *) Echo1__PRT) 
/* Connect to Analog Globals */                                                  
#define Echo1_AG                     (* (reg8 *) Echo1__AG)                       
/* Analog MUX bux enable */
#define Echo1_AMUX                   (* (reg8 *) Echo1__AMUX) 
/* Bidirectional Enable */                                                        
#define Echo1_BIE                    (* (reg8 *) Echo1__BIE)
/* Bit-mask for Aliased Register Access */
#define Echo1_BIT_MASK               (* (reg8 *) Echo1__BIT_MASK)
/* Bypass Enable */
#define Echo1_BYP                    (* (reg8 *) Echo1__BYP)
/* Port wide control signals */                                                   
#define Echo1_CTL                    (* (reg8 *) Echo1__CTL)
/* Drive Modes */
#define Echo1_DM0                    (* (reg8 *) Echo1__DM0) 
#define Echo1_DM1                    (* (reg8 *) Echo1__DM1)
#define Echo1_DM2                    (* (reg8 *) Echo1__DM2) 
/* Input Buffer Disable Override */
#define Echo1_INP_DIS                (* (reg8 *) Echo1__INP_DIS)
/* LCD Common or Segment Drive */
#define Echo1_LCD_COM_SEG            (* (reg8 *) Echo1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Echo1_LCD_EN                 (* (reg8 *) Echo1__LCD_EN)
/* Slew Rate Control */
#define Echo1_SLW                    (* (reg8 *) Echo1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Echo1_PRTDSI__CAPS_SEL       (* (reg8 *) Echo1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Echo1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Echo1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Echo1_PRTDSI__OE_SEL0        (* (reg8 *) Echo1__PRTDSI__OE_SEL0) 
#define Echo1_PRTDSI__OE_SEL1        (* (reg8 *) Echo1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Echo1_PRTDSI__OUT_SEL0       (* (reg8 *) Echo1__PRTDSI__OUT_SEL0) 
#define Echo1_PRTDSI__OUT_SEL1       (* (reg8 *) Echo1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Echo1_PRTDSI__SYNC_OUT       (* (reg8 *) Echo1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Echo1__SIO_CFG)
    #define Echo1_SIO_HYST_EN        (* (reg8 *) Echo1__SIO_HYST_EN)
    #define Echo1_SIO_REG_HIFREQ     (* (reg8 *) Echo1__SIO_REG_HIFREQ)
    #define Echo1_SIO_CFG            (* (reg8 *) Echo1__SIO_CFG)
    #define Echo1_SIO_DIFF           (* (reg8 *) Echo1__SIO_DIFF)
#endif /* (Echo1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Echo1__INTSTAT)
    #define Echo1_INTSTAT            (* (reg8 *) Echo1__INTSTAT)
    #define Echo1_SNAP               (* (reg8 *) Echo1__SNAP)
    
	#define Echo1_0_INTTYPE_REG 		(* (reg8 *) Echo1__0__INTTYPE)
#endif /* (Echo1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Echo1_H */


/* [] END OF FILE */
