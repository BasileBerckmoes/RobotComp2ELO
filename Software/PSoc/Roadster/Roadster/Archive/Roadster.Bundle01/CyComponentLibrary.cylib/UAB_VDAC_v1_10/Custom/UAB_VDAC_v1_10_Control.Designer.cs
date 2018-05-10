/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace UAB_VDAC_v1_10
{
    partial class CyUAB_VDAC_v1_10Control
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        // Begin parameter control declarations
        // End parameter control declarations

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

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.vdac13ToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.m_nudVrefVolts = new System.Windows.Forms.NumericUpDown();
            this.m_nudVagndVolts = new System.Windows.Forms.NumericUpDown();
            this.m_nudDefaultOutVolts = new System.Windows.Forms.NumericUpDown();
            this.m_cmbDacMode = new System.Windows.Forms.ComboBox();
            this.m_cmbDacGain = new System.Windows.Forms.ComboBox();
            this.m_nudClockFreq = new System.Windows.Forms.NumericUpDown();
            this.m_cmbVagndSource = new System.Windows.Forms.ComboBox();
            this.m_cmbVrefSource = new System.Windows.Forms.ComboBox();
            this.m_rbStrobeContinous = new System.Windows.Forms.RadioButton();
            this.m_rbStrobeExternal = new System.Windows.Forms.RadioButton();
            this.m_rbClockInternal = new System.Windows.Forms.RadioButton();
            this.m_rbClockExternal = new System.Windows.Forms.RadioButton();
            this.m_rbOutputFollower = new System.Windows.Forms.RadioButton();
            this.m_rbOutputFeedback = new System.Windows.Forms.RadioButton();
            this.m_gbReferenceVoltages = new System.Windows.Forms.GroupBox();
            this.m_lVrefVolts = new System.Windows.Forms.Label();
            this.m_lVagndVolts = new System.Windows.Forms.Label();
            this.m_tdTransferDiagramPanel = new System.Windows.Forms.Panel();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.m_rbModulatorNone = new System.Windows.Forms.RadioButton();
            this.m_rbModulatorExternal = new System.Windows.Forms.RadioButton();
            this.panel2 = new System.Windows.Forms.Panel();
            this.m_lDacGain = new System.Windows.Forms.Label();
            this.m_lDacMode = new System.Windows.Forms.Label();
            this.m_ldefaultOutVolts = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.m_lClockRefreshValue = new System.Windows.Forms.Label();
            this.m_lClockRefresh = new System.Windows.Forms.Label();
            this.m_lClockFreq = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVrefVolts)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVagndVolts)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDefaultOutVolts)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudClockFreq)).BeginInit();
            this.m_gbReferenceVoltages.SuspendLayout();
            this.m_tdTransferDiagramPanel.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.panel2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_nudVrefVolts
            // 
            this.m_nudVrefVolts.DecimalPlaces = 3;
            this.m_nudVrefVolts.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudVrefVolts.Location = new System.Drawing.Point(202, 19);
            this.m_nudVrefVolts.Maximum = new decimal(new int[] {
            55,
            0,
            0,
            65536});
            this.m_nudVrefVolts.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.m_nudVrefVolts.Name = "m_nudVrefVolts";
            this.m_nudVrefVolts.Size = new System.Drawing.Size(51, 20);
            this.m_nudVrefVolts.TabIndex = 2;
            this.vdac13ToolTip.SetToolTip(this.m_nudVrefVolts, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.VrefVoltsToolTip);
            this.m_nudVrefVolts.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.m_nudVrefVolts.ValueChanged += new System.EventHandler(this.nud_ValueChanged);
            // 
            // m_nudVagndVolts
            // 
            this.m_nudVagndVolts.DecimalPlaces = 3;
            this.m_nudVagndVolts.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudVagndVolts.Location = new System.Drawing.Point(201, 47);
            this.m_nudVagndVolts.Maximum = new decimal(new int[] {
            55,
            0,
            0,
            65536});
            this.m_nudVagndVolts.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.m_nudVagndVolts.Name = "m_nudVagndVolts";
            this.m_nudVagndVolts.Size = new System.Drawing.Size(52, 20);
            this.m_nudVagndVolts.TabIndex = 4;
            this.vdac13ToolTip.SetToolTip(this.m_nudVagndVolts, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.VagndVoltsToolTip);
            this.m_nudVagndVolts.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.m_nudVagndVolts.ValueChanged += new System.EventHandler(this.nud_ValueChanged);
            // 
            // m_nudDefaultOutVolts
            // 
            this.m_nudDefaultOutVolts.DecimalPlaces = 3;
            this.m_nudDefaultOutVolts.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudDefaultOutVolts.Location = new System.Drawing.Point(139, 5);
            this.m_nudDefaultOutVolts.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nudDefaultOutVolts.Name = "m_nudDefaultOutVolts";
            this.m_nudDefaultOutVolts.Size = new System.Drawing.Size(87, 20);
            this.m_nudDefaultOutVolts.TabIndex = 1;
            this.vdac13ToolTip.SetToolTip(this.m_nudDefaultOutVolts, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.defaultOutVoltsToolTip);
            this.m_nudDefaultOutVolts.Value = new decimal(new int[] {
            10,
            0,
            0,
            65536});
            this.m_nudDefaultOutVolts.ValueChanged += new System.EventHandler(this.nud_ValueChanged);
            // 
            // m_cmbDacMode
            // 
            this.m_cmbDacMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbDacMode.FormattingEnabled = true;
            this.m_cmbDacMode.Location = new System.Drawing.Point(68, 31);
            this.m_cmbDacMode.Name = "m_cmbDacMode";
            this.m_cmbDacMode.Size = new System.Drawing.Size(158, 21);
            this.m_cmbDacMode.TabIndex = 3;
            this.vdac13ToolTip.SetToolTip(this.m_cmbDacMode, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.dacSelectToolTip);
            this.m_cmbDacMode.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cmbDacGain
            // 
            this.m_cmbDacGain.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbDacGain.FormattingEnabled = true;
            this.m_cmbDacGain.Location = new System.Drawing.Point(68, 58);
            this.m_cmbDacGain.Name = "m_cmbDacGain";
            this.m_cmbDacGain.Size = new System.Drawing.Size(159, 21);
            this.m_cmbDacGain.TabIndex = 4;
            this.vdac13ToolTip.SetToolTip(this.m_cmbDacGain, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.dacRangeToolTip);
            this.m_cmbDacGain.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_nudClockFreq
            // 
            this.m_nudClockFreq.DecimalPlaces = 3;
            this.m_nudClockFreq.Enabled = false;
            this.m_nudClockFreq.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nudClockFreq.Location = new System.Drawing.Point(154, 19);
            this.m_nudClockFreq.Maximum = new decimal(new int[] {
            4000,
            0,
            0,
            0});
            this.m_nudClockFreq.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.m_nudClockFreq.Name = "m_nudClockFreq";
            this.m_nudClockFreq.Size = new System.Drawing.Size(72, 20);
            this.m_nudClockFreq.TabIndex = 16;
            this.vdac13ToolTip.SetToolTip(this.m_nudClockFreq, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.clockRateToolTip);
            this.m_nudClockFreq.Value = new decimal(new int[] {
            250,
            0,
            0,
            0});
            this.m_nudClockFreq.ValueChanged += new System.EventHandler(this.nud_ValueChanged);
            // 
            // m_cmbVagndSource
            // 
            this.m_cmbVagndSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbVagndSource.FormattingEnabled = true;
            this.m_cmbVagndSource.Location = new System.Drawing.Point(61, 46);
            this.m_cmbVagndSource.Name = "m_cmbVagndSource";
            this.m_cmbVagndSource.Size = new System.Drawing.Size(135, 21);
            this.m_cmbVagndSource.TabIndex = 3;
            this.vdac13ToolTip.SetToolTip(this.m_cmbVagndSource, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.VagndVoltsToolTip);
            this.m_cmbVagndSource.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cmbVrefSource
            // 
            this.m_cmbVrefSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbVrefSource.FormattingEnabled = true;
            this.m_cmbVrefSource.Location = new System.Drawing.Point(61, 18);
            this.m_cmbVrefSource.Name = "m_cmbVrefSource";
            this.m_cmbVrefSource.Size = new System.Drawing.Size(135, 21);
            this.m_cmbVrefSource.TabIndex = 1;
            this.vdac13ToolTip.SetToolTip(this.m_cmbVrefSource, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.VrefVoltsToolTip);
            this.m_cmbVrefSource.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_rbStrobeContinous
            // 
            this.m_rbStrobeContinous.AutoSize = true;
            this.m_rbStrobeContinous.Location = new System.Drawing.Point(6, 19);
            this.m_rbStrobeContinous.Name = "m_rbStrobeContinous";
            this.m_rbStrobeContinous.Size = new System.Drawing.Size(78, 17);
            this.m_rbStrobeContinous.TabIndex = 2;
            this.m_rbStrobeContinous.TabStop = true;
            this.m_rbStrobeContinous.Text = "Continuous";
            this.vdac13ToolTip.SetToolTip(this.m_rbStrobeContinous, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.externalStrobeToolTip);
            this.m_rbStrobeContinous.UseVisualStyleBackColor = true;
            this.m_rbStrobeContinous.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_rbStrobeExternal
            // 
            this.m_rbStrobeExternal.AutoSize = true;
            this.m_rbStrobeExternal.Location = new System.Drawing.Point(6, 42);
            this.m_rbStrobeExternal.Name = "m_rbStrobeExternal";
            this.m_rbStrobeExternal.Size = new System.Drawing.Size(63, 17);
            this.m_rbStrobeExternal.TabIndex = 1;
            this.m_rbStrobeExternal.TabStop = true;
            this.m_rbStrobeExternal.Text = "External";
            this.vdac13ToolTip.SetToolTip(this.m_rbStrobeExternal, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.externalStrobeToolTip);
            this.m_rbStrobeExternal.UseVisualStyleBackColor = true;
            this.m_rbStrobeExternal.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_rbClockInternal
            // 
            this.m_rbClockInternal.AutoSize = true;
            this.m_rbClockInternal.Location = new System.Drawing.Point(6, 19);
            this.m_rbClockInternal.Name = "m_rbClockInternal";
            this.m_rbClockInternal.Size = new System.Drawing.Size(60, 17);
            this.m_rbClockInternal.TabIndex = 2;
            this.m_rbClockInternal.TabStop = true;
            this.m_rbClockInternal.Text = "Internal";
            this.vdac13ToolTip.SetToolTip(this.m_rbClockInternal, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.clockRateEnableToolTip);
            this.m_rbClockInternal.UseVisualStyleBackColor = true;
            this.m_rbClockInternal.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_rbClockExternal
            // 
            this.m_rbClockExternal.AutoSize = true;
            this.m_rbClockExternal.Location = new System.Drawing.Point(6, 42);
            this.m_rbClockExternal.Name = "m_rbClockExternal";
            this.m_rbClockExternal.Size = new System.Drawing.Size(63, 17);
            this.m_rbClockExternal.TabIndex = 1;
            this.m_rbClockExternal.TabStop = true;
            this.m_rbClockExternal.Text = "External";
            this.vdac13ToolTip.SetToolTip(this.m_rbClockExternal, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.clockRateEnableToolTip);
            this.m_rbClockExternal.UseVisualStyleBackColor = true;
            this.m_rbClockExternal.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_rbOutputFollower
            // 
            this.m_rbOutputFollower.AutoSize = true;
            this.m_rbOutputFollower.Location = new System.Drawing.Point(6, 19);
            this.m_rbOutputFollower.Name = "m_rbOutputFollower";
            this.m_rbOutputFollower.Size = new System.Drawing.Size(64, 17);
            this.m_rbOutputFollower.TabIndex = 2;
            this.m_rbOutputFollower.TabStop = true;
            this.m_rbOutputFollower.Text = "Follower";
            this.vdac13ToolTip.SetToolTip(this.m_rbOutputFollower, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.outputFeedbackToolTip);
            this.m_rbOutputFollower.UseVisualStyleBackColor = true;
            this.m_rbOutputFollower.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_rbOutputFeedback
            // 
            this.m_rbOutputFeedback.AutoSize = true;
            this.m_rbOutputFeedback.Location = new System.Drawing.Point(6, 42);
            this.m_rbOutputFeedback.Name = "m_rbOutputFeedback";
            this.m_rbOutputFeedback.Size = new System.Drawing.Size(59, 17);
            this.m_rbOutputFeedback.TabIndex = 1;
            this.m_rbOutputFeedback.TabStop = true;
            this.m_rbOutputFeedback.Text = "Opamp";
            this.vdac13ToolTip.SetToolTip(this.m_rbOutputFeedback, global::UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource.outputFeedbackToolTip);
            this.m_rbOutputFeedback.UseVisualStyleBackColor = true;
            this.m_rbOutputFeedback.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_gbReferenceVoltages
            // 
            this.m_gbReferenceVoltages.Controls.Add(this.m_cmbVagndSource);
            this.m_gbReferenceVoltages.Controls.Add(this.m_cmbVrefSource);
            this.m_gbReferenceVoltages.Controls.Add(this.m_lVrefVolts);
            this.m_gbReferenceVoltages.Controls.Add(this.m_lVagndVolts);
            this.m_gbReferenceVoltages.Controls.Add(this.m_nudVagndVolts);
            this.m_gbReferenceVoltages.Controls.Add(this.m_nudVrefVolts);
            this.m_gbReferenceVoltages.Location = new System.Drawing.Point(0, 95);
            this.m_gbReferenceVoltages.Name = "m_gbReferenceVoltages";
            this.m_gbReferenceVoltages.Size = new System.Drawing.Size(275, 77);
            this.m_gbReferenceVoltages.TabIndex = 1;
            this.m_gbReferenceVoltages.TabStop = false;
            this.m_gbReferenceVoltages.Text = "Reference Voltages";
            // 
            // m_lVrefVolts
            // 
            this.m_lVrefVolts.AutoSize = true;
            this.m_lVrefVolts.Location = new System.Drawing.Point(3, 21);
            this.m_lVrefVolts.Name = "m_lVrefVolts";
            this.m_lVrefVolts.Size = new System.Drawing.Size(45, 13);
            this.m_lVrefVolts.TabIndex = 13;
            this.m_lVrefVolts.Text = "Vref (V):";
            // 
            // m_lVagndVolts
            // 
            this.m_lVagndVolts.AutoSize = true;
            this.m_lVagndVolts.Location = new System.Drawing.Point(3, 49);
            this.m_lVagndVolts.Name = "m_lVagndVolts";
            this.m_lVagndVolts.Size = new System.Drawing.Size(57, 13);
            this.m_lVagndVolts.TabIndex = 1;
            this.m_lVagndVolts.Text = "Vagnd (V):";
            // 
            // m_tdTransferDiagramPanel
            // 
            this.m_tdTransferDiagramPanel.Controls.Add(this.groupBox4);
            this.m_tdTransferDiagramPanel.Location = new System.Drawing.Point(281, 3);
            this.m_tdTransferDiagramPanel.Name = "m_tdTransferDiagramPanel";
            this.m_tdTransferDiagramPanel.Size = new System.Drawing.Size(484, 315);
            this.m_tdTransferDiagramPanel.TabIndex = 4;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.m_rbModulatorNone);
            this.groupBox4.Controls.Add(this.m_rbModulatorExternal);
            this.groupBox4.Location = new System.Drawing.Point(3, 248);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(95, 67);
            this.groupBox4.TabIndex = 17;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Modulator Input";
            this.groupBox4.Visible = false;
            // 
            // m_rbModulatorNone
            // 
            this.m_rbModulatorNone.AutoSize = true;
            this.m_rbModulatorNone.Location = new System.Drawing.Point(6, 19);
            this.m_rbModulatorNone.Name = "m_rbModulatorNone";
            this.m_rbModulatorNone.Size = new System.Drawing.Size(51, 17);
            this.m_rbModulatorNone.TabIndex = 2;
            this.m_rbModulatorNone.TabStop = true;
            this.m_rbModulatorNone.Text = "None";
            this.m_rbModulatorNone.UseVisualStyleBackColor = true;
            this.m_rbModulatorNone.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_rbModulatorExternal
            // 
            this.m_rbModulatorExternal.AutoSize = true;
            this.m_rbModulatorExternal.Location = new System.Drawing.Point(6, 42);
            this.m_rbModulatorExternal.Name = "m_rbModulatorExternal";
            this.m_rbModulatorExternal.Size = new System.Drawing.Size(63, 17);
            this.m_rbModulatorExternal.TabIndex = 1;
            this.m_rbModulatorExternal.TabStop = true;
            this.m_rbModulatorExternal.Text = "External";
            this.m_rbModulatorExternal.UseVisualStyleBackColor = true;
            this.m_rbModulatorExternal.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.m_cmbDacGain);
            this.panel2.Controls.Add(this.m_cmbDacMode);
            this.panel2.Controls.Add(this.m_lDacGain);
            this.panel2.Controls.Add(this.m_lDacMode);
            this.panel2.Controls.Add(this.m_ldefaultOutVolts);
            this.panel2.Controls.Add(this.m_nudDefaultOutVolts);
            this.panel2.Location = new System.Drawing.Point(0, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(275, 86);
            this.panel2.TabIndex = 0;
            // 
            // m_lDacGain
            // 
            this.m_lDacGain.AutoSize = true;
            this.m_lDacGain.Location = new System.Drawing.Point(3, 61);
            this.m_lDacGain.Name = "m_lDacGain";
            this.m_lDacGain.Size = new System.Drawing.Size(62, 13);
            this.m_lDacGain.TabIndex = 4;
            this.m_lDacGain.Text = "DAC range:";
            // 
            // m_lDacMode
            // 
            this.m_lDacMode.AutoSize = true;
            this.m_lDacMode.Location = new System.Drawing.Point(3, 34);
            this.m_lDacMode.Name = "m_lDacMode";
            this.m_lDacMode.Size = new System.Drawing.Size(61, 13);
            this.m_lDacMode.TabIndex = 4;
            this.m_lDacMode.Text = "DAC mode:";
            // 
            // m_ldefaultOutVolts
            // 
            this.m_ldefaultOutVolts.AutoSize = true;
            this.m_ldefaultOutVolts.Location = new System.Drawing.Point(3, 7);
            this.m_ldefaultOutVolts.Name = "m_ldefaultOutVolts";
            this.m_ldefaultOutVolts.Size = new System.Drawing.Size(121, 13);
            this.m_ldefaultOutVolts.TabIndex = 5;
            this.m_ldefaultOutVolts.Text = "Initial output voltage (V):";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.m_rbStrobeContinous);
            this.groupBox1.Controls.Add(this.m_rbStrobeExternal);
            this.groupBox1.Location = new System.Drawing.Point(0, 178);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(134, 67);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Strobe Source";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.m_lClockRefreshValue);
            this.groupBox2.Controls.Add(this.m_nudClockFreq);
            this.groupBox2.Controls.Add(this.m_lClockRefresh);
            this.groupBox2.Controls.Add(this.m_lClockFreq);
            this.groupBox2.Controls.Add(this.m_rbClockInternal);
            this.groupBox2.Controls.Add(this.m_rbClockExternal);
            this.groupBox2.Location = new System.Drawing.Point(0, 251);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(275, 67);
            this.groupBox2.TabIndex = 15;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Clock Source";
            // 
            // m_lClockRefreshValue
            // 
            this.m_lClockRefreshValue.AutoSize = true;
            this.m_lClockRefreshValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lClockRefreshValue.Location = new System.Drawing.Point(160, 44);
            this.m_lClockRefreshValue.Name = "m_lClockRefreshValue";
            this.m_lClockRefreshValue.Size = new System.Drawing.Size(0, 13);
            this.m_lClockRefreshValue.TabIndex = 17;
            // 
            // m_lClockRefresh
            // 
            this.m_lClockRefresh.AutoSize = true;
            this.m_lClockRefresh.Location = new System.Drawing.Point(93, 44);
            this.m_lClockRefresh.Name = "m_lClockRefresh";
            this.m_lClockRefresh.Size = new System.Drawing.Size(68, 13);
            this.m_lClockRefresh.TabIndex = 15;
            this.m_lClockRefresh.Text = "Refresh rate:";
            // 
            // m_lClockFreq
            // 
            this.m_lClockFreq.AutoSize = true;
            this.m_lClockFreq.Location = new System.Drawing.Point(93, 21);
            this.m_lClockFreq.Name = "m_lClockFreq";
            this.m_lClockFreq.Size = new System.Drawing.Size(59, 13);
            this.m_lClockFreq.TabIndex = 14;
            this.m_lClockFreq.Text = "Freq (kHz):";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.m_rbOutputFollower);
            this.groupBox3.Controls.Add(this.m_rbOutputFeedback);
            this.groupBox3.Location = new System.Drawing.Point(140, 178);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(135, 67);
            this.groupBox3.TabIndex = 16;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Output Stage";
            // 
            // CyUAB_VDAC_v1_10Control
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.m_gbReferenceVoltages);
            this.Controls.Add(this.m_tdTransferDiagramPanel);
            this.Name = "CyUAB_VDAC_v1_10Control";
            this.Size = new System.Drawing.Size(690, 232);
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVrefVolts)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVagndVolts)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDefaultOutVolts)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudClockFreq)).EndInit();
            this.m_gbReferenceVoltages.ResumeLayout(false);
            this.m_gbReferenceVoltages.PerformLayout();
            this.m_tdTransferDiagramPanel.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private ToolTip vdac13ToolTip;
        private GroupBox m_gbReferenceVoltages;
        private ComboBox m_cmbVagndSource;
        private ComboBox m_cmbVrefSource;
        private Label m_lVrefVolts;
        private Label m_lVagndVolts;
        private NumericUpDown m_nudVagndVolts;
        private NumericUpDown m_nudVrefVolts;
        private Panel m_tdTransferDiagramPanel;
        private Panel panel2;
        private ComboBox m_cmbDacGain;
        private ComboBox m_cmbDacMode;
        private Label m_lDacGain;
        private Label m_lDacMode;
        private Label m_ldefaultOutVolts;
        private NumericUpDown m_nudDefaultOutVolts;
        private GroupBox groupBox1;
        private RadioButton m_rbStrobeContinous;
        private RadioButton m_rbStrobeExternal;
        private GroupBox groupBox2;
        private Label m_lClockRefreshValue;
        private NumericUpDown m_nudClockFreq;
        private Label m_lClockRefresh;
        private Label m_lClockFreq;
        private RadioButton m_rbClockInternal;
        private RadioButton m_rbClockExternal;
        private GroupBox groupBox3;
        private RadioButton m_rbOutputFollower;
        private RadioButton m_rbOutputFeedback;
        private GroupBox groupBox4;
        private RadioButton m_rbModulatorNone;
        private RadioButton m_rbModulatorExternal;
    }
}
