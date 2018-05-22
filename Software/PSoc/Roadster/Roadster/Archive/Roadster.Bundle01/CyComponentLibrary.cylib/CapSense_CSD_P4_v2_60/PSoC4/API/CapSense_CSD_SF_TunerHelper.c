/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TunerHelper.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of Tuner helper APIs for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_TunerHelper.h"

#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    #include "`$CustomEzI2CInstanceName`.h"
    #include "`$CustomEzI2CInstanceName`_EZI2C.h"
    volatile `$INSTANCE_NAME`_MAILBOXES `$INSTANCE_NAME`_mailboxesComm;
    extern uint8 `$INSTANCE_NAME`_sensorOnMask[(((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
#endif  /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TunerStart
********************************************************************************
*
* Summary:
*  Initializes the CapSense CSD component and EzI2C communication component to use
* the  mailbox data structure for communication with the Tuner GUI.
*  Start the scanning, after initialization completes.
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
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TunerStart(void)
{
    #if (`$INSTANCE_NAME`_TUNER_API_GENERATE)

        /* Init mbx and quick check */
        `$INSTANCE_NAME`_InitMailbox(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);
        `$INSTANCE_NAME`_mailboxesComm.numMailBoxes = `$INSTANCE_NAME`_DEFAULT_MAILBOXES_NUMBER;

        /* Start CapSense and baselines */
        `$INSTANCE_NAME`_Start();

        /* Initialize baselines */
        `$INSTANCE_NAME`_InitializeEnabledBaselines();
        `$INSTANCE_NAME`_InitializeEnabledBaselines();

        /* Start EzI2C, clears buf pointers */
        `$CustomEzI2CInstanceName`_Start();

        /* Setup EzI2C buffers */
        `$CustomEzI2CInstanceName`_EzI2CSetBuffer1(sizeof(`$INSTANCE_NAME`_mailboxesComm), sizeof(`$INSTANCE_NAME`_mailboxesComm),
                                        (void *) &`$INSTANCE_NAME`_mailboxesComm);

        /* Starts scan all enabled sensors */
        `$INSTANCE_NAME`_ScanEnabledWidgets();

    #endif  /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TunerComm
********************************************************************************
*
* Summary:
*  This function is blocking. It waits until a scanning loop is completed and applies
*  new parameters from the Tuner GUI if available (manual tuning mode only). Updates
*  the enabled baselines and state of widgets. Waits while the Tuner GUI reports that
*  the mailbox content could be modified. Then loads the report data into the outbox
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
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TunerComm(void)
{
    #if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
        if (0u == `$INSTANCE_NAME`_IsBusy())
        {
            /* Apply new settings */
            #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
                `$INSTANCE_NAME`_ReadMessage(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);
            #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */

            /* Update all baselines and process all widgets */
            `$INSTANCE_NAME`_UpdateEnabledBaselines();
            `$INSTANCE_NAME`_ProcessAllWidgets(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox.outbox);
            `$INSTANCE_NAME`_PostMessage(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);

            /* Enable EZI2C interrupts, after scan complete */
            `$CustomEzI2CInstanceName`_EnableInt();

            while((`$INSTANCE_NAME`_mailboxesComm.csdMailbox.type != `$INSTANCE_NAME`_TYPE_ID) || \
                  (`$CustomEzI2CInstanceName`_EzI2CGetActivity() & `$CustomEzI2CInstanceName`_EZI2C_STATUS_BUSY)){}

            /* Disable EZI2C interrupts, while scanning */
            `$CustomEzI2CInstanceName`_DisableInt();

            /* Start scan all sensors */
            `$INSTANCE_NAME`_ScanEnabledWidgets();
        }
    #endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */

}


#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Calls the required functions to update all widgets' state:
    *   - `$INSTANCE_NAME`_GetCentroidPos() - calls only if linear sliders
    *     available.
    *   - `$INSTANCE_NAME`_GetRadialCentroidPos() - calls only if radial slider
    *     available.
    *   - `$INSTANCE_NAME`_GetTouchCentroidPos() - calls only if touch pad slider
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
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ProcessAllWidgets(volatile `$INSTANCE_NAME`_OUTBOX *outbox)
    {
        uint8 i = 0u;
        #if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
            uint8 *mb_positionAddr;
        #endif /* (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)
            uint16 pos[2];
        #endif  /* (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) */

        #if ( (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) || \
              (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) )
            uint8 widgetCnt;
        #endif  /* ((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)) ||
                *   (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
                */

        /* Calculate widget with centroids */
        #if (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->position[i] = (uint16)`$INSTANCE_NAME`_GetCentroidPos((uint32)i);
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT) */

        #if (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT); i++)
            {
                outbox->position[i] = (uint16)`$INSTANCE_NAME`_GetRadialCentroidPos((uint32)i);
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) */

        #if (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT * 2u)); i=i+2u)
            {
                if(`$INSTANCE_NAME`_GetTouchCentroidPos((uint32)i, pos) == 0u)
                {
                    outbox->position[i] = 0xFFFFu;
                    outbox->position[i+1u] = 0xFFFFu;
                }
                else
                {
                    outbox->position[i] = (uint16) pos[0u];
                    outbox->position[i+1u] =(uint16) pos[1u];
                }
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) */

        #if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
            i += `$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0u;
            for(; widgetCnt < (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT * 2u); widgetCnt += 2u)
            {
                mb_positionAddr = (uint8*) &outbox->mb_position[widgetCnt];
                if(`$INSTANCE_NAME`_GetMatrixButtonPos((uint32)i, ((uint8*) &mb_positionAddr)) == 0u)
                {
                    outbox->mb_position[widgetCnt] = 0xFFu;
                    outbox->mb_position[widgetCnt+1u] = 0xFFu;
                }
                i += 2u;
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

        /* Update On/Off State */
        (void)`$INSTANCE_NAME`_CheckIsAnyWidgetActive();

        /* Copy OnMask */
        for(i=0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_MASK_COUNT; i++)
        {
            outbox->onMask[i]  = `$INSTANCE_NAME`_sensorOnMask[i];
        }
    }


#endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */

/* [] END OF FILE */
