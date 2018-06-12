/*******************************************************************************
* \file `$INSTANCE_NAME`_Configuration.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the customizer parameters definitions.
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

#if !defined(CY_SENSE_`$INSTANCE_NAME`_CONFIGURATION_H)
#define CY_SENSE_`$INSTANCE_NAME`_CONFIGURATION_H

#include <cytypes.h>

/*******************************************************************************
* Customizer-generated defines
*******************************************************************************/
#define `$INSTANCE_NAME`_ENABLE                             (1u)
#define `$INSTANCE_NAME`_DISABLE                            (0u)

#define `$INSTANCE_NAME`_THIRD_GENERATION_BLOCK             (1u)
#define `$INSTANCE_NAME`_FOURTH_GENERATION_BLOCK            (2u)

#define `$INSTANCE_NAME`_GENERATION_BLOCK_VERSION           (`$CsdGenerationVersion`u)

/*******************************************************************************
* Creator-global defines
*******************************************************************************/

#if (`$INSTANCE_NAME`_GENERATION_BLOCK_VERSION == `$INSTANCE_NAME`_THIRD_GENERATION_BLOCK)
    #define `$INSTANCE_NAME`_CSDV1                          (1u)
#else
    #define `$INSTANCE_NAME`_CSDV1                          (0u)
#endif

#if (`$INSTANCE_NAME`_GENERATION_BLOCK_VERSION == `$INSTANCE_NAME`_FOURTH_GENERATION_BLOCK)
    #define `$INSTANCE_NAME`_CSDV2                          (1u)
#else
    #define `$INSTANCE_NAME`_CSDV2                          (0u)
#endif

#if (`$INSTANCE_NAME`_CSDV1 == 1u)
    #if (0u != CYIPBLOCK_m0s8csd_VERSION)
        #define `$INSTANCE_NAME`_CSDV1_VER2                 (1u)
    #else
        #define `$INSTANCE_NAME`_CSDV1_VER2                 (0u)
    #endif  /* (0u != CYIPBLOCK_m0s8csd_VERSION) */
#endif  /* CYIPBLOCK_m0s8csdv2_VERSION */


#define `$INSTANCE_NAME`_2000_MV                            (2000u)

#ifdef CYDEV_VDDA_MV
    #define `$INSTANCE_NAME`_CYDEV_VDDA_MV                  (CYDEV_VDDA_MV)
#else
    #ifdef CYDEV_VDD_MV
        #define `$INSTANCE_NAME`_CYDEV_VDDA_MV              (CYDEV_VDD_MV)
    #endif
#endif

#define `$INSTANCE_NAME`_BAD_CONVERSIONS_NUM                (1u)
#define `$INSTANCE_NAME`_RESAMPLING_CYCLES_MAX_NUMBER       (1u)

/*******************************************************************************
* Enabled Scan Methods
*******************************************************************************/
#define `$INSTANCE_NAME`_CSD_EN                   (`$CsdEnable`u)
#define `$INSTANCE_NAME`_CSX_EN                   (`$CsxEnable`u)
#define `$INSTANCE_NAME`_ISX_EN                   (`$IsxEnable`u)
#define `$INSTANCE_NAME`_CSD_CSX_EN               (`$INSTANCE_NAME`_CSD_EN && `$INSTANCE_NAME`_CSX_EN)
#define `$INSTANCE_NAME`_CSD_ISX_EN               (`$INSTANCE_NAME`_CSD_EN && `$INSTANCE_NAME`_ISX_EN)
#define `$INSTANCE_NAME`_CSX_ISX_EN               (`$INSTANCE_NAME`_CSX_EN && `$INSTANCE_NAME`_ISX_EN)
#define `$INSTANCE_NAME`_CSD_CSX_ISX_EN           (`$INSTANCE_NAME`_CSD_EN && `$INSTANCE_NAME`_CSX_EN & `$INSTANCE_NAME`_ISX_EN)
#define `$INSTANCE_NAME`_USES_MANY_SENSE_MODES    ((`$INSTANCE_NAME`_TOTAL_CSD_WIDGETS && \
                                                   (`$INSTANCE_NAME`_TOTAL_CSX_WIDGETS || `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS)) || \
                                                   (`$INSTANCE_NAME`_TOTAL_CSX_WIDGETS && `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS))
#define `$INSTANCE_NAME`_CSD2X_EN                 (0u)
#define `$INSTANCE_NAME`_CSX2X_EN                 (0u)

/*******************************************************************************
* Definitions for number of widgets and sensors
*******************************************************************************/
#define `$INSTANCE_NAME`_TOTAL_WIDGETS            (`$TotalWidgets`u)
#define `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS        (`$TotalCsdWidgets`u)
#define `$INSTANCE_NAME`_TOTAL_CSD_SENSORS        (`$TotalCsdSensors`u)
#define `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS        (`$TotalCsxWidgets`u)
#define `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS        (`$TotalIsxWidgets`u)
#define `$INSTANCE_NAME`_TOTAL_CSX_NODES          (`$TotalCsxNodes`u)
#define `$INSTANCE_NAME`_TOTAL_ISX_NODES          (`$TotalIsxNodes`u)

