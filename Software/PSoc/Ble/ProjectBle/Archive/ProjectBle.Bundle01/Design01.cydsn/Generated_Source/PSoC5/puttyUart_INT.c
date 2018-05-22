/*******************************************************************************
* File Name: puttyUartINT.c
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

#include "puttyUart.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (puttyUart_RX_INTERRUPT_ENABLED && (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED))
    /*******************************************************************************
    * Function Name: puttyUart_RXISR
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
    *  puttyUart_rxBuffer - RAM buffer pointer for save received data.
    *  puttyUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  puttyUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  puttyUart_rxBufferOverflow - software overflow flag. Set to one
    *     when puttyUart_rxBufferWrite index overtakes
    *     puttyUart_rxBufferRead index.
    *  puttyUart_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when puttyUart_rxBufferWrite is equal to
    *    puttyUart_rxBufferRead
    *  puttyUart_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  puttyUart_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(puttyUart_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef puttyUart_RXISR_ENTRY_CALLBACK
        puttyUart_RXISR_EntryCallback();
    #endif /* puttyUart_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START puttyUart_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = puttyUart_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in puttyUart_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (puttyUart_RX_STS_BREAK | 
                            puttyUart_RX_STS_PAR_ERROR |
                            puttyUart_RX_STS_STOP_ERROR | 
                            puttyUart_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                puttyUart_errorStatus |= readStatus & ( puttyUart_RX_STS_BREAK | 
                                                            puttyUart_RX_STS_PAR_ERROR | 
                                                            puttyUart_RX_STS_STOP_ERROR | 
                                                            puttyUart_RX_STS_OVERRUN);
                /* `#START puttyUart_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef puttyUart_RXISR_ERROR_CALLBACK
                puttyUart_RXISR_ERROR_Callback();
            #endif /* puttyUart_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & puttyUart_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = puttyUart_RXDATA_REG;
            #if (puttyUart_RXHW_ADDRESS_ENABLED)
                if(puttyUart_rxAddressMode == (uint8)puttyUart__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & puttyUart_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & puttyUart_RX_STS_ADDR_MATCH) != 0u)
                        {
                            puttyUart_rxAddressDetected = 1u;
                        }
                        else
                        {
                            puttyUart_rxAddressDetected = 0u;
                        }
                    }
                    if(puttyUart_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        puttyUart_rxBuffer[puttyUart_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    puttyUart_rxBuffer[puttyUart_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                puttyUart_rxBuffer[puttyUart_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (puttyUart_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(puttyUart_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        puttyUart_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    puttyUart_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(puttyUart_rxBufferWrite >= puttyUart_RX_BUFFER_SIZE)
                    {
                        puttyUart_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(puttyUart_rxBufferWrite == puttyUart_rxBufferRead)
                    {
                        puttyUart_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (puttyUart_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            puttyUart_RXSTATUS_MASK_REG  &= (uint8)~puttyUart_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(puttyUart_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (puttyUart_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & puttyUart_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START puttyUart_RXISR_END` */

        /* `#END` */

    #ifdef puttyUart_RXISR_EXIT_CALLBACK
        puttyUart_RXISR_ExitCallback();
    #endif /* puttyUart_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (puttyUart_RX_INTERRUPT_ENABLED && (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)) */


#if (puttyUart_TX_INTERRUPT_ENABLED && puttyUart_TX_ENABLED)
    /*******************************************************************************
    * Function Name: puttyUart_TXISR
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
    *  puttyUart_txBuffer - RAM buffer pointer for transmit data from.
    *  puttyUart_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  puttyUart_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(puttyUart_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef puttyUart_TXISR_ENTRY_CALLBACK
        puttyUart_TXISR_EntryCallback();
    #endif /* puttyUart_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START puttyUart_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((puttyUart_txBufferRead != puttyUart_txBufferWrite) &&
             ((puttyUart_TXSTATUS_REG & puttyUart_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(puttyUart_txBufferRead >= puttyUart_TX_BUFFER_SIZE)
            {
                puttyUart_txBufferRead = 0u;
            }

            puttyUart_TXDATA_REG = puttyUart_txBuffer[puttyUart_txBufferRead];

            /* Set next pointer */
            puttyUart_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START puttyUart_TXISR_END` */

        /* `#END` */

    #ifdef puttyUart_TXISR_EXIT_CALLBACK
        puttyUart_TXISR_ExitCallback();
    #endif /* puttyUart_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (puttyUart_TX_INTERRUPT_ENABLED && puttyUart_TX_ENABLED) */


/* [] END OF FILE */
