/*******************************************************************************
* File Name: bleUart1.h
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


#if !defined(CY_UART_bleUart1_H)
#define CY_UART_bleUart1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define bleUart1_RX_ENABLED                     (1u)
#define bleUart1_TX_ENABLED                     (1u)
#define bleUart1_HD_ENABLED                     (0u)
#define bleUart1_RX_INTERRUPT_ENABLED           (0u)
#define bleUart1_TX_INTERRUPT_ENABLED           (0u)
#define bleUart1_INTERNAL_CLOCK_USED            (1u)
#define bleUart1_RXHW_ADDRESS_ENABLED           (0u)
#define bleUart1_OVER_SAMPLE_COUNT              (8u)
#define bleUart1_PARITY_TYPE                    (0u)
#define bleUart1_PARITY_TYPE_SW                 (0u)
#define bleUart1_BREAK_DETECT                   (0u)
#define bleUart1_BREAK_BITS_TX                  (13u)
#define bleUart1_BREAK_BITS_RX                  (13u)
#define bleUart1_TXCLKGEN_DP                    (1u)
#define bleUart1_USE23POLLING                   (1u)
#define bleUart1_FLOW_CONTROL                   (0u)
#define bleUart1_CLK_FREQ                       (0u)
#define bleUart1_TX_BUFFER_SIZE                 (4u)
#define bleUart1_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define bleUart1_CONTROL_REG_REMOVED            (0u)
#else
    #define bleUart1_CONTROL_REG_REMOVED            (1u)
#endif /* End bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct bleUart1_backupStruct_
{
    uint8 enableState;

    #if(bleUart1_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End bleUart1_CONTROL_REG_REMOVED */

} bleUart1_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void bleUart1_Start(void) ;
void bleUart1_Stop(void) ;
uint8 bleUart1_ReadControlRegister(void) ;
void bleUart1_WriteControlRegister(uint8 control) ;

void bleUart1_Init(void) ;
void bleUart1_Enable(void) ;
void bleUart1_SaveConfig(void) ;
void bleUart1_RestoreConfig(void) ;
void bleUart1_Sleep(void) ;
void bleUart1_Wakeup(void) ;

/* Only if RX is enabled */
#if( (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) )

    #if (bleUart1_RX_INTERRUPT_ENABLED)
        #define bleUart1_EnableRxInt()  CyIntEnable (bleUart1_RX_VECT_NUM)
        #define bleUart1_DisableRxInt() CyIntDisable(bleUart1_RX_VECT_NUM)
        CY_ISR_PROTO(bleUart1_RXISR);
    #endif /* bleUart1_RX_INTERRUPT_ENABLED */

    void bleUart1_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void bleUart1_SetRxAddress1(uint8 address) ;
    void bleUart1_SetRxAddress2(uint8 address) ;

    void  bleUart1_SetRxInterruptMode(uint8 intSrc) ;
    uint8 bleUart1_ReadRxData(void) ;
    uint8 bleUart1_ReadRxStatus(void) ;
    uint8 bleUart1_GetChar(void) ;
    uint16 bleUart1_GetByte(void) ;
    uint8 bleUart1_GetRxBufferSize(void)
                                                            ;
    void bleUart1_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define bleUart1_GetRxInterruptSource   bleUart1_ReadRxStatus

#endif /* End (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) */

/* Only if TX is enabled */
#if(bleUart1_TX_ENABLED || bleUart1_HD_ENABLED)

    #if(bleUart1_TX_INTERRUPT_ENABLED)
        #define bleUart1_EnableTxInt()  CyIntEnable (bleUart1_TX_VECT_NUM)
        #define bleUart1_DisableTxInt() CyIntDisable(bleUart1_TX_VECT_NUM)
        #define bleUart1_SetPendingTxInt() CyIntSetPending(bleUart1_TX_VECT_NUM)
        #define bleUart1_ClearPendingTxInt() CyIntClearPending(bleUart1_TX_VECT_NUM)
        CY_ISR_PROTO(bleUart1_TXISR);
    #endif /* bleUart1_TX_INTERRUPT_ENABLED */

    void bleUart1_SetTxInterruptMode(uint8 intSrc) ;
    void bleUart1_WriteTxData(uint8 txDataByte) ;
    uint8 bleUart1_ReadTxStatus(void) ;
    void bleUart1_PutChar(uint8 txDataByte) ;
    void bleUart1_PutString(const char8 string[]) ;
    void bleUart1_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void bleUart1_PutCRLF(uint8 txDataByte) ;
    void bleUart1_ClearTxBuffer(void) ;
    void bleUart1_SetTxAddressMode(uint8 addressMode) ;
    void bleUart1_SendBreak(uint8 retMode) ;
    uint8 bleUart1_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define bleUart1_PutStringConst         bleUart1_PutString
    #define bleUart1_PutArrayConst          bleUart1_PutArray
    #define bleUart1_GetTxInterruptSource   bleUart1_ReadTxStatus

