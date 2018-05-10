/***************************************************************************//**
* \file `$INSTANCE_NAME`_INT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file contains the source code for implementation of the `$INSTANCE_NAME`
*   Component Interrupt Service Routine (ISR).
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
#include "cyfitter.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    #include "`$INSTANCE_NAME`_SensingCSD_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
`$CY_API_CALLBACK_HEADER_INCLUDE`

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/
/**
* \cond SECTION_CYSENSE_INTERNAL
* \addtogroup group_cysense_internal
* \{
*/

#if (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN))
    static void `$INSTANCE_NAME`_SsNextFrequencyScan(void);
#endif /* (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)) && \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN))
    static void `$INSTANCE_NAME`_SsCSDPostScan(void);
    static void `$INSTANCE_NAME`_SsCSDInitNextScan(void);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)) */
/** \}
* \endcond */


/**
* \cond SECTION_CYSENSE_INTERRUPT
* \addtogroup group_cysense_interrupt
* \{
*/


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN))


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CSDPostSingleScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the single-sensor scanning implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  `$INSTANCE_NAME`_CSDScanExt() function.
    *
    *  The following tasks are performed:
    *    1. Check if the raw data is not noisy.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Configure and start the scan for the next frequency if the
    *      multi-frequency is enabled.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The ISR handler changes the scanning for the next frequency
    *  channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user code
    *  from macros specified in Component's generated code. Refer to the
    *  \ref group_cysense_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_CSDPostSingleScan(void)
    {
        #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
            `$INSTANCE_NAME`_EntryCallback();
        #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
        (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
            if ((`$INSTANCE_NAME`_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(`$INSTANCE_NAME`_CSD_RESULT_VAL1_PTR) &
                                                        `$INSTANCE_NAME`_CSD_RESULT_VAL1_BAD_CONVS_MSK) >>
                                                        `$INSTANCE_NAME`_CSD_RESULT_VAL1_BAD_CONVS_POS)) &&
                                                        (0u < `$INSTANCE_NAME`_badConversionsNum))
            {
                /* Decrement bad conversions number */
                `$INSTANCE_NAME`_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_CSD_SEQ_START_AZ0_SKIP_MSK |
                                                             `$INSTANCE_NAME`_CSD_SEQ_START_AZ1_SKIP_MSK |
                                                             `$INSTANCE_NAME`_CSD_SEQ_START_START_MSK);
            }
            else
            {
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

            `$INSTANCE_NAME`_SsCSDPostScan();

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 > `$INSTANCE_NAME`_scanFreqIndex)
                {
                    /* Scan the next channel */
                    `$INSTANCE_NAME`_SsNextFrequencyScan();
                }
                else
                {
                    /* All channels are scanned. Reset the frequency scan channel */
                    `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
                    `$INSTANCE_NAME`_SsChangeClkFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_0);

                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
                        /* Disable HW IP block */
                        CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_configCsd);
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

                    /* Update Scan Counter */
                    `$INSTANCE_NAME`_dsRam.scanCounter++;

                    /* Sensor is totally scanned. Reset BUSY flag */
                    `$INSTANCE_NAME`_dsRam.status &= ~(`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_WDGT_SW_STS_BUSY);
                }
            #else
                {
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
                        /* Disable HW IP block */
                        CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_configCsd);
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

                    /* Update Scan Counter */
                    `$INSTANCE_NAME`_dsRam.scanCounter++;

                    /* Sensor is totally scanned. Reset BUSY flag */
                    `$INSTANCE_NAME`_dsRam.status &= ~(`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_WDGT_SW_STS_BUSY);
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

        #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
            `$INSTANCE_NAME`_ExitCallback();
        #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CSDPostMultiScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  `$INSTANCE_NAME`_Scan() or `$INSTANCE_NAME`_ScanAllWidgets() APIs.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  `$INSTANCE_NAME`_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_cysense_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_CSDPostMultiScan(void)
    {
        /* Declare and initialize ptr to sensor IO structure to appropriate address */
        `$INSTANCE_NAME`_FLASH_IO_STRUCT const *curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                                          `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2SnsFlash
                                                          + `$INSTANCE_NAME`_sensorIndex;

        #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
            `$INSTANCE_NAME`_EntryCallback();
        #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
        (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
            if ((`$INSTANCE_NAME`_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(`$INSTANCE_NAME`_CSD_RESULT_VAL1_PTR) &
                                                      `$INSTANCE_NAME`_CSD_RESULT_VAL1_BAD_CONVS_MSK) >>
                                                      `$INSTANCE_NAME`_CSD_RESULT_VAL1_BAD_CONVS_POS)) &&
                                                      (0u < `$INSTANCE_NAME`_badConversionsNum))
            {
                /* Decrement bad conversions number */
                `$INSTANCE_NAME`_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_CSD_SEQ_START_AZ0_SKIP_MSK |
                                                             `$INSTANCE_NAME`_CSD_SEQ_START_AZ1_SKIP_MSK |
                                                             `$INSTANCE_NAME`_CSD_SEQ_START_START_MSK);
            }
            else
            {
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

        `$INSTANCE_NAME`_SsCSDPostScan();

        /* Disable sensor when all frequency channels are scanned */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 == `$INSTANCE_NAME`_scanFreqIndex)
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        {
            /* Disable sensor */
            `$INSTANCE_NAME`_CSDDisconnectSns(curSnsIOPtr);
        }

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 > `$INSTANCE_NAME`_scanFreqIndex)
            {
                 /* Scan the next channel */
                `$INSTANCE_NAME`_SsNextFrequencyScan();
            }
            else
            {
                /* All channels are scanned. Reset the frequency scan channel */
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
                `$INSTANCE_NAME`_SsChangeClkFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_0);

                 /* Scan the next sensor */
                `$INSTANCE_NAME`_SsCSDInitNextScan();
            }
        #else
            /* Scan the next sensor */
            `$INSTANCE_NAME`_SsCSDInitNextScan();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

    #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
        `$INSTANCE_NAME`_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */
}


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDPostMultiScanGanged
****************************************************************************//**
*
* \brief
*  This is an internal ISR function for the multiple-sensor scanning
*  implementation for ganged sensors.
*
* \details
*  This ISR handler is triggered when the user calls the
*  `$INSTANCE_NAME`_Scan() API for a ganged sensor or the
*  `$INSTANCE_NAME`_ScanAllWidgets() API in the project with ganged sensors.
*
*  The following tasks are performed:
*    1. Disable the CSD interrupt.
*    2. Read the Counter register and update the data structure with raw data.
*    3. Connect the Vref buffer to the AMUX bus.
*    4. Disable the CSD block (after the widget has been scanned).
*    5. Update the Scan Counter.
*    6. Reset the BUSY flag.
*    7. Enable the CSD interrupt.
*
*  The ISR handler initializes scanning for the previous sensor when the
*  widget has more than one sensor.
*  The ISR handler initializes scanning for the next widget when the
*  `$INSTANCE_NAME`_ScanAllWidgets() APIs are called and the project has
*  more than one widget.
*  The ISR handler changes the IMO and initializes scanning for the next
*  frequency channels when multi-frequency scanning is enabled.
*
*  This function has two Macro Callbacks that allow calling the user
*  code from macros specified in Component's generated code. Refer to the
*  \ref group_cysense_macrocallbacks section of the PSoC Creator User Guide
*  for details.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDPostMultiScanGanged(void)
{
    #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

        /* Clear pending interrupt */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
    (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
        if ((`$INSTANCE_NAME`_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(`$INSTANCE_NAME`_CSD_RESULT_VAL1_PTR) &
                                                  `$INSTANCE_NAME`_CSD_RESULT_VAL1_BAD_CONVS_MSK) >>
                                                  `$INSTANCE_NAME`_CSD_RESULT_VAL1_BAD_CONVS_POS)) &&
                                                  (0u < `$INSTANCE_NAME`_badConversionsNum))
        {
            /* Decrement bad conversions number */
            `$INSTANCE_NAME`_badConversionsNum--;

            /* Start the re-scan */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_CSD_SEQ_START_AZ0_SKIP_MSK |
                                                         `$INSTANCE_NAME`_CSD_SEQ_START_AZ1_SKIP_MSK |
                                                         `$INSTANCE_NAME`_CSD_SEQ_START_START_MSK);
        }
        else
        {
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

        `$INSTANCE_NAME`_SsCSDPostScan();

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 == `$INSTANCE_NAME`_scanFreqIndex)
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        {
            `$INSTANCE_NAME`_SsCSDDisconnectSnsExt((uint32)`$INSTANCE_NAME`_widgetIndex, (uint32)`$INSTANCE_NAME`_sensorIndex);
        }

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 > `$INSTANCE_NAME`_scanFreqIndex)
            {
                 /* Scan the next channel */
                `$INSTANCE_NAME`_SsNextFrequencyScan();
            }
            else
            {
                /* All channels are scanned. Reset the frequency scan channel */
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
                `$INSTANCE_NAME`_SsChangeClkFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_0);

                 /* Scan the next sensor */
                `$INSTANCE_NAME`_SsCSDInitNextScan();
            }
        #else
             /* Scan the next sensor */
            `$INSTANCE_NAME`_SsCSDInitNextScan();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

    #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
        `$INSTANCE_NAME`_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */

    (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */


#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)) */

/** \}
 * \endcond */


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN))

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDPostScan
****************************************************************************//**
*
* \brief
*   This function reads rawdata and releases required HW resources after scan.
*
* \details
*   This function performs following tasks after scan:
*   - Reads SlotResult from Raw Counter;
*   - Inits bad Conversions number;
*   - Disconnects Vrefhi from AMUBUF positive input;
*   - Disconnects AMUBUF output from CSDBUSB with sych PHI2+HSCMP;
*   - Opens HCBV and HCBG switches.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SsCSDPostScan(void)
{
    uint32 tmpRawData;
    uint32 tmpMaxCount;
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                        `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2WdgtRam;

    /* Read SlotResult from Raw Counter */
    tmpRawData = `$INSTANCE_NAME`_CSD_RESULT_VAL1_REG & `$INSTANCE_NAME`_CSD_RESULT_VAL1_VALUE_MSK;

    tmpMaxCount = ((1uL << ptrWdgt->resolution) - 1uL);
    if(tmpRawData < tmpMaxCount)
    {
        `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_scanFreqIndex] = CY_LO16(tmpRawData);
    }
    else
    {
        `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_scanFreqIndex] = CY_LO16(tmpMaxCount);
    }

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)
        /* Init bad Conversions number */
        `$INSTANCE_NAME`_badConversionsNum = `$INSTANCE_NAME`_BAD_CONVERSIONS_NUM;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN) */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        /* Open HCBV and HCBG switches */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN |
                                                         `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDInitNextScan
****************************************************************************//**
*
* \brief
*   This function initializes the next sensor scan.
*
* \details
*   The function increments the sensor index, updates sense clock for matrix
*   or touchpad widgets only, sets up Compensation IDAC, enables the sensor and
*   scans it. When all the sensors are scanned it continues to set up the next widget
*   until all the widgets are scanned. The CSD block is disabled when all the widgets are
*   scanned.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SsCSDInitNextScan(void)
{
    /* Declare and initialize ptr to widget and sensor structures to appropriate address */
    #if (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) || \
            (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) || \
            (((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) && \
            (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))))
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
            `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2WdgtRam;
    #endif

    /* Check if all the sensors are scanned in widget */
    if (((uint8)`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex)].totalNumSns - 1u) > `$INSTANCE_NAME`_sensorIndex)
    {
        /* Increment sensor index to configure next sensor in widget */
        `$INSTANCE_NAME`_sensorIndex++;

        /* Update global pointer to `$INSTANCE_NAME`_RAM_SNS_STRUCT to current sensor */
        `$INSTANCE_NAME`_curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                                                  `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2SnsRam
                                                  + `$INSTANCE_NAME`_sensorIndex;

        /* Configure clock divider to row or column */
        #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) && \
             (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
            if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex)].wdgtType) ||
                (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex)].wdgtType))
            {
                `$INSTANCE_NAME`_SsCSDConfigClock();

                /* Set up scanning resolution */
                `$INSTANCE_NAME`_SsCSDCalculateScanDuration(ptrWdgt);
            }
        #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) && \
                   (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))) */

        /* Setup Compensation IDAC for next sensor in widget */
        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) || \
             (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
            `$INSTANCE_NAME`_SsCSDSetUpIdacs(ptrWdgt);
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) || \
             (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */

        /* Enable sensor */
        `$INSTANCE_NAME`_SsCSDConnectSensorExt((uint32)`$INSTANCE_NAME`_widgetIndex, (uint32)`$INSTANCE_NAME`_sensorIndex);

        /* Proceed scanning */
        `$INSTANCE_NAME`_SsCSDStartSample();
    }
    /* Call scan next widget API if requested, if not, complete the scan */
    else
    {
        `$INSTANCE_NAME`_sensorIndex = 0u;

        /* Current widget is totally scanned. Reset WIDGET BUSY flag */
        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_WDGT_SW_STS_BUSY;

        /* Check if all the widgets have been scanned */
        if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_requestScanAllWidget)
        {
            /* Configure and begin scanning next widget */
            `$INSTANCE_NAME`_SsPostAllWidgetsScan();
        }
        else
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
                /* Disable the CSD block */
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_configCsd);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

            /* all the widgets are totally scanned. Reset BUSY flag */
            `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;

            /* Update scan Counter */
            `$INSTANCE_NAME`_dsRam.scanCounter++;
        }
    }
}

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsNextFrequencyScan
    ****************************************************************************//**
    *
    * \brief
    *   This function scans the sensor on the next frequency channel.
    *
    * \details
    *   The function increments the frequency channel, changes scan frequency and 
    *   initializes the scanning process of the same sensor.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsNextFrequencyScan(void)
    {
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                                        `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2WdgtRam;

        `$INSTANCE_NAME`_scanFreqIndex++;

        /* Set Immunity */
        `$INSTANCE_NAME`_SsChangeClkFreq((uint32)`$INSTANCE_NAME`_scanFreqIndex);

        /* Update IDAC registers */
        `$INSTANCE_NAME`_SsCSDSetUpIdacs(ptrWdgt);

        /* Proceed scanning */
        `$INSTANCE_NAME`_SsCSDStartSample();
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)) */


/* [] END OF FILE */
