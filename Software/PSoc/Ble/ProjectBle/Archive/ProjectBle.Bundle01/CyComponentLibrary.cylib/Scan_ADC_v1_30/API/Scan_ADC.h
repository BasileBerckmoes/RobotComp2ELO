/***************************************************************************//**
* \file     `$INSTANCE_NAME`.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* Provides the source code to the API for the `$INSTANCE_NAME` Component.
*
********************************************************************************
* \copyright
* (c) 2015-2016, Cypress Semiconductor Corporation. All rights reserved.
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

/*******************************************************************************
                                  Project Files
*******************************************************************************/
#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "`$INSTANCE_NAME`_IRQ.h"

#define `$INSTANCE_NAME`_VREF_ROUTED                  ((`$AdcRoutedVref`) == 1u)
#if (`$INSTANCE_NAME`_VREF_ROUTED)
#include "`$INSTANCE_NAME`_vrefAMux.h"
#endif

#define `$INSTANCE_NAME`_CLOCK_INTERNAL               ((`$AclkMuxSelect`) == 1u)
#if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
#include "`$INSTANCE_NAME`_intSarClock.h"
#endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */

#define `$INSTANCE_NAME`_CFG0_FILTER_PRESENT          (`$Cfg0HasFilter`uL)
#define `$INSTANCE_NAME`_CFG1_FILTER_PRESENT          (`$Cfg1HasFilter`uL)
#define `$INSTANCE_NAME`_CFG2_FILTER_PRESENT          (`$Cfg2HasFilter`uL)
#define `$INSTANCE_NAME`_CFG3_FILTER_PRESENT          (`$Cfg3HasFilter`uL)

#define `$INSTANCE_NAME`_ANY_CONFIG_USES_FILTER       ( `$INSTANCE_NAME`_CFG0_FILTER_PRESENT \
                                                      | `$INSTANCE_NAME`_CFG1_FILTER_PRESENT \
                                                      | `$INSTANCE_NAME`_CFG2_FILTER_PRESENT \
                                                      | `$INSTANCE_NAME`_CFG3_FILTER_PRESENT \
                                                      )


#if(`$INSTANCE_NAME`_ANY_CONFIG_USES_FILTER != 0u)
    #include "`$INSTANCE_NAME`_FILTER.h"
    #include "`$INSTANCE_NAME`_UABH_A.h"
    #include "`$INSTANCE_NAME`_UABH_B.h"
    #include "`$INSTANCE_NAME`_intUabClock.h"
    #include "`$INSTANCE_NAME`_filterVinMux.h"
    #include "`$INSTANCE_NAME`_FILTERAGND2SAR_BUFFER.h"
#endif


/**
* \addtogroup group_structures
*
*/
/** Low power Mode API Support */
typedef struct
{
    /** Preserves state of block prior to sleep. */
    uint8   enableState;
}   `$INSTANCE_NAME`_BACKUP_STRUCT;

typedef struct
{
    uint32 channelBase;    /* Start of channels for the configuration */
    uint32 numChannels;    /* Number of channels in the configuration */
    uint32 ctrl;           /* Contains the initial settings for the CRTL register except for the BOOSTPUMP_EN and
                              ENABLED bits which are set in the `$INSTANCE_NAME`_Init() `$INSTANCE_NAME`_Enable()
                              respectively */
    uint32 sampleCtrl;     /* Initial SAMPLE_CTRL register value */
    uint32 sampleTime01;   /* Initial SAMPLE_TIME01 register value */
    uint32 sampleTime23;   /* Initial SAMPLE_TIME23 register value */
    uint32 rangeThres;     /* Initial RANGE_THRES register value */
    uint32 rangeCond;      /* Initial RANGE_COND register value */
    uint32 chanEn;         /* Initial CHAN_EN register value */
    uint32 rangeIntMask;   /* Initial RANGE_INTR_MASK register value */
    uint32 satIntMask;     /* Stores the initial SAT_INTR_MASK register value */
    int32 vrefMvValue;      /* Calculated value of VREF in millivolts. Used in
                               `$INSTANCE_NAME`_CountsTo*Volts() functions */
    uint32 miscConfig;      /* Miscellaneous configuration bits broken down as follows:
                                [0] - Freerunning: Set if the sample mode is freerunning
                                [1] - Filter Present: Set if the configuration uses a UAB filter
                                [2] - Mux Switch 0: Set when VSSA is used for the neg input to any single-ended channel
                            */

#if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
    uint16 clkDivider;      /* Clock divider */
#endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */

#if(`$INSTANCE_NAME`_ANY_CONFIG_USES_FILTER != 0u)
    uint16 filterClkDivider;
#endif /* `$INSTANCE_NAME`_ANY_CONFIG_USES_FILTER   != 0u */
} `$INSTANCE_NAME`_CONFIG_STRUCT;
/** @} structures */

/*******************************************************************************
*           API Constants
*******************************************************************************/
/**
* \addtogroup group_constants
* {
*/
/** \addtogroup endConversion EOS status
* \brief Parameter constants for the `$INSTANCE_NAME`_IsEndConversion()
*  function.
*  @{
*/

/** Immediately returns conversion result */
#define `$INSTANCE_NAME`_RETURN_STATUS              (1u)
/** Doesn't return until ADC conversion is done */
#define `$INSTANCE_NAME`_WAIT_FOR_RESULT            (2u)

#define `$INSTANCE_NAME`_CONTINUOUS                 (1u)
#define `$INSTANCE_NAME`_SINGLE_SHOT                (2u)
`$VNEG_SOURCE_ENUM_DEF`

/* Constants for Sleep mode states */
#define `$INSTANCE_NAME`_ENABLED                    (0x01u)
#define `$INSTANCE_NAME`_STARTED                    (0x02u)
#define `$INSTANCE_NAME`_BOOSTPUMP_ENABLED          (0x04u)
#define `$INSTANCE_NAME`_SLEEP_DFT_DCEN             (0x08u)
#define `$INSTANCE_NAME`_SLEEP_DFT_DLY_INC          (0x10u)
/** @} group_constants */

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void `$INSTANCE_NAME`_SelectConfig(uint32 config, uint32 restart);
void `$INSTANCE_NAME`_InitConfig(const `$INSTANCE_NAME`_CONFIG_STRUCT *config);
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);

CY_ISR_PROTO(`$INSTANCE_NAME`_Interrupt);

/**
* \addtogroup group_general
* @{
*/
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_StartEx(cyisraddress address);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_StartConvert(void);
void `$INSTANCE_NAME`_StopConvert(void);
void `$INSTANCE_NAME`_SetConvertMode(uint32 mode);
void `$INSTANCE_NAME`_SetEosMask(uint32 mask);
uint32 `$INSTANCE_NAME`_IsEndConversion(uint32 retMode);
int16 `$INSTANCE_NAME`_GetResult16(uint32 chan);
int32 `$INSTANCE_NAME`_GetResult32(uint32 chan);
void `$INSTANCE_NAME`_SetLowLimit(uint32 lowLimit);
void `$INSTANCE_NAME`_SetHighLimit(uint32 highLimit);
void `$INSTANCE_NAME`_SetLimitMask(uint32 limitMask);
void `$INSTANCE_NAME`_SetSatMask(uint32 satMask);
void `$INSTANCE_NAME`_SetOffset(uint32 chan, int16 offset);
void `$INSTANCE_NAME`_SetGain(uint32 chan, int32 adcGain);
int16 `$INSTANCE_NAME`_RawCounts2Counts(uint32 chan, int16 adcCounts);
float32 `$INSTANCE_NAME`_CountsTo_Volts(uint32 chan, int16 adcCounts);
int16 `$INSTANCE_NAME`_CountsTo_mVolts(uint32 chan, int16 adcCounts);
int32 `$INSTANCE_NAME`_CountsTo_uVolts(uint32 chan, int16 adcCounts);


/** @} general */

void `$INSTANCE_NAME`_SetChanMask(uint32 enableMask);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);

/**
* \addtogroup group_power
* @{
*/
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
/** @} power */
CY_ISR_PROTO( `$INSTANCE_NAME`_ISR );

/*******************************************************************************
*       Type defines
*******************************************************************************/


/*******************************************************************************
                                  Parameters
The parameters that are set in the customizer are redefined as constants here.
*******************************************************************************/

/*  Sample Mode setting constants */
#define `$INSTANCE_NAME`_TOTAL_CONFIGS                (`$AdcTotalConfigs`ul)
#define `$INSTANCE_NAME`_IRQ_REMOVE                   (0u)

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
#define `$INSTANCE_NAME`_CFG0_SUB_RESOLUTION          (`$Cfg0AdcAltResolution`u)
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
/* Clock parameters*/
#if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
    #define `$INSTANCE_NAME`_CFG0_CLOCKDIVIDER        (((CYDEV_BCLK__HFCLK__HZ) / (`$INSTANCE_NAME`_CFG0_NOMINAL_CLOCK_FREQ)) - 1u)
#endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */
/* Filter Parameters */
#if(`$INSTANCE_NAME`_CFG0_FILTER_PRESENT == 1uL)
    /* Timing settings */
    /* Clock divider register uses 0 for a divider of 1, 1 for a divider of 2, and so on. */
    #define `$INSTANCE_NAME`_CFG0_FILTERCLOCKDIVIDER  (`$Cfg0FilterClockDivider`u - 1u)
    #define `$INSTANCE_NAME`_CFG0_FILTERSTARTDELAY    (`$Cfg0FilterStartDelay`u)
