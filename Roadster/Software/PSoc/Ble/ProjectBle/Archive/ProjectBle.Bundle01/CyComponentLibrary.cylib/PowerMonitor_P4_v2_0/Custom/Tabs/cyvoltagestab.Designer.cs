namespace PowerMonitor_P4_v2_0
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.cyToolStrip1 = new PowerMonitor_P4_v2_0.CyToolStrip();
            this.colPowerConverterNumber = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colConverterName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colNominalOutputVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colAcqTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colUVFaultThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colUVWarningThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colOVWarningThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colOVFaultThreshold = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colInputScalingFactor = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colPowerConverterNumber,
            this.colConverterName,
            this.colNominalOutputVoltage,
            this.colAcqTime,
            this.colUVFaultThreshold,
            this.colUVWarningThreshold,
            this.colOVWarningThreshold,
            this.colOVFaultThreshold,
            this.colInputScalingFactor});
            this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView1.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.dataGridView1.Location = new System.Drawing.Point(0, 31);
            this.dataGridView1.Margin = new System.Windows.Forms.Padding(4);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(792, 387);
            this.dataGridView1.TabIndex = 0;
            this.dataGridView1.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            this.dataGridView1.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellValueChanged);
            this.dataGridView1.CurrentCellDirtyStateChanged += new System.EventHandler(this.dataGridView1_CurrentCellDirtyStateChanged_1);
            this.dataGridView1.SelectionChanged += new System.EventHandler(this.dataGridView1_SelectionChanged);
            // 
            // cyToolStrip1
            // 
            this.cyToolStrip1.Dock = System.Windows.Forms.DockStyle.Top;
            this.cyToolStrip1.Location = new System.Drawing.Point(0, 0);
            this.cyToolStrip1.Margin = new System.Windows.Forms.Padding(5);
            this.cyToolStrip1.Name = "cyToolStrip1";
            this.cyToolStrip1.Size = new System.Drawing.Size(792, 31);
            this.cyToolStrip1.TabIndex = 1;
            // 
            // colPowerConverterNumber
            // 
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.colPowerConverterNumber.DefaultCellStyle = dataGridViewCellStyle1;
            this.colPowerConverterNumber.FillWeight = 137.0558F;
            this.colPowerConverterNumber.HeaderText = "Converter";
            this.colPowerConverterNumber.Name = "colPowerConverterNumber";
            this.colPowerConverterNumber.ReadOnly = true;
            // 
            // colConverterName
            // 
            this.colConverterName.FillWeight = 91.21213F;
            this.colConverterName.HeaderText = "Name";
            this.colConverterName.MaxInputLength = 16;
            this.colConverterName.Name = "colConverterName";
            // 
            // colNominalOutputVoltage
            // 
            this.colNominalOutputVoltage.FillWeight = 91.21213F;
            this.colNominalOutputVoltage.HeaderText = "Nominal voltage (V)";
            this.colNominalOutputVoltage.Name = "colNominalOutputVoltage";
            // 
            // colAcqTime
            // 
            this.colAcqTime.FillWeight = 124.4593F;
            this.colAcqTime.HeaderText = "Min acquisition time (ns)";
            this.colAcqTime.Name = "colAcqTime";
            this.colAcqTime.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // colUVFaultThreshold
            // 
            this.colUVFaultThreshold.FillWeight = 91.21213F;
            this.colUVFaultThreshold.HeaderText = "UV fault threshold (V)";
            this.colUVFaultThreshold.Name = "colUVFaultThreshold";
            // 
            // colUVWarningThreshold
            // 
            this.colUVWarningThreshold.FillWeight = 91.21213F;
            this.colUVWarningThreshold.HeaderText = "UV warning threshold (V)";
            this.colUVWarningThreshold.Name = "colUVWarningThreshold";
            // 
            // colOVWarningThreshold
            // 
            this.colOVWarningThreshold.FillWeight = 91.21213F;
            this.colOVWarningThreshold.HeaderText = "OV warning threshold (V)";
            this.colOVWarningThreshold.Name = "colOVWarningThreshold";
            // 
            // colOVFaultThreshold
            // 
            this.colOVFaultThreshold.FillWeight = 91.21213F;
            this.colOVFaultThreshold.HeaderText = "OV fault threshold (V)";
            this.colOVFaultThreshold.Name = "colOVFaultThreshold";
            // 
            // colInputScalingFactor
            // 
            this.colInputScalingFactor.FillWeight = 91.21213F;
            this.colInputScalingFactor.HeaderText = "Input scaling factor";
            this.colInputScalingFactor.Name = "colInputScalingFactor";
            // 
            // CyVoltagesTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.cyToolStrip1);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyVoltagesTab";
            this.Size = new System.Drawing.Size(792, 418);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private CyToolStrip cyToolStrip1;
        private System.Windows.Forms.DataGridViewTextBoxColumn colPowerConverterNumber;
        private System.Windows.Forms.DataGridViewTextBoxColumn colConverterName;
        private System.Windows.Forms.DataGridViewTextBoxColumn colNominalOutputVoltage;
        private System.Windows.Forms.DataGridViewTextBoxColumn colAcqTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn colUVFaultThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colUVWarningThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colOVWarningThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colOVFaultThreshold;
        private System.Windows.Forms.DataGridViewTextBoxColumn colInputScalingFactor;
    }
}
