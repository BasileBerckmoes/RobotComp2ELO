/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SF.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of StreetFighter related functions.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_SLDR.h"

/* Initialize widgets counter for new dynamically created buttons  */
uint8 `$INSTANCE_NAME`_widgetsNum = `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT;

#if(`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u)

`$INSTANCE_NAME`_DynamicSliderType `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM];

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DynamicSliderInit
********************************************************************************
*
* Summary:
*  This API initializes the dynamic slider and should be called first.
*  Each dynamic slider will have a unique ID: CapSense_SLIDER_0 and CapSense_SLIDER_1
*  which can be used for other dynamic configured slider APIs.
*
* Parameters:
*  slider0 - this parameter defines the widget of the first slider.
*  slider1 - this parameter defines the widget of the second slider.
*
* Return Value:
*  0 - Sensor is successfully added to the slider.
*  1 - Operation failed. Slider is not dynamically configured when the total number
*  of sensors for both sliders is greater than 10.
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetsNum - this global variable contains the total widgets
*  number. This value increases when one or more sensors are removed from the dynamic slider.
*
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the dynamic sliders parameters.
*
* Side Effects:
*  The default sliders are Linear. The Radial slider will be converted to a linear one.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DynamicSliderInit(uint32 slider0, uint32 slider1)
{
    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].widgetNumber = (uint8)slider0;
    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].ptrGetCentroid = &`$INSTANCE_NAME`_GetCentroidPos;
    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].numberOfSensors = `$INSTANCE_NAME`_numberOfSensors[slider0];
    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].sliderType = `$INSTANCE_NAME`_SLIDER_TYPE_LINEAR;

    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].widgetNumber = (uint8)slider1;
    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].ptrGetCentroid = &`$INSTANCE_NAME`_GetCentroidPos;
    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].numberOfSensors = `$INSTANCE_NAME`_numberOfSensors[slider1];
    `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].sliderType = `$INSTANCE_NAME`_SLIDER_TYPE_LINEAR;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AddSensor
