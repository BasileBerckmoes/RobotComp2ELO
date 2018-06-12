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

#include <stdint.h>


/***************************************
*        Gesture IP block structures
***************************************/

/**
* \cond SECTION_STRUCTURES
* \addtogroup group_structures
* \{
*/

/** \brief Gesture configuration structure */
typedef struct
{
    /**
     * The size of the `$INSTANCE_NAME`_CONFIG_STRUCT in bytes.
    */
    volatile uint8_t size;

    /**
     *  Sets the minimum active step distance in the X dimension that has to be exceeded before
     *  a motion is considered active. The distance is measured in the resolution units.
     *  The range is 1 to 255.
    */
    volatile uint8_t panActiveDistanceX;

    /**
     *  Sets the minimum active step distance in the Y dimension that has to be exceeded before
     *  a motion is considered active
    */
    volatile uint8_t panActiveDistanceY;

    /**
     *  This parameter sets the minimum active step distance in the X dimension that has to be
     *  exceeded before a motion is considered an active Zoom (in or out)
    */
    volatile uint8_t zoomActiveDistanceX;

    /**
     *  This parameter sets the minimum active step distance in the Y dimension that has to be
     *  exceeded before a motion is considered an active Zoom (in or out)
    */
    volatile uint8_t zoomActiveDistanceY;

    /**
     *  This parameter sets the minimum active step distance in the X dimension that has to be exceeded
     *  before a motion is considered Flick gesture
    */
    volatile uint8_t flickActiveDistanceX;

    /**
     *  This parameter sets the minimum active step distance in the Y dimension that has to be exceeded
     *  before a motion is considered Flick gesture
    */
    volatile uint8_t flickActiveDistanceY;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to
     *  activate One-finger Scroll gesture
    */
    volatile uint8_t stScrollThreshold1X;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to
     *  activate 1-finger scroll gesture
    */
    volatile uint8_t stScrollThreshold2X;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to
     *  activate One-finger Scroll gesture
    */
    volatile uint8_t stScrollThreshold3X;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to
     *  activate One-finger Scroll gesture
    */
    volatile uint8_t stScrollThreshold4X;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to
     *  activate One-finger Scroll gesture
    */
    volatile uint8_t stScrollThreshold1Y;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to
     *  activate One-finger Scroll gesture
    */
    volatile uint8_t stScrollThreshold2Y;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to
     *  activate One-finger Scroll gesture
    */
    volatile uint8_t stScrollThreshold3Y;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to
     *  activate One-finger Scroll gesture
    */
    volatile uint8_t stScrollThreshold4Y;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance
     *  passed between 2 consecutive scans is:
     *  - (stScrollThreshold1X <= distance < stScrollThreshold2X) - for X-axis;
     *  - (stScrollThreshold1Y <= distance < stScrollThreshold2Y) - for Y-axis;
    */
    volatile uint8_t stScrollStep1;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance
     *  passed between 2 consecutive scans is:
     *  - (stScrollThreshold2X <= distance < stScrollThreshold3X) - for X-axis;
     *  - (stScrollThreshold2Y <= distance < stScrollThreshold3Y) - for Y-axis;
    */
    volatile uint8_t stScrollStep2;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance
     *  passed between 2 consecutive scans is:
     *  - (stScrollThreshold3X <= distance < stScrollThreshold4X) - for X-axis;
     *  - (stScrollThreshold3Y <= distance < stScrollThreshold4Y) - for Y-axis;
    */
    volatile uint8_t stScrollStep3;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance
     *  passed between 2 consecutive scans is:
     *  - (stScrollThreshold4X <= distance) - for X-axis;
     *  - (stScrollThreshold4Y <= distance) - for Y-axis;
    */
    volatile uint8_t stScrollStep4;

    /**
     *  This parameter sets the number of similar, sequential One-finger Scroll gestures that should
     *  be performed before the One-finger Scroll gesture is considered valid. This parameter is for the
     *  One-finger Scroll gestures.
    */
    volatile uint8_t stScrollDebounce;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep1.
    */
    volatile uint8_t dtScrollThreshold1X;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep2.
    */
    volatile uint8_t dtScrollThreshold2X;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep3.
    */
    volatile uint8_t dtScrollThreshold3X;

    /**
     *  This is a distance in the X-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep4.
    */
    volatile uint8_t dtScrollThreshold4X;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep1.
    */
    volatile uint8_t dtScrollThreshold1Y;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep2.
    */
    volatile uint8_t dtScrollThreshold2Y;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep3.
    */
    volatile uint8_t dtScrollThreshold3Y;

    /**
     *  This is a distance in the Y-axis that finger(s) should pass between 2 consecutive scans to activate
     *  Two-finger Scroll gesture. The following number of scrolls will be reported in this case: dtScrollStep4.
    */
    volatile uint8_t dtScrollThreshold4Y;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance passed
     *  between 2 consecutive scans is:
     *  - (dtScrollThreshold1X <= distance < dtScrollThreshold2X) - for X-axis;
     *  - (dtScrollThreshold1Y <= distance < dtScrollThreshold2Y) - for Y-axis;
    */
    volatile uint8_t dtScrollStep1;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance passed
     *  between 2 consecutive scans is:
     *  - (dtScrollThreshold2X <= distance < dtScrollThreshold3X) - for X-axis;
     *  - (dtScrollThreshold2Y <= distance < dtScrollThreshold3Y) - for Y-axis;
    */
    volatile uint8_t dtScrollStep2;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance passed
     *  between 2 consecutive scans is:
     *  - (dtScrollThreshold3X <= distance < dtScrollThreshold4X) - for X-axis;
     *  - (dtScrollThreshold3Y <= distance < dtScrollThreshold4Y) - for Y-axis;
    */
    volatile uint8_t dtScrollStep3;

    /**
     *  This is a number of scrolls that is reported if Scroll gesture is detected and the distance passed
     *  between 2 consecutive scans is:
     *  - (dtScrollThreshold4X <= distance) - for X-axis;
     *  - (dtScrollThreshold4Y <= distance) - for Y-axis;
    */
    volatile uint8_t dtScrollStep4;

    /**
     *  This parameter sets the number of similar, sequential Two-finger Scroll gestures that should be
     *  performed before the Two-finger Scroll gesture is considered valid. This parameter is for the
     *  Two-finger Scroll gestures.
    */
    volatile uint8_t dtScrollDebounce;

    /**
     *  This parameter sets the number of Zoom gestures that will be ignored after a Two-finger Scroll gesture
     *  is observed. This is used to filter out Zoom gestures that inevitably occur during a transition from
     *  the Two-finger Scroll.
    */
    volatile uint8_t dtScrollToZoomDebounce;

    /**
     *  This parameter sets the number of pixels in X direction that has to be exceeded before a Lift Off event
     *  to trigger the Two-finger Inertial Scroll. A high value indicates that a bigger distance should be passed
     *  to activate a Two-finger Inertial Scroll gesture.
    */
    volatile uint8_t stInScrActiveDistanceX;

    /**
     *  This parameter sets the number of pixels in Y direction that has to be exceeded before a Lift Off event
     *  to trigger the Two-finger Inertial Scroll. A high value indicates that a bigger distance should be passed
     *  to activate a Two-finger Inertial Scroll gesture.
    */
    volatile uint8_t stInScrActiveDistanceY;

    /**
     *  This use can select Low or High levels of the One-finger Inertial count. The decayCount decays through
     *  a 64-byte array or a 32-byte array. A low Inertial Scroll count level selects a 32-byte array and sends
     *  a few Inertial scrolls. High = 1. Low = 0.
    */
    volatile uint8_t stInScrCountLevel;

    /**
     *  This parameter sets the number of pixels in X direction that has to be exceeded before a Lift Off event to
     *  trigger the Two-finger Inertial Scroll. A high value indicates that a bigger distance should be passed to
     *  activate a Two-finger Inertial Scroll gesture.
    */
    volatile uint8_t dtInScrActiveDistanceX;

    /**
     *  This parameter sets the number of pixels in Y direction that has to be exceeded before a Lift Off event to
     *  trigger the Two-finger Inertial Scroll. A high value indicates that a bigger distance should be passed to
     *  activate a Two-finger Inertial Scroll gesture.
    */
    volatile uint8_t dtInScrActiveDistanceY;

    /**
     *  This use can select Low or High levels of the Two-finger Inertial count. The decayCount decays through
     *  a 64-byte array or a 32-byte array. A low Two-finger Inertial Scroll count level selects a 32-byte array
     *  and sends a few Inertial scrolls. High = 1; Low = 0;
    */
    volatile uint8_t dtInScrCountLevel;

    /**
     *  This parameter sets the minimum active step distance (in pixels) from the point of a Touchdown, near the
     *  edge, that has to be exceeded before the gesture is triggered. The path covered by the finger should not
     *  exceed the top angle threshold (topAngleThreshold) and the bottom angle threshold (bottomAngleThreshold).
    */
    volatile uint8_t edgeSwipeActiveDistance;

    /**
     *  This parameter defines the maximum angle (in degrees) that the path of a finger can subtend on the point
     *  of a Touch Down, near the edge. A 1 degree angle means that the user can do gestures only on a single line.
    */
    volatile uint8_t topAngleThreshold;

    /**
     *  This parameter defines the maximum angle (in degrees) that the path of a finger can subtend on the point of
     *  a Touchdown, near the edge. A 1 degree angle means that the user can do gestures only on a single line.
    */
    volatile uint8_t bottomAngleThreshold;

    /**
     *  This parameter sets the edge area for the Edge Swipe gestures. A valid Edge Swipe gesture should start
     *  within the width of the disambiguation region. Increasing this parameter makes it easier for the user to
     *  find the edge, but it reduces the useful area of the trackpad.
    */
    volatile uint8_t widthOfDisambiguation;

    /**
     *  This parameter sets the number of similar, sequential pan gestures that should be performed before the
     *  pan motion is considered valid. This parameter is for the One-finger Pan motions.
    */
    volatile uint8_t STPanDebounce;

    /**
     *  This parameter sets the number of similar, sequential pan gestures that should be performed before the
     *  pan motion is considered valid. This parameter is for the Two-finger Pan motions.
    */
    volatile uint8_t DTPanDebounce;

    /**
     *  This parameter sets the number of sequential Zoom gestures in a particular direction (in or out) that
     *  has to be observed before the Zoom gesture is deemed valid. The default is 2. For example, for a Zoom
     *  in action, three Zoom in gestures must be observed in sequence before reporting the action to the caller.
    */
    volatile uint8_t DTZoomDebounce;

    /**
     *  This parameter sets the number of Zoom gestures that will be ignored after a Two-finger Pan gesture is
     *  observed. This is used to filter out Zoom gestures that inevitably occur during a transition from the
     *  Two-finger Pan. If you set this parameter to 0 you will observe debounced Zoom gestures right after
     *  Two-finger Pan gestures.
    */
    volatile uint8_t DTPanToZoomDebounce;

    /**
     *  This parameter sets the number of sequential Pan gestures in a particular direction that have to be
     *  observed before the Rotate gesture is deemed invalid. For example, if this parameter is set to 20 and
     *  you are performing a Rotate action, then the touch cannot continue in the same direction for 20 Pan
     *  counts and still have a valid Rotate gesture. After this threshold is reached, the reported gesture causes
     *  to be a Rotate and the corresponding Pan gesture is reported.
    */
    volatile uint8_t rotateDebounce;

    /**
     *  Determines the number of motion gestures that must be detected before a subsequent gesture is considered as
     *  a completed gesture; for example, a debounce of 2 requires three consecutive gestures.
    */
    volatile uint8_t completedDebounce;

    /**
     *  This parameter sets the maximum radius in resolution units that the second Click in a Double Click sequence
     *  can extend. If the second Click occurs outside this radius, the Double Click sequence is discarded.
    */
    volatile uint8_t doubleClickRadius;

    /**
     *  These parameters set the maximum X-axis displacement for Click gestures (One-finger Click, Two-finger Click
     *  and constituents of One-finger Double Click).
    */
    volatile uint8_t clickRadiusX;

    /**
     *  These parameters set the maximum Y-axis displacement for Click gestures (One-finger Click, Two-finger Click
     *  and constituents of One-finger Double Click).
    */
    volatile uint8_t clickRadiusY;

    /**
     *  This parameter sets the minimum duration of how long to wait prior to decoding when touches switch from a
     *  single-touch to dual-touch or vice versa. The time is measured in milliseconds.
    */
    volatile uint16_t settlingTimeout;

    /**
     *  Resolution X axis.
    */
    volatile uint16_t resolutionX;

    /**
     *  Resolution Y axis.
    */
    volatile uint16_t resolutionY;

    /**
     *  This is the maximum time window that will be searched for the flick (in milliseconds).
    */
    volatile uint16_t flickSampleTime;

    /**
     *  This is the maximum time window that will be searched for the flick (in milliseconds).
    */
    volatile uint16_t edgeSwipeTimeout;

    /**
     *  This parameter sets the maximum time during which two touches can be on the panel before being
     *  disqualified as a Two-finger Click event. The time is measured in milliseconds.
    */
    volatile uint16_t DTClickTimeoutMax;

    /**
     *  This parameter sets the minimum duration that two touches need to be on the panel before a Two-finger Click
     *  event is registered. This filters very rapid dual-touch clicks. This helps applications define very
     *  deliberate dual-touch click events. This parameter should be set lower than the dual-touch maximum click
     *  timeout parameter.
    */
    volatile uint16_t DTClickTimeoutMin;

    /**
     *  This parameter sets the maximum duration that a touch has to be on the panel to consider this gesture as a
     *  One-finger Single Click. If the touch is placed on the panel for longer than this value,
     *  `$INSTANCE_NAME`_NO_GESTURE event is sent.
    */
    volatile uint16_t STClickTimeoutMax;

    /**
     *  This parameter sets the minimum duration that a Click can stay on the panel to qualify as a One-finger Click.
     *  This can be used by applications to set how deliberately a Single Click operation must be performed.
     *  This helps filter out noisy events or very rapid clicks which are usually performed inadvertently.
     *  This parameter should be set lower than the One-finger max click timeout parameter.
    */
    volatile uint16_t STClickTimeoutMin;

    /**
     *  This parameter is the maximum allowable time between the release times of two sequential clicks in order
     *  the motion is be considered a Double Click.
    */
    volatile uint16_t STDoubleClickTimeoutMax;

    /**
     *  This parameter sets the minimum duration between the release times of two sequential clicks in order the
     *  motion is considered a Double Click.
    */
    volatile uint16_t STDoubleClickTimeoutMin;

    /* Masks */

    /**
     *  This parameter keeps masks for the 4 gesture groups. The four most significant bits are used. Each bit
     *  represents a group. The most significant bit is associated with 4-th group. This parameter is used to enable/disable
     *  reporting for groups. When a mask is set to 0, reporting is disabled for the corresponding group.
    */
    volatile uint8_t groupMask;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group1Start;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group1End;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group2Start;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group2End;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group3Start;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group3End;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group4Start;

    /**
     *  Gesture mask group internal parameter
    */
    volatile uint8_t group4End;
} `$INSTANCE_NAME`_CONFIG_STRUCT;

