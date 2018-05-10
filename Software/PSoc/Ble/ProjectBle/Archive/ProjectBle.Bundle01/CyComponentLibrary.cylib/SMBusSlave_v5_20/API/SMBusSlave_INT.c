/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of the Interrupt Service Routine (ISR)
*  for the SM/PMBus component.
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

static uint8 `$INSTANCE_NAME`_isCmdReceived = 0u;
static uint8 `$INSTANCE_NAME`_error = 0u;
        
        
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR
********************************************************************************
*
* Summary:
*  The Interrupt Service Routine for the SM/PMBus Interrupt.
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
CY_ISR(`$INSTANCE_NAME`_ISR)
{
    /* Computed CRC value (after the process runs). For each byte received in a 
    * packet a new CRC is computed. For the first byte in a packet the CRC is
    * reset. The last byte in a packet is a CRC  (PEC) for the packet. The 
    * received PEC is compared with a computed CRC to verify the correctness of
	* the PEC.
    */
    #if (`$INSTANCE_NAME`_SUPPORT_PEC)
        static uint8 `$INSTANCE_NAME`_crc_value = 0u;
    #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */

    uint8 tmpCsr;   /* Local copy of I2C Control/Status Register */
    uint8 newByte;  /* Data byte received in given transaction */

    #ifdef `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK */

    /* Add your custom code between the following #START and #END tags */
    /* `#START ISR_ENTRY_REGION` */

    /* `#END` */
    
    tmpCsr = `$INSTANCE_NAME`_I2C_CSR_REG;   /* Make copy as interrupts clear */

    /* Complete write transaction and execute command if Stop bit was received */
    if(`$INSTANCE_NAME`_I2C_CHECK_STOP_STS(tmpCsr))
    {
        /* The component detects any Stop condition on the bus. Therefore an
        * additional check of the internal FSM state is required to determine
        * whether the host finishes the transaction to the component.
        */
        if(`$INSTANCE_NAME`_I2C_SM_SL_WR_DATA == `$INSTANCE_NAME`_I2C_state)
        {
            `$INSTANCE_NAME`_I2C_DISABLE_INT_ON_STOP;
            `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_SM_IDLE;
            
            /* Process and execute command */
            `$INSTANCE_NAME`_isCmdReceived = 0u;
            if(0u == `$INSTANCE_NAME`_error)
            {
                `$INSTANCE_NAME`_WriteHandler();
            }
            else
            {
                `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_error);
            }
        }
    }

    if(`$INSTANCE_NAME`_I2C_CHECK_BYTE_COMPLETE(tmpCsr))
    {
        if(`$INSTANCE_NAME`_I2C_CHECK_ADDRESS_STS(tmpCsr))
        {            
            newByte = `$INSTANCE_NAME`_I2C_DATA_REG;

        #if (`$INSTANCE_NAME`_SW_ADDR_DECODE)
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
                
                /* Check for read or write transaction */
                if(0u != (newByte & `$INSTANCE_NAME`_I2C_READ_FLAG))
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

                            /* If command is not received, service the receive byte protocol.
                            * Call user defined API to provide data byte for this transaction.
                            */
                            `$INSTANCE_NAME`_buffer[0u] = `$INSTANCE_NAME`_GetReceiveByteResponse();
                            `$INSTANCE_NAME`_I2C_DATA_REG = `$INSTANCE_NAME`_buffer[0u];
                            `$INSTANCE_NAME`_I2C_ACK_AND_TRANSMIT;
                            `$INSTANCE_NAME`_bufferSize = 1u;
                        #else
                            `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_ERR_READ_FLAG;
                        #endif /*`$INSTANCE_NAME`_SMBUS_MODE && `$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED */
                    }
                    if(0u != `$INSTANCE_NAME`_error)
                    {
                        /* Data Content Fault. Send FFh as host keeps clocking. */
                        `$INSTANCE_NAME`_I2C_DATA_REG = 0xFFu;
                        `$INSTANCE_NAME`_I2C_ACK_AND_TRANSMIT;
                    }
                    `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_SM_SL_RD_DATA;
                }
                else  /* Start of Write transaction, ready to write first byte */
                { 
                    `$INSTANCE_NAME`_I2C_ENABLE_INT_ON_STOP;
                    `$INSTANCE_NAME`_I2C_ACK_AND_RECEIVE;
                    `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_SM_SL_WR_DATA;
                }
                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    `$INSTANCE_NAME`_crc_value = `$INSTANCE_NAME`_crc_table[newByte];
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */

                `$INSTANCE_NAME`_bufferIndex = 0u; /* Reset buffer index */
            }
        #if(`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)
            /* When SMBALERT# pin is exposed in the component, it is required
            * to monitor if the master is broadcasting the Alert Response Address.
            * If ARA was detected and SMBALERT# pin is asserted by the device,
            * respond with the device address and handle SMBALERT# pin.
            */
            else if((0u == `$INSTANCE_NAME`_SMBALERT_PIN_REG) && (newByte == `$INSTANCE_NAME`_alertResponseAddress))
            {
                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    `$INSTANCE_NAME`_crc_value  = `$INSTANCE_NAME`_crc_table[newByte];
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
            
                `$INSTANCE_NAME`_I2C_DATA_REG = `$INSTANCE_NAME`_address;
                `$INSTANCE_NAME`_I2C_ACK_AND_TRANSMIT;
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
                
                /* Move to Read Data state to send last byte (0xFF) */
                `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_SM_SL_RD_DATA;
                `$INSTANCE_NAME`_bufferIndex = 0u;  /* Reset buffer index */
            }
        #endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */
            
        #if (`$INSTANCE_NAME`_SW_ADDR_DECODE)
            else /* No address match */
            {
                `$INSTANCE_NAME`_I2C_NAK_AND_RECEIVE;   /* NACK received address */
            }
        #endif /* `$INSTANCE_NAME`_SW_ADDR_DECODE */

        }

        /* Write transaction from master to slave */
        else if(`$INSTANCE_NAME`_I2C_SM_SL_WR_DATA == `$INSTANCE_NAME`_I2C_state)
        {
             newByte = `$INSTANCE_NAME`_I2C_DATA_REG;

            /* Check if command code was received and supported */
            if(0u == `$INSTANCE_NAME`_isCmdReceived)
            {
                `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_CheckCommand(newByte);
                `$INSTANCE_NAME`_isCmdReceived = 1u;
            }
            /* Data portion of write transaction */
            else
            {
                if(`$INSTANCE_NAME`_bufferIndex < `$INSTANCE_NAME`_bufferSize)
                {
                    `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_bufferIndex] = newByte;
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
                `$INSTANCE_NAME`_I2C_ACK_AND_RECEIVE;
                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    `$INSTANCE_NAME`_crc_value ^= newByte;
                    `$INSTANCE_NAME`_crc_value = `$INSTANCE_NAME`_crc_table[`$INSTANCE_NAME`_crc_value];
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
            }
            else /* NACK received byte */
            {
                `$INSTANCE_NAME`_I2C_NAK_AND_RECEIVE;
            }
        }
        /* Read transaction from slave to master */
        else if(`$INSTANCE_NAME`_I2C_SM_SL_RD_DATA == `$INSTANCE_NAME`_I2C_state)
        {
            if(`$INSTANCE_NAME`_I2C_CHECK_DATA_ACK(tmpCsr))
            {
                if(0u == `$INSTANCE_NAME`_error)
                {
                    #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                        `$INSTANCE_NAME`_crc_value ^= `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_bufferIndex];
                        `$INSTANCE_NAME`_crc_value = `$INSTANCE_NAME`_crc_table[`$INSTANCE_NAME`_crc_value];
                    #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
                    
                    /* First byte is sent in address state. Increment index to next byte. */
                    ++`$INSTANCE_NAME`_bufferIndex;
                    if(`$INSTANCE_NAME`_bufferIndex < `$INSTANCE_NAME`_bufferSize)
                    {
                        `$INSTANCE_NAME`_I2C_DATA_REG = `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_bufferIndex];
                    }
                #if (`$INSTANCE_NAME`_SUPPORT_PEC)
                    else if(`$INSTANCE_NAME`_bufferIndex == `$INSTANCE_NAME`_bufferSize)
                    {
                        /* Last data byte was sent. Supply PEC. */
                        `$INSTANCE_NAME`_I2C_DATA_REG = `$INSTANCE_NAME`_crc_value;
                    }
                #endif /* `$INSTANCE_NAME`_SUPPORT_PEC */
                    else /* Master attempts to read to many bytes. Send 0xFF and ACK */
                    {
                        `$INSTANCE_NAME`_I2C_DATA_REG = 0xFFu;
                        `$INSTANCE_NAME`_error = `$INSTANCE_NAME`_ERR_RD_TO_MANY_BYTES;
                    }
                }
                else /* Data Content Fault. Send 0xFF and ACK */
                {
                    `$INSTANCE_NAME`_I2C_DATA_REG = 0xFFu;
                }
                `$INSTANCE_NAME`_I2C_TRANSMIT_DATA;
            }
            else  /* Last byte NACKed, done */
            {                
                `$INSTANCE_NAME`_I2C_DATA_REG = 0xFFu;
                `$INSTANCE_NAME`_I2C_NAK_AND_TRANSMIT;
                `$INSTANCE_NAME`_I2C_DISABLE_INT_ON_STOP;
                `$INSTANCE_NAME`_I2C_state = `$INSTANCE_NAME`_I2C_SM_IDLE;
                
                #ifdef `$INSTANCE_NAME`_BTLDR_READ_EN
                    `$INSTANCE_NAME`_btldrStatus |= `$INSTANCE_NAME`_BTLDR_RD_CMPT;
                #endif /* `$INSTANCE_NAME`_BTLDR_READ_EN */
                
                `$INSTANCE_NAME`_isCmdReceived = 0u;
                if(`$INSTANCE_NAME`_error != 0u)
                {
                    `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_error);
                    `$INSTANCE_NAME`_error = 0u;
                }
            }
        }
        else /* This is invalid state and should not occur */
        {
            `$INSTANCE_NAME`_I2C_NAK_AND_RECEIVE;
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
    
    `$INSTANCE_NAME`_I2C_Stop();
    
    /* Inform user that timeout occurred */
    `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_ERR_TIMEOUT);
    
    /* Reset all variables */
    `$INSTANCE_NAME`_trActiveCount = 0u;
    `$INSTANCE_NAME`_isCmdReceived = 0u;
    `$INSTANCE_NAME`_error = 0u;
    `$INSTANCE_NAME`_I2C_Enable();
    `$INSTANCE_NAME`_EnableInt();

    #ifdef `$INSTANCE_NAME`_TIMEOUT_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_TIMEOUT_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_TIMEOUT_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
