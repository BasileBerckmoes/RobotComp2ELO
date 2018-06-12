/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace DMA_Channel_P4_v1_0.Tabs
{
    partial class CyGeneralTab
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyGeneralTab));
            this.m_chbEnableTrIn = new System.Windows.Forms.CheckBox();
            this.m_lbChannelPriority = new System.Windows.Forms.Label();
            this.m_cmbChannelPriority = new System.Windows.Forms.ComboBox();
            this.m_lbNumberOfDescriptors = new System.Windows.Forms.Label();
            this.m_cmbNumberOfDescriptors = new System.Windows.Forms.ComboBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.flowLayoutPanel1.SuspendLayout();
            this.flowLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_chbEnableTrIn
            // 
            resources.ApplyResources(this.m_chbEnableTrIn, "m_chbEnableTrIn");
            this.m_chbEnableTrIn.Name = "m_chbEnableTrIn";
            this.m_chbEnableTrIn.UseVisualStyleBackColor = true;
            // 
            // m_lbChannelPriority
            // 
            resources.ApplyResources(this.m_lbChannelPriority, "m_lbChannelPriority");
            this.m_lbChannelPriority.Name = "m_lbChannelPriority";
            // 
            // m_cmbChannelPriority
            // 
            this.m_cmbChannelPriority.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbChannelPriority.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbChannelPriority, "m_cmbChannelPriority");
            this.m_cmbChannelPriority.Name = "m_cmbChannelPriority";
            // 
            // m_lbNumberOfDescriptors
            // 
            resources.ApplyResources(this.m_lbNumberOfDescriptors, "m_lbNumberOfDescriptors");
            this.m_lbNumberOfDescriptors.Name = "m_lbNumberOfDescriptors";
            // 
            // m_cmbNumberOfDescriptors
            // 
            this.m_cmbNumberOfDescriptors.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbNumberOfDescriptors.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbNumberOfDescriptors, "m_cmbNumberOfDescriptors");
            this.m_cmbNumberOfDescriptors.Name = "m_cmbNumberOfDescriptors";
            // 
            // flowLayoutPanel1
            // 
            resources.ApplyResources(this.flowLayoutPanel1, "flowLayoutPanel1");
            this.flowLayoutPanel1.Controls.Add(this.m_lbChannelPriority);
            this.flowLayoutPanel1.Controls.Add(this.m_cmbChannelPriority);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            // 
            // flowLayoutPanel2
            // 
            resources.ApplyResources(this.flowLayoutPanel2, "flowLayoutPanel2");
            this.flowLayoutPanel2.Controls.Add(this.m_lbNumberOfDescriptors);
            this.flowLayoutPanel2.Controls.Add(this.m_cmbNumberOfDescriptors);
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            // 
            // CyGeneralTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.flowLayoutPanel2);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.m_chbEnableTrIn);
            this.Name = "CyGeneralTab";
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.flowLayoutPanel2.ResumeLayout(false);
            this.flowLayoutPanel2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox m_chbEnableTrIn;
        private System.Windows.Forms.Label m_lbChannelPriority;
        private System.Windows.Forms.ComboBox m_cmbChannelPriority;
        private System.Windows.Forms.Label m_lbNumberOfDescriptors;
        private System.Windows.Forms.ComboBox m_cmbNumberOfDescriptors;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;

    }
}

