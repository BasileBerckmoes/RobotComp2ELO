/*******************************************************************************
* File Name: bleUartINT.c
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

#include "bleUart.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (bleUart_RX_INTERRUPT_ENABLED && (bleUart_RX_ENABLED || bleUart_HD_ENABLED))
    /*******************************************************************************
    * Function Name: bleUart_RXISR
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
    *  bleUart_rxBuffer - RAM buffer pointer for save received data.
    *  bleUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  bleUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  bleUart_rxBufferOverflow - software overflow flag. Set to one
    *     when bleUart_rxBufferWrite index overtakes
    *     bleUart_rxBufferRead index.
    *  bleUart_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when bleUart_rxBufferWrite is equal to
    *    bleUart_rxBufferRead
    *  bleUart_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  bleUart_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(bleUart_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef bleUart_RXISR_ENTRY_CALLBACK
        bleUart_RXISR_EntryCallback();
    #endif /* bleUart_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START bleUart_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = bleUart_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in bleUart_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (bleUart_RX_STS_BREAK | 
                            bleUart_RX_STS_PAR_ERROR |
                            bleUart_RX_STS_STOP_ERROR | 
                            bleUart_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                bleUart_errorStatus |= readStatus & ( bleUart_RX_STS_BREAK | 
                                                            bleUart_RX_STS_PAR_ERROR | 
                                                            bleUart_RX_STS_STOP_ERROR | 
                                                            bleUart_RX_STS_OVERRUN);
                /* `#START bleUart_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef bleUart_RXISR_ERROR_CALLBACK
                bleUart_RXISR_ERROR_Callback();
            #endif /* bleUart_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & bleUart_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = bleUart_RXDATA_REG;
            #if (bleUart_RXHW_ADDRESS_ENABLED)
                if(bleUart_rxAddressMode == (uint8)bleUart__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & bleUart_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & bleUart_RX_STS_ADDR_MATCH) != 0u)
                        {
                            bleUart_rxAddressDetected = 1u;
                        }
                        else
                        {
                            bleUart_rxAddressDetected = 0u;
                        }
                    }
                    if(bleUart_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        bleUart_rxBuffer[bleUart_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    bleUart_rxBuffer[bleUart_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                bleUart_rxBuffer[bleUart_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (bleUart_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(bleUart_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        bleUart_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    bleUart_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(bleUart_rxBufferWrite >= bleUart_RX_BUFFER_SIZE)
                    {
                        bleUart_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(bleUart_rxBufferWrite == bleUart_rxBufferRead)
                    {
                        bleUart_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (bleUart_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            bleUart_RXSTATUS_MASK_REG  &= (uint8)~bleUart_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(bleUart_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (bleUart_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & bleUart_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START bleUart_RXISR_END` */

        /* `#END` */

    #ifdef bleUart_RXISR_EXIT_CALLBACK
        bleUart_RXISR_ExitCallback();
    #endif /* bleUart_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (bleUart_RX_INTERRUPT_ENABLED && (bleUart_RX_ENABLED || bleUart_HD_ENABLED)) */


#if (bleUart_TX_INTERRUPT_ENABLED && bleUart_TX_ENABLED)
    /*******************************************************************************
    * Function Name: bleUart_TXISR
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
    *  bleUart_txBuffer - RAM buffer pointer for transmit data from.
    *  bleUart_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  bleUart_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(bleUart_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef bleUart_TXISR_ENTRY_CALLBACK
        bleUart_TXISR_EntryCallback();
    #endif /* bleUart_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START bleUart_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((bleUart_txBufferRead != bleUart_txBufferWrite) &&
             ((bleUart_TXSTATUS_REG & bleUart_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(bleUart_txBufferRead >= bleUart_TX_BUFFER_SIZE)
            {
                bleUart_txBufferRead = 0u;
            }

            bleUart_TXDATA_REG = bleUart_txBuffer[bleUart_txBufferRead];

            /* Set next pointer */
            bleUart_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START bleUart_TXISR_END` */

        /* `#END` */

    #ifdef bleUart_TXISR_EXIT_CALLBACK
        bleUart_TXISR_ExitCallback();
    #endif /* bleUart_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (bleUart_TX_INTERRUPT_ENABLED && bleUart_TX_ENABLED) */


/* [] END OF FILE */
