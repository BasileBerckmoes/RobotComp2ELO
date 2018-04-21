/*******************************************************************************
* File Name: BleUart.h
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


#if !defined(CY_UART_BleUart_H)
#define CY_UART_BleUart_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define BleUart_RX_ENABLED                     (1u)
#define BleUart_TX_ENABLED                     (1u)
#define BleUart_HD_ENABLED                     (0u)
#define BleUart_RX_INTERRUPT_ENABLED           (0u)
#define BleUart_TX_INTERRUPT_ENABLED           (0u)
#define BleUart_INTERNAL_CLOCK_USED            (1u)
#define BleUart_RXHW_ADDRESS_ENABLED           (0u)
#define BleUart_OVER_SAMPLE_COUNT              (8u)
#define BleUart_PARITY_TYPE                    (0u)
#define BleUart_PARITY_TYPE_SW                 (0u)
#define BleUart_BREAK_DETECT                   (0u)
#define BleUart_BREAK_BITS_TX                  (13u)
#define BleUart_BREAK_BITS_RX                  (13u)
#define BleUart_TXCLKGEN_DP                    (1u)
#define BleUart_USE23POLLING                   (1u)
#define BleUart_FLOW_CONTROL                   (0u)
#define BleUart_CLK_FREQ                       (0u)
#define BleUart_TX_BUFFER_SIZE                 (4u)
#define BleUart_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define BleUart_CONTROL_REG_REMOVED            (0u)
#else
    #define BleUart_CONTROL_REG_REMOVED            (1u)
#endif /* End BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct BleUart_backupStruct_
{
    uint8 enableState;

    #if(BleUart_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End BleUart_CONTROL_REG_REMOVED */

} BleUart_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void BleUart_Start(void) ;
void BleUart_Stop(void) ;
uint8 BleUart_ReadControlRegister(void) ;
void BleUart_WriteControlRegister(uint8 control) ;

void BleUart_Init(void) ;
void BleUart_Enable(void) ;
void BleUart_SaveConfig(void) ;
void BleUart_RestoreConfig(void) ;
void BleUart_Sleep(void) ;
void BleUart_Wakeup(void) ;

/* Only if RX is enabled */
#if( (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) )

    #if (BleUart_RX_INTERRUPT_ENABLED)
        #define BleUart_EnableRxInt()  CyIntEnable (BleUart_RX_VECT_NUM)
        #define BleUart_DisableRxInt() CyIntDisable(BleUart_RX_VECT_NUM)
        CY_ISR_PROTO(BleUart_RXISR);
    #endif /* BleUart_RX_INTERRUPT_ENABLED */

    void BleUart_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void BleUart_SetRxAddress1(uint8 address) ;
    void BleUart_SetRxAddress2(uint8 address) ;

    void  BleUart_SetRxInterruptMode(uint8 intSrc) ;
    uint8 BleUart_ReadRxData(void) ;
    uint8 BleUart_ReadRxStatus(void) ;
    uint8 BleUart_GetChar(void) ;
    uint16 BleUart_GetByte(void) ;
    uint8 BleUart_GetRxBufferSize(void)
                                                            ;
    void BleUart_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define BleUart_GetRxInterruptSource   BleUart_ReadRxStatus

#endif /* End (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) */

/* Only if TX is enabled */
#if(BleUart_TX_ENABLED || BleUart_HD_ENABLED)

    #if(BleUart_TX_INTERRUPT_ENABLED)
        #define BleUart_EnableTxInt()  CyIntEnable (BleUart_TX_VECT_NUM)
        #define BleUart_DisableTxInt() CyIntDisable(BleUart_TX_VECT_NUM)
        #define BleUart_SetPendingTxInt() CyIntSetPending(BleUart_TX_VECT_NUM)
        #define BleUart_ClearPendingTxInt() CyIntClearPending(BleUart_TX_VECT_NUM)
        CY_ISR_PROTO(BleUart_TXISR);
    #endif /* BleUart_TX_INTERRUPT_ENABLED */

    void BleUart_SetTxInterruptMode(uint8 intSrc) ;
    void BleUart_WriteTxData(uint8 txDataByte) ;
    uint8 BleUart_ReadTxStatus(void) ;
    void BleUart_PutChar(uint8 txDataByte) ;
    void BleUart_PutString(const char8 string[]) ;
    void BleUart_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void BleUart_PutCRLF(uint8 txDataByte) ;
    void BleUart_ClearTxBuffer(void) ;
    void BleUart_SetTxAddressMode(uint8 addressMode) ;
    void BleUart_SendBreak(uint8 retMode) ;
    uint8 BleUart_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define BleUart_PutStringConst         BleUart_PutString
    #define BleUart_PutArrayConst          BleUart_PutArray
    #define BleUart_GetTxInterruptSource   BleUart_ReadTxStatus

