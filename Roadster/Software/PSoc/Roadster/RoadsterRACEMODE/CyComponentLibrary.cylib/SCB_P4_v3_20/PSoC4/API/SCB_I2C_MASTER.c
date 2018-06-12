/***************************************************************************//**
* \file `$INSTANCE_NAME`_I2C_MASTER.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C Master mode.
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
#include "`$INSTANCE_NAME`_I2C_PVT.h"

#if(`$INSTANCE_NAME`_I2C_MASTER_CONST)

/***************************************
*      I2C Master Private Vars
***************************************/

/* Master variables */
volatile uint16 `$INSTANCE_NAME`_mstrStatus;      /* Master Status byte  */
volatile uint8  `$INSTANCE_NAME`_mstrControl;     /* Master Control byte */

/* Receive buffer variables */
volatile uint8 * `$INSTANCE_NAME`_mstrRdBufPtr;   /* Pointer to Master Read buffer */
volatile uint32  `$INSTANCE_NAME`_mstrRdBufSize;  /* Master Read buffer size       */
volatile uint32  `$INSTANCE_NAME`_mstrRdBufIndex; /* Master Read buffer Index      */

/* Transmit buffer variables */
volatile uint8 * `$INSTANCE_NAME`_mstrWrBufPtr;   /* Pointer to Master Write buffer */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufSize;  /* Master Write buffer size       */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufIndex; /* Master Write buffer Index      */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */

#if (!`$INSTANCE_NAME`_CY_SCBIP_V0 && \
    `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
    static void `$INSTANCE_NAME`_I2CMasterDisableEcAm(void);
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterWriteBuf
****************************************************************************//**
*
*  Automatically writes an entire buffer of data to a slave device.
*  Once the data transfer is initiated by this function, further data transfer
*  is handled by the included ISR.
*  Enables the I2C interrupt and clears `$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT 
*  status.
*
*  \param slaveAddr: 7-bit slave address.
*  \param xferData: Pointer to buffer of data to be sent.
*  \param cnt: Size of buffer to send.
*  \param mode: Transfer mode defines:
*  (1) Whether a start or restart condition is generated at the beginning 
*  of the transfer, and
*  (2) Whether the transfer is completed or halted before the stop 
*  condition is generated on the bus.Transfer mode, mode constants 
*  may be ORed together.
*  - `$INSTANCE_NAME`_I2C_MODE_COMPLETE_XFER - Perform complete transfer 
*    from Start to Stop.
*  - `$INSTANCE_NAME`_I2C_MODE_REPEAT_START - Send Repeat Start instead 
*    of Start. A Stop is generated after transfer is completed unless 
*    NO_STOP is specified.
*  - `$INSTANCE_NAME`_I2C_MODE_NO_STOP Execute transfer without a Stop.
*    The following transfer expected to perform ReStart.
*
* \return
*  Error status.
*  - `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR - Function complete without error. 
*    The master started the transfer.
*  - `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY - Bus is busy. Nothing was sent on
*    the bus. The attempt has to be retried.
*  - `$INSTANCE_NAME`_I2C_MSTR_NOT_READY - Master is not ready for to start
*    transfer. A master still has not completed previous transaction or a 
*    slave operation is in progress (in multi-master-slave configuration).
*    Nothing was sent on the bus. The attempt has to be retried.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrStatus  - used to store current status of I2C Master.
*  `$INSTANCE_NAME`_state       - used to store current state of software FSM.
*  `$INSTANCE_NAME`_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  `$INSTANCE_NAME`_mstrWrBufPtr - used to store pointer to master write buffer.
*  `$INSTANCE_NAME`_mstrWrBufIndex - used to current index within master write
*  buffer.
*  `$INSTANCE_NAME`_mstrWrBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    if(NULL != wrData)  /* Check buffer pointer */
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
        {
            `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

            /* Check bus state */
            errStatus = `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY) ?
                            `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY : `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_I2C_FSM_HALT)
        {
            `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT;
                              errStatus  = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check if master is ready to start  */
    if(`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
    #if (!`$INSTANCE_NAME`_CY_SCBIP_V0 && \
        `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
            `$INSTANCE_NAME`_I2CMasterDisableEcAm();
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

        /* Set up write transaction */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_ADDR;
        `$INSTANCE_NAME`_mstrWrBufIndexTmp = 0u;
        `$INSTANCE_NAME`_mstrWrBufIndex    = 0u;
        `$INSTANCE_NAME`_mstrWrBufSize     = cnt;
        `$INSTANCE_NAME`_mstrWrBufPtr      = (volatile uint8 *) wrData;
        `$INSTANCE_NAME`_mstrControl       = (uint8) mode;

        slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

        `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT;

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);
        `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);

        /* The TX and RX FIFO have to be EMPTY */

        /* Enable interrupt source to catch when address is sent */
        `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);

        /* Generate Start or ReStart */
        if(`$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode))
        {
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;
        }
        else
        {
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;
        }
    }

    `$INSTANCE_NAME`_EnableInt();   /* Release lock */

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterReadBuf
****************************************************************************//**
*
*  Automatically reads an entire buffer of data from a slave device.
*  Once the data transfer is initiated by this function, further data transfer
*  is handled by the included ISR.
*  Enables the I2C interrupt and clears `$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT 
*  status.
*
*  \param slaveAddr: 7-bit slave address.
*  \param xferData: Pointer to buffer of data to be sent.
*  \param cnt: Size of buffer to send.
*  \param mode: Transfer mode defines:
*  (1) Whether a start or restart condition is generated at the beginning 
*  of the transfer, and
*  (2) Whether the transfer is completed or halted before the stop 
*  condition is generated on the bus.Transfer mode, mode constants may 
*  be ORed together. See `$INSTANCE_NAME`_I2CMasterWriteBuf() 
*  function for constants.
*
* \return
*  Error status.See `$INSTANCE_NAME`_I2CMasterWriteBuf() 
*  function for constants.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrStatus  - used to store current status of I2C Master.
*  `$INSTANCE_NAME`_state       - used to store current state of software FSM.
*  `$INSTANCE_NAME`_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  `$INSTANCE_NAME`_mstrRdBufPtr - used to store pointer to master read buffer.
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*  buffer.
*  `$INSTANCE_NAME`_mstrRdBufSize - used to store master read buffer size.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    if(NULL != rdData)
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
        {
            `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

            /* Check bus state */
            errStatus = `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY) ?
                            `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY : `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_I2C_FSM_HALT)
        {
            `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT;
                              errStatus  =  `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check master ready to proceed */
    if(`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
        #if (!`$INSTANCE_NAME`_CY_SCBIP_V0 && \
        `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
            `$INSTANCE_NAME`_I2CMasterDisableEcAm();
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

        /* Set up read transaction */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_ADDR;
        `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
        `$INSTANCE_NAME`_mstrRdBufSize  = cnt;
        `$INSTANCE_NAME`_mstrRdBufPtr   = (volatile uint8 *) rdData;
        `$INSTANCE_NAME`_mstrControl    = (uint8) mode;

        slaveAddress = (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress) | `$INSTANCE_NAME`_I2C_READ_FLAG);

        `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT;

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

        /* TX and RX FIFO have to be EMPTY */

        /* Prepare reading */
        if(`$INSTANCE_NAME`_mstrRdBufSize < `$INSTANCE_NAME`_I2C_FIFO_SIZE)
        {
            /* Reading byte-by-byte */
            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
        }
        else
        {
            /* Receive RX FIFO chunks */
            `$INSTANCE_NAME`_ENABLE_MASTER_AUTO_DATA_ACK;
            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_FULL);
        }

        /* Generate Start or ReStart */
        if(`$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode))
        {
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = (slaveAddress);
        }
        else
        {
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = (slaveAddress);
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;
        }
    }

    `$INSTANCE_NAME`_EnableInt();   /* Release lock */

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendStart
****************************************************************************//**
*
*  Generates Start condition and sends slave address with read/write bit.
*  Disables the I2C interrupt.
*  This function is blocking and does not return until start condition and
*  address byte are sent and ACK/NACK response is received or errors occurred.
*
* \param slaveAddress: Right justified 7-bit Slave address (valid range 
*  8 to 120).
* \param bitRnW: Direction of the following transfer. 
*  It is defined by read/write bit within address byte.
*  - `$INSTANCE_NAME`_I2C_WRITE_XFER_MODE - Set write direction for the 
*    following transfer.
*  - `$INSTANCE_NAME`_I2C_READ_XFER_MODE - Set read direction for the 
*    following transfer.
*
* \return
*  Error status.
*   - `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR - Function complete without error.
*   - `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY - Bus is busy. 
*     Nothing was sent on the bus. The attempt has to be retried.
*   - `$INSTANCE_NAME`_I2C_MSTR_NOT_READY - Master is not ready for to 
*     start transfer.
*     A master still has not completed previous transaction or a slave 
*     operation is in progress (in multi-master-slave configuration).
*     Nothing was sent on the bus. The attempt has to be retried.
*   - `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK - Error condition: Last byte was 
*     NAKed.
*   - `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST - Error condition: Master lost 
*     arbitration.
*   - `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR - Error condition: Master 
*     encountered a bus error. Bus error is misplaced start or stop detection.
*   - `$INSTANCE_NAME`_I2C_MSTR_ERR_ABORT_START - Error condition: The start 
*     condition generation was aborted due to beginning of Slave operation. 
*     This error condition is only applicable for Multi-Master-Slave mode.
*
* \globalvars
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendStart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32  resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Start condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
    {
        /* If bus is free, generate Start condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY;
        }
        else
        {
            `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

        #if (!`$INSTANCE_NAME`_CY_SCBIP_V0 && \
            `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
            `$INSTANCE_NAME`_I2CMasterDisableEcAm();
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

            slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

            if(0u == bitRnW) /* Write direction */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA;
            }
            else /* Read direction */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA;
                         slaveAddress |= `$INSTANCE_NAME`_I2C_READ_FLAG;
            }

            /* TX and RX FIFO have to be EMPTY */

            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress; /* Put address in TX FIFO */
            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;


            while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
            {
                /*
                * Write: wait until address has been transferred
                * Read : wait until address has been transferred, data byte is going to RX FIFO as well.
                */
            }

            /* Check the results of the address phase */
            if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
            {
                errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
            }
            else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
            {
                errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
            }
            else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
                             resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
            }
            else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR set is else condition */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
                             resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
            }

            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            if(0u != resetIp)
            {
                `$INSTANCE_NAME`_SCB_SW_RESET;
            }
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendRestart
****************************************************************************//**
*
*  Generates Restart condition and sends slave address with read/write bit.
*  This function is blocking and does not return until start condition and
*  address are sent and ACK/NACK response is received or errors occurred.
*
* \param slaveAddress: Right justified 7-bit Slave address (valid range 
*   8 to 120).
* \param bitRnW: Direction of the following transfer. It is defined by 
*  read/write bit within address byte. 
*  See `$INSTANCE_NAME`_I2CMasterSendStart() function for constants.
*
* \return
*  Error status. 
*  See `$INSTANCE_NAME`_I2CMasterSendStart() function for constants.
*
* \sideeffect
*  A valid Start or ReStart condition must be generated before calling 
*  this function. This function does nothing if Start or ReStart conditions 
*  failed before this function was called.
*  For read transaction, at least one byte has to be read before ReStart 
*  generation.
*
* \globalvars
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendRestart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating ReStart condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

        if(0u == bitRnW) /* Write direction */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA;
        }
        else  /* Read direction */
        {
            `$INSTANCE_NAME`_state  = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA;
                      slaveAddress |= `$INSTANCE_NAME`_I2C_READ_FLAG;
        }

        /* TX and RX FIFO have to be EMPTY */

        /* Clean-up interrupt status */
        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

        /* A proper ReStart sequence is: generate ReStart, then put an address byte in the TX FIFO.
        * Otherwise the master treats the address in the TX FIFO as a data byte if a previous transfer is write.
        * The write transfer continues instead of ReStart.
        */
        `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;

        while(`$INSTANCE_NAME`_CHECK_I2C_MASTER_CMD(`$INSTANCE_NAME`_I2C_MASTER_CMD_M_START))
        {
            /* Wait until ReStart has been generated */
        }

        /* Put address into TX FIFO */
        `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;

        /* Wait for address to be transferred */
        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until address has been transferred */
        }

        /* Check results of address phase */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
        {
             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }
        else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR set is else condition */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendStop
****************************************************************************//**
*
*  Generates Stop condition on the bus. 
*  The NAK is generated before Stop in case of a read transaction.
*  At least one byte has to be read if a Start or ReStart condition with read 
*  direction was generated before.
*  This function is blocking and does not return until a Stop condition is 
*  generated or error occurred.
*
* \return
*  Error status.
*  See `$INSTANCE_NAME`_I2CMasterSendStart() function for constants.
*
* \sideeffect
*  A valid Start or ReStart condition must be generated before calling 
*  this function. This function does nothing if Start or ReStart conditions 
*  failed before this function was called.
*  For read transaction, at least one byte has to be read before ReStart 
*  generation.
*
* \globalvars
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendStop(void)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Stop condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        /*
        * Write direction: generates Stop
        * Read  direction: generates NACK and Stop
        */
        `$INSTANCE_NAME`_I2C_MASTER_GENERATE_STOP;

        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP     |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until Stop has been generated */
        }

        /* Check Stop generation */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
            resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }
        else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR is set */
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
            resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP     |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterWriteByte
****************************************************************************//**
*
*  Sends one byte to a slave.
*  This function is blocking and does not return until byte is transmitted
*  or error occurred.
*
* \param data: The data byte to send to the slave.
*
* \return
*  Error status.
*  See `$INSTANCE_NAME`_I2CMasterSendStart() function for constants.
*
* \sideeffect
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*
* \globalvars
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterWriteByte(uint32 theByte)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before write byte */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        `$INSTANCE_NAME`_TX_FIFO_WR_REG = theByte;

        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until byte has been transferred */
        }

        /* Check results after byte was sent */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }
        else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR set is */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterReadByte
****************************************************************************//**
*
*  Reads one byte from a slave and generates ACK or prepares to generate NAK. 
*  The NAK will be generated before Stop or ReStart condition by 
*  `$INSTANCE_NAME`_I2CMasterSendStop() or 
*  `$INSTANCE_NAME`_I2CMasterSendRestart() function appropriately.
*  This function is blocking. It does not return until a byte is received or 
*  an error occurs.
*
* \param ackNack: Response to received byte.
*  - `$INSTANCE_NAME`_I2C_ACK_DATA - Generates ACK. 
*     The master notifies slave that transfer continues.
*  - `$INSTANCE_NAME`_I2C_NAK_DATA - Prepares to generate NAK.
*     The master will notify slave that transfer is completed.
*
* \return
*  Byte read from the slave. In case of error the MSB of returned data 
*  is set to 1.
*
* \sideeffect
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*
* \globalvars
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterReadByte(uint32 ackNack)
{
    uint32 theByte;

    /* Return invalid byte in case BUS_ERR happen during receiving */
    theByte = `$INSTANCE_NAME`_I2C_INVALID_BYTE;

    /* Check FSM state before read byte */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        while((!`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY)) &&
              (!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR)))
        {
            /* Wait until byte has been received */
        }

        /* Check the results after the byte was sent */
        if(`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
        {
            theByte = `$INSTANCE_NAME`_RX_FIFO_RD_REG;

            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);

            if(0u == ackNack)
            {
                `$INSTANCE_NAME`_I2C_MASTER_GENERATE_ACK;
            }
            else
            {
                /* NACK is generated by Stop or ReStart command */
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
            }
        }
        else
        {
            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(theByte);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterGetReadBufSize
****************************************************************************//**
*
*  Returns the number of bytes that has been transferred with an
*  `$INSTANCE_NAME`_I2CMasterReadBuf() function.
*
* \return
*  Byte count of transfer. If the transfer is not yet complete, it returns
*  the byte count transferred so far.
*
* \sideeffect
*  This function returns not valid value if 
*  `$INSTANCE_NAME`_I2C_MSTAT_ERR_ARB_LOST or
*  `$INSTANCE_NAME`_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*  buffer.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterGetReadBufSize(void)
{
    return(`$INSTANCE_NAME`_mstrRdBufIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterGetWriteBufSize
****************************************************************************//**
*
*  Returns the number of bytes that have been transferred with an
*  SCB_I2CMasterWriteBuf() function.
*
* \return
*   Byte count of transfer. If the transfer is not yet complete, it returns
*   zero unit transfer completion.
*
* \sideeffect
*   This function returns not valid value if 
*   `$INSTANCE_NAME`_I2C_MSTAT_ERR_ARB_LOST or 
*   `$INSTANCE_NAME`_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrWrBufIndex - used to current index within master write
*  buffer.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterGetWriteBufSize(void)
{
    return(`$INSTANCE_NAME`_mstrWrBufIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearReadBuf
****************************************************************************//**
*
*  Resets the read buffer pointer back to the first byte in the buffer.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*   buffer.
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CMasterClearReadBuf(void)
{
    `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

    `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
    `$INSTANCE_NAME`_mstrStatus    &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT;

    `$INSTANCE_NAME`_EnableInt();   /* Release lock */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearWriteBuf
****************************************************************************//**
*
*  Resets the write buffer pointer back to the first byte in the buffer.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*   buffer.
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CMasterClearWriteBuf(void)
{
    `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

    `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
    `$INSTANCE_NAME`_mstrStatus    &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT;

    `$INSTANCE_NAME`_EnableInt();   /* Release lock */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterStatus
****************************************************************************//**
*
*  Returns the master's communication status.
*
* \return
*  Current status of I2C master. This status incorporates status constants. 
*  Each constant is a bit field value. The value returned may have multiple 
*  bits set to indicate the status of the read or write transfer.
*  - `$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT - Read transfer complete.
*    The error condition status bits must be checked to ensure that 
*    read transfer was completed successfully.
*  - `$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT - Write transfer complete.
*    The error condition status bits must be checked to ensure that write 
*    transfer was completed successfully.
*  - `$INSTANCE_NAME`_I2C_MSTAT_XFER_INP - Transfer in progress.
*  - `$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT - Transfer has been halted. 
*    The I2C bus is waiting for ReStart or Stop condition generation.
*  - `$INSTANCE_NAME`_I2C_MSTAT_ERR_SHORT_XFER - Error condition: Write 
*    transfer completed before all bytes were transferred. The slave NAKed 
*    the byte which was expected to be ACKed.
*  - `$INSTANCE_NAME`_I2C_MSTAT_ERR_ADDR_NAK - Error condition: Slave did 
*    not acknowledge address.
*  - `$INSTANCE_NAME`_I2C_MSTAT_ERR_ARB_LOST - Error condition: Master lost 
*    arbitration during communications with slave.
*  - `$INSTANCE_NAME`_I2C_MSTAT_ERR_BUS_ERROR - Error condition: bus error 
*    occurred during master transfer due to misplaced Start or Stop 
*    condition on the bus.
*  - `$INSTANCE_NAME`_I2C_MSTAT_ERR_ABORT_XFER - Error condition: Slave was 
*    addressed by another master while master performed the start condition 
*    generation. As a result, master has automatically switched to slave 
*    mode and is responding. The master transaction has not taken place
*    This error condition only applicable for Multi-Master-Slave mode.
*  - `$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER - Error condition: This is the 
*    ORed value of all error conditions provided above.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterStatus(void)
{
    uint32 status;

    `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

    status = (uint32) `$INSTANCE_NAME`_mstrStatus;

    if (`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        /* Add status of master pending transaction: MSTAT_XFER_INP */
        status |= (uint32) `$INSTANCE_NAME`_I2C_MSTAT_XFER_INP;
    }

    `$INSTANCE_NAME`_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearStatus
****************************************************************************//**
*
*  Clears all status flags and returns the master status.
*
* \return
*  Current status of master. See the `$INSTANCE_NAME`_I2CMasterStatus() 
*  function for constants.
*
* \globalvars
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterClearStatus(void)
{
    uint32 status;

    `$INSTANCE_NAME`_DisableInt();  /* Lock from interruption */

    /* Read and clear master status */
    status = (uint32) `$INSTANCE_NAME`_mstrStatus;
    `$INSTANCE_NAME`_mstrStatus = `$INSTANCE_NAME`_I2C_MSTAT_CLEAR;

    `$INSTANCE_NAME`_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CReStartGeneration
****************************************************************************//**
*
*  Generates a ReStart condition:
*  - SCB IP V1 and later: Generates ReStart using the scb IP functionality
*    Sets the I2C_MASTER_CMD_M_START and I2C_MASTER_CMD_M_NACK (if the previous
*    transaction was read) bits in the SCB.I2C_MASTER_CMD register.
*    This combination forces the master to generate ReStart.
*
*  - SCB IP V0: Generates Restart using the GPIO and scb IP functionality.
*    After the master completes write or read, the SCL is stretched.
*    The master waits until SDA line is released by the slave. Then the GPIO
*    function is enabled and the scb IP disabled as it already does not drive
*    the bus. In case of the previous transfer was read, the NACK is generated
*    by the GPIO. The delay of tLOW is added to manage the hold time.
*    Set I2C_M_CMD.START and enable the scb IP. The ReStart generation
*    is started after the I2C function is enabled for the SCL.
*    Note1: the scb IP due re-enable generates Start but on the I2C bus it
*           appears as ReStart.
*    Note2: the I2C_M_CMD.START is queued if scb IP is disabled.
*    Note3: the I2C_STATUS_M_READ is cleared is address was NACKed before.
*
* \sideeffect
*  SCB IP V0: The NACK generation by the GPIO may cause a greater SCL period
*             than expected for the selected master data rate.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CReStartGeneration(void)
{
#if(`$INSTANCE_NAME`_CY_SCBIP_V0)
    /* Generates Restart use GPIO and scb IP functionality. Ticket ID#143715,
    * ID#145238 and ID#173656.
    */
    uint32 status = `$INSTANCE_NAME`_I2C_STATUS_REG;

    while(`$INSTANCE_NAME`_WAIT_SDA_SET_HIGH)
    {
        /* Wait when slave release SDA line: SCL tHIGH is complete */
    }

    /* Prepare DR register to drive SCL line */
    `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_LOW);

    /* Switch HSIOM to GPIO: SCL goes low */
    `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(`$INSTANCE_NAME`_HSIOM_GPIO_SEL);

    /* Disable SCB block */
    `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED;

    if(0u != (status & `$INSTANCE_NAME`_I2C_STATUS_M_READ))
    {
        /* Generate NACK use GPIO functionality */
        `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_LOW);
        CyDelayUs(`$INSTANCE_NAME`_I2C_TLOW_TIME); /* Count tLOW */

        `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_HIGH);
        while(`$INSTANCE_NAME`_WAIT_SCL_SET_HIGH)
        {
            /* Wait until slave releases SCL in case if it stretches */
        }
        CyDelayUs(`$INSTANCE_NAME`_I2C_THIGH_TIME); /* Count tHIGH */
    }

    /* Count tLOW as hold time for write and read */
    `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_LOW);
    CyDelayUs(`$INSTANCE_NAME`_I2C_TLOW_TIME); /* Count tLOW */

    /* Set command for Start generation: it will appear */
    `$INSTANCE_NAME`_I2C_MASTER_CMD_REG = `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START;

    /* Enable SCB block */
    `$INSTANCE_NAME`_CTRL_REG |= (uint32) `$INSTANCE_NAME`_CTRL_ENABLED;

    /* Switch HSIOM to I2C: */
    `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(`$INSTANCE_NAME`_HSIOM_I2C_SEL);

    /* Revert SCL DR register */
    `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_HIGH);
#else
    uint32 cmd;

    /* Generates ReStart use scb IP functionality */
    cmd  = `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START;
    cmd |= `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_M_READ) ?
                (`$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK) : (0u);

    `$INSTANCE_NAME`_I2C_MASTER_CMD_REG = cmd;
#endif /* (`$INSTANCE_NAME`_CY_SCBIP_V1) */
}

#endif /* (`$INSTANCE_NAME`_I2C_MASTER_CONST) */


#if (!`$INSTANCE_NAME`_CY_SCBIP_V0 && \
    `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CMasterDisableEcAm
    ****************************************************************************//**
    *
    *  Disables externally clocked address match to enable master operation
    *  in active mode.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_I2CMasterDisableEcAm(void)
    {
        /* Disables externally clocked address match to enable master operation in active mode.
        * This applicable only for Multi-Master-Slave with wakeup enabled. Ticket ID#192742 */
        if (0u != (`$INSTANCE_NAME`_CTRL_REG & `$INSTANCE_NAME`_CTRL_EC_AM_MODE))
        {
            /* Enable external address match logic */
            `$INSTANCE_NAME`_Stop();
            `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_EC_AM_MODE;
            `$INSTANCE_NAME`_Enable();
        }
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */


/* [] END OF FILE */
