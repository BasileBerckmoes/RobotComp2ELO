/***************************************************************************//**
* \file  `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides function prototypes and constants for the USBFS component. 
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_`$INSTANCE_NAME`_H)
#define CY_USBFS_`$INSTANCE_NAME`_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/*  User supplied definitions. */
/* `#START USER_DEFINITIONS` Place your declaration here */

/* `#END` */

/***************************************
* Enumerated Types and Parameters
***************************************/

/* USB IP memory management options. */
#define `$INSTANCE_NAME`__EP_MANUAL    (0u)
#define `$INSTANCE_NAME`__EP_DMAMANUAL (1u)
#define `$INSTANCE_NAME`__EP_DMAAUTO   (2u)

/* USB IP memory allocation options. */
#define `$INSTANCE_NAME`__MA_STATIC    (0u)
#define `$INSTANCE_NAME`__MA_DYNAMIC   (1u)


/***************************************
*    Initial Parameter Constants
***************************************/

`$APIGEN_DEFINES`
#define `$INSTANCE_NAME`_MON_VBUS               (`$mon_vbus`u)
#define `$INSTANCE_NAME`_EXTERN_VBUS            (`$extern_vbus`u)
#define `$INSTANCE_NAME`_POWER_PAD_VBUS         (`$powerpad_vbus`u)
#define `$INSTANCE_NAME`_EXTERN_VND             (`$extern_vnd`u)
#define `$INSTANCE_NAME`_EXTERN_CLS             (`$extern_cls`u)
#define `$INSTANCE_NAME`_MAX_INTERFACES_NUMBER  (`$max_interfaces_num`u)
#define `$INSTANCE_NAME`_EP_MM                  (`$endpointMM`u)
#define `$INSTANCE_NAME`_EP_MA                  (`$endpointMA`u)
#define `$INSTANCE_NAME`_ENABLE_BATT_CHARG_DET  (`$EnableBatteryChargDetect`u)
#define `$INSTANCE_NAME`_GEN_16BITS_EP_ACCESS   (`$Gen16bitEpAccessApi`u)

/* Enable Class APIs: MIDI, CDC, MSC. */         
#define `$INSTANCE_NAME`_ENABLE_CDC_CLASS_API   (0u != (`$EnableCDCApi`u))

/* General parameters */
#define `$INSTANCE_NAME`_EP_ALLOC_STATIC            (`$INSTANCE_NAME`_EP_MA == `$INSTANCE_NAME`__MA_STATIC)
#define `$INSTANCE_NAME`_EP_ALLOC_DYNAMIC           (`$INSTANCE_NAME`_EP_MA == `$INSTANCE_NAME`__MA_DYNAMIC)
#define `$INSTANCE_NAME`_EP_MANAGEMENT_MANUAL       (`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_MANUAL)
#define `$INSTANCE_NAME`_EP_MANAGEMENT_DMA          (`$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL)
#define `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL   (`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAMANUAL)
#define `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO     (`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO)
#define `$INSTANCE_NAME`_BATT_CHARG_DET_ENABLE      (CY_PSOC4 && (0u != `$INSTANCE_NAME`_ENABLE_BATT_CHARG_DET))
#define `$INSTANCE_NAME`_16BITS_EP_ACCESS_ENABLE    (CY_PSOC4 && (0u != `$INSTANCE_NAME`_GEN_16BITS_EP_ACCESS))
#define `$INSTANCE_NAME`_VBUS_MONITORING_ENABLE     (0u != `$INSTANCE_NAME`_MON_VBUS)
#define `$INSTANCE_NAME`_VBUS_MONITORING_INTERNAL   (0u == `$INSTANCE_NAME`_EXTERN_VBUS)
#define `$INSTANCE_NAME`_VBUS_POWER_PAD_ENABLE      (0u != `$INSTANCE_NAME`_POWER_PAD_VBUS)

/* Control endpoints availability */
#define `$INSTANCE_NAME`_SOF_ISR_REMOVE       (`$rm_sof_int`u)
#define `$INSTANCE_NAME`_BUS_RESET_ISR_REMOVE (`$rm_usb_int`u)
#define `$INSTANCE_NAME`_EP0_ISR_REMOVE       (`$rm_ep_isr_0`u)
#define `$INSTANCE_NAME`_ARB_ISR_REMOVE       (`$rm_arb_int`u)
#define `$INSTANCE_NAME`_DP_ISR_REMOVE        (`$rm_dp_int`u)
#define `$INSTANCE_NAME`_LPM_REMOVE           (`$rm_lpm_int`u)
#define `$INSTANCE_NAME`_SOF_ISR_ACTIVE       ((0u == `$INSTANCE_NAME`_SOF_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_BUS_RESET_ISR_ACTIVE ((0u == `$INSTANCE_NAME`_BUS_RESET_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP0_ISR_ACTIVE       ((0u == `$INSTANCE_NAME`_EP0_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_ARB_ISR_ACTIVE       ((0u == `$INSTANCE_NAME`_ARB_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DP_ISR_ACTIVE        ((0u == `$INSTANCE_NAME`_DP_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_LPM_ACTIVE           ((CY_PSOC4 && (0u == `$INSTANCE_NAME`_LPM_REMOVE)) ? 1u: 0u)

/* Data endpoints availability */
#define `$INSTANCE_NAME`_EP1_ISR_REMOVE     (`$rm_ep_isr_1`u)
#define `$INSTANCE_NAME`_EP2_ISR_REMOVE     (`$rm_ep_isr_2`u)
#define `$INSTANCE_NAME`_EP3_ISR_REMOVE     (`$rm_ep_isr_3`u)
#define `$INSTANCE_NAME`_EP4_ISR_REMOVE     (`$rm_ep_isr_4`u)
#define `$INSTANCE_NAME`_EP5_ISR_REMOVE     (`$rm_ep_isr_5`u)
#define `$INSTANCE_NAME`_EP6_ISR_REMOVE     (`$rm_ep_isr_6`u)
#define `$INSTANCE_NAME`_EP7_ISR_REMOVE     (`$rm_ep_isr_7`u)
#define `$INSTANCE_NAME`_EP8_ISR_REMOVE     (`$rm_ep_isr_8`u)
#define `$INSTANCE_NAME`_EP1_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP1_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP2_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP2_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP3_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP3_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP4_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP4_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP5_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP5_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP6_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP6_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP7_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP7_ISR_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_EP8_ISR_ACTIVE     ((0u == `$INSTANCE_NAME`_EP8_ISR_REMOVE) ? 1u: 0u)

#define `$INSTANCE_NAME`_EP_DMA_AUTO_OPT    ((CY_PSOC4) ? (1u) : (`$epDMAautoOptimization`u))
#define `$INSTANCE_NAME`_DMA1_REMOVE        (`$rm_dma_1`u)
#define `$INSTANCE_NAME`_DMA2_REMOVE        (`$rm_dma_2`u)
#define `$INSTANCE_NAME`_DMA3_REMOVE        (`$rm_dma_3`u)
#define `$INSTANCE_NAME`_DMA4_REMOVE        (`$rm_dma_4`u)
#define `$INSTANCE_NAME`_DMA5_REMOVE        (`$rm_dma_5`u)
#define `$INSTANCE_NAME`_DMA6_REMOVE        (`$rm_dma_6`u)
#define `$INSTANCE_NAME`_DMA7_REMOVE        (`$rm_dma_7`u)
#define `$INSTANCE_NAME`_DMA8_REMOVE        (`$rm_dma_8`u)
#define `$INSTANCE_NAME`_DMA1_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA1_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DMA2_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA2_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DMA3_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA3_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DMA4_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA4_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DMA5_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA5_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DMA6_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA6_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DMA7_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA7_REMOVE) ? 1u: 0u)
#define `$INSTANCE_NAME`_DMA8_ACTIVE        ((0u == `$INSTANCE_NAME`_DMA8_REMOVE) ? 1u: 0u)


/***************************************
*    Data Structures Definition
***************************************/

typedef struct
{
    uint8  attrib;
    uint8  apiEpState;
    uint8  hwEpState;
    uint8  epToggle;
    uint8  addr;
    uint8  epMode;
    uint16 buffOffset;
    uint16 bufferSize;
    uint8  interface;
} T_`$INSTANCE_NAME`_EP_CTL_BLOCK;

typedef struct
{
    uint8  interface;
    uint8  altSetting;
    uint8  addr;
    uint8  attributes;
    uint16 bufferSize;
    uint8  bMisc;
} T_`$INSTANCE_NAME`_EP_SETTINGS_BLOCK;

typedef struct
{
    uint8  status;
    uint16 length;
} T_`$INSTANCE_NAME`_XFER_STATUS_BLOCK;

typedef struct
{
    uint16  count;
    volatile uint8 *pData;
    T_`$INSTANCE_NAME`_XFER_STATUS_BLOCK *pStatusBlock;
} T_`$INSTANCE_NAME`_TD;

typedef struct
{
    uint8   c;
    const void *p_list;
} T_`$INSTANCE_NAME`_LUT;

/* Resume/Suspend API Support */
typedef struct
{
    uint8 enableState;
    uint8 mode;
#if (CY_PSOC4)
    uint8 intrSeiMask;
#endif /* (CY_PSOC4) */
} `$INSTANCE_NAME`_BACKUP_STRUCT;

/* Number of endpoint 0 data registers. */
#define `$INSTANCE_NAME`_EP0_DR_MAPPED_REG_CNT  (8u)

/* Structure to access data registers for EP0. */
typedef struct
{
    `$UINT_TYPE` epData[`$INSTANCE_NAME`_EP0_DR_MAPPED_REG_CNT];
} `$INSTANCE_NAME`_ep0_data_struct;

/* Number of SIE endpoint registers group. */
#define `$INSTANCE_NAME`_SIE_EP_REG_SIZE   (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CR0 - \
                                            `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT0)

/* Size of gap between SIE endpoint registers groups. */
#define `$INSTANCE_NAME`_SIE_GAP_CNT        (((`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP2_CNT0 - \
                                             (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT0 + \
                                              `$INSTANCE_NAME`_SIE_EP_REG_SIZE)) / sizeof(`$REG_SIZE`)) - 1u)

/* Structure to access to SIE registers for endpoint. */
typedef struct
{
    `$UINT_TYPE` epCnt0;
    `$UINT_TYPE` epCnt1;
    `$UINT_TYPE` epCr0;
    `$UINT_TYPE` gap[`$INSTANCE_NAME`_SIE_GAP_CNT];
} `$INSTANCE_NAME`_sie_ep_struct;

/* Number of ARB endpoint registers group. */
#define `$INSTANCE_NAME`_ARB_EP_REG_SIZE    (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_DR - \
                                             `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_CFG)

/* Size of gap between ARB endpoint registers groups. */
#define `$INSTANCE_NAME`_ARB_GAP_CNT        (((`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP2_CFG - \
                                             (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_CFG + \
                                              `$INSTANCE_NAME`_ARB_EP_REG_SIZE)) / sizeof(`$REG_SIZE`)) - 1u)

/* Structure to access to ARB registers for endpoint. */
typedef struct
{
    `$UINT_TYPE` epCfg;
    `$UINT_TYPE` epIntEn;
    `$UINT_TYPE` epSr;
    `$UINT_TYPE` reserved;
    `$UINT_TYPE` rwWa;
    `$UINT_TYPE` rwWaMsb;
    `$UINT_TYPE` rwRa;
    `$UINT_TYPE` rwRaMsb;
    `$UINT_TYPE` rwDr;
    `$UINT_TYPE` gap[`$INSTANCE_NAME`_ARB_GAP_CNT];
} `$INSTANCE_NAME`_arb_ep_struct;

#if (CY_PSOC4)
    /* Number of ARB endpoint registers group (16-bits access). */
    #define `$INSTANCE_NAME`_ARB_EP_REG16_SIZE      (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_DR16 - \
                                                     `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_WA16)

    /* Size of gap between ARB endpoint registers groups (16-bits access). */
    #define `$INSTANCE_NAME`_ARB_EP_REG16_GAP_CNT   (((`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW2_WA16 - \
                                                     (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_WA16 + \
                                                      `$INSTANCE_NAME`_ARB_EP_REG16_SIZE)) / sizeof(`$REG_SIZE`)) - 1u)

    /* Structure to access to ARB registers for endpoint (16-bits access). */
    typedef struct
    {
        `$UINT_TYPE` rwWa16;
        `$UINT_TYPE` reserved0;
        `$UINT_TYPE` rwRa16;
        `$UINT_TYPE` reserved1;
        `$UINT_TYPE` rwDr16;
        `$UINT_TYPE` gap[`$INSTANCE_NAME`_ARB_EP_REG16_GAP_CNT];
    } `$INSTANCE_NAME`_arb_ep_reg16_struct;
#endif /* (CY_PSOC4) */

/* Number of endpoint (takes to account that endpoints numbers are 1-8). */
#define `$INSTANCE_NAME`_NUMBER_EP  (9u)

/* Consoled SIE register groups for endpoints 1-8. */
typedef struct
{
    `$INSTANCE_NAME`_sie_ep_struct sieEp[`$INSTANCE_NAME`_NUMBER_EP];
} `$INSTANCE_NAME`_sie_eps_struct;

/* Consolidate ARB register groups for endpoints 1-8.*/
typedef struct
{
    `$INSTANCE_NAME`_arb_ep_struct arbEp[`$INSTANCE_NAME`_NUMBER_EP];
} `$INSTANCE_NAME`_arb_eps_struct;

#if (CY_PSOC4)
    /* Consolidate ARB register groups for endpoints 1-8 (16-bits access). */
    typedef struct
    {
        `$INSTANCE_NAME`_arb_ep_reg16_struct arbEp[`$INSTANCE_NAME`_NUMBER_EP];
    } `$INSTANCE_NAME`_arb_eps_reg16_struct;
#endif /* (CY_PSOC4) */


/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
void   `$INSTANCE_NAME`_InitComponent(uint8 device, uint8 mode) `=ReentrantKeil($INSTANCE_NAME . "_InitComponent")`;
void   `$INSTANCE_NAME`_Start(uint8 device, uint8 mode)         `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void   `$INSTANCE_NAME`_Init(void)                              `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void   `$INSTANCE_NAME`_Stop(void)                              `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
uint8  `$INSTANCE_NAME`_GetConfiguration(void)                  `=ReentrantKeil($INSTANCE_NAME . "_GetConfiguration")`;
uint8  `$INSTANCE_NAME`_IsConfigurationChanged(void)            `=ReentrantKeil($INSTANCE_NAME . "_IsConfigurationChanged")`;
uint8  `$INSTANCE_NAME`_GetInterfaceSetting(uint8 interfaceNumber) `=ReentrantKeil($INSTANCE_NAME . "_GetInterfaceSetting")`;
uint8  `$INSTANCE_NAME`_GetEPState(uint8 epNumber)              `=ReentrantKeil($INSTANCE_NAME . "_GetEPState")`;
uint16 `$INSTANCE_NAME`_GetEPCount(uint8 epNumber)              `=ReentrantKeil($INSTANCE_NAME . "_GetEPCount")`;
void   `$INSTANCE_NAME`_LoadInEP(uint8 epNumber, const uint8 pData[], uint16 length)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_LoadInEP")`;
uint16 `$INSTANCE_NAME`_ReadOutEP(uint8 epNumber, uint8 pData[], uint16 length)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_ReadOutEP")`;
void   `$INSTANCE_NAME`_EnableOutEP(uint8 epNumber)             `=ReentrantKeil($INSTANCE_NAME . "_EnableOutEP")`;
void   `$INSTANCE_NAME`_DisableOutEP(uint8 epNumber)            `=ReentrantKeil($INSTANCE_NAME . "_DisableOutEP")`;
void   `$INSTANCE_NAME`_Force(uint8 bState)                     `=ReentrantKeil($INSTANCE_NAME . "_Force")`;
uint8  `$INSTANCE_NAME`_GetEPAckState(uint8 epNumber)           `=ReentrantKeil($INSTANCE_NAME . "_GetEPAckState")`;
void   `$INSTANCE_NAME`_SetPowerStatus(uint8 powerStatus)       `=ReentrantKeil($INSTANCE_NAME . "_SetPowerStatus")`;
void   `$INSTANCE_NAME`_TerminateEP(uint8 epNumber)             `=ReentrantKeil($INSTANCE_NAME . "_TerminateEP")`;

