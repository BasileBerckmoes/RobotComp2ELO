/***************************************************************************//**
* \file `$INSTANCE_NAME`_EZI2C.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  EZI2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_EZI2C_PVT.h"


/***************************************
*      EZI2C Private Vars
***************************************/

volatile uint8 `$INSTANCE_NAME`_curStatus; /* Status byte */
uint8 `$INSTANCE_NAME`_fsmState;           /* FSM state   */

/* Variables intended to be used with Buffer 1: Primary slave address */
volatile uint8 * `$INSTANCE_NAME`_dataBuffer1; /* Pointer to data buffer 1 */
uint16 `$INSTANCE_NAME`_bufSizeBuf1;           /* Size of buffer 1 in bytes      */
uint16 `$INSTANCE_NAME`_protectBuf1;           /* Start index of write protected area buffer 1 */
`$EzI2cBitWidthReplacementString` `$INSTANCE_NAME`_offsetBuf1; /* Current offset within buffer 1 */
uint16 `$INSTANCE_NAME`_indexBuf1;             /* Current index within buffer 1  */

#if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
    uint8 `$INSTANCE_NAME`_addrBuf1; /* Primary slave address. Used for software comparison   */
    uint8 `$INSTANCE_NAME`_addrBuf2; /* Secondary slave address. Used for software comparison */

    /* Variables intended to be used with Buffer 2: Primary slave address */
    volatile uint8 * `$INSTANCE_NAME`_dataBuffer2; /* Pointer to data buffer 2 */
    uint16 `$INSTANCE_NAME`_bufSizeBuf2;           /* Size of buffer 2 in bytes */
    uint16 `$INSTANCE_NAME`_protectBuf2;           /* Start index of write protected area buffer 2 */
    `$EzI2cBitWidthReplacementString` `$INSTANCE_NAME`_offsetBuf2; /* Current offset within buffer 2 */
    uint16 `$INSTANCE_NAME`_indexBuf2;             /* Current index within buffer 2 */
#endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */


/***************************************
*      EZI2C Private Functions
***************************************/

#if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
    static uint32 `$INSTANCE_NAME`_EzI2CUpdateRxMatchReg(uint32 addr1, uint32 addr2);
#endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of EZI2C */
    const `$INSTANCE_NAME`_EZI2C_INIT_STRUCT `$INSTANCE_NAME`_configEzI2C =
    {
        `$INSTANCE_NAME`_EZI2C_CLOCK_STRETCHING,
        `$INSTANCE_NAME`_EZI2C_MEDIAN_FILTER_ENABLE,
        `$INSTANCE_NAME`_EZI2C_NUMBER_OF_ADDRESSES,
        `$INSTANCE_NAME`_EZI2C_PRIMARY_SLAVE_ADDRESS,
        `$INSTANCE_NAME`_EZI2C_SECONDARY_SLAVE_ADDRESS,
        `$INSTANCE_NAME`_EZI2C_SUB_ADDRESS_SIZE,
        `$INSTANCE_NAME`_EZI2C_WAKE_ENABLE,
        `$INSTANCE_NAME`_EZI2C_BYTE_MODE_ENABLE
    };

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CInit
    ****************************************************************************//**
    *
    *  Configures the `$INSTANCE_NAME` for EZI2C operation.
    *
    *  This function is intended specifically to be used when the `$INSTANCE_NAME` 
    *  configuration is set to “Unconfigured `$INSTANCE_NAME`” in the customizer. 
    *  After initializing the `$INSTANCE_NAME` in EZI2C mode using this function, 
    *  the component can be enabled using the `$INSTANCE_NAME`_Start() or 
    * `$INSTANCE_NAME`_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    * \param config: pointer to a structure that contains the following list of 
    *  fields. These fields match the selections available in the customizer. 
    *  Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EzI2CInit(const `$INSTANCE_NAME`_EZI2C_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_EZI2C, `$INSTANCE_NAME`_DUMMY_PARAM,
                                                                      `$INSTANCE_NAME`_DUMMY_PARAM);

            /* Store internal configuration */
            `$INSTANCE_NAME`_scbMode       = (uint8) `$INSTANCE_NAME`_SCB_MODE_EZI2C;
            `$INSTANCE_NAME`_scbEnableWake = (uint8) config->enableWake;
            `$INSTANCE_NAME`_scbEnableIntr = (uint8) `$INSTANCE_NAME`_SCB_IRQ_INTERNAL;

            `$INSTANCE_NAME`_numberOfAddr  = (uint8) config->numberOfAddresses;
            `$INSTANCE_NAME`_subAddrSize   = (uint8) config->subAddrSize;

        #if (`$INSTANCE_NAME`_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            `$INSTANCE_NAME`_SET_I2C_CFG_SDA_FILT_TRIM(`$INSTANCE_NAME`_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings, AF = 1, DF = 0. Ticket ID#176179 */
            `$INSTANCE_NAME`_I2C_CFG_ANALOG_FITER_ENABLE;

            /* Configure I2C interface */
            `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_GET_CTRL_BYTE_MODE  (config->enableByteMode)    |
                                            `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(config->numberOfAddresses) |
                                            `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE (config->enableWake);

            `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_EZI2C_CTRL;

            /* Configure RX direction */
            `$INSTANCE_NAME`_RX_CTRL_REG = `$INSTANCE_NAME`_EZI2C_RX_CTRL |
                                        `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(`$INSTANCE_NAME`_DIGITAL_FILTER_DISABLE);
                                                ;
            `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_CLEAR_REG;

            /* Set default address and mask */
            if(`$INSTANCE_NAME`_EZI2C_PRIMARY_ADDRESS == config->numberOfAddresses)
            {
                `$INSTANCE_NAME`_RX_MATCH_REG = `$INSTANCE_NAME`_EzI2CUpdateRxMatchReg(config->primarySlaveAddr,
                                                                                       config->primarySlaveAddr);
            }
            else
            {
                `$INSTANCE_NAME`_RX_MATCH_REG = `$INSTANCE_NAME`_EzI2CUpdateRxMatchReg(config->primarySlaveAddr,
                                                                                       config->secondarySlaveAddr);
            }

            /* Configure TX direction */
            `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_EZI2C_TX_CTRL;
            `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = ((0u != (config->enableClockStretch)) ?
                                                 `$INSTANCE_NAME`_CLEAR_REG : `$INSTANCE_NAME`_EZI2C_TX_FIFO_CTRL);

            /* Configure interrupt sources */
        #if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
           `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

            `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_EZI2C_INTR_SLAVE_MASK;
            `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;

            /* Configure interrupt with EZI2C handler but do not enable it */
            CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, (0u != (config->enableClockStretch)) ?
                                                                      (&`$INSTANCE_NAME`_EZI2C_STRETCH_ISR) :
                                                                      (&`$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR));

            if(0u != (config->enableClockStretch))
            {
                /* Configure interrupt sources */
                `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG |= `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH;
                `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            }
            else
            {
                /* Enable Auto ACK/NACK features */
                `$INSTANCE_NAME`_I2C_CTRL_REG |= `$INSTANCE_NAME`_EZI2C_CTRL_AUTO;

                /* Configure RX interrupt source */
                `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG |= `$INSTANCE_NAME`_INTR_SLAVE_I2C_START;
                `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY;
            }

            /* Configure global variables */
            `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_IDLE;

            `$INSTANCE_NAME`_curStatus  = 0u;
            `$INSTANCE_NAME`_indexBuf1  = 0u;
            `$INSTANCE_NAME`_offsetBuf1 = 0u;
            `$INSTANCE_NAME`_indexBuf2  = 0u;
            `$INSTANCE_NAME`_offsetBuf2 = 0u;

            `$INSTANCE_NAME`_addrBuf1 = (uint8) config->primarySlaveAddr;
            `$INSTANCE_NAME`_addrBuf2 = (uint8) config->secondarySlaveAddr;
        }
    }

