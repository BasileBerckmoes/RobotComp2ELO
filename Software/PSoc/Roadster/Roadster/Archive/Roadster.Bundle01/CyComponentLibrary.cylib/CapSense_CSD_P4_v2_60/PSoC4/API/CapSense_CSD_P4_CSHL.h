/*******************************************************************************
* File Name: `$INSTANCE_NAME`_CSHL.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the High Level APIs
*  for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CSHL_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_CSHL_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*   Condition compilation parameters
***************************************/

#define `$INSTANCE_NAME`_SIGNAL_SIZE                    (`$WidgetResolution`u)
#define `$INSTANCE_NAME`_AUTO_RESET                     (`$SensorAutoReset`u)
#define `$INSTANCE_NAME`_RAW_FILTER_MASK                (`$RawDataFilterType`u)

/* Signal size definition */
#define `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8              (8u)
#define `$INSTANCE_NAME`_SIGNAL_SIZE_UINT16             (16u)

/* Auto reset definition */
#define `$INSTANCE_NAME`_AUTO_RESET_DISABLE             (0u)
#define `$INSTANCE_NAME`_AUTO_RESET_ENABLE              (1u)

/* Mask for RAW and POS filters */
#define `$INSTANCE_NAME`_MEDIAN_FILTER                  (0x01u)
#define `$INSTANCE_NAME`_AVERAGING_FILTER               (0x02u)
#define `$INSTANCE_NAME`_IIR2_FILTER                    (0x04u)
#define `$INSTANCE_NAME`_IIR4_FILTER                    (0x08u)
#define `$INSTANCE_NAME`_JITTER_FILTER                  (0x10u)
#define `$INSTANCE_NAME`_IIR8_FILTER                    (0x20u)
#define `$INSTANCE_NAME`_IIR16_FILTER                   (0x40u)
#define `$INSTANCE_NAME`_RAW_FILTERS_ENABLED            (0x01u)
#define `$INSTANCE_NAME`_RAW_FILTERS_DISABLED           (0x00u)

/***************************************
*           API Constants
***************************************/

/* Widgets constants definition */
`$writerCSHLHFile`


#define `$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT            ( `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT )

#define `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT          ( `$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT + \
                                                         (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u) +\
                                                         (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT * 4u))

#define `$INSTANCE_NAME`_TOTAL_CENTROIDS_BASIC_COUNT    ( `$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT + \
                                                         (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u))

#define `$INSTANCE_NAME`_TOTAL_CENTROID_AXES_COUNT      ( `$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT + \
                                                         (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u) +\
                                                         (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT * 2u))

#define `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT             ( `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT + \
                                                          `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT + \
                                                          `$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT + \
                                                          `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT )

#define `$INSTANCE_NAME`_ANY_POS_FILTER                 ( `$INSTANCE_NAME`_MEDIAN_FILTER | \
                                                          `$INSTANCE_NAME`_AVERAGING_FILTER | \
                                                          `$INSTANCE_NAME`_IIR2_FILTER | \
                                                          `$INSTANCE_NAME`_IIR4_FILTER | \
                                                          `$INSTANCE_NAME`_JITTER_FILTER )

#define `$INSTANCE_NAME`_IS_DIPLEX_SLIDER               ( `$INSTANCE_NAME`_TOTAL_DIPLEXED_SLIDERS_COUNT > 0u)

#define `$INSTANCE_NAME`_IS_NON_DIPLEX_SLIDER           ( (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT - \
                                                           `$INSTANCE_NAME`_TOTAL_DIPLEXED_SLIDERS_COUNT) > 0u)
#define `$INSTANCE_NAME`_ADD_SLIDER_TYPE                ((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) ? \
                                                        ((`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT > 0u) || \
                                                         (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) : 0u)

#define `$INSTANCE_NAME`_TOTAL_PROX_SENSOR_COUNT        (`$INSTANCE_NAME`_TOTAL_PROX_SENSORS_COUNT)

