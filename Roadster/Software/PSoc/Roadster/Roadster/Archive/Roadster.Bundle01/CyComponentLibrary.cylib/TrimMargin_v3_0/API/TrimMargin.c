/*******************************************************************************
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides all API functionality of the TrimMargin component
*
********************************************************************************
* \copyright
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "`$INSTANCE_NAME`.h"
`$PWMInclude`

/***************************************
*   Macro helpers to simplify coding
***************************************/

/* Initializes run-time configuration in SRAM with initial values
* stored in Flash. This uses memcpy which is compiler dependent in its
* implementation.
*/
#if(CY_PSOC3)
    #define SetConfig(wrk, cfg)    (void)memcpy((void *)(wrk), (void *)(uint32)(cfg), (int16)sizeof(wrk))
#else
    #define SetConfig(wrk, cfg)    (void)memcpy((void *)(wrk), (const void *)(cfg), sizeof(wrk))
#endif /* CY_PSOC3 */

/* Checks the polarity of the voltage adjust feedback for the given power
* converter.
*/
#define IsFeedbackNegative(converterMask)   ((`$INSTANCE_NAME`_FEEDBACK & (converterMask)) != `=$NumConverters > 16 ? "0ul" : "0u"`)
#define IsFeedbackPositive(converterMask)   ((`$INSTANCE_NAME`_FEEDBACK & (converterMask)) == `=$NumConverters > 16 ? "0ul" : "0u"`)


/***************************************
*   Internal definitions
***************************************/

/* Active trim process status */
#define TRIM_SUCCESS     0u
#define TRIM_ALERT       1u
#define TRIM_NONE        2u

/* The control coefficients are scaled by 2^12=4096 (the scaling factor is set 
* as powers of 2 for efficient processing). Thus, the controller includes the 
* output gain to scale the result to the PWM resolution. 
*/
#define POST_GAIN       12u

/* This is the output saturation for the PWM. The limit must account for the 
* post gain stage (i.e. a post gain of 2^12) combined with an PWM output limit.
* The PWM limit depends on the PWM resolution.
*/
#define OUTPUT_SAT_L    0
#define OUTPUT_SAT_H    ((int32)((uint32)`$INSTANCE_NAME`_PWM_MAX << POST_GAIN))


/***************************************
*  Customizer Generated Constants
***************************************/

/** Initial margin low output voltage */
`$VMarginLowArray`;

/** Initial margin high output voltage */
`$VMarginHighArray`;

/** Nominal output voltage */
`$VNominalArray`;

/**
* Pre-calculated PWM duty cycle AFTER power converter is enabled.
* D = (Vmax-Vnom) / (Vmax-Vmin) x (2^PWMResolution - 1)
*/
`$PWMNomArray`;

/**
* Coefficients for calculation pre-run duty cycle from duty cycle.
* Pre-run duty cycle is used BEFORE power converter is enabled to 
* achieve Vadj voltage with the assumption that R1 is grounded
* in parallel with R2.
* PRE_COEF = (R4 / ( R3 + (R2||R1)) + 1) x 10^3
*/
`$preCoefArray`;

/**
* Pre-calculated PWM duty cycle BEFORE power converter is enabled.
* D_PRE_RUN = D x PRE_COEF / 10^3
*/
`$PWMPreArray`;

/**
* Pre-calculated output voltage movement(in mV) per half of PWM count.
* VDELTA = (VMAX - VMIN) / (2^PWMResolution - 1)
*/
#if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL)
`$vDeltaArray`;
#endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL */

/**
* Pre-calculated PWM duty cycle for margin low voltage.
* D_MARGIN_LOW = (VMAX - VMARGIN_LOW) / (VMAX - VMIN) x (2^PWMResolution - 1)
*/
`$pwmVMarginLowArray`;

/**
* Pre-calculated PWM duty cycle for margin high voltage.
* D_MARGIN_HIGH = (VMAX - VMARGIN_HIGH) / (VMAX - VMIN) x (2^PWMResolution - 1)
*/
`$pwmVMarginHighArray`;

