/*******************************************************************************
* File Name: bleUart.c
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

#include "bleUart.h"
#if (bleUart_INTERNAL_CLOCK_USED)
    #include "bleUart_IntClock.h"
#endif /* End bleUart_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 bleUart_initVar = 0u;

#if (bleUart_TX_INTERRUPT_ENABLED && bleUart_TX_ENABLED)
    volatile uint8 bleUart_txBuffer[bleUart_TX_BUFFER_SIZE];
    volatile uint8 bleUart_txBufferRead = 0u;
    uint8 bleUart_txBufferWrite = 0u;
#endif /* (bleUart_TX_INTERRUPT_ENABLED && bleUart_TX_ENABLED) */

#if (bleUart_RX_INTERRUPT_ENABLED && (bleUart_RX_ENABLED || bleUart_HD_ENABLED))
    uint8 bleUart_errorStatus = 0u;
    volatile uint8 bleUart_rxBuffer[bleUart_RX_BUFFER_SIZE];
    volatile uint8 bleUart_rxBufferRead  = 0u;
    volatile uint8 bleUart_rxBufferWrite = 0u;
    volatile uint8 bleUart_rxBufferLoopDetect = 0u;
    volatile uint8 bleUart_rxBufferOverflow   = 0u;
    #if (bleUart_RXHW_ADDRESS_ENABLED)
        volatile uint8 bleUart_rxAddressMode = bleUart_RX_ADDRESS_MODE;
        volatile uint8 bleUart_rxAddressDetected = 0u;
    #endif /* (bleUart_RXHW_ADDRESS_ENABLED) */
#endif /* (bleUart_RX_INTERRUPT_ENABLED && (bleUart_RX_ENABLED || bleUart_HD_ENABLED)) */


