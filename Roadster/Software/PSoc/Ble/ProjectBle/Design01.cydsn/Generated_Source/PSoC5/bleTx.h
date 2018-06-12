/*******************************************************************************
* File Name: bleTx.h  
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

#if !defined(CY_PINS_bleTx_H) /* Pins bleTx_H */
#define CY_PINS_bleTx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bleTx_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bleTx__PORT == 15 && ((bleTx__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bleTx_Write(uint8 value);
void    bleTx_SetDriveMode(uint8 mode);
uint8   bleTx_ReadDataReg(void);
uint8   bleTx_Read(void);
void    bleTx_SetInterruptMode(uint16 position, uint16 mode);
uint8   bleTx_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bleTx_SetDriveMode() function.
     *  @{
     */
        #define bleTx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bleTx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bleTx_DM_RES_UP          PIN_DM_RES_UP
        #define bleTx_DM_RES_DWN         PIN_DM_RES_DWN
        #define bleTx_DM_OD_LO           PIN_DM_OD_LO
        #define bleTx_DM_OD_HI           PIN_DM_OD_HI
        #define bleTx_DM_STRONG          PIN_DM_STRONG
        #define bleTx_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bleTx_MASK               bleTx__MASK
#define bleTx_SHIFT              bleTx__SHIFT
#define bleTx_WIDTH              1u

/* Interrupt constants */
#if defined(bleTx__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bleTx_SetInterruptMode() function.
     *  @{
     */
        #define bleTx_INTR_NONE      (uint16)(0x0000u)
        #define bleTx_INTR_RISING    (uint16)(0x0001u)
        #define bleTx_INTR_FALLING   (uint16)(0x0002u)
        #define bleTx_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bleTx_INTR_MASK      (0x01u) 
#endif /* (bleTx__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bleTx_PS                     (* (reg8 *) bleTx__PS)
/* Data Register */
#define bleTx_DR                     (* (reg8 *) bleTx__DR)
/* Port Number */
#define bleTx_PRT_NUM                (* (reg8 *) bleTx__PRT) 
/* Connect to Analog Globals */                                                  
#define bleTx_AG                     (* (reg8 *) bleTx__AG)                       
/* Analog MUX bux enable */
#define bleTx_AMUX                   (* (reg8 *) bleTx__AMUX) 
/* Bidirectional Enable */                                                        
#define bleTx_BIE                    (* (reg8 *) bleTx__BIE)
/* Bit-mask for Aliased Register Access */
#define bleTx_BIT_MASK               (* (reg8 *) bleTx__BIT_MASK)
/* Bypass Enable */
#define bleTx_BYP                    (* (reg8 *) bleTx__BYP)
/* Port wide control signals */                                                   
#define bleTx_CTL                    (* (reg8 *) bleTx__CTL)
/* Drive Modes */
#define bleTx_DM0                    (* (reg8 *) bleTx__DM0) 
#define bleTx_DM1                    (* (reg8 *) bleTx__DM1)
#define bleTx_DM2                    (* (reg8 *) bleTx__DM2) 
/* Input Buffer Disable Override */
#define bleTx_INP_DIS                (* (reg8 *) bleTx__INP_DIS)
/* LCD Common or Segment Drive */
#define bleTx_LCD_COM_SEG            (* (reg8 *) bleTx__LCD_COM_SEG)
/* Enable Segment LCD */
#define bleTx_LCD_EN                 (* (reg8 *) bleTx__LCD_EN)
/* Slew Rate Control */
#define bleTx_SLW                    (* (reg8 *) bleTx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bleTx_PRTDSI__CAPS_SEL       (* (reg8 *) bleTx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bleTx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bleTx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bleTx_PRTDSI__OE_SEL0        (* (reg8 *) bleTx__PRTDSI__OE_SEL0) 
#define bleTx_PRTDSI__OE_SEL1        (* (reg8 *) bleTx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bleTx_PRTDSI__OUT_SEL0       (* (reg8 *) bleTx__PRTDSI__OUT_SEL0) 
#define bleTx_PRTDSI__OUT_SEL1       (* (reg8 *) bleTx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bleTx_PRTDSI__SYNC_OUT       (* (reg8 *) bleTx__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bleTx__SIO_CFG)
    #define bleTx_SIO_HYST_EN        (* (reg8 *) bleTx__SIO_HYST_EN)
    #define bleTx_SIO_REG_HIFREQ     (* (reg8 *) bleTx__SIO_REG_HIFREQ)
    #define bleTx_SIO_CFG            (* (reg8 *) bleTx__SIO_CFG)
    #define bleTx_SIO_DIFF           (* (reg8 *) bleTx__SIO_DIFF)
#endif /* (bleTx__SIO_CFG) */

/* Interrupt Registers */
#if defined(bleTx__INTSTAT)
    #define bleTx_INTSTAT            (* (reg8 *) bleTx__INTSTAT)
    #define bleTx_SNAP               (* (reg8 *) bleTx__SNAP)
    
	#define bleTx_0_INTTYPE_REG 		(* (reg8 *) bleTx__0__INTTYPE)
#endif /* (bleTx__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bleTx_H */


/* [] END OF FILE */
