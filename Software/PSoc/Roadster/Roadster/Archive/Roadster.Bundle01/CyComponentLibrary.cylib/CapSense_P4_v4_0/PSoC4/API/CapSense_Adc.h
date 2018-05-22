/***************************************************************************//**
* \file `$INSTANCE_NAME`_Adc.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the sources of APIs specific to the ADC implementation.
*
* \see CapSense P4 v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
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

#if !defined(CY_CAPSENSE_`$INSTANCE_NAME`_ADC_H)
#define CY_CAPSENSE_`$INSTANCE_NAME`_ADC_H


#include "cytypes.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"

#if (`$INSTANCE_NAME`_ADC_EN)
    
/*******************************************************************************
* Function Prototypes 
*******************************************************************************/ 

/**
* \if SECTION_STANDALONE_ADC
* \addtogroup group_adc_public
* \{
*/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    void `$INSTANCE_NAME`_Start(void);
    void `$INSTANCE_NAME`_Sleep(void);
    void `$INSTANCE_NAME`_Wakeup(void);
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
/** \}
* \endif */
/**
* \if SECTION_ADC_PUBLIC
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
* \endif */


CY_ISR_PROTO(`$INSTANCE_NAME`_`$AdcModulePrefix`IntrHandler);

/**
* \if SECTION_ADC_INTERNAL
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

#define `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(o, s)  (((1uL << (s)) - 1uL) << (o))
/** \}
* \endif */

/**************************************
*           API Constants
**************************************/
#ifdef CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1
    #define `$INSTANCE_NAME`_CALIBRATE_VREF                             (`$INSTANCE_NAME`_ENABLE)
#else
    #define `$INSTANCE_NAME`_CALIBRATE_VREF                             (`$INSTANCE_NAME`_DISABLE)
#endif