#else

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the EZI2C operation.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EzI2CInit(void)
    {
        /* Configure I2C interface */
        `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_EZI2C_DEFAULT_CTRL;
        `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_EZI2C_DEFAULT_I2C_CTRL;

    #if (`$INSTANCE_NAME`_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        `$INSTANCE_NAME`_SET_I2C_CFG_SDA_FILT_TRIM(`$INSTANCE_NAME`_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

        /* Configure RX direction */
        `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_EZI2C_DEFAULT_RX_CTRL;
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_EZI2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_EZI2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_EZI2C_DEFAULT_TX_CTRL;
        `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_EZI2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with EZI2C handler but do not enable it */
    #if !defined (CY_EXTERNAL_INTERRUPT_CONFIG)
        CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);

    #if (`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE_CONST)
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_EZI2C_STRETCH_ISR);
    #else
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR);
    #endif /* (`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE_CONST) */

    #endif /* !defined (CY_EXTERNAL_INTERRUPT_CONFIG) */

        /* Configure interrupt sources */
    #if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
        `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_EZI2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

        `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_EZI2C_DEFAULT_INTR_I2C_EC_MASK;
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_EZI2C_DEFAULT_INTR_SLAVE_MASK;
        `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_EZI2C_DEFAULT_INTR_MASTER_MASK;
        `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_EZI2C_DEFAULT_INTR_RX_MASK;
        `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_EZI2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_IDLE;

        `$INSTANCE_NAME`_curStatus  = 0u;
        `$INSTANCE_NAME`_indexBuf1  = 0u;
        `$INSTANCE_NAME`_offsetBuf1 = 0u;

    #if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
        `$INSTANCE_NAME`_indexBuf2  = 0u;
        `$INSTANCE_NAME`_offsetBuf2 = 0u;

        `$INSTANCE_NAME`_addrBuf1 = `$INSTANCE_NAME`_EZI2C_PRIMARY_SLAVE_ADDRESS;
        `$INSTANCE_NAME`_addrBuf2 = `$INSTANCE_NAME`_EZI2C_SECONDARY_SLAVE_ADDRESS;
    #endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */
    }
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CStop
****************************************************************************//**
*
*  Resets the EZI2C FSM into the default state.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzI2CStop(void)
{
    `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CGetActivity
****************************************************************************//**
*
*  Returns the EZI2C slave status.
*  The read, write and error status flags reset to zero after this function
*  call. The busy status flag is cleared when the transaction intended for
*  the EZI2C slave completes.
*
* \return
*  Returns the status of the EZI2C Slave activity.
*  - `$INSTANCE_NAME`_EZI2C_STATUS_READ1 - Read transfer complete. The transfer 
*    used the primary slave address. The error condition status bit must be 
*    checked to ensure that read transfer was completed successfully.
*  - `$INSTANCE_NAME`_EZI2C_STATUS_WRITE1 - Write transfer complete. The buffer 
*    content was modified. The transfer used the primary slave address. 
*    The error condition status bit must be checked to ensure that write 
*    transfer was completed successfully.
*  - `$INSTANCE_NAME`_EZI2C_STATUS_READ2 - Read transfer complete. The transfer
*    used the secondary slave address. The error condition status bit must be 
*    checked to ensure that read transfer was completed successfully.
*  - `$INSTANCE_NAME`_EZI2C_STATUS_WRITE2 - Write transfer complete. The buffer
*    content was modified. The transfer used the secondary slave address. 
*    The error condition status bit must be checked to ensure that write 
*    transfer was completed successfully.
*  - `$INSTANCE_NAME`_EZI2C_STATUS_BUSY - A transfer intended for the primary 
*    or secondary address is in progress. The status bit is set after an 
*    address match and cleared on a Stop or ReStart condition.
*  - `$INSTANCE_NAME`_EZI2C_STATUS_ERR - An error occurred during a transfer 
*    intended for the primary or secondary slave address. The sources of error
*    are: misplaced Start or Stop condition or lost arbitration while slave 
*    drives SDA.
*    The write buffer may contain invalid byte or part of the transaction when 
*    `$INSTANCE_NAME`_EZI2C_STATUS_ERR and `$INSTANCE_NAME`_EZI2C_STATUS_WRITE1/2 
*    is set. It is recommended to discard buffer content in this case.
*
* \globalvars
*  `$INSTANCE_NAME`_curStatus - used to store the current status of the EZI2C 
*  slave.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzI2CGetActivity(void)
{
    uint32 status;

    `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

    status = `$INSTANCE_NAME`_curStatus;

    /* Relay on address match event from HW as bus busy status */
    `$Cond`if(`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_DISABLE)
    {
        /* For `$INSTANCE_NAME`_CY_SCBIP_V0 the wake is prohibited by customizer */
        `$Cond`if(`$INSTANCE_NAME`_EZI2C_EC_AM_ENABLE)
        {
            status |= `$INSTANCE_NAME`_CHECK_INTR_I2C_EC(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP) ?
                        `$INSTANCE_NAME`_EZI2C_STATUS_BUSY : 0u;
        }
        `$Cond`else
        {
            status |= `$INSTANCE_NAME`_CHECK_INTR_SLAVE(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH) ?
                        `$INSTANCE_NAME`_EZI2C_STATUS_BUSY : 0u;
        }
        `$EndCond`
    }
    `$EndCond`

    `$INSTANCE_NAME`_curStatus &= ((uint8) ~`$INSTANCE_NAME`_EZI2C_CLEAR_STATUS);

    `$INSTANCE_NAME`_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CSetAddress1
