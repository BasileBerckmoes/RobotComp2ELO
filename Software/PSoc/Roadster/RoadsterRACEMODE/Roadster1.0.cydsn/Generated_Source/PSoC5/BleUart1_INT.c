/*******************************************************************************
* File Name: BleUart1INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BleUart1.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (BleUart1_RX_INTERRUPT_ENABLED && (BleUart1_RX_ENABLED || BleUart1_HD_ENABLED))
    /*******************************************************************************
    * Function Name: BleUart1_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BleUart1_rxBuffer - RAM buffer pointer for save received data.
    *  BleUart1_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  BleUart1_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  BleUart1_rxBufferOverflow - software overflow flag. Set to one
    *     when BleUart1_rxBufferWrite index overtakes
    *     BleUart1_rxBufferRead index.
    *  BleUart1_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when BleUart1_rxBufferWrite is equal to
    *    BleUart1_rxBufferRead
    *  BleUart1_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  BleUart1_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(BleUart1_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef BleUart1_RXISR_ENTRY_CALLBACK
        BleUart1_RXISR_EntryCallback();
    #endif /* BleUart1_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START BleUart1_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = BleUart1_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in BleUart1_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (BleUart1_RX_STS_BREAK | 
                            BleUart1_RX_STS_PAR_ERROR |
                            BleUart1_RX_STS_STOP_ERROR | 
                            BleUart1_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                BleUart1_errorStatus |= readStatus & ( BleUart1_RX_STS_BREAK | 
                                                            BleUart1_RX_STS_PAR_ERROR | 
                                                            BleUart1_RX_STS_STOP_ERROR | 
                                                            BleUart1_RX_STS_OVERRUN);
                /* `#START BleUart1_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef BleUart1_RXISR_ERROR_CALLBACK
                BleUart1_RXISR_ERROR_Callback();
            #endif /* BleUart1_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & BleUart1_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = BleUart1_RXDATA_REG;
            #if (BleUart1_RXHW_ADDRESS_ENABLED)
                if(BleUart1_rxAddressMode == (uint8)BleUart1__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & BleUart1_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & BleUart1_RX_STS_ADDR_MATCH) != 0u)
                        {
                            BleUart1_rxAddressDetected = 1u;
                        }
                        else
                        {
                            BleUart1_rxAddressDetected = 0u;
                        }
                    }
                    if(BleUart1_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        BleUart1_rxBuffer[BleUart1_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    BleUart1_rxBuffer[BleUart1_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                BleUart1_rxBuffer[BleUart1_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (BleUart1_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(BleUart1_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        BleUart1_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    BleUart1_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(BleUart1_rxBufferWrite >= BleUart1_RX_BUFFER_SIZE)
                    {
                        BleUart1_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(BleUart1_rxBufferWrite == BleUart1_rxBufferRead)
                    {
                        BleUart1_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (BleUart1_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            BleUart1_RXSTATUS_MASK_REG  &= (uint8)~BleUart1_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(BleUart1_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (BleUart1_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & BleUart1_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START BleUart1_RXISR_END` */

        /* `#END` */

    #ifdef BleUart1_RXISR_EXIT_CALLBACK
        BleUart1_RXISR_ExitCallback();
    #endif /* BleUart1_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (BleUart1_RX_INTERRUPT_ENABLED && (BleUart1_RX_ENABLED || BleUart1_HD_ENABLED)) */


#if (BleUart1_TX_INTERRUPT_ENABLED && BleUart1_TX_ENABLED)
    /*******************************************************************************
    * Function Name: BleUart1_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BleUart1_txBuffer - RAM buffer pointer for transmit data from.
    *  BleUart1_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  BleUart1_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(BleUart1_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef BleUart1_TXISR_ENTRY_CALLBACK
        BleUart1_TXISR_EntryCallback();
    #endif /* BleUart1_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START BleUart1_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((BleUart1_txBufferRead != BleUart1_txBufferWrite) &&
             ((BleUart1_TXSTATUS_REG & BleUart1_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(BleUart1_txBufferRead >= BleUart1_TX_BUFFER_SIZE)
            {
                BleUart1_txBufferRead = 0u;
            }

            BleUart1_TXDATA_REG = BleUart1_txBuffer[BleUart1_txBufferRead];

            /* Set next pointer */
            BleUart1_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START BleUart1_TXISR_END` */

        /* `#END` */

    #ifdef BleUart1_TXISR_EXIT_CALLBACK
        BleUart1_TXISR_ExitCallback();
    #endif /* BleUart1_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (BleUart1_TX_INTERRUPT_ENABLED && BleUart1_TX_ENABLED) */


/* [] END OF FILE */
