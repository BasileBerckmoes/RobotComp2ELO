/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  I2S Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2S_`$INSTANCE_NAME`_H)
#define CY_I2S_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_PVT.h"


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void  `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void  `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void  `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void  `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;

#if (`$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION)
    cystatus `$INSTANCE_NAME`_SetDataBits(uint8 dataBits) `=ReentrantKeil($INSTANCE_NAME . "_SetDataBits")`;
#endif /* `$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION */

#if (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
    void   `$INSTANCE_NAME`_EnableTx(void)          `=ReentrantKeil($INSTANCE_NAME . "_EnableTx")`;
    void   `$INSTANCE_NAME`_DisableTx(void)         `=ReentrantKeil($INSTANCE_NAME . "_DisableTx")`;
    void   `$INSTANCE_NAME`_ClearTxFIFO(void)       `=ReentrantKeil($INSTANCE_NAME . "_ClearTxFIFO")`;
#endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */

#if (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
    void   `$INSTANCE_NAME`_EnableRx(void)          `=ReentrantKeil($INSTANCE_NAME . "_EnableRx")`;
    void   `$INSTANCE_NAME`_DisableRx(void)         `=ReentrantKeil($INSTANCE_NAME . "_DisableRx")`;
    void   `$INSTANCE_NAME`_ClearRxFIFO(void)       `=ReentrantKeil($INSTANCE_NAME . "_ClearRxFIFO")`;
#endif /* `$INSTANCE_NAME`_RX_DIRECTION_ENABLE */


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*           API Constants
***************************************/

/* One stereo channel supports data channels (left and right) */
#define `$INSTANCE_NAME`_TX_LEFT_CHANNEL        (0x00u)
#define `$INSTANCE_NAME`_TX_RIGHT_CHANNEL       (0x01u)
#define `$INSTANCE_NAME`_RX_LEFT_CHANNEL        (0x00u)
#define `$INSTANCE_NAME`_RX_RIGHT_CHANNEL       (0x01u)

/* Interrupt masks and channel status */
#define `$INSTANCE_NAME`_TX_FIFO_UNDERFLOW      (0x01u)
#define `$INSTANCE_NAME`_TX_FIFO_0_NOT_FULL     (0x02u)
#define `$INSTANCE_NAME`_TX_FIFO_1_NOT_FULL     (0x04u)
#define `$INSTANCE_NAME`_RX_FIFO_OVERFLOW       (0x01u)
#define `$INSTANCE_NAME`_RX_FIFO_0_NOT_EMPTY    (0x02u)
#define `$INSTANCE_NAME`_RX_FIFO_1_NOT_EMPTY    (0x04u)

#define `$INSTANCE_NAME`_TX_CH0_UNDERFLOW       (0x01u)
#define `$INSTANCE_NAME`_TX_CH0_F0_NOT_FULL     (0x02u)
#define `$INSTANCE_NAME`_TX_CH0_F1_NOT_FULL     (0x04u)
#define `$INSTANCE_NAME`_RX_CH0_OVERFLOW        (0x01u)
#define `$INSTANCE_NAME`_RX_CH0_F0_NOT_EMPTY    (0x02u)
#define `$INSTANCE_NAME`_RX_CH0_F1_NOT_EMPTY    (0x04u)

#define `$INSTANCE_NAME`_TX_CH1_UNDERFLOW       (0x08u)
#define `$INSTANCE_NAME`_TX_CH1_F0_NOT_FULL     (0x10u)
#define `$INSTANCE_NAME`_TX_CH1_F1_NOT_FULL     (0x20u)
#define `$INSTANCE_NAME`_RX_CH1_OVERFLOW        (0x08u)
#define `$INSTANCE_NAME`_RX_CH1_F0_NOT_EMPTY    (0x10u)
#define `$INSTANCE_NAME`_RX_CH1_F1_NOT_EMPTY    (0x20u)

#define `$INSTANCE_NAME`_TX_CH2_UNDERFLOW       (0x01u)
#define `$INSTANCE_NAME`_TX_CH2_F0_NOT_FULL     (0x02u)
#define `$INSTANCE_NAME`_TX_CH2_F1_NOT_FULL     (0x04u)
#define `$INSTANCE_NAME`_RX_CH2_OVERFLOW        (0x01u)
#define `$INSTANCE_NAME`_RX_CH2_F0_NOT_EMPTY    (0x02u)
#define `$INSTANCE_NAME`_RX_CH2_F1_NOT_EMPTY    (0x04u)

