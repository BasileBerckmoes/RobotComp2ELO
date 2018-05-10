/*******************************************************************************
* File Name: `$INSTANCE_NAME`_BOOT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of bootloader communication APIs for the
*  SM/PM Bus Slave component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"


/***************************************
*    Bootloader Variables
***************************************/

#if(defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN))
    uint8 `$INSTANCE_NAME`_btldrStatus;
#endif /* defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN) */

/* Naming convention is from PMBus host perspective, i.e. host reads 
* from btldrReadBuf[], which is written by bootloader.
*/ 
#ifdef `$INSTANCE_NAME`_BTLDR_READ_EN   
    uint8 `$INSTANCE_NAME`_btldrReadBuf[`$INSTANCE_NAME`_MAX_BUFFER_SIZE];
#endif /* `$INSTANCE_NAME`_BTLDR_READ_EN */

#ifdef `$INSTANCE_NAME`_BTLDR_WRITE_EN
    uint8 `$INSTANCE_NAME`_btldrWriteBuf[`$INSTANCE_NAME`_MAX_BUFFER_SIZE];
#endif /* `$INSTANCE_NAME`_BTLDR_WRITE_EN */

#if(defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN))


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_CyBtldrCommStart
    ****************************************************************************
    *
    * Summary:
    *  Starts the communication component and enables the interrupt.
    *  The read buffer initial state is full and the read always is 0xFFu.
    *  The write buffer is clear and ready to receive a command.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function enables the component interrupt. If I2C is enabled
    *  without the interrupt enabled, it can lock up the I2C bus.
    *
    ***************************************************************************/
    void `$INSTANCE_NAME`_CyBtldrCommStart(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStart")`
    {
        `$INSTANCE_NAME`_Start();
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_CyBtldrCommStop
    ****************************************************************************
    *
    * Summary:
    *  Disables the communication component and disables the interrupt.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    ***************************************************************************/
    void `$INSTANCE_NAME`_CyBtldrCommStop(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStop")`
    {
        `$INSTANCE_NAME`_Stop();
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_CyBtldrCommReset
    ****************************************************************************
    *
    * Summary:
    *  Set buffers to the initial state and reset the statuses.
    *  The read buffer initial state is full and the read always is 0xFFu.
    *  The write buffer is clear and ready to receive a command.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    ***************************************************************************/
    void `$INSTANCE_NAME`_CyBtldrCommReset(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommReset")`
    {        
        `$INSTANCE_NAME`_btldrStatus = 0u;
    }

#endif /* defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN) */

#ifdef `$INSTANCE_NAME`_BTLDR_READ_EN

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_CyBtldrCommWrite
    ****************************************************************************
    *
    * Summary:
    *  Transmits the status of an executed command to the Host.
    *  The function updates the I2C read buffer with a response and releases it
    *  to the host. All reads return 0xFF till the buffer will be released. All
    *  bytes are transferred by the I2C ISR.
    *  The function waits with timeout till all bytes are read.
    *  After exiting this function the reads return 0xFF.
    *
    * Parameters:
    *  pData:   pointer to data buffer with response command.
    *  size:    number of bytes required to be transmitted.
    *  count:   actual size of data was transmitted.
    *  timeOut: timeout value in tries of 10mS.
    *
    * Return:
    *  Status of transmit operation.
    *   CYRET_EMPTY   - in case data was not send.
    *   CYRET_SUCCESS - in case data was sent.
    *
    * Theory:
    *  This function should be called after a command to unblock the
    *  bus was received.
    *  The Exit Bootloader does not require this.
    *  
    * Side Effects:
    *  Temporary enables the I2C interrupt when called on a start of clock
    *  stretching during "Bootloader Write" transaction but disables the
    *  interrupt before returning from this function (to meet the manual command
    *  handling behavior). When called not using "Bootloader Write" - always
    *  leaves the I2C interrupt enabled.
    *
    ***************************************************************************/
    cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 * pData, uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommWrite")`
    {
        cystatus status = CYRET_TIMEOUT;
        uint16 timeOutms;

        timeOutms = 10u * (uint16)timeOut;    /* To be in 10mS units, really check 1mS*10 */

        `$INSTANCE_NAME`_DisableInt();

        `$INSTANCE_NAME`_btldrStatus &= (uint8)~`$INSTANCE_NAME`_BTLDR_RD_CMPT; /* Clear the read done flag */
        `$INSTANCE_NAME`_btldrReadBuf[0u] = (uint8)size; /* Byte count for this transaction */
        (void) memcpy((void *)&`$INSTANCE_NAME`_btldrReadBuf[1u], (`$ConstQualifier`void *)pData, `$LenType`size);

        `$INSTANCE_NAME`_EnableInt();
        
        /* Process the buffer */
        while(timeOutms != 0u)
        {
            /* Wait for transaction to complete */
            if(0u != (`$INSTANCE_NAME`_btldrStatus & `$INSTANCE_NAME`_BTLDR_RD_CMPT))
            {
                --`$INSTANCE_NAME`_bufferIndex; /* Byte count is not included */
                *count = (uint16)`$INSTANCE_NAME`_bufferIndex; 
    	        status = CYRET_SUCCESS;
                break;
            }
            CyDelay(1u); /* Wait 1mS for data to become available */
            --timeOutms;
        }
        return(status);
    }

#endif /* `$INSTANCE_NAME`_BTLDR_READ_EN */

#ifdef `$INSTANCE_NAME`_BTLDR_WRITE_EN

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_CyBtldrCommRead
    ****************************************************************************
    *
    * Summary:
    *  Receives a command from the Host.
    *  All bytes are received by the I2C ISR and stored in the internal I2C
    *  buffer. The function checks status with timeout to determine the end of
    *  transfer and then copy data to the bootloader buffer.
    *  After exiting this function, the I2C ISR is able to receive more data.
    *
    * Parameters:
    *  pData:   pointer to data buffer to store command.
    *  size:    maximum number of bytes which could to be passed back.
    *  count:   actual size of data was received.
    *  timeOut: timeout value in tries of 10mS.
    *
    * Return:
    *  Status of receive operation.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_CyBtldrCommRead(uint8 * pData, uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommRead")`
    {
        cystatus status = CYRET_TIMEOUT;
        uint16 timeOutms;
        
        timeOutms = 10u * (uint16)timeOut;    /* To be in 10mS units, really check 1mS*10 */
        
        while(timeOutms != 0u)
        {
            /* Wait for SM/PMBus master to complete write */
            if(0u != (`$INSTANCE_NAME`_btldrStatus & `$INSTANCE_NAME`_BTLDR_WR_CMPT))
            {
                /* Byte 0 contains byte count */
                *count = (`$INSTANCE_NAME`_btldrWriteBuf[0u] < size) ? `$INSTANCE_NAME`_btldrWriteBuf[0u] : size;
                (void)memcpy((void *)pData, (`$ConstQualifier`void *)&`$INSTANCE_NAME`_btldrWriteBuf[1u], `$LenType`*count);
                
                /* Clear write complete status */
                `$INSTANCE_NAME`_btldrStatus &= (uint8)~`$INSTANCE_NAME`_BTLDR_WR_CMPT;
                status = CYRET_SUCCESS;
                break;
            }
            
            CyDelay(1u); /* Wait 1mS for data to become available */
            --timeOutms;
        }

        return(status);
    }

#endif /* `$INSTANCE_NAME`_BTLDR_WRITE_EN */


/* [] END OF FILE */
