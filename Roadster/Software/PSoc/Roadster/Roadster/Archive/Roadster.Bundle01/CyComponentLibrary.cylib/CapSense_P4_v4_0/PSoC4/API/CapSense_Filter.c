/***************************************************************************//**
* \file     `$INSTANCE_NAME`_Filter.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief    This file contains the implementation source code to implement all 
*           firmware filters.
*
* \see      CapSense P4 v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
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

#include "`$INSTANCE_NAME`_Filter.h"
#include "`$INSTANCE_NAME`_Configuration.h"

#if (0 != (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN))
    #include "`$INSTANCE_NAME`_SmartSense_LL.h"
#endif /* (0 != (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN)) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #include "`$INSTANCE_NAME`_SelfTest.h"
#endif

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtInitialize
****************************************************************************//**
*
* \brief
*    Initializes all the firmware filter history, except the baseline filter.
*
* \details
*    Initializes all the firmware filter history, except the baseline filter.
*
*******************************************************************************/
void `$INSTANCE_NAME`_FtInitialize(void)
{
    uint32 widgetId;
    uint32 sensorId;
    uint32 sensorsNumber;

    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj;
    
    #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWidgetRam;
        SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT *ptrNoiseEnvelope = NULL;
    #endif /* #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN */
    
    for (widgetId = `$INSTANCE_NAME`_TOTAL_WIDGETS; widgetId-- > 0u;)
    {
        ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
        
        #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN
            ptrWidgetRam = ptrWidget->ptr2WdgtRam;
        #endif /* #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN */

        /* Find total amount of sensors in specified widget */   
        sensorsNumber = `$INSTANCE_NAME`_GET_SNS_CNT_BY_PTR(ptrWidget);    
    
        for (sensorId = sensorsNumber; sensorId-- > 0u;) 
        {
            /* Find pointer to specified sensor object */
            ptrSensor = ptrWidget->ptr2SnsRam;
            ptrSensor = &ptrSensor[sensorId];
                        
            /* Find pointer to to specified filter sensor object */
            ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;

            #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN
                /* Find pointer to specified noise envelope sensor object */
                ptrNoiseEnvelope = ptrWidget->ptr2NoiseEnvlp;
                ptrNoiseEnvelope = &ptrNoiseEnvelope[sensorId];    
            #endif /* #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN */
            
            if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
            {
                #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)             
                    ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
                #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
            }
            else
            {
                #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)             
                    ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
                #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
            }
            
            #if (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN)
                `$INSTANCE_NAME`_InitializeIIRInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
            #endif /* (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN) */                

            #if (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
                `$INSTANCE_NAME`_InitializeMedianInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
            #endif /* (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN) */

            #if (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN)
                `$INSTANCE_NAME`_InitializeAverageInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
            #endif /* (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN) */
            
            #if (`$INSTANCE_NAME`_ALP_FILTER_EN)
                `$INSTANCE_NAME`_InitializeALPInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
            #endif
            
            #if (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN)
                if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                    `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
                {
                    SmartSense_InitializeNoiseEnvelope(ptrSensor->raw[0u], ptrWidgetRam->sigPFC, ptrNoiseEnvelope);
                }
            #endif /* #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN */
        }
    }   
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateAllBaselines
****************************************************************************//**
*
* \brief    
*  Updates the baseline for all sensors in all widgets.
*
* \details
*  Updates the baseline for all sensors in all widgets. Baseline updating is a 
*  part of data processing performed by the process functions. So, no need to 
*  call this function except a specific process flow is implemented.
*  
*  This function ignores the value of the wdgtEnable register. Multiple calling 
*  of this function (or any other function with a baseline updating task) 
*  without scanning leads to unexpected behavior.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to `$INSTANCE_NAME`_CheckBaselineDuplication() for details.
*
* \return   
*  Returns the status of the update baseline operation of all widgets:
*  - CYRET_SUCCESS if operation was successfully completed
*  - CYRET_BAD_DATA if baseline processing failed
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_UpdateAllBaselines(void)
{
    uint32 widgetId; 
    cystatus bslnStatus = CYRET_SUCCESS;
    
    for(widgetId = `$INSTANCE_NAME`_TOTAL_WIDGETS; widgetId-- > 0u;)
    {            
        bslnStatus |= `$INSTANCE_NAME`_UpdateWidgetBaseline(widgetId);       
    }      
    
    return(bslnStatus);
}
  

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateWidgetBaseline
****************************************************************************//**
*
* \brief    
*  Updates the baseline for all sensors in a widget specified by input parameter.
*
* \details  
*  This function performs exactly the same tasks as 
*  `$INSTANCE_NAME`_UpdateAllBaselines(), but only for a specified widget.
*  
*  This function ignores the value of the wdgtEnable register. Multiple calling
*  of this function (or any other function with a baseline updating task) 
*  without scanning leads to unexpected behavior.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to `$INSTANCE_NAME`_CheckBaselineDuplication() for details.
*
* \param widgetId 
*  Specify the ID number of the widget to update the baseline of all sensors
*  in the widget.
*  A macro for the widget ID can be found in the 
*  `$INSTANCE_NAME` Configuration header file defined as 
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \return   
*  Returns the status of the specified widget update baseline operation:
*  - CYRET_SUCCESS if operation was successfully completed
*  - CYRET_BAD_DATA if baseline processing failed
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_UpdateWidgetBaseline(uint32 widgetId)
{
    uint32 sensorId;       
    uint32 sensorsNumber;  

    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];    
    cystatus bslnStatus = CYRET_SUCCESS;    
    
    /* Find total amount of sensors in specified widget */   
    sensorsNumber = `$INSTANCE_NAME`_GET_SNS_CNT_BY_PTR(ptrWidget);    
    
    for(sensorId = sensorsNumber; sensorId-- > 0u;)
    {
        bslnStatus |= `$INSTANCE_NAME`_UpdateSensorBaseline(widgetId, sensorId);    
    }

    return(bslnStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateSensorBaseline
****************************************************************************//**
*
* \brief    
*  Updates the baseline for a sensor in a widget specified by input parameters.
*
* \details  
*  This function performs exactly the same tasks as
*  `$INSTANCE_NAME`_UpdateAllBaselines() and 
*  `$INSTANCE_NAME`_UpdateWidgetBaseline() but only for a specified sensor.
*  
*  This function ignores the value of the wdgtEnable register. Multiple calling 
*  of this function (or any other function with a baseline updating task) 
*  without scanning leads to unexpected behavior.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to `$INSTANCE_NAME`_CheckBaselineDuplication() for details.
*
* \param   widgetId 
*  Specify the ID number of the widget to update the baseline of the sensor 
*  specified by the sensorId argument.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header 
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID. 
*
* \param   sensorId 
*  Specify the ID number of the sensor within the widget to update its baseline.
*  A macro for the sensor ID within a specified widget can be found in the 
*  `$INSTANCE_NAME` Configuration header file defined as 
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID
*
* \return   
*  Returns the status of the specified sensor update baseline operation:
*  - CYRET_SUCCESS if operation was successfully completed
*  - CYRET_BAD_DATA if baseline processing failed
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_UpdateSensorBaseline(uint32 widgetId, uint32 sensorId)
{    
    uint32 result = CYRET_SUCCESS;
    
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];    
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWidgetRam = ptrWidget->ptr2WdgtRam;   

    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    result = `$INSTANCE_NAME`_FtUpdateBaseline(ptrWidgetRam, ptrSensor, (uint32)ptrWidget->wdgtType);
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
        if (CYRET_SUCCESS != result)
        {
            result = CYRET_BAD_DATA;
            `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(widgetId, sensorId);           
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtUpdateBaseline
****************************************************************************//**
*
* \brief
*  Updates the baseline for a sensor specified by an input parameter.
*
* \details
*  Check a matching of present baseline and its inverse duplication. If they 
*  match then updates the baseline for a sensor specified by an input parameter.  
*  If don't match the function return `$INSTANCE_NAME`_TST_BSLN_DUPLICATION
*  result and don't update baseline.
*
* \param    ptrWidgetRam
*  The pointer to the widget RAM structure where all the widget parameters
*  are stored.
*
* \param    ptrSensor
*  The pointer to the sensor RAM structure where all the sensor parameters
*  are stored.
*
* \param    wdType
*  Specifies the type of a widget.
*
* \return   
*  Returns a status indicating whether the baseline has been updated:
*  - CYRET_SUCCESS if baseline updating was successful;
*  - `$INSTANCE_NAME`_PROCESS_BASELINE_FAILED if present sensor's any channel
*    baseline and its inversion doesn't matched
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_FtUpdateBaseline(
                                `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWidgetRam,
                                `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor, 
                                uint32 wdType)
{         
    uint32 sign;
    uint32 difference;        
    uint32 channel;
    uint32 bslnCoeff;
    uint32 result = CYRET_SUCCESS;
    
    #if (`$INSTANCE_NAME`_TOTAL_WIDGETS)  
        uint32 history;
    #endif /* (`$INSTANCE_NAME`_TOTAL_WIDGETS) */    
    
    /* Apply baseline to every channel in sensor */
    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;) 
    {               
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
            if (ptrSensor->bslnInv[channel] != ((uint16) ~(ptrSensor->bsln[channel])))
            {
                result = `$INSTANCE_NAME`_PROCESS_BASELINE_FAILED;
            }
            else
            {
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

        /* Calculate signal value and its sign */
        if(ptrSensor->raw[channel] >= ptrSensor->bsln[channel])
        {
            difference = (uint32)ptrSensor->raw[channel] - (uint32)ptrSensor->bsln[channel];
            sign = 1u;
            ptrSensor->negBslnRstCnt[channel] = 0u;
        }
        else
        {
            difference = (uint32)ptrSensor->bsln[channel] - (uint32)ptrSensor->raw[channel];
            sign = 0u;
        }     
        
        /* Reset baseline if condition is met */ 
        if((sign == 0u) && (difference > (uint32) ptrWidgetRam->nNoiseTh))
        {
            if(ptrSensor->negBslnRstCnt[channel] >= ptrWidgetRam->lowBslnRst)
            {                
                `$INSTANCE_NAME`_FtInitializeBaselineChannel(ptrSensor, wdType, channel);             
            }
            else
            {
                ptrSensor->negBslnRstCnt[channel]++;
            }
        }
        else
        {
            #if (!`$INSTANCE_NAME`_SENSOR_AUTO_RESET_EN)
                /* Update baseline only if signal is in range between noiseThreshold and negativenoiseThreshold */
                if ((difference <= (uint32)ptrWidgetRam->noiseTh) ||
                    ((difference < (uint32) ptrWidgetRam->nNoiseTh) && (sign == 0u)))
                {
            #endif /* (`$INSTANCE_NAME`_CSD_AUTO_RESET == `$INSTANCE_NAME`_CSD_AUTO_RESET_DISABLE) */
            
            #if (`$INSTANCE_NAME`_BASELINE_TYPE == `$INSTANCE_NAME`_IIR_BASELINE)  
                /* Calculate baseline value */
                if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
                {
                    #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) 
                        #if (`$INSTANCE_NAME`_REGULAR_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)                                    
                            history = (uint32) ptrSensor->bsln[channel] << 8u; 
                            history |= ptrSensor->bslnExt[channel];
                        #else
                            history = ptrSensor->bsln[channel];                                     
                        #endif /* (`$INSTANCE_NAME`_REGULAR_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */                            
                    
                        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_WD_BSLN_COEFF_EN)
                            bslnCoeff = ptrWidgetRam->bslnCoeff;
                        #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_WD_BSLN_COEFF_EN) */
                            bslnCoeff = `$INSTANCE_NAME`_REGULAR_IIR_BL_N;
                        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_WD_BSLN_COEFF_EN) */
                        
                        history =  `$INSTANCE_NAME`_FtIIR1stOrder(
                                        (uint32)ptrSensor->raw[channel],
                                        history, bslnCoeff, 
                                        `$INSTANCE_NAME`_REGULAR_IIR_BL_SHIFT);
                                                   
                        #if (`$INSTANCE_NAME`_REGULAR_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)                                    
                            ptrSensor->bsln[channel] = LO16(history >> 8u);
                            ptrSensor->bslnExt[channel] = LO8(history);
                        #else
                            ptrSensor->bsln[channel] = LO16(history);
                        #endif /* (`$INSTANCE_NAME`_REGULAR_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */
                    #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
                }
                else 
                {
                    #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)     
                        #if (`$INSTANCE_NAME`_PROX_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)                                
                            history = (uint32) ptrSensor->bsln[channel] << 8u; 
                            history |= ptrSensor->bslnExt[channel];
                        #else
                            history = (uint32) ptrSensor->bsln[channel];                                    
                        #endif /* (`$INSTANCE_NAME`_PROX_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */ 
                        
                        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_WD_BSLN_COEFF_EN)
                            bslnCoeff = ptrWidgetRam->bslnCoeff;
                        #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_WD_BSLN_COEFF_EN) */
                            bslnCoeff = `$INSTANCE_NAME`_PROX_IIR_BL_N;
                        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_WD_BSLN_COEFF_EN) */
                        
                        history = `$INSTANCE_NAME`_FtIIR1stOrder(
                                        (uint32)ptrSensor->raw[channel], 
                                        history, bslnCoeff,
                                        `$INSTANCE_NAME`_PROX_IIR_BL_SHIFT);
                        
                        #if (`$INSTANCE_NAME`_PROX_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)                                
                            ptrSensor->bsln[channel] = LO16(history >> 8u);
                            ptrSensor->bslnExt[channel] = LO8(history);
                        #else
                            ptrSensor->bsln[channel] = LO16(history);
                        #endif /* (`$INSTANCE_NAME`_PROX_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */        
                    #endif /* (`$INSTANCE_NAME`_PROX_SENSOR_EN)   */
                }
            #else /* (`$INSTANCE_NAME`_CSD_BASELINE_TYPE == `$INSTANCE_NAME`_IIR_BASELINE)  */
                
                /******************************************************************
                * This is the place where the bucket algorithm should be implemented.
                * The bucket method will be implemented in future component version.
                *******************************************************************/
                
            #endif /* (`$INSTANCE_NAME`_CSD_BASELINE_TYPE == `$INSTANCE_NAME`_IIR_BASELINE)  */
                    
            #if (!`$INSTANCE_NAME`_SENSOR_AUTO_RESET_EN)
                }
            #endif /* (!`$INSTANCE_NAME`_SENSOR_AUTO_RESET_EN) */
        }
                
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
            /* Update baseline inversion of every channel in sensor */    
            ptrSensor->bslnInv[channel] = ~(ptrSensor->bsln[channel]);
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

    }
    return result;    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeAllBaselines
****************************************************************************//**
*
* \brief    
*  Initializes (or re-initialize) the baseline of all sensors of all widgets.
*
* \details  
*  Initializes the baseline for all sensors of all widgets. Also, this function
*  can be used to re-initialize baselines. `$INSTANCE_NAME`_Start() calls this 
*  API as part of `$INSTANCE_NAME` operation initialization.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeAllBaselines(void)
{
    uint32 widgetId;    
    
    for(widgetId = `$INSTANCE_NAME`_TOTAL_WIDGETS; widgetId-- > 0u;)
    {
        `$INSTANCE_NAME`_InitializeWidgetBaseline(widgetId); 
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeWidgetBaseline
****************************************************************************//**
*
* \brief    
*  Initializes (or re-initialize) the baseline of all sensors in a widget 
*  specified by input parameter. 
*
* \details  
*  Initializes (or re-initializes) the baseline for all sensors of the 
*  specified widget.
*
* \param  widgetId 
*  Specify the ID number of a widget to initialize the baseline of all sensors
*  in the widget. 
*  A macro for the widget ID can be found in the 
*  `$INSTANCE_NAME` Configuration header file defined as 
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeWidgetBaseline(uint32 widgetId)
{   
    uint32 sensorId;
    uint32 sensorsNumber;
  
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];

    /* Find total amount of sensors in specified widget */   
    sensorsNumber = `$INSTANCE_NAME`_GET_SNS_CNT_BY_PTR(ptrWidget);    
    
    for(sensorId = sensorsNumber; sensorId-- > 0u;)
    {
        `$INSTANCE_NAME`_InitializeSensorBaseline(widgetId, sensorId);   
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeSensorBaseline
****************************************************************************//**
*
* \brief
*  Initializes (or re-initialize) the baseline of a sensor in a widget specified
*  by input parameters.
*
* \details  
*  Initializes (or re-initializes) the baseline for a specified sensor within
*  a specified widget.
*
* \param    widgetId 
*  Specify the ID number of a widget to initialize the baseline of all sensors
*  in the widget.
*  A macro for the widget ID can be found in the 
*  `$INSTANCE_NAME` Configuration header file defined as 
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*  
* \param    sensorId 
*  Specify the ID number of the sensor within the widget to initialize its 
*  baseline.
*  A macro for the sensor ID within a specified widget can be found in the 
*  `$INSTANCE_NAME` Configuration header file defined as 
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeSensorBaseline(uint32 widgetId, uint32 sensorId)
{      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = NULL;
    ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];

    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];

    `$INSTANCE_NAME`_FtInitializeBaseline(ptrSensor, (uint32)ptrWidget->wdgtType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtInitializeBaseline
****************************************************************************//**
*
* \brief    Initializes the baseline history for a sensor indicated by an input
*           parameter.
*
* \details  Initializes the baseline history for a sensor indicated by an input
*           parameter.
*
* \param    *ptrSensor The pointer to the sensor RAM object.
* \param    wdType     Specifies the type of a widget.
*
*******************************************************************************/
CY_INLINE void `$INSTANCE_NAME`_FtInitializeBaseline(`$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor, uint32 wdType) 
{
    uint32 channel;

    /* Apply baseline initialization to every channel in sensor */    
    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;) 
    {
        `$INSTANCE_NAME`_FtInitializeBaselineChannel(ptrSensor, wdType, channel); 
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtInitializeBaselineChannel
****************************************************************************//**
*
* \brief    Initializes the baseline history for a sensor indicated by an input
*           parameter.
*
* \details  Initializes the baseline history for a sensor indicated by an input
*           parameter.
*
* \param    *ptrSensor The pointer to the sensor RAM object.
* \param    wdType     Specifies the type of a widget.
* \param    channel    Specifies the number of the channel to be initialized.
*
*******************************************************************************/
void `$INSTANCE_NAME`_FtInitializeBaselineChannel(`$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor, uint32 wdType, uint32 channel) 
{
    #if (`$INSTANCE_NAME`_BASELINE_TYPE == `$INSTANCE_NAME`_IIR_BASELINE)  
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
                #if (`$INSTANCE_NAME`_REGULAR_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)                    
                    ptrSensor->bslnExt[channel] = 0u;                
                #endif /* (`$INSTANCE_NAME`_REGULAR_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */
            #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
        }
        else
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)     
                #if (`$INSTANCE_NAME`_PROX_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)                   
                    ptrSensor->bslnExt[channel] = 0u;               
                #endif /* (`$INSTANCE_NAME`_PROX_IIR_BL_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */
            #endif /* (`$INSTANCE_NAME`_PROX_SENSOR_EN) */
        }
    #else
        /* `$INSTANCE_NAME`_BASELINE_TYPE == `$INSTANCE_NAME`_BUCKET_BASELINE */        
        ptrSensor->bslnExt[channel] = 0u;        
    #endif /* (`$INSTANCE_NAME`_BASELINE_TYPE == `$INSTANCE_NAME`_IIR_BASELINE) */      
    
    ptrSensor->bsln[channel] = ptrSensor->raw[channel]; 
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
    /* Update baseline inversion of the channel in sensor */    
        ptrSensor->bslnInv[channel] = ~(ptrSensor->bsln[channel]);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

    ptrSensor->negBslnRstCnt[channel] = 0u;
}