/*******************************************************************************
* Total number of CSD sensors + CSX nodes
*******************************************************************************/
#define `$INSTANCE_NAME`_TOTAL_SENSORS            (`$INSTANCE_NAME`_TOTAL_CSD_SENSORS + \
                                                   `$INSTANCE_NAME`_TOTAL_CSX_NODES+ \
                                                   `$INSTANCE_NAME`_TOTAL_ISX_NODES)

/*******************************************************************************
* Total number of scan slots (used only when dual-channel scan is enabled)
*******************************************************************************/
#define `$INSTANCE_NAME`_TOTAL_SCAN_SLOTS         (`$TotalScanSlots`u)

/*******************************************************************************
* Defines widget IDs
*******************************************************************************/
`$WidgetAlias`
/*******************************************************************************
* Defines sensor IDs
*******************************************************************************/
`$SensorAlias`
`$SlotAlias`
`$AdcChannelAlias`
/*******************************************************************************
* Enabled widget types
*******************************************************************************/
#define `$INSTANCE_NAME`_BUTTON_WIDGET_EN         (`$ButtonWidgetEnable`u)
#define `$INSTANCE_NAME`_SLIDER_WIDGET_EN         (`$SliderWidgetEnable`u)
#define `$INSTANCE_NAME`_MATRIX_WIDGET_EN         (`$MatrixWidgetEnable`u)
#define `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN      (`$ProximityWidgetEnable`u)
#define `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN       (`$TouchpadWidgetEnable`u)

#define `$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN     (`$CsdMatrixWidgetEnable`u)
#define `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN   (`$CsdTouchpadWidgetEnable`u)

#define `$INSTANCE_NAME`_CSX_MATRIX_WIDGET_EN     (`$CsxMatrixWidgetEnable`u)
#define `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN   (`$CsxTouchpadWidgetEnable`u)

/*******************************************************************************
* Centroid APIs
*******************************************************************************/
#define `$INSTANCE_NAME`_CENTROID_EN              (`$CentroidEnable`u)
#define `$INSTANCE_NAME`_TOTAL_DIPLEXED_SLIDERS   (`$TotalDiplexedSliders`u)
#define `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS     (`$TotalLinearSliders`u)
#define `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS     (`$TotalRadialSliders`u)
#define `$INSTANCE_NAME`_TOTAL_TOUCHPADS          (`$TotalTouchpads`u)
#define `$INSTANCE_NAME`_MAX_CENTROID_LENGTH      (`$MaxCentroidLength`u)
#define `$INSTANCE_NAME`_SLIDER_MULT_METHOD       (`$SliderMultiplierMethod`u)
#define `$INSTANCE_NAME`_TOUCHPAD_MULT_METHOD     (`$TouchpadMultiplierMethod`u)

/*******************************************************************************
* Enabled sensor types
*******************************************************************************/
#define `$INSTANCE_NAME`_REGULAR_SENSOR_EN        (`$RegularSensorEnable`u)
#define `$INSTANCE_NAME`_PROXIMITY_SENSOR_EN      (`$ProximitySensorEnable`u)

/*******************************************************************************
* Sensor ganging
*******************************************************************************/
#define `$INSTANCE_NAME`_GANGED_SNS_EN            (`$GangedSensorEnable`u)
#define `$INSTANCE_NAME`_CSD_GANGED_SNS_EN        (`$CsdGangedSensorEnable`u)
#define `$INSTANCE_NAME`_CSX_GANGED_SNS_EN        (`$CsxGangedSensorEnable`u)

/*******************************************************************************
* Max number of sensors used among all the widgets
*******************************************************************************/
#define `$INSTANCE_NAME`_MAX_SENSORS_PER_WIDGET   (`$MaxSensorsPerWidget`u)
#define `$INSTANCE_NAME`_MAX_SENSORS_PER_5X5_TOUCHPAD (`$MaxSensorsPer5x5Touchpad`u)

/*******************************************************************************
* Total number of all used electrodes (NOT unique)
*******************************************************************************/
#define `$INSTANCE_NAME`_TOTAL_ELECTRODES         (`$TotalElectrodes`u)
/* Obsolete */
#define `$INSTANCE_NAME`_TOTAL_SENSOR_IOS         `$INSTANCE_NAME`_TOTAL_ELECTRODES

/*******************************************************************************
* Total number of used physical IOs (unique)
*******************************************************************************/
#define `$INSTANCE_NAME`_TOTAL_IO_CNT             (`$TotalIoCount`u)

/*******************************************************************************
* Array length for widget status registers
*******************************************************************************/
#define `$INSTANCE_NAME`_WDGT_STATUS_WORDS        \
                        (((uint8)((`$INSTANCE_NAME`_TOTAL_WIDGETS - 1u) / 32u)) + 1u)


/*******************************************************************************
* Auto-tuning mode selection
*******************************************************************************/
#define `$INSTANCE_NAME`_CSD_SS_DIS         (0x00ul)
#define `$INSTANCE_NAME`_CSD_SS_HW_EN       (0x01ul)
#define `$INSTANCE_NAME`_CSD_SS_TH_EN       (0x02ul)
#define `$INSTANCE_NAME`_CSD_SS_HWTH_EN     (`$INSTANCE_NAME`_CSD_SS_HW_EN | \
                                             `$INSTANCE_NAME`_CSD_SS_TH_EN)

