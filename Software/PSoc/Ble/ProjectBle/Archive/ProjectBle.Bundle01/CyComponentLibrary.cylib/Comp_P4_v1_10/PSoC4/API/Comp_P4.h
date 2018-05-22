/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMPARATOR_`$INSTANCE_NAME`_H)
#define CY_COMPARATOR_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "CyLib.h"
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
void    `$INSTANCE_NAME`_Init(void);
void    `$INSTANCE_NAME`_Enable(void);
void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_SetSpeed(uint32 speed);
uint32  `$INSTANCE_NAME`_ZeroCal(void);
void    `$INSTANCE_NAME`_LoadTrim(uint32 trimVal);
void    `$INSTANCE_NAME`_Sleep(void);
void    `$INSTANCE_NAME`_Wakeup(void);
void    `$INSTANCE_NAME`_SaveConfig(void);
void    `$INSTANCE_NAME`_RestoreConfig(void);
uint32  `$INSTANCE_NAME`_GetCompare(void);
uint32  `$INSTANCE_NAME`_GetInterruptSource(void);
void    `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask);
void    `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask);
void    `$INSTANCE_NAME`_SetInterruptMask(uint32 interruptMask);
uint32  `$INSTANCE_NAME`_GetInterruptMask(void);
uint32  `$INSTANCE_NAME`_GetInterruptSourceMasked(void);
void    `$INSTANCE_NAME`_SetInterruptMode(uint32 mode);
void    `$INSTANCE_NAME`_DisableInterruptOutput(void);

#define `$INSTANCE_NAME`_EnableInterruptOutput(void)     `$INSTANCE_NAME`_SetInterruptMask(`$INSTANCE_NAME`_GetInterruptMask() | `$INSTANCE_NAME`_INTR_MASK)
#define `$INSTANCE_NAME`_GetInterruptOutputStatus(void)  ((0u == (`$INSTANCE_NAME`_GetInterruptSourceMasked() & `$INSTANCE_NAME`_INTR_MASKED)) ? 0u : 1u)
#define `$INSTANCE_NAME`_ClearInterruptOutput(void)      `$INSTANCE_NAME`_ClearInterrupt(`$INSTANCE_NAME`_INTR)
#define `$INSTANCE_NAME`_SetInterruptOutput(void)        `$INSTANCE_NAME`_SetInterrupt(`$INSTANCE_NAME`_INTR_MASK)

/**************************************
*           API Constants
**************************************/

/* Power constants for SetSpeed() function */
#define `$INSTANCE_NAME`_SLOW_SPEED     (0x01u)
#define `$INSTANCE_NAME`_MED_SPEED      (0x02u)
#define `$INSTANCE_NAME`_HIGH_SPEED     (0x03u)

/* Trim defines for ZeroCal() function */
#define `$INSTANCE_NAME`_COMP_TRIM_SIGN_SHIFT   (5u)
#define `$INSTANCE_NAME`_COMP_TRIM_MAX_VALUE    (32u)
#define `$INSTANCE_NAME`_COMP_CALIBRATION_DELAY (10u)

/* Constants for `$INSTANCE_NAME`_SetInterruptMode(), mode parameter */
#define `$INSTANCE_NAME`_INTR_DISABLE       (0x00u)
#define `$INSTANCE_NAME`_INTR_RISING        (0x01u)
#define `$INSTANCE_NAME`_INTR_FALLING       (0x02u)
#define `$INSTANCE_NAME`_INTR_BOTH          (0x03u)

/* Constants for `$INSTANCE_NAME`_GetInterruptSource() and 
* `$INSTANCE_NAME`_ClearInterrupt(), interruptMask parameter 
*/
#define `$INSTANCE_NAME`_INTR_SHIFT         (`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_SHIFT)
#define `$INSTANCE_NAME`_INTR               ((uint32)0x01u << `$INSTANCE_NAME`_INTR_SHIFT)

/* Constants for `$INSTANCE_NAME`_SetInterrupt(), interruptMask parameter */
#define `$INSTANCE_NAME`_INTR_SET_SHIFT     (`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_SET_SHIFT)
#define `$INSTANCE_NAME`_INTR_SET           ((uint32)0x01u << `$INSTANCE_NAME`_INTR_SHIFT)