****************************************************************************//**
*
*  Sets the primary EZI2C slave address.
*
* \param address: I2C slave address for the secondary device.
*  This address is the 7-bit right-justified slave address and does not 
*   include the R/W bit.
*
*  The address value is not checked to see if it violates the I2C spec. 
*  The preferred addresses are in the range between 8 and 120 (0x08 to 0x78).
*
* \globalvars
*  `$INSTANCE_NAME`_addrBuf1 - used to store the primary 7-bit slave address 
*  value.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzI2CSetAddress1(uint32 address)
{
    `$Cond`if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE)
    {
        `$INSTANCE_NAME`_addrBuf1 = (uint8) address;

        `$INSTANCE_NAME`_RX_MATCH_REG = 
                        `$INSTANCE_NAME`_EzI2CUpdateRxMatchReg(address, (uint32) `$INSTANCE_NAME`_addrBuf2);
    }
    `$Cond`else
    {
        uint32 matchReg;

        matchReg = `$INSTANCE_NAME`_RX_MATCH_REG;

        /* Set address. */
        matchReg &= (uint32) ~`$INSTANCE_NAME`_RX_MATCH_ADDR_MASK;
        matchReg |= (uint32)  `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(address);

        `$INSTANCE_NAME`_RX_MATCH_REG = matchReg;
    }
    `$EndCond`
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CGetAddress1
****************************************************************************//**
*
*  Returns primary the EZ I2C slave address.
*  This address is the 7-bit right-justified slave address and does not include 
*  the R/W bit.
*
* \return
*  Primary EZI2C slave address.
*
* \globalvars
*  `$INSTANCE_NAME`_addrBuf1 - used to store the primary 7-bit slave address 
*  value.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzI2CGetAddress1(void)
{
    uint32 address;

    `$Cond`if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE)
    {
        address = (uint32) `$INSTANCE_NAME`_addrBuf1;
    }
    `$Cond`else
    {
        address = (`$INSTANCE_NAME`_GET_RX_MATCH_ADDR(`$INSTANCE_NAME`_RX_MATCH_REG) >>
                   `$INSTANCE_NAME`_I2C_SLAVE_ADDR_POS);
    }
    `$EndCond`

    return(address);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CSetBuffer1
****************************************************************************//**
*
*  Sets up the data buffer to be exposed to the I2C master on a primary slave
*  address request.
*
* \param bufSize: Size of the buffer in bytes.
* \param rwBoundary: Number of data bytes starting from the beginning of the 
*  buffer with read and write access. Data bytes located at offset rwBoundary 
*  or greater are read only.
*  This value must be less than or equal to the buffer size.
* \param buffer: Pointer to the data buffer.
*
* \sideeffect
*  Calling this function in the middle of a transaction intended for the 
*  primary slave address leads to unexpected behavior.
*
* \globalvars
*  `$INSTANCE_NAME`_dataBuffer1 – the pointer to the buffer to be exposed to the
*  master on a primary address.
*  `$INSTANCE_NAME`_bufSizeBuf1 - the size of the buffer to be exposed to the 
*  master on a primary address.
*  `$INSTANCE_NAME`_protectBuf1 - the start index of the read-only region in the
*  buffer to be exposed to the master on a primary address. The read-only region
*  continues up to the end the buffer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzI2CSetBuffer1(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer)
{
    if (NULL != buffer)
    {
        `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

        `$INSTANCE_NAME`_dataBuffer1 =  buffer;
        `$INSTANCE_NAME`_bufSizeBuf1 = (uint16) bufSize;
        `$INSTANCE_NAME`_protectBuf1 = (uint16) rwBoundary;

        `$INSTANCE_NAME`_EnableInt();   /* Release lock */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CSetReadBoundaryBuffer1
****************************************************************************//**
*
*  Sets the read only boundary in the data buffer to be exposed to the I2C
*  master on a primary slave address request.
*
* \param rwBoundry: Number of data bytes starting from the beginning of the 
*  buffer with read and write access. Data bytes located at offset rwBoundary 
*  or greater are read only.
*  This value must be less than or equal to the buffer size.
*
* \sideeffect
*  Calling this function in the middle of a transaction intended for the 
*  primary slave address leads to unexpected behavior.
*
* \globalvars
*  `$INSTANCE_NAME`_protectBuf1 - the start index of the read-only region in the
*  buffer to be exposed to the master on a primary address. The read-only region
*  continues up to the end the buffer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzI2CSetReadBoundaryBuffer1(uint32 rwBoundary)
{
    `$INSTANCE_NAME`_protectBuf1 = (uint16) rwBoundary;
}


#if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CUpdateRxMatchReg
    ****************************************************************************//**
    *
    *  Returns the value of the RX MATCH register for addr1 and addr2. The addr1 is
    *  accepted as the primary address and it is written to RX_MATCH.ADDRESS
    *  (addr1 << 0x01).
    *  The RX_MATCH.MASK is set as follow: addr1 and addr2 equal bits set to 1
    *  otherwise 0.
    *
    * \param addr1: I2C slave address for the primary device.
    * \param addr2: I2C slave address for the secondary device.
    *  This address is the 7-bit right-justified slave address and does
    *  not include the R/W bit.
    *
    * \return
    *  Value of RX MATCH register.
    *
    *******************************************************************************/
    static uint32 `$INSTANCE_NAME`_EzI2CUpdateRxMatchReg(uint32 addr1, uint32 addr2)
    {
        uint32 matchReg;

        matchReg  = ~(addr1 ^ addr2); /* If (addr1 and addr2) bit matches - mask bit equals 1, in other case 0 */

        matchReg  = (uint32) (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(matchReg) << `$INSTANCE_NAME`_RX_MATCH_MASK_POS);
        matchReg |= `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(addr1);

        return(matchReg);
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CSetAddress2
    ****************************************************************************//**
    *
    *  Sets the secondary EZI2C slave address.
    *
    * \param address: secondary I2C slave address.
    *  This address is the 7-bit right-justified slave address and does not 
    *  include the R/W bit.
    *  The address value is not checked to see if it violates the I2C spec. 
    *  The preferred addresses are in the range between 8 and 120 (0x08 to 0x78).
    *
    * \globalvars
    *  `$INSTANCE_NAME`_addrBuf2 - used to store the secondary 7-bit slave address 
    *  value.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EzI2CSetAddress2(uint32 address)
    {
        `$INSTANCE_NAME`_addrBuf2 = (uint8) address;

        `$INSTANCE_NAME`_RX_MATCH_REG = 
                        `$INSTANCE_NAME`_EzI2CUpdateRxMatchReg((uint32) `$INSTANCE_NAME`_addrBuf1, address);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CGetAddress2
    ****************************************************************************//**
    *
    *  Returns the secondary EZ I2C slave address.
    *  This address is the 7-bit right-justified slave address and does not include 
    *  the R/W bit.
    *
    * \return
    *  Secondary I2C slave address.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_addrBuf2 - used to store the secondary 7-bit slave address 
    *  value.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_EzI2CGetAddress2(void)
    {
        return((uint32) `$INSTANCE_NAME`_addrBuf2);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CSetBuffer2
    ****************************************************************************//**
    *
    *  Sets up the data buffer to be exposed to the I2C master on a secondary slave
    *  address request.
    *
    * \param bufSize: Size of the buffer in bytes.
    * \param rwBoundary: Number of data bytes starting from the beginning of the 
    *  buffer with read and write access. Data bytes located at offset rwBoundary 
    *  or greater are read only.
    *  This value must be less than or equal to the buffer size.
    * \param buffer: Pointer to the data buffer.
    *
    * \sideeffects
    *  Calling this function in the middle of a transaction intended for the 
    *  secondary slave address leads to unexpected behavior.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_dataBuffer2 – the pointer to the buffer to be exposed to the
    *  master on a secondary address.
    *  `$INSTANCE_NAME`_bufSizeBuf2 - the size of the buffer to be exposed to the 
    *  master on a secondary address.
    *  `$INSTANCE_NAME`_protectBuf2 - the start index of the read-only region in the
    *  buffer to be exposed to the master on a secondary address. The read-only 
    *  region continues up to the end the buffer.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EzI2CSetBuffer2(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer)
    {
        if (NULL != buffer)
        {
            `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

            `$INSTANCE_NAME`_dataBuffer2 =  buffer;
            `$INSTANCE_NAME`_bufSizeBuf2 = (uint16) bufSize;
            `$INSTANCE_NAME`_protectBuf2 = (uint16) rwBoundary;

            `$INSTANCE_NAME`_EnableInt();   /* Release lock */
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CSetReadBoundaryBuffer2
    ****************************************************************************//**
    *
    *  Sets the read only boundary in the data buffer to be exposed to the I2C
    *  master on a secondary address request.
    *
    *  \param rwBoundary: Number of data bytes starting from the beginning of the
    *   buffer with read and write access. Data bytes located at offset rwBoundary 
    *   or greater are read only.
    *   This value must be less than or equal to the buffer size.
    *
    *  \sideeffect
    *   Calling this function in the middle of a transaction intended for the 
    *   secondary slave address leads to unexpected behavior.
    *
    * \globalvars
    *  `$INSTANCE_NAME`_protectBuf2 - the start index of the read-only region in the
    *  buffer to be exposed to the master on a secondary address. The read-only 
    *  region continues up to the end the buffe
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EzI2CSetReadBoundaryBuffer2(uint32 rwBoundary)
    {
        `$INSTANCE_NAME`_protectBuf2 = (uint16) rwBoundary;
    }

#endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */


#if(`$INSTANCE_NAME`_EZI2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CSaveConfig
    ****************************************************************************//**
    *
    *  Clock stretching is  enabled: Enables INTR_I2C_EC.WAKE_UP interrupt source.
    *  It triggers on the slave address match.
    *  Clock stretching is disabled: Waits until the I2C slave becomes free and
    *  disables the block to perform reconfiguration from the active mode operation
    *  to deep sleep with wake up on the address match: enables INTR_I2C_EC.WAKE_UP
    *  interrupt source and disables the INTR_S and INTR_TX interrupt sources.
    *  The block is disabled before reconfiguration and enabled when
    *  it is completed.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EzI2CSaveConfig(void)
    {
    #if(`$INSTANCE_NAME`_CY_SCBIP_V0)

        `$Cond`if(`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Enable wakeup interrupt source on address match */
            `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
        }
        `$EndCond`

    #else
        uint8 enableInt;

        enableInt = (uint8) `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP;

        `$Cond`if(`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE)
        {
        #if (`$INSTANCE_NAME`_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID #187931 */
            `$INSTANCE_NAME`_SCBCLK_Stop();
        #endif /* (`$INSTANCE_NAME`_SCB_CLK_INTERNAL) */

            /* Enable interrupt source to wakeup device */
            `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(enableInt);
        }
        `$Cond`else
        {
            for(;;) /* Wait for end of transaction intended to slave */
            {
                if(0u == (`$INSTANCE_NAME`_GetI2CExtClkInterruptSource() & `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP))
                {
                    enableInt = CyEnterCriticalSection();

                    if(0u == (`$INSTANCE_NAME`_GetI2CExtClkInterruptSource() & `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP))
                    {
                        /* Attempts to set NACK command before disable block */
                        `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK;

                        if(0u == (`$INSTANCE_NAME`_GetI2CExtClkInterruptSource() & `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP))
                        {
                            /* NACK command was set before. It is safe to disable block */
                            `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED;
                            `$INSTANCE_NAME`_DisableInt();

                            CyExitCriticalSection(enableInt);
                            break;
                        }
                        else
                        {
                            /* Clear NACK command to prevent data NACK */
                            `$INSTANCE_NAME`_I2C_SLAVE_CLEAR_NACK;
                        }
                    }

                    CyExitCriticalSection(enableInt);
                }
            }

            /* Disable all active mode interrupt sources */
            `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
            `$INSTANCE_NAME`_SetSlaveInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
            `$INSTANCE_NAME`_ClearPendingInt();
            `$INSTANCE_NAME`_EnableInt();

            /* Enable wakeup interrupt on address match */
            `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);

            enableInt = CyEnterCriticalSection();

            `$INSTANCE_NAME`_CTRL_REG |= (uint32) `$INSTANCE_NAME`_CTRL_ENABLED;
            `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK;

            CyExitCriticalSection(enableInt);
        }
        `$EndCond`
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EzI2CRestoreConfig
    ****************************************************************************//**
    *
    *  Clock stretching is  enabled: Disables the INTR_I2C_EC.WAKE_UP interrupt
    *  source.
    *  Clock stretching is disabled: Reconfigures the EZI2C component from
    *  Deep Sleep (wake up on the address match) to active operation: disables
    *  the INTR_I2C_EC.WAKE_UP interrupt source and restores the INTR_S
    *  interrupt sources to operate in the active mode.
    *  The block is disabled before reconfiguration and enabled when
    *  it is completed.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EzI2CRestoreConfig(void)
    {
    #if(`$INSTANCE_NAME`_CY_SCBIP_V0)

        `$Cond`if(`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Disable wakeup interrupt on address match */
            `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
        }
        `$EndCond`

    #else

        `$Cond`if(`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE)
        {
            /* Disable wakeup interrupt source on address match */
            `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

        #if (`$INSTANCE_NAME`_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID #187931 */
            `$INSTANCE_NAME`_SCBCLK_Start();
        #endif /* (`$INSTANCE_NAME`_SCB_CLK_INTERNAL) */
        }
        `$Cond`else
        {
            /* NACK will be driven on the bus by wakeup or NACK command.
            * It is safe to disable block to restore active mode configuration.
            */
            `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED;

            /* Restore active mode interrupt sources */
            `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
            `$INSTANCE_NAME`_SetSlaveInterruptMode(`$INSTANCE_NAME`_EZI2C_INTR_SLAVE_MASK |
                                                   `$INSTANCE_NAME`_INTR_SLAVE_I2C_START);
            `$INSTANCE_NAME`_ClearPendingInt();

            `$INSTANCE_NAME`_CTRL_REG |= (uint32) `$INSTANCE_NAME`_CTRL_ENABLED;
        }
        `$EndCond`

    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */
    }
#endif /* (`$INSTANCE_NAME`_EZI2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
