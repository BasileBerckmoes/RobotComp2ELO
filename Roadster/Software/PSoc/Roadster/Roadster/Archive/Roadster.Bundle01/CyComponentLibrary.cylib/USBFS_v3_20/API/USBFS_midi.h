/***************************************************************************//**
* \file `$INSTANCE_NAME`_midi.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  MIDI class support.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for MIDI Devices Release 1.0
*  MIDI 1.0 Detailed Specification Document Version 4.2
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_`$INSTANCE_NAME`_midi_H)
#define CY_USBFS_`$INSTANCE_NAME`_midi_H

#include "`$INSTANCE_NAME`.h"

/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_ENABLE_MIDI_API    (0u != (`$EnableMidiApi`u))
#define `$INSTANCE_NAME`_MIDI_EXT_MODE      (`$extJackCount`u)
`$MIDI_APIGEN_DEFINES`

/* Number of external interfaces (UARTs). */
#define `$INSTANCE_NAME`_ONE_EXT_INTRF  (0x01u)
#define `$INSTANCE_NAME`_TWO_EXT_INTRF  (0x02u)
    
#define `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT \
            ((`$INSTANCE_NAME`_ENABLE_MIDI_API != 0u) && (`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE > 0) && \
             (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))

#define `$INSTANCE_NAME`_ISR_SERVICE_MIDI_IN \
            ((`$INSTANCE_NAME`_ENABLE_MIDI_API != 0u) && (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE > 0))


/***************************************
*    External References
***************************************/

#if (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_ONE_EXT_INTRF)
    #include "MIDI1_UART.h"
#endif /* (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_ONE_EXT_INTRF) */

#if (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_TWO_EXT_INTRF)
    #include "MIDI2_UART.h"
#endif /* (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_TWO_EXT_INTRF) */


/***************************************
*    Data Structure Definition
***************************************/

/* The following structure is used to hold status information for
* building and parsing incoming MIDI messages. 
*/
typedef struct
{
    uint8    length;        /* expected length */
    uint8    count;         /* current byte count */
    uint8    size;          /* complete size */
    uint8    runstat;       /* running status */
    uint8    msgBuff[4u];   /* message buffer */
} `$INSTANCE_NAME`_MIDI_RX_STATUS;


/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_midi
* @{
*/
#if defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && (`$INSTANCE_NAME`_ENABLE_MIDI_API != 0u)
    void `$INSTANCE_NAME`_MIDI_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_MIDI_Init")`;

    #if (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE > 0u)
        void `$INSTANCE_NAME`_MIDI_IN_Service(void) `=ReentrantKeil($INSTANCE_NAME . "_MIDI_IN_Service")`;
        uint8 `$INSTANCE_NAME`_PutUsbMidiIn(uint8 ic, const uint8 midiMsg[], uint8 cable) `=ReentrantKeil($INSTANCE_NAME . "_PutUsbMidiIn")`;
    #endif /* (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE > 0u) */

    #if (`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE > 0u)
        void `$INSTANCE_NAME`_MIDI_OUT_Service(void) `=ReentrantKeil($INSTANCE_NAME . "_MIDI_OUT_Service")`;
    #endif /* (`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE > 0u) */
#endif /*  (`$INSTANCE_NAME`_ENABLE_MIDI_API != 0u) */


/*******************************************************************************
*   Callback Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_callbackLocalMidiEvent
****************************************************************************//**
*
*  This is a callback function that locally processes data received from the PC 
*  in main.c. You should implement this function if you want to use it. It is 
*  called from the USB output processing routine for each MIDI output event 
*  processed (decoded) from the output endpoint buffer. 
*
*  \param cable: Cable number
*  
*  \param midiMsg: Pointer to the 3-byte MIDI message
*
*
***************************************************************************/
void `$INSTANCE_NAME`_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg)
                                                     `=ReentrantKeil($INSTANCE_NAME . "_callbackLocalMidiEvent")`;
/** @} midi */
                                                    
/***************************************
*           MIDI Constants.
***************************************/

/* Flag definitions for use with MIDI device inquiry */
#define `$INSTANCE_NAME`_INQ_SYSEX_FLAG             (0x01u)
#define `$INSTANCE_NAME`_INQ_IDENTITY_REQ_FLAG      (0x02u)

/* USB-MIDI Code Index Number Classifications (MIDI Table 4-1) */
#define `$INSTANCE_NAME`_CIN_MASK                   (0x0Fu)
#define `$INSTANCE_NAME`_RESERVED0                  (0x00u)
#define `$INSTANCE_NAME`_RESERVED1                  (0x01u)
#define `$INSTANCE_NAME`_2BYTE_COMMON               (0x02u)
#define `$INSTANCE_NAME`_3BYTE_COMMON               (0x03u)
#define `$INSTANCE_NAME`_SYSEX                      (0x04u)
#define `$INSTANCE_NAME`_1BYTE_COMMON               (0x05u)
#define `$INSTANCE_NAME`_SYSEX_ENDS_WITH1           (0x05u)
#define `$INSTANCE_NAME`_SYSEX_ENDS_WITH2           (0x06u)
#define `$INSTANCE_NAME`_SYSEX_ENDS_WITH3           (0x07u)
#define `$INSTANCE_NAME`_NOTE_OFF                   (0x08u)
#define `$INSTANCE_NAME`_NOTE_ON                    (0x09u)
#define `$INSTANCE_NAME`_POLY_KEY_PRESSURE          (0x0Au)
#define `$INSTANCE_NAME`_CONTROL_CHANGE             (0x0Bu)
#define `$INSTANCE_NAME`_PROGRAM_CHANGE             (0x0Cu)
#define `$INSTANCE_NAME`_CHANNEL_PRESSURE           (0x0Du)
#define `$INSTANCE_NAME`_PITCH_BEND_CHANGE          (0x0Eu)
#define `$INSTANCE_NAME`_SINGLE_BYTE                (0x0Fu)

#define `$INSTANCE_NAME`_CABLE_MASK                 (0xF0u)
#define `$INSTANCE_NAME`_MIDI_CABLE_00              (0x00u)
#define `$INSTANCE_NAME`_MIDI_CABLE_01              (0x10u)

#define `$INSTANCE_NAME`_EVENT_BYTE0                (0x00u)
#define `$INSTANCE_NAME`_EVENT_BYTE1                (0x01u)
#define `$INSTANCE_NAME`_EVENT_BYTE2                (0x02u)
#define `$INSTANCE_NAME`_EVENT_BYTE3                (0x03u)
#define `$INSTANCE_NAME`_EVENT_LENGTH               (0x04u)

#define `$INSTANCE_NAME`_MIDI_STATUS_BYTE_MASK      (0x80u)
#define `$INSTANCE_NAME`_MIDI_STATUS_MASK           (0xF0u)
#define `$INSTANCE_NAME`_MIDI_SINGLE_BYTE_MASK      (0x08u)
#define `$INSTANCE_NAME`_MIDI_NOTE_OFF              (0x80u)
#define `$INSTANCE_NAME`_MIDI_NOTE_ON               (0x90u)
#define `$INSTANCE_NAME`_MIDI_POLY_KEY_PRESSURE     (0xA0u)
#define `$INSTANCE_NAME`_MIDI_CONTROL_CHANGE        (0xB0u)
#define `$INSTANCE_NAME`_MIDI_PROGRAM_CHANGE        (0xC0u)
#define `$INSTANCE_NAME`_MIDI_CHANNEL_PRESSURE      (0xD0u)
#define `$INSTANCE_NAME`_MIDI_PITCH_BEND_CHANGE     (0xE0u)
#define `$INSTANCE_NAME`_MIDI_SYSEX                 (0xF0u)
#define `$INSTANCE_NAME`_MIDI_EOSEX                 (0xF7u)
#define `$INSTANCE_NAME`_MIDI_QFM                   (0xF1u)
#define `$INSTANCE_NAME`_MIDI_SPP                   (0xF2u)
#define `$INSTANCE_NAME`_MIDI_SONGSEL               (0xF3u)
#define `$INSTANCE_NAME`_MIDI_TUNEREQ               (0xF6u)
#define `$INSTANCE_NAME`_MIDI_ACTIVESENSE           (0xFEu)

/* MIDI Universal System Exclusive defines */
#define `$INSTANCE_NAME`_MIDI_SYSEX_NON_REAL_TIME   (0x7Eu)
#define `$INSTANCE_NAME`_MIDI_SYSEX_REALTIME        (0x7Fu)

/* ID of target device */
#define `$INSTANCE_NAME`_MIDI_SYSEX_ID_ALL          (0x7Fu)

/* Sub-ID#1*/
#define `$INSTANCE_NAME`_MIDI_SYSEX_GEN_INFORMATION (0x06u)
#define `$INSTANCE_NAME`_MIDI_SYSEX_GEN_MESSAGE     (0x09u)

/* Sub-ID#2*/
#define `$INSTANCE_NAME`_MIDI_SYSEX_IDENTITY_REQ    (0x01u)
#define `$INSTANCE_NAME`_MIDI_SYSEX_IDENTITY_REPLY  (0x02u)
#define `$INSTANCE_NAME`_MIDI_SYSEX_SYSTEM_ON       (0x01u)
#define `$INSTANCE_NAME`_MIDI_SYSEX_SYSTEM_OFF      (0x02u)

/* UART TX and RX interrupt priority. */
#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_CUSTOM_UART_RX_PRIOR_NUM   (0x01u)
    #define `$INSTANCE_NAME`_CUSTOM_UART_TX_PRIOR_NUM   (0x02u)
#else
    #define `$INSTANCE_NAME`_CUSTOM_UART_RX_PRIOR_NUM   (0x02u)
    #define `$INSTANCE_NAME`_CUSTOM_UART_TX_PRIOR_NUM   (0x04u)
#endif /* (CYPSOC4) */


/***************************************
*    Private Function Prototypes
***************************************/

void `$INSTANCE_NAME`_PrepareInBuffer(uint8 ic, const uint8 srcBuff[], uint8 eventLen, uint8 cable)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_PrepareInBuffer")`;
#if (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_ONE_EXT_INTRF)
    void  `$INSTANCE_NAME`_MIDI_InitInterface(void)             `=ReentrantKeil($INSTANCE_NAME . "_MIDI_InitInterface")`;
    uint8 `$INSTANCE_NAME`_ProcessMidiIn(uint8 mData, `$INSTANCE_NAME`_MIDI_RX_STATUS *rxStat)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_ProcessMidiIn")`;
    uint8 `$INSTANCE_NAME`_MIDI1_GetEvent(void)                 `=ReentrantKeil($INSTANCE_NAME . "_MIDI1_GetEvent")`;
    void  `$INSTANCE_NAME`_MIDI1_ProcessUsbOut(const uint8 epBuf[])
                                                                `=ReentrantKeil($INSTANCE_NAME . "_MIDI1_ProcessUsbOut")`;

    #if (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_TWO_EXT_INTRF)
        uint8 `$INSTANCE_NAME`_MIDI2_GetEvent(void)             `=ReentrantKeil($INSTANCE_NAME . "_MIDI2_GetEvent")`;
        void  `$INSTANCE_NAME`_MIDI2_ProcessUsbOut(const uint8 epBuf[])
                                                                `=ReentrantKeil($INSTANCE_NAME . "_MIDI2_ProcessUsbOut")`;
    #endif /* (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_TWO_EXT_INTRF) */
#endif /* (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_ONE_EXT_INTRF) */


/***************************************
*     Vars with External Linkage
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING)

#if (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE > 0)
    #if (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE >= 256)
/**
* \addtogroup group_midi
* @{
*/  
        extern volatile uint16 `$INSTANCE_NAME`_midiInPointer;                       /* Input endpoint buffer pointer */
/** @} midi*/
    #else
        extern volatile uint8 `$INSTANCE_NAME`_midiInPointer;                        /* Input endpoint buffer pointer */
    #endif /* (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE >=256) */
/**
* \addtogroup group_midi
* @{
*/  
    extern volatile uint8 `$INSTANCE_NAME`_midi_in_ep;                               /* Input endpoint number */
    extern uint8 `$INSTANCE_NAME`_midiInBuffer[`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE];  /* Input endpoint buffer */
#endif /* (`$INSTANCE_NAME`_MIDI_IN_BUFF_SIZE > 0) */

#if (`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE > 0)
    extern volatile uint8 `$INSTANCE_NAME`_midi_out_ep;                               /* Output endpoint number */
    extern uint8 `$INSTANCE_NAME`_midiOutBuffer[`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE]; /* Output endpoint buffer */
#endif /* (`$INSTANCE_NAME`_MIDI_OUT_BUFF_SIZE > 0) */

#if (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_ONE_EXT_INTRF)
    extern volatile uint8 `$INSTANCE_NAME`_MIDI1_InqFlags;                            /* Device inquiry flag */
    
    #if (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_TWO_EXT_INTRF)
        extern volatile uint8 `$INSTANCE_NAME`_MIDI2_InqFlags;                        /* Device inquiry flag */
    #endif /* (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_TWO_EXT_INTRF) */
#endif /* (`$INSTANCE_NAME`_MIDI_EXT_MODE >= `$INSTANCE_NAME`_ONE_EXT_INTRF) */
/** @} midi */
#endif /* (`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define `$INSTANCE_NAME`_MIDI_EP_Init           `$INSTANCE_NAME`_MIDI_Init
#define `$INSTANCE_NAME`_MIDI_OUT_EP_Service    `$INSTANCE_NAME`_MIDI_OUT_Service

#endif /* (CY_USBFS_`$INSTANCE_NAME`_midi_H) */


/* [] END OF FILE */
