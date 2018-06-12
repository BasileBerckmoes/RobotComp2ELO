/***************************************************************************//**
* \file `$INSTANCE_NAME`_SelfTest.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the function prototypes for the Built-In Self-Test 
*   library.
*
* \see CapSense P4 v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
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

#if !defined(CY_CAPSENSE_`$INSTANCE_NAME`_SELFTEST_H)
#define CY_CAPSENSE_`$INSTANCE_NAME`_SELFTEST_H

#include "cytypes.h"
#include "`$INSTANCE_NAME`_Sensing.h"
    
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)

/*******************************************************************************
* Function Prototypes - High-level API
*******************************************************************************/
/**
* \if SECTION_CAPSENSE_HIGH_LEVEL
* \addtogroup group_capsense_high_level
* \{
*/

uint32 `$INSTANCE_NAME`_RunSelfTest(uint32 testEnMask);

/** \}
* \endif */
    
/*******************************************************************************
* Function Prototypes - Low-level API
*******************************************************************************/
/**
* \if SECTION_CAPSENSE_LOW_LEVEL
* \addtogroup group_capsense_low_level
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

/** \}
* \endif */

/*******************************************************************************
* Function Prototypes - Internal Functions
*******************************************************************************/
/**
* \if SECTION_CAPSENSE_INTERNAL
* \addtogroup group_capsense_internal
* \{
*/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
    void `$INSTANCE_NAME`_DsUpdateGlobalCrc(void);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)    
    void `$INSTANCE_NAME`_DsUpdateWidgetCrc(uint32 widgetId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)   */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
    void `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(uint32 widgetId, uint32 sensorId);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

void `$INSTANCE_NAME`_BistInitialize(void);
void `$INSTANCE_NAME`_BistDisableMode(void);

/** \}
* \endif */

/***********************************************************************************************************************
* Local definition
***********************************************************************************************************************/
/* Defines a mask for baseline data processing failure */
#define `$INSTANCE_NAME`_PROCESS_BASELINE_FAILED                    (0x01uL << 31u)
 
/* Defines constants for Self-Test library */   
#define `$INSTANCE_NAME`_TST_LSBYTE                                 (0xFFuL)
#define `$INSTANCE_NAME`_TST_FAILED                                 (0xFFFFuL)
#define `$INSTANCE_NAME`_TST_BAD_PARAM                              (1Lu << 30u)
#define `$INSTANCE_NAME`_TST_NOT_EXECUTED                           (1Lu << 31u)
    
/* Defines an external capacitor ID */
#define `$INSTANCE_NAME`_TST_CMOD_MAP                               (0u)
#define `$INSTANCE_NAME`_TST_CSH_MAP                                (1u)    
#define `$INSTANCE_NAME`_TST_CINTA_MAP                              (2u)
#define `$INSTANCE_NAME`_TST_CINTB_MAP                              (3u)

#define `$INSTANCE_NAME`_08_BIT_SHIFT                               (8uL)

#define `$INSTANCE_NAME`_BIST_SNS_CAP_MAX_CP                        ((0x01uL << 8uL) - 1uL)
#define `$INSTANCE_NAME`_BIST_SH_CAP_MAX_CP                         ((0x01uL << 16uL) - 1uL)
#define `$INSTANCE_NAME`_BIST_SNS_CAP_UNIT_SCALE                    (1000uL)
#define `$INSTANCE_NAME`_BIST_10_BIT_MASK                           ((0x00000001uL << 10uL) - 1uL)
#define `$INSTANCE_NAME`_BIST_CALIBRATION_TARGET                    ((`$INSTANCE_NAME`_BIST_10_BIT_MASK * \
                                                                      `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL) / \
                                                                      `$INSTANCE_NAME`_PERCENTAGE_100)
/* Min IDAC code at which we can guarantee 10% of the raw count step per IDAC changing for one */
#define `$INSTANCE_NAME`_BIST_MIN_IDAC_VALUE                        (12uL)
#define `$INSTANCE_NAME`_BIST_MAX_IDAC_VALUE                        ((1uL << `$INSTANCE_NAME`_CSD_IDAC_BITS_USED) - 5uL)
#define `$INSTANCE_NAME`_BIST_MAX_MODCLK_DIVIDER                    (0xFFuL)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_LOW_RANGE                  (5uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION                 (1uL << 10uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_DURATION                   (1uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ                 (4uL)
    #define `$INSTANCE_NAME`_SENSE_DUTY_TST_EXT_CAP_WIDTH           (10uL)
    #define `$INSTANCE_NAME`_SEQ_INIT_CNT_FINE_INIT_SKIP            (0x00000000uL)