#endif /* End BleUart_TX_ENABLED || BleUart_HD_ENABLED */

#if(BleUart_HD_ENABLED)
    void BleUart_LoadRxConfig(void) ;
    void BleUart_LoadTxConfig(void) ;
#endif /* End BleUart_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BleUart) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    BleUart_CyBtldrCommStart(void) CYSMALL ;
    void    BleUart_CyBtldrCommStop(void) CYSMALL ;
    void    BleUart_CyBtldrCommReset(void) CYSMALL ;
    cystatus BleUart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus BleUart_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BleUart)
        #define CyBtldrCommStart    BleUart_CyBtldrCommStart
        #define CyBtldrCommStop     BleUart_CyBtldrCommStop
        #define CyBtldrCommReset    BleUart_CyBtldrCommReset
        #define CyBtldrCommWrite    BleUart_CyBtldrCommWrite
        #define CyBtldrCommRead     BleUart_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BleUart) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define BleUart_BYTE2BYTE_TIME_OUT (25u)
    #define BleUart_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define BleUart_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define BleUart_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define BleUart_SET_SPACE      (0x00u)
#define BleUart_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (BleUart_TX_ENABLED) || (BleUart_HD_ENABLED) )
    #if(BleUart_TX_INTERRUPT_ENABLED)
        #define BleUart_TX_VECT_NUM            (uint8)BleUart_TXInternalInterrupt__INTC_NUMBER
        #define BleUart_TX_PRIOR_NUM           (uint8)BleUart_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BleUart_TX_INTERRUPT_ENABLED */

    #define BleUart_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define BleUart_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define BleUart_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(BleUart_TX_ENABLED)
        #define BleUart_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (BleUart_HD_ENABLED) */
        #define BleUart_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (BleUart_TX_ENABLED) */

    #define BleUart_TX_STS_COMPLETE            (uint8)(0x01u << BleUart_TX_STS_COMPLETE_SHIFT)
    #define BleUart_TX_STS_FIFO_EMPTY          (uint8)(0x01u << BleUart_TX_STS_FIFO_EMPTY_SHIFT)
    #define BleUart_TX_STS_FIFO_FULL           (uint8)(0x01u << BleUart_TX_STS_FIFO_FULL_SHIFT)
    #define BleUart_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << BleUart_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (BleUart_TX_ENABLED) || (BleUart_HD_ENABLED)*/

#if( (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) )
    #if(BleUart_RX_INTERRUPT_ENABLED)
        #define BleUart_RX_VECT_NUM            (uint8)BleUart_RXInternalInterrupt__INTC_NUMBER
        #define BleUart_RX_PRIOR_NUM           (uint8)BleUart_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BleUart_RX_INTERRUPT_ENABLED */
    #define BleUart_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define BleUart_RX_STS_BREAK_SHIFT             (0x01u)
    #define BleUart_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define BleUart_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define BleUart_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define BleUart_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define BleUart_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define BleUart_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define BleUart_RX_STS_MRKSPC           (uint8)(0x01u << BleUart_RX_STS_MRKSPC_SHIFT)
    #define BleUart_RX_STS_BREAK            (uint8)(0x01u << BleUart_RX_STS_BREAK_SHIFT)
    #define BleUart_RX_STS_PAR_ERROR        (uint8)(0x01u << BleUart_RX_STS_PAR_ERROR_SHIFT)
    #define BleUart_RX_STS_STOP_ERROR       (uint8)(0x01u << BleUart_RX_STS_STOP_ERROR_SHIFT)
    #define BleUart_RX_STS_OVERRUN          (uint8)(0x01u << BleUart_RX_STS_OVERRUN_SHIFT)
    #define BleUart_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << BleUart_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define BleUart_RX_STS_ADDR_MATCH       (uint8)(0x01u << BleUart_RX_STS_ADDR_MATCH_SHIFT)
    #define BleUart_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << BleUart_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define BleUart_RX_HW_MASK                     (0x7Fu)
