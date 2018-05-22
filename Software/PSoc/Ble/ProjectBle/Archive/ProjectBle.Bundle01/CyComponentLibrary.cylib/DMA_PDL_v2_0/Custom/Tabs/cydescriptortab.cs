/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using DMA_PDL_v2_0.Utils;

namespace DMA_PDL_v2_0.Tabs
{
    internal partial class CyDescriptorTab : CyTabBase, ICyTab
    {
        #region Fields
        private TreeNode m_mouseSelectedNode; // Is used for context menu
        private CyDmaDescriptionProperties m_copiedDescriptor = null; // Descriptor which stores copied values
        #endregion

        #region Constructor
        public CyDescriptorTab(CyParameters parameters) :
            base(parameters)
        {
            InitializeComponent();
            CyPropertySite propertiesSite = new CyPropertySite();
            m_descriptorPropertyGrid.Site = propertiesSite;
            m_parameters.NumberOfDescriptorsChanged += new NumberOfDescriptorsEventHandler(NumberOfDescriptorsChanged);
            m_parameters.DescriptorNameGUIChanged += new DescriptorNameGUIEventHandler(DescriptorNameGUIChanged);
        }
        #endregion

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

        #region ICyTab implementation
        public string TabName
        {
            get
            {
                return CyCustomizer.BASIC_TAB_NAME;
            }
        }

        public void UpdateUI()
        {
            UpdateDescriptorsTree();
        }
        #endregion

        #region Private methods
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

        private TreeNode FindNodeByName(string name)
        {
            return FindNodeByName(m_descriptorsTreeView.TopNode, name);
        }

        private TreeNode FindNodeByName(TreeNode root, string name)
        {
            if (root == null) return null;
            if (root.Text == name) return root;
            return FindNodeByName(root.FirstNode, name) ?? FindNodeByName(root.NextNode, name);
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

            if (m_descriptorsTreeView.Nodes.Count > 0)
                m_descriptorsTreeView.SelectedNode = m_descriptorsTreeView.Nodes[0];
        }

        private void CopyDescriptor()
        {
            if (m_descriptorsTreeView.SelectedNode == null)
                return;

            CyDmaDescriptionProperties sourceDescriptor = null;
            string sourceDescriptorName = m_descriptorsTreeView.SelectedNode.Text;
            for (int i = 0; i < m_parameters.Descriptors.Count; i++)
            {
                if (m_parameters.Descriptors[i].DescriptorName == sourceDescriptorName)
                {
                    sourceDescriptor = m_parameters.Descriptors[i];
                    break;
                }
            }
            if (sourceDescriptor != null)
            {
                m_copiedDescriptor = new CyDmaDescriptionProperties();
                sourceDescriptor.CopyValuesTo(m_copiedDescriptor);
            }
        }

        private void PasteDescriptor()
        {
            if (m_descriptorsTreeView.SelectedNode == null || m_copiedDescriptor == null)
                return;

            CyDmaDescriptionProperties destinationDescriptor = null;
            string destinationDescriptorName = m_descriptorsTreeView.SelectedNode.Text;
            for (int i = 0; i < m_parameters.Descriptors.Count; i++)
            {
                if (m_parameters.Descriptors[i].DescriptorName == destinationDescriptorName)
                {
                    destinationDescriptor = m_parameters.Descriptors[i];
                    break;
                }
            }
            if (destinationDescriptor != null)
            {
                m_copiedDescriptor.CopyValuesTo(destinationDescriptor);
            }
            m_descriptorPropertyGrid.Refresh();
        }
        #endregion

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

        private void CyDescriptorTab_Enter(object sender, EventArgs e)
        {
            m_parameters.UpdateDescriptors(m_parameters.NumberOfDescriptors);
            NumberOfDescriptorsChanged();
        }

        private void m_descriptorsTreeView_MouseDown(object sender, MouseEventArgs e)
        {
            m_mouseSelectedNode = m_descriptorsTreeView.GetNodeAt(e.X, e.Y);
        }

        private void m_contextMenuStripTree_Opening(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (m_mouseSelectedNode == null)
            {
                e.Cancel = true;
                return;
            }
            m_descriptorsTreeView.SelectedNode = m_mouseSelectedNode;
            // Disable Paste command if there is nothing to paste
            m_pasteToolStripMenuItem.Enabled = m_copiedDescriptor != null;
        }

        private void m_copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CopyDescriptor();
        }

        private void m_pasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PasteDescriptor();
        }
        #endregion

        #region ProcessCmdKey override
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            bool result = true;

            if ((keyData == (Keys.Control | Keys.C)) && m_descriptorsTreeView.Focused)
            {
                CopyDescriptor();
            }
            else if ((keyData == (Keys.Control | Keys.V)) && m_descriptorsTreeView.Focused)
            {
                PasteDescriptor();
            }
            else
            {
                result = base.ProcessCmdKey(ref msg, keyData);
            }

            return result;
        }
        #endregion
    }
}
