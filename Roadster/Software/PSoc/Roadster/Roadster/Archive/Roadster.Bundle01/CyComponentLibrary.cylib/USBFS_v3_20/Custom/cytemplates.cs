/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace USBFS_v3_20
{
    public partial class CyUSBFSParameters
    {
        private enum CyInterfaceType { AUDIO, MIDI, CDC, GENERAL, MSC };
        private enum CyFileExt { XML, HID, DAT, H };
        private List<string> m_importAudioConfigKeys = new List<string>();
        private List<List<CyDescriptorNode>> m_importDescList = new List<List<CyDescriptorNode>>();

        #region Save Templates

        public void SaveDescriptor(CyUSBDescriptor desc, string initialDirectory)
        {
            CyDescriptorTemplate descTemplate = null;
            if (desc is CyDeviceDescriptor)
                descTemplate = new CyDeviceDescriptorTemplate(desc);
            else if (desc is CyConfigDescriptor)
                descTemplate = new CyConfigurationDescriptorTemplate(desc);
            else if (desc is CyInterfaceDescriptor)
                descTemplate = new CyInterfaceDescriptorTemplate(desc);
            else if (desc is CyAudioEndpointDescriptor)
                descTemplate = new CyAudioEndpointDescriptorTemplate(desc);
            else if (desc is CyASEndpointDescriptor)
                descTemplate = new CyASEndpointDescriptorTemplate(desc);
            else if (desc is CyEndpointDescriptor)
                descTemplate = new CyEndpointDescriptorTemplate(desc);
            else if (desc is CyHIDDescriptor)
                descTemplate = new CyHIDDescriptorTemplate(desc);
            else if (desc is CyInterfaceAssociationDescriptor)
                descTemplate = new CyIntAssociationDescriptorTemplate(desc);
            else if (desc is CyUsb20ExtensionDeviceCapabilityDescriptor)
                descTemplate = new CyUsb20ExtensionDeviceCapabilityDescriptorTemplate(desc);
            else if (desc is CyContainerIdDescriptor)
                descTemplate = new CyContainerIdDescriptorTemplate(desc);
            else
                Debug.Assert(false);

            XmlSerializer s = new XmlSerializer(typeof(CyDescriptorTemplate));
            using (StringWriter sw = new StringWriter())
            {
                string serializedXml;
                s.Serialize(sw, descTemplate);
                serializedXml = sw.ToString();
                SaveTemplate(serializedXml, desc.bDescriptorType, initialDirectory);
            }
        }

        public void SaveDescriptorList(CyDescriptorNode desc, CyUSBDescriptorType kind, string initialDirectory)
        {
            List<CyDescriptorTemplate> descTemplateList = new List<CyDescriptorTemplate>();
            BuildDescriptorTemplateList(desc, descTemplateList);
            if (kind == CyUSBDescriptorType.ALL)
            {
                descTemplateList.Add(new CyEpMemoryManagementTemplate(EPMemoryMgmt, EPMemoryAlloc));
            }
            XmlSerializer s = new XmlSerializer(typeof(List<CyDescriptorTemplate>));
            using (StringWriter sw = new StringWriter())
            {
                string serializedXml;
                s.Serialize(sw, descTemplateList);
                serializedXml = sw.ToString();
                SaveTemplate(serializedXml, kind, initialDirectory);
            }
        }

        public void SaveReport(CyDescriptorNode node_report, string initialDirectory)
        {
            XmlSerializer s = new XmlSerializer(typeof(CyReportTemplate));
            using (StringWriter sw = new StringWriter())
            {
                string serializedXml;
                CyReportTemplate report = new CyReportTemplate(node_report);
                s.Serialize(sw, report);
                serializedXml = sw.ToString();
                SaveTemplate(serializedXml, CyUSBDescriptorType.HID_REPORT, initialDirectory);
            }
        }

        private void BuildDescriptorTemplateList(CyDescriptorNode desc, List<CyDescriptorTemplate> lst)
        {
            if (desc.Value != null)
            {
                //  Reassign Display Name to child interface descriptors because CyInterfaceGeneralDescriptor 
                //  is not exported. 
                if (desc.Value is CyInterfaceGeneralDescriptor)
                {
                    string dispName = ((CyInterfaceGeneralDescriptor) desc.Value).DisplayName;
                    if (!String.IsNullOrEmpty(dispName))
                    {
                        for (int i = 0; i < desc.Nodes.Count; i++)
                        {
                            if ((desc.Nodes[i].Value is CyAudioInterfaceDescriptor) ||
                                (desc.Nodes[i].Value is CyCDCInterfaceDescriptor) ||
                                (desc.Nodes[i].Value is CyMscInterfaceDescriptor))
                                ((CyInterfaceDescriptor) desc.Nodes[i].Value).InterfaceDisplayName = dispName;
                        }
                    }
                }


                if (desc.Value is CyDeviceDescriptor)
                {
                    lst.Add(new CyDeviceDescriptorTemplate(desc.Value));
                    AddSerialToTemplateList(lst);
                }
                else if (desc.Value is CyConfigDescriptor)
                    lst.Add(new CyConfigurationDescriptorTemplate(desc.Value));
                else if (desc.Value is CyInterfaceDescriptor)
                    lst.Add(new CyInterfaceDescriptorTemplate(desc.Value));
                else if ((desc.Value is CyEndpointDescriptor) && !(desc.Value is CyAudioEndpointDescriptor))
                    lst.Add(new CyEndpointDescriptorTemplate(desc.Value));

                else if (desc.Value is CyInterfaceAssociationDescriptor)
                    lst.Add(new CyIntAssociationDescriptorTemplate(desc.Value));

                else if (desc.Value is CyBosDescriptor)
                    lst.Add(new CyBosDescriptorTemplate(desc.Value));
                else if (desc.Value is CyUsb20ExtensionDeviceCapabilityDescriptor)
                    lst.Add(new CyUsb20ExtensionDeviceCapabilityDescriptorTemplate(desc.Value));
                else if (desc.Value is CyContainerIdDescriptor)
                    lst.Add(new CyContainerIdDescriptorTemplate(desc.Value));
                    

                else if (desc.Value is CyAudioEndpointDescriptor)
                    lst.Add(new CyAudioEndpointDescriptorTemplate(desc.Value));
                else if (desc.Value is CyASEndpointDescriptor)
                    lst.Add(new CyASEndpointDescriptorTemplate(desc.Value));
                else if (desc.Value is CyACHeaderDescriptor)
                    lst.Add(new CyACHeaderDescriptorTemplate(desc.Value));
                else if (desc.Value is CyACInputTerminalDescriptor)
                    lst.Add(new CyACInputTerminalDescriptorTemplate(desc.Value)); 
                else if (desc.Value is CyACOutputTerminalDescriptor)
                    lst.Add(new CyACOutputTerminalDescriptorTemplate(desc.Value));
                else if (desc.Value is CyACMixerUnitDescriptor)
                    lst.Add(new CyACMixerUnitDescriptorTemplate(desc.Value));
                else if (desc.Value is CyACSelectorUnitDescriptor)
                    lst.Add(new CyACSelectorUnitDescriptorTemplate(desc.Value));
                else if (desc.Value is CyACFeatureUnitDescriptor)
                    lst.Add(new CyACFeatureUnitDescriptorTemplate(desc.Value));
                else if (desc.Value is CyACProcessingUnitDescriptor)
                    lst.Add(new CyACProcessingUnitDescriptorTemplate(desc.Value));
                else if (desc.Value is CyACExtensionDescriptor)
                    lst.Add(new CyACExtensionDescriptorTemplate(desc.Value));
                else if (desc.Value is CyASGeneralDescriptor)
                    lst.Add(new CyASGeneralDescriptorTemplate(desc.Value));
                else if (desc.Value is CyASFormatType1Descriptor)
                    lst.Add(new CyASFormatType1DescriptorTemplate(desc.Value));
                else if (desc.Value is CyASFormatType2Descriptor)
                    lst.Add(new CyASFormatType2DescriptorTemplate(desc.Value));

                else if (desc.Value is CyACHeaderDescriptor_v2)
                    lst.Add(new CyACHeaderDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACClockSourceDescriptor_v2)
                    lst.Add(new CyACClockSourceDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACClockSelectorDescriptor_v2)
                    lst.Add(new CyACClockSelectorDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACClockMultiplierDescriptor_v2)
                    lst.Add(new CyACClockMultiplierDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACInputTerminalDescriptor_v2)
                    lst.Add(new CyACInputTerminalDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACOutputTerminalDescriptor_v2)
                    lst.Add(new CyACOutputTerminalDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACMixerUnitDescriptor_v2)
                    lst.Add(new CyACMixerUnitDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACSelectorUnitDescriptor_v2)
                    lst.Add(new CyACSelectorUnitDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACFeatureUnitDescriptor_v2)
                    lst.Add(new CyACFeatureUnitDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACSamplingRateConverterDescriptor_v2)
                    lst.Add(new CyACSRCDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACEffectUnitDescriptor_v2)
                    lst.Add(new CyACEffectUnitDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACProcessingUnitDescriptor_v2)
                    lst.Add(new CyACProcessingUnitDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyACExtensionDescriptor_v2)
                    lst.Add(new CyACExtensionDescriptorTemplate_v2(desc.Value));
                else if (desc.Value is CyASGeneralDescriptor_v2)
                    lst.Add(new CyASGeneralDescriptorTemplate_v2(desc.Value));

                else if (desc.Value is CyMSEndpointDescriptor)
                    lst.Add(new CyMSEndpointDescriptorTemplate(desc.Value));
                else if (desc.Value is CyMSHeaderDescriptor)
                    lst.Add(new CyMSHeaderDescriptorTemplate(desc.Value));
                else if (desc.Value is CyMSInJackDescriptor)
                    lst.Add(new CyMSInJackDescriptorTemplate(desc.Value));
                else if (desc.Value is CyMSOutJackDescriptor)
                    lst.Add(new CyMSOutJackDescriptorTemplate(desc.Value));
                else if (desc.Value is CyMSElementDescriptor)
                    lst.Add(new CyMSElementDescriptorTemplate(desc.Value));

                else if (desc.Value is CyCDCHeaderDescriptor)
                    lst.Add(new CyCDCHeaderDescriptorTemplate(desc.Value));
                else if (desc.Value is CyCDCUnionDescriptor)
                    lst.Add(new CyCDCUnionDescriptorTemplate(desc.Value));
                else if (desc.Value is CyCDCCountrySelectionDescriptor)
                    lst.Add(new CyCDCCountrySelectionDescriptorTemplate(desc.Value));
                else if (desc.Value is CyCDCCallManagementDescriptor)
                    lst.Add(new CyCDCCallManagementDescriptorTemplate(desc.Value));
                else if (desc.Value is CyCDCAbstractControlMgmtDescriptor)
                    lst.Add(new CyCDCAbstractControlMgmtDescriptorTemplate(desc.Value));

                else if (desc.Value is CyHIDDescriptor)
                {
                    lst.Add(new CyHIDDescriptorTemplate(desc.Value));
                    if (((CyHIDDescriptor)desc.Value).wReportIndex != 0)
                    {
                        AddHidReportToTemplateList(((CyHIDDescriptor)desc.Value).wReportIndex, lst);
                    }
                }
                // Alternate are not included to the template, all other are
                else if (desc.Value.bDescriptorType != CyUSBDescriptorType.ALTERNATE) 
                {
                    Debug.Assert(false);
                }
            }
            for (int i = 0; i < desc.Nodes.Count; i++)
            {
                BuildDescriptorTemplateList(desc.Nodes[i], lst);
            }
        }

        private void AddSerialToTemplateList(List<CyDescriptorTemplate> lst)
        {
            CyStringDescriptor serial = GetSerialDescriptor();
            if (serial.bUsed)
            {
                lst.Add(new CySerialStringDescriptorTemplate(serial));
            }
        }

        private void AddHidReportToTemplateList(uint wReportIndex, List<CyDescriptorTemplate> lst)
        {
            string reportKey = CyDescriptorNode.GetKeyByIndex(wReportIndex);
            CyDescriptorNode node_report = m_hidReportTree.GetNodeByKey(reportKey);
            lst.Add(new CyReportTemplate(node_report));
        }

        public static void SaveTemplate(string serializedXml, CyUSBDescriptorType kind, string initialDirectory)
        {
            using (SaveFileDialog saveFileDialog1 = new SaveFileDialog())
            {
                string ext = GetTemplateFileExt(kind, false);
                string shortExt = ext.Substring(ext.IndexOf("(*.") + 3, 7);
                saveFileDialog1.Filter = String.Format("{0}XML Files (*.xml)|*.xml", ext);
                saveFileDialog1.InitialDirectory = initialDirectory;
                saveFileDialog1.DefaultExt = shortExt;
                saveFileDialog1.Title = "Save a Template File";
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        using (StreamWriter strw = new StreamWriter(saveFileDialog1.FileName))
                        {
                            strw.WriteLine(serializedXml);
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(
                            String.Format("{0}\r\n{1}", Properties.Resources.MSG_UNABLE_SAVE_TEMPLATE, ex),
                             Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }    

        #endregion Save Templates

        //------------------------------------------------------------------------------------------------------------

        #region Import Templates

        public CyUSBDescriptor ImportDescriptor(CyUSBDescriptorType kind, string initialDirectory)
        {
            CyUSBDescriptor result = null;
            CyDescriptorTemplate tDesc = null;
            try
            {
                CyFileExt fileExt;
                byte[] byteArray;
                string templateName;
                string serializedstr = LoadTemplateFromFile(kind, initialDirectory, out fileExt, out byteArray, out templateName);

                if (!String.IsNullOrEmpty(serializedstr) && (fileExt == CyFileExt.XML))
                {
                    XmlSerializer s = new XmlSerializer(typeof(CyDescriptorTemplate));
                    tDesc = (CyDescriptorTemplate)s.Deserialize(new StringReader(serializedstr));
                }
                else
                {
                    return result;
                }
                result = tDesc.ConvertToUSBDesc();
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    String.Format("{0}\r\n{1}", Properties.Resources.MSG_UNABLE_LOAD_TEMPLATE, ex),
                     Properties.Resources.MSG_TITLE_WARNING, MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

            CheckDescriptorForStrings(result);

            return result;
        }

        public bool ImportDescriptorList(CyUSBDescriptorType kind, string filePath, string initialDirectory)
        {
            bool res = false;
            List<CyUSBDescriptor> lst = new List<CyUSBDescriptor>();
            List<CyDescriptorTemplate> tDescList = null;
            bool epmmOld = true;
            try
            {
                CyFileExt fileExt;
                string serializedstr;

                if (filePath == string.Empty)
                {
                    byte[] byteArray;
                    string templateName;
                    serializedstr = LoadTemplateFromFile(kind, initialDirectory, out fileExt, out byteArray, 
                        out templateName);
                }
                else
                {
                    fileExt = CyFileExt.XML;
                    serializedstr = ReadFile(filePath).ToString();
                }

                if (!String.IsNullOrEmpty(serializedstr) && (fileExt == CyFileExt.XML))
                {
                    XmlSerializer s = new XmlSerializer(typeof(List<CyDescriptorTemplate>));
                    tDescList = (List<CyDescriptorTemplate>)s.Deserialize(new StringReader(serializedstr));
                }
                else
                {
                    return res;
                }

                for (int i = 0; i < tDescList.Count; i++)
                {
                    // Add report to the hid report tree, not include it to the lst
                    if (tDescList[i] is CyReportTemplate)
                    {
                        int wIndex = BuildReportTreeFromDesc(tDescList[i]);
                        // Set report index in the Hid descriptor
                        if (wIndex >= 0)
                        {
                            for (int j = lst.Count-1; j >= 0; j--)
                            {
                                if (lst[j].bDescriptorType == CyUSBDescriptorType.HID)
                                {
                                    ((CyHIDDescriptor) lst[j]).wReportIndex = (uint) wIndex;
                                    break;
                                }
                            }
                        }
                    }
                    else if ((tDescList[i] is CyEpMemoryManagementTemplate) && (kind == CyUSBDescriptorType.ALL))
                    {
                        EPMemoryMgmt = ((CyEpMemoryManagementTemplate) tDescList[i]).MemoryManagement;
                        EPMemoryAlloc = ((CyEpMemoryManagementTemplate)tDescList[i]).MemoryAllocation;
                        epmmOld = false;
                    }
                    else
                    {
                        lst.Add(tDescList[i].ConvertToUSBDesc());
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    String.Format("{0}\r\n{1}", Properties.Resources.MSG_UNABLE_LOAD_TEMPLATE, ex),
                     Properties.Resources.MSG_TITLE_WARNING, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return res;
            }

            for (int i = 0; i < lst.Count; i++)
            {
                CheckDescriptorForStrings(lst[i]);
            }

            if (lst.Count > 0)
            {
                if (lst[0].GetLevel() == CyUSBDescriptor.DEVICE_LEVEL)
                {
                    int numDevices = m_deviceTree.Nodes[0].Nodes.Count;
                    m_importDescList.Clear();
                    m_importAudioConfigKeys.Clear();
                    CyDescriptorNode subTree = BuildDevTreeFromDesc(lst, 0, m_deviceTree.Nodes[0].Key);
                    SortAudioInfFromBuffer();

                    if (epmmOld) // Reassign Endpoint memory management value for compatibility with previous versions
                    {
                        CyDeviceDescriptor node =
                            (CyDeviceDescriptor) m_deviceTree.Nodes[0].Nodes[numDevices].Value;
                        try
                        {
                            EPMemoryMgmt = (CyMemoryManagement)node.bMemoryMgmt;
                        }
                        catch { Debug.Assert(false); }
                    }
                    res = true;
                }
                else if (lst[0].GetLevel() == CyUSBDescriptor.INTERFACE_LEVEL)
                {
                    CyDescriptorTree tree;
                    CyInterfaceType intType;

                    if (lst[0] is CyMscInterfaceDescriptor)
                    {
                        tree = m_mscTree;
                        intType = CyInterfaceType.MSC;
                    }
                    else if(lst[0] is CyCommunicationsInterfaceDescriptor || lst[0] is CyDataInterfaceDescriptor)
                    {
                        tree = m_cdcTree;
                        intType = CyInterfaceType.CDC;
                    }
                    else if (lst[0] is CyAudioInterfaceDescriptor)
                    {
                        if (kind == CyUSBDescriptorType.MIDI)
                        {
                            tree = m_midiTree;
                            intType = CyInterfaceType.MIDI;
                        }
                        else
                        {
                            tree = m_audioTree;
                            intType = CyInterfaceType.AUDIO;
                        }
                    }
                    else
                    {
                        Debug.Assert(false);
                        return false;
                    }

                    CyDescriptorNode subTree = BuildClassSpecificTreeFromDesc(lst, 0, tree.Nodes[0].Key, intType);
                    res = true;
                }
            }
            return res;
        }

        /// <summary>
        /// Imports a HID Report from the file.
        /// </summary>
        /// <returns>ReportTemplate class</returns>
        public bool ImportReport(string fileName)
        {
            bool res = false;
            CyReportTemplate rptTemplate;
            try
            {
                string serializedstr = "";
                byte[] byteArray = null;
                string templateName = ""; 
                CyFileExt fileExt = CyFileExt.XML;
                if (String.IsNullOrEmpty(fileName))
                {
                    serializedstr = LoadTemplateFromFile(CyUSBDescriptorType.HID_REPORT, templatePath, out fileExt, out byteArray,
                                                         out templateName);
                }
                else
                {
                    StringBuilder sb = ReadFile(fileName);
                    if (sb != null)
                        serializedstr = sb.ToString();
                }
                if (!String.IsNullOrEmpty(serializedstr))
                {
                    if (fileExt == CyFileExt.HID)
                    {
                        List<CyHidReportItem> hidItems = ParseHIDFormat(byteArray);
                        res = BuildReportTreeFromDesc(hidItems, templateName) >= 0;
                    }
                    else if (fileExt == CyFileExt.DAT)
                    {
                        List<CyHidReportItem> hidItems = ParseDATFormat(serializedstr);
                        res = BuildReportTreeFromDesc(hidItems, templateName) >= 0;
                    }
                    else if (fileExt == CyFileExt.H)
                    {
                        List<CyHidReportItem> hidItems = ParseHFormat(serializedstr);
                        res = BuildReportTreeFromDesc(hidItems, templateName) >= 0;
                    }
                    else if (fileExt == CyFileExt.XML)
                    {
                        XmlSerializer s = new XmlSerializer(typeof(CyReportTemplate));
                        rptTemplate = (CyReportTemplate)s.Deserialize(new StringReader(serializedstr));
                        res = BuildReportTreeFromDesc(rptTemplate) >= 0;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    String.Format("{0}\r\n{1}", Properties.Resources.MSG_UNABLE_LOAD_TEMPLATE, ex),
                     Properties.Resources.MSG_TITLE_WARNING, MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            return res;
        }

        /// <summary>
        /// Converts the array of descriptors to the device descriptor tree. Used in import operation. 
        /// Is recursive.
        /// </summary>
        /// <param name="lst">array of descriptors</param>
        /// <param name="index">index of the current descriptor in the lst</param>
        /// <param name="parentKey">key of the parent node in the device tree</param>
        /// <returns>newly created node</returns>
        private CyDescriptorNode BuildDevTreeFromDesc(List<CyUSBDescriptor> lst, int index, string parentKey)
        {
            CyDescriptorNode node;
            if (lst[index] is CyInterfaceAssociationDescriptor)
            {
                node = m_deviceTree.AddNode(parentKey, CyUSBDescriptorType.INTERFACE_ASSOCIATION);
            }
            else if (lst[index] is CyBosDescriptor)
            {
                node = m_deviceTree.AddNode(parentKey, CyUSBDescriptorType.BOS);
            }
            else if (lst[index] is CyUsb20ExtensionDeviceCapabilityDescriptor)
            {
                node = m_deviceTree.AddNode(parentKey, CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY);
            }
            else if (lst[index] is CyContainerIdDescriptor)
            {
                node = m_deviceTree.AddNode(parentKey, CyUSBDescriptorType.CONTAINER_ID);
            }
            else
            {
                node = m_deviceTree.AddNode(parentKey);
            }
            if (node.Value.bDescriptorType == CyUSBDescriptorType.ALTERNATE)
            {
                // If interface alternate number is 0, add new Alternate node, else attach it to previous
                if (((CyInterfaceDescriptor)lst[index]).bAlternateSetting == 0)
                {
                    // If lst[index] is audio descriptor, add node to the audio tree
                    if (lst[index] is CyAudioInterfaceDescriptor)
                    {
                        AddAudioInfToBuffer(node, parentKey);
                    }

                    // If lst[index] is cdc descriptor, add node to the cdc tree
                    if (lst[index] is CyCDCInterfaceDescriptor)
                    {
                        if (!m_cdcTree.Nodes[0].Nodes.Contains(node))
                            m_cdcTree.Nodes[0].Nodes.Add(node);
                    }

                    // If lst[index] is msc descriptor, add node to the dfu tree
                    if (lst[index] is CyMscInterfaceDescriptor)
                    {
                        if (!m_mscTree.Nodes[0].Nodes.Contains(node))
                            m_mscTree.Nodes[0].Nodes.Add(node);
                    }

                    // Assign DisplayName if exists
                    if (!String.IsNullOrEmpty(((CyInterfaceDescriptor)lst[index]).InterfaceDisplayName))
                    {
                        ((CyInterfaceGeneralDescriptor) node.Value).DisplayName =
                            ((CyInterfaceDescriptor) lst[index]).InterfaceDisplayName;
                    }
                    // Make Interface node current
                    node = node.Nodes[0];
                }
                else
                {
                    byte nodeIndex = 0;
                    CyDescriptorNode configNode = m_deviceTree.GetNodeByKey(parentKey);
                    // If alternate number > 0, remove general interface node and attach alternate interface to the last
                    // existing general interface node
                    if (GetInterfaceCount(configNode) > 1)
                    {
                        configNode.Nodes.Remove(node);
                    }
                    // Find the last existing general interface node
                    for (int i = configNode.Nodes.Count - 1; i >= 0; i--)
                    {
                        if (configNode.Nodes[i].Value.bDescriptorType == CyUSBDescriptorType.ALTERNATE)
                        {
                            nodeIndex = (byte)i;
                            break;
                        }
                    }

                    CyDescriptorNode generalInterfaceNode = configNode.Nodes[nodeIndex];

                    // If lst[index] is audio descriptor, add node to the audio tree
                    if (lst[index] is CyAudioInterfaceDescriptor)
                    {
                        AddAudioInfToBuffer(generalInterfaceNode, parentKey);
                    }

                    m_deviceTree.AddNode(generalInterfaceNode.Key, configNode.Key);
                    node = generalInterfaceNode.Nodes[generalInterfaceNode.Nodes.Count - 1];
                }
            }
            node.Value = lst[index];
            node.Nodes.Clear();

            int levelParent = lst[index].GetLevel();
            int childIndex = index + 1;
            // If found a new device descriptor, start a new branch
            if ((childIndex < lst.Count) && (lst[childIndex].GetLevel() == CyUSBDescriptor.DEVICE_LEVEL))
            {
                BuildDevTreeFromDesc(lst, childIndex, m_deviceTree.Nodes[0].Key);
            }
            else
            {
                while ((childIndex < lst.Count) && (lst[childIndex].GetLevel() > levelParent))
                {
                    if (lst[childIndex].GetLevel() == levelParent + 1)
                    {
                        BuildDevTreeFromDesc(lst, childIndex, node.Key);
                    }
                    else if (lst[childIndex].GetLevel() == CyUSBDescriptor.STRING_LEVEL) // Serial String 
                    {
                        CyDescriptorNode serialNode = m_stringTree.GetNodeByKey(NODEKEY_STRING_SERIAL);
                        if (serialNode != null)
                            serialNode.Value = lst[childIndex];
                    }
                    childIndex++;
                }
            }
            return node;
        }

        private void AddAudioInfToBuffer(CyDescriptorNode node, string parentKey)
        {
            int keyIndex = 0;
            if (!m_importAudioConfigKeys.Contains(parentKey))
                m_importAudioConfigKeys.Add(parentKey);
            keyIndex = m_importAudioConfigKeys.IndexOf(parentKey);

            if (m_importDescList.Count < keyIndex + 1)
                m_importDescList.Add(new List<CyDescriptorNode>());
            if (!m_importDescList[keyIndex].Contains(node))
                m_importDescList[keyIndex].Add(node);
        }

        private void SortAudioInfFromBuffer()
        {
            foreach (List<CyDescriptorNode> infNodeList in m_importDescList) // Configurations
            {
                bool haveAS = false;
                bool haveMS = false;
                CyInterfaceType[] infTypes = new CyInterfaceType[infNodeList.Count];
                for (int k = 0; k < infNodeList.Count; k++) // General Interfaces
                {
                    bool haveAltAS = false;
                    bool haveAltMS = false;
                    CyDescriptorNode infNode = infNodeList[k];
                    for (int i = 0; i < infNode.Nodes.Count; i++) // Alternate Interfaces
                    {
                        if (((CyInterfaceDescriptor)infNode.Nodes[i].Value).bInterfaceSubClass == 
                            (byte)CyUSBOtherTypes.CyAudioSubclassCodes.AUDIOSTREAMING)
                        {
                            haveAS = true;
                            haveAltAS = true;
                        }
                        else if (((CyInterfaceDescriptor)infNode.Nodes[i].Value).bInterfaceSubClass ==
                            (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING)
                        {
                            haveMS = true;
                            haveAltMS = true;
                        }
                    }
                    if (haveAltAS) infTypes[k] = CyInterfaceType.AUDIO;
                    else if (haveAltMS) infTypes[k] = CyInterfaceType.MIDI;
                    else infTypes[k] = CyInterfaceType.GENERAL;
                }
                for (int k = 0; k < infNodeList.Count; k++) // General Interfaces
                {
                    if (infTypes[k] == CyInterfaceType.AUDIO)
                    {
                        m_audioTree.Nodes[0].Nodes.Add(infNodeList[k]);
                    }
                    else if (infTypes[k] == CyInterfaceType.MIDI)
                    {
                        m_midiTree.Nodes[0].Nodes.Add(infNodeList[k]);
                    }
                    else
                    {
                        if (!haveMS)
                            m_audioTree.Nodes[0].Nodes.Add(infNodeList[k]);
                        else if (haveMS && !haveAS)
                            m_midiTree.Nodes[0].Nodes.Add(infNodeList[k]);
                        else // haveAS & haveMS 
                        {
                            bool foundSpec = false;
                            for (int j = k + 1; j < infNodeList.Count; j++)
                            {
                                if (infTypes[j] == CyInterfaceType.AUDIO)
                                {
                                    foundSpec = true;
                                    m_audioTree.Nodes[0].Nodes.Add(infNodeList[k]);
                                    break;
                                }
                                else if (infTypes[j] == CyInterfaceType.MIDI)
                                {
                                    foundSpec = true;
                                    m_midiTree.Nodes[0].Nodes.Add(infNodeList[k]);
                                    break;
                                }
                            }
                            if (!foundSpec)
                            {
                                for (int j = k - 1; j >= 0; j--)
                                {
                                    if (infTypes[j] == CyInterfaceType.AUDIO)
                                    {
                                        m_audioTree.Nodes[0].Nodes.Add(infNodeList[k]);
                                    }
                                    else if (infTypes[j] == CyInterfaceType.MIDI)
                                    {
                                        m_midiTree.Nodes[0].Nodes.Add(infNodeList[k]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private CyDescriptorNode BuildClassSpecificTreeFromDesc(List<CyUSBDescriptor> lst, int index, string parentKey, 
                                                           CyInterfaceType interfaceType)
        {
            CyDescriptorTree tree = m_audioTree;
            if (interfaceType == CyInterfaceType.MIDI) tree = m_midiTree;
            if (interfaceType == CyInterfaceType.CDC) tree = m_cdcTree;
            if (interfaceType == CyInterfaceType.MSC) tree = m_mscTree;

            CyDescriptorNode node = new CyDescriptorNode(lst[index]);
            CyDescriptorNode parentNode = tree.GetNodeByKey(parentKey);

            if (parentNode == null) return null;

            if ((parentKey == NODEKEY_AUDIO) || (parentKey == NODEKEY_CDC) || (parentKey == NODEKEY_MSC) || 
                ((parentKey == NODEKEY_MIDI))) 
            {
                // Create general interface descriptor first or reassign to existing general descriptor
                if ((node.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE) &&
                    (((CyInterfaceDescriptor)lst[index]).bAlternateSetting > 0) &&
                    (parentNode.Nodes.Count > 0))
                {
                    parentNode = parentNode.Nodes[parentNode.Nodes.Count - 1];
                }
                else
                {
                    string displayName;
                    // Assign DisplayName if exists
                    if (!String.IsNullOrEmpty(((CyInterfaceDescriptor)lst[index]).InterfaceDisplayName))
                    {
                        // restore existing name
                        displayName = ((CyInterfaceDescriptor)lst[index]).InterfaceDisplayName;
                    }
                    else
                    {
                        // generate name for interface general descriptor
                        int newIndex = parentNode.Nodes.Count + 1;
                        string intStr = "";
                        switch (interfaceType)
                        {
                            case CyInterfaceType.AUDIO:
                                intStr = "Audio";
                                break;
                            case CyInterfaceType.CDC:
                                intStr = "CDC";
                                break;
                            case CyInterfaceType.MIDI:
                                intStr = "MIDI";
                                break;
                            case CyInterfaceType.MSC:
                                intStr = "MSC";
                                break;
                        }
                        displayName = String.Format("{0} Interface {1}", intStr, newIndex);
                    }
                    CyDescriptorNode generalInterfaceNode =
                        new CyDescriptorNode(new CyInterfaceGeneralDescriptor(displayName));
                    generalInterfaceNode.Key = generalInterfaceNode.Key.Replace(NODEKEY_USBDESCRIPTOR, 
                                                                                NODEKEY_INTERFACE);
                    parentNode.Nodes.Add(generalInterfaceNode);
                    parentNode = parentNode.Nodes[parentNode.Nodes.Count - 1];
                }
            }
            parentNode.Nodes.Add(node);


            int levelParent = lst[index].GetLevel();
            int childIndex = index + 1;
            // If found a new interface descriptor, start a new branch
            if ((childIndex < lst.Count) && (lst[childIndex].GetLevel() == CyUSBDescriptor.INTERFACE_LEVEL))
            {
                BuildClassSpecificTreeFromDesc(lst, childIndex, tree.Nodes[0].Key, interfaceType);
            }
            else
            {
                while ((childIndex < lst.Count) && (lst[childIndex].GetLevel() > levelParent))
                {
                    if (lst[childIndex].GetLevel() == levelParent + 1)
                    {
                        BuildClassSpecificTreeFromDesc(lst, childIndex, node.Key, interfaceType);
                    }
                    childIndex++;
                }
            }

            return node;
        }

        private int BuildReportTreeFromDesc(CyDescriptorTemplate rptTemplate)
        {
            int wIndex = -1;
            UInt16 lastUsagePage = 0;
            CyDescriptorNode rptNode, newNode;
            CyReportTemplate rpt = (CyReportTemplate) rptTemplate;
            if (rptTemplate != null)
            {
                rptNode = m_hidReportTree.AddNode(m_hidReportTree.Nodes[0].Key);
                //Report name
                ((CyHIDReportDescriptor)rptNode.Value).Name = rpt.m_reportName;
                //Items
                for (int i = 0; i < rpt.m_items.Count; i++)
                {
                    CyHidReportItem item = rpt.m_items[i].ConvertToHidReportItem();
                    if (item != null)
                    {
                        newNode = m_hidReportTree.AddNode(rptNode.Key);
                        ((CyHIDReportItemDescriptor)newNode.Value).Item = item;
                    }

                    // remember last usage_page
                    if ((item.Name == CyHidReportItem.RPTITEM_USAGE_PAGE) && (item.m_value.Count >= 2))
                    {
                        lastUsagePage = item.m_value[1];
                        if (item.m_value.Count > 2)
                            lastUsagePage |= (ushort)(item.m_value[2] << 8);
                    }
                    if (item.Name == CyHidReportItem.RPTITEM_USAGE)
                    {
                        CyHidDescriptorPage.SetListForItem(item, lastUsagePage);
                    }
                }
                // Get Index
                string strConfigKey = m_hidReportTree.GetKeyByNode(rptNode.Value);
                if (strConfigKey != "")
                {
                    wIndex = (int)CyDescriptorNode.GetDescriptorIndex(strConfigKey);
                }
                ParamHIDReportTreeChanged();
            }
            return wIndex;
        }

        private int BuildReportTreeFromDesc(List<CyHidReportItem> itemList, string rptName)
        {
            int wIndex = -1;
            UInt16 lastUsagePage = 0;
            CyDescriptorNode rptNode, newNode;
            if (itemList != null)
            {
                rptNode = m_hidReportTree.AddNode(m_hidReportTree.Nodes[0].Key);
                //Report name
                ((CyHIDReportDescriptor)rptNode.Value).Name = rptName;
                //Items
                for (int i = 0; i < itemList.Count; i++)
                {
                    CyHidReportItem item = itemList[i];
                    newNode = m_hidReportTree.AddNode(rptNode.Key);
                    ((CyHIDReportItemDescriptor)newNode.Value).Item = item;
                  
                    // remember last usage_page
                    if ((item.Name == CyHidReportItem.RPTITEM_USAGE_PAGE) && (item.m_value.Count >= 2))
                    {
                        lastUsagePage = item.m_value[1];
                        if (item.m_value.Count > 2)
                            lastUsagePage |= (ushort)(item.m_value[2] << 8);
                    }
                    if (item.Name == CyHidReportItem.RPTITEM_USAGE)
                    {
                        CyHidDescriptorPage.SetListForItem(item, lastUsagePage);
                    }
                }
                // Get Index
                string strConfigKey = m_hidReportTree.GetKeyByNode(rptNode.Value);
                if (strConfigKey != "")
                {
                    wIndex = (int)CyDescriptorNode.GetDescriptorIndex(strConfigKey);
                }
                ParamHIDReportTreeChanged();
            }
            return wIndex;
        }

        private void CheckDescriptorForStrings(CyUSBDescriptor desc)
        {
            if (desc == null) return;
            string newStr;
            if (desc is CyDeviceDescriptor)
            {
                newStr = ((CyDeviceDescriptor)desc).sManufacturer;
                ((CyDeviceDescriptor)desc).iwManufacturer = AddNewStrDescriptor(newStr);

                newStr = ((CyDeviceDescriptor)desc).sProduct;
                ((CyDeviceDescriptor)desc).iwProduct = AddNewStrDescriptor(newStr);
            }
            if (desc is CyConfigDescriptor)
            {
                newStr = ((CyConfigDescriptor)desc).sConfiguration;
                ((CyConfigDescriptor)desc).iwConfiguration = AddNewStrDescriptor(newStr);
            }
            if (desc is CyInterfaceDescriptor)
            {
                newStr = ((CyInterfaceDescriptor)desc).sInterface;
                ((CyInterfaceDescriptor)desc).iwInterface = AddNewStrDescriptor(newStr);
            }
            if (desc is CyInterfaceAssociationDescriptor)
            {
                newStr = ((CyInterfaceAssociationDescriptor)desc).sFunction;
                ((CyInterfaceAssociationDescriptor)desc).iwFunction = AddNewStrDescriptor(newStr);
            }
            if (desc.bDescriptorType == CyUSBDescriptorType.AUDIO)
            {
                try
                {
                    Type descType = desc.GetType();
                    FieldInfo[] fi = descType.GetFields();
                    for (int j = 0; j < fi.Length; j++)
                    {
                        if (fi[j].Name.StartsWith("iw"))
                        {
                            newStr = "";
                            string propName = fi[j].Name.Remove(0, 2).Insert(0, "s");
                            PropertyInfo pi = descType.GetProperty(propName);
                            if ((pi != null) && (pi.GetValue(desc, null) != null))
                                newStr = pi.GetValue(desc, null).ToString();
                            fi[j].SetValue(desc, AddNewStrDescriptor(newStr));
                        }
                    }
                }
                catch (Exception ex)
                {
                    Debug.Assert(false, ex.ToString());
                }
            }
        }

        private uint AddNewStrDescriptor(string str)
        {
            uint strIndex = 0;
            if (!String.IsNullOrEmpty(str))
            {
                // If string exists, return its index
                for (int i = 1; i < m_stringTree.Nodes[0].Nodes.Count; i++)
                {
                    CyStringDescriptor strDesc = (CyStringDescriptor) m_stringTree.Nodes[0].Nodes[i].Value;
                    if (strDesc.bString == str)
                        strIndex = GetStringDescriptorIndex(strDesc, this);
                }
                // If not exists, create new
                if (strIndex == 0)
                {
                    // Add string to the string descriptors list
                    CyStringDescriptor newDesc = CreateNewStringDescriptor(str, this);
                    // Get the index of the new String Descriptor
                    strIndex = GetStringDescriptorIndex(newDesc, this);
                }
            }
            return strIndex;
        }

        /// <summary>
        /// Imports a HID Report from the file.
        /// </summary>
        /// <returns>ReportTemplate class</returns>
        private static string LoadTemplateFromFile(CyUSBDescriptorType kind, string initialDirectory, out CyFileExt fileExt,
                                                   out byte[] byteArray, out string templateName)
        {
            fileExt = CyFileExt.XML;
            byteArray = null;
            templateName = "";
            StringBuilder fileContent = new StringBuilder();
            using (OpenFileDialog openFileDialog1 = new OpenFileDialog())
            {
                string ext = GetTemplateFileExt(kind, true);
                openFileDialog1.Filter = String.Format("{0}XML Files (*.xml)|*.xml", ext);
                openFileDialog1.InitialDirectory = initialDirectory;
                openFileDialog1.Title = "Open a Template File";
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    switch (Path.GetExtension(openFileDialog1.FileName))
                    {
                        case ".xml":
                            fileExt = CyFileExt.XML;
                            fileContent = ReadFile(openFileDialog1.FileName);
                            break;
                        case ".hid":
                            fileExt = CyFileExt.HID;
                            byteArray = ReadBinaryFile(openFileDialog1.FileName);
                            templateName = Path.GetFileNameWithoutExtension(openFileDialog1.FileName);
                            // fileContent could not be empty 
                            fileContent.Append(templateName);
                            break;
                        case ".dat":
                            fileExt = CyFileExt.DAT;
                            fileContent = ReadFile(openFileDialog1.FileName);
                            templateName = Path.GetFileNameWithoutExtension(openFileDialog1.FileName);
                            break;
                        case ".h":
                            fileExt = CyFileExt.H;
                            fileContent = ReadFile(openFileDialog1.FileName);
                            templateName = Path.GetFileNameWithoutExtension(openFileDialog1.FileName);
                            break;
                        default:
                            Debug.Assert(false);
                            break;
                    }

                    if (fileContent == null)
                    {
                        MessageBox.Show(Properties.Resources.MSG_UNABLE_LOAD_TEMPLATE,
                             Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
            return fileContent.ToString();
        }

        private static StringBuilder ReadFile(string fileName)
        {
            StringBuilder fileText = new StringBuilder();
            try
            {
                using (StreamReader sr = new StreamReader(fileName))
                {
                    string line;
                    while ((line = sr.ReadLine()) != null)
                    {
                        fileText.AppendLine(line);
                    }
                }
            }
            catch (Exception)
            {
                fileText = null;
            }
            return fileText;
        }

        private static byte[] ReadBinaryFile(string fileName)
        {
            byte[] buffer = new byte[0];
            if (File.Exists(fileName))
            {
                buffer = File.ReadAllBytes(fileName);
            }
            return buffer;
        }

        private List<CyHidReportItem> ParseHIDFormat(byte[] byteArray)
        {
             if (byteArray.Length == 0)
                return null;

             List<CyHidReportItem> hidItemsList = new List<CyHidReportItem>();

            int headerLen = byteArray[0];
            int oneElemLen = 10;

            for (int i = headerLen; i <= byteArray.Length - oneElemLen; i += oneElemLen)
            {
                byte prefix = Convert.ToByte(byteArray[i]);

                string itemName = CyHidReportItem.GetNameByPrefix(prefix);
                if (string.IsNullOrEmpty(itemName))
                {
                    itemName = CyHidReportItem.RPTITEM_CUSTOM;
                }
                CyHidReportItem item = new CyHidReportItem(itemName);
                item.m_value.Add(prefix);
                for (int j = 1; j < item.GetItemSize(); j++)
                {
                    item.m_value.Add(byteArray[i + j]);
                }
                hidItemsList.Add(item);
            }

            return hidItemsList;
        }

        private List<CyHidReportItem> ParseDATFormat(string fileContent)
        {
            if (String.IsNullOrEmpty(fileContent))
                return null;

            string[] bytes = fileContent.Trim().Split(' ');
            byte[] byteArray = new byte[bytes.Length];
            for (int i = 0; i < bytes.Length; i++)
            {
                try
                {
                    byteArray[i] = Convert.ToByte(bytes[i].Trim(), 16);
                }
                catch
                {
                    Debug.Assert(false);
                    return null;
                }
            }

            return ParseByteArray(byteArray);
        }

        private List<CyHidReportItem> ParseHFormat(string fileContent)
        {
            if (String.IsNullOrEmpty(fileContent))
                return null;

            //Regex 
            const string COMMENT_PATTERN = @"(//.*)";
            const string ARRAY_CONTENT_PATTERN = @"\{([^\}]+)\}";
            const string HEX_BYTE_PATTERN = @"0x..";
            Regex rgxComment = new Regex(COMMENT_PATTERN);
            Regex rgxArray = new Regex(ARRAY_CONTENT_PATTERN);
            Regex rgxByte = new Regex(HEX_BYTE_PATTERN);

            // Remove comments
            fileContent = rgxComment.Replace(fileContent, "");

            List<byte> byteArray = new List<byte>();
            MatchCollection byteElements = rgxByte.Matches(fileContent);
            foreach (Match match in byteElements)
            {
                 try
                 {
                     byteArray.Add(Convert.ToByte(match.Value.Replace("0x", ""), 16));
                 }
                 catch
                 {
                     Debug.Assert(false);
                     return null;
                 }
            }

            return ParseByteArray(byteArray.ToArray());
        }

        private List<CyHidReportItem> ParseByteArray(byte[] byteArray)
        {
            List<CyHidReportItem> hidItemsList = new List<CyHidReportItem>();

            try
            {
                for (int i = 0; i < byteArray.Length; i++)
                {
                    byte prefix = Convert.ToByte(byteArray[i]);

                    string itemName = CyHidReportItem.GetNameByPrefix(prefix);
                    if (string.IsNullOrEmpty(itemName))
                    {
                        itemName = CyHidReportItem.RPTITEM_CUSTOM;
                    }
                    
                    CyHidReportItem item = new CyHidReportItem(itemName);
                    item.m_value.Add(prefix);
                    for (int j = 1; j < item.GetItemSize(); j++)
                    {
                        item.m_value.Add(byteArray[++i]);
                    }
                    hidItemsList.Add(item);
                }
            }
            catch
            {
                Debug.Assert(false);
                return null;
            }

            return hidItemsList;
        }

        #endregion Import Templates
    }

    //============================================================================================================

    #region Descriptor Template

    /// <summary>
    /// These classes are used for xml serialization of the templates
    /// </summary>

    [Serializable()]
    [XmlInclude(typeof(CyDeviceDescriptorTemplate))]
    [XmlInclude(typeof(CyConfigurationDescriptorTemplate))]
    [XmlInclude(typeof(CyIntAssociationDescriptorTemplate))]
    [XmlInclude(typeof(CyBosDescriptorTemplate))]
    [XmlInclude(typeof(CyUsb20ExtensionDeviceCapabilityDescriptorTemplate))]
    [XmlInclude(typeof(CyContainerIdDescriptorTemplate))]
    [XmlInclude(typeof(CyInterfaceDescriptorTemplate))]
    [XmlInclude(typeof(CyEndpointDescriptorTemplate))]
    [XmlInclude(typeof(CyHIDDescriptorTemplate))]
    [XmlInclude(typeof(CySerialStringDescriptorTemplate))]
    [XmlInclude(typeof(CyReportTemplate))]
    
    [XmlInclude(typeof(CyACHeaderDescriptorTemplate))]
    [XmlInclude(typeof(CyACInputTerminalDescriptorTemplate))]
    [XmlInclude(typeof(CyACOutputTerminalDescriptorTemplate))]
    [XmlInclude(typeof(CyACMixerUnitDescriptorTemplate))]
    [XmlInclude(typeof(CyACSelectorUnitDescriptorTemplate))]
    [XmlInclude(typeof(CyACFeatureUnitDescriptorTemplate))]
    [XmlInclude(typeof(CyACProcessingUnitDescriptorTemplate))]
    [XmlInclude(typeof(CyACExtensionDescriptorTemplate))]
    [XmlInclude(typeof(CyASGeneralDescriptorTemplate))]
    [XmlInclude(typeof(CyASFormatType1DescriptorTemplate))]
    [XmlInclude(typeof(CyASFormatType2DescriptorTemplate))]
    [XmlInclude(typeof(CyAudioEndpointDescriptorTemplate))]
    [XmlInclude(typeof(CyASEndpointDescriptorTemplate))]

    [XmlInclude(typeof(CyACHeaderDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACClockSourceDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACClockSelectorDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACClockMultiplierDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACInputTerminalDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACOutputTerminalDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACMixerUnitDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACSelectorUnitDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACFeatureUnitDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACProcessingUnitDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACExtensionDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACEffectUnitDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyACSRCDescriptorTemplate_v2))]
    [XmlInclude(typeof(CyASGeneralDescriptorTemplate_v2))]

    [XmlInclude(typeof(CyMSHeaderDescriptorTemplate))]
    [XmlInclude(typeof(CyMSInJackDescriptorTemplate))]
    [XmlInclude(typeof(CyMSOutJackDescriptorTemplate))]
    [XmlInclude(typeof(CyMSElementDescriptorTemplate))]
    [XmlInclude(typeof(CyMSEndpointDescriptorTemplate))]

    [XmlInclude(typeof(CyCDCHeaderDescriptorTemplate))]
    [XmlInclude(typeof(CyCDCUnionDescriptorTemplate))]
    [XmlInclude(typeof(CyCDCCountrySelectionDescriptorTemplate))]
    [XmlInclude(typeof(CyCDCCallManagementDescriptorTemplate))]
    [XmlInclude(typeof(CyCDCAbstractControlMgmtDescriptorTemplate))]

    [XmlInclude(typeof(CyEpMemoryManagementTemplate))]

    [XmlType("Descriptor")]
    public abstract class CyDescriptorTemplate
    {
        public abstract CyUSBDescriptor ConvertToUSBDesc();

        protected static string ByteToStr(byte n)
        {
            return "0x" + n.ToString("X2");
        }
        protected static string UshortToStr(ushort n)
        {
            return "0x" + n.ToString("X4");
        }
        protected static string UintToStr(uint n)
        {
            return "0x" + n.ToString("X8");
        }
        protected static string Byte3ToStr(uint n)
        {
            return "0x" + n.ToString("X6");
        }
        protected static string ByteArrayToStr(byte[] n)
        {
            StringBuilder res = new StringBuilder();
            if (n.Length > 0)
            {
                for (int i = 0; i < n.Length - 1; i++)
                {
                    res.Append("0x" + n[i].ToString("X2") + ", ");
                }
                res.Append("0x" + n[n.Length - 1].ToString("X2"));
            }
            return res.ToString();
        }
        protected static string UshortArrayToStr(ushort[] n)
        {
            StringBuilder res = new StringBuilder();
            if (n.Length > 0)
            {
                for (int i = 0; i < n.Length - 1; i++)
                {
                    res.Append("0x" + n[i].ToString("X4") + ", ");
                }
                res.Append("0x" + n[n.Length - 1].ToString("X4"));
            }
            return res.ToString();
        }
        protected static string Byte3ArrayToStr(uint[] n)
        {
            StringBuilder res = new StringBuilder();
            if (n.Length > 0)
            {
                for (int i = 0; i < n.Length - 1; i++)
                {
                    res.Append("0x" + n[i].ToString("X6") + ", ");
                }
                res.Append("0x" + n[n.Length - 1].ToString("X6"));
            }
            return res.ToString();
        }
        protected static string CustomArrayToStr(uint[] n, int num)
        {
            StringBuilder res = new StringBuilder();
            string format = "X" + (num*2).ToString();
            if (n.Length > 0)
            {
                for (int i = 0; i < n.Length - 1; i++)
                {
                    res.Append("0x" + n[i].ToString(format) + ", ");
                }
                res.Append("0x" + n[n.Length - 1].ToString(format));
            }
            return res.ToString();
        }

        public static byte StrToHex1B(string s)
        {
            byte res = 0;
            try
            {
                res = Convert.ToByte(s.Replace("0x", "").Trim(), 16);
            }
            catch
            {
                Debug.Assert(false);
            }
            return res;
        }
        protected static ushort StrToHex2B(string s)
        {
            ushort res = 0;
            try
            {
                res = Convert.ToUInt16(s.Replace("0x", "").Trim(), 16);
            }
            catch
            {
                Debug.Assert(false);
            }
            return res;
        }
        protected static uint StrToHex3B(string s)
        {
            uint res = 0;
            try
            {
                res = Convert.ToUInt32(s.Replace("0x", "").Trim(), 16);
            }
            catch
            {
                Debug.Assert(false);
            }
            return res;
        }
        protected static uint StrToHexInt(string s)
        {
            return StrToHex3B(s);
        }
        protected static byte[] StrToHex1BArray(string s)
        {
            List<byte> reslst = new List<byte>();
            if (!String.IsNullOrEmpty(s))
            {
                try
                {
                    string[] sres = s.Split(',');
                    for (int i = 0; i < sres.Length; i++)
                    {
                        reslst.Add(StrToHex1B(sres[i]));
                    }
                }
                catch
                {
                    Debug.Assert(false);
                }
            }
            return reslst.ToArray();
        }
        protected static ushort[] StrToHex2BArray(string s)
        {
            List<ushort> reslst = new List<ushort>();
            if (!String.IsNullOrEmpty(s))
            {
                try
                {
                    string[] sres = s.Split(',');
                    for (int i = 0; i < sres.Length; i++)
                    {
                        reslst.Add(StrToHex2B(sres[i]));
                    }
                }
                catch
                {
                    Debug.Assert(false);
                }
            }
            return reslst.ToArray();
        }
        protected static uint[] StrToHex3BArray(string s)
        {
            List<uint> reslst = new List<uint>();
            if (!String.IsNullOrEmpty(s))
            {
                try
                {
                    string[] sres = s.Split(',');
                    for (int i = 0; i < sres.Length; i++)
                    {
                        reslst.Add(StrToHex3B(sres[i]));
                    }
                }
                catch
                {
                    Debug.Assert(false);
                }
            }
            return reslst.ToArray();
        }
    }
    [XmlType("Device_Descriptor")]
    public class CyDeviceDescriptorTemplate : CyDescriptorTemplate
    {
        public string bDeviceClass;
        public string bDeviceSubClass;
        public string bDeviceProtocol;
        public string bMaxPacketSize0;
        public string idVendor;
        public string idProduct;
        public string iManufacturer;
        public string iProduct;
        public string iSerialNumber;
        public string bNumConfigurations;
        public string bcdDevice;
        public string bcdUSB;
        public string bMemoryMgmt;

        // This is only for serialization.
        public CyDeviceDescriptorTemplate()
        {
        }

        public CyDeviceDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bDeviceClass = ByteToStr(((CyDeviceDescriptor)usbDesc).bDeviceClass);
            bDeviceSubClass = ByteToStr(((CyDeviceDescriptor)usbDesc).bDeviceSubClass);
            bDeviceProtocol = ByteToStr(((CyDeviceDescriptor)usbDesc).bDeviceProtocol);
            bMaxPacketSize0 = ByteToStr(((CyDeviceDescriptor)usbDesc).bMaxPacketSize0);
            idVendor = UshortToStr(((CyDeviceDescriptor)usbDesc).idVendor);
            idProduct = UshortToStr(((CyDeviceDescriptor)usbDesc).idProduct);
            iManufacturer = ((CyDeviceDescriptor)usbDesc).sManufacturer;
            iProduct = ((CyDeviceDescriptor)usbDesc).sProduct;
            iSerialNumber = ((CyDeviceDescriptor)usbDesc).sSerialNumber;
            bNumConfigurations = ByteToStr(((CyDeviceDescriptor)usbDesc).bNumConfigurations);
            bcdDevice = UshortToStr(((CyDeviceDescriptor)usbDesc).bcdDevice);
            bcdUSB = UshortToStr(((CyDeviceDescriptor)usbDesc).bcdUSB);

            if (((CyDeviceDescriptor)usbDesc).bMemoryMgmt != 0)
                bMemoryMgmt = ByteToStr(((CyDeviceDescriptor)usbDesc).bMemoryMgmt);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyDeviceDescriptor usbDesc = new CyDeviceDescriptor();

            usbDesc.bDeviceClass = StrToHex1B(bDeviceClass);
            usbDesc.bDeviceSubClass = StrToHex1B(bDeviceSubClass);
            usbDesc.bDeviceProtocol = StrToHex1B(bDeviceProtocol);
            usbDesc.bMaxPacketSize0 = StrToHex1B(bMaxPacketSize0);
            usbDesc.idVendor = StrToHex2B(idVendor);
            usbDesc.idProduct = StrToHex2B(idProduct);
            usbDesc.sManufacturer = iManufacturer;
            usbDesc.sProduct = iProduct;
            usbDesc.sSerialNumber = iSerialNumber;
            usbDesc.bNumConfigurations = StrToHex1B(bNumConfigurations);
            usbDesc.bcdDevice = StrToHex2B(bcdDevice);
            usbDesc.bcdUSB = string.IsNullOrEmpty(bcdUSB) ? CyDeviceDescriptor.BCDUSB_WITHOUT_BOS : StrToHex2B(bcdUSB);
            if (bMemoryMgmt != null)
                usbDesc.bMemoryMgmt = StrToHex1B(bMemoryMgmt);

            return usbDesc;
        }
    }
    [XmlType("Configuration_Descriptor")]
    public class CyConfigurationDescriptorTemplate : CyDescriptorTemplate
    {
        public string wTotalLength;
        public string bNumInterfaces;
        public string bConfigurationValue;
        public string iConfiguration;
        public string bmAttributes;
        public string bMaxPower;

        // This is only for serialization.
        public CyConfigurationDescriptorTemplate()
        {
        }

        public CyConfigurationDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            wTotalLength = UshortToStr(((CyConfigDescriptor)usbDesc).wTotalLength);
            bNumInterfaces = ByteToStr(((CyConfigDescriptor)usbDesc).bNumInterfaces);
            bConfigurationValue = ByteToStr(((CyConfigDescriptor)usbDesc).bConfigurationValue);
            iConfiguration = ((CyConfigDescriptor)usbDesc).sConfiguration;
            bmAttributes = ByteToStr(((CyConfigDescriptor)usbDesc).bmAttributes);
            bMaxPower = ByteToStr(((CyConfigDescriptor)usbDesc).bMaxPower);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyConfigDescriptor usbDesc = new CyConfigDescriptor();

            usbDesc.wTotalLength = StrToHex2B(wTotalLength);
            usbDesc.bNumInterfaces = StrToHex1B(bNumInterfaces);
            usbDesc.bConfigurationValue = StrToHex1B(bConfigurationValue);
            usbDesc.sConfiguration = iConfiguration;
            usbDesc.bmAttributes = StrToHex1B(bmAttributes);
            usbDesc.bMaxPower = StrToHex1B(bMaxPower);
            return usbDesc;
        }
    }
    [XmlType("Interface_Descriptor")]
    public class CyInterfaceDescriptorTemplate : CyDescriptorTemplate
    {
        public string bInterfaceClass;
        public string bInterfaceSubClass;
        public string bAlternateSetting;
        public string bInterfaceNumber;
        public string bNumEndpoints;
        public string bInterfaceProtocol;
        public string iInterface;

        public string InterfaceDisplayName;

        // This is only for serialization.
        public CyInterfaceDescriptorTemplate()
        {
        }

        public CyInterfaceDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bInterfaceClass = ByteToStr(((CyInterfaceDescriptor)usbDesc).bInterfaceClass);
            bInterfaceSubClass = ByteToStr(((CyInterfaceDescriptor)usbDesc).bInterfaceSubClass);
            bAlternateSetting = ByteToStr(((CyInterfaceDescriptor)usbDesc).bAlternateSetting);
            bInterfaceNumber = ByteToStr(((CyInterfaceDescriptor)usbDesc).bInterfaceNumber);
            bNumEndpoints = ByteToStr(((CyInterfaceDescriptor)usbDesc).bNumEndpoints);
            bInterfaceProtocol = ByteToStr(((CyInterfaceDescriptor)usbDesc).bInterfaceProtocol);
            iInterface = ((CyInterfaceDescriptor)usbDesc).sInterface;
            InterfaceDisplayName = ((CyInterfaceDescriptor)usbDesc).InterfaceDisplayName;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyInterfaceDescriptor usbDesc;
            if (StrToHex1B(bInterfaceClass) == (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_AUDIO)
                usbDesc  = new CyAudioInterfaceDescriptor();
            else if (StrToHex1B(bInterfaceClass) == (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC)
                usbDesc = new CyCommunicationsInterfaceDescriptor();
            else if (StrToHex1B(bInterfaceClass) == (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_MASS_STORAGE)
                usbDesc = new CyMscInterfaceDescriptor();
            else if (StrToHex1B(bInterfaceClass) == (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_DATA)
                usbDesc = new CyDataInterfaceDescriptor();
            else
                usbDesc = new CyInterfaceDescriptor();

            usbDesc.bInterfaceClass = StrToHex1B(bInterfaceClass);
            usbDesc.bInterfaceSubClass = StrToHex1B(bInterfaceSubClass);
            usbDesc.bAlternateSetting = StrToHex1B(bAlternateSetting);
            usbDesc.bInterfaceNumber = StrToHex1B(bInterfaceNumber);
            usbDesc.bNumEndpoints = StrToHex1B(bNumEndpoints);
            usbDesc.bInterfaceProtocol = StrToHex1B(bInterfaceProtocol);
            usbDesc.sInterface = iInterface;
            usbDesc.InterfaceDisplayName = InterfaceDisplayName;

            return usbDesc;
        }
    }

    [XmlType("Interface_Association_Descriptor")]
    public class CyIntAssociationDescriptorTemplate : CyDescriptorTemplate
    {
        public string bFirstInterface;
        public string bInterfaceCount;
        public string bFunctionClass;
        public string bFunctionSubClass;
        public string bFunctionProtocol;
        public string iFunction;

        // This is only for serialization.
        public CyIntAssociationDescriptorTemplate()
        {
        }

        public CyIntAssociationDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bFirstInterface = ByteToStr(((CyInterfaceAssociationDescriptor)usbDesc).bFirstInterface);
            bInterfaceCount = ByteToStr(((CyInterfaceAssociationDescriptor)usbDesc).bInterfaceCount);
            bFunctionClass = ByteToStr(((CyInterfaceAssociationDescriptor)usbDesc).bFunctionClass);
            bFunctionSubClass = ByteToStr(((CyInterfaceAssociationDescriptor)usbDesc).bFunctionSubClass);
            bFunctionProtocol = ByteToStr(((CyInterfaceAssociationDescriptor)usbDesc).bFunctionProtocol);
            iFunction = ((CyInterfaceAssociationDescriptor)usbDesc).sFunction;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyInterfaceAssociationDescriptor usbDesc = new CyInterfaceAssociationDescriptor();
            usbDesc.bFunctionClass = StrToHex1B(bFunctionClass);
            usbDesc.bFunctionSubClass = StrToHex1B(bFunctionSubClass);
            usbDesc.bFirstInterface = StrToHex1B(bFirstInterface);
            usbDesc.bInterfaceCount = StrToHex1B(bInterfaceCount);
            usbDesc.bFunctionProtocol = StrToHex1B(bFunctionProtocol);
            usbDesc.sFunction = iFunction;

            return usbDesc;
        }
    }

    [XmlType("BOS_Descriptor")]
    public class CyBosDescriptorTemplate : CyDescriptorTemplate
    {
        public string wTotalLength;
        public string bNumDeviceCaps;

        // This is only for serialization.
        public CyBosDescriptorTemplate()
        {
        }

        public CyBosDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bNumDeviceCaps = ByteToStr(((CyBosDescriptor)usbDesc).bNumDeviceCaps);
            wTotalLength = UshortToStr(((CyBosDescriptor)usbDesc).wTotalLength);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyBosDescriptor usbDesc = new CyBosDescriptor();
            usbDesc.bNumDeviceCaps = StrToHex1B(bNumDeviceCaps);
            usbDesc.wTotalLength = StrToHex2B(wTotalLength);

            return usbDesc;
        }
    }

    [XmlType("USB20_Extension_Device_Capability_Descriptor")]
    public class CyUsb20ExtensionDeviceCapabilityDescriptorTemplate : CyDescriptorTemplate
    {
        public string bDevCapabilityType;
        public string bmAttributes;

        // This is only for serialization.
        public CyUsb20ExtensionDeviceCapabilityDescriptorTemplate()
        {
        }

        public CyUsb20ExtensionDeviceCapabilityDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bDevCapabilityType = ByteToStr(((CyUsb20ExtensionDeviceCapabilityDescriptor)usbDesc).bDevCapabilityType);
            bmAttributes = UintToStr(((CyUsb20ExtensionDeviceCapabilityDescriptor)usbDesc).bmAttributes);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyUsb20ExtensionDeviceCapabilityDescriptor usbDesc = new CyUsb20ExtensionDeviceCapabilityDescriptor();
            usbDesc.bDevCapabilityType = StrToHex1B(bDevCapabilityType);
            usbDesc.bmAttributes = StrToHexInt(bmAttributes);

            return usbDesc;
        }
    }

    [XmlType("Container_ID_Descriptor")]
    public class CyContainerIdDescriptorTemplate : CyDescriptorTemplate
    {
        public string bDevCapabilityType;
        public string ContainerId;

        // This is only for serialization.
        public CyContainerIdDescriptorTemplate()
        {
        }

        public CyContainerIdDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bDevCapabilityType = ByteToStr(((CyContainerIdDescriptor)usbDesc).bDevCapabilityType);
            ContainerId = ((CyContainerIdDescriptor)usbDesc).ContainerId;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyContainerIdDescriptor usbDesc = new CyContainerIdDescriptor();
            usbDesc.bDevCapabilityType = StrToHex1B(bDevCapabilityType);
            usbDesc.ContainerId = ContainerId;

            return usbDesc;
        }
    }

    [XmlType("Endpoint_Descriptor")]
    public class CyEndpointDescriptorTemplate : CyDescriptorTemplate
    {
        public string bInterval;
        public string bEndpointAddress;
        public string bmAttributes;
        public string wMaxPacketSize;

        // This is only for serialization.
        public CyEndpointDescriptorTemplate()
        {
        }

        public CyEndpointDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bInterval = ByteToStr(((CyEndpointDescriptor)usbDesc).bInterval);
            bEndpointAddress = ByteToStr(((CyEndpointDescriptor)usbDesc).bEndpointAddress);
            bmAttributes = ByteToStr(((CyEndpointDescriptor)usbDesc).bmAttributes);
            wMaxPacketSize = UshortToStr(((CyEndpointDescriptor)usbDesc).wMaxPacketSize);

        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyEndpointDescriptor usbDesc = new CyEndpointDescriptor();

            usbDesc.bInterval = StrToHex1B(bInterval);
            usbDesc.bEndpointAddress = StrToHex1B(bEndpointAddress);
            usbDesc.bmAttributes = StrToHex1B(bmAttributes);
            usbDesc.wMaxPacketSize = StrToHex2B(wMaxPacketSize);

            return usbDesc;
        }
    }

    [XmlType("HID_Descriptor")]
    public class CyHIDDescriptorTemplate : CyDescriptorTemplate
    {
        public string bcdHID;
        public string bCountryCode;
        public string bNumDescriptors;
        public string bDescriptorType;
        public string wDescriptorLength;

        // This is only for serialization.
        public CyHIDDescriptorTemplate()
        {
        }

        public CyHIDDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bcdHID = UshortToStr(((CyHIDDescriptor)usbDesc).bcdHID);
            bCountryCode = ByteToStr(((CyHIDDescriptor)usbDesc).bCountryCode);
            bNumDescriptors = ByteToStr(((CyHIDDescriptor)usbDesc).bNumDescriptors);
            bDescriptorType = ByteToStr(((CyHIDDescriptor)usbDesc).bDescriptorType1);
            wDescriptorLength = UshortToStr(((CyHIDDescriptor)usbDesc).wDescriptorLength);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyHIDDescriptor usbDesc = new CyHIDDescriptor();

            usbDesc.bcdHID = StrToHex2B(bcdHID);
            usbDesc.bCountryCode = StrToHex1B(bCountryCode);
            usbDesc.bNumDescriptors = StrToHex1B(bNumDescriptors);
            usbDesc.bDescriptorType1 = StrToHex1B(bDescriptorType);
            usbDesc.wDescriptorLength = StrToHex2B(wDescriptorLength);

            return usbDesc;
        }
    }

    [XmlType("Serial_Descriptor")]
    public class CySerialStringDescriptorTemplate : CyDescriptorTemplate
    {
        public string bString;
        public bool bUsed;
        public CyStringGenerationType snType;

        // This is only for serialization.
        public CySerialStringDescriptorTemplate()
        {
        }

        public CySerialStringDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bString = ((CyStringDescriptor)usbDesc).bString;
            bUsed = ((CyStringDescriptor)usbDesc).bUsed;
            snType = ((CyStringDescriptor)usbDesc).snType;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyStringDescriptor usbDesc = new CyStringDescriptor();

            usbDesc.bString = bString;
            usbDesc.bUsed = bUsed;
            usbDesc.snType = snType;

            return usbDesc;
        }
    }

    #endregion Descriptor Template

    //============================================================================================================

    #region Report Template

    /// <summary>
    /// Used for saving and importing HID reports.
    /// </summary>
    [XmlRoot("HID_Report")]
    [XmlType("ReportTemplate")]
    public class CyReportTemplate : CyDescriptorTemplate
    {
        [XmlAttribute("Report_Name")]
        public string m_reportName;
        [XmlArray("Items")]
        [XmlArrayItem("HID_Item")]
        public List<CyReportTemplateItem> m_items;

        public CyReportTemplate()
        {
            m_items = new List<CyReportTemplateItem>();
        }

        public CyReportTemplate(CyDescriptorNode node_report)
        {
            m_reportName = ((CyHIDReportDescriptor)node_report.Value).Name;
            m_items = new List<CyReportTemplateItem>();
            for (int j = 0; j < node_report.Nodes.Count; j++)
            {
                CyHidReportItem item =
                    ((CyHIDReportItemDescriptor)node_report.Nodes[j].Value).Item;
                List<byte> byteList = new List<byte>(item.m_value);
                if (byteList.Count > 0)
                    byteList.RemoveAt(0);
                long val = 0;
                if ((item.Kind == CyHidReportItemKind.INT) || (item.Kind == CyHidReportItemKind.CUSTOM))
                {
                    val = CyUSBFSParameters.ConvertByteArrayToInt(byteList, item.IsUnsigned());
                }
                else
                {
                    if (BitConverter.IsLittleEndian)
                    {
                        for (int k = 1; k < item.m_value.Count; k++)
                        {
                            val += item.m_value[k] << (k - 1) * 8;
                        }
                    }
                    else
                    {
                        for (int k = 1; k < item.m_value.Count; k++)
                        {
                            val += item.m_value[k] << (item.m_value.Count - k - 1) * 8;
                        }
                    }
                }
                m_items.Add(new CyReportTemplateItem(item.Name, item.m_prefix, item.GetSizeBitValue(), val, 
                                                     item.m_description));
            }
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyHIDReportDescriptor usbDesc = new CyHIDReportDescriptor();
            //Report name
            usbDesc.Name = m_reportName;
            //Items
            for (int i = 0; i < m_items.Count; i++)
            {
                CyHidReportItem item = m_items[i].ConvertToHidReportItem();
            }
            return usbDesc;
        }
    }

    /// <summary>
    /// Used for saving and importing HID report items.
    /// </summary>
    [XmlType("ReportTemplateItem")]
    public class CyReportTemplateItem 
    {
        [XmlAttribute("Type")]
        public string m_type;
        [XmlAttribute("Code")]
        public int m_code;
        [XmlAttribute("Size")]
        public int m_size;
        [XmlAttribute("Value")]
        public long m_value;
        [XmlAttribute("Desc")]
        public string m_description;

        public CyReportTemplateItem()
        {
        }

        public CyReportTemplateItem(string type, int code, int size, long value, string description)
        {
            m_type = type;
            m_code = code;
            m_size = size;
            m_value = value;
            m_description = description;
        }

        public CyHidReportItem ConvertToHidReportItem()
        {
            CyHidReportItem item = new CyHidReportItem(m_type, (byte)m_code, (byte)m_size, m_value, m_description);
            return item;
        }
    }

    #endregion Report Template

    //============================================================================================================

    #region Audio Template

    [XmlType("ACHeader_Descriptor")]
    public class CyACHeaderDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bcdADC;
        public string wTotalLength;
        public string bInCollection;
        public string baInterfaceNr;

        public CyACHeaderDescriptorTemplate()
        {
        }

        public CyACHeaderDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACHeaderDescriptor desc = (CyACHeaderDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bcdADC = UshortToStr(desc.bcdADC);
            wTotalLength = UshortToStr(desc.wTotalLength);
            bInCollection = ByteToStr(desc.bInCollection);
            baInterfaceNr = ByteArrayToStr(desc.baInterfaceNr);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACHeaderDescriptor usbDesc = new CyACHeaderDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bcdADC = StrToHex2B(bcdADC);
            usbDesc.wTotalLength = StrToHex2B(wTotalLength);
            usbDesc.bInCollection = StrToHex1B(bInCollection);
            usbDesc.baInterfaceNr = StrToHex1BArray(baInterfaceNr);
            return usbDesc;
        }
    }

    [XmlType("ACInputTerminal_Descriptor")]
    public class CyACInputTerminalDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bTerminalID;
        public string wTerminalType;
        public string bAssocTerminal;
        public string bNrChannels;
        public string wChannelConfig;
        public string iChannelNames;
        public string iTerminal;

        public CyACInputTerminalDescriptorTemplate()
        {
        }

        public CyACInputTerminalDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACInputTerminalDescriptor desc = (CyACInputTerminalDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bTerminalID = ByteToStr(desc.bTerminalID);
            wTerminalType = UshortToStr(desc.wTerminalType);
            bAssocTerminal = ByteToStr(desc.bAssocTerminal);
            bNrChannels = ByteToStr(desc.bNrChannels);
            wChannelConfig = UshortToStr(desc.wChannelConfig);
            iChannelNames = desc.sChannelNames;
            iTerminal = desc.sTerminal;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACInputTerminalDescriptor usbDesc = new CyACInputTerminalDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bTerminalID = StrToHex1B(bTerminalID);
            usbDesc.wTerminalType = StrToHex2B(wTerminalType);
            usbDesc.bAssocTerminal = StrToHex1B(bAssocTerminal);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.wChannelConfig = StrToHex2B(wChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.sTerminal = iTerminal;
            return usbDesc;
        }
    }

    [XmlType("ACOutputTerminalDescriptor_Descriptor")]
    public class CyACOutputTerminalDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bTerminalID;
        public string wTerminalType;
        public string bAssocTerminal;
        public string bSourceID;
        public string iTerminal;

        public CyACOutputTerminalDescriptorTemplate()
        {
        }

        public CyACOutputTerminalDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACOutputTerminalDescriptor desc = (CyACOutputTerminalDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bTerminalID = ByteToStr(desc.bTerminalID);
            wTerminalType = UshortToStr(desc.wTerminalType);
            bAssocTerminal = ByteToStr(desc.bAssocTerminal);
            bSourceID = ByteToStr(desc.bSourceID);
            iTerminal = desc.sTerminal;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACOutputTerminalDescriptor usbDesc = new CyACOutputTerminalDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bTerminalID = StrToHex1B(bTerminalID);
            usbDesc.wTerminalType = StrToHex2B(wTerminalType);
            usbDesc.bAssocTerminal = StrToHex1B(bAssocTerminal);
            usbDesc.bSourceID = StrToHex1B(bSourceID);
            usbDesc.sTerminal = iTerminal;           
            return usbDesc;
        }
    }

    [XmlType("ACMixerUnitDescriptor_Descriptor")]
    public class CyACMixerUnitDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bUnitID;
        public string bNrInPins;
        public string baSourceID;
        public string bNrChannels;
        public string wChannelConfig;
        public string iChannelNames;
        public string bmControls;
        public string iMixer;

        public CyACMixerUnitDescriptorTemplate()
        {
        }

        public CyACMixerUnitDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACMixerUnitDescriptor desc = (CyACMixerUnitDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            bNrChannels = ByteToStr(desc.bNrChannels);
            wChannelConfig = UshortToStr(desc.wChannelConfig);
            iChannelNames = desc.sChannelNames;
            bmControls = ByteArrayToStr(desc.bmControls.ToArray());
            iMixer = desc.sMixer;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACMixerUnitDescriptor usbDesc = new CyACMixerUnitDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.wChannelConfig = StrToHex2B(wChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.bmControls = new List<byte>(StrToHex1BArray(bmControls));
            usbDesc.sMixer = iMixer;
            return usbDesc;
        }
    }

    [XmlType("ACSelectorUnit_Descriptor")]
    public class CyACSelectorUnitDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bUnitID;
        public string bNrInPins;
        public string baSourceID;
        public string iSelector;

        public CyACSelectorUnitDescriptorTemplate()
        {
        }

        public CyACSelectorUnitDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACSelectorUnitDescriptor desc = (CyACSelectorUnitDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            iSelector = desc.sSelector;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACSelectorUnitDescriptor usbDesc = new CyACSelectorUnitDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.sSelector = iSelector;
            return usbDesc;
        }
    }

    [XmlType("ACFeatureUnit_Descriptor")]
    public class CyACFeatureUnitDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bUnitID;
        public string bSourceID;
        public string bControlSize;
        public string bmaControls;
        public string iFeature;

        public CyACFeatureUnitDescriptorTemplate()
        {
        }

        public CyACFeatureUnitDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACFeatureUnitDescriptor desc = (CyACFeatureUnitDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            bSourceID = ByteToStr(desc.bSourceID);
            bControlSize = ByteToStr(desc.bControlSize);
            bmaControls = CustomArrayToStr(desc.bmaControls, desc.bControlSize);
            iFeature = desc.sFeature;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACFeatureUnitDescriptor usbDesc = new CyACFeatureUnitDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.bSourceID = StrToHex1B(bSourceID);
            usbDesc.bControlSize = StrToHex1B(bControlSize);
            usbDesc.bmaControls = StrToHex3BArray(bmaControls);
            usbDesc.sFeature = iFeature;
            return usbDesc;
        }
    }

    [XmlType("ACProcessingUnit_Descriptor")]
    public class CyACProcessingUnitDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bUnitID;
        public string wProcessType;
        public string bNrInPins;
        public string baSourceID;
        public string bNrChannels;
        public string wChannelConfig;
        public string iChannelNames;
        public string bControlSize;
        public string bmControls;
        public string iProcessing;

        public CyACProcessingUnitDescriptorTemplate()
        {
        }

        public CyACProcessingUnitDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACProcessingUnitDescriptor desc = (CyACProcessingUnitDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            wProcessType = UshortToStr(desc.wProcessType);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            bNrChannels = ByteToStr(desc.bNrChannels);
            wChannelConfig = UshortToStr(desc.wChannelConfig);
            iChannelNames = desc.sChannelNames;
            bControlSize = ByteToStr(desc.bControlSize);
            bmControls = ByteArrayToStr(desc.bmControls);
            iProcessing = desc.sProcessing;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACProcessingUnitDescriptor usbDesc = new CyACProcessingUnitDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.wProcessType = StrToHex2B(wProcessType);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.wChannelConfig = StrToHex2B(wChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.bControlSize = StrToHex1B(bControlSize);
            usbDesc.bmControls = StrToHex1BArray(bmControls);
            usbDesc.sProcessing = iProcessing;
            return usbDesc;
        }
    }

    [XmlType("ACExtension_Descriptor")]
    public class CyACExtensionDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bUnitID;
        public string wExtensionCode;
        public string bNrInPins;
        public string baSourceID;
        public string bNrChannels;
        public string wChannelConfig;
        public string iChannelNames;
        public string bControlSize;
        public string bmControls;
        public string iExtension;


        public CyACExtensionDescriptorTemplate()
        {
        }

        public CyACExtensionDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyACExtensionDescriptor desc = (CyACExtensionDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            wExtensionCode = UshortToStr(desc.wExtensionCode);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            bNrChannels = ByteToStr(desc.bNrChannels);
            wChannelConfig = UshortToStr(desc.wChannelConfig);
            iChannelNames = desc.sChannelNames;
            bControlSize = ByteToStr(desc.bControlSize);
            bmControls = ByteArrayToStr(desc.bmControls);
            iExtension = desc.sExtension;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACExtensionDescriptor usbDesc = new CyACExtensionDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.wExtensionCode = StrToHex2B(wExtensionCode);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.wChannelConfig = StrToHex2B(wChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.bControlSize = StrToHex1B(bControlSize);
            usbDesc.bmControls = StrToHex1BArray(bmControls);
            usbDesc.sExtension = iExtension;

            return usbDesc;
        }
    }

    [XmlType("ASGeneral_Descriptor")]
    public class CyASGeneralDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyASInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bTerminalLink;
        public string bDelay;
        public string wFormatTag;

        public CyASGeneralDescriptorTemplate()
        {
        }

        public CyASGeneralDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyASGeneralDescriptor desc = (CyASGeneralDescriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bTerminalLink = ByteToStr(desc.bTerminalLink);
            bDelay = ByteToStr(desc.bDelay);
            wFormatTag = UshortToStr(desc.wFormatTag);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyASGeneralDescriptor usbDesc = new CyASGeneralDescriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bTerminalLink = StrToHex1B(bTerminalLink);
            usbDesc.bDelay = StrToHex1B(bDelay);
            usbDesc.wFormatTag = StrToHex2B(wFormatTag);
            return usbDesc;
        }
    }

    [XmlType("CyASFormatType1_Descriptor")]
    public class CyASFormatType1DescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyASInterfaceDescriptorSubtypes bDescriptorSubtype;
        public CyUSBOtherTypes.CyFormatTypeCodes bFormatType;
        public string bNrChannels;
        public string bSubframeSize;
        public string bBitResolution;
        public string bSamFreqType;
        public string tLowerSamFreq;
        public string tUpperSamFreq;
        public string tSamFreq;

        public CyASFormatType1DescriptorTemplate()
        {
        }

        public CyASFormatType1DescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyASFormatType1Descriptor desc = (CyASFormatType1Descriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bNrChannels = ByteToStr(desc.bNrChannels);
            bSubframeSize = ByteToStr(desc.bSubframeSize);
            bBitResolution = ByteToStr(desc.bBitResolution);
            bSamFreqType = ByteToStr(desc.bSamFreqType);
            tLowerSamFreq = Byte3ToStr(desc.tLowerSamFreq); 
            tUpperSamFreq = Byte3ToStr(desc.tUpperSamFreq); 
            tSamFreq = Byte3ArrayToStr(desc.tSamFreq);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyASFormatType1Descriptor usbDesc = new CyASFormatType1Descriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.bSubframeSize = StrToHex1B(bSubframeSize);
            usbDesc.bBitResolution = StrToHex1B(bBitResolution);
            usbDesc.bSamFreqType = StrToHex1B(bSamFreqType);
            usbDesc.tLowerSamFreq = StrToHex3B(tLowerSamFreq);
            usbDesc.tUpperSamFreq = StrToHex3B(tUpperSamFreq);
            usbDesc.tSamFreq = StrToHex3BArray(tSamFreq);
            return usbDesc;
        }
    }

    [XmlType("CyASFormatType2_Descriptor")]
    public class CyASFormatType2DescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyASInterfaceDescriptorSubtypes bDescriptorSubtype;
        public CyUSBOtherTypes.CyFormatTypeCodes bFormatType;
        public string wMaxBitRate;
        public string wSamplesPerFrame;
        public string bSamFreqType;
        public string tLowerSamFreq;
        public string tUpperSamFreq;
        public string tSamFreq;

        public CyASFormatType2DescriptorTemplate()
        {
        }

        public CyASFormatType2DescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyASFormatType2Descriptor desc = (CyASFormatType2Descriptor)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            wMaxBitRate = UshortToStr(desc.wMaxBitRate);
            wSamplesPerFrame = UshortToStr(desc.wSamplesPerFrame);
            bSamFreqType = ByteToStr(desc.bSamFreqType);
            tLowerSamFreq = Byte3ToStr(desc.tLowerSamFreq);
            tUpperSamFreq = Byte3ToStr(desc.tUpperSamFreq); 
            tSamFreq = Byte3ArrayToStr(desc.tSamFreq);

        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyASFormatType2Descriptor usbDesc = new CyASFormatType2Descriptor();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.wMaxBitRate = StrToHex2B(wMaxBitRate);
            usbDesc.wSamplesPerFrame = StrToHex2B(wSamplesPerFrame);
            usbDesc.bSamFreqType = StrToHex1B(bSamFreqType);
            usbDesc.tLowerSamFreq = StrToHex3B(tLowerSamFreq);
            usbDesc.tUpperSamFreq = StrToHex3B(tUpperSamFreq);
            usbDesc.tSamFreq = StrToHex3BArray(tSamFreq);
            return usbDesc;
        }
    }

    [XmlType("AudioEndpoint_Descriptor")]
    public class CyAudioEndpointDescriptorTemplate : CyDescriptorTemplate
    {
        public string bInterval;
        public string bEndpointAddress;
        public string bmAttributes;
        public string wMaxPacketSize;
        public string bRefresh;
        public string bSynchAddress;


        public CyAudioEndpointDescriptorTemplate()
        {
        }

        public CyAudioEndpointDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bInterval = ByteToStr(((CyAudioEndpointDescriptor)usbDesc).bInterval);
            bEndpointAddress = ByteToStr(((CyAudioEndpointDescriptor)usbDesc).bEndpointAddress);
            bmAttributes = ByteToStr(((CyAudioEndpointDescriptor)usbDesc).bmAttributes);
            wMaxPacketSize = UshortToStr(((CyAudioEndpointDescriptor)usbDesc).wMaxPacketSize);
            bRefresh = ByteToStr(((CyAudioEndpointDescriptor)usbDesc).bRefresh);
            bSynchAddress = ByteToStr(((CyAudioEndpointDescriptor)usbDesc).bSynchAddress);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyAudioEndpointDescriptor usbDesc = new CyAudioEndpointDescriptor();

            usbDesc.bInterval = StrToHex1B(bInterval);
            usbDesc.bEndpointAddress = StrToHex1B(bEndpointAddress);
            usbDesc.bmAttributes = StrToHex1B(bmAttributes);
            usbDesc.wMaxPacketSize = StrToHex2B(wMaxPacketSize);
            usbDesc.bInterval = StrToHex1B(bInterval);
            usbDesc.bRefresh = StrToHex1B(bRefresh);
            usbDesc.bSynchAddress = StrToHex1B(bSynchAddress);

            return usbDesc;
        }
    }

    [XmlType("ASEndpoint_Descriptor")]
    public class CyASEndpointDescriptorTemplate : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyAudioClassSpecEPDescriptorTypes bDescriptorSubtype;
        public string bmAttributes;
        public string bLockDelayUnits;
        public string wLockDelay;


        public CyASEndpointDescriptorTemplate()
        {
        }

        public CyASEndpointDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            bDescriptorSubtype = ((CyASEndpointDescriptor) usbDesc).bDescriptorSubtype;
            bmAttributes = ByteToStr(((CyASEndpointDescriptor)usbDesc).bmAttributes);
            bLockDelayUnits = ByteToStr(((CyASEndpointDescriptor)usbDesc).bLockDelayUnits);
            wLockDelay = UshortToStr(((CyASEndpointDescriptor)usbDesc).wLockDelay);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyASEndpointDescriptor usbDesc = new CyASEndpointDescriptor();

            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bmAttributes = StrToHex1B(bmAttributes);
            usbDesc.bLockDelayUnits = StrToHex1B(bLockDelayUnits);
            usbDesc.wLockDelay = StrToHex2B(wLockDelay);

            return usbDesc;
        }
    }

    #endregion Audio Template

    //============================================================================================================

    #region Audio 2.0 Template

    [XmlType("ACHeader_v2_Descriptor")]
    public class CyACHeaderDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bcdADC;
        public string bCategory;
        public string wTotalLength;
        public string bmControls;

        public CyACHeaderDescriptorTemplate_v2()
        {
        }

        public CyACHeaderDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACHeaderDescriptor_v2 desc = (CyACHeaderDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bcdADC = UshortToStr(desc.bcdADC);
            bCategory = ByteToStr(desc.bCategory);
            wTotalLength = UshortToStr(desc.wTotalLength);
            bmControls = ByteToStr(desc.bmControls);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACHeaderDescriptor_v2 usbDesc = new CyACHeaderDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bcdADC = StrToHex2B(bcdADC);
            usbDesc.bCategory = StrToHex1B(bCategory);
            usbDesc.wTotalLength = StrToHex2B(wTotalLength);
            usbDesc.bmControls = StrToHex1B(bmControls);
            return usbDesc;
        }
    }

    [XmlType("ACClockSource_v2_Descriptor")]
    public class CyACClockSourceDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bClockID;
        public string bmAttributes;
        public string bmControls;
        public string bAssocTerminal;
        public string iClockSource;

        public CyACClockSourceDescriptorTemplate_v2()
        {
        }

        public CyACClockSourceDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACClockSourceDescriptor_v2 desc = (CyACClockSourceDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bClockID = ByteToStr(desc.bClockID);
            bmAttributes = ByteToStr(desc.bmAttributes);
            bmControls = ByteToStr(desc.bmControls);
            bAssocTerminal = ByteToStr(desc.bAssocTerminal);
            iClockSource = desc.sClockSource;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACClockSourceDescriptor_v2 usbDesc = new CyACClockSourceDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bClockID = StrToHex1B(bClockID);
            usbDesc.bmAttributes = StrToHex1B(bmAttributes);
            usbDesc.bmControls = StrToHex1B(bmControls);
            usbDesc.bAssocTerminal = StrToHex1B(bAssocTerminal);
            usbDesc.sClockSource = iClockSource;
            return usbDesc;
        }
    }

    [XmlType("ACClockSelector_v2_Descriptor")]
    public class CyACClockSelectorDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bClockID;
        public string bNrInPins;
        public string baCSourceID;
        public string bmControls;
        public string iClockSelector;

        public CyACClockSelectorDescriptorTemplate_v2()
        {
        }

        public CyACClockSelectorDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACClockSelectorDescriptor_v2 desc = (CyACClockSelectorDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bClockID = ByteToStr(desc.bClockID);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baCSourceID = ByteArrayToStr(desc.baCSourceID);            
            bmControls = ByteToStr(desc.bmControls);
            iClockSelector = desc.sClockSelector;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACClockSelectorDescriptor_v2 usbDesc = new CyACClockSelectorDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bClockID = StrToHex1B(bClockID);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baCSourceID = StrToHex1BArray(baCSourceID);            
            usbDesc.bmControls = StrToHex1B(bmControls);
            usbDesc.sClockSelector = iClockSelector;
            return usbDesc;
        }
    }

    [XmlType("ACClockMultiplier_v2_Descriptor")]
    public class CyACClockMultiplierDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bClockID;
        public string bCSourceID;
        public string bmControls;
        public string iClockMultiplier;

        public CyACClockMultiplierDescriptorTemplate_v2()
        {
        }

        public CyACClockMultiplierDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACClockMultiplierDescriptor_v2 desc = (CyACClockMultiplierDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bClockID = ByteToStr(desc.bClockID);
            bCSourceID = ByteToStr(desc.bCSourceID);
            bmControls = ByteToStr(desc.bmControls);
            iClockMultiplier = desc.sClockMultiplier;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACClockMultiplierDescriptor_v2 usbDesc = new CyACClockMultiplierDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bClockID = StrToHex1B(bClockID);
            usbDesc.bCSourceID = StrToHex1B(bCSourceID);
            usbDesc.bmControls = StrToHex1B(bmControls);
            usbDesc.sClockMultiplier = iClockMultiplier;
            return usbDesc;
        }
    }

    [XmlType("ACInputTerminal_v2_Descriptor")]
    public class CyACInputTerminalDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bTerminalID;
        public string wTerminalType;
        public string bAssocTerminal;
        public string bCSourceID;
        public string bNrChannels;
        public string bmChannelConfig;
        public string iChannelNames;
        public string bmControls;
        public string iTerminal;

        public CyACInputTerminalDescriptorTemplate_v2()
        {
        }

        public CyACInputTerminalDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACInputTerminalDescriptor_v2 desc = (CyACInputTerminalDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bTerminalID = ByteToStr(desc.bTerminalID);
            wTerminalType = UshortToStr(desc.wTerminalType);
            bAssocTerminal = ByteToStr(desc.bAssocTerminal);
            bCSourceID = ByteToStr(desc.bCSourceID);
            bNrChannels = ByteToStr(desc.bNrChannels);
            bmChannelConfig = UintToStr(desc.bmChannelConfig);
            iChannelNames = desc.sChannelNames;
            bmControls = UshortToStr(desc.bmControls);
            iTerminal = desc.sTerminal;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACInputTerminalDescriptor_v2 usbDesc = new CyACInputTerminalDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bTerminalID = StrToHex1B(bTerminalID);
            usbDesc.wTerminalType = StrToHex2B(wTerminalType);
            usbDesc.bAssocTerminal = StrToHex1B(bAssocTerminal);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.bmChannelConfig = StrToHexInt(bmChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.sTerminal = iTerminal;
            return usbDesc;
        }
    }

    [XmlType("ACOutputTerminalDescriptor_v2_Descriptor")]
    public class CyACOutputTerminalDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bTerminalID;
        public string wTerminalType;
        public string bAssocTerminal;
        public string bSourceID;
        public string bCSourceID;
        public string bmControls;
        public string iTerminal;

        public CyACOutputTerminalDescriptorTemplate_v2()
        {
        }

        public CyACOutputTerminalDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACOutputTerminalDescriptor_v2 desc = (CyACOutputTerminalDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bTerminalID = ByteToStr(desc.bTerminalID);
            wTerminalType = UshortToStr(desc.wTerminalType);
            bAssocTerminal = ByteToStr(desc.bAssocTerminal);
            bSourceID = ByteToStr(desc.bSourceID);
            bCSourceID = ByteToStr(desc.bCSourceID);
            bmControls = UshortToStr(desc.bmControls);
            iTerminal = desc.sTerminal;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACOutputTerminalDescriptor_v2 usbDesc = new CyACOutputTerminalDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bTerminalID = StrToHex1B(bTerminalID);
            usbDesc.wTerminalType = StrToHex2B(wTerminalType);
            usbDesc.bAssocTerminal = StrToHex1B(bAssocTerminal);
            usbDesc.bSourceID = StrToHex1B(bSourceID);
            usbDesc.bCSourceID = StrToHex1B(bCSourceID);
            usbDesc.bmControls = StrToHex2B(bmControls);
            usbDesc.sTerminal = iTerminal;
            return usbDesc;
        }
    }

    [XmlType("ACMixerUnitDescriptor_v2_Descriptor")]
    public class CyACMixerUnitDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bUnitID;
        public string bNrInPins;
        public string baSourceID;
        public string bNrChannels;
        public string bmChannelConfig;
        public string iChannelNames;
        public string bmMixerControls;
        public string bmControls;
        public string iMixer;

        public CyACMixerUnitDescriptorTemplate_v2()
        {
        }

        public CyACMixerUnitDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACMixerUnitDescriptor_v2 desc = (CyACMixerUnitDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            bNrChannels = ByteToStr(desc.bNrChannels);
            bmChannelConfig = UintToStr(desc.bmChannelConfig);
            iChannelNames = desc.sChannelNames;
            bmMixerControls = ByteArrayToStr(desc.bmMixerControls.ToArray());
            bmControls = ByteToStr(desc.bmControls);
            iMixer = desc.sMixer;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACMixerUnitDescriptor_v2 usbDesc = new CyACMixerUnitDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.bmChannelConfig = StrToHexInt(bmChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.bmMixerControls = new List<byte>(StrToHex1BArray(bmMixerControls));
            usbDesc.bmControls = StrToHex1B(bmControls);
            usbDesc.sMixer = iMixer;
            return usbDesc;
        }
    }

    [XmlType("ACSelectorUnit_v2_Descriptor")]
    public class CyACSelectorUnitDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bUnitID;
        public string bNrInPins;
        public string baSourceID;
        public string bmControls;
        public string iSelector;

        public CyACSelectorUnitDescriptorTemplate_v2()
        {
        }

        public CyACSelectorUnitDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACSelectorUnitDescriptor_v2 desc = (CyACSelectorUnitDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            bmControls = ByteToStr(desc.bmControls);
            iSelector = desc.sSelector;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACSelectorUnitDescriptor_v2 usbDesc = new CyACSelectorUnitDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.bmControls = StrToHex1B(bmControls);
            usbDesc.sSelector = iSelector;
            return usbDesc;
        }
    }

    [XmlType("ACFeatureUnit_v2_Descriptor")]
    public class CyACFeatureUnitDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bUnitID;
        public string bSourceID;
        public string bmaControls;
        public string iFeature;

        public CyACFeatureUnitDescriptorTemplate_v2()
        {
        }

        public CyACFeatureUnitDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACFeatureUnitDescriptor_v2 desc = (CyACFeatureUnitDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            bSourceID = ByteToStr(desc.bSourceID);
            bmaControls = CustomArrayToStr(desc.bmaControls, 4);
            iFeature = desc.sFeature;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACFeatureUnitDescriptor_v2 usbDesc = new CyACFeatureUnitDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.bSourceID = StrToHex1B(bSourceID);
            usbDesc.bmaControls = StrToHex3BArray(bmaControls);
            usbDesc.sFeature = iFeature;
            return usbDesc;
        }
    }

    [XmlType("ACSRC_v2_Descriptor")]
    public class CyACSRCDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bUnitID;
        public string bSourceID;
        public string bCSourceInID;
        public string bCSourceOutID;
        public string iSRC;

        public CyACSRCDescriptorTemplate_v2()
        {
        }

        public CyACSRCDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACSamplingRateConverterDescriptor_v2 desc = (CyACSamplingRateConverterDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            bSourceID = ByteToStr(desc.bSourceID);
            bCSourceInID = ByteToStr(desc.bCSourceInID);
            bCSourceOutID = ByteToStr(desc.bCSourceOutID);
            iSRC = desc.sSRC;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACSamplingRateConverterDescriptor_v2 usbDesc = new CyACSamplingRateConverterDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.bSourceID = StrToHex1B(bSourceID);
            usbDesc.bCSourceInID = StrToHex1B(bCSourceInID);
            usbDesc.bCSourceOutID = StrToHex1B(bCSourceOutID);
            usbDesc.sSRC = iSRC;
            return usbDesc;
        }
    }

    [XmlType("ACEffectUnit_v2_Descriptor")]
    public class CyACEffectUnitDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bUnitID;
        public string wEffectType;
        public string bSourceID;
        public string baControls;
        public string iEffects;

        public CyACEffectUnitDescriptorTemplate_v2()
        {
        }

        public CyACEffectUnitDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACEffectUnitDescriptor_v2 desc = (CyACEffectUnitDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            wEffectType = UshortToStr((ushort)desc.wEffectType);
            bSourceID = ByteToStr(desc.bSourceID);
            baControls = CustomArrayToStr(desc.bmaControls, 4);
            iEffects = desc.sEffects;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACEffectUnitDescriptor_v2 usbDesc = new CyACEffectUnitDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.wEffectType = (CyUSBOtherTypes.CyEffectUnitEffectTypes)StrToHex2B(wEffectType);
            usbDesc.bSourceID = StrToHex1B(bSourceID);
            usbDesc.bmaControls = StrToHex3BArray(baControls);
            usbDesc.sEffects = iEffects;
            return usbDesc;
        }
    }

    [XmlType("ACProcessingUnit_v2_Descriptor")]
    public class CyACProcessingUnitDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bUnitID;
        public string wProcessType;
        public string bNrInPins;
        public string baSourceID;
        public string bNrChannels;
        public string bmChannelConfig;
        public string iChannelNames;
        public string bmControls;
        public string iProcessing;

        public CyACProcessingUnitDescriptorTemplate_v2()
        {
        }

        public CyACProcessingUnitDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACProcessingUnitDescriptor_v2 desc = (CyACProcessingUnitDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            wProcessType = UshortToStr(desc.wProcessType);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            bNrChannels = ByteToStr(desc.bNrChannels);
            bmChannelConfig = UintToStr(desc.bmChannelConfig);
            iChannelNames = desc.sChannelNames;
            bmControls = UshortToStr(desc.bmControls);
            iProcessing = desc.sProcessing;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACProcessingUnitDescriptor_v2 usbDesc = new CyACProcessingUnitDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.wProcessType = StrToHex2B(wProcessType);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.bmChannelConfig = StrToHexInt(bmChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.bmControls = StrToHex2B(bmControls);
            usbDesc.sProcessing = iProcessing;
            return usbDesc;
        }
    }

    [XmlType("ACExtension_v2_Descriptor")]
    public class CyACExtensionDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyACInterfaceDescriptorSubtypes_v2 bDescriptorSubtype;
        public string bUnitID;
        public string wExtensionCode;
        public string bNrInPins;
        public string baSourceID;
        public string bNrChannels;
        public string bmChannelConfig;
        public string iChannelNames;
        public string bmControls;
        public string iExtension;


        public CyACExtensionDescriptorTemplate_v2()
        {
        }

        public CyACExtensionDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyACExtensionDescriptor_v2 desc = (CyACExtensionDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bUnitID = ByteToStr(desc.bUnitID);
            wExtensionCode = UshortToStr(desc.wExtensionCode);
            bNrInPins = ByteToStr(desc.bNrInPins);
            baSourceID = ByteArrayToStr(desc.baSourceID);
            bNrChannels = ByteToStr(desc.bNrChannels);
            bmChannelConfig = UintToStr(desc.bmChannelConfig);
            iChannelNames = desc.sChannelNames;
            bmControls = ByteToStr(desc.bmControls);
            iExtension = desc.sExtension;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyACExtensionDescriptor_v2 usbDesc = new CyACExtensionDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bUnitID = StrToHex1B(bUnitID);
            usbDesc.wExtensionCode = StrToHex2B(wExtensionCode);
            usbDesc.bNrInPins = StrToHex1B(bNrInPins);
            usbDesc.baSourceID = StrToHex1BArray(baSourceID);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.bmChannelConfig = StrToHexInt(bmChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            usbDesc.bmControls = StrToHex1B(bmControls);
            usbDesc.sExtension = iExtension;

            return usbDesc;
        }
    }

    [XmlType("ASGeneral_v2_Descriptor")]
    public class CyASGeneralDescriptorTemplate_v2 : CyDescriptorTemplate
    {
        public CyUSBOtherTypes.CyASInterfaceDescriptorSubtypes bDescriptorSubtype;
        public string bTerminalLink;
        public string bmControls;
        public string bFormatType;
        public string bmFormats;
        public string bNrChannels;
        public string bmChannelConfig;
        public string iChannelNames;
        
        public CyASGeneralDescriptorTemplate_v2()
        {
        }

        public CyASGeneralDescriptorTemplate_v2(CyUSBDescriptor usbDesc)
        {
            CyASGeneralDescriptor_v2 desc = (CyASGeneralDescriptor_v2)usbDesc;
            bDescriptorSubtype = desc.bDescriptorSubtype;
            bTerminalLink = ByteToStr(desc.bTerminalLink);
            bmControls = ByteToStr(desc.bmControls);
            bFormatType = ByteToStr(desc.bFormatType);
            bmFormats = UintToStr(desc.bmFormats);
            bNrChannels = ByteToStr(desc.bNrChannels);
            bmChannelConfig = UintToStr(desc.bmChannelConfig);
            iChannelNames = desc.sChannelNames;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyASGeneralDescriptor_v2 usbDesc = new CyASGeneralDescriptor_v2();
            usbDesc.bDescriptorSubtype = bDescriptorSubtype;
            usbDesc.bTerminalLink = StrToHex1B(bTerminalLink);
            usbDesc.bmControls = StrToHex1B(bmControls);
            usbDesc.bFormatType = StrToHex1B(bFormatType);
            usbDesc.bmFormats = StrToHexInt(bmFormats);
            usbDesc.bNrChannels = StrToHex1B(bNrChannels);
            usbDesc.bmChannelConfig = StrToHexInt(bmChannelConfig);
            usbDesc.sChannelNames = iChannelNames;
            return usbDesc;
        }
    }
    
    #endregion Audio 2.0 Template

    //============================================================================================================
    #region CDC Template

    [XmlType("CDCHeader_Descriptor")]
    public class CyCDCHeaderDescriptorTemplate : CyDescriptorTemplate
    {
        public string bcdADC;

        public CyCDCHeaderDescriptorTemplate()
        {
        }

        public CyCDCHeaderDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyCDCHeaderDescriptor desc = (CyCDCHeaderDescriptor)usbDesc;
            bcdADC = UshortToStr(desc.bcdADC);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyCDCHeaderDescriptor usbDesc = new CyCDCHeaderDescriptor();
            usbDesc.bcdADC = StrToHex2B(bcdADC);
            return usbDesc;
        }
    }

    [XmlType("CDCUnion_Descriptor")]
    public class CyCDCUnionDescriptorTemplate : CyDescriptorTemplate
    {
        public string bControlInterface;
        public string bSubordinateInterface;

        public CyCDCUnionDescriptorTemplate()
        {
        }

        public CyCDCUnionDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyCDCUnionDescriptor desc = (CyCDCUnionDescriptor)usbDesc;
            bControlInterface = ByteToStr(desc.bControlInterface);
            bSubordinateInterface = ByteArrayToStr(desc.bSubordinateInterface);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyCDCUnionDescriptor usbDesc = new CyCDCUnionDescriptor();
            usbDesc.bControlInterface = StrToHex1B(bControlInterface);
            usbDesc.bSubordinateInterface = StrToHex1BArray(bSubordinateInterface);
            return usbDesc;
        }
    }

    [XmlType("CDCCountrySelection_Descriptor")]
    public class CyCDCCountrySelectionDescriptorTemplate : CyDescriptorTemplate
    {
        public string iCountryCodeRelDate;
        public string wCountryCode;

        public CyCDCCountrySelectionDescriptorTemplate()
        {
        }

        public CyCDCCountrySelectionDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyCDCCountrySelectionDescriptor desc = (CyCDCCountrySelectionDescriptor)usbDesc;
            iCountryCodeRelDate = ByteToStr(desc.iCountryCodeRelDate);
            wCountryCode = UshortArrayToStr(desc.wCountryCode);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyCDCCountrySelectionDescriptor usbDesc = new CyCDCCountrySelectionDescriptor();
            usbDesc.iCountryCodeRelDate = StrToHex1B(iCountryCodeRelDate);
            usbDesc.wCountryCode = StrToHex2BArray(wCountryCode);
            return usbDesc;
        }
    }

    [XmlType("CDCCallManagement_Descriptor")]
    public class CyCDCCallManagementDescriptorTemplate : CyDescriptorTemplate
    {
        public string bmCapabilities;
        public string bDataInterface;

        public CyCDCCallManagementDescriptorTemplate()
        {
        }

        public CyCDCCallManagementDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyCDCCallManagementDescriptor desc = (CyCDCCallManagementDescriptor)usbDesc;
            bmCapabilities = ByteToStr(desc.bmCapabilities);
            bDataInterface = ByteToStr(desc.bDataInterface);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyCDCCallManagementDescriptor usbDesc = new CyCDCCallManagementDescriptor();
            usbDesc.bmCapabilities = StrToHex1B(bmCapabilities);
            usbDesc.bDataInterface = StrToHex1B(bDataInterface);
            return usbDesc;
        }
    }

    [XmlType("CDCAbstractControlMgmt_Descriptor")]
    public class CyCDCAbstractControlMgmtDescriptorTemplate : CyDescriptorTemplate
    {
        public string bmCapabilities;

        public CyCDCAbstractControlMgmtDescriptorTemplate()
        {
        }

        public CyCDCAbstractControlMgmtDescriptorTemplate(CyUSBDescriptor usbDesc)
        {
            CyCDCAbstractControlMgmtDescriptor desc = (CyCDCAbstractControlMgmtDescriptor)usbDesc;
            bmCapabilities = ByteToStr(desc.bmCapabilities);
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            CyCDCAbstractControlMgmtDescriptor usbDesc = new CyCDCAbstractControlMgmtDescriptor();
            usbDesc.bmCapabilities = StrToHex1B(bmCapabilities);
            return usbDesc;
        }
    }
    
    #endregion CDC Template

    //============================================================================================================

    #region Endpoint memory management template

    [XmlType("EndpointMemoryManagement")]
    public class CyEpMemoryManagementTemplate : CyDescriptorTemplate
    {
        public CyUSBFSParameters.CyMemoryManagement MemoryManagement;
        public CyUSBFSParameters.CyMemoryAllocation MemoryAllocation;

        public CyEpMemoryManagementTemplate()
        {
        }

        public CyEpMemoryManagementTemplate(CyUSBFSParameters.CyMemoryManagement mm, 
                                            CyUSBFSParameters.CyMemoryAllocation ma)
        {
            MemoryManagement = mm;
            MemoryAllocation = ma;
        }

        public override CyUSBDescriptor ConvertToUSBDesc()
        {
            return new CyDeviceDescriptor();
        }
    }

    #endregion Endpoint memory management template
}
