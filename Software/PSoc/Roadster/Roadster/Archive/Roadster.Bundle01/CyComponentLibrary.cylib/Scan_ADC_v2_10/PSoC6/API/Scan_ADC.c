/***************************************************************************//**
* \file     `$INSTANCE_NAME`.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* Provides the source code to the API for the `$INSTANCE_NAME` Component.
*
********************************************************************************
* \copyright
* (c) 2017, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include <sysint/cy_sysint.h>
#include <cyfitter_sysint_cfg.h>

uint8_t `$INSTANCE_NAME`_initVar = 0u;
uint8_t `$INSTANCE_NAME`_selected = 0u; /* 0 if no configuration selected. 1 otherwise. */
uint32_t `$INSTANCE_NAME`_currentConfig = 0u; /* Currently active configuration */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* \brief Performs all required initialization for this component and enables the
*  power. The power will be set to the appropriate power based on the clock
*  frequency.
*
* \param None
*
* \return None
*
* \sideeffect None
*
* \globalvars
*  \ref `$INSTANCE_NAME`_initVar (RW)
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (`$INSTANCE_NAME`_INIT_VAR_INIT_FLAG != (`$INSTANCE_NAME`_INIT_VAR_INIT_FLAG & `$INSTANCE_NAME`_initVar))
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar |= `$INSTANCE_NAME`_INIT_VAR_INIT_FLAG;
    }

    `$INSTANCE_NAME`_Enable();

    return;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartEx
****************************************************************************//**
*
* \brief This function starts the `$INSTANCE_NAME` and sets the Interrupt
* Service Routine to the provided address using the
* Cy_SysInt_Init() function. Refer to the Interrupt component
* datasheet for more information on the Cy_SysInt_Init() function.
*
* \param address This is the address of a user defined function for the ISR.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_StartEx(cy_israddress userIsr)
{
    `$INSTANCE_NAME`_Start();

    /* Interrupt core assignment will be up to the user. Initialize and enable the interrupt*/
    #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM4_ASSIGNED
    #if (CY_CPU_CORTEX_M4)
        (void)Cy_SysInt_Init(&`$INSTANCE_NAME`_IRQ_cfg, userIsr);
        NVIC_EnableIRQ(`$INSTANCE_NAME`_IRQ_cfg.intrSrc);
    #endif
    #endif

    #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM0P_ASSIGNED
    #if (CY_CPU_CORTEX_M0P)
        (void)Cy_SysInt_Init(&`$INSTANCE_NAME`_IRQ_cfg, userIsr);
        NVIC_EnableIRQ(`$INSTANCE_NAME`_IRQ_cfg.intrSrc);
    #endif
    #endif

}

/* ****************************************************************************
* Function Name: `$INSTANCE_NAME`_InitConfig
****************************************************************************//*
*
* \brief Configures all of the registers for a given configuration for scanning.
*
* \param scan Number of scan defined in the `$INSTANCE_NAME`.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitConfig(const `$INSTANCE_NAME`_CONFIG_STRUCT *config)
{
    bool deInitRouting = false;

    /* If there is an internal SAR clock, set up its divider values. */
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        `$INSTANCE_NAME`_intSarClock_Disable();
        `$INSTANCE_NAME`_intSarClock_SetDivider(config->clkDivider);
        `$INSTANCE_NAME`_intSarClock_Enable();
    #endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */

    /* Init SAR and MUX registers */
    (void)Cy_SAR_DeInit(`$INSTANCE_NAME`_SAR__HW, deInitRouting);
    (void)Cy_SAR_Init(`$INSTANCE_NAME`_SAR__HW, config->hwConfigStc);

    /* Connect Vminus to VSSA when even one channel is single-ended or multiple channels configured */
    if(1uL == `$INSTANCE_NAME`_MUX_SWITCH0_INIT)
    {
        Cy_SAR_SetVssaVminusSwitch(`$INSTANCE_NAME`_SAR__HW, CY_SAR_SWITCH_CLOSE);

        /* Set MUX_HW_CTRL_VSSA in MUX_SWITCH_HW_CTRL when multiple channels enabled */
        if(1uL < config->numChannels)
        {
            Cy_SAR_SetVssaSarSeqCtrl(`$INSTANCE_NAME`_SAR__HW, CY_SAR_SWITCH_SEQ_CTRL_ENABLE);
        }
    }

    return;
}

