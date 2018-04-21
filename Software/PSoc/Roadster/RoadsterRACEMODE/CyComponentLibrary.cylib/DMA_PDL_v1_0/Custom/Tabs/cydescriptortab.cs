/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using DMA_PDL_v1_0.Utils;

namespace DMA_PDL_v1_0.Tabs
{
    internal partial class CyDescriptorTab : CyTabBase, ICyTab
    {
        #region Overrides
        public override IEnumerable<CyCustErr> CheckControlsForErrors()
        {
            //Calling base method is not needed because there no other controls on this tab.
            foreach (CyDmaDescriptionProperties descriptor in m_parameters.Descriptors)
            {
                foreach (string errMsg in descriptor.GetErrors())
                {
                    yield return new CyCustErr(errMsg);
                }
            }
        }
        #endregion

        #region Descriptors methods

        internal void SelectDescriptor(int index)
        {
            if (index < m_parameters.Descriptors.Count)
            {
                CyDmaDescriptionProperties descriptor = m_parameters.Descriptors[index];
                m_descriptorPropertyGrid.SelectedObject = descriptor;
            }
            else
            {
                m_descriptorPropertyGrid.SelectedObject = null;
            }

        }

        internal void UpdateDescriptorsTree()
        {
            m_descriptorsTreeView.BeginUpdate();
            m_descriptorsTreeView.Nodes.Clear();
            foreach (CyDmaDescriptionProperties descriptor in m_parameters.Descriptors)
            {
                TreeNode node = new TreeNode(descriptor.DescriptorName);
                m_descriptorsTreeView.Nodes.Add(node);
            }
            m_descriptorsTreeView.EndUpdate();
            m_descriptorsTreeView.ExpandAll();
        }

        #endregion

        public CyDescriptorTab(CyParameters parameters) :
            base(parameters)
        {
            InitializeComponent();
            CyPropertySite propertiesSite = new CyPropertySite();
            m_descriptorPropertyGrid.Site = propertiesSite;
            UpdateDescriptorsTree();
            m_parameters.NumberOfDescriptorsChanged += new NumberOfDescriptorsEventHandler(NumberOfDescriptorsChanged);
            m_parameters.DescriptorNameGUIChanged += new DescriptorNameGUIEventHandler(DescriptorNameGUIChanged);
        }

        private void NumberOfDescriptorsChanged()
        {
            UpdateDescriptorsTree();
        }

        private void DescriptorNameGUIChanged(string oldName, string newName)
        {
            TreeNode node = FindNodeByName(oldName);
            node.Text = newName;
            m_parameters.SerializeDescriptors();
        }

        TreeNode FindNodeByName(string name)
        {
            return FindNodeByName(m_descriptorsTreeView.TopNode, name);
        }

        TreeNode FindNodeByName(TreeNode root, string name)
        {
            if (root == null) return null;
            if (root.Text == name) return root;
            return FindNodeByName(root.FirstNode, name) ?? FindNodeByName(root.NextNode, name);
        }

        public string TabName
        {
            get
            {
                return CyCustomizer.BASIC_TAB_NAME;
            }
        }

        #region Event handlers
        private void m_descriptorPropertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            m_parameters.SerializeDescriptors();
        }

        private void m_descriptionsTreeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            TreeNode node = m_descriptorsTreeView.SelectedNode;
            SelectDescriptor(node.Index);
        }

        public void UpdateUI()
        {

        }

        private void CyDescriptorTab_Enter(object sender, EventArgs e)
        {
            m_parameters.UpdateDescriptors(m_parameters.NumberOfDescriptors);
            NumberOfDescriptorsChanged();
        }
        #endregion
    }
}
