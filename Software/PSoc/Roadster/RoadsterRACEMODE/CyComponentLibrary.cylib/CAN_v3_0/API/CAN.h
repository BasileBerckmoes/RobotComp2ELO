/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the CAN Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAN_`$INSTANCE_NAME`_H)
#define CY_CAN_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 `$INSTANCE_NAME`_initVar;

#define `$INSTANCE_NAME`_INT_ISR_DISABLE                (`$IntISRDisable`u)


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_ARB_LOST                       (`$ArbLost`u)
#define `$INSTANCE_NAME`_OVERLOAD                       (`$Overload`u)
#define `$INSTANCE_NAME`_BIT_ERR                        (`$BitError`u)
#define `$INSTANCE_NAME`_STUFF_ERR                      (`$StuffError`u)
#define `$INSTANCE_NAME`_ACK_ERR                        (`$AckError`u)
#define `$INSTANCE_NAME`_FORM_ERR                       (`$FormError`u)
#define `$INSTANCE_NAME`_CRC_ERR                        (`$CrcError`u)
#define `$INSTANCE_NAME`_BUS_OFF                        (`$BussOff`u)
#define `$INSTANCE_NAME`_RX_MSG_LOST                    (`$RxMsgLost`u)
#define `$INSTANCE_NAME`_TX_MESSAGE                     (`$TxMsg`u)
#define `$INSTANCE_NAME`_RX_MESSAGE                     (`$RxMsg`u)
#define `$INSTANCE_NAME`_ARB_LOST_USE_HELPER            (`$ArbLostUseHelper`u)
#define `$INSTANCE_NAME`_OVERLOAD_USE_HELPER            (`$OverloadUseHelper`u)
#define `$INSTANCE_NAME`_BIT_ERR_USE_HELPER             (`$BitErrorUseHelper`u)
#define `$INSTANCE_NAME`_STUFF_ERR_USE_HELPER           (`$StuffErrorUseHelper`u)
#define `$INSTANCE_NAME`_ACK_ERR_USE_HELPER             (`$AckErrorUseHelper`u)
#define `$INSTANCE_NAME`_FORM_ERR_USE_HELPER            (`$FormErrorUseHelper`u)
#define `$INSTANCE_NAME`_CRC_ERR_USE_HELPER             (`$CrcErrorUseHelper`u)
#define `$INSTANCE_NAME`_BUS_OFF_USE_HELPER             (`$BussOffUseHelper`u)
#define `$INSTANCE_NAME`_RX_MSG_LOST_USE_HELPER         (`$RxMsgLostUseHelper`u)
#define `$INSTANCE_NAME`_TX_MESSAGE_USE_HELPER          (`$TxMsgUseHelper`u)
#define `$INSTANCE_NAME`_RX_MESSAGE_USE_HELPER          (`$RxMsgUseHelper`u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define `$INSTANCE_NAME`_RTR_AUTO_MSG_SENT          (`$RTRAutomaticReply`u)
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO              (`$StuckAtZero`u)
    #define `$INSTANCE_NAME`_SST_FAILURE                (`$SSTError`u)

    #define `$INSTANCE_NAME`_RTR_MESSAGE_USE_HELPER     (`$RTRAutomaticReplyUseHelper`u)
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO_USE_HELPER   (`$StuckAtZeroUseHelper`u)
    #define `$INSTANCE_NAME`_SST_FAILURE_USE_HELPER     (`$SSTErrorUseHelper`u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define `$INSTANCE_NAME`_ADVANCED_INTERRUPT_CFG         (`$AdvancedInterruptConfig`u)

/* TX/RX Function Enable */
`$APITxRxFunctionEnable`

/***************************************
*        Data Struct Definition
***************************************/

/* Struct for DATA of BASIC CAN mailbox */
typedef struct
{
    uint8 byte[8u];
} `$INSTANCE_NAME`_DATA_BYTES_MSG;

/* Struct for DATA of CAN RX register */
typedef struct
{
    reg8 byte[8u];
} `$INSTANCE_NAME`_DATA_BYTES;

/* Struct for 32-bit CAN register */
typedef struct
{
    reg8 byte[4u];
} `$INSTANCE_NAME`_REG_32;

/* Struct for BASIC CAN mailbox to send messages */
typedef struct
{
    uint32 id;
    uint8 rtr;
    uint8 ide;
    uint8 dlc;
    uint8 irq;
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 sst;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
    `$INSTANCE_NAME`_DATA_BYTES_MSG *msg;
} `$INSTANCE_NAME`_TX_MSG;

/* Constant configuration of CAN RX */
typedef struct
{
    uint8 rxmailbox;
    uint32 rxcmd;
    uint32 rxamr;
    uint32 rxacr;
} `$INSTANCE_NAME`_RX_CFG;

/* Constant configuration of CAN TX */
typedef struct
{
    uint8 txmailbox;
    uint32 txcmd;
    uint32 txid;
} `$INSTANCE_NAME`_TX_CFG;

/* CAN RX registers */
typedef struct
{
    `$INSTANCE_NAME`_REG_32 rxcmd;
    `$INSTANCE_NAME`_REG_32 rxid;
    `$INSTANCE_NAME`_DATA_BYTES rxdata;
    `$INSTANCE_NAME`_REG_32 rxamr;
    `$INSTANCE_NAME`_REG_32 rxacr;
    `$INSTANCE_NAME`_REG_32 rxamrd;
    `$INSTANCE_NAME`_REG_32 rxacrd;
} `$INSTANCE_NAME`_RX_STRUCT;

/* CAN TX registers */
typedef struct
{
    `$INSTANCE_NAME`_REG_32 txcmd;
    `$INSTANCE_NAME`_REG_32 txid;
    `$INSTANCE_NAME`_DATA_BYTES txdata;
} `$INSTANCE_NAME`_TX_STRUCT;

