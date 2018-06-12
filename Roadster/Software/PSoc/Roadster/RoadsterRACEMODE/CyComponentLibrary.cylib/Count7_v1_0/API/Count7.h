/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This header file contains registers and constants associated with the
*  Count7 component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COUNT7_`$INSTANCE_NAME`_H)
#define CY_COUNT7_`$INSTANCE_NAME`_H

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
* Function Prototypes
***************************************/
void  `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void  `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void  `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void  `$INSTANCE_NAME`_WriteCounter(uint8 count) `=ReentrantKeil($INSTANCE_NAME . "_WriteCounter")`;
uint8 `$INSTANCE_NAME`_ReadCounter(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCounter")`;
void  `$INSTANCE_NAME`_WritePeriod(uint8 period) `=ReentrantKeil($INSTANCE_NAME . "_WritePeriod")`;
uint8 `$INSTANCE_NAME`_ReadPeriod(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadPeriod")`;
void  `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void  `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void  `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void  `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;


/***************************************
*     Data Struct Definitions
***************************************/
/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;
    uint8 count;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*           Global Variables
***************************************/
extern `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup;
extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
* Initial Parameter
***************************************/
#define `$INSTANCE_NAME`_INITIAL_PERIOD               (`$Period`u)


/***************************************
* Registers
***************************************/
#define `$INSTANCE_NAME`_COUNT_REG                    (*(reg8 *) `$INSTANCE_NAME`_Counter7__COUNT_REG)
#define `$INSTANCE_NAME`_COUNT_PTR                    ( (reg8 *) `$INSTANCE_NAME`_Counter7__COUNT_REG)
#define `$INSTANCE_NAME`_PERIOD_REG                   (*(reg8 *) `$INSTANCE_NAME`_Counter7__PERIOD_REG)
#define `$INSTANCE_NAME`_PERIOD_PTR                   ( (reg8 *) `$INSTANCE_NAME`_Counter7__PERIOD_REG)
#define `$INSTANCE_NAME`_AUX_CONTROL_REG              (*(reg8 *) `$INSTANCE_NAME`_Counter7__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_AUX_CONTROL_PTR              ( (reg8 *) `$INSTANCE_NAME`_Counter7__CONTROL_AUX_CTL_REG)


/***************************************
* Register Constants
***************************************/
#define `$INSTANCE_NAME`_COUNTER_START                (0x20u)

/* This constant is used to mask the TC bit (bit#7) in the Count register */
#define `$INSTANCE_NAME`_COUNT_7BIT_MASK              (0x7Fu)


#endif /* CY_COUNT7_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
