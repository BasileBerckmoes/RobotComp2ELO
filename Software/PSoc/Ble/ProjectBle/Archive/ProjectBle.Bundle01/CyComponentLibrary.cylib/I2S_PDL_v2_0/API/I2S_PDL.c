/***************************************************************************//**
* \file     `$INSTANCE_NAME`.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the
*  `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*     Global variables
***************************************/

/** An instance-specific configuration structure.
*   It should be used in the associated Cy_I2S_Init() function.
*/
`=$CY_CONST_CONFIG ? "const " : ""`cy_stc_i2s_config_t `$INSTANCE_NAME`_config =
{
    .txEnabled          = `=$TxEnabled ? true : false`,
    .rxEnabled          = `=$RxEnabled ? true : false`,
    .txDmaTrigger       = `=$TxDmaTrigger ? true : false`,
    .rxDmaTrigger       = `=$RxDmaTrigger ? true : false`,
    .clkDiv             = `$ClockDiv`U,
    .extClk             = `=$ExtClk ? true : false`,
    .txMasterMode       = `=$TxMasterMode ? true : false`,
    .txAlignment        = `=GetNameForEnum("cy_en_i2s_alignment_t", $TxAlignment)`,
    .txWsPulseWidth     = `=GetNameForEnum("cy_en_i2s_ws_pw_t", $TxWsPulseWidth)`,
    .txWatchdogEnable   = `=$TxWatchdogEnable ? true : false`,
    .txWatchdogValue    = `=IntToHexString($TxWatchdogValue)`UL,
    .txSdoLatchingTime  = `=$TxSdoLatchingTime ? true : false`,
    .txSckoInversion    = `=$TxSckoPolarity ? true : false`,
    .txSckiInversion    = `=$TxSckiPolarity ? true : false`,
    .txChannels         = `$TxChannels`U,
    .txChannelLength    = `=GetNameForEnum("cy_en_i2s_len_t", $TxChannelLength)`,
    .txWordLength       = `=GetNameForEnum("cy_en_i2s_len_t", $TxWordLength)`,
    .txOverheadValue    = `=GetNameForEnum("cy_en_i2s_overhead_t", $TxOverheadValue)`,
    .txFifoTriggerLevel = `$TxFifoTriggerLevel`U,
    .rxMasterMode       = `=$RxMasterMode ? true : false`,
    .rxAlignment        = `=GetNameForEnum("cy_en_i2s_alignment_t", $RxAlignment)`,
    .rxWsPulseWidth     = `=GetNameForEnum("cy_en_i2s_ws_pw_t", $RxWsPulseWidth)`,
    .rxWatchdogEnable   = `=$RxWatchdogEnable ? true : false`,
    .rxWatchdogValue    = `=IntToHexString($RxWatchdogValue)`UL,
    .rxSdiLatchingTime  = `=$RxSdiLatchingTime ? true : false`,
    .rxSckoInversion    = `=$RxSckoPolarity ? true : false`,
    .rxSckiInversion    = `=$RxSckiPolarity ? true : false`,
    .rxChannels         = `$RxChannels`U,
    .rxChannelLength    = `=GetNameForEnum("cy_en_i2s_len_t", $RxChannelLength)`,
    .rxWordLength       = `=GetNameForEnum("cy_en_i2s_len_t", $RxWordLength)`,
    .rxSignExtension    = `=$RxSignExtension ? true : false`,
    .rxFifoTriggerLevel = `$RxFifoTriggerLevel`U
};

/* An internal variable indicates whether the `$INSTANCE_NAME` has been
*  initialized. The variable is initialized to 0 and set to 1 the first time
*  `$INSTANCE_NAME`_Start() is called. This allows the Component to
*  restart without reinitialization after the first call to the
*  `$INSTANCE_NAME`_Start() routine. The variable is cleared by the
*  `$INSTANCE_NAME`_DeInit() routine call.
*/
uint8_t `$INSTANCE_NAME`_initVar = 0U;

/* A structure to save the current TX/RX enable/disable Component state and
*  interrupt settings (the Component settings that can be changed on the fly
*  by the component API) during a stop/start sequence, and also can be used as
*  a SysPm callback context.
*/
cy_stc_i2s_context_t `$INSTANCE_NAME`_backup;


