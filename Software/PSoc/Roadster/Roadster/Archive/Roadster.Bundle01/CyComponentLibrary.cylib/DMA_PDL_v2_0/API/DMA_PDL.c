/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
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

/* Generated code */
`$DescriptorsInit`
/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME` 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  `$INSTANCE_NAME`_Init() function can be called before the 
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_ChEnable() function.
*/
uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Based on the settings for descriptor in the customizer this function runs the
* DMA_Descriptor_Init() and then initializes the channel using
* DMA_Chnl_Init(). Enables the `$INSTANCE_NAME` block using the DMA_Chnl_Enable().
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void const * srcAddress, void const * dstAddress)
{
    if (0U == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    
    Cy_DMA_Descriptor_SetSrcAddress(&`$FirstDescriprorStuct`, srcAddress);
    Cy_DMA_Descriptor_SetDstAddress(&`$FirstDescriprorStuct`, dstAddress);
    Cy_DMA_Channel_Enable(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Based on the settings for the descriptor in the customizer this function runs the
* DMA_Descriptor_Init() and then initializes the channel using
* DMA_Chnl_Init().
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    cy_stc_dma_channel_config_t channelConfig;

    /* Init all descriptors */
`$DescriptorsInitAPI`

    channelConfig.descriptor  = &`$FirstDescriprorStuct`;
    channelConfig.preemptable = `$INSTANCE_NAME`_PREEMPTABLE;
    channelConfig.priority    = `$INSTANCE_NAME`_PRIORITY;
    channelConfig.enable      = false;
    channelConfig.bufferable  = `$INSTANCE_NAME`_BUFFERABLE;

    (void)Cy_DMA_Channel_Init(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL, &channelConfig);

    Cy_DMA_Enable(`$INSTANCE_NAME`_HW);
}


#if defined(__cplusplus)
}
#endif

/* [] END OF FILE */
