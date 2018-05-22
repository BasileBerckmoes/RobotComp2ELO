/***************************************************************************//**
* \file `$INSTANCE_NAME`.c       
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* This file provides the source code to the API for the SerialNVRAM 
* Component.
* 
********************************************************************************
* Copyright (2017), Cypress Semiconductor Corporation.
******************************************************************************** 
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
* CYPRESS PROVIDES THIS SOFTWARE "AS IS" AND MAKES NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED 
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS 
* FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

/* Internal constants */
#define `$INSTANCE_NAME`_DUMMY_BYTE                           (0X22U)

CY_INLINE static void `$INSTANCE_NAME`_SetDefaultPins(void);

#if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSelectDevice(uint8 nvramId);
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiDeSelectDevice(uint8 nvramId);
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiTxBusyCheck(void);
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiRxBufferCheck(void);
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSetWriteEnable(uint8 nvramId);
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiBufferWrite(const uint8 dataWritePtr[], 
                                                                   uint32 totalDataCount);
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiBufferRead(uint8 dataReadPtr[], 
                                                                  uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiRtcRegRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSerialNoWrite(uint8 nvramId,
                                                                               const uint8 *dataPtr);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSerialNoRead(uint8 nvramId,
                                                                              uint8 *dataPtr);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiDevIdRead(uint8 nvramId, 
                                                                           uint8 *dataPtr, 
                                                                           uint32 iDLength);
#endif

#if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
    static uint32 `$INSTANCE_NAME`_I2cDataWrite(const uint8 dataWritePtr[], uint32 totalDataCount);
    static uint32 `$INSTANCE_NAME`_I2cDataRead(uint8 dataReadPtr[], uint32 totalDataCount);
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2CSendStop(uint32 i2cStatus);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cRtcRegRead(uint8 nvramId, 
                                                                           uint32 addr, 
                                                                           uint8 *dataReadPtr, 
                                                                           uint32 totalDataCount);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cSerialNoWrite(uint8 nvramId,
                                                                               const uint8 *dataPtr);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cSerialNoRead(uint8 nvramId,
                                                                              uint8 *dataPtr);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cUniqueSleep(uint8 nvramId);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cUniqueSerialNoRead(uint8 nvramId,
                                                                                    uint8 *dataPtr);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cUniqueDevIdRead(uint8 nvramId,
                                                                                 uint8 *dataPtr,
                                                                                 uint32 iDLength);
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cDevIdRead(uint8 nvramId, 
                                                                           uint8 *dataPtr, 
                                                                           uint32 iDLength);
#endif

/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME`  component
*  has been initialized. The variable is initialized to 0 and set to 1 the first
*  time `$INSTANCE_NAME`_Start() is called.
*  This allows the component to restart without reinitialization after the first 
*  call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  `$INSTANCE_NAME`_Init() function can be called before the 
*  `$INSTANCE_NAME`_Start() function.
*/
uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_SetDefaultPins
****************************************************************************//**
*
*  Sets the control pins to the default state.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SetDefaultPins(void) 
{   
    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        /* Disable the chip */
        `$INSTANCE_NAME`_CS_0_OFF;
        #if (`$INSTANCE_NAME`_CS1 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
            `$INSTANCE_NAME`_CS_1_OFF;
            #if (`$INSTANCE_NAME`_CS2 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                `$INSTANCE_NAME`_CS_2_OFF;
            #endif
                #if (`$INSTANCE_NAME`_CS3 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                    `$INSTANCE_NAME`_CS_3_OFF;
                #endif
        #endif
        #if (1 == `$INSTANCE_NAME`_ENABLE_HOLD)
            `$INSTANCE_NAME`_SetHold(`$INSTANCE_NAME`_HIGH);
        #endif
        #if (1 == `$INSTANCE_NAME`_ENABLE_WRITE_PROTECTION)
            `$INSTANCE_NAME`_SetWp(`$INSTANCE_NAME`_HIGH);
        #endif
    #endif

    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        #if (1 == `$INSTANCE_NAME`_ENABLE_WRITE_PROTECTION)
            `$INSTANCE_NAME`_SetWp(`$INSTANCE_NAME`_LOW);
        #endif
    #endif
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_Init
****************************************************************************//**
*
*  The initialization routine for the NVRAM component. 
*   Initializes the SPI/I2C block, CS, WP, and Hold configurations.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) 
{   
    /* Start the communication interface */
    `$INSTANCE_NAME`_InterfaceStart();
    
    /* Init the pins (CS, HOLD, WP) */
    `$INSTANCE_NAME`_SetDefaultPins();
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  The start function, initializes the SerialNVRAM with the default values.
*
* \globalvars
*   `$INSTANCE_NAME`_initVar: The global variable, defines if the component  
*                             will be initialized to the schematic state. 
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) 
{
    if(0u == `$INSTANCE_NAME`_initVar)      
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;      
    }
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Disables the Serial NVRAM component but does not stop the
* Master component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) 
{
    `$INSTANCE_NAME`_SetDefaultPins();
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_GetStatus
****************************************************************************//**
*
* Returns the external device ready/busy status after the initiated 
* transfer is complete.
*
*  \note The function always returns `$INSTANCE_NAME`_SUCCESS for F-RAM devices.
*
*  \param nvramId: CS for SPI, the slave address for I2C. 
* The nvramId parameter for I2C devices have the following I2C slave 
* address:  0 1 0 1 0 A2 A1 A0. The three LSB bits are configurable 
* slave address inputs A2, A1, A0. Some I2C NVRAMs use three LSB bits 
* as memory page select to address higher density than addressable through 
* dedicated address byte (s) (one or two bytes) sent after the I2C command byte. 
* For example 4Kb and 16Kb I2C F-RAMs use A0 and A2, A1,A0 bits respectively 
* as page select bits followed by 1-byte memory address. 
* Similarly, 1Mb device use A0 as page select address bit followed by 
* 2-byte memory address.
* The I2C NVRAM devices internally ignore the page select bit setting and 
* always send an ACK during the command cycle. However, page select bits are 
* internally used to set the memory page address for the subsequent access. 
* For example: the CY14C101I device has Pin A2 connected to the high level 
* and Pin A1 connected to the ground. This corresponds to valid 
* nvramId = 0xA4 or 0xA5 with lower or upper page address set.
*
*  \return 
*  status:
*  * `$INSTANCE_NAME`_SUCCESS - data is sent/received and the component is ready 
*     to send/receive new data
*  * `$INSTANCE_NAME`_DEVICE_BUSY - the component is sending/receiving previous
*      data or the device error.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_GetStatus(uint8 nvramId) 
{
    `$INSTANCE_NAME`_status status;

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        uint8 dataByte;

        status = `$INSTANCE_NAME`_StatusRegRead(nvramId, &dataByte);
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            if (`$INSTANCE_NAME`_SPI_NOT_RDY != (dataByte & `$INSTANCE_NAME`_SPI_NOT_RDY))
            {
                status = `$INSTANCE_NAME`_SUCCESS;
            }
            else
            {
                status = `$INSTANCE_NAME`_DEVICE_BUSY;
            }
        }
        else
        {
            status = `$INSTANCE_NAME`_DEVICE_BUSY;
        }    
        
    #endif

    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        uint32 dataByte;
    
        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK;
    
        /* Set the I2C Memory selection mask */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_MEM_MASK;
    
        /*  Send the Start condition and slave ID for Write */
        dataByte = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                         `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                         `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);

        /* Send Stop */
        (void)`$masterInterface`_I2CMasterSendStop(`$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);

        if (`$masterInterface`_I2C_MSTR_ERR_LB_NAK != dataByte)
        {
            status = `$INSTANCE_NAME`_SUCCESS;
        }
        else
        {
            status = `$INSTANCE_NAME`_DEVICE_BUSY;
        }   
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_MemoryWrite
****************************************************************************//**
*
* Writes the totalDataCount number of data into NVRAM.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*
*  \param addr: The 1/2/3-byte NVRAM address for Write.
*  \param *dataWritePtr: The pointer to an array of data bytes to be written.
*  \param totalDataCount: The number of data bytes to be written.
*
* \return
* Error status:
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_MemoryWrite(uint8 nvramId, 
                                                     uint32 addr, 
                                                     const uint8 *dataWritePtr, 
                                                     uint32 totalDataCount) 
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    CYASSERT(dataWritePtr); /* dataWritePtr cannot be NULL */

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiMemoryWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_I2cMemoryWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_MemoryRead
****************************************************************************//**
*
* Reads the totalDataCount number of data from NVRAM. 
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*  \param addr: The 1/2/3-byte NVRAM address for Write.
*  \param *dataReadPtr: The pointer to an array for storing data bytes.
*  \param totalDataCount: The number of data bytes to be read.
*
* \return
* Error status:
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_MemoryRead(uint8 nvramId, 
                                                    uint32 addr, 
                                                    uint8 *dataReadPtr, 
                                                    uint32 totalDataCount)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiMemoryRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_I2cMemoryRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif

    return status;
}