#if (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeIIR
****************************************************************************//**
*
* \brief    Initialize the IIR filter history.
*
* \details  Initialize the IIR filter history.
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeIIR(uint32 widgetId, uint32 sensorId)
{   
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj; 
              
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
        
    /* Find pointer to specified filter sensor object */     
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    
    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }    
    
    `$INSTANCE_NAME`_InitializeIIRInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunIIR
****************************************************************************//**
*
* \brief    Executes the IIR filter algorithm on a sensor indicated by an input
*           parameter. 
*
* \details  Executes the IIR filter algorithm on a sensor indicated by an input
*           parameter. 
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunIIR(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj; 
              
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
        
    /* Find pointer to specified filter sensor object */     
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    
    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }    
    
    `$INSTANCE_NAME`_RunIIRInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
}
    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeIIRInternal
****************************************************************************//**
*
* \brief    Initializes the IIR filter history.
*
* \details  Initializes the IIR filter history.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.                                  
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeIIRInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                            `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType)
{
    uint32 channel;

    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN)
                #if (`$INSTANCE_NAME`_REGULAR_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistory = ptrSensorObj->raw[channel];
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistoryLow = 0u;
                #else
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistory = ptrSensorObj->raw[channel] << `$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT;                   
                #endif /* (`$INSTANCE_NAME`_REGULAR_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */
            #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */    
        }
        else
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN)
                #if (`$INSTANCE_NAME`_PROX_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)
                    ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistory = ptrSensorObj->raw[channel];
                    ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistoryLow = 0u;    
                #else
                    ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistory = ptrSensorObj->raw[channel] << `$INSTANCE_NAME`_PROX_IIR_RC_SHIFT;                                   
                #endif /* (`$INSTANCE_NAME`_PROX_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */
            #endif /* (`$INSTANCE_NAME`_PROX_SENSOR_EN) */
        }    
    }    
}
 

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunIIRInternal
****************************************************************************//**
*
* \brief    Run the IIR filter.
*
* \details  Run the IIR filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/    
void `$INSTANCE_NAME`_RunIIRInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj, 
                                     `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType)
{        
    uint32 channel;
    uint32 temp;

    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN)
                #if (`$INSTANCE_NAME`_REGULAR_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)
                    temp = ((uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistory << `$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT);
                    temp |= ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistoryLow;
                    temp = `$INSTANCE_NAME`_FtIIR1stOrder((uint32)ptrSensorObj->raw[channel],
                                                        temp,
                                                        `$INSTANCE_NAME`_REGULAR_IIR_RC_N,
                                                        `$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT);
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistory = LO16(temp >>`$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT);
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistoryLow = LO8(temp);
                    ptrSensorObj->raw[channel] = LO16(temp >>`$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT);
                #else
                    temp =`$INSTANCE_NAME`_FtIIR1stOrder((uint32)ptrSensorObj->raw[channel],
                                                        (uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistory,
                                                        `$INSTANCE_NAME`_REGULAR_IIR_RC_N,
                                                        `$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT);
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].iirHistory = LO16(temp);
                    ptrSensorObj->raw[channel] = LO16(temp >>`$INSTANCE_NAME`_REGULAR_IIR_RC_SHIFT);
                #endif /* (`$INSTANCE_NAME`_REGULAR_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */
            #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */    
        }
        else
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN)
                #if (`$INSTANCE_NAME`_PROX_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE)
                    temp =  ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistory << `$INSTANCE_NAME`_PROX_IIR_RC_SHIFT;
                    temp |= ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistoryLow;
                    temp =`$INSTANCE_NAME`_FtIIR1stOrder((uint32)ptrSensorObj->raw[channel],
                                                        temp,
                                                        `$INSTANCE_NAME`_PROX_IIR_RC_N,
                                                        `$INSTANCE_NAME`_PROX_IIR_RC_SHIFT);
                    ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistory = LO16(temp >>`$INSTANCE_NAME`_PROX_IIR_RC_SHIFT);
                    ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistoryLow = LO8(temp);
                    ptrSensorObj->raw[channel] = LO16(temp >>`$INSTANCE_NAME`_PROX_IIR_RC_SHIFT);
                #else
                    temp =`$INSTANCE_NAME`_FtIIR1stOrder((uint32)ptrSensorObj->raw[channel],
                                                        (uint32)ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistory, 
                                                        `$INSTANCE_NAME`_PROX_IIR_RC_N,
                                                        `$INSTANCE_NAME`_PROX_IIR_RC_SHIFT);
                    ptrFilterHistObj.ptrProx->proxChannel[channel].iirHistory = LO16(temp);
                    ptrSensorObj->raw[channel] = LO16(temp >>`$INSTANCE_NAME`_PROX_IIR_RC_SHIFT);
                #endif /* (`$INSTANCE_NAME`_PROX_IIR_RC_TYPE == `$INSTANCE_NAME`_IIR_FILTER_PERFORMANCE) */
            #endif /* (`$INSTANCE_NAME`_PROX_SENSOR_EN) */
        }    
    }        
}    
#endif /* #if (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN) */


