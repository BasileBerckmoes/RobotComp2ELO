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
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_MBX.h"

extern uint8 `$INSTANCE_NAME`_sensorOnMask[(((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
extern uint16 `$INSTANCE_NAME`_sensorBaseline[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
extern `$INSTANCE_NAME`_SIGNAL_SIZE_TYPE `$INSTANCE_NAME`_sensorSignal[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
extern uint8 `$INSTANCE_NAME`_sensorBaselineLow[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_InitParams
    ********************************************************************************
    *
    * Summary:
    *  Configures component parameters to match the parameters in the inbox.
    *  Used only in manual tuning mode to apply new scanning parameters from Tuner
    *  GUI.
    *
    * Parameters:
    *  inbox:  Pointer to Inbox structure in RAM.
    *
    * Return:
    *  None. Contents of the structure are not modified.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_idacSettings[] - used to store idac value for all sensors.
    *  `$INSTANCE_NAME`_fingerThreshold[] - used to store finger threshold for all
    *  widgets.
    *  `$INSTANCE_NAME`_noiseThreshold[] - used to store noise threshold for all
    *  widgets.
    *  `$INSTANCE_NAME`_hysteresis[] - used to store finger threshold for all
    *  widgets.
    *  `$INSTANCE_NAME`_debounce[] - used to store finger threshold for all
    *  widgets.
    *  `$INSTANCE_NAME`_INBOX inbox - structure which is used as input buffer
    *  for parameters from Tuner GUI. Only used in manual tuning mode.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_InitParams(volatile const `$INSTANCE_NAME`_INBOX *inbox);
    static void `$INSTANCE_NAME`_InitParams(volatile const `$INSTANCE_NAME`_INBOX *inbox)
    {
        /* Define widget sensor belongs to */
        uint8 commonIndex;
        uint8 sensor = inbox->sensorIndex;
        uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];

        /* Scanning parameters */
        `$INSTANCE_NAME`_modulationIDAC[sensor] = inbox->idac1Settings;

        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
            `$INSTANCE_NAME`_compensationIDAC[sensor] = inbox->idac2Settings;
        #endif /* ( `$INSTANCE_NAME`_IDAC_CNT == 2u ) */

        `$INSTANCE_NAME`_widgetResolution[widget] = inbox->resolution;

        #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
            /* Exclude generic widget */
            if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
            {
        #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */

            /* High level parameters */
            `$INSTANCE_NAME`_fingerThreshold[widget] = inbox->fingerThreshold;
            `$INSTANCE_NAME`_noiseThreshold[widget]  = inbox->noiseThreshold;

            commonIndex = `$INSTANCE_NAME`_GetCommonParamIndex(widget);

            `$INSTANCE_NAME`_hysteresis[commonIndex] = inbox->hysteresis;
            `$INSTANCE_NAME`_debounce[commonIndex]   = inbox->debounce;

        #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
            /* Exclude generic widget */
            }
        #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */

        #if ( `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET )

            `$INSTANCE_NAME`_senseClkDividerVal[sensor] = inbox->analogSwitchDivider;
            #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
                `$INSTANCE_NAME`_sampleClkDividerVal = inbox->modulatorDivider;
            #else
                `$INSTANCE_NAME`_sampleClkDividerVal[sensor] = inbox->modulatorDivider;
            #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */
        #else
            `$INSTANCE_NAME`_senseClkDividerVal = inbox->analogSwitchDivider;
            `$INSTANCE_NAME`_sampleClkDividerVal = inbox->modulatorDivider;
        #endif /* ( `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET ) */

        /* Re-Init baselines */
        `$INSTANCE_NAME`_InitializeAllBaselines();
    }
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitMailbox
********************************************************************************
*
* Summary:
*  Initializes parameters of mailbox structure.
*  Sets type and size of mailbox structure.
*  Sets check sum to check by Tuner GUI and noReadMsg flag to indicate that this
*  is the first communication packet.
*
* Parameters:
*  mbx:  Pointer to Mailbox structure in RAM.
*
* Return:
*  None. Modifies the contents of mbx and mbx->outbox.
*
* Global Variables:
*  `$INSTANCE_NAME`_MAILBOXES - structure which incorporates two fields:
*    - numMailBoxes (number of mailboxes);
*    - `$INSTANCE_NAME`_MAILBOX csdMailbox;
*  `$INSTANCE_NAME`_MAILBOX - structure which incorporates status output and
*  input buffer fields and `$INSTANCE_NAME`_OUTBOX and `$INSTANCE_NAME`_INBOX.
*    - type (used as outbox read status of Tuner GUI);
*    - size (used as inbox apply status of component);
*    - `$INSTANCE_NAME`_OUTBOX outbox - structure which is used as output
*      buffer for report data to Tuner GUI.
*    - `$INSTANCE_NAME`_INBOX inbox - structure which is used as input buffer
*      for parameters from Tuner GUI. Only used in manual tuning mode.
*
* Side Effects:
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
    #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
        mbx->outbox.noReadMsg = 1u;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */

    mbx->outbox.checkSum = (uint16)(`$INSTANCE_NAME`_CHECK_SUM);
}


/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_PostMessage
********************************************************************************
*
* Summary:
*  This blocking function waits while Tuner GUI reports that content of mailbox
*  could be modified (clears `$INSTANCE_NAME`_BUSY_FLAG). Then loads the report
*  data to outbox and sets the busy flag.
*  In manual tuning mode the report data are:
*    - raw data, baseline, signal;
*  In auto tuning mode the added data are:
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
*  `$INSTANCE_NAME`_MAILBOXES - the structure which incorporates two fields:
*    - numMailBoxes (number of mailboxes);
*    - `$INSTANCE_NAME`_MAILBOX csdMailbox;
*  `$INSTANCE_NAME`_MAILBOX - the structure which incorporates the status output,
*  input buffer fields, `$INSTANCE_NAME`_OUTBOX, and `$INSTANCE_NAME`_INBOX.
*    - type (used as the outbox read status of the Tuner GUI);
*    - size (used as the inbox apply status of the component);
*    - `$INSTANCE_NAME`_OUTBOX outbox - the structure which is used as an output
*      buffer to report data to the Tuner GUI.
*    - `$INSTANCE_NAME`_INBOX inbox - the structure which is used as an input buffer
*      for parameters from the Tuner GUI. Only used in the manual tuning mode.
*  `$INSTANCE_NAME`_lowLevelTuningDone - used to notify the Tuner GUI that
*  tuning of scanning parameters is done. The scanning parameters in the mailbox
*  will not be updated after clearing it.
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PostMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
{
    uint8 i;

    /* Check busy flag */
    while (mbx->type != `$INSTANCE_NAME`_TYPE_ID);

    /* Copy all data - Raw, Base, Signal, OnMask */
    for(i=0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
    {
        mbx->outbox.rawData[i]  = `$INSTANCE_NAME`_sensorRaw[i];
        mbx->outbox.baseLine[i] = `$INSTANCE_NAME`_sensorBaseline[i];
        #if (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8)
            mbx->outbox.signal[i]   = (uint8)`$INSTANCE_NAME`_sensorSignal[i];
        #else
            mbx->outbox.signal[i]   = (uint16)`$INSTANCE_NAME`_sensorSignal[i];
        #endif  /* (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8) */
    }

    /* AutoTuning - need to copy all High Level parameters */
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)

        /* Parameters are changed in run time */
        for(i=0u; i < `$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT; i++)
        {
            mbx->outbox.fingerThreshold[i] = `$INSTANCE_NAME`_fingerThreshold[i];
            mbx->outbox.noiseThreshold[i]  = `$INSTANCE_NAME`_noiseThreshold[i];
        }

        /* Widget resolution, take into account TP and MB */
        for(i=0u; i < `$INSTANCE_NAME`_WIDGET_RESOLUTION_PARAMETERS_COUNT; i++)
        {
            mbx->outbox.scanResolution[i]  = `$INSTANCE_NAME`_widgetResolution[i];
        }

        /* Copy tuned idac values */
        for(i=0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
        {
            mbx->outbox.idac1Value[i] = `$INSTANCE_NAME`_modulationIDAC[i];
            #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
                mbx->outbox.idac2Value[i] = `$INSTANCE_NAME`_compensationIDAC[i];
            #endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */
        }

        /* Pass parameters only once */
        `$INSTANCE_NAME`_lowLevelTuningDone = 0u;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */

    /* Copy scan parameters */
    #if ( `$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO )
        for(i=0u; i < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; i++)
        {
            mbx->outbox.analogSwitchDivider[i] = `$INSTANCE_NAME`_senseClkDividerVal[i];
            mbx->outbox.modulatorDivider[i] = `$INSTANCE_NAME`_sampleClkDividerVal;
        }
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

    /* Set busy flag */
    mbx->type = `$INSTANCE_NAME`_BUSY_FLAG;
}

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadMessage
    ********************************************************************************
    *
    * Summary:
    *  If `$INSTANCE_NAME`_HAVE_MSG is found in the mailbox, initialize the component
    *  with the parameters found in the inbox. Signal DONE by overwriting the
    *  value in the mailbox size field.
    *  Only available when the manual tuning mode.
    *
    * Parameters:
    *  mbx:  Pointer to Mailbox structure in RAM.
    *
    * Return:
    *  None. Modifies the contents of mbx.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_MAILBOXES - the structure which incorporates two fields:
    *    - numMailBoxes (number of mailboxes);
    *    - `$INSTANCE_NAME`_MAILBOX csdMailbox;
    *  `$INSTANCE_NAME`_MAILBOX - the structure which incorporates the status output,
    *  input buffer fields,`$INSTANCE_NAME`_OUTBOX, and `$INSTANCE_NAME`_INBOX.
    *    - type (used as the outbox read status of the Tuner GUI);
    *    - size (used as the inbox apply status of the component);
    *    - `$INSTANCE_NAME`_OUTBOX outbox - the structure which is used as an output
    *      buffer to report data to the Tuner GUI.
    *    - `$INSTANCE_NAME`_INBOX inbox - the structure which is used as an input buffer
    *      for parameters from the Tuner GUI. Only used in the manual tuning mode.
    *
    * Side Effects:
    *  Initializes the component parameters if `$INSTANCE_NAME`_HAVE_MSG is received.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReadMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
    {
        volatile `$INSTANCE_NAME`_INBOX *tmpInbox;

        /* Do we have a message waiting? */
        if ((mbx->size) == `$INSTANCE_NAME`_HAVE_MSG)
        {
            tmpInbox = &(mbx->inbox);

            `$INSTANCE_NAME`_InitParams(tmpInbox);

            /* Notify host/tuner that we have consumed message */
            mbx->size = sizeof(`$INSTANCE_NAME`_MAILBOX);

            /* Default settings were changed */
            mbx->outbox.noReadMsg = 0u;
        }
    }
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */


/* [] END OF FILE */
