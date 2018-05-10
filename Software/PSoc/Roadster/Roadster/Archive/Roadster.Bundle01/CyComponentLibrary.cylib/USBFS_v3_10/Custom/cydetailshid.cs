/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Windows.Forms;

namespace USBFS_v3_10
{
    public partial class CyDetailsHID : UserControl
    {
        public CyHIDDescriptor m_descriptor;
        public CyUSBFSParameters m_parameters;

        private const byte DESCRIPTOR_TYPE_HID_ITEM = 255;
        private const byte DESCRIPTOR_TYPE_REPORT_ITEM = 0;
        private const byte DESCRIPTOR_TYPE_PHYSICAL_ITEM = 1;

        private bool m_internalChanges = false;

        public CyDetailsHID(CyHIDDescriptor descriptor, CyUSBFSParameters parameters)
        {
            InitializeComponent();
            m_descriptor = descriptor;
            m_parameters = parameters;
            InitFields();
        }

        private void InitFields()
        {
            m_internalChanges = true;
            for (int i = 0; i < CyUsbConst.CountryCodes.Length; i++)
            {
                comboBoxCountryCode.Items.Add(CyUsbConst.CountryCodes[i]);
            }
            comboBoxCountryCode.SelectedIndex = m_descriptor.bCountryCode;
            switch (m_descriptor.bDescriptorType1)
            {
                case (byte)CyUSBOtherTypes.CyHIDClassDescriptorType.HID:
                    comboBoxType.SelectedIndex = DESCRIPTOR_TYPE_HID_ITEM;
                    break;
                case (byte)CyUSBOtherTypes.CyHIDClassDescriptorType.REPORT:
                    comboBoxType.SelectedIndex = DESCRIPTOR_TYPE_REPORT_ITEM;
                    break;
                case (byte)CyUSBOtherTypes.CyHIDClassDescriptorType.PHYSICAL:
                    comboBoxType.SelectedIndex = DESCRIPTOR_TYPE_PHYSICAL_ITEM;
                    break;
                default:
                    comboBoxType.SelectedIndex = DESCRIPTOR_TYPE_REPORT_ITEM;
                    break;
            }

            FillHIDReports();

            if (m_descriptor.wReportIndex > 0)
            {
                string reportKey = CyDescriptorNode.GetKeyByIndex(m_descriptor.wReportIndex);
                CyDescriptorNode node = m_parameters.HidReportTree.GetNodeByKey(reportKey);
                if (node != null)
                {
                    comboBoxReport.SelectedItem = node.Value;
                }
            }
            m_internalChanges = false;
        }

        private void FillHIDReports()
        {
            comboBoxReport.Items.Clear();
            for (int i = 0; i < m_parameters.HidReportTree.Nodes[0].Nodes.Count; i++)
            {
                CyHIDReportDescriptor report =
                    (CyHIDReportDescriptor) m_parameters.HidReportTree.Nodes[0].Nodes[i].Value;
                comboBoxReport.Items.Add(report);
            }
        }

        #region Validation

        private void comboBoxType_Validated(object sender, EventArgs e)
        {
            switch (comboBoxType.SelectedIndex)
            {
                case DESCRIPTOR_TYPE_HID_ITEM:
                    m_descriptor.bDescriptorType1 = (byte)CyUSBOtherTypes.CyHIDClassDescriptorType.HID;
                    break;
                case DESCRIPTOR_TYPE_REPORT_ITEM:
                    m_descriptor.bDescriptorType1 = (byte)CyUSBOtherTypes.CyHIDClassDescriptorType.REPORT;
                    break;
                case DESCRIPTOR_TYPE_PHYSICAL_ITEM:
                    m_descriptor.bDescriptorType1 = (byte)CyUSBOtherTypes.CyHIDClassDescriptorType.PHYSICAL;
                    break;
            }
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void comboBoxCountryCode_Validated(object sender, EventArgs e)
        {
            m_descriptor.bCountryCode = (byte)comboBoxCountryCode.SelectedIndex;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void comboBoxReport_Validated(object sender, EventArgs e)
        {
            m_descriptor.wReportIndex = CyUSBFSParameters.SaveReportDescriptor(comboBoxReport, m_parameters);
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        #endregion Validation

        private void comboBoxReport_DropDown(object sender, EventArgs e)
        {
            FillHIDReports();
        }

    }
}
