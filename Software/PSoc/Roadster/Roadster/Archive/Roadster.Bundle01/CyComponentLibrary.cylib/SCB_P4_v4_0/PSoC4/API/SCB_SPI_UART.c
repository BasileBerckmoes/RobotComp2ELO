/***************************************************************************//**
* \file `$INSTANCE_NAME`_SPI_UART.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
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

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 `$INSTANCE_NAME`_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 `$INSTANCE_NAME`_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  `$INSTANCE_NAME`_rxBufferOverflow;
    /** \} globals */
#endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

#if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 `$INSTANCE_NAME`_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 `$INSTANCE_NAME`_txBufferTail;
#endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

#if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile `$BitWidthReplacementStringRx` `$INSTANCE_NAME`_rxBufferInternal[`$INSTANCE_NAME`_INTERNAL_RX_BUFFER_SIZE];
#endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER) */

#if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)
    volatile `$BitWidthReplacementStringTx` `$INSTANCE_NAME`_txBufferInternal[`$INSTANCE_NAME`_TX_BUFFER_SIZE];
#endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER) */


#if(`$INSTANCE_NAME`_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  `$INSTANCE_NAME`_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  `$INSTANCE_NAME`_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

        `$Cond`if (`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
        {
            if (`$INSTANCE_NAME`_rxBufferHead != `$INSTANCE_NAME`_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (`$INSTANCE_NAME`_rxBufferTail + 1u);

                if (`$INSTANCE_NAME`_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = `$INSTANCE_NAME`_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                `$INSTANCE_NAME`_rxBufferTail = locTail;

                `$Cond`if (`$INSTANCE_NAME`_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (`$INSTANCE_NAME`_INTR_RX_MASK_REG & `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        `$INSTANCE_NAME`_INTR_RX_MASK_REG |= `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY;
                    }
                }
                `$EndCond`

            }
        }
        `$Cond`else
        {
            /* Read data from RX FIFO */
            rxData = `$INSTANCE_NAME`_RX_FIFO_RD_REG;
        }
        `$EndCond`

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  `$INSTANCE_NAME`_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

        `$Cond`if (`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
        {
            locHead = `$INSTANCE_NAME`_rxBufferHead;

            if(locHead >= `$INSTANCE_NAME`_rxBufferTail)
            {
                size = (locHead - `$INSTANCE_NAME`_rxBufferTail);
            }
            else
            {
                size = (locHead + (`$INSTANCE_NAME`_INTERNAL_RX_BUFFER_SIZE - `$INSTANCE_NAME`_rxBufferTail));
            }
        }
        `$Cond`else
        {
            size = `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES;
        }
        `$EndCond`

        return (size);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  `$INSTANCE_NAME`_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiUartClearRxBuffer(void)
    {
        `$Cond`if (`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            `$INSTANCE_NAME`_DisableInt();

            /* Flush RX software buffer */
            `$INSTANCE_NAME`_rxBufferHead = `$INSTANCE_NAME`_rxBufferTail;
            `$INSTANCE_NAME`_rxBufferOverflow = 0u;

            `$INSTANCE_NAME`_CLEAR_RX_FIFO;
            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ALL);

            `$Cond`if (`$INSTANCE_NAME`_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                `$INSTANCE_NAME`_INTR_RX_MASK_REG |= `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY;
            }
            `$EndCond`
            
            /* Release lock */
            `$INSTANCE_NAME`_EnableInt();
        }
        `$Cond`else
        {
            `$INSTANCE_NAME`_CLEAR_RX_FIFO;
        }
        `$EndCond`
    }

#endif /* (`$INSTANCE_NAME`_RX_DIRECTION) */


#if(`$INSTANCE_NAME`_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  `$INSTANCE_NAME`_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  `$INSTANCE_NAME`_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiUartWriteTxData(uint32 txData)
    {
    #if (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

        `$Cond`if (`$INSTANCE_NAME`_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((`$INSTANCE_NAME`_txBufferHead == `$INSTANCE_NAME`_txBufferTail) &&
                (`$INSTANCE_NAME`_SPI_UART_FIFO_SIZE != `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                `$INSTANCE_NAME`_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (`$INSTANCE_NAME`_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (`$INSTANCE_NAME`_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == `$INSTANCE_NAME`_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_NOT_FULL);

                `$INSTANCE_NAME`_PutWordInTxBuffer(locHead, txData);

                `$INSTANCE_NAME`_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (`$INSTANCE_NAME`_INTR_TX_MASK_REG & `$INSTANCE_NAME`_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    `$INSTANCE_NAME`_INTR_TX_MASK_REG |= (uint32) `$INSTANCE_NAME`_INTR_TX_NOT_FULL;
                }
            }
        }
        `$Cond`else
        {
            /* Wait until TX FIFO has space to put data element */
            while (`$INSTANCE_NAME`_SPI_UART_FIFO_SIZE == `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES)
            {
            }

            `$INSTANCE_NAME`_TX_FIFO_WR_REG = txData;
        }
        `$EndCond`
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  `$INSTANCE_NAME`_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiUartPutArray(const `$BitWidthReplacementStringTx` wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            `$INSTANCE_NAME`_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  `$INSTANCE_NAME`_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

        `$Cond`if (`$INSTANCE_NAME`_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = `$INSTANCE_NAME`_txBufferTail;

            if (`$INSTANCE_NAME`_txBufferHead >= locTail)
            {
                size = (`$INSTANCE_NAME`_txBufferHead - locTail);
            }
            else
            {
                size = (`$INSTANCE_NAME`_txBufferHead + (`$INSTANCE_NAME`_TX_BUFFER_SIZE - locTail));
            }
        }
        `$Cond`else
        {
            size = `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES;
        }
        `$EndCond`

        return (size);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  `$INSTANCE_NAME`_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SpiUartClearTxBuffer(void)
    {
        `$Cond`if (`$INSTANCE_NAME`_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            `$INSTANCE_NAME`_DisableInt();

            /* Flush TX software buffer */
            `$INSTANCE_NAME`_txBufferHead = `$INSTANCE_NAME`_txBufferTail;

            `$INSTANCE_NAME`_INTR_TX_MASK_REG &= (uint32) ~`$INSTANCE_NAME`_INTR_TX_NOT_FULL;
            `$INSTANCE_NAME`_CLEAR_TX_FIFO;
            `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_ALL);

            /* Release lock */
            `$INSTANCE_NAME`_EnableInt();
        }
        `$Cond`else
        {
            `$INSTANCE_NAME`_CLEAR_TX_FIFO;
        }
        `$EndCond`
    }

#endif /* (`$INSTANCE_NAME`_TX_DIRECTION) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = `$INSTANCE_NAME`_GetRxInterruptMode();

    `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = `$INSTANCE_NAME`_GetTxInterruptMode();

    `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (`$INSTANCE_NAME`_ONE_BYTE_WIDTH == `$INSTANCE_NAME`_rxDataBits)
        {
            `$INSTANCE_NAME`_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            `$INSTANCE_NAME`_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            `$INSTANCE_NAME`_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (`$INSTANCE_NAME`_ONE_BYTE_WIDTH == `$INSTANCE_NAME`_rxDataBits)
        {
            value = `$INSTANCE_NAME`_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) `$INSTANCE_NAME`_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)`$INSTANCE_NAME`_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (`$INSTANCE_NAME`_ONE_BYTE_WIDTH == `$INSTANCE_NAME`_txDataBits)
        {
            `$INSTANCE_NAME`_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            `$INSTANCE_NAME`_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            `$INSTANCE_NAME`_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (`$INSTANCE_NAME`_ONE_BYTE_WIDTH == `$INSTANCE_NAME`_txDataBits)
        {
            value = (uint32) `$INSTANCE_NAME`_txBuffer[idx];
        }
        else
        {
            value  = (uint32) `$INSTANCE_NAME`_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) `$INSTANCE_NAME`_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
