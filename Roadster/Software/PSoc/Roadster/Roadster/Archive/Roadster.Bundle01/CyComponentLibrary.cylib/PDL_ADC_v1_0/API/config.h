/*******************************************************************************
* \file `$INSTANCE_NAME`_config.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable declarations for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_CONFIG_H
#define `$INSTANCE_NAME`_CONFIG_H

#include "adc/adc.h"
#include "cyfitter.h"

/* Check to see if a selected device is supported */
#if (PDL_ADC_TYPE == PDL_ADC_A)
    #error Component `$CY_COMPONENT_NAME` does not support selected device.
#endif /* PDL_ADC_TYPE == PDL_ADC_A */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Hardware pointer */
#define `$INSTANCE_NAME`_HW     `$INSTANCE_NAME`_fm_adc__HW

/* Pin function macros */
`=$bPrioExtTrigStartEnable ? "#define `$INSTANCE_NAME`_SetPinFunc_ADTG()      CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_ADTG()" : "/* ADTG pin unused */"`

/* Macro to connect the ADC channels to analog input pins. 
*  channel: Specifies the ADC channel.
*    CH0 - ADC channel 0
*    CH1 - ADC channel 1
*    ...
*    CHn - ADC channel n
*/
#define `$INSTANCE_NAME`_SetPinFunc_AN(channel)    CYDEV_SetPinFunc__`$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_##channel()

/* Interrupt selection */
extern `=$CY_CONST_CONFIG ? "const" : ""` stc_adc_irq_en_t `$INSTANCE_NAME`_IrqEn;

/* Interrupt callback function */
extern `=$CY_CONST_CONFIG ? "const" : ""` stc_adc_irq_cb_t `$INSTANCE_NAME`_IrqCb;

/* Configuration structure */
extern `=$CY_CONST_CONFIG ? "const " : ""` stc_adc_config_t `$INSTANCE_NAME`_Config;

/* Scan conversion interrupt callback function */
`=($pfnScanIrqCb eq "") || !$bScanIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnScanIrqCb . "(volatile uint32_t* pu32Argument);"`

/* Priority conversion interrupt callback function */
`=($pfnPrioIrqCb eq "") || !$bPrioIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPrioIrqCb . "(volatile uint32_t* pu32Argument);"`

/* Scan FIFO overrun error callback function */
`=($pfnScanErrIrqCb eq "") || !$bFifoOverrunIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnScanErrIrqCb . "(void);"`

/* Priority FIFO overrun error callback function */
`=($pfnPrioErrIrqCb eq "") || !$bFifoOverrunIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnPrioErrIrqCb . "(void);"`

/* Comparison interrupt callback function */
`=($pfnComparisonIrqCb eq "") || !$bComparisonIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnComparisonIrqCb . "(void);"`

/* Range condition interrupt callback function */
`=($pfnRangeComparisonIrqCb eq "") || !$bRangeComparisonIrq ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnRangeComparisonIrqCb . "(void);"`

/* ADC channels */
#define `$INSTANCE_NAME`_CH_NR              `$numLogicalChannels`U

/* Channel 0 */
#define `$INSTANCE_NAME`_CH0                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH0__PIN_MAP
#define `$INSTANCE_NAME`_CH0_MSK            ((uint32_t)(`$Ch0ActiveMasked`UL << `$INSTANCE_NAME`_CH0))
#define `$INSTANCE_NAME`_CH0_SMPL_TIME      ((uint32_t)(`$Ch0SamplingTime`UL << `$INSTANCE_NAME`_CH0))

/* Channel 1 */
#if (`$INSTANCE_NAME`_CH_NR > 1u)
#define `$INSTANCE_NAME`_CH1                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH1__PIN_MAP
#define `$INSTANCE_NAME`_CH1_MSK            ((uint32_t)(`$Ch1ActiveMasked`UL << `$INSTANCE_NAME`_CH1))
#define `$INSTANCE_NAME`_CH1_SMPL_TIME      ((uint32_t)(`$Ch1SamplingTime`UL << `$INSTANCE_NAME`_CH1))
#else
#define `$INSTANCE_NAME`_CH1_MSK            0UL
#define `$INSTANCE_NAME`_CH1_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 1u */

