/***************************************************************************//**
* \file CY_BLE_config.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the function prototypes and constants for the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_BLE_CONFIG_H)
#define CY_BLE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "cyfitter.h"
#include "syslib/cy_syslib.h"


/**
* \addtogroup group_macros
* @{
*/


/***************************************
* Services Enable defines
***************************************/
`$Defines`

    
/***************************************
* API Constants
***************************************/

/** The component operating mode. */
#define CY_BLE_CONFIG_MODE                          (`$Mode`u)
#define CY_BLE_PROFILE                              (0u)
#define CY_BLE_HCI                                  (1u)

/** The core for the Host. For DUAL core device Controller will be compiled for different core. */
#define CY_BLE_CONFIG_HOST_CORE                     (`$HostCore`u)
/** The core for the Controller in HCI mode. */
#define CY_BLE_CONFIG_HCI_CONTR_CORE                (`$HciContrCore`u)

#define CY_BLE_CORE_CORTEX_M4                       (0u)
#define CY_BLE_CORE_CORTEX_M0P                      (1u)
#define CY_BLE_CORE_CORTEX_NONE                     (0xffu)

#define CY_BLE_HOST_CORE                            ((CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M4) ? \
                                                      CY_CPU_CORTEX_M4 : CY_CPU_CORTEX_M0P)

#define CY_BLE_HCI_CONTR_CORE                       ((CY_BLE_CONFIG_HCI_CONTR_CORE == CY_BLE_CORE_CORTEX_M4) ? \
                                                      CY_CPU_CORTEX_M4 : CY_CPU_CORTEX_M0P)

#define CY_BLE_CONTR_CORE                           ((CY_BLE_CONFIG_MODE == CY_BLE_HCI) ? CY_BLE_HCI_CONTR_CORE : \
                                                        ((CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M0P) ? \
                                                        CY_CPU_CORTEX_M4 : CY_CPU_CORTEX_M0P))

#define CY_BLE_MODE_PROFILE                         ((CY_BLE_CONFIG_MODE == CY_BLE_PROFILE) && (CY_BLE_HOST_CORE))
#define CY_BLE_MODE_HCI                             ((CY_BLE_CONFIG_MODE == CY_BLE_HCI) && (CY_BLE_HCI_CONTR_CORE))

#define CY_BLE_CONFIG_EXT_PA_ENABLED                ((`$EnableExternalPaLnaOutput`u | \
                                                      `$EnableExternalPaTxOutput`u | \
                                                      `$EnableExternalLnaRxOutput`u) != 0u)

/* Indicates whether deep sleep mode is used */
#define CY_BLE_CONFIG_USE_DEEP_SLEEP                (`$UseDeepSleep`u)

/** Determines the internal stack mode. Used to switch the operation for debugging.
    - ReleaseMode - Host and Controller with software interface.
    - DebugMode - Host and Controller with IPC interface.
    - HostOnly - Host with UART interface.
    - HostContrUart - Host and Controller with a UART interface.
*/
#define CY_BLE_CONFIG_STACK_MODE                    (`$StackMode`u)
#define CY_BLE_CONFIG_STACK_HOST_ONLY               (1u)
#define CY_BLE_CONFIG_STACK_DEBUG                   (2u)
#define CY_BLE_CONFIG_STACK_RELEASE                 (3u)
#define CY_BLE_CONFIG_STACK_DEBUG_UART              (4u)
#define CY_BLE_CONFIG_STACK_HOST_IPC                (5u)

#define CY_BLE_CONFIG_STACK_MODE_CONTR_UART         ((CY_BLE_MODE_HCI) || \
                                                    ((CY_BLE_CONFIG_MODE == CY_BLE_PROFILE) && \
                                                    (CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG_UART) && \
                                                        CY_BLE_CONTR_CORE)) 

#define CY_BLE_CONFIG_STACK_MODE_HOST_UART          ((CY_BLE_MODE_PROFILE) && \
                                                    (((CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_HOST_ONLY) || \
                                                     (CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG_UART)) && \
                                                        CY_BLE_HOST_CORE))

#define CY_BLE_CONFIG_STACK_MODE_HOST_IPC           ((CY_BLE_MODE_PROFILE) && \
                                                    (((CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_HOST_IPC) || \
                                                     (CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG)) && \
                                                        CY_BLE_HOST_CORE))