#define `$INSTANCE_NAME`_CSD_AUTOTUNE       `$CsdTuningMode`


/*******************************************************************************
* General settings
*******************************************************************************/

#define `$INSTANCE_NAME`_AUTO_RESET_METHOD_LEGACY (0u)
#define `$INSTANCE_NAME`_AUTO_RESET_METHOD_SAMPLE (1u)

#define `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN       (`$MultiFreqScanEnable`u)
#define `$INSTANCE_NAME`_SENSOR_AUTO_RESET_EN     (`$SensorAutoResetEnable`u)
#define `$INSTANCE_NAME`_SENSOR_AUTO_RESET_METHOD (`$SensorAutoResetMethod`u)
#define `$INSTANCE_NAME`_NUM_CENTROIDS            (`$NumCentroids`u)
#define `$INSTANCE_NAME`_4PTS_LOCAL_MAX_EN        (`$Centroid4PtsEnable`u)
#define `$INSTANCE_NAME`_OFF_DEBOUNCE_EN          (`$OffDebounceEnable`u)
#define `$INSTANCE_NAME`_CUSTOM_DS_RAM_SIZE       (`$CustomDataStructSize`u)

/* Defines power status of HW block after scanning */
#define `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN  (`$BlockOffAfterScanEnable`u)

/* Defines number of scan frequencies */
#if (`$INSTANCE_NAME`_DISABLE != `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
    #define `$INSTANCE_NAME`_NUM_SCAN_FREQS       (3u)
#else
    #define `$INSTANCE_NAME`_NUM_SCAN_FREQS       (1u)
#endif /* #if (`$INSTANCE_NAME`_DISABLE != `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

/* Data size for thresholds / low baseline reset */
#define `$INSTANCE_NAME`_SIZE_8BITS               (8u)
#define `$INSTANCE_NAME`_SIZE_16BITS              (16u)

#define `$INSTANCE_NAME`_THRESHOLD_SIZE           `$ThresholdSize`
typedef `$ThresholdType` `$INSTANCE_NAME`_THRESHOLD_TYPE;

#if (`$INSTANCE_NAME`_AUTO_RESET_METHOD_LEGACY == `$INSTANCE_NAME`_SENSOR_AUTO_RESET_METHOD)
    #define `$INSTANCE_NAME`_LOW_BSLN_RST_SIZE        `$LowBaselineResetSize`
    typedef `$LowBaselineResetType` `$INSTANCE_NAME`_LOW_BSLN_RST_TYPE;
#else
    #define `$INSTANCE_NAME`_LOW_BSLN_RST_SIZE    (16u)
    typedef uint16 `$INSTANCE_NAME`_LOW_BSLN_RST_TYPE;
#endif /* #if (`$INSTANCE_NAME`_AUTO_RESET_METHOD_LEGACY == `$INSTANCE_NAME`_SENSOR_AUTO_RESET_METHOD) */

/* Coefficient to define touch threshold for proximity sensors */
#define `$INSTANCE_NAME`_PROX_TOUCH_COEFF         (`$TouchProxThresholdCoeff`u)

/*******************************************************************************
* General Filter Constants
*******************************************************************************/

/* Baseline algorithm options */
#define `$INSTANCE_NAME`_IIR_BASELINE                 (0u)
#define `$INSTANCE_NAME`_BUCKET_BASELINE              (1u)

#define `$INSTANCE_NAME`_BASELINE_TYPE                `$BaselineType`

/* IIR baseline filter algorithm for regular sensors*/
#define `$INSTANCE_NAME`_REGULAR_IIR_BL_TYPE          `$RegularIirFilterBaselineType`

/* IIR baseline coefficients for regular sensors */
#define `$INSTANCE_NAME`_REGULAR_IIR_BL_N             (`$RegularIirFilterBaselineN`u)
#define `$INSTANCE_NAME`_REGULAR_IIR_BL_SHIFT         (`$RegularIirFilterBaselineShift`u)

/* IIR baseline filter algorithm for proximity sensors*/
#define `$INSTANCE_NAME`_PROX_IIR_BL_TYPE             `$ProxIirFilterBaselineType`

/* IIR baseline coefficients for proximity sensors */
#define `$INSTANCE_NAME`_PROX_IIR_BL_N                (`$ProxIirFilterBaselineN`u)
#define `$INSTANCE_NAME`_PROX_IIR_BL_SHIFT            (`$ProxIirFilterBaselineShift`u)


/* IIR filter constants */
#define `$INSTANCE_NAME`_IIR_COEFFICIENT_K            (256u)

/* IIR filter type */
#define `$INSTANCE_NAME`_IIR_FILTER_STANDARD          (1u)
#define `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE       (2u)
#define `$INSTANCE_NAME`_IIR_FILTER_MEMORY            (3u)

