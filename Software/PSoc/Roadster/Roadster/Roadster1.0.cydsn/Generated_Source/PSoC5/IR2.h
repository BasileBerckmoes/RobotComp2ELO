/*******************************************************************************
* File Name: IR2.h  
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

#if !defined(CY_PINS_IR2_H) /* Pins IR2_H */
#define CY_PINS_IR2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IR2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IR2__PORT == 15 && ((IR2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IR2_Write(uint8 value);
void    IR2_SetDriveMode(uint8 mode);
uint8   IR2_ReadDataReg(void);
uint8   IR2_Read(void);
void    IR2_SetInterruptMode(uint16 position, uint16 mode);
uint8   IR2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IR2_SetDriveMode() function.
     *  @{
     */
        #define IR2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IR2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IR2_DM_RES_UP          PIN_DM_RES_UP
        #define IR2_DM_RES_DWN         PIN_DM_RES_DWN
        #define IR2_DM_OD_LO           PIN_DM_OD_LO
        #define IR2_DM_OD_HI           PIN_DM_OD_HI
        #define IR2_DM_STRONG          PIN_DM_STRONG
        #define IR2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IR2_MASK               IR2__MASK
#define IR2_SHIFT              IR2__SHIFT
#define IR2_WIDTH              1u

/* Interrupt constants */
#if defined(IR2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IR2_SetInterruptMode() function.
     *  @{
     */
        #define IR2_INTR_NONE      (uint16)(0x0000u)
        #define IR2_INTR_RISING    (uint16)(0x0001u)
        #define IR2_INTR_FALLING   (uint16)(0x0002u)
        #define IR2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IR2_INTR_MASK      (0x01u) 
#endif /* (IR2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IR2_PS                     (* (reg8 *) IR2__PS)
/* Data Register */
#define IR2_DR                     (* (reg8 *) IR2__DR)
/* Port Number */
#define IR2_PRT_NUM                (* (reg8 *) IR2__PRT) 
/* Connect to Analog Globals */                                                  
#define IR2_AG                     (* (reg8 *) IR2__AG)                       
/* Analog MUX bux enable */
#define IR2_AMUX                   (* (reg8 *) IR2__AMUX) 
/* Bidirectional Enable */                                                        
#define IR2_BIE                    (* (reg8 *) IR2__BIE)
/* Bit-mask for Aliased Register Access */
#define IR2_BIT_MASK               (* (reg8 *) IR2__BIT_MASK)
/* Bypass Enable */
#define IR2_BYP                    (* (reg8 *) IR2__BYP)
/* Port wide control signals */                                                   
#define IR2_CTL                    (* (reg8 *) IR2__CTL)
/* Drive Modes */
#define IR2_DM0                    (* (reg8 *) IR2__DM0) 
#define IR2_DM1                    (* (reg8 *) IR2__DM1)
#define IR2_DM2                    (* (reg8 *) IR2__DM2) 
/* Input Buffer Disable Override */
#define IR2_INP_DIS                (* (reg8 *) IR2__INP_DIS)
/* LCD Common or Segment Drive */
#define IR2_LCD_COM_SEG            (* (reg8 *) IR2__LCD_COM_SEG)
/* Enable Segment LCD */
#define IR2_LCD_EN                 (* (reg8 *) IR2__LCD_EN)
/* Slew Rate Control */
#define IR2_SLW                    (* (reg8 *) IR2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IR2_PRTDSI__CAPS_SEL       (* (reg8 *) IR2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IR2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IR2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IR2_PRTDSI__OE_SEL0        (* (reg8 *) IR2__PRTDSI__OE_SEL0) 
#define IR2_PRTDSI__OE_SEL1        (* (reg8 *) IR2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IR2_PRTDSI__OUT_SEL0       (* (reg8 *) IR2__PRTDSI__OUT_SEL0) 
#define IR2_PRTDSI__OUT_SEL1       (* (reg8 *) IR2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IR2_PRTDSI__SYNC_OUT       (* (reg8 *) IR2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IR2__SIO_CFG)
    #define IR2_SIO_HYST_EN        (* (reg8 *) IR2__SIO_HYST_EN)
    #define IR2_SIO_REG_HIFREQ     (* (reg8 *) IR2__SIO_REG_HIFREQ)
    #define IR2_SIO_CFG            (* (reg8 *) IR2__SIO_CFG)
    #define IR2_SIO_DIFF           (* (reg8 *) IR2__SIO_DIFF)
#endif /* (IR2__SIO_CFG) */

/* Interrupt Registers */
#if defined(IR2__INTSTAT)
    #define IR2_INTSTAT            (* (reg8 *) IR2__INTSTAT)
    #define IR2_SNAP               (* (reg8 *) IR2__SNAP)
    
	#define IR2_0_INTTYPE_REG 		(* (reg8 *) IR2__0__INTTYPE)
#endif /* (IR2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IR2_H */


/* [] END OF FILE */
