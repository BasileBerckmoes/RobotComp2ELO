/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of the scanning APIs for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
    #include "`$INSTANCE_NAME`_CSHL.h"
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    #include "`$INSTANCE_NAME`_SMS.h"
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

#if (0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER)
    #include "`$INSTANCE_NAME`_SLDR.h"
    extern uint8 `$INSTANCE_NAME`_widgetsNum;
#endif  /* (0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER) */

#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    uint8 `$INSTANCE_NAME`_immunityIndex;
    extern uint8 `$INSTANCE_NAME`_highImmunityEnable;
    extern `$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 `$INSTANCE_NAME`_config;
#endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

/* SmartSense functions */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    uint8 `$INSTANCE_NAME`_lowLevelTuningDone = 0u;
    extern uint8 `$INSTANCE_NAME`_thresholdMode;
    extern uint8 baSpeed[((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
    uint8 `$INSTANCE_NAME`_prescalersTuningDone = 0u;
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

static uint8 `$INSTANCE_NAME`_initVar = 0u;
static uint32 `$INSTANCE_NAME`_isShieldEnabled = 0u;

#if(0u != `$INSTANCE_NAME`_BIST_API_GENERATE)
    extern uint8 `$INSTANCE_NAME`_isDiagnosticEnabled;
    extern uint32 `$INSTANCE_NAME`_diagnosticCsdConfig;
#endif /* (0u != `$INSTANCE_NAME`_BIST_API_GENERATE) */

/* Global software variables */
uint8 `$INSTANCE_NAME`_delayCyclesNum = `$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES;
volatile uint8 `$INSTANCE_NAME`_csdStatusVar = 0u;   /* CapSense CSD status, control variable */
volatile uint8 `$INSTANCE_NAME`_sensorIndex = 0u;    /* Index of scanning sensor */

/* Global array of Raw Counts */
uint16 `$INSTANCE_NAME`_sensorRaw[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT] = {0u};

/* Backup variables for trim registers*/

#if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
    uint8 `$INSTANCE_NAME`_csdTrim2;
#else
    uint8 `$INSTANCE_NAME`_csdTrim1;
#endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

/* Configured constants and arrays by Customizer */
`$writerCVariables`


/* Configured constants for ports */

reg32* const `$INSTANCE_NAME`_prtSelTbl[] = {
    ((reg32 *) CYREG_HSIOM_PORT_SEL0),
    ((reg32 *) CYREG_HSIOM_PORT_SEL1),
    ((reg32 *) CYREG_HSIOM_PORT_SEL2),
    ((reg32 *) CYREG_HSIOM_PORT_SEL3),
#if(0u == CY_PSOC4SF)
    ((reg32 *) CYREG_HSIOM_PORT_SEL4)
#endif /* (0u == CY_PSOC4SF) */
};

reg32* const `$INSTANCE_NAME`_prtCfgTbl[] = {
    ((reg32 *) `$PrtRegNameReplacementString`_PRT0_PC),
    ((reg32 *) `$PrtRegNameReplacementString`_PRT1_PC),
    ((reg32 *) `$PrtRegNameReplacementString`_PRT2_PC),
    ((reg32 *) `$PrtRegNameReplacementString`_PRT3_PC),
#if(0u == CY_PSOC4SF)
    ((reg32 *) `$PrtRegNameReplacementString`_PRT4_PC)
#endif /* (0u == CY_PSOC4SF) */
};

