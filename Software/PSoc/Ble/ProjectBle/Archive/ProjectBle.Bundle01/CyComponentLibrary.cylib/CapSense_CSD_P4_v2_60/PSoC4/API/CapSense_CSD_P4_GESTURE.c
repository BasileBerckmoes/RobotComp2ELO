/*******************************************************************************
* File Name: `$INSTANCE_NAME`_GESTURE.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the Trackpad with Gestures APIs
*  for the CapSesne CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_GESTURE.h"
#include "`$INSTANCE_NAME`_PVT.h"

#if(`$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES > 0u)

/* Variables and structures */
#if (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)
    uint8 `$INSTANCE_NAME`_firstTimeIndex = `$INSTANCE_NAME`_XY_FILTERS_NOT_INITIALIZED;
    uint16 `$INSTANCE_NAME`_posFiltersDataGesture[2u*`$INSTANCE_NAME`_TP_FILTERS_NUMBER*`$INSTANCE_NAME`_MAX_FINGER] = {0u};
#endif /* (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK) */
uint8  `$INSTANCE_NAME`_maxPos[2u*`$INSTANCE_NAME`_MAX_FINGER] = {0u};
uint16  `$INSTANCE_NAME`_trackpadFingerPosZ[2u*`$INSTANCE_NAME`_MAX_FINGER] = {0u};
uint32 `$INSTANCE_NAME`_previousFingerNum = 0u;

`$INSTANCE_NAME`_ADV_CENTROID_P4_v2_60 `$INSTANCE_NAME`_advCentroidConfig;
`$INSTANCE_NAME`_ADV_CENTROID_POINTERS_P4_v2_60 `$INSTANCE_NAME`_advCentroidConfigPointers = {
    &`$INSTANCE_NAME`_Get16bitDiffCountData,
    &`$INSTANCE_NAME`_Get16bitFingerThreshold,
    &`$INSTANCE_NAME`_Get16bitNoiseThreshold,
    `$INSTANCE_NAME`_trackpadFingerPosZ,
    `$INSTANCE_NAME`_centroidMult,
    `$INSTANCE_NAME`_maxPos,
    (const uint8  *)`$INSTANCE_NAME`_rawDataIndex,
};

#if (0u != `$INSTANCE_NAME`_BALLISTIC_EN)
    `$INSTANCE_NAME`_TMG_BALLISTIC_MULT `$INSTANCE_NAME`_ballisticMultiplier;
    `$INSTANCE_NAME`_DIFF_POSITION_STRUCT `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_MAX_FINGER];
#endif /* (0u != `$INSTANCE_NAME`_BALLISTIC_EN) */


#if(0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
    ADAPTIVE_FILTER_OPS_P4_v2_60  `$INSTANCE_NAME`_adpFltOptions = {
                                        `$INSTANCE_NAME`_MAX_FILTER_COEF,
                                        `$INSTANCE_NAME`_MIN_FILTER_COEF,
                                        `$INSTANCE_NAME`_NO_MOVE_THRESHOLD,
                                        `$INSTANCE_NAME`_LITTLE_MOVE_THRESHOLD,
                                        `$INSTANCE_NAME`_LARGE_MOVE_THRESHOLD,
                                        `$INSTANCE_NAME`_DIVISOR
                                    };
#endif /* (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)) */


#if (0u != `$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES)
    `$INSTANCE_NAME`_TMG_CONFIG_STRUCT `$INSTANCE_NAME`_gesturesConfig = `$INSTANCE_NAME`_TMG_CONFIG_DEFAULT_VALUES;
#endif /* (0u != `$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES) */

