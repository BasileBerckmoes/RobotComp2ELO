/*******************************************************************************
* File Name: BleUart1.h
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


#if !defined(CY_UART_BleUart1_H)
#define CY_UART_BleUart1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define BleUart1_RX_ENABLED                     (1u)
#define BleUart1_TX_ENABLED                     (1u)
#define BleUart1_HD_ENABLED                     (0u)
#define BleUart1_RX_INTERRUPT_ENABLED           (0u)
#define BleUart1_TX_INTERRUPT_ENABLED           (0u)
#define BleUart1_INTERNAL_CLOCK_USED            (1u)
#define BleUart1_RXHW_ADDRESS_ENABLED           (0u)
#define BleUart1_OVER_SAMPLE_COUNT              (8u)
#define BleUart1_PARITY_TYPE                    (0u)
#define BleUart1_PARITY_TYPE_SW                 (0u)
#define BleUart1_BREAK_DETECT                   (0u)
#define BleUart1_BREAK_BITS_TX                  (13u)
#define BleUart1_BREAK_BITS_RX                  (13u)
#define BleUart1_TXCLKGEN_DP                    (1u)
#define BleUart1_USE23POLLING                   (1u)
#define BleUart1_FLOW_CONTROL                   (0u)
#define BleUart1_CLK_FREQ                       (0u)
#define BleUart1_TX_BUFFER_SIZE                 (4u)
#define BleUart1_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define BleUart1_CONTROL_REG_REMOVED            (0u)
#else
    #define BleUart1_CONTROL_REG_REMOVED            (1u)
#endif /* End BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct BleUart1_backupStruct_
{
    uint8 enableState;

    #if(BleUart1_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End BleUart1_CONTROL_REG_REMOVED */

} BleUart1_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void BleUart1_Start(void) ;
void BleUart1_Stop(void) ;
uint8 BleUart1_ReadControlRegister(void) ;
void BleUart1_WriteControlRegister(uint8 control) ;

void BleUart1_Init(void) ;
void BleUart1_Enable(void) ;
void BleUart1_SaveConfig(void) ;
void BleUart1_RestoreConfig(void) ;
void BleUart1_Sleep(void) ;
void BleUart1_Wakeup(void) ;

/* Only if RX is enabled */
#if( (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) )

    #if (BleUart1_RX_INTERRUPT_ENABLED)
        #define BleUart1_EnableRxInt()  CyIntEnable (BleUart1_RX_VECT_NUM)
        #define BleUart1_DisableRxInt() CyIntDisable(BleUart1_RX_VECT_NUM)
        CY_ISR_PROTO(BleUart1_RXISR);
    #endif /* BleUart1_RX_INTERRUPT_ENABLED */

    void BleUart1_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void BleUart1_SetRxAddress1(uint8 address) ;
    void BleUart1_SetRxAddress2(uint8 address) ;

    void  BleUart1_SetRxInterruptMode(uint8 intSrc) ;
    uint8 BleUart1_ReadRxData(void) ;
    uint8 BleUart1_ReadRxStatus(void) ;
    uint8 BleUart1_GetChar(void) ;
    uint16 BleUart1_GetByte(void) ;
    uint8 BleUart1_GetRxBufferSize(void)
                                                            ;
    void BleUart1_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define BleUart1_GetRxInterruptSource   BleUart1_ReadRxStatus

#endif /* End (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) */

/* Only if TX is enabled */
#if(BleUart1_TX_ENABLED || BleUart1_HD_ENABLED)

    #if(BleUart1_TX_INTERRUPT_ENABLED)
        #define BleUart1_EnableTxInt()  CyIntEnable (BleUart1_TX_VECT_NUM)
        #define BleUart1_DisableTxInt() CyIntDisable(BleUart1_TX_VECT_NUM)
        #define BleUart1_SetPendingTxInt() CyIntSetPending(BleUart1_TX_VECT_NUM)
        #define BleUart1_ClearPendingTxInt() CyIntClearPending(BleUart1_TX_VECT_NUM)
        CY_ISR_PROTO(BleUart1_TXISR);
    #endif /* BleUart1_TX_INTERRUPT_ENABLED */

    void BleUart1_SetTxInterruptMode(uint8 intSrc) ;
    void BleUart1_WriteTxData(uint8 txDataByte) ;
    uint8 BleUart1_ReadTxStatus(void) ;
    void BleUart1_PutChar(uint8 txDataByte) ;
    void BleUart1_PutString(const char8 string[]) ;
    void BleUart1_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void BleUart1_PutCRLF(uint8 txDataByte) ;
    void BleUart1_ClearTxBuffer(void) ;
    void BleUart1_SetTxAddressMode(uint8 addressMode) ;
    void BleUart1_SendBreak(uint8 retMode) ;
    uint8 BleUart1_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define BleUart1_PutStringConst         BleUart1_PutString
    #define BleUart1_PutArrayConst          BleUart1_PutArray
    #define BleUart1_GetTxInterruptSource   BleUart1_ReadTxStatus

