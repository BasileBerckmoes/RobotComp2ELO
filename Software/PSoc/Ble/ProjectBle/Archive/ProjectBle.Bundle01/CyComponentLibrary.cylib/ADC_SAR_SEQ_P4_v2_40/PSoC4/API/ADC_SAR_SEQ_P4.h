/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Sequencing Successive Approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ADC_SAR_SEQ_`$INSTANCE_NAME`_H)
#define CY_ADC_SAR_SEQ_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Clock Source setting constants */
`#cy_declare_enum AdcClockSrcType`
/*  Sample Mode setting constants */
`#cy_declare_enum AdcSampleModeType`
/*  Reference type setting constants */
`#cy_declare_enum AdcVrefSelectType`
/* Input buffer gain setting constants */
`#cy_declare_enum AdcInputBufferGainType`
/* Negative input setting sonstants in single ended mode */
`#cy_declare_enum AdcSingleEndedNegativeInputType`
/* Compare mode setting constants:
*    Mode0 - Disable
*    Mode1 - Result < Low_Limit
*    Mode2 - Low_Limit <= Result < High_Limit
*    Mode3 - High_Limit <= Result
*    Mode4 - (Result < Low_Limit) or (High_Limit <= Result)
*/
`#cy_declare_enum AdcCompareModeType`
`#cy_declare_enum AdcAlternativeResolutionType`
`#cy_declare_enum AdcDataFormatJustificationType`
`#cy_declare_enum AdcResultFormatType`
`#cy_declare_enum AdcAvgModeType`


/***************************************
*   Conditional Compilation Parameters
****************************************/ 

#define `$INSTANCE_NAME`_CY_SAR_IP_VER0               	(0u)
#define `$INSTANCE_NAME`_CY_SAR_IP_VER1               	(1u)

#if (CY_PSOC4_4100 || CY_PSOC4_4200)
    #define `$INSTANCE_NAME`_CY_SAR_IP_VER              (`$INSTANCE_NAME`_CY_SAR_IP_VER0)
#else /* Other devices */
    #define `$INSTANCE_NAME`_CY_SAR_IP_VER              (`$INSTANCE_NAME`_CY_SAR_IP_VER1)
#endif  /* (CY_PSOC4_4100 || CY_PSOC4_4200) */


/***************************************
*    Initial Parameter Constants
***************************************/
#define `$INSTANCE_NAME`_DEFAULT_SAMPLE_MODE_SEL        (`$AdcSampleMode`u)
#define `$INSTANCE_NAME`_DEFAULT_VREF_SEL               (`$AdcVrefSelect`u)
#define `$INSTANCE_NAME`_DEFAULT_NEG_INPUT_SEL          (`$AdcSingleEndedNegativeInput`u)
#define `$INSTANCE_NAME`_DEFAULT_ALT_RESOLUTION_SEL     (`$AdcAlternateResolution`u)
#define `$INSTANCE_NAME`_DEFAULT_JUSTIFICATION_SEL      (`$AdcDataFormatJustification`u)
#define `$INSTANCE_NAME`_DEFAULT_DIFF_RESULT_FORMAT_SEL (`$AdcDifferentialResultFormat`u)
#define `$INSTANCE_NAME`_DEFAULT_SE_RESULT_FORMAT_SEL   (`$AdcSingleResultFormat`u)
#define `$INSTANCE_NAME`_DEFAULT_CLOCK_SOURCE           (`$AdcClock`u)
#define `$INSTANCE_NAME`_DEFAULT_VREF_MV_VALUE          (`$AdcVrefVoltage_mV`)
#define `$INSTANCE_NAME`_DEFAULT_BUFFER_GAIN            (`$AdcInputBufGain`u)
#define `$INSTANCE_NAME`_DEFAULT_AVG_SAMPLES_NUM        (`$AdcAvgSamplesNum`u)
#define `$INSTANCE_NAME`_DEFAULT_AVG_SAMPLES_DIV        (int16)(0x100u >> (7u - `$AdcAvgSamplesNum`u))
#define `$INSTANCE_NAME`_DEFAULT_AVG_MODE               (`$AdcAvgMode`u)
#define `$INSTANCE_NAME`_MAX_RESOLUTION                 (`$AdcMaxResolution`u)
#define `$INSTANCE_NAME`_DEFAULT_LOW_LIMIT              (`$AdcLowLimit`u)
#define `$INSTANCE_NAME`_DEFAULT_HIGH_LIMIT             (`$AdcHighLimit`u)
#define `$INSTANCE_NAME`_DEFAULT_COMPARE_MODE           (`$AdcCompareMode`u)
#define `$INSTANCE_NAME`_DEFAULT_ACLKS_NUM              (`$AdcAClock`u)
#define `$INSTANCE_NAME`_DEFAULT_BCLKS_NUM              (`$AdcBClock`u)
#define `$INSTANCE_NAME`_DEFAULT_CCLKS_NUM              (`$AdcCClock`u)
#define `$INSTANCE_NAME`_DEFAULT_DCLKS_NUM              (`$AdcDClock`u)
#define `$INSTANCE_NAME`_TOTAL_CHANNELS_NUM             (`$AdcTotalChannels`u)
#define `$INSTANCE_NAME`_SEQUENCED_CHANNELS_NUM         (`$AdcSequencedChannels`u)
#define `$INSTANCE_NAME`_DEFAULT_EN_CHANNELS            (`$AdcChannelsEnConf`u)
#define `$INSTANCE_NAME`_NOMINAL_CLOCK_FREQ             (`$NominalClockFrequency`)
#define `$INSTANCE_NAME`_INJ_CHANNEL_ENABLED            (`$AdcInjChannelEnabled`u)
#define `$INSTANCE_NAME`_IRQ_REMOVE                     (`$rm_int`u)