reg32* const `$INSTANCE_NAME`_prtDRTbl[] = {
    ((reg32 *) `$PrtRegNameReplacementString`_PRT0_DR),
    ((reg32 *) `$PrtRegNameReplacementString`_PRT1_DR),
    ((reg32 *) `$PrtRegNameReplacementString`_PRT2_DR),
    ((reg32 *) `$PrtRegNameReplacementString`_PRT3_DR),
#if(0u == CY_PSOC4SF)
    ((reg32 *) `$PrtRegNameReplacementString`_PRT4_DR),
#endif /* (0u == CY_PSOC4SF) */
};

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  The Inits default CapSense configuration provided by the customizer that defines
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

        `$INSTANCE_NAME`_SetShieldState(`$INSTANCE_NAME`_SHIELD_PIN_NUMBER, `$INSTANCE_NAME`_SHIELD_PORT_NUMBER);

    #endif /* (`$INSTANCE_NAME`_IS_SHIELD_ENABLE) */

    #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        `$INSTANCE_NAME`_immunityIndex = 0u;

        if(`$INSTANCE_NAME`_highImmunityEnable == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        {
            `$INSTANCE_NAME`_SetImmunityLevel(1u);
        }
    #endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

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
*  `$INSTANCE_NAME`_csdTrim1 - contains the IDAC trim register value for the Sourcing Mode.
*  `$INSTANCE_NAME`_csdTrim2 - contains the IDAC trim register value for the Sinking Mode.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_CsdHwBlockInit(void)
{
    uint32 newRegValue;

    #if((`$INSTANCE_NAME`_CHAINED_CLOCKS != `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED) && (0u == CY_PSOC4SF)) // TODO: Should be removed after migration to SF silicon.
        newRegValue = CY_GET_XTND_REG32((void CYFAR *)(CYREG_CLK_DIVIDER_B00));   // TODO: Should be used CapSense clock defines.
        CY_SET_XTND_REG32((void CYFAR *)(CYREG_CLK_DIVIDER_B00), newRegValue & (~0x40000000uL));
    #endif  /* ((`$INSTANCE_NAME`_CHAINED_CLOCKS != `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED) && (0u == CY_PSOC4SF)) */

        /* Set trim registers for CSD Mode */
    #if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
        /* iDAC1 Sinking Mode */
        `$INSTANCE_NAME`_csdTrim2 = `$INSTANCE_NAME`_CSD_TRIM2_REG;
        newRegValue = `$INSTANCE_NAME`_csdTrim2;
        newRegValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK);

        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
            /* iDAC2 Sinking Mode */
            newRegValue &= `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK);
        #endif
        `$INSTANCE_NAME`_CSD_TRIM2_REG = newRegValue;
    #else
        /* iDAC1 Sourcing Mode */
        `$INSTANCE_NAME`_csdTrim1 = `$INSTANCE_NAME`_CSD_TRIM1_REG;
        newRegValue = `$INSTANCE_NAME`_csdTrim1;
        newRegValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK);
        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
             /* iDAC2 Sourcing Mode */
            newRegValue &= `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK);
        #endif
        `$INSTANCE_NAME`_CSD_TRIM1_REG = newRegValue;
    #endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

    /* Configure CSD and IDAC */
    `$INSTANCE_NAME`_CSD_IDAC_REG = `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG;
    `$INSTANCE_NAME`_CSD_CFG_REG = `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG;

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
*  Enables the CSD block and related resources to active mode.
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

    #if (0u == CY_PSOC4SF)
        `$INSTANCE_NAME`_SenseClk_Start();
        `$INSTANCE_NAME`_SampleClk_Start();
    #else
        `$INSTANCE_NAME`_SampleClk_Start();
        `$INSTANCE_NAME`_SenseClk_StartEx(`$INSTANCE_NAME`_SampleClk__DIV_ID);
    #endif /* (0u == CY_PSOC4SF) */

    /* Enable CSD block */
    newRegValue = `$INSTANCE_NAME`_CSD_CFG_REG;
    newRegValue |= (`$INSTANCE_NAME`_CSD_CFG_ENABLE | `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN);
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
*  any other API routine.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   `$INSTANCE_NAME`_isDiagnosticEnabled - used to scan the sensor with parameters
*   to measure capacitance with the GetSensorCp API
*   `$INSTANCE_NAME`_initVar - used to check the initial configuration,
*   modified on the first function call.
*  `$INSTANCE_NAME`_lowLevelTuningDone - used to notify the Tuner GUI that
*  the tuning parameters scanning is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    #if(0u != CharComp_BIST_API_GENERATE)
        `$INSTANCE_NAME`_isDiagnosticEnabled = 0u;
    #endif /* (0u != CharComp_BIST_API_GENERATE) */

    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();

    /* AutoTunning start */
    #if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&\
         (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE))
        /* AutoTune by sensor basis */
        `$INSTANCE_NAME`_AutoTune();
        `$INSTANCE_NAME`_lowLevelTuningDone = 1u;
    #endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) &&
               (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)) */

    /* Connect the sense comparator input to AMUXA */
    `$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL;
}


