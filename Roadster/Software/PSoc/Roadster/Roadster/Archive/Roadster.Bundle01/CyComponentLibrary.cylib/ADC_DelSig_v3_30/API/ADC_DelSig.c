/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Delta-Sigma ADC
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
    #include "`$INSTANCE_NAME`_theACLK.h"
#endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

#include "`$INSTANCE_NAME`_Ext_CP_Clk.h"

#if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
    #include "`$INSTANCE_NAME`_AMux.h"
#endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */


/***************************************
* Global data allocation
***************************************/

/* Software flag for checking conversion completed or not */
volatile uint8 `$INSTANCE_NAME`_convDone = 0u;

/* Software flag to stop conversion for single sample conversion mode
*   with resolution above 16 bits 
*/
volatile uint8 `$INSTANCE_NAME`_stopConversion = 0u;

/* To run the initialization block only at the start up */
uint8 `$INSTANCE_NAME`_initVar = 0u;

/* To check whether ADC started or not before switching the configuration */
volatile uint8 `$INSTANCE_NAME`_started = 0u;

/* Flag to hold ADC config number. By default active config is 1. */
volatile uint8 `$INSTANCE_NAME`_Config = 1u;

volatile int32 `$INSTANCE_NAME`_Offset = 0;
volatile int32 `$INSTANCE_NAME`_CountsPerVolt;


/***************************************
* Local data allocation
***************************************/