#if (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeMedian
****************************************************************************//**
*
* \brief    Initializes the Median filter history.
*
* \details  Initializes the Median filter history.
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeMedian(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj; 
              
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */     
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    
    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }
    
    `$INSTANCE_NAME`_InitializeMedianInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
}     


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunMedian
****************************************************************************//**
*
* \brief    Executes the Median filter algorithm on a sensor indicated by an input 
*           parameter. 
*
* \details  Executes the Median filter algorithm on a sensor indicated by an input 
*           parameter. 
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunMedian(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj; 
              
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */     
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    
    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }
    
    `$INSTANCE_NAME`_RunMedianInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
}
   

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeMedianInternal
****************************************************************************//**
*
* \brief    Initializes the Median filter.
*
* \details  Initializes the Median filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeMedianInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                               `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType)
{
    uint32 channel;

    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN)
                ptrFilterHistObj.ptrRegular->regularChannel[channel].medHistory[0u] = ptrSensorObj->raw[channel];
                ptrFilterHistObj.ptrRegular->regularChannel[channel].medHistory[1u] = ptrSensorObj->raw[channel];
            #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
        }
        else
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
                ptrFilterHistObj.ptrProx->proxChannel[channel].medHistory[0u] = ptrSensorObj->raw[channel];
                ptrFilterHistObj.ptrProx->proxChannel[channel].medHistory[1u] = ptrSensorObj->raw[channel];
            #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */               
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunMedianInternal
****************************************************************************//**
*
* \brief    Runs the Median filter.
*
* \details  Runs the Median filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunMedianInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                        `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType)
{
    uint32 channel;
    
    #if ((`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN) || \
         (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN))
        uint32 temp;
    #endif
    
    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {    
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {                                             
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN)
                temp = `$INSTANCE_NAME`_FtMedian((uint32)ptrSensorObj->raw[channel],\
                                                 (uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].medHistory[0u],\
                                                 (uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].medHistory[1u]);
                ptrFilterHistObj.ptrRegular->regularChannel[channel].medHistory[1u] = \
                ptrFilterHistObj.ptrRegular->regularChannel[channel].medHistory[0u];
                ptrFilterHistObj.ptrRegular->regularChannel[channel].medHistory[0u] = ptrSensorObj->raw[channel];
                ptrSensorObj->raw[channel] = LO16(temp);
            #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */     
        }
        else 
        {                   
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
                temp = `$INSTANCE_NAME`_FtMedian((uint32)ptrSensorObj->raw[channel],\
                                                 (uint32)ptrFilterHistObj.ptrProx->proxChannel[channel].medHistory[0u],\
                                                 (uint32)ptrFilterHistObj.ptrProx->proxChannel[channel].medHistory[1u]);
                ptrFilterHistObj.ptrProx->proxChannel[channel].medHistory[1u] = \
                ptrFilterHistObj.ptrProx->proxChannel[channel].medHistory[0u];
                ptrFilterHistObj.ptrProx->proxChannel[channel].medHistory[0u] = ptrSensorObj->raw[channel];
                ptrSensorObj->raw[channel] = LO16(temp);
            #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */               
        }
    }
}
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN) */