/* Channel 2 */
#if (`$INSTANCE_NAME`_CH_NR > 2u)
#define `$INSTANCE_NAME`_CH2                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH2__PIN_MAP
#define `$INSTANCE_NAME`_CH2_MSK            ((uint32_t)(`$Ch2ActiveMasked`UL << `$INSTANCE_NAME`_CH2))
#define `$INSTANCE_NAME`_CH2_SMPL_TIME      ((uint32_t)(`$Ch2SamplingTime`UL << `$INSTANCE_NAME`_CH2))
#else
#define `$INSTANCE_NAME`_CH2_MSK            0UL
#define `$INSTANCE_NAME`_CH2_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 2u */

/* Channel 3 */
#if (`$INSTANCE_NAME`_CH_NR > 3u)
#define `$INSTANCE_NAME`_CH3                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH3__PIN_MAP
#define `$INSTANCE_NAME`_CH3_MSK            ((uint32_t)(`$Ch3ActiveMasked`UL << `$INSTANCE_NAME`_CH3))
#define `$INSTANCE_NAME`_CH3_SMPL_TIME      ((uint32_t)(`$Ch3SamplingTime`UL << `$INSTANCE_NAME`_CH3))
#else
#define `$INSTANCE_NAME`_CH3_MSK            0UL
#define `$INSTANCE_NAME`_CH3_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 3u */

/* Channel 4 */
#if (`$INSTANCE_NAME`_CH_NR > 4u)
#define `$INSTANCE_NAME`_CH4                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH4__PIN_MAP
#define `$INSTANCE_NAME`_CH4_MSK            ((uint32_t)(`$Ch4ActiveMasked`UL << `$INSTANCE_NAME`_CH4))
#define `$INSTANCE_NAME`_CH4_SMPL_TIME      ((uint32_t)(`$Ch4SamplingTime`UL << `$INSTANCE_NAME`_CH4))
#else
#define `$INSTANCE_NAME`_CH4_MSK            0UL
#define `$INSTANCE_NAME`_CH4_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 4u */

/* Channel 5 */
#if (`$INSTANCE_NAME`_CH_NR > 5u)
#define `$INSTANCE_NAME`_CH5                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH5__PIN_MAP
#define `$INSTANCE_NAME`_CH5_MSK            ((uint32_t)(`$Ch5ActiveMasked`UL << `$INSTANCE_NAME`_CH5))
#define `$INSTANCE_NAME`_CH5_SMPL_TIME      ((uint32_t)(`$Ch5SamplingTime`UL << `$INSTANCE_NAME`_CH5))
#else
#define `$INSTANCE_NAME`_CH5_MSK            0UL
#define `$INSTANCE_NAME`_CH5_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 5u */   

/* Channel 6 */
#if (`$INSTANCE_NAME`_CH_NR > 6u)
#define `$INSTANCE_NAME`_CH6                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH6__PIN_MAP
#define `$INSTANCE_NAME`_CH6_MSK            ((uint32_t)(`$Ch6ActiveMasked`UL << `$INSTANCE_NAME`_CH6))
#define `$INSTANCE_NAME`_CH6_SMPL_TIME      ((uint32_t)(`$Ch6SamplingTime`UL << `$INSTANCE_NAME`_CH6))
#else
#define `$INSTANCE_NAME`_CH6_MSK            0UL
#define `$INSTANCE_NAME`_CH6_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 6u */

/* Channel 7 */
#if (`$INSTANCE_NAME`_CH_NR > 7u)
#define `$INSTANCE_NAME`_CH7                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH7__PIN_MAP
#define `$INSTANCE_NAME`_CH7_MSK            ((uint32_t)(`$Ch7ActiveMasked`UL << `$INSTANCE_NAME`_CH7))
#define `$INSTANCE_NAME`_CH7_SMPL_TIME      ((uint32_t)(`$Ch7SamplingTime`UL << `$INSTANCE_NAME`_CH7))
#else
#define `$INSTANCE_NAME`_CH7_MSK            0UL
#define `$INSTANCE_NAME`_CH7_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 7u */

/* Channel 8 */
#if (`$INSTANCE_NAME`_CH_NR > 8u)
#define `$INSTANCE_NAME`_CH8                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH8__PIN_MAP
#define `$INSTANCE_NAME`_CH8_MSK            ((uint32_t)(`$Ch8ActiveMasked`UL << `$INSTANCE_NAME`_CH8))
#define `$INSTANCE_NAME`_CH8_SMPL_TIME      ((uint32_t)(`$Ch8SamplingTime`UL << `$INSTANCE_NAME`_CH8))    
#else
#define `$INSTANCE_NAME`_CH8_MSK            0UL
#define `$INSTANCE_NAME`_CH8_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 8u */

