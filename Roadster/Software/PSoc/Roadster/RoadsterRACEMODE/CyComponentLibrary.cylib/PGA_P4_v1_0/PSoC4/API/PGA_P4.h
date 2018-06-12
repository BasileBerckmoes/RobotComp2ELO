/***************************************************************************//**
* \file     `$INSTANCE_NAME`.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the public API function prototypes and constants used in
*  the PGA_P4 Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_`$INSTANCE_NAME`_H) 
#define CY_PGA_P4_`$INSTANCE_NAME`_H 

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_VREF_MODE              (`$Vref_Input`u)
#define `$INSTANCE_NAME`_OUTPUT_MODE            (`$OutputBuffer`u)
#define `$INSTANCE_NAME`_DEEPSLEEP_SUPPORT      (`$DeepSleepOperation`u)


/***************************************
*    Variables with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 `$INSTANCE_NAME`_initVar;
/** @} globals */


/***************************************
*        Function Prototypes 
***************************************/

/**
* \addtogroup group_general
* @{
*/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetPower(uint32 powerLevel);
void `$INSTANCE_NAME`_SetGain(uint32 gainLevel);
void `$INSTANCE_NAME`_PumpControl(uint32 onOff);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
/** @} power */


/**************************************
*           API Constants
**************************************/

/* Gain setting constants */
`#cy_declare_enum PGA_P4_Gain`

/* Power setting constants */
`#cy_declare_enum PGA_P4_Power`

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup group_powerLevel
     * \brief Definitions for `$INSTANCE_NAME`_SetPower() function.
     *  @{
     */
    #define `$INSTANCE_NAME`_LOW                ((uint32)`$INSTANCE_NAME`__LOW)
    #define `$INSTANCE_NAME`_MED                ((uint32)`$INSTANCE_NAME`__MED)
    #define `$INSTANCE_NAME`_HIGH               ((uint32)`$INSTANCE_NAME`__HIGH)
    /** @} powerLevel */

    /** \addtogroup group_boostPump
     * \brief Definitions for `$INSTANCE_NAME`_PumpControl() function.
     *  @{
     */
    #define `$INSTANCE_NAME`_BOOST_ON           ((uint32)1u)
    #define `$INSTANCE_NAME`_BOOST_OFF          ((uint32)0u)
    /** @} boostPump */

    /** \addtogroup group_gain
     * \brief Definitions for `$INSTANCE_NAME`_SetGain() function.
     *  @{
     */
    #define `$INSTANCE_NAME`_GAIN_1             ((uint32)`$INSTANCE_NAME`__GAIN_1)
    #define `$INSTANCE_NAME`_GAIN_1_4           ((uint32)`$INSTANCE_NAME`__GAIN_1_4)
    #define `$INSTANCE_NAME`_GAIN_2             ((uint32)`$INSTANCE_NAME`__GAIN_2)
    #define `$INSTANCE_NAME`_GAIN_2_8           ((uint32)`$INSTANCE_NAME`__GAIN_2_8)
    #define `$INSTANCE_NAME`_GAIN_4             ((uint32)`$INSTANCE_NAME`__GAIN_4)
    #define `$INSTANCE_NAME`_GAIN_5_8           ((uint32)`$INSTANCE_NAME`__GAIN_5_8)
    #define `$INSTANCE_NAME`_GAIN_8             ((uint32)`$INSTANCE_NAME`__GAIN_8)
    #define `$INSTANCE_NAME`_GAIN_10_7          ((uint32)`$INSTANCE_NAME`__GAIN_10_7)
    #define `$INSTANCE_NAME`_GAIN_16            ((uint32)`$INSTANCE_NAME`__GAIN_16)
    #define `$INSTANCE_NAME`_GAIN_21_3          ((uint32)`$INSTANCE_NAME`__GAIN_21_3)
    #define `$INSTANCE_NAME`_GAIN_32            ((uint32)`$INSTANCE_NAME`__GAIN_32)
    /** @} gain */
/** @} group_constants */


/***************************************
* Registers
***************************************/

#define `$INSTANCE_NAME`_CTB_CTRL_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTB_CTB_CTRL)
#define `$INSTANCE_NAME`_CTB_CTRL_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__CTB_CTB_CTRL)
#define `$INSTANCE_NAME`_OA_RES_CTRL_REG        (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)
#define `$INSTANCE_NAME`_OA_RES_CTRL_PTR        ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)
#define `$INSTANCE_NAME`_OA_SW_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_SW)
#define `$INSTANCE_NAME`_OA_SW_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_SW)
#define `$INSTANCE_NAME`_OA_COMP_TRIM_REG       (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_COMP_TRIM)
#define `$INSTANCE_NAME`_OA_COMP_TRIM_PTR       ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
* Register Constants
***************************************/

/* `$INSTANCE_NAME`_CTB_CTRL_REG */
#define `$INSTANCE_NAME`_DEEPSLEEP_ON_SHIFT     (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define `$INSTANCE_NAME`_ENABLED_SHIFT          (31u)   /* [31] Enable of the CTB IP */

#define `$INSTANCE_NAME`_DEEPSLEEP_ON           ((uint32)0x01u << `$INSTANCE_NAME`_DEEPSLEEP_ON_SHIFT)
#define `$INSTANCE_NAME`_ENABLED                ((uint32)0x01u << `$INSTANCE_NAME`_ENABLED_SHIFT)

/* `$INSTANCE_NAME`_OA_RES_CTRL_REG */
#define `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT      (0u)    /* [1:0]    Power level */
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT       (11u)   /* [11]     Pump enable */
#define `$INSTANCE_NAME`_RES_TAP_SHIFT          (16u)   /* [19:16]  PGA gain (resistor tap point) */
#define `$INSTANCE_NAME`_C_FB_SHIFT             (24u)   /* [27:24]  Feedback Capacitor */

#define `$INSTANCE_NAME`_OA_PWR_MODE_MASK       ((uint32)0x03u << `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_1X    ((uint32)0x00u << `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_10X   ((uint32)0x01u << `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_MASK  ((uint32)0x01u << `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_SHIFT)
#define `$INSTANCE_NAME`_OA_PUMP_EN             ((uint32)0x01u << `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT)
#define `$INSTANCE_NAME`_RES_TAP_MASK           ((uint32)0x0Fu << `$INSTANCE_NAME`_RES_TAP_SHIFT)
#define `$INSTANCE_NAME`_C_FB_MASK              ((uint32)0x0Fu << `$INSTANCE_NAME`_C_FB_SHIFT)

/** `$INSTANCE_NAME`_OA_COMP_TRIM_REG */
#define `$INSTANCE_NAME`_OA_COMP_TRIM_SHIFT     (0u)    /* [1:0]    Opamp Compensation Capacitor Trim */
#define `$INSTANCE_NAME`_OA_COMP_TRIM_MASK      ((uint32)0x03u << `$INSTANCE_NAME`_OA_COMP_TRIM_SHIFT)

/** `$INSTANCE_NAME`_OA_SW_REG */
#define `$INSTANCE_NAME`_RBOT_TO_VSSA_SHIFT     (28u)   /* Resistor bottom  to VSSA */
#define `$INSTANCE_NAME`_RBOT_TO_VSSA           ((uint32)0x01u << `$INSTANCE_NAME`_RBOT_TO_VSSA_SHIFT)


#endif /* CY_PGA_P4_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
