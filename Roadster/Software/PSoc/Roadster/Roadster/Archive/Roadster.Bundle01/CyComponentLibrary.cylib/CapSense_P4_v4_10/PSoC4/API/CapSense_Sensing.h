/***************************************************************************//**
* \file `$INSTANCE_NAME`_Sensing.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* This file provides the headers of APIs specific to implementation of the
* sensing FW block.
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

#if !defined(CY_SENSE_`$INSTANCE_NAME`_SENSING_H)
#define CY_SENSE_`$INSTANCE_NAME`_SENSING_H

#include <CyLib.h>
#include <cyfitter.h>
#include "cytypes.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Structure.h"
#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN)
    #include "`$INSTANCE_NAME`_ISR.h"
#endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
    #include "`$INSTANCE_NAME`_SensingCSX_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
    #include "`$INSTANCE_NAME`_SensingISX_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    #include "`$INSTANCE_NAME`_SensingCSD_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    #include "`$INSTANCE_NAME`_SensingCSD2X_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    #include "`$INSTANCE_NAME`_SmartSense_LL.h"
#endif  /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
    #include "`$INSTANCE_NAME`_Adc.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */

/*******************************************************************************
* Enumeration types definition
*******************************************************************************/

/* Pin states */
#define `$INSTANCE_NAME`_GROUND                         (0u)
#define `$INSTANCE_NAME`_HIGHZ                          (1u)
#define `$INSTANCE_NAME`_SHIELD                         (2u)
#define `$INSTANCE_NAME`_SENSOR                         (3u)
#define `$INSTANCE_NAME`_TX_PIN                         (4u)
#define `$INSTANCE_NAME`_RX_PIN                         (5u)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
* \cond (SECTION_C_HIGH_LEVEL || SECTION_I_HIGH_LEVEL)
* \addtogroup group_c_high_level
* \{
*/

cystatus `$INSTANCE_NAME`_SetupWidget(uint32 widgetId);
cystatus `$INSTANCE_NAME`_Scan(void);
cystatus `$INSTANCE_NAME`_ScanAllWidgets(void);
uint32 `$INSTANCE_NAME`_IsBusy(void);

/** \}
* \endcond */

/**
* \cond (SECTION_C_LOW_LEVEL || SECTION_I_LOW_LEVEL)
* \addtogroup group_c_low_level
* \{
*/

void `$INSTANCE_NAME`_SetPinState(uint32 widgetId, uint32 sensorElement, uint32 state);
#if (`$INSTANCE_NAME`_ANYMODE_AUTOCAL)
    cystatus `$INSTANCE_NAME`_CalibrateWidget(uint32 widgetId);
    cystatus `$INSTANCE_NAME`_CalibrateAllWidgets(void);
#endif /* (`$INSTANCE_NAME`_ANYMODE_AUTOCAL)  */

/** \}
* \endcond */

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

cystatus `$INSTANCE_NAME`_SsInitialize(void);
void `$INSTANCE_NAME`_SsSetModClkClockDivider(uint32 modClk);
void `$INSTANCE_NAME`_SsSetSnsClockDivider(uint32 snsClk);
void `$INSTANCE_NAME`_SsSetClockDividers(uint32 snsClk, uint32 modClk);
void `$INSTANCE_NAME`_SsIsrInitialize(cyisraddress address);
void `$INSTANCE_NAME`_SsPostAllWidgetsScan(void);
void `$INSTANCE_NAME`_SsSetIOsInDefaultState(void);
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_ISX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))
    void `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_ENUM mode);
#endif  /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)) */
#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    cystatus `$INSTANCE_NAME`_SsAutoTune(void);
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
    void `$INSTANCE_NAME`_SsChangeImoFreq(uint32 value);
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
    cystatus `$INSTANCE_NAME`_SsReleaseResources(void);
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */

#if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) ||\
    (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)))
    void `$INSTANCE_NAME`_SsInitializeSourceSenseClk(void);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) ||\
           ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))) */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN))
    void `$INSTANCE_NAME`_SsClearCSDSensors(void);
    uint32 `$INSTANCE_NAME`_SsCSDGetColSnsClkDivider(uint32 widgetId);
    #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
        uint32 `$INSTANCE_NAME`_SsCSDGetRowSnsClkDivider(uint32 widgetId);
    #endif /* (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */
    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        uint8 `$INSTANCE_NAME`_SsCSDCalcPrsSize(uint32 snsClkDivider, uint32 resolution);
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)) */

/** \}
* \endcond */


/****************************************************************************
* m0s8csd, m0s8peri, hsiom, and IO hardware-related registers address
****************************************************************************/

#define `$INSTANCE_NAME`_DR_MASK                                (0x00000001Lu)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

    /* CSDv2 block registers   */
    #define `$INSTANCE_NAME`_CONFIG_REG                         (*(reg32 *) CYREG_CSD_CONFIG)
    #define `$INSTANCE_NAME`_CONFIG_PTR                         ( (reg32 *) CYREG_CSD_CONFIG)

    #define `$INSTANCE_NAME`_STAT_SEQ_REG                       (*(reg32 *) CYREG_CSD_CONFIG)
    #define `$INSTANCE_NAME`_STAT_SEQ_PTR                       ( (reg32 *) CYREG_CSD_CONFIG)

    #define `$INSTANCE_NAME`_IDAC_MOD_REG                       (*(reg32 *) CYREG_CSD_IDACA)
    #define `$INSTANCE_NAME`_IDAC_MOD_PTR                       ( (reg32 *) CYREG_CSD_IDACA)

    #define `$INSTANCE_NAME`_IDAC_COMP_REG                      (*(reg32 *) CYREG_CSD_IDACB)
    #define `$INSTANCE_NAME`_IDAC_COMP_PTR                      ( (reg32 *) CYREG_CSD_IDACB)

    #define `$INSTANCE_NAME`_SENSE_PERIOD_REG                   (*(reg32 *) CYREG_CSD_SENSE_PERIOD)
    #define `$INSTANCE_NAME`_SENSE_PERIOD_PTR                   ( (reg32 *) CYREG_CSD_SENSE_PERIOD)

    #define `$INSTANCE_NAME`_RESULT_VAL1_REG                    (*(reg32 *) CYREG_CSD_RESULT_VAL1)
    #define `$INSTANCE_NAME`_RESULT_VAL1_PTR                    ( (reg32 *) CYREG_CSD_RESULT_VAL1)

    #define `$INSTANCE_NAME`_RESULT_VAL2_REG                    (*(reg32 *) CYREG_CSD_RESULT_VAL2)
    #define `$INSTANCE_NAME`_RESULT_VAL2_PTR                    ( (reg32 *) CYREG_CSD_RESULT_VAL2)

    #define `$INSTANCE_NAME`_INTR_REG                           (*(reg32 *) CYREG_CSD_INTR)
    #define `$INSTANCE_NAME`_INTR_PTR                           ( (reg32 *) CYREG_CSD_INTR)

    #define `$INSTANCE_NAME`_INTR_SET_REG                       (*(reg32 *) CYREG_CSD_INTR_SET)
    #define `$INSTANCE_NAME`_INTR_SET_PTR                       ( (reg32 *) CYREG_CSD_INTR_SET)

    #define `$INSTANCE_NAME`_INTR_MASK_REG                      (*(reg32 *) CYREG_CSD_INTR_MASK)
    #define `$INSTANCE_NAME`_INTR_MASK_PTR                      ( (reg32 *) CYREG_CSD_INTR_MASK)

    #define `$INSTANCE_NAME`_COUNTER_REG                        (`$INSTANCE_NAME`_RESULT_VAL1_REG)
    #define `$INSTANCE_NAME`_COUNTER_PTR                        (`$INSTANCE_NAME`_RESULT_VAL1_PTR)

    #define `$INSTANCE_NAME`_REFGEN_REG                         (*(reg32 *) CYREG_CSD_REFGEN)
    #define `$INSTANCE_NAME`_REFGEN_PTR                         ( (reg32 *) CYREG_CSD_REFGEN)

    #define `$INSTANCE_NAME`_SEQ_TIME_REG                       (*(reg32 *) CYREG_CSD_SEQ_TIME)
    #define `$INSTANCE_NAME`_SEQ_TIME_PTR                       ( (reg32 *) CYREG_CSD_SEQ_TIME)

    #define `$INSTANCE_NAME`_SEQ_INIT_CNT_REG                   (*(reg32 *) CYREG_CSD_SEQ_INIT_CNT)
    #define `$INSTANCE_NAME`_SEQ_INIT_CNT_PTR                   ( (reg32 *) CYREG_CSD_SEQ_INIT_CNT)

    #define `$INSTANCE_NAME`_SEQ_NORM_CNT_REG                   (*(reg32 *) CYREG_CSD_SEQ_NORM_CNT)
    #define `$INSTANCE_NAME`_SEQ_NORM_CNT_PTR                   ( (reg32 *) CYREG_CSD_SEQ_NORM_CNT)

    #define `$INSTANCE_NAME`_SEQ_START_REG                      (*(reg32 *) CYREG_CSD_SEQ_START)
    #define `$INSTANCE_NAME`_SEQ_START_PTR                      ( (reg32 *) CYREG_CSD_SEQ_START)

    #define `$INSTANCE_NAME`_CSDCMP_REG                         (*(reg32 *) CYREG_CSD_CSDCMP)
    #define `$INSTANCE_NAME`_CSDCMP_PTR                         ( (reg32 *) CYREG_CSD_CSDCMP)

    #define `$INSTANCE_NAME`_HSCMP_REG                          (*(reg32 *) CYREG_CSD_HSCMP)
    #define `$INSTANCE_NAME`_HSCMP_PTR                          ( (reg32 *) CYREG_CSD_HSCMP)

    #define `$INSTANCE_NAME`_SENSE_DUTY_REG                     (*(reg32 *) CYREG_CSD_SENSE_DUTY)
    #define `$INSTANCE_NAME`_SENSE_DUTY_PTR                     ( (reg32 *) CYREG_CSD_SENSE_DUTY)

    #define `$INSTANCE_NAME`_AMBUF_REG                          (*(reg32 *) CYREG_CSD_AMBUF)
    #define `$INSTANCE_NAME`_AMBUF_PTR                          ( (reg32 *) CYREG_CSD_AMBUF)

    #define `$INSTANCE_NAME`_SW_BYP_SEL_REG                     (*(reg32 *) CYREG_CSD_SW_BYP_SEL)
    #define `$INSTANCE_NAME`_SW_BYP_SEL_PTR                     ( (reg32 *) CYREG_CSD_SW_BYP_SEL)

    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_REG                   (*(reg32 *) CYREG_CSD_SW_CMP_P_SEL)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_PTR                   ( (reg32 *) CYREG_CSD_SW_CMP_P_SEL)

    #define `$INSTANCE_NAME`_SW_REFGEN_SEL_REG                  (*(reg32 *) CYREG_CSD_SW_REFGEN_SEL)
    #define `$INSTANCE_NAME`_SW_REFGEN_SEL_PTR                  ( (reg32 *) CYREG_CSD_SW_REFGEN_SEL)

    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_REG                   (*(reg32 *) CYREG_CSD_SW_CMP_N_SEL)
    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_PTR                   ( (reg32 *) CYREG_CSD_SW_CMP_N_SEL)

    #define `$INSTANCE_NAME`_SW_RES_REG                         (*(reg32 *) CYREG_CSD_SW_RES)
    #define `$INSTANCE_NAME`_SW_RES_PTR                         ( (reg32 *) CYREG_CSD_SW_RES)

    #define `$INSTANCE_NAME`_SW_HS_P_SEL_REG                    (*(reg32 *) CYREG_CSD_SW_HS_P_SEL)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_PTR                    ( (reg32 *) CYREG_CSD_SW_HS_P_SEL)

    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_REG                  (*(reg32 *) CYREG_CSD_SW_SHIELD_SEL)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_PTR                  ( (reg32 *) CYREG_CSD_SW_SHIELD_SEL)

    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_REG                 (*(reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR                 ( (reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)

    #define `$INSTANCE_NAME`_SW_HS_N_SEL_REG                    (*(reg32 *) CYREG_CSD_SW_HS_N_SEL)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_PTR                    ( (reg32 *) CYREG_CSD_SW_HS_N_SEL)

    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_REG                  (*(reg32 *) CYREG_CSD_SW_FW_MOD_SEL)
    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR                  ( (reg32 *) CYREG_CSD_SW_FW_MOD_SEL)

    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_REG                 (*(reg32 *) CYREG_CSD_SW_FW_TANK_SEL)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR                 ( (reg32 *) CYREG_CSD_SW_FW_TANK_SEL)

    #define `$INSTANCE_NAME`_SW_DSI_SEL_REG                     (*(reg32 *) CYREG_CSD_SW_DSI_SEL)
    #define `$INSTANCE_NAME`_SW_DSI_SEL_PTR                     ( (reg32 *) CYREG_CSD_SW_DSI_SEL)

    #define `$INSTANCE_NAME`_ADC_CTL_REG                        (*(reg32 *) CYREG_CSD_ADC_CTL)
    #define `$INSTANCE_NAME`_ADC_CTL_PTR                        ( (reg32 *) CYREG_CSD_ADC_CTL)
#else

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
        /* CSD0 block registers   */
        #define `$INSTANCE_NAME`_CONFIG_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_CONFIG)
        #define `$INSTANCE_NAME`_CONFIG_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_CONFIG)
        #define `$INSTANCE_NAME`_IDAC_CONTR_REG                 (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CONTROL)
        #define `$INSTANCE_NAME`_IDAC_CONTR_PTR                 ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CONTROL)
        #define `$INSTANCE_NAME`_IDAC_REG                       (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_IDAC)
        #define `$INSTANCE_NAME`_IDAC_PTR                       ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_IDAC)
        #define `$INSTANCE_NAME`_COUNTER_REG                    (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_COUNTER)
        #define `$INSTANCE_NAME`_COUNTER_PTR                    ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_COUNTER)
        #define `$INSTANCE_NAME`_STATUS_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_STATUS)
        #define `$INSTANCE_NAME`_STATUS_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_STATUS)
        #define `$INSTANCE_NAME`_INTR_REG                       (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR)
        #define `$INSTANCE_NAME`_INTR_PTR                       ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR)
        #define `$INSTANCE_NAME`_INTR_SET_REG                   (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR_SET)
        #define `$INSTANCE_NAME`_INTR_SET_PTR                   ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR_SET)
        #define `$INSTANCE_NAME`_PWM_REG                        (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_PWM)
        #define `$INSTANCE_NAME`_PWM_PTR                        ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_PWM)
        #define `$INSTANCE_NAME`_TRIM1_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM1)
        #define `$INSTANCE_NAME`_TRIM1_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM1)
        #define `$INSTANCE_NAME`_TRIM2_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM2)
        #define `$INSTANCE_NAME`_TRIM2_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM2)
    #else
        /* CSD block registers   */
        #define `$INSTANCE_NAME`_CONFIG_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD__CSD_CONFIG)
        #define `$INSTANCE_NAME`_CONFIG_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD__CSD_CONFIG)
        #define `$INSTANCE_NAME`_IDAC_CONTR_REG                 (*(reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CONTROL)
        #define `$INSTANCE_NAME`_IDAC_CONTR_PTR                 ( (reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CONTROL)
        #define `$INSTANCE_NAME`_IDAC_REG                       (*(reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CSD_IDAC)
        #define `$INSTANCE_NAME`_IDAC_PTR                       ( (reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CSD_IDAC)
        #define `$INSTANCE_NAME`_COUNTER_REG                    (*(reg32 *) `$INSTANCE_NAME`_CSD__CSD_COUNTER)
        #define `$INSTANCE_NAME`_COUNTER_PTR                    ( (reg32 *) `$INSTANCE_NAME`_CSD__CSD_COUNTER)
        #define `$INSTANCE_NAME`_STATUS_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD__CSD_STATUS)
        #define `$INSTANCE_NAME`_STATUS_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD__CSD_STATUS)
        #define `$INSTANCE_NAME`_INTR_REG                       (*(reg32 *) `$INSTANCE_NAME`_CSD__CSD_INTR)
        #define `$INSTANCE_NAME`_INTR_PTR                       ( (reg32 *) `$INSTANCE_NAME`_CSD__CSD_INTR)
        #define `$INSTANCE_NAME`_INTR_SET_REG                   (*(reg32 *) CYREG_CSD_INTR_SET)
        #define `$INSTANCE_NAME`_INTR_SET_PTR                   ( (reg32 *) CYREG_CSD_INTR_SET)
        #define `$INSTANCE_NAME`_PWM_REG                        (*(reg32 *) CYREG_CSD_PWM)
        #define `$INSTANCE_NAME`_PWM_PTR                        ( (reg32 *) CYREG_CSD_PWM)
        #define `$INSTANCE_NAME`_TRIM1_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CSD_TRIM1)
        #define `$INSTANCE_NAME`_TRIM1_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CSD_TRIM1)
        #define `$INSTANCE_NAME`_TRIM2_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CSD_TRIM2)
        #define `$INSTANCE_NAME`_TRIM2_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod_cy_psoc4_idac__CSD_TRIM2)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN)
        #if (CY_PSOC4_4100M || CY_PSOC4_4200M || CY_PSOC4_4200L)
            #if (1u != `$INSTANCE_NAME`_CSD__CSD_NUMBER)
                #define `$INSTANCE_NAME`_SFLASH_TRIM1_REG           (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
                #define `$INSTANCE_NAME`_SFLASH_TRIM1_PTR           ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

                #define `$INSTANCE_NAME`_SFLASH_TRIM2_REG           (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
                #define `$INSTANCE_NAME`_SFLASH_TRIM2_PTR           ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
            #else
                #define `$INSTANCE_NAME`_SFLASH_TRIM1_REG           (*(reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)
                #define `$INSTANCE_NAME`_SFLASH_TRIM1_PTR           ( (reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)

                #define `$INSTANCE_NAME`_SFLASH_TRIM2_REG           (*(reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
                #define `$INSTANCE_NAME`_SFLASH_TRIM2_PTR           ( (reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
            #endif /* (1u != `$INSTANCE_NAME`_CSD__CSD_NUMBER) */
        #else
            #define `$INSTANCE_NAME`_SFLASH_TRIM1_REG               (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
            #define `$INSTANCE_NAME`_SFLASH_TRIM1_PTR               ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

            #define `$INSTANCE_NAME`_SFLASH_TRIM2_REG               (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
            #define `$INSTANCE_NAME`_SFLASH_TRIM2_PTR               ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
        #endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M || CY_PSOC4_4200L) */
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

/* CSDv1 and CSDv2 PERI CLOCK registers */
#if defined(CYIPBLOCK_m0s8peri_VERSION)
    #define `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK                  (1u)
    #define `$INSTANCE_NAME`_M0S8PERI_BLOCK_VER                 ((CYIPBLOCK_m0s8peri_VERSION))