/* Determines whether the configuration contains external negative input. */
#define `$INSTANCE_NAME`_SINGLE_PRESENT                 (`$AdcSymbolHasSingleEndedInputChannel`u)
#define `$INSTANCE_NAME`_CHANNELS_MODE                  (`$AdcChannelsModeConf`u)
#define `$INSTANCE_NAME`_MAX_CHANNELS_EN_MASK           (0xffffu >> (16u - `$INSTANCE_NAME`_SEQUENCED_CHANNELS_NUM))


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_StartConvert(void);
void `$INSTANCE_NAME`_StopConvert(void);
uint32 `$INSTANCE_NAME`_IsEndConversion(uint32 retMode);
int16 `$INSTANCE_NAME`_GetResult16(uint32 chan);
void `$INSTANCE_NAME`_SetChanMask(uint32 mask);
void `$INSTANCE_NAME`_SetLowLimit(uint32 lowLimit);
void `$INSTANCE_NAME`_SetHighLimit(uint32 highLimit);
void `$INSTANCE_NAME`_SetLimitMask(uint32 mask);
void `$INSTANCE_NAME`_SetSatMask(uint32 mask);
void `$INSTANCE_NAME`_SetOffset(uint32 chan, int16 offset);
void `$INSTANCE_NAME`_SetGain(uint32 chan, int32 adcGain);
#if(`$INSTANCE_NAME`_INJ_CHANNEL_ENABLED)
    void `$INSTANCE_NAME`_EnableInjection(void);
#endif /* `$INSTANCE_NAME`_INJ_CHANNEL_ENABLED */
#if(`$INSTANCE_NAME`_DEFAULT_JUSTIFICATION_SEL == `$INSTANCE_NAME`__RIGHT)
    int16 `$INSTANCE_NAME`_CountsTo_mVolts(uint32 chan, int16 adcCounts);
    int32 `$INSTANCE_NAME`_CountsTo_uVolts(uint32 chan, int16 adcCounts);
    float32 `$INSTANCE_NAME`_CountsTo_Volts(uint32 chan, int16 adcCounts);
#endif /* End `$INSTANCE_NAME`_DEFAULT_JUSTIFICATION_SEL == `$INSTANCE_NAME`__RIGHT */
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);

CY_ISR_PROTO( `$INSTANCE_NAME`_ISR );


/**************************************
*           API Constants
**************************************/
/* Constants for Sleep mode states */
#define `$INSTANCE_NAME`_DISABLED                   (0x00u)
#define `$INSTANCE_NAME`_ENABLED                    (0x01u)
#define `$INSTANCE_NAME`_STARTED                    (0x02u)
#define `$INSTANCE_NAME`_BOOSTPUMP_ENABLED          (0x04u)

/*   Constants for IsEndConversion() "retMode" parameter  */
#define `$INSTANCE_NAME`_RETURN_STATUS              (0x01u)
#define `$INSTANCE_NAME`_WAIT_FOR_RESULT            (0x02u)
#define `$INSTANCE_NAME`_RETURN_STATUS_INJ          (0x04u)
#define `$INSTANCE_NAME`_WAIT_FOR_RESULT_INJ        (0x08u)

#define `$INSTANCE_NAME`_MAX_FREQUENCY              (18000000)       /*18Mhz*/

#define `$INSTANCE_NAME`_RESOLUTION_12              (12u)
#define `$INSTANCE_NAME`_RESOLUTION_10              (10u)
#define `$INSTANCE_NAME`_RESOLUTION_8               (8u)

#define `$INSTANCE_NAME`_10US_DELAY                 (10u)

#define `$INSTANCE_NAME`_10V_COUNTS                 (10.0F)
#define `$INSTANCE_NAME`_10MV_COUNTS                (10000)
#define `$INSTANCE_NAME`_10UV_COUNTS                (10000000L)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;
extern volatile int16 `$INSTANCE_NAME`_offset[`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM];
extern volatile int32 `$INSTANCE_NAME`_countsPer10Volt[`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM];


/***************************************
*              Registers
***************************************/

#define `$INSTANCE_NAME`_SAR_CTRL_REG                (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CTRL )
#define `$INSTANCE_NAME`_SAR_CTRL_PTR                ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CTRL )

#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SAMPLE_CTRL )
#define `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SAMPLE_CTRL )

#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_REG       (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SAMPLE_TIME01 )
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME01_PTR       ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SAMPLE_TIME01 )

#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_REG       (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SAMPLE_TIME23 )
#define `$INSTANCE_NAME`_SAR_SAMPLE_TIME23_PTR       ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SAMPLE_TIME23 )

#define `$INSTANCE_NAME`_SAR_RANGE_THRES_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_THRES )
#define `$INSTANCE_NAME`_SAR_RANGE_THRES_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_THRES )

#define `$INSTANCE_NAME`_SAR_RANGE_COND_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_COND )
#define `$INSTANCE_NAME`_SAR_RANGE_COND_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_COND )

#define `$INSTANCE_NAME`_SAR_CHAN_EN_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_EN )
#define `$INSTANCE_NAME`_SAR_CHAN_EN_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_EN )

