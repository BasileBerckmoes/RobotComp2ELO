/***************************************************************************//**
* \file `$INSTANCE_NAME`_audio.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the USB AUDIO Class request handler.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_audio.h"
#include "`$INSTANCE_NAME`_pvt.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_CLASS)

/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)

/***************************************
*    AUDIO Variables
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING)
    /** Contains the current audio sample frequency. It is set by the host using a SET_CUR request to the endpoint.*/
    volatile uint8 `$INSTANCE_NAME`_currentSampleFrequency[`$INSTANCE_NAME`_MAX_EP][`$INSTANCE_NAME`_SAMPLE_FREQ_LEN];
    /** Used as a flag for the user code, to inform it that the host has been sent a request 
     * to change the sample frequency. The sample frequency will be sent on the next OUT transaction. 
     * It contains the endpoint address when set. The following code is recommended for 
     * detecting new sample frequency in main code:
     * \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
     *     
     * The USBFS_transferState variable is checked to make sure that the transfer completes. */
    volatile uint8 `$INSTANCE_NAME`_frequencyChanged;
    /** Contains the mute configuration set by the host.*/
    volatile uint8 `$INSTANCE_NAME`_currentMute;
    /** Contains the volume level set by the host.*/
    volatile uint8 `$INSTANCE_NAME`_currentVolume[`$INSTANCE_NAME`_VOLUME_LEN];
    volatile uint8 `$INSTANCE_NAME`_minimumVolume[`$INSTANCE_NAME`_VOLUME_LEN] = {`$INSTANCE_NAME`_VOL_MIN_LSB,
                                                                                  `$INSTANCE_NAME`_VOL_MIN_MSB};
    volatile uint8 `$INSTANCE_NAME`_maximumVolume[`$INSTANCE_NAME`_VOLUME_LEN] = {`$INSTANCE_NAME`_VOL_MAX_LSB,
                                                                                  `$INSTANCE_NAME`_VOL_MAX_MSB};
    volatile uint8 `$INSTANCE_NAME`_resolutionVolume[`$INSTANCE_NAME`_VOLUME_LEN] = {`$INSTANCE_NAME`_VOL_RES_LSB,
                                                                                     `$INSTANCE_NAME`_VOL_RES_MSB};