#else
    #define `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK                  (0u)
    #define `$INSTANCE_NAME`_M0S8PERI_BLOCK_VER                 (0u)
#endif /* (CYIPBLOCK_m0s8peri_VERSION) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
    #define `$INSTANCE_NAME`_MODCLK_DIV_REG                     (*(reg32 *)`$INSTANCE_NAME`_ModClk__DIV_REGISTER)
    #define `$INSTANCE_NAME`_MODCLK_DIV_PTR                     ( (reg32 *)`$INSTANCE_NAME`_ModClk__DIV_REGISTER)
    #define `$INSTANCE_NAME`_MODCLK_CMD_REG                     (*(reg32 *)CYREG_PERI_DIV_CMD)
    #define `$INSTANCE_NAME`_MODCLK_CMD_PTR                     ( (reg32 *)CYREG_PERI_DIV_CMD)
    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
        #define `$INSTANCE_NAME`_SNSCLK_DIV_REG                 (*(reg32 *)`$INSTANCE_NAME`_SnsClk__DIV_REGISTER)
        #define `$INSTANCE_NAME`_SNSCLK_DIV_PTR                 ( (reg32 *)`$INSTANCE_NAME`_SnsClk__DIV_REGISTER)
        #define `$INSTANCE_NAME`_SNSCLK_CMD_REG                 (*(reg32 *)CYREG_PERI_DIV_CMD)
        #define `$INSTANCE_NAME`_SNSCLK_CMD_PTR                 ( (reg32 *)CYREG_PERI_DIV_CMD)
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */
#else
    #define `$INSTANCE_NAME`_MODCLK_DIV_REG                     (*(reg32 *)`$INSTANCE_NAME`_ModClk__REGISTER)
    #define `$INSTANCE_NAME`_MODCLK_DIV_PTR                     ( (reg32 *)`$INSTANCE_NAME`_ModClk__REGISTER)
    #define `$INSTANCE_NAME`_SNSCLK_DIV_REG                     (*(reg32 *)`$INSTANCE_NAME`_SnsClk__REGISTER)
    #define `$INSTANCE_NAME`_SNSCLK_DIV_PTR                     ( (reg32 *)`$INSTANCE_NAME`_SnsClk__REGISTER)
    #define `$INSTANCE_NAME`_MODCLK_CMD_REG                     (`$INSTANCE_NAME`_MODCLK_DIV_REG)
    #define `$INSTANCE_NAME`_MODCLK_CMD_PTR                     (`$INSTANCE_NAME`_MODCLK_DIV_PTR)
    #define `$INSTANCE_NAME`_SNSCLK_CMD_REG                     (`$INSTANCE_NAME`_SNSCLK_DIV_REG)
    #define `$INSTANCE_NAME`_SNSCLK_CMD_PTR                     (`$INSTANCE_NAME`_SNSCLK_DIV_PTR)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