/*******************************************************************************
*     Functions
*******************************************************************************/


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Calls the Cy_I2S_Init() function when called the first time or after the
* \ref `$INSTANCE_NAME`_DeInit() call, then clears FIFOs, fills the first TX 
* FIFO frame with zeros, enables the TX and/or RX (accordingly to the
* configuration) and enables interrupts. For subsequent calls (after the
* \ref `$INSTANCE_NAME`_Stop() call) the configuration is left unchanged, the
* FIFOs are cleared (with the first TX FIFO frame filled with zeros), TX and/or
* RX operation and interrupts are enabled accordingly to the state before
* previous \ref `$INSTANCE_NAME`_Stop() calling.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
#if(`$INSTANCE_NAME`_TX_ENABLED)
    /* The local Tx channel counter to set the first data transmission */
    uint32_t locChanCnt;
#endif /* `$INSTANCE_NAME`_TX_ENABLED */
    
    if(0U == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_initVar = 1U;
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_CMD;
        `$INSTANCE_NAME`_backup.interruptMask = `$INSTANCE_NAME`_INT_MASK;

        (void)Cy_I2S_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config);
    }

#if(`$INSTANCE_NAME`_TX_ENABLED)
    if(0UL != (`$INSTANCE_NAME`_backup.enableState & I2S_CMD_TX_START_Msk))
    {
        Cy_I2S_ClearTxFifo(`$INSTANCE_NAME`_HW);
        
        /* The first transmission data setting. Write at least one frame to the FIFO */
        for(locChanCnt = 0UL; locChanCnt < `$INSTANCE_NAME`_config.txChannels; locChanCnt++)
        {
            Cy_I2S_WriteTxData(`$INSTANCE_NAME`_HW, 0UL);
        }
        
        Cy_I2S_EnableTx(`$INSTANCE_NAME`_HW);
    }
#endif /* `$INSTANCE_NAME`_TX_ENABLED */

#if(`$INSTANCE_NAME`_RX_ENABLED)
    if(0UL != (`$INSTANCE_NAME`_backup.enableState & I2S_CMD_RX_START_Msk))
    {
        Cy_I2S_ClearRxFifo(`$INSTANCE_NAME`_HW);
        
        Cy_I2S_EnableRx(`$INSTANCE_NAME`_HW);
    }
#endif /* `$INSTANCE_NAME`_TX_ENABLED */
    
    /* Clear possible pending interrupts */
    Cy_I2S_ClearInterrupt(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_backup.interruptMask);

    /* Enable interrupts */
    Cy_I2S_SetInterruptMask(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_backup.interruptMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Saves the current TX/RX/interrupts state (which can be changed in runtime by
* the PDL API) and then disables TX and/or RX operation and interrupts.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    if(0UL != ((I2S_CMD_TX_START_Msk | I2S_CMD_RX_START_Msk) & Cy_I2S_GetCurrentState(`$INSTANCE_NAME`_HW)))
    {
        /* Store the current component state */
        `$INSTANCE_NAME`_backup.enableState = Cy_I2S_GetCurrentState(`$INSTANCE_NAME`_HW);
        `$INSTANCE_NAME`_backup.interruptMask = Cy_I2S_GetInterruptMask(`$INSTANCE_NAME`_HW);
    
    #if(`$INSTANCE_NAME`_TX_ENABLED)
        if(0UL != (`$INSTANCE_NAME`_backup.enableState & I2S_CMD_TX_START_Msk))
        {
            Cy_I2S_DisableTx(`$INSTANCE_NAME`_HW);
        }
    #endif /* `$INSTANCE_NAME`_TX_ENABLED */

    #if(`$INSTANCE_NAME`_RX_ENABLED)
        if(0UL != (`$INSTANCE_NAME`_backup.enableState & I2S_CMD_RX_START_Msk))
        {
            Cy_I2S_DisableRx(`$INSTANCE_NAME`_HW);
        }
    #endif /* `$INSTANCE_NAME`_RX_ENABLED */
    
        /* Disable interrupts */
        Cy_I2S_SetInterruptMask(`$INSTANCE_NAME`_HW, 0UL);
    }
}
    

#if defined(__cplusplus)
}
#endif

/* [] END OF FILE */