#define `$INSTANCE_NAME`_WIDGETS_TBL_SIZE               ( `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT + \
                                                          `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)

#define `$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE          (`$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT + \
                                                         `$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT +\
                                                         `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u + \
                                                         `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT * 2u +\
                                                         `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT * 2u)

#define `$INSTANCE_NAME`_THRESHOLD_TBL_SIZE         (`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE)
#define `$INSTANCE_NAME`_DEBOUNCE_CNT_TBL_SIZE      (`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE)
#define `$INSTANCE_NAME`_RAW_DATA_INDEX_TBL_SIZE    (`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE +\
                                                     `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)

#define `$INSTANCE_NAME`_RES_MULT                   (256u)


#define `$INSTANCE_NAME`_NOT_WIDGET                     (0xFFFFFFFFu)

/*Types of centroids */
#define `$INSTANCE_NAME`_TYPE_RADIAL_SLIDER             (0x01u)
#define `$INSTANCE_NAME`_TYPE_LINEAR_SLIDER             (0x02u)
#define `$INSTANCE_NAME`_TYPE_GENERIC                   (0xFFu)

/* Defines if sensors or widgets are active */
#define `$INSTANCE_NAME`_SENSOR_IS_ACTIVE               (0x01u)
#define `$INSTANCE_NAME`_SENSOR_1_IS_ACTIVE             (0x01u)
#define `$INSTANCE_NAME`_SENSOR_2_IS_ACTIVE             (0x02u)
#define `$INSTANCE_NAME`_WIDGET_IS_ACTIVE               (0x01u)

/* Defines diplex type of Slider */
#define `$INSTANCE_NAME`_IS_DIPLEX                      (0x80u)

/* Defines fingers positions on Slider  */
#define `$INSTANCE_NAME`_POS_PREV                       (0u)
#define `$INSTANCE_NAME`_POS                            (1u)
#define `$INSTANCE_NAME`_POS_NEXT                       (2u)
#define `$INSTANCE_NAME`_CENTROID_ROUND_VALUE           (0x7F00u)
#define `$INSTANCE_NAME`_MAXIMUM_CENTROID               (0xFFu)

#define `$INSTANCE_NAME`_NEGATIVE_NOISE_THRESHOLD       (`$NegativeNoiseThreshold`u)
#define `$INSTANCE_NAME`_LOW_BASELINE_RESET             (`$LowBaselineReset`u)


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_InitializeSensorBaseline(uint32 sensor);
void `$INSTANCE_NAME`_InitializeAllBaselines(void);
void `$INSTANCE_NAME`_InitializeEnabledBaselines(void);
void `$INSTANCE_NAME`_UpdateSensorBaseline(uint32 sensor);
void `$INSTANCE_NAME`_UpdateBaselineNoThreshold(uint32 sensor);
void `$INSTANCE_NAME`_UpdateEnabledBaselines(void);
void `$INSTANCE_NAME`_UpdateWidgetBaseline(uint32 widget);
uint16 `$INSTANCE_NAME`_GetBaselineData(uint32 sensor);
void `$INSTANCE_NAME`_SetBaselineData(uint32 sensor, uint16 data);
void `$INSTANCE_NAME`_BaseInit(uint32 sensor);

#if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
    uint8 `$INSTANCE_NAME`_FindMaximum(uint8 offset, uint8 count, `$SizeReplacementString` fingerThreshold, const uint8 *diplex);
#else
    uint8 `$INSTANCE_NAME`_FindMaximum(uint8 offset, uint8 count, `$SizeReplacementString` fingerThreshold);
#endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */

#if (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
    uint8 `$INSTANCE_NAME`_CalcCentroid(`$CalcCentroidPrototypeCallReplacementString`uint8 maximum, uint8 offset, \
                                    uint8 count, uint32 resolution, `$SizeReplacementString` noiseThreshold);
#else
    uint8 `$INSTANCE_NAME`_CalcCentroid(`$CalcCentroidPrototypeCallReplacementString`uint8 maximum, uint8 offset, \
                                    uint8 count, uint16 resolution, `$SizeReplacementString` noiseThreshold);
#endif /* (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */


`$SizeReplacementString` `$INSTANCE_NAME`_GetFingerThreshold(uint32 widget);
`$SizeReplacementString` `$INSTANCE_NAME`_GetNoiseThreshold(uint32 widget);
`$SizeReplacementString` `$INSTANCE_NAME`_GetFingerHysteresis(uint32 widget);
`$SizeReplacementString` `$INSTANCE_NAME`_GetNegativeNoiseThreshold(uint32 widget);

#if(`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    void `$INSTANCE_NAME`_SetFingerThreshold(uint32 widget, `$SizeReplacementString` value);
    void `$INSTANCE_NAME`_SetNoiseThreshold(uint32 widget, `$SizeReplacementString` value);
    void `$INSTANCE_NAME`_SetFingerHysteresis(uint32 widget, `$SizeReplacementString` value);
    void `$INSTANCE_NAME`_SetNegativeNoiseThreshold(uint32 widget, `$SizeReplacementString` value);
    void `$INSTANCE_NAME`_SetDebounce(uint32 widget, uint8 value);
    void `$INSTANCE_NAME`_SetLowBaselineReset(uint32 sensor, uint8 value);
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */

`$SizeReplacementString` `$INSTANCE_NAME`_GetDiffCountData(uint32 sensor);
void `$INSTANCE_NAME`_SetDiffCountData(uint32 sensor, `$SizeReplacementString` value);

uint32 `$INSTANCE_NAME`_CheckIsSensorActive(uint32 sensor);
uint32 `$INSTANCE_NAME`_CheckIsWidgetActive(uint32 widget);
uint32 `$INSTANCE_NAME`_CheckIsAnyWidgetActive(void);
void `$INSTANCE_NAME`_EnableWidget(uint32 widget);
void `$INSTANCE_NAME`_DisableWidget(uint32 widget);
void `$INSTANCE_NAME`_EnableRawDataFilters(void);
void `$INSTANCE_NAME`_DisableRawDataFilters(void);

