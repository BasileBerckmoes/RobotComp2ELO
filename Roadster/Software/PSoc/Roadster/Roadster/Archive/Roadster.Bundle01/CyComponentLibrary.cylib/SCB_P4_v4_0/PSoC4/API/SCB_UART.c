/***************************************************************************//**
* \file `$INSTANCE_NAME`_UART.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_SPI_UART_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST && `$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when `$INSTANCE_NAME`_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 `$INSTANCE_NAME`_skipStart = 1u;
    /** \} globals */
#endif /* (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST && `$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const `$INSTANCE_NAME`_UART_INIT_STRUCT `$INSTANCE_NAME`_configUart =
    {
        `$INSTANCE_NAME`_UART_SUB_MODE,
        `$INSTANCE_NAME`_UART_DIRECTION,
        `$INSTANCE_NAME`_UART_DATA_BITS_NUM,
        `$INSTANCE_NAME`_UART_PARITY_TYPE,
        `$INSTANCE_NAME`_UART_STOP_BITS_NUM,
        `$INSTANCE_NAME`_UART_OVS_FACTOR,
        `$INSTANCE_NAME`_UART_IRDA_LOW_POWER,
        `$INSTANCE_NAME`_UART_MEDIAN_FILTER_ENABLE,
        `$INSTANCE_NAME`_UART_RETRY_ON_NACK,
        `$INSTANCE_NAME`_UART_IRDA_POLARITY,
        `$INSTANCE_NAME`_UART_DROP_ON_PARITY_ERR,
        `$INSTANCE_NAME`_UART_DROP_ON_FRAME_ERR,
        `$INSTANCE_NAME`_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        `$INSTANCE_NAME`_UART_MP_MODE_ENABLE,
        `$INSTANCE_NAME`_UART_MP_ACCEPT_ADDRESS,
        `$INSTANCE_NAME`_UART_MP_RX_ADDRESS,
        `$INSTANCE_NAME`_UART_MP_RX_ADDRESS_MASK,
        (uint32) `$INSTANCE_NAME`_SCB_IRQ_INTERNAL,
        `$INSTANCE_NAME`_UART_INTR_RX_MASK,
        `$INSTANCE_NAME`_UART_RX_TRIGGER_LEVEL,
        `$INSTANCE_NAME`_UART_INTR_TX_MASK,
        `$INSTANCE_NAME`_UART_TX_TRIGGER_LEVEL,
        (uint8) `$INSTANCE_NAME`_UART_BYTE_MODE_ENABLE,
        (uint8) `$INSTANCE_NAME`_UART_CTS_ENABLE,
        (uint8) `$INSTANCE_NAME`_UART_CTS_POLARITY,
        (uint8) `$INSTANCE_NAME`_UART_RTS_POLARITY,
        (uint8) `$INSTANCE_NAME`_UART_RTS_FIFO_LEVEL,
        (uint8) `$INSTANCE_NAME`_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartInit
    ****************************************************************************//**
    *
    *  Configures the `$INSTANCE_NAME` for UART operation.
    *
    *  This function is intended specifically to be used when the `$INSTANCE_NAME`
    *  configuration is set to “Unconfigured `$INSTANCE_NAME`” in the customizer.
    *  After initializing the `$INSTANCE_NAME` in UART mode using this function,
    *  the component can be enabled using the `$INSTANCE_NAME`_Start() or
    * `$INSTANCE_NAME`_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartInit(const `$INSTANCE_NAME`_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (`$INSTANCE_NAME`_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (`$INSTANCE_NAME`_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

            /* Configure pins */
            `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            `$INSTANCE_NAME`_scbMode       = (uint8) `$INSTANCE_NAME`_SCB_MODE_UART;
            `$INSTANCE_NAME`_scbEnableWake = (uint8) config->enableWake;
            `$INSTANCE_NAME`_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            `$INSTANCE_NAME`_rxBuffer      =         config->rxBuffer;
            `$INSTANCE_NAME`_rxDataBits    = (uint8) config->dataBits;
            `$INSTANCE_NAME`_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            `$INSTANCE_NAME`_txBuffer      =         config->txBuffer;
            `$INSTANCE_NAME`_txDataBits    = (uint8) config->dataBits;
            `$INSTANCE_NAME`_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(`$INSTANCE_NAME`_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                `$INSTANCE_NAME`_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (`$INSTANCE_NAME`_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (`$INSTANCE_NAME`_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                `$INSTANCE_NAME`_CTRL_REG  = `$INSTANCE_NAME`_GET_CTRL_OVS(config->oversample);
            }

            `$INSTANCE_NAME`_CTRL_REG     |= `$INSTANCE_NAME`_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             `$INSTANCE_NAME`_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            `$INSTANCE_NAME`_UART_CTRL_REG = `$INSTANCE_NAME`_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            `$INSTANCE_NAME`_UART_RX_CTRL_REG = `$INSTANCE_NAME`_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(`$INSTANCE_NAME`_UART_PARITY_NONE != config->parity)
            {
               `$INSTANCE_NAME`_UART_RX_CTRL_REG |= `$INSTANCE_NAME`_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    `$INSTANCE_NAME`_UART_RX_CTRL_PARITY_ENABLED;
            }

            `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                `$INSTANCE_NAME`_GET_UART_RX_CTRL_ENABLED(config->direction);

            `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                `$INSTANCE_NAME`_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            `$INSTANCE_NAME`_UART_TX_CTRL_REG = `$INSTANCE_NAME`_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                `$INSTANCE_NAME`_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(`$INSTANCE_NAME`_UART_PARITY_NONE != config->parity)
            {
               `$INSTANCE_NAME`_UART_TX_CTRL_REG |= `$INSTANCE_NAME`_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    `$INSTANCE_NAME`_UART_TX_CTRL_PARITY_ENABLED;
            }

            `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                `$INSTANCE_NAME`_GET_UART_TX_CTRL_ENABLED(config->direction);

            `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
            `$INSTANCE_NAME`_UART_FLOW_CTRL_REG = `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            `$INSTANCE_NAME`_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, `$INSTANCE_NAME`_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, &`$INSTANCE_NAME`_UART_WAKEUP_ISR);
        #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_RX_MASK_REG     = config->rxInterruptMask;
            `$INSTANCE_NAME`_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            `$INSTANCE_NAME`_rxBufferHead     = 0u;
            `$INSTANCE_NAME`_rxBufferTail     = 0u;
            `$INSTANCE_NAME`_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            `$INSTANCE_NAME`_txBufferHead = 0u;
            `$INSTANCE_NAME`_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartInit(void)
    {
        /* Configure UART interface */
        `$INSTANCE_NAME`_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        `$INSTANCE_NAME`_UART_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        `$INSTANCE_NAME`_UART_RX_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_UART_RX_CTRL;
        `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_UART_DEFAULT_RX_CTRL;
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_RX_FIFO_CTRL;
        `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        `$INSTANCE_NAME`_UART_TX_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_UART_TX_CTRL;
        `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_UART_DEFAULT_TX_CTRL;
        `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        `$INSTANCE_NAME`_UART_FLOW_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
        CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_SPI_UART_ISR);
    #endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, `$INSTANCE_NAME`_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, &`$INSTANCE_NAME`_UART_WAKEUP_ISR);
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_UART_DEFAULT_INTR_I2C_EC_MASK;
        `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_UART_DEFAULT_INTR_SPI_EC_MASK;
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_UART_DEFAULT_INTR_SLAVE_MASK;
        `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_UART_DEFAULT_INTR_MASTER_MASK;
        `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_UART_DEFAULT_INTR_RX_MASK;
        `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_INTR_TX_MASK_REG);

    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        `$INSTANCE_NAME`_rxBufferHead     = 0u;
        `$INSTANCE_NAME`_rxBufferTail     = 0u;
        `$INSTANCE_NAME`_rxBufferOverflow = 0u;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        `$INSTANCE_NAME`_txBufferHead = 0u;
        `$INSTANCE_NAME`_txBufferTail = 0u;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartPostEnable(void)
{
#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
        if (`$INSTANCE_NAME`_CHECK_`$Pn1Unconfig`_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_MASK,
                                           `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_UART);
        }
    #endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_PIN) */

    #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
            if (`$INSTANCE_NAME`_CHECK_`$Pn3Unconfig`_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_MASK,
                                               `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_UART);
            }
        #endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */
    #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

#else
    #if (`$INSTANCE_NAME`_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_TX_HSIOM_REG, `$INSTANCE_NAME`_TX_HSIOM_MASK,
                                       `$INSTANCE_NAME`_TX_HSIOM_POS, `$INSTANCE_NAME`_TX_HSIOM_SEL_UART);
    #endif /* (`$INSTANCE_NAME`_UART_TX_PIN) */

    #if (`$INSTANCE_NAME`_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_RTS_HSIOM_REG, `$INSTANCE_NAME`_RTS_HSIOM_MASK,
                                       `$INSTANCE_NAME`_RTS_HSIOM_POS, `$INSTANCE_NAME`_RTS_HSIOM_SEL_UART);
    #endif /* (`$INSTANCE_NAME`_UART_RTS_PIN) */
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_IntrTxMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartStop(void)
{
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
        if (`$INSTANCE_NAME`_CHECK_`$Pn1Unconfig`_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_MASK,
                                           `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_GPIO);
        }
    #endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_PIN) */

    #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
            if (`$INSTANCE_NAME`_CHECK_`$Pn3Unconfig`_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                `$INSTANCE_NAME`_`$PinName3Unconfig`_Write(`$INSTANCE_NAME`_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_MASK,
                                               `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_GPIO);
            }
        #endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */
    #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

