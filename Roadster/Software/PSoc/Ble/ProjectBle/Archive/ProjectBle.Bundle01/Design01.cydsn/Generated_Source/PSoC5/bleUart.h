/*******************************************************************************
* File Name: bleUart.h
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


#if !defined(CY_UART_bleUart_H)
#define CY_UART_bleUart_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define bleUart_RX_ENABLED                     (1u)
#define bleUart_TX_ENABLED                     (1u)
#define bleUart_HD_ENABLED                     (0u)
#define bleUart_RX_INTERRUPT_ENABLED           (0u)
#define bleUart_TX_INTERRUPT_ENABLED           (0u)
#define bleUart_INTERNAL_CLOCK_USED            (1u)
#define bleUart_RXHW_ADDRESS_ENABLED           (0u)
#define bleUart_OVER_SAMPLE_COUNT              (8u)
#define bleUart_PARITY_TYPE                    (0u)
#define bleUart_PARITY_TYPE_SW                 (0u)
#define bleUart_BREAK_DETECT                   (0u)
#define bleUart_BREAK_BITS_TX                  (13u)
#define bleUart_BREAK_BITS_RX                  (13u)
#define bleUart_TXCLKGEN_DP                    (1u)
#define bleUart_USE23POLLING                   (1u)
#define bleUart_FLOW_CONTROL                   (0u)
#define bleUart_CLK_FREQ                       (0u)
#define bleUart_TX_BUFFER_SIZE                 (4u)
#define bleUart_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define bleUart_CONTROL_REG_REMOVED            (0u)
#else
    #define bleUart_CONTROL_REG_REMOVED            (1u)
#endif /* End bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct bleUart_backupStruct_
{
    uint8 enableState;

    #if(bleUart_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End bleUart_CONTROL_REG_REMOVED */

} bleUart_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void bleUart_Start(void) ;
void bleUart_Stop(void) ;
uint8 bleUart_ReadControlRegister(void) ;
void bleUart_WriteControlRegister(uint8 control) ;

void bleUart_Init(void) ;
void bleUart_Enable(void) ;
void bleUart_SaveConfig(void) ;
void bleUart_RestoreConfig(void) ;
void bleUart_Sleep(void) ;
void bleUart_Wakeup(void) ;

/* Only if RX is enabled */
#if( (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) )

    #if (bleUart_RX_INTERRUPT_ENABLED)
        #define bleUart_EnableRxInt()  CyIntEnable (bleUart_RX_VECT_NUM)
        #define bleUart_DisableRxInt() CyIntDisable(bleUart_RX_VECT_NUM)
        CY_ISR_PROTO(bleUart_RXISR);
    #endif /* bleUart_RX_INTERRUPT_ENABLED */

    void bleUart_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void bleUart_SetRxAddress1(uint8 address) ;
    void bleUart_SetRxAddress2(uint8 address) ;

    void  bleUart_SetRxInterruptMode(uint8 intSrc) ;
    uint8 bleUart_ReadRxData(void) ;
    uint8 bleUart_ReadRxStatus(void) ;
    uint8 bleUart_GetChar(void) ;
    uint16 bleUart_GetByte(void) ;
    uint8 bleUart_GetRxBufferSize(void)
                                                            ;
    void bleUart_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define bleUart_GetRxInterruptSource   bleUart_ReadRxStatus

#endif /* End (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) */

/* Only if TX is enabled */
#if(bleUart_TX_ENABLED || bleUart_HD_ENABLED)

    #if(bleUart_TX_INTERRUPT_ENABLED)
        #define bleUart_EnableTxInt()  CyIntEnable (bleUart_TX_VECT_NUM)
        #define bleUart_DisableTxInt() CyIntDisable(bleUart_TX_VECT_NUM)
        #define bleUart_SetPendingTxInt() CyIntSetPending(bleUart_TX_VECT_NUM)
        #define bleUart_ClearPendingTxInt() CyIntClearPending(bleUart_TX_VECT_NUM)
        CY_ISR_PROTO(bleUart_TXISR);
    #endif /* bleUart_TX_INTERRUPT_ENABLED */

    void bleUart_SetTxInterruptMode(uint8 intSrc) ;
    void bleUart_WriteTxData(uint8 txDataByte) ;
    uint8 bleUart_ReadTxStatus(void) ;
    void bleUart_PutChar(uint8 txDataByte) ;
    void bleUart_PutString(const char8 string[]) ;
    void bleUart_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void bleUart_PutCRLF(uint8 txDataByte) ;
    void bleUart_ClearTxBuffer(void) ;
    void bleUart_SetTxAddressMode(uint8 addressMode) ;
    void bleUart_SendBreak(uint8 retMode) ;
    uint8 bleUart_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define bleUart_PutStringConst         bleUart_PutString
    #define bleUart_PutArrayConst          bleUart_PutArray
    #define bleUart_GetTxInterruptSource   bleUart_ReadTxStatus