#define `$INSTANCE_NAME`_TX_CH3_UNDERFLOW       (0x08u)
#define `$INSTANCE_NAME`_TX_CH3_F0_NOT_FULL     (0x10u)
#define `$INSTANCE_NAME`_TX_CH3_F1_NOT_FULL     (0x20u)
#define `$INSTANCE_NAME`_RX_CH3_OVERFLOW        (0x08u)
#define `$INSTANCE_NAME`_RX_CH3_F0_NOT_EMPTY    (0x10u)
#define `$INSTANCE_NAME`_RX_CH3_F1_NOT_EMPTY    (0x20u)

#define `$INSTANCE_NAME`_TX_CH4_UNDERFLOW       (0x01u)
#define `$INSTANCE_NAME`_TX_CH4_F0_NOT_FULL     (0x02u)
#define `$INSTANCE_NAME`_TX_CH4_F1_NOT_FULL     (0x04u)
#define `$INSTANCE_NAME`_RX_CH4_OVERFLOW        (0x01u)
#define `$INSTANCE_NAME`_RX_CH4_F0_NOT_EMPTY    (0x02u)
#define `$INSTANCE_NAME`_RX_CH4_F1_NOT_EMPTY    (0x04u)

/* Data bits values for dynamic bit resolution */
#define `$INSTANCE_NAME`_8BIT_DATA              (8u)
#define `$INSTANCE_NAME`_16BIT_DATA             (16u)
#define `$INSTANCE_NAME`_24BIT_DATA             (24u)
#define `$INSTANCE_NAME`_32BIT_DATA             (32u)

/* Stereo channels */
#define `$INSTANCE_NAME`_STEREO_0               (0u)
#define `$INSTANCE_NAME`_STEREO_1               (1u)
#define `$INSTANCE_NAME`_STEREO_2               (2u)
#define `$INSTANCE_NAME`_STEREO_3               (3u)
#define `$INSTANCE_NAME`_STEREO_4               (4u)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Default interrupt source */
#define `$INSTANCE_NAME`_INT_SOURCE             (`$InterruptSource`u)
#define `$INSTANCE_NAME`_RX_INT_SOURCE          (`$RxInterruptSource`u)
#define `$INSTANCE_NAME`_TX_INT_SOURCE          (`$TxInterruptSource`u)
#define `$INSTANCE_NAME`_DATA_BITS              (`$DataBits`u)


/***************************************
*             Registers
***************************************/

/* Global control register */
#define `$INSTANCE_NAME`_CONTROL_REG                (* (reg8 *) `$INSTANCE_NAME`_bI2S_CtlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_CONTROL_PTR                (  (reg8 *) `$INSTANCE_NAME`_bI2S_CtlReg__CONTROL_REG)

/* Transmit stereo channel 0 (channel 0 and channel 1) registers */
#if (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
    #define `$INSTANCE_NAME`_TX_CH0_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__F0_REG)
    #define `$INSTANCE_NAME`_TX_CH0_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__F1_REG)
    #define `$INSTANCE_NAME`_TX_CH0_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_CH0_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_REG)

/* Transmit stereo 1 (channel 2 and channel 3) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_1_PRESENT)
    #define `$INSTANCE_NAME`_TX_CH1_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_1__dpTx_u0__F0_REG)
    #define `$INSTANCE_NAME`_TX_CH1_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_1__dpTx_u0__F1_REG)
    #define `$INSTANCE_NAME`_TX_CH1_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_CH1_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_1_PRESENT */

/* Transmit stereo 2 (channel 4 and channel 5) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_2_PRESENT)
    #define `$INSTANCE_NAME`_TX_CH2_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_2__dpTx_u0__F0_REG)
    #define `$INSTANCE_NAME`_TX_CH2_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_2__dpTx_u0__F1_REG)
    #define `$INSTANCE_NAME`_TX_CH2_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_CH2_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_2_PRESENT */

/* Transmit stereo 3 (channel 6 and channel 7) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_3_PRESENT)
    #define `$INSTANCE_NAME`_TX_CH3_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_3__dpTx_u0__F0_REG)
    #define `$INSTANCE_NAME`_TX_CH3_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_3__dpTx_u0__F1_REG)
    #define `$INSTANCE_NAME`_TX_CH3_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_CH3_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_3_PRESENT */

