/*******************************************************************************
* \file     `$INSTANCE_NAME`_INT.c
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
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_USE_DMAC == 1)


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Uv_ISR_Handler
***************************************************************************//**
*
* \brief Interrupt Service Routine for the Under-Voltage Condition.
*
* \param None
*
* \return None
*
* \sideeffect Clears the UV fault of the converter that issued the most recent 
* fault. Sets the UV fault status for the converter. Then calls the fault 
* callback, passing it the converter number and the flag indicating the UV 
* condition.
* 
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_Uv_ISR_Handler)
{
    /* When a fault occurs, the fault channel is stored in bits [4:0] of the UDB FIFO */
    uint16 uvChan = ((uint16)`$INSTANCE_NAME`_HwComp_F0_REG & `$INSTANCE_NAME`_ENABLE_CONVERTER_NUM_MSK);
    `$INSTANCE_NAME`_faultConfig[uvChan] &= (uint8)(~`$INSTANCE_NAME`_ENABLE_UV_MASK);
    
    `$INSTANCE_NAME`_UVFaultStatus |= ((1ul) << uvChan);
    
    if (0 != faultCallback)
    {
        /* Adding 1 to convert zero-based channel number to 1-based converter number */
        faultCallback(((uint32)uvChan + 1ul), (uint32)`$INSTANCE_NAME`_UV_MASK);
    }
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Ov_ISR_Handler
***************************************************************************//**
*
* \brief Interrupt Service Routine for the Under-Voltage Condition.
*
* \param None
*
* \return None
*
* \sideeffect Clears both OV and UV faults of the converter that issued the most 
* recent fault. Sets the OV fault status for the converter. Then calls the fault 
* callback, passing it the converter number and the flag indicating the OV 
* condition.
* 
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_Ov_ISR_Handler)
{
    /* When a fault occurs, the fault channel is stored in bits [4:0] of the UDB FIFO */
    uint16 ovChan = ((uint16)`$INSTANCE_NAME`_HwComp_F1_REG & `$INSTANCE_NAME`_ENABLE_CONVERTER_NUM_MSK);
    `$INSTANCE_NAME`_faultConfig[ovChan] &= 
       (uint8)(~(`$INSTANCE_NAME`_ENABLE_OV_MASK | `$INSTANCE_NAME`_ENABLE_UV_MASK));
    
    `$INSTANCE_NAME`_OVFaultStatus |= ((1ul) << ovChan);
    
    if (0 != faultCallback)
    {
        /* Adding 1 to convert zero-based channel number to 1-based converter number */
        faultCallback(((uint32)ovChan + 1ul), (uint32)`$INSTANCE_NAME`_OV_MASK);
    }
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ADC_DMA_ISR
***************************************************************************//**
*
* \brief Interrupt Service Routine for the ADC.
*
* \param None
*
* \return None
*
* \sideeffect Starts the DMA chain by triggering the Sample DMA. The ISR 
* disables the ADC's interrupt because it is only meant to happen once. This 
* ensures the ADC has valid results before the DMA starts pulling results from 
* it. The global variable `$INSTANCE_NAME`_isDmaTriggered indicates that the DMA 
* was triggered in this ISR.
* 
*******************************************************************************/
CY_ISR( `$INSTANCE_NAME`_ADC_DMA_ISR )
{
    uint32 intr_status;

    /* Read interrupt status register */
    intr_status = `$INSTANCE_NAME`_ADC_SAR_INTR_REG;
    
    if (0u == `$INSTANCE_NAME`_isDmaTriggered)
    {
        CyDmaTrigger(`$INSTANCE_NAME`_DMA_Sample_CHANNEL);
        `$INSTANCE_NAME`_isDmaTriggered = 1u;
        `$INSTANCE_NAME`_ADC_IRQ_Disable();
    }

    /* Clear handled interrupt */
    `$INSTANCE_NAME`_ADC_SAR_INTR_REG = intr_status;
}

#endif /* `$INSTANCE_NAME`_USE_DMAC */


/* [] END OF FILE */