/* ****************************************************************************
* Function Name: `$INSTANCE_NAME`_SelectConfig
****************************************************************************//*
*
* \brief Selects the predefined configuration for scanning.
*
* \param config Number of configuration in the `$INSTANCE_NAME`.
*
* \param restart Set to 1u if the `$INSTANCE_NAME` should be  restarted after
* selecting the configuration.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SelectConfig(uint32_t config, uint32_t restart)
{
    /* Check whether the configuration number is valid or not */
    if(`$INSTANCE_NAME`_TOTAL_CONFIGS > config)
    {
        /* Stop the ADC before changing configurations */
        `$INSTANCE_NAME`_Stop();
        `$INSTANCE_NAME`_selected = 1u;

        if(0u == `$INSTANCE_NAME`_initVar)
        {
            `$INSTANCE_NAME`_Init();
            `$INSTANCE_NAME`_initVar |= `$INSTANCE_NAME`_INIT_VAR_INIT_FLAG;
        }
        #if (`$INSTANCE_NAME`_VREF_ROUTED)
            `$INSTANCE_NAME`_vrefAMux_DisconnectAll();
        #endif

        `$INSTANCE_NAME`_InitConfig(&`$INSTANCE_NAME`_allConfigs[config]);

        #if (`$INSTANCE_NAME`_VREF_ROUTED)
            `$INSTANCE_NAME`_vrefAMux_Select((uint8)config);
        #endif

        `$INSTANCE_NAME`_currentConfig = config;

        if(1u == restart)
        {
            /* Restart the ADC */
            `$INSTANCE_NAME`_Start();

            /* Restart the scan */
            `$INSTANCE_NAME`_StartConvert();
        }
    }
    return;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartConvert
****************************************************************************//**
*
* \brief In continuous mode, this API starts the conversion process and it runs
* continuously.

