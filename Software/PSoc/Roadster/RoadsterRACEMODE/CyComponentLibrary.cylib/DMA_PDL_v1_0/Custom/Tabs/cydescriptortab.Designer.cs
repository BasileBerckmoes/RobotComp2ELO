using System;
using System.Windows.Forms;

namespace DMA_PDL_v1_0.Tabs
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
            this.m_descriptorPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.m_descriptorsTreeView = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // m_descriptorPropertyGrid
            // 
            this.m_descriptorPropertyGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_descriptorPropertyGrid.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.m_descriptorPropertyGrid.Location = new System.Drawing.Point(280, 4);
            this.m_descriptorPropertyGrid.Margin = new System.Windows.Forms.Padding(4, 0, 4, 4);
            this.m_descriptorPropertyGrid.Name = "m_descriptorPropertyGrid";
            this.m_descriptorPropertyGrid.Size = new System.Drawing.Size(565, 531);
            this.m_descriptorPropertyGrid.TabIndex = 1;
            this.m_descriptorPropertyGrid.ToolbarVisible = false;
            this.m_descriptorPropertyGrid.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.m_descriptorPropertyGrid_PropertyValueChanged);
            // 
            // m_descriptorsTreeView
            // 
            this.m_descriptorsTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.m_descriptorsTreeView.HideSelection = false;
            this.m_descriptorsTreeView.Location = new System.Drawing.Point(4, 4);
            this.m_descriptorsTreeView.Margin = new System.Windows.Forms.Padding(4);
            this.m_descriptorsTreeView.Name = "m_descriptorsTreeView";
            this.m_descriptorsTreeView.Size = new System.Drawing.Size(264, 530);
            this.m_descriptorsTreeView.TabIndex = 0;
            this.m_descriptorsTreeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.m_descriptionsTreeView_AfterSelect);
            // 
            // CyDescriptorTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_descriptorsTreeView);
            this.Controls.Add(this.m_descriptorPropertyGrid);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyDescriptorTab";
            this.Size = new System.Drawing.Size(850, 538);
            this.Enter += new System.EventHandler(this.CyDescriptorTab_Enter);
            this.ResumeLayout(false);

        }



        #endregion
        private System.Windows.Forms.TreeView m_descriptorsTreeView;
        private System.Windows.Forms.PropertyGrid m_descriptorPropertyGrid;
    }
}