/*******************************************************************************
* Function Name: $INSTANCE_NAME`_StartEx
********************************************************************************
*
* Summary:
*  This API initializes the CapSense sensor block.
*  The sensor is configured based on the sensorMask value.
*  If a corresponding mask bit is set, the sensor will be enabled and if the mask
*  bit is cleared, the sensor will not be initialized by this API.
*  The uninitialized sensor pins will be available for the application firmware
*  to implement any functionality.
*
* Parameters:
*  sensorMask - Sensor mask. Each bit represents a sensor.
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
void `$INSTANCE_NAME`_StartEx(uint32 sensorMask)
{
    `$INSTANCE_NAME`_SetActiveSensors(sensorMask);
    `$INSTANCE_NAME`_Start();
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
*  `$INSTANCE_NAME`_csdTrim1 - contains the IDAC trim register value for the Sourcing Mode.
*  `$INSTANCE_NAME`_csdTrim2 - contains the IDAC trim register value for the Sinking Mode.
*
* Side Effects:
*  This function should be called after scans are completed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    /* Disable interrupt */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Clear all sensors */
    `$INSTANCE_NAME`_ClearSensors();

    /* Disable Clocks */
    `$INSTANCE_NAME`_SenseClk_Stop();
    `$INSTANCE_NAME`_SampleClk_Stop();

    /* Restore trim registers */
    #if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
        /* iDAC Sinking Mode */
        `$INSTANCE_NAME`_CSD_TRIM2_REG = `$INSTANCE_NAME`_csdTrim2;
    #else
        /* iDAC Sourcing Mode */
        `$INSTANCE_NAME`_CSD_TRIM1_REG = `$INSTANCE_NAME`_csdTrim1;
    #endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

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
*  `$INSTANCE_NAME`_sensorEnableMask[] - used to store the bit masks of the enabled sensors.
*
* Side Effects:
*  This function affects the current scanning and should not
*  be used outside the  component.
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
        enableFlag = `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_sensorEnableMask, snsIndex);
    }
    while(enableFlag == 0u);

    return ((uint8)snsIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanSensor
********************************************************************************
*
* Summary:
*  Sets the scan settings and starts scanning the  sensor. After scanning is complete,
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
*  Sets the busy status(scan in progress) and mode of scan as a single scan.
*  `$INSTANCE_NAME`_sensorIndex - used to store the sensor scanning sensor number.
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


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanEnableWidgets
********************************************************************************
*
* Summary:
*  This is the preferred method to scan all of the enabled widgets.
*  The API starts scanning the  sensor within the enabled widgets.
*  The ISR continues scanning the sensors until all the enabled widgets are scanned.
*  Use of the ISR ensures this function is non-blocking.
*  All the widgets are enabled by default except proximity widgets.
*  The proximity widgets must be manually enabled as their long scan time
*  is incompatible with the fast response required of other widget types.
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
*  `$INSTANCE_NAME`_sensorIndex - used to store the sensor scanning sensor number.
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
        `$INSTANCE_NAME`_PreScan(`$INSTANCE_NAME`_sensorIndex);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusy
********************************************************************************
*
* Summary:
*  Returns the state of the CapSense component. 1 means that scanning is in
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
* Function Name: `$INSTANCE_NAME`_SetActiveSensors
********************************************************************************
*
* Summary:
*  This API sets the mask bit for the  sensor. Each bit in the argument represents
*  the sensor and the sensor is disabled or enabled based on the mask bit.
*  The disabled sensor is not scanned when the scan API is called.
*
* Parameters:
*  value: sensor enable mask for sensors.
*  1 - Enables the respective sensor
*  0 - Disables the respective sensor
*
* Return Value:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorEnableMask[ ] - used to store the bit masks of the enabled sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetActiveSensors(uint32 value)
{
    uint32 snsIndex;

    for(snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorEnableMask, snsIndex, (value & 1Lu));
        value >>= 1u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns the sensor raw data from the global CapSense_sensorRaw[ ] array.
*  Each scan sensor has a unique number within the sensor array.
*  This number is assigned by the CapSense customizer in sequence.
*  Raw data can be used to perform calculations outside the CapSense
*  provided framework.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns current raw data value for a defined sensor number.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store the sensors raw data.
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
*  `$INSTANCE_NAME`_sensorRaw[] - used to store the sensors raw data.
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
    *  Sets value of sensor scan resolution for a widget.
    *  The MIN resolution can be set is 8-bit. The MAX Resolution can be set is 16 bit.
    *  This function is not available for the tuning mode "None".
    *
    * Parameters:
    *  widget:     Widget index.
    *  resolution: Represents the resolution value. The following defines which are available in the
    *              `$INSTANCE_NAME`.h file should be used:
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_8_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_9_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_10_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_11_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_12_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_13_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_14_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_15_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_16_BITS
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_widgetResolution[] - used to store scan resolution of every widget.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetScanResolution(uint32 widget, uint32 resolution)
    {
        `$INSTANCE_NAME`_widgetResolution[widget] = (uint8)resolution;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetScanResolution
    ********************************************************************************
    *
    * Summary:
    *  Returns the resolution value the appropriate sensor.
    *  This function is not available for the tuning mode "None".
    *
    * Parameters:
    *  widget:     Widget index.
    *
    * Return:
    *  resolution: Returns the resolution value for the appropriate sensor.
    *              The resolution values are defined in the `$INSTANCE_NAME`.h file
    *              The defines are encountered below:
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_8_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_9_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_10_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_11_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_12_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_13_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_14_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_15_BITS
    *              `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_16_BITS
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
        return((uint32)`$INSTANCE_NAME`_widgetResolution[widget]);
    }
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */


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
    uint32 isSensorEnabled;

