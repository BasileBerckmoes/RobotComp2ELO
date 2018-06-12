/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
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
*        Function Prototypes             
***************************************/    

void    `$INSTANCE_NAME`_Write(uint8 value) `=ReentrantKeil($INSTANCE_NAME ."_Write")`;
void    `$INSTANCE_NAME`_SetDriveMode(uint8 mode) `=ReentrantKeil($INSTANCE_NAME ."_SetDriveMode")`;
uint8   `$INSTANCE_NAME`_ReadDataReg(void) `=ReentrantKeil($INSTANCE_NAME ."_ReadDataReg")`;
uint8   `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME ."_Read")`;
uint8   `$INSTANCE_NAME`_ClearInterrupt(void) `=ReentrantKeil($INSTANCE_NAME ."_ClearInterrupt")`;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define `$INSTANCE_NAME`_DRIVE_MODE_BITS        (3)
#define `$INSTANCE_NAME`_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - `$INSTANCE_NAME`_DRIVE_MODE_BITS))
#define `$INSTANCE_NAME`_DRIVE_MODE_SHIFT       (0x00u)
#define `$INSTANCE_NAME`_DRIVE_MODE_MASK        (0x07u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)

#define `$INSTANCE_NAME`_DM_ALG_HIZ         (0x00u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
#define `$INSTANCE_NAME`_DM_DIG_HIZ         (0x01u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
#define `$INSTANCE_NAME`_DM_RES_UP          (0x02u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
#define `$INSTANCE_NAME`_DM_RES_DWN         (0x03u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
#define `$INSTANCE_NAME`_DM_OD_LO           (0x04u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
#define `$INSTANCE_NAME`_DM_OD_HI           (0x05u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
#define `$INSTANCE_NAME`_DM_STRONG          (0x06u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)
#define `$INSTANCE_NAME`_DM_RES_UPDWN       (0x07u << `$INSTANCE_NAME`_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define `$INSTANCE_NAME`_MASK               `$INSTANCE_NAME`__MASK
#define `$INSTANCE_NAME`_SHIFT              `$INSTANCE_NAME`__SHIFT
#define `$INSTANCE_NAME`_WIDTH              `$NumPins`u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define `$INSTANCE_NAME`_PS                     (* (reg32 *) `$INSTANCE_NAME`__PS)
/* Port Configuration */
#define `$INSTANCE_NAME`_PC                     (* (reg32 *) `$INSTANCE_NAME`__PC)
/* Data Register */
#define `$INSTANCE_NAME`_DR                     (* (reg32 *) `$INSTANCE_NAME`__DR)
/* Input Buffer Disable Override */
#define `$INSTANCE_NAME`_INP_DIS                (* (reg32 *) `$INSTANCE_NAME`__PC2)


#if defined(`$INSTANCE_NAME`__INTSTAT)  /* Interrupt Registers */

    #define `$INSTANCE_NAME`_INTSTAT                (* (reg32 *) `$INSTANCE_NAME`__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins `$INSTANCE_NAME`_H */


/* [] END OF FILE */
