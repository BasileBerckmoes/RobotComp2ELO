/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the CapSense TMG
*  component.
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_CAPSENSE_TMG_`$INSTANCE_NAME`_H
#define CY_CAPSENSE_TMG_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Gesture IP block structures
***************************************/
typedef struct
{
    /* Parameters */
    volatile uint8 size;
    volatile uint8 panActiveDistanceX;
    volatile uint8 panActiveDistanceY;
    volatile uint8 zoomActiveDistanceX;
    volatile uint8 zoomActiveDistanceY;
    volatile uint8 flickActiveDistanceX;
    volatile uint8 flickActiveDistanceY;
    volatile uint8 stScrollThreshold1X;
    volatile uint8 stScrollThreshold2X;
    volatile uint8 stScrollThreshold3X;
    volatile uint8 stScrollThreshold4X;
    volatile uint8 stScrollThreshold1Y;
    volatile uint8 stScrollThreshold2Y;
    volatile uint8 stScrollThreshold3Y;
    volatile uint8 stScrollThreshold4Y;
    volatile uint8 stScrollStep1;
    volatile uint8 stScrollStep2;
    volatile uint8 stScrollStep3;
    volatile uint8 stScrollStep4;
    volatile uint8 stScrollDebounce;
    volatile uint8 dtScrollThreshold1X;
    volatile uint8 dtScrollThreshold2X;
    volatile uint8 dtScrollThreshold3X;
    volatile uint8 dtScrollThreshold4X;
    volatile uint8 dtScrollThreshold1Y;
    volatile uint8 dtScrollThreshold2Y;
    volatile uint8 dtScrollThreshold3Y;
    volatile uint8 dtScrollThreshold4Y;
    volatile uint8 dtScrollStep1;
    volatile uint8 dtScrollStep2;
    volatile uint8 dtScrollStep3;
    volatile uint8 dtScrollStep4;
    volatile uint8 dtScrollDebounce;
    volatile uint8 dtScrollToZoomDebounce;
    volatile uint8 stInScrActiveDistanceX;
    volatile uint8 stInScrActiveDistanceY;
    volatile uint8 stInScrCountLevel;
    volatile uint8 dtInScrActiveDistanceX;
    volatile uint8 dtInScrActiveDistanceY;
    volatile uint8 dtInScrCountLevel;
    volatile uint8 edgeSwipeActiveDistance;
    volatile uint8 topAngleThreshold;
    volatile uint8 bottomAngleThreshold;
    volatile uint8 widthOfDisambiguation;
    volatile uint8 STPanDebounce;
    volatile uint8 DTPanDebounce;
    volatile uint8 DTZoomDebounce;
    volatile uint8 DTPanToZoomDebounce;
    volatile uint8 rotateDebounce;
    volatile uint8 completedDebounce;
    volatile uint8 doubleClickRadius;
    volatile uint8 clickRadiusX;
    volatile uint8 clickRadiusY;
    volatile uint16 settlingTimeout;
    volatile uint16 resolutionX;
    volatile uint16 resolutionY;
    volatile uint16 flickSampleTime;
    volatile uint16 edgeSwipeTimeout;
    volatile uint16 DTClickTimeoutMax;
    volatile uint16 DTClickTimeoutMin;
    volatile uint16 STClickTimeoutMax;
    volatile uint16 STClickTimeoutMin;
    volatile uint16 STDoubleClickTimeoutMax;
    volatile uint16 STDoubleClickTimeoutMin;

    /* Masks */
    volatile uint8 groupMask;
    volatile uint8 group1Start;
    volatile uint8 group1End;
    volatile uint8 group2Start;
    volatile uint8 group2End;
    volatile uint8 group3Start;
    volatile uint8 group3End;
    volatile uint8 group4Start;
    volatile uint8 group4End;
} `$INSTANCE_NAME`_CONFIG_STRUCT;


/* Touch position type */
typedef struct {
    uint16 x;
    uint16 y;
} `$INSTANCE_NAME`_POSITION_STRUCT;

/* Ballistics Multiplier external structure */
typedef struct
{
    uint8  touchNumber;            /* Number of detected fingers (0, 1 or 2). */
    uint8  accelLevel;             /* Acceleration Level */
    uint8  speedLevel;             /* Speed Level */
    uint8  divisorValue;           /* Divisor Value */
    uint8  speedThresholdX;        /* Speed Threshold X */
    uint8  speedThresholdY;        /* Speed Threshold Y */
}`$INSTANCE_NAME`_BALLISTIC_MULT;

