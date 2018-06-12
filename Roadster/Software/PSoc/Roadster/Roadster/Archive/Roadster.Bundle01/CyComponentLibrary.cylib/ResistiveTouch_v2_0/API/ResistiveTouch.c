/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the API source code for the Resistive Touch component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_xm.h"
#include "`$INSTANCE_NAME`_xp.h"
#include "`$INSTANCE_NAME`_ym.h"
#include "`$INSTANCE_NAME`_yp.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;
static uint8 `$INSTANCE_NAME`_measurementFlag = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Calls the Init() function of the ADC and AMux components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    `$INSTANCE_NAME`_AMux_Init();
    `$INSTANCE_NAME`_`$ADC`_Init();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Calls Init() if the component has not been initialized before. Calls Enable()
*  to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
* 
* Global variables:
*  `$INSTANCE_NAME`_initVar - Indicates whether the component has been
*                             initialized.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)  `=ReentrantKeil($INSTANCE_NAME . "_Start")`
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
********************************************************************************
*
* Summary:
*  Stops the ADC and AMux components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)  `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    `$INSTANCE_NAME`_`$ADC`_Stop();
    `$INSTANCE_NAME`_AMux_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the ADC component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)  `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    `$INSTANCE_NAME`_`$ADC`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ActivateX
********************************************************************************
*
* Summary: 
*  Configures the pins to measure the Y-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ActivateX(void) `=ReentrantKeil($INSTANCE_NAME . "_ActivateX")`
{
    /* Pins configuration to measure Y. */
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_ym_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_yp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_xp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_xm_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if channel 0 is not selected. */
    if(`$INSTANCE_NAME`_AMux_GetChannel() != `$INSTANCE_NAME`_AMUX_XP_CHAN)
    {
        `$INSTANCE_NAME`_AMux_Next();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ActivateY
********************************************************************************
*
* Summary: 
*  Configures the pins to measure X-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ActivateY(void) `=ReentrantKeil($INSTANCE_NAME . "_ActivateY")`
{
    /* Pins configuration to measure X. */
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_xm_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_xp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_yp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_ym_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if channel 1 is not selected. */
    if(`$INSTANCE_NAME`_AMux_GetChannel() == `$INSTANCE_NAME`_AMUX_XP_CHAN)
    {
        `$INSTANCE_NAME`_AMux_Next();
    }
    /* Switch AMux to channel 1 if AMux is disconnected. */
    else if(`$INSTANCE_NAME`_AMux_GetChannel() == `$INSTANCE_NAME`_AMUX_NO_CHAN)
    {
        `$INSTANCE_NAME`_AMux_Next();
        `$INSTANCE_NAME`_AMux_Next();
    }
    else
    {
        /* Channel 1 is already selected. */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TouchDetect
********************************************************************************
*
* Summary:
*  Determines if the screen is touched.
*
* Parameters:
*  None
*
* Return:
*  uint8: The touch state.
*  0 - untouched
*  1 - touched
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_TouchDetect(void) `=ReentrantKeil($INSTANCE_NAME . "_TouchDetect")`
{
    /* Configure x+ pin to detect touch. */
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_xp_0, PIN_DM_STRONG);

    /* Add delay for signal to stabilize. */
    CyDelayUs(5u);

    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_xp_0, PIN_DM_RES_UP);
    
    /* Switch AMux if channel 0 is not selected. */
    if(`$INSTANCE_NAME`_AMux_GetChannel() != `$INSTANCE_NAME`_AMUX_XP_CHAN)
    {
        `$INSTANCE_NAME`_AMux_Next();
    }

    /* Configure x-, y+ and y- to detect touch. */
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_xm_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_yp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(`$INSTANCE_NAME`_ym_0, PIN_DM_STRONG);

    /* Add delay for signal to stabilize. The delay is dependant on whether
    * the measurement has been done before touch detect or not.
    */
    if (`$INSTANCE_NAME`_measurementFlag == 0u)
    {
        CyDelayUs(20u);
    }
    else
    {
        `$INSTANCE_NAME`_measurementFlag = 0u;
        CyDelayUs(8u);        
    }
    /* The screen is touched if the measured value is lower than the specified
    * threshold.
    */
    return ((`$INSTANCE_NAME`_Measure() < `$INSTANCE_NAME`_TOUCH_THRESHOLD) ? 1u : 0u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Measure
********************************************************************************
*
* Summary:
*  Returns the result of the ADC conversion. Does not return until ADC
*  conversion is complete.
*
* Parameters:
*  None
*
* Return:
*  int16: the result of the ADC conversion.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_Measure(void) `=ReentrantKeil($INSTANCE_NAME . "_Measure")`
{       
    int16 result;

    /* Trigger the ADC conversion and wait for results (blocking). */
    `$INSTANCE_NAME`_`$ADC`_StartConvert();
    (void)`$INSTANCE_NAME`_`$ADC`_IsEndConversion(`$INSTANCE_NAME`_`$ADC`_WAIT_FOR_RESULT);
    result = `$INSTANCE_NAME`_`$ADC`_GetResult16();

    /* Assert a flag indicating that the measurement has been done. */
    `$INSTANCE_NAME`_measurementFlag = 1u;
    return (result);
}


/* [] END OF FILE */
