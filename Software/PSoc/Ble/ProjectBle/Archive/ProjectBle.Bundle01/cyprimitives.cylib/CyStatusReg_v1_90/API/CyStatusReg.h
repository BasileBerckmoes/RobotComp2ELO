/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_`$INSTANCE_NAME`_H) /* CY_STATUS_REG_`$INSTANCE_NAME`_H */
#define CY_STATUS_REG_`$INSTANCE_NAME`_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
    #include "CyLib.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`;
void `$INSTANCE_NAME`_InterruptEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_InterruptEnable")`;
void `$INSTANCE_NAME`_InterruptDisable(void) `=ReentrantKeil($INSTANCE_NAME . "_InterruptDisable")`;
void `$INSTANCE_NAME`_WriteMask(uint8 mask) `=ReentrantKeil($INSTANCE_NAME . "_WriteMask")`;
uint8 `$INSTANCE_NAME`_ReadMask(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadMask")`;


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define `$INSTANCE_NAME`_INPUTS              `$NumInputs`


/***************************************
*             Registers
***************************************/

/* Status Register */
#define `$INSTANCE_NAME`_Status             (* (reg8 *) `$INSTANCE_NAME`_`$stsRegReplcStr`_sts_reg__STATUS_REG )
#define `$INSTANCE_NAME`_Status_PTR         (  (reg8 *) `$INSTANCE_NAME`_`$stsRegReplcStr`_sts_reg__STATUS_REG )
#define `$INSTANCE_NAME`_Status_Mask        (* (reg8 *) `$INSTANCE_NAME`_`$stsRegReplcStr`_sts_reg__MASK_REG )
#define `$INSTANCE_NAME`_Status_Aux_Ctrl    (* (reg8 *) `$INSTANCE_NAME`_`$stsRegReplcStr`_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
