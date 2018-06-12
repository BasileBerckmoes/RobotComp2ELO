/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Windows.Forms;

namespace USBFS_v3_20
{
    public partial class CyDetailsContainerId : UserControl
    {
        #region Members

        private bool m_internalChanges = false;
        private CyContainerIdDescriptor m_descriptor;
        CyUSBFSParameters m_parameters;

        #endregion Members

        #region Constructor

        public CyDetailsContainerId(CyContainerIdDescriptor descriptor, CyUSBFSParameters parameters)
        {
            InitializeComponent();

            m_descriptor = descriptor;
            m_parameters = parameters;

            InitFields();
        }

        #endregion Constructor

        #region Private Methods

        private void InitFields()
        {
            m_internalChanges = true;

            m_tbMaskContainerId.Text = m_descriptor.ContainerId;

            m_internalChanges = false;
        }

        #endregion Private Methods

        #region Events

        private void m_tbMaskContainerId_TextChanged(object sender, EventArgs e)
        {
            m_descriptor.ContainerId = m_tbMaskContainerId.Text;

            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();

            if (CyUSBFSParameters.ContainsOnlyHexChars(m_tbMaskContainerId.Text))
            {
                errorProvider.SetError(m_tbMaskContainerId, string.Empty);
            }
            else
            {
                errorProvider.SetError(m_tbMaskContainerId, Properties.Resources.ERR_UUID_WRONG_FORMAT);
            }
        }
        #endregion Events

    }
}
