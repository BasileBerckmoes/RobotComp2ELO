/***************************************************************************//**
* \file `$INSTANCE_NAME`_Gesture.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the function prototypes for the centroid calculation
*   methods.
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

#if !defined(CY_SENSE_GESTURE_`$INSTANCE_NAME`_H)
#define CY_SENSE_GESTURE_`$INSTANCE_NAME`_H

#include "CyLib.h"
#include "`$INSTANCE_NAME`_TMG.h"
#include "`$INSTANCE_NAME`_Structure.h"


/*******************************************************************************
* Constant definitions
*******************************************************************************/
#define `$INSTANCE_NAME`_SUPPORTED_FINGERS_NUM          (2uL)

#define `$INSTANCE_NAME`_CLICK_EN                       (`$INSTANCE_NAME`_TMG_CLICKS_ENABLED)
#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_EN       (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_ENABLED)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_EN            (`$INSTANCE_NAME`_TMG_FLICKS_ENABLED)
#define `$INSTANCE_NAME`_ONE_FINGER_ROTATE_EN           (`$INSTANCE_NAME`_TMG_ROTATE_ENABLED)
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_EN           (`$INSTANCE_NAME`_TMG_ST_SCROLLS_ENABLED)
#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_EN           (`$INSTANCE_NAME`_TMG_DT_SCROLLS_ENABLED)
#define `$INSTANCE_NAME`_TWO_FINGER_ZOOM_EN             (`$INSTANCE_NAME`_TMG_ZOOM_ENABLED)

#define `$INSTANCE_NAME`_GESTURE_EN                     (`$INSTANCE_NAME`_TMG_GESTURES_ENABLED)
    
/*******************************************************************************
* Types definition
*******************************************************************************/
typedef struct{
    int16 x;
    int16 y;
}`$INSTANCE_NAME`_BALLISTIC_POS_TYPE;

typedef enum
{
    `$INSTANCE_NAME`_TOUCH_VALID = 0x00u,
    `$INSTANCE_NAME`_TOUCH_UNRECOGNIZED = 0x01u,
}`$INSTANCE_NAME`_GESTURE_STATE_ENUM;

typedef struct{
    `$INSTANCE_NAME`_TMG_POSITION_STRUCT currentPosition[`$INSTANCE_NAME`_SUPPORTED_FINGERS_NUM];
    `$INSTANCE_NAME`_GESTURE_STATE_ENUM touchState;
    uint8 touchNumber;
    uint8 maxTouchNumber;
} `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT;

/*******************************************************************************
* Function Prototypes - High-level API
*******************************************************************************/
/**
* \cond SECTION_C_HIGH_LEVEL
* \addtogroup group_c_high_level
* \{
*/

#if (0u != `$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
    uint32 `$INSTANCE_NAME`_DecodeWidgetGestures(uint32 widgetId);
#endif

void `$INSTANCE_NAME`_IncrementGestureTimestamp(void);
void `$INSTANCE_NAME`_SetGestureTimestamp(uint32 timestampValue);

/** \}
* \endcond */

/*******************************************************************************
* Function Prototypes - Internal Functions
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (0u != `$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
    void  `$INSTANCE_NAME`_GetTouchParams(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams);
#endif

void `$INSTANCE_NAME`_InitializeGestures(void);
void `$INSTANCE_NAME`_InitializeBallisticMultiplier(void);
void `$INSTANCE_NAME`_RunBallisticMultiplier(uint32 wdgtIndex);

/** \}
* \endcond */


/*******************************************************************************
* Definitions
*******************************************************************************/
#define `$INSTANCE_NAME`_FIRST_FINGER_ID                        (0uL)
#define `$INSTANCE_NAME`_SECOND_FINGER_ID                       (1uL)
#define `$INSTANCE_NAME`_X_COORDINATE_INDEX                     (0uL)
#define `$INSTANCE_NAME`_Y_COORDINATE_INDEX                     (1uL)
#define `$INSTANCE_NAME`_BALLISTIC_DIMENSIONS_NUM               (2uL)

/* Centroid Errors */
#define `$INSTANCE_NAME`_POSITION_ERROR                         (0xFFFFFFFFu)
#define `$INSTANCE_NAME`_FINGER_ERROR                           (0xFFu)

#define `$INSTANCE_NAME`_GESTURE_GROUP_MASK                     (0xF0u)

/* Code for no gesture detected case */
#define `$INSTANCE_NAME`_NO_GESTURE                             (`$INSTANCE_NAME`_TMG_NO_GESTURE)
#define `$INSTANCE_NAME`_NON_VALID_PARAMETER                    (0xFFu)
#define `$INSTANCE_NAME`_UNRECOGNIZED_GESTURE                   (0xFEu)

/* TouchDown and Lift Off Gestures */
#define `$INSTANCE_NAME`_ONE_FINGER_TOUCHDOWN                   (`$INSTANCE_NAME`_TMG_TOUCHDOWN)
#define `$INSTANCE_NAME`_ONE_FINGER_LIFT_OFF                    (`$INSTANCE_NAME`_TMG_LIFT_OFF)

/* Single touch click gestures */
#define `$INSTANCE_NAME`_ONE_FINGER_SINGLE_CLICK                (`$INSTANCE_NAME`_TMG_ST_CLICK)
#define `$INSTANCE_NAME`_ONE_FINGER_DOUBLE_CLICK                (`$INSTANCE_NAME`_TMG_ST_DOUBLECLICK)
#define `$INSTANCE_NAME`_ONE_FINGER_CLICK_AND_DRAG              (`$INSTANCE_NAME`_TMG_CLICK_AND_DRAG)

