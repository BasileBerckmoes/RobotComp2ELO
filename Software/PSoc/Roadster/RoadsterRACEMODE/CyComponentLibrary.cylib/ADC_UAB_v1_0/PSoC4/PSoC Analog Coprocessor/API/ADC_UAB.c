/*******************************************************************************
* \file     `$INSTANCE_NAME`.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief Provides the source code to the API for the `$INSTANCE_NAME` Component.
*
* Note:
*
********************************************************************************
* \copyright
* (c) 2015-2016, Cypress Semiconductor Corporation. All rights reserved. This 
* software, including source code, documentation and related materials 
* ("Software"), is owned by Cypress Semiconductor Corporation ("Cypress") and 
* is protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Therefore, you may use this Software only as provided in the license 
* agreement accompanying the software package from which you obtained this 
* Software ("EULA"). If no EULA applies, Cypress hereby grants you a personal, 
* non-exclusive, non-transferable license to copy, modify, and compile the 
* Software source code solely for use in connection with Cypress's integrated 
* circuit products. Any reproduction, modification, translation, compilation, 
* or representation of this Software except as specified above is prohibited 
* without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
* Cypress reserves the right to make changes to the Software without notice. 
* Cypress does not assume any liability arising out of the application or use 
* of the Software or any product or circuit described in the Software. Cypress 
* does not authorize its products for use in any products where a malfunction 
* or failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death ("High Risk Product"). By 
* including Cypress's product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_REFSOURCE.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

uint8 `$INSTANCE_NAME`_initVar = 0u;
uint8 `$INSTANCE_NAME`_irqEnabled = 0u;

/** Indicates whether the `$INSTANCE_NAME` is calibrating. Set by Calibrate(), cleared in CalibrateInt(). */
static uint8 `$INSTANCE_NAME`_calStatus = `$INSTANCE_NAME`_IDLE;
/** The highest raw value in linear region. Set during calibration.*/
static int32 `$INSTANCE_NAME`_calibrateHigh = 0;
/** The lowest raw value in linear region. Set during calibration.*/
static int32 `$INSTANCE_NAME`_calibrateLow = 0;
/** The scale which corresponds to the chosen range. Set by SetRange. */
static uint32 `$INSTANCE_NAME`_gainNumerator = `$INSTANCE_NAME`_GAIN_NUMERATOR;
/** The scale which corresponds to the chosen range. Set by SetRange. */
static uint32 `$INSTANCE_NAME`_gainDenominator = `$INSTANCE_NAME`_GAIN_DENOMINATOR;
/** Contains non-retained configuration information. Set by Sleep(). */
static uint8 `$INSTANCE_NAME`_backup = 0u;

