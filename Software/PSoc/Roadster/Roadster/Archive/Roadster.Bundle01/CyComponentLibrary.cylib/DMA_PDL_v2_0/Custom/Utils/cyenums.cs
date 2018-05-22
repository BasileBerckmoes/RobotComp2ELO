/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System.ComponentModel;

namespace DMA_PDL_v2_0.Utils
{
    public enum CyEPropertyIdEnum
    {
        None,
        DescriptorName,
        TriggerInputType,
        TriggerDeactivationAndRetriggering,
        DataElementSize,
        SourceAndDestinationTransferWidth,
        NumberOfDataElementsToTransfer,
        SourceIncrementEveryCycleByX,
        DestinationIncrementEveryCycleByX,
        NumberOfXLoopsToExecute,
        SourceIncrementEveryCycleByY,
        DestinationIncrementEveryCycleByY,
        TriggerOutput,
        Interrupt,
        ChainToDescriptor,
        ChannelStateOnCompletion
    }

    public enum CyEnDisEnum
    {
        Disable,
        Enable
    }

    public enum CyDescriptorTypesEnum
    {
        [Description(CyTextConst.SingleTransfer)]
        CY_DMA_SINGLE_TRANSFER,
        [Description(CyTextConst.OneDimensionTransfer)]
        CY_DMA_1D_TRANSFER,
        [Description(CyTextConst.TwoDimensionTransfer)]
        CY_DMA_2D_TRANSFER
    }
    
    public enum CyTriggerInputTypesEnum
    {
        [Description(CyTextConst.OneTransferPerTrigger)]
        CY_DMA_INTR_1ELEMENT_CMPLT,
        [Description(CyTextConst.OneXLoopTransferPerTrigger)]
        CY_DMA_INTR_X_LOOP_CMPLT,
        [Description(CyTextConst.AnEntireDescriptorTransferPerTrigger)]
        CY_DMA_INTR_DESCR_CMPLT,
        [Description(CyTextConst.EntireDescriptorChainPerTrigger)]
        CY_DMA_INTR_DESCRCHAIN_CMPLT
    }

    public enum CyTriggerDeactivationAndRetriggeringEnum
    {
        [Description(CyTextConst.RetriggerImmediately)]
        CY_DMA_RETDIG_IM,
        [Description(CyTextConst.RetriggerAfter4Sysclkcycles)]
        CY_DMA_RETDIG_4CYC,
        [Description(CyTextConst.RetriggerAfter16SysclkCycles)]
        CY_DMA_RETDIG_16CYC,
        [Description(CyTextConst.WaitForTriggerReactivation)]
        CY_DMA_WAIT_FOR_REACT
    }

    public enum CyDataElementSizeEnum
    {
        [Description(CyTextConst.Byte)]
        CY_DMA_BYTE,
        [Description(CyTextConst.Halfword)]
        CY_DMA_HALFWORD,
        [Description(CyTextConst.Word)]
        CY_DMA_WORD
    }

    public enum CySourceAndDestinationTransferWidthEnum
    {
        [Description(CyTextConst.ByteToByte)]
        ByteToByte,
        [Description(CyTextConst.HalfwordToHalfword)]
        HalfwordToHalfword,
        [Description(CyTextConst.WordToByte)]
        WordToByte,
        [Description(CyTextConst.WordToHalfword)]
        WordToHalfword,
        [Description(CyTextConst.ByteToWord)]
        ByteToWord,
        [Description(CyTextConst.HalfwordToWord)]
        HalfwordToWord,
        [Description(CyTextConst.WordToWord)]
        WordToWord
    }

    public enum CyInterruptOrTriggerOutputEnum
    {
        [Description(CyTextConst.TriggerOnEveryElementTransferCompletion)]
        CY_DMA_TRIGOUT_1ELEMENT_CMPLT,
        [Description(CyTextConst.TriggerOnEveryXLoopTransferCompletion)]
        CY_DMA_TRIGOUT_X_LOOP_CMPLT,
        [Description(CyTextConst.TriggerOnDescriptorCompletion)]
        CY_DMA_INTR_DESCR_CMPLT,
        [Description(CyTextConst.TriggerOnCompletionOfEntireDescriptorChain)]
        CY_DMA_INTR_DESCRCHAIN_CMPLT
    }


}
