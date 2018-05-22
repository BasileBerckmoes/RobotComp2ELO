/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;

namespace MDIO_Interface_v1_20.Tabs
{
    public partial class CyBasicTab : CyEditingWrapperControl
    {
        #region Class properties
        public override string TabName
        {
            get { return CyCustomizer.GENERAL_TAB_NAME; }
        }
        #endregion

        #region Constructor(s)
        public CyBasicTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();
            
            m_params = param;
            m_params.m_basicTab = this;

            // Initialize combobox
            cbDeviceAddress.Items.Clear();
            foreach (CyEDeviceAddressType item in Enum.GetValues(typeof(CyEDeviceAddressType)))
            {
                if (item != CyEDeviceAddressType.UNKNOWN)
                    cbDeviceAddress.Items.Add(item);
            }
        }
        #endregion

        #region Initialization
        public void UpdateUI()
        {
            rbBasicConfig.Checked = (m_params.OperationMode == CyEOperationModeType.BASIC);
            rbAdvancedConfig.Checked = (m_params.OperationMode == CyEOperationModeType.ADVANCED);
            rbHardware.Checked = (m_params.PhysicalAddressMode == CyEPhysicalAddressType.HARDWARE);
            rbFirmware.Checked = (m_params.PhysicalAddressMode == CyEPhysicalAddressType.FIRMWARE);
            rbAddressWidth3.Checked = (m_params.PhysicalAddressWidth == CyEPhysicalAddressWidth.BIT_3);
            rbAddressWidth5.Checked = (m_params.PhysicalAddressWidth == CyEPhysicalAddressWidth.BIT_5);
            tbPhysicalAddress.Text = CyParameters.ConvertDecToHexWithoutPrefix(m_params.PhysicalAddress);
            chbEnableExternalOE.Checked = m_params.EnableExternOE;
            // Update Device Address combobox with Expression View handling
            string errorMessage = string.Empty;

            if (m_params.DeviceAddress != CyEDeviceAddressType.UNKNOWN)
            {
                RemoveEmptyItem(cbDeviceAddress);
                cbDeviceAddress.SelectedItem = m_params.DeviceAddress;
                RemoveEmptyItem(cbDeviceAddress);
            }
            else
            {
                errorMessage = string.Format(Resources.UnrecognizableFormat, CyParamNames.DEVICE_ADDRESS);
                SetEmptyItem(cbDeviceAddress);
            }
            m_errorProvider.SetError(cbDeviceAddress, errorMessage);
        }

        private void SetEmptyItem(ComboBox comboBox)
        {
            if (comboBox.Items.Contains(CyEDeviceAddressType.UNKNOWN) == false)
            {
                comboBox.Items.Insert(0, CyEDeviceAddressType.UNKNOWN);
                bool currentGEM = m_params.GlobalEditMode;
                m_params.GlobalEditMode = false;
                comboBox.SelectedIndex = 0;
                m_params.GlobalEditMode = currentGEM;
            }
        }

        private void RemoveEmptyItem(ComboBox comboBox)
        {
            if (comboBox.Items.Contains(CyEDeviceAddressType.UNKNOWN))
                comboBox.Items.Remove(CyEDeviceAddressType.UNKNOWN);
        }
        #endregion

        #region Event Handlers
        private void cbDeviceAddress_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((CyEDeviceAddressType)cbDeviceAddress.SelectedItem != CyEDeviceAddressType.UNKNOWN)
            {
                m_params.DeviceAddress = (CyEDeviceAddressType)cbDeviceAddress.SelectedItem;
                RemoveEmptyItem(cbDeviceAddress);
            }
            m_errorProvider.SetError(cbDeviceAddress, string.Empty);
        }

        private void rbConfig_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioBox = (RadioButton)sender;
            if (radioBox.Checked == false)
            {
                return;
            }
            if (radioBox == rbBasicConfig)
            {
                m_params.OperationMode = CyEOperationModeType.BASIC;
                m_params.m_editor.HideCustomPage(Resources.AdvancedTabDisplayName);
            }
            else
            {
                m_params.OperationMode = CyEOperationModeType.ADVANCED;
                m_params.m_editor.ShowCustomPage(Resources.AdvancedTabDisplayName);
            }
        }

        private void rbPhAddress_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioBox = (RadioButton)sender;
            if (radioBox.Checked == false)
            {
                return;
            }
            if (radioBox == rbHardware)
            {
                m_params.PhysicalAddressMode = CyEPhysicalAddressType.HARDWARE;
            }
            else
            {
                m_params.PhysicalAddressMode = CyEPhysicalAddressType.FIRMWARE;
            }
            tbPhysicalAddress.Enabled = (m_params.PhysicalAddressMode == CyEPhysicalAddressType.FIRMWARE);
            lbl0x.Enabled = tbPhysicalAddress.Enabled;
            labelPhysicalAddress.Enabled = tbPhysicalAddress.Enabled;

            // Reset physical address if it's incorrect and disabled
            if (tbPhysicalAddress.Enabled == false && m_params.PhysicalAddress > CyParamRanges.PHYS_ADDRESS_5BIT_MAX)
            {
                tbPhysicalAddress.Text = CyParameters.ConvertDecToHexWithoutPrefix(m_params.GetMaxAddressByWidth());
            }

            tbPhysicalAddress_TextChanged(tbPhysicalAddress, EventArgs.Empty);
        }

        private void rbAddressWidth_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioBox = (RadioButton)sender;
            if (radioBox.Checked == false)
            {
                return;
            }
            m_params.PhysicalAddressWidth = (radioBox == rbAddressWidth3)
                ? CyEPhysicalAddressWidth.BIT_3
                : CyEPhysicalAddressWidth.BIT_5;

            tbPhysicalAddress_TextChanged(tbPhysicalAddress, EventArgs.Empty);
        }

        private void chbEnableExternalOE_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EnableExternOE = chbEnableExternalOE.Checked;
        }

        private void tbPhysicalAddress_TextChanged(object sender, EventArgs e)
        {
            byte? value;
            try
            {
                value = (byte)CyParameters.ConvertHexToDec(tbPhysicalAddress.Text, false);
            }
            catch (Exception)
            {
                value = null;
            }
            string message = string.Format(Resources.PhysicalAddressOutOfRange,
                                           CyParameters.ConvertDecToHex(CyParamRanges.PHYS_ADDRESS_MIN),
                                           CyParameters.ConvertDecToHex(m_params.GetMaxAddressByWidth()));
           
            // Update error provider
            if (tbPhysicalAddress.Enabled == false)
            {
                m_errorProvider.SetError(tbPhysicalAddress, string.Empty);
            }
            else if (value != null)
            {
                if (value < CyParamRanges.PHYS_ADDRESS_MIN || value > m_params.GetMaxAddressByWidth())
                {
                    m_errorProvider.SetError(tbPhysicalAddress, message);
                }
                else
                {
                    m_errorProvider.SetError(tbPhysicalAddress, string.Empty);
                }
            }
            else
            {
                m_errorProvider.SetError(tbPhysicalAddress, message);
            }
            m_params.PhysicalAddress = value;
        }

        private void cbDeviceAddress_Format(object sender, ListControlConvertEventArgs e)
        {
            e.Value = CyParameters.GetEnumDisplayName(e.ListItem);
        }
        #endregion
    }
}