/* Regular sensor raw count filters */
#define `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN         (`$RegularFilterEnable`u)
#define `$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN     (`$RegularIirFilterEnable`u)
#define `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN  (`$RegularMedianFilterEnable`u)
#define `$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN (`$RegularAverageFilterEnable`u)
#define `$INSTANCE_NAME`_REGULAR_RC_CUSTOM_FILTER_EN  (`$RegularCustomFilterEnable`u)
#define `$INSTANCE_NAME`_REGULAR_RC_ALP_FILTER_EN     (`$RegularAlpFilterEnable`u)

/* Proximity sensor raw count filters */
#define `$INSTANCE_NAME`_PROX_RC_FILTER_EN            (`$ProxFilterEnable`u)
#define `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN        (`$ProxIirFilterEnable`u)
#define `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN     (`$ProxMedianFilterEnable`u)
#define `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN    (`$ProxAverageFilterEnable`u)
#define `$INSTANCE_NAME`_PROX_RC_CUSTOM_FILTER_EN     (`$ProxCustomFilterEnable`u)
#define `$INSTANCE_NAME`_PROX_RC_ALP_FILTER_EN        (`$ProxAlpFilterEnable`u)

#define `$INSTANCE_NAME`_ALP_FILTER_EN                (`$AlpFilterEnable`u)
#define `$INSTANCE_NAME`_REGULAR_RC_ALP_FILTER_COEFF  (`$RegularAlpFilterCoeff`u)
#define `$INSTANCE_NAME`_PROX_RC_ALP_FILTER_COEFF     (`$ProxAlpFilterCoeff`u)

/* Raw count filters */
#define `$INSTANCE_NAME`_RC_FILTER_EN                 (`$INSTANCE_NAME`_REGULAR_RC_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_FILTER_EN)

/* IIR raw count filter algorithm for regular sensors */
#define `$INSTANCE_NAME`_REGULAR_IIR_RC_TYPE          (`$RegularIirFilterRawCountType`)

/* IIR raw count filter coefficients for regular sensors */
#define `$INSTANCE_NAME`_REGULAR_IIR_RC_N             (`$RegularIirFilterRawCountN`u)
#define `$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT         (`$RegularIirFilterRawCountShift`u)

/* IIR raw count filter algorithm for proximity sensors*/
#define `$INSTANCE_NAME`_PROX_IIR_RC_TYPE             (`$ProxIirFilterRawCountType`)

/* IIR raw count filter coefficients for proximity sensors */
#define `$INSTANCE_NAME`_PROX_IIR_RC_N                (`$ProxIirFilterRawCountN`u)
#define `$INSTANCE_NAME`_PROX_IIR_RC_SHIFT            (`$ProxIirFilterRawCountShift`u)

/* Median filter constants */

/* Order of regular sensor median filter */
#define `$INSTANCE_NAME`_REGULAR_MEDIAN_LEN           (2u)

/* Order of proximity sensor median filter */
#define `$INSTANCE_NAME`_PROX_MEDIAN_LEN              (2u)

/* Average filter constants*/
#define `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_2         (1u)
#define `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_4         (3u)

/* Order of regular sensor average filter */
#define `$INSTANCE_NAME`_REGULAR_AVERAGE_LEN          (`$RegularAverageFilterLength`)

/* Order of proximity sensor average filter */
#define `$INSTANCE_NAME`_PROX_AVERAGE_LEN             (`$ProxAverageFilterLength`)

/* Widget baseline coefficient enable */
#define `$INSTANCE_NAME`_WD_BSLN_COEFF_EN             (`$WidgetBaselineCoeffEnable`u)

/* Centroid position filters */
#define `$INSTANCE_NAME`_POSITION_FILTER_EN           (`$PositionFilterEnable`u)
#define `$INSTANCE_NAME`_POS_MEDIAN_FILTER_EN         (`$PosMedianFilterEnable`u)
#define `$INSTANCE_NAME`_POS_IIR_FILTER_EN            (`$PosIirFilterEnable`u)
#define `$INSTANCE_NAME`_POS_ADAPTIVE_IIR_FILTER_EN   (`$PosAdaptiveIirFilterEnable`u)
#define `$INSTANCE_NAME`_POS_AVERAGE_FILTER_EN        (`$PosAverageFilterEnable`u)
#define `$INSTANCE_NAME`_POS_JITTER_FILTER_EN         (`$PosJitterFilterEnable`u)
#define `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN      (`$BallisticMultiplierEnable`u)
#define `$INSTANCE_NAME`_CENTROID_3X3_CSD_EN          (`$Centroid3x3CsdEnable`u)
#define `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN          (`$Centroid5x5CsdEnable`u)
#define `$INSTANCE_NAME`_CSD_5X5_MAX_FINGERS          (`$Csd5x5maxFingers`u)

#define `$INSTANCE_NAME`_POS_IIR_COEFF                (`$PosIirFilterCoeff`u)
#define `$INSTANCE_NAME`_POS_IIR_RESET_RADIAL_SLIDER  (`$RadialSliderPosIirResetThr`u)

#define `$INSTANCE_NAME`_CSX_TOUCHPAD_UNDEFINED       (40u)

