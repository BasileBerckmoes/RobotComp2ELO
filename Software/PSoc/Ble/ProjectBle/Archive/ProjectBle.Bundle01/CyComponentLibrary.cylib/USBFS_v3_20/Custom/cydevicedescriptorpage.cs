/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace USBFS_v3_20
{
    public partial class CyDeviceDescriptorPage : CyEditingWrapperControl
    {
        #region Constants

        private const int LEVEL_DEVICE = 1;
        private const int LEVEL_CONFIGURATION = 2;
        private const int LEVEL_INTERFACE = 4;

        #endregion Constants

        #region Variables

        private UserControl m_controlDetails;
        private readonly List<UserControl> m_unusedControls;

        #endregion Variables

        #region Constructors

        public CyDeviceDescriptorPage()
        {
            InitializeComponent();
        }

        public CyDeviceDescriptorPage(CyUSBFSParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            RefreshDeviceTree();

            m_unusedControls = new List<UserControl>();
            ToolStripManager.Renderer =
                new ToolStripProfessionalRenderer(new CyCustomToolStripColors());

            m_parameters.RecalcDescriptors(m_parameters.DeviceTree.Nodes[0]);
        }

        #endregion Constructors

        #region CyEditingWrapperControl override
        public override string TabName
        {
            get { return CyCustomizer.PARAM_TAB_NAME_DEVICE; }
        }

        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            // Save all changes before closing the customizer
            m_parameters.RecalcDescriptors(m_parameters.HidReportTree.Nodes[0]);
            m_parameters.RecalcDescriptors(m_parameters.DeviceTree.Nodes[0]);
            m_parameters.SerializedDeviceDesc = m_parameters.SerializeDescriptorTree(m_parameters.DeviceTree);
            m_parameters.SetParam_rm_ep_isr();
            m_parameters.SetCdcVidPid(m_parameters.DeviceTree.Nodes[0], CyUsbConst.DEFAULT_VID.ToString("X"), 
                                                                            CyUsbConst.DEFAULT_PID.ToString("X"));

            //If there are empty fields
            if (m_parameters.EmptyFields.Count > 0)
                errorList.Add(new CyCustErr(Properties.Resources.MSG_UNDEFINED_HIDREPORT));

            //Check EP MaxPacketSize values
            if (!m_parameters.CheckEPMaxPacketSize(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.ERR_EP_MAXPACKETSIZE));
            if (!m_parameters.CheckSumEpBuffSizeNotAutoDma(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.MSG_DRC_EP_SUM_MANUAL));
            if (!m_parameters.CheckSumEpBuffSizeStatAlloc(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.MSG_DRC_EP_SUM_STATT_ALLOC));
            if (!m_parameters.CheckSumEPMaxPacketSizeAll(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.MSG_DRC_EP_SUM_AUTO));
            if (!m_parameters.CheckEPBulkMaxPacketSize(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.MSG_BULK_MAXPACKETSIZE));

            // Check EP Interval value
            if (!m_parameters.CheckEPInterruptInterval(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.ERR_EP_INTR_BINTERVAL_0));

            // Check Container ID value format
            if (!m_parameters.CheckContainerIdFormat(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.ERR_UUID_WRONG_FORMAT));

            // Check EP Unique Endpoint Number for each Alternate Setting
            if (!m_parameters.CheckUniqueEndpointNumber(m_parameters.DeviceTree.Nodes[0]))
                errorList.Add(new CyCustErr(Properties.Resources.ERR_NOTUNIQUE_EP_NUMBER));

            errorList.AddRange(base.GetErrors());
            return errorList.ToArray();
        }
        #endregion

        #region General functions

        /// <summary>
        /// Rebuilds Device Descriptors TreeView based on m_deviceTree
        /// </summary>
        private void RefreshDeviceTree()
        {
            treeViewDevice.BeginUpdate();
            treeViewDevice.Nodes.Clear();
            for (int i = 0; i < m_parameters.DeviceTree.Nodes.Count; i++)
            {
                CyDescriptorNode descriptor = m_parameters.DeviceTree.Nodes[i];
                TreeNode node = treeViewDevice.Nodes.Add(descriptor.Key, 
                                                         CyDescriptorNode.GetDescriptorLabel(descriptor), 0, 0);
                RefreshNode(descriptor, node);
            }
            treeViewDevice.ExpandAll();
            SelectedNodeChanged(treeViewDevice.SelectedNode);
            treeViewDevice.EndUpdate();
        }
        /// <summary>
        /// Recursive function that supplement RefreshDeviceTree() function
        /// </summary>
        /// <param name="descriptor"></param>
        /// <param name="treeNode"></param>
        private void RefreshNode(CyDescriptorNode descriptor, TreeNode treeNode)
        {
            const int AUDIO_IMAGE_INDEX = 3;
            const int CDC_IMAGE_INDEX = 4;
            const int MSC_IMAGE_INDEX = 5;

            int imageIndex = 0;
            for (int i = 0; i < descriptor.Nodes.Count; i++)
            {
                Color foreColor = SystemColors.ControlText;
                CyDescriptorNode descriptor_child = descriptor.Nodes[i];
                TreeNode node;
                if (descriptor_child.Value == null)
                {
                    switch (descriptor_child.Key)
                    {
                        default:
                            if (descriptor_child.Key.Contains(CyUSBFSParameters.NODEKEY_INTERFACE))
                                imageIndex = 2;
                            break;
                    }
                    node = treeNode.Nodes.Add(descriptor_child.Key,
                                              CyDescriptorNode.GetDescriptorLabel(descriptor_child), imageIndex, 
                                              imageIndex);
                }
                else
                {
                    switch (descriptor_child.Value.bDescriptorType)
                    {
                        case CyUSBDescriptorType.DEVICE:
                            imageIndex = 1;
                            break;
                        case CyUSBDescriptorType.AUDIO:
                        case CyUSBDescriptorType.CS_ENDPOINT:
                            foreColor = SystemColors.GrayText;
                            imageIndex = AUDIO_IMAGE_INDEX;
                            break;
                        case CyUSBDescriptorType.CDC:
                            foreColor = SystemColors.GrayText;
                            imageIndex = CDC_IMAGE_INDEX;
                            break;
                        case CyUSBDescriptorType.MSC:
                            foreColor = SystemColors.GrayText;
                            imageIndex = MSC_IMAGE_INDEX;
                            break;
                        case CyUSBDescriptorType.INTERFACE:
                             if ((descriptor_child.Value is CyAudioInterfaceDescriptor) ||
                                 (descriptor_child.Value is CyCDCInterfaceDescriptor) ||
                                 (descriptor_child.Value is CyMscInterfaceDescriptor))
                             {
                                 int imgIndex = 0;
                                 
                                 if(descriptor_child.Value is CyAudioInterfaceDescriptor)
                                 {
                                     imgIndex = AUDIO_IMAGE_INDEX;
                                 }
                                 else if(descriptor_child.Value is CyCDCInterfaceDescriptor)
                                 {
                                     imgIndex = CDC_IMAGE_INDEX;
                                 }
                                 else if(descriptor_child.Value is CyMscInterfaceDescriptor)
                                 {
                                     imgIndex = MSC_IMAGE_INDEX;
                                 }

                                 foreColor = SystemColors.GrayText;
                                 imageIndex = imgIndex;
                                 treeNode.ForeColor = foreColor;
                                 treeNode.ImageIndex = imgIndex;
                                 treeNode.SelectedImageIndex = imgIndex;
                             }
                             else
                                 imageIndex = 2;
                            break;
                        case CyUSBDescriptorType.ALTERNATE:
                        case CyUSBDescriptorType.CONFIGURATION:
                        case CyUSBDescriptorType.HID:
                        case CyUSBDescriptorType.INTERFACE_ASSOCIATION:
                        case CyUSBDescriptorType.BOS:
                        case CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY:
                        case CyUSBDescriptorType.CONTAINER_ID:
                        case CyUSBDescriptorType.DEVICE_CAPABILITY:
                            imageIndex = 2;
                            break;
                        case CyUSBDescriptorType.ENDPOINT:
                            imageIndex = 2;
                            if (descriptor_child.Value is CyAudioEndpointDescriptor)
                            {
                                imageIndex = AUDIO_IMAGE_INDEX;
                                foreColor = SystemColors.GrayText;
                            }
                            else if ((descriptor.Value != null) && (descriptor.Value is CyCDCInterfaceDescriptor))
                            {
                                imageIndex = CDC_IMAGE_INDEX;
                                foreColor = SystemColors.GrayText;
                            }
                            else if ((descriptor.Value != null) && (descriptor.Value is CyMscInterfaceDescriptor))
                            {
                                imageIndex = MSC_IMAGE_INDEX;
                                foreColor = SystemColors.GrayText;
                            }
                            break;
                        default:
                            Debug.Assert(false, "unhandled");
                            break;
                    }


                    if (descriptor_child.Value.bDescriptorType == CyUSBDescriptorType.HID)
                    {
                        node = treeNode.Nodes.Insert(0, descriptor_child.Key,
                                                     CyDescriptorNode.GetDescriptorLabel(descriptor_child), imageIndex,
                                                     imageIndex);
                    }
                    else if ((descriptor_child.Value.bDescriptorType == CyUSBDescriptorType.AUDIO) ||
                             (descriptor_child.Value.bDescriptorType == CyUSBDescriptorType.CDC) ||
                             (descriptor_child.Value.bDescriptorType == CyUSBDescriptorType.MSC))
                    {
                        int nodeIndex = 0;
                        for (int j = 0; j < descriptor.Nodes.IndexOf(descriptor_child); j++)
                        {
                            if ((descriptor.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.AUDIO) ||
                                (descriptor.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.CDC) ||
                                (descriptor.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.MSC))
                            {
                                nodeIndex++;
                            }
                        }
                        node = treeNode.Nodes.Insert(nodeIndex, descriptor_child.Key,
                                                     CyDescriptorNode.GetDescriptorLabel(descriptor_child), imageIndex,
                                                     imageIndex);
                    }
                    else
                    {
                        node = treeNode.Nodes.Add(descriptor_child.Key,
                                                  CyDescriptorNode.GetDescriptorLabel(descriptor_child), imageIndex,
                                                  imageIndex);
                    }
                    node.ForeColor = foreColor;
                }
                RefreshNode(descriptor_child, node);
            }
        }

        /// <summary>
        /// Manages adding a new node to the m_deviceTree operation
        /// </summary>
        /// <param name="type">Defines a type of the node to add. This parameter is significant only for special cases
        /// (HID, AUDIO, Interface). In other cases this param is not taken into account</param>
        public void AddNode(CyUSBDescriptorType type)
        {
            TreeNode treeNode = treeViewDevice.SelectedNode;
            if (treeNode != null)
            {
                if (type == CyUSBDescriptorType.BOS)
                    m_parameters.DeviceTree.AddNode(treeNode.Name, CyUSBDescriptorType.BOS);
                else if (type == CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY)
                    m_parameters.DeviceTree.AddNode(treeNode.Name, CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY);
                else if (type == CyUSBDescriptorType.CONTAINER_ID)
                    m_parameters.DeviceTree.AddNode(treeNode.Name, CyUSBDescriptorType.CONTAINER_ID);
                else if (type == CyUSBDescriptorType.HID)
                    m_parameters.DeviceTree.AddNode(treeNode.Name, CyUSBDescriptorType.HID);
                else if (type == CyUSBDescriptorType.AUDIO)
                    m_parameters.DeviceTree.AddNode(treeNode.Name, CyUSBDescriptorType.AUDIO);
                else if (type == CyUSBDescriptorType.INTERFACE_ASSOCIATION)
                    m_parameters.DeviceTree.AddNode(treeNode.Name, CyUSBDescriptorType.INTERFACE_ASSOCIATION);
                else if (treeNode.Name.Contains(CyUSBFSParameters.NODEKEY_INTERFACE))
                {
                    if (treeNode.Parent != null)
                        m_parameters.DeviceTree.AddNode(treeNode.Name, treeNode.Parent.Name);
                }
                else
                {
                    m_parameters.DeviceTree.AddNode(treeNode.Name);
                }
            }
            RefreshDeviceTree();
            if (treeNode != null) treeViewDevice.SelectedNode = treeViewDevice.Nodes.Find(treeNode.Name, true)[0];
            SelectedNodeChanged(treeViewDevice.SelectedNode);
        }

        /// <summary>
        /// Removes the selected node from the m_deviceTree
        /// </summary>
        private void RemoveNode(TreeNode treeNode)
        {
            TreeNode parent = treeNode.Parent;

            if (treeNode == null) return;

            try
            {
                CyDescriptorNode descNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);

                if (descNode.Value == null)
                {
                    if (descNode.Key.Contains(CyUSBFSParameters.NODEKEY_INTERFACE))
                    {
                        for (int i = treeNode.Index + 1; i < parent.Nodes.Count; i++)
                        {
                            CyDescriptorNode interfaceNode = 
                                m_parameters.DeviceTree.GetNodeByKey(parent.Nodes[i].Name);
                            for (int j = 0; j < interfaceNode.Nodes.Count; j++)
                            {
                                if (((CyInterfaceDescriptor)interfaceNode.Nodes[j].Value).bInterfaceNumber > 0)
                                    ((CyInterfaceDescriptor) interfaceNode.Nodes[j].Value).bInterfaceNumber--;
                            }
                        }
                    }
                }
                // Check if it is HID class. If so, confirm delete and change the Interface class to Undefined
                else if (descNode.Value.bDescriptorType == CyUSBDescriptorType.HID)
                {
                    if (MessageBox.Show(Properties.Resources.MSG_INTERFACE_CHANGE, Properties.Resources.MSG_TITLE_WARNING, 
                        MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
                    {
                        CyDescriptorNode descNodeInterface = m_parameters.DeviceTree.GetNodeByKey(parent.Name);
                        ((CyInterfaceDescriptor) descNodeInterface.Value).bInterfaceClass = 0;
                        ((CyInterfaceDescriptor) descNodeInterface.Value).bInterfaceSubClass = 0;
                        ((CyInterfaceDescriptor) descNodeInterface.Value).bInterfaceProtocol = 0;
                    }
                    else
                    {
                        return;
                    }
                }

                else if (descNode.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE)
                {
                    for (int i = parent.Nodes.IndexOf(treeNode) + 1; i < parent.Nodes.Count; i++)
                    {
                        CyDescriptorNode altInterfaceNode = 
                            m_parameters.DeviceTree.GetNodeByKey(parent.Nodes[i].Name);
                        if (((CyInterfaceDescriptor)altInterfaceNode.Value).bAlternateSetting > 0)
                            ((CyInterfaceDescriptor) altInterfaceNode.Value).bAlternateSetting--;
                    }
                }

                else if (descNode.Value.bDescriptorType == CyUSBDescriptorType.ALTERNATE)
                {
                    for (int i = treeNode.Index + 1; i < parent.Nodes.Count; i++)
                    {
                        CyDescriptorNode interfaceNode = m_parameters.DeviceTree.GetNodeByKey(parent.Nodes[i].Name);
                        for (int j = 0; j < interfaceNode.Nodes.Count; j++)
                        {
                            if (((CyInterfaceDescriptor)interfaceNode.Nodes[j].Value).bInterfaceNumber > 0)
                                ((CyInterfaceDescriptor) interfaceNode.Nodes[j].Value).bInterfaceNumber--;
                        }
                    }
                }
            }
            catch (Exception)
            {
                Debug.Assert(false);
            }

            if (parent != null)
                m_parameters.DeviceTree.RemoveNode(treeNode.Name, parent.Name);
            else
                m_parameters.DeviceTree.RemoveNode(treeNode.Name, "");

            RefreshDeviceTree();
            SelectedNodeChanged(treeViewDevice.SelectedNode);
        }

        private bool IsDescriptorPresent(TreeNode treeNode, CyUSBDescriptorType bTypte)
        {
            CyDescriptorNode node = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);

            if (node.Value.bDescriptorType == bTypte)
                return true;

            for (int i = 0; i < treeNode.Nodes.Count; i++)
            {
                if (IsDescriptorPresent(treeNode.Nodes[i], bTypte))
                    return true;
            }

            return false;
        }

        /// <summary>
        /// Updates attributes panel and manages tool buttons visibility for the selected node
        /// </summary>
        /// <param name="selectedNode"></param>
        private void SelectedNodeChanged(TreeNode selectedNode)
        {
            if (selectedNode != null)
            {
                if (m_controlDetails != null)
                {
                    panelDetails.Controls.Remove(m_controlDetails);
                    CleanControls(m_unusedControls);
                    m_unusedControls.Add(m_controlDetails);
                }
                panelDetails.Visible = true;
                toolStripOperations.Visible = true;

                //Template toolStripButtons group visibility
                toolStripSplitButtonImport.Visible = true;
                toolStripSplitButtonSave.Visible = true;
                toolStripSeparatorTemplates.Visible = true;
                toolStripSplitButtonAddInterace.Visible = false;

                CyDescriptorNode node = m_parameters.DeviceTree.GetNodeByKey(selectedNode.Name);
                CyUSBDescriptor descriptor;
                if (node != null)
                {
                    if (node.Value == null)
                    {
                        switch (node.Key)
                        {
                            case CyUSBFSParameters.NODEKEY_DEVICE:
                                CyDetailsEPMngt details_epmngt = new CyDetailsEPMngt(m_parameters);
                                details_epmngt.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(details_epmngt);
                                m_controlDetails = details_epmngt;
                                m_controlDetails.BringToFront();

                                toolStripButtonRemove.Enabled = false;
                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = true;
                                toolStripButtonAdd.Text = "Add Device";
                                break;
                            default:
                                if (node.Key.Contains(CyUSBFSParameters.NODEKEY_INTERFACE))
                                {
                                    toolStripButtonRemove.Enabled = true;
                                    toolStripButtonAddBos.Visible = false;
                                    toolStripButtonAdd.Visible = true;
                                    toolStripButtonAdd.Text = "Add Alternate Setting";
                                }
                                break;
                        }
                    }
                    else
                    {
                        descriptor = node.Value;
                        switch (descriptor.bDescriptorType)
                        {
                            case CyUSBDescriptorType.DEVICE:
                                CyDetailsDevice details_device = new CyDetailsDevice((CyDeviceDescriptor) descriptor,
                                                                                     m_parameters);
                                details_device.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(details_device);
                                m_controlDetails = details_device;

                                toolStripButtonAddBos.Text = "Add BOS";
                                toolStripButtonAddBos.Enabled = !IsDescriptorPresent(selectedNode, 
                                    CyUSBDescriptorType.BOS);
                                toolStripButtonAddBos.Visible = m_parameters.IsPSoC4AL_IpBlock;
                                toolStripButtonAdd.Visible = true;
                                toolStripButtonAdd.Text = "Add Configuration";
                                toolStripButtonRemove.Enabled = true;
                                break;
                            case CyUSBDescriptorType.CONFIGURATION:
                                CyDetailsConfig details_config = new CyDetailsConfig((CyConfigDescriptor) descriptor,
                                                                                     m_parameters);
                                details_config.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(details_config);
                                m_controlDetails = details_config;

                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonAdd.Text = "Add Interface";
                                toolStripButtonRemove.Enabled = true;
                                toolStripSplitButtonAddInterace.Visible = true;
                                break;
                            case CyUSBDescriptorType.BOS:

                                toolStripButtonAddBos.Text = "Add Container ID";
                                toolStripButtonAddBos.Enabled = !IsDescriptorPresent(selectedNode,
                                    CyUSBDescriptorType.CONTAINER_ID);
                                toolStripButtonAddBos.Visible = m_parameters.IsPSoC4AL_IpBlock;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonRemove.Enabled = true;
                                CyDetailsBos detailBos = new CyDetailsBos();
                                detailBos.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(detailBos);
                                m_controlDetails = detailBos;
                                break;
                            case CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY:
                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonRemove.Enabled = false;
                                CyDetailsUsb20Extension detailUsb20Extension = new CyDetailsUsb20Extension(
                                    (CyUsb20ExtensionDeviceCapabilityDescriptor)descriptor, m_parameters);
                                detailUsb20Extension.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(detailUsb20Extension);
                                m_controlDetails = detailUsb20Extension;
                                break;
                            case CyUSBDescriptorType.CONTAINER_ID:
                                CyDetailsContainerId detailContainerId = new CyDetailsContainerId(
                                    (CyContainerIdDescriptor)descriptor, m_parameters);
                                detailContainerId.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(detailContainerId);
                                m_controlDetails = detailContainerId;
                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonRemove.Enabled = true;
                                break;
                            case CyUSBDescriptorType.ALTERNATE:
                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonRemove.Enabled = true;
                                toolStripButtonAdd.Visible = true;
                                toolStripButtonAdd.Text = "Add Alternate Setting";
                                break;
                            case CyUSBDescriptorType.INTERFACE_ASSOCIATION:
                                CyDetailsIntAssociation details_intassociation =
                                    new CyDetailsIntAssociation((CyInterfaceAssociationDescriptor)descriptor, 
                                                                 m_parameters, this);
                                details_intassociation.Dock = DockStyle.Fill;
                                details_intassociation.RemoveClassNodeEvent +=
                                    new EventHandler(details_interface_RemoveClassNodeEvent);
                                panelDetails.Controls.Add(details_intassociation);
                                m_controlDetails = details_intassociation;

                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonRemove.Enabled = true;
                                break;
                            case CyUSBDescriptorType.INTERFACE:
                                // Calculate and display interface number as position in device tree.
                                // Interface number can differ from bInterfaceNumber if the same interface is imported 
                                // more than two times in different places.
                                int interfaceIndex = -1;
                                TreeNode parentInterfaceGeneral = selectedNode.Parent;
                                TreeNode parentConfig = parentInterfaceGeneral.Parent;
                                for (int i = 0; i < parentConfig.Nodes.Count; i++)
                                {
                                    CyUSBDescriptor desc = m_parameters.DeviceTree.GetNodeByKey(parentConfig.Nodes[i].
                                        Name).Value;
                                    if (desc is CyInterfaceGeneralDescriptor)
                                        interfaceIndex++;

                                    if (parentConfig.Nodes[i] == parentInterfaceGeneral)
                                        break;
                                }

                                CyDetailsInterface details_interface =
                                    new CyDetailsInterface((CyInterfaceDescriptor)descriptor, m_parameters, this, 
                                        interfaceIndex);
                                details_interface.Dock = DockStyle.Fill;
                                details_interface.RemoveClassNodeEvent +=
                                    new  EventHandler(details_interface_RemoveClassNodeEvent);
                                panelDetails.Controls.Add(details_interface);
                                m_controlDetails = details_interface;

                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = true;
                                toolStripButtonAdd.Text = "Add Endpoint";
                                toolStripButtonRemove.Enabled = true;
                                break;
                            case CyUSBDescriptorType.ENDPOINT:
                                bool enabled = (selectedNode.ForeColor != SystemColors.GrayText);
                                CyDetailsEndpoint details_endpoint =
                                    new CyDetailsEndpoint((CyEndpointDescriptor)descriptor, m_parameters, enabled);
                                details_endpoint.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(details_endpoint);
                                m_controlDetails = details_endpoint;

                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonRemove.Enabled = true;
                                break;
                            case CyUSBDescriptorType.HID:
                                CyDetailsHID details_hid = new CyDetailsHID((CyHIDDescriptor) descriptor, m_parameters);
                                details_hid.Dock = DockStyle.Fill;
                                panelDetails.Controls.Add(details_hid);
                                m_controlDetails = details_hid;

                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonRemove.Enabled = true;
                                break;
                            case CyUSBDescriptorType.AUDIO:
                            case CyUSBDescriptorType.CDC:
                            case CyUSBDescriptorType.MSC:
                            case CyUSBDescriptorType.CS_ENDPOINT:
                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = false;
                                toolStripButtonRemove.Enabled = true;
                                break;
                            default:
                                toolStripButtonAddBos.Visible = false;
                                toolStripButtonAdd.Visible = true;
                                toolStripButtonRemove.Enabled = true;
                                break;
                        }
                        if (m_controlDetails != null)
                            m_controlDetails.BringToFront();
                    }
                }
                // Disable adding new items for the audio read-only interfaces
                if (selectedNode.ForeColor == SystemColors.GrayText)
                {
                    toolStripButtonAdd.Visible = false;
                }


                //Set button Add enable/disable
                const int MAX_CHILDREN_NUMBER = 255;
                if (node.Nodes.Count >= MAX_CHILDREN_NUMBER)
                {
                    toolStripButtonAdd.Enabled = false;
                }
                else
                {
                    toolStripButtonAdd.Enabled = true;
                }
            }
            else
            {
                if (m_controlDetails != null)
                {
                    panelDetails.Controls.Remove(m_controlDetails);
                    CleanControls(m_unusedControls);
                    m_unusedControls.Add(m_controlDetails);
                    m_controlDetails = null;
                }
                panelDetails.Visible = false;
                toolStripSplitButtonImport.Visible = true;
                toolStripSplitButtonSave.Visible = true;
                toolStripSeparatorTemplates.Visible = true;
                toolStripSplitButtonAddInterace.Visible = false;
                toolStripButtonAdd.Visible = false;
                toolStripButtonAddBos.Visible = false;
                toolStripButtonRemove.Enabled = false;
            }
        }

        /// <summary>
        /// Removed if necessary the HID class node depending on the option selected in the Interface attributes
        /// </summary>
        private void details_interface_RemoveClassNodeEvent(object sender, EventArgs e)
        {
            TreeNode parent = treeViewDevice.SelectedNode;
            for (int i = 0; i < treeViewDevice.SelectedNode.Nodes.Count; i++)
            {
                TreeNode treeNode = treeViewDevice.SelectedNode.Nodes[i];
                CyDescriptorNode descNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);
                if ((parent != null) && (descNode != null) &&
                    (descNode.Value.bDescriptorType != CyUSBDescriptorType.ENDPOINT))
                    m_parameters.DeviceTree.RemoveNode(treeNode.Name, parent.Name);
            }
            RefreshDeviceTree();
            if (parent != null) treeViewDevice.SelectedNode = treeViewDevice.Nodes.Find(parent.Name, true)[0];
            SelectedNodeChanged(treeViewDevice.SelectedNode);
        }

        /// <summary>
        /// Disposes unused controls that could be accumulated during creation of the attributes panel each time the 
        /// selected node is changed.
        /// </summary>
        /// <param name="controlList"></param>
        public static void CleanControls(List<UserControl> controlList)
        {
            for (int i = 0; i < controlList.Count; i++)
            {
                controlList[i].Dispose();
            }
            controlList.Clear();
        }

        /// <summary>
        /// Get parent Device node for selected node
        /// </summary>
        private TreeNode GetCurrentDeviceNode()
        {
            if (treeViewDevice.SelectedNode == null || treeViewDevice.SelectedNode.Level < LEVEL_DEVICE)
                return null;

            TreeNode deviceNode = treeViewDevice.SelectedNode;
            for (int i = 0; i < treeViewDevice.SelectedNode.Level - LEVEL_DEVICE; i++)
            {
                deviceNode = deviceNode.Parent;
            }

            return deviceNode;
        }

        #endregion General functions

        #region Events

        private void CyDeviceDescriptor_Load(object sender, EventArgs e)
        {
            RefreshDeviceTree();
        }

        private void treeViewDevice_AfterSelect(object sender, TreeViewEventArgs e)
        {
            SelectedNodeChanged(e.Node);
        }

        private void toolStripButtonRemove_Click(object sender, EventArgs e)
        {
            RemoveNode(treeViewDevice.SelectedNode);
            m_parameters.ParamDeviceTreeChanged();
        }

        private void toolStripButtonAdd_Click(object sender, EventArgs e)
        {
            AddNode(CyUSBDescriptorType.DEVICE); // temporary parameter
            m_parameters.ParamDeviceTreeChanged();
        }

        private void toolStripButtonAddBos_Click(object sender, EventArgs e)
        {
            CyDescriptorNode node = m_parameters.DeviceTree.GetNodeByKey(treeViewDevice.SelectedNode.Name);

            if (node.Value.bDescriptorType == CyUSBDescriptorType.DEVICE)
            {
                AddNode(CyUSBDescriptorType.BOS);
            }
            if (node.Value.bDescriptorType == CyUSBDescriptorType.BOS)
                AddNode(CyUSBDescriptorType.CONTAINER_ID);

            m_parameters.ParamDeviceTreeChanged();
            RefreshDeviceTree();
        }

        private void toolStripSplitButtonAddInterface_DropDownOpening(object sender, EventArgs e)
        {
            // Audio submenu
            ToolStripItemCollection audioItems = audioToolStripMenuItem.DropDown.Items;
            audioItems.Clear();
            for (int i = 0; i < m_parameters.AudioTree.Nodes[0].Nodes.Count; i++)
            {
                ToolStripItem item = audioItems.Add(m_parameters.AudioTree.Nodes[0].Nodes[i].Value.ToString());
                item.Click += new EventHandler(addAudioItem_Click);
            }
            if (m_parameters.AudioTree.Nodes[0].Nodes.Count == 0)
            {
                ToolStripItem itemNoneAudio = new ToolStripMenuItem("(none)");
                itemNoneAudio.Enabled = false;
                audioItems.Add(itemNoneAudio);
            }
            // Midi submenu
            ToolStripItemCollection midiItems = mIDIToolStripMenuItem.DropDown.Items;
            midiItems.Clear();
            for (int i = 0; i < m_parameters.MidiTree.Nodes[0].Nodes.Count; i++)
            {
                ToolStripItem item = midiItems.Add(m_parameters.MidiTree.Nodes[0].Nodes[i].Value.ToString());
                item.Click += new EventHandler(addMidiItem_Click);
            }
            if (m_parameters.MidiTree.Nodes[0].Nodes.Count == 0)
            {
                ToolStripItem itemNoneMidi = new ToolStripMenuItem("(none)");
                itemNoneMidi.Enabled = false;
                midiItems.Add(itemNoneMidi);
            }
            // CDC submenu
            ToolStripItemCollection cdcItems = cdcToolStripMenuItem.DropDown.Items;
            cdcItems.Clear();
            for (int i = 0; i < m_parameters.CdcTree.Nodes[0].Nodes.Count; i++)
            {
                ToolStripItem item = cdcItems.Add(m_parameters.CdcTree.Nodes[0].Nodes[i].Value.ToString());
                item.Click += new EventHandler(addCDCItem_Click);
            }
            if (m_parameters.CdcTree.Nodes[0].Nodes.Count == 0)
            {
                ToolStripItem itemNoneCDC = new ToolStripMenuItem("(none)");
                itemNoneCDC.Enabled = false;
                cdcItems.Add(itemNoneCDC);
            }

            // MSC submenu
            ToolStripItemCollection mscItems = mscToolStripMenuItem.DropDown.Items;
            mscItems.Clear();
            for (int i = 0; i < m_parameters.MscTree.Nodes[0].Nodes.Count; i++)
            {
                ToolStripItem item = mscItems.Add(m_parameters.MscTree.Nodes[0].Nodes[i].Value.ToString());
                item.Click += new EventHandler(addMscItem_Click);
            }
            if (m_parameters.MscTree.Nodes[0].Nodes.Count == 0)
            {
                ToolStripItem itemNoneMsc = new ToolStripMenuItem("(none)");
                itemNoneMsc.Enabled = false;
                mscItems.Add(itemNoneMsc);
            }
        }

        void addAudioItem_Click(object sender, EventArgs e)
        {
            TreeNode treeNode = treeViewDevice.SelectedNode;
            if (treeNode != null)
            {
                CyDescriptorNode parentNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);
                if (parentNode != null)
                {
                    int itemIndex = audioToolStripMenuItem.DropDownItems.IndexOf((ToolStripItem)sender);
                    parentNode.Nodes.Add(m_parameters.AudioTree.Nodes[0].Nodes[itemIndex]);

                    m_parameters.ParamDeviceTreeChanged();
                    RefreshDeviceTree();
                }
            }
        }

        void addMidiItem_Click(object sender, EventArgs e)
        {
            TreeNode treeNode = treeViewDevice.SelectedNode;
            if (treeNode != null)
            {
                CyDescriptorNode parentNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);
                if (parentNode != null)
                {
                    int itemIndex = mIDIToolStripMenuItem.DropDownItems.IndexOf((ToolStripItem)sender);
                    parentNode.Nodes.Add(m_parameters.MidiTree.Nodes[0].Nodes[itemIndex]);

                    m_parameters.ParamDeviceTreeChanged();
                    RefreshDeviceTree();
                }
            }
        }

        void addCDCItem_Click(object sender, EventArgs e)
        {
            TreeNode treeNode = treeViewDevice.SelectedNode;
            if (treeNode != null)
            {
                CyDescriptorNode parentNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);
                if (parentNode != null)
                {
                    int itemIndex = cdcToolStripMenuItem.DropDownItems.IndexOf((ToolStripItem)sender);
                    parentNode.Nodes.Add(m_parameters.CdcTree.Nodes[0].Nodes[itemIndex]);

                    m_parameters.ParamDeviceTreeChanged();
                    RefreshDeviceTree();
                }
            }
        }

        void addMscItem_Click(object sender, EventArgs e)
        {
            TreeNode treeNode = treeViewDevice.SelectedNode;
            if (treeNode != null)
            {
                CyDescriptorNode parentNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);
                if (parentNode != null)
                {
                    int itemIndex = mscToolStripMenuItem.DropDownItems.IndexOf((ToolStripItem)sender);
                    parentNode.Nodes.Add(m_parameters.MscTree.Nodes[0].Nodes[itemIndex]);

                    m_parameters.ParamDeviceTreeChanged();
                    RefreshDeviceTree();
                }
            }
        }

        private void associationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddNode(CyUSBDescriptorType.INTERFACE_ASSOCIATION); 
            m_parameters.ParamDeviceTreeChanged();
        }
        
        private void CyDeviceDescriptor_VisibleChanged(object sender, EventArgs e)
        {
            //Refresh tree (if Audio, String or Report Descriptors were changed)
            if (Visible)
            {
                TreeNode selectedNode = treeViewDevice.SelectedNode;
                RefreshDeviceTree();
                if (selectedNode != null)
                {
                    TreeNode[] n = treeViewDevice.Nodes.Find(selectedNode.Name, true);
                    if (n.Length > 0) treeViewDevice.SelectedNode = n[0];
                }
            }
        }

        private void treeViewDevice_KeyDown(object sender, KeyEventArgs e)
        {
            if (toolStripButtonRemove.Visible && toolStripButtonRemove.Enabled)
                if (e.KeyCode == Keys.Delete)
                {
                    RemoveNode(treeViewDevice.SelectedNode);
                    m_parameters.ParamDeviceTreeChanged();
                }
        }

        #region DragNDrop
        private void treeViewDesc_ItemDrag(object sender, ItemDragEventArgs e)
        {
            TreeNode treeNode = e.Item as TreeNode;

            if ((treeNode != null) && (((TreeNode)e.Item).Level > 0))
            {
                CyDescriptorNode descNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);

                System.Type type = descNode.m_value.GetType();
                if (type != typeof(CyHIDDescriptor) &&
                    type != typeof(CyBosDescriptor) &&
                    type != typeof(CyUsb20ExtensionDeviceCapabilityDescriptor) &&
                    type != typeof(CyContainerIdDescriptor))
                    DoDragDrop(e.Item, DragDropEffects.Move);
            }
        }

        private void treeViewDesc_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Move;
        }

        private TreeNode m_oldNode;
        private Color m_defaultNodeColor = SystemColors.Window;

        private void treeViewDesc_DragOver(object sender, DragEventArgs e)
        {
            Point pt = ((TreeView)sender).PointToClient(new Point(e.X, e.Y));
            TreeNode aNode = ((TreeView)sender).GetNodeAt(pt);
            if ((aNode != null) && (e.Data.GetDataPresent(CyUSBFSParameters.TYPE_TREE_NODE, false)))
            {
                // If the node is a folder, change the color of the background to dark blue to simulate selection
                // Be sure to return the previous node to its original color by copying from a blank node
                if ((m_oldNode != null) && (m_oldNode != aNode))
                {
                    m_oldNode.BackColor = m_defaultNodeColor;
                    e.Effect = DragDropEffects.None;
                }
                TreeNode dragNode = (TreeNode)e.Data.GetData(CyUSBFSParameters.TYPE_TREE_NODE);
                if ((aNode.Level == dragNode.Level) || (aNode.Level == dragNode.Level - 1))
                {
                    CyDescriptorNode sourceParentDesc = m_parameters.DeviceTree.GetNodeByKey(dragNode.Parent.Name);
                    TreeNode destParent;
                    CyDescriptorNode destParentDesc;
                    if (aNode.Level == dragNode.Level)
                    {
                        destParentDesc = m_parameters.DeviceTree.GetNodeByKey(aNode.Parent.Name);
                        destParent = aNode.Parent;
                    }
                    else
                    {
                        destParentDesc = m_parameters.DeviceTree.GetNodeByKey(aNode.Name);
                        destParent = aNode;
                    }

                    bool isSubClassEquals = true;
                    CyInterfaceDescriptor sourceParentInterfaceDesc = sourceParentDesc.m_value as CyInterfaceDescriptor;
                    CyInterfaceDescriptor destParentInterfaceDesc = destParentDesc.m_value as CyInterfaceDescriptor;
                    if (sourceParentInterfaceDesc != null && destParentInterfaceDesc != null &&
                        sourceParentInterfaceDesc.bInterfaceSubClass != destParentInterfaceDesc.bInterfaceSubClass)
                        isSubClassEquals = false;

                    // This part allows drag and drop functionality on Drag Over level
                    // 1. Sub classes of parents must be equal
                    // 2. Descriptor type of parents must be equal
                    // 3. None level (first node)is exception because this node is not a USB descriptor but D'N'D 
                    //    should be allowed
                    if ((aNode.Level == CyUSBDescriptor.NONE_LEVEL && dragNode.Level == CyUSBDescriptor.DEVICE_LEVEL ||
                        aNode.Level == CyUSBDescriptor.DEVICE_LEVEL && dragNode.Level == CyUSBDescriptor.DEVICE_LEVEL ||
                        (dragNode.Parent.ImageIndex == destParent.ImageIndex || destParent.Nodes.Count == 0) &&
                        sourceParentDesc.m_value.GetType() == destParentDesc.m_value.GetType()) &&
                        isSubClassEquals)
                    {
                        aNode.BackColor = Color.LightBlue;
                        e.Effect = DragDropEffects.Move;
                        m_oldNode = aNode;
                    }
                }
            }
            if ((m_oldNode != null) && (m_oldNode != aNode))
            {
                m_oldNode.BackColor = m_defaultNodeColor;
                e.Effect = DragDropEffects.None;
            }
        }

        private void treeViewDesc_DragLeave(object sender, EventArgs e)
        {
            if (m_oldNode != null)
            {
                m_oldNode.BackColor = m_defaultNodeColor;
            }
        }

        private void treeViewDesc_DragDrop(object sender, DragEventArgs e)
        {
            if (m_oldNode != null)
            {
                m_oldNode.BackColor = m_defaultNodeColor;
            }

            if (e.Data.GetDataPresent(CyUSBFSParameters.TYPE_TREE_NODE, false))
            {
                Point pt = ((TreeView)sender).PointToClient(new Point(e.X, e.Y));
                TreeNode destinationNode = ((TreeView)sender).GetNodeAt(pt);
                TreeNode newNode = (TreeNode)e.Data.GetData(CyUSBFSParameters.TYPE_TREE_NODE);
                TreeNode sourceParent = newNode.Parent;
                TreeNode destParent;

                if (destinationNode == null)
                    return;

                if (destinationNode.Level == newNode.Level)
                {
                    destParent = destinationNode.Parent;
                }
                else if (destinationNode.Level == newNode.Level - 1)
                {
                    destParent = destinationNode;
                }
                // return if levels are not correspondent
                else return;

                if (destinationNode != newNode)
                {
                    CyDescriptorNode sourceDesc = m_parameters.DeviceTree.GetNodeByKey(newNode.Name);
                    CyDescriptorNode destinationDesc = m_parameters.DeviceTree.GetNodeByKey(destinationNode.Name);
                    CyDescriptorNode sourceParentDesc = m_parameters.DeviceTree.GetNodeByKey(sourceParent.Name);
                    CyDescriptorNode destParentDesc = m_parameters.DeviceTree.GetNodeByKey(destParent.Name);

                    // This part allows drag and drop functionality on Drag Drop level 
                    // 1. Levels must be equals 
                    // 2. D'N'D is not allowed for CyHIDescriptor 
                    // 3. D'N'D is not alloved if the same descriptor is imported two times in different places
                    if ((sourceDesc != null) && (destinationDesc != null) &&
                        (sourceParentDesc != null) && (destParent != null) &&
                        ((sourceDesc != destinationDesc) || sourceDesc.Value is CyInterfaceGeneralDescriptor) &&
                        (destinationNode.Level == CyUSBDescriptor.NONE_LEVEL || 
                        destinationDesc.m_value.GetType() != typeof(CyHIDDescriptor)) &&
                        (destParent.Level == sourceParent.Level))
                    {

                        sourceParentDesc.Nodes.RemoveAt(newNode.Index);
                        if (destinationNode == destParent)
                            destParentDesc.Nodes.Add(sourceDesc);
                        else
                            destParentDesc.Nodes.Insert(destParentDesc.Nodes.IndexOf(destinationDesc), sourceDesc);

                        m_parameters.ParamDeviceTreeChanged();
                        RefreshDeviceTree();
                        treeViewDevice.SelectedNode = treeViewDevice.Nodes.Find(newNode.Name, true)[0];
                    }
                }
            }
        }
        #endregion DragNDrop

        #endregion Events

        #region Save, Import 

        private void toolStripSplitButton_DropDownOpening(object sender, EventArgs e)
        {
            ToolStripMenuItem item = sender == toolStripSplitButtonSave
                       ? saveOneDescriptorToolStripMenuItem : importOneDescriptorToolStripMenuItem;
            if (treeViewDevice.SelectedNode != null)
            {
                CyUSBDescriptor descr = m_parameters.DeviceTree.GetNodeByKey(treeViewDevice.SelectedNode.Name).m_value;
                CyUSBDescriptorType? type;

                if (descr != null)
                    type = descr.bDescriptorType;
                else
                    type = null;

                if ((treeViewDevice.SelectedNode.Level == LEVEL_DEVICE) ||
                    (treeViewDevice.SelectedNode.Level == LEVEL_CONFIGURATION && type != CyUSBDescriptorType.BOS) ||
                    type == CyUSBDescriptorType.ENDPOINT ||
                    type == CyUSBDescriptorType.INTERFACE_ASSOCIATION ||
                    type == CyUSBDescriptorType.CONTAINER_ID ||
                    type == CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY||
                    (treeViewDevice.SelectedNode.Level == LEVEL_INTERFACE))
                {
                    item.Visible = true;
                }
                else
                {
                    item.Visible = false;
                }
            }
            else
            {
                item.Visible = false;
            }
        }

        private void saveOneDescriptorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveMenuItemClick(false);
        }

        private void saveFullConfigToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveMenuItemClick(true);
        }
        
        private void SaveMenuItemClick(bool saveList)
        {
            TreeNode treeNode = treeViewDevice.SelectedNode;
            if (saveList && (m_parameters.DeviceTree.Nodes.Count > 0))
            {
                m_parameters.SaveDescriptorList(m_parameters.DeviceTree.Nodes[0], CyUSBDescriptorType.ALL,
                    m_parameters.templatePath);
            }
            else if (treeNode != null)
            {
                CyDescriptorNode descNode = m_parameters.DeviceTree.GetNodeByKey(treeNode.Name);
                if ((descNode != null) && (descNode.Value != null))
                    m_parameters.SaveDescriptor(descNode.Value, m_parameters.templatePath);
            }
        }

        private void importOneDescriptorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TreeNode selectedNode = treeViewDevice.SelectedNode;
            if (selectedNode != null)
            {
                CyDescriptorNode node = m_parameters.DeviceTree.GetNodeByKey(selectedNode.Name);
                if (node.Value != null)
                {
                    CyUSBDescriptor descNew = m_parameters.ImportDescriptor(node.Value.bDescriptorType,
                        m_parameters.templatePath);
                    if (descNew != null)
                    {
                        if (node.m_value.bDescriptorType == descNew.bDescriptorType)
                        {
                            node.Value = (CyUSBDescriptor)descNew.Clone();
                            SelectedNodeChanged(selectedNode);
                        }
                        else
                            MessageBox.Show(Properties.Resources.MSG_UNABLE_LOAD_TEMPLATE + Environment.NewLine +
                                Properties.Resources.MSG_ERR_DESC_INCOMPATIBLE, Properties.Resources.MSG_TITLE_ERROR, 
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    m_parameters.ParamStringTreeChanged();
                    m_parameters.ParamDeviceTreeChanged();
                    m_parameters.ParamAudioTreeChanged();
                    m_parameters.ParamMidiTreeChanged();
                    m_parameters.ParamCDCTreeChanged();
                    m_parameters.ParamMscTreeChanged();
                }
            }           
        }

        private void importFullConfigurationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (m_parameters.ImportDescriptorList(CyUSBDescriptorType.ALL, string.Empty, m_parameters.templatePath))
            {
                m_parameters.ParamStringTreeChanged();
                m_parameters.ParamHIDReportTreeChanged();
                m_parameters.ParamDeviceTreeChanged();
                m_parameters.ParamAudioTreeChanged();
                m_parameters.ParamMidiTreeChanged();
                m_parameters.ParamCDCTreeChanged();
                m_parameters.ParamMscTreeChanged();
            }
            RefreshDeviceTree();
        }

        private void toolStripSplitButton_ButtonClick(object sender, EventArgs e)
        {
            ((ToolStripSplitButton)sender).ShowDropDown();
        }

        #endregion Save, Import

        #region 'Enter' key override
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Enter)
            {
                SendKeys.Send("{TAB}");
                return true;
            }
            else
                return base.ProcessCmdKey(ref msg, keyData);
        }
        #endregion 'Enter' key override

    }
}
