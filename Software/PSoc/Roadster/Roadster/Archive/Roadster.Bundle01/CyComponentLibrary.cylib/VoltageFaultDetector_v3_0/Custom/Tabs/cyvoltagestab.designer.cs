namespace VoltageFaultDetector_v3_0
{
    partial class CyVoltagesTab
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle7 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dgvVoltages = new System.Windows.Forms.DataGridView();
            this.cyToolStrip1 = new VoltageFaultDetector_v3_0.CyToolStrip();
            this.colInputScalingFactor = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colOVFaultActualThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colOVFaultThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colUVFaultActualThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colUVFaultThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colNominalVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colVoltageName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colVoltageInput = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dgvVoltages)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvVoltages
            // 
            this.dgvVoltages.AllowUserToAddRows = false;
            this.dgvVoltages.AllowUserToDeleteRows = false;
            this.dgvVoltages.AllowUserToResizeColumns = false;
            this.dgvVoltages.AllowUserToResizeRows = false;
            this.dgvVoltages.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvVoltages.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvVoltages.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colVoltageInput,
            this.colVoltageName,
            this.colNominalVoltage,
            this.colUVFaultThreshold,
            this.colUVFaultActualThreshold,
            this.colOVFaultThreshold,
            this.colOVFaultActualThreshold,
            this.colInputScalingFactor});
            this.dgvVoltages.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvVoltages.Location = new System.Drawing.Point(0, 31);
            this.dgvVoltages.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dgvVoltages.Name = "dgvVoltages";
            this.dgvVoltages.RowHeadersWidth = 20;
            this.dgvVoltages.Size = new System.Drawing.Size(1267, 400);
            this.dgvVoltages.TabIndex = 0;
            this.dgvVoltages.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dgvVoltages_CellFormatting);
            this.dgvVoltages.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvVoltages_CellValueChanged);
            this.dgvVoltages.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgvVoltages_CurrentCellDirtyStateChanged);
            this.dgvVoltages.SelectionChanged += new System.EventHandler(this.dgvVoltages_SelectionChanged);
            // 
            // cyToolStrip1
            // 
            this.cyToolStrip1.Dock = System.Windows.Forms.DockStyle.Top;
            this.cyToolStrip1.Location = new System.Drawing.Point(0, 0);
            this.cyToolStrip1.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.cyToolStrip1.Name = "cyToolStrip1";
            this.cyToolStrip1.Size = new System.Drawing.Size(1267, 31);
            this.cyToolStrip1.TabIndex = 1;
            // 
            // colInputScalingFactor
            // 
            dataGridViewCellStyle7.Format = "N3";
            dataGridViewCellStyle7.NullValue = null;
            this.colInputScalingFactor.DefaultCellStyle = dataGridViewCellStyle7;
            this.colInputScalingFactor.FillWeight = 30F;
            this.colInputScalingFactor.HeaderText = "Input scaling factor";
            this.colInputScalingFactor.MinimumWidth = 52;
            this.colInputScalingFactor.Name = "colInputScalingFactor";
            // 
            // colOVFaultActualThreshold
            // 
            dataGridViewCellStyle6.BackColor = System.Drawing.SystemColors.ControlLight;
            dataGridViewCellStyle6.Format = "N3";
            dataGridViewCellStyle6.NullValue = null;
            this.colOVFaultActualThreshold.DefaultCellStyle = dataGridViewCellStyle6;
            this.colOVFaultActualThreshold.FillWeight = 35F;
            this.colOVFaultActualThreshold.HeaderText = "OV fault actual threshold (V)";
            this.colOVFaultActualThreshold.MinimumWidth = 68;
            this.colOVFaultActualThreshold.Name = "colOVFaultActualThreshold";
            this.colOVFaultActualThreshold.ReadOnly = true;
            // 
            // colOVFaultThreshold
            // 
            dataGridViewCellStyle5.Format = "N3";
            dataGridViewCellStyle5.NullValue = null;
            this.colOVFaultThreshold.DefaultCellStyle = dataGridViewCellStyle5;
            this.colOVFaultThreshold.FillWeight = 35F;
            this.colOVFaultThreshold.HeaderText = "OV fault desired threshold (V)";
            this.colOVFaultThreshold.MinimumWidth = 68;
            this.colOVFaultThreshold.Name = "colOVFaultThreshold";
            // 
            // colUVFaultActualThreshold
            // 
            dataGridViewCellStyle4.BackColor = System.Drawing.SystemColors.ControlLight;
            dataGridViewCellStyle4.Format = "N3";
            dataGridViewCellStyle4.NullValue = null;
            this.colUVFaultActualThreshold.DefaultCellStyle = dataGridViewCellStyle4;
            this.colUVFaultActualThreshold.FillWeight = 35F;
            this.colUVFaultActualThreshold.HeaderText = "UV fault actual threshold (V)";
            this.colUVFaultActualThreshold.MinimumWidth = 68;
            this.colUVFaultActualThreshold.Name = "colUVFaultActualThreshold";
            this.colUVFaultActualThreshold.ReadOnly = true;
            // 
            // colUVFaultThreshold
            // 
            dataGridViewCellStyle3.Format = "N3";
            dataGridViewCellStyle3.NullValue = null;
            this.colUVFaultThreshold.DefaultCellStyle = dataGridViewCellStyle3;
            this.colUVFaultThreshold.FillWeight = 35F;
            this.colUVFaultThreshold.HeaderText = "UV fault desired threshold (V)";
            this.colUVFaultThreshold.MinimumWidth = 68;
            this.colUVFaultThreshold.Name = "colUVFaultThreshold";
            // 
            // colNominalVoltage
            // 
            dataGridViewCellStyle2.Format = "N3";
            dataGridViewCellStyle2.NullValue = null;
            this.colNominalVoltage.DefaultCellStyle = dataGridViewCellStyle2;
            this.colNominalVoltage.FillWeight = 35F;
            this.colNominalVoltage.HeaderText = "Nominal voltage (V)";
            this.colNominalVoltage.MinimumWidth = 58;
            this.colNominalVoltage.Name = "colNominalVoltage";
            // 
            // colVoltageName
            // 
            this.colVoltageName.FillWeight = 30F;
            this.colVoltageName.HeaderText = "Voltage name";
            this.colVoltageName.MaxInputLength = 16;
            this.colVoltageName.MinimumWidth = 58;
            this.colVoltageName.Name = "colVoltageName";
            // 
            // colVoltageInput
            // 
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.colVoltageInput.DefaultCellStyle = dataGridViewCellStyle1;
            this.colVoltageInput.FillWeight = 20F;
            this.colVoltageInput.HeaderText = "Voltage number";
            this.colVoltageInput.MinimumWidth = 58;
            this.colVoltageInput.Name = "colVoltageInput";
            this.colVoltageInput.ReadOnly = true;
            // 
            // CyVoltagesTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.dgvVoltages);
            this.Controls.Add(this.cyToolStrip1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "CyVoltagesTab";
            this.Size = new System.Drawing.Size(1267, 431);
            ((System.ComponentModel.ISupportInitialize)(this.dgvVoltages)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvVoltages;
        private CyToolStrip cyToolStrip1;
        private System.Windows.Forms.DataGridViewTextBoxColumn colVoltageInput;
        private System.Windows.Forms.DataGridViewTextBoxColumn colVoltageName;
        private System.Windows.Forms.DataGridViewTextBoxColumn colNominalVoltage;
        private System.Windows.Forms.DataGridViewTextBoxColumn colUVFaultThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colUVFaultActualThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colOVFaultThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colOVFaultActualThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colInputScalingFactor;
    }
}