#if (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeAverage
****************************************************************************//**
*
* \brief    Initializes the average filter history.
*
* \details  Initializes the average filter history.
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeAverage(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj;

    /* Find pointer to specified sensor object */
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;

    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }

    `$INSTANCE_NAME`_InitializeAverageInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunAverage
****************************************************************************//**
*
* \brief    Executes the average filter algorithm on a sensor indicated by an input 
*           parameter. 
*
* \details  Executes the average filter algorithm on a sensor indicated by an input 
*           parameter. 
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunAverage(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj; 
              
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */     
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    
    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }
    
    `$INSTANCE_NAME`_RunAverageInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeAverageInternal
****************************************************************************//**
*
* \brief    Initializes the average filter.
*
* \details  Initializes the average filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeAverageInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,\
                                                  `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType)
{
    uint32 channel;

    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN)
                ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[0] = ptrSensorObj->raw[channel];
                #if (`$INSTANCE_NAME`_REGULAR_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_4)
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[1u] = ptrSensorObj->raw[channel];
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[2u] = ptrSensorObj->raw[channel];
                #endif /* `$INSTANCE_NAME`_REGULAR_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_4 */
            #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */      
        }
        else
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN)
                ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[0] = ptrSensorObj->raw[channel];
                    #if (`$INSTANCE_NAME`_PROX_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_4)
                        ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[1u] = ptrSensorObj->raw[channel];
                        ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[2u] = ptrSensorObj->raw[channel];
                    #endif /* `$INSTANCE_NAME`_REGULAR_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_4 */
            #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunAverageInternal
****************************************************************************//**
*
* \brief    Runs the average filter.
*
* \details  Runs the average filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunAverageInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,\
                                           `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType)
{
    uint32 channel;
    uint32 temp;

    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN)
                #if (`$INSTANCE_NAME`_REGULAR_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_2)
                    temp = ((uint32)ptrSensorObj->raw[channel] + 
                            (uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[0]) >> 1u;
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[0] = ptrSensorObj->raw[channel];
                    ptrSensorObj->raw[channel] = LO16(temp);
                #else
                    temp = ((uint32)ptrSensorObj->raw[channel] + 
                            (uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[0] + 
                            (uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[1u] + 
                            (uint32)ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[2u]) >> 2u;

                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[2u] =
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[1u];
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[1u] =
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[0];
                    ptrFilterHistObj.ptrRegular->regularChannel[channel].avgHistory[0] = ptrSensorObj->raw[channel];
                    ptrSensorObj->raw[channel] = LO16(temp);
                #endif /* `$INSTANCE_NAME`_REGULAR_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_4 */
            #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
        }
        else 
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN)
                #if (`$INSTANCE_NAME`_PROX_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_2)     
                    temp = ((uint32)ptrSensorObj->raw[channel] + 
                            (uint32)ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[0]) >> 1u;
                    ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[0] = ptrSensorObj->raw[channel];
                    ptrSensorObj->raw[channel] = LO16(temp);
                #else
                    temp = ((uint32)ptrSensorObj->raw[channel] + 
                            (uint32)ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[0] +
                            (uint32)ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[1u] +
                            (uint32)ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[2u]) >> 2u;
                    
                    ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[2u] =
                    ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[1u];
                    ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[1u] =
                    ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[0];
                    ptrFilterHistObj.ptrProx->proxChannel[channel].avgHistory[0] = ptrSensorObj->raw[channel];
                    ptrSensorObj->raw[channel] = LO16(temp);
                #endif /* `$INSTANCE_NAME`_PROX_AVERAGE_LEN == `$INSTANCE_NAME`_AVERAGE_FILTER_LEN_4 */
            #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
        }
    }
}
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ALP_FILTER_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeALP
****************************************************************************//**
*
* \brief    Initializes the ALP filter history.
*
* \details  Initializes the ALP filter history.
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeALP(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj;
    
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    ptrFilterHistObj.ptrAlp = &ptrFilterHistObj.ptrAlp[sensorId];
    `$INSTANCE_NAME`_InitializeALPInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunALP
****************************************************************************//**
*
* \brief    Executes the ALP filter algorithm on a sensor indicated by an input 
*           parameter. 
*
* \details  Executes the ALP filter algorithm on a sensor indicated by an input 
*           parameter. 
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunALP(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj; 
    ALP_FLTR_CONFIG_STRUCT alpFilterConfig;
    ALP_FLTR_CONFIG_STRUCT *ptrAlpFilterConfig = &alpFilterConfig;
    CapSense_RAM_WD_BASE_STRUCT *ptrRamWidget = ptrWidget->ptr2WdgtRam;
              
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    ptrAlpFilterConfig->configParam0 = ptrRamWidget->alpOnTh;
    ptrAlpFilterConfig->configParam1 = ptrRamWidget->alpOffTh;
    ptrAlpFilterConfig->configParam2 = ptrRamWidget->fingerTh;
    ptrAlpFilterConfig->configParam3 = ptrRamWidget->noiseTh;
    ptrAlpFilterConfig->configParam4 = ptrRamWidget->hysteresis;

    /* Find pointer to specified filter sensor object */     
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    ptrFilterHistObj.ptrAlp = &ptrFilterHistObj.ptrAlp[sensorId];

    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrAlpFilterConfig->configParam5 = `$INSTANCE_NAME`_REGULAR_RC_ALP_FILTER_COEFF;
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrAlpFilterConfig->configParam5 = `$INSTANCE_NAME`_PROX_RC_ALP_FILTER_COEFF;
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }
    `$INSTANCE_NAME`_RunALPInternal(ptrFilterHistObj, ptrAlpFilterConfig, ptrSensor, (uint32)ptrWidget->wdgtType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeALPInternal
****************************************************************************//**
*
* \brief    Initializes the ALP filter.
*
* \details  Initializes the ALP filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeALPInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                            `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj,
                                            uint32 wdType)
{
    uint32 channel;

    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_ALP_FILTER_EN)
                ALP_Initialize(&ptrFilterHistObj.ptrAlp->channel[channel], &ptrSensorObj->raw[channel]);
            #endif
        }
        else
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_ALP_FILTER_EN)
                ALP_Initialize(&ptrFilterHistObj.ptrAlp->channel[channel], &ptrSensorObj->raw[channel]);
            #endif
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConfigRunALPInternal
****************************************************************************//**
*
* \brief    Prepares ALP configuration structure and runs the filter.
*
* \details  Prepares ALP configuration structure and runs the filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrRamWdgt       The pointer to the RAM widget object.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConfigRunALPInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrRamWdgt,
                                    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj,
                                    uint32 wdType)
{
    ALP_FLTR_CONFIG_STRUCT alpFilterConfig;
    
    alpFilterConfig.configParam0 = ptrRamWdgt->alpOnTh;
    alpFilterConfig.configParam1 = ptrRamWdgt->alpOffTh;
    alpFilterConfig.configParam2 = ptrRamWdgt->fingerTh;
    alpFilterConfig.configParam3 = ptrRamWdgt->noiseTh;
    alpFilterConfig.configParam4 = ptrRamWdgt->hysteresis;
    
    `$INSTANCE_NAME`_RunALPInternal(ptrFilterHistObj, &alpFilterConfig, ptrSensorObj, wdType);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunALPInternal
****************************************************************************//**
*
* \brief    Runs the ALP filter.
*
* \details  Runs the ALP filter.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrAlpFilterConfig The pointer to the filter configuration object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunALPInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj,
                                    ALP_FLTR_CONFIG_STRUCT *ptrAlpFilterConfig,
                                    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj,
                                    uint32 wdType)
{
    uint32 channel;

    for(channel = `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel-- > 0u;)
    {
        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)wdType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
        {
            #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN && `$INSTANCE_NAME`_REGULAR_RC_ALP_FILTER_EN)
                ptrAlpFilterConfig->configParam5 = `$INSTANCE_NAME`_REGULAR_RC_ALP_FILTER_COEFF;
                ALP_Run(&ptrFilterHistObj.ptrAlp->channel[channel], ptrAlpFilterConfig, &ptrSensorObj->raw[channel], &ptrSensorObj->bsln[channel]);
            #endif
        }
        else
        {
            #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN && `$INSTANCE_NAME`_PROX_RC_ALP_FILTER_EN)
                ptrAlpFilterConfig->configParam5 = `$INSTANCE_NAME`_PROX_RC_ALP_FILTER_COEFF;
                ALP_Run(&ptrFilterHistObj.ptrAlp->channel[channel], ptrAlpFilterConfig, &ptrSensorObj->raw[channel], &ptrSensorObj->bsln[channel]);
            #endif
        }
    }
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ALP_FILTER_EN) */
    