/* IDAC options */

/* Third-generation HW block IDAC gain */
#define `$INSTANCE_NAME`_IDAC_GAIN_4X                 (4u)
#define `$INSTANCE_NAME`_IDAC_GAIN_8X                 (8u)

/* Fourth-generation HW block IDAC gain */
#define `$INSTANCE_NAME`_IDAC_GAIN_LOW                (0uL)
#define `$INSTANCE_NAME`_IDAC_GAIN_MEDIUM             (1uL)
#define `$INSTANCE_NAME`_IDAC_GAIN_HIGH               (2uL)

#define `$INSTANCE_NAME`_IDAC_SOURCING                (0u)
#define `$INSTANCE_NAME`_IDAC_SINKING                 (1u)

/* Shield tank capacitor precharge source */
#define `$INSTANCE_NAME`_CSH_PRECHARGE_VREF           (0u)
#define `$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF         (1u)

/* Shield electrode delay */
#define `$INSTANCE_NAME`_NO_DELAY                     (0u)

#if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    #define `$INSTANCE_NAME`_SH_DELAY_5NS             (1u)
    #define `$INSTANCE_NAME`_SH_DELAY_10NS            (2u)
    #define `$INSTANCE_NAME`_SH_DELAY_20NS            (3u)
#else
    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV1_VER2)
        #define `$INSTANCE_NAME`_SH_DELAY_10NS        (3u)
        #define `$INSTANCE_NAME`_SH_DELAY_50NS        (2u)
    #else
        #define `$INSTANCE_NAME`_SH_DELAY_1CYCLES     (1u)
        #define `$INSTANCE_NAME`_SH_DELAY_2CYCLES     (2u)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV1_VER2) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

/* Inactive sensor connection options */
#define `$INSTANCE_NAME`_SNS_CONNECTION_GROUND        (0x00000006Lu)
#define `$INSTANCE_NAME`_SNS_CONNECTION_HIGHZ         (0x00000000Lu)
#define `$INSTANCE_NAME`_SNS_CONNECTION_SHIELD        (0x00000002Lu)

/* Sense clock selection options */
#if defined(`$INSTANCE_NAME`_TAPEOUT_STAR_USED)
    #define `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN            (0u)
#else
    #define `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN            (`$CsdV2Ref9P6Enable`u)
#endif /* defined(`$INSTANCE_NAME`_TAPEOUT_STAR_USED) */

#define `$INSTANCE_NAME`_CLK_SOURCE_DIRECT            (0x00000000Lu)

#define `$INSTANCE_NAME`_CLK_SOURCE_SSC1              (0x01u)
#define `$INSTANCE_NAME`_CLK_SOURCE_SSC2              (0x02u)
#define `$INSTANCE_NAME`_CLK_SOURCE_SSC3              (0x03u)
#define `$INSTANCE_NAME`_CLK_SOURCE_SSC4              (0x04u)

#define `$INSTANCE_NAME`_CLK_SOURCE_PRS8              (0x05u)
#define `$INSTANCE_NAME`_CLK_SOURCE_PRS12             (0x06u)
#define `$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO           (0xFFu)

#define `$INSTANCE_NAME`_MFS_IMO                      (0u)
#define `$INSTANCE_NAME`_MFS_SNS_CLK                  (1u)

/* Defines scan resolutions */
#define `$INSTANCE_NAME`_RES6BIT                      (6u)
#define `$INSTANCE_NAME`_RES7BIT                      (7u)
#define `$INSTANCE_NAME`_RES8BIT                      (8u)
#define `$INSTANCE_NAME`_RES9BIT                      (9u)
#define `$INSTANCE_NAME`_RES10BIT                     (10u)
#define `$INSTANCE_NAME`_RES11BIT                     (11u)
#define `$INSTANCE_NAME`_RES12BIT                     (12u)
#define `$INSTANCE_NAME`_RES13BIT                     (13u)
#define `$INSTANCE_NAME`_RES14BIT                     (14u)
#define `$INSTANCE_NAME`_RES15BIT                     (15u)
#define `$INSTANCE_NAME`_RES16BIT                     (16u)

/* Fourth-generation HW block: Initialization switch resistance */
#define `$INSTANCE_NAME`_INIT_SW_RES_LOW              (0x00000000Lu)
#define `$INSTANCE_NAME`_INIT_SW_RES_MEDIUM           (0x00000001Lu)
#define `$INSTANCE_NAME`_INIT_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: Initialization switch resistance */
#define `$INSTANCE_NAME`_SCAN_SW_RES_LOW              (0x00000000Lu)
#define `$INSTANCE_NAME`_SCAN_SW_RES_MEDIUM           (0x00000001Lu)
#define `$INSTANCE_NAME`_SCAN_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define `$INSTANCE_NAME`_SHIELD_SW_RES_LOW            (0x00000000Lu)
#define `$INSTANCE_NAME`_SHIELD_SW_RES_MEDIUM         (0x00000001Lu)
#define `$INSTANCE_NAME`_SHIELD_SW_RES_HIGH           (0x00000002Lu)
#define `$INSTANCE_NAME`_SHIELD_SW_RES_LOW_EMI        (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define `$INSTANCE_NAME`_INIT_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define `$INSTANCE_NAME`_INIT_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define `$INSTANCE_NAME`_INIT_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define `$INSTANCE_NAME`_INIT_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define `$INSTANCE_NAME`_SCAN_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define `$INSTANCE_NAME`_SCAN_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define `$INSTANCE_NAME`_SCAN_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define `$INSTANCE_NAME`_SCAN_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Sensing method */
#define `$INSTANCE_NAME`_SENSING_LEGACY               (0x00000000Lu)
#define `$INSTANCE_NAME`_SENSING_LOW_EMI              (0x00000001Lu)
#define `$INSTANCE_NAME`_SENSING_FULL_WAVE            (0x00000002Lu)


