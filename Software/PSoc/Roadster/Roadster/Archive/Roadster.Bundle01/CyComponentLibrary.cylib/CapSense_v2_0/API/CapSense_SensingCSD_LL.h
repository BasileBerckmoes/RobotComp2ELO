/***************************************************************************//**
* \file `$INSTANCE_NAME`_SensingCSD_LL.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the headers of APIs specific to CSD sensing implementation.
*
* \see `$INSTANCE_NAME` v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
*
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_SENSE_`$INSTANCE_NAME`_SENSINGCSD_LL_H)
#define CY_SENSE_`$INSTANCE_NAME`_SENSINGCSD_LL_H

#include "cyfitter_gpio.h"
#include "syslib/cy_syslib.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"

/****************************************************************************
* Register and mode mask definition
****************************************************************************/

#define `$INSTANCE_NAME`_CSD_CSDCMP_INIT                                (`$INSTANCE_NAME`_CSD_CSDCMP_CSDCMP_DISABLED)

/* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
    #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
    #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */
#else
    #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD                   (0x00000000uL)
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
    /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
    #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
    #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
    #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
    #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */
#else
    #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK                   (0x00000000uL)
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

#define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_COARSE                         (`$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD | `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK)

/* C_mod config */
#if ((`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) || (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
    #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_INIT             (`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)
#else
    #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_INIT             (0x00000000uL)
#endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */

/* C_tank config */
#if ((`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) || (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
    #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_INIT            (`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
#else
    #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_INIT            (0x00000000uL)
#endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */

#define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_INIT                 (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCAV_HSCMP)

/* Defining default HW configuration according to settings in customizer. */
#define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG                 (`$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_12MHZ |\
                                                             `$INSTANCE_NAME`_IREF_SRC_CFG |\
                                                             `$INSTANCE_NAME`_PWR_MODE_CFG)

