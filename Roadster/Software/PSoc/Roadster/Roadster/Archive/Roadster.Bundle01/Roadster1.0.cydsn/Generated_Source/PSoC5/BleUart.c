/*******************************************************************************
* File Name: BleUart.c
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

#include "BleUart.h"
#if (BleUart_INTERNAL_CLOCK_USED)
    #include "BleUart_IntClock.h"
#endif /* End BleUart_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 BleUart_initVar = 0u;

#if (BleUart_TX_INTERRUPT_ENABLED && BleUart_TX_ENABLED)
    volatile uint8 BleUart_txBuffer[BleUart_TX_BUFFER_SIZE];
    volatile uint8 BleUart_txBufferRead = 0u;
    uint8 BleUart_txBufferWrite = 0u;
#endif /* (BleUart_TX_INTERRUPT_ENABLED && BleUart_TX_ENABLED) */

#if (BleUart_RX_INTERRUPT_ENABLED && (BleUart_RX_ENABLED || BleUart_HD_ENABLED))
    uint8 BleUart_errorStatus = 0u;
    volatile uint8 BleUart_rxBuffer[BleUart_RX_BUFFER_SIZE];
    volatile uint8 BleUart_rxBufferRead  = 0u;
    volatile uint8 BleUart_rxBufferWrite = 0u;
    volatile uint8 BleUart_rxBufferLoopDetect = 0u;
    volatile uint8 BleUart_rxBufferOverflow   = 0u;
    #if (BleUart_RXHW_ADDRESS_ENABLED)
        volatile uint8 BleUart_rxAddressMode = BleUart_RX_ADDRESS_MODE;
        volatile uint8 BleUart_rxAddressDetected = 0u;
    #endif /* (BleUart_RXHW_ADDRESS_ENABLED) */
#endif /* (BleUart_RX_INTERRUPT_ENABLED && (BleUart_RX_ENABLED || BleUart_HD_ENABLED)) */