#if(0 != `$INSTANCE_NAME`_IS_STREET_FIGHTER)

    for (snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        isSensorEnabled = `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_sensorEnableMask, snsIndex);

        if(0u != isSensorEnabled)
        {
            `$INSTANCE_NAME`_DisableScanSlot(snsIndex);
        }
    }

#else
    for (snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        `$INSTANCE_NAME`_DisableScanSlot(snsIndex);
    }
#endif /* (0 != `$INSTANCE_NAME`_IS_STREET_FIGHTER) */
}


#if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Configures the selected slot to measure during the next measurement
    *  cycle. The corresponding pin/pins are set to the Analog High-Z mode and
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
    *  belongs to for every sensor.
    *  `$INSTANCE_NAME`_maskTable[]  - used to store the pin within the port for
    *  every sensor.
    *  `$INSTANCE_NAME`_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  The bit 7 (msb) is used to define the sensor type: single or complex.
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
    *  from the Analog Mux Bus and connected to GND, High_Z, or the Shield electrode.
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
    *  `$INSTANCE_NAME`_indexTable[] - used to store the indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  The 7bit(msb) is used to define the sensor type: single or complex.
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
*  The corresponding pins are set to the Analog High-Z mode and connected to the
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
*  `$INSTANCE_NAME`_pinShiftTbl[] - used to store a position of the pin that
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
void `$INSTANCE_NAME`_EnableSensor(uint32 sensor)
{
    uint8  pinModeShift;
    uint8  pinHSIOMShift;
    uint32 newRegisterValue;
    uint32 port;

    port = (uint32) `$INSTANCE_NAME`_portTable[sensor];
    pinModeShift = `$INSTANCE_NAME`_pinShiftTbl[sensor]  * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE;
    pinHSIOMShift = `$INSTANCE_NAME`_pinShiftTbl[sensor] * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE;

    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    newRegisterValue = *`$INSTANCE_NAME`_prtSelTbl[port];
    newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)`$INSTANCE_NAME`_CSD_SENSE_PORT_MODE << pinHSIOMShift);

    *`$INSTANCE_NAME`_prtCfgTbl[port] &= (uint32)~((uint32)`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
    *`$INSTANCE_NAME`_prtSelTbl[port] = newRegisterValue;

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableSensor
********************************************************************************
*
* Summary:
*  Disables the selected sensor. The corresponding pin is disconnected from the
*  Analog Mux Bus and connected to GND, High_Z, or the Shield electrode.
*
* Parameters:
*  sensor:  Sensor number
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_portTable[] - used to store the port number that the pin
*  belongs to for each sensor.
*  `$INSTANCE_NAME`_pinShiftTbl[] - used to store a position of the pin that is
*  configured as a sensor in the port.
*  `$INSTANCE_NAME`_prtSelTbl[] - contains pointers to the HSIOM
*  registers for each port.
*  `$INSTANCE_NAME`_PrtCfgTb[] - contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableSensor(uint32 sensor)
{
    uint32 port = (uint32) `$INSTANCE_NAME`_portTable[sensor];
    uint8  pinHSIOMShift = `$INSTANCE_NAME`_pinShiftTbl[sensor] * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE;
#if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS != `$INSTANCE_NAME`__SHIELD)
    uint32 newRegisterValue;
    uint8  pinModeShift = `$INSTANCE_NAME`_pinShiftTbl[sensor]  * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE;
#endif


    *`$INSTANCE_NAME`_prtSelTbl[port] &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);

#if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__SHIELD)
    *`$INSTANCE_NAME`_prtSelTbl[port] |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
#else

    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    newRegisterValue = *`$INSTANCE_NAME`_prtCfgTbl[port];
    newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
    newRegisterValue |=  (uint32)((uint32)`$INSTANCE_NAME`_CSD_INACTIVE_CONNECT << pinModeShift);
    *`$INSTANCE_NAME`_prtCfgTbl[port] =  newRegisterValue;

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

    *`$INSTANCE_NAME`_prtDRTbl[port]  &=  (uint32)~(uint32)((uint32)1u << `$INSTANCE_NAME`_pinShiftTbl[sensor]);

#endif /* `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__SHIELD */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PreScan
********************************************************************************
*
* Summary:
*  Sets the required settings, enables the  sensor, removes Vref from AMUX and starts the
*  scanning process of the sensor.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
* `$INSTANCE_NAME`_widgetNumber[] - the array contains numbers of widgets for each sensor.
* `$INSTANCE_NAME`_widgetResolution[] - contains the widget resolution in the MSB part.
*  baSpeed[] - contains an oversampling value for each sensor.
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
    uint32 immunitySensorIndex;

#if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
    uint32 oversamplingFactor;
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */

    /* Define widget sensor belongs to */
    widget = `$INSTANCE_NAME`_widgetNumber[sensor];

    /* Recalculate Counter Resolution to MSB 16 bits */
    counterResolution = (((uint32)`$INSTANCE_NAME`_widgetResolution[widget]) << `$INSTANCE_NAME`_MSB_RESOLUTION_OFFSET);
    counterResolution |= `$INSTANCE_NAME`_RESOLUTION_8_BITS;

#if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
    oversamplingFactor = `$INSTANCE_NAME`_GetBitValue(baSpeed, sensor);

    if(counterResolution < `$INSTANCE_NAME`_RESOLUTION_16_BITS)
    {
        counterResolution <<= oversamplingFactor;
        counterResolution |= (uint32)(`$INSTANCE_NAME`_RESOLUTION_8_BITS);
    }
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */

    /* Set Sensor Settings */
#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    immunitySensorIndex = GetImmunitySensorIndex_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_immunityIndex, sensor);
#else
    immunitySensorIndex = sensor;
#endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

    #if (0u != CY_PSOC4SF)
        `$INSTANCE_NAME`_SenseClk_Stop();
        `$INSTANCE_NAME`_SampleClk_Stop();
    #endif /* (0u != CY_PSOC4SF) */

#if ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
      (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) )
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
        `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_sampleClkDividerVal);
    #else
        `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_sampleClkDividerVal[sensor]);
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */
    `$INSTANCE_NAME`_SenseClk_SetDividerValue(`$INSTANCE_NAME`_senseClkDividerVal[sensor]);