#if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
    uint32 `$INSTANCE_NAME`_GetMatrixButtonPos(uint32 widget, uint8* pos);
#endif /* (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

#if((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 `$INSTANCE_NAME`_GetCentroidPos(uint32 widget);
#endif /* ((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 `$INSTANCE_NAME`_GetRadialCentroidPos(uint32 widget);
#endif /* #if((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)
    uint32 `$INSTANCE_NAME`_GetTouchCentroidPos(uint32 widget, uint16* pos);
#endif /* (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) */

uint32 `$INSTANCE_NAME`_GetWidgetNumber(uint32 sensor);
uint8 `$INSTANCE_NAME`_GetLowBaselineReset(uint32 sensor);
uint8 `$INSTANCE_NAME`_GetDebounce(uint32 widget);

/* Filter function prototypes for High level APIs */

/* Median filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) )
    uint16 `$INSTANCE_NAME`_MedianFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) ) */

/* Averaging filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)) )
    uint16 `$INSTANCE_NAME`_AveragingFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR2Filter(1/2prev + 1/2cur) filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) )
    uint16 `$INSTANCE_NAME`_IIR2Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR4Filter(3/4prev + 1/4cur) filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) )
    uint16 `$INSTANCE_NAME`_IIR4Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR8Filter(7/8prev + 1/8cur) filter function prototype - RawCounts only */
#if (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER))
    uint16 `$INSTANCE_NAME`_IIR8Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK */

/* IIR16Filter(15/16prev + 1/16cur) filter function prototype - RawCounts only */
#if (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER))
    uint16 `$INSTANCE_NAME`_IIR16Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK */

/* JitterFilter filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_TRACKPAD_GEST_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER)))
    uint16 `$INSTANCE_NAME`_JitterFilter(uint16 x1, uint16 x2);
#endif /* ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) || \
       *    (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) )
       *    (0u != (`$INSTANCE_NAME`_TRACKPAD_GEST_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) )
       */


/***************************************
*     Vars with External Linkage
***************************************/
extern uint16 `$INSTANCE_NAME`_sensorBaseline[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern uint8  `$INSTANCE_NAME`_sensorBaselineLow[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern `$SizeReplacementString` `$INSTANCE_NAME`_sensorSignal[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern uint8  `$INSTANCE_NAME`_sensorOnMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK];

extern uint8 `$INSTANCE_NAME`_lowBaselineResetCnt[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern uint8 `$INSTANCE_NAME`_lowBaselineReset[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

/* Generated by Customizer */
#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    extern `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern `$SizeReplacementString` `$INSTANCE_NAME`_noiseThreshold[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern `$SizeReplacementString` `$INSTANCE_NAME`_negativeNoiseThreshold[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern `$SizeReplacementString` `$INSTANCE_NAME`_hysteresis[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern uint8  `$INSTANCE_NAME`_debounce[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
#else
    extern const `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern const `$SizeReplacementString` `$INSTANCE_NAME`_noiseThreshold[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern const `$SizeReplacementString` `$INSTANCE_NAME`_hysteresis[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern const uint8  `$INSTANCE_NAME`_debounce[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */

extern const uint8 `$INSTANCE_NAME`_rawDataIndex[`$INSTANCE_NAME`_RAW_DATA_INDEX_TBL_SIZE];
extern const uint8 `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_RAW_DATA_INDEX_TBL_SIZE];

#if (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT)
    #if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
        extern uint8 `$INSTANCE_NAME`_posFiltersMask[`$INSTANCE_NAME`_TOTAL_CENTROID_AXES_COUNT];
    #else
        extern const uint8 `$INSTANCE_NAME`_posFiltersMask[`$INSTANCE_NAME`_TOTAL_CENTROID_AXES_COUNT];
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */

    extern uint32 `$INSTANCE_NAME`_centroidMult[`$INSTANCE_NAME`_TOTAL_CENTROID_AXES_COUNT];
#endif /* (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) */

/***************************************
*        Obsolete Names
***************************************/
#define `$INSTANCE_NAME`_SensorRaw              `$INSTANCE_NAME`_sensorRaw
#define `$INSTANCE_NAME`_SensorEnableMask       `$INSTANCE_NAME`_sensorEnableMask
#define `$INSTANCE_NAME`_SensorBaseline         `$INSTANCE_NAME`_sensorBaseline
#define `$INSTANCE_NAME`_SensorBaselineLow      `$INSTANCE_NAME`_sensorBaselineLow
#define `$INSTANCE_NAME`_SensorSignal           `$INSTANCE_NAME`_sensorSignal
#define `$INSTANCE_NAME`_SensorOnMask           `$INSTANCE_NAME`_sensorOnMask
#define `$INSTANCE_NAME`_LowBaselineResetCnt    `$INSTANCE_NAME`_lowBaselineResetCnt

#endif /* CY_CAPSENSE_CSD_CSHL_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
