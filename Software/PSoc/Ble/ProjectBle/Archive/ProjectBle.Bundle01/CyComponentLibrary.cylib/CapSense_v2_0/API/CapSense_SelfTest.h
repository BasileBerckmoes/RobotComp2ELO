/***************************************************************************//**
* \file `$INSTANCE_NAME`_SelfTest.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the function prototypes for the Built-In Self-Test
*   library.
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

#if !defined(CY_SENSE_`$INSTANCE_NAME`_SELFTEST_H)
#define CY_SENSE_`$INSTANCE_NAME`_SELFTEST_H

#include "syslib/cy_syslib.h"
#include "gpio/cy_gpio.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#include "`$INSTANCE_NAME`_Configuration.h"

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)

/*******************************************************************************
* Function Prototypes - High-level API
*******************************************************************************/
/**
* \cond SECTION_CYSENSE_HIGH_LEVEL
* \addtogroup group_cysense_high_level
* \{
*/

uint32 `$INSTANCE_NAME`_RunSelfTest(uint32 testEnMask);

/** \}
* \endcond */

/*******************************************************************************
* Function Prototypes - Low-level API
*******************************************************************************/
/**
* \cond SECTION_CYSENSE_LOW_LEVEL
* \addtogroup group_cysense_low_level
* \{
*/

/* CRC test group */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
    uint32 `$INSTANCE_NAME`_CheckGlobalCRC(void);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
    uint32 `$INSTANCE_NAME`_CheckWidgetCRC(uint32 widgetId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */

/* Baseline test group */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
    uint32 `$INSTANCE_NAME`_CheckBaselineDuplication(uint32 widgetId, uint32 sensorId);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN)
    uint32 `$INSTANCE_NAME`_CheckBaselineRawcountRange(uint32 widgetId, uint32 sensorId,
                                    `$INSTANCE_NAME`_BSLN_RAW_RANGE_STRUCT *ranges);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN) */