#endif /* End (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) */

/* Control Register definitions */
#define BleUart_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define BleUart_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define BleUart_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define BleUart_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define BleUart_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define BleUart_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define BleUart_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define BleUart_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define BleUart_CTRL_HD_SEND               (uint8)(0x01u << BleUart_CTRL_HD_SEND_SHIFT)
#define BleUart_CTRL_HD_SEND_BREAK         (uint8)(0x01u << BleUart_CTRL_HD_SEND_BREAK_SHIFT)
#define BleUart_CTRL_MARK                  (uint8)(0x01u << BleUart_CTRL_MARK_SHIFT)
#define BleUart_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << BleUart_CTRL_PARITY_TYPE0_SHIFT)
#define BleUart_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << BleUart_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define BleUart_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define BleUart_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define BleUart_SEND_BREAK                         (0x00u)
#define BleUart_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define BleUart_REINIT                             (0x02u)
#define BleUart_SEND_WAIT_REINIT                   (0x03u)

#define BleUart_OVER_SAMPLE_8                      (8u)
#define BleUart_OVER_SAMPLE_16                     (16u)

#define BleUart_BIT_CENTER                         (BleUart_OVER_SAMPLE_COUNT - 2u)

#define BleUart_FIFO_LENGTH                        (4u)
#define BleUart_NUMBER_OF_START_BIT                (1u)
#define BleUart_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define BleUart_TXBITCTR_BREAKBITS8X   ((BleUart_BREAK_BITS_TX * BleUart_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define BleUart_TXBITCTR_BREAKBITS ((BleUart_BREAK_BITS_TX * BleUart_OVER_SAMPLE_COUNT) - 1u)

#define BleUart_HALF_BIT_COUNT   \
                            (((BleUart_OVER_SAMPLE_COUNT / 2u) + (BleUart_USE23POLLING * 1u)) - 2u)
#if (BleUart_OVER_SAMPLE_COUNT == BleUart_OVER_SAMPLE_8)
    #define BleUart_HD_TXBITCTR_INIT   (((BleUart_BREAK_BITS_TX + \
                            BleUart_NUMBER_OF_START_BIT) * BleUart_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define BleUart_RXBITCTR_INIT  ((((BleUart_BREAK_BITS_RX + BleUart_NUMBER_OF_START_BIT) \
                            * BleUart_OVER_SAMPLE_COUNT) + BleUart_HALF_BIT_COUNT) - 1u)

#else /* BleUart_OVER_SAMPLE_COUNT == BleUart_OVER_SAMPLE_16 */
    #define BleUart_HD_TXBITCTR_INIT   ((8u * BleUart_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define BleUart_RXBITCTR_INIT      (((7u * BleUart_OVER_SAMPLE_COUNT) - 1u) + \
                                                      BleUart_HALF_BIT_COUNT)
#endif /* End BleUart_OVER_SAMPLE_COUNT */

#define BleUart_HD_RXBITCTR_INIT                   BleUart_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 BleUart_initVar;
#if (BleUart_TX_INTERRUPT_ENABLED && BleUart_TX_ENABLED)
    extern volatile uint8 BleUart_txBuffer[BleUart_TX_BUFFER_SIZE];
    extern volatile uint8 BleUart_txBufferRead;
    extern uint8 BleUart_txBufferWrite;
#endif /* (BleUart_TX_INTERRUPT_ENABLED && BleUart_TX_ENABLED) */
#if (BleUart_RX_INTERRUPT_ENABLED && (BleUart_RX_ENABLED || BleUart_HD_ENABLED))
    extern uint8 BleUart_errorStatus;
    extern volatile uint8 BleUart_rxBuffer[BleUart_RX_BUFFER_SIZE];
    extern volatile uint8 BleUart_rxBufferRead;
    extern volatile uint8 BleUart_rxBufferWrite;
    extern volatile uint8 BleUart_rxBufferLoopDetect;
    extern volatile uint8 BleUart_rxBufferOverflow;
    #if (BleUart_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 BleUart_rxAddressMode;
        extern volatile uint8 BleUart_rxAddressDetected;
    #endif /* (BleUart_RXHW_ADDRESS_ENABLED) */
