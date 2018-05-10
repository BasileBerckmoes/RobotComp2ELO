/*******************************************************************************
* \file `$INSTANCE_NAME`_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable definitions for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_config.h"     

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const" : ""` stc_adc_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bScanIrq */                      `=$bScanIrq ? "TRUE" : "FALSE"`,
    /* bPrioIrq */                      `=$bPrioIrq ? "TRUE" : "FALSE"`,
    /* bFifoOverrunIrq */               `=$bFifoOverrunIrq ? "TRUE" : "FALSE"`,
    /* bComparisonIrq */                `=$bComparisonIrq ? "TRUE" : "FALSE"`,
#if (PDL_MCU_CORE == PDL_FM4_CORE) || (PDL_MCU_CORE == PDL_FM0P_CORE)       
    /* bRangeComparisonIrq */           `=$bRangeComparisonIrq ? "TRUE" : "FALSE"`
#endif
};

/* Interrupt callback function */
`=$CY_CONST_CONFIG ? "const" : ""` stc_adc_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnScanIrqCb */                  `=($pfnScanIrqCb eq "") || !$bScanIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnScanIrqCb`, /* User-supplied callback function */
    /* pfnPrioIrqCb */                  `=($pfnPrioIrqCb eq "") || !$bPrioIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPrioIrqCb`, /* User-supplied callback function */
    /* pfnScanErrIrqCb */               `=($pfnScanErrIrqCb eq "") || !$bFifoOverrunIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnScanErrIrqCb`, /* User-supplied callback function */
    /* pfnPrioErrIrqCb */               `=($pfnPrioErrIrqCb eq "") || !$bFifoOverrunIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPrioErrIrqCb`, /* User-supplied callback function */
    /* pfnComparisonIrqCb */            `=($pfnComparisonIrqCb eq "") || !$bComparisonIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnComparisonIrqCb`, /* User-supplied callback function */
#if (PDL_MCU_CORE == PDL_FM4_CORE) || (PDL_MCU_CORE == PDL_FM0P_CORE)     
    /* pfnRangeComparisonIrqCb */       `=($pfnRangeComparisonIrqCb eq "") || !$bRangeComparisonIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRangeComparisonIrqCb` /* User-supplied callback function */
#endif
};

/* Scan conversion configuration */
`=$CY_CONST_CONFIG ? "const" : ""` stc_adc_scan_t `$INSTANCE_NAME`_Scan =
{
    /* enScanMode */                    `=GetNameForEnum("en_adc_scan_mode_t", $enScanMode)`,
    /* u32ScanCannelSelect */           {{`$INSTANCE_NAME`_ADC_ACTIVE_CHANNELS}},
    /* bScanTimerStartEnable */         `=$scanTriggerSource == None ? "FALSE" : "TRUE"`,
    /* enScanTimerTrigger */            `=$scanTriggerSource == None ? "AdcNoTimer" : $scanTriggerSource == MFT ? "AdcMft" : GetNameForEnum("en_adc_timer_select_t", LookupFitterDefine($ScanBaseTimerHw) + 2)`,
    /* u8ScanFifoDepth */               `$u8ScanFifoDepth`U
};

/* Priority conversion configuration */
`=$CY_CONST_CONFIG ? "const" : ""` stc_adc_prio_t `$INSTANCE_NAME`_Prio =
{
    /* bPrioExtTrigStartEnable */       `=$bPrioExtTrigStartEnable ? "TRUE" : "FALSE"`,
    /* bPrioTimerStartEnable */         `=$prioTriggerSource == None ? "FALSE" : "TRUE"`,
    /* enPrioTimerTrigger */            `=$prioTriggerSource == None ? "AdcNoTimer" : $prioTriggerSource == MFT ? "AdcMft" : GetNameForEnum("en_adc_timer_select_t", LookupFitterDefine($PrioBaseTimerHw) + 2)`,
    /* u8PrioFifoDepth */               `$u8PrioFifoDepth`U,
    /* u8PrioLevel1AnalogChSel */       `=$bPrioExtTrigStartEnable ? "`$Prio1LogicalChannel`" : "0U"`,
    /* u8PrioLevel2AnalogChSel */       `$Prio2LogicalChannel`
};

/* Comparison configuration */
`=$CY_CONST_CONFIG ? "const" : ""` stc_adc_compare_t `$INSTANCE_NAME`_Compare =
{
    /* u16CompareValue */               `$u16CompareValue`U,
    /* bCompareAllChannels */           `=$bCompareAllChannels ? "TRUE" : "FALSE"`,
    /* u8CompareChannel */              `$u8CompareChannel`U,
    /* bCompIrqEqualGreater */          `=$bCompIrqEqualGreater ? "TRUE" : "FALSE"`
};

/* Range comparison configuration */
`=$CY_CONST_CONFIG ? "const" : ""` stc_adc_range_compare_t `$INSTANCE_NAME`_Range =
{
    /* u16UpperLimitRangeValue */       `$u16UpperLimitRangeValue`U,
    /* u16LowerLimitRangeValue */       `$u16LowerLimitRangeValue`U,
    /* u8RangeCountValue */             `$u8RangeCountValue`U,
    /* bWithinRange */                  `=$bWithinRange ? "TRUE" : "FALSE"`,
    /* bRangeCompareAllChannels */      `=$bRangeCompareAllChannels ? "TRUE" : "FALSE"`,
    /* u8RangeCompareChannel */         `$logicalRangeCompareChannel`U
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const" : ""` stc_adc_config_t `$INSTANCE_NAME`_Config =
{
    /* bLsbAlignment */                 `=$bLsbAlignment ? "TRUE" : "FALSE"`,
    /* u32SamplingTimeSelect */         {{`$INSTANCE_NAME`_ADC_SAMPLING_TIME_SELECT}},
    /* enSamplingTimeN0 */              `=GetNameForEnum("en_adc_sample_time_t", $enSamplingTimeN0)`,
    /* u8SamplingTime0 */               `$u8SamplingTime0`U,
    /* enSamplingTimeN1 */              `=GetNameForEnum("en_adc_sample_time_t", $enSamplingTimeN1)`,
    /* u8SamplingTime1 */               `$u8SamplingTime1`U,
    /* u8ComparingClockDiv */           `=($u8ComparingClockDiv == 1) ? 0x80 : ($u8ComparingClockDiv - 2)`,
    /* u8EnableTime */                  `$u8EnableTime`U,
    /* pstcScanInit */                  `=$CY_CONST_CONFIG ? "(stc_adc_scan_t *)" : ""`&`$INSTANCE_NAME`_Scan,
    /* pstcPrioInit */                  `=$CY_CONST_CONFIG ? "(stc_adc_prio_t *)" : ""`&`$INSTANCE_NAME`_Prio,
    /* pstcComparisonInit */            `=$CY_CONST_CONFIG ? "(stc_adc_compare_t *)" : ""`&`$INSTANCE_NAME`_Compare,
#if (PDL_MCU_CORE == PDL_FM4_CORE) || (PDL_MCU_CORE == PDL_FM0P_CORE)
    /* pstcRangeComparisonInit */       `=$CY_CONST_CONFIG ? "(stc_adc_range_compare_t *)" : ""`&`$INSTANCE_NAME`_Range,
#endif
    /* pstcIrqEn */                     `=$CY_CONST_CONFIG ? "(stc_adc_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */                     `=$CY_CONST_CONFIG ? "(stc_adc_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */                    `=$bTouchNvic ? "TRUE" : "FALSE"`
} ;


/* [] END OF FILE */