#endif /* (`$INSTANCE_NAME`_CFG0_FILTER_PRESENT == 1uL) */

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
    #define `$INSTANCE_NAME`_CFG1_SUB_RESOLUTION          (`$Cfg1AdcAltResolution`u)
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
    /* Clock parameters*/
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        #define `$INSTANCE_NAME`_CFG1_CLOCKDIVIDER        (((CYDEV_BCLK__HFCLK__HZ) / (`$INSTANCE_NAME`_CFG1_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */
    /* Filter Parameters */
    #if(`$INSTANCE_NAME`_CFG1_FILTER_PRESENT == 1uL)
    /* Timing settings */
        /* Clock divider register uses 0 for a divider of 1, 1 for a divider of 2, and so on. */
        #define `$INSTANCE_NAME`_CFG1_FILTERCLOCKDIVIDER  (`$Cfg1FilterClockDivider`u - 1u)
        #define `$INSTANCE_NAME`_CFG1_FILTERSTARTDELAY    (`$Cfg1FilterStartDelay`u)
    #endif /* (`$INSTANCE_NAME`_CFG1_FILTER_PRESENT == 1uL) */
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
    #define `$INSTANCE_NAME`_CFG2_SUB_RESOLUTION          (`$Cfg2AdcAltResolution`u)
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
    /* Clock parameters*/
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        #define `$INSTANCE_NAME`_CFG2_CLOCKDIVIDER        (((CYDEV_BCLK__HFCLK__HZ) / (`$INSTANCE_NAME`_CFG2_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */
    /* Filter Parameters */
    #if(`$INSTANCE_NAME`_CFG2_FILTER_PRESENT == 1uL)
    /* Timing settings */
        /* Clock divider register uses 0 for a divider of 1, 1 for a divider of 2, and so on. */
        #define `$INSTANCE_NAME`_CFG2_FILTERCLOCKDIVIDER  (`$Cfg2FilterClockDivider`u - 1u)
        #define `$INSTANCE_NAME`_CFG2_FILTERSTARTDELAY    (`$Cfg2FilterStartDelay`u)
    #endif /* (`$INSTANCE_NAME`_CFG2_FILTER_PRESENT == 1uL) */
#endif /* (`$INSTANCE_NAME`_TOTAL_CONFIGS > 2) */

/* ************************************************************************** */
/* End configuration 2 customizer defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 3 customizer defines                                         */
/* ************************************************************************** */

#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 3)
    #define `$INSTANCE_NAME`_CFG3_SAMPLE_RATE             (`$Cfg3SampleRate`)
    #define `$INSTANCE_NAME`_CFG3_CHANNEL_BASE            (`$Cfg3AdcChannelIndex`u)
    #define `$INSTANCE_NAME`_CFG3_CHANNEL_COUNT           (`$Cfg3AdcChannelCount`u)
    #define `$INSTANCE_NAME`_CFG3_VREF_SEL_MASK           (`$Cfg3AdcVrefSelMask`u)
    #define `$INSTANCE_NAME`_CFG3_NOMINAL_CLOCK_FREQ      (`$Cfg3NominalClockFreq`u)
    #define `$INSTANCE_NAME`_CFG3_CHANNEL_EN              (`$Cfg3AdcChannelEnable`u)
    /* Sample Control Register */
    #define `$INSTANCE_NAME`_CFG3_SUB_RESOLUTION          (`$Cfg3AdcAltResolution`u)
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
    /* Clock parameters*/
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        #define `$INSTANCE_NAME`_CFG3_CLOCKDIVIDER        (((CYDEV_BCLK__HFCLK__HZ) / (`$INSTANCE_NAME`_CFG3_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (`$INSTANCE_NAME`_CLOCK_INTERNAL) */
    /* Filter Parameters */
    #if(`$INSTANCE_NAME`_CFG3_FILTER_PRESENT == 1uL)
    /* Timing settings */
        /* Clock divider register uses 0 for a divider of 1, 1 for a divider of 2, and so on. */
        #define `$INSTANCE_NAME`_CFG3_FILTERCLOCKDIVIDER  (`$Cfg3FilterClockDivider`u - 1u)
        #define `$INSTANCE_NAME`_CFG3_FILTERSTARTDELAY    (`$Cfg3FilterStartDelay`u)
    #endif /* (`$INSTANCE_NAME`_CFG3_FILTER_PRESENT == 1uL) */
#endif /* (`$INSTANCE_NAME`_TOTAL_CONFIGS > 3) */

/* ************************************************************************** */
/* End configuration 3 customizer defines                                     */
/* ************************************************************************** */

#define `$INSTANCE_NAME`_DEFAULT_SAMPLE_MODE_SEL      (0u)
#define `$INSTANCE_NAME`_FREERUNNING                  (1u)
#define `$INSTANCE_NAME`_HARDWARESOC                  (1u)

/* Constants for setting the SAR to trigger the UAB Filter */
#define `$INSTANCE_NAME`_SRAM_CTRL_TRIGGER            (0x3F000000u)

/** `$INSTANCE_NAME`_TOTAL_CHANNELS_NUM
* This constant represents the amount of input channels available for scanning.
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
extern uint8 `$INSTANCE_NAME`_initVar;
extern uint8 `$INSTANCE_NAME`_selected;

#define `$INSTANCE_NAME`_INIT_VAR_INIT_FLAG     (0x01u)

/** `$INSTANCE_NAME`_offset
* This array calibrates the offset for each channel. The first time Start() is
* called, the offset array's entries are initialized to 0, except for channels
* which are Single-Ended, Signed, and have Vneg=Vref, for which it is set to
* -2^(Resolution-1)/Vref(mV). It can be modified using ADC_SetOffset(). The array
* is used by the ADC_CountsTo_Volts(), ADC_CountsTo_mVolts(), and
* ADC_CountsTo_uVolts() functions.
*/
extern volatile int16 `$INSTANCE_NAME`_offset[`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM];

/** `$INSTANCE_NAME`_countsPer10Volt
* This array is used to calibrate the gain for each channel. It is calculated
* the first time `$INSTANCE_NAME`_Start() is called. The value depends on
* channel resolution and voltage reference. It can be changed using
* `$INSTANCE_NAME`_SetGain().
*
* This array affects the `$INSTANCE_NAME`_CountsTo_Volts(),
* `$INSTANCE_NAME`_CountsTo_mVolts(), and `$INSTANCE_NAME`_CountsTo_uVolts()
* functions by supplying the correct conversion between ADC counts and the
* applied input voltage.
*/
extern volatile int32 `$INSTANCE_NAME`_countsPer10Volt[`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM];   /* Gain compensation */
extern const `$INSTANCE_NAME`_CONFIG_STRUCT `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_TOTAL_CONFIGS];
extern const uint32 CYCODE `$INSTANCE_NAME`_InputsPlacement[`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM];

/** @} globals */

#define `$INSTANCE_NAME`_HALF_A_CC_GND              (0) /* Half A CC_GND is always zero */
#define `$INSTANCE_NAME`_SW_EXTAGND  (CyUAB_sw_id_enum) CyUAB_SW_ID(`$INSTANCE_NAME`_UABH_A_SW_STATIC_PTR,((uint32)`$INSTANCE_NAME`_UABH_A_halfuab__VAGND_SRC), CyUAB_SW_NOX)  /* static: OA+ <-> External routed agnd */
#define `$INSTANCE_NAME`_SW_EXTREFA  (CyUAB_sw_id_enum) CyUAB_SW_ID(`$INSTANCE_NAME`_UABH_A_SW_CA_IN0_PTR,((uint32)((uint32)`$INSTANCE_NAME`_UABH_A_halfuab__VREF_SRC)*`$INSTANCE_NAME`_UABH_A_DYNAMIC_FIELD_SIZE), CyUAB_SW_NOX) /* A in <-> External routed vref */
#define `$INSTANCE_NAME`_SW_EXTREFB  (CyUAB_sw_id_enum) CyUAB_SW_ID(`$INSTANCE_NAME`_UABH_A_SW_CB_IN0_PTR,((uint32)((uint32)`$INSTANCE_NAME`_UABH_A_halfuab__VREF_SRC)*`$INSTANCE_NAME`_UABH_A_DYNAMIC_FIELD_SIZE ), CyUAB_SW_NOX) /* B in <-> External routed vref */

#define `$INSTANCE_NAME`_MAX_FREQUENCY              (18000000u)       /*18Mhz*/

#define `$INSTANCE_NAME`_10US_DELAY                 (10u)
#define `$INSTANCE_NAME`_10V_COUNTS                 (10.0F)
#define `$INSTANCE_NAME`_10MV_COUNTS                (10000)
#define `$INSTANCE_NAME`_10UV_COUNTS                (10000000L)

/*******************************************************************************
*              Registers
*******************************************************************************/

#define `$INSTANCE_NAME`_SAR_CTRL_REG                   (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CTRL )
#define `$INSTANCE_NAME`_SAR_CTRL_PTR                   ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CTRL )

#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_REG            (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SAMPLE_CTRL )
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_PTR            ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SAMPLE_CTRL )

#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SAMPLE_TIME01 )
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SAMPLE_TIME01 )

#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SAMPLE_TIME23 )
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SAMPLE_TIME23 )

#define `$INSTANCE_NAME`_SAR_RANGE_THRES_REG            (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_THRES )
#define `$INSTANCE_NAME`_SAR_RANGE_THRES_PTR            ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_THRES )

#define `$INSTANCE_NAME`_SAR_RANGE_COND_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_COND )
#define `$INSTANCE_NAME`_SAR_RANGE_COND_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_COND )

#define `$INSTANCE_NAME`_SAR_CHAN_EN_REG                (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_EN )
#define `$INSTANCE_NAME`_SAR_CHAN_EN_PTR                ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_EN )

