/***************************************************************************//**
* \file `$INSTANCE_NAME`_AdaptiveFilter_LL.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the definitions for the Adaptive Filter.
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

#if !defined(CY_SENSE_ADAPTIVEFILTER_LL_H)
#define CY_SENSE_ADAPTIVEFILTER_LL_H

#include "syslib/cy_syslib.h"

/*******************************************************************************
* Public definition
*******************************************************************************/
#define ADAPTIVE_FILTER_POSITION_NONE       (0xFFFFu)

/*******************************************************************************
* Structures
*******************************************************************************/

/**
* \cond SECTION_STRUCTURES
* \addtogroup group_structures
* \{
*/

/***************************************************************************//**
* \brief Declares Adaptive Filter configuration parameters
*******************************************************************************/
typedef struct
{
    /** 
     * Maximum filter coefficient
     */
    uint8 maxK;                             
    /** 
     * Minimum filter coefficient
     */
    uint8 minK;
    /** 
     * No-movement threshold
     */
    uint8 noMovTh;
    /** 
     * Little movement threshold
     */
    uint8 littleMovTh;
    /** 
     * Large movement threshold
     */
    uint8 largeMovTh;
    /** 
     * Divisor value
     */
    uint8 divVal;
} ADAPTIVE_FILTER_CONFIG_STRUCT;

/** \}
* \endcond */

/***************************************************************************//**
* \brief Declares Adaptive Filter context parameters
*******************************************************************************/
typedef struct
{
    /** 
     * Previous X position
     */
    uint16 previousX;
    /** 
     * Previous Y position
     */
    uint16 previousY;
    /** 
     * Current filter coefficient
     */
    uint8 coefficient;
} ADAPTIVE_FILTER_CONTEXT_STRUCT;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void AdaptiveFilter_Initialize(const ADAPTIVE_FILTER_CONFIG_STRUCT *config, ADAPTIVE_FILTER_CONTEXT_STRUCT *context);
void AdaptiveFilter_Run(const ADAPTIVE_FILTER_CONFIG_STRUCT *config, 
                        ADAPTIVE_FILTER_CONTEXT_STRUCT *context, uint16 *currentX, uint16 *currentY);

#endif /* CY_SENSE_ADAPTIVEFILTER_LL_H */


/* [] END OF FILE */