#else
    `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_sampleClkDividerVal);
    `$INSTANCE_NAME`_SenseClk_SetDividerValue(`$INSTANCE_NAME`_senseClkDividerVal);
#endif /* ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
            (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) )
       */

    #if (0u != CY_PSOC4SF)
        `$INSTANCE_NAME`_SampleClk_Start();
    #endif /* (0u != CY_PSOC4SF) */

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
            #if (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
                if(`$INSTANCE_NAME`_widgetResolution[widget] > `$INSTANCE_NAME`_senseClkDividerVal[sensor] * `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_12_BITS)
            #else
                if(`$INSTANCE_NAME`_widgetResolution[widget] > `$INSTANCE_NAME`_senseClkDividerVal * `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_12_BITS)
            #endif /* ( `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */
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
    newRegValue |= `$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex];
#else
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK | `$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK);
    newRegValue |= (`$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex] |
                            (uint32)((uint32)`$INSTANCE_NAME`_compensationIDAC[immunitySensorIndex] <<
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

#if(0u != `$INSTANCE_NAME`_BIST_API_GENERATE)
    if(0u == `$INSTANCE_NAME`_isDiagnosticEnabled)
    {
#endif /* (0u != `$INSTANCE_NAME`_BIST_API_GENERATE) */

        /* Disconnect Vref Buffer from AMUX */
        newRegValue = `$INSTANCE_NAME`_CSD_CFG_REG;
        newRegValue &= ~(`$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK);
        newRegValue |= `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG;

        if(0u != `$INSTANCE_NAME`_isShieldEnabled)
        {
            newRegValue |= `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN;
        }

#if(0u != `$INSTANCE_NAME`_BIST_API_GENERATE)
    }
    else
    {
        newRegValue = `$INSTANCE_NAME`_diagnosticCsdConfig;
    }
#endif /* (0u != `$INSTANCE_NAME`_BIST_API_GENERATE) */

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Enable Sensor */
    `$INSTANCE_NAME`_EnableScanSlot(sensor);

    interruptState = CyEnterCriticalSection();

    #if (0u != CY_PSOC4SF)
        `$INSTANCE_NAME`_SenseClk_StartEx(`$INSTANCE_NAME`_SampleClk__DIV_ID);
    #endif /* (0u != CY_PSOC4SF) */

    `$INSTANCE_NAME`_CSD_CFG_REG = newRegValue;

    /* `#START `$INSTANCE_NAME`_PreSettlingDelay_Debug` */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK
    `$INSTANCE_NAME`_PreScan_PreSettlingDelay_Debug_Callback();
