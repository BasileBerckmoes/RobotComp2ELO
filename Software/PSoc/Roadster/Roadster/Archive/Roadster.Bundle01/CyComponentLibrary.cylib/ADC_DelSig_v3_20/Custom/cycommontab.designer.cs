/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


namespace ADC_DelSig_v3_20
{
    partial class CyCommonTab
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
            this.m_lblNumConfig = new System.Windows.Forms.Label();
            this.m_chbSOC = new System.Windows.Forms.CheckBox();
            this.m_grpClockSource = new System.Windows.Forms.GroupBox();
            this.m_rbExternal = new System.Windows.Forms.RadioButton();
            this.m_rbInternal = new System.Windows.Forms.RadioButton();
            this.m_chbLowPower = new System.Windows.Forms.CheckBox();
            this.m_chbEnVrefVssa = new System.Windows.Forms.CheckBox();
            this.m_chbEnModInput = new System.Windows.Forms.CheckBox();
            this.m_grpInputMode = new System.Windows.Forms.GroupBox();
            this.m_rbSingleEnded = new System.Windows.Forms.RadioButton();
            this.m_rbDiff = new System.Windows.Forms.RadioButton();
            this.m_cbNumConfig = new System.Windows.Forms.ComboBox();
            this.m_grpClockSource.SuspendLayout();
            this.m_grpInputMode.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_lblNumConfig
            // 
            this.m_lblNumConfig.AutoSize = true;
            this.m_lblNumConfig.Location = new System.Drawing.Point(3, 6);
            this.m_lblNumConfig.Name = "m_lblNumConfig";
            this.m_lblNumConfig.Size = new System.Drawing.Size(128, 13);
            this.m_lblNumConfig.TabIndex = 0;
            this.m_lblNumConfig.Text = "Number of configurations:";
            // 
            // m_chbSOC
            // 
            this.m_chbSOC.AutoSize = true;
            this.m_chbSOC.Location = new System.Drawing.Point(3, 107);
            this.m_chbSOC.Name = "m_chbSOC";
            this.m_chbSOC.Size = new System.Drawing.Size(196, 17);
            this.m_chbSOC.TabIndex = 4;
            this.m_chbSOC.Text = "Hardware SOC (Start of Conversion)";
            this.m_chbSOC.UseVisualStyleBackColor = true;
            // 
            // m_grpClockSource
            // 
            this.m_grpClockSource.Controls.Add(this.m_rbExternal);
            this.m_grpClockSource.Controls.Add(this.m_rbInternal);
            this.m_grpClockSource.Location = new System.Drawing.Point(6, 30);
            this.m_grpClockSource.Name = "m_grpClockSource";
            this.m_grpClockSource.Size = new System.Drawing.Size(103, 71);
            this.m_grpClockSource.TabIndex = 2;
            this.m_grpClockSource.TabStop = false;
            this.m_grpClockSource.Text = "Clock source";
            // 
            // m_rbExternal
            // 
            this.m_rbExternal.AutoSize = true;
            this.m_rbExternal.Location = new System.Drawing.Point(6, 42);
            this.m_rbExternal.Name = "m_rbExternal";
            this.m_rbExternal.Size = new System.Drawing.Size(63, 17);
            this.m_rbExternal.TabIndex = 1;
            this.m_rbExternal.TabStop = true;
            this.m_rbExternal.Text = "External";
            this.m_rbExternal.UseVisualStyleBackColor = true;
            // 
            // m_rbInternal
            // 
            this.m_rbInternal.AutoSize = true;
            this.m_rbInternal.Location = new System.Drawing.Point(6, 19);
            this.m_rbInternal.Name = "m_rbInternal";
            this.m_rbInternal.Size = new System.Drawing.Size(60, 17);
            this.m_rbInternal.TabIndex = 0;
            this.m_rbInternal.TabStop = true;
            this.m_rbInternal.Text = "Internal";
            this.m_rbInternal.UseVisualStyleBackColor = true;
            // 
            // m_chbLowPower
            // 
            this.m_chbLowPower.AutoSize = true;
            this.m_chbLowPower.Checked = true;
            this.m_chbLowPower.CheckState = System.Windows.Forms.CheckState.Checked;
            this.m_chbLowPower.Enabled = false;
            this.m_chbLowPower.Location = new System.Drawing.Point(3, 130);
            this.m_chbLowPower.Name = "m_chbLowPower";
            this.m_chbLowPower.Size = new System.Drawing.Size(158, 17);
            this.m_chbLowPower.TabIndex = 5;
            this.m_chbLowPower.Text = "External charge pump clock";
            this.m_chbLowPower.UseVisualStyleBackColor = true;
            // 
            // m_chbEnVrefVssa
            // 
            this.m_chbEnVrefVssa.AutoSize = true;
            this.m_chbEnVrefVssa.Location = new System.Drawing.Point(3, 153);
            this.m_chbEnVrefVssa.Name = "m_chbEnVrefVssa";
            this.m_chbEnVrefVssa.Size = new System.Drawing.Size(109, 17);
            this.m_chbEnVrefVssa.TabIndex = 6;
            this.m_chbEnVrefVssa.Text = "Enable Vref/Vssa";
            this.m_chbEnVrefVssa.UseVisualStyleBackColor = true;
            // 
            // m_chbEnModInput
            // 
            this.m_chbEnModInput.AutoSize = true;
            this.m_chbEnModInput.Location = new System.Drawing.Point(3, 176);
            this.m_chbEnModInput.Name = "m_chbEnModInput";
            this.m_chbEnModInput.Size = new System.Drawing.Size(134, 17);
            this.m_chbEnModInput.TabIndex = 7;
            this.m_chbEnModInput.Text = "Enable modulator input";
            this.m_chbEnModInput.UseVisualStyleBackColor = true;
            // 
            // m_grpInputMode
            // 
            this.m_grpInputMode.Controls.Add(this.m_rbSingleEnded);
            this.m_grpInputMode.Controls.Add(this.m_rbDiff);
            this.m_grpInputMode.Location = new System.Drawing.Point(115, 30);
            this.m_grpInputMode.Name = "m_grpInputMode";
            this.m_grpInputMode.Size = new System.Drawing.Size(116, 71);
            this.m_grpInputMode.TabIndex = 3;
            this.m_grpInputMode.TabStop = false;
            this.m_grpInputMode.Text = "Input mode";
            // 
            // m_rbSingleEnded
            // 
            this.m_rbSingleEnded.AutoSize = true;
            this.m_rbSingleEnded.Location = new System.Drawing.Point(6, 42);
            this.m_rbSingleEnded.Name = "m_rbSingleEnded";
            this.m_rbSingleEnded.Size = new System.Drawing.Size(87, 17);
            this.m_rbSingleEnded.TabIndex = 14;
            this.m_rbSingleEnded.TabStop = true;
            this.m_rbSingleEnded.Text = "Single ended";
            this.m_rbSingleEnded.UseVisualStyleBackColor = true;
            // 
            // m_rbDiff
            // 
            this.m_rbDiff.AutoSize = true;
            this.m_rbDiff.Location = new System.Drawing.Point(6, 19);
            this.m_rbDiff.Name = "m_rbDiff";
            this.m_rbDiff.Size = new System.Drawing.Size(75, 17);
            this.m_rbDiff.TabIndex = 13;
            this.m_rbDiff.TabStop = true;
            this.m_rbDiff.Text = "Differential";
            this.m_rbDiff.UseVisualStyleBackColor = true;
            // 
            // m_cbNumConfig
            // 
            this.m_cbNumConfig.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbNumConfig.FormattingEnabled = true;
            this.m_cbNumConfig.Location = new System.Drawing.Point(137, 3);
            this.m_cbNumConfig.Name = "m_cbNumConfig";
            this.m_cbNumConfig.Size = new System.Drawing.Size(50, 21);
            this.m_cbNumConfig.TabIndex = 1;
            // 
            // CyCommonTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_cbNumConfig);
            this.Controls.Add(this.m_grpInputMode);
            this.Controls.Add(this.m_chbEnModInput);
            this.Controls.Add(this.m_chbEnVrefVssa);
            this.Controls.Add(this.m_chbLowPower);
            this.Controls.Add(this.m_grpClockSource);
            this.Controls.Add(this.m_chbSOC);
            this.Controls.Add(this.m_lblNumConfig);
            this.Name = "CyCommonTab";
            this.Size = new System.Drawing.Size(239, 196);
            this.m_grpClockSource.ResumeLayout(false);
            this.m_grpClockSource.PerformLayout();
            this.m_grpInputMode.ResumeLayout(false);
            this.m_grpInputMode.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblNumConfig;
        private System.Windows.Forms.CheckBox m_chbSOC;
        private System.Windows.Forms.GroupBox m_grpClockSource;
        private System.Windows.Forms.RadioButton m_rbInternal;
        private System.Windows.Forms.RadioButton m_rbExternal;
        private System.Windows.Forms.CheckBox m_chbLowPower;
        private System.Windows.Forms.CheckBox m_chbEnVrefVssa;
        private System.Windows.Forms.CheckBox m_chbEnModInput;
        private System.Windows.Forms.GroupBox m_grpInputMode;
        private System.Windows.Forms.RadioButton m_rbSingleEnded;
        private System.Windows.Forms.RadioButton m_rbDiff;
        private System.Windows.Forms.ComboBox m_cbNumConfig;
    }
}
