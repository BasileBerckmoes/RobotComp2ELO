namespace I2C_LCD_v1_20
{
    partial class CyCustomCommandsTab
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.gbRequiredCommands = new System.Windows.Forms.GroupBox();
            this.dgvRequiredCmds = new System.Windows.Forms.DataGridView();
            this.colReqCmdSize = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.colReqDataSize = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colReqCmdByte1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colReqCmdByte2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colReqCmdByte3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colReqCmdByte4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colReqCmdDesc = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.gbCustomCommands = new System.Windows.Forms.GroupBox();
            this.dgvCustomCmds = new System.Windows.Forms.DataGridView();
            this.colCustEnable = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.colCustCmdSize = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.colCustDataSize = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCustCmdByte1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCustCmdByte2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCustCmdByte3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCustCmdByte4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCustApiName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.dataSet1 = new System.Data.DataSet();
            this.dataTable1 = new System.Data.DataTable();
            this.panel1 = new System.Windows.Forms.Panel();
            this.chbCommandPattern = new System.Windows.Forms.CheckBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.gbRequiredCommands.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvRequiredCmds)).BeginInit();
            this.gbCustomCommands.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvCustomCmds)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataTable1)).BeginInit();
            this.panel1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbRequiredCommands
            // 
            this.gbRequiredCommands.Controls.Add(this.dgvRequiredCmds);
            this.gbRequiredCommands.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbRequiredCommands.Location = new System.Drawing.Point(3, 3);
            this.gbRequiredCommands.Name = "gbRequiredCommands";
            this.gbRequiredCommands.Size = new System.Drawing.Size(853, 242);
            this.gbRequiredCommands.TabIndex = 1;
            this.gbRequiredCommands.TabStop = false;
            this.gbRequiredCommands.Text = "Required commands";
            // 
            // dgvRequiredCmds
            // 
            this.dgvRequiredCmds.AllowUserToAddRows = false;
            this.dgvRequiredCmds.AllowUserToDeleteRows = false;
            this.dgvRequiredCmds.AllowUserToResizeRows = false;
            this.dgvRequiredCmds.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvRequiredCmds.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvRequiredCmds.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colReqCmdSize,
            this.colReqDataSize,
            this.colReqCmdByte1,
            this.colReqCmdByte2,
            this.colReqCmdByte3,
            this.colReqCmdByte4,
            this.colReqCmdDesc});
            this.dgvRequiredCmds.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvRequiredCmds.Location = new System.Drawing.Point(3, 16);
            this.dgvRequiredCmds.Name = "dgvRequiredCmds";
            this.dgvRequiredCmds.RowHeadersVisible = false;
            this.dgvRequiredCmds.Size = new System.Drawing.Size(847, 223);
            this.dgvRequiredCmds.TabIndex = 0;
            this.dgvRequiredCmds.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dgv_CellFormatting);
            this.dgvRequiredCmds.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvRequiredCmds_CellValueChanged);
            this.dgvRequiredCmds.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgv_CurrentCellDirtyStateChanged);
            // 
            // colReqCmdSize
            // 
            this.colReqCmdSize.HeaderText = "Command size";
            this.colReqCmdSize.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4"});
            this.colReqCmdSize.Name = "colReqCmdSize";
            this.colReqCmdSize.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.colReqCmdSize.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // colReqDataSize
            // 
            this.colReqDataSize.HeaderText = "Data size";
            this.colReqDataSize.Name = "colReqDataSize";
            // 
            // colReqCmdByte1
            // 
            this.colReqCmdByte1.HeaderText = "CMD byte 1";
            this.colReqCmdByte1.Name = "colReqCmdByte1";
            // 
            // colReqCmdByte2
            // 
            this.colReqCmdByte2.HeaderText = "CMD byte 2";
            this.colReqCmdByte2.Name = "colReqCmdByte2";
            // 
            // colReqCmdByte3
            // 
            this.colReqCmdByte3.HeaderText = "CMD byte 3";
            this.colReqCmdByte3.Name = "colReqCmdByte3";
            // 
            // colReqCmdByte4
            // 
            this.colReqCmdByte4.HeaderText = "CMD byte 4";
            this.colReqCmdByte4.Name = "colReqCmdByte4";
            // 
            // colReqCmdDesc
            // 
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.colReqCmdDesc.DefaultCellStyle = dataGridViewCellStyle1;
            this.colReqCmdDesc.HeaderText = "Command description";
            this.colReqCmdDesc.Name = "colReqCmdDesc";
            // 
            // gbCustomCommands
            // 
            this.gbCustomCommands.Controls.Add(this.dgvCustomCmds);
            this.gbCustomCommands.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbCustomCommands.Location = new System.Drawing.Point(3, 251);
            this.gbCustomCommands.Name = "gbCustomCommands";
            this.gbCustomCommands.Size = new System.Drawing.Size(853, 271);
            this.gbCustomCommands.TabIndex = 2;
            this.gbCustomCommands.TabStop = false;
            this.gbCustomCommands.Text = "Custom commands";
            // 
            // dgvCustomCmds
            // 
            this.dgvCustomCmds.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvCustomCmds.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvCustomCmds.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colCustEnable,
            this.colCustCmdSize,
            this.colCustDataSize,
            this.colCustCmdByte1,
            this.colCustCmdByte2,
            this.colCustCmdByte3,
            this.colCustCmdByte4,
            this.colCustApiName});
            this.dgvCustomCmds.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvCustomCmds.Location = new System.Drawing.Point(3, 16);
            this.dgvCustomCmds.Name = "dgvCustomCmds";
            this.dgvCustomCmds.Size = new System.Drawing.Size(847, 252);
            this.dgvCustomCmds.TabIndex = 0;
            this.dgvCustomCmds.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dgv_CellFormatting);
            this.dgvCustomCmds.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvCustomCmds_CellValueChanged);
            this.dgvCustomCmds.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgv_CurrentCellDirtyStateChanged);
            this.dgvCustomCmds.RowHeaderMouseDoubleClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dgvCustomCmds_RowHeaderMouseDoubleClick);
            this.dgvCustomCmds.RowsAdded += new System.Windows.Forms.DataGridViewRowsAddedEventHandler(this.dgvCustomCmds_RowsAdded);
            this.dgvCustomCmds.MouseDown += new System.Windows.Forms.MouseEventHandler(this.dgvCustomCmds_MouseDown);
            // 
            // colCustEnable
            // 
            this.colCustEnable.HeaderText = "Enable";
            this.colCustEnable.Name = "colCustEnable";
            // 
            // colCustCmdSize
            // 
            this.colCustCmdSize.HeaderText = "Command size";
            this.colCustCmdSize.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4"});
            this.colCustCmdSize.Name = "colCustCmdSize";
            this.colCustCmdSize.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.colCustCmdSize.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // colCustDataSize
            // 
            this.colCustDataSize.HeaderText = "Data size";
            this.colCustDataSize.Name = "colCustDataSize";
            // 
            // colCustCmdByte1
            // 
            this.colCustCmdByte1.HeaderText = "CMD byte 1";
            this.colCustCmdByte1.Name = "colCustCmdByte1";
            // 
            // colCustCmdByte2
            // 
            this.colCustCmdByte2.HeaderText = "CMD byte 2";
            this.colCustCmdByte2.Name = "colCustCmdByte2";
            // 
            // colCustCmdByte3
            // 
            this.colCustCmdByte3.HeaderText = "CMD byte 3";
            this.colCustCmdByte3.Name = "colCustCmdByte3";
            // 
            // colCustCmdByte4
            // 
            this.colCustCmdByte4.HeaderText = "CMD byte 4";
            this.colCustCmdByte4.Name = "colCustCmdByte4";
            // 
            // colCustApiName
            // 
            this.colCustApiName.HeaderText = "API name";
            this.colCustApiName.Name = "colCustApiName";
            // 
            // dataSet1
            // 
            this.dataSet1.DataSetName = "NewDataSet";
            this.dataSet1.Tables.AddRange(new System.Data.DataTable[] {
            this.dataTable1});
            // 
            // dataTable1
            // 
            this.dataTable1.TableName = "Table1";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.chbCommandPattern);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(859, 24);
            this.panel1.TabIndex = 0;
            // 
            // chbCommandPattern
            // 
            this.chbCommandPattern.AutoSize = true;
            this.chbCommandPattern.Location = new System.Drawing.Point(0, 4);
            this.chbCommandPattern.Name = "chbCommandPattern";
            this.chbCommandPattern.Size = new System.Drawing.Size(202, 17);
            this.chbCommandPattern.TabIndex = 0;
            this.chbCommandPattern.Text = "Use command pattern for data writing";
            this.chbCommandPattern.UseVisualStyleBackColor = true;
            this.chbCommandPattern.CheckedChanged += new System.EventHandler(this.chbCommandPattern_CheckedChanged);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.gbRequiredCommands, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.gbCustomCommands, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 47.36842F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 52.63158F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(859, 525);
            this.tableLayoutPanel1.TabIndex = 3;
            // 
            // CyCustomCommandsTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoScrollMinSize = new System.Drawing.Size(0, 300);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.panel1);
            this.Name = "CyCustomCommandsTab";
            this.Size = new System.Drawing.Size(859, 549);
            this.VisibleChanged += new System.EventHandler(this.CyCustomCommandsTab_VisibleChanged);
            this.gbRequiredCommands.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRequiredCmds)).EndInit();
            this.gbCustomCommands.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvCustomCmds)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataTable1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbRequiredCommands;
        private System.Windows.Forms.GroupBox gbCustomCommands;
        private System.Windows.Forms.DataGridView dgvCustomCmds;
        private System.Windows.Forms.BindingSource bindingSource1;
        private System.Data.DataSet dataSet1;
        private System.Data.DataTable dataTable1;
        private System.Windows.Forms.DataGridView dgvRequiredCmds;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.CheckBox chbCommandPattern;
        private System.Windows.Forms.DataGridViewCheckBoxColumn colCustEnable;
        private System.Windows.Forms.DataGridViewComboBoxColumn colCustCmdSize;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCustDataSize;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCustCmdByte1;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCustCmdByte2;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCustCmdByte3;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCustCmdByte4;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCustApiName;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.DataGridViewComboBoxColumn colReqCmdSize;
        private System.Windows.Forms.DataGridViewTextBoxColumn colReqDataSize;
        private System.Windows.Forms.DataGridViewTextBoxColumn colReqCmdByte1;
        private System.Windows.Forms.DataGridViewTextBoxColumn colReqCmdByte2;
        private System.Windows.Forms.DataGridViewTextBoxColumn colReqCmdByte3;
        private System.Windows.Forms.DataGridViewTextBoxColumn colReqCmdByte4;
        private System.Windows.Forms.DataGridViewTextBoxColumn colReqCmdDesc;
    }
}
