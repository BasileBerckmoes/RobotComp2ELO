/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code of APIs for the IDAC7 component.
*
*******************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint32 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
*  Initializes all initial parameters and operating modes.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint8 interruptState;

    /* Set IDAC default values */
    interruptState = CyEnterCriticalSection();

    `$INSTANCE_NAME`_IDAC_CONTROL_REG &= (~`$INSTANCE_NAME`_POLY_DYN  &
                                          ~`$INSTANCE_NAME`_LEG1_MODE_MASK &
                                          ~`$INSTANCE_NAME`_LEG2_MODE_MASK &
                                          ~`$INSTANCE_NAME`_DSI_CTRL_EN);

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
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    /* Enable CSD */
    `$INSTANCE_NAME`_CSD_CONTROL_REG |= (`$INSTANCE_NAME`_CSD_CONFIG_ENABLE | `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN);

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
*  \param uint32 current: The current value
*  * Valid range    : [0 - 127]
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetValue(uint32 current)
{
    uint8 interruptState;
    uint32 newRegisterValue;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = `$INSTANCE_NAME`_IDAC_CONTROL_REG & ~`$INSTANCE_NAME`_CURRENT_VALUE_MASK;

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
*  \param uint32 polarity: Current polarity
*  * `$INSTANCE_NAME`_POL_SOURCE   : Source polarity
*  * `$INSTANCE_NAME`_POL_SINK     : Sink polarity
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPolarity(uint32 polarity)
{
    uint8 interruptState;
    uint32 newRegisterValue;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = `$INSTANCE_NAME`_IDAC_CONTROL_REG & ~`$INSTANCE_NAME`_POLARITY_MASK;

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
*  \param uint32 range: Current range
*  * `$INSTANCE_NAME`_RNG_4_76UA   : 37.5 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_9_52UA   : 75 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_38_1UA   : 300 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_76_2UA   : 600 nA/bit current range
*  * `$INSTANCE_NAME`_RNG_304_8UA  : 2.4 uA/bit current range
*  * `$INSTANCE_NAME`_RNG_609_6UA  : 4.8 uA/bit current range
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetRange(uint32 range)
{
    uint8 interruptState;
    uint32 newRegisterValue;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = `$INSTANCE_NAME`_IDAC_CONTROL_REG & (~`$INSTANCE_NAME`_RANGE_MASK    &
                                                            ~`$INSTANCE_NAME`_LEG1_EN       &
                                                            ~`$INSTANCE_NAME`_LEG2_EN);

    newRegisterValue |= (range << `$INSTANCE_NAME`_RANGE_POS);

    `$INSTANCE_NAME`_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/* [] END OF FILE */