#else
    #if (`$INSTANCE_NAME`_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_TX_HSIOM_REG, `$INSTANCE_NAME`_TX_HSIOM_MASK,
                                       `$INSTANCE_NAME`_TX_HSIOM_POS, `$INSTANCE_NAME`_TX_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_UART_TX_PIN) */

    #if (`$INSTANCE_NAME`_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        `$INSTANCE_NAME`_rts_Write(`$INSTANCE_NAME`_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_RTS_HSIOM_REG, `$INSTANCE_NAME`_RTS_HSIOM_MASK,
                                       `$INSTANCE_NAME`_RTS_HSIOM_POS, `$INSTANCE_NAME`_RTS_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_UART_RTS_PIN) */

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    `$INSTANCE_NAME`_UART_RX_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START;
#endif /* (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_GetTxInterruptMode() & `$INSTANCE_NAME`_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = `$INSTANCE_NAME`_RX_MATCH_REG;

    matchReg &= ((uint32) ~`$INSTANCE_NAME`_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & `$INSTANCE_NAME`_RX_MATCH_ADDR_MASK)); /* Set address  */

    `$INSTANCE_NAME`_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = `$INSTANCE_NAME`_RX_MATCH_REG;

    matchReg &= ((uint32) ~`$INSTANCE_NAME`_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << `$INSTANCE_NAME`_RX_MATCH_MASK_POS));

    `$INSTANCE_NAME`_RX_MATCH_REG = matchReg;
}


