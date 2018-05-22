/***************************************************************************//**
* \file `$INSTANCE_NAME`_Adc.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides implementation for the ADC module of the `$INSTANCE_NAME`
*   Component.
*
* \see `$INSTANCE_NAME` v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
*
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/
#include "syslib/cy_syslib.h"
#include <stddef.h>
#include "gpio/cy_gpio.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    #include "syspm/cy_syspm.h"
    #include "cyfitter_sysint_cfg.h"
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
#include "`$INSTANCE_NAME`_ModClk.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Adc.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #include "`$INSTANCE_NAME`_SelfTest.h"
#endif

#if (`$INSTANCE_NAME`_ADC_EN)

static uint8 `$INSTANCE_NAME`_initVar;
uint16 `$INSTANCE_NAME`_adcVrefMv = `$INSTANCE_NAME`_ADC_VREF_MV;


/*******************************************************************************
* Module local function declarations
*******************************************************************************/
/**
* \cond SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    static void `$INSTANCE_NAME`_SsIsrInitialize(cy_israddress address);
    static cy_en_syspm_status_t `$INSTANCE_NAME`_SwitchPowerModeCallback(cy_stc_syspm_callback_params_t *callbackParams);
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

/** \}
* \endcond */

/*******************************************************************************
* Local definition
*******************************************************************************/
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_DONE                    (1u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED                  (0u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CAL_WATCHDOG_CYCLES_NUM      (0x0000FFFFLu)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_Start
    ****************************************************************************//**
    * \if SECTION_STANDALONE_ADC
    * \brief
    *   Configures the hardware and performs calibration.
    *
    * \details
    *   Configures the hardware and performs calibration.
    * \endif
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_Start(void)
    {
        `$INSTANCE_NAME`_ClearAdcChannels();

        if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_DONE != `$INSTANCE_NAME`_initVar)
        {
            `$INSTANCE_NAME`_`$AdcModulePrefix`DsInitialize();
        }
        `$INSTANCE_NAME`_ConfigAdcResources();
        (void) `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate();
        while(`$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy() != `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE)
        {
        }
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_Sleep
    ****************************************************************************//**
    * \if SECTION_STANDALONE_ADC
    * \brief
    *  Prepares the Component for deep sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates,
    *  this function will be used to prepare the Component to enter deep sleep.
    * \endif
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_Sleep(void)
    {
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_Wakeup
    ****************************************************************************//**
    * \if SECTION_STANDALONE_ADC
    * \brief
    *  This function resumes the Component after sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates,
    *  this function will be used to resume the Component after exiting deep sleep.
    * \endif
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_Wakeup(void)
    {
    }
#endif  /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetNonDedicatedAdcChannel
****************************************************************************//**
*
* \brief
*   Sets the non dedicated channel to the given state.
*
* \details
*   Connects/disconnects the pin and the analog muxbus B. Sets the drive mode
*   of the pin as well.
*
* \param chId  The ID of the non dedicated channel to be set.
* \param state The state in which the channel is to be put:
*         - (0) `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT
*         - (1) `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(uint8 chId, uint32 state)
{
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ptr2adcIO;
    uint32  interruptState;

    ptr2adcIO = &`$INSTANCE_NAME`_adcIoList[chId];
    interruptState = Cy_SysLib_EnterCriticalSection();
    switch (state)
    {
    case `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT:
        /* Connect AMuxBusB to the selected port */
        Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)ptr2adcIO->pcPtr, (uint32)ptr2adcIO->pinNumber, (en_hsiom_sel_t)HSIOM_SEL_AMUXB);
        /* Update port configuration register (drive mode) to HiZ Analog */
        Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)ptr2adcIO->pcPtr, (uint32)ptr2adcIO->pinNumber, CY_GPIO_DM_ANALOG);
        break;

    /* Disconnection is a safe default state. Fall-through is intentional. */
    case `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT:
    default:
        /* Disconnec AMuxBusB from the selected port */
        Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)ptr2adcIO->pcPtr, (uint32)ptr2adcIO->pinNumber, (en_hsiom_sel_t)HSIOM_SEL_GPIO);
        break;
    }
    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAdcChannel
****************************************************************************//**
*
* \brief
*   Sets the given channel to the given state.
*
* \details
*   Connects/disconnects the pin and the analog muxbus B.  Sets the drive mode
*   of the pin as well.
*
* \param chId  The ID of the channel to be set.
* \param state The state in which the channel is to be put:
*         - (0) `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT
*         - (1) `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetAdcChannel(uint8 chId, uint32 state)
{
    #if (0u != `$INSTANCE_NAME`_ADC_AMUXB_INPUT_EN)
        #if (`$INSTANCE_NAME`_ADC_MIN_CHANNELS < `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS)
            if(`$INSTANCE_NAME`_ADC_SELECT_AMUXB_CH != chId)
            {
                `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(chId, state);
            }
        #endif /* (`$INSTANCE_NAME`_ADC_MIN_CHANNELS < `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS) */
    #else
        `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(chId, state);
    #endif /* (0u != `$INSTANCE_NAME`_ADC_AMUXB_INPUT_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ConfigAdcResources
****************************************************************************//**
*
* \brief
*   Configures the CSD block to be used as an ADC.
*
* \details
*   Configures the IDACB, internal switches, REFGEN, HSCOMP, enables CSD
*   block interrupt and set interrupt vector to ADC sensing method.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConfigAdcResources(void)
{
    uint32 interruptState;
    uint32 newRegValue;

    /* Configure clocks */
    `$INSTANCE_NAME`_ModClk_SetDivider(`$INSTANCE_NAME`_ADC_MODCLK_DIV_DEFAULT - 1u);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_PERIOD_PTR, (`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT - 1u));

    /* Configure the IDAC */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACB_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG | `$INSTANCE_NAME`_dsRam.adcIdac);

    /* Configure AZ Time */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_TIME_PTR, (`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_DEFAUL - 1u));

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR, 0ul);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_DSI_SEL_PTR, 0ul);

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_DUTY_PTR, 0ul);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_INIT_CNT_PTR, 1ul);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_PTR, 2ul);

    /* Configure the block-level routing */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSP_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSN_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPP_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPN_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWMOD_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWTANK_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_DEFAULT);

    interruptState = Cy_SysLib_EnterCriticalSection();
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR);
    newRegValue |= `$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_DEFAULT;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR, newRegValue);
    Cy_SysLib_ExitCriticalSection(interruptState);

    /* Config RefGen */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_NORM);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_PTR,
            `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_NORM);

    /* Configure HSCOMP */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_AZ_DEFAULT);

    /* Enable CSD block interrupt and set interrupt vector to ADC sensing method */
    `$INSTANCE_NAME`_SsIsrInitialize(&`$INSTANCE_NAME`_`$AdcModulePrefix`IntrHandler);

    /* Component is initialized */
    `$INSTANCE_NAME`_initVar = `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_DONE;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartAdcFSM
****************************************************************************//**
*
* \brief
*   Starts the CSD state machine with correct parameters to initialize an ADC
*   conversion.
*
* \details
*   Starts the CSD state machine with correct parameters to initialize an ADC
*   conversion.
*
* \param measureMode The FSM mode:
*        - (0) `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_OFF
*        - (1) `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF
*        - (2) `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREFBY2
*        - (3) `$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VIN
*
*******************************************************************************/
void `$INSTANCE_NAME`_StartAdcFSM(uint32 measureMode)
{
    uint32 tmpStartVal;

    /* Set the mode and acquisition time */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_ADC_CTL_PTR, (measureMode | (`$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_BASE - 1u)));

    if(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF == measureMode)
    {
        tmpStartVal =
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZSKIP_DEFAULT    |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSIIGNORE   |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_NOABORT     |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQMODE     |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_START;
    }
    else if (`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_OFF == measureMode)
    {
        tmpStartVal = `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_ABORT;
    }
    /* This setting is used for both MEASMODE_VREFBY2 and MEASMODE_VIN */
    else
    {
        tmpStartVal =
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_AZSKIP_DEFAULT    |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_DSIIGNORE   |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_NOABORT     |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_SEQMODE     |
            `$INSTANCE_NAME`_`$AdcModulePrefix`FSMSETTING_START;
    }

    /* Enable HSComp */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, tmpStartVal);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AdcCaptureResources
****************************************************************************//**
*
* \brief
*   Releases CSD resources from sensing mode, and sets it into ADC mode.
*
* \details
*   Releases CSD resources from sensing mode, and sets it into ADC mode.
*
* \return     The function returns cy_status of its operation.
*   - CY_RET_LOCKED  - The sensing hardware is in-use and could not be released.
*   - CY_RET_SUCCESS - Block is configured for ADC use.
*
*******************************************************************************/
cy_status `$INSTANCE_NAME`_AdcCaptureResources(void)
{
    cy_status tmpStatus = CY_RET_SUCCESS;

    #if !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        tmpStatus = `$INSTANCE_NAME`_SsReleaseResources();

        if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED == `$INSTANCE_NAME`_initVar)
        {
            if(CY_RET_SUCCESS == tmpStatus)
            {
                `$INSTANCE_NAME`_ConfigAdcResources();
            }
            else
            {
                tmpStatus = CY_RET_LOCKED;
            }
        }
    #else
        if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED == `$INSTANCE_NAME`_initVar)
        {
            `$INSTANCE_NAME`_ConfigAdcResources();
        }
    #endif  /* !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

    return tmpStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AdcReleaseResources
****************************************************************************//**
*
* \brief
*   Releases CSD resources from ADC mode.
*
* \details
*   Releases CSD resources from ADC mode.
*
* \return     The function returns cy_status of its operation.
*   CY_RET_SUCCESS   Block resources no longer in use.
*
*******************************************************************************/
cy_status `$INSTANCE_NAME`_AdcReleaseResources(void)
{
    uint32 interruptState;
    uint32 newRegValue;

    if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_DONE == `$INSTANCE_NAME`_initVar)
    {
        /* If the FSM is running, shut it down. */
        if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus
                            & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
        {
            `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_OFF);
            `$INSTANCE_NAME`_SetAdcChannel((`$INSTANCE_NAME`_dsRam.adcStatus
                            & (uint8)(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_LASTCHAN_MASK)),
                            `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT);
            `$INSTANCE_NAME`_dsRam.adcStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE;
        }

        /* Disable the subblocks. */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACB_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_AMBUF_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, 0u);

        /* Reset the block-level routing */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR, 0u);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR, 0u);

        interruptState = Cy_SysLib_EnterCriticalSection();
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR);
        newRegValue &= (uint32)(~`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_DEFAULT);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR, newRegValue);
        Cy_SysLib_ExitCriticalSection(interruptState);

         /* Disconnect all ADC channels */
        `$INSTANCE_NAME`_ClearAdcChannels();

        `$INSTANCE_NAME`_initVar = `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED;
    }

    return CY_RET_SUCCESS;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert
****************************************************************************//**
*
* \brief
*  Initializes the hardware and initiates an analog-to-digital conversion on the
*  selected input channel.
*
* \details
*  Initializes the hardware and initiates an analog-to-digital conversion on the
*  selected input channel. This API only initiates a conversion and does not
*  wait for the conversion to be completed, therefore the
*  `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy() API must be used to check the
*  status and ensure that the conversion is complete prior to reading the result,
*  starting a new conversion with the same or a different channel or reconfiguring
*  the hardware for different functionality.
*
* \param chId
*  The ID of the channel to be converted.
*
* \return
*  The function returns cystatus of its operation.
*    - CY_RET_SUCCESS - A conversion has started.
*    - CY_RET_LOCKED - The hardware is already in-use by a previously initialized
*      conversion or other functionality. No new conversion is started by this API.
*    - CY_RET_BAD_PARAM - An invalid channel Id. No conversion is started.
*
*******************************************************************************/
cy_status `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(uint8 chId)
{
    uint32 tmpStatus = CY_RET_SUCCESS;

    /* If non-standalone ADC, try to Capture resources */
    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        tmpStatus = `$INSTANCE_NAME`_AdcCaptureResources();

        if (CY_RET_SUCCESS == tmpStatus)
        {
    #else /* Otherwise, configure resources if needed. */
        if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED == `$INSTANCE_NAME`_initVar)
        {
            `$INSTANCE_NAME`_ConfigAdcResources();
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

    if(chId >= `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS)
    {
        tmpStatus = CY_RET_BAD_PARAM;
    }
    
    if (CY_RET_SUCCESS == tmpStatus)
    {
        if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
        {
            tmpStatus = CY_RET_LOCKED;
        }

        if(CY_RET_SUCCESS == tmpStatus)
        {
            #if(`$INSTANCE_NAME`_ADC_ANALOG_STARTUP_DELAY_US > 0uL)
                Cy_SysLib_DelayUs(`$INSTANCE_NAME`_ADC_ANALOG_STARTUP_DELAY_US);
            #endif /* (`$INSTANCE_NAME`_ADC_ANALOG_STARTUP_DELAY_US > 0uL) */

            /* Set Component Status */
            `$INSTANCE_NAME`_dsRam.adcStatus = (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CONVERTING | chId);

            /* Configure a desired channel if needed */
            if (chId != `$INSTANCE_NAME`_dsRam.adcActiveCh)
            {
                if (`$INSTANCE_NAME`_`$AdcModulePrefix`NO_CHANNEL != `$INSTANCE_NAME`_dsRam.adcActiveCh)
                {
                    /* Disconnect existing channel */
                    `$INSTANCE_NAME`_SetAdcChannel(`$INSTANCE_NAME`_dsRam.adcActiveCh, `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT);
                }
                /* Connect desired input */
                `$INSTANCE_NAME`_SetAdcChannel(chId, `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT);
                `$INSTANCE_NAME`_dsRam.adcActiveCh = chId;
            }

            /* Un-mask ADC_RES interrupt (enable interrupt) */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_MASK_PTR, `$INSTANCE_NAME`_CSD_INTR_MASK_ADC_RES_MSK);
            `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VIN);
        }
    }
    
    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
    
    return tmpStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy
****************************************************************************//**
*
* \brief
*   The function returns the status of the ADC's operation.
*
* \details
*   The function returns the status of the ADC's operation. A new conversion or
*   calibration must not be started unless the ADC is in the IDLE state.
*
* \return
*  The function returns the status of the ADC's operation.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE - The ADC is not busy,
*       a new conversion can be initiated.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CONVERTING - A previously
*       initiated conversion is in progress.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1 - The ADC is in the
*      first phase (of 3) of calibration.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH2 - The ADC is in the
*      second phase (of 3) of calibration.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH3 - The ADC is in the
*      third phase (of 3) of calibration.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_OVERFLOW - The most recent
*      measurement caused an overflow. The root cause of the overflow may be
*      the previous calibration values being invalid or the VDDA setting in cydwr
*      and hardware do not match. Perform re-calibration or set the
*      appropriate VDDA value in cydwr to avoid this error condition.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy(void)
{
    uint8 tmpStatus;

    if (0u != (`$INSTANCE_NAME`_CSD_ADC_RES_REG & `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_OVERFLOW_MASK))
    {
        tmpStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_OVERFLOW;
    }
    else
    {
        tmpStatus = (uint8)((*(volatile uint8 *)&`$INSTANCE_NAME`_dsRam.adcStatus) & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK);
    }

    return tmpStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`ReadResult_mVolts
****************************************************************************//**
*
* \brief
*  This is a blocking API. It initiates a conversion, waits for completion and
*  returns the result.
*
* \details
*  This is a blocking API. Internally, it starts a conversion using
*  `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(), checks the status using
*  `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy(), waits until the conversion is
*  completed and returns the result.
*
* \param chId
*  The ID of the channel to be measured
*
* \return
*  The function returns voltage in millivolts or
*  `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_RESULT if:
*   - chId is invalid
*   - The ADC conversion is not started
*   - The ADC conversion watch-dog triggered.
*******************************************************************************/
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`ReadResult_mVolts(uint8 chId)
{
    cy_status convertStatus;
    uint16 tmpValue;
    uint32 watchdogAdcCounter;

    convertStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(chId);
    if (CY_RET_SUCCESS == convertStatus)
    {
        /* Initialize Watchdog Counter with time interval which is enough to ADC conversion is completed */
        watchdogAdcCounter = `$INSTANCE_NAME`_`$AdcModulePrefix`CAL_WATCHDOG_CYCLES_NUM;
        while ((`$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy() != `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE) &&
               (0u != watchdogAdcCounter))
        {
            /* Wait until conversion complete and decrement Watchdog Counter to prevent unending loop */
            watchdogAdcCounter--;
        }
        if (0u != watchdogAdcCounter)
        {
            tmpValue = `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts(chId);
        }
        else
        {
            tmpValue = (uint16) `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_RESULT;
        }
    }
    else
    {
        tmpValue = (uint16) `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_RESULT;
    }

    return tmpValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts
****************************************************************************//**
*
* \brief
*  This API does not perform an ADC conversion and returns the last valid result
*  for the specified channel.
*
* \details
*  Returns the last valid result from the data structure for the specified channel.
*  This function can be used to read a previous result of any channel even if the
*  ADC is busy or a conversion is in progress. However, it is highly recommended
*  not to use this function with a channel that is in an active conversion.
*
* \param chId
*  The ID of the channel to be measured
*
* \return
*  The function returns a voltage in millivolts or
*  `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_CHAN_ID if chId is invalid.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts(uint8 chId)
{
    uint32 tmpRetVal = `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_CHAN_ID;

    if(chId < `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS)
    {
        tmpRetVal = `$INSTANCE_NAME`_dsRam.adcResult[chId];
    }
    return (uint16)tmpRetVal;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate
****************************************************************************//**
*
* \brief
*  Performs calibration of the ADC module.
*
* \details
*  Performs calibration for the ADC to identify the appropriate hardware configuration
*  to produce accurate results. It is recommended to run the calibration
*  periodically (for example every 10 seconds) for accuracy and compensations.
*
* \return
*  The function returns cystatus of its operation.
*    - CY_RET_SUCCESS - The block is configured for the ADC use.
*    - CY_RET_LOCKED - The hardware is already in-use by a previously initialized
*      conversion or other functionality. No new conversion is started by this API.
*
*******************************************************************************/
cy_status `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate(void)
{
    uint32 tmpStatus;
    uint32 watchdogAdcCounter;
    uint32 tmpVrefCal;

    tmpStatus = `$INSTANCE_NAME`_AdcCaptureResources();

    if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus
        & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
    {
        tmpStatus = CY_RET_LOCKED;
    }

    if (CY_RET_SUCCESS == tmpStatus)
    {
        #if(`$INSTANCE_NAME`_ADC_ANALOG_STARTUP_DELAY_US > 0uL)
            Cy_SysLib_DelayUs(`$INSTANCE_NAME`_ADC_ANALOG_STARTUP_DELAY_US);
        #endif /* (`$INSTANCE_NAME`_ADC_ANALOG_STARTUP_DELAY_US > 0uL) */

        /* Disconnect a channel if connected */
        if (`$INSTANCE_NAME`_`$AdcModulePrefix`NO_CHANNEL != `$INSTANCE_NAME`_dsRam.adcActiveCh)
        {
            `$INSTANCE_NAME`_SetAdcChannel(`$INSTANCE_NAME`_dsRam.adcActiveCh, `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT);
            `$INSTANCE_NAME`_dsRam.adcActiveCh = `$INSTANCE_NAME`_`$AdcModulePrefix`NO_CHANNEL;
        }
        
        /* Get Vref trim-value */
        tmpVrefCal = (`$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_REG & `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MSK) >>
            `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_POS;

        /* Update nominal Vref to real Vref */
        tmpVrefCal *= `$INSTANCE_NAME`_ADC_VREF_MV;
        tmpVrefCal /= `$INSTANCE_NAME`_`$AdcModulePrefix`VREF_CALIB_USED;

        `$INSTANCE_NAME`_adcVrefMv = (uint16)tmpVrefCal;

        /* Calculate deviation of trim register */
        if (tmpVrefCal > `$INSTANCE_NAME`_ADC_VREF_MV)
        {
            tmpVrefCal = tmpVrefCal - `$INSTANCE_NAME`_ADC_VREF_MV;
        }
        else
        {
            tmpVrefCal = `$INSTANCE_NAME`_ADC_VREF_MV - tmpVrefCal;
        }
        tmpVrefCal = (tmpVrefCal * `$INSTANCE_NAME`_PERCENTAGE_100) / `$INSTANCE_NAME`_ADC_VREF_MV;

        /* Use nominal Vref if trim-value is not within the allowed range */
        if (`$INSTANCE_NAME`_`$AdcModulePrefix`VREF_TRIM_MAX_DEVIATION < tmpVrefCal)
        {
            `$INSTANCE_NAME`_adcVrefMv = `$INSTANCE_NAME`_ADC_VREF_MV;
        }

        `$INSTANCE_NAME`_dsRam.adcIdac = (uint8)`$INSTANCE_NAME`_ADC_IDAC_DEFAULT;
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACB_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG |
                                                     `$INSTANCE_NAME`_dsRam.adcIdac);

        `$INSTANCE_NAME`_dsRam.adcStatus = (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1);

        /* Un-mask ADC_RES interrupt (enable interrupt) */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_MASK_PTR, `$INSTANCE_NAME`_CSD_INTR_MASK_ADC_RES_MSK);
        `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
            /* Global CRC update */
            #if (`$INSTANCE_NAME`_ENABLE ==`$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
                `$INSTANCE_NAME`_DsUpdateGlobalCrc();
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */

        /* Initialize Watchdog Counter with time interval which is enough to ADC calibration is completed */
        watchdogAdcCounter = `$INSTANCE_NAME`_`$AdcModulePrefix`CAL_WATCHDOG_CYCLES_NUM;
        while (((*(volatile uint8 *)&`$INSTANCE_NAME`_dsRam.adcStatus & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK)
                != 0u) &&  (0u != watchdogAdcCounter))
        {
            /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
            watchdogAdcCounter--;
        }
    }

    return tmpStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`Initialize
****************************************************************************//**
*
* \brief
*   Configures the hardware to ADC mode and begins a calibration.
*
* \details
*   Configures the hardware to ADC mode and begins a calibration.
*
*******************************************************************************/
void `$INSTANCE_NAME`_`$AdcModulePrefix`Initialize(void)
{
    `$INSTANCE_NAME`_ConfigAdcResources();
    (void)`$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcCapSensePrefix`Stop
****************************************************************************//**
*
* \brief
*   Disables the hardware sub-blocks that are in use while in the ADC mode,
*   and frees the routing.
*
* \details
*   This function stops the Component operation. No ADC conversion can be
*   initiated when the Component is stopped. Once stopped, the hardware block
*   may be reconfigured by the application program for any other special usage.
*   The ADC operation can be resumed by calling the
*   `$INSTANCE_NAME`_`$AdcCapSensePrefix`Resume() function or the Component can
*   be reset by calling the `$INSTANCE_NAME`_Start() function.
*   This function is called when no ADC conversion is in progress.
*
*******************************************************************************/
void `$INSTANCE_NAME`_`$AdcCapSensePrefix`Stop(void)
{
    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        (void)`$INSTANCE_NAME`_AdcReleaseResources();
    #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
    `$INSTANCE_NAME`_initVar = `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcCapSensePrefix`Resume
****************************************************************************//**
*
* \brief
*   Resumes the ADC operation after a stop call.
*
* \details
*   Resumes the ADC operation if the operation is stopped
*   previously by the `$INSTANCE_NAME`_`$AdcCapSensePrefix`Stop() API.
*
*******************************************************************************/
void `$INSTANCE_NAME`_`$AdcCapSensePrefix`Resume(void)
{
    `$INSTANCE_NAME`_`$AdcModulePrefix`Initialize();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearAdcChannels
****************************************************************************//**
*
* \brief
*  Resets all the ADC channels to disconnected state.
*
* \details
*   The function goes through all the ADC channels and disconnects the pin
*   and the analog muxbus B.  Sets the drive mode of the pin as well.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearAdcChannels(void)
{
    uint32 chId;

    for (chId = 0u; chId < `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS; chId++)
    {
        `$INSTANCE_NAME`_SetAdcChannel((uint8)chId, `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT);
    }
    `$INSTANCE_NAME`_dsRam.adcActiveCh = `$INSTANCE_NAME`_`$AdcModulePrefix`NO_CHANNEL;
}

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsIsrInitialize
****************************************************************************//**
*
* \brief
*   Enables and initializes for the function pointer for a callback for the ISR.
*
* \details
*   The  "address" is a special type cy_israddress defined by syslib. This function
*   is used by Component APIs and should not be used by an application program for
*   proper working of the Component.
*
* \param  address The address of the function to be called when interrupt is fired.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SsIsrInitialize(cy_israddress address)
{
    /* Disable interrupt */
    #if defined(`$INSTANCE_NAME`_ISR__INTC_ASSIGNED)
        NVIC_DisableIRQ(`$INSTANCE_NAME`_ISR_cfg.intrSrc);
    #endif

    /* Configure interrupt with priority and vector */
    #if defined(`$INSTANCE_NAME`_ISR__INTC_ASSIGNED)
        (void)Cy_SysInt_Init(&`$INSTANCE_NAME`_ISR_cfg, address);
    #endif

    /* Enable interrupt */
    #if defined(`$INSTANCE_NAME`_ISR__INTC_ASSIGNED)
        NVIC_EnableIRQ(`$INSTANCE_NAME`_ISR_cfg.intrSrc);
    #endif
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DeepSleepCallback
****************************************************************************//**
*
* \brief
*  Handles Active to DeepSleep power mode transition for the `$INSTANCE_NAME`
*  Component.
*
* \details
*  This API is registered with system power mode using Cy_SysPm_RegisterCallback()
*  function with CY_SYSPM_DEEPSLEEP type. After registration, this API is called by
*  Cy_SysPm_DeepSleep() to prepare or to check a status of the `$INSTANCE_NAME`
*  Component prior the core entering into DeepSleep power mode. 
*
*  Calling this function directly from the application layer is not recommended.
*
*  When this API is called with the mode parameter set to CY_SYSPM_CHECK_READY,
*  the function returns CY_SYSPM_SUCCESS if no scanning is in progress, otherwise 
*  CY_SYSPM_FAIL is returned that means that device cannot enter into DeepSleep 
*  power mode without finishing the current scan that is in progress (transition 
*  to DeepSleep power mode during the scan can disrupt a sensor scan result and 
*  produce an unexpected behavior after wakeup).
*
* \param callbackParams
*  Refer to the description of the cy_stc_syspm_callback_params_t type.
*
* \return
*  Returns the status of the operation requested by the mode parameter:
*  CY_SYSPM_SUCCESS  - DeepSleep power mode can be entered.
*  CY_SYSPM_FAIL     - DeepSleep power mode cannot be entered.
*
*******************************************************************************/
cy_en_syspm_status_t `$INSTANCE_NAME`_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams)
{
    return(`$INSTANCE_NAME`_SwitchPowerModeCallback(callbackParams));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnterLowPowerCallback
****************************************************************************//**
*
* \brief
*  Handles Active to Low Power Active (LPActive) power mode transition for 
*  the `$INSTANCE_NAME` Component.
*
* \details
*  This API is registered with system power mode using Cy_SysPm_RegisterCallback()
*  function with CY_SYSPM_ENTER_LP_MODE type. After registration, this API is called by
*  Cy_SysPm_EnterLpMode() to prepare or to check a status of the `$INSTANCE_NAME`
*  Component prior the core entering into LPActive power mode. 
*
*  Calling this function directly from the application layer is not recommended.
*
*  When this API is called with the mode parameter set to CY_SYSPM_CHECK_READY,
*  the function returns CY_SYSPM_SUCCESS if no scanning is in progress, otherwise 
*  CY_SYSPM_FAIL is returned that means that device cannot enter into LPActive 
*  power mode without finishing the current scan that is in progress (transition 
*  to LPActive power mode during the scan can disrupt a sensor scan result and 
*  produce an unexpected behavior).
*
* \param callbackParams
*  Refer to the description of the cy_stc_syspm_callback_params_t type.
*
* \return
*  Returns the status of the operation requested by the mode parameter:
*  CY_SYSPM_SUCCESS  - LPActive power mode can be entered.
*  CY_SYSPM_FAIL     - LPActive power mode cannot be entered.
*
*******************************************************************************/
cy_en_syspm_status_t `$INSTANCE_NAME`_EnterLowPowerCallback(cy_stc_syspm_callback_params_t *callbackParams)
{
    return(`$INSTANCE_NAME`_SwitchPowerModeCallback(callbackParams));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ExitLowPowerCallback
****************************************************************************//**
*
* \brief
*  Handles Low Power Active (LPActive) to Active power mode transition for 
*  the `$INSTANCE_NAME` Component.
*
* \details
*  This API is registered with system power mode using Cy_SysPm_RegisterCallback()
*  function with CY_SYSPM_EXIT_LP_MODE type. After registration, this API is called by
*  Cy_SysPm_ExitLpMode() to prepare or to check a status of the `$INSTANCE_NAME`
*  Component prior the core exiting from LPActive power mode. 
*
*  Calling this function directly from the application layer is not recommended.
*
*  When this API is called with the mode parameter set to CY_SYSPM_CHECK_READY,
*  the function returns CY_SYSPM_SUCCESS if no scanning is in progress, otherwise 
*  CY_SYSPM_FAIL is returned that means that device cannot exit LPActive 
*  power mode without finishing the current scan that is in progress (transition 
*  from LPActive to Active power mode during the scan can disrupt a sensor scan 
*  result and produce an unexpected behavior).
*
* \param callbackParams
*  Refer to the description of the cy_stc_syspm_callback_params_t type.
*
* \return
*  Returns the status of the operation requested by the mode parameter:
*  CY_SYSPM_SUCCESS  - Active power mode can be entered.
*  CY_SYSPM_FAIL     - Active power mode cannot be entered.
*
*******************************************************************************/
cy_en_syspm_status_t `$INSTANCE_NAME`_ExitLowPowerCallback(cy_stc_syspm_callback_params_t *callbackParams)
{
    return(`$INSTANCE_NAME`_SwitchPowerModeCallback(callbackParams));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SwitchPowerModeCallback
****************************************************************************//**
*
* \brief
*  Handles the switching power mode for the `$INSTANCE_NAME` Component.
*
* \details
*  This function handles swithing of system power mode.
*  When this API is called with the mode parameter set to CY_SYSPM_CHECK_READY,
*  the function returns CY_SYSPM_SUCCESS if no scanning is in progress, otherwise 
*  CY_SYSPM_FAIL is returned that means that device cannot switch power mode 
*  without finishing the current scan that is in progress (switching power mode 
*  during the scan can disrupt a sensor scan result and produce an unexpected
*  behavior).
*
* \param callbackParams
*  Refer to the description of the cy_stc_syspm_callback_params_t type.
*
* \return
*  Returns the status of the operation requeted by mode parameter:
*  CY_SYSPM_SUCCESS  - Switching power mode can be done
*  CY_SYSPM_FAIL     - Switching power mode cannot be done.
*
*******************************************************************************/
static cy_en_syspm_status_t `$INSTANCE_NAME`_SwitchPowerModeCallback(cy_stc_syspm_callback_params_t *callbackParams)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    uint8 temp;

    switch(callbackParams->mode)
    {
    case (CY_SYSPM_CHECK_READY):
        temp = `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy();
        if ((`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != temp) &&
            (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_OVERFLOW != temp))
        {
            /* Scanning in progress */
            retVal = CY_SYSPM_FAIL;
        }
        break;

    default:
        break;
    }

    return(retVal);
}

#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

#endif /* #if `$INSTANCE_NAME`_ADC_EN */


/* [] END OF FILE */