uint8 `$INSTANCE_NAME`_GetDeviceAddress(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDeviceAddress")`;

void `$INSTANCE_NAME`_EnableSofInt(void)  `=ReentrantKeil($INSTANCE_NAME . "_EnableSofInt")`;
void `$INSTANCE_NAME`_DisableSofInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableSofInt")`;


#if defined(`$INSTANCE_NAME`_ENABLE_FWSN_STRING)
    void   `$INSTANCE_NAME`_SerialNumString(uint8 snString[]) `=ReentrantKeil($INSTANCE_NAME . "_SerialNumString")`;
#endif  /* `$INSTANCE_NAME`_ENABLE_FWSN_STRING */

#if (`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE)
    uint8  `$INSTANCE_NAME`_VBusPresent(void) `=ReentrantKeil($INSTANCE_NAME . "_VBusPresent")`;
#endif /*  (`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE) */

#if (`$INSTANCE_NAME`_16BITS_EP_ACCESS_ENABLE)
    /* PSoC4 specific functions for 16-bit data register access. */
    void   `$INSTANCE_NAME`_LoadInEP16 (uint8 epNumber, const uint8 pData[], uint16 length);
    uint16 `$INSTANCE_NAME`_ReadOutEP16(uint8 epNumber,       uint8 pData[], uint16 length);
#endif /* (`$INSTANCE_NAME`_16BITS_EP_ACCESS_ENABLE) */

#if (`$INSTANCE_NAME`_BATT_CHARG_DET_ENABLE)
        uint8 `$INSTANCE_NAME`_Bcd_DetectPortType(void);
#endif /* (`$INSTANCE_NAME`_BATT_CHARG_DET_ENABLE) */

#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
    void `$INSTANCE_NAME`_InitEP_DMA(uint8 epNumber, const uint8 *pData) `=ReentrantKeil($INSTANCE_NAME . "_InitEP_DMA")`;   
    void `$INSTANCE_NAME`_Stop_DMA(uint8 epNumber) `=ReentrantKeil($INSTANCE_NAME . "_Stop_DMA")`;
/** @} general */ 
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

/**
* \addtogroup group_power
* @{
*/
uint8  `$INSTANCE_NAME`_CheckActivity(void) `=ReentrantKeil($INSTANCE_NAME . "_CheckActivity")`;
void   `$INSTANCE_NAME`_Suspend(void)       `=ReentrantKeil($INSTANCE_NAME . "_Suspend")`;
void   `$INSTANCE_NAME`_Resume(void)        `=ReentrantKeil($INSTANCE_NAME . "_Resume")`;
uint8  `$INSTANCE_NAME`_RWUEnabled(void)    `=ReentrantKeil($INSTANCE_NAME . "_RWUEnabled")`;

#if (`$INSTANCE_NAME`_LPM_ACTIVE)
    uint32 `$INSTANCE_NAME`_Lpm_GetBeslValue(void);
    uint32 `$INSTANCE_NAME`_Lpm_RemoteWakeUpAllowed(void);
    void   `$INSTANCE_NAME`_Lpm_SetResponse(uint32 response);
    uint32 `$INSTANCE_NAME`_Lpm_GetResponse(void);
#endif /* (`$INSTANCE_NAME`_LPM_ACTIVE) */

/** @} power */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
/**
* \addtogroup group_bootloader
* @{
*/
    void `$INSTANCE_NAME`_CyBtldrCommStart(void)        `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStart")`;
    void `$INSTANCE_NAME`_CyBtldrCommStop(void)         `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStop")`;
    void `$INSTANCE_NAME`_CyBtldrCommReset(void)        `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommReset")`;
    cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommWrite")`;
    cystatus `$INSTANCE_NAME`_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommRead")`;
/** @} bootloader */

    #define `$INSTANCE_NAME`_BTLDR_OUT_EP   (0x01u)
    #define `$INSTANCE_NAME`_BTLDR_IN_EP    (0x02u)

    #define `$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER  (64u)   /* Endpoint 1 (OUT) buffer size. */
    #define `$INSTANCE_NAME`_BTLDR_SIZEOF_READ_BUFFER   (64u)   /* Endpoint 2 (IN)  buffer size. */
    #define `$INSTANCE_NAME`_BTLDR_MAX_PACKET_SIZE      `$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER

    #define `$INSTANCE_NAME`_BTLDR_WAIT_1_MS            (1u)    /* Time Out quantity equal 1mS */

    /* Map-specific USB bootloader communication functions to common bootloader functions */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`)
        #define CyBtldrCommStart        `$INSTANCE_NAME`_CyBtldrCommStart
        #define CyBtldrCommStop         `$INSTANCE_NAME`_CyBtldrCommStop
        #define CyBtldrCommReset        `$INSTANCE_NAME`_CyBtldrCommReset
        #define CyBtldrCommWrite        `$INSTANCE_NAME`_CyBtldrCommWrite
        #define CyBtldrCommRead         `$INSTANCE_NAME`_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) */
#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/

#define `$INSTANCE_NAME`_EP0                        (0u)
#define `$INSTANCE_NAME`_EP1                        (1u)
#define `$INSTANCE_NAME`_EP2                        (2u)
#define `$INSTANCE_NAME`_EP3                        (3u)
#define `$INSTANCE_NAME`_EP4                        (4u)
#define `$INSTANCE_NAME`_EP5                        (5u)
#define `$INSTANCE_NAME`_EP6                        (6u)
#define `$INSTANCE_NAME`_EP7                        (7u)
#define `$INSTANCE_NAME`_EP8                        (8u)
#define `$INSTANCE_NAME`_MAX_EP                     (9u)

#define `$INSTANCE_NAME`_TRUE                       (1u)
#define `$INSTANCE_NAME`_FALSE                      (0u)

#define `$INSTANCE_NAME`_NO_EVENT_ALLOWED           (2u)
#define `$INSTANCE_NAME`_EVENT_PENDING              (1u)
#define `$INSTANCE_NAME`_NO_EVENT_PENDING           (0u)

#define `$INSTANCE_NAME`_IN_BUFFER_FULL             `$INSTANCE_NAME`_NO_EVENT_PENDING
#define `$INSTANCE_NAME`_IN_BUFFER_EMPTY            `$INSTANCE_NAME`_EVENT_PENDING
#define `$INSTANCE_NAME`_OUT_BUFFER_FULL            `$INSTANCE_NAME`_EVENT_PENDING
#define `$INSTANCE_NAME`_OUT_BUFFER_EMPTY           `$INSTANCE_NAME`_NO_EVENT_PENDING

#define `$INSTANCE_NAME`_FORCE_J                    (0xA0u)
#define `$INSTANCE_NAME`_FORCE_K                    (0x80u)
#define `$INSTANCE_NAME`_FORCE_SE0                  (0xC0u)
#define `$INSTANCE_NAME`_FORCE_NONE                 (0x00u)

#define `$INSTANCE_NAME`_IDLE_TIMER_RUNNING         (0x02u)
#define `$INSTANCE_NAME`_IDLE_TIMER_EXPIRED         (0x01u)
#define `$INSTANCE_NAME`_IDLE_TIMER_INDEFINITE      (0x00u)

#define `$INSTANCE_NAME`_DEVICE_STATUS_BUS_POWERED  (0x00u)
#define `$INSTANCE_NAME`_DEVICE_STATUS_SELF_POWERED (0x01u)

#define `$INSTANCE_NAME`_3V_OPERATION               (0x00u)
#define `$INSTANCE_NAME`_5V_OPERATION               (0x01u)
#define `$INSTANCE_NAME`_DWR_POWER_OPERATION        (0x02u)

#define `$INSTANCE_NAME`_MODE_DISABLE               (0x00u)
#define `$INSTANCE_NAME`_MODE_NAK_IN_OUT            (0x01u)
#define `$INSTANCE_NAME`_MODE_STATUS_OUT_ONLY       (0x02u)
#define `$INSTANCE_NAME`_MODE_STALL_IN_OUT          (0x03u)
#define `$INSTANCE_NAME`_MODE_RESERVED_0100         (0x04u)
#define `$INSTANCE_NAME`_MODE_ISO_OUT               (0x05u)
#define `$INSTANCE_NAME`_MODE_STATUS_IN_ONLY        (0x06u)
#define `$INSTANCE_NAME`_MODE_ISO_IN                (0x07u)
#define `$INSTANCE_NAME`_MODE_NAK_OUT               (0x08u)
#define `$INSTANCE_NAME`_MODE_ACK_OUT               (0x09u)
#define `$INSTANCE_NAME`_MODE_RESERVED_1010         (0x0Au)
#define `$INSTANCE_NAME`_MODE_ACK_OUT_STATUS_IN     (0x0Bu)
#define `$INSTANCE_NAME`_MODE_NAK_IN                (0x0Cu)
#define `$INSTANCE_NAME`_MODE_ACK_IN                (0x0Du)
#define `$INSTANCE_NAME`_MODE_RESERVED_1110         (0x0Eu)
#define `$INSTANCE_NAME`_MODE_ACK_IN_STATUS_OUT     (0x0Fu)
#define `$INSTANCE_NAME`_MODE_MASK                  (0x0Fu)
#define `$INSTANCE_NAME`_MODE_STALL_DATA_EP         (0x80u)

#define `$INSTANCE_NAME`_MODE_ACKD                  (0x10u)
#define `$INSTANCE_NAME`_MODE_OUT_RCVD              (0x20u)
#define `$INSTANCE_NAME`_MODE_IN_RCVD               (0x40u)
#define `$INSTANCE_NAME`_MODE_SETUP_RCVD            (0x80u)

#define `$INSTANCE_NAME`_RQST_TYPE_MASK             (0x60u)
#define `$INSTANCE_NAME`_RQST_TYPE_STD              (0x00u)
#define `$INSTANCE_NAME`_RQST_TYPE_CLS              (0x20u)
#define `$INSTANCE_NAME`_RQST_TYPE_VND              (0x40u)
#define `$INSTANCE_NAME`_RQST_DIR_MASK              (0x80u)
#define `$INSTANCE_NAME`_RQST_DIR_D2H               (0x80u)
#define `$INSTANCE_NAME`_RQST_DIR_H2D               (0x00u)
#define `$INSTANCE_NAME`_RQST_RCPT_MASK             (0x03u)
#define `$INSTANCE_NAME`_RQST_RCPT_DEV              (0x00u)
#define `$INSTANCE_NAME`_RQST_RCPT_IFC              (0x01u)
#define `$INSTANCE_NAME`_RQST_RCPT_EP               (0x02u)
#define `$INSTANCE_NAME`_RQST_RCPT_OTHER            (0x03u)

#if (`$INSTANCE_NAME`_LPM_ACTIVE)
    #define `$INSTANCE_NAME`_LPM_REQ_ACK            (0x01u << `$INSTANCE_NAME`_LPM_CTRL_LPM_ACK_RESP_POS)
    #define `$INSTANCE_NAME`_LPM_REQ_NACK           (0x00u)
    #define `$INSTANCE_NAME`_LPM_REQ_NYET           (0x01u << `$INSTANCE_NAME`_LPM_CTRL_NYET_EN_POS)
#endif /*(`$INSTANCE_NAME`_LPM_ACTIVE)*/

/* USB Class Codes */
#define `$INSTANCE_NAME`_CLASS_DEVICE               (0x00u)     /* Use class code info from Interface Descriptors */
#define `$INSTANCE_NAME`_CLASS_AUDIO                (0x01u)     /* Audio device */
#define `$INSTANCE_NAME`_CLASS_CDC                  (0x02u)     /* Communication device class */
#define `$INSTANCE_NAME`_CLASS_HID                  (0x03u)     /* Human Interface Device */
#define `$INSTANCE_NAME`_CLASS_PDC                  (0x05u)     /* Physical device class */
#define `$INSTANCE_NAME`_CLASS_IMAGE                (0x06u)     /* Still Imaging device */
#define `$INSTANCE_NAME`_CLASS_PRINTER              (0x07u)     /* Printer device  */
#define `$INSTANCE_NAME`_CLASS_MSD                  (0x08u)     /* Mass Storage device  */
#define `$INSTANCE_NAME`_CLASS_HUB                  (0x09u)     /* Full/Hi speed Hub */
#define `$INSTANCE_NAME`_CLASS_CDC_DATA             (0x0Au)     /* CDC data device */
#define `$INSTANCE_NAME`_CLASS_SMART_CARD           (0x0Bu)     /* Smart Card device */
#define `$INSTANCE_NAME`_CLASS_CSD                  (0x0Du)     /* Content Security device */
#define `$INSTANCE_NAME`_CLASS_VIDEO                (0x0Eu)     /* Video device */
#define `$INSTANCE_NAME`_CLASS_PHD                  (0x0Fu)     /* Personal Health care device */
#define `$INSTANCE_NAME`_CLASS_WIRELESSD            (0xDCu)     /* Wireless Controller */
#define `$INSTANCE_NAME`_CLASS_MIS                  (0xE0u)     /* Miscellaneous */
#define `$INSTANCE_NAME`_CLASS_APP                  (0xEFu)     /* Application Specific */
#define `$INSTANCE_NAME`_CLASS_VENDOR               (0xFFu)     /* Vendor specific */

/* Standard Request Types (Table 9-4) */
#define `$INSTANCE_NAME`_GET_STATUS                 (0x00u)
#define `$INSTANCE_NAME`_CLEAR_FEATURE              (0x01u)
#define `$INSTANCE_NAME`_SET_FEATURE                (0x03u)
#define `$INSTANCE_NAME`_SET_ADDRESS                (0x05u)
#define `$INSTANCE_NAME`_GET_DESCRIPTOR             (0x06u)
#define `$INSTANCE_NAME`_SET_DESCRIPTOR             (0x07u)
#define `$INSTANCE_NAME`_GET_CONFIGURATION          (0x08u)
#define `$INSTANCE_NAME`_SET_CONFIGURATION          (0x09u)
#define `$INSTANCE_NAME`_GET_INTERFACE              (0x0Au)
#define `$INSTANCE_NAME`_SET_INTERFACE              (0x0Bu)
#define `$INSTANCE_NAME`_SYNCH_FRAME                (0x0Cu)

/* Vendor Specific Request Types */
/* Request for Microsoft OS String Descriptor */
#define `$INSTANCE_NAME`_GET_EXTENDED_CONFIG_DESCRIPTOR (0x01u)

/* Descriptor Types (Table 9-5) */
#define `$INSTANCE_NAME`_DESCR_DEVICE                   (1u)
#define `$INSTANCE_NAME`_DESCR_CONFIG                   (2u)
#define `$INSTANCE_NAME`_DESCR_STRING                   (3u)
#define `$INSTANCE_NAME`_DESCR_INTERFACE                (4u)
#define `$INSTANCE_NAME`_DESCR_ENDPOINT                 (5u)
#define `$INSTANCE_NAME`_DESCR_DEVICE_QUALIFIER         (6u)
#define `$INSTANCE_NAME`_DESCR_OTHER_SPEED              (7u)
#define `$INSTANCE_NAME`_DESCR_INTERFACE_POWER          (8u)
#if (`$INSTANCE_NAME`_BOS_ENABLE)
    #define `$INSTANCE_NAME`_DESCR_BOS                  (15u)
#endif /* (`$INSTANCE_NAME`_BOS_ENABLE) */
/* Device Descriptor Defines */
#define `$INSTANCE_NAME`_DEVICE_DESCR_LENGTH            (18u)
#define `$INSTANCE_NAME`_DEVICE_DESCR_SN_SHIFT          (16u)

/* Config Descriptor Shifts and Masks */
#define `$INSTANCE_NAME`_CONFIG_DESCR_LENGTH                (0u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_TYPE                  (1u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_TOTAL_LENGTH_LOW      (2u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_TOTAL_LENGTH_HI       (3u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_NUM_INTERFACES        (4u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_CONFIG_VALUE          (5u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_CONFIGURATION         (6u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_ATTRIB                (7u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_ATTRIB_SELF_POWERED   (0x40u)
#define `$INSTANCE_NAME`_CONFIG_DESCR_ATTRIB_RWU_EN         (0x20u)

#if (`$INSTANCE_NAME`_BOS_ENABLE)
    /* Config Descriptor BOS */
    #define `$INSTANCE_NAME`_BOS_DESCR_LENGTH               (0u)
    #define `$INSTANCE_NAME`_BOS_DESCR_TYPE                 (1u)
    #define `$INSTANCE_NAME`_BOS_DESCR_TOTAL_LENGTH_LOW     (2u)
    #define `$INSTANCE_NAME`_BOS_DESCR_TOTAL_LENGTH_HI      (3u)
    #define `$INSTANCE_NAME`_BOS_DESCR_NUM_DEV_CAPS         (4u)
#endif /* (`$INSTANCE_NAME`_BOS_ENABLE) */

/* Feature Selectors (Table 9-6) */
#define `$INSTANCE_NAME`_DEVICE_REMOTE_WAKEUP           (0x01u)
#define `$INSTANCE_NAME`_ENDPOINT_HALT                  (0x00u)
#define `$INSTANCE_NAME`_TEST_MODE                      (0x02u)

/* USB Device Status (Figure 9-4) */
#define `$INSTANCE_NAME`_DEVICE_STATUS_BUS_POWERED      (0x00u)
#define `$INSTANCE_NAME`_DEVICE_STATUS_SELF_POWERED     (0x01u)
#define `$INSTANCE_NAME`_DEVICE_STATUS_REMOTE_WAKEUP    (0x02u)

/* USB Endpoint Status (Figure 9-4) */
#define `$INSTANCE_NAME`_ENDPOINT_STATUS_HALT           (0x01u)

/* USB Endpoint Directions */
#define `$INSTANCE_NAME`_DIR_IN                         (0x80u)
#define `$INSTANCE_NAME`_DIR_OUT                        (0x00u)
#define `$INSTANCE_NAME`_DIR_UNUSED                     (0x7Fu)

/* USB Endpoint Attributes */
#define `$INSTANCE_NAME`_EP_TYPE_CTRL                   (0x00u)
#define `$INSTANCE_NAME`_EP_TYPE_ISOC                   (0x01u)
#define `$INSTANCE_NAME`_EP_TYPE_BULK                   (0x02u)
#define `$INSTANCE_NAME`_EP_TYPE_INT                    (0x03u)
#define `$INSTANCE_NAME`_EP_TYPE_MASK                   (0x03u)

#define `$INSTANCE_NAME`_EP_SYNC_TYPE_NO_SYNC           (0x00u)
#define `$INSTANCE_NAME`_EP_SYNC_TYPE_ASYNC             (0x04u)
#define `$INSTANCE_NAME`_EP_SYNC_TYPE_ADAPTIVE          (0x08u)
#define `$INSTANCE_NAME`_EP_SYNC_TYPE_SYNCHRONOUS       (0x0Cu)
#define `$INSTANCE_NAME`_EP_SYNC_TYPE_MASK              (0x0Cu)

#define `$INSTANCE_NAME`_EP_USAGE_TYPE_DATA             (0x00u)
#define `$INSTANCE_NAME`_EP_USAGE_TYPE_FEEDBACK         (0x10u)
#define `$INSTANCE_NAME`_EP_USAGE_TYPE_IMPLICIT         (0x20u)
#define `$INSTANCE_NAME`_EP_USAGE_TYPE_RESERVED         (0x30u)
#define `$INSTANCE_NAME`_EP_USAGE_TYPE_MASK             (0x30u)

/* Point Status defines */
#define `$INSTANCE_NAME`_EP_STATUS_LENGTH               (0x02u)

/* Point Device defines */
#define `$INSTANCE_NAME`_DEVICE_STATUS_LENGTH           (0x02u)

#define `$INSTANCE_NAME`_STATUS_LENGTH_MAX \
                 ((`$INSTANCE_NAME`_EP_STATUS_LENGTH > `$INSTANCE_NAME`_DEVICE_STATUS_LENGTH) ? \
                        `$INSTANCE_NAME`_EP_STATUS_LENGTH : `$INSTANCE_NAME`_DEVICE_STATUS_LENGTH)

/* Transfer Completion Notification */
#define `$INSTANCE_NAME`_XFER_IDLE                      (0x00u)
#define `$INSTANCE_NAME`_XFER_STATUS_ACK                (0x01u)
#define `$INSTANCE_NAME`_XFER_PREMATURE                 (0x02u)
#define `$INSTANCE_NAME`_XFER_ERROR                     (0x03u)

/* Driver State defines */
#define `$INSTANCE_NAME`_TRANS_STATE_IDLE               (0x00u)
#define `$INSTANCE_NAME`_TRANS_STATE_CONTROL_READ       (0x02u)
#define `$INSTANCE_NAME`_TRANS_STATE_CONTROL_WRITE      (0x04u)
#define `$INSTANCE_NAME`_TRANS_STATE_NO_DATA_CONTROL    (0x06u)

/* String Descriptor defines */
#define `$INSTANCE_NAME`_STRING_MSOS                    (0xEEu)
#define `$INSTANCE_NAME`_MSOS_DESCRIPTOR_LENGTH         (18u)
#define `$INSTANCE_NAME`_MSOS_CONF_DESCR_LENGTH         (40u)

/* Return values */
#define `$INSTANCE_NAME`_BCD_PORT_SDP       (1u) /* Standard downstream port detected */
#define `$INSTANCE_NAME`_BCD_PORT_CDP       (2u) /* Charging downstream port detected */
#define `$INSTANCE_NAME`_BCD_PORT_DCP       (3u) /* Dedicated charging port detected */
#define `$INSTANCE_NAME`_BCD_PORT_UNKNOWN   (0u) /* Unable to detect charging port */
#define `$INSTANCE_NAME`_BCD_PORT_ERR       (4u) /* Error condition in detection process*/


/* Timeouts for BCD */
#define `$INSTANCE_NAME`_BCD_TIMEOUT                (400u)  /* Copied from PBK#163 TIMEOUT (300 ms) */
#define `$INSTANCE_NAME`_BCD_TDCD_DBNC              (10u)  /*BCD v1.2: DCD debounce time 10 ms*/
#define `$INSTANCE_NAME`_BCD_PRIMARY_WAIT           (40u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define `$INSTANCE_NAME`_BCD_SECONDARY_WAIT         (47u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define `$INSTANCE_NAME`_BCD_SUSPEND_DISABLE_WAIT   (2u)    /* Copied from PBK#163 TIMEOUT (2 us)   */

/* Wait cycles required before clearing SUSPEND_DEL in POWER_CTRL: 2us */
#define `$INSTANCE_NAME`_WAIT_SUSPEND_DEL_DISABLE   (2u)

/* Wait cycles required for USB regulator stabilization after it is enabled : 50ns */
#define `$INSTANCE_NAME`_WAIT_VREF_STABILITY        (0u)

#if (CY_PSOC3 || CY_PSOC5LP)
/* Wait cycles required for USB reference restore: 40us */
#define `$INSTANCE_NAME`_WAIT_VREF_RESTORE          (40u)

/* Wait cycles required for stabilization after register is written : 50ns */
#define `$INSTANCE_NAME`_WAIT_REG_STABILITY_50NS    (0u)
#define `$INSTANCE_NAME`_WAIT_REG_STABILITY_1US     (1u)

/* Wait cycles required after CR0 register write: 1 cycle */
#define `$INSTANCE_NAME`_WAIT_CR0_REG_STABILITY     (1u)

/* Wait cycles required after PD_PULLUP_N bit is set in PM_USB_CR0: 2us */
#define `$INSTANCE_NAME`_WAIT_PD_PULLUP_N_ENABLE    (2u)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if (CY_PSOC4)
    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
        #define `$INSTANCE_NAME`_DMA_DESCR0         (0u)
        #define `$INSTANCE_NAME`_DMA_DESCR1         (1u)
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define `$INSTANCE_NAME`_DMA_BUF_SIZE             (0x55u)
        #define `$INSTANCE_NAME`_DMA_BYTES_PER_BURST      (32u)
        #define `$INSTANCE_NAME`_DMA_HALFWORDS_PER_BURST  (16u)
        #define `$INSTANCE_NAME`_DMA_BURST_BYTES_MASK     (`$INSTANCE_NAME`_DMA_BYTES_PER_BURST - 1u)

        #define `$INSTANCE_NAME`_DMA_DESCR0_MASK        (0x00u)
        #define `$INSTANCE_NAME`_DMA_DESCR1_MASK        (0x80u)
        #define `$INSTANCE_NAME`_DMA_DESCR_REVERT       (0x40u)
        #define `$INSTANCE_NAME`_DMA_DESCR_16BITS       (0x20u)
        #define `$INSTANCE_NAME`_DMA_DESCR_SHIFT        (7u)

        #define `$INSTANCE_NAME`_DMA_GET_DESCR_NUM(desrc)
        #define `$INSTANCE_NAME`_DMA_GET_BURST_CNT(dmaBurstCnt) \
                    (((dmaBurstCnt) > 2u)? ((dmaBurstCnt) - 2u) : 0u)

        #define `$INSTANCE_NAME`_DMA_GET_MAX_ELEM_PER_BURST(dmaLastBurstEl) \
                    ((0u != ((dmaLastBurstEl) & `$INSTANCE_NAME`_DMA_DESCR_16BITS)) ? \
                                (`$INSTANCE_NAME`_DMA_HALFWORDS_PER_BURST - 1u) : (`$INSTANCE_NAME`_DMA_BYTES_PER_BURST - 1u))
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
#else
    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL)
        #define `$INSTANCE_NAME`_DMA_BYTES_PER_BURST    (0u)
        #define `$INSTANCE_NAME`_DMA_REQUEST_PER_BURST  (0u)
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL) */

    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        #define `$INSTANCE_NAME`_DMA_BYTES_PER_BURST    (32u)
        #define `$INSTANCE_NAME`_DMA_BYTES_REPEAT       (2u)

        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define `$INSTANCE_NAME`_DMA_BUF_SIZE           (0x55u)
        #define `$INSTANCE_NAME`_DMA_REQUEST_PER_BURST  (1u)

        #define `$INSTANCE_NAME`_EP17_SR_MASK           (0x7Fu)
        #define `$INSTANCE_NAME`_EP8_SR_MASK            (0x03u)
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
#endif /* (CY_PSOC4) */

/* DIE ID string descriptor defines */
#if defined(`$INSTANCE_NAME`_ENABLE_IDSN_STRING)
    #define `$INSTANCE_NAME`_IDSN_DESCR_LENGTH      (0x22u)
#endif /* (`$INSTANCE_NAME`_ENABLE_IDSN_STRING) */


/***************************************
*     Vars with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 `$INSTANCE_NAME`_initVar;
extern volatile uint8 `$INSTANCE_NAME`_device;
extern volatile uint8 `$INSTANCE_NAME`_transferState;
extern volatile uint8 `$INSTANCE_NAME`_configuration;
extern volatile uint8 `$INSTANCE_NAME`_configurationChanged;
extern volatile uint8 `$INSTANCE_NAME`_deviceStatus;
/** @} globals */

/**
* \addtogroup group_hid
* @{
*/
/* HID Variables */
#if defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS)
    extern volatile uint8 `$INSTANCE_NAME`_hidProtocol [`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER]; 
    extern volatile uint8 `$INSTANCE_NAME`_hidIdleRate [`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
    extern volatile uint8 `$INSTANCE_NAME`_hidIdleTimer[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
#endif /* (`$INSTANCE_NAME`_ENABLE_HID_CLASS) */
/** @} hid */


/***************************************
*              Registers
***************************************/

/* Common registers for all PSoCs: 3/4/5LP */
#define `$INSTANCE_NAME`_ARB_CFG_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_CFG)
#define `$INSTANCE_NAME`_ARB_CFG_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_CFG)

#define `$INSTANCE_NAME`_ARB_EP1_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_CFG)
#define `$INSTANCE_NAME`_ARB_EP1_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_CFG)
#define `$INSTANCE_NAME`_ARB_EP1_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP1_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP1_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_SR)
#define `$INSTANCE_NAME`_ARB_EP1_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_SR)
#define `$INSTANCE_NAME`_ARB_EP1_CFG_IND    `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_CFG
#define `$INSTANCE_NAME`_ARB_EP1_INT_EN_IND `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_INT_EN
#define `$INSTANCE_NAME`_ARB_EP1_SR_IND     `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_SR
#define `$INSTANCE_NAME`_ARB_EP_BASE        (*(volatile `$INSTANCE_NAME`_arb_eps_struct CYXDATA *) \
                                            (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP1_CFG - sizeof(`$INSTANCE_NAME`_arb_ep_struct)))

