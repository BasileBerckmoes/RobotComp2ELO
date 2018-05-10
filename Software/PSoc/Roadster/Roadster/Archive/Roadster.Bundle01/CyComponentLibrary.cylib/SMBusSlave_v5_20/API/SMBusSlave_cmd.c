/*******************************************************************************
* File Name: `$INSTANCE_NAME`_cmd.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code related to SM/PM bus command handling.
*
*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/* I2C Buffer */
uint8   `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_MAX_BUFFER_SIZE];
uint8   `$INSTANCE_NAME`_bufferIndex;
uint8   `$INSTANCE_NAME`_bufferSize;

static uint8   `$INSTANCE_NAME`_cmdPage = 0u;
static uint8 * `$INSTANCE_NAME`_cmdDataPtr;
static uint8   `$INSTANCE_NAME`_cmdProperties;
static uint8   `$INSTANCE_NAME`_lastReceivedCmd;

static void    `$INSTANCE_NAME`_FillTransaction(uint8 command) `=ReentrantKeil($INSTANCE_NAME . "_FillTransaction")`;

`$CmdTableEntry`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckCommand
********************************************************************************
*
* Summary:
*  Looks for a command in the array of supported commands.
*
* Parameters:
*  uint8 command: received command.
*
* Return:
*  `$INSTANCE_NAME`_ERR_UNSUPPORTED_CMD - command not found.
*  `$INSTANCE_NAME`_CMD_VALID - command found.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_CheckCommand(uint8 command) `=ReentrantKeil($INSTANCE_NAME . "_CheckCommand")`
{
    uint8 cmdIdx;

    /* Look for command in array of supported commands */
    for(cmdIdx = 0u; cmdIdx < `$INSTANCE_NAME`_NUM_COMMANDS; ++cmdIdx)
    {
        if(command == `$INSTANCE_NAME`_commands[cmdIdx].command)
        {
            /* Set write pointer to buffer start */
            `$INSTANCE_NAME`_bufferSize      = `$INSTANCE_NAME`_commands[cmdIdx].dataLength;
            `$INSTANCE_NAME`_lastReceivedCmd = command;
            `$INSTANCE_NAME`_cmdProperties   = `$INSTANCE_NAME`_commands[cmdIdx].cmdProp;
            `$INSTANCE_NAME`_cmdDataPtr      = `$INSTANCE_NAME`_commands[cmdIdx].dataPtr;

            /* Local copy of page command from the operating register store */
            #if(0u != `$INSTANCE_NAME`_SUPPORT_PAGE_CMD)
                `$INSTANCE_NAME`_cmdPage = `$INSTANCE_NAME`_regs.PAGE;
            #endif /* 0u != `$INSTANCE_NAME`_SUPPORT_PAGE_CMD */

            /* If PAGE is set to 0xFF, following transactions are treated as errors.
            *    - An attempt to Read from a Paged command
            *    - An attempt to Write to a Paged command that is configured as Auto
            */         
            if(0u != (`$INSTANCE_NAME`_cmdProperties & `$INSTANCE_NAME`_CMD_PAGED))
            {
                if(`$INSTANCE_NAME`_CMD_ALL_PAGES != `$INSTANCE_NAME`_cmdPage)
                {
                    /* Set data pointer to current page */
                    #if(0u != `$INSTANCE_NAME`_SUPPORT_PAGE_CMD)
                        `$INSTANCE_NAME`_cmdDataPtr += (uint16)`$INSTANCE_NAME`_bufferSize * `$INSTANCE_NAME`_cmdPage;
                    #endif /* 0u != `$INSTANCE_NAME`_SUPPORT_PAGE_CMD */
                }
                else if(0u == (`$INSTANCE_NAME`_cmdProperties & `$INSTANCE_NAME`_CMD_WR_AUTO))
                {
                    `$INSTANCE_NAME`_cmdProperties &= (`$INSTANCE_NAME`_CMD_PAGED | `$INSTANCE_NAME`_CMD_WR_MANUAL);
                }
                else
                {
                    `$INSTANCE_NAME`_cmdProperties = 0u;
                }
            }

            break; /* Command found - no need to continue */
        }
    }

    return ((`$INSTANCE_NAME`_NUM_COMMANDS == cmdIdx) ? `$INSTANCE_NAME`_ERR_UNSUPPORTED_CMD : `$INSTANCE_NAME`_CMD_VALID);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CompleteRead
********************************************************************************
*
* Summary:
*  This is a handler for commands that have Read configuration set to "Auto" or
*  "Manual". It copies data from Operating Memory (RAM) into the I2C buffer.
*  For an "Auto" transaction it is called before an address acknowledge at
*  ReStart. For "Manual" it is in the same phase but after
*  `$INSTANCE_NAME`_ReadManualHandler.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_CompleteRead(void) `=ReentrantKeil($INSTANCE_NAME . "_CompleteRead")`
{
    switch(`$INSTANCE_NAME`_lastReceivedCmd)
    {
        `$ReadHandlerCases`

        default:
            break;
    }

    /* For PSoC 4 enable interrupt for TX FIFO empty source. On PSoC 3/5LP
    * first data byte has to be loaded on address phase.
    */
    #if(CY_PSOC4)
        `$INSTANCE_NAME`_I2C_SetTxInterruptMode(`$INSTANCE_NAME`_I2C_INTR_TX_EMPTY);
    #else
        `$INSTANCE_NAME`_I2C_DATA_REG = `$INSTANCE_NAME`_buffer[0u];
        `$INSTANCE_NAME`_I2C_ACK_AND_TRANSMIT;
    #endif /* !CY_PSOC4 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteHandler
********************************************************************************
*
* Summary:
*  Handles data processing for a "Write" part of SM/PM Bus transaction.
*
* Parameters:
*  None
*
* Return:
*  uint8 status:
*   Options: 0=success, error code on fault
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteHandler(void) `=ReentrantKeil($INSTANCE_NAME . "_WriteHandler")`
{
    if(0u != (`$INSTANCE_NAME`_cmdProperties & `$INSTANCE_NAME`_CMD_WR_AUTO))
    {
        switch(`$INSTANCE_NAME`_lastReceivedCmd)
        {
            `$WriteHandlerCases`

            default:
                break;
        }
    }
    
    /* `#START ADDITIONAL_USER_CODE_FOR_BOOTLOADER` */
    
    /* `#END` */
    
    #ifdef `$INSTANCE_NAME`_WRITE_HANDLER_CALLBACK
        `$INSTANCE_NAME`_WriteHandler_Callback();
    #endif /* `$INSTANCE_NAME`_WRITE_HANDLER_CALLBACK */
    
    else if (0u != (`$INSTANCE_NAME`_cmdProperties & `$INSTANCE_NAME`_CMD_WR_MANUAL))
    {
        if(`$INSTANCE_NAME`_CMD_LEN_VALID)
        {
            `$INSTANCE_NAME`_FillTransaction(`$INSTANCE_NAME`_CMD_WRITE);
        }
    }
    else /* Data Content Fault. Ignore received data */
    {
        `$INSTANCE_NAME`_HandleBusError(`$INSTANCE_NAME`_ERR_INVALID_DATA);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadHandler
********************************************************************************
*
* Summary:
*  Handles data processing for a "Read" part of SM/PM Bus transaction.
*
* Parameters:
*  None
*
* Return:
*  uint8 status:
*   Options: 0=success, error code on fault
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadHandler(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadHandler")`
{
    uint8 error = 0u;

    if(0u != (`$INSTANCE_NAME`_cmdProperties & `$INSTANCE_NAME`_CMD_RD_AUTO))
    {  
        `$INSTANCE_NAME`_CompleteRead();
    }
    else if(0u != (`$INSTANCE_NAME`_cmdProperties & `$INSTANCE_NAME`_CMD_RD_MANUAL))
    {
        `$INSTANCE_NAME`_FillTransaction(`$INSTANCE_NAME`_CMD_READ);
    }
    else /* Data Content Fault. FFh will be sent as host keeps clocking */
    {
        error = `$INSTANCE_NAME`_ERR_INVALID_DATA;
    }
    return (error);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FillTransaction
********************************************************************************
*
* Summary:
*  Fills a transaction queue with all the user required data for "Manual"
*  handling of SM/PM Bus transaction.
*
* Parameters:
*  uint8 command: command type (read or write)
*
* Return:
*  None
*
*******************************************************************************/
static void `$INSTANCE_NAME`_FillTransaction(uint8 command) `=ReentrantKeil($INSTANCE_NAME . "_FillTransaction")`
{    
    /* Copy all data from last transaction into transaction struct */
    `$INSTANCE_NAME`_transactionData[0u].read        = command;
    `$INSTANCE_NAME`_transactionData[0u].commandCode = `$INSTANCE_NAME`_lastReceivedCmd;
    `$INSTANCE_NAME`_transactionData[0u].length      = `$INSTANCE_NAME`_bufferSize;

    /* Fill page information */
    if (0u != (`$INSTANCE_NAME`_cmdProperties & `$INSTANCE_NAME`_CMD_PAGED))
    {
        `$INSTANCE_NAME`_transactionData[0u].page = `$INSTANCE_NAME`_cmdPage;
    }
    else
    {
        /* For non-paged commands page number is zero */
        `$INSTANCE_NAME`_transactionData[0u].page = 0u;
    }
    
    /* For Write and Process Call commands copy all data to payload */
    while(0u != `$INSTANCE_NAME`_bufferIndex)
    {
        /* Copy all data into transaction structure */
        --`$INSTANCE_NAME`_bufferIndex;
        `$INSTANCE_NAME`_transactionData[0u].payload[`$INSTANCE_NAME`_bufferIndex] = `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_bufferIndex];
    }
    
    `$INSTANCE_NAME`_trActiveCount = 1u;
    
    /* Disable interrupt and wait for `$INSTANCE_NAME`_CompleteTransaction() */
    `$INSTANCE_NAME`_I2C_DisableInt();
}


/* [] END OF FILE */