/* Short test group */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)
    uint32 `$INSTANCE_NAME`_CheckSensorShort(uint32 widgetId, uint32 sensorId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
    uint32 `$INSTANCE_NAME`_CheckSns2SnsShort(uint32 widgetId, uint32 sensorId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN) */

/* Capacitance measurement test group */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
    uint32 `$INSTANCE_NAME`_GetSensorCapacitance(uint32 widgetId, uint32 sensorId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)
        uint32 `$INSTANCE_NAME`_GetShieldCapacitance(void);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`__TST_SH_CAP_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)
    uint32 `$INSTANCE_NAME`_GetExtCapCapacitance(uint32 extCapId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN) */

/* Vdda measurement */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN)
    uint16 `$INSTANCE_NAME`_GetVdda(void);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN) */

/** \}
* \endcond */

/*******************************************************************************
* Function Prototypes - Internal Functions
*******************************************************************************/
/**
* \cond SECTION_CYSENSE_INTERNAL
* \addtogroup group_cysense_internal
* \{
*/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
    void `$INSTANCE_NAME`_DsUpdateGlobalCrc(void);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
    void `$INSTANCE_NAME`_DsUpdateWidgetCrc(uint32 widgetId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
    void `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(uint32 widgetId, uint32 sensorId);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

void `$INSTANCE_NAME`_BistInitialize(void);
void `$INSTANCE_NAME`_BistDisableMode(void);

/** \}
* \endcond */

/***********************************************************************************************************************
* Local definition
***********************************************************************************************************************/
/* Defines the mask for baseline data processing failure */
#define `$INSTANCE_NAME`_PROCESS_BASELINE_FAILED                        (0x00000001uL << 31u)

/* Defines constants for Self-Test library */
#define `$INSTANCE_NAME`_TST_LSBYTE                                     (0x000000FFuL)
#define `$INSTANCE_NAME`_TST_FAILED                                     (0x0000FFFFuL)
#define `$INSTANCE_NAME`_TST_BAD_PARAM                                  (0x00000001uL << 30u)
#define `$INSTANCE_NAME`_TST_NOT_EXECUTED                               (0x00000001uL << 31u)

#if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_TST_SNS_CAP_EN || \
                                 `$INSTANCE_NAME`_TST_SH_CAP_EN  || \
                                 `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN))

    /* Defines external capacitor ID */
    #define `$INSTANCE_NAME`_TST_CMOD_MAP                               (0u)
    #define `$INSTANCE_NAME`_TST_CSH_MAP                                (1u)
    #define `$INSTANCE_NAME`_TST_CINTA_MAP                              (2u)
    #define `$INSTANCE_NAME`_TST_CINTB_MAP                              (3u)

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #define `$INSTANCE_NAME`_CSD_CTANK_HSIOM_SEL                    (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA)
    #endif  /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

    #define `$INSTANCE_NAME`_08_BIT_SHIFT                               (8uL)

    #define `$INSTANCE_NAME`_BIST_SNS_CAP_MAX_CP                        ((0x00000001uL << 8uL) - 1uL)
    #define `$INSTANCE_NAME`_BIST_SH_CAP_MAX_CP                         ((0x00000001uL << 16uL) - 1uL)
    #define `$INSTANCE_NAME`_BIST_SNS_CAP_UNIT_SCALE                    (1000uL)
    #define `$INSTANCE_NAME`_BIST_10_BIT_MASK                           ((0x00000001uL << 10uL) - 1uL)
    #define `$INSTANCE_NAME`_BIST_CALIBRATION_TARGET                    ((`$INSTANCE_NAME`_BIST_10_BIT_MASK * \
                                                                          `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL) / \
                                                                          `$INSTANCE_NAME`_PERCENTAGE_100)

    #define `$INSTANCE_NAME`_BIST_AVG_CYCLES_PER_LOOP                   (5u)
    #define `$INSTANCE_NAME`_BIST_MAX_CHARGE_TIME_US                    (100u)
    /* Increased scan time duration to cover coarse and fine init cycles */
    #define `$INSTANCE_NAME`_BIST_MAX_17_BITS_VALUE                     (0x0001FFFFLu)
    #define `$INSTANCE_NAME`_BIST_MAX_SCAN_TIME                         ((`$INSTANCE_NAME`_BIST_MAX_17_BITS_VALUE * `$INSTANCE_NAME`_CSD_SCANSPEED_DIVIDER) /\
                                                                            (CYDEV_CLK_PERICLK__MHZ))
    #define `$INSTANCE_NAME`_BIST_CALIBR_WATCHDOG_CYCLES_NUM            (((`$INSTANCE_NAME`_CPU_CLOCK_FREQ_MHZ) * (`$INSTANCE_NAME`_BIST_MAX_SCAN_TIME)) /\
                                                                            (`$INSTANCE_NAME`_BIST_AVG_CYCLES_PER_LOOP))
    #define `$INSTANCE_NAME`_BIST_PRECHARGE_WATCHDOG_CYCLES_NUM          (((`$INSTANCE_NAME`_CPU_CLOCK_FREQ_MHZ) * (`$INSTANCE_NAME`_BIST_MAX_CHARGE_TIME_US)) /\
                                                                          (`$INSTANCE_NAME`_BIST_AVG_CYCLES_PER_LOOP))

    /* Min idac code at which we can guarantee 10% of raw count step per idac changing for one */
    #define `$INSTANCE_NAME`_BIST_MIN_IDAC_VALUE                        (12uL)
    #define `$INSTANCE_NAME`_BIST_MAX_MODCLK_DIVIDER                    (0x000000FFuL)
    #define `$INSTANCE_NAME`_BIST_CAL_MIDDLE_BIT                        (0x40u)

    #define `$INSTANCE_NAME`_TST_EXT_CAP_LOW_RANGE                      (5uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION                     (0x00000001uL << 10uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_DURATION                       (1uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ                     (4uL)
    #define `$INSTANCE_NAME`_SENSE_DUTY_TST_EXT_CAP_WIDTH               (10uL)
    #define `$INSTANCE_NAME`_SEQ_INIT_CNT_FINE_INIT_SKIP                (0x00000000uL)

    #define `$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION_75                  ((`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION >> 1uL) +\
                                                                         (`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION >> 2uL))
    #define `$INSTANCE_NAME`_TST_EXT_CAP_MLTPLR                         (2u)
    #define `$INSTANCE_NAME`_CSDCMP_TST_CAP_MEAS                        (0x00000201uL)

    /***********************************************************************************************************************
    * HW CSD Block Config
    ***********************************************************************************************************************/
    #define `$INSTANCE_NAME`_BIST_INTR_SET_CFG                          (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_CFG                    (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_CAP_SENSE_DUTY_SEL                    (0x00010000uL)
    #define `$INSTANCE_NAME`_BIST_AMBUF_PWR_MODE_OFF                    (`$INSTANCE_NAME`_CSD_AMBUF_PWR_MODE_OFF)
    #define `$INSTANCE_NAME`_BIST_AUTO_ZERO_TIME                        (`$INSTANCE_NAME`_CSD_AUTO_ZERO_TIME)

    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_BIST_DEFAULT_CSD_IO_SEL             (`$INSTANCE_NAME`_CSD_TX_N_OUT_EN_PHI1 | `$INSTANCE_NAME`_CSD_TX_N_AMUXA_EN_PHI2 |\
                                                                 `$INSTANCE_NAME`_CSD_TX_OUT_EN_PHI1_DELAY | `$INSTANCE_NAME`_CSD_TX_AMUXB_EN_PHI2_DELAY)
    #else
        #define `$INSTANCE_NAME`_BIST_DEFAULT_CSD_IO_SEL             (`$INSTANCE_NAME`_CSD_TX_N_OUT_EN_PHI1 | `$INSTANCE_NAME`_CSD_TX_N_AMUXA_EN_PHI2)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

    #define `$INSTANCE_NAME`_BIST_DEFAULT_CSD_SW_DSI_SEL                (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_ADC_CTL_CFG                           (0x00000000uL)

    /* Shield switch default config */
    #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_INIT                 (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCAV_HSCMP)
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_HSCMP)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1 | \
                                                                      `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                      `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #else
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG              (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

    /* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */
    #else
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD                   (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */
    #else
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK                   (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                    (`$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK)
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    #define `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_COARSE                    (`$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD | `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK)
    #define `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_CFG                       (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_SW_HS_N_SEL_CFG                       (0x00000000uL)

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN)
        #define `$INSTANCE_NAME`_BIST_AZ_ENABLE_CFG                  (`$INSTANCE_NAME`_CSD_HSCMP_AZ_EN_MSK)
    #else
        #define `$INSTANCE_NAME`_BIST_AZ_ENABLE_CFG                  (0uL)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN) */

    #define `$INSTANCE_NAME`_BIST_HSCMP_CFG                             (`$INSTANCE_NAME`_CSD_HSCMP_HSCMP_EN_MSK | `$INSTANCE_NAME`_BIST_AZ_ENABLE_CFG)
    #define `$INSTANCE_NAME`_BIST_CSDCMP_INIT                           (`$INSTANCE_NAME`_CSD_CSDCMP_CSDCMP_DISABLED)

    #define `$INSTANCE_NAME`_BIST_BLOCK_ON_DELAY                        (3uL * CYDEV_CLK_PERICLK__MHZ)
    #define `$INSTANCE_NAME`_BIST_HSCMP_ON_DELAY                        (1uL * CYDEV_CLK_PERICLK__MHZ)

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT    (`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT    (0x00000000uL)
        #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */

        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT   (`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT   (0x00000000uL)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */

    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT        (`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)

        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT       (`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT        (0x00000000uL)
        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT       (0x00000000uL)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */


    #define `$INSTANCE_NAME`_BIST_SW_RES_INIT                           (`$INSTANCE_NAME`_CSD_INIT_SWITCH_RES << CSD_SW_RES_RES_HCAV_Pos)
    #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_SCAN                    (0x00000000uL)
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
         (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_SCAN               (`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                         `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_F2CB_PHI2)
    #else
        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_SCAN               (0x00000000uL)
    #endif

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
         (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_HSCMP)
    #elif((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
          (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_HSCMP)
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                         `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
    #else
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (0x00000000uL)
    #endif
    #define `$INSTANCE_NAME`_BIST_SW_RES_SCAN                           ((`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CSD_SW_RES_RES_HCBV_Pos) |\
                                                                         (`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CSD_SW_RES_RES_HCBG_Pos))
    #define `$INSTANCE_NAME`_BIST_HSCMP_SCAN_MASK                       (`$INSTANCE_NAME`_CSD_HSCMP_HSCMP_EN_MSK)
    #define `$INSTANCE_NAME`_BIST_IDACB_CFG                             (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_IDACA_CFG                             (0x01830000uL)

    /* IDAC Gain in nA */
    #define `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN                      (2400uL)

    #if ((CYDEV_CLK_PERICLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ)
        #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_12MHZ)
    #elif ((CYDEV_CLK_PERICLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ)
        #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_24MHZ)
    #else
        /* ((CYDEV_CLK_PERICLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_48MHZ) */
        #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_48MHZ)
    #endif

    #if(`$INSTANCE_NAME`_VREF_SRSS != `$INSTANCE_NAME`_CSD_VREF_SOURCE)
        #define `$INSTANCE_NAME`_BIST_SW_REFGEN_SEL_CFG                 (`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_SW_SGRP_MSK)
    #else
        #define `$INSTANCE_NAME`_BIST_SW_REFGEN_SEL_CFG                 (`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_SW_SGR_MSK)
    #endif /* (`$INSTANCE_NAME`_VREF_SRSS != `$INSTANCE_NAME`_CSD_VREF_SOURCE) */

    #define `$INSTANCE_NAME`_BIST_CSD_CONFIG                            (`$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_2_CYCLES | \
                                                                         `$INSTANCE_NAME`_IREF_SRC_CFG |\
                                                                         `$INSTANCE_NAME`_PWR_MODE_CFG)

#endif /* (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_TST_SNS_CAP_EN || \
                                       `$INSTANCE_NAME`_TST_SH_CAP_EN  || \
                                       `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)) */

#define `$INSTANCE_NAME`_TST_MEASMODE_VREF                              (0x1uL << CSD_ADC_CTL_ADC_MODE_Pos)
#define `$INSTANCE_NAME`_TST_MEASMODE_VREFBY2                           (0x2uL << CSD_ADC_CTL_ADC_MODE_Pos)
#define `$INSTANCE_NAME`_TST_MEASMODE_VIN                               (0x3uL << CSD_ADC_CTL_ADC_MODE_Pos)

/* Clock defines */
#define `$INSTANCE_NAME`_TST_VDDA_MODCLK_DIV_DEFAULT                    (`$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER)
#define `$INSTANCE_NAME`_TST_VDDA_SENSE_DIV_DEFAULT                     (0x4uL)
#define `$INSTANCE_NAME`_TST_VDDA_TOTAL_CLOCK_DIV                       (`$INSTANCE_NAME`_TST_VDDA_MODCLK_DIV_DEFAULT * \
                                                                         `$INSTANCE_NAME`_TST_VDDA_SENSE_DIV_DEFAULT)

