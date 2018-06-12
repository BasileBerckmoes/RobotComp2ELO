/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the Comparator component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call `$INSTANCE_NAME`_Init() because
*  the `$INSTANCE_NAME`_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* \sideeffect
*  This API includes blocking timeout required to run CSD IP block.
*  Minimum timeout required for CSD IP block start is specified by
*  `$INSTANCE_NAME`_CSD_IP_STARTUP_TIMEOUT define.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_SAMPLECLK_DIVIDER);

    /* Set CSD IP block switches */
    #if (`$INSTANCE_NAME`_INTERNAL_BANDGAP_REFERENCE == `$INSTANCE_NAME`_VOLTAGE_REF_SOURCE)
        `$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_REG |= `$INSTANCE_NAME`_SW_SGR_CLOSED;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_BANDGAP_REFERENCE == `$INSTANCE_NAME`_VOLTAGE_REF_SOURCE) */
    #if (`$INSTANCE_NAME`_2000_MV >= `$INSTANCE_NAME`_CYDEV_VDDA_MV)
        `$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_REG |= `$INSTANCE_NAME`_SW_IRLB_CLOSED | `$INSTANCE_NAME`_SW_IRH_CLOSED;
    #endif /* (`$INSTANCE_NAME`_2000_MV <= `$INSTANCE_NAME`_CYDEV_VDDA_MV) */
    `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_REG = `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_REG_INIT;

    /* Set initial configuration for CSD IP block */
    `$INSTANCE_NAME`_CSD_CONFIG_REG |= `$INSTANCE_NAME`_CSD_CONFIG_REG_INIT;
    CyDelayUs(`$INSTANCE_NAME`_CSD_IP_STARTUP_TIMEOUT);

    `$INSTANCE_NAME`_CSD_REFGEN_REG = `$INSTANCE_NAME`_CSD_REFGEN_REG_INIT;
    `$INSTANCE_NAME`_CSD_CSDCMP_REG = `$INSTANCE_NAME`_CSD_CSDCMP_REG_INIT;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
