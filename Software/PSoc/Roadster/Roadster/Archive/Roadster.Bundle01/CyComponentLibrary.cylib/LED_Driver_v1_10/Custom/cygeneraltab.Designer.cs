/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

namespace LED_Driver_v1_10
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyGeneralTab));
            this.m_lblNumSegments = new System.Windows.Forms.Label();
            this.m_cbNumSegments = new System.Windows.Forms.ComboBox();
            this.m_cbNumCommons = new System.Windows.Forms.ComboBox();
            this.m_lblNumCommons = new System.Windows.Forms.Label();
            this.m_grpCommonDrive = new System.Windows.Forms.GroupBox();
            this.m_rbCommonDriveHigh = new System.Windows.Forms.RadioButton();
            this.m_rbCommonDriveLow = new System.Windows.Forms.RadioButton();
            this.m_grpSegmentDrive = new System.Windows.Forms.GroupBox();
            this.m_rbSeqmentDriveHigh = new System.Windows.Forms.RadioButton();
            this.m_rbSeqmentDriveLow = new System.Windows.Forms.RadioButton();
            this.m_grpClockSource = new System.Windows.Forms.GroupBox();
            this.m_lblActualRefreshRate = new System.Windows.Forms.Label();
            this.m_rbExternalClock = new System.Windows.Forms.RadioButton();
            this.m_rbInternalClock = new System.Windows.Forms.RadioButton();
            this.m_numRefreshRate = new System.Windows.Forms.NumericUpDown();
            this.m_lblRefreshRate = new System.Windows.Forms.Label();
            this.m_grpBrightnessCtl = new System.Windows.Forms.GroupBox();
            this.m_rbDisableBrightnessCtl = new System.Windows.Forms.RadioButton();
            this.m_rbEnableBrightnessCtl = new System.Windows.Forms.RadioButton();
            this.warningProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_grpCommonDrive.SuspendLayout();
            this.m_grpSegmentDrive.SuspendLayout();
            this.m_grpClockSource.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRefreshRate)).BeginInit();
            this.m_grpBrightnessCtl.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.warningProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // m_lblNumSegments
            // 
            resources.ApplyResources(this.m_lblNumSegments, "m_lblNumSegments");
            this.m_lblNumSegments.Name = "m_lblNumSegments";
            // 
            // m_cbNumSegments
            // 
            this.m_cbNumSegments.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbNumSegments.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbNumSegments, "m_cbNumSegments");
            this.m_cbNumSegments.Name = "m_cbNumSegments";
            // 
            // m_cbNumCommons
            // 
            this.m_cbNumCommons.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbNumCommons.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbNumCommons, "m_cbNumCommons");
            this.m_cbNumCommons.Name = "m_cbNumCommons";
            // 
            // m_lblNumCommons
            // 
            resources.ApplyResources(this.m_lblNumCommons, "m_lblNumCommons");
            this.m_lblNumCommons.Name = "m_lblNumCommons";
            // 
            // m_grpCommonDrive
            // 
            this.m_grpCommonDrive.Controls.Add(this.m_rbCommonDriveHigh);
            this.m_grpCommonDrive.Controls.Add(this.m_rbCommonDriveLow);
            resources.ApplyResources(this.m_grpCommonDrive, "m_grpCommonDrive");
            this.m_grpCommonDrive.Name = "m_grpCommonDrive";
            this.m_grpCommonDrive.TabStop = false;
            // 
            // m_rbCommonDriveHigh
            // 
            resources.ApplyResources(this.m_rbCommonDriveHigh, "m_rbCommonDriveHigh");
            this.m_rbCommonDriveHigh.Name = "m_rbCommonDriveHigh";
            this.m_rbCommonDriveHigh.TabStop = true;
            this.m_rbCommonDriveHigh.UseVisualStyleBackColor = true;
            // 
            // m_rbCommonDriveLow
            // 
            resources.ApplyResources(this.m_rbCommonDriveLow, "m_rbCommonDriveLow");
            this.m_rbCommonDriveLow.Name = "m_rbCommonDriveLow";
            this.m_rbCommonDriveLow.TabStop = true;
            this.m_rbCommonDriveLow.UseVisualStyleBackColor = true;
            // 
            // m_grpSegmentDrive
            // 
            this.m_grpSegmentDrive.Controls.Add(this.m_rbSeqmentDriveHigh);
            this.m_grpSegmentDrive.Controls.Add(this.m_rbSeqmentDriveLow);
            resources.ApplyResources(this.m_grpSegmentDrive, "m_grpSegmentDrive");
            this.m_grpSegmentDrive.Name = "m_grpSegmentDrive";
            this.m_grpSegmentDrive.TabStop = false;
            // 
            // m_rbSeqmentDriveHigh
            // 
            resources.ApplyResources(this.m_rbSeqmentDriveHigh, "m_rbSeqmentDriveHigh");
            this.m_rbSeqmentDriveHigh.Name = "m_rbSeqmentDriveHigh";
            this.m_rbSeqmentDriveHigh.TabStop = true;
            this.m_rbSeqmentDriveHigh.UseVisualStyleBackColor = true;
            // 
            // m_rbSeqmentDriveLow
            // 
            resources.ApplyResources(this.m_rbSeqmentDriveLow, "m_rbSeqmentDriveLow");
            this.m_rbSeqmentDriveLow.Name = "m_rbSeqmentDriveLow";
            this.m_rbSeqmentDriveLow.TabStop = true;
            this.m_rbSeqmentDriveLow.UseVisualStyleBackColor = true;
            // 
            // m_grpClockSource
            // 
            this.m_grpClockSource.Controls.Add(this.m_lblActualRefreshRate);
            this.m_grpClockSource.Controls.Add(this.m_rbExternalClock);
            this.m_grpClockSource.Controls.Add(this.m_rbInternalClock);
            this.m_grpClockSource.Controls.Add(this.m_numRefreshRate);
            this.m_grpClockSource.Controls.Add(this.m_lblRefreshRate);
            resources.ApplyResources(this.m_grpClockSource, "m_grpClockSource");
            this.m_grpClockSource.Name = "m_grpClockSource";
            this.m_grpClockSource.TabStop = false;
            // 
            // m_lblActualRefreshRate
            // 
            resources.ApplyResources(this.m_lblActualRefreshRate, "m_lblActualRefreshRate");
            this.m_lblActualRefreshRate.Name = "m_lblActualRefreshRate";
            // 
            // m_rbExternalClock
            // 
            resources.ApplyResources(this.m_rbExternalClock, "m_rbExternalClock");
            this.m_rbExternalClock.Name = "m_rbExternalClock";
            this.m_rbExternalClock.TabStop = true;
            this.m_rbExternalClock.UseVisualStyleBackColor = true;
            // 
            // m_rbInternalClock
            // 
            resources.ApplyResources(this.m_rbInternalClock, "m_rbInternalClock");
            this.m_rbInternalClock.Name = "m_rbInternalClock";
            this.m_rbInternalClock.TabStop = true;
            this.m_rbInternalClock.UseVisualStyleBackColor = true;
            // 
            // m_numRefreshRate
            // 
            resources.ApplyResources(this.m_numRefreshRate, "m_numRefreshRate");
            this.m_numRefreshRate.Name = "m_numRefreshRate";
            // 
            // m_lblRefreshRate
            // 
            resources.ApplyResources(this.m_lblRefreshRate, "m_lblRefreshRate");
            this.m_lblRefreshRate.Name = "m_lblRefreshRate";
            // 
            // m_grpBrightnessCtl
            // 
            this.m_grpBrightnessCtl.Controls.Add(this.m_rbDisableBrightnessCtl);
            this.m_grpBrightnessCtl.Controls.Add(this.m_rbEnableBrightnessCtl);
            resources.ApplyResources(this.m_grpBrightnessCtl, "m_grpBrightnessCtl");
            this.m_grpBrightnessCtl.Name = "m_grpBrightnessCtl";
            this.m_grpBrightnessCtl.TabStop = false;
            // 
            // m_rbDisableBrightnessCtl
            // 
            resources.ApplyResources(this.m_rbDisableBrightnessCtl, "m_rbDisableBrightnessCtl");
            this.m_rbDisableBrightnessCtl.Name = "m_rbDisableBrightnessCtl";
            this.m_rbDisableBrightnessCtl.TabStop = true;
            this.m_rbDisableBrightnessCtl.UseVisualStyleBackColor = true;
            // 
            // m_rbEnableBrightnessCtl
            // 
            resources.ApplyResources(this.m_rbEnableBrightnessCtl, "m_rbEnableBrightnessCtl");
            this.m_rbEnableBrightnessCtl.Name = "m_rbEnableBrightnessCtl";
            this.m_rbEnableBrightnessCtl.TabStop = true;
            this.m_rbEnableBrightnessCtl.UseVisualStyleBackColor = true;
            // 
            // warningProvider
            // 
            this.warningProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.warningProvider.ContainerControl = this;
            resources.ApplyResources(this.warningProvider, "warningProvider");
            // 
            // CyGeneralTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_grpBrightnessCtl);
            this.Controls.Add(this.m_grpClockSource);
            this.Controls.Add(this.m_grpSegmentDrive);
            this.Controls.Add(this.m_grpCommonDrive);
            this.Controls.Add(this.m_cbNumCommons);
            this.Controls.Add(this.m_lblNumCommons);
            this.Controls.Add(this.m_cbNumSegments);
            this.Controls.Add(this.m_lblNumSegments);
            this.Name = "CyGeneralTab";
            this.m_grpCommonDrive.ResumeLayout(false);
            this.m_grpCommonDrive.PerformLayout();
            this.m_grpSegmentDrive.ResumeLayout(false);
            this.m_grpSegmentDrive.PerformLayout();
            this.m_grpClockSource.ResumeLayout(false);
            this.m_grpClockSource.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRefreshRate)).EndInit();
            this.m_grpBrightnessCtl.ResumeLayout(false);
            this.m_grpBrightnessCtl.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.warningProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblNumSegments;
        private System.Windows.Forms.ComboBox m_cbNumSegments;
        private System.Windows.Forms.ComboBox m_cbNumCommons;
        private System.Windows.Forms.Label m_lblNumCommons;
        private System.Windows.Forms.GroupBox m_grpCommonDrive;
        private System.Windows.Forms.RadioButton m_rbCommonDriveHigh;
        private System.Windows.Forms.RadioButton m_rbCommonDriveLow;
        private System.Windows.Forms.GroupBox m_grpSegmentDrive;
        private System.Windows.Forms.RadioButton m_rbSeqmentDriveHigh;
        private System.Windows.Forms.RadioButton m_rbSeqmentDriveLow;
        private System.Windows.Forms.GroupBox m_grpClockSource;
        private System.Windows.Forms.RadioButton m_rbExternalClock;
        private System.Windows.Forms.RadioButton m_rbInternalClock;
        private System.Windows.Forms.Label m_lblRefreshRate;
        private System.Windows.Forms.NumericUpDown m_numRefreshRate;
        private System.Windows.Forms.GroupBox m_grpBrightnessCtl;
        private System.Windows.Forms.RadioButton m_rbDisableBrightnessCtl;
        private System.Windows.Forms.RadioButton m_rbEnableBrightnessCtl;
        private System.Windows.Forms.Label m_lblActualRefreshRate;
        private System.Windows.Forms.ErrorProvider warningProvider;
    }
}
