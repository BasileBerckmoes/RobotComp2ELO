/*******************************************************************************
* File Name: puttyUart1INT.c
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

#include "puttyUart1.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (puttyUart1_RX_INTERRUPT_ENABLED && (puttyUart1_RX_ENABLED || puttyUart1_HD_ENABLED))
    /*******************************************************************************
    * Function Name: puttyUart1_RXISR
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
    *  puttyUart1_rxBuffer - RAM buffer pointer for save received data.
    *  puttyUart1_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  puttyUart1_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  puttyUart1_rxBufferOverflow - software overflow flag. Set to one
    *     when puttyUart1_rxBufferWrite index overtakes
    *     puttyUart1_rxBufferRead index.
    *  puttyUart1_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when puttyUart1_rxBufferWrite is equal to
    *    puttyUart1_rxBufferRead
    *  puttyUart1_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  puttyUart1_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(puttyUart1_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef puttyUart1_RXISR_ENTRY_CALLBACK
        puttyUart1_RXISR_EntryCallback();
    #endif /* puttyUart1_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START puttyUart1_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = puttyUart1_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in puttyUart1_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (puttyUart1_RX_STS_BREAK | 
                            puttyUart1_RX_STS_PAR_ERROR |
                            puttyUart1_RX_STS_STOP_ERROR | 
                            puttyUart1_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                puttyUart1_errorStatus |= readStatus & ( puttyUart1_RX_STS_BREAK | 
                                                            puttyUart1_RX_STS_PAR_ERROR | 
                                                            puttyUart1_RX_STS_STOP_ERROR | 
                                                            puttyUart1_RX_STS_OVERRUN);
                /* `#START puttyUart1_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef puttyUart1_RXISR_ERROR_CALLBACK
                puttyUart1_RXISR_ERROR_Callback();
            #endif /* puttyUart1_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & puttyUart1_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = puttyUart1_RXDATA_REG;
            #if (puttyUart1_RXHW_ADDRESS_ENABLED)
                if(puttyUart1_rxAddressMode == (uint8)puttyUart1__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & puttyUart1_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & puttyUart1_RX_STS_ADDR_MATCH) != 0u)
                        {
                            puttyUart1_rxAddressDetected = 1u;
                        }
                        else
                        {
                            puttyUart1_rxAddressDetected = 0u;
                        }
                    }
                    if(puttyUart1_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        puttyUart1_rxBuffer[puttyUart1_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    puttyUart1_rxBuffer[puttyUart1_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                puttyUart1_rxBuffer[puttyUart1_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (puttyUart1_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(puttyUart1_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        puttyUart1_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    puttyUart1_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(puttyUart1_rxBufferWrite >= puttyUart1_RX_BUFFER_SIZE)
                    {
                        puttyUart1_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(puttyUart1_rxBufferWrite == puttyUart1_rxBufferRead)
                    {
                        puttyUart1_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (puttyUart1_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            puttyUart1_RXSTATUS_MASK_REG  &= (uint8)~puttyUart1_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(puttyUart1_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (puttyUart1_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & puttyUart1_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START puttyUart1_RXISR_END` */

        /* `#END` */

    #ifdef puttyUart1_RXISR_EXIT_CALLBACK
        puttyUart1_RXISR_ExitCallback();
    #endif /* puttyUart1_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (puttyUart1_RX_INTERRUPT_ENABLED && (puttyUart1_RX_ENABLED || puttyUart1_HD_ENABLED)) */


#if (puttyUart1_TX_INTERRUPT_ENABLED && puttyUart1_TX_ENABLED)
    /*******************************************************************************
    * Function Name: puttyUart1_TXISR
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
    *  puttyUart1_txBuffer - RAM buffer pointer for transmit data from.
    *  puttyUart1_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  puttyUart1_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(puttyUart1_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef puttyUart1_TXISR_ENTRY_CALLBACK
        puttyUart1_TXISR_EntryCallback();
    #endif /* puttyUart1_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START puttyUart1_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((puttyUart1_txBufferRead != puttyUart1_txBufferWrite) &&
             ((puttyUart1_TXSTATUS_REG & puttyUart1_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(puttyUart1_txBufferRead >= puttyUart1_TX_BUFFER_SIZE)
            {
                puttyUart1_txBufferRead = 0u;
            }

            puttyUart1_TXDATA_REG = puttyUart1_txBuffer[puttyUart1_txBufferRead];

            /* Set next pointer */
            puttyUart1_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START puttyUart1_TXISR_END` */

        /* `#END` */

    #ifdef puttyUart1_TXISR_EXIT_CALLBACK
        puttyUart1_TXISR_ExitCallback();
    #endif /* puttyUart1_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (puttyUart1_TX_INTERRUPT_ENABLED && puttyUart1_TX_ENABLED) */


/* [] END OF FILE */
