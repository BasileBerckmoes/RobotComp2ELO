namespace MDIO_Interface_v1_20.Tabs
{
    partial class CyAdvancedTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyAdvancedTab));
            this.dgvRegisters = new System.Windows.Forms.DataGridView();
            this.addressDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.initValueDisplayDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.maskDisplayDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.clearOnReadDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.writeOnlyDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.triggerOnWriteDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.triggerOnReadDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.auxBitsDataGridViewColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.cyRegAddressBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listBoxRegSpaces = new MDIO_Interface_v1_20.Tabs.CyRefreshingListBox();
            this.panelBottom = new System.Windows.Forms.Panel();
            this.chbEnableAuxBits = new System.Windows.Forms.CheckBox();
            this.toolStripRegSpace = new System.Windows.Forms.ToolStrip();
            this.toolStripButtonAdd = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonRemove = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonImport = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonExport = new System.Windows.Forms.ToolStripButton();
            this.gbRegisters = new System.Windows.Forms.GroupBox();
            this.gbRegSpaceSettings = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lblRegisterName = new System.Windows.Forms.Label();
            this.lblMemoryType = new System.Windows.Forms.Label();
            this.tbName = new System.Windows.Forms.TextBox();
            this.cbMemoryType = new System.Windows.Forms.ComboBox();
            this.tbStartAddress = new System.Windows.Forms.TextBox();
            this.lblConfigType = new System.Windows.Forms.Label();
            this.lblStartAddress = new System.Windows.Forms.Label();
            this.cbConfigType = new System.Windows.Forms.ComboBox();
            this.tbEndAddress = new System.Windows.Forms.TextBox();
            this.lblDataWidth = new System.Windows.Forms.Label();
            this.lblEndAddress = new System.Windows.Forms.Label();
            this.cbDataWidth = new System.Windows.Forms.ComboBox();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cyRegAddressBindingSource)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panelBottom.SuspendLayout();
            this.toolStripRegSpace.SuspendLayout();
            this.gbRegisters.SuspendLayout();
            this.gbRegSpaceSettings.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvRegisters
            // 
            this.dgvRegisters.AllowUserToAddRows = false;
            this.dgvRegisters.AllowUserToDeleteRows = false;
            this.dgvRegisters.AllowUserToResizeColumns = false;
            this.dgvRegisters.AllowUserToResizeRows = false;
            this.dgvRegisters.AutoGenerateColumns = false;
            this.dgvRegisters.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvRegisters.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvRegisters.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.addressDataGridViewTextBoxColumn,
            this.initValueDisplayDataGridViewTextBoxColumn,
            this.maskDisplayDataGridViewTextBoxColumn,
            this.clearOnReadDataGridViewCheckBoxColumn,
            this.writeOnlyDataGridViewCheckBoxColumn,
            this.triggerOnWriteDataGridViewCheckBoxColumn,
            this.triggerOnReadDataGridViewCheckBoxColumn,
            this.auxBitsDataGridViewColumn});
            this.dgvRegisters.DataSource = this.cyRegAddressBindingSource;
            resources.ApplyResources(this.dgvRegisters, "dgvRegisters");
            this.dgvRegisters.Name = "dgvRegisters";
            this.dgvRegisters.RowHeadersVisible = false;
            this.dgvRegisters.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dgvRegisters_CellFormatting);
            this.dgvRegisters.CellPainting += new System.Windows.Forms.DataGridViewCellPaintingEventHandler(this.dgvRegisters_CellPainting);
            this.dgvRegisters.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvRegisters_CellValueChanged);
            this.dgvRegisters.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgvRegisters_CurrentCellDirtyStateChanged);
            // 
            // addressDataGridViewTextBoxColumn
            // 
            this.addressDataGridViewTextBoxColumn.DataPropertyName = "Address";
            resources.ApplyResources(this.addressDataGridViewTextBoxColumn, "addressDataGridViewTextBoxColumn");
            this.addressDataGridViewTextBoxColumn.Name = "addressDataGridViewTextBoxColumn";
            // 
            // initValueDisplayDataGridViewTextBoxColumn
            // 
            this.initValueDisplayDataGridViewTextBoxColumn.DataPropertyName = "InitValueDisplay";
            resources.ApplyResources(this.initValueDisplayDataGridViewTextBoxColumn, "initValueDisplayDataGridViewTextBoxColumn");
            this.initValueDisplayDataGridViewTextBoxColumn.Name = "initValueDisplayDataGridViewTextBoxColumn";
            // 
            // maskDisplayDataGridViewTextBoxColumn
            // 
            this.maskDisplayDataGridViewTextBoxColumn.DataPropertyName = "MaskDisplay";
            resources.ApplyResources(this.maskDisplayDataGridViewTextBoxColumn, "maskDisplayDataGridViewTextBoxColumn");
            this.maskDisplayDataGridViewTextBoxColumn.Name = "maskDisplayDataGridViewTextBoxColumn";
            // 
            // clearOnReadDataGridViewCheckBoxColumn
            // 
            this.clearOnReadDataGridViewCheckBoxColumn.DataPropertyName = "ClearOnRead";
            resources.ApplyResources(this.clearOnReadDataGridViewCheckBoxColumn, "clearOnReadDataGridViewCheckBoxColumn");
            this.clearOnReadDataGridViewCheckBoxColumn.Name = "clearOnReadDataGridViewCheckBoxColumn";
            // 
            // writeOnlyDataGridViewCheckBoxColumn
            // 
            this.writeOnlyDataGridViewCheckBoxColumn.DataPropertyName = "WriteOnly";
            resources.ApplyResources(this.writeOnlyDataGridViewCheckBoxColumn, "writeOnlyDataGridViewCheckBoxColumn");
            this.writeOnlyDataGridViewCheckBoxColumn.Name = "writeOnlyDataGridViewCheckBoxColumn";
            // 
            // triggerOnWriteDataGridViewCheckBoxColumn
            // 
            this.triggerOnWriteDataGridViewCheckBoxColumn.DataPropertyName = "TriggerOnWrite";
            resources.ApplyResources(this.triggerOnWriteDataGridViewCheckBoxColumn, "triggerOnWriteDataGridViewCheckBoxColumn");
            this.triggerOnWriteDataGridViewCheckBoxColumn.Name = "triggerOnWriteDataGridViewCheckBoxColumn";
            // 
            // triggerOnReadDataGridViewCheckBoxColumn
            // 
            this.triggerOnReadDataGridViewCheckBoxColumn.DataPropertyName = "TriggerOnRead";
            resources.ApplyResources(this.triggerOnReadDataGridViewCheckBoxColumn, "triggerOnReadDataGridViewCheckBoxColumn");
            this.triggerOnReadDataGridViewCheckBoxColumn.Name = "triggerOnReadDataGridViewCheckBoxColumn";
            // 
            // auxBitsDataGridViewColumn
            // 
            this.auxBitsDataGridViewColumn.DataPropertyName = "AuxBitsDisplay";
            resources.ApplyResources(this.auxBitsDataGridViewColumn, "auxBitsDataGridViewColumn");
            this.auxBitsDataGridViewColumn.MaxInputLength = 4;
            this.auxBitsDataGridViewColumn.Name = "auxBitsDataGridViewColumn";
            // 
            // cyRegAddressBindingSource
            // 
            this.cyRegAddressBindingSource.DataSource = typeof(MDIO_Interface_v1_20.CyRegAddress);
            // 
            // splitContainer1
            // 
            resources.ApplyResources(this.splitContainer1, "splitContainer1");
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.listBoxRegSpaces);
            this.splitContainer1.Panel1.Controls.Add(this.panelBottom);
            this.splitContainer1.Panel1.Controls.Add(this.toolStripRegSpace);
            // 
            // splitContainer1.Panel2
            // 
            resources.ApplyResources(this.splitContainer1.Panel2, "splitContainer1.Panel2");
            this.splitContainer1.Panel2.Controls.Add(this.gbRegisters);
            this.splitContainer1.Panel2.Controls.Add(this.gbRegSpaceSettings);
            // 
            // listBoxRegSpaces
            // 
            resources.ApplyResources(this.listBoxRegSpaces, "listBoxRegSpaces");
            this.listBoxRegSpaces.FormattingEnabled = true;
            this.listBoxRegSpaces.Name = "listBoxRegSpaces";
            this.listBoxRegSpaces.SelectedIndexChanged += new System.EventHandler(this.listBoxRegSpaces_SelectedIndexChanged);
            this.listBoxRegSpaces.Format += new System.Windows.Forms.ListControlConvertEventHandler(this.listBoxRegSpaces_Format);
            // 
            // panelBottom
            // 
            this.panelBottom.Controls.Add(this.chbEnableAuxBits);
            resources.ApplyResources(this.panelBottom, "panelBottom");
            this.panelBottom.Name = "panelBottom";
            // 
            // chbEnableAuxBits
            // 
            resources.ApplyResources(this.chbEnableAuxBits, "chbEnableAuxBits");
            this.chbEnableAuxBits.Name = "chbEnableAuxBits";
            this.chbEnableAuxBits.UseVisualStyleBackColor = true;
            this.chbEnableAuxBits.CheckedChanged += new System.EventHandler(this.chbEnableAuxBits_CheckedChanged);
            // 
            // toolStripRegSpace
            // 
            this.toolStripRegSpace.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStripRegSpace.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonAdd,
            this.toolStripButtonRemove,
            this.toolStripSeparator1,
            this.toolStripButtonImport,
            this.toolStripButtonExport});
            resources.ApplyResources(this.toolStripRegSpace, "toolStripRegSpace");
            this.toolStripRegSpace.Name = "toolStripRegSpace";
            // 
            // toolStripButtonAdd
            // 
            this.toolStripButtonAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonAdd.Image = global::MDIO_Interface_v1_20.Resources.Add;
            resources.ApplyResources(this.toolStripButtonAdd, "toolStripButtonAdd");
            this.toolStripButtonAdd.Name = "toolStripButtonAdd";
            this.toolStripButtonAdd.Click += new System.EventHandler(this.toolStripButtonAdd_Click);
            // 
            // toolStripButtonRemove
            // 
            this.toolStripButtonRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonRemove.Image = global::MDIO_Interface_v1_20.Resources.DeleteHS;
            resources.ApplyResources(this.toolStripButtonRemove, "toolStripButtonRemove");
            this.toolStripButtonRemove.Name = "toolStripButtonRemove";
            this.toolStripButtonRemove.Click += new System.EventHandler(this.toolStripButtonRemove_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            resources.ApplyResources(this.toolStripSeparator1, "toolStripSeparator1");
            // 
            // toolStripButtonImport
            // 
            this.toolStripButtonImport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonImport.Image = global::MDIO_Interface_v1_20.Resources.Import;
            resources.ApplyResources(this.toolStripButtonImport, "toolStripButtonImport");
            this.toolStripButtonImport.Name = "toolStripButtonImport";
            this.toolStripButtonImport.Click += new System.EventHandler(this.toolStripButtonImport_Click);
            // 
            // toolStripButtonExport
            // 
            this.toolStripButtonExport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonExport.Image = global::MDIO_Interface_v1_20.Resources.Export;
            resources.ApplyResources(this.toolStripButtonExport, "toolStripButtonExport");
            this.toolStripButtonExport.Name = "toolStripButtonExport";
            this.toolStripButtonExport.Click += new System.EventHandler(this.toolStripButtonExport_Click);
            // 
            // gbRegisters
            // 
            this.gbRegisters.Controls.Add(this.dgvRegisters);
            resources.ApplyResources(this.gbRegisters, "gbRegisters");
            this.gbRegisters.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbRegisters.Name = "gbRegisters";
            this.gbRegisters.TabStop = false;
            // 
            // gbRegSpaceSettings
            // 
            this.gbRegSpaceSettings.Controls.Add(this.panel1);
            resources.ApplyResources(this.gbRegSpaceSettings, "gbRegSpaceSettings");
            this.gbRegSpaceSettings.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbRegSpaceSettings.Name = "gbRegSpaceSettings";
            this.gbRegSpaceSettings.TabStop = false;
            // 
            // panel1
            // 
            resources.ApplyResources(this.panel1, "panel1");
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.lblRegisterName);
            this.panel1.Controls.Add(this.lblMemoryType);
            this.panel1.Controls.Add(this.tbName);
            this.panel1.Controls.Add(this.cbMemoryType);
            this.panel1.Controls.Add(this.tbStartAddress);
            this.panel1.Controls.Add(this.lblConfigType);
            this.panel1.Controls.Add(this.lblStartAddress);
            this.panel1.Controls.Add(this.cbConfigType);
            this.panel1.Controls.Add(this.tbEndAddress);
            this.panel1.Controls.Add(this.lblDataWidth);
            this.panel1.Controls.Add(this.lblEndAddress);
            this.panel1.Controls.Add(this.cbDataWidth);
            this.panel1.Name = "panel1";
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // lblRegisterName
            // 
            resources.ApplyResources(this.lblRegisterName, "lblRegisterName");
            this.lblRegisterName.Name = "lblRegisterName";
            // 
            // lblMemoryType
            // 
            resources.ApplyResources(this.lblMemoryType, "lblMemoryType");
            this.lblMemoryType.Name = "lblMemoryType";
            // 
            // tbName
            // 
            resources.ApplyResources(this.tbName, "tbName");
            this.tbName.Name = "tbName";
            this.tbName.TextChanged += new System.EventHandler(this.tbName_TextChanged);
            this.tbName.Validated += new System.EventHandler(this.tbName_Validated);
            // 
            // cbMemoryType
            // 
            this.cbMemoryType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbMemoryType.FormattingEnabled = true;
            resources.ApplyResources(this.cbMemoryType, "cbMemoryType");
            this.cbMemoryType.Name = "cbMemoryType";
            this.cbMemoryType.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            this.cbMemoryType.Format += new System.Windows.Forms.ListControlConvertEventHandler(this.cb_Format);
            // 
            // tbStartAddress
            // 
            resources.ApplyResources(this.tbStartAddress, "tbStartAddress");
            this.tbStartAddress.Name = "tbStartAddress";
            this.tbStartAddress.TextChanged += new System.EventHandler(this.tbStartEndAddress_TextChanged);
            this.tbStartAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbStartEndAddress_KeyPress);
            // 
            // lblConfigType
            // 
            resources.ApplyResources(this.lblConfigType, "lblConfigType");
            this.lblConfigType.Name = "lblConfigType";
            // 
            // lblStartAddress
            // 
            resources.ApplyResources(this.lblStartAddress, "lblStartAddress");
            this.lblStartAddress.Name = "lblStartAddress";
            // 
            // cbConfigType
            // 
            this.cbConfigType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbConfigType.FormattingEnabled = true;
            resources.ApplyResources(this.cbConfigType, "cbConfigType");
            this.cbConfigType.Name = "cbConfigType";
            this.cbConfigType.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            this.cbConfigType.Format += new System.Windows.Forms.ListControlConvertEventHandler(this.cb_Format);
            // 
            // tbEndAddress
            // 
            resources.ApplyResources(this.tbEndAddress, "tbEndAddress");
            this.tbEndAddress.Name = "tbEndAddress";
            this.tbEndAddress.TextChanged += new System.EventHandler(this.tbStartEndAddress_TextChanged);
            this.tbEndAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbStartEndAddress_KeyPress);
            // 
            // lblDataWidth
            // 
            resources.ApplyResources(this.lblDataWidth, "lblDataWidth");
            this.lblDataWidth.Name = "lblDataWidth";
            // 
            // lblEndAddress
            // 
            resources.ApplyResources(this.lblEndAddress, "lblEndAddress");
            this.lblEndAddress.Name = "lblEndAddress";
            // 
            // cbDataWidth
            // 
            this.cbDataWidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDataWidth.FormattingEnabled = true;
            resources.ApplyResources(this.cbDataWidth, "cbDataWidth");
            this.cbDataWidth.Name = "cbDataWidth";
            this.cbDataWidth.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            this.cbDataWidth.Format += new System.Windows.Forms.ListControlConvertEventHandler(this.cb_Format);
            // 
            // CyAdvancedTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Name = "CyAdvancedTab";
            this.Load += new System.EventHandler(this.CyAdvancedTab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cyRegAddressBindingSource)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.panelBottom.ResumeLayout(false);
            this.panelBottom.PerformLayout();
            this.toolStripRegSpace.ResumeLayout(false);
            this.toolStripRegSpace.PerformLayout();
            this.gbRegisters.ResumeLayout(false);
            this.gbRegSpaceSettings.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvRegisters;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ToolStrip toolStripRegSpace;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.GroupBox gbRegSpaceSettings;
        private System.Windows.Forms.Label lblRegisterName;
        private System.Windows.Forms.TextBox tbName;
        private System.Windows.Forms.Label lblStartAddress;
        private System.Windows.Forms.TextBox tbStartAddress;
        private System.Windows.Forms.Label lblEndAddress;
        private System.Windows.Forms.TextBox tbEndAddress;
        private System.Windows.Forms.Label lblDataWidth;
        private System.Windows.Forms.ComboBox cbDataWidth;
        private System.Windows.Forms.Label lblMemoryType;
        private System.Windows.Forms.ComboBox cbMemoryType;
        private System.Windows.Forms.Label lblConfigType;
        private System.Windows.Forms.ComboBox cbConfigType;
        private System.Windows.Forms.GroupBox gbRegisters;
        private System.Windows.Forms.ToolStripButton toolStripButtonAdd;
        private System.Windows.Forms.ToolStripButton toolStripButtonRemove;
        private System.Windows.Forms.ToolStripButton toolStripButtonImport;
        private System.Windows.Forms.ToolStripButton toolStripButtonExport;
        private CyRefreshingListBox listBoxRegSpaces;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chbEnableAuxBits;
        private System.Windows.Forms.BindingSource cyRegAddressBindingSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn addressDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn initValueDisplayDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn maskDisplayDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn clearOnReadDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn writeOnlyDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn triggerOnWriteDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn triggerOnReadDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn auxBitsDataGridViewColumn;
        private System.Windows.Forms.Panel panelBottom;
    }
}