#define `$INSTANCE_NAME`_SAR_START_CTRL_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_START_CTRL )
#define `$INSTANCE_NAME`_SAR_START_CTRL_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_START_CTRL )
/* CDT-230388: These constants are getting added to cyfitter.h */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_REG               (*(reg32 *) CYREG_SAR_DFT_CTRL )
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_PTR               ( (reg32 *) CYREG_SAR_DFT_CTRL )

#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_REG            (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_CONFIG00 )
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_PTR            ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_CONFIG00 )
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_IND            ( `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_CONFIG00 )

#define `$INSTANCE_NAME`_SAR_CHAN_WORK_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_WORK00 )
#define `$INSTANCE_NAME`_SAR_CHAN_WORK_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_WORK00 )

#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_REG            (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_RESULT0 )
#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_PTR            ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_RESULT0 )

#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_IND            ( `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_CHAN_RESULT00 )

#define `$INSTANCE_NAME`_SAR_CHAN0_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT00 )
#define `$INSTANCE_NAME`_SAR_CHAN0_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT00 )

#define `$INSTANCE_NAME`_SAR_CHAN1_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT01 )
#define `$INSTANCE_NAME`_SAR_CHAN1_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT01 )

#define `$INSTANCE_NAME`_SAR_CHAN2_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT2 )
#define `$INSTANCE_NAME`_SAR_CHAN2_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT2 )

#define `$INSTANCE_NAME`_SAR_CHAN3_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT3 )
#define `$INSTANCE_NAME`_SAR_CHAN3_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT3 )

#define `$INSTANCE_NAME`_SAR_CHAN4_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT4 )
#define `$INSTANCE_NAME`_SAR_CHAN4_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT4 )

#define `$INSTANCE_NAME`_SAR_CHAN5_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT5 )
#define `$INSTANCE_NAME`_SAR_CHAN5_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT5 )

#define `$INSTANCE_NAME`_SAR_CHAN6_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT6 )
#define `$INSTANCE_NAME`_SAR_CHAN6_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT6 )

#define `$INSTANCE_NAME`_SAR_CHAN7_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT7 )
#define `$INSTANCE_NAME`_SAR_CHAN7_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT7 )

#define `$INSTANCE_NAME`_SAR_CHAN8_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT8 )
#define `$INSTANCE_NAME`_SAR_CHAN8_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT8 )

#define `$INSTANCE_NAME`_SAR_CHAN9_RESULT_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT9 )
#define `$INSTANCE_NAME`_SAR_CHAN9_RESULT_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT9 )

#define `$INSTANCE_NAME`_SAR_CHAN10_RESULT_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT10 )
#define `$INSTANCE_NAME`_SAR_CHAN10_RESULT_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT10 )

#define `$INSTANCE_NAME`_SAR_CHAN11_RESULT_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT11 )
#define `$INSTANCE_NAME`_SAR_CHAN11_RESULT_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT11 )

#define `$INSTANCE_NAME`_SAR_CHAN12_RESULT_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT12 )
#define `$INSTANCE_NAME`_SAR_CHAN12_RESULT_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT12 )

#define `$INSTANCE_NAME`_SAR_CHAN13_RESULT_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT13 )
#define `$INSTANCE_NAME`_SAR_CHAN13_RESULT_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT13 )

#define `$INSTANCE_NAME`_SAR_CHAN14_RESULT_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT14 )
#define `$INSTANCE_NAME`_SAR_CHAN14_RESULT_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT14 )

#define `$INSTANCE_NAME`_SAR_CHAN15_RESULT_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT15 )
#define `$INSTANCE_NAME`_SAR_CHAN15_RESULT_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_1__SAR_CHAN_RESULT15 )
/* CDT-230483: These will be in cyfitter. */
#define `$INSTANCE_NAME`_SAR_CHAN_WORK_UPDATED_REG      (*(reg32 *) CYREG_SAR_CHAN_WORK_UPDATED)
#define `$INSTANCE_NAME`_SAR_CHAN_WORK_UPDATED_PTR      ( (reg32 *) CYREG_SAR_CHAN_WORK_UPDATED)

#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_UPDATED_REG    ( *(reg32 *) CYREG_SAR_CHAN_RESULT_UPDATED )
#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_UPDATED_PTR    ( (reg32 *) CYREG_SAR_CHAN_RESULT_UPDATED )

#define `$INSTANCE_NAME`_SAR_CHAN_WORK_NEWVALUE_REG     (*(reg32 *) CYREG_SAR_CHAN_WORK_NEWVALUE)
#define `$INSTANCE_NAME`_SAR_CHAN_WORK_NEWVALUE_PTR     ( (reg32 *) CYREG_SAR_CHAN_WORK_NEWVALUE)

#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_NEWVALUE_REG   ( *(reg32 *) CYREG_SAR_CHAN_RESULT_NEWVALUE )
#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_NEWVALUE_PTR   ( (reg32 *) CYREG_SAR_CHAN_RESULT_NEWVALUE )

#define `$INSTANCE_NAME`_SAR_STATUS_REG                 (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_STATUS )
#define `$INSTANCE_NAME`_SAR_STATUS_PTR                 ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_STATUS )

#define `$INSTANCE_NAME`_SAR_AVG_START_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_AVG_STAT )
#define `$INSTANCE_NAME`_SAR_AVG_START_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_AVG_STAT )

#define `$INSTANCE_NAME`_SAR_INTR_REG                   (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR )
#define `$INSTANCE_NAME`_SAR_INTR_PTR                   ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR )

#define `$INSTANCE_NAME`_SAR_INTR_SET_REG               (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_SET )
#define `$INSTANCE_NAME`_SAR_INTR_SET_PTR               ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_SET )

#define `$INSTANCE_NAME`_SAR_INTR_MASK_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_MASK )
#define `$INSTANCE_NAME`_SAR_INTR_MASK_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_MASK )

#define `$INSTANCE_NAME`_SAR_INTR_MASKED_REG            (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_MASKED )
#define `$INSTANCE_NAME`_SAR_INTR_MASKED_PTR            ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_MASKED )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_SET_REG      (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR_SET )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_SET_PTR      ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR_SET )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASK_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR_MASK )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASK_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR_MASK )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASKED_REG \
                                                 (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR_MASKED )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASKED_PTR \
                                                 ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_SATURATE_INTR_MASKED )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_SET_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR_SET )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_SET_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR_SET )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASK_REG        (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR_MASK )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASK_PTR        ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR_MASK )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASKED_REG      (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR_MASKED )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASKED_PTR      ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_RANGE_INTR_MASKED )

#define `$INSTANCE_NAME`_SAR_INTR_CAUSE_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_CAUSE )
#define `$INSTANCE_NAME`_SAR_INTR_CAUSE_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INTR_CAUSE )

#define `$INSTANCE_NAME`_SAR_INJ_CHAN_CONFIG_REG        (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INJ_CHAN_CONFIG)
#define `$INSTANCE_NAME`_SAR_INJ_CHAN_CONFIG_PTR        ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INJ_CHAN_CONFIG)

#define `$INSTANCE_NAME`_SAR_INJ_RESULT_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INJ_RESULT )
#define `$INSTANCE_NAME`_SAR_INJ_RESULT_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar_1__SAR_INJ_RESULT )
/* CDT-230388: These constants are getting added to cyfitter.h */
#define `$INSTANCE_NAME`_MUX_SWITCH0_REG                (*(reg32 *)  CYREG_SAR_MUX_SWITCH0 )
#define `$INSTANCE_NAME`_MUX_SWITCH0_PTR                ( (reg32 *)  CYREG_SAR_MUX_SWITCH0 )

#define `$INSTANCE_NAME`_MUX_SWITCH_HW_CTRL_REG         (*(reg32 *)  CYREG_SAR_MUX_SWITCH_HW_CTRL )
#define `$INSTANCE_NAME`_MUX_SWITCH_HW_CTRL_PTR         ( (reg32 *)  CYREG_SAR_MUX_SWITCH_HW_CTRL )

#define `$INSTANCE_NAME`_PUMP_CTRL_REG                  (*(reg32 *)  CYREG_SAR_PUMP_CTRL )
#define `$INSTANCE_NAME`_PUMP_CTRL_PTR                  ( (reg32 *)  CYREG_SAR_PUMP_CTRL )

#define `$INSTANCE_NAME`_ANA_TRIM_REG                   (*(reg32 *)  CYREG_SAR_ANA_TRIM )
#define `$INSTANCE_NAME`_ANA_TRIM_PTR                   ( (reg32 *)  CYREG_SAR_ANA_TRIM )

#define `$INSTANCE_NAME`_WOUNDING_REG                   (*(reg32 *)  CYREG_SAR_WOUNDING )
#define `$INSTANCE_NAME`_WOUNDING_PTR                   ( (reg32 *)  CYREG_SAR_WOUNDING )

/*******************************************************************************
*       Register Constants
*******************************************************************************/
#define `$INSTANCE_NAME`_VIN_SWITCH_CLOSED                        (0xFu)
#define `$INSTANCE_NAME`_VIN_ALL_SWITCHES_MASK                    (0xFFFFu)     /* Mask for SW_C**_IN0 VIN settings */

#define `$INSTANCE_NAME`_INTC_NUMBER                              (`$INSTANCE_NAME`_IRQ__INTC_NUMBER)
#define `$INSTANCE_NAME`_INTC_PRIOR_NUMBER                        (`$INSTANCE_NAME`_IRQ__INTC_PRIOR_NUM)

