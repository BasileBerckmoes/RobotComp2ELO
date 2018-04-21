/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Forms;

namespace USBFS_v3_10
{
    public partial class CyDetailsDevice : UserControl
    {
        private const byte CLASS_NONE_ITEM = 0;
        private const byte CLASS_CDC_ITEM = 1;
        private const byte CLASS_VENDORSPEC_ITEM = 2;

        public CyDeviceDescriptor m_descriptor;
        public CyUSBFSParameters m_parameters;
        private bool m_internalChanges = false;

        public CyDetailsDevice(CyDeviceDescriptor descriptor, CyUSBFSParameters parameters)
        {
            InitializeComponent();
            m_descriptor = descriptor;
            m_parameters = parameters;
            InitFields();
        }

        private void InitFields()
        {
            m_internalChanges = true;
            FillStrings();
            numUpDownVID.Value = m_descriptor.idVendor;
            numUpDownPID.Value = m_descriptor.idProduct;
            numUpDownRelease.Value = m_descriptor.bcdDevice;
            numUpDownProtocol.Value = m_descriptor.bDeviceProtocol;

            // Manufacturer string
            if (m_descriptor.iwManufacturer > 0)
            {
                string configStrKey = CyDescriptorNode.GetKeyByIndex(m_descriptor.iwManufacturer);
                CyDescriptorNode node = m_parameters.StringTree.GetNodeByKey(configStrKey);
                if (node != null)
                {
                    comboBoxManufacter.SelectedItem = node.Value;
                }
            }
            else
            {
                comboBoxManufacter.Text = "";
            }

            // Product string
            if (m_descriptor.iwProduct > 0)
            {
                string configStrKey = CyDescriptorNode.GetKeyByIndex(m_descriptor.iwProduct);
                CyDescriptorNode node = m_parameters.StringTree.GetNodeByKey(configStrKey);
                if (node != null)
                {
                    comboBoxProductString.SelectedItem = node.Value;
                }
            }
            else
            {
                comboBoxProductString.Text = "";
            }

            // Class
            switch (m_descriptor.bDeviceClass)
            {
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_NONE:
                    comboBoxDeviceClass.SelectedIndex = CLASS_NONE_ITEM;
                    break;
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC:
                    comboBoxDeviceClass.SelectedIndex = CLASS_CDC_ITEM;
                    break;
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_VENDORSPEC:
                    comboBoxDeviceClass.SelectedIndex = CLASS_VENDORSPEC_ITEM;
                    break;
                default:
                    comboBoxDeviceClass.Text = m_descriptor.bDeviceClass.ToString("X2");
                    break;
            }
            // Subclass
            switch (m_descriptor.bDeviceSubClass)
            {
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_NONE:
                    comboBoxDeviceSubclass.SelectedIndex = 0;
                    break;
                default:
                    comboBoxDeviceSubclass.Text = m_descriptor.bDeviceSubClass.ToString("X2");
                    break;
            }   

            // Serial Number String
            CyStringDescriptor serialDesc = m_parameters.GetSerialDescriptor();
            if (!serialDesc.bUsed)
                labelSerial.Text = String.Empty;
            else
            {
                switch (serialDesc.snType)
                {
                    case CyStringGenerationType.USER_ENTERED_TEXT:
                        labelSerial.Text = serialDesc.bString;
                        break;
                    case CyStringGenerationType.SILICON_NUMBER:
                        labelSerial.Text = "Silicon Generated SN";
                        break;
                    case CyStringGenerationType.USER_CALL_BACK:
                        labelSerial.Text = "User Call Back";
                        break;
                    default:
                        break;
                }
            }

            // Device number
            int devNumber = -1;
            for (int i = 0; i < m_parameters.DeviceTree.Nodes[0].Nodes.Count; i++)
            {
                if (m_parameters.DeviceTree.Nodes[0].Nodes[i].Value == m_descriptor)
                {
                    devNumber = i;
                    label1DeviceNumber.Text = devNumber.ToString();
                }
            }

            m_internalChanges = false;
        }

        private void FillStrings()
        {
            comboBoxManufacter.Items.Clear();
            comboBoxProductString.Items.Clear();
            List<CyStringDescriptor> strList = m_parameters.GetStringDescList();
            comboBoxManufacter.Items.AddRange(strList.ToArray());
            comboBoxProductString.Items.AddRange(strList.ToArray());
          
        }

        private void ValidateDeviceSubClass()
        {
            if (m_descriptor.bDeviceClass == 0)
            {
                if(m_descriptor.bDeviceSubClass == 0)
                {
                    comboBoxDeviceSubclass.Enabled = false;
                    wrgProvider.SetError(comboBoxDeviceSubclass, string.Empty);
                }
                else
                    wrgProvider.SetError(comboBoxDeviceSubclass, Properties.Resources.WRG_DEVICE_SUBCLASS);
            }
            else
            {
                comboBoxDeviceSubclass.Enabled = true;
                wrgProvider.SetError(comboBoxDeviceSubclass, string.Empty);
            }
        }

        #region Validation

