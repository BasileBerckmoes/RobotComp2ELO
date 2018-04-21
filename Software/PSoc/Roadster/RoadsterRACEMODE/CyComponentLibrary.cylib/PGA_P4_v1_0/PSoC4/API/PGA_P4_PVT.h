/***************************************************************************//**
* \file     `$INSTANCE_NAME`_PVT.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the private constants and macros used in
*  the PGA_P4 Component code.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_`$INSTANCE_NAME`_PVT_H) 
#define CY_PGA_P4_`$INSTANCE_NAME`_PVT_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*         Internal Constants
***************************************/
    
#define `$INSTANCE_NAME`_POWER                  ((uint32)`$Power`u)
#define `$INSTANCE_NAME`_GAIN                   ((uint32)`$Gain`u)
    
#define `$INSTANCE_NAME`_POWER_MAX              (`$INSTANCE_NAME`_HIGH)
#define `$INSTANCE_NAME`_GAIN_MAX               (`$INSTANCE_NAME`_GAIN_32)

/* ((Gain steps / 2) + 1) */
#define `$INSTANCE_NAME`_COMP_TAB_HEIGHT        ((`$INSTANCE_NAME`_GAIN_MAX >> 1u) + 1u)
#define `$INSTANCE_NAME`_COMP_TAB_WIDTH         (`$INSTANCE_NAME`_POWER_MAX)
#define `$INSTANCE_NAME`_GET_COMP_TAB_GAIN_MASK (0x00000007u)

#define `$INSTANCE_NAME`_VREF_INTERNAL          (0u)
#define `$INSTANCE_NAME`_OUTPUT_MODE_10x        (1u)

#define `$INSTANCE_NAME`_DEFAULT_POWER          ((uint32)`$INSTANCE_NAME`_POWER << `$INSTANCE_NAME`_OA_PWR_MODE_SHIFT)
#define `$INSTANCE_NAME`_DEFAULT_GAIN           ((uint32)`$INSTANCE_NAME`_GAIN << `$INSTANCE_NAME`_RES_TAP_SHIFT)
#define `$INSTANCE_NAME`_DEFAULT_GAIN_POWER     (`$INSTANCE_NAME`_DEFAULT_GAIN | `$INSTANCE_NAME`_DEFAULT_POWER)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint32 `$INSTANCE_NAME`_internalGainPower;
extern const uint32 `$INSTANCE_NAME`_compTab[`$INSTANCE_NAME`_COMP_TAB_HEIGHT][`$INSTANCE_NAME`_COMP_TAB_WIDTH];


/***************************************
*       Macro Definitions
***************************************/

/* Returns true if component available in Deep Sleep power mode */
#define `$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT (`$INSTANCE_NAME`_DEEPSLEEP_SUPPORT != 0u)
/* Returns true if component uses 10x (Class AB) output buffer mode*/
#define `$INSTANCE_NAME`_CHECK_OUTPUT_MODE      (`$INSTANCE_NAME`_OUTPUT_MODE == `$INSTANCE_NAME`_OUTPUT_MODE_10x)
#define `$INSTANCE_NAME`_GET_DEEPSLEEP_ON       ((`$INSTANCE_NAME`_CHECK_DEEPSLEEP_SUPPORT) ? \
                                                    (`$INSTANCE_NAME`_DEEPSLEEP_ON) : (0u))
#define `$INSTANCE_NAME`_GET_OA_DRIVE_STR       ((`$INSTANCE_NAME`_CHECK_OUTPUT_MODE) ? \
                                                    (`$INSTANCE_NAME`_OA_DRIVE_STR_SEL_10X) : \
                                                        (`$INSTANCE_NAME`_OA_DRIVE_STR_SEL_1X))
#define `$INSTANCE_NAME`_GET_POWER              (`$INSTANCE_NAME`_internalGainPower & \
                                                    `$INSTANCE_NAME`_OA_PWR_MODE_MASK)
#define `$INSTANCE_NAME`_DEFAULT_CTB_CTRL       (`$INSTANCE_NAME`_GET_DEEPSLEEP_ON | `$INSTANCE_NAME`_ENABLED)
#define `$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL    (`$INSTANCE_NAME`_GET_OA_DRIVE_STR | `$INSTANCE_NAME`_OA_PUMP_EN)
#define `$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL_MASK (`$INSTANCE_NAME`_OA_DRIVE_STR_SEL_MASK | `$INSTANCE_NAME`_OA_PUMP_EN)
#define `$INSTANCE_NAME`_GET_COMP_TAB_GAIN      ((`$INSTANCE_NAME`_internalGainPower >> \
                                                    (`$INSTANCE_NAME`_RES_TAP_SHIFT + 1u)) & \
                                                        `$INSTANCE_NAME`_GET_COMP_TAB_GAIN_MASK)
#define `$INSTANCE_NAME`_GET_COMP_TAB           (`$INSTANCE_NAME`_compTab[`$INSTANCE_NAME`_GET_COMP_TAB_GAIN] \
                                                                         [`$INSTANCE_NAME`_GET_POWER - 1u])
#define `$INSTANCE_NAME`_GET_C_FB               (`$INSTANCE_NAME`_GET_COMP_TAB & `$INSTANCE_NAME`_C_FB_MASK)
#define `$INSTANCE_NAME`_GET_OA_COMP_TRIM       (`$INSTANCE_NAME`_GET_COMP_TAB & `$INSTANCE_NAME`_OA_COMP_TRIM_MASK)


#endif /* CY_PGA_P4_`$INSTANCE_NAME`_PVT_H */

/* [] END OF FILE */