/*******************************************************************************
* CSD/CSX Common settings
*******************************************************************************/

#define `$INSTANCE_NAME`_BLOCK_ANALOG_WAKEUP_DELAY_US (`$CsdV2AnalogWakeupDelayUs`u)

#define `$INSTANCE_NAME`_MFS_METHOD                   (`$MultiFreqScanMethod`u)
#define `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F1      (`$ImoFreqOffsetF1`u)
#define `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F2      (`$ImoFreqOffsetF2`u)

/*******************************************************************************
* CSD Specific settings
*******************************************************************************/

/* CSD scan method settings */
#define `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN          (`$CsdIdacAutoCalibrateEnable`u)
`$CsdConfig`
#define `$INSTANCE_NAME`_CSD_SCANSPEED_DIVIDER        (`$CsdScanSpeedDivider`u)
#define `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN        (`$CsdCommonSenseClockEnable`u)
#define `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE           (`$CsdSenseClockSource`)
#define `$INSTANCE_NAME`_CSD_SNS_CLK_DIVIDER          (`$CsdSenseClockDivider`u)
#define `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION  (`$CsdInactiveSensorConnection`)
#define `$INSTANCE_NAME`_CSD_IDAC_COMP_EN             (`$CsdIdacCompEnable`u)
#define `$INSTANCE_NAME`_CSD_IDAC_CONFIG              (`$CsdIdacConfig`)
#define `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL       (`$CsdRawCountCalibrationLevel`u)
#define `$INSTANCE_NAME`_CSD_DUALIDAC_LEVEL           (`$CsdDualIdacLevel`u)
#define `$INSTANCE_NAME`_CSD_PRESCAN_SETTLING_TIME    (`$CsdPrescanSettlingTime`u)
#define `$INSTANCE_NAME`_CSD_SNSCLK_R_CONST           (`$CsdSnsClockConstantR`u)
#define `$INSTANCE_NAME`_CSD_VREF_MV                  (`$CsdVrefMv`u)

/* CSD settings - Fourth-generation HW block */
#define `$INSTANCE_NAME`_CSD_ANALOG_STARTUP_DELAY_US  (`$CsdAnalogStartupDelayUs`u)
#define `$INSTANCE_NAME`_CSD_FINE_INIT_TIME           (`$CsdFineInitCycles`u)
#define `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN   (`$CsdDedicatedIdacCompEnable`u)
#define `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN             (`$CsdAutoZeroEnable`u)
#define `$INSTANCE_NAME`_CSD_AUTO_ZERO_TIME           (`$CsdAutoZeroTime`Lu)
#define `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN          (`$CsdNoiseMetricEnable`u)
#define `$INSTANCE_NAME`_CSD_NOISE_METRIC_TH          (`$CsdNoiseMetricThreshold`Lu)
#define `$INSTANCE_NAME`_CSD_INIT_SWITCH_RES          (`$CsdInitSwitchRes`)
#define `$INSTANCE_NAME`_CSD_SENSING_METHOD           (`$CsdSensingMethod`)
#define `$INSTANCE_NAME`_CSD_SHIELD_SWITCH_RES        (`$CsdShieldSwitchRes`)
#define `$INSTANCE_NAME`_CSD_GAIN                     (`$CsdGain`Lu)

#define `$INSTANCE_NAME`_CSD_MFS_DIVIDER_OFFSET_F1    (`$CsdMFSDividerOffsetF1`u)
#define `$INSTANCE_NAME`_CSD_MFS_DIVIDER_OFFSET_F2    (`$CsdMFSDividerOffsetF2`u)


/*******************************************************************************
* CSX Specific settings
*******************************************************************************/

/* CSX scan method settings */
#define `$INSTANCE_NAME`_CSX_SCANSPEED_DIVIDER        (`$CsxScanSpeedDivider`u)
#define `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN         (`$CsxCommonTxClockEnable`u)
#define `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE            (`$CsxTxClockSource`)
#define `$INSTANCE_NAME`_CSX_TX_CLK_DIVIDER           (`$CsxTxClockDivider`u)
#define `$INSTANCE_NAME`_CSX_MAX_FINGERS              (`$CsxMaxFingers`u)
#define `$INSTANCE_NAME`_CSX_MAX_LOCAL_PEAKS          (`$CsxMaxLocalPeaks`u)
#define `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN          (`$CsxIdacAutoCalibrateEnable`u)
#define `$INSTANCE_NAME`_CSX_IDAC_BITS_USED           (`$CsxIdacBitsUsed`u)
#define `$INSTANCE_NAME`_CSX_RAWCOUNT_CAL_LEVEL       (`$CsxRawCountCalibrationLevel`u)
`$CsxConfig`
#define `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES (`$CsxSkipAndOversampleNodes`u)
#define `$INSTANCE_NAME`_CSX_MULTIPHASE_TX_EN         (`$CsxMultiphaseTxEnable`u)
#define `$INSTANCE_NAME`_CSX_MAX_TX_PHASE_LENGTH      (`$CsxMaxTxPhaseLength`u)

