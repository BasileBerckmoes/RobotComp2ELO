/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains Pin function prototypes and register defines
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
#include "`$INSTANCE_NAME`_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} `$INSTANCE_NAME`_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   `$INSTANCE_NAME`_Read(void);
void    `$INSTANCE_NAME`_Write(uint8 value);
uint8   `$INSTANCE_NAME`_ReadDataReg(void);
#if defined(`$INSTANCE_NAME`__PC) || (CY_PSOC4_4200L) 
    void    `$INSTANCE_NAME`_SetDriveMode(uint8 mode);
#endif
void    `$INSTANCE_NAME`_SetInterruptMode(uint16 position, uint16 mode);
uint8   `$INSTANCE_NAME`_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void `$INSTANCE_NAME`_Sleep(void); 
void `$INSTANCE_NAME`_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(`$INSTANCE_NAME`__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define `$INSTANCE_NAME`_DRIVE_MODE_BITS        (3)
    #define `$INSTANCE_NAME`_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - `$INSTANCE_NAME`_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the `$INSTANCE_NAME`_SetDriveMode() function.
         *  @{
         */
        #define `$INSTANCE_NAME`_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define `$INSTANCE_NAME`_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define `$INSTANCE_NAME`_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define `$INSTANCE_NAME`_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define `$INSTANCE_NAME`_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define `$INSTANCE_NAME`_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define `$INSTANCE_NAME`_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define `$INSTANCE_NAME`_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define `$INSTANCE_NAME`_MASK               `$INSTANCE_NAME`__MASK
#define `$INSTANCE_NAME`_SHIFT              `$INSTANCE_NAME`__SHIFT
#define `$INSTANCE_NAME`_WIDTH              `$NumPins`u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in `$INSTANCE_NAME`_SetInterruptMode() function.
     *  @{
     */
        #define `$INSTANCE_NAME`_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define `$INSTANCE_NAME`_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define `$INSTANCE_NAME`_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define `$INSTANCE_NAME`_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(`$INSTANCE_NAME`__SIO)
    #define `$INSTANCE_NAME`_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(`$INSTANCE_NAME`__PC) && (CY_PSOC4_4200L)
    #define `$INSTANCE_NAME`_USBIO_ENABLE               ((uint32)0x80000000u)
    #define `$INSTANCE_NAME`_USBIO_DISABLE              ((uint32)(~`$INSTANCE_NAME`_USBIO_ENABLE))
    #define `$INSTANCE_NAME`_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define `$INSTANCE_NAME`_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define `$INSTANCE_NAME`_USBIO_ENTER_SLEEP          ((uint32)((1u << `$INSTANCE_NAME`_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << `$INSTANCE_NAME`_USBIO_SUSPEND_DEL_SHIFT)))
    #define `$INSTANCE_NAME`_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << `$INSTANCE_NAME`_USBIO_SUSPEND_SHIFT)))
    #define `$INSTANCE_NAME`_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << `$INSTANCE_NAME`_USBIO_SUSPEND_DEL_SHIFT)))
    #define `$INSTANCE_NAME`_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(`$INSTANCE_NAME`__PC)
    /* Port Configuration */
    #define `$INSTANCE_NAME`_PC                 (* (reg32 *) `$INSTANCE_NAME`__PC)
#endif
/* Pin State */
#define `$INSTANCE_NAME`_PS                     (* (reg32 *) `$INSTANCE_NAME`__PS)
/* Data Register */
#define `$INSTANCE_NAME`_DR                     (* (reg32 *) `$INSTANCE_NAME`__DR)
/* Input Buffer Disable Override */
#define `$INSTANCE_NAME`_INP_DIS                (* (reg32 *) `$INSTANCE_NAME`__PC2)

/* Interrupt configuration Registers */
#define `$INSTANCE_NAME`_INTCFG                 (* (reg32 *) `$INSTANCE_NAME`__INTCFG)
#define `$INSTANCE_NAME`_INTSTAT                (* (reg32 *) `$INSTANCE_NAME`__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define `$INSTANCE_NAME`_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(`$INSTANCE_NAME`__SIO)
    #define `$INSTANCE_NAME`_SIO_REG            (* (reg32 *) `$INSTANCE_NAME`__SIO)
#endif /* (`$INSTANCE_NAME`__SIO_CFG) */

/* USBIO registers */
#if !defined(`$INSTANCE_NAME`__PC) && (CY_PSOC4_4200L)
    #define `$INSTANCE_NAME`_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define `$INSTANCE_NAME`_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define `$INSTANCE_NAME`_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define `$INSTANCE_NAME`_DRIVE_MODE_SHIFT       (0x00u)
#define `$INSTANCE_NAME`_DRIVE_MODE_MASK        (0x07u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins `$INSTANCE_NAME`_H */


/* [] END OF FILE */