/* Constants for `$INSTANCE_NAME`_GetInterruptMask() and 
* `$INSTANCE_NAME`_SetInterruptMask(), interruptMask parameter 
*/
#define `$INSTANCE_NAME`_INTR_MASK_SHIFT    (`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_MASK_SHIFT)
#define `$INSTANCE_NAME`_INTR_MASK          ((uint32)0x01u << `$INSTANCE_NAME`_INTR_MASK_SHIFT)

/* Constants for `$INSTANCE_NAME`_GetInterruptSourceMasked() */ 
#define `$INSTANCE_NAME`_INTR_MASKED_SHIFT  (`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_MASKED_SHIFT)
#define `$INSTANCE_NAME`_INTR_MASKED        ((uint32)0x01u << `$INSTANCE_NAME`_INTR_MASKED_SHIFT)


/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_HYSTERESIS         (`$Hysteresis`u)
#define `$INSTANCE_NAME`_POWER              (`$Power`u)
#define `$INSTANCE_NAME`_DEEPSLEEP_SUPPORT  (`$DeepSleepSupport`u)
#define `$INSTANCE_NAME`_INTERRUPT_EN       (`$InterruptEnabled`u)
#define `$INSTANCE_NAME`_INTERRUPT          (`$Interrupt`u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  `$INSTANCE_NAME`_initVar;


/**************************************
*             Registers
**************************************/

#define `$INSTANCE_NAME`_CTB_CTRL_REG               (* (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define `$INSTANCE_NAME`_CTB_CTRL_PTR               (  (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTBM_CTB_CTRL)

#define `$INSTANCE_NAME`_OA_RES_CTRL_REG            (* (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)
#define `$INSTANCE_NAME`_OA_RES_CTRL_PTR            (  (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)

#define `$INSTANCE_NAME`_OA_COMP_STAT_REG           (* (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__COMP_STAT)
#define `$INSTANCE_NAME`_OA_COMP_STAT_PTR           (  (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__COMP_STAT)

#define `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG         (* (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_OFFSET_TRIM)
#define `$INSTANCE_NAME`_OA_OFFSET_TRIM_PTR         (  (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_OFFSET_TRIM)

#define `$INSTANCE_NAME`_OA_SLOPE_OFFSET_TRIM_REG   (* (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_SLOPE_OFFSET_TRIM)
#define `$INSTANCE_NAME`_OA_SLOPE_OFFSET_TRIM_PTR   (  (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_SLOPE_OFFSET_TRIM)

#define `$INSTANCE_NAME`_OA_COMP_SHIFT              (`$INSTANCE_NAME`_cy_psoc4_abuf__COMP_STAT_SHIFT)

#define `$INSTANCE_NAME`_INTR_REG       (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR)
#define `$INSTANCE_NAME`_INTR_PTR       ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR)

#define `$INSTANCE_NAME`_INTR_SET_REG   (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_SET)
#define `$INSTANCE_NAME`_INTR_SET_PTR   ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_SET)

#define `$INSTANCE_NAME`_INTR_MASK_REG    (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_MASK) 
#define `$INSTANCE_NAME`_INTR_MASK_PTR    ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_MASK) 

#define `$INSTANCE_NAME`_INTR_MASKED_REG  (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_MASKED) 
#define `$INSTANCE_NAME`_INTR_MASKED_PTR  ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__INTR_MASKED)

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
#define `$INSTANCE_NAME`_OA_COMP_EN_SHIFT           (4u)    /* [4]      Comparator enable */
#define `$INSTANCE_NAME`_OA_HYST_EN_SHIFT           (5u)    /* [5]      Hysteresis enable (10mV) */
#define `$INSTANCE_NAME`_OA_BYPASS_DSI_SYNC_SHIFT   (6u)    /* [6]      Bypass comparator output synchronization for DSI (trigger) output */
#define `$INSTANCE_NAME`_OA_COMPINT_SHIFT           (8u)    /* [9:8]    Sets Interrupt mode */
#define `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */

#define `$INSTANCE_NAME`_OA_PWR_MODE                ((uint32) 0x02u << `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT)
#define `$INSTANCE_NAME`_OA_PWR_MODE_MASK           ((uint32) 0x03u << `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT)
#define `$INSTANCE_NAME`_OA_COMP_EN                 ((uint32) 0x01u << `$INSTANCE_NAME`_OA_COMP_EN_SHIFT)
#define `$INSTANCE_NAME`_OA_HYST_EN                 ((uint32) 0x01u << `$INSTANCE_NAME`_OA_HYST_EN_SHIFT)
#define `$INSTANCE_NAME`_OA_BYPASS_DSI_SYNC         ((uint32) 0x01u << `$INSTANCE_NAME`_OA_BYPASS_DSI_SYNC_SHIFT)
#define `$INSTANCE_NAME`_OA_COMPINT_MASK            ((uint32) 0x03u << `$INSTANCE_NAME`_OA_COMPINT_SHIFT)
#define `$INSTANCE_NAME`_OA_PUMP_EN                 ((uint32) 0x01u << `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define `$INSTANCE_NAME`_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (`$INSTANCE_NAME`_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define `$INSTANCE_NAME`_GET_OA_HYST_EN(hyst)           ((0u != (hyst)) ? (`$INSTANCE_NAME`_OA_HYST_EN) : (0u))
#define `$INSTANCE_NAME`_GET_OA_PWR_MODE(mode)          ((mode) & `$INSTANCE_NAME`_OA_PWR_MODE_MASK)
#define `$INSTANCE_NAME`_CHECK_PWR_MODE_OFF             (0u != (`$INSTANCE_NAME`_OA_RES_CTRL_REG & \
                                                                `$INSTANCE_NAME`_OA_PWR_MODE_MASK))
#define `$INSTANCE_NAME`_GET_OA_COMPINT(intType)        ((uint32) ((((uint32)(intType) << `$INSTANCE_NAME`_OA_COMPINT_SHIFT)) & \
                                                        `$INSTANCE_NAME`_OA_COMPINT_MASK))

#define `$INSTANCE_NAME`_GET_INTR_MASK(mask)            ((0u != (mask)) ? (`$INSTANCE_NAME`_INTR_MASK) : (0u))

/* Returns true if component available in Deep Sleep power mode*/ 
#define `$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT        (0u != `$INSTANCE_NAME`_DEEPSLEEP_SUPPORT) 

#define `$INSTANCE_NAME`_DEFAULT_CTB_CTRL (`$INSTANCE_NAME`_GET_DEEPSLEEP_ON(`$INSTANCE_NAME`_DEEPSLEEP_SUPPORT) | \
                                           `$INSTANCE_NAME`_CTB_CTRL_ENABLED)

#define `$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL (`$INSTANCE_NAME`_OA_COMP_EN | \
                                              `$INSTANCE_NAME`_GET_OA_HYST_EN(`$INSTANCE_NAME`_HYSTERESIS)  | \
                                              `$INSTANCE_NAME`_GET_OA_COMPINT(`$INSTANCE_NAME`_INTERRUPT) |\
                                              `$INSTANCE_NAME`_OA_BYPASS_DSI_SYNC)

#define `$INSTANCE_NAME`_INTR_MASK_REG_DEFAULT  (`$INSTANCE_NAME`_GET_INTR_MASK(`$INSTANCE_NAME`_INTERRUPT_EN))


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

/* Power constants for SetSpeed() function */
#define `$INSTANCE_NAME`_SLOWSPEED      (`$INSTANCE_NAME`_SLOW_SPEED)
#define `$INSTANCE_NAME`_MEDSPEED       (`$INSTANCE_NAME`_MED_SPEED)
#define `$INSTANCE_NAME`_HIGHSPEED      (`$INSTANCE_NAME`_HIGH_SPEED)

#define `$INSTANCE_NAME`_OA_CTRL_REG        (`$INSTANCE_NAME`_OA_RES_CTRL_REG)
#define `$INSTANCE_NAME`_OA_COMPSTAT_REG    (`$INSTANCE_NAME`_OA_COMP_STAT_REG)
#define `$INSTANCE_NAME`_OA_COMPSHIFT       (`$INSTANCE_NAME`_OA_COMP_SHIFT)

#define `$INSTANCE_NAME`_OA_CTB_EN_SHIFT    (`$INSTANCE_NAME`_CTB_CTRL_ENABLED_SHIFT)
#define `$INSTANCE_NAME`_OA_PWR_MODE_HIGH   (`$INSTANCE_NAME`_HIGH_SPEED) 
#define `$INSTANCE_NAME`_OA_BYPASS_SHIFT    (`$INSTANCE_NAME`_OA_BYPASS_DSI_SYNC_SHIFT)

#endif /*  CY_COMPARATOR_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