*  Activates the hardware and begins the component operation. It is not
*  necessary to call `$INSTANCE_NAME`_Enable() because the
*  `$INSTANCE_NAME`_Start() API calls this function, which is the preferred
*  method to begin the component operation.
*
* \sideeffect
*  This API includes a blocking timeout required to run Reference Generator and
*  CSD CMP blocks.
*  The minimum timeout required for REFGEN block start is specified by
*  `$INSTANCE_NAME`_REFGEN_STARTUP_TIMEOUT define.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_SampleClk_Start();

    `$INSTANCE_NAME`_CSD_REFGEN_REG |= `$INSTANCE_NAME`_REFGEN_EN;
    `$INSTANCE_NAME`_CSD_CSDCMP_REG |= `$INSTANCE_NAME`_CSDCMP_EN;

    CyDelayUs(`$INSTANCE_NAME`_REFGEN_STARTUP_TIMEOUT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  Performs all of the required initialization for the component and enables
*  power to the block. The first time the routine is executed, the power level
*  is set. When called to restart the comparator following a
*  `$INSTANCE_NAME`_Stop() call, the current component parameter settings are
*  retained.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_initVar - This variable is used to indicate the initial
*  configuration of this component. The variable is initialized to zero and
*  set to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows
*  the component initialization without re-initialization in all subsequent
*  calls to the `$INSTANCE_NAME`_Start() routine.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_initVar = 1u;
        `$INSTANCE_NAME`_Init();
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
*  Turn off the Comparator block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_CSD_CSDCMP_REG &= ~`$INSTANCE_NAME`_CSDCMP_EN;
    `$INSTANCE_NAME`_CSD_REFGEN_REG &= ~`$INSTANCE_NAME`_REFGEN_EN;

    `$INSTANCE_NAME`_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
****************************************************************************//**
*
*  This function returns a nonzero value when the voltage connected to the
*  positive input is greater than Vref.
*
*  \return
*  uint32: Comparator output state. The nonzero value when the positive input
*          voltage is greater than Vref; otherwise, the return value is zero.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetCompare(void)
{
    return ((uint32)(0u != (`$INSTANCE_NAME`_CSD_STATUS_REG & `$INSTANCE_NAME`_CSDCMP_OUT)));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetReferenceVoltageType
****************************************************************************//**
*
*  The API enables the REFGEN block in the bypass mode if the input voltage
*  reference is fixed. Or else, it enables the REFGEN block in the high power
*  mode.
*
*  \param
*  refVoltageType:    Comparator response time parameter.
* * `$INSTANCE_NAME`_FIXED_REF_VOLTAGE      - The fixed reference voltage type
* * `$INSTANCE_NAME`_ADJUSTABLE_REF_VOLTAGE - The adjustable reference voltage
*                                             type
*
* \sideeffect
*  This API stops the component for reconfiguration. All interrupts are disabled
*  for the time this API is called.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetReferenceVoltageType(uint32 refVoltageType)
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CSD_CSDCMP_REG &= ~`$INSTANCE_NAME`_CSDCMP_EN;

    if (`$INSTANCE_NAME`_FIXED_REF_VOLTAGE == refVoltageType)
    {
        `$INSTANCE_NAME`_CSD_REFGEN_REG = (`$INSTANCE_NAME`_CSD_REFGEN_REG & ~`$INSTANCE_NAME`_RES_EN) |
            `$INSTANCE_NAME`_BYPASS;

        `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_REG = `$INSTANCE_NAME`_SW_SCRH_CLOSED;
    }
    else /* `$INSTANCE_NAME`_ADJUSTABLE_REF_VOLTAGE */
    {
        `$INSTANCE_NAME`_CSD_REFGEN_REG = (`$INSTANCE_NAME`_CSD_REFGEN_REG & ~`$INSTANCE_NAME`_BYPASS) |
            `$INSTANCE_NAME`_RES_EN;

        `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_REG = `$INSTANCE_NAME`_SW_SCRL_CLOSED;
    }

    `$INSTANCE_NAME`_CSD_CSDCMP_REG |= `$INSTANCE_NAME`_CSDCMP_EN;
    CyExitCriticalSection(interruptState);

    CyDelayUs(`$INSTANCE_NAME`_CSDCMP_STARTUP_TIMEOUT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetVoltageTap
****************************************************************************//**
*
*  Sets the reference voltage if the REFGEN block is enabled.
*
*  \param
*  voltageTap:    The tap number in the range from 1 to 32. The parameter can
*                 be calculated as following:
*                 Tap value = Round (Required reference voltage in mV /
*                                    `$INSTANCE_NAME`_VREF_STEP_MVOLTS)
*                 Note: The required reference voltage in mV should be in the
*                       range from 0.6V to Vrange (Actual reference voltage
*                       range from the component customizer).
*                       `$INSTANCE_NAME`_VREF_STEP_MVOLTS value is provided
*                       in the component header file.
*
* \sideeffect
*  This API has no effect if the REFGEN block is in the bypass mode.
*  This API stops the component for reconfiguration. All interrupts are disabled
*  for the time this API is called.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetVoltageTap(uint32 voltageTap)
{
    uint8 interruptState;

    voltageTap = (uint32) ((voltageTap - 1u) << CYFLD_CSD_VREFLO_SEL__OFFSET);
    CYASSERT(0u == (voltageTap & ~`$INSTANCE_NAME`_VREFLO_SEL_MASK));

    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CSD_CSDCMP_REG &= ~`$INSTANCE_NAME`_CSDCMP_EN;

    `$INSTANCE_NAME`_CSD_REFGEN_REG = (`$INSTANCE_NAME`_CSD_REFGEN_REG & ~`$INSTANCE_NAME`_VREFLO_SEL_MASK) |
        voltageTap;

    `$INSTANCE_NAME`_CSD_CSDCMP_REG |= `$INSTANCE_NAME`_CSDCMP_EN;
    CyExitCriticalSection(interruptState);

    CyDelayUs(`$INSTANCE_NAME`_CSDCMP_STARTUP_TIMEOUT);
}


/* [] END OF FILE */