#endif /* (BleUart_RX_INTERRUPT_ENABLED && (BleUart_RX_ENABLED || BleUart_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define BleUart__B_UART__AM_SW_BYTE_BYTE 1
#define BleUart__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define BleUart__B_UART__AM_HW_BYTE_BY_BYTE 3
#define BleUart__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define BleUart__B_UART__AM_NONE 0

#define BleUart__B_UART__NONE_REVB 0
#define BleUart__B_UART__EVEN_REVB 1
#define BleUart__B_UART__ODD_REVB 2
#define BleUart__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define BleUart_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define BleUart_NUMBER_OF_STOP_BITS    (1u)

#if (BleUart_RXHW_ADDRESS_ENABLED)
    #define BleUart_RX_ADDRESS_MODE    (0u)
    #define BleUart_RX_HW_ADDRESS1     (0u)
    #define BleUart_RX_HW_ADDRESS2     (0u)
#endif /* (BleUart_RXHW_ADDRESS_ENABLED) */

#define BleUart_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << BleUart_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << BleUart_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << BleUart_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << BleUart_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << BleUart_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << BleUart_RX_STS_BREAK_SHIFT) \
                                        | (0 << BleUart_RX_STS_OVERRUN_SHIFT))

#define BleUart_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << BleUart_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << BleUart_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << BleUart_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << BleUart_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BleUart_CONTROL_REG \
                            (* (reg8 *) BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define BleUart_CONTROL_PTR \
                            (  (reg8 *) BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BleUart_TX_ENABLED)
    #define BleUart_TXDATA_REG          (* (reg8 *) BleUart_BUART_sTX_TxShifter_u0__F0_REG)
    #define BleUart_TXDATA_PTR          (  (reg8 *) BleUart_BUART_sTX_TxShifter_u0__F0_REG)
    #define BleUart_TXDATA_AUX_CTL_REG  (* (reg8 *) BleUart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BleUart_TXDATA_AUX_CTL_PTR  (  (reg8 *) BleUart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BleUart_TXSTATUS_REG        (* (reg8 *) BleUart_BUART_sTX_TxSts__STATUS_REG)
    #define BleUart_TXSTATUS_PTR        (  (reg8 *) BleUart_BUART_sTX_TxSts__STATUS_REG)
    #define BleUart_TXSTATUS_MASK_REG   (* (reg8 *) BleUart_BUART_sTX_TxSts__MASK_REG)
    #define BleUart_TXSTATUS_MASK_PTR   (  (reg8 *) BleUart_BUART_sTX_TxSts__MASK_REG)
    #define BleUart_TXSTATUS_ACTL_REG   (* (reg8 *) BleUart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define BleUart_TXSTATUS_ACTL_PTR   (  (reg8 *) BleUart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(BleUart_TXCLKGEN_DP)
        #define BleUart_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BleUart_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BleUart_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define BleUart_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define BleUart_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BleUart_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BleUart_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BleUart_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BleUart_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define BleUart_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) BleUart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* BleUart_TXCLKGEN_DP */

#endif /* End BleUart_TX_ENABLED */

#if(BleUart_HD_ENABLED)

    #define BleUart_TXDATA_REG             (* (reg8 *) BleUart_BUART_sRX_RxShifter_u0__F1_REG )
    #define BleUart_TXDATA_PTR             (  (reg8 *) BleUart_BUART_sRX_RxShifter_u0__F1_REG )
    #define BleUart_TXDATA_AUX_CTL_REG     (* (reg8 *) BleUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define BleUart_TXDATA_AUX_CTL_PTR     (  (reg8 *) BleUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BleUart_TXSTATUS_REG           (* (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart_TXSTATUS_PTR           (  (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart_TXSTATUS_MASK_REG      (* (reg8 *) BleUart_BUART_sRX_RxSts__MASK_REG )
    #define BleUart_TXSTATUS_MASK_PTR      (  (reg8 *) BleUart_BUART_sRX_RxSts__MASK_REG )
    #define BleUart_TXSTATUS_ACTL_REG      (* (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BleUart_TXSTATUS_ACTL_PTR      (  (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End BleUart_HD_ENABLED */

#if( (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) )
    #define BleUart_RXDATA_REG             (* (reg8 *) BleUart_BUART_sRX_RxShifter_u0__F0_REG )
    #define BleUart_RXDATA_PTR             (  (reg8 *) BleUart_BUART_sRX_RxShifter_u0__F0_REG )
    #define BleUart_RXADDRESS1_REG         (* (reg8 *) BleUart_BUART_sRX_RxShifter_u0__D0_REG )
    #define BleUart_RXADDRESS1_PTR         (  (reg8 *) BleUart_BUART_sRX_RxShifter_u0__D0_REG )
    #define BleUart_RXADDRESS2_REG         (* (reg8 *) BleUart_BUART_sRX_RxShifter_u0__D1_REG )
    #define BleUart_RXADDRESS2_PTR         (  (reg8 *) BleUart_BUART_sRX_RxShifter_u0__D1_REG )
    #define BleUart_RXDATA_AUX_CTL_REG     (* (reg8 *) BleUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BleUart_RXBITCTR_PERIOD_REG    (* (reg8 *) BleUart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BleUart_RXBITCTR_PERIOD_PTR    (  (reg8 *) BleUart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BleUart_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BleUart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BleUart_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BleUart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BleUart_RXBITCTR_COUNTER_REG   (* (reg8 *) BleUart_BUART_sRX_RxBitCounter__COUNT_REG )
    #define BleUart_RXBITCTR_COUNTER_PTR   (  (reg8 *) BleUart_BUART_sRX_RxBitCounter__COUNT_REG )

    #define BleUart_RXSTATUS_REG           (* (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart_RXSTATUS_PTR           (  (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart_RXSTATUS_MASK_REG      (* (reg8 *) BleUart_BUART_sRX_RxSts__MASK_REG )
    #define BleUart_RXSTATUS_MASK_PTR      (  (reg8 *) BleUart_BUART_sRX_RxSts__MASK_REG )
    #define BleUart_RXSTATUS_ACTL_REG      (* (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BleUart_RXSTATUS_ACTL_PTR      (  (reg8 *) BleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) */

#if(BleUart_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define BleUart_INTCLOCK_CLKEN_REG     (* (reg8 *) BleUart_IntClock__PM_ACT_CFG)
    #define BleUart_INTCLOCK_CLKEN_PTR     (  (reg8 *) BleUart_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define BleUart_INTCLOCK_CLKEN_MASK    BleUart_IntClock__PM_ACT_MSK
#endif /* End BleUart_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(BleUart_TX_ENABLED)
    #define BleUart_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End BleUart_TX_ENABLED */

#if(BleUart_HD_ENABLED)
    #define BleUart_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End BleUart_HD_ENABLED */

#if( (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) )
    #define BleUart_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define BleUart_WAIT_1_MS      BleUart_BL_CHK_DELAY_MS   

#define BleUart_TXBUFFERSIZE   BleUart_TX_BUFFER_SIZE
#define BleUart_RXBUFFERSIZE   BleUart_RX_BUFFER_SIZE

#if (BleUart_RXHW_ADDRESS_ENABLED)
    #define BleUart_RXADDRESSMODE  BleUart_RX_ADDRESS_MODE
    #define BleUart_RXHWADDRESS1   BleUart_RX_HW_ADDRESS1
    #define BleUart_RXHWADDRESS2   BleUart_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define BleUart_RXAddressMode  BleUart_RXADDRESSMODE
#endif /* (BleUart_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define BleUart_initvar                    BleUart_initVar

#define BleUart_RX_Enabled                 BleUart_RX_ENABLED
#define BleUart_TX_Enabled                 BleUart_TX_ENABLED
#define BleUart_HD_Enabled                 BleUart_HD_ENABLED
#define BleUart_RX_IntInterruptEnabled     BleUart_RX_INTERRUPT_ENABLED
#define BleUart_TX_IntInterruptEnabled     BleUart_TX_INTERRUPT_ENABLED
#define BleUart_InternalClockUsed          BleUart_INTERNAL_CLOCK_USED
#define BleUart_RXHW_Address_Enabled       BleUart_RXHW_ADDRESS_ENABLED
#define BleUart_OverSampleCount            BleUart_OVER_SAMPLE_COUNT
#define BleUart_ParityType                 BleUart_PARITY_TYPE

#if( BleUart_TX_ENABLED && (BleUart_TXBUFFERSIZE > BleUart_FIFO_LENGTH))
    #define BleUart_TXBUFFER               BleUart_txBuffer
    #define BleUart_TXBUFFERREAD           BleUart_txBufferRead
    #define BleUart_TXBUFFERWRITE          BleUart_txBufferWrite
#endif /* End BleUart_TX_ENABLED */
#if( ( BleUart_RX_ENABLED || BleUart_HD_ENABLED ) && \
     (BleUart_RXBUFFERSIZE > BleUart_FIFO_LENGTH) )
    #define BleUart_RXBUFFER               BleUart_rxBuffer
    #define BleUart_RXBUFFERREAD           BleUart_rxBufferRead
    #define BleUart_RXBUFFERWRITE          BleUart_rxBufferWrite
    #define BleUart_RXBUFFERLOOPDETECT     BleUart_rxBufferLoopDetect
    #define BleUart_RXBUFFER_OVERFLOW      BleUart_rxBufferOverflow
