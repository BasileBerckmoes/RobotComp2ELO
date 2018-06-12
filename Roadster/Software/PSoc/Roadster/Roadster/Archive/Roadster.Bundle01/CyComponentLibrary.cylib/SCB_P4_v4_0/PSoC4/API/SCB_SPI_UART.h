/***************************************************************************//**
* \file `$INSTANCE_NAME`_SPI_UART.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_`$INSTANCE_NAME`_H)
#define CY_SCB_SPI_UART_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_SPI_MODE                   (`$SpiMode`u)
#define `$INSTANCE_NAME`_SPI_SUB_MODE               (`$SpiSubMode`u)
#define `$INSTANCE_NAME`_SPI_CLOCK_MODE             (`$SpiSclkMode`u)
#define `$INSTANCE_NAME`_SPI_OVS_FACTOR             (`$SpiOvsFactor`u)
#define `$INSTANCE_NAME`_SPI_MEDIAN_FILTER_ENABLE   (`$SpiMedianFilterEnable`u)
#define `$INSTANCE_NAME`_SPI_LATE_MISO_SAMPLE_ENABLE (`$SpiLateMisoSampleEnable`u)
#define `$INSTANCE_NAME`_SPI_RX_DATA_BITS_NUM       (`$SpiNumberOfRxDataBits`u)
#define `$INSTANCE_NAME`_SPI_TX_DATA_BITS_NUM       (`$SpiNumberOfTxDataBits`u)
#define `$INSTANCE_NAME`_SPI_WAKE_ENABLE            (`$SpiWakeEnable`u)
#define `$INSTANCE_NAME`_SPI_BITS_ORDER             (`$SpiBitsOrder`u)
#define `$INSTANCE_NAME`_SPI_TRANSFER_SEPARATION    (`$SpiTransferSeparation`u)
#define `$INSTANCE_NAME`_SPI_NUMBER_OF_SS_LINES     (`$SpiNumberOfSelectLines`u)
#define `$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE         (`$SpiRxBufferSize`u)
#define `$INSTANCE_NAME`_SPI_TX_BUFFER_SIZE         (`$SpiTxBufferSize`u)

#define `$INSTANCE_NAME`_SPI_INTERRUPT_MODE         (`$SpiInterruptMode`u)

#define `$INSTANCE_NAME`_SPI_INTR_RX_MASK           (`= IntToHexString(`$SpiRxIntrMask`)`u)
#define `$INSTANCE_NAME`_SPI_INTR_TX_MASK           (`= IntToHexString(`$SpiTxIntrMask`)`u)

#define `$INSTANCE_NAME`_SPI_RX_TRIGGER_LEVEL       (`$SpiRxTriggerLevel`u)
#define `$INSTANCE_NAME`_SPI_TX_TRIGGER_LEVEL       (`$SpiTxTriggerLevel`u)

#define `$INSTANCE_NAME`_SPI_BYTE_MODE_ENABLE       (`$SpiByteModeEnable`u)
#define `$INSTANCE_NAME`_SPI_FREE_RUN_SCLK_ENABLE   (`$SpiFreeRunningSclk`u)
#define `$INSTANCE_NAME`_SPI_SS0_POLARITY           (`$SpiSs0Polarity`u)
#define `$INSTANCE_NAME`_SPI_SS1_POLARITY           (`$SpiSs1Polarity`u)
#define `$INSTANCE_NAME`_SPI_SS2_POLARITY           (`$SpiSs2Polarity`u)
#define `$INSTANCE_NAME`_SPI_SS3_POLARITY           (`$SpiSs3Polarity`u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_UART_SUB_MODE              (`$UartSubMode`u)
#define `$INSTANCE_NAME`_UART_DIRECTION             (`$UartDirection`u)
#define `$INSTANCE_NAME`_UART_DATA_BITS_NUM         (`$UartNumberOfDataBits`u)
#define `$INSTANCE_NAME`_UART_PARITY_TYPE           (`$UartParityType`u)
#define `$INSTANCE_NAME`_UART_STOP_BITS_NUM         (`$UartNumberOfStopBits`u)
#define `$INSTANCE_NAME`_UART_OVS_FACTOR            (`$UartOvsFactor`u)
#define `$INSTANCE_NAME`_UART_IRDA_LOW_POWER        (`$UartIrdaLowPower`u)
#define `$INSTANCE_NAME`_UART_MEDIAN_FILTER_ENABLE  (`$UartMedianFilterEnable`u)
#define `$INSTANCE_NAME`_UART_RETRY_ON_NACK         (`$UartSmCardRetryOnNack`u)
#define `$INSTANCE_NAME`_UART_IRDA_POLARITY         (`$UartIrdaPolarity`u)
#define `$INSTANCE_NAME`_UART_DROP_ON_FRAME_ERR     (`$UartDropOnFrameErr`u)
#define `$INSTANCE_NAME`_UART_DROP_ON_PARITY_ERR    (`$UartDropOnParityErr`u)
#define `$INSTANCE_NAME`_UART_WAKE_ENABLE           (`$UartWakeEnable`u)
#define `$INSTANCE_NAME`_UART_RX_BUFFER_SIZE        (`$UartRxBufferSize`u)
#define `$INSTANCE_NAME`_UART_TX_BUFFER_SIZE        (`$UartTxBufferSize`u)
#define `$INSTANCE_NAME`_UART_MP_MODE_ENABLE        (`$UartMpEnable`u)
#define `$INSTANCE_NAME`_UART_MP_ACCEPT_ADDRESS     (`$UartMpRxAcceptAddress`u)
#define `$INSTANCE_NAME`_UART_MP_RX_ADDRESS         (`= IntToHexString(`$UartMpRxAddress`)`u)
#define `$INSTANCE_NAME`_UART_MP_RX_ADDRESS_MASK    (`= IntToHexString(`$UartMpRxAddressMask`)`u)

#define `$INSTANCE_NAME`_UART_INTERRUPT_MODE        (`$UartInterruptMode`u)

#define `$INSTANCE_NAME`_UART_INTR_RX_MASK          (`= IntToHexString(`$UartRxIntrMask`)`u)
#define `$INSTANCE_NAME`_UART_INTR_TX_MASK          (`= IntToHexString(`$UartTxIntrMask`)`u)

#define `$INSTANCE_NAME`_UART_RX_TRIGGER_LEVEL      (`$UartRxTriggerLevel`u)
#define `$INSTANCE_NAME`_UART_TX_TRIGGER_LEVEL      (`$UartTxTriggerLevel`u)

#define `$INSTANCE_NAME`_UART_BYTE_MODE_ENABLE      (`$UartByteModeEnable`u)
#define `$INSTANCE_NAME`_UART_CTS_ENABLE            (`$UartCtsEnable`u)
#define `$INSTANCE_NAME`_UART_CTS_POLARITY          (`$UartCtsPolarity`u)
#define `$INSTANCE_NAME`_UART_RTS_ENABLE            (`$UartRtsEnable`u)
#define `$INSTANCE_NAME`_UART_RTS_POLARITY          (`$UartRtsPolarity`u)
#define `$INSTANCE_NAME`_UART_RTS_FIFO_LEVEL        (`$UartRtsTriggerLevel`u)

#define `$INSTANCE_NAME`_UART_RX_BREAK_WIDTH        (`$UartRxBreakWidth`u)

/* SPI mode enum */
#define `$INSTANCE_NAME`_SPI_SLAVE  (0u)
#define `$INSTANCE_NAME`_SPI_MASTER (1u)