/****************************************************************************
* m0s8csd, m0s8peri, hsiom, and IO hardware-related registers masks
****************************************************************************/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

    #if(0u != `$INSTANCE_NAME`_CSX_EN)
        #define `$INSTANCE_NAME`_CMOD_CONNECTION                (`$INSTANCE_NAME`_CSD__CSHIELD_PAD)
    #else
        #define `$INSTANCE_NAME`_CMOD_CONNECTION                (`$INSTANCE_NAME`_CSD__DEDICATED_IO0)
    #endif /* (`$INSTANCE_NAME`_CSX_EN == 1u) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        #define `$INSTANCE_NAME`_CTANK_CONNECTION           (`$INSTANCE_NAME`_CSD__DEDICATED_IO1)
    #else
        #define `$INSTANCE_NAME`_CTANK_CONNECTION               (0u)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

    /* CSDv2 masks for the resistance or low EMI (slow ramp)  */
    #define `$INSTANCE_NAME`_RES_LOW                            (0u)
    #define `$INSTANCE_NAME`_RES_MED                            (1u)
    #define `$INSTANCE_NAME`_RES_HIGH                           (2u)
    #define `$INSTANCE_NAME`_RES_LOWEMI                         (3u)

    /* CSDv2 masks for the waveforms for corresponding switch  */
    #define `$INSTANCE_NAME`_STATIC_OPEN                        (0x00000000Lu)
    #define `$INSTANCE_NAME`_STATIC_CLOSE                       (0x00000001Lu)
    #define `$INSTANCE_NAME`_PHI1                               (0x00000002Lu)
    #define `$INSTANCE_NAME`_PHI2                               (0x00000003Lu)
    #define `$INSTANCE_NAME`_PHI1_HSCMP                         (0x00000004Lu)
    #define `$INSTANCE_NAME`_PHI2_HSCMP                         (0x00000005Lu)
    #define `$INSTANCE_NAME`_HSCMP                              (0x00000006Lu)

    #define `$INSTANCE_NAME`_SW_DSI_CMOD                        (1uL << 4u)
    #define `$INSTANCE_NAME`_SW_DSI_CTANK                       (1uL << 0u)

    /* CSDv2 CSD_CONFIG register masks    */
    #define `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_MASK           (((0x00000001Lu << CYFLD_CSD_FILTER_DELAY__SIZE) - 1u) << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_2_CYCLES       (0x00000002Lu)
    #define `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_3_CYCLES       (0x00000003Lu)
    #define `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_4_CYCLES       (0x00000004Lu)
    #define `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ          (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_2_CYCLES << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_24MHZ          (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_3_CYCLES << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_48MHZ          (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_4_CYCLES << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_SHIELD_DELAY_MASK           (((0x00000001Lu << CYFLD_CSD_SHIELD_DELAY__SIZE) - 1u) << CYFLD_CSD_SHIELD_DELAY__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK               (((0x00000001Lu << CYFLD_CSD_SENSE_EN__SIZE) - 1u) << CYFLD_CSD_SENSE_EN__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_CHARGE_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_CHARGE_MODE__SIZE) - 1u) << CYFLD_CSD_CHARGE_MODE__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_MUTUAL_CAP_MASK             (((0x00000001Lu << CYFLD_CSD_MUTUAL_CAP__SIZE) - 1u) << CYFLD_CSD_MUTUAL_CAP__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_CSX_DUAL_CNT_MASK           (((0x00000001Lu << CYFLD_CSD_CSX_DUAL_CNT__SIZE) - 1u) << CYFLD_CSD_CSX_DUAL_CNT__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_DSI_COUNT_SEL_MASK          (((0x00000001Lu << CYFLD_CSD_DSI_COUNT_SEL__SIZE) - 1u) << CYFLD_CSD_DSI_COUNT_SEL__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_DSI_SAMPLE_EN_MASK          (((0x00000001Lu << CYFLD_CSD_DSI_SAMPLE_EN__SIZE) - 1u) << CYFLD_CSD_DSI_SAMPLE_EN__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_SAMPLE_SYNC_MASK            (((0x00000001Lu << CYFLD_CSD_SAMPLE_SYNC__SIZE) - 1u) << CYFLD_CSD_SAMPLE_SYNC__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_DSI_SENSE_EN_MASK           (((0x00000001Lu << CYFLD_CSD_DSI_SENSE_EN__SIZE) - 1u) << CYFLD_CSD_DSI_SENSE_EN__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_LP_MODE_MASK                (((0x00000001Lu << CYFLD_CSD_LP_MODE__SIZE) - 1u) << CYFLD_CSD_LP_MODE__OFFSET)
    #define `$INSTANCE_NAME`_CONFIG_ENABLE_MASK                 (((0x00000001Lu << CYFLD_CSD_ENABLE__SIZE) - 1u) << CYFLD_CSD_ENABLE__OFFSET)

    /* CSDv2 CSD_STATUS register masks    */
    #define `$INSTANCE_NAME`_STATUS_CSD_CHARGE_MASK             (((0x00000001Lu << CYFLD_CSD_CSD_CHARGE__SIZE) - 1u) << CYFLD_CSD_CSD_CHARGE__OFFSET)
    #define `$INSTANCE_NAME`_STATUS_CSD_SENSE_MASK              (((0x00000001Lu << CYFLD_CSD_CSD_SENSE__SIZE) - 1u) << CYFLD_CSD_CSD_SENSE__OFFSET)
    #define `$INSTANCE_NAME`_STATUS_HSCMP_OUT_MASK              (((0x00000001Lu << CYFLD_CSD_HSCMP_OUT__SIZE) - 1u) << CYFLD_CSD_HSCMP_OUT__OFFSET)
    #define `$INSTANCE_NAME`_STATUS_CSDCMP_OUT_MASK             (((0x00000001Lu << CYFLD_CSD_CSDCMP_OUT__SIZE) - 1u) << CYFLD_CSD_CSDCMP_OUT__OFFSET)

    /* CSDv2 STAT_SEQ register masks    */
    #define `$INSTANCE_NAME`_STAT_SEQ_SEQ_STATE_MASK            (((0x00000001Lu << CYFLD_CSD_SEQ_STATE__SIZE) - 1u) << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define `$INSTANCE_NAME`_STAT_SEQ_ADC_STATE_MASK            (((0x00000001Lu << CYFLD_CSD_ADC_STATE__SIZE) - 1u) << CYFLD_CSD_ADC_STATE__OFFSET)

    /* CSDv2 sequencer state codes */
    #define `$INSTANCE_NAME`_STAT_SEQ_IDLE                      (0x00000000Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define `$INSTANCE_NAME`_STAT_SEQ_INIT_COARSE               (0x00000001Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define `$INSTANCE_NAME`_STAT_SEQ_AUTO_ZERO_0               (0x00000002Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define `$INSTANCE_NAME`_STAT_SEQ_SAMPLE_INIT               (0x00000003Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define `$INSTANCE_NAME`_STAT_SEQ_AUTO_ZERO_1               (0x00000004Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define `$INSTANCE_NAME`_STAT_SEQ_SAMPLE_NORM               (0x00000005Lu << CYFLD_CSD_SEQ_STATE__OFFSET)


    /* CSDv2 STAT_CNTS register masks    */
    #define `$INSTANCE_NAME`_STAT_CNTS_NUM_CONV_MASK            (((0x00000001Lu << CYFLD_CSD_NUM_CONV__SIZE) - 1u) << CYFLD_CSD_NUM_CONV__OFFSET)

    /* CSDv2 RESULT_VAL1 register masks    */
    #define `$INSTANCE_NAME`_RESULT_VAL1_VALUE_MASK             (((0x00000001Lu << CYFLD_CSD_VALUE__SIZE) - 1u) << CYFLD_CSD_VALUE__OFFSET)
    #define `$INSTANCE_NAME`_RESULT_VAL1_BAD_CONVS_MASK         (((0x00000001Lu << CYFLD_CSD_BAD_CONVS__SIZE) - 1u) << CYFLD_CSD_BAD_CONVS__OFFSET)

    /* CSDv2 RESULT_VAL2 register masks    */
    #define `$INSTANCE_NAME`_RESULT_VAL2_VALUE_MASK             (0x0000FFFFLu)

    /* CSDv2 INTR register masks    */
    #define `$INSTANCE_NAME`_INTR_SAMPLE_MASK                   (((0x00000001Lu << CYFLD_CSD_SAMPLE__SIZE) - 1u) << CYFLD_CSD_SAMPLE__OFFSET)
    #define `$INSTANCE_NAME`_INTR_INIT_MASK                     (((0x00000001Lu << CYFLD_CSD_INIT__SIZE) - 1u) << CYFLD_CSD_INIT__OFFSET)
    #define `$INSTANCE_NAME`_INTR_ADC_RES_MASK                  (((0x00000001Lu << CYFLD_CSD_ADC_RES__SIZE) - 1u) << CYFLD_CSD_ADC_RES__OFFSET)

    /* CSDv2 INTR_SET register masks    */
    #define `$INSTANCE_NAME`_INTR_SET_SAMPLE_MASK               (`$INSTANCE_NAME`_INTR_SAMPLE_MASK)
    #define `$INSTANCE_NAME`_INTR_SET_INIT_MASK                 (`$INSTANCE_NAME`_INTR_INIT_MASK)
    #define `$INSTANCE_NAME`_INTR_SET_ADC_RES_MASK              (`$INSTANCE_NAME`_INTR_ADC_RES_MASK)
    #define `$INSTANCE_NAME`_INTR_SET_MASK                      (`$INSTANCE_NAME`_INTR_SET_SAMPLE_MASK | \
                                                                 `$INSTANCE_NAME`_INTR_SET_INIT_MASK | \
                                                                 `$INSTANCE_NAME`_INTR_SET_ADC_RES_MASK)

    /* CSDv2 INTR_MASK register masks    */
    #define `$INSTANCE_NAME`_INTR_MASK_SAMPLE_MASK              (`$INSTANCE_NAME`_INTR_SAMPLE_MASK)
    #define `$INSTANCE_NAME`_INTR_MASK_INIT_MASK                (`$INSTANCE_NAME`_INTR_INIT_MASK)
    #define `$INSTANCE_NAME`_INTR_MASK_ADC_RES_MASK             (`$INSTANCE_NAME`_INTR_ADC_RES_MASK)


    /* CSDv2 HSCMP v2 register masks    */
    #define `$INSTANCE_NAME`_HSCMP_EN_MASK                      (((0x00000001Lu << CYFLD_CSD_HSCMP_EN__SIZE) - 1u) << CYFLD_CSD_HSCMP_EN__OFFSET)
    #define `$INSTANCE_NAME`_HSCMP_INVERT_MASK                  (((0x00000001Lu << CYFLD_CSD_HSCMP_INVERT__SIZE) - 1u) << CYFLD_CSD_HSCMP_INVERT__OFFSET)
    #define `$INSTANCE_NAME`_CSD_AZ_EN_MASK                     (((0x00000001Lu << CYFLD_CSD_AZ_EN__SIZE) - 1u) << CYFLD_CSD_AZ_EN__OFFSET)

    /* CSDv2 AMBUF v2 register masks    */
    #define `$INSTANCE_NAME`_AMBUF_AMBUF_EN_MASK                ((0x00000001Lu << CYFLD_CSD_PWR_MODE__SIZE) - 1u)
    #define `$INSTANCE_NAME`_AMBUF_PWR_MODE_OFF                 (CYVAL_CSD_PWR_MODE_OFF)
    #define `$INSTANCE_NAME`_AMBUF_PWR_MODE_NORM                (CYVAL_CSD_PWR_MODE_NORM)
    #define `$INSTANCE_NAME`_AMBUF_PWR_MODE_HI                  (CYVAL_CSD_PWR_MODE_HI)

    /* CSDv2 REFGEN v2 register masks    */
    #define `$INSTANCE_NAME`_REFGEN_REFGEN_EN_MASK              ((0x00000001Lu << CYFLD_CSD_REFGEN_EN__SIZE) - 1u)
    #define `$INSTANCE_NAME`_REFGEN_BYPASS_MASK                 (((0x00000001Lu << CYFLD_CSD_BYPASS__SIZE) - 1u) << CYFLD_CSD_BYPASS__OFFSET)
    #define `$INSTANCE_NAME`_REFGEN_VDDA_EN_MASK                (((0x00000001Lu << CYFLD_CSD_VDDA_EN__SIZE) - 1u) << CYFLD_CSD_VDDA_EN__OFFSET)
    #define `$INSTANCE_NAME`_REFGEN_RES_EN_MASK                 (((0x00000001Lu << CYFLD_CSD_RES_EN__SIZE) - 1u) << CYFLD_CSD_RES_EN__OFFSET)
    #define `$INSTANCE_NAME`_REFGEN_GAIN_MASK                   (((0x00000001Lu << CYFLD_CSD_GAIN__SIZE) - 1u) << CYFLD_CSD_GAIN__OFFSET)
    #define `$INSTANCE_NAME`_REFGEN_VREFLO_SEL_MASK             (((0x00000001Lu << CYFLD_CSD_VREFLO_SEL__SIZE) - 1u) << CYFLD_CSD_VREFLO_SEL__OFFSET)
    #define `$INSTANCE_NAME`_REFGEN_VREFLO_INT_MASK             (((0x00000001Lu << CYFLD_CSD_VREFLO_INT__SIZE) - 1u) << CYFLD_CSD_VREFLO_INT__OFFSET)

    /* CSDv2 IDACA v2 register masks  */
    #define `$INSTANCE_NAME`_IDAC_MOD_VAL_MASK                  (((0x00000001Lu << CYFLD_CSD_VAL__SIZE) - 1u) << CYFLD_CSD_VAL__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_POLARITY_MASK             (((0x00000001Lu << CYFLD_CSD_POLARITY__SIZE) - 1u) << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_POLARITY_VSSA_SRC         ((uint32)CYVAL_CSD_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_POLARITY_VDDA_SNK         ((uint32)CYVAL_CSD_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_POLARITY_SENSE            ((uint32)CYVAL_CSD_POLARITY_SENSE << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_POLARITY_SENSE_INV        ((uint32)CYVAL_CSD_POLARITY_SENSE_INV << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_POL_DYN_MASK              (((0x00000001Lu << CYFLD_CSD_POL_DYN__SIZE) - 1u) << CYFLD_CSD_POL_DYN__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG1_MODE__SIZE) - 1u) << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG1_MODE_GP_STATIC)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG1_MODE_GP << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_CSD_STATIC_MASK ((uint32)CYVAL_CSD_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_CSD_MASK        (0x00000003Lu << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG2_MODE__SIZE) - 1u) << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG2_MODE_GP_STATIC)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG2_MODE_GP << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_CSD_STATIC_MASK (0x00000002Lu << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_CSD_MASK        ((uint32)CYVAL_CSD_LEG2_MODE_CSD << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_MOD_BAL_MODE_PHI1             ((uint32)CYVAL_CSD_BAL_MODE_PHI1 << CYFLD_CSD_BAL_MODE__OFFSET)

    #define `$INSTANCE_NAME`_IDAC_MOD_DSI_CTRL_EN_MASK          (0x00200000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK                (0x00C00000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_LO_MASK        (0x00000000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_MED_MASK       (0x00400000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_HI_MASK        (0x00800000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG1_EN_MASK              (0x01000000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_LEG2_EN_MASK              (0x02000000Lu)

    /* CSDv2 IDACB v2 register masks  */
    #define `$INSTANCE_NAME`_IDAC_COMP_VAL_MASK                  (((0x00000001Lu << CYFLD_CSD_VAL__SIZE) - 1u) << CYFLD_CSD_VAL__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_POLARITY_MASK             (((0x00000001Lu << CYFLD_CSD_POLARITY__SIZE) - 1u) << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_POLARITY_VSSA_SRC         ((uint32)CYVAL_CSD_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_POLARITY_VDDA_SNK         ((uint32)CYVAL_CSD_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_POLARITY_SENSE            ((uint32)CYVAL_CSD_POLARITY_SENSE << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_POLARITY_SENSE_INV        ((uint32)CYVAL_CSD_POLARITY_SENSE_INV << CYFLD_CSD_POLARITY__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_POL_DYN_MASK              (((0x00000001Lu << CYFLD_CSD_POL_DYN__SIZE) - 1u) << CYFLD_CSD_POL_DYN__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG1_MODE__SIZE) - 1u) << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG1_MODE_GP_STATIC)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG1_MODE_GP << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_CSD_STATIC_MASK ((uint32)CYVAL_CSD_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_CSD_MASK        (0x00000003Lu << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG2_MODE__SIZE) - 1u) << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG2_MODE_GP_STATIC)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG2_MODE_GP << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_CSD_STATIC_MASK (0x00000002Lu << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_CSD_MASK        ((uint32)CYVAL_CSD_LEG2_MODE_CSD << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define `$INSTANCE_NAME`_IDAC_COMP_DSI_CTRL_EN_MASK          (0x00200000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_RANGE_MASK                (0x00C00000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_RANGE_IDAC_LO_MASK        (0x00000000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_RANGE_IDAC_MED_MASK       (0x00400000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_RANGE_IDAC_HI_MASK        (0x00800000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG1_EN_MASK              (0x01000000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_LEG2_EN_MASK              (0x02000000Lu)

    /* CSDv2 SENSE_PERIOD register masks  */
    #define `$INSTANCE_NAME`_SENSE_PERIOD_SENSE_DIV_MASK        (((0x00000001Lu << CYFLD_CSD_SENSE_DIV__SIZE) - 1u) << CYFLD_CSD_SENSE_DIV__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_PERIOD_LFSR_SIZE_MASK        (((0x00000001Lu << CYFLD_CSD_LFSR_SIZE__SIZE) - 1u) << CYFLD_CSD_LFSR_SIZE__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_PERIOD_LFSR_SCALE_MASK       (((0x00000001Lu << CYFLD_CSD_LFSR_SCALE__SIZE) - 1u) << CYFLD_CSD_LFSR_SCALE__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_PERIOD_LFSR_CLEAR_MASK       (((0x00000001Lu << CYFLD_CSD_LFSR_CLEAR__SIZE) - 1u) << CYFLD_CSD_LFSR_CLEAR__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_PERIOD_SEL_LFSR_MSB_MASK     (((0x00000001Lu << CYFLD_CSD_SEL_LFSR_MSB__SIZE) - 1u) << CYFLD_CSD_SEL_LFSR_MSB__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_6MHZ                         (6u)
    #define `$INSTANCE_NAME`_SENSE_PERIOD_SENSE_DIV_6MHZ        (CYDEV_BCLK__HFCLK__KHZ/`$INSTANCE_NAME`_CSD_SCANSPEED_DIVIDER/`$INSTANCE_NAME`_SENSE_6MHZ)

    /* CSDv2 SW_BYP_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYA_MASK             (((0x00000001Lu << CYFLD_CSD_SW_BYA__SIZE) - 1u) << CYFLD_CSD_SW_BYA__OFFSET)
    #define `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYB_MASK             (((0x00000001Lu << CYFLD_CSD_SW_BYB__SIZE) - 1u) << CYFLD_CSD_SW_BYB__OFFSET)
    #define `$INSTANCE_NAME`_SW_BYP_SEL_SW_CBCC_MASK            (((0x00000001Lu << CYFLD_CSD_SW_CBCC__SIZE) - 1u) << CYFLD_CSD_SW_CBCC__OFFSET)

    /* CSDv2 SW_REFGEN_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_IAIB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IAIB__SIZE) - 1u) << CYFLD_CSD_SW_IAIB__OFFSET)
    #define `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_IBCB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IBCB__SIZE) - 1u) << CYFLD_CSD_SW_IBCB__OFFSET)
    #define `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGMB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_SGMB__SIZE) - 1u) << CYFLD_CSD_SW_SGMB__OFFSET)
    #define `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGRE_MASK         (((0x00000001Lu << CYFLD_CSD_SW_SGRE__SIZE) - 1u) << CYFLD_CSD_SW_SGRE__OFFSET)
    #define `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SGR__SIZE) - 1u) << CYFLD_CSD_SW_SGR__OFFSET)

    /* CSDv2 SW_CMP_N_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRH_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SCRH__SIZE) - 1u) << CYFLD_CSD_SW_SCRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRH_STATIC_OPEN   (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_SCRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE  (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_SCRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRL_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SCRL__SIZE) - 1u) << CYFLD_CSD_SW_SCRL__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRL_STATIC_OPEN   (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_SCRL__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRL_STATIC_CLOSE  (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_SCRL__OFFSET)

    /* CSDv2 SEQ_TIME register masks  */
    #define `$INSTANCE_NAME`_SEQ_TIME_AZ_TIME_MASK              (((0x00000001Lu << CYFLD_CSD_AZ_TIME__SIZE) - 1u) << CYFLD_CSD_AZ_TIME__OFFSET)

    /* CSDv2 SEQ_INIT_CNT register masks  */
    #define `$INSTANCE_NAME`_SEQ_INIT_CNT_CONV_CNT_MASK         (((0x00000001Lu << CYFLD_CSD_CONV_CNT__SIZE) - 1u) << CYFLD_CSD_CONV_CNT__OFFSET)

    /* CSDv2 SEQ_NORM_CNT register masks  */
    #define `$INSTANCE_NAME`_SEQ_NORM_CNT_CONV_CNT_MASK         (((0x00000001Lu << CYFLD_CSD_CONV_CNT__SIZE) - 1u) << CYFLD_CSD_CONV_CNT__OFFSET)

    /* CSDv2 SW_RES register masks  */
    #define `$INSTANCE_NAME`_SW_RES_RES_HCAV_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCAV__SIZE) - 1u) << CYFLD_CSD_RES_HCAV__OFFSET)
    #define `$INSTANCE_NAME`_SW_RES_RES_HCAG_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCAG__SIZE) - 1u) << CYFLD_CSD_RES_HCAG__OFFSET)
    #define `$INSTANCE_NAME`_SW_RES_RES_HCBV_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCBV__SIZE) - 1u) << CYFLD_CSD_RES_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_RES_RES_HCBG_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCBG__SIZE) - 1u) << CYFLD_CSD_RES_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_RES_RES_F1PM_MASK               (((0x00000001Lu << CYFLD_CSD_RES_F1PM__SIZE) - 1u) << CYFLD_CSD_RES_F1PM__OFFSET)
    #define `$INSTANCE_NAME`_SW_RES_RES_F2PT_MASK               (((0x00000001Lu << CYFLD_CSD_RES_F2PT__SIZE) - 1u) << CYFLD_CSD_RES_F2PT__OFFSET)

    #define `$INSTANCE_NAME`_SW_RES_RES_DEFAULT                 ((`$INSTANCE_NAME`_CSD_INIT_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET) | \
                                                                 (`$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET))

    /* CSDv2 SW_HS_P_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMPM__SIZE) - 1u) << CYFLD_CSD_SW_HMPM__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_OPEN    (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HMPM__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE   (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_HMPM__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMPT__SIZE) - 1u) << CYFLD_CSD_SW_HMPT__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_OPEN    (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HMPT__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE   (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_HMPT__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMPS__SIZE) - 1u) << CYFLD_CSD_SW_HMPS__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_OPEN    (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HMPS__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE   (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_HMPS__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMA_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMMA__SIZE) - 1u) << CYFLD_CSD_SW_HMMA__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMA_STATIC_OPEN    (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HMMA__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE   (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_HMMA__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMMB__SIZE) - 1u) << CYFLD_CSD_SW_HMMB__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_OPEN    (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HMMB__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE   (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_HMMB__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMCA_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMCA__SIZE) - 1u) << CYFLD_CSD_SW_HMCA__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMCB_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMCB__SIZE) - 1u) << CYFLD_CSD_SW_HMCB__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMRH_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMRH__SIZE) - 1u) << CYFLD_CSD_SW_HMRH__OFFSET)

    /* CSDv2 SW_SHIELD_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCAV_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCAV__SIZE) - 1u) << CYFLD_CSD_SW_HCAV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCAV_STATIC_OPEN  (`$INSTANCE_NAME`_STATIC_OPEN)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCAV_HSCMP        (`$INSTANCE_NAME`_HSCMP)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCAG_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCAG__SIZE) - 1u) << CYFLD_CSD_SW_HCAG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCBV__SIZE) - 1u) << CYFLD_CSD_SW_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_HSCMP        (`$INSTANCE_NAME`_HSCMP << CYFLD_CSD_SW_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI1         (`$INSTANCE_NAME`_PHI1 << CYFLD_CSD_SW_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI2         (`$INSTANCE_NAME`_PHI2 << CYFLD_CSD_SW_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI1_HSCMP   (`$INSTANCE_NAME`_PHI1_HSCMP << CYFLD_CSD_SW_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP   (`$INSTANCE_NAME`_PHI2_HSCMP << CYFLD_CSD_SW_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN  (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HCBV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCBG__SIZE) - 1u) << CYFLD_CSD_SW_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_HSCMP        (`$INSTANCE_NAME`_HSCMP << CYFLD_CSD_SW_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI1         (`$INSTANCE_NAME`_PHI1 << CYFLD_CSD_SW_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI2         (`$INSTANCE_NAME`_PHI2 << CYFLD_CSD_SW_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI1_HSCMP   (`$INSTANCE_NAME`_PHI1_HSCMP << CYFLD_CSD_SW_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP   (`$INSTANCE_NAME`_PHI2_HSCMP << CYFLD_CSD_SW_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN  (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HCBG__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCCV_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCCV__SIZE) - 1u) << CYFLD_CSD_SW_HCCV__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCCG_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCCG__SIZE) - 1u) << CYFLD_CSD_SW_HCCG__OFFSET)

    /* CSDv2 SEQ_START register masks  */
    #define `$INSTANCE_NAME`_SEQ_START_START_MASK               (((0x00000001Lu << CYFLD_CSD_START__SIZE) - 1u) << CYFLD_CSD_START__OFFSET)
    #define `$INSTANCE_NAME`_SEQ_START_SEQ_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_SEQ_MODE__SIZE) - 1u) << CYFLD_CSD_SEQ_MODE__OFFSET)
    #define `$INSTANCE_NAME`_SEQ_START_ABORT_MASK               (((0x00000001Lu << CYFLD_CSD_ABORT__SIZE) - 1u) << CYFLD_CSD_ABORT__OFFSET)
    #define `$INSTANCE_NAME`_SEQ_START_DSI_START_EN_MASK        (((0x00000001Lu << CYFLD_CSD_DSI_START_EN__SIZE) - 1u) << CYFLD_CSD_DSI_START_EN__OFFSET)
    #define `$INSTANCE_NAME`_SEQ_START_AZ0_SKIP_MASK            (((0x00000001Lu << CYFLD_CSD_AZ0_SKIP__SIZE) - 1u) << CYFLD_CSD_AZ0_SKIP__OFFSET)
    #define `$INSTANCE_NAME`_SEQ_START_AZ1_SKIP_MASK            (((0x00000001Lu << CYFLD_CSD_AZ1_SKIP__SIZE) - 1u) << CYFLD_CSD_AZ1_SKIP__OFFSET)

    /* CSDv2 SW_CMP_P_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPM_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFPM__SIZE) - 1u) << CYFLD_CSD_SW_SFPM__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPM_STATIC_OPEN   (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_SFPM__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE  (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_SFPM__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPT_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFPT__SIZE) - 1u) << CYFLD_CSD_SW_SFPT__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPT_STATIC_OPEN   (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_SFPT__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE  (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_SFPT__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPS_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFPS__SIZE) - 1u) << CYFLD_CSD_SW_SFPS__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPS_STATIC_OPEN   (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_SFPS__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE  (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_SFPS__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFMA_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFMA__SIZE) - 1u) << CYFLD_CSD_SW_SFMA__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFMB_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFMB__SIZE) - 1u) << CYFLD_CSD_SW_SFMB__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFCA_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFCA__SIZE) - 1u) << CYFLD_CSD_SW_SFCA__OFFSET)
    #define `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFCB_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFCB__SIZE) - 1u) << CYFLD_CSD_SW_SFCB__OFFSET)

    /* CSDv2 CSDCMP register masks    */
    #define `$INSTANCE_NAME`_CSDCMP_CSDCMP_EN_MASK              (((0x00000001Lu << CYFLD_CSD_CSDCMP_EN__SIZE) - 1u) << CYFLD_CSD_CSDCMP_EN__OFFSET)
    #define `$INSTANCE_NAME`_CSDCMP_POLARITY_SEL_MASK           (((0x00000001Lu << CYFLD_CSD_POLARITY_SEL__SIZE) - 1u) << CYFLD_CSD_POLARITY_SEL__OFFSET)
    #define `$INSTANCE_NAME`_CSDCMP_FEEDBACK_MODE_MASK          (((0x00000001Lu << CYFLD_CSD_FEEDBACK_MODE__SIZE) - 1u) << CYFLD_CSD_FEEDBACK_MODE__OFFSET)
    #define `$INSTANCE_NAME`_CSDCMP_AZ_EN_MASK                  (((0x00000001Lu << CYFLD_CSD_AZ_EN__SIZE) - 1u) << CYFLD_CSD_AZ_EN__OFFSET)

    /* CSDv2 SENSE_DUTY register masks  */
    #define `$INSTANCE_NAME`_SENSE_DUTY_SENSE_WIDTH_MASK        (((0x00000001Lu << CYFLD_CSD_SENSE_WIDTH__SIZE) - 1u) << CYFLD_CSD_SENSE_WIDTH__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_DUTY_SENSE_POL_MASK          (((0x00000001Lu << CYFLD_CSD_SENSE_POL__SIZE) - 1u) << CYFLD_CSD_SENSE_POL__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI1_MASK       (((0x00000001Lu << CYFLD_CSD_OVERLAP_PHI1__SIZE) - 1u) << CYFLD_CSD_OVERLAP_PHI1__OFFSET)
    #define `$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI2_MASK       (((0x00000001Lu << CYFLD_CSD_OVERLAP_PHI2__SIZE) - 1u) << CYFLD_CSD_OVERLAP_PHI2__OFFSET)

    /* CSDv2 SW_AMUXBUF_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRBY_MASK        (((0x00000001Lu << CYFLD_CSD_SW_IRBY__SIZE) - 1u) << CYFLD_CSD_SW_IRBY__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRLB_MASK        (((0x00000001Lu << CYFLD_CSD_SW_IRLB__SIZE) - 1u) << CYFLD_CSD_SW_IRLB__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRLB_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_IRLB__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICA_MASK         (((0x00000001Lu << CYFLD_CSD_SW_ICA__SIZE) - 1u) << CYFLD_CSD_SW_ICA__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_ICB__SIZE) - 1u) << CYFLD_CSD_SW_ICB__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICB_PHI2_HSCMP   (`$INSTANCE_NAME`_PHI2_HSCMP << CYFLD_CSD_SW_ICB__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRLI_MASK        (((0x00000001Lu << CYFLD_CSD_SW_IRLI__SIZE) - 1u) << CYFLD_CSD_SW_IRLI__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRH_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IRH__SIZE) - 1u) << CYFLD_CSD_SW_IRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_IRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRL_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IRL__SIZE) - 1u) << CYFLD_CSD_SW_IRL__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRL_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IRL__SIZE) - 1u) << CYFLD_CSD_SW_IRL__OFFSET)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_DEFAULT          (0x01030000Lu)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICB_PHI2         (0x00030000uL)
    #define `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICB_PHI1         (`$INSTANCE_NAME`_PHI1 << CYFLD_CSD_SW_ICB__OFFSET)

    /* CSDv2 SW_FW_TANK_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCCC_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCCC__SIZE) - 1u) << CYFLD_CSD_SW_HCCC__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCCD_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCCD__SIZE) - 1u) << CYFLD_CSD_SW_HCCD__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCRH__SIZE) - 1u) << CYFLD_CSD_SW_HCRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_OPEN    (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HCRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE   (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_HCRH__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRL_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCRL__SIZE) - 1u) << CYFLD_CSD_SW_HCRL__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRL_STATIC_OPEN    (`$INSTANCE_NAME`_STATIC_OPEN << CYFLD_CSD_SW_HCRL__OFFSET)
    #define `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRL_STATIC_CLOSE   (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_HCRL__OFFSET)

    /* CSDv2 SW_FW_MOD_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1PM_MASK         (((0x00000001Lu << CYFLD_CSD_SW_F1PM__SIZE) - 1u) << CYFLD_CSD_SW_F1PM__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_F1PM__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1MA_MASK         (((0x00000001Lu << CYFLD_CSD_SW_F1MA__SIZE) - 1u) << CYFLD_CSD_SW_F1MA__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_F1MA__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1CA_MASK         (((0x00000001Lu << CYFLD_CSD_SW_F1CA__SIZE) - 1u) << CYFLD_CSD_SW_F1CA__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_F1CA__OFFSET)

    /* CSDv2 SW_FW_TANK_SEL register masks  */
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2PT__SIZE) - 1u) << CYFLD_CSD_SW_F2PT__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_F2PT__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CB_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2CB__SIZE) - 1u) << CYFLD_CSD_SW_F2CB__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CB_PHI2        (`$INSTANCE_NAME`_PHI2 << CYFLD_CSD_SW_F2CB__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2MA_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2MA__SIZE) - 1u) << CYFLD_CSD_SW_F2MA__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_F2MA__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CA_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2CA__SIZE) - 1u) << CYFLD_CSD_SW_F2CA__OFFSET)
    #define `$INSTANCE_NAME`_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE (`$INSTANCE_NAME`_STATIC_CLOSE << CYFLD_CSD_SW_F2CA__OFFSET)

    /* Defining default CSDv2 configuration according to settings in customizer. */
    #define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG                 (`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_2_CYCLES | `$INSTANCE_NAME`_CONFIG_SAMPLE_SYNC_MASK)

    /* CSDv2 CTANK masks    */
    #define `$INSTANCE_NAME`_CTANK_DR_VDDIO                     (0x0u)
    #define `$INSTANCE_NAME`_CTANK_DR_VSSIO                     (`$INSTANCE_NAME`_DR_MASK << `$INSTANCE_NAME`_CSH_SHIFT)

    /* CSDv2 IDACs' masks */
    #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY      (`$INSTANCE_NAME`_IDAC_MOD_POLARITY_VDDA_SNK)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY     (`$INSTANCE_NAME`_IDAC_COMP_POLARITY_VDDA_SNK)
        #define `$INSTANCE_NAME`_CSH_DR_CONFIG                  (`$INSTANCE_NAME`_CTANK_DR_VSSIO)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY      (0x00000000Lu)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY     (0x00000000Lu)
        #define `$INSTANCE_NAME`_CSH_DR_CONFIG                  (`$INSTANCE_NAME`_CTANK_DR_VDDIO)
    #endif /*  (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)
            #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
                #define `$INSTANCE_NAME`_IDACB_USED             (1u)
            #else
                #define `$INSTANCE_NAME`_IDACB_USED             (0u)
            #endif /* (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_LEG2_MODE (`$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK)
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG1_MODE (`$INSTANCE_NAME`_IDAC_COMP_LEG1_EN_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_CSD_STATIC_MASK)
            #define `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL      (`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK |\
                                                                `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_IAIB_MASK)
        #else
            #define `$INSTANCE_NAME`_IDACB_USED                 (0u)
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_LEG2_MODE (`$INSTANCE_NAME`_IDAC_MOD_LEG2_EN_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_CSD_STATIC_MASK)
            #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG1_MODE (`$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK)
            #define `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL      (`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK)
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */
    #else
        #define `$INSTANCE_NAME`_IDACB_USED                     (0u)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_LEG2_MODE     (`$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG1_MODE    (`$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL          (`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_LEG1_MODE         (`$INSTANCE_NAME`_IDAC_MOD_LEG1_EN_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_MOD_LEG1_MODE_CSD_MASK)
    #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG2_MODE        (`$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_GP_STATIC_MASK)

    /* IDACs ranges */
    #if (`$INSTANCE_NAME`_IDAC_GAIN_LOW == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE         (`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_LO_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE        (`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_LO_MASK)
    #elif (`$INSTANCE_NAME`_IDAC_GAIN_MEDIUM == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE         (`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_MED_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE        (`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_MED_MASK)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE         (`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_HI_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE        (`$INSTANCE_NAME`_IDAC_MOD_RANGE_IDAC_HI_MASK)
    #endif /* (`$INSTANCE_NAME`_CSD_IDAC_GAIN == `$INSTANCE_NAME`_IDAC_RANGE_8X) */

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD                   (`$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_LEG1_MODE |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_LEG2_MODE)

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP                  (`$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG1_MODE |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_LEG2_MODE)

    #define `$INSTANCE_NAME`_CALIBRATE_IDAC_MOD                 (`$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_POLARITY |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_LEG1_MODE |\
                                                                `$INSTANCE_NAME`_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK)

    #define `$INSTANCE_NAME`_CALIBRATE_IDAC_COMP                (`$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE |\
                                                                `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_POLARITY |\
                                                                `$INSTANCE_NAME`_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK |\
                                                                `$INSTANCE_NAME`_IDAC_COMP_LEG2_MODE_GP_STATIC_MASK)

    #define `$INSTANCE_NAME`_CALIBRATE_SW_REFGEN_SEL            (`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK)

    #define `$INSTANCE_NAME`_DEFAULT_REFGEN_GAIN                (`$INSTANCE_NAME`_CSD_GAIN << CYFLD_CSD_GAIN__OFFSET)
    #define `$INSTANCE_NAME`_VREF_HI_OVERSHOOT_CORRECTION       (0x00000001Lu)
    #define `$INSTANCE_NAME`_VREF_LOW_MAX_VALUE                 (31Lu)
    #define `$INSTANCE_NAME`_DEFAULT_REFGEN_VREFLO_SEL          ((`$INSTANCE_NAME`_VREF_LOW_MAX_VALUE - `$INSTANCE_NAME`_VREF_HI_OVERSHOOT_CORRECTION) \
                                                                  <<  CYFLD_CSD_VREFLO_SEL__OFFSET)

    #define `$INSTANCE_NAME`_REFGEN_WITH_SHIELD                 (`$INSTANCE_NAME`_REFGEN_REFGEN_EN_MASK |\
                                                                `$INSTANCE_NAME`_REFGEN_RES_EN_MASK |\
                                                                `$INSTANCE_NAME`_DEFAULT_REFGEN_GAIN |\
                                                                `$INSTANCE_NAME`_DEFAULT_REFGEN_VREFLO_SEL)

    #define `$INSTANCE_NAME`_REFGEN_NO_SHIELD                  (`$INSTANCE_NAME`_REFGEN_REFGEN_EN_MASK |\
                                                                `$INSTANCE_NAME`_REFGEN_RES_EN_MASK |\
                                                                `$INSTANCE_NAME`_DEFAULT_REFGEN_GAIN)

    #define `$INSTANCE_NAME`_SENSE_PERIOD_LFSR_SIZE_SHIFT       (CYFLD_CSD_LFSR_SIZE__OFFSET)

    /* Initial PRS mode */
    #define `$INSTANCE_NAME`_PRS_8_CONFIG                       (`$INSTANCE_NAME`_CLK_SOURCE_PRS8)
    #define `$INSTANCE_NAME`_PRS_12_CONFIG                      (`$INSTANCE_NAME`_CLK_SOURCE_PRS12)

    #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_SENSE_PERIOD           (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT)
    #elif (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_SENSE_PERIOD           (`$INSTANCE_NAME`_CLK_SOURCE_SSC2)
    #elif ((`$INSTANCE_NAME`_CLK_SOURCE_PRS8) == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_SENSE_PERIOD           (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #elif ((`$INSTANCE_NAME`_CLK_SOURCE_PRS12) == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_SENSE_PERIOD           (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_SENSE_PERIOD           (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE            (`$INSTANCE_NAME`_DEFAULT_SENSE_PERIOD)

    /* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_ISX_EN) || \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN))
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_CMOD             (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_CMOD             (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_CMOD             (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */
    #else
        #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_CMOD                 (0x00000000uL)
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

    #if ((0u != `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_TANK             (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_HS_P_SEL_SCAN_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_TANK             (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_HS_P_SEL_SCAN_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION)
            #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_TANK             (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_HS_P_SEL_SCAN_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_TANK             (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
            #define `$INSTANCE_NAME`_HS_P_SEL_SCAN_TANK               (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (`$INSTANCE_NAME`_CSD__CSH_TANK_PAD == `$INSTANCE_NAME`_CTANK_CONNECTION) */
        #define `$INSTANCE_NAME`_SW_HS_P_SEL_SCAN                     (`$INSTANCE_NAME`_HS_P_SEL_SCAN_TANK)
    #else
        #define `$INSTANCE_NAME`_HS_P_SEL_COARSE_TANK                 (0x00000000uL)
        #define `$INSTANCE_NAME`_SW_HS_P_SEL_SCAN                     (`$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #endif /* ((0u != `$INSTANCE_NAME`_CSD__CSD_CSH_TANK_ENABLE) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)) */

    #define `$INSTANCE_NAME`_SW_HS_P_SEL_COARSE                 (`$INSTANCE_NAME`_HS_P_SEL_COARSE_CMOD | `$INSTANCE_NAME`_HS_P_SEL_COARSE_TANK)

    /***************************************
    * CSDv2 Registers shifts
    ***************************************/
    #define `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT                 (CYFLD_CSD_SHIELD_DELAY__OFFSET)
    #define `$INSTANCE_NAME`_LFSR_SIZE_SHIFT                    (CYFLD_CSD_LFSR_SIZE__OFFSET)
    #define `$INSTANCE_NAME`_RESULT_VAL1_BAD_CONVS_SHIFT        (CYFLD_CSD_BAD_CONVS__OFFSET)
    #define `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_SHIFT        (CYFLD_CSD_SW_HCBV__OFFSET)

    /***************************************
    * LFSR Register masks
    ***************************************/
    #define `$INSTANCE_NAME`_RESOLUTION_OFFSET                  (0u)
    #define `$INSTANCE_NAME`_LFSR_TABLE_SIZE                    (4u)

    #define `$INSTANCE_NAME`_PRS_LENGTH_2_BITS                  (0x00000003Lu)
    #define `$INSTANCE_NAME`_PRS_LENGTH_3_BITS                  (0x00000007Lu)
    #define `$INSTANCE_NAME`_PRS_LENGTH_4_BITS                  (0x0000000FLu)
    #define `$INSTANCE_NAME`_PRS_LENGTH_5_BITS                  (0x0000001FLu)
    #define `$INSTANCE_NAME`_PRS_LENGTH_8_BITS                  (0x000000FFLu)
    #define `$INSTANCE_NAME`_PRS_LENGTH_12_BITS                 (0x00000FFFLu)

    #if(`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN)
        #define `$INSTANCE_NAME`_SNSCLK_SSC1_PERIOD                (3u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC2_PERIOD                (7u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC3_PERIOD                (15u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC4_PERIOD                (31u)

        #define `$INSTANCE_NAME`_SNSCLK_SSC1_RANGE                 (1u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC2_RANGE                 (3u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC3_RANGE                 (7u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC4_RANGE                 (15u)
    #else

        #define `$INSTANCE_NAME`_SNSCLK_SSC1_PERIOD                (63u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC2_PERIOD                (127u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC3_PERIOD                (511u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC4_PERIOD                (1023u)

        #define `$INSTANCE_NAME`_SNSCLK_SSC1_RANGE                 (16u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC2_RANGE                 (16u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC3_RANGE                 (16u)
        #define `$INSTANCE_NAME`_SNSCLK_SSC4_RANGE                 (16u)
    #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN) */

    #define `$INSTANCE_NAME`_LFSR_DITHER_PERCENTAGE             (10uL)
    #define `$INSTANCE_NAME`_SNSCLK_SSC1_THRESHOLD              (`$INSTANCE_NAME`_LFSR_DITHER_PERCENTAGE * `$INSTANCE_NAME`_SNSCLK_SSC1_RANGE)
    #define `$INSTANCE_NAME`_SNSCLK_SSC2_THRESHOLD              (`$INSTANCE_NAME`_LFSR_DITHER_PERCENTAGE * `$INSTANCE_NAME`_SNSCLK_SSC2_RANGE)
    #define `$INSTANCE_NAME`_SNSCLK_SSC3_THRESHOLD              (`$INSTANCE_NAME`_LFSR_DITHER_PERCENTAGE * `$INSTANCE_NAME`_SNSCLK_SSC3_RANGE)
    #define `$INSTANCE_NAME`_SNSCLK_SSC4_THRESHOLD              (`$INSTANCE_NAME`_LFSR_DITHER_PERCENTAGE * `$INSTANCE_NAME`_SNSCLK_SSC4_RANGE)

    #define `$INSTANCE_NAME`_HFCLK_SNSCLK_FACTOR                (160u)
    #define `$INSTANCE_NAME`_SKIP_INIT_CYCLES                   (4u)

