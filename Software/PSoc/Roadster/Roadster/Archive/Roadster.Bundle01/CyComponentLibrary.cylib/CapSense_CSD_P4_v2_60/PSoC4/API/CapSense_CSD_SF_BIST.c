/*******************************************************************************
* File Name: `$INSTANCE_NAME`_BIST.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code for the Built In Self Test APIs
*  for the CapSesne CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_BIST.h"
#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_SMS.h"

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
    #include "`$INSTANCE_NAME`_CSHL.h"
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

uint8 `$INSTANCE_NAME`_isDiagnosticEnabled = 0u;
uint32 `$INSTANCE_NAME`_diagnosticCsdConfig;

extern uint8 `$INSTANCE_NAME`_widgetResolution[];
extern uint8 `$INSTANCE_NAME`_widgetNumber[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern uint8 `$INSTANCE_NAME`_modulationIDAC[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
extern `$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 `$INSTANCE_NAME`_config;

#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    extern uint8 `$INSTANCE_NAME`_immunityIndex;
#endif /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

extern uint8 `$INSTANCE_NAME`_highImmunityEnable;

#if((0u == `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO))
    extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
#else
    extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal;
#endif /* ((0u == `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO)) */

#if((0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO))
    extern uint8 `$INSTANCE_NAME`_senseClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
#else
    extern uint8 `$INSTANCE_NAME`_senseClkDividerVal;
