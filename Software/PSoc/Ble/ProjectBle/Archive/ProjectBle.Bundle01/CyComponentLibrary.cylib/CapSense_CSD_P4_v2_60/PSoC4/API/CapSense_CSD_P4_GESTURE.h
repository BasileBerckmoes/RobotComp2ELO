/*******************************************************************************
* File Name: `$INSTANCE_NAME`_GESTURE.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the Trackpad with
*  Gestures APIs for the CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_GESTURE_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_GESTURE_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_CSHL.h"
#include "`$INSTANCE_NAME`_TMG.h"
#include "`$INSTANCE_NAME`_PVT.h"


/***************************************
*   Condition compilation parameters
***************************************/

#define `$INSTANCE_NAME`_CLICK_GEST_ENABLED             (`$Gestures_ClicksEnabled`u)
#define `$INSTANCE_NAME`_ZOOM_GEST_ENABLED              (`$Gestures_ZoomEnabled`u)
#define `$INSTANCE_NAME`_ST_SCROLL_GEST_ENABLED         (`$Gestures_OneFingerScrollsEnabled`u)
#define `$INSTANCE_NAME`_DT_SCROLL_GEST_ENABLED         (`$Gestures_TwoFingerScrollsEnabled`u)
#define `$INSTANCE_NAME`_FLICK_GEST_ENABLED             (`$Gestures_FlicksEnabled`u)
#define `$INSTANCE_NAME`_ROTATE_GEST_ENABLED            (`$Gestures_RotateEnabled`u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_GEST_ENABLED        (`$Gestures_EdgeSwipesEnabled`u)

/* Condition to enable Trackpad with Gestures API  */
#define `$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES       (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT)

/* IIR filter coefficient */
#define `$INSTANCE_NAME`_XY_IIR_COEF                    (0x08u)

/* Mask for RAW and POS filters */
#define `$INSTANCE_NAME`_XY_IIR_MASK                    (0x08u)
#define `$INSTANCE_NAME`_XY_JITTER_MASK                 (0x10u)
#define `$INSTANCE_NAME`_XY_BALLISTIC_MASK              (0x40u)
#define `$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK           (0x80u)

/* Ballistic Multiplier */
#if (0u != (`$INSTANCE_NAME`_XY_BALLISTIC_MASK & `$INSTANCE_NAME`_TRACKPAD_GEST_POS_FILTERS_MASK))
#define `$INSTANCE_NAME`_BALLISTIC_EN                   (1u)
#else
#define `$INSTANCE_NAME`_BALLISTIC_EN                   (0u)
#endif /* (0u != (`$INSTANCE_NAME`_XY_BALLISTIC_MASK & `$INSTANCE_NAME`_TRACKPAD_GEST_POS_FILTERS_MASK)) */

/* XY IIR filter coefficients */
#define `$INSTANCE_NAME`_XY_IIR_DISABLED                (0u)
#define `$INSTANCE_NAME`_XY_IIR_2                       (1u)
#define `$INSTANCE_NAME`_XY_IIR_4                       (2u)
#define `$INSTANCE_NAME`_XY_IIR_8                       (3u)
#define `$INSTANCE_NAME`_XY_IIR_16                      (4u)
#define `$INSTANCE_NAME`_XY_IIR_COEF_MASK               (7u)

/* XY filters initialize flag */
#define `$INSTANCE_NAME`_XY_FILTERS_INITIALIZED         (3u)
#define `$INSTANCE_NAME`_XY_FILTERS_NOT_INITIALIZED     (0u)

#define `$INSTANCE_NAME`_X0Y0_FILTERS_INITIALIZED       (1u)
#define `$INSTANCE_NAME`_X0Y0_FILTERS_NOT_INITIALIZED   (0u)

#define `$INSTANCE_NAME`_X1Y1_FILTERS_INITIALIZED       (2u)
#define `$INSTANCE_NAME`_X1Y1_FILTERS_NOT_INITIALIZED   (0u)

/* Enable XY filtering for the second finger*/
#define `$INSTANCE_NAME`_XY_SECOND_FINGER_FILTER_EN     (0u)


/***************************************
*           API Constants
***************************************/

/* Widgets constants definition */
#define `$INSTANCE_NAME`_TRACKPAD__TPG                  (`$trackpadWithGesturesWidgetID`u)

/* Mask for Trackpad with Gestures position filters */
#define `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK    (`$INSTANCE_NAME`_TRACKPAD_GEST_POS_FILTERS_MASK)

