using System;
using System.Windows.Forms;

namespace DMA_PDL_v2_0.Tabs
{
    partial class CyDescriptorTab
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer m_components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (m_components != null))
            {
                m_components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.m_descriptorPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.m_descriptorsTreeView = new System.Windows.Forms.TreeView();
            this.m_contextMenuStripTree = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.m_copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.m_pasteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.m_contextMenuStripTree.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_descriptorPropertyGrid
            // 
            this.m_descriptorPropertyGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_descriptorPropertyGrid.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.m_descriptorPropertyGrid.Location = new System.Drawing.Point(210, 3);
            this.m_descriptorPropertyGrid.Margin = new System.Windows.Forms.Padding(3, 0, 3, 3);
            this.m_descriptorPropertyGrid.Name = "m_descriptorPropertyGrid";
            this.m_descriptorPropertyGrid.Size = new System.Drawing.Size(424, 431);
            this.m_descriptorPropertyGrid.TabIndex = 1;
            this.m_descriptorPropertyGrid.ToolbarVisible = false;
            this.m_descriptorPropertyGrid.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.m_descriptorPropertyGrid_PropertyValueChanged);
            // 
            // m_descriptorsTreeView
            // 
            this.m_descriptorsTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.m_descriptorsTreeView.ContextMenuStrip = this.m_contextMenuStripTree;
            this.m_descriptorsTreeView.HideSelection = false;
            this.m_descriptorsTreeView.Location = new System.Drawing.Point(3, 3);
            this.m_descriptorsTreeView.Name = "m_descriptorsTreeView";
            this.m_descriptorsTreeView.Size = new System.Drawing.Size(199, 431);
            this.m_descriptorsTreeView.TabIndex = 0;
            this.m_descriptorsTreeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.m_descriptionsTreeView_AfterSelect);
            this.m_descriptorsTreeView.MouseDown += new System.Windows.Forms.MouseEventHandler(this.m_descriptorsTreeView_MouseDown);
            // 
            // m_contextMenuStripTree
            // 
            this.m_contextMenuStripTree.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.m_copyToolStripMenuItem,
            this.m_pasteToolStripMenuItem});
            this.m_contextMenuStripTree.Name = "m_contextMenuStripTree";
            this.m_contextMenuStripTree.Size = new System.Drawing.Size(103, 48);
            this.m_contextMenuStripTree.Opening += new System.ComponentModel.CancelEventHandler(this.m_contextMenuStripTree_Opening);
            // 
            // m_copyToolStripMenuItem
            // 
            this.m_copyToolStripMenuItem.Image = global::DMA_PDL_v2_0.Resources.Copy;
            this.m_copyToolStripMenuItem.Name = "m_copyToolStripMenuItem";
            this.m_copyToolStripMenuItem.Size = new System.Drawing.Size(102, 22);
            this.m_copyToolStripMenuItem.Text = "Copy";
            this.m_copyToolStripMenuItem.Click += new System.EventHandler(this.m_copyToolStripMenuItem_Click);
            // 
            // m_pasteToolStripMenuItem
            // 
            this.m_pasteToolStripMenuItem.Image = global::DMA_PDL_v2_0.Resources.Paste;
            this.m_pasteToolStripMenuItem.Name = "m_pasteToolStripMenuItem";
            this.m_pasteToolStripMenuItem.Size = new System.Drawing.Size(102, 22);
            this.m_pasteToolStripMenuItem.Text = "Paste";
            this.m_pasteToolStripMenuItem.Click += new System.EventHandler(this.m_pasteToolStripMenuItem_Click);
            // 
            // CyDescriptorTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_descriptorsTreeView);
            this.Controls.Add(this.m_descriptorPropertyGrid);
            this.Name = "CyDescriptorTab";
            this.Size = new System.Drawing.Size(638, 437);
            this.Enter += new System.EventHandler(this.CyDescriptorTab_Enter);
            this.m_contextMenuStripTree.ResumeLayout(false);
            this.ResumeLayout(false);

        }



        #endregion
        private System.Windows.Forms.TreeView m_descriptorsTreeView;
        private System.Windows.Forms.PropertyGrid m_descriptorPropertyGrid;
        private ContextMenuStrip m_contextMenuStripTree;
        private System.ComponentModel.IContainer components;
        private ToolStripMenuItem m_copyToolStripMenuItem;
        private ToolStripMenuItem m_pasteToolStripMenuItem;
    }
}
