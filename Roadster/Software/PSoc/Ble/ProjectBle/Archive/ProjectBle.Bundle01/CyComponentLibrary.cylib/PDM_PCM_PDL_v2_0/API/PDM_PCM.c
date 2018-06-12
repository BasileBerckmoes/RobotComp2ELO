/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the
*  `$INSTANCE_NAME` component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/** An instance-specific configuration structure.
*   It should be used in the associated Cy_PDM_PCM_Init() function.
*/
`=$CY_CONST_CONFIG ? "const " : ""` cy_stc_pdm_pcm_config_t `$INSTANCE_NAME`_config =
{
    .clkDiv             = `=GetNameForEnum("cy_en_pdm_pcm_clk_div_t", $ClkDiv)`,
    .mclkDiv            = `=GetNameForEnum("cy_en_pdm_pcm_clk_div_t", $MclkDiv)`,
    .ckoDiv             = `$CkoDiv`U,
    .ckoDelay           = `$CkoDelay`U,
    .sincDecRate        = `$SincDecRate`U,
    .chanSelect         = `=GetNameForEnum("cy_en_pdm_pcm_out_t", $ChanSelect)`,
    .chanSwapEnable     = `=$ChanSwap ? true : false`,
    .highPassFilterGain = `$HighPassFilterGain`U,
    .highPassDisable    = `=$HighPassDisable ? true : false`,
    .softMuteCycles     = `=GetNameForEnum("cy_en_pdm_pcm_s_cycles_t", $SoftMuteCycles)`,
    .softMuteFineGain   = `$SoftMuteFineGain`UL,
    .softMuteEnable     = `=$SoftMuteEnable ? true : false`,
    .wordLen            = `=GetNameForEnum("cy_en_pdm_pcm_word_len_t", $WordLength)`,
    .signExtension      = `=$SignExtension ? true : false`,
    .gainLeft           = `=GetNameForEnum("cy_en_pdm_pcm_gain_t", $GainLeft)`,
    .gainRight          = `=GetNameForEnum("cy_en_pdm_pcm_gain_t", $GainRight)`,
    .rxFifoTriggerLevel = `$RxFifoTriggerLevel`U,
    .dmaTriggerEnable   = `=$RxFifoDmaEnable ? true : false`,
    .interruptMask      = `$InterruptMask`
};

/* An internal variable indicates whether the `$INSTANCE_NAME` has been
*  initialized. The variable is initialized to 0 and set to 1 the first time
*  `$INSTANCE_NAME`_Start() is called. This allows the Component to
*  restart without reinitialization after the first call to the
*  `$INSTANCE_NAME`_Start() routine. The variable is cleared by the
*  `$INSTANCE_NAME`_DeInit() routine call.
*/
uint8_t `$INSTANCE_NAME`_initVar = 0U;

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Calls the Cy_PDM_PCM_Init() function when called the first time or after the
* \ref `$INSTANCE_NAME`_DeInit() call, then clears FIFO and enables the PDM-PCM 
* data coversion. For subsequent calls (after the
* \ref `$INSTANCE_NAME`_Stop() call) the configuration is left unchanged, the
* FIFO is cleared and the PDM-PCM data coversion is enabled.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0U == `$INSTANCE_NAME`_initVar)
    {
        (void) Cy_PDM_PCM_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config);
        `$INSTANCE_NAME`_initVar = 1U;
    }

    Cy_PDM_PCM_ClearFifo(`$INSTANCE_NAME`_HW);
    Cy_PDM_PCM_Enable(`$INSTANCE_NAME`_HW);
}


/* [] END OF FILE */