#endif /* End bleUart1_TX_ENABLED || bleUart1_HD_ENABLED */

#if(bleUart1_HD_ENABLED)
    void bleUart1_LoadRxConfig(void) ;
    void bleUart1_LoadTxConfig(void) ;
#endif /* End bleUart1_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bleUart1) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    bleUart1_CyBtldrCommStart(void) CYSMALL ;
    void    bleUart1_CyBtldrCommStop(void) CYSMALL ;
    void    bleUart1_CyBtldrCommReset(void) CYSMALL ;
    cystatus bleUart1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus bleUart1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bleUart1)
        #define CyBtldrCommStart    bleUart1_CyBtldrCommStart
        #define CyBtldrCommStop     bleUart1_CyBtldrCommStop
        #define CyBtldrCommReset    bleUart1_CyBtldrCommReset
        #define CyBtldrCommWrite    bleUart1_CyBtldrCommWrite
        #define CyBtldrCommRead     bleUart1_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_bleUart1) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define bleUart1_BYTE2BYTE_TIME_OUT (25u)
    #define bleUart1_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define bleUart1_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define bleUart1_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define bleUart1_SET_SPACE      (0x00u)
#define bleUart1_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (bleUart1_TX_ENABLED) || (bleUart1_HD_ENABLED) )
    #if(bleUart1_TX_INTERRUPT_ENABLED)
        #define bleUart1_TX_VECT_NUM            (uint8)bleUart1_TXInternalInterrupt__INTC_NUMBER
        #define bleUart1_TX_PRIOR_NUM           (uint8)bleUart1_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* bleUart1_TX_INTERRUPT_ENABLED */

    #define bleUart1_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define bleUart1_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define bleUart1_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(bleUart1_TX_ENABLED)
        #define bleUart1_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (bleUart1_HD_ENABLED) */
        #define bleUart1_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (bleUart1_TX_ENABLED) */

    #define bleUart1_TX_STS_COMPLETE            (uint8)(0x01u << bleUart1_TX_STS_COMPLETE_SHIFT)
    #define bleUart1_TX_STS_FIFO_EMPTY          (uint8)(0x01u << bleUart1_TX_STS_FIFO_EMPTY_SHIFT)
    #define bleUart1_TX_STS_FIFO_FULL           (uint8)(0x01u << bleUart1_TX_STS_FIFO_FULL_SHIFT)
    #define bleUart1_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << bleUart1_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (bleUart1_TX_ENABLED) || (bleUart1_HD_ENABLED)*/

#if( (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) )
    #if(bleUart1_RX_INTERRUPT_ENABLED)
        #define bleUart1_RX_VECT_NUM            (uint8)bleUart1_RXInternalInterrupt__INTC_NUMBER
        #define bleUart1_RX_PRIOR_NUM           (uint8)bleUart1_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* bleUart1_RX_INTERRUPT_ENABLED */
    #define bleUart1_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define bleUart1_RX_STS_BREAK_SHIFT             (0x01u)
    #define bleUart1_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define bleUart1_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define bleUart1_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define bleUart1_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define bleUart1_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define bleUart1_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define bleUart1_RX_STS_MRKSPC           (uint8)(0x01u << bleUart1_RX_STS_MRKSPC_SHIFT)
    #define bleUart1_RX_STS_BREAK            (uint8)(0x01u << bleUart1_RX_STS_BREAK_SHIFT)
    #define bleUart1_RX_STS_PAR_ERROR        (uint8)(0x01u << bleUart1_RX_STS_PAR_ERROR_SHIFT)
    #define bleUart1_RX_STS_STOP_ERROR       (uint8)(0x01u << bleUart1_RX_STS_STOP_ERROR_SHIFT)
    #define bleUart1_RX_STS_OVERRUN          (uint8)(0x01u << bleUart1_RX_STS_OVERRUN_SHIFT)
    #define bleUart1_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << bleUart1_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define bleUart1_RX_STS_ADDR_MATCH       (uint8)(0x01u << bleUart1_RX_STS_ADDR_MATCH_SHIFT)
    #define bleUart1_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << bleUart1_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define bleUart1_RX_HW_MASK                     (0x7Fu)
