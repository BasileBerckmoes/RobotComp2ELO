/***************************************************************************//**
* \file     `$INSTANCE_NAME`.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* Provides the source code to the API for the `$INSTANCE_NAME` Component.
*
********************************************************************************
* \copyright
* (c) 2017, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#if !defined(CY_`$INSTANCE_NAME`_H)
#define CY_`$INSTANCE_NAME`_H

#include <cy_device_headers.h>
#include <sar/cy_sar.h>

#define `$INSTANCE_NAME`_VREF_ROUTED                  ((`$AdcRoutedVref`) == 1u)
#if (`$INSTANCE_NAME`_VREF_ROUTED)
#include "`$INSTANCE_NAME`_vrefAMux.h"
#endif

#define `$INSTANCE_NAME`_CLOCK_INTERNAL               ((`$AclkMuxSelect`) == 1u)
#if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
#include "`$INSTANCE_NAME`_intSarClock.h"
#endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */

/**
* \addtogroup group_structures
*
*/
typedef struct
{
    uint32_t channelBase;                   /* Start of channels for the configuration */
    uint32_t numChannels;                   /* Number of channels in the configuration */
    const cy_stc_sar_config_t *hwConfigStc; /* PDL structure */
    uint32_t miscConfig;                    /* Miscellaneous configuration bits broken down as follows:
                                            [0] - Freerunning: Set if the sample mode is freerunning
                                            [2] - Mux Switch 0: Set when VSSA is used for the neg input to any single-ended channel
                                            */
#if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
    uint32_t clkDivider;                    /* Clock divider */
#endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */

} `$INSTANCE_NAME`_CONFIG_STRUCT;
/** @} structures */

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void `$INSTANCE_NAME`_SelectConfig(uint32_t config, uint32_t restart);
void `$INSTANCE_NAME`_InitConfig(const `$INSTANCE_NAME`_CONFIG_STRUCT *config);
void `$INSTANCE_NAME`_Init(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);

/**
* \addtogroup group_general
* @{
*/
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_StartEx(cy_israddress userIsr);
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_StartConvert(void);
__STATIC_INLINE void `$INSTANCE_NAME`_StopConvert(void);
void `$INSTANCE_NAME`_SetConvertMode(cy_en_sar_start_convert_sel_t mode);
void `$INSTANCE_NAME`_SetEosMask(uint32_t mask);
uint32_t `$INSTANCE_NAME`_IsEndConversion(cy_en_sar_return_mode_t retMode);
__STATIC_INLINE int16_t `$INSTANCE_NAME`_GetResult16(uint32_t chan);
__STATIC_INLINE int32_t `$INSTANCE_NAME`_GetResult32(uint32_t chan);
__STATIC_INLINE void `$INSTANCE_NAME`_SetLowLimit(uint32_t lowLimit);
__STATIC_INLINE void `$INSTANCE_NAME`_SetHighLimit(uint32_t highLimit);
__STATIC_INLINE void `$INSTANCE_NAME`_SetLimitMask(uint32_t limitMask);
__STATIC_INLINE void `$INSTANCE_NAME`_SetSatMask(uint32_t satMask);
__STATIC_INLINE cy_en_sar_status_t `$INSTANCE_NAME`_SetOffset(uint32_t chan, int16_t offset);
__STATIC_INLINE cy_en_sar_status_t `$INSTANCE_NAME`_SetGain(uint32_t chan, int32_t adcGain);
__STATIC_INLINE float32_t `$INSTANCE_NAME`_CountsTo_Volts(uint32_t chan, int16_t adcCounts);
__STATIC_INLINE int16_t `$INSTANCE_NAME`_CountsTo_mVolts(uint32_t chan, int16_t adcCounts);
__STATIC_INLINE int32_t `$INSTANCE_NAME`_CountsTo_uVolts(uint32_t chan, int16_t adcCounts);

/** @} general */

void `$INSTANCE_NAME`_SetChanMask(uint32_t enableMask);

