/***************************************************************************//**
* \file `$INSTANCE_NAME_pvt`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides private function prototypes and constants for the 
*  USBFS component. It is not intended to be used in the user project.
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_`$INSTANCE_NAME`_pvt_H)
#define CY_USBFS_`$INSTANCE_NAME`_pvt_H

#include "`$INSTANCE_NAME`.h"
   
#ifdef `$INSTANCE_NAME`_ENABLE_AUDIO_CLASS
    #include "`$INSTANCE_NAME`_audio.h"
#endif /* `$INSTANCE_NAME`_ENABLE_AUDIO_CLASS */

#ifdef `$INSTANCE_NAME`_ENABLE_CDC_CLASS
    #include "`$INSTANCE_NAME`_cdc.h"
#endif /* `$INSTANCE_NAME`_ENABLE_CDC_CLASS */

#if (`$INSTANCE_NAME`_ENABLE_MIDI_CLASS)
    #include "`$INSTANCE_NAME`_midi.h"
#endif /* (`$INSTANCE_NAME`_ENABLE_MIDI_CLASS) */

#if (`$INSTANCE_NAME`_ENABLE_MSC_CLASS)
    #include "`$INSTANCE_NAME`_msc.h"
#endif /* (`$INSTANCE_NAME`_ENABLE_MSC_CLASS) */

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        #include <CyDMA.h>
    #else
        #include <CyDmac.h>
        #if ((`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
            #include "`$INSTANCE_NAME`_EP_DMA_Done_isr.h"
            #include "`$INSTANCE_NAME`_EP8_DMA_Done_SR.h"
            #include "`$INSTANCE_NAME`_EP17_DMA_Done_SR.h"
        #endif /* ((`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)) */
    #endif /* (CY_PSOC4) */
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

#if (`$INSTANCE_NAME`_DMA1_ACTIVE)
    #include "`$INSTANCE_NAME`_ep1_dma.h"
    #define `$INSTANCE_NAME`_EP1_DMA_CH     (`$INSTANCE_NAME`_ep1_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA1_ACTIVE) */

#if (`$INSTANCE_NAME`_DMA2_ACTIVE)
    #include "`$INSTANCE_NAME`_ep2_dma.h"
    #define `$INSTANCE_NAME`_EP2_DMA_CH     (`$INSTANCE_NAME`_ep2_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA2_ACTIVE) */

#if (`$INSTANCE_NAME`_DMA3_ACTIVE)
    #include "`$INSTANCE_NAME`_ep3_dma.h"
    #define `$INSTANCE_NAME`_EP3_DMA_CH     (`$INSTANCE_NAME`_ep3_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA3_ACTIVE) */

#if (`$INSTANCE_NAME`_DMA4_ACTIVE)
    #include "`$INSTANCE_NAME`_ep4_dma.h"
    #define `$INSTANCE_NAME`_EP4_DMA_CH     (`$INSTANCE_NAME`_ep4_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA4_ACTIVE) */

#if (`$INSTANCE_NAME`_DMA5_ACTIVE)
    #include "`$INSTANCE_NAME`_ep5_dma.h"
    #define `$INSTANCE_NAME`_EP5_DMA_CH     (`$INSTANCE_NAME`_ep5_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA5_ACTIVE) */

#if (`$INSTANCE_NAME`_DMA6_ACTIVE)
    #include "`$INSTANCE_NAME`_ep6_dma.h"
    #define `$INSTANCE_NAME`_EP6_DMA_CH     (`$INSTANCE_NAME`_ep6_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA6_ACTIVE) */

#if (`$INSTANCE_NAME`_DMA7_ACTIVE)
    #include "`$INSTANCE_NAME`_ep7_dma.h"
    #define `$INSTANCE_NAME`_EP7_DMA_CH     (`$INSTANCE_NAME`_ep7_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA7_ACTIVE) */

#if (`$INSTANCE_NAME`_DMA8_ACTIVE)
    #include "`$INSTANCE_NAME`_ep8_dma.h"
    #define `$INSTANCE_NAME`_EP8_DMA_CH     (`$INSTANCE_NAME`_ep8_dma_CHANNEL)
#endif /* (`$INSTANCE_NAME`_DMA8_ACTIVE) */


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors. */
`$APIGEN_FUNCDECL`