#define `$INSTANCE_NAME`_SAR_START_CTRL_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_START_CTRL )
#define `$INSTANCE_NAME`_SAR_START_CTRL_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_START_CTRL )

#define `$INSTANCE_NAME`_SAR_DFT_CTRL_REG            (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_DFT_CTRL )
#define `$INSTANCE_NAME`_SAR_DFT_CTRL_PTR            ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_DFT_CTRL )

#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define `$INSTANCE_NAME`_SAR_CHAN_CONFIG_IND         `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_CONFIG00

#define `$INSTANCE_NAME`_SAR_CHAN_WORK_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_WORK00 )
#define `$INSTANCE_NAME`_SAR_CHAN_WORK_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_WORK00 )

#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_IND         `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT00

#define `$INSTANCE_NAME`_SAR_CHAN0_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define `$INSTANCE_NAME`_SAR_CHAN0_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT00 )

#define `$INSTANCE_NAME`_SAR_CHAN1_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT01 )
#define `$INSTANCE_NAME`_SAR_CHAN1_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT01 )

#define `$INSTANCE_NAME`_SAR_CHAN2_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT02 )
#define `$INSTANCE_NAME`_SAR_CHAN2_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT02 )

#define `$INSTANCE_NAME`_SAR_CHAN3_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT03 )
#define `$INSTANCE_NAME`_SAR_CHAN3_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT03 )

#define `$INSTANCE_NAME`_SAR_CHAN4_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT04 )
#define `$INSTANCE_NAME`_SAR_CHAN4_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT04 )

#define `$INSTANCE_NAME`_SAR_CHAN5_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT05 )
#define `$INSTANCE_NAME`_SAR_CHAN5_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT05 )

#define `$INSTANCE_NAME`_SAR_CHAN6_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT06 )
#define `$INSTANCE_NAME`_SAR_CHAN6_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT06 )

#define `$INSTANCE_NAME`_SAR_CHAN7_RESULT_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT07 )
#define `$INSTANCE_NAME`_SAR_CHAN7_RESULT_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT07 )

#if(`$INSTANCE_NAME`_CY_SAR_IP_VER != `$INSTANCE_NAME`_CY_SAR_IP_VER0)
    #define `$INSTANCE_NAME`_SAR_CHAN8_RESULT_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT08 )
    #define `$INSTANCE_NAME`_SAR_CHAN8_RESULT_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT08 )

    #define `$INSTANCE_NAME`_SAR_CHAN9_RESULT_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT09 )
    #define `$INSTANCE_NAME`_SAR_CHAN9_RESULT_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT09 )

    #define `$INSTANCE_NAME`_SAR_CHAN10_RESULT_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT10 )
    #define `$INSTANCE_NAME`_SAR_CHAN10_RESULT_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT10 )

    #define `$INSTANCE_NAME`_SAR_CHAN11_RESULT_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT11 )
    #define `$INSTANCE_NAME`_SAR_CHAN11_RESULT_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT11 )

    #define `$INSTANCE_NAME`_SAR_CHAN12_RESULT_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT12 )
    #define `$INSTANCE_NAME`_SAR_CHAN12_RESULT_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT12 )

    #define `$INSTANCE_NAME`_SAR_CHAN13_RESULT_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT13 )
    #define `$INSTANCE_NAME`_SAR_CHAN13_RESULT_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT13 )

    #define `$INSTANCE_NAME`_SAR_CHAN14_RESULT_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT14 )
    #define `$INSTANCE_NAME`_SAR_CHAN14_RESULT_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT14 )

    #define `$INSTANCE_NAME`_SAR_CHAN15_RESULT_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT15 )
    #define `$INSTANCE_NAME`_SAR_CHAN15_RESULT_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT15 )
#endif /* (`$INSTANCE_NAME`_CY_SAR_IP_VER != `$INSTANCE_NAME`_CY_SAR_IP_VER0) */

#define `$INSTANCE_NAME`_SAR_CHAN_WORK_VALID_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_WORK_VALID)
#define `$INSTANCE_NAME`_SAR_CHAN_WORK_VALID_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_WORK_VALID)

#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_VALID_REG  ( *(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )
#define `$INSTANCE_NAME`_SAR_CHAN_RESULT_VALID_PTR  ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )

#define `$INSTANCE_NAME`_SAR_STATUS_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_STATUS )
#define `$INSTANCE_NAME`_SAR_STATUS_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_STATUS )

#define `$INSTANCE_NAME`_SAR_AVG_START_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_AVG_STAT )
#define `$INSTANCE_NAME`_SAR_AVG_START_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_AVG_STAT )

#define `$INSTANCE_NAME`_SAR_INTR_REG                (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR )
#define `$INSTANCE_NAME`_SAR_INTR_PTR                ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR )

#define `$INSTANCE_NAME`_SAR_INTR_SET_REG            (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_SET )
#define `$INSTANCE_NAME`_SAR_INTR_SET_PTR            ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_SET )

#define `$INSTANCE_NAME`_SAR_INTR_MASK_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_MASK )
#define `$INSTANCE_NAME`_SAR_INTR_MASK_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_MASK )

#define `$INSTANCE_NAME`_SAR_INTR_MASKED_REG         (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_MASKED )
#define `$INSTANCE_NAME`_SAR_INTR_MASKED_PTR         ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_MASKED )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_REG       (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_PTR       ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_SET_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR_SET )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_SET_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR_SET )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASK_REG (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASK_PTR ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )

#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASKED_REG \
                                                 (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )
#define `$INSTANCE_NAME`_SAR_SATURATE_INTR_MASKED_PTR \
                                                 ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_SET_REG      (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR_SET )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_SET_PTR      ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR_SET )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASK_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR_MASK )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASK_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR_MASK )

#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASKED_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )
#define `$INSTANCE_NAME`_SAR_RANGE_INTR_MASKED_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )

#define `$INSTANCE_NAME`_SAR_INTR_CAUSE_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_CAUSE )
#define `$INSTANCE_NAME`_SAR_INTR_CAUSE_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sar__SAR_INTR_CAUSE )

#if(`$INSTANCE_NAME`_INJ_CHANNEL_ENABLED)
    #define `$INSTANCE_NAME`_SAR_INJ_CHAN_CONFIG_REG \
                                                 (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )
    #define `$INSTANCE_NAME`_SAR_INJ_CHAN_CONFIG_PTR    \
                                                 ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )

    #define `$INSTANCE_NAME`_SAR_INJ_RESULT_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
    #define `$INSTANCE_NAME`_SAR_INJ_RESULT_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
#endif /* `$INSTANCE_NAME`_INJ_CHANNEL_ENABLED */
    
#define `$INSTANCE_NAME`_MUX_SWITCH0_REG           (*(reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_MUX_SWITCH0 )
#define `$INSTANCE_NAME`_MUX_SWITCH0_PTR           ( (reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_MUX_SWITCH0 )

#define `$INSTANCE_NAME`_MUX_SWITCH_HW_CTRL_REG    (*(reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )
#define `$INSTANCE_NAME`_MUX_SWITCH_HW_CTRL_PTR    ( (reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )

#define `$INSTANCE_NAME`_PUMP_CTRL_REG             (*(reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_PUMP_CTRL )
#define `$INSTANCE_NAME`_PUMP_CTRL_PTR             ( (reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_PUMP_CTRL )

#define `$INSTANCE_NAME`_ANA_TRIM_REG              (*(reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_ANA_TRIM )
#define `$INSTANCE_NAME`_ANA_TRIM_PTR              ( (reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_ANA_TRIM )

#define `$INSTANCE_NAME`_WOUNDING_REG              (*(reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_WOUNDING )
#define `$INSTANCE_NAME`_WOUNDING_PTR              ( (reg32 *)  `$INSTANCE_NAME`_cy_psoc4_sar__SAR_WOUNDING )


/**************************************
*       Register Constants
**************************************/
#define `$INSTANCE_NAME`_INTC_NUMBER                (`$INSTANCE_NAME`_IRQ__INTC_NUMBER)
#define `$INSTANCE_NAME`_INTC_PRIOR_NUMBER          (`$INSTANCE_NAME`_IRQ__INTC_PRIOR_NUM)

/* defines for CTRL register */
#define `$INSTANCE_NAME`_VREF_INTERNAL1024          (0x00000040Lu)
#define `$INSTANCE_NAME`_VREF_EXTERNAL              (0x00000050Lu)
#define `$INSTANCE_NAME`_VREF_VDDA_2                (0x00000060Lu)
#define `$INSTANCE_NAME`_VREF_VDDA                  (0x00000070Lu)
#define `$INSTANCE_NAME`_VREF_INTERNAL1024BYPASSED  (0x000000C0Lu)
#define `$INSTANCE_NAME`_VREF_VDDA_2BYPASSED        (0x000000E0Lu)
#define `$INSTANCE_NAME`_VREF_INTERNALVREF          (0x00000040Lu)
#define `$INSTANCE_NAME`_VREF_INTERNALVREFBYPASSED  (0x000000C0Lu)

#define `$INSTANCE_NAME`_NEG_VSSA_KELVIN            (0x00000000Lu)
#define `$INSTANCE_NAME`_NEG_VSSA                   (0x00000200Lu)
#define `$INSTANCE_NAME`_NEG_VREF                   (0x00000E00Lu)
#if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM > 1u)
    #define `$INSTANCE_NAME`_NEG_OTHER              (uint16)((uint16)`$INSTANCE_NAME`_cy_psoc4_sarmux_8__VNEG << 9u)
#else
    #define `$INSTANCE_NAME`_NEG_OTHER              (0)
#endif /* `$INSTANCE_NAME`_TOTAL_CHANNELS_NUM > 1u */

#define `$INSTANCE_NAME`_SAR_HW_CTRL_NEGVREF        (0x00002000Lu)

#define `$INSTANCE_NAME`_BOOSTPUMP_EN               (0x00100000Lu)

#define `$INSTANCE_NAME`_NORMAL_PWR                 (0x00000000Lu)
#define `$INSTANCE_NAME`_HALF_PWR                   (0x01000000Lu)
#define `$INSTANCE_NAME`_MORE_PWR                   (0x02000000Lu)
#define `$INSTANCE_NAME`_QUARTER_PWR                (0x03000000Lu)
#define `$INSTANCE_NAME`_DEEPSLEEP_ON               (0x08000000Lu)

#define `$INSTANCE_NAME`_DSI_SYNC_CONFIG            (0x10000000Lu)
#define `$INSTANCE_NAME`_DSI_MODE                   (0x20000000Lu)
#define `$INSTANCE_NAME`_SWITCH_DISABLE             (0x40000000Lu)
#define `$INSTANCE_NAME`_ENABLE                     (0x80000000Lu)