/**
* \addtogroup group_power
* @{
*/
__STATIC_INLINE void `$INSTANCE_NAME`_Sleep(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Wakeup(void);

/** @} power */

/**
* \addtogroup group_interrupt
* @{
*/
void `$INSTANCE_NAME`_ISR(void);
void `$INSTANCE_NAME`_IRQ_Enable(void);
void `$INSTANCE_NAME`_IRQ_Disable(void);

/** @} interrupt */

/*******************************************************************************
                                  Parameters
The parameters that are set in the customizer are redefined as constants here.
*******************************************************************************/

/*  Sample Mode setting constants */
#define `$INSTANCE_NAME`_TOTAL_CONFIGS                (`$AdcTotalConfigs`ul)

/* ************************************************************************** */
/* Begin configuration 0 customizer defines                                   */
/* ************************************************************************** */

#define `$INSTANCE_NAME`_CFG0_SAMPLE_RATE             (`$Cfg0SampleRate`)
#define `$INSTANCE_NAME`_CFG0_CHANNEL_BASE            (`$Cfg0AdcChannelIndex`u)
#define `$INSTANCE_NAME`_CFG0_CHANNEL_COUNT           (`$Cfg0AdcChannelCount`u)
#define `$INSTANCE_NAME`_CFG0_VREF_SEL_MASK           (`$Cfg0AdcVrefSelMask`u)
#define `$INSTANCE_NAME`_CFG0_NOMINAL_CLOCK_FREQ      (`$Cfg0NominalClockFreq`u)
#define `$INSTANCE_NAME`_CFG0_CHANNEL_EN              (`$Cfg0AdcChannelEnable`u)

/* Sample Control Register */
#define `$INSTANCE_NAME`_CFG0_SINGLE_ENDED_FORMAT     (`$Cfg0AdcSingleEndedFormat`uL)
#define `$INSTANCE_NAME`_CFG0_DIFFERENTIAL_FORMAT     (`$Cfg0AdcDifferentialFormat`uL)
#define `$INSTANCE_NAME`_CFG0_SAMPLES_AVERAGED        (`$Cfg0AdcSamplesAveraged`uL)
#define `$INSTANCE_NAME`_CFG0_RANGE_INTR_MASK         (`$Cfg0AdcSaturateMask`u)
#define `$INSTANCE_NAME`_CFG0_SATURATE_INTR_MASK      (`$Cfg0AdcRangeMask`u)
#define `$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL          (`$Cfg0AdcCtrlVnegSel`)
#define `$INSTANCE_NAME`_CFG0_SINGLE_PRESENT          (`$Cfg0AdcSingleEndedPresent`)
#define `$INSTANCE_NAME`_CFG0_VREF_MV_VALUE           (`$Cfg0AdcVrefVoltageMv`)
#define `$INSTANCE_NAME`_CFG0_APERTURE_TIME0          (`$Cfg0AdcApertureTime0`uL)
#define `$INSTANCE_NAME`_CFG0_APERTURE_TIME1          (`$Cfg0AdcApertureTime1`uL)
#define `$INSTANCE_NAME`_CFG0_APERTURE_TIME2          (`$Cfg0AdcApertureTime2`uL)
#define `$INSTANCE_NAME`_CFG0_APERTURE_TIME3          (`$Cfg0AdcApertureTime3`uL)
#define `$INSTANCE_NAME`_CFG0_FREERUNNING             (`$Cfg0AdcFreeRunning`u)
#define `$INSTANCE_NAME`_CFG0_AVGERAGING_MODE         (`$Cfg0AdcAveragingMode`uL)
#define `$INSTANCE_NAME`_CFG0_LOW_LIMIT               (`$Cfg0AdcRangeLowLimit`u)
#define `$INSTANCE_NAME`_CFG0_HIGH_LIMIT              (`$Cfg0AdcRangeHighLimit`u)
#define `$INSTANCE_NAME`_CFG0_RANGE_COND              (`$Cfg0AdcRangeCondition`uL)
#define `$INSTANCE_NAME`_CFG0_USE_SOC                 (`$Cfg0UseSoc`uL)
#define `$INSTANCE_NAME`_CFG0_VREF_PWR                (`$Cfg0PwrCtrlVref`uL)
#define `$INSTANCE_NAME`_CFG0_COMP_PWR                (`$Cfg0CompPower`uL)
#define `$INSTANCE_NAME`_CFG0_COMP_DLY                (`$Cfg0CompDelay`uL)

/* Clock parameters*/
#if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
    #define `$INSTANCE_NAME`_CFG0_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (`$INSTANCE_NAME`_CFG0_NOMINAL_CLOCK_FREQ)) - 1u)
#endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */

/* ************************************************************************** */
/* End configuration 0 customizer defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 1 customizer defines                                   */
/* ************************************************************************** */

#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 1)
    #define `$INSTANCE_NAME`_CFG1_SAMPLE_RATE             (`$Cfg1SampleRate`)
    #define `$INSTANCE_NAME`_CFG1_CHANNEL_BASE            (`$Cfg1AdcChannelIndex`u)
    #define `$INSTANCE_NAME`_CFG1_CHANNEL_COUNT           (`$Cfg1AdcChannelCount`u)
    #define `$INSTANCE_NAME`_CFG1_VREF_SEL_MASK           (`$Cfg1AdcVrefSelMask`u)
    #define `$INSTANCE_NAME`_CFG1_NOMINAL_CLOCK_FREQ      (`$Cfg1NominalClockFreq`u)
    #define `$INSTANCE_NAME`_CFG1_CHANNEL_EN              (`$Cfg1AdcChannelEnable`u)

    /* Sample Control Register */
    #define `$INSTANCE_NAME`_CFG1_SINGLE_ENDED_FORMAT     (`$Cfg1AdcSingleEndedFormat`uL)
    #define `$INSTANCE_NAME`_CFG1_DIFFERENTIAL_FORMAT     (`$Cfg1AdcDifferentialFormat`uL)
    #define `$INSTANCE_NAME`_CFG1_SAMPLES_AVERAGED        (`$Cfg1AdcSamplesAveraged`uL)
    #define `$INSTANCE_NAME`_CFG1_RANGE_INTR_MASK         (`$Cfg1AdcSaturateMask`u)
    #define `$INSTANCE_NAME`_CFG1_SATURATE_INTR_MASK      (`$Cfg1AdcRangeMask`u)
    #define `$INSTANCE_NAME`_CFG1_VNEG_INPUT_SEL          (`$Cfg1AdcCtrlVnegSel`)
    #define `$INSTANCE_NAME`_CFG1_SINGLE_PRESENT          (`$Cfg1AdcSingleEndedPresent`)
    #define `$INSTANCE_NAME`_CFG1_VREF_MV_VALUE           (`$Cfg1AdcVrefVoltageMv`)
    #define `$INSTANCE_NAME`_CFG1_APERTURE_TIME0          (`$Cfg1AdcApertureTime0`uL)
    #define `$INSTANCE_NAME`_CFG1_APERTURE_TIME1          (`$Cfg1AdcApertureTime1`uL)
    #define `$INSTANCE_NAME`_CFG1_APERTURE_TIME2          (`$Cfg1AdcApertureTime2`uL)
    #define `$INSTANCE_NAME`_CFG1_APERTURE_TIME3          (`$Cfg1AdcApertureTime3`uL)
    #define `$INSTANCE_NAME`_CFG1_FREERUNNING             (`$Cfg1AdcFreeRunning`u)
    #define `$INSTANCE_NAME`_CFG1_AVGERAGING_MODE         (`$Cfg1AdcAveragingMode`uL)
    #define `$INSTANCE_NAME`_CFG1_LOW_LIMIT               (`$Cfg1AdcRangeLowLimit`u)
    #define `$INSTANCE_NAME`_CFG1_HIGH_LIMIT              (`$Cfg1AdcRangeHighLimit`u)
    #define `$INSTANCE_NAME`_CFG1_RANGE_COND              (`$Cfg1AdcRangeCondition`uL)
    #define `$INSTANCE_NAME`_CFG1_USE_SOC                 (`$Cfg1UseSoc`uL)
    #define `$INSTANCE_NAME`_CFG1_VREF_PWR                (`$Cfg1PwrCtrlVref`uL)
    #define `$INSTANCE_NAME`_CFG1_COMP_PWR                (`$Cfg1CompPower`uL)
    #define `$INSTANCE_NAME`_CFG1_COMP_DLY                (`$Cfg1CompDelay`uL)

    /* Clock parameters*/
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        #define `$INSTANCE_NAME`_CFG1_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (`$INSTANCE_NAME`_CFG1_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */
#endif /* #if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 1) */

/* ************************************************************************** */
/* End configuration 1 customizer defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 2 customizer defines                                         */
/* ************************************************************************** */

#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 2)
    #define `$INSTANCE_NAME`_CFG2_SAMPLE_RATE             (`$Cfg2SampleRate`)
    #define `$INSTANCE_NAME`_CFG2_CHANNEL_BASE            (`$Cfg2AdcChannelIndex`u)
    #define `$INSTANCE_NAME`_CFG2_CHANNEL_COUNT           (`$Cfg2AdcChannelCount`u)
    #define `$INSTANCE_NAME`_CFG2_VREF_SEL_MASK           (`$Cfg2AdcVrefSelMask`u)
    #define `$INSTANCE_NAME`_CFG2_NOMINAL_CLOCK_FREQ      (`$Cfg2NominalClockFreq`u)
    #define `$INSTANCE_NAME`_CFG2_CHANNEL_EN              (`$Cfg2AdcChannelEnable`u)

    /* Sample Control Register */
    #define `$INSTANCE_NAME`_CFG2_SINGLE_ENDED_FORMAT     (`$Cfg2AdcSingleEndedFormat`uL)
    #define `$INSTANCE_NAME`_CFG2_DIFFERENTIAL_FORMAT     (`$Cfg2AdcDifferentialFormat`uL)
    #define `$INSTANCE_NAME`_CFG2_SAMPLES_AVERAGED        (`$Cfg2AdcSamplesAveraged`uL)
    #define `$INSTANCE_NAME`_CFG2_RANGE_INTR_MASK         (`$Cfg2AdcSaturateMask`u)
    #define `$INSTANCE_NAME`_CFG2_SATURATE_INTR_MASK      (`$Cfg2AdcRangeMask`u)
    #define `$INSTANCE_NAME`_CFG2_VNEG_INPUT_SEL          (`$Cfg2AdcCtrlVnegSel`)
    #define `$INSTANCE_NAME`_CFG2_SINGLE_PRESENT          (`$Cfg2AdcSingleEndedPresent`)
    #define `$INSTANCE_NAME`_CFG2_VREF_MV_VALUE           (`$Cfg2AdcVrefVoltageMv`)
    #define `$INSTANCE_NAME`_CFG2_APERTURE_TIME0          (`$Cfg2AdcApertureTime0`uL)
    #define `$INSTANCE_NAME`_CFG2_APERTURE_TIME1          (`$Cfg2AdcApertureTime1`uL)
    #define `$INSTANCE_NAME`_CFG2_APERTURE_TIME2          (`$Cfg2AdcApertureTime2`uL)
    #define `$INSTANCE_NAME`_CFG2_APERTURE_TIME3          (`$Cfg2AdcApertureTime3`uL)
    #define `$INSTANCE_NAME`_CFG2_FREERUNNING             (`$Cfg2AdcFreeRunning`u)
    #define `$INSTANCE_NAME`_CFG2_AVGERAGING_MODE         (`$Cfg2AdcAveragingMode`uL)
    #define `$INSTANCE_NAME`_CFG2_LOW_LIMIT               (`$Cfg2AdcRangeLowLimit`u)
    #define `$INSTANCE_NAME`_CFG2_HIGH_LIMIT              (`$Cfg2AdcRangeHighLimit`u)
    #define `$INSTANCE_NAME`_CFG2_RANGE_COND              (`$Cfg2AdcRangeCondition`uL)
    #define `$INSTANCE_NAME`_CFG2_USE_SOC                 (`$Cfg2UseSoc`uL)
    #define `$INSTANCE_NAME`_CFG2_VREF_PWR                (`$Cfg2PwrCtrlVref`uL)
    #define `$INSTANCE_NAME`_CFG2_COMP_PWR                (`$Cfg2CompPower`uL)
    #define `$INSTANCE_NAME`_CFG2_COMP_DLY                (`$Cfg2CompDelay`uL)

    /* Clock parameters*/
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        #define `$INSTANCE_NAME`_CFG2_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (`$INSTANCE_NAME`_CFG2_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */
#endif /* (`$INSTANCE_NAME`_TOTAL_CONFIGS > 2) */


/* ************************************************************************** */
/* End configuration 2 customizer defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 3 customizer defines                                   */
/* ************************************************************************** */
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 3)
    #define `$INSTANCE_NAME`_CFG3_SAMPLE_RATE             (`$Cfg3SampleRate`)
    #define `$INSTANCE_NAME`_CFG3_CHANNEL_BASE            (`$Cfg3AdcChannelIndex`u)
    #define `$INSTANCE_NAME`_CFG3_CHANNEL_COUNT           (`$Cfg3AdcChannelCount`u)
    #define `$INSTANCE_NAME`_CFG3_VREF_SEL_MASK           (`$Cfg3AdcVrefSelMask`u)
    #define `$INSTANCE_NAME`_CFG3_NOMINAL_CLOCK_FREQ      (`$Cfg3NominalClockFreq`u)
    #define `$INSTANCE_NAME`_CFG3_CHANNEL_EN              (`$Cfg3AdcChannelEnable`u)

    /* Sample Control Register */
    #define `$INSTANCE_NAME`_CFG3_SINGLE_ENDED_FORMAT     (`$Cfg3AdcSingleEndedFormat`uL)
    #define `$INSTANCE_NAME`_CFG3_DIFFERENTIAL_FORMAT     (`$Cfg3AdcDifferentialFormat`uL)
    #define `$INSTANCE_NAME`_CFG3_SAMPLES_AVERAGED        (`$Cfg3AdcSamplesAveraged`uL)
    #define `$INSTANCE_NAME`_CFG3_RANGE_INTR_MASK         (`$Cfg3AdcSaturateMask`u)
    #define `$INSTANCE_NAME`_CFG3_SATURATE_INTR_MASK      (`$Cfg3AdcRangeMask`u)
    #define `$INSTANCE_NAME`_CFG3_VNEG_INPUT_SEL          (`$Cfg3AdcCtrlVnegSel`)
    #define `$INSTANCE_NAME`_CFG3_SINGLE_PRESENT          (`$Cfg3AdcSingleEndedPresent`)
    #define `$INSTANCE_NAME`_CFG3_VREF_MV_VALUE           (`$Cfg3AdcVrefVoltageMv`)
    #define `$INSTANCE_NAME`_CFG3_APERTURE_TIME0          (`$Cfg3AdcApertureTime0`uL)
    #define `$INSTANCE_NAME`_CFG3_APERTURE_TIME1          (`$Cfg3AdcApertureTime1`uL)
    #define `$INSTANCE_NAME`_CFG3_APERTURE_TIME2          (`$Cfg3AdcApertureTime2`uL)
    #define `$INSTANCE_NAME`_CFG3_APERTURE_TIME3          (`$Cfg3AdcApertureTime3`uL)
    #define `$INSTANCE_NAME`_CFG3_FREERUNNING             (`$Cfg3AdcFreeRunning`u)
    #define `$INSTANCE_NAME`_CFG3_AVGERAGING_MODE         (`$Cfg3AdcAveragingMode`uL)
    #define `$INSTANCE_NAME`_CFG3_LOW_LIMIT               (`$Cfg3AdcRangeLowLimit`u)
    #define `$INSTANCE_NAME`_CFG3_HIGH_LIMIT              (`$Cfg3AdcRangeHighLimit`u)
    #define `$INSTANCE_NAME`_CFG3_RANGE_COND              (`$Cfg3AdcRangeCondition`uL)
    #define `$INSTANCE_NAME`_CFG3_USE_SOC                 (`$Cfg3UseSoc`uL)
    #define `$INSTANCE_NAME`_CFG3_VREF_PWR                (`$Cfg3PwrCtrlVref`uL)
    #define `$INSTANCE_NAME`_CFG3_COMP_PWR                (`$Cfg3CompPower`uL)
    #define `$INSTANCE_NAME`_CFG3_COMP_DLY                (`$Cfg3CompDelay`uL)

    /* Clock parameters*/
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        #define `$INSTANCE_NAME`_CFG3_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (`$INSTANCE_NAME`_CFG3_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */
#endif /* (`$INSTANCE_NAME`_TOTAL_CONFIGS > 3) */