extern const uint8 CYCODE `$INSTANCE_NAME`_MSOS_DESCRIPTOR[`$INSTANCE_NAME`_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE `$INSTANCE_NAME`_MSOS_CONFIGURATION_DESCR[`$INSTANCE_NAME`_MSOS_CONF_DESCR_LENGTH];
#if defined(`$INSTANCE_NAME`_ENABLE_IDSN_STRING)
    extern uint8 `$INSTANCE_NAME`_idSerialNumberStringDescriptor[`$INSTANCE_NAME`_IDSN_DESCR_LENGTH];
#endif /* (`$INSTANCE_NAME`_ENABLE_IDSN_STRING) */

extern volatile uint8 `$INSTANCE_NAME`_interfaceNumber;
extern volatile uint8 `$INSTANCE_NAME`_interfaceSetting[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
extern volatile uint8 `$INSTANCE_NAME`_interfaceSettingLast[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
extern volatile uint8 `$INSTANCE_NAME`_deviceAddress;
extern volatile uint8 `$INSTANCE_NAME`_interfaceStatus[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *`$INSTANCE_NAME`_interfaceClass;

extern volatile T_`$INSTANCE_NAME`_EP_CTL_BLOCK `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_MAX_EP];
extern volatile T_`$INSTANCE_NAME`_TD `$INSTANCE_NAME`_currentTD;

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        extern const uint8 `$INSTANCE_NAME`_DmaChan[`$INSTANCE_NAME`_MAX_EP];
    #else
        extern uint8 `$INSTANCE_NAME`_DmaChan[`$INSTANCE_NAME`_MAX_EP];
        extern uint8 `$INSTANCE_NAME`_DmaTd  [`$INSTANCE_NAME`_MAX_EP];
    #endif /* (CY_PSOC4) */
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    extern uint8  `$INSTANCE_NAME`_DmaEpBurstCnt   [`$INSTANCE_NAME`_MAX_EP];
    extern uint8  `$INSTANCE_NAME`_DmaEpLastBurstEl[`$INSTANCE_NAME`_MAX_EP];

    extern uint8  `$INSTANCE_NAME`_DmaEpBurstCntBackup  [`$INSTANCE_NAME`_MAX_EP];
    extern uint32 `$INSTANCE_NAME`_DmaEpBufferAddrBackup[`$INSTANCE_NAME`_MAX_EP];
    
    extern const uint8 `$INSTANCE_NAME`_DmaReqOut     [`$INSTANCE_NAME`_MAX_EP];    
    extern const uint8 `$INSTANCE_NAME`_DmaBurstEndOut[`$INSTANCE_NAME`_MAX_EP];
#else
    #if (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)
        extern uint8 `$INSTANCE_NAME`_DmaNextTd[`$INSTANCE_NAME`_MAX_EP];
        extern volatile uint16 `$INSTANCE_NAME`_inLength [`$INSTANCE_NAME`_MAX_EP];
        extern volatile uint8  `$INSTANCE_NAME`_inBufFull[`$INSTANCE_NAME`_MAX_EP];
        extern const uint8 `$INSTANCE_NAME`_epX_TD_TERMOUT_EN[`$INSTANCE_NAME`_MAX_EP];
        extern const uint8 *`$INSTANCE_NAME`_inDataPointer[`$INSTANCE_NAME`_MAX_EP];
    #endif /* (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u) */
#endif /* CY_PSOC4 */
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */

extern volatile uint8 `$INSTANCE_NAME`_ep0Toggle;
extern volatile uint8 `$INSTANCE_NAME`_lastPacketSize;
extern volatile uint8 `$INSTANCE_NAME`_ep0Mode;
extern volatile uint8 `$INSTANCE_NAME`_ep0Count;
extern volatile uint16 `$INSTANCE_NAME`_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  `$INSTANCE_NAME`_ReInitComponent(void)            `=ReentrantKeil($INSTANCE_NAME . "_ReInitComponent")`;
void  `$INSTANCE_NAME`_HandleSetup(void)                `=ReentrantKeil($INSTANCE_NAME . "_HandleSetup")`;
void  `$INSTANCE_NAME`_HandleIN(void)                   `=ReentrantKeil($INSTANCE_NAME . "_HandleIN")`;
void  `$INSTANCE_NAME`_HandleOUT(void)                  `=ReentrantKeil($INSTANCE_NAME . "_HandleOUT")`;
void  `$INSTANCE_NAME`_LoadEP0(void)                    `=ReentrantKeil($INSTANCE_NAME . "_LoadEP0")`;
uint8 `$INSTANCE_NAME`_InitControlRead(void)            `=ReentrantKeil($INSTANCE_NAME . "_InitControlRead")`;
uint8 `$INSTANCE_NAME`_InitControlWrite(void)           `=ReentrantKeil($INSTANCE_NAME . "_InitControlWrite")`;
void  `$INSTANCE_NAME`_ControlReadDataStage(void)       `=ReentrantKeil($INSTANCE_NAME . "_ControlReadDataStage")`;
void  `$INSTANCE_NAME`_ControlReadStatusStage(void)     `=ReentrantKeil($INSTANCE_NAME . "_ControlReadStatusStage")`;
void  `$INSTANCE_NAME`_ControlReadPrematureStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlReadPrematureStatus")`;
uint8 `$INSTANCE_NAME`_InitControlWrite(void)           `=ReentrantKeil($INSTANCE_NAME . "_InitControlWrite")`;
uint8 `$INSTANCE_NAME`_InitZeroLengthControlTransfer(void) `=ReentrantKeil($INSTANCE_NAME . "_InitZeroLengthControlTransfer")`;
void  `$INSTANCE_NAME`_ControlWriteDataStage(void)      `=ReentrantKeil($INSTANCE_NAME . "_ControlWriteDataStage")`;
void  `$INSTANCE_NAME`_ControlWriteStatusStage(void)    `=ReentrantKeil($INSTANCE_NAME . "_ControlWriteStatusStage")`;
void  `$INSTANCE_NAME`_ControlWritePrematureStatus(void)`=ReentrantKeil($INSTANCE_NAME . "_ControlWritePrematureStatus")`;
uint8 `$INSTANCE_NAME`_InitNoDataControlTransfer(void)  `=ReentrantKeil($INSTANCE_NAME . "_InitNoDataControlTransfer")`;
void  `$INSTANCE_NAME`_NoDataControlStatusStage(void)   `=ReentrantKeil($INSTANCE_NAME . "_NoDataControlStatusStage")`;
void  `$INSTANCE_NAME`_InitializeStatusBlock(void)      `=ReentrantKeil($INSTANCE_NAME . "_InitializeStatusBlock")`;
void  `$INSTANCE_NAME`_UpdateStatusBlock(uint8 completionCode) `=ReentrantKeil($INSTANCE_NAME . "_UpdateStatusBlock")`;
uint8 `$INSTANCE_NAME`_DispatchClassRqst(void)          `=ReentrantKeil($INSTANCE_NAME . "_DispatchClassRqst")`;

void `$INSTANCE_NAME`_Config(uint8 clearAltSetting) `=ReentrantKeil($INSTANCE_NAME . "_Config")`;
void `$INSTANCE_NAME`_ConfigAltChanged(void)        `=ReentrantKeil($INSTANCE_NAME . "_ConfigAltChanged")`;
void `$INSTANCE_NAME`_ConfigReg(void)               `=ReentrantKeil($INSTANCE_NAME . "_ConfigReg")`;
void `$INSTANCE_NAME`_EpStateInit(void)             `=ReentrantKeil($INSTANCE_NAME . "_EpStateInit")`;


const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetConfigTablePtr(uint8 confIndex)`=ReentrantKeil($INSTANCE_NAME . "_GetConfigTablePtr")`;
const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetDeviceTablePtr(void)           `=ReentrantKeil($INSTANCE_NAME . "_GetDeviceTablePtr")`;
#if (`$INSTANCE_NAME`_BOS_ENABLE)
    const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetBOSPtr(void)               `=ReentrantKeil($INSTANCE_NAME . "_GetBOSPtr")`;
#endif /* (`$INSTANCE_NAME`_BOS_ENABLE) */
const uint8 CYCODE *`$INSTANCE_NAME`_GetInterfaceClassTablePtr(void)                    `=ReentrantKeil($INSTANCE_NAME . "_GetInterfaceClassTablePtr")`;
uint8 `$INSTANCE_NAME`_ClearEndpointHalt(void)                                          `=ReentrantKeil($INSTANCE_NAME . "_ClearEndpointHalt")`;
uint8 `$INSTANCE_NAME`_SetEndpointHalt(void)                                            `=ReentrantKeil($INSTANCE_NAME . "_SetEndpointHalt")`;
uint8 `$INSTANCE_NAME`_ValidateAlternateSetting(void)                                   `=ReentrantKeil($INSTANCE_NAME . "_ValidateAlternateSetting")`;

void `$INSTANCE_NAME`_SaveConfig(void)      `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void)   `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;

#if (CY_PSOC3 || CY_PSOC5LP)
    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
        void `$INSTANCE_NAME`_LoadNextInEP(uint8 epNumber, uint8 mode)  `=ReentrantKeil($INSTANCE_NAME . "_LoadNextInEP")`;
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)) */
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if defined(`$INSTANCE_NAME`_ENABLE_IDSN_STRING)
    void `$INSTANCE_NAME`_ReadDieID(uint8 descr[])  `=ReentrantKeil($INSTANCE_NAME . "_ReadDieID")`;
#endif /* `$INSTANCE_NAME`_ENABLE_IDSN_STRING */

#if defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS)
    uint8 `$INSTANCE_NAME`_DispatchHIDClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchHIDClassRqst")`;
#endif /* (`$INSTANCE_NAME`_ENABLE_HID_CLASS) */

#if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_CLASS)
    uint8 `$INSTANCE_NAME`_DispatchAUDIOClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchAUDIOClassRqst")`;
#endif /* (`$INSTANCE_NAME`_ENABLE_AUDIO_CLASS) */

#if defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS)
    uint8 `$INSTANCE_NAME`_DispatchCDCClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchCDCClassRqst")`;
#endif /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS) */

#if (`$INSTANCE_NAME`_ENABLE_MSC_CLASS)
    #if (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS)
        uint8 `$INSTANCE_NAME`_DispatchMSCClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchMSCClassRqst")`;
    #endif /* (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS) */
#endif /* (`$INSTANCE_NAME`_ENABLE_MSC_CLASS */

CY_ISR_PROTO(`$INSTANCE_NAME`_EP_0_ISR);
CY_ISR_PROTO(`$INSTANCE_NAME`_BUS_RESET_ISR);

#if (`$INSTANCE_NAME`_SOF_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_SOF_ISR);
#endif /* (`$INSTANCE_NAME`_SOF_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP1_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_1_ISR);
#endif /* (`$INSTANCE_NAME`_EP1_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP2_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_2_ISR);
#endif /* (`$INSTANCE_NAME`_EP2_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP3_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_3_ISR);
#endif /* (`$INSTANCE_NAME`_EP3_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP4_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_4_ISR);
#endif /* (`$INSTANCE_NAME`_EP4_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP5_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_5_ISR);
#endif /* (`$INSTANCE_NAME`_EP5_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP6_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_6_ISR);
#endif /* (`$INSTANCE_NAME`_EP6_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP7_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_7_ISR);
#endif /* (`$INSTANCE_NAME`_EP7_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP8_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_8_ISR);
#endif /* (`$INSTANCE_NAME`_EP8_ISR_ACTIVE) */

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
    CY_ISR_PROTO(`$INSTANCE_NAME`_ARB_ISR);
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

#if (`$INSTANCE_NAME`_DP_ISR_ACTIVE)
    CY_ISR_PROTO(`$INSTANCE_NAME`_DP_ISR);
#endif /* (`$INSTANCE_NAME`_DP_ISR_ACTIVE) */

#if (CY_PSOC4)
    CY_ISR_PROTO(`$INSTANCE_NAME`_INTR_HI_ISR);
    CY_ISR_PROTO(`$INSTANCE_NAME`_INTR_MED_ISR);
    CY_ISR_PROTO(`$INSTANCE_NAME`_INTR_LO_ISR);
    #if (`$INSTANCE_NAME`_LPM_ACTIVE)
        CY_ISR_PROTO(`$INSTANCE_NAME`_LPM_ISR);
    #endif /* (`$INSTANCE_NAME`_LPM_ACTIVE) */
#endif /* (CY_PSOC4) */

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    #if (`$INSTANCE_NAME`_DMA1_ACTIVE)
        void `$INSTANCE_NAME`_EP1_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA1_ACTIVE) */

    #if (`$INSTANCE_NAME`_DMA2_ACTIVE)
        void `$INSTANCE_NAME`_EP2_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA2_ACTIVE) */

    #if (`$INSTANCE_NAME`_DMA3_ACTIVE)
        void `$INSTANCE_NAME`_EP3_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA3_ACTIVE) */

    #if (`$INSTANCE_NAME`_DMA4_ACTIVE)
        void `$INSTANCE_NAME`_EP4_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA4_ACTIVE) */

    #if (`$INSTANCE_NAME`_DMA5_ACTIVE)
        void `$INSTANCE_NAME`_EP5_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA5_ACTIVE) */

    #if (`$INSTANCE_NAME`_DMA6_ACTIVE)
        void `$INSTANCE_NAME`_EP6_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA6_ACTIVE) */

    #if (`$INSTANCE_NAME`_DMA7_ACTIVE)
        void `$INSTANCE_NAME`_EP7_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA7_ACTIVE) */

    #if (`$INSTANCE_NAME`_DMA8_ACTIVE)
        void `$INSTANCE_NAME`_EP8_DMA_DONE_ISR(void);
    #endif /* (`$INSTANCE_NAME`_DMA8_ACTIVE) */

