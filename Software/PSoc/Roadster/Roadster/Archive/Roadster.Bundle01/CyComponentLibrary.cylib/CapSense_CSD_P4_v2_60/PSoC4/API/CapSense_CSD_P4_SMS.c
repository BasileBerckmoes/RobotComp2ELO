/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SMS.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of wrapper between CapSense CSD component
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_SMS.h"
#include "`$INSTANCE_NAME`_PVT.h"

#include "cytypes.h"

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)


/*  Real Charge Divider values */
#if ((0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) && (0u == CY_PSOC4_4000))
    /*  Dividers are not chained */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            4u,     4u,     4u,    8u,    8u,    8u,    8u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u
        };
    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            2u,     2u,     2u,    4u,    4u,    4u,    4u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u
        };
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */

#elif (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
    /*  Dividers are not chained (PSoC 4000) */
    #if (CYDEV_BCLK__HFCLK__MHZ >= 12u)
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >= 6u)
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u
        };
    #else
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */

#else
    /*  Dividers are chained (PSoC 4100, PSoC 4200) */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            2u,     2u,     2u,    4u,    4u,    4u,    4u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        const uint8 `$INSTANCE_NAME`_prescalerTable[`$INSTANCE_NAME`_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* ((0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) && (0u == CY_PSOC4_4000)) */


uint8 `$INSTANCE_NAME`_noiseEnvelopeTbl[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
uint8 `$INSTANCE_NAME`_runningDifferenceTbl[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
uint8 `$INSTANCE_NAME`_signRegisterTbl[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
uint16 `$INSTANCE_NAME`_sampleMinTbl[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
uint16 `$INSTANCE_NAME`_sampleMaxTbl[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
uint16 `$INSTANCE_NAME`_previousSampleTbl[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
uint8 `$INSTANCE_NAME`_kValueTbl[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

`$writerCAutoSensitivity`

`$INSTANCE_NAME`_CONFIG_TYPE_P4_v2_60 `$INSTANCE_NAME`_config;
`$INSTANCE_NAME`_CONFIG_TYPE_POINTERS_P4_v2_60 const `$INSTANCE_NAME`_configPointers = {
    `$INSTANCE_NAME`_modulationIDAC,
    `$INSTANCE_NAME`_compensationIDAC,
    `$INSTANCE_NAME`_sensorSensitivity,
    `$INSTANCE_NAME`_senseClkDividerVal,
    `$INSTANCE_NAME`_sampleClkDividerVal,
    `$INSTANCE_NAME`_widgetNumber,
    `$INSTANCE_NAME`_widgetResolution,
    `$INSTANCE_NAME`_noiseEnvelopeTbl,
    `$INSTANCE_NAME`_runningDifferenceTbl,
    `$INSTANCE_NAME`_signRegisterTbl,
    `$INSTANCE_NAME`_sampleMinTbl,
    `$INSTANCE_NAME`_sampleMaxTbl,
    `$INSTANCE_NAME`_previousSampleTbl,
    `$INSTANCE_NAME`_kValueTbl,
    `$INSTANCE_NAME`_scanSpeedTbl,
    `$INSTANCE_NAME`_prescalerTable,
    (const uint8  *)`$INSTANCE_NAME`_rawDataIndex,
    (const uint8  *)`$INSTANCE_NAME`_numberOfSensors,
    &`$INSTANCE_NAME`_GetSensorRaw,
    &`$INSTANCE_NAME`_PreScan,
    &`$INSTANCE_NAME`_ReadSensorRaw,
    &`$INSTANCE_NAME`_GetBitValue,
    &`$INSTANCE_NAME`_SetBitValue
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AutoTune
********************************************************************************
*
* Summary:
*  Provides the tuning procedure for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   `$INSTANCE_NAME`_config: the structure which contains configuration parameters
*   `$INSTANCE_NAME`_senseClkDividerVal[]: used to store the Analog Switch
*   dividers for each sensor.
*   `$INSTANCE_NAME`_senseClkDividerVal[]: used to store the
*    Analog Switch divider for all sensors.
*   `$INSTANCE_NAME`_prescalersTuningDone - used to notify the Tuner GUI that
*   the pre-scalers tuning  is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_AutoTune(void)
{
    uint32 curSensor;
    uint32 widget;

    `$INSTANCE_NAME`_config.totalScanslotsNum = `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT;
    `$INSTANCE_NAME`_config.totalWidgetsNum = `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX;
    `$INSTANCE_NAME`_config.totalSensorsNum = `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT;

    `$INSTANCE_NAME`_config.hfclkFreq_MHz = CYDEV_BCLK__HFCLK__MHZ;
    `$INSTANCE_NAME`_config.sensetivitySeed = `$INSTANCE_NAME`_SENSETIVITY_FACTOR;

    `$INSTANCE_NAME`_config.pointers = &`$INSTANCE_NAME`_configPointers;

    `$INSTANCE_NAME`_SetAnalogSwitchesSrcDirect();

    for(widget = 0u; widget < `$INSTANCE_NAME`_config.totalWidgetsNum; widget++)
    {
        `$INSTANCE_NAME`_widgetResolution[widget] = `$INSTANCE_NAME`_CALIBRATION_RESOLUTION;
    }


    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        `$INSTANCE_NAME`_senseClkDividerVal[curSensor] = `$INSTANCE_NAME`_CALIBRATION_ASD;
        `$INSTANCE_NAME`_sampleClkDividerVal[curSensor] = `$INSTANCE_NAME`_CALIBRATION_MD;
    }

    `$INSTANCE_NAME`_DisableBaselineIDAC();

    CalibrateSensors_P4_v2_60(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_CAL_RAW_COUNT);

    #if(0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
        `$INSTANCE_NAME`_NormalizeWidgets(`$INSTANCE_NAME`_END_OF_WIDGETS_INDEX, `$INSTANCE_NAME`_modulationIDAC);
    #endif /* (0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)  */

    TunePrescalers_P4_v2_60(&`$INSTANCE_NAME`_config);

    #if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
        `$INSTANCE_NAME`_prescalersTuningDone = 1u;
    #endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

    CalibrateSensors_P4_v2_60(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_CAL_RAW_COUNT);
    #if(0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
        `$INSTANCE_NAME`_NormalizeWidgets(`$INSTANCE_NAME`_END_OF_WIDGETS_INDEX, `$INSTANCE_NAME`_modulationIDAC);
    #endif /* (0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)  */
    TuneSensitivity_P4_v2_60(&`$INSTANCE_NAME`_config);

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
*
* Parameters:
*  sensor: sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumber[] - contains widget Number for given sensor.
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  For other sensors the array element equals to 255.
*  `$INSTANCE_NAME`_numberOfSensors[widget] - Number of sensors in the widget.
*   `$INSTANCE_NAME`_fingerThreshold[] - contains the level of signal for each sensor
*   that determines if a finger present on the sensor.
*   `$INSTANCE_NAME`_negativeNoiseThreshold[] - negative Noise Threshold
*   `$INSTANCE_NAME`_hysteresis[] - the array with hysteresis values.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_UpdateThresholds(uint32 sensor)
{
    `$SizeReplacementString` fingerThreshold;
    uint32 widget;

    widget = `$INSTANCE_NAME`_widgetNumber[sensor];

    #if(0u != `$INSTANCE_NAME`_FLEXIBLE_THRESHOLDS_EN)
        fingerThreshold = `$INSTANCE_NAME`_fingerThreshold[widget];
        /* Update Threshold manually (flexible) */
        `$INSTANCE_NAME`_noiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        `$INSTANCE_NAME`_negativeNoiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        `$INSTANCE_NAME`_hysteresis[widget] = (uint8)(fingerThreshold >> 3u);
    #else
        /* Calculate Finger Threshold and Noise Threshold with Smartsense (automatic) */
        CalculateThresholds_P4_v2_60(&`$INSTANCE_NAME`_config, (uint8)sensor, (uint8)widget, `$INSTANCE_NAME`_fingerThreshold, `$INSTANCE_NAME`_noiseThreshold);

        fingerThreshold = `$INSTANCE_NAME`_fingerThreshold[widget];

        /* Update Threshold based on calculated with Smartsense (automatic) */
        `$INSTANCE_NAME`_negativeNoiseThreshold[widget] = `$INSTANCE_NAME`_noiseThreshold[widget];

        if(fingerThreshold < `$INSTANCE_NAME`_THRESHOLD_1)
        {
            `$INSTANCE_NAME`_hysteresis[widget] = (uint8)(fingerThreshold >> 3u);
        }
        else if(fingerThreshold <  `$INSTANCE_NAME`_THRESHOLD_2)
        {
            `$INSTANCE_NAME`_hysteresis[widget] = (uint8)(fingerThreshold >> 4u);
        }
        else if(fingerThreshold <  `$INSTANCE_NAME`_THRESHOLD_3)
        {
            `$INSTANCE_NAME`_hysteresis[widget] = (uint8)(fingerThreshold >> 5u);
        }
        else if(fingerThreshold <  `$INSTANCE_NAME`_THRESHOLD_4)
        {
            `$INSTANCE_NAME`_hysteresis[widget] = (uint8)(fingerThreshold >> 6u);
        }
        else
        {
            `$INSTANCE_NAME`_hysteresis[widget] = 0u;
        }
    #endif /* (0u != `$INSTANCE_NAME`_FLEXIBLE_THRESHOLDS_EN)  */
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
* Function Name: `$INSTANCE_NAME`_DisableBaselineIDAC
********************************************************************************
*
* Summary:
*  The API disables the Compensation IDAC.
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
void `$INSTANCE_NAME`_DisableBaselineIDAC(void)
{
    uint32 newRegValue;

    newRegValue = `$INSTANCE_NAME`_CSD_IDAC_REG;

    newRegValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK | `$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK);
    newRegValue |= `$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE;

    `$INSTANCE_NAME`_CSD_IDAC_REG = newRegValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableBaselineIDAC
********************************************************************************
*
* Summary:
*  The API enables the Compensation IDAC.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_compensationIDAC[] - used to store a 7-bit idac value for all the sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void  `$INSTANCE_NAME`_EnableBaselineIDAC(const `$INSTANCE_NAME`_CONFIG_TYPE_P4_v2_60 *config)
{
    uint32 curSensor;
    uint32 newRegValue;

    for(curSensor = 0u; curSensor < config->totalScanslotsNum; curSensor++)
    {
        `$INSTANCE_NAME`_compensationIDAC[curSensor] = `$INSTANCE_NAME`_modulationIDAC[curSensor] / 2u;
        `$INSTANCE_NAME`_modulationIDAC[curSensor] = (`$INSTANCE_NAME`_modulationIDAC[curSensor] + 1u) / 2u;
    }

    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    newRegValue = `$INSTANCE_NAME`_CSD_IDAC_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK | `$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK);
    newRegValue |= (`$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE | `$INSTANCE_NAME`_CSD_IDAC2_MODE_FIXED);
    `$INSTANCE_NAME`_CSD_IDAC_REG = newRegValue;

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSensitivity
********************************************************************************
*
* Summary:
*  This API sets the sensitivity value for the sensor. The sensitivity
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
* `$INSTANCE_NAME`_sensorSensitivity[] - This 8-bits array contains Sensitivity in the LSB nibble
*                                and Noise Reset Counter value in the MSB nibble.
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
    `$INSTANCE_NAME`_sensorSensitivity[sensor] &= (uint8)~`$INSTANCE_NAME`_SENSITIVITY_MASK;
    /* Set SensorSensitivity value in LSB nibble */
    `$INSTANCE_NAME`_sensorSensitivity[sensor] |= (uint8)value;
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
*  `$INSTANCE_NAME`_kValueTbl[] - This 8-bits array contains the K value for each sensor.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetSensitivityCoefficient(uint32 sensor)
{
    return (`$INSTANCE_NAME`_kValueTbl[sensor]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNoiseEnvelope
********************************************************************************
*
* Summary:
*  This function returns the noise value of a
*  component.
*
* Parameters:
*  sensor - Sensor number.
*
* Return:
*  The noise envelope value of the sensor
*  indicated by argument.
*
* Global Variables:
*  `$INSTANCE_NAME`_noiseEnvelopeTbl[] - array with Noise Envelope.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetNoiseEnvelope(uint32 sensor)
{
    return((uint16)((uint16)`$INSTANCE_NAME`_noiseEnvelopeTbl[sensor] << 1u) + 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNormalizedDiffCountData
********************************************************************************
*
* Summary:
*  This API returns normalized difference count data.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns a normalized count value of the sensor indicated by the
*  argument.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorSignal[] - array with difference counts for sensors
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetNormalizedDiffCountData(uint32 sensor)
{
    return (uint16)(((uint32)`$INSTANCE_NAME`_sensorSignal[sensor] << 7u) / `$INSTANCE_NAME`_kValueTbl[sensor]);
}

#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

/* [] END OF FILE */
