/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Reflection;
using CyDesigner.Extensions.Common;

namespace USBFS_v3_20
{
    public partial class CyCDCDescriptorPage : CyBaseDescriptorPage
    {
        #region Constructors

        public CyCDCDescriptorPage() 
            : base ()
        {
            InitializeComponent();
        }

        public CyCDCDescriptorPage(CyUSBFSParameters parameters)
            : base(parameters, CyUSBDescriptorType.CDC)
        {
            InitializeComponent();
            InitAdditionalCheckBoxes();
        }

        #endregion Constructors

        //------------------------------------------------------------------------------------------------------------

        #region CyEditingWrapperControl override
        public override string TabName
        {
            get { return CyCustomizer.PARAM_TAB_NAME_CDC; }
        }

        public override IEnumerable<CyCustErr> GetErrors()
        {
            // Save all changes before closing the customizer
            m_parameters.SerializedCDCDesc = m_parameters.SerializeDescriptorTree(m_parameters.CdcTree);

            return base.GetErrors();
        }
        #endregion

        //------------------------------------------------------------------------------------------------------------

        #region Initialization

        public void InitAdditionalCheckBoxes()
        {
            checkBoxEnableCDCApi.Checked = m_parameters.EnableCDCApi;
        }

        /// <summary>
        /// Initializes m_reportItems list and fills listBoxItems listBox.
        /// </summary>
        protected override void InitItems()
        {
            m_ItemsList = new List<CyUSBDescriptor>();

            m_ItemsList.Add(new CyCommunicationsInterfaceDescriptor());
            m_ItemsList.Add(new CyDataInterfaceDescriptor());

            ((CyCDCInterfaceDescriptor)m_ItemsList[0]).bInterfaceClass = 
                                            (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC;
            ((CyCDCInterfaceDescriptor)m_ItemsList[1]).bInterfaceClass = 
                                            (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_DATA;

            m_ItemsList.Add(new CyCDCHeaderDescriptor());
            m_ItemsList.Add(new CyCDCUnionDescriptor());
            m_ItemsList.Add(new CyCDCCountrySelectionDescriptor());
            m_ItemsList.Add(new CyCDCCallManagementDescriptor());
            m_ItemsList.Add(new CyCDCAbstractControlMgmtDescriptor());

            m_ItemsList.Add(new CyEndpointDescriptor());
        }


        protected override bool IncludeACListItems(CyDescriptorNode interfaceNode)
        {
            bool includeAC = false;
            if (interfaceNode.Value is CyCDCInterfaceDescriptor)
            {
                if (((CyCDCInterfaceDescriptor)interfaceNode.Value).bInterfaceClass ==
                    (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC)
                {
                    includeAC = true;
                }
            }
            return includeAC;
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
                    item.Text = ((CyInterfaceDescriptor) m_ItemsList[i]).bInterfaceClass ==
                                (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC
                                    ? "Communications"
                                    : "Data";
                    listViewDescList.Items.Add(item);
                }
                else if (((m_ItemsList[i] is CyCDCHeaderDescriptor) ||
                          (m_ItemsList[i] is CyCDCUnionDescriptor) ||
                          (m_ItemsList[i] is CyCDCCountrySelectionDescriptor) ||
                          (m_ItemsList[i] is CyCDCCallManagementDescriptor) ||
                          (m_ItemsList[i] is CyCDCAbstractControlMgmtDescriptor)) && includeAC)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_COMM];
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

        private void checkBoxEnableCDCApi_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.EnableCDCApi = checkBoxEnableCDCApi.Checked;
        }

        #endregion Events
    }
}