#else
    #if (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)
        CY_ISR_PROTO(`$INSTANCE_NAME`_EP_DMA_DONE_ISR);
    #endif /* (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */


/***************************************
*         Request Handlers
***************************************/

uint8 `$INSTANCE_NAME`_HandleStandardRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleStandardRqst")`;
uint8 `$INSTANCE_NAME`_DispatchClassRqst(void)  `=ReentrantKeil($INSTANCE_NAME . "_DispatchClassRqst")`;
uint8 `$INSTANCE_NAME`_HandleVendorRqst(void)   `=ReentrantKeil($INSTANCE_NAME . "_HandleVendorRqst")`;


/***************************************
*    HID Internal references
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS)
    void `$INSTANCE_NAME`_FindReport(void)            `=ReentrantKeil($INSTANCE_NAME . "_FindReport")`;
    void `$INSTANCE_NAME`_FindReportDescriptor(void)  `=ReentrantKeil($INSTANCE_NAME . "_FindReportDescriptor")`;
    void `$INSTANCE_NAME`_FindHidClassDecriptor(void) `=ReentrantKeil($INSTANCE_NAME . "_FindHidClassDecriptor")`;
#endif /* `$INSTANCE_NAME`_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING)
    void `$INSTANCE_NAME`_MIDI_IN_EP_Service(void)  `=ReentrantKeil($INSTANCE_NAME . "_MIDI_IN_EP_Service")`;
#endif /* (`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) */