/*******************************************************************************
* Function Name: bleUart_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  bleUart_Start() sets the initVar variable, calls the
*  bleUart_Init() function, and then calls the
*  bleUart_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The bleUart_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time bleUart_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the bleUart_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(bleUart_initVar == 0u)
    {
        bleUart_Init();
        bleUart_initVar = 1u;
    }

    bleUart_Enable();
}


/*******************************************************************************
* Function Name: bleUart_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call bleUart_Init() because
*  the bleUart_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void bleUart_Init(void) 
{
    #if(bleUart_RX_ENABLED || bleUart_HD_ENABLED)

        #if (bleUart_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(bleUart_RX_VECT_NUM, &bleUart_RXISR);
            CyIntSetPriority(bleUart_RX_VECT_NUM, bleUart_RX_PRIOR_NUM);
            bleUart_errorStatus = 0u;
        #endif /* (bleUart_RX_INTERRUPT_ENABLED) */

        #if (bleUart_RXHW_ADDRESS_ENABLED)
            bleUart_SetRxAddressMode(bleUart_RX_ADDRESS_MODE);
            bleUart_SetRxAddress1(bleUart_RX_HW_ADDRESS1);
            bleUart_SetRxAddress2(bleUart_RX_HW_ADDRESS2);
        #endif /* End bleUart_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        bleUart_RXBITCTR_PERIOD_REG = bleUart_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        bleUart_RXSTATUS_MASK_REG  = bleUart_INIT_RX_INTERRUPTS_MASK;
    #endif /* End bleUart_RX_ENABLED || bleUart_HD_ENABLED*/

    #if(bleUart_TX_ENABLED)
        #if (bleUart_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(bleUart_TX_VECT_NUM, &bleUart_TXISR);
            CyIntSetPriority(bleUart_TX_VECT_NUM, bleUart_TX_PRIOR_NUM);
        #endif /* (bleUart_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (bleUart_TXCLKGEN_DP)
            bleUart_TXBITCLKGEN_CTR_REG = bleUart_BIT_CENTER;
            bleUart_TXBITCLKTX_COMPLETE_REG = ((bleUart_NUMBER_OF_DATA_BITS +
                        bleUart_NUMBER_OF_START_BIT) * bleUart_OVER_SAMPLE_COUNT) - 1u;
        #else
            bleUart_TXBITCTR_PERIOD_REG = ((bleUart_NUMBER_OF_DATA_BITS +
                        bleUart_NUMBER_OF_START_BIT) * bleUart_OVER_SAMPLE_8) - 1u;
        #endif /* End bleUart_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (bleUart_TX_INTERRUPT_ENABLED)
            bleUart_TXSTATUS_MASK_REG = bleUart_TX_STS_FIFO_EMPTY;
        #else
            bleUart_TXSTATUS_MASK_REG = bleUart_INIT_TX_INTERRUPTS_MASK;
        #endif /*End bleUart_TX_INTERRUPT_ENABLED*/

    #endif /* End bleUart_TX_ENABLED */

    #if(bleUart_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        bleUart_WriteControlRegister( \
            (bleUart_ReadControlRegister() & (uint8)~bleUart_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(bleUart_PARITY_TYPE << bleUart_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End bleUart_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: bleUart_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call bleUart_Enable() because the bleUart_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void bleUart_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (bleUart_RX_ENABLED || bleUart_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        bleUart_RXBITCTR_CONTROL_REG |= bleUart_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        bleUart_RXSTATUS_ACTL_REG  |= bleUart_INT_ENABLE;

        #if (bleUart_RX_INTERRUPT_ENABLED)
            bleUart_EnableRxInt();

            #if (bleUart_RXHW_ADDRESS_ENABLED)
                bleUart_rxAddressDetected = 0u;
            #endif /* (bleUart_RXHW_ADDRESS_ENABLED) */
        #endif /* (bleUart_RX_INTERRUPT_ENABLED) */
    #endif /* (bleUart_RX_ENABLED || bleUart_HD_ENABLED) */

    #if(bleUart_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!bleUart_TXCLKGEN_DP)
            bleUart_TXBITCTR_CONTROL_REG |= bleUart_CNTR_ENABLE;
        #endif /* End bleUart_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        bleUart_TXSTATUS_ACTL_REG |= bleUart_INT_ENABLE;
        #if (bleUart_TX_INTERRUPT_ENABLED)
            bleUart_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            bleUart_EnableTxInt();
        #endif /* (bleUart_TX_INTERRUPT_ENABLED) */
     #endif /* (bleUart_TX_INTERRUPT_ENABLED) */

    #if (bleUart_INTERNAL_CLOCK_USED)
        bleUart_IntClock_Start();  /* Enable the clock */
    #endif /* (bleUart_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: bleUart_Stop
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
void bleUart_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (bleUart_RX_ENABLED || bleUart_HD_ENABLED)
        bleUart_RXBITCTR_CONTROL_REG &= (uint8) ~bleUart_CNTR_ENABLE;
    #endif /* (bleUart_RX_ENABLED || bleUart_HD_ENABLED) */

    #if (bleUart_TX_ENABLED)
        #if(!bleUart_TXCLKGEN_DP)
            bleUart_TXBITCTR_CONTROL_REG &= (uint8) ~bleUart_CNTR_ENABLE;
        #endif /* (!bleUart_TXCLKGEN_DP) */
    #endif /* (bleUart_TX_ENABLED) */

    #if (bleUart_INTERNAL_CLOCK_USED)
        bleUart_IntClock_Stop();   /* Disable the clock */
    #endif /* (bleUart_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (bleUart_RX_ENABLED || bleUart_HD_ENABLED)
        bleUart_RXSTATUS_ACTL_REG  &= (uint8) ~bleUart_INT_ENABLE;

        #if (bleUart_RX_INTERRUPT_ENABLED)
            bleUart_DisableRxInt();
        #endif /* (bleUart_RX_INTERRUPT_ENABLED) */
    #endif /* (bleUart_RX_ENABLED || bleUart_HD_ENABLED) */

    #if (bleUart_TX_ENABLED)
        bleUart_TXSTATUS_ACTL_REG &= (uint8) ~bleUart_INT_ENABLE;

        #if (bleUart_TX_INTERRUPT_ENABLED)
            bleUart_DisableTxInt();
        #endif /* (bleUart_TX_INTERRUPT_ENABLED) */
    #endif /* (bleUart_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: bleUart_ReadControlRegister
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
uint8 bleUart_ReadControlRegister(void) 
{
    #if (bleUart_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(bleUart_CONTROL_REG);
    #endif /* (bleUart_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: bleUart_WriteControlRegister
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
void  bleUart_WriteControlRegister(uint8 control) 
{
    #if (bleUart_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       bleUart_CONTROL_REG = control;
    #endif /* (bleUart_CONTROL_REG_REMOVED) */
}


#if(bleUart_RX_ENABLED || bleUart_HD_ENABLED)
    /*******************************************************************************
    * Function Name: bleUart_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      bleUart_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      bleUart_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      bleUart_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      bleUart_RX_STS_BREAK            Interrupt on break.
    *      bleUart_RX_STS_OVERRUN          Interrupt on overrun error.
    *      bleUart_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      bleUart_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void bleUart_SetRxInterruptMode(uint8 intSrc) 
    {
        bleUart_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: bleUart_ReadRxData
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
    *  bleUart_rxBuffer - RAM buffer pointer for save received data.
    *  bleUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  bleUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  bleUart_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 bleUart_ReadRxData(void) 
    {
        uint8 rxData;

    #if (bleUart_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        bleUart_DisableRxInt();

        locRxBufferRead  = bleUart_rxBufferRead;
        locRxBufferWrite = bleUart_rxBufferWrite;

        if( (bleUart_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = bleUart_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= bleUart_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            bleUart_rxBufferRead = locRxBufferRead;

            if(bleUart_rxBufferLoopDetect != 0u)
            {
                bleUart_rxBufferLoopDetect = 0u;
                #if ((bleUart_RX_INTERRUPT_ENABLED) && (bleUart_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( bleUart_HD_ENABLED )
                        if((bleUart_CONTROL_REG & bleUart_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            bleUart_RXSTATUS_MASK_REG  |= bleUart_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        bleUart_RXSTATUS_MASK_REG  |= bleUart_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end bleUart_HD_ENABLED */
                #endif /* ((bleUart_RX_INTERRUPT_ENABLED) && (bleUart_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = bleUart_RXDATA_REG;
        }

        bleUart_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = bleUart_RXDATA_REG;

    #endif /* (bleUart_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: bleUart_ReadRxStatus
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
    *  bleUart_RX_STS_FIFO_NOTEMPTY.
    *  bleUart_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  bleUart_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   bleUart_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   bleUart_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 bleUart_ReadRxStatus(void) 
    {
        uint8 status;

        status = bleUart_RXSTATUS_REG & bleUart_RX_HW_MASK;

    #if (bleUart_RX_INTERRUPT_ENABLED)
        if(bleUart_rxBufferOverflow != 0u)
        {
            status |= bleUart_RX_STS_SOFT_BUFF_OVER;
            bleUart_rxBufferOverflow = 0u;
        }
    #endif /* (bleUart_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: bleUart_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. bleUart_GetChar() is
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
    *  bleUart_rxBuffer - RAM buffer pointer for save received data.
    *  bleUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  bleUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  bleUart_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 bleUart_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (bleUart_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        bleUart_DisableRxInt();

        locRxBufferRead  = bleUart_rxBufferRead;
        locRxBufferWrite = bleUart_rxBufferWrite;

        if( (bleUart_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = bleUart_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= bleUart_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            bleUart_rxBufferRead = locRxBufferRead;

            if(bleUart_rxBufferLoopDetect != 0u)
            {
                bleUart_rxBufferLoopDetect = 0u;
                #if( (bleUart_RX_INTERRUPT_ENABLED) && (bleUart_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( bleUart_HD_ENABLED )
                        if((bleUart_CONTROL_REG & bleUart_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            bleUart_RXSTATUS_MASK_REG |= bleUart_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        bleUart_RXSTATUS_MASK_REG |= bleUart_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end bleUart_HD_ENABLED */
                #endif /* bleUart_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = bleUart_RXSTATUS_REG;
            if((rxStatus & bleUart_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = bleUart_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (bleUart_RX_STS_BREAK | bleUart_RX_STS_PAR_ERROR |
                                bleUart_RX_STS_STOP_ERROR | bleUart_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        bleUart_EnableRxInt();

    #else

        rxStatus =bleUart_RXSTATUS_REG;
        if((rxStatus & bleUart_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = bleUart_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (bleUart_RX_STS_BREAK | bleUart_RX_STS_PAR_ERROR |
                            bleUart_RX_STS_STOP_ERROR | bleUart_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (bleUart_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: bleUart_GetByte
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
    uint16 bleUart_GetByte(void) 
    {
        
    #if (bleUart_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        bleUart_DisableRxInt();
        locErrorStatus = (uint16)bleUart_errorStatus;
        bleUart_errorStatus = 0u;
        bleUart_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | bleUart_ReadRxData() );
    #else
        return ( ((uint16)bleUart_ReadRxStatus() << 8u) | bleUart_ReadRxData() );
    #endif /* bleUart_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: bleUart_GetRxBufferSize
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
    *  bleUart_rxBufferWrite - used to calculate left bytes.
    *  bleUart_rxBufferRead - used to calculate left bytes.
    *  bleUart_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 bleUart_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (bleUart_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        bleUart_DisableRxInt();

        if(bleUart_rxBufferRead == bleUart_rxBufferWrite)
        {
            if(bleUart_rxBufferLoopDetect != 0u)
            {
                size = bleUart_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(bleUart_rxBufferRead < bleUart_rxBufferWrite)
        {
            size = (bleUart_rxBufferWrite - bleUart_rxBufferRead);
        }
        else
        {
            size = (bleUart_RX_BUFFER_SIZE - bleUart_rxBufferRead) + bleUart_rxBufferWrite;
        }

        bleUart_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((bleUart_RXSTATUS_REG & bleUart_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (bleUart_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: bleUart_ClearRxBuffer
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
    *  bleUart_rxBufferWrite - cleared to zero.
    *  bleUart_rxBufferRead - cleared to zero.
    *  bleUart_rxBufferLoopDetect - cleared to zero.
    *  bleUart_rxBufferOverflow - cleared to zero.
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
    void bleUart_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        bleUart_RXDATA_AUX_CTL_REG |= (uint8)  bleUart_RX_FIFO_CLR;
        bleUart_RXDATA_AUX_CTL_REG &= (uint8) ~bleUart_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (bleUart_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        bleUart_DisableRxInt();

        bleUart_rxBufferRead = 0u;
        bleUart_rxBufferWrite = 0u;
        bleUart_rxBufferLoopDetect = 0u;
        bleUart_rxBufferOverflow = 0u;

        bleUart_EnableRxInt();

    #endif /* (bleUart_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: bleUart_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  bleUart__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  bleUart__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  bleUart__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  bleUart__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  bleUart__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  bleUart_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  bleUart_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void bleUart_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(bleUart_RXHW_ADDRESS_ENABLED)
            #if(bleUart_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* bleUart_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = bleUart_CONTROL_REG & (uint8)~bleUart_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << bleUart_CTRL_RXADDR_MODE0_SHIFT);
                bleUart_CONTROL_REG = tmpCtrl;

                #if(bleUart_RX_INTERRUPT_ENABLED && \
                   (bleUart_RXBUFFERSIZE > bleUart_FIFO_LENGTH) )
                    bleUart_rxAddressMode = addressMode;
                    bleUart_rxAddressDetected = 0u;
                #endif /* End bleUart_RXBUFFERSIZE > bleUart_FIFO_LENGTH*/
            #endif /* End bleUart_CONTROL_REG_REMOVED */
        #else /* bleUart_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End bleUart_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: bleUart_SetRxAddress1
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
    void bleUart_SetRxAddress1(uint8 address) 
    {
        bleUart_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: bleUart_SetRxAddress2
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
    void bleUart_SetRxAddress2(uint8 address) 
    {
        bleUart_RXADDRESS2_REG = address;
    }

#endif  /* bleUart_RX_ENABLED || bleUart_HD_ENABLED*/


#if( (bleUart_TX_ENABLED) || (bleUart_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: bleUart_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   bleUart_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   bleUart_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   bleUart_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   bleUart_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void bleUart_SetTxInterruptMode(uint8 intSrc) 
    {
        bleUart_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: bleUart_WriteTxData
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
    *  bleUart_txBuffer - RAM buffer pointer for save data for transmission
    *  bleUart_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  bleUart_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  bleUart_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void bleUart_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(bleUart_initVar != 0u)
        {
        #if (bleUart_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            bleUart_DisableTxInt();

            if( (bleUart_txBufferRead == bleUart_txBufferWrite) &&
                ((bleUart_TXSTATUS_REG & bleUart_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                bleUart_TXDATA_REG = txDataByte;
            }
            else
            {
                if(bleUart_txBufferWrite >= bleUart_TX_BUFFER_SIZE)
                {
                    bleUart_txBufferWrite = 0u;
                }

                bleUart_txBuffer[bleUart_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                bleUart_txBufferWrite++;
            }

            bleUart_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            bleUart_TXDATA_REG = txDataByte;

        #endif /*(bleUart_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: bleUart_ReadTxStatus
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
    uint8 bleUart_ReadTxStatus(void) 
    {
        return(bleUart_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: bleUart_PutChar
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
    *  bleUart_txBuffer - RAM buffer pointer for save data for transmission
    *  bleUart_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  bleUart_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  bleUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void bleUart_PutChar(uint8 txDataByte) 
    {
    #if (bleUart_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            bleUart_DisableTxInt();
        #endif /* (bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = bleUart_txBufferWrite;
            locTxBufferRead  = bleUart_txBufferRead;

        #if ((bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            bleUart_EnableTxInt();
        #endif /* (bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(bleUart_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((bleUart_TXSTATUS_REG & bleUart_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            bleUart_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= bleUart_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            bleUart_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            bleUart_DisableTxInt();
        #endif /* (bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            bleUart_txBufferWrite = locTxBufferWrite;

        #if ((bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            bleUart_EnableTxInt();
        #endif /* (bleUart_TX_BUFFER_SIZE > bleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (bleUart_TXSTATUS_REG & bleUart_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                bleUart_SetPendingTxInt();
            }
        }

    #else

        while((bleUart_TXSTATUS_REG & bleUart_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        bleUart_TXDATA_REG = txDataByte;

    #endif /* bleUart_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: bleUart_PutString
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
    *  bleUart_initVar - checked to identify that the component has been
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
    void bleUart_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(bleUart_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                bleUart_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: bleUart_PutArray
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
    *  bleUart_initVar - checked to identify that the component has been
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
    void bleUart_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(bleUart_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                bleUart_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: bleUart_PutCRLF
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
    *  bleUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void bleUart_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(bleUart_initVar != 0u)
        {
            bleUart_PutChar(txDataByte);
            bleUart_PutChar(0x0Du);
            bleUart_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: bleUart_GetTxBufferSize
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
    *  bleUart_txBufferWrite - used to calculate left space.
    *  bleUart_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 bleUart_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (bleUart_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        bleUart_DisableTxInt();

        if(bleUart_txBufferRead == bleUart_txBufferWrite)
        {
            size = 0u;
        }
        else if(bleUart_txBufferRead < bleUart_txBufferWrite)
        {
            size = (bleUart_txBufferWrite - bleUart_txBufferRead);
        }
        else
        {
            size = (bleUart_TX_BUFFER_SIZE - bleUart_txBufferRead) +
                    bleUart_txBufferWrite;
        }

        bleUart_EnableTxInt();

    #else

        size = bleUart_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & bleUart_TX_STS_FIFO_FULL) != 0u)
        {
            size = bleUart_FIFO_LENGTH;
        }
        else if((size & bleUart_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (bleUart_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: bleUart_ClearTxBuffer
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
    *  bleUart_txBufferWrite - cleared to zero.
    *  bleUart_txBufferRead - cleared to zero.
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
    void bleUart_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        bleUart_TXDATA_AUX_CTL_REG |= (uint8)  bleUart_TX_FIFO_CLR;
        bleUart_TXDATA_AUX_CTL_REG &= (uint8) ~bleUart_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (bleUart_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        bleUart_DisableTxInt();

        bleUart_txBufferRead = 0u;
        bleUart_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        bleUart_EnableTxInt();

    #endif /* (bleUart_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: bleUart_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   bleUart_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   bleUart_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   bleUart_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   bleUart_SEND_WAIT_REINIT - Performs both options: 
    *      bleUart_SEND_BREAK and bleUart_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  bleUart_initVar - checked to identify that the component has been
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
    *     When interrupt appear with bleUart_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The bleUart_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void bleUart_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(bleUart_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(bleUart_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == bleUart_SEND_BREAK) ||
                (retMode == bleUart_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                bleUart_WriteControlRegister(bleUart_ReadControlRegister() |
                                                      bleUart_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                bleUart_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = bleUart_TXSTATUS_REG;
                }
                while((tmpStat & bleUart_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == bleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = bleUart_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & bleUart_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == bleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart_REINIT) ||
                (retMode == bleUart_SEND_WAIT_REINIT) )
            {
                bleUart_WriteControlRegister(bleUart_ReadControlRegister() &
                                              (uint8)~bleUart_CTRL_HD_SEND_BREAK);
            }

        #else /* bleUart_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == bleUart_SEND_BREAK) ||
                (retMode == bleUart_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (bleUart_PARITY_TYPE != bleUart__B_UART__NONE_REVB) || \
                                    (bleUart_PARITY_TYPE_SW != 0u) )
                    bleUart_WriteControlRegister(bleUart_ReadControlRegister() |
                                                          bleUart_CTRL_HD_SEND_BREAK);
                #endif /* End bleUart_PARITY_TYPE != bleUart__B_UART__NONE_REVB  */

                #if(bleUart_TXCLKGEN_DP)
                    txPeriod = bleUart_TXBITCLKTX_COMPLETE_REG;
                    bleUart_TXBITCLKTX_COMPLETE_REG = bleUart_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = bleUart_TXBITCTR_PERIOD_REG;
                    bleUart_TXBITCTR_PERIOD_REG = bleUart_TXBITCTR_BREAKBITS8X;
                #endif /* End bleUart_TXCLKGEN_DP */

                /* Send zeros */
                bleUart_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = bleUart_TXSTATUS_REG;
                }
                while((tmpStat & bleUart_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == bleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = bleUart_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & bleUart_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == bleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart_REINIT) ||
                (retMode == bleUart_SEND_WAIT_REINIT) )
            {

            #if(bleUart_TXCLKGEN_DP)
                bleUart_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                bleUart_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End bleUart_TXCLKGEN_DP */

            #if( (bleUart_PARITY_TYPE != bleUart__B_UART__NONE_REVB) || \
                 (bleUart_PARITY_TYPE_SW != 0u) )
                bleUart_WriteControlRegister(bleUart_ReadControlRegister() &
                                                      (uint8) ~bleUart_CTRL_HD_SEND_BREAK);
            #endif /* End bleUart_PARITY_TYPE != NONE */
            }
        #endif    /* End bleUart_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: bleUart_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       bleUart_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       bleUart_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears bleUart_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void bleUart_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( bleUart_CONTROL_REG_REMOVED == 0u )
            bleUart_WriteControlRegister(bleUart_ReadControlRegister() |
                                                  bleUart_CTRL_MARK);
        #endif /* End bleUart_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( bleUart_CONTROL_REG_REMOVED == 0u )
            bleUart_WriteControlRegister(bleUart_ReadControlRegister() &
                                                  (uint8) ~bleUart_CTRL_MARK);
        #endif /* End bleUart_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndbleUart_TX_ENABLED */

#if(bleUart_HD_ENABLED)


    /*******************************************************************************
    * Function Name: bleUart_LoadRxConfig
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
    void bleUart_LoadRxConfig(void) 
    {
        bleUart_WriteControlRegister(bleUart_ReadControlRegister() &
                                                (uint8)~bleUart_CTRL_HD_SEND);
        bleUart_RXBITCTR_PERIOD_REG = bleUart_HD_RXBITCTR_INIT;

    #if (bleUart_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        bleUart_SetRxInterruptMode(bleUart_INIT_RX_INTERRUPTS_MASK);
    #endif /* (bleUart_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: bleUart_LoadTxConfig
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
    void bleUart_LoadTxConfig(void) 
    {
    #if (bleUart_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        bleUart_SetRxInterruptMode(0u);
    #endif /* (bleUart_RX_INTERRUPT_ENABLED) */

        bleUart_WriteControlRegister(bleUart_ReadControlRegister() | bleUart_CTRL_HD_SEND);
        bleUart_RXBITCTR_PERIOD_REG = bleUart_HD_TXBITCTR_INIT;
    }

#endif  /* bleUart_HD_ENABLED */


/* [] END OF FILE */