/* Error value if given bad channel ID. */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_CHAN_ID            (0x0000FFFFuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_RESULT             (0x0000FFFFuL)
/* Obsolete */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BADCHANID              (0x0000FFFFuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BADRESULT              (0x0000FFFFuL)

/* Statuses defined for use with IsBusy */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_LASTCHAN_MASK         (0x0000000FuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK              (0x000000F0uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE                  (0x0u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1              (0x10u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH2              (0x20u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH3              (0x30u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CONVERTING            (0x40u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_OVERFLOW              (0x80u)

/* Potential channel states */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT                 (1uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT              (0uL)

/* Input/Output constants */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_MASK            (0xFuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_GPIO            (0x0uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_AMUXBUSB        (0x7uL)

#define `$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_MASK                 (0x7uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_DISCONNECT           (0x0uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_INPUT                (0x1uL)

/* Adc Config */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_FILTER_DELAY_MASK     `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_FILTER_DELAY__OFFSET, \
                                                                        CYFLD_CSD_FILTER_DELAY__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_SHIELD_DELAY_MASK     `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_SHIELD_DELAY__OFFSET, \
                                                                        CYFLD_CSD_SHIELD_DELAY__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_SENSE_EN_MASK         `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_SENSE_EN__OFFSET, \
                                                                        CYFLD_CSD_SENSE_EN__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_CHARGE_MODE_MASK      `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_CHARGE_MODE__OFFSET, \
                                                                        CYFLD_CSD_CHARGE_MODE__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_MUTUAL_CAP_MASK       `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_MUTUAL_CAP__OFFSET, \
                                                                        CYFLD_CSD_MUTUAL_CAP__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_CSX_DUAL_CNT_MASK     `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_CSX_DUAL_CNT__OFFSET, \
                                                                        CYFLD_CSD_CSX_DUAL_CNT__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DSI_COUNT_SEL_MASK    `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_DSI_COUNT_SEL__OFFSET, \
                                                                        CYFLD_CSD_DSI_COUNT_SEL__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DSI_SAMPLE_EN_MASK    `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_DSI_SAMPLE_EN__OFFSET, \
                                                                        CYFLD_CSD_DSI_SAMPLE_EN__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_SAMPLE_SYNC_MASK      `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_SAMPLE_SYNC__OFFSET, \
                                                                        CYFLD_CSD_SAMPLE_SYNC__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DSI_SENSE_EN_MASK     `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_DSI_SENSE_EN__OFFSET, \
                                                                        CYFLD_CSD_DSI_SENSE_EN__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_LP_MODE_MASK          `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_LP_MODE__OFFSET, \
                                                                        CYFLD_CSD_LP_MODE__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_ENABLE_MASK           `$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_ENABLE__OFFSET, \
                                                                        CYFLD_CSD_ENABLE__SIZE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DEFAULT               (`$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_ENABLE_MASK | \
                                                                        (2uL << CYFLD_CSD_FILTER_DELAY__OFFSET) | \
                                                                        `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_SAMPLE_SYNC_MASK | \
                                                                        `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_SENSE_EN_MASK | \
                                                                        `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DSI_COUNT_SEL_MASK)

/* Measurement modes */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_SHIFT               (CYFLD_CSD_ADC_MODE__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_MASK                (0x3uL << `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_OFF                 (0x0uL << `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF                (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREFBY2             (0x2uL << `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VIN                 (0x3uL << `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_SHIFT)

/* Clock defines */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT            (0x4uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV              (`$INSTANCE_NAME`_ADC_MODCLK_DIV_DEFAULT * \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT)
/* SEQ_TIME field definitions: AZ Time */
#define `$INSTANCE_NAME`_ADC_MAX_AZ_TIME                                (21u)
#if (`$INSTANCE_NAME`_ADC_MAX_AZ_TIME < `$INSTANCE_NAME`_ADC_AZ_TIME)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE            (((CYDEV_BCLK__HFCLK__HZ * `$INSTANCE_NAME`_ADC_MAX_AZ_TIME) / \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV) / 1000000uL)
#else
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE            (((CYDEV_BCLK__HFCLK__HZ * `$INSTANCE_NAME`_ADC_AZ_TIME) / \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV) / 1000000uL)
#endif

#if (0 == `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_DEFAUL          (1u)
#else
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_DEFAUL          (`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE)
#endif

/* Acquisition time definitions: ADC_CTL */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_TIME_US          (10uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_BASE             ((`$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_TIME_US * \
                                                                        (CYDEV_BCLK__HFCLK__MHZ)) / \
                                                                         `$INSTANCE_NAME`_`$AdcModulePrefix`TOTAL_CLOCK_DIV)

/* SEQ_START field definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_START_SHIFT       (CYFLD_CSD_START__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_START_MASK        (`$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_START__OFFSET, CYFLD_CSD_START__SIZE))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_STARTSEQ          (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_START_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQ_MODE_SHIFT    (CYFLD_CSD_SEQ_MODE__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQ_MODE_MASK     (`$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_SEQ_MODE__OFFSET, CYFLD_CSD_SEQ_MODE__SIZE))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQ_MODE_ADC      (0x0uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQ_MODE_COARSE   (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQ_MODE_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_ABORT_SHIFT       (CYFLD_CSD_ABORT__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_ABORT_MASK        (`$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_ABORT__OFFSET, CYFLD_CSD_ABORT__SIZE))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_ABORT             (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_ABORT_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSI_START_EN_SHIFT (CYFLD_CSD_DSI_START_EN__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSI_START_EN_MASK (`$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_DSI_START_EN__OFFSET, CYFLD_CSD_DSI_START_EN__SIZE))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSI_START_EN      (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSI_START_EN_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP_SHIFT     (CYFLD_CSD_AZ0_SKIP__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP_MASK      (`$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_AZ0_SKIP__OFFSET, CYFLD_CSD_AZ0_SKIP__SIZE))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP           (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP_SHIFT     (CYFLD_CSD_AZ1_SKIP__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP_MASK      (`$INSTANCE_NAME`_`$AdcModulePrefix`OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_AZ1_SKIP__OFFSET, CYFLD_CSD_AZ1_SKIP__SIZE))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP           (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP_SHIFT)

#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_NOAZSKIP          (0uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZSKIP_DEFAULT    (`$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ0SKIP \
                                                                        | ((0u != `$INSTANCE_NAME`_ADC_AZ_EN) \
                                                                        ? 0u \
                                                                        : `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZ1SKIP))
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSIIGNORE         (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_NOABORT           (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQMODE           (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_START             (0x00000001uL)

/* Interrupt definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SHIFT              (CYFLD_CSD_ADC_RES__OFFSET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_MASK               (0x1uL << `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SHIFT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_CLEAR              (0x00000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET                (`$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_MASK)

/* IDACB definitions */
/* The idac configuration for ADC use is mostly static, with only the VAL field
   varying. 
   Dynamic Polarity = 1 << 7
   Polarity (normal) = 0 << 8
   Balance, Leg1, Leg2 modes = don't care.
   DSI Control Enable (no mix) = 0 << 21
   Range (low) = 0 << 22
   Leg1, Leg2 enable = 0
   Leg3 enable = 1 << 26
   */

#define `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG                 (0x04000080uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_VAL_MASK               (0x7FuL)
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

#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CTANK_PINSHIFT            (9uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PINSHIFT             (6uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PORT_MASK            (0x400uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_CMOD                  (1uL << 4)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_CTANK                 (1uL << 0)

#define `$INSTANCE_NAME`_`$AdcModulePrefix`LVTHRESH                     (2700uL)

/* Vrefhi is achieved via a gain applied to a source. Source value is usually 1.2V */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREFSRC_MV                   (1200uL)
/* The reference voltage is measured at nominal 2400 mV. Measured amount is stored in CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1 */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREFCALIB_BASE               (2400uL)

/* RefGen settings */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_GAIN_SHIFT            (CYFLD_CSD_GAIN__OFFSET)

/* At low voltage, REFGEN is enabled and bypassed. */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_LV                    (0x00000011uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_LV                 (0x01000100uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_LV                     (0x00000002uL)
/* At normal voltage, REFGEN uses customizer-defined gain */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_NORM                  (0x00000041uL | \
                                                                        (`$INSTANCE_NAME`_ADC_GAIN << \
                                                                        `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_GAIN_SHIFT))

#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_NORM               (0x00000000uL)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_DIV_SHIFT     (0u)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_PA_DIV_SHIFT  (8u)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_DISABLE_SHIFT (30u)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_ENABLE_SHIFT  (31u)
    /* No ADC prefix */
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_DISABLE_MASK  ((uint32)((uint32)1u << `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_DISABLE_SHIFT))
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_ENABLE_MASK   ((uint32)((uint32)1u << `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_ENABLE_SHIFT))

    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_DIV_REG           (*(reg32 *)`$INSTANCE_NAME`_ModClk__DIV_REGISTER)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_DIV_PTR           ( (reg32 *)`$INSTANCE_NAME`_ModClk__DIV_REGISTER)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_REG           (*(reg32 *)CYREG_PERI_DIV_CMD)
    #define `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_PTR           ( (reg32 *)CYREG_PERI_DIV_CMD)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

/* HSCOMP definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_AZ_SHIFT               (31uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_AZ_DEFAULT             (0x00000001uL | \
                                                                        (`$INSTANCE_NAME`_ADC_AZ_EN << \
                                                                        `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_AZ_SHIFT))

#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_HSCMP_OUT_MASK        (0x1uL << 2uL)

/* ADC_RES definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`RES_MAX                      ((1uL << `$INSTANCE_NAME`_ADC_RESOLUTION) - 1uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_OVERFLOW_MASK        (0x40000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_ABORT_MASK           (0x80000000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_HSCMPPOL_MASK        (0x00010000uL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_VALUE_MASK           (0x0000FFFFuL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`UNDERFLOW_LIMIT              (8000u)

/* Actual VREFHI is used in calculations. */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`VREFHI_MV                    (`$INSTANCE_NAME`_ADC_VREF_MV)

/* Register definitions */
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_REG                   (*(reg32 *) CYREG_CSD_CONFIG)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SPARE_REG                    (*(reg32 *) CYREG_CSD_SPARE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_REG                   (*(reg32 *) CYREG_CSD_STATUS)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STAT_SEQ_REG                 (*(reg32 *) CYREG_CSD_STAT_SEQ)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STAT_CNTS_REG                (*(reg32 *) CYREG_CSD_STAT_CNTS)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`RESULT_VAL1_REG              (*(reg32 *) CYREG_CSD_RESULT_VAL1)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`RESULT_VAL2_REG              (*(reg32 *) CYREG_CSD_RESULT_VAL2)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_REG                  (*(reg32 *) CYREG_CSD_ADC_RES)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_REG                     (*(reg32 *) CYREG_CSD_INTR)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_SET_REG                 (*(reg32 *) CYREG_CSD_INTR_SET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_REG                (*(reg32 *) CYREG_CSD_INTR_MASK)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASKED_REG              (*(reg32 *) CYREG_CSD_INTR_MASKED)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_REG                    (*(reg32 *) CYREG_CSD_HSCMP)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_REG                    (*(reg32 *) CYREG_CSD_AMBUF)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_REG                   (*(reg32 *) CYREG_CSD_REFGEN)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CSDCMP_REG                   (*(reg32 *) CYREG_CSD_CSDCMP)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`IDACA_REG                    (*(reg32 *) CYREG_CSD_IDACA)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_REG                    (*(reg32 *) CYREG_CSD_IDACB)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_RES_REG                   (*(reg32 *) CYREG_CSD_SW_RES)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_PERIOD_REG             (*(reg32 *) CYREG_CSD_SENSE_PERIOD)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DUTY_REG               (*(reg32 *) CYREG_CSD_SENSE_DUTY)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_P_SEL_REG              (*(reg32 *) CYREG_CSD_SW_HS_P_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_N_SEL_REG              (*(reg32 *) CYREG_CSD_SW_HS_N_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_REG            (*(reg32 *) CYREG_CSD_SW_SHIELD_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUXBUF_SEL_REG           (*(reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_REG               (*(reg32 *) CYREG_CSD_SW_BYP_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_P_SEL_REG             (*(reg32 *) CYREG_CSD_SW_CMP_P_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_N_SEL_REG             (*(reg32 *) CYREG_CSD_SW_CMP_N_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_SEL_REG            (*(reg32 *) CYREG_CSD_SW_REFGEN_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_MOD_SEL_REG            (*(reg32 *) CYREG_CSD_SW_FW_MOD_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_TANK_SEL_REG           (*(reg32 *) CYREG_CSD_SW_FW_TANK_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_SEL_REG               (*(reg32 *) CYREG_CSD_SW_DSI_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_REG                 (*(reg32 *) CYREG_CSD_SEQ_TIME)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_INIT_CNT_REG             (*(reg32 *) CYREG_CSD_SEQ_INIT_CNT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_NORM_CNT_REG             (*(reg32 *) CYREG_CSD_SEQ_NORM_CNT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_CTL_REG                  (*(reg32 *) CYREG_CSD_ADC_CTL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_START_REG                (*(reg32 *) CYREG_CSD_SEQ_START)

#define `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_PTR                   ((reg32 *) CYREG_CSD_CONFIG)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SPARE_PTR                    ((reg32 *) CYREG_CSD_SPARE)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_PTR                   ((reg32 *) CYREG_CSD_STATUS)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STAT_SEQ_PTR                 ((reg32 *) CYREG_CSD_STAT_SEQ)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`STAT_CNTS_PTR                ((reg32 *) CYREG_CSD_STAT_CNTS)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`RESULT_VAL1_PTR              ((reg32 *) CYREG_CSD_RESULT_VAL1)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`RESULT_VAL2_PTR              ((reg32 *) CYREG_CSD_RESULT_VAL2)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_PTR                  ((reg32 *) CYREG_CSD_ADC_RES)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_PTR                     ((reg32 *) CYREG_CSD_INTR)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_SET_PTR                 ((reg32 *) CYREG_CSD_INTR_SET)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR                ((reg32 *) CYREG_CSD_INTR_MASK)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASKED_PTR              ((reg32 *) CYREG_CSD_INTR_MASKED)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_PTR                    ((reg32 *) CYREG_CSD_HSCMP)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_PTR                    ((reg32 *) CYREG_CSD_AMBUF)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_PTR                   ((reg32 *) CYREG_CSD_REFGEN)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CSDCMP_PTR                   ((reg32 *) CYREG_CSD_CSDCMP)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`IDACA_PTR                    ((reg32 *) CYREG_CSD_IDACA)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR                    ((reg32 *) CYREG_CSD_IDACB)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_RES_PTR                   ((reg32 *) CYREG_CSD_SW_RES)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_PERIOD_PTR             ((reg32 *) CYREG_CSD_SENSE_PERIOD)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DUTY_PTR               ((reg32 *) CYREG_CSD_SENSE_DUTY)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_P_SEL_PTR              ((reg32 *) CYREG_CSD_SW_HS_P_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_N_SEL_PTR              ((reg32 *) CYREG_CSD_SW_HS_N_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_PTR            ((reg32 *) CYREG_CSD_SW_SHIELD_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUXBUF_SEL_PTR           ((reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR               ((reg32 *) CYREG_CSD_SW_BYP_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_P_SEL_PTR             ((reg32 *) CYREG_CSD_SW_CMP_P_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_N_SEL_PTR             ((reg32 *) CYREG_CSD_SW_CMP_N_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_SEL_PTR            ((reg32 *) CYREG_CSD_SW_REFGEN_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_MOD_SEL_PTR            ((reg32 *) CYREG_CSD_SW_FW_MOD_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_TANK_SEL_PTR           ((reg32 *) CYREG_CSD_SW_FW_TANK_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_SEL_PTR               ((reg32 *) CYREG_CSD_SW_DSI_SEL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_PTR                 ((reg32 *) CYREG_CSD_SEQ_TIME)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_INIT_CNT_PTR             ((reg32 *) CYREG_CSD_SEQ_INIT_CNT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_NORM_CNT_PTR             ((reg32 *) CYREG_CSD_SEQ_NORM_CNT)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_CTL_PTR                  ((reg32 *) CYREG_CSD_ADC_CTL)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_START_PTR                ((reg32 *) CYREG_CSD_SEQ_START)


#endif 	/* `$INSTANCE_NAME`_ADC_EN */

#endif	/* CY_CAPSENSE_`$INSTANCE_NAME`_ADC_H */


/* [] END OF FILE */