/* defines for STATUS register */
#define `$INSTANCE_NAME`_STATUS_BUSY                (0x80000000Lu)

/* defines for SAMPLE_CTRL register */
#define `$INSTANCE_NAME`_ALT_RESOLUTION_10BIT       (0x00000001Lu)
#define `$INSTANCE_NAME`_ALT_RESOLUTION_8BIT        (0x00000000Lu)

#define `$INSTANCE_NAME`_DATA_ALIGN_LEFT            (0x00000002Lu)
#define `$INSTANCE_NAME`_DATA_ALIGN_RIGHT           (0x00000000Lu)

#define `$INSTANCE_NAME`_SE_SIGNED_RESULT           (0x00000004Lu)
#define `$INSTANCE_NAME`_SE_UNSIGNED_RESULT         (0x00000000Lu)

#define `$INSTANCE_NAME`_DIFF_SIGNED_RESULT         (0x00000008Lu)
#define `$INSTANCE_NAME`_DIFF_UNSIGNED_RESULT       (0x00000000Lu)

#define `$INSTANCE_NAME`_AVG_CNT_OFFSET             (4u)
#define `$INSTANCE_NAME`_AVG_CNT_MASK               (0x00000070Lu)
#define `$INSTANCE_NAME`_AVG_SHIFT                  (0x00000080Lu)

#define `$INSTANCE_NAME`_CONTINUOUS_EN              (0x00010000Lu)
#define `$INSTANCE_NAME`_DSI_TRIGGER_EN             (0x00020000Lu)
#define `$INSTANCE_NAME`_DSI_TRIGGER_LEVEL          (0x00040000Lu)
#define `$INSTANCE_NAME`_DSI_SYNC_TRIGGER           (0x00080000Lu)
#define `$INSTANCE_NAME`_EOS_DSI_OUT_EN             (0x80000000Lu)

/* defines for SAMPLE_TIME01 / SAMPLE_TIME23 registers */
#define `$INSTANCE_NAME`_SAMPLE_TIME13_OFFSET       (16u)
#define `$INSTANCE_NAME`_SAMPLE_TIME02_MASK         (0x000003FFLu)
#define `$INSTANCE_NAME`_SAMPLE_TIME13_MASK         (0x03FF0000Lu)

/* defines for RANGE_THRES registers */
#define `$INSTANCE_NAME`_RANGE_HIGH_OFFSET          (16u)
#define `$INSTANCE_NAME`_RANGE_HIGH_MASK            (0xFFFF0000Lu)
#define `$INSTANCE_NAME`_RANGE_LOW_MASK             (0x0000FFFFLu)

/* defines for RANGE_COND register */
/* Compare mode setting constants:
*    BELOW   - Result < Low_Limit
*    INSIDE  - Low_Limit <= Result < High_Limit
*    ABOVE   - High_Limit <= Result
*    OUTSIDE - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define `$INSTANCE_NAME`_CMP_MODE_BELOW             (0x00000000Lu)
#define `$INSTANCE_NAME`_CMP_MODE_INSIDE            (0x40000000Lu)
#define `$INSTANCE_NAME`_CMP_MODE_ABOVE             (0x80000000Lu)
#define `$INSTANCE_NAME`_CMP_MODE_OUTSIDE           (0xC0000000Lu)
#define `$INSTANCE_NAME`_CMP_OFFSET                 (30u)

/* defines for _START_CTRL register */
#define `$INSTANCE_NAME`_FW_TRIGGER                 (0x00000001Lu)

/* defines for DFT_CTRL register */
#define `$INSTANCE_NAME`_DLY_INC                    (0x00000001Lu)
#define `$INSTANCE_NAME`_HIZ                        (0x00000002Lu)
#define `$INSTANCE_NAME`_DFT_INC_MASK               (0x000F0000Lu)
#define `$INSTANCE_NAME`_DFT_OUTC_MASK              (0x00700000Lu)
#define `$INSTANCE_NAME`_SEL_CSEL_DFT_MASK          (0x0F000000Lu)

/* configuration for clock speed > 9 Mhz based on
* characterization results
*/
#define `$INSTANCE_NAME`_SEL_CSEL_DFT_CHAR          (0x03000000Lu)
#define `$INSTANCE_NAME`_EN_CSEL_DFT                (0x10000000Lu)
#define `$INSTANCE_NAME`_DCEN                       (0x20000000Lu)
#define `$INSTANCE_NAME`_ADFT_OVERRIDE              (0x80000000Lu)

/* defines for CHAN_CONFIG / DIE_CHAN_CONFIG register
*  and channelsConfig parameter
*/
#define `$INSTANCE_NAME`_SARMUX_VIRT_SELECT         (0x00000070Lu)
#define `$INSTANCE_NAME`_DIFFERENTIAL_EN            (0x00000100Lu)
#define `$INSTANCE_NAME`_ALT_RESOLUTION_ON          (0x00000200Lu)
#define `$INSTANCE_NAME`_AVERAGING_EN               (0x00000400Lu)

#define `$INSTANCE_NAME`_SAMPLE_TIME_SEL_SHIFT      (12u)
#define `$INSTANCE_NAME`_SAMPLE_TIME_SEL_MASK       (0x00003000Lu)

#define `$INSTANCE_NAME`_CHANNEL_CONFIG_MASK        (0x00003700Lu)

