/*******************************************************************************
* File Name: IR5.h  
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

#if !defined(CY_PINS_IR5_H) /* Pins IR5_H */
#define CY_PINS_IR5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IR5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IR5__PORT == 15 && ((IR5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IR5_Write(uint8 value);
void    IR5_SetDriveMode(uint8 mode);
uint8   IR5_ReadDataReg(void);
uint8   IR5_Read(void);
void    IR5_SetInterruptMode(uint16 position, uint16 mode);
uint8   IR5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IR5_SetDriveMode() function.
     *  @{
     */
        #define IR5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IR5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IR5_DM_RES_UP          PIN_DM_RES_UP
        #define IR5_DM_RES_DWN         PIN_DM_RES_DWN
        #define IR5_DM_OD_LO           PIN_DM_OD_LO
        #define IR5_DM_OD_HI           PIN_DM_OD_HI
        #define IR5_DM_STRONG          PIN_DM_STRONG
        #define IR5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IR5_MASK               IR5__MASK
#define IR5_SHIFT              IR5__SHIFT
#define IR5_WIDTH              1u

/* Interrupt constants */
#if defined(IR5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IR5_SetInterruptMode() function.
     *  @{
     */
        #define IR5_INTR_NONE      (uint16)(0x0000u)
        #define IR5_INTR_RISING    (uint16)(0x0001u)
        #define IR5_INTR_FALLING   (uint16)(0x0002u)
        #define IR5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IR5_INTR_MASK      (0x01u) 
#endif /* (IR5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IR5_PS                     (* (reg8 *) IR5__PS)
/* Data Register */
#define IR5_DR                     (* (reg8 *) IR5__DR)
/* Port Number */
#define IR5_PRT_NUM                (* (reg8 *) IR5__PRT) 
/* Connect to Analog Globals */                                                  
#define IR5_AG                     (* (reg8 *) IR5__AG)                       
/* Analog MUX bux enable */
#define IR5_AMUX                   (* (reg8 *) IR5__AMUX) 
/* Bidirectional Enable */                                                        
#define IR5_BIE                    (* (reg8 *) IR5__BIE)
/* Bit-mask for Aliased Register Access */
#define IR5_BIT_MASK               (* (reg8 *) IR5__BIT_MASK)
/* Bypass Enable */
#define IR5_BYP                    (* (reg8 *) IR5__BYP)
/* Port wide control signals */                                                   
#define IR5_CTL                    (* (reg8 *) IR5__CTL)
/* Drive Modes */
#define IR5_DM0                    (* (reg8 *) IR5__DM0) 
#define IR5_DM1                    (* (reg8 *) IR5__DM1)
#define IR5_DM2                    (* (reg8 *) IR5__DM2) 
/* Input Buffer Disable Override */
#define IR5_INP_DIS                (* (reg8 *) IR5__INP_DIS)
/* LCD Common or Segment Drive */
#define IR5_LCD_COM_SEG            (* (reg8 *) IR5__LCD_COM_SEG)
/* Enable Segment LCD */
#define IR5_LCD_EN                 (* (reg8 *) IR5__LCD_EN)
/* Slew Rate Control */
#define IR5_SLW                    (* (reg8 *) IR5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IR5_PRTDSI__CAPS_SEL       (* (reg8 *) IR5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IR5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IR5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IR5_PRTDSI__OE_SEL0        (* (reg8 *) IR5__PRTDSI__OE_SEL0) 
#define IR5_PRTDSI__OE_SEL1        (* (reg8 *) IR5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IR5_PRTDSI__OUT_SEL0       (* (reg8 *) IR5__PRTDSI__OUT_SEL0) 
#define IR5_PRTDSI__OUT_SEL1       (* (reg8 *) IR5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IR5_PRTDSI__SYNC_OUT       (* (reg8 *) IR5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IR5__SIO_CFG)
    #define IR5_SIO_HYST_EN        (* (reg8 *) IR5__SIO_HYST_EN)
    #define IR5_SIO_REG_HIFREQ     (* (reg8 *) IR5__SIO_REG_HIFREQ)
    #define IR5_SIO_CFG            (* (reg8 *) IR5__SIO_CFG)
    #define IR5_SIO_DIFF           (* (reg8 *) IR5__SIO_DIFF)
#endif /* (IR5__SIO_CFG) */

/* Interrupt Registers */
#if defined(IR5__INTSTAT)
    #define IR5_INTSTAT            (* (reg8 *) IR5__INTSTAT)
    #define IR5_SNAP               (* (reg8 *) IR5__SNAP)
    
	#define IR5_0_INTTYPE_REG 		(* (reg8 *) IR5__0__INTTYPE)
#endif /* (IR5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IR5_H */


/* [] END OF FILE */
