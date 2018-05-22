/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides all API functionality of the `$INSTANCE_NAME` component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"


/*******************************************************************************
* Variables
********************************************************************************/
uint8  `$INSTANCE_NAME`_initVar = 0u;
volatile uint16 `$INSTANCE_NAME`_lo[`$INSTANCE_NAME`_CUSTOM_NUM_SENSORS];
volatile uint16 `$INSTANCE_NAME`_hi[`$INSTANCE_NAME`_CUSTOM_NUM_SENSORS];
volatile uint8  `$INSTANCE_NAME`_busyFlag;
volatile uint8  `$INSTANCE_NAME`_contMode;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
* Starts the component. Calls the `$INSTANCE_NAME`_Init() API if the component
* has not been initialized before. Calls the enable API.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* If not already initialized, then initialize hardware and software */
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables and stops the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_busyFlag - used for reflect sensor masuring.
*
***************u****************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;

    /* Change shared regs, need to be safety */
    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG = (`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_CTRL_EOC_TRIG);
 
    `$INSTANCE_NAME`_EOC_ISR_Disable();

    `$INSTANCE_NAME`_busyFlag = 0u;

    /* shared regs config are done */
    CyExitCriticalSection(enableInterrupts);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init()
********************************************************************************
*
* Summary:
*  Initializes the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_busyFlag - used for reflect sensor masuring.
*  `$INSTANCE_NAME`_contMode - used for reflect modes of operation used:
*     - `$INSTANCE_NAME`_MODE_CONTINUOUS.
*     - `$INSTANCE_NAME`_MODE_ONESHOT.
*
********************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    `$INSTANCE_NAME`_contMode = `$INSTANCE_NAME`_CUSTOM_CONTINUOUS_MODE;
    `$INSTANCE_NAME`_busyFlag = 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable()
********************************************************************************
*
* Summary:
*  Enables the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
********************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 enableInterrupts;

    /* Change shared regs, need to be safety */
    enableInterrupts = CyEnterCriticalSection();

    /* Setup the number of Sensors from the customizer */
    `$INSTANCE_NAME`_CONTROL_REG = ((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_CTRL_EOC_TRIG) | 
                                   ((uint8)((`$INSTANCE_NAME`_CUSTOM_NUM_SENSORS - 1u)  << 
                                             `$INSTANCE_NAME`_CTRL_REG_SNS_SHIFT))  |
                                             `$INSTANCE_NAME`_CTRL_REG_ENABLE);

    /* Reset Timer FIFOs */
    CY_SET_REG16(`$INSTANCE_NAME`_FIFO_AUXCTL_PTR, (CY_GET_REG16(`$INSTANCE_NAME`_FIFO_AUXCTL_PTR) |
                                                                 `$INSTANCE_NAME`_FIFO_CLEAR_MASK));
    CY_SET_REG16(`$INSTANCE_NAME`_FIFO_AUXCTL_PTR, (CY_GET_REG16(`$INSTANCE_NAME`_FIFO_AUXCTL_PTR) &
                                                                 (uint16)~`$INSTANCE_NAME`_FIFO_CLEAR_MASK));

    /* shared regs config are done */
    CyExitCriticalSection(enableInterrupts);

    /* Enable the buried ISR component */
    `$INSTANCE_NAME`_EOC_ISR_StartEx(&`$INSTANCE_NAME`_EOC_ISR_Int);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Trigger
********************************************************************************
*
* Summary:
*  Provides a valid strobe/trigger output on the conv terminal.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_busyFlag - used for reflect sensor masuring.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Trigger(void) `=ReentrantKeil($INSTANCE_NAME . "_Trigger")`
{
    uint8 enableInterrupts;

    if( 0u == `$INSTANCE_NAME`_busyFlag)
    {
        /* Change shared regs, need to be safety */
        enableInterrupts = CyEnterCriticalSection();

        /* Generate a CONV strobe */
        `$INSTANCE_NAME`_CONTROL_REG ^= `$INSTANCE_NAME`_CTRL_TRIG;

        `$INSTANCE_NAME`_busyFlag = 1u;

        /* shared regs config are done */
        CyExitCriticalSection(enableInterrupts);
    }
    else
    {
        /* Do nothing */
    }

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTemperature
********************************************************************************
*
* Summary:
*  Calculates the temperature in degrees Celsius.
*
* Parameters:
*  uint8 SensorNum. The TMP05 sensor number from 0..3.
*
* Return:
*  int16 Temperature in 1/100ths degrees C of the requested sensor.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_GetTemperature(uint8 sensorNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTemperature")`
{
    uint16 hi_temp;
    uint16 lo_temp;
    
    `$INSTANCE_NAME`_EOC_ISR_Disable();
    hi_temp = `$INSTANCE_NAME`_hi[sensorNum];
    lo_temp = `$INSTANCE_NAME`_lo[sensorNum];
    `$INSTANCE_NAME`_EOC_ISR_Enable();
    
    /* Calculates temp for each sensor based on mathematical equation shown in TMP05 datasheet */
    return ((int16)((`$INSTANCE_NAME`_SCALED_CONST_TMP1 - 
		   ((`$INSTANCE_NAME`_SCALED_CONST_TMP2 * (int32) hi_temp) / (int32) lo_temp))));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConversionStatus
********************************************************************************
*
* Summary:
*  Enables firmware to synchronize with the hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8 status code:
*   `$INSTANCE_NAME`_STATUS_IN_PROGRESS - Conversion in progress.
*   `$INSTANCE_NAME`_STATUS_COMPLETE - Conversion complete.
*   `$INSTANCE_NAME`_STATUS_ERROR - Sensor Error.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ConversionStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ConversionStatus")`
{
    return (`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_STATUS_CLR_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMode
********************************************************************************
*
* Summary:
*  Sets the operating mode of the component.
*
* Parameters:
*  uint8 mode: operating mode:
*   `$INSTANCE_NAME`_MODE_CONTINUOUS - Continuous mode.
*   `$INSTANCE_NAME`_MODE_ONESHOT - One-shot mode.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_contMode - used for reflect modes of operation used:
*     - `$INSTANCE_NAME`_MODE_CONTINUOUS.
*     - `$INSTANCE_NAME`_MODE_ONESHOT.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetMode(uint8 mode) `=ReentrantKeil($INSTANCE_NAME . "_SetMode")`
{
   `$INSTANCE_NAME`_contMode = mode;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DiscoverSensors
********************************************************************************
*
* Summary:
*  This API is provided for applications that might have a variable number of
*  temperature sensors connected. It automatically detects how many temperature
*  sensors are daisy-chained to the component. The algorithm starts by checking
*  to see if the number of sensors actually connected matches the NumSensors
*  parameter setting in the Basic Tab of the component customizer. If not,
*  it will retry assuming 1 less sensor is connected. This process will repeat
*  until the actual number of sensors connected is known.
*  Confirming whether or not a sensor is attached or not takes a few hundred
*  milliseconds per sensor per iteration of the algorithm. To limit the
*  sensing time, reduce the NumSensors parameter setting in the General Tab
*  of the component customizer to the maximum number of possible sensors
*  in the system.
*
* Parameters:
*  None
*
* Return:
*  uint8 representing the number of sensors actually connected (0..4).
*
* Global Variables:
*  `$INSTANCE_NAME`_contMode - used for reflect modes of operation used:
*     - `$INSTANCE_NAME`_MODE_CONTINUOUS.
*     - `$INSTANCE_NAME`_MODE_ONESHOT.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DiscoverSensors(void) `=ReentrantKeil($INSTANCE_NAME . "_DiscoverSensors")`
{
    uint8 sensorCount = `$INSTANCE_NAME`_CUSTOM_NUM_SENSORS;
    uint8 enableInterrupts;
    uint8 eocRegStatus;
    uint8 contFlag;

    if (0u != (`$INSTANCE_NAME`_MODE_CONTINUOUS & `$INSTANCE_NAME`_contMode))
    {
        `$INSTANCE_NAME`_contMode = `$INSTANCE_NAME`_MODE_ONESHOT;
        contFlag = 1u;
    }
    else
    {
        contFlag = 0u;
    }

    /* Change shared regs, need to be safety */
    enableInterrupts = CyEnterCriticalSection();

    /* Setup the number of Sensors from the customizer */
    `$INSTANCE_NAME`_CONTROL_REG = ((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_CTRL_NUM_SNS_MASK) | 
                                   (uint8)((`$INSTANCE_NAME`_CUSTOM_NUM_SENSORS - 1u) << 
                                            `$INSTANCE_NAME`_CTRL_REG_SNS_SHIFT));
                                     
    /* shared regs config are done */
    CyExitCriticalSection(enableInterrupts);

    /* Start conversion */
    `$INSTANCE_NAME`_Trigger();

    /* Wait for conversion complete or error */
    do
    {
        eocRegStatus = `$INSTANCE_NAME`_ConversionStatus();
    }
    while (eocRegStatus == `$INSTANCE_NAME`_STATUS_IN_PROGRESS);

    /* Error returned, re-try with 1 less sensor */
    if (0u != (eocRegStatus & `$INSTANCE_NAME`_STATUS_ERR))
    {
        do
        {
            sensorCount--;

            if (0u == sensorCount)
            {
                eocRegStatus = 0u;
            }
            else
            {
                /* Change shared regs, need to be safety */
                enableInterrupts = CyEnterCriticalSection();

                `$INSTANCE_NAME`_CONTROL_REG = ((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_CTRL_NUM_SNS_MASK) | 
                                               (uint8)((sensorCount - 1u) << `$INSTANCE_NAME`_CTRL_REG_SNS_SHIFT));

                /* shared regs config are done */
                CyExitCriticalSection(enableInterrupts);

                 /* Start conversion */
                `$INSTANCE_NAME`_Trigger();

                /* Wait for conversion complete or error */
                do
                {
                    eocRegStatus = `$INSTANCE_NAME`_ConversionStatus();
                }
                while (eocRegStatus == `$INSTANCE_NAME`_STATUS_IN_PROGRESS);
            }
        }
        while (0u != (eocRegStatus & `$INSTANCE_NAME`_STATUS_ERR));
    }

    if (0u != contFlag)
    {
        `$INSTANCE_NAME`_contMode = `$INSTANCE_NAME`_MODE_CONTINUOUS;
    }

    return (sensorCount);
}


/* [] END OF FILE */
