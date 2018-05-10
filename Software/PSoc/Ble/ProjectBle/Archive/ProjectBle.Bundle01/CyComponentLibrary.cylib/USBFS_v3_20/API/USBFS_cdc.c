/***************************************************************************//**
* \file `$INSTANCE_NAME`_cdc.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the USB CDC class request handler.
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

#include "`$INSTANCE_NAME`_cdc.h"
#include "`$INSTANCE_NAME`_pvt.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS)

/*******************************************************************************
*    CDC Variables
*******************************************************************************/

/*PUBLIC*/
/** Contains the current line coding structure. The host sets it using a
 * SET_LINE_CODING request and returns it to the user code using the
 * `$INSTANCE_NAME`_GetDTERate(), `$INSTANCE_NAME`_GetCharFormat(),
 * `$INSTANCE_NAME`_GetParityType(), and `$INSTANCE_NAME`_GetDataBits() APIs.
 * It is an array of 2 elements for COM port 1 and COM port 2 for MultiCOM port
 * support. In case of 1 COM port, data is in 0 element.*/
volatile uint8 `$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM][`$INSTANCE_NAME`_LINE_CODING_SIZE] =
{
    /*COM Port 1*/
    {
    0x00u, 0xC2u, 0x01u, 0x00u,     /* Data terminal rate 115200 */
    0x00u,                          /* 1 Stop bit */
    0x00u,                          /* None parity */
    0x08u                           /* 8 data bits */
    },
    /*COM Port 2*/
    {
    0x00u, 0xC2u, 0x01u, 0x00u,     /* Data terminal rate 115200 */
    0x00u,                          /* 1 Stop bit */
    0x00u,                          /* None parity */
    0x08u                           /* 8 data bits */
    }
};

/**Used as a flag for the `$INSTANCE_NAME`_IsLineChanged() API, to inform it that the
 * host has been sent a request to change line coding or control bitmap. It is 
 * an array of 2 elements for COM port 1 and COM port 2 for MultiCOM port 
 * support. In case of 1 COM port, data is in 0 element.*/
volatile uint8  `$INSTANCE_NAME`_linesChanged[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
/** Contains the current control-signal bitmap. The host sets it using a
 * SET_CONTROL_LINE request and returns it to the user code using the 
 * `$INSTANCE_NAME`_GetLineControl() API. It is an array of 2 elements for COM 
 * port 1 and COM port 2 for MultiCOM port support. In case of 1 COM port, data 
 * is in 0 element.*/
volatile uint16 `$INSTANCE_NAME`_linesControlBitmap[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
/** Contains the 16-bit serial state value that was sent using the 
 * \ref `$INSTANCE_NAME`_SendSerialState() API. . It is an array of 2 elements 
 * for COM port 1 and COM port 2 for MultiCOM port support. In case of 1 COM 
 * port, data is in 0 element.*/
volatile uint16 `$INSTANCE_NAME`_serialStateBitmap[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
/** Contains the data IN endpoint number. It is initialized after a 
 * SET_CONFIGURATION request based on a user descriptor. It is used in CDC APIs 
 * to send data to the PC. It is an array of 2 elements for COM port 1 and COM 
 * port 2 for MultiCOM port support. In case of 1 COM port, data is in 0 element.*/
volatile uint8  `$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
/** Contains the data OUT endpoint number. It is initialized after a 
 * SET_CONFIGURATION request based on user descriptor. It is used in CDC APIs to 
 * receive data from the PC. It is an array of 2 elements for COM port 1 and COM  
 * port 2 for MultiCOM port support. In case of 1 COM port, data is in 0 element.*/