/* UART direction enum */
#define `$INSTANCE_NAME`_UART_RX    (1u)
#define `$INSTANCE_NAME`_UART_TX    (2u)
#define `$INSTANCE_NAME`_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define `$INSTANCE_NAME`_SPI_SLAVE_CONST        (1u)
    #define `$INSTANCE_NAME`_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define `$INSTANCE_NAME`_RX_DIRECTION           (1u)
    #define `$INSTANCE_NAME`_TX_DIRECTION           (1u)
    #define `$INSTANCE_NAME`_UART_RX_DIRECTION      (1u)
    #define `$INSTANCE_NAME`_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER   (0u)
    #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define `$INSTANCE_NAME`_INTERNAL_RX_BUFFER_SIZE    (`$INSTANCE_NAME`_rxBufferSize + 1u)
    #define `$INSTANCE_NAME`_RX_BUFFER_SIZE             (`$INSTANCE_NAME`_rxBufferSize)
    #define `$INSTANCE_NAME`_TX_BUFFER_SIZE             (`$INSTANCE_NAME`_txBufferSize)

    /* Return true if buffer is provided */
    #define `$INSTANCE_NAME`_CHECK_RX_SW_BUFFER (NULL != `$INSTANCE_NAME`_rxBuffer)
    #define `$INSTANCE_NAME`_CHECK_TX_SW_BUFFER (NULL != `$INSTANCE_NAME`_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define `$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST  (1u)
    #define `$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST (1u)
    #define `$INSTANCE_NAME`_CHECK_SPI_WAKE_ENABLE  ((0u != `$INSTANCE_NAME`_scbEnableWake) && `$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    #define `$INSTANCE_NAME`_CHECK_UART_WAKE_ENABLE ((0u != `$INSTANCE_NAME`_scbEnableWake) && `$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)

    /* SPI/UART: TX or RX FIFO size */
    #if (`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        #define `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE             (`$INSTANCE_NAME`_FIFO_SIZE)
        #define `$INSTANCE_NAME`_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE (`$INSTANCE_NAME`_GET_FIFO_SIZE(`$INSTANCE_NAME`_CTRL_REG & \
                                                                                    `$INSTANCE_NAME`_CTRL_BYTE_MODE))

        #define `$INSTANCE_NAME`_CHECK_UART_RTS_CONTROL_FLOW \
                    ((`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(`$INSTANCE_NAME`_UART_FLOW_CTRL_REG)))
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define `$INSTANCE_NAME`_SPI_RX_DIRECTION (1u)
        #define `$INSTANCE_NAME`_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #define `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE `$INSTANCE_NAME`_GET_FIFO_SIZE(`$INSTANCE_NAME`_SPI_BYTE_MODE_ENABLE)

        /* SPI internal RX and TX buffers */
        #define `$INSTANCE_NAME`_INTERNAL_SPI_RX_SW_BUFFER  (`$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE > \
                                                                `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE)
        #define `$INSTANCE_NAME`_INTERNAL_SPI_TX_SW_BUFFER  (`$INSTANCE_NAME`_SPI_TX_BUFFER_SIZE > \
                                                                `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER  (`$INSTANCE_NAME`_INTERNAL_SPI_RX_SW_BUFFER)
        #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER  (`$INSTANCE_NAME`_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define `$INSTANCE_NAME`_INTERNAL_RX_BUFFER_SIZE    (`$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE + 1u)
        #define `$INSTANCE_NAME`_RX_BUFFER_SIZE             (`$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE)
        #define `$INSTANCE_NAME`_TX_BUFFER_SIZE             (`$INSTANCE_NAME`_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define `$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST  (0u != `$INSTANCE_NAME`_SPI_WAKE_ENABLE)
        #define `$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define `$INSTANCE_NAME`_UART_RX_DIRECTION (0u != (`$INSTANCE_NAME`_UART_DIRECTION & `$INSTANCE_NAME`_UART_RX))
        #define `$INSTANCE_NAME`_UART_TX_DIRECTION (0u != (`$INSTANCE_NAME`_UART_DIRECTION & `$INSTANCE_NAME`_UART_TX))

        /* Get FIFO size */
        #define `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE `$INSTANCE_NAME`_GET_FIFO_SIZE(`$INSTANCE_NAME`_UART_BYTE_MODE_ENABLE)

        /* UART internal RX and TX buffers */
        #define `$INSTANCE_NAME`_INTERNAL_UART_RX_SW_BUFFER  (`$INSTANCE_NAME`_UART_RX_BUFFER_SIZE > \
                                                                `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE)
        #define `$INSTANCE_NAME`_INTERNAL_UART_TX_SW_BUFFER  (`$INSTANCE_NAME`_UART_TX_BUFFER_SIZE > \
                                                                    `$INSTANCE_NAME`_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER  (`$INSTANCE_NAME`_INTERNAL_UART_RX_SW_BUFFER)
        #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER  (`$INSTANCE_NAME`_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define `$INSTANCE_NAME`_INTERNAL_RX_BUFFER_SIZE    (`$INSTANCE_NAME`_UART_RX_BUFFER_SIZE + 1u)
        #define `$INSTANCE_NAME`_RX_BUFFER_SIZE             (`$INSTANCE_NAME`_UART_RX_BUFFER_SIZE)
        #define `$INSTANCE_NAME`_TX_BUFFER_SIZE             (`$INSTANCE_NAME`_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define `$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST  (0u)
        #define `$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST (0u != `$INSTANCE_NAME`_UART_WAKE_ENABLE)

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define `$INSTANCE_NAME`_SPI_SLAVE_CONST    (`$INSTANCE_NAME`_SPI_MODE == `$INSTANCE_NAME`_SPI_SLAVE)
    #define `$INSTANCE_NAME`_SPI_MASTER_CONST   (`$INSTANCE_NAME`_SPI_MODE == `$INSTANCE_NAME`_SPI_MASTER)

    /* Direction */
    #define `$INSTANCE_NAME`_RX_DIRECTION ((`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) ? \
                                            (`$INSTANCE_NAME`_SPI_RX_DIRECTION) : (`$INSTANCE_NAME`_UART_RX_DIRECTION))

    #define `$INSTANCE_NAME`_TX_DIRECTION ((`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) ? \
                                            (`$INSTANCE_NAME`_SPI_TX_DIRECTION) : (`$INSTANCE_NAME`_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define `$INSTANCE_NAME`_CHECK_RX_SW_BUFFER (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
    #define `$INSTANCE_NAME`_CHECK_TX_SW_BUFFER (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST    (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
    #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST    (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)

    /* Wake up enable */
    #define `$INSTANCE_NAME`_CHECK_SPI_WAKE_ENABLE  (`$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST)
    #define `$INSTANCE_NAME`_CHECK_UART_WAKE_ENABLE (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define `$INSTANCE_NAME`_CHECK_UART_RTS_CONTROL_FLOW    (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG && \
                                                             `$INSTANCE_NAME`_UART_RTS_ENABLE)

#endif /* End (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/

/* `$INSTANCE_NAME`_SPI_INIT_STRUCT */
typedef struct
{
    /** Mode of operation for SPI. The following defines are available choices:
     *  - `$INSTANCE_NAME`_SPI_SLAVE
     *  - `$INSTANCE_NAME`_SPI_MASTE
    */
    uint32 mode;

    /** Submode of operation for SPI. The following defines are available
     *  choices:
     *  - `$INSTANCE_NAME`_SPI_MODE_MOTOROLA
     *  - `$INSTANCE_NAME`_SPI_MODE_TI_COINCIDES
     *  - `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES
     *  - `$INSTANCE_NAME`_SPI_MODE_NATIONAL
    */
    uint32 submode;

    /** Determines the sclk relationship for Motorola submode. Ignored
     *  for other submodes. The following defines are available choices:
     *  - `$INSTANCE_NAME`_SPI_SCLK_CPHA0_CPOL0
     *  - `$INSTANCE_NAME`_SPI_SCLK_CPHA0_CPOL1
     *  - `$INSTANCE_NAME`_SPI_SCLK_CPHA1_CPOL0
     *  - `$INSTANCE_NAME`_SPI_SCLK_CPHA1_CPOL1
    */
    uint32 sclkMode;

    /** Oversampling factor for the SPI clock. Ignored for Slave mode operation.
    */
    uint32 oversample;

    /** Applies median filter on the input lines: 0 – not applied, 1 – applied.
    */
    uint32 enableMedianFilter;

    /** Applies late sampling of MISO line: 0 – not applied, 1 – applied.
     *  Ignored for slave mode.
    */
    uint32 enableLateSampling;

    /** Enables wakeup from low power mode: 0 – disable, 1 – enable.
     *  Ignored for master mode.
    */
    uint32 enableWake;

    /** Number of data bits for RX direction.
     *  Different dataBitsRx and dataBitsTx are only allowed for National
     *  submode.
    */
    uint32 rxDataBits;

    /** Number of data bits for TX direction.
     *  Different dataBitsRx and dataBitsTx are only allowed for National
     *  submode.
    */
    uint32 txDataBits;

    /** Determines the bit ordering. The following defines are available
     *  choices:
     *  - `$INSTANCE_NAME`_BITS_ORDER_LSB_FIRST
     *  - `$INSTANCE_NAME`_BITS_ORDER_MSB_FIRST
    */
    uint32 bitOrder;

    /** Determines whether transfers are back to back or have SS disabled
     *  between words. Ignored for slave mode. The following defines are
     *  available choices:
     *  - `$INSTANCE_NAME`_SPI_TRANSFER_CONTINUOUS
     *  - `$INSTANCE_NAME`_SPI_TRANSFER_SEPARATED
    */
    uint32 transferSeperation;

    /** Size of the RX buffer in bytes/words (depends on rxDataBits parameter).
     *  A value equal to the RX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the RX FIFO depth results in a software
     *  buffer.
     *  The `$INSTANCE_NAME`_INTR _RX_NOT_EMPTY interrupt has to be enabled to
     *  transfer data into the software buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 rxBufferSize;

    /** Buffer space provided for a RX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal (rxBufferSize + 1) in bytes if
     *    dataBitsRx is less or equal to 8, otherwise (2 * (rxBufferSize + 1))
     *    in bytes. The software RX buffer always keeps one element empty.
     *    For correct operation the allocated RX buffer has to be one element
     *    greater than maximum packet size expected to be received.
    */
    uint8* rxBuffer;

    /** Size of the TX buffer in bytes/words(depends on txDataBits parameter).
     *  A value equal to the TX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the TX FIFO depth results in a software
     *  buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 txBufferSize;

    /** Buffer space provided for a TX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal txBufferSize if dataBitsTx is
     *    less or equal to 8, otherwise (2* txBufferSize).
    */
    uint8* txBuffer;

    /** Enables component interrupt: 0 – disable, 1 – enable.
     *  The interrupt has to be enabled if software buffer is used.
    */
    uint32 enableInterrupt;

    /** Mask of enabled interrupt sources for the RX direction. This mask is
     *  written regardless of the setting of the enable Interrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - `$INSTANCE_NAME`_INTR_RX_FIFO_LEVEL
     *  - `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY
     *  - `$INSTANCE_NAME`_INTR_RX_FULL
     *  - `$INSTANCE_NAME`_INTR_RX_OVERFLOW
     *  - `$INSTANCE_NAME`_INTR_RX_UNDERFLOW
     *  - `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR
    */
    uint32 rxInterruptMask;

    /** FIFO level for an RX FIFO level interrupt. This value is written
     *  regardless of whether the RX FIFO level interrupt source is enabled.
    */
    uint32 rxTriggerLevel;

    /** Mask of enabled interrupt sources for the TX direction. This mask is
     *  written regardless of the setting of the enable Interrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - `$INSTANCE_NAME`_INTR_TX_FIFO_LEVEL
     *  - `$INSTANCE_NAME`_INTR_TX_NOT_FULL
     *  - `$INSTANCE_NAME`_INTR_TX_EMPTY
     *  - `$INSTANCE_NAME`_INTR_TX_OVERFLOW
     *  - `$INSTANCE_NAME`_INTR_TX_UNDERFLOW
     *  - `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE
    */
    uint32 txInterruptMask;

    /** FIFO level for a TX FIFO level interrupt. This value is written
     * regardless of whether the TX FIFO level interrupt source is enabled.
    */
    uint32 txTriggerLevel;

    /** When enabled the TX and RX FIFO depth is doubled and equal to
     *  16 bytes: 0 – disable, 1 – enable. This implies that number of
     *  TX and RX data bits must be less than or equal to 8.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableByteMode;

    /** Enables continuous SCLK generation by the SPI master: 0 – disable,
     *  1 – enable.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableFreeRunSclk;

    /** Active polarity of slave select lines 0-3. This is bit mask where bit
     *  `$INSTANCE_NAME`_SPI_SLAVE_SELECT0 corresponds to slave select 0
     *  polarity, bit `$INSTANCE_NAME`_SPI_SLAVE_SELECT1 – slave select 1
     *  polarity and so on. Polarity constants are:
     *  - `$INSTANCE_NAME`_SPI_SS_ACTIVE_LOW
     *  - `$INSTANCE_NAME`_SPI_SS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 polaritySs;
} `$INSTANCE_NAME`_SPI_INIT_STRUCT;


/* `$INSTANCE_NAME`_UART_INIT_STRUCT */
typedef struct
{
    /** Mode of operation for the UART. The following defines are available
     *  choices:
     *  - `$INSTANCE_NAME`_UART_MODE_STD
     *  - `$INSTANCE_NAME`_UART_MODE_SMARTCARD
     *  - `$INSTANCE_NAME`_UART_MODE_IRDA
    */
    uint32 mode;

    /** Direction of operation for the UART. The following defines are available
     *  choices:
     *  - `$INSTANCE_NAME`_UART_TX_RX
     *  - `$INSTANCE_NAME`_UART_RX
     *  - `$INSTANCE_NAME`_UART_TX
    */
    uint32 direction;

    /** Number of data bits.
    */
    uint32 dataBits;

    /** Determines the parity. The following defines are available choices:
     *  - `$INSTANCE_NAME`_UART_PARITY_EVEN
     *  - `$INSTANCE_NAME`_UART_PARITY_ODD
     *  - `$INSTANCE_NAME`_UART_PARITY_NONE
    */
    uint32 parity;

    /** Determines the number of stop bits. The following defines are available
     *  choices:
     *  - `$INSTANCE_NAME`_UART_STOP_BITS_1
     *  - `$INSTANCE_NAME`_UART_STOP_BITS_1_5
     *  - `$INSTANCE_NAME`_UART_STOP_BITS_2
    */
    uint32 stopBits;

    /** Oversampling factor for the UART.
     *
     *  Note The oversampling factor values are changed when enableIrdaLowPower
     *  is enabled:
     *  - `$INSTANCE_NAME`_UART_IRDA_LP_OVS16
     *  - `$INSTANCE_NAME`_UART_IRDA_LP_OVS32
     *  - `$INSTANCE_NAME`_UART_IRDA_LP_OVS48
     *  - `$INSTANCE_NAME`_UART_IRDA_LP_OVS96
     *  - `$INSTANCE_NAME`_UART_IRDA_LP_OVS192
     *  - `$INSTANCE_NAME`_UART_IRDA_LP_OVS768
     *  - `$INSTANCE_NAME`_UART_IRDA_LP_OVS1536
    */
    uint32 oversample;

    /** Enables IrDA low power RX mode operation: 0 – disable, 1 – enable.
     *  The TX functionality does not work when enabled.
    */
    uint32 enableIrdaLowPower;

    /** Applies median filter on the input lines:  0 – not applied, 1 – applied.
    */
    uint32 enableMedianFilter;

    /** Enables retry when NACK response was received: 0 – disable, 1 – enable.
     *  Only current content of TX FIFO is re-sent.
     *  Ignored for modes other than SmartCard.
    */
    uint32 enableRetryNack;

    /** Inverts polarity of RX line: 0 – non-inverting, 1 – inverting.
     *  Ignored for modes other than IrDA.
    */
    uint32 enableInvertedRx;

    /** Drop data from RX FIFO if parity error is detected: 0 – disable,
     *  1 – enable.
    */
    uint32 dropOnParityErr;

    /** Drop data from RX FIFO if a frame error is detected: 0 – disable,
     *  1 – enable.
    */
    uint32 dropOnFrameErr;

    /** Enables wakeup from low power mode: 0 – disable, 1 – enable.
     *  Ignored for modes other than standard UART. The RX functionality
     *  has to be enabled.
    */
    uint32 enableWake;

    /** Size of the RX buffer in bytes/words (depends on rxDataBits parameter).
     *  A value equal to the RX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the RX FIFO depth results in a software
     *  buffer.
     *  The `$INSTANCE_NAME`_INTR _RX_NOT_EMPTY interrupt has to be enabled to
     *  transfer data into the software buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 rxBufferSize;

    /** Buffer space provided for a RX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal (rxBufferSize + 1) in bytes if
     *    dataBitsRx is less or equal to 8, otherwise (2 * (rxBufferSize + 1))
     *    in bytes. The software RX buffer always keeps one element empty.
     *    For correct operation the allocated RX buffer has to be one element
     *    greater than maximum packet size expected to be received.
    */
    uint8* rxBuffer;

    /** Size of the TX buffer in bytes/words(depends on txDataBits parameter).
     *  A value equal to the TX FIFO depth implies the usage of buffering in
     *  hardware. A value greater than the TX FIFO depth results in a software
     *  buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 /
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE /
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *    PSoC Analog Coprocessor devices.
    */
    uint32 txBufferSize;

    /** Buffer space provided for a TX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software
     *    buffering. The buffer size must equal txBufferSize if dataBitsTx is
     *    less or equal to 8, otherwise (2* txBufferSize).
    */
    uint8* txBuffer;

    /** Enables multiprocessor mode: 0 – disable, 1 – enable.
    */
    uint32 enableMultiproc;

    /** Enables matched address to be accepted: 0 – disable, 1 – enable.
    */
    uint32 multiprocAcceptAddr;

    /** 8 bit address to match in Multiprocessor mode. Ignored for other modes.
    */
    uint32 multiprocAddr;

    /** 8 bit mask of address bits that are compared for a Multiprocessor
     *  address match. Ignored for other modes.
     *  - Bit value 0 – excludes bit from address comparison.
     *  - Bit value 1 – the bit needs to match with the corresponding bit
     *   of the device address.
    */
    uint32 multiprocAddrMask;

    /** Enables component interrupt: 0 – disable, 1 – enable.
     *  The interrupt has to be enabled if software buffer is used.
    */
    uint32 enableInterrupt;

    /** Mask of interrupt sources to enable in the RX direction. This mask is
     *  written regardless of the setting of the enableInterrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - `$INSTANCE_NAME`_INTR_RX_FIFO_LEVEL
     *  - `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY
     *  - `$INSTANCE_NAME`_INTR_RX_FULL
     *  - `$INSTANCE_NAME`_INTR_RX_OVERFLOW
     *  - `$INSTANCE_NAME`_INTR_RX_UNDERFLOW
     *  - `$INSTANCE_NAME`_INTR_RX_FRAME_ERROR
     *  - `$INSTANCE_NAME`_INTR_RX_PARITY_ERROR
    */
    uint32 rxInterruptMask;

    /** FIFO level for an RX FIFO level interrupt. This value is written
     *  regardless of whether the RX FIFO level interrupt source is enabled.
    */
    uint32 rxTriggerLevel;

    /** Mask of interrupt sources to enable in the TX direction. This mask is
     *  written regardless of the setting of the enableInterrupt field.
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - `$INSTANCE_NAME`_INTR_TX_FIFO_LEVEL
     *  - `$INSTANCE_NAME`_INTR_TX_NOT_FULL
     *  - `$INSTANCE_NAME`_INTR_TX_EMPTY
     *  - `$INSTANCE_NAME`_INTR_TX_OVERFLOW
     *  - `$INSTANCE_NAME`_INTR_TX_UNDERFLOW
     *  - `$INSTANCE_NAME`_INTR_TX_UART_DONE
     *  - `$INSTANCE_NAME`_INTR_TX_UART_NACK
     *  - `$INSTANCE_NAME`_INTR_TX_UART_ARB_LOST
    */
    uint32 txInterruptMask;

    /** FIFO level for a TX FIFO level interrupt. This value is written
     *  regardless of whether the TX FIFO level interrupt source is enabled.
    */
    uint32 txTriggerLevel;

    /** When enabled the TX and RX FIFO depth is doubled and equal to
     *  16 bytes: 0 – disable, 1 – enable. This implies that number of
     *  Data bits must be less than or equal to 8.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableByteMode;

    /** Enables usage of CTS input signal by the UART transmitter : 0 – disable,
     *  1 – enable.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 enableCts;

    /** Sets active polarity of CTS input signal:
     *  - `$INSTANCE_NAME`_UART_CTS_ACTIVE_LOW
     *  - `$INSTANCE_NAME`_UART_CTS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 ctsPolarity;

    /** RX FIFO level for RTS signal activation. While the RX FIFO has fewer
     *  entries than the RTS FIFO level value the RTS signal remains active,
     *  otherwise the RTS signal becomes inactive. By setting this field to 0,
     *  RTS signal activation is disabled.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 rtsRxFifoLevel;

    /** Sets active polarity of RTS output signal:
     *  - `$INSTANCE_NAME`_UART_RTS_ ACTIVE_LOW
     *  - `$INSTANCE_NAME`_UART_RTS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     *  PSoC Analog Coprocessor.
    */
    uint8 rtsPolarity;

    /** Configures the width of a break signal in that triggers the break
     *  detection interrupt source. A Break is a low level on the RX line.
     *  Valid range is 1-16 UART bits times.
    */
    uint8 breakWidth;
} `$INSTANCE_NAME`_UART_INIT_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_spi
* @{
*/
/* SPI specific functions */
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    void `$INSTANCE_NAME`_SpiInit(const `$INSTANCE_NAME`_SPI_INIT_STRUCT *config);
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


#if(`$INSTANCE_NAME`_SCB_MODE_SPI_INC)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiIsBusBusy
    ****************************************************************************//**
    *
    *  Returns the current status on the bus. The bus status is determined using
    *  the slave select signal.
    *  - Motorola and National Semiconductor sub-modes: The bus is busy after
    *    the slave select line is activated and lasts until the slave select line
    *    is deactivated.
    *  - Texas Instrument sub-modes: The bus is busy at the moment of the initial
    *    pulse on the slave select line and lasts until the transfer is complete.
    *    If SPI Master is configured to use "Separated transfers"
    *    (see Continuous versus Separated Transfer Separation), the bus is busy
    *    during each element transfer and is free between each element transfer.
    *    The Master does not activate SS line immediately after data has been
    *    written into the TX FIFO.
    *
    *  \return slaveSelect: Current status on the bus.
    *   If the returned value is nonzero, the bus is busy.
    *   If zero is returned, the bus is free. The bus status is determined using
    *   the slave select signal.
    *
    *******************************************************************************/
    #define `$INSTANCE_NAME`_SpiIsBusBusy() ((uint32) (0u != (`$INSTANCE_NAME`_SPI_STATUS_REG & \
                                                              `$INSTANCE_NAME`_SPI_STATUS_BUS_BUSY)))

    #if (`$INSTANCE_NAME`_SPI_MASTER_CONST)
        void `$INSTANCE_NAME`_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(`$INSTANCE_NAME`_SPI_MASTER_CONST) */

    #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        void `$INSTANCE_NAME`_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */
#endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_INC) */
/** @} spi */

/**
* \addtogroup group_uart
* @{
*/
/* UART specific functions */
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    void `$INSTANCE_NAME`_UartInit(const `$INSTANCE_NAME`_UART_INIT_STRUCT *config);
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(`$INSTANCE_NAME`_SCB_MODE_UART_INC)
    void `$INSTANCE_NAME`_UartSetRxAddress(uint32 address);
    void `$INSTANCE_NAME`_UartSetRxAddressMask(uint32 addressMask);


    /* UART RX direction APIs */
    #if(`$INSTANCE_NAME`_UART_RX_DIRECTION)
        uint32 `$INSTANCE_NAME`_UartGetChar(void);
        uint32 `$INSTANCE_NAME`_UartGetByte(void);

        #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void `$INSTANCE_NAME`_UartSetRtsPolarity(uint32 polarity);
            void `$INSTANCE_NAME`_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */
    #endif /* (`$INSTANCE_NAME`_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(`$INSTANCE_NAME`_UART_TX_DIRECTION)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_UartPutChar
        ****************************************************************************//**
        *
        *  Places a byte of data in the transmit buffer to be sent at the next available
        *  bus time. This function is blocking and waits until there is a space
        *  available to put requested data in the transmit buffer.
        *  For UART Multi Processor mode this function can send 9-bits data as well.
        *  Use `$INSTANCE_NAME`_UART_MP_MARK to add a mark to create an address byte.
        *
        *  \param txDataByte: the data to be transmitted.
        *
        *******************************************************************************/
        #define `$INSTANCE_NAME`_UartPutChar(ch)    `$INSTANCE_NAME`_SpiUartWriteTxData((uint32)(ch))

        void `$INSTANCE_NAME`_UartPutString(const char8 string[]);
        void `$INSTANCE_NAME`_UartPutCRLF(uint32 txDataByte);
        void `$INSTANCE_NAME`_UartSendBreakBlocking(uint32 breakWidth);

        #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void `$INSTANCE_NAME`_UartEnableCts(void);
            void `$INSTANCE_NAME`_UartDisableCts(void);
            void `$INSTANCE_NAME`_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */
    #endif /* (`$INSTANCE_NAME`_UART_TX_DIRECTION) */
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UART_INC) */
/** @} uart */

