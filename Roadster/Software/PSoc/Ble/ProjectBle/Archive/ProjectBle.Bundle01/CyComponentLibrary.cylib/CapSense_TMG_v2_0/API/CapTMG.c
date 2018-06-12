/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of the API for the CapSense TMG component.
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DecodeAllGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures in the customizer and returns the detected
*  gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior calling this or any other API for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  currentTimestamp : Current timestamp value.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  Detected gesture code.
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_DecodeAllGestures(uint32_t touchNumber, uint32_t currentTimestamp, const `$INSTANCE_NAME`_POSITION_STRUCT *pos)
{
    uint32_t gestureID = `$INSTANCE_NAME`_NO_GESTURE;
    #if(0u != `$INSTANCE_NAME`_GESTURES_ENABLED)
        /* Variable for detected click gestures */
        uint32_t clickGesture = `$INSTANCE_NAME`_NO_GESTURE;

        /* Variable for detected single touch gestures */
        uint32_t stGesture = `$INSTANCE_NAME`_NO_GESTURE;

        /* Variable for detected double touch gestures */
        uint32_t dtGesture = `$INSTANCE_NAME`_NO_GESTURE;

        #if (`$INSTANCE_NAME`_ROTATE_ENABLED != 0u)
            static uint32_t rotationActive = 0u;
        #endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED != 0u) */

        #if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)
            static uint32_t edgeTimeoutStamp = 0u;
            uint32_t deltaTimeoutStamp = 0u;
        #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u) */

        #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                             (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                             (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
            static uint32_t edgeSwipeActive = 0u;
        #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                                   (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                                   (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */

        #if ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                         (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                         (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
            static uint32_t clickAndDragActive = 0u;
        #endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                               (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                               (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */

        #if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
            uint32_t edgeSwipeGesture = `$INSTANCE_NAME`_NO_GESTURE;
        #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) */

        #if ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u))
            clickGesture = Gesture_DecodeAllClickGestures((uint8_t)touchNumber, currentTimestamp, pos);
        #endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)) */

        #if (`$INSTANCE_NAME`_CLICKS_ENABLED != 0u)
            gestureID = clickGesture;
            #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) || (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u))
            if (clickGesture == `$INSTANCE_NAME`_CLICK_AND_DRAG)
            {
                clickAndDragActive = 1u;
            }
            #endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) || (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)) */
        #endif /* (`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) */

        #if (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)
            stGesture = Gesture_DecodeSTRotateGestures((uint8_t)touchNumber, currentTimestamp, pos);

            #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) || (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u))
                #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u))
                    if ((clickAndDragActive == 1u) || (edgeSwipeActive == 1u))
                #elif (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)
                    if (clickAndDragActive == 1u)
                #elif (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
                    if (edgeSwipeActive == 1u)
                #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)) */
                {
                    stGesture = `$INSTANCE_NAME`_NO_GESTURE;
                }
            #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) || (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)) */
            if ((stGesture == `$INSTANCE_NAME`_ROTATE_CW) || (stGesture == `$INSTANCE_NAME`_ROTATE_CCW))
            {
                rotationActive = `$INSTANCE_NAME`_ROTATE_TO_OTHER_DEBOUNCE;
            }
            else
            {
                if (rotationActive > 0u)
                {
                    rotationActive--;
                }
            }

            if (((stGesture == `$INSTANCE_NAME`_NO_GESTURE)||(stGesture == `$INSTANCE_NAME`_TOUCHDOWN) \
                                            ||(stGesture == `$INSTANCE_NAME`_LIFT_OFF))&&(rotationActive == 0u))
        #else
            if ((stGesture == `$INSTANCE_NAME`_NO_GESTURE)||(stGesture == `$INSTANCE_NAME`_TOUCHDOWN) \
                                            ||(stGesture == `$INSTANCE_NAME`_LIFT_OFF))
        #endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u) */
        {
            #if (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)
                #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u))
                    if ((clickAndDragActive == 0u)&&(edgeSwipeActive == 0u))
                #elif (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)
                    if (clickAndDragActive == 0u)
                #elif (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
                    if (edgeSwipeActive == 0u)
                #else
                    if (1u == 1u)
                #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)) */
                {
                    stGesture = Gesture_DecodeSTScrollGestures((uint8_t)touchNumber, currentTimestamp, pos);
                }
            #elif (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u)
                stGesture = Gesture_DecodeFlickGestures((uint8_t)touchNumber, currentTimestamp, pos);
            #endif /* (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) */
        }

        #if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
            edgeSwipeGesture = Gesture_DecodeEdgeSwipeGestures((uint8_t)touchNumber, currentTimestamp, pos);

            #if (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)
                if (((edgeSwipeGesture != `$INSTANCE_NAME`_NO_GESTURE) && \
                    (edgeSwipeGesture != `$INSTANCE_NAME`_TOUCHDOWN) && (edgeSwipeGesture != `$INSTANCE_NAME`_LIFT_OFF)) \
                                                                                            && (rotationActive == 0u))
            #else
                if ((edgeSwipeGesture != `$INSTANCE_NAME`_NO_GESTURE) && \
                    (edgeSwipeGesture != `$INSTANCE_NAME`_TOUCHDOWN) && (edgeSwipeGesture != `$INSTANCE_NAME`_LIFT_OFF))
            #endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u) */
            {
                stGesture = edgeSwipeGesture;
                #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                                     (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                                     (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
                    edgeSwipeActive = 1u;
                #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                                           (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                                           (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */
            }
        #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) */

        if ((stGesture != `$INSTANCE_NAME`_NO_GESTURE)&&(stGesture != `$INSTANCE_NAME`_TOUCHDOWN) \
                                            &&(stGesture != `$INSTANCE_NAME`_LIFT_OFF))
        {
            gestureID = stGesture;
        }
        else if ((clickGesture == `$INSTANCE_NAME`_TOUCHDOWN) || (clickGesture == `$INSTANCE_NAME`_LIFT_OFF))
        {
            #if(`$INSTANCE_NAME`_CLICKS_ENABLED != 0u)
                gestureID = clickGesture;
            #else
                gestureID = `$INSTANCE_NAME`_NO_GESTURE;
            #endif /* (`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) */
        }
        else
        {
            /* Do not change gestureID */
        }

        dtGesture = `$INSTANCE_NAME`_DecodeZoomGestures(touchNumber, currentTimestamp, pos);
        if ((dtGesture == `$INSTANCE_NAME`_NO_GESTURE) || (dtGesture == `$INSTANCE_NAME`_TOUCHDOWN) \
                                            || (dtGesture == `$INSTANCE_NAME`_LIFT_OFF))
        {
            dtGesture = `$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber, currentTimestamp, pos);
        }
        else
        {
            (void)`$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber, currentTimestamp, pos);
        }

        if ((dtGesture != `$INSTANCE_NAME`_NO_GESTURE) && (dtGesture != `$INSTANCE_NAME`_TOUCHDOWN) \
                                            && (dtGesture != `$INSTANCE_NAME`_LIFT_OFF))
        {
            gestureID = dtGesture;
        }

        #if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)
            if((gestureID >= `$INSTANCE_NAME`_EDGE_SWIPE_LEFT)&&(gestureID <= `$INSTANCE_NAME`_EDGE_SWIPE_BOTTOM))
            {
                edgeTimeoutStamp = currentTimestamp;
            }
        #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u) */

        if ((clickGesture == `$INSTANCE_NAME`_LIFT_OFF) || (clickGesture == `$INSTANCE_NAME`_TOUCHDOWN) || \
                (gestureID == `$INSTANCE_NAME`_NO_GESTURE))
        {
            #if ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                             (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                             (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
                if(0u != clickAndDragActive)
                {
                    clickAndDragActive = 0u;
                }
            #endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                                   (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                                   (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */

            #if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)
            deltaTimeoutStamp = currentTimestamp - edgeTimeoutStamp;
            if ((clickGesture == `$INSTANCE_NAME`_LIFT_OFF) || (deltaTimeoutStamp >= `$INSTANCE_NAME`_EDGE_SWIPE_COMPLETE_TIMEOUT))
            {
                edgeTimeoutStamp = 0u;
                #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) || \
                                                                            (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)))
                    if(0u != edgeSwipeActive)
                    {
                        edgeSwipeActive = 0u;
                    }

                #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) || \
                                                                            (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u))) */
            }
            #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u) */
        }
    #endif /* (0u != `$INSTANCE_NAME`_GESTURES_ENABLED) */

    return (gestureID);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ballisticsMultiplier
********************************************************************************
*
* Summary:
*  This API is to run the ballistic Multiplier.
*  `$INSTANCE_NAME`_TimerEnableInt has to be called once prior calling this API.
*
* Parameters:
*   ballisticMultiplier: Pointer to the structure which contains API parameters.
*   currentTimestamp : Current timestamp value.
*   pos: Pointer to dX and dY coordinates.
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_BallisticsMultiplier(const `$INSTANCE_NAME`_BALLISTIC_MULT * ballisticMultiplier, uint32_t currentTimestamp, int16_t *pos)
{
    #if (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u)
        `$INSTANCE_NAME`_BALLISTIC_MULT_INT ballisticsStrct;
        ballisticsStrct.paramStr = *ballisticMultiplier;
        ballisticsStrct.currentTimestamp = currentTimestamp;
        BallisticMultiplier(&ballisticsStrct, pos);
    #endif /* (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u) */
}


/* [] END OF FILE */
