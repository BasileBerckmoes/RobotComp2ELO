/*******************************************************************************
* File Name: `$INSTANCE_NAME`_MBX.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of Tuner communication APIs for the
*  CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_MBX.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START `$INSTANCE_NAME`_MBX` */

/* `#END` */

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_InitCsdParams
    ********************************************************************************
    *
    * Summary:
    *  Configures the CSD parameters to match the parameters in the inbox.
    *  Used only in the manual tuning mode to apply new scanning parameters from the Tuner
    *  GUI.
    *
    * Parameters:
    *  inbox:  Pointer to Inbox structure in RAM.
    *
    * Return:
    *  None. Contents of the structure are not modified.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_modulationIDAC[]      - stores modulation IDAC values.
    *  `$INSTANCE_NAME`_compensationIDAC[]    - stores compensation IDAC values.
    *  `$INSTANCE_NAME`_widgetResolution[]    - used to store the scan resolution values for each widget.
    *  `$INSTANCE_NAME`_senseClkDividerVal[]  - used to store the sense clock divider values for each widget.
    *  `$INSTANCE_NAME`_sampleClkDividerVal[] - used to store the sample clock divider values for each widget.
    *  `$INSTANCE_NAME`_fingerThreshold[]     - used to store the finger threshold values for each widget.
    *  `$INSTANCE_NAME`_noiseThreshold[]      - used to store the noise threshold values for each widget.
    *  `$INSTANCE_NAME`_hysteresis[]          - used to store the hysteresis values for each widget.
    *  `$INSTANCE_NAME`_debounce[]            - used to store the debounce values for each widget.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_InitCsdParams(volatile const `$INSTANCE_NAME`_INBOX *inbox);
    static void `$INSTANCE_NAME`_InitCsdParams(volatile const `$INSTANCE_NAME`_INBOX *inbox)
    {
        /* Define widget sensor belongs to */
        uint8 sensor = inbox->sensorIndex;
        uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];

        /* Scanning parameters */
        #if(0u == `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE)
            `$INSTANCE_NAME`_modulationIDAC[sensor] = inbox->`$INSTANCE_NAME`_inboxCsdCfg.modulatorIDAC;

            #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
                `$INSTANCE_NAME`_compensationIDAC[sensor] = inbox->`$INSTANCE_NAME`_inboxCsdCfg.compensationIDAC;
            #endif /* ( `$INSTANCE_NAME`_IDAC_CNT == 2u ) */
        #endif /* (0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE) */

        `$INSTANCE_NAME`_SetIDACRange((uint32)inbox->`$INSTANCE_NAME`_inboxCsdCfg.idacRange);

        `$INSTANCE_NAME`_widgetResolution[widget] =
        (uint32)(~(`$INSTANCE_NAME`_RESOLUTION_16_BITS << inbox->`$INSTANCE_NAME`_inboxCsdCfg.scanResolution));

        `$INSTANCE_NAME`_widgetResolution[widget] &= `$INSTANCE_NAME`_RESOLUTION_16_BITS;

        #if (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET )
            `$INSTANCE_NAME`_senseClkDividerVal[sensor] = inbox->`$INSTANCE_NAME`_inboxCsdCfg.analogSwitchDivider;
            `$INSTANCE_NAME`_sampleClkDividerVal[sensor] = inbox->`$INSTANCE_NAME`_inboxCsdCfg.modulatorDivider;
        #else
            `$INSTANCE_NAME`_senseClkDividerVal = inbox->`$INSTANCE_NAME`_inboxCsdCfg.analogSwitchDivider;
            `$INSTANCE_NAME`_sampleClkDividerVal = inbox->`$INSTANCE_NAME`_inboxCsdCfg.modulatorDivider;
        #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET ) */

        #if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
            #if (0u != `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
                /* Exclude generic widget */
                if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
                {
            #endif  /* 0u != `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */

                /* High level parameters */
                `$INSTANCE_NAME`_fingerThreshold[widget] = inbox->`$INSTANCE_NAME`_inboxCsdCfg.fingerThreshold;
                `$INSTANCE_NAME`_noiseThreshold[widget]  = inbox->`$INSTANCE_NAME`_inboxCsdCfg.noiseThreshold;

                `$INSTANCE_NAME`_hysteresis[widget] = inbox->`$INSTANCE_NAME`_inboxCsdCfg.hysteresis;
                `$INSTANCE_NAME`_debounce[widget]   = inbox->`$INSTANCE_NAME`_inboxCsdCfg.debounce;

                #if(`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
                    `$INSTANCE_NAME`_centroidMult[widget] = (uint16)((inbox->`$INSTANCE_NAME`_inboxCsdCfg.apiResolution *
                                                            (uint32)`$INSTANCE_NAME`_RES_MULT) / (uint32)`$INSTANCE_NAME`_numberOfSensors[widget]);

                #endif /* (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */

            #if (0u != `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
                /* Exclude generic widget */
                }
            #endif  /* 0u != `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */

            /* Re-Init baseline */
            `$INSTANCE_NAME`_InitializeAllBaselines();
        #endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */
    }
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_InitGesturesParams
    ********************************************************************************
    *
    * Summary:
    *  Configures the parameters of gestures to match the parameters in the inbox.
    *  Used only in the manual and auto tuning mode or if the gestures support is enabled.
    *  Intended apply new scanning parameters from the Tuner GUI.
    *
    * Parameters:
    *  inbox:  Pointer to Inbox structure in RAM.
    *
    * Return:
    *  None. Contents of the structure are not modified.
    *
    *******************************************************************************/
