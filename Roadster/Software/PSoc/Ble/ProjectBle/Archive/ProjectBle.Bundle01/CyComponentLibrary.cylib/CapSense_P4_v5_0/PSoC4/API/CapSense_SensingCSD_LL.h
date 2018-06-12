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

#include <CyLib.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <cypins.h>
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Sensing.h"

/****************************************************************************
* Register and mode mask definition
****************************************************************************/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    #define `$INSTANCE_NAME`_CSD_CSDCMP_INIT                                (`$INSTANCE_NAME`_CSDCMP_CSDCMP_DISABLED)

    /* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */
    #else
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_CMOD                   (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */
    #else
        #define `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK                   (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_COARSE                         (`$INSTANCE_NAME`_HS_P_SEL_COARSE_CMOD | `$INSTANCE_NAME`_CSD_HS_P_SEL_COARSE_TANK)

    /* C_mod config */
    #if ((`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) || (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_INIT             (`$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                     `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                     `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)
        #define `$INSTANCE_NAME`_SW_DSI_SEL_CMODPAD                 (`$INSTANCE_NAME`_SW_DSI_CMOD)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_INIT             (0x00000000uL)
        #define `$INSTANCE_NAME`_SW_DSI_SEL_CMODPAD                 (0x00000000uL)
    #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */

    /* C_tank config */
    #if ((`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) || (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_INIT            (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                     `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                     `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
        #define `$INSTANCE_NAME`_SW_DSI_SEL_TANKPAD                 (`$INSTANCE_NAME`_SW_DSI_CTANK)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_INIT            (0x00000000uL)
        #define `$INSTANCE_NAME`_SW_DSI_SEL_TANKPAD                 (0x00000000uL)
    #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */

    #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_INIT                 (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCAV_HSCMP)

    /* Defining default HW configuration according to settings in customizer. */
    #define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG                 (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ |\
                                                                 `$INSTANCE_NAME`_CONFIG_SAMPLE_SYNC_MASK)
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN)
        /* Enable CSDCMP */
        #define `$INSTANCE_NAME`_CSD_CSDCMP_SCAN                (`$INSTANCE_NAME`_CSDCMP_CSDCMP_EN_MASK |\
                                                                 `$INSTANCE_NAME`_CSDCMP_AZ_EN_MASK)
    #else
        /* Enable CSDCMP */
        #define `$INSTANCE_NAME`_CSD_CSDCMP_SCAN                (`$INSTANCE_NAME`_CSDCMP_CSDCMP_EN_MASK)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_CSD_HS_P_SEL_SCAN_TANK                 (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_HS_P_SEL_SCAN_TANK)
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_STATIC_OPEN)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    /* SW_FW_MOD_SEL switches state for Coarse initialization of CMOD (sense path) */
    #define `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SCAN                 (0x00000000uL)

    #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SCAN            (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE | \
                                                                 `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CB_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SCAN            (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)) */

    /* Shield switch default config */
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_HSCMP)
        #else
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI1 | \
                                                                     `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP)
        #else
            #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                     `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #else
        #define `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN              (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

    #define `$INSTANCE_NAME`_CSD_SW_RES_INIT                        (`$INSTANCE_NAME`_CSD_INIT_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET)
    #define `$INSTANCE_NAME`_CSD_SW_RES_SCAN                        ((`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET) |\
                                                                     (`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBG__OFFSET))

    #define `$INSTANCE_NAME`_CSD_SHIELD_GPIO_DM                 (`$INSTANCE_NAME`_GPIO_STRGDRV)
    #define `$INSTANCE_NAME`_CSD_SENSOR_HSIOM_SEL               (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE)
    #define `$INSTANCE_NAME`_CSD_SHIELD_HSIOM_SEL               (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD)
    #define `$INSTANCE_NAME`_CSD_CMOD_HSIOM_SEL                 (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA)

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_BALL_MODE         ((uint32)`$INSTANCE_NAME`_IDAC_MOD_BALL_MODE_FULL <<\
                                                                 CYFLD_CSD_BAL_MODE__OFFSET)
    #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_BALL_MODE        ((uint32)`$INSTANCE_NAME`_IDAC_COMP_BALL_MODE_FULL <<\
                                                                 CYFLD_CSD_BAL_MODE__OFFSET)

    #define `$INSTANCE_NAME`_DEFAULT_SENSE_DUTY_SEL             (`$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI1_MASK |\
                                                                 `$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI2_MASK)

    #define `$INSTANCE_NAME`_CSD_IDAC_MOD_BITS_USED                     (7u)
    #define `$INSTANCE_NAME`_CAL_MIDDLE_BIT                             (1uL << (`$INSTANCE_NAME`_CSD_IDAC_MOD_BITS_USED - 1u))

    #define `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM                      (9u)

    #if (`$INSTANCE_NAME`_IDAC_GAIN_HIGH == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA                 (2400u)
    #elif (`$INSTANCE_NAME`_IDAC_GAIN_MEDIUM == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA                 (300u)
    #else
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA                 (37u)
    #endif /* (`$INSTANCE_NAME`_IDAC_GAIN_HIGH == `$INSTANCE_NAME`_CSD_IDAC_GAIN) */

    /* Defining the drive mode of pins depending on the Inactive sensor connection setting in the Component customizer. */
    #if(`$INSTANCE_NAME`_SNS_CONNECTION_GROUND == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_INACTIVE_SNS_GPIO_DM               (CY_SYS_PINS_DM_STRONG)
    #elif(`$INSTANCE_NAME`_SNS_CONNECTION_HIGHZ == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_INACTIVE_SNS_GPIO_DM               (CY_SYS_PINS_DM_ALG_HIZ)
    #elif(`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
        #define `$INSTANCE_NAME`_CSD_INACTIVE_SNS_GPIO_DM               (CY_SYS_PINS_DM_ALG_HIZ)
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
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE                 ((uint32)`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_LO << CYFLD_CSD_RANGE__OFFSET)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE                ((uint32)`$INSTANCE_NAME`_IDAC_COMP_RANGE_IDAC_LO << CYFLD_CSD_RANGE__OFFSET)
    #elif (`$INSTANCE_NAME`_IDAC_GAIN_MEDIUM == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE                 ((uint32)`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_MED << CYFLD_CSD_RANGE__OFFSET)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE                ((uint32)`$INSTANCE_NAME`_IDAC_COMP_RANGE_IDAC_MED << CYFLD_CSD_RANGE__OFFSET)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE                 ((uint32)`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_HI << CYFLD_CSD_RANGE__OFFSET)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE                ((uint32)`$INSTANCE_NAME`_IDAC_COMP_RANGE_IDAC_HI << CYFLD_CSD_RANGE__OFFSET)
    #endif

    /* IDACs Polarities */
    #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY              ((uint32)`$INSTANCE_NAME`_IDAC_MOD_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY             ((uint32)`$INSTANCE_NAME`_IDAC_COMP_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY              ((uint32)`$INSTANCE_NAME`_IDAC_MOD_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY             ((uint32)`$INSTANCE_NAME`_IDAC_COMP_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
    #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

    #define `$INSTANCE_NAME`_SW_REFGEN_VREF_SRC                         (`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK)

    /* IDAC legs configuration */
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))
            #define `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL              (`$INSTANCE_NAME`_SW_REFGEN_VREF_SRC | `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_IAIB_MASK)
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG1_MODE        (`$INSTANCE_NAME`_IDAC_COMP_LEG1_EN_MASK |\
                                                                        ((uint32)`$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET))
    #else
            #define `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL              (`$INSTANCE_NAME`_SW_REFGEN_VREF_SRC)
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG1_MODE        ((uint32)`$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */


    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
         (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG2_MODE        (`$INSTANCE_NAME`_IDAC_COMP_LEG2_EN_MASK |\
                                                                        ((uint32)`$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_CSD_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))
    #else
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG2_MODE        ((uint32)`$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
            (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */

    /* IDACs register configuration is based on the Component configuration */
    #define `$INSTANCE_NAME`_IDAC_MOD_DEFAULT_CFG                       (`$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_BALL_MODE | \
                                                                        ((uint32)(`$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_CSD << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                         `$INSTANCE_NAME`_IDAC_MOD_LEG1_EN_MASK | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG2_MODE)

    #define `$INSTANCE_NAME`_IDAC_COMP_DEFAULT_CFG                      (`$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_BALL_MODE | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG1_MODE | \
                                                                        ((uint32)(`$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET)))

    #define `$INSTANCE_NAME`_IDAC_MOD_CALIBRATION_CFG                   ((uint32)(`$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_BALL_MODE | \
                                                                        ((uint32)(`$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_CSD << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                         `$INSTANCE_NAME`_IDAC_MOD_LEG1_EN_MASK | \
                                                                        ((uint32)((uint32)`$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))))

    #define `$INSTANCE_NAME`_IDAC_COMP_CALIBRATION_CFG                  ((uint32)(`$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY | \
                                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_BALL_MODE | \
                                                                        ((uint32)((uint32)`$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_GP_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                        ((uint32)((uint32)`$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))))
#else
    #define `$INSTANCE_NAME`_CSD_IDAC_MOD_BITS_USED                     (8u)

    #define `$INSTANCE_NAME`_IDAC_MOD_CFG_MASK                  (`$INSTANCE_NAME`_IDAC_POLARITY1_MIR_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_MOD_MODE_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_MOD_MASK)

    #define `$INSTANCE_NAME`_IDAC_COMP_CFG_MASK                 (`$INSTANCE_NAME`_IDAC_POLARITY2_MIR_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_COMP_RANGE_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_COMP_MODE_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_COMP_MASK)

        #define `$INSTANCE_NAME`_PRS_8_CONFIG                       `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK
    #define `$INSTANCE_NAME`_PRS_12_CONFIG                      (`$INSTANCE_NAME`_CONFIG_PRS_12_8_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK)

    /* Third-generation HW block Initial PRS mode */
    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRS8 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE        `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK

    #elif (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE        (`$INSTANCE_NAME`_CONFIG_PRS_12_8_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE        (0u)
    #endif /* (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE == `$INSTANCE_NAME`_PRS_8BITS) */

    /* Third-generation HW block Set IDAC polarity */
    #if (`$INSTANCE_NAME`_CSD_IDAC_CONFIG == `$INSTANCE_NAME`_IDAC_SINKING)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY          `$INSTANCE_NAME`_CONFIG_POLARITY_MASK
        #define `$INSTANCE_NAME`_CSH_DR_CONFIG                  `$INSTANCE_NAME`_CTANK_DR_VDDIO
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY          (0u)
        #define `$INSTANCE_NAME`_CSH_DR_CONFIG                  `$INSTANCE_NAME`_CTANK_DR_VSSIO
    #endif /* (`$INSTANCE_NAME`_CSD_IDAC_CONFIG == `$INSTANCE_NAME`_IDAC_SINKING) */

    /* Defining default CSD configuration according to settings in customizer. */
    #define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG                 (`$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_MASK |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY |\
                                                                `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_DRV_MASK)

    #define `$INSTANCE_NAME`_CSD_ENABLE_MASK                    (`$INSTANCE_NAME`_CONFIG_ENABLE_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK)

    /* Third-generation HW block Defining mask intended for clearing bits related to pre-charging options. */
    #define `$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK              (`$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK  |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK)

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG              (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN       (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                `$INSTANCE_NAME`_CSD_ENABLE_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)


    /* Third-generation HW block Ctank pre-charge mode configuration */
    #if(`$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC == `$INSTANCE_NAME`_CSH_PRECHARGE_VREF)
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            #define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG    (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK)
        #else
            #define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG    (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK)
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
    #else
        #define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG        (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)
    #endif /* (`$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC == `$INSTANCE_NAME`__CSH_PRECHARGE_IO_BUF) */

    #define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG_CSD_EN     (`$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_ENABLE_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK)

#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

/* Calibration constants */
#define `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR                       (10u)
#define `$INSTANCE_NAME`_CAL_MIDDLE_BIT                                 (1uL << (`$INSTANCE_NAME`_CSD_IDAC_MOD_BITS_USED - 1u))

#define `$INSTANCE_NAME`_CSD_AVG_CYCLES_PER_LOOP                   (5u)
#define `$INSTANCE_NAME`_CSD_MEASURE_MAX_TIME_US                   (6000u)
#define `$INSTANCE_NAME`_CSD_PRECHARGE_MAX_TIME_US                 (250u)

#define `$INSTANCE_NAME`_CSD_CALIBR_WATCHDOG_CYCLES_NUM            (((CYDEV_BCLK__SYSCLK__MHZ) * (`$INSTANCE_NAME`_CSD_MEASURE_MAX_TIME_US)) /\
                                                                    (`$INSTANCE_NAME`_CSD_AVG_CYCLES_PER_LOOP))
#define `$INSTANCE_NAME`_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM         (((CYDEV_BCLK__SYSCLK__MHZ) * (`$INSTANCE_NAME`_CSD_MEASURE_MAX_TIME_US)) /\
                                                                    (`$INSTANCE_NAME`_CSD_AVG_CYCLES_PER_LOOP))

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

