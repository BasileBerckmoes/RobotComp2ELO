/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Text.RegularExpressions;


[assembly: System.Runtime.CompilerServices.InternalsVisibleTo("UnitTests")]
namespace USBFS_v3_20
{
    public partial class CyCustomizer : ICyAPICustomize_v1
    {
        #region ICyAPICustomize_v1 Members

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
                                                          IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            // Get dict from main file.
            if (customizers.Count > 0)
                paramDict = customizers[0].MacroDictionary;

            //Extract parameters
            CyUSBFSParameters parameters = new CyUSBFSParameters(query);

            parameters.SetNodesISerialNumber();

            //if special descriptors are present then send them to the end (for more pleasing view in API)
            ArrangeDescForPleasingView(parameters.DeviceTree);

            //Update Parameters to include last changes
            parameters.RecalcDescriptors(parameters.HidReportTree.Nodes[0]);
            parameters.RecalcDescriptors(parameters.DeviceTree.Nodes[0]);

            //Prepare m_hidReportTree for parsing (remove comment items)
            for (int i = 0; i < parameters.HidReportTree.Nodes[0].Nodes.Count; i++)
                for (int j = 0; j < parameters.HidReportTree.Nodes[0].Nodes[i].Nodes.Count; j++)
                {
                    if (((CyHIDReportItemDescriptor)parameters.HidReportTree.Nodes[0].Nodes[i].Nodes[j].Value)
                                                                                                    .Item.IsComment())
                    {
                        parameters.HidReportTree.Nodes[0].Nodes[i].Nodes.RemoveAt(j--);
                    }
                }

            // Generate the descriptor, storage and other data structures
            string instanceName = query.GetCommittedParam("INSTANCE_NAME").Value;
            CyUSBCodeGenerator g = new CyUSBCodeGenerator(instanceName, parameters);
            g.GenerateCode();

            foreach (KeyValuePair<string, string> p in g.CodeParameterDictionary)
            {
                paramDict.Add(p.Key, p.Value);
            }