#endif /* End BleUart_RX_ENABLED */

#ifdef BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BleUart_CONTROL                BleUart_CONTROL_REG
#endif /* End BleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BleUart_TX_ENABLED)
    #define BleUart_TXDATA                 BleUart_TXDATA_REG
    #define BleUart_TXSTATUS               BleUart_TXSTATUS_REG
    #define BleUart_TXSTATUS_MASK          BleUart_TXSTATUS_MASK_REG
    #define BleUart_TXSTATUS_ACTL          BleUart_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(BleUart_TXCLKGEN_DP)
        #define BleUart_TXBITCLKGEN_CTR        BleUart_TXBITCLKGEN_CTR_REG
        #define BleUart_TXBITCLKTX_COMPLETE    BleUart_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define BleUart_TXBITCTR_PERIOD        BleUart_TXBITCTR_PERIOD_REG
        #define BleUart_TXBITCTR_CONTROL       BleUart_TXBITCTR_CONTROL_REG
        #define BleUart_TXBITCTR_COUNTER       BleUart_TXBITCTR_COUNTER_REG
    #endif /* BleUart_TXCLKGEN_DP */
#endif /* End BleUart_TX_ENABLED */

#if(BleUart_HD_ENABLED)
    #define BleUart_TXDATA                 BleUart_TXDATA_REG
    #define BleUart_TXSTATUS               BleUart_TXSTATUS_REG
    #define BleUart_TXSTATUS_MASK          BleUart_TXSTATUS_MASK_REG
    #define BleUart_TXSTATUS_ACTL          BleUart_TXSTATUS_ACTL_REG
