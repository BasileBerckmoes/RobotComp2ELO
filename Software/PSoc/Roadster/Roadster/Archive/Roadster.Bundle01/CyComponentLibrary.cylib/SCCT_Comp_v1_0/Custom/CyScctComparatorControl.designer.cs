/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace SCCT_Comp_v1_0
{
    partial class CyScctComparatorControl
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyScctComparatorControl));
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pbox_waveform = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.m_rbPolarity_Inve = new System.Windows.Forms.RadioButton();
            this.m_rbPolarity_NonInve = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.m_rbSync_Bypass = new System.Windows.Forms.RadioButton();
            this.m_rbSync_Norm = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbox_waveform)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox2
            // 
            resources.ApplyResources(this.pictureBox2, "pictureBox2");
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.TabStop = false;
            // 
            // pbox_waveform
            // 
            this.pbox_waveform.BackColor = System.Drawing.Color.White;
            resources.ApplyResources(this.pbox_waveform, "pbox_waveform");
            this.pbox_waveform.Name = "pbox_waveform";
            this.pbox_waveform.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.m_rbPolarity_Inve);
            this.groupBox1.Controls.Add(this.m_rbPolarity_NonInve);
            resources.ApplyResources(this.groupBox1, "groupBox1");
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.TabStop = false;
            // 
            // m_rbPolarity_Inve
            // 
            resources.ApplyResources(this.m_rbPolarity_Inve, "m_rbPolarity_Inve");
            this.m_rbPolarity_Inve.Name = "m_rbPolarity_Inve";
            this.m_rbPolarity_Inve.TabStop = true;
            this.m_rbPolarity_Inve.UseVisualStyleBackColor = true;
            this.m_rbPolarity_Inve.CheckedChanged += new System.EventHandler(this.m_rbPolarity_CheckedChanged);
            // 
            // m_rbPolarity_NonInve
            // 
            resources.ApplyResources(this.m_rbPolarity_NonInve, "m_rbPolarity_NonInve");
            this.m_rbPolarity_NonInve.Name = "m_rbPolarity_NonInve";
            this.m_rbPolarity_NonInve.TabStop = true;
            this.m_rbPolarity_NonInve.UseVisualStyleBackColor = true;
            this.m_rbPolarity_NonInve.CheckedChanged += new System.EventHandler(this.m_rbPolarity_CheckedChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.m_rbSync_Bypass);
            this.groupBox2.Controls.Add(this.m_rbSync_Norm);
            resources.ApplyResources(this.groupBox2, "groupBox2");
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.TabStop = false;
            // 
            // m_rbSync_Bypass
            // 
            resources.ApplyResources(this.m_rbSync_Bypass, "m_rbSync_Bypass");
            this.m_rbSync_Bypass.Name = "m_rbSync_Bypass";
            this.m_rbSync_Bypass.TabStop = true;
            this.m_rbSync_Bypass.UseVisualStyleBackColor = true;
            this.m_rbSync_Bypass.CheckedChanged += new System.EventHandler(this.m_rbSync_CheckedChanged);
            // 
            // m_rbSync_Norm
            // 
            resources.ApplyResources(this.m_rbSync_Norm, "m_rbSync_Norm");
            this.m_rbSync_Norm.Name = "m_rbSync_Norm";
            this.m_rbSync_Norm.TabStop = true;
            this.m_rbSync_Norm.UseVisualStyleBackColor = true;
            this.m_rbSync_Norm.CheckedChanged += new System.EventHandler(this.m_rbSync_CheckedChanged);
            // 
            // CyScctComparatorControl
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pbox_waveform);
            this.Name = "CyScctComparatorControl";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbox_waveform)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pbox_waveform;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton m_rbSync_Bypass;
        private System.Windows.Forms.RadioButton m_rbSync_Norm;
        private System.Windows.Forms.RadioButton m_rbPolarity_Inve;
        private System.Windows.Forms.RadioButton m_rbPolarity_NonInve;
    }
}


//[] END OF FILE