/* for CHAN_CONFIG only */
#define `$INSTANCE_NAME`_DSI_OUT_EN                 (0x80000000Lu)

/* for INJ_CHAN_CONFIG only */
#define `$INSTANCE_NAME`_INJ_TAILGATING             (0x40000000Lu)
#define `$INSTANCE_NAME`_INJ_CHAN_EN                (0x80000000Lu)

/* defines for CHAN_WORK register */
#define `$INSTANCE_NAME`_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define `$INSTANCE_NAME`_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define `$INSTANCE_NAME`_SAR_WRK_MAX_8BIT           (0x00000100Lu)

/* defines for CHAN_RESULT register */
#define `$INSTANCE_NAME`_RESULT_MASK                (0x0000FFFFLu)
#define `$INSTANCE_NAME`_SATURATE_INTR_MIR          (0x20000000Lu)
#define `$INSTANCE_NAME`_RANGE_INTR_MIR             (0x40000000Lu)
#define `$INSTANCE_NAME`_CHAN_RESULT_VALID_MIR      (0x80000000Lu)

/* defines for INTR_MASK register */
#define `$INSTANCE_NAME`_EOS_MASK                   (0x00000001Lu)
#define `$INSTANCE_NAME`_OVERFLOW_MASK              (0x00000002Lu)
#define `$INSTANCE_NAME`_FW_COLLISION_MASK          (0x00000004Lu)
#define `$INSTANCE_NAME`_DSI_COLLISION_MASK         (0x00000008Lu)
#define `$INSTANCE_NAME`_INJ_EOC_MASK               (0x00000010Lu)
#define `$INSTANCE_NAME`_INJ_SATURATE_MASK          (0x00000020Lu)
#define `$INSTANCE_NAME`_INJ_RANGE_MASK             (0x00000040Lu)
#define `$INSTANCE_NAME`_INJ_COLLISION_MASK         (0x00000080Lu)

/* defines for INJ_RESULT register */
#define `$INSTANCE_NAME`_INJ_COLLISION_INTR_MIR     (0x10000000Lu)
#define `$INSTANCE_NAME`_INJ_SATURATE_INTR_MIR      (0x20000000Lu)
#define `$INSTANCE_NAME`_INJ_RANGE_INTR_MIR         (0x40000000Lu)
#define `$INSTANCE_NAME`_INJ_EOC_INTR_MIR           (0x80000000Lu)

/* defines for MUX_SWITCH0 register */
#define `$INSTANCE_NAME`_MUX_FW_VSSA_VMINUS         (0x00010000Lu)

/* defines for PUMP_CTRL register */
#define `$INSTANCE_NAME`_PUMP_CTRL_ENABLED          (0x80000000Lu)

/* additional defines for channelsConfig parameter */
#define `$INSTANCE_NAME`_IS_SATURATE_EN_MASK        (0x00000001Lu)
#define `$INSTANCE_NAME`_IS_RANGE_CTRL_EN_MASK      (0x00000002Lu)

/* defines for WOUNDING register */
#define `$INSTANCE_NAME`_WOUNDING_12BIT             (0x00000000Lu)
#define `$INSTANCE_NAME`_WOUNDING_10BIT             (0x00000001Lu)
#define `$INSTANCE_NAME`_WOUNDING_8BIT              (0x00000002Lu)

/* Trim value based on characterization */
#define `$INSTANCE_NAME`_TRIM_COEF                  (2u)

#if(`$INSTANCE_NAME`_MAX_RESOLUTION == `$INSTANCE_NAME`_RESOLUTION_10)
    #define `$INSTANCE_NAME`_ALT_WOUNDING           `$INSTANCE_NAME`_WOUNDING_10BIT
#else
    #define `$INSTANCE_NAME`_ALT_WOUNDING           `$INSTANCE_NAME`_WOUNDING_8BIT
#endif /* `$INSTANCE_NAME`_MAX_RESOLUTION == `$INSTANCE_NAME`_RESOLUTION_10 */

#if(`$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__VDDA_2)
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_VDDA_2
#elif(`$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__VDDA)
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_VDDA
#elif(`$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__INTERNAL1024)
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_INTERNAL1024
#elif(`$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__INTERNAL1024BYPASSED)
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_INTERNAL1024BYPASSED
#elif(`$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__INTERNALVREF)
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_INTERNALVREF
#elif(`$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__INTERNALVREFBYPASSED)
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_INTERNALVREFBYPASSED
#elif(`$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__VDDA_2BYPASSED)
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_VDDA_2BYPASSED
#else
    #define `$INSTANCE_NAME`_DEFAULT_VREF_SOURCE    `$INSTANCE_NAME`_VREF_EXTERNAL
#endif /* `$INSTANCE_NAME`_DEFAULT_VREF_SEL == `$INSTANCE_NAME`__VDDA_2 */

#if(`$INSTANCE_NAME`_DEFAULT_NEG_INPUT_SEL == `$INSTANCE_NAME`__VSS)
    /* Connect NEG input of SARADC to VSSA close to the SARADC for single channel mode */
    #if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u)
        #define `$INSTANCE_NAME`_DEFAULT_SE_NEG_INPUT    `$INSTANCE_NAME`_NEG_VSSA
    #else
        #define `$INSTANCE_NAME`_DEFAULT_SE_NEG_INPUT    `$INSTANCE_NAME`_NEG_VSSA_KELVIN
    #endif /* (`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) */
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) && (`$INSTANCE_NAME`_CHANNELS_MODE != 0u))
        #define `$INSTANCE_NAME`_DEFAULT_MUX_SWITCH0     0u
    #else    /* miltiple channels or one single channel */
        #define `$INSTANCE_NAME`_DEFAULT_MUX_SWITCH0     `$INSTANCE_NAME`_MUX_FW_VSSA_VMINUS
    #endif /* (`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) */