/* Trackpad with Gestures APIs */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AdvancedCentroidInit
********************************************************************************
*
* Summary:
*  Initializes Advanced Centroid.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   `$INSTANCE_NAME`_advCentroidConfig - the structure
*   which contains API parameters;
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_AdvancedCentroidInit(void)
{
     /* Initializes Advanced Centroid Structure with Configuration parameters */
    `$INSTANCE_NAME`_advCentroidConfig.sliderXCount = `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_TRACKPAD__TPG];
    `$INSTANCE_NAME`_advCentroidConfig.segCount = `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_TRACKPAD__TPG]
                                                   + `$INSTANCE_NAME`_numberOfSensors[`$INSTANCE_NAME`_TRACKPAD__TPG + 1u];
    `$INSTANCE_NAME`_advCentroidConfig.penultimateThreshold = `$INSTANCE_NAME`_PENULTIMATE_THRESHOLD;
    `$INSTANCE_NAME`_advCentroidConfig.virtualSensorThreshold = `$INSTANCE_NAME`_VIRTUAL_SENSOR_THRESHOLD;
    `$INSTANCE_NAME`_advCentroidConfig.crossCouplingThreshold = `$INSTANCE_NAME`_CROSS_COUPLING_THRESHOLD;
    `$INSTANCE_NAME`_advCentroidConfig.maxFinger = `$INSTANCE_NAME`_MAX_FINGER;
    `$INSTANCE_NAME`_advCentroidConfig.widgetTPG = `$INSTANCE_NAME`_TRACKPAD__TPG;
    `$INSTANCE_NAME`_advCentroidConfig.pointers = &`$INSTANCE_NAME`_advCentroidConfigPointers;

    #if (0u != `$INSTANCE_NAME`_BALLISTIC_EN)
        /* Initializes Ballistic Multiplier Structure with Configuration parameters */
        `$INSTANCE_NAME`_ballisticMultiplier.accelLevel = `$INSTANCE_NAME`_ACCELERATION_LEVEL;
        `$INSTANCE_NAME`_ballisticMultiplier.speedLevel = `$INSTANCE_NAME`_SPEED_LEVEL;
        `$INSTANCE_NAME`_ballisticMultiplier.divisorValue = `$INSTANCE_NAME`_DIVISOR_VALUE;
        `$INSTANCE_NAME`_ballisticMultiplier.speedThresholdX = `$INSTANCE_NAME`_SPEED_THRESHOLD_X;
        `$INSTANCE_NAME`_ballisticMultiplier.speedThresholdY = `$INSTANCE_NAME`_SPEED_THRESHOLD_Y;
        `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = `$INSTANCE_NAME`_POSITION_NO_FINGER;
        `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = `$INSTANCE_NAME`_POSITION_NO_FINGER;
        `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = `$INSTANCE_NAME`_POSITION_NO_FINGER;
        `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = `$INSTANCE_NAME`_POSITION_NO_FINGER;
    #endif /* (0u != `$INSTANCE_NAME`_BALLISTIC_EN) */

    #if (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
        AdaptiveFilterInit_P4_v2_60(&`$INSTANCE_NAME`_adpFltOptions);
    #endif /* (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)) */

    /* Initializes Advanced Centroid */
    AdvCentroidInit_P4_v2_60();
    (void)`$INSTANCE_NAME`_TMG_TimerEnableInt();
    `$INSTANCE_NAME`_TMG_InitGestures(&`$INSTANCE_NAME`_gesturesConfig);
}