/* ***************************SAR_CTRL_REG fields *************************** */
/* VREF_SEL bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_VREF_SEL_MSK                    (0x00000070u)
#define `$INSTANCE_NAME`_SAR_CTRL_VREF_SEL_SHFT                   (4ul)
    /* VREF_SEL bitfield enumerated values */
    #define `$INSTANCE_NAME`_VREF_SEL_VREF0                       (0x0ul)
    #define `$INSTANCE_NAME`_VREF_SEL_VREF1                       (0x1ul)
    #define `$INSTANCE_NAME`_VREF_SEL_VREF2                       (0x2ul)
    #define `$INSTANCE_NAME`_VREF_SEL_VREF_AROUTE                 (0x3ul)
    #define `$INSTANCE_NAME`_VREF_SEL_VBGR                        (0x4ul)
    #define `$INSTANCE_NAME`_VREF_SEL_VREF_EXT                    (0x5ul)
    #define `$INSTANCE_NAME`_VREF_SEL_VDDA_DIV_2                  (0x6ul)
    #define `$INSTANCE_NAME`_VREF_SEL_VDDA                        (0x7ul)

#define `$INSTANCE_NAME`__SAR_CTRL_VREF_BYP_AND_SEL_MSK           (0x000000F0u)
#define `$INSTANCE_NAME`__INTERNAL1024                            (`$INSTANCE_NAME`_VREF_SEL_VBGR \
                                                                    << `$INSTANCE_NAME`_SAR_CTRL_VREF_SEL_SHFT)
/* VREF is zero for the component if routed by Creator to an internal reference */
#define `$INSTANCE_NAME`__INTERNALVREF                            (0x0ul)
#define `$INSTANCE_NAME`__VDDA_VREF                               (`$INSTANCE_NAME`_VREF_SEL_VDDA \
                                                                    << `$INSTANCE_NAME`_SAR_CTRL_VREF_SEL_SHFT)
#define `$INSTANCE_NAME`__EXT_VREF                               (`$INSTANCE_NAME`_VREF_SEL_VREF_EXT \
                                                                    << `$INSTANCE_NAME`_SAR_CTRL_VREF_SEL_SHFT)
/* VREF_BYP_CAP_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_VREF_BYP_CAP_EN_MSK             (0x00000080u)
#define `$INSTANCE_NAME`_SAR_CTRL_VREF_BYP_CAP_EN_SHFT            (7U)

/* NEG_SEL bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_MSK                     (0x00000e00ul)
#define `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT                    (9ul)
    /* NEG_SEL bitfield enumerated values */
    #define `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN                  (0x0uL)
    #define `$INSTANCE_NAME`_NEG_SEL_ART_VSSA                     (0x1uL)
    #define `$INSTANCE_NAME`_NEG_SEL_P1                           (0x2uL)
    #define `$INSTANCE_NAME`_NEG_SEL_P3                           (0x3uL)
    #define `$INSTANCE_NAME`_NEG_SEL_P5                           (0x4uL)
    #define `$INSTANCE_NAME`_NEG_SEL_P7                           (0x5uL)
    #define `$INSTANCE_NAME`_NEG_SEL_ACORE                        (0x6uL)
    #define `$INSTANCE_NAME`_NEG_SEL_VREF                         (0x7uL)
    #define `$INSTANCE_NAME`_NEG_VREF_SHIFTED                     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                                    << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT)
/* SAR_HW_CTRL_NEGVREF bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_SAR_HW_CTRL_NEGVREF_MSK         (0x00002000u)
#define `$INSTANCE_NAME`_SAR_CTRL_SAR_HW_CTRL_NEGVREF_SHFT        (13U)

/* PWR_CTRL_VREF bitfield -- 2 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_PWR_CTRL_VREF_MSK               (0x0000c000u)
#define `$INSTANCE_NAME`_SAR_CTRL_PWR_CTRL_VREF_SHFT              (14u)
    /* PWR_CTRL_VREF bitfield enumerated values */
    #define `$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR             (0x0uL)
    #define `$INSTANCE_NAME`_PWR_CTRL_VREF_THIRD_PWR              (0x2uL)

/* SPARE bitfield -- 4 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_SPARE_MSK                       (0x000f0000u)
#define `$INSTANCE_NAME`_SAR_CTRL_SPARE_SHFT                      (16U)

/* BOOSTPUMP_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_BOOSTPUMP_EN_MSK                (0x00100000u)
#define `$INSTANCE_NAME`_SAR_CTRL_BOOSTPUMP_EN_SHFT               (20U)

/* REFBUF_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_REFBUF_EN_MSK                   (0x00200000u)
#define `$INSTANCE_NAME`_SAR_CTRL_REFBUF_EN_SHFT                  (21U)

/* ICONT_LV bitfield -- 2 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_ICONT_LV_MSK                    (0x03000000u)
#define `$INSTANCE_NAME`_SAR_CTRL_ICONT_LV_SHFT                   (24U)
    /* ICONT_LV bitfield enumerated values */
    #define `$INSTANCE_NAME`_ICONT_LV_NORMAL_PWR                  (0x0)
    #define `$INSTANCE_NAME`_ICONT_LV_HALF_PWR                    (0x1)
    #define `$INSTANCE_NAME`_ICONT_LV_MORE_PWR                    (0x2)
    #define `$INSTANCE_NAME`_ICONT_LV_QUARTER_PWR                 (0x3)

/* DEEPSLEEP_ON bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_DEEPSLEEP_ON_MSK                (0x08000000u)
#define `$INSTANCE_NAME`_SAR_CTRL_DEEPSLEEP_ON_SHFT               (27U)

/* DSI_SYNC_CONFIG bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_DSI_SYNC_CONFIG_MSK             (0x10000000u)
#define `$INSTANCE_NAME`_SAR_CTRL_DSI_SYNC_CONFIG_SHFT            (28U)

/* DSI_MODE bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_DSI_MODE_MSK                    (0x20000000u)
#define `$INSTANCE_NAME`_SAR_CTRL_DSI_MODE_SHFT                   (29U)

/* SWITCH_DISABLE bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_SWITCH_DISABLE_MSK              (0x40000000u)
#define `$INSTANCE_NAME`_SAR_CTRL_SWITCH_DISABLE_SHFT             (30U)

/* ENABLED bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CTRL_ENABLED_MSK                     (0x80000000u)
#define `$INSTANCE_NAME`_SAR_CTRL_ENABLED_SHFT                    (31U)


/* ***********************SAR_SAMPLE_CTRL_REG fields ************************ */
/* SUB_RESOLUTION bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SUB_RESOLUTION_MSK       (0x00000001u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SUB_RESOLUTION_SHFT      (0U)
    /* SUB_RESOLUTION bitfield enumerated values */
    #define `$INSTANCE_NAME`_SUB_RESOLUTION_8B                    (0x0U)
    #define `$INSTANCE_NAME`_SUB_RESOLUTION_10B                   (0x1U)

/* LEFT_ALIGN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_LEFT_ALIGN_MSK           (0x00000002u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_LEFT_ALIGN_SHFT          (1u)

/* SINGLE_ENDED_SIGNED bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_MSK  (0x00000004u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_SHFT (2u)
    /* SINGLE_ENDED_SIGNED bitfield enumerated values */
    #define `$INSTANCE_NAME`_SINGLE_ENDED_SIGNED_UNSIGNED         (0x0L)
    #define `$INSTANCE_NAME`_SINGLE_ENDED_SIGNED_SIGNED           (0x1L)

/* DIFFERENTIAL_SIGNED bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_MSK  (0x00000008u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_SHFT (3u)
    /* DIFFERENTIAL_SIGNED bitfield enumerated values */
    #define `$INSTANCE_NAME`_DIFFERENTIAL_SIGNED_UNSIGNED         (0x0u)
    #define `$INSTANCE_NAME`_DIFFERENTIAL_SIGNED_SIGNED           (0x1u)

/* AVG_CNT bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_CNT_MSK              (0x00000070u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_CNT_SHFT             (4u)

/* AVG_SHIFT bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_SHIFT_MSK            (0x00000080u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_SHIFT_SHFT           (7u)

/* AVG_MODE bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_MODE_MSK             (0x00000100u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_MODE_SHFT            (8u)
    /* AVG_MODE bitfield enumerated values */
    #define `$INSTANCE_NAME`_AVG_MODE_ACCUNDUMP                   (0x0u)
    #define `$INSTANCE_NAME`_AVG_MODE_INTERLEAVED                 (0x1u)

/* CONTINUOUS bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_CONTINUOUS_MSK           (0x00010000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_CONTINUOUS_SHFT          (16u)

/* DSI_TRIGGER_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_MSK       (0x00020000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_SHFT      (17u)

/* DSI_TRIGGER_LEVEL bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_MSK    (0x00040000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_SHFT   (18u)

/* DSI_SYNC_TRIGGER bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_SYNC_TRIGGER_MSK     (0x00080000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_SYNC_TRIGGER_SHFT    (19u)

/* UAB_SCAN_MODE bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_UAB_SCAN_MODE_MSK        (0x00400000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_UAB_SCAN_MODE_SHFT       (22u)
    /* UAB_SCAN_MODE bitfield enumerated values */
    #define `$INSTANCE_NAME`_UAB_SCAN_MODE_UNSCHEDULED            (0x0u)
    #define `$INSTANCE_NAME`_UAB_SCAN_MODE_SCHEDULED              (0x1u)

