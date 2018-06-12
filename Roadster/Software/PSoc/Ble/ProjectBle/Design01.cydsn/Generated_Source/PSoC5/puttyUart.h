/*******************************************************************************
* File Name: puttyUart.h
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


#if !defined(CY_UART_puttyUart_H)
#define CY_UART_puttyUart_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define puttyUart_RX_ENABLED                     (1u)
#define puttyUart_TX_ENABLED                     (1u)
#define puttyUart_HD_ENABLED                     (0u)
#define puttyUart_RX_INTERRUPT_ENABLED           (0u)
#define puttyUart_TX_INTERRUPT_ENABLED           (0u)
#define puttyUart_INTERNAL_CLOCK_USED            (1u)
#define puttyUart_RXHW_ADDRESS_ENABLED           (0u)
#define puttyUart_OVER_SAMPLE_COUNT              (8u)
#define puttyUart_PARITY_TYPE                    (0u)
#define puttyUart_PARITY_TYPE_SW                 (0u)
#define puttyUart_BREAK_DETECT                   (0u)
#define puttyUart_BREAK_BITS_TX                  (13u)
#define puttyUart_BREAK_BITS_RX                  (13u)
#define puttyUart_TXCLKGEN_DP                    (1u)
#define puttyUart_USE23POLLING                   (1u)
#define puttyUart_FLOW_CONTROL                   (0u)
#define puttyUart_CLK_FREQ                       (0u)
#define puttyUart_TX_BUFFER_SIZE                 (4u)
#define puttyUart_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define puttyUart_CONTROL_REG_REMOVED            (0u)
#else
    #define puttyUart_CONTROL_REG_REMOVED            (1u)
#endif /* End puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct puttyUart_backupStruct_
{
    uint8 enableState;

    #if(puttyUart_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End puttyUart_CONTROL_REG_REMOVED */

} puttyUart_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void puttyUart_Start(void) ;
void puttyUart_Stop(void) ;
uint8 puttyUart_ReadControlRegister(void) ;
void puttyUart_WriteControlRegister(uint8 control) ;

void puttyUart_Init(void) ;
void puttyUart_Enable(void) ;
void puttyUart_SaveConfig(void) ;
void puttyUart_RestoreConfig(void) ;
void puttyUart_Sleep(void) ;
void puttyUart_Wakeup(void) ;

/* Only if RX is enabled */
#if( (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) )

    #if (puttyUart_RX_INTERRUPT_ENABLED)
        #define puttyUart_EnableRxInt()  CyIntEnable (puttyUart_RX_VECT_NUM)
        #define puttyUart_DisableRxInt() CyIntDisable(puttyUart_RX_VECT_NUM)
        CY_ISR_PROTO(puttyUart_RXISR);
    #endif /* puttyUart_RX_INTERRUPT_ENABLED */

    void puttyUart_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void puttyUart_SetRxAddress1(uint8 address) ;
    void puttyUart_SetRxAddress2(uint8 address) ;

    void  puttyUart_SetRxInterruptMode(uint8 intSrc) ;
    uint8 puttyUart_ReadRxData(void) ;
    uint8 puttyUart_ReadRxStatus(void) ;
    uint8 puttyUart_GetChar(void) ;
    uint16 puttyUart_GetByte(void) ;
    uint8 puttyUart_GetRxBufferSize(void)
                                                            ;
    void puttyUart_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define puttyUart_GetRxInterruptSource   puttyUart_ReadRxStatus

#endif /* End (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) */

/* Only if TX is enabled */
#if(puttyUart_TX_ENABLED || puttyUart_HD_ENABLED)

    #if(puttyUart_TX_INTERRUPT_ENABLED)
        #define puttyUart_EnableTxInt()  CyIntEnable (puttyUart_TX_VECT_NUM)
        #define puttyUart_DisableTxInt() CyIntDisable(puttyUart_TX_VECT_NUM)
        #define puttyUart_SetPendingTxInt() CyIntSetPending(puttyUart_TX_VECT_NUM)
        #define puttyUart_ClearPendingTxInt() CyIntClearPending(puttyUart_TX_VECT_NUM)
        CY_ISR_PROTO(puttyUart_TXISR);
    #endif /* puttyUart_TX_INTERRUPT_ENABLED */

    void puttyUart_SetTxInterruptMode(uint8 intSrc) ;
    void puttyUart_WriteTxData(uint8 txDataByte) ;
    uint8 puttyUart_ReadTxStatus(void) ;
    void puttyUart_PutChar(uint8 txDataByte) ;
    void puttyUart_PutString(const char8 string[]) ;
    void puttyUart_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void puttyUart_PutCRLF(uint8 txDataByte) ;
    void puttyUart_ClearTxBuffer(void) ;
    void puttyUart_SetTxAddressMode(uint8 addressMode) ;
    void puttyUart_SendBreak(uint8 retMode) ;
    uint8 puttyUart_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define puttyUart_PutStringConst         puttyUart_PutString
    #define puttyUart_PutArrayConst          puttyUart_PutArray
    #define puttyUart_GetTxInterruptSource   puttyUart_ReadTxStatus