#define CY_BLE_CONFIG_STACK_CONTR_CORE              ((CY_BLE_MODE_HCI) || \
                                                    ((CY_BLE_CONFIG_MODE == CY_BLE_PROFILE) && \
                                                    ((CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_RELEASE) && \
                                                        (CY_BLE_HOST_CORE)) || \
                                                    (((CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG) || \
                                                    (CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG_UART)) &&\
                                                        (CY_BLE_CONTR_CORE))))

#define CY_BLE_CONFIG_STACK_IPC_CONTR_CORE          ((CY_BLE_CONFIG_MODE == CY_BLE_PROFILE) && \
                                                    (CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG) && \
                                                    (CY_BLE_CONTR_CORE))

#define CY_BLE_CONFIG_CONTR_CORE                    ((CY_BLE_CONFIG_MODE == CY_BLE_HCI) ? \
                                                        CY_BLE_CONFIG_HCI_CONTR_CORE : \
                                                    ((CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_RELEASE) ? \
                                                        CY_BLE_CONFIG_HOST_CORE : \
                                                    (((CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG) || \
                                                     (CY_BLE_CONFIG_STACK_MODE == CY_BLE_CONFIG_STACK_DEBUG_UART)) ? \
                                                        ((CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M4) ? \
                                                            CY_BLE_CORE_CORTEX_M0P : CY_BLE_CORE_CORTEX_M4) : \
                                                        CY_BLE_CORE_CORTEX_NONE)) )

#define CY_BLE_HOST_CONTR_CORE				        (CY_BLE_MODE_PROFILE || CY_BLE_CONFIG_STACK_CONTR_CORE)	

#if(CY_BLE_CONFIG_STACK_CONTR_CORE) /* Check for the proper BLESS ISR configuration in the DWR  */
    
#if ((CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M4) && \
    (!defined `$INSTANCE_NAME`_bless_isr__INTC_CORTEXM4_ASSIGNED))
    #error Enable `$INSTANCE_NAME`_bless_isr interrupt for the ARM CM4 core in the interrupt configuration tab of \
        the Design-Wide Resources (DWR) file (project.cydwr)     
#endif /* (CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M4) */
#if ((CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M0P) && \
    (!defined `$INSTANCE_NAME`_bless_isr__INTC_CORTEXM0P_ASSIGNED))
    #error Enable `$INSTANCE_NAME`_bless_isr interrupt for the ARM CM0+ core in the interrupt configuration tab of \
        the Design-Wide Resources (DWR) file (project.cydwr)     
#endif /* CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M0P) */

#endif /* (CY_BLE_CONFIG_STACK_CONTR_CORE) */

#if(CY_BLE_CONFIG_STACK_MODE_CONTR_UART) /* Check for the proper UART ISR configuration in the DWR  */

#if((CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M4) && \
    (!defined `$INSTANCE_NAME`_uart_isr__INTC_CORTEXM4_ASSIGNED))
    #error Enable `$INSTANCE_NAME`_uart_isr interrupt for the ARM CM4 core in the interrupt configuration tab of \
        the Design-Wide Resources (DWR) file (project.cydwr)     
#endif /* CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M4 */
#if((CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M0P) && \
    (!defined `$INSTANCE_NAME`_uart_isr__INTC_CORTEXM0P_ASSIGNED))
    #error Enable `$INSTANCE_NAME`_uart_isr interrupt for the ARM CM0+ core in the interrupt configuration tab of \
        the Design-Wide Resources (DWR) file (project.cydwr)     
#endif /* CY_BLE_CONFIG_CONTR_CORE == CY_BLE_CORE_CORTEX_M0P */
    
#endif /* (CY_BLE_CONFIG_STACK_MODE_CONTR_UART) */

#if(CY_BLE_CONFIG_STACK_MODE_HOST_UART) /* Check for the proper HOST UART ISR configuration in the DWR  */

#if((CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M4) && \
    (!defined `$INSTANCE_NAME`_host_uart_isr__INTC_CORTEXM4_ASSIGNED))
    #error Enable `$INSTANCE_NAME`_host_uart_isr interrupt for the ARM CM4 core in the interrupt configuration tab of \
        the Design-Wide Resources (DWR) file (project.cydwr)     
