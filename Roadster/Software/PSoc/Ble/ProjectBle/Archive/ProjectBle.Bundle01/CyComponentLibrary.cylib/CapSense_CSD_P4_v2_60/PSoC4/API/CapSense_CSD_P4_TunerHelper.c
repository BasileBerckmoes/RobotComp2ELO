/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TunerHelper.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of the Tuner helper APIs for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_TunerHelper.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    #include "`$CustomEzI2CInstanceName`.h"
    #include "`$CustomEzI2CInstanceName`_EZI2C.h"
    volatile `$INSTANCE_NAME`_MAILBOXES `$INSTANCE_NAME`_mailboxesComm;
#endif  /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */

/* `#START `$INSTANCE_NAME`_TunerHelper_HEADER` */

/* `#END` */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TunerStart
********************************************************************************
*
* Summary:
*  Initializes the CapSense CSD component and EzI2C communication component to use
*  a mailbox data structure for communication with the Tuner GUI.
*  Start the scanning, after initialization is complete.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TunerStart(void)
{
    #if (0u != `$INSTANCE_NAME`_TUNER_API_GENERATE)

        /* Init mbx and quick check */
        `$INSTANCE_NAME`_InitMailbox(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);
        `$INSTANCE_NAME`_mailboxesComm.numMailBoxes = `$INSTANCE_NAME`_DEFAULT_MAILBOXES_NUMBER;

        /* Start CapSense and baselines */
        `$INSTANCE_NAME`_Start();

        /* Initialize baselines */
        #if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
            `$INSTANCE_NAME`_InitializeEnabledBaselines();
        #endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

        /* Start EzI2C, clears buf pointers */
        `$CustomEzI2CInstanceName`_Start();

        /* Setup EzI2C buffers */
        `$CustomEzI2CInstanceName`_EzI2CSetBuffer1(sizeof(`$INSTANCE_NAME`_mailboxesComm), sizeof(`$INSTANCE_NAME`_mailboxesComm),
                                                   (volatile uint8 *) &`$INSTANCE_NAME`_mailboxesComm);

        /* Starts scan all enabled sensors */
        `$INSTANCE_NAME`_ScanEnabledWidgets();

    #endif  /* (0u != `$INSTANCE_NAME`_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TunerComm
********************************************************************************
*
* Summary:
*  This function is blocking. It waits till scanning loop is completed and applies
*  the new parameters from the Tuner GUI if available (the manual tuning mode only). Updates
*  the enabled baselines and state of widgets. Waits while the Tuner GUI reports that
*  the mailbox content  could be modified. Then loads the report data into the outbox
*  and sets a busy flag. Starts a new scanning loop.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TunerComm(void)
{
    #if (0u != `$INSTANCE_NAME`_TUNER_API_GENERATE)
        if (0u == `$INSTANCE_NAME`_IsBusy())
        {
            /* Apply new settings */
            #if((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) &&\
                (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL))

                `$INSTANCE_NAME`_ReadMessage(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);

            #endif  /* ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) &&\
                        (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                        (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)) */

            #if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
                /* Update all baselines and process all widgets */
                `$INSTANCE_NAME`_UpdateEnabledBaselines();
                `$INSTANCE_NAME`_ProcessAllWidgets(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox.outbox);
            #endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

            `$INSTANCE_NAME`_PostMessage(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);

            /* Enable EZI2C interrupts, after scan complete */
            `$CustomEzI2CInstanceName`_EnableInt();

            while((`$INSTANCE_NAME`_mailboxesComm.csdMailbox.type != `$INSTANCE_NAME`_TYPE_ID) ||
                  (0u != (`$CustomEzI2CInstanceName`_EzI2CGetActivity() & `$CustomEzI2CInstanceName`_EZI2C_STATUS_BUSY))){}

            /* Disable EZI2C interrupts, while scanning */
            `$CustomEzI2CInstanceName`_DisableInt();

            /* Start scan all sensors */
            `$INSTANCE_NAME`_ScanEnabledWidgets();
        }
    #endif /* (0u != `$INSTANCE_NAME`_TUNER_API_GENERATE) */
}