/* Ballistics Multiplier library structure */
typedef struct
{
    `$INSTANCE_NAME`_BALLISTIC_MULT paramStr;
    uint32 currentTimestamp;       /* Current timestamp */
}`$INSTANCE_NAME`_BALLISTIC_MULT_INT;


/***************************************
*        Component constants
***************************************/
#define `$INSTANCE_NAME`_CONFIG_DEFAULT_VALUES \
{ \
    /* Parameters */ \
    sizeof(`$INSTANCE_NAME`_CONFIG_STRUCT), \
    `$Gestures_PanActiveDistanceThresholdX`u,    /* .panActiveDistanceX */ \
    `$Gestures_PanActiveDistanceThresholdY`u,    /* .panActiveDistanceY */ \
    `$Gestures_ZoomActiveDistanceThresholdX`u,    /* .zoomActiveDistanceX */ \
    `$Gestures_ZoomActiveDistanceThresholdY`u,    /* .zoomActiveDistanceY */ \
    `$Gestures_FlickActiveDistanceThresholdX`u,    /* .flickActiveDistanceX */ \
    `$Gestures_FlickActiveDistanceThresholdY`u,    /* .flickActiveDistanceY */ \
    `$Gestures_stScrollThreshold1X`u,    /* .stScrollThreshold1X */ \
    `$Gestures_stScrollThreshold2X`u,    /* .stScrollThreshold2X */ \
    `$Gestures_stScrollThreshold3X`u,    /* .stScrollThreshold3X */ \
    `$Gestures_stScrollThreshold4X`u,    /* .stScrollThreshold4X */ \
    `$Gestures_stScrollThreshold1Y`u,    /* .stScrollThreshold1Y */ \
    `$Gestures_stScrollThreshold2Y`u,    /* .stScrollThreshold2Y */ \
    `$Gestures_stScrollThreshold3Y`u,    /* .stScrollThreshold3Y */ \
    `$Gestures_stScrollThreshold4Y`u,    /* .stScrollThreshold4Y */ \
    `$Gestures_stScrollStep1`u,     /* .stScrollStep1 */ \
    `$Gestures_stScrollStep2`u,     /* .stScrollStep2 */ \
    `$Gestures_stScrollStep3`u,     /* .stScrollStep3 */ \
    `$Gestures_stScrollStep4`u,     /* .stScrollStep4 */ \
    `$Gestures_stScrollDebounce`u,     /* .stScrollDebounce */ \
    `$Gestures_dtScrollThreshold1X`u,    /* .dtScrollThreshold1X */ \
    `$Gestures_dtScrollThreshold2X`u,    /* .dtScrollThreshold2X */ \
    `$Gestures_dtScrollThreshold3X`u,    /* .dtScrollThreshold3X */ \
    `$Gestures_dtScrollThreshold4X`u,    /* .dtScrollThreshold4X */ \
    `$Gestures_dtScrollThreshold1Y`u,    /* .dtScrollThreshold1Y */ \
    `$Gestures_dtScrollThreshold2Y`u,    /* .dtScrollThreshold2Y */ \
    `$Gestures_dtScrollThreshold3Y`u,    /* .dtScrollThreshold3Y */ \
    `$Gestures_dtScrollThreshold4Y`u,    /* .dtScrollThreshold4Y */ \
    `$Gestures_dtScrollStep1`u,     /* .dtScrollStep1 */ \
    `$Gestures_dtScrollStep2`u,     /* .dtScrollStep2 */ \
    `$Gestures_dtScrollStep3`u,     /* .dtScrollStep3 */ \
    `$Gestures_dtScrollStep4`u,     /* .dtScrollStep4 */ \
    `$Gestures_dtScrollDebounce`u,     /* .dtScrollDebounce */ \
    `$Gestures_dtScrollToZoomDebounce`u,    /* .dtScrollToZoomDebounce*/ \
    `$Gestures_stInertialScrollActiveDistanceThresholdX`u,    /* .stInScrActiveDistanceX */ \
    `$Gestures_stInertialScrollActiveDistanceThresholdY`u,    /* .stInScrActiveDistanceY */ \
    `$Gestures_stInertialScrollCountLevel`u,     /* .stInScrCountLevel */ \
    `$Gestures_dtInertialScrollActiveDistanceThresholdX`u,    /* .dtInScrActiveDistanceX */ \
    `$Gestures_dtInertialScrollActiveDistanceThresholdY`u,    /* .dtInScrActiveDistanceY */ \
    `$Gestures_dtInertialScrollCountLevel`u,     /* .dtInScrCountLevel */ \
    `$Gestures_EdgeSwipeActiveDistance`u,   /* .edgeSwipeActiveDistance */ \
    `$Gestures_TopAngleThreshold`u,    /* .topAngleThreshold*/ \
    `$Gestures_BottomAngleThreshold`u,    /* .bottomAngleThreshold*/ \
    `$Gestures_WidthOfDisambiguationRegion`u,   /* .widthOfDisambiguation */ \
    `$Gestures_DebouncePanCount`u,     /* .STPanDebounce */ \
    `$Gestures_DebounceScrollCount`u,     /* .ScrollDebounce */ \
    `$Gestures_DebounceZoomCount`u,     /* .DTZoomDebounce */ \
    `$Gestures_DebounceScrollToZoomCount`u,    /* .DTScrollToZoomDebounce */ \
    `$Gestures_RotateDebounceLimit`u,    /* .rotateDebounce */ \
    `$Gestures_CompletedDebounce`u,     /* .completedDebounce */ \
    `$Gestures_DoubleClickMaxRadius`u,    /* .doubleClickRadius */ \
    `$Gestures_ClickXRadiusPixels`u,    /* .clickRadiusX */ \
    `$Gestures_ClickYRadiusPixels`u,    /* .clickRadiusY */ \
    `$Gestures_SettlingTimeout`u,    /* .settlingTimeout */ \
    `$Gesture_ResolutionX`u,  /* .resolutionX */ \
    `$Gesture_ResolutionY`u,  /* .resolutionY */ \
    `$Gestures_FlickSampleTime`u,    /* .flickSampleTime */ \
    `$Gestures_EdgeSwipeTime`u,   /* .edgeSwipeTimeout */ \
    `$Gestures_TwoFingerClickMaxTimeout`u,   /* .DTClickTimeoutMax */ \
    `$Gestures_TwoFingerClickMinTimeout`u,    /* .DTClickTimeoutMin */ \
    `$Gestures_SingleClickMaxTimeout`u,   /* .STClickTimeoutMax */ \
    `$Gestures_SingleClickMinTimeout`u,    /* .STClickTimeoutMin */ \
    `$Gestures_DoubleClickMaxTimeout`u,   /* .STDoubleClickTimeoutMax */ \
    `$Gestures_DoubleClickMinTimeout`u,   /* .STDoubleClickTimeoutMin */ \
 \
    /* Masks */ \
    240u,   /* .groupMask */ \
    40u,    /* .group1Start */ \
    41u,    /* .group1End */ \
    48u,    /* .group2Start */ \
    63u,    /* .group2End */ \
    72u,    /* .group3Start */ \
    73u,    /* .group3End */ \
    144u,   /* .group4Start */ \
    159u    /* .group4End */ \
}


