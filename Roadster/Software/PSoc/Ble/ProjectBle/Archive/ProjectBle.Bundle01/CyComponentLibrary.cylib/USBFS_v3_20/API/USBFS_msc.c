/***************************************************************************//**
* \file `$INSTANCE_NAME`_cdc.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the USB MSC Class request handler and global API for MSC 
*  class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_msc.h"
#include "`$INSTANCE_NAME`_pvt.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS)

/***************************************
*          Internal variables
***************************************/

static uint8 `$INSTANCE_NAME`_lunCount = `$INSTANCE_NAME`_MSC_LUN_NUMBER;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DispatchMSCClassRqst
****************************************************************************//**
*   
*  \internal 
*  This routine dispatches MSC class requests.
*
* \return
*  Status of request processing: handled or not handled.
*
* \globalvars
*  `$INSTANCE_NAME`_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DispatchMSCClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchMSCClassRqst")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;
    
    /* Get request data. */
    uint16 value  = `$INSTANCE_NAME`_GET_UINT16(`$INSTANCE_NAME`_wValueHiReg,  `$INSTANCE_NAME`_wValueLoReg);
    uint16 dataLength = `$INSTANCE_NAME`_GET_UINT16(`$INSTANCE_NAME`_wLengthHiReg, `$INSTANCE_NAME`_wLengthLoReg);
       
    /* Check request direction: D2H or H2D. */
    if (0u != (`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (`$INSTANCE_NAME`_MSC_GET_MAX_LUN == `$INSTANCE_NAME`_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == `$INSTANCE_NAME`_MSC_GET_MAX_LUN_WVALUE) &&
                (dataLength == `$INSTANCE_NAME`_MSC_GET_MAX_LUN_WLENGTH))
            {
                /* Reply to Get Max LUN request: setup control read. */
                `$INSTANCE_NAME`_currentTD.pData = &`$INSTANCE_NAME`_lunCount;
                `$INSTANCE_NAME`_currentTD.count =  `$INSTANCE_NAME`_MSC_GET_MAX_LUN_WLENGTH;
                
                requestHandled  = `$INSTANCE_NAME`_InitControlRead();
            }
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (`$INSTANCE_NAME`_MSC_RESET == `$INSTANCE_NAME`_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == `$INSTANCE_NAME`_MSC_RESET_WVALUE) &&
                (dataLength == `$INSTANCE_NAME`_MSC_RESET_WLENGTH))
            {
                /* Handle to Bulk-Only Reset request: no data control transfer. */
                `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_MSC_RESET_WLENGTH;
                
            #ifdef `$INSTANCE_NAME`_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK
                `$INSTANCE_NAME`_DispatchMSCClass_MSC_RESET_RQST_Callback();
            #endif /* (`$INSTANCE_NAME`_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK) */
                
                requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
            }
        }
    }
    
    return (requestHandled);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MSC_SetLunCount
****************************************************************************//**
*
*  This function sets the number of logical units supported in the application. 
*  The default number of logical units is set in the component customizer.
*
*  \param lunCount: Count of the logical units. Valid range is between 1 and 16.
*
*
* \globalvars
*  `$INSTANCE_NAME`_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_MSC_SetLunCount(uint8 lunCount) `=ReentrantKeil($INSTANCE_NAME . "_MSC_SetLunCount")`
{
    `$INSTANCE_NAME`_lunCount = (lunCount - 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MSC_GetLunCount
****************************************************************************//**
*
*  This function returns the number of logical units.
*
* \return
*   Number of the logical units.
*
* \globalvars
*  `$INSTANCE_NAME`_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_MSC_GetLunCount(void) `=ReentrantKeil($INSTANCE_NAME . "_MSC_GetLunCount")`
{
    return (`$INSTANCE_NAME`_lunCount + 1u);
}   

#endif /* (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS) */


/* [] END OF FILE */
