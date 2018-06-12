/*******************************************************************************
* File Name: `$INSTANCE_NAME`INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the code that operates during the interrupt service
*  routine.  For this component, most of the runtime code is located in
*  the ISR.
*
*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR
********************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.
*
* Parameters:
*  `$INSTANCE_NAME`_dataPtrS1 - The global variable which stores the pointer to the
*  data exposed to an I2C master for the first slave address.
*
*  `$INSTANCE_NAME`_rwOffsetS1 - The global variable which stores an offset for read
*  and write operations, is set at each write sequence of the first slave
*  address.
*
*  `$INSTANCE_NAME`_rwIndexS1: global variable, which stores pointer to the next
*  value to be read or written for the first slave address.
*
* `$INSTANCE_NAME`_wrProtectS1 - The global variable which stores an offset where data
*  is read only for the first slave address.
*
* `$INSTANCE_NAME`_bufSizeS1 - The global variable which stores the size of a data array
*  exposed to the I2C master for the first slave address.
*
*  `$INSTANCE_NAME`_dataPtrS2 - The global variable which stores a pointer to the
*  data exposed to the I2C master for the second slave address.
*
*  `$INSTANCE_NAME`_rwOffsetS2 - The global variable which stores an offset for read
*  and write operations, is set at each write sequence of the second slave
*  device.
*
*  `$INSTANCE_NAME`_rwIndexS2 - The global variable which stores a pointer to the next
*  value to be read or written for the second slave address.
*
* `$INSTANCE_NAME`_wrProtectS2 - The global variable which stores an offset where data
*  is "Read only" for the second slave address.  ??
*
* `$INSTANCE_NAME`_bufSizeS2 - The global variable which stores the size of a data array
*  exposed to the I2C master for the second slave address.
*
* `$INSTANCE_NAME`_curState - The global variable which stores a current state of an
*  I2C state machine.
*
*  `$INSTANCE_NAME`_curStatus - The global variable which stores the current status of
*  the component.
*
* Return:
*  `$INSTANCE_NAME`_rwOffsetS1 - The global variable which stores an offset for read
*  and write operations, is set at each write sequence of the first slave
*  address and is reset if a received slave address matches the first slave address
*  and a next operation will be read.
*
*  `$INSTANCE_NAME`_rwIndexS1 - The global variable which stores a pointer to the next
*  value to be read or written for the first slave address. Is set to
*  `$INSTANCE_NAME`_rwOffsetS1 and than incremented if a received slave address
*  matches the first slave address and a next operation will be read.
*
*  `$INSTANCE_NAME`_rwOffsetS2 - The global variable which stores an offset for read
*  and write operations, is set at each write sequence of the second slave
*  address. This variable changes if a new sub-address is passed to the slave.
*
*  `$INSTANCE_NAME`_rwIndexS2 - The global variable which stores a pointer to the next
*  value to be read or written for the second slave address. This variable
*  changes if a new sub-address is passed to the slave.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_ISR)
{
    static uint8  tmp8;
    static uint8  tmpCsr;

#if (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_16BIT)
    static uint16 tmp16;
#endif /* (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_16BIT) */

#ifdef `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK
    `$INSTANCE_NAME`_ISR_EntryCallback();