#endif /* End BleUart1_TX_ENABLED || BleUart1_HD_ENABLED */

#if(BleUart1_HD_ENABLED)
    void BleUart1_LoadRxConfig(void) ;
    void BleUart1_LoadTxConfig(void) ;
#endif /* End BleUart1_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BleUart1) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    BleUart1_CyBtldrCommStart(void) CYSMALL ;
    void    BleUart1_CyBtldrCommStop(void) CYSMALL ;
    void    BleUart1_CyBtldrCommReset(void) CYSMALL ;
    cystatus BleUart1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus BleUart1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BleUart1)
        #define CyBtldrCommStart    BleUart1_CyBtldrCommStart
        #define CyBtldrCommStop     BleUart1_CyBtldrCommStop
        #define CyBtldrCommReset    BleUart1_CyBtldrCommReset
        #define CyBtldrCommWrite    BleUart1_CyBtldrCommWrite
        #define CyBtldrCommRead     BleUart1_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BleUart1) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define BleUart1_BYTE2BYTE_TIME_OUT (25u)
    #define BleUart1_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define BleUart1_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define BleUart1_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define BleUart1_SET_SPACE      (0x00u)
#define BleUart1_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (BleUart1_TX_ENABLED) || (BleUart1_HD_ENABLED) )
    #if(BleUart1_TX_INTERRUPT_ENABLED)
        #define BleUart1_TX_VECT_NUM            (uint8)BleUart1_TXInternalInterrupt__INTC_NUMBER
        #define BleUart1_TX_PRIOR_NUM           (uint8)BleUart1_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BleUart1_TX_INTERRUPT_ENABLED */

    #define BleUart1_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define BleUart1_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define BleUart1_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(BleUart1_TX_ENABLED)
        #define BleUart1_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (BleUart1_HD_ENABLED) */
        #define BleUart1_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (BleUart1_TX_ENABLED) */

    #define BleUart1_TX_STS_COMPLETE            (uint8)(0x01u << BleUart1_TX_STS_COMPLETE_SHIFT)
    #define BleUart1_TX_STS_FIFO_EMPTY          (uint8)(0x01u << BleUart1_TX_STS_FIFO_EMPTY_SHIFT)
    #define BleUart1_TX_STS_FIFO_FULL           (uint8)(0x01u << BleUart1_TX_STS_FIFO_FULL_SHIFT)
    #define BleUart1_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << BleUart1_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (BleUart1_TX_ENABLED) || (BleUart1_HD_ENABLED)*/

#if( (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) )
    #if(BleUart1_RX_INTERRUPT_ENABLED)
        #define BleUart1_RX_VECT_NUM            (uint8)BleUart1_RXInternalInterrupt__INTC_NUMBER
        #define BleUart1_RX_PRIOR_NUM           (uint8)BleUart1_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BleUart1_RX_INTERRUPT_ENABLED */
    #define BleUart1_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define BleUart1_RX_STS_BREAK_SHIFT             (0x01u)
    #define BleUart1_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define BleUart1_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define BleUart1_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define BleUart1_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define BleUart1_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define BleUart1_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define BleUart1_RX_STS_MRKSPC           (uint8)(0x01u << BleUart1_RX_STS_MRKSPC_SHIFT)
    #define BleUart1_RX_STS_BREAK            (uint8)(0x01u << BleUart1_RX_STS_BREAK_SHIFT)
    #define BleUart1_RX_STS_PAR_ERROR        (uint8)(0x01u << BleUart1_RX_STS_PAR_ERROR_SHIFT)
    #define BleUart1_RX_STS_STOP_ERROR       (uint8)(0x01u << BleUart1_RX_STS_STOP_ERROR_SHIFT)
    #define BleUart1_RX_STS_OVERRUN          (uint8)(0x01u << BleUart1_RX_STS_OVERRUN_SHIFT)
    #define BleUart1_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << BleUart1_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define BleUart1_RX_STS_ADDR_MATCH       (uint8)(0x01u << BleUart1_RX_STS_ADDR_MATCH_SHIFT)
    #define BleUart1_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << BleUart1_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define BleUart1_RX_HW_MASK                     (0x7Fu)
