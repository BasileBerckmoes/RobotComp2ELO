/***************************************************************************//**
* \file     `$INSTANCE_NAME`_Filter.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief    This file contains the definitions for all firmware filters 
*           implementation.
*
* \see      CapSense P4 v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
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

#if !defined(CY_CAPSENSE_`$INSTANCE_NAME`_FILTER_H)
#define CY_CAPSENSE_`$INSTANCE_NAME`_FILTER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
    
#include "`$INSTANCE_NAME`_Structure.h"    
#include "`$INSTANCE_NAME`_Configuration.h"
    
/***************************************
* Function Prototypes 
***************************************/ 

/*******************************************************************************
* LOW LEVEL API 
*******************************************************************************/
/**
* \if SECTION_CAPSENSE_LOW_LEVEL
* \addtogroup group_capsense_low_level
* \{
*/
    
cystatus `$INSTANCE_NAME`_UpdateAllBaselines(void);
cystatus `$INSTANCE_NAME`_UpdateWidgetBaseline(uint32 widgetId);
cystatus `$INSTANCE_NAME`_UpdateSensorBaseline(uint32 widgetId, uint32 sensorId);

void `$INSTANCE_NAME`_InitializeAllBaselines(void);    
void `$INSTANCE_NAME`_InitializeWidgetBaseline(uint32 widgetId);
void `$INSTANCE_NAME`_InitializeSensorBaseline(uint32 widgetId, uint32 sensorId);

/** \}
* \endif */

/*******************************************************************************
* Function Prototypes - internal functions
*******************************************************************************/
/**
* \if SECTION_CAPSENSE_INTERNAL
* \addtogroup group_capsense_internal
* \{
*/

void `$INSTANCE_NAME`_FtInitialize(void);

#if (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN)
    void `$INSTANCE_NAME`_RunNoiseEnvelope(uint32 widgetId, uint32 sensorId);
    void `$INSTANCE_NAME`_InitializeNoiseEnvelope(uint32 widgetId, uint32 sensorId);
#endif /* #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN */

#if (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN)
    void `$INSTANCE_NAME`_InitializeIIR(uint32 widgetId, uint32 sensorId);
    void `$INSTANCE_NAME`_RunIIR(uint32 widgetId, uint32 sensorId);
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN) */

#if (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
    void `$INSTANCE_NAME`_InitializeMedian(uint32 widgetId, uint32 sensorId);
    void `$INSTANCE_NAME`_RunMedian(uint32 widgetId, uint32 sensorId);
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN) */

#if (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN)
    void `$INSTANCE_NAME`_InitializeAverage(uint32 widgetId, uint32 sensorId);
    void `$INSTANCE_NAME`_RunAverage(uint32 widgetId, uint32 sensorId);
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN) */

void `$INSTANCE_NAME`_FtInitializeBaseline(`$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor, uint32 wdType);
uint32 `$INSTANCE_NAME`_FtUpdateBaseline(
                            `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWidgetRam,
                            `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor, 
                            uint32 wdType);

#if (`$INSTANCE_NAME`_POS_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
uint32 `$INSTANCE_NAME`_FtMedian(uint32 x1, uint32 x2, uint32 x3);
#endif /*`$INSTANCE_NAME`_POS_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN*/

uint32 `$INSTANCE_NAME`_FtIIR1stOrder(uint32 input, uint32 prevOutput, uint32 n, uint32 shift);

#if (`$INSTANCE_NAME`_POS_JITTER_FILTER_EN)
    uint32 `$INSTANCE_NAME`_FtJitter(uint32 input, uint32 prevOutput);
#endif /* `$INSTANCE_NAME`_POS_JITTER_FILTER_EN */

void `$INSTANCE_NAME`_FtInitializeBaselineChannel(`$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor, uint32 wdType, uint32 channel); 

#if (`$INSTANCE_NAME`_REGULAR_RC_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_FILTER_EN)
    void `$INSTANCE_NAME`_FtRunEnabledFilters(uint32 widgetId, uint32 sensorId);
    void `$INSTANCE_NAME`_FtRunEnabledFiltersInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj, 
                                                      `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_FILTER_EN) */


#if (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN)
    void `$INSTANCE_NAME`_InitializeIIRInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                  `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void `$INSTANCE_NAME`_RunIIRInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                           `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN) */

#if (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
    void `$INSTANCE_NAME`_InitializeMedianInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                     `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);    
    void `$INSTANCE_NAME`_RunMedianInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                              `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);    
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN) */

#if (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN)
    void `$INSTANCE_NAME`_InitializeAverageInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                      `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void `$INSTANCE_NAME`_RunAverageInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                               `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ALP_FILTER_EN)
    void `$INSTANCE_NAME`_InitializeALP(uint32 widgetId, uint32 sensorId);
    void `$INSTANCE_NAME`_RunALP(uint32 widgetId, uint32 sensorId);
    void `$INSTANCE_NAME`_InitializeALPInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj,
                                                uint32 wdType);
    void `$INSTANCE_NAME`_ConfigRunALPInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrRamWdgt,
                                        `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj,
                                        uint32 wdType);
    void `$INSTANCE_NAME`_RunALPInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                        ALP_FLTR_CONFIG_STRUCT *ptrAlpFilterConfig,
                                        `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj,
                                        uint32 wdType);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ALP_FILTER_EN) */

/** \}
* \endif */

/***************************************
* Initial Parameter Constants
***************************************/
#define NOISE_ENVELOPE_SHIFT                        (0x02u)
#define NOISE_ENVELOPE_RUN_DIFF_SHIFT               (0x03u)
#define NOISE_ENVELOPE_SIGN_REG                     (0x0Fu)
#define NOISE_ENVELOPE_SIGN_REG_SHIFT               (0x01u)
#define NOISE_ENVELOPE_RESET_COUNTER                (0x0Au)
#define NOISE_ENVELOPE_4_TIMES                      (0x02u)

#endif /* End CY_CAPSENSE_`$INSTANCE_NAME`_FILTER_H */


/* [] END OF FILE */