/* Sleep Mode API Support */
typedef struct
{
    uint8  enableState;
    #if (CY_PSOC3 || CY_PSOC5)
        uint32 intSr;
        uint32 intEn;
        uint32 cmd;
        uint32 cfg;
    #endif /* CY_PSOC3 || CY_PSOC5 */
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8  `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
uint8  `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
uint8  `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
uint8  `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
uint8  `$INSTANCE_NAME`_GlobalIntEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_GlobalIntEnable")`;
uint8  `$INSTANCE_NAME`_GlobalIntDisable(void) `=ReentrantKeil($INSTANCE_NAME . "_GlobalIntDisable")`;
uint8  `$INSTANCE_NAME`_SetPreScaler(uint16 bitrate) `=ReentrantKeil($INSTANCE_NAME . "_SetPreScaler")`;
uint8  `$INSTANCE_NAME`_SetArbiter(uint8 arbiter) `=ReentrantKeil($INSTANCE_NAME . "_SetArbiter")`;
uint8  `$INSTANCE_NAME`_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                                `=ReentrantKeil($INSTANCE_NAME . "_SetTsegSample")`;
uint8  `$INSTANCE_NAME`_SetRestartType(uint8 reset) `=ReentrantKeil($INSTANCE_NAME . "_SetRestartType")`;
uint8  `$INSTANCE_NAME`_SetEdgeMode(uint8 edge) `=ReentrantKeil($INSTANCE_NAME . "_SetEdgeMode")`;
uint8  `$INSTANCE_NAME`_SetOpMode(uint8 opMode) `=ReentrantKeil($INSTANCE_NAME . "_SetOpMode")`;
uint8  `$INSTANCE_NAME`_RXRegisterInit(reg32 *regAddr, uint32 config)
                                            `=ReentrantKeil($INSTANCE_NAME . "_RXRegisterInit")`;
uint8  `$INSTANCE_NAME`_SetIrqMask(uint16 mask) `=ReentrantKeil($INSTANCE_NAME . "_SetIrqMask")`;
uint8  `$INSTANCE_NAME`_GetTXErrorFlag(void) `=ReentrantKeil($INSTANCE_NAME . "_GetTXErrorFlag")`;
uint8  `$INSTANCE_NAME`_GetRXErrorFlag(void) `=ReentrantKeil($INSTANCE_NAME . "_GetRXErrorFlag")`;
uint8  `$INSTANCE_NAME`_GetTXErrorCount(void) `=ReentrantKeil($INSTANCE_NAME . "_GetTXErrorCount")`;
uint8  `$INSTANCE_NAME`_GetRXErrorCount(void) `=ReentrantKeil($INSTANCE_NAME . "_GetRXErrorCount")`;
uint8  `$INSTANCE_NAME`_GetErrorState(void) `=ReentrantKeil($INSTANCE_NAME . "_GetErrorState")`;
void   `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void   `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void   `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void   `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;

#if (!(CY_PSOC3 || CY_PSOC5))
    uint8  `$INSTANCE_NAME`_SetSwapDataEndianness(uint8 swap);
    uint8  `$INSTANCE_NAME`_SetErrorCaptureRegisterMode(uint8 ecrMode);
    uint32 `$INSTANCE_NAME`_ReadErrorCaptureRegister(void);
    uint8  `$INSTANCE_NAME`_ArmErrorCaptureRegister(void);
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#if (`$INSTANCE_NAME`_ARB_LOST)
    void `$INSTANCE_NAME`_ArbLostIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_ArbLostIsr")`;
#endif /* `$INSTANCE_NAME`_ARB_LOST */
#if (`$INSTANCE_NAME`_OVERLOAD)
    void `$INSTANCE_NAME`_OvrLdErrorIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_OvrLdErrorIsr")`;
#endif /* `$INSTANCE_NAME`_OVERLOAD */
#if (`$INSTANCE_NAME`_BIT_ERR)
    void `$INSTANCE_NAME`_BitErrorIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_BitErrorIsr")`;
#endif /* `$INSTANCE_NAME`_BIT_ERR */
#if (`$INSTANCE_NAME`_STUFF_ERR)
    void `$INSTANCE_NAME`_BitStuffErrorIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_BitStuffErrorIsr")`;
#endif /* `$INSTANCE_NAME`_STUFF_ERR */
#if (`$INSTANCE_NAME`_ACK_ERR)
    void `$INSTANCE_NAME`_AckErrorIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_AckErrorIsr")`;
#endif /* `$INSTANCE_NAME`_ACK_ERR */
#if (`$INSTANCE_NAME`_FORM_ERR)
    void `$INSTANCE_NAME`_MsgErrorIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_MsgErrorIsr")`;
#endif /* `$INSTANCE_NAME`_FORM_ERR */
#if (`$INSTANCE_NAME`_CRC_ERR)
    void `$INSTANCE_NAME`_CrcErrorIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_CrcErrorIsr")`;
#endif /* `$INSTANCE_NAME`_CRC_ERR */
#if (`$INSTANCE_NAME`_BUS_OFF)
    void `$INSTANCE_NAME`_BusOffIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_BusOffIsr")`;
#endif /* `$INSTANCE_NAME`_BUS_OFF */
#if (`$INSTANCE_NAME`_RX_MSG_LOST)
    void `$INSTANCE_NAME`_MsgLostIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_MsgLostIsr")`;
#endif /* `$INSTANCE_NAME`_RX_MSG_LOST */
#if (`$INSTANCE_NAME`_TX_MESSAGE)
   void `$INSTANCE_NAME`_MsgTXIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_MsgTXIsr")`;
#endif /* `$INSTANCE_NAME`_TX_MESSAGE */
#if (`$INSTANCE_NAME`_RX_MESSAGE)
    void `$INSTANCE_NAME`_MsgRXIsr(void) `=ReentrantKeil($INSTANCE_NAME . "_MsgRXIsr")`;
#endif /* `$INSTANCE_NAME`_RX_MESSAGE */

#if (!(CY_PSOC3 || CY_PSOC5))
    #if (`$INSTANCE_NAME`_RTR_AUTO_MSG_SENT)
        void `$INSTANCE_NAME`_RtrAutoMsgSentIsr(void);
    #endif /* `$INSTANCE_NAME`_RTR_MESSAGE */
    #if (`$INSTANCE_NAME`_STUCK_AT_ZERO)
        void `$INSTANCE_NAME`_StuckAtZeroIsr(void);
    #endif /* `$INSTANCE_NAME`_STUCK_AT_ZERO */
    #if (`$INSTANCE_NAME`_SST_FAILURE)
        void `$INSTANCE_NAME`_SSTErrorIsr(void);
    #endif /* `$INSTANCE_NAME`_SST_ERROR */
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

uint8 `$INSTANCE_NAME`_RxBufConfig(const `$INSTANCE_NAME`_RX_CFG *rxConfig) \
                                   `=ReentrantKeil($INSTANCE_NAME . "_RxBufConfig")`;
uint8 `$INSTANCE_NAME`_TxBufConfig(const `$INSTANCE_NAME`_TX_CFG *txConfig) \
                                   `=ReentrantKeil($INSTANCE_NAME . "_TxBufConfig")`;
uint8 `$INSTANCE_NAME`_RxTxBuffersConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RxTxBuffersConfig")`;                                
uint8 `$INSTANCE_NAME`_SendMsg(const `$INSTANCE_NAME`_TX_MSG *message) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg")`;
void  `$INSTANCE_NAME`_TxCancel(uint8 bufferId) `=ReentrantKeil($INSTANCE_NAME . "_TxCancel")`;
void  `$INSTANCE_NAME`_ReceiveMsg(uint8 rxMailbox) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg")`;

#if (`$INSTANCE_NAME`_TX0_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name0`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name0`")`;
#endif /* `$INSTANCE_NAME`_TX0_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_TX1_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name1`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name1`")`;
#endif /* `$INSTANCE_NAME`_TX1_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_TX2_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name2`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name2`")`;
#endif /* `$INSTANCE_NAME`_TX2_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_TX3_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name3`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name3`")`;
#endif /* `$INSTANCE_NAME`_TX3_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_TX4_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name4`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name4`")`;
#endif /* `$INSTANCE_NAME`_TX4_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_TX5_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name5`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name5`")`;
#endif /* `$INSTANCE_NAME`_TX5_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_TX6_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name6`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name6`")`;
#endif /* `$INSTANCE_NAME`_TX6_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_TX7_FUNC_ENABLE)
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name7`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name7`")`;
#endif /* `$INSTANCE_NAME`_TX7_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX0_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name0`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name0`")`;
#endif /* `$INSTANCE_NAME`_RX0_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX1_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name1`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name1`")`;
#endif /* `$INSTANCE_NAME`_RX1_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX2_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name2`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name2`")`;
#endif /* `$INSTANCE_NAME`_RX2_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX3_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name3`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name3`")`;
#endif /* `$INSTANCE_NAME`_RX3_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX4_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name4`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name4`")`;
#endif /* `$INSTANCE_NAME`_RX4_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX5_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name5`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name5`")`;
#endif /* `$INSTANCE_NAME`_RX5_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX6_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name6`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name6`")`;
#endif /* `$INSTANCE_NAME`_RX6_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX7_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name7`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name7`")`;
#endif /* `$INSTANCE_NAME`_RX7_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX8_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name8`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name8`")`;
#endif /* `$INSTANCE_NAME`_RX8_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX9_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name9`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name9`")`;
#endif /* `$INSTANCE_NAME`_RX9_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX10_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name10`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name10`")`;
#endif /* `$INSTANCE_NAME`_RX10_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX11_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name11`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name11`")`;
#endif /* `$INSTANCE_NAME`_RX11_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX12_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name12`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name12`")`;
#endif /* `$INSTANCE_NAME`_RX12_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX13_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name13`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name13`")`;
#endif /* `$INSTANCE_NAME`_RX13_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX14_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name14`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name14`")`;
#endif /* `$INSTANCE_NAME`_RX14_FUNC_ENABLE */
#if (`$INSTANCE_NAME`_RX15_FUNC_ENABLE)
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name15`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name15`")`;
#endif /* `$INSTANCE_NAME`_RX15_FUNC_ENABLE */

#if(!`$INSTANCE_NAME`_INT_ISR_DISABLE)
    /* Interrupt handler */
    CY_ISR_PROTO(`$INSTANCE_NAME`_ISR);
#endif /* !`$INSTANCE_NAME`_INT_ISR_DISABLE */


/***************************************
*           API Constants
***************************************/

#if (!`$INSTANCE_NAME`_INT_ISR_DISABLE)
    /* Number of `$INSTANCE_NAME`_isr interrupt */
    #define `$INSTANCE_NAME`_ISR_NUMBER            ((uint8) `$INSTANCE_NAME``[isr]`_INTC_NUMBER)
    /* Priority of `$INSTANCE_NAME`_isr interrupt */
    #define `$INSTANCE_NAME`_ISR_PRIORITY          ((uint8) `$INSTANCE_NAME``[isr]`_INTC_PRIOR_NUM)
#endif /* !`$INSTANCE_NAME`_INT_ISR_DISABLE */

/* One bit time in CAN clock cycles */
#define `$INSTANCE_NAME`_ONE_BIT_TIME              ((`$INSTANCE_NAME`_BITRATE + 1u) * \
        ((`$INSTANCE_NAME`_CFG_REG_TSEG1 + 1u) + (`$INSTANCE_NAME`_CFG_REG_TSEG2 + 1u) + 1u))

/* Timeout for CAN state machine to switch operation mode to Run */
#define `$INSTANCE_NAME`_MODE_STATE_RUN_TIMEOUT    (12u * `$INSTANCE_NAME`_ONE_BIT_TIME)
/* Timeout for CAN state machine to switch operation mode to Stop */
#define `$INSTANCE_NAME`_MODE_STATE_STOP_TIMEOUT   (160u * `$INSTANCE_NAME`_ONE_BIT_TIME)

/* One or more parameters to function were invalid. */
#define `$INSTANCE_NAME`_FAIL                      (0x01u)
#define `$INSTANCE_NAME`_OUT_OF_RANGE              (0x02u)

#if (CY_PSOC3 || CY_PSOC5)
    /* PM_ACT_CFG (Active Power Mode CFG Register) */
    #define `$INSTANCE_NAME`_ACT_PWR_EN            (`$INSTANCE_NAME``[CanIP]`_PM_ACT_MSK)    /* Power enable mask */
    /* PM_STBY_CFG (Alternate Active (Standby) Power Mode CFG Register) */
    #define `$INSTANCE_NAME`_STBY_PWR_EN           (`$INSTANCE_NAME``[CanIP]`_PM_STBY_MSK)   /* Power enable mask */
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Number of TX and RX mailboxes */
#define `$INSTANCE_NAME`_NUMBER_OF_TX_MAILBOXES    (8u)
#define `$INSTANCE_NAME`_NUMBER_OF_RX_MAILBOXES    (16u)

/* Error status of CAN */
#define `$INSTANCE_NAME`_ERROR_ACTIVE              (0x00u)
#define `$INSTANCE_NAME`_ERROR_PASIVE              (0x01u)
#define `$INSTANCE_NAME`_ERROR_BUS_OFF             (0x10u)

/* Operation mode */
#define `$INSTANCE_NAME`_INITIAL_MODE              (0x00u)
#define `$INSTANCE_NAME`_STOP_MODE                 (0x00u)
#define `$INSTANCE_NAME`_ACTIVE_RUN_MODE           (0x01u)
#define `$INSTANCE_NAME`_LISTEN_ONLY_MODE          (0x02u)
#if (!(CY_PSOC3 || CY_PSOC5))
    #define `$INSTANCE_NAME`_INTERNAL_LOOP_BACK    (0x06u)
    #define `$INSTANCE_NAME`_EXTERNAL_LOOP_BACK    (0x04u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */
`$MailboxNamesDefines`

/***************************************
*    Initial Parameter Constants
***************************************/

/* General */
#define `$INSTANCE_NAME`_BITRATE                   (`$Bitrate`u)
#define `$INSTANCE_NAME`_CFG_REG_TSEG1             (`$Tseg1`u - 1u)
#define `$INSTANCE_NAME`_CFG_REG_TSEG2             (`$Tseg2`u - 1u)
#define `$INSTANCE_NAME`_CFG_REG_SJW               (`$Sjw`u - 1u)
#define `$INSTANCE_NAME`_SAMPLING_MODE             (`$Sm`u)
#define `$INSTANCE_NAME`_ARBITER                   (`$Arbiter`u)
#define `$INSTANCE_NAME`_RESET_TYPE                (`$Reset`u)
#define `$INSTANCE_NAME`_SYNC_EDGE                 (`$EdgeMode`u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define `$INSTANCE_NAME`_SWAP_DATA_END         (`$SwapDataByteEndianness`u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* Interrupts */
#define `$INSTANCE_NAME`_INT_ENABLE                (`$IntEnable`u)