/* Acquisition time definitions: ADC_CTL */
#define `$INSTANCE_NAME`_VDDA_ACQUISITION_TIME_US                       (10uL)
#define `$INSTANCE_NAME`_VDDA_ACQUISITION_BASE                          ((`$INSTANCE_NAME`_VDDA_ACQUISITION_TIME_US * \
                                                                        (CYDEV_CLK_PERICLK__MHZ)) / \
                                                                        `$INSTANCE_NAME`_TST_VDDA_TOTAL_CLOCK_DIV)

#define `$INSTANCE_NAME`_TST_VDDA_ADC_AZ_TIME                           (5uL)
#define `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_BASE                         (((CYDEV_CLK_PERICLK__HZ * `$INSTANCE_NAME`_TST_VDDA_ADC_AZ_TIME) / \
                                                                           `$INSTANCE_NAME`_TST_VDDA_TOTAL_CLOCK_DIV) / 1000000uL)

#if (0 == `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_BASE)
    #define `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_DEFAULT                  (1u)
#else
    #define `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_DEFAULT                  (`$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_BASE)
#endif




#define `$INSTANCE_NAME`_TST_VDDA_FILTER_DELAY                          (2uL)
#define `$INSTANCE_NAME`_TST_VDDA_FINE_INIT_TIME                        (1u)
#define `$INSTANCE_NAME`_TST_VDDA_SCAN_DURATION                         (2uL)

