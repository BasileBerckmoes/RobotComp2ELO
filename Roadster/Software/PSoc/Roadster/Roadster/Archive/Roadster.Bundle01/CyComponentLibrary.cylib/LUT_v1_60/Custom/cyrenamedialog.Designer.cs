namespace LUT_v1_60
{
    partial class CyRenameDialog
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.buttonOk = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.m_placeHolderPanel = new System.Windows.Forms.Panel();
            this.m_dgv = new System.Windows.Forms.DataGridView();
            this.m_colDefaultName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_colNewName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_placeHolderPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgv)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonOk
            // 
            this.buttonOk.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonOk.AutoSize = true;
            this.buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.buttonOk.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.buttonOk.Location = new System.Drawing.Point(158, 274);
            this.buttonOk.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.buttonOk.Name = "buttonOk";
            this.buttonOk.Size = new System.Drawing.Size(75, 24);
            this.buttonOk.TabIndex = 7;
            this.buttonOk.Text = "OK";
            this.buttonOk.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Location = new System.Drawing.Point(9, 268);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox1.Size = new System.Drawing.Size(224, 2);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            // 
            // m_placeHolderPanel
            // 
            this.m_placeHolderPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_placeHolderPanel.Controls.Add(this.m_dgv);
            this.m_placeHolderPanel.Location = new System.Drawing.Point(9, 8);
            this.m_placeHolderPanel.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.m_placeHolderPanel.Name = "m_placeHolderPanel";
            this.m_placeHolderPanel.Size = new System.Drawing.Size(224, 250);
            this.m_placeHolderPanel.TabIndex = 8;
            // 
            // m_dgv
            // 
            this.m_dgv.AllowUserToAddRows = false;
            this.m_dgv.AllowUserToDeleteRows = false;
            this.m_dgv.AllowUserToResizeColumns = false;
            this.m_dgv.AllowUserToResizeRows = false;
            this.m_dgv.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_dgv.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.m_colDefaultName,
            this.m_colNewName});
            this.m_dgv.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_dgv.Location = new System.Drawing.Point(0, 0);
            this.m_dgv.Name = "m_dgv";
            this.m_dgv.RowHeadersVisible = false;
            this.m_dgv.Size = new System.Drawing.Size(224, 250);
            this.m_dgv.TabIndex = 0;
            this.m_dgv.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_dgv_CellValueChanged);
            // 
            // m_colDefaultName
            // 
            this.m_colDefaultName.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.LightGray;
            this.m_colDefaultName.DefaultCellStyle = dataGridViewCellStyle2;
            this.m_colDefaultName.HeaderText = "Default name";
            this.m_colDefaultName.Name = "m_colDefaultName";
            this.m_colDefaultName.ReadOnly = true;
            this.m_colDefaultName.Width = 95;
            // 
            // m_colNewName
            // 
            this.m_colNewName.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_colNewName.HeaderText = "New name";
            this.m_colNewName.MaxInputLength = 10;
            this.m_colNewName.Name = "m_colNewName";
            // 
            // CyRenameDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(242, 304);
            this.Controls.Add(this.m_placeHolderPanel);
            this.Controls.Add(this.buttonOk);
            this.Controls.Add(this.groupBox1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(144, 129);
            this.Name = "CyRenameDialog";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Rename Terminals";
            this.m_placeHolderPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_dgv)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOk;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Panel m_placeHolderPanel;
        private System.Windows.Forms.DataGridView m_dgv;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_colDefaultName;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_colNewName;

    }
}