#if ((0u != `$INSTANCE_NAME`_TUNER_API_GENERATE) && (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Calls the required functions to update all the widgets' state:
    *   - `$INSTANCE_NAME`_GetCentroidPos() - calls only if linear sliders are
    *     available.
    *   - `$INSTANCE_NAME`_GetRadialCentroidPos() - calls only if the  radial slider is
    *     available.
    *   - `$INSTANCE_NAME`_GetTouchCentroidPos() - calls only if the  touchpad slider
    *     available.
    *   - `$INSTANCE_NAME`_CheckIsAnyWidgetActive();
    *  The results of operations are copied to OUTBOX.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_OUTBOX outbox - the structure which is used as an output
    *  buffer to report data to the Tuner GUI.
    *  Update fields:
    *    - position[];
    *    - OnMask[];
    *
    * Global Variables:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ProcessAllWidgets(volatile `$INSTANCE_NAME`_OUTBOX *outbox)
    {
        uint8  i = 0u;

        #if (0u != `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
            uint8 mbPositionBuf[`$INSTANCE_NAME`_MB_POSITION_BUFFER_SIZE];
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT)
            uint16 centroidPosBuf[`$INSTANCE_NAME`_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if(0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT)
            `$INSTANCE_NAME`_POSITION_STRUCT trackpadPosBuf[`$INSTANCE_NAME`_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if ( (0u != `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) || \
              (0u != `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT))
            uint8 widgetCnt;
        #endif  /* ((0u != `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)) ||
                *   (0u != `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
                */

        /* Calculate widget with centroids */
        #if (0u != `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->centroidPosition[i] = (uint16)`$INSTANCE_NAME`_GetCentroidPos((uint32)i);
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT); i++)
            {
                outbox->centroidPosition[i] = (uint16)`$INSTANCE_NAME`_GetRadialCentroidPos((uint32)i);
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u)); i=i+2u)
            {
                if(`$INSTANCE_NAME`_GetTouchCentroidPos((uint32)i, centroidPosBuf) == 0u)
                {
                    outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_X_INDEX] = `$INSTANCE_NAME`_MAX_UINT_16;
                    outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_Y_INDEX] = `$INSTANCE_NAME`_MAX_UINT_16;
                }
                else
                {
                    outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_X_INDEX] =
                    (uint16) centroidPosBuf[`$INSTANCE_NAME`_FIRST_FINGER_X_INDEX];

                    outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_Y_INDEX] =
                    (uint16) centroidPosBuf[`$INSTANCE_NAME`_FIRST_FINGER_Y_INDEX];
                }
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT * 4u)); i=i+4u)
            {
                outbox->fingersNum[`$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX] =
                (uint8)`$INSTANCE_NAME`_GetDoubleTouchCentroidPos(trackpadPosBuf);

                outbox->gestureID[`$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX] =
                (uint8)`$INSTANCE_NAME`_DecodeAllGestures((uint32)outbox->fingersNum[`$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX], trackpadPosBuf);

                #if((0u != `$INSTANCE_NAME`_ST_SCROLL_GEST_ENABLED) || (0u != `$INSTANCE_NAME`_DT_SCROLL_GEST_ENABLED))
                    /*
                    Report Scroll count only for scroll and Inertial Scroll gestures.
                    For all other gestures report scroll count as zero to tuner.
                     */
                    if (((outbox->gestureID[`$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX] & `$INSTANCE_NAME`_GESTURE_TYPE_MASK) == `$INSTANCE_NAME`_NON_INERTIAL_SCROLL) ||
                        ((outbox->gestureID[`$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX] & `$INSTANCE_NAME`_GESTURE_TYPE_MASK) == `$INSTANCE_NAME`_INERTIAL_SCROLL))
                    {
                        outbox->scrollCnt = `$INSTANCE_NAME`_GetScrollCnt();
                    }
                    else
                    {
                        outbox->scrollCnt = 0u;
                    }
                #endif /* ((0u != `$INSTANCE_NAME`_ST_SCROLL_GEST_ENABLED) || (0u != `$INSTANCE_NAME`_DT_SCROLL_GEST_ENABLED)) */

                outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_X_INDEX] = `$INSTANCE_NAME`_MAX_UINT_16;
                outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_Y_INDEX] = `$INSTANCE_NAME`_MAX_UINT_16;
                outbox->centroidPosition[i + `$INSTANCE_NAME`_SECOND_FINGER_X_INDEX] = `$INSTANCE_NAME`_MAX_UINT_16;
                outbox->centroidPosition[i + `$INSTANCE_NAME`_SECOND_FINGER_Y_INDEX] = `$INSTANCE_NAME`_MAX_UINT_16;

                if(0u != outbox->fingersNum[`$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX])
                {
                    outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_X_INDEX] =
                    (uint16) trackpadPosBuf[`$INSTANCE_NAME`_FIRST_FINGER_INDEX].x;

                    outbox->centroidPosition[i + `$INSTANCE_NAME`_FIRST_FINGER_Y_INDEX] =
                    (uint16) trackpadPosBuf[`$INSTANCE_NAME`_FIRST_FINGER_INDEX].y;

                    if(outbox->fingersNum[`$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX] > 1u)
                    {
                        outbox->centroidPosition[i + `$INSTANCE_NAME`_SECOND_FINGER_X_INDEX] =
                        (uint16) trackpadPosBuf[`$INSTANCE_NAME`_SECOND_FINGER_INDEX].x;

                        outbox->centroidPosition[i + `$INSTANCE_NAME`_SECOND_FINGER_Y_INDEX] =
                        (uint16) trackpadPosBuf[`$INSTANCE_NAME`_SECOND_FINGER_INDEX].y;
                    }
                }
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
            i += `$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0u;
            for(; widgetCnt < (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT * 2u); widgetCnt += 2u)
            {
                if(`$INSTANCE_NAME`_GetMatrixButtonPos((uint32)i, mbPositionBuf) == 0u)
                {
                    outbox->mbPosition[widgetCnt] = `$INSTANCE_NAME`_MAX_UINT_8;
                    outbox->mbPosition[widgetCnt+1u] = `$INSTANCE_NAME`_MAX_UINT_8;
                }
                else
                {
                    outbox->mbPosition[widgetCnt] = mbPositionBuf[0u];
                    outbox->mbPosition[widgetCnt+1u] = mbPositionBuf[1u];
                }
                i += 2u;
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
            /* Update On/Off State */
            (void)`$INSTANCE_NAME`_CheckIsAnyWidgetActive();

            /* Copy OnMask */
            for(i=0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_MASK_COUNT; i++)
            {
                outbox->onMask[i]  = `$INSTANCE_NAME`_sensorOnMask[i];
            }
        #endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

        /* `#START `$INSTANCE_NAME`_ProcessAllWidgets_Debug` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_PROCESS_ALL_WIDGETS_CALLBACK
            `$INSTANCE_NAME`_ProcessAllWidgets_Callback();
        #endif /* `$INSTANCE_NAME`_PROCESS_ALL_WIDGETS_CALLBACK */
    }


#endif /* ((0u != `$INSTANCE_NAME`_TUNER_API_GENERATE) && (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)) */


/* [] END OF FILE */