volatile uint8  `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
/** Contains the data IN endpoint number for COMMUNICATION interface. It is 
 * initialized after a SET_CONFIGURATION request based on a user descriptor. It 
 * is used in CDC APIs to send data to the PC. It is an array of 2 elements for 
 * COM port 1 and COM port 2 for MultiCOM port support. In case of 1 COM port, 
 * data is in 0 element.*/
volatile uint8  `$INSTANCE_NAME`_cdcCommInInterruptEp[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];

/*PRIVATE*/

#define `$INSTANCE_NAME`_CDC_IN_EP      (0u)
#define `$INSTANCE_NAME`_CDC_OUT_EP     (1u)
#define `$INSTANCE_NAME`_CDC_NOTE_EP    (2u)

#define `$INSTANCE_NAME`_CDC_EP_MASK    (0x01u)

#define `$INSTANCE_NAME`_GET_EP_COM_NUM(cdcComNums, epType) (((cdcComNums) >> (epType)) & `$INSTANCE_NAME`_CDC_EP_MASK)


/***************************************
*     Static Function Prototypes
***************************************/
#if (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API != 0u)
    static uint16 `$INSTANCE_NAME`_StrLen(const char8 string[]) `=ReentrantKeil($INSTANCE_NAME . "_StrLen")`;
    static t_`$INSTANCE_NAME`_cdc_notification `$INSTANCE_NAME`_serialStateNotification =
    {

        `$INSTANCE_NAME`_SERIAL_STATE_REQUEST_TYPE, /* bRequestType    */
        `$INSTANCE_NAME`_SERIAL_STATE,              /* bNotification   */
        0u,                                         /* wValue          */
        0u,                                         /* wValueMSB       */
        0u,                                         /* wIndex          */
        0u,                                         /* wIndexMSB       */
        `$INSTANCE_NAME`_SERIAL_STATE_LENGTH,       /* wLength         */
        0u,                                         /* wLengthMSB      */
        0u,                                         /* wSerialState    */
        0u,                                         /* wSerialStateMSB */
    };
    static uint8 `$INSTANCE_NAME`_activeCom = 0u;
#endif /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API != 0u) */


/***************************************
* Custom Declarations
***************************************/

/* `#START CDC_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DispatchCDCClassRqst
****************************************************************************//**
*
*  This routine dispatches CDC class requests.
*
* \return
*  requestHandled
*
* \globalvars
*   `$INSTANCE_NAME`_linesCoding: Contains the current line coding structure.
*     It is set by the Host using SET_LINE_CODING request and returned to the
*     user code by the USBFS_GetDTERate(), USBFS_GetCharFormat(),
*     USBFS_GetParityType(), USBFS_GetDataBits() APIs.
*   `$INSTANCE_NAME`_linesControlBitmap: Contains the current control signal
*     bitmap. It is set by the Host using SET_CONTROL_LINE request and returned
*     to the user code by the USBFS_GetLineControl() API.
*   `$INSTANCE_NAME`_linesChanged: This variable is used as a flag for the
*     USBFS_IsLineChanged() API, to be aware that Host has been sent request
*     for changing Line Coding or Control Bitmap.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DispatchCDCClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchCDCClassRqst")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;
    uint8 comPort;

    comPort = `$INSTANCE_NAME`_GetInterfaceComPort((uint8)`$INSTANCE_NAME`_wIndexLoReg);

    /* Check request direction: D2H or H2D. */
    if (0u != (`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */

        switch (`$INSTANCE_NAME`_bRequestReg)
        {
            case `$INSTANCE_NAME`_CDC_GET_LINE_CODING:
                `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_LINE_CODING_SIZE;
                `$INSTANCE_NAME`_currentTD.pData = `$INSTANCE_NAME`_linesCoding[comPort];
                requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                break;

            /* `#START CDC_READ_REQUESTS` Place other request handler here */

            /* `#END` */

            default:
            /* Do not handle this request unless callback is defined. */
            #ifdef `$INSTANCE_NAME`_DISPATCH_CDC_CLASS_CDC_READ_REQUESTS_CALLBACK
                requestHandled = `$INSTANCE_NAME`_DispatchCDCClass_CDC_READ_REQUESTS_Callback();
            #endif /* (`$INSTANCE_NAME`_DISPATCH_CDC_CLASS_CDC_READ_REQUESTS_CALLBACK) */
                break;
        }
    }
    else
    {
        /* Handle direction from host to device. */

        switch (`$INSTANCE_NAME`_bRequestReg)
        {
            case `$INSTANCE_NAME`_CDC_SET_LINE_CODING:
                `$INSTANCE_NAME`_currentTD.count  = `$INSTANCE_NAME`_LINE_CODING_SIZE;
                `$INSTANCE_NAME`_currentTD.pData  = `$INSTANCE_NAME`_linesCoding[comPort];
                `$INSTANCE_NAME`_linesChanged[comPort] |= `$INSTANCE_NAME`_LINE_CODING_CHANGED;

                requestHandled = `$INSTANCE_NAME`_InitControlWrite();
                break;

            case `$INSTANCE_NAME`_CDC_SET_CONTROL_LINE_STATE:
                `$INSTANCE_NAME`_linesControlBitmap[comPort] = (uint8) `$INSTANCE_NAME`_wValueLoReg;
                `$INSTANCE_NAME`_linesChanged[comPort]      |= `$INSTANCE_NAME`_LINE_CONTROL_CHANGED;

                requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                break;

            /* `#START CDC_WRITE_REQUESTS` Place other request handler here */

            /* `#END` */

            default:
                /* Do not handle this request unless callback is defined. */
            #ifdef `$INSTANCE_NAME`_DISPATCH_CDC_CLASS_CDC_WRITE_REQUESTS_CALLBACK
                requestHandled = `$INSTANCE_NAME`_DispatchCDCClass_CDC_WRITE_REQUESTS_Callback();
            #endif /* (`$INSTANCE_NAME`_DISPATCH_CDC_CLASS_CDC_WRITE_REQUESTS_CALLBACK) */
                break;
        }
    }

    return(requestHandled);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterfaceComPort
************************************************************************//**
*   \internal
*  Internal function which gets number of COM port by specified interface
*   number.
*
* \param uint8 interface
*  Interface number
*
* \return
*  COM port number (0 or 1) or error 0xFF
*
***************************************************************************/
uint8 `$INSTANCE_NAME`_GetInterfaceComPort(uint8 interface) `=ReentrantKeil($INSTANCE_NAME . "_GetInterfaceComPort")`
{
    uint8 comPort = 0u;
    uint8 res = 0xFFu;
    uint8 notEp;

    while (comPort < `$INSTANCE_NAME`_MAX_MULTI_COM_NUM)
    {
        notEp = `$INSTANCE_NAME`_cdcCommInInterruptEp[comPort];

        if (`$INSTANCE_NAME`_EP[notEp].interface == interface)
        {
            res = comPort;
            comPort = `$INSTANCE_NAME`_MAX_MULTI_COM_NUM;
        }

        comPort++;
    }
    return (res);
}


/***************************************
* Optional CDC APIs
***************************************/
#if (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API != 0u)
/***************************************************************************
* Function Name: `$INSTANCE_NAME`_CDC_Init
************************************************************************//**
*
*  This function initializes the CDC interface to be ready to receive data
*  from the PC. The API set active communication port to 0 in the case of 
*  multiple communication port support.This API should be called after the 
*  device has been started and configured using USBUART_Start() API to 
*  initialize and start the USBFS component operation. Then call the 
*  USBUART_GetConfiguration() API to wait until the host has enumerated and 
*  configured the device. For example:
*
*  \snippet /USBFS_sut_02.cydsn/main.c wait for enumeration
*
* \return
*  cystatus:
*   Return Value    Description
*   `$INSTANCE_NAME`_SUCCESS   CDC interface was initialized correctly
*   `$INSTANCE_NAME`_FAILURE   CDC interface was not initialized
*
* \globalvars
*   `$INSTANCE_NAME`_linesChanged: Initialized to zero.
*   `$INSTANCE_NAME`_cdcDataOutEp: Used as an OUT endpoint number.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_CDC_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_CDC_Init")`
{
    uint8 comPort;
    uint8 outEp;
    uint8 ret = `$INSTANCE_NAME`_SUCCESS;

    `$INSTANCE_NAME`_activeCom = 0u;
    `$INSTANCE_NAME`_linesChanged[`$INSTANCE_NAME`_COM_PORT1] = 0u;
    `$INSTANCE_NAME`_linesChanged[`$INSTANCE_NAME`_COM_PORT2] = 0u;

    for(comPort = 0u; comPort<`$INSTANCE_NAME`_MAX_MULTI_COM_NUM; comPort++)
    {
        outEp = `$INSTANCE_NAME`_cdcDataOutEp[comPort];
        if((0u != outEp) && (`$INSTANCE_NAME`_MAX_EP > outEp))
        {
            `$INSTANCE_NAME`_EnableOutEP(outEp);
        }

    }

    /* COM Port 1 should be correct to proceed. */
    if ((0u == `$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_COM_PORT1]) \
            || (0u == `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_COM_PORT1]) \
            || (0u ==  `$INSTANCE_NAME`_cdcCommInInterruptEp[`$INSTANCE_NAME`_COM_PORT1])
            || (`$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_COM_PORT1] >= `$INSTANCE_NAME`_MAX_EP)
            || (`$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_COM_PORT1] >= `$INSTANCE_NAME`_MAX_EP)
            || (`$INSTANCE_NAME`_cdcCommInInterruptEp[`$INSTANCE_NAME`_COM_PORT1] >= `$INSTANCE_NAME`_MAX_EP))
    {
        ret = `$INSTANCE_NAME`_FAILURE;
    }

    return (ret);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutData
****************************************************************************//**
*
*  This function sends a specified number of bytes from the location specified
*  by a pointer to the PC. The `$INSTANCE_NAME`_CDCIsReady() function should be
*  called before sending new data, to be sure that the previous data has
*  finished sending.
*  If the last sent packet is less than maximum packet size the USB transfer
*  of this short packet will identify the end of the segment. If the last sent
*  packet is exactly maximum packet size, it shall be followed by a zero-length
*  packet (which is a short packet) to assure the end of segment is properly
*  identified. To send zero-length packet, use `$INSTANCE_NAME`_PutData() API
*  with length parameter set to zero.
*
*  \param pData: pointer to the buffer containing data to be sent.
*  \param length: Specifies the number of bytes to send from the pData
*  buffer. Maximum length will be limited by the maximum packet
*  size for the endpoint. Data will be lost if length is greater than Max
*  Packet Size.
*
* \globalvars
*
*   `$INSTANCE_NAME`_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutData(const uint8* pData, uint16 length) `=ReentrantKeil($INSTANCE_NAME . "_PutData")`
{
    uint8 epNumber = `$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_activeCom];

    /* Limit length to maximum packet size for endpoint. */
    if (length > `$INSTANCE_NAME`_EP[epNumber].bufferSize)
    {
        /* Caution: Data will be lost if length is greater than Max Packet Size. */
        length = `$INSTANCE_NAME`_EP[epNumber].bufferSize;

        /* Halt CPU in debug mode */
        CYASSERT(0u != 0u);
    }

    `$INSTANCE_NAME`_LoadInEP(epNumber, pData, length);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StrLen
****************************************************************************//**
*
*  Calculates length of a null terminated string.
*
*  \param string: pointer to the string.
*
* \return
*  Length of the string
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_StrLen(const char8 string[]) `=ReentrantKeil($INSTANCE_NAME . "_StrLen")`
{
    uint16 len = 0u;

    while (string[len] != (char8)0)
    {
        len++;
    }

    return ((uint16) len);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_PutString
************************************************************************//**
*
*  This function sends a null terminated string to the PC. This function will
*  block if there is not enough memory to place the whole string. It will block
*  until the entire string has been written to the transmit buffer.
*  The `$INSTANCE_NAME`_CDCIsReady() function should be called before
*  sending data with a new call to `$INSTANCE_NAME`_PutString(), to be sure
*  that the previous data has finished sending. This function sends
*  zero-length packet automatically, if the length of the last packet, sent
*  by this API, is equal to Max Packet Size
*
*  \param string: pointer to the string to be sent to the PC.
*
* \globalvars
*
*   `$INSTANCE_NAME`_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
* \reentrant
*  No.
*
***************************************************************************/
void `$INSTANCE_NAME`_PutString(const char8 string[]) `=ReentrantKeil($INSTANCE_NAME . "_PutString")`
{
    uint16 strLength;
    uint16 sendLength;
    uint16 bufIndex = 0u;

    uint8  epNumber = `$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_activeCom];

    /* Get length string length (it is terminated with zero). */
    strLength = `$INSTANCE_NAME`_StrLen(string);

    do
    {
        /* Limit length to maximum packet size of endpoint. */
        sendLength = (strLength > `$INSTANCE_NAME`_EP[epNumber].bufferSize) ?
                                  `$INSTANCE_NAME`_EP[epNumber].bufferSize : strLength;

        /* Load IN endpoint and expose it to host. */
        `$INSTANCE_NAME`_LoadInEP(epNumber, (const uint8 *)&string[bufIndex], sendLength);
        strLength -= sendLength;

        /* If more data are present to send or full packet was sent */
        if ((strLength > 0u) || (sendLength == `$INSTANCE_NAME`_EP[epNumber].bufferSize))
        {
            bufIndex += sendLength;

            /* Wait until host read data from IN endpoint buffer. */
            while (`$INSTANCE_NAME`_IN_BUFFER_FULL == `$INSTANCE_NAME`_EP[epNumber].apiEpState)
            {
            }

            /* If last packet is exactly maximum packet size, it shall be followed
            * by a zero-length packet to assure the end of segment is properly
            * identified by the terminal.
            */
            if (0u == strLength)
            {
                `$INSTANCE_NAME`_LoadInEP(epNumber, NULL, 0u);
            }
        }
    }
    while (strLength > 0u);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_PutChar
************************************************************************//**
*
*  This function writes a single character to the PC at a time. This is an
*  inefficient way to send large amounts of data.
*
*  \param txDataByte: Character to be sent to the PC.
*
*  \globalvars
*
*   `$INSTANCE_NAME`_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
*  \reentrant
*  No.
*
***************************************************************************/
void `$INSTANCE_NAME`_PutChar(char8 txDataByte) `=ReentrantKeil($INSTANCE_NAME . "_PutChar")`
{
    uint8 dataByte;
    dataByte = (uint8) txDataByte;

    `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_activeCom], &dataByte, 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutCRLF
****************************************************************************//**
*
*  This function sends a carriage return (0x0D) and line feed (0x0A) to the
*  PC. This APIis provided to mimic API provided by our other UART components
*
* \globalvars
*
*   `$INSTANCE_NAME`_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutCRLF(void) `=ReentrantKeil($INSTANCE_NAME . "_PutCRLF")`
{
    const uint8 CYCODE txData[] = {0x0Du, 0x0Au};

    `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_activeCom], (const uint8 *)txData, 2u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCount
****************************************************************************//**
*
*  This function returns the number of bytes that were received from the PC.
*  The returned length value should be passed to `$INSTANCE_NAME`_GetData() as
*  a parameter to read all received data. If all of the received data is not
*  read at one time by the `$INSTANCE_NAME`_GetData() API, the unread data will
*  be lost.
*
* \return
*  Returns the number of received bytes. The maximum amount of received data at
*  a time is limited by the maximum packet size for the endpoint.
*
* \globalvars
*   `$INSTANCE_NAME`_cdcDataOutEp: CDC OUT endpoint number used.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetCount(void) `=ReentrantKeil($INSTANCE_NAME . "_GetCount")`
{
    uint16 bytesCount;

    uint8  epNumber = `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_activeCom];

    if (`$INSTANCE_NAME`_OUT_BUFFER_FULL == `$INSTANCE_NAME`_EP[epNumber].apiEpState)
    {
        bytesCount = `$INSTANCE_NAME`_GetEPCount(epNumber);
    }
    else
    {
        bytesCount = 0u;
    }

    return (bytesCount);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DataIsReady
****************************************************************************//**
*
*  This function returns a non-zero value if the component received data or
*  received zero-length packet. The `$INSTANCE_NAME`_GetAll() or
*  `$INSTANCE_NAME`_GetData() API should be called to read data from the buffer
*  and reinitialize the OUT endpoint even when a zero-length packet is
*  received. These APIs will return zero value when zero-length packet is
*  received.
*
* \return
*  If the OUT packet is received, this function returns a non-zero value.
*  Otherwise, it returns zero.
*
* \globalvars
*   `$INSTANCE_NAME`_cdcDataOutEp: CDC OUT endpoint number used.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DataIsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_DataIsReady")`
{
    return (`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_activeCom]));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CDCIsReady
****************************************************************************//**
*
*  This function returns a non-zero value if the component is ready to send more
*  data to the PC; otherwise, it returns zero. The function should be called
*  before sending new data when using any of the following APIs:
*  `$INSTANCE_NAME`_PutData(),`$INSTANCE_NAME`_PutString(),
*  `$INSTANCE_NAME`_PutChar or `$INSTANCE_NAME`_PutCRLF(),
*  to be sure that the previous data has finished sending.
*
* \return
*  If the buffer can accept new data, this function returns a non-zero value.
*  Otherwise, it returns zero.
*
* \globalvars
*   `$INSTANCE_NAME`_cdcDataInEp: CDC IN endpoint number used.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_CDCIsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_CDCIsReady")`
{
    return (`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_activeCom]));
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_GetData
************************************************************************//**
*
*  This function gets a specified number of bytes from the input buffer and
*  places them in a data array specified by the passed pointer.
*  The `$INSTANCE_NAME`_DataIsReady() API should be called first, to be sure
*  that data is received from the host. If all received data will not be read at
*  once, the unread data will be lost. The `$INSTANCE_NAME`_GetData() API should
*  be called to get the number of bytes that were received.
*
*  \param pData: Pointer to the data array where data will be placed.
*  \param Length: Number of bytes to read into the data array from the RX buffer.
*          Maximum length is limited by the the number of received bytes
*          or 64 bytes.
*
* \return
*         Number of bytes which function moves from endpoint RAM into the
*         data array. The function moves fewer than the requested number
*         of bytes if the host sends fewer bytes than requested or sends
*         zero-length packet.
*
* \globalvars
*   `$INSTANCE_NAME`_cdcDataOutEp: CDC OUT endpoint number used.
*
* \reentrant
*  No.
*
***************************************************************************/
uint16 `$INSTANCE_NAME`_GetData(uint8* pData, uint16 length) `=ReentrantKeil($INSTANCE_NAME . "_GetData")`
{
    uint8 epNumber = `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_activeCom];

    /* Read data from OUT endpoint buffer. */
    length = `$INSTANCE_NAME`_ReadOutEP(epNumber, pData, length);

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL)
    /* Wait until DMA complete transferring data from OUT endpoint buffer. */
    while (`$INSTANCE_NAME`_OUT_BUFFER_FULL == `$INSTANCE_NAME`_GetEPState(epNumber))
    {
    }

    /* Enable OUT endpoint to communicate with host. */
    `$INSTANCE_NAME`_EnableOutEP(epNumber);
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL) */

    return (length);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAll
****************************************************************************//**
*
*  This function gets all bytes of received data from the input buffer and
*  places them into a specified data array. The
*  `$INSTANCE_NAME`_DataIsReady() API should be called first, to be sure
*  that data is received from the host.
*
*  \param pData: Pointer to the data array where data will be placed.
*
* \return
*  Number of bytes received. The maximum amount of the received at a time
*  data is 64 bytes.
*
* \globalvars
*   - \ref `$INSTANCE_NAME`_cdcDataOutEp: CDC OUT endpoint number used.
*   - \ref `$INSTANCE_NAME`_EP[].bufferSize: EP max packet size is used as a
*     length to read all data from the EP buffer.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetAll(uint8* pData) `=ReentrantKeil($INSTANCE_NAME . "_GetAll")`
{
    uint8 epNumber = `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_activeCom];
    uint16 dataLength;

    /* Read data from OUT endpoint buffer. */
    dataLength = `$INSTANCE_NAME`_ReadOutEP(epNumber, pData, `$INSTANCE_NAME`_EP[epNumber].bufferSize);

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL)
    /* Wait until DMA complete transferring data from OUT endpoint buffer. */
    while (`$INSTANCE_NAME`_OUT_BUFFER_FULL == `$INSTANCE_NAME`_GetEPState(epNumber))
    {
    }

    /* Enable OUT endpoint to communicate with host. */
    `$INSTANCE_NAME`_EnableOutEP(epNumber);
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL) */

    return (dataLength);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_GetChar
************************************************************************//**
*
*  This function reads one byte of received data from the buffer. If more than
*  one byte has been received from the host, the rest of the data will be lost.
*
* \return
*  Received one character.
*
* \globalvars
*   `$INSTANCE_NAME`_cdcDataOutEp: CDC OUT endpoint number used.
*
* \reentrant
*  No.
*
***************************************************************************/
uint8 `$INSTANCE_NAME`_GetChar(void) `=ReentrantKeil($INSTANCE_NAME . "_GetChar")`
{
     uint8 rxData;
     uint8 epNumber = `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_activeCom];

    (void) `$INSTANCE_NAME`_ReadOutEP(epNumber, &rxData, 1u);

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL)
    /* Wait until DMA complete transferring data from OUT endpoint buffer. */
    while (`$INSTANCE_NAME`_OUT_BUFFER_FULL == `$INSTANCE_NAME`_GetEPState(epNumber))
    {
    }

    /* Enable OUT endpoint to communicate with host. */
    `$INSTANCE_NAME`_EnableOutEP(epNumber);
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL) */

    return (rxData);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsLineChanged
****************************************************************************//**
*
*  This function returns clear on read status of the line. It returns not zero
*  value when the host sends updated coding or control information to the
*  device. The `$INSTANCE_NAME`_GetDTERate(), `$INSTANCE_NAME`_GetCharFormat()
*  or `$INSTANCE_NAME`_GetParityType() or `$INSTANCE_NAME`_GetDataBits() API
*  should be called to read data coding information.
*  The `$INSTANCE_NAME`_GetLineControl() API should be called to read line
*  control information.
*
* \return
*  If SET_LINE_CODING or CDC_SET_CONTROL_LINE_STATE requests are received, it
*  returns a non-zero value. Otherwise, it returns zero.
*  Return Value                 | Description
*  -----------------------------|--------------------------
*  USBUART_LINE_CODING_CHANGED  | Line coding changed
*  USBUART_LINE_CONTROL_CHANGED |   Line control changed
*
* \globalvars
*  - \ref `$INSTANCE_NAME`_transferState: it is checked to be sure then OUT
*    data phase has been complete, and data written to the lineCoding or
*    Control Bitmap buffer.
*  - \ref `$INSTANCE_NAME`_linesChanged: used as a flag to be aware that
*    Host has been sent request for changing Line Coding or Control Bitmap.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_IsLineChanged(void) `=ReentrantKeil($INSTANCE_NAME . "_IsLineChanged")`
{
    uint8 state = 0u;

    /* transferState is checked to be sure then OUT data phase has been complete */
    if (`$INSTANCE_NAME`_transferState == `$INSTANCE_NAME`_TRANS_STATE_IDLE)
    {
        if (`$INSTANCE_NAME`_linesChanged[`$INSTANCE_NAME`_activeCom] != 0u)
        {
            state = `$INSTANCE_NAME`_linesChanged[`$INSTANCE_NAME`_activeCom];
            `$INSTANCE_NAME`_linesChanged[`$INSTANCE_NAME`_activeCom] = 0u;
        }
    }

    return (state);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDTERate
************************************************************************//**
*
*  This function returns the data terminal rate set for this port in bits
*  per second.
*
* \return
*  Returns a uint32 value of the data rate in bits per second.
*
* \globalvars
*  `$INSTANCE_NAME`_linesCoding: First four bytes converted to uint32
*    depend on compiler, and returned as a data rate.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetDTERate(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDTERate")`
{
    uint32 rate;

    rate = `$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_activeCom][`$INSTANCE_NAME`_LINE_CODING_RATE + 3u];
    rate = (rate << 8u) | `$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_activeCom][`$INSTANCE_NAME`_LINE_CODING_RATE + 2u];
    rate = (rate << 8u) | `$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_activeCom][`$INSTANCE_NAME`_LINE_CODING_RATE + 1u];
    rate = (rate << 8u) | `$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_activeCom][`$INSTANCE_NAME`_LINE_CODING_RATE];

    return (rate);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCharFormat
****************************************************************************//**
*
*  Returns the number of stop bits.
*
* \return
*  Returns the number of stop bits.
*  Return               |Value Description
*  ---------------------|-------------------
*  USBUART_1_STOPBIT    | 1 stop bit
*  USBUART_1_5_STOPBITS | 1,5 stop bits
*  USBUART_2_STOPBITS   | 2 stop bits
*
*
* \globalvars
*  `$INSTANCE_NAME`_linesCoding: used to get a parameter.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetCharFormat(void) `=ReentrantKeil($INSTANCE_NAME . "_GetCharFormat")`
{
    return (`$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_activeCom][`$INSTANCE_NAME`_LINE_CODING_STOP_BITS]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetParityType
****************************************************************************//**
*
*  This function returns the parity type for the CDC port.
*
* \return
*  Returns the parity type.
*   Return               | Value Description
*  ----------------------|-------------------
*  USBUART_PARITY_NONE   | 1 stop bit
*  USBUART_PARITY_ODD    | 1,5 stop bits
*  USBUART_PARITY_EVEN   | 2 stop bits
*  USBUART_PARITY_MARK   | Mark
*  USBUART_PARITY_SPACE  | Space
*
* \globalvars
*  `$INSTANCE_NAME`_linesCoding: used to get a parameter.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetParityType(void) `=ReentrantKeil($INSTANCE_NAME . "_GetParityType")`
{
    return (`$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_activeCom][`$INSTANCE_NAME`_LINE_CODING_PARITY]);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDataBits
************************************************************************//**
*
*  This function returns the number of data bits for the CDC port.
*
* \return
*  Returns the number of data bits.
*  The number of data bits can be 5, 6, 7, 8 or 16.
*
* \globalvars
*  `$INSTANCE_NAME`_linesCoding: used to get a parameter.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetDataBits(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDataBits")`
{
    return (`$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_activeCom][`$INSTANCE_NAME`_LINE_CODING_DATA_BITS]);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_GetLineControl
************************************************************************//**
*
*  This function returns Line control bitmap that the host sends to the
*  device.
*
* \return
*  Returns Line control bitmap.
*  Return                   |Value Notes
*  -------------------------|-----------------------------------------------
*  USBUART_LINE_CONTROL_DTR |Indicates that a DTR signal is present. This signal corresponds to V.24 signal 108/2 and RS232 signal DTR.
*  USBUART_LINE_CONTROL_RTS |Carrier control for half-duplex modems. This signal corresponds to V.24 signal 105 and RS232 signal RTS.
*  RESERVED                 |The rest of the bits are reserved.
*
*  *Note* Some terminal emulation programs do not properly handle these
*  control signals. They update information about DTR and RTS state only
*  when the RTS signal changes the state.
*
* \globalvars
*  `$INSTANCE_NAME`_linesControlBitmap: used to get a parameter.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetLineControl(void) `=ReentrantKeil($INSTANCE_NAME . "_GetLineControl")`
{
    return (`$INSTANCE_NAME`_linesControlBitmap[`$INSTANCE_NAME`_activeCom]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SendSerialState
****************************************************************************//**
*
*  Sends the serial state notification to the host using the interrupt
*  endpoint for the COM port selected using the API SetComPort().The
*  `$INSTANCE_NAME`_NotificationIsReady() API must be called to check if the
*  Component is ready to send more serial state to the host. The API will
*  not send the notification data if the interrupt endpoint Max Packet Size
*  is less than the required 10 bytes.
*
* \param uint16 serialState
*  16-bit value that will be sent from the device to the
*  host as SERIAL_STATE notification using the IN interrupt endpoint. Refer
*  to revision 1.2 of the CDC PSTN Subclass specification for bit field
*  definitions of the 16-bit serial state value.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SendSerialState (uint16 serialState) `=ReentrantKeil($INSTANCE_NAME . "_SendSerialState ")`
{
    uint8 epNumber = `$INSTANCE_NAME`_cdcCommInInterruptEp[`$INSTANCE_NAME`_activeCom];

    if(`$INSTANCE_NAME`_SERIAL_STATE_SIZE <= `$INSTANCE_NAME`_EP[epNumber].bufferSize)
    {
        /* Save current SERIAL_STATE bitmap. */
        `$INSTANCE_NAME`_serialStateBitmap[`$INSTANCE_NAME`_activeCom] = serialState;

        /* Add interface number */
        `$INSTANCE_NAME`_serialStateNotification.wIndex = `$INSTANCE_NAME`_EP[epNumber].interface;

        /*Form SERIAL_STATE data*/
        `$INSTANCE_NAME`_serialStateNotification.wSerialState =    LO8(`$INSTANCE_NAME`_serialStateBitmap[`$INSTANCE_NAME`_activeCom]);
        `$INSTANCE_NAME`_serialStateNotification.wSerialStateMSB = HI8(`$INSTANCE_NAME`_serialStateBitmap[`$INSTANCE_NAME`_activeCom]);

        `$INSTANCE_NAME`_LoadInEP(epNumber, (uint8 *) &`$INSTANCE_NAME`_serialStateNotification, sizeof(`$INSTANCE_NAME`_serialStateNotification));
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSerialState
****************************************************************************//**
*
*  This function returns the current serial state value for the COM port
*  selected using the API SetComPort().
*
* \return
*  16-bit serial state value. Refer to revision 1.2 of the CDC PSTN Subclass
*  specification for bit field definitions of the 16-bit serial state value.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetSerialState(void) `=ReentrantKeil($INSTANCE_NAME . "_GetSerialState ")`
{
    return `$INSTANCE_NAME`_serialStateBitmap[`$INSTANCE_NAME`_activeCom];
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_NotificationIsReady
****************************************************************************//**
*
*  This function returns a non-zero value if the Component is ready to send
*  more notifications to the host; otherwise, it returns zero. The function
*  should be called before sending new notifications when using
*  `$INSTANCE_NAME`_SendSerialState() to ensure that any previous
*  notification data has been already sent to the host.
*
* \return
*  If the buffer can accept new data(endpoint buffer not full), this
*  function returns a non-zero value. Otherwise, it returns zero.
*
* \globalvars
*   `$INSTANCE_NAME`_cdcDataInEp: CDC IN endpoint number used.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_NotificationIsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_NotificationIsReady")`
{
    return (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdcCommInInterruptEp[`$INSTANCE_NAME`_activeCom]].apiEpState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetComPort
****************************************************************************//**
*
*  This function allows the user to select from one of the two COM ports
*  they wish to address in the instance of having multiple COM ports
*  instantiated though the use of a composite device. Once set, all future
*  function calls related to the USBUART will be affected. This addressed
*  COM port can be changed during run time.
*
* \param comNumber
*  Contains the COM interface the user wishes to address. Value can either
*  be 0 or 1 since a maximum of only 2 COM ports can be supported. Note that
*  this COM port number is not the COM port number assigned on the PC side
*  for the UART communication. If a value greater than 1 is passed, the
*  function returns without performing any action.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetComPort(uint8 comNumber) `=ReentrantKeil($INSTANCE_NAME . "_SetComPort ")`
{
    if ((`$INSTANCE_NAME`_activeCom != comNumber) && \
            (comNumber < `$INSTANCE_NAME`_MAX_MULTI_COM_NUM ))
    {
        `$INSTANCE_NAME`_activeCom = comNumber;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetComPort
****************************************************************************//**
*
*  This function returns the current selected COM port that the user is
*  currently addressing in the instance of having multiple COM ports
*  instantiated though the use of a composite device.
*
* \return
*  Returns the currently selected COM port. Value can either be 0 or 1 since
*  a maximum of only 2 COM ports can be supported. . Note that this COM port
*  number is not the COM port number assigned on the PC side for the UART
*  communication.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetComPort(void) `=ReentrantKeil($INSTANCE_NAME . "_GetComPort ")`
{
    return (`$INSTANCE_NAME`_activeCom);
}


#endif  /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API) */


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_Cdc_EpInit
************************************************************************//**
*
*  \internal
*  This routine decide type of endpoint (IN, OUT, Notification) and same to
*   appropriate global variables  according to COM port number.
*   `$INSTANCE_NAME`_cdcDataInEp[], `$INSTANCE_NAME`_cdcCommInInterruptEp[],
*   `$INSTANCE_NAME`_cdcDataOutEp[]
*
* \param pEP: Pointer to structure with current EP description.
* \param epNum: EP number
* \param cdcComNums: Bit array of current COM ports for CDC IN, OUT,
*        and notification EPs(0 - COM port 1, 1- COM port 2)
*
* \return
*  Updated cdcComNums
*
* \reentrant
*  No.
*
***************************************************************************/
uint8 `$INSTANCE_NAME`_Cdc_EpInit(const T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) `=ReentrantKeil($INSTANCE_NAME . "_ConfigAltChanged")`
{
    uint8 epType;

    epType = pEP->attributes & `$INSTANCE_NAME`_EP_TYPE_MASK;

    if (0u != (pEP->addr & `$INSTANCE_NAME`_DIR_IN))
    {
        if (epType != `$INSTANCE_NAME`_EP_TYPE_INT)
        {
            `$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_GET_EP_COM_NUM(cdcComNums, `$INSTANCE_NAME`_CDC_IN_EP)] = epNum;
            cdcComNums |= (uint8)(`$INSTANCE_NAME`_COM_PORT2 << `$INSTANCE_NAME`_CDC_IN_EP);
        }
        else
        {

            `$INSTANCE_NAME`_cdcCommInInterruptEp[`$INSTANCE_NAME`_GET_EP_COM_NUM(cdcComNums, `$INSTANCE_NAME`_CDC_NOTE_EP)] = epNum;
            cdcComNums |= (uint8)(`$INSTANCE_NAME`_COM_PORT2 << `$INSTANCE_NAME`_CDC_NOTE_EP);
        }
    }
    else
    {
        if (epType != `$INSTANCE_NAME`_EP_TYPE_INT)
        {
            `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_GET_EP_COM_NUM(cdcComNums, `$INSTANCE_NAME`_CDC_OUT_EP)] = epNum;
            cdcComNums |= (uint8)(`$INSTANCE_NAME`_COM_PORT2 << `$INSTANCE_NAME`_CDC_OUT_EP);
        }
    }
    return (cdcComNums);
}


/*******************************************************************************
* Additional user functions supporting CDC Requests
********************************************************************************/

/* `#START CDC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS) */


/* [] END OF FILE */
