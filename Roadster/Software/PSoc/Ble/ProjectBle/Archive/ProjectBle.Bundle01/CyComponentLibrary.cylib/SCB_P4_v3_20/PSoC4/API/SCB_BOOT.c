/***************************************************************************//**
* \file `$INSTANCE_NAME`_BOOT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
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

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED) && \
                                (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStart
****************************************************************************//**
*
*  Starts `$INSTANCE_NAME` component. After this function call the component is 
*  ready for communication.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStart(void)
{
    if (`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_I2CCyBtldrCommStart();
    }
    else if (`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_EzI2CCyBtldrCommStart();
    }
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    else if (`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_SpiCyBtldrCommStart();
    }
    else if (`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_UartCyBtldrCommStart();
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStop
****************************************************************************//**
*
*  Stops `$INSTANCE_NAME` component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStop(void)
{
    if (`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_I2CCyBtldrCommStop();
    }
    else if (`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_EzI2CCyBtldrCommStop();
    }
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    else if (`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_SpiCyBtldrCommStop();
    }
    else if (`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_UartCyBtldrCommStop();
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommReset
****************************************************************************//**
*
*  Clears `$INSTANCE_NAME` component buffers.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommReset(void)
{
    if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_I2CCyBtldrCommReset();
    }
    else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_EzI2CCyBtldrCommReset();
    }
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_SpiCyBtldrCommReset();
    }
    else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_UartCyBtldrCommReset();
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommRead
****************************************************************************//**
*
*  Allows the caller to read data from the bootloader host (the host writes the 
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
*  \param pData: Pointer to storage for the block of data to be read from the
*   bootloader host.
*  \param size: Number of bytes to be read.
*  \param count: Pointer to the variable to write the number of bytes actually
*   read.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
* \return
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommWrite
****************************************************************************//**
*
*  Allows the caller to write data to the bootloader host (the host reads the 
*  data). The function does not use timeout and returns after data has been copied
*  into the slave read buffer. This data available to be read by the bootloader
*  host until following host data write.
*
*  \param pData: Pointer to the block of data to be written to the bootloader host.
*  \param size: Number of bytes to be written.
*  \param count: Pointer to the variable to write the number of bytes actually
*   written.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
    {
        status = `$INSTANCE_NAME`_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