#define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MAX_DEVIATION      (20uL)

/* The reference voltage macros */
#define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_0_8          (800uL)
#define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_1_2          (1164uL)
#define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_1_6          (1600uL)
#define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_2_1          (2133uL)
#define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_2_6          (2600uL)

#if (`$INSTANCE_NAME`_TST_VDDA_VREF_MV < `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_1_2)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_USED          (`$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_0_8)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF1)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_0P8_Pos)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_0P8_Msk)
#elif (`$INSTANCE_NAME`_TST_VDDA_VREF_MV < `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_1_6)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_USED          (`$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_1_2)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF0)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P2_Pos)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P2_Msk)
#elif (`$INSTANCE_NAME`_TST_VDDA_VREF_MV < `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_2_1)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_USED          (`$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_1_6)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF0)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P6_Pos)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P6_Msk)
#elif (`$INSTANCE_NAME`_TST_VDDA_VREF_MV < `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_2_6)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_USED          (`$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_2_1)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF1)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_2P1_Pos)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_2P1_Msk)
#else
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_USED          (`$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_BASE_2_6)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF2)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF2_VREF_HI_LEVELS_2P6_Pos)
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF2_VREF_HI_LEVELS_2P6_Msk)
#endif

#define `$INSTANCE_NAME`_TST_VDDA_BAD_RESULT                            (0xFFFFu)


#define `$INSTANCE_NAME`_TST_VDDA_CONFIG_DEFAULT_CFG                    (`$INSTANCE_NAME`_CSD_CONFIG_ENABLE_MSK |\
                                                                         `$INSTANCE_NAME`_CSD_CONFIG_SAMPLE_SYNC_MSK |\
                                                                         `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN_MSK |\
                                                                         `$INSTANCE_NAME`_CSD_CONFIG_DSI_COUNT_SEL_MSK)