#if((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT))
    static void `$INSTANCE_NAME`_InitGesturesParams(volatile const `$INSTANCE_NAME`_INBOX *inbox);
    static void `$INSTANCE_NAME`_InitGesturesParams(volatile const `$INSTANCE_NAME`_INBOX *inbox)
    {
        #if(0u != `$INSTANCE_NAME`_IS_ANY_GESTURES_EN)
            #if(0u != `$INSTANCE_NAME`_CLICK_GEST_ENABLED)
                `$INSTANCE_NAME`_gesturesConfig.clickRadiusX            = (uint8)inbox->`$INSTANCE_NAME`_inboxTmgCfg.clickRadiusX;
                `$INSTANCE_NAME`_gesturesConfig.clickRadiusY            = (uint8)inbox->`$INSTANCE_NAME`_inboxTmgCfg.clickRadiusY;
                `$INSTANCE_NAME`_gesturesConfig.doubleClickRadius       = (uint8)inbox->`$INSTANCE_NAME`_inboxTmgCfg.doubleClickRadius;
                `$INSTANCE_NAME`_gesturesConfig.STDoubleClickTimeoutMax = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stDoubleClickTimeoutMax;
                `$INSTANCE_NAME`_gesturesConfig.STDoubleClickTimeoutMin = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stDoubleClickTimeoutMin;
                `$INSTANCE_NAME`_gesturesConfig.STClickTimeoutMax       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stClickTimeoutMax;
                `$INSTANCE_NAME`_gesturesConfig.STClickTimeoutMin       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stClickTimeoutMin;
                `$INSTANCE_NAME`_gesturesConfig.DTClickTimeoutMax       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtClickTimeoutMax;
                `$INSTANCE_NAME`_gesturesConfig.DTClickTimeoutMin       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtClickTimeoutMin;
            #endif /* (0u != `$INSTANCE_NAME`_CLICK_GEST_ENABLED) */

            #if(0u != `$INSTANCE_NAME`_ZOOM_GEST_ENABLED)
                `$INSTANCE_NAME`_gesturesConfig.dtScrollToZoomDebounce  = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtPanToZoomDebounce;
                `$INSTANCE_NAME`_gesturesConfig.DTZoomDebounce          = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtZoomDebounce;
                `$INSTANCE_NAME`_gesturesConfig.zoomActiveDistanceX     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.zoomActiveDistanceX;
                `$INSTANCE_NAME`_gesturesConfig.zoomActiveDistanceY     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.zoomActiveDistanceY;
            #endif /* (0u != `$INSTANCE_NAME`_ZOOM_GEST_ENABLED) */

            #if(0u != `$INSTANCE_NAME`_ST_SCROLL_GEST_ENABLED)
                `$INSTANCE_NAME`_gesturesConfig.stScrollDebounce        = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrDebounce;

                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold1X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold1X;
                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold2X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold2X;
                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold3X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold3X;
                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold4X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold4X;
                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold1Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold1Y;
                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold2Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold2Y;
                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold3Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold3Y;
                `$INSTANCE_NAME`_gesturesConfig.stScrollThreshold4Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrThreshold4Y;
                `$INSTANCE_NAME`_gesturesConfig.stScrollStep1           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrStep1;
                `$INSTANCE_NAME`_gesturesConfig.stScrollStep2           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrStep2;
                `$INSTANCE_NAME`_gesturesConfig.stScrollStep3           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrStep3;
                `$INSTANCE_NAME`_gesturesConfig.stScrollStep4           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stScrStep4;
                `$INSTANCE_NAME`_gesturesConfig.stInScrActiveDistanceX  = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stInScrActiveDistanceX;
                `$INSTANCE_NAME`_gesturesConfig.stInScrActiveDistanceY  = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stInScrActiveDistanceY;
                `$INSTANCE_NAME`_gesturesConfig.stInScrCountLevel       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.stInScrCountLevel;
            #endif /* (0u != `$INSTANCE_NAME`_ST_SCROLL_GEST_ENABLED) */

            #if(0u != `$INSTANCE_NAME`_DT_SCROLL_GEST_ENABLED)
                `$INSTANCE_NAME`_gesturesConfig.dtScrollDebounce        = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrDebounce;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold1X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold1X;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold2X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold2X;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold3X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold3X;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold4X     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold4X;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold1Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold1Y;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold2Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold2Y;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold3Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold3Y;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollThreshold4Y     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrThreshold4Y;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollStep1           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrStep1;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollStep2           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrStep2;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollStep3           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrStep3;
                `$INSTANCE_NAME`_gesturesConfig.dtScrollStep4           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtScrStep4;
                `$INSTANCE_NAME`_gesturesConfig.dtInScrActiveDistanceX  = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtInScrActiveDistanceX;
                `$INSTANCE_NAME`_gesturesConfig.dtInScrActiveDistanceY  = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtInScrActiveDistanceY;
                `$INSTANCE_NAME`_gesturesConfig.dtInScrCountLevel       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.dtInScrCountLevel;
            #endif /* (0u != `$INSTANCE_NAME`_DT_SCROLL_GEST_ENABLED) */

            #if(0u != `$INSTANCE_NAME`_FLICK_GEST_ENABLED)
                `$INSTANCE_NAME`_gesturesConfig.flickSampleTime         = inbox->`$INSTANCE_NAME`_inboxTmgCfg.flickSampleTime;
                `$INSTANCE_NAME`_gesturesConfig.flickActiveDistanceX    = inbox->`$INSTANCE_NAME`_inboxTmgCfg.flickActiveDistanceX;
                `$INSTANCE_NAME`_gesturesConfig.flickActiveDistanceY    = inbox->`$INSTANCE_NAME`_inboxTmgCfg.flickActiveDistanceY;
            #endif /* (0u != `$INSTANCE_NAME`_FLICK_GEST_ENABLED) */

            #if(0u != `$INSTANCE_NAME`_ROTATE_GEST_ENABLED)
                `$INSTANCE_NAME`_gesturesConfig.rotateDebounce          = inbox->`$INSTANCE_NAME`_inboxTmgCfg.rotateDebounce;
            #endif /* (0u != `$INSTANCE_NAME`_ROTATE_GEST_ENABLED) */

            #if(0u != `$INSTANCE_NAME`_EDGE_SWIPE_GEST_ENABLED)
                `$INSTANCE_NAME`_gesturesConfig.edgeSwipeActiveDistance = inbox->`$INSTANCE_NAME`_inboxTmgCfg.edgeSwipeActiveDistance;
                `$INSTANCE_NAME`_gesturesConfig.bottomAngleThreshold    = inbox->`$INSTANCE_NAME`_inboxTmgCfg.bottomAngleThreshold;
                `$INSTANCE_NAME`_gesturesConfig.edgeSwipeTimeout        = inbox->`$INSTANCE_NAME`_inboxTmgCfg.edgeSwipeTime;
                `$INSTANCE_NAME`_TMG_edgeSwipeCompleteTimeout           = inbox->`$INSTANCE_NAME`_inboxTmgCfg.edgeSwipeCompleteTimeout;
                `$INSTANCE_NAME`_gesturesConfig.topAngleThreshold       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.topAngleThreshold;
                `$INSTANCE_NAME`_gesturesConfig.widthOfDisambiguation   = inbox->`$INSTANCE_NAME`_inboxTmgCfg.widthOfDisambiguation;
            #endif /* (0u != `$INSTANCE_NAME`_EDGE_SWIPE_GEST_ENABLED) */

            `$INSTANCE_NAME`_TMG_InitGestures(&`$INSTANCE_NAME`_gesturesConfig);
        #endif /* (0u != `$INSTANCE_NAME`_IS_ANY_GESTURES_EN) */

        #if(0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)
            `$INSTANCE_NAME`_posFiltersMask[`$INSTANCE_NAME`_TRACKPAD__TPG] = inbox->`$INSTANCE_NAME`_inboxTmgCfg.filtersMask;
        #endif /* (0u != `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK) */

        #if(0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK))
            `$INSTANCE_NAME`_adpFltOptions.divVal       = inbox->`$INSTANCE_NAME`_inboxTmgCfg.filterDivisor;
            `$INSTANCE_NAME`_adpFltOptions.largeMovTh   = inbox->`$INSTANCE_NAME`_inboxTmgCfg.largeMovThreshold;
            `$INSTANCE_NAME`_adpFltOptions.littleMovTh  = inbox->`$INSTANCE_NAME`_inboxTmgCfg.littleMovThreshold;
            `$INSTANCE_NAME`_adpFltOptions.maxK     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.maxFilterCoef;
            `$INSTANCE_NAME`_adpFltOptions.minK     = inbox->`$INSTANCE_NAME`_inboxTmgCfg.minFilterCoef;
            `$INSTANCE_NAME`_adpFltOptions.noMovTh      = inbox->`$INSTANCE_NAME`_inboxTmgCfg.noMovThreshold;
        #endif /* (0u != (`$INSTANCE_NAME`_XY_ADAPTIVE_IIR_MASK & `$INSTANCE_NAME`_TP_GESTURE_POS_FILTERS_MASK)) */
    }
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT)) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitMailbox
********************************************************************************
*
* Summary:
*  Initializes parameters of the mailbox structure.
*  Sets the type and size of the mailbox structure.
*  Sets a check sum to check by the Tuner GUI and noReadMsg flag to indicate that this
*  is the first communication packet.
*
* Parameters:
*  mbx:  Pointer to Mailbox structure in RAM.
*
* Return:
*  None. Modifies the contents of mbx and mbx->outbox.
*
* Global Variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitMailbox(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
{
    /* Restore TYPE_ID (clear busy flag) to indicate "action complete" */
    mbx->type = `$INSTANCE_NAME`_TYPE_ID;
    /* Restore default value - clear "have_msg" */
    mbx->size = sizeof(`$INSTANCE_NAME`_MAILBOX);

    /* Additional fields for async and reset handling */
    #if((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
        (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL))
        mbx->outbox.noReadMessage = 1u;
    #endif  /* ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)) */

    mbx->outbox.checkSum = (uint16)(`$INSTANCE_NAME`_CHECK_SUM);
}