/* CSX settings - Fourth-generation HW block */
#define `$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US  (`$CsxAnalogStartupDelayUs`u)
#define `$INSTANCE_NAME`_CSX_AUTO_ZERO_EN             (`$CsxAutoZeroEnable`u)
#define `$INSTANCE_NAME`_CSX_AUTO_ZERO_TIME           (`$CsxAutoZeroTime`u)
#define `$INSTANCE_NAME`_CSX_FINE_INIT_TIME           (`$CsxFineInitCycles`u)
#define `$INSTANCE_NAME`_CSX_NOISE_METRIC_EN          (`$CsxNoiseMetricEnable`u)
#define `$INSTANCE_NAME`_CSX_NOISE_METRIC_TH          (`$CsxNoiseMetricThreshold`u)
#define `$INSTANCE_NAME`_CSX_INIT_SWITCH_RES          (`$CsxInitSwitchRes`)
#define `$INSTANCE_NAME`_CSX_SCAN_SWITCH_RES          (`$CsxScanSwitchRes`)
#define `$INSTANCE_NAME`_CSX_INIT_SHIELD_SWITCH_RES   (`$CsxInitShieldSwitchRes`)
#define `$INSTANCE_NAME`_CSX_SCAN_SHIELD_SWITCH_RES   (`$CsxScanShieldSwitchRes`)

#define `$INSTANCE_NAME`_CSX_MFS_DIVIDER_OFFSET_F1    (`$CsxMFSDividerOffsetF1`u)
#define `$INSTANCE_NAME`_CSX_MFS_DIVIDER_OFFSET_F2    (`$CsxMFSDividerOffsetF2`u)

/* Gesture parameters */
#define `$INSTANCE_NAME`_GES_GLOBAL_EN                (`$GestureGlobalEnable`u)

/*******************************************************************************
* ISX Specific settings
*******************************************************************************/

/* ISX scan method settings */
#define `$INSTANCE_NAME`_ISX_SCANSPEED_DIVIDER        (`$IsxScanSpeedDivider`u)
#define `$INSTANCE_NAME`_ISX_LX_CLK_DIVIDER           (`$IsxTxClockDivider`u)
#define `$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN          (`$IsxIdacAutoCalibrateEnable`u)
#define `$INSTANCE_NAME`_ISX_IDAC_BITS_USED           (`$IsxIdacBitsUsed`u)
#define `$INSTANCE_NAME`_ISX_RAWCOUNT_CAL_LEVEL       (`$IsxRawCountCalibrationLevel`u)
`$IsxConfig`
#define `$INSTANCE_NAME`_ISX_SKIP_OVSMPL_SPECIFIC_NODES (`$IsxSkipAndOversampleNodes`u)
#define `$INSTANCE_NAME`_ISX_MAX_TX_PHASE_LENGTH      (`$IsxMaxTxPhaseLength`u)
#define `$INSTANCE_NAME`_ISX_PIN_COUNT_LX             (`$IsxPinCountLx`u)
/* ISX settings - Fourth-generation HW block */
#define `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN             (`$IsxAutoZeroEnable`u)
#define `$INSTANCE_NAME`_ISX_AUTO_ZERO_TIME           (`$IsxAutoZeroTime`u)
#define `$INSTANCE_NAME`_ISX_FINE_INIT_TIME           (`$IsxFineInitCycles`u)
#define `$INSTANCE_NAME`_ISX_NOISE_METRIC_EN          (`$IsxNoiseMetricEnable`u)
#define `$INSTANCE_NAME`_ISX_NOISE_METRIC_TH          (`$IsxNoiseMetricThreshold`u)
#define `$INSTANCE_NAME`_ISX_INIT_SWITCH_RES          (`$IsxInitSwitchRes`)
#define `$INSTANCE_NAME`_ISX_SCAN_SWITCH_RES          (`$IsxScanSwitchRes`)
#define `$INSTANCE_NAME`_ISX_INIT_SHIELD_SWITCH_RES   (`$IsxInitShieldSwitchRes`)
#define `$INSTANCE_NAME`_ISX_SCAN_SHIELD_SWITCH_RES   (`$IsxScanShieldSwitchRes`)

`$IsxPinRemap`
/*******************************************************************************
* Global Parameter Definitions
*******************************************************************************/

