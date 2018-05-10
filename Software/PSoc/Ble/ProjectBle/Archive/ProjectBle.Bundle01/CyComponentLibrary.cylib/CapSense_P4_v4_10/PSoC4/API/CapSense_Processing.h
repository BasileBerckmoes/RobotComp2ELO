/***************************************************************************//**
* \file `$INSTANCE_NAME`_Processing.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* This file provides the function prototypes for the Data Processing module.
* The Data Processing module is responsible for the low level raw counts
* processing provided by the sensing module, maintaining baseline and 
* difference values and performing high-level widget processing like updating
* button status or calculating slider position.
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

#if !defined(CY_SENSE_`$INSTANCE_NAME`_DATA_PROCESS_H)
#define CY_SENSE_`$INSTANCE_NAME`_DATA_PROCESS_H

#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Structure.h"

#if (0 != (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN))
    #include "`$INSTANCE_NAME`_SmartSense_LL.h"
#endif /* (0 != (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN)) */

/*******************************************************************************
* Definitions
*******************************************************************************/

/* Define the data processing tasks */

/* Applies all enabled filters in the default order to the raw counts */
#define `$INSTANCE_NAME`_PROCESS_FILTER             (0x01Lu)

/* Updates baselines using current raw count values for the widget/sensor */
#define `$INSTANCE_NAME`_PROCESS_BASELINE           (0x02Lu)

/* Calculates differences for the widget/sensor */
#define `$INSTANCE_NAME`_PROCESS_DIFFCOUNTS         (0x04Lu)

/* Runs the noise envelope filter to measure noise magnitude for the widget/sensor */
#define `$INSTANCE_NAME`_PROCESS_CALC_NOISE         (0x08Lu)

/* Updates widget thresholds based on raw counts noise magnitude */
#define `$INSTANCE_NAME`_PROCESS_THRESHOLDS         (0x10Lu)

/* Runs the widget-specific processing algorithms and updates it status */
#define `$INSTANCE_NAME`_PROCESS_STATUS             (0x20Lu)

/* Runs the deconvolution algorithm for the widgets with the multiphase TX scanning */
#define `$INSTANCE_NAME`_PROCESS_DECONVOLUTION      (0x40Lu)

/* Definition that combines all possible processing tasks */
#define `$INSTANCE_NAME`_PROCESS_ALL    (`$INSTANCE_NAME`_PROCESS_FILTER        | \
                                         `$INSTANCE_NAME`_PROCESS_BASELINE      | \
                                         `$INSTANCE_NAME`_PROCESS_DIFFCOUNTS    | \
                                         `$INSTANCE_NAME`_PROCESS_CALC_NOISE    | \
                                         `$INSTANCE_NAME`_PROCESS_THRESHOLDS    | \
                                         `$INSTANCE_NAME`_PROCESS_DECONVOLUTION | \
                                         `$INSTANCE_NAME`_PROCESS_STATUS )

/*******************************************************************************
* Function Prototypes 
*******************************************************************************/

/*******************************************************************************
* Function Prototypes - internal functions.
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

void `$INSTANCE_NAME`_DpInitialize(void);

#if ((0u != `$INSTANCE_NAME`_BUTTON_WIDGET_EN) || (0u != `$INSTANCE_NAME`_CSX_MATRIX_WIDGET_EN))
    uint32 `$INSTANCE_NAME`_DpProcessButton(uint32 currStatus, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if ((0u != `$INSTANCE_NAME`_BUTTON_WIDGET_EN) || (0u != `$INSTANCE_NAME`_CSX_MATRIX_WIDGET_EN)) */

#if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_DpProcessCsxTouchpad(
                uint32 currStatus, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_DpProcessProximity(uint32 currStatus, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_DpProcessSlider(uint32 currStatus, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_DpProcessCsdMatrix(uint32 currStatus, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_DpProcessCsdTouchpad(
                uint32 currStatus, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
    uint32 `$INSTANCE_NAME`_DpProcessCsdWidgetRawCounts(
                    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
    
    uint32 `$INSTANCE_NAME`_DpProcessCsdSensorRawCountsExt(
                    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt, 
                    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns,
                    `$INSTANCE_NAME`_PTR_FILTER_VARIANT fltrHistV, 
                     uint32 mode);
    
    void `$INSTANCE_NAME`_DpProcessCsdWidgetStatus(uint32 widgetId, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

#if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
    uint32 `$INSTANCE_NAME`_DpProcessCsxWidgetRawCounts(
            `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);

    uint32 `$INSTANCE_NAME`_DpProcessCsxSensorRawCountsExt(
                    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt, 
                    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns,
                    `$INSTANCE_NAME`_PTR_FILTER_VARIANT fltrHistV, 
                     uint32 mode);
    
    void `$INSTANCE_NAME`_DpProcessCsxWidgetStatus(
                uint32 widgetId, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */

#if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS)
    uint32 `$INSTANCE_NAME`_DpProcessIsxWidgetRawCounts(
            `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);

    uint32 `$INSTANCE_NAME`_DpProcessIsxSensorRawCountsExt(
                    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt, 
                    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns,
                    `$INSTANCE_NAME`_PTR_FILTER_VARIANT fltrHistV, 
                     uint32 mode);
    
    void `$INSTANCE_NAME`_DpProcessIsxWidgetStatus(
                uint32 wdgtId, `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS) */

void `$INSTANCE_NAME`_DpUpdateDifferences(
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT  *ptrRamWdgt, `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns);

#if (0u != (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN))
    void `$INSTANCE_NAME`_DpUpdateThresholds(
                    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrRamWdgt,
                    SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT *ptrNoiseEnvelope,
                    uint32 startFlag);
#endif /* #if (0u != (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN)) */

#if (0u != `$INSTANCE_NAME`_CSX_MULTIPHASE_TX_EN)
    void `$INSTANCE_NAME`_DpDeconvolution(`$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif /* #if (0u != `$INSTANCE_NAME`_CSX_MULTIPHASE_TX_EN) */


/** \}
* \endcond */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_DATA_PROCESS_H */


/* [] END OF FILE */