/* ************************************************************************** */
/* End configuration 3 customizer defines                                     */
/* ************************************************************************** */

#define `$INSTANCE_NAME`_DEFAULT_SAMPLE_MODE_SEL      (0u)
#define `$INSTANCE_NAME`_FREERUNNING                  (1u)
#define `$INSTANCE_NAME`_HARDWARESOC                  (1u)
#define `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN          (0x0uL)
#define `$INSTANCE_NAME`_NEG_SEL_VREF                 (0x7uL)
#define `$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR     (0x0uL)

/** `$INSTANCE_NAME`_TOTAL_CHANNELS_NUM
* This constant represents the number of input channels available for scanning.
*/
#define `$INSTANCE_NAME`_TOTAL_CHANNELS_NUM           (`$AdcTotalChannels`u)

/*******************************************************************************
*    Variables with External Linkage
*******************************************************************************/
/**
* \addtogroup group_globals
* Globals are noted in the descriptions of the functions that use globals.
* They are marked with (R), (W), or (RW) noting whether the variable is read,
* write, or read/write.
* @{
*/

/** `$INSTANCE_NAME`_initVar
* The `$INSTANCE_NAME`_initVar variable is used to indicate
* initial configuration of this component. The variable is initialized to zero and
* set to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows for
* component initialization without reinitialization in all subsequent calls to the
* `$INSTANCE_NAME`_Start() routine.
*
* If reinitialization of the component is required, then the `$INSTANCE_NAME`_Init() function
* can be called before the `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_Enable()
* functions.
*/
extern uint8_t `$INSTANCE_NAME`_initVar;
extern uint8_t `$INSTANCE_NAME`_selected;
extern uint32_t `$INSTANCE_NAME`_currentConfig;