/* Rotate gestures */
#define `$INSTANCE_NAME`_ONE_FINGER_ROTATE_CW                   (`$INSTANCE_NAME`_TMG_ROTATE_CW)
#define `$INSTANCE_NAME`_ONE_FINGER_ROTATE_CCW                  (`$INSTANCE_NAME`_TMG_ROTATE_CCW)

/* Scroll gestures */
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_UP          (`$INSTANCE_NAME`_TMG_INERTIAL_ST_SCROLL_VERTICAL_UP)
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_DOWN        (`$INSTANCE_NAME`_TMG_INERTIAL_ST_SCROLL_VERTICAL_DOWN)
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_LEFT        (`$INSTANCE_NAME`_TMG_INERTIAL_ST_SCROLL_HORIZONTAL_LEFT)
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_RIGHT       (`$INSTANCE_NAME`_TMG_INERTIAL_ST_SCROLL_HORIZONTAL_RIGHT)

#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_UP          (`$INSTANCE_NAME`_TMG_INERTIAL_DT_SCROLL_VERTICAL_UP)
#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_DOWN        (`$INSTANCE_NAME`_TMG_INERTIAL_DT_SCROLL_VERTICAL_DOWN)
#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_LEFT        (`$INSTANCE_NAME`_TMG_INERTIAL_DT_SCROLL_HORIZONTAL_LEFT)
#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_RIGHT       (`$INSTANCE_NAME`_TMG_INERTIAL_DT_SCROLL_HORIZONTAL_RIGHT)

#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_UP                   (`$INSTANCE_NAME`_TMG_ST_SCROLL_VERTICAL_UP)
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_DOWN                 (`$INSTANCE_NAME`_TMG_ST_SCROLL_VERTICAL_DOWN)
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_LEFT                 (`$INSTANCE_NAME`_TMG_ST_SCROLL_HORIZONTAL_LEFT)
#define `$INSTANCE_NAME`_ONE_FINGER_SCROLL_RIGHT                (`$INSTANCE_NAME`_TMG_ST_SCROLL_HORIZONTAL_RIGHT)

#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_UP                   (`$INSTANCE_NAME`_TMG_DT_SCROLL_VERTICAL_UP)
#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_DOWN                 (`$INSTANCE_NAME`_TMG_DT_SCROLL_VERTICAL_DOWN)
#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_LEFT                 (`$INSTANCE_NAME`_TMG_DT_SCROLL_HORIZONTAL_LEFT)
#define `$INSTANCE_NAME`_TWO_FINGER_SCROLL_RIGHT                (`$INSTANCE_NAME`_TMG_DT_SCROLL_HORIZONTAL_RIGHT)

/* Dual touch click gesture */
#define `$INSTANCE_NAME`_TWO_FINGER_SINGLE_CLICK                (`$INSTANCE_NAME`_TMG_DT_CLICK)

/* Zoom Gestures */
#define `$INSTANCE_NAME`_TWO_FINGER_ZOOM_IN                     (`$INSTANCE_NAME`_TMG_ZOOM_IN)
#define `$INSTANCE_NAME`_TWO_FINGER_ZOOM_OUT                    (`$INSTANCE_NAME`_TMG_ZOOM_OUT)

/* Flick gestures */
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_UP                    (`$INSTANCE_NAME`_TMG_FLICK_NORTH)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_UP_RIGHT              (`$INSTANCE_NAME`_TMG_FLICK_NORTH_EAST)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_RIGHT                 (`$INSTANCE_NAME`_TMG_FLICK_EAST)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_DOWN_RIGHT            (`$INSTANCE_NAME`_TMG_FLICK_SOUTH_EAST)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_DOWN                  (`$INSTANCE_NAME`_TMG_FLICK_SOUTH)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_DOWN_LEFT             (`$INSTANCE_NAME`_TMG_FLICK_SOUTH_WEST)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_LEFT                  (`$INSTANCE_NAME`_TMG_FLICK_WEST)
#define `$INSTANCE_NAME`_ONE_FINGER_FLICK_UP_LEFT               (`$INSTANCE_NAME`_TMG_FLICK_NORTH_WEST)

/* Edge swipe gestures */
#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_UP               (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_TOP)
#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_DOWN             (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_BOTTOM)
#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_LEFT             (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_LEFT)
#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_RIGTH            (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_RIGHT)
#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_GROUP            (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_LEFT &\
                                                                 `$INSTANCE_NAME`_TMG_EDGE_SWIPE_RIGHT &\
                                                                 `$INSTANCE_NAME`_TMG_EDGE_SWIPE_TOP &\
                                                                 `$INSTANCE_NAME`_TMG_EDGE_SWIPE_BOTTOM)
#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_GESTURE          (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_LEFT |\
                                                                 `$INSTANCE_NAME`_TMG_EDGE_SWIPE_RIGHT |\
                                                                 `$INSTANCE_NAME`_TMG_EDGE_SWIPE_TOP |\
                                                                 `$INSTANCE_NAME`_TMG_EDGE_SWIPE_BOTTOM)

#define `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_COMPLETE_TIMEOUT (`$INSTANCE_NAME`_TMG_EDGE_SWIPE_COMPLETE_TIMEOUT)

/* Invalid coordinates */
#define `$INSTANCE_NAME`_INVALID_COORDINATE                     (`$INSTANCE_NAME`_TMG_INVALID_COORDINATE)


#endif /* CY_SENSE_GESTURE_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