#define `$INSTANCE_NAME`_ARB_EP2_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP2_CFG)
#define `$INSTANCE_NAME`_ARB_EP2_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP2_CFG)
#define `$INSTANCE_NAME`_ARB_EP2_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP2_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP2_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP2_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP2_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP2_SR)
#define `$INSTANCE_NAME`_ARB_EP2_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP2_SR)

#define `$INSTANCE_NAME`_ARB_EP3_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP3_CFG)
#define `$INSTANCE_NAME`_ARB_EP3_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP3_CFG)
#define `$INSTANCE_NAME`_ARB_EP3_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP3_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP3_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP3_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP3_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP3_SR)
#define `$INSTANCE_NAME`_ARB_EP3_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP3_SR)

#define `$INSTANCE_NAME`_ARB_EP4_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP4_CFG)
#define `$INSTANCE_NAME`_ARB_EP4_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP4_CFG)
#define `$INSTANCE_NAME`_ARB_EP4_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP4_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP4_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP4_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP4_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP4_SR)
#define `$INSTANCE_NAME`_ARB_EP4_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP4_SR)

#define `$INSTANCE_NAME`_ARB_EP5_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP5_CFG)
#define `$INSTANCE_NAME`_ARB_EP5_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP5_CFG)
#define `$INSTANCE_NAME`_ARB_EP5_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP5_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP5_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP5_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP5_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP5_SR)
#define `$INSTANCE_NAME`_ARB_EP5_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP5_SR)

#define `$INSTANCE_NAME`_ARB_EP6_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP6_CFG)
#define `$INSTANCE_NAME`_ARB_EP6_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP6_CFG)
#define `$INSTANCE_NAME`_ARB_EP6_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP6_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP6_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP6_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP6_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP6_SR)
#define `$INSTANCE_NAME`_ARB_EP6_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP6_SR)

#define `$INSTANCE_NAME`_ARB_EP7_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP7_CFG)
#define `$INSTANCE_NAME`_ARB_EP7_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP7_CFG)
#define `$INSTANCE_NAME`_ARB_EP7_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP7_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP7_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP7_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP7_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP7_SR)
#define `$INSTANCE_NAME`_ARB_EP7_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP7_SR)

#define `$INSTANCE_NAME`_ARB_EP8_CFG_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP8_CFG)
#define `$INSTANCE_NAME`_ARB_EP8_CFG_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP8_CFG)
#define `$INSTANCE_NAME`_ARB_EP8_INT_EN_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP8_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP8_INT_EN_REG (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP8_INT_EN)
#define `$INSTANCE_NAME`_ARB_EP8_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP8_SR)
#define `$INSTANCE_NAME`_ARB_EP8_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_EP8_SR)

#define `$INSTANCE_NAME`_ARB_INT_EN_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_INT_EN)
#define `$INSTANCE_NAME`_ARB_INT_EN_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_INT_EN)
#define `$INSTANCE_NAME`_ARB_INT_SR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_INT_SR)
#define `$INSTANCE_NAME`_ARB_INT_SR_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_INT_SR)

#define `$INSTANCE_NAME`_ARB_RW1_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_DR)
#define `$INSTANCE_NAME`_ARB_RW1_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_RA)

#define `$INSTANCE_NAME`_ARB_RW1_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW1_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_WA)
#define `$INSTANCE_NAME`_ARB_RW1_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_WA_MSB)
#define `$INSTANCE_NAME`_ARB_RW1_DR_IND     `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_DR
#define `$INSTANCE_NAME`_ARB_RW1_RA_IND     `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_RA
#define `$INSTANCE_NAME`_ARB_RW1_RA_MSB_IND `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_RA_MSB
#define `$INSTANCE_NAME`_ARB_RW1_WA_IND     `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_WA
#define `$INSTANCE_NAME`_ARB_RW1_WA_MSB_IND `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_WA_MSB

#define `$INSTANCE_NAME`_ARB_RW2_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW2_DR)
#define `$INSTANCE_NAME`_ARB_RW2_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW2_RA)
#define `$INSTANCE_NAME`_ARB_RW2_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW2_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW2_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW2_WA)
#define `$INSTANCE_NAME`_ARB_RW2_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW2_WA_MSB)

#define `$INSTANCE_NAME`_ARB_RW3_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW3_DR)
#define `$INSTANCE_NAME`_ARB_RW3_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW3_RA)
#define `$INSTANCE_NAME`_ARB_RW3_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW3_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW3_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW3_WA)
#define `$INSTANCE_NAME`_ARB_RW3_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW3_WA_MSB)

#define `$INSTANCE_NAME`_ARB_RW4_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW4_DR)
#define `$INSTANCE_NAME`_ARB_RW4_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW4_RA)
#define `$INSTANCE_NAME`_ARB_RW4_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW4_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW4_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW4_WA)
#define `$INSTANCE_NAME`_ARB_RW4_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW4_WA_MSB)

#define `$INSTANCE_NAME`_ARB_RW5_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW5_DR)
#define `$INSTANCE_NAME`_ARB_RW5_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW5_RA)
#define `$INSTANCE_NAME`_ARB_RW5_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW5_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW5_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW5_WA)
#define `$INSTANCE_NAME`_ARB_RW5_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW5_WA_MSB)

#define `$INSTANCE_NAME`_ARB_RW6_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW6_DR)
#define `$INSTANCE_NAME`_ARB_RW6_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW6_RA)
#define `$INSTANCE_NAME`_ARB_RW6_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW6_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW6_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW6_WA)
#define `$INSTANCE_NAME`_ARB_RW6_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW6_WA_MSB)

#define `$INSTANCE_NAME`_ARB_RW7_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW7_DR)
#define `$INSTANCE_NAME`_ARB_RW7_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW7_RA)
#define `$INSTANCE_NAME`_ARB_RW7_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW7_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW7_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW7_WA)
#define `$INSTANCE_NAME`_ARB_RW7_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW7_WA_MSB)

#define `$INSTANCE_NAME`_ARB_RW8_DR_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW8_DR)
#define `$INSTANCE_NAME`_ARB_RW8_RA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW8_RA)
#define `$INSTANCE_NAME`_ARB_RW8_RA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW8_RA_MSB)
#define `$INSTANCE_NAME`_ARB_RW8_WA_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW8_WA)
#define `$INSTANCE_NAME`_ARB_RW8_WA_MSB_PTR ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW8_WA_MSB)

#define `$INSTANCE_NAME`_BUF_SIZE_PTR       ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__BUF_SIZE)
#define `$INSTANCE_NAME`_BUF_SIZE_REG       (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__BUF_SIZE)
#define `$INSTANCE_NAME`_BUS_RST_CNT_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__BUS_RST_CNT)
#define `$INSTANCE_NAME`_BUS_RST_CNT_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__BUS_RST_CNT)
#define `$INSTANCE_NAME`_CWA_PTR            ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CWA)
#define `$INSTANCE_NAME`_CWA_REG            (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CWA)
#define `$INSTANCE_NAME`_CWA_MSB_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CWA_MSB)
#define `$INSTANCE_NAME`_CWA_MSB_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CWA_MSB)
#define `$INSTANCE_NAME`_CR0_PTR            ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CR0)
#define `$INSTANCE_NAME`_CR0_REG            (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CR0)
#define `$INSTANCE_NAME`_CR1_PTR            ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CR1)
#define `$INSTANCE_NAME`_CR1_REG            (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__CR1)

