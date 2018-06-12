/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using DMA_PDL_v2_0.Tabs;
using DMA_PDL_v2_0.Utils;
using System.Text;
using System.Diagnostics;

namespace DMA_PDL_v2_0
{
    [CyCompDevCustomizer]
    public class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v2
    {
        internal const string BASIC_TAB_NAME = "Basic";
        internal const string DESCRIPTOR_TAB_NAME = "Descriptors";
        private string m_instanceName;
        internal const string CY_CONST = "`=$CY_CONST_CONFIG ? \"const \" : \"\"`";

        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            CyDescriptorTab descriptorsTab = new CyDescriptorTab(parameters);

            CyParamExprDelegate descriptorExprDelegate = delegate (ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                descriptorsTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
            editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
            editor.AddCustomPage(Resources.DescriptorsTabDisplayName, descriptorsTab, descriptorExprDelegate, DESCRIPTOR_TAB_NAME);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            descriptorsTab.UpdateUI();
            parameters.GlobalEditMode = true;
            return editor.ShowDialog();
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyAPICustomize_v2 members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args, IEnumerable<CyAPICustomizer> apis)
        {
            CyParameters parameters = new CyParameters(args.InstQuery);
            m_instanceName = parameters.GetInstanceName();
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            string descriptorsInitStr = GenerateDescriptorsInitStr(parameters.Descriptors);
            string descriptorsInitAPIStr = GenerateDescriptorsInitAPIStr(parameters.Descriptors);
            string descriptorsInitHeaderStr = GenerateDescriptorsInitHeaderStr(parameters.Descriptors);
            Dictionary<string, string> paramDict = (customizers.Count > 0)
                ? customizers[0].MacroDictionary
                : new Dictionary<string, string>();
            paramDict.Add("DescriptorsInit", descriptorsInitStr);
            paramDict.Add("DescriptorsInitAPI", descriptorsInitAPIStr);
            paramDict.Add("DescriptorsInitHeader", descriptorsInitHeaderStr);
            paramDict.Add("FirstDescriprorStuct",
                (parameters.Descriptors.Count > 0)?(m_instanceName + "_" + parameters.Descriptors[0].DescriptorName):null);

            foreach (CyAPICustomizer customizer in customizers)
            {
                customizer.MacroDictionary = paramDict;
                yield return customizer;
            }
        }

        private string GenerateDescriptorsInitHeaderStr(IEnumerable<CyDmaDescriptionProperties> descriptors)
        {
            StringBuilder sb = new StringBuilder();
            foreach (CyDmaDescriptionProperties descriptor in descriptors)
            {
                sb.AppendLine(String.Format("extern {0}cy_stc_dma_descriptor_config_t {1}_{2}_config;", CY_CONST, m_instanceName, descriptor.DescriptorName));
                sb.AppendLine(String.Format("extern cy_stc_dma_descriptor_t {0}_{1};", m_instanceName, descriptor.DescriptorName));
                sb.AppendLine();
            }
            return sb.ToString();
        }

        private string GenerateDescriptorsInitAPIStr(IEnumerable<CyDmaDescriptionProperties> descriptors)
        {
            StringBuilder sb = new StringBuilder();
            foreach (CyDmaDescriptionProperties descriptor in descriptors)
            {
                sb.AppendLine(String.Format("    (void)Cy_DMA_Descriptor_Init(&{0}_{1}, &{0}_{1}_config);", m_instanceName, descriptor.DescriptorName));
            }
            return sb.ToString();
        }

