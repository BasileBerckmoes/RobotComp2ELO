/***************************************************************************//**
* \file `$INSTANCE_NAME`_vnd.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the  USB vendor request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_pvt.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if(`$INSTANCE_NAME`_EXTERN_VND == `$INSTANCE_NAME`_FALSE)

/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleVendorRqst
****************************************************************************//**
*
*  This routine provide users with a method to implement vendor specific
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_HandleVendorRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleVendorRqst")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;

    /* Check request direction: D2H or H2D. */
    if (0u != (`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        switch (`$INSTANCE_NAME`_bRequestReg)
        {
            case `$INSTANCE_NAME`_GET_EXTENDED_CONFIG_DESCRIPTOR:
            #if defined(`$INSTANCE_NAME`_ENABLE_MSOS_STRING)
                `$INSTANCE_NAME`_currentTD.pData = (volatile uint8 *) &`$INSTANCE_NAME`_MSOS_CONFIGURATION_DESCR[0u];
                `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_MSOS_CONFIGURATION_DESCR[0u];
                requestHandled  = `$INSTANCE_NAME`_InitControlRead();
            #endif /* (`$INSTANCE_NAME`_ENABLE_MSOS_STRING) */
                break;
            
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_HANDLE_VENDOR_RQST_CALLBACK
    if (`$INSTANCE_NAME`_FALSE == requestHandled)
    {
        requestHandled = `$INSTANCE_NAME`_HandleVendorRqst_Callback();
    }
#endif /* (`$INSTANCE_NAME`_HANDLE_VENDOR_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */


#endif /* `$INSTANCE_NAME`_EXTERN_VND */


/* [] END OF FILE */
