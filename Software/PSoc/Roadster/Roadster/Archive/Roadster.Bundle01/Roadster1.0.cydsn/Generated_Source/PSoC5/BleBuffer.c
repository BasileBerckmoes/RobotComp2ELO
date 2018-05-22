/*******************************************************************************
* File Name: BleBuffer.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "BleBuffer.h"

uint8 BleBuffer_initVar = 0u;


/*******************************************************************************   
* Function Name: BleBuffer_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  BleBuffer_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void BleBuffer_Init(void) 
{
    BleBuffer_SetPower(BleBuffer_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: BleBuffer_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void BleBuffer_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    BleBuffer_PUMP_CR1_REG  |= (BleBuffer_PUMP_CR1_CLKSEL | BleBuffer_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    BleBuffer_PM_ACT_CFG_REG |= BleBuffer_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    BleBuffer_PM_STBY_CFG_REG |= BleBuffer_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   BleBuffer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BleBuffer_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void BleBuffer_Start(void) 
{
    if(BleBuffer_initVar == 0u)
    {
        BleBuffer_initVar = 1u;
        BleBuffer_Init();
    }

    BleBuffer_Enable();
}


/*******************************************************************************
* Function Name: BleBuffer_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void BleBuffer_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    BleBuffer_PM_ACT_CFG_REG &= (uint8)(~BleBuffer_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    BleBuffer_PM_STBY_CFG_REG &= (uint8)(~BleBuffer_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(BleBuffer_PM_ACT_CFG_REG == 0u)
    {
        BleBuffer_PUMP_CR1_REG &= (uint8)(~(BleBuffer_PUMP_CR1_CLKSEL | BleBuffer_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: BleBuffer_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void BleBuffer_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        BleBuffer_CR_REG &= (uint8)(~BleBuffer_PWR_MASK);
        BleBuffer_CR_REG |= power & BleBuffer_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(BleBuffer_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
