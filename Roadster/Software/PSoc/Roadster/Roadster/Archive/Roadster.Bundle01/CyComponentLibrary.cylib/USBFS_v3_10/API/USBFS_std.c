/***************************************************************************//**
* \file `$INSTANCE_NAME`_std.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the USB Standard request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_pvt.h"

/***************************************
*   Static data allocation
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_FWSN_STRING)
    static volatile uint8* `$INSTANCE_NAME`_fwSerialNumberStringDescriptor;
    static volatile uint8  `$INSTANCE_NAME`_snStringConfirm = `$INSTANCE_NAME`_FALSE;
#endif  /* (`$INSTANCE_NAME`_ENABLE_FWSN_STRING) */

#if defined(`$INSTANCE_NAME`_ENABLE_FWSN_STRING)
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_SerialNumString
    ************************************************************************//**
    *
    *  This function is available only when the User Call Back option in the 
    *  Serial Number String descriptor properties is selected. Application 
    *  firmware can provide the source of the USB device serial number string 
    *  descriptor during run time. The default string is used if the application 
    *  firmware does not use this function or sets the wrong string descriptor.
    *
    *  \param snString:  Pointer to the user-defined string descriptor. The 
    *  string descriptor should meet the Universal Serial Bus Specification 
    *  revision 2.0 chapter 9.6.7
    *  Offset|Size|Value|Description
    *  ------|----|------|---------------------------------
    *  0     |1   |N     |Size of this descriptor in bytes
    *  1     |1   |0x03  |STRING Descriptor Type
    *  2     |N-2 |Number|UNICODE encoded string
    *  
    * *For example:* uint8 snString[16]={0x0E,0x03,'F',0,'W',0,'S',0,'N',0,'0',0,'1',0};
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void  `$INSTANCE_NAME`_SerialNumString(uint8 snString[]) `=ReentrantKeil($INSTANCE_NAME . "_SerialNumString")`
    {
        `$INSTANCE_NAME`_snStringConfirm = `$INSTANCE_NAME`_FALSE;
        
        if (snString != NULL)
        {
            /* Check descriptor validation */
            if ((snString[0u] > 1u) && (snString[1u] == `$INSTANCE_NAME`_DESCR_STRING))
            {
                `$INSTANCE_NAME`_fwSerialNumberStringDescriptor = snString;
                `$INSTANCE_NAME`_snStringConfirm = `$INSTANCE_NAME`_TRUE;
            }
        }
    }
#endif  /* `$INSTANCE_NAME`_ENABLE_FWSN_STRING */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleStandardRqst
****************************************************************************//**
*
*  This Routine dispatches standard requests
*
*
* \return
*  TRUE if request handled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_HandleStandardRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleStandardRqst")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;
    `$UINT_TYPE` interfaceNumber;
    `$UINT_TYPE` configurationN;
    `$UINT_TYPE` bmRequestType = `$INSTANCE_NAME`_bmRequestTypeReg;

#if defined(`$INSTANCE_NAME`_ENABLE_STRINGS)
    volatile uint8 *pStr = 0u;
    #if defined(`$INSTANCE_NAME`_ENABLE_DESCRIPTOR_STRINGS)
        uint8 nStr;
        uint8 descrLength;
    #endif /* (`$INSTANCE_NAME`_ENABLE_DESCRIPTOR_STRINGS) */
