/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_`$INSTANCE_NAME`_H)
#define CY_OPAMP_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetPower(uint32 power);
void `$INSTANCE_NAME`_PumpControl(uint32 onOff);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define `$INSTANCE_NAME`_LOW_POWER      (1u)
#define `$INSTANCE_NAME`_MED_POWER      (2u)
#define `$INSTANCE_NAME`_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define `$INSTANCE_NAME`_PUMP_ON        (1u)
#define `$INSTANCE_NAME`_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_OUTPUT_CURRENT         (`$OutputCurrent`u)
#define `$INSTANCE_NAME`_POWER                  (`$Power`u)
#define `$INSTANCE_NAME`_MODE                   (`$Mode`u)
#define `$INSTANCE_NAME`_OA_COMP_TRIM_VALUE     (`$Compensation`u)
#define `$INSTANCE_NAME`_DEEPSLEEP_SUPPORT      (`$DeepSleepSupport`u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  `$INSTANCE_NAME`_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define `$INSTANCE_NAME`_CTB_CTRL_REG       (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define `$INSTANCE_NAME`_CTB_CTRL_PTR       ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define `$INSTANCE_NAME`_CTB_CTRL_REG       (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define `$INSTANCE_NAME`_CTB_CTRL_PTR       ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define `$INSTANCE_NAME`_OA_RES_CTRL_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)
#define `$INSTANCE_NAME`_OA_RES_CTRL_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)
#define `$INSTANCE_NAME`_OA_COMP_TRIM_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_COMP_TRIM)
#define `$INSTANCE_NAME`_OA_COMP_TRIM_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* `$INSTANCE_NAME`_CTB_CTRL_REG */
#define `$INSTANCE_NAME`_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define `$INSTANCE_NAME`_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define `$INSTANCE_NAME`_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << `$INSTANCE_NAME`_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define `$INSTANCE_NAME`_CTB_CTRL_ENABLED               ((uint32) 0x01u << `$INSTANCE_NAME`_CTB_CTRL_ENABLED_SHIFT)


/* `$INSTANCE_NAME`_OA_RES_CTRL_REG */
#define `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define `$INSTANCE_NAME`_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define `$INSTANCE_NAME`_OA_PWR_MODE                ((uint32) 0x02u << `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT)
#define `$INSTANCE_NAME`_OA_PWR_MODE_MASK           ((uint32) 0x03u << `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT)
#define `$INSTANCE_NAME`_OA_COMP_EN                 ((uint32) 0x00u << `$INSTANCE_NAME`_OA_COMP_EN_SHIFT)
#define `$INSTANCE_NAME`_OA_PUMP_EN                 ((uint32) 0x01u << `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define `$INSTANCE_NAME`_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (`$INSTANCE_NAME`_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define `$INSTANCE_NAME`_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (`$INSTANCE_NAME`_OA_DRIVE_STR_SEL_10X) : \
                                                                             (`$INSTANCE_NAME`_OA_DRIVE_STR_SEL_1X))
#define `$INSTANCE_NAME`_GET_OA_PWR_MODE(mode)          ((mode) & `$INSTANCE_NAME`_OA_PWR_MODE_MASK)
#define `$INSTANCE_NAME`_CHECK_PWR_MODE_OFF             (0u != (`$INSTANCE_NAME`_OA_RES_CTRL_REG & \
                                                                `$INSTANCE_NAME`_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define `$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT        (0u != `$INSTANCE_NAME`_DEEPSLEEP_SUPPORT) 

#define `$INSTANCE_NAME`_DEFAULT_CTB_CTRL (`$INSTANCE_NAME`_GET_DEEPSLEEP_ON(`$INSTANCE_NAME`_DEEPSLEEP_SUPPORT) | \
                                           `$INSTANCE_NAME`_CTB_CTRL_ENABLED)

#define `$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL (`$INSTANCE_NAME`_OA_COMP_EN | \
                                              `$INSTANCE_NAME`_GET_OA_DRIVE_STR(`$INSTANCE_NAME`_OUTPUT_CURRENT))

#define `$INSTANCE_NAME`_DEFAULT_OA_COMP_TRIM_REG (`$INSTANCE_NAME`_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define `$INSTANCE_NAME`_LOWPOWER                   (`$INSTANCE_NAME`_LOW_POWER)
#define `$INSTANCE_NAME`_MEDPOWER                   (`$INSTANCE_NAME`_MED_POWER)
#define `$INSTANCE_NAME`_HIGHPOWER                  (`$INSTANCE_NAME`_HIGH_POWER)

/* PUMP ON/OFF defines */
#define `$INSTANCE_NAME`_PUMPON                     (`$INSTANCE_NAME`_PUMP_ON)
#define `$INSTANCE_NAME`_PUMPOFF                    (`$INSTANCE_NAME`_PUMP_OFF)

#define `$INSTANCE_NAME`_OA_CTRL                    (`$INSTANCE_NAME`_CTB_CTRL_REG)
#define `$INSTANCE_NAME`_OA_RES_CTRL                (`$INSTANCE_NAME`_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define `$INSTANCE_NAME`_OA_CTB_EN_SHIFT            (`$INSTANCE_NAME`_CTB_CTRL_ENABLED_SHIFT)
#define `$INSTANCE_NAME`_OA_PUMP_CTRL_SHIFT         (`$INSTANCE_NAME`_OA_PUMP_EN_SHIFT)
#define `$INSTANCE_NAME`_OA_PUMP_EN_MASK            (0x800u)
#define `$INSTANCE_NAME`_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
