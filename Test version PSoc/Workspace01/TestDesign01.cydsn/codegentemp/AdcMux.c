/*******************************************************************************
* File Name: AdcMux.c
* Version 2.0
*
* Description:
*  This file provides the API functionality of the ADC SAR Sequencer Component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "AdcMux.h"
#if(AdcMux_IRQ_REMOVE == 0u)
    #include "AdcMux_IRQ.h"
#endif   /* End AdcMux_IRQ_REMOVE */

int16  AdcMux_finalArray[AdcMux_NUMBER_OF_CHANNELS];
uint32 AdcMux_initVar = 0u;
static uint8 AdcMux_tempChan;
static uint8 AdcMux_finalChan;
static uint8 AdcMux_tempTD = CY_DMA_INVALID_TD;
static uint8 AdcMux_finalTD = CY_DMA_INVALID_TD;


/****************************************************************************
* Function Name: AdcMux_Disable()
*****************************************************************************
*
* Summary:
*  Disables the component without disabling the ADC SAR.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
****************************************************************************/
void AdcMux_Disable(void)
{
    AdcMux_CONTROL_REG &= ((uint8)(~AdcMux_BASE_COMPONENT_ENABLE));

    (void) CyDmaChDisable(AdcMux_tempChan);
    CyDmaTdFree(AdcMux_tempTD);
    AdcMux_tempTD = CY_DMA_INVALID_TD;

    (void) CyDmaChDisable(AdcMux_finalChan);
    CyDmaTdFree(AdcMux_finalTD);
    AdcMux_finalTD = CY_DMA_INVALID_TD;
}


/*******************************************************************************
* Function Name: AdcMux_Init
********************************************************************************
*
* Summary:
*  Inits channels for DMA transfer. Provides loading period to the AMUX address
*  selection counter
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void AdcMux_Init(void)
{
    /* Init DMA, 2 bytes bursts, each burst requires a request */
    AdcMux_tempChan = AdcMux_TempBuf_DmaInitialize(AdcMux_TEMP_BYTES_PER_BURST,
        AdcMux_REQUEST_PER_BURST, (uint16)(HI16(CYDEV_PERIPH_BASE)), (uint16)(HI16(CYDEV_SRAM_BASE)));

    /* Init DMA, (AdcMux_NUMBER_OF_CHANNELS << 1u) bytes bursts, each burst requires a request */
    AdcMux_finalChan = AdcMux_FinalBuf_DmaInitialize((uint8)AdcMux_FINAL_BYTES_PER_BURST,
        AdcMux_REQUEST_PER_BURST, (uint16)(HI16(CYDEV_SRAM_BASE)), (uint16)(HI16(CYDEV_SRAM_BASE)));

    #if(AdcMux_IRQ_REMOVE == 0u)
        /* Set the ISR to point to the AdcMux_IRQ Interrupt. */
        AdcMux_IRQ_SetVector(&AdcMux_ISR);
        /* Set the priority. */
        AdcMux_IRQ_SetPriority((uint8)AdcMux_INTC_NUMBER);
    #endif   /* End AdcMux_IRQ_REMOVE */

}


/*******************************************************************************
* Function Name: AdcMux_Enable
********************************************************************************
*
* Summary:
*  Enables DMA channels, address selection counter and FSM of Base component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void AdcMux_Enable(void)
{
    uint8 enableInterrupts;

    static int16 AdcMux_tempArray[AdcMux_NUMBER_OF_CHANNELS];
    
    (void)CyDmaClearPendingDrq(AdcMux_tempChan);
    (void)CyDmaClearPendingDrq(AdcMux_finalChan);
    
    
    /* Provides initialization procedure for the TempBuf DMA
    * Configure this Td as follows:
    *  - The TD is looping on itself
    *  - Increment the destination address, but not the source address
    */

    if (AdcMux_tempTD == DMA_INVALID_TD)
    {
        AdcMux_tempTD = CyDmaTdAllocate();
    }

    (void) CyDmaTdSetConfiguration(AdcMux_tempTD, AdcMux_TEMP_TRANSFER_COUNT,
        AdcMux_tempTD, ((uint8)AdcMux_TempBuf__TD_TERMOUT_EN | (uint8)TD_INC_DST_ADR));

    /* From the SAR to the TempArray */
    (void) CyDmaTdSetAddress(AdcMux_tempTD, (uint16)(LO16((uint32)AdcMux_SAR_DATA_ADDR_0)),
        (uint16)(LO16((uint32)AdcMux_tempArray)));

    /* Associate the TD with the channel */
    (void) CyDmaChSetInitialTd(AdcMux_tempChan, AdcMux_tempTD);


    /* Provides initialization procedure for the FinalBuf DMA
    * Configure this Td as follows:
    *  - The TD is looping on itself
    *  - Increment the source and destination address
    */

    if (AdcMux_finalTD == DMA_INVALID_TD)
    {
        AdcMux_finalTD = CyDmaTdAllocate();
    }
    
    (void) CyDmaTdSetConfiguration(AdcMux_finalTD, (AdcMux_FINAL_BYTES_PER_BURST),
        AdcMux_finalTD, ((uint8)(AdcMux_FinalBuf__TD_TERMOUT_EN) | (uint8)TD_INC_SRC_ADR |
            (uint8)TD_INC_DST_ADR));

    /* From the the TempArray to Final Array */
    (void) CyDmaTdSetAddress(AdcMux_finalTD, (uint16)(LO16((uint32)AdcMux_tempArray)),
        (uint16)(LO16((uint32)AdcMux_finalArray)));

    /* Associate the TD with the channel */
    (void) CyDmaChSetInitialTd(AdcMux_finalChan, AdcMux_finalTD);
    
    (void) CyDmaChEnable(AdcMux_tempChan, 1u);
    (void) CyDmaChEnable(AdcMux_finalChan, 1u);

    /* Enable Counter and give Enable pulse to set an address of the last channel */
    enableInterrupts = CyEnterCriticalSection();
    AdcMux_CYCLE_COUNTER_AUX_CONTROL_REG |= ((uint8)(AdcMux_CYCLE_COUNTER_ENABLE));
    CyExitCriticalSection(enableInterrupts);

    /* Enable FSM of the Base Component */
    AdcMux_CONTROL_REG |= ((uint8)(AdcMux_BASE_COMPONENT_ENABLE));
    AdcMux_CONTROL_REG |= ((uint8)(AdcMux_LOAD_COUNTER_PERIOD));

    #if(AdcMux_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(AdcMux_INTC_NUMBER);
    #endif   /* End AdcMux_IRQ_REMOVE */
}