#if (CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_INIT_INTERRUPT_MASK (((uint16) `$INSTANCE_NAME`_INT_ENABLE) | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_ARB_LOST    <<  `$INSTANCE_NAME`_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_OVERLOAD    <<  `$INSTANCE_NAME`_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_BIT_ERR     <<  `$INSTANCE_NAME`_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_STUFF_ERR   <<  `$INSTANCE_NAME`_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_ACK_ERR     <<  `$INSTANCE_NAME`_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_FORM_ERR    <<  `$INSTANCE_NAME`_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_CRC_ERR     << (`$INSTANCE_NAME`_ONE_BYTE_OFFSET          + \
                                                                     `$INSTANCE_NAME`_CRC_ERROR_SHIFT)))       | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_BUS_OFF     << (`$INSTANCE_NAME`_ONE_BYTE_OFFSET          + \
                                                                     `$INSTANCE_NAME`_BUS_OFF_SHIFT)))         | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_RX_MSG_LOST << (`$INSTANCE_NAME`_ONE_BYTE_OFFSET          + \
                                                                     `$INSTANCE_NAME`_RX_MSG_LOST_SHIFT)))     | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_TX_MESSAGE  << (`$INSTANCE_NAME`_ONE_BYTE_OFFSET          + \
                                                                     `$INSTANCE_NAME`_TX_MESSAGE_SHIFT)))      | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_RX_MESSAGE  << (`$INSTANCE_NAME`_ONE_BYTE_OFFSET          + \
                                                                     `$INSTANCE_NAME`_RX_MESSAGE_SHIFT))))
#else /* CY_PSOC4 */
    #define `$INSTANCE_NAME`_INIT_INTERRUPT_MASK    (((uint16) `$INSTANCE_NAME`_INT_ENABLE) | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_ARB_LOST    <<  `$INSTANCE_NAME`_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_OVERLOAD    <<  `$INSTANCE_NAME`_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_BIT_ERR     <<  `$INSTANCE_NAME`_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_STUFF_ERR   <<  `$INSTANCE_NAME`_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_ACK_ERR     <<  `$INSTANCE_NAME`_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_FORM_ERR    <<  `$INSTANCE_NAME`_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_CRC_ERR     <<  `$INSTANCE_NAME`_CRC_ERROR_SHIFT))        | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_BUS_OFF     <<  `$INSTANCE_NAME`_BUS_OFF_SHIFT))          | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_RX_MSG_LOST <<  `$INSTANCE_NAME`_RX_MSG_LOST_SHIFT))      | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_TX_MESSAGE  <<  `$INSTANCE_NAME`_TX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_RX_MESSAGE  <<  `$INSTANCE_NAME`_RX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_RTR_AUTO_MSG_SENT  << `$INSTANCE_NAME`_RTR_MSG_SHIFT))    | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_STUCK_AT_ZERO << `$INSTANCE_NAME`_STUCK_AT_ZERO_SHIFT))   | \
                ((uint16) ((uint16) `$INSTANCE_NAME`_SST_FAILURE   << `$INSTANCE_NAME`_SST_FAILURE_SHIFT)))
#endif /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*             Registers
***************************************/

#if (CY_PSOC3 || CY_PSOC5)
#define `$INSTANCE_NAME`_TX          ( (volatile `$INSTANCE_NAME`_TX_STRUCT XDATA *) `$INSTANCE_NAME``[CanIP]`_TX0_CMD)
#define `$INSTANCE_NAME`_RX          ( (volatile `$INSTANCE_NAME`_RX_STRUCT XDATA *) `$INSTANCE_NAME``[CanIP]`_RX0_CMD)
#define `$INSTANCE_NAME`_INT_SR_REG  (*(volatile `$INSTANCE_NAME`_REG_32 XDATA *) `$INSTANCE_NAME``[CanIP]`_CSR_INT_SR)
#define `$INSTANCE_NAME`_INT_SR_PTR  ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CSR_INT_SR)
#define `$INSTANCE_NAME`_INT_EN_REG  (*(volatile `$INSTANCE_NAME`_REG_32 XDATA *) `$INSTANCE_NAME``[CanIP]`_CSR_INT_EN)
#define `$INSTANCE_NAME`_INT_EN_PTR  ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CSR_INT_EN)
#define `$INSTANCE_NAME`_BUF_SR_REG  (*(volatile `$INSTANCE_NAME`_REG_32 XDATA *) `$INSTANCE_NAME``[CanIP]`_CSR_BUF_SR)
#define `$INSTANCE_NAME`_BUF_SR_PTR  ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CSR_BUF_SR)
#define `$INSTANCE_NAME`_ERR_SR_REG  (*(volatile `$INSTANCE_NAME`_REG_32 XDATA *) `$INSTANCE_NAME``[CanIP]`_CSR_ERR_SR)
#define `$INSTANCE_NAME`_ERR_SR_PTR  ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CSR_ERR_SR)
#define `$INSTANCE_NAME`_CMD_REG     (*(volatile `$INSTANCE_NAME`_REG_32 XDATA *) `$INSTANCE_NAME``[CanIP]`_CSR_CMD)
#define `$INSTANCE_NAME`_CMD_PTR     ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CSR_CMD)
#define `$INSTANCE_NAME`_CFG_REG     (*(volatile `$INSTANCE_NAME`_REG_32 XDATA *) `$INSTANCE_NAME``[CanIP]`_CSR_CFG)
#define `$INSTANCE_NAME`_CFG_PTR     ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CSR_CFG)

/* Power manager */
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG           (*(reg8 *) `$INSTANCE_NAME``[CanIP]`_PM_ACT_CFG)
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR           ( (reg8 *) `$INSTANCE_NAME``[CanIP]`_PM_ACT_CFG)
#define `$INSTANCE_NAME`_PM_STBY_CFG_REG          (*(reg8 *) `$INSTANCE_NAME``[CanIP]`_PM_STBY_CFG)
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR          ( (reg8 *) `$INSTANCE_NAME``[CanIP]`_PM_STBY_CFG)

#define `$INSTANCE_NAME`_RX_FIRST_REGISTER_PTR    ((reg32 *) `$INSTANCE_NAME``[CanIP]`_RX0_CMD)
#define `$INSTANCE_NAME`_RX_LAST_REGISTER_PTR     ((reg32 *) `$INSTANCE_NAME``[CanIP]`_RX15_ACRD)

#else /* CY_PSOC4 */
#define `$INSTANCE_NAME`_TX    ((volatile `$INSTANCE_NAME`_TX_STRUCT XDATA *) `$INSTANCE_NAME``[CanIP]`_CAN_TX0_CONTROL)
#define `$INSTANCE_NAME`_RX    ((volatile `$INSTANCE_NAME`_RX_STRUCT XDATA *) `$INSTANCE_NAME``[CanIP]`_CAN_RX0_CONTROL)
#define `$INSTANCE_NAME`_TX_REG                   (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_CAN_TX0_CONTROL)
#define `$INSTANCE_NAME`_TX_PTR                   ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CAN_TX0_CONTROL)
#define `$INSTANCE_NAME`_RX_REG                   (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_CAN_RX0_CONTROL)
#define `$INSTANCE_NAME`_RX_PTR                   ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CAN_RX0_CONTROL)
#define `$INSTANCE_NAME`_INT_SR_REG               (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_INT_STATUS)
#define `$INSTANCE_NAME`_INT_SR_PTR               ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_INT_STATUS)
#define `$INSTANCE_NAME`_INT_EN_REG               (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_INT_EBL)
#define `$INSTANCE_NAME`_INT_EN_PTR               ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_INT_EBL)
#define `$INSTANCE_NAME`_BUF_SR_REG               (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_BUFFER_STATUS)
#define `$INSTANCE_NAME`_BUF_SR_PTR               ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_BUFFER_STATUS)
#define `$INSTANCE_NAME`_ERR_SR_REG               (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_ERROR_STATUS)
#define `$INSTANCE_NAME`_ERR_SR_PTR               ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_ERROR_STATUS)
#define `$INSTANCE_NAME`_CNTL_REG                 (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_CNTL)
#define `$INSTANCE_NAME`_CNTL_PTR                 ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CNTL)
#define `$INSTANCE_NAME`_CMD_REG                  (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_COMMAND)
#define `$INSTANCE_NAME`_CMD_PTR                  ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_COMMAND)
#define `$INSTANCE_NAME`_CFG_REG                  (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_CONFIG)
#define `$INSTANCE_NAME`_CFG_PTR                  ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CONFIG)
#define `$INSTANCE_NAME`_ECR_REG                  (*(reg32 *) `$INSTANCE_NAME``[CanIP]`_ECR)
#define `$INSTANCE_NAME`_ECR_PTR                  ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_ECR)
#define `$INSTANCE_NAME`_RX_FIRST_REGISTER_PTR    ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CAN_RX0_CONTROL)
#define `$INSTANCE_NAME`_RX_LAST_REGISTER_PTR     ( (reg32 *) `$INSTANCE_NAME``[CanIP]`_CAN_RX15_ACR_DATA)

#define `$INSTANCE_NAME`_TX_DATA_LO_REG(i)        (*(reg32 *) (&`$INSTANCE_NAME`_TX[i].txdata))
#define `$INSTANCE_NAME`_TX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&`$INSTANCE_NAME`_TX[i].txdata) + \
                                                  `$INSTANCE_NAME`_DATA_HIGH_ADDR))
#define `$INSTANCE_NAME`_RX_DATA_LO_REG(i)        (*(reg32 *) (&`$INSTANCE_NAME`_RX[i].rxdata))
#define `$INSTANCE_NAME`_RX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&`$INSTANCE_NAME`_RX[i].rxdata) + \
                                                  `$INSTANCE_NAME`_DATA_HIGH_ADDR))
#endif /* (CY_PSOC3 || CY_PSOC5) */

#define `$INSTANCE_NAME`_TX_CMD_PTR(i)            ( (reg32 *) (&`$INSTANCE_NAME`_TX[i].txcmd))
#define `$INSTANCE_NAME`_TX_CMD_REG(i)            (*(reg32 *) (&`$INSTANCE_NAME`_TX[i].txcmd))
#define `$INSTANCE_NAME`_RX_CMD_PTR(i)            ( (reg32 *) (&`$INSTANCE_NAME`_RX[i].rxcmd))
#define `$INSTANCE_NAME`_RX_CMD_REG(i)            (*(reg32 *) (&`$INSTANCE_NAME`_RX[i].rxcmd))
#define `$INSTANCE_NAME`_RX_ID_PTR(i)             ( (reg32 *) (&`$INSTANCE_NAME`_RX[i].rxid))
#define `$INSTANCE_NAME`_RX_ID_REG(i)             (*(reg32 *) (&`$INSTANCE_NAME`_RX[i].rxid))
#define `$INSTANCE_NAME`_TX_ID_PTR(i)             ( (reg32 *) (&`$INSTANCE_NAME`_TX[i].txid))
#define `$INSTANCE_NAME`_TX_ID_REG(i)             (*(reg32 *) (&`$INSTANCE_NAME`_TX[i].txid))