********************************************************************************
*
* Summary:
*  This API adds the sensor to the next free position in the Slider.
*  The number is calculated on the FILO manner: First In, Last Out.
*  This means that the last removed sensor will be added first to the slider.
*
* Parameters:
*  slider - parameter that defines the slider to which the user adds
*  the additional sensor (Slider-0 or Slider-1). When both sliders are
*  connected then slider is defined as 0 (Slider-0).
*
*  sliderResolution - resolution of created slider.
*
* Return Value:
*  0 - Sensor is successfully added to the slider.
*  1 - Operation failed. Sensor is not dynamically added when the
*  total number of sensors for both sliders is greater than 10 or
*  if all sensors are added to the slider.
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetsNum - this global variable contains a total widgets
*  number. This value increases when one or more sensors are removed from the dynamic slider.
*
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the sliders parameters.
*
*  `$INSTANCE_NAME`_widgetNumber[] - This array contains widget Number for given sensor.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_AddSensor(uint32 slider, uint32 sliderResolution)
{
    uint32 sldWidget;
    uint32 retVal;
    uint32 rawIndex;

    retVal = 1u;
    sldWidget = `$INSTANCE_NAME`_widgetNumberSld[slider].widgetNumber;

    if(`$INSTANCE_NAME`_numberOfSensors[sldWidget] < `$INSTANCE_NAME`_widgetNumberSld[slider].numberOfSensors)
    {
        rawIndex = `$INSTANCE_NAME`_GetRawIndex(sldWidget);
        if(slider == `$INSTANCE_NAME`_SLIDER_1)
        {
            `$INSTANCE_NAME`_widgetsNum--;
            `$INSTANCE_NAME`_widgetNumber[rawIndex] = sldWidget;
        }

        `$INSTANCE_NAME`_numberOfSensors[sldWidget]++;
        `$INSTANCE_NAME`_centroidMult[sldWidget] = `$INSTANCE_NAME`_GetCentroidMult(slider, sliderResolution);

        `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorEnableMask, rawIndex, 1u);
        retVal = 0u;
    }
    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RemoveSensor
********************************************************************************
*
* Summary:
*  This API removes the sensor from the last position in the Slider.
*  After calling this API, a new sensor will appear in the disabled state.
*  This sensor can be used as a button when enabled.
*
* Parameters:
*  slider - this parameter defines the slider number for sensor removing.
*
*  sliderResolution - resolution of created slider.
*
* Return Value:
*  Widget number of created button.
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetsNum - this global variable contains the total widgets
*  number. This value increases when one or more sensors are removed from the dynamic slider.
*
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the dynamic sliders' parameters.
*
*  `$INSTANCE_NAME`_numberOfSensors[]  - the number of sensors in the widget.
*
*  `$INSTANCE_NAME`_rawDataIndex[] - contains the 1st sensor position in the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_RemoveSensor(uint32 slider, uint32 sliderResolution)
{
    uint32 sldWidget;
    uint32 rawIndex;
    uint32 newWidgetNumber;

    sldWidget = `$INSTANCE_NAME`_widgetNumberSld[slider].widgetNumber;
    `$INSTANCE_NAME`_numberOfSensors[sldWidget]--;
    `$INSTANCE_NAME`_centroidMult[sldWidget] = `$INSTANCE_NAME`_GetCentroidMult(slider, sliderResolution);

    rawIndex = `$INSTANCE_NAME`_GetRawIndex(sldWidget);

    `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorEnableMask, rawIndex, 0u);

    if(slider == `$INSTANCE_NAME`_SLIDER_1)
    {
        `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_widgetsNum] = 1u;
        `$INSTANCE_NAME`_rawDataIndex[`$INSTANCE_NAME`_widgetsNum] = (uint8)rawIndex;

        `$INSTANCE_NAME`_widgetsNum++;
        newWidgetNumber = (uint32)`$INSTANCE_NAME`_widgetsNum - 1u;
        `$INSTANCE_NAME`_widgetNumber[rawIndex] = newWidgetNumber;
    }
    else
    {
        newWidgetNumber = `$INSTANCE_NAME`_NOT_WIDGET;
    }

    return (newWidgetNumber);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConnectSliders
********************************************************************************
*
* Summary:
*  This API creates the high resolution slider by merging Slider-0
*  and Slider-1 together.
*
* Parameters:
*  mainSlider - This parameter defines the slider number which settings must
*  be applied to the merged slider.
*
*  sliderResolution - resolution of created slider.
*
* Return Value:
*  None.
*
* Global Variables:
*
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the dynamic sliders' parameters.
*
*  `$INSTANCE_NAME`_numberOfSensors[]  - the number of sensors in the widget.
*
*
*   `$INSTANCE_NAME`_hysteresis[]  - this array contains a hysteresis value for each widget.
*
*   `$INSTANCE_NAME`_debounce[]  - this array contains a debounce value for each widget.
*
*   `$INSTANCE_NAME`_centroidMult[]  - this array contains a multiplier for the slider polynomial.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConnectSliders(uint32 mainSlider, uint32 sliderResolution)
{
    uint32 sld0Widget;
    uint32 sld1Widget;

    #if(`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
        uint32 secondSlider;
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */

    CYASSERT(mainSlider < `$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM);

    sld0Widget = `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].widgetNumber;
    sld1Widget = `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].widgetNumber;

    if(`$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].numberOfSensors == `$INSTANCE_NAME`_numberOfSensors[sld0Widget])
    {
    #if(`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
        secondSlider = (mainSlider == `$INSTANCE_NAME`_SLIDER_1) ? `$INSTANCE_NAME`_SLIDER_0 : `$INSTANCE_NAME`_SLIDER_1;
        `$INSTANCE_NAME`_hysteresis[mainSlider] = `$INSTANCE_NAME`_hysteresis[secondSlider];
        `$INSTANCE_NAME`_debounce[mainSlider] = `$INSTANCE_NAME`_debounce[secondSlider];
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */
        `$INSTANCE_NAME`_numberOfSensors[sld0Widget] = `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].numberOfSensors +
                                                       `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].numberOfSensors;

        `$INSTANCE_NAME`_centroidMult[sld0Widget] = `$INSTANCE_NAME`_GetCentroidMult(`$INSTANCE_NAME`_SLIDER_0, sliderResolution);

        `$INSTANCE_NAME`_DisableWidget(sld1Widget);
        `$INSTANCE_NAME`_EnableWidget(sld0Widget);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisconnectSliders
********************************************************************************
*
* Summary:
*  This function converts the high resolution slider into two independent sliders.
*
* Parameters:
*  sld0Resolution - resolution of created slider-0.
*  sld1Resolution - resolution of created slider-1.
*
* Return Value:
*  None.
*
* Global Variables:
*
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the dynamic sliders' parameters.
*
*  `$INSTANCE_NAME`_numberOfSensors[]  - the number of sensors in the widget.
*
*  `$INSTANCE_NAME`_centroidMult[]  - this array contains a multiplier for the slider polynomial.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisconnectSliders(uint32 sld0Resolution, uint32 sld1Resolution)
{
    uint32 sld0Widget;
    uint32 sld1Widget;

    sld0Widget = `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].widgetNumber;
    sld1Widget = `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].widgetNumber;

    `$INSTANCE_NAME`_numberOfSensors[sld0Widget] = `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_0].numberOfSensors;

    `$INSTANCE_NAME`_centroidMult[sld0Widget] = `$INSTANCE_NAME`_GetCentroidMult(`$INSTANCE_NAME`_SLIDER_0, sld0Resolution);
    `$INSTANCE_NAME`_centroidMult[sld1Widget] = `$INSTANCE_NAME`_GetCentroidMult(`$INSTANCE_NAME`_SLIDER_1, sld1Resolution);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConvertToLinearSlider
********************************************************************************
*
* Summary:
*  This function converts a radial slider into a linear slider.
*
* Parameters:
*  slider - slider number.
*
* Return Value:
*  None.
*
* Global Variables:
*
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the dynamic sliders' parameters.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConvertToLinearSlider(uint32 slider)
{
    uint32 widget;
    uint32 numberOfSensors;
    CYASSERT(slider < `$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM);

    widget = `$INSTANCE_NAME`_GetSliderWidgetNumber(slider);
    numberOfSensors = (uint32)`$INSTANCE_NAME`_numberOfSensors[widget];
    `$INSTANCE_NAME`_centroidMult[widget] = (uint16)((uint32)`$INSTANCE_NAME`_centroidMult[widget] * numberOfSensors) / (numberOfSensors - 1u);

    `$INSTANCE_NAME`_widgetNumberSld[slider].sliderType = `$INSTANCE_NAME`_SLIDER_TYPE_LINEAR;
    `$INSTANCE_NAME`_widgetNumberSld[slider].ptrGetCentroid = &`$INSTANCE_NAME`_GetCentroidPos;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConvertToRadialSlider
