/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version 2.30
*
* Description:
*  This file provides the source code of the Interrupt Service Routine (ISR)
*  for the SM/PM Bus component.
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/* User section to add header files and variable declarations */
/*`#START VAR_INCLUDE_REGION`*/

/*`#END`*/

static void `$INSTANCE_NAME`_ResetBus(void);

static uint8 `$INSTANCE_NAME`_isCmdReceived = 0u; /* Indicates if command was received */
static uint8 `$INSTANCE_NAME`_error = 0u;         /* Error code or zero if no errors detected */ 
static uint8 `$INSTANCE_NAME`_rdOverflowCnt = 0u; /* Determines how many extra bytes were loaded in TX FIFO */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2C_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB I2C mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_ISR)
{   
    /* Computed CRC value (after the process runs). For each byte received in a 
    * packet a new CRC is computed. For the first byte in a packet the CRC is
    * reset. The last byte in a packet is a CRC  (PEC) for the packet. The
    * received PEC is compared with a computed CRC to verify the correctness of
	* PEC.
    */
    #if (`$INSTANCE_NAME`_SUPPORT_PEC)
        static uint8 `$INSTANCE_NAME`_crc_value = 0u;
    #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
    
    uint32 diffCount;
    uint32 newByte;
    uint32 intSource;
    
    #ifdef `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK */
    
    /* Add your custom code between the following #START and #END tags */
    /* `#START ISR_ENTRY_REGION` */

    /* `#END` */

    intSource = `$INSTANCE_NAME`_I2C_INTR_SLAVE_REG;

    /* INTR_SLAVE_I2C_BUS_ERROR or `$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_ARB_LOST:
    * Misplaced Start or Stop condition occurred on bus.
    */
    if(0u != (intSource & (`$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_BUS_ERROR |
                           `$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_ARB_LOST)))
    {
        `$INSTANCE_NAME`_ResetBus();
    }
    else
    {
        /* NACK: Host completes read. Complete transaction and clear flags */
        if(0u != (intSource & `$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_NACK))
        {
            `$INSTANCE_NAME`_I2C_ClearSlaveInterruptSource(`$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_NACK);

            /* If no Data Content faults were detected, determine reason for 
            * TX_FIFO overflow. False overflow condition may occur due to
            * use of TX_EMPTY status as interrupt source for data transmission.
            */
            if(0u == `$INSTANCE_NAME`_error)
            {
                /* All entries from TX FIFO. Max value is 9: 8 (FIFO) + 1 (SHIFTER) */
                diffCount = (`$INSTANCE_NAME`_I2C_GET_TX_FIFO_ENTRIES + `$INSTANCE_NAME`_I2C_GET_TX_FIFO_SR_VALID);
                if(diffCount < `$INSTANCE_NAME`_rdOverflowCnt)
                {
                    `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_ERR_RD_TO_MANY_BYTES);
                }
            }
            else
            {
                `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_error);
                `$INSTANCE_NAME`_error = 0u;
            }
            `$INSTANCE_NAME`_isCmdReceived = 0u;
            
            #ifdef `$INSTANCE_NAME`_BTLDR_READ_EN
                `$INSTANCE_NAME`_btldrStatus |= `$INSTANCE_NAME`_BTLDR_RD_CMPT;
            #endif /* `$INSTANCE_NAME`_BTLDR_READ_EN */
            
            /* Cleanup TX FIFO */
            `$INSTANCE_NAME`_rdOverflowCnt = 0u;
            `$INSTANCE_NAME`_I2C_SetTxInterruptMode(`$INSTANCE_NAME`_I2C_NO_INTR_SOURCES); 
            `$INSTANCE_NAME`_I2C_CLEAR_TX_FIFO;
            `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_I2C_FSM_IDLE;
        }

        /* WRITE_STOP: Host completes write. Complete transaction or report error */
        if(0u != (intSource & `$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_WRITE_STOP))
        {
            `$INSTANCE_NAME`_I2C_ClearSlaveInterruptSource(`$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_WRITE_STOP);
            `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_I2C_FSM_IDLE;
            
            /* If delayed stop or not restart, complete write */
            if(((0u != (intSource & `$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_ADDR_MATCH)) && 
              (!`$INSTANCE_NAME`_I2C_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_I2C_STATUS_S_READ))) ||
              (0u == (intSource & `$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_START)))
            {
                if(0u == `$INSTANCE_NAME`_error)
                {
                    `$INSTANCE_NAME`_WriteHandler();
                }
                else
                {
                    `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_error);
                    `$INSTANCE_NAME`_error = 0u;
                }
                `$INSTANCE_NAME`_isCmdReceived = 0u;
            }
            `$INSTANCE_NAME`_I2C_SetRxInterruptMode(`$INSTANCE_NAME`_I2C_NO_INTR_SOURCES);
        }

        /* ADDR_MATCH: Determine direction of a transfer */
        if(0u != (intSource & `$INSTANCE_NAME`_I2C_INTR_SLAVE_I2C_ADDR_MATCH))
        {   
            `$INSTANCE_NAME`_I2C_ClearSlaveInterruptSource(`$INSTANCE_NAME`_I2C_INTR_SLAVE_ALL);
    
            newByte = `$INSTANCE_NAME`_I2C_RX_FIFO_RD_REG;
            `$INSTANCE_NAME`_I2C_ClearRxInterruptSource(`$INSTANCE_NAME`_I2C_INTR_RX_ALL);

        #if(`$INSTANCE_NAME`_SW_ADDR_DECODE) /* Check for address match. Address in RX FIFO */
            if(((newByte & `$INSTANCE_NAME`_ADDR_MASK) == `$INSTANCE_NAME`_address) ||
                (newByte == `$INSTANCE_NAME`_GENERAL_CALL_ADDR))
        #endif /* `$INSTANCE_NAME`_SW_ADDR_DECODE */
            {
                /* Add your custom code between the following #START and #END tags */
                /* `#START PRIMARY_ADDRESS_MATCH_REGION` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_PRIMARY_ADDRESS_MATCH_CALLBACK
                    `$INSTANCE_NAME`_ISR_PrimaryAddressMatch_Callback();
                #endif /* `$INSTANCE_NAME`_PRIMARY_ADDRESS_MATCH_CALLBACK */
                
                /* Determine direction for transaction */
                if(`$INSTANCE_NAME`_I2C_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_I2C_STATUS_S_READ))
                {
                    if(0u != `$INSTANCE_NAME`_isCmdReceived)
                    {
                        /* Determine if the received command is supported */
                        if(0u == `$INSTANCE_NAME`_error)
                        {
                            `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_ReadHandler();
                            #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                                newByte ^= `$INSTANCE_NAME`_crc_value;
                            #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
                        }
                    }
                    else
                    {
                        #if(`$INSTANCE_NAME`_SMBUS_MODE && `$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED)

                            /* If command is not received, service receive byte protocol.
                            * Call user defined API to provide data byte for this transaction.
                            */
                            `$INSTANCE_NAME`_buffer[0u] = `$INSTANCE_NAME`_GetReceiveByteResponse();
                            `$INSTANCE_NAME`_I2C_SetTxInterruptMode(`$INSTANCE_NAME`_I2C_INTR_TX_EMPTY);
                            `$INSTANCE_NAME`_bufferSize = 1u;
                        #else
                            `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_ERR_READ_FLAG;
                        #endif /*`$INSTANCE_NAME`_SMBUS_MODE && `$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED */
                    }
                    if(0u != `$INSTANCE_NAME`_error)
                    {
                        /* Data Content Fault. Send FFh as host keeps clocking. */
                        `$INSTANCE_NAME`_I2C_SetTxInterruptMode(`$INSTANCE_NAME`_I2C_INTR_TX_EMPTY);
                    }
                    `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_I2C_FSM_SL_RD;
                }
                else /* Write transaction */
                {
                    `$INSTANCE_NAME`_I2C_SetRxInterruptMode(`$INSTANCE_NAME`_I2C_INTR_RX_NOT_EMPTY);
                    `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_I2C_FSM_SL_WR;
                }
                `$INSTANCE_NAME`_I2C_I2C_SLAVE_GENERATE_ACK;

                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    `$INSTANCE_NAME`_crc_value = `$INSTANCE_NAME`_crc_table[newByte];
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
            }
        #if(`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)
            /* When SMBALERT# pin is exposed in the component it is required
            * to monitor if the master is broadcasting the Alert Response Address.
            * If ARA was detected and SMBALERT# pin is asserted by the device,
            * respond with the device address and handle SMBALERT# pin.
            */
            else if((0u == (`$INSTANCE_NAME`_SMBALERT_PIN_REG & `$INSTANCE_NAME`_SMBALERT_PIN_MASK)) &&
                    (newByte == `$INSTANCE_NAME`_alertResponseAddress))
            {
                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    `$INSTANCE_NAME`_crc_value  = `$INSTANCE_NAME`_crc_table[newByte];
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */

                `$INSTANCE_NAME`_I2C_I2C_SLAVE_GENERATE_ACK;
                `$INSTANCE_NAME`_buffer[0u] = `$INSTANCE_NAME`_address;
                `$INSTANCE_NAME`_bufferSize = 1u;
                switch(`$INSTANCE_NAME`_smbAlertMode)
                {
                case `$INSTANCE_NAME`_AUTO_MODE:  
                    `$INSTANCE_NAME`_SetSmbAlert(1u); /* De-assert SMBALERT# pin (active low) */
                    break;
                case `$INSTANCE_NAME`_MANUAL_MODE:
                    `$INSTANCE_NAME`_HandleSmbAlertResponse(); /* Call user provided API to handle SMBALERT# pin */
                    break;
                default:
                    break;  /* DO_NOTHING mode: component takes no action */
                }
                `$INSTANCE_NAME`_I2C_SetTxInterruptMode(`$INSTANCE_NAME`_I2C_INTR_TX_EMPTY);
                `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_I2C_FSM_SL_RD;
            }
        #endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */
        
        #if(`$INSTANCE_NAME`_SW_ADDR_DECODE)
            else /* No address match */
            {
                `$INSTANCE_NAME`_I2C_I2C_SLAVE_GENERATE_NACK;   /* NACK received address */
            }
        #endif /* `$INSTANCE_NAME`_SW_ADDR_DECODE */
        
            `$INSTANCE_NAME`_bufferIndex = 0u; /* Reset buffer index */
        }

        /* RX_NOT_EMPTY: Master writes to slave. Put data into buffer. */
        if(`$INSTANCE_NAME`_I2C_CHECK_INTR_RX_MASKED(`$INSTANCE_NAME`_I2C_INTR_RX_NOT_EMPTY))
        {
            newByte = `$INSTANCE_NAME`_I2C_RX_FIFO_RD_REG;
            if(0u == `$INSTANCE_NAME`_isCmdReceived) /* Check if a command code was received and supported */
            {
                `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_CheckCommand((uint8)newByte);
                `$INSTANCE_NAME`_isCmdReceived = 1u;
            }
            else /* Data portion of write transaction */
            {
                if(`$INSTANCE_NAME`_bufferIndex < `$INSTANCE_NAME`_bufferSize)
                {
                    `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_bufferIndex] = (uint8)newByte;
                }
            #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                else if(`$INSTANCE_NAME`_bufferIndex == `$INSTANCE_NAME`_bufferSize)
                {
                    if(newByte != `$INSTANCE_NAME`_crc_value)
                    {
                        `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_ERR_CORRUPTED_DATA;
                    }
                }
            #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
                else /* Data Transmission Fault: Host Sends Too Many Bytes */
                {
                    `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_ERR_WR_TO_MANY_BYTES;
                }
                ++`$INSTANCE_NAME`_bufferIndex;
            }
            if(0u == `$INSTANCE_NAME`_error)
            {
                `$INSTANCE_NAME`_I2C_I2C_SLAVE_GENERATE_ACK;

                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    `$INSTANCE_NAME`_crc_value ^= (uint8)newByte;
                    `$INSTANCE_NAME`_crc_value = `$INSTANCE_NAME`_crc_table[`$INSTANCE_NAME`_crc_value];
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
            }
            else /* NACK received byte */
            {
                `$INSTANCE_NAME`_I2C_I2C_SLAVE_GENERATE_NACK;
            }
            `$INSTANCE_NAME`_I2C_ClearRxInterruptSource(`$INSTANCE_NAME`_I2C_INTR_RX_NOT_EMPTY);
        }

        /* TX_EMPTY: Master reads from slave. Provide read data or 0xFF if overflow. */
        if(`$INSTANCE_NAME`_I2C_CHECK_INTR_TX_MASKED(`$INSTANCE_NAME`_I2C_INTR_TX_EMPTY))
        {
            if((0u == `$INSTANCE_NAME`_error) && (`$INSTANCE_NAME`_bufferIndex < `$INSTANCE_NAME`_bufferSize))
            {
                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    `$INSTANCE_NAME`_crc_value ^= `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_bufferIndex];
                    `$INSTANCE_NAME`_crc_value = `$INSTANCE_NAME`_crc_table[`$INSTANCE_NAME`_crc_value];
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
            
                `$INSTANCE_NAME`_I2C_TX_FIFO_WR_REG = (uint32)`$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_bufferIndex];
                ++`$INSTANCE_NAME`_bufferIndex;
            }
        #if (`$INSTANCE_NAME`_SUPPORT_PEC)
            else if((0u == `$INSTANCE_NAME`_error) && (`$INSTANCE_NAME`_bufferIndex == `$INSTANCE_NAME`_bufferSize))
            {
                /* Last data byte was sent. Supply PEC. */
                `$INSTANCE_NAME`_I2C_TX_FIFO_WR_REG = (uint32)`$INSTANCE_NAME`_crc_value;
                ++`$INSTANCE_NAME`_bufferIndex;
            }
        #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
            else
            {
                `$INSTANCE_NAME`_I2C_TX_FIFO_WR_REG = `$INSTANCE_NAME`_I2C_I2C_SLAVE_OVFL_RETURN;
                ++`$INSTANCE_NAME`_rdOverflowCnt;
            }
            `$INSTANCE_NAME`_I2C_ClearTxInterruptSource(`$INSTANCE_NAME`_I2C_INTR_TX_EMPTY);
        }
    }

    #ifdef `$INSTANCE_NAME`_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TIMEOUT_ISR
********************************************************************************
*
* Summary:
*  Handles a bus timeout occurrence event.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_TIMEOUT_ISR)
{
    #ifdef `$INSTANCE_NAME`_TIMEOUT_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_TIMEOUT_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_TIMEOUT_ISR_ENTRY_CALLBACK */
    
    `$INSTANCE_NAME`_ResetBus();

    /* Timeout interrupt is sticky and needs to be manually cleared */
    `$INSTANCE_NAME`_I2C_TMOUT_ClearInterrupt(`$INSTANCE_NAME`_I2C_TMOUT_INTR_MASK_TC);

    /* Inform user that timeout occurred */
    `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_ERR_TIMEOUT);
    
    /* Reset all variables */
    `$INSTANCE_NAME`_trActiveCount = 0u;
    `$INSTANCE_NAME`_isCmdReceived = 0u;
    `$INSTANCE_NAME`_error = 0u;
    `$INSTANCE_NAME`_rdOverflowCnt = 0u;
    
    `$INSTANCE_NAME`_EnableInt();

    #ifdef `$INSTANCE_NAME`_TIMEOUT_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_TIMEOUT_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_TIMEOUT_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ResetBus
********************************************************************************
*
* Summary:
*  Resets the I2C block, all the status and interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ResetBus(void)
{
    `$INSTANCE_NAME`_I2C_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_I2C_CTRL_ENABLED; /* Disable SCB block */

    /* Disable interrupt sources */
    `$INSTANCE_NAME`_I2C_SetRxInterruptMode(`$INSTANCE_NAME`_I2C_NO_INTR_SOURCES);
    `$INSTANCE_NAME`_I2C_SetTxInterruptMode(`$INSTANCE_NAME`_I2C_NO_INTR_SOURCES);
    
    /* Clear interrupt sources */
    `$INSTANCE_NAME`_I2C_ClearTxInterruptSource(`$INSTANCE_NAME`_I2C_INTR_RX_ALL);
    `$INSTANCE_NAME`_I2C_ClearRxInterruptSource(`$INSTANCE_NAME`_I2C_INTR_TX_ALL);
    `$INSTANCE_NAME`_I2C_ClearSlaveInterruptSource(`$INSTANCE_NAME`_I2C_INTR_SLAVE_ALL);

    `$INSTANCE_NAME`_I2C_CTRL_REG |= (uint32) `$INSTANCE_NAME`_I2C_CTRL_ENABLED;  /* Enable SCB block */

    `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_I2C_FSM_IDLE;
}


/* [] END OF FILE */