/***************************************
*        Register Constants
***************************************/

/* Run/Stop mode */
#define `$INSTANCE_NAME`_MODE_STOP                (0x00u)
#define `$INSTANCE_NAME`_MODE_START               (0x01u)

/* Transmit buffer arbiter */
#define `$INSTANCE_NAME`_ROUND_ROBIN              (0x00u)
#define `$INSTANCE_NAME`_FIXED_PRIORITY           (0x01u)

/* Restart type */
#define `$INSTANCE_NAME`_MANUAL_RESTART           (0x00u)
#define `$INSTANCE_NAME`_AUTO_RESTART             (0x01u)

/* Sampling mode */
#define `$INSTANCE_NAME`_ONE_SAMPLE_POINT         (0x00u)
#define `$INSTANCE_NAME`_THREE_SAMPLE_POINTS      (0x01u)

/* Edge mode */
#define `$INSTANCE_NAME`_EDGE_R_TO_D              (0x00u)
#define `$INSTANCE_NAME`_BOTH_EDGES               (0x01u)

/* Extended identifier */
#define `$INSTANCE_NAME`_STANDARD_MESSAGE         (0x00u)
#define `$INSTANCE_NAME`_EXTENDED_MESSAGE         (0x01u)

/* Write Protect Mask for Basic and Full mailboxes */
#define `$INSTANCE_NAME`_TX_WPN_CLEAR           ((uint32) (~`$INSTANCE_NAME`_TX_WPN_SET))
#define `$INSTANCE_NAME`_RX_WPN_CLEAR           ((uint32) (~`$INSTANCE_NAME`_RX_WPN_SET))
#define `$INSTANCE_NAME`_TX_RSVD_MASK           ((uint32) 0x00FF00FFu)
#define `$INSTANCE_NAME`_TX_READ_BACK_MASK      (`$INSTANCE_NAME`_TX_WPN_CLEAR & `$INSTANCE_NAME`_TX_RSVD_MASK)
#define `$INSTANCE_NAME`_RX_READ_BACK_MASK      (`$INSTANCE_NAME`_RX_WPN_CLEAR & `$INSTANCE_NAME`_TX_RSVD_MASK)
#define `$INSTANCE_NAME`_RX_CMD_REG_WIDTH       (0x20u)

#if (CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (`$INSTANCE_NAME`_TWO_BYTE_OFFSET + `$INSTANCE_NAME`_TX_WPNH_SHIFT))))
    #define `$INSTANCE_NAME`_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (`$INSTANCE_NAME`_TWO_BYTE_OFFSET + `$INSTANCE_NAME`_RX_WPNH_SHIFT))))
#else  /* CY_PSOC4 */
    #define `$INSTANCE_NAME`_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_WPNH_SHIFT)))
    #define `$INSTANCE_NAME`_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_RX_WPNH_SHIFT)))

    /* CAN IP Block Enable */
    #define `$INSTANCE_NAME`_IP_ENABLE_SHIFT    (31u)
    #define `$INSTANCE_NAME`_IP_ENABLE          ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_IP_ENABLE_SHIFT))

    /* Error Capture register mode setting */
    #define `$INSTANCE_NAME`_ECR_FREE_RUNNING   (0x00u)
    #define `$INSTANCE_NAME`_ECR_ERROR_CAPTURE  (0x01u)

    /* Swap Endian */
    #define `$INSTANCE_NAME`_SWAP_ENDIANNESS_DISABLE  (0x00u)
    #define `$INSTANCE_NAME`_SWAP_ENDIANNESS_ENABLE   (0x01u)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* TX send message */
#define `$INSTANCE_NAME`_TX_REQUEST_PENDING     (0x01u)
#define `$INSTANCE_NAME`_RETRY_NUMBER           (0x03u)
#define `$INSTANCE_NAME`_SEND_MESSAGE_SHIFT     (0u)
#define `$INSTANCE_NAME`_SEND_MESSAGE           ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_SEND_MESSAGE_SHIFT))

/* Offsets to maintain bytes within uint32 */
#define `$INSTANCE_NAME`_ONE_BYTE_OFFSET        (8u)
#define `$INSTANCE_NAME`_TWO_BYTE_OFFSET        (16u)
#define `$INSTANCE_NAME`_THREE_BYTE_OFFSET      (24u)