#if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_CurrentMemoryRead
    ****************************************************************************//**
    *
    * Reads totalDataCount number of the data current address of I2C NVRAM. 
    *
    *  \param nvramId: The slave address for I2C.
    *  The nvramId parameter for I2C devices has the following format: 
    *  0 0 0 0 0 A2 A1 A0. The R/W bit is not used.
    *  Three LSB bits define the slave address inputs A2, A1 or A2, A1, and A0 bits
    *  for the I2C devices that have A2, A1, and A0 bits for the page select.  
    *  Bit A0 is the page select bit and it equals to 1 for address from 0x10000.
    *  For example: the CY14C101I device has Pin A2 connected to the high level 
    *  and Pin A1 connected to the ground. This corresponds to 
    *  valid 0x04 for reading data with the address below 0x10000 and
    *  nvramId = 0x05 for reading data with the address from 0x10000.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A Communication error.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_CurrentMemoryRead(uint8 nvramId, 
                                                               uint8 *dataReadPtr, 
                                                               uint32 totalDataCount)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
 
        CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK;
        
        /* Set the I2C Memory selection mask */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_MEM_MASK;
        
        /* Send the Start condition and slave ID for Read */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_READ_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);

        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of the totalDataCount bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataReadPtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);

        return status;
    }
#endif