#endif /* End puttyUart_TX_ENABLED || puttyUart_HD_ENABLED */

#if(puttyUart_HD_ENABLED)
    void puttyUart_LoadRxConfig(void) ;
    void puttyUart_LoadTxConfig(void) ;
#endif /* End puttyUart_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_puttyUart) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    puttyUart_CyBtldrCommStart(void) CYSMALL ;
    void    puttyUart_CyBtldrCommStop(void) CYSMALL ;
    void    puttyUart_CyBtldrCommReset(void) CYSMALL ;
    cystatus puttyUart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus puttyUart_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_puttyUart)
        #define CyBtldrCommStart    puttyUart_CyBtldrCommStart
        #define CyBtldrCommStop     puttyUart_CyBtldrCommStop
        #define CyBtldrCommReset    puttyUart_CyBtldrCommReset
        #define CyBtldrCommWrite    puttyUart_CyBtldrCommWrite
        #define CyBtldrCommRead     puttyUart_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_puttyUart) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define puttyUart_BYTE2BYTE_TIME_OUT (25u)
    #define puttyUart_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define puttyUart_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define puttyUart_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define puttyUart_SET_SPACE      (0x00u)
#define puttyUart_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (puttyUart_TX_ENABLED) || (puttyUart_HD_ENABLED) )
    #if(puttyUart_TX_INTERRUPT_ENABLED)
        #define puttyUart_TX_VECT_NUM            (uint8)puttyUart_TXInternalInterrupt__INTC_NUMBER
        #define puttyUart_TX_PRIOR_NUM           (uint8)puttyUart_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* puttyUart_TX_INTERRUPT_ENABLED */

    #define puttyUart_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define puttyUart_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define puttyUart_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(puttyUart_TX_ENABLED)
        #define puttyUart_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (puttyUart_HD_ENABLED) */
        #define puttyUart_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (puttyUart_TX_ENABLED) */

    #define puttyUart_TX_STS_COMPLETE            (uint8)(0x01u << puttyUart_TX_STS_COMPLETE_SHIFT)
    #define puttyUart_TX_STS_FIFO_EMPTY          (uint8)(0x01u << puttyUart_TX_STS_FIFO_EMPTY_SHIFT)
    #define puttyUart_TX_STS_FIFO_FULL           (uint8)(0x01u << puttyUart_TX_STS_FIFO_FULL_SHIFT)
    #define puttyUart_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << puttyUart_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (puttyUart_TX_ENABLED) || (puttyUart_HD_ENABLED)*/

#if( (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) )
    #if(puttyUart_RX_INTERRUPT_ENABLED)
        #define puttyUart_RX_VECT_NUM            (uint8)puttyUart_RXInternalInterrupt__INTC_NUMBER
        #define puttyUart_RX_PRIOR_NUM           (uint8)puttyUart_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* puttyUart_RX_INTERRUPT_ENABLED */
    #define puttyUart_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define puttyUart_RX_STS_BREAK_SHIFT             (0x01u)
    #define puttyUart_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define puttyUart_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define puttyUart_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define puttyUart_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define puttyUart_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define puttyUart_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define puttyUart_RX_STS_MRKSPC           (uint8)(0x01u << puttyUart_RX_STS_MRKSPC_SHIFT)
    #define puttyUart_RX_STS_BREAK            (uint8)(0x01u << puttyUart_RX_STS_BREAK_SHIFT)
    #define puttyUart_RX_STS_PAR_ERROR        (uint8)(0x01u << puttyUart_RX_STS_PAR_ERROR_SHIFT)
    #define puttyUart_RX_STS_STOP_ERROR       (uint8)(0x01u << puttyUart_RX_STS_STOP_ERROR_SHIFT)
    #define puttyUart_RX_STS_OVERRUN          (uint8)(0x01u << puttyUart_RX_STS_OVERRUN_SHIFT)
    #define puttyUart_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << puttyUart_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define puttyUart_RX_STS_ADDR_MATCH       (uint8)(0x01u << puttyUart_RX_STS_ADDR_MATCH_SHIFT)
    #define puttyUart_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << puttyUart_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define puttyUart_RX_HW_MASK                     (0x7Fu)
