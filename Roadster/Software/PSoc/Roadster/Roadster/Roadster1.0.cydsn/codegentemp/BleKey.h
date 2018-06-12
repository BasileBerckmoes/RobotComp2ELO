/*******************************************************************************
* File Name: BleKey.h  
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

#if !defined(CY_PINS_BleKey_H) /* Pins BleKey_H */
#define CY_PINS_BleKey_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BleKey_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BleKey__PORT == 15 && ((BleKey__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BleKey_Write(uint8 value);
void    BleKey_SetDriveMode(uint8 mode);
uint8   BleKey_ReadDataReg(void);
uint8   BleKey_Read(void);
void    BleKey_SetInterruptMode(uint16 position, uint16 mode);
uint8   BleKey_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BleKey_SetDriveMode() function.
     *  @{
     */
        #define BleKey_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BleKey_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BleKey_DM_RES_UP          PIN_DM_RES_UP
        #define BleKey_DM_RES_DWN         PIN_DM_RES_DWN
        #define BleKey_DM_OD_LO           PIN_DM_OD_LO
        #define BleKey_DM_OD_HI           PIN_DM_OD_HI
        #define BleKey_DM_STRONG          PIN_DM_STRONG
        #define BleKey_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BleKey_MASK               BleKey__MASK
#define BleKey_SHIFT              BleKey__SHIFT
#define BleKey_WIDTH              1u

/* Interrupt constants */
#if defined(BleKey__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BleKey_SetInterruptMode() function.
     *  @{
     */
        #define BleKey_INTR_NONE      (uint16)(0x0000u)
        #define BleKey_INTR_RISING    (uint16)(0x0001u)
        #define BleKey_INTR_FALLING   (uint16)(0x0002u)
        #define BleKey_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BleKey_INTR_MASK      (0x01u) 
#endif /* (BleKey__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BleKey_PS                     (* (reg8 *) BleKey__PS)
/* Data Register */
#define BleKey_DR                     (* (reg8 *) BleKey__DR)
/* Port Number */
#define BleKey_PRT_NUM                (* (reg8 *) BleKey__PRT) 
/* Connect to Analog Globals */                                                  
#define BleKey_AG                     (* (reg8 *) BleKey__AG)                       
/* Analog MUX bux enable */
#define BleKey_AMUX                   (* (reg8 *) BleKey__AMUX) 
/* Bidirectional Enable */                                                        
#define BleKey_BIE                    (* (reg8 *) BleKey__BIE)
/* Bit-mask for Aliased Register Access */
#define BleKey_BIT_MASK               (* (reg8 *) BleKey__BIT_MASK)
/* Bypass Enable */
#define BleKey_BYP                    (* (reg8 *) BleKey__BYP)
/* Port wide control signals */                                                   
#define BleKey_CTL                    (* (reg8 *) BleKey__CTL)
/* Drive Modes */
#define BleKey_DM0                    (* (reg8 *) BleKey__DM0) 
#define BleKey_DM1                    (* (reg8 *) BleKey__DM1)
#define BleKey_DM2                    (* (reg8 *) BleKey__DM2) 
/* Input Buffer Disable Override */
#define BleKey_INP_DIS                (* (reg8 *) BleKey__INP_DIS)
/* LCD Common or Segment Drive */
#define BleKey_LCD_COM_SEG            (* (reg8 *) BleKey__LCD_COM_SEG)
/* Enable Segment LCD */
#define BleKey_LCD_EN                 (* (reg8 *) BleKey__LCD_EN)
/* Slew Rate Control */
#define BleKey_SLW                    (* (reg8 *) BleKey__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BleKey_PRTDSI__CAPS_SEL       (* (reg8 *) BleKey__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BleKey_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BleKey__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BleKey_PRTDSI__OE_SEL0        (* (reg8 *) BleKey__PRTDSI__OE_SEL0) 
#define BleKey_PRTDSI__OE_SEL1        (* (reg8 *) BleKey__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BleKey_PRTDSI__OUT_SEL0       (* (reg8 *) BleKey__PRTDSI__OUT_SEL0) 
#define BleKey_PRTDSI__OUT_SEL1       (* (reg8 *) BleKey__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BleKey_PRTDSI__SYNC_OUT       (* (reg8 *) BleKey__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BleKey__SIO_CFG)
    #define BleKey_SIO_HYST_EN        (* (reg8 *) BleKey__SIO_HYST_EN)
    #define BleKey_SIO_REG_HIFREQ     (* (reg8 *) BleKey__SIO_REG_HIFREQ)
    #define BleKey_SIO_CFG            (* (reg8 *) BleKey__SIO_CFG)
    #define BleKey_SIO_DIFF           (* (reg8 *) BleKey__SIO_DIFF)
#endif /* (BleKey__SIO_CFG) */

/* Interrupt Registers */
#if defined(BleKey__INTSTAT)
    #define BleKey_INTSTAT            (* (reg8 *) BleKey__INTSTAT)
    #define BleKey_SNAP               (* (reg8 *) BleKey__SNAP)
    
	#define BleKey_0_INTTYPE_REG 		(* (reg8 *) BleKey__0__INTTYPE)
#endif /* (BleKey__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BleKey_H */


/* [] END OF FILE */