#endif /* End (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) */

/* Control Register definitions */
#define BleUart1_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define BleUart1_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define BleUart1_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define BleUart1_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define BleUart1_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define BleUart1_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define BleUart1_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define BleUart1_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define BleUart1_CTRL_HD_SEND               (uint8)(0x01u << BleUart1_CTRL_HD_SEND_SHIFT)
#define BleUart1_CTRL_HD_SEND_BREAK         (uint8)(0x01u << BleUart1_CTRL_HD_SEND_BREAK_SHIFT)
#define BleUart1_CTRL_MARK                  (uint8)(0x01u << BleUart1_CTRL_MARK_SHIFT)
#define BleUart1_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << BleUart1_CTRL_PARITY_TYPE0_SHIFT)
#define BleUart1_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << BleUart1_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define BleUart1_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define BleUart1_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define BleUart1_SEND_BREAK                         (0x00u)
#define BleUart1_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define BleUart1_REINIT                             (0x02u)
#define BleUart1_SEND_WAIT_REINIT                   (0x03u)

#define BleUart1_OVER_SAMPLE_8                      (8u)
#define BleUart1_OVER_SAMPLE_16                     (16u)

#define BleUart1_BIT_CENTER                         (BleUart1_OVER_SAMPLE_COUNT - 2u)

#define BleUart1_FIFO_LENGTH                        (4u)
#define BleUart1_NUMBER_OF_START_BIT                (1u)
#define BleUart1_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define BleUart1_TXBITCTR_BREAKBITS8X   ((BleUart1_BREAK_BITS_TX * BleUart1_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define BleUart1_TXBITCTR_BREAKBITS ((BleUart1_BREAK_BITS_TX * BleUart1_OVER_SAMPLE_COUNT) - 1u)

#define BleUart1_HALF_BIT_COUNT   \
                            (((BleUart1_OVER_SAMPLE_COUNT / 2u) + (BleUart1_USE23POLLING * 1u)) - 2u)
#if (BleUart1_OVER_SAMPLE_COUNT == BleUart1_OVER_SAMPLE_8)
    #define BleUart1_HD_TXBITCTR_INIT   (((BleUart1_BREAK_BITS_TX + \
                            BleUart1_NUMBER_OF_START_BIT) * BleUart1_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define BleUart1_RXBITCTR_INIT  ((((BleUart1_BREAK_BITS_RX + BleUart1_NUMBER_OF_START_BIT) \
                            * BleUart1_OVER_SAMPLE_COUNT) + BleUart1_HALF_BIT_COUNT) - 1u)

#else /* BleUart1_OVER_SAMPLE_COUNT == BleUart1_OVER_SAMPLE_16 */
    #define BleUart1_HD_TXBITCTR_INIT   ((8u * BleUart1_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define BleUart1_RXBITCTR_INIT      (((7u * BleUart1_OVER_SAMPLE_COUNT) - 1u) + \
                                                      BleUart1_HALF_BIT_COUNT)
#endif /* End BleUart1_OVER_SAMPLE_COUNT */

#define BleUart1_HD_RXBITCTR_INIT                   BleUart1_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 BleUart1_initVar;
#if (BleUart1_TX_INTERRUPT_ENABLED && BleUart1_TX_ENABLED)
    extern volatile uint8 BleUart1_txBuffer[BleUart1_TX_BUFFER_SIZE];
    extern volatile uint8 BleUart1_txBufferRead;
    extern uint8 BleUart1_txBufferWrite;