/* Channel 9 */
#if (`$INSTANCE_NAME`_CH_NR > 9u)
#define `$INSTANCE_NAME`_CH9                `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH9__PIN_MAP
#define `$INSTANCE_NAME`_CH9_MSK            ((uint32_t)(`$Ch9ActiveMasked`UL << `$INSTANCE_NAME`_CH9))
#define `$INSTANCE_NAME`_CH9_SMPL_TIME      ((uint32_t)(`$Ch9SamplingTime`UL << `$INSTANCE_NAME`_CH9))
#else
#define `$INSTANCE_NAME`_CH9_MSK            0UL
#define `$INSTANCE_NAME`_CH9_SMPL_TIME      0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 9u */
#if (`$INSTANCE_NAME`_CH_NR > 10u)
#define `$INSTANCE_NAME`_CH10               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH10__PIN_MAP
#define `$INSTANCE_NAME`_CH10_MSK           ((uint32_t)(`$Ch10ActiveMasked`UL << `$INSTANCE_NAME`_CH10))
#define `$INSTANCE_NAME`_CH10_SMPL_TIME     ((uint32_t)(`$Ch10SamplingTime`UL << `$INSTANCE_NAME`_CH10))
#else
#define `$INSTANCE_NAME`_CH10_MSK           0UL
#define `$INSTANCE_NAME`_CH10_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 10u */
#if (`$INSTANCE_NAME`_CH_NR > 11u)
#define `$INSTANCE_NAME`_CH11               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH11__PIN_MAP
#define `$INSTANCE_NAME`_CH11_MSK           ((uint32_t)(`$Ch11ActiveMasked`UL << `$INSTANCE_NAME`_CH11))
#define `$INSTANCE_NAME`_CH11_SMPL_TIME     ((uint32_t)(`$Ch11SamplingTime`UL << `$INSTANCE_NAME`_CH11))
#else
#define `$INSTANCE_NAME`_CH11_MSK           0UL
#define `$INSTANCE_NAME`_CH11_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 11u */
#if (`$INSTANCE_NAME`_CH_NR > 12u)
#define `$INSTANCE_NAME`_CH12               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH12__PIN_MAP
#define `$INSTANCE_NAME`_CH12_MSK           ((uint32_t)(`$Ch12ActiveMasked`UL << `$INSTANCE_NAME`_CH12))
#define `$INSTANCE_NAME`_CH12_SMPL_TIME     ((uint32_t)(`$Ch12SamplingTime`UL << `$INSTANCE_NAME`_CH12))
#else
#define `$INSTANCE_NAME`_CH12_MSK           0UL
#define `$INSTANCE_NAME`_CH12_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 12u */
#if (`$INSTANCE_NAME`_CH_NR > 13u)
#define `$INSTANCE_NAME`_CH13               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH13__PIN_MAP
#define `$INSTANCE_NAME`_CH13_MSK           ((uint32_t)(`$Ch13ActiveMasked`UL << `$INSTANCE_NAME`_CH13))
#define `$INSTANCE_NAME`_CH13_SMPL_TIME     ((uint32_t)(`$Ch13SamplingTime`UL << `$INSTANCE_NAME`_CH13))
#else
#define `$INSTANCE_NAME`_CH13_MSK           0UL
#define `$INSTANCE_NAME`_CH13_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 13u */
#if (`$INSTANCE_NAME`_CH_NR > 14u)
#define `$INSTANCE_NAME`_CH14               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH14__PIN_MAP
#define `$INSTANCE_NAME`_CH14_MSK           ((uint32_t)(`$Ch14ActiveMasked`UL << `$INSTANCE_NAME`_CH14))
#define `$INSTANCE_NAME`_CH14_SMPL_TIME     ((uint32_t)(`$Ch14SamplingTime`UL << `$INSTANCE_NAME`_CH14))
#else
#define `$INSTANCE_NAME`_CH14_MSK           0UL
#define `$INSTANCE_NAME`_CH14_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 14u */
#if (`$INSTANCE_NAME`_CH_NR > 15u)
#define `$INSTANCE_NAME`_CH15               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH15__PIN_MAP
#define `$INSTANCE_NAME`_CH15_MSK           ((uint32_t)(`$Ch15ActiveMasked`UL << `$INSTANCE_NAME`_CH15))
#define `$INSTANCE_NAME`_CH15_SMPL_TIME     ((uint32_t)(`$Ch15SamplingTime`UL << `$INSTANCE_NAME`_CH15))
#else
#define `$INSTANCE_NAME`_CH15_MSK           0UL
#define `$INSTANCE_NAME`_CH15_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 15u */
#if (`$INSTANCE_NAME`_CH_NR > 16u)
#define `$INSTANCE_NAME`_CH16               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH16__PIN_MAP
#define `$INSTANCE_NAME`_CH16_MSK           ((uint32_t)(`$Ch16ActiveMasked`UL << `$INSTANCE_NAME`_CH16))
#define `$INSTANCE_NAME`_CH16_SMPL_TIME     ((uint32_t)(`$Ch16SamplingTime`UL << `$INSTANCE_NAME`_CH16))
#else
#define `$INSTANCE_NAME`_CH16_MSK           0UL
#define `$INSTANCE_NAME`_CH16_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 16u */
#if (`$INSTANCE_NAME`_CH_NR > 17u)
#define `$INSTANCE_NAME`_CH17               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH17__PIN_MAP
#define `$INSTANCE_NAME`_CH17_MSK           ((uint32_t)(`$Ch17ActiveMasked`UL << `$INSTANCE_NAME`_CH17))
#define `$INSTANCE_NAME`_CH17_SMPL_TIME     ((uint32_t)(`$Ch17SamplingTime`UL << `$INSTANCE_NAME`_CH17))
#else
#define `$INSTANCE_NAME`_CH17_MSK           0UL
#define `$INSTANCE_NAME`_CH17_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 17u */
#if (`$INSTANCE_NAME`_CH_NR > 18u)
#define `$INSTANCE_NAME`_CH18               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH18__PIN_MAP
#define `$INSTANCE_NAME`_CH18_MSK           ((uint32_t)(`$Ch18ActiveMasked`UL << `$INSTANCE_NAME`_CH18))
#define `$INSTANCE_NAME`_CH18_SMPL_TIME     ((uint32_t)(`$Ch18SamplingTime`UL << `$INSTANCE_NAME`_CH18))
#else
#define `$INSTANCE_NAME`_CH18_MSK           0UL
#define `$INSTANCE_NAME`_CH18_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 18u */
#if (`$INSTANCE_NAME`_CH_NR > 19u)
#define `$INSTANCE_NAME`_CH19               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH19__PIN_MAP
#define `$INSTANCE_NAME`_CH19_MSK           ((uint32_t)(`$Ch19ActiveMasked`UL << `$INSTANCE_NAME`_CH19))
#define `$INSTANCE_NAME`_CH19_SMPL_TIME     ((uint32_t)(`$Ch19SamplingTime`UL << `$INSTANCE_NAME`_CH19))
#else
#define `$INSTANCE_NAME`_CH19_MSK           0UL
#define `$INSTANCE_NAME`_CH19_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 19u */
#if (`$INSTANCE_NAME`_CH_NR > 20u)
#define `$INSTANCE_NAME`_CH20               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH20__PIN_MAP
#define `$INSTANCE_NAME`_CH20_MSK           ((uint32_t)(`$Ch20ActiveMasked`UL << `$INSTANCE_NAME`_CH20))
#define `$INSTANCE_NAME`_CH20_SMPL_TIME     ((uint32_t)(`$Ch20SamplingTime`UL << `$INSTANCE_NAME`_CH20))
#else
#define `$INSTANCE_NAME`_CH20_MSK           0UL
#define `$INSTANCE_NAME`_CH20_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 20u */
#if (`$INSTANCE_NAME`_CH_NR > 21u)
#define `$INSTANCE_NAME`_CH21               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH21__PIN_MAP
#define `$INSTANCE_NAME`_CH21_MSK           ((uint32_t)(`$Ch21ActiveMasked`UL << `$INSTANCE_NAME`_CH21))
#define `$INSTANCE_NAME`_CH21_SMPL_TIME     ((uint32_t)(`$Ch21SamplingTime`UL << `$INSTANCE_NAME`_CH21))
#else
#define `$INSTANCE_NAME`_CH21_MSK           0UL
#define `$INSTANCE_NAME`_CH21_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 21u */
#if (`$INSTANCE_NAME`_CH_NR > 22u)
#define `$INSTANCE_NAME`_CH22               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH22__PIN_MAP
#define `$INSTANCE_NAME`_CH22_MSK           ((uint32_t)(`$Ch22ActiveMasked`UL << `$INSTANCE_NAME`_CH22))
#define `$INSTANCE_NAME`_CH22_SMPL_TIME     ((uint32_t)(`$Ch22SamplingTime`UL << `$INSTANCE_NAME`_CH22))
#else
#define `$INSTANCE_NAME`_CH22_MSK           0UL
#define `$INSTANCE_NAME`_CH22_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 22u */
#if (`$INSTANCE_NAME`_CH_NR > 23u)
#define `$INSTANCE_NAME`_CH23               `$INSTANCE_NAME`_fm_adc__`$INSTANCE_NAME`_CH23__PIN_MAP
#define `$INSTANCE_NAME`_CH23_MSK           ((uint32_t)(`$Ch23ActiveMasked`UL << `$INSTANCE_NAME`_CH23))
#define `$INSTANCE_NAME`_CH23_SMPL_TIME     ((uint32_t)(`$Ch23SamplingTime`UL << `$INSTANCE_NAME`_CH23))
#else
#define `$INSTANCE_NAME`_CH23_MSK           0UL
#define `$INSTANCE_NAME`_CH23_SMPL_TIME     0UL
#endif /* `$INSTANCE_NAME`_CH_NR > 23u */