#define `$INSTANCE_NAME`_TST_VDDA_IDACA_DEFAULT_CFG                     (0x00000000uL)
#define `$INSTANCE_NAME`_TST_VDDA_IDACB_DEFAULT_CFG                     (`$INSTANCE_NAME`_TST_VDDA_IDAC_DEFAULT |\
                                                                        (`$INSTANCE_NAME`_CSD_IDACB_POL_DYN_DYNAMIC << \
                                                                          `$INSTANCE_NAME`_CSD_IDACB_POL_DYN_POS) |\
                                                                          `$INSTANCE_NAME`_CSD_IDACB_LEG3_EN_MSK)

#define `$INSTANCE_NAME`_TST_CSDCMP_DEFAULT_CFG                         (0x00000000uL)
#define `$INSTANCE_NAME`_TST_SW_DSI_SEL_DEFAULT_CFG                     (0x00000000uL)
#define `$INSTANCE_NAME`_TST_SENSE_DUTY_VDDA_CFG                        (0x00000000uL)
#define `$INSTANCE_NAME`_TST_SEQ_INIT_CNT_DEFAULT_CFG                   (`$INSTANCE_NAME`_TST_VDDA_FINE_INIT_TIME)
#define `$INSTANCE_NAME`_TST_SEQ_NORM_CNT_DEFAULT_CFG                   (`$INSTANCE_NAME`_TST_VDDA_SCAN_DURATION)
#define `$INSTANCE_NAME`_TST_SW_HS_P_SEL_DEFAULT_CFG                    (`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SW_HMRH_STATIC_CLOSE)
#define `$INSTANCE_NAME`_TST_SW_HS_N_SEL_DEFAULT_CFG                    (`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_SW_HCCD_STATIC_CLOSE)
#define `$INSTANCE_NAME`_TST_SW_SHIELD_SEL_DEFAULT_CFG                  (0x00000000uL)
#define `$INSTANCE_NAME`_TST_SW_BYP_SEL_DEFAULT_CFG                     (`$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYA_MSK |\
                                                                         `$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYB_MSK)
#define `$INSTANCE_NAME`_TST_SW_CMP_P_SEL_DEFAULT_CFG                   (0x00000000uL)
#define `$INSTANCE_NAME`_TST_SW_CMP_N_SEL_DEFAULT_CFG                   (0x00000000uL)
#define `$INSTANCE_NAME`_TST_SW_FW_MOD_SEL_DEFAULT_CFG                  (`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_C1CC_STATIC_CLOSE |\
                                                                         `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SW_C1CD_STATIC_CLOSE)
#define `$INSTANCE_NAME`_TST_SW_FW_TANK_SEL_DEFAULT_CFG                 (`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_C2CC_STATIC_CLOSE |\
                                                                         `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SW_C2CD_STATIC_CLOSE)
#define `$INSTANCE_NAME`_TST_SW_REFGEN_SEL_DEFAULT_CFG                  (`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_SW_SGR_MSK)
#define `$INSTANCE_NAME`_TST_REFGEN_DEFAULT_CFG                         (`$INSTANCE_NAME`_CSD_REFGEN_REFGEN_EN_MSK |\
                                                                         `$INSTANCE_NAME`_CSD_REFGEN_RES_EN_MSK |\
                                                                        ((uint32)`$INSTANCE_NAME`_TST_VDDA_VREF_GAIN << \
                                                                         `$INSTANCE_NAME`_CSD_REFGEN_GAIN_POS))
#define `$INSTANCE_NAME`_TST_SW_AMUXBUF_SEL_DEFAULT_CFG                 (0x00000000uL)
#define `$INSTANCE_NAME`_TST_HSCMP_DEFAULT_CFG                          (`$INSTANCE_NAME`_CSD_HSCMP_HSCMP_EN_MSK |\
                                                                         `$INSTANCE_NAME`_CSD_HSCMP_AZ_EN_MSK)

#define `$INSTANCE_NAME`_TST_VDDA_SEQ_START_MEASURE_CFG                 (`$INSTANCE_NAME`_CSD_SEQ_START_AZ0_SKIP_MSK |\
                                                                        `$INSTANCE_NAME`_CSD_SEQ_START_START_MSK)

#endif /* #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_SELFTEST_H */


/* [] END OF FILE */