/**
* \cond SECTION_C_LOW_LEVEL
* \addtogroup group_c_low_level
* \{
*/

void `$INSTANCE_NAME`_CSDSetupWidget(uint32 widgetId);
void `$INSTANCE_NAME`_CSDSetupWidgetExt(uint32 widgetId, uint32 sensorId);
void `$INSTANCE_NAME`_CSDScan(void);
void `$INSTANCE_NAME`_CSDScanExt(void);
#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
    cystatus `$INSTANCE_NAME`_CSDCalibrateWidget(uint32 widgetId, uint32 target);
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))  */
void `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr);
void `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr);

/** \}
* \endcond */

/*****************************************************
* Function Prototypes - internal Low Level functions
*****************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
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
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    uint32 `$INSTANCE_NAME`_SsCSDGetNumberOfConversions(uint32 snsClkDivider, uint32 resolution, uint32 snsClkSrc);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
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
extern CY_ISR_PROTO(`$INSTANCE_NAME`_CSDPostSingleScan);
extern CY_ISR_PROTO(`$INSTANCE_NAME`_CSDPostMultiScan);
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
extern CY_ISR_PROTO(`$INSTANCE_NAME`_CSDPostMultiScanGanged);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
    extern uint8 `$INSTANCE_NAME`_badConversionsNum;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_SENSINGCSD_LL_H */


/* [] END OF FILE */
