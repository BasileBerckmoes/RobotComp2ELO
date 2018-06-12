/*******************************************************************************
* File Name: puttyUart1.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_puttyUart1_H)
#define CY_UART_puttyUart1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define puttyUart1_RX_ENABLED                     (1u)
#define puttyUart1_TX_ENABLED                     (1u)
#define puttyUart1_HD_ENABLED                     (0u)
#define puttyUart1_RX_INTERRUPT_ENABLED           (0u)
#define puttyUart1_TX_INTERRUPT_ENABLED           (0u)
#define puttyUart1_INTERNAL_CLOCK_USED            (1u)
#define puttyUart1_RXHW_ADDRESS_ENABLED           (0u)
#define puttyUart1_OVER_SAMPLE_COUNT              (8u)
#define puttyUart1_PARITY_TYPE                    (0u)
#define puttyUart1_PARITY_TYPE_SW                 (0u)
#define puttyUart1_BREAK_DETECT                   (0u)
#define puttyUart1_BREAK_BITS_TX                  (13u)
#define puttyUart1_BREAK_BITS_RX                  (13u)
#define puttyUart1_TXCLKGEN_DP                    (1u)
#define puttyUart1_USE23POLLING                   (1u)
#define puttyUart1_FLOW_CONTROL                   (0u)
#define puttyUart1_CLK_FREQ                       (0u)
#define puttyUart1_TX_BUFFER_SIZE                 (4u)
#define puttyUart1_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define puttyUart1_CONTROL_REG_REMOVED            (0u)
#else
    #define puttyUart1_CONTROL_REG_REMOVED            (1u)
#endif /* End puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct puttyUart1_backupStruct_
{
    uint8 enableState;

    #if(puttyUart1_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End puttyUart1_CONTROL_REG_REMOVED */

} puttyUart1_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void puttyUart1_Start(void) ;
void puttyUart1_Stop(void) ;
uint8 puttyUart1_ReadControlRegister(void) ;
void puttyUart1_WriteControlRegister(uint8 control) ;

void puttyUart1_Init(void) ;
void puttyUart1_Enable(void) ;
void puttyUart1_SaveConfig(void) ;
void puttyUart1_RestoreConfig(void) ;
void puttyUart1_Sleep(void) ;
void puttyUart1_Wakeup(void) ;

/* Only if RX is enabled */
#if( (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) )

    #if (puttyUart1_RX_INTERRUPT_ENABLED)
        #define puttyUart1_EnableRxInt()  CyIntEnable (puttyUart1_RX_VECT_NUM)
        #define puttyUart1_DisableRxInt() CyIntDisable(puttyUart1_RX_VECT_NUM)
        CY_ISR_PROTO(puttyUart1_RXISR);
    #endif /* puttyUart1_RX_INTERRUPT_ENABLED */

    void puttyUart1_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void puttyUart1_SetRxAddress1(uint8 address) ;
    void puttyUart1_SetRxAddress2(uint8 address) ;

    void  puttyUart1_SetRxInterruptMode(uint8 intSrc) ;
    uint8 puttyUart1_ReadRxData(void) ;
    uint8 puttyUart1_ReadRxStatus(void) ;
    uint8 puttyUart1_GetChar(void) ;
    uint16 puttyUart1_GetByte(void) ;
    uint8 puttyUart1_GetRxBufferSize(void)
                                                            ;
    void puttyUart1_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define puttyUart1_GetRxInterruptSource   puttyUart1_ReadRxStatus

#endif /* End (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) */

