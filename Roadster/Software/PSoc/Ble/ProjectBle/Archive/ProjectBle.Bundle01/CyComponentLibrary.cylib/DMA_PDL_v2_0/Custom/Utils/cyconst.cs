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
    public static class CyConst
    {
        public const string C_DESCRIPTOR_NAME_DEF = "";
        public const string C_CHAIN_TO_DESCRIPTOR_DEF = "Nothing";
        public const CyEnDisEnum C_CHANNEL_STATE_ON_COMPLETION_DEF = CyEnDisEnum.Enable;
        public const CyTriggerInputTypesEnum C_TRIGGER_INPUT_TYPE_DEF =
            CyTriggerInputTypesEnum.CY_DMA_INTR_1ELEMENT_CMPLT;
        public const CyTriggerDeactivationAndRetriggeringEnum C_TRIGGER_DEACTIVATION_AND_RETRIGGERING_DEF =
            CyTriggerDeactivationAndRetriggeringEnum.CY_DMA_RETDIG_IM;
        public const CyInterruptOrTriggerOutputEnum C_TRIGGER_OUTPUT_DEF =
            CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_1ELEMENT_CMPLT;
        public const CyInterruptOrTriggerOutputEnum C_INTERRUPT_DEF =
            CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_1ELEMENT_CMPLT;
        public const CyDataElementSizeEnum C_DATA_ELEMENT_SIZE_DEF =
            CyDataElementSizeEnum.CY_DMA_WORD;
        public const CySourceAndDestinationTransferWidthEnum C_SOURCE_AND_DESTINATION_TRANSFER_WIDTH_DEF =
            CySourceAndDestinationTransferWidthEnum.WordToWord;
        public static readonly CyRange R_NUMBER_OF_DESCRIPTORS_DEF =
            new CyRange(1, 1, 255);
        public const int C_CATEGORY_LOOP_TRANSFER_DEF = 1;
        public const UInt16 C_CATEGORY_LOOP_TRANSFER_UINT16_DEF = 1;

        public static readonly CyRange R_NUMBER_OF_DATA_ELEMENTS_TO_TRANSFER =
            new CyRange(C_CATEGORY_LOOP_TRANSFER_UINT16_DEF, 1, 256);
        public static readonly CyRange R_SOURCE_INCREMENT_EVERY_CYCLE_BY_X =
            new CyRange(C_CATEGORY_LOOP_TRANSFER_DEF, -2048, 2047);
        public static readonly CyRange R_DESTINATION_INCREMENT_EVERY_CYCLE_BY_X =
            new CyRange(C_CATEGORY_LOOP_TRANSFER_DEF, -2048, 2047);
        public static readonly CyRange R_NUMBER_OF_X_LOOPS_TO_EXECUTE =
            new CyRange(C_CATEGORY_LOOP_TRANSFER_UINT16_DEF, 1, 256);
        public static readonly CyRange R_SOURCE_INCREMENT_EVERY_CYCLE_BY_Y =
            new CyRange(C_CATEGORY_LOOP_TRANSFER_DEF, -2048, 2047);
        public static readonly CyRange R_DESTINATION_INCREMENT_EVERY_CYCLE_BY_Y =
            new CyRange(C_CATEGORY_LOOP_TRANSFER_DEF, -2048, 2047);
    }
}