/**
* \addtogroup group_spi_uart
* @{
*/
#if(`$INSTANCE_NAME`_RX_DIRECTION)
    uint32 `$INSTANCE_NAME`_SpiUartReadRxData(void);
    uint32 `$INSTANCE_NAME`_SpiUartGetRxBufferSize(void);
    void   `$INSTANCE_NAME`_SpiUartClearRxBuffer(void);
#endif /* (`$INSTANCE_NAME`_RX_DIRECTION) */

/* Common APIs TX direction */
#if(`$INSTANCE_NAME`_TX_DIRECTION)
    void   `$INSTANCE_NAME`_SpiUartWriteTxData(uint32 txData);
    void   `$INSTANCE_NAME`_SpiUartPutArray(const `$BitWidthReplacementStringTx` wrBuf[], uint32 count);
    uint32 `$INSTANCE_NAME`_SpiUartGetTxBufferSize(void);
    void   `$INSTANCE_NAME`_SpiUartClearTxBuffer(void);
#endif /* (`$INSTANCE_NAME`_TX_DIRECTION) */
/** @} spi_uart */

CY_ISR_PROTO(`$INSTANCE_NAME`_SPI_UART_ISR);

#if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(`$INSTANCE_NAME`_UART_WAKEUP_ISR);
#endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   `$INSTANCE_NAME`_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 `$INSTANCE_NAME`_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   `$INSTANCE_NAME`_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 `$INSTANCE_NAME`_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        #define `$INSTANCE_NAME`_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    `$INSTANCE_NAME`_rxBufferInternal[(idx)] = ((`$BitWidthReplacementStringRx`) (rxDataByte)); \
                }while(0)

        #define `$INSTANCE_NAME`_GetWordFromRxBuffer(idx) `$INSTANCE_NAME`_rxBufferInternal[(idx)]

    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        #define `$INSTANCE_NAME`_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        `$INSTANCE_NAME`_txBufferInternal[(idx)] = ((`$BitWidthReplacementStringTx`) (txDataByte)); \
                    }while(0)

        #define `$INSTANCE_NAME`_GetWordFromTxBuffer(idx) `$INSTANCE_NAME`_txBufferInternal[(idx)]

    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (`$INSTANCE_NAME`_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define `$INSTANCE_NAME`_SPI_MODE_MOTOROLA      (0x00u)
#define `$INSTANCE_NAME`_SPI_MODE_TI_COINCIDES  (0x01u)
#define `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES   (0x11u)
#define `$INSTANCE_NAME`_SPI_MODE_NATIONAL      (0x02u)
#define `$INSTANCE_NAME`_SPI_MODE_MASK          (0x03u)
#define `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define `$INSTANCE_NAME`_SPI_MODE_NS_MICROWIRE  (`$INSTANCE_NAME`_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define `$INSTANCE_NAME`_BITS_ORDER_LSB_FIRST   (0u)
#define `$INSTANCE_NAME`_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define `$INSTANCE_NAME`_SPI_TRANSFER_SEPARATED     (0u)
#define `$INSTANCE_NAME`_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT0    (`$INSTANCE_NAME`_SCB__SS0_POSISTION)
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT1    (`$INSTANCE_NAME`_SCB__SS1_POSISTION)
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT2    (`$INSTANCE_NAME`_SCB__SS2_POSISTION)
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT3    (`$INSTANCE_NAME`_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define `$INSTANCE_NAME`_SPI_SS_ACTIVE_LOW  (0u)
#define `$INSTANCE_NAME`_SPI_SS_ACTIVE_HIGH (1u)

#define `$INSTANCE_NAME`_INTR_SPIM_TX_RESTORE   (`$INSTANCE_NAME`_INTR_TX_OVERFLOW)

#define `$INSTANCE_NAME`_INTR_SPIS_TX_RESTORE     (`$INSTANCE_NAME`_INTR_TX_OVERFLOW | \
                                                 `$INSTANCE_NAME`_INTR_TX_UNDERFLOW)

/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define `$INSTANCE_NAME`_UART_MODE_STD          (0u)
#define `$INSTANCE_NAME`_UART_MODE_SMARTCARD    (1u)
#define `$INSTANCE_NAME`_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define `$INSTANCE_NAME`_UART_RX    (1u)
#define `$INSTANCE_NAME`_UART_TX    (2u)
#define `$INSTANCE_NAME`_UART_TX_RX (3u)

/* UART parity enum */
#define `$INSTANCE_NAME`_UART_PARITY_EVEN   (0u)
#define `$INSTANCE_NAME`_UART_PARITY_ODD    (1u)
#define `$INSTANCE_NAME`_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define `$INSTANCE_NAME`_UART_STOP_BITS_1   (2u)
#define `$INSTANCE_NAME`_UART_STOP_BITS_1_5 (3u)
#define `$INSTANCE_NAME`_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS16     (16u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS32     (32u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS48     (48u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS96     (96u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS192    (192u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS768    (768u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define `$INSTANCE_NAME`_UART_MP_MARK       (0x100u)
#define `$INSTANCE_NAME`_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define `$INSTANCE_NAME`_UART_CTS_ACTIVE_LOW    (0u)
#define `$INSTANCE_NAME`_UART_CTS_ACTIVE_HIGH   (1u)
#define `$INSTANCE_NAME`_UART_RTS_ACTIVE_LOW    (0u)
#define `$INSTANCE_NAME`_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define `$INSTANCE_NAME`_INTR_RX_ERR        (`$INSTANCE_NAME`_INTR_RX_OVERFLOW    | \
                                             `$INSTANCE_NAME`_INTR_RX_UNDERFLOW   | \
                                             `$INSTANCE_NAME`_INTR_RX_FRAME_ERROR | \
                                             `$INSTANCE_NAME`_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for `$INSTANCE_NAME`_UartGetByte() */
#define `$INSTANCE_NAME`_UART_RX_OVERFLOW       (`$INSTANCE_NAME`_INTR_RX_OVERFLOW << 8u)
#define `$INSTANCE_NAME`_UART_RX_UNDERFLOW      (`$INSTANCE_NAME`_INTR_RX_UNDERFLOW << 8u)
#define `$INSTANCE_NAME`_UART_RX_FRAME_ERROR    (`$INSTANCE_NAME`_INTR_RX_FRAME_ERROR << 8u)
#define `$INSTANCE_NAME`_UART_RX_PARITY_ERROR   (`$INSTANCE_NAME`_INTR_RX_PARITY_ERROR << 8u)
#define `$INSTANCE_NAME`_UART_RX_ERROR_MASK     (`$INSTANCE_NAME`_UART_RX_OVERFLOW    | \
                                                 `$INSTANCE_NAME`_UART_RX_UNDERFLOW   | \
                                                 `$INSTANCE_NAME`_UART_RX_FRAME_ERROR | \
                                                 `$INSTANCE_NAME`_UART_RX_PARITY_ERROR)

