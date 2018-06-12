/*******************************************************************************
* File Name: BleUartINT.c
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

#include "BleUart.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (BleUart_RX_INTERRUPT_ENABLED && (BleUart_RX_ENABLED || BleUart_HD_ENABLED))
    /*******************************************************************************
    * Function Name: BleUart_RXISR
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
    *  BleUart_rxBuffer - RAM buffer pointer for save received data.
    *  BleUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  BleUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  BleUart_rxBufferOverflow - software overflow flag. Set to one
    *     when BleUart_rxBufferWrite index overtakes
    *     BleUart_rxBufferRead index.
    *  BleUart_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when BleUart_rxBufferWrite is equal to
    *    BleUart_rxBufferRead
    *  BleUart_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  BleUart_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(BleUart_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef BleUart_RXISR_ENTRY_CALLBACK
        BleUart_RXISR_EntryCallback();
    #endif /* BleUart_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START BleUart_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = BleUart_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in BleUart_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (BleUart_RX_STS_BREAK | 
                            BleUart_RX_STS_PAR_ERROR |
                            BleUart_RX_STS_STOP_ERROR | 
                            BleUart_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                BleUart_errorStatus |= readStatus & ( BleUart_RX_STS_BREAK | 
                                                            BleUart_RX_STS_PAR_ERROR | 
                                                            BleUart_RX_STS_STOP_ERROR | 
                                                            BleUart_RX_STS_OVERRUN);
                /* `#START BleUart_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef BleUart_RXISR_ERROR_CALLBACK
                BleUart_RXISR_ERROR_Callback();
            #endif /* BleUart_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & BleUart_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = BleUart_RXDATA_REG;
            #if (BleUart_RXHW_ADDRESS_ENABLED)
                if(BleUart_rxAddressMode == (uint8)BleUart__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & BleUart_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & BleUart_RX_STS_ADDR_MATCH) != 0u)
                        {
                            BleUart_rxAddressDetected = 1u;
                        }
                        else
                        {
                            BleUart_rxAddressDetected = 0u;
                        }
                    }
                    if(BleUart_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        BleUart_rxBuffer[BleUart_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    BleUart_rxBuffer[BleUart_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                BleUart_rxBuffer[BleUart_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (BleUart_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(BleUart_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        BleUart_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    BleUart_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(BleUart_rxBufferWrite >= BleUart_RX_BUFFER_SIZE)
                    {
                        BleUart_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(BleUart_rxBufferWrite == BleUart_rxBufferRead)
                    {
                        BleUart_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (BleUart_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            BleUart_RXSTATUS_MASK_REG  &= (uint8)~BleUart_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(BleUart_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (BleUart_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & BleUart_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START BleUart_RXISR_END` */

        /* `#END` */

    #ifdef BleUart_RXISR_EXIT_CALLBACK
        BleUart_RXISR_ExitCallback();
    #endif /* BleUart_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (BleUart_RX_INTERRUPT_ENABLED && (BleUart_RX_ENABLED || BleUart_HD_ENABLED)) */


#if (BleUart_TX_INTERRUPT_ENABLED && BleUart_TX_ENABLED)
    /*******************************************************************************
    * Function Name: BleUart_TXISR
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
    *  BleUart_txBuffer - RAM buffer pointer for transmit data from.
    *  BleUart_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  BleUart_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(BleUart_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef BleUart_TXISR_ENTRY_CALLBACK
        BleUart_TXISR_EntryCallback();
    #endif /* BleUart_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START BleUart_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((BleUart_txBufferRead != BleUart_txBufferWrite) &&
             ((BleUart_TXSTATUS_REG & BleUart_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(BleUart_txBufferRead >= BleUart_TX_BUFFER_SIZE)
            {
                BleUart_txBufferRead = 0u;
            }

            BleUart_TXDATA_REG = BleUart_txBuffer[BleUart_txBufferRead];

            /* Set next pointer */
            BleUart_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START BleUart_TXISR_END` */

        /* `#END` */

    #ifdef BleUart_TXISR_EXIT_CALLBACK
        BleUart_TXISR_ExitCallback();
    #endif /* BleUart_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (BleUart_TX_INTERRUPT_ENABLED && BleUart_TX_ENABLED) */


/* [] END OF FILE */
