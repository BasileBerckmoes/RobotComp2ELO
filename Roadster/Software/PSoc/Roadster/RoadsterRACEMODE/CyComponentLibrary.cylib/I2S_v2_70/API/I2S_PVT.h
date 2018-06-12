/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PVT.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the I2S
*  component. This code must not be used in user main code context.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2S_PVT_`$INSTANCE_NAME`_H)
#define CY_I2S_PVT_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_DIRECTION              (`$Direction`u)
#define `$INSTANCE_NAME`_WORD_SELECT            (`$WordSelect`u)
#define `$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION (0u == `$StaticBitResolution`u)
#define `$INSTANCE_NAME`_RX_DATA_INTERLEAVING   (`$RxDataInterleaving`u)
#define `$INSTANCE_NAME`_TX_DATA_INTERLEAVING   (`$TxDataInterleaving`u)

#define `$INSTANCE_NAME`_DIR_RX                 (0x01u)
#define `$INSTANCE_NAME`_DIR_TX                 (0x02u)
#define `$INSTANCE_NAME`_DIR_RX_AND_TX          (0x03u)

#define `$INSTANCE_NAME`_RX_DIRECTION_ENABLE    (0u != (`$INSTANCE_NAME`_DIR_RX & `$INSTANCE_NAME`_DIRECTION))
#define `$INSTANCE_NAME`_TX_DIRECTION_ENABLE    (0u != (`$INSTANCE_NAME`_DIR_TX & `$INSTANCE_NAME`_DIRECTION))

#define `$INSTANCE_NAME`_NUMBER_RX_CHANNELS     (`$NumRxChannels`u)
#define `$INSTANCE_NAME`_NUMBER_TX_CHANNELS     (`$NumTxChannels`u)

#define `$INSTANCE_NAME`_RX_DATA_SEPARATE       (0u == `$INSTANCE_NAME`_RX_DATA_INTERLEAVING)
#define `$INSTANCE_NAME`_RX_DATA_INTERLEAVED    (0u != `$INSTANCE_NAME`_RX_DATA_INTERLEAVING)

#define `$INSTANCE_NAME`_TX_DATA_SEPARATE       (0u == `$INSTANCE_NAME`_TX_DATA_INTERLEAVING)
#define `$INSTANCE_NAME`_TX_DATA_INTERLEAVED    (0u != `$INSTANCE_NAME`_TX_DATA_INTERLEAVING)

#define `$INSTANCE_NAME`_RX_BYTE_SWAP_ENABLE    (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE && (0u != `$EnableRxByteSwap`u))
#define `$INSTANCE_NAME`_TX_BYTE_SWAP_ENABLE    (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE && (0u != `$EnableTxByteSwap`u))

#define `$INSTANCE_NAME`_RX_STEREO_0_ONLY       (`$INSTANCE_NAME`_NUMBER_RX_CHANNELS <= 2u)
#define `$INSTANCE_NAME`_RX_STEREO_1_PRESENT    (`$INSTANCE_NAME`_NUMBER_RX_CHANNELS >= 4u)
#define `$INSTANCE_NAME`_RX_STEREO_2_PRESENT    (`$INSTANCE_NAME`_NUMBER_RX_CHANNELS >= 6u)
#define `$INSTANCE_NAME`_RX_STEREO_3_PRESENT    (`$INSTANCE_NAME`_NUMBER_RX_CHANNELS >= 8u)
#define `$INSTANCE_NAME`_RX_STEREO_4_PRESENT    (`$INSTANCE_NAME`_NUMBER_RX_CHANNELS == 10u)

#define `$INSTANCE_NAME`_TX_STEREO_0_ONLY       (`$INSTANCE_NAME`_NUMBER_TX_CHANNELS <= 2u)
#define `$INSTANCE_NAME`_TX_STEREO_1_PRESENT    (`$INSTANCE_NAME`_NUMBER_TX_CHANNELS >= 4u)
#define `$INSTANCE_NAME`_TX_STEREO_2_PRESENT    (`$INSTANCE_NAME`_NUMBER_TX_CHANNELS >= 6u)
#define `$INSTANCE_NAME`_TX_STEREO_3_PRESENT    (`$INSTANCE_NAME`_NUMBER_TX_CHANNELS >= 8u)
#define `$INSTANCE_NAME`_TX_STEREO_4_PRESENT    (`$INSTANCE_NAME`_NUMBER_TX_CHANNELS == 10u)

