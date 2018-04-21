/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the Programmable
*  Voltage Reference component.
*
* Note:
*  None
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PVref_P4_`$INSTANCE_NAME`_H)
#define CY_PVref_P4_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_SEL_OUTPUT_VOLTAGE      (`$SelOutputVoltage`u)
#define `$INSTANCE_NAME`_SEL_REFERENCE_SOURCE    (`$RefSource`u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} `$INSTANCE_NAME`_backup_struct;


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
void `$INSTANCE_NAME`_SetTap(uint32 dividerTap);
void `$INSTANCE_NAME`_SetVRefSrc(uint32 reference);
/** @} group_general */
/**
* \addtogroup group_power
* @{
*/
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
/** @} power */


/***************************************
*           Global Variables
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8 `$INSTANCE_NAME`_initVar;
/** @} globals */


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_VDDA_MVOLTS             (`$VddaMVolts`u)
#define `$INSTANCE_NAME`_BANDGAP_MVOLTS          (`$BgMVolts`u)

#define `$INSTANCE_NAME`_BANDGAP_REFERENCE       (0u)
#define `$INSTANCE_NAME`_VDDA_REFERENCE          (1u)

#define `$INSTANCE_NAME`_PRB_CTRL_REG_INIT       (`$INSTANCE_NAME`_PRB_IP_ENABLE | \
            (uint32) ((uint32) `$INSTANCE_NAME`_SEL_REFERENCE_SOURCE << `$INSTANCE_NAME`_VDDA_ENABLE_POS))
#define `$INSTANCE_NAME`_PRB_REF_REG_INIT        ( \
            (uint32) ((uint32) `$INSTANCE_NAME`_SEL_REFERENCE_SOURCE << `$INSTANCE_NAME`_VREF_SUPPLY_SEL_POS) | \
            (uint32) ((uint32) (`$INSTANCE_NAME`_SEL_OUTPUT_VOLTAGE - 1u) << `$INSTANCE_NAME`_VREF_LEVEL_SEL_MASK_POS))


/***************************************
*             Registers
***************************************/

/* Programmable Voltage Reference IP block registers */
#define `$INSTANCE_NAME`_PRB_CTRL_REG            (*(reg32*) CYREG_PASS_PRB_CTRL)
#define `$INSTANCE_NAME`_PRB_CTRL_PTR            ( (reg32*) CYREG_PASS_PRB_CTRL)
#define `$INSTANCE_NAME`_PRB_REF_REG             (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_pref_PRB_REF)
#define `$INSTANCE_NAME`_PRB_REF_PTR             ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_pref_PRB_REF)


/***************************************
*       Register Constants
***************************************/

/* Global Programmable Voltage Reference IP block register bits */
#define `$INSTANCE_NAME`_VBGR_BUF_GAIN_MASK_POS  (0u)
#define `$INSTANCE_NAME`_VDDA_ENABLE_POS         (4u)
#define `$INSTANCE_NAME`_DEEPSLEEP_ON_POS        (30u)
#define `$INSTANCE_NAME`_PRB_IP_ENABLE_POS       (31u)

#define `$INSTANCE_NAME`_VBGR_BUF_GAIN_MASK      ((uint32) ((uint32) 0x03u << `$INSTANCE_NAME`_VBGR_BUF_GAIN_MASK_POS))
#define `$INSTANCE_NAME`_VDDA_ENABLE             ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_VDDA_ENABLE_POS))
#define `$INSTANCE_NAME`_DEEPSLEEP_ON            ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_DEEPSLEEP_ON_POS))
#define `$INSTANCE_NAME`_PRB_IP_ENABLE           ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_PRB_IP_ENABLE_POS))

/* VREF Control register bits */
#define `$INSTANCE_NAME`_VREF_ENABLE_POS         (0u)
#define `$INSTANCE_NAME`_VREF_SUPPLY_SEL_POS     (1u)
#define `$INSTANCE_NAME`_VREF_LEVEL_SEL_MASK_POS (4u)

#define `$INSTANCE_NAME`_VREF_ENABLE             ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_VREF_ENABLE_POS))
#define `$INSTANCE_NAME`_VREF_SUPPLY_SEL         ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_VREF_SUPPLY_SEL_POS))
#define `$INSTANCE_NAME`_VREF_LEVEL_SEL_MASK     ((uint32) ((uint32) 0x0Fu << `$INSTANCE_NAME`_VREF_LEVEL_SEL_MASK_POS))

#endif /* End CY_PVref_P4_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
