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

#include "cytypes.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Sensing.h"

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)

/*******************************************************************************
* Function Prototypes - High-level API
*******************************************************************************/

/**
* \cond (SECTION_C_HIGH_LEVEL)
* \addtogroup group_c_high_level
* \{
*/

uint32 `$INSTANCE_NAME`_RunSelfTest(uint32 testEnMask);

/** \}
* \endcond */

/*******************************************************************************
* Function Prototypes - Low-level API
*******************************************************************************/

/**
* \cond (SECTION_C_LOW_LEVEL)
* \addtogroup group_c_low_level
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
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))
    uint16 `$INSTANCE_NAME`_GetVdda(void);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)) */

/** \}
* \endcond */

/*******************************************************************************
* Function Prototypes - Internal Functions
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
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

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN))
    CY_ISR_PROTO(`$INSTANCE_NAME`_BistPostSingleScan);
#endif

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

    /* Defines external capacitor ID */
    #define `$INSTANCE_NAME`_TST_CMOD_MAP                               (0u)
    #define `$INSTANCE_NAME`_TST_CSH_MAP                                (1u)
    #define `$INSTANCE_NAME`_TST_CINTA_MAP                              (2u)
    #define `$INSTANCE_NAME`_TST_CINTB_MAP                              (3u)

    #define `$INSTANCE_NAME`_08_BIT_SHIFT                               (8uL)

    #define `$INSTANCE_NAME`_BIST_SNS_CAP_MAX_CP                        ((0x00000001uL << 8uL) - 1uL)
    #define `$INSTANCE_NAME`_BIST_SH_CAP_MAX_CP                         ((0x00000001uL << 16uL) - 1uL)
    #define `$INSTANCE_NAME`_BIST_SNS_CAP_UNIT_SCALE                    (1000uL)
    #define `$INSTANCE_NAME`_BIST_10_BIT_MASK                           ((0x00000001uL << 10uL) - 1uL)
    #define `$INSTANCE_NAME`_BIST_CALIBRATION_TARGET                    ((`$INSTANCE_NAME`_BIST_10_BIT_MASK * \
                                                                          `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL) / \
                                                                          `$INSTANCE_NAME`_PERCENTAGE_100)

    #define `$INSTANCE_NAME`_BIST_AVG_CYCLES_PER_LOOP                   (5u)
    #define `$INSTANCE_NAME`_BIST_MEASURE_MAX_TIME_US                   (3000u)
    #define `$INSTANCE_NAME`_BIST_PRECHARGE_MAX_TIME_US                 (250u)

    #define `$INSTANCE_NAME`_BIST_MEASURE_WATCHDOG_CYCLES_NUM           (((CYDEV_BCLK__HFCLK__MHZ) * (`$INSTANCE_NAME`_BIST_MEASURE_MAX_TIME_US)) /\
                                                                        (`$INSTANCE_NAME`_BIST_AVG_CYCLES_PER_LOOP))
    #define `$INSTANCE_NAME`_BIST_PRECHARGE_WATCHDOG_CYCLES_NUM         (((CYDEV_BCLK__HFCLK__MHZ) * (`$INSTANCE_NAME`_BIST_PRECHARGE_MAX_TIME_US)) /\
                                                                        (`$INSTANCE_NAME`_BIST_AVG_CYCLES_PER_LOOP))

    /* Min idac code at which we can guarantee 10% of raw count step per idac changing for one */
    #define `$INSTANCE_NAME`_BIST_MIN_IDAC_VALUE                        (12uL)
    #define `$INSTANCE_NAME`_BIST_MAX_IDAC_VALUE                        ((1uL << `$INSTANCE_NAME`_IDAC_BITS_USED) - 5uL)
    #define `$INSTANCE_NAME`_BIST_MAX_MODCLK_DIVIDER                    (0x000000FFuL)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_LOW_RANGE                  (5uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION                 (0x00000001uL << 10uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_DURATION                   (1uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ                 (4uL)
    #define `$INSTANCE_NAME`_SENSE_DUTY_TST_EXT_CAP_WIDTH           (10uL)
    #define `$INSTANCE_NAME`_SEQ_INIT_CNT_FINE_INIT_SKIP            (0x00000000uL)
    #define `$INSTANCE_NAME`_IDAC_BITS_USED                         (7u)
#else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
    #define `$INSTANCE_NAME`_TST_EXT_CAP_LOW_RANGE                  (5uL << 3uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION                 (0xFFuL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_SNSCLK_DIVIDER             (0xFFuL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_DURATION                   (`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION << \
                                                                     `$INSTANCE_NAME`_RESOLUTION_OFFSET)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ                 (2uL)
    #define `$INSTANCE_NAME`_IDAC_BITS_USED                         (8u)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