#if (CY_PSOC3 || CY_PSOC5)
    /* Set/Clear bits macro for `$INSTANCE_NAME`_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_ACK_MSG_SHIFT       (0u)
    #define `$INSTANCE_NAME`_RX_ACK_MSG             ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_RTR_ABORT_SHIFT     (2u)
    #define `$INSTANCE_NAME`_RX_RTR_ABORT_MASK      ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_BUF_ENABLE_SHIFT    (3u)
    #define `$INSTANCE_NAME`_RX_BUF_ENABLE_MASK     ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_RTRREPLY_SHIFT      (4u)
    #define `$INSTANCE_NAME`_RX_RTRREPLY_MASK       ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_INT_ENABLE_SHIFT    (5u)
    #define `$INSTANCE_NAME`_RX_INT_ENABLE_MASK     ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_LINKING_SHIFT       (6u)
    #define `$INSTANCE_NAME`_RX_LINKING_MASK        ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_WPNL_SHIFT          (7u)
    #define `$INSTANCE_NAME`_RX_WPNL_MASK           ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_DLC_VALUE_SHIFT     (0u)
    #define `$INSTANCE_NAME`_RX_DLC_VALUE_MASK      ((uint8) ((uint8) 0x0Fu << `$INSTANCE_NAME`_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_IDE_SHIFT           (4u)
    #define `$INSTANCE_NAME`_RX_IDE_MASK            ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_WPNH_SHIFT          (7u)
    #define `$INSTANCE_NAME`_RX_WPNH_MASK           ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_WPNH_SHIFT))

    #define `$INSTANCE_NAME`_RX_ACK_MESSAGE(i)    (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_ACK_MSG)
    #define `$INSTANCE_NAME`_RX_RTR_ABORT_MESSAGE(i) \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_RTR_ABORT_MASK)
    #define `$INSTANCE_NAME`_RX_BUF_ENABLE(i)      \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_BUF_ENABLE_MASK)
    #define `$INSTANCE_NAME`_RX_BUF_DISABLE(i)     \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_RX_BUF_ENABLE_MASK))
    #define `$INSTANCE_NAME`_SET_RX_RTRREPLY(i)    \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_RTRREPLY_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_RTRREPLY(i)  \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_RX_RTRREPLY_MASK))
    #define `$INSTANCE_NAME`_RX_INT_ENABLE(i)      \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_INT_ENABLE_MASK)
    #define `$INSTANCE_NAME`_RX_INT_DISABLE(i)     \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_RX_INT_ENABLE_MASK))
    #define `$INSTANCE_NAME`_SET_RX_LINKING(i)     \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_LINKING_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_LINKING(i)   \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_RX_LINKING_MASK))
    #define `$INSTANCE_NAME`_SET_RX_WNPL(i)     (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_WPNL_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_WNPL(i)      \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_RX_WPNL_MASK))
    #define `$INSTANCE_NAME`_SET_RX_WNPH(i)     (`$INSTANCE_NAME`_RX[i].rxcmd.byte[2u] |= `$INSTANCE_NAME`_RX_WPNH_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_WNPH(i)      \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[2u] &= (uint8) (~`$INSTANCE_NAME`_RX_WPNH_MASK))
    #define `$INSTANCE_NAME`_GET_DLC(i)            \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[2u] & `$INSTANCE_NAME`_RX_DLC_VALUE_MASK)
    #define `$INSTANCE_NAME`_GET_RX_IDE(i)         ((uint8) \
            (`$INSTANCE_NAME`_RX[i].rxcmd.byte[2u] & `$INSTANCE_NAME`_RX_IDE_MASK) >> `$INSTANCE_NAME`_RX_IDE_SHIFT)
    #define `$INSTANCE_NAME`_GET_RX_ID(i)          ((`$INSTANCE_NAME`_GET_RX_IDE(i)) ? \
            (CY_GET_REG32(`$INSTANCE_NAME`_RX_ID_PTR(i)) >> `$INSTANCE_NAME`_SET_TX_ID_EXTENDED_MSG_SHIFT) : \
            (CY_GET_REG32(`$INSTANCE_NAME`_RX_ID_PTR(i)) >> `$INSTANCE_NAME`_SET_TX_ID_STANDARD_MSG_SHIFT))

    /* Set/Clear bits macro for `$INSTANCE_NAME`_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_ABORT_SHIFT        (1u)
    #define `$INSTANCE_NAME`_TX_ABORT_MASK         ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TRANSMIT_INT_ENABLE   (0x01u)
    #define `$INSTANCE_NAME`_TRANSMIT_INT_DISABLE  (0x00u)
    #define `$INSTANCE_NAME`_TX_INT_ENABLE_SHIFT   (2u)
    #define `$INSTANCE_NAME`_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_WPNL_SHIFT         (3u)
    #define `$INSTANCE_NAME`_TX_WPNL_MASK          ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_DLC_VALUE_SHIFT    (0u)
    #define `$INSTANCE_NAME`_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define `$INSTANCE_NAME`_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_DLC_UPPER_VALUE_SHIFT))
    #define `$INSTANCE_NAME`_TX_DLC_VALUE_MASK     ((uint8) ((uint8) 0x0Fu << `$INSTANCE_NAME`_TX_DLC_VALUE_SHIFT))
    #define `$INSTANCE_NAME`_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_IDE_SHIFT          (20u)
    #define `$INSTANCE_NAME`_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_RTR_SHIFT          (21u)
    #define `$INSTANCE_NAME`_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  `$INSTANCE_NAME`_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_WPNH_SHIFT         (7u)
    #define `$INSTANCE_NAME`_TX_WPNH_MASK          ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_TX_WPNH_SHIFT))

    #define `$INSTANCE_NAME`_TX_TRANSMIT_MESSAGE(i) \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[0u] |= `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST)
    #define `$INSTANCE_NAME`_TX_ABORT_MESSAGE(i)   \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[0u] = (`$INSTANCE_NAME`_TX[i].txcmd.byte[0u] & \
            (uint8) (~`$INSTANCE_NAME`_TX_TRANSMIT_REQUEST)) | `$INSTANCE_NAME`_TX_ABORT_MASK)
    #define `$INSTANCE_NAME`_TX_INT_ENABLE(i)      \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[0u] |= (uint8) `$INSTANCE_NAME`_TX_INT_ENABLE_MASK)
    #define `$INSTANCE_NAME`_TX_INT_DISABLE(i)     \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_TX_INT_ENABLE_MASK))
    #define `$INSTANCE_NAME`_SET_TX_WNPL(i)        \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[0u] |= `$INSTANCE_NAME`_TX_WPNL_MASK)
    #define `$INSTANCE_NAME`_CLEAR_TX_WNPL(i)      \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_TX_WPNL_MASK))
    #define `$INSTANCE_NAME`_SET_TX_IDE(i)         (`$INSTANCE_NAME`_TX[i].txcmd.byte[2u] |= \
            (uint8) (`$INSTANCE_NAME`_TX_IDE_MASK >> `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_CLEAR_TX_IDE(i)       (`$INSTANCE_NAME`_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~`$INSTANCE_NAME`_TX_IDE_MASK)) >> `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_SET_TX_RTR(i)         (`$INSTANCE_NAME`_TX[i].txcmd.byte[2u] |= \
            (uint8) (`$INSTANCE_NAME`_TX_RTR_MASK >> `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_CLEAR_TX_RTR(i)       (`$INSTANCE_NAME`_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~`$INSTANCE_NAME`_TX_RTR_MASK)) >> `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_SET_TX_WNPH(i)        \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[2u] |= `$INSTANCE_NAME`_TX_WPNH_MASK)
    #define `$INSTANCE_NAME`_CLEAR_TX_WNPH(i)      \
            (`$INSTANCE_NAME`_TX[i].txcmd.byte[2u] &= (uint8) (~`$INSTANCE_NAME`_TX_WPNH_MASK))

    #define `$INSTANCE_NAME`_RX_DATA_BYTE(mailbox, i) (`$INSTANCE_NAME`_RX[mailbox].rxdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
    #define `$INSTANCE_NAME`_TX_DATA_BYTE(mailbox, i) (`$INSTANCE_NAME`_TX[mailbox].txdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
#else  /* CY_PSOC4 */
    /* Set/Clear bits macro for `$INSTANCE_NAME`_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_ACK_MSG_SHIFT       (0u)
    #define `$INSTANCE_NAME`_RX_ACK_MSG             ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_RTR_ABORT_SHIFT     (2u)
    #define `$INSTANCE_NAME`_RX_RTR_ABORT_MASK      ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_BUF_ENABLE_SHIFT    (3u)
    #define `$INSTANCE_NAME`_RX_BUF_ENABLE_MASK     ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_RTRREPLY_SHIFT      (4u)
    #define `$INSTANCE_NAME`_RX_RTRREPLY_MASK       ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_INT_ENABLE_SHIFT    (5u)
    #define `$INSTANCE_NAME`_RX_INT_ENABLE_MASK     ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_LINKING_SHIFT       (6u)
    #define `$INSTANCE_NAME`_RX_LINKING_MASK        ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_WPNL_SHIFT          (7u)
    #define `$INSTANCE_NAME`_RX_WPNL_MASK           ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_DLC_VALUE_SHIFT     (16u)
    #define `$INSTANCE_NAME`_RX_DLC_VALUE_MASK      ((uint32) ((uint32) 0x0Fu << `$INSTANCE_NAME`_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_IDE_SHIFT           (20u)
    #define `$INSTANCE_NAME`_RX_IDE_MASK            ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define `$INSTANCE_NAME`_RX_WPNH_SHIFT          (23u)
    #define `$INSTANCE_NAME`_RX_WPNH_MASK           ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_WPNH_SHIFT))

    #define `$INSTANCE_NAME`_RX_ACK_MESSAGE(i)       (`$INSTANCE_NAME`_RX_CMD_REG(i) |= `$INSTANCE_NAME`_RX_ACK_MSG)
    #define `$INSTANCE_NAME`_RX_RTR_ABORT_MESSAGE(i) (`$INSTANCE_NAME`_RX_CMD_REG(i) |= \
                                                     `$INSTANCE_NAME`_RX_RTR_ABORT_MASK)
    #define `$INSTANCE_NAME`_RX_BUF_ENABLE(i)      (`$INSTANCE_NAME`_RX_CMD_REG(i) |= \
                                                   `$INSTANCE_NAME`_RX_BUF_ENABLE_MASK)
    #define `$INSTANCE_NAME`_RX_BUF_DISABLE(i)     (`$INSTANCE_NAME`_RX_CMD_REG(i) &= \
                                                   (uint32) (~`$INSTANCE_NAME`_RX_BUF_ENABLE_MASK))
    #define `$INSTANCE_NAME`_SET_RX_RTRREPLY(i)    (`$INSTANCE_NAME`_RX_CMD_REG(i) |= \
                                                   `$INSTANCE_NAME`_RX_RTRREPLY_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_RTRREPLY(i)  (`$INSTANCE_NAME`_RX_CMD_REG(i) &= \
                                                   (uint32) (~`$INSTANCE_NAME`_RX_RTRREPLY_MASK))
    #define `$INSTANCE_NAME`_RX_INT_ENABLE(i)      (`$INSTANCE_NAME`_RX_CMD_REG(i) |= \
                                                   `$INSTANCE_NAME`_RX_INT_ENABLE_MASK)
    #define `$INSTANCE_NAME`_RX_INT_DISABLE(i)     (`$INSTANCE_NAME`_RX_CMD_REG(i) &= \
                                                   (uint32) (~`$INSTANCE_NAME`_RX_INT_ENABLE_MASK))
    #define `$INSTANCE_NAME`_SET_RX_LINKING(i)     (`$INSTANCE_NAME`_RX_CMD_REG(i) |= `$INSTANCE_NAME`_RX_LINKING_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_LINKING(i)   (`$INSTANCE_NAME`_RX_CMD_REG(i) &= \
                                                   (uint32) (~`$INSTANCE_NAME`_RX_LINKING_MASK))
    #define `$INSTANCE_NAME`_SET_RX_WNPL(i)        (`$INSTANCE_NAME`_RX_CMD_REG(i) |= `$INSTANCE_NAME`_RX_WPNL_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_WNPL(i)      (`$INSTANCE_NAME`_RX_CMD_REG(i) &= \
                                                   (uint32) (~`$INSTANCE_NAME`_RX_WPNL_MASK))
    #define `$INSTANCE_NAME`_SET_RX_WNPH(i)        (`$INSTANCE_NAME`_RX_CMD_REG(i) |= `$INSTANCE_NAME`_RX_WPNH_MASK)
    #define `$INSTANCE_NAME`_CLEAR_RX_WNPH(i)      (`$INSTANCE_NAME`_RX_CMD_REG(i) &= \
                                                   (uint32) (~`$INSTANCE_NAME`_RX_WPNH_MASK))
    #define `$INSTANCE_NAME`_GET_DLC(i)            ((uint32) ((`$INSTANCE_NAME`_RX_CMD_REG(i) & \
            `$INSTANCE_NAME`_RX_DLC_VALUE_MASK) >> `$INSTANCE_NAME`_RX_DLC_VALUE_SHIFT))
    #define `$INSTANCE_NAME`_GET_RX_IDE(i)         ((uint32) ((`$INSTANCE_NAME`_RX_CMD_REG(i) & \
            `$INSTANCE_NAME`_RX_IDE_MASK) >> `$INSTANCE_NAME`_RX_IDE_SHIFT))
    #define `$INSTANCE_NAME`_GET_RX_ID(i)          ((`$INSTANCE_NAME`_GET_RX_IDE(i) == 0u) ? \
            (`$INSTANCE_NAME`_RX_ID_REG(i) >> `$INSTANCE_NAME`_SET_TX_ID_STANDARD_MSG_SHIFT) : \
            (`$INSTANCE_NAME`_RX_ID_REG(i) >> `$INSTANCE_NAME`_SET_TX_ID_EXTENDED_MSG_SHIFT))

    /* Set/Clear bits macro for `$INSTANCE_NAME`_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST   \
            ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_ABORT_SHIFT        (1u)
    #define `$INSTANCE_NAME`_TX_ABORT_MASK         ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TRANSMIT_INT_ENABLE   (0x01u)
    #define `$INSTANCE_NAME`_TRANSMIT_INT_DISABLE  (0x00u)
    #define `$INSTANCE_NAME`_TX_INT_ENABLE_SHIFT   (2u)
    #define `$INSTANCE_NAME`_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_WPNL_SHIFT         (3u)
    #define `$INSTANCE_NAME`_TX_WPNL_MASK          ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_DLC_VALUE_SHIFT    (0u)
    #define `$INSTANCE_NAME`_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define `$INSTANCE_NAME`_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_DLC_UPPER_VALUE_SHIFT))
    #define `$INSTANCE_NAME`_TX_DLC_VALUE_MASK     ((uint32) ((uint32) 0x0Fu << `$INSTANCE_NAME`_TX_DLC_VALUE_SHIFT))
    #define `$INSTANCE_NAME`_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_IDE_SHIFT          (20u)
    #define `$INSTANCE_NAME`_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << `$INSTANCE_NAME`_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_RTR_SHIFT          (21u)
    #define `$INSTANCE_NAME`_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  `$INSTANCE_NAME`_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define `$INSTANCE_NAME`_TX_WPNH_SHIFT         (23u)
    #define `$INSTANCE_NAME`_TX_WPNH_MASK          ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_TX_WPNH_SHIFT))

    #define `$INSTANCE_NAME`_TX_TRANSMIT_MESSAGE(i) \
            (`$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_TX_TRANSMIT_REQUEST)
    #define `$INSTANCE_NAME`_TX_ABORT_MESSAGE(i) (`$INSTANCE_NAME`_TX_CMD_REG(i) = (`$INSTANCE_NAME`_TX_CMD_REG(i) & \
            (uint32) (~`$INSTANCE_NAME`_TX_TRANSMIT_REQUEST)) | `$INSTANCE_NAME`_TX_ABORT_MASK)
    #define `$INSTANCE_NAME`_TX_INT_ENABLE(i)    (`$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_TX_INT_ENABLE_MASK)
    #define `$INSTANCE_NAME`_TX_INT_DISABLE(i)   (`$INSTANCE_NAME`_TX_CMD_REG(i) &= \
                                                 (uint32) (~`$INSTANCE_NAME`_TX_INT_ENABLE_MASK))
    #define `$INSTANCE_NAME`_SET_TX_WNPL(i)     (`$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_TX_WPNL_MASK)
    #define `$INSTANCE_NAME`_CLEAR_TX_WNPL(i)   \
            (`$INSTANCE_NAME`_TX_CMD_REG(i) &= (uint32)(~`$INSTANCE_NAME`_TX_WPNL_MASK))
    #define `$INSTANCE_NAME`_SET_TX_IDE(i)      (`$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_TX_IDE_MASK)
    #define `$INSTANCE_NAME`_CLEAR_TX_IDE(i)    \
            (`$INSTANCE_NAME`_TX_CMD_REG(i) &= (uint32) (~`$INSTANCE_NAME`_TX_IDE_MASK))
    #define `$INSTANCE_NAME`_SET_TX_RTR(i)      (`$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_TX_RTR_MASK)
    #define `$INSTANCE_NAME`_CLEAR_TX_RTR(i)    \
            (`$INSTANCE_NAME`_TX_CMD_REG(i) &= (uint32) (~`$INSTANCE_NAME`_TX_RTR_MASK))
    #define `$INSTANCE_NAME`_SET_TX_WNPH(i)     (`$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_TX_WPNH_MASK)
    #define `$INSTANCE_NAME`_CLEAR_TX_WNPH(i)   \
            (`$INSTANCE_NAME`_TX_CMD_REG(i) &= (uint32)(~`$INSTANCE_NAME`_TX_WPNH_MASK))

    #define `$INSTANCE_NAME`_DATA_HIGH_ADDR     (4u)
    #define `$INSTANCE_NAME`_DATA_BYTE_MASK     ((uint32) 0xFFu)

    #define `$INSTANCE_NAME`_RX_DATA_BYTE(mailbox, i) (((i) > 3u) ? \
            (uint8) (`$INSTANCE_NAME`_RX_DATA_HI_REG(mailbox) >> ((7u - (i)) * `$INSTANCE_NAME`_ONE_BYTE_OFFSET)) : \
            (uint8) (`$INSTANCE_NAME`_RX_DATA_LO_REG(mailbox) >> ((3u - (i)) * `$INSTANCE_NAME`_ONE_BYTE_OFFSET)))

    #define `$INSTANCE_NAME`_TX_DATA_BYTE(mailbox, i, byte) (((i) > 3u) ? \
        (`$INSTANCE_NAME`_TX_DATA_HI_REG(mailbox) = (`$INSTANCE_NAME`_TX_DATA_HI_REG(mailbox) & \
        (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << ((7u - (i)) * `$INSTANCE_NAME`_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((7u - (i)) * `$INSTANCE_NAME`_ONE_BYTE_OFFSET))) : \
        (`$INSTANCE_NAME`_TX_DATA_LO_REG(mailbox) = (`$INSTANCE_NAME`_TX_DATA_LO_REG(mailbox) & \
        (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << ((3u - (i)) * `$INSTANCE_NAME`_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((3u - (i)) * `$INSTANCE_NAME`_ONE_BYTE_OFFSET))))
#endif /* CY_PSOC3 || CY_PSOC5 */