#if(`$INSTANCE_NAME`_SENSING_LEGACY == `$INSTANCE_NAME`_CSD_SENSING_METHOD)

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN)
        /* Enable CSDCMP */
        #define `$INSTANCE_NAME`_CSD_CSDCMP_SCAN                (`$INSTANCE_NAME`_CSD_CSDCMP_CSDCMP_EN_MSK |\
                                                                 `$INSTANCE_NAME`_CSD_CSDCMP_AZ_EN_MSK)
    #else
        /* Enable CSDCMP */
        #define `$INSTANCE_NAME`_CSD_CSDCMP_SCAN                (`$INSTANCE_NAME`_CSD_CSDCMP_CSDCMP_EN_MSK)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK)
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    /* SW_FW_MOD_SEL switches state for Coarse initialization of CMOD (sense path) */
    #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SCAN                 (0x00000000uL)

    #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SCAN            (`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE | \
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2CB_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SCAN            (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)) */

    /* Shield switch default config */
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_HSCMP)
        #else
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1 | \
                                                                     `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP)
        #else
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                     `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #else
        #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN              (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

    #define `$INSTANCE_NAME`_CSD_SW_RES_INIT                        (`$INSTANCE_NAME`_CSD_INIT_SWITCH_RES << CSD_SW_RES_RES_HCAV_Pos)
    #define `$INSTANCE_NAME`_CSD_SW_RES_SCAN                        ((`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CSD_SW_RES_RES_HCBV_Pos) |\
                                                                     (`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CSD_SW_RES_RES_HCBG_Pos))

    #define `$INSTANCE_NAME`_CSD_SHIELD_GPIO_DM                 (CY_GPIO_DM_STRONG_IN_OFF)
    #define `$INSTANCE_NAME`_CSD_SENSOR_HSIOM_SEL               (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE)
    #define `$INSTANCE_NAME`_CSD_SHIELD_HSIOM_SEL               (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD)
    #define `$INSTANCE_NAME`_CSD_CMOD_HSIOM_SEL                 (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA)

    #define `$INSTANCE_NAME`_DEFAULT_IDACA_BALL_MODE            (`$INSTANCE_NAME`_CSD_IDACA_BALL_MODE_FULL <<\
                                                                 `$INSTANCE_NAME`_CSD_IDACA_BALL_MODE_POS)
    #define `$INSTANCE_NAME`_DEFAULT_IDACB_BALL_MODE            (`$INSTANCE_NAME`_CSD_IDACB_BALL_MODE_FULL <<\
                                                                 `$INSTANCE_NAME`_CSD_IDACB_BALL_MODE_POS)

    #define `$INSTANCE_NAME`_DEFAULT_SENSE_DUTY_SEL             (`$INSTANCE_NAME`_CSD_SENSE_DUTY_SENSE_POL_PHI_HIGH)

#elif(`$INSTANCE_NAME`_SENSING_LOW_EMI == `$INSTANCE_NAME`_CSD_SENSING_METHOD)

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN)
        /* Enable CSDCMP */
        #define `$INSTANCE_NAME`_CSD_CSDCMP_SCAN                (`$INSTANCE_NAME`_CSD_CSDCMP_CSDCMP_EN_MSK  |\
                                                                 `$INSTANCE_NAME`_CSD_CSDCMP_CMP_PHASE_PHI2 |\
                                                                 `$INSTANCE_NAME`_CSD_CSDCMP_AZ_EN_MSK)
    #else
        /* Enable CSDCMP */
        #define `$INSTANCE_NAME`_CSD_CSDCMP_SCAN                (`$INSTANCE_NAME`_CSD_CSDCMP_CSDCMP_EN_MSK |\
                                                                 `$INSTANCE_NAME`_CSD_CSDCMP_CMP_PHASE_PHI2)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN) */

    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_OPEN)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

    #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SCAN             (`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                     `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1CA_PHI2)
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SCAN            (0x00000000uL)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SCAN             (0x00000000uL)
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SCAN            (`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                     `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2CA_PHI2)
    #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */

    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if(`$INSTANCE_NAME`_IDAC_SINKING != `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN             (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP | `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1 | `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCAG_PHI1)
        #else
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN             (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1 | `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP | `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCAV_PHI1)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #else
        #if(`$INSTANCE_NAME`_IDAC_SINKING != `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN             (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCAG_PHI1)
        #else
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN             (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCAV_PHI1)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

    #define `$INSTANCE_NAME`_CSD_SW_RES_INIT                    ((`$INSTANCE_NAME`_CSD_F1PM_SWITCH_RES_LE_INIT << CSD_SW_RES_RES_F1PM_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_F2PT_SWITCH_RES_LE_INIT << CSD_SW_RES_RES_F2PT_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCAG_SWITCH_RES_LE_INIT << CSD_SW_RES_RES_HCAG_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCAV_SWITCH_RES_LE_INIT << CSD_SW_RES_RES_HCAV_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCBG_SWITCH_RES_LE_INIT << CSD_SW_RES_RES_HCBG_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCBV_SWITCH_RES_LE_INIT << CSD_SW_RES_RES_HCBV_Pos))

    #define `$INSTANCE_NAME`_CSD_SW_RES_SCAN                    ((`$INSTANCE_NAME`_CSD_F1PM_SWITCH_RES_LE_SCAN << CSD_SW_RES_RES_F1PM_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_F2PT_SWITCH_RES_LE_SCAN << CSD_SW_RES_RES_F2PT_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCAG_SWITCH_RES_LE_SCAN << CSD_SW_RES_RES_HCAG_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCAV_SWITCH_RES_LE_SCAN << CSD_SW_RES_RES_HCAV_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCBG_SWITCH_RES_LE_SCAN << CSD_SW_RES_RES_HCBG_Pos) |\
                                                                 (`$INSTANCE_NAME`_CSD_HCBV_SWITCH_RES_LE_SCAN << CSD_SW_RES_RES_HCBV_Pos))

    #define `$INSTANCE_NAME`_CSD_SHIELD_GPIO_DM                 (CY_GPIO_DM_ANALOG)
    #define `$INSTANCE_NAME`_CSD_SENSOR_HSIOM_SEL               (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA)
    #define `$INSTANCE_NAME`_CSD_SHIELD_HSIOM_SEL               (`$INSTANCE_NAME`_HSIOM_SEL_AMUXB)
    #define `$INSTANCE_NAME`_CSD_CMOD_HSIOM_SEL                 (`$INSTANCE_NAME`_HSIOM_SEL_GPIO)

    #define `$INSTANCE_NAME`_DEFAULT_IDACA_BALL_MODE            (`$INSTANCE_NAME`_CSD_IDACA_BALL_MODE_PHI2 <<\
                                                                 `$INSTANCE_NAME`_CSD_IDACA_BALL_MODE_POS)
    #define `$INSTANCE_NAME`_DEFAULT_IDACB_BALL_MODE            (`$INSTANCE_NAME`_CSD_IDACB_BALL_MODE_FULL <<\
                                                                 `$INSTANCE_NAME`_CSD_IDACB_BALL_MODE_POS)

    #if(`$INSTANCE_NAME`_IDAC_SINKING != `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
        #define `$INSTANCE_NAME`_DEFAULT_SENSE_DUTY_SEL             (0x00000000uL)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_SENSE_DUTY_SEL             (`$INSTANCE_NAME`_CSD_SENSE_DUTY_SENSE_POL_MSK)
    #endif /* (`$INSTANCE_NAME`_IDAC_SINKING != `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

