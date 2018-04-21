/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the `$INSTANCE_NAME`
*  component.
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

#if !defined(`$INSTANCE_NAME`_CH_H)
#define `$INSTANCE_NAME`_CH_H

#include "cy_device_headers.h"
#include "cyfitter.h"
#include "dma/cy_dma.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define `$INSTANCE_NAME`_DW_BLOCK                    (`$INSTANCE_NAME`_DW__BLOCK_NUMBER)
#define `$INSTANCE_NAME`_DW_CHANNEL                  (`$INSTANCE_NAME`_DW__CHANNEL_NUMBER)
#define `$INSTANCE_NAME`_HW                          ((DW_Type *) `$INSTANCE_NAME`_DW__BLOCK_HW)

/* Channel settings */
#define `$INSTANCE_NAME`_PRIORITY                    (`$CHANNEL_PRIORITY`u)
#define `$INSTANCE_NAME`_DESCRIPTOR_NUM              (`$NUM_OF_DESCRIPTORS`u)
#define `$INSTANCE_NAME`_PREEMTAMBLE                 (`$PREEMPTABLE`u)

#define `$INSTANCE_NAME`_DW_BLOCK_NUM        (`$INSTANCE_NAME`_DW_BLOCK)
#define `$INSTANCE_NAME`_DW_CHANNEL_NUM      (`$INSTANCE_NAME`_DW_CHANNEL)