#endif /* End bleUart_TX_ENABLED || bleUart_HD_ENABLED */

#if(bleUart_HD_ENABLED)
    void bleUart_LoadRxConfig(void) ;
    void bleUart_LoadTxConfig(void) ;
#endif /* End bleUart_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bleUart) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    bleUart_CyBtldrCommStart(void) CYSMALL ;
    void    bleUart_CyBtldrCommStop(void) CYSMALL ;
    void    bleUart_CyBtldrCommReset(void) CYSMALL ;
    cystatus bleUart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus bleUart_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bleUart)
        #define CyBtldrCommStart    bleUart_CyBtldrCommStart
        #define CyBtldrCommStop     bleUart_CyBtldrCommStop
        #define CyBtldrCommReset    bleUart_CyBtldrCommReset
        #define CyBtldrCommWrite    bleUart_CyBtldrCommWrite
        #define CyBtldrCommRead     bleUart_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bleUart) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define bleUart_BYTE2BYTE_TIME_OUT (25u)
    #define bleUart_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define bleUart_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define bleUart_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define bleUart_SET_SPACE      (0x00u)
#define bleUart_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (bleUart_TX_ENABLED) || (bleUart_HD_ENABLED) )
    #if(bleUart_TX_INTERRUPT_ENABLED)
        #define bleUart_TX_VECT_NUM            (uint8)bleUart_TXInternalInterrupt__INTC_NUMBER
        #define bleUart_TX_PRIOR_NUM           (uint8)bleUart_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* bleUart_TX_INTERRUPT_ENABLED */

    #define bleUart_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define bleUart_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define bleUart_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(bleUart_TX_ENABLED)
        #define bleUart_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (bleUart_HD_ENABLED) */
        #define bleUart_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (bleUart_TX_ENABLED) */

    #define bleUart_TX_STS_COMPLETE            (uint8)(0x01u << bleUart_TX_STS_COMPLETE_SHIFT)
    #define bleUart_TX_STS_FIFO_EMPTY          (uint8)(0x01u << bleUart_TX_STS_FIFO_EMPTY_SHIFT)
    #define bleUart_TX_STS_FIFO_FULL           (uint8)(0x01u << bleUart_TX_STS_FIFO_FULL_SHIFT)
    #define bleUart_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << bleUart_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (bleUart_TX_ENABLED) || (bleUart_HD_ENABLED)*/

#if( (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) )
    #if(bleUart_RX_INTERRUPT_ENABLED)
        #define bleUart_RX_VECT_NUM            (uint8)bleUart_RXInternalInterrupt__INTC_NUMBER
        #define bleUart_RX_PRIOR_NUM           (uint8)bleUart_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* bleUart_RX_INTERRUPT_ENABLED */
    #define bleUart_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define bleUart_RX_STS_BREAK_SHIFT             (0x01u)
    #define bleUart_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define bleUart_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define bleUart_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define bleUart_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define bleUart_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define bleUart_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define bleUart_RX_STS_MRKSPC           (uint8)(0x01u << bleUart_RX_STS_MRKSPC_SHIFT)
    #define bleUart_RX_STS_BREAK            (uint8)(0x01u << bleUart_RX_STS_BREAK_SHIFT)
    #define bleUart_RX_STS_PAR_ERROR        (uint8)(0x01u << bleUart_RX_STS_PAR_ERROR_SHIFT)
    #define bleUart_RX_STS_STOP_ERROR       (uint8)(0x01u << bleUart_RX_STS_STOP_ERROR_SHIFT)
    #define bleUart_RX_STS_OVERRUN          (uint8)(0x01u << bleUart_RX_STS_OVERRUN_SHIFT)
    #define bleUart_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << bleUart_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define bleUart_RX_STS_ADDR_MATCH       (uint8)(0x01u << bleUart_RX_STS_ADDR_MATCH_SHIFT)
    #define bleUart_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << bleUart_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define bleUart_RX_HW_MASK                     (0x7Fu)
