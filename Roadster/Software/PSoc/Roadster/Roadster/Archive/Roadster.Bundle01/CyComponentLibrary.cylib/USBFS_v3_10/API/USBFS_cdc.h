/***************************************************************************//**
* \file `$INSTANCE_NAME`_cdc.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  CDC class.
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

#if !defined(CY_USBFS_`$INSTANCE_NAME`_cdc_H)
#define CY_USBFS_`$INSTANCE_NAME`_cdc_H

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
* Prototypes of the `$INSTANCE_NAME`_cdc API.
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
#if (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API != 0u)
    uint8 `$INSTANCE_NAME`_CDC_Init(void)            `=ReentrantKeil($INSTANCE_NAME . "_CDC_Init")`;
    void `$INSTANCE_NAME`_PutData(const uint8* pData, uint16 length) `=ReentrantKeil($INSTANCE_NAME . "_PutData")`;
    void `$INSTANCE_NAME`_PutString(const char8 string[])            `=ReentrantKeil($INSTANCE_NAME . "_PutString")`;
    void `$INSTANCE_NAME`_PutChar(char8 txDataByte) `=ReentrantKeil($INSTANCE_NAME . "_PutChar")`;
    void `$INSTANCE_NAME`_PutCRLF(void)             `=ReentrantKeil($INSTANCE_NAME . "_PutCRLF")`;
    uint16 `$INSTANCE_NAME`_GetCount(void)          `=ReentrantKeil($INSTANCE_NAME . "_GetCount")`;
    uint8  `$INSTANCE_NAME`_CDCIsReady(void)        `=ReentrantKeil($INSTANCE_NAME . "_CDCIsReady")`;
    uint8  `$INSTANCE_NAME`_DataIsReady(void)       `=ReentrantKeil($INSTANCE_NAME . "_DataIsReady")`;
    uint16 `$INSTANCE_NAME`_GetData(uint8* pData, uint16 length)     `=ReentrantKeil($INSTANCE_NAME . "_GetData")`;
    uint16 `$INSTANCE_NAME`_GetAll(uint8* pData)    `=ReentrantKeil($INSTANCE_NAME . "_GetAll")`;
    uint8  `$INSTANCE_NAME`_GetChar(void)           `=ReentrantKeil($INSTANCE_NAME . "_GetChar")`;
    uint8  `$INSTANCE_NAME`_IsLineChanged(void)     `=ReentrantKeil($INSTANCE_NAME . "_IsLineChanged")`;
    uint32 `$INSTANCE_NAME`_GetDTERate(void)        `=ReentrantKeil($INSTANCE_NAME . "_GetDTERate")`;
    uint8  `$INSTANCE_NAME`_GetCharFormat(void)     `=ReentrantKeil($INSTANCE_NAME . "_GetCharFormat")`;
    uint8  `$INSTANCE_NAME`_GetParityType(void)     `=ReentrantKeil($INSTANCE_NAME . "_GetParityType")`;
    uint8  `$INSTANCE_NAME`_GetDataBits(void)       `=ReentrantKeil($INSTANCE_NAME . "_GetDataBits")`;
    uint16 `$INSTANCE_NAME`_GetLineControl(void)    `=ReentrantKeil($INSTANCE_NAME . "_GetLineControl")`;
    void `$INSTANCE_NAME`_SendSerialState (uint16 serialState) `=ReentrantKeil($INSTANCE_NAME . "_SendSerialState ")`;
    uint16 `$INSTANCE_NAME`_GetSerialState (void)   `=ReentrantKeil($INSTANCE_NAME . "_GetSerialState ")`;
    void `$INSTANCE_NAME`_SetComPort (uint8 comNumber) `=ReentrantKeil($INSTANCE_NAME . "_SetComPort ")`;
    uint8 `$INSTANCE_NAME`_GetComPort (void)        `=ReentrantKeil($INSTANCE_NAME . "_GetComPort ")`;
    uint8 `$INSTANCE_NAME`_NotificationIsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_NotificationIsReady")`;

#endif  /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API) */
/** @} cdc */