#define `$INSTANCE_NAME`_CLICKS_ENABLED                 (`$ClickGesturesEnable`u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_ENABLED             (`$EdgeSwipeGestureEnable`u)
#define `$INSTANCE_NAME`_FLICKS_ENABLED                 (`$FlickGesturesEnable`u)
#define `$INSTANCE_NAME`_ST_SCROLLS_ENABLED             (`$STScrollGesturesEnable`u)
#define `$INSTANCE_NAME`_ROTATE_ENABLED                 (`$RotateGesturesEnable`u)
#define `$INSTANCE_NAME`_DT_SCROLLS_ENABLED             (`$DTScrollGesturesEnable`u)
#define `$INSTANCE_NAME`_ZOOM_ENABLED                   (`$ZoomGesturesEnable`u)
#define `$INSTANCE_NAME`_BALLISTICS_ENABLED             (`$BallisticsEnable`u)

#define `$INSTANCE_NAME`_ROTATE_TO_OTHER_DEBOUNCE       (10u)


/***************************************
*        Function Prototypes
***************************************/
cystatus `$INSTANCE_NAME`_TimerEnableInt(void);
void     `$INSTANCE_NAME`_TimerDisableInt(void);
uint32   `$INSTANCE_NAME`_DecodeAllGestures(uint32 touchNumber, const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
void     `$INSTANCE_NAME`_BallisticsMultiplier(const `$INSTANCE_NAME`_BALLISTIC_MULT * ballisticMultiplier, int16 *pos);

extern uint32 `$INSTANCE_NAME`_currentTimestamp;


/***************************************
*        External API
***************************************/
extern void Gesture_Init(const `$INSTANCE_NAME`_CONFIG_STRUCT *config);
extern uint32 Gesture_GetSettlingStartTime(void);
extern uint16 Gesture_GetTouchDuration(void);

#if ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u))
    extern uint8 Gesture_DecodeAllClickGestures(uint8 touchNumber, uint32 currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
    extern uint16 Gesture_GetInterClickDuration(void);
#endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)) */

#if (`$INSTANCE_NAME`_ZOOM_ENABLED == 1u)
    extern uint8 Gesture_DecodeDTZoomGestures(uint8 touchNumber, uint32 currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_ZOOM_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u)
    extern uint8 Gesture_DecodeDTScrollGestures(uint8 touchNumber, uint32 currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)
    extern uint8 Gesture_DecodeSTScrollGestures(uint8 touchNumber, uint32 currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u)
    extern uint8 Gesture_DecodeFlickGestures(uint8 touchNumber, uint32 currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u) */

#if ((`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) && (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u))
    /*******************************************************************************
    *  If you see this error, it means that you have both Flick gestures and
    *  ST_Scroll gestures enabled. To make the component work, disable
    *  either the Flick or ST_Scroll gestures in the component customizer.
    *  For more information refer to the component datasheet.
    *******************************************************************************/
    #error "Flick and ST Scroll gestures can not be enabled simultaneously!"

#endif /* ((`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) && (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u)) */

#if (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)
    extern uint8 Gesture_DecodeSTRotateGestures(uint8 touchNumber, uint32 currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
    extern uint8 Gesture_DecodeEdgeSwipeGestures(uint8 touchNumber, uint32 currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u)
    extern void BallisticMultiplier_TMG_v1_00(`$INSTANCE_NAME`_BALLISTIC_MULT_INT * ballisticMultiplier, int16 *pos);
#endif /* (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u) */

#if ((`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) || (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u))
    extern uint8 Gesture_GetScrollCnt(void);
#endif /* ((`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) || (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u)) */


/***************************************
*        Defines for Gesture Codes
***************************************/
/* Code for no gesture detected case */
#define `$INSTANCE_NAME`_NO_GESTURE                          (0x00u)

/* Single touch click gestures */
#define `$INSTANCE_NAME`_ST_CLICK                            (0x20u)
#define `$INSTANCE_NAME`_ST_DOUBLECLICK                      (0x22u)
#define `$INSTANCE_NAME`_CLICK_AND_DRAG                      (0x24u)

/* Rotate gestures */
#define `$INSTANCE_NAME`_ROTATE_CW                           (0x28u)
#define `$INSTANCE_NAME`_ROTATE_CCW                          (0x29u)

/* TouchDown and Lift Off Gestures */
#define `$INSTANCE_NAME`_TOUCHDOWN                           (0x2Fu)
#define `$INSTANCE_NAME`_LIFT_OFF                            (0x4Fu)

/* Scroll gestures */
#define `$INSTANCE_NAME`_INERTIAL_ST_SCROLL_VERTICAL_UP      (0xB0u)
#define `$INSTANCE_NAME`_INERTIAL_ST_SCROLL_VERTICAL_DOWN    (0xB2u)
#define `$INSTANCE_NAME`_INERTIAL_ST_SCROLL_HORIZONTAL_LEFT  (0xB4u)
#define `$INSTANCE_NAME`_INERTIAL_ST_SCROLL_HORIZONTAL_RIGHT (0xB6u)

#define `$INSTANCE_NAME`_INERTIAL_DT_SCROLL_VERTICAL_UP      (0xB8u)
#define `$INSTANCE_NAME`_INERTIAL_DT_SCROLL_VERTICAL_DOWN    (0xBAu)
#define `$INSTANCE_NAME`_INERTIAL_DT_SCROLL_HORIZONTAL_LEFT  (0xBCu)
#define `$INSTANCE_NAME`_INERTIAL_DT_SCROLL_HORIZONTAL_RIGHT (0xBEu)

#define `$INSTANCE_NAME`_ST_SCROLL_VERTICAL_UP               (0xC0u)
#define `$INSTANCE_NAME`_ST_SCROLL_VERTICAL_DOWN             (0xC2u)
#define `$INSTANCE_NAME`_ST_SCROLL_HORIZONTAL_LEFT           (0xC4u)
#define `$INSTANCE_NAME`_ST_SCROLL_HORIZONTAL_RIGHT          (0xC6u)

#define `$INSTANCE_NAME`_DT_SCROLL_VERTICAL_UP               (0xC8u)
#define `$INSTANCE_NAME`_DT_SCROLL_VERTICAL_DOWN             (0xCAu)
#define `$INSTANCE_NAME`_DT_SCROLL_HORIZONTAL_LEFT           (0xCCu)
#define `$INSTANCE_NAME`_DT_SCROLL_HORIZONTAL_RIGHT          (0xCEu)

/* Dual touch click gesture */
#define `$INSTANCE_NAME`_DT_CLICK                            (0x40u)

/* Zoom Gestures */
#define `$INSTANCE_NAME`_ZOOM_IN                             (0x48u)
#define `$INSTANCE_NAME`_ZOOM_OUT                            (0x49u)

/* Flick gestures */
#define `$INSTANCE_NAME`_FLICK_NORTH                         (0x50u)
#define `$INSTANCE_NAME`_FLICK_NORTH_EAST                    (0x52u)
#define `$INSTANCE_NAME`_FLICK_EAST                          (0x54u)
#define `$INSTANCE_NAME`_FLICK_SOUTH_EAST                    (0x56u)
#define `$INSTANCE_NAME`_FLICK_SOUTH                         (0x58u)
#define `$INSTANCE_NAME`_FLICK_SOUTH_WEST                    (0x5Au)
#define `$INSTANCE_NAME`_FLICK_WEST                          (0x5Cu)
#define `$INSTANCE_NAME`_FLICK_NORTH_WEST                    (0x5Eu)

/* Edge swipe gestures */
#define `$INSTANCE_NAME`_EDGE_SWIPE_LEFT                    (0xA0u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_RIGHT                   (0xA2u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_TOP                     (0xA4u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_BOTTOM                  (0xA6u)

#define `$INSTANCE_NAME`_EDGE_SWIPE_COMPLETE_TIMEOUT        (`$Gestures_EdgeSwipeCompleteTimeout`u)

/* Invalid coordinates */
#define `$INSTANCE_NAME`_INVALID_COORDINATE                 (0xFFFFu)




/***************************************
*        Component macro definitions
***************************************/


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_InitGestures
********************************************************************************
*
* Summary:
*  This routine initializes gesture parameters internal to the gesture
*  algorithm. It has to be called once in the 'main ()' function before calling
*  any API or macro which decodes gestures.
*
* Parameters:
*  config: pointer to structure with configuration for Gesture IP block
*
* Return:
*  None
*
*******************************************************************************/
#define `$INSTANCE_NAME`_InitGestures(config) (Gesture_Init(config))


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_DecodeClickGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures listed under the Clicks section of Gestures and
*  returns the gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior calling this or any other API or macro
*  for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32 - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeClickGestures(touchNumber,pos) ((uint32)Gesture_DecodeAllClickGestures( \
                        (uint8)(touchNumber), (`$INSTANCE_NAME`_currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeClickGestures(touchNumber,pos) (`$INSTANCE_NAME`_NO_GESTURE)
#endif /* (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_DecodeZoomGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures listed under the Zoom in/out section of Gestures
*  and returns the gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior using this or any other API or macro for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32 - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ZOOM_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeZoomGestures(touchNumber,pos) ((uint32)Gesture_DecodeDTZoomGestures( \
                        (uint8)(touchNumber), (`$INSTANCE_NAME`_currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeZoomGestures(touchNumber,pos) (`$INSTANCE_NAME`_NO_GESTURE)
#endif /* (`$INSTANCE_NAME`_ZOOM_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_DecodeDTScrollGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures listed under the DT Scrolls section of Gestures
*  and returns the gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior using this or any other API or macro for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32 - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber,pos) ((uint32)Gesture_DecodeDTScrollGestures( \
                        (uint8)(touchNumber), (`$INSTANCE_NAME`_currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber,pos) (`$INSTANCE_NAME`_NO_GESTURE)
#endif /* (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_DecodeFlickGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures listed under the Flicks section of Gestures and
*  returns the gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior using this or any other API or macro for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32 - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeFlickGestures(touchNumber,pos) ((uint32)Gesture_DecodeFlickGestures( \
                        (uint8)(touchNumber), (`$INSTANCE_NAME`_currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeFlickGestures(touchNumber,pos) (`$INSTANCE_NAME`_NO_GESTURE)
#endif /* (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_DecodeSTScrollGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures listed under the ST Scroll section of Gestures
*  and returns the gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior using this or any other API or macro for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32 - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeSTScrollGestures(touchNumber,pos) ((uint32)Gesture_DecodeSTScrollGestures( \
                        (uint8)(touchNumber), (`$INSTANCE_NAME`_currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeSTScrollGestures(touchNumber,pos) (`$INSTANCE_NAME`_NO_GESTURE)
#endif /* (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_DecodeRotateGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures listed under the Rotate section of Gestures and
*  returns the gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior using this or any other API or macro for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32 - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeRotateGestures(touchNumber,pos) ((uint32)Gesture_DecodeSTRotateGestures( \
                        (uint8)(touchNumber), (`$INSTANCE_NAME`_currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeRotateGestures(touchNumber,pos) (`$INSTANCE_NAME`_NO_GESTURE)
#endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_DecodeEdgeSwipe
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures listed under the Edge swipe section of Gestures
*  and returns the gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior using this or any other API or macro for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32 - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeEdgeSwipe(touchNumber,pos) ((uint32)Gesture_DecodeEdgeSwipeGestures( \
                        (uint8)(touchNumber), (`$INSTANCE_NAME`_currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeEdgeSwipe(touchNumber,pos) (`$INSTANCE_NAME`_NO_GESTURE)
#endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_GetTimerTouchCounter
********************************************************************************
*
* Summary:
*  Returns the Overall time that touch(es) is (are) on the panel. It is equal
*  to a difference between the lift-off time and touch-down time. Its unit
*  is milliseconds.
*
* Parameters:
*  None
*
* Return:
*  uint32 - Time since the fingers are present on the trackpad
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetTimerTouchCounter() ((uint32)Gesture_GetTouchDuration())


#if (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)
    /*******************************************************************************
    * Macro Name: `$INSTANCE_NAME`_GetTimerClickCounter
    ********************************************************************************
    *
    * Summary:
    *  Returns the Gesture_interClickDuration value. This macro is available only
    *  if click gestures are enabled.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint32 - the Gesture_interClickDuration value, which is used for time
    *  stamping and decoding click gestures.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_GetTimerClickCounter() ((uint32) Gesture_GetInterClickDuration())
#endif /* (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) */


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_GetSettlingStartTime
********************************************************************************
*
* Summary:
*  Returns the Gesture_settlingStartTime - timestamp of start settling event.
*
* Parameters:
*  None
*
* Return:
*  uint32 - the timestamp of start settling event.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetSettlingStartTime() (Gesture_GetSettlingStartTime())


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_GetTimerGlobalCounter
********************************************************************************
*
* Summary:
*  Returns the current Timestamp value.
*
* Parameters:
*  None
*
* Return:
*  uint32 - Current Timestamp value.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetTimerGlobalCounter() (`$INSTANCE_NAME`_currentTimestamp)


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_SetTimerGlobalCounter
********************************************************************************
*
* Summary:
*  Sets the CurrentTimestamp value.
*
* Parameters:
*  currentTimestamp: Timestamp value to be set.
*
* Return:
*  None
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetTimerGlobalCounter(currentTimestamp) (`$INSTANCE_NAME`_currentTimestamp = (currentTimestamp))


/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_GetScrollCnt
********************************************************************************
*
* Summary:
*  Returns scroll step value which corresponds to number of scroll gestures
*  detected during one scan.
*
* Parameters:
*  None
*
* Return:
*  uint8 - Returns number of scrolls when finger exceeds Scroll Threshold.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetScrollCnt() (Gesture_GetScrollCnt())

#endif /* CY_CAPSENSE_TMG_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