/**
* Pre-calculated PWM duty cycle for startup voltage.
* D_STARTUP = (VMAX - VSTARTUP) / (VMAX-VMIN) x (2^PWMResolution - 1)
*/
`$PWMStartupArray`;

/**
* Pre-calculated PWM duty cycle for startup voltage BEFORE power converter is enabled.
* D_STARTUP_PRE_RUN = D_STARTUP * PRE_COEF / 10^3;
*/
`$PWMStartupPreArray`;

/** Maximum converter output voltage */
`$VMaxArray`;

/** Minimum converter output voltage */
`$VMinArray`;

`$PWMCompareArray`;


/***************************************
*       Global variables
***************************************/

/** Indicates whether the component has been initialized. It is initialized
* to zero and set to one the first time `$INSTANCE_NAME`_Start() is called.
* This allows a component restart without re-initialization in all
* subsequent calls to the `$INSTANCE_NAME`_Start() routine.
*/
uint8 `$INSTANCE_NAME`_initVar = 0u;

/** The bit mask indicating which PWMs are generating an alert */
`$ConverterMaskType` `$INSTANCE_NAME`_alertSource;

/** This is an update rate for PWM duty cycle when calling
* `$INSTANCE_NAME`_ActiveTrim() API for incremental controller type.
*/
uint8 `$INSTANCE_NAME`_trimCycleCount;

