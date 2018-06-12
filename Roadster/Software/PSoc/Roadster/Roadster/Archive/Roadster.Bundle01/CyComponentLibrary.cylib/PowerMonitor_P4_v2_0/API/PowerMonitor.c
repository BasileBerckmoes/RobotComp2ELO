/*******************************************************************************
* \file     `$INSTANCE_NAME`.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief Provides the source code to the API for the `$INSTANCE_NAME` Component.
*
* Note:
*
********************************************************************************
* \copyright
* (c) 2015-2016, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NON-INFRINGEMENT, IMPLIED
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

uint32 `$INSTANCE_NAME`_initVar = 0u;

`$INSTANCE_NAME`_callback faultCallback;

#if (`$INSTANCE_NAME`_USE_DMAC == 1)
/** Indicates whether the `$INSTANCE_NAME` DMAs have been triggered. */
volatile uint8 `$INSTANCE_NAME`_isDmaTriggered = 0u;
#endif /* `$INSTANCE_NAME`_USE_DMA */

/* Enabled fault array */
uint8 `$INSTANCE_NAME`_faultEnable[`$INSTANCE_NAME`_NUM_CONVERTERS] = `$FaultModeDefault`;   

/* Voltage tab related arrays as set in the customizer. */
/* Temporarily use these to load the ADC count limit arrays. */
const uint32 `$INSTANCE_NAME`_UVFaultThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS]
    = `$UVFaultThresholdInit`;
const uint32 `$INSTANCE_NAME`_UVWarnThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS]
    = `$UVWarnThresholdInit`;
const uint32 `$INSTANCE_NAME`_OVWarnThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS]
    = `$OVWarnThresholdInit`;
const uint32 `$INSTANCE_NAME`_OVFaultThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS]
    = `$OVFaultThresholdInit`;
const uint32 `$INSTANCE_NAME`_AdcClockSelect[`$INSTANCE_NAME`_NUM_CONVERTERS]
    = `$AdcClockSelect`;

const uint32 `$INSTANCE_NAME`_VoltageScalingFactor[`$INSTANCE_NAME`_NUM_CONVERTERS]
    = `$VoltageScaleInit`;

const uint32 `$INSTANCE_NAME`_CountScalingFactor[`$INSTANCE_NAME`_NUM_CONVERTERS]
    = `$CountScaleInit`;

/* Limit arrays in mV. */
uint32 `$INSTANCE_NAME`_UVFaultThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
uint32 `$INSTANCE_NAME`_OVFaultThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
uint32 `$INSTANCE_NAME`_UVWarnThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
uint32 `$INSTANCE_NAME`_OVWarnThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];

/* Limit arrays in ADC counts. */
uint16 `$INSTANCE_NAME`_UVFaultThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];
uint16 `$INSTANCE_NAME`_OVFaultThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];
uint16 `$INSTANCE_NAME`_UVWarnThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];
uint16 `$INSTANCE_NAME`_OVWarnThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];

/* Warn and Fault status for power monitors */
volatile uint32 `$INSTANCE_NAME`_UVWarnStatus  = 0uL;
volatile uint32 `$INSTANCE_NAME`_OVWarnStatus  = 0uL;
volatile uint32 `$INSTANCE_NAME`_UVFaultStatus = 0uL;
volatile uint32 `$INSTANCE_NAME`_OVFaultStatus = 0uL;
volatile uint32 `$INSTANCE_NAME`_PGoodStatus   = 0uL;

/* Local function prototype */
static uint16 `$INSTANCE_NAME`_mVToCounts(uint32 mV, uint32 chan, cystatus * funcStatus);
static uint32 `$INSTANCE_NAME`_GetAvgCntField(uint32 avgNum, cystatus * funcStatus);