#endif /* End (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) */

/* Control Register definitions */
#define puttyUart_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define puttyUart_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define puttyUart_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define puttyUart_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define puttyUart_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define puttyUart_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define puttyUart_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define puttyUart_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define puttyUart_CTRL_HD_SEND               (uint8)(0x01u << puttyUart_CTRL_HD_SEND_SHIFT)
#define puttyUart_CTRL_HD_SEND_BREAK         (uint8)(0x01u << puttyUart_CTRL_HD_SEND_BREAK_SHIFT)
#define puttyUart_CTRL_MARK                  (uint8)(0x01u << puttyUart_CTRL_MARK_SHIFT)
#define puttyUart_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << puttyUart_CTRL_PARITY_TYPE0_SHIFT)
#define puttyUart_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << puttyUart_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define puttyUart_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define puttyUart_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define puttyUart_SEND_BREAK                         (0x00u)
#define puttyUart_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define puttyUart_REINIT                             (0x02u)
#define puttyUart_SEND_WAIT_REINIT                   (0x03u)

#define puttyUart_OVER_SAMPLE_8                      (8u)
#define puttyUart_OVER_SAMPLE_16                     (16u)

#define puttyUart_BIT_CENTER                         (puttyUart_OVER_SAMPLE_COUNT - 2u)

#define puttyUart_FIFO_LENGTH                        (4u)
#define puttyUart_NUMBER_OF_START_BIT                (1u)
#define puttyUart_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define puttyUart_TXBITCTR_BREAKBITS8X   ((puttyUart_BREAK_BITS_TX * puttyUart_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define puttyUart_TXBITCTR_BREAKBITS ((puttyUart_BREAK_BITS_TX * puttyUart_OVER_SAMPLE_COUNT) - 1u)

#define puttyUart_HALF_BIT_COUNT   \
                            (((puttyUart_OVER_SAMPLE_COUNT / 2u) + (puttyUart_USE23POLLING * 1u)) - 2u)
#if (puttyUart_OVER_SAMPLE_COUNT == puttyUart_OVER_SAMPLE_8)
    #define puttyUart_HD_TXBITCTR_INIT   (((puttyUart_BREAK_BITS_TX + \
                            puttyUart_NUMBER_OF_START_BIT) * puttyUart_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define puttyUart_RXBITCTR_INIT  ((((puttyUart_BREAK_BITS_RX + puttyUart_NUMBER_OF_START_BIT) \
                            * puttyUart_OVER_SAMPLE_COUNT) + puttyUart_HALF_BIT_COUNT) - 1u)

#else /* puttyUart_OVER_SAMPLE_COUNT == puttyUart_OVER_SAMPLE_16 */
    #define puttyUart_HD_TXBITCTR_INIT   ((8u * puttyUart_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define puttyUart_RXBITCTR_INIT      (((7u * puttyUart_OVER_SAMPLE_COUNT) - 1u) + \
                                                      puttyUart_HALF_BIT_COUNT)
#endif /* End puttyUart_OVER_SAMPLE_COUNT */

#define puttyUart_HD_RXBITCTR_INIT                   puttyUart_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 puttyUart_initVar;
#if (puttyUart_TX_INTERRUPT_ENABLED && puttyUart_TX_ENABLED)
    extern volatile uint8 puttyUart_txBuffer[puttyUart_TX_BUFFER_SIZE];
    extern volatile uint8 puttyUart_txBufferRead;
    extern uint8 puttyUart_txBufferWrite;