#if (CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_DATA_BYTE_1            (3u)
    #define `$INSTANCE_NAME`_DATA_BYTE_2            (2u)
    #define `$INSTANCE_NAME`_DATA_BYTE_3            (1u)
    #define `$INSTANCE_NAME`_DATA_BYTE_4            (0u)
    #define `$INSTANCE_NAME`_DATA_BYTE_5            (7u)
    #define `$INSTANCE_NAME`_DATA_BYTE_6            (6u)
    #define `$INSTANCE_NAME`_DATA_BYTE_7            (5u)
    #define `$INSTANCE_NAME`_DATA_BYTE_8            (4u)

    /* Macros for access to RX DATA for mailbox(i) */
    #define `$INSTANCE_NAME`_RX_DATA_BYTE1(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_1]
    #define `$INSTANCE_NAME`_RX_DATA_BYTE2(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_2]
    #define `$INSTANCE_NAME`_RX_DATA_BYTE3(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_3]
    #define `$INSTANCE_NAME`_RX_DATA_BYTE4(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_4]
    #define `$INSTANCE_NAME`_RX_DATA_BYTE5(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_5]
    #define `$INSTANCE_NAME`_RX_DATA_BYTE6(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_6]
    #define `$INSTANCE_NAME`_RX_DATA_BYTE7(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_7]
    #define `$INSTANCE_NAME`_RX_DATA_BYTE8(i)       `$INSTANCE_NAME`_RX[i].rxdata.byte[`$INSTANCE_NAME`_DATA_BYTE_8]

    /* Macros for access to TX DATA for mailbox(i) */
    #define `$INSTANCE_NAME`_TX_DATA_BYTE1(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_1]
    #define `$INSTANCE_NAME`_TX_DATA_BYTE2(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_2]
    #define `$INSTANCE_NAME`_TX_DATA_BYTE3(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_3]
    #define `$INSTANCE_NAME`_TX_DATA_BYTE4(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_4]
    #define `$INSTANCE_NAME`_TX_DATA_BYTE5(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_5]
    #define `$INSTANCE_NAME`_TX_DATA_BYTE6(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_6]
    #define `$INSTANCE_NAME`_TX_DATA_BYTE7(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_7]
    #define `$INSTANCE_NAME`_TX_DATA_BYTE8(i)       `$INSTANCE_NAME`_TX[i].txdata.byte[`$INSTANCE_NAME`_DATA_BYTE_8]