/*******************************************************************************
* Function Name: AdcMux_Start
********************************************************************************
*
* Summary:
*  Starts component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  If the initVar variable is already set, this function only calls the 
*  AdcMux_Enable() function
*
* Reentrant:
*  No.
*
*******************************************************************************/
void AdcMux_Start(void)
{
    if(AdcMux_initVar == 0u)
    {
        AdcMux_Init();
        AdcMux_initVar = 1u;
    }

    AdcMux_Enable();
    AdcMux_SAR_Start();
    (void) CY_GET_REG8(AdcMux_STATUS_PTR);

}


/*******************************************************************************
* Function Name: AdcMux_Stop
********************************************************************************
*
* Summary:
*  Stops component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void AdcMux_Stop(void)
{
    AdcMux_SAR_Stop();
    AdcMux_Disable();
}

#if(AdcMux_SAMPLE_MODE != AdcMux_SAMPLE_MODE_HW_TRIGGERED)

    /*******************************************************************************
    * Function Name: AdcMux_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  When the Sample Mode parameter is set to 'Free Running', the component will
    * operate in a continuous mode. The channels will be scanned continuously until
    * _StopConvert()or  _Stop() is called
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Calling AdcMux_StartConvert() disables the external SOC pin.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void AdcMux_StartConvert(void)
    {
        #if(AdcMux_SAMPLE_MODE != AdcMux_SAMPLE_MODE_FREE_RUNNING)

            AdcMux_CONTROL_REG |= ((uint8)(AdcMux_SOFTWARE_SOC_PULSE));

        #else

            AdcMux_SAR_StartConvert();

        #endif /*
                 #if(AdcMux_SAMPLE_MODE !=
                 AdcMux_SAMPLE_MODE_FREE_RUNNING)
               */
    }


    /*******************************************************************************
    * Function Name: AdcMux_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the component to stop all conversions
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  In free-running and software trigger mode, this function sets a software 
    *  version of the SOC to low level and switches the SOC source to hardware SOC 
    *  input (Hardware trigger).
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void AdcMux_StopConvert(void)
    {
        AdcMux_SAR_StopConvert();
    }

#endif /* AdcMux_SAMPLE_MODE != AdcMux_SAMPLE_MODE_HW_TRIGGERED */


/*******************************************************************************
* Function Name: AdcMux_IsEndConversion
********************************************************************************
*
* Summary:
*  Checks for ADC end of conversion for the case one channel and end of scan
*  for the case of multiple channels
*
* Parameters:
*  retMode: Check conversion return mode
*   Values:
*         - AdcMux_RETURN_STATUS      - Immediately returns the 
*                                                 status
*         - AdcMux_WAIT_FOR_RESULT    - Does not return a result 
*                                                 until the conversion 
*                                                 is complete
*
* Return:
*  If a nonzero value is returned, the last conversion is complete. If the 
*  returned value is zero, the ADC_SAR_Seq is still calculating the last result
*
* Side Effects:
*  This function reads the end of conversion status, which is cleared on read
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32 AdcMux_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
      status = AdcMux_STATUS_REG;
    } while ((status == 0u) && (retMode == AdcMux_WAIT_FOR_RESULT));

    return((uint32)status);
}


/*******************************************************************************
* Function Name: AdcMux_GetResult16
********************************************************************************
*
* Summary:
*  Returns the ADC result for channel chan
*
* Parameters:
*  chan: The ADC channel in which to return the result. The first channel is 0 
*        and the last channel is the total number of channels - 1
*
* Return:
*  Returns converted data as a signed 16-bit integer
*
* Side Effects:
*  Converts the ADC counts to the 2's complement form
*
* Reentrant:
*  No.
*
*******************************************************************************/
int16 AdcMux_GetResult16(uint16 chan)
{
    return (AdcMux_finalArray[AdcMux_GET_RESULT_INDEX_OFFSET - chan] - AdcMux_SAR_shift);
}


