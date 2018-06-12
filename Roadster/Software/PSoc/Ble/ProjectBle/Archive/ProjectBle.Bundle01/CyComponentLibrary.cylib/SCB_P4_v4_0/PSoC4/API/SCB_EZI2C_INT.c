/***************************************************************************//**
* \file `$INSTANCE_NAME`_EZI2C_INT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in EZI2C mode.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_EZI2C_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if(`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EZI2C_STRETCH_ISR
    ****************************************************************************//**
    *
    *  Handles the Interrupt Service Routine for the SCB EZI2C mode.
    *  The clock stretching is used during operation.
    *
    *******************************************************************************/
    CY_ISR_PROTO(`$INSTANCE_NAME`_EZI2C_STRETCH_ISR)
    {
        static uint16 locBufSize;
        uint32 locIndex;
        uint32 locStatus;

        uint32 endTransfer;
        uint32 fifoIndex;
        uint32 locByte;

        uint32 locIntrCause;
        uint32 locIntrSlave;

    #ifdef `$INSTANCE_NAME`_EZI2C_STRETCH_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EZI2C_STRETCH_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_EZI2C_STRETCH_ISR_ENTRY_CALLBACK */

    #if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
        /* Variable intended to be used with either buffer */
        static volatile uint8 * `$INSTANCE_NAME`_dataBuffer; /* Pointer to data buffer              */
        static uint16 `$INSTANCE_NAME`_bufSizeBuf;           /* Size of buffer in bytes             */
        static uint16 `$INSTANCE_NAME`_protectBuf;           /* Start index of write protected area */

        static uint8 activeAddress;
        uint32 ackResponse;

        ackResponse = `$INSTANCE_NAME`_EZI2C_ACK_RECEIVED_ADDRESS;
    #endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */

    #if !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER)
        if(NULL != `$INSTANCE_NAME`_customIntrHandler)
        {
            `$INSTANCE_NAME`_customIntrHandler();
        }
    #else
        CY_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER();
    #endif /* !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER) */

        /* Make local copy of global variable */
        locIndex = `$INSTANCE_NAME`_EZI2C_GET_INDEX(activeAddress);

        /* Get interrupt sources */
        locIntrSlave = `$INSTANCE_NAME`_GetSlaveInterruptSource();
        locIntrCause = `$INSTANCE_NAME`_GetInterruptCause();

        /* INTR_SLAVE.I2C_ARB_LOST and INTR_SLAVE_I2C.BUS_ERROR */
        /* Handles errors on the bus. There are cases when both bits are set.
        * The error recovery is common: re-enable the scb IP. The content of the RX FIFO is lost.
        */
        if(0u != (locIntrSlave & (`$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST |
                                  `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR)))
        {
            `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED; /* Disable SCB block */

        #if(`$INSTANCE_NAME`_CY_SCBIP_V0)
            if(0u != ((uint8) `$INSTANCE_NAME`_EZI2C_STATUS_BUSY & `$INSTANCE_NAME`_curStatus))
        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */
            {
                `$INSTANCE_NAME`_curStatus &= (uint8) ~`$INSTANCE_NAME`_EZI2C_STATUS_BUSY;
                `$INSTANCE_NAME`_curStatus |= (uint8)  `$INSTANCE_NAME`_EZI2C_STATUS_ERR;

                /* INTR_TX_EMPTY is enabled in the address phase to receive data */
                if(0u == (`$INSTANCE_NAME`_GetTxInterruptMode() & `$INSTANCE_NAME`_INTR_TX_EMPTY))
                {
                    /* Write complete */
                    if(`$INSTANCE_NAME`_indexBuf1 != `$INSTANCE_NAME`_offsetBuf1)
                    {
                        `$INSTANCE_NAME`_curStatus |= (uint8) `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP;
                    }
                }
                else
                {
                    /* Read complete */
                    `$INSTANCE_NAME`_curStatus |= (uint8) `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK;
                }
            }

            `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_DATA;

            /* Disable TX and RX interrupt sources */
            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
            `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

        #if(`$INSTANCE_NAME`_CY_SCBIP_V0)
            /* Clear interrupt sources as they are not automatically cleared after SCB is disabled */
            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ALL);
            `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);
        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

            `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_IDLE;

            `$INSTANCE_NAME`_CTRL_REG |= (uint32) `$INSTANCE_NAME`_CTRL_ENABLED;  /* Enable SCB block */
        }
        else
        {
            /* INTR_I2C_EC_WAKE_UP */
            /* Wakes up device from deep sleep */
            if(0u != (locIntrCause & `$INSTANCE_NAME`_INTR_CAUSE_I2C_EC))
            {
                /* Disables wakeup interrupt source but does not clear it. It is cleared in INTR_SLAVE_I2C_ADDR_MATCH */
                `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
            }

            if(0u != (locIntrCause & (`$INSTANCE_NAME`_INTR_CAUSE_RX | `$INSTANCE_NAME`_INTR_CAUSE_SLAVE)))
            {
                /* INTR_RX.NOT_EMPTY */
                /* Receives data byte-by-byte. Does not use RX FIFO capabilities */
                if (0u != (`$INSTANCE_NAME`_GetRxInterruptSourceMasked() & `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
                {
                #if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
                    /* If I2C_STOP service is delayed to I2C_ADDR_MATCH the address byte is in the RX FIFO and
                    * RX_NOT_EMPTY is enabled. The address byte has to stay into RX FIFO therefore
                    * RX.NOT_EMPTY service has to be skipped. The address byte has to be read by I2C_ADDR_MATCH.
                    */
                    if (0u == (locIntrCause & `$INSTANCE_NAME`_INTR_CAUSE_SLAVE))
                #endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */
                    {
                        locByte = `$INSTANCE_NAME`_RX_FIFO_RD_REG;

                        switch(`$INSTANCE_NAME`_fsmState)
                        {
                        case `$INSTANCE_NAME`_EZI2C_FSM_BYTE_WRITE:
                            if(0u != locBufSize)
                            {
                                /* Store data byte and ACK */
                                `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_ACK;

                                `$INSTANCE_NAME`_dataBuffer`$BufNum`[locIndex] = (uint8) locByte;
                                locIndex++;
                                locBufSize--;
                            }
                            else
                            {
                                /* Discard data byte and NACK */
                                `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK;
                            }
                            break;

                    #if(`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16_CONST)
                        case `$INSTANCE_NAME`_EZI2C_FSM_OFFSET_HI8:

                            `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_ACK;

                            /* Store offset most significant byre */
                            locBufSize = (uint16) ((uint8) locByte);

                            `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_OFFSET_LO8;

                            break;
                    #endif /* (`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16_CONST) */

                        case `$INSTANCE_NAME`_EZI2C_FSM_OFFSET_LO8:

                            `$Cond`if (`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16)
                            {
                                /* Collect 2 bytes offset */
                                locByte = ((uint32) ((uint32) locBufSize << 8u)) | locByte;
                            }
                            `$EndCond`

                            /* Check offset against buffer size */
                            if(locByte < (uint32) `$INSTANCE_NAME`_bufSizeBuf`$BufNum`)
                            {
                                `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_ACK;

                                /* Update local buffer index with new offset */
                                locIndex = locByte;

                                /* Get available buffer size to write */
                                locBufSize = (uint16) ((locByte < `$INSTANCE_NAME`_protectBuf`$BufNum`) ?
                                                       (`$INSTANCE_NAME`_protectBuf`$BufNum` - locByte) : (0u));

                            #if(`$INSTANCE_NAME`_CY_SCBIP_V0)

                                if(locBufSize < `$INSTANCE_NAME`_EZI2C_FIFO_SIZE)
                                {
                                    /* Set FSM state to receive byte by byte */
                                    `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_BYTE_WRITE;
                                }
                                /* Receive RX FIFO chunks */
                                else if(locBufSize == `$INSTANCE_NAME`_EZI2C_FIFO_SIZE)
                                {
                                    `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA; /* NACK when RX FIFO is full */
                                    `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                                }
                                else
                                {
                                    `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_ACK; /* Stretch when RX FIFO is full */
                                    `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_FULL);
                                }

                            #else

                                `$Cond`if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE)
                                {
                                    /* Set FSM state to receive byte by byte.
                                    * The byte by byte receive is always chosen for two addresses. Ticket ID#175559.
                                    */
                                    `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_BYTE_WRITE;
                                }
                                `$Cond`else
                                {
                                    if (locBufSize < `$INSTANCE_NAME`_EZI2C_FIFO_SIZE)
                                    {
                                        /* Set FSM state to receive byte by byte */
                                        `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_BYTE_WRITE;
                                    }
                                    /* Receive RX FIFO chunks */
                                    else if (locBufSize == `$INSTANCE_NAME`_EZI2C_FIFO_SIZE)
                                    {
                                        `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA; /* NACK when RX FIFO is full */
                                        `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                                    }
                                    else
                                    {
                                        `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_ACK; /* Stretch when RX FIFO is full */
                                        `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_FULL);
                                    }
                                }
                                `$EndCond`

                            #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

                                /* Store local offset into global variable */
                                `$INSTANCE_NAME`_EZI2C_SET_OFFSET(activeAddress, locIndex);
                            }
                            else
                            {
                                /* Discard offset byte and NACK */
                                `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK;
                            }
                            break;

                        default:
                            CYASSERT(0u != 0u); /* Should never get there */
                            break;
                        }

                        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
                    }
                }
                /* INTR_RX.FULL, INTR_SLAVE.I2C_STOP */
                /* Receive FIFO chunks: auto data ACK is enabled */
                else if (0u != (`$INSTANCE_NAME`_I2C_CTRL_REG & `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK))
                {
                    /* Slave interrupt (I2C_STOP or I2C_ADDR_MATCH) leads to completion of read.
                    * A completion event has a higher priority than the FIFO full.
                    * Read remaining data from RX FIFO.
                    */
                    if(0u != (locIntrCause & `$INSTANCE_NAME`_INTR_CAUSE_SLAVE))
                    {
                        /* Read remaining bytes from RX FIFO */
                        fifoIndex = `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES;

                        `$Cond`if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE)
                        {
                            /* Update with current address match */
                            if(`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH))
                            {
                                /* Update RX FIFO entries as address byte is there now */
                                fifoIndex = `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES;

                                /* If SR is valid, RX FIFO is full and address is in SHIFTER:
                                * read 8 entries and leave address in RX FIFO for further processing.
                                * If SR is invalid, address is already in RX FIFO: read (entries-1).
                                */
                                fifoIndex -= ((0u != `$INSTANCE_NAME`_GET_RX_FIFO_SR_VALID) ? (0u) : (1u));
                            }
                        }
                        `$EndCond`

                        `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_DATA;
                        endTransfer = `$INSTANCE_NAME`_EZI2C_CONTINUE_TRANSFER;
                    }
                    else
                    /* INTR_RX_FULL */
                    /* Continue transfer or disable INTR_RX_FULL to catch completion event. */
                    {
                        /* Calculate buffer size available to write data into */
                        locBufSize -= (uint16) `$INSTANCE_NAME`_EZI2C_FIFO_SIZE;

                        if(locBufSize <= `$INSTANCE_NAME`_EZI2C_FIFO_SIZE)
                        {
                            /* Send NACK when RX FIFO overflow */
                            fifoIndex   = locBufSize;
                            endTransfer = `$INSTANCE_NAME`_EZI2C_COMPLETE_TRANSFER;
                        }
                        else
                        {
                            /* Continue  transaction */
                            fifoIndex   = `$INSTANCE_NAME`_EZI2C_FIFO_SIZE;
                            endTransfer = `$INSTANCE_NAME`_EZI2C_CONTINUE_TRANSFER;
                        }
                    }

                    for(; (0u != fifoIndex); fifoIndex--)
                    {
                        /* Store data in buffer */
                        `$INSTANCE_NAME`_dataBuffer`$BufNum`[locIndex] = (uint8) `$INSTANCE_NAME`_RX_FIFO_RD_REG;
                        locIndex++;
                    }

                    /* Complete transfer sending NACK when RX FIFO overflow */
                    if(`$INSTANCE_NAME`_EZI2C_COMPLETE_TRANSFER == endTransfer)
                    {
                        `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_NACK;

                        /* Disable INTR_RX_FULL during last RX FIFO chunk reception */
                        `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                    }

                    `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_FULL |
                                                            `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
                }
                else
                {
                    /* Exit for slave interrupts which are not active for RX direction:
                    * INTR_SLAVE.I2C_ADDR_MATCH and INTR_SLAVE.I2C_STOP while byte-by-byte reception.
                    */
                }
            }

            if(0u != (locIntrCause & `$INSTANCE_NAME`_INTR_CAUSE_SLAVE))
            {
                /* INTR_SLAVE.I2C_STOP */
                /* Catch Stop condition: completion of write or read transfer */
            #if(!`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
                if(0u != (locIntrSlave & `$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP))
            #else
                /* Prevent triggering when matched address was NACKed */
                if((0u != (locIntrSlave & `$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP)) &&
                   (0u != ((uint8) `$INSTANCE_NAME`_EZI2C_STATUS_BUSY & `$INSTANCE_NAME`_curStatus)))
            #endif
                {
                    /* Disable TX and RX interrupt sources */
                    `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                    `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

                    /* Set read completion mask */
                    locStatus = `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK;

                    /* Check if buffer content was modified: the address phase resets the locIndex */
                    if(locIndex != `$INSTANCE_NAME`_EZI2C_GET_OFFSET(activeAddress))
                    {
                        locStatus |= `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP;
                    }

                    /* Complete read or write transaction */
                    locStatus &= locIntrSlave;
                    `$INSTANCE_NAME`_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus);
                    locStatus |= (uint32)  `$INSTANCE_NAME`_curStatus;
                    locStatus &= (uint32) ~`$INSTANCE_NAME`_EZI2C_STATUS_BUSY;
                    `$INSTANCE_NAME`_curStatus = (uint8) locStatus;

                    `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_IDLE;

                    `$Cond`if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE)
                    {
                        /* Store local index into global variable, before address phase */
                        `$INSTANCE_NAME`_EZI2C_SET_INDEX(activeAddress, locIndex);
                    }
                    `$EndCond`
                }

                /* INTR_SLAVE.I2C_ADDR_MATCH */
                /* The matched address is received: the slave starts its operation.
                * INTR_SLAVE_I2C_STOP updates the buffer index before the address phase for two addresses mode.
                * This is done to update buffer index correctly before the address phase changes it.
                */
                if(0u != (locIntrSlave & `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH))
                {
                    `$Cond`if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE)
                    {
                        /* Read address byte from RX FIFO */
                        locByte = `$INSTANCE_NAME`_GET_I2C_7BIT_ADDRESS(`$INSTANCE_NAME`_RX_FIFO_RD_REG);

                        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);

                        /* Check received address against device addresses */
                        if(`$INSTANCE_NAME`_addrBuf1 == locByte)
                        {
                            /* Set buffer exposed to primary slave address */
                            `$INSTANCE_NAME`_dataBuffer = `$INSTANCE_NAME`_dataBuffer1;
                            `$INSTANCE_NAME`_bufSizeBuf = `$INSTANCE_NAME`_bufSizeBuf1;
                            `$INSTANCE_NAME`_protectBuf = `$INSTANCE_NAME`_protectBuf1;

                            activeAddress = `$INSTANCE_NAME`_EZI2C_ACTIVE_ADDRESS1;
                        }
                        else if(`$INSTANCE_NAME`_addrBuf2 == locByte)
                        {
                            /* Set buffer exposed to secondary slave address */
                            `$INSTANCE_NAME`_dataBuffer = `$INSTANCE_NAME`_dataBuffer2;
                            `$INSTANCE_NAME`_bufSizeBuf = `$INSTANCE_NAME`_bufSizeBuf2;
                            `$INSTANCE_NAME`_protectBuf = `$INSTANCE_NAME`_protectBuf2;

                            activeAddress = `$INSTANCE_NAME`_EZI2C_ACTIVE_ADDRESS2;
                        }
                        else
                        {
                            /* Address does not match */
                            ackResponse = `$INSTANCE_NAME`_EZI2C_NACK_RECEIVED_ADDRESS;
                        }
                    }
                    `$EndCond`

                #if(`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST)
                    if(`$INSTANCE_NAME`_EZI2C_NACK_RECEIVED_ADDRESS == ackResponse)
                    {
                        /* Clear interrupt sources before NACK address */
                        `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
                        `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);

                    #if(!`$INSTANCE_NAME`_CY_SCBIP_V0)
                        /* Disable INTR_I2C_STOP to not trigger after matched address is NACKed. Ticket ID#156094 */
                        `$INSTANCE_NAME`_DISABLE_INTR_SLAVE(`$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP);
                    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

                        /* NACK address byte: it does not match neither primary nor secondary */
                        `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK;
                    }
                    else
                #endif /* (`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE_CONST) */
                    {

                    #if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
                        if(!`$INSTANCE_NAME`_SECONDARY_ADDRESS_ENABLE)
                        {
                            /* Set buffer exposed to primary slave address */
                            `$INSTANCE_NAME`_dataBuffer = `$INSTANCE_NAME`_dataBuffer1;
                            `$INSTANCE_NAME`_bufSizeBuf = `$INSTANCE_NAME`_bufSizeBuf1;
                            `$INSTANCE_NAME`_protectBuf = `$INSTANCE_NAME`_protectBuf1;

                            activeAddress = `$INSTANCE_NAME`_EZI2C_ACTIVE_ADDRESS1;
                        }
                    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

                        /* Bus becomes busy after address is received */
                        `$INSTANCE_NAME`_curStatus |= (uint8) `$INSTANCE_NAME`_EZI2C_STATUS_BUSY;

                        /* Slave is read or written: set current offset */
                        locIndex = `$INSTANCE_NAME`_EZI2C_GET_OFFSET(activeAddress);

                        /* Check transaction direction */
                        if(`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_S_READ))
                        {
                            /* Calculate slave buffer size */
                            locBufSize = `$INSTANCE_NAME`_bufSizeBuf`$BufNum` - (uint16) locIndex;

                            /* Clear TX FIFO to start fill from offset */
                            `$INSTANCE_NAME`_CLEAR_TX_FIFO;
                            `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_EMPTY);
                        }
                        else
                        {
                            /* Master writes: enable reception interrupt. The FSM state was set in INTR_SLAVE_I2C_STOP */
                            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
                        }

                        /* Clear interrupt sources before ACK address */
                        `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
                        `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);

                    #if (!`$INSTANCE_NAME`_CY_SCBIP_V0)
                        /* Enable STOP to trigger after address match is ACKed. Ticket ID#156094 */
                        `$INSTANCE_NAME`_ENABLE_INTR_SLAVE(`$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP);
                    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

                        /* ACK the address byte */
                        `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_ACK;
                    }
                }

                /* Clear slave interrupt sources */
                `$INSTANCE_NAME`_ClearSlaveInterruptSource(locIntrSlave);
            }

            /* INTR_TX.EMPTY */
            /* Transmits data to the master: loads data into the TX FIFO. The 0xFF sends out if the master reads
            * out the buffer. The address reception with a read flag clears the TX FIFO to be loaded with data.
            */
            if(0u != (`$INSTANCE_NAME`_GetInterruptCause() & `$INSTANCE_NAME`_INTR_CAUSE_TX))
            {
                /* Put data into TX FIFO until there is a room */
                do
                {
                    /* Check transmit buffer range: locBufSize calculates after address reception */
                    if(0u != locBufSize)
                    {
                        `$INSTANCE_NAME`_TX_FIFO_WR_REG = (uint32) `$INSTANCE_NAME`_dataBuffer`$BufNum`[locIndex];
                        locIndex++;
                        locBufSize--;
                    }
                    else
                    {
                        `$INSTANCE_NAME`_TX_FIFO_WR_REG = `$INSTANCE_NAME`_EZI2C_OVFL_RETURN;
                    }
                }
                while(`$INSTANCE_NAME`_EZI2C_FIFO_SIZE != `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES);

                `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_EMPTY);
            }
        }

        /* Store local index copy into global variable */
        `$INSTANCE_NAME`_EZI2C_SET_INDEX(activeAddress, locIndex);

    #ifdef `$INSTANCE_NAME`_EZI2C_STRETCH_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EZI2C_STRETCH_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EZI2C_STRETCH_ISR_EXIT_CALLBACK */

    }
