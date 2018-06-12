/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands for the PDM_PCM
*  component.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;

`=$CY_CONST_CONFIG ? "const " : ""` cy_stc_pdm_pcm_config_t `$INSTANCE_NAME`_config =
{
    .clkDiv = `$INSTANCE_NAME`_CLK_DIV,
    .mclkDiv = `$INSTANCE_NAME`_MCLK_DIV,
    .ckoDiv = `$INSTANCE_NAME`_CKO_DIV,
    .ckoDelay = `$INSTANCE_NAME`_CKO_DELAY,

    .sincDecRate = `$INSTANCE_NAME`_SINC_DEC_RATE,
    
    .chanSelect = `$INSTANCE_NAME`_CHAN_SELECT,
    .chanSwapEnable = `$INSTANCE_NAME`_CHAN_SWAP,
    
    .highPassFilterCoeff = `$INSTANCE_NAME`_HPF_COEFF,
    .highPassDisable = `$INSTANCE_NAME`_HPF_DISABLE,
    
    .softMuteCycles = `$INSTANCE_NAME`_SOFT_MUTE_CYCLES,
    .softMuteFineGain = `$INSTANCE_NAME`_SOFT_MUTE_GAIN,
    .softMuteEnable = `$INSTANCE_NAME`_SOFT_MUTE_ENABLE,
 
    .wordLen = `$INSTANCE_NAME`_WORD_LEN,
    .wordBitExtension = `$INSTANCE_NAME`_WORD_BIT_EXT,
    
    .gainLeft = `$INSTANCE_NAME`_GAIN_LEFT,
    .gainRight = `$INSTANCE_NAME`_GAIN_RIGHT,

    .dataStreamingEnable = `$INSTANCE_NAME`_DATA_STREAM_ENABLE,
    
    .rxFifoTriggerLevel = `$INSTANCE_NAME`_RX_FIFO_TRG_LVL,

    .dmaTriggerEnable = `$INSTANCE_NAME`_DMA_TRG_ENABLE,
    .interruptMask = `$INSTANCE_NAME`_INT_MASK
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
*  Enables PDM_PCM interface. Starts the generation of the sck and ws outputs.
*  The Tx and Rx directions remain disabled. It is not necessary to call
*  PDMPCM_Enable() because the PDMPCM_Start() routine calls this function, which is
*  the preferred method to begin component operation.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_EnableDataStream();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
*  Starts the PDMPCM interface. Starts the generation of the sck and ws outputs.
*  The Tx and Rx directions remain disabled.
*
* \globalvars
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        (void)`$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
*  Disables the PDMPCM interface. The sck and ws outputs are set to 0. The Tx and
*  Rx directions are disabled and their FIFOs are cleared.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
	`$INSTANCE_NAME`_DisableDataStream();
    `$INSTANCE_NAME`_ClearFifo();
    `$INSTANCE_NAME`_Disable();
}


/* [] END OF FILE */
