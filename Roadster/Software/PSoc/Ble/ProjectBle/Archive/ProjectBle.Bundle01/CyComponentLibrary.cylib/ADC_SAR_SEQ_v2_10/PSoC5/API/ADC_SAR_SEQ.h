/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition of the
*  ADC SAR Sequencer Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_`$INSTANCE_NAME`_H)
    #define CY_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "`$INSTANCE_NAME`_TempBuf_dma.h"
#include "`$INSTANCE_NAME`_FinalBuf_dma.h"
#include "`$INSTANCE_NAME`_SAR.h"

#define `$INSTANCE_NAME`_NUMBER_OF_CHANNELS    (`$NumChannels`u)
#define `$INSTANCE_NAME`_SAMPLE_MODE           (`$SampleMode`u)
#define `$INSTANCE_NAME`_CLOCK_SOURCE          (`$ClockSource`u)

extern int16  `$INSTANCE_NAME`_finalArray[`$INSTANCE_NAME`_NUMBER_OF_CHANNELS];
extern uint32 `$INSTANCE_NAME`_initVar;

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*        Function Prototypes
***************************************/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Disable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);

uint32 `$INSTANCE_NAME`_IsEndConversion(uint8 retMode);
int16 `$INSTANCE_NAME`_GetResult16(uint16 chan);
int16 `$INSTANCE_NAME`_GetAdcResult(void);
void `$INSTANCE_NAME`_SetOffset(int32 offset);
void `$INSTANCE_NAME`_SetResolution(uint8 resolution);
void `$INSTANCE_NAME`_SetScaledGain(int32 adcGain);
int32 `$INSTANCE_NAME`_CountsTo_mVolts(int16 adcCounts);
int32 `$INSTANCE_NAME`_CountsTo_uVolts(int16 adcCounts);
float32 `$INSTANCE_NAME`_CountsTo_Volts(int16 adcCounts);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);

CY_ISR_PROTO( `$INSTANCE_NAME`_ISR );

/* Obsolete API for backward compatibility.
*  Should not be used in new designs.
*/
void `$INSTANCE_NAME`_SetGain(int32 adcGain);


/**************************************
*    Initial Parameter Constants
**************************************/
#define `$INSTANCE_NAME`_IRQ_REMOVE             (`$rm_int`u)                /* Removes internal interrupt */


/***************************************
*             Registers
***************************************/
#define `$INSTANCE_NAME`_CYCLE_COUNTER_AUX_CONTROL_REG \
                                               (*(reg8 *) `$INSTANCE_NAME`_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_CYCLE_COUNTER_AUX_CONTROL_PTR \
                                               ( (reg8 *) `$INSTANCE_NAME`_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_CONTROL_REG    (*(reg8 *) \
                                             `$INSTANCE_NAME`_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_CONTROL_PTR    ( (reg8 *) \
                                             `$INSTANCE_NAME`_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_COUNT_REG      (*(reg8 *) \
                                             `$INSTANCE_NAME`_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define `$INSTANCE_NAME`_COUNT_PTR      ( (reg8 *) \
                                             `$INSTANCE_NAME`_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define `$INSTANCE_NAME`_STATUS_REG     (*(reg8 *) `$INSTANCE_NAME`_bSAR_SEQ_EOCSts__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_PTR     ( (reg8 *) `$INSTANCE_NAME`_bSAR_SEQ_EOCSts__STATUS_REG)

#define `$INSTANCE_NAME`_SAR_DATA_ADDR_0 (`$INSTANCE_NAME`_SAR_ADC_SAR__WRK0)
#define `$INSTANCE_NAME`_SAR_DATA_ADDR_1 (`$INSTANCE_NAME`_SAR_ADC_SAR__WRK1)
#define `$INSTANCE_NAME`_SAR_DATA_ADDR_0_REG (*(reg8 *) \
                                              `$INSTANCE_NAME`_SAR_ADC_SAR__WRK0)
#define `$INSTANCE_NAME`_SAR_DATA_ADDR_1_REG (*(reg8 *) \
                                              `$INSTANCE_NAME`_SAR_ADC_SAR__WRK1)


/**************************************
*       Register Constants
**************************************/

#if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define `$INSTANCE_NAME`_INTC_PRIOR_NUMBER          (uint8)(`$INSTANCE_NAME`_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define `$INSTANCE_NAME`_INTC_NUMBER                (uint8)(`$INSTANCE_NAME`_IRQ__INTC_NUMBER)

#endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */


/***************************************
*       API Constants
***************************************/

/* Constants for IsEndConversion() "retMode" parameter */
#define `$INSTANCE_NAME`_RETURN_STATUS              (0x01u)
#define `$INSTANCE_NAME`_WAIT_FOR_RESULT            (0x00u)

/* Defines for the Resolution parameter */
#define `$INSTANCE_NAME`_BITS_12    `$INSTANCE_NAME`_SAR__BITS_12
#define `$INSTANCE_NAME`_BITS_10    `$INSTANCE_NAME`_SAR__BITS_10
#define `$INSTANCE_NAME`_BITS_8     `$INSTANCE_NAME`_SAR__BITS_8

#define `$INSTANCE_NAME`_CYCLE_COUNTER_ENABLE    (0x20u)
#define `$INSTANCE_NAME`_BASE_COMPONENT_ENABLE   (0x01u)
#define `$INSTANCE_NAME`_LOAD_COUNTER_PERIOD     (0x02u)
#define `$INSTANCE_NAME`_SOFTWARE_SOC_PULSE      (0x04u)

/* Generic DMA Configuration parameters */
#define `$INSTANCE_NAME`_TEMP_BYTES_PER_BURST     (uint8)(2u)
#define `$INSTANCE_NAME`_TEMP_TRANSFER_COUNT      ((uint16)`$INSTANCE_NAME`_NUMBER_OF_CHANNELS << 1u)
#define `$INSTANCE_NAME`_FINAL_BYTES_PER_BURST    ((uint16)`$INSTANCE_NAME`_NUMBER_OF_CHANNELS << 1u)
#define `$INSTANCE_NAME`_REQUEST_PER_BURST        (uint8)(1u)

#define `$INSTANCE_NAME`_GET_RESULT_INDEX_OFFSET    ((uint8)`$INSTANCE_NAME`_NUMBER_OF_CHANNELS - 1u)

/* Define for Sample Mode  */
#define `$INSTANCE_NAME`_SAMPLE_MODE_FREE_RUNNING    (0x00u)
#define `$INSTANCE_NAME`_SAMPLE_MODE_SW_TRIGGERED    (0x01u)
#define `$INSTANCE_NAME`_SAMPLE_MODE_HW_TRIGGERED    (0x02u)

/* Define for Clock Source  */
#define `$INSTANCE_NAME`_CLOCK_INTERNAL              (0x00u)
#define `$INSTANCE_NAME`_CLOCK_EXTERNAL              (0x01u)


/***************************************
*        Optional Function Prototypes
***************************************/
#if(`$INSTANCE_NAME`_SAMPLE_MODE != `$INSTANCE_NAME`_SAMPLE_MODE_HW_TRIGGERED)
    void `$INSTANCE_NAME`_StartConvert(void);
    void `$INSTANCE_NAME`_StopConvert(void);
#endif /* `$INSTANCE_NAME`_SAMPLE_MODE != `$INSTANCE_NAME`_SAMPLE_MODE_HW_TRIGGERED */

#endif  /* !defined(CY_`$INSTANCE_NAME`_H) */

/* [] END OF FILE */