/* Constant to check if any position filter exists  */
#define `$INSTANCE_NAME`_TP_GESTURE_ANY_POS_FILTER      ( `$INSTANCE_NAME`_XY_IIR_MASK | \
                                                           `$INSTANCE_NAME`_XY_JITTER_MASK | \
                                                           `$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK )

/* Filters Number */
#define `$INSTANCE_NAME`_TP_FILTERS_NUMBER              (3u)

/* Offsets for X and Y coordinates */
#define `$INSTANCE_NAME`_TP_GESTURE_POS_IIR             (0u)
#define `$INSTANCE_NAME`_TP_GESTURE_POS_AF              (4u)
#define `$INSTANCE_NAME`_TP_GESTURE_POS_JIT             (8u)

/* Fingers identifiers */
#define `$INSTANCE_NAME`_FIRST_FINGER_ID                (0u)
#define `$INSTANCE_NAME`_SECOND_FINGER_ID               (1u)

/* TMG_BallisticsMultiplier offsets */
#define `$INSTANCE_NAME`_FIRST_FINGER_OFFSET            (0u)
#define `$INSTANCE_NAME`_SECOND_FINGER_OFFSET           (2u)
#define `$INSTANCE_NAME`_DX_ID                          (0u)
#define `$INSTANCE_NAME`_DY_ID                          (1u)

/* Maximums for X and Y coordinates */
#define `$INSTANCE_NAME`_TP_GESTURE_POS_X_MAX           (4000u)
#define `$INSTANCE_NAME`_TP_GESTURE_POS_Y_MAX           (4000u)

/* Centroid Errors */
#define `$INSTANCE_NAME`_POSITION_ERROR                 (0xFFFFFFFFu)
#define `$INSTANCE_NAME`_FINGER_ERROR                   (0xFFu)

/* Previous Position Initial */
#define `$INSTANCE_NAME`_POSITION_NO_FINGER             (-1)

/***************************************
*        Defines for Gesture Codes
***************************************/
/* Code for no gesture detected case */
#define `$INSTANCE_NAME`_NO_GESTURE                  (0x00u)

/* Single touch click gestures */
#define `$INSTANCE_NAME`_ST_CLICK                    (0x20u)
#define `$INSTANCE_NAME`_ST_DOUBLECLICK              (0x22u)
#define `$INSTANCE_NAME`_CLICK_AND_DRAG              (0x24u)

/* Rotate gestures */
#define `$INSTANCE_NAME`_ROTATE_CW                   (0x28u)
#define `$INSTANCE_NAME`_ROTATE_CCW                  (0x29u)

/* TouchDown and Lift Off Gestures */
#define `$INSTANCE_NAME`_TOUCHDOWN                   (0x2Fu)
#define `$INSTANCE_NAME`_LIFT_OFF                    (0x4Fu)

/* ST Scroll gestures */
#define `$INSTANCE_NAME`_ST_SCROLL_NORTH             (0xC0u)
#define `$INSTANCE_NAME`_ST_SCROLL_SOUTH             (0xC2u)
#define `$INSTANCE_NAME`_ST_SCROLL_WEST              (0xC4u)
#define `$INSTANCE_NAME`_ST_SCROLL_EAST              (0xC6u)
#define `$INSTANCE_NAME`_ST_INERTIAL_SCROLL_NORTH    (0xB0u)
#define `$INSTANCE_NAME`_ST_INERTIAL_SCROLL_SOUTH    (0xB2u)
#define `$INSTANCE_NAME`_ST_INERTIAL_SCROLL_WEST     (0xB4u)
#define `$INSTANCE_NAME`_ST_INERTIAL_SCROLL_EAST     (0xB6u)

/* DT Scroll gestures */
#define `$INSTANCE_NAME`_DT_SCROLL_NORTH             (0xC8u)
#define `$INSTANCE_NAME`_DT_SCROLL_SOUTH             (0xCAu)
#define `$INSTANCE_NAME`_DT_SCROLL_WEST              (0xCCu)
#define `$INSTANCE_NAME`_DT_SCROLL_EAST              (0xCEu)
#define `$INSTANCE_NAME`_DT_INERTIAL_SCROLL_NORTH    (0xB8u)
#define `$INSTANCE_NAME`_DT_INERTIAL_SCROLL_SOUTH    (0xBAu)
#define `$INSTANCE_NAME`_DT_INERTIAL_SCROLL_WEST     (0xBCu)
#define `$INSTANCE_NAME`_DT_INERTIAL_SCROLL_EAST     (0xBEu)

/* Dual touch click gesture */
#define `$INSTANCE_NAME`_DT_CLICK                    (0x40u)

/* Zoom Gestures */
#define `$INSTANCE_NAME`_ZOOM_IN                     (0x48u)
#define `$INSTANCE_NAME`_ZOOM_OUT                    (0x49u)

/* Flick gestures */
#define `$INSTANCE_NAME`_FLICK_NORTH                 (0x50u)
#define `$INSTANCE_NAME`_FLICK_NORTH_EAST            (0x52u)
#define `$INSTANCE_NAME`_FLICK_EAST                  (0x54u)
#define `$INSTANCE_NAME`_FLICK_SOUTH_EAST            (0x56u)
#define `$INSTANCE_NAME`_FLICK_SOUTH                 (0x58u)
#define `$INSTANCE_NAME`_FLICK_SOUTH_WEST            (0x5Au)
#define `$INSTANCE_NAME`_FLICK_WEST                  (0x5Cu)
#define `$INSTANCE_NAME`_FLICK_NORTH_WEST            (0x5Eu)

/* Edge swipe gestures */
#define `$INSTANCE_NAME`_EDGE_SWIPE_LEFT             (0xA0u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_RIGHT            (0xA2u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_TOP              (0xA4u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_BOTTOM           (0xA6u)
#define `$INSTANCE_NAME`_EDGE_SWIPE_MASK             (0xA0u)   /*The Mask for the Edge Swipe Gestures */

/* Gesture groups masks */
#define `$INSTANCE_NAME`_GROUP1_MASK                 (0x10u)
#define `$INSTANCE_NAME`_GROUP2_MASK                 (0x20u)
#define `$INSTANCE_NAME`_GROUP3_MASK                 (0x40u)
#define `$INSTANCE_NAME`_GROUP4_MASK                 (0x80u)

/* Invalid coordinates */
#define `$INSTANCE_NAME`_INVALID_COORDINATE          (0xFFFFu)


/***************************************
*         Parameters
***************************************/
`$AdvCentroidThresholds`

#define `$INSTANCE_NAME`_PENULTIMATE_THRESHOLD          (`$INSTANCE_NAME`_ADV_PENULTIMATE_THRESHOLD + `$INSTANCE_NAME`_ADV_CROSS_COUPLING_THRESHOLD)
#define `$INSTANCE_NAME`_VIRTUAL_SENSOR_THRESHOLD       (`$INSTANCE_NAME`_ADV_VIRTUAL_SENSOR_THRESHOLD + `$INSTANCE_NAME`_ADV_CROSS_COUPLING_THRESHOLD)
#define `$INSTANCE_NAME`_CROSS_COUPLING_THRESHOLD       (`$INSTANCE_NAME`_ADV_CROSS_COUPLING_THRESHOLD)

/* Number of supported fingers */
#define `$INSTANCE_NAME`_MAX_FINGER                     (2u)

/* Ballistic Multiplier Parameters */
`$BallisticMultiplier`

/* Adaptive Filter Parameters */
`$AdaptiveIIRFilterDefines`


/***************************************
*        Structures
***************************************/

/* Touch position type */
typedef struct {
    uint16 x;
    uint16 y;
} `$INSTANCE_NAME`_POSITION_STRUCT;

/* Touch position type */
typedef struct {
    int16 x;
    int16 y;
} `$INSTANCE_NAME`_DIFF_POSITION_STRUCT;

/* Adaptive Filter type */
typedef struct
{
    uint8   maxK;     /* Max Filter Coefficient */
    uint8   minK;     /* Min Filter Coefficient */
    uint8   noMovTh;     /* No Movement Threshold */
    uint8   littleMovTh; /* Little Movement Threshold */
    uint8   largeMovTh;  /* Large Movement Threshold */
    uint8   divVal;      /* Divisor Value */
}ADAPTIVE_FILTER_OPS_P4_v2_60;

/* Advanced Centroid pointers type */
typedef struct
{
    uint16 (*ptrGet16bitDiffCountData)(uint32 sensor);  /* Pointer to `$INSTANCE_NAME`_sensorSignal[] */
    uint16 (*ptrGet16bitFingerThreshold)(uint32 widget);  /* Pointer to `$INSTANCE_NAME`_fingerThreshold[] */
    uint16 (*ptrGet16bitNoiseThreshold)(uint32 widget);   /* Pointer to `$INSTANCE_NAME`_noiseThreshold[] */
    uint16  *positionZ;             /* Pointer to the array - Z position */
    uint32  *centroidMult;          /* Pointer to `$INSTANCE_NAME`_centroidMult[] */
    uint8   *maxPos;                /* Pointer to `$INSTANCE_NAME`_maxPos[] */
    uint8 const *rawDataIndex;      /* Pointer to `$INSTANCE_NAME`_rawDataIndex[] */
}`$INSTANCE_NAME`_ADV_CENTROID_POINTERS_P4_v2_60;

/* Advanced Centroid variables type */
typedef struct
{
    uint16  penultimateThreshold;   /* `$INSTANCE_NAME`_PENULTIMATE_THRESHOLD const */
    uint16  virtualSensorThreshold; /* `$INSTANCE_NAME`_VIRTUAL_SENSOR_THRESHOLD const */
    uint16  crossCouplingThreshold; /* `$INSTANCE_NAME`_CROSS_COUPLING_THRESHOLD const */
    uint8   sliderXCount;           /* Number of segments on X axis - const */
    uint8   segCount;               /* Number of segments on both axis - const */
    uint8   maxFinger;              /* Number of supported fingers - const */
    uint8   widgetTPG;              /* Trackpad with Gestures widget */
    `$INSTANCE_NAME`_ADV_CENTROID_POINTERS_P4_v2_60 * pointers;
}`$INSTANCE_NAME`_ADV_CENTROID_P4_v2_60;


/***************************************
*        Function Prototypes
***************************************/

#if (0u != `$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES)
    uint32 `$INSTANCE_NAME`_DecodeAllGestures(uint32 touchNumber, const `$INSTANCE_NAME`_POSITION_STRUCT *pos);
    #define `$INSTANCE_NAME`_GetScrollCnt() `$INSTANCE_NAME`_TMG_GetScrollCnt()
    /*  High level Functions Prototypes   */
    uint32 `$INSTANCE_NAME`_GetDoubleTouchCentroidPos(`$INSTANCE_NAME`_POSITION_STRUCT *pos);
    #if (0u != `$INSTANCE_NAME`_BALLISTIC_EN)
        uint32 `$INSTANCE_NAME`_GetDiffDoubleCentroidPos(`$INSTANCE_NAME`_DIFF_POSITION_STRUCT *pos);
    #endif /* (0u != `$INSTANCE_NAME`_BALLISTIC_EN) */

    /*  Internal Functions Prototypes     */
    void `$INSTANCE_NAME`_AdvancedCentroidInit(void);
    #if (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)
        void `$INSTANCE_NAME`_ApplyPositionFilters(uint32 fingerID, `$INSTANCE_NAME`_POSITION_STRUCT pos[]);
    #endif /* (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK) */

    #if (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
        uint16 `$INSTANCE_NAME`_IIRXFilter(uint16 x1, uint16 x2, uint32 iirFilterCoef);
    #endif /* (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & \
            *          `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
            */

    #if (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
        void AdaptiveFilterInit_P4_v2_60(ADAPTIVE_FILTER_OPS_P4_v2_60 *options);
        void AdaptiveFilter_P4_v2_60(uint16 *curX, uint16 *curY, uint16 *prevX, uint16 *prevY);
    #endif /* (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & \
                        *          `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
                        */

    uint16 `$INSTANCE_NAME`_GetTrackpadValueZ(uint32 axisID, uint32 fingerID);
    uint16 `$INSTANCE_NAME`_Get16bitDiffCountData(uint32 sensor);
    uint16 `$INSTANCE_NAME`_Get16bitFingerThreshold(uint32 widget);
    uint16 `$INSTANCE_NAME`_Get16bitNoiseThreshold(uint32 widget);

    /*  Pre-compiler Functions Prototypes     */
    void AdvCentroidInit_P4_v2_60(void);
    uint32 GetDoubleCentroidPos_P4_v2_60(`$INSTANCE_NAME`_ADV_CENTROID_P4_v2_60 *config, `$INSTANCE_NAME`_POSITION_STRUCT *pos);
#endif /* (0u != `$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES) */


/***************************************
*     Vars with External Linkage
***************************************/
#if(0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
    extern ADAPTIVE_FILTER_OPS_P4_v2_60 `$INSTANCE_NAME`_adpFltOptions;
#endif /* (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)) */

#if (0u != `$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES)
    extern `$INSTANCE_NAME`_TMG_CONFIG_STRUCT `$INSTANCE_NAME`_gesturesConfig;
#endif /* (0u != `$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES) */


#endif /* CY_CAPSENSE_CSD_GESTURE_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
