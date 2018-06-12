/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides DMA channel defines and API function definitions.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_DMA_CHANNEL_`$INSTANCE_NAME`_H
#define CY_DMA_CHANNEL_`$INSTANCE_NAME`_H

#include "CyDMA.h"

    
/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_CHANNEL           (`$INSTANCE_NAME`__CHANNEL_NUMBER)
#define `$INSTANCE_NAME`_CHANNEL_MASK      ((uint32)(1UL << `$INSTANCE_NAME`_CHANNEL))


/***************************************
*        Function Prototypes
***************************************/

/* Functions specific to this DMA channel */
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Start(void * srcAddress, void * dstAddress);

/* Inline functions that call global API functions */
static void   `$INSTANCE_NAME`_ChEnable(void);
static void   `$INSTANCE_NAME`_ChDisable(void);
static void   `$INSTANCE_NAME`_Trigger(void);
static void   `$INSTANCE_NAME`_SetPriority(int32 priority);
static int32  `$INSTANCE_NAME`_GetPriority(void);
static void   `$INSTANCE_NAME`_SetNextDescriptor(int32 descriptor);
static int32  `$INSTANCE_NAME`_GetNextDescriptor(void);
static void   `$INSTANCE_NAME`_SetConfiguration(int32 descriptor, const cydma_init_struct * config);
static void   `$INSTANCE_NAME`_ValidateDescriptor(int32 descriptor);
static uint32 `$INSTANCE_NAME`_GetDescriptorStatus(int32 descriptor);
static void   `$INSTANCE_NAME`_SetSrcAddress(int32 descriptor, void * srcAddress);
static void * `$INSTANCE_NAME`_GetSrcAddress(int32 descriptor);
static void   `$INSTANCE_NAME`_SetDstAddress(int32 descriptor, void * dstAddress);
static void * `$INSTANCE_NAME`_GetDstAddress(int32 descriptor);
static void   `$INSTANCE_NAME`_SetDataElementSize(int32 descriptor, uint32 dataElementSize);
static uint32 `$INSTANCE_NAME`_GetDataElementSize(int32 descriptor);
static void   `$INSTANCE_NAME`_SetNumDataElements(int32 descriptor, int32 numDataElements);
static int32  `$INSTANCE_NAME`_GetNumDataElements(int32 descriptor);
static void   `$INSTANCE_NAME`_SetSrcDstTransferWidth(int32 descriptor, uint32 transferWidth);
static uint32 `$INSTANCE_NAME`_GetSrcDstTransferWidth(int32 descriptor);
static void   `$INSTANCE_NAME`_SetAddressIncrement(int32 descriptor, uint32 addressIncrement);
static uint32 `$INSTANCE_NAME`_GetAddressIncrement(int32 descriptor);
static void   `$INSTANCE_NAME`_SetTriggerType(int32 descriptor, uint32 triggerType);
static uint32 `$INSTANCE_NAME`_GetTriggerType(int32 descriptor);
static void   `$INSTANCE_NAME`_SetTransferMode(int32 descriptor, uint32 transferMode);
static uint32 `$INSTANCE_NAME`_GetTransferMode(int32 descriptor);
static void   `$INSTANCE_NAME`_SetPreemptable(int32 descriptor, uint32 preemptable);
static uint32 `$INSTANCE_NAME`_GetPreemptable(int32 descriptor);
static void   `$INSTANCE_NAME`_SetPostCompletionActions(int32 descriptor, uint32 actions);
static uint32 `$INSTANCE_NAME`_GetPostCompletionAction(int32 descriptor);
static cydma_callback_t `$INSTANCE_NAME`_SetInterruptCallback(cydma_callback_t callback);
static cydma_callback_t `$INSTANCE_NAME`_GetInterruptCallback(void);


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ChEnable
********************************************************************************
*
* Summary:
*  Enables the DMA channel. It is not necessary to call `$INSTANCE_NAME`_ChEnable()
*  because the `$INSTANCE_NAME`_Start() API calls this function, which is the
*  preferred method to begin the component operation.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  If this function is called before `$INSTANCE_NAME`_Start(), or `$INSTANCE_NAME`_Init()
*  or `$INSTANCE_NAME`_SetConfiguration(), and `$INSTANCE_NAME`_SetSrcAddress()
*  and `$INSTANCE_NAME`_SetDstAddress the operation of the DMA is 
*  undefined and could result in system data corruption. 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_ChEnable(void)
{
    CyDmaChEnable(`$INSTANCE_NAME`_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ChDisable
********************************************************************************
*
* Summary:
*  Disables the DMA channel.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  If this function is called during a DMA transfer the transfer is aborted. 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_ChDisable(void)
{
    CyDmaChDisable(`$INSTANCE_NAME`_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Trigger
********************************************************************************
*
* Summary:
*  Triggers the DMA channel, this is useful only for software triggers. This is
*  not needed when hardware triggers are used.
*
* Parameters:
*  None.
*                   
* Return:
*  None. 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_Trigger(void)
{
    CyDmaTrigger(`$INSTANCE_NAME`_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPriority
********************************************************************************
*
* Summary:
*  Sets the priority for the channel.
*
* Parameters:
*  priority: Priority for channel. Priority can be 0,1,2, or 3.
*            0 is the highest priority.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called while the channel is enabled.
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetPriority(int32 priority)
{
    CyDmaSetPriority(`$INSTANCE_NAME`_CHANNEL, priority);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPriority
********************************************************************************
*
* Summary:
*  Gets the priority for the channel.
*
* Parameters:
*  None.
*                   
* Return:
*  Priority for channel. Priority can be 0,1,2, or 3. 0 is the highest priority.
*
*******************************************************************************/
static CY_INLINE int32 `$INSTANCE_NAME`_GetPriority(void)
{
    return (CyDmaGetPriority(`$INSTANCE_NAME`_CHANNEL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetNextDescriptor
********************************************************************************
*
* Summary:
*  Sets the descriptor that should be run the next time the channel is
*  triggered.
*
* Parameters:
*  descriptor: Next Descriptor to run (0 or 1).
*                   
* Side effect:
*  This function should not be called while the channel is enabled.
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetNextDescriptor(int32 descriptor)
{
    CyDmaSetNextDescriptor(`$INSTANCE_NAME`_CHANNEL, descriptor);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextDescriptor
********************************************************************************
*
* Summary:
*  Returns the next descriptor that should be run, as set by 
*  `$INSTANCE_NAME`_SetNextDescriptor().
*
* Parameters:
*  None.
*                   
* Return:
*  Next Descriptor to run (0 or 1).
*
*******************************************************************************/
static CY_INLINE int32 `$INSTANCE_NAME`_GetNextDescriptor(void)
{
    return (CyDmaGetNextDescriptor(`$INSTANCE_NAME`_CHANNEL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetConfiguration
********************************************************************************
*
* Summary:
*  Sets configuration information for the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  config: Pointer to a configuration structure. Refer to cydma_init_struct
*          structure definition in CyDMA_P4.h or the component datasheet.
*                   
* Return:
*  None.
*
* Side effect:
*  The status register associated with the specified descriptor is reset to
*  zero after this function call. This function also validates the descriptor.
*  This function should not be called while the descriptor is active.
*  This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetConfiguration(int32 descriptor, const cydma_init_struct * config)
{
    CyDmaSetConfiguration(`$INSTANCE_NAME`_CHANNEL, descriptor, config);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ValidateDescriptor
********************************************************************************
*
* Summary:
*  Validates the specified descriptor after it has been invalidated.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  None. 
*
* Side effect:
*  The status register associated with the specified descriptor is reset to
*  zero after this function call. This function should not be called while the
*  descriptor is active. This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_ValidateDescriptor(int32 descriptor)
{
    CyDmaValidateDescriptor(`$INSTANCE_NAME`_CHANNEL, descriptor);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDescriptorStatus
********************************************************************************
*
* Summary:
*  Returns the status of the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Returns the contents of the specified descriptors status register. Refer to 
*  descriptor status register bit definitions in CyDMA_P4.h or the API
*  description in the DMA channel datasheet for more information.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetDescriptorStatus(int32 descriptor)
{
    return (CyDmaGetDescriptorStatus(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSrcAddress
********************************************************************************
*
* Summary:
*  Configures the source address for the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  srcAddress: Address of DMA transfer source.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetSrcAddress(int32 descriptor, void * srcAddress)
{
    CyDmaSetSrcAddress(`$INSTANCE_NAME`_CHANNEL, descriptor, srcAddress);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSrcAddress
********************************************************************************
*
* Summary:
*  Returns the source address for the specified descriptor, set by either 
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_SetSrcAddress().
*
* Parameters:
*  descriptor: Specifies descriptor (0 or 1) used by this function.
*                   
* Return:
*  Source address written to specified descriptor.
*
*******************************************************************************/
static CY_INLINE void * `$INSTANCE_NAME`_GetSrcAddress(int32 descriptor)
{
    return (CyDmaGetSrcAddress(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDstAddress
********************************************************************************
*
* Summary:
*  Configures the destination address for the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  dstAddress: Address of DMA transfer destination.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetDstAddress(int32 descriptor, void * dstAddress)
{
    CyDmaSetDstAddress(`$INSTANCE_NAME`_CHANNEL, descriptor, dstAddress);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDstAddress
********************************************************************************
*
* Summary:
*  Returns the destination address for the specified descriptor, set by either 
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_SetDstAddress().
*
* Parameters:
*  descriptor: Specifies descriptor (0 or 1) used by this function.
*                   
* Return:
*  Destination address written to specified descriptor.
*
*******************************************************************************/
static CY_INLINE void * `$INSTANCE_NAME`_GetDstAddress(int32 descriptor)
{
    return (CyDmaGetDstAddress(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDataElementSize
********************************************************************************
*
* Summary:
*  Sets the data element size for the specified descriptor.
*
* Parameters:
*  descriptor:      Descriptor (0 or 1) modified by this function.
*  dataElementSize: Specifies the size of the data element. The DMA transfer
*                   engine transfers one data element at a time. How these
*                   transfers occur is controlled by the transfer mode.
*                   Refer to the API bit field definitions in CyDMA_P4.h or API
*                   description in the DMA channel datasheet for the parameter
*                   options.
*
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetDataElementSize(int32 descriptor, uint32 dataElementSize)
{
    CyDmaSetDataElementSize(`$INSTANCE_NAME`_CHANNEL, descriptor, dataElementSize);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDataElementSize
********************************************************************************
*
* Summary:
*  Returns the data element size configured for the specified descriptor, set by
*  `$INSTANCE_NAME`_SetDataElementSize() or `$INSTANCE_NAME`_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  The size of the data element. The DMA transfer engine transfers one data
*  element at a time. How these transfers occur is controlled by the transfer
*  mode. Refer to the API bit field definitions in CyDMA_P4.h or the API 
*  description in the DMA channel datasheet for more information.
*
* Note:
*  The size of the source and destination can be configured to use the
*  data element size, or a Word, this is set in `$INSTANCE_NAME`_SetSrcDstTransferWidth().
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetDataElementSize(int32 descriptor)
{
    return (CyDmaGetDataElementSize(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetNumDataElements
********************************************************************************
*
* Summary:
*  Sets the number of data elements to transfer for specified descriptor.
*
* Parameters:
*  descriptor:      Descriptor (0 or 1) modified by this function.
*  numDataElements: Total number of data elements this descriptor transfers.
*                   Valid ranges are 1 to 65536.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetNumDataElements(int32 descriptor, int32 numDataElements)
{
    CyDmaSetNumDataElements(`$INSTANCE_NAME`_CHANNEL, descriptor, numDataElements);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumDataElements
********************************************************************************
*
* Summary:
*  Returns the number of data elements to be transferred. Only reflects the
*  value written by `$INSTANCE_NAME`_SetNumDataElements() or `$INSTANCE_NAME`_SetConfiguration().
*  This does not reflect how many elements have been transferred. For that
*  information use the `$INSTANCE_NAME`_GetDescriptorStatus() function.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Number of data elements to transfer.
*
*******************************************************************************/
static CY_INLINE int32 `$INSTANCE_NAME`_GetNumDataElements(int32 descriptor)
{
    return (CyDmaGetNumDataElements(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSrcDstTransferWidth
********************************************************************************
*
* Summary:
*  Sets the width of the source and destination. The DMA can either read and
*  write data from the source and destination at the size specified by
*  `$INSTANCE_NAME`_SetDataElementSize() or by a word (4bytes). This also determines how
*  many bytes the addresses are incremented if increment source and destination
*  address are turned on.
*
* Parameters:
*  descriptor:    Descriptor (0 or 1) modified by this function.
*  transferWidth: Specifies the source and destination widths. Refer to the API
*                 bit field definitions in CyDMA_P4.h or the API description in
*                 the DMA channel datasheet for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetSrcDstTransferWidth(int32 descriptor, uint32 transferWidth)
{
    CyDmaSetSrcDstTransferWidth(`$INSTANCE_NAME`_CHANNEL, descriptor, transferWidth);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSrcDstTransferWidth
********************************************************************************
*
* Summary:
*  Returns the width of the source and destination, as set by 
*  `$INSTANCE_NAME`_SetSrcDstTransferWidth() or `$INSTANCE_NAME`_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Width of source and destination. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetSrcDstTransferWidth(int32 descriptor)
{
    return (CyDmaGetSrcDstTransferWidth(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAddressIncrement
********************************************************************************
*
* Summary:
*  Sets whether the source or destination addresses are incremented after the
*  transfer of each data element. The amount that the source and destination
*  address are incremented is determined by the `$INSTANCE_NAME`_SetSrcDstTransferWidth()
*  function. The addresses will either be incremented by the data element size
*  or by a word (4 bytes).
*
* Parameters:
*  descriptor:       Descriptor (0 or 1) modified by this function.
*  addressIncrement: Address increment settings. Refer to the API bit field
*                    definitions in CyDMA_P4.h or the API description in the DMA
*                    channel datasheet for the parameter options.
*    
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetAddressIncrement(int32 descriptor, uint32 addressIncrement)
{
    CyDmaSetAddressIncrement(`$INSTANCE_NAME`_CHANNEL, descriptor, addressIncrement);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAddressIncrement
********************************************************************************
*
* Summary:
*  Returns address increment settings as set by `$INSTANCE_NAME`_SetAddressIncrement()
*  or `$INSTANCE_NAME`_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Address increment settings. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetAddressIncrement(int32 descriptor)
{
    return (CyDmaGetAddressIncrement(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTriggerType
********************************************************************************
*
* Summary:
*  Sets the type of input trigger for the DMA For level sensitive triggers sets
*  how long the DMA waits for the trigger to go low (deactivate) before
*  triggering the channel again.
*
* Parameters:
*  descriptor:  Descriptor (0 or 1) modified by this function.
*  triggerType: Type of DMA trigger. Refer to the API bit field definitions in
*               CyDMA_P4.h or the API description in the DMA channel datasheet
*               for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetTriggerType(int32 descriptor, uint32 triggerType)
{
    CyDmaSetTriggerType(`$INSTANCE_NAME`_CHANNEL, descriptor, triggerType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTriggerType
********************************************************************************
*
* Summary:
*  Returns the trigger deactivation settings as set by `$INSTANCE_NAME`_SetTriggerType()
*  or `$INSTANCE_NAME`_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Trigger deactivation settings. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetTriggerType(int32 descriptor)
{
    return (CyDmaGetTriggerType(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTransferMode
********************************************************************************
*
* Summary:
*  Sets the DMA transfer mode. This determines how the DMA reacts to each trigger
*  event.
*
* Parameters:
*  descriptor:   Descriptor (0 or 1) modified by this function.
*  transferMode: Specifies the DMA transfer mode settings. Refer to the API bit
*                field definitions in CyDMA_P4.h or the API description in the
*                DMA channel datasheet for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetTransferMode(int32 descriptor, uint32 transferMode)
{
    CyDmaSetTransferMode(`$INSTANCE_NAME`_CHANNEL, descriptor, transferMode);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTransferMode
********************************************************************************
*
* Summary:
*  Returns the transfer mode for the specified descriptor as set by 
*  `$INSTANCE_NAME`_SetTransferMode() or `$INSTANCE_NAME`_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  DMA transfer mode settings. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetTransferMode(int32 descriptor)
{
    return (CyDmaGetTransferMode(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPreemptable
********************************************************************************
*
* Summary:
*  Determines if the descriptor is preemptable.
*
* Parameters:
*  descriptor:  Descriptor (0 or 1) modified by this function.
*  preemptable: Descriptor preemption settings. Refer to the API bit field
*               definitions in CyDMA_P4.h or the API description in the DMA 
*               channel datasheet for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetPreemptable(int32 descriptor, uint32 preemptable)
{
    CyDmaSetPreemptable(`$INSTANCE_NAME`_CHANNEL, descriptor, preemptable);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPreemptable
********************************************************************************
*
* Summary:
*  Returns whether or not the descriptor is preemptable.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Descriptor preemption setting. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetPreemptable(int32 descriptor)
{
    return (CyDmaGetPreemptable(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPostCompletionActions
********************************************************************************
*
* Summary:
*  Determines what occurs after a descriptor completes.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  actions:    Specifies descriptor post completion actions. Refer to the API
*              bit field definitions in CyDMA_P4.h or the API description in the
*              DMA channel datasheet for the parameter options.
*                   
* Return:
*  None.  
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_SetPostCompletionActions(int32 descriptor, uint32 actions)
{
    CyDmaSetPostCompletionActions(`$INSTANCE_NAME`_CHANNEL, descriptor, actions);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPostCompletionAction
********************************************************************************
*
* Summary:
*  Returns the post descriptor action settings as set by 
*  `$INSTANCE_NAME`_SetPostCompletionActions() or `$INSTANCE_NAME`_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Post descriptor actions. Refer to the API bit field definitions in CyDMA_P4.h
*  or the API description in the DMA channel datasheet for more information.
*
*******************************************************************************/
static CY_INLINE uint32 `$INSTANCE_NAME`_GetPostCompletionAction(int32 descriptor)
{
    return (CyDmaGetPostCompletionActions(`$INSTANCE_NAME`_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptCallback
********************************************************************************
*
* Summary:
*  Sets a user defined callback function to be called by the DMA interrupt. The
*  function should contain code to process the interrupt request for the 
*  associated DMA channel.
*
* Parameters:
*  callback: Pointer to the user defined callback function.
*
* Return:
*  Pointer to the function previously set for the specified channel. 
*
*******************************************************************************/
static CY_INLINE cydma_callback_t `$INSTANCE_NAME`_SetInterruptCallback(cydma_callback_t callback)
{
    return (CyDmaSetInterruptCallback(`$INSTANCE_NAME`_CHANNEL, callback));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptCallback
********************************************************************************
*
* Summary:
*  Returns the pointer to the interrupt callback function for the specified DMA
*  channel.
*
* Parameters:
*  None.
*
* Return:
*  Callback function pointer for the specified channel.
*
*******************************************************************************/
static CY_INLINE cydma_callback_t `$INSTANCE_NAME`_GetInterruptCallback(void)
{    
    return (CyDmaGetInterruptCallback(`$INSTANCE_NAME`_CHANNEL));
}


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_CHANNEL_CFG           (`$ChanConfig`)
#define `$INSTANCE_NAME`_DESCR0_CFG            (`$Td0Config`)
#define `$INSTANCE_NAME`_DESCR1_CFG            (`$Td1Config`)


#endif /* CY_DMA_CHANNEL_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
