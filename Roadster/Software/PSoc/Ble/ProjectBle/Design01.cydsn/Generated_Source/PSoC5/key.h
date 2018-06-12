/*******************************************************************************
* File Name: key.h  
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

#if !defined(CY_PINS_key_H) /* Pins key_H */
#define CY_PINS_key_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "key_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 key__PORT == 15 && ((key__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    key_Write(uint8 value);
void    key_SetDriveMode(uint8 mode);
uint8   key_ReadDataReg(void);
uint8   key_Read(void);
void    key_SetInterruptMode(uint16 position, uint16 mode);
uint8   key_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the key_SetDriveMode() function.
     *  @{
     */
        #define key_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define key_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define key_DM_RES_UP          PIN_DM_RES_UP
        #define key_DM_RES_DWN         PIN_DM_RES_DWN
        #define key_DM_OD_LO           PIN_DM_OD_LO
        #define key_DM_OD_HI           PIN_DM_OD_HI
        #define key_DM_STRONG          PIN_DM_STRONG
        #define key_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define key_MASK               key__MASK
#define key_SHIFT              key__SHIFT
#define key_WIDTH              1u

/* Interrupt constants */
#if defined(key__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in key_SetInterruptMode() function.
     *  @{
     */
        #define key_INTR_NONE      (uint16)(0x0000u)
        #define key_INTR_RISING    (uint16)(0x0001u)
        #define key_INTR_FALLING   (uint16)(0x0002u)
        #define key_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define key_INTR_MASK      (0x01u) 
#endif /* (key__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define key_PS                     (* (reg8 *) key__PS)
/* Data Register */
#define key_DR                     (* (reg8 *) key__DR)
/* Port Number */
#define key_PRT_NUM                (* (reg8 *) key__PRT) 
/* Connect to Analog Globals */                                                  
#define key_AG                     (* (reg8 *) key__AG)                       
/* Analog MUX bux enable */
#define key_AMUX                   (* (reg8 *) key__AMUX) 
/* Bidirectional Enable */                                                        
#define key_BIE                    (* (reg8 *) key__BIE)
/* Bit-mask for Aliased Register Access */
#define key_BIT_MASK               (* (reg8 *) key__BIT_MASK)
/* Bypass Enable */
#define key_BYP                    (* (reg8 *) key__BYP)
/* Port wide control signals */                                                   
#define key_CTL                    (* (reg8 *) key__CTL)
/* Drive Modes */
#define key_DM0                    (* (reg8 *) key__DM0) 
#define key_DM1                    (* (reg8 *) key__DM1)
#define key_DM2                    (* (reg8 *) key__DM2) 
/* Input Buffer Disable Override */
#define key_INP_DIS                (* (reg8 *) key__INP_DIS)
/* LCD Common or Segment Drive */
#define key_LCD_COM_SEG            (* (reg8 *) key__LCD_COM_SEG)
/* Enable Segment LCD */
#define key_LCD_EN                 (* (reg8 *) key__LCD_EN)
/* Slew Rate Control */
#define key_SLW                    (* (reg8 *) key__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define key_PRTDSI__CAPS_SEL       (* (reg8 *) key__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define key_PRTDSI__DBL_SYNC_IN    (* (reg8 *) key__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define key_PRTDSI__OE_SEL0        (* (reg8 *) key__PRTDSI__OE_SEL0) 
#define key_PRTDSI__OE_SEL1        (* (reg8 *) key__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define key_PRTDSI__OUT_SEL0       (* (reg8 *) key__PRTDSI__OUT_SEL0) 
#define key_PRTDSI__OUT_SEL1       (* (reg8 *) key__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define key_PRTDSI__SYNC_OUT       (* (reg8 *) key__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(key__SIO_CFG)
    #define key_SIO_HYST_EN        (* (reg8 *) key__SIO_HYST_EN)
    #define key_SIO_REG_HIFREQ     (* (reg8 *) key__SIO_REG_HIFREQ)
    #define key_SIO_CFG            (* (reg8 *) key__SIO_CFG)
    #define key_SIO_DIFF           (* (reg8 *) key__SIO_DIFF)
#endif /* (key__SIO_CFG) */

/* Interrupt Registers */
#if defined(key__INTSTAT)
    #define key_INTSTAT            (* (reg8 *) key__INTSTAT)
    #define key_SNAP               (* (reg8 *) key__SNAP)
    
	#define key_0_INTTYPE_REG 		(* (reg8 *) key__0__INTTYPE)
#endif /* (key__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_key_H */


/* [] END OF FILE */
