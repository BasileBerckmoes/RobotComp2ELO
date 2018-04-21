/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the `$INSTANCE_NAME`
*  component
*
* Note:
*  None
*
********************************************************************************
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
* DMA_Descr_Init() and then initializes the channel using
* DMA_Chnl_Init(). Enables the `$INSTANCE_NAME` block using the DMA_Chnl_Enable().
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (0U == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    
    Cy_DMA_Chnl_Enable(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Based on the settings for descriptor in the customizer this function runs the
* DMA_Descr_Init() and then initializes the channel using
* DMA_Chnl_Init().
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    cy_stc_dma_chnl_config_t channelConfig;

    /* Init all descriptors */
`$DescriptorsInitAPI`


    #if (`$INSTANCE_NAME`_DESCRIPTOR_NUM >= 1u)
        channelConfig.DMA_Descriptor = &`$FirstDescriprorStuct`;
        channelConfig.preemptable = `$INSTANCE_NAME`_PREEMTAMBLE;
        channelConfig.priority    = `$INSTANCE_NAME`_PRIORITY;
        channelConfig.enable      = 0u;

        (void)Cy_DMA_Chnl_Init(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL, &channelConfig);
    #endif /* (`$INSTANCE_NAME`_DESCRIPTOR_NUM >= 1u) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetNextDescriptor
****************************************************************************//**
*
* Sets a the next Descriptor for the current descriptor of the DMA channel.
* The DMA channel is disabled while this action is being processed.
*
* \param descriptor
* Poiner to a Descriptor structure.
*  
*******************************************************************************/
void `$INSTANCE_NAME`_SetNextDescriptor(const cy_stc_dma_descr_t* descriptor)
{
    Cy_DMA_Descr_SetNxtDescr(Cy_DMA_Chnl_GetCurrentDescr(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL), descriptor);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextDescriptor
****************************************************************************//**
*
* Sets a the next Descriptor for the current descriptor of the DMA channel.
* The DMA channel is disabled while this action is being processed.
*
* \return descriptor
* Poiner to a Descriptor structure.
*  
*******************************************************************************/
cy_stc_dma_descr_t* `$INSTANCE_NAME`_GetNextDescriptor(void)
{
    DW_DESCR_STRUCT_Type* currentDescriptor = Cy_DMA_Chnl_GetCurrentDescr(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
    
    return((DW_DESCR_STRUCT_Type*)currentDescriptor->DESCR_NEXT_PTR);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSrcDstTransferWidth
****************************************************************************//**
*
* Sets the transfer width for source and destination transfer widths of
* the Descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param options
* Macros set up for the four options
*  
*******************************************************************************/
void `$INSTANCE_NAME`_SetSrcDstTransferWidth(cy_stc_dma_descr_t* descriptor, uint32_t options)
{
    uint32_t ctlRegVal = descriptor->DESCR_CTL & ((uint32_t)~(DW_DESCR_STRUCT_DESCR_CTL_SRC_TRANSFER_SIZE_Msk | \
            DW_DESCR_STRUCT_DESCR_CTL_DST_TRANSFER_SIZE_Msk));
    
    descriptor->DESCR_CTL = ctlRegVal |
        ((options << DW_DESCR_STRUCT_DESCR_CTL_SRC_TRANSFER_SIZE_Pos) &
        (DW_DESCR_STRUCT_DESCR_CTL_SRC_TRANSFER_SIZE_Msk | DW_DESCR_STRUCT_DESCR_CTL_DST_TRANSFER_SIZE_Msk));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSrcDstTransferWidth
****************************************************************************//**
*
* Gets the transfer width for source and destination transfer widths of
* the Descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* Macros set up for the four options
*  
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_GetSrcDstTransferWidth(const cy_stc_dma_descr_t* descriptor)
{
    uint32_t ctlRegVal = descriptor->DESCR_CTL & (DW_DESCR_STRUCT_DESCR_CTL_SRC_TRANSFER_SIZE_Msk |
        DW_DESCR_STRUCT_DESCR_CTL_DST_TRANSFER_SIZE_Msk);
    
    return(ctlRegVal >> DW_DESCR_STRUCT_DESCR_CTL_SRC_TRANSFER_SIZE_Pos);
}


#if defined(__cplusplus)
}
#endif

/* [] END OF FILE */