#if (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ApplyPositionFilters
********************************************************************************
*
* Summary:
*  Applies the position filters to X,Y coordinates.
*  To provider the filters linearity at the starting the X,Y coordinates are
*  reinitialized for each finger after detection the finger touch.
*
* Parameters:
*  fingerID: Finger Number. Values: 0u - First Finger, 1u - Second Finger
*
*  pos: Pointer to the structure
*  of two uint16 elements, where result
*  of calculation of X and Y position is stored:
*  pos[0].x - X position for First Finger;
*  pos[0].y - Y position for First Finger;
*  pos[1].x - X position for Second Finger;
*  pos[1].y - Y position for Second Finger;
*
* Return:
*  None.
*
* Global Variables:
*  None.
*
* Side Effects:
*
*******************************************************************************/
void `$INSTANCE_NAME`_ApplyPositionFilters(uint32 fingerID, `$INSTANCE_NAME`_POSITION_STRUCT pos[])
{
    uint8  posFiltersMask;
    uint16 posX;
    uint16 posY;
    uint32 offsetX;
    uint32 offsetY;

    #if (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
        uint32 iirFilterCoef;
    #endif /* (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & \
           *          `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
           */

    /* Calculates XY positions offsets for current Finger: X0, Y0, X1, Y1 */
    offsetX = fingerID << 1u;
    offsetY = offsetX + 1u;

    /* Gets the mask to check if a certain filter is enabled */
    posFiltersMask = `$INSTANCE_NAME`_posFiltersMask[`$INSTANCE_NAME`_TRACKPAD__TPG];

    /* Checks if this TPG has enabled filters */
    if (0u != (posFiltersMask & `$INSTANCE_NAME`_TP_GESTURE_ANY_POS_FILTER))
    {
        /* Gets X, Y positions for current Finger */
        posX = pos[fingerID].x;
        posY = pos[fingerID].y;

        /* Checks if filter for X and Y positions needs to be initialized */
        if (0u != (`$INSTANCE_NAME`_firstTimeIndex & ((uint8)fingerID + 1u)))
        {
            /* Does filtering */

            #if (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
                if (0u != (posFiltersMask & `$INSTANCE_NAME`_XY_IIR_MASK))
                {
                    iirFilterCoef = (uint32)posFiltersMask & (uint32)`$INSTANCE_NAME`_XY_IIR_COEF_MASK;

                    posX = (uint16) `$INSTANCE_NAME`_IIRXFilter(posX,
                                                           `$INSTANCE_NAME`_posFiltersDataGesture[offsetX], iirFilterCoef);
                    `$INSTANCE_NAME`_posFiltersDataGesture[offsetX] = posX;

                    posY = (uint16) `$INSTANCE_NAME`_IIRXFilter(posY,
                                                            `$INSTANCE_NAME`_posFiltersDataGesture[offsetY], iirFilterCoef);
                    `$INSTANCE_NAME`_posFiltersDataGesture[offsetY] = posY;
                }
            #endif /* (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & \
                   *          `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
                   */

            #if (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
                if ((0u != (posFiltersMask & `$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK)) && (`$INSTANCE_NAME`_SECOND_FINGER_ID != fingerID))
                {
                    AdaptiveFilter_P4_v2_60(&posX, &posY,
                                            &`$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_AF + offsetX],
                                            &`$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_AF + offsetY]);
                    `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_AF + offsetX] = posX;
                    `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_AF + offsetY] = posY;
                }
            #endif /* (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & \
                    *          `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
                    */

            #if (0u != (`$INSTANCE_NAME`_XY_JITTER_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
                if (0u != (posFiltersMask & `$INSTANCE_NAME`_XY_JITTER_MASK))
                {
                    posX = (uint16) `$INSTANCE_NAME`_JitterFilter(posX,
                                                        `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_JIT + offsetX]);
                    `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_JIT + offsetX] = posX;

                    posY = (uint16) `$INSTANCE_NAME`_JitterFilter(posY,
                                                        `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_JIT + offsetY]);
                    `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_JIT + offsetY] = posY;
                }
            #endif /* (0u != (`$INSTANCE_NAME`_XY_JITTER_MASK & \
                   *          `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
                   */

            /* Saves positions */
            pos[fingerID].x = posX;
            pos[fingerID].y = posY;
        }
        else
        {
            /* Inits filters */
            `$INSTANCE_NAME`_posFiltersDataGesture[offsetX] = posX;
            `$INSTANCE_NAME`_posFiltersDataGesture[offsetY] = posY;

            `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_JIT + offsetX] = posX;
            `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_JIT + offsetY] = posY;

            `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_AF + offsetX] = posX;
            `$INSTANCE_NAME`_posFiltersDataGesture[`$INSTANCE_NAME`_TP_GESTURE_POS_AF + offsetY] = posY;

            `$INSTANCE_NAME`_firstTimeIndex |= ((uint8)fingerID + 1u);
        }
    }
}
#endif /* (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDoubleTouchCentroidPos
********************************************************************************
*
* Summary:
*  If fingers are present on the trackpad, this function calculates the X and Y
*  position of fingers by calculating the centroids within a trackpad specified
*  range. The X and Y positions are calculated to the resolutions set in the
*  component customizer. Returns the number of fingers on the trackpad.
*  The position filters are applied to the result if enabled.
*  This function is available only if a trackpad with gestures is enabled in
*  customizer.
*
* Parameters:
*
*  pos: Pointer to the structure
*  of two uint16 elements, where result
*  of calculation of X and Y position is stored:
*  pos[0].x - X position for First Finger;
*  pos[0].y - Y position for First Finger;
*  pos[1].x - X position for Second Finger;
*  pos[1].y - Y position for Second Finger;
*
* Return:
*  uint32: number of finger on the trackpad (max 2), 0 if no finger present.
*  If more than 2 fingers are present, 0xFFFFFFFF should be returned.
*
* Global Variables:
*  None.
*
* Side Effects:
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetDoubleTouchCentroidPos(`$INSTANCE_NAME`_POSITION_STRUCT *pos)
{
    uint32 fingerNum;

    fingerNum = GetDoubleCentroidPos_P4_v2_60(&`$INSTANCE_NAME`_advCentroidConfig, pos);

    #if (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)
        if((fingerNum == 0u) || (fingerNum != `$INSTANCE_NAME`_previousFingerNum))
        {
            /* Resets filters */
            `$INSTANCE_NAME`_firstTimeIndex = `$INSTANCE_NAME`_XY_FILTERS_NOT_INITIALIZED;
        }

        if((fingerNum != 0u) && (fingerNum != `$INSTANCE_NAME`_POSITION_ERROR))
        {
            /* Does XY filtering for First Finger*/
            `$INSTANCE_NAME`_ApplyPositionFilters(`$INSTANCE_NAME`_FIRST_FINGER_ID, pos);

            #if (0u != `$INSTANCE_NAME`_XY_SECOND_FINGER_FILTER_EN)
                /* Does XY filtering for Second Finger*/
                `$INSTANCE_NAME`_ApplyPositionFilters(`$INSTANCE_NAME`_SECOND_FINGER_ID, pos);
            #endif /* (0u != `$INSTANCE_NAME`_XY_SECOND_FINGER_FILTER_EN) */
        }
    #endif /* (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK) */

    #if (0u != `$INSTANCE_NAME`_BALLISTIC_EN)
        /* Resets the previous position to remove the jump the first touch */
        if(`$INSTANCE_NAME`_previousFingerNum == 0u)
        {
            `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].x;
            `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].y;

            `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = pos[`$INSTANCE_NAME`_SECOND_FINGER_ID].x;
            `$INSTANCE_NAME`_previousPos[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = pos[`$INSTANCE_NAME`_SECOND_FINGER_ID].y;
        }
    #endif /* (0u != `$INSTANCE_NAME`_BALLISTIC_EN) */

    /* Saves fingerNum */
    `$INSTANCE_NAME`_previousFingerNum = fingerNum;

    return (fingerNum);
}


#if (0u != `$INSTANCE_NAME`_BALLISTIC_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDiffDoubleCentroidPos
********************************************************************************
*
* Summary:
*  This function calculates the difference of the current X,Y co-ordinates
*  and previous co-ordinates. The function applies ballistic multiplier
*  on the actual difference.
*
* Parameters:
*
*  (int16* pos): Pointer to the structure of two int16 elements,
*   where result of calculation of X and Y position are stored:
*  pos[0].x - X position for First Finger;
*  pos[0].y - Y position for First Finger;
*  pos[1].x - X position for Second Finger;
*  pos[1].y - Y position for Second Finger;
*
* Return:
*  uint32: number of finger on the trackpad (max 2), 0 if no finger present.
*  If more than 2 fingers are present, 0xFFFFFFFF should be returned.
*
* Global Variables:
*  None.
*
* Side Effects:
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetDiffDoubleCentroidPos(`$INSTANCE_NAME`_DIFF_POSITION_STRUCT *pos)
{
    uint32 fingerNum;
    uint32 i;
    uint32 previousFingerValue;
    int16 diffPosition[2u*`$INSTANCE_NAME`_MAX_FINGER] =
    {`$INSTANCE_NAME`_POSITION_NO_FINGER,
    `$INSTANCE_NAME`_POSITION_NO_FINGER,
    `$INSTANCE_NAME`_POSITION_NO_FINGER,
    `$INSTANCE_NAME`_POSITION_NO_FINGER};

    /* Save the previous finger value to initialize the difference correctly */
    previousFingerValue = `$INSTANCE_NAME`_previousFingerNum;

    /* Gets the absolute X,Y values */
    fingerNum = `$INSTANCE_NAME`_GetDoubleTouchCentroidPos((`$INSTANCE_NAME`_POSITION_STRUCT*)pos);
    `$INSTANCE_NAME`_ballisticMultiplier.touchNumber = (uint8)fingerNum;

    if(fingerNum != `$INSTANCE_NAME`_POSITION_ERROR)
    {
        for(i = 0u; i < fingerNum; i++)
        {
            /* Calculates the difference between current and previous X */
            diffPosition[(i << 1u)] = pos[i].x - `$INSTANCE_NAME`_previousPos[i].x;
            /* Saves previous X positions */
            `$INSTANCE_NAME`_previousPos[i].x = pos[i].x;

            /* Calculates the difference between current and previous Y */
            diffPosition[(i << 1u) + `$INSTANCE_NAME`_SECOND_FINGER_ID] = pos[i].y - `$INSTANCE_NAME`_previousPos[i].y;
            /* Saves previous Y positions */
            `$INSTANCE_NAME`_previousPos[i].y = pos[i].y;
        }

        /* Reset diffPosition when the finger is pressing the first time */
        if((previousFingerValue == 0u) || (fingerNum == 0u))
        {
            diffPosition[`$INSTANCE_NAME`_FIRST_FINGER_OFFSET + `$INSTANCE_NAME`_DX_ID] = 0u;
            diffPosition[`$INSTANCE_NAME`_FIRST_FINGER_OFFSET + `$INSTANCE_NAME`_DY_ID] = 0u;
        }

        /* Applies the ballistics */
        `$INSTANCE_NAME`_TMG_BallisticsMultiplier(&`$INSTANCE_NAME`_ballisticMultiplier, diffPosition);

        /* Rewrites the output with the new values */
        pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = diffPosition[`$INSTANCE_NAME`_FIRST_FINGER_OFFSET + `$INSTANCE_NAME`_DX_ID];
        pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = diffPosition[`$INSTANCE_NAME`_FIRST_FINGER_OFFSET + `$INSTANCE_NAME`_DY_ID];
        pos[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = diffPosition[`$INSTANCE_NAME`_SECOND_FINGER_OFFSET + `$INSTANCE_NAME`_DX_ID];
        pos[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = diffPosition[`$INSTANCE_NAME`_SECOND_FINGER_OFFSET + `$INSTANCE_NAME`_DY_ID];
    }

    return (fingerNum);
}
#endif /* (0u != `$INSTANCE_NAME`_BALLISTIC_EN) */

#if (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIRXFilter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/X filter function. IIR1/X = 1/X current + (1 - 1/X) previous:
    *  IIR = 1/2 Current Value + 1/2 Previous Value
    *  IIR = 1/4 Current Value + 3/4 Previous Value
    *  IIR = 1/8 Current Value + 7/8 Previous Value
    *  IIR = 1/16 Current Value + 15/16 Previous Value
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *  iirFilterCoef:
    *    1 - X=2;
    *    2 - X=4;
    *    3 - X=8;
    *    4 - X=16;
    *
    * Return:
    *  Returns a filtered value.
    *
    * Global Variables:
    *  None.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIRXFilter(uint16 x1, uint16 x2, uint32 iirFilterCoef)
    {
        uint32 tmp;

        tmp = (uint32)x1;
        tmp += (((uint32)x2 << iirFilterCoef) - ((uint32)x2));
        tmp >>= iirFilterCoef;

        return ((uint16) tmp);
    }
#endif /* (0u != (`$INSTANCE_NAME`_XY_IIR_MASK & \
        *          `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
        */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GettrackpadValueZ
********************************************************************************
*
* Summary:
*  This API returns the Trackpad Z value which correspond to Finger area.
*
* Parameters:
*   uint32: axisID. 0 - X axis, 1 - Y axis
*   uint32: fingerID - finger Number. 0 - first finger , 1 - second finger.
*
* Return:
*  Trackpad Z value
*
* Global Variables:
*  `$INSTANCE_NAME`_trackpadFingerPosZ[]  - stores the Z value.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetTrackpadValueZ(uint32 axisID, uint32 fingerID)
{
    /* Calculates finger offset relatively to axisID: */
    /* X0, Y0, X1, Y1 */
    fingerID <<= 1u;

    return(`$INSTANCE_NAME`_trackpadFingerPosZ[axisID + fingerID]);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Get16bitDiffCountData
********************************************************************************
*
* Summary:
*  This function returns the 16 bit Sensor Signal from the component.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns the difference count value of the sensor indicated by the
*  argument.
*
* Global Variables:
*  CapSense_sensorSignal[] - the array with difference counts for sensors
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_Get16bitDiffCountData(uint32 sensor)
{
    return ((uint16)`$INSTANCE_NAME`_GetDiffCountData(sensor));
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Get16bitFingerThreshold
********************************************************************************
*
* Summary:
*  This function reads the 16 bit finger threshold from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the finger threshold of the widget indicated by the argument.
*
* Global Variables:
*  CapSense_fingerThreshold[] - This array contains the level of signal
*  for each widget that is determined if a finger is present on the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_Get16bitFingerThreshold(uint32 widget)
{
    return((uint16)`$INSTANCE_NAME`_GetFingerThreshold(widget));
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Get16bitNoiseThreshold
********************************************************************************
*
* Summary:
*  This function reads the 16 bit noise threshold from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the noise threshold of the widget indicated by the argument.
*
* Global Variables:
*  CapSense_noiseThreshold[] - This array contains the level of signal
*  for each widget that determines the level of noise in the capacitive scan.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_Get16bitNoiseThreshold(uint32 widget)
{
    return ((uint16)`$INSTANCE_NAME`_GetNoiseThreshold(widget));
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DecodeAllGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures in the customizer and returns the detected
*  gesture code.
*  CapSense_TMG_InitGestures and CapSense_TMG_TimerEnableInt has to be
*  called once prior calling this or any other API for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: pointer to structure with coordinates of touches
*
* Return:
*  Detected gesture code:
*
*  NO_GESTURE   0x00
*  ST_CLICK 0x20
*  ST_DOUBLECLICK   0x22
*  ST_CLICKANDDRAG  0x24
*  ROTATE_CW    0x28
*  ROTATE_CCW   0x29
*  TOUCHDOWN    0x2F
*  ST_SCROLL_NORTH  0xC0
*  ST_SCROLL_SOUTH  0xC2
*  ST_SCROLL_WEST   0xC4
*  ST_SCROLL_EAST   0xC6
*  ST_INERTIAL_SCROLL_NORTH 0xB0
*  ST_INERTIAL_SCROLL_SOUTH 0xB2
*  ST_INERTIAL_SCROLL_WEST  0xB4
*  ST_INERTIAL_SCROLL_EAST  0xB6
*  DT_SCROLL_NORTH  0xC8
*  DT_SCROLL_SOUTH  0XCA
*  DT_SCROLL_WEST   0XCC
*  DT_SCROLL_EAST   0XCE
*  DT_INERTIAL_SCROLL_NORTH 0XB8
*  DT_INERTIAL_SCROLL_SOUTH 0XBA
*  DT_INERTIAL_SCROLL_WEST  0XBC
*  DT_INERTIAL_SCROLL_EAST  0xBE
*  DT_CLICK 0x40
*  ZOOM_IN  0x48
*  ZOOM_OUT 0x49
*  LIFT_OFF 0x4F
*  FLICK_NORTH  0x50
*  FLICK_NORTH_EAST 0x52
*  FLICK_EAST   0x54
*  FLICK_SOUTH_EAST 0x56
*  FLICK_SOUTH  0x58
*  FLICK_SOUTH_WEST 0x5A
*  FLICK_WEST   0x5C
*  FLICK_NORTH_WEST 0x5E
*  EDGE_SWIPE_LEFT  0xA0
*  EDGE_SWIPE_RIGHT 0xA2
*  EDGE_SWIPE_TOP   0xA4
*  EDGE_SWIPE_BOTTOM    0xA6
*  INVALID_COORDINATE   0xFFFF
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_DecodeAllGestures(uint32 touchNumber, const `$INSTANCE_NAME`_POSITION_STRUCT *pos)
{
    uint32 gestureID;
    #if (0u != `$INSTANCE_NAME`_EDGE_SWIPE_GEST_ENABLED)
        static uint32 gestureCounter = 0u;
    #endif /* (0u != `$INSTANCE_NAME`_EDGE_SWIPE_GEST_ENABLED) */

    /* Checks if Number of fingers is less than three */
    if(`$INSTANCE_NAME`_FINGER_ERROR != (uint8)touchNumber)
    {
        gestureID = `$INSTANCE_NAME`_TMG_DecodeAllGestures(touchNumber, (const `$INSTANCE_NAME`_TMG_POSITION_STRUCT*)pos);

        #if (0u != `$INSTANCE_NAME`_EDGE_SWIPE_GEST_ENABLED)
            /* Checks if the gesture is EGDE SWIPE */
            if ((gestureID & 0xF0u) == `$INSTANCE_NAME`_EDGE_SWIPE_MASK)
            {
                /* Set flag that the gesture is EGDE SWIPE */
                gestureCounter = `$INSTANCE_NAME`_EDGE_SWIPE_MASK;
            }
            else if((gestureCounter == `$INSTANCE_NAME`_EDGE_SWIPE_MASK) && (gestureID == `$INSTANCE_NAME`_TOUCHDOWN))
            {
                /* Set flag that the gesture is EGDE SWIPE after the TOUCHDOWN event only*/
                gestureCounter = 0u;
            }
            else
            {
                /* There was not EDGE SWIPE gestures */
            }

            /* Checks if the gesture is INERTIAL_SCROLL and the TOUCHDOWN event has not taken place before */
            if((gestureID >= `$INSTANCE_NAME`_ST_INERTIAL_SCROLL_NORTH) && (gestureID <= `$INSTANCE_NAME`_ST_INERTIAL_SCROLL_EAST) && (gestureCounter > 0u))
            {
                /* Block INERTIAL_SCROLL detecting */
                gestureID = `$INSTANCE_NAME`_NO_GESTURE;
            }
        #endif /* (0u != `$INSTANCE_NAME`_EDGE_SWIPE_GEST_ENABLED) */
    }
    else
    {
        gestureID = `$INSTANCE_NAME`_NO_GESTURE;
    }

    return (gestureID);
}

#endif /* (`$INSTANCE_NAME`_TRACKPADS_WITH_GESTURES > 0u) */


/* [] END OF FILE */