/* Compound section definitions */
#define `$INSTANCE_NAME`_ANY_NONSS_AUTOCAL ((0u != `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN) || \
                                       (0u != `$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN) || \
                                      ((`$INSTANCE_NAME`_CSD_AUTOTUNE == `$INSTANCE_NAME`_CSD_SS_DIS) && (0u != `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN)))
#define `$INSTANCE_NAME`_ANYMODE_AUTOCAL (((0u != `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN) \
                                       || (0u != `$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN)) \
                                       || (0u != `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
/* RAM Global Parameters Definitions */
`$RamGlobalDefines`
`$WidgetDefines`
/* RAM Sensor Parameters Definitions */
`$SensorDefines`
`$GesturesDefines`
/*******************************************************************************
* ADC Specific Macros
*******************************************************************************/
#define `$INSTANCE_NAME`_ADC_RES8BIT                  (8u)
#define `$INSTANCE_NAME`_ADC_RES10BIT                 (10u)

#define `$INSTANCE_NAME`_ADC_FULLRANGE_MODE           (0u)
#define `$INSTANCE_NAME`_ADC_VREF_MODE                (1u)

#define `$INSTANCE_NAME`_ADC_MIN_CHANNELS             (1u)
#define `$INSTANCE_NAME`_ADC_EN                       (`$AdcEnable`u)
#define `$INSTANCE_NAME`_ADC_STANDALONE_EN            (`$AdcStandaloneEnable`u)
#define `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS           (`$AdcTotalChannels`u)
#define `$INSTANCE_NAME`_ADC_RESOLUTION               (`$AdcResolution`)
#define `$INSTANCE_NAME`_ADC_AMUXB_INPUT_EN           (`$AdcAmuxbInputEnable`u)
#define `$INSTANCE_NAME`_ADC_SELECT_AMUXB_CH          (`$AdcSelectAmuxBusChannel`u)
#define `$INSTANCE_NAME`_ADC_AZ_EN                    (`$AdcAzEnable`Lu)
#define `$INSTANCE_NAME`_ADC_AZ_TIME                  (`$AdcAzTime`u)
#define `$INSTANCE_NAME`_ADC_VREF_MV                  (`$AdcVrefMv`u)
#define `$INSTANCE_NAME`_ADC_GAIN                     (`$AdcGain`Lu)
#define `$INSTANCE_NAME`_ADC_IDAC_DEFAULT             (`$AdcIdacDefault`u)
#define `$INSTANCE_NAME`_ADC_MODCLK_DIV_DEFAULT       (`$AdcModClkDivDefault`u)
#define `$INSTANCE_NAME`_ADC_MEASURE_MODE             (`$AdcMeasureMode`)
#define `$INSTANCE_NAME`_ADC_ANALOG_STARTUP_DELAY_US  (`$AdcAnalogStartupDelayUs`u)
#define `$INSTANCE_NAME`_ADC_ACQUISITION_TIME_US      (`$AdcAcqTime`u)

/*******************************************************************************
* Built-In Self-Test Configuration
*******************************************************************************/
#define `$INSTANCE_NAME`_SELF_TEST_EN                   (`$SelfTestEnable`Lu)
#define `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN              (`$SelfTestGlobalCrcEnable`Lu)
#define `$INSTANCE_NAME`_TST_WDGT_CRC_EN                (`$SelfTestWidgetCrcEnable`Lu)
#define `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN        (`$SelfTestBaselineDuplicationEnable`Lu)
#define `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN      (`$SelfTestBaselineRawCountRangeEnable`Lu)
#define `$INSTANCE_NAME`_TST_SNS_SHORT_EN               (`$SelfTestSnsShortEnable`Lu)
#define `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN           (`$SelfTestSns2SnsEnable`Lu)
#define `$INSTANCE_NAME`_TST_SNS_CAP_EN                 (`$SelfTestSnsCapEnable`Lu)
#define `$INSTANCE_NAME`_TST_SH_CAP_EN                  (`$SelfTestShCapEnable`Lu)
#define `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN            (`$SelfTestExtCapEnable`Lu)
#define `$INSTANCE_NAME`_TST_INTERNAL_CAP_EN            (`$SelfTestIntCapEnable`Lu)
#define `$INSTANCE_NAME`_TST_VDDA_EN                    (`$SelfTestVddaEnable`Lu)
#define `$INSTANCE_NAME`_TST_FINE_INIT_TIME             (`$SelfTestFineInitCycles`Lu)
`$SelfTestMaskDefines`
`$SelfTestDefines`
#define `$INSTANCE_NAME`_TST_ANALOG_STARTUP_DELAY_US    (`$SelfTestAnalogStartupDelayUs`u)

/*******************************************************************************
* Gesture Configuration
*******************************************************************************/
#define `$INSTANCE_NAME`_TIMESTAMP_INTERVAL             (`$TimestampInterval`Lu)
#define `$INSTANCE_NAME`_GESTURE_EN_WIDGET_ID           (`$GestureEnWidget`Lu)
#define `$INSTANCE_NAME`_BALLISTIC_EN_WIDGET_ID         (`$BallisticEnWidget`Lu)


#endif /* CY_SENSE_`$INSTANCE_NAME`_CONFIGURATION_H */


/* [] END OF FILE */