        private void comboBoxDeviceClass_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBoxDeviceClass.SelectedIndex)
            {
                case CLASS_NONE_ITEM:
                    m_descriptor.bDeviceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_NONE;
                    break;
                case CLASS_CDC_ITEM:
                    m_descriptor.bDeviceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC;
                    break;
                case CLASS_VENDORSPEC_ITEM:
                    m_descriptor.bDeviceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_VENDORSPEC;
                    break;
                default:
                    break;
            }
            if (comboBoxDeviceClass.SelectedIndex >= 0)
            {
                errorProvider.SetError(comboBoxDeviceClass, "");
            }
            ValidateDeviceSubClass();

            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }


        private void comboBoxDeviceSubclass_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBoxDeviceSubclass.SelectedIndex)
            {
                case CLASS_NONE_ITEM:
                    m_descriptor.bDeviceSubClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_NONE;
                    break;
                default:
                    break;
            }
            if (comboBoxDeviceSubclass.SelectedIndex >= 0)
            {
                errorProvider.SetError(comboBoxDeviceSubclass, "");
            }
            ValidateDeviceSubClass();

            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void comboBoxManufacter_Validated(object sender, EventArgs e)
        {
            m_descriptor.iwManufacturer = CyUSBFSParameters.SaveStringDescriptor(comboBoxManufacter, m_parameters);
            m_descriptor.sManufacturer = comboBoxManufacter.Text;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void comboBoxProductString_Validated(object sender, EventArgs e)
        {
            m_descriptor.iwProduct = CyUSBFSParameters.SaveStringDescriptor(comboBoxProductString, m_parameters);
            m_descriptor.sProduct = comboBoxProductString.Text;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void numUpDownVID_Validated(object sender, EventArgs e)
        {
            if (m_descriptor.idVendor != Convert.ToUInt16(numUpDownVID.Value))
            {
                m_descriptor.idVendor = Convert.ToUInt16(numUpDownVID.Value);
                if (!m_internalChanges)
                    m_parameters.ParamDeviceTreeChanged();
            }
        }

        private void numUpDownPID_Validated(object sender, EventArgs e)
        {
            if (m_descriptor.idProduct != Convert.ToUInt16(numUpDownPID.Value))
            {
                m_descriptor.idProduct = Convert.ToUInt16(numUpDownPID.Value);
                if (!m_internalChanges)
                    m_parameters.ParamDeviceTreeChanged();
            }
        }

        private void numUpDownRelease_Validated(object sender, EventArgs e)
        {
            if (m_descriptor.bcdDevice != Convert.ToUInt16(numUpDownRelease.Value))
            {
                m_descriptor.bcdDevice = Convert.ToUInt16(numUpDownRelease.Value);
                if (!m_internalChanges)
                    m_parameters.ParamDeviceTreeChanged();
            }
        }

        /// <summary>
        /// Used for Device Class and Subclass comboboxes to handle custom values
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox_Validating(object sender, System.ComponentModel.CancelEventArgs e)
        {
            byte res;
            ComboBox cb = (ComboBox)sender;
            string text = cb.Text;
            if (text.StartsWith("0x"))
                text = text.Remove(0, 2);
            if (cb.SelectedIndex < 0)
            {
                if (Byte.TryParse(text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out res))
                {
                    if (sender == comboBoxDeviceClass)
                        m_descriptor.bDeviceClass = res;
                    else if (sender == comboBoxDeviceSubclass)
                        m_descriptor.bDeviceSubClass = res;

                    ValidateDeviceSubClass();

                    m_parameters.ParamDeviceTreeChanged();
                }

            }
            if (!String.IsNullOrEmpty(errorProvider.GetError(cb)))
                e.Cancel = true;
        }

        /// <summary>
        /// Used for Class and Subclass comboboxes to set errorProvider
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox_TextChanged(object sender, EventArgs e)
        {
            byte res;
            ComboBox cb = (ComboBox)sender;
            string text = cb.Text;
            if (text.StartsWith("0x"))
                text = text.Remove(0, 2);
            if ((cb.SelectedIndex < 0) || (!cb.Items.Contains(text)))
            {
                if (cb.Items.Contains(text))
                {
                    if(text.Length > 2)
                        text = text.Substring(0, 2);
                }

                if (Byte.TryParse(text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out res))
                {
                    errorProvider.SetError(cb, "");

                    if (sender == comboBoxDeviceClass)
                        m_descriptor.bDeviceClass = res;
                    else if (sender == comboBoxDeviceSubclass)
                        m_descriptor.bDeviceSubClass = res;

                    ValidateDeviceSubClass();
                    if (!m_internalChanges)
                        m_parameters.ParamDeviceTreeChanged();
                }
                else
                    errorProvider.SetError(cb,
                                           String.Format(Properties.Resources.MSG_INCORRECT_VALUE_RANGE, "00", "FF"));
            }
            else
            {
                errorProvider.SetError(cb, "");
            }
        }

        private void numUpDownProtocol_ValueChanged(object sender, EventArgs e)
        {
            m_descriptor.bDeviceProtocol = (byte)numUpDownProtocol.Value;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        #endregion Validation
    }
}