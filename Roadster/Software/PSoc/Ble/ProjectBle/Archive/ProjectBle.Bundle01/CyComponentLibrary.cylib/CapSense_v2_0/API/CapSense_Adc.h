/***************************************************************************//**
* \file `$INSTANCE_NAME`_Adc.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the sources of APIs specific to the ADC implementation.
*
* \see `$INSTANCE_NAME` v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
*
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_SENSE_`$INSTANCE_NAME`_ADC_H)
#define CY_SENSE_`$INSTANCE_NAME`_ADC_H

#include "syslib/cy_syslib.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    #include "syspm/cy_syspm.h"
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
#include "`$INSTANCE_NAME`_Structure.h"

#if (`$INSTANCE_NAME`_ADC_EN)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
* \cond SECTION_STANDALONE_ADC
* \addtogroup group_adc_public
* \{
*/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    void `$INSTANCE_NAME`_Start(void);
    void `$INSTANCE_NAME`_Sleep(void);
    void `$INSTANCE_NAME`_Wakeup(void);

    cy_en_syspm_status_t `$INSTANCE_NAME`_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams);
    cy_en_syspm_status_t `$INSTANCE_NAME`_EnterLowPowerCallback(cy_stc_syspm_callback_params_t *callbackParams);
    cy_en_syspm_status_t `$INSTANCE_NAME`_ExitLowPowerCallback(cy_stc_syspm_callback_params_t *callbackParams);

#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
/** \}
* \endcond */

/**
* \cond SECTION_ADC_PUBLIC
* \addtogroup group_adc_public
* \{
*/

cy_status `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(uint8 chId);
uint8 `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy(void);
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`ReadResult_mVolts(uint8 chId);
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts(uint8 chId);
cy_status `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate(void);

void `$INSTANCE_NAME`_`$AdcCapSensePrefix`Stop(void);
void `$INSTANCE_NAME`_`$AdcCapSensePrefix`Resume(void);

/** \}
* \endcond */

void `$INSTANCE_NAME`_`$AdcModulePrefix`IntrHandler(void);

/**
* \cond SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

void `$INSTANCE_NAME`_`$AdcModulePrefix`Initialize(void);
void `$INSTANCE_NAME`_SetAdcChannel(uint8 chId, uint32 state);
void `$INSTANCE_NAME`_ConfigAdcResources(void);
void `$INSTANCE_NAME`_StartAdcFSM(uint32 measureMode);
cy_status `$INSTANCE_NAME`_AdcCaptureResources(void);
cy_status `$INSTANCE_NAME`_AdcReleaseResources(void);
void `$INSTANCE_NAME`_ClearAdcChannels(void);
void `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(uint8 chId, uint32 state);

/** \}
* \endcond */

/**************************************
* Global software/external variables
**************************************/

extern uint16 `$INSTANCE_NAME`_adcVrefMv;

/**************************************
*           API Constants
**************************************/