#endif /* CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M4 */
#if((CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M0P) && \
    (!defined `$INSTANCE_NAME`_host_uart_isr__INTC_CORTEXM0P_ASSIGNED))
    #error Enable `$INSTANCE_NAME`_host_uart_isr interrupt for the ARM CM0+ core in the interrupt configuration tab of \
        the Design-Wide Resources (DWR) file (project.cydwr)     
#endif /* CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M0P */
    
#endif /* (CY_BLE_CONFIG_STACK_MODE_HOST_UART) */

/** The maximum number of BLE connections */
#define CY_BLE_CONFIG_CONN_COUNT                    (4u)
/** The number of BLE connections */
#define CY_BLE_CONFIG_GATTC_COUNT                   (`$GattClientInstCount`)
/** The number of GAP Peripheral configurations */
#define CY_BLE_CONFIG_GAP_PERIPHERAL_COUNT          (`$GapPeripheralCount`)
/** The number of GAP Broadcaster configurations */
#define CY_BLE_CONFIG_GAP_BROADCASTER_COUNT         (`$GapBroadcasterCount`)
/** The number of GAP Central configurations */
#define CY_BLE_CONFIG_GAP_CENTRAL_COUNT             (`$GapCentralCount`)
/** The number of GAP Observer configurations */
#define CY_BLE_CONFIG_GAP_OBSERVER_COUNT            (`$GapObserverCount`)
/** The number of Security configurations */
#define CY_BLE_CONFIG_AUTH_INFO_COUNT               (`$AuthInfoCount`)
/** LL Privacy 1.2 feature */
#define CY_BLE_CONFIG_ENABLE_LL_PRIVACY             (`$SecurityEnableLLPrivacy`)
/** LE 2 Mbps feature */
#define CY_BLE_CONFIG_ENABLE_PHY_UPDATE             (`$LE2Mbps`u)
/** The GAP security level */
#define CY_BLE_CONFIG_GAP_SECURITY_LEVEL            (`$SecurityLevel`)
#define CY_BLE_CONFIG_SHARING_MODE                  (`$SharingMode`u)
/** The GAP Role */
#define CY_BLE_CONFIG_GAP_ROLE                      (`$GAP_ROLE`)
/** The Bonding Requirement */
#define CY_BLE_CONFIG_BONDING_REQUIREMENT           (`$SecurityBonding`)
/** The maximum number of bonded devices to be supported by this device.  */
#define CY_BLE_CONFIG_MAX_BONDED_DEVICES            (`$MaxBondedDevices`u)
/** The maximum number of peer devices whose addresses should be resolved by this device. */
#define CY_BLE_CONFIG_MAX_RESOLVABLE_DEVICES        (`$MaxResolvableDevices`u)
/** The maximum number of devices that can be added to the whitelist. */
#define CY_BLE_CONFIG_MAX_WHITE_LIST_SIZE           (`$MaxWhitelistSize`u)

`$GapDefines`

/* Additional queue depth provided from the customizer  */
#define CY_BLE_CONFIG_ADD_Q_DEPTH_PER_CONN          (`$AddQdepthPerConn`u)

/** GATT MTU Size */
#define CY_BLE_CONFIG_GATT_MTU                      (`$MTUSize`)

/** GATT Maximum attribute length */
#define CY_BLE_CONFIG_GATT_DB_MAX_VALUE_LEN         (`$GattDBMaxValueLen`)

#define CY_BLE_GATT_DB_INDEX_COUNT                  (`$GattDBSize`)

/** The number of characteristics supporting a Reliable Write property */
#define CY_BLE_CONFIG_GATT_RELIABLE_CHAR_COUNT      (`$ReliableWriteCharCount`)
/** The total length of characteristics with Reliable Write property */
#define CY_BLE_CONFIG_GATT_RELIABLE_CHAR_LENGTH     (`$ReliableWriteCharLength`)

/** The parameter to enable an application to provide a dynamically allocated buffer for preparing a Write request.  */            
#define CY_BLE_CONFIG_GATT_ENABLE_EXTERNAL_PREP_WRITE_BUFF   (`$EnableExternalPrepWriteBuff`u)

/** The parameter to enable configuration of the L2CAP logical channels */
#define CY_BLE_CONFIG_L2CAP_ENABLE                  (`$EnableL2capLogicalChannels`u)
    