/* REPEAT_INVALID bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_REPEAT_INVALID_MSK       (0x00800000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_REPEAT_INVALID_SHFT      (23u)

/* VALID_SEL bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_SEL_MSK            (0x07000000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_SEL_SHFT           (24u)

/* VALID_SEL_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_SEL_EN_MSK         (0x08000000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_SEL_EN_SHFT        (27u)

/* VALID_IGNORE bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_IGNORE_MSK         (0x10000000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_IGNORE_SHFT        (28u)

/* TRIGGER_OUT_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_MSK       (0x40000000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_SHFT      (30u)

/* EOS_DSI_OUT_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_MSK       (0x80000000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_SHFT      (31u)


/* **********************SAR_SAMPLE_TIME01_REG fields *********************** */
/* SAMPLE_TIME0 bitfield -- 10 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME0_MSK       (0x000003ffu)
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME0_SHFT      (0u)

/* SAMPLE_TIME1 bitfield -- 10 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME1_MSK       (0x03ff0000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME1_SHFT      (16u)


/* **********************SAR_SAMPLE_TIME23_REG fields *********************** */
/* SAMPLE_TIME2 bitfield -- 10 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME2_MSK       (0x000003ffu)
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME2_SHFT      (0u)

/* SAMPLE_TIME3 bitfield -- 10 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME3_MSK       (0x03ff0000u)
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME3_SHFT      (16u)


/* ***********************SAR_RANGE_THRES_REG fields ************************ */
/* RANGE_LOW bitfield -- 16 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_LOW_MSK            (0x0000ffffu)
#define `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_LOW_SHFT           (0U)

/* RANGE_HIGH bitfield -- 16 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_HIGH_MSK           (0xffff0000u)
#define `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_HIGH_SHFT          (16U)


/* ************************SAR_RANGE_COND_REG fields ************************ */
/* RANGE_COND bitfield -- 2 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_RANGE_COND_RANGE_COND_MSK            (0xc0000000u)
#define `$INSTANCE_NAME`_SAR_RANGE_COND_RANGE_COND_SHFT           (30u)
    /* RANGE_COND bitfield enumerated values */
    #define `$INSTANCE_NAME`_RANGE_COND_BELOW                     (0x0)
    #define `$INSTANCE_NAME`_RANGE_COND_INSIDE                    (0x1)
    #define `$INSTANCE_NAME`_RANGE_COND_ABOVE                     (0x2)
    #define `$INSTANCE_NAME`_RANGE_COND_OUTSIDE                   (0x3)


/* *************************SAR_CHAN_EN_REG fields ************************** */
/* CHAN_EN bitfield -- 16 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_EN_CHAN_EN_MSK                  (0x0000ffffu)
#define `$INSTANCE_NAME`_SAR_CHAN_EN_CHAN_EN_SHFT                 (0u)


/* ************************SAR_START_CTRL_REG fields ************************ */
/* FW_TRIGGER bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_START_CTRL_FW_TRIGGER_MSK            (0x00000001uL)
#define `$INSTANCE_NAME`_SAR_START_CTRL_FW_TRIGGER_SHFT           (0u)


/* *************************SAR_DFT_CTRL_REG fields ************************* */
/* DLY_INC bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DLY_INC_MSK                 (0x00000001uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DLY_INC_SHFT                (0u)

/* HIZ bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_HIZ_MSK                     (0x00000002uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_HIZ_SHFT                    (1u)

/* DFT_INC bitfield -- 4 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DFT_INC_MSK                 (0x000f0000uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DFT_INC_SHFT                (16u)

/* DFT_OUTC bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DFT_OUTC_MSK                (0x00700000uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DFT_OUTC_SHFT               (20u)

/* SEL_CSEL_DFT bitfield -- 4 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_SEL_CSEL_DFT_MSK            (0x0f000000uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_SEL_CSEL_DFT_SHFT           (24u)

/* EN_CSEL_DFT bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_EN_CSEL_DFT_MSK             (0x10000000uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_EN_CSEL_DFT_SHFT            (28u)

/* DCEN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DCEN_MSK                    (0x20000000uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_DCEN_SHFT                   (29u)

/* ADFT_OVERRIDE bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_ADFT_OVERRIDE_MSK           (0x80000000uL)
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_ADFT_OVERRIDE_SHFT          (31u)

/* ***********************SAR_CHAN_CONFIG_REG fields *********************** */
/* POS_PIN_ADDR bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_POS_PIN_ADDR_MSK         (0x00000007u)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_POS_PIN_ADDR_SHFT        (0u)

/* POS_PORT_ADDR bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_POS_PORT_ADDR_MSK        (0x00000070u)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_POS_PORT_ADDR_SHFT       (4u)
    /* POS_PORT_ADDR bitfield enumerated values */
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_SARMUX                 (0x0)
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_CTB0                   (0x1)
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_CTB1                   (0x2)
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_CTB2                   (0x3)
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_CTB3                   (0x4)
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_AROUTE_VIRT2           (0x5)
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_AROUTE_VIRT1           (0x6)
    #define `$INSTANCE_NAME`_POS_PORT_ADDR_SARMUX_VIRT            (0x7)

/* DIFFERENTIAL_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_DIFFERENTIAL_EN_MSK      (0x00000100uL)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_DIFFERENTIAL_EN_SHFT     (8u)

/* RESOLUTION bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_RESOLUTION_MSK           (0x00000200u)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_RESOLUTION_SHFT          (9u)
    /* RESOLUTION bitfield enumerated values */
    #define `$INSTANCE_NAME`_RESOLUTION_MAXRES                    (0x0)
    #define `$INSTANCE_NAME`_RESOLUTION_SUBRES                    (0x1)

/* AVG_EN bitfield -- 1 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_AVG_EN_MSK               (0x00000400u)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_AVG_EN_SHFT              (10u)

/* SAMPLE_TIME_SEL bitfield -- 2 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_MSK      (0x00003000u)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_SHFT     (12u)

/* NEG_PIN_ADDR bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_NEG_PIN_ADDR_MSK         (0x00070000u)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_NEG_PIN_ADDR_SHFT        (16u)

/* NEG_PORT_ADDR bitfield -- 3 bits wide -- RW access */
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_NEG_PORT_ADDR_MSK        (0x00700000u)
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_NEG_PORT_ADDR_SHFT       (20u)
/* NEG_PORT_ADDR bitfield enumerated values */
#define `$INSTANCE_NAME`_NEG_PORT_ADDR_SARMUX                     (0x0)
#define `$INSTANCE_NAME`_NEG_PORT_ADDR_CTB3                       (0x4)
/* NEG_ADDR_EN bitfield */
#define `$INSTANCE_NAME`_CHANNEL_CONFIG_NEG_ADDR_EN_MSK           (0x01000000u)
#define `$INSTANCE_NAME`_CHANNEL_CONFIG_NEG_ADDR_EN_SHFT          (24u)
/*Mask for everything that is set by `$INSTANCE_NAME`_channelsConfig[] */
#define `$INSTANCE_NAME`_CHANNEL_CONFIG_MASK                      (0x80003700u)
/* Channels are differential if DIFFERENTIAL _EN or NEG_ADDR_EN */
#define `$INSTANCE_NAME`_CHANNEL_CONFIG_DIFF_ALL_MSK              (`$INSTANCE_NAME`_SAR_CHAN_CONFIG_DIFFERENTIAL_EN_MSK \
                                                                  | `$INSTANCE_NAME`_CHANNEL_CONFIG_NEG_ADDR_EN_MSK)
/* ***********************SAR_CHAN_WORK_REG fields ************************* */
#define `$INSTANCE_NAME`_SAR_WRK_MAX_12BIT                        (0x00001000u)
#define `$INSTANCE_NAME`_SAR_WRK_MAX_10BIT                        (0x00000400u)
#define `$INSTANCE_NAME`_SAR_WRK_MAX_8BIT                         (0x00000100u)


/* ***********************SAR_CHAN_RESULT_REG fields ************************ */
#define `$INSTANCE_NAME`_RESULT_MASK                              (0x0000FFFFLu)
#define `$INSTANCE_NAME`_SATURATE_INTR_MIR                        (0x20000000Lu)
#define `$INSTANCE_NAME`_RANGE_INTR_MIR                           (0x40000000Lu)
#define `$INSTANCE_NAME`_CHAN_RESULT_VALID_MIR                    (0x80000000Lu)


/* ***********************SAR_INTR_MASK_REG fields ************************* */
#define `$INSTANCE_NAME`_EOS_MASK                                 (0x00000001u)
#define `$INSTANCE_NAME`_OVERFLOW_MASK                            (0x00000002u)
#define `$INSTANCE_NAME`_FW_COLLISION_MASK                        (0x00000004u)
#define `$INSTANCE_NAME`_DSI_COLLISION_MASK                       (0x00000008u)
#define `$INSTANCE_NAME`_INJ_EOC_MASK                             (0x00000010u)
#define `$INSTANCE_NAME`_INJ_SATURATE_MASK                        (0x00000020u)
#define `$INSTANCE_NAME`_INJ_RANGE_MASK                           (0x00000040u)
#define `$INSTANCE_NAME`_INJ_COLLISION_MASK                       (0x00000080u)

/* ************************  SAR_STATUS_REG fields ************************* */
#define `$INSTANCE_NAME`_CUR_CHAN_MSK                             (0x0000001Fu)
#define `$INSTANCE_NAME`_SW_VREF_NEG_MSK                          (0x40000000u)
#define `$INSTANCE_NAME`_SW_VREF_NEG_SHFT                         (30u)
#define `$INSTANCE_NAME`_BUSY_MSK                                 (0x80000000u)
#define `$INSTANCE_NAME`_BUSY_SHFT                                (31u)

