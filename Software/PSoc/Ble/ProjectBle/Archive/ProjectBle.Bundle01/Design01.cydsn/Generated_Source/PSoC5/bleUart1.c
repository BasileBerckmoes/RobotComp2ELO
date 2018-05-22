/*******************************************************************************
* File Name: bleUart1.c
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

#include "bleUart1.h"
#if (bleUart1_INTERNAL_CLOCK_USED)
    #include "bleUart1_IntClock.h"
#endif /* End bleUart1_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 bleUart1_initVar = 0u;

#if (bleUart1_TX_INTERRUPT_ENABLED && bleUart1_TX_ENABLED)
    volatile uint8 bleUart1_txBuffer[bleUart1_TX_BUFFER_SIZE];
    volatile uint8 bleUart1_txBufferRead = 0u;
    uint8 bleUart1_txBufferWrite = 0u;
#endif /* (bleUart1_TX_INTERRUPT_ENABLED && bleUart1_TX_ENABLED) */

#if (bleUart1_RX_INTERRUPT_ENABLED && (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED))
    uint8 bleUart1_errorStatus = 0u;
    volatile uint8 bleUart1_rxBuffer[bleUart1_RX_BUFFER_SIZE];
    volatile uint8 bleUart1_rxBufferRead  = 0u;
    volatile uint8 bleUart1_rxBufferWrite = 0u;
    volatile uint8 bleUart1_rxBufferLoopDetect = 0u;
    volatile uint8 bleUart1_rxBufferOverflow   = 0u;
    #if (bleUart1_RXHW_ADDRESS_ENABLED)
        volatile uint8 bleUart1_rxAddressMode = bleUart1_RX_ADDRESS_MODE;
        volatile uint8 bleUart1_rxAddressDetected = 0u;
    #endif /* (bleUart1_RXHW_ADDRESS_ENABLED) */
#endif /* (bleUart1_RX_INTERRUPT_ENABLED && (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)) */


