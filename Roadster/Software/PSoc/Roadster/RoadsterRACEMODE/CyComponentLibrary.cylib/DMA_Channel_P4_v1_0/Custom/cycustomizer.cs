/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Diagnostics;
using System.Collections.Generic;
using DMA_Channel_P4_v1_0.Tabs;

namespace DMA_Channel_P4_v1_0
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyVerilogCustomize_v1, ICyAPICustomize_v2
    {
        #region  Class constants
        public const string BUILTIN_TAB_NAME = "Built-in";

        public const string VERILOG_COMPONENT_NANE = "cy_m0s8_dma_v1_0";
        public const string VERILOG_PARAM_NAME = "ChanPriority";
        public const string VERILOG_PARAM_DISPLAY_NAME = "priority";
        
        public const string CHAN_CONFIG_PRM = "ChanConfig";
        public const string TD0_CONFIG_PRM = "Td0Config";
        public const string TD1_CONFIG_PRM = "Td1Config";

        public const int CHCTL_CHAN_PRIORITY = 28;
        public const int TDCTL_CHAIN_TO = 29;
        public const int TDCTL_IS_PREEMTABLE = 28;
        public const int TDCTL_GENERATE_IRQ = 27;
        public const int TDCTL_INVALIDATE = 26;
        public const int TDCTL_INCREMENT_SRC_ADDRESS = 23;
        public const int TDCTL_INCREMENT_DST_ADDRESS = 21;
        public const int TDCTL_DATA_SIZE = 16;
        public const int TDCTL_SRC_DST_TRANSFER_SIZE = 20;
        public const int TDCTL_TRANSFER_MODE = 30;
        public const int TDCTL_TRIGGER_TYPE = 24;
        #endregion

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            parameters.Editor = editor;
                        
            CyDescriptorTab descriptor0Tab = new CyDescriptorTab(parameters, CyDescriptorTab.DESCRIPTOR0);
            CyDescriptorTab descriptor1Tab = new CyDescriptorTab(parameters, CyDescriptorTab.DESCRIPTOR1);
            CyGeneralTab channelTab = new CyGeneralTab(parameters);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                descriptor0Tab.UpdateUI();
                descriptor1Tab.UpdateUI();
                channelTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Resources.ChannelTabName, channelTab, exprDelegate, channelTab.TabName);
            editor.AddCustomPage(Resources.Descriptor0TabName, descriptor0Tab, exprDelegate, descriptor0Tab.TabName);
            editor.AddCustomPage(Resources.Descriptor1TabName, descriptor1Tab, exprDelegate, descriptor1Tab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabName, BUILTIN_TAB_NAME);

            editor.UseBigEditor = true;

            descriptor0Tab.UpdateUI();
            descriptor1Tab.UpdateUI();
            channelTab.UpdateUI();
            

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
                
        #region ICyVerilogCustomize_v1 Members
        public CyCustErr CustomizeVerilog(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, out string codeSnippet)
        {
            CyCustErr err = CyCustErr.Ok;
            codeSnippet = string.Empty;
            CyVerilogWriter vw = new CyVerilogWriter(VERILOG_COMPONENT_NANE, query.InstanceName);

            //Add Generics.
            foreach (string paramName in query.GetParamNames())
            {
                CyCompDevParam param = query.GetCommittedParam(paramName);

                if (paramName == VERILOG_PARAM_NAME)
                    vw.AddGeneric(VERILOG_PARAM_DISPLAY_NAME, param.Value);
            }
            
            //Add Ports
            foreach (string termName in termQuery.GetTerminalNames())
            {
                string termBaseName = termQuery.GetTermBaseName(termName);
                CyCompDevTermDir termDirection = termQuery.GetTermDirection(termName);
                bool termHasNoDrivers = termQuery.GetHasNoDrivers(termName);

                string value;
                if (termDirection != CyCompDevTermDir.OUTPUT && termHasNoDrivers)
                {
                    value = termQuery.GetTermDefaultVlogExpr(termName);
                }
                else
                {
                    value = termQuery.GetTermSigSegName(termName);
                }
                vw.AddPort(termBaseName, value);
            }

            codeSnippet = vw.ToString();
            return err;
        }
        #endregion
 
        #region ICyAPICustomize_v2
        System.Collections.Generic.IEnumerable<CyAPICustomizer> ICyAPICustomize_v2.CustomizeAPIs(
            ICyAPICustomizeArgs_v2 args, System.Collections.Generic.IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            CyParameters prms = new CyParameters(args.InstQuery);
            
            if (customizers.Count > 0)
            {
                paramDict = customizers[0].MacroDictionary;
            }

            UInt32 chCtl = 0;
            UInt32[] tdConfig = new UInt32[2] { 0, 0 };

            chCtl = GetChConfig(prms);
            tdConfig[CyDescriptorTab.DESCRIPTOR0] = GetTdConfig(CyDescriptorTab.DESCRIPTOR0, prms);

            if(prms.TdNum != 1)
                tdConfig[CyDescriptorTab.DESCRIPTOR1] = GetTdConfig(CyDescriptorTab.DESCRIPTOR1, prms);

            paramDict.Add(CHAN_CONFIG_PRM, UintToStringHEX(chCtl));
            paramDict.Add(TD0_CONFIG_PRM, UintToStringHEX(tdConfig[CyDescriptorTab.DESCRIPTOR0]));
            paramDict.Add(TD1_CONFIG_PRM, UintToStringHEX(tdConfig[CyDescriptorTab.DESCRIPTOR1]));

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
                yield return customizers[i];
            }
        }

        private UInt32 GetChConfig(CyParameters prms)
        {
            UInt32 chCtl = 0;

            chCtl |= (UInt32)prms.ChanPriority << CHCTL_CHAN_PRIORITY;

            return chCtl;
        }

        private UInt32 GetTdConfig(int num, CyParameters prms)
        {
            UInt32 tdCtl = 0;

            tdCtl |= Convert.ToUInt32(prms.GetChainTo(num)) << TDCTL_CHAIN_TO;
            tdCtl |= Convert.ToUInt32(prms.GetIsPreemtable(num)) << TDCTL_IS_PREEMTABLE;
            tdCtl |= Convert.ToUInt32(prms.GetGenerateIrq(num)) << TDCTL_GENERATE_IRQ;
            tdCtl |= Convert.ToUInt32(prms.GetInvalidate(num)) << TDCTL_INVALIDATE;
            tdCtl |= Convert.ToUInt32(prms.GetIncrementSrcAddress(num)) << TDCTL_INCREMENT_SRC_ADDRESS;
            tdCtl |= Convert.ToUInt32(prms.GetIncrementDstAddress(num)) << TDCTL_INCREMENT_DST_ADDRESS;
            tdCtl |= prms.GetNumDataElements(num) - 1;

            if (prms.GetDataSize(num) == CyEDataSizeType.HALFWORD)
                tdCtl |= (UInt32)CyEDataSizeType.HALFWORD << TDCTL_DATA_SIZE;
            else if (prms.GetDataSize(num) == CyEDataSizeType.WORD)
                tdCtl |= (UInt32)CyEDataSizeType.WORD << TDCTL_DATA_SIZE;

            if (prms.GetSrcDstTransferSize(num) == CyESrcDstTransferSize.ELEMENT_WORD)
                tdCtl |= (UInt32)CyESrcDstTransferSize.ELEMENT_WORD << TDCTL_SRC_DST_TRANSFER_SIZE;
            if (prms.GetSrcDstTransferSize(num) == CyESrcDstTransferSize.WORD_ELEMENT)
                tdCtl |= (UInt32)(CyESrcDstTransferSize.WORD_ELEMENT + 2) << TDCTL_SRC_DST_TRANSFER_SIZE;
            if (prms.GetSrcDstTransferSize(num) == CyESrcDstTransferSize.WORD_WORD)
                tdCtl |= (UInt32)(CyESrcDstTransferSize.WORD_WORD + 2) << TDCTL_SRC_DST_TRANSFER_SIZE;

            if (prms.GetTransferMode(num) == CyETransferMode.ENTIRE_DESCRIPTOR)
                tdCtl |= (UInt32)CyETransferMode.ENTIRE_DESCRIPTOR << TDCTL_TRANSFER_MODE;
            if (prms.GetTransferMode(num) == CyETransferMode.ENTIRE_DESCRIPTOR_CHAIN)
                tdCtl |= (UInt32)CyETransferMode.ENTIRE_DESCRIPTOR_CHAIN << TDCTL_TRANSFER_MODE;

            if (prms.GetTriggerType(num) == CyETriggerType.LEVEL_FOUR)
                tdCtl |= (UInt32)CyETriggerType.LEVEL_FOUR << TDCTL_TRIGGER_TYPE;
            if (prms.GetTriggerType(num) == CyETriggerType.LEVEL_EIGHT)
                tdCtl |= (UInt32)CyETriggerType.LEVEL_EIGHT << TDCTL_TRIGGER_TYPE;
            if (prms.GetTriggerType(num) == CyETriggerType.LEVEL_UNKNOWN)
                tdCtl |= (UInt32)CyETriggerType.LEVEL_UNKNOWN << TDCTL_TRIGGER_TYPE;

            return tdCtl;
        }

        private string UintToStringHEX(UInt32 ui32)
        {
            return "0x" + ui32.ToString("X8") + "u";
        }
        #endregion
    }
}
