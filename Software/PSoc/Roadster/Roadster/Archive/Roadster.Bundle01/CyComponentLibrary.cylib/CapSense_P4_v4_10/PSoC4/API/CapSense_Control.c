/***************************************************************************//**
* \file `$INSTANCE_NAME`_Control.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* This file provides the source code to the Control module API of the Component.
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

#include "cytypes.h"
#include "CyLib.h"
#include "cyPm.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Control.h"
#include "`$INSTANCE_NAME`_Processing.h"
#include "`$INSTANCE_NAME`_Filter.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#include "`$INSTANCE_NAME`_Tuner.h"

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #include "`$INSTANCE_NAME`_SelfTest.h"
#endif

#if (0u != `$INSTANCE_NAME`_ADC_EN)
    #include "`$INSTANCE_NAME`_Adc.h"
#endif /* (0u != `$INSTANCE_NAME`_ADC_EN) */

/***********************************************************************************************************************
* Local definition
***********************************************************************************************************************/
#define `$INSTANCE_NAME`_INIT_DONE   (1u)
#define `$INSTANCE_NAME`_INIT_NEEDED (0u)

/***********************************************************************************************************************
* Local variables
***********************************************************************************************************************/
static uint8 `$INSTANCE_NAME`_InitVar = `$INSTANCE_NAME`_INIT_NEEDED;

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* \brief
*  Initializes Component hardware and firmware modules. This function should be 
*  called by the application program prior to calling any other function of the 
*  Component.
*
* \details
*  This function initializes the Component hardware and firmware modules and 
*  should be called by the application program prior to calling any other API
*  of the Component. When this function is called, the following tasks are 
*  executed as part of the initialization process:
*    1. Initialize the registers of the \ref group_structures variable 
*       `$INSTANCE_NAME`_dsRam based on the user selection in Component 
*       configuration wizard. 
*    2. Configure the hardware to perform sensing.
*    \if SECTION_C_HIGH_LEVEL
*    3. If SmartSense Auto-tuning is selected for the CSD Tuning mode in the 
*       Basic tab, the auto-tuning algorithm is executed to set the optimal 
*       values for the hardware parameters of the widgets/sensors.
*    \endif
*    4. Calibrate the sensors and find the optimal values for IDACs of each 
*       widget / sensor, if Enable auto-calibration is enabled on the
*       Advanced -> Mode Setting subtab.
*    5. Perform a scan for all sensors and initialize the baseline history. 
*       During the scan, CPU is in the sleep mode to save power.
*    6. If the firmware filters are enabled in the Advanced General tab, the 
*       filter histories are also initialized.

