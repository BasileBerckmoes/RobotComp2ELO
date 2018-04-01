/*******************************************************************************
* File Name: JoyStickADC.h
* Version 2.10
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

#if !defined(CY_JoyStickADC_H)
    #define CY_JoyStickADC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "JoyStickADC_TempBuf_dma.h"
#include "JoyStickADC_FinalBuf_dma.h"
#include "JoyStickADC_SAR.h"

#define JoyStickADC_NUMBER_OF_CHANNELS    (2u)
#define JoyStickADC_SAMPLE_MODE           (0u)
#define JoyStickADC_CLOCK_SOURCE          (0u)

extern int16  JoyStickADC_finalArray[JoyStickADC_NUMBER_OF_CHANNELS];
extern uint32 JoyStickADC_initVar;

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ADC_SAR_SEQ_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*        Function Prototypes
***************************************/
void JoyStickADC_Init(void);
void JoyStickADC_Enable(void);
void JoyStickADC_Disable(void);
void JoyStickADC_Start(void);
void JoyStickADC_Stop(void);

uint32 JoyStickADC_IsEndConversion(uint8 retMode);
int16 JoyStickADC_GetResult16(uint16 chan);
int16 JoyStickADC_GetAdcResult(void);
void JoyStickADC_SetOffset(int32 offset);
void JoyStickADC_SetResolution(uint8 resolution);
void JoyStickADC_SetScaledGain(int32 adcGain);
int32 JoyStickADC_CountsTo_mVolts(int16 adcCounts);
int32 JoyStickADC_CountsTo_uVolts(int16 adcCounts);
float32 JoyStickADC_CountsTo_Volts(int16 adcCounts);
void JoyStickADC_Sleep(void);
void JoyStickADC_Wakeup(void);
void JoyStickADC_SaveConfig(void);
void JoyStickADC_RestoreConfig(void);

CY_ISR_PROTO( JoyStickADC_ISR );

/* Obsolete API for backward compatibility.
*  Should not be used in new designs.
*/
void JoyStickADC_SetGain(int32 adcGain);


/**************************************
*    Initial Parameter Constants
**************************************/
#define JoyStickADC_IRQ_REMOVE             (0u)                /* Removes internal interrupt */


/***************************************
*             Registers
***************************************/
#define JoyStickADC_CYCLE_COUNTER_AUX_CONTROL_REG \
                                               (*(reg8 *) JoyStickADC_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define JoyStickADC_CYCLE_COUNTER_AUX_CONTROL_PTR \
                                               ( (reg8 *) JoyStickADC_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define JoyStickADC_CONTROL_REG    (*(reg8 *) \
                                             JoyStickADC_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define JoyStickADC_CONTROL_PTR    ( (reg8 *) \
                                             JoyStickADC_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define JoyStickADC_COUNT_REG      (*(reg8 *) \
                                             JoyStickADC_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define JoyStickADC_COUNT_PTR      ( (reg8 *) \
                                             JoyStickADC_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define JoyStickADC_STATUS_REG     (*(reg8 *) JoyStickADC_bSAR_SEQ_EOCSts__STATUS_REG)
#define JoyStickADC_STATUS_PTR     ( (reg8 *) JoyStickADC_bSAR_SEQ_EOCSts__STATUS_REG)

#define JoyStickADC_SAR_DATA_ADDR_0 (JoyStickADC_SAR_ADC_SAR__WRK0)
#define JoyStickADC_SAR_DATA_ADDR_1 (JoyStickADC_SAR_ADC_SAR__WRK1)
#define JoyStickADC_SAR_DATA_ADDR_0_REG (*(reg8 *) \
                                              JoyStickADC_SAR_ADC_SAR__WRK0)
#define JoyStickADC_SAR_DATA_ADDR_1_REG (*(reg8 *) \
                                              JoyStickADC_SAR_ADC_SAR__WRK1)


/**************************************
*       Register Constants
**************************************/

#if(JoyStickADC_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define JoyStickADC_INTC_PRIOR_NUMBER          (uint8)(JoyStickADC_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define JoyStickADC_INTC_NUMBER                (uint8)(JoyStickADC_IRQ__INTC_NUMBER)

#endif   /* End JoyStickADC_IRQ_REMOVE */


/***************************************
*       API Constants
***************************************/

/* Constants for IsEndConversion() "retMode" parameter */
#define JoyStickADC_RETURN_STATUS              (0x01u)
#define JoyStickADC_WAIT_FOR_RESULT            (0x00u)

/* Defines for the Resolution parameter */
#define JoyStickADC_BITS_12    JoyStickADC_SAR__BITS_12
#define JoyStickADC_BITS_10    JoyStickADC_SAR__BITS_10
#define JoyStickADC_BITS_8     JoyStickADC_SAR__BITS_8

#define JoyStickADC_CYCLE_COUNTER_ENABLE    (0x20u)
#define JoyStickADC_BASE_COMPONENT_ENABLE   (0x01u)
#define JoyStickADC_LOAD_COUNTER_PERIOD     (0x02u)
#define JoyStickADC_SOFTWARE_SOC_PULSE      (0x04u)

/* Generic DMA Configuration parameters */
#define JoyStickADC_TEMP_BYTES_PER_BURST     (uint8)(2u)
#define JoyStickADC_TEMP_TRANSFER_COUNT      ((uint16)JoyStickADC_NUMBER_OF_CHANNELS << 1u)
#define JoyStickADC_FINAL_BYTES_PER_BURST    ((uint16)JoyStickADC_NUMBER_OF_CHANNELS << 1u)
#define JoyStickADC_REQUEST_PER_BURST        (uint8)(1u)

#define JoyStickADC_GET_RESULT_INDEX_OFFSET    ((uint8)JoyStickADC_NUMBER_OF_CHANNELS - 1u)

/* Define for Sample Mode  */
#define JoyStickADC_SAMPLE_MODE_FREE_RUNNING    (0x00u)
#define JoyStickADC_SAMPLE_MODE_SW_TRIGGERED    (0x01u)
#define JoyStickADC_SAMPLE_MODE_HW_TRIGGERED    (0x02u)

/* Define for Clock Source  */
#define JoyStickADC_CLOCK_INTERNAL              (0x00u)
#define JoyStickADC_CLOCK_EXTERNAL              (0x01u)


/***************************************
*        Optional Function Prototypes
***************************************/
#if(JoyStickADC_SAMPLE_MODE != JoyStickADC_SAMPLE_MODE_HW_TRIGGERED)
    void JoyStickADC_StartConvert(void);
    void JoyStickADC_StopConvert(void);
#endif /* JoyStickADC_SAMPLE_MODE != JoyStickADC_SAMPLE_MODE_HW_TRIGGERED */

#endif  /* !defined(CY_JoyStickADC_H) */

/* [] END OF FILE */