#define `$INSTANCE_NAME`_CLIP_DETECT_ENABLE     (0u != `$EnableClipDetect`u)


/***************************************
*      Internal API Constants
***************************************/

#if (`$INSTANCE_NAME`_TX_BYTE_SWAP_ENABLE || `$INSTANCE_NAME`_RX_BYTE_SWAP_ENABLE)
    #define `$INSTANCE_NAME`_MIN_DATA_BITS             (16u)
    #define `$INSTANCE_NAME`_MAX_DATA_BITS             (24u)
#else
    #define `$INSTANCE_NAME`_MIN_DATA_BITS             (8u)
    #define `$INSTANCE_NAME`_MAX_DATA_BITS             (`$INSTANCE_NAME`_WORD_SELECT >> 1u)
#endif /* `$INSTANCE_NAME`_TX_BYTE_SWAP_ENABLE || `$INSTANCE_NAME`_RX_BYTE_SWAP_ENABLE */

#define `$INSTANCE_NAME`_CH0_STS_MASK                  (0x07u)
#define `$INSTANCE_NAME`_CH1_STS_MASK                  (0x38u)
#define `$INSTANCE_NAME`_CH2_STS_MASK                  (0x07u)
#define `$INSTANCE_NAME`_CH3_STS_MASK                  (0x38u)
#define `$INSTANCE_NAME`_CH4_STS_MASK                  (0x07u)
#define `$INSTANCE_NAME`_CH0_STS_SHIFT                 (0u)
#define `$INSTANCE_NAME`_CH1_STS_SHIFT                 (3u)
#define `$INSTANCE_NAME`_CH2_STS_SHIFT                 (0u)
#define `$INSTANCE_NAME`_CH3_STS_SHIFT                 (3u)
#define `$INSTANCE_NAME`_CH4_STS_SHIFT                 (0u)

#define `$INSTANCE_NAME`_BIT_RESOLUTION_MODE_MASK      (0x18u)


/***************************************
*             Registers
***************************************/

/* Bit counter registers */
#define `$INSTANCE_NAME`_AUX_CONTROL_REG            (* (reg8 *) `$INSTANCE_NAME`_bI2S_BitCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_AUX_CONTROL_PTR            (  (reg8 *) `$INSTANCE_NAME`_bI2S_BitCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_CNT_PERIOD_REG             (* (reg8 *) `$INSTANCE_NAME`_bI2S_BitCounter__PERIOD_REG)
#define `$INSTANCE_NAME`_CNT_PERIOD_PTR             (  (reg8 *) `$INSTANCE_NAME`_bI2S_BitCounter__PERIOD_REG)
#define `$INSTANCE_NAME`_CNT_COUNT_REG              (* (reg8 *) `$INSTANCE_NAME`_bI2S_BitCounter__COUNT_REG)
#define `$INSTANCE_NAME`_CNT_COUNT_PTR              (  (reg8 *) `$INSTANCE_NAME`_bI2S_BitCounter__COUNT_REG)

/* Transmit stereo channel 0 (channel 0 and channel 1) registers */
#if (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
    #define `$INSTANCE_NAME`_TX_CH0_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH0_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX__STS_REG            (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_CH0_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_CH0_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_STS0_1_ACTL_REG     (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_STS0_1_ACTL_PTR     (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_AUX_CTL_REG)

/* Transmit stereo 1 (channel 2 and channel 3) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_1_PRESENT)
    #define `$INSTANCE_NAME`_TX_CH1_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_1__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH1_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_1__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH1_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_CH1_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__MASK_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_1_PRESENT */