/*******************************************************************************
* Function Name: AdcMux_GetAdcResult
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA register, not the results buffer
*
* Parameters:
*  None.
*
* Return:
*  The last ADC conversion result
*
* Side Effects:
*  Converts the ADC counts to the 2's complement form
*
* Reentrant:
*  No.
*
*******************************************************************************/
int16 AdcMux_GetAdcResult(void)
{
    return (AdcMux_SAR_GetResult16());
}


/*******************************************************************************
* Function Name: AdcMux_SetOffset
********************************************************************************
*
* Summary:
*  Sets the ADC offset which is used by the functions _CountsTo_uVolts(),
*  _CountsTo_mVolts() and _CountsTo_Volts() to substract the offset from the
*  given reading before calculating the voltage conversion
*
* Parameters:
*  offset: This value is measured when the inputs are shorted or connected to
*  the same input voltage
*
* Return:
*  None.
*
* Side Effects:
*  Affects AdcMux_CountsTo_Volts(), 
*  AdcMux_CountsTo_mVolts(), and AdcMux_CountsTo_uVolts() 
*  by subtracting the given offset.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void AdcMux_SetOffset(int32 offset)
{
    AdcMux_SAR_SetOffset((int16)offset);
}


/*******************************************************************************
* Function Name: AdcMux_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*  This function does not affect the actual conversion with PSoC5 ES1 silicon.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC_SAR_Seq resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  AdcMux_StopConvert(), change the resolution, then restart the
*  conversions with AdcMux_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use AdcMux_IsEndConversion() to wait until conversion is 
*  complete  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  AdcMux_SetResolution() is called before data is valid again.
*  Affects AdcMux_CountsTo_Volts(), AdcMux_CountsTo_mVolts(), 
*  and AdcMux_CountsTo_uVolts() by calculating the correct conversion 
*  between ADC counts and the applied input voltage. Calculation depends on 
*  resolution, input range, and voltage reference.
*
*******************************************************************************/
void AdcMux_SetResolution(uint8 resolution)
{
    AdcMux_SAR_SetResolution(resolution);
}


/*******************************************************************************
* Function Name: AdcMux_SetGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per volt for the voltage conversion
*
* Parameters:
*  adcGain: counts per volt
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void AdcMux_SetGain(int32 adcGain)
{
    AdcMux_SAR_SetGain((int16)adcGain);
}


/*******************************************************************************
* Function Name: AdcMux_SetScaledGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per 10 volts for the voltage conversion functions
*  that follow. This value is set by default by the reference and input range
*  settings. It should only be used to further calibrate the ADC with a known
*  input or if the ADC is using an external reference.
*
* Parameters:
*  int32  adcGain  counts per 10 volt
*
* Return:
*  None.
*
* Side Effects:
*  Affects AdcMux_CountsTo_Volts(), AdcMux_CountsTo_mVolts(),
*  AdcMux_CountsTo_uVolts() by supplying the correct conversion 
*  between ADC counts and the applied input voltage
*
* Reentrant:
*  No.
*
*******************************************************************************/
void AdcMux_SetScaledGain(int32 adcGain)
{
    AdcMux_SAR_SetScaledGain(adcGain);
}


/*******************************************************************************
* Function Name: AdcMux_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to mVolts as a 32-bit integer
*
* Parameters:
*  adcCounts: Result from the ADC_SAR_Seq conversion
*
* Return:
*  Result in mV
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int32 AdcMux_CountsTo_mVolts(int16 adcCounts)
{
    return ((int32) AdcMux_SAR_CountsTo_mVolts(adcCounts));
}


/*******************************************************************************
* Function Name: AdcMux_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to uVolts as a 32-bit integer
*
* Parameters:
*  adcCounts: Result from the ADC conversion
*
* Return:
*  Result in uV
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int32 AdcMux_CountsTo_uVolts(int16 adcCounts)
{
    return (AdcMux_SAR_CountsTo_uVolts(adcCounts));
}


/*******************************************************************************
* Function Name: AdcMux_CountsTo_Volts
********************************************************************************
*
* Summary:
*  Converts the ADC output to Volts as a floating point number
*
* Parameters:
*  adcCounts: Result from the ADC_SAR_Seq conversion
*
* Return:
*  Result in volts
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
float32 AdcMux_CountsTo_Volts(int16 adcCounts)
{
    return (AdcMux_SAR_CountsTo_Volts(adcCounts));
}


/* [] END OF FILE */