/* ***********************SAR_MUX_SWITCH0_REG fields *********************** */
#define `$INSTANCE_NAME`_MUX_FW_VSSA_VMINUS                       (0x00010000Lu)


/* ***********************SAR_PUMP_CTRL_REG fields *********************** */
#define `$INSTANCE_NAME`_PUMP_CTRL_ENABLED                        (0x80000000Lu)

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
/* Begin configuration 0 calculated defines                                         */
/* ************************************************************************** */

#define `$INSTANCE_NAME`_CFG0_SAMPLE_TIME01_INIT \
        ((`$INSTANCE_NAME`_CFG0_APERTURE_TIME0 \
        << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME0_SHFT) \
        | (`$INSTANCE_NAME`_CFG0_APERTURE_TIME1 \
        << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME1_SHFT))

#define `$INSTANCE_NAME`_CFG0_SAMPLE_TIME23_INIT \
        ((`$INSTANCE_NAME`_CFG0_APERTURE_TIME2 \
        << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME2_SHFT) \
        | (`$INSTANCE_NAME`_CFG0_APERTURE_TIME3 \
        << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME3_SHFT))

/* Enable soc pin if used */
#define `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_EN_INIT \
        (`$INSTANCE_NAME`_CFG0_USE_SOC \
        << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_SHFT)

/* Set soc operation to edge or level based on sample mode */
#if(`$INSTANCE_NAME`_CFG0_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
    #define `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_LEVEL_INIT    (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_MSK)
#else /* Edge trigger */
    #define `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_LEVEL_INIT    (0u)
#endif /* End `$INSTANCE_NAME`_CFG0_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

/* Set SE_NEG_INPUT */
#if(`$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
    #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT ))
#elif(`$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)
    /* Do not connect VNEG to VREF when one channel in differential mode used */
    /* Only needed for config 0 since 2+ configs == 2+ channels */
    #if((`$INSTANCE_NAME`_CFG0_CHANNEL_COUNT == 1u) && (`$INSTANCE_NAME`_CFG0_SINGLE_PRESENT == 0u))
        #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT     0u
    #else    /* multiple channels or one single channel */
        #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                            << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT )
    #endif /* (`$INSTANCE_NAME`_CFG0_CHANNEL_COUNT == 1u) && (`$INSTANCE_NAME`_CFG0_CHANNELS_MODE != 0u) */
#elif (`$INSTANCE_NAME`_CFG0_SINGLE_PRESENT != 0u)
    #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG0_NEG_OTHER
#else
    #define `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT         0u
#endif /* `$INSTANCE_NAME`_CFG0_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

#if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM > 1u)
    #define `$INSTANCE_NAME`_CFG0_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_cy_psoc4_sarmux_1__VNEG0 << 9u)
    #define `$INSTANCE_NAME`_CFG0_SWITCH_CONF_INIT          0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define `$INSTANCE_NAME`_CFG0_SWITCH_CONF_INIT          `$INSTANCE_NAME`_SAR_CTRL_SWITCH_DISABLE_MSK
    #define `$INSTANCE_NAME`_CFG0_NEG_OTHER                 0u
#endif /* `$INSTANCE_NAME`_CFG0_CHANNEL_COUNT > 1u */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u)
    #define `$INSTANCE_NAME`_CFG0_HW_CTRL_NEGVREF_INIT      0u
#else
    #define `$INSTANCE_NAME`_CFG0_HW_CTRL_NEGVREF_INIT      `$INSTANCE_NAME`_SAR_CTRL_SAR_HW_CTRL_NEGVREF_MSK
#endif /* `$INSTANCE_NAME`_CFG0_CHANNEL_COUNT == 1u */

#define `$INSTANCE_NAME`_CFG0_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

/* SAMPLE_CTRL initial values */
#define `$INSTANCE_NAME`_CFG0_SE_RESULT_FORMAT_INIT \
        (`$INSTANCE_NAME`_CFG0_SINGLE_ENDED_FORMAT \
        << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_SHFT)

#define `$INSTANCE_NAME`_CFG0_DIFF_RESULT_FORMAT_INIT \
        (`$INSTANCE_NAME`_CFG0_DIFFERENTIAL_FORMAT \
        << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_SHFT)

#define `$INSTANCE_NAME`_CFG0_AVG_SAMPLES_NUM_INIT \
        (`$INSTANCE_NAME`_CFG0_SAMPLES_AVERAGED \
        << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_CNT_SHFT)

/* Combination of Average Mode and Average Shift */
#define `$INSTANCE_NAME`_CFG0_AVG_MODE_INIT \
        (`$INSTANCE_NAME`_CFG0_AVGERAGING_MODE \
        << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_SHIFT_SHFT)

/* If using a filter, set TRIGGER_OUT_EN  and SCAN_MODE to scheduled*/
#if(`$INSTANCE_NAME`_CFG0_FILTER_PRESENT == 1uL)
    #define `$INSTANCE_NAME`_CFG0_TRIGGER_OUT_INIT \
            (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_MSK)
    #define `$INSTANCE_NAME`_CFG0_UAB_SCAN_MODE_INIT \
            (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_UAB_SCAN_MODE_MSK)
#else
    #define `$INSTANCE_NAME`_CFG0_TRIGGER_OUT_INIT      (0u)
    #define `$INSTANCE_NAME`_CFG0_UAB_SCAN_MODE_INIT    (0u)
#endif

#define `$INSTANCE_NAME`_CFG0_CTRL_INIT  \
        (`$INSTANCE_NAME`_CFG0_VREF_SEL_MASK \
        | `$INSTANCE_NAME`_CFG0_POWER_INIT \
        | `$INSTANCE_NAME`_SAR_CTRL_REFBUF_EN_MSK \
        | `$INSTANCE_NAME`_SAR_CTRL_DSI_SYNC_CONFIG_MSK  \
        | `$INSTANCE_NAME`_CFG0_SWITCH_CONF_INIT \
        | `$INSTANCE_NAME`_CFG0_SE_NEG_INPUT_INIT \
        | `$INSTANCE_NAME`_CFG0_HW_CTRL_NEGVREF_INIT )

#define `$INSTANCE_NAME`_CFG0_SAMPLE_CTRL_INIT \
        (`$INSTANCE_NAME`_CFG0_SUB_RESOLUTION \
        | `$INSTANCE_NAME`_CFG0_SE_RESULT_FORMAT_INIT \
        | `$INSTANCE_NAME`_CFG0_DIFF_RESULT_FORMAT_INIT \
        | `$INSTANCE_NAME`_CFG0_AVG_SAMPLES_NUM_INIT \
        | `$INSTANCE_NAME`_CFG0_AVG_MODE_INIT \
        | `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_LEVEL_INIT \
        | `$INSTANCE_NAME`_CFG0_DSI_TRIGGER_EN_INIT \
        | `$INSTANCE_NAME`_CFG0_UAB_SCAN_MODE_INIT \
        | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_IGNORE_MSK \
        | `$INSTANCE_NAME`_CFG0_TRIGGER_OUT_INIT \
        | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_MSK \
)

#define `$INSTANCE_NAME`_CFG0_RANGE_THRES_INIT \
        (`$INSTANCE_NAME`_CFG0_LOW_LIMIT \
        | (uint32)((uint32)`$INSTANCE_NAME`_CFG0_HIGH_LIMIT \
        << `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_HIGH_SHFT))

#define `$INSTANCE_NAME`_CFG0_RANGE_COND_INIT \
        ((uint32)(`$INSTANCE_NAME`_CFG0_RANGE_COND \
        << `$INSTANCE_NAME`_SAR_RANGE_COND_RANGE_COND_SHFT))
/* Misc Config
    [0] - Freerunning: Set if the sample mode is freerunning
    [1] - Filter Present: Set if the configuration uses a UAB filter
*/
#define `$INSTANCE_NAME`_CFG0_MISC_CONFIG_INIT \
        (`$INSTANCE_NAME`_CFG0_FREERUNNING \
        | (`$INSTANCE_NAME`_CFG0_FILTER_PRESENT \
        << `$INSTANCE_NAME`_MISC_CONFIG_FILTER_PRESENT_SHFT))
/* ************************************************************************** */
/* End configuration 0 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 1 calculated defines                                         */
/* ************************************************************************** */

