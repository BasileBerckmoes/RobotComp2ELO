/*******************************************************************************
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides all API functionality of the SENT component
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static uint8 `$INSTANCE_NAME`_CalculateCrc(uint8 const data[]);
static void `$INSTANCE_NAME`_SwapBuffers(void);

#if (`$INSTANCE_NAME`_PAUSE_PULSE == `$INSTANCE_NAME`__ENABLED)
    static uint8 `$INSTANCE_NAME`_CalculatePauseData(uint8 const data[]);
#endif /* `$INSTANCE_NAME`_PAUSE_PULSE == `$INSTANCE_NAME`__ENABLED */


/*******************************************************************************
*   Global variables
*******************************************************************************/

/** The global variable that indicates the initialization status of the 
*  `$INSTANCE_NAME` component
*/
uint8 `$INSTANCE_NAME`_initVar = 0U;

/** The variable that indicates a component status, see \ref group_sent_status */
uint8 `$INSTANCE_NAME`_status = `$INSTANCE_NAME`_READY;


/*******************************************************************************
*       Local variables
*******************************************************************************/

/* The buffers that provide continuous data transmission */
static uint8 `$INSTANCE_NAME`_buf0[`$INSTANCE_NAME`_LAST_IDX];
static uint8 `$INSTANCE_NAME`_buf1[`$INSTANCE_NAME`_LAST_IDX];

/* The pointers to switch through the buffers */
static uint8 *`$INSTANCE_NAME`_bufTx; /* Pointer to the "transfer" data buffer */
static uint8 *`$INSTANCE_NAME`_bufPr; /* Pointer to the "prepare" data buffer */