#else  /* CY_PSOC4 */
    /* Macros for access to RX DATA for mailbox(i) */
    #define `$INSTANCE_NAME`_RX_DATA_BYTE1(i)       \
            ((uint8) (`$INSTANCE_NAME`_RX_DATA_LO_REG(i) >> `$INSTANCE_NAME`_THREE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_RX_DATA_BYTE2(i)       \
            ((uint8) (`$INSTANCE_NAME`_RX_DATA_LO_REG(i) >> `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_RX_DATA_BYTE3(i)       \
            ((uint8) (`$INSTANCE_NAME`_RX_DATA_LO_REG(i) >> `$INSTANCE_NAME`_ONE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_RX_DATA_BYTE4(i)       ((uint8) `$INSTANCE_NAME`_RX_DATA_LO_REG(i))
    #define `$INSTANCE_NAME`_RX_DATA_BYTE5(i)       \
            ((uint8) (`$INSTANCE_NAME`_RX_DATA_HI_REG(i) >> `$INSTANCE_NAME`_THREE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_RX_DATA_BYTE6(i)       \
            ((uint8) (`$INSTANCE_NAME`_RX_DATA_HI_REG(i) >> `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_RX_DATA_BYTE7(i)       \
            ((uint8) (`$INSTANCE_NAME`_RX_DATA_HI_REG(i) >> `$INSTANCE_NAME`_ONE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_RX_DATA_BYTE8(i)       ((uint8) `$INSTANCE_NAME`_RX_DATA_HI_REG(i))

    /* Macros for access to TX DATA for mailbox(i) */
    #define `$INSTANCE_NAME`_TX_DATA_BYTE1(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) = (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << `$INSTANCE_NAME`_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << `$INSTANCE_NAME`_THREE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_TX_DATA_BYTE2(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) = (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << `$INSTANCE_NAME`_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_TX_DATA_BYTE3(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) = (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << `$INSTANCE_NAME`_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << `$INSTANCE_NAME`_ONE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_TX_DATA_BYTE4(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) = (`$INSTANCE_NAME`_TX_DATA_LO_REG(i) & \
            (uint32) (~`$INSTANCE_NAME`_DATA_BYTE_MASK)) | (uint32) (byte))
    #define `$INSTANCE_NAME`_TX_DATA_BYTE5(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) = (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << `$INSTANCE_NAME`_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << `$INSTANCE_NAME`_THREE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_TX_DATA_BYTE6(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) = (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << `$INSTANCE_NAME`_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << `$INSTANCE_NAME`_TWO_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_TX_DATA_BYTE7(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) = (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (`$INSTANCE_NAME`_DATA_BYTE_MASK << `$INSTANCE_NAME`_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << `$INSTANCE_NAME`_ONE_BYTE_OFFSET))
    #define `$INSTANCE_NAME`_TX_DATA_BYTE8(i, byte) \
            (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) = (`$INSTANCE_NAME`_TX_DATA_HI_REG(i) & \
            (uint32) (~`$INSTANCE_NAME`_DATA_BYTE_MASK)) | (uint32) (byte))
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Macros for setting Tx Msg Identifier in `$INSTANCE_NAME`_TX_ID register */
#define `$INSTANCE_NAME`_SET_TX_ID_STANDARD_MSG_SHIFT  (21u)
#define `$INSTANCE_NAME`_SET_TX_ID_EXTENDED_MSG_SHIFT  (3u)
#define `$INSTANCE_NAME`_SET_TX_ID_STANDARD_MSG(i, id) (CY_SET_REG32(`$INSTANCE_NAME`_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << `$INSTANCE_NAME`_SET_TX_ID_STANDARD_MSG_SHIFT)))
#define `$INSTANCE_NAME`_SET_TX_ID_EXTENDED_MSG(i, id) (CY_SET_REG32(`$INSTANCE_NAME`_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << `$INSTANCE_NAME`_SET_TX_ID_EXTENDED_MSG_SHIFT)))

/* Mask for bits within `$INSTANCE_NAME`_CSR_CFG */
#define `$INSTANCE_NAME`_EDGE_MODE_SHIFT           (0u)
/* Bit 0 within CSR_CFG */
#define `$INSTANCE_NAME`_EDGE_MODE_MASK            ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_EDGE_MODE_SHIFT))
#define `$INSTANCE_NAME`_SAMPLE_MODE_SHIFT         (1u)
/* Bit 1 within CSR_CFG */
#define `$INSTANCE_NAME`_SAMPLE_MODE_MASK          ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_SAMPLE_MODE_SHIFT))
#define `$INSTANCE_NAME`_CFG_REG_SJW_SHIFT         (2u)
/* Bits 3-2 within CSR_CFG */
#define `$INSTANCE_NAME`_CFG_REG_SJW_MASK          ((uint8) ((uint8) 0x03u << `$INSTANCE_NAME`_CFG_REG_SJW_SHIFT))
#define `$INSTANCE_NAME`_CFG_REG_SJW_LOWER_LIMIT   (0x03u)  /* the lowest allowed value of cfg_sjw */
#define `$INSTANCE_NAME`_RESET_SHIFT               (4u)
/* Bit 4 within CSR_CFG    */
#define `$INSTANCE_NAME`_RESET_MASK                ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RESET_SHIFT))
#define `$INSTANCE_NAME`_CFG_REG_TSEG2_SHIFT       (5u)
/* Bits 7-5 within CSR_CFG */
#define `$INSTANCE_NAME`_CFG_REG_TSEG2_MASK        ((uint8) ((uint8) 0x07u << `$INSTANCE_NAME`_CFG_REG_TSEG2_SHIFT))
/* Highest allowed value of cfg_tseg2 */
#define `$INSTANCE_NAME`_CFG_REG_TSEG2_UPPER_LIMIT (0x07u)
/* Lowest allowed value of cfg_tseg2 */
#define `$INSTANCE_NAME`_CFG_REG_TSEG2_LOWER_LIMIT (0x02u)
/* Lowest allowed value of cfg_tseg2 if sample point is one point */
#define `$INSTANCE_NAME`_CFG_REG_TSEG2_EXCEPTION   (0x01u)
/* Bits 11-8 within CSR_CFG */
#define `$INSTANCE_NAME`_CFG_REG_TSEG1_SHIFT       (8u)
#define `$INSTANCE_NAME`_CFG_REG_TSEG1_MASK        (0x0Fu)
/* Highest allowed value of cfg_tseg1 */
#define `$INSTANCE_NAME`_CFG_REG_TSEG1_UPPER_LIMIT (0x0Fu)
/* Lowest allowed value of cfg_tseg1 */
#define `$INSTANCE_NAME`_CFG_REG_TSEG1_LOWER_LIMIT (0x02u)
#define `$INSTANCE_NAME`_ARBITER_SHIFT             (12u)

#if (CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_ARBITRATION_SHIFT     (4u)
    /* Bit 12 within CSR_CFG */
    #define `$INSTANCE_NAME`_ARBITRATION_MASK      ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_ARBITRATION_SHIFT))
#else  /* CY_PSOC4 */
    #define `$INSTANCE_NAME`_ARBITRATION_SHIFT     (12u)
    /* Bit 12 within CSR_CFG */
    #define `$INSTANCE_NAME`_ARBITRATION_MASK      ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_ARBITRATION_SHIFT))
    /* Bit 13 within CSR_CFG */
    #define `$INSTANCE_NAME`_ENDIANNESS_SHIFT      (13u)
    #define `$INSTANCE_NAME`_ENDIANNESS_MASK       ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_ENDIANNESS_SHIFT))
    /* Bit 14 within CSR_CFG */
    #define `$INSTANCE_NAME`_ECR_MODE_SHIFT        (14u)
    #define `$INSTANCE_NAME`_ECR_MODE_MASK         ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_ECR_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Bits 23-16 within CSR_CFG */
#define `$INSTANCE_NAME`_BITRATE_SHIFT             (16u)
#define `$INSTANCE_NAME`_BITRATE_MASK              (0x7FFFu)
#define `$INSTANCE_NAME`_BITRATE_MASK_SHIFTED      \
        ((uint32) ((uint32) `$INSTANCE_NAME`_BITRATE_MASK << `$INSTANCE_NAME`_BITRATE_SHIFT))

/* Mask for bits within `$INSTANCE_NAME`_CSR_CMD */
#define `$INSTANCE_NAME`_MODE_SHIFT                (0u)
/* Bit 0 within CSR_CMD */
#define `$INSTANCE_NAME`_MODE_MASK                 ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_MODE_SHIFT))
#define `$INSTANCE_NAME`_OPMODE_MASK_SHIFT         (1u)
/* Bit 1 within CSR_CMD */
#define `$INSTANCE_NAME`_OPMODE_MASK               ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_OPMODE_MASK_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x03u << `$INSTANCE_NAME`_MODE_SHIFT))
#else  /* CY_PSOC4 */
    #define `$INSTANCE_NAME`_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x07u << `$INSTANCE_NAME`_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask for bits within `$INSTANCE_NAME`_CSR_CMD */
#define `$INSTANCE_NAME`_ERROR_STATE_SHIFT         (0u)
/* Bit 17-16 within ERR_SR */
#define `$INSTANCE_NAME`_ERROR_STATE_MASK          ((uint8) ((uint8) 0x03u << `$INSTANCE_NAME`_ERROR_STATE_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_TX_ERROR_FLAG_SHIFT   (2u)
    /* Bit 18 within ERR_SR */
    #define `$INSTANCE_NAME`_TX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_TX_ERROR_FLAG_SHIFT))
    #define `$INSTANCE_NAME`_RX_ERROR_FLAG_SHIFT   (3u)
    /* Bit 19 within ERR_SR */
    #define `$INSTANCE_NAME`_RX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_ERROR_FLAG_SHIFT))
#else  /* CY_PSOC4 */
    #define `$INSTANCE_NAME`_TX_ERROR_FLAG_SHIFT   (18u)
    /* Bit 18 within ERR_SR */
    #define `$INSTANCE_NAME`_TX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_TX_ERROR_FLAG_SHIFT))
    #define `$INSTANCE_NAME`_RX_ERROR_FLAG_SHIFT   (19u)
    /* Bit 19 within ERR_SR */
    #define `$INSTANCE_NAME`_RX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_ERROR_FLAG_SHIFT))

    /* Mask and Macros for bits within `$INSTANCE_NAME`_ECR_REG */
    #define `$INSTANCE_NAME`_ECR_STATUS_ARM        (0x01u)
    /* Mask for clearing `$INSTANCE_NAME`INT_STATUS */
    #define `$INSTANCE_NAME`_INT_STATUS_MASK       (0x00001FFCu)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask and Macros for bits within `$INSTANCE_NAME`_INT_EN_REG */
#define `$INSTANCE_NAME`_GLOBAL_INT_SHIFT          (0u)
#define `$INSTANCE_NAME`_ARBITRATION_LOST_SHIFT    (2u)
#define `$INSTANCE_NAME`_OVERLOAD_ERROR_SHIFT      (3u)
#define `$INSTANCE_NAME`_BIT_ERROR_SHIFT           (4u)
#define `$INSTANCE_NAME`_STUFF_ERROR_SHIFT         (5u)
#define `$INSTANCE_NAME`_ACK_ERROR_SHIFT           (6u)
#define `$INSTANCE_NAME`_FORM_ERROR_SHIFT          (7u)

#if (CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_CRC_ERROR_SHIFT       (0u)
    #define `$INSTANCE_NAME`_BUS_OFF_SHIFT         (1u)
    #define `$INSTANCE_NAME`_RX_MSG_LOST_SHIFT     (2u)
    #define `$INSTANCE_NAME`_TX_MESSAGE_SHIFT      (3u)
    #define `$INSTANCE_NAME`_RX_MESSAGE_SHIFT      (4u)

    /* Bit 0 within INT_EN */
    #define `$INSTANCE_NAME`_GLOBAL_INT_MASK       ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_ARBITRATION_LOST_MASK ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_OVERLOAD_ERROR_MASK   ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_BIT_ERROR_MASK        ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_STUFF_ERROR_MASK      ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_ACK_ERROR_MASK        ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_FORM_ERROR_MASK       ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_CRC_ERROR_MASK        ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_BUS_OFF_MASK          ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_RX_MSG_LOST_MASK      ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_TX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_RX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << `$INSTANCE_NAME`_RX_MESSAGE_SHIFT))

    #define `$INSTANCE_NAME`_ARBITRATION_LOST_INT_ENABLE   \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] |= `$INSTANCE_NAME`_ARBITRATION_LOST_MASK)
    #define `$INSTANCE_NAME`_ARBITRATION_LOST_INT_DISABLE  \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_ARBITRATION_LOST_MASK))
    #define `$INSTANCE_NAME`_OVERLOAD_ERROR_INT_ENABLE     \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] |= `$INSTANCE_NAME`_OVERLOAD_ERROR_MASK)
    #define `$INSTANCE_NAME`_OVERLOAD_ERROR_INT_DISABLE    \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_OVERLOAD_ERROR_MASK))
    #define `$INSTANCE_NAME`_BIT_ERROR_LOST_INT_ENABLE     \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] |= `$INSTANCE_NAME`_BIT_ERROR_MASK)
    #define `$INSTANCE_NAME`_BIT_ERROR_LOST_INT_DISABLE    \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_BIT_ERROR_MASK))
    #define `$INSTANCE_NAME`_STUFF_ERROR_INT_ENABLE        \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] |= `$INSTANCE_NAME`_STUFF_ERROR_MASK)
    #define `$INSTANCE_NAME`_STUFF_ERROR_INT_DISABLE       \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_STUFF_ERROR_MASK))
    #define `$INSTANCE_NAME`_ACK_ERROR_INT_ENABLE          \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] |= `$INSTANCE_NAME`_ACK_ERROR_MASK)
    #define `$INSTANCE_NAME`_ACK_ERROR_INT_DISABLE         \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_ACK_ERROR_MASK))
    #define `$INSTANCE_NAME`_FORM_ERROR_INT_ENABLE         \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] |= `$INSTANCE_NAME`_FORM_ERROR_MASK)
    #define `$INSTANCE_NAME`_FORM_ERROR_INT_DISABLE        \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_FORM_ERROR_MASK))
    #define `$INSTANCE_NAME`_CRC_ERROR_INT_ENABLE          \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] |= `$INSTANCE_NAME`_CRC_ERROR_MASK)
    #define `$INSTANCE_NAME`_CRC_ERROR_INT_DISABLE         \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] &= (uint8) (~`$INSTANCE_NAME`_CRC_ERROR_MASK))
    #define `$INSTANCE_NAME`_BUS_OFF_INT_ENABLE            \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] |= `$INSTANCE_NAME`_BUS_OFF_MASK)
    #define `$INSTANCE_NAME`_BUS_OFF_INT_DISABLE           \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] &= (uint8) (~`$INSTANCE_NAME`_BUS_OFF_MASK))
    #define `$INSTANCE_NAME`_RX_MSG_LOST_INT_ENABLE        \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] |= `$INSTANCE_NAME`_RX_MSG_LOST_MASK)
    #define `$INSTANCE_NAME`_RX_MSG_LOST_INT_DISABLE       \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] &= (uint8) (~`$INSTANCE_NAME`_RX_MSG_LOST_MASK))
    #define `$INSTANCE_NAME`_TX_MSG_INT_ENABLE             \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] |= `$INSTANCE_NAME`_TX_MESSAGE_MASK)
    #define `$INSTANCE_NAME`_TX_MSG_INT_DISABLE            \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] &= (uint8) (~`$INSTANCE_NAME`_TX_MESSAGE_MASK))
    #define `$INSTANCE_NAME`_RX_MSG_INT_ENABLE             \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] |= `$INSTANCE_NAME`_RX_MESSAGE_MASK)
    #define `$INSTANCE_NAME`_RX_MSG_INT_DISABLE            \
            (`$INSTANCE_NAME`_INT_EN_REG.byte[1u] &= (uint8) (~`$INSTANCE_NAME`_RX_MESSAGE_MASK))
#else  /* CY_PSOC4 */
    #define `$INSTANCE_NAME`_CRC_ERROR_SHIFT       (8u)
    #define `$INSTANCE_NAME`_BUS_OFF_SHIFT         (9u)
    #define `$INSTANCE_NAME`_RX_MSG_LOST_SHIFT     (10u)
    #define `$INSTANCE_NAME`_TX_MESSAGE_SHIFT      (11u)
    #define `$INSTANCE_NAME`_RX_MESSAGE_SHIFT      (12u)

    /* Mask and Macros for bits within `$INSTANCE_NAME`_INT_EN_REG */
    /* Bit 0 within INT_EN */
    #define `$INSTANCE_NAME`_GLOBAL_INT_MASK       ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_ARBITRATION_LOST_MASK ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_OVERLOAD_ERROR_MASK   ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_BIT_ERROR_MASK        ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_STUFF_ERROR_MASK      ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_ACK_ERROR_MASK        ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_FORM_ERROR_MASK       ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_CRC_ERROR_MASK        ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_BUS_OFF_MASK          ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_RX_MSG_LOST_MASK      ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_TX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_RX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RX_MESSAGE_SHIFT))

    #define `$INSTANCE_NAME`_ARBITRATION_LOST_INT_ENABLE   \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_ARBITRATION_LOST_MASK)
    #define `$INSTANCE_NAME`_ARBITRATION_LOST_INT_DISABLE  \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_ARBITRATION_LOST_MASK))
    #define `$INSTANCE_NAME`_OVERLOAD_ERROR_INT_ENABLE     \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_OVERLOAD_ERROR_MASK)
    #define `$INSTANCE_NAME`_OVERLOAD_ERROR_INT_DISABLE    \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_OVERLOAD_ERROR_MASK))
    #define `$INSTANCE_NAME`_BIT_ERROR_LOST_INT_ENABLE     \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_BIT_ERROR_MASK)
    #define `$INSTANCE_NAME`_BIT_ERROR_LOST_INT_DISABLE    \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_BIT_ERROR_MASK))
    #define `$INSTANCE_NAME`_STUFF_ERROR_INT_ENABLE        \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_STUFF_ERROR_MASK)
    #define `$INSTANCE_NAME`_STUFF_ERROR_INT_DISABLE       \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_STUFF_ERROR_MASK))
    #define `$INSTANCE_NAME`_ACK_ERROR_INT_ENABLE          \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_ACK_ERROR_MASK)
    #define `$INSTANCE_NAME`_ACK_ERROR_INT_DISABLE         \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_ACK_ERROR_MASK))
    #define `$INSTANCE_NAME`_FORM_ERROR_INT_ENABLE         \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_FORM_ERROR_MASK)
    #define `$INSTANCE_NAME`_FORM_ERROR_INT_DISABLE        \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_FORM_ERROR_MASK))
    #define `$INSTANCE_NAME`_CRC_ERROR_INT_ENABLE          \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_CRC_ERROR_MASK)
    #define `$INSTANCE_NAME`_CRC_ERROR_INT_DISABLE         \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_CRC_ERROR_MASK))
    #define `$INSTANCE_NAME`_BUS_OFF_INT_ENABLE            \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_BUS_OFF_MASK)
    #define `$INSTANCE_NAME`_BUS_OFF_INT_DISABLE           \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_BUS_OFF_MASK))
    #define `$INSTANCE_NAME`_RX_MSG_LOST_INT_ENABLE        \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_RX_MSG_LOST_MASK)
    #define `$INSTANCE_NAME`_RX_MSG_LOST_INT_DISABLE       \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_RX_MSG_LOST_MASK))
    #define `$INSTANCE_NAME`_TX_MSG_INT_ENABLE             \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_TX_MESSAGE_MASK)
    #define `$INSTANCE_NAME`_TX_MSG_INT_DISABLE            \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_TX_MESSAGE_MASK))
    #define `$INSTANCE_NAME`_RX_MSG_INT_ENABLE             \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_RX_MESSAGE_MASK)
    #define `$INSTANCE_NAME`_RX_MSG_INT_DISABLE            \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_RX_MESSAGE_MASK))

    /* Bit 13 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_RTR_MSG_SHIFT              (13u)
    #define `$INSTANCE_NAME`_RTR_MSG_MASK               ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_RTR_MSG_SHIFT))
    #define `$INSTANCE_NAME`_RTR_MSG_INT_ENABLE         (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_RTR_MSG_MASK)
    #define `$INSTANCE_NAME`_RTR_MSG_INT_DISABLE        \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_RTR_MSG_MASK))
    /* Bit 14 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO_SHIFT        (14u)
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO_MASK         \
            ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_STUCK_AT_ZERO_SHIFT))
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO_INT_ENABLE   \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_STUCK_AT_ZERO_MASK)
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO_INT_DISABLE  \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_STUCK_AT_ZERO_MASK))
    /* Bit 15 within INT_EN and INT_SR */
    #define `$INSTANCE_NAME`_SST_FAILURE_SHIFT          (15u)
    #define `$INSTANCE_NAME`_SST_FAILURE_MASK           \
            ((uint32) ((uint32) 0x01u << `$INSTANCE_NAME`_SST_FAILURE_SHIFT))
    #define `$INSTANCE_NAME`_SST_FAILURE_INT_ENABLE     \
            (`$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_SST_FAILURE_MASK)
    #define `$INSTANCE_NAME`_SST_FAILURE_INT_DISABLE    \
            (`$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~`$INSTANCE_NAME`_SST_FAILURE_MASK))
#endif /* CY_PSOC3 || CY_PSOC5 */

#define `$INSTANCE_NAME`_GLOBAL_INT_ENABLE_SHIFT        (0u)
#define `$INSTANCE_NAME`_ARBITRATION_LOST_ENABLE_SHIFT  (2u)
#define `$INSTANCE_NAME`_OVERLOAD_ERROR_ENABLE_SHIFT    (3u)
#define `$INSTANCE_NAME`_BIT_ERROR_ENABLE_SHIFT         (4u)
#define `$INSTANCE_NAME`_STUFF_ERROR_ENABLE_SHIFT       (5u)
#define `$INSTANCE_NAME`_ACK_ERROR_ENABLE_SHIFT         (6u)
#define `$INSTANCE_NAME`_FORM_ERROR_ENABLE_SHIFT        (7u)
#define `$INSTANCE_NAME`_CRC_ERROR_ENABLE_SHIFT         (8u)
#define `$INSTANCE_NAME`_BUS_OFF_ENABLE_SHIFT           (9u)
#define `$INSTANCE_NAME`_RX_MSG_LOST_ENABLE_SHIFT       (10u)
#define `$INSTANCE_NAME`_TX_MESSAGE_ENABLE_SHIFT        (11u)
#define `$INSTANCE_NAME`_RX_MESSAGE_ENABLE_SHIFT        (12u)

#define `$INSTANCE_NAME`_GLOBAL_INT_ENABLE    ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_GLOBAL_INT_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_ARBITRATION_LOST_ENABLE \
        ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_ARBITRATION_LOST_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_OVERLOAD_ERROR_ENABLE   \
        ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_OVERLOAD_ERROR_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_BIT_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_BIT_ERROR_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_STUFF_ERROR_ENABLE   ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_STUFF_ERROR_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_ACK_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_ACK_ERROR_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_FORM_ERROR_ENABLE    ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_FORM_ERROR_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_CRC_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_CRC_ERROR_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_BUS_OFF_ENABLE       ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_BUS_OFF_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_RX_MSG_LOST_ENABLE   ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_RX_MSG_LOST_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_TX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_TX_MESSAGE_ENABLE_SHIFT))
