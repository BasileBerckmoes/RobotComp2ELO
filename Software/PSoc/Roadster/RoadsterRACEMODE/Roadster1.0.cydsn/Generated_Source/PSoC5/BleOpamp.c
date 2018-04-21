/*******************************************************************************
* File Name: BleOpamp.c
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

#include "BleOpamp.h"

uint8 BleOpamp_initVar = 0u;


/*******************************************************************************   
* Function Name: BleOpamp_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  BleOpamp_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void BleOpamp_Init(void) 
{
    BleOpamp_SetPower(BleOpamp_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: BleOpamp_Enable
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
void BleOpamp_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    BleOpamp_PUMP_CR1_REG  |= (BleOpamp_PUMP_CR1_CLKSEL | BleOpamp_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    BleOpamp_PM_ACT_CFG_REG |= BleOpamp_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    BleOpamp_PM_STBY_CFG_REG |= BleOpamp_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   BleOpamp_Start
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
*  BleOpamp_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void BleOpamp_Start(void) 
{
    if(BleOpamp_initVar == 0u)
    {
        BleOpamp_initVar = 1u;
        BleOpamp_Init();
    }

    BleOpamp_Enable();
}


/*******************************************************************************
* Function Name: BleOpamp_Stop
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
void BleOpamp_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    BleOpamp_PM_ACT_CFG_REG &= (uint8)(~BleOpamp_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    BleOpamp_PM_STBY_CFG_REG &= (uint8)(~BleOpamp_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(BleOpamp_PM_ACT_CFG_REG == 0u)
    {
        BleOpamp_PUMP_CR1_REG &= (uint8)(~(BleOpamp_PUMP_CR1_CLKSEL | BleOpamp_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: BleOpamp_SetPower
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
void BleOpamp_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        BleOpamp_CR_REG &= (uint8)(~BleOpamp_PWR_MASK);
        BleOpamp_CR_REG |= power & BleOpamp_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(BleOpamp_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
