/*******************************************************************************
* File Name: AdcMux.h
* Version 2.0
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

#if !defined(CY_AdcMux_H)
    #define CY_AdcMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "AdcMux_TempBuf_dma.h"
#include "AdcMux_FinalBuf_dma.h"
#include "AdcMux_SAR.h"

#define AdcMux_NUMBER_OF_CHANNELS    (4u)
#define AdcMux_SAMPLE_MODE           (0u)
#define AdcMux_CLOCK_SOURCE          (0u)

extern int16  AdcMux_finalArray[AdcMux_NUMBER_OF_CHANNELS];
extern uint32 AdcMux_initVar;

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ADC_SAR_SEQ_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*        Function Prototypes
***************************************/
void AdcMux_Init(void);
void AdcMux_Enable(void);
void AdcMux_Disable(void);
void AdcMux_Start(void);
void AdcMux_Stop(void);

uint32 AdcMux_IsEndConversion(uint8 retMode);
int16 AdcMux_GetResult16(uint16 chan);
int16 AdcMux_GetAdcResult(void);
void AdcMux_SetOffset(int32 offset);
void AdcMux_SetResolution(uint8 resolution);
void AdcMux_SetScaledGain(int32 adcGain);
int32 AdcMux_CountsTo_mVolts(int16 adcCounts);
int32 AdcMux_CountsTo_uVolts(int16 adcCounts);
float32 AdcMux_CountsTo_Volts(int16 adcCounts);
void AdcMux_Sleep(void);
void AdcMux_Wakeup(void);
void AdcMux_SaveConfig(void);
void AdcMux_RestoreConfig(void);

CY_ISR_PROTO( AdcMux_ISR );

/* Obsolete API for backward compatibility.
*  Should not be used in new designs.
*/
void AdcMux_SetGain(int32 adcGain);


/**************************************
*    Initial Parameter Constants
**************************************/
#define AdcMux_IRQ_REMOVE             (0u)                /* Removes internal interrupt */


/***************************************
*             Registers
***************************************/
#define AdcMux_CYCLE_COUNTER_AUX_CONTROL_REG \
                                               (*(reg8 *) AdcMux_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define AdcMux_CYCLE_COUNTER_AUX_CONTROL_PTR \
                                               ( (reg8 *) AdcMux_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define AdcMux_CONTROL_REG    (*(reg8 *) \
                                             AdcMux_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define AdcMux_CONTROL_PTR    ( (reg8 *) \
                                             AdcMux_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define AdcMux_COUNT_REG      (*(reg8 *) \
                                             AdcMux_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define AdcMux_COUNT_PTR      ( (reg8 *) \
                                             AdcMux_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define AdcMux_STATUS_REG     (*(reg8 *) AdcMux_bSAR_SEQ_EOCSts__STATUS_REG)
#define AdcMux_STATUS_PTR     ( (reg8 *) AdcMux_bSAR_SEQ_EOCSts__STATUS_REG)

#define AdcMux_SAR_DATA_ADDR_0 (AdcMux_SAR_ADC_SAR__WRK0)
#define AdcMux_SAR_DATA_ADDR_1 (AdcMux_SAR_ADC_SAR__WRK1)
#define AdcMux_SAR_DATA_ADDR_0_REG (*(reg8 *) \
                                              AdcMux_SAR_ADC_SAR__WRK0)
#define AdcMux_SAR_DATA_ADDR_1_REG (*(reg8 *) \
                                              AdcMux_SAR_ADC_SAR__WRK1)


/**************************************
*       Register Constants
**************************************/

#if(AdcMux_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define AdcMux_INTC_PRIOR_NUMBER          (uint8)(AdcMux_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define AdcMux_INTC_NUMBER                (uint8)(AdcMux_IRQ__INTC_NUMBER)

#endif   /* End AdcMux_IRQ_REMOVE */


/***************************************
*       API Constants
***************************************/

/* Constants for IsEndConversion() "retMode" parameter */
#define AdcMux_RETURN_STATUS              (0x01u)
#define AdcMux_WAIT_FOR_RESULT            (0x00u)

/* Defines for the Resolution parameter */
#define AdcMux_BITS_12    AdcMux_SAR__BITS_12
#define AdcMux_BITS_10    AdcMux_SAR__BITS_10
#define AdcMux_BITS_8     AdcMux_SAR__BITS_8

#define AdcMux_CYCLE_COUNTER_ENABLE    (0x20u)
#define AdcMux_BASE_COMPONENT_ENABLE   (0x01u)
#define AdcMux_LOAD_COUNTER_PERIOD     (0x02u)
#define AdcMux_SOFTWARE_SOC_PULSE      (0x04u)

/* Generic DMA Configuration parameters */
#define AdcMux_TEMP_BYTES_PER_BURST     (uint8)(2u)
#define AdcMux_TEMP_TRANSFER_COUNT      ((uint16)AdcMux_NUMBER_OF_CHANNELS << 1u)
#define AdcMux_FINAL_BYTES_PER_BURST    ((uint16)AdcMux_NUMBER_OF_CHANNELS << 1u)
#define AdcMux_REQUEST_PER_BURST        (uint8)(1u)

#define AdcMux_GET_RESULT_INDEX_OFFSET    ((uint8)AdcMux_NUMBER_OF_CHANNELS - 1u)

/* Define for Sample Mode  */
#define AdcMux_SAMPLE_MODE_FREE_RUNNING    (0x00u)
#define AdcMux_SAMPLE_MODE_SW_TRIGGERED    (0x01u)
#define AdcMux_SAMPLE_MODE_HW_TRIGGERED    (0x02u)

/* Define for Clock Source  */
#define AdcMux_CLOCK_INTERNAL              (0x00u)
#define AdcMux_CLOCK_EXTERNAL              (0x01u)


/***************************************
*        Optional Function Prototypes
***************************************/
#if(AdcMux_SAMPLE_MODE != AdcMux_SAMPLE_MODE_HW_TRIGGERED)
    void AdcMux_StartConvert(void);
    void AdcMux_StopConvert(void);
#endif /* AdcMux_SAMPLE_MODE != AdcMux_SAMPLE_MODE_HW_TRIGGERED */

#endif  /* !defined(CY_AdcMux_H) */

/* [] END OF FILE */