/***************************************
*    CDC Internal references
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS)

    typedef struct
    {
        uint8  bRequestType;
        uint8  bNotification;
        uint8  wValue;
        uint8  wValueMSB;
        uint8  wIndex;
        uint8  wIndexMSB;
        uint8  wLength;
        uint8  wLengthMSB;
        uint8  wSerialState;
        uint8  wSerialStateMSB;
    } t_`$INSTANCE_NAME`_cdc_notification;

    uint8 `$INSTANCE_NAME`_GetInterfaceComPort(uint8 interface) `=ReentrantKeil($INSTANCE_NAME . "_GetInterfaceComPort")`;
    uint8 `$INSTANCE_NAME`_Cdc_EpInit( const T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) `=ReentrantKeil($INSTANCE_NAME . "_ConfigAltChanged")`;

    extern volatile uint8  `$INSTANCE_NAME`_cdc_dataInEpList[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
    extern volatile uint8  `$INSTANCE_NAME`_cdc_dataOutEpList[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
    extern volatile uint8  `$INSTANCE_NAME`_cdc_commInEpList[`$INSTANCE_NAME`_MAX_MULTI_COM_NUM];
#endif /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS) */


#endif /* CY_USBFS_`$INSTANCE_NAME`_pvt_H */


/* [] END OF FILE */