/*******************************************************************************
* Function Name: bleUart1_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  bleUart1_Start() sets the initVar variable, calls the
*  bleUart1_Init() function, and then calls the
*  bleUart1_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The bleUart1_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time bleUart1_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the bleUart1_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void bleUart1_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(bleUart1_initVar == 0u)
    {
        bleUart1_Init();
        bleUart1_initVar = 1u;
    }

    bleUart1_Enable();
}


/*******************************************************************************
* Function Name: bleUart1_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call bleUart1_Init() because
*  the bleUart1_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void bleUart1_Init(void) 
{
    #if(bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)

        #if (bleUart1_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(bleUart1_RX_VECT_NUM, &bleUart1_RXISR);
            CyIntSetPriority(bleUart1_RX_VECT_NUM, bleUart1_RX_PRIOR_NUM);
            bleUart1_errorStatus = 0u;
        #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */

        #if (bleUart1_RXHW_ADDRESS_ENABLED)
            bleUart1_SetRxAddressMode(bleUart1_RX_ADDRESS_MODE);
            bleUart1_SetRxAddress1(bleUart1_RX_HW_ADDRESS1);
            bleUart1_SetRxAddress2(bleUart1_RX_HW_ADDRESS2);
        #endif /* End bleUart1_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        bleUart1_RXBITCTR_PERIOD_REG = bleUart1_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        bleUart1_RXSTATUS_MASK_REG  = bleUart1_INIT_RX_INTERRUPTS_MASK;
    #endif /* End bleUart1_RX_ENABLED || bleUart1_HD_ENABLED*/

    #if(bleUart1_TX_ENABLED)
        #if (bleUart1_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(bleUart1_TX_VECT_NUM, &bleUart1_TXISR);
            CyIntSetPriority(bleUart1_TX_VECT_NUM, bleUart1_TX_PRIOR_NUM);
        #endif /* (bleUart1_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (bleUart1_TXCLKGEN_DP)
            bleUart1_TXBITCLKGEN_CTR_REG = bleUart1_BIT_CENTER;
            bleUart1_TXBITCLKTX_COMPLETE_REG = ((bleUart1_NUMBER_OF_DATA_BITS +
                        bleUart1_NUMBER_OF_START_BIT) * bleUart1_OVER_SAMPLE_COUNT) - 1u;
        #else
            bleUart1_TXBITCTR_PERIOD_REG = ((bleUart1_NUMBER_OF_DATA_BITS +
                        bleUart1_NUMBER_OF_START_BIT) * bleUart1_OVER_SAMPLE_8) - 1u;
        #endif /* End bleUart1_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (bleUart1_TX_INTERRUPT_ENABLED)
            bleUart1_TXSTATUS_MASK_REG = bleUart1_TX_STS_FIFO_EMPTY;
        #else
            bleUart1_TXSTATUS_MASK_REG = bleUart1_INIT_TX_INTERRUPTS_MASK;
        #endif /*End bleUart1_TX_INTERRUPT_ENABLED*/

    #endif /* End bleUart1_TX_ENABLED */

    #if(bleUart1_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        bleUart1_WriteControlRegister( \
            (bleUart1_ReadControlRegister() & (uint8)~bleUart1_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(bleUart1_PARITY_TYPE << bleUart1_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End bleUart1_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: bleUart1_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call bleUart1_Enable() because the bleUart1_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  bleUart1_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void bleUart1_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        bleUart1_RXBITCTR_CONTROL_REG |= bleUart1_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        bleUart1_RXSTATUS_ACTL_REG  |= bleUart1_INT_ENABLE;

        #if (bleUart1_RX_INTERRUPT_ENABLED)
            bleUart1_EnableRxInt();

            #if (bleUart1_RXHW_ADDRESS_ENABLED)
                bleUart1_rxAddressDetected = 0u;
            #endif /* (bleUart1_RXHW_ADDRESS_ENABLED) */
        #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */
    #endif /* (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED) */

    #if(bleUart1_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!bleUart1_TXCLKGEN_DP)
            bleUart1_TXBITCTR_CONTROL_REG |= bleUart1_CNTR_ENABLE;
        #endif /* End bleUart1_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        bleUart1_TXSTATUS_ACTL_REG |= bleUart1_INT_ENABLE;
        #if (bleUart1_TX_INTERRUPT_ENABLED)
            bleUart1_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            bleUart1_EnableTxInt();
        #endif /* (bleUart1_TX_INTERRUPT_ENABLED) */
     #endif /* (bleUart1_TX_INTERRUPT_ENABLED) */

    #if (bleUart1_INTERNAL_CLOCK_USED)
        bleUart1_IntClock_Start();  /* Enable the clock */
    #endif /* (bleUart1_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: bleUart1_Stop
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
void bleUart1_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)
        bleUart1_RXBITCTR_CONTROL_REG &= (uint8) ~bleUart1_CNTR_ENABLE;
    #endif /* (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED) */

    #if (bleUart1_TX_ENABLED)
        #if(!bleUart1_TXCLKGEN_DP)
            bleUart1_TXBITCTR_CONTROL_REG &= (uint8) ~bleUart1_CNTR_ENABLE;
        #endif /* (!bleUart1_TXCLKGEN_DP) */
    #endif /* (bleUart1_TX_ENABLED) */

    #if (bleUart1_INTERNAL_CLOCK_USED)
        bleUart1_IntClock_Stop();   /* Disable the clock */
    #endif /* (bleUart1_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)
        bleUart1_RXSTATUS_ACTL_REG  &= (uint8) ~bleUart1_INT_ENABLE;

        #if (bleUart1_RX_INTERRUPT_ENABLED)
            bleUart1_DisableRxInt();
        #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */
    #endif /* (bleUart1_RX_ENABLED || bleUart1_HD_ENABLED) */

    #if (bleUart1_TX_ENABLED)
        bleUart1_TXSTATUS_ACTL_REG &= (uint8) ~bleUart1_INT_ENABLE;

        #if (bleUart1_TX_INTERRUPT_ENABLED)
            bleUart1_DisableTxInt();
        #endif /* (bleUart1_TX_INTERRUPT_ENABLED) */
    #endif /* (bleUart1_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: bleUart1_ReadControlRegister
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
uint8 bleUart1_ReadControlRegister(void) 
{
    #if (bleUart1_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(bleUart1_CONTROL_REG);
    #endif /* (bleUart1_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: bleUart1_WriteControlRegister
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
void  bleUart1_WriteControlRegister(uint8 control) 
{
    #if (bleUart1_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       bleUart1_CONTROL_REG = control;
    #endif /* (bleUart1_CONTROL_REG_REMOVED) */
}


#if(bleUart1_RX_ENABLED || bleUart1_HD_ENABLED)
    /*******************************************************************************
    * Function Name: bleUart1_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      bleUart1_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      bleUart1_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      bleUart1_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      bleUart1_RX_STS_BREAK            Interrupt on break.
    *      bleUart1_RX_STS_OVERRUN          Interrupt on overrun error.
    *      bleUart1_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      bleUart1_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void bleUart1_SetRxInterruptMode(uint8 intSrc) 
    {
        bleUart1_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: bleUart1_ReadRxData
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
    *  bleUart1_rxBuffer - RAM buffer pointer for save received data.
    *  bleUart1_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  bleUart1_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  bleUart1_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 bleUart1_ReadRxData(void) 
    {
        uint8 rxData;

    #if (bleUart1_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        bleUart1_DisableRxInt();

        locRxBufferRead  = bleUart1_rxBufferRead;
        locRxBufferWrite = bleUart1_rxBufferWrite;

        if( (bleUart1_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = bleUart1_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= bleUart1_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            bleUart1_rxBufferRead = locRxBufferRead;

            if(bleUart1_rxBufferLoopDetect != 0u)
            {
                bleUart1_rxBufferLoopDetect = 0u;
                #if ((bleUart1_RX_INTERRUPT_ENABLED) && (bleUart1_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( bleUart1_HD_ENABLED )
                        if((bleUart1_CONTROL_REG & bleUart1_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            bleUart1_RXSTATUS_MASK_REG  |= bleUart1_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        bleUart1_RXSTATUS_MASK_REG  |= bleUart1_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end bleUart1_HD_ENABLED */
                #endif /* ((bleUart1_RX_INTERRUPT_ENABLED) && (bleUart1_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = bleUart1_RXDATA_REG;
        }

        bleUart1_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = bleUart1_RXDATA_REG;

    #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: bleUart1_ReadRxStatus
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
    *  bleUart1_RX_STS_FIFO_NOTEMPTY.
    *  bleUart1_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  bleUart1_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   bleUart1_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   bleUart1_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 bleUart1_ReadRxStatus(void) 
    {
        uint8 status;

        status = bleUart1_RXSTATUS_REG & bleUart1_RX_HW_MASK;

    #if (bleUart1_RX_INTERRUPT_ENABLED)
        if(bleUart1_rxBufferOverflow != 0u)
        {
            status |= bleUart1_RX_STS_SOFT_BUFF_OVER;
            bleUart1_rxBufferOverflow = 0u;
        }
    #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: bleUart1_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. bleUart1_GetChar() is
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
    *  bleUart1_rxBuffer - RAM buffer pointer for save received data.
    *  bleUart1_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  bleUart1_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  bleUart1_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 bleUart1_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (bleUart1_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        bleUart1_DisableRxInt();

        locRxBufferRead  = bleUart1_rxBufferRead;
        locRxBufferWrite = bleUart1_rxBufferWrite;

        if( (bleUart1_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = bleUart1_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= bleUart1_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            bleUart1_rxBufferRead = locRxBufferRead;

            if(bleUart1_rxBufferLoopDetect != 0u)
            {
                bleUart1_rxBufferLoopDetect = 0u;
                #if( (bleUart1_RX_INTERRUPT_ENABLED) && (bleUart1_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( bleUart1_HD_ENABLED )
                        if((bleUart1_CONTROL_REG & bleUart1_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            bleUart1_RXSTATUS_MASK_REG |= bleUart1_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        bleUart1_RXSTATUS_MASK_REG |= bleUart1_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end bleUart1_HD_ENABLED */
                #endif /* bleUart1_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = bleUart1_RXSTATUS_REG;
            if((rxStatus & bleUart1_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = bleUart1_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (bleUart1_RX_STS_BREAK | bleUart1_RX_STS_PAR_ERROR |
                                bleUart1_RX_STS_STOP_ERROR | bleUart1_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        bleUart1_EnableRxInt();

    #else

        rxStatus =bleUart1_RXSTATUS_REG;
        if((rxStatus & bleUart1_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = bleUart1_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (bleUart1_RX_STS_BREAK | bleUart1_RX_STS_PAR_ERROR |
                            bleUart1_RX_STS_STOP_ERROR | bleUart1_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: bleUart1_GetByte
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
    uint16 bleUart1_GetByte(void) 
    {
        
    #if (bleUart1_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        bleUart1_DisableRxInt();
        locErrorStatus = (uint16)bleUart1_errorStatus;
        bleUart1_errorStatus = 0u;
        bleUart1_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | bleUart1_ReadRxData() );
    #else
        return ( ((uint16)bleUart1_ReadRxStatus() << 8u) | bleUart1_ReadRxData() );
    #endif /* bleUart1_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: bleUart1_GetRxBufferSize
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
    *  bleUart1_rxBufferWrite - used to calculate left bytes.
    *  bleUart1_rxBufferRead - used to calculate left bytes.
    *  bleUart1_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 bleUart1_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (bleUart1_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        bleUart1_DisableRxInt();

        if(bleUart1_rxBufferRead == bleUart1_rxBufferWrite)
        {
            if(bleUart1_rxBufferLoopDetect != 0u)
            {
                size = bleUart1_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(bleUart1_rxBufferRead < bleUart1_rxBufferWrite)
        {
            size = (bleUart1_rxBufferWrite - bleUart1_rxBufferRead);
        }
        else
        {
            size = (bleUart1_RX_BUFFER_SIZE - bleUart1_rxBufferRead) + bleUart1_rxBufferWrite;
        }

        bleUart1_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((bleUart1_RXSTATUS_REG & bleUart1_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: bleUart1_ClearRxBuffer
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
    *  bleUart1_rxBufferWrite - cleared to zero.
    *  bleUart1_rxBufferRead - cleared to zero.
    *  bleUart1_rxBufferLoopDetect - cleared to zero.
    *  bleUart1_rxBufferOverflow - cleared to zero.
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
    void bleUart1_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        bleUart1_RXDATA_AUX_CTL_REG |= (uint8)  bleUart1_RX_FIFO_CLR;
        bleUart1_RXDATA_AUX_CTL_REG &= (uint8) ~bleUart1_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (bleUart1_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        bleUart1_DisableRxInt();

        bleUart1_rxBufferRead = 0u;
        bleUart1_rxBufferWrite = 0u;
        bleUart1_rxBufferLoopDetect = 0u;
        bleUart1_rxBufferOverflow = 0u;

        bleUart1_EnableRxInt();

    #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: bleUart1_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  bleUart1__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  bleUart1__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  bleUart1__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  bleUart1__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  bleUart1__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  bleUart1_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  bleUart1_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void bleUart1_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(bleUart1_RXHW_ADDRESS_ENABLED)
            #if(bleUart1_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* bleUart1_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = bleUart1_CONTROL_REG & (uint8)~bleUart1_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << bleUart1_CTRL_RXADDR_MODE0_SHIFT);
                bleUart1_CONTROL_REG = tmpCtrl;

                #if(bleUart1_RX_INTERRUPT_ENABLED && \
                   (bleUart1_RXBUFFERSIZE > bleUart1_FIFO_LENGTH) )
                    bleUart1_rxAddressMode = addressMode;
                    bleUart1_rxAddressDetected = 0u;
                #endif /* End bleUart1_RXBUFFERSIZE > bleUart1_FIFO_LENGTH*/
            #endif /* End bleUart1_CONTROL_REG_REMOVED */
        #else /* bleUart1_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End bleUart1_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: bleUart1_SetRxAddress1
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
    void bleUart1_SetRxAddress1(uint8 address) 
    {
        bleUart1_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: bleUart1_SetRxAddress2
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
    void bleUart1_SetRxAddress2(uint8 address) 
    {
        bleUart1_RXADDRESS2_REG = address;
    }

#endif  /* bleUart1_RX_ENABLED || bleUart1_HD_ENABLED*/


#if( (bleUart1_TX_ENABLED) || (bleUart1_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: bleUart1_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   bleUart1_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   bleUart1_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   bleUart1_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   bleUart1_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void bleUart1_SetTxInterruptMode(uint8 intSrc) 
    {
        bleUart1_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: bleUart1_WriteTxData
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
    *  bleUart1_txBuffer - RAM buffer pointer for save data for transmission
    *  bleUart1_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  bleUart1_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  bleUart1_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void bleUart1_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(bleUart1_initVar != 0u)
        {
        #if (bleUart1_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            bleUart1_DisableTxInt();

            if( (bleUart1_txBufferRead == bleUart1_txBufferWrite) &&
                ((bleUart1_TXSTATUS_REG & bleUart1_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                bleUart1_TXDATA_REG = txDataByte;
            }
            else
            {
                if(bleUart1_txBufferWrite >= bleUart1_TX_BUFFER_SIZE)
                {
                    bleUart1_txBufferWrite = 0u;
                }

                bleUart1_txBuffer[bleUart1_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                bleUart1_txBufferWrite++;
            }

            bleUart1_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            bleUart1_TXDATA_REG = txDataByte;

        #endif /*(bleUart1_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: bleUart1_ReadTxStatus
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
    uint8 bleUart1_ReadTxStatus(void) 
    {
        return(bleUart1_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: bleUart1_PutChar
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
    *  bleUart1_txBuffer - RAM buffer pointer for save data for transmission
    *  bleUart1_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  bleUart1_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  bleUart1_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void bleUart1_PutChar(uint8 txDataByte) 
    {
    #if (bleUart1_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            bleUart1_DisableTxInt();
        #endif /* (bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = bleUart1_txBufferWrite;
            locTxBufferRead  = bleUart1_txBufferRead;

        #if ((bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            bleUart1_EnableTxInt();
        #endif /* (bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(bleUart1_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((bleUart1_TXSTATUS_REG & bleUart1_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            bleUart1_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= bleUart1_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            bleUart1_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3))
            bleUart1_DisableTxInt();
        #endif /* (bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3) */

            bleUart1_txBufferWrite = locTxBufferWrite;

        #if ((bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3))
            bleUart1_EnableTxInt();
        #endif /* (bleUart1_TX_BUFFER_SIZE > bleUart1_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (bleUart1_TXSTATUS_REG & bleUart1_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                bleUart1_SetPendingTxInt();
            }
        }

    #else

        while((bleUart1_TXSTATUS_REG & bleUart1_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        bleUart1_TXDATA_REG = txDataByte;

    #endif /* bleUart1_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: bleUart1_PutString
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
    *  bleUart1_initVar - checked to identify that the component has been
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
    void bleUart1_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(bleUart1_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                bleUart1_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: bleUart1_PutArray
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
    *  bleUart1_initVar - checked to identify that the component has been
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
    void bleUart1_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(bleUart1_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                bleUart1_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: bleUart1_PutCRLF
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
    *  bleUart1_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void bleUart1_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(bleUart1_initVar != 0u)
        {
            bleUart1_PutChar(txDataByte);
            bleUart1_PutChar(0x0Du);
            bleUart1_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: bleUart1_GetTxBufferSize
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
    *  bleUart1_txBufferWrite - used to calculate left space.
    *  bleUart1_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 bleUart1_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (bleUart1_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        bleUart1_DisableTxInt();

        if(bleUart1_txBufferRead == bleUart1_txBufferWrite)
        {
            size = 0u;
        }
        else if(bleUart1_txBufferRead < bleUart1_txBufferWrite)
        {
            size = (bleUart1_txBufferWrite - bleUart1_txBufferRead);
        }
        else
        {
            size = (bleUart1_TX_BUFFER_SIZE - bleUart1_txBufferRead) +
                    bleUart1_txBufferWrite;
        }

        bleUart1_EnableTxInt();

    #else

        size = bleUart1_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & bleUart1_TX_STS_FIFO_FULL) != 0u)
        {
            size = bleUart1_FIFO_LENGTH;
        }
        else if((size & bleUart1_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (bleUart1_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: bleUart1_ClearTxBuffer
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
    *  bleUart1_txBufferWrite - cleared to zero.
    *  bleUart1_txBufferRead - cleared to zero.
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
    void bleUart1_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        bleUart1_TXDATA_AUX_CTL_REG |= (uint8)  bleUart1_TX_FIFO_CLR;
        bleUart1_TXDATA_AUX_CTL_REG &= (uint8) ~bleUart1_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (bleUart1_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        bleUart1_DisableTxInt();

        bleUart1_txBufferRead = 0u;
        bleUart1_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        bleUart1_EnableTxInt();

    #endif /* (bleUart1_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: bleUart1_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   bleUart1_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   bleUart1_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   bleUart1_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   bleUart1_SEND_WAIT_REINIT - Performs both options: 
    *      bleUart1_SEND_BREAK and bleUart1_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  bleUart1_initVar - checked to identify that the component has been
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
    *     When interrupt appear with bleUart1_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The bleUart1_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void bleUart1_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(bleUart1_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(bleUart1_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == bleUart1_SEND_BREAK) ||
                (retMode == bleUart1_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() |
                                                      bleUart1_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                bleUart1_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = bleUart1_TXSTATUS_REG;
                }
                while((tmpStat & bleUart1_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == bleUart1_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart1_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = bleUart1_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & bleUart1_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == bleUart1_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart1_REINIT) ||
                (retMode == bleUart1_SEND_WAIT_REINIT) )
            {
                bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() &
                                              (uint8)~bleUart1_CTRL_HD_SEND_BREAK);
            }

        #else /* bleUart1_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == bleUart1_SEND_BREAK) ||
                (retMode == bleUart1_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (bleUart1_PARITY_TYPE != bleUart1__B_UART__NONE_REVB) || \
                                    (bleUart1_PARITY_TYPE_SW != 0u) )
                    bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() |
                                                          bleUart1_CTRL_HD_SEND_BREAK);
                #endif /* End bleUart1_PARITY_TYPE != bleUart1__B_UART__NONE_REVB  */

                #if(bleUart1_TXCLKGEN_DP)
                    txPeriod = bleUart1_TXBITCLKTX_COMPLETE_REG;
                    bleUart1_TXBITCLKTX_COMPLETE_REG = bleUart1_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = bleUart1_TXBITCTR_PERIOD_REG;
                    bleUart1_TXBITCTR_PERIOD_REG = bleUart1_TXBITCTR_BREAKBITS8X;
                #endif /* End bleUart1_TXCLKGEN_DP */

                /* Send zeros */
                bleUart1_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = bleUart1_TXSTATUS_REG;
                }
                while((tmpStat & bleUart1_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == bleUart1_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart1_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = bleUart1_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & bleUart1_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == bleUart1_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == bleUart1_REINIT) ||
                (retMode == bleUart1_SEND_WAIT_REINIT) )
            {

            #if(bleUart1_TXCLKGEN_DP)
                bleUart1_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                bleUart1_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End bleUart1_TXCLKGEN_DP */

            #if( (bleUart1_PARITY_TYPE != bleUart1__B_UART__NONE_REVB) || \
                 (bleUart1_PARITY_TYPE_SW != 0u) )
                bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() &
                                                      (uint8) ~bleUart1_CTRL_HD_SEND_BREAK);
            #endif /* End bleUart1_PARITY_TYPE != NONE */
            }
        #endif    /* End bleUart1_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: bleUart1_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       bleUart1_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       bleUart1_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears bleUart1_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void bleUart1_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( bleUart1_CONTROL_REG_REMOVED == 0u )
            bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() |
                                                  bleUart1_CTRL_MARK);
        #endif /* End bleUart1_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( bleUart1_CONTROL_REG_REMOVED == 0u )
            bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() &
                                                  (uint8) ~bleUart1_CTRL_MARK);
        #endif /* End bleUart1_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndbleUart1_TX_ENABLED */

#if(bleUart1_HD_ENABLED)


    /*******************************************************************************
    * Function Name: bleUart1_LoadRxConfig
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
    void bleUart1_LoadRxConfig(void) 
    {
        bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() &
                                                (uint8)~bleUart1_CTRL_HD_SEND);
        bleUart1_RXBITCTR_PERIOD_REG = bleUart1_HD_RXBITCTR_INIT;

    #if (bleUart1_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        bleUart1_SetRxInterruptMode(bleUart1_INIT_RX_INTERRUPTS_MASK);
    #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: bleUart1_LoadTxConfig
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
    void bleUart1_LoadTxConfig(void) 
    {
    #if (bleUart1_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        bleUart1_SetRxInterruptMode(0u);
    #endif /* (bleUart1_RX_INTERRUPT_ENABLED) */

        bleUart1_WriteControlRegister(bleUart1_ReadControlRegister() | bleUart1_CTRL_HD_SEND);
        bleUart1_RXBITCTR_PERIOD_REG = bleUart1_HD_TXBITCTR_INIT;
    }

#endif  /* bleUart1_HD_ENABLED */


/* [] END OF FILE */