#if(`$INSTANCE_NAME`_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check `$INSTANCE_NAME`_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != `$INSTANCE_NAME`_SpiUartGetRxBufferSize())
        {
            rxData = `$INSTANCE_NAME`_SpiUartReadRxData();
        }

        if (`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - `$INSTANCE_NAME`_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - `$INSTANCE_NAME`_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - `$INSTANCE_NAME`_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - `$INSTANCE_NAME`_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check `$INSTANCE_NAME`_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        `$Cond`if (`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
        {
            `$INSTANCE_NAME`_DisableInt();
        }
        `$EndCond`

        if (0u != `$INSTANCE_NAME`_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            `$Cond`if (`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
            {
                `$INSTANCE_NAME`_EnableInt();
            }
            `$EndCond`

            /* Get received byte */
            rxData = `$INSTANCE_NAME`_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = `$INSTANCE_NAME`_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            `$Cond`if (`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);

                `$INSTANCE_NAME`_EnableInt();
            }
            `$EndCond`
        }

        /* Get and clear RX error mask */
        tmpStatus = (`$INSTANCE_NAME`_GetRxInterruptSource() & `$INSTANCE_NAME`_INTR_RX_ERR);
        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - `$INSTANCE_NAME`_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - `$INSTANCE_NAME`_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                `$INSTANCE_NAME`_UART_FLOW_CTRL_REG |= (uint32)  `$INSTANCE_NAME`_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                `$INSTANCE_NAME`_UART_FLOW_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = `$INSTANCE_NAME`_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~`$INSTANCE_NAME`_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (`$INSTANCE_NAME`_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            `$INSTANCE_NAME`_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

#endif /* (`$INSTANCE_NAME`_UART_RX_DIRECTION) */


#if(`$INSTANCE_NAME`_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            `$INSTANCE_NAME`_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartPutCRLF(uint32 txDataByte)
    {
        `$INSTANCE_NAME`_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        `$INSTANCE_NAME`_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        `$INSTANCE_NAME`_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`SCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_UartEnableCts(void)
        {
            `$INSTANCE_NAME`_UART_FLOW_CTRL_REG |= (uint32)  `$INSTANCE_NAME`_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_UartDisableCts(void)
        {
            `$INSTANCE_NAME`_UART_FLOW_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - `$INSTANCE_NAME`_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - `$INSTANCE_NAME`_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                `$INSTANCE_NAME`_UART_FLOW_CTRL_REG |= (uint32)  `$INSTANCE_NAME`_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                `$INSTANCE_NAME`_UART_FLOW_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartSendBreakBlocking
    ****************************************************************************//**
    *
    * Sends a break condition (logic low) of specified width on UART TX line.
    * Blocks until break is completed. Only call this function when UART TX FIFO
    * and shifter are empty.
    *
    * \param breakWidth
    * Width of break condition. Valid range is 4 to 16 bits.
    *
    * \note
    * Before sending break all UART TX interrupt sources are disabled. The state
    * of UART TX interrupt sources is restored before function returns.
    *
    * \sideeffect
    * If this function is called while there is data in the TX FIFO or shifter that
    * data will be shifted out in packets the size of breakWidth.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = `$INSTANCE_NAME`_GetTxInterruptMode();
        `$INSTANCE_NAME`_SetTxInterruptMode(0u);
        `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = `$INSTANCE_NAME`_TX_CTRL_REG;

        /* Set break width */
        `$INSTANCE_NAME`_TX_CTRL_REG = (`$INSTANCE_NAME`_TX_CTRL_REG & (uint32) ~`$INSTANCE_NAME`_TX_CTRL_DATA_WIDTH_MASK) |
                                        `$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        `$INSTANCE_NAME`_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (`$INSTANCE_NAME`_GetTxInterruptSource() & `$INSTANCE_NAME`_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        `$INSTANCE_NAME`_TX_CTRL_REG = txCtrlReg;
        `$INSTANCE_NAME`_SetTxInterruptMode(txIntrReg);
    }
#endif /* (`$INSTANCE_NAME`_UART_TX_DIRECTION) */


#if (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartSaveConfig(void)
    {
    #if (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != `$INSTANCE_NAME`_skipStart)
        {
            `$INSTANCE_NAME`_UART_RX_CTRL_REG |= (uint32)  `$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            `$INSTANCE_NAME`_UART_RX_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        `$INSTANCE_NAME`_CLEAR_UART_RX_WAKE_INTR;
        `$INSTANCE_NAME`_RxWakeClearPendingInt();
        `$INSTANCE_NAME`_RxWakeEnableInt();
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartRestoreConfig(void)
    {
    #if (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        `$INSTANCE_NAME`_RxWakeDisableInt();
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */
    }


    #if (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(`$INSTANCE_NAME`_UART_WAKEUP_ISR)
        {
        #ifdef `$INSTANCE_NAME`_UART_WAKEUP_ISR_ENTRY_CALLBACK
            `$INSTANCE_NAME`_UART_WAKEUP_ISR_EntryCallback();
        #endif /* `$INSTANCE_NAME`_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            `$INSTANCE_NAME`_CLEAR_UART_RX_WAKE_INTR;

        #ifdef `$INSTANCE_NAME`_UART_WAKEUP_ISR_EXIT_CALLBACK
            `$INSTANCE_NAME`_UART_WAKEUP_ISR_ExitCallback();
        #endif /* `$INSTANCE_NAME`_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */
#endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