/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_PostMessage
********************************************************************************
*
* Summary:
*  This blocking function waits while the Tuner GUI reports that the mailbox content
*  could be modified (clears `$INSTANCE_NAME`_BUSY_FLAG). Then loads the report
*  data to the outbox and sets a busy flag.
*  In the manual tuning mode the report data is:
*    - raw data, baseline, signal;
*  In the auto tuning mode the added data is:
*    - fingerThreshold;
*    - noiseThreshold;
*    - scanResolution;
*    - idacValue;
*    - prescaler.
*
* Parameters:
*  mbx:  Pointer to Mailbox structure in RAM.
*
* Return:
*  None. Modifies the contents of mbx->outbox.
*
* Global Variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PostMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
{
    uint8 i;

    #if ( `$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO )
        uint8 tmpResolutionIndex;
        uint16 tmpResolutionValue;
    #endif /* ( `$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO ) */

    /* Check busy flag */
    while (mbx->type != `$INSTANCE_NAME`_TYPE_ID){}

    /* Copy scan parameters */
    #if((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) || (0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE))
        /* Copy tuned idac values */
        for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
        {
            mbx->outbox.modulationIDAC[i] = `$INSTANCE_NAME`_modulationIDAC[i];
            #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
                mbx->outbox.compensationIDAC[i] = `$INSTANCE_NAME`_compensationIDAC[i];
            #endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */
        }
    #endif /* ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) || (0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE)) */

    #if ( `$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO )
        for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; i++)
        {
            mbx->outbox.analogSwitchDivider[i] = `$INSTANCE_NAME`_senseClkDividerVal[i];
            mbx->outbox.modulatorDivider[i] = `$INSTANCE_NAME`_sampleClkDividerVal[i];
        }

        /* Widget resolution, take to account TP and MB */
        for(i = 0u; i < `$INSTANCE_NAME`_WIDGET_RESOLUTION_PARAMETERS_COUNT; i++)
        {
            tmpResolutionValue = (uint16)(`$INSTANCE_NAME`_widgetResolution[i] >> `$INSTANCE_NAME`_MSB_RESOLUTION_OFFSET);
            tmpResolutionIndex = 0u;

            while(0u != tmpResolutionValue)
            {
                tmpResolutionIndex++;
                tmpResolutionValue >>= 1u;
            }

            mbx->outbox.scanResolution[i] = tmpResolutionIndex;
        }

        #if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
            /* Parameters are changed in run time */
            for(i = 0u; i < `$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT; i++)
            {
                mbx->outbox.fingerThreshold[i] = `$INSTANCE_NAME`_fingerThreshold[i];
                mbx->outbox.noiseThreshold[i]  = `$INSTANCE_NAME`_noiseThreshold[i];
                mbx->outbox.hysteresis[i]      = `$INSTANCE_NAME`_hysteresis[i];
            }
        #endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */


    /* Copy all data - Raw, Base, Signal, OnMask */
    for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
    {
        mbx->outbox.rawData[i]  = `$INSTANCE_NAME`_sensorRaw[i];
        #if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
            mbx->outbox.baseLine[i] = `$INSTANCE_NAME`_sensorBaseline[i];
            #if (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8)
                mbx->outbox.sensorSignal[i]   = (uint8)`$INSTANCE_NAME`_sensorSignal[i];
            #else
                mbx->outbox.sensorSignal[i]   = (uint16)`$INSTANCE_NAME`_sensorSignal[i];
            #endif  /* (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8) */
        #endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */
    }

    /* Set busy flag */
    mbx->type = `$INSTANCE_NAME`_BUSY_FLAG;
}


#if ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
     (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL))

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadMessage
    ********************************************************************************
    *
    * Summary:
    *  If `$INSTANCE_NAME`_HAVE_MSG is found in the mailbox, the function initializes
    *   the component with parameters which are found in the inbox.
    *   Signal is DONE by overwriting the value in the mailbox size field.
    *  Only available in the manual tuning mode.
    *
    * Parameters:
    *  mbx:  Pointer to Mailbox structure in RAM.
    *
    * Return:
    *  None. Modifies the contents of mbx.
    *
    * Global Variables:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReadMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
    {
        volatile `$INSTANCE_NAME`_INBOX *tmpInbox;

        /* Do we have a message waiting? */
        if ((mbx->size) == `$INSTANCE_NAME`_HAVE_MSG)
        {
            tmpInbox = &(mbx->inbox);

            #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
                if(tmpInbox->sensorIndex != `$INSTANCE_NAME`_MAX_UINT_8)
                {
                    `$INSTANCE_NAME`_InitCsdParams(tmpInbox);
                }
            #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */

            #if(0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT)
                if(tmpInbox->sensorIndex == `$INSTANCE_NAME`_MAX_UINT_8)
                {
                    `$INSTANCE_NAME`_InitGesturesParams(tmpInbox);
                }
            #endif /* (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) */

            /* Notify host/tuner that we have consumed message */
            mbx->size = sizeof(`$INSTANCE_NAME`_MAILBOX);

            /* Default settings were changed */
            mbx->outbox.noReadMessage = 0u;

            /* `#START `$INSTANCE_NAME`_MBX_READ_MSG` */

            /* `#END` */

            #ifdef `$INSTANCE_NAME`_READ_MESSAGE_MBX_READ_MSG_CALLBACK
                `$INSTANCE_NAME`_ReadMessage_MBX_READ_MSG_Callback();
            #endif /* `$INSTANCE_NAME`_READ_MESSAGE_MBX_READ_MSG_CALLBACK */
        }
    }
#endif  /* ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) && (0u != `$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
            (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)) */


/* [] END OF FILE */