/* Transmit stereo 2 (channel 4 and channel 5) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_2_PRESENT)
    #define `$INSTANCE_NAME`_TX_CH2_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_2__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH2_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_2__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH2_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_CH2_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_STS2_3_ACTL_REG     (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_STS2_3_ACTL_PTR     (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_2_PRESENT */

/* Transmit stereo 3 (channel 6 and channel 7) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_3_PRESENT)
    #define `$INSTANCE_NAME`_TX_CH3_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_3__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH3_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_3__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH3_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_CH3_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_2__Sts__MASK_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_3_PRESENT */

/* Transmit stereo 4 (channel 8 and channel 9) registers */
#if (`$INSTANCE_NAME`_TX_STEREO_4_PRESENT)   
    #define `$INSTANCE_NAME`_TX_CH4_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_4__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH4_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_4__dpTx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_CH4_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_4__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_CH4_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_4__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_TX_STS4_ACTL_REG       (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_4__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TX_STS4_ACTL_PTR       (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_4__Sts__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_TX_STEREO_4_PRESENT */
#endif /* `$INSTANCE_NAME`_TX_DIRECTION_ENABLE */

/* Receive stereo 0 (channel 0 and channel 1) registers */
#if (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)  
    #define `$INSTANCE_NAME`_RX_CH0_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH0_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX__STS_REG            (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_CH0_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_CH0_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_STS0_1_ACTL_REG     (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_STS0_1_ACTL_PTR     (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH0_D0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__D0_REG)
    #define `$INSTANCE_NAME`_RX_CH0_D1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__D1_REG)

/* Receive stereo 1 (channel 2 and channel 3) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_1_PRESENT)
    #define `$INSTANCE_NAME`_RX_CH1_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_1__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH1_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_1__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH1_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_CH1_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_CH1_D0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_1__dpRx_u0__D0_REG)
    #define `$INSTANCE_NAME`_RX_CH1_D1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_1__dpRx_u0__D1_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_1_PRESENT */

/* Stereo 2 (channel 4 and channel 5) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_2_PRESENT)  
    #define `$INSTANCE_NAME`_RX_CH2_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_2__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH2_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_2__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH2_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_CH2_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_STS2_3_ACTL_REG     (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_STS2_3_ACTL_PTR     (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH2_D0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_2__dpRx_u0__D0_REG)
    #define `$INSTANCE_NAME`_RX_CH2_D1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_2__dpRx_u0__D1_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_2_PRESENT */

/* Stereo 3 (channel 6 and channel 7) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_3_PRESENT)
    #define `$INSTANCE_NAME`_RX_CH3_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_3__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH3_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_3__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH3_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_CH3_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_2__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_CH3_D0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_3__dpRx_u0__D0_REG)
    #define `$INSTANCE_NAME`_RX_CH3_D1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_3__dpRx_u0__D1_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_3_PRESENT */

/* Stereo 4 (channel 8 and channel 9) registers */
#if (`$INSTANCE_NAME`_RX_STEREO_4_PRESENT)
    #define `$INSTANCE_NAME`_RX_CH4_ACTL_REG        (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_4__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH4_ACTL_PTR        (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_4__dpRx_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH4_STS_MASK_REG    (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_4__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_CH4_STS_MASK_PTR    (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_4__Sts__MASK_REG)
    #define `$INSTANCE_NAME`_RX_STS4_ACTL_REG       (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_4__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_STS4_ACTL_PTR       (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_4__Sts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_RX_CH4_D0_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_4__dpRx_u0__D0_REG)
    #define `$INSTANCE_NAME`_RX_CH4_D1_PTR          (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_4__dpRx_u0__D1_REG)
#endif /* `$INSTANCE_NAME`_RX_STEREO_4_PRESENT */
#endif /* `$INSTANCE_NAME`_RX_DIRECTION_ENABLE */


/***************************************
*               Macros
***************************************/
            