#endif /* `$INSTANCE_NAME`_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK */


    CyDelayCycles(`$INSTANCE_NAME`_delayCyclesNum);

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
*  sets the scan sensor in the non? sampling state, turns off the Idac(Current Source IDAC),
*  disconnects the IDAC(Sink mode) and applies Vref on AMUX.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store sensors raw data.
*  baSpeed[] - contains oversampling value for each sensor.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PostScan(uint32 sensor)
{
    uint8 immunitySensorIndex;
    uint32 newRegValue;
#if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
    uint32 oversamplingFactor;
    uint32 widget;
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */

    /* `#START `$INSTANCE_NAME`_PostScan_Debug` */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_POST_SCAN_DEBUG_CALLBACK
    `$INSTANCE_NAME`_PostScan_Debug_Callback();
#endif /* `$INSTANCE_NAME`_POST_SCAN_DEBUG_Callback */


#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    #if(0u != CY_PSOC4SF)
        CY_SYS_CLK_IMO_TRIM1_REG = `$INSTANCE_NAME`_config.immunity0;
    #else
        CySysClkWriteImoFreq(`$INSTANCE_NAME`_config.immunity0);
    #endif /* (0u != CY_PSOC4SF) */
#endif /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    immunitySensorIndex = GetImmunitySensorIndex_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_immunityIndex, sensor);
#else
    immunitySensorIndex = sensor;
#endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

    /* Read SlotResult from Raw Counter */
    `$INSTANCE_NAME`_sensorRaw[immunitySensorIndex]  = (uint16)`$INSTANCE_NAME`_CSD_CNT_REG;

#if ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN))
    widget = `$INSTANCE_NAME`_widgetNumber[sensor];
    if(`$INSTANCE_NAME`_widgetResolution[widget] < `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_16_BITS)
    {
        oversamplingFactor = `$INSTANCE_NAME`_GetBitValue(baSpeed, sensor);
        `$INSTANCE_NAME`_sensorRaw[immunitySensorIndex] >>= oversamplingFactor;
    }
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) && (0 != `$INSTANCE_NAME`_IS_OVERSAMPLING_EN)) */


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
*  CapSense sensor functionality will be disabled by this API on the pin enabled
*  as a shield electrode.
*
* Parameters:
*  portNumber: contains the shield electrode port number (0, 1, 2).
*  pinNumber: contains the shield electrode pin number (0, 1, 2, ... , 7).
*
* Return Value:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumber[] - stores widget numbers.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableShieldElectrode(uint32 pinNumber, uint32 portNumber)
{
    #if(defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT))
        uint32 sensor;
        uint32 widget;
    #endif /* (defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)) */

    #if(defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT))
        #if(0u != `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)
            sensor = `$INSTANCE_NAME`_GetSensorNumber(pinNumber, portNumber);

            if(`$INSTANCE_NAME`_NOT_SENSOR != sensor)
            {
                widget = `$INSTANCE_NAME`_widgetNumber[sensor];
                `$INSTANCE_NAME`_DisableWidget(widget);
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT) */
    #endif /* (defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)) */

    `$INSTANCE_NAME`_SetShieldState(pinNumber, portNumber);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableShieldElectrode
********************************************************************************
*
* Summary:
*  This API disables the shield electrode on a specified port and pin.
*
* Parameters:
*  portNumber: contains the shield electrode port number (0, 1, 2).
*  pinNumber: contains the shield electrode pin number (0, 1, 2, ... , 7).
*
* Return Value:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_prtCfgTbl[] - contains pointers to the port config registers for each port.
*  `$INSTANCE_NAME`_prtSelTbl[] - contains pointers to the HSIOM registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableShieldElectrode(uint32 pinNumber, uint32 portNumber)
{
    #if(defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT))
        uint32 sensor;
        uint32 widget;
    #endif /* (defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)) */

    *`$INSTANCE_NAME`_prtCfgTbl[portNumber] &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << (pinNumber * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE));
    *`$INSTANCE_NAME`_prtSelTbl[portNumber] &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << (pinNumber * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE));

    #if(defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT))
        #if(0u != `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)
            sensor = `$INSTANCE_NAME`_GetSensorNumber(pinNumber, portNumber);

            `$INSTANCE_NAME`_isShieldEnabled &= (uint32)(~(1u << ((portNumber * `$INSTANCE_NAME`_MAX_PORT_NUMBER) + pinNumber)));

            if(`$INSTANCE_NAME`_NOT_SENSOR != sensor)
            {
                widget = `$INSTANCE_NAME`_widgetNumber[sensor];
                `$INSTANCE_NAME`_EnableWidget(widget);
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT) */
    #endif /* (defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetShieldState
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
*  `$INSTANCE_NAME`_prtCfgTbl[] - contains pointers to the port config registers for each port.
*  `$INSTANCE_NAME`_prtSelTbl[] - contains pointers to the HSIOM registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetShieldState(uint32 pinNumber, uint32 portNumber)
{
    uint32 newRegValue;

    *`$INSTANCE_NAME`_prtCfgTbl[portNumber] &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << (pinNumber * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE));
    newRegValue = *`$INSTANCE_NAME`_prtSelTbl[portNumber];
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << (pinNumber * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE));
    newRegValue |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << (pinNumber * `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE));
    *`$INSTANCE_NAME`_prtSelTbl[portNumber] = newRegValue;

    `$INSTANCE_NAME`_isShieldEnabled |= (1u << ((portNumber * `$INSTANCE_NAME`_MAX_PORT_NUMBER) + pinNumber));
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
*  This API returns a scanning sensor number when the sensor scan is in progress.
*  When the sensor scan is completed, the API returns
*  $INSTANCE_NAME`_NOT_SENSOR (0xFFFFFFFF) (when no sensor is scanned).
*
* Parameters:
*   None.
*
* Return:
*  Returns Sensor number if the sensor is being scanned and
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


#if(defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetSensorNumber
    ********************************************************************************
    *
    * Summary:
    *  This API calculates the Sensor Index for a given Pin and Port.
    *
    * Parameters:
    *  portNumber: contains port number (0, 1, 2).
    *  pinNumber: contains pin number (0, 1, 2, ... , 7).
    *
    * Return:
    *  Sensor Index
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_portTable[] - used to store the port number that pin
    *  belongs to for each sensor.
    *  `$INSTANCE_NAME`_pinShiftTbl[] - used to store a position of the pin that is
    *  configured as a sensor in the port.
    *
    * Side Effects:
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetSensorNumber(uint32 pinNumber, uint32 portNumber)
    {
        uint32 pinTblSize;
        uint32 currentSensor;

        uint32 retVal;
        retVal = `$INSTANCE_NAME`_NOT_SENSOR;

        pinTblSize = sizeof(`$INSTANCE_NAME`_pinShiftTbl);

        currentSensor = 0u;

        while((currentSensor < pinTblSize) && (pinNumber != `$INSTANCE_NAME`_pinShiftTbl[currentSensor]))
        {
            currentSensor++;
        }

        if(currentSensor < pinTblSize)
        {
            if(portNumber == `$INSTANCE_NAME`_portTable[currentSensor])
            {
                retVal = currentSensor;
            }
        }

        return(retVal);
    }
#endif /* (defined(`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)) */


#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckEmcSensorEnable
********************************************************************************
*
* Summary:
*  This API checks if Immunity is enabled for the sensor
*
* Parameters:
*   sensor: Sensor number.
*   immunityIndex: Immunity Index
*
* Return:
*  Returns 1 if Immunity is enabled for the sensor, 0 otherwise.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckEmcSensorEnable(uint32 immunityIndex, uint32 sensor)
{
    uint32 immunitySensorIndexEnable;
    uint32 retVal;

    retVal = 1u;
    immunitySensorIndexEnable = GetImmunitySensorIndex_SF_v1_0(&`$INSTANCE_NAME`_config, immunityIndex, sensor);

    if(immunitySensorIndexEnable == sensor)
    {
        retVal = 0u;
    }

    return(retVal);
}
#endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOneScanComplete
********************************************************************************
*
* Summary:
*  This API sets Scan Complete Flag or initializes the next scanning
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csdStatusVar - used to provide the status and mode of the scanning process.
*  `$INSTANCE_NAME`_sensorIndex - used to store a sensor scanning sensor number.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOneScanComplete(void)
{
    if ((`$INSTANCE_NAME`_csdStatusVar & `$INSTANCE_NAME`_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        `$INSTANCE_NAME`_csdStatusVar &= (uint8)~`$INSTANCE_NAME`_SW_STS_BUSY;
    }
    else
    {
        /* Proceed scanning */
        `$INSTANCE_NAME`_sensorIndex = (uint8)`$INSTANCE_NAME`_FindNextSensor(`$INSTANCE_NAME`_sensorIndex);

        /* Check end of scan */
        if(`$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
        {
            `$INSTANCE_NAME`_PreScan(`$INSTANCE_NAME`_sensorIndex);
        }
        else
        {
            `$INSTANCE_NAME`_csdStatusVar &= (uint8)~`$INSTANCE_NAME`_SW_STS_BUSY;
        }
    }

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableBaselineIDAC
********************************************************************************
*
* Summary:
* The  API disables the compensation IDAC.
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
*  `$INSTANCE_NAME`_modulationIDAC[] - used to store an 8-bit idac value for all the sensors.
*  `$INSTANCE_NAME`_compensationIDAC[] - used to store a 7-bit idac value for all the sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void  `$INSTANCE_NAME`_EnableBaselineIDAC(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config)
{
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
        uint32 curSensor;
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)*/
    #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        uint32 immunitySensorIndex;
        uint32 channel;

        #if((CapSense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
            uint32 widget;
            uint32 immunityCounts;
        #endif  /* ((CapSense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */

    #endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */
    uint32 newRegValue;

    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    for(curSensor = 0u; curSensor < config->totalScanslotsNum; curSensor++)
    {
        #if (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
            #if((CapSense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
                /*  Get widget Number */
                widget = `$INSTANCE_NAME`_widgetNumber[curSensor];

                /*  Check if we have slider and set immunityCounts for IDAC*/
                if((widget >`$INSTANCE_NAME`_END_OF_SLIDERS_INDEX) && (widget < `$INSTANCE_NAME`_TOTAL_WIDGET_COUNT))
                {
                    /* For Immunity = High calibrate the sensors and proximity only. */
                    immunityCounts = `$INSTANCE_NAME`_highImmunityEnable;
                }
                else
                {
                    /* The Immunity = High is not supported for sliders and dynamic buttons that are appeared from sliders. */
                    immunityCounts = `$INSTANCE_NAME`_IMMUNITY_LOW;
                }

                /*  Divide IDACs to 2 */
                for(channel = 0u; channel < immunityCounts; channel++)
            #else
                for(channel = 0u; channel < `$INSTANCE_NAME`_highImmunityEnable; channel++)
            #endif /* ((CapSense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (CapSense_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
                {
                    immunitySensorIndex = `$INSTANCE_NAME`_GetImmunityIndex(curSensor, channel);
                    `$INSTANCE_NAME`_compensationIDAC[immunitySensorIndex] = `$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex] / 2u;
                    `$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex] = (`$INSTANCE_NAME`_modulationIDAC[immunitySensorIndex] + 1u) / 2u;
                }
        #else
            `$INSTANCE_NAME`_compensationIDAC[curSensor] = `$INSTANCE_NAME`_modulationIDAC[curSensor] / 2u;
            `$INSTANCE_NAME`_modulationIDAC[curSensor] = (`$INSTANCE_NAME`_modulationIDAC[curSensor] + 1u) / 2u;
        #endif /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)*/
    }
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)*/

    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    newRegValue = `$INSTANCE_NAME`_CSD_IDAC_REG;
    newRegValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK | `$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK);
    newRegValue |= (`$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED | `$INSTANCE_NAME`_CSD_IDAC2_MODE_VARIABLE);
    `$INSTANCE_NAME`_CSD_IDAC_REG = newRegValue;

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetBitValue
********************************************************************************
*
* Summary:
*  The API returns the  bit status of the bit in the table array which contains the masks.
*
* Parameters:
*  table[] - array with the bit masks.
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
uint32 `$INSTANCE_NAME`_GetBitValue(uint8 table[], uint32 position)
{
    uint32 offset;
    uint8 enMask;

    /* The position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of
       table[] array.
    */
    enMask = 0x01u << (position & 0x07u);

    return ((table[offset] & enMask) ? 1u : 0u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBitValue
********************************************************************************
*
* Summary:
*  The API sets a bit status of the bit in the table array which contains the masks.
*
* Parameters:
*  table[] - array with the bit masks.
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

    /* The position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for the appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of
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
* Function Name: `$INSTANCE_NAME`_GetCommonParamIndex
********************************************************************************
*
* Summary:
*  The API returns the widget which is common for dynamic sliders' parameters.
*
* Parameters:
*  widget - widget number.
*
* Return:
*  widget - widget number for dynamic slider.
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumberSld - structure with dynamic sliders' parameters.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetCommonParamIndex(uint32 widget)
{
    uint8 retVal;
    retVal = widget;

    #if(`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u)
        if(widget > (`$INSTANCE_NAME`_END_OF_WIDGETS_INDEX - 1u))
        {
            retVal = `$INSTANCE_NAME`_widgetNumberSld[`$INSTANCE_NAME`_SLIDER_1].widgetNumber;
        }
    #endif /* (`$INSTANCE_NAME`_TOTAL_SLIDERS_COUNT >= 2u) */

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ChangeImoFreq
********************************************************************************
*
* Summary:
*  the API changes the IMO Frequency.
*
* Parameters:
*  value - IMO Frequency.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_highImmunityEnable - used to notify whether the frequency
*  hopping is enabled.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ChangeImoFreq(uint32 value)
{
#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    if(`$INSTANCE_NAME`_highImmunityEnable == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    {
        #if(0u != CY_PSOC4SF)
            CY_SYS_CLK_IMO_TRIM1_REG = (uint8)(value);
        #else
            CySysClkWriteImoFreq(value);
        #endif /* (0u != CY_PSOC4SF) */
    }
#endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */
}


/* [] END OF FILE */
