/*******************************************************************************
* File Name: BleState.h  
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

#if !defined(CY_PINS_BleState_H) /* Pins BleState_H */
#define CY_PINS_BleState_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BleState_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BleState__PORT == 15 && ((BleState__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BleState_Write(uint8 value);
void    BleState_SetDriveMode(uint8 mode);
uint8   BleState_ReadDataReg(void);
uint8   BleState_Read(void);
void    BleState_SetInterruptMode(uint16 position, uint16 mode);
uint8   BleState_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BleState_SetDriveMode() function.
     *  @{
     */
        #define BleState_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BleState_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BleState_DM_RES_UP          PIN_DM_RES_UP
        #define BleState_DM_RES_DWN         PIN_DM_RES_DWN
        #define BleState_DM_OD_LO           PIN_DM_OD_LO
        #define BleState_DM_OD_HI           PIN_DM_OD_HI
        #define BleState_DM_STRONG          PIN_DM_STRONG
        #define BleState_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BleState_MASK               BleState__MASK
#define BleState_SHIFT              BleState__SHIFT
#define BleState_WIDTH              1u

/* Interrupt constants */
#if defined(BleState__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BleState_SetInterruptMode() function.
     *  @{
     */
        #define BleState_INTR_NONE      (uint16)(0x0000u)
        #define BleState_INTR_RISING    (uint16)(0x0001u)
        #define BleState_INTR_FALLING   (uint16)(0x0002u)
        #define BleState_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BleState_INTR_MASK      (0x01u) 
#endif /* (BleState__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BleState_PS                     (* (reg8 *) BleState__PS)
/* Data Register */
#define BleState_DR                     (* (reg8 *) BleState__DR)
/* Port Number */
#define BleState_PRT_NUM                (* (reg8 *) BleState__PRT) 
/* Connect to Analog Globals */                                                  
#define BleState_AG                     (* (reg8 *) BleState__AG)                       
/* Analog MUX bux enable */
#define BleState_AMUX                   (* (reg8 *) BleState__AMUX) 
/* Bidirectional Enable */                                                        
#define BleState_BIE                    (* (reg8 *) BleState__BIE)
/* Bit-mask for Aliased Register Access */
#define BleState_BIT_MASK               (* (reg8 *) BleState__BIT_MASK)
/* Bypass Enable */
#define BleState_BYP                    (* (reg8 *) BleState__BYP)
/* Port wide control signals */                                                   
#define BleState_CTL                    (* (reg8 *) BleState__CTL)
/* Drive Modes */
#define BleState_DM0                    (* (reg8 *) BleState__DM0) 
#define BleState_DM1                    (* (reg8 *) BleState__DM1)
#define BleState_DM2                    (* (reg8 *) BleState__DM2) 
/* Input Buffer Disable Override */
#define BleState_INP_DIS                (* (reg8 *) BleState__INP_DIS)
/* LCD Common or Segment Drive */
#define BleState_LCD_COM_SEG            (* (reg8 *) BleState__LCD_COM_SEG)
/* Enable Segment LCD */
#define BleState_LCD_EN                 (* (reg8 *) BleState__LCD_EN)
/* Slew Rate Control */
#define BleState_SLW                    (* (reg8 *) BleState__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BleState_PRTDSI__CAPS_SEL       (* (reg8 *) BleState__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BleState_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BleState__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BleState_PRTDSI__OE_SEL0        (* (reg8 *) BleState__PRTDSI__OE_SEL0) 
#define BleState_PRTDSI__OE_SEL1        (* (reg8 *) BleState__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BleState_PRTDSI__OUT_SEL0       (* (reg8 *) BleState__PRTDSI__OUT_SEL0) 
#define BleState_PRTDSI__OUT_SEL1       (* (reg8 *) BleState__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BleState_PRTDSI__SYNC_OUT       (* (reg8 *) BleState__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BleState__SIO_CFG)
    #define BleState_SIO_HYST_EN        (* (reg8 *) BleState__SIO_HYST_EN)
    #define BleState_SIO_REG_HIFREQ     (* (reg8 *) BleState__SIO_REG_HIFREQ)
    #define BleState_SIO_CFG            (* (reg8 *) BleState__SIO_CFG)
    #define BleState_SIO_DIFF           (* (reg8 *) BleState__SIO_DIFF)
#endif /* (BleState__SIO_CFG) */

/* Interrupt Registers */
#if defined(BleState__INTSTAT)
    #define BleState_INTSTAT            (* (reg8 *) BleState__INTSTAT)
    #define BleState_SNAP               (* (reg8 *) BleState__SNAP)
    
	#define BleState_0_INTTYPE_REG 		(* (reg8 *) BleState__0__INTTYPE)
#endif /* (BleState__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BleState_H */


/* [] END OF FILE */