#endif /* ((0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensorCp
********************************************************************************
*
* Summary:
*  This API implements sensor capacitance measurement in the range from 5 pF to 200 pF.
*  This is part of the component BIST feature.
*
* Parameters:
*  sensor: Sensor index.
*
* Return Value:
*  This API returns the Sensor parasitic capacitance (Cp) of the sensor indicated
*  as an argument. The unit of the sensor Cp value is pico-farads.
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumber[] - stores widget numbers
*  `$INSTANCE_NAME`_widgetResolution[] - used to store scan resolution of every widget.
*  `$INSTANCE_NAME`_sampleClkDividerVal[] - used to store the Modulator dividers
*   for every sensor.
*   `$INSTANCE_NAME`_senseClkDividerVal[] - used to store the Analog Switch dividers
*   for every sensor.
*   `$INSTANCE_NAME`_modulationIDAC[] - used to store 8-bit idac value for every sensor.
*   `$INSTANCE_NAME`_compensationIDAC[] - – used to store 7-bit idac value for every sensor.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetSensorCp(uint32 sensor)
{
    uint32 widget;
    uint32 sensorCp;
    uint32 idacRegisterValue;
    uint32 immunitySensorIndex1;
    uint32 immunitySensorIndex2;
    uint8  idac0Value;
    uint8  idac1Value;
    uint8  idac2Value;
    uint8  resolutionValue;
    uint8  sampleClkDividerVal;
    uint8  senseClkDividerVal;

    #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        `$INSTANCE_NAME`_immunityIndex = 0u;

        if(`$INSTANCE_NAME`_highImmunityEnable == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        {
            `$INSTANCE_NAME`_SetImmunityLevel(1u);
        }
    #endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

    `$INSTANCE_NAME`_AutoTuneInit();
    `$INSTANCE_NAME`_isDiagnosticEnabled = 1u;
    `$INSTANCE_NAME`_diagnosticCsdConfig = `$INSTANCE_NAME`_CP_SCANNING_CONFIG;

    widget = `$INSTANCE_NAME`_widgetNumber[sensor];

    /* Save CSD_IDAC_REG value  */
    idacRegisterValue = `$INSTANCE_NAME`_CSD_IDAC_REG;
    resolutionValue = `$INSTANCE_NAME`_widgetResolution[widget];
    `$INSTANCE_NAME`_widgetResolution[widget] = `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_12_BITS;

    #if((0u == `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO))
        sampleClkDividerVal = `$INSTANCE_NAME`_sampleClkDividerVal[sensor];
        `$INSTANCE_NAME`_sampleClkDividerVal[sensor] = `$INSTANCE_NAME`_SAMPLE_MEASURING_DIV;
    #else
        sampleClkDividerVal = `$INSTANCE_NAME`_sampleClkDividerVal;
        `$INSTANCE_NAME`_sampleClkDividerVal = `$INSTANCE_NAME`_SAMPLE_MEASURING_DIV;
    #endif /* ((0u == `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO)) */

    #if((0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO))
        senseClkDividerVal = `$INSTANCE_NAME`_senseClkDividerVal[sensor];
        `$INSTANCE_NAME`_senseClkDividerVal[sensor] = `$INSTANCE_NAME`_SENSE_MEASURING_DIV;
    #else
        senseClkDividerVal = `$INSTANCE_NAME`_senseClkDividerVal;
        `$INSTANCE_NAME`_senseClkDividerVal = `$INSTANCE_NAME`_SENSE_MEASURING_DIV;
    #endif /* ((0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) */

    idac0Value = `$INSTANCE_NAME`_modulationIDAC[sensor];
    immunitySensorIndex1 = GetImmunitySensorIndex_SF_v1_0(&`$INSTANCE_NAME`_config, 1, sensor);
    idac1Value = `$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex1];
    immunitySensorIndex2 = GetImmunitySensorIndex_SF_v1_0(&`$INSTANCE_NAME`_config, 2, sensor);
    idac2Value = `$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex2];

    `$INSTANCE_NAME`_CsdHwBlockInit();
    `$INSTANCE_NAME`_Enable();

    /* Connect the sense comparator input to AMUXA */
    `$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL;

    /* disable the baselining IDAC  */
    `$INSTANCE_NAME`_DisableBaselineIDAC();

    CalibrateOneDAC_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_CAL_RAW_COUNT, sensor, `$INSTANCE_NAME`_modulationIDAC);

    /*  Calculate Cp in pF  */
    sensorCp = `$INSTANCE_NAME`_ReadSensorRaw(sensor);

    sensorCp = sensorCp * `$INSTANCE_NAME`_modulationIDAC[sensor];
    sensorCp = (sensorCp * `$INSTANCE_NAME`_CP_FACTOR) / `$INSTANCE_NAME`_CP_DIVIDER;

    /* Restore CSD_IDAC_REG value */
    `$INSTANCE_NAME`_CSD_IDAC_REG = idacRegisterValue;
    `$INSTANCE_NAME`_widgetResolution[widget] = resolutionValue;

    #if((0u == `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO))
        `$INSTANCE_NAME`_sampleClkDividerVal[sensor] = sampleClkDividerVal;
    #else
        `$INSTANCE_NAME`_sampleClkDividerVal = sampleClkDividerVal;
    #endif /* ((0u == `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO)) */

    #if((0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO))
        `$INSTANCE_NAME`_senseClkDividerVal[sensor] = senseClkDividerVal;
    #else
        `$INSTANCE_NAME`_senseClkDividerVal = senseClkDividerVal;
    #endif /* ((0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) */

    `$INSTANCE_NAME`_modulationIDAC[sensor] = idac0Value;
    `$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex1] = idac1Value;
    `$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex2] = idac2Value;


    `$INSTANCE_NAME`_isDiagnosticEnabled = 0u;

    return (sensorCp);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MeasureCmod
********************************************************************************
*
* Summary:
*  This API measures the CMOD external capacitor value in pF.
*
* Parameters:
*  value: Returns measured CMOD in pico-farads.
*
* Return Value:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_MeasureCmod(void)
{
    uint32 csdConfigBackup;
    uint32 idacConfigBackup;

    uint32 hsiomConfigBackup;
    uint32 gpioConfigBackup;

    uint32 curSample;
    uint32 tmpResult;
    uint32 newRegisterValue;

    uint8 interruptState;

#if((`$INSTANCE_NAME`_CHAINED_CLOCKS != `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED) && (0u == CY_PSOC4SF))  // TODO: Should be used CapSense clock defines.
    /* Set chained clocks */
    newRegisterValue = CY_GET_XTND_REG32((void CYFAR *)(CYREG_CLK_DIVIDER_B00));
    CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_DIVIDER_B00), newRegisterValue | (0x40000000uL));