#endif /*  `$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DispatchAUDIOClassRqst
****************************************************************************//**
*
*  This routine dispatches class requests
*
* \return
*  Results of Audio Class request handling: 
*  - `$INSTANCE_NAME`_TRUE  - request was handled without errors
*  - `$INSTANCE_NAME`_FALSE - error occurs during handling of request     
*
* \globalvars
*   `$INSTANCE_NAME`_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   `$INSTANCE_NAME`_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       
*  \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
*      
*   `$INSTANCE_NAME`_transferState variable is checked to be sure that transfer
*              completes.
*   `$INSTANCE_NAME`_currentMute: Contains mute configuration set by Host.
*   `$INSTANCE_NAME`_currentVolume: Contains volume level set by Host.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DispatchAUDIOClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchAUDIOClassRqst")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;
    
    uint8 RqstRcpt = (uint8)(`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_RCPT_MASK);
#if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING)
    uint8 wValueHi = (uint8) `$INSTANCE_NAME`_wValueHiReg;
    uint8 epNumber = (uint8) `$INSTANCE_NAME`_wIndexLoReg & `$INSTANCE_NAME`_DIR_UNUSED;
#endif /* (`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING) */
    
    /* Check request direction: D2H or H2D. */
    if (0u != (`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (`$INSTANCE_NAME`_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is to endpoint. */
            switch (`$INSTANCE_NAME`_bRequestReg)
            {
                case `$INSTANCE_NAME`_GET_CUR:
                #if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == `$INSTANCE_NAME`_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        `$INSTANCE_NAME`_currentTD.wCount = `$INSTANCE_NAME`_SAMPLE_FREQ_LEN;
                        `$INSTANCE_NAME`_currentTD.pData  = `$INSTANCE_NAME`_currentSampleFrequency[epNumber];
                        
                        requestHandled   = `$INSTANCE_NAME`_InitControlRead();
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK    
                    `$INSTANCE_NAME`_DispatchAUDIOClass_AUDIO_READ_REQUESTS_Callback();
                #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK) */                   
                break;
                
                default:
                    /* Do not handle this request unless callback is defined. */
                    break;
            }
        
        }
        else if (`$INSTANCE_NAME`_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (`$INSTANCE_NAME`_bRequestReg)
            {
                case `$INSTANCE_NAME`_GET_CUR:
                #if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == `$INSTANCE_NAME`_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK
                        `$INSTANCE_NAME`_DispatchAUDIOClass_MUTE_CONTROL_GET_REQUEST_Callback();
                    #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        `$INSTANCE_NAME`_currentTD.wCount = 1u;
                        `$INSTANCE_NAME`_currentTD.pData  = &`$INSTANCE_NAME`_currentMute;
                        
                        requestHandled = `$INSTANCE_NAME`_InitControlRead();
                    }
                    else if (wValueHi == `$INSTANCE_NAME`_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK
                        `$INSTANCE_NAME`_DispatchAUDIOClass_VOLUME_CONTROL_GET_REQUEST_Callback();
                    #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME, */
                        `$INSTANCE_NAME`_currentTD.wCount = `$INSTANCE_NAME`_VOLUME_LEN;
                        `$INSTANCE_NAME`_currentTD.pData  = `$INSTANCE_NAME`_currentVolume;
                        
                        requestHandled = `$INSTANCE_NAME`_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK
                        `$INSTANCE_NAME`_DispatchAUDIOClass_OTHER_GET_CUR_REQUESTS_Callback();
                    #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK) */
                    }
                    break;
                    
                case `$INSTANCE_NAME`_GET_MIN:
                    if (wValueHi == `$INSTANCE_NAME`_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        `$INSTANCE_NAME`_currentTD.wCount = `$INSTANCE_NAME`_VOLUME_LEN;
                        `$INSTANCE_NAME`_currentTD.pData  = &`$INSTANCE_NAME`_minimumVolume[0];
                        
                        requestHandled = `$INSTANCE_NAME`_InitControlRead();
                    }
                    break;
                    
                case `$INSTANCE_NAME`_GET_MAX:
                    if (wValueHi == `$INSTANCE_NAME`_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        `$INSTANCE_NAME`_currentTD.wCount = `$INSTANCE_NAME`_VOLUME_LEN;
                        `$INSTANCE_NAME`_currentTD.pData  = &`$INSTANCE_NAME`_maximumVolume[0];
                        
                        requestHandled = `$INSTANCE_NAME`_InitControlRead();
                    }
                    break;
                    
                case `$INSTANCE_NAME`_GET_RES:
                    if (wValueHi == `$INSTANCE_NAME`_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        `$INSTANCE_NAME`_currentTD.wCount = `$INSTANCE_NAME`_VOLUME_LEN;
                        `$INSTANCE_NAME`_currentTD.pData  = &`$INSTANCE_NAME`_resolutionVolume[0];
                        
                        requestHandled   = `$INSTANCE_NAME`_InitControlRead();
                    }
                    break;
                    
                /* The contents of the status message is reserved for future use.
                * For the time being, a null packet should be returned in the data stage of the
                * control transfer, and the received null packet should be ACKed.
                */
                case `$INSTANCE_NAME`_GET_STAT:
                    `$INSTANCE_NAME`_currentTD.wCount = 0u;    
                    
                    requestHandled = `$INSTANCE_NAME`_InitControlWrite();

                #endif /* (`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK
                    `$INSTANCE_NAME`_DispatchAUDIOClass_AUDIO_WRITE_REQUESTS_Callback();
                #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else
        {   
            /* Do not handle other requests recipients. */
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (`$INSTANCE_NAME`_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is endpoint. */
            switch (`$INSTANCE_NAME`_bRequestReg)
            {
                case `$INSTANCE_NAME`_SET_CUR:
                #if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == `$INSTANCE_NAME`_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        `$INSTANCE_NAME`_currentTD.wCount = `$INSTANCE_NAME`_SAMPLE_FREQ_LEN;
                        `$INSTANCE_NAME`_currentTD.pData  = `$INSTANCE_NAME`_currentSampleFrequency[epNumber];
                        `$INSTANCE_NAME`_frequencyChanged = (uint8) epNumber;
                        
                        requestHandled   = `$INSTANCE_NAME`_InitControlWrite();
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING) */

                    /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                    /* `#END` */

                #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK
                    `$INSTANCE_NAME`_DispatchAUDIOClass_AUDIO_SAMPLING_FREQ_REQUESTS_Callback();
                #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else if(`$INSTANCE_NAME`_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (`$INSTANCE_NAME`_bRequestReg)
            {
                case `$INSTANCE_NAME`_SET_CUR:
                #if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == `$INSTANCE_NAME`_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK
                        `$INSTANCE_NAME`_DispatchAUDIOClass_MUTE_SET_REQUEST_Callback();
                    #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        `$INSTANCE_NAME`_currentTD.wCount = 1u;
                        `$INSTANCE_NAME`_currentTD.pData  = &`$INSTANCE_NAME`_currentMute;
                        
                        requestHandled = `$INSTANCE_NAME`_InitControlWrite();
                    }
                    else if (wValueHi == `$INSTANCE_NAME`_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK
                        `$INSTANCE_NAME`_DispatchAUDIOClass_VOLUME_CONTROL_SET_REQUEST_Callback();
                    #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME */
                        `$INSTANCE_NAME`_currentTD.wCount = `$INSTANCE_NAME`_VOLUME_LEN;
                        `$INSTANCE_NAME`_currentTD.pData  = `$INSTANCE_NAME`_currentVolume;
                        
                        requestHandled = `$INSTANCE_NAME`_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK
                        `$INSTANCE_NAME`_DispatchAUDIOClass_OTHER_SET_CUR_REQUESTS_Callback();
                    #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK) */
                    }
                #endif /*  `$INSTANCE_NAME`_ENABLE_AUDIO_STREAMING */
                
                
                    /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                    /* `#END` */
                    
                #ifdef `$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK
                    `$INSTANCE_NAME`_DispatchAUDIOClass_AUDIO_CONTROL_SEL_REQUESTS_Callback();
                #endif /* (`$INSTANCE_NAME`_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK) */
                break;

                default:
                    /* Do not handle this request. */
                break;
            }
        }
        else
        {
            /* Do not handle other requests recipients. */
        }
    }

    return (requestHandled);
}
#endif /* (USER_SUPPLIED_AUDIO_HANDLER) */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* (`$INSTANCE_NAME`_ENABLE_AUDIO_CLASS) */


/* [] END OF FILE */