/** \brief Ballistic multiplier configuration structure */
typedef struct
{
    /** Number of detected fingers (0, 1 or 2) */
    uint8_t  touchNumber;
    /** Acceleration Coefficient */
    uint8_t  accelCoeff;
    /** Speed Coefficient */
    uint8_t  speedCoeff;
    /** Divisor Value */
    uint8_t  divisorValue;
    /** Speed Threshold X */
    uint8_t  speedThresholdX;
    /** Speed Threshold Y */
    uint8_t  speedThresholdY;
}`$INSTANCE_NAME`_BALLISTIC_MULT;

/** \}
* \endcond */

/* Touch position type */
typedef struct {
    uint16_t x;
    uint16_t y;
} `$INSTANCE_NAME`_POSITION_STRUCT;

/* Ballistics Multiplier library structure */
typedef struct
{
    `$INSTANCE_NAME`_BALLISTIC_MULT paramStr;
    uint32_t currentTimestamp;       /* Current timestamp */
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
#define `$INSTANCE_NAME`_GESTURES_ENABLED               ((0u != `$INSTANCE_NAME`_CLICKS_ENABLED) ||\
                                                         (0u != `$INSTANCE_NAME`_EDGE_SWIPE_ENABLED) ||\
                                                         (0u != `$INSTANCE_NAME`_FLICKS_ENABLED) ||\
                                                         (0u != `$INSTANCE_NAME`_ST_SCROLLS_ENABLED) ||\
                                                         (0u != `$INSTANCE_NAME`_ROTATE_ENABLED) ||\
                                                         (0u != `$INSTANCE_NAME`_DT_SCROLLS_ENABLED) ||\
                                                         (0u != `$INSTANCE_NAME`_ZOOM_ENABLED))