#elif(`$INSTANCE_NAME`_SENSING_FULL_WAVE == `$INSTANCE_NAME`_CSD_SENSING_METHOD)
#else
    #error "Not supported sensing method."
#endif /* (`$INSTANCE_NAME`_SENSING_LEGACY == `$INSTANCE_NAME`_CSD_SENSING_METHOD) */


/***************************************
* API Constants
***************************************/
/* Definition of time interval that is enough for charging 100nF capacitor */
#define `$INSTANCE_NAME`_CSD_AVG_CYCLES_PER_LOOP                    (5u)
#define `$INSTANCE_NAME`_CSD_MAX_CHARGE_TIME_US                     (100u)
#define `$INSTANCE_NAME`_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM          (((`$INSTANCE_NAME`_CPU_CLOCK_FREQ_MHZ) * (`$INSTANCE_NAME`_CSD_MAX_CHARGE_TIME_US)) /\
                                                                        (`$INSTANCE_NAME`_CSD_AVG_CYCLES_PER_LOOP))

#define `$INSTANCE_NAME`_CSD_IDAC_MOD_BITS_USED                     (7u)
#define `$INSTANCE_NAME`_CAL_MIDDLE_BIT                             (1uL << (`$INSTANCE_NAME`_CSD_IDAC_MOD_BITS_USED - 1u))
/* Increased scan time duration to cover coarse and fine init cycles */
#define `$INSTANCE_NAME`_MAX_17_BITS_VALUE                          (0x0001FFFFLu)
#define `$INSTANCE_NAME`_MAX_SCAN_TIME                              ((`$INSTANCE_NAME`_MAX_17_BITS_VALUE * `$INSTANCE_NAME`_CSD_SCANSPEED_DIVIDER) /\
                                                                        (CYDEV_CLK_PERICLK__MHZ))
#define `$INSTANCE_NAME`_CALIBR_WATCHDOG_CYCLES_NUM                 (((`$INSTANCE_NAME`_CPU_CLOCK_FREQ_MHZ) * (`$INSTANCE_NAME`_MAX_SCAN_TIME)) /\
                                                                        (`$INSTANCE_NAME`_CSD_AVG_CYCLES_PER_LOOP))

#define `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM                      (9u)

/* Calibration constants */
#define `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR                   (10u)

#if (`$INSTANCE_NAME`_IDAC_GAIN_HIGH == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
    #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA                 (2400u)
#elif (`$INSTANCE_NAME`_IDAC_GAIN_MEDIUM == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
    #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA                 (300u)
#else
    #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA                 (37u)
#endif /* (`$INSTANCE_NAME`_IDAC_GAIN_HIGH == `$INSTANCE_NAME`_CSD_IDAC_GAIN) */

/* Defining the drive mode of pins depending on the Inactive sensor connection setting in the Component customizer. */
#if(`$INSTANCE_NAME`_SNS_CONNECTION_GROUND == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
    #define `$INSTANCE_NAME`_CSD_INACTIVE_SNS_GPIO_DM               (CY_GPIO_DM_STRONG)
