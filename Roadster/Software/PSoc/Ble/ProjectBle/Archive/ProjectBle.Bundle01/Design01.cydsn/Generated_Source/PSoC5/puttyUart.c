/*******************************************************************************
* File Name: puttyUart.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "puttyUart.h"
#if (puttyUart_INTERNAL_CLOCK_USED)
    #include "puttyUart_IntClock.h"
#endif /* End puttyUart_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 puttyUart_initVar = 0u;

#if (puttyUart_TX_INTERRUPT_ENABLED && puttyUart_TX_ENABLED)
    volatile uint8 puttyUart_txBuffer[puttyUart_TX_BUFFER_SIZE];
    volatile uint8 puttyUart_txBufferRead = 0u;
    uint8 puttyUart_txBufferWrite = 0u;
#endif /* (puttyUart_TX_INTERRUPT_ENABLED && puttyUart_TX_ENABLED) */

#if (puttyUart_RX_INTERRUPT_ENABLED && (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED))
    uint8 puttyUart_errorStatus = 0u;
    volatile uint8 puttyUart_rxBuffer[puttyUart_RX_BUFFER_SIZE];
    volatile uint8 puttyUart_rxBufferRead  = 0u;
    volatile uint8 puttyUart_rxBufferWrite = 0u;
    volatile uint8 puttyUart_rxBufferLoopDetect = 0u;
    volatile uint8 puttyUart_rxBufferOverflow   = 0u;
    #if (puttyUart_RXHW_ADDRESS_ENABLED)
        volatile uint8 puttyUart_rxAddressMode = puttyUart_RX_ADDRESS_MODE;
        volatile uint8 puttyUart_rxAddressDetected = 0u;
    #endif /* (puttyUart_RXHW_ADDRESS_ENABLED) */
#endif /* (puttyUart_RX_INTERRUPT_ENABLED && (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)) */