/* Internal Global Variables */
uint32 `$INSTANCE_NAME`_samplesAveraged;
volatile uint8 `$INSTANCE_NAME`_faultConfig[`$INSTANCE_NAME`_NUM_CONVERTERS];
uint32 `$INSTANCE_NAME`_converterCounts[`$INSTANCE_NAME`_NUM_CONVERTERS];

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
***************************************************************************//**
*
* \brief Initialize the component.
*
* \param None
*
* \return None
*
* \sideeffect Clears all pending fault and warning status and resets all 
* thresholds to values from the customizer settings. All faults are disabled.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32 i;
    uint32 chanConfig;
    cystatus funcStatus;

    /* Initialize ADC in order to use voltage conversion tables. */
    `$INSTANCE_NAME`_ADC_Init();
    `$INSTANCE_NAME`_ADC_initVar = 1u;
    
    `$INSTANCE_NAME`_ADC_SAR_CHAN_EN_REG = (1uL << `$INSTANCE_NAME`_NUM_CONVERTERS) - 1uL;
    
    /*  Reset status, enable, and samples averaged. */
    `$INSTANCE_NAME`_samplesAveraged = `$INSTANCE_NAME`_SAMPLE_AVERAGED;
    `$INSTANCE_NAME`_UVWarnStatus = 0uL;
    `$INSTANCE_NAME`_OVWarnStatus = 0uL;
    `$INSTANCE_NAME`_UVFaultStatus = 0uL;
    `$INSTANCE_NAME`_OVFaultStatus = 0uL;
    
    #if (`$INSTANCE_NAME`_USE_PGOOD == 1) 
        `$INSTANCE_NAME`_PGood_Control_Reg_Write(0u);
    #endif /*(`$INSTANCE_NAME`_USE_PGOOD == 1))*/
    
    /* Set the samples averaged for the SAR */
    #if (1uL == `$INSTANCE_NAME`_SAMPLE_AVERAGED)
        /* Clear AVG_CNT to disable averaging. AVG_SHIFT is set. */
        `$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG = (`$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG & 
            ~`$INSTANCE_NAME`_ADC_AVG_CNT_MASK) | `$INSTANCE_NAME`_ADC_AVG_SHIFT;
    #else   
        i = `$INSTANCE_NAME`_GetAvgCntField(`$INSTANCE_NAME`_SAMPLE_AVERAGED, &funcStatus);

        /* Set the AVG_CNT to enable averaging. AVG_SHIFT is set. */ 
        `$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG = (`$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG & 
            ~`$INSTANCE_NAME`_ADC_AVG_CNT_MASK) | ((uint32)(i << `$INSTANCE_NAME`_ADC_AVG_CNT_OFFSET) |
            `$INSTANCE_NAME`_ADC_AVG_SHIFT);
    #endif
    
    for (i = 0uL; i < `$INSTANCE_NAME`_NUM_CONVERTERS; i++)
    {
        /* Get the current channel configuration value */
        chanConfig = CY_GET_REG32((reg32 *)(`$INSTANCE_NAME`_ADC_SAR_CHAN_CONFIG_IND + (uint32)(i << 2u)));
        
        #if (1uL == `$INSTANCE_NAME`_SAMPLE_AVERAGED)
            /* Clear the SAR AVE_EN to disable averaging. */
            chanConfig &= ~`$INSTANCE_NAME`_ADC_AVERAGING_EN;
        #else
            chanConfig |= `$INSTANCE_NAME`_ADC_AVERAGING_EN;
        #endif
        
        /* Set the ADC Chan Sample Time */
        chanConfig |= (`$INSTANCE_NAME`_AdcClockSelect[i] << `$INSTANCE_NAME`_ADC_SAMPLE_TIME_SEL_SHIFT);
        CY_SET_REG32((reg32 *)(`$INSTANCE_NAME`_ADC_SAR_CHAN_CONFIG_IND + (uint32)(i << 2)), chanConfig);
            
        /*  Set the fault modes to be checked from the customizer. */
        `$INSTANCE_NAME`_faultEnable[i] = `$INSTANCE_NAME`_DEFAULT_FAULT_MODE;
        
        /* Initialize the `$INSTANCE_NAME`_faultConfig array all faults disabled. */
        `$INSTANCE_NAME`_faultConfig[i] = (uint8) i;
        
        /* Set the threshold limits from the customizer. */
        `$INSTANCE_NAME`_UVFaultThreshold_mV[i] = `$INSTANCE_NAME`_UVFaultThresholdInit_mV[i];
        `$INSTANCE_NAME`_UVFaultThreshold_Count[i] = `$INSTANCE_NAME`_mVToCounts(`$INSTANCE_NAME`_UVFaultThreshold_mV[i], i, &funcStatus);
        
        `$INSTANCE_NAME`_OVFaultThreshold_mV[i] = `$INSTANCE_NAME`_OVFaultThresholdInit_mV[i];
        `$INSTANCE_NAME`_OVFaultThreshold_Count[i] = `$INSTANCE_NAME`_mVToCounts(`$INSTANCE_NAME`_OVFaultThreshold_mV[i], i, &funcStatus);
        
        `$INSTANCE_NAME`_UVWarnThreshold_mV[i] = `$INSTANCE_NAME`_UVWarnThresholdInit_mV[i];
        `$INSTANCE_NAME`_UVWarnThreshold_Count[i] = `$INSTANCE_NAME`_mVToCounts(`$INSTANCE_NAME`_UVWarnThreshold_mV[i], i, &funcStatus);
        
        `$INSTANCE_NAME`_OVWarnThreshold_mV[i] = `$INSTANCE_NAME`_OVWarnThresholdInit_mV[i];
        `$INSTANCE_NAME`_OVWarnThreshold_Count[i] = `$INSTANCE_NAME`_mVToCounts(`$INSTANCE_NAME`_OVWarnThreshold_mV[i], i, &funcStatus);
    }
    
    #if (`$INSTANCE_NAME`_USE_DMAC == 1)
        
    /* Sample DMA*/ 
    `$INSTANCE_NAME`_DMA_Sample_Start((void *) `$INSTANCE_NAME`_ADC_cy_psoc4_sar__SAR_CHAN_RESULT00, (void *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_A0_REG);
    `$INSTANCE_NAME`_DMA_Sample_SetNumDataElements(0, ((int32) `$INSTANCE_NAME`_NUM_CONVERTERS));
    CYDMA_DESCR_BASE.descriptor[`$INSTANCE_NAME`_DMA_Sample_CHANNEL][0].status &= ~(uint32)CYDMA_TRANSFER_INDEX;
    
    /* UV limit DMA */
    `$INSTANCE_NAME`_DMA_LimitUV_Start((void *) &`$INSTANCE_NAME`_UVFaultThreshold_Count, (void *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_D0_REG);
    `$INSTANCE_NAME`_DMA_LimitUV_SetNumDataElements(0, ((int32) `$INSTANCE_NAME`_NUM_CONVERTERS));
    CYDMA_DESCR_BASE.descriptor[`$INSTANCE_NAME`_DMA_LimitUV_CHANNEL][0].status &= ~(uint32)CYDMA_TRANSFER_INDEX;
    
    /* OV limit DMA */
    `$INSTANCE_NAME`_DMA_LimitOV_Start((void *) &`$INSTANCE_NAME`_OVFaultThreshold_Count, (void *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_D1_REG);
    `$INSTANCE_NAME`_DMA_LimitOV_SetNumDataElements(0, ((int32) `$INSTANCE_NAME`_NUM_CONVERTERS));   
    CYDMA_DESCR_BASE.descriptor[`$INSTANCE_NAME`_DMA_LimitOV_CHANNEL][0].status &= ~(uint32)CYDMA_TRANSFER_INDEX;
    
    /* Enable DMA */
    `$INSTANCE_NAME`_DMA_Enable_Start((void *) &`$INSTANCE_NAME`_faultConfig, (void *) `$INSTANCE_NAME`_HwComp_Comp_u0__A1_REG);
    `$INSTANCE_NAME`_DMA_Enable_SetNumDataElements(0, ((int32) `$INSTANCE_NAME`_NUM_CONVERTERS));
    CYDMA_DESCR_BASE.descriptor[`$INSTANCE_NAME`_DMA_Enable_CHANNEL][0].status &= ~(uint32)CYDMA_TRANSFER_INDEX;
    
    /* Check DMA */
    `$INSTANCE_NAME`_DMA_Check_Start((void *) `$INSTANCE_NAME`_HwComp_Comp_u0__A1_REG, (void *) `$INSTANCE_NAME`_HwComp_MyEnable__CONTROL_REG);
    `$INSTANCE_NAME`_DMA_Check_SetNumDataElements(0, 1);

    #endif /* `$INSTANCE_NAME`_USE_DMAC */
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
***************************************************************************//**
*
* \brief Enables hardware blocks within the component and starts scanning. The 
* `$INSTANCE_NAME`_Start or `$INSTANCE_NAME`_Init function must be called prior 
* to calling this function.
*
* \param None
*
* \return None
* 
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) 
{
    #if (1 == `$INSTANCE_NAME`_USE_DMAC)
        
    `$INSTANCE_NAME`_DMA_Sample_ChEnable();
    CyDmaEnable();
        
    /* Start ISRs. */
    `$INSTANCE_NAME`_uv_isr_StartEx(&`$INSTANCE_NAME`_Uv_ISR_Handler);
    `$INSTANCE_NAME`_ov_isr_StartEx(&`$INSTANCE_NAME`_Ov_ISR_Handler);
    `$INSTANCE_NAME`_ADC_IRQ_Enable();
    #endif /* (`$INSTANCE_NAME`_USE_DMAC == 1) */

    /* Start ADC with power monitor ISR. */
    `$INSTANCE_NAME`_ADC_Start();
    #if (`$INSTANCE_NAME`_USE_DMAC == 1)
    `$INSTANCE_NAME`_ADC_IRQ_StartEx((cyisraddress) &`$INSTANCE_NAME`_ADC_DMA_ISR);
    #endif /* (`$INSTANCE_NAME`_USE_DMAC == 1) */

    #if(`$INSTANCE_NAME`_EXPOSE_SOC == 0)
    `$INSTANCE_NAME`_ADC_StartConvert();
    #endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* \brief Enables the component. Calls `$INSTANCE_NAME`_Init() if the component 
* has not been initialized before. Calls `$INSTANCE_NAME`_Enable().
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0uL == `$INSTANCE_NAME`_initVar)
    {
       `$INSTANCE_NAME`_Init();
       `$INSTANCE_NAME`_initVar = 1uL;
    }

    /* Enable the component */
    `$INSTANCE_NAME`_Enable();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* \brief Disables the component. ADC sampling stops.
*
* \param None
*
* \returns None
*
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{   
    /* Stop the hardware */
    #if (1 == `$INSTANCE_NAME`_USE_DMAC)
        `$INSTANCE_NAME`_ADC_IRQ_Disable();
        `$INSTANCE_NAME`_DMA_Sample_ChDisable();
        `$INSTANCE_NAME`_isDmaTriggered = 0u;
    #endif /* (`$INSTANCE_NAME`_USE_DMAC == 1) */
    `$INSTANCE_NAME`_ADC_Stop();
    
    /* De-assert the output signals */
    `$INSTANCE_NAME`_UVWarnStatus = 0uL;
    `$INSTANCE_NAME`_OVWarnStatus = 0uL;
    `$INSTANCE_NAME`_UVFaultStatus = 0uL;
    `$INSTANCE_NAME`_OVFaultStatus = 0uL;
    
    #if (`$INSTANCE_NAME`_USE_PGOOD == 1)
        `$INSTANCE_NAME`_PGood_Control_Reg_Write(0u);
    #endif /*(`$INSTANCE_NAME`_USE_PGOOD == 1)*/
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableFault
****************************************************************************//**
*
* \brief Enables fault detection for the desired converters. When a fault 
* happens in the specific converter, the component stops scanning faults for 
* that converter until it is re-enabled by calling this API.
* 
* Specifically which fault sources are enabled is configured using the 
* `$INSTANCE_NAME`_SetFaultMode().
* 
* Only OV faults (if set as a fault source) are automatically enabled by 
* `$INSTANCE_NAME`_Init. Calling this API enables checking for all configured
* faults.
* 
* \param converterMask     Mask that sets which converters should be checked for 
* faults. Each bit is linked to one converter. If the bit is not set, the 
* current configuration is kept.
* 
* \return None
* 
* \sideeffect Enabled fault settings are updated even when component is stopped.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableFault(uint32 converterMask) 
{
    uint8 converter;
    uint8 converterNum;
    uint8 enableShifted;
    
    /* Update `$INSTANCE_NAME`_faultConfig */
    for (converter = 0u; converter < `$INSTANCE_NAME`_NUM_CONVERTERS; converter++)
    {
        if (0u != (converterMask & (1uL << converter)))
        {
            converterNum = converter;
            enableShifted = (`$INSTANCE_NAME`_faultEnable[converter] << `$INSTANCE_NAME`_ENABLE_OV_SHIFT);
            `$INSTANCE_NAME`_faultConfig[converter] = (converterNum | enableShifted | `$INSTANCE_NAME`_ENABLE_FAULT_MASK);
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableFault
****************************************************************************//**
*
* \brief Disables UV fault detection for the desired converters. 
* 
* To disable OV fault detection use `$INSTANCE_NAME`_SetFaultMode(). This
* ensures that OV faults will still be detected after calling
* `$INSTANCE_NAME`_DisableFault(). 
*
* \param converterMask     Mask that sets which converters should be disabled 
* for faults. Each bit is linked to one converter. If the bit is not set, the 
* current configuration is kept.
*
* \return None
*
* \sideeffect Disabled fault settings are updated even when component is stopped.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableFault(uint32 converterMask) 
{
    uint32 i;
    
    /* Update `$INSTANCE_NAME`_faultConfig */
    for (i = 0u; i < `$INSTANCE_NAME`_NUM_CONVERTERS; i++)
    {
        if (0u != (uint32)(converterMask & (1uL << i)))
        {
            `$INSTANCE_NAME`_faultConfig[i] &= (uint8)(~`$INSTANCE_NAME`_ENABLE_UV_MASK);
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFaultMode
****************************************************************************//**
*
* \brief Configures fault sources for each power converter. Two fault sources 
* are available: OV and UV. The fault sources defined in the customizer set 
* the initial fault source values. Updated fault sources are not active until API
* `$INSTANCE_NAME`_EnableFault() is called.
*
* \param converterNum      Specifies the converter number. 
*                          - 1 = Converter 1,
*                          - 2 = Converter 2,
*                          - ...
*                          - 8 = Converter 8
* \param faultMode         - Bit 0: Enable OV Fault
*                          - Bit 1: Enable UV Fault
*
* \return None
* 
* \sideeffect Fault mode settings are updated even when component is stopped.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFaultMode(uint32 converterNum, uint32 faultMode)
{
    /* Changing from 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    if (`$INSTANCE_NAME`_NUM_CONVERTERS > chan)
    {
        /* Update the fault mode array */
        `$INSTANCE_NAME`_faultEnable[chan] = (uint8)(faultMode & `$INSTANCE_NAME`_FAULT_MODE_MASK);
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultMode
****************************************************************************//**
*
* \brief Returns enabled fault sources from the component.
* - Bit0: OV fault source
* - Bit1: UV fault source
*
* \param converterNum       Specifies the converter number.
*
* \return uint32
* 
* \sideeffect Returns zero if converterNum is an invalid value.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetFaultMode(uint32 converterNum) 
{
    /* Changing from 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    uint32 faultMode = 0uL;
    
    if (`$INSTANCE_NAME`_NUM_CONVERTERS > chan)
    {
        faultMode = (uint32)(`$INSTANCE_NAME`_faultEnable[chan]);
    }
    return faultMode;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPGoodStatus
****************************************************************************//**
*
* \brief Returns the pgood status of all converters. Each bit represents the 
* pgood of one converter. 
* 
* The pgood status and the pgood terminal are updated when this API is called.
* 
* The pgood status of a converter is a combination of 
* `$INSTANCE_NAME`_faultEnable[] state, set in the GUI or the 
* `$INSTANCE_NAME`_SetFaultMode() API, and the voltage of the converter.
* 
* If the OV and UV faults are not enabled in `$INSTANCE_NAME`_faultEnable[] then 
* pgood is always high.
* 
* If only UV faults are enabled then pgood is high when the converter's voltage
* is above the UV limit.
* 
* If only OV faults are enabled then pgood is high when the converter's voltage 
* is below the OV limit.
* 
* If both OV and UV faults are enabled then pgood is high when the converter's
* voltage is between the OV and UV limits.
* 
* Note that enabling/disabling OV/UV detection through the 
* `$INSTANCE_NAME`_EnableFault() and `$INSTANCE_NAME`_DisableFault() APIs do not
* affect the pgood status.
*
* \param None
*
* \return uint32
* 
* \sideeffect The PGood terminal values are updated with the values returned by 
* this API.  Returns 0 if component is disabled.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetPGoodStatus(void) 
{
    uint32 i;
    uint16 chanCounts;
    uint32 PGoodMask = 0uL;
    uint32 PGoodReturn = 0uL;
    
    if (0u != `$INSTANCE_NAME`_ENABLED)
    {
        `$INSTANCE_NAME`_PGoodStatus = 0uL;
        for (i = 0u; i < `$INSTANCE_NAME`_NUM_CONVERTERS; i++)
        {
            chanCounts = (uint16) `$INSTANCE_NAME`_ADC_GetResult16(i);
            
            if (((0u == (`$INSTANCE_NAME`_faultEnable[i] & `$INSTANCE_NAME`_UV_MASK)) || 
               (chanCounts >= `$INSTANCE_NAME`_UVFaultThreshold_Count[i])) &&
            
               ((0u == (`$INSTANCE_NAME`_faultEnable[i] & `$INSTANCE_NAME`_OV_MASK)) || 
               (chanCounts <= `$INSTANCE_NAME`_OVFaultThreshold_Count[i])))
            {
                /* Converter within threshold limits set PGood bit high. */
                `$INSTANCE_NAME`_PGoodStatus |= (1uL << i);
            }
            
            if (0u != (`$INSTANCE_NAME`_faultEnable[i] & (`$INSTANCE_NAME`_UV_MASK | `$INSTANCE_NAME`_OV_MASK)))
            {
                PGoodMask |= (1uL << i);
            }
        }
        
        #if (`$INSTANCE_NAME`_USE_PGOOD == 1)
            /* If using a global PGood instead of individual PGood signals */
            #if (0u == `$INSTANCE_NAME`_PGOOD_CONFIG)
                if (0uL != (~`$INSTANCE_NAME`_PGoodStatus & PGoodMask))
                {
                    `$INSTANCE_NAME`_PGood_Control_Reg_Write(0x00u);
                }
                else
                {
                    `$INSTANCE_NAME`_PGood_Control_Reg_Write(0xFFu);
                }
            #else
                `$INSTANCE_NAME`_PGood_Control_Reg_Write((uint8)`$INSTANCE_NAME`_PGoodStatus);
            #endif
        #endif /*(`$INSTANCE_NAME`_USE_PGOOD == 1)*/
        
        PGoodReturn = `$INSTANCE_NAME`_PGoodStatus;
    }
    return PGoodReturn;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultSource
****************************************************************************//**
*
* \brief Returns pending fault sources from the component where each bit 
* represents a converter. This API can be used to poll the fault status of the 
* component. When this API returns a non-zero value, the 
* `$INSTANCE_NAME`_GetOVFaultStatus(), `$INSTANCE_NAME`_GetUVFaultStatus() APIs
* can provide further information on which power converter(s) caused the fault. 
* The fault source bits are cleared by calling the relevant Get Fault Status 
* APIs.
* 
* If DMA is not used, the fault status is updated on calling this API. This API
* has the same behavior as the DMA, performing the equivalent OV and UV 
* comparison in firmware rather than hardware.
*
* \param None
*
* \return uint32
* 
* \sideeffect Fault sources are cleared by the Stop API. 
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetFaultSource(void) 
{
    #if (`$INSTANCE_NAME`_USE_DMAC == 0)
        uint8 chan;
        uint16 chanCounts;
    
        if (0uL != `$INSTANCE_NAME`_ENABLED)
        {    
            /* DMA not used. Update the OV and UV Fault values with latest . */
            for (chan = 0u; chan < `$INSTANCE_NAME`_NUM_CONVERTERS; chan++)
            {
                chanCounts = (uint16) `$INSTANCE_NAME`_ADC_GetResult16((uint32) chan);
                
                /* Update the UVFaultStatus if active. */
                if ((`$INSTANCE_NAME`_faultConfig[chan] & `$INSTANCE_NAME`_ENABLE_UV_MASK) != 0u)
                {
                    if (chanCounts <= `$INSTANCE_NAME`_UVFaultThreshold_Count[chan])  
                    {
                        `$INSTANCE_NAME`_UVFaultStatus |= (1uL << chan);
                        `$INSTANCE_NAME`_faultConfig[chan] &= (uint8)(~`$INSTANCE_NAME`_ENABLE_UV_MASK);
                    }
                }
                    
                /* Update the OVFaultStatus if active.*/
                if ((`$INSTANCE_NAME`_faultConfig[chan] & `$INSTANCE_NAME`_ENABLE_OV_MASK) != 0u)
                {
                    if (chanCounts >= `$INSTANCE_NAME`_OVFaultThreshold_Count[chan])  
                    {
                        `$INSTANCE_NAME`_OVFaultStatus |= (1uL << chan);
                        `$INSTANCE_NAME`_faultConfig[chan] &= 
                             (uint8) (~(`$INSTANCE_NAME`_ENABLE_OV_MASK | `$INSTANCE_NAME`_ENABLE_UV_MASK));
                    }
                }
            }
        }
    #endif /* (`$INSTANCE_NAME`_USE_DMAC == 0) */

    /* Return the status */
    return (`$INSTANCE_NAME`_UVFaultStatus | `$INSTANCE_NAME`_OVFaultStatus);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVFaultStatus
****************************************************************************//**
*
* \brief Return over voltage fault status of each power converter where each bit 
* represents a converter. The fault bits are cleared on read. Once a fault is 
* detected, the component will no longer update the fault status for the faulty 
* converter until `$INSTANCE_NAME`_EnableFault API is called to re-enable fault 
* detection on the specific converter. 
*
* \param None
*
* \return 32-bit status indicating the over voltage fault status of each
* power converter.
*
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetOVFaultStatus(void)
{
    uint8 critical = CyEnterCriticalSection();
    
    uint32 OVFaultStatus = `$INSTANCE_NAME`_OVFaultStatus;
    `$INSTANCE_NAME`_OVFaultStatus = 0uL;
    
    CyExitCriticalSection(critical);
    
    return OVFaultStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVFaultStatus
****************************************************************************//**
*
* \brief Return under voltage fault status of each power converter where each 
* bit represents a converter. The fault bits are cleared on read. Once a fault 
* is detected, the component will not longer update the fault status for the 
* faulty converter until `$INSTANCE_NAME`_EnableFault API is called to re-enable 
* fault detection on the specific converter.
*
* \param None
*
* \return 32-bit status indicating the under voltage fault status of each
* power converter.
*
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetUVFaultStatus(void)
{
    uint8  critical = CyEnterCriticalSection();
    
    uint32 UVFaultStatus = `$INSTANCE_NAME`_UVFaultStatus;
    `$INSTANCE_NAME`_UVFaultStatus = 0uL;
    
    CyExitCriticalSection(critical);
    
    return UVFaultStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVWarnStatus
****************************************************************************//**
*
* \brief Returns over voltage warning status of each power converter where each 
* bit represents a converter. The warning status is updated on calling this API. 
* No background task updates the warning bits. The intent is to optimize the 
* fault detection as the warning status is not called frequently.
*
* \param None
*
* \return 32-bit status indicating the over voltage warning status of each
* power converter.
* 
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetOVWarnStatus(void)
{
    uint32 chan;
    uint16 chanCounts;
    uint32 OVWarnStatus = 0uL;
    
    if ((0u != `$INSTANCE_NAME`_ENABLED) && (1u == `$INSTANCE_NAME`_DEFAULT_OV_WARN_MODE))
    {    
        for (chan = 0u; chan < `$INSTANCE_NAME`_NUM_CONVERTERS; chan++)
        {
            chanCounts = (uint16) `$INSTANCE_NAME`_ADC_GetResult16(chan);
            
            if (chanCounts > `$INSTANCE_NAME`_OVWarnThreshold_Count[chan])  
            {
                OVWarnStatus |= (1uL << chan);
            }
        }
    }
    
    return OVWarnStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVWarnStatus
****************************************************************************//**
*
* \brief Returns under voltage warning status of each power converter where 
* each bit represents a converter. The warning status is updated on calling this 
* API. No background task updates the warning bits. The intent is to optimize 
* the fault detection as the warning status is not called frequently.
*
* \param None
*
* \return 32-bit value indicating under voltage warning status for each power
* converter.
* 
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetUVWarnStatus(void)
{
    uint32 chan;
    uint16 chanCounts;
    uint32 UVWarnStatus = 0uL;
    
    if ((0u != `$INSTANCE_NAME`_ENABLED) && (1u == `$INSTANCE_NAME`_DEFAULT_UV_WARN_MODE))
    {    
        for (chan = 0u; chan < `$INSTANCE_NAME`_NUM_CONVERTERS; chan++)
        {
            chanCounts = (uint16) `$INSTANCE_NAME`_ADC_GetResult16(chan);
            
            if (chanCounts < `$INSTANCE_NAME`_UVWarnThreshold_Count[chan])  
            {
                UVWarnStatus |= (1uL << chan);
            }
        }
    }
    
    return UVWarnStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUVWarnThreshold
****************************************************************************//**
*
* \brief Sets the power converter under voltage warning threshold for the 
* specified power converter. 
*
* \param converterNum         Specifies the converter number
* \param uvWarnThreshold_mV   Specifies the under voltage warning threshold in 
* mV. 
* - Min value = 1 mV.
* - Max value = 65535 mV.
*
* \return cystatus CYRET_SUCCESS or CYRET_BAD_PARAM
* 
* \sideeffect None
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetUVWarnThreshold(uint32 converterNum, uint32 uvWarnThreshold_mV) 
{
    /* Convert 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    uint16 uvWarnCounts;
    cystatus funcStatus = CYRET_BAD_PARAM;
    
    uvWarnCounts = `$INSTANCE_NAME`_mVToCounts(uvWarnThreshold_mV, chan, &funcStatus);
    if(funcStatus == CYRET_SUCCESS)
    {
        /* Set the under voltage warn threshold */
        `$INSTANCE_NAME`_UVWarnThreshold_Count[chan] = uvWarnCounts;
        `$INSTANCE_NAME`_UVWarnThreshold_mV[chan] = uvWarnThreshold_mV;
    }
    return funcStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVWarnThreshold
****************************************************************************//**
*
* \brief Returns the power converter under voltage warning threshold for the 
* specified power converter in mV. 
*
* \param converterNum      Specifies the converter number
*
* \return 32-bit value indicating the under voltage threshold in mV. Return
* zero if converterNum is more than the number of converters.
* 
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetUVWarnThreshold(uint32 converterNum) 
{
    /* Convert 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    uint32 uvWarnThreshold_mV = 0uL;

    if (chan < `$INSTANCE_NAME`_NUM_CONVERTERS)
    {
        uvWarnThreshold_mV = `$INSTANCE_NAME`_UVWarnThreshold_mV[chan];
    }

    return uvWarnThreshold_mV;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOVWarnThreshold
****************************************************************************//**
*
* \brief Sets the power converter over voltage warning threshold for the 
* specified power converter. 
*
* \param converterNum      Specifies the converter number
* \param ovWarnThreshold_mv   Specifies the over voltage warning threshold in mV. 
*                          
* - Min value = 1 mV.
* - Max value = 65535 mV.
*
* \return cystatus CYRET_SUCCESS or CYRET_BAD_PARAM
* 
* \sideeffect None
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetOVWarnThreshold(uint32 converterNum, uint32 ovWarnThreshold_mV)
{
    /* Convert 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    uint16 ovWarnCounts;
    cystatus funcStatus = CYRET_BAD_PARAM;

    ovWarnCounts = `$INSTANCE_NAME`_mVToCounts(ovWarnThreshold_mV, (chan), &funcStatus);
    if(funcStatus == CYRET_SUCCESS)
    {
        /* Set the over voltage warn threshold for warn checking */
        `$INSTANCE_NAME`_OVWarnThreshold_Count[chan] = ovWarnCounts;
        `$INSTANCE_NAME`_OVWarnThreshold_mV[chan] = ovWarnThreshold_mV;
    }
    return funcStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVWarnThreshold
****************************************************************************//**
*
* \brief Returns the power converter over voltage warning threshold for the 
* specified power converter in mV.
*
* \param converterNum      Specifies the converter number
*
* \return 32-bit value indicating the over voltage threshold in mV.
* 
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetOVWarnThreshold(uint32 converterNum) 
{
    /* Convert 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    uint32 ovWarnThreshold_mV = 0uL;

    if (chan < `$INSTANCE_NAME`_NUM_CONVERTERS)
    {
        ovWarnThreshold_mV = `$INSTANCE_NAME`_OVWarnThreshold_mV[chan];
    }

    return ovWarnThreshold_mV;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUVFaultThreshold
****************************************************************************//**
*
* \brief Sets the power converter under voltage fault threshold for the 
* specified power converter
*
* \param converterNum         Specifies the converter number
* \patam UVFaultThreshold_mV  Specifies the under voltage fault threshold in mV. 
*                             
* - Min value = 1vmV.
* - Max = 65535 mV.
*
* \return cystatus CYRET_SUCCESS or CYRET_BAD_PARAM
* 
* \sideeffect None
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetUVFaultThreshold(uint32 converterNum, uint32 uvFaultThreshold_mV) 
{
    /* Convert 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    uint16 uvFaultCounts;
    cystatus funcStatus = CYRET_BAD_PARAM;

    uvFaultCounts = `$INSTANCE_NAME`_mVToCounts(uvFaultThreshold_mV, chan, &funcStatus);
    if(funcStatus == CYRET_SUCCESS)
    {
        /* Set the threshold */
        `$INSTANCE_NAME`_UVFaultThreshold_Count[chan] = uvFaultCounts;
        `$INSTANCE_NAME`_UVFaultThreshold_mV[chan] = uvFaultThreshold_mV;
    }
    return funcStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVFaultThreshold
****************************************************************************//**
*
* \brief Returns the power converter under voltage fault threshold for the 
* specified power converter in mV.  
*
* \param converterNum      Specifies the converter number
*
* \return 32-bit value indicating the under voltage fault threshold in mV.
* 
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetUVFaultThreshold(uint32 converterNum) 
{
    /* Convert 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    uint32 uvFaultThreshold_mV = 0uL;

    if (chan < `$INSTANCE_NAME`_NUM_CONVERTERS)
    {
        uvFaultThreshold_mV = `$INSTANCE_NAME`_UVFaultThreshold_mV[chan];
    }

    return uvFaultThreshold_mV;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOVFaultThreshold
****************************************************************************//**
*
* \brief Sets the power converter over voltage fault threshold for the specified 
* power converter. 
* 
* \param converterNum         Specifies the converter number
* \param OVFaultThreshold_mV  Specifies the over voltage fault threshold in mV. 
*                             
* - Min value = 1 mV.
* - Max value = 65535 mV.
*
* \return cystatus CYRET_SUCCESS or CYRET_BAD_PARAM
* 
* \sideeffect None
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetOVFaultThreshold(uint32 converterNum, uint32 ovFaultThreshold_mV) 
{
    uint16 ovFaultCounts;
    uint32 chan = converterNum - 1uL;
    cystatus funcStatus = CYRET_BAD_PARAM;

    ovFaultCounts = `$INSTANCE_NAME`_mVToCounts(ovFaultThreshold_mV, (chan), &funcStatus);
    if(funcStatus == CYRET_SUCCESS)
    {
        /* Set the over voltage fault threshold */
        `$INSTANCE_NAME`_OVFaultThreshold_Count[chan] = ovFaultCounts;
        `$INSTANCE_NAME`_OVFaultThreshold_mV[chan] = ovFaultThreshold_mV;
    }
    return funcStatus;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVFaultThreshold
****************************************************************************//**
*
* \brief Returns the power converter over voltage fault threshold for the 
* specified power converter in mV. 
*
* \param converterNum      Specifies the converter number.
*
* \return 32-bit value indicating the over voltage fault threshold in mV.
*
* \sideeffect None
* 
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetOVFaultThreshold(uint32 converterNum) 
{
    uint32 ovFaultThreshold_mV = 0uL;
    uint32 chan = converterNum - 1uL;
    if ((converterNum > 0uL) && (converterNum <= `$INSTANCE_NAME`_NUM_CONVERTERS))
    {
       ovFaultThreshold_mV = `$INSTANCE_NAME`_OVFaultThreshold_mV[chan];
    }

    return (ovFaultThreshold_mV);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetConverterVoltage
****************************************************************************//**
*
* \brief Returns the converter output voltage for the specified power converter 
* in mV. 
*
* \param converterNum      Specifies the converter number.
*
* \return Output voltage for the specified converter in mV. Valid range is 
* 1 - 65535. (uint32)
* 
* \sideeffect None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetConverterVoltage(uint32 converterNum) 
{
    uint32 mV = 0uL;
    int16 adcResult;

    /* Convert 1-based converter to zero-based channel number */
    uint32 chan = converterNum - 1uL;
    
    if (chan < `$INSTANCE_NAME`_NUM_CONVERTERS)
    {
        adcResult = `$INSTANCE_NAME`_ADC_GetResult16(chan);
        
        /* Scale the result and add half of scaling factor before integer division */
        mV = (uint32) adcResult;
        mV = mV * `$INSTANCE_NAME`_CountScalingFactor[chan];
        mV = (mV + `$INSTANCE_NAME`_SCALE_ROUNDING) >> `$INSTANCE_NAME`_SCALE_DIVIDE;
    }
    
    return mV;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSamplesAveraged()
****************************************************************************//**
*
* \brief Set number of samples taken for averaged channels. If a number that is 
* not a power of 2 is provided a CYRET_BAD_PARAM value is returned.
*
* \param numSample      1, 2, 4, 8, 16, 32, 64, 128, 256
*
* \return cystatus CYRET_SUCCESS or CYRET_BAD_PARAM
* 
* \sideeffect None
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetSamplesAveraged(uint32 numSample)
{
    uint32 i;
    uint32 j;
    uint32 chanConfig;
    cystatus funcStatus =  CYRET_BAD_PARAM;
    
    
    if (1uL == numSample)
    {
        /* Clear the SAR AVE_EN and AVG_CNT to disable averaging. AVG_SHIFT is set. */
        for (j = 0u; j < `$INSTANCE_NAME`_NUM_CONVERTERS; j++)
        {
            chanConfig = CY_GET_REG32((reg32 *)(`$INSTANCE_NAME`_ADC_SAR_CHAN_CONFIG_IND + (uint32)(j << 2u)));
            chanConfig &= ~`$INSTANCE_NAME`_ADC_AVERAGING_EN;
            CY_SET_REG32((reg32 *)(`$INSTANCE_NAME`_ADC_SAR_CHAN_CONFIG_IND + (uint32)(j << 2)), chanConfig);
        }
        `$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG = (`$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG & 
            ~`$INSTANCE_NAME`_ADC_AVG_CNT_MASK);
        `$INSTANCE_NAME`_samplesAveraged = numSample;
        funcStatus = CYRET_SUCCESS;
    }
    else
    {
        i = `$INSTANCE_NAME`_GetAvgCntField(numSample, &funcStatus);
        
        if( funcStatus == CYRET_SUCCESS)
        {
            /* Set the SAR AVE_EN and AVG_CNT to enable averaging. AVG_SHIFT is set. */ 
            for (j = 0u; j < `$INSTANCE_NAME`_NUM_CONVERTERS; j++)
            {
                chanConfig = CY_GET_REG32((reg32 *)(`$INSTANCE_NAME`_ADC_SAR_CHAN_CONFIG_IND + (uint32)(j << 2u)));
                chanConfig |= `$INSTANCE_NAME`_ADC_AVERAGING_EN;
                CY_SET_REG32((reg32 *)(`$INSTANCE_NAME`_ADC_SAR_CHAN_CONFIG_IND + (uint32)(j << 2)), chanConfig);
            }
            `$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG = (`$INSTANCE_NAME`_ADC_SAR_SAMPLE_CTRL_REG & 
                ~`$INSTANCE_NAME`_ADC_AVG_CNT_MASK) | (uint32)(i << `$INSTANCE_NAME`_ADC_AVG_CNT_OFFSET);
                
            `$INSTANCE_NAME`_samplesAveraged = numSample;
        }
    }
    return funcStatus;
}
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSamplesAveraged()
****************************************************************************//**
*
* \brief Returns the samples averaged configured in the customizer or by the
* `$INSTANCE_NAME`_SetSamplesAveraged() API.
*
* \param None
*
* \return Number of samples averaged.
* 
* \sideeffect None
*
*******************************************************************************/

/* This function is implemented as a macro since it simply returns */
/* the `$INSTANCE_NAME`_samplesAveraged variable. This variable is */
/* used for efficiency when a differentiating between no averaging, */
/* `$INSTANCE_NAME`_samplesAveraged=1, and the number of samples when averaging.*/


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFaultCallbackFunction()
****************************************************************************//**
*
* \brief Set the fault callback function. The callback function is called every
* time a fault happens. The callback function requires two arguments:
* - typedef (*`$INSTANCE_NAME`_callback_func) (uint32 converterNum, 
* uint32 fault_type)
*
* \param func      fault callback function
*
* \return None
* 
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFaultCallbackFunction(`$INSTANCE_NAME`_callback func)
{
    faultCallback = func;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAvgCntField()
********************************************************************************
*
* \brief
*  Convert an average number to the AVG_CNT used by the ADC
*
* \param avgNum Number of samples averaged by the ADC.
* \param convSuccess pointer to conversion result returns: CYRET_SUCCESS, 
* CYRET_BAD_PARAM
*
* \return counts AVG_CNT field corresponding to desired number of samples averaged.
*
* \sideeffect None
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_GetAvgCntField(uint32 avgNum, cystatus * funcStatus)
{
    uint32 i = 0uL;
    uint32 mask = 1uL;
    
    /* Check that avgNum is less than or equal to maximum and is a power of two */
    if ((0uL == ((avgNum - 1uL) & avgNum )) && (avgNum <= `$INSTANCE_NAME`_MAX_SAMPLES))
    {
        for(i = 0uL; i <= `$INSTANCE_NAME`_MAX_SAMPLES_BIT; i++)
        {
            mask = mask << 1uL;
            if(mask == avgNum)
            {
                *funcStatus = CYRET_SUCCESS;
                break;
            }
        }
    }
    else
    {
        *funcStatus = CYRET_BAD_PARAM;
    }
    
    return i;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_mVToCounts()
********************************************************************************
*
* \brief
*  Convert mV to Counts for current ADC Config.
*
* \param mV          Millivolt value to convert to counts. Must be 1 to 0x10000.
* \param chan        channel id, zero-based index
* \param convSuccess pointer to conversion result returns: CYRET_SUCCESS, 
* CYRET_BAD_PARAM
*
* \return counts     ADC raw counts corresponding to desired mV value
*
* \sideeffect None
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_mVToCounts(uint32 mV, uint32 chan, cystatus * funcStatus)
{
    uint32 counts = 0uL;
    
    if ((chan < `$INSTANCE_NAME`_NUM_CONVERTERS) && ((mV > 0uL) && (mV < 0x10000uL)))
    {
        counts = mV * `$INSTANCE_NAME`_VoltageScalingFactor[chan];
        counts += `$INSTANCE_NAME`_SCALE_ROUNDING;
        counts = counts >> `$INSTANCE_NAME`_SCALE_DIVIDE;
        counts += (uint32) `$INSTANCE_NAME`_ADC_offset[chan];
        
        if (counts < 0x10000uL)
        {
            *funcStatus = CYRET_SUCCESS;
        }
        else
        {
            counts = 0uL;
            *funcStatus = CYRET_BAD_DATA;
        }
    }
    else
    {
        *funcStatus = CYRET_BAD_PARAM;
    }
    
    return (uint16) counts;
}

/* [] END OF FILE */
