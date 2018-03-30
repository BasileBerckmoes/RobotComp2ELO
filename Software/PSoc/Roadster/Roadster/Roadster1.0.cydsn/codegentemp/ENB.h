/*******************************************************************************
* File Name: ENB.h  
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

#if !defined(CY_PINS_ENB_H) /* Pins ENB_H */
#define CY_PINS_ENB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ENB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ENB__PORT == 15 && ((ENB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ENB_Write(uint8 value);
void    ENB_SetDriveMode(uint8 mode);
uint8   ENB_ReadDataReg(void);
uint8   ENB_Read(void);
void    ENB_SetInterruptMode(uint16 position, uint16 mode);
uint8   ENB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ENB_SetDriveMode() function.
     *  @{
     */
        #define ENB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ENB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ENB_DM_RES_UP          PIN_DM_RES_UP
        #define ENB_DM_RES_DWN         PIN_DM_RES_DWN
        #define ENB_DM_OD_LO           PIN_DM_OD_LO
        #define ENB_DM_OD_HI           PIN_DM_OD_HI
        #define ENB_DM_STRONG          PIN_DM_STRONG
        #define ENB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ENB_MASK               ENB__MASK
#define ENB_SHIFT              ENB__SHIFT
#define ENB_WIDTH              1u

/* Interrupt constants */
#if defined(ENB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ENB_SetInterruptMode() function.
     *  @{
     */
        #define ENB_INTR_NONE      (uint16)(0x0000u)
        #define ENB_INTR_RISING    (uint16)(0x0001u)
        #define ENB_INTR_FALLING   (uint16)(0x0002u)
        #define ENB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ENB_INTR_MASK      (0x01u) 
#endif /* (ENB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ENB_PS                     (* (reg8 *) ENB__PS)
/* Data Register */
#define ENB_DR                     (* (reg8 *) ENB__DR)
/* Port Number */
#define ENB_PRT_NUM                (* (reg8 *) ENB__PRT) 
/* Connect to Analog Globals */                                                  
#define ENB_AG                     (* (reg8 *) ENB__AG)                       
/* Analog MUX bux enable */
#define ENB_AMUX                   (* (reg8 *) ENB__AMUX) 
/* Bidirectional Enable */                                                        
#define ENB_BIE                    (* (reg8 *) ENB__BIE)
/* Bit-mask for Aliased Register Access */
#define ENB_BIT_MASK               (* (reg8 *) ENB__BIT_MASK)
/* Bypass Enable */
#define ENB_BYP                    (* (reg8 *) ENB__BYP)
/* Port wide control signals */                                                   
#define ENB_CTL                    (* (reg8 *) ENB__CTL)
/* Drive Modes */
#define ENB_DM0                    (* (reg8 *) ENB__DM0) 
#define ENB_DM1                    (* (reg8 *) ENB__DM1)
#define ENB_DM2                    (* (reg8 *) ENB__DM2) 
/* Input Buffer Disable Override */
#define ENB_INP_DIS                (* (reg8 *) ENB__INP_DIS)
/* LCD Common or Segment Drive */
#define ENB_LCD_COM_SEG            (* (reg8 *) ENB__LCD_COM_SEG)
/* Enable Segment LCD */
#define ENB_LCD_EN                 (* (reg8 *) ENB__LCD_EN)
/* Slew Rate Control */
#define ENB_SLW                    (* (reg8 *) ENB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ENB_PRTDSI__CAPS_SEL       (* (reg8 *) ENB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ENB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ENB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ENB_PRTDSI__OE_SEL0        (* (reg8 *) ENB__PRTDSI__OE_SEL0) 
#define ENB_PRTDSI__OE_SEL1        (* (reg8 *) ENB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ENB_PRTDSI__OUT_SEL0       (* (reg8 *) ENB__PRTDSI__OUT_SEL0) 
#define ENB_PRTDSI__OUT_SEL1       (* (reg8 *) ENB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ENB_PRTDSI__SYNC_OUT       (* (reg8 *) ENB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ENB__SIO_CFG)
    #define ENB_SIO_HYST_EN        (* (reg8 *) ENB__SIO_HYST_EN)
    #define ENB_SIO_REG_HIFREQ     (* (reg8 *) ENB__SIO_REG_HIFREQ)
    #define ENB_SIO_CFG            (* (reg8 *) ENB__SIO_CFG)
    #define ENB_SIO_DIFF           (* (reg8 *) ENB__SIO_DIFF)
#endif /* (ENB__SIO_CFG) */

/* Interrupt Registers */
#if defined(ENB__INTSTAT)
    #define ENB_INTSTAT            (* (reg8 *) ENB__INTSTAT)
    #define ENB_SNAP               (* (reg8 *) ENB__SNAP)
    
	#define ENB_0_INTTYPE_REG 		(* (reg8 *) ENB__0__INTTYPE)
#endif /* (ENB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ENB_H */


/* [] END OF FILE */
