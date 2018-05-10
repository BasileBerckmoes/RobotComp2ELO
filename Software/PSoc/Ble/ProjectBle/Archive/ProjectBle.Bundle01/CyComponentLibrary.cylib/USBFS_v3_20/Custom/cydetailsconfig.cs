/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace USBFS_v3_20
{
    public partial class CyDetailsConfig : UserControl
    {
        private const int COMBOBOX_DEVICE_BUS_POWERED_INDEX = 0;
        private const int COMBOBOX_DEVICE_SELF_POWERED_INDEX = 1;

        private bool m_internalChanges = false;
        private CyConfigDescriptor m_descriptor;
        private CyUSBFSParameters m_parameters;

        public CyUSBFSParameters Parameters
        {
            get { return m_parameters; }
            set { m_parameters = value; }
        }

        public CyConfigDescriptor Descriptor
        {
            get { return m_descriptor; }
            set { m_descriptor = value; }
        }

        public CyDetailsConfig(CyConfigDescriptor descriptor, CyUSBFSParameters parameters)
        {
            InitializeComponent();
            Descriptor = descriptor;
            Parameters = parameters;
            InitFields();
        }

        private void InitFields()
        {
            m_internalChanges = true;
            comboBoxConfigString.Text = "";
            numUpDownMaxPower.Value = (Descriptor.bMaxPower * 2);
            comboBoxDevicePower.SelectedIndex = (Descriptor.bmAttributes & 0x40) == 0 ? 0 : 1;
            comboBoxRemoteWakeup.SelectedIndex = (Descriptor.bmAttributes & 0x20) == 0 ? 0 : 1;

            // Configuration string
            FillConfigStrings();

            if (Descriptor.iwConfiguration > 0)
            {
                string configStrKey = CyDescriptorNode.GetKeyByIndex(Descriptor.iwConfiguration);
                CyDescriptorNode node = Parameters.StringTree.GetNodeByKey(configStrKey);
                if (node != null)
                {
                    comboBoxConfigString.SelectedItem = node.Value;
                }
            }
            else
            {
                comboBoxConfigString.Text = "";
            }
            m_internalChanges = false;
        }

        private void comboBoxConfigString_DropDown(object sender, EventArgs e)
        {
            FillConfigStrings();
        }

        private void FillConfigStrings()
        {
            comboBoxConfigString.Items.Clear();
            List<CyStringDescriptor> strList = Parameters.GetStringDescList();
            comboBoxConfigString.Items.AddRange(strList.ToArray());
        }

        #region Validation

        private void ValidateMaxPower()
        {
            if (comboBoxDevicePower.SelectedIndex == COMBOBOX_DEVICE_BUS_POWERED_INDEX &&
                numUpDownMaxPower.Value == 0)
            {
                warningProvider.SetError(numUpDownMaxPower, Properties.Resources.WRG_MAX_POWER);
            }
            else
            {
                warningProvider.SetError(numUpDownMaxPower, string.Empty);
            }
        }

        private void ValidateSelfPoweredVbusMonitoring()
        {
            if (comboBoxDevicePower.SelectedIndex == COMBOBOX_DEVICE_SELF_POWERED_INDEX &&
                !Parameters.Mon_vbus)
            {
                warningProvider.SetError(comboBoxDevicePower, Properties.Resources.WRG_DEVICE_SELF_POVERED_MONIT);
            }
            else
            {
                warningProvider.SetError(comboBoxDevicePower, string.Empty);
            }
        }

        private void comboBoxConfigString_Validated(object sender, EventArgs e)
        {
            Descriptor.iwConfiguration = CyUSBFSParameters.SaveStringDescriptor(comboBoxConfigString, Parameters);
            Descriptor.sConfiguration = comboBoxConfigString.Text;
            if (!m_internalChanges)
                Parameters.ParamDeviceTreeChanged();
        }

        private void comboBoxDevicePower_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((comboBoxDevicePower.SelectedIndex >= 0) && (comboBoxRemoteWakeup.SelectedIndex >= 0))
            {
                byte devicePower = (byte) comboBoxDevicePower.SelectedIndex;
                byte remoteWakeup = (byte) comboBoxRemoteWakeup.SelectedIndex;
                Descriptor.bmAttributes = (byte)((1 << CyConfigDescriptor.BMATTRIBUTES_RESERVED_OFFSET) |
                    (devicePower << CyConfigDescriptor.DEVICE_POWER_OFFSET) | 
                    (remoteWakeup << CyConfigDescriptor.REMOTE_WAKEUP_OFFSET));
                if (!m_internalChanges)
                    Parameters.ParamDeviceTreeChanged();

                ValidateSelfPoweredVbusMonitoring();
                ValidateMaxPower();
            }
        }

        private void numUpDownMaxPower_ValueChanged(object sender, EventArgs e)
        {
            Descriptor.bMaxPower = (byte)(Convert.ToUInt16(numUpDownMaxPower.Value) / 2);
            if (!m_internalChanges)
                Parameters.ParamDeviceTreeChanged();

            numUpDownMaxPower.Value = Descriptor.bMaxPower * 2;

            ValidateMaxPower();
        }
        #endregion Validation

    }
}