/* Transmit stereo 4 (channel 8 and channel 9) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_4_PRESENT)   
    #define `$INSTANCE_NAME`_TX_CH4_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_4__dpTx_u0__F0_REG)
    #define `$INSTANCE_NAME`_TX_CH4_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_4__dpTx_u0__F1_REG)
    #define `$INSTANCE_NAME`_TX_CH4_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_4__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_CH4_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_4__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_4_PRESENT */
#endif /* `$INSTANCE_NAME`_TX_DIRECTION_ENABLE */

/* Receive stereo 0 (channel 0 and channel 1) registers */
#if (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)  
    #define `$INSTANCE_NAME`_RX_CH0_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__F0_REG)
    #define `$INSTANCE_NAME`_RX_CH0_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__F1_REG)
    #define `$INSTANCE_NAME`_RX_CH0_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_CH0_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_REG)

/* Receive stereo 1 (channel 2 and channel 3) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_1_PRESENT)
    #define `$INSTANCE_NAME`_RX_CH1_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_1__dpRx_u0__F0_REG)
    #define `$INSTANCE_NAME`_RX_CH1_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_1__dpRx_u0__F1_REG)
    #define `$INSTANCE_NAME`_RX_CH1_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_CH1_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_1_PRESENT */

/* Stereo 2 (channel 4 and channel 5) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_2_PRESENT)  
    #define `$INSTANCE_NAME`_RX_CH2_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_2__dpRx_u0__F0_REG)
    #define `$INSTANCE_NAME`_RX_CH2_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_2__dpRx_u0__F1_REG)
    #define `$INSTANCE_NAME`_RX_CH2_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_CH2_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_2_PRESENT */

/* Stereo 3 (channel 6 and channel 7) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_3_PRESENT)
    #define `$INSTANCE_NAME`_RX_CH3_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_3__dpRx_u0__F0_REG)
    #define `$INSTANCE_NAME`_RX_CH3_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_3__dpRx_u0__F1_REG)
    #define `$INSTANCE_NAME`_RX_CH3_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_CH3_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_3_PRESENT */

/* Stereo 4 (channel 8 and channel 9) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_4_PRESENT)
    #define `$INSTANCE_NAME`_RX_CH4_F0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_4__dpRx_u0__F0_REG)
    #define `$INSTANCE_NAME`_RX_CH4_F1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_4__dpRx_u0__F1_REG)
    #define `$INSTANCE_NAME`_RX_CH4_STS_REG         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_4__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_CH4_STS_PTR         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_4__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_4_PRESENT */
#endif /* `$INSTANCE_NAME`_RX_DIRECTION_ENABLE */


/***************************************
*       Register Constants
***************************************/

/* Control register bits */
#define `$INSTANCE_NAME`_TX_EN              (0x01u)
#define `$INSTANCE_NAME`_RX_EN              (0x02u)
#define `$INSTANCE_NAME`_EN                 (0x04u)
#define `$INSTANCE_NAME`_8BIT_MODE          (0x00u)
#define `$INSTANCE_NAME`_16BIT_MODE         (0x08u)
#define `$INSTANCE_NAME`_24BIT_MODE         (0x10u)
#define `$INSTANCE_NAME`_32BIT_MODE         (0x18u)

/* FIFO control bits */
#define `$INSTANCE_NAME`_FIFO0_CLR          (0x01u)
#define `$INSTANCE_NAME`_FIFO1_CLR          (0x02u)
#define `$INSTANCE_NAME`_FIFO0_LVL          (0x04u) 
#define `$INSTANCE_NAME`_FIFO1_LVL          (0x08u)

/* Interrupt mask and enable bits */ 
#define `$INSTANCE_NAME`_STS_MASK           (0x3Fu)      
#define `$INSTANCE_NAME`_INT_EN             (0x10u)

/* Bit counter control bits */
#define `$INSTANCE_NAME`_CNT_START          (0x20u)


