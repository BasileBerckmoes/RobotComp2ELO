/***************************************************************************//**
* \file `$INSTANCE_NAME`_Gesture.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the source code for the centroid calculation methods
*   of the Component.
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

#include "syslib/cy_syslib.h"
#include <stddef.h>
#include "systick/cy_systick.h"
#include "`$INSTANCE_NAME`_Gesture.h"

#define `$INSTANCE_NAME`_CSX_ERROR_TOUCH_NUMBER     (3u)


/***********************************************************************************************************************
* Static Function Prototypes
***********************************************************************************************************************/
/**
* \cond SECTION_CYSENSE_INTERNAL
* \addtogroup group_cysense_internal
* \{
*/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SLIDER_WIDGET_EN)
    __STATIC_INLINE void `$INSTANCE_NAME`_GetCsdSldTouches(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SLIDER_WIDGET_EN) */

    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
    __STATIC_INLINE void `$INSTANCE_NAME`_GetCsdTpTouches(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN)
    __STATIC_INLINE void `$INSTANCE_NAME`_GetCsxTpTouches(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN)
    static uint8  `$INSTANCE_NAME`_bmPrevFingerNum;
    static `$INSTANCE_NAME`_TMG_POSITION_STRUCT `$INSTANCE_NAME`_bmPrevFingerPos;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN) */

