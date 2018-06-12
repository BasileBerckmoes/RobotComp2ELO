/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the `$INSTANCE_NAME`
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_`$INSTANCE_NAME`_H)
#define CY_`$INSTANCE_NAME`_H

#include <cy_device_headers.h>
#include <ctdac/cy_ctdac.h>
#ifdef CTBM0
#include <ctb/cy_ctb.h>
#endif
#include <syspm/cy_syspm.h>

/*******************************************************************************
                            Symbol Data Types
The data types that are used in the customizer are redefined as constants here.
*******************************************************************************/
#define `$INSTANCE_NAME`_COMP_REFSOURCE_EXTERNAL            0uL
#define `$INSTANCE_NAME`_COMP_REFSOURCE_VDDA                1uL
#define `$INSTANCE_NAME`_COMP_REFSOURCE_DWR                 2uL
#define `$INSTANCE_NAME`_COMP_FORMAT_UNSIGNED               0uL
#define `$INSTANCE_NAME`_COMP_FORMAT_SIGNED                 1uL
#define `$INSTANCE_NAME`_COMP_OUTPUT_UNBUFFERED_PIN         0uL
#define `$INSTANCE_NAME`_COMP_OUTPUT_UNBUFFERED_INTERNAL    1uL
#define `$INSTANCE_NAME`_COMP_OUTPUT_BUFFERED_PIN           2uL
#define `$INSTANCE_NAME`_COMP_OUTPUT_BUFFERED_INTERNAL      3uL
#define `$INSTANCE_NAME`_COMP_UPDATE_DIRECT                 0uL
#define `$INSTANCE_NAME`_COMP_UPDATE_BUFFERED               1uL
#define `$INSTANCE_NAME`_COMP_UPDATE_STROBE_EDGE            2uL
#define `$INSTANCE_NAME`_COMP_UPDATE_STROBE_IMMEDIATE       3uL
#define `$INSTANCE_NAME`_COMP_UPDATE_STROBE_LEVEL           4uL
#define `$INSTANCE_NAME`_COMP_DEEPSLEEP_OFF                 0uL
#define `$INSTANCE_NAME`_COMP_DEEPSLEEP_ON                  1uL

/*******************************************************************************
                            Internal Constants
*******************************************************************************/
#define `$INSTANCE_NAME`_COMP_INTERRUPT_ENABLE          1uL
#define `$INSTANCE_NAME`_COMP_INTERRUPT_DISABLE         0uL
#define `$INSTANCE_NAME`_COMP_AREF_CURRENT_LOW_USED     (CYDEV_SYSTEM_AREF_CURRENT == CYDEV_SYSTEM_AREF_CURRENT_LOW)

/*******************************************************************************
                                  Parameters
The parameters that are set in the customizer are redefined as constants here.
*******************************************************************************/
#define `$INSTANCE_NAME`_PARAM_VrefSource           (`$VrefSource`uL)
#define `$INSTANCE_NAME`_PARAM_InitialCode          (`$InitialCode`)
#define `$INSTANCE_NAME`_PARAM_OutputBuffer         (`$OutputBuffer`uL)
#define `$INSTANCE_NAME`_PARAM_SampleAndHold        (`$SampleAndHold`uL)
#define `$INSTANCE_NAME`_PARAM_OutputBufferPower    (`$OutputBufferPower`uL)
#define `$INSTANCE_NAME`_PARAM_DacCodeMode          (`$DacCodeMode`uL)
#define `$INSTANCE_NAME`_PARAM_UpdateMode           (`$UpdateMode`uL)
#define `$INSTANCE_NAME`_PARAM_DeepSleep            (`$DeepSleep`uL)
#define `$INSTANCE_NAME`_PARAM_ShowTrig             (`$ShowTrig`uL)
#define `$INSTANCE_NAME`_PARAM_OpAmpUsage           (`$OpAmpUsage`uL)
#define `$INSTANCE_NAME`_PARAM_VrefVoltage_mV       (`$VrefVoltage_mV`uL)
#define `$INSTANCE_NAME`_PARAM_ReferenceBufferUsed  (`$INSTANCE_NAME`_PARAM_VrefSource != `$INSTANCE_NAME`_COMP_REFSOURCE_VDDA)
#define `$INSTANCE_NAME`_PARAM_OutputBufferUsed     (`$INSTANCE_NAME`_PARAM_OutputBuffer > `$INSTANCE_NAME`_COMP_OUTPUT_UNBUFFERED_INTERNAL)

