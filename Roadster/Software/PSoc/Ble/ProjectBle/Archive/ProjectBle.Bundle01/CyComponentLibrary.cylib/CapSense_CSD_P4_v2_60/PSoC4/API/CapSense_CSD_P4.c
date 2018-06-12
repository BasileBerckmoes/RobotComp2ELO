/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code for scanning APIs for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"
#include "cypins.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
    #include "`$INSTANCE_NAME`_CSHL.h"
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

/* This definition is intended to prevent unexpected linker error.
   For more details please see the IAR Technical Note 49981 */
#if defined(__ICCARM__)
    extern void `$INSTANCE_NAME`_EnableSensor(uint32 sensor);
    extern void `$INSTANCE_NAME`_DisableSensor(uint32 sensor);
#endif /* (__ICCARM__) */

/* SmartSense functions */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    uint8 `$INSTANCE_NAME`_lowLevelTuningDone = 0u;
    uint8 `$INSTANCE_NAME`_scanSpeedTbl[((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
    uint8 `$INSTANCE_NAME`_prescalersTuningDone = 0u;
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

/* Global software variables */
volatile uint8 `$INSTANCE_NAME`_csdStatusVar = 0u;   /* CapSense CSD status, variable */
volatile uint8 `$INSTANCE_NAME`_sensorIndex = 0u;    /* Index of scannig sensor */

/* Global array of Raw Counts */
uint16 `$INSTANCE_NAME`_sensorRaw[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};

/* Backup variables for trim registers*/
#if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
    uint8 `$INSTANCE_NAME`_csdTrim2;
#else
    uint8 `$INSTANCE_NAME`_csdTrim1;
#endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

/* Global array of un-scanned sensors state */
uint8 `$INSTANCE_NAME`_unscannedSnsDriveMode[`$INSTANCE_NAME`_PORT_PIN_CONFIG_TBL_ZISE];

/* Backup array for `$INSTANCE_NAME`_sensorEnableMask */
uint8 `$INSTANCE_NAME`_sensorEnableMaskBackup[(((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];

/* Configured constants and arrays by Customizer */
`$writerCVariables`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  API initializes default CapSense configuration provided by the customizer that defines
*  the mode of component operations and resets all the sensors to an inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_immunityIndex - defines immunity level.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32 curSensor;

    #if(`$INSTANCE_NAME`_IS_SHIELD_ENABLE)

        #if((`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) || (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE))
            uint32 newRegValue;

            newRegValue = `$INSTANCE_NAME`_CTANK_CONNECTION_REG;
            newRegValue &= ~(`$INSTANCE_NAME`_CSD_CTANK_CONNECTION_MASK);
            newRegValue |= `$INSTANCE_NAME`_CSD_CTANK_TO_AMUXBUS_B;
            `$INSTANCE_NAME`_CTANK_CONNECTION_REG = newRegValue;

            #if(`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF)
                newRegValue = `$INSTANCE_NAME`_CTANK_PORT_PC_REG;
                newRegValue &= ~(`$INSTANCE_NAME`_CSD_CTANK_PC_MASK);
                newRegValue |= `$INSTANCE_NAME`_CTANK_PC_STRONG_MODE;
                `$INSTANCE_NAME`_CTANK_PORT_PC_REG = newRegValue;

                newRegValue = `$INSTANCE_NAME`_CTANK_PORT_DR_REG;
                newRegValue &= ~(`$INSTANCE_NAME`_CTANK_DR_MASK);
                newRegValue |= `$INSTANCE_NAME`_CTANK_DR_CONFIG;
                `$INSTANCE_NAME`_CTANK_PORT_DR_REG = newRegValue;
            #endif /* (`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */

        #endif /* ((`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) || (`$INSTANCE_NAME`_CSH_TANK_ENABLE)) */

        `$INSTANCE_NAME`_EnableShieldElectrode((uint32)`$INSTANCE_NAME`_SHIELD_PIN_NUMBER, (uint32)`$INSTANCE_NAME`_SHIELD_PORT_NUMBER);

    #endif /* (`$INSTANCE_NAME`_IS_SHIELD_ENABLE) */

    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; curSensor++)
    {
        `$INSTANCE_NAME`_SetUnscannedSensorState(curSensor, `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS);
    }

    `$INSTANCE_NAME`_CsdHwBlockInit();
    `$INSTANCE_NAME`_SetShieldDelay(`$INSTANCE_NAME`_SHIELD_DELAY );

    /* Clear all sensors */
    `$INSTANCE_NAME`_ClearSensors();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CsdHwBlockInit
********************************************************************************
*
* Summary:
*  Initialises the hardware parameters of the CSD block
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csdTrim1 - Contains IDAC trim register value for Sourcing Mode.
*  `$INSTANCE_NAME`_csdTrim2 - Contains IDAC trim register value for Sinking Mode.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_CsdHwBlockInit(void)
{
    uint32 newRegValue;

        /* Set trim registers for CSD Mode */
    #if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
        /* iDAC1 Sinking Mode */
        `$INSTANCE_NAME`_csdTrim2 = (uint8)`$INSTANCE_NAME`_CSD_TRIM2_REG;
        newRegValue = `$INSTANCE_NAME`_csdTrim2;
        newRegValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)((uint32)`$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG & (uint32)`$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK);

        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
            /* iDAC2 Sinking Mode */
            newRegValue &= `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)((uint32)`$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG & (uint32)`$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK);
        #endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */
        `$INSTANCE_NAME`_CSD_TRIM2_REG = newRegValue;
    #else
        /* iDAC1 Sourcing Mode */
        `$INSTANCE_NAME`_csdTrim1 = (uint8)`$INSTANCE_NAME`_CSD_TRIM1_REG;
        newRegValue = `$INSTANCE_NAME`_csdTrim1;
        newRegValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)((uint32)`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG & (uint32)`$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK);
        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
             /* iDAC2 Sourcing Mode */
            newRegValue &= `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)((uint32)`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG & (uint32)`$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK);
        #endif
        `$INSTANCE_NAME`_CSD_TRIM1_REG = newRegValue;
    #endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

    /* Configure CSD and IDAC */
    #if (`$INSTANCE_NAME`_IDAC_CNT > 1u)
        `$INSTANCE_NAME`_CSD_IDAC_REG = `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG;
        `$INSTANCE_NAME`_CSD_CFG_REG = `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG;
    #else
        `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK  | `$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK);
        `$INSTANCE_NAME`_CSD_IDAC_REG |= `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG;

        `$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CONFIG_MASK);
        `$INSTANCE_NAME`_CSD_CFG_REG |= (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG);
    #endif /* (`$INSTANCE_NAME`_IDAC_CNT > 1u) */


    /* Connect Cmod to AMUX bus */
    newRegValue = `$INSTANCE_NAME`_CMOD_CONNECTION_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A;
    `$INSTANCE_NAME`_CMOD_CONNECTION_REG = newRegValue;

    /* Configure Dead Band PWM if it is enabled */
    #if(`$INSTANCE_NAME`_CSD_4B_PWM_MODE != `$INSTANCE_NAME`__PWM_OFF)
        `$INSTANCE_NAME`_CSD_4B_PWM_REG = `$INSTANCE_NAME`_DEFAULT_CSD_4B_PWM_CONFIG;
    #endif /* (`$INSTANCE_NAME`_CSD_4B_PWM_MODE != `$INSTANCE_NAME`__PWM_OFF) */

    /* Setup ISR */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
    #if !defined(CY_EXTERNAL_INTERRUPT_CONFIG)
        (void)CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_ISR);
        CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
    #endif /* (CY_EXTERNAL_INTERRUPT_CONFIG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the CSD block and related resources to an active mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint32 newRegValue;

    /* Enable Clocks */
    `$INSTANCE_NAME`_SenseClk_Stop();
    `$INSTANCE_NAME`_SampleClk_Stop();

    `$INSTANCE_NAME`_SampleClk_SetDividerValue((uint16)`$INSTANCE_NAME`_INITIAL_CLK_DIVIDER);
    `$INSTANCE_NAME`_SenseClk_SetDividerValue((uint16)`$INSTANCE_NAME`_INITIAL_CLK_DIVIDER);

    #if (0u == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        `$INSTANCE_NAME`_SenseClk_Start();
        `$INSTANCE_NAME`_SampleClk_Start();
    #else
        `$INSTANCE_NAME`_SampleClk_Start();
        `$INSTANCE_NAME`_SenseClk_StartEx(`$INSTANCE_NAME`_SampleClk__DIV_ID);
    #endif /* (0u == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

    /* Enable the CSD block */
    newRegValue = `$INSTANCE_NAME`_CSD_CFG_REG;
    newRegValue |= (`$INSTANCE_NAME`_CSD_CFG_ENABLE | `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN
                                                   | `$INSTANCE_NAME`_CSD_CFG_SENSE_EN);
    `$INSTANCE_NAME`_CSD_CFG_REG = newRegValue;

    /* Enable interrupt */
    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin the component operation. CapSense_Start()
*  calls the CapSense_Init() function, and then calls the CapSense_Enable()
*  function. Initializes the registers and starts the CSD method of the CapSense
*  component. Resets all the sensors to an inactive state. Enables interrupts for
*  sensors scanning. When the SmartSense tuning mode is selected, the tuning procedure
*  is applied for all the sensors. The CapSense_Start() routine must be called before
*  any other API routines.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   `$INSTANCE_NAME`_initVar - used to check the initial configuration,
*   modified on the first function call.
*  `$INSTANCE_NAME`_lowLevelTuningDone - Used to notify the Tuner GUI that
*   tuning of the scanning parameters is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{

    static uint8 `$INSTANCE_NAME`_initVar = 0u;

    #if((0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO))
        uint32 curSensor;
        uint32 rawLevel;
        uint32 widget;
    #endif /* ((0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO)) */

    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();

    /* AutoTunning start */
    #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
        #if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
            `$INSTANCE_NAME`_AutoTune();
            `$INSTANCE_NAME`_lowLevelTuningDone = 1u;
        #endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */
    #else
        #if(0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE)

            #if(`$INSTANCE_NAME`_IDAC_CNT > 1u)
                `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK);
            #endif /* (`$INSTANCE_NAME`_IDAC_CNT > 1u) */

            for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
            {
                widget = `$INSTANCE_NAME`_widgetNumber[curSensor];
                rawLevel = `$INSTANCE_NAME`_widgetResolution[widget] >> `$INSTANCE_NAME`_RESOLUTION_OFFSET;

                /* Calibration level should be equal to 85% from scanning resolution */
                rawLevel = (rawLevel * 85u) / 100u;

                `$INSTANCE_NAME`_CalibrateSensor(curSensor, rawLevel, `$INSTANCE_NAME`_modulationIDAC);
            }

            #if(0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
                `$INSTANCE_NAME`_NormalizeWidgets(`$INSTANCE_NAME`_END_OF_WIDGETS_INDEX, `$INSTANCE_NAME`_modulationIDAC);
            #endif /* (0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)  */

            #if(`$INSTANCE_NAME`_IDAC_CNT > 1u)
                for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
                {
                    `$INSTANCE_NAME`_compensationIDAC[curSensor] = `$INSTANCE_NAME`_modulationIDAC[curSensor] / 2u;
                    `$INSTANCE_NAME`_modulationIDAC[curSensor] = (`$INSTANCE_NAME`_modulationIDAC[curSensor] + 1u) / 2u;
                }
                `$INSTANCE_NAME`_CSD_IDAC_REG |= `$INSTANCE_NAME`_CSD_IDAC2_MODE_FIXED;
            #endif /* (`$INSTANCE_NAME`_IDAC_CNT > 1u) */

        #endif /* (0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) */

    #endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

    /* Initialize Advanced Centroid */
    #if(`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
        `$INSTANCE_NAME`_AdvancedCentroidInit();
    #endif /* (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */

    /* Connect sense comparator input to AMUXA */
    `$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Stops the sensor scanning, disables component interrupts, and resets all the
*  sensors to an inactive state. Disables the Active mode power template bits for
*  the subcomponents used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csdTrim1 - Contains the IDAC trim register value for the Sourcing Mode.
*  `$INSTANCE_NAME`_csdTrim2 - Contains the IDAC trim register value for vSinking Mode.
*
* Side Effects:
*  This function should be called after scans are completed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    /* Disable interrupt */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    `$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN | `$INSTANCE_NAME`_CSD_CFG_SENSE_EN);

    #if(`$INSTANCE_NAME`_IDAC_CNT == 2u)
        `$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_ENABLE);
    #endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */

    /* Disable the Clocks */
    `$INSTANCE_NAME`_SenseClk_Stop();
    `$INSTANCE_NAME`_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FindNextSensor
********************************************************************************
*
* Summary:
*  Finds the next sensor to scan.
*
* Parameters:
*  snsIndex:  Current index of sensor.
*
* Return:
*  Returns the next sensor index to scan.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorEnableMask[] - used to store bit masks of the enabled sensors.
*
* Side Effects:
*  This function affects the  current scanning and should not
*  be used outside the component.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_FindNextSensor(uint8 snsIndex)
{
    uint32 enableFlag;

    /* Check if sensor enabled */
    do
    {
        /* Proceed with next sensor */
        snsIndex++;
        if(snsIndex == `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
        {
            break;
        }
        enableFlag = `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_sensorEnableMask, (uint32)snsIndex);
    }
    while(enableFlag == 0u);

    return ((uint8)snsIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanSensor
********************************************************************************
*
* Summary:
*  Sets the scan settings and starts scanning a sensor. After scanning is complete,
*  the ISR copies the measured sensor raw data to the global raw sensor array.
*  Use of the ISR ensures this function is non-blocking.
*  Each sensor has a unique number within the sensor array.
*  This number is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and mode of scan as single scan.
*  `$INSTANCE_NAME`_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to the provided sensor argument.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ScanSensor(uint32 sensor)
{
    /* Clears status/control variable and set sensorIndex */
    `$INSTANCE_NAME`_csdStatusVar = 0u;
    `$INSTANCE_NAME`_sensorIndex = (uint8)sensor;

    /* Start of sensor scan */
    `$INSTANCE_NAME`_csdStatusVar = (`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_SW_CTRL_SINGLE_SCAN);
    `$INSTANCE_NAME`_PreScan(sensor);
}


#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanWidget
********************************************************************************
*
* Summary:
*  Sets the scan settings and starts scanning a widget.
*
* Parameters:
*  uint32 widget: Widget number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and clears the single scan mode.
*  `$INSTANCE_NAME`_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to 0xFF and provided to function `$INSTANCE_NAME`_FindNextSensor or
*  `$INSTANCE_NAME`_sensorEnableMask[] - used to store bit masks of the enabled sensors.
*  `$INSTANCE_NAME`_sensorEnableMaskBackup[] - used to backup bit masks of the enabled
*   sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ScanWidget(uint32 widget)
{
    uint32 sensorsPerWidget;
    uint32 lastSensor;
    uint32 snsIndex;

    /* Get first sensor in widget */
    `$INSTANCE_NAME`_sensorIndex = `$INSTANCE_NAME`_rawDataIndex[widget];

    /* Get number of sensors in widget */
    sensorsPerWidget = `$INSTANCE_NAME`_numberOfSensors[widget];

    /* Check if generic Sensor */
    if(sensorsPerWidget == 0u)
    {
        sensorsPerWidget = 1u;
    }

    /* Get last sensor in widget */
    lastSensor = (`$INSTANCE_NAME`_rawDataIndex[widget] + sensorsPerWidget) - 1u;

    /* Backup sensorEnableMask array */
    for(snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_MASK; snsIndex++)
    {
        /* Backup sensorEnableMask array */
        `$INSTANCE_NAME`_sensorEnableMaskBackup[snsIndex] = `$INSTANCE_NAME`_sensorEnableMask[snsIndex];
    }

    /* Update sensorEnableMask to scan the sensors that belong to widget */
    for(snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        /* Update sensorEnableMask array bits to scan the widget only */
        if((snsIndex >= `$INSTANCE_NAME`_sensorIndex) && (snsIndex <= lastSensor))
        {
            /* Set sensor bit to scan */
            `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorEnableMask, snsIndex, 1u);
        }
        else
        {
            /* Reset sensor bit to do not scan */
            `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorEnableMask, snsIndex, 0u);
        }
    }

    /* Check end of scan condition */
    if(`$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
    {
        /* Set widget busy bit in status/control variable*/
        `$INSTANCE_NAME`_csdStatusVar = (`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_SW_CTRL_WIDGET_SCAN);
        /* Scan first sensor of widget*/
        `$INSTANCE_NAME`_PreScan((uint32)`$INSTANCE_NAME`_sensorIndex);
    }
}
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanEnableWidgets
********************************************************************************
*
* Summary:
*  This is the preferred method to scan all of the enabled widgets.
*  The API starts scanning a sensor within the enabled widgets.
*  The ISR continues scanning the sensors until all the enabled widgets are scanned.
*  Use of the ISR ensures this function is non-blocking.
*  All the widgets are enabled by default except proximity widgets.
*  The proximity widgets must be manually enabled as their long scan time
*  is incompatible with a fast response required of other widget types.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and clears the single scan mode.
*  `$INSTANCE_NAME`_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to 0xFF and provided to function `$INSTANCE_NAME`_FindNextSensor or
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ScanEnabledWidgets(void)
{
    /* Clears status/control variable and set sensorIndex */
    `$INSTANCE_NAME`_csdStatusVar = 0u;
    `$INSTANCE_NAME`_sensorIndex = 0xFFu;

    /* Find next sensor */
    `$INSTANCE_NAME`_sensorIndex = (uint8)`$INSTANCE_NAME`_FindNextSensor(`$INSTANCE_NAME`_sensorIndex);

    /* Check end of scan condition */
    if(`$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
    {
        `$INSTANCE_NAME`_csdStatusVar |= `$INSTANCE_NAME`_SW_STS_BUSY;
        `$INSTANCE_NAME`_PreScan((uint32)`$INSTANCE_NAME`_sensorIndex);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusy
********************************************************************************
*
* Summary:
*  Returns the state of the CapSense component. 1 means that scanning in
*  progress and 0 means that scanning is complete.
*
* Parameters:
*  None
*
* Return:
*  Returns the state of scanning. 1 - scanning in progress, 0 - scanning
*  completed.
*
* Global Variables:
*  `$INSTANCE_NAME`_csdStatusVar - used to provide the status and mode of the scanning process.
*  Checks the busy status.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsBusy(void)
{
    return ((uint32)((0u != (`$INSTANCE_NAME`_csdStatusVar & `$INSTANCE_NAME`_SW_STS_BUSY)) ? 1u : 0u));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns sensor raw data from the global CapSense_sensorRaw[ ] array.
*  Each scan sensor has a unique number within the sensor array.
*  This number is assigned by the CapSense customizer in sequence.
*  Raw data can be used to perform calculations outside of the CapSense
*  provided framework.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns the current raw data value for a defined sensor number.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store sensors raw data.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_ReadSensorRaw(uint32 sensor)
{
    return `$INSTANCE_NAME`_sensorRaw[sensor];
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteSensorRaw
********************************************************************************
*
* Summary:
*  This API writes the raw count value passed as an argument to the sensor Raw count array.
*
* Parameters:
*  sensor:  Sensor number.
*  value: Raw count value.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store sensors raw data.
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteSensorRaw(uint32 sensor, uint16 value)
{
    `$INSTANCE_NAME`_sensorRaw[sensor] = value;
}


#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetScanResolution
    ********************************************************************************
    *
    * Summary:
    *  Sets a value of the sensor scan resolution for a widget.
    *  The MIN resolution can be set 8-bit. The MAX Resolution can be set 16 bit.
    *  This function is not available for the tuning mode "None".
    *
    * Parameters:
    *  widget:     Widget index.
    *  resolution: Represents the resolution value. The following defines which are available in the
    *              `$INSTANCE_NAME`.h file should be used:
    *              `$INSTANCE_NAME`_RESOLUTION_6_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_7_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_8_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_9_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_10_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_11_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_12_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_13_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_14_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_15_BITS
    *              `$INSTANCE_NAME`_RESOLUTION_16_BITS
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_widgetResolution[] - used to store scan resolution of each widget.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetScanResolution(uint32 widget, uint32 resolution)
    {
        `$INSTANCE_NAME`_widgetResolution[widget] = resolution;
    }
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetScanResolution
********************************************************************************
*
* Summary:
*  Returns the resolution value for the appropriate sensor.
*  This function is not available for tuning mode "None".
*
* Parameters:
*  widget:     Widget index.
*
* Return:
*  resolution: Returns the resolution value for the appropriate sensor.
*              The resolution values are defined in the `$INSTANCE_NAME`.h file
*              The defines are encountered below:
*              `$INSTANCE_NAME`_RESOLUTION_6_BITS
*              `$INSTANCE_NAME`_RESOLUTION_7_BITS
*              `$INSTANCE_NAME`_RESOLUTION_8_BITS
*              `$INSTANCE_NAME`_RESOLUTION_9_BITS
*              `$INSTANCE_NAME`_RESOLUTION_10_BITS
*              `$INSTANCE_NAME`_RESOLUTION_11_BITS
*              `$INSTANCE_NAME`_RESOLUTION_12_BITS
*              `$INSTANCE_NAME`_RESOLUTION_13_BITS
*              `$INSTANCE_NAME`_RESOLUTION_14_BITS
*              `$INSTANCE_NAME`_RESOLUTION_15_BITS
*              `$INSTANCE_NAME`_RESOLUTION_16_BITS
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetResolution[] - used to store scan resolution of every widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetScanResolution(uint32 widget)
{
    return(`$INSTANCE_NAME`_widgetResolution[widget]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearSensors
********************************************************************************
*
* Summary:
*  Resets all the sensors to the non-sampling state by sequentially disconnecting
*  all the sensors from Analog MUX Bus and putting them to an inactive state.
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
void `$INSTANCE_NAME`_ClearSensors(void)
{
    uint32 snsIndex;

    for (snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        `$INSTANCE_NAME`_DisableScanSlot(snsIndex);
    }
}


#if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Configures the selected slot to measure during the next measurement
    *  cycle. The corresponding pin/pins are set to Analog High-Z mode and
    *  connected to the Analog Mux Bus. This also enables the comparator function.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Constants:
    *  `$INSTANCE_NAME`_portTable[]  - used to store the port number that pin
    *  belongs to for each sensor.
    *  `$INSTANCE_NAME`_maskTable[]  - used to store the pin within the port for
    *  each sensor.
    *  `$INSTANCE_NAME`_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  Bit 7 (msb) is used to define the sensor type: single or complex.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EnableScanSlot(uint32 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 *index;
        /* Read sensor type: single or complex */
        uint8 snsType = `$INSTANCE_NAME`_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & `$INSTANCE_NAME`_COMPLEX_SS_FLAG) == 0u)
        {
            /* Enable sensor (single) */
            `$INSTANCE_NAME`_EnableSensor(slot);
        }
        else
        {
            /* Enable complex sensor */
            snsType &= ~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
            index = &`$INSTANCE_NAME`_indexTable[snsType];
            snsNumber = `$INSTANCE_NAME`_maskTable[slot];

            for (j = 0u; j < snsNumber; j++)
            {
                `$INSTANCE_NAME`_EnableSensor(index[j]);
            }
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DisableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Disables the selected slot. The corresponding pin/pins is/are disconnected
    *  from the Analog Mux Bus and connected to GND, High_Z or Shield electrode.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_portTable[]  - used to store the port number that pin
    *  belongs to for each sensor.
    *  `$INSTANCE_NAME`_maskTable[]  - used to store the pin within the port for
    *  each sensor.
    *  `$INSTANCE_NAME`_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  7bit(msb) is used to define the sensor type: single or complex.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_DisableScanSlot(uint32 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 *index;

        /* Read sensor type: single or complex */
        uint8 snsType = `$INSTANCE_NAME`_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & `$INSTANCE_NAME`_COMPLEX_SS_FLAG) == 0u)
        {
            /* Disable sensor (single) */
            `$INSTANCE_NAME`_DisableSensor(slot);
        }
        else
        {
            /* Disable complex sensor */
            snsType &= ~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
            index = &`$INSTANCE_NAME`_indexTable[snsType];
            snsNumber = `$INSTANCE_NAME`_maskTable[slot];

            for (j=0; j < snsNumber; j++)
            {
                `$INSTANCE_NAME`_DisableSensor(index[j]);
            }
        }
    }
#endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableSensor
********************************************************************************
*
* Summary:
*  Configures the selected sensor to measure during the next measurement cycle.
*  The corresponding pins are set to Analog High-Z mode and connected to the
*  Analog Mux Bus. This also enables the comparator function.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  `$INSTANCE_NAME`_pinShiftTbl[] - used to store position of pin that
*  configured as sensor in port.
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  `$INSTANCE_NAME`_PrtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableSensor(uint32 sensor)
{
    uint8  pinModeShift;
    uint8  pinHSIOMShift;
    uint8 interruptState;
    uint32 newRegisterValue;
    uint32 port;

    port = (uint32) `$INSTANCE_NAME`_portTable[sensor];
    pinModeShift = `$INSTANCE_NAME`_pinShiftTbl[sensor]  * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE;
    pinHSIOMShift = `$INSTANCE_NAME`_pinShiftTbl[sensor] * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = *`$INSTANCE_NAME`_prtSelTbl[port];
    newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)`$INSTANCE_NAME`_CSD_SENSE_PORT_MODE << pinHSIOMShift);

    *`$INSTANCE_NAME`_prtCfgTbl[port] &= (uint32)~((uint32)`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
    *`$INSTANCE_NAME`_prtSelTbl[port] = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableSensor
********************************************************************************
*
* Summary:
*  Disables the selected sensor. The corresponding pin is disconnected from the
*  Analog Mux Bus and connected to GND, High_Z or Shield electrode.
*
* Parameters:
*  sensor:  Sensor number
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  `$INSTANCE_NAME`_pinShiftTbl[] - used to store position of pin that
*  configured as a sensor in the port.
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  `$INSTANCE_NAME`_PrtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableSensor(uint32 sensor)
{
    uint8 interruptState;
    uint32 newRegisterValue;

    uint32 port = (uint32) `$INSTANCE_NAME`_portTable[sensor];
    uint8  pinHSIOMShift = `$INSTANCE_NAME`_pinShiftTbl[sensor] * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE;
    uint8  pinModeShift = `$INSTANCE_NAME`_pinShiftTbl[sensor]  * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE;

    uint32 inactiveConnect = `$INSTANCE_NAME`_SNS_HIZANALOG_CONNECT;
    uint32 sensorState = `$INSTANCE_NAME`_unscannedSnsDriveMode[sensor];

    *`$INSTANCE_NAME`_prtSelTbl[port] &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);

    #if(`$INSTANCE_NAME`_IS_SHIELD_ENABLE != 0)
    if(sensorState != (uint32)`$INSTANCE_NAME`__SHIELD)
    {
    #else
        /* Connected to Ground if shield is disabled */
        if(sensorState == (uint32)`$INSTANCE_NAME`__SHIELD)
        {
            sensorState = (uint32)`$INSTANCE_NAME`__GROUND;
        }
    #endif /* (`$INSTANCE_NAME`_IS_SHIELD_ENABLE) */
        if(sensorState != (uint32)`$INSTANCE_NAME`__HIZ_ANALOG)
        {
            /* Connected to Ground */
            inactiveConnect = (uint32)`$INSTANCE_NAME`_SNS_GROUND_CONNECT;
        }

        interruptState = CyEnterCriticalSection();

        /* Set drive mode */
        newRegisterValue = *`$INSTANCE_NAME`_prtCfgTbl[port];
        newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
        newRegisterValue |=  (uint32)(inactiveConnect << pinModeShift);
        *`$INSTANCE_NAME`_prtCfgTbl[port] =  newRegisterValue;

        CyExitCriticalSection(interruptState);

        *`$INSTANCE_NAME`_prtDRTbl[port]  &=  (uint32)~(uint32)((uint32)1u << `$INSTANCE_NAME`_pinShiftTbl[sensor]);
    #if(`$INSTANCE_NAME`_IS_SHIELD_ENABLE != 0)
    }
    else
    {
        /* Connect to Shield */
        *`$INSTANCE_NAME`_prtSelTbl[port] |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
    }
    #endif /* (`$INSTANCE_NAME`_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDriveModeAllPins
********************************************************************************
*
* Summary:
* This API sets the drive mode of port pins used by the CapSense
* component (sensors, guard, shield, shield tank and Cmod) to drive the
* mode specified by the argument.
*
* Parameters:
*  driveMode:  Drive mode definition.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  `$INSTANCE_NAME`_pinShiftTbl[] - used to store position of pin that
*  configured as a sensor in the port.
*
* Side Effects:
*  This API shall be called only after CapSense component is stopped.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetDriveModeAllPins(uint32 driveMode)
{
    uint8 curSensor;
    #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
        uint8 snsNumber;
        uint8 snsType;
    #endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */
    uint32 prtNumberTmp;
    uint32 pinNumberTmp;

    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; curSensor++)
    {
        #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
            /* Read sensor type: single or complex */
            snsType = `$INSTANCE_NAME`_portTable[curSensor];

            /* Check if sensor is complex */
            if ((snsType & `$INSTANCE_NAME`_COMPLEX_SS_FLAG) == 0u)
            {
                /* The sensor is not complex */
                snsNumber = curSensor;
            }
            else
            {
                /* Get dedicated sensor ID of the complex sensor */
                snsType &= ~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
                snsNumber = `$INSTANCE_NAME`_indexTable[snsType];
            }

            prtNumberTmp = `$INSTANCE_NAME`_portTable[snsNumber];
            pinNumberTmp = `$INSTANCE_NAME`_pinShiftTbl[snsNumber];
        #else
            prtNumberTmp = `$INSTANCE_NAME`_portTable[curSensor];
            pinNumberTmp = `$INSTANCE_NAME`_pinShiftTbl[curSensor];
        #endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */

        `$INSTANCE_NAME`_SetPinDriveMode(driveMode, pinNumberTmp, prtNumberTmp);
    }

    `$INSTANCE_NAME`_SetPinDriveMode(driveMode, (uint32)`$INSTANCE_NAME`_CMOD_PIN_NUMBER, (uint32)`$INSTANCE_NAME`_CMOD_PRT_NUMBER);

    #if(0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE)
        `$INSTANCE_NAME`_SetPinDriveMode(driveMode, (uint32)`$INSTANCE_NAME`_CTANK_PIN_NUMBER, (uint32)`$INSTANCE_NAME`_CTANK_PRT_NUMBER);
    #endif /* (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE) */

    #if(0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE)
        `$INSTANCE_NAME`_SetPinDriveMode(driveMode, (uint32)`$INSTANCE_NAME`_SHIELD_PIN_NUMBER, (uint32)`$INSTANCE_NAME`_SHIELD_PORT_NUMBER);
    #endif /* (0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreDriveModeAllPins
********************************************************************************
*
* Summary:
*  This API restores the drive for all the CapSense port pins to the original
*  state.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*
* Side Effects:
*  This API is called only after the CapSense component is stopped.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreDriveModeAllPins(void)
{
    uint32 newRegisterValue;

    `$INSTANCE_NAME`_SetDriveModeAllPins(CY_SYS_PINS_DM_ALG_HIZ);

    newRegisterValue = `$INSTANCE_NAME`_CMOD_CONNECTION_REG;
    newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
    newRegisterValue |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A;
    `$INSTANCE_NAME`_CMOD_CONNECTION_REG = newRegisterValue;

    #if(0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE)
        newRegisterValue = `$INSTANCE_NAME`_CTANK_CONNECTION_REG;
        newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_CTANK_CONNECTION_MASK);
        newRegisterValue |= `$INSTANCE_NAME`_CSD_CTANK_TO_AMUXBUS_B;
        `$INSTANCE_NAME`_CTANK_CONNECTION_REG = newRegisterValue;
    #endif/* (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE) */

    #if(0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE)
        newRegisterValue = *`$INSTANCE_NAME`_prtSelTbl[`$INSTANCE_NAME`_SHIELD_PORT_NUMBER];
        newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << ((uint32)`$INSTANCE_NAME`_SHIELD_PIN_NUMBER * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE));
        newRegisterValue |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << ((uint32)`$INSTANCE_NAME`_SHIELD_PIN_NUMBER * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE));
        *`$INSTANCE_NAME`_prtSelTbl[`$INSTANCE_NAME`_SHIELD_PORT_NUMBER] = newRegisterValue;
    #endif /* (0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPinDriveMode
********************************************************************************
*
* Summary:
* This API sets the drive mode for the appropriate port/pin.
*
* Parameters:
*  driveMode:  Drive mode definition.
*  portNumber: contains port number (0, 1, 2).
*  pinNumber: contains pin number (0, 1, 2, ... , 7).
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  `$INSTANCE_NAME`_prtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  This API is called only after CapSense component is stopped.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPinDriveMode(uint32 driveMode, uint32 pinNumber, uint32 portNumber)
{
    uint32  pinModeShift;
    uint32 newRegisterValue;

    pinModeShift  = pinNumber * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE;

    newRegisterValue = *`$INSTANCE_NAME`_prtCfgTbl[portNumber];
    newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
    newRegisterValue |=  (uint32)((uint32)driveMode << pinModeShift);
    *`$INSTANCE_NAME`_prtCfgTbl[portNumber] =  newRegisterValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PreScan
********************************************************************************
*
* Summary:
*  Sets required settings, enables a sensor, removes Vref from AMUX and starts the
*  scanning process of the sensor.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
* `$INSTANCE_NAME`_widgetNumber[] - This array contains numbers of widgets for each sensor.
* `$INSTANCE_NAME`_widgetResolution[] - Contains the widget resolution.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PreScan(uint32 sensor)
{
    uint8 widget;
    uint8 interruptState;
    uint32 newRegValue;
    uint32 counterResolution;

    #if(`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO)
        uint8 senseClkDivMath;
        uint8 sampleClkDivMath;
    #endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO) */

    #if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
         (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
        uint32 oversamplingFactor;
    #endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
               (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */

    /* Define widget sensor belongs to */
    widget = `$INSTANCE_NAME`_widgetNumber[sensor];

    /* Recalculate Counter Resolution to MSB 16 bits */
    counterResolution = `$INSTANCE_NAME`_widgetResolution[widget];

    #if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
         (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
        oversamplingFactor = `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_scanSpeedTbl, sensor);

        if(counterResolution < `$INSTANCE_NAME`_RESOLUTION_16_BITS)
        {
            counterResolution <<= oversamplingFactor;
            counterResolution |= (uint32)(`$INSTANCE_NAME`_RESOLUTION_8_BITS);
        }
    #endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
               (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */

    #if (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        `$INSTANCE_NAME`_SenseClk_Stop();
        `$INSTANCE_NAME`_SampleClk_Stop();
    #endif /* (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

    #if (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
        `$INSTANCE_NAME`_SampleClk_SetDividerValue((uint16)`$INSTANCE_NAME`_sampleClkDividerVal[sensor]);
        `$INSTANCE_NAME`_SenseClk_SetDividerValue((uint16)`$INSTANCE_NAME`_senseClkDividerVal[sensor]);
    #else
        `$INSTANCE_NAME`_SampleClk_SetDividerValue((uint16)`$INSTANCE_NAME`_sampleClkDividerVal);
        `$INSTANCE_NAME`_SenseClk_SetDividerValue((uint16)`$INSTANCE_NAME`_senseClkDividerVal);
    #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */

    #if (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        `$INSTANCE_NAME`_SampleClk_Start();
        `$INSTANCE_NAME`_SenseClk_StartEx(`$INSTANCE_NAME`_SampleClk__DIV_ID);

        #if(`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE)
            CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
            `$INSTANCE_NAME`_CSD_CNT_REG = `$INSTANCE_NAME`_ONE_CYCLE;
            while(0u != (`$INSTANCE_NAME`_CSD_CNT_REG & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
            {
            /* Wait until scanning is complete */
            }
            `$INSTANCE_NAME`_CSD_INTR_REG = 1u;
            CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
        #endif /* `$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE */
    #endif /* (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)

    #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
        if(`$INSTANCE_NAME`_prescalersTuningDone != 0u)
        {
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

            CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

            newRegValue = `$INSTANCE_NAME`_CSD_CFG_REG;
            newRegValue |= `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT;

            #if(`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO)

                newRegValue &= ~(`$INSTANCE_NAME`_PRS_MODE_MASK);

                #if (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
                    senseClkDivMath = `$INSTANCE_NAME`_senseClkDividerVal[sensor];
                    sampleClkDivMath = `$INSTANCE_NAME`_sampleClkDividerVal[sensor];
                #else
                    senseClkDivMath = `$INSTANCE_NAME`_senseClkDividerVal;
                    sampleClkDivMath = `$INSTANCE_NAME`_sampleClkDividerVal;
                #endif /* ( `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */

                #if(0u == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
                    senseClkDivMath *= sampleClkDivMath;
                #endif /* (0u == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

                if((senseClkDivMath * `$INSTANCE_NAME`_RESOLUTION_12_BITS) <
                   (sampleClkDivMath * `$INSTANCE_NAME`_widgetResolution[widget]))
                {
                    newRegValue |= `$INSTANCE_NAME`_CSD_PRS_12_BIT;
                }
            #endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO) */

            `$INSTANCE_NAME`_CSD_CFG_REG = newRegValue;

            CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

    #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
        }
    #endif /* (`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE) */

#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

    /* Set Idac Value */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
    newRegValue = `$INSTANCE_NAME`_CSD_IDAC_REG;

#if (`$INSTANCE_NAME`_IDAC_CNT == 1u)
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK);
    newRegValue |= `$INSTANCE_NAME`_modulationIDAC[sensor];
#else
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK | `$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK);
    newRegValue |= (`$INSTANCE_NAME`_modulationIDAC[sensor] |
                            (uint32)((uint32)`$INSTANCE_NAME`_compensationIDAC[sensor] <<
                            `$INSTANCE_NAME`_CSD_IDAC2_DATA_OFFSET));
#endif /* (`$INSTANCE_NAME`_IDAC_CNT == 1u) */

    `$INSTANCE_NAME`_CSD_IDAC_REG = newRegValue;

#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF)
    newRegValue = `$INSTANCE_NAME`_CMOD_CONNECTION_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A;
    `$INSTANCE_NAME`_CMOD_CONNECTION_REG = newRegValue;

    newRegValue = `$INSTANCE_NAME`_CMOD_PORT_PC_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_PC_MASK);
    newRegValue |= `$INSTANCE_NAME`_CMOD_PC_HIGH_Z_MODE;
    `$INSTANCE_NAME`_CMOD_PORT_PC_REG = newRegValue;
#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */

    /* Disconnect Vref Buffer from AMUX */
    newRegValue = `$INSTANCE_NAME`_CSD_CFG_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK);
    newRegValue |= `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG;

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Enable Sensor */
    `$INSTANCE_NAME`_EnableScanSlot(sensor);

    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CSD_CFG_REG = newRegValue;

    /* `#START `$INSTANCE_NAME`_PreSettlingDelay_Debug` */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK
    `$INSTANCE_NAME`_PreScan_Pre_SettlingDelay_Debug_Callback();
#endif /* `$INSTANCE_NAME`_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK */

    CyDelayCycles(`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES);

    /* `#START `$INSTANCE_NAME`_PreScan_Debug` */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_PRE_SCAN_DEBUG_CALLBACK
    `$INSTANCE_NAME`_PreScan_Debug_Callback();
#endif /* `$INSTANCE_NAME`_PRE_SCAN_DEBUG_CALLBACK */

    `$INSTANCE_NAME`_CSD_CNT_REG = counterResolution;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PostScan
********************************************************************************
*
* Summary:
*  Stores the results of measurement in the `$INSTANCE_NAME`_sensorRaw[] array,
*  sets the scanning sensor in the non-sampling state, turns off Idac(Current Source IDAC),
*  disconnects the IDAC(Sink mode), and applies Vref on AMUX.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store sensors raw data.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PostScan(uint32 sensor)
{
    uint32 newRegValue;
#if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
     (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
    uint32 oversamplingFactor;
    uint32 widget;
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
           (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */

    /* `#START `$INSTANCE_NAME`_PostScan_Debug` */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_POST_SCAN_DEBUG_CALLBACK
    `$INSTANCE_NAME`_PostScan_Debug_Callback();
#endif /* `$INSTANCE_NAME`_POST_SCAN_DEBUG_Callback */

    /* Read SlotResult from Raw Counter */
    `$INSTANCE_NAME`_sensorRaw[sensor]  = (uint16)`$INSTANCE_NAME`_CSD_CNT_REG;

#if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
     (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
    widget = `$INSTANCE_NAME`_widgetNumber[sensor];
    if(`$INSTANCE_NAME`_widgetResolution[widget] < `$INSTANCE_NAME`_RESOLUTION_16_BITS)
    {
        oversamplingFactor = `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_scanSpeedTbl, sensor);
        `$INSTANCE_NAME`_sensorRaw[sensor] >>= oversamplingFactor;
    }
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
           (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */

    /* Disable Sensor */
    `$INSTANCE_NAME`_DisableScanSlot(sensor);

    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF)
    newRegValue = `$INSTANCE_NAME`_CMOD_CONNECTION_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_B;
    `$INSTANCE_NAME`_CMOD_CONNECTION_REG = newRegValue;

    newRegValue = `$INSTANCE_NAME`_CMOD_PORT_PC_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_PC_MASK);
    newRegValue |= `$INSTANCE_NAME`_CMOD_PC_STRONG_MODE;
    `$INSTANCE_NAME`_CMOD_PORT_PC_REG = newRegValue;

    newRegValue = `$INSTANCE_NAME`_CMOD_PORT_DR_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CMOD_DR_MASK);
    newRegValue |= `$INSTANCE_NAME`_CMOD_DR_CONFIG;
    `$INSTANCE_NAME`_CMOD_PORT_DR_REG = newRegValue;
#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */

    /* Connect Vref Buffer to AMUX bus  */
    newRegValue = `$INSTANCE_NAME`_CSD_CFG_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK);
    newRegValue |= `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG;
    `$INSTANCE_NAME`_CSD_CFG_REG = newRegValue;

    /* Set Idac Value = 0 */
#if (`$INSTANCE_NAME`_IDAC_CNT == 1u)
    `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK);
#else
    `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK | `$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK);
#endif /* (`$INSTANCE_NAME`_IDAC_CNT == 1u) */

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableShieldElectrode
********************************************************************************
*
* Summary:
*  This API enables or disables the shield electrode on a specified port pin.
*
* Parameters:
*  portNumber: contains the shield electrode port number (0, 1, 2).
*  pinNumber: contains the shield electrode pin number (0, 1, 2, ... , 7).
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_prtCfgTbl[] - Contains pointers to the port config registers for each port.
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableShieldElectrode(uint32 pinNumber, uint32 portNumber)
{
    uint32 newRegValue;

    *`$INSTANCE_NAME`_prtCfgTbl[portNumber] &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << (pinNumber * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE));
    newRegValue = *`$INSTANCE_NAME`_prtSelTbl[portNumber];
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << (pinNumber * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE));
    newRegValue |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << (pinNumber * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE));
    *`$INSTANCE_NAME`_prtSelTbl[portNumber] = newRegValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetShieldDelay
********************************************************************************
*
* Summary:
*  This API sets a shield delay.
*
* Parameters:
*  delay:  shield delay value:
*                               0 - no delay
*                               1 - 1 cycle delay
*                               2 - 2 cycles delay
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
void `$INSTANCE_NAME`_SetShieldDelay(uint32 delay)
{
    uint32 newRegValue;

    delay &= 0x03u;

    newRegValue = `$INSTANCE_NAME`_CSD_CFG_REG;
    newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_SHIELD_DELAY);
    newRegValue |= (delay << `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY_POS);
    `$INSTANCE_NAME`_CSD_CFG_REG = newRegValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCurrentScanningSensor
********************************************************************************
*
* Summary:
*  This API returns scanning sensor number when sensor scan is in progress.
*  When sensor scan is completed the API returns
*  $INSTANCE_NAME`_NOT_SENSOR (0xFFFFFFFF) (when no sensor is scanned).
*
* Parameters:
*   None.
*
* Return:
*  Returns Sensor number if sensor is being scanned and
*  $INSTANCE_NAME`_NOT_SENSOR (0xFFFFFFFF) if scanning is complete.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorIndex - the sensor number is being scanned.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadCurrentScanningSensor(void)
{
    return ((uint32)(( 0u != (`$INSTANCE_NAME`_csdStatusVar & `$INSTANCE_NAME`_SW_STS_BUSY)) ?
                     `$INSTANCE_NAME`_sensorIndex : `$INSTANCE_NAME`_NOT_SENSOR));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetBitValue
********************************************************************************
*
* Summary:
*  The API returns a bit status of the bit in the table array which contains the masks.
*
* Parameters:
*  table[] - array with bit masks.
*  position - position of bit in the table[] array.
*
* Return:
*  0 - bit is not set; 1 - bit is set.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetBitValue(const uint8 table[], uint32 position)
{
    uint32 offset;
    uint8 enMask;

    /* position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for an appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of the
       table[] array.
    */
    enMask = 0x01u << (position & 0x07u);

    return ((0u !=(table[offset] & enMask)) ? 1Lu : 0Lu);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBitValue
********************************************************************************
*
* Summary:
*  The API sets a bit status of the bit in the table array which contains masks.
*
* Parameters:
*  table[] - array with bit masks.
*  position - position of bit in the table[] array.
*  value: 0 - bit is not set; 1 - bit is set.
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
void `$INSTANCE_NAME`_SetBitValue(uint8 table[], uint32 position, uint32 value)
{
    uint32 offset;
    uint8 enMask;

    /* position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for an appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of the
       table[] array.
    */
    enMask = 0x01u << (position & 0x07u);

    if(0u != value)
    {
        table[offset] |= enMask;
    }
    else
    {
        table[offset] &= (uint8)~(enMask);
    }
}



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSenseClkDivider
********************************************************************************
*
* Summary:
*  This API returns a value of the sense clock divider for the  sensor.
*
* Parameters:
*  sensor: sensor index. The index value can be
*  from 0 to (`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the sense clock divider of the sensor.
*
* Global Variables:
*  `$INSTANCE_NAME`_senseClkDividerVal[] - stores the sense clock divider values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetSenseClkDivider(uint32 sensor)
{
    #if(0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
        return((uint32)`$INSTANCE_NAME`_senseClkDividerVal[sensor]);
    #else
        return((uint32)`$INSTANCE_NAME`_senseClkDividerVal);
    #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */
}

#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetSenseClkDivider
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the sense clock divider for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  senseClk: represents the sense clock value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_senseClkDividerVal[] - stores the sense clock divider values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetSenseClkDivider(uint32 sensor, uint32 senseClk)
    {
        #if(0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
            `$INSTANCE_NAME`_senseClkDividerVal[sensor] = (uint8)senseClk;
        #else
            `$INSTANCE_NAME`_senseClkDividerVal = (uint8)senseClk;
        #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */
    }
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetModulatorClkDivider
********************************************************************************
*
* Summary:
*  This API returns a value of the modulator sample clock divider for the  sensor.
*
* Parameters:
*  sensor: sensor index. The value of index can be
*  from 0 to (`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the modulator sample clock divider for the  sensor.
*
* Global Variables:
*  `$INSTANCE_NAME`_sampleClkDividerVal[] - stores the modulator sample divider values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetModulatorClkDivider(uint32 sensor)
{
    #if(0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
        return((uint32)`$INSTANCE_NAME`_sampleClkDividerVal[sensor]);
    #else
        return((uint32)`$INSTANCE_NAME`_sampleClkDividerVal);
    #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */
}

#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetModulatorClkDivider
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the modulator sample clock divider for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  modulatorClk: represents the modulator sample clock value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_sampleClkDividerVal[] - stores the modulator sample divider values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk)
    {
        #if(0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
            `$INSTANCE_NAME`_sampleClkDividerVal[sensor] = (uint8)modulatorClk;
        #else
            `$INSTANCE_NAME`_sampleClkDividerVal = (uint8)modulatorClk;
        #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */
    }
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetModulationIDAC
********************************************************************************
*
* Summary:
*  This API returns a value of the modulation IDAC for the  sensor.
*
* Parameters:
*  sensor: sensor index. The index value can be
*  from 0 to (`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the modulation IDAC of the sensor.
*
* Global Variables:
*  `$INSTANCE_NAME`_modulationIDAC[] - stores modulation IDAC values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetModulationIDAC(uint32 sensor)
{
        return((uint32)`$INSTANCE_NAME`_modulationIDAC[sensor]);
}

#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetModulationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the modulation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  compIdacValue: represents the modulation IDAC data register value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_modulationIDAC[] - array with modulation IDAC values
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetModulationIDAC(uint32 sensor, uint32 modIdacValue)
    {
        `$INSTANCE_NAME`_modulationIDAC[sensor] = (uint8)modIdacValue;
    }
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */


#if(`$INSTANCE_NAME`_IDAC_CNT > 1u)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCompensationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API returns a value of the compensation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor: sensor index. The index value can be
    *  from 0 to (`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT-1).
    *
    * Return:
    *  This API returns the compensation IDAC of the sensor.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_compensationIDAC[] - stores the compensation IDAC values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetCompensationIDAC(uint32 sensor)
    {
        return((uint32)`$INSTANCE_NAME`_compensationIDAC[sensor]);
    }
#endif /* (`$INSTANCE_NAME`_IDAC_CNT > 1u) */


#if((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (`$INSTANCE_NAME`_IDAC_CNT > 1u))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCompensationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of compensation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  compIdacValue: represents the compensation IDAC data register value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_compensationIDAC[] - an array with compensation IDAC values
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue)
    {
        `$INSTANCE_NAME`_compensationIDAC[sensor] = (uint8)compIdacValue;
    }
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (`$INSTANCE_NAME`_IDAC_CNT > 1u)) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetIDACRange
********************************************************************************
*
* Summary:
*  This API returns a value that indicates the IDAC range used by the
*  component to scan sensors. The IDAC range is common for all the sensors.
*
* Parameters:
*  None
*
* Return:
*  This API Returns a value that indicates the IDAC range:
*      0 - IDAC range set to 4x
*      1 - IDAC range set to 8x
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetIDACRange(void)
{
    return((0u != (`$INSTANCE_NAME`_CSD_IDAC_REG & `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X)) ? 1uL : 0uL);
}

#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetIDACRange
    ********************************************************************************
    *
    * Summary:
    *  This API sets the IDAC range to the 4x (1.2uA/bit) or 8x (2.4uA/bit) mode.
    *  The IDAC range is common for all the sensors and common for the modulation and
    *  compensation IDACs.
    *
    * Parameters:
    *  iDacRange:  represents value for IDAC range
    *  0 -  IDAC range set to 4x (1.2uA/bit)
    *  1 or >1 - IDAC range set to 8x (2.4uA/bit)
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetIDACRange(uint32 iDacRange)
    {
        if(iDacRange != 0u)
        {
            /*  IDAC range = 8x (2.4uA/bit) */
            `$INSTANCE_NAME`_CSD_IDAC_REG |= (`$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X |\
                                              `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X);
        }
        else
        {
            /*  IDAC range = 4x (1.2uA/bit) */
            /*  IDAC range = 8x (2.4uA/bit) */
            `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X |\
                                               `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X);
        }
    }
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */


#if((0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO))
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
    *  Returns the current raw data value for a defined sensor number.
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
#endif /* ((0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) && (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) */


#if((0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CalibrateSensor
    ********************************************************************************
    *
    * Summary:
    *  Computes the one sensor IDAC value, which provides the raw signal on
    *  a specified level, with a specified prescaler, speed, and resolution.
    *
    * Parameters:
    *  sensor - Sensor Number.
    *
    *  rawLevel -  Raw data level which should be reached during the calibration
    *              procedure.
    *
    *  idacLevelsTbl - Pointer to the modulatorIdac data register configuration table.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_CalibrateSensor(uint32 sensor, uint32 rawLevel, uint8 idacLevelsTbl[])
    {
        uint8 mask;
        uint16 rawData;

        rawData = 0u;

        mask = 0x80u;
        /* Init IDAC for null Channel */
        idacLevelsTbl[sensor] = 0x00u;

        do
        {
            /* Set bit for null Channel */
            idacLevelsTbl[sensor] |= mask;

            /* Scan null Channel and get Rawdata */
            rawData = `$INSTANCE_NAME`_GetSensorRaw(sensor);

            /* Decrease IDAC until Rawdata reaches rawLevel */
            if(rawData < rawLevel)
            {
                /* Reset bit for null Channel  */
                idacLevelsTbl[sensor] &= (uint8)~mask;
            }

            mask >>= 1u;
        }
        while(mask > 0u);

    }
#endif /* ((0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) && (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_AUTO)) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUnscannedSensorState
********************************************************************************
*
* Summary:
*  This API sets a state for un-scanned sensors.
*  It is possible to set the state to Ground, High-Z, or the shield electrode.
*  The un-scanned sensor can be connected to a shield electrode only if the shield is
*  enabled. If the shield is disabled and this API is called with the parameter which
*  indicates the shield state, the un-scanned sensor will be connected to Ground.
*
* Parameters:
*  sensor - Sensor Number.
*  sensorState: This parameter indicates un-scanned sensor state:
*
*     `$INSTANCE_NAME`__GROUND 0
*     `$INSTANCE_NAME`__HIZ_ANALOG 1
*     `$INSTANCE_NAME`__SHIELD 2
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_unscannedSnsDriveMode[] - used to store the state for
*  un-scanned sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetUnscannedSensorState(uint32 sensor, uint32 sensorState)
{
    #if(`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
        uint8 snsType;
        uint8 curSensor;
        uint16 snsNumber;

        /* Read sensor type: single or complex */
        snsType = `$INSTANCE_NAME`_portTable[sensor];

        /* Check if sensor is complex */
        if(0u != (snsType & `$INSTANCE_NAME`_COMPLEX_SS_FLAG))
        {
            snsType &= (uint8)~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
            snsNumber = (uint16)`$INSTANCE_NAME`_maskTable[sensor];

            for (curSensor=0u; curSensor < snsNumber; curSensor++)
            {
                sensor = `$INSTANCE_NAME`_indexTable[snsType + curSensor];
                `$INSTANCE_NAME`_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
            }
        }
        else
        {
            `$INSTANCE_NAME`_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
        }
    #else
        `$INSTANCE_NAME`_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
    #endif /* (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS) */
}

#if(0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_NormalizeWidgets
********************************************************************************
*
* Summary:
*  This API aligns all the parameters of the widget to the maximum parameter.
*
* Parameters:
*  uint32 widgetsNum: Number of widgets.
*  uint8 *dataPrt: pointer to array with widget parameters.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_numberOfSensors[] - Number of sensors in the widget.
*  `$INSTANCE_NAME`_rawDataIndex[currentWidget] - Contains the  1st sensor
*  position in the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_NormalizeWidgets(uint32 widgetsNum, uint8 dataPtr[])
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
#endif /* (0u != `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT) */

/* [] END OF FILE */