#if(CY_BLE_CONFIG_L2CAP_ENABLE != 0u)
    /** L2CAP MTU Size */
    #define CY_BLE_CONFIG_L2CAP_MTU                 (`$L2capMtuSize`u)
    /** L2CAP MPS Size */
    #define CY_BLE_CONFIG_L2CAP_MPS                 (`$L2capMpsSize`u)
    /** Number of L2CAP Logical channels */
    #define CY_BLE_CONFIG_L2CAP_LOGICAL_CHANNEL_COUNT        (`$L2capNumChannels`u) 
    /** Number of L2CAP PSMs */
    #define CY_BLE_CONFIG_L2CAP_PSM_COUNT           (`$L2capNumPsm`u)
#endif  /* CY_BLE_L2CAP_ENABLE != 0u */


#define CY_BLE_CONFIG_GATT_DB_ATT_VAL_COUNT         (`$AttValuesLenArraySize`)

/** Max Tx payload size */
#define CY_BLE_CONFIG_LL_MAX_TX_PAYLOAD_SIZE        (`$MaxTxPayloadSize`)
/** Max Rx payload size */
#define CY_BLE_CONFIG_LL_MAX_RX_PAYLOAD_SIZE        (`$MaxRxPayloadSize`)

/** GATT Role */
#define CY_BLE_CONFIG_GATT_ROLE                     (`$GATT_ROLE`)
#define CY_BLE_CONFIG_GATT_DB_CCCD_COUNT            (`$AttValueCCCDArraySize`)

/** Max unique services in the project */
#define CY_BLE_MAX_SRVI                             (`$ServiceCallbackCount`)


/***************************************
* API Constants for BLE services
* (using in CY_BLE_<service>.h)
***************************************/

/* HIDS */
/** The maximum supported count of HID services for the GATT Server role */
#define CY_BLE_CONFIG_HIDSS_SERVICE_COUNT           (`$HidsSCount`)
/** The maximum supported count of HID reports for the GATT Server role */
#define CY_BLE_CONFIG_HIDSS_REPORT_COUNT            (`$HidsSReportCount`)
    
/** The maximum supported count of HID services for the GATT Client role */
#define CY_BLE_CONFIG_HIDSC_SERVICE_COUNT           (`$HidsCCount`)
/** The maximum supported count of HID reports for the GATT Client role  */
#define CY_BLE_CONFIG_HIDSC_REPORT_COUNT            (`$HidsCReportCount`)

`$HidsServiceIndex`

`$HidsReportCharIndex`

/* BAS */
/** The maximum supported count of BAS services for the GATT Server role */
#define CY_BLE_CONFIG_BASS_SERVICE_COUNT            (`$BasSCount`)
/** The maximum supported count of BAS reports for the GATT Client role */
#define CY_BLE_CONFIG_BASC_SERVICE_COUNT            (`$BasCCount`)

`$BasServiceIndex`

/* ESS */
/** The maximum supported count of ESS characteristics for the GATT Client role */
#define CY_BLE_CONFIG_ES_TOTAL_CHAR_COUNT           (`$EsscCharCount`)

/* AIOS */
/** The maximum supported count of AIOS characteristics for the GATT Client role */
#define CY_BLE_CONFIG_AIO_TOTAL_CHAR_COUNT          (`$AioscCharCount`)

/* CUSTOM */
/** The maximum supported count of Custom services for the GATT Server role */
#define CY_BLE_CONFIG_CUSTOMS_SERVICE_COUNT         (`$CustomSCount`)
/** The maximum supported count of Custom services for the GATT Client role */
#define CY_BLE_CONFIG_CUSTOMC_SERVICE_COUNT         (`$CustomCCount`)
/** The maximum supported count of the Custom Service characteristics */
#define CY_BLE_CONFIG_CUSTOM_SERVICE_CHAR_COUNT     (`$CustomMaxCharacteristicCount`)
/** The maximum supported count of the Custom Service descriptors in one characteristic */
#define CY_BLE_CONFIG_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT  (`$CustomMaxDescriptorCount`)

/* Below are the indexes and handles of the defined Custom Services and their characteristics */
`$CustomDefines`

/** @} group_macros */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CY_BLE_CONFIG_H */

/* [] END OF FILE */