#endif  /* ((`$INSTANCE_NAME`_CHAINED_CLOCKS != `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED) && (0u == CY_PSOC4SF)) */

    /* Set clocks */
    `$INSTANCE_NAME`_SenseClk_SetDividerValue(`$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV);
    `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_CMOD_MEASURE_SAMPLE_CLK_DIV);

    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Backup configuration registers */
    csdConfigBackup = `$INSTANCE_NAME`_CSD_CFG_REG;
    idacConfigBackup = `$INSTANCE_NAME`_CSD_IDAC_REG;

    hsiomConfigBackup = `$INSTANCE_NAME`_CMOD_CONNECTION_REG;
    gpioConfigBackup = `$INSTANCE_NAME`_CMOD_PORT_PC_REG;

    /* Connect Cmod to pin */
    newRegisterValue = `$INSTANCE_NAME`_CMOD_CONNECTION_REG;
    newRegisterValue &= ~(`$INSTANCE_NAME`_CMOD_MEASURE_HSIOM_MASK);
    newRegisterValue |= (uint32)((uint32)`$INSTANCE_NAME`_CMOD_MEASURE_HSIOM_CONFIG);

     /* Set Mode 0 (analog mode) to Cmod to pin */
    `$INSTANCE_NAME`_CMOD_PORT_PC_REG &= (uint32)~((uint32)`$INSTANCE_NAME`_CMOD_MEASURE_PORT_MODE_MASK);
    `$INSTANCE_NAME`_CMOD_CONNECTION_REG = newRegisterValue;

    `$INSTANCE_NAME`_CSD_CFG_REG = `$INSTANCE_NAME`_CMOD_MEASURE_CSD_CONFIG;
    `$INSTANCE_NAME`_CSD_IDAC_REG = `$INSTANCE_NAME`_CMOD_MEASURE_IDAC_CONFIG;

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

    tmpResult = 0u;
    interruptState = CyIntGetState(`$INSTANCE_NAME`_ISR_NUMBER);
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Scan avgSamples times */
    for(curSample = 0u; curSample < `$INSTANCE_NAME`_CMOD_MEASURE_AVG_SAMPLES_NUM; curSample++)
    {
        `$INSTANCE_NAME`_CSD_CNT_REG = `$INSTANCE_NAME`_CMOD_MEASURE_RES;
        while(0u != (`$INSTANCE_NAME`_CSD_CNT_REG & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
        {

        }

        tmpResult += `$INSTANCE_NAME`_CSD_CNT_REG;
    }

    /* Calculate Cmod value */
    tmpResult /= `$INSTANCE_NAME`_CMOD_MEASURE_AVG_SAMPLES_NUM;

    if(tmpResult >= (`$INSTANCE_NAME`_CMOD_MEASURE_MAX_VAL))
    {
        tmpResult = 0u;
    }

    tmpResult = (tmpResult * `$INSTANCE_NAME`_FULL_DIVIDER * `$INSTANCE_NAME`_CMOD_MEASURE_IDAC_VAL)/
                `$INSTANCE_NAME`_CMOD_CAP_COEFICIENT;

    /* Restore registers */
    `$INSTANCE_NAME`_CSD_CFG_REG = csdConfigBackup;
    `$INSTANCE_NAME`_CSD_IDAC_REG = idacConfigBackup;

    `$INSTANCE_NAME`_CMOD_CONNECTION_REG = hsiomConfigBackup;
    `$INSTANCE_NAME`_CMOD_PORT_PC_REG = gpioConfigBackup;

    /* Restore interrupts */
    `$INSTANCE_NAME`_CSD_INTR_REG = 1u;
    CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);

    if(0u != interruptState)
    {
        CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
    }

#if((`$INSTANCE_NAME`_CHAINED_CLOCKS != `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED) && (0u == CY_PSOC4SF))  // TODO: Should be used CapSense clock defines.
    /* Set unchained clocks */
    newRegisterValue = CY_GET_XTND_REG32((void CYFAR *)(CYREG_CLK_DIVIDER_B00));
    CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_DIVIDER_B00), newRegisterValue & (~0x40000000uL));
#endif  /* ((`$INSTANCE_NAME`_CHAINED_CLOCKS != `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED) && (0u == CY_PSOC4SF)) */

    return (tmpResult);
}


/* [] END OF FILE */