        private string GenerateDescriptorsInitStr(IEnumerable<CyDmaDescriptionProperties> descriptors)
        {
            StringBuilder sb = new StringBuilder();
            foreach (CyDmaDescriptionProperties descriptor in descriptors)
            {
                sb.AppendLine(String.Format("{0}cy_stc_dma_descriptor_config_t {1}_{2}_config =", CY_CONST, m_instanceName, descriptor.DescriptorName));
                sb.AppendLine("{");
                sb.AppendLine(String.Format("    .retrigger       = {0},", GenerateDeactivationAndRetriggering(descriptor.TriggerDeactivationAndRetriggering)));
                sb.AppendLine(String.Format("    .interruptType   = {0},", GenerateInterrupt(descriptor.Interrupt)));
                sb.AppendLine(String.Format("    .triggerOutType  = {0},", GenerateTriggerOutput(descriptor.TriggerOutput)));
                sb.AppendLine(String.Format("    .channelState    = {0},", GenerateChannelStateOnCompletion(descriptor.ChannelStateOnCompletion)));
                sb.AppendLine(String.Format("    .triggerInType   = {0},", GenerateTriggerInput(descriptor.TriggerInputType)));
                sb.AppendLine(String.Format("    .dataSize        = {0},", descriptor.DataElementSize));
                sb.AppendLine(String.Format("    .srcTransferSize = {0},", GenerateSourceTransferWidth(descriptor.SourceAndDestinationTransferWidth, descriptor.DataElementSize)));
                sb.AppendLine(String.Format("    .dstTransferSize = {0},", GenerateDestinationTransferWidth(descriptor.SourceAndDestinationTransferWidth, descriptor.DataElementSize)));  
                sb.AppendLine(String.Format("    .descriptorType  = {0},", GenerateDescriptorType(descriptor.NumberOfDataElementsToTransfer, descriptor.NumberOfXLoopsToExecute)));
                sb.AppendLine("    .srcAddress      = NULL,");
                sb.AppendLine("    .dstAddress      = NULL,");
                sb.AppendLine(String.Format("    .srcXincrement   = {0}L,", descriptor.SourceIncrementEveryCycleByX));
                sb.AppendLine(String.Format("    .dstXincrement   = {0}L,", descriptor.DestinationIncrementEveryCycleByX));
                sb.AppendLine(String.Format("    .xCount          = {0}UL,", descriptor.NumberOfDataElementsToTransfer));
                sb.AppendLine(String.Format("    .srcYincrement   = {0}L,", descriptor.SourceIncrementEveryCycleByY));
                sb.AppendLine(String.Format("    .dstYincrement   = {0}L,", descriptor.DestinationIncrementEveryCycleByY));
                sb.AppendLine(String.Format("    .yCount          = {0}UL,", descriptor.NumberOfXLoopsToExecute));

                string chainToDescriptor;
                if ((String.IsNullOrEmpty(descriptor.ChainToDescriptor))||(descriptor.ChainToDescriptor == CyConst.C_CHAIN_TO_DESCRIPTOR_DEF)) 
                {
                    chainToDescriptor = "NULL";
                }
                else
                {
                    chainToDescriptor = String.Format("&{0}_{1}", m_instanceName, descriptor.ChainToDescriptor);
                }

                sb.AppendLine(String.Format("    .nextDescriptor  = {0}", chainToDescriptor));
                sb.AppendLine("};");
                sb.AppendLine();
                sb.AppendLine(String.Format("cy_stc_dma_descriptor_t {0}_{1} =", m_instanceName, descriptor.DescriptorName));
                sb.AppendLine("{");
                sb.AppendLine("    .ctl = 0UL,");
                sb.AppendLine("    .src = 0UL,");
                sb.AppendLine("    .dst = 0UL,");
                sb.AppendLine("    .xCtl = 0UL,");
                sb.AppendLine("    .yCtl = 0UL,");
                sb.AppendLine("    .nextPtr = 0UL");
                sb.AppendLine("};");
                sb.AppendLine();
            }

            return sb.ToString();
        }

        private string GenerateChannelStateOnCompletion(CyEnDisEnum channelStateOnCompletion)
        {
            switch (channelStateOnCompletion)
            {
                case CyEnDisEnum.Enable:
                    return "CY_DMA_CHANNEL_ENABLED";
                case CyEnDisEnum.Disable:
                    return "CY_DMA_CHANNEL_DISABLED";
                default:
                    Debug.Fail("Unhandled descriptor channel State On Completion");
                    return "CY_DMA_CHANNEL_ENABLED";
            }
        }

        private static string GenerateInterrupt(CyInterruptOrTriggerOutputEnum value)
        {
            switch (value)
            {
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_1ELEMENT_CMPLT:
                    return "CY_DMA_1ELEMENT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_X_LOOP_CMPLT:
                    return "CY_DMA_X_LOOP";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCR_CMPLT:
                    return "CY_DMA_DESCR";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCRCHAIN_CMPLT:
                    return "CY_DMA_DESCR_CHAIN";
                default:
                    Debug.Fail("Unhandled descriptor interrupt");
                    return "CY_DMA_INTR_1ELEMENT_CMPLT";
            }
        }
        