/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_Init(void);
__STATIC_INLINE void `$INSTANCE_NAME`_ChEnable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_ChDisable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetDescriptor(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE cy_stc_dma_descr_t* `$INSTANCE_NAME`_GetDescriptor(void);
void `$INSTANCE_NAME`_SetNextDescriptor(const cy_stc_dma_descr_t* descriptor);
cy_stc_dma_descr_t* `$INSTANCE_NAME`_GetNextDescriptor(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetPriority(uint32_t Priority);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetPriority(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetSrcAddress(cy_stc_dma_descr_t* descriptor, const uint32_t* SrcAddress);
__STATIC_INLINE uint32_t* `$INSTANCE_NAME`_GetSrcAddress(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetDstAddress(cy_stc_dma_descr_t* descriptor, const uint32_t* DstAddress);
__STATIC_INLINE uint32_t* `$INSTANCE_NAME`_GetDstAddress(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetDataElementSize(cy_stc_dma_descr_t* descriptor, uint32_t DataSize);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetDataElementSize(const cy_stc_dma_descr_t* descriptor);
void `$INSTANCE_NAME`_SetSrcDstTransferWidth(cy_stc_dma_descr_t* descriptor, uint32_t options);
uint32_t `$INSTANCE_NAME`_GetSrcDstTransferWidth(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetXloopNumDataElements(cy_stc_dma_descr_t* descriptor, uint32_t number);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetXloopNumDataElements(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetXloopSrcIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetXloopSrcIncrement(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetXloopDstIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetXloopDstIncrement(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetYloopNumDataElements(cy_stc_dma_descr_t* descriptor, uint32_t number);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetYloopNumDataElements(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetYloopSrcIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetYloopSrcIncrement(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE void `$INSTANCE_NAME`_SetYloopDstIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetYloopDstIncrement(const cy_stc_dma_descr_t* descriptor);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptCause(void);
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void);


/***************************************
*    Global Variables
***************************************/
extern uint8_t `$INSTANCE_NAME`_initVar;

`$DescriptorsInitHeader`

/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Disables the channel and clears any DMA transfers pending in the channel.
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void)
{
    Cy_DMA_Chnl_DeInit(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ChEnable
****************************************************************************//**
*
* Enables `$INSTANCE_NAME` channel.
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ChEnable(void)
{
    Cy_DMA_Chnl_Enable(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CHDisable
****************************************************************************//**
*
* Disables `$INSTANCE_NAME` channel.
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ChDisable(void)
{
    Cy_DMA_Chnl_Disable(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDescriptor
****************************************************************************//**
*
* Sets a Descriptor as the current descriptor for the `$INSTANCE_NAME` channel.
*
* \param descriptor
* Poiner to a Descriptor structure.
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetDescriptor(const cy_stc_dma_descr_t* descriptor)
{
    Cy_DMA_Chnl_SetDescr(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL, descriptor);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDescriptor
****************************************************************************//**
*
* Returns the pointer to the structure that is the descriptor for the ongoing
* transfer in the `$INSTANCE_NAME`. `$INSTANCE_NAME` channel is disabled while this action is processed.
*
* \return
* Poiner to a Descriptor structure.
*  
*******************************************************************************/
__STATIC_INLINE cy_stc_dma_descr_t* `$INSTANCE_NAME`_GetDescriptor(void)
{
    return(Cy_DMA_Chnl_GetCurrentDescr(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPriority
****************************************************************************//**
*
* Sets priority for the channel.
*
* \param Priority
* Priority of the channel.
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetPriority(uint32_t Priority)
{
    Cy_DMA_Chnl_SetPriority(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL, Priority);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPriority
****************************************************************************//**
*
* Gets the priority of the channel.
*
* \return Priority
* Priority of the channel.
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetPriority(void)
{
    return (Cy_DMA_Chnl_GetPriority(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSrcAddress
****************************************************************************//**
*
* Sets source address for the channel.
*
* \param descriptor
* Descriptor pointer.
*
* \param SrcAddress
* source address.
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetSrcAddress(cy_stc_dma_descr_t* descriptor, const uint32_t* SrcAddress)
{
    Cy_DMA_Descr_SetSrcAddr(descriptor, (const void*)SrcAddress);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSrcAddress
****************************************************************************//**
*
* Gets source address for the channel.
*
* \param descriptor
* Descriptor pointer.
*
* \return
* source address of the channel.
*  
*******************************************************************************/
__STATIC_INLINE uint32_t* `$INSTANCE_NAME`_GetSrcAddress(const cy_stc_dma_descr_t* descriptor)
{
    return((uint32_t*)(descriptor->DESCR_SRC));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDstAddress
****************************************************************************//**
*
* Sets destination address for the channel
*
* \param descriptor
* Descriptor pointer.
*
* \param DstAddress
* destination address.
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetDstAddress(cy_stc_dma_descr_t* descriptor, const uint32_t* DstAddress)
{
    Cy_DMA_Descr_SetDestAddr(descriptor, (const void*)DstAddress);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDstAddress
****************************************************************************//**
*
* Gets destination address for the channel.
*
* \param descriptor
* Descriptor pointer.
*
* \return
* destination address of the channel.
*  
*******************************************************************************/
__STATIC_INLINE uint32_t* `$INSTANCE_NAME`_GetDstAddress(const cy_stc_dma_descr_t* descriptor)
{
    return((uint32_t*)(descriptor->DESCR_DST));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDataElementSize
****************************************************************************//**
*
* Sets the data element size for the Descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param DataSize
* Data element size
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetDataElementSize(cy_stc_dma_descr_t* descriptor, uint32_t DataSize)
{
    descriptor->DESCR_CTL = _CLR_SET_FLD32U(descriptor->DESCR_CTL,
            DW_DESCR_STRUCT_DESCR_CTL_DATA_SIZE, DataSize);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDataElementSize
****************************************************************************//**
*
* Gets the data element size for the Descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* Data element size
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetDataElementSize(const cy_stc_dma_descr_t* descriptor)
{
    return(_FLD2VAL(DW_DESCR_STRUCT_DESCR_CTL_DATA_SIZE, descriptor->DESCR_CTL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetXloopNumDataElements
****************************************************************************//**
*
* Sets the number of data elements for the X loop of the descriptor 
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param number
* Number of data elements
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetXloopNumDataElements(cy_stc_dma_descr_t* descriptor, uint32_t number)
{
    descriptor->DESCR_X_CTL = _CLR_SET_FLD32U(descriptor->DESCR_X_CTL, DW_DESCR_STRUCT_DESCR_X_CTL_X_COUNT, number);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetXloopNumDataElements
****************************************************************************//**
*
* Gets the number of data elements for the X loop of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* Macros set up for the four options
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetXloopNumDataElements(const cy_stc_dma_descr_t* descriptor)
{
    return (_FLD2VAL(DW_DESCR_STRUCT_DESCR_X_CTL_X_COUNT, descriptor->DESCR_X_CTL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetXloopSrcIncrement
****************************************************************************//**
*
* Sets the source increment parameter for the X loop of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param increment
* value of the source increment
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetXloopSrcIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment)
{
    descriptor->DESCR_X_CTL = _CLR_SET_FLD32U(descriptor->DESCR_X_CTL, DW_DESCR_STRUCT_DESCR_X_CTL_SRC_X_INCR, increment);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetXloopSrcIncrement
****************************************************************************//**
*
* Gets the source increment parameter for the X loop of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* value of the source increment
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetXloopSrcIncrement(const cy_stc_dma_descr_t* descriptor)
{
    return (_FLD2VAL(DW_DESCR_STRUCT_DESCR_X_CTL_SRC_X_INCR, descriptor->DESCR_X_CTL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetXloopDstIncrement
****************************************************************************//**
*
* Sets the destination increment parameter for the X loop of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param increment
* value of the destination increment
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetXloopDstIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment)
{
    descriptor->DESCR_X_CTL = _CLR_SET_FLD32U(descriptor->DESCR_X_CTL, DW_DESCR_STRUCT_DESCR_X_CTL_DST_X_INCR, increment);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetXloopDstIncrement
****************************************************************************//**
*
* Gets the destination increment parameter for the X loop of the descriptor 
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* value of the destination increment
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetXloopDstIncrement(const cy_stc_dma_descr_t* descriptor)
{
    return (_FLD2VAL(DW_DESCR_STRUCT_DESCR_X_CTL_DST_X_INCR, descriptor->DESCR_X_CTL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetYloopNumDataElements
****************************************************************************//**
*
* Sets the number of data elements for the Y loop of the descriptor 
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param number
* Number of data elements
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetYloopNumDataElements(cy_stc_dma_descr_t* descriptor, uint32_t number)
{
    descriptor->DESCR_Y_CTL = _CLR_SET_FLD32U(descriptor->DESCR_Y_CTL, DW_DESCR_STRUCT_DESCR_Y_CTL_Y_COUNT, number);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetYloopNumDataElements
****************************************************************************//**
*
* Gets the number of data elements for the Y loop of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* Macros set up for the four options
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetYloopNumDataElements(const cy_stc_dma_descr_t* descriptor)
{
    return (_FLD2VAL(DW_DESCR_STRUCT_DESCR_Y_CTL_Y_COUNT, descriptor->DESCR_Y_CTL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetYloopSrcIncrement
****************************************************************************//**
*
* Sets the source increment parameter for the Y loop of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param increment
* value of the source increment
*  
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetYloopSrcIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment)
{
    descriptor->DESCR_Y_CTL = _CLR_SET_FLD32U(descriptor->DESCR_Y_CTL, DW_DESCR_STRUCT_DESCR_Y_CTL_SRC_Y_INCR, increment);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetYloopSrcIncrement
****************************************************************************//**
*
* Gets the source increment parameter for the outer Y of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* value of the source increment
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetYloopSrcIncrement(const cy_stc_dma_descr_t* descriptor)
{
    return (_FLD2VAL(DW_DESCR_STRUCT_DESCR_Y_CTL_SRC_Y_INCR, descriptor->DESCR_Y_CTL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetYloopDstIncrement
****************************************************************************//**
*
* Sets the destination increment parameter for the Y loop of the descriptor
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \param increment
* value of the destination increment
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetYloopDstIncrement(cy_stc_dma_descr_t* descriptor, uint32_t increment)
{
    descriptor->DESCR_Y_CTL = _CLR_SET_FLD32U(descriptor->DESCR_Y_CTL, DW_DESCR_STRUCT_DESCR_Y_CTL_DST_Y_INCR, increment);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetYloopDstIncrement
****************************************************************************//**
*
* Gets the destination increment parameter for the Y loop of the descriptor 
*
* \param descriptor
* Descriptor for which the data element size is set
*
* \return
* value of the destination increment
*  
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetYloopDstIncrement(const cy_stc_dma_descr_t* descriptor)
{
    return (_FLD2VAL(DW_DESCR_STRUCT_DESCR_Y_CTL_DST_Y_INCR, descriptor->DESCR_Y_CTL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus()
****************************************************************************//**
*
* This function can be used to determine the interrupt status of the
* DMA channel.
*
* \return
* Returns a status of an interrupt for specified channel.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return (Cy_DMA_Chnl_GetInterruptStatus(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptCause
****************************************************************************//**
*
* This function can be used to determine the interrupt reason of the
* DMA channel.
*
* \return
* Returns a status of an interrupt for specified channel.
* - "0": NO_INTR
* - "1": COMPLETION
* - "2": SRC_BUS_ERROR
* - "3": DST_BUS_ERROR
* - "4": SRC_MISAL
* - "5": DST_MISAL
* - "6": CURR_PTR_NULL
* - "7": ACTIVE_CH_DISABLED
* - "8": DESCR_BUS_ERROR
* - "9"-"15": Not used.
*
* For error related interrupt causes (INTR_CAUSE is "1", "2", "3", ..., "8"),
* the channel is disabled (HW sets CH_CTL.ENABLED to '0').
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptCause(void)
{
    return (Cy_DMA_Chnl_GetInterruptCause(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
*
* This function clears the interrupt status.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(void)
{
    Cy_DMA_Chnl_ClearInterrupt(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
*
* This function sets the interrupt.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(void)
{
    Cy_DMA_Chnl_SetInterrupt(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
*
* This function gets interrupt mask value.
*
* \return
* Returns an interrupt mask value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return (Cy_DMA_Chnl_GetInterruptMask(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
****************************************************************************//**
*
* This function sets interrupt mask value.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(void)
{
    Cy_DMA_Chnl_SetInterruptMask(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
****************************************************************************//**
*
* This function returns logical and of corresponding INTR and INTR_MASK fields
* in a single load operation.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return (Cy_DMA_Chnl_GetInterruptStatusMasked(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DW_CHANNEL));
}


#if defined(__cplusplus)
}
#endif

#endif/* (`$INSTANCE_NAME`_CH_H) */

/* [] END OF FILE */
