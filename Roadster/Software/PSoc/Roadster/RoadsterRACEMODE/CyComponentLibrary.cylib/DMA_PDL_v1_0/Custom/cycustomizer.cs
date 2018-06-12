/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using DMA_PDL_v1_0.Tabs;
using DMA_PDL_v1_0.Utils;
using System.Text;
using System.Diagnostics;

namespace DMA_PDL_v1_0
{
    [CyCompDevCustomizer]
    public class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v2
    {
        internal const string BASIC_TAB_NAME = "Basic";
        internal const string DESCRIPTOR_TAB_NAME = "Descriptors";
        private string m_instanceName;

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
                sb.AppendLine(String.Format("extern cy_stc_dma_descr_config_t {0}_{1}_SETTINGS;", m_instanceName, descriptor.DescriptorName));
                sb.AppendLine(String.Format("extern cy_stc_dma_descr_t {0}_{1};", m_instanceName, descriptor.DescriptorName));
                sb.AppendLine();
            }
            return sb.ToString();
        }

        private string GenerateDescriptorsInitAPIStr(IEnumerable<CyDmaDescriptionProperties> descriptors)
        {
            StringBuilder sb = new StringBuilder();
            foreach (CyDmaDescriptionProperties descriptor in descriptors)
            {
                sb.AppendLine(String.Format("    (void)Cy_DMA_Descr_Init(&{0}_{1}, &{0}_{1}_SETTINGS);", m_instanceName, descriptor.DescriptorName));
            }
            return sb.ToString();
        }

        private string GenerateDescriptorsInitStr(IEnumerable<CyDmaDescriptionProperties> descriptors)
        {
            StringBuilder sb = new StringBuilder();
            foreach (CyDmaDescriptionProperties descriptor in descriptors)
            {
                sb.AppendLine(String.Format("cy_stc_dma_descr_config_t {0}_{1}_SETTINGS = {{", m_instanceName, descriptor.DescriptorName));
                sb.AppendLine(String.Format("    .deact = (uint32_t){0},", descriptor.TriggerDeactivationAndRetriggering));
                sb.AppendLine(String.Format("    .intrType = (uint32_t){0},", GenerateInterrupt(descriptor.Interrupt)));
                sb.AppendLine(String.Format("    .trigoutType = (uint32_t){0},", GenerateTriggerOutput(descriptor.TriggerOutput)));
                sb.AppendLine(String.Format("    .chStateAtCmplt = (uint32_t){0},", GenerateChannelStateOnCompletion(descriptor.ChannelStateOnCompletion)));
                sb.AppendLine(String.Format("    .triginType = (uint32_t){0},", GenerateTriggerInput(descriptor.TriggerInputType)));
                sb.AppendLine(String.Format("    .dataSize = (uint32_t){0},", descriptor.DataElementSize));
                sb.AppendLine(String.Format("    .srcTxfrSize = (uint32_t){0},", GenerateSourceTransferWidth(descriptor.SourceAndDestinationTransferWidth, descriptor.DataElementSize)));
                sb.AppendLine(String.Format("    .destTxfrSize = (uint32_t){0},", GenerateDestinationTransferWidth(descriptor.SourceAndDestinationTransferWidth, descriptor.DataElementSize)));
                sb.AppendLine("    .descrType = (uint32_t)CY_DMA_2D_TRANSFER,");
                sb.AppendLine("    .srcAddr = 0u,");
                sb.AppendLine("    .destAddr = 0u,");
                sb.AppendLine(String.Format("    .srcXincr = {0}u,", descriptor.SourceIncrementEveryCycleByX));
                sb.AppendLine(String.Format("    .destXincr = {0}u,", descriptor.DestinationIncrementEveryCycleByX));
                sb.AppendLine(String.Format("    .xCount = {0}u,", descriptor.NumberOfDataElementsToTransferX));
                sb.AppendLine(String.Format("    .srcYincr = {0}u,", descriptor.SourceIncrementEveryCycleByY));
                sb.AppendLine(String.Format("    .destYincr = {0}u,", descriptor.DestinationIncrementEveryCycleByY));
                sb.AppendLine(String.Format("    .yCount = {0}u,", descriptor.NumberOfDataElementsToTransferY));

                string chainToDescriptor;
                if ((String.IsNullOrEmpty(descriptor.ChainToDescriptor))||(descriptor.ChainToDescriptor == CyConst.C_CHAIN_TO_DESCRIPTOR_DEF)) 
                {
                    chainToDescriptor = "0u";
                }
                else
                {
                    chainToDescriptor = String.Format("&{0}_{1}", m_instanceName, descriptor.ChainToDescriptor);
                }

                sb.AppendLine(String.Format("    .descrNext = {0},", chainToDescriptor));
                sb.AppendLine("};");
                sb.AppendLine();
                sb.AppendLine(String.Format("cy_stc_dma_descr_t {0}_{1} = {{", m_instanceName, descriptor.DescriptorName));
                sb.AppendLine("    .DESCR_CTL = 0u,");
                sb.AppendLine("    .DESCR_SRC = 0u,");
                sb.AppendLine("    .DESCR_DST = 0u,");
                sb.AppendLine("    .DESCR_X_CTL = 0u,");
                sb.AppendLine("    .DESCR_Y_CTL = 0u,");
                sb.AppendLine("    .DESCR_NEXT_PTR = 0u");
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
                    return "CY_DMA_CH_ENABLED";
                case CyEnDisEnum.Disable:
                    return "CY_DMA_CH_DISABLED";
                default:
                    Debug.Fail("Unhandled descriptor channel State On Completion");
                    return "CY_DMA_CH_ENABLED";
            }
        }

        private static string GenerateInterrupt(CyInterruptOrTriggerOutputEnum value)
        {
            switch (value)
            {
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_1ELEMENT_CMPLT:
                    return "CY_DMA_INTR_1ELEMENT_CMPLT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_X_LOOP_CMPLT:
                    return "CY_DMA_INTR_X_LOOP_CMPLT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCR_CMPLT:
                    return "CY_DMA_INTR_DESCR_CMPLT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCRCHAIN_CMPLT:
                    return "CY_DMA_INTR_DESCRCHAIN_CMPLT";
                default:
                    Debug.Fail("Unhandled descriptor interrupt");
                    return "CY_DMA_INTR_1ELEMENT_CMPLT";
            }
        }

        private static string GenerateTriggerOutput(CyInterruptOrTriggerOutputEnum value)
        {
            switch (value)
            {
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_1ELEMENT_CMPLT:
                    return "CY_DMA_TRIGOUT_1ELEMENT_CMPLT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_TRIGOUT_X_LOOP_CMPLT:
                    return "CY_DMA_TRIGOUT_X_LOOP_CMPLT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCR_CMPLT:
                    return "CY_DMA_TRIGOUT_DESCR_CMPLT";
                case CyInterruptOrTriggerOutputEnum.CY_DMA_INTR_DESCRCHAIN_CMPLT:
                    return "CY_DMA_TRIGOUT_DESCRCHAIN_CMPLT";
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
                    return "CY_DMA_TRIGIN_1ELEMENT";
                case CyTriggerInputTypesEnum.CY_DMA_INTR_X_LOOP_CMPLT:
                    return "CY_DMA_TRIGIN_XLOOP";
                case CyTriggerInputTypesEnum.CY_DMA_INTR_DESCR_CMPLT:
                    return "CY_DMA_TRIGIN_DESCR";
                case CyTriggerInputTypesEnum.CY_DMA_INTR_DESCRCHAIN_CMPLT:
                    return "CY_DMA_TRIGIN_DESCRCHAIN";
                default:
                    Debug.Fail("Unhandled descriptor trigger input");
                    return "CY_DMA_TRIGIN_1ELEMENT";
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
                            return CyTextConst.CY_DMA_TXFR_SIZE_DATA_SIZE;
                        case CySourceAndDestinationTransferWidthEnum.WordToByte:
                            return CyTextConst.CY_DMA_TXFR_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_HALFWORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToHalfword:
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToWord:
                            return CyTextConst.CY_DMA_TXFR_SIZE_DATA_SIZE;
                        case CySourceAndDestinationTransferWidthEnum.WordToHalfword:
                            return CyTextConst.CY_DMA_TXFR_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_WORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.WordToWord:
                            return CyTextConst.CY_DMA_TXFR_SIZE_DATA_SIZE;
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
                            return CyTextConst.CY_DMA_TXFR_SIZE_DATA_SIZE;
                        case CySourceAndDestinationTransferWidthEnum.ByteToWord:
                            return CyTextConst.CY_DMA_TXFR_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_HALFWORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToHalfword:
                        case CySourceAndDestinationTransferWidthEnum.WordToHalfword:
                            return CyTextConst.CY_DMA_TXFR_SIZE_DATA_SIZE;
                        case CySourceAndDestinationTransferWidthEnum.HalfwordToWord:
                            return CyTextConst.CY_DMA_TXFR_SIZE_WORD;
                        default:
                            Debug.Fail(CyTextConst.CY_DMA_UNKNOWN_SIZE);
                            return CyTextConst.CY_DMA_UNKNOWN_SIZE;
                    }
                case CyDataElementSizeEnum.CY_DMA_WORD:
                    switch (value)
                    {
                        case CySourceAndDestinationTransferWidthEnum.WordToWord:
                            return CyTextConst.CY_DMA_TXFR_SIZE_DATA_SIZE;
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
