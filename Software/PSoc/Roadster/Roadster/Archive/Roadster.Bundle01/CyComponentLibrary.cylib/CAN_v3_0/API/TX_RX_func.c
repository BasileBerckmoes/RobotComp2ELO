/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TX_RX_func.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  There are functions process "Full" Receive and Transmit mailboxes:
*     - `$INSTANCE_NAME`_SendMsg0-7();
*     - `$INSTANCE_NAME`_ReceiveMsg0-15();
*  Transmission of message, and receive routine for "Basic" mailboxes:
*     - `$INSTANCE_NAME`_SendMsg();
*     - `$INSTANCE_NAME`_TxCancel();
*     - `$INSTANCE_NAME`_ReceiveMsg();
*
*  Note:
*   None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/* `#START TX_RX_FUNCTION` */

/* `#END` */


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg
********************************************************************************
*
* Summary:
*  This function is Send Message from one of Basic mailboxes. The function loops
*  through the transmit message buffer designed as Basic CAN mailboxes for the
*  first free available and sends from it. The number of retries is limited.
*
* Parameters:
*  message: The pointer to a structure that contains all required data to send
*           messages.
*
* Return:
*  Indication if message has been sent.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SendMsg(const `$INSTANCE_NAME`_TX_MSG *message) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg")`
{
    uint8 i, j, shift;
    uint8 retry = 0u;
    uint8 result = `$INSTANCE_NAME`_FAIL;
    uint32 regTemp;

    while (retry < `$INSTANCE_NAME`_RETRY_NUMBER)
    {
        shift = 1u;    /* Start from first mailbox */
        for (i = 0u; i < `$INSTANCE_NAME`_NUMBER_OF_TX_MAILBOXES; i++)
        {
            /* Find Basic TX mailboxes */
            if ((`$INSTANCE_NAME`_TX_MAILBOX_TYPE & shift) == 0u)
            {
                /* Find free mailbox */
                #if (CY_PSOC3 || CY_PSOC5)
                    if ((`$INSTANCE_NAME`_BUF_SR_REG.byte[2] & shift) == 0u)
                #else  /* CY_PSOC4 */
                    if ((`$INSTANCE_NAME`_BUF_SR_REG &
                        (uint32) ((uint32) shift << `$INSTANCE_NAME`_TWO_BYTE_OFFSET)) == 0u)
                #endif /* CY_PSOC3 || CY_PSOC5 */
                    {
                        regTemp = 0u;

                        /* Set message parameters */
                        if (message->rtr != `$INSTANCE_NAME`_STANDARD_MESSAGE)
                        {
                            regTemp = `$INSTANCE_NAME`_TX_RTR_MASK;    /* RTR message Enable */
                        }

                        if (message->ide == `$INSTANCE_NAME`_STANDARD_MESSAGE)
                        {
                            `$INSTANCE_NAME`_SET_TX_ID_STANDARD_MSG(i, message->id);
                        }
                        else
                        {
                            regTemp |= `$INSTANCE_NAME`_TX_IDE_MASK;
                            `$INSTANCE_NAME`_SET_TX_ID_EXTENDED_MSG(i, message->id);
                        }

                        if (message->dlc < `$INSTANCE_NAME`_TX_DLC_MAX_VALUE)
                        {
                            regTemp |= ((uint32) message->dlc) << `$INSTANCE_NAME`_TWO_BYTE_OFFSET;
                        }
                        else
                        {
                            regTemp |= `$INSTANCE_NAME`_TX_DLC_UPPER_VALUE;
                        }

                        if (message->irq != `$INSTANCE_NAME`_TRANSMIT_INT_DISABLE)
                        {
                            regTemp |= `$INSTANCE_NAME`_TX_INT_ENABLE_MASK;    /* Transmit Interrupt Enable */
                        }

                        for (j = 0u; (j < message->dlc) && (j < `$INSTANCE_NAME`_TX_DLC_MAX_VALUE); j++)
                        {
                            #if (CY_PSOC3 || CY_PSOC5)
                                `$INSTANCE_NAME`_TX_DATA_BYTE(i, j) = message->msg->byte[j];
                            #else /* CY_PSOC4 */
                                `$INSTANCE_NAME`_TX_DATA_BYTE(i, j, message->msg->byte[j]);
                            #endif /* CY_PSOC3 || CY_PSOC5 */
                        }

                    `$ISRDisable`
                        /* WPN[23] and WPN[3] set to 1 for write to CAN Control reg */
                        CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(i), (regTemp | `$INSTANCE_NAME`_TX_WPN_SET));

                        #if (CY_PSOC3 || CY_PSOC5)
                            CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(i), `$INSTANCE_NAME`_SEND_MESSAGE);
                        #else /* CY_PSOC4 */
                            if (message->sst != `$INSTANCE_NAME`_STANDARD_MESSAGE)
                            {
                                /* Single Shot Transmission */
                                `$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_SEND_MESSAGE |
                                `$INSTANCE_NAME`_TX_ABORT_MASK;
                            }
                            else
                            {
                                `$INSTANCE_NAME`_TX_CMD_REG(i) |= `$INSTANCE_NAME`_SEND_MESSAGE;
                            }
                        #endif /* CY_PSOC3 || CY_PSOC5 */

                    `$ISREnable`
                        result = CYRET_SUCCESS;
                    }
            }
            shift <<= 1u;
            if (result == CYRET_SUCCESS)
            {
                break;
            }
        }
        if (result == CYRET_SUCCESS)
        {
            break;
        }
        else
        {
            retry++;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_TxCancel
********************************************************************************
*
* Summary:
*  This function cancels transmission of a message that has been queued to be
*  transmitted. Values between 0 and 7 are valid.
*
* Parameters:
*  bufferId: The mailbox number.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_TxCancel(uint8 bufferId) `=ReentrantKeil($INSTANCE_NAME . "_TxCancel")`
{
    if (bufferId < `$INSTANCE_NAME`_NUMBER_OF_TX_MAILBOXES)
    {
        `$INSTANCE_NAME`_TX_ABORT_MESSAGE(bufferId);
    }
}


#if (`$INSTANCE_NAME`_TX0_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name0`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 0. The function checks
    *  if mailbox 0 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name0`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name0`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[0u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(0u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name0`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name0`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name0`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name0`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(0u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(0u)) | `$TX_send0`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX0_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_TX1_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name1`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 1. The function checks
    *  if mailbox 1 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name1`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name1`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[1u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(1u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name1`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name1`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name1`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name1`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(1u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(1u)) | `$TX_send1`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX1_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_TX2_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name2`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 2. The function checks
    *  if mailbox 2 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name2`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name2`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[2u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(2u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name2`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name2`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name2`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name2`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(2u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(2u)) | `$TX_send2`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX2_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_TX3_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name3`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 3. The function checks
    *  if mailbox 3 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name3`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name3`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[3u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(3u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name3`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name3`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name3`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name3`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(3u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(3u)) | `$TX_send3`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX3_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_TX4_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name4`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 4. The function checks
    *  if mailbox 4 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name4`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name4`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[4u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(4u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name4`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name4`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name4`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name4`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(4u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(4u)) | `$TX_send4`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX4_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_TX5_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name5`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 5. The function checks
    *  if mailbox 5 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name5`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name5`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[5u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(5u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name5`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name5`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name5`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name5`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(5u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(5u)) | `$TX_send5`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX5_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_TX6_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name6`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 6. The function checks
    *  if mailbox 6 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name6`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name6`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[6u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(6u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name6`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name6`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name6`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name6`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(6u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(6u)) | `$TX_send6`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX6_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_TX7_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_SendMsg`$TX_name7`)
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 7. The function checks
    *  if mailbox 7 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    `$INSTANCE_NAME`_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SendMsg`$TX_name7`(void) `=ReentrantKeil($INSTANCE_NAME . "_SendMsg`$TX_name7`")`
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((`$INSTANCE_NAME`_TX[7u].txcmd.byte[0u] & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((`$INSTANCE_NAME`_TX_CMD_REG(7u) & `$INSTANCE_NAME`_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = `$INSTANCE_NAME`_FAIL;
            }
            else
            {
                /* `#START MESSAGE_`$TX_name7`_TRASMITTED` */

                /* `#END` */

                #ifdef `$INSTANCE_NAME`_SEND_MSG_`$TX_name7`_CALLBACK
                    `$INSTANCE_NAME`_SendMsg_`$TX_name7`_Callback();
                #endif /* `$INSTANCE_NAME`_SEND_MSG_`$TX_name7`_CALLBACK */

                CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(7u),
                CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(7u)) | `$TX_send7`);
            }

        return (result);
    }
#endif /* `$INSTANCE_NAME`_TX7_FUNC_ENABLE */


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg
********************************************************************************
*
* Summary:
*  This function is the entry point to Receive Message Interrupt for Basic
*  mailboxes. Clears the Receive particular Message interrupt flag. Generated
*  only if one of the Receive mailboxes is designed as Basic.
*
* Parameters:
*  rxMailbox: The mailbox number that trig Receive Message Interrupt.
*
* Return:
*  None.
*
* Reentrant:
*  Depends on the Customer code.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ReceiveMsg(uint8 rxMailbox) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        if ((`$INSTANCE_NAME`_RX[rxMailbox].rxcmd.byte[0u] & `$INSTANCE_NAME`_RX_ACK_MSG) != 0u)
    #else  /* CY_PSOC4 */
        if ((`$INSTANCE_NAME`_RX_CMD_REG(rxMailbox) & `$INSTANCE_NAME`_RX_ACK_MSG) != 0u)
    #endif /* CY_PSOC3 || CY_PSOC5 */
        {
            /* `#START MESSAGE_BASIC_RECEIVED` */

            /* `#END` */

            #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_CALLBACK
                `$INSTANCE_NAME`_ReceiveMsg_Callback();
            #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_CALLBACK */

            #if (CY_PSOC3 || CY_PSOC5)
                `$INSTANCE_NAME`_RX[rxMailbox].rxcmd.byte[0u] |= `$INSTANCE_NAME`_RX_ACK_MSG;
            #else  /* CY_PSOC4 */
                `$INSTANCE_NAME`_RX_CMD_REG(rxMailbox) |= `$INSTANCE_NAME`_RX_ACK_MSG;
            #endif /* CY_PSOC3 || CY_PSOC5 */
        }
}


#if (`$INSTANCE_NAME`_RX0_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name0`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 0 Interrupt. Clears the
    *  Receive Message 0 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name0`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name0`")`
    {
        /* `#START MESSAGE_`$RX_name0`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name0`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name0`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name0`_CALLBACK */

`$RX_ack0`
    }
#endif /* `$INSTANCE_NAME`_RX0_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX1_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:    `$INSTANCE_NAME`_ReceiveMsg`$RX_name1`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 1 Interrupt. Clears the
    *  Receive Message 1 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name1`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name1`")`
    {
        /* `#START MESSAGE_`$RX_name1`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name1`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name1`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name1`_CALLBACK */

`$RX_ack1`
    }
#endif /* `$INSTANCE_NAME`_RX1_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX2_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name2`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 2 Interrupt. Clears the
    *  Receive Message 2 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name2`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name2`")`
    {
        /* `#START MESSAGE_`$RX_name2`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name2`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name2`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name2`_CALLBACK */

`$RX_ack2`
    }
#endif /* `$INSTANCE_NAME`_RX2_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX3_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name3`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 3 Interrupt. Clears the
    *  Receive Message 3 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name3`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name3`")`
    {
        /* `#START MESSAGE_`$RX_name3`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name3`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name3`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name3`_CALLBACK */

`$RX_ack3`
    }
#endif /* `$INSTANCE_NAME`_RX3_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX4_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name4`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 4 Interrupt. Clears the
    *  Receive Message 4 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name4`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name4`")`
    {
        /* `#START MESSAGE_`$RX_name4`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name4`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name4`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name4`_CALLBACK */

`$RX_ack4`
    }
#endif /* `$INSTANCE_NAME`_RX4_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX5_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name5`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 5 Interrupt. Clears the
    *  Receive Message 5 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name5`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name5`")`
    {
        /* `#START MESSAGE_`$RX_name5`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name5`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name5`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name5`_CALLBACK */

`$RX_ack5`
    }
#endif /* `$INSTANCE_NAME`_RX5_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX6_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name6`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 6 Interrupt. Clears the
    *  Receive Message 6 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name6`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name6`")`
    {
        /* `#START MESSAGE_`$RX_name6`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name6`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name6`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name6`_CALLBACK */

`$RX_ack6`
    }
#endif /* `$INSTANCE_NAME`_RX6_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX7_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name7`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 7 Interrupt. Clears the
    *  Receive Message 7 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name7`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name7`")`
    {
        /* `#START MESSAGE_`$RX_name7`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name7`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name7`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name7`_CALLBACK */

`$RX_ack7`
    }
#endif /* `$INSTANCE_NAME`_RX7_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX8_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name8`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 8 Interrupt. Clears the
    *  Receive Message 8 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name8`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name8`")`
    {
        /* `#START MESSAGE_`$RX_name8`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name8`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name8`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name8`_CALLBACK */

`$RX_ack8`
    }
#endif /* `$INSTANCE_NAME`_RX8_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX9_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name9`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 9 Interrupt. Clears the
    *  Receive Message 9 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name9`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name9`")`
    {
        /* `#START MESSAGE_`$RX_name9`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name9`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name9`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name9`_CALLBACK */

`$RX_ack9`
    }
#endif /* `$INSTANCE_NAME`_RX9_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX10_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name10`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 10 Interrupt. Clears the
    *  Receive Message 10 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name10`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name10`")`
    {
        /* `#START MESSAGE_`$RX_name10`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name10`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name10`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name10`_CALLBACK */

`$RX_ack10`
    }
#endif /* `$INSTANCE_NAME`_RX10_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX11_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name11`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 11 Interrupt. Clears the
    *  Receive Message 11 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name11`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name11`")`
    {
        /* `#START MESSAGE_`$RX_name11`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name11`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name11`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name11`_CALLBACK */

`$RX_ack11`
    }
#endif /* `$INSTANCE_NAME`_RX11_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX12_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name12`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 12 Interrupt. Clears the
    *  Receive Message 12 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name12`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name12`")`
    {
        /* `#START MESSAGE_`$RX_name12`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name12`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name12`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name12`_CALLBACK */

`$RX_ack12`
    }
#endif /* `$INSTANCE_NAME`_RX12_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX13_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name13`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 13 Interrupt. Clears the
    *  Receive Message 13 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name13`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name13`")`
    {
        /* `#START MESSAGE_`$RX_name13`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name13`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name13`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name13`_CALLBACK */

`$RX_ack13`
    }
#endif /* `$INSTANCE_NAME`_RX13_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX14_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name14`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 14 Interrupt. Clears the
    *  Receive Message 14 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name14`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name14`")`
    {
        /* `#START MESSAGE_`$RX_name14`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name14`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name14`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name14`_CALLBACK */

`$RX_ack14`
    }
#endif /* `$INSTANCE_NAME`_RX14_FUNC_ENABLE */


#if (`$INSTANCE_NAME`_RX15_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   `$INSTANCE_NAME`_ReceiveMsg`$RX_name15`
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 15 Interrupt. Clears the
    *  Receive Message 15 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReceiveMsg`$RX_name15`(void) `=ReentrantKeil($INSTANCE_NAME . "_ReceiveMsg`$RX_name15`")`
    {
        /* `#START MESSAGE_`$RX_name15`_RECEIVED` */

        /* `#END` */

        #ifdef `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name15`_CALLBACK
            `$INSTANCE_NAME`_ReceiveMsg_`$RX_name15`_Callback();
        #endif /* `$INSTANCE_NAME`_RECEIVE_MSG_`$RX_name15`_CALLBACK */

`$RX_ack15`
    }
#endif /* `$INSTANCE_NAME`_RX15_FUNC_ENABLE */


/* [] END OF FILE */