#define `$INSTANCE_NAME`_ROTATE_TO_OTHER_DEBOUNCE       (10u)


/***************************************
*        Function Prototypes
***************************************/
uint32_t   `$INSTANCE_NAME`_DecodeAllGestures(uint32_t touchNumber, uint32_t currentTimestamp, const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
void     `$INSTANCE_NAME`_BallisticsMultiplier(const `$INSTANCE_NAME`_BALLISTIC_MULT * ballisticMultiplier, uint32_t currentTimestamp, int16_t *pos);


/***************************************
*        External API
***************************************/
extern void Gesture_Init(const `$INSTANCE_NAME`_CONFIG_STRUCT *config);
extern uint32_t Gesture_GetSettlingStartTime(void);
extern uint16_t Gesture_GetTouchDuration(void);

#if ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u))
    extern uint8_t Gesture_DecodeAllClickGestures(uint8_t touchNumber, uint32_t currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
    extern uint16_t Gesture_GetInterClickDuration(void);
#endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)) */

#if (`$INSTANCE_NAME`_ZOOM_ENABLED == 1u)
    extern uint8_t Gesture_DecodeDTZoomGestures(uint8_t touchNumber, uint32_t currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_ZOOM_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u)
    extern uint8_t Gesture_DecodeDTScrollGestures(uint8_t touchNumber, uint32_t currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)
    extern uint8_t Gesture_DecodeSTScrollGestures(uint8_t touchNumber, uint32_t currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u)
    extern uint8_t Gesture_DecodeFlickGestures(uint8_t touchNumber, uint32_t currentTimestamp, \
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
    extern uint8_t Gesture_DecodeSTRotateGestures(uint8_t touchNumber, uint32_t currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
    extern uint8_t Gesture_DecodeEdgeSwipeGestures(uint8_t touchNumber, uint32_t currentTimestamp, \
                                                            const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) */

#if (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u)
    extern void BallisticMultiplier(`$INSTANCE_NAME`_BALLISTIC_MULT_INT * ballisticMultiplier, int16_t *pos);
#endif /* (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u) */

#if ((`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) || (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u))
    extern uint8_t Gesture_GetScrollCnt(void);
    extern uint8_t Gesture_GetDecayCnt(void);
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
*  currentTimestamp: Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32_t - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeClickGestures(touchNumber, currentTimestamp, pos) ((uint32_t)Gesture_DecodeAllClickGestures( \
                        (uint8_t)(touchNumber), (currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeClickGestures(touchNumber, currentTimestamp, pos) (`$INSTANCE_NAME`_NO_GESTURE)
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
*  currentTimestamp: Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32_t - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ZOOM_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeZoomGestures(touchNumber, currentTimestamp, pos) ((uint32_t)Gesture_DecodeDTZoomGestures( \
                        (uint8_t)(touchNumber), (currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeZoomGestures(touchNumber, currentTimestamp, pos) (`$INSTANCE_NAME`_NO_GESTURE)
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
*  currentTimestamp: Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32_t - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_DT_SCROLLS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber, currentTimestamp, pos) ((uint32_t)Gesture_DecodeDTScrollGestures( \
                        (uint8_t)(touchNumber), (currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber, currentTimestamp, pos) (`$INSTANCE_NAME`_NO_GESTURE)
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
*  currentTimestamp: Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32_t - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeFlickGestures(touchNumber, currentTimestamp, pos) ((uint32_t)Gesture_DecodeFlickGestures( \
                        (uint8_t)(touchNumber), (currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeFlickGestures(touchNumber, currentTimestamp, pos) (`$INSTANCE_NAME`_NO_GESTURE)
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
*  currentTimestamp: Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32_t - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeSTScrollGestures(touchNumber, currentTimestamp, pos) ((uint32_t)Gesture_DecodeSTScrollGestures( \
                        (uint8_t)(touchNumber), (currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeSTScrollGestures(touchNumber, currentTimestamp, pos) (`$INSTANCE_NAME`_NO_GESTURE)
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
*  currentTimestamp: Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32_t - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeRotateGestures(touchNumber, currentTimestamp, pos) ((uint32_t)Gesture_DecodeSTRotateGestures( \
                        (uint8_t)(touchNumber), (currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeRotateGestures(touchNumber, currentTimestamp, pos) (`$INSTANCE_NAME`_NO_GESTURE)
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
*  currentTimestamp: Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  uint32_t - detected gesture code.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
    #define `$INSTANCE_NAME`_DecodeEdgeSwipe(touchNumber, currentTimestamp, pos) ((uint32_t)Gesture_DecodeEdgeSwipeGestures( \
                        (uint8_t)(touchNumber), (currentTimestamp), (pos)))
#else
    #define `$INSTANCE_NAME`_DecodeEdgeSwipe(touchNumber, currentTimestamp, pos) (`$INSTANCE_NAME`_NO_GESTURE)
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
*  uint32_t - Time since the fingers are present on the trackpad
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetTimerTouchCounter() ((uint32_t)Gesture_GetTouchDuration())


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
    *  uint32_t - the Gesture_interClickDuration value, which is used for time
    *  stamping and decoding click gestures.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_GetTimerClickCounter() ((uint32_t) Gesture_GetInterClickDuration())
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
*  uint32_t - the timestamp of start settling event.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetSettlingStartTime() (Gesture_GetSettlingStartTime())


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
*  uint8_t - Returns number of scrolls when finger exceeds Scroll Threshold.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetScrollCnt() (Gesture_GetScrollCnt())

/*******************************************************************************
* Macro Name: `$INSTANCE_NAME`_GetDecayCnt
********************************************************************************
*
* Summary:
*  Returns scroll inertial step value.
*
* Parameters:
*  None
*
* Return:
*  uint8_t - Returns scroll inertial step value.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetDecayCnt() (Gesture_GetDecayCnt())

#endif /* CY_CAPSENSE_TMG_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