#elif(`$INSTANCE_NAME`_SNS_CONNECTION_HIGHZ == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
    #define `$INSTANCE_NAME`_CSD_INACTIVE_SNS_GPIO_DM               (CY_GPIO_DM_ANALOG)
#elif(`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
    #define `$INSTANCE_NAME`_CSD_INACTIVE_SNS_GPIO_DM               (CY_GPIO_DM_STRONG_IN_OFF)
#else
    #error "Unsupported inactive connection for the inactive sensors."
#endif /* (`$INSTANCE_NAME`_SNS_CONNECTION_GROUND == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION) */


/* Clock Source Mode */
#if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE                (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT)
#elif (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE                (`$INSTANCE_NAME`_CLK_SOURCE_SSC2)
#elif ((`$INSTANCE_NAME`_CLK_SOURCE_PRS8) == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE                (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
#elif ((`$INSTANCE_NAME`_CLK_SOURCE_PRS12) == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE                (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
#else
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE                (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
#endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

/* IDACs Ranges */
#if (`$INSTANCE_NAME`_IDAC_GAIN_LOW == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
    #define `$INSTANCE_NAME`_DEFAULT_IDACA_RANGE                    (`$INSTANCE_NAME`_CSD_IDACA_RANGE_IDAC_LO << `$INSTANCE_NAME`_CSD_IDACA_RANGE_POS)
    #define `$INSTANCE_NAME`_DEFAULT_IDACB_RANGE                    (`$INSTANCE_NAME`_CSD_IDACB_RANGE_IDAC_LO << `$INSTANCE_NAME`_CSD_IDACB_RANGE_POS)
#elif (`$INSTANCE_NAME`_IDAC_GAIN_MEDIUM == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
    #define `$INSTANCE_NAME`_DEFAULT_IDACA_RANGE                    (`$INSTANCE_NAME`_CSD_IDACA_RANGE_IDAC_MED << `$INSTANCE_NAME`_CSD_IDACA_RANGE_POS)
    #define `$INSTANCE_NAME`_DEFAULT_IDACB_RANGE                    (`$INSTANCE_NAME`_CSD_IDACB_RANGE_IDAC_MED << `$INSTANCE_NAME`_CSD_IDACB_RANGE_POS)
#else
    #define `$INSTANCE_NAME`_DEFAULT_IDACA_RANGE                    (`$INSTANCE_NAME`_CSD_IDACA_RANGE_IDAC_HI << `$INSTANCE_NAME`_CSD_IDACA_RANGE_POS)
    #define `$INSTANCE_NAME`_DEFAULT_IDACB_RANGE                    (`$INSTANCE_NAME`_CSD_IDACB_RANGE_IDAC_HI << `$INSTANCE_NAME`_CSD_IDACB_RANGE_POS)
#endif

/* IDACs Polarities */
#if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
    #define `$INSTANCE_NAME`_DEFAULT_IDACA_POLARITY                 (`$INSTANCE_NAME`_CSD_IDACA_POLARITY_VDDA_SNK << `$INSTANCE_NAME`_CSD_IDACA_POLARITY_POS)
    #define `$INSTANCE_NAME`_DEFAULT_IDACB_POLARITY                 (`$INSTANCE_NAME`_CSD_IDACB_POLARITY_VDDA_SNK << `$INSTANCE_NAME`_CSD_IDACB_POLARITY_POS)
#else
    #define `$INSTANCE_NAME`_DEFAULT_IDACA_POLARITY                 (`$INSTANCE_NAME`_CSD_IDACA_POLARITY_VSSA_SRC << `$INSTANCE_NAME`_CSD_IDACA_POLARITY_POS)
    #define `$INSTANCE_NAME`_DEFAULT_IDACB_POLARITY                 (`$INSTANCE_NAME`_CSD_IDACB_POLARITY_VSSA_SRC << `$INSTANCE_NAME`_CSD_IDACB_POLARITY_POS)
#endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */


#if(`$INSTANCE_NAME`_VREF_SRSS != `$INSTANCE_NAME`_CSD_VREF_SOURCE)
    #define `$INSTANCE_NAME`_CSD_SW_REFGEN_VREF_SRC                 (`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_SW_SGRP_MSK)
#else
    #define `$INSTANCE_NAME`_CSD_SW_REFGEN_VREF_SRC                 (`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_SW_SGR_MSK)
#endif /* (`$INSTANCE_NAME`_VREF_SRSS != `$INSTANCE_NAME`_CSD_VREF_SOURCE) */


/* IDAC legs configuration */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))
        #define `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL              (`$INSTANCE_NAME`_CSD_SW_REFGEN_VREF_SRC | `$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_SW_IAIB_MSK)
        #define `$INSTANCE_NAME`_DEFAULT_IDACB_LEG1_MODE            (`$INSTANCE_NAME`_CSD_IDACB_LEG1_EN_MSK |\
                                                                    (`$INSTANCE_NAME`_CSD_IDACB_LEG1_MODE_CSD_STATIC << `$INSTANCE_NAME`_CSD_IDACB_LEG1_MODE_POS))
