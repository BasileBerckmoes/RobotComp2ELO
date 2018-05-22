/***************************************************************************//**
* \file `$INSTANCE_NAME`_I2C_INT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in I2C mode.
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

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_I2C_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2C_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB I2C mode.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_I2C_ISR)
{
    uint32 diffCount;
    uint32 endTransfer;

#ifdef `$INSTANCE_NAME`_I2C_ISR_ENTRY_CALLBACK
    `$INSTANCE_NAME`_I2C_ISR_EntryCallback();
#endif /* `$INSTANCE_NAME`_I2C_ISR_ENTRY_CALLBACK */

#if (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    uint32 response;

    response = `$INSTANCE_NAME`_I2C_ACK_ADDR;
#endif /* (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

    endTransfer = 0u; /* Continue active transfer */

    /* Calls customer routine if registered */
    if(NULL != `$INSTANCE_NAME`_customIntrHandler)
    {
        `$INSTANCE_NAME`_customIntrHandler();
    }

    if(`$INSTANCE_NAME`_CHECK_INTR_I2C_EC_MASKED(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP))
    {
        /* Mask-off after wakeup */
        `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
    }

    /* Master and Slave error tracking:
    * Add the master state check to track only the master errors when the master is active or
    * track slave errors when the slave is active or idle.
    * A special MMS case: in the address phase with misplaced Start: the master sets the LOST_ARB and
    * slave BUS_ERR. The valid event is LOST_ARB comes from the master.
    */
    if(`$INSTANCE_NAME`_CHECK_I2C_FSM_MASTER)
    {
        `$Cond`if(`$INSTANCE_NAME`_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_BUS_ERROR:
            * A misplaced Start or Stop condition occurred on the bus: complete the transaction.
            * The interrupt is cleared in I2C_FSM_EXIT_IDLE.
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_MASTER_MASKED(`$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
            {
                `$INSTANCE_NAME`_mstrStatus |= (uint16) (`$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER |
                                                         `$INSTANCE_NAME`_I2C_MSTAT_ERR_BUS_ERROR);

                endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
            }

            /* INTR_MASTER_I2C_ARB_LOST:
            * The MultiMaster lost arbitrage during transaction.
            * A Misplaced Start or Stop condition is treated as lost arbitration when the master drives the SDA.
            * The interrupt source is cleared in I2C_FSM_EXIT_IDLE.
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_MASTER_MASKED(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
            {
                `$INSTANCE_NAME`_mstrStatus |= (uint16) (`$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER |
                                                         `$INSTANCE_NAME`_I2C_MSTAT_ERR_ARB_LOST);

                endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
            }

            `$Cond`if(`$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE)
            {
                /* I2C_MASTER_CMD_M_START_ON_IDLE:
                * MultiMaster-Slave does not generate start, because Slave was addressed.
                * Pass control to slave.
                */
                if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_CMD(`$INSTANCE_NAME`_I2C_MASTER_CMD_M_START_ON_IDLE))
                {
                    `$INSTANCE_NAME`_mstrStatus |= (uint16) (`$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER |
                                                             `$INSTANCE_NAME`_I2C_MSTAT_ERR_ABORT_XFER);

                    endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
                }
            }
            `$EndCond`

            /* The error handling common part:
            * Sets a completion flag of the master transaction and passes control to:
            *  - I2C_FSM_EXIT_IDLE - to complete transaction in case of: ARB_LOST or BUS_ERR.
            *  - I2C_FSM_IDLE      - to take chance for the slave to process incoming transaction.
            */
            if(0u != endTransfer)
            {
                /* Set completion flags for master */
                `$INSTANCE_NAME`_mstrStatus |= (uint16) `$INSTANCE_NAME`_GET_I2C_MSTAT_CMPLT;

                `$Cond`if(`$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE)
                {
                    if(`$INSTANCE_NAME`_CHECK_I2C_FSM_ADDR)
                    {
                        /* Start generation is set after another master starts accessing Slave.
                        * Clean-up master and turn to slave. Set state to IDLE.
                        */
                        if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_CMD(`$INSTANCE_NAME`_I2C_MASTER_CMD_M_START_ON_IDLE))
                        {
                            `$INSTANCE_NAME`_I2C_MASTER_CLEAR_START;

                            endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        /* Valid arbitration lost on the address phase happens only when: master LOST_ARB is set and
                        * slave BUS_ERR is cleared. Only in that case set the state to IDLE without SCB IP re-enable.
                        */
                        else if((!`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR))
                               && `$INSTANCE_NAME`_CHECK_INTR_MASTER_MASKED(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
                        {
                            endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        else
                        {
                            endTransfer = 0u; /* Causes I2C_FSM_EXIT_IDLE to be set below */
                        }

                        if(0u != endTransfer) /* Clean-up master to proceed with slave */
                        {
                            `$INSTANCE_NAME`_CLEAR_TX_FIFO; /* Shifter keeps address, clear it */

                            `$INSTANCE_NAME`_DISABLE_MASTER_AUTO_DATA_ACK; /* In case of reading disable autoACK */

                            /* Clean-up master interrupt sources */
                            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

                            /* Disable data processing interrupts: they have to be cleared before */
                            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                            `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

                            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                        }
                        else
                        {
                            /* Set I2C_FSM_EXIT_IDLE for BUS_ERR and ARB_LOST (that is really bus error) */
                            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_EXIT_IDLE;
                        }
                    }
                    else
                    {
                        /* Set I2C_FSM_EXIT_IDLE if any other state than address */
                        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_EXIT_IDLE;
                    }
                }
                `$Cond`else
                {
                    /* In case of LOST*/
                    `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_EXIT_IDLE;
                }
                `$EndCond`
            }
        }
        `$EndCond`
    }
    else /* (`$INSTANCE_NAME`_CHECK_I2C_FSM_SLAVE) */
    {
        `$Cond`if(`$INSTANCE_NAME`_I2C_SLAVE)
        {
            /* INTR_SLAVE_I2C_BUS_ERROR or `$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST:
            * A Misplaced Start or Stop condition occurred on the bus: set a flag
            * to notify an error condition.
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR |
                                                        `$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST))
            {
                if(`$INSTANCE_NAME`_CHECK_I2C_FSM_RD)
                {
                    /* TX direction: master reads from slave */
                    `$INSTANCE_NAME`_slStatus &= (uint8) ~`$INSTANCE_NAME`_I2C_SSTAT_RD_BUSY;
                    `$INSTANCE_NAME`_slStatus |= (uint8) (`$INSTANCE_NAME`_I2C_SSTAT_RD_ERR |
                                                          `$INSTANCE_NAME`_I2C_SSTAT_RD_CMPLT);
                }
                else
                {
                    /* RX direction: master writes into slave */
                    `$INSTANCE_NAME`_slStatus &= (uint8) ~`$INSTANCE_NAME`_I2C_SSTAT_WR_BUSY;
                    `$INSTANCE_NAME`_slStatus |= (uint8) (`$INSTANCE_NAME`_I2C_SSTAT_WR_ERR |
                                                          `$INSTANCE_NAME`_I2C_SSTAT_WR_CMPLT);
                }

                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_EXIT_IDLE;
            }
        }
        `$EndCond`
    }

    /* States description:
    * Any Master operation starts from: the ADDR_RD/WR state as the master generates traffic on the bus.
    * Any Slave operation starts from: the IDLE state as the slave always waits for actions from the master.
    */

    /* FSM Master */
    if(`$INSTANCE_NAME`_CHECK_I2C_FSM_MASTER)
    {
        `$Cond`if(`$INSTANCE_NAME`_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_STOP:
            * A Stop condition was generated by the master: the end of the transaction.
            * Set completion flags to notify the API.
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_MASTER_MASKED(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP))
            {
                `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP);

                `$INSTANCE_NAME`_mstrStatus |= (uint16) `$INSTANCE_NAME`_GET_I2C_MSTAT_CMPLT;
                `$INSTANCE_NAME`_state       = `$INSTANCE_NAME`_I2C_FSM_IDLE;
            }
            else
            {
                if(`$INSTANCE_NAME`_CHECK_I2C_FSM_ADDR) /* Address stage */
                {
                    /* INTR_MASTER_I2C_NACK:
                    * The master sent an address but it was NACKed by the slave. Complete transaction.
                    */
                    if(`$INSTANCE_NAME`_CHECK_INTR_MASTER_MASKED(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
                    {
                        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK);

                        `$INSTANCE_NAME`_mstrStatus |= (uint16) (`$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER |
                                                                 `$INSTANCE_NAME`_I2C_MSTAT_ERR_ADDR_NAK);

                        endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
                    }
                    /* INTR_TX_UNDERFLOW. The master sent an address:
                    *  - TX direction: the clock is stretched after the ACK phase, because the TX FIFO is
                    *    EMPTY. The TX EMPTY cleans all the TX interrupt sources.
                    *  - RX direction: the 1st byte is received, but there is no ACK permission,
                    *    the clock is stretched after 1 byte is received.
                    */
                    else
                    {
                        if(`$INSTANCE_NAME`_CHECK_I2C_FSM_RD) /* Reading */
                        {
                            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA;
                        }
                        else /* Writing */
                        {
                            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA;
                            if(0u != `$INSTANCE_NAME`_mstrWrBufSize)
                            {
                                /* Enable INTR.TX_EMPTY if there is data to transmit */
                                `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_EMPTY);
                            }
                        }
                    }
                }

                if(`$INSTANCE_NAME`_CHECK_I2C_FSM_DATA) /* Data phase */
                {
                    if(`$INSTANCE_NAME`_CHECK_I2C_FSM_RD) /* Reading */
                    {
                        /* INTR_RX_FULL:
                        * RX direction: the master received 8 bytes.
                        * Get data from RX FIFO and decide whether to ACK or  NACK the following bytes.
                        */
                        if(`$INSTANCE_NAME`_CHECK_INTR_RX_MASKED(`$INSTANCE_NAME`_INTR_RX_FULL))
                        {
                            /* Calculate difference */
                            diffCount =  `$INSTANCE_NAME`_mstrRdBufSize -
                                        (`$INSTANCE_NAME`_mstrRdBufIndex + `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES);

                            /* Proceed transaction or end it when RX FIFO becomes FULL again */
                            if(diffCount > `$INSTANCE_NAME`_I2C_FIFO_SIZE)
                            {
                                diffCount = `$INSTANCE_NAME`_I2C_FIFO_SIZE;
                            }
                            else
                            {
                                if(0u == diffCount)
                                {
                                    `$INSTANCE_NAME`_DISABLE_MASTER_AUTO_DATA_ACK;

                                    diffCount   = `$INSTANCE_NAME`_I2C_FIFO_SIZE;
                                    endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
                                }
                            }

                            for(; (0u != diffCount); diffCount--)
                            {
                                `$INSTANCE_NAME`_mstrRdBufPtr[`$INSTANCE_NAME`_mstrRdBufIndex] = (uint8)
                                                                                        `$INSTANCE_NAME`_RX_FIFO_RD_REG;
                                `$INSTANCE_NAME`_mstrRdBufIndex++;
                            }
                        }
                        /* INTR_RX_NOT_EMPTY:
                        * RX direction: the master received one data byte, ACK or NACK it.
                        * The last byte is stored and NACKed by the master. The NACK and Stop is
                        * generated by one command generate Stop.
                        */
                        else if(`$INSTANCE_NAME`_CHECK_INTR_RX_MASKED(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
                        {
                            /* Put data in component buffer */
                            `$INSTANCE_NAME`_mstrRdBufPtr[`$INSTANCE_NAME`_mstrRdBufIndex] = (uint8) `$INSTANCE_NAME`_RX_FIFO_RD_REG;
                            `$INSTANCE_NAME`_mstrRdBufIndex++;

                            if(`$INSTANCE_NAME`_mstrRdBufIndex < `$INSTANCE_NAME`_mstrRdBufSize)
                            {
                                `$INSTANCE_NAME`_I2C_MASTER_GENERATE_ACK;
                            }
                            else
                            {
                               endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
                            }
                        }
                        else
                        {
                            /* Do nothing */
                        }

                        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ALL);
                    }
                    else /* Writing */
                    {
                        /* INTR_MASTER_I2C_NACK :
                        * The master writes data to the slave and NACK was received: not all the bytes were
                        * written to the slave from the TX FIFO. Revert the index if there is data in
                        * the TX FIFO and pass control to a complete transfer.
                        */
                        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER_MASKED(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
                        {
                            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK);

                            /* Rollback write buffer index: NACKed byte remains in shifter */
                            `$INSTANCE_NAME`_mstrWrBufIndexTmp -= (`$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES +
                                                                   `$INSTANCE_NAME`_GET_TX_FIFO_SR_VALID);

                            /* Update number of transferred bytes */
                            `$INSTANCE_NAME`_mstrWrBufIndex = `$INSTANCE_NAME`_mstrWrBufIndexTmp;

                            `$INSTANCE_NAME`_mstrStatus |= (uint16) (`$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER |
                                                                     `$INSTANCE_NAME`_I2C_MSTAT_ERR_SHORT_XFER);

                            `$INSTANCE_NAME`_CLEAR_TX_FIFO;

                            endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
                        }
                        /* INTR_TX_EMPTY :
                        * TX direction: the TX FIFO is EMPTY, the data from the buffer needs to be put there.
                        * When there is no data in the component buffer, the underflow interrupt is
                        * enabled to catch when all the data has been transferred.
                        */
                        else if(`$INSTANCE_NAME`_CHECK_INTR_TX_MASKED(`$INSTANCE_NAME`_INTR_TX_EMPTY))
                        {
                            while(`$INSTANCE_NAME`_I2C_FIFO_SIZE != `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES)
                            {
                                /* The temporary mstrWrBufIndexTmp is used because slave could NACK the byte and index
                                * roll-back required in this case. The mstrWrBufIndex is updated at the end of transfer.
                                */
                                if(`$INSTANCE_NAME`_mstrWrBufIndexTmp < `$INSTANCE_NAME`_mstrWrBufSize)
                                {
                                #if(!`$INSTANCE_NAME`_CY_SCBIP_V0)
                                   /* Clear INTR_TX.UNDERFLOW before putting the last byte into TX FIFO. This ensures
                                    * a proper trigger at the end of transaction when INTR_TX.UNDERFLOW single trigger
                                    * event. Ticket ID# 156735.
                                    */
                                    if(`$INSTANCE_NAME`_mstrWrBufIndexTmp == (`$INSTANCE_NAME`_mstrWrBufSize - 1u))
                                    {
                                        `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);
                                        `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);
                                    }
                                 #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

                                    /* Put data into TX FIFO */
                                    `$INSTANCE_NAME`_TX_FIFO_WR_REG = (uint32) `$INSTANCE_NAME`_mstrWrBufPtr[`$INSTANCE_NAME`_mstrWrBufIndexTmp];
                                    `$INSTANCE_NAME`_mstrWrBufIndexTmp++;
                                }
                                else
                                {
                                    break; /* No more data to put */
                                }
                            }

                        #if(`$INSTANCE_NAME`_CY_SCBIP_V0)
                            if(`$INSTANCE_NAME`_mstrWrBufIndexTmp == `$INSTANCE_NAME`_mstrWrBufSize)
                            {
                                `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);
                            }

                            `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_ALL);
                        #else
                            `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_EMPTY);
                        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */
                        }
                        /* INTR_TX_UNDERFLOW:
                        * TX direction: all data from the TX FIFO was transferred to the slave.
                        * The transaction needs to be completed.
                        */
                        else if(`$INSTANCE_NAME`_CHECK_INTR_TX_MASKED(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW))
                        {
                            /* Update number of transferred bytes */
                            `$INSTANCE_NAME`_mstrWrBufIndex = `$INSTANCE_NAME`_mstrWrBufIndexTmp;

                            endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                }

                if(0u != endTransfer) /* Complete transfer */
                {
                    /* Clean-up master after reading: only in case of NACK */
                    `$INSTANCE_NAME`_DISABLE_MASTER_AUTO_DATA_ACK;

                    /* Disable data processing interrupts: they have to be cleared before */
                    `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                    `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

                    if(`$INSTANCE_NAME`_CHECK_I2C_MODE_NO_STOP(`$INSTANCE_NAME`_mstrControl))
                    {
                        /* On-going transaction is suspended: the ReStart is generated by the API request */
                        `$INSTANCE_NAME`_mstrStatus |= (uint16) (`$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT |
                                                                 `$INSTANCE_NAME`_GET_I2C_MSTAT_CMPLT);

                        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
                    }
                    else
                    {
                        /* Complete transaction: exclude the data processing state and generate Stop.
                        * The completion status will be set after Stop generation.
                        * A special case is read: because NACK and Stop are generated by the command below.
                        * Lost arbitration can occur during NACK generation when
                        * the other master is still reading from the slave.
                        */
                        `$INSTANCE_NAME`_I2C_MASTER_GENERATE_STOP;
                    }
                }
            }

        } /* (`$INSTANCE_NAME`_I2C_MASTER) */
        `$EndCond`

    } /* (`$INSTANCE_NAME`_CHECK_I2C_FSM_MASTER) */


    /* FSM Slave */
    else if(`$INSTANCE_NAME`_CHECK_I2C_FSM_SLAVE)
    {
        `$Cond`if(`$INSTANCE_NAME`_I2C_SLAVE)
        {
            /* INTR_SLAVE_NACK:
            * The master completes reading the slave: the appropriate flags have to be set.
            * The TX FIFO is cleared after an overflow condition is set.
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK))
            {
                `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK);

                /* All entries that remain in TX FIFO are: FIFO Size + 1 (SHIFTER) */
                diffCount = (`$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES + `$INSTANCE_NAME`_GET_TX_FIFO_SR_VALID);

                if(`$INSTANCE_NAME`_slOverFlowCount > diffCount) /* Overflow */
                {
                    `$INSTANCE_NAME`_slStatus |= (uint8) `$INSTANCE_NAME`_I2C_SSTAT_RD_OVFL;
                }
                else /* No Overflow */
                {
                    /* Roll-back temporary index */
                    `$INSTANCE_NAME`_slRdBufIndexTmp -= (diffCount - `$INSTANCE_NAME`_slOverFlowCount);
                }

                /* Update slave of transferred bytes */
                `$INSTANCE_NAME`_slRdBufIndex = `$INSTANCE_NAME`_slRdBufIndexTmp;

                /* Clean-up TX FIFO */
                `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                `$INSTANCE_NAME`_slOverFlowCount = 0u;
                `$INSTANCE_NAME`_CLEAR_TX_FIFO;

                /* Complete master reading */
                `$INSTANCE_NAME`_slStatus &= (uint8) ~`$INSTANCE_NAME`_I2C_SSTAT_RD_BUSY;
                `$INSTANCE_NAME`_slStatus |= (uint8)  `$INSTANCE_NAME`_I2C_SSTAT_RD_CMPLT;
                `$INSTANCE_NAME`_state     =  `$INSTANCE_NAME`_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_WRITE_STOP:
            * The master completes writing to the slave: the appropriate flags have to be set.
            * The RX FIFO contains 1-8 bytes from the previous transaction which needs to be read.
            * There is a possibility that RX FIFO contains an address, it needs to leave it there.
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP))
            {
                `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP);

                /* Read bytes from RX FIFO when auto data ACK receive logic is enabled. Otherwise all data bytes
                * were already read from the RX FIFO except for address byte which has to stay here to be handled by
                * I2C_ADDR_MATCH.
                */
                if (0u != (`$INSTANCE_NAME`_I2C_CTRL_REG & `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK))
                {
                    while(0u != `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES)
                    {
                        `$Cond`if(`$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS)
                        {
                            if((1u == `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES) &&
                               (`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH)))
                            {
                                break; /* Leave address in RX FIFO */
                            }
                        }
                        `$EndCond`

                        /* Put data in component buffer */
                        `$INSTANCE_NAME`_slWrBufPtr[`$INSTANCE_NAME`_slWrBufIndex] = (uint8) `$INSTANCE_NAME`_RX_FIFO_RD_REG;
                        `$INSTANCE_NAME`_slWrBufIndex++;
                    }

                    `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_DATA;
                }

                if(`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_OVERFLOW))
                {
                    `$INSTANCE_NAME`_slStatus |= (uint8) `$INSTANCE_NAME`_I2C_SSTAT_WR_OVFL;
                }

                /* Clears RX interrupt sources triggered on data receiving */
                `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ALL);

                /* Complete master writing */
                `$INSTANCE_NAME`_slStatus &= (uint8) ~`$INSTANCE_NAME`_I2C_SSTAT_WR_BUSY;
                `$INSTANCE_NAME`_slStatus |= (uint8)  `$INSTANCE_NAME`_I2C_SSTAT_WR_CMPLT;
                `$INSTANCE_NAME`_state     =  `$INSTANCE_NAME`_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_ADDR_MATCH or INTR_SLAVE_I2C_GENERAL:
            * The address match or general call address event starts the slave operation:
            * after leaving the TX or RX direction has to be chosen.
            * The wakeup interrupt must be cleared only after an address match is set.
            */
        #if (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
            if (`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH |
                                                         `$INSTANCE_NAME`_INTR_SLAVE_I2C_GENERAL))
        #else
            if (`$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH))
        #endif /* (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */
            {
                /* Clear externally clocked address match interrupt source when internally clocked is set */
                `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);

                `$Cond`if (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER)
                {
                    if (NULL != `$INSTANCE_NAME`_customAddressHandler)
                    {
                        /* Call custom address handler */
                        response = `$INSTANCE_NAME`_customAddressHandler();
                    }
                    else
                    {
                        /* Read address from the RX FIFO. If there is no address underflow triggers but
                        * component does not use that source. */
                        (void) `$INSTANCE_NAME`_RX_FIFO_RD_REG;
                        response = `$INSTANCE_NAME`_I2C_ACK_ADDR;
                    }

                    /* Clears RX sources after address was received in the RX FIFO */
                    `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ALL);
                }
                `$EndCond`

            #if (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
                if (response == `$INSTANCE_NAME`_I2C_NAK_ADDR)
                {
                #if (!`$INSTANCE_NAME`_CY_SCBIP_V0)
                    /* Disable write stop interrupt source as it triggers after address was NACKed. Ticket ID#156094 */
                    `$INSTANCE_NAME`_DISABLE_INTR_SLAVE(`$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP);
                #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

                    /* Clear address match and stop history */
                    `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);

                    /* ACK the address byte */
                    `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK;
                }
                else
            #endif /* (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */
                {
                    if(`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_S_READ))
                    /* TX direction: master reads from slave */
                    {
                        `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_EMPTY);

                        /* Set temporary index to address buffer clear from API */
                        `$INSTANCE_NAME`_slRdBufIndexTmp = `$INSTANCE_NAME`_slRdBufIndex;

                        /* Start master reading */
                        `$INSTANCE_NAME`_slStatus |= (uint8) `$INSTANCE_NAME`_I2C_SSTAT_RD_BUSY;
                        `$INSTANCE_NAME`_state     = `$INSTANCE_NAME`_I2C_FSM_SL_RD;
                    }
                    else
                    /* RX direction: master writes into slave */
                    {
                        /* Calculate available buffer size */
                        diffCount = (`$INSTANCE_NAME`_slWrBufSize - `$INSTANCE_NAME`_slWrBufIndex);

                    #if (`$INSTANCE_NAME`_CY_SCBIP_V0)
                        if(diffCount < `$INSTANCE_NAME`_I2C_FIFO_SIZE)
                        /* Receive data: byte-by-byte */
                        {
                            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
                        }
                        else
                        /* Receive data: into RX FIFO */
                        {
                            if(diffCount == `$INSTANCE_NAME`_I2C_FIFO_SIZE)
                            {
                                /* NACK when RX FIFO become FULL */
                                `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA;
                            }
                            else
                            {
                                /* Stretch clock when RX FIFO becomes FULL */
                                `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_ACK;
                                `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_FULL);
                            }
                        }

                    #else
                        `$Cond`if(`$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS)
                        {
                            /* Enable RX.NOT_EMPTY interrupt source to receive byte by byte.
                            * The byte by byte receive is always chosen for the case when an address is accepted
                            * in RX FIFO. Ticket ID#175559.
                            */
                            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
                        }
                        `$Cond`else
                        {
                            if(diffCount < `$INSTANCE_NAME`_I2C_FIFO_SIZE)
                            /* Receive data: byte-by-byte */
                            {
                                `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
                            }
                            else
                            /* Receive data: into RX FIFO */
                            {
                                if(diffCount == `$INSTANCE_NAME`_I2C_FIFO_SIZE)
                                {
                                    /* NACK when RX FIFO become FULL */
                                    `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA;
                                }
                                else
                                {
                                    /* Stretch clock when RX FIFO becomes FULL */
                                    `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_ACK;
                                    `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_FULL);
                                }
                            }
                        }
                        `$EndCond`
                    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

                        /* Start master reading */
                        `$INSTANCE_NAME`_slStatus |= (uint8) `$INSTANCE_NAME`_I2C_SSTAT_WR_BUSY;
                        `$INSTANCE_NAME`_state     = `$INSTANCE_NAME`_I2C_FSM_SL_WR;
                    }

                    /* Clear address match and stop history */
                    `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);

                #if (!`$INSTANCE_NAME`_CY_SCBIP_V0)
                    /* Enable write stop interrupt source as it triggers after address was NACKed. Ticket ID#156094 */
                    `$INSTANCE_NAME`_ENABLE_INTR_SLAVE(`$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP);
                #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

                    /* ACK the address byte */
                    `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_ACK;
                }
            }

            /* `$INSTANCE_NAME`_INTR_RX_FULL:
            * Get data from the RX FIFO and decide whether to ACK or NACK the following bytes
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_RX_MASKED(`$INSTANCE_NAME`_INTR_RX_FULL))
            {
                /* Calculate available buffer size to take into account that RX FIFO is FULL */
                diffCount =  `$INSTANCE_NAME`_slWrBufSize -
                            (`$INSTANCE_NAME`_slWrBufIndex + `$INSTANCE_NAME`_I2C_FIFO_SIZE);

                if(diffCount > `$INSTANCE_NAME`_I2C_FIFO_SIZE) /* Proceed transaction */
                {
                    diffCount   = `$INSTANCE_NAME`_I2C_FIFO_SIZE;
                    endTransfer = 0u;  /* Continue active transfer */
                }
                else /* End when FIFO becomes FULL again */
                {
                    endTransfer = `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER;
                }

                for(; (0u != diffCount); diffCount--)
                {
                    /* Put data in component buffer */
                    `$INSTANCE_NAME`_slWrBufPtr[`$INSTANCE_NAME`_slWrBufIndex] = (uint8) `$INSTANCE_NAME`_RX_FIFO_RD_REG;
                    `$INSTANCE_NAME`_slWrBufIndex++;
                }

                if(0u != endTransfer) /* End transfer sending NACK */
                {
                    `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_NACK;

                    /* INTR_RX_FULL triggers earlier than INTR_SLAVE_I2C_STOP:
                    * disable all RX interrupt sources.
                    */
                    `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
                }

                `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_FULL);
            }
            /* `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY:
            * The buffer size is less than 8: it requires processing in byte-by-byte mode.
            */
            else if(`$INSTANCE_NAME`_CHECK_INTR_RX_MASKED(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
            {
                diffCount = `$INSTANCE_NAME`_RX_FIFO_RD_REG;

                if(`$INSTANCE_NAME`_slWrBufIndex < `$INSTANCE_NAME`_slWrBufSize)
                {
                    `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_ACK;

                    /* Put data into component buffer */
                    `$INSTANCE_NAME`_slWrBufPtr[`$INSTANCE_NAME`_slWrBufIndex] = (uint8) diffCount;
                    `$INSTANCE_NAME`_slWrBufIndex++;
                }
                else /* Overflow: there is no space in write buffer */
                {
                    `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK;

                    `$INSTANCE_NAME`_slStatus |= (uint8) `$INSTANCE_NAME`_I2C_SSTAT_WR_OVFL;
                }

                `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
            }
            else
            {
                /* Does nothing */
            }


            /* `$INSTANCE_NAME`_INTR_TX_EMPTY:
            * The master reads the slave: provide data to read or 0xFF in the case of the end of the buffer
            * The overflow condition must be captured, but not set until the end of transaction.
            * There is a possibility of a false overflow due to TX FIFO utilization.
            */
            if(`$INSTANCE_NAME`_CHECK_INTR_TX_MASKED(`$INSTANCE_NAME`_INTR_TX_EMPTY))
            {
                while(`$INSTANCE_NAME`_I2C_FIFO_SIZE != `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES)
                {
                    /* Temporary slRdBufIndexTmp is used because the master can NACK the byte and
                    * index roll-back is required in this case. The slRdBufIndex is updated at the end
                    * of the read transfer.
                    */
                    if(`$INSTANCE_NAME`_slRdBufIndexTmp < `$INSTANCE_NAME`_slRdBufSize)
                    /* Data from buffer */
                    {
                        `$INSTANCE_NAME`_TX_FIFO_WR_REG = (uint32) `$INSTANCE_NAME`_slRdBufPtr[`$INSTANCE_NAME`_slRdBufIndexTmp];
                        `$INSTANCE_NAME`_slRdBufIndexTmp++;
                    }
                    else
                    /* Probably Overflow */
                    {
                        `$INSTANCE_NAME`_TX_FIFO_WR_REG = `$INSTANCE_NAME`_I2C_SLAVE_OVFL_RETURN;

                        if(`$INSTANCE_NAME`_slOverFlowCount <= `$INSTANCE_NAME`_I2C_TX_OVERFLOW_COUNT)
                        {
                            /* Get counter in range of overflow. */
                            `$INSTANCE_NAME`_slOverFlowCount++;
                        }
                    }
                }

                `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_EMPTY);
            }

        }  /* (`$INSTANCE_NAME`_I2C_SLAVE) */
        `$EndCond`
    }


    /* FSM EXIT:
    * Slave:  INTR_SLAVE_I2C_BUS_ERROR, INTR_SLAVE_I2C_ARB_LOST
    * Master: INTR_MASTER_I2C_BUS_ERROR, INTR_MASTER_I2C_ARB_LOST.
    */
    else
    {
        `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED; /* Disable scb IP */

        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

        `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_DATA;
        `$INSTANCE_NAME`_DISABLE_MASTER_AUTO_DATA;

    #if(`$INSTANCE_NAME`_CY_SCBIP_V0)
        `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
        `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

        /* Clear interrupt sources as they are not automatically cleared after SCB is disabled */
        `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ALL);
        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_TX_ALL);
        `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);
        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

        `$INSTANCE_NAME`_CTRL_REG |= (uint32) `$INSTANCE_NAME`_CTRL_ENABLED;  /* Enable scb IP */
    }

#ifdef `$INSTANCE_NAME`_I2C_ISR_EXIT_CALLBACK
    `$INSTANCE_NAME`_I2C_ISR_ExitCallback();
#endif /* `$INSTANCE_NAME`_I2C_ISR_EXIT_CALLBACK */

}


/* [] END OF FILE */