#endif /* (BleUart1_TX_INTERRUPT_ENABLED && BleUart1_TX_ENABLED) */
#if (BleUart1_RX_INTERRUPT_ENABLED && (BleUart1_RX_ENABLED || BleUart1_HD_ENABLED))
    extern uint8 BleUart1_errorStatus;
    extern volatile uint8 BleUart1_rxBuffer[BleUart1_RX_BUFFER_SIZE];
    extern volatile uint8 BleUart1_rxBufferRead;
    extern volatile uint8 BleUart1_rxBufferWrite;
    extern volatile uint8 BleUart1_rxBufferLoopDetect;
    extern volatile uint8 BleUart1_rxBufferOverflow;
    #if (BleUart1_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 BleUart1_rxAddressMode;
        extern volatile uint8 BleUart1_rxAddressDetected;
    #endif /* (BleUart1_RXHW_ADDRESS_ENABLED) */
#endif /* (BleUart1_RX_INTERRUPT_ENABLED && (BleUart1_RX_ENABLED || BleUart1_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define BleUart1__B_UART__AM_SW_BYTE_BYTE 1
#define BleUart1__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define BleUart1__B_UART__AM_HW_BYTE_BY_BYTE 3
#define BleUart1__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define BleUart1__B_UART__AM_NONE 0

#define BleUart1__B_UART__NONE_REVB 0
#define BleUart1__B_UART__EVEN_REVB 1
#define BleUart1__B_UART__ODD_REVB 2
#define BleUart1__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define BleUart1_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define BleUart1_NUMBER_OF_STOP_BITS    (1u)

#if (BleUart1_RXHW_ADDRESS_ENABLED)
    #define BleUart1_RX_ADDRESS_MODE    (0u)
    #define BleUart1_RX_HW_ADDRESS1     (0u)
    #define BleUart1_RX_HW_ADDRESS2     (0u)
#endif /* (BleUart1_RXHW_ADDRESS_ENABLED) */

#define BleUart1_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << BleUart1_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << BleUart1_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << BleUart1_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << BleUart1_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << BleUart1_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << BleUart1_RX_STS_BREAK_SHIFT) \
                                        | (0 << BleUart1_RX_STS_OVERRUN_SHIFT))