/* The array with precalculated gain compensation coefficients */
static `$INSTANCE_NAME`_GCOR_STRUCT `$INSTANCE_NAME`_gcor[`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS];



/***************************************
* Forward function references
***************************************/
static void `$INSTANCE_NAME`_InitConfig(uint8 config) `=ReentrantKeil($INSTANCE_NAME . "_InitConfig")`;
static void `$INSTANCE_NAME`_GainCompensation(uint8 inputRange, uint16 idealDecGain, uint16 idealOddDecGain, 
                            uint8 resolution, uint8 config) `=ReentrantKeil($INSTANCE_NAME . "_GainCompensation")`;
static void `$INSTANCE_NAME`_SetDSMRef0Reg(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_SetDSMRef0Reg")`;


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
*******************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
* `$INSTANCE_NAME`_Start().
*
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

    `$INSTANCE_NAME`_Config = 1u;
    `$INSTANCE_NAME`_convDone = 0u;

    `$INSTANCE_NAME`_Ext_CP_Clk_SetMode(CYCLK_DUTY);

    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_theACLK_SetMode(CYCLK_DUTY);
    #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

    #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
        /* Set interrupt priority */
        CyIntSetPriority(`$INSTANCE_NAME`_INTC_NUMBER, `$INSTANCE_NAME`_INTC_PRIOR_NUMBER);
    #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */

    /* Init static registers with common configuration */
    `$INSTANCE_NAME`_DSM_DEM0_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_DEM0;
    `$INSTANCE_NAME`_DSM_DEM1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_DEM1;
    `$INSTANCE_NAME`_DSM_MISC_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_MISC;
    `$INSTANCE_NAME`_DSM_CLK_REG    |= `$INSTANCE_NAME`_`$Config1_Name`_DSM_CLK;
    `$INSTANCE_NAME`_DSM_REF1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF1;

    `$INSTANCE_NAME`_DSM_OUT0_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_OUT0;
    `$INSTANCE_NAME`_DSM_OUT1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_OUT1;

    `$INSTANCE_NAME`_DSM_CR0_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR0;
    `$INSTANCE_NAME`_DSM_CR1_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR1;
#if(`$INSTANCE_NAME`_MI_ENABLE != 0u) /* Enable Modulator Input */
    `$INSTANCE_NAME`_DSM_CR3_REG     |= `$INSTANCE_NAME`_DSM_MODBIT_EN;
#else
    `$INSTANCE_NAME`_DSM_CR3_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR3;
#endif /* `$INSTANCE_NAME`_MI_ENABLE != 0u*/    
    `$INSTANCE_NAME`_DSM_CR8_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR8;
    `$INSTANCE_NAME`_DSM_CR9_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR9;
    `$INSTANCE_NAME`_DSM_CR13_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR13;

    `$INSTANCE_NAME`_DEC_SR_REG      = `$INSTANCE_NAME`_`$Config1_Name`_DEC_SR;

    /* Calculate Gain compensation coefficients for all configurations */
    `$INSTANCE_NAME`_GainCompensation(`$INSTANCE_NAME`_`$Config1_Name`_INPUT_RANGE,
                                      `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_DEC_GAIN,
                                      `$INSTANCE_NAME`_`$Config1_Name`_IDEAL_ODDDEC_GAIN,
                                      `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION,
                                      `$INSTANCE_NAME`_`$Config1_Name`);
    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1)
        `$INSTANCE_NAME`_GainCompensation(`$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE,
                                          `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_DEC_GAIN,
                                          `$INSTANCE_NAME`_`$Config2_Name`_IDEAL_ODDDEC_GAIN,
                                          `$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION,
                                          `$INSTANCE_NAME`_`$Config2_Name`);
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1 */
    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2)
        `$INSTANCE_NAME`_GainCompensation(`$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE,
                                          `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_DEC_GAIN,
                                          `$INSTANCE_NAME`_`$Config3_Name`_IDEAL_ODDDEC_GAIN,
                                          `$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION,
                                          `$INSTANCE_NAME`_`$Config3_Name`);
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2 */
    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3)
        `$INSTANCE_NAME`_GainCompensation(`$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE,
                                          `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_DEC_GAIN,
                                          `$INSTANCE_NAME`_`$Config4_Name`_IDEAL_ODDDEC_GAIN,
                                          `$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION,
                                          `$INSTANCE_NAME`_`$Config4_Name`);
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3 */

    /* Set GCOR register for config1 */
    `$INSTANCE_NAME`_DEC_GVAL_REG = `$INSTANCE_NAME`_gcor[`$INSTANCE_NAME`_Config - 1u].gval;
    CY_SET_REG16(`$INSTANCE_NAME`_DEC_GCOR_16B_PTR, `$INSTANCE_NAME`_gcor[`$INSTANCE_NAME`_Config - 1u].gcor);

    /* Initialize the registers with default customizer settings for config1 */
    `$INSTANCE_NAME`_InitConfig(`$INSTANCE_NAME`_Config);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
*******************************************************************************
*
* Summary:
*  Enables the ADC DelSig block operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects: 
*  Enables internal interrupt.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
	uint8 config;
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Read volatile variable to the local variable */
    config = `$INSTANCE_NAME`_Config;
    
    /* Enable active mode power for ADC */
    `$INSTANCE_NAME`_PWRMGR_DEC_REG |= `$INSTANCE_NAME`_ACT_PWR_DEC_EN;
    `$INSTANCE_NAME`_PWRMGR_DSM_REG |= `$INSTANCE_NAME`_ACT_PWR_DSM_EN;

     /* Enable alternative active mode power for ADC */
    `$INSTANCE_NAME`_STBY_PWRMGR_DEC_REG |= `$INSTANCE_NAME`_STBY_PWR_DEC_EN;
    `$INSTANCE_NAME`_STBY_PWRMGR_DSM_REG |= `$INSTANCE_NAME`_STBY_PWR_DSM_EN;

    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and REFBUF1, enable PRES */
    `$INSTANCE_NAME`_RESET_CR4_REG |= `$INSTANCE_NAME`_IGNORE_PRESA1;
    `$INSTANCE_NAME`_RESET_CR5_REG |= `$INSTANCE_NAME`_IGNORE_PRESA2;

    `$INSTANCE_NAME`_DSM_CR17_REG |= (`$INSTANCE_NAME`_DSM_EN_BUF_VREF | `$INSTANCE_NAME`_DSM_EN_BUF_VCM);

    /* Code to disable the REFBUF0 if reference chosen is External ref */
    #if (((`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) || \
          (`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32)) || \
         ((`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1) && \
          ((`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||  \
           (`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))) || \
         ((`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2) && \
          ((`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||  \
           (`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))) || \
         ((`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3) && \
          ((`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) || \
           (`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))))
        if (((config == 1u) &&
            ((`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||
             (`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
            ((config == 2u) &&
            ((`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||
             (`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
            ((config == 3u) &&
            ((`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||
             (`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
            ((config == 4u) &&
            ((`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P03) ||
             (`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE == `$INSTANCE_NAME`_EXT_REF_ON_P32))))
        {
            /* Disable the REFBUF0 */
            `$INSTANCE_NAME`_DSM_CR17_REG &= (uint8)~`$INSTANCE_NAME`_DSM_EN_BUF_VREF;
        }
    #endif /* External ref */

    #if (((`$INSTANCE_NAME`_`$Config1_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) || \
         ((`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1) && \
          (`$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)) || \
         ((`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2) && \
          (`$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)) || \
         ((`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3) && \
          (`$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF))))
        if(((config == 1u) &&
            (`$INSTANCE_NAME`_`$Config1_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) &&
            ((`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) &&
             (`$INSTANCE_NAME`_`$Config1_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
             ((config == 2u) &&
              (`$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) &&
             ((`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) &&
             (`$INSTANCE_NAME`_`$Config2_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
             ((config == 3u) &&
              (`$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) &&
             ((`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) &&
             (`$INSTANCE_NAME`_`$Config3_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32))) ||
             ((config == 4u) &&
              (`$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) &&
             ((`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P03) &&
             (`$INSTANCE_NAME`_`$Config4_Name`_REFERENCE != `$INSTANCE_NAME`_EXT_REF_ON_P32))))
        {
            /* Enable the REFBUF1 */
            `$INSTANCE_NAME`_DSM_REF0_REG |= `$INSTANCE_NAME`_DSM_EN_BUF_VREF_INN;
        }
    #endif /* VSSA_TO_2VREF */
    if(config != 0u)
    {
        /* Suppress compiler warning */
    }

    /* Wait for 3 microseconds */
    CyDelayUs(`$INSTANCE_NAME`_PRES_DELAY_TIME);

    /* Enable the press circuit */
    `$INSTANCE_NAME`_RESET_CR4_REG &= (uint8)~`$INSTANCE_NAME`_IGNORE_PRESA1;
    `$INSTANCE_NAME`_RESET_CR5_REG &= (uint8)~`$INSTANCE_NAME`_IGNORE_PRESA2;

    /* Enable negative pumps for DSM  */
    `$INSTANCE_NAME`_PUMP_CR1_REG  |= ( `$INSTANCE_NAME`_PUMP_CR1_CLKSEL | `$INSTANCE_NAME`_PUMP_CR1_FORCE );

    /* Enable Modulator Chopping if required */
    `$INSTANCE_NAME`_DSM_CR2_REG = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR2;

    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_PWRMGR_CLK_REG |= `$INSTANCE_NAME`_ACT_PWR_CLK_EN;
        `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG |= `$INSTANCE_NAME`_STBY_PWR_CLK_EN;
    #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

    /* Enable the active and alternate active power for charge pump clock */
    `$INSTANCE_NAME`_PWRMGR_CHARGE_PUMP_CLK_REG |= `$INSTANCE_NAME`_ACT_PWR_CHARGE_PUMP_CLK_EN;
    `$INSTANCE_NAME`_STBY_PWRMGR_CHARGE_PUMP_CLK_REG |= `$INSTANCE_NAME`_STBY_PWR_CHARGE_PUMP_CLK_EN;

    #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(`$INSTANCE_NAME`_INTC_NUMBER);
        /* Enable interrupt */
        CyIntEnable(`$INSTANCE_NAME`_INTC_NUMBER);
    #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all required initialization for this component and enables
*  the power. It configure all the register the first time it is called.
*  Subsequent calls of the Start function only enable the ADC and turn
*  on the power. If multiple configurations are selected, it will
*  configure the ADC for configuration 1 by default, unless the
*  `$INSTANCE_NAME`_SelectConfiguration( ) function has been called to change
*  the default setting.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Side Effects: 
*  Enables internal interrupt.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        if(`$INSTANCE_NAME`_started == 0u)
        {
            `$INSTANCE_NAME`_Init();
        }
        `$INSTANCE_NAME`_initVar = 1u;
    }

    /* Enable the ADC */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  This function stops and powers down the ADC component and the internal
*  clock if the external clock is not selected. If an external clock is
*  used, it is up to the designer to power down the external clock it
*  required.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Stop conversions */
    `$INSTANCE_NAME`_DEC_CR_REG &= (uint8)~`$INSTANCE_NAME`_DEC_START_CONV;
    `$INSTANCE_NAME`_DEC_SR_REG |=  `$INSTANCE_NAME`_DEC_INTR_CLEAR;

    /* Disable PRES, Disable power to VCMBUF0, REFBUF0 and REFBUF1,
       enable PRES */
    `$INSTANCE_NAME`_RESET_CR4_REG |= `$INSTANCE_NAME`_IGNORE_PRESA1;
    `$INSTANCE_NAME`_RESET_CR5_REG |= `$INSTANCE_NAME`_IGNORE_PRESA2;

    `$INSTANCE_NAME`_DSM_CR17_REG &= (uint8)~(`$INSTANCE_NAME`_DSM_EN_BUF_VREF | `$INSTANCE_NAME`_DSM_EN_BUF_VCM);
    `$INSTANCE_NAME`_DSM_REF0_REG &= (uint8)~`$INSTANCE_NAME`_DSM_EN_BUF_VREF_INN;

    /* Wait for 3 microseconds. */
    CyDelayUs(`$INSTANCE_NAME`_PRES_DELAY_TIME);

    /* Enable the press circuit */
    `$INSTANCE_NAME`_RESET_CR4_REG &= (uint8)~`$INSTANCE_NAME`_IGNORE_PRESA1;
    `$INSTANCE_NAME`_RESET_CR5_REG &= (uint8)~`$INSTANCE_NAME`_IGNORE_PRESA2;

    /* Disable power to the ADC */
    `$INSTANCE_NAME`_PWRMGR_DSM_REG &= (uint8)~`$INSTANCE_NAME`_ACT_PWR_DSM_EN;

    /* Disable power to Decimator block */
    `$INSTANCE_NAME`_PWRMGR_DEC_REG &= (uint8)~`$INSTANCE_NAME`_ACT_PWR_DEC_EN;

    /* Disable alternative active power to the ADC */
    `$INSTANCE_NAME`_STBY_PWRMGR_DEC_REG &= (uint8)~`$INSTANCE_NAME`_STBY_PWR_DEC_EN;
    `$INSTANCE_NAME`_STBY_PWRMGR_DSM_REG &= (uint8)~`$INSTANCE_NAME`_STBY_PWR_DSM_EN;

   /* Disable negative pumps for DSM  */
    `$INSTANCE_NAME`_PUMP_CR1_REG &= (uint8)~(`$INSTANCE_NAME`_PUMP_CR1_CLKSEL | `$INSTANCE_NAME`_PUMP_CR1_FORCE );

    /* This is only valid if there is an internal clock */
    #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
        `$INSTANCE_NAME`_PWRMGR_CLK_REG &= (uint8)~`$INSTANCE_NAME`_ACT_PWR_CLK_EN;
        `$INSTANCE_NAME`_STBY_PWRMGR_CLK_REG &= (uint8)~`$INSTANCE_NAME`_STBY_PWR_CLK_EN;
    #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

    /* Disable Modulator Chopping */
    `$INSTANCE_NAME`_DSM_CR2_REG &= (uint8)~`$INSTANCE_NAME`_DSM_MOD_CHOP_EN;
    /* Disable power to charge pump clock */
    `$INSTANCE_NAME`_PWRMGR_CHARGE_PUMP_CLK_REG &= (uint8)~`$INSTANCE_NAME`_ACT_PWR_CHARGE_PUMP_CLK_EN;
    `$INSTANCE_NAME`_STBY_PWRMGR_CHARGE_PUMP_CLK_REG &= (uint8)~`$INSTANCE_NAME`_STBY_PWR_CHARGE_PUMP_CLK_EN;
    
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBufferGain
********************************************************************************
*
* Summary:
*  Sets input buffer gain.
*
* Parameters:
*  gain:  Two bit value to select a gain of 1, 2, 4, or 8.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetBufferGain(uint8 gain) `=ReentrantKeil($INSTANCE_NAME . "_SetBufferGain")`
{
    uint8 tmpReg;
    tmpReg = `$INSTANCE_NAME`_DSM_BUF1_REG & (uint8)~`$INSTANCE_NAME`_DSM_GAIN_MASK;
    tmpReg |= (uint8)(gain << `$INSTANCE_NAME`_DSM_GAIN_SHIFT) & `$INSTANCE_NAME`_DSM_GAIN_MASK;
    `$INSTANCE_NAME`_DSM_BUF1_REG = tmpReg;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCoherency
********************************************************************************
*
* Summary:
*  This function allows the user to change which of the ADC's 3 word
*  result will trigger a coherency unlock. The ADC's result will not be
*  updated until the set byte is read either by the ADC or DMA. 
*  By default the LSB is the coherency byte for right alignment data format. 
*  The middle or high byte is set automatically depend on left alignment 
*  configuration for DMA data transfer.
*  If DMA or if a custom API requires different byte to be read the last,
*  this API should be used to set the last byte of the ADC result that is read. 
*  If a multibyte read is performed either by DMA or the ARM processor, the
*  coherency can be set to any byte in the last word read.
*
* Parameters:
*  coherency:  Two bit value to set the coherency bit.
*           00-Coherency checking off
*           01-low byte is key byte
*           02-middle byte is the key byte
*           03-high byte is the key byte
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCoherency(uint8 coherency) `=ReentrantKeil($INSTANCE_NAME . "_SetCoherency")`
{
    uint8 tmpReg;

    tmpReg = `$INSTANCE_NAME`_DEC_COHER_REG & (uint8)~`$INSTANCE_NAME`_DEC_SAMP_KEY_MASK;
    tmpReg |= coherency & `$INSTANCE_NAME`_DEC_SAMP_KEY_MASK;
    `$INSTANCE_NAME`_DEC_COHER_REG = tmpReg;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGCOR
********************************************************************************
*
* Summary:
*  Calculates a new GCOR value and writes it into the GCOR register. 
*  The GCOR value is a 16-bit value that represents a gain of 0 to 2. 
*  The ADC result is multiplied by this value before it is placed in the ADC 
*  output registers. The numerical format for the GCOR value is:
*  0x0000 -> 0.000
*  0x8000 -> 1.000
*  0xFFFF -> 1.99997
*  When executing the function, the old GCOR value is multiplied by
*  gainAdjust and reloaded into the GCOR register.
*
* Parameters:
*  gainAdjust:  floating point value to set GCOR registers.
*
* Return:
*  uint8: 0 - if GCOR value is within the expected range.
*         1 - the correction value is outside GCOR value range of
*             0.00 to 1.9999.
*
* Side Effects:  The GVAL register is set to the amount of valid bits in the
*                GCOR  register minus one. If GVAL is 15 (0x0F), all 16 bits
*                of the GCOR registers will be valid. If for example GVAL is
*                11 (0x0B) only 12 bits will be valid. The least 4 bits will
*                be lost when the GCOR value is shifted 4 places to the right.
*
******************************************************************************/
uint8 `$INSTANCE_NAME`_SetGCOR(float32 gainAdjust) `=ReentrantKeil($INSTANCE_NAME . "_SetGCOR")`
{
    uint16 tmpReg;
    uint8 status;
    float32 tmpValue;

    tmpReg = `$INSTANCE_NAME`_gcor[`$INSTANCE_NAME`_Config - 1u].gcor;
    tmpValue = ((float32)tmpReg / (float32)`$INSTANCE_NAME`_IDEAL_GAIN_CONST);
    tmpValue = tmpValue * gainAdjust;

    if (tmpValue > 1.9999)
    {
        status = 1u;
    }
    else
    {
        tmpValue *= (float32)`$INSTANCE_NAME`_IDEAL_GAIN_CONST;
		tmpReg = (uint16)tmpValue;
        CY_SET_REG16(`$INSTANCE_NAME`_DEC_GCOR_16B_PTR, tmpReg);
        /* Update gain array to be used by SelectConfiguration() API */
       `$INSTANCE_NAME`_gcor[`$INSTANCE_NAME`_Config - 1u].gcor = tmpReg;

        status = 0u;

    }
    return(status);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadGCOR
*******************************************************************************
*
* Summary:
*  This API returns the current GCOR register value, normalized based on the
*  GVAL register settings.
*  For example, if the GCOR value is 0x0812 and the GVAL register is set to 
*  11 (0x0B) then the returned value will be shifted by for bits to the left.
*  (Actual GCOR value = 0x0812, returned value = 0x8120)
*
* Parameters:
*  None
*
* Return:
*  uint16:  Normalized GCOR value.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_ReadGCOR(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadGCOR")`
{
    uint8 gValue;
    uint16 gcorValue;

    gValue = `$INSTANCE_NAME`_DEC_GVAL_REG;
    gcorValue = CY_GET_REG16(`$INSTANCE_NAME`_DEC_GCOR_16B_PTR);

    if (gValue < `$INSTANCE_NAME`_MAX_GVAL)
    {
        gcorValue <<= `$INSTANCE_NAME`_MAX_GVAL - gValue;
    }

    return gcorValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartConvert
********************************************************************************
*
* Summary:
*  Forces the ADC to initiate a conversion. If in the "Single Sample"
*  mode, one conversion will be performed then the ADC will halt. If in
*  one of the other three conversion modes, the ADC will run
*  continuously until the ADC_Stop() or ADC_StopConvert() is called.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_StartConvert(void) `=ReentrantKeil($INSTANCE_NAME . "_StartConvert")`
{
    /* Start the conversion */
    `$INSTANCE_NAME`_DEC_CR_REG |= `$INSTANCE_NAME`_DEC_START_CONV;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StopConvert
********************************************************************************
*
* Summary:
*  Forces the ADC to stop all conversions. If the ADC is in the middle of a
*  conversion, the ADC will be reset and not provide a result for that partial
*  conversion.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_StopConvert(void) `=ReentrantKeil($INSTANCE_NAME . "_StopConvert")`
{
    /* Stop all conversions */
    `$INSTANCE_NAME`_DEC_CR_REG &= (uint8)~`$INSTANCE_NAME`_DEC_START_CONV;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsEndConversion
********************************************************************************
*
* Summary:
*  Checks the status that the most recently started conversion has completed.
*  The status is cleared by any of ADC_GetResult8(), ADC_GetResult16() or 
*  ADC_GetResult32() API.
*  This function provides the programmer with two options. In one mode this 
*  function immediately returns with the conversion status. In the other mode,
*  the function does not return (blocking) until the conversion has completed.
*
* Parameters:
*  retMode: Check conversion return mode. See the following table for options.
*   `$INSTANCE_NAME`_RETURN_STATUS -   Immediately returns conversion result
*                                      status.
*   `$INSTANCE_NAME`_WAIT_FOR_RESULT - Does not return until ADC conversion
*                                      is complete.
*
* Return:
*  If a nonzero value is returned, the last conversion has completed.
*  If the returned value is zero, the ADC is still calculating the last result.
*
* Global variables:
*  `$INSTANCE_NAME`_convDone:  Used to check whether conversion is complete
*  or not for single sample mode with resolution is above 16
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_IsEndConversion(uint8 retMode) `=ReentrantKeil($INSTANCE_NAME . "_IsEndConversion")`
{
    uint8 status;

    do
    {
        /* Check for stop convert if conversion mode is Single Sample with
        *   resolution above 16 bit
        */
        if(`$INSTANCE_NAME`_stopConversion != 0u)
        {
            status = `$INSTANCE_NAME`_convDone;
        }
        else
        {
            status = `$INSTANCE_NAME`_DEC_SR_REG & `$INSTANCE_NAME`_DEC_CONV_DONE;
        }
    }while((status != `$INSTANCE_NAME`_DEC_CONV_DONE) && (retMode == `$INSTANCE_NAME`_WAIT_FOR_RESULT));

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult8
********************************************************************************
*
* Summary:
*  This function returns the result of an 8-bit conversion. If the
*  resolution is set greater than 8-bits, the LSB of the result will be
*  returned. When the ADC is configured for 8-bit single ended mode,
*  the ADC_GetResult16() function should be used instead. This
*  function returns only signed 8-bit values. The maximum positive
*  signed 8-bit value is 127, but in singled ended 8-bit mode, the
*  maximum positive value is 255.
*
* Parameters:
*  None
*
* Return:
*  int8: The LSB of the last ADC conversion.
*
* Global variables:
*  `$INSTANCE_NAME`_convDone:  Cleared in single sample mode with resolution
*                              above 16 bits
*
*******************************************************************************/
int8 `$INSTANCE_NAME`_GetResult8( void ) `=ReentrantKeil($INSTANCE_NAME . "_GetResult8")`
{
    int8 result;
    uint8 coherency;

    /* Read active coherency configuration */
    coherency = `$INSTANCE_NAME`_DEC_COHER_REG & `$INSTANCE_NAME`_DEC_SAMP_KEY_MASK;

    result = (int8)`$INSTANCE_NAME`_DEC_SAMP_REG;

    if(coherency == `$INSTANCE_NAME`_DEC_SAMP_KEY_MID)
    {   /* Dummy read of the middle byte to unlock the coherency */
        (void)`$INSTANCE_NAME`_DEC_SAMPM_REG;
    }
    else  if(coherency == `$INSTANCE_NAME`_DEC_SAMP_KEY_HIGH)
    {   /* Dummy read of the MSB byte to unlock the coherency */
        (void)`$INSTANCE_NAME`_DEC_SAMPH_REG;
    }
    else /*No action required for other coherency */
    {
    }
    /* Clear conversion complete status in Single Sample mode with resolution above 16 bit */
    if(`$INSTANCE_NAME`_stopConversion != 0u)
    {
        `$INSTANCE_NAME`_convDone = 0u;
    }
    return (result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult16
********************************************************************************
*
* Summary:
*  Returns a 16-bit result for a conversion with a result that has a
*  resolution of 8 to 16 bits. If the resolution is set greater than 16-bits,
*  it will return the 16 least significant bits of the result. When the ADC
*  is configured for 16-bit single ended mode, the ADC_GetResult32()
*  function should be used instead. This function returns only signed
*  16-bit result, which allows a maximum positive value of 32767, not 65535.
*  This function supports different coherency settings.
*
* Parameters:
*   void
*
* Return:
*  int16:  ADC result.
*
* Global variables:
*  `$INSTANCE_NAME`_convDone:  Cleared in single sample mode with resolution
*                              above 16 bits
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_GetResult16(void) `=ReentrantKeil($INSTANCE_NAME . "_GetResult16")`
{
    uint16 result;
    uint8 coherency;

    /* Read active coherency configuration */
    coherency = `$INSTANCE_NAME`_DEC_COHER_REG & `$INSTANCE_NAME`_DEC_SAMP_KEY_MASK;

    if(coherency <= `$INSTANCE_NAME`_DEC_SAMP_KEY_LOW)
    {   /*  Use default method to read result registers i.e. LSB byte read at the end*/
        #if (CY_PSOC3)
            result = `$INSTANCE_NAME`_DEC_SAMPM_REG;
            result = (result << 8u) | `$INSTANCE_NAME`_DEC_SAMP_REG;
        #else
            result = (CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_16B_PTR));
        #endif /* CY_PSOC3 */
    }
    else /* MID or HIGH */
    {   /* Read middle byte at the end */
        #if (CY_PSOC3)
            result = (CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_16B_PTR));
        #else
            result = `$INSTANCE_NAME`_DEC_SAMP_REG;
            result |=  (uint16)((uint16)`$INSTANCE_NAME`_DEC_SAMPM_REG << 8u);
        #endif /* CY_PSOC3 */
        if(coherency == `$INSTANCE_NAME`_DEC_SAMP_KEY_HIGH)
        {   /* Dummy read of the MSB byte to unlock the coherency */
            (void)`$INSTANCE_NAME`_DEC_SAMPH_REG;
        }
    }
    /* Clear conversion complete status in Single Sample mode with resolution above 16 bit */
    if(`$INSTANCE_NAME`_stopConversion != 0u)
    {
        `$INSTANCE_NAME`_convDone = 0u;
    }

    return ((int16)result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult32
********************************************************************************
*
* Summary:
*  Returns a 32-bit result for a conversion with a result that has a
*  resolution of 8 to 20 bits.
*  This function supports different coherency settings.
*
* Parameters:
*  None
*
* Return:
*  int32: Result of the last ADC conversion.
*
* Global variables:
*  `$INSTANCE_NAME`_convDone:  Cleared in single sample mode with resolution
*                              above 16 bits
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_GetResult32(void) `=ReentrantKeil($INSTANCE_NAME . "_GetResult32")`
{
    uint32 result;
    uint8 coherency;
    #if (CY_PSOC3)
	    uint16 tmp;
    #endif /* CY_PSOC3 */

    /* Read active coherency configuration */
    coherency = `$INSTANCE_NAME`_DEC_COHER_REG & `$INSTANCE_NAME`_DEC_SAMP_KEY_MASK;

    if(coherency <= `$INSTANCE_NAME`_DEC_SAMP_KEY_LOW)
    {   /*  Use default method to read result registers i.e. LSB byte read at the end*/
        #if (CY_PSOC3)
            result = `$INSTANCE_NAME`_DEC_SAMPH_REG;
            if((result & 0x80u) != 0u)
            {   /* Sign extend */
                result |= 0xFF00u;
            }
            result = (result << 8u) | `$INSTANCE_NAME`_DEC_SAMPM_REG;
            result = (result << 8u) | `$INSTANCE_NAME`_DEC_SAMP_REG;
        #else
            result = CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMPH_16B_PTR);
            result = (result << 16u) | (CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_16B_PTR));
        #endif /* CY_PSOC3 */
    }
    else if(coherency == `$INSTANCE_NAME`_DEC_SAMP_KEY_MID)
    {   /* Read middle byte at the end */
        #if (CY_PSOC3)
            result = `$INSTANCE_NAME`_DEC_SAMPH_REG;
            if((result & 0x80u) != 0u)
            {   /* Sign extend */
                result |= 0xFF00u;
            }
            result = (result << 16u) | (CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_16B_PTR));
        #else
            result = CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMPH_16B_PTR);
            result = (result << 16u) | `$INSTANCE_NAME`_DEC_SAMP_REG;
            result |=  (uint32)((uint32)`$INSTANCE_NAME`_DEC_SAMPM_REG << 8u);
        #endif /* CY_PSOC3 */
    }
    else /*`$INSTANCE_NAME`_DEC_SAMP_KEY_HIGH */
    {
        /* Read MSB byte at the end */
        #if (CY_PSOC3)
            result = CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_16B_PTR);
			tmp = `$INSTANCE_NAME`_DEC_SAMPH_REG;
            if((tmp & 0x80u) != 0u)
            {   /* Sign extend */
                tmp |= 0xFF00u;
            }
            result |= (uint32)tmp << 16u;
        #else
            result = CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMP_16B_PTR);
            result |= (uint32)((uint32)CY_GET_REG16(`$INSTANCE_NAME`_DEC_SAMPH_16B_PTR) << 16u);
        #endif /* CY_PSOC3 */
    }
    /* Clear conversion complete status in Single Sample mode with resolution above 16 bit */
    if(`$INSTANCE_NAME`_stopConversion != 0u)
    {
        `$INSTANCE_NAME`_convDone = 0u;
    }

    return ((int32)result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOffset
********************************************************************************
*
* Summary:
*  Sets the ADC offset which is used by the functions ADC_CountsTo_uVolts, 
*  ADC_CountsTo_mVolts, and ADC_CountsTo_Volts to subtract the offset from the 
*  given reading before calculating the voltage conversion.
*
* Parameters:
*  int32:  This value is a measured value when the inputs are shorted or 
*          connected to the same input voltage.
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_Offset:  Modified to set the user provided offset. This
*  variable is used for offset calibration purpose.
*
* Side Effects:
*  Affects the `$INSTANCE_NAME`_CountsTo_Volts,
*  `$INSTANCE_NAME`_CountsTo_mVolts, `$INSTANCE_NAME`_CountsTo_uVolts functions
*  by subtracting the given offset.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOffset(int32 offset) `=ReentrantKeil($INSTANCE_NAME . "_SetOffset")`
{

    `$INSTANCE_NAME`_Offset = offset;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per volt for the voltage conversion
*  functions below. This value is set by default by the reference and
*  input range settings. It should only be used to further calibrate the
*  ADC with a known input or if an external reference is used. This
*  function may also be used to calibrate an entire signal chain, not
*  just the ADC.
*
* Parameters:
*  int32: ADC gain in counts per volt.
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  modified to set the ADC gain in counts
*   per volt.
*
* Side Effects:
*  Affects the `$INSTANCE_NAME`_CountsTo_Volts,
*  `$INSTANCE_NAME`_CountsTo_mVolts, `$INSTANCE_NAME`_CountsTo_uVolts functions
*  supplying the correct conversion between ADC counts and voltage.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetGain(int32 adcGain) `=ReentrantKeil($INSTANCE_NAME . "_SetGain")`
{
    `$INSTANCE_NAME`_CountsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Converts the ADC counts output to mVolts as a 16-bit integer. For
*  example, if the ADC measured 0.534 volts, the return value would
*  be 534 mVolts.
*
* Parameters:
*  int32: adcCounts Result from the ADC conversion.
*
* Return:
*  int16:  Result in mVolts
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  used to convert ADC counts to mVolts.
*  `$INSTANCE_NAME`_Offset:  Used as the offset while converting ADC counts
*   to mVolts.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_CountsTo_mVolts(int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_mVolts")`
{

    int16 mVolts;

    /* Convert adcCounts to the right align if left option selected */
    #if(`$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV != 0)
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config1_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV */
    #if((`$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV != 0) && (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1))
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config2_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV */
    #if((`$INSTANCE_NAME`_`$Config3_Name`_DEC_DIV != 0) && (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2))
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config3_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config3_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV */
    #if((`$INSTANCE_NAME`_`$Config4_Name`_DEC_DIV != 0) && (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3))
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config4_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config4_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV */

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_Offset;

    mVolts = (int16)(( adcCounts * `$INSTANCE_NAME`_1MV_COUNTS ) / `$INSTANCE_NAME`_CountsPerVolt) ;

    return(mVolts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_Volts
********************************************************************************
*
* Summary:
*  Converts the ADC output to Volts as a floating point number. For
*  example, if the ADC measure a voltage of 1.2345 Volts, the
*  returned result would be +1.2345 Volts.
*
* Parameters:
*  int32 adcCounts:  Result from the ADC conversion.
*
* Return:
*  float32: Result in Volts
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  used to convert to Volts.
*  `$INSTANCE_NAME`_Offset:  Used as the offset while converting ADC counts
*   to Volts.
*
*******************************************************************************/
float32 `$INSTANCE_NAME`_CountsTo_Volts(int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_Volts")`
{

    float32 Volts;

    /* Convert adcCounts to the right align if left option selected */
    #if(`$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV != 0)
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config1_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV */
    #if((`$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV != 0) && (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1))
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config2_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV */
    #if((`$INSTANCE_NAME`_`$Config3_Name`_DEC_DIV != 0) && (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2))
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config3_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config3_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV */
    #if((`$INSTANCE_NAME`_`$Config4_Name`_DEC_DIV != 0) && (`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3))
        if(`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config4_Name`)
        {
            adcCounts /= `$INSTANCE_NAME`_`$Config4_Name`_DEC_DIV;
        }
    #endif /* `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV */

    /* Subtract ADC offset */
    adcCounts -= `$INSTANCE_NAME`_Offset;

    Volts = (float32)adcCounts / (float32)`$INSTANCE_NAME`_CountsPerVolt;

    return( Volts );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to uVolts as a 32-bit integer. For example,
*  if the ADC measured -0.02345 Volts, the return value would be -23450 uVolts.
*
* Parameters:
*  int32 adcCounts: Result from the ADC conversion.
*
* Return:
*  int32:  Result in uVolts
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  used to convert ADC counts to mVolts.
*  `$INSTANCE_NAME`_Offset:  Used as the offset while converting ADC counts
*   to mVolts.
*
* Theory:
*  Care must be taken to not exceed the maximum value for a 31 bit signed
*  number in the conversion to uVolts and at the same time not lose resolution.
*
*  uVolts = ((A * adcCounts) / ((int32)`$INSTANCE_NAME`_CountsPerVolt / B));
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_CountsTo_uVolts(int32 adcCounts) `=ReentrantKeil($INSTANCE_NAME . "_CountsTo_uVolts")`
{

    int32 uVolts;
    int32 coefA;
    int32 coefB;
    uint8 resolution;

    /* Set the resolution based on the configuration */
    /* Convert adcCounts to the right align if left option selected */
    if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config1_Name`)
    {
        resolution = `$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION;
        #if(`$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV != 0)
            adcCounts /= `$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV;
        #endif /* `$INSTANCE_NAME`_`$Config1_Name`_DEC_DIV */
    }
    else if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config2_Name`)
    {
        resolution = `$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION;
        #if(`$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV != 0)
            adcCounts /= `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV;
        #endif /* `$INSTANCE_NAME`_`$Config2_Name`_DEC_DIV */
    }
    else if (`$INSTANCE_NAME`_Config == `$INSTANCE_NAME`_`$Config3_Name`)
    {
        resolution = `$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION;
        #if(`$INSTANCE_NAME`_`$Config3_Name`_DEC_DIV != 0)
            adcCounts /= `$INSTANCE_NAME`_`$Config3_Name`_DEC_DIV;
        #endif /* `$INSTANCE_NAME`_`$Config3_Name`_DEC_DIV */
    }
    else
    {
        resolution = `$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION;
        #if(`$INSTANCE_NAME`_`$Config4_Name`_DEC_DIV != 0)
            adcCounts /= `$INSTANCE_NAME`_`$Config4_Name`_DEC_DIV;
        #endif /* `$INSTANCE_NAME`_`$Config4_Name`_DEC_DIV */
    }

    switch (resolution)
    {
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_12) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_12) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_12) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_12) )
            case (uint8)`$INSTANCE_NAME`__BITS_12:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_2;
                coefB = `$INSTANCE_NAME`_DIVISOR_2;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_12 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_13) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_13) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_13) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_13) )
            case (uint8)`$INSTANCE_NAME`__BITS_13:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_4;
                coefB = `$INSTANCE_NAME`_DIVISOR_4;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_13 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_14) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_14) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_14) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_14) )
            case (uint8)`$INSTANCE_NAME`__BITS_14:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_8;
                coefB = `$INSTANCE_NAME`_DIVISOR_8;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_14 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_15) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_15) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_15) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_15) )
            case (uint8)`$INSTANCE_NAME`__BITS_15:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_16;
                coefB = `$INSTANCE_NAME`_DIVISOR_16;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_15 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_16) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_16) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_16) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_16) )
            case (uint8)`$INSTANCE_NAME`__BITS_16:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_32;
                coefB = `$INSTANCE_NAME`_DIVISOR_32;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_16 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_17) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_17) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_17) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_17) )
            case (uint8)`$INSTANCE_NAME`__BITS_17:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_64;
                coefB = `$INSTANCE_NAME`_DIVISOR_64;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_17 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_18) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_18) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_18) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_18) )
            case (uint8)`$INSTANCE_NAME`__BITS_18:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_125;
                coefB = `$INSTANCE_NAME`_DIVISOR_125;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_18 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_19) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_19) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_19) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_19) )
            case (uint8)`$INSTANCE_NAME`__BITS_19:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_250;
                coefB = `$INSTANCE_NAME`_DIVISOR_250;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_19 */    
        #if( (`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_20) || \
             (`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_20) || \
             (`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_20) || \
             (`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION == `$INSTANCE_NAME`__BITS_20) )
            case (uint8)`$INSTANCE_NAME`__BITS_20:
                coefA = `$INSTANCE_NAME`_1UV_COUNTS / `$INSTANCE_NAME`_DIVISOR_500;
                coefB = `$INSTANCE_NAME`_DIVISOR_500;
                break;
        #endif /* `$INSTANCE_NAME`__BITS_20 */    
        default:    /* resolution < 12 */
            /* 11 bits ADC + 2^20(1048576) = 31 bits */
            coefA = `$INSTANCE_NAME`_1UV_COUNTS;
            coefB = `$INSTANCE_NAME`_DIVISOR_1;
            break;
    }
    coefB = `$INSTANCE_NAME`_CountsPerVolt / coefB;
    uVolts = ((coefA * adcCounts) / coefB) - ((coefA * `$INSTANCE_NAME`_Offset) / coefB);

    return( uVolts );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitConfig(uint8 config)
********************************************************************************
*
* Summary:
*  Initializes all registers based on customizer settings
*
* Parameters:
*   void
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_CountsPerVolt:  Used to set the default counts per volt.
*
* Side Effects: Rewrites the coherency set by `$INSTANCE_NAME`_SetCoherency()
*   API to the default value.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_InitConfig(uint8 config) `=ReentrantKeil($INSTANCE_NAME . "_InitConfig")`
{
    `$INSTANCE_NAME`_stopConversion = 0u;

    if (config == 1u)
    {
        /* `$Comment_Config1` */
        `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config1_Name`_DEC_CR;
        `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config1_Name`_DEC_SHIFT1;
        `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config1_Name`_DEC_SHIFT2;
        `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR2;
        `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR2H;
        `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DEC_DR1;
        `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCOR;
        `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCORM;
        `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config1_Name`_DEC_OCORH;
        `$INSTANCE_NAME`_DEC_COHER_REG   = `$INSTANCE_NAME`_`$Config1_Name`_DEC_COHER;

        `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR4;
        `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR5;
        `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR6;
        `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR7;
        `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR10;
        `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR11;
        `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR12;
        `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR14;
        `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR15;
        `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR16;
        `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_CR17;
        /* Set DSM_REF0_REG by disabling and enabling the PRESS circuit */
        `$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config1_Name`_DSM_REF0);
        `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF2;
        `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_REF3;

        `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF0;
        `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF1;
        `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF2;
        `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config1_Name`_DSM_BUF3;

        /* To select either Vssa or Vref to -ve input of DSM depending on
        *  the input  range selected.
        */
        #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
            #if (`$INSTANCE_NAME`_`$Config1_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                `$INSTANCE_NAME`_AMux_Select(1u);
            #else
                `$INSTANCE_NAME`_AMux_Select(0u);
            #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
        #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */

        /* Set the Conversion stop if resolution is above 16 bit and conversion
        *   mode is Single sample
        */
        #if(`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION > 16 && \
            `$INSTANCE_NAME`_`$Config1_Name`_CONV_MODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
            `$INSTANCE_NAME`_stopConversion = 1u;
        #endif /* Single sample with resolution above 16 bits. */

        `$INSTANCE_NAME`_CountsPerVolt = (int32)`$INSTANCE_NAME`_`$Config1_Name`_COUNTS_PER_VOLT;

        `$INSTANCE_NAME`_Ext_CP_Clk_SetDividerRegister(`$INSTANCE_NAME`_`$Config1_Name`_CP_CLK_DIVIDER, 1u);

        /* This is only valid if there is an internal clock */
        #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
            `$INSTANCE_NAME`_theACLK_SetDividerRegister(`$INSTANCE_NAME`_`$Config1_Name`_ADC_CLK_DIVIDER, 1u);
        #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

        #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
            /* Set interrupt vector */
            (void)CyIntSetVector(`$INSTANCE_NAME`_INTC_NUMBER, &`$INSTANCE_NAME`_ISR1);
        #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */
    }

    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1)
        if(config == 2u)
        {
            /* `$Comment_Config2` */
            `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config2_Name`_DEC_CR;
            `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config2_Name`_DEC_SHIFT1;
            `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config2_Name`_DEC_SHIFT2;
            `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR2;
            `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR2H;
            `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DEC_DR1;
            `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCOR;
            `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCORM;
            `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config2_Name`_DEC_OCORH;
            `$INSTANCE_NAME`_DEC_COHER_REG   = `$INSTANCE_NAME`_`$Config2_Name`_DEC_COHER;

            `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR4;
            `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR5;
            `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR6;
            `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR7;
            `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR10;
            `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR11;
            `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR12;
            `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR14;
            `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR15;
            `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR16;
            `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_CR17;
            /* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
            `$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config2_Name`_DSM_REF0);
            `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_REF2;
            `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_REF3;

            `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF0;
            `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF1;
            `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF2;
            `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config2_Name`_DSM_BUF3;

            /* To select either Vssa or Vref to -ve input of DSM depending on
            *  the input range selected.
            */

            #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
                #if (`$INSTANCE_NAME`_`$Config2_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                    `$INSTANCE_NAME`_AMux_Select(1u);
                #else
                    `$INSTANCE_NAME`_AMux_Select(0u);
                #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
            #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */

            /* Set the Conversion stop if resolution is above 16 bit and
            *   conversion mode is Single sample
            */
            #if(`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION > 16 && \
                `$INSTANCE_NAME`_`$Config2_Name`_CONV_MODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
                `$INSTANCE_NAME`_stopConversion = 1u;
            #endif /* Single sample with resolution above 16 bits. */

            `$INSTANCE_NAME`_CountsPerVolt = (int32)`$INSTANCE_NAME`_`$Config2_Name`_COUNTS_PER_VOLT;

            `$INSTANCE_NAME`_Ext_CP_Clk_SetDividerRegister(`$INSTANCE_NAME`_`$Config2_Name`_CP_CLK_DIVIDER, 1u);

            /* This is only valid if there is an internal clock */
            #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
                `$INSTANCE_NAME`_theACLK_SetDividerRegister(`$INSTANCE_NAME`_`$Config2_Name`_ADC_CLK_DIVIDER, 1u);
            #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

            #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
                /* Set interrupt vector */
                (void)CyIntSetVector(`$INSTANCE_NAME`_INTC_NUMBER, &`$INSTANCE_NAME`_ISR2);
            #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */
        }
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 1 */

    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2)
        if(config == 3u)
        {
            /* `$Comment_Config3` */
            `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config3_Name`_DEC_CR;
            `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config3_Name`_DEC_SHIFT1;
            `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config3_Name`_DEC_SHIFT2;
            `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR2;
            `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR2H;
            `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DEC_DR1;
            `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCOR;
            `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCORM;
            `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config3_Name`_DEC_OCORH;
            `$INSTANCE_NAME`_DEC_COHER_REG   = `$INSTANCE_NAME`_`$Config3_Name`_DEC_COHER;

            `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR4;
            `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR5;
            `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR6;
            `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR7;
            `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR10;
            `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR11;
            `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR12;
            `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR14;
            `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR15;
            `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR16;
            `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_CR17;
            /* Set DSM_REF0_REG by disabling and enabling the PRESS circuit */
            `$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config3_Name`_DSM_REF0);
            `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_REF2;
            `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_REF3;

            `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF0;
            `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF1;
            `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF2;
            `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config3_Name`_DSM_BUF3;

            /* To select either Vssa or Vref to -ve input of DSM depending on
            *  the input range selected.
            */
            #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
                #if (`$INSTANCE_NAME`_`$Config3_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                    `$INSTANCE_NAME`_AMux_Select(1u);
                #else
                    `$INSTANCE_NAME`_AMux_Select(0u);
                #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
            #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */

            /* Set the Conversion stop if resolution is above 16 bit and
               conversion  mode is Single sample */
            #if(`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION > 16 && \
                `$INSTANCE_NAME`_`$Config3_Name`_CONV_MODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
                `$INSTANCE_NAME`_stopConversion = 1u;
            #endif /* Single sample with resolution above 16 bits */

            `$INSTANCE_NAME`_CountsPerVolt = (int32)`$INSTANCE_NAME`_`$Config3_Name`_COUNTS_PER_VOLT;

            `$INSTANCE_NAME`_Ext_CP_Clk_SetDividerRegister(`$INSTANCE_NAME`_`$Config3_Name`_CP_CLK_DIVIDER, 1u);

            /* This is only valid if there is an internal clock */
            #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
                `$INSTANCE_NAME`_theACLK_SetDividerRegister(`$INSTANCE_NAME`_`$Config3_Name`_ADC_CLK_DIVIDER, 1u);
            #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

            #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
                /* Set interrupt vector */
                (void)CyIntSetVector(`$INSTANCE_NAME`_INTC_NUMBER, &`$INSTANCE_NAME`_ISR3);
            #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */
        }
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 2 */

    #if(`$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3)
        if (config == 4u)
        {
            /* `$Comment_Config4` */
            `$INSTANCE_NAME`_DEC_CR_REG      = `$INSTANCE_NAME`_`$Config4_Name`_DEC_CR;
            `$INSTANCE_NAME`_DEC_SHIFT1_REG  = `$INSTANCE_NAME`_`$Config4_Name`_DEC_SHIFT1;
            `$INSTANCE_NAME`_DEC_SHIFT2_REG  = `$INSTANCE_NAME`_`$Config4_Name`_DEC_SHIFT2;
            `$INSTANCE_NAME`_DEC_DR2_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR2;
            `$INSTANCE_NAME`_DEC_DR2H_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR2H;
            `$INSTANCE_NAME`_DEC_DR1_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DEC_DR1;
            `$INSTANCE_NAME`_DEC_OCOR_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCOR;
            `$INSTANCE_NAME`_DEC_OCORM_REG   = `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCORM;
            `$INSTANCE_NAME`_DEC_OCORH_REG   = `$INSTANCE_NAME`_`$Config4_Name`_DEC_OCORH;
            `$INSTANCE_NAME`_DEC_COHER_REG   = `$INSTANCE_NAME`_`$Config4_Name`_DEC_COHER;

            `$INSTANCE_NAME`_DSM_CR4_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR4;
            `$INSTANCE_NAME`_DSM_CR5_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR5;
            `$INSTANCE_NAME`_DSM_CR6_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR6;
            `$INSTANCE_NAME`_DSM_CR7_REG     = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR7;
            `$INSTANCE_NAME`_DSM_CR10_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR10;
            `$INSTANCE_NAME`_DSM_CR11_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR11;
            `$INSTANCE_NAME`_DSM_CR12_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR12;
            `$INSTANCE_NAME`_DSM_CR14_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR14;
            `$INSTANCE_NAME`_DSM_CR15_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR15;
            `$INSTANCE_NAME`_DSM_CR16_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR16;
            `$INSTANCE_NAME`_DSM_CR17_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_CR17;
            /* Set DSM_REF0_REG by disabling and enabling the PRESS circuit */
            `$INSTANCE_NAME`_SetDSMRef0Reg(`$INSTANCE_NAME`_`$Config4_Name`_DSM_REF0);
            `$INSTANCE_NAME`_DSM_REF2_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_REF2;
            `$INSTANCE_NAME`_DSM_REF3_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_REF3;

            `$INSTANCE_NAME`_DSM_BUF0_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF0;
            `$INSTANCE_NAME`_DSM_BUF1_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF1;
            `$INSTANCE_NAME`_DSM_BUF2_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF2;
            `$INSTANCE_NAME`_DSM_BUF3_REG    = `$INSTANCE_NAME`_`$Config4_Name`_DSM_BUF3;

            /* To select either Vssa or Vref to -ve input of DSM depending on
            *  the input range selected.
            */
            #if(`$INSTANCE_NAME`_DEFAULT_INPUT_MODE)
                #if (`$INSTANCE_NAME`_`$Config4_Name`_INPUT_RANGE == `$INSTANCE_NAME`_IR_VSSA_TO_2VREF)
                    `$INSTANCE_NAME`_AMux_Select(1u);
                #else
                    `$INSTANCE_NAME`_AMux_Select(0u);
                #endif /* `$INSTANCE_NAME`_IR_VSSA_TO_2VREF) */
            #endif /* `$INSTANCE_NAME`_DEFAULT_INPUT_MODE */

            /* Set the Conversion stop if resolution is above 16 bit and
               conversion mode is Single sample */
            #if(`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION > 16 && \
                `$INSTANCE_NAME`_`$Config4_Name`_CONV_MODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
                `$INSTANCE_NAME`_stopConversion = 1u;
            #endif /* Single sample with resolution above 16 bits */

            `$INSTANCE_NAME`_CountsPerVolt = (int32)`$INSTANCE_NAME`_`$Config4_Name`_COUNTS_PER_VOLT;

            `$INSTANCE_NAME`_Ext_CP_Clk_SetDividerRegister(`$INSTANCE_NAME`_`$Config4_Name`_CP_CLK_DIVIDER, 1u);

            /* This is only valid if there is an internal clock */
            #if(`$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK)
                `$INSTANCE_NAME`_theACLK_SetDividerRegister(`$INSTANCE_NAME`_`$Config4_Name`_ADC_CLK_DIVIDER, 1u);
            #endif /* `$INSTANCE_NAME`_DEFAULT_INTERNAL_CLK */

            #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
                /* Set interrupt vector */
                (void)CyIntSetVector(`$INSTANCE_NAME`_INTC_NUMBER, &`$INSTANCE_NAME`_ISR4);
            #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */
        }
    #endif /* `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS > 3 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SelectCofiguration
********************************************************************************
*
* Summary:
*  Sets one of up to four ADC configurations. Before setting the new
*  configuration, the ADC is stopped and powered down. After setting
*  the new configuration, the ADC can be powered and conversion
*  can be restarted depending up on the value of second parameter
*  restart. If the value of this parameter is 1, then ADC will be
*  restarted. If this value is zero, then user must call `$INSTANCE_NAME`_Start
*  and `$INSTANCE_NAME`_StartConvert() to restart the conversion.
*
* Parameters:
*  config:  configuration user wants to select.
*           Valid range: 1..4
*  restart:  Restart option. 1 means start the ADC and restart the conversion.
*                            0 means do not start the ADC and conversion.
*
* Return:
*  None
*
* Side Effects: 
*  Enables internal interrupt.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SelectConfiguration(uint8 config, uint8 restart)
                                              `=ReentrantKeil($INSTANCE_NAME . "_SelectConfiguration")`
{
    /* Check whether the configuration number is valid or not */
    if((config > 0u) && (config <= `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS))
    {
        /* Set the flag to ensure Start() API doesn't override the 
		*  selected configuration
		*/
        if(`$INSTANCE_NAME`_initVar == 0u)
        {
            `$INSTANCE_NAME`_started = 1u;
        }

        /* Update the config flag */
        `$INSTANCE_NAME`_Config = config;

        /* Stop the ADC  */
        `$INSTANCE_NAME`_Stop();

        /* Set the  ADC registers based on the configuration */
        `$INSTANCE_NAME`_InitConfig(config);

        /* Compensate the gain */
        `$INSTANCE_NAME`_DEC_GVAL_REG = `$INSTANCE_NAME`_gcor[config - 1u].gval;
        CY_SET_REG16(`$INSTANCE_NAME`_DEC_GCOR_16B_PTR, `$INSTANCE_NAME`_gcor[config - 1u].gcor);

        if(restart == 1u)
        {
            /* Restart the ADC */
            `$INSTANCE_NAME`_Start();

            /* Restart the ADC conversion */
            `$INSTANCE_NAME`_StartConvert();
        }
    }
    else
    {
        /* Halt CPU in debug mode if config is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GainCompensation
********************************************************************************
*
* Summary:
*  This API calculates the trim value and then store this to gcor structure.
*
* Parameters:
*  inputRange:  input range for which trim value is to be calculated.
*  IdealDecGain:  Ideal Decimator gain for the selected resolution and
*                 conversion  mode.
*  IdealOddDecGain:  Ideal odd decimation gain for the selected resolution and
                     conversion mode.
*  resolution:  Resolution to select the proper flash location for trim value.
*  config:      Specifies the configuration number
*               Valid range: 1..4
*
* Return:
*  None
*
*******************************************************************************/
static void `$INSTANCE_NAME`_GainCompensation(uint8 inputRange, uint16 idealDecGain, uint16 idealOddDecGain,
                              uint8 resolution, uint8 config) `=ReentrantKeil($INSTANCE_NAME . "_GainCompensation")`
{
    int8 flash;
	int32 normalised;
	uint16 gcorValue;
    uint32 gcorTmp;

    if((config > 0u) && (config <= `$INSTANCE_NAME`_DEFAULT_NUM_CONFIGS))
    {
        switch(inputRange)
        {
            case `$INSTANCE_NAME`_IR_VNEG_VREF_DIFF:
            case `$INSTANCE_NAME`_IR_VSSA_TO_2VREF:
                /* Normalize the flash Value */
                if(resolution > 15u)
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_16_20;
                }
                else
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_DIFF_8_15;
                }
                break;

            case `$INSTANCE_NAME`_IR_VNEG_VREF_2_DIFF:
                /* Normalize the flash Value */
                if(resolution > 15u)
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_16_20;
                }
                else
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_2_DIFF_8_15;
                }
                break;

            case `$INSTANCE_NAME`_IR_VNEG_VREF_4_DIFF:
                /* Normalize the flash Value */
                if(resolution > 15u)
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_16_20;
                }
                else
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_4_DIFF_8_15;
                }
                break;

            case `$INSTANCE_NAME`_IR_VNEG_VREF_16_DIFF:
                /* Normalize the flash Value */
                if(resolution > 15u)
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_16_20;
                }
                else
                {
                    flash = `$INSTANCE_NAME`_DEC_TRIM_VREF_16_DIFF_8_15;
                }
                break;

            default:
                flash = 0;
                break;
        }

        /* Add two values */
		normalised = (int32)idealDecGain + ((int32)flash * 32);
        gcorTmp = (uint32)normalised * (uint32)idealOddDecGain;
        gcorValue = (uint16)(gcorTmp / `$INSTANCE_NAME`_IDEAL_GAIN_CONST);

        if (resolution < (`$INSTANCE_NAME`_MAX_GVAL - 1u))
        {
            gcorValue = (gcorValue >> (`$INSTANCE_NAME`_MAX_GVAL - (resolution + 1u)));
            `$INSTANCE_NAME`_gcor[config - 1u].gval = (resolution + 1u);
        }
        else
        {
            /* Use all 16 bits */
            `$INSTANCE_NAME`_gcor[config - 1u].gval = `$INSTANCE_NAME`_MAX_GVAL;
        }

        /* Save the gain correction register value */
        `$INSTANCE_NAME`_gcor[config - 1u].gcor = gcorValue;
    }
    else
    {
        /* Halt CPU in debug mode if config is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDSMRef0Reg(uint8)
******************************************************************************
*
* Summary:
*  This API sets the DSM_REF0 register. This is written for internal use.
*
* Parameters:
*  value:  Value to be written to DSM_REF0 register.
*
* Return:
*  None
*
******************************************************************************/
static void `$INSTANCE_NAME`_SetDSMRef0Reg(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_SetDSMRef0Reg")`
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and REFBUF1, enable PRES */
    `$INSTANCE_NAME`_RESET_CR4_REG |= (`$INSTANCE_NAME`_IGNORE_PRESA1 | `$INSTANCE_NAME`_IGNORE_PRESD1);
    `$INSTANCE_NAME`_RESET_CR5_REG |= (`$INSTANCE_NAME`_IGNORE_PRESA2 | `$INSTANCE_NAME`_IGNORE_PRESD2);
    `$INSTANCE_NAME`_DSM_REF0_REG = value;

    /* Wait for 3 microseconds */
    CyDelayUs(`$INSTANCE_NAME`_PRES_DELAY_TIME);
    /* Enable the press circuit */
    `$INSTANCE_NAME`_RESET_CR4_REG &= (uint8)~(`$INSTANCE_NAME`_IGNORE_PRESA1 | `$INSTANCE_NAME`_IGNORE_PRESD1);
    `$INSTANCE_NAME`_RESET_CR5_REG &= (uint8)~(`$INSTANCE_NAME`_IGNORE_PRESA2 | `$INSTANCE_NAME`_IGNORE_PRESD2);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read8
********************************************************************************
*
* Summary:
*  This function simplifies getting results from the ADC when only a
*  single reading is required. When called, it will start ADC
*  conversions, wait for the conversion to be complete, stop ADC
*  conversion and return the result. This is a blocking function and will
*  not return until the result is ready.
*
* Parameters:
*  None
*
* Return:
*  int8:  ADC result.
*
*******************************************************************************/
int8 `$INSTANCE_NAME`_Read8(void) `=ReentrantKeil($INSTANCE_NAME . "_Read8")`
{
    int8 result;

    /* Clear pending conversion done status */
    `$INSTANCE_NAME`_DEC_SR_REG |= `$INSTANCE_NAME`_DEC_INTR_CLEAR;
    `$INSTANCE_NAME`_StartConvert();
    (void)`$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT);
     result = `$INSTANCE_NAME`_GetResult8();
    `$INSTANCE_NAME`_StopConvert();
    
     return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read16
********************************************************************************
*
* Summary:
*  This function simplifies getting results from the ADC when only a
*  single reading is required. When called, it will start ADC
*  conversions, wait for the conversion to be complete, stop ADC
*  conversion and return the result. This is a blocking function and will
*  not return until the result is ready.
*
* Parameters:
*   void
*
* Return:
*  int16:  ADC result.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_Read16(void) `=ReentrantKeil($INSTANCE_NAME . "_Read16")`
{
    int16 result;

    /* Clear pending conversion done status */
    `$INSTANCE_NAME`_DEC_SR_REG |= `$INSTANCE_NAME`_DEC_INTR_CLEAR;
    `$INSTANCE_NAME`_StartConvert();
    (void)`$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT);
     result = `$INSTANCE_NAME`_GetResult16();
    `$INSTANCE_NAME`_StopConvert();
    
     return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read32
********************************************************************************
*
* Summary:
*  This function simplifies getting results from the ADC when only a
*  single reading is required. When called, it will start ADC
*  conversions, wait for the conversion to be complete, stop ADC
*  conversion and return the result. This is a blocking function and will
*  not return until the result is ready.
*
* Parameters:
*  None
*
* Return:
*  int32: ADC result.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_Read32(void) `=ReentrantKeil($INSTANCE_NAME . "_Read32")`
{
    int32 result;
    
    /* Clear pending conversion done status */
    `$INSTANCE_NAME`_DEC_SR_REG |= `$INSTANCE_NAME`_DEC_INTR_CLEAR;
    `$INSTANCE_NAME`_StartConvert();
    (void)`$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT);
     result = `$INSTANCE_NAME`_GetResult32();
    `$INSTANCE_NAME`_StopConvert();
    
     return(result);
}


/* [] END OF FILE */