#define `$INSTANCE_NAME`_DMA_THRES_PTR      ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__DMA_THRES)
#define `$INSTANCE_NAME`_DMA_THRES_REG      (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__DMA_THRES)
#define `$INSTANCE_NAME`_DMA_THRES_MSB_PTR  ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__DMA_THRES_MSB)
#define `$INSTANCE_NAME`_DMA_THRES_MSB_REG  (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__DMA_THRES_MSB)

#define `$INSTANCE_NAME`_EP_ACTIVE_PTR      ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP_ACTIVE)
#define `$INSTANCE_NAME`_EP_ACTIVE_REG      (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP_ACTIVE)
#define `$INSTANCE_NAME`_EP_TYPE_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP_TYPE)
#define `$INSTANCE_NAME`_EP_TYPE_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP_TYPE)

#define `$INSTANCE_NAME`_EP0_CNT_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_CNT)
#define `$INSTANCE_NAME`_EP0_CNT_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_CNT)
#define `$INSTANCE_NAME`_EP0_CR_PTR         ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_CR)
#define `$INSTANCE_NAME`_EP0_CR_REG         (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_CR)
#define `$INSTANCE_NAME`_EP0_DR0_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR0)
#define `$INSTANCE_NAME`_EP0_DR0_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR0)
#define `$INSTANCE_NAME`_EP0_DR1_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR1)
#define `$INSTANCE_NAME`_EP0_DR1_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR1)
#define `$INSTANCE_NAME`_EP0_DR2_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR2)
#define `$INSTANCE_NAME`_EP0_DR2_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR2)
#define `$INSTANCE_NAME`_EP0_DR3_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR3)
#define `$INSTANCE_NAME`_EP0_DR3_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR3)
#define `$INSTANCE_NAME`_EP0_DR4_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR4)
#define `$INSTANCE_NAME`_EP0_DR4_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR4)
#define `$INSTANCE_NAME`_EP0_DR5_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR5)
#define `$INSTANCE_NAME`_EP0_DR5_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR5)
#define `$INSTANCE_NAME`_EP0_DR6_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR6)
#define `$INSTANCE_NAME`_EP0_DR6_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR6)
#define `$INSTANCE_NAME`_EP0_DR7_PTR        ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR7)
#define `$INSTANCE_NAME`_EP0_DR7_REG        (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR7)
#define `$INSTANCE_NAME`_EP0_DR0_IND        `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR0
#define `$INSTANCE_NAME`_EP0_DR_BASE        (*(volatile `$INSTANCE_NAME`_ep0_data_struct CYXDATA *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__EP0_DR0)

#define `$INSTANCE_NAME`_OSCLK_DR0_PTR      ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__OSCLK_DR0)
#define `$INSTANCE_NAME`_OSCLK_DR0_REG      (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__OSCLK_DR0)
#define `$INSTANCE_NAME`_OSCLK_DR1_PTR      ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__OSCLK_DR1)
#define `$INSTANCE_NAME`_OSCLK_DR1_REG      (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__OSCLK_DR1)

#define `$INSTANCE_NAME`_SIE_EP_INT_EN_PTR  ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP_INT_EN)
#define `$INSTANCE_NAME`_SIE_EP_INT_EN_REG  (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP_INT_EN)
#define `$INSTANCE_NAME`_SIE_EP_INT_SR_PTR  ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP_INT_SR)
#define `$INSTANCE_NAME`_SIE_EP_INT_SR_REG  (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP_INT_SR)

#define `$INSTANCE_NAME`_SIE_EP1_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT0)
#define `$INSTANCE_NAME`_SIE_EP1_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT0)
#define `$INSTANCE_NAME`_SIE_EP1_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT1)
#define `$INSTANCE_NAME`_SIE_EP1_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT1)
#define `$INSTANCE_NAME`_SIE_EP1_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CR0)
#define `$INSTANCE_NAME`_SIE_EP1_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CR0)
#define `$INSTANCE_NAME`_SIE_EP1_CNT1_IND   `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT1
#define `$INSTANCE_NAME`_SIE_EP1_CNT0_IND   `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT0
#define `$INSTANCE_NAME`_SIE_EP1_CR0_IND    `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CR0
#define `$INSTANCE_NAME`_SIE_EP_BASE        (*(volatile `$INSTANCE_NAME`_sie_eps_struct CYXDATA *) \
                                            (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP1_CNT0 - sizeof(`$INSTANCE_NAME`_sie_ep_struct)))

#define `$INSTANCE_NAME`_SIE_EP2_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP2_CNT0)
#define `$INSTANCE_NAME`_SIE_EP2_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP2_CNT0)
#define `$INSTANCE_NAME`_SIE_EP2_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP2_CNT1)
#define `$INSTANCE_NAME`_SIE_EP2_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP2_CNT1)
#define `$INSTANCE_NAME`_SIE_EP2_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP2_CR0)
#define `$INSTANCE_NAME`_SIE_EP2_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP2_CR0)

#define `$INSTANCE_NAME`_SIE_EP3_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP3_CNT0)
#define `$INSTANCE_NAME`_SIE_EP3_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP3_CNT0)
#define `$INSTANCE_NAME`_SIE_EP3_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP3_CNT1)
#define `$INSTANCE_NAME`_SIE_EP3_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP3_CNT1)
#define `$INSTANCE_NAME`_SIE_EP3_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP3_CR0)
#define `$INSTANCE_NAME`_SIE_EP3_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP3_CR0)

#define `$INSTANCE_NAME`_SIE_EP4_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP4_CNT0)
#define `$INSTANCE_NAME`_SIE_EP4_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP4_CNT0)
#define `$INSTANCE_NAME`_SIE_EP4_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP4_CNT1)
#define `$INSTANCE_NAME`_SIE_EP4_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP4_CNT1)
#define `$INSTANCE_NAME`_SIE_EP4_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP4_CR0)
#define `$INSTANCE_NAME`_SIE_EP4_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP4_CR0)

#define `$INSTANCE_NAME`_SIE_EP5_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP5_CNT0)
#define `$INSTANCE_NAME`_SIE_EP5_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP5_CNT0)
#define `$INSTANCE_NAME`_SIE_EP5_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP5_CNT1)
#define `$INSTANCE_NAME`_SIE_EP5_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP5_CNT1)
#define `$INSTANCE_NAME`_SIE_EP5_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP5_CR0)
#define `$INSTANCE_NAME`_SIE_EP5_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP5_CR0)

#define `$INSTANCE_NAME`_SIE_EP6_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP6_CNT0)
#define `$INSTANCE_NAME`_SIE_EP6_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP6_CNT0)
#define `$INSTANCE_NAME`_SIE_EP6_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP6_CNT1)
#define `$INSTANCE_NAME`_SIE_EP6_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP6_CNT1)
#define `$INSTANCE_NAME`_SIE_EP6_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP6_CR0)
#define `$INSTANCE_NAME`_SIE_EP6_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP6_CR0)

#define `$INSTANCE_NAME`_SIE_EP7_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP7_CNT0)
#define `$INSTANCE_NAME`_SIE_EP7_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP7_CNT0)
#define `$INSTANCE_NAME`_SIE_EP7_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP7_CNT1)
#define `$INSTANCE_NAME`_SIE_EP7_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP7_CNT1)
#define `$INSTANCE_NAME`_SIE_EP7_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP7_CR0)
#define `$INSTANCE_NAME`_SIE_EP7_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP7_CR0)

#define `$INSTANCE_NAME`_SIE_EP8_CNT0_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP8_CNT0)
#define `$INSTANCE_NAME`_SIE_EP8_CNT0_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP8_CNT0)
#define `$INSTANCE_NAME`_SIE_EP8_CNT1_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP8_CNT1)
#define `$INSTANCE_NAME`_SIE_EP8_CNT1_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP8_CNT1)
#define `$INSTANCE_NAME`_SIE_EP8_CR0_PTR    ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP8_CR0)
#define `$INSTANCE_NAME`_SIE_EP8_CR0_REG    (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SIE_EP8_CR0)

#define `$INSTANCE_NAME`_SOF0_PTR           ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SOF0)
#define `$INSTANCE_NAME`_SOF0_REG           (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SOF0)
#define `$INSTANCE_NAME`_SOF1_PTR           ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SOF1)
#define `$INSTANCE_NAME`_SOF1_REG           (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__SOF1)

#define `$INSTANCE_NAME`_USB_CLK_EN_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__USB_CLK_EN)
#define `$INSTANCE_NAME`_USB_CLK_EN_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__USB_CLK_EN)

#define `$INSTANCE_NAME`_USBIO_CR0_PTR      ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__USBIO_CR0)
#define `$INSTANCE_NAME`_USBIO_CR0_REG      (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__USBIO_CR0)
#define `$INSTANCE_NAME`_USBIO_CR1_PTR      ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__USBIO_CR1)
#define `$INSTANCE_NAME`_USBIO_CR1_REG      (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__USBIO_CR1)

#define `$INSTANCE_NAME`_DYN_RECONFIG_PTR   ( (`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__DYN_RECONFIG)
#define `$INSTANCE_NAME`_DYN_RECONFIG_REG   (*(`$REG_SIZE` *) `$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__DYN_RECONFIG)

#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_ARB_RW1_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW1_RA16)
    #define `$INSTANCE_NAME`_ARB_RW1_RA16_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW1_RA16)
    #define `$INSTANCE_NAME`_ARB_RW1_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW1_WA16)
    #define `$INSTANCE_NAME`_ARB_RW1_WA16_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW1_WA16)
    #define `$INSTANCE_NAME`_ARB_RW1_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW1_DR16)
    #define `$INSTANCE_NAME`_ARB_RW1_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW1_DR16)
    #define `$INSTANCE_NAME`_ARB_EP16_BASE      (*(volatile `$INSTANCE_NAME`_arb_eps_reg16_struct CYXDATA *) \
                                                (`$INSTANCE_NAME`_`$PRIMITIVE_INSTANCE`__ARB_RW1_WA16 - sizeof(`$INSTANCE_NAME`_arb_ep_reg16_struct)))

    #define `$INSTANCE_NAME`_ARB_RW2_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW2_DR16)
    #define `$INSTANCE_NAME`_ARB_RW2_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW2_RA16)
    #define `$INSTANCE_NAME`_ARB_RW2_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW2_WA16)

    #define `$INSTANCE_NAME`_ARB_RW3_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW3_DR16)
    #define `$INSTANCE_NAME`_ARB_RW3_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW3_RA16)
    #define `$INSTANCE_NAME`_ARB_RW3_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW3_WA16)

    #define `$INSTANCE_NAME`_ARB_RW4_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW4_DR16)
    #define `$INSTANCE_NAME`_ARB_RW4_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW4_RA16)
    #define `$INSTANCE_NAME`_ARB_RW4_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW4_WA16)

    #define `$INSTANCE_NAME`_ARB_RW5_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW5_DR16)
    #define `$INSTANCE_NAME`_ARB_RW5_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW5_RA16)
    #define `$INSTANCE_NAME`_ARB_RW5_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW5_WA16)

    #define `$INSTANCE_NAME`_ARB_RW6_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW6_DR16)
    #define `$INSTANCE_NAME`_ARB_RW6_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW6_RA16)
    #define `$INSTANCE_NAME`_ARB_RW6_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW6_WA16)

    #define `$INSTANCE_NAME`_ARB_RW7_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW7_DR16)
    #define `$INSTANCE_NAME`_ARB_RW7_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW7_RA16)
    #define `$INSTANCE_NAME`_ARB_RW7_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW7_WA16)

    #define `$INSTANCE_NAME`_ARB_RW8_DR16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW8_DR16)
    #define `$INSTANCE_NAME`_ARB_RW8_RA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW8_RA16)
    #define `$INSTANCE_NAME`_ARB_RW8_WA16_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__ARB_RW8_WA16)

    #define `$INSTANCE_NAME`_OSCLK_DR16_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__OSCLK_DR16)
    #define `$INSTANCE_NAME`_OSCLK_DR16_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__OSCLK_DR16)

    #define `$INSTANCE_NAME`_SOF16_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__SOF16)
    #define `$INSTANCE_NAME`_SOF16_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__SOF16)
    
    #define `$INSTANCE_NAME`_CWA16_PTR          ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__CWA16)
    #define `$INSTANCE_NAME`_CWA16_REG          (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__CWA16)

    #define `$INSTANCE_NAME`_DMA_THRES16_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__DMA_THRES16)
    #define `$INSTANCE_NAME`_DMA_THRES16_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__DMA_THRES16)

    #define `$INSTANCE_NAME`_USB_CLK_EN_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_CLK_EN)
    #define `$INSTANCE_NAME`_USB_CLK_EN_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_CLK_EN)

    #define `$INSTANCE_NAME`_USBIO_CR2_PTR      ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USBIO_CR2)
    #define `$INSTANCE_NAME`_USBIO_CR2_REG      (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USBIO_CR2)

    #define `$INSTANCE_NAME`_USB_MEM            ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__MEM_DATA0)

    #define `$INSTANCE_NAME`_POWER_CTRL_REG      (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_POWER_CTRL)
    #define `$INSTANCE_NAME`_POWER_CTRL_PTR      ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_POWER_CTRL)

    #define `$INSTANCE_NAME`_CHGDET_CTRL_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_CHGDET_CTRL)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_CHGDET_CTRL)

    #define `$INSTANCE_NAME`_USBIO_CTRL_REG      (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_USBIO_CTRL)
    #define `$INSTANCE_NAME`_USBIO_CTRL_PTR      ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_USBIO_CTRL)

    #define `$INSTANCE_NAME`_FLOW_CTRL_REG       (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_FLOW_CTRL)
    #define `$INSTANCE_NAME`_FLOW_CTRL_PTR       ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_FLOW_CTRL)

    #define `$INSTANCE_NAME`_LPM_CTRL_REG        (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_LPM_CTRL)
    #define `$INSTANCE_NAME`_LPM_CTRL_PTR        ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_LPM_CTRL)

    #define `$INSTANCE_NAME`_LPM_STAT_REG        (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_LPM_STAT)
    #define `$INSTANCE_NAME`_LPM_STAT_PTR        ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_LPM_STAT)

    #define `$INSTANCE_NAME`_PHY_CONTROL_REG     (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_PHY_CONTROL)
    #define `$INSTANCE_NAME`_PHY_CONTROL_PTR     ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_PHY_CONTROL)

    #define `$INSTANCE_NAME`_INTR_SIE_REG        (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE)
    #define `$INSTANCE_NAME`_INTR_SIE_PTR        ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE)

    #define `$INSTANCE_NAME`_INTR_SIE_SET_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE_SET)
    #define `$INSTANCE_NAME`_INTR_SIE_SET_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE_SET)

    #define `$INSTANCE_NAME`_INTR_SIE_MASK_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE_MASK)
    #define `$INSTANCE_NAME`_INTR_SIE_MASK_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE_MASK)

    #define `$INSTANCE_NAME`_INTR_SIE_MASKED_REG (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE_MASKED)
    #define `$INSTANCE_NAME`_INTR_SIE_MASKED_PTR ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_SIE_MASKED)

    #define `$INSTANCE_NAME`_INTR_LVL_SEL_REG    (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_LVL_SEL)
    #define `$INSTANCE_NAME`_INTR_LVL_SEL_PTR    ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_LVL_SEL)

    #define `$INSTANCE_NAME`_INTR_CAUSE_HI_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_CAUSE_HI)
    #define `$INSTANCE_NAME`_INTR_CAUSE_HI_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_CAUSE_HI)

    #define `$INSTANCE_NAME`_INTR_CAUSE_LO_REG   (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_CAUSE_LO)
    #define `$INSTANCE_NAME`_INTR_CAUSE_LO_PTR   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_CAUSE_LO)

    #define `$INSTANCE_NAME`_INTR_CAUSE_MED_REG  (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_CAUSE_MED)
    #define `$INSTANCE_NAME`_INTR_CAUSE_MED_PTR  ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_INTR_CAUSE_MED)

    #define `$INSTANCE_NAME`_DFT_CTRL_REG        (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_DFT_CTRL)
    #define `$INSTANCE_NAME`_DFT_CTRL_PTR        ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_usb__USB_DFT_CTRL)

    #if (`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE)
        #if (`$INSTANCE_NAME`_VBUS_POWER_PAD_ENABLE)
            /* Vbus power pad pin is hard wired to P13[2] */
            #define `$INSTANCE_NAME`_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT13_PS)
            #define `$INSTANCE_NAME`_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT13_PS)
            #define `$INSTANCE_NAME`_VBUS_VALID         (0x04u)
        #else
            /* Vbus valid pin is hard wired to P0[0] */
            #define `$INSTANCE_NAME`_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT0_PS)
            #define `$INSTANCE_NAME`_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT0_PS)
            #define `$INSTANCE_NAME`_VBUS_VALID         (0x01u)
        #endif
    #endif /*(`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE) */

    #define `$INSTANCE_NAME`_BURSTEND_0_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND0_TR_OUTPUT)
    #define `$INSTANCE_NAME`_BURSTEND_1_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND1_TR_OUTPUT)
    #define `$INSTANCE_NAME`_BURSTEND_2_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND2_TR_OUTPUT)
    #define `$INSTANCE_NAME`_BURSTEND_3_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND3_TR_OUTPUT)
    #define `$INSTANCE_NAME`_BURSTEND_4_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND4_TR_OUTPUT)
    #define `$INSTANCE_NAME`_BURSTEND_5_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND5_TR_OUTPUT)
    #define `$INSTANCE_NAME`_BURSTEND_6_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND6_TR_OUTPUT)
    #define `$INSTANCE_NAME`_BURSTEND_7_TR_OUTPUT    (`$INSTANCE_NAME`_cy_m0s8_usb__BURSTEND7_TR_OUTPUT)
    
