/***************************************************************************//**
* \file `$INSTANCE_NAME`_BOOT.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_`$INSTANCE_NAME`_H)
#define CY_SCB_BOOT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_PVT.h"

#if (`$INSTANCE_NAME`_SCB_MODE_I2C_INC)
    #include "`$INSTANCE_NAME`_I2C.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_INC) */

#if (`$INSTANCE_NAME`_SCB_MODE_EZI2C_INC)
    #include "`$INSTANCE_NAME`_EZI2C.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_EZI2C_INC) */

#if (`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC)
    #include "`$INSTANCE_NAME`_SPI_UART.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define `$INSTANCE_NAME`_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (`$INSTANCE_NAME`_SCB_MODE_I2C_INC)
    #define `$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED     (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED && \
                                                            (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             `$INSTANCE_NAME`_I2C_SLAVE_CONST))
#else
     #define `$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (`$INSTANCE_NAME`_SCB_MODE_EZI2C_INC)
    #define `$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED   (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED && \
                                                         `$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define `$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (`$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (`$INSTANCE_NAME`_SCB_MODE_SPI_INC)
    #define `$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED     (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED && \
                                                            (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             `$INSTANCE_NAME`_SPI_SLAVE_CONST))
#else
        #define `$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (`$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (`$INSTANCE_NAME`_SCB_MODE_UART_INC)
       #define `$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED    (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED && \
                                                            (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (`$INSTANCE_NAME`_UART_RX_DIRECTION && \
                                                              `$INSTANCE_NAME`_UART_TX_DIRECTION)))
#else
     #define `$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (`$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define `$INSTANCE_NAME`_BTLDR_COMM_MODE_ENABLED    (`$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED   || \
                                                     `$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED   || \
                                                     `$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED || \
                                                     `$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void `$INSTANCE_NAME`_I2CCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_I2CCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_I2CCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
        #define `$INSTANCE_NAME`_CyBtldrCommStart   `$INSTANCE_NAME`_I2CCyBtldrCommStart
        #define `$INSTANCE_NAME`_CyBtldrCommStop    `$INSTANCE_NAME`_I2CCyBtldrCommStop
        #define `$INSTANCE_NAME`_CyBtldrCommReset   `$INSTANCE_NAME`_I2CCyBtldrCommReset
        #define `$INSTANCE_NAME`_CyBtldrCommRead    `$INSTANCE_NAME`_I2CCyBtldrCommRead
        #define `$INSTANCE_NAME`_CyBtldrCommWrite   `$INSTANCE_NAME`_I2CCyBtldrCommWrite
    #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void `$INSTANCE_NAME`_EzI2CCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_EzI2CCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_EzI2CCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
        #define `$INSTANCE_NAME`_CyBtldrCommStart   `$INSTANCE_NAME`_EzI2CCyBtldrCommStart
        #define `$INSTANCE_NAME`_CyBtldrCommStop    `$INSTANCE_NAME`_EzI2CCyBtldrCommStop
        #define `$INSTANCE_NAME`_CyBtldrCommReset   `$INSTANCE_NAME`_EzI2CCyBtldrCommReset
        #define `$INSTANCE_NAME`_CyBtldrCommRead    `$INSTANCE_NAME`_EzI2CCyBtldrCommRead
        #define `$INSTANCE_NAME`_CyBtldrCommWrite   `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite
    #endif /* (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void `$INSTANCE_NAME`_SpiCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_SpiCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_SpiCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
        #define `$INSTANCE_NAME`_CyBtldrCommStart   `$INSTANCE_NAME`_SpiCyBtldrCommStart
        #define `$INSTANCE_NAME`_CyBtldrCommStop    `$INSTANCE_NAME`_SpiCyBtldrCommStop
        #define `$INSTANCE_NAME`_CyBtldrCommReset   `$INSTANCE_NAME`_SpiCyBtldrCommReset
        #define `$INSTANCE_NAME`_CyBtldrCommRead    `$INSTANCE_NAME`_SpiCyBtldrCommRead
        #define `$INSTANCE_NAME`_CyBtldrCommWrite   `$INSTANCE_NAME`_SpiCyBtldrCommWrite
    #endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void `$INSTANCE_NAME`_UartCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_UartCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_UartCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
        #define `$INSTANCE_NAME`_CyBtldrCommStart   `$INSTANCE_NAME`_UartCyBtldrCommStart
        #define `$INSTANCE_NAME`_CyBtldrCommStop    `$INSTANCE_NAME`_UartCyBtldrCommStop
        #define `$INSTANCE_NAME`_CyBtldrCommReset   `$INSTANCE_NAME`_UartCyBtldrCommReset
        #define `$INSTANCE_NAME`_CyBtldrCommRead    `$INSTANCE_NAME`_UartCyBtldrCommRead
        #define `$INSTANCE_NAME`_CyBtldrCommWrite   `$INSTANCE_NAME`_UartCyBtldrCommWrite
    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED)
    #if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void `$INSTANCE_NAME`_CyBtldrCommStart(void);
        void `$INSTANCE_NAME`_CyBtldrCommStop (void);
        void `$INSTANCE_NAME`_CyBtldrCommReset(void);
        cystatus `$INSTANCE_NAME`_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`)
        #define CyBtldrCommStart    `$INSTANCE_NAME`_CyBtldrCommStart
        #define CyBtldrCommStop     `$INSTANCE_NAME`_CyBtldrCommStop
        #define CyBtldrCommReset    `$INSTANCE_NAME`_CyBtldrCommReset
        #define CyBtldrCommWrite    `$INSTANCE_NAME`_CyBtldrCommWrite
        #define CyBtldrCommRead     `$INSTANCE_NAME`_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define `$INSTANCE_NAME`_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define `$INSTANCE_NAME`_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define `$INSTANCE_NAME`_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define `$INSTANCE_NAME`_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef `$INSTANCE_NAME`_SPI_BYTE_TO_BYTE
    #define `$INSTANCE_NAME`_SPI_BYTE_TO_BYTE   (`$SpiByteToByte`u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef `$INSTANCE_NAME`_UART_BYTE_TO_BYTE
    #define `$INSTANCE_NAME`_UART_BYTE_TO_BYTE  (`$UartByteToByte`u)
#endif /* `$INSTANCE_NAME`_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
