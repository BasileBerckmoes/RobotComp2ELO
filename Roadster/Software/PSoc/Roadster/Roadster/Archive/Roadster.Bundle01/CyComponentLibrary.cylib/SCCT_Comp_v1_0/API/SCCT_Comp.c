/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the SCCT Comparator
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "CyLib.h"

#if (1u == CYDEV_VARIABLE_VDDA)
    #include "CyScBoostClk.h"
#endif /* 1u == CYDEV_VARIABLE_VDDA */

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the `$INSTANCE_NAME` according to the customizer
*  settings. It is not necessary to call `$INSTANCE_NAME`_Init() because the
*  `$INSTANCE_NAME`_Start() API calls this function and is the preferred method
*  to begin `$INSTANCE_NAME` operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    /* Set Naked Op-Amp - Comparator mode */
    `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_COMPARATOR;

    /* Reset `$INSTANCE_NAME` Control Register 1 to initial value */
    `$INSTANCE_NAME`_CR1_REG = 0u;

    /* Set bias current to normal operation */
    `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_BIAS;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins `$INSTANCE_NAME` operation. It is not
*  necessary to call `$INSTANCE_NAME`_Enable() because the
*  `$INSTANCE_NAME`_Start() API calls this function, which is the preferred
*  method to begin `$INSTANCE_NAME` operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable power to the `$INSTANCE_NAME` in Active mode */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;

    /* Enable the power to the `$INSTANCE_NAME` in Alternative active mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;

    /* `$INSTANCE_NAME` internal Pump Clock Selection */
    `$INSTANCE_NAME`_PUMP_CR1_REG |= `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL;

    #if (1u == CYDEV_VARIABLE_VDDA)

        if (1u == CyScPumpEnabled)
        {
            `$INSTANCE_NAME`_BSTCLK_REG &= (uint8)(~`$INSTANCE_NAME`_BST_CLK_INDEX_MASK);
            `$INSTANCE_NAME`_BSTCLK_REG |= (`$INSTANCE_NAME`_BST_CLK_EN | CyScBoostClk__INDEX);
            `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
            CyScBoostClk_Start();
        }
        else
        {
            `$INSTANCE_NAME`_BSTCLK_REG &= (uint8)(~`$INSTANCE_NAME`_BST_CLK_EN);
            `$INSTANCE_NAME`_SC_MISC_REG &= (uint8)(~`$INSTANCE_NAME`_PUMP_FORCE);
        }

    #endif /* 1u == CYDEV_VARIABLE_VDDA */

    CyExitCriticalSection(enableInterrupts);

    /* Enable clock (aclk) to the `$INSTANCE_NAME` and disable dynamic control */
    `$INSTANCE_NAME`_SC_CLK_REG = `$INSTANCE_NAME`_CLK_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the `$INSTANCE_NAME` and
*  enables power to the `$INSTANCE_NAME`. The first time the routine is
*  executed, the `$INSTANCE_NAME` is initialized to the configuration from the
*  customizer. When called to restart the `$INSTANCE_NAME` following a
*  `$INSTANCE_NAME`_Stop() call, the current `$INSTANCE_NAME` parameter
*  settings are retained.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
* Side Effect:
*  If the initVar variable is already set, this function only calls the
*  `$INSTANCE_NAME`_Enable() function.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if (0u == `$INSTANCE_NAME`_initVar)
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
*  Turns off the `$INSTANCE_NAME`. It will disable the related SC/CT block.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;    

    enableInterrupts = CyEnterCriticalSection();

    /* Disble power to the `$INSTANCE_NAME` in Active mode template */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG &= (uint8)(~`$INSTANCE_NAME`_ACT_PWR_EN);

    /* Disble power to the `$INSTANCE_NAME` in Alternative Active mode template */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8)(~`$INSTANCE_NAME`_STBY_PWR_EN);

    #if (1u == CYDEV_VARIABLE_VDDA)

        `$INSTANCE_NAME`_BSTCLK_REG &= (uint8)(~`$INSTANCE_NAME`_BST_CLK_EN);

        /* Disable pumps only if there aren't any SC/CT block in use */
        if (0u == (`$INSTANCE_NAME`_PM_ACT_CFG_REG & `$INSTANCE_NAME`_PM_ACT_CFG_MASK))
        {
            `$INSTANCE_NAME`_SC_MISC_REG &= (uint8)(~`$INSTANCE_NAME`_PUMP_FORCE);
            `$INSTANCE_NAME`_PUMP_CR1_REG &= (uint8)(~`$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL);
            CyScBoostClk_Stop();
        }

    #endif /* 1u == CYDEV_VARIABLE_VDDA */

    CyExitCriticalSection(enableInterrupts);
    
    /* Disable clock (aclk) to `$INSTANCE_NAME` */
    `$INSTANCE_NAME`_SC_CLK_REG &= (uint8)(~`$INSTANCE_NAME`_CLK_EN);
}


/* [] END OF FILE */