#else /* (CY_PSOC3 || CY_PSOC5LP) */

    /* `$INSTANCE_NAME`_PM_USB_CR0 */
    #define `$INSTANCE_NAME`_PM_USB_CR0_PTR     ( (reg8 *) CYREG_PM_USB_CR0)
    #define `$INSTANCE_NAME`_PM_USB_CR0_REG     (*(reg8 *) CYREG_PM_USB_CR0)

    /* `$INSTANCE_NAME`_PM_ACT/STBY_CFG */
    #define `$INSTANCE_NAME`_PM_ACT_CFG_PTR     ( (reg8 *) `$INSTANCE_NAME`_USB__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_PM_ACT_CFG_REG     (*(reg8 *) `$INSTANCE_NAME`_USB__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_PM_STBY_CFG_PTR    ( (reg8 *) `$INSTANCE_NAME`_USB__PM_STBY_CFG)
    #define `$INSTANCE_NAME`_PM_STBY_CFG_REG    (*(reg8 *) `$INSTANCE_NAME`_USB__PM_STBY_CFG)

    #if (!CY_PSOC5LP)
        #define `$INSTANCE_NAME`_USBIO_CR2_PTR  (  (reg8 *) `$INSTANCE_NAME`_USB__USBIO_CR2)
        #define `$INSTANCE_NAME`_USBIO_CR2_REG  (* (reg8 *) `$INSTANCE_NAME`_USB__USBIO_CR2)
    #endif /* (!CY_PSOC5LP) */

    /* `$INSTANCE_NAME`_USB_MEM - USB IP memory buffer */
    #define `$INSTANCE_NAME`_USB_MEM            ((reg8 *) CYDEV_USB_MEM_BASE)

    #if (`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE)
        #if (`$INSTANCE_NAME`_VBUS_MONITORING_INTERNAL)
            #define `$INSTANCE_NAME`_VBUS_STATUS_REG    (*(reg8 *) `$INSTANCE_NAME`_VBUS__PS)
            #define `$INSTANCE_NAME`_VBUS_STATUS_PTR    ( (reg8 *) `$INSTANCE_NAME`_VBUS__PS)
            #define `$INSTANCE_NAME`_VBUS_VALID         (`$INSTANCE_NAME`_VBUS__MASK)
        #else
            #define `$INSTANCE_NAME`_VBUS_STATUS_REG    (*(reg8 *) `$INSTANCE_NAME`_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define `$INSTANCE_NAME`_VBUS_STATUS_PTR    ( (reg8 *) `$INSTANCE_NAME`_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define `$INSTANCE_NAME`_VBUS_VALID         (`$INSTANCE_NAME`_Vbus_ps_sts_sts_reg__MASK)
        #endif /* (`$INSTANCE_NAME`_VBUS_MONITORING_INTERNAL) */
    #endif /*(`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE) */
#endif /* (CY_PSOC4) */


/***************************************
*       Interrupt source constants
***************************************/

#define `$INSTANCE_NAME`_DP_INTC_PRIORITY       `$INSTANCE_NAME`_dp_int__INTC_PRIOR_NUM
#define `$INSTANCE_NAME`_DP_INTC_VECT_NUM       `$INSTANCE_NAME`_dp_int__INTC_NUMBER

#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_DMA_AUTO_INTR_PRIO (0u)
    
    #define `$INSTANCE_NAME`_INTR_HI_PRIORITY   `$INSTANCE_NAME`_high_int__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_INTR_HI_VECT_NUM   `$INSTANCE_NAME`_high_int__INTC_NUMBER

    #define `$INSTANCE_NAME`_INTR_MED_PRIORITY  `$INSTANCE_NAME`_med_int__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_INTR_MED_VECT_NUM  `$INSTANCE_NAME`_med_int__INTC_NUMBER

    #define `$INSTANCE_NAME`_INTR_LO_PRIORITY   `$INSTANCE_NAME`_lo_int__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_INTR_LO_VECT_NUM   `$INSTANCE_NAME`_lo_int__INTC_NUMBER

    /* Interrupt sources in `$INSTANCE_NAME`_isrCallbacks[] table */
    #define `$INSTANCE_NAME`_SOF_INTR_NUM       (0u)
    #define `$INSTANCE_NAME`_BUS_RESET_INT_NUM  (1u)
    #define `$INSTANCE_NAME`_EP0_INTR_NUM       (2u)
    #define `$INSTANCE_NAME`_LPM_INTR_NUM       (3u)
    #define `$INSTANCE_NAME`_ARB_EP_INTR_NUM    (4u)
    #define `$INSTANCE_NAME`_EP1_INTR_NUM       (5u)
    #define `$INSTANCE_NAME`_EP2_INTR_NUM       (6u)
    #define `$INSTANCE_NAME`_EP3_INTR_NUM       (7u)
    #define `$INSTANCE_NAME`_EP4_INTR_NUM       (8u)
    #define `$INSTANCE_NAME`_EP5_INTR_NUM       (9u)
    #define `$INSTANCE_NAME`_EP6_INTR_NUM       (10u)
    #define `$INSTANCE_NAME`_EP7_INTR_NUM       (11u)
    #define `$INSTANCE_NAME`_EP8_INTR_NUM       (12u)

#else
    #define `$INSTANCE_NAME`_BUS_RESET_PRIOR    `$INSTANCE_NAME`_bus_reset__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_BUS_RESET_MASK     `$INSTANCE_NAME`_bus_reset__INTC_MASK
    #define `$INSTANCE_NAME`_BUS_RESET_VECT_NUM `$INSTANCE_NAME`_bus_reset__INTC_NUMBER

    #define `$INSTANCE_NAME`_SOF_PRIOR          `$INSTANCE_NAME`_sof_int__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_SOF_MASK           `$INSTANCE_NAME`_sof_int__INTC_MASK
    #define `$INSTANCE_NAME`_SOF_VECT_NUM       `$INSTANCE_NAME`_sof_int__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_0_PRIOR         `$INSTANCE_NAME`_ep_0__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_0_MASK          `$INSTANCE_NAME`_ep_0__INTC_MASK
    #define `$INSTANCE_NAME`_EP_0_VECT_NUM      `$INSTANCE_NAME`_ep_0__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_1_PRIOR         `$INSTANCE_NAME`_ep_1__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_1_MASK          `$INSTANCE_NAME`_ep_1__INTC_MASK
    #define `$INSTANCE_NAME`_EP_1_VECT_NUM      `$INSTANCE_NAME`_ep_1__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_2_PRIOR         `$INSTANCE_NAME`_ep_2__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_2_MASK          `$INSTANCE_NAME`_ep_2__INTC_MASK
    #define `$INSTANCE_NAME`_EP_2_VECT_NUM      `$INSTANCE_NAME`_ep_2__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_3_PRIOR         `$INSTANCE_NAME`_ep_3__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_3_MASK          `$INSTANCE_NAME`_ep_3__INTC_MASK
    #define `$INSTANCE_NAME`_EP_3_VECT_NUM      `$INSTANCE_NAME`_ep_3__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_4_PRIOR         `$INSTANCE_NAME`_ep_4__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_4_MASK          `$INSTANCE_NAME`_ep_4__INTC_MASK
    #define `$INSTANCE_NAME`_EP_4_VECT_NUM      `$INSTANCE_NAME`_ep_4__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_5_PRIOR         `$INSTANCE_NAME`_ep_5__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_5_MASK          `$INSTANCE_NAME`_ep_5__INTC_MASK
    #define `$INSTANCE_NAME`_EP_5_VECT_NUM      `$INSTANCE_NAME`_ep_5__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_6_PRIOR         `$INSTANCE_NAME`_ep_6__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_6_MASK          `$INSTANCE_NAME`_ep_6__INTC_MASK
    #define `$INSTANCE_NAME`_EP_6_VECT_NUM      `$INSTANCE_NAME`_ep_6__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_7_PRIOR         `$INSTANCE_NAME`_ep_7__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_7_MASK          `$INSTANCE_NAME`_ep_7__INTC_MASK
    #define `$INSTANCE_NAME`_EP_7_VECT_NUM      `$INSTANCE_NAME`_ep_7__INTC_NUMBER

    #define `$INSTANCE_NAME`_EP_8_PRIOR         `$INSTANCE_NAME`_ep_8__INTC_PRIOR_NUM
    #define `$INSTANCE_NAME`_EP_8_MASK          `$INSTANCE_NAME`_ep_8__INTC_MASK
    #define `$INSTANCE_NAME`_EP_8_VECT_NUM      `$INSTANCE_NAME`_ep_8__INTC_NUMBER

    /* Set ARB ISR priority 0 to be highest for all EPX ISRs. */
    #define `$INSTANCE_NAME`_ARB_PRIOR          (0u)
    #define `$INSTANCE_NAME`_ARB_MASK           `$INSTANCE_NAME`_arb_int__INTC_MASK
    #define `$INSTANCE_NAME`_ARB_VECT_NUM       `$INSTANCE_NAME`_arb_int__INTC_NUMBER
#endif /* (CY_PSOC4) */


/***************************************
*       Endpoint 0 offsets (Table 9-2)
***************************************/
#define `$INSTANCE_NAME`_bmRequestTypeReg      `$INSTANCE_NAME`_EP0_DR_BASE.epData[0u]
#define `$INSTANCE_NAME`_bRequestReg           `$INSTANCE_NAME`_EP0_DR_BASE.epData[1u]
#define `$INSTANCE_NAME`_wValueLoReg           `$INSTANCE_NAME`_EP0_DR_BASE.epData[2u]
#define `$INSTANCE_NAME`_wValueHiReg           `$INSTANCE_NAME`_EP0_DR_BASE.epData[3u]
#define `$INSTANCE_NAME`_wIndexLoReg           `$INSTANCE_NAME`_EP0_DR_BASE.epData[4u]
#define `$INSTANCE_NAME`_wIndexHiReg           `$INSTANCE_NAME`_EP0_DR_BASE.epData[5u]
#define `$INSTANCE_NAME`_wLengthLoReg          `$INSTANCE_NAME`_EP0_DR_BASE.epData[6u]
#define `$INSTANCE_NAME`_wLengthHiReg          `$INSTANCE_NAME`_EP0_DR_BASE.epData[7u]

/* Compatibility defines */
#define `$INSTANCE_NAME`_lengthLoReg           `$INSTANCE_NAME`_EP0_DR_BASE.epData[6u]
#define `$INSTANCE_NAME`_lengthHiReg           `$INSTANCE_NAME`_EP0_DR_BASE.epData[7u]


/***************************************
*       Register Constants
***************************************/

#define `$INSTANCE_NAME`_3500MV     (3500u)
#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_VDDD_MV    (CYDEV_VBUS_MV)
#else
    #define `$INSTANCE_NAME`_VDDD_MV    (CYDEV_VDDD_MV)
#endif /* (CY_PSOC4) */


/* `$INSTANCE_NAME`_USB_CLK */
#define `$INSTANCE_NAME`_USB_CLK_CSR_CLK_EN_POS (0u)
#define `$INSTANCE_NAME`_USB_CLK_CSR_CLK_EN     ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_USB_CLK_CSR_CLK_EN_POS))
#define `$INSTANCE_NAME`_USB_CLK_ENABLE         (`$INSTANCE_NAME`_USB_CLK_CSR_CLK_EN)

/* `$INSTANCE_NAME`_CR0 */
#define `$INSTANCE_NAME`_CR0_DEVICE_ADDRESS_POS     (0u)
#define `$INSTANCE_NAME`_CR0_ENABLE_POS             (7u)
#define `$INSTANCE_NAME`_CR0_DEVICE_ADDRESS_MASK    ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x7Fu << `$INSTANCE_NAME`_CR0_DEVICE_ADDRESS_POS))
#define `$INSTANCE_NAME`_CR0_ENABLE                 ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_CR0_ENABLE_POS))


/* `$INSTANCE_NAME`_CR1 */
#define `$INSTANCE_NAME`_CR1_REG_ENABLE_POS         (0u)
#define `$INSTANCE_NAME`_CR1_ENABLE_LOCK_POS        (1u)
#define `$INSTANCE_NAME`_CR1_BUS_ACTIVITY_POS       (2u)
#define `$INSTANCE_NAME`_CR1_TRIM_OFFSET_MSB_POS    (3u)
#define `$INSTANCE_NAME`_CR1_REG_ENABLE             ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_CR1_REG_ENABLE_POS))
#define `$INSTANCE_NAME`_CR1_ENABLE_LOCK            ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_CR1_ENABLE_LOCK_POS))
#define `$INSTANCE_NAME`_CR1_BUS_ACTIVITY           ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_CR1_BUS_ACTIVITY_POS))
#define `$INSTANCE_NAME`_CR1_TRIM_OFFSET_MSB        ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_CR1_TRIM_OFFSET_MSB_POS))

/* `$INSTANCE_NAME`_EPX_CNT */
#define `$INSTANCE_NAME`_EP0_CNT_DATA_TOGGLE        (0x80u)
#define `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE        (0x80u)
#define `$INSTANCE_NAME`_EPX_CNT0_MASK              (0x0Fu)
#define `$INSTANCE_NAME`_EPX_CNTX_MSB_MASK          (0x07u)
#define `$INSTANCE_NAME`_EPX_CNTX_ADDR_SHIFT        (0x04u)
#define `$INSTANCE_NAME`_EPX_CNTX_ADDR_OFFSET       (0x10u)
#define `$INSTANCE_NAME`_EPX_CNTX_CRC_COUNT         (0x02u)
#define `$INSTANCE_NAME`_EPX_DATA_BUF_MAX           (512u)

/* `$INSTANCE_NAME`_USBIO_CR0 */

#define `$INSTANCE_NAME`_USBIO_CR0_TEN              (0x80u)
#define `$INSTANCE_NAME`_USBIO_CR0_TSE0             (0x40u)
#define `$INSTANCE_NAME`_USBIO_CR0_TD               (0x20u)
#define `$INSTANCE_NAME`_USBIO_CR0_RD               (0x01u)

/* `$INSTANCE_NAME`_USBIO_CR1 */
#define `$INSTANCE_NAME`_USBIO_CR1_DM0_POS      (0u)
#define `$INSTANCE_NAME`_USBIO_CR1_DP0_POS      (1u)
#define `$INSTANCE_NAME`_USBIO_CR1_USBPUEN_POS  (2u)
#define `$INSTANCE_NAME`_USBIO_CR1_IOMODE_POS   (5u)
#define `$INSTANCE_NAME`_USBIO_CR1_DM0          ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_USBIO_CR1_DM0_POS))
#define `$INSTANCE_NAME`_USBIO_CR1_DP0          ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_USBIO_CR1_DP0_POS))
#define `$INSTANCE_NAME`_USBIO_CR1_USBPUEN      ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_USBIO_CR1_USBPUEN_POS))
#define `$INSTANCE_NAME`_USBIO_CR1_IOMODE       ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_USBIO_CR1_IOMODE_POS))

/* `$INSTANCE_NAME`_FASTCLK_IMO_CR */
#define `$INSTANCE_NAME`_FASTCLK_IMO_CR_USBCLK_ON   (0x40u)
#define `$INSTANCE_NAME`_FASTCLK_IMO_CR_XCLKEN      (0x20u)
#define `$INSTANCE_NAME`_FASTCLK_IMO_CR_FX2ON       (0x10u)

/* `$INSTANCE_NAME`_ARB_EPX_CFG */
#define `$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY_POS    (0u)
#define `$INSTANCE_NAME`_ARB_EPX_CFG_DMA_REQ_POS        (1u)
#define `$INSTANCE_NAME`_ARB_EPX_CFG_CRC_BYPASS_POS     (2u)
#define `$INSTANCE_NAME`_ARB_EPX_CFG_RESET_POS          (3u)
#define `$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY        ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY_POS))
#define `$INSTANCE_NAME`_ARB_EPX_CFG_DMA_REQ            ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_CFG_DMA_REQ_POS))
#define `$INSTANCE_NAME`_ARB_EPX_CFG_CRC_BYPASS         ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_CFG_CRC_BYPASS_POS))
#define `$INSTANCE_NAME`_ARB_EPX_CFG_RESET              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_CFG_RESET_POS))