/*******************************************************************************
*  Constants for `$INSTANCE_NAME`_cdc API.
*******************************************************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define `$INSTANCE_NAME`_CDC_SET_LINE_CODING        (0x20u)
#define `$INSTANCE_NAME`_CDC_GET_LINE_CODING        (0x21u)
#define `$INSTANCE_NAME`_CDC_SET_CONTROL_LINE_STATE (0x22u)

/*PSTN Subclass Specific Notifications (CDC ver 1.2 Table 30)*/
#define `$INSTANCE_NAME`_SERIAL_STATE               (0x20u)

#define `$INSTANCE_NAME`_LINE_CODING_CHANGED        (0x01u)
#define `$INSTANCE_NAME`_LINE_CONTROL_CHANGED       (0x02u)

#define `$INSTANCE_NAME`_1_STOPBIT                  (0x00u)
#define `$INSTANCE_NAME`_1_5_STOPBITS               (0x01u)
#define `$INSTANCE_NAME`_2_STOPBITS                 (0x02u)

#define `$INSTANCE_NAME`_PARITY_NONE                (0x00u)
#define `$INSTANCE_NAME`_PARITY_ODD                 (0x01u)
#define `$INSTANCE_NAME`_PARITY_EVEN                (0x02u)
#define `$INSTANCE_NAME`_PARITY_MARK                (0x03u)
#define `$INSTANCE_NAME`_PARITY_SPACE               (0x04u)

#define `$INSTANCE_NAME`_LINE_CODING_SIZE           (0x07u)
#define `$INSTANCE_NAME`_LINE_CODING_RATE           (0x00u)
#define `$INSTANCE_NAME`_LINE_CODING_STOP_BITS      (0x04u)
#define `$INSTANCE_NAME`_LINE_CODING_PARITY         (0x05u)
#define `$INSTANCE_NAME`_LINE_CODING_DATA_BITS      (0x06u)

#define `$INSTANCE_NAME`_LINE_CONTROL_DTR           (0x01u)
#define `$INSTANCE_NAME`_LINE_CONTROL_RTS           (0x02u)

#define `$INSTANCE_NAME`_MAX_MULTI_COM_NUM          (2u) 

#define `$INSTANCE_NAME`_COM_PORT1                  (0u) 
#define `$INSTANCE_NAME`_COM_PORT2                  (1u) 

#define `$INSTANCE_NAME`_SUCCESS                    (0u)
#define `$INSTANCE_NAME`_FAILURE                    (1u)

#define `$INSTANCE_NAME`_SERIAL_STATE_SIZE          (10u)

/* SerialState constants*/
#define `$INSTANCE_NAME`_SERIAL_STATE_REQUEST_TYPE  (0xA1u)
#define `$INSTANCE_NAME`_SERIAL_STATE_LENGTH        (0x2u)

/*******************************************************************************
* External data references
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
extern volatile uint8  `$INSTANCE_NAME`_linesCoding[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM][`$INSTANCE_NAME`_LINE_CODING_SIZE];
extern volatile uint8  `$INSTANCE_NAME`_linesChanged[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
extern volatile uint16 `$INSTANCE_NAME`_linesControlBitmap[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
extern volatile uint16 `$INSTANCE_NAME`_serialStateBitmap[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
extern volatile uint8  `$INSTANCE_NAME`_cdcDataInEp[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
extern volatile uint8  `$INSTANCE_NAME`_cdcDataOutEp[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
extern volatile uint8  `$INSTANCE_NAME`_cdcCommInInterruptEp[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
/** @} cdc */

/*******************************************************************************
* The following code is DEPRECATED and
* must not be used.
*******************************************************************************/


#define `$INSTANCE_NAME`_lineCoding             `$INSTANCE_NAME`_linesCoding[0]
#define `$INSTANCE_NAME`_lineChanged            `$INSTANCE_NAME`_linesChanged[0]
#define `$INSTANCE_NAME`_lineControlBitmap      `$INSTANCE_NAME`_linesControlBitmap[0]
#define `$INSTANCE_NAME`_cdc_data_in_ep         `$INSTANCE_NAME`_cdcDataInEp[0]
#define `$INSTANCE_NAME`_cdc_data_out_ep        `$INSTANCE_NAME`_cdcDataOutEp[0]

#endif /* (CY_USBFS_`$INSTANCE_NAME`_cdc_H) */


/* [] END OF FILE */