#endif /* `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK */
    
    /* Entry from interrupt
    *  In the hardware address compare mode, we can assume we only get interrupted
    *  when a valid address is recognized. In the software address compare mode,
    *  we have to check every address after a start condition.
    */

    /* Make copy to check Stop condition after bus has been released */
    tmpCsr = `$INSTANCE_NAME`_CSR_REG;

    /* Check for address phase of the transaction */
    if (`$INSTANCE_NAME`_IS_BIT_SET(tmpCsr, `$INSTANCE_NAME`_CSR_ADDRESS))
    {
        #if (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES)

            /* Get slave address from data register */
            tmp8 = ((`$INSTANCE_NAME`_DATA_REG >> `$INSTANCE_NAME`_ADDRESS_SHIFT) & `$INSTANCE_NAME`_SADDR_MASK);

            if (tmp8 == `$INSTANCE_NAME`_addrS1)   /* Check for address 1  */
            {
                if (`$INSTANCE_NAME`_IS_BIT_SET(`$INSTANCE_NAME`_DATA_REG, `$INSTANCE_NAME`_READ_FLAG))
                {  /* Prepare next read op, get data and place in register */

                    /* Load first data byte  */
                    `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_dataPtrS1[`$INSTANCE_NAME`_rwOffsetS1];

                    /* ACK and transmit */
                    `$INSTANCE_NAME`_CSR_REG = (`$INSTANCE_NAME`_CSR_ACK | `$INSTANCE_NAME`_CSR_TRANSMIT);

                    /* Set index to offset */
                    `$INSTANCE_NAME`_rwIndexS1 = `$INSTANCE_NAME`_rwOffsetS1;

                    /* Advance to data location */
                    ++`$INSTANCE_NAME`_rwIndexS1;

                    /* Set Read busy status */
                    `$INSTANCE_NAME`_curStatus |= `$INSTANCE_NAME`_STATUS_RD1BUSY;

                    /* Prepare for read transaction */
                    `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV1_RD_DATA;
                }
                else  /* Start of a Write transaction, reset pointers, first byte is address */
                {  /* Prepare next operation to write offset */

                    /* ACK and ready to receive sub address */
                    `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                    /* Set Write busy status */
                    `$INSTANCE_NAME`_curStatus |= `$INSTANCE_NAME`_STATUS_WR1BUSY;

                    /* Prepare for read transaction */
                    `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV1_WR_ADDR;

                    /* Stop Interrupt Enable */
                    `$INSTANCE_NAME`_CFG_REG  |= `$INSTANCE_NAME`_CFG_STOP_IE;

                }  /* Prepared for next Write transaction */
            }   /* Slave address #1 is processed */
            else if (tmp8 == `$INSTANCE_NAME`_addrS2)   /* Check for address 2  */
            {
                if (`$INSTANCE_NAME`_IS_BIT_SET(`$INSTANCE_NAME`_DATA_REG, `$INSTANCE_NAME`_READ_FLAG))
                {  /* Prepare next read op, get data and place in register */

                    /* Load first data byte  */
                    `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_dataPtrS2[`$INSTANCE_NAME`_rwOffsetS2];

                    /* ACK and transmit */
                    `$INSTANCE_NAME`_CSR_REG = (`$INSTANCE_NAME`_CSR_ACK | `$INSTANCE_NAME`_CSR_TRANSMIT);

                    /* Reset pointer to previous offset */
                    `$INSTANCE_NAME`_rwIndexS2 = `$INSTANCE_NAME`_rwOffsetS2;

                    /* Advance to data location */
                    ++`$INSTANCE_NAME`_rwIndexS2;

                    /* Set read busy status */
                    `$INSTANCE_NAME`_curStatus |= `$INSTANCE_NAME`_STATUS_RD2BUSY;

                    /* Prepare for read transaction */
                    `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV2_RD_DATA;

                }  /* Prepared for next Read transaction */
                else  /* Start of write transfer, reset ptrs, 1st byte is address */
                {  /* Prepare next operation to write offset */

                    /* ACK and ready to receive address */
                    `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                    /* Set Write busy status */
                    `$INSTANCE_NAME`_curStatus |= `$INSTANCE_NAME`_STATUS_WR2BUSY;

                    /* Prepare for read transaction */
                    `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV2_WR_ADDR;

                    /* Enable interrupt on Stop */
                    `$INSTANCE_NAME`_CFG_REG  |= `$INSTANCE_NAME`_CFG_STOP_IE;
                } /* Prepared for the next Write transaction */
            }
            else   /* No address match */
            {   /* NAK address Match  */
                `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
            }
        #else /* One slave address - hardware address matching */

            if (`$INSTANCE_NAME`_IS_BIT_SET(`$INSTANCE_NAME`_DATA_REG, `$INSTANCE_NAME`_READ_FLAG))
            {   /* Prepare next read op, get data and place in register */

                /* Load first data byte  */
                `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_dataPtrS1[`$INSTANCE_NAME`_rwOffsetS1];

                /* ACK and transmit */
                `$INSTANCE_NAME`_CSR_REG = (`$INSTANCE_NAME`_CSR_ACK | `$INSTANCE_NAME`_CSR_TRANSMIT);

                /* Reset pointer to previous offset */
                `$INSTANCE_NAME`_rwIndexS1 = `$INSTANCE_NAME`_rwOffsetS1;

                /* Advance to data location */
                ++`$INSTANCE_NAME`_rwIndexS1;

                /* Set read busy status */
                `$INSTANCE_NAME`_curStatus |= `$INSTANCE_NAME`_STATUS_RD1BUSY;

                /* Prepare for read transaction */
                `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV1_RD_DATA;
            }
            else  /* Start of write transfer, reset ptrs, 1st byte is address */
            {   /* Prepare next operation to write offset */

                /* ACK and ready to receive address */
                `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                /* Set Write activity */
                `$INSTANCE_NAME`_curStatus |= `$INSTANCE_NAME`_STATUS_WR1BUSY;

                /* Prepare for read transaction */
                `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV1_WR_ADDR;

                /* Enable interrupt on stop */
                `$INSTANCE_NAME`_CFG_REG |= `$INSTANCE_NAME`_CFG_STOP_IE;
            }
        #endif  /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES) */
    }
    else if (`$INSTANCE_NAME`_IS_BIT_SET(tmpCsr, `$INSTANCE_NAME`_CSR_BYTE_COMPLETE))
    {   /* Check for data transfer */

        /* Data transfer state machine */
        switch (`$INSTANCE_NAME`_curState)
        {
            /* Address written from Master to Slave. */
            case `$INSTANCE_NAME`_SM_DEV1_WR_ADDR:

                /* If 8-bit interface, Advance to WR_Data, else to ADDR2 */
                #if (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_8BIT)
                    tmp8 = `$INSTANCE_NAME`_DATA_REG;
                    if (tmp8 < `$INSTANCE_NAME`_bufSizeS1)
                    {
                        /* ACK and ready to receive data */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                        /* Set offset to new value */
                        `$INSTANCE_NAME`_rwOffsetS1 = tmp8;

                        /* Reset index to offset value */
                        `$INSTANCE_NAME`_rwIndexS1 = tmp8;

                        /* Prepare for write transaction */
                        `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV1_WR_DATA;
                    }
                    else    /* Out of range, NAK data and don't set offset */
                    {
                        /* NAK master */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
                    }

                #else   /* 16-bit */
                    /* Save MSB of address */
                    tmp16 = `$INSTANCE_NAME`_DATA_REG;

                    /* ACK and ready to receive address */
                    `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                    /* Prepare to get LSB of address */
                    `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV1_WR_ADDR_LSB;

                #endif  /* (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_8BIT) */

            break;  /* case `$INSTANCE_NAME`_SM_DEV1_WR_ADDR */

            #if (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_16BIT)

                /* Only used with 16-bit interface */
                case `$INSTANCE_NAME`_SM_DEV1_WR_ADDR_LSB:

                    /* Create offset */
                    tmp16 = (uint16) (tmp16 << `$INSTANCE_NAME`_ADDRESS_LSB_SHIFT) | `$INSTANCE_NAME`_DATA_REG;

                    /* Check range */
                    if(tmp16 < `$INSTANCE_NAME`_bufSizeS1)
                    {
                        /* ACK and ready to receive address */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                        /* Set offset to new value */
                        `$INSTANCE_NAME`_rwOffsetS1 = tmp16;

                        /* Reset index to offset value */
                        `$INSTANCE_NAME`_rwIndexS1 = tmp16;

                        /* Prepare for write transaction */
                        `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV1_WR_DATA;
                    }
                    else    /* Out of range, NAK data and don't set offset */
                    {
                        /* NAK master */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
                    }
                break; /* case `$INSTANCE_NAME`_SM_DEV1_WR_ADDR_LSB */

            #endif  /* (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_16BIT) */


            /* Data written from master to slave. */
            case `$INSTANCE_NAME`_SM_DEV1_WR_DATA:

                /* Check for valid range */
                if (`$INSTANCE_NAME`_rwIndexS1 < `$INSTANCE_NAME`_wrProtectS1)
                {
                    /* Get data, to ACK quickly */
                    tmp8 = `$INSTANCE_NAME`_DATA_REG;

                    /* ACK and ready to receive sub address */
                    `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                    /* Write data to array */
                    `$INSTANCE_NAME`_dataPtrS1[`$INSTANCE_NAME`_rwIndexS1] = tmp8;

                    /* Increment pointer */
                    `$INSTANCE_NAME`_rwIndexS1++;
                }
                else
                {
                    /* NAK cause beyond write area */
                    `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
                }
            break;  /* `$INSTANCE_NAME`_SM_DEV1_WR_DATA */


            /* Data read by master from slave */
            case `$INSTANCE_NAME`_SM_DEV1_RD_DATA:

                /* Check ACK/NAK */
                if ((tmpCsr & `$INSTANCE_NAME`_CSR_LRB) == `$INSTANCE_NAME`_CSR_LRB_ACK)
                {
                    /* Check for valid range */
                    if (`$INSTANCE_NAME`_rwIndexS1 < `$INSTANCE_NAME`_bufSizeS1)
                    {
                        /* Get data from array */
                        `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_dataPtrS1[`$INSTANCE_NAME`_rwIndexS1];

                        /* Send Data */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_TRANSMIT;

                        /* Increment pointer */
                        ++`$INSTANCE_NAME`_rwIndexS1;
                    }
                    else    /* No valid range */
                    {
                        /* Out of range send FFs */
                        `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_DUMMY_DATA;

                        /* Send Data */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_TRANSMIT;
                    }
                }
                else    /* Data was NAKed */
                {
                    /* Send dummy data at the end of read transaction */
                    `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_DUMMY_DATA;

                    /* Clear transmit bit at the end of read transaction */
                    `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;

                    /* Clear Busy Flag */
                    `$INSTANCE_NAME`_curStatus &= ((uint8) ~`$INSTANCE_NAME`_STATUS_BUSY);

                    /* Error or Stop, reset state */
                    `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_IDLE;

                }
            break;  /* `$INSTANCE_NAME`_SM_DEV1_RD_DATA */

            /* Second Device Address */
            #if (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES)

                case `$INSTANCE_NAME`_SM_DEV2_WR_ADDR:

                    /* If 8-bit interface, Advance to WR_Data, else to ADDR2 */
                    #if (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_8BIT)

                        tmp8 = `$INSTANCE_NAME`_DATA_REG;
                        if (tmp8 < `$INSTANCE_NAME`_bufSizeS2)
                        {
                            /* ACK and ready to receive address */
                            `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                            /* Set offset to new value */
                            `$INSTANCE_NAME`_rwOffsetS2 = tmp8;

                            /* Reset index to offset value */
                            `$INSTANCE_NAME`_rwIndexS2 = tmp8;

                            /* Prepare for write transaction */
                            `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV2_WR_DATA;
                        }
                        else    /* Out of range, NAK data and don't set offset */
                        {
                            /* NAK master */
                            `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
                        }
                    #else
                        /* Save LSB of address */
                        tmp16 = `$INSTANCE_NAME`_DATA_REG;

                        /* ACK and ready to receive address */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                        /* Prepare to get LSB of address */
                        `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV2_WR_ADDR_LSB;
                    #endif  /* (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_8BIT) */

                break;  /* `$INSTANCE_NAME`_SM_DEV2_WR_ADDR */

                #if (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_16BIT)

                    /* Only used with 16-bit interface */
                    case `$INSTANCE_NAME`_SM_DEV2_WR_ADDR_LSB:
                        /* Create offset */
                        tmp16 = (uint16) (tmp16 << 8u) | `$INSTANCE_NAME`_DATA_REG;
                        if (tmp16 < `$INSTANCE_NAME`_bufSizeS2)
                        {
                            /* ACK and ready to receive address */
                            `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                            /* Set offset to new value */
                            `$INSTANCE_NAME`_rwOffsetS2 = tmp16;

                            /* Reset index to offset value */
                            `$INSTANCE_NAME`_rwIndexS2 = tmp16;

                            /* Prepare for write transaction */
                            `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_DEV2_WR_DATA;
                        }
                        else    /* Out of range, NAK data and don't set offset */
                        {
                            /* NAK master */
                            `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
                        }
                        break; /* `$INSTANCE_NAME`_SM_DEV2_WR_ADDR_LSB */

                #endif   /* (`$INSTANCE_NAME`_SUBADDR_WIDTH == `$INSTANCE_NAME`_SUBADDR_16BIT) */


                /* Data written from master to slave. */
                case `$INSTANCE_NAME`_SM_DEV2_WR_DATA:

                    /* Check for valid range */
                    if (`$INSTANCE_NAME`_rwIndexS2 < `$INSTANCE_NAME`_wrProtectS2)
                    {
                        /* Get data, to ACK quickly */
                        tmp8 = `$INSTANCE_NAME`_DATA_REG;

                        /* ACK and ready to receive sub address */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_ACK;

                        /* Write data to array */
                        `$INSTANCE_NAME`_dataPtrS2[`$INSTANCE_NAME`_rwIndexS2] = tmp8;

                        /* Inc pointer */
                        ++`$INSTANCE_NAME`_rwIndexS2;
                    }
                    else
                    {
                        /* NAK cause beyond write area */
                        `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
                    }
                    break;  /* `$INSTANCE_NAME`_SM_DEV2_WR_DATA */

                    /* Data read by master from slave */
                    case `$INSTANCE_NAME`_SM_DEV2_RD_DATA:

                        if ((tmpCsr & `$INSTANCE_NAME`_CSR_LRB) == `$INSTANCE_NAME`_CSR_LRB_ACK)
                        {   /* ACKed */
                            /* Check for valid range */
                            if (`$INSTANCE_NAME`_rwIndexS2 < `$INSTANCE_NAME`_bufSizeS2)
                            {   /* Check ACK/NAK */
                                /* Get data from array */
                                `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_dataPtrS2[`$INSTANCE_NAME`_rwIndexS2];

                                /* Send Data */
                                `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_TRANSMIT;

                                /* Increment pointer */
                                `$INSTANCE_NAME`_rwIndexS2++;
                            }
                            else    /* Not valid range */
                            {
                                /* Out of range send FFs */
                                `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_DUMMY_DATA;

                                /* Send Data */
                                `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_TRANSMIT;
                            }
                        }
                        else    /* NAKed */
                        {
                            /* Out of range send FFs */
                            `$INSTANCE_NAME`_DATA_REG = `$INSTANCE_NAME`_DUMMY_DATA;

                            /* Send Data */
                            `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_TRANSMIT;

                            /* Clear busy status */
                            `$INSTANCE_NAME`_curStatus &= ((uint8) ~`$INSTANCE_NAME`_STATUS_BUSY);

                            /* Error or Stop, reset state */
                            `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_IDLE;
                        }   /* End if ACK/NAK */

                        break;  /* `$INSTANCE_NAME`_SM_DEV2_RD_DATA */

            #endif  /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES) */

            default:
                /* Invalid state, reset state to idle */
                `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_IDLE;

                /* Reset offsets and index */
                `$INSTANCE_NAME`_rwOffsetS1 = 0u;
                `$INSTANCE_NAME`_rwIndexS1  = 0u;

                /* Dummy NAK to release bus */
                `$INSTANCE_NAME`_CSR_REG = `$INSTANCE_NAME`_CSR_NAK;
                break;

        }  /* End switch/case `$INSTANCE_NAME`_curState */
    }
    else
    {
        /* Intentional blank line */
    }

    /* Check if Stop was detected */
    if (`$INSTANCE_NAME`_IS_BIT_SET(`$INSTANCE_NAME`_CSR_REG, `$INSTANCE_NAME`_CSR_STOP_STATUS))
    {
        /* Clear Busy flag */
        `$INSTANCE_NAME`_curStatus &= ((uint8) ~`$INSTANCE_NAME`_STATUS_BUSY);

        /* error or stop - reset state */
        `$INSTANCE_NAME`_curState = `$INSTANCE_NAME`_SM_IDLE;

        /* Disable interrupt on Stop */
        `$INSTANCE_NAME`_CFG_REG &= ((uint8) ~`$INSTANCE_NAME`_CFG_STOP_IE);
    }
#ifdef `$INSTANCE_NAME`_ISR_EXIT_CALLBACK
    `$INSTANCE_NAME`_ISR_ExitCallback();
#endif /* `$INSTANCE_NAME`_ISR_EXIT_CALLBACK */    
}


#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  The interrupt handler to trigger after a wakeup.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_WAKEUP_ISR)
    {
    #ifdef `$INSTANCE_NAME`_WAKEUP_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_WAKEUP_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_WAKEUP_ISR_ENTRY_CALLBACK */         
        
        `$INSTANCE_NAME`_wakeupSource = 1u;  /* I2C was wakeup source */

        /* SCL is stretched until EZI2C_Wakeup() is called */
        
    #ifdef `$INSTANCE_NAME`_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_ISR_EXIT_CALLBACK */         
    }
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */


/* [] END OF FILE */
