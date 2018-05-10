/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code of APIs for the IDAC7 component.
*
*******************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint32_t `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
*  Initializes all initial parameters and operating modes.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32_t interruptState;
    uint32_t newRegisterValue;

    /* Set IDAC default values */
    interruptState = CyEnterCriticalSection();

    newRegisterValue = (uint32_t)`$INSTANCE_NAME`_IDAC_CONTROL_REG;
    newRegisterValue &= (uint32_t)(~`$INSTANCE_NAME`_POLY_DYN  &
                                 ~`$INSTANCE_NAME`_LEG1_MODE_MASK &
                                 ~`$INSTANCE_NAME`_LEG2_MODE_MASK &
                                 ~`$INSTANCE_NAME`_DSI_CTRL_EN);
    `$INSTANCE_NAME`_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(interruptState);

    /* Set initial configuration */
    `$INSTANCE_NAME`_SetValue(`$INSTANCE_NAME`_CURRENT_VALUE);
    `$INSTANCE_NAME`_SetPolarity(`$INSTANCE_NAME`_CURRENT_POLARITY);
    `$INSTANCE_NAME`_SetRange(`$INSTANCE_NAME`_CURRENT_RANGE);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
*  Enables the IDAC for operation.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint32_t interruptState;
    uint32_t newRegisterValue;
	
    interruptState = CyEnterCriticalSection();

    /* Enable CSD */
	newRegisterValue = (uint32_t)`$INSTANCE_NAME`_CSD_CONTROL_REG;
    newRegisterValue |= (`$INSTANCE_NAME`_CSD_CONFIG_ENABLE | `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN);
    `$INSTANCE_NAME`_CSD_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  Initializes all the parameters required to setup the component as defined
*  in the customizer.
*
*  This component does not stop the CSD IP block. One possible way to turn off 
*  the entire CSD block is to use a specific define (`$INSTANCE_NAME`_CSD_CONFIG_ENABLE) 
*  for the m0s8csdv2 IP block control register (`$INSTANCE_NAME`_CSD_CONTROL_REG): 
*  `$INSTANCE_NAME`_CSD_CONTROL_REG &= ~`$INSTANCE_NAME`_CSD_CONFIG_ENABLE
*
* \globalvars
*  \ref `$INSTANCE_NAME`_initVar - this variable is used to indicate the initial
*  configuration of this component. The variable is initialized to zero and
*  set to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows
*  the component initialization without re-initialization in all subsequent
*  calls to the `$INSTANCE_NAME`_Start() routine.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
*  The Stop is not required.
*
*  This component does not stop the CSD IP block. One possible way to turn off 
*  the entire CSD block is to use a specific define (`$INSTANCE_NAME`_CSD_CONFIG_ENABLE) 
*  for the m0s8csdv2 IP block control register (`$INSTANCE_NAME`_CSD_CONTROL_REG): 
*  `$INSTANCE_NAME`_CSD_CONTROL_REG &= ~`$INSTANCE_NAME`_CSD_CONFIG_ENABLE
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    /* Do nothing */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetValue
****************************************************************************//**
*
*  Sets the IDAC current to the new value.
*
*  \param uint32_t current: The current value
*  * Valid range    : [0 - 127]
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetValue(uint32_t current)
{
    uint32_t interruptState;
    uint32_t newRegisterValue;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = (uint32_t)`$INSTANCE_NAME`_IDAC_CONTROL_REG & ~`$INSTANCE_NAME`_CURRENT_VALUE_MASK;

    newRegisterValue |= ((current << `$INSTANCE_NAME`_CURRENT_VALUE_POS) & `$INSTANCE_NAME`_CURRENT_VALUE_MASK);

    `$INSTANCE_NAME`_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPolarity
****************************************************************************//**
*
*  Sets polarity to either sink or source.
*
*  \param uint32_t polarity: Current polarity
*  * `$INSTANCE_NAME`_POL_SOURCE   : Source polarity
*  * `$INSTANCE_NAME`_POL_SINK     : Sink polarity
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPolarity(uint32_t polarity)
{
    uint32_t interruptState;
    uint32_t newRegisterValue;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = (uint32_t)`$INSTANCE_NAME`_IDAC_CONTROL_REG & ~`$INSTANCE_NAME`_POLARITY_MASK;

    newRegisterValue |= ((polarity << `$INSTANCE_NAME`_POLARITY_POS) & `$INSTANCE_NAME`_POLARITY_MASK);

    `$INSTANCE_NAME`_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetRange
****************************************************************************//**
*
* Sets the IDAC range to one of the six ranges.
*
*  \param uint32_t range: Current range
*  * `$INSTANCE_NAME`_RNG_4_96UA   : 39.06 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_9_922UA   : 78.125 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_39_69UA   : 312.5 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_79_38UA   : 625 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_317_5UA  : 2.5 uA/bit current range
*  * `$INSTANCE_NAME`_RNG_635_0UA  : 5.0 uA/bit current range
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetRange(uint32_t range)
{
    uint32_t interruptState;
    uint32_t newRegisterValue;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = (uint32_t)`$INSTANCE_NAME`_IDAC_CONTROL_REG & (~`$INSTANCE_NAME`_RANGE_MASK    &
                                                            ~`$INSTANCE_NAME`_LEG1_EN       &
                                                            ~`$INSTANCE_NAME`_LEG2_EN);

    newRegisterValue |= (range << `$INSTANCE_NAME`_RANGE_POS);

    `$INSTANCE_NAME`_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/* [] END OF FILE */
