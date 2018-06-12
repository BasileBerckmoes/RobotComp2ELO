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


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensorCp
********************************************************************************
*
* Summary:
*  This API implements the sensor capacitance measurement in the range from 5 pF to 200 pF.
*  This is a part of the component BIST feature.
*
* Parameters:
*  sensor: Sensor index.
*
* Return Value:
*  This API returns the Sensor parasitic capacitance (Cp) of the sensor indicated
*  as an argument. The unit of the sensor Cp value is pico-farads.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetSensorCp(uint32 sensor)
{
    uint32 result;
    `$INSTANCE_NAME`_CP_MEASURE_CONFIG `$INSTANCE_NAME`_cpMeasureCfg;

    #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
        `$INSTANCE_NAME`_cpMeasureCfg.sensor  = (uint8)sensor;
    #endif  /* End `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */
    `$INSTANCE_NAME`_cpMeasureCfg.pinNumber  = `$INSTANCE_NAME`_pinShiftTbl[sensor];
    `$INSTANCE_NAME`_cpMeasureCfg.portNumber = `$INSTANCE_NAME`_portTable[sensor];
    `$INSTANCE_NAME`_cpMeasureCfg.senseClkDiv   = `$INSTANCE_NAME`_SENSE_CLK_DIV_MIN >> 1u;
    `$INSTANCE_NAME`_cpMeasureCfg.sampleClkDiv  = `$INSTANCE_NAME`_SAMPLE_CLK_DIV;
    `$INSTANCE_NAME`_cpMeasureCfg.avgSamplesNum    = `$INSTANCE_NAME`_AVG_SAMPLES_NUM;
    `$INSTANCE_NAME`_cpMeasureCfg.calibrationCount = (uint16)`$INSTANCE_NAME`_CALIBRATION_COUNT;
    `$INSTANCE_NAME`_cpMeasureCfg.scanResolution   = `$INSTANCE_NAME`_SCANNING_RESOLUTION;

    result = `$INSTANCE_NAME`_GetLowCp(&`$INSTANCE_NAME`_cpMeasureCfg);

    return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MeasureCmod
********************************************************************************
*
* Summary:
*  This API measures the CMOD external capacitor value in pF in the range from
*  100pF to 40000 pF.
*
* Parameters:
*  value: Return measured CMOD in pico-farads.
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
    uint32 result;
    uint32 hsiomConfigBackup;
    uint32 gpioConfigBackup;

    `$INSTANCE_NAME`_CP_MEASURE_CONFIG `$INSTANCE_NAME`_cpMeasureCfg;

    hsiomConfigBackup = `$INSTANCE_NAME`_CMOD_CONNECTION_REG & `$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK;
    gpioConfigBackup  = `$INSTANCE_NAME`_CMOD_PORT_PC_REG & `$INSTANCE_NAME`_CSD_CMOD_PC_MASK;

    #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
        `$INSTANCE_NAME`_cpMeasureCfg.sensor             = 0u;
    #endif  /* End `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */
    `$INSTANCE_NAME`_cpMeasureCfg.pinNumber        = (uint8)`$INSTANCE_NAME`_CMOD_PIN_NUMBER;
    `$INSTANCE_NAME`_cpMeasureCfg.portNumber       = `$INSTANCE_NAME`_CMOD_PRT_NUMBER;
    `$INSTANCE_NAME`_cpMeasureCfg.idacValue        = `$INSTANCE_NAME`_CMOD_MEASURE_IDAC_VAL;
    `$INSTANCE_NAME`_cpMeasureCfg.senseClkDiv      = `$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV;
    `$INSTANCE_NAME`_cpMeasureCfg.sampleClkDiv     = `$INSTANCE_NAME`_CMOD_MEASURE_SAMPLE_CLK_DIV;
    `$INSTANCE_NAME`_cpMeasureCfg.avgSamplesNum    = `$INSTANCE_NAME`_CMOD_MEASURE_AVG_SAMPLES_NUM;
    `$INSTANCE_NAME`_cpMeasureCfg.scanResolution   = `$INSTANCE_NAME`_CMOD_MEASURE_RES;

    result = `$INSTANCE_NAME`_GetHighCp(&`$INSTANCE_NAME`_cpMeasureCfg);

    `$INSTANCE_NAME`_CMOD_CONNECTION_REG &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
    `$INSTANCE_NAME`_CMOD_CONNECTION_REG |= hsiomConfigBackup;

    `$INSTANCE_NAME`_CMOD_PORT_PC_REG &= ~(`$INSTANCE_NAME`_CSD_CMOD_PC_MASK);
    `$INSTANCE_NAME`_CMOD_PORT_PC_REG |=  (gpioConfigBackup);


    return (result);
}


#if(0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MeasureCShield
********************************************************************************
*
* Summary:
*  This API implements the shield electrode capacitance measurement in the range
*  from 5 pF to 200 pF. Returns 0 for greater capacitance values.
*  This is a part of component BIST feature.
*
* Parameters:
*  None.
*
* Return Value:
*  This API returns the shield electrode capacitance (Cp).
*  The unit of sensor Cp value is pico-farads.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_MeasureCShield(void)
{
    uint32 result;
    `$INSTANCE_NAME`_CP_MEASURE_CONFIG `$INSTANCE_NAME`_cpMeasureCfg;

    `$INSTANCE_NAME`_cpMeasureCfg.pinNumber  =  (uint8)`$INSTANCE_NAME`_SHIELD_PIN_NUMBER;
    `$INSTANCE_NAME`_cpMeasureCfg.portNumber = `$INSTANCE_NAME`_SHIELD_PORT_NUMBER;
    `$INSTANCE_NAME`_cpMeasureCfg.senseClkDiv   = `$INSTANCE_NAME`_SENSE_CLK_DIV_MIN >> 1u;
    `$INSTANCE_NAME`_cpMeasureCfg.sampleClkDiv  = `$INSTANCE_NAME`_SAMPLE_CLK_DIV;
    `$INSTANCE_NAME`_cpMeasureCfg.avgSamplesNum    = `$INSTANCE_NAME`_AVG_SAMPLES_NUM;
    `$INSTANCE_NAME`_cpMeasureCfg.calibrationCount = (uint16)`$INSTANCE_NAME`_CALIBRATION_COUNT;
    `$INSTANCE_NAME`_cpMeasureCfg.scanResolution   = `$INSTANCE_NAME`_SCANNING_RESOLUTION;

    result = `$INSTANCE_NAME`_GetLowCp(&`$INSTANCE_NAME`_cpMeasureCfg);

    return(result);
}


#if(0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_MeasureCShieldTank
    ********************************************************************************
    *
    * Summary:
    *  This API measures the CTANK external capacitor value in pF in the range from
    *  100pF to 40000 pF.
    *
    * Parameters:
    *  value: Returns measured CTANK in pico-farads.
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
    uint32 `$INSTANCE_NAME`_MeasureCShieldTank(void)
    {
        uint32 result;
        uint32 hsiomConfigBackup;
        uint32 gpioConfigBackup;

        `$INSTANCE_NAME`_CP_MEASURE_CONFIG `$INSTANCE_NAME`_cpMeasureCfg;

        hsiomConfigBackup = `$INSTANCE_NAME`_CTANK_CONNECTION_REG & `$INSTANCE_NAME`_CSD_CTANK_CONNECTION_MASK;
        gpioConfigBackup  = `$INSTANCE_NAME`_CTANK_PORT_PC_REG & `$INSTANCE_NAME`_CSD_CTANK_PC_MASK;

        `$INSTANCE_NAME`_cpMeasureCfg.pinNumber        = (uint8)`$INSTANCE_NAME`_CTANK_PIN_NUMBER;
        `$INSTANCE_NAME`_cpMeasureCfg.portNumber       = `$INSTANCE_NAME`_CTANK_PRT_NUMBER;
        `$INSTANCE_NAME`_cpMeasureCfg.idacValue        = `$INSTANCE_NAME`_CTANK_MEASURE_IDAC_VAL;
        `$INSTANCE_NAME`_cpMeasureCfg.senseClkDiv      = `$INSTANCE_NAME`_CTANK_MEASURE_SENSE_CLK_DIV;
        `$INSTANCE_NAME`_cpMeasureCfg.sampleClkDiv     = `$INSTANCE_NAME`_CTANK_MEASURE_SAMPLE_CLK_DIV;
        `$INSTANCE_NAME`_cpMeasureCfg.avgSamplesNum    = `$INSTANCE_NAME`_CTANK_MEASURE_AVG_SAMPLES_NUM;
        `$INSTANCE_NAME`_cpMeasureCfg.scanResolution   = `$INSTANCE_NAME`_CTANK_MEASURE_RES;

        result = `$INSTANCE_NAME`_GetHighCp(&`$INSTANCE_NAME`_cpMeasureCfg);

        `$INSTANCE_NAME`_CTANK_CONNECTION_REG &= ~(`$INSTANCE_NAME`_CSD_CTANK_CONNECTION_MASK);
        `$INSTANCE_NAME`_CTANK_CONNECTION_REG |= hsiomConfigBackup;

        `$INSTANCE_NAME`_CTANK_PORT_PC_REG &= ~(`$INSTANCE_NAME`_CSD_CTANK_PC_MASK);
        `$INSTANCE_NAME`_CTANK_PORT_PC_REG |=  (gpioConfigBackup);

        return (result);
    }
#endif /* (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE) */

#endif /* (0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetLowCp
********************************************************************************
*
* Summary:
*  This is internal API function intended to measurement capacitance of electrode
*  that is connected to the port/pin indicated as argument.
*  This is part of BIST feature of component.
*
* Parameters:
*  None.
*
* Return Value:
*  This API returns the electrode capacitance (Cp).
*  The unit of sensor Cp value is pico-farads.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetLowCp(`$INSTANCE_NAME`_CP_MEASURE_CONFIG *config)
{
    uint32 sensorCp;
    uint32 sensorRaw;
    uint32 statusVar;
    uint32 interruptState;
    uint32 idacRegisterValue;
    uint32 newRegisterValue;

    newRegisterValue  = `$INSTANCE_NAME`_CSD_TRIM1_REG;
    newRegisterValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
    newRegisterValue |= ((uint32)`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG &
                        (uint32)`$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK);
    `$INSTANCE_NAME`_CSD_TRIM1_REG = newRegisterValue;

    interruptState = CyIntGetState(`$INSTANCE_NAME`_ISR_NUMBER);
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Save CSD_IDAC_REG value  */
    idacRegisterValue = `$INSTANCE_NAME`_CSD_IDAC_REG;

    newRegisterValue = `$INSTANCE_NAME`_CSD_IDAC_REG;
    #if(`$INSTANCE_NAME`_IDAC_CNT > 1u)
        newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK | `$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK |
                              `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X | `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X);
    #else
        newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK | `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X);
    #endif /* (`$INSTANCE_NAME`_IDAC_CNT > 1u) */
    `$INSTANCE_NAME`_CSD_IDAC_REG = newRegisterValue | `$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE;

    do
    {
        do
        {
            config->senseClkDiv <<= 1u;
            statusVar = `$INSTANCE_NAME`_CalibrateIDAC(config);
        }while((statusVar != `$INSTANCE_NAME`_CALIBRATION_SUCCESS) && (config->senseClkDiv < `$INSTANCE_NAME`_SENSE_CLK_DIV_MAX));

        config->idacValue >>= 1u;

        /*  Calculate Cp in pF  */
        sensorRaw = `$INSTANCE_NAME`_ScanSensorCp(config);

        if((sensorRaw > (uint32)`$INSTANCE_NAME`_CHARGE_VALIDATION_ERROR_TOP) ||
            (sensorRaw < (uint32)`$INSTANCE_NAME`_CHARGE_VALIDATION_ERROR_BOT))
        {
            statusVar = `$INSTANCE_NAME`_VALIDATION_FAIL;
        }
        else
        {
            statusVar = `$INSTANCE_NAME`_VALIDATION_SUCCESS;
        }
    }
    while((statusVar != `$INSTANCE_NAME`_VALIDATION_SUCCESS) && (config->senseClkDiv < `$INSTANCE_NAME`_SENSE_CLK_DIV_MAX));

    sensorCp = (sensorRaw * config->senseClkDiv * config->idacValue) / `$INSTANCE_NAME`_SENSITIVITY_COEFFICIENT;
    if(sensorCp >= (`$INSTANCE_NAME`_CP_MEASURE_MAX_VAL))
    {
        sensorCp = 0u;
    }

    /* Restore CSD_IDAC_REG value */
    `$INSTANCE_NAME`_CSD_IDAC_REG = idacRegisterValue;

    if(0u != interruptState)
    {
        CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
    }

    return (sensorCp);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetHighCp
********************************************************************************
*
* Summary:
*  This is internal API function intended to measurement capacitance of capacitor
*  that is connected to the port/pin indicated as argument.
*  This is part of BIST feature of component.
*
* Parameters:
*  None.
*
* Return Value:
*  This API returns the electrode capacitance (Cp).
*  The unit of sensor Cp value is pico-farads.
*
* Global Variables:
*  None
*
* Side Effects:
*  CSD component should be stopped before calling this API.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetHighCp(const `$INSTANCE_NAME`_CP_MEASURE_CONFIG *config)
{
    uint32 csdConfigBackup;
    uint32 idacConfigBackup;
    uint32 curSample;
    uint32 tmpResult;
    uint32 newRegisterValue;

    uint8 interruptState;

    newRegisterValue  = `$INSTANCE_NAME`_CSD_TRIM1_REG;
    newRegisterValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
    newRegisterValue |= ((uint32)`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG &\
                         (uint32)`$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK);
    `$INSTANCE_NAME`_CSD_TRIM1_REG = newRegisterValue;

    `$INSTANCE_NAME`_SenseClk_Stop();
    `$INSTANCE_NAME`_SampleClk_Stop();

    /* Set clocks */
    `$INSTANCE_NAME`_SenseClk_SetDividerValue(config->senseClkDiv);
    `$INSTANCE_NAME`_SampleClk_SetDividerValue(config->sampleClkDiv);

    /* Enable Clocks */
    #if (0u == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        `$INSTANCE_NAME`_SenseClk_Start();
        `$INSTANCE_NAME`_SampleClk_Start();
    #else
        `$INSTANCE_NAME`_SampleClk_Start();
        `$INSTANCE_NAME`_SenseClk_StartEx(`$INSTANCE_NAME`_SampleClk__DIV_ID);
    #endif /* (0u == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

    /* Backup the configuration registers */
    csdConfigBackup = `$INSTANCE_NAME`_CSD_CFG_REG;
    idacConfigBackup = `$INSTANCE_NAME`_CSD_IDAC_REG & `$INSTANCE_NAME`_IDAC1_CONFIG_MASK;

    interruptState = CyEnterCriticalSection();

    `$INSTANCE_NAME`_ConnectElectrode((uint32)config->pinNumber, (uint32)config->portNumber);

    `$INSTANCE_NAME`_CSD_CFG_REG  = `$INSTANCE_NAME`_HIGH_CP_MEASURE_CSD_CONFIG;

    `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_IDAC1_CONFIG_MASK);
    `$INSTANCE_NAME`_CSD_IDAC_REG |= (`$INSTANCE_NAME`_HIGH_CP_MEASURE_IDAC_CONFIG | (uint32)config->idacValue);

    CyExitCriticalSection(interruptState);

    tmpResult = 0u;
    interruptState = CyIntGetState(`$INSTANCE_NAME`_ISR_NUMBER);
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Scan avgSamples times */
    for(curSample = 0u; curSample < config->avgSamplesNum; curSample++)
    {
        `$INSTANCE_NAME`_CSD_CNT_REG = config->scanResolution;
        while(0u != (`$INSTANCE_NAME`_CSD_CNT_REG & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
        {

        }

        tmpResult += `$INSTANCE_NAME`_CSD_CNT_REG;
    }

    /* Calculate Cmod value */
    tmpResult /= config->avgSamplesNum;
    tmpResult = (tmpResult * (uint32)`$INSTANCE_NAME`_FULL_DIVIDER * (uint32)config->idacValue)/
                ((uint32)CYDEV_BCLK__HFCLK__MHZ * (uint32)(config->scanResolution >> `$INSTANCE_NAME`_RESOLUTION_OFFSET));

        /* Restore the registers */
    `$INSTANCE_NAME`_CSD_CFG_REG = csdConfigBackup;

    `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_IDAC1_CONFIG_MASK);
    `$INSTANCE_NAME`_CSD_IDAC_REG |= idacConfigBackup;

    /* Restore interrupts */
    `$INSTANCE_NAME`_CSD_INTR_REG = 1u;
    CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);

    if(0u != interruptState)
    {
        CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
    }

    `$INSTANCE_NAME`_SenseClk_Stop();
    `$INSTANCE_NAME`_SampleClk_Stop();

    return (tmpResult);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanSensorCp
********************************************************************************
*
* Summary:
*  This function scans sensor with given idac and resolution parameters.
*
* Parameters:
*  sensor - Sensor number.
*
*  idac - Sensor's iDAC1 value
*
*  resolution - scanning resolution
*
*  avgSamples - Number of samples to average
*
* Return:
*  Returns the current raw data value for a defined sensor number.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16  `$INSTANCE_NAME`_ScanSensorCp(const `$INSTANCE_NAME`_CP_MEASURE_CONFIG *config)
{
    uint32 curSample;
    uint32 avgVal = 0u;
    uint32 watchdogCounter;
    uint32 newIdacRegisterValue;
    uint32 newConfigRegisterValue;

    uint16 senseClkDividerVal;

    #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
        uint8 j;
        uint8 snsNumber;
        const uint8 *index;
        uint8 complexPinNumber;
        uint8 complexPortNumber;
    #endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */

    #if (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        senseClkDividerVal = config->senseClkDiv;
    #else
        senseClkDividerVal = config->senseClkDiv / `$INSTANCE_NAME`_SAMPLE_CLK_DIV;
    #endif /* (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

    /* Set clocks */
    `$INSTANCE_NAME`_SenseClk_SetDividerValue(senseClkDividerVal);
    `$INSTANCE_NAME`_SampleClk_SetDividerValue(config->sampleClkDiv);

    /* Connect the Cmod to pin */
    newConfigRegisterValue = `$INSTANCE_NAME`_CMOD_CONNECTION_REG;
    newConfigRegisterValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
    newConfigRegisterValue |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A;
    `$INSTANCE_NAME`_CMOD_CONNECTION_REG = newConfigRegisterValue;

    /* Set Idac Value */
    newIdacRegisterValue = `$INSTANCE_NAME`_CSD_IDAC_REG;
    newIdacRegisterValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK);
    newIdacRegisterValue |= config->idacValue;

    /* Save the CSD configuration */
    newConfigRegisterValue = `$INSTANCE_NAME`_CSD_CFG_REG;

    /* Enable the sensor */
    #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
        if (((config->portNumber) & `$INSTANCE_NAME`_COMPLEX_SS_FLAG) == 0u)
        {
            `$INSTANCE_NAME`_ConnectElectrode((uint32)config->pinNumber, (uint32)config->portNumber);
        }
        else
        {
            /* Enable the complex sensor */
            complexPinNumber = config->portNumber;
            complexPinNumber &= ~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
            index = &`$INSTANCE_NAME`_indexTable[complexPinNumber];
            snsNumber = `$INSTANCE_NAME`_maskTable[config->sensor];

            for (j = 0u; j < snsNumber; j++)
            {
                complexPinNumber  = `$INSTANCE_NAME`_pinShiftTbl[index[j]];
                complexPortNumber = `$INSTANCE_NAME`_portTable[index[j]];
                `$INSTANCE_NAME`_ConnectElectrode((uint32)complexPinNumber, (uint32)complexPortNumber);
            }
        }
    #else
        `$INSTANCE_NAME`_ConnectElectrode((uint32)config->pinNumber, (uint32)config->portNumber);
    #endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */

    /* Scan avgSamples times */
    for(curSample = 0u; curSample < config->avgSamplesNum; curSample++)
    {
        /* Configure CSD for precharge */
        `$INSTANCE_NAME`_CSD_CFG_REG = `$INSTANCE_NAME`_CP_PRECHARGE_CONFIG;
        `$INSTANCE_NAME`_CSD_IDAC_REG = `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG;

    #if(`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
        `$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_POLARITY_VDDIO);
    #endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

        watchdogCounter = `$INSTANCE_NAME`_PRECHARGE_WATCHDOG_CYCLES_NUM;
        while((0u == (`$INSTANCE_NAME`_CSD_STAT_REG & `$INSTANCE_NAME`_CSD_STAT_SAMPLE)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }
    #if(`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
        `$INSTANCE_NAME`_CSD_CFG_REG |= (`$INSTANCE_NAME`_CSD_CFG_POLARITY_VDDIO);
    #endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

        `$INSTANCE_NAME`_CSD_IDAC_REG = newIdacRegisterValue;

        /* Configure CSD for scanning */
        `$INSTANCE_NAME`_CSD_CFG_REG = (`$INSTANCE_NAME`_CP_SCANNING_CONFIG);
        /* Set resolution and begin scanning  */
        `$INSTANCE_NAME`_CSD_CNT_REG = config->scanResolution;
        while(0u != (`$INSTANCE_NAME`_CSD_CNT_REG & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
        {
            /* Wait until scanning is complete */
        }
        /* Read data */
        if(0u != watchdogCounter)
        {
            avgVal += `$INSTANCE_NAME`_CSD_CNT_REG;
        }
        else
        {
            avgVal = 0u;
        }
    }

    /* Disable the sensor */
    #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
        if (((config->portNumber) & `$INSTANCE_NAME`_COMPLEX_SS_FLAG) == 0u)
        {
            `$INSTANCE_NAME`_DisconnectElectrode((uint32)config->pinNumber, (uint32)config->portNumber);
        }
        else
        {
            /* Disable the complex sensor */
            complexPinNumber = config->portNumber;
            complexPinNumber &= ~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
            index = &`$INSTANCE_NAME`_indexTable[complexPinNumber];
            snsNumber = `$INSTANCE_NAME`_maskTable[config->sensor];

            for (j = 0u; j < snsNumber; j++)
            {
                complexPinNumber  = `$INSTANCE_NAME`_pinShiftTbl[index[j]];
                complexPortNumber = `$INSTANCE_NAME`_portTable[index[j]];
                `$INSTANCE_NAME`_DisconnectElectrode((uint32)complexPinNumber, (uint32)complexPortNumber);
            }
        }
    #else
        `$INSTANCE_NAME`_DisconnectElectrode((uint32)config->pinNumber, (uint32)config->portNumber);
    #endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */

    /* Restore the CSD configuration */
    `$INSTANCE_NAME`_CSD_CFG_REG = newConfigRegisterValue;

    /* Restore the interrupts */
    `$INSTANCE_NAME`_CSD_INTR_REG = 1u;
    CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);

    return ((uint16)(avgVal / config->avgSamplesNum));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCalibratedIDAC
********************************************************************************
*
* Summary:
*  Computes the IDAC values for sensor, which provide the raw signal on
*  the specified level, with specified prescaler, speed and resolution.
*
* Parameters:
*
*  rawLevel -  Raw data level wich should be reached during the callibration
*              procedure.
*
*  sensor - Sensor Number
*
*  resolution - Sensor resolution
*
* Return:
*  Calibrated iDAC1 value
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CalibrateIDAC(`$INSTANCE_NAME`_CP_MEASURE_CONFIG *config)
{
    uint8 mask;
    uint32 rawData;
    uint32 retVal;

    /* Init calibration bit */
    mask = 0x80u;
    /* Init IDAC  */
    config->idacValue = 0x00u;

    do
    {
        /* Set calibration bit */
        config->idacValue |= mask;
        rawData = `$INSTANCE_NAME`_ScanSensorCp(config);

        if(rawData < config->calibrationCount)
        {
            /* Reset calibration bit */
            config->idacValue &= (uint8)~mask;
        }

        /* Prepare next bit to set or reset */
        mask >>= 1u;

    }while(mask > 0u);

    if((rawData > (uint32)`$INSTANCE_NAME`_CALIBRATION_ERROR_TOP) || (rawData < (uint32)`$INSTANCE_NAME`_CALIBRATION_ERROR_BOT))
    {
        retVal = `$INSTANCE_NAME`_CALIBRATION_FAIL;
    }
    else
    {
        retVal = `$INSTANCE_NAME`_CALIBRATION_SUCCESS;
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConnectElectrode
********************************************************************************
*
* Summary:
*  Connects Shield electrode.
*
* Parameters:
*  pinNumber:  Electrode pin number.
*  portNumber: Electrode port number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for every port.
*  `$INSTANCE_NAME`_PrtCfgTb[] - Contains pointers to the port config
*  registers for every port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConnectElectrode(uint32 pinNumber, uint32 portNumber)
{
    uint32  pinModeShift;
    uint32  pinHSIOMShift;
    uint32 newRegisterValue;

    pinModeShift  = pinNumber * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE;
    pinHSIOMShift = pinNumber * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE;

    newRegisterValue = *`$INSTANCE_NAME`_prtSelTbl[portNumber];
    newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)`$INSTANCE_NAME`_CSD_SENSE_PORT_MODE << pinHSIOMShift);

    *`$INSTANCE_NAME`_prtCfgTbl[portNumber] &= (uint32)~((uint32)`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
    *`$INSTANCE_NAME`_prtSelTbl[portNumber] = newRegisterValue;

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisconnectElectrode
********************************************************************************
*
* Summary:
*  Disconnects Shield electrode.
*
* Parameters:
*  pinNumber:  Electrode pin number.
*  portNumber: Electrode port number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for every port.
*  `$INSTANCE_NAME`_PrtCfgTb[] - Contains pointers to the port config
*  registers for every port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisconnectElectrode(uint32 pinNumber, uint32 portNumber)
{
    uint32  pinHSIOMShift;

    #if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS != `$INSTANCE_NAME`__SHIELD)
        uint32 newRegisterValue;
        uint32  pinModeShift;
        pinModeShift = pinNumber  * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE;
    #endif

    pinHSIOMShift = pinNumber * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE;

    *`$INSTANCE_NAME`_prtSelTbl[portNumber] &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);

    #if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__SHIELD)
        *`$INSTANCE_NAME`_prtSelTbl[portNumber] |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
    #else

    newRegisterValue = *`$INSTANCE_NAME`_prtCfgTbl[portNumber];
    newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
    newRegisterValue |=  (uint32)((uint32)`$INSTANCE_NAME`_CSD_INACTIVE_CONNECT << pinModeShift);
    *`$INSTANCE_NAME`_prtCfgTbl[portNumber] =  newRegisterValue;

    *`$INSTANCE_NAME`_prtDRTbl[portNumber]  &=  (uint32)~(uint32)((uint32)1u << pinNumber);

#endif /* `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__SHIELD */
}

/* [] END OF FILE */
