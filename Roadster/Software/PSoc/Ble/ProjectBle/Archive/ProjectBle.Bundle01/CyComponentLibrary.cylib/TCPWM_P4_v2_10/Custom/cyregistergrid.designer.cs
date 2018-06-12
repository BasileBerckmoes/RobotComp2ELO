namespace TCPWM_P4_v2_10
{
    partial class CyRegisterGrid
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dgvRegisters = new System.Windows.Forms.DataGridView();
            this.ColHeader = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColRegister1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColSwap = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ColRegister2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvRegisters
            // 
            this.dgvRegisters.AllowUserToAddRows = false;
            this.dgvRegisters.AllowUserToDeleteRows = false;
            this.dgvRegisters.AllowUserToResizeColumns = false;
            this.dgvRegisters.AllowUserToResizeRows = false;
            this.dgvRegisters.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dgvRegisters.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvRegisters.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColHeader,
            this.ColRegister1,
            this.ColSwap,
            this.ColRegister2});
            this.dgvRegisters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvRegisters.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.dgvRegisters.Location = new System.Drawing.Point(0, 0);
            this.dgvRegisters.Name = "dgvRegisters";
            this.dgvRegisters.RowHeadersVisible = false;
            this.dgvRegisters.Size = new System.Drawing.Size(221, 99);
            this.dgvRegisters.TabIndex = 9;
            this.dgvRegisters.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvRegisters_CellValueChanged);
            // 
            // ColHeader
            // 
            this.ColHeader.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.ControlText;
            this.ColHeader.DefaultCellStyle = dataGridViewCellStyle3;
            this.ColHeader.HeaderText = "";
            this.ColHeader.Name = "ColHeader";
            this.ColHeader.ReadOnly = true;
            this.ColHeader.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.ColHeader.Width = 5;
            // 
            // ColRegister1
            // 
            this.ColRegister1.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ColRegister1.HeaderText = "Register";
            this.ColRegister1.Name = "ColRegister1";
            this.ColRegister1.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // ColSwap
            // 
            this.ColSwap.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.ColSwap.HeaderText = "Swap";
            this.ColSwap.Name = "ColSwap";
            this.ColSwap.Width = 40;
            // 
            // ColRegister2
            // 
            this.ColRegister2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ColRegister2.HeaderText = "RegisterBuf";
            this.ColRegister2.Name = "ColRegister2";
            this.ColRegister2.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // CyRegisterGrid
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.dgvRegisters);
            this.Name = "CyRegisterGrid";
            this.Size = new System.Drawing.Size(221, 99);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvRegisters;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColHeader;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColRegister1;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColSwap;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColRegister2;
    }
}
