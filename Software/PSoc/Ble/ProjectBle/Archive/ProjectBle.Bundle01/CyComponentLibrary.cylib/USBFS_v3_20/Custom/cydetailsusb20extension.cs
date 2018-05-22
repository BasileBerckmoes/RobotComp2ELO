/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace USBFS_v3_20
{
    public partial class CyDetailsUsb20Extension : UserControl
    {
        #region Members

        private bool m_internalChanges = false;
        private CyUsb20ExtensionDeviceCapabilityDescriptor m_descriptor;
        CyUSBFSParameters m_parameters;

        #endregion Members

        public CyDetailsUsb20Extension(CyUsb20ExtensionDeviceCapabilityDescriptor descriptor, CyUSBFSParameters parameters)
        {
            InitializeComponent();

            m_descriptor = descriptor;
            m_parameters = parameters;

            #region Add Event Handlers
            checkBoxEnableLPM.CheckedChanged += checkBoxes_CheckedChanged;
            checkBoxBaselineBESL.CheckedChanged += checkBoxes_CheckedChanged;
            checkBoxDeepBESL.CheckedChanged += checkBoxes_CheckedChanged;

            numBaselineBESL.ValueChanged += nums_ValueChanged;
            numDeepBESL.ValueChanged += nums_ValueChanged;
            #endregion Add Event Handlers

            InitFields();
        }


        #region Private Methods

        private void InitFields()
        {
            m_internalChanges = true;

            numBaselineBESL.Value = m_descriptor.BaselineBeslValue;
            numDeepBESL.Value = m_descriptor.DeepBeslValue;

            checkBoxBaselineBESL.Checked = m_descriptor.BaselineBeslValid;
            checkBoxDeepBESL.Checked = m_descriptor.DeepBeslValid;
            checkBoxEnableLPM.Checked = m_descriptor.Lpm;

            UpdateUiVisibility();
            m_internalChanges = false;
        }

        private void UpdateUiVisibility()
        {
            bool isLPM = checkBoxEnableLPM.Checked;
            bool isBaselineBESL = checkBoxBaselineBESL.Checked;
            bool isBoxDeepBESL = checkBoxDeepBESL.Checked;

            checkBoxBaselineBESL.Enabled = isLPM;
            checkBoxDeepBESL.Enabled = isLPM;

            label0xBaselineBESL.Enabled = numBaselineBESL.Enabled = isLPM && isBaselineBESL;
            label0xDeepBESL.Enabled = numDeepBESL.Enabled = isLPM && isBoxDeepBESL;
        }

        #endregion Private Methods

        #region Events

        private void checkBoxes_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox checkBoxSender = (CheckBox)sender;

            UpdateUiVisibility();

            if (checkBoxSender == checkBoxEnableLPM)
            {
                m_descriptor.Lpm = checkBoxSender.Checked;

                if (!checkBoxSender.Checked)
                {
                    checkBoxBaselineBESL.Checked = false;
                    checkBoxDeepBESL.Checked = false;
                }
            }
            else if (checkBoxSender == checkBoxBaselineBESL)
            {
                m_descriptor.BaselineBeslValid = checkBoxSender.Checked;

                if (!checkBoxSender.Checked)
                    numBaselineBESL.Value = 0;
            }
            else if (checkBoxSender == checkBoxDeepBESL)
            {
                m_descriptor.DeepBeslValid = checkBoxSender.Checked;

                if (!checkBoxSender.Checked)
                    numDeepBESL.Value = 0;
            }
            else
            {
                Debug.Fail("Not handled parameter.");
            }

            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void nums_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown numSender = (NumericUpDown)sender;

            if (numSender == numBaselineBESL)
            {
                m_descriptor.BaselineBeslValue = (uint)numSender.Value;
            }
            else if (numSender == numDeepBESL)
            {
                m_descriptor.DeepBeslValue = (uint)numSender.Value;
            }
            else
            {
                Debug.Fail("Not handled parameter.");
            }

            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        #endregion Events
    }
}