#else

    /* CSDv1 CSD_CONFIG register masks    */
    #define `$INSTANCE_NAME`_CONFIG_BYPASS_SEL_MASK         (0x00000004Lu)
    #define `$INSTANCE_NAME`_CONFIG_FILTER_EN_MASK          (0x00000008Lu)
    #define `$INSTANCE_NAME`_CONFIG_DUAL_CAP_EN_MASK        (0x00000010Lu)
    #define `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK          (0x00000020Lu)
    #define `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK         (0x00000040Lu)
    #define `$INSTANCE_NAME`_CONFIG_PRS_12_8_MASK           (0x00000080Lu)
    #define `$INSTANCE_NAME`_CONFIG_SHIELD_DELAY_MASK       (0x00000600Lu)
    #define `$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_MASK      (0x00000800Lu)
    #define `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK           (0x00001000Lu)
    #define `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK          (0x00002000Lu)
    #define `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK          (0x00004000Lu)
    #define `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK           (0x00008000Lu)
    #define `$INSTANCE_NAME`_CONFIG_POLARITY_MASK           (0x00010000Lu)
    #define `$INSTANCE_NAME`_CONFIG_POLARITY2_MASK          (0x00020000Lu)
    #define `$INSTANCE_NAME`_CONFIG_MUTUALCAP_EN_MASK       (0x00040000Lu)
    #define `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK      (0x00080000Lu)
    #define `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK      (0x00200000Lu)
    #define `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_MASK        (0x00400000Lu)
    #define `$INSTANCE_NAME`_CONFIG_REFBUF_DRV_MASK         (0x01800000Lu)
    #define `$INSTANCE_NAME`_CONFIG_DDFTSEL_MASK            (0x1C000000Lu)
    #define `$INSTANCE_NAME`_CONFIG_ADFTEN_MASK             (0x20000000Lu)
    #define `$INSTANCE_NAME`_CONFIG_DDFT_COMP_MASK          (0x40000000Lu)
    #define `$INSTANCE_NAME`_CONFIG_ENABLE_MASK             (0x80000000Lu)

    /* CSDv1 CSD_IDAC register masks  */
    #define `$INSTANCE_NAME`_IDAC_MOD_MASK                  (0x000000FFLu)
    #define `$INSTANCE_NAME`_IDAC_MOD_MODE_MASK             (0x00000300Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK            (0x00000400Lu)
    #define `$INSTANCE_NAME`_IDAC_POLARITY1_MIR_MASK        (0x00001000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_MASK                 (0x007F0000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_MODE_MASK            (0x03000000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_RANGE_MASK           (0x04000000Lu)
    #define `$INSTANCE_NAME`_IDAC_POLARITY2_MIR_MASK        (0x10000000Lu)
    #define `$INSTANCE_NAME`_IDAC_FEEDBACK_MODE_MASK        (0x40000000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_MODE_OFF              (0x00000000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_MODE_FIXED            (0x00000100Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE         (0x00000200Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_MODE_DSI              (0x00000300Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_MODE_OFF             (0x00000000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_MODE_FIXED           (0x01000000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_MODE_VARIABLE        (0x02000000Lu)
    #define `$INSTANCE_NAME`_IDAC_COMP_MODE_DSI             (0x03000000Lu)
    #define `$INSTANCE_NAME`_IDAC_MOD_VALUE_SHIFT           (0u)
    #define `$INSTANCE_NAME`_IDAC_MOD_CFG_MASK              (`$INSTANCE_NAME`_IDAC_POLARITY1_MIR_MASK |\
                                                            `$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK |\
                                                            `$INSTANCE_NAME`_IDAC_MOD_MODE_MASK |\
                                                            `$INSTANCE_NAME`_IDAC_MOD_MASK)

    #define `$INSTANCE_NAME`_IDAC_COMP_CFG_MASK              (`$INSTANCE_NAME`_IDAC_POLARITY2_MIR_MASK |\
                                                            `$INSTANCE_NAME`_IDAC_COMP_RANGE_MASK |\
                                                            `$INSTANCE_NAME`_IDAC_COMP_MODE_MASK |\
                                                            `$INSTANCE_NAME`_IDAC_COMP_MASK)

    /* CSDv1 CSD_COUNTER register masks   */
    #define `$INSTANCE_NAME`_COUNTER_COUNTER_MASK           (0x0000FFFFLu)
    #define `$INSTANCE_NAME`_COUNTER_PERIOD_MASK            (0xFFFF0000Lu)

    /* CSDv1 CSD_STATUS register masks    */
    #define `$INSTANCE_NAME`_STATUS_CSD_CHARGE_MASK         (0x00000001Lu)
    #define `$INSTANCE_NAME`_STATUS_CSD_SENSE_MASK          (0x00000002Lu)
    #define `$INSTANCE_NAME`_STATUS_COMP_OUT_MASK           (0x00000004Lu)
    #define `$INSTANCE_NAME`_STATUS_SAMPLE                  (0x00000008Lu)

    /* CSDv1 CSD_INTR, CSD_INTR_SET register masks  */
    #define `$INSTANCE_NAME`_INTR_CSD_MASK                  (0x00000001Lu)
    #define `$INSTANCE_NAME`_INTR_SET_CSD_MASK              (0x00000001Lu)
    #define `$INSTANCE_NAME`_INTR_SET_MASK                  (`$INSTANCE_NAME`_INTR_SET_CSD_MASK)

    /* CSDv1 CSD_PWM register masks   */
    #define `$INSTANCE_NAME`_PWM_COUNT_MASK                 (0x0000000FLu)
    #define `$INSTANCE_NAME`_PWM_SEL_MASK                   (0x00000030Lu)

    /* CSDv1 CSD_TRIM1/2 (for IDAC) register masks    */
    #define `$INSTANCE_NAME`_IDAC_TRIM2_MOD_SNK_MASK        (0x0000000FLu)
    #define `$INSTANCE_NAME`_IDAC_TRIM2_COMP_SNK_MASK       (0x000000F0Lu)
    #define `$INSTANCE_NAME`_IDAC_TRIM1_MOD_SRC_MASK        (0x0000000FLu)
    #define `$INSTANCE_NAME`_IDAC_TRIM1_COMP_SRC_MASK       (0x000000F0Lu)

    /* CSDv1 CSD_TRIM FLASH register masks    */
    #define `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_MOD_MASK      (0x0FLu)
    #define `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_COMP_MASK     (0xF0Lu)

    /* CSDv1 Clock register masks    */
    #define `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT           (0u)
    #define `$INSTANCE_NAME`_SNSCLK_CMD_PA_DIV_SHIFT        (8u)
    #define `$INSTANCE_NAME`_SNSCLK_CMD_DISABLE_SHIFT       (30u)
    #define `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_SHIFT        (31u)
    #define `$INSTANCE_NAME`_SNSCLK_CMD_DISABLE_MASK        ((uint32)((uint32)1u << `$INSTANCE_NAME`_SNSCLK_CMD_DISABLE_SHIFT))
    #define `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK         ((uint32)((uint32)1u << `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_SHIFT))

    /* CSDv1 CTANK masks    */
    #define `$INSTANCE_NAME`_CTANK_DR_VDDIO                 (0x0u)
    #define `$INSTANCE_NAME`_CTANK_DR_VSSIO                 (`$INSTANCE_NAME`_DR_MASK << `$INSTANCE_NAME`_CSH_SHIFT)

    #define `$INSTANCE_NAME`_PRS_8_CONFIG                   `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK
    #define `$INSTANCE_NAME`_PRS_12_CONFIG                  (`$INSTANCE_NAME`_CONFIG_PRS_12_8_MASK |\
                                                            `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK)

    /* CSDv1 Initial PRS mode */
    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRS8 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE    `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK

    #elif (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE    (`$INSTANCE_NAME`_CONFIG_PRS_12_8_MASK |\
                                                            `$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE    (0u)
    #endif /* (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE == `$INSTANCE_NAME`_PRS_8BITS) */

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN)

    /* CSDv1 Set IDAC polarity */
    #if (`$INSTANCE_NAME`_CSD_IDAC_CONFIG == `$INSTANCE_NAME`_IDAC_SINKING)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY      `$INSTANCE_NAME`_CONFIG_POLARITY_MASK
        #define `$INSTANCE_NAME`_CSH_DR_CONFIG              `$INSTANCE_NAME`_CTANK_DR_VDDIO
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY      (0u)
        #define `$INSTANCE_NAME`_CSH_DR_CONFIG              `$INSTANCE_NAME`_CTANK_DR_VSSIO
    #endif /* (`$INSTANCE_NAME`_CSD_IDAC_CONFIG == `$INSTANCE_NAME`_IDAC_SINKING) */

    /* Defining default CSD configuration according to settings in customizer. */
    #define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG             (`$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_MASK |\
                                                             `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY |\
                                                             `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_DRV_MASK)

    #define `$INSTANCE_NAME`_CSD_ENABLE_MASK                (`$INSTANCE_NAME`_CONFIG_ENABLE_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK)

    /* CSDv1 Defining mask intended for clearing bits related to pre-charging options. */
    #define `$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK          (`$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK  |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK)

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG          (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN   (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                             `$INSTANCE_NAME`_CSD_ENABLE_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)


    /* CSDv1 Ctank pre-charge mode configuration */
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

    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN) */

    #define `$INSTANCE_NAME`_RESOLUTION_OFFSET                  (16u)
    #define `$INSTANCE_NAME`_PRS_LENGTH_12_BITS                 (0x00000FFFLu)
    #define `$INSTANCE_NAME`_PRS_LENGTH_8_BITS                  (0x000000FFLu)
    #define `$INSTANCE_NAME`_CSD_PRS_12_BIT                     (`$INSTANCE_NAME`_CONFIG_PRS_12_8_MASK)
    #define `$INSTANCE_NAME`_PRS_MODE_MASK                      (`$INSTANCE_NAME`_CONFIG_PRS_12_8_MASK)

    /***************************************
    * CSDv1 Registers shifts
    ***************************************/
    #define `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT                 (0x09u)
    #define `$INSTANCE_NAME`_IDAC_COMP_DATA_OFFSET              (16u)

