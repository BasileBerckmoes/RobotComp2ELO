/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SF.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and structure declarations for the
*  StreetFighter related APIs for the CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_SF_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_SF_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"

#define `$INSTANCE_NAME`_RES_MULT               (256u)

#define `$INSTANCE_NAME`_MAX_SLIDER_SIZE        (10u)
#define `$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM    (2u)

#define `$INSTANCE_NAME`_MAIN_SLIDER            (1u)
#define `$INSTANCE_NAME`_SECOND_SLIDER          (0u)

#define `$INSTANCE_NAME`_SLIDER_0               (0u)
#define `$INSTANCE_NAME`_SLIDER_1               (1u)

#define `$INSTANCE_NAME`_SLIDER_TYPE_LINEAR     (1u)
#define `$INSTANCE_NAME`_SLIDER_TYPE_RADIAL     (0u)

#define `$INSTANCE_NAME`_NO_CENTROID            (0xFFFFu)

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
    #include "`$INSTANCE_NAME`_CSHL.h"

    #if(`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
        extern uint8 `$INSTANCE_NAME`_widgetResolution[`$INSTANCE_NAME`_RESOLUTIONS_TBL_SIZE];
        extern uint8 `$INSTANCE_NAME`_debounce[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
        extern `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE `$INSTANCE_NAME`_hysteresis[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */

    #if((0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER) && (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u))
        extern uint8 `$INSTANCE_NAME`_rawDataIndex[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE + `$INSTANCE_NAME`_MAX_SLIDER_SIZE];
        extern uint8 `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE + `$INSTANCE_NAME`_MAX_SLIDER_SIZE];
    #else
        extern const uint8 `$INSTANCE_NAME`_rawDataIndex[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE];
        extern const uint8 `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE];
    #endif /* ((0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER) && (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u)) */

    #if(0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
        extern uint16 `$INSTANCE_NAME`_centroidMult[`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT];
    #endif /* (0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT) */

#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

extern uint8 `$INSTANCE_NAME`_sensorEnableMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK];

#if(`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u)

typedef struct{
    uint16 (*ptrGetCentroid)(uint32 widget);
    uint8 widgetNumber;
    uint8 numberOfSensors;
    uint8 sliderType;
}`$INSTANCE_NAME`_DynamicSliderType;

extern `$INSTANCE_NAME`_DynamicSliderType `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM];

void `$INSTANCE_NAME`_DynamicSliderInit(uint32 slider0, uint32 slider1);
uint32 `$INSTANCE_NAME`_AddSensor(uint32 slider, uint32 sliderResolution);
uint32 `$INSTANCE_NAME`_RemoveSensor(uint32 slider, uint32 sliderResolution);
uint16 `$INSTANCE_NAME`_GetDynamicCentroidPos(uint32 slider);
void `$INSTANCE_NAME`_ConvertToLinearSlider(uint32 slider);
void `$INSTANCE_NAME`_ConvertToRadialSlider(uint32 slider);
void `$INSTANCE_NAME`_ConnectSliders(uint32 mainSlider, uint32 sliderResolution);
void `$INSTANCE_NAME`_DisconnectSliders(uint32 sld0Resolution, uint32 sld1Resolution);
uint32 `$INSTANCE_NAME`_GetSliderWidgetNumber(uint32 slider);

uint32 `$INSTANCE_NAME`_GetRawIndex(uint32 sldWidget);
uint16 `$INSTANCE_NAME`_GetCentroidMult(uint32 slider, uint32 sldResolution);

extern uint8 `$INSTANCE_NAME`_widgetsNum;

#endif /* (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u) */

#endif  /* (CY_CAPSENSE_CSD_SF_`$INSTANCE_NAME`_H)*/


/* [] END OF FILE */
