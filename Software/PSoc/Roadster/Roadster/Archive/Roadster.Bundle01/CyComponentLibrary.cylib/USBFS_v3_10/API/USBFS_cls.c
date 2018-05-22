/***************************************************************************//**
* \file `$INSTANCE_NAME`_cls.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the USB Class request handler.
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

#if(`$INSTANCE_NAME`_EXTERN_CLS == `$INSTANCE_NAME`_FALSE)

/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DispatchClassRqst
****************************************************************************//**
*  This routine dispatches class specific requests depend on interface class.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DispatchClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchClassRqst")`
{
    uint8 requestHandled;
    uint8 interfaceNumber;

    /* Get interface to which request is intended. */
    switch (`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_RCPT_MASK)
    {
        case `$INSTANCE_NAME`_RQST_RCPT_IFC:
            /* Class-specific request directed to interface: wIndexLoReg 
            * contains interface number.
            */
            interfaceNumber = (uint8) `$INSTANCE_NAME`_wIndexLoReg;
            break;
        
        case `$INSTANCE_NAME`_RQST_RCPT_EP:
            /* Class-specific request directed to endpoint: wIndexLoReg contains 
            * endpoint number. Find interface related to endpoint, 
            */
            interfaceNumber = `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_wIndexLoReg & `$INSTANCE_NAME`_DIR_UNUSED].interface;
            break;
            
        default:
            /* Default interface is zero. */
            interfaceNumber = 0u;
            break;
    }

#if (defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS) ||\
            defined(`$INSTANCE_NAME`_ENABLE_AUDIO_CLASS) ||\
            defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS) ||\
            `$INSTANCE_NAME`_ENABLE_MSC_CLASS)

    /* Handle class request depends on interface type. */
    switch (`$INSTANCE_NAME`_interfaceClass[interfaceNumber])
    {
    #if defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS)
        case `$INSTANCE_NAME`_CLASS_HID:
            requestHandled = `$INSTANCE_NAME`_DispatchHIDClassRqst();
            break;
    #endif /* (`$INSTANCE_NAME`_ENABLE_HID_CLASS) */
            
    #if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_CLASS)
        case `$INSTANCE_NAME`_CLASS_AUDIO:
            requestHandled = `$INSTANCE_NAME`_DispatchAUDIOClassRqst();
            break;
    #endif /* (`$INSTANCE_NAME`_CLASS_AUDIO) */
            
    #if defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS)
        case `$INSTANCE_NAME`_CLASS_CDC:
            requestHandled = `$INSTANCE_NAME`_DispatchCDCClassRqst();
            break;
    #endif /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS) */
        
    #if (`$INSTANCE_NAME`_ENABLE_MSC_CLASS)
        case `$INSTANCE_NAME`_CLASS_MSD:
        #if (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS)
            /* MSC requests are handled by the component. */
            requestHandled = `$INSTANCE_NAME`_DispatchMSCClassRqst();
        #elif defined(`$INSTANCE_NAME`_DISPATCH_MSC_CLASS_RQST_CALLBACK)
            /* MSC requests are handled by user defined callbcak. */
            requestHandled = `$INSTANCE_NAME`_DispatchMSCClassRqst_Callback();
        #else
            /* MSC requests are not handled. */
            requestHandled = `$INSTANCE_NAME`_FALSE;
        #endif /* (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS) */
            break;
    #endif /* (`$INSTANCE_NAME`_ENABLE_MSC_CLASS) */
        
        default:
            /* Request is not handled: unknown class request type. */
            requestHandled = `$INSTANCE_NAME`_FALSE;
            break;
    }
#else /*No class is defined*/
    if (0u != interfaceNumber)
    {
        /* Suppress warning message */
    }
    requestHandled = `$INSTANCE_NAME`_FALSE;
#endif /*HID or AUDIO or MSC or CDC class enabled*/

    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_DISPATCH_CLASS_RQST_CALLBACK
    if (`$INSTANCE_NAME`_FALSE == requestHandled)
    {
        requestHandled = `$INSTANCE_NAME`_DispatchClassRqst_Callback(interfaceNumber);
    }
#endif /* (`$INSTANCE_NAME`_DISPATCH_CLASS_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* `$INSTANCE_NAME`_EXTERN_CLS */


/* [] END OF FILE */
