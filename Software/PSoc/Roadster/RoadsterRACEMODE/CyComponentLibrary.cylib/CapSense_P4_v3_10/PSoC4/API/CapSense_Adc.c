/***************************************************************************//**
* \file `$INSTANCE_NAME`_Adc.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides implementation for the ADC module of the CapSense 
*   component.
*
* \see CapSense P4 v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
*
*//*****************************************************************************
* Copyright (2016), Cypress Semiconductor Corporation.
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
#if !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    #include "`$INSTANCE_NAME`_Sensing.h"
#endif  /* !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */

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
* \if SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

static void `$INSTANCE_NAME`_SetNonDedicatedAdcChannel(uint8 chId, uint32 state);

/** \}
* \endif */

/*******************************************************************************
* Local definition
*******************************************************************************/
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_DONE   (1u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED (0u)
#define `$INSTANCE_NAME`_`$AdcModulePrefix`CAL_WATCHDOG_CYCLES_NUM   (0x0000FFFFLu)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`Start
    ****************************************************************************//**
    * \brief
    *   Configures the hardware and performs a calibration.
    *
    * \details
    *   Configures the hardware and performs a calibration.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_`$AdcModulePrefix`Start(void)
    {
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
    * Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`Sleep
    ****************************************************************************//**
    *
    * \brief
    *  Prepares the component to deep sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates, 
    *  this function shall be used to prepare the component to enter deep sleep.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_`$AdcModulePrefix`Sleep(void)
    {
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`Wakeup
    ****************************************************************************//**
    *
    * \brief
    *  This function resumes the component after sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates,
    *  this function shall be used to resume the component after exiting deep sleep.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_`$AdcModulePrefix`Wakeup(void)
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
        CY_SET_REG32(ptr2adcIO->hsiomPtr, (tmpVal \
            | (`$INSTANCE_NAME`_`$AdcModulePrefix`HSIOM_PRTSEL_AMUXBUSB << pinHSIOMShift)));
    
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
*   Configures the IDACB, internal switches, REFGEN, and HSCOMP.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ConfigAdcResources(void)
{   
    uint32 totalClkDiv;
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        `$INSTANCE_NAME`_`$AdcModulePrefix`SetModClkClockDivider(1uL);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_PERIOD_PTR, \
        3uL);
    #else
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_PERIOD_PTR, \
        `$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_SINGLEDIV);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
    /* Configure the IDAC */
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`CONFIG_DEFAULT );
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR, \
     `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG \
     | `$INSTANCE_NAME`_dsRam.adcIdac);
    /* Autozero time needs to be scaled down by clock dividers.
       Autozero time should be 5us. SEQ_TIME_DEFAULT is the duration assuming clk_sns = clk_hf.
       Actually, clk_sns = clk_hf/(csd_peri_div * sense_div) */ 
    totalClkDiv = ((CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_PERIOD_PTR) & 0xfffuL) + 1UL) \
        * (((CY_GET_REG32(`$INSTANCE_NAME`_ModClk__DIV_REGISTER)>>`$INSTANCE_NAME`_`$AdcModulePrefix`CLK16VAL_SHIFT)
        & `$INSTANCE_NAME`_`$AdcModulePrefix`CLK16_MASK) + 1UL);
    
    if(0u < (`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE / totalClkDiv))
    {
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_PTR, \
                (`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_BASE / totalClkDiv) - 1u);
    }
    else
    {
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_TIME_PTR, 0u);        
    }
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACA_PTR, 0ul);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`CSDCMP_PTR, 0ul);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_DSI_SEL_PTR, 0ul);
    
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_DUTY_PTR, 0ul);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_INIT_CNT_PTR, 1ul);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SEQ_NORM_CNT_PTR, 2ul);
    
    /* Configure the block-level routing */
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSP_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_HSN_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_PTR, \
        `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_P_SEL_PTR, \
        `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPP_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_N_SEL_PTR, \
        `$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMPN_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_MOD_SEL_PTR, \
        `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWMOD_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_TANK_SEL_PTR, \
        `$INSTANCE_NAME`_`$AdcModulePrefix`SW_FWTANK_DEFAULT);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_SEL_PTR, \
        `$INSTANCE_NAME`_`$AdcModulePrefix`SW_REFGEN_DEFAULT);

    /* Config RefGen.  The routing of the HS_N and AMUXBUF switches depend on RefGen. */
    #if (`$INSTANCE_NAME`_`$AdcModulePrefix`VDDA_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`LVTHRESH)

        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_LV);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUXBUF_SEL_PTR, \
            `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_LV);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_LV);
    #else
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_NORM);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUXBUF_SEL_PTR, \
            `$INSTANCE_NAME`_`$AdcModulePrefix`SW_AMUBUF_NORM);
    #endif /* `$INSTANCE_NAME`_`$AdcModulePrefix`VDDA_MV < `$INSTANCE_NAME`_`$AdcModulePrefix`LVTHRESH */
    
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
    uint32 totalClkDiv;
    uint32 tmpStartVal;
    /* Set the mode and aperture size. */
    totalClkDiv = ((CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SENSE_PERIOD_PTR) & 0xfffuL) + 1UL) \
        * (((CY_GET_REG32(`$INSTANCE_NAME`_ModClk__DIV_REGISTER)>>`$INSTANCE_NAME`_`$AdcModulePrefix`CLK16VAL_SHIFT)
        & `$INSTANCE_NAME`_`$AdcModulePrefix`CLK16_MASK) + 1UL);
    
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`ADC_CTL_PTR, (measureMode | \
                 ((`$INSTANCE_NAME`_`$AdcModulePrefix`MEASURE_APERTURE_BASE / totalClkDiv ) - 1u)));
    
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
        tmpStartVal = \
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
    if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_DONE == `$INSTANCE_NAME`_initVar)
    {
        /* If the FSM is running, shut it down. */
        if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus \
            & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
        {
            `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_OFF);
            `$INSTANCE_NAME`_SetAdcChannel((`$INSTANCE_NAME`_dsRam.adcStatus \
                & (uint8)(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_LASTCHAN_MASK)),
                                            `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT);
            `$INSTANCE_NAME`_dsRam.adcStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE;
        }
        
        /* Disable the subblocks. */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR, 0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`REFGEN_PTR, 0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`AMBUF_PTR,  0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`HSCMP_PTR,  0x0UL);
        
        /* Reset the block-level routing */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_P_SEL_PTR,    0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_HS_N_SEL_PTR,    0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_PTR,  0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR,     0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_P_SEL_PTR,   0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_CMP_N_SEL_PTR,   0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_MOD_SEL_PTR,  0x0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_FW_TANK_SEL_PTR, 0x0UL);
        
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
*  Initializes an analog-to-digital conversion on the selected channel.
*
* \details
*  Initializes an analog-to-digital conversion on the selected channel.
*
* \param chId 
*  The ID of the channel to be converted. 
*
* \return 
*  The function returns cystatus of its operation.
*    - CYRET_LOCKED - The CSD hardware is in-use by CapSense. No conversion started.
*    - CYRET_BAD_PARAM - The chId was out of bounds. No conversion started.
*    - CYRET_STARTED - The ADC is already converting. No conversion started.
*    - CYRET_SUCCESS - A conversion has started.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(uint8 chId)
{
    uint32 tmpStatus = CYRET_SUCCESS;
    
    /* If CapSense, try to Capture resources */
    #if !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    tmpStatus = `$INSTANCE_NAME`_AdcCaptureResources();

    if (CYRET_SUCCESS == tmpStatus)
    {
    #else /* Otherwise, configure resources if needed. */
    if (`$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_ConfigAdcResources();
    } 
    #endif /* !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
        if(chId >= `$INSTANCE_NAME`_ADC_TOTAL_CHANNELS)
        {
            tmpStatus = CYRET_BAD_PARAM;
        }
        if (CYRET_SUCCESS == tmpStatus)
        {
            if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
            {
                tmpStatus = CYRET_STARTED;
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
    #if !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN)
    }
    #endif /* !(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
    return tmpStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy
****************************************************************************//**
*
* \brief
*   The function returns the status of ADC's operation.
*
* \details
*   The function returns the status of ADC's operation.
*
* \return     
*  The function returns status of the ADC's operation.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE - The ADC is not in use.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CONVERTING - A conversion is 
*      in progress.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1 - The ADC is in the 
*      first phase (of 3) of calibration.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH2 - The ADC is in the 
*      second phase (of 3) of calibration.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH3 - The ADC is in the 
*      third phase (of 3) of calibration.
*    - `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_OVERFLOW - The most recent 
*      measurement caused an overflow.
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
*  The blocking function that starts a conversion, waits for the end of the 
*  conversion and returs the result. 
*
* \details
*  The blocking function that starts a conversion, waits for the end of the 
*  conversion and returs the result. 
*
* \param chId  
*  The ID of the channel to be measured 
*
* \return
*  The function returns voltage in millivolts or
*  `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BADCHANID if chId is invalid.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`ReadResult_mVolts(uint8 chId)
{
    uint16 tmpValue;
    (void) `$INSTANCE_NAME`_`$AdcModulePrefix`StartConvert(chId);
    while(`$INSTANCE_NAME`_`$AdcModulePrefix`IsBusy() != `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE)
    {
    }
    tmpValue = `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts(chId);
    return tmpValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts
****************************************************************************//**
*
* \brief
*  Returns the last valid result for the given channel.
*
* \details
*  Returns the last valid result for the given channel.
*
* \param chId  
*  The ID of the channel to be measured 
*
* \return     
*  The function returns voltage in mV or
*  `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BADCHANID if chId is invalid.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`GetResult_mVolts(uint8 chId)
{
    uint32 tmpRetVal = `$INSTANCE_NAME`_`$AdcModulePrefix`VALUE_BADCHANID;
    
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
*  Performs built-in calibration.
*
* \details
*  Performs built-in calibration.
*
* \return  
*  The function returns cystatus of its operation.
*    - CYRET_LOCKED    - The CSD hardware is in-use by CapSense, and could not be released.
*    - CYRET_SUCCESS   - The block is configured for ADC use.
*    - CYRET_STARTED   - Another ADC operation is in progress; this one was not completed.
*   
*******************************************************************************/
cystatus `$INSTANCE_NAME`_`$AdcModulePrefix`Calibrate(void)
{
    uint32 tmpStatus;
    uint32 watchdogAdcCounter;

    tmpStatus = `$INSTANCE_NAME`_AdcCaptureResources();
    if(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE != (`$INSTANCE_NAME`_dsRam.adcStatus \
        & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK) )
    {
        tmpStatus = CYRET_STARTED;
    }
    
    if (CYRET_SUCCESS == tmpStatus)
    {
        uint8 tmpFlashByte0;
        uint8 tmpFlashByte1;
        uint32 tmpVrefCal;
        #if (0u != CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1)
            tmpFlashByte0 = CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1);
            tmpFlashByte1 = CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM2);
            tmpVrefCal = (uint32)tmpFlashByte0 | (((uint32)tmpFlashByte1) << 8u);
            tmpVrefCal = (tmpVrefCal * (uint32)(`$INSTANCE_NAME`_ADC_VREF_MV)) \
                         / (uint32)(`$INSTANCE_NAME`_`$AdcModulePrefix`VREFCALIB_BASE);
            `$INSTANCE_NAME`_`$AdcModulePrefix`Vref_mV = (uint16)tmpVrefCal;
        #endif        
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR, \
                     `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG \
                     | `$INSTANCE_NAME`_dsRam.adcIdac);
        `$INSTANCE_NAME`_dsRam.adcStatus = (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET);
        `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF);

        /* Global CRC update */
        #if (`$INSTANCE_NAME`_ENABLE ==`$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
            `$INSTANCE_NAME`_DsUpdateGlobalCrc();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */
    }
    
    /* Initialize Watchdog Counter with time interval which is enough to ADC clibration is completed */
    watchdogAdcCounter = `$INSTANCE_NAME`_`$AdcModulePrefix`CAL_WATCHDOG_CYCLES_NUM;
    while (((*(volatile uint8 *)&`$INSTANCE_NAME`_dsRam.adcStatus & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK) \
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
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`Stop
****************************************************************************//**
*
* \brief
*   Disables the CSD sub-blocks that are in use while in the ADC mode, and frees 
*   the routing.
*
* \details
*   Disables the CSD sub-blocks that are in use while in the ADC mode, and frees 
*   the routing.
*
*******************************************************************************/
void `$INSTANCE_NAME`_`$AdcModulePrefix`Stop(void)
{
    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN)
        (void) `$INSTANCE_NAME`_AdcReleaseResources();
    #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_ADC_STANDALONE_EN) */
    `$INSTANCE_NAME`_initVar = `$INSTANCE_NAME`_`$AdcModulePrefix`INIT_NEEDED;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`Resume
****************************************************************************//**
*
* \brief
*   Resumes the ADC Component after a Stop call.
*
* \details
*   Resumes the ADC Component after a Stop call.
*
*******************************************************************************/
void `$INSTANCE_NAME`_`$AdcModulePrefix`Resume(void)
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