#if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_MemoryFastReadOpcode
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from SPI NVRAM using
    * the Fast Read command.
    *
    *  \param nvramId: CS for SPI
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status:
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
    *     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_MemoryFastReadOpcode(uint8 nvramId, 
                                                                  uint32 addr, 
                                                                  uint8 *dataReadPtr, 
                                                                  uint32 totalDataCount)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);
        
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Send the F-RAM Fast Read command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_SRAM_FAST_READ_CMD);   
            
            /* For densities greater than or equal to 1MBit, send a 3-byte address */
            #if (`$INSTANCE_NAME`_DENSITY_1_MBIT <= `$INSTANCE_NAME`_DENSITY)
                `$masterInterface`_SpiUartWriteTxData((addr & `$INSTANCE_NAME`_MSB_ADDR_MASK)>>`$INSTANCE_NAME`_MSB_ADDR_SHIFTBITS);
            #endif
        
            /* Send a 2-byte address */
            `$masterInterface`_SpiUartWriteTxData((addr & `$INSTANCE_NAME`_ISB_ADDR_MASK)>>`$INSTANCE_NAME`_ISB_ADDR_SHIFTBITS);
            `$masterInterface`_SpiUartWriteTxData(addr);
        
            /* Wait for the transmission to complete */
            status = `$INSTANCE_NAME`_SpiTxBusyCheck();
            
            if (`$INSTANCE_NAME`_SUCCESS == status)
            {
                /* Send the dummy byte to start receiving data */
                `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_DUMMY_BYTE);
                
                /* Read the data bytes */
                status = `$INSTANCE_NAME`_SpiBufferRead(dataReadPtr, totalDataCount);
            }
            
            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }

        
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_StatusRegWrite
    ****************************************************************************//**
    *
    * Writes the NVRAM Status register.
    *
    *  \param nvramId: CS for SPI.
    *  \param dataByte: The 1-byte status register data to be written.
    *
    * \return
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
    *     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_StatusRegWrite(uint8 nvramId, uint8 dataByte)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Send the WREN command */
        status = `$INSTANCE_NAME`_SpiSetWriteEnable(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)`$INSTANCE_NAME`_SpiSelectDevice(nvramId);

            /* Send Write Status Register command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_WRSR_CMD);

            /* Send the status register data */
            `$masterInterface`_SpiUartWriteTxData((uint32)dataByte);
            
            /* Wait for the transmission to complete */
            status = `$INSTANCE_NAME`_SpiTxBusyCheck();

            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_StatusRegRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Status register. 
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataByte: The pointer to the holding status register value.
    *
    * \return
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
    *     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_StatusRegRead(uint8 nvramId, uint8 *dataByte)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Clear the receive buffer */
        `$masterInterface`_SpiUartClearRxBuffer();

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Send the status register Read command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_RDSR_CMD);

            /* Send the dummy byte to receive data */
            `$masterInterface`_SpiUartWriteTxData(0x00U);

            /* Wait for the transmission to complete */
            status = `$INSTANCE_NAME`_SpiTxBusyCheck();
        
            if (`$INSTANCE_NAME`_SUCCESS == status)
            {
                /* Ensure data is received in the receive buffer */
                status = `$INSTANCE_NAME`_SpiRxBufferCheck();
                
                /* Read the buffer twice because the second byte received 
                   is the status reg data 
                */
                *dataByte = (uint8)`$masterInterface`_SpiUartReadRxData(); 
                *dataByte = (uint8)`$masterInterface`_SpiUartReadRxData();
            }

            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }

    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_WriteProcessorCompanion
    ****************************************************************************//**
    *
    * Writes the SPI F-RAM processor companion register. 
    * This function is applicable for the devices which support WRPC and RDPC. 
    * Refer to the device datasheet for details.
    *
    *  \note To write the RTC register of the companion device, this function 
    *  should set the W bit of the RTC/Alarm Control register
    *  (`$INSTANCE_NAME`_COMPANION_RTC_ALARM_CTL) and then write the RTC register.
    *  For example, the following code updates the Day register with value = 4:
    *  `$INSTANCE_NAME`_status status;
    *  uint8 writeCommand = 2u;
    *  uint8 day = 4u;
    *  status = `$INSTANCE_NAME`_WriteProcessorCompanion(`$INSTANCE_NAME`_CS0,
    *                             `$INSTANCE_NAME`_COMPANION_RTC_ALARM_CTL, 
    *                             &writeCommand, 1u);
    *  status = `$INSTANCE_NAME`_WriteProcessorCompanion(`$INSTANCE_NAME`_CS0,
    *                             `$INSTANCE_NAME`_COMPANION_DAY_01_07, 
    *                             &day, 1u);
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 8-bit F-RAM Processor companion
    *  register address for Write.
    *  \param *dataPtr: The pointer to an array of data to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_WriteProcessorCompanion(uint8 nvramId,
                                                                     uint32 addr,
                                                                     const uint8 *dataPtr,
                                                                     uint32 totalDataCount)
    {
        `$INSTANCE_NAME`_status status;

        /* Send the WREN command */
        status = `$INSTANCE_NAME`_SpiSetWriteEnable(nvramId);
        
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)`$INSTANCE_NAME`_SpiSelectDevice(nvramId);

            /* Send the processor companion register Write command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_WRPC_CMD);
            
            /* Send 1 register address byte */
            `$masterInterface`_SpiUartWriteTxData(addr);
            
            /* Send the processor companion register */
            status = `$INSTANCE_NAME`_SpiBufferWrite(dataPtr, totalDataCount);

            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId); 
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_ReadProcessorCompanion
    ****************************************************************************//**
    *
    * Reads the SPI F-RAM processor companion register. 
    * This function is applicable for the devices which support WRPC and RDPC. 
    * Refer to the device datasheet for details.
    *
    *  \note To read the data from the RTC register of the companion device, 
    *  this function should set the R bit of the RTC/Alarm Control register
    *  (`$INSTANCE_NAME`_COMPANION_RTC_ALARM_CTL) and then read the RTC register.
    *  For example, the following code reads the Day register:
    *  `$INSTANCE_NAME`_status status;
    *  uint8 readCommand = 1u;
    *  uint8 day = 4u;
    *  status = `$INSTANCE_NAME`_WriteProcessorCompanion(`$INSTANCE_NAME`_CS0, 
    *                             `$INSTANCE_NAME`_COMPANION_RTC_ALARM_CTL, 
    *                             &readCommand, 1u);
    *  status = `$INSTANCE_NAME`_ReadProcessorCompanion(`$INSTANCE_NAME`_CS0, 
    *                             `$INSTANCE_NAME`_COMPANION_DAY_01_07,
    *                             &day, 1u);
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 8-bit F-RAM Processor companion
    *  register address for Read.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_ReadProcessorCompanion(uint8 nvramId,
                                                                    uint32 addr,
                                                                    uint8 *dataReadPtr,
                                                                    uint32 totalDataCount)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Send the F-RAM processor companion register Read command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_RDPC_CMD);   
        
            /* Send 1 address byte */
            `$masterInterface`_SpiUartWriteTxData(addr);
        
            /* Read the data bytes */
            status = `$INSTANCE_NAME`_SpiBufferRead(dataReadPtr, totalDataCount);
            
            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
#endif


#if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_MemCtrlRegWrite
    ****************************************************************************//**
    *
    * Writes to NVRAM Memory Control Register.    
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param dataByte: The 1-byte Memory Control register data to be written.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
    *     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_MemCtrlRegWrite(uint8 nvramId, uint8 dataByte)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_CR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId,
                                                       `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                       `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the Memory Control Register address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(`$INSTANCE_NAME`_MEM_CTR_REG_ADDR, 
                                                              `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
            if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
            {
               /* Send the data byte for Write */
               i2cStatus = `$masterInterface`_I2CMasterWriteByte((uint32)dataByte, 
                                                                 `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
            }
        }

        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus); 

        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_MemCtrlRegRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Memory Control Register content.  
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param *dataByte: The pointer for holding the Control register value.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_MemCtrlRegRead(uint8 nvramId, uint8 *dataByte)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_CR_MASK;

        /* Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Write the the Memory Control Register address to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(`$INSTANCE_NAME`_MEM_CTR_REG_ADDR, 
                                                              `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = `$masterInterface`_I2CMasterSendRestart((uint32)nvramId, 
                                                                `$masterInterface`_I2C_READ_XFER_MODE, 
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        /* Read the byte with NAK data */
        i2cStatus = `$masterInterface`_I2CMasterReadByte(`$masterInterface`_I2C_NAK_DATA, 
                                                         dataByte, 
                                                         `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus); 

        return status;
    }
#endif


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* Sends the NVRAM command for sleep.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*  The nvramId parameter for the FM24VN10 families has the following I2C slave
*  address format: 0 1 0 1 0 A2 A1 A16. 
*  Bits A2 and A1 are the slave address inputs. 
*  Bit A16 is the page select bit and it can have any value for this function. 
*  Four FM24VN10 devices can be connected to I2C bus with the following
*  nvramId parameter values:
*  * 0x50 - Both A2 and A1 pins are connected to the ground.
*  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
*  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
*  * 0x56 – Both A2 and A1 pins are connected to the high level.
*
* \return 
* Error status
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_Sleep(uint8 nvramId)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status =  `$INSTANCE_NAME`_NvCommand(nvramId, `$INSTANCE_NAME`_NVRAM_SLEEP_CMD);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        /* Check if the device is FM24V10 */
        if (`$INSTANCE_NAME`_I2C_FM24V10_SLAVE_ID == (`$INSTANCE_NAME`_I2C_FM24V10_SLAVE_ID & nvramId))
        {
            status = `$INSTANCE_NAME`_I2cUniqueSleep(nvramId);
        }
        else
        {
            status = `$INSTANCE_NAME`_I2cNvCommand(nvramId, `$INSTANCE_NAME`_NVRAM_SLEEP_CMD);
        }  
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_NvCommand
****************************************************************************//**
*
* Sends the NVRAM command. This is supported by nvSRAM only. 
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*  \param nvcmd: The 8-bit NVRAM command.
*
* \return 
* Error status
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_NvCommand(uint8 nvramId, uint8 nvcmd)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiNvCommand(nvramId, (uint32)nvcmd);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_I2cNvCommand(nvramId, (uint32)nvcmd);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_SerialNoWrite
****************************************************************************//**
*
* Writes the NVRAM Serial number. 
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*
*  \note This function is applicable for devices with a serial number in the 
*  Control registers map. 
*  The `$INSTANCE_NAME`_RtcRegWrite()/`$INSTANCE_NAME`_WriteProcessorCompanion() 
*  functions are used for devices with a serial number in the RTC / processor 
*  companion register map. For more detail, refer to the device datasheet.
*
*  \param *dataPtr: The pointer to an array of the serial number
*  data to be written.
*
* \return
* Error status
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_SerialNoWrite(uint8 nvramId, const uint8 *dataPtr)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    CYASSERT(dataPtr); /* dataPtr cannot be NULL */

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiSerialNoWrite(nvramId, dataPtr);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_I2cSerialNoWrite(nvramId, dataPtr);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_SerialNoRead
****************************************************************************//**
*
* Reads the NVRAM Serial number.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*  The nvramId parameter for the FM24VN10 families has the following
*  I2C slave address  format: 0 1 0 1 0 A2 A1 A16. 
*  Bits A2 and A1 are the slave address inputs. 
*  Bit A16 is the page select bit and it can have any value for this function. 
*  Four FM24VN10 devices can be connected to I2C bus with the following
*  nvramId parameter values:
*  * 0x50 - Both A2 and A1 pins are connected to the ground.
*  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
*  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
*  * 0x56 – Both A2 and A1 pins are connected to the high level.
*
*  \note This function is not applicable for devices with a serial number in 
*  RTC / processor companion register map.
*  The `$INSTANCE_NAME`_RtcRegRead()/`$INSTANCE_NAME`_ReadProcessorCompanion() 
*  functions are used for devices with a serial number in the RTC / processor 
*  companion register map. For more detail, refer to the device datasheet.
*
*  \param *dataPtr: The pointer to an array for storing serial number data.
*
* \return 
* Error status
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_SerialNoRead(uint8 nvramId, uint8 *dataPtr)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    CYASSERT(dataPtr); /* dataPtr cannot be NULL */

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiSerialNoRead(nvramId, dataPtr);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        /* Check if the device is FM24V10 */
        if (`$INSTANCE_NAME`_I2C_FM24V10_SLAVE_ID == (`$INSTANCE_NAME`_I2C_FM24V10_SLAVE_ID & nvramId))
        {
            status = `$INSTANCE_NAME`_I2cUniqueSerialNoRead(nvramId, dataPtr);
        }
        else
        {
            status = `$INSTANCE_NAME`_I2cSerialNoRead(nvramId, dataPtr);  
        }
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_DevIdRead
****************************************************************************//**
*
* Reads the NVRAM device ID. This is supported by nvSRAM and F-RAM above 128Kbit.
* A pre-defined ID length covers the following varying device's IDs across
* different product families: 
*  * CY14B101PA - The DevID size is 4 bytes
*  * FM25VN10   - The DevID size is 9 bytes
*  * CY15B104Q  - The DevID size is 9 bytes
*  * CY14B101I  - The DevID size is 4 bytes
*  * FM24VN10   - The DevID size is 3 bytes
*  * FM31L278   - The DevID size is 8 bytes
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*  The nvramId parameter for the FM24VN10 families has the I2C slave address  
*  following format: 0 1 0 1 0 A2 A1 A16. 
*  Bits A2 and A1 are the slave address inputs. 
*  Bit A16 is the page select bit and it can have any value for this function. 
*  Four FM24VN10 devices can be connected to I2C bus with the following
*  nvramId parameter values:
*  * 0x50 - Both A2 and A1 pins are connected to the ground.
*  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
*  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
*  * 0x56 – Both A2 and A1 pins are connected to the high level.

*  \param *dataPtr: The pointer to an array for storing the device ID.
*  \param IDLength: The four predefines for the ID length (3ByteDeviceID, 
*         4ByteDeviceID, 8ByteDeviceID, 9ByteDeviceID).
*
* \return 
* Error status
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_DevIdRead(uint8 nvramId, uint8 *dataPtr, uint8 iDLength)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    CYASSERT(dataPtr); /* dataPtr cannot be NULL */

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiDevIdRead(nvramId, dataPtr, (uint32)iDLength);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        /* Check if the device is FM24V10 */
        if (`$INSTANCE_NAME`_I2C_FM24V10_SLAVE_ID == (`$INSTANCE_NAME`_I2C_FM24V10_SLAVE_ID & nvramId))
        {
            status = `$INSTANCE_NAME`_I2cUniqueDevIdRead(nvramId, dataPtr, (uint32)iDLength);
        }
        else
        {
            status = `$INSTANCE_NAME`_I2cDevIdRead(nvramId, dataPtr, (uint32)iDLength); 
        }
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_RtcRegWrite
****************************************************************************//**
*
* Writes the totalDataCount number of data into NVRAM RTC / F-RAM 
* Processor Companion registers. 
*
*  \note To write the RTC register, this function 
*  should set the W bit of the Flags register
*  (`$INSTANCE_NAME`_RTC_FLAGS) and then write the RTC register.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*  \param addr: The 8-bit NVRAM RTC / F-RAM Proc companion register
*   address for Write.
*  \param *dataWritePtr: The pointer to an array of RTC data bytes to be written.
*  \param totalDataCount: The number of RTC data bytes to be written.
*
* \return 
* Error status
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_RtcRegWrite(uint8 nvramId, 
                                                     uint32 addr, 
                                                     const uint8 *dataWritePtr, 
                                                     uint32 totalDataCount)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    CYASSERT(dataWritePtr); /* dataWritePtr cannot be NULL */

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiRtcRegWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_I2cRtcRegWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_RtcRegRead
****************************************************************************//**
*
* Reads the totalDataCount number of data from nvSRAM RTC / F-RAM Processor 
* Companion registers. 
*
*  \note To read the data from the RTC register of the companion device, 
*  this function should set the R bit of the Flags register
*  (`$INSTANCE_NAME`_RTC_FLAGS) and then read the RTC register.
*
*  \param nvramId: CS for SPI, the slave address for I2C
*  For I2C devices see the detailed format in
*  `$INSTANCE_NAME`_GetStatus() description.
*  \param addr: The 8-bit nvSRAM RTC / F-RAM Proc companion
*  register address for read.
*  \param *dataReadPtr: The pointer to an array for storing RTC data bytes.
*  \param totalDataCount: The number of RTC data bytes to be read.
*
* \return 
* Error status
*  * `$INSTANCE_NAME`_SUCCESS - No errors.
*  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
*  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
*     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
`$INSTANCE_NAME`_status `$INSTANCE_NAME`_RtcRegRead(uint8 nvramId, 
                                    uint32 addr, 
                                    uint8 *dataReadPtr, 
                                    uint32 totalDataCount)
{
    `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

    CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

    #if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_SpiRtcRegRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif
    #if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
        status = `$INSTANCE_NAME`_I2cRtcRegRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif

    return status;
}


#if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_CurrentRtcRegRead
    ****************************************************************************//**
    *
    * Reads the current totalDataCount number of data from nvSRAM RTC / F-RAM 
    * Processor Companion registers. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param *dataReadPtr: The pointer to an array for storing RTC data bytes. 
    *  \param totalDataCount: The number of RTC data bytes to be read.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    `$INSTANCE_NAME`_status `$INSTANCE_NAME`_CurrentRtcRegRead(uint8 nvramId, 
                                                               uint8 *dataReadPtr, 
                                                               uint32 totalDataCount)
    {       
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
 
        CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */
 
        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK;

        /* Set the RTC Registers selection mask */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_RTCR_MASK;    

        /* Send the Start condition and slave ID for Read */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_READ_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);

         /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of the totalDataCount bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataReadPtr, totalDataCount);
        }
       
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);

        return status;
    }