/*******************************************************************************
* Function Name: BleUart_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  BleUart_Start() sets the initVar variable, calls the
*  BleUart_Init() function, and then calls the
*  BleUart_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The BleUart_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time BleUart_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the BleUart_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BleUart_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(BleUart_initVar == 0u)
    {
        BleUart_Init();
        BleUart_initVar = 1u;
    }

    BleUart_Enable();
}


/*******************************************************************************
* Function Name: BleUart_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call BleUart_Init() because
*  the BleUart_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BleUart_Init(void) 
{
    #if(BleUart_RX_ENABLED || BleUart_HD_ENABLED)

        #if (BleUart_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(BleUart_RX_VECT_NUM, &BleUart_RXISR);
            CyIntSetPriority(BleUart_RX_VECT_NUM, BleUart_RX_PRIOR_NUM);
            BleUart_errorStatus = 0u;
        #endif /* (BleUart_RX_INTERRUPT_ENABLED) */

        #if (BleUart_RXHW_ADDRESS_ENABLED)
            BleUart_SetRxAddressMode(BleUart_RX_ADDRESS_MODE);
            BleUart_SetRxAddress1(BleUart_RX_HW_ADDRESS1);
            BleUart_SetRxAddress2(BleUart_RX_HW_ADDRESS2);
        #endif /* End BleUart_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        BleUart_RXBITCTR_PERIOD_REG = BleUart_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        BleUart_RXSTATUS_MASK_REG  = BleUart_INIT_RX_INTERRUPTS_MASK;
    #endif /* End BleUart_RX_ENABLED || BleUart_HD_ENABLED*/

    #if(BleUart_TX_ENABLED)
        #if (BleUart_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(BleUart_TX_VECT_NUM, &BleUart_TXISR);
            CyIntSetPriority(BleUart_TX_VECT_NUM, BleUart_TX_PRIOR_NUM);
        #endif /* (BleUart_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (BleUart_TXCLKGEN_DP)
            BleUart_TXBITCLKGEN_CTR_REG = BleUart_BIT_CENTER;
            BleUart_TXBITCLKTX_COMPLETE_REG = ((BleUart_NUMBER_OF_DATA_BITS +
                        BleUart_NUMBER_OF_START_BIT) * BleUart_OVER_SAMPLE_COUNT) - 1u;
        #else
            BleUart_TXBITCTR_PERIOD_REG = ((BleUart_NUMBER_OF_DATA_BITS +
                        BleUart_NUMBER_OF_START_BIT) * BleUart_OVER_SAMPLE_8) - 1u;
        #endif /* End BleUart_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (BleUart_TX_INTERRUPT_ENABLED)
            BleUart_TXSTATUS_MASK_REG = BleUart_TX_STS_FIFO_EMPTY;
        #else
            BleUart_TXSTATUS_MASK_REG = BleUart_INIT_TX_INTERRUPTS_MASK;
        #endif /*End BleUart_TX_INTERRUPT_ENABLED*/

    #endif /* End BleUart_TX_ENABLED */

    #if(BleUart_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        BleUart_WriteControlRegister( \
            (BleUart_ReadControlRegister() & (uint8)~BleUart_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(BleUart_PARITY_TYPE << BleUart_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End BleUart_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: BleUart_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call BleUart_Enable() because the BleUart_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BleUart_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void BleUart_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (BleUart_RX_ENABLED || BleUart_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        BleUart_RXBITCTR_CONTROL_REG |= BleUart_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        BleUart_RXSTATUS_ACTL_REG  |= BleUart_INT_ENABLE;

        #if (BleUart_RX_INTERRUPT_ENABLED)
            BleUart_EnableRxInt();

            #if (BleUart_RXHW_ADDRESS_ENABLED)
                BleUart_rxAddressDetected = 0u;
            #endif /* (BleUart_RXHW_ADDRESS_ENABLED) */
        #endif /* (BleUart_RX_INTERRUPT_ENABLED) */
    #endif /* (BleUart_RX_ENABLED || BleUart_HD_ENABLED) */

    #if(BleUart_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!BleUart_TXCLKGEN_DP)
            BleUart_TXBITCTR_CONTROL_REG |= BleUart_CNTR_ENABLE;
        #endif /* End BleUart_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        BleUart_TXSTATUS_ACTL_REG |= BleUart_INT_ENABLE;
        #if (BleUart_TX_INTERRUPT_ENABLED)
            BleUart_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            BleUart_EnableTxInt();
        #endif /* (BleUart_TX_INTERRUPT_ENABLED) */
     #endif /* (BleUart_TX_INTERRUPT_ENABLED) */

    #if (BleUart_INTERNAL_CLOCK_USED)
        BleUart_IntClock_Start();  /* Enable the clock */
    #endif /* (BleUart_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BleUart_Stop
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
void BleUart_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (BleUart_RX_ENABLED || BleUart_HD_ENABLED)
        BleUart_RXBITCTR_CONTROL_REG &= (uint8) ~BleUart_CNTR_ENABLE;
    #endif /* (BleUart_RX_ENABLED || BleUart_HD_ENABLED) */

    #if (BleUart_TX_ENABLED)
        #if(!BleUart_TXCLKGEN_DP)
            BleUart_TXBITCTR_CONTROL_REG &= (uint8) ~BleUart_CNTR_ENABLE;
        #endif /* (!BleUart_TXCLKGEN_DP) */
    #endif /* (BleUart_TX_ENABLED) */

    #if (BleUart_INTERNAL_CLOCK_USED)
        BleUart_IntClock_Stop();   /* Disable the clock */
    #endif /* (BleUart_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (BleUart_RX_ENABLED || BleUart_HD_ENABLED)
        BleUart_RXSTATUS_ACTL_REG  &= (uint8) ~BleUart_INT_ENABLE;

        #if (BleUart_RX_INTERRUPT_ENABLED)
            BleUart_DisableRxInt();
        #endif /* (BleUart_RX_INTERRUPT_ENABLED) */
    #endif /* (BleUart_RX_ENABLED || BleUart_HD_ENABLED) */

    #if (BleUart_TX_ENABLED)
        BleUart_TXSTATUS_ACTL_REG &= (uint8) ~BleUart_INT_ENABLE;

        #if (BleUart_TX_INTERRUPT_ENABLED)
            BleUart_DisableTxInt();
        #endif /* (BleUart_TX_INTERRUPT_ENABLED) */
    #endif /* (BleUart_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BleUart_ReadControlRegister
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
uint8 BleUart_ReadControlRegister(void) 
{
    #if (BleUart_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(BleUart_CONTROL_REG);
    #endif /* (BleUart_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: BleUart_WriteControlRegister
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
void  BleUart_WriteControlRegister(uint8 control) 
{
    #if (BleUart_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       BleUart_CONTROL_REG = control;
    #endif /* (BleUart_CONTROL_REG_REMOVED) */
}


#if(BleUart_RX_ENABLED || BleUart_HD_ENABLED)
    /*******************************************************************************
    * Function Name: BleUart_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      BleUart_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      BleUart_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      BleUart_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      BleUart_RX_STS_BREAK            Interrupt on break.
    *      BleUart_RX_STS_OVERRUN          Interrupt on overrun error.
    *      BleUart_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      BleUart_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BleUart_SetRxInterruptMode(uint8 intSrc) 
    {
        BleUart_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: BleUart_ReadRxData
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
    *  BleUart_rxBuffer - RAM buffer pointer for save received data.
    *  BleUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BleUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BleUart_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BleUart_ReadRxData(void) 
    {
        uint8 rxData;

    #if (BleUart_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BleUart_DisableRxInt();

        locRxBufferRead  = BleUart_rxBufferRead;
        locRxBufferWrite = BleUart_rxBufferWrite;

        if( (BleUart_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BleUart_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= BleUart_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BleUart_rxBufferRead = locRxBufferRead;

            if(BleUart_rxBufferLoopDetect != 0u)
            {
                BleUart_rxBufferLoopDetect = 0u;
                #if ((BleUart_RX_INTERRUPT_ENABLED) && (BleUart_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BleUart_HD_ENABLED )
                        if((BleUart_CONTROL_REG & BleUart_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BleUart_RXSTATUS_MASK_REG  |= BleUart_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BleUart_RXSTATUS_MASK_REG  |= BleUart_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BleUart_HD_ENABLED */
                #endif /* ((BleUart_RX_INTERRUPT_ENABLED) && (BleUart_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = BleUart_RXDATA_REG;
        }

        BleUart_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = BleUart_RXDATA_REG;

    #endif /* (BleUart_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BleUart_ReadRxStatus
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
    *  BleUart_RX_STS_FIFO_NOTEMPTY.
    *  BleUart_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  BleUart_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   BleUart_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   BleUart_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 BleUart_ReadRxStatus(void) 
    {
        uint8 status;

        status = BleUart_RXSTATUS_REG & BleUart_RX_HW_MASK;

    #if (BleUart_RX_INTERRUPT_ENABLED)
        if(BleUart_rxBufferOverflow != 0u)
        {
            status |= BleUart_RX_STS_SOFT_BUFF_OVER;
            BleUart_rxBufferOverflow = 0u;
        }
    #endif /* (BleUart_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: BleUart_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. BleUart_GetChar() is
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
    *  BleUart_rxBuffer - RAM buffer pointer for save received data.
    *  BleUart_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BleUart_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BleUart_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BleUart_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (BleUart_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BleUart_DisableRxInt();

        locRxBufferRead  = BleUart_rxBufferRead;
        locRxBufferWrite = BleUart_rxBufferWrite;

        if( (BleUart_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BleUart_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= BleUart_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BleUart_rxBufferRead = locRxBufferRead;

            if(BleUart_rxBufferLoopDetect != 0u)
            {
                BleUart_rxBufferLoopDetect = 0u;
                #if( (BleUart_RX_INTERRUPT_ENABLED) && (BleUart_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BleUart_HD_ENABLED )
                        if((BleUart_CONTROL_REG & BleUart_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BleUart_RXSTATUS_MASK_REG |= BleUart_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BleUart_RXSTATUS_MASK_REG |= BleUart_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BleUart_HD_ENABLED */
                #endif /* BleUart_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = BleUart_RXSTATUS_REG;
            if((rxStatus & BleUart_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = BleUart_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (BleUart_RX_STS_BREAK | BleUart_RX_STS_PAR_ERROR |
                                BleUart_RX_STS_STOP_ERROR | BleUart_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        BleUart_EnableRxInt();

    #else

        rxStatus =BleUart_RXSTATUS_REG;
        if((rxStatus & BleUart_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = BleUart_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (BleUart_RX_STS_BREAK | BleUart_RX_STS_PAR_ERROR |
                            BleUart_RX_STS_STOP_ERROR | BleUart_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (BleUart_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BleUart_GetByte
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
    uint16 BleUart_GetByte(void) 
    {
        
    #if (BleUart_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        BleUart_DisableRxInt();
        locErrorStatus = (uint16)BleUart_errorStatus;
        BleUart_errorStatus = 0u;
        BleUart_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | BleUart_ReadRxData() );
    #else
        return ( ((uint16)BleUart_ReadRxStatus() << 8u) | BleUart_ReadRxData() );
    #endif /* BleUart_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: BleUart_GetRxBufferSize
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
    *  BleUart_rxBufferWrite - used to calculate left bytes.
    *  BleUart_rxBufferRead - used to calculate left bytes.
    *  BleUart_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 BleUart_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BleUart_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        BleUart_DisableRxInt();

        if(BleUart_rxBufferRead == BleUart_rxBufferWrite)
        {
            if(BleUart_rxBufferLoopDetect != 0u)
            {
                size = BleUart_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(BleUart_rxBufferRead < BleUart_rxBufferWrite)
        {
            size = (BleUart_rxBufferWrite - BleUart_rxBufferRead);
        }
        else
        {
            size = (BleUart_RX_BUFFER_SIZE - BleUart_rxBufferRead) + BleUart_rxBufferWrite;
        }

        BleUart_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((BleUart_RXSTATUS_REG & BleUart_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (BleUart_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: BleUart_ClearRxBuffer
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
    *  BleUart_rxBufferWrite - cleared to zero.
    *  BleUart_rxBufferRead - cleared to zero.
    *  BleUart_rxBufferLoopDetect - cleared to zero.
    *  BleUart_rxBufferOverflow - cleared to zero.
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
    void BleUart_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        BleUart_RXDATA_AUX_CTL_REG |= (uint8)  BleUart_RX_FIFO_CLR;
        BleUart_RXDATA_AUX_CTL_REG &= (uint8) ~BleUart_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BleUart_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BleUart_DisableRxInt();

        BleUart_rxBufferRead = 0u;
        BleUart_rxBufferWrite = 0u;
        BleUart_rxBufferLoopDetect = 0u;
        BleUart_rxBufferOverflow = 0u;

        BleUart_EnableRxInt();

    #endif /* (BleUart_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: BleUart_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  BleUart__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  BleUart__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  BleUart__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  BleUart__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  BleUart__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BleUart_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  BleUart_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void BleUart_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(BleUart_RXHW_ADDRESS_ENABLED)
            #if(BleUart_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* BleUart_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = BleUart_CONTROL_REG & (uint8)~BleUart_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << BleUart_CTRL_RXADDR_MODE0_SHIFT);
                BleUart_CONTROL_REG = tmpCtrl;

                #if(BleUart_RX_INTERRUPT_ENABLED && \
                   (BleUart_RXBUFFERSIZE > BleUart_FIFO_LENGTH) )
                    BleUart_rxAddressMode = addressMode;
                    BleUart_rxAddressDetected = 0u;
                #endif /* End BleUart_RXBUFFERSIZE > BleUart_FIFO_LENGTH*/
            #endif /* End BleUart_CONTROL_REG_REMOVED */
        #else /* BleUart_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End BleUart_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BleUart_SetRxAddress1
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
    void BleUart_SetRxAddress1(uint8 address) 
    {
        BleUart_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: BleUart_SetRxAddress2
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
    void BleUart_SetRxAddress2(uint8 address) 
    {
        BleUart_RXADDRESS2_REG = address;
    }

#endif  /* BleUart_RX_ENABLED || BleUart_HD_ENABLED*/


#if( (BleUart_TX_ENABLED) || (BleUart_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: BleUart_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   BleUart_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   BleUart_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   BleUart_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   BleUart_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BleUart_SetTxInterruptMode(uint8 intSrc) 
    {
        BleUart_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: BleUart_WriteTxData
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
    *  BleUart_txBuffer - RAM buffer pointer for save data for transmission
    *  BleUart_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  BleUart_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  BleUart_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BleUart_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(BleUart_initVar != 0u)
        {
        #if (BleUart_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            BleUart_DisableTxInt();

            if( (BleUart_txBufferRead == BleUart_txBufferWrite) &&
                ((BleUart_TXSTATUS_REG & BleUart_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                BleUart_TXDATA_REG = txDataByte;
            }
            else
            {
                if(BleUart_txBufferWrite >= BleUart_TX_BUFFER_SIZE)
                {
                    BleUart_txBufferWrite = 0u;
                }

                BleUart_txBuffer[BleUart_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                BleUart_txBufferWrite++;
            }

            BleUart_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            BleUart_TXDATA_REG = txDataByte;

        #endif /*(BleUart_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: BleUart_ReadTxStatus
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
    uint8 BleUart_ReadTxStatus(void) 
    {
        return(BleUart_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: BleUart_PutChar
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
    *  BleUart_txBuffer - RAM buffer pointer for save data for transmission
    *  BleUart_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  BleUart_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  BleUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void BleUart_PutChar(uint8 txDataByte) 
    {
    #if (BleUart_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            BleUart_DisableTxInt();
        #endif /* (BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = BleUart_txBufferWrite;
            locTxBufferRead  = BleUart_txBufferRead;

        #if ((BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            BleUart_EnableTxInt();
        #endif /* (BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(BleUart_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((BleUart_TXSTATUS_REG & BleUart_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            BleUart_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= BleUart_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            BleUart_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            BleUart_DisableTxInt();
        #endif /* (BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            BleUart_txBufferWrite = locTxBufferWrite;

        #if ((BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3))
            BleUart_EnableTxInt();
        #endif /* (BleUart_TX_BUFFER_SIZE > BleUart_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (BleUart_TXSTATUS_REG & BleUart_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                BleUart_SetPendingTxInt();
            }
        }

    #else

        while((BleUart_TXSTATUS_REG & BleUart_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        BleUart_TXDATA_REG = txDataByte;

    #endif /* BleUart_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BleUart_PutString
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
    *  BleUart_initVar - checked to identify that the component has been
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
    void BleUart_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BleUart_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                BleUart_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BleUart_PutArray
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
    *  BleUart_initVar - checked to identify that the component has been
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
    void BleUart_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BleUart_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                BleUart_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BleUart_PutCRLF
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
    *  BleUart_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BleUart_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(BleUart_initVar != 0u)
        {
            BleUart_PutChar(txDataByte);
            BleUart_PutChar(0x0Du);
            BleUart_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: BleUart_GetTxBufferSize
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
    *  BleUart_txBufferWrite - used to calculate left space.
    *  BleUart_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 BleUart_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BleUart_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BleUart_DisableTxInt();

        if(BleUart_txBufferRead == BleUart_txBufferWrite)
        {
            size = 0u;
        }
        else if(BleUart_txBufferRead < BleUart_txBufferWrite)
        {
            size = (BleUart_txBufferWrite - BleUart_txBufferRead);
        }
        else
        {
            size = (BleUart_TX_BUFFER_SIZE - BleUart_txBufferRead) +
                    BleUart_txBufferWrite;
        }

        BleUart_EnableTxInt();

    #else

        size = BleUart_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & BleUart_TX_STS_FIFO_FULL) != 0u)
        {
            size = BleUart_FIFO_LENGTH;
        }
        else if((size & BleUart_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (BleUart_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: BleUart_ClearTxBuffer
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
    *  BleUart_txBufferWrite - cleared to zero.
    *  BleUart_txBufferRead - cleared to zero.
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
    void BleUart_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        BleUart_TXDATA_AUX_CTL_REG |= (uint8)  BleUart_TX_FIFO_CLR;
        BleUart_TXDATA_AUX_CTL_REG &= (uint8) ~BleUart_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BleUart_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BleUart_DisableTxInt();

        BleUart_txBufferRead = 0u;
        BleUart_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        BleUart_EnableTxInt();

    #endif /* (BleUart_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BleUart_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   BleUart_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   BleUart_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   BleUart_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   BleUart_SEND_WAIT_REINIT - Performs both options: 
    *      BleUart_SEND_BREAK and BleUart_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BleUart_initVar - checked to identify that the component has been
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
    *     When interrupt appear with BleUart_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The BleUart_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void BleUart_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(BleUart_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(BleUart_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == BleUart_SEND_BREAK) ||
                (retMode == BleUart_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                BleUart_WriteControlRegister(BleUart_ReadControlRegister() |
                                                      BleUart_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                BleUart_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BleUart_TXSTATUS_REG;
                }
                while((tmpStat & BleUart_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BleUart_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BleUart_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BleUart_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BleUart_REINIT) ||
                (retMode == BleUart_SEND_WAIT_REINIT) )
            {
                BleUart_WriteControlRegister(BleUart_ReadControlRegister() &
                                              (uint8)~BleUart_CTRL_HD_SEND_BREAK);
            }

        #else /* BleUart_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == BleUart_SEND_BREAK) ||
                (retMode == BleUart_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (BleUart_PARITY_TYPE != BleUart__B_UART__NONE_REVB) || \
                                    (BleUart_PARITY_TYPE_SW != 0u) )
                    BleUart_WriteControlRegister(BleUart_ReadControlRegister() |
                                                          BleUart_CTRL_HD_SEND_BREAK);
                #endif /* End BleUart_PARITY_TYPE != BleUart__B_UART__NONE_REVB  */

                #if(BleUart_TXCLKGEN_DP)
                    txPeriod = BleUart_TXBITCLKTX_COMPLETE_REG;
                    BleUart_TXBITCLKTX_COMPLETE_REG = BleUart_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = BleUart_TXBITCTR_PERIOD_REG;
                    BleUart_TXBITCTR_PERIOD_REG = BleUart_TXBITCTR_BREAKBITS8X;
                #endif /* End BleUart_TXCLKGEN_DP */

                /* Send zeros */
                BleUart_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BleUart_TXSTATUS_REG;
                }
                while((tmpStat & BleUart_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BleUart_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BleUart_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BleUart_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BleUart_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BleUart_REINIT) ||
                (retMode == BleUart_SEND_WAIT_REINIT) )
            {

            #if(BleUart_TXCLKGEN_DP)
                BleUart_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                BleUart_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End BleUart_TXCLKGEN_DP */

            #if( (BleUart_PARITY_TYPE != BleUart__B_UART__NONE_REVB) || \
                 (BleUart_PARITY_TYPE_SW != 0u) )
                BleUart_WriteControlRegister(BleUart_ReadControlRegister() &
                                                      (uint8) ~BleUart_CTRL_HD_SEND_BREAK);
            #endif /* End BleUart_PARITY_TYPE != NONE */
            }
        #endif    /* End BleUart_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: BleUart_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       BleUart_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       BleUart_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears BleUart_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void BleUart_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( BleUart_CONTROL_REG_REMOVED == 0u )
            BleUart_WriteControlRegister(BleUart_ReadControlRegister() |
                                                  BleUart_CTRL_MARK);
        #endif /* End BleUart_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( BleUart_CONTROL_REG_REMOVED == 0u )
            BleUart_WriteControlRegister(BleUart_ReadControlRegister() &
                                                  (uint8) ~BleUart_CTRL_MARK);
        #endif /* End BleUart_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndBleUart_TX_ENABLED */

#if(BleUart_HD_ENABLED)


    /*******************************************************************************
    * Function Name: BleUart_LoadRxConfig
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
    void BleUart_LoadRxConfig(void) 
    {
        BleUart_WriteControlRegister(BleUart_ReadControlRegister() &
                                                (uint8)~BleUart_CTRL_HD_SEND);
        BleUart_RXBITCTR_PERIOD_REG = BleUart_HD_RXBITCTR_INIT;

    #if (BleUart_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        BleUart_SetRxInterruptMode(BleUart_INIT_RX_INTERRUPTS_MASK);
    #endif /* (BleUart_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BleUart_LoadTxConfig
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
    void BleUart_LoadTxConfig(void) 
    {
    #if (BleUart_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        BleUart_SetRxInterruptMode(0u);
    #endif /* (BleUart_RX_INTERRUPT_ENABLED) */

        BleUart_WriteControlRegister(BleUart_ReadControlRegister() | BleUart_CTRL_HD_SEND);
        BleUart_RXBITCTR_PERIOD_REG = BleUart_HD_TXBITCTR_INIT;
    }

#endif  /* BleUart_HD_ENABLED */


/* [] END OF FILE */