#define `$INSTANCE_NAME`_INIT_VAR_INIT_FLAG     (0x01u)

extern const `$INSTANCE_NAME`_CONFIG_STRUCT `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_TOTAL_CONFIGS];

/* SysPm callback structure for deep sleep entry and exit.
 * Call the Cy_SysPm_RegisterCallback function with this
 * structure before calling Cy_SysPm_DeepSleep.
*/
extern cy_stc_syspm_callback_t `$INSTANCE_NAME`_DeepSleepCallbackStruct;

/** @} globals */

/* ************************************************************************** */
/* *******************Global MUX_SWITCH0 Definitions ************************ */
/* ************************************************************************** */
#if(`$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) && (`$INSTANCE_NAME`_CFG0_SINGLE_PRESENT == 0u))
        #define `$INSTANCE_NAME`_MUX_SWITCH0_INIT      0u
    #else    /* multiple channels or one single ended channel */
        #define `$INSTANCE_NAME`_MUX_SWITCH0_INIT      1u
    #endif /* ((`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) && (`$INSTANCE_NAME`_CFG0_SINGLE_PRESENT == 0u)) */
#else
    #define `$INSTANCE_NAME`_MUX_SWITCH0_INIT          0u
#endif /* `$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

/* ************************************************************************** */
/* Begin configuration 0 calculated defines                                   */
/* ************************************************************************** */
#define `$INSTANCE_NAME`_CFG0_SAMPLE_TIME01_INIT \
        ((`$INSTANCE_NAME`_CFG0_APERTURE_TIME0 \
        << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
        | (`$INSTANCE_NAME`_CFG0_APERTURE_TIME1 \
        << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

#define `$INSTANCE_NAME`_CFG0_SAMPLE_TIME23_INIT \
        ((`$INSTANCE_NAME`_CFG0_APERTURE_TIME2 \
        << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
        | (`$INSTANCE_NAME`_CFG0_APERTURE_TIME3 \
        << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

/* Enable soc pin if used */
#define `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_EN_INIT \
        (`$INSTANCE_NAME`_CFG0_USE_SOC \
        << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

/* Set soc operation to edge or level based on sample mode */
#if(`$INSTANCE_NAME`_CFG0_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
    #define `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
#else /* Edge trigger */
    #define `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_LEVEL_INIT    (0u)
#endif /* End `$INSTANCE_NAME`_CFG0_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

/* Set SE_NEG_INPUT */
#if(`$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
    #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
#elif(`$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)

    /* Do not connect VNEG to VREF when one channel in differential mode used */
    /* Only needed for config 0 since 2+ configs == 2+ channels */
    #if((`$INSTANCE_NAME`_CFG0_CHANNEL_COUNT == 1u) && (`$INSTANCE_NAME`_CFG0_SINGLE_PRESENT == 0u))
        #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT     0u
    #else    /* multiple channels or one single channel */
        #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                            << SAR_CTRL_NEG_SEL_Pos )
    #endif /* (`$INSTANCE_NAME`_CFG0_CHANNEL_COUNT == 1u) && (`$INSTANCE_NAME`_CFG0_CHANNELS_MODE != 0u) */
#elif (`$INSTANCE_NAME`_CFG0_SINGLE_PRESENT != 0u)
    #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG0_NEG_OTHER
#else
    #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT         0u
#endif /* `$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

#if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM > 1u)
    #define `$INSTANCE_NAME`_CFG0_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_SARMUX__VNEG0 << SAR_CTRL_NEG_SEL_Pos)
    #define `$INSTANCE_NAME`_CFG0_SWITCH_CONF_INIT          0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define `$INSTANCE_NAME`_CFG0_SWITCH_CONF_INIT          SAR_CTRL_SWITCH_DISABLE_Msk
    #define `$INSTANCE_NAME`_CFG0_NEG_OTHER                 0u
#endif /* `$INSTANCE_NAME`_CFG0_CHANNEL_COUNT > 1u */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u)
    #define `$INSTANCE_NAME`_CFG0_HW_CTRL_NEGVREF_INIT      0u
#else
    #define `$INSTANCE_NAME`_CFG0_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk
#endif /* `$INSTANCE_NAME`_CFG0_CHANNEL_COUNT == 1u */

#define `$INSTANCE_NAME`_CFG0_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

/* SAMPLE_CTRL initial values */
#define `$INSTANCE_NAME`_CFG0_SE_RESULT_FORMAT_INIT \
        (`$INSTANCE_NAME`_CFG0_SINGLE_ENDED_FORMAT \
        << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

#define `$INSTANCE_NAME`_CFG0_DIFF_RESULT_FORMAT_INIT \
        (`$INSTANCE_NAME`_CFG0_DIFFERENTIAL_FORMAT \
        << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

#define `$INSTANCE_NAME`_CFG0_AVG_SAMPLES_NUM_INIT \
        (`$INSTANCE_NAME`_CFG0_SAMPLES_AVERAGED \
        << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

/* Combination of Average Mode and Average Shift */
#define `$INSTANCE_NAME`_CFG0_AVG_MODE_INIT \
        (`$INSTANCE_NAME`_CFG0_AVGERAGING_MODE \
        << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

#define `$INSTANCE_NAME`_CFG0_TRIGGER_OUT_INIT      (0u)
#define `$INSTANCE_NAME`_CFG0_UAB_SCAN_MODE_INIT    (0u)

#define `$INSTANCE_NAME`_CFG0_VREF_POWER_INIT  \
        (`$INSTANCE_NAME`_CFG0_VREF_PWR \
        << SAR_CTRL_PWR_CTRL_VREF_Pos)

#define `$INSTANCE_NAME`_CFG0_COMP_PWR_INIT  \
        (`$INSTANCE_NAME`_CFG0_COMP_PWR \
        << SAR_CTRL_COMP_PWR_Pos)

#define `$INSTANCE_NAME`_CFG0_COMP_DLY_INIT  \
        (`$INSTANCE_NAME`_CFG0_COMP_DLY \
        << SAR_CTRL_COMP_DLY_Pos)

#define `$INSTANCE_NAME`_CFG0_CTRL_INIT  \
        (`$INSTANCE_NAME`_CFG0_VREF_POWER_INIT \
        | `$INSTANCE_NAME`_CFG0_VREF_SEL_MASK \
        | `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT \
        | `$INSTANCE_NAME`_CFG0_HW_CTRL_NEGVREF_INIT \
        | `$INSTANCE_NAME`_CFG0_COMP_DLY_INIT \
        | SAR_CTRL_REFBUF_EN_Msk \
        | `$INSTANCE_NAME`_CFG0_COMP_PWR_INIT \
        | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
        | `$INSTANCE_NAME`_CFG0_SWITCH_CONF_INIT )

#define `$INSTANCE_NAME`_CFG0_SAMPLE_CTRL_INIT \
        (`$INSTANCE_NAME`_CFG0_SE_RESULT_FORMAT_INIT \
        | `$INSTANCE_NAME`_CFG0_DIFF_RESULT_FORMAT_INIT \
        | `$INSTANCE_NAME`_CFG0_AVG_SAMPLES_NUM_INIT \
        | `$INSTANCE_NAME`_CFG0_AVG_MODE_INIT \
        | `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_LEVEL_INIT \
        | `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_EN_INIT \
        | `$INSTANCE_NAME`_CFG0_UAB_SCAN_MODE_INIT \
        | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
        | `$INSTANCE_NAME`_CFG0_TRIGGER_OUT_INIT \
        | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
)

#define `$INSTANCE_NAME`_CFG0_RANGE_THRES_INIT \
        (`$INSTANCE_NAME`_CFG0_LOW_LIMIT \
        | (uint32)((uint32)`$INSTANCE_NAME`_CFG0_HIGH_LIMIT \
        << SAR_RANGE_THRES_RANGE_HIGH_Pos))

#define `$INSTANCE_NAME`_CFG0_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)`$INSTANCE_NAME`_CFG0_RANGE_COND

/* Misc Config
    [0] - Freerunning: Set if the sample mode is freerunning
*/
#define `$INSTANCE_NAME`_CFG0_MISC_CONFIG_INIT \
        (`$INSTANCE_NAME`_CFG0_FREERUNNING)

/* ************************************************************************** */
/* End configuration 0 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 1 calculated defines                                   */
/* ************************************************************************** */
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 1)
    #define `$INSTANCE_NAME`_CFG1_SAMPLE_TIME01_INIT \
            ((`$INSTANCE_NAME`_CFG1_APERTURE_TIME0 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
            | (`$INSTANCE_NAME`_CFG1_APERTURE_TIME1 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

    #define `$INSTANCE_NAME`_CFG1_SAMPLE_TIME23_INIT \
            ((`$INSTANCE_NAME`_CFG1_APERTURE_TIME2 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
            | (`$INSTANCE_NAME`_CFG1_APERTURE_TIME3 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

    /* Enable soc pin if used */
    #define `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_EN_INIT \
            (`$INSTANCE_NAME`_CFG1_USE_SOC \
            << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

    /* Set soc operation to edge or level based on sample mode */
    #if(`$INSTANCE_NAME`_CFG1_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
        #define `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
    #else /* Edge trigger */
        #define `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End `$INSTANCE_NAME`_CFG1_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

    /* Set SE_NEG_INPUT */
    #if(`$INSTANCE_NAME`_CFG1_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
    #elif(`$INSTANCE_NAME`_CFG1_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                            << SAR_CTRL_NEG_SEL_Pos )
    #elif (`$INSTANCE_NAME`_CFG1_SINGLE_PRESENT != 0u)
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG1_NEG_OTHER
    #else
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT         0u
    #endif /* `$INSTANCE_NAME`_CFG1_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

    #define `$INSTANCE_NAME`_CFG1_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_SARMUX__VNEG1 << SAR_CTRL_NEG_SEL_Pos)
    #define `$INSTANCE_NAME`_CFG1_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define `$INSTANCE_NAME`_CFG1_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk

    #define `$INSTANCE_NAME`_CFG1_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define `$INSTANCE_NAME`_CFG1_SE_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG1_SINGLE_ENDED_FORMAT \
            << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

    #define `$INSTANCE_NAME`_CFG1_DIFF_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG1_DIFFERENTIAL_FORMAT \
            << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

    #define `$INSTANCE_NAME`_CFG1_AVG_SAMPLES_NUM_INIT \
            (`$INSTANCE_NAME`_CFG1_SAMPLES_AVERAGED \
            << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

    /* Combination of Average Mode and Average Shift */
    #define `$INSTANCE_NAME`_CFG1_AVG_MODE_INIT \
            (`$INSTANCE_NAME`_CFG1_AVGERAGING_MODE \
            << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

    #define `$INSTANCE_NAME`_CFG1_TRIGGER_OUT_INIT      (0u)
    #define `$INSTANCE_NAME`_CFG1_UAB_SCAN_MODE_INIT    (0u)

    #define `$INSTANCE_NAME`_CFG1_VREF_POWER_INIT  \
            (`$INSTANCE_NAME`_CFG1_VREF_PWR \
            << SAR_CTRL_PWR_CTRL_VREF_Pos)

    #define `$INSTANCE_NAME`_CFG1_COMP_PWR_INIT  \
            (`$INSTANCE_NAME`_CFG1_COMP_PWR \
            << SAR_CTRL_COMP_PWR_Pos)

    #define `$INSTANCE_NAME`_CFG1_COMP_DLY_INIT  \
            (`$INSTANCE_NAME`_CFG1_COMP_DLY \
            << SAR_CTRL_COMP_DLY_Pos)

    #define `$INSTANCE_NAME`_CFG1_CTRL_INIT  \
            (`$INSTANCE_NAME`_CFG1_VREF_POWER_INIT \
            | `$INSTANCE_NAME`_CFG1_VREF_SEL_MASK \
            | `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT \
            | `$INSTANCE_NAME`_CFG1_HW_CTRL_NEGVREF_INIT \
            | `$INSTANCE_NAME`_CFG1_COMP_DLY_INIT \
            | SAR_CTRL_REFBUF_EN_Msk \
            | `$INSTANCE_NAME`_CFG1_COMP_PWR_INIT \
            | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
            | `$INSTANCE_NAME`_CFG1_SWITCH_CONF_INIT )

    #define `$INSTANCE_NAME`_CFG1_SAMPLE_CTRL_INIT \
            (`$INSTANCE_NAME`_CFG1_SE_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG1_DIFF_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG1_AVG_SAMPLES_NUM_INIT \
            | `$INSTANCE_NAME`_CFG1_AVG_MODE_INIT \
            | `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_LEVEL_INIT \
            | `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_EN_INIT \
            | `$INSTANCE_NAME`_CFG1_UAB_SCAN_MODE_INIT \
            | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
            | `$INSTANCE_NAME`_CFG1_TRIGGER_OUT_INIT \
            | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
    )

    #define `$INSTANCE_NAME`_CFG1_RANGE_THRES_INIT \
            (`$INSTANCE_NAME`_CFG1_LOW_LIMIT \
            | (uint32)((uint32)`$INSTANCE_NAME`_CFG1_HIGH_LIMIT \
            << SAR_RANGE_THRES_RANGE_HIGH_Pos))

    #define `$INSTANCE_NAME`_CFG1_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)`$INSTANCE_NAME`_CFG1_RANGE_COND

    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
    */
    #define `$INSTANCE_NAME`_CFG1_MISC_CONFIG_INIT \
            (`$INSTANCE_NAME`_CFG1_FREERUNNING)
#endif /* `$INSTANCE_NAME`_TOTAL_CONFIGS > 1 */

/* ************************************************************************** */
/* End configuration 1 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 2 calculated defines                                   */
/* ************************************************************************** */
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 2)
    #define `$INSTANCE_NAME`_CFG2_SAMPLE_TIME01_INIT \
            ((`$INSTANCE_NAME`_CFG2_APERTURE_TIME0 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
            | (`$INSTANCE_NAME`_CFG2_APERTURE_TIME1 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

    #define `$INSTANCE_NAME`_CFG2_SAMPLE_TIME23_INIT \
            ((`$INSTANCE_NAME`_CFG2_APERTURE_TIME2 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
            | (`$INSTANCE_NAME`_CFG2_APERTURE_TIME3 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

    /* Enable soc pin if used */
    #define `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_EN_INIT \
            (`$INSTANCE_NAME`_CFG2_USE_SOC \
            << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

    /* Set soc operation to edge or level based on sample mode */
    #if(`$INSTANCE_NAME`_CFG2_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
        #define `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
    #else /* Edge trigger */
        #define `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End `$INSTANCE_NAME`_CFG2_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

    /* Set SE_NEG_INPUT */
    #if(`$INSTANCE_NAME`_CFG2_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
    #elif(`$INSTANCE_NAME`_CFG2_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                                << SAR_CTRL_NEG_SEL_Pos )
    #elif (`$INSTANCE_NAME`_CFG2_SINGLE_PRESENT != 0u)
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG2_NEG_OTHER
    #else
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT         0u
    #endif /* `$INSTANCE_NAME`_CFG2_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

   #define `$INSTANCE_NAME`_CFG2_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_SARMUX__VNEG2 << SAR_CTRL_NEG_SEL_Pos)

    #define `$INSTANCE_NAME`_CFG2_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define `$INSTANCE_NAME`_CFG2_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk

    #define `$INSTANCE_NAME`_CFG2_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define `$INSTANCE_NAME`_CFG2_SE_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG2_SINGLE_ENDED_FORMAT \
            << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

    #define `$INSTANCE_NAME`_CFG2_DIFF_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG2_DIFFERENTIAL_FORMAT \
            << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

    #define `$INSTANCE_NAME`_CFG2_AVG_SAMPLES_NUM_INIT \
            (`$INSTANCE_NAME`_CFG2_SAMPLES_AVERAGED \
            << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

    /* Combination of Average Mode and Average Shift */
    #define `$INSTANCE_NAME`_CFG2_AVG_MODE_INIT \
            (`$INSTANCE_NAME`_CFG2_AVGERAGING_MODE \
            << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

    #define `$INSTANCE_NAME`_CFG2_TRIGGER_OUT_INIT      (0u)
    #define `$INSTANCE_NAME`_CFG2_UAB_SCAN_MODE_INIT    (0u)


    #define `$INSTANCE_NAME`_CFG2_VREF_POWER_INIT  \
            (`$INSTANCE_NAME`_CFG2_VREF_PWR \
            << SAR_CTRL_PWR_CTRL_VREF_Pos)

    #define `$INSTANCE_NAME`_CFG2_COMP_PWR_INIT  \
            (`$INSTANCE_NAME`_CFG2_COMP_PWR \
            << SAR_CTRL_COMP_PWR_Pos)

    #define `$INSTANCE_NAME`_CFG2_COMP_DLY_INIT  \
            (`$INSTANCE_NAME`_CFG2_COMP_DLY \
            << SAR_CTRL_COMP_DLY_Pos)

    #define `$INSTANCE_NAME`_CFG2_CTRL_INIT  \
            (`$INSTANCE_NAME`_CFG2_VREF_POWER_INIT \
            | `$INSTANCE_NAME`_CFG2_VREF_SEL_MASK \
            | `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT \
            | `$INSTANCE_NAME`_CFG2_HW_CTRL_NEGVREF_INIT \
            | `$INSTANCE_NAME`_CFG2_COMP_DLY_INIT \
            | SAR_CTRL_REFBUF_EN_Msk \
            | `$INSTANCE_NAME`_CFG2_COMP_PWR_INIT \
            | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
            | `$INSTANCE_NAME`_CFG2_SWITCH_CONF_INIT )


    #define `$INSTANCE_NAME`_CFG2_SAMPLE_CTRL_INIT \
            (`$INSTANCE_NAME`_CFG2_SE_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG2_DIFF_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG2_AVG_SAMPLES_NUM_INIT \
            | `$INSTANCE_NAME`_CFG2_AVG_MODE_INIT \
            | `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_LEVEL_INIT \
            | `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_EN_INIT \
            | `$INSTANCE_NAME`_CFG2_UAB_SCAN_MODE_INIT \
            | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
            | `$INSTANCE_NAME`_CFG2_TRIGGER_OUT_INIT \
            | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
    )

    #define `$INSTANCE_NAME`_CFG2_RANGE_THRES_INIT \
            (`$INSTANCE_NAME`_CFG2_LOW_LIMIT \
            | (uint32)((uint32)`$INSTANCE_NAME`_CFG2_HIGH_LIMIT \
            << SAR_RANGE_THRES_RANGE_HIGH_Pos))

    #define `$INSTANCE_NAME`_CFG2_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)`$INSTANCE_NAME`_CFG2_RANGE_COND

    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
    */
    #define `$INSTANCE_NAME`_CFG2_MISC_CONFIG_INIT \
            (`$INSTANCE_NAME`_CFG2_FREERUNNING)
#endif /* `$INSTANCE_NAME`_TOTAL_CONFIGS > 2 */

/* ************************************************************************** */
/* End configuration 2 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 3 calculated defines                                   */
/* ************************************************************************** */
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 3)
    #define `$INSTANCE_NAME`_CFG3_SAMPLE_TIME01_INIT \
            ((`$INSTANCE_NAME`_CFG3_APERTURE_TIME0 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
            | (`$INSTANCE_NAME`_CFG3_APERTURE_TIME1 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

    #define `$INSTANCE_NAME`_CFG3_SAMPLE_TIME23_INIT \
            ((`$INSTANCE_NAME`_CFG3_APERTURE_TIME2 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
            | (`$INSTANCE_NAME`_CFG3_APERTURE_TIME3 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

    /* Enable soc pin if used */
    #define `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_EN_INIT \
            (`$INSTANCE_NAME`_CFG3_USE_SOC \
             << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

    /* Set soc operation to edge or level based on sample mode */
    #if(`$INSTANCE_NAME`_CFG3_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
        #define `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
    #else /* Edge trigger */
        #define `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End `$INSTANCE_NAME`_CFG3_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

    /* Set SE_NEG_INPUT  */
    #if(`$INSTANCE_NAME`_CFG3_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
    #elif(`$INSTANCE_NAME`_CFG3_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                                << SAR_CTRL_NEG_SEL_Pos )
    #elif (`$INSTANCE_NAME`_CFG3_SINGLE_PRESENT != 0u)
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG3_NEG_OTHER
    #else
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT         0u
    #endif /* `$INSTANCE_NAME`_CFG3_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

    #define `$INSTANCE_NAME`_CFG3_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_SARMUX__VNEG3 << SAR_CTRL_NEG_SEL_Pos)

    #define `$INSTANCE_NAME`_CFG3_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define `$INSTANCE_NAME`_CFG3_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk

    #define `$INSTANCE_NAME`_CFG3_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define `$INSTANCE_NAME`_CFG3_SE_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG3_SINGLE_ENDED_FORMAT \
            << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

    #define `$INSTANCE_NAME`_CFG3_DIFF_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG3_DIFFERENTIAL_FORMAT \
            << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

    #define `$INSTANCE_NAME`_CFG3_AVG_SAMPLES_NUM_INIT \
            (`$INSTANCE_NAME`_CFG3_SAMPLES_AVERAGED \
            << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

    /* Combination of Average Mode and Average Shift */
    #define `$INSTANCE_NAME`_CFG3_AVG_MODE_INIT \
            (`$INSTANCE_NAME`_CFG3_AVGERAGING_MODE \
            << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

    #define `$INSTANCE_NAME`_CFG3_TRIGGER_OUT_INIT      (0u)
    #define `$INSTANCE_NAME`_CFG3_UAB_SCAN_MODE_INIT    (0u)

    #define `$INSTANCE_NAME`_CFG3_VREF_POWER_INIT  \
            (`$INSTANCE_NAME`_CFG3_VREF_PWR \
            << SAR_CTRL_PWR_CTRL_VREF_Pos)

    #define `$INSTANCE_NAME`_CFG3_COMP_PWR_INIT  \
            (`$INSTANCE_NAME`_CFG3_COMP_PWR \
            << SAR_CTRL_COMP_PWR_Pos)

    #define `$INSTANCE_NAME`_CFG3_COMP_DLY_INIT  \
            (`$INSTANCE_NAME`_CFG3_COMP_DLY \
            << SAR_CTRL_COMP_DLY_Pos)

    #define `$INSTANCE_NAME`_CFG3_CTRL_INIT  \
            (`$INSTANCE_NAME`_CFG3_VREF_POWER_INIT \
            | `$INSTANCE_NAME`_CFG3_VREF_SEL_MASK \
            | `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT \
            | `$INSTANCE_NAME`_CFG3_HW_CTRL_NEGVREF_INIT \
            | `$INSTANCE_NAME`_CFG3_COMP_DLY_INIT \
            | SAR_CTRL_REFBUF_EN_Msk \
            | `$INSTANCE_NAME`_CFG3_COMP_PWR_INIT \
            | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
            | `$INSTANCE_NAME`_CFG3_SWITCH_CONF_INIT )


    #define `$INSTANCE_NAME`_CFG3_SAMPLE_CTRL_INIT \
            (`$INSTANCE_NAME`_CFG3_SE_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG3_DIFF_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG3_AVG_SAMPLES_NUM_INIT \
            | `$INSTANCE_NAME`_CFG3_AVG_MODE_INIT \
            | `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_LEVEL_INIT \
            | `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_EN_INIT \
            | `$INSTANCE_NAME`_CFG3_UAB_SCAN_MODE_INIT \
            | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
            | `$INSTANCE_NAME`_CFG3_TRIGGER_OUT_INIT \
            | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
    )

    #define `$INSTANCE_NAME`_CFG3_RANGE_THRES_INIT \
            (`$INSTANCE_NAME`_CFG3_LOW_LIMIT \
            | (uint32)((uint32)`$INSTANCE_NAME`_CFG3_HIGH_LIMIT \
            << SAR_RANGE_THRES_RANGE_HIGH_Pos))

    #define `$INSTANCE_NAME`_CFG3_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)`$INSTANCE_NAME`_CFG3_RANGE_COND

    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
    */
    #define `$INSTANCE_NAME`_CFG3_MISC_CONFIG_INIT \
            (`$INSTANCE_NAME`_CFG3_FREERUNNING )

#endif /* `$INSTANCE_NAME`_TOTAL_CONFIGS > 3 */

/* ************************************************************************** */
/* End configuration 3 calculated defines                                     */
/* ************************************************************************** */

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//*
*
* \brief Enables the component.
*
* \param None
*
* \return None
*
* \sideeffect
*  None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_SAR_Enable(`$INSTANCE_NAME`_SAR__HW);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* \brief This function stops ADC conversions and puts the ADC into its lowest
* power mode.
*
* \param None
*
* \return None
*
* \sideeffect
* Do not use the `$INSTANCE_NAME`_Stop() API to halt conversions. Instead use the
* `$INSTANCE_NAME`_StopConvert() API. If you use the `$INSTANCE_NAME`_Stop() API
* to halt conversions then later use the `$INSTANCE_NAME`_Start() and
* `$INSTANCE_NAME`_StartConvert() APIs to resume conversions, the first channel
* of the scan may be corrupt. The `$INSTANCE_NAME`_StopConvert() API will enable
* the `$INSTANCE_NAME` to complete the current scan of channels. After the
* channel scan is complete, the `$INSTANCE_NAME` will stop all conversions, which
* can be detected by the use of an ISR or the `$INSTANCE_NAME`_IsEndConversion()
* function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void)
{
    Cy_SAR_Disable(`$INSTANCE_NAME`_SAR__HW);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StopConvert
****************************************************************************//**
*
* \brief Forces the `$INSTANCE_NAME` to stop conversions. If a conversion is
* currently executing, that conversion will complete, but no further conversions
* will occur.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_StopConvert(void)
{
    Cy_SAR_StopConvert(`$INSTANCE_NAME`_SAR__HW);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult16
****************************************************************************//**
*
* \brief Gets the data available in the channel result data register
*
* \param chan The `$INSTANCE_NAME` channel to read the result from. The first
* channel is 0.
*
* \return Returns converted data as a signed 16-bit integer.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE int16_t `$INSTANCE_NAME`_GetResult16(uint32_t chan)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels);

    return Cy_SAR_GetResult16(`$INSTANCE_NAME`_SAR__HW, chan);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult32
****************************************************************************//**
*
* \brief Gets the data available in the channel result data register.
*
* \param chan The `$INSTANCE_NAME` channel to read the result from. The first
* channel is 0.
*
* \return Returns converted data as a signed 32-bit integer.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE int32_t `$INSTANCE_NAME`_GetResult32(uint32_t chan)
{
    int32_t finalResult;

    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels);

    finalResult = Cy_SAR_GetResult32(`$INSTANCE_NAME`_SAR__HW, chan);

    return finalResult;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetLowLimit
****************************************************************************//**
*
* \brief Sets the low limit parameter for a limit condition.
*
* \param lowLimit The low limit for a limit condition.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetLowLimit(uint32_t lowLimit)
{
    Cy_SAR_SetLowLimit(`$INSTANCE_NAME`_SAR__HW, lowLimit);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetHighLimit
****************************************************************************//**
*
* \brief Sets the high limit parameter for a limit condition.
*
* \param highLimit The high limit for a limit condition.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetHighLimit(uint32_t highLimit)
{
    Cy_SAR_SetHighLimit(`$INSTANCE_NAME`_SAR__HW, highLimit);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetLimitMask
****************************************************************************//**
*
* \brief Sets the channel limit condition mask.
*
*
* \param limitMask
* Sets which channels can cause a limit condition interrupt.
* Bit N of the mask enables the limit condition interrupt for channel N.
* The limitMask cannot be larger than the number of channels.
* If a channel is not enabled, it cannot cause any interrupts.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetLimitMask(uint32_t limitMask)
{
    Cy_SAR_SetRangeInterruptMask(`$INSTANCE_NAME`_SAR__HW, limitMask);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSatMask
****************************************************************************//**
*
* \brief Sets the channel saturation event mask.
*
* \param satMask
* Sets which channels can cause a saturation event interrupt.
* Bit N of the mask enables the saturation event interrupt for channel N.
* The satMask cannot be larger than the number of channels.
* If a channel is not enabled, it cannot cause any interrupts.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetSatMask(uint32_t satMask)
{
    Cy_SAR_SetSatInterruptMask(`$INSTANCE_NAME`_SAR__HW, satMask);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOffset
****************************************************************************//**
*
* \brief Sets the ADC offset that is used by the functions `$INSTANCE_NAME`_CountsTo_uVolts,
* `$INSTANCE_NAME`_CountsTo_mVolts, and `$INSTANCE_NAME`_CountsTo_Volts.
*
* Offset is applied to counts before unit scaling and gain.  All CountsTo_[mV, uV, V]olts()
* functions use the following equation:
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* See CountsTo_Volts() for more about this formula.
*
* To set channel 0's offset based on known V_offset_mV, use:
*     `$INSTANCE_NAME`_SetOffset(0uL, -1 * V_offset_mV * (1uL << (Resolution - 1)) / V_ref_mV);
*
* \param chan `$INSTANCE_NAME` channel number.
*
* \param offset This value is a measured value when the inputs are shorted or
* connected to the same input voltage.
*
* \return cy_en_sar_status_t
* - CY_SAR_BAD_PARAM: channel number is equal to or greater than CY_SAR_MAX_NUM_CHANNELS
* - CY_SAR_SUCCESS: offset was set successfully
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE cy_en_sar_status_t `$INSTANCE_NAME`_SetOffset(uint32_t chan, int16_t offset)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels);

    return Cy_SAR_SetOffset(chan, offset);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
****************************************************************************//**
*
* \brief Sets the `$INSTANCE_NAME` gain in counts per 10 volt for the voltage
* conversion functions. This value is set by default by the reference and
* input range settings. Gain is applied after offset and unit scaling.  All
* CountsTo_[mV, uV, V]olts() functions use the following equation:
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* See CountsTo_Volts() for more about this formula.
*
* To set channel 0's gain based on known V_ref_mV, use:
*     `$INSTANCE_NAME`_SetGain(0uL, 10000 * (1uL << (Resolution - 1)) / V_ref_mV);
*
* \param chan `$INSTANCE_NAME` channel number.
*
* \param adcGain `$INSTANCE_NAME` gain in counts per 10 volt.
*
* \return cy_en_sar_status_t
* - CY_SAR_BAD_PARAM: channel number is equal to or greater than CY_SAR_MAX_NUM_CHANNELS
* - CY_SAR_SUCCESS: gain was set successfully
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE cy_en_sar_status_t `$INSTANCE_NAME`_SetGain(uint32_t chan, int32_t adcGain)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels);

    return Cy_SAR_SetGain(chan, adcGain);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_Volts
****************************************************************************//**
*
* \brief Converts the ADC output to Volts as a float32. For example, if the ADC
* measured 0.534 volts, the return value would be 0.534.
* The calculation of voltage depends on the contents of Cy_SAR_offset[],
* Cy_SAR_countsPer10Volt[], and other parameters.  The equation used is:
*
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* -Counts = Raw Counts from SAR register
* -AvgDivider = divider based on averaging mode
*     -Sequential, Sum: AvgDivider = number averaged
*         Note: The divider should be a maximum of 16. If using more averages,
*         pre-scale Counts by (number averaged / 16)
*     -Interleaved, Sum: AvgDivider = number averaged
*     -Sequential, Fixed: AvgDivider = 1
* -Offset = Cy_SAR_offset[]
* -TEN_VOLT = 10V constant and unit scalar.
* -Gain = Cy_SAR_countsPer10Volt[]
*
* When the Vref is based on Vdda, the value used for Vdda is set for the project
* in the System tab of the DWR.
*
* \param chan `$INSTANCE_NAME` channel number.
*
* \param adcCounts Result from the `$INSTANCE_NAME` conversion.
*
* \return Result in Volts.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE float32_t `$INSTANCE_NAME`_CountsTo_Volts(uint32_t chan, int16_t adcCounts)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels);

    return Cy_SAR_CountsTo_Volts(`$INSTANCE_NAME`_SAR__HW, chan, adcCounts);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_mVolts
****************************************************************************//**
*
* \brief Converts the ADC output to millivolts as an int16. For example, if the ADC
* measured 0.534 volts, the return value would be 534.
* The calculation of voltage depends on the contents of Cy_SAR_offset[],
* Cy_SAR_countsPer10Volt[], and other parameters.  The equation used is:
*
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* -Counts = Raw Counts from SAR register
* -AvgDivider = divider based on averaging mode
*     -Sequential, Sum: AvgDivider = number averaged
*         Note: The divider should be a maximum of 16. If using more averages,
*         pre-scale Counts by (number averaged / 16)
*     -Interleaved, Sum: AvgDivider = number averaged
*     -Sequential, Fixed: AvgDivider = 1
* -Offset = Cy_SAR_offset[]
* -TEN_VOLT = 10V constant and unit scalar.
* -Gain = Cy_SAR_countsPer10Volt[]
*
* When the Vref is based on Vdda, the value used for Vdda is set for the project
* in the System tab of the DWR.
*
* \param chan `$INSTANCE_NAME` channel number.
*
* \param adcCounts Result from the `$INSTANCE_NAME` conversion.
*
* \return Result in mV.
*
* \sideeffect None.
*
*******************************************************************************/
__STATIC_INLINE int16_t `$INSTANCE_NAME`_CountsTo_mVolts(uint32_t chan, int16_t adcCounts)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels);

    return Cy_SAR_CountsTo_mVolts(`$INSTANCE_NAME`_SAR__HW, chan, adcCounts);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_uVolts
****************************************************************************//**
*
* \brief Converts the ADC output to microvolts as an int32. For example, if the ADC
* measured 0.534 volts, the return value would be 534000.
* The calculation of voltage depends on the contents of Cy_SAR_offset[],
* Cy_SAR_countsPer10Volt[], and other parameters.  The equation used is:
*
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* -Counts = Raw Counts from SAR register
* -AvgDivider = divider based on averaging mode
*     -Sequential, Sum: AvgDivider = number averaged
*         Note: The divider should be a maximum of 16. If using more averages,
*         pre-scale Counts by (number averaged / 16)
*     -Interleaved, Sum: AvgDivider = number averaged
*     -Sequential, Fixed: AvgDivider = 1
* -Offset = Cy_SAR_offset[]
* -TEN_VOLT = 10V constant and unit scalar.
* -Gain = Cy_SAR_countsPer10Volt[]
*
* When the Vref is based on Vdda, the value used for Vdda is set for the project
* in the System tab of the DWR.
*
* \param chan `$INSTANCE_NAME` channel number.
*
* \param adcCounts Result from the `$INSTANCE_NAME` conversion.
*
* \return Result in microvolts.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE int32_t `$INSTANCE_NAME`_CountsTo_uVolts(uint32_t chan, int16_t adcCounts)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels);

    return Cy_SAR_CountsTo_uVolts(`$INSTANCE_NAME`_SAR__HW, chan, adcCounts);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* \brief This is the preferred routine to prepare the component for sleep. The
* `$INSTANCE_NAME`_Sleep() routine saves the current component state. Then it
* calls the `$INSTANCE_NAME`_Stop() function.
*
* Calling this routine directly is not needed.
* The `$INSTANCE_NAME`_DeepSleepCallbackStruct will ensure this routine
* is called before the device enters Deep Sleep mode.
*
* \param None
*
* \return None
*
* \sideeffect If this function is called twice in the enable state of the
* component, the disabled state of the component will be stored. So
* `$INSTANCE_NAME`_Enable() and `$INSTANCE_NAME`_StartConvert() must be called
* after `$INSTANCE_NAME`_Wakeup() in this case.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup (W)
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Sleep(void)
{
    Cy_SAR_Sleep(`$INSTANCE_NAME`_SAR__HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
* \brief This is the preferred routine to restore the component to the state when
* `$INSTANCE_NAME`_Sleep() was called.
* If the component was enabled before the `$INSTANCE_NAME`_Sleep()
* function was called, the `$INSTANCE_NAME`_Wakeup() function also re-enables the
* component.
*
* Calling this routine directly is not needed.
* The `$INSTANCE_NAME`_DeepSleepCallbackStruct will ensure this routine
* is called after the device wakes up from Deep Sleep mode.
*
* \param None
*
* \return None
*
* \sideeffect
* Calling this function without previously calling `$INSTANCE_NAME`_Sleep() may lead to
* unpredictable results.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup (R)
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Wakeup(void)
{
    Cy_SAR_Wakeup(`$INSTANCE_NAME`_SAR__HW);
}

#endif /* !defined(CY_`$INSTANCE_NAME`_H) */

/* [] END OF FILE */