        private static string GenerateDeactivationAndRetriggering(CyTriggerDeactivationAndRetriggeringEnum value)
        {
            switch (value)
            {
                case CyTriggerDeactivationAndRetriggeringEnum.CY_DMA_RETDIG_IM:
                    return "CY_DMA_RETRIG_IM";
                case CyTriggerDeactivationAndRetriggeringEnum.CY_DMA_RETDIG_4CYC:
                    return "CY_DMA_RETRIG_4CYC";
                case CyTriggerDeactivationAndRetriggeringEnum.CY_DMA_RETDIG_16CYC:
                    return "CY_DMA_RETRIG_16CYC";
                case CyTriggerDeactivationAndRetriggeringEnum.CY_DMA_WAIT_FOR_REACT:
                    return "CY_DMA_WAIT_FOR_REACT";
                default:
                    Debug.Fail("Unhandled Deactivation And Retriggering value");
                    return "CY_DMA_RETRIG_IM";
            }
        }

        private static string GenerateTriggerOutput(CyInterruptOrTriggerOutputEnum value)
        {
            switch (value)
            {
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_1ELEMENT_CMPLT:
                    return "CY_DMA_1ELEMENT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_X_LOOP_CMPLT:
                    return "CY_DMA_X_LOOP";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCR_CMPLT:
                    return "CY_DMA_DESCR";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCRCHAIN_CMPLT:
                    return "CY_DMA_DESCR_CHAIN";
                default:
                    Debug.Fail("Unhandled descriptor trigger output");
                    return "CY_DMA_TRIGOUT_1ELEMENT_CMPLT";
            }
        }

        private static string GenerateTriggerInput(CyTriggerInputTypesEnum value)
        {
            switch (value)
            {
                case CyTriggerInputTypesEnum.CY_DMA_INTR_1ELEMENT_CMPLT:
                    return "CY_DMA_1ELEMENT";
                case CyTriggerInputTypesEnum.CY_DMA_INTR_X_LOOP_CMPLT:
                    return "CY_DMA_X_LOOP";
                case CyTriggerInputTypesEnum.CY_DMA_INTR_DESCR_CMPLT:
                    return "CY_DMA_DESCR";
                case CyTriggerInputTypesEnum.CY_DMA_INTR_DESCRCHAIN_CMPLT:
                    return "CY_DMA_DESCR_CHAIN";
                default:
                    Debug.Fail("Unhandled descriptor trigger input");
                    return "CY_DMA_TRIGIN_1ELEMENT";
            }
        }
        
        private static string GenerateDescriptorType(UInt16 xCount, UInt16 yCount)
        {
            if(1 == xCount)
            {
                return CyTextConst.CY_DMA_SINGLE_TRANSFER;
            }
            else if(1 == yCount)
            {
                return CyTextConst.CY_DMA_1D_TRANSFER;
            }
            else
            {
                return CyTextConst.CY_DMA_2D_TRANSFER;
            }
        }

        private static string GenerateSourceTransferWidth(CySourceAndDestinationTransferWidthEnum value, CyDataElementSizeEnum size)
        {
            switch (size)
            {
                case CyDataElementSizeEnum.CY_DMA_BYTE:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.ByteToByte:
                        case CySourceAndDestinationTransferWidthEnum.ByteToWord:
                            return CyTextConst.CY_DMA_XFER_SIZE_DATA;
                        case CySourceAndDestinationTransferWidthEnum.WordToByte:
                            return CyTextConst.CY_DMA_XFER_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_HALFWORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToHalfword:
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToWord:
                            return CyTextConst.CY_DMA_XFER_SIZE_DATA;
                        case CySourceAndDestinationTransferWidthEnum.WordToHalfword:
                            return CyTextConst.CY_DMA_XFER_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_WORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.WordToWord:
                            return CyTextConst.CY_DMA_XFER_SIZE_DATA;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                default:
                    Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                    return CyTextConst.CY_DMA_UNKNOWN_SIZE;
            }
        }

        private static string GenerateDestinationTransferWidth(CySourceAndDestinationTransferWidthEnum value, CyDataElementSizeEnum size)
        {
            switch (size)
            {
                case CyDataElementSizeEnum.CY_DMA_BYTE:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.ByteToByte:
                        case CySourceAndDestinationTransferWidthEnum.WordToByte:
                            return CyTextConst.CY_DMA_XFER_SIZE_DATA;
                        case CySourceAndDestinationTransferWidthEnum.ByteToWord:
                            return CyTextConst.CY_DMA_XFER_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_HALFWORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToHalfword:
                        case CySourceAndDestinationTransferWidthEnum.WordToHalfword:
                            return CyTextConst.CY_DMA_XFER_SIZE_DATA;
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToWord:
                            return CyTextConst.CY_DMA_XFER_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_WORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.WordToWord:
                            return CyTextConst.CY_DMA_XFER_SIZE_DATA;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                default:
                    Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                    return CyTextConst.CY_DMA_UNKNOWN_SIZE;
            }
        }
        #endregion
    }
}
