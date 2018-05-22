namespace PowerMonitor_P4_v2_0
{
    partial class CyGeneralTab
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
            this.label1 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.numNumConverters = new System.Windows.Forms.NumericUpDown();
            this.cbPgoodConfig = new System.Windows.Forms.ComboBox();
            this.gbFaultSources = new System.Windows.Forms.GroupBox();
            this.chbFaultUv = new System.Windows.Forms.CheckBox();
            this.chbFaultOv = new System.Windows.Forms.CheckBox();
            this.gbWarningSources = new System.Windows.Forms.GroupBox();
            this.chbWarningUv = new System.Windows.Forms.CheckBox();
            this.chbWarningOv = new System.Windows.Forms.CheckBox();
            this.gbGeneral = new System.Windows.Forms.GroupBox();
            this.gbAdcSettings = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.m_lblRspTime = new System.Windows.Forms.Label();
            this.m_lblAdcRange = new System.Windows.Forms.Label();
            this.m_lblRefreshTime = new System.Windows.Forms.Label();
            this.m_chbExposeSoc = new System.Windows.Forms.CheckBox();
            this.m_lblSampleAve = new System.Windows.Forms.Label();
            this.m_nudVrefVolts = new System.Windows.Forms.NumericUpDown();
            this.m_chbEnableDma = new System.Windows.Forms.CheckBox();
            this.m_cbSamplesAve = new System.Windows.Forms.ComboBox();
            this.m_lblVrefSelect = new System.Windows.Forms.Label();
            this.m_cbVrefDisplay = new System.Windows.Forms.ComboBox();
            this.m_lblAdcRangeValue = new System.Windows.Forms.Label();
            this.m_lblExtVref = new System.Windows.Forms.Label();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbLoadConfig = new System.Windows.Forms.ToolStripButton();
            this.tsbSaveConfig = new System.Windows.Forms.ToolStripButton();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.numNumConverters)).BeginInit();
            this.gbFaultSources.SuspendLayout();
            this.gbWarningSources.SuspendLayout();
            this.gbGeneral.SuspendLayout();
            this.gbAdcSettings.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVrefVolts)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(112, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Number of converters:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 44);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(80, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "Pgood terminal:";
            // 
            // numNumConverters
            // 
            this.numNumConverters.Location = new System.Drawing.Point(162, 19);
            this.numNumConverters.Margin = new System.Windows.Forms.Padding(3, 3, 19, 3);
            this.numNumConverters.Name = "numNumConverters";
            this.numNumConverters.Size = new System.Drawing.Size(114, 20);
            this.numNumConverters.TabIndex = 1;
            // 
            // cbPgoodConfig
            // 
            this.cbPgoodConfig.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPgoodConfig.FormattingEnabled = true;
            this.cbPgoodConfig.Location = new System.Drawing.Point(162, 41);
            this.cbPgoodConfig.Name = "cbPgoodConfig";
            this.cbPgoodConfig.Size = new System.Drawing.Size(114, 21);
            this.cbPgoodConfig.TabIndex = 2;
            this.cbPgoodConfig.SelectedIndexChanged += new System.EventHandler(this.cbPgoodConfig_SelectedIndexChanged);
            // 
            // gbFaultSources
            // 
            this.gbFaultSources.AutoSize = true;
            this.gbFaultSources.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.gbFaultSources.Controls.Add(this.chbFaultUv);
            this.gbFaultSources.Controls.Add(this.chbFaultOv);
            this.gbFaultSources.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbFaultSources.Location = new System.Drawing.Point(3, 90);
            this.gbFaultSources.Name = "gbFaultSources";
            this.gbFaultSources.Size = new System.Drawing.Size(129, 107);
            this.gbFaultSources.TabIndex = 1;
            this.gbFaultSources.TabStop = false;
            this.gbFaultSources.Text = "Fault sources";
            // 
            // chbFaultUv
            // 
            this.chbFaultUv.AutoSize = true;
            this.chbFaultUv.Location = new System.Drawing.Point(6, 42);
            this.chbFaultUv.Name = "chbFaultUv";
            this.chbFaultUv.Size = new System.Drawing.Size(117, 17);
            this.chbFaultUv.TabIndex = 1;
            this.chbFaultUv.Text = "Under voltage (UV)";
            this.chbFaultUv.UseVisualStyleBackColor = true;
            this.chbFaultUv.CheckedChanged += new System.EventHandler(this.chbFaultUv_CheckedChanged);
            // 
            // chbFaultOv
            // 
            this.chbFaultOv.AutoSize = true;
            this.chbFaultOv.Location = new System.Drawing.Point(6, 19);
            this.chbFaultOv.Name = "chbFaultOv";
            this.chbFaultOv.Size = new System.Drawing.Size(111, 17);
            this.chbFaultOv.TabIndex = 0;
            this.chbFaultOv.Text = "Over voltage (OV)";
            this.chbFaultOv.UseVisualStyleBackColor = true;
            this.chbFaultOv.CheckedChanged += new System.EventHandler(this.chbFaultOv_CheckedChanged);
            // 
            // gbWarningSources
            // 
            this.gbWarningSources.AutoSize = true;
            this.gbWarningSources.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.gbWarningSources.Controls.Add(this.chbWarningUv);
            this.gbWarningSources.Controls.Add(this.chbWarningOv);
            this.gbWarningSources.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbWarningSources.Location = new System.Drawing.Point(138, 90);
            this.gbWarningSources.Name = "gbWarningSources";
            this.gbWarningSources.Size = new System.Drawing.Size(163, 107);
            this.gbWarningSources.TabIndex = 2;
            this.gbWarningSources.TabStop = false;
            this.gbWarningSources.Text = "Warning sources";
            // 
            // chbWarningUv
            // 
            this.chbWarningUv.AutoSize = true;
            this.chbWarningUv.Location = new System.Drawing.Point(6, 42);
            this.chbWarningUv.Name = "chbWarningUv";
            this.chbWarningUv.Size = new System.Drawing.Size(117, 17);
            this.chbWarningUv.TabIndex = 1;
            this.chbWarningUv.Text = "Under voltage (UV)";
            this.chbWarningUv.UseVisualStyleBackColor = true;
            this.chbWarningUv.CheckedChanged += new System.EventHandler(this.chbWarningUv_CheckedChanged);
            // 
            // chbWarningOv
            // 
            this.chbWarningOv.AutoSize = true;
            this.chbWarningOv.Location = new System.Drawing.Point(6, 19);
            this.chbWarningOv.Name = "chbWarningOv";
            this.chbWarningOv.Size = new System.Drawing.Size(111, 17);
            this.chbWarningOv.TabIndex = 0;
            this.chbWarningOv.Text = "Over voltage (OV)";
            this.chbWarningOv.UseVisualStyleBackColor = true;
            this.chbWarningOv.CheckedChanged += new System.EventHandler(this.chbWarningOv_CheckedChanged);
            // 
            // gbGeneral
            // 
            this.gbGeneral.AutoSize = true;
            this.gbGeneral.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.SetColumnSpan(this.gbGeneral, 2);
            this.gbGeneral.Controls.Add(this.label1);
            this.gbGeneral.Controls.Add(this.numNumConverters);
            this.gbGeneral.Controls.Add(this.cbPgoodConfig);
            this.gbGeneral.Controls.Add(this.label6);
            this.gbGeneral.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbGeneral.Location = new System.Drawing.Point(3, 3);
            this.gbGeneral.Name = "gbGeneral";
            this.gbGeneral.Size = new System.Drawing.Size(298, 81);
            this.gbGeneral.TabIndex = 0;
            this.gbGeneral.TabStop = false;
            this.gbGeneral.Text = "General settings";
            // 
            // gbAdcSettings
            // 
            this.gbAdcSettings.AutoSize = true;
            this.gbAdcSettings.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.gbAdcSettings.Controls.Add(this.tableLayoutPanel2);
            this.gbAdcSettings.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbAdcSettings.Location = new System.Drawing.Point(307, 3);
            this.gbAdcSettings.Name = "gbAdcSettings";
            this.tableLayoutPanel1.SetRowSpan(this.gbAdcSettings, 2);
            this.gbAdcSettings.Size = new System.Drawing.Size(274, 194);
            this.gbAdcSettings.TabIndex = 25;
            this.gbAdcSettings.TabStop = false;
            this.gbAdcSettings.Text = "ADC settings";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.AutoSize = true;
            this.tableLayoutPanel2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel2.ColumnCount = 3;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Controls.Add(this.m_lblRspTime, 0, 6);
            this.tableLayoutPanel2.Controls.Add(this.m_lblAdcRange, 1, 3);
            this.tableLayoutPanel2.Controls.Add(this.m_lblRefreshTime, 0, 5);
            this.tableLayoutPanel2.Controls.Add(this.m_chbExposeSoc, 1, 4);
            this.tableLayoutPanel2.Controls.Add(this.m_lblSampleAve, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.m_nudVrefVolts, 2, 2);
            this.tableLayoutPanel2.Controls.Add(this.m_chbEnableDma, 0, 4);
            this.tableLayoutPanel2.Controls.Add(this.m_cbSamplesAve, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.m_lblVrefSelect, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.m_cbVrefDisplay, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.m_lblAdcRangeValue, 2, 3);
            this.tableLayoutPanel2.Controls.Add(this.m_lblExtVref, 1, 2);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 17);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 7;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.Size = new System.Drawing.Size(265, 158);
            this.tableLayoutPanel2.TabIndex = 29;
            // 
            // m_lblRspTime
            // 
            this.m_lblRspTime.AutoSize = true;
            this.tableLayoutPanel2.SetColumnSpan(this.m_lblRspTime, 2);
            this.m_lblRspTime.Location = new System.Drawing.Point(2, 139);
            this.m_lblRspTime.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRspTime.Name = "m_lblRspTime";
            this.m_lblRspTime.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lblRspTime.Size = new System.Drawing.Size(80, 19);
            this.m_lblRspTime.TabIndex = 27;
            this.m_lblRspTime.Text = "Response time:";
            // 
            // m_lblAdcRange
            // 
            this.m_lblAdcRange.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lblAdcRange.AutoSize = true;
            this.m_lblAdcRange.Location = new System.Drawing.Point(92, 74);
            this.m_lblAdcRange.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblAdcRange.Name = "m_lblAdcRange";
            this.m_lblAdcRange.Padding = new System.Windows.Forms.Padding(0, 0, 0, 12);
            this.m_lblAdcRange.Size = new System.Drawing.Size(81, 25);
            this.m_lblAdcRange.TabIndex = 30;
            this.m_lblAdcRange.Text = " ADC range (V):";
            // 
            // m_lblRefreshTime
            // 
            this.m_lblRefreshTime.AutoSize = true;
            this.tableLayoutPanel2.SetColumnSpan(this.m_lblRefreshTime, 2);
            this.m_lblRefreshTime.Location = new System.Drawing.Point(2, 120);
            this.m_lblRefreshTime.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRefreshTime.Name = "m_lblRefreshTime";
            this.m_lblRefreshTime.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lblRefreshTime.Size = new System.Drawing.Size(80, 19);
            this.m_lblRefreshTime.TabIndex = 22;
            this.m_lblRefreshTime.Text = "ADC scan time:";
            // 
            // m_chbExposeSoc
            // 
            this.m_chbExposeSoc.AutoSize = true;
            this.m_chbExposeSoc.Location = new System.Drawing.Point(92, 101);
            this.m_chbExposeSoc.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbExposeSoc.Name = "m_chbExposeSoc";
            this.m_chbExposeSoc.Size = new System.Drawing.Size(86, 17);
            this.m_chbExposeSoc.TabIndex = 23;
            this.m_chbExposeSoc.Text = "Expose SOC";
            this.m_chbExposeSoc.UseVisualStyleBackColor = true;
            this.m_chbExposeSoc.CheckedChanged += new System.EventHandler(this.m_chbExposeSoc_CheckedChanged);
            // 
            // m_lblSampleAve
            // 
            this.m_lblSampleAve.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lblSampleAve.AutoSize = true;
            this.m_lblSampleAve.Location = new System.Drawing.Point(2, 6);
            this.m_lblSampleAve.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblSampleAve.Name = "m_lblSampleAve";
            this.m_lblSampleAve.Size = new System.Drawing.Size(82, 13);
            this.m_lblSampleAve.TabIndex = 16;
            this.m_lblSampleAve.Text = "Voltage filtering:";
            // 
            // m_nudVrefVolts
            // 
            this.m_nudVrefVolts.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.m_nudVrefVolts.DecimalPlaces = 3;
            this.m_nudVrefVolts.Location = new System.Drawing.Point(182, 52);
            this.m_nudVrefVolts.Margin = new System.Windows.Forms.Padding(2, 2, 15, 2);
            this.m_nudVrefVolts.Maximum = new decimal(new int[] {
            55,
            0,
            0,
            65536});
            this.m_nudVrefVolts.Name = "m_nudVrefVolts";
            this.m_nudVrefVolts.Size = new System.Drawing.Size(68, 20);
            this.m_nudVrefVolts.TabIndex = 26;
            this.m_nudVrefVolts.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.m_nudVrefVolts.Value = new decimal(new int[] {
            1024,
            0,
            0,
            196608});
            this.m_nudVrefVolts.TextChanged += new System.EventHandler(this.m_nudVrefVolts_TextChanged);
            // 
            // m_chbEnableDma
            // 
            this.m_chbEnableDma.AutoSize = true;
            this.m_chbEnableDma.Location = new System.Drawing.Point(2, 101);
            this.m_chbEnableDma.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbEnableDma.Name = "m_chbEnableDma";
            this.m_chbEnableDma.Size = new System.Drawing.Size(86, 17);
            this.m_chbEnableDma.TabIndex = 19;
            this.m_chbEnableDma.Text = "Enable DMA";
            this.m_chbEnableDma.UseVisualStyleBackColor = true;
            this.m_chbEnableDma.CheckedChanged += new System.EventHandler(this.m_chbEnableDma_CheckedChanged);
            // 
            // m_cbSamplesAve
            // 
            this.tableLayoutPanel2.SetColumnSpan(this.m_cbSamplesAve, 2);
            this.m_cbSamplesAve.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_cbSamplesAve.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSamplesAve.FormattingEnabled = true;
            this.m_cbSamplesAve.Location = new System.Drawing.Point(92, 2);
            this.m_cbSamplesAve.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbSamplesAve.Name = "m_cbSamplesAve";
            this.m_cbSamplesAve.Size = new System.Drawing.Size(171, 21);
            this.m_cbSamplesAve.TabIndex = 13;
            this.m_cbSamplesAve.SelectedIndexChanged += new System.EventHandler(this.m_cbSamplesAve_SelectedIndexChanged);
            // 
            // m_lblVrefSelect
            // 
            this.m_lblVrefSelect.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lblVrefSelect.AutoSize = true;
            this.m_lblVrefSelect.Location = new System.Drawing.Point(2, 31);
            this.m_lblVrefSelect.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblVrefSelect.Name = "m_lblVrefSelect";
            this.m_lblVrefSelect.Size = new System.Drawing.Size(60, 13);
            this.m_lblVrefSelect.TabIndex = 18;
            this.m_lblVrefSelect.Text = "Vref select:";
            // 
            // m_cbVrefDisplay
            // 
            this.tableLayoutPanel2.SetColumnSpan(this.m_cbVrefDisplay, 2);
            this.m_cbVrefDisplay.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_cbVrefDisplay.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbVrefDisplay.FormattingEnabled = true;
            this.m_cbVrefDisplay.Location = new System.Drawing.Point(92, 27);
            this.m_cbVrefDisplay.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbVrefDisplay.Name = "m_cbVrefDisplay";
            this.m_cbVrefDisplay.Size = new System.Drawing.Size(171, 21);
            this.m_cbVrefDisplay.TabIndex = 15;
            this.m_cbVrefDisplay.SelectedIndexChanged += new System.EventHandler(this.m_cbVrefDisplay_SelectedIndexChanged);
            // 
            // m_lblAdcRangeValue
            // 
            this.m_lblAdcRangeValue.AutoSize = true;
            this.m_lblAdcRangeValue.Location = new System.Drawing.Point(182, 74);
            this.m_lblAdcRangeValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblAdcRangeValue.Name = "m_lblAdcRangeValue";
            this.m_lblAdcRangeValue.Size = new System.Drawing.Size(34, 13);
            this.m_lblAdcRangeValue.TabIndex = 31;
            this.m_lblAdcRangeValue.Text = "2.048";
            // 
            // m_lblExtVref
            // 
            this.m_lblExtVref.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lblExtVref.AutoSize = true;
            this.m_lblExtVref.Location = new System.Drawing.Point(92, 55);
            this.m_lblExtVref.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblExtVref.Name = "m_lblExtVref";
            this.m_lblExtVref.Size = new System.Drawing.Size(77, 13);
            this.m_lblExtVref.TabIndex = 25;
            this.m_lblExtVref.Text = " Vref value (V):";
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbLoadConfig,
            this.tsbSaveConfig});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(842, 27);
            this.toolStrip1.TabIndex = 27;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbLoadConfig
            // 
            this.tsbLoadConfig.Image = global::PowerMonitor_P4_v2_0.Resources.Open;
            this.tsbLoadConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbLoadConfig.Name = "tsbLoadConfig";
            this.tsbLoadConfig.Size = new System.Drawing.Size(134, 24);
            this.tsbLoadConfig.Text = "Load Configuration";
            this.tsbLoadConfig.Click += new System.EventHandler(this.LoadConfig);
            // 
            // tsbSaveConfig
            // 
            this.tsbSaveConfig.Image = global::PowerMonitor_P4_v2_0.Resources.Save;
            this.tsbSaveConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSaveConfig.Name = "tsbSaveConfig";
            this.tsbSaveConfig.Size = new System.Drawing.Size(132, 24);
            this.tsbSaveConfig.Text = "Save Configuration";
            this.tsbSaveConfig.Click += new System.EventHandler(this.SaveConfig);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.gbGeneral, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.gbFaultSources, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.gbAdcSettings, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.gbWarningSources, 1, 1);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 30);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(584, 200);
            this.tableLayoutPanel1.TabIndex = 28;
            // 
            // CyGeneralTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.toolStrip1);
            this.Name = "CyGeneralTab";
            this.Size = new System.Drawing.Size(842, 524);
            this.Load += new System.EventHandler(this.CyBasicTab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numNumConverters)).EndInit();
            this.gbFaultSources.ResumeLayout(false);
            this.gbFaultSources.PerformLayout();
            this.gbWarningSources.ResumeLayout(false);
            this.gbWarningSources.PerformLayout();
            this.gbGeneral.ResumeLayout(false);
            this.gbGeneral.PerformLayout();
            this.gbAdcSettings.ResumeLayout(false);
            this.gbAdcSettings.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVrefVolts)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown numNumConverters;
        private System.Windows.Forms.ComboBox cbPgoodConfig;
        private System.Windows.Forms.GroupBox gbFaultSources;
        private System.Windows.Forms.CheckBox chbFaultUv;
        private System.Windows.Forms.CheckBox chbFaultOv;
        private System.Windows.Forms.GroupBox gbWarningSources;
        private System.Windows.Forms.CheckBox chbWarningUv;
        private System.Windows.Forms.CheckBox chbWarningOv;
        private System.Windows.Forms.GroupBox gbGeneral;
        private System.Windows.Forms.GroupBox gbAdcSettings;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsbLoadConfig;
        private System.Windows.Forms.ToolStripButton tsbSaveConfig;
        private System.Windows.Forms.Label m_lblSampleAve;
        private System.Windows.Forms.ComboBox m_cbVrefDisplay;
        private System.Windows.Forms.ComboBox m_cbSamplesAve;
        private System.Windows.Forms.Label m_lblVrefSelect;
        private System.Windows.Forms.CheckBox m_chbEnableDma;
        private System.Windows.Forms.Label m_lblRefreshTime;
        private System.Windows.Forms.CheckBox m_chbExposeSoc;
        private System.Windows.Forms.Label m_lblExtVref;
        private System.Windows.Forms.NumericUpDown m_nudVrefVolts;
        private System.Windows.Forms.Label m_lblRspTime;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Label m_lblAdcRange;
        private System.Windows.Forms.Label m_lblAdcRangeValue;
    }
}
