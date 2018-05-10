/***************************************************************************//**
* \file `$INSTANCE_NAME`_hid.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the USB HID Class request handler. 
*
* Related Document:
*  Device Class Definition for Human Interface Devices (HID) Version 1.11
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_hid.h"
#include "`$INSTANCE_NAME`_pvt.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


#if defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS)

/***************************************
*    HID Variables
***************************************/
/** This variable is initialized in the USBFS_InitComponent() API to the 
 * PROTOCOL_REPORT value. It is controlled by the host using the 
 * HID_SET_PROTOCOL request. The value is returned to the user code by the 
 * USBFS_GetProtocol() API.*/
volatile uint8 `$INSTANCE_NAME`_hidProtocol[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];

/** This variable controls the HID report rate. It is controlled by the host 
 * using the HID_SET_IDLE request and used by the USBFS_UpdateHIDTimer() API to 
 * reload timer.*/
volatile uint8 `$INSTANCE_NAME`_hidIdleRate[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];

/** This variable contains the timer counter, which is decremented and reloaded 
 * by the USBFS_UpdateHIDTimer() API.*/
volatile uint8 `$INSTANCE_NAME`_hidIdleTimer[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER]; /* HID device idle rate value */


/***************************************
* Custom Declarations
***************************************/

/* `#START HID_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateHIDTimer
****************************************************************************//**
*
*  This function updates the HID Report idle timer and returns the status and 
*  reloads the timer if it expires.
*
*  \param interface Contains the interface number.
*
* \return
*  Returns the state of the HID timer. Symbolic names and their associated values are given here:
*  Return Value               |Notes
*  ---------------------------|------------------------------------------------
*  USBFS_IDLE_TIMER_EXPIRED   | The timer expired.
*  USBFS_IDLE_TIMER_RUNNING   | The timer is running.
*  USBFS_IDLE_TIMER_IDEFINITE | The report is sent when data or state changes.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_UpdateHIDTimer(uint8 interface) `=ReentrantKeil($INSTANCE_NAME . "_UpdateHIDTimer")`
{
    uint8 stat = `$INSTANCE_NAME`_IDLE_TIMER_INDEFINITE;

    if(`$INSTANCE_NAME`_hidIdleRate[interface] != 0u)
    {
        if(`$INSTANCE_NAME`_hidIdleTimer[interface] > 0u)
        {
            `$INSTANCE_NAME`_hidIdleTimer[interface]--;
            stat = `$INSTANCE_NAME`_IDLE_TIMER_RUNNING;
        }
        else
        {
            `$INSTANCE_NAME`_hidIdleTimer[interface] = `$INSTANCE_NAME`_hidIdleRate[interface];
            stat = `$INSTANCE_NAME`_IDLE_TIMER_EXPIRED;
        }
    }

    return((uint8)stat);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetProtocol
****************************************************************************//**
*
*  This function returns the HID protocol value for the selected interface.
*
*  \param interface:  Contains the interface number.
*
*  \return
*  Returns the protocol value. 
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetProtocol(uint8 interface) `=ReentrantKeil($INSTANCE_NAME . "_GetProtocol")`
{
    return(`$INSTANCE_NAME`_hidProtocol[interface]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DispatchHIDClassRqst
****************************************************************************//**
*
*  This routine dispatches class requests
*
* \return
*  Results of HID Class request handling: 
*  - `$INSTANCE_NAME`_TRUE  - request was handled without errors
*  - `$INSTANCE_NAME`_FALSE - error occurs during handling of request  
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DispatchHIDClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchHIDClassRqst")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;

    uint8 interfaceNumber = (uint8) `$INSTANCE_NAME`_wIndexLoReg;
    
    /* Check request direction: D2H or H2D. */
    if (0u != (`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        switch (`$INSTANCE_NAME`_bRequestReg)
        {
            case `$INSTANCE_NAME`_GET_DESCRIPTOR:
                if (`$INSTANCE_NAME`_wValueHiReg == `$INSTANCE_NAME`_DESCR_HID_CLASS)
                {
                    `$INSTANCE_NAME`_FindHidClassDecriptor();
                    if (`$INSTANCE_NAME`_currentTD.count != 0u)
                    {
                        requestHandled = `$INSTANCE_NAME`_InitControlRead();
                    }
                }
                else if (`$INSTANCE_NAME`_wValueHiReg == `$INSTANCE_NAME`_DESCR_HID_REPORT)
                {
                    `$INSTANCE_NAME`_FindReportDescriptor();
                    if (`$INSTANCE_NAME`_currentTD.count != 0u)
                    {
                        requestHandled = `$INSTANCE_NAME`_InitControlRead();
                    }
                }
                else
                {   
                    /* Do not handle this request. */
                }
                break;
                
            case `$INSTANCE_NAME`_HID_GET_REPORT:
                `$INSTANCE_NAME`_FindReport();
                if (`$INSTANCE_NAME`_currentTD.count != 0u)
                {
                    requestHandled = `$INSTANCE_NAME`_InitControlRead();
                }
                break;

            case `$INSTANCE_NAME`_HID_GET_IDLE:
                /* This function does not support multiple reports per interface*/
                /* Validate interfaceNumber and Report ID (should be 0): Do not support Idle per Report ID */
                if ((interfaceNumber < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER) && (`$INSTANCE_NAME`_wValueLoReg == 0u)) 
                {
                    `$INSTANCE_NAME`_currentTD.count = 1u;
                    `$INSTANCE_NAME`_currentTD.pData = &`$INSTANCE_NAME`_hidIdleRate[interfaceNumber];
                    requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                }
                break;
                
            case `$INSTANCE_NAME`_HID_GET_PROTOCOL:
                /* Validate interfaceNumber */
                if( interfaceNumber < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER)
                {
                    `$INSTANCE_NAME`_currentTD.count = 1u;
                    `$INSTANCE_NAME`_currentTD.pData = &`$INSTANCE_NAME`_hidProtocol[interfaceNumber];
                    requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   
        /* Handle direction from host to device. */
        
        switch (`$INSTANCE_NAME`_bRequestReg)
        {
            case `$INSTANCE_NAME`_HID_SET_REPORT:
                `$INSTANCE_NAME`_FindReport();
                if (`$INSTANCE_NAME`_currentTD.count != 0u)
                {
                    requestHandled = `$INSTANCE_NAME`_InitControlWrite();
                }
                break;
                
            case `$INSTANCE_NAME`_HID_SET_IDLE:
                /* This function does not support multiple reports per interface */
                /* Validate interfaceNumber and Report ID (should be 0): Do not support Idle per Report ID */
                if ((interfaceNumber < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER) && (`$INSTANCE_NAME`_wValueLoReg == 0u))
                {
                    `$INSTANCE_NAME`_hidIdleRate[interfaceNumber] = (uint8)`$INSTANCE_NAME`_wValueHiReg;
                    /* With regards to HID spec: "7.2.4 Set_Idle Request"
                    *  Latency. If the current period has gone past the
                    *  newly proscribed time duration, then a report
                    *  will be generated immediately.
                    */
                    if(`$INSTANCE_NAME`_hidIdleRate[interfaceNumber] <
                       `$INSTANCE_NAME`_hidIdleTimer[interfaceNumber])
                    {
                        /* Set the timer to zero and let the UpdateHIDTimer() API return IDLE_TIMER_EXPIRED status*/
                        `$INSTANCE_NAME`_hidIdleTimer[interfaceNumber] = 0u;
                    }
                    /* If the new request is received within 4 milliseconds
                    *  (1 count) of the end of the current period, then the
                    *  new request will have no effect until after the report.
                    */
                    else if(`$INSTANCE_NAME`_hidIdleTimer[interfaceNumber] <= 1u)
                    {
                        /* Do nothing.
                        *  Let the UpdateHIDTimer() API continue to work and
                        *  return IDLE_TIMER_EXPIRED status
                        */
                    }
                    else
                    {   /* Reload the timer*/
                        `$INSTANCE_NAME`_hidIdleTimer[interfaceNumber] =
                        `$INSTANCE_NAME`_hidIdleRate[interfaceNumber];
                    }
                    requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                }
                break;

            case `$INSTANCE_NAME`_HID_SET_PROTOCOL:
                /* Validate interfaceNumber and protocol (must be 0 or 1) */
                if ((interfaceNumber < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER) && (`$INSTANCE_NAME`_wValueLoReg <= 1u))
                {
                    `$INSTANCE_NAME`_hidProtocol[interfaceNumber] = (uint8)`$INSTANCE_NAME`_wValueLoReg;
                    requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                }
                break;
            
            default:    
                /* Unknown class request is not handled. */
                break;
        }
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: USB_FindHidClassDescriptor
****************************************************************************//**
*
*  This routine find Hid Class Descriptor pointer based on the Interface number
*  and Alternate setting then loads the currentTD structure with the address of
*  the buffer and the size.
*  The HID Class Descriptor resides inside the config descriptor.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_FindHidClassDecriptor(void) `=ReentrantKeil($INSTANCE_NAME . "_FindHidClassDecriptor")`
{
    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = `$INSTANCE_NAME`_GetConfigTablePtr(`$INSTANCE_NAME`_configuration - 1u);
    
    interfaceN = (uint8) `$INSTANCE_NAME`_wIndexLoReg;
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number*/
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp->p_list;
    
    /* Now use Alternate setting number */
    pTmp = &pTmp[`$INSTANCE_NAME`_interfaceSetting[interfaceN]];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp->p_list;
    
    /* Fifth entry in the LUT points to Hid Class Descriptor in Configuration Descriptor */
    pTmp = &pTmp[4u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    
    /* The first byte contains the descriptor length */
    `$INSTANCE_NAME`_currentTD.count = *pDescr;
    `$INSTANCE_NAME`_currentTD.pData = pDescr;
}


/*******************************************************************************
* Function Name: USB_FindReportDescriptor
****************************************************************************//**
*
*  This routine find Hid Report Descriptor pointer based on the Interface
*  number, then loads the currentTD structure with the address of the buffer
*  and the size.
*  Hid Report Descriptor is located after IN/OUT/FEATURE reports.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_FindReportDescriptor(void) `=ReentrantKeil($INSTANCE_NAME . "_FindReportDescriptor")`
{
    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = `$INSTANCE_NAME`_GetConfigTablePtr(`$INSTANCE_NAME`_configuration - 1u);
    interfaceN = (uint8) `$INSTANCE_NAME`_wIndexLoReg;
    
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp->p_list;
    
    /* Now use Alternate setting number */
    pTmp = &pTmp[`$INSTANCE_NAME`_interfaceSetting[interfaceN]];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp->p_list;
    
    /* Fourth entry in the LUT starts the Hid Report Descriptor */
    pTmp = &pTmp[3u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    
    /* The 1st and 2nd bytes of descriptor contain its length. LSB is 1st. */
    `$INSTANCE_NAME`_currentTD.count =  ((uint16)((uint16) pDescr[1u] << 8u) | pDescr[0u]);
    `$INSTANCE_NAME`_currentTD.pData = &pDescr[2u];
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FindReport
****************************************************************************//**
*
*  This routine sets up a transfer based on the Interface number, Report Type
*  and Report ID, then loads the currentTD structure with the address of the
*  buffer and the size.  The caller has to decide if it is a control read or
*  control write.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_FindReport(void) `=ReentrantKeil($INSTANCE_NAME . "_FindReport")`
{
    const T_`$INSTANCE_NAME`_LUT CYCODE *pTmp;
    T_`$INSTANCE_NAME`_TD *pTD;
    uint8 reportType;
    uint8 interfaceN;
 
    /* `#START HID_FINDREPORT` Place custom handling here */

    /* `#END` */
    
#ifdef `$INSTANCE_NAME`_FIND_REPORT_CALLBACK
    `$INSTANCE_NAME`_FindReport_Callback();
#endif /* (`$INSTANCE_NAME`_FIND_REPORT_CALLBACK) */
    
    `$INSTANCE_NAME`_currentTD.count = 0u;   /* Init not supported condition */
    pTmp = `$INSTANCE_NAME`_GetConfigTablePtr(`$INSTANCE_NAME`_configuration - 1u);
    reportType = (uint8) `$INSTANCE_NAME`_wValueHiReg;
    interfaceN = (uint8) `$INSTANCE_NAME`_wIndexLoReg;
    
    /* Third entry in the LUT Configuration Table starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp->p_list;
    if (interfaceN < `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER)
    {
        /* Now use Alternate setting number */
        pTmp = &pTmp[`$INSTANCE_NAME`_interfaceSetting[interfaceN]];
        
        /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
        pTmp = (const T_`$INSTANCE_NAME`_LUT CYCODE *) pTmp->p_list;
        
        /* Validate reportType to comply with "7.2.1 Get_Report Request" */
        if ((reportType >= `$INSTANCE_NAME`_HID_GET_REPORT_INPUT) &&
            (reportType <= `$INSTANCE_NAME`_HID_GET_REPORT_FEATURE))
        {
            /* Get the entry proper TD (IN, OUT or Feature Report Table)*/
            pTmp = &pTmp[reportType - 1u];
            
            /* Get reportID */
            reportType = (uint8) `$INSTANCE_NAME`_wValueLoReg;
            
            /* Validate table support by the HID descriptor, compare table count with reportID */
            if (pTmp->c >= reportType)
            {
                pTD = (T_`$INSTANCE_NAME`_TD *) pTmp->p_list;
                pTD = &pTD[reportType];                          /* select entry depend on report ID*/
                `$INSTANCE_NAME`_currentTD.pData = pTD->pData;   /* Buffer pointer */
                `$INSTANCE_NAME`_currentTD.count = pTD->count;   /* Buffer Size */
                `$INSTANCE_NAME`_currentTD.pStatusBlock = pTD->pStatusBlock;
            }
        }
    }
}


/*******************************************************************************
* Additional user functions supporting HID Requests
********************************************************************************/

/* `#START HID_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  `$INSTANCE_NAME`_ENABLE_HID_CLASS */


/* [] END OF FILE */