/* Only if TX is enabled */
#if(puttyUart1_TX_ENABLED || puttyUart1_HD_ENABLED)

    #if(puttyUart1_TX_INTERRUPT_ENABLED)
        #define puttyUart1_EnableTxInt()  CyIntEnable (puttyUart1_TX_VECT_NUM)
        #define puttyUart1_DisableTxInt() CyIntDisable(puttyUart1_TX_VECT_NUM)
        #define puttyUart1_SetPendingTxInt() CyIntSetPending(puttyUart1_TX_VECT_NUM)
        #define puttyUart1_ClearPendingTxInt() CyIntClearPending(puttyUart1_TX_VECT_NUM)
        CY_ISR_PROTO(puttyUart1_TXISR);
    #endif /* puttyUart1_TX_INTERRUPT_ENABLED */

    void puttyUart1_SetTxInterruptMode(uint8 intSrc) ;
    void puttyUart1_WriteTxData(uint8 txDataByte) ;
    uint8 puttyUart1_ReadTxStatus(void) ;
    void puttyUart1_PutChar(uint8 txDataByte) ;
    void puttyUart1_PutString(const char8 string[]) ;
    void puttyUart1_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void puttyUart1_PutCRLF(uint8 txDataByte) ;
    void puttyUart1_ClearTxBuffer(void) ;
    void puttyUart1_SetTxAddressMode(uint8 addressMode) ;
    void puttyUart1_SendBreak(uint8 retMode) ;
    uint8 puttyUart1_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define puttyUart1_PutStringConst         puttyUart1_PutString
    #define puttyUart1_PutArrayConst          puttyUart1_PutArray
    #define puttyUart1_GetTxInterruptSource   puttyUart1_ReadTxStatus

#endif /* End puttyUart1_TX_ENABLED || puttyUart1_HD_ENABLED */

#if(puttyUart1_HD_ENABLED)
    void puttyUart1_LoadRxConfig(void) ;
    void puttyUart1_LoadTxConfig(void) ;
#endif /* End puttyUart1_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_puttyUart1) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    puttyUart1_CyBtldrCommStart(void) CYSMALL ;
    void    puttyUart1_CyBtldrCommStop(void) CYSMALL ;
    void    puttyUart1_CyBtldrCommReset(void) CYSMALL ;
    cystatus puttyUart1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus puttyUart1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_puttyUart1)
        #define CyBtldrCommStart    puttyUart1_CyBtldrCommStart
        #define CyBtldrCommStop     puttyUart1_CyBtldrCommStop
        #define CyBtldrCommReset    puttyUart1_CyBtldrCommReset
        #define CyBtldrCommWrite    puttyUart1_CyBtldrCommWrite
        #define CyBtldrCommRead     puttyUart1_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_puttyUart1) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define puttyUart1_BYTE2BYTE_TIME_OUT (25u)
    #define puttyUart1_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define puttyUart1_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define puttyUart1_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define puttyUart1_SET_SPACE      (0x00u)
#define puttyUart1_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (puttyUart1_TX_ENABLED) || (puttyUart1_HD_ENABLED) )
    #if(puttyUart1_TX_INTERRUPT_ENABLED)
        #define puttyUart1_TX_VECT_NUM            (uint8)puttyUart1_TXInternalInterrupt__INTC_NUMBER
        #define puttyUart1_TX_PRIOR_NUM           (uint8)puttyUart1_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* puttyUart1_TX_INTERRUPT_ENABLED */

    #define puttyUart1_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define puttyUart1_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define puttyUart1_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(puttyUart1_TX_ENABLED)
        #define puttyUart1_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (puttyUart1_HD_ENABLED) */
        #define puttyUart1_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (puttyUart1_TX_ENABLED) */

    #define puttyUart1_TX_STS_COMPLETE            (uint8)(0x01u << puttyUart1_TX_STS_COMPLETE_SHIFT)
    #define puttyUart1_TX_STS_FIFO_EMPTY          (uint8)(0x01u << puttyUart1_TX_STS_FIFO_EMPTY_SHIFT)
    #define puttyUart1_TX_STS_FIFO_FULL           (uint8)(0x01u << puttyUart1_TX_STS_FIFO_FULL_SHIFT)
    #define puttyUart1_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << puttyUart1_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (puttyUart1_TX_ENABLED) || (puttyUart1_HD_ENABLED)*/

