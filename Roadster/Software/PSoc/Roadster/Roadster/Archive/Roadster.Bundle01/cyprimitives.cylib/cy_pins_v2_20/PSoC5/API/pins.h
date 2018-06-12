/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
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

#if !defined(CY_PINS_`$INSTANCE_NAME`_H) /* Pins `$INSTANCE_NAME`_H */
#define CY_PINS_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "`$INSTANCE_NAME`_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 `$INSTANCE_NAME`__PORT == 15 && ((`$INSTANCE_NAME`__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    `$INSTANCE_NAME`_Write(uint8 value);
void    `$INSTANCE_NAME`_SetDriveMode(uint8 mode);
uint8   `$INSTANCE_NAME`_ReadDataReg(void);
uint8   `$INSTANCE_NAME`_Read(void);
void    `$INSTANCE_NAME`_SetInterruptMode(uint16 position, uint16 mode);
uint8   `$INSTANCE_NAME`_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the `$INSTANCE_NAME`_SetDriveMode() function.
     *  @{
     */
        #define `$INSTANCE_NAME`_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define `$INSTANCE_NAME`_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define `$INSTANCE_NAME`_DM_RES_UP          PIN_DM_RES_UP
        #define `$INSTANCE_NAME`_DM_RES_DWN         PIN_DM_RES_DWN
        #define `$INSTANCE_NAME`_DM_OD_LO           PIN_DM_OD_LO
        #define `$INSTANCE_NAME`_DM_OD_HI           PIN_DM_OD_HI
        #define `$INSTANCE_NAME`_DM_STRONG          PIN_DM_STRONG
        #define `$INSTANCE_NAME`_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define `$INSTANCE_NAME`_MASK               `$INSTANCE_NAME`__MASK
#define `$INSTANCE_NAME`_SHIFT              `$INSTANCE_NAME`__SHIFT
#define `$INSTANCE_NAME`_WIDTH              `$NumPins`u

/* Interrupt constants */
#if defined(`$INSTANCE_NAME`__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in `$INSTANCE_NAME`_SetInterruptMode() function.
     *  @{
     */
        #define `$INSTANCE_NAME`_INTR_NONE      (uint16)(0x0000u)
        #define `$INSTANCE_NAME`_INTR_RISING    (uint16)(0x0001u)
        #define `$INSTANCE_NAME`_INTR_FALLING   (uint16)(0x0002u)
        #define `$INSTANCE_NAME`_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define `$INSTANCE_NAME`_INTR_MASK      (0x01u) 
#endif /* (`$INSTANCE_NAME`__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define `$INSTANCE_NAME`_PS                     (* (reg8 *) `$INSTANCE_NAME`__PS)
/* Data Register */
#define `$INSTANCE_NAME`_DR                     (* (reg8 *) `$INSTANCE_NAME`__DR)
/* Port Number */
#define `$INSTANCE_NAME`_PRT_NUM                (* (reg8 *) `$INSTANCE_NAME`__PRT) 
/* Connect to Analog Globals */                                                  
#define `$INSTANCE_NAME`_AG                     (* (reg8 *) `$INSTANCE_NAME`__AG)                       
/* Analog MUX bux enable */
#define `$INSTANCE_NAME`_AMUX                   (* (reg8 *) `$INSTANCE_NAME`__AMUX) 
/* Bidirectional Enable */                                                        
#define `$INSTANCE_NAME`_BIE                    (* (reg8 *) `$INSTANCE_NAME`__BIE)
/* Bit-mask for Aliased Register Access */
#define `$INSTANCE_NAME`_BIT_MASK               (* (reg8 *) `$INSTANCE_NAME`__BIT_MASK)
/* Bypass Enable */
#define `$INSTANCE_NAME`_BYP                    (* (reg8 *) `$INSTANCE_NAME`__BYP)
/* Port wide control signals */                                                   
#define `$INSTANCE_NAME`_CTL                    (* (reg8 *) `$INSTANCE_NAME`__CTL)
/* Drive Modes */
#define `$INSTANCE_NAME`_DM0                    (* (reg8 *) `$INSTANCE_NAME`__DM0) 
#define `$INSTANCE_NAME`_DM1                    (* (reg8 *) `$INSTANCE_NAME`__DM1)
#define `$INSTANCE_NAME`_DM2                    (* (reg8 *) `$INSTANCE_NAME`__DM2) 
/* Input Buffer Disable Override */
#define `$INSTANCE_NAME`_INP_DIS                (* (reg8 *) `$INSTANCE_NAME`__INP_DIS)
/* LCD Common or Segment Drive */
#define `$INSTANCE_NAME`_LCD_COM_SEG            (* (reg8 *) `$INSTANCE_NAME`__LCD_COM_SEG)
/* Enable Segment LCD */
#define `$INSTANCE_NAME`_LCD_EN                 (* (reg8 *) `$INSTANCE_NAME`__LCD_EN)
/* Slew Rate Control */
#define `$INSTANCE_NAME`_SLW                    (* (reg8 *) `$INSTANCE_NAME`__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define `$INSTANCE_NAME`_PRTDSI__CAPS_SEL       (* (reg8 *) `$INSTANCE_NAME`__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define `$INSTANCE_NAME`_PRTDSI__DBL_SYNC_IN    (* (reg8 *) `$INSTANCE_NAME`__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define `$INSTANCE_NAME`_PRTDSI__OE_SEL0        (* (reg8 *) `$INSTANCE_NAME`__PRTDSI__OE_SEL0) 
#define `$INSTANCE_NAME`_PRTDSI__OE_SEL1        (* (reg8 *) `$INSTANCE_NAME`__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define `$INSTANCE_NAME`_PRTDSI__OUT_SEL0       (* (reg8 *) `$INSTANCE_NAME`__PRTDSI__OUT_SEL0) 
#define `$INSTANCE_NAME`_PRTDSI__OUT_SEL1       (* (reg8 *) `$INSTANCE_NAME`__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define `$INSTANCE_NAME`_PRTDSI__SYNC_OUT       (* (reg8 *) `$INSTANCE_NAME`__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(`$INSTANCE_NAME`__SIO_CFG)
    #define `$INSTANCE_NAME`_SIO_HYST_EN        (* (reg8 *) `$INSTANCE_NAME`__SIO_HYST_EN)
    #define `$INSTANCE_NAME`_SIO_REG_HIFREQ     (* (reg8 *) `$INSTANCE_NAME`__SIO_REG_HIFREQ)
    #define `$INSTANCE_NAME`_SIO_CFG            (* (reg8 *) `$INSTANCE_NAME`__SIO_CFG)
    #define `$INSTANCE_NAME`_SIO_DIFF           (* (reg8 *) `$INSTANCE_NAME`__SIO_DIFF)
#endif /* (`$INSTANCE_NAME`__SIO_CFG) */

/* Interrupt Registers */
#if defined(`$INSTANCE_NAME`__INTSTAT)
    #define `$INSTANCE_NAME`_INTSTAT            (* (reg8 *) `$INSTANCE_NAME`__INTSTAT)
    #define `$INSTANCE_NAME`_SNAP               (* (reg8 *) `$INSTANCE_NAME`__SNAP)
    
`$IntrPoundDefine_API_GEN`
#endif /* (`$INSTANCE_NAME`__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
