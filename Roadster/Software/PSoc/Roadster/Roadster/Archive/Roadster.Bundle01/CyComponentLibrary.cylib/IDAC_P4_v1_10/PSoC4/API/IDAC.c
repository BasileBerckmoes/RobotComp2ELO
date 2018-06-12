/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of APIs for the IDAC_P4 component.
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint32 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes IDAC registers with initial values provided from customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32 regVal;
    uint8 enableInterrupts;

    /* Set initial configuration */
    enableInterrupts = CyEnterCriticalSection();
    
    #if(`$INSTANCE_NAME`_MODE_SOURCE == `$INSTANCE_NAME`_IDAC_POLARITY)
        regVal  = `$INSTANCE_NAME`_CSD_TRIM1_REG & ~(`$INSTANCE_NAME`_CSD_IDAC_TRIM1_MASK);
        regVal |=  (`$INSTANCE_NAME`_SFLASH_TRIM1_REG & `$INSTANCE_NAME`_CSD_IDAC_TRIM1_MASK);
        `$INSTANCE_NAME`_CSD_TRIM1_REG = regVal;
    #else
        regVal  = `$INSTANCE_NAME`_CSD_TRIM2_REG & ~(`$INSTANCE_NAME`_CSD_IDAC_TRIM2_MASK);
        regVal |=  (`$INSTANCE_NAME`_SFLASH_TRIM2_REG & `$INSTANCE_NAME`_CSD_IDAC_TRIM2_MASK);
        `$INSTANCE_NAME`_CSD_TRIM2_REG = regVal;
    #endif /* (`$INSTANCE_NAME`_MODE_SOURCE == `$INSTANCE_NAME`_IDAC_POLARITY) */

    /* clear previous values */
    `$INSTANCE_NAME`_IDAC_CONTROL_REG &= ((uint32)~((uint32)`$INSTANCE_NAME`_IDAC_VALUE_MASK <<
        `$INSTANCE_NAME`_IDAC_VALUE_POSITION)) | ((uint32)~((uint32)`$INSTANCE_NAME`_IDAC_MODE_MASK <<
        `$INSTANCE_NAME`_IDAC_MODE_POSITION))  | ((uint32)~((uint32)`$INSTANCE_NAME`_IDAC_RANGE_MASK  <<
        `$INSTANCE_NAME`_IDAC_RANGE_POSITION));

    `$INSTANCE_NAME`_IDAC_POLARITY_CONTROL_REG &= (~(uint32)((uint32)`$INSTANCE_NAME`_IDAC_POLARITY_MASK <<
        `$INSTANCE_NAME`_IDAC_POLARITY_POSITION));

    /* set new configuration */
    `$INSTANCE_NAME`_IDAC_CONTROL_REG |= (((uint32)`$INSTANCE_NAME`_IDAC_INIT_VALUE <<
        `$INSTANCE_NAME`_IDAC_VALUE_POSITION) | ((uint32)`$INSTANCE_NAME`_IDAC_RANGE <<
        `$INSTANCE_NAME`_IDAC_RANGE_POSITION));

    `$INSTANCE_NAME`_IDAC_POLARITY_CONTROL_REG |= ((uint32)`$INSTANCE_NAME`_IDAC_POLARITY <<
                                                           `$INSTANCE_NAME`_IDAC_POLARITY_POSITION);

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables IDAC operations.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable the IDAC */
    `$INSTANCE_NAME`_IDAC_CONTROL_REG |= ((uint32)`$INSTANCE_NAME`_IDAC_EN_MODE <<
                                                  `$INSTANCE_NAME`_IDAC_MODE_POSITION);
    `$INSTANCE_NAME`_IDAC_POLARITY_CONTROL_REG |= ((uint32)`$INSTANCE_NAME`_IDAC_CSD_EN <<
                                                           `$INSTANCE_NAME`_IDAC_CSD_EN_POSITION);
    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Starts the IDAC hardware.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar
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
********************************************************************************
*
* Summary:
*  Stops the IDAC hardware.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Disable the IDAC */
    `$INSTANCE_NAME`_IDAC_CONTROL_REG &= ((uint32)~((uint32)`$INSTANCE_NAME`_IDAC_MODE_MASK <<
        `$INSTANCE_NAME`_IDAC_MODE_POSITION));
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetValue
********************************************************************************
*
* Summary:
*  Sets the IDAC value.
*
* Parameters:
*  uint32 value
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetValue(uint32 value)
{
    uint8 enableInterrupts;
    uint32 newRegisterValue;

    enableInterrupts = CyEnterCriticalSection();

    #if(`$INSTANCE_NAME`_IDAC_VALUE_POSITION != 0u)
        newRegisterValue = ((`$INSTANCE_NAME`_IDAC_CONTROL_REG & (~(uint32)((uint32)`$INSTANCE_NAME`_IDAC_VALUE_MASK <<
        `$INSTANCE_NAME`_IDAC_VALUE_POSITION))) | (value << `$INSTANCE_NAME`_IDAC_VALUE_POSITION));
    #else
        newRegisterValue = ((`$INSTANCE_NAME`_IDAC_CONTROL_REG & (~(uint32)`$INSTANCE_NAME`_IDAC_VALUE_MASK)) | value);
    #endif /* `$INSTANCE_NAME`_IDAC_VALUE_POSITION != 0u */

    `$INSTANCE_NAME`_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(enableInterrupts);
}

/* [] END OF FILE */