#if( (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) )
    #if(puttyUart1_RX_INTERRUPT_ENABLED)
        #define puttyUart1_RX_VECT_NUM            (uint8)puttyUart1_RXInternalInterrupt__INTC_NUMBER
        #define puttyUart1_RX_PRIOR_NUM           (uint8)puttyUart1_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* puttyUart1_RX_INTERRUPT_ENABLED */
    #define puttyUart1_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define puttyUart1_RX_STS_BREAK_SHIFT             (0x01u)
    #define puttyUart1_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define puttyUart1_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define puttyUart1_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define puttyUart1_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define puttyUart1_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define puttyUart1_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define puttyUart1_RX_STS_MRKSPC           (uint8)(0x01u << puttyUart1_RX_STS_MRKSPC_SHIFT)
    #define puttyUart1_RX_STS_BREAK            (uint8)(0x01u << puttyUart1_RX_STS_BREAK_SHIFT)
    #define puttyUart1_RX_STS_PAR_ERROR        (uint8)(0x01u << puttyUart1_RX_STS_PAR_ERROR_SHIFT)
    #define puttyUart1_RX_STS_STOP_ERROR       (uint8)(0x01u << puttyUart1_RX_STS_STOP_ERROR_SHIFT)
    #define puttyUart1_RX_STS_OVERRUN          (uint8)(0x01u << puttyUart1_RX_STS_OVERRUN_SHIFT)
    #define puttyUart1_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << puttyUart1_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define puttyUart1_RX_STS_ADDR_MATCH       (uint8)(0x01u << puttyUart1_RX_STS_ADDR_MATCH_SHIFT)
    #define puttyUart1_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << puttyUart1_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define puttyUart1_RX_HW_MASK                     (0x7Fu)
#endif /* End (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) */

/* Control Register definitions */
#define puttyUart1_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define puttyUart1_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define puttyUart1_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define puttyUart1_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define puttyUart1_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define puttyUart1_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define puttyUart1_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define puttyUart1_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define puttyUart1_CTRL_HD_SEND               (uint8)(0x01u << puttyUart1_CTRL_HD_SEND_SHIFT)
#define puttyUart1_CTRL_HD_SEND_BREAK         (uint8)(0x01u << puttyUart1_CTRL_HD_SEND_BREAK_SHIFT)
#define puttyUart1_CTRL_MARK                  (uint8)(0x01u << puttyUart1_CTRL_MARK_SHIFT)
#define puttyUart1_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << puttyUart1_CTRL_PARITY_TYPE0_SHIFT)
#define puttyUart1_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << puttyUart1_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define puttyUart1_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define puttyUart1_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define puttyUart1_SEND_BREAK                         (0x00u)
#define puttyUart1_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define puttyUart1_REINIT                             (0x02u)
#define puttyUart1_SEND_WAIT_REINIT                   (0x03u)

#define puttyUart1_OVER_SAMPLE_8                      (8u)
#define puttyUart1_OVER_SAMPLE_16                     (16u)

#define puttyUart1_BIT_CENTER                         (puttyUart1_OVER_SAMPLE_COUNT - 2u)

#define puttyUart1_FIFO_LENGTH                        (4u)
#define puttyUart1_NUMBER_OF_START_BIT                (1u)
#define puttyUart1_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define puttyUart1_TXBITCTR_BREAKBITS8X   ((puttyUart1_BREAK_BITS_TX * puttyUart1_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define puttyUart1_TXBITCTR_BREAKBITS ((puttyUart1_BREAK_BITS_TX * puttyUart1_OVER_SAMPLE_COUNT) - 1u)

#define puttyUart1_HALF_BIT_COUNT   \
                            (((puttyUart1_OVER_SAMPLE_COUNT / 2u) + (puttyUart1_USE23POLLING * 1u)) - 2u)