#endif /* (puttyUart_TX_INTERRUPT_ENABLED && puttyUart_TX_ENABLED) */
#if (puttyUart_RX_INTERRUPT_ENABLED && (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED))
    extern uint8 puttyUart_errorStatus;
    extern volatile uint8 puttyUart_rxBuffer[puttyUart_RX_BUFFER_SIZE];
    extern volatile uint8 puttyUart_rxBufferRead;
    extern volatile uint8 puttyUart_rxBufferWrite;
    extern volatile uint8 puttyUart_rxBufferLoopDetect;
    extern volatile uint8 puttyUart_rxBufferOverflow;
    #if (puttyUart_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 puttyUart_rxAddressMode;
        extern volatile uint8 puttyUart_rxAddressDetected;
    #endif /* (puttyUart_RXHW_ADDRESS_ENABLED) */
#endif /* (puttyUart_RX_INTERRUPT_ENABLED && (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define puttyUart__B_UART__AM_SW_BYTE_BYTE 1
#define puttyUart__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define puttyUart__B_UART__AM_HW_BYTE_BY_BYTE 3
#define puttyUart__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define puttyUart__B_UART__AM_NONE 0

#define puttyUart__B_UART__NONE_REVB 0
#define puttyUart__B_UART__EVEN_REVB 1
#define puttyUart__B_UART__ODD_REVB 2
#define puttyUart__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define puttyUart_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define puttyUart_NUMBER_OF_STOP_BITS    (1u)

#if (puttyUart_RXHW_ADDRESS_ENABLED)
    #define puttyUart_RX_ADDRESS_MODE    (0u)
    #define puttyUart_RX_HW_ADDRESS1     (0u)
    #define puttyUart_RX_HW_ADDRESS2     (0u)
#endif /* (puttyUart_RXHW_ADDRESS_ENABLED) */

#define puttyUart_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << puttyUart_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << puttyUart_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << puttyUart_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << puttyUart_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << puttyUart_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << puttyUart_RX_STS_BREAK_SHIFT) \
                                        | (0 << puttyUart_RX_STS_OVERRUN_SHIFT))