#define `$INSTANCE_NAME`_RX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_RX_MESSAGE_ENABLE_SHIFT))

#if (!(CY_PSOC3 || CY_PSOC5))
    #define `$INSTANCE_NAME`_RTR_MESSAGE_ENABLE_SHIFT   (13u)
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO_ENABLE_SHIFT (14u)
    #define `$INSTANCE_NAME`_SST_FAILURE_ENABLE_SHIFT   (15u)

    #define `$INSTANCE_NAME`_RTR_MESSAGE_ENABLE   \
            ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_RTR_MESSAGE_ENABLE_SHIFT))
    #define `$INSTANCE_NAME`_STUCK_AT_ZERO_ENABLE \
            ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_STUCK_AT_ZERO_ENABLE_SHIFT))
    #define `$INSTANCE_NAME`_SST_FAILURE_ENABLE   \
            ((uint16) ((uint16) 0x01u << `$INSTANCE_NAME`_SST_FAILURE_ENABLE_SHIFT))
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define `$INSTANCE_NAME`_REG_ADDR_MASK        ((uint32) 0x0000FFFFu)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define `$INSTANCE_NAME`_TREE_BYTE_OFFSET     (`$INSTANCE_NAME`_THREE_BYTE_OFFSET)

/* `$INSTANCE_NAME`_SetRestartType() parameters */
#define `$INSTANCE_NAME`_RESTART_BY_HAND      (`$INSTANCE_NAME`_MANUAL_RESTART)

/* `$INSTANCE_NAME`_SetOpMode() parameters */
#define `$INSTANCE_NAME`_LISTEN_ONLY          (`$INSTANCE_NAME`_LISTEN_ONLY_MODE)
#define `$INSTANCE_NAME`_ACTIVE_MODE          (`$INSTANCE_NAME`_INITIAL_MODE)

#ifdef `$INSTANCE_NAME`_ISR_CALLBACK
    #define `$INSTANCE_NAME`_ISR_INTERRUPT_CALLBACK
    #define `$INSTANCE_NAME`_ISR_InterruptCallback  `$INSTANCE_NAME`_Isr_Callback
#endif

#endif /* CY_CAN_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
