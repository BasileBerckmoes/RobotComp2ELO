/***************************************************************************//**
* \file `$INSTANCE_NAME`_SPI.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
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

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const `$INSTANCE_NAME`_SPI_INIT_STRUCT `$INSTANCE_NAME`_configSpi =
    {
        `$INSTANCE_NAME`_SPI_MODE,
        `$INSTANCE_NAME`_SPI_SUB_MODE,
        `$INSTANCE_NAME`_SPI_CLOCK_MODE,
        `$INSTANCE_NAME`_SPI_OVS_FACTOR,
        `$INSTANCE_NAME`_SPI_MEDIAN_FILTER_ENABLE,
        `$INSTANCE_NAME`_SPI_LATE_MISO_SAMPLE_ENABLE,
        `$INSTANCE_NAME`_SPI_WAKE_ENABLE,
        `$INSTANCE_NAME`_SPI_RX_DATA_BITS_NUM,
        `$INSTANCE_NAME`_SPI_TX_DATA_BITS_NUM,
        `$INSTANCE_NAME`_SPI_BITS_ORDER,
        `$INSTANCE_NAME`_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) `$INSTANCE_NAME`_SCB_IRQ_INTERNAL,
        `$INSTANCE_NAME`_SPI_INTR_RX_MASK,
        `$INSTANCE_NAME`_SPI_RX_TRIGGER_LEVEL,
        `$INSTANCE_NAME`_SPI_INTR_TX_MASK,
        `$INSTANCE_NAME`_SPI_TX_TRIGGER_LEVEL,
        (uint8) `$INSTANCE_NAME`_SPI_BYTE_MODE_ENABLE,
        (uint8) `$INSTANCE_NAME`_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) `$INSTANCE_NAME`_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiInit
    ****************************************************************************//**
    *
    *  Configures the `$INSTANCE_NAME` for SPI operation.
    *
    *  This function is intended specifically to be used when the `$INSTANCE_NAME` 
    *  configuration is set to “Unconfigured `$INSTANCE_NAME`” in the customizer. 
    *  After initializing the `$INSTANCE_NAME` in SPI mode using this function, 
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
    void `$INSTANCE_NAME`_SpiInit(const `$INSTANCE_NAME`_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_SPI, config->mode, `$INSTANCE_NAME`_DUMMY_PARAM);

            /* Store internal configuration */
            `$INSTANCE_NAME`_scbMode       = (uint8) `$INSTANCE_NAME`_SCB_MODE_SPI;
            `$INSTANCE_NAME`_scbEnableWake = (uint8) config->enableWake;
            `$INSTANCE_NAME`_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            `$INSTANCE_NAME`_rxBuffer      =         config->rxBuffer;
            `$INSTANCE_NAME`_rxDataBits    = (uint8) config->rxDataBits;
            `$INSTANCE_NAME`_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            `$INSTANCE_NAME`_txBuffer      =         config->txBuffer;
            `$INSTANCE_NAME`_txDataBits    = (uint8) config->txDataBits;
            `$INSTANCE_NAME`_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_GET_CTRL_OVS(config->oversample)           |
                                            `$INSTANCE_NAME`_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            `$INSTANCE_NAME`_CTRL_SPI;

            `$INSTANCE_NAME`_SPI_CTRL_REG = `$INSTANCE_NAME`_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            `$INSTANCE_NAME`_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES_MASK) |
                                            `$INSTANCE_NAME`_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            `$INSTANCE_NAME`_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            `$INSTANCE_NAME`_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            `$INSTANCE_NAME`_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            `$INSTANCE_NAME`_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            `$INSTANCE_NAME`_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            `$INSTANCE_NAME`_RX_CTRL_REG     =  `$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                `$INSTANCE_NAME`_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                `$INSTANCE_NAME`_SPI_RX_CTRL;

            `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                `$INSTANCE_NAME`_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                `$INSTANCE_NAME`_SPI_TX_CTRL;

            `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_SPI_UART_ISR);

            /* Configure interrupt sources */
            `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_INTR_TX_MASK_REG);

            /* Set active SS0 */
            `$INSTANCE_NAME`_SpiSetActiveSlaveSelect(`$INSTANCE_NAME`_SPI_SLAVE_SELECT0);

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
    * Function Name: `$INSTANCE_NAME`_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiInit(void)
    {
        /* Configure SPI interface */
        `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_SPI_DEFAULT_CTRL;
        `$INSTANCE_NAME`_SPI_CTRL_REG = `$INSTANCE_NAME`_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_SPI_DEFAULT_RX_CTRL;
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_SPI_DEFAULT_TX_CTRL;
        `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
            CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_SPI_UART_ISR);
    #endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_SPI_DEFAULT_INTR_I2C_EC_MASK;
        `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_SPI_DEFAULT_INTR_SPI_EC_MASK;
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_SPI_DEFAULT_INTR_SLAVE_MASK;
        `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_SPI_DEFAULT_INTR_MASTER_MASK;
        `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_SPI_DEFAULT_INTR_RX_MASK;
        `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (`$INSTANCE_NAME`_SPI_MASTER_CONST)
        `$INSTANCE_NAME`_SpiSetActiveSlaveSelect(`$INSTANCE_NAME`_SPI_SLAVE_SELECT0);
    #endif /* (`$INSTANCE_NAME`_SPI_MASTER_CONST) */

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
* Function Name: `$INSTANCE_NAME`_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiPostEnable(void)
{
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    if (`$INSTANCE_NAME`_CHECK_SPI_MASTER)
    {
    #if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN) */

    #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */

    #if (`$INSTANCE_NAME`_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS1_HSIOM_REG, `$INSTANCE_NAME`_SS1_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS1_HSIOM_POS, `$INSTANCE_NAME`_SS1_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_SS1_PIN) */

    #if (`$INSTANCE_NAME`_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS2_HSIOM_REG, `$INSTANCE_NAME`_SS2_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS2_HSIOM_POS, `$INSTANCE_NAME`_SS2_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_SS2_PIN) */

    #if (`$INSTANCE_NAME`_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS3_HSIOM_REG, `$INSTANCE_NAME`_SS3_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS3_HSIOM_POS, `$INSTANCE_NAME`_SS3_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_SS3_PIN) */
    }

#else

    #if (`$INSTANCE_NAME`_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SCLK_M_HSIOM_REG, `$INSTANCE_NAME`_SCLK_M_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SCLK_M_HSIOM_POS, `$INSTANCE_NAME`_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_MISO_SDA_TX_PIN_PIN) */

    #if (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS0_M_HSIOM_REG, `$INSTANCE_NAME`_SS0_M_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS0_M_HSIOM_POS, `$INSTANCE_NAME`_SS0_M_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN) */

    #if (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS1_M_HSIOM_REG, `$INSTANCE_NAME`_SS1_M_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS1_M_HSIOM_POS, `$INSTANCE_NAME`_SS1_M_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN) */

    #if (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS2_M_HSIOM_REG, `$INSTANCE_NAME`_SS2_M_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS2_M_HSIOM_POS, `$INSTANCE_NAME`_SS2_M_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN) */

    #if (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS3_M_HSIOM_REG, `$INSTANCE_NAME`_SS3_M_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS3_M_HSIOM_POS, `$INSTANCE_NAME`_SS3_M_HSIOM_SEL_SPI);
    #endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN) */

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_IntrTxMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiStop(void)
{
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    if (`$INSTANCE_NAME`_CHECK_SPI_MASTER)
    {
    #if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
        /* Set output pin state after block is disabled */
        `$INSTANCE_NAME`_`$PinName2Unconfig`_Write(`$INSTANCE_NAME`_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_`$PinName2Unconfig`_PIN) */

    #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
        /* Set output pin state after block is disabled */
        `$INSTANCE_NAME`_`$PinName3Unconfig`_Write(`$INSTANCE_NAME`_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_REG, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_POS, `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_`$PinName3Unconfig`_PIN) */

    #if (`$INSTANCE_NAME`_SS1_PIN)
        /* Set output pin state after block is disabled */
        `$INSTANCE_NAME`_spi_ss1_Write(`$INSTANCE_NAME`_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS1_HSIOM_REG, `$INSTANCE_NAME`_SS1_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS1_HSIOM_POS, `$INSTANCE_NAME`_SS1_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_SS1_PIN) */

    #if (`$INSTANCE_NAME`_SS2_PIN)
        /* Set output pin state after block is disabled */
        `$INSTANCE_NAME`_spi_ss2_Write(`$INSTANCE_NAME`_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS2_HSIOM_REG, `$INSTANCE_NAME`_SS2_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS2_HSIOM_POS, `$INSTANCE_NAME`_SS2_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_SS2_PIN) */

    #if (`$INSTANCE_NAME`_SS3_PIN)
        /* Set output pin state after block is disabled */
        `$INSTANCE_NAME`_spi_ss3_Write(`$INSTANCE_NAME`_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS3_HSIOM_REG, `$INSTANCE_NAME`_SS3_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS3_HSIOM_POS, `$INSTANCE_NAME`_SS3_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_GetTxInterruptMode() & `$INSTANCE_NAME`_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_GetTxInterruptMode() & `$INSTANCE_NAME`_INTR_SPIS_TX_RESTORE);
    }

#else

#if (`$INSTANCE_NAME`_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    `$INSTANCE_NAME`_sclk_m_Write(`$INSTANCE_NAME`_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SCLK_M_HSIOM_REG, `$INSTANCE_NAME`_SCLK_M_HSIOM_MASK,
                                   `$INSTANCE_NAME`_SCLK_M_HSIOM_POS, `$INSTANCE_NAME`_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (`$INSTANCE_NAME`_MISO_SDA_TX_PIN_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    `$INSTANCE_NAME`_ss0_m_Write(`$INSTANCE_NAME`_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS0_M_HSIOM_REG, `$INSTANCE_NAME`_SS0_M_HSIOM_MASK,
                                   `$INSTANCE_NAME`_SS0_M_HSIOM_POS, `$INSTANCE_NAME`_SS0_M_HSIOM_SEL_GPIO);
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    `$INSTANCE_NAME`_ss1_m_Write(`$INSTANCE_NAME`_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS1_M_HSIOM_REG, `$INSTANCE_NAME`_SS1_M_HSIOM_MASK,
                                   `$INSTANCE_NAME`_SS1_M_HSIOM_POS, `$INSTANCE_NAME`_SS1_M_HSIOM_SEL_GPIO);
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    `$INSTANCE_NAME`_ss2_m_Write(`$INSTANCE_NAME`_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS2_M_HSIOM_REG, `$INSTANCE_NAME`_SS2_M_HSIOM_MASK,
                                   `$INSTANCE_NAME`_SS2_M_HSIOM_POS, `$INSTANCE_NAME`_SS2_M_HSIOM_SEL_GPIO);
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    `$INSTANCE_NAME`_ss3_m_Write(`$INSTANCE_NAME`_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS3_M_HSIOM_REG, `$INSTANCE_NAME`_SS3_M_HSIOM_MASK,
                                   `$INSTANCE_NAME`_SS3_M_HSIOM_POS, `$INSTANCE_NAME`_SS3_M_HSIOM_SEL_GPIO);
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN) */

    #if (`$INSTANCE_NAME`_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_GetTxInterruptMode() & `$INSTANCE_NAME`_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        `$INSTANCE_NAME`_IntrTxMask = LO16(`$INSTANCE_NAME`_GetTxInterruptMode() & `$INSTANCE_NAME`_INTR_SPIS_TX_RESTORE);
    #endif /* (`$INSTANCE_NAME`_SPI_MASTER_CONST) */

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (`$INSTANCE_NAME`_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = `$INSTANCE_NAME`_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~`$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  `$INSTANCE_NAME`_GET_SPI_CTRL_SS(slaveSelect);

        `$INSTANCE_NAME`_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_CONST) */


#if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - `$INSTANCE_NAME`_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - `$INSTANCE_NAME`_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - `$INSTANCE_NAME`_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = `$INSTANCE_NAME`_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            `$INSTANCE_NAME`_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            `$INSTANCE_NAME`_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */


#if(`$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
        `$INSTANCE_NAME`_SetSpiExtClkInterruptMode(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        `$INSTANCE_NAME`_SetSpiExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
    }
#endif /* (`$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