/* `$INSTANCE_NAME`_ARB_EPX_INT / SR */
#define `$INSTANCE_NAME`_ARB_EPX_INT_IN_BUF_FULL_POS    (0u)
#define `$INSTANCE_NAME`_ARB_EPX_INT_DMA_GNT_POS        (1u)
#define `$INSTANCE_NAME`_ARB_EPX_INT_BUF_OVER_POS       (2u)
#define `$INSTANCE_NAME`_ARB_EPX_INT_BUF_UNDER_POS      (3u)
#define `$INSTANCE_NAME`_ARB_EPX_INT_ERR_INT_POS        (4u)
#define `$INSTANCE_NAME`_ARB_EPX_INT_IN_BUF_FULL        ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_INT_IN_BUF_FULL_POS))
#define `$INSTANCE_NAME`_ARB_EPX_INT_DMA_GNT            ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_INT_DMA_GNT_POS))
#define `$INSTANCE_NAME`_ARB_EPX_INT_BUF_OVER           ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_INT_BUF_OVER_POS))
#define `$INSTANCE_NAME`_ARB_EPX_INT_BUF_UNDER          ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_INT_BUF_UNDER_POS))
#define `$INSTANCE_NAME`_ARB_EPX_INT_ERR_INT            ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_INT_ERR_INT_POS))

#if (CY_PSOC4)
#define `$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN_POS     (5u)
#define `$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN         ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN_POS))
#endif /* (CY_PSOC4) */

/* Common arbiter interrupt sources for all PSoC devices. */
#define `$INSTANCE_NAME`_ARB_EPX_INT_COMMON    (`$INSTANCE_NAME`_ARB_EPX_INT_IN_BUF_FULL | \
                                                `$INSTANCE_NAME`_ARB_EPX_INT_DMA_GNT     | \
                                                `$INSTANCE_NAME`_ARB_EPX_INT_BUF_OVER    | \
                                                `$INSTANCE_NAME`_ARB_EPX_INT_BUF_UNDER   | \
                                                `$INSTANCE_NAME`_ARB_EPX_INT_ERR_INT)

#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_ARB_EPX_INT_ALL    (`$INSTANCE_NAME`_ARB_EPX_INT_COMMON | `$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN)
#else
    #define `$INSTANCE_NAME`_ARB_EPX_INT_ALL    (`$INSTANCE_NAME`_ARB_EPX_INT_COMMON)
#endif /* (CY_PSOC4) */

/* `$INSTANCE_NAME`_ARB_CFG */
#define `$INSTANCE_NAME`_ARB_CFG_AUTO_MEM_POS   (4u)
#define `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_POS    (5u)
#define `$INSTANCE_NAME`_ARB_CFG_CFG_CMP_POS    (7u)
#define `$INSTANCE_NAME`_ARB_CFG_AUTO_MEM       ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_CFG_AUTO_MEM_POS))
#define `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_MASK   ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x3u << `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_POS))
#define `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_NONE   ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x0u << `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_POS))
#define `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_MANUAL ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_POS))
#define `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_AUTO   ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x2u << `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_POS))
#define `$INSTANCE_NAME`_ARB_CFG_CFG_CMP        ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_CFG_CFG_CMP_POS))

/* `$INSTANCE_NAME`_DYN_RECONFIG */
#define `$INSTANCE_NAME`_DYN_RECONFIG_EP_SHIFT      (1u)
#define `$INSTANCE_NAME`_DYN_RECONFIG_ENABLE_POS    (0u)
#define `$INSTANCE_NAME`_DYN_RECONFIG_EPNO_POS      (1u)
#define `$INSTANCE_NAME`_DYN_RECONFIG_RDY_STS_POS   (4u)
#define `$INSTANCE_NAME`_DYN_RECONFIG_ENABLE        ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_DYN_RECONFIG_ENABLE_POS))
#define `$INSTANCE_NAME`_DYN_RECONFIG_EPNO_MASK     ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x7u << `$INSTANCE_NAME`_DYN_RECONFIG_EPNO_POS))
#define `$INSTANCE_NAME`_DYN_RECONFIG_RDY_STS       ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_DYN_RECONFIG_RDY_STS_POS))

/* `$INSTANCE_NAME`_ARB_INT */
#define `$INSTANCE_NAME`_ARB_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define `$INSTANCE_NAME`_ARB_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define `$INSTANCE_NAME`_ARB_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define `$INSTANCE_NAME`_ARB_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define `$INSTANCE_NAME`_ARB_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define `$INSTANCE_NAME`_ARB_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define `$INSTANCE_NAME`_ARB_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define `$INSTANCE_NAME`_ARB_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define `$INSTANCE_NAME`_ARB_INT_EP1_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP1_INTR_POS))
#define `$INSTANCE_NAME`_ARB_INT_EP2_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP2_INTR_POS))
#define `$INSTANCE_NAME`_ARB_INT_EP3_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP3_INTR_POS))
#define `$INSTANCE_NAME`_ARB_INT_EP4_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP4_INTR_POS))
#define `$INSTANCE_NAME`_ARB_INT_EP5_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP5_INTR_POS))
#define `$INSTANCE_NAME`_ARB_INT_EP6_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP6_INTR_POS))
#define `$INSTANCE_NAME`_ARB_INT_EP7_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP7_INTR_POS))
#define `$INSTANCE_NAME`_ARB_INT_EP8_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x1u << `$INSTANCE_NAME`_ARB_INT_EP8_INTR_POS))

/* `$INSTANCE_NAME`_SIE_INT */
#define `$INSTANCE_NAME`_SIE_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define `$INSTANCE_NAME`_SIE_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define `$INSTANCE_NAME`_SIE_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define `$INSTANCE_NAME`_SIE_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define `$INSTANCE_NAME`_SIE_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define `$INSTANCE_NAME`_SIE_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define `$INSTANCE_NAME`_SIE_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define `$INSTANCE_NAME`_SIE_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define `$INSTANCE_NAME`_SIE_INT_EP1_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP1_INTR_POS))
#define `$INSTANCE_NAME`_SIE_INT_EP2_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP2_INTR_POS))
#define `$INSTANCE_NAME`_SIE_INT_EP3_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP3_INTR_POS))
#define `$INSTANCE_NAME`_SIE_INT_EP4_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP4_INTR_POS))
#define `$INSTANCE_NAME`_SIE_INT_EP5_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP5_INTR_POS))
#define `$INSTANCE_NAME`_SIE_INT_EP6_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP6_INTR_POS))
#define `$INSTANCE_NAME`_SIE_INT_EP7_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP7_INTR_POS))
#define `$INSTANCE_NAME`_SIE_INT_EP8_INTR              ((`$UINT_TYPE`) ((`$UINT_TYPE`) 0x01u << `$INSTANCE_NAME`_SIE_INT_EP8_INTR_POS))

#if (CY_PSOC4)
    /* `$INSTANCE_NAME`_POWER_CTRL_REG */
    #define `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_POS       (0u)  /* [0] */
    #define `$INSTANCE_NAME`_POWER_CTRL_SUSPEND_POS              (2u)  /* [1] */
    #define `$INSTANCE_NAME`_POWER_CTRL_SUSPEND_DEL_POS          (3u)  /* [3] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ISOLATE_POS              (4u)  /* [4] */
    #define `$INSTANCE_NAME`_POWER_CTRL_CHDET_PWR_CTL_POS        (5u)  /* [5] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DM_PULLDOWN_POS   (25u) /* [25] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS (26u) /* [26] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_RCVR_POS          (27u) /* [27] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DPO_POS           (28u) /* [28] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DMO_POS           (29u) /* [29] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_CHGDET_POS        (30u) /* [30] */
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_POS               (31u) /* [31] */
    #define `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_MASK      ((uint32) 0x03u << `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_0         ((uint32) 0x00u << `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_1         ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_GPIO      ((uint32) 0x02u << `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_PHY       ((uint32) 0x03u << `$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_SUSPEND                  ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_SUSPEND_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_SUSPEND_DEL              ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_SUSPEND_DEL_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ISOLATE                  ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ISOLATE_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_CHDET_PWR_CTL_MASK       ((uint32) 0x03u << `$INSTANCE_NAME`_POWER_CTRL_CHDET_PWR_CTL_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DM_PULLDOWN       ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DM_PULLDOWN_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_VBUS_PULLDOWN     ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_RCVR              ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ENABLE_RCVR_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DPO               ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DPO_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DMO               ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DMO_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE_CHGDET            ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ENABLE_CHGDET_POS)
    #define `$INSTANCE_NAME`_POWER_CTRL_ENABLE                   ((uint32) 0x01u << `$INSTANCE_NAME`_POWER_CTRL_ENABLE_POS)

    /* `$INSTANCE_NAME`_CHGDET_CTRL_REG */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DP_POS        (0u)  /* [0] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DM_POS        (1u)  /* [1] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_EN_POS        (2u)  /* [2] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_REF_DP_POS         (3u)  /* [3] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_REF_DM_POS         (4u)  /* [4] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_REF_EN_POS         (5u)  /* [5] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_DCD_SRC_EN_POS     (6u)  /* [6] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_POS      (12u) /* [12] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_OUT_POS       (31u) /* [31] */
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DP            ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DP_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DM            ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DM_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_EN            ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_COMP_EN_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_REF_DP             ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_REF_DP_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_REF_DM             ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_REF_DM_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_REF_EN             ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_REF_EN_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_DCD_SRC_EN         ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_DCD_SRC_EN_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_MASK     ((uint32) 0x03u << `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_NORMAL   ((uint32) 0x00u << `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_VBG      ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_DONTUSE  ((uint32) 0x02u << `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_ADFTIN   ((uint32) 0x03u << `$INSTANCE_NAME`_CHGDET_CTRL_ADFT_CTRL_POS)
    #define `$INSTANCE_NAME`_CHGDET_CTRL_COMP_OUT           ((uint32) 0x01u << `$INSTANCE_NAME`_CHGDET_CTRL_COMP_OUT_POS)

    /* `$INSTANCE_NAME`_LPM_CTRL */
    #define `$INSTANCE_NAME`_LPM_CTRL_LPM_EN_POS        (0u)
    #define `$INSTANCE_NAME`_LPM_CTRL_LPM_ACK_RESP_POS  (1u)
    #define `$INSTANCE_NAME`_LPM_CTRL_NYET_EN_POS       (2u)
    #define `$INSTANCE_NAME`_LPM_CTRL_SUB_RESP_POS      (4u)
    #define `$INSTANCE_NAME`_LPM_CTRL_LPM_EN            ((uint32) 0x01u << `$INSTANCE_NAME`_LPM_CTRL_LPM_EN_POS)
    #define `$INSTANCE_NAME`_LPM_CTRL_LPM_ACK_RESP      ((uint32) 0x01u << `$INSTANCE_NAME`_LPM_CTRL_LPM_ACK_RESP_POS)
    #define `$INSTANCE_NAME`_LPM_CTRL_NYET_EN           ((uint32) 0x01u << `$INSTANCE_NAME`_LPM_CTRL_NYET_EN_POS)
    #define `$INSTANCE_NAME`_LPM_CTRL_ACK_NYET_MASK     ((uint32) 0x03u << `$INSTANCE_NAME`_LPM_CTRL_LPM_ACK_RESP_POS)
    #define `$INSTANCE_NAME`_LPM_CTRL_SUB_RESP          ((uint32) 0x01u << `$INSTANCE_NAME`_LPM_CTRL_SUB_RESP_POS)

    #define `$INSTANCE_NAME`_LPM_STAT_LPM_BESL_POS          (0u)
    #define `$INSTANCE_NAME`_LPM_STAT_LPM_REMOTE_WAKE_POS   (4u)
    #define `$INSTANCE_NAME`_LPM_STAT_LPM_BESL_MASK         ((uint32) 0x0Fu << `$INSTANCE_NAME`_LPM_STAT_LPM_BESL_POS)
    #define `$INSTANCE_NAME`_LPM_STAT_LPM_REMOTE_WAKE       ((uint32) 0x01u << `$INSTANCE_NAME`_LPM_STAT_LPM_REMOTE_WAKE_POS)

    /* `$INSTANCE_NAME`_INTR_SIE */
    #define `$INSTANCE_NAME`_INTR_SIE_SOF_INTR_POS          (0u) /* [0] Interrupt for USB SOF   */
    #define `$INSTANCE_NAME`_INTR_SIE_BUS_RESET_INTR_POS    (1u) /* [1] Interrupt for BUS RESET */
    #define `$INSTANCE_NAME`_INTR_SIE_EP0_INTR_POS          (2u) /* [2] Interrupt for EP0       */
    #define `$INSTANCE_NAME`_INTR_SIE_LPM_INTR_POS          (3u) /* [3] Interrupt for LPM       */
    #define `$INSTANCE_NAME`_INTR_SIE_RESUME_INTR_POS       (4u) /* [4] Interrupt for RESUME (not used by component) */
    #define `$INSTANCE_NAME`_INTR_SIE_SOF_INTR              ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_SIE_SOF_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_SIE_BUS_RESET_INTR        ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_SIE_BUS_RESET_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_SIE_EP0_INTR              ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_SIE_EP0_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_SIE_LPM_INTR              ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_SIE_LPM_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_SIE_RESUME_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_SIE_RESUME_INTR_POS)

    /* `$INSTANCE_NAME`_INTR_CAUSE_LO, MED and HI */
    #define `$INSTANCE_NAME`_INTR_CAUSE_SOF_INTR_POS       (0u)  /* [0] Interrupt status for USB SOF    */
    #define `$INSTANCE_NAME`_INTR_CAUSE_BUS_RESET_INTR_POS (1u)  /* [1] Interrupt status for USB BUS RSET */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP0_INTR_POS       (2u)  /* [2] Interrupt status for USB EP0    */
    #define `$INSTANCE_NAME`_INTR_CAUSE_LPM_INTR_POS       (3u)  /* [3] Interrupt status for USB LPM    */
    #define `$INSTANCE_NAME`_INTR_CAUSE_RESUME_INTR_POS    (4u)  /* [4] Interrupt status for USB RESUME */
    #define `$INSTANCE_NAME`_INTR_CAUSE_ARB_INTR_POS       (7u)  /* [7] Interrupt status for USB ARB    */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP1_INTR_POS       (8u)  /* [8] Interrupt status for USB EP1    */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP2_INTR_POS       (9u)  /* [9] Interrupt status for USB EP2    */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP3_INTR_POS       (10u) /* [10] Interrupt status for USB EP3   */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP4_INTR_POS       (11u) /* [11] Interrupt status for USB EP4   */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP5_INTR_POS       (12u) /* [12] Interrupt status for USB EP5   */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP6_INTR_POS       (13u) /* [13] Interrupt status for USB EP6   */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP7_INTR_POS       (14u) /* [14] Interrupt status for USB EP7   */
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP8_INTR_POS       (15u) /* [15] Interrupt status for USB EP8   */
    #define `$INSTANCE_NAME`_INTR_CAUSE_SOF_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_SOF_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_BUS_RESET_INTR     ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_BUS_RESET_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP0_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP0_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_LPM_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_LPM_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_RESUME_INTR        ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_RESUME_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_ARB_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_ARB_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP1_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP1_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP2_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP2_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP3_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP3_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP4_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP4_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP5_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP5_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP6_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP6_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP7_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP7_INTR_POS)
    #define `$INSTANCE_NAME`_INTR_CAUSE_EP8_INTR           ((uint32) 0x01u << `$INSTANCE_NAME`_INTR_CAUSE_EP8_INTR_POS)

    #define `$INSTANCE_NAME`_INTR_CAUSE_CTRL_INTR_MASK     (`$INSTANCE_NAME`_INTR_CAUSE_SOF_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_BUS_RESET_INTR | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP0_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_LPM_INTR)

    #define `$INSTANCE_NAME`_INTR_CAUSE_EP1_8_INTR_MASK    (`$INSTANCE_NAME`_INTR_CAUSE_EP1_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP2_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP3_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP4_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP5_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP6_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP7_INTR       | \
                                                            `$INSTANCE_NAME`_INTR_CAUSE_EP8_INTR)

    #define `$INSTANCE_NAME`_INTR_CAUSE_EP_INTR_SHIFT      (`$INSTANCE_NAME`_INTR_CAUSE_ARB_INTR_POS - \
                                                           (`$INSTANCE_NAME`_INTR_CAUSE_LPM_INTR_POS + 1u))
    #define `$INSTANCE_NAME`_INTR_CAUSE_SRC_COUNT          (13u)

    #define `$INSTANCE_NAME`_CHGDET_CTRL_PRIMARY    (`$INSTANCE_NAME`_CHGDET_CTRL_COMP_EN | \
                                                     `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DM | \
                                                     `$INSTANCE_NAME`_CHGDET_CTRL_REF_EN  | \
                                                     `$INSTANCE_NAME`_CHGDET_CTRL_REF_DP)

    #define `$INSTANCE_NAME`_CHGDET_CTRL_SECONDARY  (`$INSTANCE_NAME`_CHGDET_CTRL_COMP_EN | \
                                                     `$INSTANCE_NAME`_CHGDET_CTRL_COMP_DP | \
                                                     `$INSTANCE_NAME`_CHGDET_CTRL_REF_EN  | \
                                                     `$INSTANCE_NAME`_CHGDET_CTRL_REF_DM)

    #define `$INSTANCE_NAME`_CHGDET_CTRL_DEFAULT    (0x00000900u)


#else /* (CY_PSOC3 || CY_PSOC5LP) */
    #define `$INSTANCE_NAME`_PM_ACT_EN_FSUSB            `$INSTANCE_NAME`_USB__PM_ACT_MSK
    #define `$INSTANCE_NAME`_PM_STBY_EN_FSUSB           `$INSTANCE_NAME`_USB__PM_STBY_MSK
    #define `$INSTANCE_NAME`_PM_AVAIL_EN_FSUSBIO        (0x10u)

    #define `$INSTANCE_NAME`_PM_USB_CR0_REF_EN          (0x01u)
    #define `$INSTANCE_NAME`_PM_USB_CR0_PD_N            (0x02u)
    #define `$INSTANCE_NAME`_PM_USB_CR0_PD_PULLUP_N     (0x04u)