#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    /* CSDv1 and CSDv2 Clock register masks    */
    #define `$INSTANCE_NAME`_MODCLK_CMD_DIV_SHIFT               (0u)
    #define `$INSTANCE_NAME`_MODCLK_CMD_PA_DIV_SHIFT            (8u)
    #define `$INSTANCE_NAME`_MODCLK_CMD_DISABLE_SHIFT           (30u)
    #define `$INSTANCE_NAME`_MODCLK_CMD_ENABLE_SHIFT            (31u)
    #define `$INSTANCE_NAME`_MODCLK_CMD_DISABLE_MASK            ((uint32)((uint32)1u << `$INSTANCE_NAME`_MODCLK_CMD_DISABLE_SHIFT))
    #define `$INSTANCE_NAME`_MODCLK_CMD_ENABLE_MASK             ((uint32)((uint32)1u << `$INSTANCE_NAME`_MODCLK_CMD_ENABLE_SHIFT))

/* CintB and CintA pin registers  */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) \
    || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) \
    || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) \
    || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_ISX_EN))

    #define `$INSTANCE_NAME`_CintA_PC_REG                       (* (reg32 *) `$INSTANCE_NAME`_CintA__0__PC)
    #define `$INSTANCE_NAME`_CintA_DR_REG                       (* (reg32 *) `$INSTANCE_NAME`_CintA__0__DR)
    #define `$INSTANCE_NAME`_CintA_HSIOM_REG                    (* (reg32 *) `$INSTANCE_NAME`_CintA__0__HSIOM)
    #define `$INSTANCE_NAME`_CintB_PC_REG                       (* (reg32 *) `$INSTANCE_NAME`_CintB__0__PC)
    #define `$INSTANCE_NAME`_CintB_DR_REG                       (* (reg32 *) `$INSTANCE_NAME`_CintB__0__DR)
    #define `$INSTANCE_NAME`_CintB_HSIOM_REG                    (* (reg32 *) `$INSTANCE_NAME`_CintB__0__HSIOM)

    #define `$INSTANCE_NAME`_CintA_PC_PTR                       ((reg32 *) `$INSTANCE_NAME`_CintA__0__PC)
    #define `$INSTANCE_NAME`_CintA_DR_PTR                       ((reg32 *) `$INSTANCE_NAME`_CintA__0__DR)
    #define `$INSTANCE_NAME`_CintA_HSIOM_PTR                    ((reg32 *) `$INSTANCE_NAME`_CintA__0__HSIOM)
    #define `$INSTANCE_NAME`_CintB_PC_PTR                       ((reg32 *) `$INSTANCE_NAME`_CintB__0__PC)
    #define `$INSTANCE_NAME`_CintB_DR_PTR                       ((reg32 *) `$INSTANCE_NAME`_CintB__0__DR)
    #define `$INSTANCE_NAME`_CintB_HSIOM_PTR                    ((reg32 *) `$INSTANCE_NAME`_CintB__0__HSIOM)

    /* CintB and CintA pin masks                                                */
    #define `$INSTANCE_NAME`_CintA_HSIOM_MASK                   ((uint32)`$INSTANCE_NAME`_CintA__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CintA_HSIOM_SHIFT                  ((uint32)`$INSTANCE_NAME`_CintA__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CintA_SHIFT                        ((uint32)`$INSTANCE_NAME`_CintA__0__SHIFT)

    #define `$INSTANCE_NAME`_CintB_HSIOM_MASK                   ((uint32)`$INSTANCE_NAME`_CintB__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CintB_HSIOM_SHIFT                  ((uint32)`$INSTANCE_NAME`_CintB__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CintB_SHIFT                        ((uint32)`$INSTANCE_NAME`_CintB__0__SHIFT)