/*******************************************************************************
* Function Name: puttyUart_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  puttyUart_Start() sets the initVar variable, calls the
*  puttyUart_Init() function, and then calls the
*  puttyUart_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The puttyUart_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time puttyUart_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the puttyUart_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void puttyUart_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(puttyUart_initVar == 0u)
    {
        puttyUart_Init();
        puttyUart_initVar = 1u;
    }

    puttyUart_Enable();
}


/*******************************************************************************
* Function Name: puttyUart_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call puttyUart_Init() because
*  the puttyUart_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void puttyUart_Init(void) 
{
    #if(puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)

        #if (puttyUart_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(puttyUart_RX_VECT_NUM, &puttyUart_RXISR);
            CyIntSetPriority(puttyUart_RX_VECT_NUM, puttyUart_RX_PRIOR_NUM);
            puttyUart_errorStatus = 0u;
        #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */

        #if (puttyUart_RXHW_ADDRESS_ENABLED)
            puttyUart_SetRxAddressMode(puttyUart_RX_ADDRESS_MODE);
            puttyUart_SetRxAddress1(puttyUart_RX_HW_ADDRESS1);
            puttyUart_SetRxAddress2(puttyUart_RX_HW_ADDRESS2);
        #endif /* End puttyUart_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        puttyUart_RXBITCTR_PERIOD_REG = puttyUart_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        puttyUart_RXSTATUS_MASK_REG  = puttyUart_INIT_RX_INTERRUPTS_MASK;
    #endif /* End puttyUart_RX_ENABLED || puttyUart_HD_ENABLED*/

    #if(puttyUart_TX_ENABLED)
        #if (puttyUart_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(puttyUart_TX_VECT_NUM, &puttyUart_TXISR);
            CyIntSetPriority(puttyUart_TX_VECT_NUM, puttyUart_TX_PRIOR_NUM);
        #endif /* (puttyUart_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (puttyUart_TXCLKGEN_DP)
            puttyUart_TXBITCLKGEN_CTR_REG = puttyUart_BIT_CENTER;
            puttyUart_TXBITCLKTX_COMPLETE_REG = ((puttyUart_NUMBER_OF_DATA_BITS +
                        puttyUart_NUMBER_OF_START_BIT) * puttyUart_OVER_SAMPLE_COUNT) - 1u;
        #else
            puttyUart_TXBITCTR_PERIOD_REG = ((puttyUart_NUMBER_OF_DATA_BITS +
                        puttyUart_NUMBER_OF_START_BIT) * puttyUart_OVER_SAMPLE_8) - 1u;
        #endif /* End puttyUart_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (puttyUart_TX_INTERRUPT_ENABLED)
            puttyUart_TXSTATUS_MASK_REG = puttyUart_TX_STS_FIFO_EMPTY;
        #else
            puttyUart_TXSTATUS_MASK_REG = puttyUart_INIT_TX_INTERRUPTS_MASK;
        #endif /*End puttyUart_TX_INTERRUPT_ENABLED*/

    #endif /* End puttyUart_TX_ENABLED */

    #if(puttyUart_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        puttyUart_WriteControlRegister( \
            (puttyUart_ReadControlRegister() & (uint8)~puttyUart_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(puttyUart_PARITY_TYPE << puttyUart_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End puttyUart_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: puttyUart_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call puttyUart_Enable() because the puttyUart_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  puttyUart_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void puttyUart_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        puttyUart_RXBITCTR_CONTROL_REG |= puttyUart_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        puttyUart_RXSTATUS_ACTL_REG  |= puttyUart_INT_ENABLE;

        #if (puttyUart_RX_INTERRUPT_ENABLED)
            puttyUart_EnableRxInt();

            #if (puttyUart_RXHW_ADDRESS_ENABLED)
                puttyUart_rxAddressDetected = 0u;
            #endif /* (puttyUart_RXHW_ADDRESS_ENABLED) */
        #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */
    #endif /* (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED) */

    #if(puttyUart_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!puttyUart_TXCLKGEN_DP)
            puttyUart_TXBITCTR_CONTROL_REG |= puttyUart_CNTR_ENABLE;
        #endif /* End puttyUart_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        puttyUart_TXSTATUS_ACTL_REG |= puttyUart_INT_ENABLE;
        #if (puttyUart_TX_INTERRUPT_ENABLED)
            puttyUart_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            puttyUart_EnableTxInt();
        #endif /* (puttyUart_TX_INTERRUPT_ENABLED) */
     #endif /* (puttyUart_TX_INTERRUPT_ENABLED) */

    #if (puttyUart_INTERNAL_CLOCK_USED)
        puttyUart_IntClock_Start();  /* Enable the clock */
    #endif /* (puttyUart_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: puttyUart_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void puttyUart_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)
        puttyUart_RXBITCTR_CONTROL_REG &= (uint8) ~puttyUart_CNTR_ENABLE;
    #endif /* (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED) */

    #if (puttyUart_TX_ENABLED)
        #if(!puttyUart_TXCLKGEN_DP)
            puttyUart_TXBITCTR_CONTROL_REG &= (uint8) ~puttyUart_CNTR_ENABLE;
        #endif /* (!puttyUart_TXCLKGEN_DP) */
    #endif /* (puttyUart_TX_ENABLED) */

    #if (puttyUart_INTERNAL_CLOCK_USED)
        puttyUart_IntClock_Stop();   /* Disable the clock */
    #endif /* (puttyUart_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)
        puttyUart_RXSTATUS_ACTL_REG  &= (uint8) ~puttyUart_INT_ENABLE;

        #if (puttyUart_RX_INTERRUPT_ENABLED)
            puttyUart_DisableRxInt();
        #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */
    #endif /* (puttyUart_RX_ENABLED || puttyUart_HD_ENABLED) */

    #if (puttyUart_TX_ENABLED)
        puttyUart_TXSTATUS_ACTL_REG &= (uint8) ~puttyUart_INT_ENABLE;

        #if (puttyUart_TX_INTERRUPT_ENABLED)
            puttyUart_DisableTxInt();
        #endif /* (puttyUart_TX_INTERRUPT_ENABLED) */
    #endif /* (puttyUart_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: puttyUart_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 puttyUart_ReadControlRegister(void) 
{
    #if (puttyUart_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(puttyUart_CONTROL_REG);
    #endif /* (puttyUart_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: puttyUart_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  puttyUart_WriteControlRegister(uint8 control) 
{
    #if (puttyUart_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       puttyUart_CONTROL_REG = control;
    #endif /* (puttyUart_CONTROL_REG_REMOVED) */
}


#if(puttyUart_RX_ENABLED || puttyUart_HD_ENABLED)
    /*******************************************************************************
    * Function Name: puttyUart_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      puttyUart_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      puttyUart_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      puttyUart_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      puttyUart_RX_STS_BREAK            Interrupt on break.
    *      puttyUart_RX_STS_OVERRUN          Interrupt on overrun error.
    *      puttyUart_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      puttyUart_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void puttyUart_SetRxInterruptMode(uint8 intSrc) 
    {
        puttyUart_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: puttyUart_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  puttyUart_rxBuffer - RAM buffer pointer for save received data.
    *  puttyUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  puttyUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  puttyUart_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 puttyUart_ReadRxData(void) 
    {
        uint8 rxData;

    #if (puttyUart_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        puttyUart_DisableRxInt();

        locRxBufferRead  = puttyUart_rxBufferRead;
        locRxBufferWrite = puttyUart_rxBufferWrite;

        if( (puttyUart_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = puttyUart_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= puttyUart_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            puttyUart_rxBufferRead = locRxBufferRead;

            if(puttyUart_rxBufferLoopDetect != 0u)
            {
                puttyUart_rxBufferLoopDetect = 0u;
                #if ((puttyUart_RX_INTERRUPT_ENABLED) && (puttyUart_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( puttyUart_HD_ENABLED )
                        if((puttyUart_CONTROL_REG & puttyUart_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            puttyUart_RXSTATUS_MASK_REG  |= puttyUart_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        puttyUart_RXSTATUS_MASK_REG  |= puttyUart_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end puttyUart_HD_ENABLED */
                #endif /* ((puttyUart_RX_INTERRUPT_ENABLED) && (puttyUart_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = puttyUart_RXDATA_REG;
        }

        puttyUart_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = puttyUart_RXDATA_REG;

    #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: puttyUart_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  puttyUart_RX_STS_FIFO_NOTEMPTY.
    *  puttyUart_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  puttyUart_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   puttyUart_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   puttyUart_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 puttyUart_ReadRxStatus(void) 
    {
        uint8 status;

        status = puttyUart_RXSTATUS_REG & puttyUart_RX_HW_MASK;

    #if (puttyUart_RX_INTERRUPT_ENABLED)
        if(puttyUart_rxBufferOverflow != 0u)
        {
            status |= puttyUart_RX_STS_SOFT_BUFF_OVER;
            puttyUart_rxBufferOverflow = 0u;
        }
    #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: puttyUart_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. puttyUart_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  puttyUart_rxBuffer - RAM buffer pointer for save received data.
    *  puttyUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  puttyUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  puttyUart_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 puttyUart_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (puttyUart_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        puttyUart_DisableRxInt();

        locRxBufferRead  = puttyUart_rxBufferRead;
        locRxBufferWrite = puttyUart_rxBufferWrite;

        if( (puttyUart_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = puttyUart_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= puttyUart_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            puttyUart_rxBufferRead = locRxBufferRead;

            if(puttyUart_rxBufferLoopDetect != 0u)
            {
                puttyUart_rxBufferLoopDetect = 0u;
                #if( (puttyUart_RX_INTERRUPT_ENABLED) && (puttyUart_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( puttyUart_HD_ENABLED )
                        if((puttyUart_CONTROL_REG & puttyUart_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            puttyUart_RXSTATUS_MASK_REG |= puttyUart_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        puttyUart_RXSTATUS_MASK_REG |= puttyUart_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end puttyUart_HD_ENABLED */
                #endif /* puttyUart_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = puttyUart_RXSTATUS_REG;
            if((rxStatus & puttyUart_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = puttyUart_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (puttyUart_RX_STS_BREAK | puttyUart_RX_STS_PAR_ERROR |
                                puttyUart_RX_STS_STOP_ERROR | puttyUart_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        puttyUart_EnableRxInt();

    #else

        rxStatus =puttyUart_RXSTATUS_REG;
        if((rxStatus & puttyUart_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = puttyUart_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (puttyUart_RX_STS_BREAK | puttyUart_RX_STS_PAR_ERROR |
                            puttyUart_RX_STS_STOP_ERROR | puttyUart_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: puttyUart_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 puttyUart_GetByte(void) 
    {
        
    #if (puttyUart_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        puttyUart_DisableRxInt();
        locErrorStatus = (uint16)puttyUart_errorStatus;
        puttyUart_errorStatus = 0u;
        puttyUart_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | puttyUart_ReadRxData() );
    #else
        return ( ((uint16)puttyUart_ReadRxStatus() << 8u) | puttyUart_ReadRxData() );
    #endif /* puttyUart_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: puttyUart_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  puttyUart_rxBufferWrite - used to calculate left bytes.
    *  puttyUart_rxBufferRead - used to calculate left bytes.
    *  puttyUart_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 puttyUart_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (puttyUart_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        puttyUart_DisableRxInt();

        if(puttyUart_rxBufferRead == puttyUart_rxBufferWrite)
        {
            if(puttyUart_rxBufferLoopDetect != 0u)
            {
                size = puttyUart_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(puttyUart_rxBufferRead < puttyUart_rxBufferWrite)
        {
            size = (puttyUart_rxBufferWrite - puttyUart_rxBufferRead);
        }
        else
        {
            size = (puttyUart_RX_BUFFER_SIZE - puttyUart_rxBufferRead) + puttyUart_rxBufferWrite;
        }

        puttyUart_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((puttyUart_RXSTATUS_REG & puttyUart_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: puttyUart_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_rxBufferWrite - cleared to zero.
    *  puttyUart_rxBufferRead - cleared to zero.
    *  puttyUart_rxBufferLoopDetect - cleared to zero.
    *  puttyUart_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void puttyUart_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        puttyUart_RXDATA_AUX_CTL_REG |= (uint8)  puttyUart_RX_FIFO_CLR;
        puttyUart_RXDATA_AUX_CTL_REG &= (uint8) ~puttyUart_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (puttyUart_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        puttyUart_DisableRxInt();

        puttyUart_rxBufferRead = 0u;
        puttyUart_rxBufferWrite = 0u;
        puttyUart_rxBufferLoopDetect = 0u;
        puttyUart_rxBufferOverflow = 0u;

        puttyUart_EnableRxInt();

    #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: puttyUart_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  puttyUart__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  puttyUart__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  puttyUart__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  puttyUart__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  puttyUart__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  puttyUart_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void puttyUart_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(puttyUart_RXHW_ADDRESS_ENABLED)
            #if(puttyUart_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* puttyUart_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = puttyUart_CONTROL_REG & (uint8)~puttyUart_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << puttyUart_CTRL_RXADDR_MODE0_SHIFT);
                puttyUart_CONTROL_REG = tmpCtrl;

                #if(puttyUart_RX_INTERRUPT_ENABLED && \
                   (puttyUart_RXBUFFERSIZE > puttyUart_FIFO_LENGTH) )
                    puttyUart_rxAddressMode = addressMode;
                    puttyUart_rxAddressDetected = 0u;
                #endif /* End puttyUart_RXBUFFERSIZE > puttyUart_FIFO_LENGTH*/
            #endif /* End puttyUart_CONTROL_REG_REMOVED */
        #else /* puttyUart_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End puttyUart_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: puttyUart_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void puttyUart_SetRxAddress1(uint8 address) 
    {
        puttyUart_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: puttyUart_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void puttyUart_SetRxAddress2(uint8 address) 
    {
        puttyUart_RXADDRESS2_REG = address;
    }

#endif  /* puttyUart_RX_ENABLED || puttyUart_HD_ENABLED*/


#if( (puttyUart_TX_ENABLED) || (puttyUart_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: puttyUart_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   puttyUart_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   puttyUart_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   puttyUart_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   puttyUart_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void puttyUart_SetTxInterruptMode(uint8 intSrc) 
    {
        puttyUart_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: puttyUart_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  puttyUart_txBuffer - RAM buffer pointer for save data for transmission
    *  puttyUart_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  puttyUart_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  puttyUart_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void puttyUart_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(puttyUart_initVar != 0u)
        {
        #if (puttyUart_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            puttyUart_DisableTxInt();

            if( (puttyUart_txBufferRead == puttyUart_txBufferWrite) &&
                ((puttyUart_TXSTATUS_REG & puttyUart_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                puttyUart_TXDATA_REG = txDataByte;
            }
            else
            {
                if(puttyUart_txBufferWrite >= puttyUart_TX_BUFFER_SIZE)
                {
                    puttyUart_txBufferWrite = 0u;
                }

                puttyUart_txBuffer[puttyUart_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                puttyUart_txBufferWrite++;
            }

            puttyUart_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            puttyUart_TXDATA_REG = txDataByte;

        #endif /*(puttyUart_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: puttyUart_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 puttyUart_ReadTxStatus(void) 
    {
        return(puttyUart_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: puttyUart_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_txBuffer - RAM buffer pointer for save data for transmission
    *  puttyUart_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  puttyUart_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  puttyUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void puttyUart_PutChar(uint8 txDataByte) 
    {
    #if (puttyUart_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            puttyUart_DisableTxInt();
        #endif /* (puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = puttyUart_txBufferWrite;
            locTxBufferRead  = puttyUart_txBufferRead;

        #if ((puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            puttyUart_EnableTxInt();
        #endif /* (puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(puttyUart_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((puttyUart_TXSTATUS_REG & puttyUart_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            puttyUart_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= puttyUart_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            puttyUart_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            puttyUart_DisableTxInt();
        #endif /* (puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            puttyUart_txBufferWrite = locTxBufferWrite;

        #if ((puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            puttyUart_EnableTxInt();
        #endif /* (puttyUart_TX_BUFFER_SIZE > puttyUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (puttyUart_TXSTATUS_REG & puttyUart_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                puttyUart_SetPendingTxInt();
            }
        }

    #else

        while((puttyUart_TXSTATUS_REG & puttyUart_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        puttyUart_TXDATA_REG = txDataByte;

    #endif /* puttyUart_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: puttyUart_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void puttyUart_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(puttyUart_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                puttyUart_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: puttyUart_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void puttyUart_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(puttyUart_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                puttyUart_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: puttyUart_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void puttyUart_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(puttyUart_initVar != 0u)
        {
            puttyUart_PutChar(txDataByte);
            puttyUart_PutChar(0x0Du);
            puttyUart_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: puttyUart_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  puttyUart_txBufferWrite - used to calculate left space.
    *  puttyUart_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 puttyUart_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (puttyUart_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        puttyUart_DisableTxInt();

        if(puttyUart_txBufferRead == puttyUart_txBufferWrite)
        {
            size = 0u;
        }
        else if(puttyUart_txBufferRead < puttyUart_txBufferWrite)
        {
            size = (puttyUart_txBufferWrite - puttyUart_txBufferRead);
        }
        else
        {
            size = (puttyUart_TX_BUFFER_SIZE - puttyUart_txBufferRead) +
                    puttyUart_txBufferWrite;
        }

        puttyUart_EnableTxInt();

    #else

        size = puttyUart_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & puttyUart_TX_STS_FIFO_FULL) != 0u)
        {
            size = puttyUart_FIFO_LENGTH;
        }
        else if((size & puttyUart_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (puttyUart_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: puttyUart_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_txBufferWrite - cleared to zero.
    *  puttyUart_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void puttyUart_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        puttyUart_TXDATA_AUX_CTL_REG |= (uint8)  puttyUart_TX_FIFO_CLR;
        puttyUart_TXDATA_AUX_CTL_REG &= (uint8) ~puttyUart_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (puttyUart_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        puttyUart_DisableTxInt();

        puttyUart_txBufferRead = 0u;
        puttyUart_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        puttyUart_EnableTxInt();

    #endif /* (puttyUart_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: puttyUart_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   puttyUart_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   puttyUart_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   puttyUart_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   puttyUart_SEND_WAIT_REINIT - Performs both options: 
    *      puttyUart_SEND_BREAK and puttyUart_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  puttyUart_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with puttyUart_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The puttyUart_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void puttyUart_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(puttyUart_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(puttyUart_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == puttyUart_SEND_BREAK) ||
                (retMode == puttyUart_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() |
                                                      puttyUart_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                puttyUart_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = puttyUart_TXSTATUS_REG;
                }
                while((tmpStat & puttyUart_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == puttyUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == puttyUart_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = puttyUart_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & puttyUart_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == puttyUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == puttyUart_REINIT) ||
                (retMode == puttyUart_SEND_WAIT_REINIT) )
            {
                puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() &
                                              (uint8)~puttyUart_CTRL_HD_SEND_BREAK);
            }

        #else /* puttyUart_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == puttyUart_SEND_BREAK) ||
                (retMode == puttyUart_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (puttyUart_PARITY_TYPE != puttyUart__B_UART__NONE_REVB) || \
                                    (puttyUart_PARITY_TYPE_SW != 0u) )
                    puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() |
                                                          puttyUart_CTRL_HD_SEND_BREAK);
                #endif /* End puttyUart_PARITY_TYPE != puttyUart__B_UART__NONE_REVB  */

                #if(puttyUart_TXCLKGEN_DP)
                    txPeriod = puttyUart_TXBITCLKTX_COMPLETE_REG;
                    puttyUart_TXBITCLKTX_COMPLETE_REG = puttyUart_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = puttyUart_TXBITCTR_PERIOD_REG;
                    puttyUart_TXBITCTR_PERIOD_REG = puttyUart_TXBITCTR_BREAKBITS8X;
                #endif /* End puttyUart_TXCLKGEN_DP */

                /* Send zeros */
                puttyUart_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = puttyUart_TXSTATUS_REG;
                }
                while((tmpStat & puttyUart_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == puttyUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == puttyUart_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = puttyUart_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & puttyUart_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == puttyUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == puttyUart_REINIT) ||
                (retMode == puttyUart_SEND_WAIT_REINIT) )
            {

            #if(puttyUart_TXCLKGEN_DP)
                puttyUart_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                puttyUart_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End puttyUart_TXCLKGEN_DP */

            #if( (puttyUart_PARITY_TYPE != puttyUart__B_UART__NONE_REVB) || \
                 (puttyUart_PARITY_TYPE_SW != 0u) )
                puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() &
                                                      (uint8) ~puttyUart_CTRL_HD_SEND_BREAK);
            #endif /* End puttyUart_PARITY_TYPE != NONE */
            }
        #endif    /* End puttyUart_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: puttyUart_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       puttyUart_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       puttyUart_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears puttyUart_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void puttyUart_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( puttyUart_CONTROL_REG_REMOVED == 0u )
            puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() |
                                                  puttyUart_CTRL_MARK);
        #endif /* End puttyUart_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( puttyUart_CONTROL_REG_REMOVED == 0u )
            puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() &
                                                  (uint8) ~puttyUart_CTRL_MARK);
        #endif /* End puttyUart_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndputtyUart_TX_ENABLED */

#if(puttyUart_HD_ENABLED)


    /*******************************************************************************
    * Function Name: puttyUart_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void puttyUart_LoadRxConfig(void) 
    {
        puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() &
                                                (uint8)~puttyUart_CTRL_HD_SEND);
        puttyUart_RXBITCTR_PERIOD_REG = puttyUart_HD_RXBITCTR_INIT;

    #if (puttyUart_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        puttyUart_SetRxInterruptMode(puttyUart_INIT_RX_INTERRUPTS_MASK);
    #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: puttyUart_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void puttyUart_LoadTxConfig(void) 
    {
    #if (puttyUart_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        puttyUart_SetRxInterruptMode(0u);
    #endif /* (puttyUart_RX_INTERRUPT_ENABLED) */

        puttyUart_WriteControlRegister(puttyUart_ReadControlRegister() | puttyUart_CTRL_HD_SEND);
        puttyUart_RXBITCTR_PERIOD_REG = puttyUart_HD_TXBITCTR_INIT;
    }

#endif  /* puttyUart_HD_ENABLED */


/* [] END OF FILE */