#define `$INSTANCE_NAME`_BIST_CAL_MIDDLE_BIT                        (1uL << (`$INSTANCE_NAME`_IDAC_BITS_USED - 1u))
#define `$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION_75                  ((`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION >> 1uL) +\
                                                                     (`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION >> 2uL))
#define `$INSTANCE_NAME`_TST_EXT_CAP_MLTPLR                         (2u)
#define `$INSTANCE_NAME`_CSDCMP_TST_CAP_MEAS                        (0x00000201uL)

/***********************************************************************************************************************
* HW CSD Block Config
***********************************************************************************************************************/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

    #define `$INSTANCE_NAME`_BIST_INTR_SET_CFG                          (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_CFG                    (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_CAP_SENSE_DUTY_SEL                    (0x00010000uL)
    #define `$INSTANCE_NAME`_BIST_AMBUF_PWR_MODE_OFF                    (`$INSTANCE_NAME`_AMBUF_PWR_MODE_OFF)
    #define `$INSTANCE_NAME`_BIST_AUTO_ZERO_TIME                        (`$INSTANCE_NAME`_CSD_AUTO_ZERO_TIME)

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_CMODPAD                (`$INSTANCE_NAME`_SW_DSI_CMOD)
        #elif (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_CMODPAD                (`$INSTANCE_NAME`_SW_DSI_CTANK)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_CMODPAD                (0x00000000uL)
        #endif

        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_TANKPAD                (`$INSTANCE_NAME`_SW_DSI_CTANK)
        #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_TANKPAD                (`$INSTANCE_NAME`_SW_DSI_CMOD)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_TANKPAD                (0x00000000uL)
        #endif
    #else
        #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_CMODPAD                (`$INSTANCE_NAME`_SW_DSI_CMOD)
        #define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_TANKPAD                (`$INSTANCE_NAME`_SW_DSI_CTANK)
    #endif

    #define `$INSTANCE_NAME`_BIST_DEFAULT_SW_DSI_SEL                    (`$INSTANCE_NAME`_BIST_SW_DSI_SEL_CMODPAD | \
                                                                         `$INSTANCE_NAME`_BIST_SW_DSI_SEL_TANKPAD)
    #define `$INSTANCE_NAME`_BIST_ADC_CTL_CFG                           (0x00000000uL)
    /* Shield switch default config */
    #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_INIT                 (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCAV_HSCMP)
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_HSCMP)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI1 | \
                                                                      `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG          (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                      `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    #else
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG              (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

    /* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */
    #else
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD                   (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */
    #else
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK                   (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK                     (`$INSTANCE_NAME`_STATIC_OPEN)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN_TANK)
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN                       (`$INSTANCE_NAME`_STATIC_OPEN)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    #define `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_COARSE                    (`$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_CMOD | `$INSTANCE_NAME`_BIST_HS_P_SEL_COARSE_TANK)
    #define `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_CFG                       (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_SW_HS_N_SEL_CFG                       (0x00000000uL)

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN)
        #define `$INSTANCE_NAME`_BIST_AZ_ENABLE_CFG                  (`$INSTANCE_NAME`_CSD_AZ_EN_MASK)
    #else
        #define `$INSTANCE_NAME`_BIST_AZ_ENABLE_CFG                  (0uL)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN) */

    #define `$INSTANCE_NAME`_BIST_HSCMP_CFG                             (`$INSTANCE_NAME`_HSCMP_EN_MASK | `$INSTANCE_NAME`_BIST_AZ_ENABLE_CFG)
    #define `$INSTANCE_NAME`_BIST_CSDCMP_INIT                           (`$INSTANCE_NAME`_CSDCMP_CSDCMP_DISABLED)

    #define `$INSTANCE_NAME`_BIST_BLOCK_ON_DELAY                        (3uL * CYDEV_BCLK__HFCLK__MHZ)
    #define `$INSTANCE_NAME`_BIST_HSCMP_ON_DELAY                        (1uL * CYDEV_BCLK__HFCLK__MHZ)

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT    (`$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT    (0x00000000uL)
        #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */

        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT   (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT   (0x00000000uL)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */

    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT        (`$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)

        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT       (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                 `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
    #else
        #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT        (0x00000000uL)
        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT       (0x00000000uL)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */


    #define `$INSTANCE_NAME`_BIST_SW_RES_INIT                           (`$INSTANCE_NAME`_CSD_INIT_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET)
    #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_SCAN                    (0x00000000uL)
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
         (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_SCAN               (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                         `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CB_PHI2)
    #else
        #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_SCAN               (0x00000000uL)
    #endif

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
         (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_HSCMP)
    #elif((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
          (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_HSCMP)
    #elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                         `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
    #else
        #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL                     (0x00000000uL)
    #endif
    #define `$INSTANCE_NAME`_BIST_SW_RES_SCAN                           ((`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET) |\
                                                                         (`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBG__OFFSET))
    #define `$INSTANCE_NAME`_BIST_HSCMP_SCAN_MASK                       (`$INSTANCE_NAME`_HSCMP_EN_MASK)
    #define `$INSTANCE_NAME`_BIST_IDACB_CFG                             (0x00000000uL)
    #define `$INSTANCE_NAME`_BIST_IDACA_CFG                             (0x01830000uL)

    /* IDAC Gain in nA */
    #define `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN                      (2400uL)

    #if ((CYDEV_BCLK__HFCLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ)
        #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ)
    #elif ((CYDEV_BCLK__HFCLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ)
        #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_24MHZ)
    #else
        /* ((CYDEV_BCLK__HFCLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_48MHZ) */
        #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_48MHZ)
    #endif

    #define `$INSTANCE_NAME`_BIST_CSD_CONFIG                            (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_2_CYCLES)
    #define `$INSTANCE_NAME`_BIST_SW_REFGEN_SEL_CFG                     (`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK)

    #define `$INSTANCE_NAME`_TST_MEASMODE_VREF                              (0x1uL << CYFLD_CSD_ADC_MODE__OFFSET)
    #define `$INSTANCE_NAME`_TST_MEASMODE_VREFBY2                           (0x2uL << CYFLD_CSD_ADC_MODE__OFFSET)
    #define `$INSTANCE_NAME`_TST_MEASMODE_VIN                               (0x3uL << CYFLD_CSD_ADC_MODE__OFFSET)

    /* Clock defines */
    #define `$INSTANCE_NAME`_TST_VDDA_MODCLK_DIV_DEFAULT                    (`$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER)
    #define `$INSTANCE_NAME`_TST_VDDA_SENSE_DIV_DEFAULT                     (0x4uL)
    #define `$INSTANCE_NAME`_TST_VDDA_TOTAL_CLOCK_DIV                       (`$INSTANCE_NAME`_TST_VDDA_MODCLK_DIV_DEFAULT * \
                                                                             `$INSTANCE_NAME`_TST_VDDA_SENSE_DIV_DEFAULT)

    /* Acquisition time definitions: ADC_CTL */
    #define `$INSTANCE_NAME`_VDDA_ACQUISITION_TIME_US                       (10uL)
    #define `$INSTANCE_NAME`_VDDA_ACQUISITION_BASE                          ((`$INSTANCE_NAME`_VDDA_ACQUISITION_TIME_US * \
                                                                            (CYDEV_BCLK__HFCLK__MHZ)) / \
                                                                            `$INSTANCE_NAME`_TST_VDDA_TOTAL_CLOCK_DIV)

    #define `$INSTANCE_NAME`_TST_VDDA_ADC_AZ_TIME                           (5uL)
    #define `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_BASE                         (((CYDEV_BCLK__HFCLK__HZ * `$INSTANCE_NAME`_TST_VDDA_ADC_AZ_TIME) / \
                                                                               `$INSTANCE_NAME`_TST_VDDA_TOTAL_CLOCK_DIV) / 1000000uL)

    #if (0 == `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_BASE)
        #define `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_DEFAULT                  (1u)
    #else
        #define `$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_DEFAULT                  (`$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_BASE)
    #endif




    #define `$INSTANCE_NAME`_TST_VDDA_FILTER_DELAY                          (2uL)
    #define `$INSTANCE_NAME`_TST_VDDA_FINE_INIT_TIME                        (`$INSTANCE_NAME`_TST_FINE_INIT_TIME)
    #define `$INSTANCE_NAME`_TST_VDDA_SCAN_DURATION                         (2uL)

    #define `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MAX_DEVIATION               (20uL)

    /* The reference voltage macros */
    #define `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_USED                       (2400uL)

    #define `$INSTANCE_NAME`_TST_VDDA_BAD_RESULT                            (0xFFFFu)


    #define `$INSTANCE_NAME`_TST_VDDA_CONFIG_DEFAULT_CFG                    (`$INSTANCE_NAME`_CONFIG_ENABLE_MASK |\
                                                                             `$INSTANCE_NAME`_CONFIG_SAMPLE_SYNC_MASK |\
                                                                             `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |\
                                                                             `$INSTANCE_NAME`_CONFIG_DSI_COUNT_SEL_MASK)

    #define `$INSTANCE_NAME`_TST_VDDA_IDACA_DEFAULT_CFG                     (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_VDDA_IDACB_DEFAULT_CFG                     (`$INSTANCE_NAME`_TST_VDDA_IDAC_DEFAULT |\
                                                                            (`$INSTANCE_NAME`_IDAC_COMP_POL_DYN_DYNAMIC << \
                                                                              CYFLD_CSD_POL_DYN__OFFSET) |\
                                                                              `$INSTANCE_NAME`_IDAC_COMP_LEG3_EN_MASK)

    #define `$INSTANCE_NAME`_TST_CSDCMP_DEFAULT_CFG                         (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_SW_DSI_SEL_DEFAULT_CFG                     (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_SENSE_DUTY_VDDA_CFG                        (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_SEQ_INIT_CNT_DEFAULT_CFG                   (1u)
    #define `$INSTANCE_NAME`_TST_SEQ_NORM_CNT_DEFAULT_CFG                   (`$INSTANCE_NAME`_TST_VDDA_SCAN_DURATION)
    #define `$INSTANCE_NAME`_TST_SW_HS_P_SEL_DEFAULT_CFG                    (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMRH_STATIC_CLOSE)
    #define `$INSTANCE_NAME`_TST_SW_HS_N_SEL_DEFAULT_CFG                    (`$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCCD_STATIC_CLOSE)
    #define `$INSTANCE_NAME`_TST_SW_SHIELD_SEL_DEFAULT_CFG                  (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_SW_BYP_SEL_DEFAULT_CFG                     (`$INSTANCE_NAME`_SW_BYP_SEL_SW_BYA_MASK |\
                                                                             `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYB_MASK)
    #define `$INSTANCE_NAME`_TST_SW_CMP_P_SEL_DEFAULT_CFG                   (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_SW_CMP_N_SEL_DEFAULT_CFG                   (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_SW_FW_MOD_SEL_DEFAULT_CFG                  (`$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_C1CC_STATIC_CLOSE |\
                                                                             `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_C1CD_STATIC_CLOSE)
    #define `$INSTANCE_NAME`_TST_SW_FW_TANK_SEL_DEFAULT_CFG                 (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_C2CC_STATIC_CLOSE |\
                                                                             `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_C2CD_STATIC_CLOSE)
    #define `$INSTANCE_NAME`_TST_SW_REFGEN_SEL_DEFAULT_CFG                  (`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK)
    #define `$INSTANCE_NAME`_TST_REFGEN_DEFAULT_CFG                         (`$INSTANCE_NAME`_REFGEN_REFGEN_EN_MASK |\
                                                                             `$INSTANCE_NAME`_REFGEN_RES_EN_MASK |\
                                                                            ((uint32)`$INSTANCE_NAME`_TST_VDDA_VREF_GAIN << \
                                                                             CYFLD_CSD_GAIN__OFFSET))
    #define `$INSTANCE_NAME`_TST_SW_AMUXBUF_SEL_DEFAULT_CFG                 (0x00000000uL)
    #define `$INSTANCE_NAME`_TST_HSCMP_DEFAULT_CFG                          (`$INSTANCE_NAME`_HSCMP_EN_MASK |\
                                                                             `$INSTANCE_NAME`_CSD_AZ_EN_MASK)

    #define `$INSTANCE_NAME`_TST_VDDA_SEQ_START_MEASURE_CFG                 (`$INSTANCE_NAME`_SEQ_START_AZ0_SKIP_MASK |\
                                                                            `$INSTANCE_NAME`_SEQ_START_START_MASK)