#endif /* End (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) */

/* Control Register definitions */
#define bleUart1_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define bleUart1_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define bleUart1_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define bleUart1_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define bleUart1_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define bleUart1_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define bleUart1_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define bleUart1_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define bleUart1_CTRL_HD_SEND               (uint8)(0x01u << bleUart1_CTRL_HD_SEND_SHIFT)
#define bleUart1_CTRL_HD_SEND_BREAK         (uint8)(0x01u << bleUart1_CTRL_HD_SEND_BREAK_SHIFT)
#define bleUart1_CTRL_MARK                  (uint8)(0x01u << bleUart1_CTRL_MARK_SHIFT)
#define bleUart1_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << bleUart1_CTRL_PARITY_TYPE0_SHIFT)
#define bleUart1_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << bleUart1_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define bleUart1_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define bleUart1_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define bleUart1_SEND_BREAK                         (0x00u)
#define bleUart1_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define bleUart1_REINIT                             (0x02u)
#define bleUart1_SEND_WAIT_REINIT                   (0x03u)

#define bleUart1_OVER_SAMPLE_8                      (8u)
#define bleUart1_OVER_SAMPLE_16                     (16u)

#define bleUart1_BIT_CENTER                         (bleUart1_OVER_SAMPLE_COUNT - 2u)

#define bleUart1_FIFO_LENGTH                        (4u)
#define bleUart1_NUMBER_OF_START_BIT                (1u)
#define bleUart1_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define bleUart1_TXBITCTR_BREAKBITS8X   ((bleUart1_BREAK_BITS_TX * bleUart1_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define bleUart1_TXBITCTR_BREAKBITS ((bleUart1_BREAK_BITS_TX * bleUart1_OVER_SAMPLE_COUNT) - 1u)

#define bleUart1_HALF_BIT_COUNT   \
                            (((bleUart1_OVER_SAMPLE_COUNT / 2u) + (bleUart1_USE23POLLING * 1u)) - 2u)
#if (bleUart1_OVER_SAMPLE_COUNT == bleUart1_OVER_SAMPLE_8)
    #define bleUart1_HD_TXBITCTR_INIT   (((bleUart1_BREAK_BITS_TX + \
                            bleUart1_NUMBER_OF_START_BIT) * bleUart1_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define bleUart1_RXBITCTR_INIT  ((((bleUart1_BREAK_BITS_RX + bleUart1_NUMBER_OF_START_BIT) \
                            * bleUart1_OVER_SAMPLE_COUNT) + bleUart1_HALF_BIT_COUNT) - 1u)

#else /* bleUart1_OVER_SAMPLE_COUNT == bleUart1_OVER_SAMPLE_16 */
    #define bleUart1_HD_TXBITCTR_INIT   ((8u * bleUart1_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define bleUart1_RXBITCTR_INIT      (((7u * bleUart1_OVER_SAMPLE_COUNT) - 1u) + \
                                                      bleUart1_HALF_BIT_COUNT)
#endif /* End bleUart1_OVER_SAMPLE_COUNT */

#define bleUart1_HD_RXBITCTR_INIT                   bleUart1_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 bleUart1_initVar;
#if (bleUart1_TX_INTERRUPT_ENABLED && bleUart1_TX_ENABLED)
    extern volatile uint8 bleUart1_txBuffer[bleUart1_TX_BUFFER_SIZE];
    extern volatile uint8 bleUart1_txBufferRead;
    extern uint8 bleUart1_txBufferWrite;
#endif /* (bleUart1_TX_INTERRUPT_ENABLED && bleUart1_TX_ENABLED) */
#if (bleUart1_RX_INTERRUPT_ENABLED && (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED))
    extern uint8 bleUart1_errorStatus;
    extern volatile uint8 bleUart1_rxBuffer[bleUart1_RX_BUFFER_SIZE];
    extern volatile uint8 bleUart1_rxBufferRead;
    extern volatile uint8 bleUart1_rxBufferWrite;
    extern volatile uint8 bleUart1_rxBufferLoopDetect;
    extern volatile uint8 bleUart1_rxBufferOverflow;
    #if (bleUart1_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 bleUart1_rxAddressMode;
        extern volatile uint8 bleUart1_rxAddressDetected;
    #endif /* (bleUart1_RXHW_ADDRESS_ENABLED) */