#endif /* End (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) */

/* Control Register definitions */
#define bleUart_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define bleUart_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define bleUart_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define bleUart_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define bleUart_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define bleUart_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define bleUart_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define bleUart_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define bleUart_CTRL_HD_SEND               (uint8)(0x01u << bleUart_CTRL_HD_SEND_SHIFT)
#define bleUart_CTRL_HD_SEND_BREAK         (uint8)(0x01u << bleUart_CTRL_HD_SEND_BREAK_SHIFT)
#define bleUart_CTRL_MARK                  (uint8)(0x01u << bleUart_CTRL_MARK_SHIFT)
#define bleUart_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << bleUart_CTRL_PARITY_TYPE0_SHIFT)
#define bleUart_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << bleUart_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define bleUart_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define bleUart_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define bleUart_SEND_BREAK                         (0x00u)
#define bleUart_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define bleUart_REINIT                             (0x02u)
#define bleUart_SEND_WAIT_REINIT                   (0x03u)

#define bleUart_OVER_SAMPLE_8                      (8u)
#define bleUart_OVER_SAMPLE_16                     (16u)

#define bleUart_BIT_CENTER                         (bleUart_OVER_SAMPLE_COUNT - 2u)

#define bleUart_FIFO_LENGTH                        (4u)
#define bleUart_NUMBER_OF_START_BIT                (1u)
#define bleUart_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define bleUart_TXBITCTR_BREAKBITS8X   ((bleUart_BREAK_BITS_TX * bleUart_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define bleUart_TXBITCTR_BREAKBITS ((bleUart_BREAK_BITS_TX * bleUart_OVER_SAMPLE_COUNT) - 1u)

#define bleUart_HALF_BIT_COUNT   \
                            (((bleUart_OVER_SAMPLE_COUNT / 2u) + (bleUart_USE23POLLING * 1u)) - 2u)
#if (bleUart_OVER_SAMPLE_COUNT == bleUart_OVER_SAMPLE_8)
    #define bleUart_HD_TXBITCTR_INIT   (((bleUart_BREAK_BITS_TX + \
                            bleUart_NUMBER_OF_START_BIT) * bleUart_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define bleUart_RXBITCTR_INIT  ((((bleUart_BREAK_BITS_RX + bleUart_NUMBER_OF_START_BIT) \
                            * bleUart_OVER_SAMPLE_COUNT) + bleUart_HALF_BIT_COUNT) - 1u)

#else /* bleUart_OVER_SAMPLE_COUNT == bleUart_OVER_SAMPLE_16 */
    #define bleUart_HD_TXBITCTR_INIT   ((8u * bleUart_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define bleUart_RXBITCTR_INIT      (((7u * bleUart_OVER_SAMPLE_COUNT) - 1u) + \
                                                      bleUart_HALF_BIT_COUNT)
#endif /* End bleUart_OVER_SAMPLE_COUNT */

#define bleUart_HD_RXBITCTR_INIT                   bleUart_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 bleUart_initVar;
#if (bleUart_TX_INTERRUPT_ENABLED && bleUart_TX_ENABLED)
    extern volatile uint8 bleUart_txBuffer[bleUart_TX_BUFFER_SIZE];
    extern volatile uint8 bleUart_txBufferRead;
    extern uint8 bleUart_txBufferWrite;
#endif /* (bleUart_TX_INTERRUPT_ENABLED && bleUart_TX_ENABLED) */
#if (bleUart_RX_INTERRUPT_ENABLED && (bleUart_RX_ENABLED || bleUart_HD_ENABLED))
    extern uint8 bleUart_errorStatus;
    extern volatile uint8 bleUart_rxBuffer[bleUart_RX_BUFFER_SIZE];
    extern volatile uint8 bleUart_rxBufferRead;
    extern volatile uint8 bleUart_rxBufferWrite;
    extern volatile uint8 bleUart_rxBufferLoopDetect;
    extern volatile uint8 bleUart_rxBufferOverflow;
    #if (bleUart_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 bleUart_rxAddressMode;
        extern volatile uint8 bleUart_rxAddressDetected;
    #endif /* (bleUart_RXHW_ADDRESS_ENABLED) */
