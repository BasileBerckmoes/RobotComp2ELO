/***************************************************************************//**
* \file `$INSTANCE_NAME`_SPI_BOOT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component SPI mode.
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

#include "`$INSTANCE_NAME`_BOOT.h"
#include "`$INSTANCE_NAME`_SPI_UART.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiCyBtldrCommStart
****************************************************************************//**
*
*  Starts the SPI component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiCyBtldrCommStart(void)
{
    `$INSTANCE_NAME`_Start();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiCyBtldrCommStop
****************************************************************************//**
*
*  Disables the SPI component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiCyBtldrCommStop(void)
{
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiCyBtldrCommReset
****************************************************************************//**
*
*  Resets the receive and transmit communication buffers.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiCyBtldrCommReset(void)
{
    /* Clear RX and TX buffers */
    `$INSTANCE_NAME`_SpiUartClearRxBuffer();
    `$INSTANCE_NAME`_SpiUartClearTxBuffer();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiCyBtldrCommRead
****************************************************************************//**
*
*  Allows the caller to read data from the bootloader host (the host writes the
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
*  \param pData: Pointer to storage for the block of data to be read from the
*   bootloader host
*  \param size: Number of bytes to be read.
*  \param count: Pointer to the variable to write the number of bytes actually
*   read.
*  \param timeOut: Number of units in 10 ms to wait before returning
*   because of a timeout.
*
* \return
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem. For more information refer to the
*  "Return Codes" section of the System Reference Guide.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SpiCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 byteCount;
    uint32 timeoutMs;
    uint32 i;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS check to 1mS checks */

        /* Wait with timeout 1mS for packet start */
        byteCount = 0u;
        do
        {
            /* Check packet start */
            if (0u != `$INSTANCE_NAME`_SpiUartGetRxBufferSize())
            {
                /* Wait for packet end */
                do
                {
                    byteCount = `$INSTANCE_NAME`_SpiUartGetRxBufferSize();
                    CyDelayUs(`$INSTANCE_NAME`_SPI_BYTE_TO_BYTE);
                }
                while (byteCount != `$INSTANCE_NAME`_SpiUartGetRxBufferSize());

                /* Disable data reception into RX FIFO */
                `$INSTANCE_NAME`_RX_FIFO_CTRL_REG |= `$INSTANCE_NAME`_RX_FIFO_CTRL_FREEZE;

                byteCount = `$INSTANCE_NAME`_BYTES_TO_COPY(byteCount, size);
                *count = (uint16) byteCount;
                status = CYRET_SUCCESS;

                break;
            }

            CyDelay(`$INSTANCE_NAME`_WAIT_1_MS);
            --timeoutMs;
        }
        while (0u != timeoutMs);

        /* Get data from the RX buffer into bootloader buffer */
        for (i = 0u; i < byteCount; ++i)
        {
            pData[i] = (uint8) `$INSTANCE_NAME`_SpiUartReadRxData();
        }
    }

    return (status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiCyBtldrCommWrite
****************************************************************************//**
*
*  Allows the caller to read data from the bootloader host (the host writes the
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
*  \param pData: Pointer to the block of data to be written to the bootloader
*   host.
*  \param size: Number of bytes to be written.
*  \param count: Pointer to the variable to write the number of bytes actually
*   written.
*  \param timeOut: Number of units in 10 ms to wait before returning
*   because of a timeout.
*
*  \return
*   Returns CYRET_SUCCESS if no problem was encountered or returns the value
*   that best describes the problem. For more information refer to the
*   "Return Codes" section of the System Reference Guide.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 timeoutMs;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS check to 1mS checks */

        /* Put data into TX buffer */
        `$INSTANCE_NAME`_SpiUartPutArray(pData, (uint32) size);

        /* Wait with timeout 1mS for packet end */
        do
        {
            /* Check for packet end */
            if ((0u == `$INSTANCE_NAME`_SpiUartGetTxBufferSize()) &&
                (0u == (`$INSTANCE_NAME`_SPI_STATUS_REG & `$INSTANCE_NAME`_SPI_STATUS_BUS_BUSY)) &&
                (0u == (`$INSTANCE_NAME`_TX_FIFO_STATUS_REG & `$INSTANCE_NAME`_TX_FIFO_SR_VALID)))
            {
                *count = size;
                status = CYRET_SUCCESS;

                break;
            }

            CyDelay(`$INSTANCE_NAME`_WAIT_1_MS);
            --timeoutMs;
        }
        while (0u != timeoutMs);

        /* Enable data reception into RX FIFO */
        `$INSTANCE_NAME`_SpiUartClearRxBuffer();
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_RX_FIFO_CTRL_FREEZE;
    }

    return (status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