/*******************************************************************************
                            Enumerated Definitions
*******************************************************************************/
/** This enum type is used when calling `$INSTANCE_NAME`_SetSampleAndHold().*/
typedef enum {
    `$INSTANCE_NAME`_SH_DISABLE  = 0u,      /**< Disable sample and hold by disconnecting the S/H capacitor */
    `$INSTANCE_NAME`_SH_SAMPLE   = 1u,      /**< Sample the VDAC output */
    `$INSTANCE_NAME`_SH_HOLD     = 2u,      /**< Hold the VDAC output */
}`$INSTANCE_NAME`_en_sample_hold_t;

/*******************************************************************************
                    Variables with External Linkage
*******************************************************************************/

/** Configuration structure for initializing the CTDAC PDL */
extern `=$CY_CONST_CONFIG ? "const " : ""`cy_stc_ctdac_config_t `$INSTANCE_NAME`_ctdacConfig;

#if `$INSTANCE_NAME`_PARAM_OutputBufferUsed
    /** Configuration structure for initializing Opamp0 of the CTB as the CTDAC output buffer */
    extern `=$CY_CONST_CONFIG ? "const " : ""`cy_stc_ctb_opamp_config_t `$INSTANCE_NAME`_outputBufferConfig;
#endif

#if `$INSTANCE_NAME`_PARAM_ReferenceBufferUsed
    /** Configuration structure for initializing Opamp1 of the CTB as the CTDAC reference buffer */
    extern `=$CY_CONST_CONFIG ? "const " : ""`cy_stc_ctb_opamp_config_t `$INSTANCE_NAME`_refBufferConfig;
#endif

/** Tracks whether block is initialized (1) or not (0). */
extern uint8_t `$INSTANCE_NAME`_initVar;

/**
* \addtogroup group_globals
* \{
*/

/** System power management callback structure for Deep Sleep entry and exit.
* This callback is needed in order to disable deglitching before
* the device enters Deep Sleep. This ensures that the deglitch switches
* are closed and that DAC operation in Deep Sleep, if enabled, is correct.
* The callback also ensures that deglitching is re-enabled when the device wakes up.
* Registering this Deep Sleep callback is needed only if Deep Sleep operation
* is enabled in the Customizer Configure dialog (see \ref customizer_enable_deepsleep).
*
* \snippet SUT_2.cydsn/main_cm4.c SNIPPET_DEEPSLEEP
*/
extern cy_stc_syspm_callback_t `$INSTANCE_NAME`_DeepSleepCallbackStruct;

/** \} group_globals */

/*******************************************************************************
                        CTDAC Configuration Defines
Constants used in the configuration structure for initializing the CTDAC
*******************************************************************************/
#define `$INSTANCE_NAME`_CTDAC_HW                   `=LookupFitterDefine("`$INSTANCE_NAME`_CTDAC__HW")` /**< The pointer to the base address of the CTDAC instance */

#define `$INSTANCE_NAME`_CTDAC_REFSOURCE            ((`$INSTANCE_NAME`_PARAM_VrefSource == `$INSTANCE_NAME`_COMP_REFSOURCE_VDDA) ? \
                                                    CY_CTDAC_REFSOURCE_VDDA : CY_CTDAC_REFSOURCE_EXTERNAL)
#define `$INSTANCE_NAME`_CTDAC_SIGNMODE             ((`$INSTANCE_NAME`_PARAM_DacCodeMode == `$INSTANCE_NAME`_COMP_FORMAT_SIGNED) ? \
                                                    CY_CTDAC_FORMAT_SIGNED : CY_CTDAC_FORMAT_UNSIGNED)
#define `$INSTANCE_NAME`_CTDAC_UPDATEMODE           (cy_en_ctdac_update_t) `$INSTANCE_NAME`_PARAM_UpdateMode
#define `$INSTANCE_NAME`_CTDAC_OUTPUTBUFFER         ((`$INSTANCE_NAME`_PARAM_OutputBuffer <= `$INSTANCE_NAME`_COMP_OUTPUT_UNBUFFERED_INTERNAL) ? \
                                                    CY_CTDAC_OUTPUT_UNBUFFERED : CY_CTDAC_OUTPUT_BUFFERED)
#define `$INSTANCE_NAME`_CTDAC_DEGLITCHMODE         ((`$INSTANCE_NAME`_PARAM_OutputBuffer <= `$INSTANCE_NAME`_COMP_OUTPUT_UNBUFFERED_INTERNAL) ? \
                                                    CY_CTDAC_DEGLITCHMODE_UNBUFFERED : CY_CTDAC_DEGLITCHMODE_BUFFERED)