/* Error value if given bad channel ID. */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_CHAN_ID            (0x0000FFFFuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_RESULT             (0x0000FFFFuL)

/* Statuses defined for use with IsBusy */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_LASTCHAN_MASK         (0x0000000FuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK              (0x000000F0uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE                  (0x00u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1              (0x10u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH2              (0x20u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH3              (0x30u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CONVERTING            (0x40u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_OVERFLOW              (0x80u)

/* Potential channel states */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT                 (1uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT              (0uL)

/* Active channel when ADC is not configured */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`NO_CHANNEL                   (0xFFu)

/* Input/Output constants */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_GPIO            (HSIOM_SEL_GPIO)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_AMUXBUSB        (HSIOM_SEL_AMUXB)

#define `$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_DISCONNECT           (CY_GPIO_DM_ANALOG)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_INPUT                (CY_GPIO_DM_HIGHZ)

/* Default filter delay */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FILTER_DELAY_DEFAULT         (2uL)

/* Adc Config */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DEFAULT               (CSD_CONFIG_ENABLE_Msk | \
                                                                            CSD_CONFIG_SAMPLE_SYNC_Msk | \
                                                                            CSD_CONFIG_SENSE_EN_Msk | \
                                                                            CSD_CONFIG_DSI_COUNT_SEL_Msk | \
                                                                            (`$INSTANCE_NAME`_`$AdcModulePrefix`FILTER_DELAY_DEFAULT << CSD_CONFIG_FILTER_DELAY_Pos))

/* Measurement modes */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_OFF                 (0x0uL << CSD_ADC_CTL_ADC_MODE_Pos)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF                (0x1uL << CSD_ADC_CTL_ADC_MODE_Pos)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREFBY2             (0x2uL << CSD_ADC_CTL_ADC_MODE_Pos)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VIN                 (0x3uL << CSD_ADC_CTL_ADC_MODE_Pos)

/* Clock defines */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT            (0x4uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV              (`$INSTANCE_NAME`_ADC_MODCLK_DIV_DEFAULT * \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT)

/* The MAX possible value of the AZ time in CSD_SENSE cycles. The value is limited by the width of the SEQ_TIME register */
#define `$INSTANCE_NAME`_ADC_SEQ_TIME_MAX                               (0x100u)

#define `$INSTANCE_NAME`_ADC_SEQ_TIME_CYCLES                            (((CYDEV_CLK_PERICLK__HZ * `$INSTANCE_NAME`_ADC_AZ_TIME) / \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV) / 1000000uL)

#if (`$INSTANCE_NAME`_ADC_SEQ_TIME_MAX < `$INSTANCE_NAME`_ADC_SEQ_TIME_CYCLES)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE            (`$INSTANCE_NAME`_ADC_SEQ_TIME_MAX)
#else
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE            (`$INSTANCE_NAME`_ADC_SEQ_TIME_CYCLES)
#endif

#if (0 == `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_DEFAUL          (1u)
#else
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_DEFAUL          (`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE)
#endif

/* Acquisition time definitions: ADC_CTL */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_TIME_US          (10uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_BASE             ((`$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_TIME_US * \
                                                                        (CYDEV_CLK_PERICLK__MHZ)) / \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV)

/* SEQ_START field definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_ABORT             (0x1uL << CSD_SEQ_START_ABORT_Pos)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSI_START_EN      (0x1uL << CSD_SEQ_START_DSI_START_EN_Pos)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP           (0x1uL << CSD_SEQ_START_AZ0_SKIP_Pos)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP           (0x1uL << CSD_SEQ_START_AZ1_SKIP_Pos)


#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_NOAZSKIP          (0uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZSKIP_DEFAULT    (`$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP \
                                                                            | ((0u != `$INSTANCE_NAME`_ADC_AZ_EN) \
                                                                            ? 0u \
                                                                            : `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSIIGNORE         (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_NOABORT           (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQMODE           (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_START             (0x00000001uL)

/* IDACB definitions
*  The idac configuration for ADC use is mostly static, with only the VAL field varying.
*   Dynamic Polarity = 1 << 7
*   Polarity (normal) = 0 << 8
*   Balance, Leg1, Leg2 modes = don't care.
*   DSI Control Enable (no mix) = 0 << 21
*   Range (low) = 0 << 22
*   Leg1, Leg2 enable = 0
*   Leg3 enable = 1 << 26
*/
#define `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG                 (0x04000080uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CLK16_MASK                   (0xFFFFuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CLK16VAL_SHIFT               (8uL)

/* Switch definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSP_DEFAULT               (0x10000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSN_DEFAULT               (0x00100000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSP_GETINPOL              (0x00010000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSN_GETINPOL              (0x01000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_DEFAULT            (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_VDDA2CSDBUSB       (0x00000100uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_DEFAULT               (0x00110000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPP_DEFAULT              (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPN_DEFAULT              (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_DEFAULT            (0x10000000uL)

#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWMOD_DEFAULT             (0x01100000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWTANK_DEFAULT            (0x01100000uL)

/* The reference voltage macros */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_0_8          (800uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_1_2          (1164uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_1_6          (1600uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_2_1          (2133uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_2_6          (2600uL)

#if (`$INSTANCE_NAME`_ADC_VREF_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_1_2)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_USED          (`$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_0_8)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF1)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_0P8_Pos)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_0P8_Msk)
#elif (`$INSTANCE_NAME`_ADC_VREF_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_1_6)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_USED          (`$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_1_2)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF0)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P2_Pos)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P2_Msk)
#elif (`$INSTANCE_NAME`_ADC_VREF_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_2_1)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_USED          (`$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_1_6)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF0)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P6_Pos)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF0_VREF_HI_LEVELS_1P6_Msk)
#elif (`$INSTANCE_NAME`_ADC_VREF_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_2_6)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_USED          (`$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_2_1)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF1)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_2P1_Pos)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF1_VREF_HI_LEVELS_2P1_Msk)
#else
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_USED          (`$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_BASE_2_6)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_REG            (SFLASH->CSDV2_CSD0_ADC_VREF2)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_POS            (SFLASH_CSDV2_CSD0_ADC_VREF2_VREF_HI_LEVELS_2P6_Pos)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MSK            (SFLASH_CSDV2_CSD0_ADC_VREF2_VREF_HI_LEVELS_2P6_Msk)
#endif

#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MAX_DEVIATION      (20uL)

/* RefGen settings */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_GAIN_SHIFT            (CSD_REFGEN_GAIN_Pos)

/* At low voltage, REFGEN is enabled and bypassed. */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_LV                    (0x00000011uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_LV                 (0x01000100uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_LV                     (0x00000002uL)
/* At normal voltage, REFGEN uses customizer-defined gain */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_NORM                  (0x00000041UL | (`$INSTANCE_NAME`_ADC_GAIN << \
                                                                            `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_GAIN_SHIFT))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_NORM               (0x00000000uL)

/* HSCOMP definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_AZ_DEFAULT             (CSD_HSCMP_HSCMP_EN_Msk | (`$INSTANCE_NAME`_ADC_AZ_EN << CSD_HSCMP_AZ_EN_Pos))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_HSCMP_OUT_MASK        (CSD_HSCMP_HSCMP_INVERT_Msk)

/* ADC_RES definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`RES_MAX                      ((1uL << `$INSTANCE_NAME`_ADC_RESOLUTION) - 1uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_OVERFLOW_MASK        (CSD_ADC_RES_ADC_OVERFLOW_Msk)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_ABORT_MASK           (CSD_ADC_RES_ADC_ABORT_Msk)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_HSCMPPOL_MASK        (CSD_ADC_RES_HSCMP_POL_Msk)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_VALUE_MASK           (CSD_ADC_RES_VIN_CNT_Msk)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`UNDERFLOW_LIMIT              (8000u)

#endif  /* `$INSTANCE_NAME`_ADC_EN */

#endif  /* CY_SENSE_`$INSTANCE_NAME`_ADC_H */


/* [] END OF FILE */
