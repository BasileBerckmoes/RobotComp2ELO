/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


namespace TCPWM_P4_v2_10
{
    partial class CyQuadDecTab
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.label1 = new System.Windows.Forms.Label();
            this.m_cbEncodingMode = new System.Windows.Forms.ComboBox();
            this.groupBoxInterrupt = new System.Windows.Forms.GroupBox();
            this.m_cbInterruptOnTC = new System.Windows.Forms.CheckBox();
            this.m_cbInterruptOnCC = new System.Windows.Forms.CheckBox();
            this.dgvAdvanced = new System.Windows.Forms.DataGridView();
            this.ColumnLabel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnPresent = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ColumnMode = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.groupBoxInterrupt.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAdvanced)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.label1.Location = new System.Drawing.Point(3, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 13);
            this.label1.TabIndex = 40;
            this.label1.Text = "Encoding mode:";
            // 
            // m_cbEncodingMode
            // 
            this.m_cbEncodingMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbEncodingMode.FormattingEnabled = true;
            this.m_cbEncodingMode.Location = new System.Drawing.Point(93, 6);
            this.m_cbEncodingMode.Name = "m_cbEncodingMode";
            this.m_cbEncodingMode.Size = new System.Drawing.Size(87, 21);
            this.m_cbEncodingMode.TabIndex = 1;
            // 
            // groupBoxInterrupt
            // 
            this.groupBoxInterrupt.Controls.Add(this.m_cbInterruptOnTC);
            this.groupBoxInterrupt.Controls.Add(this.m_cbInterruptOnCC);
            this.groupBoxInterrupt.Location = new System.Drawing.Point(6, 33);
            this.groupBoxInterrupt.Name = "groupBoxInterrupt";
            this.groupBoxInterrupt.Size = new System.Drawing.Size(174, 68);
            this.groupBoxInterrupt.TabIndex = 2;
            this.groupBoxInterrupt.TabStop = false;
            this.groupBoxInterrupt.Text = "Interrupt";
            // 
            // m_cbInterruptOnTC
            // 
            this.m_cbInterruptOnTC.AutoSize = true;
            this.m_cbInterruptOnTC.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.m_cbInterruptOnTC.Location = new System.Drawing.Point(6, 19);
            this.m_cbInterruptOnTC.Name = "m_cbInterruptOnTC";
            this.m_cbInterruptOnTC.Size = new System.Drawing.Size(109, 17);
            this.m_cbInterruptOnTC.TabIndex = 25;
            this.m_cbInterruptOnTC.Text = "On terminal count";
            this.m_cbInterruptOnTC.UseVisualStyleBackColor = true;
            // 
            // m_cbInterruptOnCC
            // 
            this.m_cbInterruptOnCC.AutoSize = true;
            this.m_cbInterruptOnCC.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.m_cbInterruptOnCC.Location = new System.Drawing.Point(6, 42);
            this.m_cbInterruptOnCC.Name = "m_cbInterruptOnCC";
            this.m_cbInterruptOnCC.Size = new System.Drawing.Size(155, 17);
            this.m_cbInterruptOnCC.TabIndex = 26;
            this.m_cbInterruptOnCC.Text = "On compare/capture count";
            this.m_cbInterruptOnCC.UseVisualStyleBackColor = true;
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
            this.dgvAdvanced.Location = new System.Drawing.Point(234, 6);
            this.dgvAdvanced.Name = "dgvAdvanced";
            this.dgvAdvanced.RowHeadersVisible = false;
            this.dgvAdvanced.Size = new System.Drawing.Size(221, 111);
            this.dgvAdvanced.TabIndex = 3;
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
            this.ColumnLabel.HeaderText = "Input";
            this.ColumnLabel.Name = "ColumnLabel";
            this.ColumnLabel.ReadOnly = true;
            this.ColumnLabel.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.ColumnLabel.Width = 37;
            // 
            // ColumnPresent
            // 
            this.ColumnPresent.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.ColumnPresent.FillWeight = 96.70051F;
            this.ColumnPresent.HeaderText = "Present";
            this.ColumnPresent.Name = "ColumnPresent";
            this.ColumnPresent.Width = 49;
            // 
            // ColumnMode
            // 
            this.ColumnMode.FillWeight = 96.70051F;
            this.ColumnMode.HeaderText = "Mode";
            this.ColumnMode.Name = "ColumnMode";
            // 
            // CyQuadDecTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.m_cbEncodingMode);
            this.Controls.Add(this.groupBoxInterrupt);
            this.Controls.Add(this.dgvAdvanced);
            this.Name = "CyQuadDecTab";
            this.Size = new System.Drawing.Size(544, 242);
            this.groupBoxInterrupt.ResumeLayout(false);
            this.groupBoxInterrupt.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAdvanced)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox m_cbEncodingMode;
        private System.Windows.Forms.GroupBox groupBoxInterrupt;
        private System.Windows.Forms.CheckBox m_cbInterruptOnTC;
        private System.Windows.Forms.CheckBox m_cbInterruptOnCC;
        private System.Windows.Forms.DataGridView dgvAdvanced;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnLabel;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColumnPresent;
        private System.Windows.Forms.DataGridViewComboBoxColumn ColumnMode;

    }
}