#if ((`$INSTANCE_NAME`_REGULAR_RC_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_FILTER_EN))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtRunEnabledFilters
****************************************************************************//**
*
* \brief    Runs all enabled filters.
*
* \details  Runs all enabled filters.
*
* \param    widgetId Specifies the ID number of a widget to update the IIR filter history.*
* \param    sensorId Specifies the ID number of a sensor in the widget to update the IIR 
*           filter history.
*
*******************************************************************************/
void `$INSTANCE_NAME`_FtRunEnabledFilters(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];      
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    `$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj; 
              
    /* Find pointer to specified sensor object */     
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */     
    ptrFilterHistObj.ptr = ptrWidget->ptr2FltrHistory;
    
    if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrWidget->wdgtType != `$INSTANCE_NAME`_WD_PROXIMITY_E)
    {
        #if (`$INSTANCE_NAME`_REGULAR_SENSOR_EN)
            ptrFilterHistObj.ptrRegular = &ptrFilterHistObj.ptrRegular[sensorId];
        #endif /* (`$INSTANCE_NAME`_REGULAR_SENSOR_EN) */
    }
    else
    {
        #if (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN)
            ptrFilterHistObj.ptrProx = &ptrFilterHistObj.ptrProx[sensorId];
        #endif /* (`$INSTANCE_NAME`_PROXIMITY_SENSOR_EN) */
    }
    
    `$INSTANCE_NAME`_FtRunEnabledFiltersInternal(ptrFilterHistObj, ptrSensor, (uint32)ptrWidget->wdgtType);
    
    #if (`$INSTANCE_NAME`_ALP_FILTER_EN)
        `$INSTANCE_NAME`_ConfigRunALPInternal(ptrFilterHistObj, ptrWidget->ptr2WdgtRam, ptrSensor, (uint32)ptrWidget->wdgtType);
    #endif
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtRunEnabledFiltersInternal
****************************************************************************//**
*
* \brief    Runs all enabled filters.
*
* \details  Runs all enabled filters.
*
* \param    ptrFilterHistObj The pointer to the filter RAM object of the sensor.
* \param    ptrSensorObj     The pointer to the sensor RAM object of the sensor.
* \param    wdType           Specifies the type of a widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_FtRunEnabledFiltersInternal(`$INSTANCE_NAME`_PTR_FILTER_VARIANT ptrFilterHistObj, 
                                                  `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType)
{
    #if (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
        `$INSTANCE_NAME`_RunMedianInternal(ptrFilterHistObj, ptrSensorObj, wdType);
    #endif /* (`$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN) */
    
    #if (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN)    
        `$INSTANCE_NAME`_RunIIRInternal(ptrFilterHistObj, ptrSensorObj, wdType);
    #endif /* (`$INSTANCE_NAME`_REGULAR_RC_IIR_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_IIR_FILTER_EN) */ 

    #if (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN)
        `$INSTANCE_NAME`_RunAverageInternal(ptrFilterHistObj, ptrSensorObj, wdType);
    #endif /* (`$INSTANCE_NAME`_REGULAR_RC_AVERAGE_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_AVERAGE_FILTER_EN) */            
}
#endif /* (`$INSTANCE_NAME`_REGULAR_RC_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_FILTER_EN) */