/** 
* The PWM duty cycle for nominal output voltage. Initialized with customizer
* settings in `$INSTANCE_NAME`_Init(). Recalculated in SetNominalVoltage()
* when a new value is set. Used by Nominal() to set PWM for the open loop margin.
*/
`$DutyCycleType` `$INSTANCE_NAME`_vNominalDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/** 
* The PWM duty cycle for the margin low output voltage. Initialized with customizer 
* settings in `$INSTANCE_NAME`_Init(). Recalculated in SetMarginLowVoltage()
* when a new value is set. Used by MarginLow() to set PWM for the open loop margin.
*/
`$DutyCycleType` `$INSTANCE_NAME`_vMarginLowDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/** 
* The PWM duty cycle for the margin high output voltage. Initialized with customizer 
* settings in `$INSTANCE_NAME`_Init(). Recalculated in SetMarginHighVoltage()
* when a new value is set. Used by MarginHigh() to set PWM for the open loop margin.
*/
`$DutyCycleType` `$INSTANCE_NAME`_vMarginHighDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/** Nominal output voltage */
uint16 `$INSTANCE_NAME`_vNom[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/** Margin low output voltage */
uint16 `$INSTANCE_NAME`_vMarginLow[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/** Margin high output voltage */
uint16 `$INSTANCE_NAME`_vMarginHigh[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

#if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL)
/* Internal PWM duty cycle for active trimming with integral controller */
static int32 integralControlOut[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/* Set in the SetDutyCycle() API to indicate that the duty cycle has been
* changed for a particular power converter. Used in the TrimActive() API
* to skip the current trim cycle if there was a change in the duty cycle
* for a specified power converter.
*/
static `$ConverterMaskType` dutyCycleChanged = 0u;
#else
/* Error history for incremental controller */
`$INSTANCE_NAME`_TRIMCTL_STRUCT `$INSTANCE_NAME`_trimCtl[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL */


/***************************************
*   Internal Functions Prototypes
***************************************/ 

#if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL)
static uint8 `$INSTANCE_NAME`_IntegralControllerProcess(uint8 converterNum, int16 error) `=ReentrantKeil($INSTANCE_NAME . "_IntegralControllerProcess")`;
#else
static uint8 `$INSTANCE_NAME`_IncrementalControllerProcess(uint8 converterNum, int16 error) `=ReentrantKeil($INSTANCE_NAME . "_IncrementalControllerProcess")`;
#endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* \brief Starts the component operation.
*
*  Calls the `$INSTANCE_NAME`_Init() API if the component has not been initialized
*  before. Calls `$INSTANCE_NAME`_Enable() API.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_initVar
*
* \reentrant No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* \brief Initializes component's parameters to those set in the customizer.
*
*  It is not necessary to call `$INSTANCE_NAME`_Init() because the `$INSTANCE_NAME`_Start()
*  routine calls this function, which is the preferred method to begin the component
*  operation. PWM duty cycles are set to pre-run values to achieve the
*  startup voltage target assuming that the power converters are not yet turned
*  on (disabled).
*
* \globalvars
*  \ref `$INSTANCE_NAME`_vNom <br>
*  \ref `$INSTANCE_NAME`_vMarginLow <br>
*  \ref `$INSTANCE_NAME`_vMarginHigh <br>
*  \ref `$INSTANCE_NAME`_vNominalDutyCycle <br>
*  \ref `$INSTANCE_NAME`_vMarginLowDutyCycle <br>
*  \ref `$INSTANCE_NAME`_vMarginHighDutyCycle
*
* \reentrant No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    uint8 idx;
    #if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL)
        uint32 scaledDutyCycle;
    #endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL */

    /* Initialize run-time configuration variables with customizer settings */
    SetConfig(`$INSTANCE_NAME`_vNom, `$INSTANCE_NAME`_VNOMINAL);
    SetConfig(`$INSTANCE_NAME`_vMarginLow, `$INSTANCE_NAME`_VMARGIN_LOW);
    SetConfig(`$INSTANCE_NAME`_vMarginHigh, `$INSTANCE_NAME`_VMARGIN_HIGH);
    SetConfig(`$INSTANCE_NAME`_vNominalDutyCycle, `$INSTANCE_NAME`_VNOMINAL_DUTYCYCLE);
    SetConfig(`$INSTANCE_NAME`_vMarginLowDutyCycle, `$INSTANCE_NAME`_VMARGIN_LOW_DUTYCYCLE);
    SetConfig(`$INSTANCE_NAME`_vMarginHighDutyCycle, `$INSTANCE_NAME`_VMARGIN_HIGH_DUTYCYCLE);
`$PWMInit`
    /* Set PWM Prerun duty-cycle for Startup voltage */
    for (idx = 0u; idx < `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS; ++idx)
    {
        CY_SET_REG`$PWMRegSize`(pwmCompare[idx], `$INSTANCE_NAME`_STARTUP_PRE_RUN_DUTYCYCLE[idx]);
        
        /* Set integral controller output for Startup voltage */
        #if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL)
            scaledDutyCycle = (uint32)`$INSTANCE_NAME`_STARTUP_PRE_RUN_DUTYCYCLE[idx] << POST_GAIN;
            integralControlOut[idx] = (int32)scaledDutyCycle;
        #endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL */
    }

    /* By default the trim process uses slow cycle count value */
    `$INSTANCE_NAME`_SetTrimCycleCount(`$INSTANCE_NAME`_CYCLE_SLOW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* \brief Enables the generation of PWMs outputs.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    #if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL)
        /* Reset the history gathered by ActiveTrim() calls for incremental controller
        * method. This uses memset which is compiler dependent in its implementation.
        */
        #if(CY_PSOC3)
            (void)memset((void *)`$INSTANCE_NAME`_trimCtl, '\0', (int16)sizeof(`$INSTANCE_NAME`_trimCtl));
        #else
            (void)memset((void *)`$INSTANCE_NAME`_trimCtl, 0, sizeof(`$INSTANCE_NAME`_trimCtl));
        #endif /* CY_PSOC3 */
    #endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL */

    /* Enable PWMs */
    #if (`$INSTANCE_NAME`_UDB_PWM)
        `$INSTANCE_NAME`_CTRL_REG |= `$INSTANCE_NAME`_CTRL_ENABLE;
    #endif /* `$INSTANCE_NAME`_UDB_PWM */
`$PWMEnable`
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* \brief 
*  Disables the component. Stops the PWMs.
*
*  trim[x] outputs halted in an undefined state. Use the pin-specific API 
*  PinName_SetDriveMode(PIN_DM_DIG_HIZ) to change the drive mode of the
*  connected to these outputs pins to High Impedance Digital.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    /* Disable PWMs */
    #if (`$INSTANCE_NAME`_UDB_PWM)
        `$INSTANCE_NAME`_CTRL_REG &= (uint8)~`$INSTANCE_NAME`_CTRL_ENABLE;
    #endif /* `$INSTANCE_NAME`_UDB_PWM */
`$PWMStop`
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConvertVoltageToDutyCycle
****************************************************************************//**
*
* \brief
*  Returns the PWM duty cycle required to achieve the desired voltage on
*  the selected power converter.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \param marginHiVoltage
*  Specifies the desired power converter output voltage in mV. 
*  Valid range: 1..65535.
*
* \return PWM duty cycle required to achieve the desired voltage. Return type
*  (uint8/uint16) depends on the PWM resolution. 
*
* \globalvars
*  \ref `$INSTANCE_NAME`_VMAX <br>
*  \ref `$INSTANCE_NAME`_VMIN

*
*******************************************************************************/
`$DutyCycleType` `$INSTANCE_NAME`_ConvertVoltageToDutyCycle(uint8 converterNum, uint16 desiredVoltage) `=ReentrantKeil($INSTANCE_NAME . "_ConvertVoltageToDutyCycle")`
{
    /* This defines the range for all converters, i.e. the difference
    * between the maximum and minimum voltage limits.
    */
    `$vRangeArray`;
    uint16 dutyCycle;
    `$ConverterMaskType` converterMask;

    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    /* Convert converter number to array index and bit mask */
    --converterNum;

    /* Calculate converter bit mask */
    converterMask = (`$ConverterMaskType`)(((`$ConverterMaskType`)1u) << converterNum);

    /* Saturate the output within the converter dynamic range */
    if(desiredVoltage > `$INSTANCE_NAME`_VMAX[converterNum])
    {
        desiredVoltage = `$INSTANCE_NAME`_VMAX[converterNum];
    }
    else if(desiredVoltage < `$INSTANCE_NAME`_VMIN[converterNum])
    {
        desiredVoltage = `$INSTANCE_NAME`_VMIN[converterNum];
    }
    else
    {
        /* Desired value is within the range */
    }

    /* Calculate duty cycle depending on the converter polarity */
    if(IsFeedbackPositive(converterMask))
    {
        dutyCycle = desiredVoltage - `$INSTANCE_NAME`_VMIN[converterNum];
    }
    else
    {
        dutyCycle = `$INSTANCE_NAME`_VMAX[converterNum] - desiredVoltage;
    }
    dutyCycle = (uint16)((dutyCycle * (uint32)`$INSTANCE_NAME`_PWM_MAX) / vRange[converterNum]);

    return ((`$DutyCycleType`)dutyCycle);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConvertVoltageToPreRunDutyCycle
****************************************************************************//**
*
* \brief
*  Returns the PWM duty cycle required to achieve the desired voltage on
*  the selected power converter
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \param marginHiVoltage
*  Specifies the desired power converter output voltage in mV. 
*  Valid range: 1..65535.
*
* \return PWM duty cycle required to achieve the desired voltage. Return type
*  (uint8/uint16) depends on the PWM resolution.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_PRE_COEF
*
*******************************************************************************/
`$DutyCycleType` `$INSTANCE_NAME`_ConvertVoltageToPreRunDutyCycle(uint8 converterNum, uint16 desiredVoltage) `=ReentrantKeil($INSTANCE_NAME . "_ConvertVoltageToPreRunDutyCycle")`
{
    uint16 dutyCycle;

    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    dutyCycle = `$INSTANCE_NAME`_ConvertVoltageToDutyCycle(converterNum, desiredVoltage);
    dutyCycle = (uint16)((dutyCycle * (uint32)`$INSTANCE_NAME`_PRE_COEF[converterNum-1u]) / 1000u);

    /* Saturate duty cycle to PWM resolution */
    if (dutyCycle > `$INSTANCE_NAME`_PWM_MAX)
    {
        dutyCycle = `$INSTANCE_NAME`_PWM_MAX;
    }
    return ((`$DutyCycleType`)dutyCycle);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMarginHighVoltage
****************************************************************************//**
*
* \brief
*  Sets the margin high output voltage of the specified power converter.
*
*  This overrides the present vMarginHigh[x] setting and recalculates 
*  vMarginHighDutyCycle[x] to be ready for use by `$INSTANCE_NAME`_MarginHigh().
*  Note: calling this API does NOT cause any change in the PWM output
*  duty cycle.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \param marginHiVoltage
*  Specifies the desired power converter output voltage in mV. 
*  Valid range: 1..65535
*
* \globalvars
*  \ref `$INSTANCE_NAME`_vMarginHigh <br>
*  \ref `$INSTANCE_NAME`_vMarginHighDutyCycle
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetMarginHighVoltage(uint8 converterNum, uint16 marginHiVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetMarginHighVoltage")`
{
    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    /* Set new margin voltage */
    `$INSTANCE_NAME`_vMarginHigh[converterNum-1u] = marginHiVoltage;

    /* Recalculate duty cycle for new voltage */
    `$INSTANCE_NAME`_vMarginHighDutyCycle[converterNum-1u] =
        `$INSTANCE_NAME`_ConvertVoltageToDutyCycle(converterNum, marginHiVoltage);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMarginHighVoltage
****************************************************************************//**
*
* \brief Returns the margin high output voltage of the specified power converter.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \return Power converter margin high output voltage in mV.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetMarginHighVoltage(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetMarginHighVoltage")`
{
    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    return (`$INSTANCE_NAME`_vMarginHigh[converterNum-1u]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMarginLowVoltage
****************************************************************************//**
*
* \brief 
*  Sets the margin low output voltage of the specified power converter.
*
*  This overrides the present vMarginLow[x] setting and recalculates
*  vMarginLowDutyCycle[x] to be ready for use by `$INSTANCE_NAME`_MarginLow().
*  Note: calling this API does NOT cause any change in the PWM output
*  duty cycle.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \param marginLoVoltage
*  Specifies the desired power converter output margin low voltage in mV.
*  Valid range: 1..65535
*
* \globalvars
*  \ref `$INSTANCE_NAME`_vMarginLow <br>
*  \ref `$INSTANCE_NAME`_vMarginLowDutyCycle
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetMarginLowVoltage(uint8 converterNum, uint16 marginLoVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetMarginLowVoltage")`
{
    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    /* Set new margin voltage */
    `$INSTANCE_NAME`_vMarginLow[converterNum-1u] = marginLoVoltage;

    /* Recalculate duty cycle for new voltage */
    `$INSTANCE_NAME`_vMarginLowDutyCycle[converterNum-1u] = 
        `$INSTANCE_NAME`_ConvertVoltageToDutyCycle(converterNum, marginLoVoltage);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMarginLowVoltage
****************************************************************************//**
*
* \brief 
*  Returns the margin low output voltage of the specified power converter.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \return Power converter margin low output voltage in mV.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetMarginLowVoltage(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetMarginLowVoltage")`
{
    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    return (`$INSTANCE_NAME`_vMarginLow[converterNum-1u]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetNominalVoltage
****************************************************************************//**
*
* \brief 
*  Sets the nominal output voltage of the specified power converter.
*
*  This overrides the present vNom[x] setting and recalculates
*  vNominalDutyCycle to be ready for use by `$INSTANCE_NAME`_MarginLow().
*  Note: calling this API does NOT cause any change in the PWM output
*  duty cycle.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \param nominalVoltage
*  Specifies the desired power converter output nominal voltage in mV.
*  Valid range: 1..65535
*
* \globalvars
*  \ref `$INSTANCE_NAME`_vNom <br>
*  \ref `$INSTANCE_NAME`_vNominalDutyCycle
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetNominalVoltage(uint8 converterNum, uint16 nominalVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetNominalVoltage")`
{
    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    /* Set new nominal voltage */
    `$INSTANCE_NAME`_vNom[converterNum-1u] = nominalVoltage;

    /* Recalculate duty cycle for new voltage */
    `$INSTANCE_NAME`_vNominalDutyCycle[converterNum-1u] = `$INSTANCE_NAME`_ConvertVoltageToDutyCycle(converterNum, nominalVoltage);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNominalVoltage
****************************************************************************//**
*
* \brief 
*  Returns the nominal output voltage of the specified power converter.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \return Power converter nominal output voltage in mV.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetNominalVoltage(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetNominalVoltage")`
{
    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    return (`$INSTANCE_NAME`_vNom[converterNum-1u]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ActiveTrim
****************************************************************************//**
*
* \brief
*  Adjusts the PWM duty cycle of the specified power converter to get the power
*  converter actual voltage output closer to the desired voltage output.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \param actualVoltage
*  Specifies the current actual power converter output voltage reading in mV.
*  Valid range: 1..65535.
*
* \param desiredVoltage
*  Specifies the desired power converter output voltage in mV.
*  Valid range: 1..65535.
*
* \sideeffect
*  Calling this API may change the PWM duty cycle driving the control
*  voltage of the selected power converter causing the change in the power
*  converter output voltage.
*  If the desiredVoltage cannot be achieved because the PWM duty cycle is at
*  the min or max level, the alert signal will be asserted until the alert
*  condition is removed, only possible by calling this API with achievable
*  desiredVoltage.
*  NOTE The caller must ensure that the difference between the actual and
*  desired values is less than or equal to 32767.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ActiveTrim(uint8 converterNum, uint16 actualVoltage, uint16 desiredVoltage) `=ReentrantKeil($INSTANCE_NAME . "_ActiveTrim")`
{
    `$ConverterMaskType`  converterMask;
    uint16  error; 
    uint8   status;

    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    /* Convert converter number to array index */
    --converterNum;
    
    /* Calculate converter bit mask */
    converterMask = (`$ConverterMaskType`)(((`$ConverterMaskType`)1u) << converterNum);

    /* The converter polarity controls the error sign, i.e. whether increment or
    * decrement the current PWM duty cycle to achieve the desired voltage.
    */
    if(IsFeedbackPositive(converterMask))
    {
        error = desiredVoltage - actualVoltage;
    }
    else
    {
        error = actualVoltage - desiredVoltage;
    }

    /* Compute the next PWM duty cycle for a given error value */
    #if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL)
        status = `$INSTANCE_NAME`_IncrementalControllerProcess(converterNum, (int16)error);
    #else
        status = `$INSTANCE_NAME`_IntegralControllerProcess(converterNum, (int16)error);
    #endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL */

    switch(status)
    {
    case TRIM_SUCCESS:
        
        /* Clear corresponding alert source bit */
        `$INSTANCE_NAME`_alertSource &= (`$ConverterMaskType`)~converterMask;
        
        /* De-assert alert pin if no PWMs generating alert */
        #ifdef `$INSTANCE_NAME`_ALERT_PRESENT
            if(`$INSTANCE_NAME`_alertSource == 0u)
            {
                `$INSTANCE_NAME`_CTRL_REG &= (uint8)~`$INSTANCE_NAME`_CTRL_ALERT;
            }
        #endif /* `$INSTANCE_NAME`_ALERT_PRESENT */
        break;

    case TRIM_ALERT:

        /* Set alert source for this converter */
        `$INSTANCE_NAME`_alertSource |= converterMask;

        /* Assert alert pin */
        #ifdef `$INSTANCE_NAME`_ALERT_PRESENT
            `$INSTANCE_NAME`_CTRL_REG |= `$INSTANCE_NAME`_CTRL_ALERT;
        #endif /* `$INSTANCE_NAME`_ALERT_PRESENT */
        break;
    
    default:
        break; /* No actions for this cycle */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDutyCycle
****************************************************************************//**
*
* \brief
*  Sets the PWM duty cycle of the PWM associated with the specified power
*  converter.
*
*  The PWM period is always fixed at the maximum value depending on the
*  resolutions set in the customizer.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
* \param dutyCycle
*  Specifies the PWM duty cycle in PWM clock counts.
*  Valid range: 0..255 (uint8) or 0..1023 (uint16) depending on the resolution.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetDutyCycle(uint8 converterNum, `$DutyCycleType` dutyCycle) `=ReentrantKeil($INSTANCE_NAME . "_SetDutyCycle")`
{
    #if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL)
        uint32 scaledDutyCycle;
    #endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL */

    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));
    
    --converterNum;
    CY_SET_REG`$PWMRegSize`(pwmCompare[converterNum], dutyCycle);
    
    #if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL)
        /* Update the controller output to reflect a new duty cycle value and
        * set the flag the duty cycle has been changed. */
        scaledDutyCycle = (uint32)dutyCycle << POST_GAIN;
        integralControlOut[converterNum] = (int32)scaledDutyCycle;
        dutyCycleChanged |= (`$ConverterMaskType`)((`$ConverterMaskType`)1u << converterNum);
    #endif /* TrimMargin_CONTROLLER_TYPE == TrimMargin_INTEGRAL */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDutyCycle
****************************************************************************//**
*
* \brief
*  Gets the current PWM duty cycle of the PWM associated with the specified
*  power converter.
*
*  Note: if the `$INSTANCE_NAME`_ActiveTrim() API is being called regularly,
*  the value returned should be expected to change over time.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.

* \return PWM duty cycle in PWM clock counts. Return type (uint8/uint16)
*  depends on the resolution.
*
*******************************************************************************/
`$DutyCycleType` `$INSTANCE_NAME`_GetDutyCycle(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetDutyCycle")`
{
    /* Halt CPU in debug mode if converterNum is out of valid range */
    CYASSERT((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS));

    return ((`$DutyCycleType`)CY_GET_REG`$PWMRegSize`(pwmCompare[converterNum-1u]));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAlertSource
****************************************************************************//**
*
* \brief
*  Returns a bit mask indicating which PWMs are generating an alert.
*
* \return Bit field Alert Source. Return type (uint8/uint16/uint32) depends on
*  the number of converters.
*
*  Bits    Description       
*  0       1 - Failure to achieve power converter regulation on trim output 1
*  1       1 - Failure to achieve power converter regulation on trim output 2
*  ...
*  23      1 - Failure to achieve power converter regulation on trim output 24
*
*******************************************************************************/
`$ConverterMaskType` `$INSTANCE_NAME`_GetAlertSource(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertSource")`
{
    return (`$INSTANCE_NAME`_alertSource);
}


/*******************************************************************************
* Function Name: IntegralControllerProcess
****************************************************************************//**
*
* \brief
*  Computes the next PWM duty cycle for a given error using the integral
*  controller and sets it to the PWM associated with the specified power
*  converter.
*
* \return Trim operation status for the specified power converter.
*  TRIM_ALERT -   PWM is at a min or max duty cycle, but the desired power
*                 converter output voltage has not been achieved.
*  TRIM_SUCCESS - the next PWM duty cycle was computed successfully. 
*  TRIM_NONE    - no change to the PWM duty cycle.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL)
static uint8 `$INSTANCE_NAME`_IntegralControllerProcess(uint8 converterNum, int16 error) `=ReentrantKeil($INSTANCE_NAME . "_IntegralControllerProcess")`
{
    /* Integral coefficients for the controller multiplied by the control sample time */
    `$PIDCoefficients`;
    `$ConverterMaskType` converterMask;
    uint8  status;

    converterMask = (`$ConverterMaskType`)(((`$ConverterMaskType`)1u) << converterNum);

    /* Compute the new controller output or skip the current trim iteration
    * depending on whether the new duty cycle has been set prior an attempt to
    * trim a power converter. This allows the converter output to change
    * respectively before calculating a new controller output. 
    */
    if ((dutyCycleChanged & converterMask) == 0u)
    {
        status = TRIM_ALERT;

        /* Compute the new integral controller output */
        integralControlOut[converterNum] += error * (int32)Ki[converterNum];

        /* Saturate the controller output within the PWM duty cycle range */
        if (integralControlOut[converterNum] < OUTPUT_SAT_L)
        {
            integralControlOut[converterNum] = OUTPUT_SAT_L;
        }
        else if (integralControlOut[converterNum] > OUTPUT_SAT_H)
        {
            integralControlOut[converterNum] = OUTPUT_SAT_H;
        }
        else
        {
            status = TRIM_SUCCESS;
        }

        /* Set the new PWM duty cycle */
        CY_SET_REG`$PWMRegSize`(pwmCompare[converterNum], ((uint32)integralControlOut[converterNum] >> POST_GAIN));
    }
    else
    {
        dutyCycleChanged &= (`$ConverterMaskType`)~converterMask;
        status = TRIM_NONE;
    }
    return status;
}
#endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INTEGRAL */


/*******************************************************************************
* Function Name: IncrementalControllerProcess
****************************************************************************//**
*
* \brief
*  Computes the next PWM duty cycle for a given error using the incremental
*  controller and sets it to the PWM associated with the specified power
*  converter
*
* \return Trim operation status for the specified power converter.
*  TRIM_ALERT -   PWM is at a min or max duty cycle, but the desired power
*                 converter output voltage has not been achieved.
*  TRIM_SUCCESS - the next PWM duty cycle was computed successfully.
*  TRIM_NONE    - no change to the PWM duty cycle.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL)
static uint8 `$INSTANCE_NAME`_IncrementalControllerProcess(uint8 converterNum, int16 error) `=ReentrantKeil($INSTANCE_NAME . "_IncrementalControllerProcess")`
{
    uint8 status = TRIM_NONE;
    int16 newDutyCycle;

    /* If error is positive and greater than half-bit of PWM, adjust above history */
    if (error > (int16)`$INSTANCE_NAME`_VDELTA[converterNum])
    {
        ++(`$INSTANCE_NAME`_trimCtl[converterNum].above);
    }
    else
    {
        /* If error is negative and greater than half-bit of PWM, adjust below history */
        if ((error + (int16)`$INSTANCE_NAME`_VDELTA[converterNum]) < 0)
        {
            ++(`$INSTANCE_NAME`_trimCtl[converterNum].below);
        }
    }

    /* When gathered enough history, check for trim adjustment */
    if ((`$INSTANCE_NAME`_trimCtl[converterNum].above +
         `$INSTANCE_NAME`_trimCtl[converterNum].below) > `$INSTANCE_NAME`_trimCycleCount)
    {
        /* Read current PWM duty cycle */
        newDutyCycle = (int16)CY_GET_REG`$PWMRegSize`(pwmCompare[converterNum]);
        
        /* If Above dominant, then increase the PWM duty cycle */
        if (`$INSTANCE_NAME`_trimCtl[converterNum].below < `$INSTANCE_NAME`_MIN_DELTA)
        {
            ++newDutyCycle;
        }

        /* If Below dominant, then decrease the PWM duty cycle */
        if (`$INSTANCE_NAME`_trimCtl[converterNum].above < `$INSTANCE_NAME`_MIN_DELTA)
        {
            --newDutyCycle;
        }

        /* Check if the calculated duty cycle is within the valid range */
        if ((newDutyCycle >= (int16)`$INSTANCE_NAME`_PWM_MIN) && (newDutyCycle <= (int16)`$INSTANCE_NAME`_PWM_MAX))
        {
            /* Set new PWM duty cycle */
            CY_SET_REG`$PWMRegSize`(pwmCompare[converterNum], (`$DutyCycleType`)newDutyCycle);
            status = TRIM_SUCCESS;
        }
        else
        {
            status = TRIM_ALERT;
        }
        
        /* Clear history */
        `$INSTANCE_NAME`_trimCtl[converterNum].above = 0u;
        `$INSTANCE_NAME`_trimCtl[converterNum].below = 0u;
    }
    return (status);
}
#endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL */


/* [] END OF FILE */