#define BleUart1_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << BleUart1_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << BleUart1_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << BleUart1_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << BleUart1_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BleUart1_CONTROL_REG \
                            (* (reg8 *) BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define BleUart1_CONTROL_PTR \
                            (  (reg8 *) BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BleUart1_TX_ENABLED)
    #define BleUart1_TXDATA_REG          (* (reg8 *) BleUart1_BUART_sTX_TxShifter_u0__F0_REG)
    #define BleUart1_TXDATA_PTR          (  (reg8 *) BleUart1_BUART_sTX_TxShifter_u0__F0_REG)
    #define BleUart1_TXDATA_AUX_CTL_REG  (* (reg8 *) BleUart1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BleUart1_TXDATA_AUX_CTL_PTR  (  (reg8 *) BleUart1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BleUart1_TXSTATUS_REG        (* (reg8 *) BleUart1_BUART_sTX_TxSts__STATUS_REG)
    #define BleUart1_TXSTATUS_PTR        (  (reg8 *) BleUart1_BUART_sTX_TxSts__STATUS_REG)
    #define BleUart1_TXSTATUS_MASK_REG   (* (reg8 *) BleUart1_BUART_sTX_TxSts__MASK_REG)
    #define BleUart1_TXSTATUS_MASK_PTR   (  (reg8 *) BleUart1_BUART_sTX_TxSts__MASK_REG)
    #define BleUart1_TXSTATUS_ACTL_REG   (* (reg8 *) BleUart1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define BleUart1_TXSTATUS_ACTL_PTR   (  (reg8 *) BleUart1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(BleUart1_TXCLKGEN_DP)
        #define BleUart1_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BleUart1_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BleUart1_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define BleUart1_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define BleUart1_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BleUart1_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BleUart1_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BleUart1_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BleUart1_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define BleUart1_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) BleUart1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* BleUart1_TXCLKGEN_DP */

#endif /* End BleUart1_TX_ENABLED */

#if(BleUart1_HD_ENABLED)

    #define BleUart1_TXDATA_REG             (* (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__F1_REG )
    #define BleUart1_TXDATA_PTR             (  (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__F1_REG )
    #define BleUart1_TXDATA_AUX_CTL_REG     (* (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define BleUart1_TXDATA_AUX_CTL_PTR     (  (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BleUart1_TXSTATUS_REG           (* (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart1_TXSTATUS_PTR           (  (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart1_TXSTATUS_MASK_REG      (* (reg8 *) BleUart1_BUART_sRX_RxSts__MASK_REG )
    #define BleUart1_TXSTATUS_MASK_PTR      (  (reg8 *) BleUart1_BUART_sRX_RxSts__MASK_REG )
    #define BleUart1_TXSTATUS_ACTL_REG      (* (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BleUart1_TXSTATUS_ACTL_PTR      (  (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End BleUart1_HD_ENABLED */

#if( (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) )
    #define BleUart1_RXDATA_REG             (* (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__F0_REG )
    #define BleUart1_RXDATA_PTR             (  (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__F0_REG )
    #define BleUart1_RXADDRESS1_REG         (* (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__D0_REG )
    #define BleUart1_RXADDRESS1_PTR         (  (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__D0_REG )
    #define BleUart1_RXADDRESS2_REG         (* (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__D1_REG )
    #define BleUart1_RXADDRESS2_PTR         (  (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__D1_REG )
    #define BleUart1_RXDATA_AUX_CTL_REG     (* (reg8 *) BleUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BleUart1_RXBITCTR_PERIOD_REG    (* (reg8 *) BleUart1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BleUart1_RXBITCTR_PERIOD_PTR    (  (reg8 *) BleUart1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BleUart1_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BleUart1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BleUart1_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BleUart1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BleUart1_RXBITCTR_COUNTER_REG   (* (reg8 *) BleUart1_BUART_sRX_RxBitCounter__COUNT_REG )
    #define BleUart1_RXBITCTR_COUNTER_PTR   (  (reg8 *) BleUart1_BUART_sRX_RxBitCounter__COUNT_REG )

    #define BleUart1_RXSTATUS_REG           (* (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart1_RXSTATUS_PTR           (  (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define BleUart1_RXSTATUS_MASK_REG      (* (reg8 *) BleUart1_BUART_sRX_RxSts__MASK_REG )
    #define BleUart1_RXSTATUS_MASK_PTR      (  (reg8 *) BleUart1_BUART_sRX_RxSts__MASK_REG )
    #define BleUart1_RXSTATUS_ACTL_REG      (* (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BleUart1_RXSTATUS_ACTL_PTR      (  (reg8 *) BleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) */

#if(BleUart1_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define BleUart1_INTCLOCK_CLKEN_REG     (* (reg8 *) BleUart1_IntClock__PM_ACT_CFG)
    #define BleUart1_INTCLOCK_CLKEN_PTR     (  (reg8 *) BleUart1_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define BleUart1_INTCLOCK_CLKEN_MASK    BleUart1_IntClock__PM_ACT_MSK
#endif /* End BleUart1_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(BleUart1_TX_ENABLED)
    #define BleUart1_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End BleUart1_TX_ENABLED */

#if(BleUart1_HD_ENABLED)
    #define BleUart1_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End BleUart1_HD_ENABLED */

#if( (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) )
    #define BleUart1_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define BleUart1_WAIT_1_MS      BleUart1_BL_CHK_DELAY_MS   

#define BleUart1_TXBUFFERSIZE   BleUart1_TX_BUFFER_SIZE
#define BleUart1_RXBUFFERSIZE   BleUart1_RX_BUFFER_SIZE

#if (BleUart1_RXHW_ADDRESS_ENABLED)
    #define BleUart1_RXADDRESSMODE  BleUart1_RX_ADDRESS_MODE
    #define BleUart1_RXHWADDRESS1   BleUart1_RX_HW_ADDRESS1
    #define BleUart1_RXHWADDRESS2   BleUart1_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define BleUart1_RXAddressMode  BleUart1_RXADDRESSMODE
#endif /* (BleUart1_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define BleUart1_initvar                    BleUart1_initVar

#define BleUart1_RX_Enabled                 BleUart1_RX_ENABLED
#define BleUart1_TX_Enabled                 BleUart1_TX_ENABLED
#define BleUart1_HD_Enabled                 BleUart1_HD_ENABLED
#define BleUart1_RX_IntInterruptEnabled     BleUart1_RX_INTERRUPT_ENABLED
#define BleUart1_TX_IntInterruptEnabled     BleUart1_TX_INTERRUPT_ENABLED
#define BleUart1_InternalClockUsed          BleUart1_INTERNAL_CLOCK_USED
#define BleUart1_RXHW_Address_Enabled       BleUart1_RXHW_ADDRESS_ENABLED
#define BleUart1_OverSampleCount            BleUart1_OVER_SAMPLE_COUNT
#define BleUart1_ParityType                 BleUart1_PARITY_TYPE

#if( BleUart1_TX_ENABLED && (BleUart1_TXBUFFERSIZE > BleUart1_FIFO_LENGTH))
    #define BleUart1_TXBUFFER               BleUart1_txBuffer
    #define BleUart1_TXBUFFERREAD           BleUart1_txBufferRead
    #define BleUart1_TXBUFFERWRITE          BleUart1_txBufferWrite
#endif /* End BleUart1_TX_ENABLED */
#if( ( BleUart1_RX_ENABLED || BleUart1_HD_ENABLED ) && \
     (BleUart1_RXBUFFERSIZE > BleUart1_FIFO_LENGTH) )
    #define BleUart1_RXBUFFER               BleUart1_rxBuffer
    #define BleUart1_RXBUFFERREAD           BleUart1_rxBufferRead
    #define BleUart1_RXBUFFERWRITE          BleUart1_rxBufferWrite
    #define BleUart1_RXBUFFERLOOPDETECT     BleUart1_rxBufferLoopDetect
    #define BleUart1_RXBUFFER_OVERFLOW      BleUart1_rxBufferOverflow