#if (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WRITE_BYTE
    ********************************************************************************
    *
    * Summary:
    *  Writes a single byte into the Tx FIFO for the specified channel.
    *
    * Parameters:
    *  channel:  Specifies the stereo channel number.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  wrData:  Byte containing the data to transmit.
    *  wordSelect:  Indicates to write to the Left (0) or Right (1) channel. In the
    *               interleaved mode this parameter is ignored.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_TX_DATA_INTERLEAVED)            
        #define `$INSTANCE_NAME`_WRITE_BYTE(channel, wrData, wordSelect) \
            (* `$INSTANCE_NAME`_TX_##channel##_F0_PTR = (wrData))
    #else
        #define `$INSTANCE_NAME`_WRITE_BYTE(channel, wrData, wordSelect) \
            do { \
                if(0u == (wordSelect)) \
                {* `$INSTANCE_NAME`_TX_##channel##_F0_PTR = (wrData);} \
                else \
                {* `$INSTANCE_NAME`_TX_##channel##_F1_PTR = (wrData);} \
            } while(0)
    #endif /* `$INSTANCE_NAME`_TX_DATA_INTERLEAVED */

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SET_TX_INT_MASK
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt source for the specified Tx stereo channel. Multiple
    *  sources may be ORed.
    *
    * Parameters:
    *  channel:  Specifies the stereo channel number.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  interruptSource:  Specifies the constant for the selected interrupt sources.
    *    `$INSTANCE_NAME`_TX_FIFO_UNDERFLOW
    *    `$INSTANCE_NAME`_TX_FIFO_0_NOT_FULL
    *    `$INSTANCE_NAME`_TX_FIFO_1_NOT_FULL
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_SET_TX_INT_MASK(channel, interruptSource) \
        do { \
            `$INSTANCE_NAME`_TX_##channel##_STS_MASK_REG &= (uint8) ~`$INSTANCE_NAME`_##channel##_STS_MASK; \
            `$INSTANCE_NAME`_TX_##channel##_STS_MASK_REG |= (uint8)((interruptSource) << `$INSTANCE_NAME`_##channel##_STS_SHIFT); \
        } while(0)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CLEAR_TX_FIFO
    ********************************************************************************
    *
    * Summary:
    *  Clears out the Tx FIFO for the specified stereo channel.
    *  NOTE The macro modifies a shared device register (ACTL) that must not be
    *  concurrently accessed. Therefore its execution must be protected by a critical
    *  section to ensure the operation is atomic.
    *
    * Parameters:
    *  channel: Specifies the stereo channel number
    *   CH0 - Stereo channel 0
    *   CH1 - Stereo channel 1
    *   CH2 - Stereo channel 2
    *   CH3 - Stereo channel 3
    *   CH4 - Stereo channel 4
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_CLEAR_TX_FIFO(channel) \
        do { \
            `$INSTANCE_NAME`_TX_##channel##_ACTL_REG |= (uint8) (`$INSTANCE_NAME`_FIFO0_CLR | `$INSTANCE_NAME`_FIFO1_CLR); \
            `$INSTANCE_NAME`_TX_##channel##_ACTL_REG &= (uint8)~(`$INSTANCE_NAME`_FIFO0_CLR | `$INSTANCE_NAME`_FIFO1_CLR); \
        } while (0)

#endif /* `$INSTANCE_NAME`_TX_DIRECTION_ENABLE */

#if (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_READ_BYTE
    ********************************************************************************
    *
    * Summary:
    *  Returns a single byte from the Rx FIFO of the specified channel.
    *
    * Parameters:
    *  channel: Specifies the stereo channel number.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  wordSelect: Indicates to read from the Left (0) or Right (1) channel. In the
    *              interleaved mode this parameter is ignored.
    *
    * Return:
    *  Byte containing the data received.
    *
    *******************************************************************************/
    #if (`$INSTANCE_NAME`_RX_DATA_INTERLEAVED)
        #define `$INSTANCE_NAME`_READ_BYTE(channel, wordSelect) (* `$INSTANCE_NAME`_RX_##channel##_F0_PTR)
    #else
        #define `$INSTANCE_NAME`_READ_BYTE(channel, wordSelect) \
            ((0u == (wordSelect)) ? (* `$INSTANCE_NAME`_RX_##channel##_F0_PTR) : (* `$INSTANCE_NAME`_RX_##channel##_F1_PTR))

    #endif /* `$INSTANCE_NAME`_RX_DATA_INTERLEAVED */


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SET_RX_INT_MASK
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt source for the specified Rx stereo channel. Multiple
    *  sources may be ORed.
    *
    * Parameters:
    *  channel:  Specifies the stereo channel number.
    *    CH0 - Stereo channel 0
    *    CH1 - Stereo channel 1
    *    CH2 - Stereo channel 2
    *    CH3 - Stereo channel 3
    *    CH4 - Stereo channel 4
    *  interruptSource:  Specifies the constant for the selected interrupt sources.
    *    `$INSTANCE_NAME`_RX_FIFO_OVERFLOW
    *    `$INSTANCE_NAME`_RX_FIFO_0_NOT_EMPTY
    *    `$INSTANCE_NAME`_RX_FIFO_1_NOT_EMPTY
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_SET_RX_INT_MASK(channel, interruptSource) \
        do { \
            `$INSTANCE_NAME`_RX_##channel##_STS_MASK_REG &= (uint8) ~`$INSTANCE_NAME`_##channel##_STS_MASK; \
            `$INSTANCE_NAME`_RX_##channel##_STS_MASK_REG |= (uint8)((interruptSource) << `$INSTANCE_NAME`_##channel##_STS_SHIFT); \
        } while(0)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CLEAR_RX_FIFO
    ********************************************************************************
    *
    * Summary:
    *  Clears out the Rx FIFO for the specified stereo channel.
    *  NOTE The macro modifies a shared device register (ACTL) that must not be
    *  concurrently accessed. Therefore its execution must be protected by a critical
    *  section to ensure the operation is atomic.
    *
    * Parameters:
    *  channel: Specifies the stereo channel number
    *   CH0 - Stereo channel 0
    *   CH1 - Stereo channel 1
    *   CH2 - Stereo channel 2
    *   CH3 - Stereo channel 3
    *   CH4 - Stereo channel 4
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_CLEAR_RX_FIFO(channel) \
        do { \
            `$INSTANCE_NAME`_RX_##channel##_ACTL_REG |= (uint8) (`$INSTANCE_NAME`_FIFO0_CLR | `$INSTANCE_NAME`_FIFO1_CLR); \
            `$INSTANCE_NAME`_RX_##channel##_ACTL_REG &= (uint8)~(`$INSTANCE_NAME`_FIFO0_CLR | `$INSTANCE_NAME`_FIFO1_CLR); \
        } while (0)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SET_POS_THRESHOLD
    ********************************************************************************
    *
    * Summary:
    *  Sets the 8-bit positive clip detection threshold for the specified channel.
    *
    * Parameters:
    *  channel: Specifies the stereo channel number.
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
    #define `$INSTANCE_NAME`_SET_POS_THRESHOLD(channel, threshold) (* `$INSTANCE_NAME`_RX_##channel##_D0_PTR = (uint8)(threshold))


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SET_NEG_THRESHOLD
    ********************************************************************************
    *
    * Summary:
    *  Sets the 8-bit negative clip detection threshold for the specified channel.
    *
    * Parameters:
    *  channel: Specifies the stereo channel number.
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
    #define `$INSTANCE_NAME`_SET_NEG_THRESHOLD(channel, threshold) (* `$INSTANCE_NAME`_RX_##channel##_D1_PTR = (uint8)(threshold))

#endif /* `$INSTANCE_NAME`_RX_DIRECTION_ENABLE */


/***************************************
*       Obsolete
***************************************/

/* Following code is OBSOLETE and must not be used for new designs */

void  `$INSTANCE_NAME`_SaveConfig(void)             `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void  `$INSTANCE_NAME`_RestoreConfig(void)          `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;

#if(`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
    #define `$INSTANCE_NAME`_TX_REG                         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__A0_REG)
    #define `$INSTANCE_NAME`_TX_PTR                         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__A0_REG)
    #define `$INSTANCE_NAME`_TX_FIFO_0_REG                  (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__F0_REG)
    #define `$INSTANCE_NAME`_TX_FIFO_1_REG                  (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__F1_REG)
    #define `$INSTANCE_NAME`_TX_FIFO_0_PTR                  (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__F0_REG)
    #define `$INSTANCE_NAME`_TX_FIFO_1_PTR                  (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_CH_0__dpTx_u0__F1_REG)
    #define `$INSTANCE_NAME`_TX_STATUS_REG                  (* (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_STATUS_PTR                  (  (reg8 *) `$INSTANCE_NAME`_bI2S_Tx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_TX_AUX_CONTROL_REG             `$INSTANCE_NAME`_TX_CH0_ACTL_REG
    #define `$INSTANCE_NAME`_TX_AUX_CONTROL_PTR             `$INSTANCE_NAME`_TX_CH0_ACTL_PTR
    #define `$INSTANCE_NAME`_TX_STATUS_MASK_REG             `$INSTANCE_NAME`_TX_CH0_MASK_REG
    #define `$INSTANCE_NAME`_TX_STATUS_MASK_PTR             `$INSTANCE_NAME`_TX_CH0_MASK_PTR
    #define `$INSTANCE_NAME`_TX_STATUS_AUX_CONTROL_REG      `$INSTANCE_NAME`_TX_STS0_1_ACTL_REG
    #define `$INSTANCE_NAME`_TX_STATUS_AUX_CONTROL_PTR      `$INSTANCE_NAME`_TX_STS0_1_ACTL_PTR
#endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */

#if(`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
    #define `$INSTANCE_NAME`_RX_REG                         (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__A0_REG)
    #define `$INSTANCE_NAME`_RX_PTR                         (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__A0_REG)
    #define `$INSTANCE_NAME`_RX_FIFO_0_REG                  (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__F0_REG)
    #define `$INSTANCE_NAME`_RX_FIFO_1_REG                  (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__F1_REG)
    #define `$INSTANCE_NAME`_RX_FIFO_0_PTR                  (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__F0_REG)
    #define `$INSTANCE_NAME`_RX_FIFO_1_PTR                  (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_CH_0__dpRx_u0__F1_REG)
    #define `$INSTANCE_NAME`_RX_STATUS_REG                  (* (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_STATUS_PTR                  (  (reg8 *) `$INSTANCE_NAME`_bI2S_Rx_STS_0__Sts__STATUS_REG)
    #define `$INSTANCE_NAME`_RX_AUX_CONTROL_REG             `$INSTANCE_NAME`_RX_CH0_ACTL_REG
    #define `$INSTANCE_NAME`_RX_AUX_CONTROL_PTR             `$INSTANCE_NAME`_RX_CH0_ACTL_PTR
    #define `$INSTANCE_NAME`_RX_STATUS_MASK_REG             `$INSTANCE_NAME`_RX_CH0_STS_MASK_REG
    #define `$INSTANCE_NAME`_RX_STATUS_MASK_PTR             `$INSTANCE_NAME`_RX_CH0_STS_MASK_PTR
    #define `$INSTANCE_NAME`_RX_STATUS_AUX_CONTROL_REG      `$INSTANCE_NAME`_RX_STS0_1_ACTL_REG
    #define `$INSTANCE_NAME`_RX_STATUS_AUX_CONTROL_PTR      `$INSTANCE_NAME`_RX_STS0_1_ACTL_PTR
#endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */

/* Direction enum. */
#define `$INSTANCE_NAME`__TX        (`$INSTANCE_NAME`_DIR_TX)
#define `$INSTANCE_NAME`__RX        (`$INSTANCE_NAME`_DIR_RX)
#define `$INSTANCE_NAME`__RX_AND_TX (`$INSTANCE_NAME`_DIR_RX_AND_TX)

/* Data interleaving enum. */
#define `$INSTANCE_NAME`__SEPARATE      (`$INSTANCE_NAME`_DATA_SEPARATE)
#define `$INSTANCE_NAME`__INTERLEAVED   (`$INSTANCE_NAME`_DATA_INTERLEAVED)

#endif /* (CY_I2S_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