#if (puttyUart1_OVER_SAMPLE_COUNT == puttyUart1_OVER_SAMPLE_8)
    #define puttyUart1_HD_TXBITCTR_INIT   (((puttyUart1_BREAK_BITS_TX + \
                            puttyUart1_NUMBER_OF_START_BIT) * puttyUart1_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define puttyUart1_RXBITCTR_INIT  ((((puttyUart1_BREAK_BITS_RX + puttyUart1_NUMBER_OF_START_BIT) \
                            * puttyUart1_OVER_SAMPLE_COUNT) + puttyUart1_HALF_BIT_COUNT) - 1u)

#else /* puttyUart1_OVER_SAMPLE_COUNT == puttyUart1_OVER_SAMPLE_16 */
    #define puttyUart1_HD_TXBITCTR_INIT   ((8u * puttyUart1_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define puttyUart1_RXBITCTR_INIT      (((7u * puttyUart1_OVER_SAMPLE_COUNT) - 1u) + \
                                                      puttyUart1_HALF_BIT_COUNT)
#endif /* End puttyUart1_OVER_SAMPLE_COUNT */

#define puttyUart1_HD_RXBITCTR_INIT                   puttyUart1_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 puttyUart1_initVar;
#if (puttyUart1_TX_INTERRUPT_ENABLED && puttyUart1_TX_ENABLED)
    extern volatile uint8 puttyUart1_txBuffer[puttyUart1_TX_BUFFER_SIZE];
    extern volatile uint8 puttyUart1_txBufferRead;
    extern uint8 puttyUart1_txBufferWrite;
#endif /* (puttyUart1_TX_INTERRUPT_ENABLED && puttyUart1_TX_ENABLED) */
#if (puttyUart1_RX_INTERRUPT_ENABLED && (puttyUart1_RX_ENABLED || puttyUart1_HD_ENABLED))
    extern uint8 puttyUart1_errorStatus;
    extern volatile uint8 puttyUart1_rxBuffer[puttyUart1_RX_BUFFER_SIZE];
    extern volatile uint8 puttyUart1_rxBufferRead;
    extern volatile uint8 puttyUart1_rxBufferWrite;
    extern volatile uint8 puttyUart1_rxBufferLoopDetect;
    extern volatile uint8 puttyUart1_rxBufferOverflow;
    #if (puttyUart1_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 puttyUart1_rxAddressMode;
        extern volatile uint8 puttyUart1_rxAddressDetected;
    #endif /* (puttyUart1_RXHW_ADDRESS_ENABLED) */
#endif /* (puttyUart1_RX_INTERRUPT_ENABLED && (puttyUart1_RX_ENABLED || puttyUart1_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define puttyUart1__B_UART__AM_SW_BYTE_BYTE 1
#define puttyUart1__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define puttyUart1__B_UART__AM_HW_BYTE_BY_BYTE 3
#define puttyUart1__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define puttyUart1__B_UART__AM_NONE 0

#define puttyUart1__B_UART__NONE_REVB 0
#define puttyUart1__B_UART__EVEN_REVB 1
#define puttyUart1__B_UART__ODD_REVB 2
#define puttyUart1__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define puttyUart1_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define puttyUart1_NUMBER_OF_STOP_BITS    (1u)

#if (puttyUart1_RXHW_ADDRESS_ENABLED)
    #define puttyUart1_RX_ADDRESS_MODE    (0u)
    #define puttyUart1_RX_HW_ADDRESS1     (0u)
    #define puttyUart1_RX_HW_ADDRESS2     (0u)
#endif /* (puttyUart1_RXHW_ADDRESS_ENABLED) */

#define puttyUart1_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << puttyUart1_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << puttyUart1_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << puttyUart1_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << puttyUart1_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << puttyUart1_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << puttyUart1_RX_STS_BREAK_SHIFT) \
                                        | (0 << puttyUart1_RX_STS_OVERRUN_SHIFT))