#endif /* End BleUart_HD_ENABLED */

#if( (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) )
    #define BleUart_RXDATA                 BleUart_RXDATA_REG
    #define BleUart_RXADDRESS1             BleUart_RXADDRESS1_REG
    #define BleUart_RXADDRESS2             BleUart_RXADDRESS2_REG
    #define BleUart_RXBITCTR_PERIOD        BleUart_RXBITCTR_PERIOD_REG
    #define BleUart_RXBITCTR_CONTROL       BleUart_RXBITCTR_CONTROL_REG
    #define BleUart_RXBITCTR_COUNTER       BleUart_RXBITCTR_COUNTER_REG
    #define BleUart_RXSTATUS               BleUart_RXSTATUS_REG
    #define BleUart_RXSTATUS_MASK          BleUart_RXSTATUS_MASK_REG
    #define BleUart_RXSTATUS_ACTL          BleUart_RXSTATUS_ACTL_REG
#endif /* End  (BleUart_RX_ENABLED) || (BleUart_HD_ENABLED) */

#if(BleUart_INTERNAL_CLOCK_USED)
    #define BleUart_INTCLOCK_CLKEN         BleUart_INTCLOCK_CLKEN_REG
#endif /* End BleUart_INTERNAL_CLOCK_USED */

#define BleUart_WAIT_FOR_COMLETE_REINIT    BleUart_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_BleUart_H */


/* [] END OF FILE */
