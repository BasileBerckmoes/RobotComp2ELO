/***************************************************************************
* File Name: JoyStickADC_FinalBuf_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <JoyStickADC_FinalBuf_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* JoyStickADC_FinalBuf__DRQ_CTL_REG
* 
* 
* JoyStickADC_FinalBuf__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* JoyStickADC_FinalBuf__NUMBEROF_TDS
* 
* Priority of this channel.
* JoyStickADC_FinalBuf__PRIORITY
* 
* True if JoyStickADC_FinalBuf_TERMIN_SEL is used.
* JoyStickADC_FinalBuf__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* JoyStickADC_FinalBuf__TERMIN_SEL
* 
* 
* True if JoyStickADC_FinalBuf_TERMOUT0_SEL is used.
* JoyStickADC_FinalBuf__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* JoyStickADC_FinalBuf__TERMOUT0_SEL
* 
* 
* True if JoyStickADC_FinalBuf_TERMOUT1_SEL is used.
* JoyStickADC_FinalBuf__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* JoyStickADC_FinalBuf__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of JoyStickADC_FinalBuf dma channel */
uint8 JoyStickADC_FinalBuf_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 JoyStickADC_FinalBuf_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 JoyStickADC_FinalBuf_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    JoyStickADC_FinalBuf_DmaHandle = (uint8)JoyStickADC_FinalBuf__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(JoyStickADC_FinalBuf_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)JoyStickADC_FinalBuf__TERMOUT0_SEL,
                                  (uint8)JoyStickADC_FinalBuf__TERMOUT1_SEL,
                                  (uint8)JoyStickADC_FinalBuf__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(JoyStickADC_FinalBuf_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(JoyStickADC_FinalBuf_DmaHandle, (uint8)JoyStickADC_FinalBuf__PRIORITY);
    
    return JoyStickADC_FinalBuf_DmaHandle;
}

/*********************************************************************
* Function Name: void JoyStickADC_FinalBuf_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with JoyStickADC_FinalBuf.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void JoyStickADC_FinalBuf_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(JoyStickADC_FinalBuf_DmaHandle);
}