/* The local index used to jump through pulses */
static uint8 `$INSTANCE_NAME`_idx = `$INSTANCE_NAME`_NEW_FRAME;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Interrupt
****************************************************************************//**
*
* Provides SENT transmission.
*
* This is the interrupt handler which prepares the TCPWM component for the next 
* nibble pulse generation.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_Interrupt)
{
    switch(`$INSTANCE_NAME`_idx)
    {

    #if (`$INSTANCE_NAME`_TRANSMIT_MODE == `$INSTANCE_NAME`__SINGLE_MODE)

        /* Prepare PWM to be stopped on the next PWM interrupt */
        case `$INSTANCE_NAME`_PREPARE_TO_STOP_COUNTER:
        {
            `$INSTANCE_NAME`_PWM_WritePeriod(`$INSTANCE_NAME`_TICKS_PREP_TO_STOP);
            `$INSTANCE_NAME`_PWM_WriteCompare(`$INSTANCE_NAME`_COMP_PREP_TO_STOP);

            /* Update the index value to stop the counter in the next interrupt */
            `$INSTANCE_NAME`_idx = `$INSTANCE_NAME`_STOP_COUNTER;
        }
        break;

        /* One frame transmission was done (Single mode). Stop the PWM and 
        *  prepare the PWM to sent new frame
        */
        case `$INSTANCE_NAME`_STOP_COUNTER:
        {
            `$INSTANCE_NAME`_PWM_TriggerCommand(`$INSTANCE_NAME`_PWM_MASK, `$INSTANCE_NAME`_PWM_CMD_STOP);

            /* Prepare PWM to sent sync pulse if new frame transmission would be
            *  requested.
            */
            `$INSTANCE_NAME`_PWM_WritePeriod(`$INSTANCE_NAME`_SYNC_TICKS - 1U);
            
            /* Clear all required PWM registers */
            `$INSTANCE_NAME`_PWM_WriteCompare(0U);
            `$INSTANCE_NAME`_PWM_WriteCounter(0U);
            `$INSTANCE_NAME`_PWM_WritePeriodBuf(0U);

            `$INSTANCE_NAME`_status = `$INSTANCE_NAME`_READY;
        }
        break;
    #else

        /* One frame transmission was done (Continuous mode). If new data is 
        *  ready swap the buffers, and send the sync pulse
        */
        case `$INSTANCE_NAME`_END_OF_FRAME:
        {
            `$INSTANCE_NAME`_PWM_WriteCompare(`$INSTANCE_NAME`_PWM_LOW_TICKS);
            `$INSTANCE_NAME`_idx = `$INSTANCE_NAME`_NEW_FRAME;

            /* Check for the new data available */
            if (`$INSTANCE_NAME`_status == `$INSTANCE_NAME`_BUSY)
            {
                `$INSTANCE_NAME`_SwapBuffers();
                `$INSTANCE_NAME`_status = `$INSTANCE_NAME`_READY;
            }

            `$INSTANCE_NAME`_PWM_WritePeriodBuf(`$INSTANCE_NAME`_SYNC_TICKS - 1U);

        }
        break;
    #endif /* `$INSTANCE_NAME`_TRANSMIT_MODE == `$INSTANCE_NAME`__SINGLE_MODE */

        /* The default case indicates that message sending is in progress and 
        *  the next nibble pulse should be prepared
        */
        default:
        {
            `$INSTANCE_NAME`_PWM_WritePeriodBuf((`$INSTANCE_NAME`_ZERO_TICKS - 1U) + 
            (uint32) `$INSTANCE_NAME`_bufTx[`$INSTANCE_NAME`_idx]);

            ++`$INSTANCE_NAME`_idx;
        }
        break;
    }
    /* Set a switch trigger flag in the TCPWM trigger register */
    `$INSTANCE_NAME`_PWM_TriggerCommand(`$INSTANCE_NAME`_PWM_MASK, `$INSTANCE_NAME`_PWM_CMD_CAPTURE);

    /* Clear the interrupt pending flag*/
    `$INSTANCE_NAME`_PWM_ClearInterrupt(`$INSTANCE_NAME`_PWM_INTR_MASK_TC);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Initialize/Restore default `$INSTANCE_NAME` configuration.
*
*******************************************************************************/
void   `$INSTANCE_NAME`_Init(void)
{
    `$INSTANCE_NAME`_CLK_SetDividerValue(`$INSTANCE_NAME`_CLOCK_DIVIDER);
    
    `$INSTANCE_NAME`_PWM_Init();
    `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_Interrupt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Initializes `$INSTANCE_NAME` with default customizer values when called
* the first time and enables `$INSTANCE_NAME`.
* For subsequent calls the configuration is left unchanged and only the 
* component is enabled.
*
* \param data
* The pointer to the uint8 array of length `$INSTANCE_NAME`_USER_NIBBLES, where
* the 1st byte is the status nibble and the next 6 bytes are data nibbles.
*
* \globalvars 
* \ref `$INSTANCE_NAME`_initVar
*
* Note each call of `$INSTANCE_NAME`_Start() will restart the counter and the 
* message will be transmitted from the first nibble.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(uint8 const data[]) 
{
    if (`$INSTANCE_NAME`_initVar == 0U)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1U; 
    }

    `$INSTANCE_NAME`_bufPr = `$INSTANCE_NAME`_buf0;
    `$INSTANCE_NAME`_UpdateData(data);

    `$INSTANCE_NAME`_bufTx = `$INSTANCE_NAME`_buf0;
    `$INSTANCE_NAME`_bufPr = `$INSTANCE_NAME`_buf1;

#if (`$INSTANCE_NAME`_TRANSMIT_MODE != `$INSTANCE_NAME`__SINGLE_MODE)
    `$INSTANCE_NAME`_status = `$INSTANCE_NAME`_READY;
#endif /* `$INSTANCE_NAME`_TRANSMIT_MODE != `$INSTANCE_NAME`__SINGLE_MODE */

    /* Reset a SENT_TX interrupt state machine */
    `$INSTANCE_NAME`_idx = `$INSTANCE_NAME`_NEW_FRAME;
    `$INSTANCE_NAME`_PWM_WritePeriod(`$INSTANCE_NAME`_SYNC_TICKS - 1U);
    
    /* Enable the PWM component */
    `$INSTANCE_NAME`_PWM_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateData
****************************************************************************//**
*
* Writes the frame with new data into the transfer buffer.
*
* \param data
* The pointer to the uint8 array of length `$INSTANCE_NAME`_USER_NIBBLES, where
* the first byte is the status nibble and the next six bytes are data nibbles.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UpdateData(uint8 const data[])
{
    uint8 i;

    `$INSTANCE_NAME`_status = `$INSTANCE_NAME`_READY;

    /* Check for the "prepare" data buffer allocation */
    if (`$INSTANCE_NAME`_bufPr != NULL)
    {
        for(i = 0U; i < `$INSTANCE_NAME`_USER_NIBBLES; i++)
        {
            `$INSTANCE_NAME`_bufPr[i] = data[i] & `$INSTANCE_NAME`_NIBBLE_MASK;
        }

        `$INSTANCE_NAME`_bufPr[`$INSTANCE_NAME`_CRC_IDX] = `$INSTANCE_NAME`_CalculateCrc(`$INSTANCE_NAME`_bufPr);

    #if (`$INSTANCE_NAME`_PAUSE_PULSE == `$INSTANCE_NAME`__ENABLED)

        /* Calculate pause pulse value */
        `$INSTANCE_NAME`_bufPr[`$INSTANCE_NAME`_PAUSE_IDX] = 
        `$INSTANCE_NAME`_CalculatePauseData(`$INSTANCE_NAME`_bufPr);
    #endif /* `$INSTANCE_NAME`_PAUSE_PULSE == `$INSTANCE_NAME`__ENABLED */

    #if (`$INSTANCE_NAME`_TRANSMIT_MODE == `$INSTANCE_NAME`__SINGLE_MODE)

        /* Restart the PWM (Single mode), swap the buffers for the new frame
        *  transition
        */
        if (`$INSTANCE_NAME`_idx == `$INSTANCE_NAME`_STOP_COUNTER)
        {
            `$INSTANCE_NAME`_idx = `$INSTANCE_NAME`_NEW_FRAME;
            `$INSTANCE_NAME`_SwapBuffers();

            `$INSTANCE_NAME`_PWM_WriteCompare(`$INSTANCE_NAME`_PWM_LOW_TICKS);
            `$INSTANCE_NAME`_PWM_TriggerCommand(`$INSTANCE_NAME`_PWM_MASK, `$INSTANCE_NAME`_PWM_CMD_START);
        }
    #endif /* `$INSTANCE_NAME`_TRANSMIT_MODE == `$INSTANCE_NAME`__SINGLE_MODE */ 

        `$INSTANCE_NAME`_status = `$INSTANCE_NAME`_BUSY;
    }
    else
    {
       CYASSERT(0U != 0U);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CalculateCrc
****************************************************************************//**
*
* Calculates the cyclic redundancy check value.
*
* \param data
* The pointer to the uint8 array of length `$INSTANCE_NAME`_USER_NIBBLES, where
* the 1st byte is the status nibble and the next 6 bytes are data nibbles.
*
* \return
* The cyclic redundancy check value of the new data nibbles.
*
*******************************************************************************/
static uint8 `$INSTANCE_NAME`_CalculateCrc(uint8 const data[])
{
    /* This is a lookup table that writes in the RAM memory */
    static const uint8 crcTable[] = 
    {
        0U, 13U, 7U, 10U, 14U, 3U, 9U, 4U,
        1U, 12U, 6U, 11U, 15U, 2U, 8U, 5U
    };
    
    /* Write the seed value in the crc variable before calculations */
    uint8 crc = `$INSTANCE_NAME`_SEED;
    uint32 i;
    
    /* Calculate the data CRC value */
    for(i = 1U; i < `$INSTANCE_NAME`_USER_NIBBLES; i++)
    {
        crc = crcTable[crc] ^ (data[i] & `$INSTANCE_NAME`_NIBBLE_MASK);
    }

#if (`$INSTANCE_NAME`_CRC_IMPLEMENTATION == `$INSTANCE_NAME`__NEWCRC)
    /* The checksum using new CRC method */
    crc = crcTable[crc];
#endif /* `$INSTANCE_NAME`_CRC_IMPLEMENTATION == `$INSTANCE_NAME`__NEWCRC */

    return (crc);
}

#if (`$INSTANCE_NAME`_PAUSE_PULSE == `$INSTANCE_NAME`__ENABLED)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CalculatePauseData
    ****************************************************************************//**
    *
    * Calculates the duration of the pause nibble, for the frame with new data.
    *
    * \param data
    * The pointer to the uint8 array of length `$INSTANCE_NAME`_ALL_NIBBLES, where
    * the 1st byte is the status nibble, the next 6 bytes are data nibbles,
    * and the last nibble is a CRC value.
    *
    * \return
    * The duration of the pause period (in clock period units).
    *
    *******************************************************************************/
    static uint8 `$INSTANCE_NAME`_CalculatePauseData(uint8 const data[])
    {
        uint8 frameDuration = `$INSTANCE_NAME`_ALL_TICKS - ((uint8)`$INSTANCE_NAME`_SYNC_TICKS + `$INSTANCE_NAME`_ZERO_TICKS);

        uint8 i;

        for(i = 0U; i < `$INSTANCE_NAME`_ALL_NIBBLES; i++)
        {
            frameDuration -= (`$INSTANCE_NAME`_ZERO_TICKS + (data[i] & `$INSTANCE_NAME`_NIBBLE_MASK));
        }

        return (frameDuration);
    }
#endif /* `$INSTANCE_NAME`_PAUSE_PULSE == `$INSTANCE_NAME`__ENABLED */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SwapBuffers
****************************************************************************//**
*
* Internal function which swaps the "transmition" and "prepare" buffers
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SwapBuffers(void)
{
    if (`$INSTANCE_NAME`_bufTx == `$INSTANCE_NAME`_buf0)
    {
        `$INSTANCE_NAME`_bufTx = `$INSTANCE_NAME`_buf1;
        `$INSTANCE_NAME`_bufPr = `$INSTANCE_NAME`_buf0;
    }
    else
    {
        `$INSTANCE_NAME`_bufTx = `$INSTANCE_NAME`_buf0;
        `$INSTANCE_NAME`_bufPr = `$INSTANCE_NAME`_buf1;
    }
}


/* [] END OF FILE */
