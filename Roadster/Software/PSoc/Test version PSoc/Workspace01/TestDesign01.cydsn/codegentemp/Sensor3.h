/*******************************************************************************
* File Name: Sensor3.h  
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

#if !defined(CY_PINS_Sensor3_H) /* Pins Sensor3_H */
#define CY_PINS_Sensor3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sensor3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Sensor3__PORT == 15 && ((Sensor3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Sensor3_Write(uint8 value);
void    Sensor3_SetDriveMode(uint8 mode);
uint8   Sensor3_ReadDataReg(void);
uint8   Sensor3_Read(void);
void    Sensor3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Sensor3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Sensor3_SetDriveMode() function.
     *  @{
     */
        #define Sensor3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Sensor3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Sensor3_DM_RES_UP          PIN_DM_RES_UP
        #define Sensor3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Sensor3_DM_OD_LO           PIN_DM_OD_LO
        #define Sensor3_DM_OD_HI           PIN_DM_OD_HI
        #define Sensor3_DM_STRONG          PIN_DM_STRONG
        #define Sensor3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Sensor3_MASK               Sensor3__MASK
#define Sensor3_SHIFT              Sensor3__SHIFT
#define Sensor3_WIDTH              1u

/* Interrupt constants */
#if defined(Sensor3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Sensor3_SetInterruptMode() function.
     *  @{
     */
        #define Sensor3_INTR_NONE      (uint16)(0x0000u)
        #define Sensor3_INTR_RISING    (uint16)(0x0001u)
        #define Sensor3_INTR_FALLING   (uint16)(0x0002u)
        #define Sensor3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Sensor3_INTR_MASK      (0x01u) 
#endif /* (Sensor3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sensor3_PS                     (* (reg8 *) Sensor3__PS)
/* Data Register */
#define Sensor3_DR                     (* (reg8 *) Sensor3__DR)
/* Port Number */
#define Sensor3_PRT_NUM                (* (reg8 *) Sensor3__PRT) 
/* Connect to Analog Globals */                                                  
#define Sensor3_AG                     (* (reg8 *) Sensor3__AG)                       
/* Analog MUX bux enable */
#define Sensor3_AMUX                   (* (reg8 *) Sensor3__AMUX) 
/* Bidirectional Enable */                                                        
#define Sensor3_BIE                    (* (reg8 *) Sensor3__BIE)
/* Bit-mask for Aliased Register Access */
#define Sensor3_BIT_MASK               (* (reg8 *) Sensor3__BIT_MASK)
/* Bypass Enable */
#define Sensor3_BYP                    (* (reg8 *) Sensor3__BYP)
/* Port wide control signals */                                                   
#define Sensor3_CTL                    (* (reg8 *) Sensor3__CTL)
/* Drive Modes */
#define Sensor3_DM0                    (* (reg8 *) Sensor3__DM0) 
#define Sensor3_DM1                    (* (reg8 *) Sensor3__DM1)
#define Sensor3_DM2                    (* (reg8 *) Sensor3__DM2) 
/* Input Buffer Disable Override */
#define Sensor3_INP_DIS                (* (reg8 *) Sensor3__INP_DIS)
/* LCD Common or Segment Drive */
#define Sensor3_LCD_COM_SEG            (* (reg8 *) Sensor3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sensor3_LCD_EN                 (* (reg8 *) Sensor3__LCD_EN)
/* Slew Rate Control */
#define Sensor3_SLW                    (* (reg8 *) Sensor3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sensor3_PRTDSI__CAPS_SEL       (* (reg8 *) Sensor3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sensor3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sensor3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sensor3_PRTDSI__OE_SEL0        (* (reg8 *) Sensor3__PRTDSI__OE_SEL0) 
#define Sensor3_PRTDSI__OE_SEL1        (* (reg8 *) Sensor3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sensor3_PRTDSI__OUT_SEL0       (* (reg8 *) Sensor3__PRTDSI__OUT_SEL0) 
#define Sensor3_PRTDSI__OUT_SEL1       (* (reg8 *) Sensor3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sensor3_PRTDSI__SYNC_OUT       (* (reg8 *) Sensor3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Sensor3__SIO_CFG)
    #define Sensor3_SIO_HYST_EN        (* (reg8 *) Sensor3__SIO_HYST_EN)
    #define Sensor3_SIO_REG_HIFREQ     (* (reg8 *) Sensor3__SIO_REG_HIFREQ)
    #define Sensor3_SIO_CFG            (* (reg8 *) Sensor3__SIO_CFG)
    #define Sensor3_SIO_DIFF           (* (reg8 *) Sensor3__SIO_DIFF)
#endif /* (Sensor3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Sensor3__INTSTAT)
    #define Sensor3_INTSTAT            (* (reg8 *) Sensor3__INTSTAT)
    #define Sensor3_SNAP               (* (reg8 *) Sensor3__SNAP)
    
	#define Sensor3_0_INTTYPE_REG 		(* (reg8 *) Sensor3__0__INTTYPE)
#endif /* (Sensor3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Sensor3_H */


/* [] END OF FILE */