            //Save result
            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }
            return customizers;
        }

        private void ArrangeDescForPleasingView(CyDescriptorTree deviceTree)
        {
            // if BOS descriptor is present send it to the end
            if (deviceTree.Nodes[0].Nodes.Count != 0)
            {
                for (int i = 0; i < deviceTree.Nodes[0].Nodes.Count; i++)
                {
                    CyDescriptorNode deviceNode = deviceTree.Nodes[0].Nodes[i];

                    if (CyDescriptorNode.IsDescriptorPresent(deviceNode, CyUSBDescriptorType.BOS))
                    {
                        for (int j = 0; j < deviceNode.Nodes.Count; j++)
                        {
                            if (deviceNode.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.BOS &&
                                j != deviceNode.Nodes.Count - 1)
                            {
                                CyDescriptorNode bosNode = deviceNode.Nodes[j];
                                deviceNode.Nodes.Remove(bosNode);
                                deviceNode.Nodes.Add(bosNode);
                                break;
                            }
                        }
                    }
                }
            }
        }
        #endregion
    }

    // Start refactoring into a class that returns a set of dictionaries similar to the
    // CyAPICustomizer
    internal class CyUSBCodeGenerator : CyUsbCodePrimitives
    {
        private const string DMA_USB_REQ_TR_OUT = "DMA_USB_REQ_TR_OUT";
        private const string DMA_USB_BURST_END_TR_OUT = "DMA_USB_BURST_END_TR_OUT";
        private const string EP_DMA_USB_REQ_TR_SEL_ARRAY = "EP_DMA_USB_REQ_TR_SEL_ARRAY";
        private const string DMA_USB_REQ_TR_OUT_STRVALUE = "(0xC0020100U)";
        private const string DMA_USB_BURST_END_TR_OUT_STRVALUE = "(0xC0020300U)";

        private const string EP_MANAGEMENT_DMA_ARRAY = "EP_MANAGEMENT_DMA_ARRAY";
        private const string EP_TD_TERMOUT_EN_ARRAY = "EP_TD_TERMOUT_EN_ARRAY";

        private const string DEF_INTR_LVL_SEL = "INTR_LVL_SEL";
        private const string DEF_BOS_ENABLE = "BOS_ENABLE";

        private const string APIGEN_ISR_CALLBACKS = "APIGEN_ISR_CALLBACKS";

        private const string APIGEN_DEFINES = "APIGEN_DEFINES";
        private const string APIGEN_FUNCDECL = "APIGEN_FUNCDECL";
        private const string MIDI_APIGEN_DEFINES = "MIDI_APIGEN_DEFINES";

        private const string APIGEN_DEVICE_DESCRIPTORS = "APIGEN_DEVICE_DESCRIPTORS";
        private const string APIGEN_DEVICE_TABLES = "APIGEN_DEVICE_TABLES";
        private const string DEF_NUM_DEVICES = "NUM_DEVICES";

        private const string APIGEN_STRING_DESCRIPTORS = "APIGEN_STRING_DESCRIPTORS";
        private const string APIGEN_SN_DESCRIPTOR = "APIGEN_SN_DESCRIPTOR";

        private const string DEF_DESCRIPTOR_STRING = "ENABLE_DESCRIPTOR_STRINGS";

        private const string DEF_ENABLE_STRINGS = "ENABLE_STRINGS";
        private const string DEF_MSOS_STRING = "ENABLE_MSOS_STRING";
        private const string DEF_SN_STRING = "ENABLE_SN_STRING";
        private const string DEF_FWSN_STRING = "ENABLE_FWSN_STRING";
        private const string DEF_IDSN_STRING = "ENABLE_IDSN_STRING";
        private const string DEF_DYN_ALLOCATION = "DYNAMIC_ALLOCATION";
        private const string DEF_MAX_REPORTID_NUMBER = "MAX_REPORTID_NUMBER";

        private const string APIGEN_HIDREPORT_DESCRIPTORS = "APIGEN_HIDREPORT_DESCRIPTORS";
        private const string APIGEN_HIDREPORT_TABLES = "APIGEN_HIDREPORT_TABLES";
        private const string DEF_ENABLE_HID_CLASS = "ENABLE_HID_CLASS";
        private const string DEF_ENABLE_AUDIO_CLASS = "ENABLE_AUDIO_CLASS";
        private const string DEF_ENABLE_AS_CLASS = "ENABLE_AUDIO_STREAMING";
        private const string DEF_ENABLE_MS_CLASS = "ENABLE_MIDI_STREAMING";
        private const string DEF_ENABLE_CDC_CLASS = "ENABLE_CDC_CLASS";
        private const string DEF_ENABLE_MSC_CLASS = "ENABLE_MSC_CLASS";
        private const string DEF_ENABLE_MIDI_CLASS = "ENABLE_MIDI_CLASS";
        private const string DEF_MIDI_IN_BUFF_SIZE = "MIDI_IN_BUFF_SIZE";
        private const string DEF_MIDI_OUT_BUFF_SIZE = "MIDI_OUT_BUFF_SIZE";

        private const int SN_INDEX = 0;
        private const int EE_INDEX = 1;

        private const int DEF_VALUE_PADRIGHT = 46;

        private const int SOF_LVL_SEL_OFFSET = 0;
        private const int BUS_RSET_LVL_SEL_OFFSET = 2;
        private const int EP0_LVL_SEL_OFFSET = 4;
        private const int LPM_LVL_SEL_OFFSET = 6;
        private const int ARB_EP_LVL_SEL_OFFSET = 14;
        private const int EP1_LVL_SEL_OFFSET = 16;
        private const int EP2_LVL_SEL_OFFSET = 18;
        private const int EP3_LVL_SEL_OFFSET = 20;
        private const int EP4_LVL_SEL_OFFSET = 22;
        private const int EP5_LVL_SEL_OFFSET = 24;
        private const int EP6_LVL_SEL_OFFSET = 26;
        private const int EP7_LVL_SEL_OFFSET = 28;
        private const int EP8_LVL_SEL_OFFSET = 30;

        private byte m_maxReportID = 0;
        private List<int> m_hidClassReferences = new List<int>();

        private readonly string m_instanceName;
        private readonly CyUSBFSParameters m_parameters;
        private readonly Dictionary<string, string> m_codeParameters = new Dictionary<string, string>();

        public CyUSBCodeGenerator(string instanceName, CyUSBFSParameters parameters) : base(instanceName)
        {
            m_instanceName = instanceName;
            m_parameters = parameters;
        }

        public void GenerateCode()
        {
            GenerateDevices();
            GenerateStrings();
            GenerateHIDReports();
        }

        /// <summary>
        /// Generates descriptors from the m_deviceTree
        /// </summary>
        private void GenerateDevices()
        {
            CyUsbCodePrimitives.HidClassQualList.Clear();

            //Generate the descriptors
            CyUsbDescriptorGenTree gtDescr = new CyUsbDescriptorGenTree();
            string deviceDescr = gtDescr.Generate(m_parameters.DeviceTree.Nodes[0].Nodes, m_instanceName,
                                                  m_instanceName);
            // Calculate the element number in the table and store it in the m_hidClassReferences
            const string HID_CLASS_LABEL = "HID Class Descriptor\r\n";
            int indHid = -1;
            m_hidClassReferences.Clear();
            int indConfig = deviceDescr.IndexOf("Config Descriptor");
            indHid = deviceDescr.IndexOf(HID_CLASS_LABEL, indHid + 1);
            while (indHid >= 0)
            {
                int count = GetElemNumInArray(deviceDescr.Substring(indConfig, indHid - indConfig));
                m_hidClassReferences.Add(count);
                indHid = deviceDescr.IndexOf(HID_CLASS_LABEL, indHid + 1);
            }

            AddFuncDeclarations(deviceDescr);
            m_codeParameters.Add(APIGEN_DEVICE_DESCRIPTORS, deviceDescr);

            CyUsbDeviceRootTableGen genTable = new CyUsbDeviceRootTableGen(m_instanceName);
            string deviceTables = genTable.Generate(m_parameters.DeviceTree.Nodes[0].Nodes, m_instanceName,
                                                    m_instanceName);
            AddFuncDeclarations(deviceTables);
            m_codeParameters.Add(APIGEN_DEVICE_TABLES, deviceTables);
            AddDefine(DEF_NUM_DEVICES, m_parameters.DeviceTree.Nodes[0].Nodes.Count.ToString());

            // Memory Allocation define
            if (m_parameters.EPMemoryAlloc == CyUSBFSParameters.CyMemoryAllocation.MA_Dynamic)
            {
                AddDefine(DEF_DYN_ALLOCATION);
            }

            // Add Audio define if necessary
            if (deviceDescr.IndexOf("AUDIO") >= 0)
                AddDefine(DEF_ENABLE_AUDIO_CLASS);

            // Add AudioStreaming define if necessary
            if (deviceDescr.IndexOf("AudioStreaming") >= 0)
                AddDefine(DEF_ENABLE_AS_CLASS);

            // Add CDC define if necessary
            if (deviceDescr.IndexOf("CDC") >= 0)
                AddDefine(DEF_ENABLE_CDC_CLASS);

            // Add MIDI define if necessary
            if (deviceDescr.IndexOf("MIDI") >= 0)
            {
                AddDefine(DEF_ENABLE_MIDI_CLASS, "1");
                AddDefineMidi(DEF_ENABLE_MS_CLASS);

                // MIDI enpoints buffer size
                ushort inSize = 0;
                ushort outSize = 0;
                GetMidiBuffSize(m_parameters.DeviceTree.Nodes[0], ref inSize, ref outSize);
                AddDefineMidi(DEF_MIDI_IN_BUFF_SIZE, inSize.ToString());
                AddDefineMidi(DEF_MIDI_OUT_BUFF_SIZE, outSize.ToString());
            }
            else
            {
                AddDefine(DEF_ENABLE_MIDI_CLASS, "0");
            }

            // Add MSC define if necessary
            if (deviceDescr.IndexOf("MSC") >= 0)
                AddDefine(DEF_ENABLE_MSC_CLASS, "1");
            else
                AddDefine(DEF_ENABLE_MSC_CLASS, "0");

            // Add BOS define if necessary
            AddDefine(DEF_BOS_ENABLE, BoolToIntString(CyDescriptorNode.IsDescriptorPresent(m_parameters.DeviceTree.
                Nodes[0], CyUSBDescriptorType.BOS)));

            // Add ISR tables if necessary
            if (m_parameters.IsPSoC4AL_IpBlock)
            {
                uint intrLvlSel = GetLvlSelReg();
                StringBuilder isrCallBacksTable;

                GetIsrCallBacksTable(out isrCallBacksTable);

                AddDefine(DEF_INTR_LVL_SEL, HexDoubleWordString(intrLvlSel));
                m_codeParameters.Add(APIGEN_ISR_CALLBACKS, isrCallBacksTable.ToString());
            }

            // Add Endpoints Mamagement DMA and Termout Enable arrays
            StringBuilder epManagDmaTable = new StringBuilder();
            StringBuilder epTermoutEnTable = new StringBuilder();

            GetEpTables(out epManagDmaTable, out epTermoutEnTable);

            m_codeParameters.Add(EP_MANAGEMENT_DMA_ARRAY, epManagDmaTable.ToString());
            m_codeParameters.Add(EP_TD_TERMOUT_EN_ARRAY, epTermoutEnTable.ToString());

            m_codeParameters.Add(DMA_USB_REQ_TR_OUT, DMA_USB_REQ_TR_OUT_STRVALUE);
            m_codeParameters.Add(DMA_USB_BURST_END_TR_OUT, DMA_USB_BURST_END_TR_OUT_STRVALUE);
            m_codeParameters.Add(EP_DMA_USB_REQ_TR_SEL_ARRAY, GetEpDmaReqTrOutArray());
        }

        /// <summary>
        /// Generates descriptors from the m_stringTree
        /// </summary>
        private void GenerateStrings()
        {
            // String Descriptors
            bool enableStrings = false;
            CyUsbStringDescriptorGenTree gtStrings = new CyUsbStringDescriptorGenTree();
            string stringDescr = gtStrings.Generate(m_parameters.StringTree.Nodes[0].Nodes, m_instanceName,
                                                    m_instanceName);
            if (m_parameters.StringTree.Nodes[0].Nodes.Count > 1)
            {
                enableStrings = true;
                AddDefine(DEF_DESCRIPTOR_STRING);
            }
            // Special String support MS OS String (EE)
            CyStringDescriptor s = (CyStringDescriptor)m_parameters.StringTree.Nodes[1].Nodes[EE_INDEX].Value;
            if (s.bUsed)
            {
                enableStrings = true;
                AddDefine(DEF_MSOS_STRING);
            }
            // Special String support SN String
            s = (CyStringDescriptor)m_parameters.StringTree.Nodes[1].Nodes[SN_INDEX].Value;
            CyUsbStringSNDescriptorGen cg = new CyUsbStringSNDescriptorGen(m_instanceName);
            StringBuilder snCode = new StringBuilder(cg.GenHeader(s, m_instanceName, m_instanceName));
            if (s.bUsed)
            {
                enableStrings = true;
                snCode.Append(cg.GenBody(s, m_instanceName, m_instanceName));
                snCode.Append(cg.GenFooter(s, m_instanceName, m_instanceName));
                AddFuncDeclarations(snCode.ToString());
                m_codeParameters.Add(APIGEN_SN_DESCRIPTOR, snCode.ToString());

                AddDefine(DEF_SN_STRING);

                if (s.snType == CyStringGenerationType.USER_CALL_BACK)
                {
                    AddDefine(DEF_FWSN_STRING);
                }
                else if (s.snType == CyStringGenerationType.SILICON_NUMBER)
                {
                    AddDefine(DEF_IDSN_STRING);
                }
            }
            AddFuncDeclarations(stringDescr);
            m_codeParameters.Add(APIGEN_STRING_DESCRIPTORS, stringDescr);
            if (enableStrings)
            {
                AddDefine(DEF_ENABLE_STRINGS);
            }
        }

        /// <summary>
        /// Generates descriptors from the m_hidReportTree
        /// </summary>
        private void GenerateHIDReports()
        {
            CyUsbHIDReportDescriptorGenTree gtHIDReport = new CyUsbHIDReportDescriptorGenTree();
            string HIDReportDescr = gtHIDReport.Generate(m_parameters.HidReportTree.Nodes[0], m_instanceName,
                                                         m_instanceName);
            string HIDReportTables = GenReportTables(m_parameters.DeviceTree.Nodes[0], m_instanceName,
                                                     m_instanceName);

            if (HIDReportDescr.Length > 0)
            {
                AddDefine(DEF_ENABLE_HID_CLASS);
                AddFuncDeclarations(HIDReportDescr);
                AddFuncDeclarations(HIDReportTables);
                m_codeParameters.Add(APIGEN_HIDREPORT_DESCRIPTORS, HIDReportDescr);
                m_codeParameters.Add(APIGEN_HIDREPORT_TABLES, HIDReportTables);
                for (int i = 0; i < m_parameters.HidReportTree.Nodes[0].Nodes.Count; i++)
                {
                    int rptIndex = i + 1;
                    ushort reportSize = ReportDescriptorSize(m_parameters.HidReportTree.Nodes[0].Nodes[i].Nodes);
                    AddDefine(string.Format("HID_RPT_{0}_SIZE_LSB", rptIndex),
                              String.Format("{0}", HexByteString((byte)(reportSize & 0xFF))));
                    AddDefine(string.Format("HID_RPT_{0}_SIZE_MSB", rptIndex),
                              String.Format("{0}", HexByteString((byte)((reportSize >> 8) & 0xFF))));
                }
            }

            AddDefine(DEF_MAX_REPORTID_NUMBER, m_maxReportID.ToString());
        }

        private string GenReportTables(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            for (int i = 0; i < node.Nodes.Count; i++)
            {
                string qual = GenerateQualName(qualName, node.Nodes[i], i);
                code.Append(GenReportTables(node.Nodes[i], instName, qual));
            }
            if (node.Value != null)
            {
                if (node.Value.bDescriptorType == CyUSBDescriptorType.HID)
                {
                    CyHIDDescriptor h = (CyHIDDescriptor) node.Value;
                    code.Append(GenReportTable(h.bReportIndex, instName, qualName));
                }
            }
            return code.ToString();
        }

        private string GenReportTable(int rptIndex, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            if ((rptIndex > 0) && (rptIndex <= m_parameters.HidReportTree.Nodes[0].Nodes.Count))
            {
                CyDescriptorNode ReportTop = m_parameters.HidReportTree.Nodes[0].Nodes[rptIndex - 1];
                List<CyHidReportID> reports = GetReportIDList(ReportTop);
                int inputReportsCount = CyHidReportID.GetCount(reports, CyHidReportItem.RPTITEM_INPUT);
                int outputReportsCount = CyHidReportID.GetCount(reports, CyHidReportItem.RPTITEM_OUTPUT);
                int featureReportsCount = CyHidReportID.GetCount(reports, CyHidReportItem.RPTITEM_FEATURE);
                m_maxReportID = CyHidReportID.GetMaxReportID(reports);

                code.AppendFormat("#if !defined(USER_DEFINE_{0}_HID_RPT_STORAGE)\r\n", qualName);
                if (CyHidReportID.GetCount(reports, CyHidReportItem.RPTITEM_INPUT) > 0)
                {
                    code.AppendLine("/*********************************************************************");
                    code.AppendLine("* HID Input Report Storage");
                    code.AppendLine("*********************************************************************/");
                    for (int i = 0; i < reports.Count; i++)
                    {
                        if (reports[i].m_inputSize > 0)
                        {
                            string idStr = reports[i].GetIDString();
                            code.AppendFormat("T_{0}_XFER_STATUS_BLOCK {1}_IN_RPT_SCB{2};{3}", instName, qualName,
                                                idStr, NEWLINE);
                            AddFuncDeclaration(String.Format("T_{0}_XFER_STATUS_BLOCK {1}_IN_RPT_SCB{2}", instName,
                                                 qualName, idStr));
                            string bufArray = GenerateAllocateArray(qualName + "_IN_BUF" + idStr,
                                                                  qualName + "_IN_BUF_SIZE" + idStr);
                            code.AppendLine(bufArray);
                            AddFuncDeclaration(bufArray);
                            AddDefineNoInstance(qualName + "_IN_BUF_SIZE" + idStr, reports[i].m_inputSize);
                        }
                    }

                    code.AppendLine("/*********************************************************************");
                    code.AppendLine("* HID Input Report TD Table");
                    code.AppendLine("*********************************************************************/");
                    uint rptTableLen = CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_INPUT) + 1u;
                    code.Append(GenerateTDHeader(String.Format("{0}_IN_RPT_TABLE[{1}u]", qualName, rptTableLen)));
                    for (int i = 0; i < rptTableLen; i++)
                    {
                        CyHidReportID rpt = CyHidReportID.ReportWithID(reports, (byte)i,
                                                                       CyHidReportItem.RPTITEM_INPUT);
                        if (rpt != null)
                        {
                            string idStr = rpt.GetIDString();
                            code.Append(GenerateTDEntry(qualName + "_IN_BUF_SIZE" + idStr,
                                            qualName + "_IN_BUF" + idStr + "[0u]", qualName + "_IN_RPT_SCB" + idStr));
                        }
                        else
                        {
                            code.Append(GenerateTDEntry(HexByteString(0), NULL_PTR, NULL_PTR));
                        }
                        code.Append(COMMA_NEWLINE);
                    }

                    code.AppendFormat("{0};{1}", GenerateFooter(), NEWLINE);
                    AddDefineNoInstance(qualName + "_NUM_IN_RPTS", (uint)inputReportsCount);
                }

                if (CyHidReportID.GetCount(reports, CyHidReportItem.RPTITEM_OUTPUT) > 0)
                {
                    code.AppendLine("/*********************************************************************");
                    code.AppendLine("* HID Output Report Storage");
                    code.AppendLine("*********************************************************************/");
                    for (int i = 0; i < reports.Count; i++)
                    {
                        if (reports[i].m_outputSize > 0)
                        {
                            string idStr = reports[i].GetIDString();
                            code.AppendFormat("T_{0}_XFER_STATUS_BLOCK {1}_OUT_RPT_SCB{2};{3}", instName, qualName,
                                                                idStr, NEWLINE);
                            AddFuncDeclaration(String.Format("T_{0}_XFER_STATUS_BLOCK {1}_OUT_RPT_SCB{2}", instName,
                                                 qualName, idStr));
                            string bufArray = GenerateAllocateArray(qualName + "_OUT_BUF" + idStr,
                                                                  qualName + "_OUT_BUF_SIZE" + idStr);
                            code.AppendLine(bufArray);
                            AddFuncDeclaration(bufArray);
                            AddDefineNoInstance(qualName + "_OUT_BUF_SIZE" + idStr, reports[i].m_outputSize);
                        }
                    }
                    code.AppendLine("/*********************************************************************");
                    code.AppendLine("* HID Output Report TD Table");
                    code.AppendLine("*********************************************************************/");
                    uint rptTableLen = CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_OUTPUT) + 1u;
                    code.Append(GenerateTDHeader(String.Format("{0}_OUT_RPT_TABLE[{1}u]", qualName, rptTableLen)));
                    for (int i = 0; i < rptTableLen; i++)
                    {
                        CyHidReportID rpt = CyHidReportID.ReportWithID(reports, (byte)i,
                                                                       CyHidReportItem.RPTITEM_OUTPUT);
                        if (rpt != null)
                        {
                            string idStr = rpt.GetIDString();
                            code.Append(GenerateTDEntry(qualName + "_OUT_BUF_SIZE" + idStr,
                                            qualName + "_OUT_BUF" + idStr + "[0u]", qualName + "_OUT_RPT_SCB" + idStr));
                        }
                        else
                        {
                            code.Append(GenerateTDEntry(HexByteString(0), NULL_PTR, NULL_PTR));
                        }
                        code.Append(COMMA_NEWLINE);
                    }
                    code.AppendFormat("{0};{1}", GenerateFooter(), NEWLINE);
                    AddDefineNoInstance(qualName + "_NUM_OUT_RPTS", (uint)outputReportsCount);
                }

                if (CyHidReportID.GetCount(reports, CyHidReportItem.RPTITEM_FEATURE) > 0)
                {
                    code.AppendLine("/*********************************************************************");
                    code.AppendLine("* HID Feature Report Storage");
                    code.AppendLine("*********************************************************************/");
                    for (int i = 0; i < reports.Count; i++)
                    {
                        if (reports[i].m_featureSize > 0)
                        {
                            string idStr = reports[i].GetIDString();

                            code.AppendFormat("T_{0}_XFER_STATUS_BLOCK {1}_FEATURE_RPT_SCB{2};{3}", instName, qualName,
                                                idStr, NEWLINE);
                            AddFuncDeclaration(String.Format("T_{0}_XFER_STATUS_BLOCK {1}_FEATURE_RPT_SCB{2}",
                                                instName, qualName, idStr));

                            string bufArray = GenerateAllocateArray(qualName + "_FEATURE_BUF" + idStr,
                                                                    qualName + "_FEATURE_BUF_SIZE" + idStr);
                            code.AppendLine(bufArray);
                            AddFuncDeclaration(bufArray);
                            AddDefineNoInstance(qualName + "_FEATURE_BUF_SIZE" + idStr,
                                                reports[i].m_featureSize);
                        }
                    }
                    code.AppendLine("/*********************************************************************");
                    code.AppendLine("* HID Feature Report TD Table");
                    code.AppendLine("*********************************************************************/");
                    uint rptTableLen = CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_FEATURE) + 1u;
                    code.Append(GenerateTDHeader(String.Format("{0}_FEATURE_RPT_TABLE[{1}u]", qualName, rptTableLen)));
                    for (int i = 0; i < rptTableLen; i++)
                    {
                        CyHidReportID rpt = CyHidReportID.ReportWithID(reports, (byte)i,
                                                                       CyHidReportItem.RPTITEM_FEATURE);
                        if (rpt != null)
                        {
                            string idStr = rpt.GetIDString();
                            code.Append(GenerateTDEntry(qualName + "_FEATURE_BUF_SIZE" + idStr,
                                     qualName + "_FEATURE_BUF" + idStr + "[0u]", qualName + "_FEATURE_RPT_SCB" + idStr));
                        }
                        else
                        {
                            code.Append(GenerateTDEntry(HexByteString(0), NULL_PTR, NULL_PTR));
                        }
                        code.Append(COMMA_NEWLINE);
                    }
                    code.AppendFormat("{0};{1}", GenerateFooter(), NEWLINE);
                    AddDefineNoInstance(qualName + "_NUM_FEATURE_RPTS", (uint)featureReportsCount);
                }
                // Generate define for compability with previous versions
                if (reports.Count > 0 && reports[0].m_hasID)
                {
                    int maxID = 0;
                    if (inputReportsCount > 0)
                    {
                        maxID = CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_INPUT);
                        AddDefineNoInstance(qualName + "_IN_RPT_SCB", qualName + "_IN_RPT_SCB_ID" + maxID);
                        AddDefineNoInstance(qualName + "_IN_BUF", qualName + "_IN_BUF_ID" + maxID);
                        AddDefineNoInstance(qualName + "_IN_BUF_SIZE", qualName + "_IN_BUF_SIZE_ID" + maxID);
                    }
                    if (outputReportsCount > 0)
                    {
                        maxID = CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_OUTPUT);
                        AddDefineNoInstance(qualName + "_OUT_RPT_SCB", qualName + "_OUT_RPT_SCB_ID" + maxID);
                        AddDefineNoInstance(qualName + "_OUT_BUF", qualName + "_OUT_BUF_ID" + maxID);
                        AddDefineNoInstance(qualName + "_OUT_BUF_SIZE", qualName + "_OUT_BUF_SIZE_ID" + maxID);
                    }
                    if (featureReportsCount > 0)
                    {
                        maxID = CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_FEATURE);
                        AddDefineNoInstance(qualName + "_FEATURE_RPT_SCB", qualName + "_FEATURE_RPT_SCB_ID" + maxID);
                        AddDefineNoInstance(qualName + "_FEATURE_BUF", qualName + "_FEATURE_BUF_ID" + maxID);
                        AddDefineNoInstance(qualName + "_FEATURE_BUF_SIZE", qualName + "_FEATURE_BUF_SIZE_ID" + maxID);
                    }
                }

                code.AppendLine("/*********************************************************************");
                code.AppendLine("* HID Report Look Up Table         This table has four entries:");
                code.AppendLine("*                                        IN Report Table");
                code.AppendLine("*                                        OUT Report Table");
                code.AppendLine("*                                        Feature Report Table");
                code.AppendLine("*                                        HID Report Descriptor");
                code.AppendLine("*                                        HID Class Descriptor");
                code.AppendLine("*********************************************************************/");
                code.Append(GenerateLUTHeader(qualName + "_TABLE[5u]"));
                AddDefineNoInstance(qualName + "_COUNT", 1); // HID Class only has one LUT to link to the Interface

                if (inputReportsCount > 0)
                {
                    code.Append(GenerateLUTEntry(qualName + "_IN_RPT_TABLE",
                        (byte)(CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_INPUT))));
                }
                else
                {
                    code.Append(GenerateNullLUTEntry());
                }
                code.Append(COMMA_NEWLINE);
                if (outputReportsCount > 0)
                {
                    code.Append(GenerateLUTEntry(qualName + "_OUT_RPT_TABLE",
                        (byte)(CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_OUTPUT))));
                }
                else
                {
                    code.Append(GenerateNullLUTEntry());
                }
                code.Append(COMMA_NEWLINE);
                if (featureReportsCount > 0)
                {
                    code.Append(GenerateLUTEntry(qualName + "_FEATURE_RPT_TABLE",
                        (byte)(CyHidReportID.GetMaxReportID(reports, CyHidReportItem.RPTITEM_FEATURE))));
                }
                else
                {
                    code.Append(GenerateNullLUTEntry());
                }
                code.Append(COMMA_NEWLINE);
                string s = GenerateLUTEntry(string.Format("{0}_HIDREPORT_DESCRIPTOR{1}[0]", instName, rptIndex), 1);
                s = s.Replace("&", "(const void *)&");
                code.Append(s);
                code.Append(COMMA_NEWLINE);
                // Find appropriate reference
                string qualNameWithoutHid = qualName.Remove(qualName.LastIndexOf("_HID"), "_HID".Length);
                string qualNameWithoutInterface = qualName.Remove(qualName.LastIndexOf("_INTERFACE"));
                int ind = HidClassQualList.IndexOf(qualNameWithoutHid);
                s = GenerateLUTEntry(string.Format("{0}_DESCR[{1}]", qualNameWithoutInterface,
                                     m_hidClassReferences[ind]), 1);
                s = s.Replace("&", "(const void *)&");
                code.Append(s);

                code.AppendLine();
                code.AppendFormat("{0};{1}", GenerateFooter(), NEWLINE);
                code.AppendFormat("#endif /* USER_DEFINE_{0}_HID_RPT_STORAGE */{1}", qualName, NEWLINE);
            }
            return code.ToString();
        }

        private static List<CyHidReportID> GetReportIDList(CyDescriptorNode nodeRpt)
        {
            List<CyHidReportID> reportIDs = new List<CyHidReportID>();
            for (int i = 0; i < nodeRpt.Nodes.Count; i++)
            {
                CyDescriptorNode node = nodeRpt.Nodes[i];
                if (node.Value != null)
                {
                    if (node.Value.bDescriptorType == CyUSBDescriptorType.HID_REPORT_ITEM)
                    {
                        CyHidReportID currentReport = null;
                        CyHIDReportItemDescriptor h = (CyHIDReportItemDescriptor)node.Value;
                        if (h.Item.Name == CyHidReportItem.RPTITEM_REPORT_ID)
                        {
                            if (h.Item.m_value.Count >= 2)
                            {
                                reportIDs.Add(new CyHidReportID());
                                currentReport = reportIDs[reportIDs.Count - 1];
                                currentReport.m_id = h.Item.m_value[1];
                                currentReport.m_hasID = true;
                                currentReport.m_inputSize =
                                    (ushort)ReportSize(nodeRpt, CyHidReportItem.RPTITEM_INPUT, currentReport);
                                currentReport.m_outputSize =
                                    (ushort)ReportSize(nodeRpt, CyHidReportItem.RPTITEM_OUTPUT, currentReport);
                                currentReport.m_featureSize =
                                    (ushort)ReportSize(nodeRpt, CyHidReportItem.RPTITEM_FEATURE, currentReport);

                            }
                        }
                    }
                }
            }
            if (reportIDs.Count == 0)
            {
                reportIDs.Add(new CyHidReportID());
                CyHidReportID currentReport = reportIDs[reportIDs.Count - 1];
                currentReport.m_hasID = false;
                currentReport.m_inputSize =
                    (ushort)ReportSize(nodeRpt, CyHidReportItem.RPTITEM_INPUT, currentReport);
                currentReport.m_outputSize =
                    (ushort)ReportSize(nodeRpt, CyHidReportItem.RPTITEM_OUTPUT, currentReport);
                currentReport.m_featureSize =
                    (ushort)ReportSize(nodeRpt, CyHidReportItem.RPTITEM_FEATURE, currentReport);
            }
            return reportIDs;
        }

        private static uint ReportSize(CyDescriptorNode n, string itemType, CyHidReportID rpt)
        {
            CyHIDReportItemDescriptor h;
            long fullSize = 0;
            long curSize = 0;
            long curCount = 0;
            bool foundRptID = !rpt.m_hasID;
            for (int i = 0; i < n.Nodes.Count; i++)
            {
                h = (CyHIDReportItemDescriptor)n.Nodes[i].Value;
                if (h.Item.Name == CyHidReportItem.RPTITEM_REPORT_ID)
                {
                    foundRptID = (h.Item.m_value[1] == rpt.m_id);
                }
                if (!foundRptID)
                {
                    continue;
                }

                if ((h.Item.Name == CyHidReportItem.RPTITEM_REPORT_SIZE) ||
                    (h.Item.Name == CyHidReportItem.RPTITEM_REPORT_COUNT))
                {
                    List<byte> tmpArr = new List<byte>(h.Item.m_value);
                    if (tmpArr.Count > 0)
                        tmpArr.RemoveAt(0);
                    if (h.Item.Name == CyHidReportItem.RPTITEM_REPORT_SIZE)
                        curSize = CyUSBFSParameters.ConvertByteArrayToInt(tmpArr, true);
                    if (h.Item.Name == CyHidReportItem.RPTITEM_REPORT_COUNT)
                        curCount = CyUSBFSParameters.ConvertByteArrayToInt(tmpArr, true);
                }
                else if (h.Item.Name == itemType)
                {
                    fullSize += curSize * curCount;
                }
            }
            //if (fullSize == 0)
            //    fullSize = curSize * curCount;
            // COnvert from bits to bytes
            if (fullSize % 8 == 0)
            {
                fullSize /= 8;
            }
            else
            {
                fullSize = fullSize/8 + 1;
            }
            // Max size is limited to 64 bytes
            if (fullSize > 64) fullSize = 64;
            // Add 1 byte for Report ID
            if (fullSize > 0)
            {
                fullSize++;
            }
            return (ushort)fullSize;
        }

        private void GetMidiBuffSize(CyDescriptorNode node, ref ushort inSize, ref ushort outSize)
        {
            if ((node.Value != null) && (node.Value is CyAudioInterfaceDescriptor) &&
                (((CyAudioInterfaceDescriptor)node.Value).bInterfaceSubClass ==
                  (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING))
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    if ((node.Nodes[i].Value != null) && (node.Nodes[i].Value is CyEndpointDescriptor))
                    {
                        CyEndpointDescriptor epDesc = (CyEndpointDescriptor)node.Nodes[i].Value;
                        if (epDesc.Direction == CyUSBOtherTypes.CyEndptDirections.IN)
                        {
                            if (epDesc.wMaxPacketSize > inSize)
                                inSize = epDesc.wMaxPacketSize;
                        }
                        else
                        {
                            if (epDesc.wMaxPacketSize > outSize)
                                outSize = epDesc.wMaxPacketSize;
                        }
                    }
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    GetMidiBuffSize(node.Nodes[i], ref inSize, ref outSize);
                }
            }
        }

        private string GetEpDmaReqTrOutArray()
        {
            StringBuilder res = new StringBuilder();

            res.Append("0u,");

            for(int i = 1; i < m_parameters.UsedEp.Length; i++)
            {
                if (m_parameters.UsedEp[i])
                    res.Append(string.Format("{0}        {1}_ep{2}_dma__TR_OUTPUT,", NEWLINE, INSTANCE_NAME, i));
                else
                    res.Append(string.Format("{0}        0u,", NEWLINE));
            }

            return res.ToString();
        }

        private void GetEpTables(out StringBuilder epManagementDmaTable, out StringBuilder epTermoutEnTable)
        {
            epManagementDmaTable = new StringBuilder();
            epTermoutEnTable = new StringBuilder();

            // first element always 0.
            epManagementDmaTable.AppendFormat("0u,\r\n");
            epTermoutEnTable.AppendFormat("0u,\r\n");

            for (int epNum = 1; epNum < CyEndpointDescriptor.MAX_EP_NUM; epNum++)
            {
                GetepEpManagementRow(epNum, ref epManagementDmaTable, ref epTermoutEnTable);
                epManagementDmaTable.AppendLine();
                epTermoutEnTable.AppendLine();
            }

            GetepEpManagementRow(CyEndpointDescriptor.MAX_EP_NUM, ref epManagementDmaTable, ref epTermoutEnTable);
        }

        private void GetepEpManagementRow(int epNum, ref StringBuilder epManagementDmaTable,
            ref StringBuilder epTermoutEnTable)
        {
            if (epNum >= m_parameters.UsedEp.Length)
                Debug.Fail("m_parameters.UsedEp[] out of range.");

            if ((m_parameters.EPMemoryMgmt == CyUSBFSParameters.CyMemoryManagement.EP_DMAauto ||
                m_parameters.EPMemoryMgmt == CyUSBFSParameters.CyMemoryManagement.EP_DMAmanual) &&
                m_parameters.UsedEp[epNum])
            {
                epManagementDmaTable.AppendFormat("            (uint8) {0}_ep{1}_dma_CHANNEL,", INSTANCE_NAME, epNum);
                epTermoutEnTable.AppendFormat("            {0}_ep{1}__TD_TERMOUT_EN,", INSTANCE_NAME, epNum);
            }
            else
            {
                epManagementDmaTable.AppendFormat("            0u,");
                epTermoutEnTable.AppendFormat("            0u,");
            }
        }

        private void GetIsrCallBacksTable(out StringBuilder isrCallBacksTable)
        {
            isrCallBacksTable = new StringBuilder();

            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.EnableSofInterrupt, "SOF"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.IsBusReset, "BUS_RESET"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.IsEp0, "EP_0"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.IsLpm, "LPM"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.EPMemoryMgmt !=
                CyUSBFSParameters.CyMemoryManagement.EP_Manual, "ARB"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.UsedEp[1], "EP_1"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.UsedEp[2], "EP_2"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.UsedEp[3], "EP_3"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.UsedEp[4], "EP_4"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.UsedEp[5], "EP_5"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.UsedEp[6], "EP_6"));
            isrCallBacksTable.AppendLine(GetCallBacksTableRow(m_parameters.UsedEp[7], "EP_7"));
            isrCallBacksTable.AppendFormat(GetCallBacksTableRow(m_parameters.UsedEp[8], "EP_8"));
        }

        private string GetCallBacksTableRow(bool isIsr, string name)
        {
            if (isIsr)
                return string.Format("            &{0}_{1}_ISR,", INSTANCE_NAME, name);
            else
                return "            NULL,";
        }

        private uint GetLvlSelReg()
        {
            uint interruptReg = 0;

            if (m_parameters.EPMemoryMgmt != CyUSBFSParameters.CyMemoryManagement.EP_Manual)
                interruptReg |= (uint)m_parameters.ArbiterIntrGroup << ARB_EP_LVL_SEL_OFFSET;
            if (m_parameters.EnableSofInterrupt)
                interruptReg |= (uint)m_parameters.StartOfFrameIntrGroup << SOF_LVL_SEL_OFFSET;
            if (m_parameters.IsBusReset)
                interruptReg |= (uint)m_parameters.BusResetIntrGroup << BUS_RSET_LVL_SEL_OFFSET;

            interruptReg |= (uint)m_parameters.Ep0IntrGroup << EP0_LVL_SEL_OFFSET;

            if (m_parameters.IsEp1)
                interruptReg |= (uint)m_parameters.Ep1IntrGroup << EP1_LVL_SEL_OFFSET;
            if (m_parameters.IsEp2)
                interruptReg |= (uint)m_parameters.Ep2IntrGroup << EP2_LVL_SEL_OFFSET;
            if (m_parameters.IsEp3)
                interruptReg |= (uint)m_parameters.Ep3IntrGroup << EP3_LVL_SEL_OFFSET;
            if (m_parameters.IsEp4)
                interruptReg |= (uint)m_parameters.Ep4IntrGroup << EP4_LVL_SEL_OFFSET;
            if (m_parameters.IsEp5)
                interruptReg |= (uint)m_parameters.Ep5IntrGroup << EP5_LVL_SEL_OFFSET;
            if (m_parameters.IsEp6)
                interruptReg |= (uint)m_parameters.Ep6IntrGroup << EP6_LVL_SEL_OFFSET;
            if (m_parameters.IsEp7)
                interruptReg |= (uint)m_parameters.Ep7IntrGroup << EP7_LVL_SEL_OFFSET;
            if (m_parameters.IsEp8)
                interruptReg |= (uint)m_parameters.Ep8IntrGroup << EP8_LVL_SEL_OFFSET;

            if (m_parameters.IsLpm)
                interruptReg |= (uint)m_parameters.LpmIntrGroup << LPM_LVL_SEL_OFFSET;

            return interruptReg;
        }

        /// <summary>
        /// Template for defines generation. General header.
        /// </summary>
        /// <param name="d"></param>
        private void AddDefine(string d)
        {
            AddDefineNoInstance(string.Format("{0}_{1}", m_instanceName, d), "");
        }

        /// <summary>
        /// Template for defines generation. General header.
        /// </summary>
        /// <param name="d"></param>
        private void AddDefine(string d, string v)
        {
            v = String.Format("({0}u)", v.TrimEnd('u'));
            AddDefineNoInstance(string.Format("{0}_{1}", m_instanceName, d), v);
        }

        /// <summary>
        /// Template for defines generation. MIDI header.
        /// </summary>
        /// <param name="d"></param>
        private void AddDefineMidi(string d)
        {
            AddDefineNoInstance(string.Format("{0}_{1}", m_instanceName, d), "", MIDI_APIGEN_DEFINES);
        }

        /// <summary>
        /// Template for defines generation. MIDI header.
        /// </summary>
        /// <param name="d"></param>
        private void AddDefineMidi(string d, string v)
        {
            v = String.Format("({0}u)", v.TrimEnd('u'));
            AddDefineNoInstance(string.Format("{0}_{1}", m_instanceName, d), v, MIDI_APIGEN_DEFINES);
        }

        /// <summary>
        /// Template for defines generation.
        /// </summary>
        /// <param name="d"></param>
        private void AddDefineNoInstance(string d, uint v, string paramName = APIGEN_DEFINES)
        {
            string val = String.Format("({0}u)", v);
            AddDefineNoInstance(d, val, paramName);
        }

        /// <summary>
        /// Template for defines generation.
        /// </summary>
        /// <param name="d"></param>
        private void AddDefineNoInstance(string d, string v, string paramName = APIGEN_DEFINES)
        {
            string defs;
            bool noErr = m_codeParameters.TryGetValue(paramName, out defs);
            //Debug.Assert(noErr);
            m_codeParameters.Remove(paramName);
            defs += string.Format("#define {0}", d).PadRight(DEF_VALUE_PADRIGHT) + string.Format(" {0}", v) + NEWLINE;

            m_codeParameters.Add(paramName, defs);
        }

        private List<string> GetFunctionHeaders(string code)
        {
            List<string> headers = new List<string>();

            //Regex
            const string HEADER_PATTERN = @"(const[^\n]+\](?= =))";
            Regex rgx = new Regex(HEADER_PATTERN);
            MatchCollection matches = rgx.Matches(code);
            foreach (Match match in matches)
            {
                headers.Add(match.Value);
            }

            return headers;
        }

        /// <summary>
        /// Template for function declaration
        /// </summary>
        /// <param name="func"></param>
        private void AddFuncDeclaration(string func)
        {
            string defs;
            bool noErr = m_codeParameters.TryGetValue(APIGEN_FUNCDECL, out defs);
            m_codeParameters.Remove(APIGEN_FUNCDECL);
            if (func.Contains(";"))
            {
                defs += string.Format("extern {0}", func);
            }
            else
            {
                defs += string.Format("extern {0};{1}", func, NEWLINE);
            }
            m_codeParameters.Add(APIGEN_FUNCDECL, defs);
        }

        private void AddFuncDeclarations(string code)
        {
            List<string> headers = GetFunctionHeaders(code);
            for (int i = 0; i < headers.Count; i++)
            {
                AddFuncDeclaration(headers[i]);
            }
        }

        public Dictionary<string, string> CodeParameterDictionary
        {
            get { return m_codeParameters; }
        }
    }

    /// <summary>
    /// CyUsbCodePrimitives class contains miscellaneous functions for standard code generation
    /// </summary>
    public class CyUsbCodePrimitives
    {
        private const int MAX_LINE_LENGTH = 120;
        private const int COMMENT_WIDTH = 40;
        public const string COMMA_NEWLINE = ",\r\n";
        public const string NEWLINE = "\r\n";
        public const string FOOTER_BRACKET = NEWLINE + "};" + NEWLINE;
        public const string CODE = "CYCODE";
        private string m_instanceName;

        private static List<string> m_hidClassQualList = new List<string>();

        public static List<string> HidClassQualList
        {
            get { return CyUsbCodePrimitives.m_hidClassQualList; }
            set { CyUsbCodePrimitives.m_hidClassQualList = value; }
        }

        public CyUsbCodePrimitives(string instanceName)
        {
            m_instanceName = instanceName;
        }

        public string GenerateAllocateArray(string n, int s)
        {
            return GenerateAllocateArray(n, s.ToString());
        }

        public string GenerateAllocateArray(string n, string s)
        {
            string code = String.Format("uint8 {0}[{1}            {2}];{1}", n, NEWLINE, s);
            return code;
        }

        public byte MSB(ushort i)
        {
            return (byte) (0xff & (i >> 8));
        }

        public byte LSB(ushort i)
        {
            return (byte) (0xff & i);
        }

        public string BoolToIntString(bool b)
        {
            return Convert.ToInt32(b).ToString();
        }

        public string HexByteString(byte b)
        {
            return string.Format("0x{0:X2}u", b);
        }

        public string HexWordString(ushort w)
        {
            return string.Format("0x{0:X4}u", w);
        }

        public string HexDoubleWordString(uint w)
        {
            return string.Format("0x{0:X8}u", w);
        }

        public string GenerateDescrByte(string c, byte b)
        {
            return GenerateDescrByteArray(c, new byte[] {b});
        }

        public string GenerateDescrDWLS(string c, ushort u)
        {
            return GenerateDescrByteArray(c, new byte[] { LSB(u), MSB(u) });
        }

        public string GenerateDescr3Byte(string c, uint u)
        {
            return GenerateDescrByteArray(c, new byte[]
                                             {(byte) (0xff & u), (byte) (0xff & (u >> 8)), (byte) (0xff & (u >> 16))});
        }

        public string GenerateDescrInt(string c, uint u)
        {
            return GenerateDescrByteArray(c, new byte[] { (byte)(0xff & u), (byte)(0xff & (u >> 8)),
                                                          (byte)(0xff & (u >> 16)), (byte)(0xff & (u >> 24)) });
        }

        public string GenerateDescrByteArray(string c, byte[] b)
        {
            StringBuilder s = new StringBuilder();
            s.AppendFormat("/* {0}*/ ", c.PadRight(COMMENT_WIDTH, ' '));
            if (b.Length > 0)
            {
                for (int i = 0; i < b.Length - 1; i++)
                {
                    s.Append(HexByteString(b[i]));
                    s.Append(", ");
                }
                s.Append(HexByteString(b[b.Length - 1]));
            }
            return s.ToString();
        }

        public string GenerateDescrDWLSArray(string c, ushort[] b)
        {
            StringBuilder s = new StringBuilder();
            s.AppendFormat("/* {0}*/ ", c.PadRight(COMMENT_WIDTH, ' '));
            if (b.Length > 0)
            {
                for (int i = 0; i < b.Length - 1; i++)
                {
                    s.Append(HexByteString(LSB(b[i])));
                    s.Append(", ");
                    s.Append(HexByteString(MSB(b[i])));
                    s.Append(", ");
                }
                s.Append(HexByteString(LSB(b[b.Length - 1])));
                s.Append(", ");
                s.Append(HexByteString(MSB(b[b.Length - 1])));
            }
            return s.ToString();
        }

        public string GenerateDescr3ByteArray(string c, uint[] b)
        {
            return GenerateDescrCustomArray(c, b, 3);
        }

        public string GenerateDescrCustomArray(string c, uint[] b, int num)
        {
            StringBuilder s = new StringBuilder();
            s.AppendFormat("/* {0}*/ ", c.PadRight(COMMENT_WIDTH, ' '));
            int len = s.Length;
            if (b.Length > 0)
            {
                for (int i = 0; i < b.Length; i++)
                {
                    for (int j = 0; j < num; j++)
                    {
                        if (j < 4) // max possible num for uint is 4
                            s.Append(HexByteString((byte)(0xff & (b[i] >> (8 * j)))));
                        else
                            s.Append(HexByteString(0x00));
                        s.Append(", ");
                    }
                    if (i < b.Length - 1)
                    {
                        s.AppendLine();
                        s.Append("".PadLeft(len));
                    }
                }

                s = new StringBuilder(s.ToString().TrimEnd(' ', ','));
            }
            return s.ToString();
        }

        public string GeneratePtr(string d)
        {
            string s = string.Format("    &{0}", d);
            return s;
        }

        public string GenerateUsbUnicode(string d)
        {
            StringBuilder s = new StringBuilder();
            string comma = "";
            int lineLength = 0;

            if (String.IsNullOrEmpty(d) == false)
            {
                for (int i = 0; i < d.Length; i++)
                {
                    s.Append(comma);
                    if (lineLength > 72)
                    {
                        s.AppendLine();
                        s.Append(" ");
                        lineLength = 1;
                    }

                    s.AppendFormat("(uint8)'{0}', 0u", d.Substring(i, 1));
                    comma = ",";
                    lineLength += 15;
                }
            }
            return s.ToString();
        }

        public string GenerateVoidPtr(string d)
        {
            string s = string.Format("    (const void *)({0})", d);
            return s;
        }

        public string GenerateReportItem(CyHIDReportItemDescriptor d)
        {
            StringBuilder s = new StringBuilder();
            s.AppendFormat("/* {0}*/ ", d.Item.Name.PadRight(COMMENT_WIDTH, ' '));
            for (byte i = 0; i < d.Item.GetItemSize(); i++)
            {
                s.Append(HexByteString(d.Item.m_value[i]) + ", ");
            }
            s.Append(NEWLINE);
            return s.ToString();
        }

        public static ushort ReportDescriptorSize(List<CyDescriptorNode> nodes)
        {
            ushort size = 0;
            CyHIDReportItemDescriptor h;
            for (int i = 0; i < nodes.Count; i++)
            {
                h = (CyHIDReportItemDescriptor)nodes[i].Value;
                size += h.Item.GetItemSize();
            }
            return size;
        }

        public string GenerateSymbolicByte(string c, string sym)
        {
            string s = string.Format("/* {0}*/ ", c.PadRight(COMMENT_WIDTH, ' '));
            s += sym;
            return s;
        }

        public string GenerateWordCount(string c, ushort u)
        {
            StringBuilder s = new StringBuilder();
            s.AppendFormat("/* {0}*/ ", c.PadRight(COMMENT_WIDTH, ' '));
            s.Append(HexByteString(LSB(u)));
            s.Append(", ");
            s.Append(HexByteString(MSB(u)));
            return s.ToString();
        }

        public string GenerateByte(byte b)
        {
            string s = HexByteString(b);
            return s;
        }

        public string GenerateWord(ushort w)
        {
            string s = HexWordString(w);
            return s;
        }

        public string GenerateLUTHeader(string n)
        {
            string s = String.Format("const T_{0}_LUT {1} {2} = {{{3}", INSTANCE_NAME, CODE, n, Environment.NewLine);
            return s;
        }

        public string GenerateLUTEntry(string n, byte c)
        {
            StringBuilder s = new StringBuilder();
            s.Append("    {");
            s.Append(HexByteString(c));
            s.Append(", ");
            s.Append(GeneratePtr(n));
            s.Append("}");
            return s.ToString();
        }

        public string GenerateLUTEntry(string n, string c)
        {
            string s = String.Format("    {{{0}, {1}}}", c, GeneratePtr(n));
            if (s.Length > MAX_LINE_LENGTH)
                s = s.Insert(s.IndexOf(',') + 2, "\r\n");
            return s;
        }

        public string GenerateNullLUTEntry()
        {
            StringBuilder s = new StringBuilder();
            s.AppendFormat("    {{{0},    {1}}}", HexByteString(0), NULL_PTR);
            return s.ToString();
        }

        public string GenerateTDHeader(string n)
        {
            string s = String.Format("const T_{0}_TD {1} {2} = {{{3}", INSTANCE_NAME, CODE, n, NEWLINE);
            return s;
        }

        public string GenerateTDEntry(byte c, string p, string d)
        {
            StringBuilder s = new StringBuilder();
            s.Append("    {{");
            s.AppendFormat("{0}, ", HexByteString(c));
            s.Append(p == NULL_PTR ? NULL_PTR : GeneratePtr(p));
            s.Append(", ");
            s.Append(d == NULL_PTR ? NULL_PTR : GeneratePtr(d));
            s.Append("}}");
            return s.ToString();
        }

        public string GenerateTDEntry(string c, string p, string d)
        {
            StringBuilder s = new StringBuilder();
            s.AppendFormat("    {{{0}{1}", c, COMMA_NEWLINE);
            s.Append(p == NULL_PTR ? ("    " + NULL_PTR) : GeneratePtr(p));
            s.Append(COMMA_NEWLINE);
            s.Append(d == NULL_PTR ? ("    " + NULL_PTR) : GeneratePtr(d));
            s.Append("}");
            return s.ToString();
        }

        public string GenerateNullTDEntry()
        {
            string s = String.Format("    {{{0}, {0}, {0}}}", HexByteString(0));
            return s;
        }

        public string GenerateFooter()
        {
            return "}";
        }

        public static string GenerateQualName(string qual, CyDescriptorNode node, int i)
        {
            if (node.Value.bDescriptorType == CyUSBDescriptorType.ALTERNATE)
            {
                qual = String.Format("{0}_INTERFACE{1}", qual, i);
            }
            else if (node.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE)
            {
                qual = String.Format("{0}_ALTERNATE{1}", qual, i);
            }
            else if (node.Value.bDescriptorType == CyUSBDescriptorType.HID)
            {
                qual = String.Format("{0}_{1}", qual, node.Value.bDescriptorType);
            }
            else if (node.Value.bDescriptorType == CyUSBDescriptorType.BOS)
            {
                qual = String.Format("{0}_{1}", qual, node.Value.bDescriptorType);
            }
            else
            {
                qual = String.Format("{0}_{1}", qual, node.Value.bDescriptorType + i.ToString());
            }
            return qual;
        }

        public static int GetElemNumInArray(string code)
        {
            int sum = -1;
            int ind1 = code.LastIndexOf('{');
            while (ind1 >= 0)
            {
                sum++;
                ind1 = code.IndexOf(',', ind1+1);
            }
            return sum;
        }

        public static StringBuilder InsertLengthInArrayHeader(string code, uint length)
        {
            int lastIndex = code.LastIndexOf("[]");
            if (lastIndex >= 0)
            {
                code = code.Insert(lastIndex + 1, String.Format("{0}u", length));
            }

            return new StringBuilder(code);
        }

        public string INSTANCE_NAME
        {
            get { return m_instanceName; }
            set { m_instanceName = value; }
        }

        public string NULL_PTR
        {
            get { return "NULL"; }
        }
    }

    #region Descriptor Code Generators

    public abstract class CyUsbCodeGen : CyUsbCodePrimitives
    {
        protected string m_nl;

        public CyUsbCodeGen(string instanceName) : base(instanceName)
        {
            m_nl = "";
        }

        public virtual string Generate(List<CyDescriptorNode> nodes, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyUsbCodeGenMaker f = new CyUsbCodeGenMaker();
            CyUsbDescriptorGenTree cgt = new CyUsbDescriptorGenTree();

            for (int i = 0; i < nodes.Count; i++)
            {
                string qual = GenerateQualName(qualName,nodes[i], i);
                CyUsbCodeGen cg = f.MakeDescriptorGenerator(nodes[i].Value, INSTANCE_NAME);
                code.Append(cg.GenHeader(nodes[i].Value, instName, qual));
                code.Append(cg.GenBody(nodes[i].Value, instName, qual));
                code.Append(cgt.Generate(nodes[i].Nodes, instName, qual));
                code.Append(cg.GenFooter(nodes[i].Value, instName, qual));
            }
            return code.ToString();
        }

        public virtual string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            return String.Empty;
        }

        public abstract string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName);
        public abstract string GenBody(CyUSBDescriptor ud, string instanceName, string qualName);
        public abstract string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName);

        protected string GenLUTEntry(string instanceName, string tableSuffix, byte c)
        {
            StringBuilder code = new StringBuilder();
            code.Append(m_nl);
            m_nl = COMMA_NEWLINE;
            code.Append(GenerateLUTEntry(instanceName + tableSuffix, c));
            return code.ToString();
        }

        protected string GenNullLUTEntry()
        {
            StringBuilder code = new StringBuilder();
            code.Append(m_nl);
            m_nl = COMMA_NEWLINE;
            code.Append(GenerateNullLUTEntry());
            return code.ToString();
        }
    }

    internal class CyUsbDeviceDescriptorGen : CyUsbCodeGen
    {
        public CyUsbDeviceDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyDeviceDescriptor d = (CyDeviceDescriptor) ud;
            // Header Comment
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Device Descriptors");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("const uint8 {0} {1}_DESCR[{2}u] = {{{3}", CODE, qualName, d.bLength, NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}",
                              GenerateDescrByte("DescriptorType: DEVICE", (byte) d.bDescriptorType), COMMA_NEWLINE);

            if (d.bcdUSB == CyDeviceDescriptor.BCDUSB_WITHOUT_BOS)
                code.AppendFormat("{0}{1}", GenerateDescrDWLS("bcdUSB (ver 2.0)", d.bcdUSB), COMMA_NEWLINE); // 0x0200
            else
                code.AppendFormat("{0}{1}", GenerateDescrDWLS("bcdUSB (ver 2.01)", d.bcdUSB), COMMA_NEWLINE); // 0x0201

            code.AppendFormat("{0}{1}", GenerateDescrByte("bDeviceClass", d.bDeviceClass), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("bDeviceSubClass", d.bDeviceSubClass), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("bDeviceProtocol", d.bDeviceProtocol), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("bMaxPacketSize0", 8), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrDWLS("idVendor", d.idVendor), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrDWLS("idProduct", d.idProduct), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrDWLS("bcdDevice", d.bcdDevice),COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("iManufacturer", d.iManufacturer), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("iProduct", d.iProduct), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("iSerialNumber", d.iSerialNumber),COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("bNumConfigurations", d.bNumConfigurations), NEWLINE);
            code.AppendLine("};");

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbBosDescriptorGen : CyUsbCodeGen
    {
        public CyUsbBosDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return string.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            CyBosDescriptor d = (CyBosDescriptor)ud;
            // Header Comment
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* BOS Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("const uint8 {0} {1}_DESCR[{2}u] = {{{3}", CODE, qualName, d.wTotalLength, NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" BOS Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: BOS", (byte)d.bDescriptorType),
                COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTotalLength", d.wTotalLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bNumDeviceCaps", d.bNumDeviceCaps), COMMA_NEWLINE);

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return FOOTER_BRACKET;
        }
    }

    internal class CyUsb20ExtensionDescriptorGen : CyUsbCodeGen
    {
        public CyUsb20ExtensionDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return string.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            CyUsb20ExtensionDeviceCapabilityDescriptor d = (CyUsb20ExtensionDeviceCapabilityDescriptor)ud;
            // Header Comment
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Usb 2.0 Extension Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorType: Device Capability",
                CyUsb20ExtensionDeviceCapabilityDescriptor.DEVICE_CAPABILITY_TYPE_CODE), // hardcoded
                COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDevCapabilityType: USB 2.0 Extension",
                d.bDevCapabilityType), COMMA_NEWLINE);
            code.Append(GenerateDescrInt(" bmAttributes", d.bmAttributes));

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return string.Empty;
        }
    }

    internal class CyContainerIdDescriptorGen : CyUsbCodeGen
    {
        public CyContainerIdDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return string.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            CyContainerIdDescriptor d = (CyContainerIdDescriptor)ud;
            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Container ID Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorType: Device Capability",
                CyContainerIdDescriptor.DEVICE_CAPABILITY_TYPE_CODE), // hardcoded
                COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDevCapabilityType: USB 2.0 Extension",
                d.bDevCapabilityType), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bReserved", (byte)0), COMMA_NEWLINE);

            List<byte> listUuid = CyContainerIdDescriptor.UuidToHexByteList(d.ContainerId);

            for (int byteNum = 0; byteNum < listUuid.Count; byteNum++)
            {
                string commaNewLine = COMMA_NEWLINE;

                if (byteNum == listUuid.Count - 1)
                    commaNewLine = string.Empty;

                code.AppendFormat("{0}{1}", GenerateDescrByte(string.Format(" Container ID (byte[{0}])", byteNum),
                    listUuid[byteNum]), commaNewLine);
            }

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return string.Empty;
        }
    }

    internal class CyUsbConfigDescriptorGen : CyUsbCodeGen
    {
        public CyUsbConfigDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyConfigDescriptor d = (CyConfigDescriptor) ud;
            // Header Comment
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Config Descriptor  ");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("const uint8 {0} {1}_DESCR[{2}u] = {{{3}", CODE, qualName, d.wTotalLength, NEWLINE);

            code.AppendFormat("{0}{1}", GenerateDescrByte(" Config Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: CONFIG", (byte) d.bDescriptorType),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTotalLength", d.wTotalLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bNumInterfaces", d.bNumInterfaces), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bConfigurationValue", (byte) (d.bConfigurationValue + 1)),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" iConfiguration", d.iConfiguration), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bmAttributes", d.bmAttributes), COMMA_NEWLINE);
            code.Append(GenerateDescrByte(" bMaxPower", d.bMaxPower));

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return FOOTER_BRACKET;
        }
    }

    internal class CyUsbInterfaceGeneralDescriptorGen : CyUsbCodeGen
    {
        public CyUsbInterfaceGeneralDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbInterfaceDescriptorGen : CyUsbCodeGen
    {
        public CyUsbInterfaceDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyInterfaceDescriptor d = (CyInterfaceDescriptor) ud;
            string isAudioCdcOrMs = ((ud is CyAudioInterfaceDescriptor) && (d.bInterfaceSubClass ==
                                    (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING)) ? "MIDIStreaming " :
                                    ((ud is CyAudioInterfaceDescriptor) && (d.bInterfaceSubClass ==
                                    (byte)CyUSBOtherTypes.CyAudioSubclassCodes.AUDIOSTREAMING)) ? "AudioStreaming " :
                                    ((ud is CyAudioInterfaceDescriptor) && (d.bInterfaceSubClass ==
                                    (byte)CyUSBOtherTypes.CyAudioSubclassCodes.AUDIOCONTROL)) ? "AudioControl " :
                                    (ud is CyAudioInterfaceDescriptor) ? "Audio " :
                                    (ud is CyDataInterfaceDescriptor) ? "Data " :
                                    (ud is CyCDCInterfaceDescriptor) ? "CDC " :
                                    (ud is CyMscInterfaceDescriptor) ? "MSC " : String.Empty;
            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendFormat("* {0}Interface Descriptor", isAudioCdcOrMs).AppendLine();
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" Interface Descriptor Length", d.bLength),COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: INTERFACE", (byte) d.bDescriptorType),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bInterfaceNumber", d.bInterfaceNumber), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bAlternateSetting", d.bAlternateSetting), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bNumEndpoints", d.bNumEndpoints), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bInterfaceClass", d.bInterfaceClass), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bInterfaceSubClass", d.bInterfaceSubClass), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bInterfaceProtocol", d.bInterfaceProtocol),COMMA_NEWLINE);
            code.Append(GenerateDescrByte(" iInterface", d.iInterface));

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbIntAssociationDescriptorGen : CyUsbCodeGen
    {
        public CyUsbIntAssociationDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyInterfaceAssociationDescriptor d = (CyInterfaceAssociationDescriptor)ud;

            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Interface Association Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" Interface Association Descriptor Length", d.bLength),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: INTERFACE ASSOCIATION",
                              (byte)d.bDescriptorType), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bFirstInterface", d.bFirstInterface), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bInterfaceCount", d.bInterfaceCount), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bFunctionClass", d.bFunctionClass), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bFunctionSubClass", d.bFunctionSubClass), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bFunctionProtocol", d.bFunctionProtocol), COMMA_NEWLINE);
            code.Append(GenerateDescrByte(" iFunction", d.iFunction));

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbEndpointDescriptorGen : CyUsbCodeGen
    {
        public CyUsbEndpointDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenBody(node.Value, instName, qualName));
            code.Append(GenFooter(node.Value, instName, qualName));
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyEndpointDescriptor d = (CyEndpointDescriptor) ud;
            // Fix EndpointAddress issue
            if ((d.bEndpointAddress & 0x0F) == 0)
            {
                d.bEndpointAddress |= 1;
            }
            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Endpoint Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" Endpoint Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: ENDPOINT", (byte) d.bDescriptorType),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bEndpointAddress", d.bEndpointAddress), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bmAttributes", d.bmAttributes), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wMaxPacketSize", d.wMaxPacketSize), COMMA_NEWLINE);
            // bInterval does not apply to Bulk endpoints.
            if (d.bmAttributes == (byte)CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_BULK)
                code.Append(GenerateDescrByte(" bInterval", 0));
            else
                code.Append(GenerateDescrByte(" bInterval", d.bInterval));

            if (ud is CyAudioEndpointDescriptor)
            {
                CyAudioEndpointDescriptor d1 = (CyAudioEndpointDescriptor)ud;
                code.Append(COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bRefresh", d1.bRefresh), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" bSynchAddress", d1.bSynchAddress));
            }

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbASEndpointDescriptorGen : CyUsbCodeGen
    {
        public CyUsbASEndpointDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenBody(node.Value, instName, qualName));
            code.Append(GenFooter(node.Value, instName, qualName));
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyASEndpointDescriptor d = (CyASEndpointDescriptor)ud;

            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* AS Endpoint Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" Endpoint Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: CS_ENDPOINT", (byte)d.bDescriptorType),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bmAttributes", d.bmAttributes), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bLockDelayUnits", d.bLockDelayUnits), COMMA_NEWLINE);
            code.AppendFormat(GenerateDescrDWLS(" wLockDelay", d.wLockDelay));

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbMSEndpointDescriptorGen : CyUsbCodeGen
    {
        public CyUsbMSEndpointDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenBody(node.Value, instName, qualName));
            code.Append(GenFooter(node.Value, instName, qualName));
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyMSEndpointDescriptor d = (CyMSEndpointDescriptor)ud;

            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* MS Bulk Data Endpoint Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" Endpoint Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: CS_ENDPOINT", (byte)d.bDescriptorType),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bNumEmbMIDIJack", d.bNumEmbMIDIJack), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baAssocJackID", d.baAssocJackID), "");

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbHIDClassDescriptorGen : CyUsbCodeGen
    {
        public CyUsbHIDClassDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenBody(node.Value, instName, qualName));
            code.Append(GenFooter(node.Value, instName, qualName));
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyHIDDescriptor d = (CyHIDDescriptor) ud;
            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* HID Class Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(" HID Class Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: HID_CLASS", (byte) d.bDescriptorType),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrDWLS(" bcdHID", 0x0111), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bCountryCode", d.bCountryCode), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bNumDescriptors", d.bNumDescriptors), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorType", d.bDescriptorType1), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateSymbolicByte(" wDescriptorLength (LSB)",
                                                             string.Format("{0}_HID_RPT_{1}_SIZE_LSB", instanceName,
                                                                           d.bReportIndex)), COMMA_NEWLINE);
            code.Append(GenerateSymbolicByte(" wDescriptorLength (MSB)",
                                         string.Format("{0}_HID_RPT_{1}_SIZE_MSB", instanceName, d.bReportIndex)));

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbAudioDescriptorGen : CyUsbCodeGen
    {
        public CyUsbAudioDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenBody(node.Value, instName, qualName));
            code.Append(GenFooter(node.Value, instName, qualName));
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendFormat("* {0} Descriptor", ud).AppendLine();
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(String.Format(" {0} Descriptor Length", ud), ud.bLength),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: AUDIO", (byte)ud.bDescriptorType),
                                  COMMA_NEWLINE);

            if (ud is CyACHeaderDescriptor)
            {
                CyACHeaderDescriptor d = (CyACHeaderDescriptor) ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" bcdADC", d.bcdADC), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTotalLength", d.wTotalLength), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bInCollection", d.bInCollection),
                                  d.bInCollection > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByteArray(" baInterfaceNr", d.baInterfaceNr));
            }
            else if (ud is CyACInputTerminalDescriptor)
            {
                CyACInputTerminalDescriptor d = (CyACInputTerminalDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bTerminalID", d.bTerminalID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTerminalType", d.wTerminalType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bAssocTerminal", d.bAssocTerminal), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wChannelConfig", d.wChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iTerminal", d.iTerminal));

            }
            else if (ud is CyACOutputTerminalDescriptor)
            {
                CyACOutputTerminalDescriptor d = (CyACOutputTerminalDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bTerminalID", d.bTerminalID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTerminalType", d.wTerminalType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bAssocTerminal", d.bAssocTerminal), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bSourceID", d.bSourceID), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iTerminal", d.iTerminal));

            }
            else if (ud is CyACMixerUnitDescriptor)
            {
                CyACMixerUnitDescriptor d = (CyACMixerUnitDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wChannelConfig", d.wChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" bmControls", d.bmControls.ToArray()),
                                  d.bmControls.Count > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByte(" iMixer", d.iMixer));

            }
            else if (ud is CyACSelectorUnitDescriptor)
            {
                CyACSelectorUnitDescriptor d = (CyACSelectorUnitDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByte(" iSelector", d.iSelector));

            }
            else if (ud is CyACFeatureUnitDescriptor)
            {
                CyACFeatureUnitDescriptor d = (CyACFeatureUnitDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bSourceID", d.bSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bControlSize", d.bControlSize), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrCustomArray(" bmaControls", d.bmaControls, d.bControlSize),
                                  (d.bmaControls.Length > 0) && (d.bControlSize > 0) ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByte(" iFeature", d.iFeature));

            }
            else if (ud is CyACProcessingUnitDescriptor)
            {
                CyACProcessingUnitDescriptor d = (CyACProcessingUnitDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wProcessType", d.wProcessType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wChannelConfig", d.wChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bControlSize", d.bControlSize), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" bmControls", d.bmControls),
                                  d.bmControls.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByte(" iProcessing", d.iProcessing));
            }
            else if (ud is CyACExtensionDescriptor)
            {
                CyACExtensionDescriptor d = (CyACExtensionDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wExtensionCode", d.wExtensionCode), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wChannelConfig", d.wChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bControlSize", d.bControlSize), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" bmControls", d.bmControls),
                                  d.bmControls.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByte(" iExtension", d.iExtension));

            }
            else if (ud is CyASGeneralDescriptor)
            {
                CyASGeneralDescriptor d = (CyASGeneralDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bTerminalLink", d.bTerminalLink), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDelay", d.bDelay), COMMA_NEWLINE);
                code.Append(GenerateDescrDWLS(" wFormatTag", d.wFormatTag));

            }
            else if ((ud is CyASFormatType1Descriptor) || (ud is CyASFormatType2Descriptor))
            {
                CyASFormatTypeBaseDescriptor d = (CyASFormatTypeBaseDescriptor) ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte) d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bFormatType", (byte) d.bFormatType), COMMA_NEWLINE);

                if (ud is CyASFormatType1Descriptor)
                {
                    CyASFormatType1Descriptor d1 = (CyASFormatType1Descriptor)ud;

                    code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d1.bNrChannels), COMMA_NEWLINE);
                    code.AppendFormat("{0}{1}", GenerateDescrByte(" bSubframeSize", d1.bSubframeSize), COMMA_NEWLINE);
                    code.AppendFormat("{0}{1}", GenerateDescrByte(" bBitResolution", d1.bBitResolution), COMMA_NEWLINE);
                }
                else if (ud is CyASFormatType2Descriptor)
                {
                    CyASFormatType2Descriptor d1 = (CyASFormatType2Descriptor)ud;

                    code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wMaxBitRate", d1.wMaxBitRate), COMMA_NEWLINE);
                    code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wSamplesPerFrame", d1.wSamplesPerFrame),
                                      COMMA_NEWLINE);
                }

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bSamFreqType", d.bSamFreqType), COMMA_NEWLINE);
                if (d.bSamFreqType == 0)
                {
                    code.AppendFormat("{0}{1}", GenerateDescrByteArray(" tLowerSamFreq",
                        CyUSBFSParameters.ConvertInt3ToByteArray(d.tLowerSamFreq).ToArray()), COMMA_NEWLINE);
                    code.Append(GenerateDescrByteArray(" tUpperSamFreq",
                        CyUSBFSParameters.ConvertInt3ToByteArray(d.tUpperSamFreq).ToArray()));
                }
                else
                {
                    code.Append(GenerateDescr3ByteArray(" tSamFreq", d.tSamFreq));
                }
            }
            //---------------------------------------------------------------------------------------------------------
            #region v2.0

            if (ud is CyACHeaderDescriptor_v2)
            {
                CyACHeaderDescriptor_v2 d = (CyACHeaderDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" bcdADC", d.bcdADC), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bCategory", d.bCategory), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTotalLength", d.wTotalLength), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" bmControls", d.bmControls));
            }
            else if (ud is CyACClockSourceDescriptor_v2)
            {
                CyACClockSourceDescriptor_v2 d = (CyACClockSourceDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bClockID", d.bClockID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmAttributes", d.bmAttributes), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bAssocTerminal", d.bAssocTerminal), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iClockSource", d.iClockSource));

            }
            else if (ud is CyACClockSelectorDescriptor_v2)
            {
                CyACClockSelectorDescriptor_v2 d = (CyACClockSelectorDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bClockID", d.bClockID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baCSourceID", d.baCSourceID),
                                    d.baCSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iClockSelector", d.iClockSelector));

            }
            else if (ud is CyACClockMultiplierDescriptor_v2)
            {
                CyACClockMultiplierDescriptor_v2 d = (CyACClockMultiplierDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bClockID", d.bClockID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bCSourceID", d.bCSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iClockMultiplier", d.iClockMultiplier));

            }
            else if (ud is CyACInputTerminalDescriptor_v2)
            {
                CyACInputTerminalDescriptor_v2 d = (CyACInputTerminalDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bTerminalID", d.bTerminalID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTerminalType", d.wTerminalType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bAssocTerminal", d.bAssocTerminal), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bCSourceID", d.bCSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrInt(" bmChannelConfig", d.bmChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iTerminal", d.iTerminal));

            }
            else if (ud is CyACOutputTerminalDescriptor_v2)
            {
                CyACOutputTerminalDescriptor_v2 d = (CyACOutputTerminalDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bTerminalID", d.bTerminalID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTerminalType", d.wTerminalType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bAssocTerminal", d.bAssocTerminal), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bSourceID", d.bSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bCSourceID", d.bCSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iTerminal", d.iTerminal));

            }
            else if (ud is CyACMixerUnitDescriptor_v2)
            {
                CyACMixerUnitDescriptor_v2 d = (CyACMixerUnitDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrInt(" bmChannelConfig", d.bmChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" bmMixerControls", d.bmMixerControls.ToArray()),
                                  d.bmMixerControls.Count > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iMixer", d.iMixer));

            }
            else if (ud is CyACSelectorUnitDescriptor_v2)
            {
                CyACSelectorUnitDescriptor_v2 d = (CyACSelectorUnitDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iSelector", d.iSelector));

            }
            else if (ud is CyACFeatureUnitDescriptor_v2)
            {
                CyACFeatureUnitDescriptor_v2 d = (CyACFeatureUnitDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bSourceID", d.bSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrCustomArray(" bmaControls", d.bmaControls, 4),
                                  (d.bmaControls.Length > 0) ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByte(" iFeature", d.iFeature));
            }
            else if (ud is CyACSamplingRateConverterDescriptor_v2)
            {
                CyACSamplingRateConverterDescriptor_v2 d = (CyACSamplingRateConverterDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bSourceID", d.bSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bCSourceInID", d.bCSourceInID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bCSourceOutID", d.bCSourceOutID), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iSRC", d.iSRC));
            }
            else if (ud is CyACEffectUnitDescriptor_v2)
            {
                CyACEffectUnitDescriptor_v2 d = (CyACEffectUnitDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wEffectType", (ushort)d.wEffectType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bSourceID", d.bSourceID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrCustomArray(" bmaControls", d.bmaControls, 4),
                                  d.bmaControls.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByte(" iEffects", d.iEffects));
            }
            else if (ud is CyACProcessingUnitDescriptor_v2)
            {
                CyACProcessingUnitDescriptor_v2 d = (CyACProcessingUnitDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wProcessType", d.wProcessType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrInt(" bmChannelConfig", d.bmChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iProcessing", d.iProcessing));
            }
            else if (ud is CyACExtensionDescriptor_v2)
            {
                CyACExtensionDescriptor_v2 d = (CyACExtensionDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bUnitID", d.bUnitID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wExtensionCode", d.wExtensionCode), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInPins", d.bNrInPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.baSourceID.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrInt(" bmChannelConfig", d.bmChannelConfig), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iChannelNames", d.iChannelNames), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iExtension", d.iExtension));

            }
            else if (ud is CyASGeneralDescriptor_v2)
            {
                CyASGeneralDescriptor_v2 d = (CyASGeneralDescriptor_v2)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bTerminalLink", d.bTerminalLink), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmControls", d.bmControls), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bFormatType", d.bFormatType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrInt(" bmFormats", d.bmFormats), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrChannels", d.bNrChannels), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrInt(" bmChannelConfig", d.bmChannelConfig), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" iChannelNames", d.iChannelNames));

            }
            #endregion

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbMidiDescriptorGen : CyUsbCodeGen
    {
        public CyUsbMidiDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenBody(node.Value, instName, qualName));
            code.Append(GenFooter(node.Value, instName, qualName));
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendFormat("* {0} Descriptor", ud).AppendLine();
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(String.Format(" {0} Descriptor Length", ud), ud.bLength),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: AUDIO", (byte)ud.bDescriptorType),
                                  COMMA_NEWLINE);

            if (ud is CyMSHeaderDescriptor)
            {
                CyMSHeaderDescriptor d = (CyMSHeaderDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" bcdADC", d.bcdMSC), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrDWLS(" wTotalLength", d.wTotalLength), "");
            }
            else if (ud is CyMSInJackDescriptor)
            {
                CyMSInJackDescriptor d = (CyMSInJackDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bJackType", (byte)d.bJackType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bJackID", d.bJackID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iJack", d.iJack), "");

            }
            else if (ud is CyMSOutJackDescriptor)
            {
                CyMSOutJackDescriptor d = (CyMSOutJackDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bJackType", (byte)d.bJackType), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bJackID", d.bJackID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInputPins", d.bNrInputPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.bNrInputPins > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourcePin),
                                  d.bNrInputPins > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iJack", d.iJack), "");

            }
            else if (ud is CyMSElementDescriptor)
            {
                CyMSElementDescriptor d = (CyMSElementDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype", (byte)d.bDescriptorSubtype),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bElementID", d.bElementID), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrInputPins", d.bNrInputPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourceID),
                                  d.bNrInputPins > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" baSourceID", d.baSourcePin),
                                  d.bNrInputPins > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bNrOutPins", d.bNrOutPins), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bInTerminalLink", d.bInTerminalLink), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bOutTerminalLink", d.bOutTerminalLink), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" bElCapsSize", d.bElCapsSize), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByteArray(" bmElementCaps", d.bmElementCaps),
                                  d.bNrInputPins > 0 ? COMMA_NEWLINE : NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte(" iElement", d.iElement), "");

            }

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbCDCDescriptorGen : CyUsbCodeGen
    {
        public CyUsbCDCDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenBody(node.Value, instName, qualName));
            code.Append(GenFooter(node.Value, instName, qualName));
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            // Header Comment
            code.AppendLine(",");
            code.AppendLine("/*********************************************************************");
            code.AppendFormat("* {0} Descriptor", ud).AppendLine();
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("{0}{1}", GenerateDescrByte(String.Format(" {0} Descriptor Length", ud), ud.bLength),
                              COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" DescriptorType: CS_INTERFACE", 0x24), // 0x24 hardcoded
                                  COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte(" bDescriptorSubtype",
                                        (byte)((CyCDCClassDescriptor)ud).bDescriptorSubtype), COMMA_NEWLINE);

            if (ud is CyCDCHeaderDescriptor)
            {
                CyCDCHeaderDescriptor d = (CyCDCHeaderDescriptor)ud;

                code.Append(GenerateDescrDWLS(" bcdADC", d.bcdADC));
            }
            else if (ud is CyCDCUnionDescriptor)
            {
                CyCDCUnionDescriptor d = (CyCDCUnionDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bControlInterface", d.bControlInterface),
                                    d.bSubordinateInterface.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrByteArray(" bSubordinateInterface", d.bSubordinateInterface));

            }
            else if (ud is CyCDCCountrySelectionDescriptor)
            {
                CyCDCCountrySelectionDescriptor d = (CyCDCCountrySelectionDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" iCountryCodeRelDate", d.iCountryCodeRelDate),
                                            d.wCountryCode.Length > 0 ? COMMA_NEWLINE : NEWLINE);
                code.Append(GenerateDescrDWLSArray(" wCountryCode", d.wCountryCode));

            }
            else if (ud is CyCDCCallManagementDescriptor)
            {
                CyCDCCallManagementDescriptor d = (CyCDCCallManagementDescriptor)ud;

                code.AppendFormat("{0}{1}", GenerateDescrByte(" bmCapabilities", d.bmCapabilities), COMMA_NEWLINE);
                code.Append(GenerateDescrByte(" bDataInterface", d.bDataInterface));
            }
            else if (ud is CyCDCAbstractControlMgmtDescriptor)
            {
                CyCDCAbstractControlMgmtDescriptor d = (CyCDCAbstractControlMgmtDescriptor)ud;

                code.Append(GenerateDescrByte(" bmCapabilities", d.bmCapabilities));
            }

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbStringDescriptorGen : CyUsbCodeGen
    {
        public CyUsbStringDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            CyStringDescriptor d = (CyStringDescriptor) ud;
            StringBuilder code = new StringBuilder();
            // Header Comment
            code.Append(COMMA_NEWLINE);
            code.AppendLine("/*********************************************************************");
            code.AppendFormat("* String Descriptor: \"{0}\"\r\n", d.bString);
            code.AppendLine("*********************************************************************/");
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyStringDescriptor d = (CyStringDescriptor) ud;

            if (d.bString != null)
            {
                code.AppendFormat("{0}{1}", GenerateDescrByte("Descriptor Length", (byte) (2 + (d.bString.Length*2))),
                                  COMMA_NEWLINE);
                code.AppendFormat("{0}{1} ", GenerateDescrByte("DescriptorType: STRING", (byte) d.bDescriptorType),
                                  COMMA_NEWLINE);
                code.Append(GenerateUsbUnicode(d.bString));
            }
            else
            {
                code.AppendFormat("{0}{1}", GenerateDescrByte("Descriptor Length", 2), COMMA_NEWLINE);
                code.Append(GenerateDescrByte("DescriptorType: STRING",  (byte) d.bDescriptorType));
            }

            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbStringZeroDescriptorGen : CyUsbCodeGen
    {
        public CyUsbStringZeroDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Language ID Descriptor has to be the 0th descriptor, so it will anchor
            // all of the string descriptors
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* String Descriptor Table");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("const uint8 {0} {1}_STRING_DESCRIPTORS[] = {{{2}", CODE, qualName, NEWLINE);
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Language ID Descriptor");
            code.AppendLine("*********************************************************************/");
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            CyStringZeroDescriptor d = (CyStringZeroDescriptor) ud;
            StringBuilder code = new StringBuilder();
            code.AppendFormat("{0}{1}", GenerateDescrByte("Descriptor Length", d.bLength), COMMA_NEWLINE);
            code.AppendFormat("{0}{1}", GenerateDescrByte("DescriptorType: STRING", (byte) d.bDescriptorType),
                              COMMA_NEWLINE);
            code.Append(GenerateDescrDWLS("Language Id", d.wLANGID));
            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Language ID Descriptor has to be the 0th descriptor, so it will close
            // all of the string descriptors
            code.Append(COMMA_NEWLINE);
            code.AppendLine("/*********************************************************************/");
            code.AppendLine(GenerateDescrByte("Marks the end of the list.", 0) + "};");
            code.AppendLine("/*********************************************************************/");
            return code.ToString();
        }
    }

    internal class CyUsbStringSNDescriptorGen : CyUsbCodeGen
    {
        public CyUsbStringSNDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Serial Number String Descriptor
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Serial Number String Descriptor");
            code.AppendLine("*********************************************************************/");
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            CyStringDescriptor d = (CyStringDescriptor) ud;
            StringBuilder code = new StringBuilder();
            code.AppendFormat("const uint8 {0} {1}_SN_STRING_DESCRIPTOR[{2}] = {{{3}", CODE, qualName, d.bLength, NEWLINE);
            if (d.bString != null)
            {
                code.AppendFormat("{0}{1}", GenerateDescrByte("Descriptor Length", d.bLength), COMMA_NEWLINE);
                code.AppendFormat("{0}{1}", GenerateDescrByte("DescriptorType: STRING", (byte) d.bDescriptorType),
                                  COMMA_NEWLINE);
                code.Append(GenerateUsbUnicode(d.bString));
            }
            else
            {
                code.AppendFormat("{0}{1}", GenerateDescrByte("Descriptor Length", 2), COMMA_NEWLINE);
                code.Append(GenerateDescrByte("DescriptorType: STRING",  (byte) d.bDescriptorType));
            }
            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            // Microsoft Operating System Descriptor
            string code = String.Format("{0}}};{0}", NEWLINE);
            return code;
        }
    }

    internal class CyUsbStringMSOSDescriptorGen : CyUsbCodeGen
    {
        public CyUsbStringMSOSDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Microsoft Operating System Descriptors
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Microsoft Operating System Descriptor");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("const uint8 {0} {1}_MSOS_DESCRIPTOR[] = {{{2}", CODE, qualName, NEWLINE);
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            CyStringDescriptor d = (CyStringDescriptor) ud;
            StringBuilder code = new StringBuilder();
            code.Append(GenerateDescrByte("Descriptor Length", d.bLength));
            code.Append(COMMA_NEWLINE);
            code.Append(GenerateDescrByte("DescriptorType: STRING", (byte) d.bDescriptorType));
            code.Append(COMMA_NEWLINE);
            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            // Microsoft Operating System Descriptor
            return FOOTER_BRACKET;
        }
    }

    internal class CyUsbHIDReportDescriptorGen : CyUsbCodeGen
    {
        public CyUsbHIDReportDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyHIDReportDescriptor d = (CyHIDReportDescriptor)ud;
            // Header Comment
            code.AppendLine("/*********************************************************************");
            code.AppendFormat("* HID Report Descriptor: {0}{1}", d.Name, NEWLINE);
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("const uint8 {0} {1} = {{{2}", CODE, qualName, NEWLINE);
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            CyHIDReportDescriptor d = (CyHIDReportDescriptor) ud;
            StringBuilder code = new StringBuilder();
            code.AppendLine("/*********************************************************************");
            code.AppendFormat("* HID Report Descriptor: {0}{1}", d.Name, NEWLINE);
            code.AppendLine("*********************************************************************/");
            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            code.AppendLine("/*********************************************************************/");
            code.Append(GenerateDescrDWLS("End of the HID Report Descriptor", 0));
            code.AppendLine("};");
            code.AppendLine("/*********************************************************************/");
            return code.ToString();
        }
    }

    internal class CyUsbHIDReportItemGen : CyUsbCodeGen
    {
        public CyUsbHIDReportItemGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            CyHIDReportItemDescriptor d = (CyHIDReportItemDescriptor) ud;
            return GenerateReportItem(d);
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    internal class CyUsbUnknownDescriptorGen : CyUsbCodeGen
    {
        public CyUsbUnknownDescriptorGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Header Comment
            code.AppendLine("/*********************************************************************");
            code.AppendLine(string.Format("* Unknown Descriptor {0}:::{1}", ud.bDescriptorType, ud.bLength));
            code.AppendLine("*********************************************************************/");
            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }
    }

    #endregion Descriptor Code Generators

    #region Table Generators

    internal class CyUsbDeviceRootTableGen : CyUsbCodeGen
    {
        public CyUsbDeviceRootTableGen(string instanceName) : base(instanceName)
        {
            m_nl = "";
        }

        public override string Generate(List<CyDescriptorNode> nodes, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Generate the children
            for (int i = 0; i < nodes.Count; i++)
            {
                CyUsbDeviceTableGen cgt = new CyUsbDeviceTableGen(INSTANCE_NAME);
                string qual = GenerateQualName(qualName,nodes[i], i);
                code.Append(cgt.Generate(nodes[i], instName, qual));
            }

            code.Append(GenHeader(nodes[0].Value, instName, instName));
            code = InsertLengthInArrayHeader(code.ToString(), (uint)nodes.Count);
            for (int i = 0; i < nodes.Count; i++)
            {
                string qual = GenerateQualName(qualName,nodes[i], i);
                code.Append(this.GenLUTEntry(qual, "_TABLE", ((CyDeviceDescriptor)nodes[i].Value).bNumConfigurations));
            }
            code.Append(GenFooter(nodes[0].Value, instName, instName));
            return code.ToString();
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            Debug.Assert(false);
            return String.Empty;
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Device Root Table Header
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Device Table -- Indexed by the device number.");
            code.AppendLine("*********************************************************************/");
            code.Append(GenerateLUTHeader(qualName + "_TABLE[]"));
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            Debug.Assert(false);
            return String.Empty;
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return FOOTER_BRACKET;
        }
    }

    internal class CyUsbDeviceTableGen : CyUsbCodeGen
    {
        public CyUsbDeviceTableGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Generate the children
            if (node.Nodes.Count > 0)
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    if (node.Nodes[i].Value.bDescriptorType != CyUSBDescriptorType.CONFIGURATION)
                        continue;

                    CyUsbConfigTableGen cgt = new CyUsbConfigTableGen(INSTANCE_NAME);
                    string qual = GenerateQualName(qualName, node.Nodes[i], i);
                    code.Append(cgt.Generate(node.Nodes[i], instName, qual));
                }
            }

            byte numConfig = ((CyDeviceDescriptor)node.Value).bNumConfigurations;

            code.Append(GenHeader(node.Value, instName, qualName));
            // Length of array equals number of configurations + 2 (DEVICE_DESCR and BOS_TABLE)
            code = InsertLengthInArrayHeader(code.ToString(), numConfig + 2u);

            // Generate BOS_TABLE LUT
            if (!CyDescriptorNode.IsDescriptorPresent(node, CyUSBDescriptorType.BOS))
                code.Append(this.GenNullLUTEntry());
            else
                code.Append(this.GenLUTEntry(qualName, "_BOS_DESCR", numConfig));

            // Generate CONFIGURATION_TABLE LUT
            for (int i = 0; i < node.Nodes.Count; i++)
            {
                if (node.Nodes[i].Value.bDescriptorType == CyUSBDescriptorType.BOS)
                    continue;

                string qual = GenerateQualName(qualName, node.Nodes[i], i);
                code.Append(this.GenLUTEntry(qual, "_TABLE", numConfig));
            }
            code.Append(GenFooter(node.Value, instName, qualName));

            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyDeviceDescriptor d = (CyDeviceDescriptor) ud;
            // Device  Table Header
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Device Dispatch Table -- Points to the Device Descriptor and each of");
            code.AppendLine("*                          and Configuration Tables for this Device ");
            code.AppendLine("*********************************************************************/");
            code.Append(GenerateLUTHeader(qualName + "_TABLE[]"));
            code.Append(GenLUTEntry(qualName, "_DESCR", d.bNumConfigurations));
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            Debug.Assert(false);
            return String.Empty;
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return FOOTER_BRACKET;
        }
    }

    internal class CyUsbConfigTableGen : CyUsbCodeGen
    {
        public CyUsbConfigTableGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            // Generate any child tables
            for (int i = 0; i < node.Nodes.Count; i++)
            {
                CyUsbInterfaceTableGen cgt = new CyUsbInterfaceTableGen(INSTANCE_NAME);
                string qual = GenerateQualName(qualName, node.Nodes[i], i);
                code.Append(cgt.Generate(node.Nodes[i], instName, qual));

            }
            // Generate the Endpoint Table
            CyUsbEndportTableGen gtEP = new CyUsbEndportTableGen(INSTANCE_NAME);
            code.Append(gtEP.Generate(node, instName, qualName));


            // Generate the interface class table
            uint arrLength = 0;
            code.AppendFormat("const uint8 {0} {1}_INTERFACE_CLASS[] = {{", CODE, qualName).AppendLine();
            for (int i = 0; i < node.Nodes.Count; i++)
                for (int j = 0; j < Math.Min(1, node.Nodes[i].Nodes.Count); j++)
                {
                    CyDescriptorNode nodeAlternate = node.Nodes[i].Nodes[j];
                    if ((nodeAlternate.Value != null) && (nodeAlternate.Value is CyInterfaceDescriptor))
                    {
                        CyInterfaceDescriptor desc = (CyInterfaceDescriptor) nodeAlternate.Value;
                        code.Append(GenerateByte(desc.bInterfaceClass));
                        if ((i != node.Nodes.Count -1) || (j != node.Nodes[i].Nodes.Count - 1))
                            code.Append(", ");
                        arrLength++;
                    }
                }
            code.AppendLine().AppendLine("};");
            code = InsertLengthInArrayHeader(code.ToString(), arrLength);

            code.Append(GenHeader(node.Value, instName, qualName));
            code.Append(GenLUTEntry(qualName, "_EP_SETTINGS_TABLE", gtEP.GetNumEPDescriptors(node)));
            arrLength = 3;
            for (int i = 0; i < node.Nodes.Count; i++)
            {
                string qual = GenerateQualName(qualName, node.Nodes[i], i);

                if (node.Nodes[i].Nodes.Count > 0)
                {
                    code.Append(GenInterfaceTblPtr(node.Nodes[i].Nodes[0], (byte) node.Nodes[i].Nodes.Count,
                                               instName, qual));
                    arrLength++;
                }
            }
            code = InsertLengthInArrayHeader(code.ToString(), arrLength);

            code.Append(GenLUTEntry(qualName, "_INTERFACE_CLASS", 0));
            code.Append(GenFooter(node.Value, instName, qualName));

            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Device  Table Header
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Config Dispatch Table -- Points to the Config Descriptor and each of");
            code.AppendLine("*                          and endpoint setup table and to each");
            code.AppendLine("*                          interface table if it specifies a USB Class");
            code.AppendLine("*********************************************************************/");
            code.Append(GenerateLUTHeader(qualName + "_TABLE[]"));
            code.Append(GenLUTEntry(qualName, "_DESCR", 1));
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return String.Empty;
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            string code = "\r\n};\r\n";
            return code;
        }

        private string GenInterfaceTblPtr(CyDescriptorNode node, byte alternateCount, string instanceName,
                                          string qualName)
        {
            StringBuilder code = new StringBuilder();
            CyInterfaceDescriptor d = (CyInterfaceDescriptor) node.Value;
            // If class in not HID, don't generate Interface table
            if (d.bInterfaceClass != (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_HID)
            {
                code.Append(GenNullLUTEntry());
            }
            else
            {
                code.Append(GenLUTEntry(qualName, "_TABLE", alternateCount));
            }

            return code.ToString();
        }
    }

    internal class CyUsbInterfaceTableGen : CyUsbCodeGen
    {
        public CyUsbInterfaceTableGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            bool foundClassDescr = false;
            for (int j = 0; j < node.Nodes.Count; j++)
            {
                if (FindClassDescriptor(node.Nodes[j]))
                {
                    foundClassDescr = true;
                    break;
                }
            }
            if (foundClassDescr)
            {
                uint arrLength = 0;
                code.Append(GenHeader(node.Value, instName, qualName));
                for (int j = 0; j < node.Nodes.Count; j++)
                {
                    CyDescriptorNode nodeAlternate = node.Nodes[j];

                    if (FindClassDescriptor(nodeAlternate))
                    {
                        string qualAlt = GenerateQualName(qualName, nodeAlternate, j);
                        for (int i = 0; i < nodeAlternate.Nodes.Count; i++)
                        {
                            string qual = GenerateQualName(qualAlt, nodeAlternate.Nodes[i], i);
                            string entry = GenBody(nodeAlternate.Nodes[i].Value, qual, qual);
                            if (String.IsNullOrEmpty(entry) == false)
                            {
                                arrLength++;
                                code.Append(entry);
                            }
                        }
                    }
                }
                code = InsertLengthInArrayHeader(code.ToString(), arrLength);
                code = new StringBuilder(code.ToString().TrimEnd('\r', '\n', ','));
                code.Append(GenFooter(node.Value, instName, qualName));
            }
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Device  Table Header
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Interface Dispatch Table -- Points to the Class Dispatch Tables");
            code.AppendLine("*********************************************************************/");
            code.Append(GenerateLUTHeader(qualName + "_TABLE[]"));
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            if (ud.bDescriptorType != CyUSBDescriptorType.ENDPOINT)
            {
                code.Append(GenerateLUTEntry(qualName + "_TABLE", qualName + "_COUNT"));
                code.Append(",\r\n");
            }
            return code.ToString();
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            string code = "\r\n};\r\n";
            return code;
        }

        private bool FindClassDescriptor(CyDescriptorNode node)
        {
            bool found = false;

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                CyDescriptorNode n = node.Nodes[i];
                if (n.Nodes.Count > 0)
                {
                    found = FindClassDescriptor(n);
                }
                if (n.Value.bDescriptorType == CyUSBDescriptorType.HID)
                {
                    found = true;
                }
            }
            return found;
        }
    }

    internal class CyUsbEndportTableGen : CyUsbCodeGen
    {
        public CyUsbEndportTableGen(string instanceName)
            : base(instanceName)
        {
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            uint arrLength = 0;
            if (node.Value.bDescriptorType == CyUSBDescriptorType.CONFIGURATION)
            {
                code.Append(GenHeader(node.Value, instName, qualName));
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    CyDescriptorNode igd = node.Nodes[i];
                    for (int j = 0; j < igd.Nodes.Count; j++)
                    {
                        CyDescriptorNode id = igd.Nodes[j];
                        CyInterfaceDescriptor d = (CyInterfaceDescriptor) id.Value;
                        byte CurInterface = d.bInterfaceNumber;
                        byte curInterfaceClass = d.bInterfaceClass;
                        byte CurAltSetting = d.bAlternateSetting;
                        for (int k = 0; k < id.Nodes.Count; k++)
                        {
                            CyDescriptorNode en = id.Nodes[k];
                            if (en.Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                            {
                                code.Append(FormatEndpointSetting(CurInterface, CurAltSetting,
                                    (CyEndpointDescriptor)en.Value, curInterfaceClass));
                                arrLength++;
                            }
                        }
                    }
                }
                if (arrLength == 0)
                {
                    // Add {NULL} value to the array
                    code.Append("{" + NULL_PTR + "}");
                    arrLength++;
                }
                code = InsertLengthInArrayHeader(code.ToString(), arrLength);
                code.Append(GenFooter(node.Value, instName, qualName));
            }
            return code.ToString();
        }

        public override string GenHeader(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            // Table Header
            code.AppendLine("/*********************************************************************");
            code.AppendLine("* Endpoint Setting Table -- This table contain the endpoint setting");
            code.AppendLine("*                           for each endpoint in the configuration. It");
            code.AppendLine("*                           contains the necessary information to");
            code.AppendLine("*                           configure the endpoint hardware for each");
            code.AppendLine("*                           interface and alternate setting.");
            code.AppendLine("*********************************************************************/");
            code.AppendFormat("const T_{0}_EP_SETTINGS_BLOCK {1} {2}_EP_SETTINGS_TABLE[] = {{{3}", INSTANCE_NAME, CODE,
                              qualName, NEWLINE);
            code.AppendLine("/* IFC  ALT    EPAddr bmAttr MaxPktSize Class ********************/");
            return code.ToString();
        }

        public override string GenBody(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            return string.Empty;
        }

        public override string GenFooter(CyUSBDescriptor ud, string instanceName, string qualName)
        {
            string code = String.Format("{0}}};{0}", NEWLINE);
            return code;
        }

        public byte GetNumEPDescriptors(CyDescriptorNode node)
        {
            byte count = 0;
            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT))
            {
                count = 1;
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    count += GetNumEPDescriptors(node.Nodes[i]);
                }
            }
            return count;
        }

        private string FormatEndpointSetting(byte ifc, byte alt, CyEndpointDescriptor d, byte ifclass)
        {
            StringBuilder code = new StringBuilder();
            code.Append(m_nl);
            code.Append("{");
            code.AppendFormat("{0}, ", GenerateByte(ifc));
            code.AppendFormat("{0}, ", GenerateByte(alt));
            code.AppendFormat("{0}, ", GenerateByte(d.bEndpointAddress));
            code.AppendFormat("{0}, ", GenerateByte(d.bmAttributes));
            code.AppendFormat("{0},   ", GenerateWord(d.wMaxPacketSize));
            //code.Append(GenerateByte(d.DoubleBuffer ? (byte) 1 : (byte) 0)); // buffer type
            code.Append(GenerateByte(ifclass));
            code.Append("}");
            m_nl = COMMA_NEWLINE;
            return code.ToString();
        }
    }

    #endregion

    #region Tree Generators

    internal abstract class CyGenTree
    {
        public abstract string Generate(List<CyDescriptorNode> nodes, string instName, string qualName);
        public abstract string Generate(CyDescriptorNode node, string instName, string qualName);
    }

    internal class CyUsbDescriptorGenTree : CyGenTree
    {
        public CyUsbDescriptorGenTree()
        {
        }

        public override string Generate(List<CyDescriptorNode> nodes, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            CyUsbCodeGenMaker f = new CyUsbCodeGenMaker();

            CyUsbDescriptorGenTree cgt = new CyUsbDescriptorGenTree();

            for (int i = 0; i < nodes.Count; i++)
            {
                string qual = CyUsbCodePrimitives.GenerateQualName(qualName, nodes[i], i);
                CyUsbCodeGen cg = f.MakeDescriptorGenerator(nodes[i].Value, instName);
                code.Append(cg.GenHeader(nodes[i].Value, instName, qual));
                code.Append(cg.GenBody(nodes[i].Value, instName, qual));
                if (nodes[i].Value.bDescriptorType == CyUSBDescriptorType.INTERFACE)
                {
                    CyDescriptorNode n = nodes[i];

                    // Class Descriptors first
                    for (int j = 0; j < n.Nodes.Count; j++)
                    {
                        if (n.Nodes[j].Value.bDescriptorType != CyUSBDescriptorType.ENDPOINT)
                        {
                            code.Append(cgt.Generate(n.Nodes[j], instName, qual));

                            if (n.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.HID)
                                CyUsbCodePrimitives.HidClassQualList.Add(qual);
                        }
                    }
                    // Now, the endpoints
                    for (int j = 0; j < n.Nodes.Count; j++)
                    {
                        if (n.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                        {
                            code.Append(cgt.Generate(n.Nodes[j], instName, qual));
                            // Class-specific endpoints
                            for (int k = 0; k < n.Nodes[j].Nodes.Count; k++)
                            {
                                code.Append(cgt.Generate(n.Nodes[j].Nodes[k], instName, qual));
                            }
                        }
                    }
                }
                else
                {
                    code.Append(cgt.Generate(nodes[i].Nodes, instName, qual));
                }
                code.Append(cg.GenFooter(nodes[i].Value, instName, qual));
            }
            return code.ToString();
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            CyUsbCodeGenMaker f = new CyUsbCodeGenMaker();
            CyUsbCodeGen cg = f.MakeDescriptorGenerator(node.Value, instName);
            string code = cg.Generate(node, instName, qualName);

            return code;
        }
    }

    internal class CyUsbStringDescriptorGenTree : CyGenTree
    {
        public CyUsbStringDescriptorGenTree()
        {
        }

        public override string Generate(List<CyDescriptorNode> nodes, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();
            uint arrLength = 0;

            if (nodes.Count > 1)
            {
                CyUsbCodeGenMaker f = new CyUsbCodeGenMaker();

                //The zeroth string should be the LangID/Zero code generator
                CyUsbCodeGen zcg = f.MakeDescriptorGenerator(nodes[0].Value, instName);

                code.Append(zcg.GenHeader(nodes[0].Value, instName, qualName));
                code.Append(zcg.GenBody(nodes[0].Value, instName, qualName));
                arrLength += nodes[0].Value.bLength;

                for (int i = 1; i < nodes.Count; i++)
                {
                    CyUsbCodeGen cg = f.MakeDescriptorGenerator(nodes[i].Value, instName);
                    code.Append(cg.GenHeader(nodes[i].Value, instName, qualName));
                    code.Append(cg.GenBody(nodes[i].Value, instName, qualName));
                    code.Append(cg.GenFooter(nodes[i].Value, instName, qualName));
                    arrLength += nodes[i].Value.bLength;
                }
                code.Append(zcg.GenFooter(nodes[0].Value, instName, qualName));
                arrLength++;
                code = CyUsbCodePrimitives.InsertLengthInArrayHeader(code.ToString(), arrLength);
            }
            return code.ToString();
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            Debug.Assert(false);
            return String.Empty;
        }
    }

    internal class CyUsbHIDReportDescriptorGenTree : CyGenTree
    {
        public CyUsbHIDReportDescriptorGenTree()
        {
        }

        public override string Generate(List<CyDescriptorNode> nodes, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            if (nodes.Count > 0)
            {
                CyUsbCodeGenMaker f = new CyUsbCodeGenMaker();
                CyUsbCodeGen cg = f.MakeDescriptorGenerator(nodes[0].Value, instName);
                CyUsbHIDReportItemGenTree hgt = new CyUsbHIDReportItemGenTree();
                CyUsbCodePrimitives prim = new CyUsbCodePrimitives(instName);

                for (int i = 0; i < nodes.Count; i++)
                {
                    int rptIndex = i + 1;
                    string qualHead = string.Format("{0}_HIDREPORT_DESCRIPTOR{1}[]", qualName, rptIndex);
                    code.Append(cg.GenHeader(nodes[i].Value, instName, qualHead));
                    code.Append(prim.GenerateSymbolicByte(" Descriptor Size (Not part of descriptor)",
                                  qualName + "_HID_RPT_" + rptIndex + "_SIZE_LSB" + CyUsbCodePrimitives.COMMA_NEWLINE +
                                  qualName + "_HID_RPT_" + rptIndex + "_SIZE_MSB") + CyUsbCodePrimitives.COMMA_NEWLINE);
                    code.Append(hgt.Generate(nodes[i], instName, qualName)); // Generate the HID Report Items
                    code.Append(cg.GenFooter(nodes[i].Value, instName, qualName));
                    int reportSize = CyUsbCodePrimitives.ReportDescriptorSize(nodes[i].Nodes) + 4;
                    code = CyUsbCodePrimitives.InsertLengthInArrayHeader(code.ToString(), (uint)reportSize);
                }
            }
            return code.ToString();
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            return Generate(node.Nodes, instName, qualName);
        }
    }

    internal class CyUsbHIDReportItemGenTree : CyGenTree
    {
        public CyUsbHIDReportItemGenTree()
        {
        }

        public override string Generate(List<CyDescriptorNode> nodes, string instName, string qualName)
        {
            StringBuilder code = new StringBuilder();

            if (nodes.Count > 0)
            {
                CyUsbCodeGenMaker f = new CyUsbCodeGenMaker();
                CyUsbCodeGen cg = f.MakeDescriptorGenerator(nodes[0].Value, instName);

                for (int i = 0; i < nodes.Count; i++)
                {
                    code.Append(cg.GenBody(nodes[i].Value, instName, qualName));
                }
                code.Append(cg.GenFooter(nodes[0].Value, instName, qualName));
            }
            return code.ToString();
        }

        public override string Generate(CyDescriptorNode node, string instName, string qualName)
        {
            return Generate(node.Nodes, instName, qualName);
        }
    }

    internal class CyUsbCodeGenMaker
    {
        public CyUsbCodeGenMaker()
        {
        }

        public CyUsbCodeGen MakeDescriptorGenerator(CyUSBDescriptor d, string instName)
        {
            CyUsbCodeGen c;

            Type d_t = d.GetType();

            if (d_t == typeof (CyDeviceDescriptor))
            {
                c = new CyUsbDeviceDescriptorGen(instName);
            }
            else if (d_t == typeof(CyBosDescriptor))
            {
                c = new CyUsbBosDescriptorGen(instName);
            }
            else if (d_t == typeof(CyUsb20ExtensionDeviceCapabilityDescriptor))
            {
                c = new CyUsb20ExtensionDescriptorGen(instName);
            }
            else if (d_t == typeof(CyContainerIdDescriptor))
            {
                c = new CyContainerIdDescriptorGen(instName);
            }
            else if (d_t == typeof (CyConfigDescriptor))
            {
                c = new CyUsbConfigDescriptorGen(instName);
            }
            else if (d_t == typeof (CyInterfaceGeneralDescriptor))
            {
                c = new CyUsbInterfaceGeneralDescriptorGen(instName);
            }
            else if (d_t == typeof(CyInterfaceAssociationDescriptor))
            {
                c = new CyUsbIntAssociationDescriptorGen(instName);
            }
            else if ((d_t == typeof(CyInterfaceDescriptor)) || (d_t == typeof(CyAudioInterfaceDescriptor)) ||
                (d_t == typeof(CyCommunicationsInterfaceDescriptor)) || (d_t == typeof(CyDataInterfaceDescriptor)) ||
                (d_t == typeof(CyMscInterfaceDescriptor)))
            {
                c = new CyUsbInterfaceDescriptorGen(instName);
            }
            else if ((d_t == typeof(CyEndpointDescriptor)) || (d_t == typeof(CyAudioEndpointDescriptor)))
            {
                c = new CyUsbEndpointDescriptorGen(instName);
            }
            else if (d_t == typeof(CyASEndpointDescriptor))
            {
                c = new CyUsbASEndpointDescriptorGen(instName);
            }
            else if (d_t == typeof(CyMSEndpointDescriptor))
            {
                c = new CyUsbMSEndpointDescriptorGen(instName);
            }
            else if (d_t == typeof (CyHIDDescriptor))
            {
                c = new CyUsbHIDClassDescriptorGen(instName);
            }
            else if (d_t == typeof (CyStringDescriptor))
            {
                c = new CyUsbStringDescriptorGen(instName);
            }
            else if (d_t == typeof (CyStringZeroDescriptor))
            {
                c = new CyUsbStringZeroDescriptorGen(instName);
            }
            else if (d_t == typeof (CyHIDReportDescriptor))
            {
                c = new CyUsbHIDReportDescriptorGen(instName);
            }
            else if (d_t == typeof (CyHIDReportItemDescriptor))
            {
                c = new CyUsbHIDReportItemGen(instName);
            }
            else if ((d_t == typeof(CyACHeaderDescriptor)) ||
                (d_t == typeof(CyACInputTerminalDescriptor)) ||
                (d_t == typeof(CyACOutputTerminalDescriptor)) ||
                (d_t == typeof(CyACMixerUnitDescriptor)) ||
                (d_t == typeof(CyACSelectorUnitDescriptor)) ||
                (d_t == typeof(CyACFeatureUnitDescriptor)) ||
                (d_t == typeof(CyACProcessingUnitDescriptor)) ||
                (d_t == typeof(CyACExtensionDescriptor)) ||
                (d_t == typeof(CyASGeneralDescriptor)) ||
                (d_t == typeof(CyASFormatType1Descriptor)) ||
                (d_t == typeof(CyASFormatType2Descriptor)) ||

                (d_t == typeof(CyACHeaderDescriptor_v2)) ||
                (d_t == typeof(CyACClockSourceDescriptor_v2)) ||
                (d_t == typeof(CyACClockSelectorDescriptor_v2)) ||
                (d_t == typeof(CyACClockMultiplierDescriptor_v2)) ||
                (d_t == typeof(CyACInputTerminalDescriptor_v2)) ||
                (d_t == typeof(CyACOutputTerminalDescriptor_v2)) ||
                (d_t == typeof(CyACMixerUnitDescriptor_v2)) ||
                (d_t == typeof(CyACSelectorUnitDescriptor_v2)) ||
                (d_t == typeof(CyACFeatureUnitDescriptor_v2)) ||
                (d_t == typeof(CyACSamplingRateConverterDescriptor_v2)) ||
                (d_t == typeof(CyACEffectUnitDescriptor_v2)) ||
                (d_t == typeof(CyACProcessingUnitDescriptor_v2)) ||
                (d_t == typeof(CyACExtensionDescriptor_v2)) ||
                (d_t == typeof(CyASGeneralDescriptor_v2)))
            {
                c = new CyUsbAudioDescriptorGen(instName);
            }
            else if ((d_t == typeof (CyMSHeaderDescriptor)) ||
                (d_t == typeof(CyMSInJackDescriptor)) ||
                (d_t == typeof(CyMSOutJackDescriptor)) ||
                (d_t == typeof(CyMSElementDescriptor)))
            {
                c = new CyUsbMidiDescriptorGen(instName);
            }
            else if ((d_t == typeof(CyCDCHeaderDescriptor)) ||
                (d_t == typeof(CyCDCUnionDescriptor)) ||
                (d_t == typeof(CyCDCCountrySelectionDescriptor)) ||
                (d_t == typeof(CyCDCCallManagementDescriptor)) ||
                (d_t == typeof(CyCDCAbstractControlMgmtDescriptor)))
            {
                c = new CyUsbCDCDescriptorGen(instName);
            }
            else
            {
                Debug.Assert(false);
                c = null;
            }

            return c;
        }
    }

    #endregion Tree Generators

    internal class CyHidReportID
    {
        public byte m_id;
        public bool m_hasID;
        public ushort m_inputSize;
        public ushort m_outputSize;
        public ushort m_featureSize;

        public static int GetCount(List<CyHidReportID> reports, string name)
        {
            int count = 0;
            for (int i = 0; i < reports.Count; i++)
			{
                if (reports[i].m_inputSize > 0 && name == CyHidReportItem.RPTITEM_INPUT)
                    count++;
                else if (reports[i].m_outputSize > 0 && name == CyHidReportItem.RPTITEM_OUTPUT)
                    count++;
                else if (reports[i].m_featureSize > 0 && name == CyHidReportItem.RPTITEM_FEATURE)
                    count++;
			}
            return count;
        }

        public static byte GetMaxReportID(List<CyHidReportID> reports)
        {
            byte max = 0;
            for (int i = 0; i < reports.Count; i++)
            {
                if (reports[i].m_id > max)
                    max = reports[i].m_id;
            }
            return max;
        }

        public static byte GetMaxReportID(List<CyHidReportID> reports, string name)
        {
            byte max = 0;
            for (int i = 0; i < reports.Count; i++)
            {
                if (name == CyHidReportItem.RPTITEM_INPUT && reports[i].m_inputSize > 0 && reports[i].m_id > max)
                    max = reports[i].m_id;
                else if (name == CyHidReportItem.RPTITEM_OUTPUT && reports[i].m_outputSize > 0 && reports[i].m_id > max)
                    max = reports[i].m_id;
                else if (name == CyHidReportItem.RPTITEM_FEATURE && reports[i].m_featureSize > 0 && reports[i].m_id > max)
                    max = reports[i].m_id;
            }
            return max;
        }

        public static CyHidReportID ReportWithID(List<CyHidReportID> reports, byte id, string name)
        {
            CyHidReportID report = null;
            for (int i = 0; i < reports.Count; i++)
            {
                if (reports[i].m_id == id)
                {
                    if ((name == CyHidReportItem.RPTITEM_INPUT && reports[i].m_inputSize > 0) ||
                        (name == CyHidReportItem.RPTITEM_OUTPUT && reports[i].m_outputSize > 0) ||
                        (name == CyHidReportItem.RPTITEM_FEATURE && reports[i].m_featureSize > 0))
                    {
                        report = reports[i];
                        break;
                    }
                }
            }
            return report;
        }

        public string GetIDString()
        {
            string str = "";
            if (m_hasID)
            {
                str = "_ID" + m_id;
            }
            return str;
        }
    }
}