#define puttyUart1_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << puttyUart1_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << puttyUart1_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << puttyUart1_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << puttyUart1_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define puttyUart1_CONTROL_REG \
                            (* (reg8 *) puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define puttyUart1_CONTROL_PTR \
                            (  (reg8 *) puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(puttyUart1_TX_ENABLED)
    #define puttyUart1_TXDATA_REG          (* (reg8 *) puttyUart1_BUART_sTX_TxShifter_u0__F0_REG)
    #define puttyUart1_TXDATA_PTR          (  (reg8 *) puttyUart1_BUART_sTX_TxShifter_u0__F0_REG)
    #define puttyUart1_TXDATA_AUX_CTL_REG  (* (reg8 *) puttyUart1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define puttyUart1_TXDATA_AUX_CTL_PTR  (  (reg8 *) puttyUart1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define puttyUart1_TXSTATUS_REG        (* (reg8 *) puttyUart1_BUART_sTX_TxSts__STATUS_REG)
    #define puttyUart1_TXSTATUS_PTR        (  (reg8 *) puttyUart1_BUART_sTX_TxSts__STATUS_REG)
    #define puttyUart1_TXSTATUS_MASK_REG   (* (reg8 *) puttyUart1_BUART_sTX_TxSts__MASK_REG)
    #define puttyUart1_TXSTATUS_MASK_PTR   (  (reg8 *) puttyUart1_BUART_sTX_TxSts__MASK_REG)
    #define puttyUart1_TXSTATUS_ACTL_REG   (* (reg8 *) puttyUart1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define puttyUart1_TXSTATUS_ACTL_PTR   (  (reg8 *) puttyUart1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(puttyUart1_TXCLKGEN_DP)
        #define puttyUart1_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define puttyUart1_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define puttyUart1_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define puttyUart1_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define puttyUart1_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define puttyUart1_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define puttyUart1_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define puttyUart1_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define puttyUart1_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define puttyUart1_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) puttyUart1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* puttyUart1_TXCLKGEN_DP */

#endif /* End puttyUart1_TX_ENABLED */

#if(puttyUart1_HD_ENABLED)

    #define puttyUart1_TXDATA_REG             (* (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__F1_REG )
    #define puttyUart1_TXDATA_PTR             (  (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__F1_REG )
    #define puttyUart1_TXDATA_AUX_CTL_REG     (* (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define puttyUart1_TXDATA_AUX_CTL_PTR     (  (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define puttyUart1_TXSTATUS_REG           (* (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart1_TXSTATUS_PTR           (  (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart1_TXSTATUS_MASK_REG      (* (reg8 *) puttyUart1_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart1_TXSTATUS_MASK_PTR      (  (reg8 *) puttyUart1_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart1_TXSTATUS_ACTL_REG      (* (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define puttyUart1_TXSTATUS_ACTL_PTR      (  (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End puttyUart1_HD_ENABLED */

#if( (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) )
    #define puttyUart1_RXDATA_REG             (* (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__F0_REG )
    #define puttyUart1_RXDATA_PTR             (  (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__F0_REG )
    #define puttyUart1_RXADDRESS1_REG         (* (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__D0_REG )
    #define puttyUart1_RXADDRESS1_PTR         (  (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__D0_REG )
    #define puttyUart1_RXADDRESS2_REG         (* (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__D1_REG )
    #define puttyUart1_RXADDRESS2_PTR         (  (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__D1_REG )
    #define puttyUart1_RXDATA_AUX_CTL_REG     (* (reg8 *) puttyUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define puttyUart1_RXBITCTR_PERIOD_REG    (* (reg8 *) puttyUart1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define puttyUart1_RXBITCTR_PERIOD_PTR    (  (reg8 *) puttyUart1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define puttyUart1_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) puttyUart1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define puttyUart1_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) puttyUart1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define puttyUart1_RXBITCTR_COUNTER_REG   (* (reg8 *) puttyUart1_BUART_sRX_RxBitCounter__COUNT_REG )
    #define puttyUart1_RXBITCTR_COUNTER_PTR   (  (reg8 *) puttyUart1_BUART_sRX_RxBitCounter__COUNT_REG )

    #define puttyUart1_RXSTATUS_REG           (* (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart1_RXSTATUS_PTR           (  (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart1_RXSTATUS_MASK_REG      (* (reg8 *) puttyUart1_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart1_RXSTATUS_MASK_PTR      (  (reg8 *) puttyUart1_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart1_RXSTATUS_ACTL_REG      (* (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define puttyUart1_RXSTATUS_ACTL_PTR      (  (reg8 *) puttyUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) */

#if(puttyUart1_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define puttyUart1_INTCLOCK_CLKEN_REG     (* (reg8 *) puttyUart1_IntClock__PM_ACT_CFG)
    #define puttyUart1_INTCLOCK_CLKEN_PTR     (  (reg8 *) puttyUart1_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define puttyUart1_INTCLOCK_CLKEN_MASK    puttyUart1_IntClock__PM_ACT_MSK
#endif /* End puttyUart1_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(puttyUart1_TX_ENABLED)
    #define puttyUart1_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End puttyUart1_TX_ENABLED */

#if(puttyUart1_HD_ENABLED)
    #define puttyUart1_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End puttyUart1_HD_ENABLED */

#if( (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) )
    #define puttyUart1_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define puttyUart1_WAIT_1_MS      puttyUart1_BL_CHK_DELAY_MS   

#define puttyUart1_TXBUFFERSIZE   puttyUart1_TX_BUFFER_SIZE
#define puttyUart1_RXBUFFERSIZE   puttyUart1_RX_BUFFER_SIZE

#if (puttyUart1_RXHW_ADDRESS_ENABLED)
    #define puttyUart1_RXADDRESSMODE  puttyUart1_RX_ADDRESS_MODE
    #define puttyUart1_RXHWADDRESS1   puttyUart1_RX_HW_ADDRESS1
    #define puttyUart1_RXHWADDRESS2   puttyUart1_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define puttyUart1_RXAddressMode  puttyUart1_RXADDRESSMODE
#endif /* (puttyUart1_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define puttyUart1_initvar                    puttyUart1_initVar

#define puttyUart1_RX_Enabled                 puttyUart1_RX_ENABLED
#define puttyUart1_TX_Enabled                 puttyUart1_TX_ENABLED
#define puttyUart1_HD_Enabled                 puttyUart1_HD_ENABLED
#define puttyUart1_RX_IntInterruptEnabled     puttyUart1_RX_INTERRUPT_ENABLED
#define puttyUart1_TX_IntInterruptEnabled     puttyUart1_TX_INTERRUPT_ENABLED
#define puttyUart1_InternalClockUsed          puttyUart1_INTERNAL_CLOCK_USED
#define puttyUart1_RXHW_Address_Enabled       puttyUart1_RXHW_ADDRESS_ENABLED
#define puttyUart1_OverSampleCount            puttyUart1_OVER_SAMPLE_COUNT
#define puttyUart1_ParityType                 puttyUart1_PARITY_TYPE

#if( puttyUart1_TX_ENABLED && (puttyUart1_TXBUFFERSIZE > puttyUart1_FIFO_LENGTH))
    #define puttyUart1_TXBUFFER               puttyUart1_txBuffer
    #define puttyUart1_TXBUFFERREAD           puttyUart1_txBufferRead
    #define puttyUart1_TXBUFFERWRITE          puttyUart1_txBufferWrite
#endif /* End puttyUart1_TX_ENABLED */
#if( ( puttyUart1_RX_ENABLED || puttyUart1_HD_ENABLED ) && \
     (puttyUart1_RXBUFFERSIZE > puttyUart1_FIFO_LENGTH) )
    #define puttyUart1_RXBUFFER               puttyUart1_rxBuffer
    #define puttyUart1_RXBUFFERREAD           puttyUart1_rxBufferRead
    #define puttyUart1_RXBUFFERWRITE          puttyUart1_rxBufferWrite
    #define puttyUart1_RXBUFFERLOOPDETECT     puttyUart1_rxBufferLoopDetect
    #define puttyUart1_RXBUFFER_OVERFLOW      puttyUart1_rxBufferOverflow
#endif /* End puttyUart1_RX_ENABLED */

#ifdef puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define puttyUart1_CONTROL                puttyUart1_CONTROL_REG
#endif /* End puttyUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(puttyUart1_TX_ENABLED)
    #define puttyUart1_TXDATA                 puttyUart1_TXDATA_REG
    #define puttyUart1_TXSTATUS               puttyUart1_TXSTATUS_REG
    #define puttyUart1_TXSTATUS_MASK          puttyUart1_TXSTATUS_MASK_REG
    #define puttyUart1_TXSTATUS_ACTL          puttyUart1_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(puttyUart1_TXCLKGEN_DP)
        #define puttyUart1_TXBITCLKGEN_CTR        puttyUart1_TXBITCLKGEN_CTR_REG
        #define puttyUart1_TXBITCLKTX_COMPLETE    puttyUart1_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define puttyUart1_TXBITCTR_PERIOD        puttyUart1_TXBITCTR_PERIOD_REG
        #define puttyUart1_TXBITCTR_CONTROL       puttyUart1_TXBITCTR_CONTROL_REG
        #define puttyUart1_TXBITCTR_COUNTER       puttyUart1_TXBITCTR_COUNTER_REG
    #endif /* puttyUart1_TXCLKGEN_DP */
#endif /* End puttyUart1_TX_ENABLED */

#if(puttyUart1_HD_ENABLED)
    #define puttyUart1_TXDATA                 puttyUart1_TXDATA_REG
    #define puttyUart1_TXSTATUS               puttyUart1_TXSTATUS_REG
    #define puttyUart1_TXSTATUS_MASK          puttyUart1_TXSTATUS_MASK_REG
    #define puttyUart1_TXSTATUS_ACTL          puttyUart1_TXSTATUS_ACTL_REG
#endif /* End puttyUart1_HD_ENABLED */

#if( (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) )
    #define puttyUart1_RXDATA                 puttyUart1_RXDATA_REG
    #define puttyUart1_RXADDRESS1             puttyUart1_RXADDRESS1_REG
    #define puttyUart1_RXADDRESS2             puttyUart1_RXADDRESS2_REG
    #define puttyUart1_RXBITCTR_PERIOD        puttyUart1_RXBITCTR_PERIOD_REG
    #define puttyUart1_RXBITCTR_CONTROL       puttyUart1_RXBITCTR_CONTROL_REG
    #define puttyUart1_RXBITCTR_COUNTER       puttyUart1_RXBITCTR_COUNTER_REG
    #define puttyUart1_RXSTATUS               puttyUart1_RXSTATUS_REG
    #define puttyUart1_RXSTATUS_MASK          puttyUart1_RXSTATUS_MASK_REG
    #define puttyUart1_RXSTATUS_ACTL          puttyUart1_RXSTATUS_ACTL_REG
#endif /* End  (puttyUart1_RX_ENABLED) || (puttyUart1_HD_ENABLED) */

#if(puttyUart1_INTERNAL_CLOCK_USED)
    #define puttyUart1_INTCLOCK_CLKEN         puttyUart1_INTCLOCK_CLKEN_REG
#endif /* End puttyUart1_INTERNAL_CLOCK_USED */

#define puttyUart1_WAIT_FOR_COMLETE_REINIT    puttyUart1_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_puttyUart1_H */


/* [] END OF FILE */