#endif /* (CY_PSOC4) */


/***************************************
*       Macros Definitions
***************************************/

#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_ClearSieInterruptSource(intMask) \
                do{ \
                    `$INSTANCE_NAME`_INTR_SIE_REG = (uint32) (intMask); \
                }while(0)
#else
    #define `$INSTANCE_NAME`_ClearSieInterruptSource(intMask) \
                do{ /* Does nothing. */ }while(0)
#endif /* (CY_PSOC4) */

#define `$INSTANCE_NAME`_ClearSieEpInterruptSource(intMask) \
            do{ \
                `$INSTANCE_NAME`_SIE_EP_INT_SR_REG = (`$UINT_TYPE`) (intMask); \
            }while(0)

#define `$INSTANCE_NAME`_GET_ACTIVE_IN_EP_CR0_MODE(epType)  (((epType) == `$INSTANCE_NAME`_EP_TYPE_ISOC) ? \
                                                                (`$INSTANCE_NAME`_MODE_ISO_IN) : (`$INSTANCE_NAME`_MODE_ACK_IN))

#define `$INSTANCE_NAME`_GET_ACTIVE_OUT_EP_CR0_MODE(epType) (((epType) == `$INSTANCE_NAME`_EP_TYPE_ISOC) ? \
                                                                (`$INSTANCE_NAME`_MODE_ISO_OUT) : (`$INSTANCE_NAME`_MODE_ACK_OUT))

#define `$INSTANCE_NAME`_GET_EP_TYPE(epNumber)  (`$INSTANCE_NAME`_EP[epNumber].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK)

#define `$INSTANCE_NAME`_GET_UINT16(hi, low)    (((uint16) ((uint16) (hi) << 8u)) | ((uint16) (low) & 0xFFu))


/***************************************
*    Initialization Register Settings
***************************************/

/* Clear device address and enable USB IP respond to USB traffic. */
#define `$INSTANCE_NAME`_DEFUALT_CR0    (`$INSTANCE_NAME`_CR0_ENABLE)

/* Arbiter configuration depends on memory management mode. */
#define `$INSTANCE_NAME`_DEFAULT_ARB_CFG    ((`$INSTANCE_NAME`_EP_MANAGEMENT_MANUAL) ? (`$INSTANCE_NAME`_ARB_CFG_DMA_CFG_NONE) : \
                                                ((`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL) ? \
                                                    (`$INSTANCE_NAME`_ARB_CFG_DMA_CFG_MANUAL) : \
                                                        (`$INSTANCE_NAME`_ARB_CFG_AUTO_MEM | `$INSTANCE_NAME`_ARB_CFG_DMA_CFG_AUTO)))

/* Enable arbiter interrupt for active endpoints only */
#define `$INSTANCE_NAME`_DEFAULT_ARB_INT_EN \
        ((`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA1_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP1_INTR_POS) | \
         (`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA2_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP2_INTR_POS) | \
         (`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA3_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP3_INTR_POS) | \
         (`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA4_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP4_INTR_POS) | \
         (`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA5_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP5_INTR_POS) | \
         (`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA6_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP6_INTR_POS) | \
         (`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA7_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP7_INTR_POS) | \
         (`$UINT_TYPE`) ((`$UINT_TYPE`) `$INSTANCE_NAME`_DMA8_ACTIVE << `$INSTANCE_NAME`_ARB_INT_EP8_INTR_POS))

/* Enable all SIE endpoints interrupts */
#define `$INSTANCE_NAME`_DEFAULT_SIE_EP_INT_EN  (`$INSTANCE_NAME`_SIE_INT_EP1_INTR | \
                                                 `$INSTANCE_NAME`_SIE_INT_EP2_INTR | \
                                                 `$INSTANCE_NAME`_SIE_INT_EP3_INTR | \
                                                 `$INSTANCE_NAME`_SIE_INT_EP4_INTR | \
                                                 `$INSTANCE_NAME`_SIE_INT_EP5_INTR | \
                                                 `$INSTANCE_NAME`_SIE_INT_EP6_INTR | \
                                                 `$INSTANCE_NAME`_SIE_INT_EP7_INTR | \
                                                 `$INSTANCE_NAME`_SIE_INT_EP8_INTR)

#define `$INSTANCE_NAME`_ARB_EPX_CFG_DEFAULT    (`$INSTANCE_NAME`_ARB_EPX_CFG_RESET | \
                                                 `$INSTANCE_NAME`_ARB_EPX_CFG_CRC_BYPASS)

/* Default EP arbiter interrupt source register */
#define `$INSTANCE_NAME`_ARB_EPX_INT_COMMON_MASK   (`$INSTANCE_NAME`_ARB_EPX_INT_IN_BUF_FULL | \
                                                    `$INSTANCE_NAME`_ARB_EPX_INT_BUF_OVER    | \
                                                    `$INSTANCE_NAME`_ARB_EPX_INT_BUF_UNDER   | \
                                                    `$INSTANCE_NAME`_ARB_EPX_INT_ERR_INT     | \
                                                    (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL ? `$INSTANCE_NAME`_ARB_EPX_INT_DMA_GNT : 0u))

#define `$INSTANCE_NAME`_CLEAR_REG      (0u)