#endif /* (bleUart_RX_INTERRUPT_ENABLED && (bleUart_RX_ENABLED || bleUart_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define bleUart__B_UART__AM_SW_BYTE_BYTE 1
#define bleUart__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define bleUart__B_UART__AM_HW_BYTE_BY_BYTE 3
#define bleUart__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define bleUart__B_UART__AM_NONE 0

#define bleUart__B_UART__NONE_REVB 0
#define bleUart__B_UART__EVEN_REVB 1
#define bleUart__B_UART__ODD_REVB 2
#define bleUart__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define bleUart_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define bleUart_NUMBER_OF_STOP_BITS    (1u)

#if (bleUart_RXHW_ADDRESS_ENABLED)
    #define bleUart_RX_ADDRESS_MODE    (0u)
    #define bleUart_RX_HW_ADDRESS1     (0u)
    #define bleUart_RX_HW_ADDRESS2     (0u)
#endif /* (bleUart_RXHW_ADDRESS_ENABLED) */

#define bleUart_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << bleUart_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << bleUart_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << bleUart_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << bleUart_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << bleUart_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << bleUart_RX_STS_BREAK_SHIFT) \
                                        | (0 << bleUart_RX_STS_OVERRUN_SHIFT))

#define bleUart_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << bleUart_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << bleUart_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << bleUart_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << bleUart_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define bleUart_CONTROL_REG \
                            (* (reg8 *) bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define bleUart_CONTROL_PTR \
                            (  (reg8 *) bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(bleUart_TX_ENABLED)
    #define bleUart_TXDATA_REG          (* (reg8 *) bleUart_BUART_sTX_TxShifter_u0__F0_REG)
    #define bleUart_TXDATA_PTR          (  (reg8 *) bleUart_BUART_sTX_TxShifter_u0__F0_REG)
    #define bleUart_TXDATA_AUX_CTL_REG  (* (reg8 *) bleUart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define bleUart_TXDATA_AUX_CTL_PTR  (  (reg8 *) bleUart_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define bleUart_TXSTATUS_REG        (* (reg8 *) bleUart_BUART_sTX_TxSts__STATUS_REG)
    #define bleUart_TXSTATUS_PTR        (  (reg8 *) bleUart_BUART_sTX_TxSts__STATUS_REG)
    #define bleUart_TXSTATUS_MASK_REG   (* (reg8 *) bleUart_BUART_sTX_TxSts__MASK_REG)
    #define bleUart_TXSTATUS_MASK_PTR   (  (reg8 *) bleUart_BUART_sTX_TxSts__MASK_REG)
    #define bleUart_TXSTATUS_ACTL_REG   (* (reg8 *) bleUart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define bleUart_TXSTATUS_ACTL_PTR   (  (reg8 *) bleUart_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(bleUart_TXCLKGEN_DP)
        #define bleUart_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define bleUart_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define bleUart_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define bleUart_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define bleUart_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define bleUart_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define bleUart_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define bleUart_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define bleUart_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define bleUart_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) bleUart_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* bleUart_TXCLKGEN_DP */

#endif /* End bleUart_TX_ENABLED */

#if(bleUart_HD_ENABLED)

    #define bleUart_TXDATA_REG             (* (reg8 *) bleUart_BUART_sRX_RxShifter_u0__F1_REG )
    #define bleUart_TXDATA_PTR             (  (reg8 *) bleUart_BUART_sRX_RxShifter_u0__F1_REG )
    #define bleUart_TXDATA_AUX_CTL_REG     (* (reg8 *) bleUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define bleUart_TXDATA_AUX_CTL_PTR     (  (reg8 *) bleUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define bleUart_TXSTATUS_REG           (* (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart_TXSTATUS_PTR           (  (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart_TXSTATUS_MASK_REG      (* (reg8 *) bleUart_BUART_sRX_RxSts__MASK_REG )
    #define bleUart_TXSTATUS_MASK_PTR      (  (reg8 *) bleUart_BUART_sRX_RxSts__MASK_REG )
    #define bleUart_TXSTATUS_ACTL_REG      (* (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define bleUart_TXSTATUS_ACTL_PTR      (  (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End bleUart_HD_ENABLED */

#if( (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) )
    #define bleUart_RXDATA_REG             (* (reg8 *) bleUart_BUART_sRX_RxShifter_u0__F0_REG )
    #define bleUart_RXDATA_PTR             (  (reg8 *) bleUart_BUART_sRX_RxShifter_u0__F0_REG )
    #define bleUart_RXADDRESS1_REG         (* (reg8 *) bleUart_BUART_sRX_RxShifter_u0__D0_REG )
    #define bleUart_RXADDRESS1_PTR         (  (reg8 *) bleUart_BUART_sRX_RxShifter_u0__D0_REG )
    #define bleUart_RXADDRESS2_REG         (* (reg8 *) bleUart_BUART_sRX_RxShifter_u0__D1_REG )
    #define bleUart_RXADDRESS2_PTR         (  (reg8 *) bleUart_BUART_sRX_RxShifter_u0__D1_REG )
    #define bleUart_RXDATA_AUX_CTL_REG     (* (reg8 *) bleUart_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define bleUart_RXBITCTR_PERIOD_REG    (* (reg8 *) bleUart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define bleUart_RXBITCTR_PERIOD_PTR    (  (reg8 *) bleUart_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define bleUart_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) bleUart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define bleUart_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) bleUart_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define bleUart_RXBITCTR_COUNTER_REG   (* (reg8 *) bleUart_BUART_sRX_RxBitCounter__COUNT_REG )
    #define bleUart_RXBITCTR_COUNTER_PTR   (  (reg8 *) bleUart_BUART_sRX_RxBitCounter__COUNT_REG )

    #define bleUart_RXSTATUS_REG           (* (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart_RXSTATUS_PTR           (  (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart_RXSTATUS_MASK_REG      (* (reg8 *) bleUart_BUART_sRX_RxSts__MASK_REG )
    #define bleUart_RXSTATUS_MASK_PTR      (  (reg8 *) bleUart_BUART_sRX_RxSts__MASK_REG )
    #define bleUart_RXSTATUS_ACTL_REG      (* (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define bleUart_RXSTATUS_ACTL_PTR      (  (reg8 *) bleUart_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) */

#if(bleUart_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define bleUart_INTCLOCK_CLKEN_REG     (* (reg8 *) bleUart_IntClock__PM_ACT_CFG)
    #define bleUart_INTCLOCK_CLKEN_PTR     (  (reg8 *) bleUart_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define bleUart_INTCLOCK_CLKEN_MASK    bleUart_IntClock__PM_ACT_MSK
#endif /* End bleUart_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(bleUart_TX_ENABLED)
    #define bleUart_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End bleUart_TX_ENABLED */

#if(bleUart_HD_ENABLED)
    #define bleUart_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End bleUart_HD_ENABLED */

#if( (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) )
    #define bleUart_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define bleUart_WAIT_1_MS      bleUart_BL_CHK_DELAY_MS   

#define bleUart_TXBUFFERSIZE   bleUart_TX_BUFFER_SIZE
#define bleUart_RXBUFFERSIZE   bleUart_RX_BUFFER_SIZE

#if (bleUart_RXHW_ADDRESS_ENABLED)
    #define bleUart_RXADDRESSMODE  bleUart_RX_ADDRESS_MODE
    #define bleUart_RXHWADDRESS1   bleUart_RX_HW_ADDRESS1
    #define bleUart_RXHWADDRESS2   bleUart_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define bleUart_RXAddressMode  bleUart_RXADDRESSMODE
#endif /* (bleUart_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define bleUart_initvar                    bleUart_initVar

#define bleUart_RX_Enabled                 bleUart_RX_ENABLED
#define bleUart_TX_Enabled                 bleUart_TX_ENABLED
#define bleUart_HD_Enabled                 bleUart_HD_ENABLED
#define bleUart_RX_IntInterruptEnabled     bleUart_RX_INTERRUPT_ENABLED
#define bleUart_TX_IntInterruptEnabled     bleUart_TX_INTERRUPT_ENABLED
#define bleUart_InternalClockUsed          bleUart_INTERNAL_CLOCK_USED
#define bleUart_RXHW_Address_Enabled       bleUart_RXHW_ADDRESS_ENABLED
#define bleUart_OverSampleCount            bleUart_OVER_SAMPLE_COUNT
#define bleUart_ParityType                 bleUart_PARITY_TYPE

#if( bleUart_TX_ENABLED && (bleUart_TXBUFFERSIZE > bleUart_FIFO_LENGTH))
    #define bleUart_TXBUFFER               bleUart_txBuffer
    #define bleUart_TXBUFFERREAD           bleUart_txBufferRead
    #define bleUart_TXBUFFERWRITE          bleUart_txBufferWrite
#endif /* End bleUart_TX_ENABLED */
#if( ( bleUart_RX_ENABLED || bleUart_HD_ENABLED ) && \
     (bleUart_RXBUFFERSIZE > bleUart_FIFO_LENGTH) )
    #define bleUart_RXBUFFER               bleUart_rxBuffer
    #define bleUart_RXBUFFERREAD           bleUart_rxBufferRead
    #define bleUart_RXBUFFERWRITE          bleUart_rxBufferWrite
    #define bleUart_RXBUFFERLOOPDETECT     bleUart_rxBufferLoopDetect
    #define bleUart_RXBUFFER_OVERFLOW      bleUart_rxBufferOverflow
#endif /* End bleUart_RX_ENABLED */

#ifdef bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define bleUart_CONTROL                bleUart_CONTROL_REG
#endif /* End bleUart_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(bleUart_TX_ENABLED)
    #define bleUart_TXDATA                 bleUart_TXDATA_REG
    #define bleUart_TXSTATUS               bleUart_TXSTATUS_REG
    #define bleUart_TXSTATUS_MASK          bleUart_TXSTATUS_MASK_REG
    #define bleUart_TXSTATUS_ACTL          bleUart_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(bleUart_TXCLKGEN_DP)
        #define bleUart_TXBITCLKGEN_CTR        bleUart_TXBITCLKGEN_CTR_REG
        #define bleUart_TXBITCLKTX_COMPLETE    bleUart_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define bleUart_TXBITCTR_PERIOD        bleUart_TXBITCTR_PERIOD_REG
        #define bleUart_TXBITCTR_CONTROL       bleUart_TXBITCTR_CONTROL_REG
        #define bleUart_TXBITCTR_COUNTER       bleUart_TXBITCTR_COUNTER_REG
    #endif /* bleUart_TXCLKGEN_DP */
#endif /* End bleUart_TX_ENABLED */

#if(bleUart_HD_ENABLED)
    #define bleUart_TXDATA                 bleUart_TXDATA_REG
    #define bleUart_TXSTATUS               bleUart_TXSTATUS_REG
    #define bleUart_TXSTATUS_MASK          bleUart_TXSTATUS_MASK_REG
    #define bleUart_TXSTATUS_ACTL          bleUart_TXSTATUS_ACTL_REG
#endif /* End bleUart_HD_ENABLED */

#if( (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) )
    #define bleUart_RXDATA                 bleUart_RXDATA_REG
    #define bleUart_RXADDRESS1             bleUart_RXADDRESS1_REG
    #define bleUart_RXADDRESS2             bleUart_RXADDRESS2_REG
    #define bleUart_RXBITCTR_PERIOD        bleUart_RXBITCTR_PERIOD_REG
    #define bleUart_RXBITCTR_CONTROL       bleUart_RXBITCTR_CONTROL_REG
    #define bleUart_RXBITCTR_COUNTER       bleUart_RXBITCTR_COUNTER_REG
    #define bleUart_RXSTATUS               bleUart_RXSTATUS_REG
    #define bleUart_RXSTATUS_MASK          bleUart_RXSTATUS_MASK_REG
    #define bleUart_RXSTATUS_ACTL          bleUart_RXSTATUS_ACTL_REG
#endif /* End  (bleUart_RX_ENABLED) || (bleUart_HD_ENABLED) */

#if(bleUart_INTERNAL_CLOCK_USED)
    #define bleUart_INTCLOCK_CLKEN         bleUart_INTCLOCK_CLKEN_REG
#endif /* End bleUart_INTERNAL_CLOCK_USED */

#define bleUart_WAIT_FOR_COMLETE_REINIT    bleUart_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_bleUart_H */


/* [] END OF FILE */