#define `$INSTANCE_NAME`_CTDAC_DEEPSLEEP            ((`$INSTANCE_NAME`_PARAM_DeepSleep == `$INSTANCE_NAME`_COMP_DEEPSLEEP_OFF) ? \
                                                    CY_CTDAC_DEEPSLEEP_DISABLE : CY_CTDAC_DEEPSLEEP_ENABLE)

#define `$INSTANCE_NAME`_DEGLITCH_TARGET_TIME_NS    (700uL)
#define `$INSTANCE_NAME`_FACTOR_NANO_TO_MICRO       (1000uL)
#define `$INSTANCE_NAME`_DEGLITCH_TARGET_CYCLES     (((CYDEV_CLK_PERICLK__MHZ * `$INSTANCE_NAME`_DEGLITCH_TARGET_TIME_NS) / `$INSTANCE_NAME`_FACTOR_NANO_TO_MICRO) - 1uL)

#if `$INSTANCE_NAME`_PARAM_ReferenceBufferUsed
    #define `$INSTANCE_NAME`_CTB_HW                     `$INSTANCE_NAME`_REFBUF__HW
    #define `$INSTANCE_NAME`_CTB_REFBUF_OPAMP_NUM       CY_CTB_OPAMP_1
    #define `$INSTANCE_NAME`_CTB_REFBUF_POWER           CY_CTB_POWER_MEDIUM
    #define `$INSTANCE_NAME`_CTB_REFBUF_DRIVE           CY_CTB_MODE_OPAMP1X
    #define `$INSTANCE_NAME`_CTB_REFBUF_DEEPSLEEP       ((`$INSTANCE_NAME`_PARAM_DeepSleep == `$INSTANCE_NAME`_COMP_DEEPSLEEP_OFF) ? \
                                                        CY_CTB_DEEPSLEEP_DISABLE : CY_CTB_DEEPSLEEP_ENABLE)
    #if `$INSTANCE_NAME`_COMP_AREF_CURRENT_LOW_USED
        #define `$INSTANCE_NAME`_CTB_REFBUF_PUMP        CY_CTB_PUMP_DISABLE
    #else
        #define `$INSTANCE_NAME`_CTB_REFBUF_PUMP        ((`$INSTANCE_NAME`_PARAM_DeepSleep == `$INSTANCE_NAME`_COMP_DEEPSLEEP_OFF) ? \
                                                        CY_CTB_PUMP_ENABLE : CY_CTB_PUMP_DISABLE)
    #endif
#endif

/*******************************************************************************
                        CTB Configuration Defines
Constants used in the configuration structure for initializing the CTB
*******************************************************************************/
#if `$INSTANCE_NAME`_PARAM_OutputBufferUsed
    #if !defined(`$INSTANCE_NAME`_CTB_HW)
        #define `$INSTANCE_NAME`_CTB_HW                `$INSTANCE_NAME`_VOUTBUF__HW
    #endif
    #define `$INSTANCE_NAME`_CTB_VOUTBUF_OPAMP_NUM      CY_CTB_OPAMP_0
    #define `$INSTANCE_NAME`_CTB_VOUTBUF_POWER          (cy_en_ctb_power_t) `$INSTANCE_NAME`_PARAM_OutputBufferPower
    #define `$INSTANCE_NAME`_CTB_VOUTBUF_DRIVE          ((`$INSTANCE_NAME`_PARAM_OutputBuffer == `$INSTANCE_NAME`_COMP_OUTPUT_BUFFERED_INTERNAL) ? \
                                                            CY_CTB_MODE_OPAMP1X : CY_CTB_MODE_OPAMP10X)
    #define `$INSTANCE_NAME`_CTB_VOUTBUF_DEEPSLEEP      ((`$INSTANCE_NAME`_PARAM_DeepSleep == `$INSTANCE_NAME`_COMP_DEEPSLEEP_OFF) ? \
                                                        CY_CTB_DEEPSLEEP_DISABLE : CY_CTB_DEEPSLEEP_ENABLE)
    #if `$INSTANCE_NAME`_COMP_AREF_CURRENT_LOW_USED
        #define `$INSTANCE_NAME`_CTB_VOUTBUF_PUMP       CY_CTB_PUMP_DISABLE
    #else
        #define `$INSTANCE_NAME`_CTB_VOUTBUF_PUMP       ((`$INSTANCE_NAME`_PARAM_DeepSleep == `$INSTANCE_NAME`_COMP_DEEPSLEEP_OFF) ? \
                                                        CY_CTB_PUMP_ENABLE : CY_CTB_PUMP_DISABLE)
    #endif
