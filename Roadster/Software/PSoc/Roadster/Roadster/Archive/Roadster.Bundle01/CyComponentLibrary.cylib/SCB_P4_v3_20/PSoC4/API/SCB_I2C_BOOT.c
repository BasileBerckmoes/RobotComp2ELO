/***************************************************************************//**
* \file `$INSTANCE_NAME`_I2C_BOOT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component I2C mode.
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
#include "`$INSTANCE_NAME`_I2C_PVT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED)

/***************************************
*    Private I/O Component Vars
***************************************/

/* Writes to this buffer */
static uint8 `$INSTANCE_NAME`_slReadBuf[`$INSTANCE_NAME`_I2C_BTLDR_SIZEOF_READ_BUFFER];

/* Reads from this buffer */
static uint8 `$INSTANCE_NAME`_slWriteBuf[`$INSTANCE_NAME`_I2C_BTLDR_SIZEOF_WRITE_BUFFER];

/* Flag to release buffer to be read */
static uint32 `$INSTANCE_NAME`_applyBuffer;


/***************************************
*    Private Function Prototypes
***************************************/

static void `$INSTANCE_NAME`_I2CResposeInsert(void);


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CCyBtldrCommStart
****************************************************************************//**
*
*  Starts the I2C component and enables its interrupt.
*  Every incoming I2C write transaction is treated as a command for the
*  bootloader.
*  Every incoming I2C read transaction returns 0xFF until the bootloader
*  provides a response to the executed command.
*
* \globalvars
*  `$INSTANCE_NAME`_applyBuffer - the flag to release the buffer with a response
*  to be read by the host.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CCyBtldrCommStart(void)
{
    `$INSTANCE_NAME`_I2CSlaveInitWriteBuf(`$INSTANCE_NAME`_slWriteBuf, `$INSTANCE_NAME`_I2C_BTLDR_SIZEOF_WRITE_BUFFER);
    `$INSTANCE_NAME`_I2CSlaveInitReadBuf (`$INSTANCE_NAME`_slReadBuf, 0u);

    `$INSTANCE_NAME`_SetCustomInterruptHandler(&`$INSTANCE_NAME`_I2CResposeInsert);
    `$INSTANCE_NAME`_applyBuffer = 0u;

    `$INSTANCE_NAME`_Start();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CCyBtldrCommStop
****************************************************************************//**
*
*  Disables the I2C component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CCyBtldrCommStop(void)
{
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CCyBtldrCommReset
****************************************************************************//**
*
*  Resets read and write I2C buffers to the initial state and resets the slave
*  status.
*
* \globalvars
*  `$INSTANCE_NAME`_slRdBufSize - used to store slave read buffer size.
*  `$INSTANCE_NAME`_slRdBufIndex - used to store the current index within the
*  slave read buffer.
*  `$INSTANCE_NAME`_slWrBufIndex - used to store current index within slave
*  write buffer.
*  `$INSTANCE_NAME`_slStatus  - used to store current status of I2C slave.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CCyBtldrCommReset(void)
{
    /* Make read buffer full */
    `$INSTANCE_NAME`_slRdBufSize = 0u;

    /* Reset write buffer and Read buffer */
    `$INSTANCE_NAME`_slRdBufIndex = 0u;
    `$INSTANCE_NAME`_slWrBufIndex = 0u;

    /* Clear read and write status */
    `$INSTANCE_NAME`_slStatus = 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CCyBtldrCommRead
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
*  \return
*   Returns CYRET_SUCCESS if no problem was encountered or returns the value
*   that best describes the problem. For more information refer to the
*   "Return Codes" section of the System Reference Guide.
*
* \globalvars
*  `$INSTANCE_NAME`_slStatus  - used to store current status of I2C slave.
*  `$INSTANCE_NAME`_slWriteBuf - used to store received command.
*  `$INSTANCE_NAME`_slWrBufIndex - used to store current index within slave
*  write buffer.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_I2CCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 timeoutMs;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS check to 1mS checks */

        while (0u != timeoutMs)
        {
            /* Check if host complete write */
            if (0u != (`$INSTANCE_NAME`_I2C_SSTAT_WR_CMPLT & `$INSTANCE_NAME`_slStatus))
            {
                /* Copy number of written bytes */
                *count = (uint16) `$INSTANCE_NAME`_slWrBufIndex;

                /* Clear slave status and write index */
                `$INSTANCE_NAME`_slStatus = 0u;
                `$INSTANCE_NAME`_slWrBufIndex = 0u;

                /* Copy command into bootloader buffer */
                (void) memcpy((void *) pData, (const void *) `$INSTANCE_NAME`_slWriteBuf,
                                              `$INSTANCE_NAME`_BYTES_TO_COPY(*count, size));

                status = CYRET_SUCCESS;
                break;
            }

            CyDelay(`$INSTANCE_NAME`_WAIT_1_MS);
            --timeoutMs;
        }
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CCyBtldrCommWrite
****************************************************************************//**
*
*  Allows the caller to write data to the bootloader host (the host reads the
*  data). The function does not use timeout and returns after data has been
*  copied into the slave read buffer. This data is available to be read by the
*  bootloader host until following host data write.
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
* \globalvars
*  `$INSTANCE_NAME`_applyBuffer - the flag to release the buffer with
*  to be read by the host.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        /* Copy response into read buffer */
        *count = size;
        (void) memcpy((void *) `$INSTANCE_NAME`_slReadBuf, (const void *) pData, (uint32) size);

        /* Read buffer is ready to be released to host */
        `$INSTANCE_NAME`_applyBuffer = (uint32) size;

        if (0u != timeOut)
        {
            /* Suppress compiler warning */
        }

        status = CYRET_SUCCESS;
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CResposeInsert
****************************************************************************//**
*
*  Releases the read buffer to be read when a response is copied to the buffer
*  and a new read transaction starts.
*  Closes the read buffer when write transaction is started.
*
* \globalvars
*  `$INSTANCE_NAME`_applyBuffer - the flag to release the buffer with a response
*  to be read by the host.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_I2CResposeInsert(void)
{
    if (`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH))
    {
        if (`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_S_READ))
        {
            /* Address phase, host reads: release read buffer */
            if (0u != `$INSTANCE_NAME`_applyBuffer)
            {
                `$INSTANCE_NAME`_slRdBufSize  = `$INSTANCE_NAME`_applyBuffer;
                `$INSTANCE_NAME`_slRdBufIndex = 0u;
                `$INSTANCE_NAME`_applyBuffer  = 0u;
            }
        }
        else
        {
            /* Address phase, host writes: close read buffer */
            if (`$INSTANCE_NAME`_slRdBufIndex != `$INSTANCE_NAME`_slRdBufSize)
            {
                `$INSTANCE_NAME`_slRdBufIndex = `$INSTANCE_NAME`_slRdBufSize;
            }
        }
    }
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