#endif /* (bleUart1_RX_INTERRUPT_ENABLED && (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define bleUart1__B_UART__AM_SW_BYTE_BYTE 1
#define bleUart1__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define bleUart1__B_UART__AM_HW_BYTE_BY_BYTE 3
#define bleUart1__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define bleUart1__B_UART__AM_NONE 0

#define bleUart1__B_UART__NONE_REVB 0
#define bleUart1__B_UART__EVEN_REVB 1
#define bleUart1__B_UART__ODD_REVB 2
#define bleUart1__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define bleUart1_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define bleUart1_NUMBER_OF_STOP_BITS    (1u)

#if (bleUart1_RXHW_ADDRESS_ENABLED)
    #define bleUart1_RX_ADDRESS_MODE    (0u)
    #define bleUart1_RX_HW_ADDRESS1     (0u)
    #define bleUart1_RX_HW_ADDRESS2     (0u)
#endif /* (bleUart1_RXHW_ADDRESS_ENABLED) */

#define bleUart1_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << bleUart1_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << bleUart1_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << bleUart1_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << bleUart1_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << bleUart1_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << bleUart1_RX_STS_BREAK_SHIFT) \
                                        | (0 << bleUart1_RX_STS_OVERRUN_SHIFT))

#define bleUart1_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << bleUart1_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << bleUart1_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << bleUart1_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << bleUart1_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define bleUart1_CONTROL_REG \
                            (* (reg8 *) bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define bleUart1_CONTROL_PTR \
                            (  (reg8 *) bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(bleUart1_TX_ENABLED)
    #define bleUart1_TXDATA_REG          (* (reg8 *) bleUart1_BUART_sTX_TxShifter_u0__F0_REG)
    #define bleUart1_TXDATA_PTR          (  (reg8 *) bleUart1_BUART_sTX_TxShifter_u0__F0_REG)
    #define bleUart1_TXDATA_AUX_CTL_REG  (* (reg8 *) bleUart1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define bleUart1_TXDATA_AUX_CTL_PTR  (  (reg8 *) bleUart1_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define bleUart1_TXSTATUS_REG        (* (reg8 *) bleUart1_BUART_sTX_TxSts__STATUS_REG)
    #define bleUart1_TXSTATUS_PTR        (  (reg8 *) bleUart1_BUART_sTX_TxSts__STATUS_REG)
    #define bleUart1_TXSTATUS_MASK_REG   (* (reg8 *) bleUart1_BUART_sTX_TxSts__MASK_REG)
    #define bleUart1_TXSTATUS_MASK_PTR   (  (reg8 *) bleUart1_BUART_sTX_TxSts__MASK_REG)
    #define bleUart1_TXSTATUS_ACTL_REG   (* (reg8 *) bleUart1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define bleUart1_TXSTATUS_ACTL_PTR   (  (reg8 *) bleUart1_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(bleUart1_TXCLKGEN_DP)
        #define bleUart1_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define bleUart1_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define bleUart1_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define bleUart1_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define bleUart1_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define bleUart1_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define bleUart1_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define bleUart1_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define bleUart1_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define bleUart1_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) bleUart1_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* bleUart1_TXCLKGEN_DP */

#endif /* End bleUart1_TX_ENABLED */

#if(bleUart1_HD_ENABLED)

    #define bleUart1_TXDATA_REG             (* (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__F1_REG )
    #define bleUart1_TXDATA_PTR             (  (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__F1_REG )
    #define bleUart1_TXDATA_AUX_CTL_REG     (* (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define bleUart1_TXDATA_AUX_CTL_PTR     (  (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define bleUart1_TXSTATUS_REG           (* (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart1_TXSTATUS_PTR           (  (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart1_TXSTATUS_MASK_REG      (* (reg8 *) bleUart1_BUART_sRX_RxSts__MASK_REG )
    #define bleUart1_TXSTATUS_MASK_PTR      (  (reg8 *) bleUart1_BUART_sRX_RxSts__MASK_REG )
    #define bleUart1_TXSTATUS_ACTL_REG      (* (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define bleUart1_TXSTATUS_ACTL_PTR      (  (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End bleUart1_HD_ENABLED */

#if( (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) )
    #define bleUart1_RXDATA_REG             (* (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__F0_REG )
    #define bleUart1_RXDATA_PTR             (  (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__F0_REG )
    #define bleUart1_RXADDRESS1_REG         (* (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__D0_REG )
    #define bleUart1_RXADDRESS1_PTR         (  (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__D0_REG )
    #define bleUart1_RXADDRESS2_REG         (* (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__D1_REG )
    #define bleUart1_RXADDRESS2_PTR         (  (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__D1_REG )
    #define bleUart1_RXDATA_AUX_CTL_REG     (* (reg8 *) bleUart1_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define bleUart1_RXBITCTR_PERIOD_REG    (* (reg8 *) bleUart1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define bleUart1_RXBITCTR_PERIOD_PTR    (  (reg8 *) bleUart1_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define bleUart1_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) bleUart1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define bleUart1_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) bleUart1_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define bleUart1_RXBITCTR_COUNTER_REG   (* (reg8 *) bleUart1_BUART_sRX_RxBitCounter__COUNT_REG )
    #define bleUart1_RXBITCTR_COUNTER_PTR   (  (reg8 *) bleUart1_BUART_sRX_RxBitCounter__COUNT_REG )

    #define bleUart1_RXSTATUS_REG           (* (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart1_RXSTATUS_PTR           (  (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_REG )
    #define bleUart1_RXSTATUS_MASK_REG      (* (reg8 *) bleUart1_BUART_sRX_RxSts__MASK_REG )
    #define bleUart1_RXSTATUS_MASK_PTR      (  (reg8 *) bleUart1_BUART_sRX_RxSts__MASK_REG )
    #define bleUart1_RXSTATUS_ACTL_REG      (* (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define bleUart1_RXSTATUS_ACTL_PTR      (  (reg8 *) bleUart1_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) */

#if(bleUart1_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define bleUart1_INTCLOCK_CLKEN_REG     (* (reg8 *) bleUart1_IntClock__PM_ACT_CFG)
    #define bleUart1_INTCLOCK_CLKEN_PTR     (  (reg8 *) bleUart1_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define bleUart1_INTCLOCK_CLKEN_MASK    bleUart1_IntClock__PM_ACT_MSK
#endif /* End bleUart1_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(bleUart1_TX_ENABLED)
    #define bleUart1_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End bleUart1_TX_ENABLED */

#if(bleUart1_HD_ENABLED)
    #define bleUart1_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End bleUart1_HD_ENABLED */

#if( (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) )
    #define bleUart1_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define bleUart1_WAIT_1_MS      bleUart1_BL_CHK_DELAY_MS   

#define bleUart1_TXBUFFERSIZE   bleUart1_TX_BUFFER_SIZE
#define bleUart1_RXBUFFERSIZE   bleUart1_RX_BUFFER_SIZE

#if (bleUart1_RXHW_ADDRESS_ENABLED)
    #define bleUart1_RXADDRESSMODE  bleUart1_RX_ADDRESS_MODE
    #define bleUart1_RXHWADDRESS1   bleUart1_RX_HW_ADDRESS1
    #define bleUart1_RXHWADDRESS2   bleUart1_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define bleUart1_RXAddressMode  bleUart1_RXADDRESSMODE
#endif /* (bleUart1_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define bleUart1_initvar                    bleUart1_initVar

#define bleUart1_RX_Enabled                 bleUart1_RX_ENABLED
#define bleUart1_TX_Enabled                 bleUart1_TX_ENABLED
#define bleUart1_HD_Enabled                 bleUart1_HD_ENABLED
#define bleUart1_RX_IntInterruptEnabled     bleUart1_RX_INTERRUPT_ENABLED
#define bleUart1_TX_IntInterruptEnabled     bleUart1_TX_INTERRUPT_ENABLED
#define bleUart1_InternalClockUsed          bleUart1_INTERNAL_CLOCK_USED
#define bleUart1_RXHW_Address_Enabled       bleUart1_RXHW_ADDRESS_ENABLED
#define bleUart1_OverSampleCount            bleUart1_OVER_SAMPLE_COUNT
#define bleUart1_ParityType                 bleUart1_PARITY_TYPE

#if( bleUart1_TX_ENABLED && (bleUart1_TXBUFFERSIZE > bleUart1_FIFO_LENGTH))
    #define bleUart1_TXBUFFER               bleUart1_txBuffer
    #define bleUart1_TXBUFFERREAD           bleUart1_txBufferRead
    #define bleUart1_TXBUFFERWRITE          bleUart1_txBufferWrite
#endif /* End bleUart1_TX_ENABLED */
#if( ( bleUart1_RX_ENABLED || bleUart1_HD_ENABLED ) && \
     (bleUart1_RXBUFFERSIZE > bleUart1_FIFO_LENGTH) )
    #define bleUart1_RXBUFFER               bleUart1_rxBuffer
    #define bleUart1_RXBUFFERREAD           bleUart1_rxBufferRead
    #define bleUart1_RXBUFFERWRITE          bleUart1_rxBufferWrite
    #define bleUart1_RXBUFFERLOOPDETECT     bleUart1_rxBufferLoopDetect
    #define bleUart1_RXBUFFER_OVERFLOW      bleUart1_rxBufferOverflow
#endif /* End bleUart1_RX_ENABLED */

#ifdef bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define bleUart1_CONTROL                bleUart1_CONTROL_REG
#endif /* End bleUart1_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(bleUart1_TX_ENABLED)
    #define bleUart1_TXDATA                 bleUart1_TXDATA_REG
    #define bleUart1_TXSTATUS               bleUart1_TXSTATUS_REG
    #define bleUart1_TXSTATUS_MASK          bleUart1_TXSTATUS_MASK_REG
    #define bleUart1_TXSTATUS_ACTL          bleUart1_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(bleUart1_TXCLKGEN_DP)
        #define bleUart1_TXBITCLKGEN_CTR        bleUart1_TXBITCLKGEN_CTR_REG
        #define bleUart1_TXBITCLKTX_COMPLETE    bleUart1_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define bleUart1_TXBITCTR_PERIOD        bleUart1_TXBITCTR_PERIOD_REG
        #define bleUart1_TXBITCTR_CONTROL       bleUart1_TXBITCTR_CONTROL_REG
        #define bleUart1_TXBITCTR_COUNTER       bleUart1_TXBITCTR_COUNTER_REG
    #endif /* bleUart1_TXCLKGEN_DP */
#endif /* End bleUart1_TX_ENABLED */

#if(bleUart1_HD_ENABLED)
    #define bleUart1_TXDATA                 bleUart1_TXDATA_REG
    #define bleUart1_TXSTATUS               bleUart1_TXSTATUS_REG
    #define bleUart1_TXSTATUS_MASK          bleUart1_TXSTATUS_MASK_REG
    #define bleUart1_TXSTATUS_ACTL          bleUart1_TXSTATUS_ACTL_REG
#endif /* End bleUart1_HD_ENABLED */

#if( (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) )
    #define bleUart1_RXDATA                 bleUart1_RXDATA_REG
    #define bleUart1_RXADDRESS1             bleUart1_RXADDRESS1_REG
    #define bleUart1_RXADDRESS2             bleUart1_RXADDRESS2_REG
    #define bleUart1_RXBITCTR_PERIOD        bleUart1_RXBITCTR_PERIOD_REG
    #define bleUart1_RXBITCTR_CONTROL       bleUart1_RXBITCTR_CONTROL_REG
    #define bleUart1_RXBITCTR_COUNTER       bleUart1_RXBITCTR_COUNTER_REG
    #define bleUart1_RXSTATUS               bleUart1_RXSTATUS_REG
    #define bleUart1_RXSTATUS_MASK          bleUart1_RXSTATUS_MASK_REG
    #define bleUart1_RXSTATUS_ACTL          bleUart1_RXSTATUS_ACTL_REG
#endif /* End  (bleUart1_RX_ENABLED) || (bleUart1_HD_ENABLED) */

#if(bleUart1_INTERNAL_CLOCK_USED)
    #define bleUart1_INTCLOCK_CLKEN         bleUart1_INTCLOCK_CLKEN_REG
#endif /* End bleUart1_INTERNAL_CLOCK_USED */

#define bleUart1_WAIT_FOR_COMLETE_REINIT    bleUart1_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_bleUart1_H */


/* [] END OF FILE */