#else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
    #define `$INSTANCE_NAME`_TST_EXT_CAP_LOW_RANGE                  (5uL << 3uL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION                 (0xFFuL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_SNSCLK_DIVIDER             (0xFFuL)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_DURATION                   (`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION << \
                                                                     `$INSTANCE_NAME`_RESOLUTION_OFFSET)
    #define `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ                 (2uL)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

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

#define `$INSTANCE_NAME`_BIST_SW_DSI_SEL_CFG                        (`$INSTANCE_NAME`_BIST_SW_DSI_SEL_CMODPAD | \
                                                                     `$INSTANCE_NAME`_BIST_SW_DSI_SEL_TANKPAD)

#define `$INSTANCE_NAME`_BIST_ADC_CTL_CFG                           (0x00000000uL)
    
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
     (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
    #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG                 (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_HSCMP)
    
#elif((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
      (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
    #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG                 (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_HSCMP)
#elif(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
    #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG                 (`$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                     `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
#else
    #define `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG                 (0x00000000uL)
#endif 

#define `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_CFG                       (0x00000000uL)
#define `$INSTANCE_NAME`_BIST_SW_HS_N_SEL_CFG                       (0x00000000uL)
#define `$INSTANCE_NAME`_BIST_HSCMP_CFG                             (0x00000000uL)

#define `$INSTANCE_NAME`_BIST_BLOCK_ON_DELAY                        (3uL * CYDEV_BCLK__SYSCLK__MHZ)
#define `$INSTANCE_NAME`_BIST_HSCMP_ON_DELAY                        (1uL * CYDEV_BCLK__SYSCLK__MHZ)

#if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
    #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT                (`$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                    `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                    `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)
#else
    #define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT                (0x00000000uL)
#endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */

#if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
    #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT               (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                    `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                    `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
#else
    #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT               (0x00000000uL)
#endif

#if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
    #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT               (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                    `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                    `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
#else
    #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT               (0x00000000uL)
#endif 

#define `$INSTANCE_NAME`_BIST_SW_RES_INIT                           (`$INSTANCE_NAME`_CSD_INIT_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET)
#define `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_SCAN                     (0x00000000uL)
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && \
     (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION))
    #define `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_SCAN               (`$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE | `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CB_PHI2)
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
#define `$INSTANCE_NAME`_BIST_SW_RES_SCAN                           ((`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET) | \
                                                                    (`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBG__OFFSET))
#define `$INSTANCE_NAME`_BIST_HSCMP_SCAN_MASK                       (`$INSTANCE_NAME`_HSCMP_EN_MASK)
#define `$INSTANCE_NAME`_BIST_IDACB_CFG                             (0x00000000uL)
#define `$INSTANCE_NAME`_BIST_IDACA_CFG                             (0x01830000uL)

/* IDAC Gain = IDAC_HI that corresponds to 1LSB = 2400 nA */
#define `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN                      (2400uL)

#if ((CYDEV_BCLK__HFCLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ)
    #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ)
#elif ((CYDEV_BCLK__HFCLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ)
    #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_24MHZ)
#else 
    /* ((CYDEV_BCLK__HFCLK__HZ / `$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER) <= `$INSTANCE_NAME`_MOD_CSD_CLK_48MHZ) */
    #define `$INSTANCE_NAME`_FILTER_DELAY_CFG                       (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_48MHZ)
#endif    

#define `$INSTANCE_NAME`_BIST_CSD_CONFIG                            (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_2_CYCLES | \
                                                                     `$INSTANCE_NAME`_CONFIG_SAMPLE_SYNC_MASK)

#else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

#define `$INSTANCE_NAME`_BIST_CSD_CONFIG                            (`$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_DRV_MASK)

#define `$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG                 (`$INSTANCE_NAME`_BIST_CSD_CONFIG | \
                                                                     `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK | \
                                                                     `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)
    
#define `$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG_CSD_EN          (`$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG | \
                                                                     `$INSTANCE_NAME`_CSD_ENABLE_MASK)

/* CSDv1 Ctank pre-charge mode configuration */
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

#endif /* End CY_CAPSENSE_`$INSTANCE_NAME`_SELFTEST_H */


/* [] END OF FILE */
