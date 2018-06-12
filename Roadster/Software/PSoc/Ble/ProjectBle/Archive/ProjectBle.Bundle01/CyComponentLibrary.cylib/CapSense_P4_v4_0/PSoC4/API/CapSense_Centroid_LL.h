/***************************************************************************//**
* \file `$INSTANCE_NAME`_Centroid_LL.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the function prototypes for the centroid calculation 
*   methods.
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

#if !defined(CY_CAPSENSE_`$INSTANCE_NAME`_CENTROID_LL_H)
#define CY_CAPSENSE_`$INSTANCE_NAME`_CENTROID_LL_H

#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Structure.h"
    
/*******************************************************************************
* Definitions
*******************************************************************************/
    
/* Centroid-related definitions */
#define `$INSTANCE_NAME`_CENTROID_POS_PREV                  (0u) 
#define `$INSTANCE_NAME`_CENTROID_POS                       (1u)
#define `$INSTANCE_NAME`_CENTROID_POS_NEXT                  (2u)
#define `$INSTANCE_NAME`_CENTROID_ROUND_VALUE               (0x7Fu)
#define `$INSTANCE_NAME`_CENTROID_MAXIMUM                   (0xFFu)
#define `$INSTANCE_NAME`_CENTROID_DIPLEX_SECTION_LENGTH     (0x02u)

/*******************************************************************************
* Function Prototypes 
*******************************************************************************/

/*******************************************************************************
* Function Prototypes - internal functions
*******************************************************************************/
/**
* \if SECTION_CAPSENSE_INTERNAL
* \addtogroup group_capsense_internal
* \{
*/

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) || \
     (`$INSTANCE_NAME`_ENABLE  == `$INSTANCE_NAME`_SLIDER_WIDGET_EN))
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_4PTS_LOCAL_MAX_EN)
        uint32 `$INSTANCE_NAME`_DpFindLocalMaxSd4pts(`$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt,
                                                     `$INSTANCE_NAME`_RAM_SNS_STRUCT ptrSns[],
                                                     uint32 snsCount, uint32 fingerThreshold);
    #else
        uint32 `$INSTANCE_NAME`_DpFindLocalMaxSd(`$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns, 
                                                 uint32 snsCount, uint32 fingerThreshold);
    #endif
#endif

#if (0u != `$INSTANCE_NAME`_TOTAL_DIPLEXED_SLIDERS)
    uint32 `$INSTANCE_NAME`_DpFindLocalMaxDiplex(
                    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns, 
                    uint32 snsCount, 
                    uint8 const *diplexTable, 
                    uint32 fingerThreshold);
#endif

#if ((0u != `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
    uint32 `$INSTANCE_NAME`_DpCalcLinearCentroid(uint16 *position, uint32 multiplier, uint32 snsCount);
#endif

#if (0u != `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS)
    uint32 `$INSTANCE_NAME`_DpCalcRadialCentroid(uint16 *position, uint32 multiplier, uint32 snsCount);
#endif

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN)
    void `$INSTANCE_NAME`_DpFindLocalMaxDd(`$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
    void `$INSTANCE_NAME`_DpCalcTouchPadCentroid(`$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
    void `$INSTANCE_NAME`_DpTouchTracking(`$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
    uint32 `$INSTANCE_NAME`_DpFilterTouchRecord(`$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt);
#endif

/** \}
* \endif */

#endif /* End CY_CAPSENSE_`$INSTANCE_NAME`_CENTROID_LL_H */


/* [] END OF FILE */