********************************************************************************
*
* Summary:
*  This function converts a linear slider into a radial slider.
*
* Parameters:
*  slider - slider number.
*
* Return Value:
*  None.
*
* Global Variables:
*
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the dynamic sliders' parameters.
*
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConvertToRadialSlider(uint32 slider)
{
    uint32 widget;
    uint32 numberOfSensors;
    CYASSERT(slider < `$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM);

    widget = `$INSTANCE_NAME`_GetSliderWidgetNumber(slider);
    numberOfSensors = (uint32)`$INSTANCE_NAME`_numberOfSensors[widget];
    `$INSTANCE_NAME`_centroidMult[widget] = (uint16)((uint32)`$INSTANCE_NAME`_centroidMult[widget] * (numberOfSensors - 1u)) / numberOfSensors;

    `$INSTANCE_NAME`_widgetNumberSld[slider].sliderType = `$INSTANCE_NAME`_SLIDER_TYPE_RADIAL;
    `$INSTANCE_NAME`_widgetNumberSld[slider].ptrGetCentroid = &`$INSTANCE_NAME`_GetRadialCentroidPos;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDynamicCentroidPos
********************************************************************************
*
* Summary:
*  Calculates a position value of the dynamic (linear or radial) slider.
*
* Parameters:
*  slider - slider number.
*
* Return Value:
*  uint16: Position value of the dynamic (linear or radial) slider.
*
* Global Variables:
*
*  `$INSTANCE_NAME`_widgetNumberSld - structure with dynamic sliders' parameters.
*
* Side Effects:
*  If any sensors within the slider widget are active, the function returns values
* from zero to the API resolution value set in the CapSense customizer or set by
* CapSense_ConnectSliders, CapSense_DisconnectSliders APIs. If no sensor is active,
* the function returns `$INSTANCE_NAME`_NO_CENTROID (0xFFFF).
* If an error occurs during execution of the centroid/diplexing algorithm,
* the function returns `$INSTANCE_NAME`_NO_CENTROID (0xFFFF).
* There are no checks of the widget argument provided to this function.
* An incorrect widget value causes unexpected position calculations.
* Note If noise counts on the slider segments are greater than the noise threshold,
* this subroutine may generate a false finger press result. The noise threshold
* should be set carefully (high enough above the noise level) so that noise will
* not generate a false finger press.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetDynamicCentroidPos(uint32 slider)
{
    uint16 retVal;
    uint32 widget;

    CYASSERT(slider < `$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM);
    widget = `$INSTANCE_NAME`_widgetNumberSld[slider].widgetNumber;
    retVal = `$INSTANCE_NAME`_widgetNumberSld[slider].ptrGetCentroid(widget);

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSliderWidgetNumber
********************************************************************************
*
* Summary:
*  This API returns a widget number for the slider.
*
* Parameters:
*  sliderNumber: slider index. The value of the index can be from 0 to
*  (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT-1). A slider can be linear or a radial one.
*
* Return:
*  This API returns the widget number of slider.
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumberSld - the structure with the dynamic sliders' parameters.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetSliderWidgetNumber(uint32 slider)
{
    uint32 sliderWidgetNumber;

    CYASSERT(slider < `$INSTANCE_NAME`_DYNAMIC_SLIDERS_NUM);
    sliderWidgetNumber = `$INSTANCE_NAME`_widgetNumberSld[slider].widgetNumber;

    return(sliderWidgetNumber);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRawIndex
********************************************************************************
*
* Summary:
*  The API calculates a Dynamic Slider's widget Number in the
*  `$INSTANCE_NAME`_widgetNumber[] array.
*
* Parameters:
*  sldWidget - dynamic slider Widget ID.
*
* Return:
*  widget Number.
*
* Global Variables:
*  `$INSTANCE_NAME`_rawDataIndex[] - contains the  1st sensor position in the widget.
*  `$INSTANCE_NAME`_numberOfSensors[] - number of sensors in the slider.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetRawIndex(uint32 sldWidget)
{
    return ((uint32)`$INSTANCE_NAME`_rawDataIndex[sldWidget] + (uint32)`$INSTANCE_NAME`_numberOfSensors[sldWidget]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCentroidMult
********************************************************************************
*
* Summary:
*  Calculates a Multiplier for the slider polynomial.
*
* Parameters:
*  sldWidget - dynamic slider Widget ID.
*  sldResolution - resolution of slider.
*
* Return:
*  Multiplier for slider polynomial.
*
* Global Variables:
*  `$INSTANCE_NAME`_numberOfSensors[] - the number of sensors in the slider.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetCentroidMult(uint32 slider, uint32 sldResolution)
{
    uint8 sliderCoefficient;
    uint16 retVal;
    uint32 sldWidget;

    sliderCoefficient = `$INSTANCE_NAME`_widgetNumberSld[slider].sliderType;

    sldWidget = `$INSTANCE_NAME`_GetSliderWidgetNumber(slider);
    retVal    = (uint16)((sldResolution * (uint32)`$INSTANCE_NAME`_RES_MULT) /
                        ((uint32)`$INSTANCE_NAME`_numberOfSensors[sldWidget] - sliderCoefficient));

    return (retVal);
}

#endif /* (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u) */


/* [] END OF FILE */
