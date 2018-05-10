/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


namespace TCPWM_P4_v2_0
{
    partial class CyPWMTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyPWMTab));
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.m_label0 = new System.Windows.Forms.Label();
            this.m_cbPrescaler = new System.Windows.Forms.ComboBox();
            this.m_pbPWMGraph = new System.Windows.Forms.PictureBox();
            this.m_panelMain = new System.Windows.Forms.Panel();
            this.numUpDownDeadTime = new System.Windows.Forms.NumericUpDown();
            this.registerGrid = new TCPWM_P4_v2_0.CyRegisterGrid();
            this.m_labelRunMode = new System.Windows.Forms.Label();
            this.m_cbRunMode = new System.Windows.Forms.ComboBox();
            this.groupBoxInterrupt = new System.Windows.Forms.GroupBox();
            this.m_cbInterruptOnTC = new System.Windows.Forms.CheckBox();
            this.m_cbInterruptOnCC = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.dgvAdvanced = new System.Windows.Forms.DataGridView();
            this.ColumnLabel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnPresent = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ColumnMode = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.labelDtCycle = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.m_cbStopEvent = new System.Windows.Forms.ComboBox();
            this.m_cbKillEvent = new System.Windows.Forms.ComboBox();
            this.m_cbOutCCInvert = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.m_cbAlign = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.m_cbOutLineInvert = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.m_cbPwmMode = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.panelPicture = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbPWMGraph)).BeginInit();
            this.m_panelMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownDeadTime)).BeginInit();
            this.groupBoxInterrupt.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAdvanced)).BeginInit();
            this.panelPicture.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_label0
            // 
            resources.ApplyResources(this.m_label0, "m_label0");
            this.m_label0.Name = "m_label0";
            // 
            // m_cbPrescaler
            // 
            this.m_cbPrescaler.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbPrescaler.FormattingEnabled = true;
            this.m_cbPrescaler.Items.AddRange(new object[] {
            resources.GetString("m_cbPrescaler.Items"),
            resources.GetString("m_cbPrescaler.Items1"),
            resources.GetString("m_cbPrescaler.Items2"),
            resources.GetString("m_cbPrescaler.Items3"),
            resources.GetString("m_cbPrescaler.Items4"),
            resources.GetString("m_cbPrescaler.Items5"),
            resources.GetString("m_cbPrescaler.Items6")});
            resources.ApplyResources(this.m_cbPrescaler, "m_cbPrescaler");
            this.m_cbPrescaler.Name = "m_cbPrescaler";
            // 
            // m_pbPWMGraph
            // 
            this.m_pbPWMGraph.BackColor = System.Drawing.Color.White;
            resources.ApplyResources(this.m_pbPWMGraph, "m_pbPWMGraph");
            this.m_pbPWMGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_pbPWMGraph.Name = "m_pbPWMGraph";
            this.m_pbPWMGraph.TabStop = false;
            // 
            // m_panelMain
            // 
            this.m_panelMain.Controls.Add(this.numUpDownDeadTime);
            this.m_panelMain.Controls.Add(this.registerGrid);
            this.m_panelMain.Controls.Add(this.m_labelRunMode);
            this.m_panelMain.Controls.Add(this.m_cbPrescaler);
            this.m_panelMain.Controls.Add(this.m_cbRunMode);
            this.m_panelMain.Controls.Add(this.groupBoxInterrupt);
            this.m_panelMain.Controls.Add(this.label4);
            this.m_panelMain.Controls.Add(this.dgvAdvanced);
            this.m_panelMain.Controls.Add(this.labelDtCycle);
            this.m_panelMain.Controls.Add(this.label3);
            this.m_panelMain.Controls.Add(this.m_cbStopEvent);
            this.m_panelMain.Controls.Add(this.m_cbKillEvent);
            this.m_panelMain.Controls.Add(this.m_cbOutCCInvert);
            this.m_panelMain.Controls.Add(this.label2);
            this.m_panelMain.Controls.Add(this.m_cbAlign);
            this.m_panelMain.Controls.Add(this.label6);
            this.m_panelMain.Controls.Add(this.m_cbOutLineInvert);
            this.m_panelMain.Controls.Add(this.m_label0);
            this.m_panelMain.Controls.Add(this.label1);
            this.m_panelMain.Controls.Add(this.m_cbPwmMode);
            this.m_panelMain.Controls.Add(this.label5);
            resources.ApplyResources(this.m_panelMain, "m_panelMain");
            this.m_panelMain.Name = "m_panelMain";
            // 
            // numUpDownDeadTime
            // 
            resources.ApplyResources(this.numUpDownDeadTime, "numUpDownDeadTime");
            this.numUpDownDeadTime.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownDeadTime.Name = "numUpDownDeadTime";
            // 
            // registerGrid
            // 
            resources.ApplyResources(this.registerGrid, "registerGrid");
            this.registerGrid.Name = "registerGrid";
            this.registerGrid.DataChanged += new System.EventHandler(this.registerGrid_DataChanged);
            // 
            // m_labelRunMode
            // 
            resources.ApplyResources(this.m_labelRunMode, "m_labelRunMode");
            this.m_labelRunMode.Name = "m_labelRunMode";
            // 
            // m_cbRunMode
            // 
            this.m_cbRunMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRunMode.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbRunMode, "m_cbRunMode");
            this.m_cbRunMode.Name = "m_cbRunMode";
            // 
            // groupBoxInterrupt
            // 
            this.groupBoxInterrupt.Controls.Add(this.m_cbInterruptOnTC);
            this.groupBoxInterrupt.Controls.Add(this.m_cbInterruptOnCC);
            resources.ApplyResources(this.groupBoxInterrupt, "groupBoxInterrupt");
            this.groupBoxInterrupt.Name = "groupBoxInterrupt";
            this.groupBoxInterrupt.TabStop = false;
            // 
            // m_cbInterruptOnTC
            // 
            resources.ApplyResources(this.m_cbInterruptOnTC, "m_cbInterruptOnTC");
            this.m_cbInterruptOnTC.Name = "m_cbInterruptOnTC";
            this.m_cbInterruptOnTC.UseVisualStyleBackColor = true;
            // 
            // m_cbInterruptOnCC
            // 
            resources.ApplyResources(this.m_cbInterruptOnCC, "m_cbInterruptOnCC");
            this.m_cbInterruptOnCC.Name = "m_cbInterruptOnCC";
            this.m_cbInterruptOnCC.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.Name = "label4";
            // 
            // dgvAdvanced
            // 
            this.dgvAdvanced.AllowUserToAddRows = false;
            this.dgvAdvanced.AllowUserToDeleteRows = false;
            this.dgvAdvanced.AllowUserToOrderColumns = true;
            this.dgvAdvanced.AllowUserToResizeColumns = false;
            this.dgvAdvanced.AllowUserToResizeRows = false;
            this.dgvAdvanced.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvAdvanced.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvAdvanced.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnLabel,
            this.ColumnPresent,
            this.ColumnMode});
            this.dgvAdvanced.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            resources.ApplyResources(this.dgvAdvanced, "dgvAdvanced");
            this.dgvAdvanced.Name = "dgvAdvanced";
            this.dgvAdvanced.RowHeadersVisible = false;
            this.dgvAdvanced.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgvAdvanced_CurrentCellDirtyStateChanged);
            // 
            // ColumnLabel
            // 
            this.ColumnLabel.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.ControlText;
            this.ColumnLabel.DefaultCellStyle = dataGridViewCellStyle1;
            this.ColumnLabel.FillWeight = 106.599F;
            resources.ApplyResources(this.ColumnLabel, "ColumnLabel");
            this.ColumnLabel.Name = "ColumnLabel";
            this.ColumnLabel.ReadOnly = true;
            this.ColumnLabel.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // ColumnPresent
            // 
            this.ColumnPresent.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.ColumnPresent.FillWeight = 96.70051F;
            resources.ApplyResources(this.ColumnPresent, "ColumnPresent");
            this.ColumnPresent.Name = "ColumnPresent";
            // 
            // ColumnMode
            // 
            this.ColumnMode.FillWeight = 96.70051F;
            resources.ApplyResources(this.ColumnMode, "ColumnMode");
            this.ColumnMode.Name = "ColumnMode";
            // 
            // labelDtCycle
            // 
            resources.ApplyResources(this.labelDtCycle, "labelDtCycle");
            this.labelDtCycle.Name = "labelDtCycle";
            // 
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
            // 
            // m_cbStopEvent
            // 
            this.m_cbStopEvent.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbStopEvent.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbStopEvent, "m_cbStopEvent");
            this.m_cbStopEvent.Name = "m_cbStopEvent";
            // 
            // m_cbKillEvent
            // 
            this.m_cbKillEvent.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbKillEvent.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbKillEvent, "m_cbKillEvent");
            this.m_cbKillEvent.Name = "m_cbKillEvent";
            // 
            // m_cbOutCCInvert
            // 
            this.m_cbOutCCInvert.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbOutCCInvert.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbOutCCInvert, "m_cbOutCCInvert");
            this.m_cbOutCCInvert.Name = "m_cbOutCCInvert";
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // m_cbAlign
            // 
            this.m_cbAlign.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbAlign.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbAlign, "m_cbAlign");
            this.m_cbAlign.Name = "m_cbAlign";
            // 
            // label6
            // 
            resources.ApplyResources(this.label6, "label6");
            this.label6.Name = "label6";
            // 
            // m_cbOutLineInvert
            // 
            this.m_cbOutLineInvert.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbOutLineInvert.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbOutLineInvert, "m_cbOutLineInvert");
            this.m_cbOutLineInvert.Name = "m_cbOutLineInvert";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // m_cbPwmMode
            // 
            this.m_cbPwmMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbPwmMode.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbPwmMode, "m_cbPwmMode");
            this.m_cbPwmMode.Name = "m_cbPwmMode";
            // 
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.Name = "label5";
            // 
            // panelPicture
            // 
            resources.ApplyResources(this.panelPicture, "panelPicture");
            this.panelPicture.Controls.Add(this.m_pbPWMGraph);
            this.panelPicture.Name = "panelPicture";
            // 
            // CyPWMTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panelPicture);
            this.Controls.Add(this.m_panelMain);
            this.Name = "CyPWMTab";
            ((System.ComponentModel.ISupportInitialize)(this.m_pbPWMGraph)).EndInit();
            this.m_panelMain.ResumeLayout(false);
            this.m_panelMain.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownDeadTime)).EndInit();
            this.groupBoxInterrupt.ResumeLayout(false);
            this.groupBoxInterrupt.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAdvanced)).EndInit();
            this.panelPicture.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label m_label0;
        private System.Windows.Forms.ComboBox m_cbPrescaler;
        private System.Windows.Forms.PictureBox m_pbPWMGraph;
        private System.Windows.Forms.Panel m_panelMain;
        private System.Windows.Forms.DataGridView dgvAdvanced;
        private System.Windows.Forms.GroupBox groupBoxInterrupt;
        private System.Windows.Forms.CheckBox m_cbInterruptOnTC;
        private System.Windows.Forms.CheckBox m_cbInterruptOnCC;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox m_cbPwmMode;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox m_cbAlign;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox m_cbStopEvent;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox m_cbKillEvent;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox m_cbOutLineInvert;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox m_cbOutCCInvert;
        private System.Windows.Forms.Label labelDtCycle;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnLabel;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColumnPresent;
        private System.Windows.Forms.DataGridViewComboBoxColumn ColumnMode;
        private System.Windows.Forms.Panel panelPicture;
        private System.Windows.Forms.Label m_labelRunMode;
        private System.Windows.Forms.ComboBox m_cbRunMode;
        private CyRegisterGrid registerGrid;
        private System.Windows.Forms.NumericUpDown numUpDownDeadTime;
    }
}
