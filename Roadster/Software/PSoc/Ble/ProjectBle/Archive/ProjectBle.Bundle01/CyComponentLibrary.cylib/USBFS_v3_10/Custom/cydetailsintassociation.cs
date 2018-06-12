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
    public partial class CyDetailsIntAssociation : UserControl
    {
        private const byte CLASS_NONE_ITEM = 0;
        private const byte CLASS_HID_ITEM = 1;
        private const byte CLASS_VENDORSPEC_ITEM = 2;

        private readonly CyInterfaceAssociationDescriptor m_descriptor;
        private readonly CyUSBFSParameters m_parameters;
        private readonly CyDeviceDescriptorPage m_parentFrm;

        public event EventHandler RemoveClassNodeEvent;

        private bool m_internalChanges = false;

        public CyDetailsIntAssociation(CyInterfaceAssociationDescriptor descriptor, CyUSBFSParameters parameters,
                                  CyDeviceDescriptorPage parentForm)
        {
            InitializeComponent();
            m_descriptor = descriptor;
            m_parameters = parameters;
            m_parentFrm = parentForm;
            InitFields();
        }

        protected void OnRemoveClassNodeEvent()
        {
            if (RemoveClassNodeEvent != null)
                RemoveClassNodeEvent(this, EventArgs.Empty);
        }

        private void InitFields()
        {
            m_internalChanges = true;
            FillStrings();
            numUpDownFirstInterface.Value = m_descriptor.bFirstInterface;
            numUpDownInterfaceCount.Value = m_descriptor.bInterfaceCount;
            numUpDownClass.Value = m_descriptor.bFunctionClass;
            numUpDownSubclass.Value = m_descriptor.bFunctionSubClass;
            numUpDownProtocol.Value = m_descriptor.bFunctionProtocol;
            // Interface string
            if (m_descriptor.iwFunction > 0)
            {
                string configStrKey = CyDescriptorNode.GetKeyByIndex(m_descriptor.iwFunction);
                CyDescriptorNode node = m_parameters.StringTree.GetNodeByKey(configStrKey);
                if (node != null)
                {
                    comboBoxInterfaceString.SelectedItem = node.Value;
                }
            }
            else
            {
                comboBoxInterfaceString.Text = "";
            }
            m_internalChanges = false;
        }

        private void FillStrings()
        {
            comboBoxInterfaceString.Items.Clear();
            List<CyStringDescriptor> strList = m_parameters.GetStringDescList();
            comboBoxInterfaceString.Items.AddRange(strList.ToArray());
                
        }

        #region Event handlers
        private void comboBoxInterfaceString_Validated(object sender, EventArgs e)
        {
            m_descriptor.iwFunction = CyUSBFSParameters.SaveStringDescriptor(comboBoxInterfaceString, m_parameters);
            m_descriptor.sFunction = comboBoxInterfaceString.Text;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }


        private void numUpDown_ValueChanged(object sender, EventArgs e)
        {
            byte value = (byte)((NumericUpDown)sender).Value;

            if (sender == numUpDownFirstInterface)
                m_descriptor.bFirstInterface = value;

            if (sender == numUpDownInterfaceCount)
                m_descriptor.bInterfaceCount = value;

            if (sender == numUpDownClass)
                m_descriptor.bFunctionClass = value;

            if (sender == numUpDownSubclass)
                m_descriptor.bFunctionSubClass = value;
            
            if (sender == numUpDownProtocol)
                m_descriptor.bFunctionProtocol = value;
            
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }
        #endregion Event handlers
    }
}
