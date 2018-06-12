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
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_`$INSTANCE_NAME`_H) /* CY_CONTROL_REG_`$INSTANCE_NAME`_H */
#define CY_CONTROL_REG_`$INSTANCE_NAME`_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    `$INSTANCE_NAME`_Write(uint8 control) `=ReentrantKeil($INSTANCE_NAME . "_Write")`;
uint8   `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`;

void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`; 
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define `$INSTANCE_NAME`_Control        (* (reg8 *) `$INSTANCE_NAME`_`$CtlModeReplacementString`_ctrl_reg__CONTROL_REG )
#define `$INSTANCE_NAME`_Control_PTR    (  (reg8 *) `$INSTANCE_NAME`_`$CtlModeReplacementString`_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
