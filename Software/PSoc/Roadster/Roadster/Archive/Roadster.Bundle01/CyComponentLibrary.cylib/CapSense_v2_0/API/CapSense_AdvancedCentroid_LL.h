/***************************************************************************//**
* \file `$INSTANCE_NAME`_AdvancedCentroid_LL.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides constants and parameter values for the Advanced 
*   Centroid APIs.
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

#if !defined(CY_SENSE_ADVANCEDCENTROID_LL_H)
#define CY_SENSE_ADVANCEDCENTROID_LL_H

#include "syslib/cy_syslib.h"

/*******************************************************************************
* Global definition
*******************************************************************************/
#define ADVANCED_CENTROID_MAX_TOUCHES                       (0x02u)
#define ADVANCED_CENTROID_NO_TOUCHES                        (0x00u)
#define ADVANCED_CENTROID_POSITION_NONE                     (0xFFFFu)
#define ADVANCED_CENTROID_POSITION_ERROR                    (0xFFFFFFFFu)

/*******************************************************************************
* Structures
*******************************************************************************/

/***************************************************************************//**
* \brief Declares Advanced Centroid configuration parameters
*******************************************************************************/
typedef struct
{
    /**
     *  Finger threshold of widget
     */
    uint16 fingerTh;
    /**
     *  Penultimate threshold
     */
    uint16 penultimateTh;
    /**
     *  Virtual sensor threshold
     */
    uint16 virtualSnsTh;
    /**
     *  X axis maximum position
     */
    uint16 resolutionX;
    /**
     *  Y axis maximum position
     */
    uint16 resolutionY;
    /**
     *  Cross-coupling threshold
     */
    uint8 crossCouplingTh;
    /**
     *  Number of segments on X axis
     */
    uint8 snsCountX;
    /**
     *  Number of segments on Y axis
     */
    uint8 snsCountY;
    /**
     *  Edge correction enabled
     */
    uint8 edgeCorrectionEn;
    /**
     *  Two-finger detection enabled
     */
    uint8 twoFingersEn;
} ADVANCED_CENTROID_CONFIG_STRUCT;
    
/**
* \cond SECTION_STRUCTURES
* \addtogroup group_structures
* \{
*/

/***************************************************************************//**
* \brief Declares Advanced Centroid position structure
*******************************************************************************/
typedef struct 
{
    /**
     *  X position 
     */
    uint16 x;                                               
    /**
     *  Y position
     */
    uint16 y;
    /**
     *  Z value of X axis
     */
    uint16 zX;
    /**
     *  Z value of Y axis
     */
    uint16 zY;
} ADVANCED_CENTROID_POSITION_STRUCT;

/***************************************************************************//**
* \brief Declares Advanced Centroid touch structure
*******************************************************************************/
typedef struct
{
    /**
     *  Array of position structure 
     */
    ADVANCED_CENTROID_POSITION_STRUCT pos[ADVANCED_CENTROID_MAX_TOUCHES];   
    /**
     *  Number of touches
     */
    uint8 touchNum;                                         
} ADVANCED_CENTROID_TOUCH_STRUCT;

/** \}
* \endcond */

/***************************************************************************//**
* \brief Declares Advanced Centroid context parameters
*******************************************************************************/
typedef struct
{
    /**
     *  Array of sensor signals arranged X then Y 
     */
    uint16 *ptrSns;                                         
    /**
     *  The pointer to the touch structure 
     */
    ADVANCED_CENTROID_TOUCH_STRUCT *touch;                  
} ADVANCED_CENTROID_CONTEXT_STRUCT;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
uint32 AdvancedCentroid_GetTouchCoordinates(const ADVANCED_CENTROID_CONFIG_STRUCT *config,
                                                  ADVANCED_CENTROID_CONTEXT_STRUCT *context);

#endif /* CY_SENSE_ADVANCEDCENTROID_LL_H */


/* [] END OF FILE */
