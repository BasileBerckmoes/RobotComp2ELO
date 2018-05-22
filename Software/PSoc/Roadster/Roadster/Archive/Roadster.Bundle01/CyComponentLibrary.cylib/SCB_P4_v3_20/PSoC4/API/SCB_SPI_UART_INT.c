/***************************************************************************//**
* \file `$INSTANCE_NAME`_SPI_UART_INT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_SPI_UART_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_SPI_UART_ISR)
{
#if (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

#if (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef `$INSTANCE_NAME`_SPI_UART_ISR_ENTRY_CALLBACK
    `$INSTANCE_NAME`_SPI_UART_ISR_EntryCallback();
#endif /* `$INSTANCE_NAME`_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != `$INSTANCE_NAME`_customIntrHandler)
    {
        `$INSTANCE_NAME`_customIntrHandler();
    }

    `$Cond`if(`$INSTANCE_NAME`_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
    }
    `$EndCond`

    `$Cond`if (`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
    {
        if (`$INSTANCE_NAME`_CHECK_INTR_RX_MASKED(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (`$INSTANCE_NAME`_rxBufferHead + 1u);

                /* Adjust local head index */
                if (`$INSTANCE_NAME`_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == `$INSTANCE_NAME`_rxBufferTail)
                {
                    `$Cond`if (`$INSTANCE_NAME`_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        `$INSTANCE_NAME`_INTR_RX_MASK_REG &= ~`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    `$Cond`else
                    {
                        /* Overflow: through away received data element */
                        (void) `$INSTANCE_NAME`_RX_FIFO_RD_REG;
                        `$INSTANCE_NAME`_rxBufferOverflow = (uint8) `$INSTANCE_NAME`_INTR_RX_OVERFLOW;
                    }
                    `$EndCond`
                }
                else
                {
                    /* Store received data */
                    `$INSTANCE_NAME`_PutWordInRxBuffer(locHead, `$INSTANCE_NAME`_RX_FIFO_RD_REG);

                    /* Move head index */
                    `$INSTANCE_NAME`_rxBufferHead = locHead;
                }
            }
            while(0u != `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES);

            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
        }
    }
    `$EndCond`


    `$Cond`if (`$INSTANCE_NAME`_CHECK_TX_SW_BUFFER)
    {
        if (`$INSTANCE_NAME`_CHECK_INTR_TX_MASKED(`$INSTANCE_NAME`_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (`$INSTANCE_NAME`_txBufferHead != `$INSTANCE_NAME`_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (`$INSTANCE_NAME`_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (`$INSTANCE_NAME`_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    `$INSTANCE_NAME`_TX_FIFO_WR_REG = `$INSTANCE_NAME`_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    `$INSTANCE_NAME`_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    `$INSTANCE_NAME`_DISABLE_INTR_TX(`$INSTANCE_NAME`_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (`$INSTANCE_NAME`_SPI_UART_FIFO_SIZE != `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES);

            `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_NOT_FULL);
        }
    }
    `$EndCond`

#ifdef `$INSTANCE_NAME`_SPI_UART_ISR_EXIT_CALLBACK
    `$INSTANCE_NAME`_SPI_UART_ISR_ExitCallback();
#endif /* `$INSTANCE_NAME`_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
