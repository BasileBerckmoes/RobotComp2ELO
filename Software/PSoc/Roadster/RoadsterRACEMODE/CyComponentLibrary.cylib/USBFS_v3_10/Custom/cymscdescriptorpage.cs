/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;

namespace USBFS_v3_10
{
    public partial class CyMassStoragePage: CyBaseDescriptorPage
    {
        #region CyEditingWrapperControl override
        public override string TabName
        {
            get { return CyCustomizer.PARAM_TAB_NAME_MASS_STORAGE; }
        }
        #endregion

        #region Constructors
        public CyMassStoragePage(CyUSBFSParameters parameters)
            : base(parameters, CyUSBDescriptorType.MSC)
        {
            InitializeComponent();
            InitAdditionalControls();
        }
        #endregion Constructors

        #region Initialization
        public void InitAdditionalControls()
        {
            m_lblNumLun.Enabled = m_numericLun.Enabled =
                m_chbHandleMscRequests.Checked = m_parameters.HandleMscRequests;

            // Update Logical Units Number
            if (m_parameters.MscLogicalUnitsNum > m_numericLun.Maximum)
                m_numericLun.Value = m_numericLun.Maximum;
            else if (m_parameters.MscLogicalUnitsNum < m_numericLun.Minimum)
                m_numericLun.Value = m_numericLun.Minimum;
            else
                m_numericLun.Value = m_parameters.MscLogicalUnitsNum;
        }

        protected override void InitItems()
        {
            m_ItemsList = new List<CyUSBDescriptor>();

            m_ItemsList.Add(new CyMscInterfaceDescriptor());
            m_ItemsList.Add(new CyEndpointDescriptor());
        }

        protected override bool IncludeACListItems(CyDescriptorNode interfaceNode)
        {
            return interfaceNode.m_value is CyMscInterfaceDescriptor;
        }

        protected override void FillListViewItems(bool includeInterface, bool includeAC, bool includeAS, bool includeEP,
            bool includeASEP)
        {
            listViewDescList.BeginUpdate();
            listViewDescList.Items.Clear();
            for (int i = 0; i < m_ItemsList.Count; i++)
            {
                ListViewItem item = new ListViewItem(m_ItemsList[i].ToString());
                item.ImageIndex = 5;
                item.Tag = i;

                if (m_ItemsList[i] is CyInterfaceDescriptor && includeInterface)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_INTERACE];
                    item.Text = "MSC Interface";
                    listViewDescList.Items.Add(item);
                }
                else if ((m_ItemsList[i] is CyEndpointDescriptor) && includeEP)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_ENDPOINT];
                    listViewDescList.Items.Add(item);
                }
            }
            listViewDescList.EndUpdate();
        }
        #endregion Initialization

        #region Events
        private void m_chbEnMscRequests_CheckedChanged(object sender, EventArgs e)
        {
            m_lblNumLun.Enabled = m_numericLun.Enabled = 
                m_parameters.HandleMscRequests = m_chbHandleMscRequests.Checked;
        }

        private void m_numericLun_ValueChanged(object sender, EventArgs e)
        {
            m_parameters.MscLogicalUnitsNum = (byte)m_numericLun.Value;
        }
        #endregion Events
    }
}
