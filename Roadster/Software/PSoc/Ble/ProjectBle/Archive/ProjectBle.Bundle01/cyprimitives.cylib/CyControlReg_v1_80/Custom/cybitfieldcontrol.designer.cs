namespace CyCustomizer.CyControlReg_v1_80
{
    partial class CyBitfieldControl
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
            this.bSetAll = new System.Windows.Forms.Button();
            this.nInputs = new System.Windows.Forms.NumericUpDown();
            this.lInputs = new System.Windows.Forms.Label();
            this.chReset = new System.Windows.Forms.CheckBox();
            this.chBus = new System.Windows.Forms.CheckBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.m_dgvBitFieldConfig = new System.Windows.Forms.DataGridView();
            this.cbSetAll = new System.Windows.Forms.ComboBox();
            this.Bit = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Mode = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.InitialValue = new System.Windows.Forms.DataGridViewComboBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.nInputs)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvBitFieldConfig)).BeginInit();
            this.SuspendLayout();
            // 
            // bSetAll
            // 
            this.bSetAll.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bSetAll.Location = new System.Drawing.Point(80, 202);
            this.bSetAll.Name = "bSetAll";
            this.bSetAll.Size = new System.Drawing.Size(80, 23);
            this.bSetAll.TabIndex = 7;
            this.bSetAll.Text = "Set all modes";
            this.bSetAll.UseVisualStyleBackColor = true;
            this.bSetAll.Click += new System.EventHandler(this.bSetAll_Click);
            // 
            // nInputs
            // 
            this.nInputs.BackColor = System.Drawing.Color.White;
            this.nInputs.Location = new System.Drawing.Point(51, 6);
            this.nInputs.Margin = new System.Windows.Forms.Padding(2);
            this.nInputs.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.nInputs.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nInputs.Name = "nInputs";
            this.nInputs.Size = new System.Drawing.Size(34, 20);
            this.nInputs.TabIndex = 1;
            this.nInputs.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nInputs.ValueChanged += new System.EventHandler(this.nInputs_ValueChanged);
            this.nInputs.KeyUp += new System.Windows.Forms.KeyEventHandler(this.nInputs_KeyUp);
            // 
            // lInputs
            // 
            this.lInputs.Location = new System.Drawing.Point(3, 8);
            this.lInputs.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lInputs.Name = "lInputs";
            this.lInputs.Size = new System.Drawing.Size(44, 16);
            this.lInputs.TabIndex = 4;
            this.lInputs.Text = "Outputs:";
            // 
            // chReset
            // 
            this.chReset.AutoSize = true;
            this.chReset.Location = new System.Drawing.Point(51, 61);
            this.chReset.Name = "chReset";
            this.chReset.Size = new System.Drawing.Size(90, 17);
            this.chReset.TabIndex = 3;
            this.chReset.Text = "External reset";
            this.chReset.UseVisualStyleBackColor = true;
            this.chReset.Click += new System.EventHandler(this.chReset_CheckedChanged);
            this.chReset.Validating += new System.ComponentModel.CancelEventHandler(this.chReset_Validating);
            // 
            // chBus
            // 
            this.chBus.AutoSize = true;
            this.chBus.Location = new System.Drawing.Point(51, 38);
            this.chBus.Name = "chBus";
            this.chBus.Size = new System.Drawing.Size(94, 17);
            this.chBus.TabIndex = 2;
            this.chBus.Text = "Display as bus";
            this.chBus.UseVisualStyleBackColor = true;
            this.chBus.Click += new System.EventHandler(this.chBus_CheckedChanged);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.m_dgvBitFieldConfig, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.cbSetAll, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.bSetAll, 1, 1);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(167, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(219, 228);
            this.tableLayoutPanel1.TabIndex = 4;
            // 
            // m_dgvBitFieldConfig
            // 
            this.m_dgvBitFieldConfig.AllowUserToAddRows = false;
            this.m_dgvBitFieldConfig.AllowUserToDeleteRows = false;
            this.m_dgvBitFieldConfig.AllowUserToResizeColumns = false;
            this.m_dgvBitFieldConfig.AllowUserToResizeRows = false;
            this.m_dgvBitFieldConfig.BackgroundColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.m_dgvBitFieldConfig.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.m_dgvBitFieldConfig.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_dgvBitFieldConfig.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Bit,
            this.Mode,
            this.InitialValue});
            this.tableLayoutPanel1.SetColumnSpan(this.m_dgvBitFieldConfig, 2);
            this.m_dgvBitFieldConfig.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.m_dgvBitFieldConfig.Location = new System.Drawing.Point(0, 0);
            this.m_dgvBitFieldConfig.Margin = new System.Windows.Forms.Padding(0);
            this.m_dgvBitFieldConfig.MultiSelect = false;
            this.m_dgvBitFieldConfig.Name = "m_dgvBitFieldConfig";
            this.m_dgvBitFieldConfig.RowHeadersVisible = false;
            this.m_dgvBitFieldConfig.Size = new System.Drawing.Size(219, 199);
            this.m_dgvBitFieldConfig.TabIndex = 5;
            this.m_dgvBitFieldConfig.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.m_dgvBitFieldConfig_EditingControlShowing);
            this.m_dgvBitFieldConfig.Enter += new System.EventHandler(this.m_dgvBitFieldConfig_Enter);
            // 
            // cbSetAll
            // 
            this.cbSetAll.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cbSetAll.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbSetAll.FormatString = "Direct";
            this.cbSetAll.FormattingEnabled = true;
            this.cbSetAll.IntegralHeight = false;
            this.cbSetAll.Items.AddRange(new object[] {
            "Direct",
            "Sync",
            "Pulse"});
            this.cbSetAll.Location = new System.Drawing.Point(3, 204);
            this.cbSetAll.Name = "cbSetAll";
            this.cbSetAll.Size = new System.Drawing.Size(71, 21);
            this.cbSetAll.TabIndex = 6;
            // 
            // Bit
            // 
            this.Bit.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.LightGray;
            this.Bit.DefaultCellStyle = dataGridViewCellStyle2;
            this.Bit.FillWeight = 50F;
            this.Bit.HeaderText = "Bit";
            this.Bit.MinimumWidth = 20;
            this.Bit.Name = "Bit";
            this.Bit.ReadOnly = true;
            this.Bit.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Programmatic;
            // 
            // Mode
            // 
            this.Mode.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Mode.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.ComboBox;
            this.Mode.HeaderText = "Mode     ";
            this.Mode.Items.AddRange(new object[] {
            "Direct",
            "Sync",
            "Pulse"});
            this.Mode.Name = "Mode";
            this.Mode.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // InitialValue
            // 
            this.InitialValue.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.InitialValue.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.ComboBox;
            this.InitialValue.HeaderText = "Initial value";
            this.InitialValue.Items.AddRange(new object[] {
            "0",
            "1"});
            this.InitialValue.Name = "InitialValue";
            // 
            // CyBitfieldControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.chBus);
            this.Controls.Add(this.chReset);
            this.Controls.Add(this.lInputs);
            this.Controls.Add(this.nInputs);
            this.MinimumSize = new System.Drawing.Size(10, 10);
            this.Name = "CyBitfieldControl";
            this.Size = new System.Drawing.Size(411, 246);
            ((System.ComponentModel.ISupportInitialize)(this.nInputs)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvBitFieldConfig)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bSetAll;
        private System.Windows.Forms.NumericUpDown nInputs;
        private System.Windows.Forms.Label lInputs;
        private System.Windows.Forms.CheckBox chReset;
        private System.Windows.Forms.CheckBox chBus;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.ComboBox cbSetAll;
        private System.Windows.Forms.DataGridView m_dgvBitFieldConfig;
        private System.Windows.Forms.DataGridViewTextBoxColumn Bit;
        private System.Windows.Forms.DataGridViewComboBoxColumn Mode;
        private System.Windows.Forms.DataGridViewComboBoxColumn InitialValue;
    }
}