#endif /* (`$INSTANCE_NAME`_ENABLE_STRINGS) */
    
    static volatile uint8 `$INSTANCE_NAME`_tBuffer[`$INSTANCE_NAME`_STATUS_LENGTH_MAX];
    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;

    `$INSTANCE_NAME`_currentTD.count = 0u;

    if (`$INSTANCE_NAME`_RQST_DIR_D2H == (bmRequestType & `$INSTANCE_NAME`_RQST_DIR_MASK))
    {
        /* Control Read */
        switch (`$INSTANCE_NAME`_bRequestReg)
        {
            case `$INSTANCE_NAME`_GET_DESCRIPTOR:
                if (`$INSTANCE_NAME`_DESCR_DEVICE ==`$INSTANCE_NAME`_wValueHiReg)
                {
                    pTmp = `$INSTANCE_NAME`_GetDeviceTablePtr();
                    `$INSTANCE_NAME`_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                    `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_DEVICE_DESCR_LENGTH;
                    
                    requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                }
                else if (`$INSTANCE_NAME`_DESCR_CONFIG == `$INSTANCE_NAME`_wValueHiReg)
                {
                    pTmp = `$INSTANCE_NAME`_GetConfigTablePtr((uint8) `$INSTANCE_NAME`_wValueLoReg);
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        `$INSTANCE_NAME`_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                        `$INSTANCE_NAME`_currentTD.count = (uint16)((uint16)(`$INSTANCE_NAME`_currentTD.pData)[`$INSTANCE_NAME`_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                                                            (`$INSTANCE_NAME`_currentTD.pData)[`$INSTANCE_NAME`_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                    }
                }
                
            #if(`$INSTANCE_NAME`_BOS_ENABLE)
                else if (`$INSTANCE_NAME`_DESCR_BOS == `$INSTANCE_NAME`_wValueHiReg)
                {
                    pTmp = `$INSTANCE_NAME`_GetBOSPtr();
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        `$INSTANCE_NAME`_currentTD.pData = (volatile uint8 *)pTmp;
                        `$INSTANCE_NAME`_currentTD.count = ((uint16)((uint16)(`$INSTANCE_NAME`_currentTD.pData)[`$INSTANCE_NAME`_BOS_DESCR_TOTAL_LENGTH_HI] << 8u)) | \
                                                                             (`$INSTANCE_NAME`_currentTD.pData)[`$INSTANCE_NAME`_BOS_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                    }
                }
            #endif /*(`$INSTANCE_NAME`_BOS_ENABLE)*/
            
            #if defined(`$INSTANCE_NAME`_ENABLE_STRINGS)
                else if (`$INSTANCE_NAME`_DESCR_STRING == `$INSTANCE_NAME`_wValueHiReg)
                {
                /* Descriptor Strings */
                #if defined(`$INSTANCE_NAME`_ENABLE_DESCRIPTOR_STRINGS)
                    nStr = 0u;
                    pStr = (volatile uint8 *) &`$INSTANCE_NAME`_STRING_DESCRIPTORS[0u];
                    
                    while ((`$INSTANCE_NAME`_wValueLoReg > nStr) && (*pStr != 0u))
                    {
                        /* Read descriptor length from 1st byte */
                        descrLength = *pStr;
                        /* Move to next string descriptor */
                        pStr = &pStr[descrLength];
                        nStr++;
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE_DESCRIPTOR_STRINGS) */
                
                /* Microsoft OS String */
                #if defined(`$INSTANCE_NAME`_ENABLE_MSOS_STRING)
                    if (`$INSTANCE_NAME`_STRING_MSOS == `$INSTANCE_NAME`_wValueLoReg)
                    {
                        pStr = (volatile uint8 *)& `$INSTANCE_NAME`_MSOS_DESCRIPTOR[0u];
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE_MSOS_STRING) */
                
                /* SN string */
                #if defined(`$INSTANCE_NAME`_ENABLE_SN_STRING)
                    if ((`$INSTANCE_NAME`_wValueLoReg != 0u) && 
                        (`$INSTANCE_NAME`_wValueLoReg == `$INSTANCE_NAME`_DEVICE0_DESCR[`$INSTANCE_NAME`_DEVICE_DESCR_SN_SHIFT]))
                    {
                    #if defined(`$INSTANCE_NAME`_ENABLE_IDSN_STRING)
                        /* Read DIE ID and generate string descriptor in RAM */
                        `$INSTANCE_NAME`_ReadDieID(`$INSTANCE_NAME`_idSerialNumberStringDescriptor);
                        pStr = `$INSTANCE_NAME`_idSerialNumberStringDescriptor;
                    #elif defined(`$INSTANCE_NAME`_ENABLE_FWSN_STRING)
                        
                        if(`$INSTANCE_NAME`_snStringConfirm != `$INSTANCE_NAME`_FALSE)
                        {
                            pStr = `$INSTANCE_NAME`_fwSerialNumberStringDescriptor;
                        }
                        else
                        {
                            pStr = (volatile uint8 *)&`$INSTANCE_NAME`_SN_STRING_DESCRIPTOR[0u];
                        }
                    #else
                        pStr = (volatile uint8 *)&`$INSTANCE_NAME`_SN_STRING_DESCRIPTOR[0u];
                    #endif  /* (`$INSTANCE_NAME`_ENABLE_IDSN_STRING) */
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE_SN_STRING) */
                
                    if (*pStr != 0u)
                    {
                        `$INSTANCE_NAME`_currentTD.count = *pStr;
                        `$INSTANCE_NAME`_currentTD.pData = pStr;
                        requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                    }
                }
            #endif /*  `$INSTANCE_NAME`_ENABLE_STRINGS */
                else
                {
                    requestHandled = `$INSTANCE_NAME`_DispatchClassRqst();
                }
                break;
                
            case `$INSTANCE_NAME`_GET_STATUS:
                switch (bmRequestType & `$INSTANCE_NAME`_RQST_RCPT_MASK)
                {
                    case `$INSTANCE_NAME`_RQST_RCPT_EP:
                        `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_EP_STATUS_LENGTH;
                        `$INSTANCE_NAME`_tBuffer[0u]     = `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_wIndexLoReg & `$INSTANCE_NAME`_DIR_UNUSED].hwEpState;
                        `$INSTANCE_NAME`_tBuffer[1u]     = 0u;
                        `$INSTANCE_NAME`_currentTD.pData = &`$INSTANCE_NAME`_tBuffer[0u];
                        
                        requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                        break;
                    case `$INSTANCE_NAME`_RQST_RCPT_DEV:
                        `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_DEVICE_STATUS_LENGTH;
                        `$INSTANCE_NAME`_tBuffer[0u]     = `$INSTANCE_NAME`_deviceStatus;
                        `$INSTANCE_NAME`_tBuffer[1u]     = 0u;
                        `$INSTANCE_NAME`_currentTD.pData = &`$INSTANCE_NAME`_tBuffer[0u];
                        
                        requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case `$INSTANCE_NAME`_GET_CONFIGURATION:
                `$INSTANCE_NAME`_currentTD.count = 1u;
                `$INSTANCE_NAME`_currentTD.pData = (volatile uint8 *) &`$INSTANCE_NAME`_configuration;
                requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                break;
                
            case `$INSTANCE_NAME`_GET_INTERFACE:
                `$INSTANCE_NAME`_currentTD.count = 1u;
                `$INSTANCE_NAME`_currentTD.pData = (volatile uint8 *) &`$INSTANCE_NAME`_interfaceSetting[`$INSTANCE_NAME`_wIndexLoReg];
                requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                break;
                
            default: /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {
        /* Control Write */
        switch (`$INSTANCE_NAME`_bRequestReg)
        {
            case `$INSTANCE_NAME`_SET_ADDRESS:
                /* Store address to be set in `$INSTANCE_NAME`_NoDataControlStatusStage(). */
                `$INSTANCE_NAME`_deviceAddress = (uint8) `$INSTANCE_NAME`_wValueLoReg;
                requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                break;
                
            case `$INSTANCE_NAME`_SET_CONFIGURATION:
                configurationN = `$INSTANCE_NAME`_wValueLoReg;
                
                /* Verify that configuration descriptor exists */
                if(configurationN > 0u)
                {
                    pTmp = `$INSTANCE_NAME`_GetConfigTablePtr((uint8) configurationN - 1u);
                }
                
                /* Responds with a Request Error when configuration number is invalid */
                if (((configurationN > 0u) && (pTmp != NULL)) || (configurationN == 0u))
                {
                    /* Set new configuration if it has been changed */
                    if(configurationN != `$INSTANCE_NAME`_configuration)
                    {
                        `$INSTANCE_NAME`_configuration = (uint8) configurationN;
                        `$INSTANCE_NAME`_configurationChanged = `$INSTANCE_NAME`_TRUE;
                        `$INSTANCE_NAME`_Config(`$INSTANCE_NAME`_TRUE);
                    }
                    requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                }
                break;
                
            case `$INSTANCE_NAME`_SET_INTERFACE:
                if (0u != `$INSTANCE_NAME`_ValidateAlternateSetting())
                {
                    /* Get interface number from the request. */
                    interfaceNumber = `$INSTANCE_NAME`_wIndexLoReg;
                    `$INSTANCE_NAME`_interfaceNumber = (uint8) `$INSTANCE_NAME`_wIndexLoReg;
                     
                    /* Check if alternate settings is changed for interface. */
                    if (`$INSTANCE_NAME`_interfaceSettingLast[interfaceNumber] != `$INSTANCE_NAME`_interfaceSetting[interfaceNumber])
                    {
                        `$INSTANCE_NAME`_configurationChanged = `$INSTANCE_NAME`_TRUE;
                    
                        /* Change alternate setting for the endpoints. */
                    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_MANUAL && `$INSTANCE_NAME`_EP_ALLOC_DYNAMIC)
                        `$INSTANCE_NAME`_Config(`$INSTANCE_NAME`_FALSE);
                    #else
                        `$INSTANCE_NAME`_ConfigAltChanged();
                    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_MANUAL && `$INSTANCE_NAME`_EP_ALLOC_DYNAMIC) */
                    }
                    
                    requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                }
                break;
                
            case `$INSTANCE_NAME`_CLEAR_FEATURE:
                switch (bmRequestType & `$INSTANCE_NAME`_RQST_RCPT_MASK)
                {
                    case `$INSTANCE_NAME`_RQST_RCPT_EP:
                        if (`$INSTANCE_NAME`_wValueLoReg == `$INSTANCE_NAME`_ENDPOINT_HALT)
                        {
                            requestHandled = `$INSTANCE_NAME`_ClearEndpointHalt();
                        }
                        break;
                    case `$INSTANCE_NAME`_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (`$INSTANCE_NAME`_wValueLoReg == `$INSTANCE_NAME`_DEVICE_REMOTE_WAKEUP)
                        {
                            `$INSTANCE_NAME`_deviceStatus &= (uint8)~`$INSTANCE_NAME`_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                        }
                        break;
                    case `$INSTANCE_NAME`_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (`$INSTANCE_NAME`_wIndexLoReg < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER)
                        {
                            `$INSTANCE_NAME`_interfaceStatus[`$INSTANCE_NAME`_wIndexLoReg] &= (uint8) ~`$INSTANCE_NAME`_wValueLoReg;
                            requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case `$INSTANCE_NAME`_SET_FEATURE:
                switch (bmRequestType & `$INSTANCE_NAME`_RQST_RCPT_MASK)
                {
                    case `$INSTANCE_NAME`_RQST_RCPT_EP:
                        if (`$INSTANCE_NAME`_wValueLoReg == `$INSTANCE_NAME`_ENDPOINT_HALT)
                        {
                            requestHandled = `$INSTANCE_NAME`_SetEndpointHalt();
                        }
                        break;
                        
                    case `$INSTANCE_NAME`_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (`$INSTANCE_NAME`_wValueLoReg == `$INSTANCE_NAME`_DEVICE_REMOTE_WAKEUP)
                        {
                            `$INSTANCE_NAME`_deviceStatus |= `$INSTANCE_NAME`_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                        }
                        break;
                        
                    case `$INSTANCE_NAME`_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (`$INSTANCE_NAME`_wIndexLoReg < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER)
                        {
                            `$INSTANCE_NAME`_interfaceStatus[`$INSTANCE_NAME`_wIndexLoReg] &= (uint8) ~`$INSTANCE_NAME`_wValueLoReg;
                            requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                        }
                        break;
                    
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    
    return (requestHandled);
}


#if defined(`$INSTANCE_NAME`_ENABLE_IDSN_STRING)
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadDieID
    ************************************************************************//**
    *
    *  This routine read Die ID and generate Serial Number string descriptor.
    *
    *  \param descr:  pointer on string descriptor. This string size has to be equal or
    *          greater than `$INSTANCE_NAME`_IDSN_DESCR_LENGTH.
    *
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void `$INSTANCE_NAME`_ReadDieID(uint8 descr[]) `=ReentrantKeil($INSTANCE_NAME . "_ReadDieID")`
    {
        const char8 CYCODE hex[] = "0123456789ABCDEF";
        `$UINT_TYPE` i;
        `$UINT_TYPE` j = 0u;
        uint8 uniqueId[8u];

        if (NULL != descr)
        {
            /* Initialize descriptor header. */
            descr[0u] = `$INSTANCE_NAME`_IDSN_DESCR_LENGTH;
            descr[1u] = `$INSTANCE_NAME`_DESCR_STRING;
            
            /* Unique ID size is 8 bytes. */
            CyGetUniqueId((uint32 *) uniqueId);

            /* Fill descriptor with unique device ID. */
            for (i = 2u; i < `$INSTANCE_NAME`_IDSN_DESCR_LENGTH; i += 4u)
            {
                descr[i]      = (uint8) hex[(uniqueId[j] >> 4u)];
                descr[i + 1u] = 0u;
                descr[i + 2u] = (uint8) hex[(uniqueId[j] & 0x0Fu)];
                descr[i + 3u] = 0u;
                ++j;
            }
        }
    }
#endif /* (`$INSTANCE_NAME`_ENABLE_IDSN_STRING) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConfigReg
****************************************************************************//**
*
*  This routine configures hardware registers from the variables.
*  It is called from `$INSTANCE_NAME`_Config() function and from RestoreConfig
*  after Wakeup.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConfigReg(void) `=ReentrantKeil($INSTANCE_NAME . "_ConfigReg")`
{
    `$UINT_TYPE` ep;

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
    uint8 epType = 0u;
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */

    /* Go thought all endpoints and set hardware configuration */
    for (ep = `$INSTANCE_NAME`_EP1; ep < `$INSTANCE_NAME`_MAX_EP; ++ep)
    {
        `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epCfg = `$INSTANCE_NAME`_ARB_EPX_CFG_DEFAULT;
        
    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
        /* Enable arbiter endpoint interrupt sources */
        `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epIntEn = `$INSTANCE_NAME`_ARB_EPX_INT_MASK;
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */
    
        if (`$INSTANCE_NAME`_EP[ep].epMode != `$INSTANCE_NAME`_MODE_DISABLE)
        {
            if (0u != (`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN))
            {
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_MODE_NAK_IN;
                
            #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4)
                /* Clear DMA_TERMIN for IN endpoint. */
                `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epIntEn &= (uint32) ~`$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN;
            #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4) */
            }
            else
            {
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_MODE_NAK_OUT;

            #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
                /* (CY_PSOC4): DMA_TERMIN for OUT endpoint is set above. */
                
                /* Prepare endpoint type mask. */
                epType |= (uint8) (0x01u << (ep - `$INSTANCE_NAME`_EP1));
            #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
            }
        }
        else
        {
            `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_MODE_STALL_DATA_EP;
        }
        
    #if (!`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        #if (CY_PSOC4)
            `$INSTANCE_NAME`_ARB_EP16_BASE.arbEp[ep].rwRa16  = (uint32) `$INSTANCE_NAME`_EP[ep].buffOffset;
            `$INSTANCE_NAME`_ARB_EP16_BASE.arbEp[ep].rwWa16  = (uint32) `$INSTANCE_NAME`_EP[ep].buffOffset;
        #else
            `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].rwRa    = LO8(`$INSTANCE_NAME`_EP[ep].buffOffset);
            `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].rwRaMsb = HI8(`$INSTANCE_NAME`_EP[ep].buffOffset);
            `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].rwWa    = LO8(`$INSTANCE_NAME`_EP[ep].buffOffset);
            `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].rwWaMsb = HI8(`$INSTANCE_NAME`_EP[ep].buffOffset);
        #endif /* (CY_PSOC4) */
    #endif /* (!`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
    }

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
     /* BUF_SIZE depend on DMA_THRESS value:0x55-32 bytes  0x44-16 bytes 0x33-8 bytes 0x22-4 bytes 0x11-2 bytes */
    `$INSTANCE_NAME`_BUF_SIZE_REG = `$INSTANCE_NAME`_DMA_BUF_SIZE;

    /* Configure DMA burst threshold */
#if (CY_PSOC4)
    `$INSTANCE_NAME`_DMA_THRES16_REG   = `$INSTANCE_NAME`_DMA_BYTES_PER_BURST;
#else
    `$INSTANCE_NAME`_DMA_THRES_REG     = `$INSTANCE_NAME`_DMA_BYTES_PER_BURST;
    `$INSTANCE_NAME`_DMA_THRES_MSB_REG = 0u;
#endif /* (CY_PSOC4) */
    `$INSTANCE_NAME`_EP_ACTIVE_REG = `$INSTANCE_NAME`_DEFAULT_ARB_INT_EN;
    `$INSTANCE_NAME`_EP_TYPE_REG   = epType;
    
    /* Cfg_cmp bit set to 1 once configuration is complete. */
    /* Lock arbiter configtuation */
    `$INSTANCE_NAME`_ARB_CFG_REG |= (`$UINT_TYPE`)  `$INSTANCE_NAME`_ARB_CFG_CFG_CMP;
    /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
    `$INSTANCE_NAME`_ARB_CFG_REG &= (`$UINT_TYPE`) ~`$INSTANCE_NAME`_ARB_CFG_CFG_CMP;

#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */

    /* Enable interrupt SIE interurpt source from EP0-EP1 */
    `$INSTANCE_NAME`_SIE_EP_INT_EN_REG = (`$UINT_TYPE`) `$INSTANCE_NAME`_DEFAULT_SIE_EP_INT_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EpStateInit
****************************************************************************//**
*
*  This routine initialize state of Data end points based of its type: 
*   IN  - `$INSTANCE_NAME`_IN_BUFFER_EMPTY (`$INSTANCE_NAME`_EVENT_PENDING)
*   OUT - `$INSTANCE_NAME`_OUT_BUFFER_EMPTY (`$INSTANCE_NAME`_NO_EVENT_PENDING)
*
*******************************************************************************/
void `$INSTANCE_NAME`_EpStateInit(void) `=ReentrantKeil($INSTANCE_NAME . "_EpStateInit")`
{
    uint8 i;

    for (i = `$INSTANCE_NAME`_EP1; i < `$INSTANCE_NAME`_MAX_EP; i++)
    { 
        if (0u != (`$INSTANCE_NAME`_EP[i].addr & `$INSTANCE_NAME`_DIR_IN))
        {
            /* IN Endpoint */
            `$INSTANCE_NAME`_EP[i].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }
        else
        {
            /* OUT Endpoint */
            `$INSTANCE_NAME`_EP[i].apiEpState = `$INSTANCE_NAME`_NO_EVENT_PENDING;
        }
    }
                    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Config
****************************************************************************//**
*
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
*  \param clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* `$INSTANCE_NAME`_interfaceClass - Initialized class array for each interface.
*   It is used for handling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Config(uint8 clearAltSetting) `=ReentrantKeil($INSTANCE_NAME . "_Config")`
{
    uint8 ep;
    uint8 curEp;
    uint8 i;
    uint8 epType;
    const uint8 *pDescr;
    
    #if (!`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        uint16 buffCount = 0u;
    #endif /* (!`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */

    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;
    const T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Clear endpoints settings */
    for (ep = 0u; ep < `$INSTANCE_NAME`_MAX_EP; ++ep)
    {
        `$INSTANCE_NAME`_EP[ep].attrib     = 0u;
        `$INSTANCE_NAME`_EP[ep].hwEpState  = 0u;
        `$INSTANCE_NAME`_EP[ep].epToggle   = 0u;
        `$INSTANCE_NAME`_EP[ep].bufferSize = 0u;
        `$INSTANCE_NAME`_EP[ep].interface  = 0u;
        `$INSTANCE_NAME`_EP[ep].apiEpState = `$INSTANCE_NAME`_NO_EVENT_PENDING;
        `$INSTANCE_NAME`_EP[ep].epMode     = `$INSTANCE_NAME`_MODE_DISABLE;   
    }

    /* Clear Alternate settings for all interfaces. */
    if (0u != clearAltSetting)
    {
        for (i = 0u; i < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER; ++i)
        {
            `$INSTANCE_NAME`_interfaceSetting[i]     = 0u;
            `$INSTANCE_NAME`_interfaceSettingLast[i] = 0u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if (`$INSTANCE_NAME`_configuration > 0u)
    {
        #if defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS)
            uint8 cdcComNums = 0u;
        #endif  /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS) */  

        pTmp = `$INSTANCE_NAME`_GetConfigTablePtr(`$INSTANCE_NAME`_configuration - 1u);
        
        /* Set Power status for current configuration */
        pDescr = (const uint8 *)pTmp->p_list;
        if ((pDescr[`$INSTANCE_NAME`_CONFIG_DESCR_ATTRIB] & `$INSTANCE_NAME`_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            `$INSTANCE_NAME`_deviceStatus |= (uint8)  `$INSTANCE_NAME`_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            `$INSTANCE_NAME`_deviceStatus &= (uint8) ~`$INSTANCE_NAME`_DEVICE_STATUS_SELF_POWERED;
        }
        
        /* Move to next element */
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if (`$INSTANCE_NAME`_EP_MANAGEMENT_MANUAL && `$INSTANCE_NAME`_EP_ALLOC_DYNAMIC)
            /* Configure for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK *) pTmp->p_list;
            
            for (i = 0u; i < ep; i++)
            {     
                /* Compare current Alternate setting with EP Alt */
                if (`$INSTANCE_NAME`_interfaceSetting[pEP->interface] == pEP->altSetting)
                {                                                          
                    curEp  = pEP->addr & `$INSTANCE_NAME`_DIR_UNUSED;
                    epType = pEP->attributes & `$INSTANCE_NAME`_EP_TYPE_MASK;
                    
                    `$INSTANCE_NAME`_EP[curEp].addr       = pEP->addr;
                    `$INSTANCE_NAME`_EP[curEp].attrib     = pEP->attributes;
                    `$INSTANCE_NAME`_EP[curEp].bufferSize = pEP->bufferSize;

                    if (0u != (pEP->addr & `$INSTANCE_NAME`_DIR_IN))
                    {
                        /* IN Endpoint */
                        `$INSTANCE_NAME`_EP[curEp].epMode     = `$INSTANCE_NAME`_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                        `$INSTANCE_NAME`_EP[curEp].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
                    
                    #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE > 0))
                        if ((pEP->bMisc == `$INSTANCE_NAME`_CLASS_AUDIO) && (epType == `$INSTANCE_NAME`_EP_TYPE_BULK))
                        {
                            `$INSTANCE_NAME`_midi_in_ep = curEp;
                        }
                    #endif  /* (`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) */
                    }
                    else
                    {
                        /* OUT Endpoint */
                        `$INSTANCE_NAME`_EP[curEp].epMode     = `$INSTANCE_NAME`_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                        `$INSTANCE_NAME`_EP[curEp].apiEpState = `$INSTANCE_NAME`_NO_EVENT_PENDING;
                        
                    #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && (`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE > 0))
                        if ((pEP->bMisc == `$INSTANCE_NAME`_CLASS_AUDIO) && (epType == `$INSTANCE_NAME`_EP_TYPE_BULK))
                        {
                            `$INSTANCE_NAME`_midi_out_ep = curEp;
                        }
                    #endif  /* (`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) */
                    }

                #if(defined (`$INSTANCE_NAME`_ENABLE_CDC_CLASS))
                    if((pEP->bMisc == `$INSTANCE_NAME`_CLASS_CDC_DATA) ||(pEP->bMisc == `$INSTANCE_NAME`_CLASS_CDC))
                    {
                        cdcComNums = `$INSTANCE_NAME`_Cdc_EpInit(pEP, curEp, cdcComNums);
                    }
                #endif  /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS) */
                }
                
                pEP = &pEP[1u];
            }
            
        #else
            for (i = `$INSTANCE_NAME`_EP1; i < `$INSTANCE_NAME`_MAX_EP; ++i)
            {
                /* p_list points the endpoint setting table. */
                pEP = (const T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
                /* Find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                
                for (curEp = 0u; curEp < ep; ++curEp)
                {
                    if (i == (pEP->addr & `$INSTANCE_NAME`_DIR_UNUSED))
                    {
                        /* Compare endpoint buffers size with current size to find greater. */
                        if (`$INSTANCE_NAME`_EP[i].bufferSize < pEP->bufferSize)
                        {
                            `$INSTANCE_NAME`_EP[i].bufferSize = pEP->bufferSize;
                        }
                        
                        /* Compare current Alternate setting with EP Alt */
                        if (`$INSTANCE_NAME`_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {                            
                            `$INSTANCE_NAME`_EP[i].addr = pEP->addr;
                            `$INSTANCE_NAME`_EP[i].attrib = pEP->attributes;
                            
                            epType = pEP->attributes & `$INSTANCE_NAME`_EP_TYPE_MASK;
                            
                            if (0u != (pEP->addr & `$INSTANCE_NAME`_DIR_IN))
                            {
                                /* IN Endpoint */
                                `$INSTANCE_NAME`_EP[i].epMode     = `$INSTANCE_NAME`_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                                `$INSTANCE_NAME`_EP[i].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
                                
                            #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE > 0))
                                if ((pEP->bMisc == `$INSTANCE_NAME`_CLASS_AUDIO) && (epType == `$INSTANCE_NAME`_EP_TYPE_BULK))
                                {
                                    `$INSTANCE_NAME`_midi_in_ep = i;
                                }
                            #endif  /* (`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) */
                            }
                            else
                            {
                                /* OUT Endpoint */
                                `$INSTANCE_NAME`_EP[i].epMode     = `$INSTANCE_NAME`_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                                `$INSTANCE_NAME`_EP[i].apiEpState = `$INSTANCE_NAME`_NO_EVENT_PENDING;
                                
                            #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && (`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE > 0))
                                if ((pEP->bMisc == `$INSTANCE_NAME`_CLASS_AUDIO) && (epType == `$INSTANCE_NAME`_EP_TYPE_BULK))
                                {
                                    `$INSTANCE_NAME`_midi_out_ep = i;
                                }
                            #endif  /* (`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) */
                            }

                        #if (defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS))
                            if((pEP->bMisc == `$INSTANCE_NAME`_CLASS_CDC_DATA) ||(pEP->bMisc == `$INSTANCE_NAME`_CLASS_CDC))
                            {
                                cdcComNums = `$INSTANCE_NAME`_Cdc_EpInit(pEP, i, cdcComNums);
                            }
                        #endif  /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS) */

                            #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
                                break;  /* Use first EP setting in Auto memory management */
                            #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
                        }
                    }
                    
                    pEP = &pEP[1u];
                }
            }
        #endif /*  (`$INSTANCE_NAME`_EP_MANAGEMENT_MANUAL && `$INSTANCE_NAME`_EP_ALLOC_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for handling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (const T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /* Configure interface number for each EP */
            `$INSTANCE_NAME`_EP[pEP->addr & `$INSTANCE_NAME`_DIR_UNUSED].interface = pEP->interface;
            pEP = &pEP[1u];
        }
        
        /* Init pointer on interface class table */
        `$INSTANCE_NAME`_interfaceClass = `$INSTANCE_NAME`_GetInterfaceClassTablePtr();
        
    /* Set the endpoint buffer addresses */
    #if (!`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        buffCount = 0u;
        for (ep = `$INSTANCE_NAME`_EP1; ep < `$INSTANCE_NAME`_MAX_EP; ++ep)
        {
            `$INSTANCE_NAME`_EP[ep].buffOffset = buffCount;        
            buffCount += `$INSTANCE_NAME`_EP[ep].bufferSize;
            
        #if (`$INSTANCE_NAME`_GEN_16BITS_EP_ACCESS)
            /* Align EP buffers to be event size to access 16-bits DR register. */
            buffCount += (0u != (buffCount & 0x01u)) ? 1u : 0u;
        #endif /* (`$INSTANCE_NAME`_GEN_16BITS_EP_ACCESS) */            
        }
    #endif /* (!`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */

        /* Configure hardware registers */
        `$INSTANCE_NAME`_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConfigAltChanged
****************************************************************************//**
*
*  This routine update configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConfigAltChanged(void) `=ReentrantKeil($INSTANCE_NAME . "_ConfigAltChanged")`
{
    `$UINT_TYPE` ep;
    `$UINT_TYPE` curEp;
    `$UINT_TYPE` epType;
    `$UINT_TYPE` i;
    uint8 interfaceNum;

    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;
    const T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Init Endpoints and Device Status if configured */
    if (`$INSTANCE_NAME`_configuration > 0u)
    {
        /* Get number of endpoints configurations (ep). */
        pTmp = `$INSTANCE_NAME`_GetConfigTablePtr(`$INSTANCE_NAME`_configuration - 1u);
        pTmp = &pTmp[1u];
        ep = pTmp->c;

        /* Get pointer to endpoints setting table (pEP). */
        pEP = (const T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        
        /* Look through all possible endpoint configurations. Find endpoints 
        * which belong to current interface and alternate settings for 
        * re-configuration.
        */
        interfaceNum = `$INSTANCE_NAME`_interfaceNumber;
        for (i = 0u; i < ep; i++)
        {
            /* Find endpoints which belong to current interface and alternate settings. */
            if ((interfaceNum == pEP->interface) && 
                (`$INSTANCE_NAME`_interfaceSetting[interfaceNum] == pEP->altSetting))
            {
                curEp  = ((`$UINT_TYPE`) pEP->addr & `$INSTANCE_NAME`_DIR_UNUSED);
                epType = ((`$UINT_TYPE`) pEP->attributes & `$INSTANCE_NAME`_EP_TYPE_MASK);
                
                /* Change the SIE mode for the selected EP to NAK ALL */
                `$INSTANCE_NAME`_EP[curEp].epToggle   = 0u;
                `$INSTANCE_NAME`_EP[curEp].addr       = pEP->addr;
                `$INSTANCE_NAME`_EP[curEp].attrib     = pEP->attributes;
                `$INSTANCE_NAME`_EP[curEp].bufferSize = pEP->bufferSize;

                if (0u != (pEP->addr & `$INSTANCE_NAME`_DIR_IN))
                {
                    /* IN Endpoint */
                    `$INSTANCE_NAME`_EP[curEp].epMode     = `$INSTANCE_NAME`_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                    `$INSTANCE_NAME`_EP[curEp].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
                }
                else
                {
                    /* OUT Endpoint */
                    `$INSTANCE_NAME`_EP[curEp].epMode     = `$INSTANCE_NAME`_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                    `$INSTANCE_NAME`_EP[curEp].apiEpState = `$INSTANCE_NAME`_NO_EVENT_PENDING;
                }
                
                /* Make SIE to NAK any endpoint requests */
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[curEp].epCr0 = `$INSTANCE_NAME`_MODE_NAK_IN_OUT;

            #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
                /* Clear IN data ready. */
                `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[curEp].epCfg &= (`$UINT_TYPE`) ~`$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY;

                /* Select endpoint number of reconfiguration */
                `$INSTANCE_NAME`_DYN_RECONFIG_REG = (`$UINT_TYPE`) ((curEp - 1u) << `$INSTANCE_NAME`_DYN_RECONFIG_EP_SHIFT);
                
                /* Request for dynamic re-configuration of endpoint. */
                `$INSTANCE_NAME`_DYN_RECONFIG_REG |= `$INSTANCE_NAME`_DYN_RECONFIG_ENABLE;
                
                /* Wait until block is ready for re-configuration */
                while (0u == (`$INSTANCE_NAME`_DYN_RECONFIG_REG & `$INSTANCE_NAME`_DYN_RECONFIG_RDY_STS))
                {
                }
                
                /* Once DYN_RECONFIG_RDY_STS bit is set, FW can change the EP configuration. */
                /* Change EP Type with new direction */
                if (0u != (pEP->addr & `$INSTANCE_NAME`_DIR_IN))
                {
                    /* Set endpoint type: 0 - IN and 1 - OUT. */
                    `$INSTANCE_NAME`_EP_TYPE_REG &= (`$UINT_TYPE`) ~(`$UINT_TYPE`)((`$UINT_TYPE`) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Clear DMA_TERMIN for IN endpoint */
                    `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[curEp].epIntEn &= (uint32) ~`$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                else
                {
                    /* Set endpoint type: 0 - IN and 1- OUT. */
                    `$INSTANCE_NAME`_EP_TYPE_REG |= (`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Set DMA_TERMIN for OUT endpoint */
                    `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[curEp].epIntEn |= (uint32) `$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                
                /* Complete dynamic re-configuration: all endpoint related status and signals 
                * are set into the default state.
                */
                `$INSTANCE_NAME`_DYN_RECONFIG_REG &= (`$UINT_TYPE`) ~`$INSTANCE_NAME`_DYN_RECONFIG_ENABLE;

            #else
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[curEp].epCnt0 = HI8(`$INSTANCE_NAME`_EP[curEp].bufferSize);
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[curEp].epCnt1 = LO8(`$INSTANCE_NAME`_EP[curEp].bufferSize);
                
                #if (CY_PSOC4)
                    `$INSTANCE_NAME`_ARB_EP16_BASE.arbEp[curEp].rwRa16  = (uint32) `$INSTANCE_NAME`_EP[curEp].buffOffset;
                    `$INSTANCE_NAME`_ARB_EP16_BASE.arbEp[curEp].rwWa16  = (uint32) `$INSTANCE_NAME`_EP[curEp].buffOffset;
                #else
                    `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[curEp].rwRa    = LO8(`$INSTANCE_NAME`_EP[curEp].buffOffset);
                    `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[curEp].rwRaMsb = HI8(`$INSTANCE_NAME`_EP[curEp].buffOffset);
                    `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[curEp].rwWa    = LO8(`$INSTANCE_NAME`_EP[curEp].buffOffset);
                    `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[curEp].rwWaMsb = HI8(`$INSTANCE_NAME`_EP[curEp].buffOffset);
                #endif /* (CY_PSOC4) */                
            #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
            }
            
            pEP = &pEP[1u]; /* Get next EP element */
        }
        
        /* The main loop has to re-enable DMA and OUT endpoint */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetConfigTablePtr
****************************************************************************//**
*
*  This routine returns a pointer a configuration table entry
*
*  \param confIndex:  Configuration Index
*
* \return
*  Device Descriptor pointer or NULL when descriptor does not exist.
*
*******************************************************************************/
const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetConfigTablePtr(uint8 confIndex)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_GetConfigTablePtr")`
{
    /* Device Table */
    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;

    pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) `$INSTANCE_NAME`_TABLE[`$INSTANCE_NAME`_device].p_list;

    /* The first entry points to the Device Descriptor,
    *  the second entry point to the BOS Descriptor
    *  the rest configuration entries.
    *  Set pointer to the first Configuration Descriptor
    */
    pTmp = &pTmp[2u];
    /* For this table, c is the number of configuration descriptors  */
    if(confIndex >= pTmp->c)   /* Verify that required configuration descriptor exists */
    {
        pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) NULL;
    }
    else
    {
        pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp[confIndex].p_list;
    }

    return (pTmp);
}


#if (`$INSTANCE_NAME`_BOS_ENABLE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetBOSPtr
    ****************************************************************************//**
    *
    *  This routine returns a pointer a BOS table entry
    *
    *  
    *
    * \return
    *  BOS Descriptor pointer or NULL when descriptor does not exist.
    *
    *******************************************************************************/
    const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetBOSPtr(void)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetBOSPtr")`
    {
        /* Device Table */
        const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;

        pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) `$INSTANCE_NAME`_TABLE[`$INSTANCE_NAME`_device].p_list;

        /* The first entry points to the Device Descriptor,
        *  the second entry points to the BOS Descriptor
        */
        pTmp = &pTmp[1u];
        pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp->p_list;
        return (pTmp);
    }
#endif /* (`$INSTANCE_NAME`_BOS_ENABLE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDeviceTablePtr
****************************************************************************//**
*
*  This routine returns a pointer to the Device table
*
* \return
*  Device Table pointer
*
*******************************************************************************/
const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetDeviceTablePtr(void)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetDeviceTablePtr")`
{
    /* Device Table */
    return( (const T_`$INSTANCE_NAME`_LUT CYCODE *) `$INSTANCE_NAME`_TABLE[`$INSTANCE_NAME`_device].p_list );
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
****************************************************************************//**
*
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* \return
*  Interface Class table pointer.
*
*******************************************************************************/
const uint8 CYCODE *`$INSTANCE_NAME`_GetInterfaceClassTablePtr(void)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_GetInterfaceClassTablePtr")`
{
    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;
    const uint8 CYCODE *pInterfaceClass;
    uint8 currentInterfacesNum;

    pTmp = `$INSTANCE_NAME`_GetConfigTablePtr(`$INSTANCE_NAME`_configuration - 1u);
    if (pTmp != NULL)
    {
        currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[`$INSTANCE_NAME`_CONFIG_DESCR_NUM_INTERFACES];
        /* Third entry in the LUT starts the Interface Table pointers */
        /* The INTERFACE_CLASS table is located after all interfaces */
        pTmp = &pTmp[currentInterfacesNum + 2u];
        pInterfaceClass = (const uint8 CYCODE *) pTmp->p_list;
    }
    else
    {
        pInterfaceClass = (const uint8 CYCODE *) NULL;
    }

    return (pInterfaceClass);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TerminateEP
****************************************************************************//**
*
*  This function terminates the specified USBFS endpoint.
*  This function should be used before endpoint reconfiguration.
*
*  \param ep Contains the data endpoint number.
*
*  \reentrant
*  No.
*
* \sideeffect
* 
* The device responds with a NAK for any transactions on the selected endpoint.
*   
*******************************************************************************/
void `$INSTANCE_NAME`_TerminateEP(uint8 epNumber) `=ReentrantKeil($INSTANCE_NAME . "_TerminateEP")`
{
    /* Get endpoint number */
    epNumber &= `$INSTANCE_NAME`_DIR_UNUSED;

    if ((epNumber > `$INSTANCE_NAME`_EP0) && (epNumber < `$INSTANCE_NAME`_MAX_EP))
    {
        /* Set the endpoint Halt */
        `$INSTANCE_NAME`_EP[epNumber].hwEpState |= `$INSTANCE_NAME`_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        `$INSTANCE_NAME`_EP[epNumber].epToggle = 0u;
        `$INSTANCE_NAME`_EP[epNumber].apiEpState = `$INSTANCE_NAME`_NO_EVENT_ALLOWED;

        if ((`$INSTANCE_NAME`_EP[epNumber].addr & `$INSTANCE_NAME`_DIR_IN) != 0u)
        {   
            /* IN Endpoint */
            `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[epNumber].epCr0 = `$INSTANCE_NAME`_MODE_NAK_IN;
        }
        else
        {
            /* OUT Endpoint */
            `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[epNumber].epCr0 = `$INSTANCE_NAME`_MODE_NAK_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetEndpointHalt
****************************************************************************//**
*
*  This routine handles set endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetEndpointHalt(void) `=ReentrantKeil($INSTANCE_NAME . "_SetEndpointHalt")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;
    `$UINT_TYPE` ep;
    
    /* Set endpoint halt */
    ep = `$INSTANCE_NAME`_wIndexLoReg & `$INSTANCE_NAME`_DIR_UNUSED;

    if ((ep > `$INSTANCE_NAME`_EP0) && (ep < `$INSTANCE_NAME`_MAX_EP))
    {
        /* Set the endpoint Halt */
        `$INSTANCE_NAME`_EP[ep].hwEpState |= (`$INSTANCE_NAME`_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        `$INSTANCE_NAME`_EP[ep].epToggle = 0u;
        `$INSTANCE_NAME`_EP[ep].apiEpState |= `$INSTANCE_NAME`_NO_EVENT_ALLOWED;

        if ((`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = (`$INSTANCE_NAME`_MODE_STALL_DATA_EP | 
                                                            `$INSTANCE_NAME`_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = (`$INSTANCE_NAME`_MODE_STALL_DATA_EP | 
                                                            `$INSTANCE_NAME`_MODE_ACK_OUT);
        }
        requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearEndpointHalt
****************************************************************************//**
*
*  This routine handles clear endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ClearEndpointHalt(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearEndpointHalt")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;
    `$UINT_TYPE` ep;

    /* Clear endpoint halt */
    ep = `$INSTANCE_NAME`_wIndexLoReg & `$INSTANCE_NAME`_DIR_UNUSED;

    if ((ep > `$INSTANCE_NAME`_EP0) && (ep < `$INSTANCE_NAME`_MAX_EP))
    {
        /* Clear the endpoint Halt */
        `$INSTANCE_NAME`_EP[ep].hwEpState &= (uint8) ~`$INSTANCE_NAME`_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        `$INSTANCE_NAME`_EP[ep].epToggle = 0u;
        
        /* Clear toggle bit for already armed packet */
        `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCnt0 = (`$UINT_TYPE`) ~(`$UINT_TYPE`)`$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        
        /* Return API State as it was defined before */
        `$INSTANCE_NAME`_EP[ep].apiEpState &= (uint8) ~`$INSTANCE_NAME`_NO_EVENT_ALLOWED;

        if ((`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            if(`$INSTANCE_NAME`_EP[ep].apiEpState == `$INSTANCE_NAME`_IN_BUFFER_EMPTY)
            {       
                /* Wait for next packet from application */
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_MODE_NAK_IN;
            }
            else    /* Continue armed transfer */
            {
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_MODE_ACK_IN;
            }
        }
        else
        {
            /* OUT Endpoint */
            if (`$INSTANCE_NAME`_EP[ep].apiEpState == `$INSTANCE_NAME`_OUT_BUFFER_FULL)
            {       
                /* Allow application to read full buffer */
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_MODE_NAK_OUT;
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_MODE_ACK_OUT;
            }
        }
        
        requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ValidateAlternateSetting
****************************************************************************//**
*
*  Validates (and records) a SET INTERFACE request.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ValidateAlternateSetting(void) `=ReentrantKeil($INSTANCE_NAME . "_ValidateAlternateSetting")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;
    
    uint8 interfaceNum;
    uint8 curInterfacesNum;
    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;
    
    /* Get interface number from the request. */
    interfaceNum = (uint8) `$INSTANCE_NAME`_wIndexLoReg;
    
    /* Get number of interfaces for current configuration. */
    pTmp = `$INSTANCE_NAME`_GetConfigTablePtr(`$INSTANCE_NAME`_configuration - 1u);
    curInterfacesNum  = ((const uint8 *) pTmp->p_list)[`$INSTANCE_NAME`_CONFIG_DESCR_NUM_INTERFACES];

    /* Validate that interface number is within range. */
    if ((interfaceNum <= curInterfacesNum) || (interfaceNum <= `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER))
    {
        /* Save current and new alternate settings (come with request) to make 
        * desicion about following endpoint re-configuration.
        */
        `$INSTANCE_NAME`_interfaceSettingLast[interfaceNum] = `$INSTANCE_NAME`_interfaceSetting[interfaceNum];
        `$INSTANCE_NAME`_interfaceSetting[interfaceNum]     = (uint8) `$INSTANCE_NAME`_wValueLoReg;
        
        requestHandled = `$INSTANCE_NAME`_TRUE;
    }

    return (requestHandled);
}


/* [] END OF FILE */