#else
        #define `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL              (`$INSTANCE_NAME`_CSD_SW_REFGEN_VREF_SRC)
        #define `$INSTANCE_NAME`_DEFAULT_IDACB_LEG1_MODE            (`$INSTANCE_NAME`_CSD_IDACB_LEG1_MODE_GP_STATIC << `$INSTANCE_NAME`_CSD_IDACB_LEG1_MODE_POS)
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
     (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))
        #define `$INSTANCE_NAME`_DEFAULT_IDACB_LEG2_MODE            (`$INSTANCE_NAME`_CSD_IDACA_LEG2_EN_MSK |\
                                                                    (`$INSTANCE_NAME`_CSD_IDACA_LEG2_MODE_CSD_STATIC << `$INSTANCE_NAME`_CSD_IDACA_LEG2_MODE_POS))
#else
        #define `$INSTANCE_NAME`_DEFAULT_IDACB_LEG2_MODE            (`$INSTANCE_NAME`_CSD_IDACA_LEG2_MODE_GP_STATIC << `$INSTANCE_NAME`_CSD_IDACA_LEG2_MODE_POS)
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
        (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */

/* IDACs register configuration is based on the Component configuration */
#define `$INSTANCE_NAME`_IDAC_MOD_DEFAULT_CFG                       (`$INSTANCE_NAME`_DEFAULT_IDACA_RANGE | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACA_POLARITY | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACA_BALL_MODE | \
                                                                    (`$INSTANCE_NAME`_CSD_IDACA_LEG1_MODE_CSD << `$INSTANCE_NAME`_CSD_IDACA_LEG1_MODE_POS) | \
                                                                     `$INSTANCE_NAME`_CSD_IDACA_LEG1_EN_MSK | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACB_LEG2_MODE)

#define `$INSTANCE_NAME`_IDAC_COMP_DEFAULT_CFG                      (`$INSTANCE_NAME`_DEFAULT_IDACB_RANGE | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACB_POLARITY | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACB_BALL_MODE | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACB_LEG1_MODE | \
                                                                    (`$INSTANCE_NAME`_CSD_IDACB_LEG2_MODE_GP_STATIC << `$INSTANCE_NAME`_CSD_IDACB_LEG2_MODE_POS))

#define `$INSTANCE_NAME`_IDAC_MOD_CALIBRATION_CFG                   (`$INSTANCE_NAME`_DEFAULT_IDACA_RANGE | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACA_POLARITY | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACA_BALL_MODE | \
                                                                    (`$INSTANCE_NAME`_CSD_IDACA_LEG1_MODE_CSD << `$INSTANCE_NAME`_CSD_IDACA_LEG1_MODE_POS) | \
                                                                     `$INSTANCE_NAME`_CSD_IDACA_LEG1_EN_MSK | \
                                                                    (`$INSTANCE_NAME`_CSD_IDACA_LEG2_MODE_GP_STATIC << `$INSTANCE_NAME`_CSD_IDACA_LEG2_MODE_POS))

