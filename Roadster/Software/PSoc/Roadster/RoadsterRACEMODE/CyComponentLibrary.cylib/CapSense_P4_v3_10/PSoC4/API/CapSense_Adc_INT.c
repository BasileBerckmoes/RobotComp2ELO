/***************************************************************************//**
* \file `$INSTANCE_NAME`_Adc_INT.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file contains the source code for implementation of the CapSense 
*   component ADC functionality Interrupt Service Routine (ISR).
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
#include "cytypes.h"
#include "cyfitter.h"
#include "`$INSTANCE_NAME`_Adc.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

extern uint16 `$INSTANCE_NAME`_`$AdcModulePrefix`Vref_mV;

/**
* \if SECTION_ADC_INTERRUPT
* \addtogroup group_capsense_interrupt
* \{
*/

#if (`$INSTANCE_NAME`_ADC_EN)    
    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_`$AdcModulePrefix`IntrHandler
****************************************************************************//**
*
* \brief
*   This is an internal ISR function for ADC implementation.
*
* \details
*   This ISR is triggered after a measurement completes or during calibration
*   phases.
*   
*   To use the entry or exit callbacks, define
*   `$INSTANCE_NAME`_ADC_[ENTRY|EXIT]_CALLBACK
*   and define the corresponding function, `$INSTANCE_NAME`_`$AdcModulePrefix`[Entry|Exit]Callback().
*
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_`$AdcModulePrefix`IntrHandler)
{
    static uint16 tVssa2Vref;
    static uint16 tRecover;
    static uint16 tVdda2Vref;
    static uint16 vdda_mV;
    
    #ifdef `$INSTANCE_NAME`_`$AdcModulePrefixMacro`ENTRY_CALLBACK
        `$INSTANCE_NAME`_`$AdcModulePrefix`EntryCallback();
    #endif /* `$INSTANCE_NAME`_`$AdcModulePrefixMacro`ENTRY_CALLBACK */

    /* Un-request the interrupt. */
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET);
    CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_CLEAR);
    
    /* ADC could have been converting or calibrating; handle each differently. */
    if (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CONVERTING == (`$INSTANCE_NAME`_dsRam.adcStatus
        & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
    {
        uint32 tmpResult;
        uint32 polarity;
        uint16 t_full = tVssa2Vref + tVdda2Vref;
        uint16 RES_MAX = (uint16)(1uL << `$INSTANCE_NAME`_ADC_RESOLUTION) - 1u;
        uint8 tmpChId = `$INSTANCE_NAME`_dsRam.adcStatus \
            & (uint8)(`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_LASTCHAN_MASK);
        
        /* Get entire register */
        tmpResult = CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_PTR);
        /* Get just polarity bit */
        polarity = (tmpResult & `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_HSCMPPOL_MASK);
        /* Get just counts */
        tmpResult &= `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_VALUE_MASK;
        
        /* HSCMP polarity is 0:sink, 1:source */
        if(0UL != polarity) /* Sourcing */
        {
            /* Saturate result at tVssa2Vref */
            tmpResult = (tmpResult > tVssa2Vref) ? tVssa2Vref : tmpResult;
            /* Scale result to Resolution range */
            tmpResult = ((tVssa2Vref - tmpResult) * RES_MAX) / t_full;
        }
        else /* Sinking */
        {
            #if (0 == `$INSTANCE_NAME`_ADC_MEASURE_MODE)
                /* Scale result with sink/source mismatch*/
                tmpResult = ((2uL * tRecover) * tmpResult) / tVssa2Vref;
                /* Saturate result at t_Vdda2Vref*/
                tmpResult = (tmpResult > tVdda2Vref) ? tVdda2Vref : tmpResult;
                /* Scale result to Resolution range */
                tmpResult = ((tVssa2Vref + tmpResult) * RES_MAX)
                            / t_full;
            #else
                /* In vref mode, we are not supposed to be sinking. Saturate */
                tmpResult = (tVssa2Vref * RES_MAX) / t_full;
            #endif
        }
        /* Scale result by max voltage and store it*/
        tmpResult = (vdda_mV * tmpResult) / RES_MAX;
        `$INSTANCE_NAME`_dsRam.adcResult[tmpChId] = (uint16)(tmpResult);
        
        /* Put adc in waiting state */
        `$INSTANCE_NAME`_SetAdcChannel(tmpChId, `$INSTANCE_NAME`_`$AdcModulePrefix`CHAN_DISCONNECT);
        `$INSTANCE_NAME`_dsRam.adcStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE;
    }
    else if (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1 == (`$INSTANCE_NAME`_dsRam.adcStatus \
        & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
    {
        tVssa2Vref = (uint16)(CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_PTR) \
        & `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_VALUE_MASK);
        #if (0 == `$INSTANCE_NAME`_ADC_MEASURE_MODE)
            /* In normal mode, continue calibrating to get > Vref measurements */
            `$INSTANCE_NAME`_dsRam.adcStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH2;
            CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR, \
                `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET);
            `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREFBY2);
        #else
            /* In Vref mode, calibration is done, set upper range to 0 and 
               voltage range to Vref */
            tVdda2Vref = 0;
            vdda_mV = `$INSTANCE_NAME`_`$AdcModulePrefix`Vref_mV;
            `$INSTANCE_NAME`_dsRam.adcStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE;
        #endif
    }
    else if (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH2 == (`$INSTANCE_NAME`_dsRam.adcStatus \
        & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
    {
        tRecover = (uint16)(CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_PTR) \
        & `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_VALUE_MASK);
        /* Disconnect amuxbusB, Connect VDDA to csdbusB */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR, 0UL);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_PTR, \
            `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_VDDA2CSDBUSB);
        
        `$INSTANCE_NAME`_dsRam.adcStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH3;
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET);
        `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VIN);
        
    }
    else if (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH3 == (`$INSTANCE_NAME`_dsRam.adcStatus \
        & `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_FSM_MASK))
    {
        uint16 tFull;
        uint16 targetTFull = (uint16)(1uL << (`$INSTANCE_NAME`_ADC_RESOLUTION + 2u));
        /* Reconnect amuxbusB, disconnect VDDA */
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_SEL_PTR,
            `$INSTANCE_NAME`_`$AdcModulePrefix`SW_SHIELD_DEFAULT);
        CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_SEL_PTR, 
            `$INSTANCE_NAME`_`$AdcModulePrefix`SW_BYP_DEFAULT);
                
        /* Get counts from Vdda */
        tVdda2Vref = (uint16)(CY_GET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_PTR) \
        & `$INSTANCE_NAME`_`$AdcModulePrefix`ADC_RES_VALUE_MASK);
        /* Calibrate tVdda2Vref with Sink/Source mismatch*/
        tVdda2Vref = ((2u * tVdda2Vref) * tRecover) / tVssa2Vref;
        /*Test whether the full range is 2-bits higher than adc resolution */
        tFull = (tVssa2Vref + tVdda2Vref);
        if ((tFull < targetTFull) && (`$INSTANCE_NAME`_dsRam.adcIdac != 1u))
        {
            /* Scale Idac down, integer arithmetic guarantees it will be equal or lower than ratio */
            uint8 targetIdac = (uint8)((`$INSTANCE_NAME`_dsRam.adcIdac * tFull) / targetTFull);
            targetIdac = (targetIdac > 0u) ? targetIdac : 1u;
            `$INSTANCE_NAME`_dsRam.adcIdac = targetIdac;
            CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_PTR, \
                         `$INSTANCE_NAME`_`$AdcModulePrefix`IDACB_CONFIG \
                         | `$INSTANCE_NAME`_dsRam.adcIdac);
            /* Recalibrate with new idac. */
            `$INSTANCE_NAME`_dsRam.adcStatus = (`$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_CALIBPH1);
            CY_SET_REG32(`$INSTANCE_NAME`_`$AdcModulePrefix`INTR_MASK_PTR, `$INSTANCE_NAME`_`$AdcModulePrefix`INTERRUPT_SET);
            `$INSTANCE_NAME`_StartAdcFSM(`$INSTANCE_NAME`_`$AdcModulePrefix`MEASMODE_VREF);
        }
        else
        {
            `$INSTANCE_NAME`_dsRam.adcStatus = `$INSTANCE_NAME`_`$AdcModulePrefix`STATUS_IDLE;
            vdda_mV = `$INSTANCE_NAME`_`$AdcModulePrefix`Vref_mV + ((`$INSTANCE_NAME`_`$AdcModulePrefix`Vref_mV * tVdda2Vref) / tVssa2Vref);
        }
    }
    /* If interrupt is called without defined ADC state, do nothing. */
    else{}
    
    #ifdef `$INSTANCE_NAME`_`$AdcModulePrefixMacro`EXIT_CALLBACK
        `$INSTANCE_NAME`_`$AdcModulePrefix`ExitCallback();
    #endif /* `$INSTANCE_NAME`_`$AdcModulePrefixMacro`EXIT_CALLBACK */
}


#endif /* `$INSTANCE_NAME`_ADC_EN */

/** \}
 * \endif */

 
/* [] END OF FILE */
