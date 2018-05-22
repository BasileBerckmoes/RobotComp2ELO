/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


namespace TCPWM_P4_v2_10
{
    partial class CyTCPWMTab
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
            this.groupBoxSignals = new System.Windows.Forms.GroupBox();
            this.cbSignalCapture = new System.Windows.Forms.CheckBox();
            this.cbSignalStop = new System.Windows.Forms.CheckBox();
            this.cbSignalStart = new System.Windows.Forms.CheckBox();
            this.cbSignalCount = new System.Windows.Forms.CheckBox();
            this.cbSignalReload = new System.Windows.Forms.CheckBox();
            this.groupBoxSignals.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxSignals
            // 
            this.groupBoxSignals.Controls.Add(this.cbSignalCapture);
            this.groupBoxSignals.Controls.Add(this.cbSignalStop);
            this.groupBoxSignals.Controls.Add(this.cbSignalStart);
            this.groupBoxSignals.Controls.Add(this.cbSignalCount);
            this.groupBoxSignals.Controls.Add(this.cbSignalReload);
            this.groupBoxSignals.Location = new System.Drawing.Point(3, 3);
            this.groupBoxSignals.Name = "groupBoxSignals";
            this.groupBoxSignals.Size = new System.Drawing.Size(155, 137);
            this.groupBoxSignals.TabIndex = 0;
            this.groupBoxSignals.TabStop = false;
            this.groupBoxSignals.Text = "Input signals";
            // 
            // cbSignalCapture
            // 
            this.cbSignalCapture.AutoSize = true;
            this.cbSignalCapture.Location = new System.Drawing.Point(6, 111);
            this.cbSignalCapture.Name = "cbSignalCapture";
            this.cbSignalCapture.Size = new System.Drawing.Size(103, 17);
            this.cbSignalCapture.TabIndex = 5;
            this.cbSignalCapture.Text = "capture / switch";
            this.cbSignalCapture.UseVisualStyleBackColor = true;
            this.cbSignalCapture.CheckedChanged += new System.EventHandler(this.cbSignal_CheckedChanged);
            // 
            // cbSignalStop
            // 
            this.cbSignalStop.AutoSize = true;
            this.cbSignalStop.Location = new System.Drawing.Point(6, 88);
            this.cbSignalStop.Name = "cbSignalStop";
            this.cbSignalStop.Size = new System.Drawing.Size(69, 17);
            this.cbSignalStop.TabIndex = 4;
            this.cbSignalStop.Text = "stop / kill";
            this.cbSignalStop.UseVisualStyleBackColor = true;
            this.cbSignalStop.CheckedChanged += new System.EventHandler(this.cbSignal_CheckedChanged);
            // 
            // cbSignalStart
            // 
            this.cbSignalStart.AutoSize = true;
            this.cbSignalStart.Location = new System.Drawing.Point(6, 65);
            this.cbSignalStart.Name = "cbSignalStart";
            this.cbSignalStart.Size = new System.Drawing.Size(78, 17);
            this.cbSignalStart.TabIndex = 3;
            this.cbSignalStart.Text = "start / phiB";
            this.cbSignalStart.UseVisualStyleBackColor = true;
            this.cbSignalStart.CheckedChanged += new System.EventHandler(this.cbSignal_CheckedChanged);
            // 
            // cbSignalCount
            // 
            this.cbSignalCount.AutoSize = true;
            this.cbSignalCount.Location = new System.Drawing.Point(6, 42);
            this.cbSignalCount.Name = "cbSignalCount";
            this.cbSignalCount.Size = new System.Drawing.Size(85, 17);
            this.cbSignalCount.TabIndex = 2;
            this.cbSignalCount.Text = "count / phiA";
            this.cbSignalCount.UseVisualStyleBackColor = true;
            this.cbSignalCount.CheckedChanged += new System.EventHandler(this.cbSignal_CheckedChanged);
            // 
            // cbSignalReload
            // 
            this.cbSignalReload.AutoSize = true;
            this.cbSignalReload.Location = new System.Drawing.Point(6, 19);
            this.cbSignalReload.Name = "cbSignalReload";
            this.cbSignalReload.Size = new System.Drawing.Size(91, 17);
            this.cbSignalReload.TabIndex = 1;
            this.cbSignalReload.Text = "reload / index";
            this.cbSignalReload.UseVisualStyleBackColor = true;
            this.cbSignalReload.CheckedChanged += new System.EventHandler(this.cbSignal_CheckedChanged);
            // 
            // CyTCPWMTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxSignals);
            this.Name = "CyTCPWMTab";
            this.Size = new System.Drawing.Size(166, 157);
            this.groupBoxSignals.ResumeLayout(false);
            this.groupBoxSignals.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxSignals;
        private System.Windows.Forms.CheckBox cbSignalCapture;
        private System.Windows.Forms.CheckBox cbSignalStop;
        private System.Windows.Forms.CheckBox cbSignalStart;
        private System.Windows.Forms.CheckBox cbSignalCount;
        private System.Windows.Forms.CheckBox cbSignalReload;
    }
}