*  Any next call of this API repeats an initialization process except for 
*  data structure initialization. Therefore, it is possible to change the 
*  Component configuration from the application program by writing to the 
*  data structure registers and calling this function again. This is also 
*  done inside the `$INSTANCE_NAME`_RunTuner() function when a restart command 
*  is received. 
*
*  When the Component operation is stopped by the `$INSTANCE_NAME`_Stop() 
*  function, the `$INSTANCE_NAME`_Start() function repeats an initialization 
*  process including data structure initialization.
*
* \return
*  Returns the status of the initialization process. If CYRET_SUCCESS is not 
*  received, some of the initialization fails and the Component may not operate
*  as expected.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_Start(void)
{
    cystatus result;    
    
    /* Initialize `$INSTANCE_NAME` modules */
    result = `$INSTANCE_NAME`_Initialize();
   
    #if (`$INSTANCE_NAME`_CSD_AUTOTUNE != `$INSTANCE_NAME`_CSD_SS_DIS)
        if (CYRET_SUCCESS == result)
        {
            result = `$INSTANCE_NAME`_SsAutoTune();
        }
    #endif /* #if (`$INSTANCE_NAME`_CSD_AUTOTUNE != `$INSTANCE_NAME`_CSD_SS_DIS) */

    #if (`$INSTANCE_NAME`_ANY_NONSS_AUTOCAL)
        if (CYRET_SUCCESS == result)
        {
            result = `$INSTANCE_NAME`_CalibrateAllWidgets();
        }
    #endif /* (`$INSTANCE_NAME`_ANY_NONSS_AUTOCAL) */

    if (CYRET_SUCCESS == result)
    {
        result = `$INSTANCE_NAME`_ScanAllWidgets();
    }

    if (CYRET_SUCCESS == result)
    {
        /* Wait for scan to finish. */
        while(`$INSTANCE_NAME`_NOT_BUSY != `$INSTANCE_NAME`_IsBusy())
        {            
        }
    }
    `$INSTANCE_NAME`_FtInitialize();
    `$INSTANCE_NAME`_InitializeAllBaselines();

    #if (0u != `$INSTANCE_NAME`_ADC_EN)
        `$INSTANCE_NAME`_`$AdcModulePrefix`Initialize();
    #endif /* (0u != `$INSTANCE_NAME`_ADC_EN) */

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Initialize
****************************************************************************//**
*
* \brief
*  This function initializes the `$INSTANCE_NAME` Component.
*
* \details
*  This API initializes all sub-modules of the `$INSTANCE_NAME` Component:
*   - Data Structure - set the default Component parameters defined in the Customizer.
*   - Data Processing - resets all widget statuses.
*   - Tuner - resets tuning state.
*   - Sensing - prepares CSD HW for operation.
*
*  Note that Data Structure module is initialized only once after the reset or
*  `$INSTANCE_NAME`_Stop() API is called. The repeated calls of Initialize API
*  will not re-initialize Data Structure. This is done to preserve Component
*  parameters that user may set in runtime.
*
*  If default Component parameters are needed the `$INSTANCE_NAME`_DsInitialize()
*  API must be called directly from the application code.
*
* \return
*  Return CYRET_SUCCESS if the initialization was successful.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_Initialize(void)
{
    cystatus result;

    /* The Data Structure and Tuner are initialized only once */
    if (`$INSTANCE_NAME`_INIT_NEEDED == `$INSTANCE_NAME`_InitVar)
    {
        `$INSTANCE_NAME`_DsInitialize();
        `$INSTANCE_NAME`_TuInitialize();
        `$INSTANCE_NAME`_InitVar = `$INSTANCE_NAME`_INIT_DONE;
    }

    `$INSTANCE_NAME`_DpInitialize();

    result = `$INSTANCE_NAME`_SsInitialize();

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* \brief
*  Stops the Component operation.
*
* \details
*  This function stops the Component operation, no sensor scanning can be 
*  executed when the Component is stopped. Once stopped, the hardware block may 
*  be reconfigured by the application program for any other special usage. The 
*  Component operation can be resumed by calling the `$INSTANCE_NAME`_Resume() 
*  function or the Component can be reset by calling the 
*  `$INSTANCE_NAME`_Start() function.
*  
*  This function should be called when no scanning is in progress. 
*  I.e. `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
* \return
*  Returns the status of the stop process. If CYRET_SUCCESS is not received, 
*  the stop process fails and retries may be required.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_Stop(void)
{
    cystatus result = CYRET_SUCCESS;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
        /* Release CSD resources */
        result = `$INSTANCE_NAME`_SsReleaseResources();

        /* Release ADC resources */
        `$INSTANCE_NAME`_`$AdcCapSensePrefix`Stop();
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */

    `$INSTANCE_NAME`_InitVar = `$INSTANCE_NAME`_INIT_NEEDED;

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Resume
****************************************************************************//**
*
* \brief
*  Resumes the Component operation if `$INSTANCE_NAME`_Stop() function was 
*  called previously.
*
* \details
*  This function resumes the Component operation if the operation is stopped
*  previously by the `$INSTANCE_NAME`_Stop() function. The following tasks are 
*  executed as part of the operation resume process:
*    1. Reset all Widgets/Sensors status.
*    2. Configure the hardware to perform capacitive sensing.
*
* \return
*  Returns the status of the resume process. If CYRET_SUCCESS is not received,
*  the resume process fails and retries may be required.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_Resume(void)
{
    cystatus result;

    /* The Tuner are initialized only once to do not break communication */
    if (`$INSTANCE_NAME`_INIT_NEEDED == `$INSTANCE_NAME`_InitVar)
    {
        `$INSTANCE_NAME`_TuInitialize();
        `$INSTANCE_NAME`_InitVar = `$INSTANCE_NAME`_INIT_DONE;
    }
    `$INSTANCE_NAME`_DpInitialize();

    result = `$INSTANCE_NAME`_SsInitialize();

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ProcessAllWidgets
****************************************************************************//**
*
* \brief
*  Performs full data processing of all enabled widgets.
*
* \details
*  This function performs all data processes for all enabled widgets in the 
*  Component. The following tasks are executed as part of processing all the 
*  widgets:
*    1. Apply raw-count filters to raw counts, if they are enabled in the 
*       customizer.
*    2. Update thresholds if the SmartSense Full Auto-Tuning is enabled in
*       the customizer.
*    3. Update the Baselines and Difference counts for all sensors.
*    4. Update the sensor and widget status (on/off), update centroid for 
*       sliders and X/Y position for touchpads.
*  
*  Disabled widgets are not processed. To disable/enable a widget, set 
*  appropriate values in the 
*  `$INSTANCE_NAME`_WDGT_ENABLE<RegisterNumber>_PARAM_ID register using the
*  `$INSTANCE_NAME`_SetParam() function.
*  This function should be called only after all the sensors in the Component
*  are scanned. Calling this function multiple times without sensor scanning
*  causes unexpected behavior.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to `$INSTANCE_NAME`_CheckBaselineDuplication() for details.
*
* \return
*  Returns the status of the processing operation. If CYRET_SUCCESS is not received, 
*  the processing fails and retries may be required.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_ProcessAllWidgets(void)
{
    uint32 wdgtId;
    cystatus result = CYRET_SUCCESS;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;

    ptrFlashWdgt = `$INSTANCE_NAME`_dsFlash.wdgtArray;

    for (wdgtId = 0u; wdgtId < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtId++)
    {
        if (0uL != `$INSTANCE_NAME`_GET_WIDGET_EN_STATUS(wdgtId))
        {
            switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
            {
            #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
                case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                    result = `$INSTANCE_NAME`_DpProcessCsdWidgetRawCounts(ptrFlashWdgt);
                    `$INSTANCE_NAME`_DpProcessCsdWidgetStatus(wdgtId, ptrFlashWdgt);
                    break;
            #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

            #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
                case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                    result = `$INSTANCE_NAME`_DpProcessCsxWidgetRawCounts(ptrFlashWdgt);
                    `$INSTANCE_NAME`_DpProcessCsxWidgetStatus(wdgtId, ptrFlashWdgt);
                    break;
            #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */

            #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS)
                case `$INSTANCE_NAME`_SENSE_METHOD_ISX_E:
                    result = `$INSTANCE_NAME`_DpProcessIsxWidgetRawCounts(ptrFlashWdgt);
                    `$INSTANCE_NAME`_DpProcessIsxWidgetStatus(wdgtId, ptrFlashWdgt);
                    break;
            #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS) */

            default:
                CYASSERT(0u);
                break;
            }
                    
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
                if (CYRET_SUCCESS != result)
                {
                    `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(wdgtId, result);
                    result = CYRET_BAD_DATA;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */
                    
        }
        ptrFlashWdgt++;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ProcessWidget
****************************************************************************//**
*
* \brief
*  Performs full data processing of the specified widget if it is enabled.
*
* \details
*  This function performs exactly the same tasks as 
*  `$INSTANCE_NAME`_ProcessAllWidgets(), but only for a specified widget. This 
*  function can be used along with the `$INSTANCE_NAME`_SetupWidget() and 
*  `$INSTANCE_NAME`_Scan() functions to scan and process data for a specific
*  widget. This function should be called only after all the sensors in the 
*  widgets are scanned. A disabled widget is not processed by this function.
*  
*  The pipeline scan method (i.e. during scanning of a widget perform processing
*  of the previously scanned widget) can be implemented using this function and
*  it may reduce the total scan/process time, increase the refresh rate and 
*  decrease the power consumption.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to `$INSTANCE_NAME`_CheckBaselineDuplication() for details.
*
* \param widgetId 
*  Specify the ID number of the widget to be processed. 
*  A macro for the widget ID can be found in the 
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID
*
* \return
*  Returns the status of the widget processing:
*  - CYRET_SUCCESS if operation is successfully completed
*  - CYRET_BAD_PARAM if the input parameter is invalid
*  - CYRET_INVALID_STATE if the specified widget is disabled
*  - CYRET_BAD_DATA if processing was failed
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_ProcessWidget(uint32 widgetId)
{
    cystatus result = CYRET_SUCCESS;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;

    if (widgetId >= `$INSTANCE_NAME`_TOTAL_WIDGETS)
    {
        result = CYRET_BAD_PARAM;
    }

    if ((CYRET_SUCCESS == result) && (0uL == `$INSTANCE_NAME`_GET_WIDGET_EN_STATUS(widgetId)))
    {
        result = CYRET_INVALID_STATE;
    }

    if (CYRET_SUCCESS == result)
    {
        ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];

        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                result = `$INSTANCE_NAME`_DpProcessCsdWidgetRawCounts(ptrFlashWdgt);
                `$INSTANCE_NAME`_DpProcessCsdWidgetStatus(widgetId, ptrFlashWdgt);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                result = `$INSTANCE_NAME`_DpProcessCsxWidgetRawCounts(ptrFlashWdgt);
                `$INSTANCE_NAME`_DpProcessCsxWidgetStatus(widgetId, ptrFlashWdgt);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_ISX_E:
                result = `$INSTANCE_NAME`_DpProcessIsxWidgetRawCounts(ptrFlashWdgt);
                `$INSTANCE_NAME`_DpProcessIsxWidgetStatus(widgetId, ptrFlashWdgt);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS) */

        default:
            CYASSERT(0u);
            break;
        }

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
            if (CYRET_SUCCESS != result)
            {
                `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(widgetId, result);
                result = CYRET_BAD_DATA;
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */
    }
    return result;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ProcessWidgetExt
****************************************************************************//**
*
* \brief
*  Performs customized data processing on the selected widget.
*
* \details
*  This function performs data processes for the specified widget specified by 
*  the mode parameter. The execution order of the requested operations is from 
*  LSB to MSB of the mode parameter. If a different order is needed, this API 
*  can be called multiple times with the required mode parameter. 
*  
*  This function can be used with any of the available scan functions. This 
*  function should be called only after all sensors in the specified widget are
*  scanned. Calling this function multiple times with the same mode without 
*  sensor scanning causes unexpected behavior. This function ignores the value 
*  of the wdgtEnable register. 
*  \if SECTION_C_LOW_LEVEL
*  The `$INSTANCE_NAME`_PROCESS_CALC_NOISE and 
*  `$INSTANCE_NAME`_PROCESS_THRESHOLDS flags are supported by the CSD sensing
*  method only when the auto-tuning mode is enabled.
*  \endif
*  The pipeline scan method (i.e. during scanning of a widget perform processing
*  of a previously scanned widget) can be implemented using this function and it
*  may reduce the total scan/process time, increase the refresh rate and 
*  decrease the power consumption.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to `$INSTANCE_NAME`_CheckBaselineDuplication() for details.
*
* \param widgetId 
*  Specify the ID number of the widget to be processed. 
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header 
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.

* \param mode 
*  Specify the type of widget processing that needs to be executed for the 
*  specified widget:
*    1.	Bits [31..6] - Reserved
*    2.	Bits [5..0] - `$INSTANCE_NAME`_PROCESS_ALL - Execute all tasks
*    3.	Bit [5] - `$INSTANCE_NAME`_PROCESS_STATUS - Update Status (on/off, 
*       centroid position)
*    \if SECTION_C_LOW_LEVEL
*    4.	Bit [4] - `$INSTANCE_NAME`_PROCESS_THRESHOLDS - Update Thresholds 
*       (only in CSD auto-tuning mode)
*    5.	Bit [3] - `$INSTANCE_NAME`_PROCESS_CALC_NOISE - Calculate Noise (only in
*       CSD auto-tuning mode)
*    \endif
*    6.	Bit [2] - `$INSTANCE_NAME`_PROCESS_DIFFCOUNTS - Update Difference Counts
*    7.	Bit [1] - `$INSTANCE_NAME`_PROCESS_BASELINE - Update Baselines
*    8.	Bit [0] - `$INSTANCE_NAME`_PROCESS_FILTER - Run Firmware Filter
*
* \return
*  Returns the status of the widget processing operation:
*  - CYRET_SUCCESS if processing is successfully performed
*  - CYRET_BAD_PARAM if the input parameter is invalid
*  - CYRET_BAD_DATA if processing was failed
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_ProcessWidgetExt(uint32 widgetId, uint32 mode)
{
    uint32 snsCount;
    cystatus result = CYRET_BAD_PARAM;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT fltrHistV;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns;

    #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
        uint32 isProxWdgt;
    #endif

    if (widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS)
    {
        ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
        snsCount = `$INSTANCE_NAME`_GET_SNS_CNT_BY_PTR(ptrFlashWdgt);
        ptrSns = ptrFlashWdgt->ptr2SnsRam;
        fltrHistV.ptr = ptrFlashWdgt->ptr2FltrHistory;

        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
            {
                /* Determine if widget is type of proximity.
                 * The Proximity widgets use different filters and
                 * therefore have different filter history object structure */
                isProxWdgt =
                    (`$INSTANCE_NAME`_GET_WIDGET_TYPE(ptrFlashWdgt) == `$INSTANCE_NAME`_WD_PROXIMITY_E) ? 1Lu : 0Lu;

                /* Run the desired processing for the all CSD widget sensors */
                for (;snsCount-- > 0u;)
                {
                    result = `$INSTANCE_NAME`_DpProcessCsdSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);

                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
                        if (CYRET_SUCCESS != result)
                        {
                            result = (result | `$INSTANCE_NAME`_TST_LSBYTE) & snsCount;
                        }
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

                    /* Move to the next sensor and filter history objects */
                    ptrSns++;
                    `$INSTANCE_NAME`_INC_FLTR_OBJ_VARIANT(isProxWdgt, fltrHistV);
                }

                if (0u != (mode & `$INSTANCE_NAME`_PROCESS_STATUS))
                {
                    `$INSTANCE_NAME`_DpProcessCsdWidgetStatus(widgetId, ptrFlashWdgt);
                }
                break;
            }
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:

                #if (0u != `$INSTANCE_NAME`_CSX_MULTIPHASE_TX_EN)
                    if ((0u != (mode & `$INSTANCE_NAME`_PROCESS_DECONVOLUTION)) &&
                        (0u != (ptrFlashWdgt->staticConfig & `$INSTANCE_NAME`_MULTIPHASE_TX_MASK)))
                    {
                        `$INSTANCE_NAME`_DpDeconvolution(ptrFlashWdgt);
                    }
                #endif /* #if (0u != `$INSTANCE_NAME`_CSX_MULTIPHASE_TX_EN) */

                /* Run the desired processing for the all CSX widget sensors */
                for (;snsCount-- > 0u;)
                {
                    result = `$INSTANCE_NAME`_DpProcessCsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);

                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
                        if (CYRET_SUCCESS != result)
                        {
                            result = (result | `$INSTANCE_NAME`_TST_LSBYTE) & snsCount;
                        }
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

                    /* Move to the next sensor and filter history objects */
                    ptrSns++;
                    `$INSTANCE_NAME`_INC_FLTR_OBJ_VARIANT(0u, fltrHistV);
                }

                if (0u != (mode & `$INSTANCE_NAME`_PROCESS_STATUS))
                {
                    `$INSTANCE_NAME`_DpProcessCsxWidgetStatus(widgetId, ptrFlashWdgt);
                }
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_ISX_E:
                /* Run the desired processing for the all ISX widget sensors */
                for (;snsCount-- > 0u;)
                {
                    result = `$INSTANCE_NAME`_DpProcessIsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                    
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
                        if (CYRET_SUCCESS != result)
                        {
                            result = (result | `$INSTANCE_NAME`_TST_LSBYTE) & snsCount;
                        }
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */
                    
                    /* Move to the next sensor and filter history objects */
                    ptrSns++;
                    `$INSTANCE_NAME`_INC_FLTR_OBJ_VARIANT(0u, fltrHistV);
                }

                if (0u != (mode & `$INSTANCE_NAME`_PROCESS_STATUS))
                {
                    `$INSTANCE_NAME`_DpProcessIsxWidgetStatus(widgetId, ptrFlashWdgt);
                }
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS) */
        
        default:
            CYASSERT(0u);
            break;
        }

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
            if (CYRET_SUCCESS != result)
            {
                `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(widgetId, snsCount);
                result = CYRET_BAD_DATA;
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ProcessSensorExt
****************************************************************************//**
*
* \brief
*  Performs customized data processing on the selected widget's sensor.
*
* \details
*  This function performs data processes for the specified sensor specified by
*  the mode parameter. The execution order of the requested operations is from 
*  LSB to MSB of the mode parameter. If a different order is needed, this 
*  function can be called multiple times with the required mode parameter.
*  
*  This function can be used with any of the available scan functions. This 
*  function should be called only after a specified sensor in the widget is 
*  scanned. Calling this function multiple times with the same mode without 
*  sensor scanning causes unexpected behavior. This function ignores the value 
*  of the wdgtEnable register. 
*  
*  \if SECTION_C_LOW_LEVEL
*  The `$INSTANCE_NAME`_PROCESS_CALC_NOISE and 
*  `$INSTANCE_NAME`_PROCESS_THRESHOLDS flags are supported by the CSD sensing 
*  method only when the auto-tuning mode is enabled.
*  \endif
*
*  The pipeline scan method (i.e. during scanning of a sensor perform processing
*  of a previously scanned sensor) can be implemented using this function and it
*  may reduce the total scan/process time, increase the refresh rate and 
*  decrease the power consumption.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to `$INSTANCE_NAME`_CheckBaselineDuplication() for details.
*
* \param widgetId  
*  Specify the ID number of the widget to process one of its sensors. 
*  A macro for the widget ID can be found in the 
*  `$INSTANCE_NAME` Configuration header file defined as 
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID
*  
* \param sensorId  
*  Specify the ID number of the sensor within the widget to process it.
*  A macro for the sensor ID within a specified widget can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as 
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID
*  
* \param mode      
*  Specify the type of the sensor processing that needs to be executed for the
*  specified sensor:
*    1. Bits [31..5] - Reserved
*    2. Bits [4..0] - `$INSTANCE_NAME`_PROCESS_ALL - Executes all tasks
*    \if SECTION_C_LOW_LEVEL
*    3. Bit [4] - `$INSTANCE_NAME`_PROCESS_THRESHOLDS - Updates Thresholds (only
*       in auto-tuning mode)
*    4. Bit [3] - `$INSTANCE_NAME`_PROCESS_CALC_NOISE - Calculates Noise (only 
*       in auto-tuning mode)
*    \endif
*    5. Bit [2] - `$INSTANCE_NAME`_PROCESS_DIFFCOUNTS - Updates Difference Count
*    6. Bit [1] - `$INSTANCE_NAME`_PROCESS_BASELINE - Updates Baseline
*    7. Bit [0] - `$INSTANCE_NAME`_PROCESS_FILTER - Runs Firmware Filter
*
* \return
*  Returns the status of the sensor process operation:
*  - CYRET_SUCCESS if processing is successfully performed
*  - CYRET_BAD_PARAM if the input parameter is invalid
*  - CYRET_BAD_DATA if processing was failed
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_ProcessSensorExt(uint32 widgetId, uint32 sensorId, uint32 mode)
{
    cystatus result = CYRET_BAD_PARAM;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt;
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT fltrHistV;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSns;

    if ((widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS) && (sensorId < `$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)))
    {
        result = CYRET_SUCCESS;

        ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
        fltrHistV.ptr = ptrFlashWdgt->ptr2FltrHistory;
        ptrSns = ptrFlashWdgt->ptr2SnsRam;
        ptrSns += sensorId;

        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                if (`$INSTANCE_NAME`_WD_PROXIMITY_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType)
                {
                    #if (0u != `$INSTANCE_NAME`_PROX_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrProx[sensorId];
                    #endif /* #if (0u != `$INSTANCE_NAME`_PROX_RC_FILTER_EN) */
                }
                else
                {
                    #if (0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrRegular[sensorId];
                    #endif /* #if (0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN) */
                }

                result = `$INSTANCE_NAME`_DpProcessCsdSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                #if (0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN)
                    fltrHistV.ptr = &fltrHistV.ptrRegular[sensorId];
                #endif /* #if (0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN) */

                result = `$INSTANCE_NAME`_DpProcessCsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */
        
        #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_ISX_E:
                if (`$INSTANCE_NAME`_WD_PROXIMITY_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType)
                {
                    #if (0u != `$INSTANCE_NAME`_PROX_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrProx[sensorId];
                    #endif /* #if (0u != `$INSTANCE_NAME`_PROX_RC_FILTER_EN) */
                }
                else
                {
                    #if (0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrRegular[sensorId];
                    #endif /* #if (0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN) */
                }

                result = `$INSTANCE_NAME`_DpProcessIsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS) */

        default:
            CYASSERT(0u);
            break;
        }
                
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
            if (CYRET_SUCCESS != result)
            {
                `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(widgetId, sensorId);
                result = CYRET_BAD_DATA;
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */
        
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* \brief
*  Prepares the Component to deep sleep.
*
* \details
*  Currently this function is empty and exists as a place for future updates, 
*  this function shall be used to prepare the Component to enter deep sleep.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
* \brief
*  This function shall be used to resume the Component after exiting deep sleep.
*
* \details
*  This function resumes the Component after sleep.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
	#if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
		#if(`$INSTANCE_NAME`_CSDV2_ANALOG_WAKEUP_DELAY_US > 0uL)
			CyDelayUs(`$INSTANCE_NAME`_CSDV2_ANALOG_WAKEUP_DELAY_US);
		#endif /* (`$INSTANCE_NAME`_CSDV2_ANALOG_WAKEUP_DELAY_US > 0uL) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


/* [] END OF FILE */