#elif(`$INSTANCE_NAME`_DEFAULT_NEG_INPUT_SEL == `$INSTANCE_NAME`__VREF)
    /* Do not connect VNEG to VREF when one channel in differential mode used */
    #if((`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) && (`$INSTANCE_NAME`_CHANNELS_MODE != 0u))
        #define `$INSTANCE_NAME`_DEFAULT_SE_NEG_INPUT    0u
    #else    /* miltiple channels or one single channel */
        #define `$INSTANCE_NAME`_DEFAULT_SE_NEG_INPUT    `$INSTANCE_NAME`_NEG_VREF
    #endif /* (`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) */
    #define `$INSTANCE_NAME`_DEFAULT_MUX_SWITCH0     0u
#elif (`$INSTANCE_NAME`_SINGLE_PRESENT != 0u)
    #define `$INSTANCE_NAME`_DEFAULT_SE_NEG_INPUT    `$INSTANCE_NAME`_NEG_OTHER
    #define `$INSTANCE_NAME`_DEFAULT_MUX_SWITCH0     0u
#else
    #define `$INSTANCE_NAME`_DEFAULT_SE_NEG_INPUT    0u
    #define `$INSTANCE_NAME`_DEFAULT_MUX_SWITCH0     0u
#endif /* `$INSTANCE_NAME`_DEFAULT_NEG_INPUT_SEL == `$INSTANCE_NAME`__VREF */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u)
    #define `$INSTANCE_NAME`_DEFAULT_HW_CTRL_NEGVREF 0u
#else
    #define `$INSTANCE_NAME`_DEFAULT_HW_CTRL_NEGVREF `$INSTANCE_NAME`_SAR_HW_CTRL_NEGVREF
#endif /* (`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM == 1u) */


#if(`$INSTANCE_NAME`_DEFAULT_ALT_RESOLUTION_SEL == `$INSTANCE_NAME`__RES8)
    #define `$INSTANCE_NAME`_DEFAULT_ALT_RESOLUTION     (`$INSTANCE_NAME`_ALT_RESOLUTION_8BIT)
    #define `$INSTANCE_NAME`_DEFAULT_MAX_WRK_ALT        (`$INSTANCE_NAME`_SAR_WRK_MAX_8BIT)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ALT_RESOLUTION     (`$INSTANCE_NAME`_ALT_RESOLUTION_10BIT)
    #define `$INSTANCE_NAME`_DEFAULT_MAX_WRK_ALT        (`$INSTANCE_NAME`_SAR_WRK_MAX_10BIT)
#endif /* End `$INSTANCE_NAME`_DEFAULT_ALT_RESOLUTION_SEL == `$INSTANCE_NAME`__RES8 */

#if(`$INSTANCE_NAME`_DEFAULT_JUSTIFICATION_SEL == `$INSTANCE_NAME`__RIGHT)
    #define `$INSTANCE_NAME`_DEFAULT_JUSTIFICATION  `$INSTANCE_NAME`_DATA_ALIGN_RIGHT
#else
    #define `$INSTANCE_NAME`_DEFAULT_JUSTIFICATION  `$INSTANCE_NAME`_DATA_ALIGN_LEFT
#endif /* `$INSTANCE_NAME`_DEFAULT_JUSTIFICATION_SEL == `$INSTANCE_NAME`__RIGHT */

#if(`$INSTANCE_NAME`_DEFAULT_DIFF_RESULT_FORMAT_SEL == `$INSTANCE_NAME`__FSIGNED)
    #define `$INSTANCE_NAME`_DEFAULT_DIFF_RESULT_FORMAT `$INSTANCE_NAME`_DIFF_SIGNED_RESULT
#else
    #define `$INSTANCE_NAME`_DEFAULT_DIFF_RESULT_FORMAT `$INSTANCE_NAME`_DIFF_UNSIGNED_RESULT
#endif /* `$INSTANCE_NAME`_DEFAULT_DIFF_RESULT_FORMAT_SEL == `$INSTANCE_NAME`__FSIGNED */

#if(`$INSTANCE_NAME`_DEFAULT_SE_RESULT_FORMAT_SEL == `$INSTANCE_NAME`__FSIGNED)
    #define `$INSTANCE_NAME`_DEFAULT_SE_RESULT_FORMAT `$INSTANCE_NAME`_SE_SIGNED_RESULT
#else
    #define `$INSTANCE_NAME`_DEFAULT_SE_RESULT_FORMAT `$INSTANCE_NAME`_SE_UNSIGNED_RESULT
#endif /* `$INSTANCE_NAME`_DEFAULT_SE_RESULT_FORMAT_SEL == `$INSTANCE_NAME`__FSIGNED */

#if(`$INSTANCE_NAME`_DEFAULT_SAMPLE_MODE_SEL == `$INSTANCE_NAME`__FREERUNNING)
    #define `$INSTANCE_NAME`_DSI_TRIGGER        0u