#if (CY_PSOC4)
    /* Set USB lock option when IMO is locked to USB traffic. */
    #define `$INSTANCE_NAME`_DEFUALT_CR1    ((0u != CySysClkImoGetUsbLock()) ? (`$INSTANCE_NAME`_CR1_ENABLE_LOCK) : (0u))

    /* Recommended value is increased from 3 to 10 due to suppress glitch on  
     * RSE0 with USB2.0 hubs (LF CLK = 32kHz equal to 350us). */
    #define `$INSTANCE_NAME`_DEFUALT_BUS_RST_CNT  (10u)

    /* Select VBUS sources as: valid, PHY of GPIO, and clears isolate bit. */
    /* Application level must ensure that VBUS is valid valid to use. */
    #define `$INSTANCE_NAME`_DEFAULT_POWER_CTRL_VBUS    (`$INSTANCE_NAME`_POWER_CTRL_ENABLE_VBUS_PULLDOWN | \
                                                         ((!`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE) ? \
                                                            (`$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_1) : \
                                                                (`$INSTANCE_NAME`_VBUS_POWER_PAD_ENABLE ? \
                                                                    (`$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_PHY) : \
                                                                    (`$INSTANCE_NAME`_POWER_CTRL_VBUS_VALID_OVR_GPIO))))
    /* Enable USB IP. */
    #define `$INSTANCE_NAME`_DEFAULT_POWER_CTRL_PHY (`$INSTANCE_NAME`_POWER_CTRL_SUSPEND     | \
                                                     `$INSTANCE_NAME`_POWER_CTRL_SUSPEND_DEL | \
                                                     `$INSTANCE_NAME`_POWER_CTRL_ENABLE_RCVR | \
                                                     `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DPO  | \
                                                     `$INSTANCE_NAME`_POWER_CTRL_ENABLE_DMO  | \
                                                     `$INSTANCE_NAME`_POWER_CTRL_ENABLE)

    /* Assign interrupt between levels lo, med, hi. */
    #define `$INSTANCE_NAME`_DEFAULT_INTR_LVL_SEL   ((uint32) (`$INSTANCE_NAME`_INTR_LVL_SEL))

    /* Enable interrupt source in the INTR_SIE. The SOF is always disabled and EP0 is enabled. */
    #define `$INSTANCE_NAME`_DEFAULT_INTR_SIE_MASK \
                ((uint32) ((uint32) `$INSTANCE_NAME`_BUS_RESET_ISR_ACTIVE << `$INSTANCE_NAME`_INTR_SIE_BUS_RESET_INTR_POS) | \
                 (uint32) ((uint32) `$INSTANCE_NAME`_SOF_ISR_ACTIVE       << `$INSTANCE_NAME`_INTR_SIE_SOF_INTR_POS)       | \
                 (uint32) ((uint32) `$INSTANCE_NAME`_LPM_ACTIVE           << `$INSTANCE_NAME`_INTR_SIE_LPM_INTR_POS)       | \
                 (uint32) ((uint32) `$INSTANCE_NAME`_INTR_SIE_EP0_INTR))

    /* Arbiter interrupt sources */
    #define `$INSTANCE_NAME`_ARB_EPX_INT_MASK   (`$INSTANCE_NAME`_ARB_EPX_INT_COMMON_MASK | \
                                                (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO ? `$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN : 0u))

    /* Common DMA configuration */
    #define `$INSTANCE_NAME`_DMA_COMMON_CFG     (CYDMA_PULSE | CYDMA_ENTIRE_DESCRIPTOR | \
                                                 CYDMA_NON_PREEMPTABLE)


#else
    #define `$INSTANCE_NAME`_ARB_EPX_INT_MASK   (`$INSTANCE_NAME`_ARB_EPX_INT_COMMON_MASK)

    #define `$INSTANCE_NAME`_DEFUALT_CR1        (`$INSTANCE_NAME`_CR1_ENABLE_LOCK)

    /* Recommended value is 3 for LF CLK = 100kHz equal to 100us. */
    #define `$INSTANCE_NAME`_DEFUALT_BUS_RST_CNT    (10u)
#endif /* (CY_PSOC4) */

/*
* \addtogroup group_deprecated
* @{
*/

/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Renamed type definitions */
#define `$INSTANCE_NAME`_CODE CYCODE
#define `$INSTANCE_NAME`_FAR CYFAR
#if defined(__C51__) || defined(__CX51__)
    #define `$INSTANCE_NAME`_DATA data
    #define `$INSTANCE_NAME`_XDATA xdata
#else
    #define `$INSTANCE_NAME`_DATA
    #define `$INSTANCE_NAME`_XDATA
#endif /*  __C51__ */
#define `$INSTANCE_NAME`_NULL       NULL
/** @} deprecated */
/* Renamed structure fields */
#define wBuffOffset         buffOffset
#define wBufferSize         bufferSize
#define bStatus             status
#define wLength             length
#define wCount              count

/* Renamed global variable */
#define CurrentTD           `$INSTANCE_NAME`_currentTD
#define `$INSTANCE_NAME`_interfaceSetting_last       `$INSTANCE_NAME`_interfaceSettingLast

/* Renamed global constants */
#define `$INSTANCE_NAME`_DWR_VDDD_OPERATION         (`$INSTANCE_NAME`_DWR_POWER_OPERATION)

/* Renamed functions */
#define `$INSTANCE_NAME`_bCheckActivity             `$INSTANCE_NAME`_CheckActivity
#define `$INSTANCE_NAME`_bGetConfiguration          `$INSTANCE_NAME`_GetConfiguration
#define `$INSTANCE_NAME`_bGetInterfaceSetting       `$INSTANCE_NAME`_GetInterfaceSetting
#define `$INSTANCE_NAME`_bGetEPState                `$INSTANCE_NAME`_GetEPState
#define `$INSTANCE_NAME`_wGetEPCount                `$INSTANCE_NAME`_GetEPCount
#define `$INSTANCE_NAME`_bGetEPAckState             `$INSTANCE_NAME`_GetEPAckState
#define `$INSTANCE_NAME`_bRWUEnabled                `$INSTANCE_NAME`_RWUEnabled
#define `$INSTANCE_NAME`_bVBusPresent               `$INSTANCE_NAME`_VBusPresent

#define `$INSTANCE_NAME`_bConfiguration             `$INSTANCE_NAME`_configuration
#define `$INSTANCE_NAME`_bInterfaceSetting          `$INSTANCE_NAME`_interfaceSetting
#define `$INSTANCE_NAME`_bDeviceAddress             `$INSTANCE_NAME`_deviceAddress
#define `$INSTANCE_NAME`_bDeviceStatus              `$INSTANCE_NAME`_deviceStatus
#define `$INSTANCE_NAME`_bDevice                    `$INSTANCE_NAME`_device
#define `$INSTANCE_NAME`_bTransferState             `$INSTANCE_NAME`_transferState
#define `$INSTANCE_NAME`_bLastPacketSize            `$INSTANCE_NAME`_lastPacketSize

#define `$INSTANCE_NAME`_LoadEP                     `$INSTANCE_NAME`_LoadInEP
#define `$INSTANCE_NAME`_LoadInISOCEP               `$INSTANCE_NAME`_LoadInEP
#define `$INSTANCE_NAME`_EnableOutISOCEP            `$INSTANCE_NAME`_EnableOutEP

#define `$INSTANCE_NAME`_SetVector                  CyIntSetVector
#define `$INSTANCE_NAME`_SetPriority                CyIntSetPriority
#define `$INSTANCE_NAME`_EnableInt                  CyIntEnable

/* Replace with register access. */
#define `$INSTANCE_NAME`_bmRequestType      `$INSTANCE_NAME`_EP0_DR0_PTR
#define `$INSTANCE_NAME`_bRequest           `$INSTANCE_NAME`_EP0_DR1_PTR
#define `$INSTANCE_NAME`_wValue             `$INSTANCE_NAME`_EP0_DR2_PTR
#define `$INSTANCE_NAME`_wValueHi           `$INSTANCE_NAME`_EP0_DR3_PTR
#define `$INSTANCE_NAME`_wValueLo           `$INSTANCE_NAME`_EP0_DR2_PTR
#define `$INSTANCE_NAME`_wIndex             `$INSTANCE_NAME`_EP0_DR4_PTR
#define `$INSTANCE_NAME`_wIndexHi           `$INSTANCE_NAME`_EP0_DR5_PTR
#define `$INSTANCE_NAME`_wIndexLo           `$INSTANCE_NAME`_EP0_DR4_PTR
#define `$INSTANCE_NAME`_length             `$INSTANCE_NAME`_EP0_DR6_PTR
#define `$INSTANCE_NAME`_lengthHi           `$INSTANCE_NAME`_EP0_DR7_PTR
#define `$INSTANCE_NAME`_lengthLo           `$INSTANCE_NAME`_EP0_DR6_PTR

/* Rename VBUS monitoring registers. */
#if (CY_PSOC3 || CY_PSOC5LP)
    #if (`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE)
        #if (`$INSTANCE_NAME`_VBUS_MONITORING_INTERNAL)
            #define `$INSTANCE_NAME`_VBUS_DR_PTR    ( (reg8 *) `$INSTANCE_NAME`_VBUS__DR)
            #define `$INSTANCE_NAME`_VBUS_DR_REG    (*(reg8 *) `$INSTANCE_NAME`_VBUS__DR)
            #define `$INSTANCE_NAME`_VBUS_PS_PTR    ( (reg8 *) `$INSTANCE_NAME`_VBUS__PS)
            #define `$INSTANCE_NAME`_VBUS_PS_REG    (*(reg8 *) `$INSTANCE_NAME`_VBUS__PS)
            #define `$INSTANCE_NAME`_VBUS_MASK          `$INSTANCE_NAME`_VBUS__MASK
        #else
            #define `$INSTANCE_NAME`_VBUS_PS_PTR    ( (reg8 *) `$INSTANCE_NAME`_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define `$INSTANCE_NAME`_VBUS_MASK      (0x01u)
        #endif /* (`$INSTANCE_NAME`_VBUS_MONITORING_INTERNAL) */
    #endif /*(`$INSTANCE_NAME`_VBUS_MONITORING_ENABLE) */
        
    /* Pointer DIE structure in flash (8 bytes): Y and X location, wafer, lot msb, lot lsb, 
    *  work week, fab/year, minor. */
    #define `$INSTANCE_NAME`_DIE_ID             CYDEV_FLSHID_CUST_TABLES_BASE

     #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        #if (`$INSTANCE_NAME`_DMA1_ACTIVE)
            #define `$INSTANCE_NAME`_ep1_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep1__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep1_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA1_ACTIVE) */

        #if (`$INSTANCE_NAME`_DMA2_ACTIVE)
            #define `$INSTANCE_NAME`_ep2_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep2__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep2_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA2_ACTIVE) */

        #if (`$INSTANCE_NAME`_DMA3_ACTIVE)
            #define `$INSTANCE_NAME`_ep3_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep3__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep3_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA3_ACTIVE) */

        #if (`$INSTANCE_NAME`_DMA4_ACTIVE)
            #define `$INSTANCE_NAME`_ep4_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep4__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep4_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA4_ACTIVE) */

        #if (`$INSTANCE_NAME`_DMA5_ACTIVE)
            #define `$INSTANCE_NAME`_ep5_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep5__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep5_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA5_ACTIVE) */

        #if (`$INSTANCE_NAME`_DMA6_ACTIVE)
            #define `$INSTANCE_NAME`_ep6_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep6__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep6_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA6_ACTIVE) */

        #if (`$INSTANCE_NAME`_DMA7_ACTIVE)
            #define `$INSTANCE_NAME`_ep7_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep7__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep7_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA7_ACTIVE) */

        #if (`$INSTANCE_NAME`_DMA8_ACTIVE)
            #define `$INSTANCE_NAME`_ep8_TD_TERMOUT_EN  (`$INSTANCE_NAME`_ep8__TD_TERMOUT_EN)
        #else
            #define `$INSTANCE_NAME`_ep8_TD_TERMOUT_EN  (0u)
        #endif /* (`$INSTANCE_NAME`_DMA8_ACTIVE) */
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */   
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

/* Rename USB IP registers. */
#define `$INSTANCE_NAME`_ARB_CFG        `$INSTANCE_NAME`_ARB_CFG_PTR

#define `$INSTANCE_NAME`_ARB_EP1_CFG    `$INSTANCE_NAME`_ARB_EP1_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP1_INT_EN `$INSTANCE_NAME`_ARB_EP1_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP1_SR     `$INSTANCE_NAME`_ARB_EP1_SR_PTR

#define `$INSTANCE_NAME`_ARB_EP2_CFG    `$INSTANCE_NAME`_ARB_EP2_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP2_INT_EN `$INSTANCE_NAME`_ARB_EP2_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP2_SR     `$INSTANCE_NAME`_ARB_EP2_SR_PTR

#define `$INSTANCE_NAME`_ARB_EP3_CFG    `$INSTANCE_NAME`_ARB_EP3_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP3_INT_EN `$INSTANCE_NAME`_ARB_EP3_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP3_SR     `$INSTANCE_NAME`_ARB_EP3_SR_PTR

#define `$INSTANCE_NAME`_ARB_EP4_CFG    `$INSTANCE_NAME`_ARB_EP4_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP4_INT_EN `$INSTANCE_NAME`_ARB_EP4_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP4_SR     `$INSTANCE_NAME`_ARB_EP4_SR_PTR

#define `$INSTANCE_NAME`_ARB_EP5_CFG    `$INSTANCE_NAME`_ARB_EP5_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP5_INT_EN `$INSTANCE_NAME`_ARB_EP5_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP5_SR     `$INSTANCE_NAME`_ARB_EP5_SR_PTR

#define `$INSTANCE_NAME`_ARB_EP6_CFG    `$INSTANCE_NAME`_ARB_EP6_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP6_INT_EN `$INSTANCE_NAME`_ARB_EP6_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP6_SR     `$INSTANCE_NAME`_ARB_EP6_SR_PTR

#define `$INSTANCE_NAME`_ARB_EP7_CFG    `$INSTANCE_NAME`_ARB_EP7_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP7_INT_EN `$INSTANCE_NAME`_ARB_EP7_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP7_SR     `$INSTANCE_NAME`_ARB_EP7_SR_PTR

#define `$INSTANCE_NAME`_ARB_EP8_CFG    `$INSTANCE_NAME`_ARB_EP8_CFG_PTR
#define `$INSTANCE_NAME`_ARB_EP8_INT_EN `$INSTANCE_NAME`_ARB_EP8_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_EP8_SR     `$INSTANCE_NAME`_ARB_EP8_SR_PTR

#define `$INSTANCE_NAME`_ARB_INT_EN     `$INSTANCE_NAME`_ARB_INT_EN_PTR
#define `$INSTANCE_NAME`_ARB_INT_SR     `$INSTANCE_NAME`_ARB_INT_SR_PTR

#define `$INSTANCE_NAME`_ARB_RW1_DR     `$INSTANCE_NAME`_ARB_RW1_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW1_RA     `$INSTANCE_NAME`_ARB_RW1_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW1_RA_MSB `$INSTANCE_NAME`_ARB_RW1_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW1_WA     `$INSTANCE_NAME`_ARB_RW1_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW1_WA_MSB `$INSTANCE_NAME`_ARB_RW1_WA_MSB_PTR

#define `$INSTANCE_NAME`_ARB_RW2_DR     `$INSTANCE_NAME`_ARB_RW2_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW2_RA     `$INSTANCE_NAME`_ARB_RW2_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW2_RA_MSB `$INSTANCE_NAME`_ARB_RW2_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW2_WA     `$INSTANCE_NAME`_ARB_RW2_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW2_WA_MSB `$INSTANCE_NAME`_ARB_RW2_WA_MSB_PTR

#define `$INSTANCE_NAME`_ARB_RW3_DR     `$INSTANCE_NAME`_ARB_RW3_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW3_RA     `$INSTANCE_NAME`_ARB_RW3_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW3_RA_MSB `$INSTANCE_NAME`_ARB_RW3_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW3_WA     `$INSTANCE_NAME`_ARB_RW3_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW3_WA_MSB `$INSTANCE_NAME`_ARB_RW3_WA_MSB_PTR

#define `$INSTANCE_NAME`_ARB_RW4_DR     `$INSTANCE_NAME`_ARB_RW4_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW4_RA     `$INSTANCE_NAME`_ARB_RW4_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW4_RA_MSB `$INSTANCE_NAME`_ARB_RW4_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW4_WA     `$INSTANCE_NAME`_ARB_RW4_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW4_WA_MSB `$INSTANCE_NAME`_ARB_RW4_WA_MSB_PTR

#define `$INSTANCE_NAME`_ARB_RW5_DR     `$INSTANCE_NAME`_ARB_RW5_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW5_RA     `$INSTANCE_NAME`_ARB_RW5_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW5_RA_MSB `$INSTANCE_NAME`_ARB_RW5_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW5_WA     `$INSTANCE_NAME`_ARB_RW5_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW5_WA_MSB `$INSTANCE_NAME`_ARB_RW5_WA_MSB_PTR

#define `$INSTANCE_NAME`_ARB_RW6_DR     `$INSTANCE_NAME`_ARB_RW6_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW6_RA     `$INSTANCE_NAME`_ARB_RW6_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW6_RA_MSB `$INSTANCE_NAME`_ARB_RW6_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW6_WA     `$INSTANCE_NAME`_ARB_RW6_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW6_WA_MSB `$INSTANCE_NAME`_ARB_RW6_WA_MSB_PTR

#define `$INSTANCE_NAME`_ARB_RW7_DR     `$INSTANCE_NAME`_ARB_RW7_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW7_RA     `$INSTANCE_NAME`_ARB_RW7_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW7_RA_MSB `$INSTANCE_NAME`_ARB_RW7_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW7_WA     `$INSTANCE_NAME`_ARB_RW7_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW7_WA_MSB `$INSTANCE_NAME`_ARB_RW7_WA_MSB_PTR

#define `$INSTANCE_NAME`_ARB_RW8_DR     `$INSTANCE_NAME`_ARB_RW8_DR_PTR
#define `$INSTANCE_NAME`_ARB_RW8_RA     `$INSTANCE_NAME`_ARB_RW8_RA_PTR
#define `$INSTANCE_NAME`_ARB_RW8_RA_MSB `$INSTANCE_NAME`_ARB_RW8_RA_MSB_PTR
#define `$INSTANCE_NAME`_ARB_RW8_WA     `$INSTANCE_NAME`_ARB_RW8_WA_PTR
#define `$INSTANCE_NAME`_ARB_RW8_WA_MSB `$INSTANCE_NAME`_ARB_RW8_WA_MSB_PTR

#define `$INSTANCE_NAME`_BUF_SIZE       `$INSTANCE_NAME`_BUF_SIZE_PTR
#define `$INSTANCE_NAME`_BUS_RST_CNT    `$INSTANCE_NAME`_BUS_RST_CNT_PTR
#define `$INSTANCE_NAME`_CR0            `$INSTANCE_NAME`_CR0_PTR
#define `$INSTANCE_NAME`_CR1            `$INSTANCE_NAME`_CR1_PTR
#define `$INSTANCE_NAME`_CWA            `$INSTANCE_NAME`_CWA_PTR
#define `$INSTANCE_NAME`_CWA_MSB        `$INSTANCE_NAME`_CWA_MSB_PTR

#define `$INSTANCE_NAME`_DMA_THRES      `$INSTANCE_NAME`_DMA_THRES_PTR
#define `$INSTANCE_NAME`_DMA_THRES_MSB  `$INSTANCE_NAME`_DMA_THRES_MSB_PTR

#define `$INSTANCE_NAME`_EP_ACTIVE      `$INSTANCE_NAME`_EP_ACTIVE_PTR
#define `$INSTANCE_NAME`_EP_TYPE        `$INSTANCE_NAME`_EP_TYPE_PTR

#define `$INSTANCE_NAME`_EP0_CNT        `$INSTANCE_NAME`_EP0_CNT_PTR
#define `$INSTANCE_NAME`_EP0_CR         `$INSTANCE_NAME`_EP0_CR_PTR
#define `$INSTANCE_NAME`_EP0_DR0        `$INSTANCE_NAME`_EP0_DR0_PTR
#define `$INSTANCE_NAME`_EP0_DR1        `$INSTANCE_NAME`_EP0_DR1_PTR
#define `$INSTANCE_NAME`_EP0_DR2        `$INSTANCE_NAME`_EP0_DR2_PTR
#define `$INSTANCE_NAME`_EP0_DR3        `$INSTANCE_NAME`_EP0_DR3_PTR
#define `$INSTANCE_NAME`_EP0_DR4        `$INSTANCE_NAME`_EP0_DR4_PTR
#define `$INSTANCE_NAME`_EP0_DR5        `$INSTANCE_NAME`_EP0_DR5_PTR
#define `$INSTANCE_NAME`_EP0_DR6        `$INSTANCE_NAME`_EP0_DR6_PTR
#define `$INSTANCE_NAME`_EP0_DR7        `$INSTANCE_NAME`_EP0_DR7_PTR

#define `$INSTANCE_NAME`_OSCLK_DR0      `$INSTANCE_NAME`_OSCLK_DR0_PTR
#define `$INSTANCE_NAME`_OSCLK_DR1      `$INSTANCE_NAME`_OSCLK_DR1_PTR

#define `$INSTANCE_NAME`_PM_ACT_CFG     `$INSTANCE_NAME`_PM_ACT_CFG_PTR
#define `$INSTANCE_NAME`_PM_STBY_CFG    `$INSTANCE_NAME`_PM_STBY_CFG_PTR

#define `$INSTANCE_NAME`_SIE_EP_INT_EN  `$INSTANCE_NAME`_SIE_EP_INT_EN_PTR
#define `$INSTANCE_NAME`_SIE_EP_INT_SR  `$INSTANCE_NAME`_SIE_EP_INT_SR_PTR

#define `$INSTANCE_NAME`_SIE_EP1_CNT0   `$INSTANCE_NAME`_SIE_EP1_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP1_CNT1   `$INSTANCE_NAME`_SIE_EP1_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP1_CR0    `$INSTANCE_NAME`_SIE_EP1_CR0_PTR

#define `$INSTANCE_NAME`_SIE_EP2_CNT0   `$INSTANCE_NAME`_SIE_EP2_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP2_CNT1   `$INSTANCE_NAME`_SIE_EP2_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP2_CR0    `$INSTANCE_NAME`_SIE_EP2_CR0_PTR

#define `$INSTANCE_NAME`_SIE_EP3_CNT0   `$INSTANCE_NAME`_SIE_EP3_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP3_CNT1   `$INSTANCE_NAME`_SIE_EP3_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP3_CR0    `$INSTANCE_NAME`_SIE_EP3_CR0_PTR

#define `$INSTANCE_NAME`_SIE_EP4_CNT0   `$INSTANCE_NAME`_SIE_EP4_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP4_CNT1   `$INSTANCE_NAME`_SIE_EP4_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP4_CR0    `$INSTANCE_NAME`_SIE_EP4_CR0_PTR

#define `$INSTANCE_NAME`_SIE_EP5_CNT0   `$INSTANCE_NAME`_SIE_EP5_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP5_CNT1   `$INSTANCE_NAME`_SIE_EP5_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP5_CR0    `$INSTANCE_NAME`_SIE_EP5_CR0_PTR

#define `$INSTANCE_NAME`_SIE_EP6_CNT0   `$INSTANCE_NAME`_SIE_EP6_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP6_CNT1   `$INSTANCE_NAME`_SIE_EP6_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP6_CR0    `$INSTANCE_NAME`_SIE_EP6_CR0_PTR

#define `$INSTANCE_NAME`_SIE_EP7_CNT0   `$INSTANCE_NAME`_SIE_EP7_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP7_CNT1   `$INSTANCE_NAME`_SIE_EP7_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP7_CR0    `$INSTANCE_NAME`_SIE_EP7_CR0_PTR

#define `$INSTANCE_NAME`_SIE_EP8_CNT0   `$INSTANCE_NAME`_SIE_EP8_CNT0_PTR
#define `$INSTANCE_NAME`_SIE_EP8_CNT1   `$INSTANCE_NAME`_SIE_EP8_CNT1_PTR
#define `$INSTANCE_NAME`_SIE_EP8_CR0    `$INSTANCE_NAME`_SIE_EP8_CR0_PTR

#define `$INSTANCE_NAME`_SOF0           `$INSTANCE_NAME`_SOF0_PTR
#define `$INSTANCE_NAME`_SOF1           `$INSTANCE_NAME`_SOF1_PTR

#define `$INSTANCE_NAME`_USB_CLK_EN     `$INSTANCE_NAME`_USB_CLK_EN_PTR

#define `$INSTANCE_NAME`_USBIO_CR0      `$INSTANCE_NAME`_USBIO_CR0_PTR
#define `$INSTANCE_NAME`_USBIO_CR1      `$INSTANCE_NAME`_USBIO_CR1_PTR
#define `$INSTANCE_NAME`_USBIO_CR2      `$INSTANCE_NAME`_USBIO_CR2_PTR

#define `$INSTANCE_NAME`_DM_INP_DIS_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_Dm__INP_DIS)
#define `$INSTANCE_NAME`_DM_INP_DIS_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_Dm__INP_DIS)
#define `$INSTANCE_NAME`_DP_INP_DIS_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_Dp__INP_DIS)
#define `$INSTANCE_NAME`_DP_INP_DIS_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_Dp__INP_DIS)
#define `$INSTANCE_NAME`_DP_INTSTAT_PTR     ( (`$REG_SIZE` *) `$INSTANCE_NAME`_Dp__INTSTAT)
#define `$INSTANCE_NAME`_DP_INTSTAT_REG     (*(`$REG_SIZE` *) `$INSTANCE_NAME`_Dp__INTSTAT)
#define `$INSTANCE_NAME`_DM_MASK            `$INSTANCE_NAME`_Dm__0__MASK
#define `$INSTANCE_NAME`_DP_MASK            `$INSTANCE_NAME`_Dp__0__MASK

#define USBFS_SIE_EP_INT_EP1_MASK        (0x01u)
#define USBFS_SIE_EP_INT_EP2_MASK        (0x02u)
#define USBFS_SIE_EP_INT_EP3_MASK        (0x04u)
#define USBFS_SIE_EP_INT_EP4_MASK        (0x08u)
#define USBFS_SIE_EP_INT_EP5_MASK        (0x10u)
#define USBFS_SIE_EP_INT_EP6_MASK        (0x20u)
#define USBFS_SIE_EP_INT_EP7_MASK        (0x40u)
#define USBFS_SIE_EP_INT_EP8_MASK        (0x80u)

#define `$INSTANCE_NAME`_ARB_EPX_SR_IN_BUF_FULL     (0x01u)
#define `$INSTANCE_NAME`_ARB_EPX_SR_DMA_GNT         (0x02u)
#define `$INSTANCE_NAME`_ARB_EPX_SR_BUF_OVER        (0x04u)
#define `$INSTANCE_NAME`_ARB_EPX_SR_BUF_UNDER       (0x08u)

#define `$INSTANCE_NAME`_ARB_EPX_INT_EN_ALL `$INSTANCE_NAME`_ARB_EPX_INT_ALL

#define `$INSTANCE_NAME`_CR1_BUS_ACTIVITY_SHIFT     (0x02u)

#define `$INSTANCE_NAME`_BUS_RST_COUNT      `$INSTANCE_NAME`_DEFUALT_BUS_RST_CNT

#define `$INSTANCE_NAME`_ARB_INT_MASK       `$INSTANCE_NAME`_DEFAULT_ARB_INT_EN

#if (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
    /* CY_PSOC3 interrupt registers */
    #define `$INSTANCE_NAME`_USB_ISR_PRIOR  ((reg8 *) CYDEV_INTC_PRIOR0)
    #define `$INSTANCE_NAME`_USB_ISR_SET_EN ((reg8 *) CYDEV_INTC_SET_EN0)
    #define `$INSTANCE_NAME`_USB_ISR_CLR_EN ((reg8 *) CYDEV_INTC_CLR_EN0)
    #define `$INSTANCE_NAME`_USB_ISR_VECT   ((cyisraddress *) CYDEV_INTC_VECT_MBASE)
#elif (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_PANTHER)
    /* CY_PSOC5LP interrupt registers */
    #define `$INSTANCE_NAME`_USB_ISR_PRIOR  ((reg8 *) CYDEV_NVIC_PRI_0)
    #define `$INSTANCE_NAME`_USB_ISR_SET_EN ((reg8 *) CYDEV_NVIC_SETENA0)
    #define `$INSTANCE_NAME`_USB_ISR_CLR_EN ((reg8 *) CYDEV_NVIC_CLRENA0)
    #define `$INSTANCE_NAME`_USB_ISR_VECT   ((cyisraddress *) CYDEV_NVIC_VECT_OFFSET)
#endif /*  CYDEV_CHIP_DIE_EXPECT */


#endif /* (CY_USBFS_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