#endif  /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)) */

/* CMOD and CSH capacitor port-pins registers */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_ISX_EN))

    #define `$INSTANCE_NAME`_CSH_PC_REG                         (* (reg32 *) `$INSTANCE_NAME`_Csh__PC)
    #define `$INSTANCE_NAME`_CSH_PC_PTR                         (  (reg32 *) `$INSTANCE_NAME`_Csh__PC)
    #define `$INSTANCE_NAME`_CSH_DR_REG                         (* (reg32 *) `$INSTANCE_NAME`_Csh__DR)
    #define `$INSTANCE_NAME`_CSH_DR_PTR                         (  (reg32 *) `$INSTANCE_NAME`_Csh__DR)
    #define `$INSTANCE_NAME`_CSH_HSIOM_REG                      (* (reg32 *) `$INSTANCE_NAME`_Csh__0__HSIOM)
    #define `$INSTANCE_NAME`_CSH_HSIOM_PTR                      (  (reg32 *) `$INSTANCE_NAME`_Csh__0__HSIOM)

    #define `$INSTANCE_NAME`_CMOD_PC_REG                        (* (reg32 *) `$INSTANCE_NAME`_Cmod__PC)
    #define `$INSTANCE_NAME`_CMOD_PC_PTR                        (  (reg32 *) `$INSTANCE_NAME`_Cmod__PC)
    #define `$INSTANCE_NAME`_CMOD_PC_SHIFT                      (`$INSTANCE_NAME`_Cmod__0__SHIFT * 3u)
    #define `$INSTANCE_NAME`_CMOD_DR_REG                        (* (reg32 *) `$INSTANCE_NAME`_Cmod__DR)
    #define `$INSTANCE_NAME`_CMOD_DR_PTR                        (  (reg32 *) `$INSTANCE_NAME`_Cmod__DR)
    #define `$INSTANCE_NAME`_CMOD_DR_SHIFT                      `$INSTANCE_NAME`_Cmod__0__SHIFT
    #define `$INSTANCE_NAME`_CMOD_HSIOM_REG                     (* (reg32 *) `$INSTANCE_NAME`_Cmod__0__HSIOM)
    #define `$INSTANCE_NAME`_CMOD_HSIOM_PTR                     (  (reg32 *) `$INSTANCE_NAME`_Cmod__0__HSIOM)

    /* Cmod and Csh pin masks */
    #define `$INSTANCE_NAME`_CMOD_HSIOM_MASK                    `$INSTANCE_NAME`_Cmod__0__HSIOM_MASK
    #define `$INSTANCE_NAME`_CMOD_HSIOM_SHIFT                   `$INSTANCE_NAME`_Cmod__0__HSIOM_SHIFT
    #define `$INSTANCE_NAME`_CSH_HSIOM_MASK                     `$INSTANCE_NAME`_Csh__0__HSIOM_MASK
    #define `$INSTANCE_NAME`_CSH_HSIOM_SHIFT                    `$INSTANCE_NAME`_Csh__0__HSIOM_SHIFT
    #define `$INSTANCE_NAME`_CSH_SHIFT                          `$INSTANCE_NAME`_Csh__0__SHIFT
    #define `$INSTANCE_NAME`_CSH_PC_SHIFT                       (`$INSTANCE_NAME`_Csh__0__SHIFT * 3u)