#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 1)
    #define `$INSTANCE_NAME`_CFG1_SAMPLE_TIME01_INIT \
            ((`$INSTANCE_NAME`_CFG1_APERTURE_TIME0 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME0_SHFT) \
            | (`$INSTANCE_NAME`_CFG1_APERTURE_TIME1 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME1_SHFT))

    #define `$INSTANCE_NAME`_CFG1_SAMPLE_TIME23_INIT \
            ((`$INSTANCE_NAME`_CFG1_APERTURE_TIME2 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME2_SHFT) \
            | (`$INSTANCE_NAME`_CFG1_APERTURE_TIME3 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME3_SHFT))

    /* Enable soc pin if used */
    #define `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_EN_INIT \
            (`$INSTANCE_NAME`_CFG1_USE_SOC \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_SHFT)

    /* Set soc operation to edge or level based on sample mode */
    #if(`$INSTANCE_NAME`_CFG1_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
        #define `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_LEVEL_INIT    (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_MSK)
    #else /* Edge trigger */
        #define `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End `$INSTANCE_NAME`_CFG1_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

    /* Set SE_NEG_INPUT */
    #if(`$INSTANCE_NAME`_CFG1_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT ))
    #elif(`$INSTANCE_NAME`_CFG1_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                            << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT )
    #elif (`$INSTANCE_NAME`_CFG1_SINGLE_PRESENT != 0u)
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG1_NEG_OTHER
    #else
        #define `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT         0u
    #endif /* `$INSTANCE_NAME`_CFG1_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

    #define `$INSTANCE_NAME`_CFG1_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_cy_psoc4_sarmux_1__VNEG1 << 9u)
    #define `$INSTANCE_NAME`_CFG1_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define `$INSTANCE_NAME`_CFG1_HW_CTRL_NEGVREF_INIT      `$INSTANCE_NAME`_SAR_CTRL_SAR_HW_CTRL_NEGVREF_MSK

    #define `$INSTANCE_NAME`_CFG1_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define `$INSTANCE_NAME`_CFG1_SE_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG1_SINGLE_ENDED_FORMAT \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_SHFT)

    #define `$INSTANCE_NAME`_CFG1_DIFF_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG1_DIFFERENTIAL_FORMAT \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_SHFT)

    #define `$INSTANCE_NAME`_CFG1_AVG_SAMPLES_NUM_INIT \
            (`$INSTANCE_NAME`_CFG1_SAMPLES_AVERAGED \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_CNT_SHFT)

    /* Combination of Average Mode and Average Shift */
    #define `$INSTANCE_NAME`_CFG1_AVG_MODE_INIT \
            (`$INSTANCE_NAME`_CFG1_AVGERAGING_MODE \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_SHIFT_SHFT)

    /* If using a filter, set TRIGGER_OUT_EN  and SCAN_MODE to scheduled*/
    #if(`$INSTANCE_NAME`_CFG1_FILTER_PRESENT == 1uL)
        #define `$INSTANCE_NAME`_CFG1_TRIGGER_OUT_INIT \
                (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_MSK)
        #define `$INSTANCE_NAME`_CFG1_UAB_SCAN_MODE_INIT \
                (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_UAB_SCAN_MODE_MSK)
    #else
        #define `$INSTANCE_NAME`_CFG1_TRIGGER_OUT_INIT      (0u)
        #define `$INSTANCE_NAME`_CFG1_UAB_SCAN_MODE_INIT    (0u)
    #endif

    #define `$INSTANCE_NAME`_CFG1_CTRL_INIT  \
            (`$INSTANCE_NAME`_CFG1_VREF_SEL_MASK \
            | `$INSTANCE_NAME`_CFG1_POWER_INIT \
            | `$INSTANCE_NAME`_SAR_CTRL_REFBUF_EN_MSK \
            | `$INSTANCE_NAME`_SAR_CTRL_DSI_SYNC_CONFIG_MSK  \
            | `$INSTANCE_NAME`_CFG1_SWITCH_CONF_INIT \
            | `$INSTANCE_NAME`_CFG1_SE_NEG_INPUT_INIT \
            | `$INSTANCE_NAME`_CFG1_HW_CTRL_NEGVREF_INIT )

    #define `$INSTANCE_NAME`_CFG1_SAMPLE_CTRL_INIT \
            (`$INSTANCE_NAME`_CFG1_SUB_RESOLUTION \
            | `$INSTANCE_NAME`_CFG1_SE_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG1_DIFF_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG1_AVG_SAMPLES_NUM_INIT \
            | `$INSTANCE_NAME`_CFG1_AVG_MODE_INIT \
            | `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_LEVEL_INIT \
            | `$INSTANCE_NAME`_CFG1_DSI_TRIGGER_EN_INIT \
            | `$INSTANCE_NAME`_CFG1_UAB_SCAN_MODE_INIT \
            | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_IGNORE_MSK \
            | `$INSTANCE_NAME`_CFG1_TRIGGER_OUT_INIT \
            | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_MSK \
    )

    #define `$INSTANCE_NAME`_CFG1_RANGE_THRES_INIT \
            (`$INSTANCE_NAME`_CFG1_LOW_LIMIT \
            | (uint32)((uint32)`$INSTANCE_NAME`_CFG1_HIGH_LIMIT \
            << `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_HIGH_SHFT))

    #define `$INSTANCE_NAME`_CFG1_RANGE_COND_INIT \
            ((uint32)(`$INSTANCE_NAME`_CFG1_RANGE_COND \
            << `$INSTANCE_NAME`_SAR_RANGE_COND_RANGE_COND_SHFT))
    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
        [1] - Filter Present: Set if the configuration uses a UAB filter
    */
    #define `$INSTANCE_NAME`_CFG1_MISC_CONFIG_INIT \
            (`$INSTANCE_NAME`_CFG1_FREERUNNING \
            | (`$INSTANCE_NAME`_CFG1_FILTER_PRESENT \
            << `$INSTANCE_NAME`_MISC_CONFIG_FILTER_PRESENT_SHFT))
#endif /* `$INSTANCE_NAME`_TOTAL_CONFIGS > 1 */

/* ************************************************************************** */
/* End configuration 1 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 2 calculated defines                                         */
/* ************************************************************************** */

#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 2)
    #define `$INSTANCE_NAME`_CFG2_SAMPLE_TIME01_INIT \
            ((`$INSTANCE_NAME`_CFG2_APERTURE_TIME0 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME0_SHFT) \
            | (`$INSTANCE_NAME`_CFG2_APERTURE_TIME1 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME1_SHFT))

    #define `$INSTANCE_NAME`_CFG2_SAMPLE_TIME23_INIT \
            ((`$INSTANCE_NAME`_CFG2_APERTURE_TIME2 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME2_SHFT) \
            | (`$INSTANCE_NAME`_CFG2_APERTURE_TIME3 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME3_SHFT))

    /* Enable soc pin if used */
    #define `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_EN_INIT \
            (`$INSTANCE_NAME`_CFG2_USE_SOC \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_SHFT)

    /* Set soc operation to edge or level based on sample mode */
    #if(`$INSTANCE_NAME`_CFG2_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
        #define `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_LEVEL_INIT    (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_MSK)
    #else /* Edge trigger */
        #define `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End `$INSTANCE_NAME`_CFG2_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

    /* Set SE_NEG_INPUT */
    #if(`$INSTANCE_NAME`_CFG2_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT ))
    #elif(`$INSTANCE_NAME`_CFG2_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                                << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT )
    #elif (`$INSTANCE_NAME`_CFG2_SINGLE_PRESENT != 0u)
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG2_NEG_OTHER
    #else
        #define `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT         0u
    #endif /* `$INSTANCE_NAME`_CFG2_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

   #define `$INSTANCE_NAME`_CFG2_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_cy_psoc4_sarmux_1__VNEG2 << 9u)
   
    #define `$INSTANCE_NAME`_CFG2_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define `$INSTANCE_NAME`_CFG2_HW_CTRL_NEGVREF_INIT      `$INSTANCE_NAME`_SAR_CTRL_SAR_HW_CTRL_NEGVREF_MSK

    #define `$INSTANCE_NAME`_CFG2_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define `$INSTANCE_NAME`_CFG2_SE_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG2_SINGLE_ENDED_FORMAT \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_SHFT)

    #define `$INSTANCE_NAME`_CFG2_DIFF_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG2_DIFFERENTIAL_FORMAT \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_SHFT)

    #define `$INSTANCE_NAME`_CFG2_AVG_SAMPLES_NUM_INIT \
            (`$INSTANCE_NAME`_CFG2_SAMPLES_AVERAGED \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_CNT_SHFT)

    /* Combination of Average Mode and Average Shift */
    #define `$INSTANCE_NAME`_CFG2_AVG_MODE_INIT \
            (`$INSTANCE_NAME`_CFG2_AVGERAGING_MODE \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_SHIFT_SHFT)

    /* If using a filter, set TRIGGER_OUT_EN  and SCAN_MODE to scheduled*/
    #if(`$INSTANCE_NAME`_CFG2_FILTER_PRESENT == 1uL)
        #define `$INSTANCE_NAME`_CFG2_TRIGGER_OUT_INIT \
                (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_MSK)
        #define `$INSTANCE_NAME`_CFG2_UAB_SCAN_MODE_INIT \
                (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_UAB_SCAN_MODE_MSK)
    #else
        #define `$INSTANCE_NAME`_CFG2_TRIGGER_OUT_INIT      (0u)
        #define `$INSTANCE_NAME`_CFG2_UAB_SCAN_MODE_INIT    (0u)
    #endif

    #define `$INSTANCE_NAME`_CFG2_CTRL_INIT  \
            (`$INSTANCE_NAME`_CFG2_VREF_SEL_MASK \
            | `$INSTANCE_NAME`_CFG2_POWER_INIT \
            | `$INSTANCE_NAME`_SAR_CTRL_REFBUF_EN_MSK \
            | `$INSTANCE_NAME`_SAR_CTRL_DSI_SYNC_CONFIG_MSK  \
            | `$INSTANCE_NAME`_CFG2_SWITCH_CONF_INIT \
            | `$INSTANCE_NAME`_CFG2_SE_NEG_INPUT_INIT \
            | `$INSTANCE_NAME`_CFG2_HW_CTRL_NEGVREF_INIT )


    #define `$INSTANCE_NAME`_CFG2_SAMPLE_CTRL_INIT \
            (`$INSTANCE_NAME`_CFG2_SUB_RESOLUTION \
            | `$INSTANCE_NAME`_CFG2_SE_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG2_DIFF_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG2_AVG_SAMPLES_NUM_INIT \
            | `$INSTANCE_NAME`_CFG2_AVG_MODE_INIT \
            | `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_LEVEL_INIT \
            | `$INSTANCE_NAME`_CFG2_DSI_TRIGGER_EN_INIT \
            | `$INSTANCE_NAME`_CFG2_UAB_SCAN_MODE_INIT \
            | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_IGNORE_MSK \
            | `$INSTANCE_NAME`_CFG2_TRIGGER_OUT_INIT \
            | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_MSK \
    )

    #define `$INSTANCE_NAME`_CFG2_RANGE_THRES_INIT \
            (`$INSTANCE_NAME`_CFG2_LOW_LIMIT \
            | (uint32)((uint32)`$INSTANCE_NAME`_CFG2_HIGH_LIMIT \
            << `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_HIGH_SHFT))

    #define `$INSTANCE_NAME`_CFG2_RANGE_COND_INIT \
            ((uint32)(`$INSTANCE_NAME`_CFG2_RANGE_COND \
            << `$INSTANCE_NAME`_SAR_RANGE_COND_RANGE_COND_SHFT))
    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
        [1] - Filter Present: Set if the configuration uses a UAB filter
    */
    #define `$INSTANCE_NAME`_CFG2_MISC_CONFIG_INIT \
            (`$INSTANCE_NAME`_CFG2_FREERUNNING \
            | (`$INSTANCE_NAME`_CFG2_FILTER_PRESENT \
            << `$INSTANCE_NAME`_MISC_CONFIG_FILTER_PRESENT_SHFT))