#if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
    static `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT `$INSTANCE_NAME`_touchParams;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN) */


/** \}
* \endcond */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetTouchParams
    ****************************************************************************//**
    *
    * \brief
    *  This function is intended to get the number of touches on touchpar or slider,
    *  position of each touch and the max number of touches which can be processed
    *  to recognize gestures.
    *
    * \details
    *  This function implements call of appropriate API to get the touch parameters
    *  depending on the type of widget, that is passed through the wdgtId nparameter.
    *  For the CSD touchpad and the CSX touchpad, function returns X and Y coordinates
    *  of each touch.
    *  For the CSD slider, functions returns the position as the X coordinate.
    *  Y coordinate for CSD sliders is always "0".
    *  This is an internal function. Calling this function from application layer is
    *  not recommended.
    *
    * \param wdgtIndex
    *  Specifies the ID number of the widget, the touch parameters needs to be
    *  returned for.
    *
    * \param touchParams
    *  Pointer to the structure which is intended to store the number of touches,
    *  position of each touch and the max number of touches which can be processed
    *  to recognize gestures for widget, that is passed through the wdgtId nparameter.
    *
    *******************************************************************************/
    void  `$INSTANCE_NAME`_GetTouchParams(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams)
    {
        `$INSTANCE_NAME`_WD_TYPE_ENUM widgetType;
        `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;

        ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex];
        widgetType = `$INSTANCE_NAME`_GET_WIDGET_TYPE(ptrFlashWdgt);

        switch(widgetType)
        {

        #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SLIDER_WIDGET_EN)
            case `$INSTANCE_NAME`_WD_LINEAR_SLIDER_E:
            case `$INSTANCE_NAME`_WD_RADIAL_SLIDER_E:
                `$INSTANCE_NAME`_GetCsdSldTouches(wdgtIndex, touchParams);
                break;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SLIDER_WIDGET_EN) */

        #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN)
            case `$INSTANCE_NAME`_WD_TOUCHPAD_E:
                #if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
                    {
                        `$INSTANCE_NAME`_GetCsdTpTouches(wdgtIndex, touchParams);
                    }
                #endif /* #if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
                #if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN)
                    if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
                    {
                       `$INSTANCE_NAME`_GetCsxTpTouches(wdgtIndex, touchParams);
                    }
                #endif /* #if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN) */
                break;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN) */

        default:
            CY_ASSERT(0 != 0);
            break;
        }
    }


    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SLIDER_WIDGET_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_GetCsdSldTouches
        ****************************************************************************//**
        *
        * \brief
        *  This function is intended to get the number of touches on CSD slider, the
        *  position of each touch and the max number of touches which can be processed
        *  to recognize gestures.
        *
        * \details
        *  This function implements calculation of the number of touches on CSD slider,
        *  getting coordinates of each touch and the max number of touches which can be
        *  processed to recognize gestures for the current CSD slider configuration.
        *  Functions returns the slider touch position as the X coordinate. Y coordinate
        *  for CSD sliders is always "0".
        *  This is an internal function. Calling this function from application layer is
        *  not recommended.
        *
        * \param wdgtIndex
        *  Specifies the ID number of the widget, the touch parameters needs to be
        *  returned for.
        *
        * \param touchParams
        *  Pointer to the structure which is intended to store the number of touches,
        *  position of each touch and the max number of touches which can be processed
        *  to recognize gestures for widget, that is passed through the wdgtId nparameter.
        *
        *******************************************************************************/
        __STATIC_INLINE void `$INSTANCE_NAME`_GetCsdSldTouches(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams)
        {
            uint32 tmpVal;
            `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;
            `$INSTANCE_NAME`_RAM_WD_SLIDER_STRUCT *ptrRamWdgtSld;

            ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex];
            ptrRamWdgtSld = (`$INSTANCE_NAME`_RAM_WD_SLIDER_STRUCT*)ptrFlashWdgt->ptr2WdgtRam;

            touchParams->touchNumber = 0uL;
            for(tmpVal = 0uL; tmpVal < `$INSTANCE_NAME`_NUM_CENTROIDS; tmpVal++)
            {
                if(ptrRamWdgtSld->position[tmpVal] != `$INSTANCE_NAME`_SLIDER_POS_NONE)
                {
                    touchParams->touchNumber += 1uL;
                }
            }

            touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = ptrRamWdgtSld->position[`$INSTANCE_NAME`_FIRST_FINGER_ID];
            touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = 0u;

            #if(`$INSTANCE_NAME`_NUM_CENTROIDS > 1u)
                touchParams->maxTouchNumber = 2u;
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = ptrRamWdgtSld->position[`$INSTANCE_NAME`_SECOND_FINGER_ID];
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = 0u;
            #else
                touchParams->maxTouchNumber = 1u;
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = `$INSTANCE_NAME`_SLIDER_POS_NONE;
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = `$INSTANCE_NAME`_SLIDER_POS_NONE;
            #endif /* (2u == `$INSTANCE_NAME`_NUM_CENTROIDS) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SLIDER_WIDGET_EN) */


    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_GetCsdTpTouches
        ****************************************************************************//**
        *
        * \brief
        *  This function is intended to get the number of touches on CSD touchpad, the
        *  position of each touch and the max number of touches which can be processed
        *  to recognize gestures.
        *
        * \details
        *  This function implements calculation of the number of touches on CSD touchpad,
        *  getting coordinates of each touch and the max number of touches which can be
        *  processed to recognize gestures for the current CSD touchpad configuration.
        *  Functions returns the X and Y coordinates of each touch.
        *  This is an internal function. Calling this function from application layer is
        *  not recommended.
        *
        * \param wdgtIndex
        *  Specifies the ID number of the widget, the touch parameters needs to be
        *  returned for.
        *
        * \param touchParams
        *  Pointer to the structure which is intended to store the number of touches,
        *  position of each touch and the max number of touches which can be processed
        *  to recognize gestures for widget, that is passed through the wdgtId nparameter.
        *
        *******************************************************************************/
        __STATIC_INLINE void `$INSTANCE_NAME`_GetCsdTpTouches(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams)
        {
            uint16 tmpPosX;
            uint16 tmpPosY;

            `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;
            `$INSTANCE_NAME`_RAM_WD_CSD_TOUCHPAD_STRUCT *ptrRamWdgtTp;

            ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex];
            ptrRamWdgtTp = (`$INSTANCE_NAME`_RAM_WD_CSD_TOUCHPAD_STRUCT*)ptrFlashWdgt->ptr2WdgtRam;

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN)
                if (0 != (ptrFlashWdgt->staticConfig & `$INSTANCE_NAME`_CENTROID_5X5_MASK))
                {
                    touchParams->maxTouchNumber = 2u;
                    touchParams->touchNumber = ptrRamWdgtTp->position.touchNum;

                    tmpPosX = ptrRamWdgtTp->position.pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].x;
                    touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = tmpPosX;

                    /* Cypress ID: #233241 */
                    tmpPosY = ptrRamWdgtTp->position.pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].y;
                    tmpPosY = (tmpPosY != `$INSTANCE_NAME`_TOUCHPAD_POS_NONE) ? (ptrFlashWdgt->yResolution - tmpPosY) : tmpPosY;
                    touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = tmpPosY;

                    tmpPosX = ptrRamWdgtTp->position.pos[`$INSTANCE_NAME`_SECOND_FINGER_ID].x;
                    touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = tmpPosX;

                    tmpPosY = ptrRamWdgtTp->position.pos[`$INSTANCE_NAME`_SECOND_FINGER_ID].y;
                    tmpPosY = (tmpPosY != `$INSTANCE_NAME`_TOUCHPAD_POS_NONE) ? (ptrFlashWdgt->yResolution - tmpPosY) : tmpPosY;
                    touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = tmpPosY;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_3X3_CSD_EN)
                if (0u != (ptrFlashWdgt->staticConfig & `$INSTANCE_NAME`_CENTROID_3X3_MASK))
                {
                    if((`$INSTANCE_NAME`_TOUCHPAD_POS_NONE != ptrRamWdgtTp->posX) && (`$INSTANCE_NAME`_TOUCHPAD_POS_NONE != ptrRamWdgtTp->posY))
                    {
                        touchParams->touchNumber = 1u;
                    }
                    else
                    {
                        touchParams->touchNumber = 0u;
                    }

                    touchParams->maxTouchNumber = 1u;
                    tmpPosX = ptrRamWdgtTp->posX;
                    touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = tmpPosX;

                    /* Cypress ID: #233241 */
                    tmpPosY = ptrRamWdgtTp->posY;
                    tmpPosY = (tmpPosY != `$INSTANCE_NAME`_TOUCHPAD_POS_NONE) ? (ptrFlashWdgt->yResolution - tmpPosY) : tmpPosY;
                    touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = tmpPosY;

                    touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = `$INSTANCE_NAME`_TOUCHPAD_POS_NONE;
                    touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = `$INSTANCE_NAME`_TOUCHPAD_POS_NONE;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_3X3_CSD_EN) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */


    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_GetCsxTpTouches
        ****************************************************************************//**
        *
        * \brief
        *  This function is intended to get the number of touches on CSX touchpad, the
        *  position of each touch and the max number of touches which can be processed
        *  to recognize gestures.
        *
        * \details
        *  This function implements calculation of the number of touches on CSX touchpad,
        *  getting coordinates of each touch and the max number of touches which can be
        *  processed to recognize gestures for the current CSX touchpad configuration.
        *  Functions returns the X and Y coordinates of each touch.
        *  This is an internal function. Calling this function from application layer is
        *  not recommended.
        *
        * \param wdgtIndex
        *  Specifies the ID number of the widget, the touch parameters needs to be
        *  returned for.
        *
        * \param touchParams
        *  Pointer to the structure which is intended to store the number of touches,
        *  position of each touch and the max number of touches which can be processed
        *  to recognize gestures for widget, that is passed through the wdgtId nparameter.
        *
        *******************************************************************************/
        __STATIC_INLINE void `$INSTANCE_NAME`_GetCsxTpTouches(uint32 wdgtIndex, `$INSTANCE_NAME`_TOUCH_PARAM_STRUCT *touchParams)
        {
            uint8 error;
            uint8 index;

            uint16 tmpPosX;
            uint16 tmpPosY;

            static uint8 prevTouchNumber = 0u;
            static uint8 prevTouchId[`$INSTANCE_NAME`_CSX_MAX_FINGERS];

            `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;
            `$INSTANCE_NAME`_RAM_WD_CSX_TOUCHPAD_STRUCT *ptrRamWdgtTp;

            ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex];
            ptrRamWdgtTp = (`$INSTANCE_NAME`_RAM_WD_CSX_TOUCHPAD_STRUCT*)ptrFlashWdgt->ptr2WdgtRam;

            touchParams->touchNumber = `$INSTANCE_NAME`_dsRam.snsStatus[wdgtIndex];

            tmpPosX = ptrRamWdgtTp->touch[`$INSTANCE_NAME`_FIRST_FINGER_ID].x;
            touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = tmpPosX;

            /* Cypress ID: #233241 */
            tmpPosY = ptrRamWdgtTp->touch[`$INSTANCE_NAME`_FIRST_FINGER_ID].y;
            tmpPosY = (tmpPosY != `$INSTANCE_NAME`_TOUCHPAD_POS_NONE) ? (ptrFlashWdgt->yResolution - tmpPosY) : tmpPosY;
            touchParams->currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = tmpPosY;

            #if(`$INSTANCE_NAME`_CSX_MAX_FINGERS > 1u)
                touchParams->maxTouchNumber = 2u;
                tmpPosX = ptrRamWdgtTp->touch[`$INSTANCE_NAME`_SECOND_FINGER_ID].x;
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = tmpPosX;

                /* Cypress ID: #233241 */
                tmpPosY = ptrRamWdgtTp->touch[`$INSTANCE_NAME`_SECOND_FINGER_ID].y;
                tmpPosY = (tmpPosY != `$INSTANCE_NAME`_TOUCHPAD_POS_NONE) ? (ptrFlashWdgt->yResolution - tmpPosY) : tmpPosY;
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = tmpPosY;
            #else
                touchParams->maxTouchNumber = 1u;
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = `$INSTANCE_NAME`_TOUCHPAD_POS_NONE;
                touchParams->currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = `$INSTANCE_NAME`_TOUCHPAD_POS_NONE;
            #endif /* (`$INSTANCE_NAME`_CSX_MAX_FINGERS > 1u) */

            error = 0u;
            #if (`$INSTANCE_NAME`_CSX_MAX_FINGERS == 1u)
                if((touchParams->touchNumber == 1u) && (prevTouchNumber == 1u))
                {
                    if(prevTouchId[0u] != ptrRamWdgtTp->touch[0u].id)
                    {
                        error++;
                    }
                }
            #else
                if (touchParams->touchNumber == 1u)
                {
                    if (prevTouchNumber == 1u)
                    {
                        if (prevTouchId[0u] != ptrRamWdgtTp->touch[0u].id)
                        {
                            error++;
                        }
                    }
                    else if (prevTouchNumber > 1u)
                    {
                        if ((prevTouchId[0u] != ptrRamWdgtTp->touch[0u].id) &&
                            (prevTouchId[1u] != ptrRamWdgtTp->touch[0u].id))
                        {
                            error++;
                        }
                    }
                }
                else if (touchParams->touchNumber == 2u)
                {
                    if (prevTouchNumber > 0u)
                    {
                        if (prevTouchId[0u] != ptrRamWdgtTp->touch[0u].id)
                        {
                            error++;
                        }
                        else if (prevTouchNumber > 1u)
                        {
                            if (prevTouchId[1u] != ptrRamWdgtTp->touch[1u].id)
                            {
                                error++;
                            }
                        }
                    }
                }
            #endif

            prevTouchNumber = touchParams->touchNumber;
            for (index = 0u; index < `$INSTANCE_NAME`_CSX_MAX_FINGERS; index++)
            {
                prevTouchId[index] = ptrRamWdgtTp->touch[index].id;
            }

            if (error != 0u)
            {
                touchParams->touchNumber = `$INSTANCE_NAME`_CSX_ERROR_TOUCH_NUMBER;
            }
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeGestures
****************************************************************************//**
*
* \brief
*  This function is intended to initialize the internal parameters of the
*  Gestures IP.
*
* \details
*  This routine initializes gesture parameters internal to the gesture
*  algorithm. It has to be called once prior to call any API or macro which
*  decodes gestures.
*  This is an internal function. Calling this function from application layer is
*  not recommended.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeGestures(void)
{
    `$INSTANCE_NAME`_dsRam.timestamp = 0uL;

    #if(0u != `$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
        `$INSTANCE_NAME`_touchParams.touchNumber = 0u;
        `$INSTANCE_NAME`_touchParams.maxTouchNumber = 0u;
        `$INSTANCE_NAME`_touchParams.touchState = `$INSTANCE_NAME`_TOUCH_VALID;

        `$INSTANCE_NAME`_touchParams.currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].x = `$INSTANCE_NAME`_TMG_INVALID_COORDINATE;
        `$INSTANCE_NAME`_touchParams.currentPosition[`$INSTANCE_NAME`_FIRST_FINGER_ID].y = `$INSTANCE_NAME`_TMG_INVALID_COORDINATE;

        `$INSTANCE_NAME`_touchParams.currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].x = `$INSTANCE_NAME`_TMG_INVALID_COORDINATE;
        `$INSTANCE_NAME`_touchParams.currentPosition[`$INSTANCE_NAME`_SECOND_FINGER_ID].y = `$INSTANCE_NAME`_TMG_INVALID_COORDINATE;

        `$INSTANCE_NAME`_TMG_InitGestures(&`$INSTANCE_NAME`_dsRam.gestures);
    #endif
}


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DecodeWidgetGestures
    ****************************************************************************//**
    *
    * \brief
    *  Decodes all enabled gestures for the specified widget and returns the
    *  gesture code.
    *
    * \details
    *  This function decodes all the enabled gestures on a specific widget and
    *  returns a code for the detected gesture. Refer to the Gesture tab section
    *  for more details on supported Gestures.
    *
    *  This function is called only after scan and data processing are completed
    *  for the specified widget.
    *
    *  The Timestamp must be updated before calling this function using the
    *  `$INSTANCE_NAME`_IncrementGestureTimestamp() function.
    *
    * \param wdgtIndex
    *  Specifies the ID number of the widget to decode the gesture. A macro for the
    *  widget ID can be found in the `$INSTANCE_NAME` Configuration header file
    *  defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
    *
    * \return
    *  Returns the status of the gesture detection or the detected gesture code:
    *    - `$INSTANCE_NAME`_NON_VALID_PARAMETER
    *    - `$INSTANCE_NAME`_NO_GESTURE
    *    - `$INSTANCE_NAME`_UNRECOGNIZED_GESTURE
    *    - `$INSTANCE_NAME`_ONE_FINGER_TOUCHDOWN
    *    - `$INSTANCE_NAME`_ONE_FINGER_LIFT_OFF
    *    - `$INSTANCE_NAME`_ONE_FINGER_SINGLE_CLICK
    *    - `$INSTANCE_NAME`_ONE_FINGER_DOUBLE_CLICK
    *    - `$INSTANCE_NAME`_ONE_FINGER_CLICK_AND_DRAG
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_UP
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_DOWN
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_RIGHT
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_LEFT
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_UP
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_DOWN
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_RIGHT
    *    - `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_LEFT
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_UP
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_DOWN
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_RIGHT
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_LEFT
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_UP_RIGHT
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_DOWN_RIGHT
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_DOWN_LEFT
    *    - `$INSTANCE_NAME`_ONE_FINGER_FLICK_UP_LEFT
    *    - `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_UP
    *    - `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_DOWN
    *    - `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_RIGTH
    *    - `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_LEFT
    *    - `$INSTANCE_NAME`_ONE_FINGER_ROTATE_CW
    *    - `$INSTANCE_NAME`_ONE_FINGER_ROTATE_CCW
    *    - `$INSTANCE_NAME`_TWO_FINGER_SINGLE_CLICK
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_UP
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_DOWN
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_RIGHT
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_LEFT
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_UP
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_DOWN
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_RIGHT
    *    - `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_LEFT
    *    - `$INSTANCE_NAME`_TWO_FINGER_ZOOM_IN
    *    - `$INSTANCE_NAME`_TWO_FINGER_ZOOM_OUT
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_DecodeWidgetGestures(uint32 widgetId)
    {
        uint32 tmpValue;

        #if (0u != `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_EN)
            static uint32 gestureCounter = 0u;
        #endif

        if(widgetId != `$INSTANCE_NAME`_GESTURE_EN_WIDGET_ID)
        {
            tmpValue = `$INSTANCE_NAME`_NON_VALID_PARAMETER;
        }
        else
        {
            `$INSTANCE_NAME`_GetTouchParams(widgetId, &`$INSTANCE_NAME`_touchParams);

            switch (`$INSTANCE_NAME`_touchParams.touchState)
            {
            case `$INSTANCE_NAME`_TOUCH_UNRECOGNIZED:
                if (`$INSTANCE_NAME`_touchParams.touchNumber == 0u)
                {
                    `$INSTANCE_NAME`_touchParams.touchState = `$INSTANCE_NAME`_TOUCH_VALID;
                    `$INSTANCE_NAME`_TMG_InitGestures(&`$INSTANCE_NAME`_dsRam.gestures);
                    tmpValue = `$INSTANCE_NAME`_NO_GESTURE;
                }
                else
                {
                    tmpValue = `$INSTANCE_NAME`_UNRECOGNIZED_GESTURE;
                }
                break;

            case `$INSTANCE_NAME`_TOUCH_VALID:
                if (`$INSTANCE_NAME`_touchParams.touchNumber > `$INSTANCE_NAME`_touchParams.maxTouchNumber)
                {
                    `$INSTANCE_NAME`_touchParams.touchState = `$INSTANCE_NAME`_TOUCH_UNRECOGNIZED;
                    tmpValue = `$INSTANCE_NAME`_UNRECOGNIZED_GESTURE;
                }
                else
                {
                    tmpValue = `$INSTANCE_NAME`_TMG_DecodeAllGestures((uint32)`$INSTANCE_NAME`_touchParams.touchNumber,
                                                                      `$INSTANCE_NAME`_dsRam.timestamp, `$INSTANCE_NAME`_touchParams.currentPosition);

                    #if (0u != `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_EN)
                        /* Checks if the gesture is EGDE SWIPE */
                        if (`$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_GROUP == (tmpValue & `$INSTANCE_NAME`_GESTURE_GROUP_MASK))
                        {
                            /* Set flag that the gesture is EGDE SWIPE */
                            gestureCounter = `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_GESTURE;
                        }
                        else if((gestureCounter == `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_GESTURE) && (tmpValue == `$INSTANCE_NAME`_ONE_FINGER_TOUCHDOWN))
                        {
                            /* Set flag that the gesture is EGDE SWIPE after the TOUCHDOWN event only */
                            gestureCounter = 0u;
                        }
                        else
                        {
                            /* There was not EDGE SWIPE gestures */
                        }

                        /* Checks if the gesture is INERTIAL_SCROLL and the TOUCHDOWN event has not taken place before */
                        if((tmpValue >= `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_UP) &&
                           (tmpValue <= `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_RIGHT) &&
                           (gestureCounter > 0u))
                        {
                            /* Block INERTIAL_SCROLL detecting */
                            tmpValue = `$INSTANCE_NAME`_NO_GESTURE;
                        }
                    #endif /* (0u != `$INSTANCE_NAME`_ONE_FINGER_EDGE_SWIPE_EN) */
                }
                break;
            default:
                `$INSTANCE_NAME`_touchParams.touchState = `$INSTANCE_NAME`_TOUCH_UNRECOGNIZED;
                tmpValue = `$INSTANCE_NAME`_UNRECOGNIZED_GESTURE;
                break;
            }
        }

        ((`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)(`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam))->gestureId = (uint8)tmpValue;

        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ONE_FINGER_SCROLL_EN) || \
             (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TWO_FINGER_SCROLL_EN))

            if((tmpValue >= `$INSTANCE_NAME`_ONE_FINGER_SCROLL_UP) &&
               (tmpValue <= `$INSTANCE_NAME`_TWO_FINGER_SCROLL_RIGHT))
            {
                ((`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)(`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam))->scrollCnt = `$INSTANCE_NAME`_TMG_GetScrollCnt();
            }
            if((tmpValue >= `$INSTANCE_NAME`_ONE_FINGER_SCROLL_INERTIAL_UP) &&
               (tmpValue <= `$INSTANCE_NAME`_TWO_FINGER_SCROLL_INERTIAL_RIGHT))
            {
                ((`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)(`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam))->scrollCnt = `$INSTANCE_NAME`_TMG_GetDecayCnt();
            }
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ONE_FINGER_SCROLL_EN) || \
                   (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TWO_FINGER_SCROLL_EN)) */

        return (tmpValue);
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN) */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_InitializeBallisticMultiplier
    ****************************************************************************//**
    *
    * \brief
    *  This function is intended to initialize the internal parameters of the
    *  ballistic multiplier filter.
    *
    * \details
    *  This routine initializes the parameters internal to the ballistic multiplier
    *  algorithm. It has to be called once prior to call the
    *  `$INSTANCE_NAME`_RunBallisticMultiplier() function.
    *  This is an internal function. Calling this function from application layer is
    *  not recommended.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_InitializeBallisticMultiplier(void)
    {
        int16 diffPosInit[`$INSTANCE_NAME`_BALLISTIC_DIMENSIONS_NUM] = {0, 0};

        `$INSTANCE_NAME`_bmPrevFingerNum   = 0u;
        `$INSTANCE_NAME`_dsRam.ballisticConfig.touchNumber = 0u;
        `$INSTANCE_NAME`_bmPrevFingerPos.x = `$INSTANCE_NAME`_TOUCHPAD_POS_NONE;
        `$INSTANCE_NAME`_bmPrevFingerPos.y = `$INSTANCE_NAME`_TOUCHPAD_POS_NONE;

        `$INSTANCE_NAME`_TMG_BallisticsMultiplier(&`$INSTANCE_NAME`_dsRam.ballisticConfig, `$INSTANCE_NAME`_dsRam.timestamp, diffPosInit);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_RunBallisticMultiplier
    ****************************************************************************//**
    *
    * \brief
    *  This function runs the Ballistic multiplier algorithm fo the widget specified
    *  by the wdgtIndex parameter.
    *
    * \details
    *  The `$INSTANCE_NAME`_RunBallisticMultiplier() routine implements the following functionality:
    *   - Gets the type of the widget passed through the wdgtIndex
    *     parameter.
    *   - initializes the `$INSTANCE_NAME`_ballisticMultiplier based on the type of
    *     the widget passed through the wdgtIndex parameter.
    *   - Runs the Ballistic multiplier algorithm for the specified widget.
    *   - Writes a processed position to the posXDelta and posYDelta registers in the
    *     `$INSTANCE_NAME`_RAM_WD_CSD_TOUCHPAD_STRUCT structure.
    *   This is an internal function. Calling this function from application layer is
    *   not recommended.
    *
    * \param wdgtIndex
    *  Specifies the ID number of the widget, the position, processed by Ballistic multiplier
    *  needs to be returned for.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_RunBallisticMultiplier(uint32 wdgtIndex)
    {
        `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;
        `$INSTANCE_NAME`_RAM_WD_CSD_TOUCHPAD_STRUCT *ptrRamWdgtTp;

        uint8 fingerNum = 0u;
        int16 diffPosition[`$INSTANCE_NAME`_BALLISTIC_DIMENSIONS_NUM];
        `$INSTANCE_NAME`_TMG_POSITION_STRUCT curPos = {`$INSTANCE_NAME`_TOUCHPAD_POS_NONE, `$INSTANCE_NAME`_TOUCHPAD_POS_NONE};

        ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex];
        ptrRamWdgtTp = (`$INSTANCE_NAME`_RAM_WD_CSD_TOUCHPAD_STRUCT*)ptrFlashWdgt->ptr2WdgtRam;

        if(`$INSTANCE_NAME`_BALLISTIC_EN_WIDGET_ID == wdgtIndex)
        {
            /* Get centroid position data for 5x5 CSD touchpad */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN)
                if (0u != (ptrFlashWdgt->staticConfig & `$INSTANCE_NAME`_CENTROID_5X5_MASK))
                {
                    curPos.x = ptrRamWdgtTp->position.pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].x;
                    curPos.y = ptrRamWdgtTp->position.pos[`$INSTANCE_NAME`_FIRST_FINGER_ID].y;
                    fingerNum = ((`$INSTANCE_NAME`_TOUCHPAD_POS_NONE != curPos.x) &&
                                 (`$INSTANCE_NAME`_TOUCHPAD_POS_NONE != curPos.y)) ? ptrRamWdgtTp->position.touchNum : 0u;
                }
            #endif

            /* Get centroid position data for 3x3 CSD touchpad */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_3X3_CSD_EN)
                if (0u != (ptrFlashWdgt->staticConfig & `$INSTANCE_NAME`_CENTROID_3X3_MASK))
                {
                    curPos.x = ptrRamWdgtTp->posX;
                    curPos.y = ptrRamWdgtTp->posY;
                    fingerNum = ((`$INSTANCE_NAME`_TOUCHPAD_POS_NONE != curPos.x) &&
                                 (`$INSTANCE_NAME`_TOUCHPAD_POS_NONE != curPos.y)) ? 1u : 0u;
                }
            #endif

            /* Reset the Ballistic multiplier algorithm to initial state in case if another finger has been recognized
             * as first.
            */
            if((0u != fingerNum) && (`$INSTANCE_NAME`_bmPrevFingerNum > fingerNum))
            {
                `$INSTANCE_NAME`_InitializeBallisticMultiplier();
            }

            if(0u != fingerNum)
            {
                /* Reset the internal variables to the current values if the finger is pressing the first time. */
                if((`$INSTANCE_NAME`_TOUCHPAD_POS_NONE == `$INSTANCE_NAME`_bmPrevFingerPos.x) ||
                   (`$INSTANCE_NAME`_TOUCHPAD_POS_NONE == `$INSTANCE_NAME`_bmPrevFingerPos.y))
                {
                    `$INSTANCE_NAME`_bmPrevFingerNum   = fingerNum;
                    `$INSTANCE_NAME`_bmPrevFingerPos.x = curPos.x;
                    `$INSTANCE_NAME`_bmPrevFingerPos.y = curPos.y;
                }

                /* Calculates the difference between current and previous XY of the first finger. */
                diffPosition[`$INSTANCE_NAME`_X_COORDINATE_INDEX] = (int16)curPos.x - (int16)`$INSTANCE_NAME`_bmPrevFingerPos.x;
                diffPosition[`$INSTANCE_NAME`_Y_COORDINATE_INDEX] = (int16)curPos.y - (int16)`$INSTANCE_NAME`_bmPrevFingerPos.y;
            }
            else
            {
                /* Set the difference between current and previous XY and current number of fingers on the touchpad
                 * to "0" if there are no touches detected.
                */
                fingerNum = 0u;
                diffPosition[`$INSTANCE_NAME`_X_COORDINATE_INDEX] = 0;
                diffPosition[`$INSTANCE_NAME`_Y_COORDINATE_INDEX] = 0;
            }

            /* Initialize the touchNumber field of the ballisticConfig structure with the actual number of fingers
             * on the touchpad surface.
            */
            `$INSTANCE_NAME`_dsRam.ballisticConfig.touchNumber = fingerNum;

            /* Run the Ballistic multiplier algorithm. */
            `$INSTANCE_NAME`_TMG_BallisticsMultiplier(&`$INSTANCE_NAME`_dsRam.ballisticConfig, `$INSTANCE_NAME`_dsRam.timestamp, diffPosition);

            /* Save the processed difference to the target registers. */
            ptrRamWdgtTp->posXDelta = diffPosition[`$INSTANCE_NAME`_X_COORDINATE_INDEX];
            ptrRamWdgtTp->posYDelta = diffPosition[`$INSTANCE_NAME`_Y_COORDINATE_INDEX];

            /* Store the cuttent XY position of the first finger and the number of fingers on the touchpad surface for
             * the next call of the `$INSTANCE_NAME`_RunBallisticMultiplier() function.
            */
            `$INSTANCE_NAME`_bmPrevFingerNum   = fingerNum;
            `$INSTANCE_NAME`_bmPrevFingerPos.x = curPos.x;
            `$INSTANCE_NAME`_bmPrevFingerPos.y = curPos.y;
        }
        else
        {
            /* Set the posXDelta and posYDelta registers to "0" in case of call this function for wrong widget. */
            ptrRamWdgtTp->posXDelta = 0;
            ptrRamWdgtTp->posYDelta = 0;
        }
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IncrementGestureTimestamp
****************************************************************************//**
*
* \brief
*  Increases the timestamp register for the predefined timestamp interval.
*
* \details
*  This function increments the Component timestamp
*  (`$INSTANCE_NAME`_TIMESTAMP_VALUE register) by the interval specified
*  in the `$INSTANCE_NAME`_TIMESTAMP_INTERVAL_VALUE register. The unit for
*  both registers is millisecond and default value of
*  `$INSTANCE_NAME`_TIMESTAMP_INTERVAL_VALUE is 1.
*
*  It is the application layer responsibility to periodically call this
*  function or register a periodic callback to this function to keep the
*  Component timestamp updated and operational, which is vital for the
*  operation of Gesture and Ballistic multiplier features.
*
*  The Component timestamp can be updated in one of the three methods:
*  - Register a periodic callback for the
*    `$INSTANCE_NAME`_IncrementGestureTimestamp() function.
*  - Periodically call the `$INSTANCE_NAME`_IncrementGestureTimestamp() function
*    by application layer.
*  - Directly modify the timestamp using the
*    `$INSTANCE_NAME`_SetGestureTimestamp() function.
*
*  The interval at which this function is called should match with interval
*  defined in `$INSTANCE_NAME`_TIMESTAMP_INTERVAL_VALUE register. Either the
*  register value can be updated to match the callback interval or the callback
*  can be made at interval set in the register.
*
*  If a timestamp is available from another source or from host controller,
*  application layer may choose to periodically update the Component timestamp
*  by using `$INSTANCE_NAME`_SetGestureTimestamp() function instead of
*  registering a callback.
*
*******************************************************************************/
void `$INSTANCE_NAME`_IncrementGestureTimestamp(void)
{
    `$INSTANCE_NAME`_dsRam.timestamp += `$INSTANCE_NAME`_dsRam.timestampInterval;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGestureTimestamp
****************************************************************************//**
*
* \brief
*  Rewrites the timestamp register by the specified value.
*
* \details
*  This function writes the specified value into the Component timestamp
*  (i.e. `$INSTANCE_NAME`_TIMESTAMP_VALUE register).
*
*  If a timestamp is available from another source or from host controller,
*  application layer may choose to periodically update the Component timestamp
*  by using this function instead of registering a callback.
*
*  It is not recommended to modify the Component timestamp arbitrarily or
*  simultaneously use with the `$INSTANCE_NAME`_IncrementGestureTimestamp()
*  function.
*
* \param timestampValue
*  Specifies the timestamp value (in ms).
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetGestureTimestamp(uint32 timestampValue)
{
    `$INSTANCE_NAME`_dsRam.timestamp = timestampValue;
}


/* [] END OF FILE */
