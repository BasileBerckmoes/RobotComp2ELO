/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SMS.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of a wrapper between the CapSense CSD component
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_SMS.h"
#include "`$INSTANCE_NAME`_PVT.h"

#if(0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER)
    #include "`$INSTANCE_NAME`_SLDR.h"
#endif /* (0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER) */

#include "cytypes.h"

#define `$INSTANCE_NAME`_PRS_CORRECTION_DIVIDER (4u)
#define `$INSTANCE_NAME`_MAX_RESOLUTION         (65535u)
#define `$INSTANCE_NAME`_SENSITIVITY_DIVIDER    (10u)

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
    #define `$INSTANCE_NAME`_SENSETIVITY_FACTOR (1228u)
#else
    #define `$INSTANCE_NAME`_SENSETIVITY_FACTOR (2456u)
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
    extern uint8 `$INSTANCE_NAME`_prescalersTuningDone;
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */


/*  Real Charge Divider values */
#if (0u != CY_PSOC4SF)
    #if (CYDEV_BCLK__HFCLK__MHZ >= 12u)
        const uint8 prescalerTable[] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >= 6u)
        const uint8 prescalerTable[] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u
        };
    #else
        const uint8 prescalerTable[] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
#else
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        const uint8 prescalerTable[] = {
            4u,     4u,     4u,    8u,    8u,    8u,    8u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        const uint8 prescalerTable[] = {
            2u,     2u,     2u,    4u,    4u,    4u,    4u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u
        };
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        const uint8 prescalerTable[] = {
            2u,     2u,     2u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* (0u == CY_PSOC4SF) */

extern const uint8 `$INSTANCE_NAME`_proxTouchThresMap[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE];

extern uint8 `$INSTANCE_NAME`_thresholdMode;

extern uint16 `$INSTANCE_NAME`_sensorRaw[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];

extern uint8 `$INSTANCE_NAME`_widgetResolution[`$INSTANCE_NAME`_RESOLUTIONS_TBL_SIZE];
extern uint8 `$INSTANCE_NAME`_widgetNumber[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

#if((0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER) && (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u))
    extern uint8 `$INSTANCE_NAME`_rawDataIndex[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE + `$INSTANCE_NAME`_MAX_SLIDER_SIZE];
    extern uint8 `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE + `$INSTANCE_NAME`_MAX_SLIDER_SIZE];
#else
    extern const uint8 `$INSTANCE_NAME`_rawDataIndex[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE];
    extern const uint8 `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_WIDGETS_TBL_SIZE];
#endif /* ((0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER) && (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u)) */

extern uint8 `$INSTANCE_NAME`_modulationIDAC[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
extern uint8 `$INSTANCE_NAME`_compensationIDAC[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];


extern uint8 `$INSTANCE_NAME`_senseClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal;
#else
    extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    extern const uint8 `$INSTANCE_NAME`_ImmSnsMap[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
#endif /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

extern uint8 `$INSTANCE_NAME`_proxEnableMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK];
extern uint8 `$INSTANCE_NAME`_sensorEnableMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK];

extern uint8 `$INSTANCE_NAME`_sensorBaselineLow[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];

extern `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[`$INSTANCE_NAME`_THRESHOLD_TBL_SIZE];
extern `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE `$INSTANCE_NAME`_noiseThreshold[`$INSTANCE_NAME`_THRESHOLD_TBL_SIZE];
extern `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE `$INSTANCE_NAME`_hysteresis[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
extern `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE `$INSTANCE_NAME`_negativeNoiseThreshold[`$INSTANCE_NAME`_THRESHOLD_TBL_SIZE];

extern uint8 `$INSTANCE_NAME`_highImmunityEnable;

uint8 baNoiseEnvelope[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
uint8 baRunningDifference[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
uint8 baSignRegister[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
uint16 waSampleMin[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
uint16 waSampleMax[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
uint16 waPreviousSample[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
uint8 baK[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
uint8 baSpeed[((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];

`$writerCAutoSensitivity`

`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 `$INSTANCE_NAME`_config;
`$INSTANCE_NAME`_CONFIG_TYPE_POINTERS_SF_v1_0 const `$INSTANCE_NAME`_configPointers = {
    `$INSTANCE_NAME`_PROXIMITY_K_SCALING_FACTOR,
    `$INSTANCE_NAME`_modulationIDAC,
    `$INSTANCE_NAME`_compensationIDAC,
     SMS_LIB_SensorSensitivity,
    `$INSTANCE_NAME`_senseClkDividerVal,
    &`$INSTANCE_NAME`_sampleClkDividerVal,
    `$INSTANCE_NAME`_widgetNumber,
    `$INSTANCE_NAME`_sensorEnableMask,
    `$INSTANCE_NAME`_widgetResolution,
    (const uint8  *)`$INSTANCE_NAME`_rawDataIndex,
    (const uint8  *)`$INSTANCE_NAME`_numberOfSensors,
    #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        `$INSTANCE_NAME`_ImmSnsMap,
    #else
        0u,
    #endif /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */
    `$INSTANCE_NAME`_proxEnableMask,
    &`$INSTANCE_NAME`_GetSensorRaw,
    &`$INSTANCE_NAME`_PreScan,
    &`$INSTANCE_NAME`_ChangeImoFreq,
    &`$INSTANCE_NAME`_ReadSensorRaw,
    &`$INSTANCE_NAME`_GetBitValue,
    &`$INSTANCE_NAME`_SetBitValue
};

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AutoTuneInit
********************************************************************************
*
* Summary:
*  Initialises the tuning configuration structure.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_highImmunityEnable: Used to notify whether the Immunity Level
*   is high.
*   `$INSTANCE_NAME`_config: the structure which contains the configuration parameters
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_AutoTuneInit(void)
{
    if(`$INSTANCE_NAME`_highImmunityEnable == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    {
        `$INSTANCE_NAME`_config.totalScanslotsNum = `$INSTANCE_NAME`_IMMUNITY_ENABLE_SCANSLOTS_NUM;
    }
    else
    {
        `$INSTANCE_NAME`_config.totalScanslotsNum = `$INSTANCE_NAME`_IMMUNITY_DISABLE_SCANSLOTS_NUM;
    }

    #if((`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u) && (0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER))
        `$INSTANCE_NAME`_config.totalWidgetsNum = `$INSTANCE_NAME`_widgetsNum;
    #else
        `$INSTANCE_NAME`_config.totalWidgetsNum = `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT;
    #endif /* ((`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u) && (0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER)) */

    `$INSTANCE_NAME`_config.totalSensorsNum = `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT;
    `$INSTANCE_NAME`_config.totalButtonsNum = `$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT;
    `$INSTANCE_NAME`_config.totalSlidersNum = `$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT + `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT + `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT;
    `$INSTANCE_NAME`_config.totalGenericsNum = `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT;
    `$INSTANCE_NAME`_config.immunityLevel = `$INSTANCE_NAME`_highImmunityEnable;
    `$INSTANCE_NAME`_config.immunityChannelSize = `$INSTANCE_NAME`_IMMUNITY_CHANNEL_SIZE;

    #if(0u != CY_PSOC4SF)
        `$INSTANCE_NAME`_config.immunity0 = (uint8)CY_SYS_CLK_IMO_TRIM1_REG;
        if(`$INSTANCE_NAME`_config.immunity0 < 40u)
        {
            `$INSTANCE_NAME`_config.immunity1 = `$INSTANCE_NAME`_config.immunity0 + 20u;
            `$INSTANCE_NAME`_config.immunity2 = `$INSTANCE_NAME`_config.immunity0 + 40u;
        }
        else if(`$INSTANCE_NAME`_config.immunity0 < 215u)
        {
            `$INSTANCE_NAME`_config.immunity1 = `$INSTANCE_NAME`_config.immunity0 - 20u;
            `$INSTANCE_NAME`_config.immunity2 = `$INSTANCE_NAME`_config.immunity0 + 20u;
        }
        else
        {
            `$INSTANCE_NAME`_config.immunity1 = `$INSTANCE_NAME`_config.immunity0 - 20u;
            `$INSTANCE_NAME`_config.immunity2 = `$INSTANCE_NAME`_config.immunity0 - 40u;
        }
    #else
        `$INSTANCE_NAME`_config.immunity0 = `$INSTANCE_NAME`_CH0_BCLK_HFCLK_MHZ;
        `$INSTANCE_NAME`_config.immunity1 = `$INSTANCE_NAME`_CH1_BCLK_HFCLK_MHZ;
        `$INSTANCE_NAME`_config.immunity2 = `$INSTANCE_NAME`_CH2_BCLK_HFCLK_MHZ;
    #endif /* (0u != CY_PSOC4SF) */

    `$INSTANCE_NAME`_config.imoFreq_MHz = CYDEV_BCLK__HFCLK__MHZ;
    `$INSTANCE_NAME`_config.sensetivitySeed = `$INSTANCE_NAME`_SENSETIVITY_FACTOR;
    `$INSTANCE_NAME`_config.pointers = &`$INSTANCE_NAME`_configPointers;
}



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AutoTune
********************************************************************************
*
* Summary:
*  Provides a tuning procedure for all the sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   `$INSTANCE_NAME`_config: a structure which contains the configuration parameters
*   `$INSTANCE_NAME`_senseClkDividerVal[]: used to store the Analog Switch
*    dividers for each sensor.
*   `$INSTANCE_NAME`_sampleClkDividerVal: this variable used to store the
*    Analog Switch divider for all the sensors.
*   `$INSTANCE_NAME`_prescalersTuningDone - used to notify the Tuner GUI that
*   tuning of pre-scalers  is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_AutoTune(void)
{
    uint32 curSensor;
    uint32 widget;

    `$INSTANCE_NAME`_AutoTuneInit();

    `$INSTANCE_NAME`_SetAnalogSwitchesSrcDirect();

    for(widget = 0u; widget < `$INSTANCE_NAME`_config.totalWidgetsNum; widget++)
    {
        `$INSTANCE_NAME`_widgetResolution[widget] = `$INSTANCE_NAME`_CALIBRATION_RESOLUTION;
    }

    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        `$INSTANCE_NAME`_senseClkDividerVal[curSensor] = `$INSTANCE_NAME`_CALIBRATION_ASD;
        `$INSTANCE_NAME`_sampleClkDividerVal = `$INSTANCE_NAME`_CALIBRATION_MD;
    }

    `$INSTANCE_NAME`_DisableBaselineIDAC();

    CalibrateSensors_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_CAL_RAW_COUNT);
    `$INSTANCE_NAME`_NormalizeWidgets(`$INSTANCE_NAME`_END_OF_WIDGETS_INDEX, `$INSTANCE_NAME`_modulationIDAC);

    TunePrescalers_SF_v1_0(&`$INSTANCE_NAME`_config);
   `$INSTANCE_NAME`_sampleClkDividerVal = `$INSTANCE_NAME`_SCANNING_MD;

    #if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
        `$INSTANCE_NAME`_prescalersTuningDone = 1u;
    #endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

    CalibrateSensors_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_CAL_RAW_COUNT);
    `$INSTANCE_NAME`_NormalizeWidgets(`$INSTANCE_NAME`_END_OF_WIDGETS_INDEX, `$INSTANCE_NAME`_modulationIDAC);

    TuneSensitivity_SF_v1_0(&`$INSTANCE_NAME`_config);

    `$INSTANCE_NAME`_EnableBaselineIDAC(&`$INSTANCE_NAME`_config);

    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        `$INSTANCE_NAME`_UpdateThresholds(curSensor);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateThresholds
********************************************************************************
*
* Summary:
*  The API updates the Finger Threshold, Hysteresis, Noise Threshold, and
*  Negative Noise Threshold in the AutoTuning (Smartsense) Mode.
*  When the automatic threshold is enabled, this API calculates the threshold parameters
*  based on the measured noise envelope of the sensor. In this mode, the API calculates
*  the finger threshold for a given sensor along with other thresholds.
*  When the automatic threshold is disabled, this API does not calculate the
*  finger threshold. All other thresholds are calculated by this API based on
*  the finger threshold value set by the caller. In this mode, the API expects the caller
*  to set an appropriate finger threshold values prior to calling this API.
*
* Parameters:
*  sensor: sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumber[] - contains widget Number for a given sensor.
*  `$INSTANCE_NAME`_proxEnableMask[] - contains a proximity sensor scanning state for SF.
*  CapSense_proxEnableMask[0] contains the masked bits for proximity sensors
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_proxTouchThresMap[] - defines a proximity sensor number.
*  For other sensors the array element equals 255.
*  `$INSTANCE_NAME`_numberOfSensors[widget] - the number of sensors in the widget.
*  `$INSTANCE_NAME`_thresholdMode - defines which threshold mode should be used
*   in the SmartSense algorithm.
*   `$INSTANCE_NAME`_fingerThreshold[] - contains the level of signal for each sensor
*   that determines if a finger is present on the sensor.
*   `$INSTANCE_NAME`_negativeNoiseThreshold[] - the negative Noise Threshold
*   `$INSTANCE_NAME`_hysteresis[] - the array with a hysteresis values.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_UpdateThresholds(uint32 sensor)
{
    `$SizeReplacementString` fingerThreshold;

    uint32 widget;
    uint32 thresholdModeMask;
    uint32 hysteresisIndex;

    widget = `$INSTANCE_NAME`_widgetNumber[sensor];

    #if(0u != `$INSTANCE_NAME`_TOTAL_PROX_SENSORS_COUNT)

        if(((`$INSTANCE_NAME`_numberOfSensors[widget] > 1u) && (0u != `$INSTANCE_NAME`_SLIDER_THRESHOLDS_MANUAL)) ||
           (`$INSTANCE_NAME`_highImmunityEnable == `$INSTANCE_NAME`_IMMUNITY_HIGH))
        {
            thresholdModeMask = `$INSTANCE_NAME`_THRESHOLD_MANUAL;
        }
        else
        {
            thresholdModeMask = (0u != `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_proxEnableMask, sensor)) ? `$INSTANCE_NAME`_PROX_THRESHOLD_AUTO_FLAG :
                                                                                                                `$INSTANCE_NAME`_THRESHOLD_AUTO_FLAG;
        }

    #else
        if(((`$INSTANCE_NAME`_numberOfSensors[widget] > 1u) && (0u != `$INSTANCE_NAME`_SLIDER_THRESHOLDS_MANUAL)) ||
           (`$INSTANCE_NAME`_highImmunityEnable == `$INSTANCE_NAME`_IMMUNITY_HIGH))
        {
            thresholdModeMask = `$INSTANCE_NAME`_THRESHOLD_MANUAL;
        }
        else
        {
            thresholdModeMask = `$INSTANCE_NAME`_THRESHOLD_AUTO_FLAG;
        }
    #endif /* (0u != `$INSTANCE_NAME`_TOTAL_PROX_SENSORS_COUNT) */

    if(((`$INSTANCE_NAME`_thresholdMode & thresholdModeMask) != 0u))
    {
        /* Calculate Finger Threshold and Noise Threshold with Smartsense (automatic) */
        CalculateThresholds_SF_v1_0(&`$INSTANCE_NAME`_config, (uint8)sensor, `$INSTANCE_NAME`_sensorRaw, (uint8)widget, `$INSTANCE_NAME`_fingerThreshold, `$INSTANCE_NAME`_noiseThreshold);
    }

    fingerThreshold = `$INSTANCE_NAME`_fingerThreshold[widget];
    hysteresisIndex = `$INSTANCE_NAME`_GetCommonParamIndex(widget);

    if((`$INSTANCE_NAME`_thresholdMode & thresholdModeMask) == 0u)
    {
        /* Update Threshold manually (flexible) */
        `$INSTANCE_NAME`_noiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        `$INSTANCE_NAME`_negativeNoiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        `$INSTANCE_NAME`_hysteresis[hysteresisIndex] = (uint8)(fingerThreshold >> 3u);
    }
    else
    {
        /* Update Threshold based on calculated with Smartsense (automatic) */
        `$INSTANCE_NAME`_negativeNoiseThreshold[widget] = `$INSTANCE_NAME`_noiseThreshold[widget];

        if(fingerThreshold < `$INSTANCE_NAME`_THRESHOLD_1)
        {
            `$INSTANCE_NAME`_hysteresis[hysteresisIndex] = (uint8)(fingerThreshold >> 3u);
        }
        else if(fingerThreshold <  `$INSTANCE_NAME`_THRESHOLD_2)
        {
            `$INSTANCE_NAME`_hysteresis[hysteresisIndex] = (uint8)(fingerThreshold >> 4u);
        }
        else if(fingerThreshold <  `$INSTANCE_NAME`_THRESHOLD_3)
        {
            `$INSTANCE_NAME`_hysteresis[hysteresisIndex] = (uint8)(fingerThreshold >> 5u);
        }
        else if(fingerThreshold <  `$INSTANCE_NAME`_THRESHOLD_4)
        {
            `$INSTANCE_NAME`_hysteresis[hysteresisIndex] = (uint8)(fingerThreshold >> 6u);
        }
        else
        {
            `$INSTANCE_NAME`_hysteresis[hysteresisIndex] = 0u;
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensorRaw
********************************************************************************
*
* Summary:
*  The API updates and gets uprated raw data from the sensor.
*
* Parameters:
*  sensor - Sensor number.
*
* Return:
*  Returns current raw data value for defined sensor number.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16  `$INSTANCE_NAME`_GetSensorRaw(uint32 sensor)
{
    uint32 curSample;
    uint32 avgVal = 0u;

    for(curSample = 0u; curSample < `$INSTANCE_NAME`_AVG_SAMPLES_NUM; curSample++)
    {

        `$INSTANCE_NAME`_ScanSensor((uint32)sensor);
        while(`$INSTANCE_NAME`_IsBusy() == 1u)
        {
            /* Wait while sensor is busy */
        }
        avgVal += `$INSTANCE_NAME`_ReadSensorRaw((uint32)sensor);
    }

    return((uint16)(avgVal / `$INSTANCE_NAME`_AVG_SAMPLES_NUM));
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNoiseEnvelope
********************************************************************************
*
* Summary:
*  This function returns the noise value of the
*  component.
*
* Parameters:
*  sensor - Sensor number.
*
* Return:
*  The noise envelope value of the sensor
*  indicated by the argument.
*
* Global Variables:
*  baNoiseEnvelope[] - the array with Noise Envelope.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetNoiseEnvelope(uint32 sensor)
{
    #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        uint32 immunitySensorIndex;
        uint32 baNoiseEnvelope0;
        uint32 baNoiseEnvelope1;
        uint32 baNoiseEnvelope2;

        baNoiseEnvelope0 = baNoiseEnvelope[sensor];
        immunitySensorIndex = `$INSTANCE_NAME`_GetImmunityIndex(sensor, 1u);
        baNoiseEnvelope1 = baNoiseEnvelope[immunitySensorIndex];
        immunitySensorIndex = `$INSTANCE_NAME`_GetImmunityIndex(sensor, 2u);
        baNoiseEnvelope2 = baNoiseEnvelope[immunitySensorIndex];
        immunitySensorIndex = `$INSTANCE_NAME`_MedianFilter(baNoiseEnvelope0, baNoiseEnvelope1, baNoiseEnvelope2);
        return((uint16)(immunitySensorIndex << 1u) + 1u);
    #else
        return((uint16)(baNoiseEnvelope[sensor] << 1u) + 1u);
    #endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_NormalizeWidgets
********************************************************************************
*
* Summary:
*  This API aligns all the widget parameters to the maximum parameter.
*
* Parameters:
*  uint32 widgetsNum: Number of widgets.
*  uint8 *datsPrt: pointer ro array with widget parameters.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_numberOfSensors[] - the number of sensors in the widget.
*  `$INSTANCE_NAME`_rawDataIndex[currentWidget] - contains the  1st sensor
*  position in the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr)
{
    uint32 currentWidget;
    uint32 currentSensor;
    uint32 lastSensor;
    uint32 sensorsPerWidget;
    uint32 maxPerWidget;

    for(currentWidget = 0u; currentWidget < widgetsNum; currentWidget++)
    {
        maxPerWidget = 0u;

        sensorsPerWidget = `$INSTANCE_NAME`_numberOfSensors[currentWidget];
        currentSensor = `$INSTANCE_NAME`_rawDataIndex[currentWidget];
        lastSensor = currentSensor + sensorsPerWidget;

        while(currentSensor < lastSensor)
        {
            if(maxPerWidget < dataPtr[currentSensor])
            {
                maxPerWidget = dataPtr[currentSensor];
            }
            currentSensor++;
        }

        currentSensor = `$INSTANCE_NAME`_rawDataIndex[currentWidget];

        while(currentSensor < lastSensor)
        {
            dataPtr[currentSensor] = (uint8)maxPerWidget;
            currentSensor++;
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAnalogSwitchesSrcDirect
********************************************************************************
*
* Summary:
*  This API switches the charge clock source to prescaler.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetAnalogSwitchesSrcDirect(void)
{
    `$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_PRS_SELECT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSensitivity
********************************************************************************
*
* Summary:
*  This API sets a sensitivity value for the sensor. The sensitivity
*  value is used during the auto-tuning algorithm executed as part of the CapSense_Start API.
*  This API is called by the application layer prior to calling the CapSense_Start API.
*  Calling this API after execution of CapSense_Start API has no effect.
*
* Parameters:
*  sensor  Sensor index
*  data    Sensitivity of the sensor. Possible values are below
*  1 - 0.1pf sensitivity
*  2 - 0.2pf sensitivity
*  3 - 0.3pf sensitivity
*  4 - 0.4pf sensitivity
*  5 - 0.5pf sensitivity
*  6 - 0.6pf sensitivity
*  7 - 0.7pf sensitivity
*  8 - 0.8pf sensitivity
*  9 - 0.9pf sensitivity
*  10 - 1.0pf sensitivity
*  All other values, set sensitivity to 1.0pf
*
*  Return Value:
*   None
*
* Global Variables:
* SMS_LIB_SensorSensitivity[] - this 8-bits array contains Sensitivity in the LSB nibble
*                                and a Noise Reset Counter value in the MSB nibble.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSensitivity(uint32 sensor, uint32 value)
{
    if(value > 10u)
    {
        value = 10u;
    }

    /* Clear SensorSensitivity value in LSB nibble */
    SMS_LIB_SensorSensitivity[sensor] &= ~`$INSTANCE_NAME`_SENSITIVITY_MASK;
    /* Set SensorSensitivity value in LSB nibble */
    SMS_LIB_SensorSensitivity[sensor] |= (uint8)value;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensitivityCoefficient
********************************************************************************
*
* Summary:
*  This API returns the K coefficient for the appropriate sensor.
*
* Parameters:
*  sensor:  Sensor index
*
*  Return Value:
*   K - value for the appropriate sensor.
*
* Global Variables:
*  baK[] - this 8-bits array contains the K value for each sensor.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetSensitivityCoefficient(uint32 sensor)
{
    return (baK[sensor]);
}


#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

/* [] END OF FILE */
