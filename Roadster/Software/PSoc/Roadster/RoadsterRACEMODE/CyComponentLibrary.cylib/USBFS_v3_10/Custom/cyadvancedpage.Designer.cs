/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



namespace USBFS_v3_10
{
    partial class CyAdvancedPage
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyAdvancedPage));
            this.checkBox16BitEpApi = new System.Windows.Forms.CheckBox();
            this.checkBoxBattChargDetect = new System.Windows.Forms.CheckBox();
            this.radioButtonVbusPoweredPad = new System.Windows.Forms.RadioButton();
            this.radioButtonVbusInternal = new System.Windows.Forms.RadioButton();
            this.radioButtonVbusExternal = new System.Windows.Forms.RadioButton();
            this.checkBoxExtClass = new System.Windows.Forms.CheckBox();
            this.checkBoxSofOutput = new System.Windows.Forms.CheckBox();
            this.checkBoxExtVendor = new System.Windows.Forms.CheckBox();
            this.checkBoxVBusMon = new System.Windows.Forms.CheckBox();
            this.errProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.wrgProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_gbxVbusMonitoring = new System.Windows.Forms.GroupBox();
            this.m_gbxUsbRequests = new System.Windows.Forms.GroupBox();
            this.m_gbxSoF = new System.Windows.Forms.GroupBox();
            this.checkBoxSofInterrupt = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.wrgProvider)).BeginInit();
            this.m_gbxVbusMonitoring.SuspendLayout();
            this.m_gbxUsbRequests.SuspendLayout();
            this.m_gbxSoF.SuspendLayout();
            this.SuspendLayout();
            // 
            // checkBox16BitEpApi
            // 
            this.checkBox16BitEpApi.AutoSize = true;
            this.checkBox16BitEpApi.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBox16BitEpApi.Location = new System.Drawing.Point(12, 241);
            this.checkBox16BitEpApi.Name = "checkBox16BitEpApi";
            this.checkBox16BitEpApi.Size = new System.Drawing.Size(269, 21);
            this.checkBox16BitEpApi.TabIndex = 5;
            this.checkBox16BitEpApi.Text = "Generate 16-bit endpoint access APIs";
            this.checkBox16BitEpApi.UseVisualStyleBackColor = true;
            this.checkBox16BitEpApi.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // checkBoxBattChargDetect
            // 
            this.checkBoxBattChargDetect.AutoSize = true;
            this.checkBoxBattChargDetect.Location = new System.Drawing.Point(12, 214);
            this.checkBoxBattChargDetect.Name = "checkBoxBattChargDetect";
            this.checkBoxBattChargDetect.Size = new System.Drawing.Size(237, 21);
            this.checkBoxBattChargDetect.TabIndex = 4;
            this.checkBoxBattChargDetect.Text = "Enable battery charger detection";
            this.checkBoxBattChargDetect.UseVisualStyleBackColor = true;
            this.checkBoxBattChargDetect.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // radioButtonVbusPoweredPad
            // 
            this.radioButtonVbusPoweredPad.AutoSize = true;
            this.radioButtonVbusPoweredPad.Location = new System.Drawing.Point(29, 78);
            this.radioButtonVbusPoweredPad.Name = "radioButtonVbusPoweredPad";
            this.radioButtonVbusPoweredPad.Size = new System.Drawing.Size(136, 21);
            this.radioButtonVbusPoweredPad.TabIndex = 10;
            this.radioButtonVbusPoweredPad.TabStop = true;
            this.radioButtonVbusPoweredPad.Text = "VBUS power pad";
            this.radioButtonVbusPoweredPad.UseVisualStyleBackColor = true;
            this.radioButtonVbusPoweredPad.CheckedChanged += new System.EventHandler(this.radioButtonVbus_CheckedChanged);
            // 
            // radioButtonVbusInternal
            // 
            this.radioButtonVbusInternal.AutoSize = true;
            this.radioButtonVbusInternal.Location = new System.Drawing.Point(29, 24);
            this.radioButtonVbusInternal.Name = "radioButtonVbusInternal";
            this.radioButtonVbusInternal.Size = new System.Drawing.Size(231, 21);
            this.radioButtonVbusInternal.TabIndex = 0;
            this.radioButtonVbusInternal.TabStop = true;
            this.radioButtonVbusInternal.Text = "IO pin internal to the component";
            this.radioButtonVbusInternal.UseVisualStyleBackColor = true;
            this.radioButtonVbusInternal.CheckedChanged += new System.EventHandler(this.radioButtonVbus_CheckedChanged);
            // 
            // radioButtonVbusExternal
            // 
            this.radioButtonVbusExternal.AutoSize = true;
            this.radioButtonVbusExternal.Location = new System.Drawing.Point(29, 51);
            this.radioButtonVbusExternal.Name = "radioButtonVbusExternal";
            this.radioButtonVbusExternal.Size = new System.Drawing.Size(234, 21);
            this.radioButtonVbusExternal.TabIndex = 1;
            this.radioButtonVbusExternal.TabStop = true;
            this.radioButtonVbusExternal.Text = "IO pin external to the component";
            this.radioButtonVbusExternal.UseVisualStyleBackColor = true;
            this.radioButtonVbusExternal.CheckedChanged += new System.EventHandler(this.radioButtonVbus_CheckedChanged);
            // 
            // checkBoxExtClass
            // 
            this.checkBoxExtClass.AutoSize = true;
            this.checkBoxExtClass.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxExtClass.Location = new System.Drawing.Point(6, 23);
            this.checkBoxExtClass.Name = "checkBoxExtClass";
            this.checkBoxExtClass.Size = new System.Drawing.Size(252, 21);
            this.checkBoxExtClass.TabIndex = 0;
            this.checkBoxExtClass.Text = "Handle class requests in user code";
            this.checkBoxExtClass.UseVisualStyleBackColor = true;
            this.checkBoxExtClass.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // checkBoxSofOutput
            // 
            this.checkBoxSofOutput.AutoSize = true;
            this.checkBoxSofOutput.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxSofOutput.Location = new System.Drawing.Point(6, 23);
            this.checkBoxSofOutput.Name = "checkBoxSofOutput";
            this.checkBoxSofOutput.Size = new System.Drawing.Size(150, 21);
            this.checkBoxSofOutput.TabIndex = 0;
            this.checkBoxSofOutput.Text = "Enable SOF output";
            this.checkBoxSofOutput.UseVisualStyleBackColor = true;
            this.checkBoxSofOutput.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // checkBoxExtVendor
            // 
            this.checkBoxExtVendor.AutoSize = true;
            this.checkBoxExtVendor.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxExtVendor.Location = new System.Drawing.Point(6, 50);
            this.checkBoxExtVendor.Name = "checkBoxExtVendor";
            this.checkBoxExtVendor.Size = new System.Drawing.Size(264, 21);
            this.checkBoxExtVendor.TabIndex = 1;
            this.checkBoxExtVendor.Text = "Handle vendor requests in user code";
            this.checkBoxExtVendor.UseVisualStyleBackColor = true;
            this.checkBoxExtVendor.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // checkBoxVBusMon
            // 
            this.checkBoxVBusMon.AutoSize = true;
            this.checkBoxVBusMon.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxVBusMon.Location = new System.Drawing.Point(12, 95);
            this.checkBoxVBusMon.Name = "checkBoxVBusMon";
            this.checkBoxVBusMon.Size = new System.Drawing.Size(137, 21);
            this.checkBoxVBusMon.TabIndex = 2;
            this.checkBoxVBusMon.Text = "VBUS Monitoring";
            this.checkBoxVBusMon.UseVisualStyleBackColor = true;
            this.checkBoxVBusMon.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // errProvider
            // 
            this.errProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errProvider.ContainerControl = this;
            // 
            // toolTip1
            // 
            this.toolTip1.AutoPopDelay = 20000;
            this.toolTip1.InitialDelay = 500;
            this.toolTip1.ReshowDelay = 100;
            // 
            // wrgProvider
            // 
            this.wrgProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.wrgProvider.ContainerControl = this;
            this.wrgProvider.Icon = ((System.Drawing.Icon)(resources.GetObject("wrgProvider.Icon")));
            // 
            // m_gbxVbusMonitoring
            // 
            this.m_gbxVbusMonitoring.Controls.Add(this.radioButtonVbusInternal);
            this.m_gbxVbusMonitoring.Controls.Add(this.radioButtonVbusPoweredPad);
            this.m_gbxVbusMonitoring.Controls.Add(this.radioButtonVbusExternal);
            this.m_gbxVbusMonitoring.Location = new System.Drawing.Point(6, 98);
            this.m_gbxVbusMonitoring.Name = "m_gbxVbusMonitoring";
            this.m_gbxVbusMonitoring.Size = new System.Drawing.Size(501, 107);
            this.m_gbxVbusMonitoring.TabIndex = 3;
            this.m_gbxVbusMonitoring.TabStop = false;
            // 
            // m_gbxUsbRequests
            // 
            this.m_gbxUsbRequests.Controls.Add(this.checkBoxExtClass);
            this.m_gbxUsbRequests.Controls.Add(this.checkBoxExtVendor);
            this.m_gbxUsbRequests.Location = new System.Drawing.Point(206, 8);
            this.m_gbxUsbRequests.Name = "m_gbxUsbRequests";
            this.m_gbxUsbRequests.Size = new System.Drawing.Size(301, 81);
            this.m_gbxUsbRequests.TabIndex = 1;
            this.m_gbxUsbRequests.TabStop = false;
            this.m_gbxUsbRequests.Text = "USB Requests";
            // 
            // m_gbxSoF
            // 
            this.m_gbxSoF.Controls.Add(this.checkBoxSofInterrupt);
            this.m_gbxSoF.Controls.Add(this.checkBoxSofOutput);
            this.m_gbxSoF.Location = new System.Drawing.Point(6, 8);
            this.m_gbxSoF.Name = "m_gbxSoF";
            this.m_gbxSoF.Size = new System.Drawing.Size(194, 81);
            this.m_gbxSoF.TabIndex = 0;
            this.m_gbxSoF.TabStop = false;
            this.m_gbxSoF.Text = "Start-of-Frame (SOF)";
            // 
            // checkBoxSofInterrupt
            // 
            this.checkBoxSofInterrupt.AutoSize = true;
            this.checkBoxSofInterrupt.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxSofInterrupt.Location = new System.Drawing.Point(6, 50);
            this.checkBoxSofInterrupt.Name = "checkBoxSofInterrupt";
            this.checkBoxSofInterrupt.Size = new System.Drawing.Size(167, 21);
            this.checkBoxSofInterrupt.TabIndex = 1;
            this.checkBoxSofInterrupt.Text = "Enable SOF interrupt ";
            this.checkBoxSofInterrupt.UseVisualStyleBackColor = true;
            this.checkBoxSofInterrupt.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // CyAdvancedPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.checkBoxVBusMon);
            this.Controls.Add(this.m_gbxSoF);
            this.Controls.Add(this.m_gbxUsbRequests);
            this.Controls.Add(this.m_gbxVbusMonitoring);
            this.Controls.Add(this.checkBox16BitEpApi);
            this.Controls.Add(this.checkBoxBattChargDetect);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyAdvancedPage";
            this.Size = new System.Drawing.Size(752, 413);
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.wrgProvider)).EndInit();
            this.m_gbxVbusMonitoring.ResumeLayout(false);
            this.m_gbxVbusMonitoring.PerformLayout();
            this.m_gbxUsbRequests.ResumeLayout(false);
            this.m_gbxUsbRequests.PerformLayout();
            this.m_gbxSoF.ResumeLayout(false);
            this.m_gbxSoF.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBoxSofOutput;
        private System.Windows.Forms.CheckBox checkBoxVBusMon;
        private System.Windows.Forms.CheckBox checkBoxExtVendor;
        private System.Windows.Forms.CheckBox checkBoxExtClass;
        private System.Windows.Forms.RadioButton radioButtonVbusExternal;
        private System.Windows.Forms.RadioButton radioButtonVbusInternal;
        private System.Windows.Forms.CheckBox checkBoxBattChargDetect;
        private System.Windows.Forms.ErrorProvider errProvider;
        private System.Windows.Forms.CheckBox checkBox16BitEpApi;
        private System.Windows.Forms.RadioButton radioButtonVbusPoweredPad;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.ErrorProvider wrgProvider;
        private System.Windows.Forms.GroupBox m_gbxVbusMonitoring;
        private System.Windows.Forms.GroupBox m_gbxUsbRequests;
        private System.Windows.Forms.GroupBox m_gbxSoF;
        private System.Windows.Forms.CheckBox checkBoxSofInterrupt;
    }
}
