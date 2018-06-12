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
#include <cytypes.h>
#include "CyLib.h"

#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Adc.h"
#include "`$INSTANCE_NAME`_ISR.h"

#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    #include "`$INSTANCE_NAME`_Sensing.h"
#endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #include "`$INSTANCE_NAME`_SelfTest.h"
#endif

#if (`$INSTANCE_NAME`_ADC_EN)

static uint8 `$INSTANCE_NAME`_initVar;
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`Vref_mV = `$INSTANCE_NAME`_ADC_VREF_MV;

/*******************************************************************************
* Module local function declarations
*******************************************************************************/

/**
* \cond SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

static void `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(uint8 chId, uint32 state);
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    void `$INSTANCE_NAME`_`$AdcModulePrefix`SetModClkClockDivider(uint32 modClk);
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

/** \}
* \endcond */

/*******************************************************************************
* Local definition
*******************************************************************************/
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_DONE   (1u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED (0u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CAL_WATCHDOG_CYCLES_NUM   (0x0000FFFFLu)

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
    *  this function shall be used to prepare the Component to enter deep sleep.
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
    *  this function shall be used to resume the Component after exiting deep sleep.
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
static void `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(uint8 chId, uint32 state)
{
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ptr2adcIO;
    uint32 newRegisterValue;
    uint8  interruptState;
    uint32 pinHSIOMShift;
    uint32 pinModeShift;
    uint32 tmpVal;

    ptr2adcIO = &`$INSTANCE_NAME`_adcIoList[chId];
    pinHSIOMShift = (uint32)ptr2adcIO->hsiomShift;
    pinModeShift = (uint32)ptr2adcIO->shift;
    
    /* Clear port connections. */
    tmpVal = CY_GET_REG32(ptr2adcIO->hsiomPtr);
    tmpVal &= ~(`$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_MASK << pinHSIOMShift);
    
    interruptState = CyEnterCriticalSection();

    switch (state)
    {
    case `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT:
        
        /* Connect AMuxBusB to the selected port. */
        CY_SET_REG32(ptr2adcIO->hsiomPtr, (tmpVal | (`$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_AMUXBUSB << pinHSIOMShift)));
    
        /* Update port configuration register (drive mode) to HiZ output, buffered input */
        newRegisterValue = CY_GET_REG32(ptr2adcIO->pcPtr);
        newRegisterValue &= ~(`$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_MASK << pinModeShift);
        newRegisterValue |= (`$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_INPUT << pinModeShift);
        CY_SET_REG32(ptr2adcIO->pcPtr, newRegisterValue);
    
        /* Cmod and Ctank are not typical GPIO, require CSD setting. */
        if (0u != ((uint32)(ptr2adcIO->hsiomPtr) & `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PORT_MASK))
        {
            if (`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CTANK_PINSHIFT == pinModeShift)
            {
                CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_SEL_PTR, \
                    `$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_CTANK);  
            }
            else if (`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PINSHIFT == pinModeShift)
            {
                CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_SEL_PTR, \
                    `$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_CMOD);  
            }
            else { /* No action */ }
        }
        break;
        
    /* Disconnection is a safe default state. Fall-through is intentional. */
    case `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT:
    default:
        /* tmpVal contains cleared hsiom state. */
        CY_SET_REG32(ptr2adcIO->hsiomPtr, tmpVal);
    
        /* Update port configuration register (drive mode) to HiZ input/output by clearing PC*/
        newRegisterValue = CY_GET_REG32(ptr2adcIO->pcPtr);
        newRegisterValue &= ~(`$INSTANCE_NAME`_`$AdcModulePrefix`GPIO_PC_MASK << pinModeShift);
        CY_SET_REG32(ptr2adcIO->pcPtr, newRegisterValue);
        
        /* Cmod and Ctank are not typical GPIO, require CSD setting. */
        if (0u != ((uint32)(ptr2adcIO->hsiomPtr) & `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PORT_MASK))
        {
            if ((`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CTANK_PINSHIFT == pinModeShift) ||
                (`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMOD_PINSHIFT == pinModeShift ))
            {
                CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_SEL_PTR, 0u);  
            }
        }
        break;
    }

    CyExitCriticalSection(interruptState);
    
    /* Set logic 0 to port data register */
    tmpVal = CY_GET_REG32(ptr2adcIO->drPtr);
    tmpVal &= (uint32)~(uint32)((uint32)1u << ptr2adcIO->drShift);
    CY_SET_REG32(ptr2adcIO->drPtr, tmpVal);
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
        if(`$INSTANCE_NAME`_ADC_SELECT_AMUXB_CH != chId)
        {
            `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(chId, state);
        }
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
    uint8  interruptState;
    uint32 newRegValue;

    /* Configure clocks */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        `$INSTANCE_NAME`_`$AdcModulePrefix`SetModClkClockDivider(`$INSTANCE_NAME`_ADC_MODCLK_DIV_DEFAULT);
    #else
        `$INSTANCE_NAME`_SsSetModClkClockDivider(`$INSTANCE_NAME`_ADC_MODCLK_DIV_DEFAULT);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_PERIOD_PTR, (`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DIV_DEFAULT - 1u));

    /* Configure the IDAC */
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG | `$INSTANCE_NAME`_dsRam.adcIdac);

    /* Configure AZ Time */
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_PTR, (uint32)(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_DEFAUL - 1u));

    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`CSDCMP_PTR, 0);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_SEL_PTR, 0);
    
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DUTY_PTR, 0);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_INIT_CNT_PTR, 1u);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_NORM_CNT_PTR, 2u);
    
    /* Configure the block-level routing */
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSP_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSN_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPP_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPN_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_MOD_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWMOD_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWTANK_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_DEFAULT);

    interruptState = CyEnterCriticalSection();
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR);
    newRegValue |= `$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_DEFAULT;
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR, newRegValue);
    CyExitCriticalSection(interruptState);
    
    /* Config RefGen.  The routing of the HS_N and AMUXBUF switches depend on RefGen. */
    #if (`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`LVTHRESH)

        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_LV);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_LV);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_LV);
    #else
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_NORM);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_NORM);
    #endif /* `$INSTANCE_NAME`__CYDEV_VDDA_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`LVTHRESH */
    
    /* Configure HSCOMP */
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_AZ_DEFAULT);
    
    /* Set the ISR vector */
    `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_`$AdcModulePrefix`IntrHandler);
    
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
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`ADC_CTL_PTR, (measureMode | (`$INSTANCE_NAME`_`$AdcModulePrefix`ACQUISITION_BASE - 1u)));
    
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
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_START_PTR, tmpStartVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AdcCaptureResources
****************************************************************************//**
*
* \brief
*   Releases CSD resources from CapSense mode, and sets it into ADC mode.
*
* \details
*   Releases CSD resources from CapSense mode, and sets it into ADC mode.
*
* \return     The function returns cystatus of its operation.
*   - CYRET_LOCKED  - The CSD hardware is in-use by CapSense, and could not be released.
*   - CYRET_SUCCESS - Block is configured for ADC use.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_AdcCaptureResources(void)
{
    cystatus tmpStatus = CYRET_SUCCESS;

    #if !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        tmpStatus = `$INSTANCE_NAME`_SsReleaseResources();

        if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED == `$INSTANCE_NAME`_initVar)
        {
            if(CYRET_SUCCESS == tmpStatus) 
            {
                `$INSTANCE_NAME`_ConfigAdcResources();
            }
            else
            {
                tmpStatus = CYRET_LOCKED;
            }
        }
    #else
        if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED == `$INSTANCE_NAME`_initVar)
        {
            `$INSTANCE_NAME`_ConfigAdcResources();
        } 
    #endif /* !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

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
* \return     The function returns cystatus of its operation.
*   CYRET_SUCCESS   Block resources no longer in use.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_AdcReleaseResources(void)
{
    uint8  interruptState;
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
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR, 0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_PTR, 0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_PTR,  0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_PTR,  0);
        
        /* Reset the block-level routing */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_P_SEL_PTR,    0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_N_SEL_PTR,    0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_PTR,  0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_P_SEL_PTR,   0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_N_SEL_PTR,   0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_MOD_SEL_PTR,  0);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_TANK_SEL_PTR, 0);
        
    
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR);
        newRegValue &= (uint32)(~`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_DEFAULT);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR, newRegValue);
        CyExitCriticalSection(interruptState);
        
         /* Disconnect all ADC channels */
        `$INSTANCE_NAME`_ClearAdcChannels();
        
        `$INSTANCE_NAME`_initVar = `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED;
    }
    
    return CYRET_SUCCESS;
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
*  starting a new conversion with the same or a different channel, or reconfiguring
*  the hardware for different functionality. 
*
* \param chId 
*  The ID of the channel to be converted. 
*
* \return 
*  The function returns cystatus of its operation.
*    - CYRET_SUCCESS - A conversion has started.
*    - CYRET_LOCKED - The hardware is already in-use by a previously initialized 
*      conversion or other functionality. No new conversion is started by this API.
*    - CYRET_BAD_PARAM - An invalid channel Id. No conversion is started.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(uint8 chId)
{
    uint32 tmpStatus = CYRET_SUCCESS;
    
    /* If CapSense, try to Capture resources */
    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        tmpStatus = `$INSTANCE_NAME`_AdcCaptureResources();

        if (CYRET_SUCCESS == tmpStatus)
        {
    #else /* Otherwise, configure resources if needed. */
        if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED == `$INSTANCE_NAME`_initVar)
        {
            `$INSTANCE_NAME`_ConfigAdcResources();
        } 
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
    
        if(chId >= `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS)
        {
            tmpStatus = CYRET_BAD_PARAM;
        }
        if (CYRET_SUCCESS == tmpStatus)
        {
            if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
            {
                tmpStatus = CYRET_LOCKED;
            }
            
            if(CYRET_SUCCESS == tmpStatus)
            {
                /* Set Component Status */
                `$INSTANCE_NAME`_dsRam.adcStatus = (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CONVERTING | chId);
                
                /* Connect desired input */
                `$INSTANCE_NAME`_SetAdcChannel(chId, `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_CONNECT);
                    
                /* Set interrupt request */
                CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET);
                `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VIN);
            }
        }
    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        }
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
    
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
*	   the previous calibration values being invalid or the VDDA setting in cydwr 
*      and hardware do not match. Perform re-calibration or set the
*	   appropriate VDDA value in cydwr to avoid this error condition.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy(void)
{
    uint8 tmpStatus;
    if (0u != (`$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_REG & `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_OVERFLOW_MASK))
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
*  The function returns voltage in milli-volts or
*  `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BAD_RESULT if:
*   - chId is invalid
*   - the ADC conversion is not started
*   - the ADC conversion watch-dog triggered.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`ReadResult_mVolts(uint8 chId)
{
    cystatus convertStatus;
    uint16 tmpValue;
    uint32 watchdogAdcCounter;

    convertStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(chId);
    if (CYRET_SUCCESS == convertStatus)
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
*  The function returns a voltage in milli-volts or
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
*    - CYRET_SUCCESS - The block is configured for the ADC use.
*    - CYRET_LOCKED - The hardware is already in-use by a previously initialized 
*      conversion or other functionality. No new conversion is started by this API.
*   
*******************************************************************************/
cystatus `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate(void)
{
    uint32 tmpStatus;
    uint32 watchdogAdcCounter;
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CALIBRATE_VREF)
        uint8 tmpFlashByte0;
        uint8 tmpFlashByte1;
        uint32 tmpVrefCal;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CALIBRATE_VREF) */

    tmpStatus = `$INSTANCE_NAME`_AdcCaptureResources();
    if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus
        & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK) )
    {
        tmpStatus = CYRET_LOCKED;
    }
    
    if (CYRET_SUCCESS == tmpStatus)
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CALIBRATE_VREF)
            tmpFlashByte0 = CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1);
            tmpFlashByte1 = CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM2);
            tmpVrefCal = (uint32)tmpFlashByte0 | (((uint32)tmpFlashByte1) << 8u);
            tmpVrefCal = (tmpVrefCal * (uint32)(`$INSTANCE_NAME`_ADC_VREF_MV)) \
                         / (uint32)(`$INSTANCE_NAME`_`$AdcModulePrefix`VREFCALIB_BASE);
            `$INSTANCE_NAME`_`$AdcModulePrefix`Vref_mV = (uint16)tmpVrefCal;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CALIBRATE_VREF) */

        `$INSTANCE_NAME`_dsRam.adcIdac = (uint8)`$INSTANCE_NAME`_ADC_IDAC_DEFAULT;
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG \
                     | `$INSTANCE_NAME`_dsRam.adcIdac);
        
        `$INSTANCE_NAME`_dsRam.adcStatus = (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET);
        `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF);

        /* Global CRC update */
        #if (`$INSTANCE_NAME`_ENABLE ==`$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
            `$INSTANCE_NAME`_DsUpdateGlobalCrc();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */
    }
    
    /* Initialize Watchdog Counter with time interval which is enough to ADC calibration is completed */
    watchdogAdcCounter = `$INSTANCE_NAME`_`$AdcModulePrefix`CAL_WATCHDOG_CYCLES_NUM;
    while (((*(volatile uint8 *)&`$INSTANCE_NAME`_dsRam.adcStatus & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK)
            != 0u) &&  (0u != watchdogAdcCounter))
    {
        /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
        watchdogAdcCounter--;
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
    (void) `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate();
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
*   This function stops the Component operation, no ADC conversion can be 
*   initiated when the Component is stopped. Once stopped, the hardware block
*   may be reconfigured by the application program for any other special usage. 
*   The ADC operation can be resumed by calling the 
*   `$INSTANCE_NAME`_`$AdcCapSensePrefix`Resume() function or the Component can
*   be reset by calling the `$INSTANCE_NAME`_Start() function. 
*   This function should be called when no ADC conversion is in progress.
*
*******************************************************************************/
void `$INSTANCE_NAME`_`$AdcCapSensePrefix`Stop(void)
{
    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        (void) `$INSTANCE_NAME`_AdcReleaseResources();
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
*   This function resumes the ADC operation if the operation is stopped 
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
}

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`SetModClkClockDivider
    ****************************************************************************//**
    *
    * \brief
    *   Sets the divider values for the modulator clock and then starts
    *   the modulator clock.
    *
    * \details
    *   It is not recommended to call this function directly by the application layer.
    *   It is used by initialization to enable the clocks.
    *
    * \param
    *   modClk The divider value for the modulator clock.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_`$AdcModulePrefix`SetModClkClockDivider(uint32 modClk)
    {
        /*  Stop modulator clock   */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_PTR,
                     ((uint32)`$INSTANCE_NAME`_ModClk__DIV_ID <<
                     `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_DIV_SHIFT)|
                     ((uint32)`$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_DISABLE_MASK));

        /*
         * Set divider value for sense modClk.
         * 1u is subtracted from modClk because Divider register value 0 corresponds
         * to dividing by 1.
         */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_DIV_PTR, ((modClk - 1u) << 8u));

        /*  Check whether previous modulator clock start command has finished. */
        while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_PTR) & `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_ENABLE_MASK))
        {
            /*  Wait until previous modulator clock start command has finished. */
        }

        /*  Start modulator clock, aligned to HFCLK */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_PTR,
                     (uint32)(((uint32)`$INSTANCE_NAME`_ModClk__DIV_ID << `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_DIV_SHIFT) |
                      ((uint32)`$INSTANCE_NAME`_ModClk__PA_DIV_ID << `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_PA_DIV_SHIFT) |
                      `$INSTANCE_NAME`_`$AdcModulePrefix`MODCLK_CMD_ENABLE_MASK));
    }
#endif /* `$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN */

#endif  /* #if `$INSTANCE_NAME`_ADC_EN */  


/* [] END OF FILE */