#if (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteByte
    ********************************************************************************
    *
    * Summary:
    *  This macro writes a single byte into the Tx FIFO for the specified stereo
    *  channel. You have to check the Tx status before this call to confirm that
    *  the Tx FIFO is not full.
    *
    * Parameters:
    *  channel (for Tx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for the Tx direction.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  wrData: Byte containing the data to transmit.
    *  wordSelect: Indicates to write to the Left (0) or Right (1) channel. In the
    *    interleaved mode this parameter is ignored.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_TX_STEREO_0_ONLY)
        #define `$INSTANCE_NAME`_WriteByte(wrData, wordSelect) `$INSTANCE_NAME`_WRITE_BYTE(CH0, wrData, wordSelect)
    #else
        #define `$INSTANCE_NAME`_WriteByte(channel, wrData, wordSelect) `$INSTANCE_NAME`_WRITE_BYTE(channel, wrData, wordSelect)
    #endif /* `$INSTANCE_NAME`_TX_STEREO_0_ONLY */


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadTxStatus
    ****************************************************************************
    *
    * Summary:
    *  Returns the status of the specified stereo channel(s).
    *  In multi-channel configuration, the status bits of stereo channel 0 are
    *  combined with stereo channel 1, and the bits of channel 2 are combined
    *  with channel 3. Therefore the API will return the combined status of
    *  stereo channel 0 and stereo channel 1 if the status for channel 0 or
    *  channel 1 is requested.
    *
    * Parameters:
    *  channel (for Tx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for Tx direction.
    *    CH0  - Stereo channel 0
    *    CH1  - Stereo channel 1
    *    CH2  - Stereo channel 2
    *    CH3  - Stereo channel 3
    *    CH4  - Stereo channel 4
    *
    * Return:
    *  Status bits associated with the specified stereo channel.
    *    Bits 
    *    0   CH0/CH2/CH4 underflow status (Clear on Read)
    *    1   CH0/CH2/CH4 FIFO 0 not full status
    *    2   CH0/CH2/CH4 FIFO 1 not full status
    *    3   CH1/CH3 underflow status (Clear on Read)
    *    4   CH1/CH3 FIFO 0 not full status
    *    5   CH1/CH3 FIFO 1 not full status
    *
    * Side Effects:
    *  Clears the status register bits that are Clear on Read.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_ReadTxStatus(channel) (`$INSTANCE_NAME`_TX_##channel##_STS_REG & `$INSTANCE_NAME`_STS_MASK)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt source for the specified Tx stereo channel. Multiple
    *  sources may be ORed.
    *
    * Parameters:
    *  channel (for Tx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for Tx direction.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  interruptSource: Specifies the constant for the selected interrupt sources.
    *    `$INSTANCE_NAME`_TX_FIFO_UNDERFLOW
    *    `$INSTANCE_NAME`_TX_FIFO_0_NOT_FULL
    *    `$INSTANCE_NAME`_TX_FIFO_1_NOT_FULL
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_TX_STEREO_0_ONLY)
        #define `$INSTANCE_NAME`_SetTxInterruptMode(interruptSource) (`$INSTANCE_NAME`_TX_CH0_STS_MASK_REG = (uint8)(interruptSource))
    #else
        #define `$INSTANCE_NAME`_SetTxInterruptMode(channel, interruptSource) `$INSTANCE_NAME`_SET_TX_INT_MASK(channel, interruptSource)
    #endif /* `$INSTANCE_NAME`_TX_STEREO_0_ONLY */

#endif /* `$INSTANCE_NAME`_TX_DIRECTION_ENABLE */

#if (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadByte
    ********************************************************************************
    *
    * Summary:
    *  Returns a single byte from the Rx FIFO of the specified channel.
    *
    * Parameters:
    *  channel (for Rx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for Rx direction.
    *    CH0  - Stereo channel 0
    *    CH1  - Stereo channel 1
    *    CH2  - Stereo channel 2
    *    CH3  - Stereo channel 3
    *    CH4  - Stereo channel 4
    *  wordSelect: Indicates to read from the Left (0) or Right (1) channel. In the
    *    interleaved mode this parameter is ignored.
    *
    * Return:
    *  Byte containing the data received.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_RX_STEREO_0_ONLY)
        #define `$INSTANCE_NAME`_ReadByte(wordSelect) `$INSTANCE_NAME`_READ_BYTE(CH0, wordSelect)
    #else
        #define `$INSTANCE_NAME`_ReadByte(channel, wordSelect) `$INSTANCE_NAME`_READ_BYTE(channel, wordSelect)
    #endif /* `$INSTANCE_NAME`_RX_STEREO_0_ONLY */


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadRxStatus
    ****************************************************************************
    *
    * Summary:
    *  Returns the status of the specified stereo channel(s).
    *  In multi-channel configuration, the status bits of stereo channel 0 are
    *  combined with stereo channel 1, and the bits of channel 2 are combined
    *  with channel 3. Therefore the API will return the combined status of
    *  stereo channel 0 and stereo channel 1 if the status for channel 0 or
    *  channel 1 is requested.
    *
    * Parameters:
    *  channel (for Rx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for Rx direction. 
    *    CH0  - Stereo channel 0
    *    CH1  - Stereo channel 1
    *    CH2  - Stereo channel 2
    *    CH3  - Stereo channel 3
    *    CH4  - Stereo channel 4
    *
    * Return:
    *  Status bits associated with the specified stereo channel.
    *    Bits 
    *    0   CH0/CH2/CH4 overflow status (Clear on Read)
    *    1   CH0/CH2/CH4 FIFO 0 not empty status
    *    2   CH0/CH2/CH4 FIFO 1 not empty status
    *    3   CH1/CH3 overflow status (Clear on Read)
    *    4   CH1/CH3 FIFO 0 not empty status
    *    5   CH1/CH3 FIFO 1 not empty status
    *
    * Side Effects:
    *  Clears the status register bits that are Clear on Read.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_ReadRxStatus(channel) (`$INSTANCE_NAME`_RX_##channel##_STS_REG & `$INSTANCE_NAME`_STS_MASK)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt source for the specified Rx stereo channel. Multiple
    *  sources may be ORed.
    *
    * Parameters:
    *  channel (for Rx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for Rx direction.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  interruptSource: Specifies the constant for the selected interrupt sources.
    *    `$INSTANCE_NAME`_RX_FIFO_OVERFLOW
    *    `$INSTANCE_NAME`_RX_FIFO_0_NOT_EMPTY
    *    `$INSTANCE_NAME`_RX_FIFO_1_NOT_EMPTY
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_RX_STEREO_0_ONLY)
        #define `$INSTANCE_NAME`_SetRxInterruptMode(interruptSource) (`$INSTANCE_NAME`_RX_CH0_STS_MASK_REG = (uint8)(interruptSource))
    #else
        #define `$INSTANCE_NAME`_SetRxInterruptMode(channel, interruptSource) `$INSTANCE_NAME`_SET_RX_INT_MASK(channel, interruptSource)
    #endif /* `$INSTANCE_NAME`_RX_STEREO_0_ONLY */


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetPositiveClipThreshold
    ********************************************************************************
    *
    * Summary:
    *  Sets the 8-bit positive clip detection threshold for the specified channel.
    *  This API is available if the Enable rx clip detection parameter is selected
    *  in the Configure dialog.
    *
    * Parameters:
    *  channel (for Rx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for the Rx direction.  
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  uint8 threshold: Specifies the positive clip detection threshold.
    *    Valid range: 0..127.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_RX_STEREO_0_ONLY)
        #define `$INSTANCE_NAME`_SetPositiveClipThreshold(threshold) `$INSTANCE_NAME`_SET_POS_THRESHOLD(CH0, threshold)
    #else
        #define `$INSTANCE_NAME`_SetPositiveClipThreshold(channel, threshold) `$INSTANCE_NAME`_SET_POS_THRESHOLD(channel, threshold)
    #endif /* `$INSTANCE_NAME`_RX_STEREO_0_ONLY */

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetNegativeClipThreshold
    ********************************************************************************
    *
    * Summary:
    *  Sets the 8-bit negative clip detection threshold for the specified channel.
    *  This API is available if the Enable rx clip detection parameter is selected
    *  in the Configure dialog.
    *
    * Parameters:
    *  channel (for Rx multi-channel only): Specifies the stereo channel number.
    *   Note The macro expects channel parameter only when more than one stereo
    *   channel is selected for Rx direction.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  int8 threshold: Specifies the negative clip detection threshold.
    *    Valid range: -1..-128.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_RX_STEREO_0_ONLY)
        #define `$INSTANCE_NAME`_SetNegativeClipThreshold(threshold) `$INSTANCE_NAME`_SET_NEG_THRESHOLD(CH0, threshold)
    #else
        #define `$INSTANCE_NAME`_SetNegativeClipThreshold(channel, threshold) `$INSTANCE_NAME`_SET_NEG_THRESHOLD(channel, threshold)
    #endif /* `$INSTANCE_NAME`_RX_STEREO_0_ONLY */

#endif /* `$INSTANCE_NAME`_RX_DIRECTION_ENABLE */


#endif /* CY_I2S_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