#define `$INSTANCE_NAME`_ADC_ACTIVE_CHANNELS ( \
    `$INSTANCE_NAME`_CH0_MSK  | `$INSTANCE_NAME`_CH1_MSK  | `$INSTANCE_NAME`_CH2_MSK  | `$INSTANCE_NAME`_CH3_MSK  | \
    `$INSTANCE_NAME`_CH4_MSK  | `$INSTANCE_NAME`_CH5_MSK  | `$INSTANCE_NAME`_CH6_MSK  | `$INSTANCE_NAME`_CH7_MSK  | \
    `$INSTANCE_NAME`_CH8_MSK  | `$INSTANCE_NAME`_CH9_MSK  | `$INSTANCE_NAME`_CH10_MSK | `$INSTANCE_NAME`_CH11_MSK | \
    `$INSTANCE_NAME`_CH12_MSK | `$INSTANCE_NAME`_CH13_MSK | `$INSTANCE_NAME`_CH14_MSK | `$INSTANCE_NAME`_CH15_MSK | \
    `$INSTANCE_NAME`_CH16_MSK | `$INSTANCE_NAME`_CH17_MSK | `$INSTANCE_NAME`_CH18_MSK | `$INSTANCE_NAME`_CH19_MSK | \
    `$INSTANCE_NAME`_CH20_MSK | `$INSTANCE_NAME`_CH21_MSK | `$INSTANCE_NAME`_CH22_MSK | `$INSTANCE_NAME`_CH23_MSK)

