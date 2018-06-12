namespace ScanComp_v1_10
{
    partial class CyChannelsTab
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            this.lblChannels = new System.Windows.Forms.Label();
            this.numChannels = new System.Windows.Forms.NumericUpDown();
            this.dgvChannels = new System.Windows.Forms.DataGridView();
            this.colChannelNum = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colInterruptMode = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.colDacVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.numChannels)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvChannels)).BeginInit();
            this.SuspendLayout();
            // 
            // lblChannels
            // 
            this.lblChannels.AutoSize = true;
            this.lblChannels.Location = new System.Drawing.Point(3, 10);
            this.lblChannels.Name = "lblChannels";
            this.lblChannels.Size = new System.Drawing.Size(111, 13);
            this.lblChannels.TabIndex = 0;
            this.lblChannels.Text = "Sequenced channels:";
            // 
            // numChannels
            // 
            this.numChannels.Location = new System.Drawing.Point(121, 8);
            this.numChannels.Name = "numChannels";
            this.numChannels.Size = new System.Drawing.Size(71, 20);
            this.numChannels.TabIndex = 0;
            // 
            // dgvChannels
            // 
            this.dgvChannels.AllowUserToAddRows = false;
            this.dgvChannels.AllowUserToDeleteRows = false;
            this.dgvChannels.AllowUserToResizeColumns = false;
            this.dgvChannels.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgvChannels.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dgvChannels.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            this.dgvChannels.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colChannelNum,
            this.colInterruptMode,
            this.colDacVoltage});
            this.dgvChannels.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.dgvChannels.Location = new System.Drawing.Point(6, 34);
            this.dgvChannels.Name = "dgvChannels";
            this.dgvChannels.RowHeadersVisible = false;
            this.dgvChannels.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dgvChannels.Size = new System.Drawing.Size(332, 41);
            this.dgvChannels.TabIndex = 1;
            this.dgvChannels.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvChannels_CellValueChanged);
            // 
            // colChannelNum
            // 
            this.colChannelNum.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.LightGray;
            this.colChannelNum.DefaultCellStyle = dataGridViewCellStyle2;
            this.colChannelNum.HeaderText = "Channel";
            this.colChannelNum.Name = "colChannelNum";
            this.colChannelNum.ReadOnly = true;
            this.colChannelNum.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.colChannelNum.Width = 52;
            // 
            // colInterruptMode
            // 
            this.colInterruptMode.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.colInterruptMode.DefaultCellStyle = dataGridViewCellStyle3;
            this.colInterruptMode.HeaderText = "Interrupt mode";
            this.colInterruptMode.Name = "colInterruptMode";
            // 
            // colDacVoltage
            // 
            this.colDacVoltage.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.colDacVoltage.DefaultCellStyle = dataGridViewCellStyle4;
            this.colDacVoltage.HeaderText = "DAC voltage (mV)";
            this.colDacVoltage.Name = "colDacVoltage";
            this.colDacVoltage.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.colDacVoltage.Width = 97;
            // 
            // CyChannelsTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.dgvChannels);
            this.Controls.Add(this.numChannels);
            this.Controls.Add(this.lblChannels);
            this.Name = "CyChannelsTab";
            this.Size = new System.Drawing.Size(353, 90);
            this.VisibleChanged += new System.EventHandler(this.CyChannelsTab_VisibleChanged);
            ((System.ComponentModel.ISupportInitialize)(this.numChannels)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvChannels)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblChannels;
        private System.Windows.Forms.NumericUpDown numChannels;
        private System.Windows.Forms.DataGridView dgvChannels;
        private System.Windows.Forms.DataGridViewTextBoxColumn colChannelNum;
        private System.Windows.Forms.DataGridViewComboBoxColumn colInterruptMode;
        private System.Windows.Forms.DataGridViewTextBoxColumn colDacVoltage;
    }
}
