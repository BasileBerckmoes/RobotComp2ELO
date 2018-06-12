/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;

namespace DMA_PDL_v2_0.Utils
{
    public static class CyTextConst
    {
        #region Customizer constants
        public const string INSTANCE_NAME_DMA_PDL = "DMA_PDL";

        // NOTE: not localizable - tab names should match "Category" field
        // of the corresponding symbol parameters (for correct expression view)
        public const string TAB_NAME_BASIC = "Basic";
        public const string TAB_NAME_DESCRIPTORS = "Descriptors";
        public const string TAB_NAME_BUILTIN = "Built-in";
        #endregion

        #region Property grid categories names
        public const string CATEGORY_DESCRIPTOR = "Descriptor";
        public const string CATEGORY_TRIGGER_INPUT_TYPE = "Input trigger options";
        public const string CATEGORY_TRANSFER_SETTING = "Transfer setting";
        public const string CATEGORY_X_LOOP_TRANSFER = "X loop transfer";
        public const string CATEGORY_Y_LOOP_TRANSFER = "Y loop transfer";
        #endregion

        #region Property grid properties names
        public const string DESCRIPTOR_NAME = "Descriptor Name";
        public const string TRIGGER_INPUT_TYPE = "Trigger input type";
        public const string TRIGGER_DEACTIVATION_AND_RETRIGGERING = "Trigger deactivation and retriggering";
        public const string CHAIN_TO_DESCRIPTOR = "Chain to descriptor";
        public const string CHANNEL_STATE_ON_COMPLETION = "Channel state on completion";
        public const string DATA_ELEMENT_SIZE = "Data element size";
        public const string SOURCE_AND_DESTINATION_TRANSFER_WIDTH = "Source and destination transfer width";
        public const string NUMBER_OF_DATA_ELEMENTS_TO_TRANSFER = "Number of data elements to transfer";
        public const string NUMBER_OF_X_LOOPS_TO_EXECUTE = "Number of X-loops to execute";
        public const string SOURCE_INCREMENT_EVERY_CYCLE_BY = "Source increment every cycle by ";
        public const string DESTINATION_INCREMENT_EVERY_CYCLE_BY = "Destination increment every cycle by ";
        public const string TRIGGER_OUTPUT = "Trigger output";
        public const string INTERRUPT = "Interrupt";
        #endregion

        #region Property grid units
        public const string UNIT_BYTES = "(Byte)";
        public const string UNIT_WORDS = "(Word)";
        public const string UNIT_HALFWORDS = "(Halfword)";
        #endregion

        #region Transfer size
        public const string DMA_BYTE = "DMA_BYTE";
        public const string DMA_HALFWORD = "DMA_HALFWORD";
        public const string DMA_WORD = "DMA_WORD";
        public const string CY_DMA_UNKNOWN_SIZE = "Unhandled transfer size";
        public const string CY_DMA_XFER_SIZE_DATA = "CY_DMA_TRANSFER_SIZE_DATA";
        public const string CY_DMA_XFER_SIZE_WORD = "CY_DMA_TRANSFER_SIZE_WORD";
        #endregion
        
        #region Descriptor type
        public const string CY_DMA_SINGLE_TRANSFER = "CY_DMA_SINGLE_TRANSFER";
        public const string CY_DMA_1D_TRANSFER = "CY_DMA_1D_TRANSFER";
        public const string CY_DMA_2D_TRANSFER = "CY_DMA_2D_TRANSFER";
        #endregion

