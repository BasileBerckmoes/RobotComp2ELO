/***************************************************************************//**
* \file     `$INSTANCE_NAME`.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the PGA_P4 Component
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"


uint8 `$INSTANCE_NAME`_initVar = 0u; /**< Describes the init state of the component */

uint32 `$INSTANCE_NAME`_internalGainPower = 0u; /**< Stores component Gain, Power and Enable values */

/***************************************************************************//**
* Compensation table 
*
* There is a feedback compensation capacitor recomended setting (for certain 
* gain and power setting) under the mask 0x0F000000u
* or (`$INSTANCE_NAME`_C_FB_MASK)
*
* Also there is an OpAmp compensation recomended setting (for certain 
* gain and power setting) under the mask 0x00000003u
* or (`$INSTANCE_NAME`_GET_OA_COMP_TRIM)
*
* There is only 6 values for whole gain range because the recommended 
* values are for each pair of adjacent gain values, e.g.:
* the first (index = 0) value is for gain = 1 and 1.4,
* the second (index = 1) value is for gain = 2 and 2.8,and so on,
* and the sixth (index = 5) value is for gain = 32 only.
*******************************************************************************/
const uint32 `$INSTANCE_NAME`_compTab[`$INSTANCE_NAME`_COMP_TAB_HEIGHT][`$INSTANCE_NAME`_COMP_TAB_WIDTH] =
{
#if (`$INSTANCE_NAME`_CHECK_OUTPUT_MODE) /* Class AB */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x07000002u, 0x09000002u, 0x09000002u},
    {0x04000002u, 0x04000002u, 0x04000002u},
    {0x03000001u, 0x02000002u, 0x03000002u},
    {0x01000001u, 0x00000002u, 0x00000002u},
    {0x01000001u, 0x01000001u, 0x02000001u}
#else /* Class A */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x08000002u, 0x09000002u, 0x09000002u},
    {0x03000001u, 0x05000002u, 0x04000002u},
    {0x00000001u, 0x02000002u, 0x03000002u},
    {0x00000001u, 0x00000002u, 0x01000002u},
    {0x00000001u, 0x00000001u, 0x00000001u}
#endif /* `$INSTANCE_NAME`_OUTPUT_MODE */
};


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
*  Initializes component's parameters to the values set by user in the 
*  customizer of the component placed onto schematic. Usually it is called in 
*  `$INSTANCE_NAME`_Start().
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    /* Set default internal variable value */
    `$INSTANCE_NAME`_internalGainPower = `$INSTANCE_NAME`_DEFAULT_GAIN_POWER;
    
    /* Set default register values */
    `$INSTANCE_NAME`_CTB_CTRL_REG |= `$INSTANCE_NAME`_DEFAULT_CTB_CTRL;
    `$INSTANCE_NAME`_OA_RES_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL_MASK;
    `$INSTANCE_NAME`_OA_RES_CTRL_REG |= `$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL;
    
    #if (`$INSTANCE_NAME`_VREF_MODE == `$INSTANCE_NAME`_VREF_INTERNAL)
        /* Configure resistor matrix bottom to the internal Vss */
        `$INSTANCE_NAME`_OA_SW_REG |= `$INSTANCE_NAME`_RBOT_TO_VSSA;
    #endif /* Vref Internal */
    
    /* Check if component has been enabled */
    if((`$INSTANCE_NAME`_OA_RES_CTRL_REG & `$INSTANCE_NAME`_OA_PWR_MODE_MASK) != 0u)
    {
        /* Set the default power level */
        `$INSTANCE_NAME`_Enable();
    }
    
    /* Set default gain and correspondent Cfb and OA_trim values */
    `$INSTANCE_NAME`_SetGain(`$INSTANCE_NAME`_GAIN);
}


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
*  Powers up amplifier (to default power level or restored after 
*  previous `$INSTANCE_NAME`_Stop() call).
*  Usually it is called in `$INSTANCE_NAME`_Start().
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_OA_RES_CTRL_REG |= `$INSTANCE_NAME`_GET_POWER;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  Enables the amplifier operation (calls `$INSTANCE_NAME`_Enable).
*  Also on the first call (after the system reset) initializes all the component
*  related registers with default values (calls `$INSTANCE_NAME`_Init).
*
*  \globalvars
*   The `$INSTANCE_NAME`_initVar variable is used to indicate initial
*   configuration of this component. The variable is initialized to zero (0u)
*   and set to one (1u) at the first time `$INSTANCE_NAME`_Start() is called.
*   This allows to enable the component without re-initialization in all
*   subsequent calls of the `$INSTANCE_NAME`_Start() routine.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(`$INSTANCE_NAME`_initVar == 0u)
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
*  Powers down the amplifier.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{ 
    `$INSTANCE_NAME`_OA_RES_CTRL_REG &= (uint32)~`$INSTANCE_NAME`_OA_PWR_MODE_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
****************************************************************************//**
*
*  Sets the power level of amplifier.
*
* \param powerLevel
*  The power level setting of amplifier. Possible values:
*   * `$INSTANCE_NAME`_LOW - The lowest power consumption.
*   * `$INSTANCE_NAME`_MED - The middle setting.
*   * `$INSTANCE_NAME`_HIGH - The highest amplifier bandwidth.
*
*  \internal
*   The `$INSTANCE_NAME`_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPower(uint32 powerLevel)
{
    uint32 locTmp;
    
    /* Save the powerLevel */
    `$INSTANCE_NAME`_internalGainPower &= (uint32) ~`$INSTANCE_NAME`_OA_PWR_MODE_MASK;
    `$INSTANCE_NAME`_internalGainPower |= powerLevel & `$INSTANCE_NAME`_OA_PWR_MODE_MASK;
    
    /* Save the rest of register bitfields */
    locTmp = `$INSTANCE_NAME`_OA_RES_CTRL_REG &
        (uint32)~(`$INSTANCE_NAME`_OA_PWR_MODE_MASK | `$INSTANCE_NAME`_C_FB_MASK);
           
    /* Set the power and the feedback capacitor values into the control register */
    `$INSTANCE_NAME`_OA_RES_CTRL_REG  = locTmp | `$INSTANCE_NAME`_GET_POWER | `$INSTANCE_NAME`_GET_C_FB;
    
    /* Set the OA compensation capacitor value */
    `$INSTANCE_NAME`_OA_COMP_TRIM_REG = `$INSTANCE_NAME`_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
****************************************************************************//**
*
*  Sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* \param gainLevel
*  The gain setting of amplifier. Possible values:
*   * `$INSTANCE_NAME`_GAIN_1    - gain 1.0.
*   * `$INSTANCE_NAME`_GAIN_1_4  - gain 1.4.
*   * `$INSTANCE_NAME`_GAIN_2    - gain 2.0.
*   * `$INSTANCE_NAME`_GAIN_2_8  - gain 2.8.
*   * `$INSTANCE_NAME`_GAIN_4    - gain 4.0.
*   * `$INSTANCE_NAME`_GAIN_5_8  - gain 5.8.
*   * `$INSTANCE_NAME`_GAIN_8    - gain 8.0.
*   * `$INSTANCE_NAME`_GAIN_10_7 - gain 10.7.
*   * `$INSTANCE_NAME`_GAIN_16   - gain 16.0
*   * `$INSTANCE_NAME`_GAIN_21_3 - gain 21.3.
*   * `$INSTANCE_NAME`_GAIN_32   - gain 32.0.
*
*  \internal
*   The `$INSTANCE_NAME`_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetGain(uint32 gainLevel)
{
    uint32 locTmp;
    
    /* Save the gainLevel */
    `$INSTANCE_NAME`_internalGainPower &= (uint32) ~`$INSTANCE_NAME`_RES_TAP_MASK;
    `$INSTANCE_NAME`_internalGainPower |= ((uint32)(gainLevel << `$INSTANCE_NAME`_RES_TAP_SHIFT)) &
                                                                 `$INSTANCE_NAME`_RES_TAP_MASK;
    /* Save the rest of register bitfields */
    locTmp = `$INSTANCE_NAME`_OA_RES_CTRL_REG &
        (uint32)~(`$INSTANCE_NAME`_RES_TAP_MASK | `$INSTANCE_NAME`_C_FB_MASK);
    
    /* Set the gain and the feedback capacitor values into the control register */
    `$INSTANCE_NAME`_OA_RES_CTRL_REG = locTmp | (`$INSTANCE_NAME`_internalGainPower &
        `$INSTANCE_NAME`_RES_TAP_MASK) | `$INSTANCE_NAME`_GET_C_FB;
    
    /* Set the OA compensation capacitor value */
    `$INSTANCE_NAME`_OA_COMP_TRIM_REG = `$INSTANCE_NAME`_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PumpControl
****************************************************************************//**
*
*  Allows the user to turn the amplifier's boost pump on or off.
*  By Default the `$INSTANCE_NAME`_Init() function turns the pump on.
*  
* \param onOff
*  The boost pump setting. Possible values:
*   * `$INSTANCE_NAME`_BOOST_OFF - Turn off the pump.
*   * `$INSTANCE_NAME`_BOOST_ON  - Turn on the pump.
*
**********************************************************************************/
void `$INSTANCE_NAME`_PumpControl(uint32 onOff)
{
    if(onOff == `$INSTANCE_NAME`_BOOST_ON)
    {
        `$INSTANCE_NAME`_OA_RES_CTRL_REG |= `$INSTANCE_NAME`_OA_PUMP_EN;
    }
    else
    {
        `$INSTANCE_NAME`_OA_RES_CTRL_REG &= (uint32)~`$INSTANCE_NAME`_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