#define `$INSTANCE_NAME`_IDAC_COMP_CALIBRATION_CFG                  (`$INSTANCE_NAME`_DEFAULT_IDACB_RANGE | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACB_POLARITY | \
                                                                     `$INSTANCE_NAME`_DEFAULT_IDACB_BALL_MODE | \
                                                                    (`$INSTANCE_NAME`_CSD_IDACB_LEG1_MODE_GP_STATIC << `$INSTANCE_NAME`_CSD_IDACB_LEG1_MODE_POS) | \
                                                                    (`$INSTANCE_NAME`_CSD_IDACB_LEG2_MODE_GP_STATIC << `$INSTANCE_NAME`_CSD_IDACB_LEG2_MODE_POS))

/***************************************
* Global software variables
***************************************/

extern uint32 `$INSTANCE_NAME`_configCsd;

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
    extern uint8 `$INSTANCE_NAME`_badConversionsNum;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    /* Stores IDAC and raw count that corresponds to a sensor with maximum Cp within a widget */
    extern uint8 `$INSTANCE_NAME`_calibratedIdac;
    extern uint16 `$INSTANCE_NAME`_calibratedRawcount;
    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        extern uint8 `$INSTANCE_NAME`_calibratedIdacRow;
        extern uint16 `$INSTANCE_NAME`_calibratedRawcountRow;
    #endif /*(`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */

/***************************************
* Function Prototypes
**************************************/

/* Interrupt handler */
extern void `$INSTANCE_NAME`_CSDPostSingleScan(void);
extern void `$INSTANCE_NAME`_CSDPostMultiScan(void);

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
    extern void `$INSTANCE_NAME`_CSDPostMultiScanGanged(void);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */


/**
* \cond SECTION_CYSENSE_LOW_LEVEL
* \addtogroup group_cysense_low_level
* \{
*/

void `$INSTANCE_NAME`_CSDSetupWidget(uint32 widgetId);
void `$INSTANCE_NAME`_CSDSetupWidgetExt(uint32 widgetId, uint32 sensorId);
void `$INSTANCE_NAME`_CSDScan(void);
void `$INSTANCE_NAME`_CSDScanExt(void);
#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
    cy_status `$INSTANCE_NAME`_CSDCalibrateWidget(uint32 widgetId, uint32 target);
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN)) */
void `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr);
void `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr);

/** \}
* \endcond */

/*****************************************************
* Function Prototypes - internal Low Level functions
*****************************************************/
/**
* \cond SECTION_CYSENSE_INTERNAL
* \addtogroup group_cysense_internal
* \{
*/

void `$INSTANCE_NAME`_SsCSDInitialize(void);
void `$INSTANCE_NAME`_SsCSDStartSample(void);
void `$INSTANCE_NAME`_SsCSDSetUpIdacs(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt);
void `$INSTANCE_NAME`_SsCSDConfigClock(void);
void `$INSTANCE_NAME`_SsCSDElectrodeCheck(void);
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
    void `$INSTANCE_NAME`_SsCSDDisableShieldElectrodes(void);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */
uint32 `$INSTANCE_NAME`_SsCSDGetNumberOfConversions(uint32 snsClkDivider, uint32 resolution, uint32 snsClkSrc);
void `$INSTANCE_NAME`_SsCSDCalculateScanDuration(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt);
void `$INSTANCE_NAME`_SsCSDConnectSensorExt(uint32 widgetId, uint32 sensorId);
void `$INSTANCE_NAME`_SsCSDDisconnectSnsExt(uint32 widgetId, uint32 sensorId);

#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN)) */

/** \}
* \endcond */

/***************************************
* Global software variables
***************************************/
extern uint32 `$INSTANCE_NAME`_configCsd;
/* Interrupt handler */
extern void `$INSTANCE_NAME`_CSDPostSingleScan(void);
extern void `$INSTANCE_NAME`_CSDPostMultiScan(void);
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
extern void `$INSTANCE_NAME`_CSDPostMultiScanGanged(void);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
    extern uint8 `$INSTANCE_NAME`_badConversionsNum;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_SENSINGCSD_LL_H */


/* [] END OF FILE */