#else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

#define `$INSTANCE_NAME`_BIST_CSD_CONFIG                            (`$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_DRV_MASK)

#define `$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG                 (`$INSTANCE_NAME`_BIST_CSD_CONFIG | \
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)

#define `$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG_CSD_EN          (`$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG | \
                                                                     `$INSTANCE_NAME`_CSD_ENABLE_MASK)

/* Third-generation HW block Ctank pre-charge mode configuration */
#if(`$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC == `$INSTANCE_NAME`_CSH_PRECHARGE_VREF)
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #define  `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG       (`$INSTANCE_NAME`_BIST_CSD_CONFIG | \
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK)
    #else
        #define  `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG       (`$INSTANCE_NAME`_BIST_CSD_CONFIG | \
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
#else
    #define  `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG           (`$INSTANCE_NAME`_BIST_CSD_CONFIG |\
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                     `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK |\
                                                                     `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK |\
                                                                     `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)

#endif /* (`$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC == `$INSTANCE_NAME`__CSH_PRECHARGE_IO_BUF) */

#define  `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG_CSD_EN        (`$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG | \
                                                                     `$INSTANCE_NAME`_CONFIG_ENABLE_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK)

#define `$INSTANCE_NAME`_BIST_IDAC_CFG                              (0x00000200uL)
#define `$INSTANCE_NAME`_BIST_IDAC_MOD_MASK                         (0x000003FFuL)
#define `$INSTANCE_NAME`_BIST_IDAC_MOD_VAL_MASK                     (0x000000FFuL)

/* IDAC Gain = 8x that corresponds to 1LSB = 1200 nA */
#define `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN                      (1200uL)

#define `$INSTANCE_NAME`_BIST_SCAN_DURATION                         (`$INSTANCE_NAME`_BIST_10_BIT_MASK << `$INSTANCE_NAME`_RESOLUTION_OFFSET)
#define `$INSTANCE_NAME`_BIST_SCAN_DURATION_255                     (0x1FFuL << `$INSTANCE_NAME`_RESOLUTION_OFFSET)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

#endif /* #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_SELFTEST_H */


/* [] END OF FILE */