#define puttyUart_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << puttyUart_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << puttyUart_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << puttyUart_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << puttyUart_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define puttyUart_CONTROL_REG \
                            (* (reg8 *) puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define puttyUart_CONTROL_PTR \
                            (  (reg8 *) puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(puttyUart_TX_ENABLED)
    #define puttyUart_TXDATA_REG          (* (reg8 *) puttyUart_BUART_sTX_TxShifter_u0__F0_REG)
    #define puttyUart_TXDATA_PTR          (  (reg8 *) puttyUart_BUART_sTX_TxShifter_u0__F0_REG)
    #define puttyUart_TXDATA_AUX_CTL_REG  (* (reg8 *) puttyUart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define puttyUart_TXDATA_AUX_CTL_PTR  (  (reg8 *) puttyUart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define puttyUart_TXSTATUS_REG        (* (reg8 *) puttyUart_BUART_sTX_TxSts__STATUS_REG)
    #define puttyUart_TXSTATUS_PTR        (  (reg8 *) puttyUart_BUART_sTX_TxSts__STATUS_REG)
    #define puttyUart_TXSTATUS_MASK_REG   (* (reg8 *) puttyUart_BUART_sTX_TxSts__MASK_REG)
    #define puttyUart_TXSTATUS_MASK_PTR   (  (reg8 *) puttyUart_BUART_sTX_TxSts__MASK_REG)
    #define puttyUart_TXSTATUS_ACTL_REG   (* (reg8 *) puttyUart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define puttyUart_TXSTATUS_ACTL_PTR   (  (reg8 *) puttyUart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(puttyUart_TXCLKGEN_DP)
        #define puttyUart_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define puttyUart_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define puttyUart_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define puttyUart_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define puttyUart_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define puttyUart_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define puttyUart_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define puttyUart_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define puttyUart_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define puttyUart_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) puttyUart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* puttyUart_TXCLKGEN_DP */

#endif /* End puttyUart_TX_ENABLED */

#if(puttyUart_HD_ENABLED)

    #define puttyUart_TXDATA_REG             (* (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__F1_REG )
    #define puttyUart_TXDATA_PTR             (  (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__F1_REG )
    #define puttyUart_TXDATA_AUX_CTL_REG     (* (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define puttyUart_TXDATA_AUX_CTL_PTR     (  (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define puttyUart_TXSTATUS_REG           (* (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart_TXSTATUS_PTR           (  (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart_TXSTATUS_MASK_REG      (* (reg8 *) puttyUart_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart_TXSTATUS_MASK_PTR      (  (reg8 *) puttyUart_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart_TXSTATUS_ACTL_REG      (* (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define puttyUart_TXSTATUS_ACTL_PTR      (  (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End puttyUart_HD_ENABLED */

#if( (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) )
    #define puttyUart_RXDATA_REG             (* (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__F0_REG )
    #define puttyUart_RXDATA_PTR             (  (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__F0_REG )
    #define puttyUart_RXADDRESS1_REG         (* (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__D0_REG )
    #define puttyUart_RXADDRESS1_PTR         (  (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__D0_REG )
    #define puttyUart_RXADDRESS2_REG         (* (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__D1_REG )
    #define puttyUart_RXADDRESS2_PTR         (  (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__D1_REG )
    #define puttyUart_RXDATA_AUX_CTL_REG     (* (reg8 *) puttyUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define puttyUart_RXBITCTR_PERIOD_REG    (* (reg8 *) puttyUart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define puttyUart_RXBITCTR_PERIOD_PTR    (  (reg8 *) puttyUart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define puttyUart_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) puttyUart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define puttyUart_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) puttyUart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define puttyUart_RXBITCTR_COUNTER_REG   (* (reg8 *) puttyUart_BUART_sRX_RxBitCounter__COUNT_REG )
    #define puttyUart_RXBITCTR_COUNTER_PTR   (  (reg8 *) puttyUart_BUART_sRX_RxBitCounter__COUNT_REG )

    #define puttyUart_RXSTATUS_REG           (* (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart_RXSTATUS_PTR           (  (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_REG )
    #define puttyUart_RXSTATUS_MASK_REG      (* (reg8 *) puttyUart_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart_RXSTATUS_MASK_PTR      (  (reg8 *) puttyUart_BUART_sRX_RxSts__MASK_REG )
    #define puttyUart_RXSTATUS_ACTL_REG      (* (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define puttyUart_RXSTATUS_ACTL_PTR      (  (reg8 *) puttyUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) */

#if(puttyUart_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define puttyUart_INTCLOCK_CLKEN_REG     (* (reg8 *) puttyUart_IntClock__PM_ACT_CFG)
    #define puttyUart_INTCLOCK_CLKEN_PTR     (  (reg8 *) puttyUart_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define puttyUart_INTCLOCK_CLKEN_MASK    puttyUart_IntClock__PM_ACT_MSK
#endif /* End puttyUart_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(puttyUart_TX_ENABLED)
    #define puttyUart_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End puttyUart_TX_ENABLED */

#if(puttyUart_HD_ENABLED)
    #define puttyUart_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End puttyUart_HD_ENABLED */

#if( (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) )
    #define puttyUart_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define puttyUart_WAIT_1_MS      puttyUart_BL_CHK_DELAY_MS   

#define puttyUart_TXBUFFERSIZE   puttyUart_TX_BUFFER_SIZE
#define puttyUart_RXBUFFERSIZE   puttyUart_RX_BUFFER_SIZE

#if (puttyUart_RXHW_ADDRESS_ENABLED)
    #define puttyUart_RXADDRESSMODE  puttyUart_RX_ADDRESS_MODE
    #define puttyUart_RXHWADDRESS1   puttyUart_RX_HW_ADDRESS1
    #define puttyUart_RXHWADDRESS2   puttyUart_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define puttyUart_RXAddressMode  puttyUart_RXADDRESSMODE
#endif /* (puttyUart_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define puttyUart_initvar                    puttyUart_initVar

#define puttyUart_RX_Enabled                 puttyUart_RX_ENABLED
#define puttyUart_TX_Enabled                 puttyUart_TX_ENABLED
#define puttyUart_HD_Enabled                 puttyUart_HD_ENABLED
#define puttyUart_RX_IntInterruptEnabled     puttyUart_RX_INTERRUPT_ENABLED
#define puttyUart_TX_IntInterruptEnabled     puttyUart_TX_INTERRUPT_ENABLED
#define puttyUart_InternalClockUsed          puttyUart_INTERNAL_CLOCK_USED
#define puttyUart_RXHW_Address_Enabled       puttyUart_RXHW_ADDRESS_ENABLED
#define puttyUart_OverSampleCount            puttyUart_OVER_SAMPLE_COUNT
#define puttyUart_ParityType                 puttyUart_PARITY_TYPE

#if( puttyUart_TX_ENABLED && (puttyUart_TXBUFFERSIZE > puttyUart_FIFO_LENGTH))
    #define puttyUart_TXBUFFER               puttyUart_txBuffer
    #define puttyUart_TXBUFFERREAD           puttyUart_txBufferRead
    #define puttyUart_TXBUFFERWRITE          puttyUart_txBufferWrite
#endif /* End puttyUart_TX_ENABLED */
#if( ( puttyUart_RX_ENABLED || puttyUart_HD_ENABLED ) && \
     (puttyUart_RXBUFFERSIZE > puttyUart_FIFO_LENGTH) )
    #define puttyUart_RXBUFFER               puttyUart_rxBuffer
    #define puttyUart_RXBUFFERREAD           puttyUart_rxBufferRead
    #define puttyUart_RXBUFFERWRITE          puttyUart_rxBufferWrite
    #define puttyUart_RXBUFFERLOOPDETECT     puttyUart_rxBufferLoopDetect
    #define puttyUart_RXBUFFER_OVERFLOW      puttyUart_rxBufferOverflow
#endif /* End puttyUart_RX_ENABLED */

#ifdef puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define puttyUart_CONTROL                puttyUart_CONTROL_REG
#endif /* End puttyUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(puttyUart_TX_ENABLED)
    #define puttyUart_TXDATA                 puttyUart_TXDATA_REG
    #define puttyUart_TXSTATUS               puttyUart_TXSTATUS_REG
    #define puttyUart_TXSTATUS_MASK          puttyUart_TXSTATUS_MASK_REG
    #define puttyUart_TXSTATUS_ACTL          puttyUart_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(puttyUart_TXCLKGEN_DP)
        #define puttyUart_TXBITCLKGEN_CTR        puttyUart_TXBITCLKGEN_CTR_REG
        #define puttyUart_TXBITCLKTX_COMPLETE    puttyUart_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define puttyUart_TXBITCTR_PERIOD        puttyUart_TXBITCTR_PERIOD_REG
        #define puttyUart_TXBITCTR_CONTROL       puttyUart_TXBITCTR_CONTROL_REG
        #define puttyUart_TXBITCTR_COUNTER       puttyUart_TXBITCTR_COUNTER_REG
    #endif /* puttyUart_TXCLKGEN_DP */
#endif /* End puttyUart_TX_ENABLED */

#if(puttyUart_HD_ENABLED)
    #define puttyUart_TXDATA                 puttyUart_TXDATA_REG
    #define puttyUart_TXSTATUS               puttyUart_TXSTATUS_REG
    #define puttyUart_TXSTATUS_MASK          puttyUart_TXSTATUS_MASK_REG
    #define puttyUart_TXSTATUS_ACTL          puttyUart_TXSTATUS_ACTL_REG
#endif /* End puttyUart_HD_ENABLED */

#if( (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) )
    #define puttyUart_RXDATA                 puttyUart_RXDATA_REG
    #define puttyUart_RXADDRESS1             puttyUart_RXADDRESS1_REG
    #define puttyUart_RXADDRESS2             puttyUart_RXADDRESS2_REG
    #define puttyUart_RXBITCTR_PERIOD        puttyUart_RXBITCTR_PERIOD_REG
    #define puttyUart_RXBITCTR_CONTROL       puttyUart_RXBITCTR_CONTROL_REG
    #define puttyUart_RXBITCTR_COUNTER       puttyUart_RXBITCTR_COUNTER_REG
    #define puttyUart_RXSTATUS               puttyUart_RXSTATUS_REG
    #define puttyUart_RXSTATUS_MASK          puttyUart_RXSTATUS_MASK_REG
    #define puttyUart_RXSTATUS_ACTL          puttyUart_RXSTATUS_ACTL_REG
#endif /* End  (puttyUart_RX_ENABLED) || (puttyUart_HD_ENABLED) */

#if(puttyUart_INTERNAL_CLOCK_USED)
    #define puttyUart_INTCLOCK_CLKEN         puttyUart_INTCLOCK_CLKEN_REG
#endif /* End puttyUart_INTERNAL_CLOCK_USED */

#define puttyUart_WAIT_FOR_COMLETE_REINIT    puttyUart_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_puttyUart_H */


/* [] END OF FILE */