#endif /* (`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_ENABLE_CONST) */


#if(`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_DISABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR
    ****************************************************************************//**
    *
    *  Handles the Interrupt Service Routine for the SCB EZI2C mode.
    *  Clock stretching is NOT used during operation.
    *
    *******************************************************************************/
    CY_ISR_PROTO(`$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR)
    {
    #if(`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16_CONST)
        static uint8 locOffset;
    #endif /* (`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16_CONST) */

        uint32 locByte;
        uint32 locStatus;
        uint32 locIntrSlave;
        uint32 locIntrCause;

    #ifdef `$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR_ENTRY_CALLBACK */

    #if !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER)
        /* Calls registered customer routine to manage interrupt sources */
        if(NULL != `$INSTANCE_NAME`_customIntrHandler)
        {
            `$INSTANCE_NAME`_customIntrHandler();
        }
    #else
        CY_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER();
    #endif /* !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER) */

        locByte = 0u;

        /* Get copy of triggered slave interrupt sources */
        locIntrSlave = `$INSTANCE_NAME`_GetSlaveInterruptSource();
        locIntrCause = `$INSTANCE_NAME`_GetInterruptCause();

        /* INTR_SLAVE.I2C_ARB_LOST and INTR_SLAVE.I2C_BUS_ERROR */
        /* Handles errors on the bus: There are cases when both bits are set.
        * The error recovery is common: re-enable the scb IP. The content of the RX FIFO is lost.
        */
        if(0u != (locIntrSlave & (`$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST |
                                  `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR)))
        {
            `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED; /* Disable SCB block */

        #if (`$INSTANCE_NAME`_CY_SCBIP_V0)
            if(0u != (locIntrSlave & `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH))
        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */
            {
                `$INSTANCE_NAME`_curStatus |= (uint8) `$INSTANCE_NAME`_EZI2C_STATUS_ERR;

                if(0u != (`$INSTANCE_NAME`_EZI2C_FSM_WRITE_MASK & `$INSTANCE_NAME`_fsmState))
                {
                    /* Write complete */
                    if(`$INSTANCE_NAME`_indexBuf1 != `$INSTANCE_NAME`_offsetBuf1)
                    {
                        `$INSTANCE_NAME`_curStatus |= (uint8) `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP;
                    }
                }
                else
                {
                    /* Read complete */
                    `$INSTANCE_NAME`_curStatus |= (uint8) `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK;
                }
            }

            /* Clean-up interrupt sources */
            `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

        #if (`$INSTANCE_NAME`_CY_SCBIP_V0)
            /* Clear interrupt sources as they are not automatically cleared after SCB is disabled */
            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
            `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);
        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

            `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_IDLE;

            `$INSTANCE_NAME`_CTRL_REG |= (uint32) `$INSTANCE_NAME`_CTRL_ENABLED;  /* Enable SCB block */
        }
        else
        {
            /* INTR_RX.NOT_EMPTY */
            /* The slave receives data from the master: accepts into the RX FIFO. At least one entry is available to be
            * read. The offset is written first and all the following bytes are data (expected to be put in the buffer).
            * The slave ACKs all bytes, but it discards them if they do not match the write criteria.
            * The slave NACKs the bytes in the case of an RX FIFO overflow.
            */
            if(0u != (locIntrCause & `$INSTANCE_NAME`_INTR_CAUSE_RX))
            {
                /* Read byte from the RX FIFO */
                locByte = `$INSTANCE_NAME`_RX_FIFO_RD_REG;

                switch(`$INSTANCE_NAME`_fsmState)
                {

                case `$INSTANCE_NAME`_EZI2C_FSM_BYTE_WRITE:
                    /* Check buffer index against protect area */
                    if(`$INSTANCE_NAME`_indexBuf1 < `$INSTANCE_NAME`_protectBuf1)
                    {
                        /* Stores received byte into buffer */
                        `$INSTANCE_NAME`_dataBuffer1[`$INSTANCE_NAME`_indexBuf1] = (uint8) locByte;
                        `$INSTANCE_NAME`_indexBuf1++;
                    }
                    else
                    {
                        /* Discard current byte and sets FSM state to discard following bytes */
                        `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_WAIT_STOP;
                    }

                    break;

            #if(`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16_CONST)
                case `$INSTANCE_NAME`_EZI2C_FSM_OFFSET_HI8:

                    /* Store high byte of offset */
                    locOffset = (uint8) locByte;

                    `$INSTANCE_NAME`_fsmState  = `$INSTANCE_NAME`_EZI2C_FSM_OFFSET_LO8;

                    break;
            #endif /* (`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16_CONST) */

                case `$INSTANCE_NAME`_EZI2C_FSM_OFFSET_LO8:

                    `$Cond`if(`$INSTANCE_NAME`_SUB_ADDRESS_SIZE16)
                    {
                        /* Append offset with high byte */
                        locByte = ((uint32) ((uint32) locOffset << 8u)) | locByte;
                    }
                    `$EndCond`

                    /* Check if offset within buffer range */
                    if(locByte < (uint32) `$INSTANCE_NAME`_bufSizeBuf1)
                    {
                        /* Store and sets received offset */
                        `$INSTANCE_NAME`_offsetBuf1 = (`$EzI2cBitWidthReplacementString`) locByte;
                        `$INSTANCE_NAME`_indexBuf1  = (uint16) locByte;

                        /* Move FSM to data receive state */
                        `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_BYTE_WRITE;
                    }
                    else
                    {
                        /* Reset index due to TX FIFO fill */
                        `$INSTANCE_NAME`_indexBuf1 = (uint16) `$INSTANCE_NAME`_offsetBuf1;

                        /* Discard current byte and sets FSM state to default to discard following bytes */
                        `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_WAIT_STOP;
                    }

                    break;

                case `$INSTANCE_NAME`_EZI2C_FSM_WAIT_STOP:
                    /* Clear RX FIFO to discard all received data */
                    `$INSTANCE_NAME`_CLEAR_RX_FIFO;

                    break;

                default:
                    CYASSERT(0u != 0u); /* Should never get there */
                    break;
                }

                `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
            }


            /* INTR_SLAVE.I2C_START */
            /* Catches start of transfer to trigger TX FIFO update event */
            if(0u != (locIntrSlave & `$INSTANCE_NAME`_INTR_SLAVE_I2C_START))
            {
            #if(!`$INSTANCE_NAME`_CY_SCBIP_V0)
                `$Cond`if(`$INSTANCE_NAME`_EZI2C_EC_AM_ENABLE)
                {
                    /* Manage INTR_I2C_EC.WAKE_UP as slave busy status */
                    `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
                }
                `$Cond`else
                {
                    /* Manage INTR_SLAVE.I2C_ADDR_MATCH as slave busy status */
                    `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH);
                }
                `$EndCond`
            #else
                /* Manage INTR_SLAVE.I2C_ADDR_MATCH as slave busy status */
                `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH);
            #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

                /* Clear TX FIFO and put a byte */
                `$INSTANCE_NAME`_FAST_CLEAR_TX_FIFO;
                `$INSTANCE_NAME`_TX_FIFO_WR_REG = (uint32) `$INSTANCE_NAME`_dataBuffer1[`$INSTANCE_NAME`_offsetBuf1];

                /* Store buffer index to be handled by INTR_SLAVE.I2C_STOP */
                locByte = (uint32) `$INSTANCE_NAME`_indexBuf1;

                /* Update index: one byte is already in the TX FIFO */
                `$INSTANCE_NAME`_indexBuf1 = (uint16) `$INSTANCE_NAME`_offsetBuf1 + 1u;

                /* Enable INTR_TX.NOT_FULL to load TX FIFO */
                `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_TRIGGER);

                /* Clear locIntrSlave after INTR.TX_TRIGGER is enabled */
                `$INSTANCE_NAME`_ClearSlaveInterruptSource(locIntrSlave);

                locIntrCause |= `$INSTANCE_NAME`_INTR_CAUSE_TX;
            }


            /* INTR_TX.TRIGGER */
            /* Transmits data to the master: loads data into the TX FIFO. The TX FIFO is loaded with data
            *  until used entries are less than `$INSTANCE_NAME`_TX_LOAD_SIZE. If index reaches end of the
            *  buffer the 0xFF is sent to the end of transfer.
            */
            if(0u != (locIntrCause & `$INSTANCE_NAME`_INTR_CAUSE_TX))
            {
                /* Put data into TX FIFO until there is room */
                do
                {
                    /* Check transmit buffer range */
                    if(`$INSTANCE_NAME`_indexBuf1 < `$INSTANCE_NAME`_bufSizeBuf1)
                    {
                        `$INSTANCE_NAME`_TX_FIFO_WR_REG = (uint32) `$INSTANCE_NAME`_dataBuffer1[`$INSTANCE_NAME`_indexBuf1];
                        `$INSTANCE_NAME`_indexBuf1++;
                    }
                    else
                    {
                        `$INSTANCE_NAME`_TX_FIFO_WR_REG = `$INSTANCE_NAME`_EZI2C_OVFL_RETURN;
                    }

                }
                while(`$INSTANCE_NAME`_TX_LOAD_SIZE != `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES);

                `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_TRIGGER);
            }


            /* INTR_SLAVE.I2C_STOP */
            /* Catch completion of write or read transfer. */
            if(0u != (locIntrSlave & `$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP))
            {
                if(0u == (locIntrSlave & `$INSTANCE_NAME`_INTR_SLAVE_I2C_START))
                {
                #if(!`$INSTANCE_NAME`_CY_SCBIP_V0)
                    `$Cond`if(`$INSTANCE_NAME`_EZI2C_EC_AM_ENABLE)
                    {
                        /* Manage INTR_I2C_EC.WAKE_UP as slave busy status */
                        `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
                    }
                    `$EndCond`
                #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

                    /* Manage INTR_SLAVE.I2C_ADDR_MATCH as slave busy status */
                    `$INSTANCE_NAME`_ClearSlaveInterruptSource(locIntrSlave);

                    /* Read current buffer index */
                    locByte = (uint32) `$INSTANCE_NAME`_indexBuf1;
                }

                /* Set read completion mask */
                locStatus = `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK;

                if((locByte != `$INSTANCE_NAME`_offsetBuf1) &&
                   (0u != (`$INSTANCE_NAME`_EZI2C_FSM_WRITE_MASK & `$INSTANCE_NAME`_fsmState)))
                {
                    /* Set write completion mask */
                    locStatus |= `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP;
                }

                /* Set completion flags in the status variable */
                `$INSTANCE_NAME`_curStatus |= (uint8) (locStatus & locIntrSlave);

                `$INSTANCE_NAME`_fsmState = `$INSTANCE_NAME`_EZI2C_FSM_IDLE;
            }


        #if(!`$INSTANCE_NAME`_CY_SCBIP_V0)
            `$Cond`if(`$INSTANCE_NAME`_EZI2C_EC_AM_ENABLE)
            {
                /* INTR_I2C_EC.WAKE_UP */
                /* Wake up device from deep sleep on address match event. The matched address is NACKed */
                if(0u != (locIntrCause & `$INSTANCE_NAME`_INTR_CAUSE_I2C_EC))
                {
                    `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK; /* NACK in active mode */
                    `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
                }
            }
            `$EndCond`
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */
        }

    #ifdef `$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EZI2C_NO_STRETCH_ISR_EXIT_CALLBACK */

    }
#endif /* (`$INSTANCE_NAME`_EZI2C_SCL_STRETCH_DISABLE_CONST) */


/* [] END OF FILE */