#endif

/*******************************************************************************
                        Function Prototypes
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Init(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetValue(int32_t value);
__STATIC_INLINE void `$INSTANCE_NAME`_SetValueBuffered(int32_t value);
__STATIC_INLINE void `$INSTANCE_NAME`_SetSignMode(cy_en_ctdac_format_t signMode);
void `$INSTANCE_NAME`_SetDeepSleepMode(cy_en_ctdac_deep_sleep_t deepSleepMode);

void `$INSTANCE_NAME`_SetSampleAndHold(`$INSTANCE_NAME`_en_sample_hold_t mode);

/**
* \addtogroup group_component
* \{
*/
void `$INSTANCE_NAME`_EasySampleAndHold(void);
/** \} group_component */

__STATIC_INLINE void `$INSTANCE_NAME`_EnableInterrupt(void);
__STATIC_INLINE void `$INSTANCE_NAME`_DisableInterrupt(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void);
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(void);

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Powers up all required hardware blocks. This includes the DAC hardware block
* and CTB hardware block, if used.
* If no opamps are used, the CTB hardware block is untouched.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_CTDAC_Enable(`$INSTANCE_NAME`_CTDAC_HW);

#if (`$INSTANCE_NAME`_PARAM_ReferenceBufferUsed || `$INSTANCE_NAME`_PARAM_OutputBufferUsed)
    Cy_CTB_Enable(`$INSTANCE_NAME`_CTB_HW);
#endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Initializes all required hardware blocks. This includes the DAC hardware block
* and CTB hardware block, if used.
* If no opamps are used, the CTB hardware block is untouched.
*
* This function should only be called once (after reset) and
* does not enable the hardware.
*
* `$INSTANCE_NAME`_Start() is the preferred function to initialize
* and enable the hardware.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Init(void)
{
    (void)Cy_CTDAC_Init(`$INSTANCE_NAME`_CTDAC_HW, &`$INSTANCE_NAME`_ctdacConfig);

#if `$INSTANCE_NAME`_PARAM_ReferenceBufferUsed
    (void)Cy_CTB_OpampInit(`$INSTANCE_NAME`_CTB_HW, `$INSTANCE_NAME`_CTB_REFBUF_OPAMP_NUM, &`$INSTANCE_NAME`_refBufferConfig);
#endif

#if `$INSTANCE_NAME`_PARAM_OutputBufferUsed
    (void)Cy_CTB_OpampInit(`$INSTANCE_NAME`_CTB_HW, `$INSTANCE_NAME`_CTB_VOUTBUF_OPAMP_NUM, &`$INSTANCE_NAME`_outputBufferConfig);
#endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Powers down all required hardware blocks. This includes the DAC hardware block
* and CTB hardware block, if used.
* If no opamps are used, the CTB hardware block is untouched.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void)
{
    Cy_CTDAC_Disable(`$INSTANCE_NAME`_CTDAC_HW);

#if (`$INSTANCE_NAME`_PARAM_ReferenceBufferUsed || `$INSTANCE_NAME`_PARAM_OutputBufferUsed)
    Cy_CTB_Disable(`$INSTANCE_NAME`_CTB_HW);
#endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetValue
****************************************************************************//**
*
* Set the value that the DAC will output on the next Peri clock cycle.
* This function should only be called in the Direct write \ref customizer_update_mode.
*
* Only the least significant 12 bits have an effect.
* Sign extension of negative values is unnecessary and is
* ignored by the hardware. The way in which the DAC interprets the 12-bit
* data is controlled by `$INSTANCE_NAME`_SetSignMode().
*
* \param value
* Value to write into the DAC value register.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetValue(int32_t value)
{
    Cy_CTDAC_SetValue(`$INSTANCE_NAME`_CTDAC_HW, value);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetValueBuffered
****************************************************************************//**
*
* Set the value that the DAC will output on the next DAC clock cycle or strobe
* event, if strobe is enabled.
* This function should be called in all modes except the Direct write \ref customizer_update_mode.
*
* Only the least significant 12 bits have an effect.
* Sign extension of negative values is unnecessary and is
* ignored by the hardware. The way in which the CTDAC interprets the 12-bit
* data is controlled by `$INSTANCE_NAME`_SetSignMode().
*
* \param value
* Value to write into the DAC next value register.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetValueBuffered(int32_t value)
{
    Cy_CTDAC_SetValueBuffered(`$INSTANCE_NAME`_CTDAC_HW, value);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSignMode
****************************************************************************//**
*
* Sets whether to interpret the DAC value as signed or unsigned.
* In unsigned mode, the DAC value register is used without any decoding.
* In signed  mode, the MSB is inverted by adding 0x800 to the DAC value.
* This converts the lowest signed number, 0x800, to the lowest unsigned
* number, 0x000.
*
* \param signMode
* - CY_CTDAC_FORMAT_UNSIGNED: For unsigned mode
* - CY_CTDAC_FORMAT_SIGNED: For signed mode
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetSignMode(cy_en_ctdac_format_t signMode)
{
    Cy_CTDAC_SetSignMode(`$INSTANCE_NAME`_CTDAC_HW, signMode);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableInterrupt
****************************************************************************//**
*
* Enable the DAC interrupt to be forwarded to the CPU interrupt
* controller so that it can be handled by a user function.
*
* Interrupts are available in all \ref customizer_update_mode except Direct write.
* The update mode is configured in the GUI basic tab.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableInterrupt(void)
{
    Cy_CTDAC_SetInterruptMask(`$INSTANCE_NAME`_CTDAC_HW, `$INSTANCE_NAME`_COMP_INTERRUPT_ENABLE);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableInterrupt
****************************************************************************//**
*
* Disable the DAC interrupt to be forwarded to the CPU interrupt
* controller.
*
* Interrupts are available in all \ref customizer_update_mode except Direct write.
* The update mode is configured in the GUI basic tab.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisableInterrupt(void)
{
    Cy_CTDAC_SetInterruptMask(`$INSTANCE_NAME`_CTDAC_HW, `$INSTANCE_NAME`_COMP_INTERRUPT_DISABLE);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
*
* Returns whether the DAC interrupt is configured to be
* forwarded to the CPU interrupt controller or not.
* See `$INSTANCE_NAME`_EnableInterrupt() and `$INSTANCE_NAME`_DisableInterrupt().
*
* Interrupts are available in all \ref customizer_update_mode except Direct write.
* The update mode is configured in the GUI basic tab.
*
* \return
* - 0 = Interrupt is disabled (will not be forwarded to interrupt controller)
* - 1 = Interrupt is enabled (will be forwarded to interrupt controller)
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return Cy_CTDAC_GetInterruptMask(`$INSTANCE_NAME`_CTDAC_HW);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
****************************************************************************//**
*
* Returns the interrupt status which gets set by the hardware
* when the buffered value register, CTDAC_VAL_NXT, is transferred to the
* value register, CTDAC_VAL. Once set, the DAC is ready to accept a new value.
*
* Interrupts are available in all \ref customizer_update_mode except Direct write.
* The update mode is configured in the GUI basic tab.
*
* \return
* - 0 = Value not transferred
* - 1 = Value transferred
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return Cy_CTDAC_GetInterruptStatus(`$INSTANCE_NAME`_CTDAC_HW);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns the bitwise AND of `$INSTANCE_NAME`_GetInterruptStatus() and
* `$INSTANCE_NAME`_GetInterruptMask(). When high, the DAC interrupt is
* asserted and the interrupt is forwarded to the CPU interrupt
* controller.
*
* Interrupts are available in all \ref customizer_update_mode except Direct write.
* The update mode is configured in the GUI basic tab.
*
* \return
* - 0 = Value not transferred or not forwarded to the CPU interrupt controller.
* - 1 = Value transferred and forwarded to the CPU interrupt controller.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return Cy_CTDAC_GetInterruptStatusMasked(`$INSTANCE_NAME`_CTDAC_HW);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
*
* Clears the interrupt that was set by the hardware.
* When using the interrupt, it must be cleared with this function so that
* the hardware can set subsequent interrupts and those interrupts
* can be forwarded to the interrupt controller, if enabled.
*
* Interrupts are available in all \ref customizer_update_mode except Direct write.
* The update mode is configured in the GUI basic tab.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(void)
{
    Cy_CTDAC_ClearInterrupt(`$INSTANCE_NAME`_CTDAC_HW);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
*
* Forces the DAC interrupt to trigger using software.
*
* Interrupts are available in all \ref customizer_update_mode except Direct write.
* The update mode is configured in the GUI basic tab.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(void)
{
    Cy_CTDAC_SetInterrupt(`$INSTANCE_NAME`_CTDAC_HW);
}

#endif /* !defined(CY_`$INSTANCE_NAME`_H) */

/* [] END OF FILE */