* In Single Shot mode, the function triggers a single scan and
* every scan requires a call of this function. The mode is set with the
* Sample Mode parameter in the customizer. The customizer setting can be
* overridden at run time with the `$INSTANCE_NAME`_SetConvertMode() function.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_StartConvert(void)
{
    if (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk == (`$INSTANCE_NAME`_SAR__HW->SAMPLE_CTRL & SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk))
    {
        Cy_SAR_StartConvert(`$INSTANCE_NAME`_SAR__HW, CY_SAR_START_CONVERT_CONTINUOUS);
    }
    else
    {
        Cy_SAR_StartConvert(`$INSTANCE_NAME`_SAR__HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetConvertMode
****************************************************************************//**
*
* \brief Sets the conversion mode to either Single-Shot or continuous. This
* function overrides the settings applied in the customizer. Changing
* configurations will restore the values set in the customizer.
*
* \param mode Sets the conversion mode.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetConvertMode(cy_en_sar_start_convert_sel_t mode)
{
    switch(mode)
    {
    case CY_SAR_START_CONVERT_CONTINUOUS:
        `$INSTANCE_NAME`_SAR__HW->SAMPLE_CTRL |= SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk;
        break;
    case CY_SAR_START_CONVERT_SINGLE_SHOT:
    default:
        `$INSTANCE_NAME`_SAR__HW->SAMPLE_CTRL &= ~SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk;
        break;
    }
}

/* ****************************************************************************
* Function Name: `$INSTANCE_NAME`_IRQ_Enable
****************************************************************************//*
*
* \brief Enables interrupts to occur at the end of a conversion. Global
* interrupts must also be enabled for the `$INSTANCE_NAME` interrupts to occur.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_IRQ_Enable(void){
    /* Interrupt core assignment will be up to the user. */
    #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM4_ASSIGNED
    #if (CY_CPU_CORTEX_M4)
        NVIC_EnableIRQ(`$INSTANCE_NAME`_IRQ_cfg.intrSrc);
    #endif
    #endif

    #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM0P_ASSIGNED
    #if (CY_CPU_CORTEX_M0P)
        NVIC_EnableIRQ(`$INSTANCE_NAME`_IRQ_cfg.intrSrc);
    #endif
    #endif
}

/* ****************************************************************************
* Function Name: `$INSTANCE_NAME`_IRQ_Disable
****************************************************************************//*
*
* \brief Disables end of conversion interrupts.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_IRQ_Disable(void){
    /* Interrupt core assignment will be up to the user. */
    #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM4_ASSIGNED
    #if (CY_CPU_CORTEX_M4)
        NVIC_DisableIRQ(`$INSTANCE_NAME`_IRQ_cfg.intrSrc);
    #endif
    #endif

    #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM0P_ASSIGNED
    #if (CY_CPU_CORTEX_M0P)
        NVIC_DisableIRQ(`$INSTANCE_NAME`_IRQ_cfg.intrSrc);
    #endif
    #endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetEosMask
****************************************************************************//**
*
* \brief Sets or clears the End of Scan (EOS) interrupt mask.
*
* \param mask 1 to set the mask, 0 to clear the mask.
*
* \return None
*
* \sideeffect All other bits in the INTR register are cleared by this function.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetEosMask(uint32_t mask)
{
    uint32_t intrMaskReg;

    intrMaskReg = (0uL == mask) ? CY_SAR_DEINIT : SAR_INTR_MASK_EOS_MASK_Msk;

    Cy_SAR_SetInterruptMask(`$INSTANCE_NAME`_SAR__HW, intrMaskReg);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetChanMask
****************************************************************************//*
*
* \brief Sets enable/disable mask for all channels in current configuration.
*
*
* \param enableMask
*  Channel enable/disable mask.
*
* \sideeffect
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetChanMask(uint32_t enableMask)
{
    uint32 chanCount = `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_currentConfig].numChannels;
    enableMask &= (uint32)((uint32)(1ul << chanCount) - 1ul);

    Cy_SAR_SetChanMask(`$INSTANCE_NAME`_SAR__HW, enableMask);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsEndConversion
****************************************************************************//**
*
* \brief Immediately returns the status of the conversion or does not return
* (blocking) until the conversion completes, depending on the retMode parameter.
* In blocking mode, there is a time out of about 10 seconds for a CPU speed of
* 100 Mhz.
*
* \param retMode Check conversion return mode.
*
* \return uint32_t: If a nonzero value is returned, the last conversion is complete.
* If the returned value is zero, the `$INSTANCE_NAME` is still calculating the last result.
*
* \sideeffect This function reads the end of conversion status, and clears it afterward.
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_IsEndConversion(cy_en_sar_return_mode_t retMode)
{
    uint32 endOfConversion = 0u;
    cy_en_sar_status_t result;

    result = Cy_SAR_IsEndConversion(`$INSTANCE_NAME`_SAR__HW, retMode);

    if (result == CY_SAR_SUCCESS)
    {
        endOfConversion = 1u;
    }

    return endOfConversion;
}

/* ****************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//*
*
* \brief Initialize the component according to parameters defined in the
* customizer.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32_t configNum = 0u;

    if(0u == `$INSTANCE_NAME`_initVar)
    {
        /* Interrupt core assignment will be up to the user. Initialize but do not enable the interrupt*/
        #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM4_ASSIGNED
        #if (CY_CPU_CORTEX_M4)
            (void)Cy_SysInt_Init(&`$INSTANCE_NAME`_IRQ_cfg, &`$INSTANCE_NAME`_ISR);
        #endif
        #endif

        #ifdef `$INSTANCE_NAME`_IRQ__INTC_CORTEXM0P_ASSIGNED
        #if (CY_CPU_CORTEX_M0P)
            (void)Cy_SysInt_Init(&`$INSTANCE_NAME`_IRQ_cfg, &`$INSTANCE_NAME`_ISR);
        #endif
        #endif

        /* Initialize configuration zero if SelectConfig has not been called */
        if(0u == `$INSTANCE_NAME`_selected)
        {
            `$INSTANCE_NAME`_selected = 1u;
            configNum = 0uL;

            /* Change Vref selection if is was routed by Creator. Break. */
            #if (`$INSTANCE_NAME`_VREF_ROUTED)
                `$INSTANCE_NAME`_vrefAMux_DisconnectAll();
            #endif

            `$INSTANCE_NAME`_InitConfig(&`$INSTANCE_NAME`_allConfigs[configNum]);

            /* Change Vref selection if is was routed by Creator. Make. */
            #if (`$INSTANCE_NAME`_VREF_ROUTED)
                `$INSTANCE_NAME`_vrefAMux_Select((uint8)configNum);
            #endif
        }
    }
}
/* [] END OF FILE */