#if (`$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunNoiseEnvelope
****************************************************************************//**
*
* \brief    Executes the noise envelope  filter algorithm on a sensor indicated by 
*           an input parameter to measure the pk-to-pk noise in the sensor raw count.
*
* \details  Executes the noise envelope  filter algorithm on a sensor indicated by 
*           an input parameter to measure the pk-to-pk noise in the sensor raw count.
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RunNoiseEnvelope(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWidgetRam = ptrWidget->ptr2WdgtRam;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT *ptrNoiseEnvelope = NULL;

    /* Find pointer to specified sensor object */
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */
    ptrNoiseEnvelope = ptrWidget->ptr2NoiseEnvlp;
    ptrNoiseEnvelope = &ptrNoiseEnvelope[sensorId];

    SmartSense_RunNoiseEnvelope(ptrSensor->raw[0u], ptrWidgetRam->sigPFC, ptrNoiseEnvelope);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeNoiseEnvelope
****************************************************************************//**
*
* \brief    Initializes the noise-envelope filter
*
* \details  Initializes the noise-envelope filter
*
* \param    widgetId Specifies the ID number of the widget.
* \param    sensorId Specifies the ID number of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeNoiseEnvelope(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWidgetRam = ptrWidget->ptr2WdgtRam;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;    
    SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT *ptrNoiseEnvelope = NULL;

    /* Find pointer to specified sensor object */
    ptrSensor = ptrWidget->ptr2SnsRam;
    ptrSensor = &ptrSensor[sensorId];
    
    /* Find pointer to specified filter sensor object */
    ptrNoiseEnvelope = ptrWidget->ptr2NoiseEnvlp;
    ptrNoiseEnvelope = &ptrNoiseEnvelope[sensorId];    

    SmartSense_InitializeNoiseEnvelope(ptrSensor->raw[0u], ptrWidgetRam->sigPFC, ptrNoiseEnvelope);
}
#endif /* #if `$INSTANCE_NAME`_CSD_AUTOTUNE & `$INSTANCE_NAME`_CSD_SS_TH_EN */


#if (`$INSTANCE_NAME`_POS_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtMedian
****************************************************************************//**
*
* \brief    Return the median value from the three passed arguments.
*
* \details  Return the median value from the three passed arguments.
*
* \param    x1 The first value to be compared.
* \param    x2 The second value to be compared.
* \param    x3 The third value to be compared.
*
* \return   Returns the median value of input arguments.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_FtMedian(uint32 x1, uint32 x2, uint32 x3)
{
    uint32 tmp;

    if (x1 > x2)
    {
        tmp = x2;
        x2 = x1;
        x1 = tmp;
    }

    if (x2 > x3)
    {
        x2 = x3;
    }

    return ((x1 > x2) ? x1 : x2);
}
#endif /*`$INSTANCE_NAME`_POS_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_REGULAR_RC_MEDIAN_FILTER_EN || `$INSTANCE_NAME`_PROX_RC_MEDIAN_FILTER_EN*/


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtIIR1stOrder
****************************************************************************//**
*
* \brief    Return the filtered data by the IIR 1-st order algorithm
*
* \details  Return the filtered data by the IIR 1-st order algorithm
*
* \param    input      The data to be filtered.
* \param    prevOutput The previous filtered data.
* \param    n          The IIR filter coefficient (n/256).
* \param    shift      The parameter is used to shift input data to have free LSB 
*                       bits for a fraction storage of the filter output calculation.
*
* \return   Returns the filtered data.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_FtIIR1stOrder(uint32 input, uint32 prevOutput, uint32 n, uint32 shift)
{   
    uint32 output;
   
    /*
    * n - IIR filter coefficient (n/256)
    * shift - Used to shift input data to have free LSB bits
    * for fraction storage of filter output calculation
    */
    output = ((n * (input << shift)) + ((`$INSTANCE_NAME`_IIR_COEFFICIENT_K - n) * prevOutput)) >> 8u;
    
    /* Shift operation of output will be done in upper level API if needed */
    return output;
}


#if (`$INSTANCE_NAME`_POS_JITTER_FILTER_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FtJitter
****************************************************************************//**
*
* \brief    Returns the filtered data by the jitter algorithm.
*
* \details  Returns the filtered data by the jitter algorithm.
*
* \param    input      The data to be filtered.
* \param    prevOutput The previous filtered data.
*
*
* \return   Returns the filtered data.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_FtJitter(uint32 input, uint32 prevOutput)
{
    if (prevOutput > input)
    {
        input++;
    }
    else if (prevOutput < input)
    {
        input--;
    }
    else
    { 
        /* Nothing to do - MISRA 14.1 requirement*/
    }
    return input;
}
#endif /* `$INSTANCE_NAME`_POS_JITTER_FILTER_EN */


/* [] END OF FILE */
