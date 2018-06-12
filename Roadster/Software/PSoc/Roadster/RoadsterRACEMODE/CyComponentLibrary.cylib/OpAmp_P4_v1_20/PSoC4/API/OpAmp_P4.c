/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Opamp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u; /* Defines if component was initialized */
static uint32 `$INSTANCE_NAME`_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
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
    `$INSTANCE_NAME`_internalPower = `$INSTANCE_NAME`_POWER;
    `$INSTANCE_NAME`_CTB_CTRL_REG = `$INSTANCE_NAME`_DEFAULT_CTB_CTRL;
    `$INSTANCE_NAME`_OA_RES_CTRL_REG = `$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL;
    `$INSTANCE_NAME`_OA_COMP_TRIM_REG = `$INSTANCE_NAME`_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
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
    `$INSTANCE_NAME`_OA_RES_CTRL_REG |= `$INSTANCE_NAME`_internalPower | \
                                        `$INSTANCE_NAME`_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables power 
*  to the block. The first time the routine is executed, the Power level, Mode, 
*  and Output mode are set. When called to restart the Opamp following a Stop() call, 
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if( 0u == `$INSTANCE_NAME`_initVar)
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
*  Turn off the Opamp block.
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
    `$INSTANCE_NAME`_OA_RES_CTRL_REG &= ((uint32)~(`$INSTANCE_NAME`_OA_PWR_MODE_MASK | \
                                                   `$INSTANCE_NAME`_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   `$INSTANCE_NAME`_LOW_POWER - Lowest active power
*   `$INSTANCE_NAME`_MED_POWER - Medium power
*   `$INSTANCE_NAME`_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void `$INSTANCE_NAME`_SetPower(uint32 power)
{
    uint32 tmp;
    
    `$INSTANCE_NAME`_internalPower = `$INSTANCE_NAME`_GET_OA_PWR_MODE(power);
    tmp = `$INSTANCE_NAME`_OA_RES_CTRL_REG & \
           (uint32)~`$INSTANCE_NAME`_OA_PWR_MODE_MASK;
    `$INSTANCE_NAME`_OA_RES_CTRL_REG = tmp | `$INSTANCE_NAME`_internalPower;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PumpControl
********************************************************************************
*
* Summary:
*  Allows the user to turn the Opamp's boost pump on or off. By Default the Start() 
*  function turns on the pump. Use this API to turn it off. The boost must be 
*  turned on when the supply is less than 2.7 volts and off if the supply is more 
*  than 4 volts.
*
* Parameters:
*  onOff: Control the pump.
*   `$INSTANCE_NAME`_PUMP_OFF - Turn off the pump
*   `$INSTANCE_NAME`_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void `$INSTANCE_NAME`_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        `$INSTANCE_NAME`_OA_RES_CTRL |= `$INSTANCE_NAME`_OA_PUMP_EN;    
    }
    else
    {
        `$INSTANCE_NAME`_OA_RES_CTRL &= (uint32)~`$INSTANCE_NAME`_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
