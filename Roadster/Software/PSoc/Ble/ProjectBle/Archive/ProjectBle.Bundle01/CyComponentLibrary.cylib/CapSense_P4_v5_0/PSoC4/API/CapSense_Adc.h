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

#include "cytypes.h"
#include "`$INSTANCE_NAME`_Configuration.h"
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
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

/** \}
* \endcond */

/**
* \cond SECTION_ADC_PUBLIC
* \addtogroup group_adc_public
* \{
*/
cystatus `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(uint8 chId);
uint8 `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy(void);
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`ReadResult_mVolts(uint8 chId);
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts(uint8 chId);
cystatus `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate(void);

void `$INSTANCE_NAME`_`$AdcCapSensePrefix`Stop(void);
void `$INSTANCE_NAME`_`$AdcCapSensePrefix`Resume(void);

/** \}
* \endcond */

CY_ISR_PROTO(`$INSTANCE_NAME`_`$AdcModulePrefix`IntrHandler);

/**
* \cond SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

void `$INSTANCE_NAME`_`$AdcModulePrefix`Initialize(void);
void `$INSTANCE_NAME`_SetAdcChannel(uint8 chId, uint32 state);
void `$INSTANCE_NAME`_ConfigAdcResources(void);
void `$INSTANCE_NAME`_StartAdcFSM(uint32 measureMode);
cystatus `$INSTANCE_NAME`_AdcCaptureResources(void);
cystatus `$INSTANCE_NAME`_AdcReleaseResources(void);
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

#define `$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_INPUT                (0x1uL)

/* Default filter delay */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FILTER_DELAY_DEFAULT         (2uL)

/* Adc Config */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DEFAULT               (`$INSTANCE_NAME`_CONFIG_ENABLE_MASK | \
                                                                            `$INSTANCE_NAME`_CONFIG_SAMPLE_SYNC_MASK | \
                                                                            `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK | \
                                                                            `$INSTANCE_NAME`_CONFIG_DSI_COUNT_SEL_MASK | \
                                                                            `$INSTANCE_NAME`_`$AdcModulePrefix`FILTER_DELAY_DEFAULT)

/* Measurement modes */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_OFF                 (0x0uL << CYFLD_CSD_ADC_MODE__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF                (0x1uL << CYFLD_CSD_ADC_MODE__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREFBY2             (0x2uL << CYFLD_CSD_ADC_MODE__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VIN                 (0x3uL << CYFLD_CSD_ADC_MODE__OFFSET)

/* Clock defines */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT            (0x4uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV              (`$INSTANCE_NAME`_ADC_MODCLK_DIV_DEFAULT * \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT)

/* The MAX possible value of the AZ time in CSD_SENSE cycles. The value is limited by the width of the SEQ_TIME register */
#define `$INSTANCE_NAME`_ADC_SEQ_TIME_MAX                               (0x100u)

#define `$INSTANCE_NAME`_ADC_SEQ_TIME_CYCLES                            (((CYDEV_BCLK__HFCLK__HZ * `$INSTANCE_NAME`_ADC_AZ_TIME) / \
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
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_BASE             ((`$INSTANCE_NAME`_ADC_ACQUISITION_TIME_US * \
                                                                        (CYDEV_BCLK__HFCLK__MHZ)) / \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV)

/* SEQ_START field definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_ABORT             (0x1uL << CYFLD_CSD_ABORT__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSI_START_EN      (0x1uL << CYFLD_CSD_DSI_START_EN__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP           (0x1uL << CYFLD_CSD_AZ0_SKIP__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP           (0x1uL << CYFLD_CSD_AZ1_SKIP__OFFSET)


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
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CLK16_MASK                   (0x0000FFFFuL)
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
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CTANK_PINSHIFT            (9uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PINSHIFT             (6uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PORT_MASK            (0x400uL)

#define `$INSTANCE_NAME`_`$AdcModulePrefix`LVTHRESH                     (2700uL)

/* The reference voltage is measured at nominal 2400 mV. Measured amount is stored in CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1 */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREFCALIB_BASE               (2400uL)

/* RefGen settings */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_GAIN_SHIFT            (CYFLD_CSD_GAIN__OFFSET)

/* At low voltage, REFGEN is enabled and bypassed. */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_LV                 (0x01000100uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_LV                     (0x00000002uL)
/* At normal voltage, REFGEN uses customizer-defined gain */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_NORM                  (0x00000041uL | (`$INSTANCE_NAME`_ADC_GAIN << \
                                                                            `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_GAIN_SHIFT))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_NORM               (0x00000000uL)

/* HSCOMP definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_AZ_DEFAULT             (`$INSTANCE_NAME`_HSCMP_EN_MASK | \
                                                                            (`$INSTANCE_NAME`_ADC_AZ_EN << CYFLD_CSD_AZ_EN__OFFSET))

/* ADC_RES definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`RES_MAX                      ((1uL << `$INSTANCE_NAME`_ADC_RESOLUTION) - 1uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_OVERFLOW_MASK        (0x40000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_ABORT_MASK           (0x80000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_HSCMPPOL_MASK        (0x00010000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_VALUE_MASK           (0x0000FFFFuL)

#endif  /* `$INSTANCE_NAME`_ADC_EN */

#endif  /* CY_SENSE_`$INSTANCE_NAME`_ADC_H */


/* [] END OF FILE */