#define `$INSTANCE_NAME`_INTR_UART_TX_RESTORE   (`$INSTANCE_NAME`_INTR_TX_OVERFLOW  | \
                                                 `$INSTANCE_NAME`_INTR_TX_UART_NACK | \
                                                 `$INSTANCE_NAME`_INTR_TX_UART_DONE | \
                                                 `$INSTANCE_NAME`_INTR_TX_UART_ARB_LOST)


/***************************************
*     Vars with External Linkage
***************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const `$INSTANCE_NAME`_SPI_INIT_STRUCT  `$INSTANCE_NAME`_configSpi;
    extern const `$INSTANCE_NAME`_UART_INIT_STRUCT `$INSTANCE_NAME`_configUart;
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST && `$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
    extern uint8 `$INSTANCE_NAME`_skipStart;
#endif /* (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST && `$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define `$INSTANCE_NAME`_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR)
#define `$INSTANCE_NAME`_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE)
#define `$INSTANCE_NAME`_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~`$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR)

#define `$INSTANCE_NAME`_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~`$INSTANCE_NAME`_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define `$INSTANCE_NAME`_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS16   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS16 : \
         ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS32   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS32 : \
          ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS48   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS48 : \
           ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS96   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS96 : \
            ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS192  == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS192 : \
             ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS768  == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS768 : \
              ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS1536 == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS16)))))))

#define `$INSTANCE_NAME`_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (`$INSTANCE_NAME`_UART_RX & (direction))) ? \
                                                                     (`$INSTANCE_NAME`_RX_CTRL_ENABLED) : (0u))

#define `$INSTANCE_NAME`_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (`$INSTANCE_NAME`_UART_TX & (direction))) ? \
                                                                     (`$INSTANCE_NAME`_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define `$INSTANCE_NAME`_CTRL_SPI      (`$INSTANCE_NAME`_CTRL_MODE_SPI)
#define `$INSTANCE_NAME`_SPI_RX_CTRL   (`$INSTANCE_NAME`_RX_CTRL_ENABLED)
#define `$INSTANCE_NAME`_SPI_TX_CTRL   (`$INSTANCE_NAME`_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define `$INSTANCE_NAME`_SPI_SS_POLARITY \
             (((uint32) `$INSTANCE_NAME`_SPI_SS0_POLARITY << `$INSTANCE_NAME`_SPI_SLAVE_SELECT0) | \
              ((uint32) `$INSTANCE_NAME`_SPI_SS1_POLARITY << `$INSTANCE_NAME`_SPI_SLAVE_SELECT1) | \
              ((uint32) `$INSTANCE_NAME`_SPI_SS2_POLARITY << `$INSTANCE_NAME`_SPI_SLAVE_SELECT2) | \
              ((uint32) `$INSTANCE_NAME`_SPI_SS3_POLARITY << `$INSTANCE_NAME`_SPI_SLAVE_SELECT3))

#if(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define `$INSTANCE_NAME`_SPI_DEFAULT_CTRL \
                    (`$INSTANCE_NAME`_GET_CTRL_OVS(`$INSTANCE_NAME`_SPI_OVS_FACTOR) | \
                     `$INSTANCE_NAME`_GET_CTRL_BYTE_MODE (`$INSTANCE_NAME`_SPI_BYTE_MODE_ENABLE) | \
                     `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE(`$INSTANCE_NAME`_SPI_WAKE_ENABLE)      | \
                     `$INSTANCE_NAME`_CTRL_SPI)

    #define `$INSTANCE_NAME`_SPI_DEFAULT_SPI_CTRL \
                    (`$INSTANCE_NAME`_GET_SPI_CTRL_CONTINUOUS    (`$INSTANCE_NAME`_SPI_TRANSFER_SEPARATION)       | \
                     `$INSTANCE_NAME`_GET_SPI_CTRL_SELECT_PRECEDE(`$INSTANCE_NAME`_SPI_SUB_MODE &                   \
                                                                  `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES_MASK)     | \
                     `$INSTANCE_NAME`_GET_SPI_CTRL_SCLK_MODE     (`$INSTANCE_NAME`_SPI_CLOCK_MODE)                | \
                     `$INSTANCE_NAME`_GET_SPI_CTRL_LATE_MISO_SAMPLE(`$INSTANCE_NAME`_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     `$INSTANCE_NAME`_GET_SPI_CTRL_SCLK_CONTINUOUS(`$INSTANCE_NAME`_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     `$INSTANCE_NAME`_GET_SPI_CTRL_SSEL_POLARITY (`$INSTANCE_NAME`_SPI_SS_POLARITY)               | \
                     `$INSTANCE_NAME`_GET_SPI_CTRL_SUB_MODE      (`$INSTANCE_NAME`_SPI_SUB_MODE)                  | \
                     `$INSTANCE_NAME`_GET_SPI_CTRL_MASTER_MODE   (`$INSTANCE_NAME`_SPI_MODE))

    /* RX direction */
    #define `$INSTANCE_NAME`_SPI_DEFAULT_RX_CTRL \
                    (`$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(`$INSTANCE_NAME`_SPI_RX_DATA_BITS_NUM)     | \
                     `$INSTANCE_NAME`_GET_RX_CTRL_BIT_ORDER (`$INSTANCE_NAME`_SPI_BITS_ORDER)           | \
                     `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN    (`$INSTANCE_NAME`_SPI_MEDIAN_FILTER_ENABLE) | \
                     `$INSTANCE_NAME`_SPI_RX_CTRL)

    #define `$INSTANCE_NAME`_SPI_DEFAULT_RX_FIFO_CTRL \
                    `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(`$INSTANCE_NAME`_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define `$INSTANCE_NAME`_SPI_DEFAULT_TX_CTRL \
                    (`$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(`$INSTANCE_NAME`_SPI_TX_DATA_BITS_NUM) | \
                     `$INSTANCE_NAME`_GET_TX_CTRL_BIT_ORDER (`$INSTANCE_NAME`_SPI_BITS_ORDER)       | \
                     `$INSTANCE_NAME`_SPI_TX_CTRL)

    #define `$INSTANCE_NAME`_SPI_DEFAULT_TX_FIFO_CTRL \
                    `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(`$INSTANCE_NAME`_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define `$INSTANCE_NAME`_SPI_DEFAULT_INTR_SPI_EC_MASK   (`$INSTANCE_NAME`_NO_INTR_SOURCES)

    #define `$INSTANCE_NAME`_SPI_DEFAULT_INTR_I2C_EC_MASK   (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (`$INSTANCE_NAME`_SPI_INTR_RX_MASK & `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR)

    #define `$INSTANCE_NAME`_SPI_DEFAULT_INTR_MASTER_MASK \
                    (`$INSTANCE_NAME`_SPI_INTR_TX_MASK & `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE)

    #define `$INSTANCE_NAME`_SPI_DEFAULT_INTR_RX_MASK \
                    (`$INSTANCE_NAME`_SPI_INTR_RX_MASK & (uint32) ~`$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR)

    #define `$INSTANCE_NAME`_SPI_DEFAULT_INTR_TX_MASK \
                    (`$INSTANCE_NAME`_SPI_INTR_TX_MASK & (uint32) ~`$INSTANCE_NAME`_INTR_MASTER_SPI_DONE)

#endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define `$INSTANCE_NAME`_CTRL_UART      (`$INSTANCE_NAME`_CTRL_MODE_UART)
#define `$INSTANCE_NAME`_UART_RX_CTRL   (`$INSTANCE_NAME`_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define `$INSTANCE_NAME`_UART_TX_CTRL   (`$INSTANCE_NAME`_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(`$INSTANCE_NAME`_UART_MODE_IRDA == `$INSTANCE_NAME`_UART_SUB_MODE)

        #define `$INSTANCE_NAME`_DEFAULT_CTRL_OVS   ((0u != `$INSTANCE_NAME`_UART_IRDA_LOW_POWER) ?              \
                                (`$INSTANCE_NAME`_UART_GET_CTRL_OVS_IRDA_LP(`$INSTANCE_NAME`_UART_OVS_FACTOR)) : \
                                (`$INSTANCE_NAME`_CTRL_OVS_IRDA_OVS16))

    #else

        #define `$INSTANCE_NAME`_DEFAULT_CTRL_OVS   `$INSTANCE_NAME`_GET_CTRL_OVS(`$INSTANCE_NAME`_UART_OVS_FACTOR)

    #endif /* (`$INSTANCE_NAME`_UART_MODE_IRDA == `$INSTANCE_NAME`_UART_SUB_MODE) */

    #define `$INSTANCE_NAME`_UART_DEFAULT_CTRL \
                                (`$INSTANCE_NAME`_GET_CTRL_BYTE_MODE  (`$INSTANCE_NAME`_UART_BYTE_MODE_ENABLE)  | \
                                 `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(`$INSTANCE_NAME`_UART_MP_ACCEPT_ADDRESS) | \
                                 `$INSTANCE_NAME`_DEFAULT_CTRL_OVS                                              | \
                                 `$INSTANCE_NAME`_CTRL_UART)

    #define `$INSTANCE_NAME`_UART_DEFAULT_UART_CTRL \
                                    (`$INSTANCE_NAME`_GET_UART_CTRL_MODE(`$INSTANCE_NAME`_UART_SUB_MODE))

    /* RX direction */
    #define `$INSTANCE_NAME`_UART_DEFAULT_RX_CTRL_PARITY \
                                ((`$INSTANCE_NAME`_UART_PARITY_NONE != `$INSTANCE_NAME`_UART_PARITY_TYPE) ?      \
                                  (`$INSTANCE_NAME`_GET_UART_RX_CTRL_PARITY(`$INSTANCE_NAME`_UART_PARITY_TYPE) | \
                                   `$INSTANCE_NAME`_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define `$INSTANCE_NAME`_UART_DEFAULT_UART_RX_CTRL \
                    (`$INSTANCE_NAME`_GET_UART_RX_CTRL_MODE(`$INSTANCE_NAME`_UART_STOP_BITS_NUM)                    | \
                     `$INSTANCE_NAME`_GET_UART_RX_CTRL_POLARITY(`$INSTANCE_NAME`_UART_IRDA_POLARITY)                | \
                     `$INSTANCE_NAME`_GET_UART_RX_CTRL_MP_MODE(`$INSTANCE_NAME`_UART_MP_MODE_ENABLE)                | \
                     `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(`$INSTANCE_NAME`_UART_DROP_ON_PARITY_ERR) | \
                     `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(`$INSTANCE_NAME`_UART_DROP_ON_FRAME_ERR)   | \
                     `$INSTANCE_NAME`_GET_UART_RX_CTRL_BREAK_WIDTH(`$INSTANCE_NAME`_UART_RX_BREAK_WIDTH)            | \
                     `$INSTANCE_NAME`_UART_DEFAULT_RX_CTRL_PARITY)


    #define `$INSTANCE_NAME`_UART_DEFAULT_RX_CTRL \
                                (`$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(`$INSTANCE_NAME`_UART_DATA_BITS_NUM)        | \
                                 `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN    (`$INSTANCE_NAME`_UART_MEDIAN_FILTER_ENABLE) | \
                                 `$INSTANCE_NAME`_GET_UART_RX_CTRL_ENABLED(`$INSTANCE_NAME`_UART_DIRECTION))

    #define `$INSTANCE_NAME`_UART_DEFAULT_RX_FIFO_CTRL \
                                `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(`$INSTANCE_NAME`_UART_RX_TRIGGER_LEVEL)

    #define `$INSTANCE_NAME`_UART_DEFAULT_RX_MATCH_REG  ((0u != `$INSTANCE_NAME`_UART_MP_MODE_ENABLE) ?          \
                                (`$INSTANCE_NAME`_GET_RX_MATCH_ADDR(`$INSTANCE_NAME`_UART_MP_RX_ADDRESS) | \
                                 `$INSTANCE_NAME`_GET_RX_MATCH_MASK(`$INSTANCE_NAME`_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define `$INSTANCE_NAME`_UART_DEFAULT_TX_CTRL_PARITY (`$INSTANCE_NAME`_UART_DEFAULT_RX_CTRL_PARITY)

    #define `$INSTANCE_NAME`_UART_DEFAULT_UART_TX_CTRL \
                                (`$INSTANCE_NAME`_GET_UART_TX_CTRL_MODE(`$INSTANCE_NAME`_UART_STOP_BITS_NUM)       | \
                                 `$INSTANCE_NAME`_GET_UART_TX_CTRL_RETRY_NACK(`$INSTANCE_NAME`_UART_RETRY_ON_NACK) | \
                                 `$INSTANCE_NAME`_UART_DEFAULT_TX_CTRL_PARITY)

    #define `$INSTANCE_NAME`_UART_DEFAULT_TX_CTRL \
                                (`$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(`$INSTANCE_NAME`_UART_DATA_BITS_NUM) | \
                                 `$INSTANCE_NAME`_GET_UART_TX_CTRL_ENABLED(`$INSTANCE_NAME`_UART_DIRECTION))

    #define `$INSTANCE_NAME`_UART_DEFAULT_TX_FIFO_CTRL \
                                `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(`$INSTANCE_NAME`_UART_TX_TRIGGER_LEVEL)

    #define `$INSTANCE_NAME`_UART_DEFAULT_FLOW_CTRL \
                        (`$INSTANCE_NAME`_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(`$INSTANCE_NAME`_UART_RTS_FIFO_LEVEL) | \
                         `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_RTS_POLARITY (`$INSTANCE_NAME`_UART_RTS_POLARITY)   | \
                         `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_CTS_POLARITY (`$INSTANCE_NAME`_UART_CTS_POLARITY)   | \
                         `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_CTS_ENABLE   (`$INSTANCE_NAME`_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define `$INSTANCE_NAME`_UART_DEFAULT_INTR_I2C_EC_MASK  (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_UART_DEFAULT_INTR_SPI_EC_MASK  (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_UART_DEFAULT_INTR_SLAVE_MASK   (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_UART_DEFAULT_INTR_MASTER_MASK  (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_UART_DEFAULT_INTR_RX_MASK      (`$INSTANCE_NAME`_UART_INTR_RX_MASK)
    #define `$INSTANCE_NAME`_UART_DEFAULT_INTR_TX_MASK      (`$INSTANCE_NAME`_UART_INTR_TX_MASK)

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS0    (`$INSTANCE_NAME`_SPI_SLAVE_SELECT0)
#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS1    (`$INSTANCE_NAME`_SPI_SLAVE_SELECT1)
#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS2    (`$INSTANCE_NAME`_SPI_SLAVE_SELECT2)
#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS3    (`$INSTANCE_NAME`_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