#define `$INSTANCE_NAME`_ADC_SAMPLING_TIME_SELECT ( \
    `$INSTANCE_NAME`_CH0_SMPL_TIME  | `$INSTANCE_NAME`_CH1_SMPL_TIME  | `$INSTANCE_NAME`_CH2_SMPL_TIME  | `$INSTANCE_NAME`_CH3_SMPL_TIME  | \
    `$INSTANCE_NAME`_CH4_SMPL_TIME  | `$INSTANCE_NAME`_CH5_SMPL_TIME  | `$INSTANCE_NAME`_CH6_SMPL_TIME  | `$INSTANCE_NAME`_CH7_SMPL_TIME  | \
    `$INSTANCE_NAME`_CH8_SMPL_TIME  | `$INSTANCE_NAME`_CH9_SMPL_TIME  | `$INSTANCE_NAME`_CH10_SMPL_TIME | `$INSTANCE_NAME`_CH11_SMPL_TIME | \
    `$INSTANCE_NAME`_CH12_SMPL_TIME | `$INSTANCE_NAME`_CH13_SMPL_TIME | `$INSTANCE_NAME`_CH14_SMPL_TIME | `$INSTANCE_NAME`_CH15_SMPL_TIME | \
    `$INSTANCE_NAME`_CH16_SMPL_TIME | `$INSTANCE_NAME`_CH17_SMPL_TIME | `$INSTANCE_NAME`_CH18_SMPL_TIME | `$INSTANCE_NAME`_CH19_SMPL_TIME | \
    `$INSTANCE_NAME`_CH20_SMPL_TIME | `$INSTANCE_NAME`_CH21_SMPL_TIME | `$INSTANCE_NAME`_CH22_SMPL_TIME | `$INSTANCE_NAME`_CH23_SMPL_TIME)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
