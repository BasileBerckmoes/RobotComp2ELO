/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the CSD Comparator
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u; /* Defines if component was initialized */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables 
*  power to the block. The first time the routine is executed and the power level
*  are set. When called to restart the comparator following a Stop() call,
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
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
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_SAMPLECLK_DIVIDER);
        
    `$INSTANCE_NAME`_CONFIG_REG = `$INSTANCE_NAME`_DEFAULT_CONFIG;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Turn off the Comparator block. CSD block still enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    uint8 interruptState;
    
    `$INSTANCE_NAME`_SampleClk_Stop();
    
    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint8 interruptState;
    
    `$INSTANCE_NAME`_SampleClk_Start();
    
    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
********************************************************************************
*
* Summary:
*  Sets the power and speed to one of two settings.
*
* Parameters:
*  speed: enumerated speed mode value.
*   `$INSTANCE_NAME`_SLOW_SPEED  - Slow speed / Low power
*   `$INSTANCE_NAME`_HIGH_SPEED  - Fast speed / High power
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint32 speed)
{
    uint8 interruptState;
    
    interruptState = CyEnterCriticalSection();
    if(0u != speed)
    {
        `$INSTANCE_NAME`_CONFIG_REG |= (uint32)  `$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW;
    }
    else
    {
        `$INSTANCE_NAME`_CONFIG_REG &= (uint32) ~`$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW;
    }
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
********************************************************************************
*
* Summary:
*  This function returns a nonzero value when the voltage connected to the 
*  positive input is greater than Vref. 
*
* Parameters:
*  None
*
* Return:
*  Comparator output state. Nonzero value when the positive input voltage is 
*  greater than Vref; otherwise, the return value is zero.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetCompare(void)
{
    return((uint32)(0u != (`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_STATUS_SAMPLE)));
}


/* [] END OF FILE */