        #region Property grid properties description
        public const string DESCRIPTION_DESCRIPTOR_NAME =
            "This parameter sets up the instance name for the descriptor.";
        public const string DESCRIPTION_TRIGGER_INPUT_TYPE =
            "Trigger input type will set up the character of each trigger";
        public const string DESCRIPTION_TRIGGER_DEACTIVATION_AND_RETRIGGERING =
            "This parameter sets up the trigger deactivation options for the descriptor.";
        public const string DESCRIPTION_CHAIN_TO_DESCRIPTOR =
            "";
        public const string DESCRIPTION_CHANNEL_STATE_ON_COMPLETION =
            "This is the state of the channel when the descriptor is completed";
        public const string DESCRIPTION_DATA_ELEMENT_SIZE =
            "This parameter sets up the data element size parameter in the descriptor.";
        public const string DESCRIPTION_SOURCE_AND_DESTINATION_TRANSFER_WIDTH =
            "This sets up the source and destination transfer size parameters.";
        public const string DESCRIPTION_NUMBER_OF_DATA_ELEMENTS_TO_TRANSFER =
            "This parameter is available for the X loop setting. This parameter configures how many transfers are effected in each X loop.";
        public const string DESCRIPTION_NUMBER_OF_X_LOOPS_TO_EXECUTE =
            "This parameter is available for the Y loop setting. This parameter configures how many X-loops are effected in each Y loop.";
        public const string DESCRIPTION_SOURCE_INCREMENT_EVERY_CYCLE_BY =
            "This integer determines the source address increment after each transfer. When this value is set to zero, it is equivalent to disabling the source increment feature.";
        public const string DESCRIPTION_DESTINATION_INCREMENT_EVERY_CYCLE_BY =
            "This integer determines the destination address increment after each transfer. When this value is set to zero, it is equivalent to disabling the destination increment feature.";
        public const string DESCRIPTION_TRIGGER_OUTPUT =
            "This is the selection for what event would trigger the DMA output.";
        public const string DESCRIPTION_INTERRUPT =
            "This is the selection for what event would trigger the DMA interrupt.";
        #endregion


        #region Property grid properties values

        
        //enum DescriptorTypesEnum
        public const string SingleTransfer = "Single transfer";
        public const string OneDimensionTransfer = "1D transfer";
        public const string TwoDimensionTransfer = "2D transfer";
        
        //enum TriggerInputTypesEnum
        public const string OneTransferPerTrigger = "One transfer per trigger";
        public const string OneXLoopTransferPerTrigger = "One X loop transfer per trigger";
        public const string AnEntireDescriptorTransferPerTrigger = "An entire descriptor transfer per trigger";
        public const string EntireDescriptorChainPerTrigger = "Entire descriptor chain per trigger";

        //enum TriggerDeactivationAndRetriggeringEnum
        public const string RetriggerImmediately = "Retrigger immediately (pulse trigger)";
        public const string RetriggerAfter4Sysclkcycles = "Retrigger after 4 Clk_Slow cycles";
        public const string RetriggerAfter16SysclkCycles = "Retrigger after 16 Clk_Slow cycles";
        public const string WaitForTriggerReactivation = "Wait for trigger reactivation";

        //enum DataElementSizeEnum
        public const string Byte = "Byte";
        public const string Halfword = "Halfword (2 bytes)";
        public const string Word = "Word (4 bytes)";

        //enum SourceAndDestinationTransferWidthEnum
        public const string ByteToByte = "Byte to Byte";
        public const string HalfwordToHalfword = "Halfword to Halfword";
        public const string WordToByte = "Word to Byte";
        public const string WordToHalfword = "Word to Halfword";
        public const string ByteToWord = "Byte to Word";
        public const string HalfwordToWord = "Halfword to Word";
        public const string WordToWord = "Word to Word";

        //enum InterruptOrTriggerOutput
        public const string TriggerOnEveryElementTransferCompletion = "Trigger on every element transfer completion";
        public const string TriggerOnEveryXLoopTransferCompletion = "Trigger on every X loop transfer completion";
        public const string TriggerOnDescriptorCompletion = "Trigger on descriptor completion";
        public const string TriggerOnCompletionOfEntireDescriptorChain = "Trigger on completion of entire descriptor chain";

        #endregion
    }
}
