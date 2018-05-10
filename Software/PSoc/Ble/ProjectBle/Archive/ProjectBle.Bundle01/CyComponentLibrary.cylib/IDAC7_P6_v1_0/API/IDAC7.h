/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the IDAC7
*  component.
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_IDAC7_`$INSTANCE_NAME`_H)
#define CY_IDAC7_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "syslib/cy_syslib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_CURRENT_VALUE        ((uint32_t)`$Value`)
#define `$INSTANCE_NAME`_CURRENT_RANGE        ((uint32_t)`$IDACRange`)
#define `$INSTANCE_NAME`_CURRENT_POLARITY     ((uint32_t)`$Polarity`)


/**************************************
*    Enumerated Types and Parameters
**************************************/

/* IDAC7 polarity setting constants */
`#cy_declare_enum PolarityType`

/* IDAC7 range setting constants */
`#cy_declare_enum RangeType`

/* IDAC7 polarity setting definitions */
#define `$INSTANCE_NAME`_POL_SOURCE           ((uint32_t)`$INSTANCE_NAME`__POL_SOURCE)
#define `$INSTANCE_NAME`_POL_SINK             ((uint32_t)`$INSTANCE_NAME`__POL_SINK)

/* IDAC7 range setting definitions */
#define `$INSTANCE_NAME`_RNG_4_96UA           ((uint32_t)`$INSTANCE_NAME`__RNG_4_96UA)
#define `$INSTANCE_NAME`_RNG_9_922UA          ((uint32_t)`$INSTANCE_NAME`__RNG_9_92UA)
#define `$INSTANCE_NAME`_RNG_39_69UA          ((uint32_t)`$INSTANCE_NAME`__RNG_39_69UA)
#define `$INSTANCE_NAME`_RNG_79_38UA          ((uint32_t)`$INSTANCE_NAME`__RNG_79_38UA)
#define `$INSTANCE_NAME`_RNG_317_5UA          ((uint32_t)`$INSTANCE_NAME`__RNG_317_5UA)
#define `$INSTANCE_NAME`_RNG_635_0UA          ((uint32_t)`$INSTANCE_NAME`__RNG_635_0UA)


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
void `$INSTANCE_NAME`_SetValue(uint32_t current);
void `$INSTANCE_NAME`_SetPolarity(uint32_t polarity);
void `$INSTANCE_NAME`_SetRange(uint32_t range);
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
extern uint32_t `$INSTANCE_NAME`_initVar;
/** @} globals */


/***************************************
*            API Constants
***************************************/

/* CSD Config register constants */
#define `$INSTANCE_NAME`_CSD_CONFIG_ENABLE_POS   ((uint32_t)31u)
#define `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN_POS ((uint32_t)12u)
#define `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN     ((uint32_t)(0x1u) <<  `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN_POS)
#define `$INSTANCE_NAME`_CSD_CONFIG_ENABLE       ((uint32_t)(0x1u) <<  `$INSTANCE_NAME`_CSD_CONFIG_ENABLE_POS)

/* IDAC register constants */
#define `$INSTANCE_NAME`_CURRENT_VALUE_POS       ((uint32_t)0u)
#define `$INSTANCE_NAME`_POLY_DYN_POS            ((uint32_t)7u)
#define `$INSTANCE_NAME`_POLARITY_POS            ((uint32_t)8u)
#define `$INSTANCE_NAME`_LEG1_MODE_POS           ((uint32_t)16u)
#define `$INSTANCE_NAME`_LEG2_MODE_POS           ((uint32_t)18u)
#define `$INSTANCE_NAME`_DSI_CTRL_EN_POS         ((uint32_t)21u)
#define `$INSTANCE_NAME`_RANGE_POS               ((uint32_t)22u)
#define `$INSTANCE_NAME`_LEG1_EN_POS             ((uint32_t)24u)
#define `$INSTANCE_NAME`_LEG2_EN_POS             ((uint32_t)25u)

#define `$INSTANCE_NAME`_CURRENT_VALUE_MASK      ((uint32_t)(0x7Fu)  <<  `$INSTANCE_NAME`_CURRENT_VALUE_POS)
#define `$INSTANCE_NAME`_POLARITY_MASK           ((uint32_t)(0x3u)   <<  `$INSTANCE_NAME`_POLARITY_POS)
#define `$INSTANCE_NAME`_POLY_DYN                ((uint32_t)(0x1u)   <<  `$INSTANCE_NAME`_POLY_DYN_POS)
#define `$INSTANCE_NAME`_LEG1_MODE_MASK          ((uint32_t)(0x3u)   <<  `$INSTANCE_NAME`_LEG1_MODE_POS)
#define `$INSTANCE_NAME`_LEG2_MODE_MASK          ((uint32_t)(0x3u)   <<  `$INSTANCE_NAME`_LEG2_MODE_POS)
#define `$INSTANCE_NAME`_DSI_CTRL_EN             ((uint32_t)(0x1u)   <<  `$INSTANCE_NAME`_DSI_CTRL_EN_POS)
#define `$INSTANCE_NAME`_RANGE_MASK              ((uint32_t)(0x3u)   <<  `$INSTANCE_NAME`_RANGE_POS)
#define `$INSTANCE_NAME`_LEG1_EN                 ((uint32_t)(0x1u)   <<  `$INSTANCE_NAME`_LEG1_EN_POS)
#define `$INSTANCE_NAME`_LEG2_EN                 ((uint32_t)(0x1u)   <<  `$INSTANCE_NAME`_LEG2_EN_POS)


/***************************************
*        Registers
***************************************/

/* The pointer to the base address of the HW CSD instance. */
#define `$INSTANCE_NAME`_CSD_HW                  (`$INSTANCE_NAME`_cy_mxs40_csidac__HW)

/* CSD Configuration and Control register */
#define `$INSTANCE_NAME`_CSD_CONTROL_REG         (`$INSTANCE_NAME`_CSD_HW->CONFIG)
#define `$INSTANCE_NAME`_CSD_CONTROL_PTR         ( (reg32 *) &`$INSTANCE_NAME`_CSD_HW->CONFIG)

#if (0 == `$INSTANCE_NAME`_cy_mxs40_csidac__IDX)
    /* IDACA Configuration register */
    #define `$INSTANCE_NAME`_IDAC_CONTROL_REG    (`$INSTANCE_NAME`_CSD_HW->IDACA)
    #define `$INSTANCE_NAME`_IDAC_CONTROL_PTR    ( (reg32 *) &`$INSTANCE_NAME`_CSD_HW->IDACA)
#else
    /* IDACB Configuration register */
    #define `$INSTANCE_NAME`_IDAC_CONTROL_REG    (`$INSTANCE_NAME`_CSD_HW->IDACB)
    #define `$INSTANCE_NAME`_IDAC_CONTROL_PTR    ( (reg32 *) &`$INSTANCE_NAME`_CSD_HW->IDACB)
#endif /* (0 == `$INSTANCE_NAME`_cy_mxs40_csidac__IDX) */

#endif /* CY_IDAC7_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
