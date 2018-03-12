/*******************************************************************************
* File Name: Sensor0.h  
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

#if !defined(CY_PINS_Sensor0_H) /* Pins Sensor0_H */
#define CY_PINS_Sensor0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sensor0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Sensor0__PORT == 15 && ((Sensor0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Sensor0_Write(uint8 value);
void    Sensor0_SetDriveMode(uint8 mode);
uint8   Sensor0_ReadDataReg(void);
uint8   Sensor0_Read(void);
void    Sensor0_SetInterruptMode(uint16 position, uint16 mode);
uint8   Sensor0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Sensor0_SetDriveMode() function.
     *  @{
     */
        #define Sensor0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Sensor0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Sensor0_DM_RES_UP          PIN_DM_RES_UP
        #define Sensor0_DM_RES_DWN         PIN_DM_RES_DWN
        #define Sensor0_DM_OD_LO           PIN_DM_OD_LO
        #define Sensor0_DM_OD_HI           PIN_DM_OD_HI
        #define Sensor0_DM_STRONG          PIN_DM_STRONG
        #define Sensor0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Sensor0_MASK               Sensor0__MASK
#define Sensor0_SHIFT              Sensor0__SHIFT
#define Sensor0_WIDTH              1u

/* Interrupt constants */
#if defined(Sensor0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Sensor0_SetInterruptMode() function.
     *  @{
     */
        #define Sensor0_INTR_NONE      (uint16)(0x0000u)
        #define Sensor0_INTR_RISING    (uint16)(0x0001u)
        #define Sensor0_INTR_FALLING   (uint16)(0x0002u)
        #define Sensor0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Sensor0_INTR_MASK      (0x01u) 
#endif /* (Sensor0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sensor0_PS                     (* (reg8 *) Sensor0__PS)
/* Data Register */
#define Sensor0_DR                     (* (reg8 *) Sensor0__DR)
/* Port Number */
#define Sensor0_PRT_NUM                (* (reg8 *) Sensor0__PRT) 
/* Connect to Analog Globals */                                                  
#define Sensor0_AG                     (* (reg8 *) Sensor0__AG)                       
/* Analog MUX bux enable */
#define Sensor0_AMUX                   (* (reg8 *) Sensor0__AMUX) 
/* Bidirectional Enable */                                                        
#define Sensor0_BIE                    (* (reg8 *) Sensor0__BIE)
/* Bit-mask for Aliased Register Access */
#define Sensor0_BIT_MASK               (* (reg8 *) Sensor0__BIT_MASK)
/* Bypass Enable */
#define Sensor0_BYP                    (* (reg8 *) Sensor0__BYP)
/* Port wide control signals */                                                   
#define Sensor0_CTL                    (* (reg8 *) Sensor0__CTL)
/* Drive Modes */
#define Sensor0_DM0                    (* (reg8 *) Sensor0__DM0) 
#define Sensor0_DM1                    (* (reg8 *) Sensor0__DM1)
#define Sensor0_DM2                    (* (reg8 *) Sensor0__DM2) 
/* Input Buffer Disable Override */
#define Sensor0_INP_DIS                (* (reg8 *) Sensor0__INP_DIS)
/* LCD Common or Segment Drive */
#define Sensor0_LCD_COM_SEG            (* (reg8 *) Sensor0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sensor0_LCD_EN                 (* (reg8 *) Sensor0__LCD_EN)
/* Slew Rate Control */
#define Sensor0_SLW                    (* (reg8 *) Sensor0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sensor0_PRTDSI__CAPS_SEL       (* (reg8 *) Sensor0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sensor0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sensor0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sensor0_PRTDSI__OE_SEL0        (* (reg8 *) Sensor0__PRTDSI__OE_SEL0) 
#define Sensor0_PRTDSI__OE_SEL1        (* (reg8 *) Sensor0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sensor0_PRTDSI__OUT_SEL0       (* (reg8 *) Sensor0__PRTDSI__OUT_SEL0) 
#define Sensor0_PRTDSI__OUT_SEL1       (* (reg8 *) Sensor0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sensor0_PRTDSI__SYNC_OUT       (* (reg8 *) Sensor0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Sensor0__SIO_CFG)
    #define Sensor0_SIO_HYST_EN        (* (reg8 *) Sensor0__SIO_HYST_EN)
    #define Sensor0_SIO_REG_HIFREQ     (* (reg8 *) Sensor0__SIO_REG_HIFREQ)
    #define Sensor0_SIO_CFG            (* (reg8 *) Sensor0__SIO_CFG)
    #define Sensor0_SIO_DIFF           (* (reg8 *) Sensor0__SIO_DIFF)
#endif /* (Sensor0__SIO_CFG) */

/* Interrupt Registers */
#if defined(Sensor0__INTSTAT)
    #define Sensor0_INTSTAT            (* (reg8 *) Sensor0__INTSTAT)
    #define Sensor0_SNAP               (* (reg8 *) Sensor0__SNAP)
    
	#define Sensor0_0_INTTYPE_REG 		(* (reg8 *) Sensor0__0__INTTYPE)
#endif /* (Sensor0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Sensor0_H */


/* [] END OF FILE */