#endif /* `$INSTANCE_NAME`_TOTAL_CONFIGS > 2 */

/* ************************************************************************** */
/* End configuration 2 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 3 calculated defines                                         */
/* ************************************************************************** */

#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 3)
    #define `$INSTANCE_NAME`_CFG3_SAMPLE_TIME01_INIT \
            ((`$INSTANCE_NAME`_CFG3_APERTURE_TIME0 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME0_SHFT) \
            | (`$INSTANCE_NAME`_CFG3_APERTURE_TIME1 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_SAMPLE_TIME1_SHFT))

    #define `$INSTANCE_NAME`_CFG3_SAMPLE_TIME23_INIT \
            ((`$INSTANCE_NAME`_CFG3_APERTURE_TIME2 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME2_SHFT) \
            | (`$INSTANCE_NAME`_CFG3_APERTURE_TIME3 \
            << `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_SAMPLE_TIME3_SHFT))

    /* Enable soc pin if used */
    #define `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_EN_INIT \
            (`$INSTANCE_NAME`_CFG3_USE_SOC \
             << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_SHFT)

    /* Set soc operation to edge or level based on sample mode */
    #if(`$INSTANCE_NAME`_CFG3_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING)
        #define `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_LEVEL_INIT    (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_MSK)
    #else /* Edge trigger */
        #define `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End `$INSTANCE_NAME`_CFG3_FREERUNNING == `$INSTANCE_NAME`_FREERUNNING */

    /* Set SE_NEG_INPUT  */
    #if(`$INSTANCE_NAME`_CFG3_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN)
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT \
            ((uint32)(`$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN \
            << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT ))
    #elif(`$INSTANCE_NAME`_CFG3_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VREF)
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT     (`$INSTANCE_NAME`_NEG_SEL_VREF \
                                                                << `$INSTANCE_NAME`_SAR_CTRL_NEG_SEL_SHFT )
    #elif (`$INSTANCE_NAME`_CFG3_SINGLE_PRESENT != 0u)
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT         `$INSTANCE_NAME`_CFG3_NEG_OTHER
    #else
        #define `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT         0u
    #endif /* `$INSTANCE_NAME`_CFG3_VNEG_INPUT_SEL == `$INSTANCE_NAME`_NEG_SEL_VSSA_KELVIN */

    #define `$INSTANCE_NAME`_CFG3_NEG_OTHER                 (uint16)((uint16)`$INSTANCE_NAME`_cy_psoc4_sarmux_1__VNEG3 << 9u)

    #define `$INSTANCE_NAME`_CFG3_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define `$INSTANCE_NAME`_CFG3_HW_CTRL_NEGVREF_INIT      `$INSTANCE_NAME`_SAR_CTRL_SAR_HW_CTRL_NEGVREF_MSK

    #define `$INSTANCE_NAME`_CFG3_POWER_INIT  (`$INSTANCE_NAME`_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define `$INSTANCE_NAME`_CFG3_SE_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG3_SINGLE_ENDED_FORMAT \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_SHFT)

    #define `$INSTANCE_NAME`_CFG3_DIFF_RESULT_FORMAT_INIT \
            (`$INSTANCE_NAME`_CFG3_DIFFERENTIAL_FORMAT \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_SHFT)

    #define `$INSTANCE_NAME`_CFG3_AVG_SAMPLES_NUM_INIT \
            (`$INSTANCE_NAME`_CFG3_SAMPLES_AVERAGED \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_CNT_SHFT)

    /* Combination of Average Mode and Average Shift */
    #define `$INSTANCE_NAME`_CFG3_AVG_MODE_INIT \
            (`$INSTANCE_NAME`_CFG3_AVGERAGING_MODE \
            << `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_AVG_SHIFT_SHFT)

    /* If using a filter, set TRIGGER_OUT_EN  and SCAN_MODE to scheduled*/
    #if(`$INSTANCE_NAME`_CFG3_FILTER_PRESENT == 1uL)
        #define `$INSTANCE_NAME`_CFG3_TRIGGER_OUT_INIT \
                (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_MSK)
        #define `$INSTANCE_NAME`_CFG3_UAB_SCAN_MODE_INIT \
                (`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_UAB_SCAN_MODE_MSK)
    #else
        #define `$INSTANCE_NAME`_CFG3_TRIGGER_OUT_INIT      (0u)
        #define `$INSTANCE_NAME`_CFG3_UAB_SCAN_MODE_INIT    (0u)
    #endif

    #define `$INSTANCE_NAME`_CFG3_CTRL_INIT  \
            (`$INSTANCE_NAME`_CFG3_VREF_SEL_MASK \
            | `$INSTANCE_NAME`_CFG3_POWER_INIT \
            | `$INSTANCE_NAME`_SAR_CTRL_REFBUF_EN_MSK \
            | `$INSTANCE_NAME`_SAR_CTRL_DSI_SYNC_CONFIG_MSK  \
            | `$INSTANCE_NAME`_CFG3_SWITCH_CONF_INIT \
            | `$INSTANCE_NAME`_CFG3_SE_NEG_INPUT_INIT \
            | `$INSTANCE_NAME`_CFG3_HW_CTRL_NEGVREF_INIT )


    #define `$INSTANCE_NAME`_CFG3_SAMPLE_CTRL_INIT \
            (`$INSTANCE_NAME`_CFG3_SUB_RESOLUTION \
            | `$INSTANCE_NAME`_CFG3_SE_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG3_DIFF_RESULT_FORMAT_INIT \
            | `$INSTANCE_NAME`_CFG3_AVG_SAMPLES_NUM_INIT \
            | `$INSTANCE_NAME`_CFG3_AVG_MODE_INIT \
            | `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_LEVEL_INIT \
            | `$INSTANCE_NAME`_CFG3_DSI_TRIGGER_EN_INIT \
            | `$INSTANCE_NAME`_CFG3_UAB_SCAN_MODE_INIT \
            | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_VALID_IGNORE_MSK \
            | `$INSTANCE_NAME`_CFG3_TRIGGER_OUT_INIT \
            | `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_MSK \
    )

    #define `$INSTANCE_NAME`_CFG3_RANGE_THRES_INIT \
            (`$INSTANCE_NAME`_CFG3_LOW_LIMIT \
            | (uint32)((uint32)`$INSTANCE_NAME`_CFG3_HIGH_LIMIT \
            << `$INSTANCE_NAME`_SAR_RANGE_THRES_RANGE_HIGH_SHFT))

    #define `$INSTANCE_NAME`_CFG3_RANGE_COND_INIT \
            ((uint32)(`$INSTANCE_NAME`_CFG3_RANGE_COND \
            << `$INSTANCE_NAME`_SAR_RANGE_COND_RANGE_COND_SHFT))
    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
        [1] - Filter Present: Set if the configuration uses a UAB filter
    */
    #define `$INSTANCE_NAME`_CFG3_MISC_CONFIG_INIT \
            (`$INSTANCE_NAME`_CFG3_FREERUNNING \
            | (`$INSTANCE_NAME`_CFG3_FILTER_PRESENT \
            << `$INSTANCE_NAME`_MISC_CONFIG_FILTER_PRESENT_SHFT))

#endif /* `$INSTANCE_NAME`_TOTAL_CONFIGS > 3 */

/* ************************************************************************** */
/* End configuration 3 calculated defines                                     */
/* ************************************************************************** */


/*******************************************************************************
*       Configuration Structure Constants
*******************************************************************************/

/* Misc Config
    [0] - Freerunning: Set if the sample mode is freerunning
    [1] - Filter Present: Set if the configuration uses a UAB filter
    [2] - Mux Switch 0: Set when VSSA is used for the neg input to any single-ended channel
*/
#define `$INSTANCE_NAME`_MISC_CONFIG_FREERUNNING_MSK        0x01u
#define `$INSTANCE_NAME`_MISC_CONFIG_FILTER_PRESENT_MSK     0x02u
#define `$INSTANCE_NAME`_MISC_CONFIG_FILTER_PRESENT_SHFT    0x01u
#define `$INSTANCE_NAME`_MISC_CONFIG_MUX_SWITCH0_MSK        0x04u
#define `$INSTANCE_NAME`_MISC_CONFIG_MUX_SWITCH0_SHFT       0x02u

`$FILTER_TYPE_ENUM_DEF`
/* Configuration description defines */
`$ConfigDescriptionDefines`
#endif /* !defined(CY_`$INSTANCE_NAME`_H) */
/* [] END OF FILE */
