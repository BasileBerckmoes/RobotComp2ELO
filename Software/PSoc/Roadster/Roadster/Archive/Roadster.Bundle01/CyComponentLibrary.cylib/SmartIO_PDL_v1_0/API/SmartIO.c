/*******************************************************************************
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the  API for the SmartIO Component.
*
*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

/* Initialization global variable */
uint8_t `$INSTANCE_NAME`_initVar = 0u;

/* Clock configuration */
static uint32_t `$INSTANCE_NAME`_clkConfig = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* \brief Initializes the component as specified in the Configuration Dialog.
*
* This function can also be used to reinitialize the component to the settings 
* as specified in the Configuration dialog.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_Init
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    /* Save the clock configuration */
    `$INSTANCE_NAME`_clkConfig = `$INSTANCE_NAME`_INIT_CLOCK_SRC;
    /* General control */
    `$INSTANCE_NAME`_PORT->CTL = `$INSTANCE_NAME`_INIT_CTL_CONFIG;
    /* Synchronization control */
    `$INSTANCE_NAME`_PORT->SYNC_CTL = `$INSTANCE_NAME`_INIT_SYNC_CONFIG;
    /* LUT input selection */
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT0] = `$INSTANCE_NAME`_INIT_LUT0_SEL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT1] = `$INSTANCE_NAME`_INIT_LUT1_SEL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT2] = `$INSTANCE_NAME`_INIT_LUT2_SEL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT3] = `$INSTANCE_NAME`_INIT_LUT3_SEL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT4] = `$INSTANCE_NAME`_INIT_LUT4_SEL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT5] = `$INSTANCE_NAME`_INIT_LUT5_SEL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT6] = `$INSTANCE_NAME`_INIT_LUT6_SEL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_SEL[`$INSTANCE_NAME`_LUT7] = `$INSTANCE_NAME`_INIT_LUT7_SEL_CONFIG;
    /* LUT control */
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT0] = `$INSTANCE_NAME`_INIT_LUT0_CTL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT1] = `$INSTANCE_NAME`_INIT_LUT1_CTL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT2] = `$INSTANCE_NAME`_INIT_LUT2_CTL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT3] = `$INSTANCE_NAME`_INIT_LUT3_CTL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT4] = `$INSTANCE_NAME`_INIT_LUT4_CTL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT5] = `$INSTANCE_NAME`_INIT_LUT5_CTL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT6] = `$INSTANCE_NAME`_INIT_LUT6_CTL_CONFIG;
    `$INSTANCE_NAME`_PORT->LUT_CTL[`$INSTANCE_NAME`_LUT7] = `$INSTANCE_NAME`_INIT_LUT7_CTL_CONFIG;
    /* Configure the Data Unit */
    `$INSTANCE_NAME`_PORT->DU_SEL = `$INSTANCE_NAME`_INIT_DU_SEL;
    `$INSTANCE_NAME`_PORT->DU_CTL = `$INSTANCE_NAME`_INIT_DU_CTL;
    `$INSTANCE_NAME`_PORT->DATA = `$INSTANCE_NAME`_INIT_DU_DATA_REG;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* \brief Invokes `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Enable().
*  
* After this function call, the component is initialized to specified values
* in the Configuration dialog and is then enabled.
*
* If calling this function after calling `$INSTANCE_NAME`_Stop(), the fabric
* will set the clock configuration as specified before calling Stop().
*
* \globalvars
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified
*  on first function call.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_Start
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    uint32_t regVal;
    
    if (0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u; /* Component was initialized */
    }
    else
    {
        /* Restore the component settings if Stop() was called */
        if ((`$INSTANCE_NAME`_PORT->CTL & SMARTIO_PRT_CTL_ENABLED_Msk) == 0u)
        {
            /* Clear the pipeline bit and clear the clock field */            
            regVal = `$INSTANCE_NAME`_PORT->CTL & `$INSTANCE_NAME`_PIPELINE_DISABLE & `$INSTANCE_NAME`_CLOCK_CLEAR;
            /* Restore the clock settings */
            `$INSTANCE_NAME`_PORT->CTL = regVal | `$INSTANCE_NAME`_clkConfig;
        }
    }
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* \brief The routing fabric is bypassed and the block is powered down.
*
* This function saves the clock configuration before powering down. Calling
* Start() will enable the block and restore the clock setting.
* 
* \globalvars
*  `$INSTANCE_NAME`_clkConfig - used to save the clock configuration.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_Stop
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    uint32_t regVal;
    
    /* Disable the block */
    `$INSTANCE_NAME`_Disable();
    /* Save the clock setting */
    `$INSTANCE_NAME`_clkConfig = `$INSTANCE_NAME`_PORT->CTL & SMARTIO_PRT_CTL_CLOCK_SRC_Msk;
    /* Clear the clock source */
    regVal = `$INSTANCE_NAME`_PORT->CTL & `$INSTANCE_NAME`_CLOCK_CLEAR;
    /* Enable the pipeline and set the clock source to const zero */
    `$INSTANCE_NAME`_PORT->CTL = regVal | `$INSTANCE_NAME`_PIPELINE_ENABLE | `$INSTANCE_NAME`_CLOCK_CONST_ZERO;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBypass
****************************************************************************//**
*
* \brief Bypasses channels on a bit by bit basis. 
*
* Bypassed channels behave as if the SmartIO component was not present for 
* those particular channels. 
*  
* <b>Note</b> This function impacts all channels on the port. It will write
* over the bypass configuration of all the channels. 
*
* \param portChannel
*  The channel location to be bypassed on the port. If the bit value is 0, 
*  the channel is not bypassed; if the bit value is 1, the channel is bypassed.
*  Valid options are documented in \ref channelConst. These should be ORed
*  to configure multiple bypass channels.
* 
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_SetBypass
*******************************************************************************/
void `$INSTANCE_NAME`_SetBypass(uint32_t portChannel)
{   
    uint32_t regVal;
    
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    /* Configure the bypass settings of the SmartIO pins */
    regVal = `$INSTANCE_NAME`_PORT->CTL & `$INSTANCE_NAME`_BYPASS_CLEAR;
    `$INSTANCE_NAME`_PORT->CTL = regVal | (((uint32_t)(portChannel << SMARTIO_PRT_CTL_BYPASS_Pos))
                                    & SMARTIO_PRT_CTL_BYPASS_Msk);
    /* Re-enable the block */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClockSelect
****************************************************************************//**
*
* \brief Selects the component clock source.
*
* The clock selection impacts the reset behavior of the component and low power
* operation. Refer to the Functional Description section of the component
* datasheet for more information.
*
* \param clockSrc
*  The component clock source. Valid options are documented in \ref clockConst.
* 
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_ClockSelect
*******************************************************************************/
void `$INSTANCE_NAME`_ClockSelect(uint32_t clockSrc)
{
    uint32_t regVal;
    
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    /* Configure the clock source */
    regVal = `$INSTANCE_NAME`_PORT->CTL & `$INSTANCE_NAME`_CLOCK_CLEAR;
    `$INSTANCE_NAME`_PORT->CTL = regVal | (((uint32_t)(clockSrc << SMARTIO_PRT_CTL_CLOCK_SRC_Pos) 
                                    & SMARTIO_PRT_CTL_CLOCK_SRC_Msk));
    /* Re-enable the block */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HoldOverride
****************************************************************************//**
*
* \brief Controls the port's chip hibernate mode override. 
*
* This function should be used when the block is desired to be operational
* during chip deep-sleep or hibernate mode. The override functionality allows 
* the port with SmartIO component to be operational during these modes. When
* in chip active/sleep modes, the hold override functionality should be disabled.
*
* \param ovCtrl
*  Hold override control. Valid options are documented in \ref hldOvrConst.
* 
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_HoldOverride
*******************************************************************************/
void `$INSTANCE_NAME`_HoldOverride(uint32_t ovCtrl)
{
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    /* Set hold override mode */
    if (ovCtrl == `$INSTANCE_NAME`_OVCTRL_ENABLE)
    {
        `$INSTANCE_NAME`_PORT->CTL |= `$INSTANCE_NAME`_HLD_OVR_SMARTIO;
    }    
    else
    {
        `$INSTANCE_NAME`_PORT->CTL &= `$INSTANCE_NAME`_HLD_OVR_HSIOM;
    }
    /* Re-enable the block */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IoSyncMode
****************************************************************************//**
*
* \brief Controls synchronization of signals coming from I/O Pin. 
*
* The synchronization is performed using the component clock. Synchronization 
* should not be used if the component is configured to operate in asynchronous
* mode.
*
* <b>Note</b> This function impacts all gpio terminals on the port. It will 
* write over the synchronization configuration of all the gpio terminals. 
*
* \param portTerm
*  The terminal location on the port. If the bit value is 0, the terminal is
*  not synchronized; if the bit value is 1, the terminal is synchronized.
*  Valid options are documented in \ref termConst. These should be ORed to 
*  configure multiple terminals.
* 
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_IoSyncMode
*******************************************************************************/
void `$INSTANCE_NAME`_IoSyncMode(uint32_t portTerm)
{
    uint32_t regVal;
    
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    /* Configure the IO synchronization */
    regVal = `$INSTANCE_NAME`_PORT->SYNC_CTL & `$INSTANCE_NAME`_IO_SYNC_CLEAR;
    `$INSTANCE_NAME`_PORT->SYNC_CTL = regVal | (((uint32_t)(portTerm << SMARTIO_PRT_SYNC_CTL_IO_SYNC_EN_Pos))
                                         & SMARTIO_PRT_SYNC_CTL_IO_SYNC_EN_Msk);
    /* Re-enable the block */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ChipSyncMode
****************************************************************************//**
*
* \brief Controls synchronization of signals coming from chip to the component. 
*
* The synchronization is performed using the component clock. Synchronization 
* should not be used if the component is configured to operate in asynchronous
* mode.
*
* <b>Note</b> This function impacts all data terminals on the port. It will 
* write over the synchronization configuration of all the data terminals. 
*
* \param portTerm
*  The terminal location on the port. If the bit value is 0, the terminal is
*  not synchronized; if the bit value is 1, the terminal is synchronized.
*  Valid options are documented in \ref termConst. These should be ORed to 
*  configure multiple terminals.
* 
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_ChipSyncMode
*******************************************************************************/
void `$INSTANCE_NAME`_ChipSyncMode(uint32_t portTerm)
{
    uint32_t regVal;
    
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    /* Configure the Chip data synchronization */
    regVal = `$INSTANCE_NAME`_PORT->SYNC_CTL & `$INSTANCE_NAME`_DATA_SYNC_CLEAR;
    `$INSTANCE_NAME`_PORT->SYNC_CTL = regVal | (((uint32_t)(portTerm << SMARTIO_PRT_SYNC_CTL_CHIP_SYNC_EN_Pos))
                                        & SMARTIO_PRT_SYNC_CTL_CHIP_SYNC_EN_Msk);
    /* Re-enable the block */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LUT_SelectInputs
****************************************************************************//**
*
* \brief This function is used to select individual inputs to the specified LUT. 
*
* This function can be used to configure multiple LUTs with the same input
* configuration.
* 
* <b>Note</b> The selections are different for the upper and lower nibbles.
* See the LUT input parameters and Functional Description section in the
* component datasheet for more information.
*
* \param lutNum
*  LUT number. Valid options are documented in \ref lutNumConst.
*
* \param inputNum
*  The input number (input0, input1, input2). Valid options are documented 
*  in \ref inputNumConst. Note that LUT input0 does not accept LUT0 output as
*  an input.
*
* \param inputSrc
*  The source of the LUT input. Valid options are documented in
*  \ref inputSrcConst.
*
* \return 
*  Status of the LUT input selection.
*   Status          | Description
*   ----------------|--------------------
*   CY_RET_SUCCESS   | Write successful
*   CY_RET_BAD_PARAM | Invalid parameter
* 
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_LUT_SelectInputs
*******************************************************************************/
cy_status `$INSTANCE_NAME`_LUT_SelectInputs(uint32_t lutNum, uint32_t inputNum, uint32_t inputSrc)
{
    cy_status callStatus = CY_RET_SUCCESS;
    uint32_t sel;

    /* Input validation */
    if((inputSrc == `$INSTANCE_NAME`_SRC_LUT0) && ((inputNum & `$INSTANCE_NAME`_LUT_INPUT0) == `$INSTANCE_NAME`_LUT_INPUT0))
    {
        /* LUT input0 does not support LUT0 as an input */
        callStatus = CY_RET_BAD_PARAM;
    }
    if((inputSrc == `$INSTANCE_NAME`_SRC_DU) && ((inputNum & (`$INSTANCE_NAME`_LUT_INPUT1 | `$INSTANCE_NAME`_LUT_INPUT2)) != 0u))
    {
        /* LUT input1 and input2 do not support DU output as an input */
        callStatus = CY_RET_BAD_PARAM;
    }
    
    /* Configure LUT selection */
    if (callStatus != CY_RET_BAD_PARAM)
    {
        /* Must disable the block before configuring */
        `$INSTANCE_NAME`_Disable();
        
        sel = `$INSTANCE_NAME`_PORT->LUT_SEL[lutNum];
        switch(inputNum)
        {
            case `$INSTANCE_NAME`_LUT_INPUT0:
                sel = (sel & `$INSTANCE_NAME`_LUT_TR0_CLEAR) 
                        | ((uint32_t)(inputSrc << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk);
                break;
            case `$INSTANCE_NAME`_LUT_INPUT1:
                sel = (sel & `$INSTANCE_NAME`_LUT_TR1_CLEAR) 
                        | ((uint32_t)(inputSrc << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk);
                break;
            case `$INSTANCE_NAME`_LUT_INPUT2:
                sel = (sel & `$INSTANCE_NAME`_LUT_TR2_CLEAR)
                        | ((uint32_t)(inputSrc << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk);
                break;
            case `$INSTANCE_NAME`_LUT_INPUT_ALL:
                sel = (sel & `$INSTANCE_NAME`_LUT_TR_CLEAR_ALL) 
                        | ((uint32_t)(inputSrc << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk)
                        | ((uint32_t)(inputSrc << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk)
                        | ((uint32_t)(inputSrc << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk);
                break;
            default: 
                callStatus = CY_RET_BAD_PARAM;
                break;
        }
        `$INSTANCE_NAME`_PORT->LUT_SEL[lutNum] = sel;
        
        /* Re-enable the block */
        `$INSTANCE_NAME`_Enable();
    }    
    return callStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LUT_ConfigureMode
****************************************************************************//**
*
* \brief This function sets the logical function of the selected LUT (based on 
*  the 3 inputs) and specifies its operating mode. 
*
*  This function can be used to configure multiple LUTs with the same 
*  configuration. The LUT mapping (truth table) is defined as follows.
*
*   input2 | input1 | input0 | Mapping bit
*   -------| ------ | ------ | -----------
*     0    |   0    |   0    |    bit0
*     0    |   0    |   1    |    bit1
*     0    |   1    |   0    |    bit2
*     0    |   1    |   1    |    bit3
*     1    |   0    |   0    |    bit4
*     1    |   0    |   1    |    bit5
*     1    |   1    |   0    |    bit6
*     1    |   1    |   1    |    bit7
*
* \param lutNum
*  LUT number. Valid options are documented in \ref lutNumConst.
*
* \param mapping
*  This is the LUT truth table. Bit0 corresponds to the LUT output when the 
*  input value is (in2=0, in1=0, in0=0). Bit7 corresponds to the LUT output 
*  when the input value is (in2=1, in1=1, in0=1).
*
* \param mode
*  The LUT mode. Valid options are documented in \ref modeConst.
* 
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_LUT_ConfigureMode
*******************************************************************************/
void `$INSTANCE_NAME`_LUT_ConfigureMode(uint32_t lutNum, uint32_t mapping, uint32_t mode)
{
    uint32_t ctl;
    
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    
    ctl = `$INSTANCE_NAME`_PORT->LUT_CTL[lutNum] & `$INSTANCE_NAME`_LUT_CTL_CLEAR;
    `$INSTANCE_NAME`_PORT->LUT_CTL[lutNum] = ctl 
                                            | (((uint32_t)((mapping << SMARTIO_PRT_LUT_CTL_LUT_Pos)
                                            & SMARTIO_PRT_LUT_CTL_LUT_Msk))
                                            | ((uint32_t)(((uint32_t)mode << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos) 
                                            & SMARTIO_PRT_LUT_CTL_LUT_OPC_Msk)));
    /* Re-enable the block */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DU_SelectTriggers
****************************************************************************//**
*
* \brief Selects the trigger sources for the data unit.
*
* \param tr0Sel
*  Trigger 0 input selection. Valid options are documented in \ref duTrConst.
*
* \param tr1Sel
*  Trigger 1 input selection. Valid options are documented in \ref duTrConst.
*
* \param tr2Sel
*  Trigger 2 input selection. Valid options are documented in \ref duTrConst.
*
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_DU_SelectTriggers
*******************************************************************************/
cy_status `$INSTANCE_NAME`_DU_SelectTriggers(uint32_t tr0Sel, uint32_t tr1Sel, uint32_t tr2Sel)
{
    cy_status callStatus = CY_RET_SUCCESS;
    uint32_t sel;
    
    if((tr0Sel > `$INSTANCE_NAME`_DUTRIG_MAX) || (tr1Sel > `$INSTANCE_NAME`_DUTRIG_MAX) || (tr2Sel > `$INSTANCE_NAME`_DUTRIG_MAX))
    {
        callStatus = CY_RET_BAD_PARAM;
    }
    else
    {
        /* Must disable the block before configuring */
        `$INSTANCE_NAME`_Disable();
        
        sel = `$INSTANCE_NAME`_PORT->DU_SEL & `$INSTANCE_NAME`_DU_TR_CLEAR_ALL;
        `$INSTANCE_NAME`_PORT->DU_SEL = sel 
                                | ((uint32_t)(tr0Sel << SMARTIO_PRT_DU_SEL_DU_TR0_SEL_Pos))
                                | ((uint32_t)(tr1Sel << SMARTIO_PRT_DU_SEL_DU_TR1_SEL_Pos))
                                | ((uint32_t)(tr2Sel << SMARTIO_PRT_DU_SEL_DU_TR2_SEL_Pos));
        
        /* Re-enable the block */
        `$INSTANCE_NAME`_Enable();
    }
    
    return callStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DU_SelectData
****************************************************************************//**
*
* \brief Specifies the values for the Data0 and Data1 registers in the Data Unit.
*
* \param dataNum
*  DU DATA register selection. Valid options are documented in \ref duDataConst.
*
* \param dataSel
*  DU DATA register source selection. Valid options are documented in \ref duDataSrcConst.
*
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_DU_SelectData
*******************************************************************************/
cy_status `$INSTANCE_NAME`_DU_SelectData(uint32_t dataNum, uint32_t dataSel)
{
    cy_status callStatus = CY_RET_SUCCESS;
    uint32_t sel;
    
    /* Must disable the block before configuring */
    `$INSTANCE_NAME`_Disable();
    
    sel = `$INSTANCE_NAME`_PORT->DU_SEL;
    switch(dataNum)
    {
        case `$INSTANCE_NAME`_DATA0:
            sel = (sel & `$INSTANCE_NAME`_DU_DATA0_CLEAR)
                  | (uint32_t)((dataSel << SMARTIO_PRT_DU_SEL_DU_DATA0_SEL_Pos) & SMARTIO_PRT_DU_SEL_DU_DATA0_SEL_Msk);
        break;
        case `$INSTANCE_NAME`_DATA1:
            sel = (sel & `$INSTANCE_NAME`_DU_DATA1_CLEAR)
                  | (uint32_t)((dataSel << SMARTIO_PRT_DU_SEL_DU_DATA1_SEL_Pos) & SMARTIO_PRT_DU_SEL_DU_DATA1_SEL_Msk);
        break;
        case `$INSTANCE_NAME`_DATA_BOTH:
            sel = (sel & `$INSTANCE_NAME`_DU_DATA01_CLEAR_BOTH)
                   |(uint32_t)((dataSel << SMARTIO_PRT_DU_SEL_DU_DATA0_SEL_Pos) & SMARTIO_PRT_DU_SEL_DU_DATA0_SEL_Msk)
                   |(uint32_t)((dataSel << SMARTIO_PRT_DU_SEL_DU_DATA1_SEL_Pos) & SMARTIO_PRT_DU_SEL_DU_DATA1_SEL_Msk);
        break;
        default:
            callStatus = CY_RET_BAD_PARAM;
        break;
    }
    `$INSTANCE_NAME`_PORT->DU_SEL = sel;
    
    /* Re-enable the block */
    `$INSTANCE_NAME`_Enable();
    
    return callStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DU_RegValue
****************************************************************************//**
*
* \brief Specifies the 8-bit value in the internal DU register that may be a
* source for Data0 and/or Data1.
*
* \param dataValue
*  8-bit value to be stored in the register.
*
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_DU_RegValue
*******************************************************************************/
cy_status `$INSTANCE_NAME`_DU_RegValue(uint32_t dataValue)
{
    cy_status callStatus = CY_RET_SUCCESS;
    
    if(dataValue > `$INSTANCE_NAME`_REGVAL_MAX)
    {
        callStatus = CY_RET_BAD_PARAM;
    }
    else
    {
        /* Must disable the block before configuring */
        `$INSTANCE_NAME`_Disable();
        `$INSTANCE_NAME`_PORT->DATA = dataValue;
        /* Re-enable the block */
        `$INSTANCE_NAME`_Enable();
    }
    
    return callStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DU_OpCode
****************************************************************************//**
*
* \brief Selects the data unit operation and the size of the data to be 
* operated on (1 to 8 bits).
*
* \param opCode
*  Op-code for the Data Unit. Valid options are documented in \ref duOpcConst.
*
* \param dataSize
*  Size/width of the data unit operands. Range: 1 to 8 bits.
*
* \sideeffect
*  This function disables the block for reconfiguration. During this time,
*  all signals on the port will be bypassed. All peripheral and gpio signals
*  must be stopped or properly handled to account for the bypass state.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_DU_OpCode
*******************************************************************************/
cy_status `$INSTANCE_NAME`_DU_OpCode(uint32_t opCode, uint32_t dataSize)
{
    cy_status callStatus = CY_RET_SUCCESS;
    
    if((opCode == 0u) || (opCode > `$INSTANCE_NAME`_OPC_MAX) || (dataSize > `$INSTANCE_NAME`_DUSIZE_MAX))
    {
        callStatus = CY_RET_BAD_PARAM;
    }
    else
    {
         /* Must disable the block before configuring */
        `$INSTANCE_NAME`_Disable();
        `$INSTANCE_NAME`_PORT->DU_CTL = (uint32_t)(((dataSize - 1u) << SMARTIO_PRT_DU_CTL_DU_SIZE_Pos))
                         | (uint32_t)((opCode << SMARTIO_PRT_DU_CTL_DU_OPC_Pos));       
        /* Re-enable the block */
        `$INSTANCE_NAME`_Enable();
    }
    
    return callStatus;
}


/* [] END OF FILE */
