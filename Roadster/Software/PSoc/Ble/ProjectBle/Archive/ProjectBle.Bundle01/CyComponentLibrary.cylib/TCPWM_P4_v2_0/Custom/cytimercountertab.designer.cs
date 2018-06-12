namespace TCPWM_P4_v2_0
{
    partial class CyTimerCounterTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyTimerCounterTab));
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.m_label0 = new System.Windows.Forms.Label();
            this.m_cbPrescaler = new System.Windows.Forms.ComboBox();
            this.m_label1 = new System.Windows.Forms.Label();
            this.m_cbCounterMode = new System.Windows.Forms.ComboBox();
            this.m_label2 = new System.Windows.Forms.Label();
            this.m_cbCompareCapture = new System.Windows.Forms.ComboBox();
            this.m_label6 = new System.Windows.Forms.Label();
            this.m_cbRunMode = new System.Windows.Forms.ComboBox();
            this.m_pbCounterGraph = new System.Windows.Forms.PictureBox();
            this.m_panel1 = new System.Windows.Forms.Panel();
            this.registerGrid = new TCPWM_P4_v2_0.CyRegisterGrid();
            this.groupBoxInterrupt = new System.Windows.Forms.GroupBox();
            this.m_cbInterruptOnTC = new System.Windows.Forms.CheckBox();
            this.m_cbInterruptOnCC = new System.Windows.Forms.CheckBox();
            this.dgvAdvanced = new System.Windows.Forms.DataGridView();
            this.ColumnLabel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnPresent = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ColumnMode = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.m_pbCounterGraph)).BeginInit();
            this.m_panel1.SuspendLayout();
            this.groupBoxInterrupt.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAdvanced)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
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
            // m_label1
            // 
            resources.ApplyResources(this.m_label1, "m_label1");
            this.m_label1.Name = "m_label1";
            // 
            // m_cbCounterMode
            // 
            this.m_cbCounterMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbCounterMode.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbCounterMode, "m_cbCounterMode");
            this.m_cbCounterMode.Name = "m_cbCounterMode";
            // 
            // m_label2
            // 
            resources.ApplyResources(this.m_label2, "m_label2");
            this.m_label2.Name = "m_label2";
            // 
            // m_cbCompareCapture
            // 
            this.m_cbCompareCapture.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbCompareCapture.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbCompareCapture, "m_cbCompareCapture");
            this.m_cbCompareCapture.Name = "m_cbCompareCapture";
            // 
            // m_label6
            // 
            resources.ApplyResources(this.m_label6, "m_label6");
            this.m_label6.Name = "m_label6";
            // 
            // m_cbRunMode
            // 
            this.m_cbRunMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRunMode.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbRunMode, "m_cbRunMode");
            this.m_cbRunMode.Name = "m_cbRunMode";
            // 
            // m_pbCounterGraph
            // 
            this.m_pbCounterGraph.BackColor = System.Drawing.Color.White;
            resources.ApplyResources(this.m_pbCounterGraph, "m_pbCounterGraph");
            this.m_pbCounterGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_pbCounterGraph.Name = "m_pbCounterGraph";
            this.m_pbCounterGraph.TabStop = false;
            // 
            // m_panel1
            // 
            this.m_panel1.Controls.Add(this.registerGrid);
            this.m_panel1.Controls.Add(this.groupBoxInterrupt);
            this.m_panel1.Controls.Add(this.dgvAdvanced);
            this.m_panel1.Controls.Add(this.m_label0);
            this.m_panel1.Controls.Add(this.m_label1);
            this.m_panel1.Controls.Add(this.m_cbPrescaler);
            this.m_panel1.Controls.Add(this.m_label2);
            this.m_panel1.Controls.Add(this.m_label6);
            this.m_panel1.Controls.Add(this.m_cbRunMode);
            this.m_panel1.Controls.Add(this.m_cbCompareCapture);
            this.m_panel1.Controls.Add(this.m_cbCounterMode);
            resources.ApplyResources(this.m_panel1, "m_panel1");
            this.m_panel1.Name = "m_panel1";
            // 
            // registerGrid
            // 
            resources.ApplyResources(this.registerGrid, "registerGrid");
            this.registerGrid.Name = "registerGrid";
            this.registerGrid.DataChanged += new System.EventHandler(this.registerGrid_DataChanged);
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
            // dgvAdvanced
            // 
            this.dgvAdvanced.AllowUserToAddRows = false;
            this.dgvAdvanced.AllowUserToDeleteRows = false;
            this.dgvAdvanced.AllowUserToOrderColumns = true;
            this.dgvAdvanced.AllowUserToResizeColumns = false;
            this.dgvAdvanced.AllowUserToResizeRows = false;
            this.dgvAdvanced.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvAdvanced.BackgroundColor = System.Drawing.SystemColors.Control;
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
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // CyTimerCounterTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_pbCounterGraph);
            this.Controls.Add(this.m_panel1);
            this.Name = "CyTimerCounterTab";
            ((System.ComponentModel.ISupportInitialize)(this.m_pbCounterGraph)).EndInit();
            this.m_panel1.ResumeLayout(false);
            this.m_panel1.PerformLayout();
            this.groupBoxInterrupt.ResumeLayout(false);
            this.groupBoxInterrupt.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAdvanced)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label m_label0;
        private System.Windows.Forms.ComboBox m_cbPrescaler;
        private System.Windows.Forms.Label m_label1;
        private System.Windows.Forms.ComboBox m_cbCounterMode;
        private System.Windows.Forms.Label m_label2;
        private System.Windows.Forms.ComboBox m_cbCompareCapture;
        private System.Windows.Forms.Label m_label6;
        private System.Windows.Forms.ComboBox m_cbRunMode;
        private System.Windows.Forms.PictureBox m_pbCounterGraph;
        private System.Windows.Forms.Panel m_panel1;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.DataGridView dgvAdvanced;
        private System.Windows.Forms.GroupBox groupBoxInterrupt;
        private System.Windows.Forms.CheckBox m_cbInterruptOnTC;
        private System.Windows.Forms.CheckBox m_cbInterruptOnCC;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnLabel;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColumnPresent;
        private System.Windows.Forms.DataGridViewComboBoxColumn ColumnMode;
        private CyRegisterGrid registerGrid;
    }
}