static uint32 `$INSTANCE_NAME`_IsHardwareFree(void);

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConversionInt
****************************************************************************//**
*
* Called when an interrupt occurs if IRQ is enabled. Clears pending interrupt. 
* Calls entry and exit callbacks, if they are defined in cyapicallbacks.h.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConversionInt(void)
{
    uint8 interruptState = CyEnterCriticalSection();
    
    #ifdef `$INSTANCE_NAME`_CONVERSIONINT_ENTRY_CALLBACK
       `$INSTANCE_NAME`_ConversionInt_EntryCallback();
    #endif /* `$INSTANCE_NAME`_CONVERSIONINT_ENTRY_CALLBACK */
    
    /* Clear interrupt */
    `$INSTANCE_NAME`_ClearInterrupt();
    
    #ifdef `$INSTANCE_NAME`_CONVERSIONINT_EXIT_CALLBACK
       `$INSTANCE_NAME`_ConversionInt_ExitCallback();
    #endif /* `$INSTANCE_NAME`_CONVERSIONINT_EXIT_CALLBACK */ 
    
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Performs all required initialization for this component, and enables the
* power. The power is set to the appropriate level based on the clock 
*frequency. Does not start a conversion.
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
* Function Name: `$INSTANCE_NAME`_StartConvert
****************************************************************************//**
*
* Begins a conversion.
*
* \retval uint32 The function returns cystatus of its operation.
*    - CYRET_STARTED - The `$INSTANCE_NAME` is already converting. No new 
*      conversion started.
*    - CYRET_SUCCESS - A new conversion has started.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_StartConvert(void)
{
    uint32 `$INSTANCE_NAME`_convertStatus = CYRET_SUCCESS;
    if (0u == `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_RETURN_STATUS))
    {
        `$INSTANCE_NAME`_convertStatus = CYRET_STARTED;
    }
    else
    {
        /* Clear any pending interrupt */
        `$INSTANCE_NAME`_ClearInterrupt();
        /* Start decimator */
        `$INSTANCE_NAME`_DCM_CTRL_REG |= (1uL << `$INSTANCE_NAME`_DCM_CTRL_START_SHIFT);
        if (0u != `$INSTANCE_NAME`_irqEnabled)
        {
            /* Enable interrupt */
            `$INSTANCE_NAME`_HALF_A_INTR_MASK_REG = `$INSTANCE_NAME`_DCM_INTR_MASK;
        }
    }
    return `$INSTANCE_NAME`_convertStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Disables underlying hardware.  Terminates conversion if there is a conversion 
* in progress.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop (void)
{
    `$INSTANCE_NAME`_HALF_A_Stop();
    `$INSTANCE_NAME`_HALF_B_Stop();
    `$INSTANCE_NAME`_DCM_GLOBALCTRL_REG = 0uL;
    `$INSTANCE_NAME`_REFSOURCE_Stop();
    if (0u != `$INSTANCE_NAME`_irqEnabled)
    {
        /* Disable interrupt */
        `$INSTANCE_NAME`_HALF_A_INTR_MASK_REG &= ~`$INSTANCE_NAME`_DCM_INTR_MASK;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Configures hardware and data structures according to component parameters. 
* Does not power hardware.  Called from `$INSTANCE_NAME`_Start().
* `$INSTANCE_NAME`_Start() is the preferred method for initializing the 
* component. The ISR is set to the `$INSTANCE_NAME`_ConversionInt() here. During 
* calibration, the ISR is temporarily set to the 
* `$INSTANCE_NAME`_CalibrateInt() and then restored to 
* `$INSTANCE_NAME`_ConversionInt().
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    /* Initialize UAB halves */
    `$INSTANCE_NAME`_HALF_A_Init(&`$INSTANCE_NAME`_HALF_A_config);
    `$INSTANCE_NAME`_HALF_B_Init(&`$INSTANCE_NAME`_HALF_B_config);
    /* Initialize reference */
    `$INSTANCE_NAME`_REFSOURCE_Init();
    /* Initialize the decimator. */
    `$INSTANCE_NAME`_DCM_CTRL_REG = (`$INSTANCE_NAME`_DCM_CTRL_DEFAULT
        | (`$INSTANCE_NAME`_DCM_CTRL_REG & `$INSTANCE_NAME`_DCM_CTRL_SEL_MASK));
    `$INSTANCE_NAME`_DCM_OVR_REG = `$INSTANCE_NAME`_DCM_OVR_DEFAULT;
    /* Set Interrupt vector */
    `$INSTANCE_NAME`_BUR_ISR_StartEx(&`$INSTANCE_NAME`_ConversionInt);
    /* Clear any pending interrupt */
    `$INSTANCE_NAME`_HALF_A_INTR_REG = `$INSTANCE_NAME`_DCM_INTR_MASK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Enables underlying hardware. Does not start a conversion. Called from  
* `$INSTANCE_NAME`_Start(). `$INSTANCE_NAME`_Start() is the preferred method for 
* initializing the component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    /* Enable and start the UAB halves */
    `$INSTANCE_NAME`_HALF_A_Enable();
    `$INSTANCE_NAME`_HALF_B_Enable();
    `$INSTANCE_NAME`_HALF_A_Run(1u);
    `$INSTANCE_NAME`_HALF_B_Run(1u);
    `$INSTANCE_NAME`_REFSOURCE_Enable();
    /*Enable the decimator. */
    `$INSTANCE_NAME`_DCM_GLOBALCTRL_REG = `$INSTANCE_NAME`_DCM_GLOBALCTRL_DEFAULT;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableIRQ
****************************************************************************//**
*
* Enables interrupt after a conversion finishes. Conversion entry and exit 
* callbacks should be defined in <i>cyapicallbacks.h</i>.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableIRQ(void)
{
    `$INSTANCE_NAME`_irqEnabled = 1u;
    /* Enable interrupt */
    `$INSTANCE_NAME`_HALF_A_INTR_MASK_REG = `$INSTANCE_NAME`_DCM_INTR_MASK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableIRQ
****************************************************************************//**
*
* Disables interrupt after a conversion finishes.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableIRQ(void)
{
    `$INSTANCE_NAME`_irqEnabled = 0u;
    `$INSTANCE_NAME`_HALF_A_INTR_MASK_REG &= ~(`$INSTANCE_NAME`_DCM_INTR_MASK);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsEndConversion
****************************************************************************//**
*
* Immediately returns the status of the conversion or does not return (blocking) 
* until the conversion completes, depending on the retMode parameter.
*
* \param retMode Check conversion return mode. See the following table for 
* options.
* 
* <table>
* <tr>
*   <th>Options</th>
*   <th>Description</th>
* </tr>
* <tr>
*   <td>`$INSTANCE_NAME`_RETURN_STATUS</td>
*   <td>Immediately returns the conversion or calibrate status. If the value 
*   returned is non-zero, the conversion is not complete, and this function should 
*   be retried until a result of zero is returned.</td>
* </tr>
* <tr>
*   <td>`$INSTANCE_NAME`_WAIT_FOR_RESULT</td>
*   <td>Does not return a result until the `$INSTANCE_NAME` conversion is 
*   complete.</td>
* </tr>
* </table>
* 
* \retval uint32 If a nonzero value is returned, the last conversion is complete. 
* If the returned value is zero, the `$INSTANCE_NAME` is still calculating the 
* last result.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_eoc_enum retMode)
{
    uint32 `$INSTANCE_NAME`_timeout = 0uL;
    uint32 `$INSTANCE_NAME`_convertStatus = `$INSTANCE_NAME`_IsHardwareFree();

    if ( `$INSTANCE_NAME`_RETURN_STATUS != retMode)
    {
        while ((`$INSTANCE_NAME`_CONVERSION_BUSY == `$INSTANCE_NAME`_convertStatus) 
            && (`$INSTANCE_NAME`_TIMEOUT_DURATION >= `$INSTANCE_NAME`_timeout))
        {
            `$INSTANCE_NAME`_convertStatus = `$INSTANCE_NAME`_IsHardwareFree();
            `$INSTANCE_NAME`_timeout++;
        }
    }
    
    return `$INSTANCE_NAME`_convertStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsHardwareFree
****************************************************************************//**
*
* Helper function for IsEndConversion
*
* \retval uint32 If a nonzero value is returned, the hardware is not in use. 
* If the returned value is zero, the `$INSTANCE_NAME` hardware is in use.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_IsHardwareFree(void)
{
    /* For firmware trigger, simply check the start bit, which is cleared by
     * the decimator after every conversion.
     * Calibration uses firmware trigger, so this captures the case of
     * a calibration in progress. */
    uint32 `$INSTANCE_NAME`_busyStatus = (`$INSTANCE_NAME`_DCM_CTRL_REG & (1uL << `$INSTANCE_NAME`_DCM_CTRL_START_SHIFT));
    `$INSTANCE_NAME`_busyStatus = (`$INSTANCE_NAME`_busyStatus == (1uL << `$INSTANCE_NAME`_DCM_CTRL_START_SHIFT) )
                                            ? `$INSTANCE_NAME`_CONVERSION_BUSY
                                            : `$INSTANCE_NAME`_CONVERSION_DONE;
    return `$INSTANCE_NAME`_busyStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Calibrate
****************************************************************************//**
*
* Configures hardware for calibration.  The status of the calibration is either 
* returned immediately or is blocked until the calibration completes, depending 
* on the calibrateMode input.
*
* \param calibrateMode Check calibration return mode. See the following table 
* for options.
* 
* <table>
* <tr>
*   <th>Options</th>
*   <th>Description</th>
* </tr>
* <tr>
*   <td>`$INSTANCE_NAME`_USE_INTERRUPT</td>
*   <td>Calibration will be interrupt-driven.  Will enter calibration interrupt 
*   twice, then set `$INSTANCE_NAME`_calStatus to IDLE. Other tasks may be 
*   performed while waiting for calibration to complete.</td>
* </tr>
* <tr>
*   <td>`$INSTANCE_NAME`_WAIT_FOR_CALIBRATE</td>
*   <td>Does not return a result until the `$INSTANCE_NAME` calibration is 
*   complete.</td>
* </tr>
* </table>
* 
* \retval uint32 The status of the calibration. If nonzero, calibration was 
* successful.
*
* \sideeffect Sets the UAB interrupt vector to `$INSTANCE_NAME`_CalibrateInt 
* during calibration. Sets it back to `$INSTANCE_NAME`_ConversionInt when 
* finished.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Calibrate(`$INSTANCE_NAME`_calibrate_mode_enum calibrateMode)
{
    uint32 retStatus = 1uL;
    if (`$INSTANCE_NAME`_CONVERSION_BUSY == `$INSTANCE_NAME`_IsHardwareFree())
    {
        retStatus = 0uL;
    }
    else
    {
        /* Clear any pending interrupt */
        `$INSTANCE_NAME`_ClearInterrupt();
        /* Configure first stage */
        `$INSTANCE_NAME`_HALF_A_SetCapB(`$INSTANCE_NAME`_HA_B_CAP_CAL);
        `$INSTANCE_NAME`_HALF_A_SetCapC(`$INSTANCE_NAME`_HA_C_CAP_CAL);
        `$INSTANCE_NAME`_HALF_A_SW_CB_IN0_REG = `$INSTANCE_NAME`_HA_B_IN0_CAL1;
        `$INSTANCE_NAME`_HALF_A_SW_CB_IN1_REG = `$INSTANCE_NAME`_HA_B_IN1_CAL1;
        /* Start decimator */
        `$INSTANCE_NAME`_DCM_CTRL_REG |= (1uL << `$INSTANCE_NAME`_DCM_CTRL_START_SHIFT);
        `$INSTANCE_NAME`_calStatus = `$INSTANCE_NAME`_CALIBRATING_PHASE1;
        
        if (`$INSTANCE_NAME`_USE_INTERRUPT == calibrateMode)
        {
            `$INSTANCE_NAME`_BUR_ISR_SetVector(&`$INSTANCE_NAME`_CalibrateInt);
            /* Enable interrupt */
            `$INSTANCE_NAME`_HALF_A_INTR_MASK_REG = `$INSTANCE_NAME`_DCM_INTR_MASK;
        }
        else
        {
            /* Disable interrupt */
            `$INSTANCE_NAME`_HALF_A_INTR_MASK_REG &= ~(`$INSTANCE_NAME`_DCM_INTR_MASK);
            /* Blocking conversion could timeout. If it does, this function will also
            report a timeout.  In this case, skip the second wait for end of conversion,
            calibration has failed. Continue with phase 2 to restore switches, caps, 
            and other settings to pre-calibrate condition. */
            retStatus = `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT);
            `$INSTANCE_NAME`_ProcessCalibratePhase1();
            if (`$INSTANCE_NAME`_CONVERSION_DONE == retStatus)
            {
                retStatus = `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT);
            }
            `$INSTANCE_NAME`_ProcessCalibratePhase2();
            `$INSTANCE_NAME`_ClearInterrupt();
        }
    }
    return retStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RawToResult16
****************************************************************************//**
*
* For given raw input, returns the calibrated `$INSTANCE_NAME` result.  This 
* result is saturated at the lower and upper limits of the operating resolution. 
* The calibration formula is:
* 
* (((raw - calibrateHigh) * (MAX_HIGH - MAX_LOW)) / (calibrateHigh - calibrateLow)) + MAX_LOW.
*
* \param raw The direct output of the decimator register.
*
* \retval int16 Saturated, calibrated `$INSTANCE_NAME` result.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_RawToResult16(int32 raw)
{
    int32 result = (((raw - `$INSTANCE_NAME`_calibrateLow) 
                * (`$INSTANCE_NAME`_MAX_HIGH - `$INSTANCE_NAME`_MAX_LOW)) 
                / (`$INSTANCE_NAME`_calibrateHigh - `$INSTANCE_NAME`_calibrateLow)) 
                + `$INSTANCE_NAME`_MAX_LOW;
    /* Saturate co_est */
    if (result < `$INSTANCE_NAME`_LIMIT_LOWBOUND)
    {
        result = `$INSTANCE_NAME`_LIMIT_LOWBOUND;
    }
    
    if (result > `$INSTANCE_NAME`_LIMIT_HIGHBOUND) 
    { 
        result = `$INSTANCE_NAME`_LIMIT_HIGHBOUND;
    }
    return (int16)result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_mVolts
****************************************************************************//**
*
* For given counts input, returns the voltage relative to Vneg.  For example, if 
* the input voltage to the ADC was 0.534 volts, the return value would be 534. 
* The equation for the result is:
* 
* result (mV) = counts * (reference/(Resolution/2)) * gain + Vneg.
*
* In Differential Mode, Vneg is zero. In Single-Ended Mode, Vneg is the reference.
*
* Resolution is 14-bit.
*
* Note that the multiplication of counts (14-bit max), reference (14-bit max) and 
* gain (2 max) results in a maximum of of 29-bits. An increase in any of these
* parameters will cause the result to overflow 32 bits.
*
* \param counts A calibrated `$INSTANCE_NAME` result.
*
* \retval int16 The voltage relative to Vneg in units of millivolts.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_CountsTo_mVolts(int32 counts)
{
    /* Multiplying reference and gain here to ensure the integer math works for fractional gains */
    uint32 result = (`$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV * `$INSTANCE_NAME`_gainNumerator) \
              / `$INSTANCE_NAME`_gainDenominator;
    uint32 vneg = (`$INSTANCE_NAME`_SINGLE_ENDED == `$INSTANCE_NAME`_PARAM_INPUT_MODE) ? 
        `$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV :
        0uL;
    
    /* Using right shift to divide reference by Resolution/2. Right shift is more
    efficient on the CM0 than divide for integer values*/ 
    result = (((uint32) counts * result) >> (`$INSTANCE_NAME`_PARAM_RESOLUTION - 1u)) + vneg;
    return (int16) result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_uVolts
****************************************************************************//**
*
* For given counts input, returns the voltage relative to Vneg. For example, if 
* the ADC measured 0.534 volts, the return value would be 534000. The equation 
* for the result is:
* 
* result (&micro;V) = counts * (reference/(Resolution/2)) * gain + Vneg.
*
* In Differential Mode, Vneg is zero. In Single-Ended Mode, Vneg is reference.
*
* \param counts A calibrated `$INSTANCE_NAME` result.
*
* \retval int32 The voltage relative to Vneg in units of microvolts.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_CountsTo_uVolts(int32 counts)
{
    /* reference in uVolts, divided by Resolution/2 and scaled by the gain to prevent overflowing in final calculation */
    uint32 scaledVref = (`$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_UV_SCALEDOWN * `$INSTANCE_NAME`_gainNumerator) \
              / `$INSTANCE_NAME`_gainDenominator;
    
    uint32 vneg = (`$INSTANCE_NAME`_SINGLE_ENDED == `$INSTANCE_NAME`_PARAM_INPUT_MODE) ? 
        (`$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV * `$INSTANCE_NAME`_UNITCONST_FACTOR_MV2UV) :
        0uL;
        
    int32 result = ((int32) counts * (int32) scaledVref) + (int32) vneg;
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_Volts
****************************************************************************//**
*
* For given counts input, returns the voltage relative to Vneg. For example, if 
* the ADC measured 0.534 volts, the return value would be 0.534. The equation 
* for the result is:
* 
* result (V) = counts * (reference/(Resolution/2)) * gain + Vneg.
*
* In Differential Mode, Vneg is zero. In Single-Ended Mode, Vneg is the reference.
*
* \param counts A calibrated `$INSTANCE_NAME` result.
*
* \retval float32 The voltage relative to Vneg in units of volts.
*
*******************************************************************************/
float32 `$INSTANCE_NAME`_CountsTo_Volts(int32 counts)
{
    uint32 vref = `$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV;
    float32 result = (float32) vref;
    
    /* result stores the reference value converted from mV to Volts */
    result = result / `$INSTANCE_NAME`_UNITCONST_DIVISOR_MV2V;
    
    uint32 halfResolution = (1uL << (`$INSTANCE_NAME`_PARAM_RESOLUTION - 1uL));
    float32 gain = ((float32)`$INSTANCE_NAME`_gainNumerator) / ((float32)`$INSTANCE_NAME`_gainDenominator);
    
    float32 vneg = (`$INSTANCE_NAME`_SINGLE_ENDED == `$INSTANCE_NAME`_PARAM_INPUT_MODE) ? 
        result :
        ((float32) 0.0);
        
    /* result scaled by the gain */
    result = result * gain;
    result = (((((float32) counts) * result)) / ((float32) halfResolution)) + vneg;

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* Prepare the component for entering deep sleep.  The underlying hardware 
* requires a high speed clock, so it will not run in deep sleep. Do not call 
* this function before normal sleep (cpu off). For normal sleep, a conversion 
* will continue operating as normal.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    /* Save  enable state */
    if (0UL != (`$INSTANCE_NAME`_HALF_A_SRAM_CTRL_REG & `$INSTANCE_NAME`_HALF_A_RUN_MASK))
    {
        /* Component is enabled */
        `$INSTANCE_NAME`_backup = 1u;
        /* Stop the configuration */
        `$INSTANCE_NAME`_Stop();
    }
    else
    {
        /* Component is disabled */
        `$INSTANCE_NAME`_backup = 0u;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
* Restore the component to its pre-deep sleep condition.  Should be called just 
* after awaking from deep sleep.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{     
    if (0u != `$INSTANCE_NAME`_backup) /* If block was enabled... */
    {
        /* Then enable rest of block */
        `$INSTANCE_NAME`_Enable();
    } /* Do nothing if component was disable before */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ProcessCalibratePhase1
****************************************************************************//**
*
* Processes first phase of calibration and begins phase two.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ProcessCalibratePhase1(void)
{
    /* Collect data point (usually VSSA-reference raw) */
    `$INSTANCE_NAME`_calibrateLow = (int32) `$INSTANCE_NAME`_DCM_RESULT_REG;
    /* Configure switches for 2nd phase (Usually reference-Vssa) */
    `$INSTANCE_NAME`_HALF_A_SW_CB_IN0_REG = `$INSTANCE_NAME`_HA_B_IN0_CAL2;
    `$INSTANCE_NAME`_HALF_A_SW_CB_IN1_REG = `$INSTANCE_NAME`_HA_B_IN1_CAL2;
    /* Start decimator */
    `$INSTANCE_NAME`_DCM_CTRL_REG |= (1uL << `$INSTANCE_NAME`_DCM_CTRL_START_SHIFT);
    `$INSTANCE_NAME`_calStatus = `$INSTANCE_NAME`_CALIBRATING_PHASE2;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ProcessCalibratePhase2
****************************************************************************//**
*
* Processes second phase of calibration and returns hardware to normal.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ProcessCalibratePhase2(void)
{
    /* Collect data points (usually Vref-Vref raw */
    `$INSTANCE_NAME`_calibrateHigh = (int32) `$INSTANCE_NAME`_DCM_RESULT_REG;
    /* Configure for normal operation (varies by se/diff and Vneg) */
    `$INSTANCE_NAME`_HALF_A_SetCapB(`$INSTANCE_NAME`_HA_B_CAP_DEFAULT);
    `$INSTANCE_NAME`_HALF_A_SetCapC(`$INSTANCE_NAME`_HA_C_CAP_DEFAULT);
    `$INSTANCE_NAME`_HALF_A_SW_CB_IN0_REG = `$INSTANCE_NAME`_HA_B_IN0_CONV;
    `$INSTANCE_NAME`_HALF_A_SW_CB_IN1_REG = `$INSTANCE_NAME`_HA_B_IN1_CONV;
    `$INSTANCE_NAME`_calStatus = `$INSTANCE_NAME`_IDLE;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CalibrateInt
****************************************************************************//**
*
* Interrupt function for calibration.  Calibrate sets this function as the UAB 
* vector.  During its execution, it restores the conversion function as the 
* vector.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CalibrateInt(void)
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    
    #ifdef `$INSTANCE_NAME`_CALIBRATEINT_ENTRY_CALLBACK
       `$INSTANCE_NAME`_CalibrateInt_EntryCallback();
    #endif /* `$INSTANCE_NAME`_CALIBRATEINT_ENTRY_CALLBACK */ 

    /* Clear interrupt */
    `$INSTANCE_NAME`_ClearInterrupt();
    
    if (`$INSTANCE_NAME`_CALIBRATING_PHASE1 == `$INSTANCE_NAME`_calStatus)
    {
        /* Starts calibrate phase 2 */
        `$INSTANCE_NAME`_ProcessCalibratePhase1();
    }
    else if (`$INSTANCE_NAME`_CALIBRATING_PHASE2 == `$INSTANCE_NAME`_calStatus)
    {
        `$INSTANCE_NAME`_ProcessCalibratePhase2();
        if (0u != `$INSTANCE_NAME`_irqEnabled)
        {
            `$INSTANCE_NAME`_HALF_A_INTR_MASK_REG = `$INSTANCE_NAME`_DCM_INTR_MASK;
        }
        `$INSTANCE_NAME`_BUR_ISR_SetVector(&`$INSTANCE_NAME`_ConversionInt);
    }
    else
    {
        /* This branch intentionally blank because this ISR is not expecting to
         * be called from a state other than PHASE1 or PHASE2. */
    }
    
    #ifdef `$INSTANCE_NAME`_CALIBRATEINT_EXIT_CALLBACK
       `$INSTANCE_NAME`_CalibrateInt_ExitCallback();
    #endif /* `$INSTANCE_NAME`_CALIBRATEINT_EXIT_CALLBACK */ 
    
    CyExitCriticalSection(interruptState);
}
/* [] END OF FILE */