#endif  /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)) */

/* GPIO register masks */
#define `$INSTANCE_NAME`_CSH_TO_AMUXBUS_B_MASK                  (0x00000007Lu)
#define `$INSTANCE_NAME`_CSH_PC_MASK                            (0x00000007Lu)
#define `$INSTANCE_NAME`_CSH_PC_STRONG_MODE                     (0x00000006Lu)

#define `$INSTANCE_NAME`_HSIOM_SEL_MASK                         (0x0000000FLu)
#define `$INSTANCE_NAME`_HSIOM_SEL_GPIO                         (0x00000000Lu)
#define `$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE                    (0x00000004Lu)
#define `$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD                   (0x00000005Lu)
#define `$INSTANCE_NAME`_HSIOM_SEL_AMUXA                        (0x00000006Lu)
#define `$INSTANCE_NAME`_HSIOM_SEL_AMUXB                        (0x00000007Lu)
#define `$INSTANCE_NAME`_HSIOM_SEL_ACT_0                        (0x00000008Lu)

#define `$INSTANCE_NAME`_GPIO_PC_MASK                           (0x00000007Lu)
#define `$INSTANCE_NAME`_GPIO_HIGHZ_MASK                        (0x00000007Lu)
#define `$INSTANCE_NAME`_GPIO_STRGDRV                           (0x00000006Lu)