#else /* Firmware trigger */
    #define `$INSTANCE_NAME`_DSI_TRIGGER        (`$INSTANCE_NAME`_DSI_TRIGGER_EN | `$INSTANCE_NAME`_DSI_SYNC_TRIGGER)
#endif /* End `$INSTANCE_NAME`_DEFAULT_SAMPLE_MODE == `$INSTANCE_NAME`__FREERUNNING */

#if(`$INSTANCE_NAME`_INJ_CHANNEL_ENABLED)
    #define `$INSTANCE_NAME`_SAR_INTR_MASK      (`$INSTANCE_NAME`_EOS_MASK | `$INSTANCE_NAME`_INJ_EOC_MASK)
#else
    #define `$INSTANCE_NAME`_SAR_INTR_MASK      (`$INSTANCE_NAME`_EOS_MASK)
#endif /* `$INSTANCE_NAME`_INJ_CHANNEL_ENABLED*/

#if(`$INSTANCE_NAME`_DEFAULT_AVG_MODE == `$INSTANCE_NAME`__FIXEDRESOLUTION)
    #define `$INSTANCE_NAME`_AVG_SHIFT_MODE     `$INSTANCE_NAME`_AVG_SHIFT
#else
    #define `$INSTANCE_NAME`_AVG_SHIFT_MODE     0u
#endif /* End `$INSTANCE_NAME`_DEFAULT_AVG_MODE */

#define `$INSTANCE_NAME`_COMPARE_MODE           (uint32)((uint32)(`$INSTANCE_NAME`_DEFAULT_COMPARE_MODE) \
                                                << `$INSTANCE_NAME`_CMP_OFFSET)

#if(`$INSTANCE_NAME`_TOTAL_CHANNELS_NUM > 1u)
    #define `$INSTANCE_NAME`_DEFAULT_SWITCH_CONF    0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define `$INSTANCE_NAME`_DEFAULT_SWITCH_CONF    `$INSTANCE_NAME`_SWITCH_DISABLE
#endif /* End `$INSTANCE_NAME`_TOTAL_CHANNELS_NUM > 1 */

#define `$INSTANCE_NAME`_DEFAULT_POWER \
       ((`$INSTANCE_NAME`_NOMINAL_CLOCK_FREQ > (`$INSTANCE_NAME`_MAX_FREQUENCY / 4)) ? `$INSTANCE_NAME`_NORMAL_PWR : \
       ((`$INSTANCE_NAME`_NOMINAL_CLOCK_FREQ > (`$INSTANCE_NAME`_MAX_FREQUENCY / 8)) ? `$INSTANCE_NAME`_HALF_PWR : \
                                                                                       `$INSTANCE_NAME`_QUARTER_PWR))

#define `$INSTANCE_NAME`_DEFAULT_CTRL_REG_CFG       (`$INSTANCE_NAME`_DEFAULT_VREF_SOURCE \
                                                   | `$INSTANCE_NAME`_DEFAULT_SE_NEG_INPUT \
                                                   | `$INSTANCE_NAME`_DEFAULT_HW_CTRL_NEGVREF \
                                                   | `$INSTANCE_NAME`_DEFAULT_POWER \
                                                   | `$INSTANCE_NAME`_DSI_SYNC_CONFIG \
                                                   | `$INSTANCE_NAME`_DEFAULT_SWITCH_CONF)

#define `$INSTANCE_NAME`_DEFAULT_SAMPLE_CTRL_REG_CFG (`$INSTANCE_NAME`_DEFAULT_DIFF_RESULT_FORMAT \
                                                    | `$INSTANCE_NAME`_DEFAULT_SE_RESULT_FORMAT \
                                                    | `$INSTANCE_NAME`_DEFAULT_JUSTIFICATION \
                                                    | `$INSTANCE_NAME`_DEFAULT_ALT_RESOLUTION \
                                           | (uint8)(`$INSTANCE_NAME`_DEFAULT_AVG_SAMPLES_NUM \
                                                   << `$INSTANCE_NAME`_AVG_CNT_OFFSET) \
                                                    | `$INSTANCE_NAME`_AVG_SHIFT_MODE \
                                                    | `$INSTANCE_NAME`_DSI_TRIGGER \
                                                    | `$INSTANCE_NAME`_EOS_DSI_OUT_EN)

#define `$INSTANCE_NAME`_DEFAULT_RANGE_THRES_REG_CFG (`$INSTANCE_NAME`_DEFAULT_LOW_LIMIT \
            | (uint32)((uint32)`$INSTANCE_NAME`_DEFAULT_HIGH_LIMIT << `$INSTANCE_NAME`_RANGE_HIGH_OFFSET))

#define `$INSTANCE_NAME`_DEFAULT_SAMPLE_TIME01_REG_CFG (`$INSTANCE_NAME`_DEFAULT_ACLKS_NUM \
            | (uint32)((uint32)`$INSTANCE_NAME`_DEFAULT_BCLKS_NUM << `$INSTANCE_NAME`_SAMPLE_TIME13_OFFSET))

#define `$INSTANCE_NAME`_DEFAULT_SAMPLE_TIME23_REG_CFG (`$INSTANCE_NAME`_DEFAULT_CCLKS_NUM \
            | (uint32)((uint32)`$INSTANCE_NAME`_DEFAULT_DCLKS_NUM << `$INSTANCE_NAME`_SAMPLE_TIME13_OFFSET))


#endif /* End CY_ADC_SAR_SEQ_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