#endif


#if (1 == `$INSTANCE_NAME`_ENABLE_WRITE_PROTECTION)
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SetWp
    ****************************************************************************//**
    *
    * Sets the WP pin to HIGH or LOW.
    *
    *  \param value:  HIGH (1), LOW (0). 
    *
    *  \note
    *  The Active LOW level for SPI NVRAM and Active HIGH level for I2C NVRAM
    *  prevent write operation to the memory and the Status register. Refer to 
    *  the device datasheet for the choices about the software and hardware write 
    *  protection.    
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetWp(uint8 value)
    {
        `$INSTANCE_NAME`_WP_Write(value);
    }
#endif


#if ((`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE) &&\
    (1 == `$INSTANCE_NAME`_ENABLE_HOLD))
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SetHold
    ****************************************************************************//**
    *
    * Sets the HOLD pin to HIGH or LOW.
    *
    *  \param value:  `$INSTANCE_NAME`_HIGH (1), `$INSTANCE_NAME`_LOW (0). 
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetHold(uint8 value)
    {
        `$INSTANCE_NAME`_HOLD_Write(value);
    }
#endif


#if (`$INSTANCE_NAME`_INTERFACE_SPI_SCB == `$INSTANCE_NAME`_INTERFACE)
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiSelectDevice
    ****************************************************************************//**
    *
    * Sets the CS pin to the low state for a device with an SPI interface.
    *
    *  \param nvramId: CS for SPI
    * * `$INSTANCE_NAME`_CS0 - The SPI device connected to the CS_0 pin.
    * * `$INSTANCE_NAME`_CS1 - The SPI device connected to the CS_1 pin.
    * * `$INSTANCE_NAME`_CS2 - The SPI device connected to the CS_2 pin.
    * * `$INSTANCE_NAME`_CS3 - The SPI device connected to the CS_3 pin.
    *
    * \return
    *  error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *
    *******************************************************************************/
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSelectDevice(uint8 nvramId)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        switch(nvramId)
        {
            case `$INSTANCE_NAME`_CS0:
            {
                `$INSTANCE_NAME`_CS_0_ON;
                break;
            }
            case `$INSTANCE_NAME`_CS1:
            {
                #if (`$INSTANCE_NAME`_CS1 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                    `$INSTANCE_NAME`_CS_1_ON;
                #else
                    status = `$INSTANCE_NAME`_DEVICE_ERROR;
                #endif
                break;
            }
            case `$INSTANCE_NAME`_CS2:
            {
                #if (`$INSTANCE_NAME`_CS2 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                    `$INSTANCE_NAME`_CS_2_ON;
                #else
                    status = `$INSTANCE_NAME`_DEVICE_ERROR;
                #endif
                break;
            }
            case `$INSTANCE_NAME`_CS3:
            {
                #if (`$INSTANCE_NAME`_CS3 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                    `$INSTANCE_NAME`_CS_3_ON;
                #else
                    status = `$INSTANCE_NAME`_DEVICE_ERROR;
                #endif
                break;
            }
            default:
            {
                status = `$INSTANCE_NAME`_DEVICE_ERROR;
                break;
            }
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiDeSelectDevice
    ****************************************************************************//**
    *
    * Sets the CS pin to the high state for a device with an SPI interface.
    *
    *  \param nvramId: CS for SPI
    * * `$INSTANCE_NAME`_CS0 - The SPI device connected to the CS_0 pin.
    * * `$INSTANCE_NAME`_CS1 - The SPI device connected to the CS_1 pin.
    * * `$INSTANCE_NAME`_CS2 - The SPI device connected to the CS_2 pin.
    * * `$INSTANCE_NAME`_CS3 - The SPI device connected to the CS_3 pin.
    *
    * \return
    *  error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *
    *******************************************************************************/
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiDeSelectDevice(uint8 nvramId)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        switch(nvramId)
        {
            case `$INSTANCE_NAME`_CS0:
            {
                `$INSTANCE_NAME`_CS_0_OFF;
                break;
            }
            case `$INSTANCE_NAME`_CS1:
            {
                #if (`$INSTANCE_NAME`_CS1 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                    `$INSTANCE_NAME`_CS_1_OFF;
                #else
                    status = `$INSTANCE_NAME`_DEVICE_ERROR;
                #endif
                break;
            }
            case `$INSTANCE_NAME`_CS2:
            {
                #if (`$INSTANCE_NAME`_CS2 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                    `$INSTANCE_NAME`_CS_2_OFF;
                #else
                    status = `$INSTANCE_NAME`_DEVICE_ERROR;
                #endif
                break;
            }
            case `$INSTANCE_NAME`_CS3:
            {
                #if (`$INSTANCE_NAME`_CS3 < `$INSTANCE_NAME`_SPI_CHIP_SELECT)
                    `$INSTANCE_NAME`_CS_3_OFF;
                #else
                    status = `$INSTANCE_NAME`_DEVICE_ERROR;
                #endif
                break;
            }
            default:
            {
                status = `$INSTANCE_NAME`_DEVICE_ERROR;
                break;
            }
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiTxBusyCheck
    ****************************************************************************//**
    *
    * Waits until the SPI bus is busy.
    *
    * \return
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - The TX transmission is complete.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
    *     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiTxBusyCheck(void)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
        uint32 timeout;

        /* Initialize a timeout */
        timeout = 0u;
        
        /* Wait for the transmission to complete */
        while ((0u != `$masterInterface`_SpiIsBusBusy()) || 
               (`$masterInterface`_INTR_MASTER_SPI_DONE != `$masterInterface`_GetMasterInterruptSource()))
        {
            /* Check for a communication timeout */
            if(`$INSTANCE_NAME`_SPI_COM_TIMEOUT < timeout)
            {
                /* An error in the SPI communication */
                status = `$INSTANCE_NAME`_TIMEOUT_ERROR;
                
                break;
            }
            timeout++;
        }
        
        `$masterInterface`_ClearMasterInterruptSource(`$masterInterface`_INTR_MASTER_SPI_DONE);
        
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiRxBufferCheck
    ****************************************************************************//**
    *
    * Waits until the Rx buffer is empty.
    *
    * \return
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does
    *    not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiRxBufferCheck(void)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
        uint32 timeout;

        /* Initialize a timeout */
        timeout = 0u;
        
        /* Ensure data is received in the receive buffer */
        while(0U == `$masterInterface`_SpiUartGetRxBufferSize())
        {
            /* Check for a communication timeout */
            if(`$INSTANCE_NAME`_SPI_COM_TIMEOUT < timeout)
            {
                /* An error in the SPI communication */
                status = `$INSTANCE_NAME`_TIMEOUT_ERROR;
                
                break;
            }
            timeout++;
        }  
        
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiSetWriteEnable
    ****************************************************************************//**
    *
    * Sends the WREN command.
    *
    *  \param nvramId: CS for SPI.
    *
    * \return
    * Error status   
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSetWriteEnable(uint8 nvramId) 
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);
        
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Send the WREN command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_WREN);
            
            /* Wait for the transmission to complete */
            status = `$INSTANCE_NAME`_SpiTxBusyCheck();
            
            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
            
            /* Wait for 1 us to form enough of pulse duration */
            CyDelayUs(1u);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiBufferWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return
    * Error status   
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiBufferWrite(const uint8 dataWritePtr[], 
                                                                   uint32 totalDataCount) 
    {
        uint32 i;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
        uint32 data;

        /* Wait for the transmission to complete */
        status = `$INSTANCE_NAME`_SpiTxBusyCheck();
        
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            for (i = 0u; (i < totalDataCount); i++ )
            {
                /* Get the next byte from the array of data */
                data = (uint32)dataWritePtr[i];

                /* Send the data byte */
                `$masterInterface`_SpiUartWriteTxData(data);
                
                /* Wait for the transmission to complete */
                status = `$INSTANCE_NAME`_SpiTxBusyCheck();
            }
        }

        return status;
    }
    

    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiBufferRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from the SPI Buffer. 
    *
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiBufferRead(uint8 dataReadPtr[], 
                                                                            uint32 totalDataCount)
    {
        uint32 i;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
        uint32 data;

        /* Wait for the transmission to complete */
        status = `$INSTANCE_NAME`_SpiTxBusyCheck();
        
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /*  Read the data bytes from NVRAM */
            for (i = 0u; (i < totalDataCount); i++)
            {
                /* Clear the receive buffer */
                `$masterInterface`_SpiUartClearRxBuffer();

                /* Send the dummy byte to receive data */
                `$masterInterface`_SpiUartWriteTxData(0x00U);
                
                /* Wait for the transmission to complete */
                status = `$INSTANCE_NAME`_SpiTxBusyCheck();
                
                if (`$INSTANCE_NAME`_SUCCESS == status)
                {
                    /* Ensure data is received in the receive buffer */
                    status = `$INSTANCE_NAME`_SpiRxBufferCheck();
                    
                    /* Read the data byte and store it in the read buffer  */
                    data = `$masterInterface`_SpiUartReadRxData();
                    dataReadPtr[i] = (uint8)data;
                }
            }
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiMemoryWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return
    *  Error status   
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount) 
    {
        `$INSTANCE_NAME`_status status;

        /* Send the WREN command */
        status = `$INSTANCE_NAME`_SpiSetWriteEnable(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)`$INSTANCE_NAME`_SpiSelectDevice(nvramId);

            /* Send the F-RAM Write command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_SRAM_WRITE_CMD);   
            
            /* For densities greater than or equal to 1MBit, send a 3-byte address */
            #if (`$INSTANCE_NAME`_DENSITY_1_MBIT <= `$INSTANCE_NAME`_DENSITY)
                `$masterInterface`_SpiUartWriteTxData((addr & `$INSTANCE_NAME`_MSB_ADDR_MASK)>>`$INSTANCE_NAME`_MSB_ADDR_SHIFTBITS);
            #endif
        
            /* Send a 2-byte address */
            `$masterInterface`_SpiUartWriteTxData((addr & `$INSTANCE_NAME`_ISB_ADDR_MASK)>>`$INSTANCE_NAME`_ISB_ADDR_SHIFTBITS);
            `$masterInterface`_SpiUartWriteTxData(addr);

            /* Send the data bytes */
            status = `$INSTANCE_NAME`_SpiBufferWrite(dataWritePtr, totalDataCount);

            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiMemoryRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from NVRAM. 
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Send F-RAM Read command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_SRAM_READ_CMD);   
            
            /* For densities greater than or equal to 1MBit, send a 3-byte address */
            #if (`$INSTANCE_NAME`_DENSITY_1_MBIT <= `$INSTANCE_NAME`_DENSITY)
                `$masterInterface`_SpiUartWriteTxData((addr & `$INSTANCE_NAME`_MSB_ADDR_MASK)>>`$INSTANCE_NAME`_MSB_ADDR_SHIFTBITS);
            #endif
        
            /* Send a 2-byte address */
            `$masterInterface`_SpiUartWriteTxData((addr & `$INSTANCE_NAME`_ISB_ADDR_MASK)>>`$INSTANCE_NAME`_ISB_ADDR_SHIFTBITS);
            `$masterInterface`_SpiUartWriteTxData(addr);

            /* Read the data bytes */
            status = `$INSTANCE_NAME`_SpiBufferRead(dataReadPtr, totalDataCount);

            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiRtcRegWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM RTC / F-RAM 
    * Processor Companion registers. 
    *
    *  \param nvramId: CS for SPIю
    *  \param addr: The 8-bit NVRAM RTC / F-RAM Proc companion
    *  register address for Write.
    *  \param *dataWritePtr: The pointer to an array of RTC data bytes to be written.
    *  \param totalDataCount: The number of RTC data bytes to be written.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount)
    {
        `$INSTANCE_NAME`_status status;

        /* Send the WREN command */
        status = `$INSTANCE_NAME`_SpiSetWriteEnable(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)`$INSTANCE_NAME`_SpiSelectDevice(nvramId);

            /* Send the RTC Write command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_WRTC_CMD);   
                
            /* Send 1 address byte */
            `$masterInterface`_SpiUartWriteTxData(addr);

            /* Send the RTC data bytes */
            status = `$INSTANCE_NAME`_SpiBufferWrite(dataWritePtr, totalDataCount);

            /* De-select the device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId); 
        }
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiRtcRegRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from nvSRAM RTC / F-RAM Processor 
    * Companion registers. 
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 8-bit nvSRAM RTC / F-RAM Proc companion
    *  register address for Read. 
    *  \param *dataReadPtr: The pointer to an array for storing RTC data bytes.
    *  \param totalDataCount: The number of RTC data bytes to be read.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiRtcRegRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Send the RTC Read command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_RDRTC_CMD);   
        
            /* Send 1 address byte */
            `$masterInterface`_SpiUartWriteTxData(addr);
        
            /* Read the RTC data bytes */
            status = `$INSTANCE_NAME`_SpiBufferRead(dataReadPtr, totalDataCount);
            
            /* De-select the device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiNvCommand
    ****************************************************************************//**
    *
    * Sends the NVRAM command. This is supported by nvSRAM only. 
    *
    *  \param nvramId: CS for SPI.
    *  \param nvcmd: The 8-bit NVRAM command.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Send the WREN command */
        status = `$INSTANCE_NAME`_SpiSetWriteEnable(nvramId);
        
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)`$INSTANCE_NAME`_SpiSelectDevice(nvramId);
            
            /* Send the nvcmd command */
            `$masterInterface`_SpiUartWriteTxData(nvcmd);
            
            /* Wait for the transmission to complete */
            status = `$INSTANCE_NAME`_SpiTxBusyCheck();
            
            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiSerialNoWrite
    ****************************************************************************//**
    *
    * Writes the NVRAM Serial number.
    *
    *  \note  The processor companion devices, such as FM33256BG, 
    *  do not support this function. They have the Serial number storage 
    *  is in the RTC/companion space. 
    *  The `$INSTANCE_NAME`_WriteProcessorCompanion() / 
    * `$INSTANCE_NAME`_ReadProcessorCompanion()  functions are used to 
    *  write / read the serial number. Refer to the device datasheet for details. 
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataPtr: The pointer to an array of serial number data to be written.
    *
    * \return
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSerialNoWrite(uint8 nvramId, 
                                                                               const uint8 *dataPtr)
    {
        `$INSTANCE_NAME`_status status;

        /* Send the WREN command */
        status = `$INSTANCE_NAME`_SpiSetWriteEnable(nvramId);
        
        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)`$INSTANCE_NAME`_SpiSelectDevice(nvramId);

            /* Send the Serial number Write command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_WRSN_CMD);
            
            /* Send the serial number */
            status = `$INSTANCE_NAME`_SpiBufferWrite(dataPtr, `$INSTANCE_NAME`_SERIAL_NUM_LENGTH);

            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiSerialNoRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Serial number.
    *
    *  \note  The processor companion devices, such as FM33256BG, 
    *  do not support this function. They have the Serial number storage 
    *  is in the RTC/companion space. 
    *  The `$INSTANCE_NAME`_WriteProcessorCompanion() / 
    * `$INSTANCE_NAME`_ReadProcessorCompanion()  functions are used to 
    *  write / read the serial number. Refer to the device datasheet for details.
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataPtr: The pointer to an array for storing the serial number data.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiSerialNoRead(uint8 nvramId, 
                                                                              uint8 *dataPtr)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Clear the receive buffer */
        `$masterInterface`_SpiUartClearRxBuffer();

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {  
            /* Send the serial number Read command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_RDSN_CMD);

            /* Read the serial number data */
            status = `$INSTANCE_NAME`_SpiBufferRead(dataPtr, `$INSTANCE_NAME`_SERIAL_NUM_LENGTH);

            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }

    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_SpiDevIdRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Device ID. This is supported by nvSRAM and F-RAM above 128Kbit.
    * A pre-defined ID length covers the following varying device's IDs across
    * different product families: 
    *  * CY14B101PA - The DevID size is 4 bytes.
    *  * FM25VN10   - The DevID size is 9 bytes.
    *  * CY15B104Q  - The DevID size is 9 bytes.
    *  * CY14B101I  - The DevID size is 4 bytes.
    *  * FM24VN10   - The DevID size is 3 bytes.
    *  * FM31L278   - The DevID size is 8 bytes.
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataPtr: The pointer to an array for storing a device ID.
    *  \param iDLength: The four predefines for the ID length:
    *         `$INSTANCE_NAME`_3_BYTE_DEVICE_ID, 
    *         `$INSTANCE_NAME`_4_BYTE_DEVICE_ID,
    *         `$INSTANCE_NAME`_8_BYTE_DEVICE_ID, 
    *         `$INSTANCE_NAME`_9_BYTE_DEVICE_ID.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does 
    *     not respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_SpiDevIdRead(uint8 nvramId,
                                                                           uint8 *dataPtr,
                                                                           uint32 iDLength)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Clear the receive buffer */
        `$masterInterface`_SpiUartClearRxBuffer();

        /* Select the F-RAM device */
        status = `$INSTANCE_NAME`_SpiSelectDevice(nvramId);

        if (`$INSTANCE_NAME`_SUCCESS == status)
        {
            /* Send the status register Read command */
            `$masterInterface`_SpiUartWriteTxData(`$INSTANCE_NAME`_NVRAM_RDID_CMD);

            /* Read device ID data */
            status = `$INSTANCE_NAME`_SpiBufferRead(dataPtr, iDLength);
            
            /* De-select the F-RAM device  */
            (void)`$INSTANCE_NAME`_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
#endif


#if (`$INSTANCE_NAME`_INTERFACE_I2C_SCB == `$INSTANCE_NAME`_INTERFACE)
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cDataWrite
    ****************************************************************************//**
    *
    * Sends the totalDataCount number of data.
    *
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return 
    * error status
    * *  See `$INSTANCE_NAME`_I2cDataRead() function for constants.
    *
    *******************************************************************************/
    static uint32 `$INSTANCE_NAME`_I2cDataWrite(const uint8 dataWritePtr[], uint32 totalDataCount)
    {
        uint32 i;
        uint32 i2cStatus = `$masterInterface`_I2C_MSTR_NO_ERROR;
        uint32 data;

        /* Send data bytes for Write */
        for (i = 0u; (i < totalDataCount); i++ )
        {
            /* Get the next byte from the array of data */
            data = (uint32)dataWritePtr[i];
            
            /* Send the data byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(data, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
                       
            if (`$masterInterface`_I2C_MSTR_NO_ERROR != i2cStatus)
            {
                /* An I2C error */
                break;
            }
        }

        return i2cStatus;
    }

    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cDataRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from the I2C bus. 
    *
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * error status
    *  * `$masterInterface`_I2C_MSTR_NO_ERROR - No errors.
    *  * `$masterInterface`_I2C_MSTR_BUS_BUSY - Bus is busy.
    *  Nothing was sent on the bus.
    *  * `$masterInterface`_I2C_MSTR_NOT_READY - Master is not ready
    *  for to start transfer.
    *  * `$masterInterface`_I2C_MSTR_ERR_LB_NAK - Last byte was NAKed.
    *  * `$masterInterface`_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration.
    *  * `$masterInterface`_I2C_MSTR_ERR_BUS_ERR - Master encountered a bus error.
    *  * `$masterInterface`_I2C_MSTR_ERR_ABORT_START - The start condition
    *     generation  was aborted due to beginning of Slave operation.
    *  * `$masterInterface`_I2C_MSTR_ERR_TIMEOUT - The function is timed out.
    *
    *******************************************************************************/
    static uint32 `$INSTANCE_NAME`_I2cDataRead(uint8 dataReadPtr[], uint32 totalDataCount)
    {
        uint32 i;
        uint32 i2cStatus = `$masterInterface`_I2C_MSTR_NO_ERROR;
        uint8 i2cData;
        
        /* Read array of the totalDataCount bytes with ASK data */
        for (i = 0u; (i < (totalDataCount - 1u)); i++)
        {
            i2cStatus = `$masterInterface`_I2CMasterReadByte(`$masterInterface`_I2C_ACK_DATA, 
                                                             &i2cData, 
                                                             `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
            dataReadPtr[i] = i2cData;
        }
        
        /* Read the last byte with NAK data */
        i2cStatus = `$masterInterface`_I2CMasterReadByte(`$masterInterface`_I2C_NAK_DATA, 
                                                         &i2cData, 
                                                         `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        dataReadPtr[totalDataCount - 1u] = i2cData;

        return i2cStatus;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2CSendStop
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param i2cStatus: The status of the I2C communication.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_BUSY - The I2C bus or the NVRAM device is busy.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The NVRAM device is busy or
    *   wrong last address.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2CSendStop(uint32 i2cStatus)
    {
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Check for errors */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* No errors. Send Stop */
            i2cStatus = `$masterInterface`_I2CMasterSendStop(`$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }
        else if ((`$masterInterface`_I2C_MSTR_BUS_BUSY == i2cStatus) ||
                (`$masterInterface`_I2C_MSTR_NOT_READY == i2cStatus))
        {
            /* The I2C bus is busy */
            status = `$INSTANCE_NAME`_DEVICE_BUSY;
        }
        else if (`$masterInterface`_I2C_MSTR_ERR_LB_NAK == i2cStatus)     
        {
            /* The NVRAM device is busy or wrong last address */
            status = `$INSTANCE_NAME`_DEVICE_ERROR;
            i2cStatus = `$masterInterface`_I2CMasterSendStop(`$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }
        else
        {
            /* Other communications error */
            status = `$INSTANCE_NAME`_COMMUNICATION_ERROR;
            i2cStatus = `$masterInterface`_I2CMasterSendStop(`$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        return status;
    }
    

    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cMemoryWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_BUSY - The I2C bus or the NVRAM device is busy.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount) 
    {
        uint32 i2cStatus;

        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the I2C Memory selection mask */
        nvramId |= `$INSTANCE_NAME`_NVRAM_SEL_MEM_MASK;
        
        /* For densities > 1-Mbit, add the MSB bit in in the slave ID (bit0) */
        #if (`$INSTANCE_NAME`_DENSITY_1_MBIT <= `$INSTANCE_NAME`_DENSITY)
            nvramId |= (uint8)(((addr & `$INSTANCE_NAME`_MSBIT_MASK)>>`$INSTANCE_NAME`_MSB_ADDR_SHIFTBITS) &
                              `$INSTANCE_NAME`_LSBIT_MASK);
        #endif

        /* Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ISB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(((addr & `$INSTANCE_NAME`_ISB_ADDR_MASK)
                                                               >>`$INSTANCE_NAME`_ISB_ADDR_SHIFTBITS), 
                                                             `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(addr, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }
        
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send data bytes for Write */
            i2cStatus = `$INSTANCE_NAME`_I2cDataWrite(dataWritePtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cMemoryRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from NVRAM. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of the data bytes to be read.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
    
        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the I2C Memory selection mask */
        nvramId |= `$INSTANCE_NAME`_NVRAM_SEL_MEM_MASK;
    
        /* For densities > 1-Mbit, add the MSB bit in the slave ID (bit0) */
        #if (`$INSTANCE_NAME`_DENSITY_1_MBIT <= `$INSTANCE_NAME`_DENSITY)
            nvramId |= (uint8)(((addr & `$INSTANCE_NAME`_MSBIT_MASK)>>`$INSTANCE_NAME`_MSB_ADDR_SHIFTBITS) &
                              `$INSTANCE_NAME`_LSBIT_MASK);
        #endif

        /* Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Write the SRAM address to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ISB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(((addr & `$INSTANCE_NAME`_ISB_ADDR_MASK)
                                                              >>`$INSTANCE_NAME`_ISB_ADDR_SHIFTBITS), 
                                                             `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(addr, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = `$masterInterface`_I2CMasterSendRestart((uint32)nvramId, 
                                                                `$masterInterface`_I2C_READ_XFER_MODE, 
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of totalDataCount bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataReadPtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cRtcRegWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM RTC / F-RAM 
    * Processor Companion registers. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param addr: The 8-bit NVRAM RTC/F-RAM Proc companion
    *   register address for Write.
    *  \param *dataWritePtr: The pointer to an array of the RTC
    *  data bytes to be written.
    *  \param totalDataCount: The number of the RTC data bytes to be written.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status  status = `$INSTANCE_NAME`_SUCCESS;
        
        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
       
        /* Set RTC Registers selection mask */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_RTCR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the register address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(addr, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
            if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
            {
                /* Send the data bytes for Write */
                i2cStatus = `$INSTANCE_NAME`_I2cDataWrite(dataWritePtr, totalDataCount);
            }
        }

        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);     

        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cRtcRegRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from nvSRAM RTC/F-RAM Processor 
    * Companion registers. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param addr: The 8-bit nvSRAM RTC/F-RAM Proc companion register address for Read.
    *  \param *dataReadPtr: The pointer to an array for storing the RTC data bytes.
    *  \param totalDataCount: The number of the RTC data bytes to be read.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cRtcRegRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
       
        /* Set RTC Registers selection mask */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_RTCR_MASK;

        /* Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Write the SRAM address to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the RTC register address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(addr, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }
        
        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = `$masterInterface`_I2CMasterSendRestart((uint32)nvramId, 
                                                                `$masterInterface`_I2C_READ_XFER_MODE, 
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of the totalDataCount bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataReadPtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);
        
        return status;
    }


    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cNvCommand
    ****************************************************************************//**
    *
    * Sends the NVRAM command. This is supported by nvSRAM only. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param nvcmd: The 8-bit NVRAM command.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_CR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the Command Register address */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(`$INSTANCE_NAME`_COMMAND_REG_ADDR, 
                                                              `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
            if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
            {
               /* Send the data byte for Write */
               i2cStatus = `$masterInterface`_I2CMasterWriteByte(nvcmd, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
            }
        }

        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);

        return status;
    }
   
   
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cSerialNoWrite
    ****************************************************************************//**
    *
    * Writes the NVRAM Serial number. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param *dataPtr: The pointer to an array of serial number data to be written.
    *
    * \return
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cSerialNoWrite(uint8 nvramId,
                                                                               const uint8 *dataPtr)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status  status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_CR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the Serial Number address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(`$INSTANCE_NAME`_SERIAL_NUM_REG_ADDR,
                                                              `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
            if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
            {
                /* Send the data bytes for Write */
                i2cStatus = `$INSTANCE_NAME`_I2cDataWrite(dataPtr, `$INSTANCE_NAME`_SERIAL_NUM_LENGTH);
            }
        }

        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);  
        
        return status;
    }
   
        
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cSerialNoRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Serial number.
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param *dataPtr: The pointer to an array for storing the serial number data.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cSerialNoRead(uint8 nvramId,
                                                                              uint8 *dataPtr)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_CR_MASK;

        /* Send the Start condition and slave ID */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE,
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Write the Serial Number address to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(`$INSTANCE_NAME`_SERIAL_NUM_REG_ADDR,
                                                              `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }
        
        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = `$masterInterface`_I2CMasterSendRestart((uint32)nvramId,
                                                                `$masterInterface`_I2C_READ_XFER_MODE,
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of `$INSTANCE_NAME`_SERIAL_NUM_LENGTH bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataPtr, `$INSTANCE_NAME`_SERIAL_NUM_LENGTH);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);
        
        return status;
    }  

    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cUniqueSleep
    ****************************************************************************//**
    *
    * Sends the NVRAM command for sleep for the I2C devices with
    *  the unique serial number. (Example, FM24V10).
    *
    *  \param nvramId: Еhe slave address for I2C
    *  The nvramId parameter for the FM24VN10 families has the following format: 
    *  0 1 0 1 0 A2 A1 A16. 
    *  Bits A2 and A1 are the slave address inputs. 
    *  Bit A16 is the page select bit and it can have any value for this function. 
    *  Four FM24VN10 devices can be connected to I2C bus with the following
    *  nvramId parameter values:
    *  * 0x50 - Both A2 and A1 pins are connected to the ground.
    *  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
    *  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
    *  * 0x56 – Both A2 and A1 pins are connected to the high level.
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_TIMEOUT_ERROR - The device does not 
    *     respond or `$INSTANCE_NAME`_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cUniqueSleep(uint8 nvramId)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = (nvramId & `$INSTANCE_NAME`_I2C_RSVD_SLAVE_ADDR_MASK) << 1u; 
        
        /* Send the Start condition and Reserved Slave ID */
        i2cStatus = `$masterInterface`_I2CMasterSendStart(`$INSTANCE_NAME`_RSVD_SLAVE_ID, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Write the slave ID to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte((uint32)nvramId, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and Reserved Slave ID */
            (void)`$masterInterface`_I2CMasterSendRestart(`$INSTANCE_NAME`_RSVD_SLAVE_SLEEP_ID, 
                                                                `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);
        
        return status;
    }

        
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cUniqueSerialNoRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Serial number for the I2C devices with
    *  the unique serial number. (Example, FM24V10).
    *
    *  \param nvramId: The slave address for I2C.
    *  The nvramId parameter for the FM24VN10 families has the following format: 
    *  0 1 0 1 0 A2 A1 A16. 
    *  Bits A2 and A1 are the slave address inputs. 
    *  Bit A16 is the page select bit and it can have any value for this function. 
    *  Four FM24VN10 devices can be connected to I2C bus with the following
    *  nvramId parameter values:
    *  * 0x50 - Both A2 and A1 pins are connected to the ground.
    *  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
    *  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
    *  * 0x56 – Both A2 and A1 pins are connected to the high level.
    *  \param *dataPtr: The pointer to an array for storing the serial number data.
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cUniqueSerialNoRead(uint8 nvramId,
                                                                                    uint8 *dataPtr)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = (nvramId & `$INSTANCE_NAME`_I2C_RSVD_SLAVE_ADDR_MASK) << 1u; 
        
        /* Send the Start condition and Reserved Slave ID */
        i2cStatus = `$masterInterface`_I2CMasterSendStart(`$INSTANCE_NAME`_RSVD_SLAVE_ID, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Write the slave ID to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte((uint32)nvramId, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and Reserved Slave ID to read the serial number. */
            i2cStatus = `$masterInterface`_I2CMasterSendRestart(`$INSTANCE_NAME`_RSVD_SLAVE_SERIAL_NUM_ID, 
                                                                `$masterInterface`_I2C_READ_XFER_MODE, 
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of `$INSTANCE_NAME`_SERIAL_NUM_LENGTH bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataPtr, `$INSTANCE_NAME`_SERIAL_NUM_LENGTH);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);
        
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cUniqueDevIdRead
    ****************************************************************************//**
    *
    * Reads the NVRAM device ID for the devices with unique serial number
    * (for example, FM24VN10 device).
    * A pre-defined ID length covers the following varying device's IDs across
    * different product families: 
    *  * FM24VN10   - The DevID size is 3 bytes.
    *
    *  \param nvramId: The slave address for I2C.
    *  The nvramId parameter for the FM24VN10 families has the following format: 
    *  0 1 0 1 0 A2 A1 A16. 
    *  Bits A2 and A1 are the slave address inputs. 
    *  Bit A16 is the page select bit and it can have any value for this function. 
    *  Four FM24VN10 devices can be connected to I2C bus with the following
    *  nvramId parameter values:
    *  * 0x50 - Both A2 and A1 pins are connected to the ground.
    *  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
    *  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
    *  * 0x56 – Both A2 and A1 pins are connected to the high level.
    *  \param *dataPtr: The pointer to an array for storing the device ID.
    *  \param IDLength: The ID length (3ByteDeviceID for the FM24VN10 device).    
    *
    * \return 
    * Error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cUniqueDevIdRead(uint8 nvramId,
                                                                           uint8 *dataPtr,
                                                                           uint32 iDLength)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = (nvramId & `$INSTANCE_NAME`_I2C_RSVD_SLAVE_ADDR_MASK) << 1u; 
        
        /* Send the Start condition and Reserved Slave ID */
        i2cStatus = `$masterInterface`_I2CMasterSendStart(`$INSTANCE_NAME`_RSVD_SLAVE_ID, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE, 
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);

        /* Write the slave ID to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte((uint32)nvramId, `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and Reserved Slave ID to read the device ID */
            i2cStatus = `$masterInterface`_I2CMasterSendRestart(`$INSTANCE_NAME`_RSVD_SLAVE_DEV_ID, 
                                                                `$masterInterface`_I2C_READ_XFER_MODE, 
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of `$INSTANCE_NAME`_SERIAL_NUM_LENGTH bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataPtr, iDLength);
        }

        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);

        return status;
    }

    /*******************************************************************************
    * Function Name:   `$INSTANCE_NAME`_I2cDevIdRead
    ****************************************************************************//**
    *
    * Reads the NVRAM device ID. This is supported by nvSRAM and F-RAM above 128Kbit.
    * A pre-defined ID length covers the following varying device IDs across
    * different product families: 
    *  * CY14B101PA - The DevID size is 4 bytes.
    *  * FM25VN10   - The DevID size is 9 bytes.
    *  * CY15B104Q  - The DevID size is 9 bytes.
    *  * CY14B101I  - The DevID size is 4 bytes.
    *  * FM31L278   - The DevID size is 8 bytes.
    *
    *  \note This function is not applicable for the FM24VN10 devices. 
    *  The `$INSTANCE_NAME`_UniqueDevIdRead() function is used
    *  FM24VN10 devices. For more detail, refer to the device datasheet.
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  `$INSTANCE_NAME`_GetStatus() description.
    *  \param *dataPtr: The pointer to an array for storing the device ID.
    *  \param iDLength: The four pre-defines for the ID length (3ByteDeviceID, 
    *         4ByteDeviceID, 8ByteDeviceID, 9ByteDeviceID).
    *
    * \return 
    * error status
    *  * `$INSTANCE_NAME`_SUCCESS - No errors.
    *  * `$INSTANCE_NAME`_DEVICE_ERROR - The wrong device or a device error.
    *  * `$INSTANCE_NAME`_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static `$INSTANCE_NAME`_status `$INSTANCE_NAME`_I2cDevIdRead(uint8 nvramId,
                                                                           uint8 *dataPtr,
                                                                           uint32 iDLength)
    {
        uint32 i2cStatus;
        `$INSTANCE_NAME`_status status = `$INSTANCE_NAME`_SUCCESS;
    
        /* Apply the mask to unused bits */
        nvramId = nvramId & `$INSTANCE_NAME`_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | `$INSTANCE_NAME`_NVRAM_SEL_CR_MASK;

        /* Send the Start condition and slave ID for Write */
        i2cStatus = `$masterInterface`_I2CMasterSendStart((uint32)nvramId, 
                                                          `$masterInterface`_I2C_WRITE_XFER_MODE,
                                                          `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        
        /* Write the Device ID address to the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = `$masterInterface`_I2CMasterWriteByte(`$INSTANCE_NAME`_DEVICE_ID_REG_ADDR,
                                                              `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }
        
        /* Read data from the slave */
        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = `$masterInterface`_I2CMasterSendRestart((uint32)nvramId, 
                                                                `$masterInterface`_I2C_READ_XFER_MODE,
                                                                `$INSTANCE_NAME`_I2C_COM_TIMEOUT_MS);
        }

        if (`$masterInterface`_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of iDLength bytes */
            i2cStatus = `$INSTANCE_NAME`_I2cDataRead(dataPtr, iDLength);
        }
        
        /* Send Stop and get the error status */
        status = `$INSTANCE_NAME`_I2CSendStop(i2cStatus);

        return status;
    }    
#endif


/* [] END OF FILE */