#define `$INSTANCE_NAME`_SNS_GROUND_CONNECT                     (0x00000006Lu)

#define `$INSTANCE_NAME`_GPIO_PC_BIT_SIZE                       (3u)

/***************************************
* API Constants
***************************************/

#define `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ                      (12000000uL)
#define `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ                      (24000000uL)
#define `$INSTANCE_NAME`_MOD_CSD_CLK_48MHZ                      (48000000uL)

/* ISR Number to work with CyLib functions */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    #define `$INSTANCE_NAME`_ISR0_NUMBER                         (`$INSTANCE_NAME`_ISR0__INTC_NUMBER)
    #define `$INSTANCE_NAME`_ISR1_NUMBER                         (`$INSTANCE_NAME`_ISR1__INTC_NUMBER)
#else
    #define `$INSTANCE_NAME`_ISR_NUMBER                         (`$INSTANCE_NAME`_ISR__INTC_NUMBER)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

/* Multi-frequency scanning constants */
#define `$INSTANCE_NAME`_FREQ_CHANNEL_0                         (0u)
#define `$INSTANCE_NAME`_FREQ_CHANNEL_1                         (1u)
#define `$INSTANCE_NAME`_FREQ_CHANNEL_2                         (2u)

/* Bit-mask which says that scanning is not complete */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    /* Bit 18: WIDGET BUSY flag status for CSD2X (scan is ccomplete for both channels */
    #define `$INSTANCE_NAME`_STATUS_CSD01_BUSY_SIZE             (0x00000001Lu)
    #define `$INSTANCE_NAME`_STATUS_CSD01_BUSY_SHIFT            (18u)
    #define `$INSTANCE_NAME`_STATUS_CSD01_BUSY_MASK             (`$INSTANCE_NAME`_STATUS_CSD01_BUSY_SIZE << `$INSTANCE_NAME`_STATUS_CSD01_BUSY_SHIFT)

    #define `$INSTANCE_NAME`_SW_STS_BUSY                        (`$INSTANCE_NAME`_STATUS_CSD01_BUSY_MASK)
#else
    #define `$INSTANCE_NAME`_SW_STS_BUSY                        (`$INSTANCE_NAME`_STATUS_CSD0_MASK)
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#define `$INSTANCE_NAME`_NOT_BUSY                               (0u)

#define `$INSTANCE_NAME`_WDGT_SW_STS_BUSY                       (`$INSTANCE_NAME`_STATUS_WDGT0_BUSY_MASK)

/* Definition of time interval that is enough for charging 100nF capacitor */
#define `$INSTANCE_NAME`_AVG_CYCLES_PER_LOOP                    (5u)
#define `$INSTANCE_NAME`_MAX_CHARGE_TIME_US                     (100u)
#define `$INSTANCE_NAME`_SOFTWARE_WDT_CYCLES_NUM                (((CYDEV_BCLK__SYSCLK__MHZ) * (`$INSTANCE_NAME`_MAX_CHARGE_TIME_US)) /\
                                                                 (`$INSTANCE_NAME`_AVG_CYCLES_PER_LOOP))

#define `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM                  (9u)
#define `$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC         (`$INSTANCE_NAME`_CSD_PRESCAN_SETTLING_TIME * CYDEV_BCLK__SYSCLK__MHZ)
#define `$INSTANCE_NAME`_CMOD_DISCHARGE_TIME                    (2u)
#define `$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES_CALC             (`$INSTANCE_NAME`_CMOD_DISCHARGE_TIME * CYDEV_BCLK__SYSCLK__MHZ)

#if(`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC >= `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM)
    #define `$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES          (`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC -\
                                                                `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM)
#else
    #define `$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES          (`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC)
#endif /* (`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC >= `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM) */

#if(`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES_CALC >= `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM)
    #define `$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES              (`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES_CALC -\
                                                                `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM)
#else
    #define `$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES              (`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES_CALC)
#endif /* (`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES_CALC >= `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM) */

#define `$INSTANCE_NAME`_PRECHARGE_IDAC_MOD_VAL                 (0xF0u)
#define `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG              (`$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE |\
                                                                 `$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK |\
                                                                 `$INSTANCE_NAME`_IDAC_FEEDBACK_MODE_MASK |\
                                                                 `$INSTANCE_NAME`_PRECHARGE_IDAC_MOD_VAL)

#define `$INSTANCE_NAME`_CNT_RESOLUTION_12_BITS                 (0x0FFF0000Lu)
#define `$INSTANCE_NAME`_ONE_CYCLE                              (0x00010000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_16_BITS                     (0xFFFF0000Lu)
#define `$INSTANCE_NAME`_DISCONNECT_IO_FLAG                     (1u)
#define `$INSTANCE_NAME`_PRESCALERS_TBL_SIZE                    (16u)

/* Calibration constants */
#define `$INSTANCE_NAME`_CALIBRATION_LEVEL_85                   (85u)
#define `$INSTANCE_NAME`_PERCENTAGE_100                         (0x00000064Lu)
#define `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR_NEG           (10u)
#define `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR_POS           (10u)
#define `$INSTANCE_NAME`_IDAC_MOD_MAX_INT_MATH_SHIFT            (16u)
#define `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR_MULT          ((((`$INSTANCE_NAME`_PERCENTAGE_100 + `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR_POS + 1u) \
                                                                 << `$INSTANCE_NAME`_IDAC_MOD_MAX_INT_MATH_SHIFT) / `$INSTANCE_NAME`_PERCENTAGE_100))
#define `$INSTANCE_NAME`_IDAC_MOD_MIN_CALIB_ERROR_MULT          ((((`$INSTANCE_NAME`_PERCENTAGE_100 - `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR_NEG - 1u) \
                                                                 << `$INSTANCE_NAME`_IDAC_MOD_MAX_INT_MATH_SHIFT) / `$INSTANCE_NAME`_PERCENTAGE_100))

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    #define `$INSTANCE_NAME`_CSD_IDAC_BITS_USED                 (7u)
#else
    #define `$INSTANCE_NAME`_CSD_IDAC_BITS_USED                 (8u)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
#define `$INSTANCE_NAME`_CAL_MIDDLE_BIT                         (1uL << (`$INSTANCE_NAME`_CSD_IDAC_BITS_USED - 1u))
#define `$INSTANCE_NAME`_MAX_16_BITS_VALUE                      (0x0000FFFFLu)
#define `$INSTANCE_NAME`_MAX_SCAN_TIME                          (`$INSTANCE_NAME`_MAX_16_BITS_VALUE * `$INSTANCE_NAME`_CSD_SCANSPEED_DIVIDER)
#define `$INSTANCE_NAME`_CALIBR_WATCHDOG_CYCLES_NUM             (`$INSTANCE_NAME`_MAX_SCAN_TIME / `$INSTANCE_NAME`_AVG_CYCLES_PER_LOOP)
#define `$INSTANCE_NAME`_ALL_WIDGETS_WATCHDOG_CYCLES_NUM        (`$INSTANCE_NAME`_TOTAL_WIDGETS * `$INSTANCE_NAME`_CALIBR_WATCHDOG_CYCLES_NUM)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    #define `$INSTANCE_NAME`_EXT_CAP_WATCHDOG_CYCLES_NUM                 (`$INSTANCE_NAME`_MAX_SCAN_TIME)
#else
    #define `$INSTANCE_NAME`_EXT_CAP_WATCHDOG_CYCLES_NUM                 (`$INSTANCE_NAME`_CALIBR_WATCHDOG_CYCLES_NUM)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN)
    #if (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA             (2400u)
    #elif (`$INSTANCE_NAME`_IDAC_GAIN_HIGH == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA             (2400u)
    #elif (`$INSTANCE_NAME`_IDAC_GAIN_4X == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA             (1200u)
    #elif (`$INSTANCE_NAME`_IDAC_GAIN_MEDIUM == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA             (300u)
    #else
        #define `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA             (37u)
    #endif /* (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD_IDAC_GAIN) */
#endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
    #define `$INSTANCE_NAME`_CSD_DUAL_IDAC_FACTOR               (2u)
#else
    #define `$INSTANCE_NAME`_CSD_DUAL_IDAC_FACTOR               (1u)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

#define `$INSTANCE_NAME`_EMPTY_SLOT                          (255u)

/***************************************
* Global software/external variables
***************************************/
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))
    extern `$INSTANCE_NAME`_SENSE_METHOD_ENUM `$INSTANCE_NAME`_currentSenseMethod;
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)) */

#if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
    extern uint8 `$INSTANCE_NAME`_scanFreqIndex;
    extern uint8 `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_NUM_SCAN_FREQS];
#else
    extern const uint8 `$INSTANCE_NAME`_scanFreqIndex;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    extern volatile uint8 `$INSTANCE_NAME`_widgetIndex0;
    extern volatile uint8 `$INSTANCE_NAME`_sensorIndex0;
    extern volatile uint8 `$INSTANCE_NAME`_widgetIndex1;
    extern volatile uint8 `$INSTANCE_NAME`_sensorIndex1;
#else
    extern volatile uint8 `$INSTANCE_NAME`_widgetIndex;
    extern volatile uint8 `$INSTANCE_NAME`_sensorIndex;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
extern uint8 `$INSTANCE_NAME`_requestScanAllWidget;
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    extern `$INSTANCE_NAME`_RAM_SNS_STRUCT *`$INSTANCE_NAME`_curRamSnsPtr0;
    extern `$INSTANCE_NAME`_RAM_SNS_STRUCT *`$INSTANCE_NAME`_curRamSnsPtr1;
#else
    extern `$INSTANCE_NAME`_RAM_SNS_STRUCT *`$INSTANCE_NAME`_curRamSnsPtr;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN))
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
         extern `$INSTANCE_NAME`_FLASH_WD_STRUCT const *`$INSTANCE_NAME`_curFlashWdgtPtr0;
         extern `$INSTANCE_NAME`_FLASH_WD_STRUCT const *`$INSTANCE_NAME`_curFlashWdgtPtr1;
    #else
         extern `$INSTANCE_NAME`_FLASH_WD_STRUCT const *`$INSTANCE_NAME`_curFlashWdgtPtr;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN))  */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
    /*  Pointer to Flash structure holding info of sensor to be scanned  */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
        extern `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curFlashSnsPtr0;
        extern `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curFlashSnsPtr1;
    #else
        extern `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curFlashSnsPtr;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */
#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    extern uint8 `$INSTANCE_NAME`_prescalersTuningDone;
    extern const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE];
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    extern `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curSnsIOPtr0;
    extern `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curSnsIOPtr1;
#else
    extern `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curSnsIOPtr;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_SENSING_H */


/* [] END OF FILE */