#endif /* End BleUart1_RX_ENABLED */

#ifdef BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BleUart1_CONTROL                BleUart1_CONTROL_REG
#endif /* End BleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BleUart1_TX_ENABLED)
    #define BleUart1_TXDATA                 BleUart1_TXDATA_REG
    #define BleUart1_TXSTATUS               BleUart1_TXSTATUS_REG
    #define BleUart1_TXSTATUS_MASK          BleUart1_TXSTATUS_MASK_REG
    #define BleUart1_TXSTATUS_ACTL          BleUart1_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(BleUart1_TXCLKGEN_DP)
        #define BleUart1_TXBITCLKGEN_CTR        BleUart1_TXBITCLKGEN_CTR_REG
        #define BleUart1_TXBITCLKTX_COMPLETE    BleUart1_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define BleUart1_TXBITCTR_PERIOD        BleUart1_TXBITCTR_PERIOD_REG
        #define BleUart1_TXBITCTR_CONTROL       BleUart1_TXBITCTR_CONTROL_REG
        #define BleUart1_TXBITCTR_COUNTER       BleUart1_TXBITCTR_COUNTER_REG
    #endif /* BleUart1_TXCLKGEN_DP */
#endif /* End BleUart1_TX_ENABLED */

#if(BleUart1_HD_ENABLED)
    #define BleUart1_TXDATA                 BleUart1_TXDATA_REG
    #define BleUart1_TXSTATUS               BleUart1_TXSTATUS_REG
    #define BleUart1_TXSTATUS_MASK          BleUart1_TXSTATUS_MASK_REG
    #define BleUart1_TXSTATUS_ACTL          BleUart1_TXSTATUS_ACTL_REG
#endif /* End BleUart1_HD_ENABLED */

#if( (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) )
    #define BleUart1_RXDATA                 BleUart1_RXDATA_REG
    #define BleUart1_RXADDRESS1             BleUart1_RXADDRESS1_REG
    #define BleUart1_RXADDRESS2             BleUart1_RXADDRESS2_REG
    #define BleUart1_RXBITCTR_PERIOD        BleUart1_RXBITCTR_PERIOD_REG
    #define BleUart1_RXBITCTR_CONTROL       BleUart1_RXBITCTR_CONTROL_REG
    #define BleUart1_RXBITCTR_COUNTER       BleUart1_RXBITCTR_COUNTER_REG
    #define BleUart1_RXSTATUS               BleUart1_RXSTATUS_REG
    #define BleUart1_RXSTATUS_MASK          BleUart1_RXSTATUS_MASK_REG
    #define BleUart1_RXSTATUS_ACTL          BleUart1_RXSTATUS_ACTL_REG
#endif /* End  (BleUart1_RX_ENABLED) || (BleUart1_HD_ENABLED) */

#if(BleUart1_INTERNAL_CLOCK_USED)
    #define BleUart1_INTCLOCK_CLKEN         BleUart1_INTCLOCK_CLKEN_REG
#endif /* End BleUart1_INTERNAL_CLOCK_USED */

#define BleUart1_WAIT_FOR_COMLETE_REINIT    BleUart1_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_BleUart1_H */


/* [] END OF FILE */
