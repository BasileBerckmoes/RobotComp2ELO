namespace PowerMonitor_v1_60
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
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.numNumConverters = new System.Windows.Forms.NumericUpDown();
            this.numAuxChannels = new System.Windows.Forms.NumericUpDown();
            this.cbVoltageFilterType = new System.Windows.Forms.ComboBox();
            this.cbCurrentFilterType = new System.Windows.Forms.ComboBox();
            this.cbAuxFilterType = new System.Windows.Forms.ComboBox();
            this.cbPgoodConfig = new System.Windows.Forms.ComboBox();
            this.gbFaultSources = new System.Windows.Forms.GroupBox();
            this.chbFaultOc = new System.Windows.Forms.CheckBox();
            this.chbFaultUv = new System.Windows.Forms.CheckBox();
            this.chbFaultOv = new System.Windows.Forms.CheckBox();
            this.gbWarningSources = new System.Windows.Forms.GroupBox();
            this.chbWarningOc = new System.Windows.Forms.CheckBox();
            this.chbWarningUv = new System.Windows.Forms.CheckBox();
            this.chbWarningOv = new System.Windows.Forms.CheckBox();
            this.cbDiffCurrentRange = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.chbExposeCalibration = new System.Windows.Forms.CheckBox();
            this.lblLowVoltageMode = new System.Windows.Forms.Label();
            this.cbLowVoltageMode = new System.Windows.Forms.ComboBox();
            this.m_lblAdcBufferMode = new System.Windows.Forms.Label();
            this.m_cbAdcBufferMode = new System.Windows.Forms.ComboBox();
            this.m_lblEocConfig = new System.Windows.Forms.Label();
            this.m_cbEocConfig = new System.Windows.Forms.ComboBox();
            this.gbGeneral = new System.Windows.Forms.GroupBox();
            this.gbVoltageMeasurement = new System.Windows.Forms.GroupBox();
            this.gbCurrentMeasurement = new System.Windows.Forms.GroupBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbLoadConfig = new System.Windows.Forms.ToolStripButton();
            this.tsbSaveConfig = new System.Windows.Forms.ToolStripButton();
            ((System.ComponentModel.ISupportInitialize)(this.numNumConverters)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAuxChannels)).BeginInit();
            this.gbFaultSources.SuspendLayout();
            this.gbWarningSources.SuspendLayout();
            this.gbGeneral.SuspendLayout();
            this.gbVoltageMeasurement.SuspendLayout();
            this.gbCurrentMeasurement.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(112, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Number of converters:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(143, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Number of auxilary channels:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(105, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Voltage filtering type:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(103, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Current filtering type:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(143, 13);
            this.label5.TabIndex = 4;
            this.label5.Text = "Auxilary voltage filtering type:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 76);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(80, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "Pgood terminal:";
            // 
            // numNumConverters
            // 
            this.numNumConverters.Location = new System.Drawing.Point(162, 20);
            this.numNumConverters.Name = "numNumConverters";
            this.numNumConverters.Size = new System.Drawing.Size(114, 20);
            this.numNumConverters.TabIndex = 6;
            // 
            // numAuxChannels
            // 
            this.numAuxChannels.Location = new System.Drawing.Point(162, 47);
            this.numAuxChannels.Name = "numAuxChannels";
            this.numAuxChannels.Size = new System.Drawing.Size(114, 20);
            this.numAuxChannels.TabIndex = 7;
            // 
            // cbVoltageFilterType
            // 
            this.cbVoltageFilterType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbVoltageFilterType.FormattingEnabled = true;
            this.cbVoltageFilterType.Location = new System.Drawing.Point(178, 19);
            this.cbVoltageFilterType.Name = "cbVoltageFilterType";
            this.cbVoltageFilterType.Size = new System.Drawing.Size(114, 21);
            this.cbVoltageFilterType.TabIndex = 8;
            this.cbVoltageFilterType.SelectedIndexChanged += new System.EventHandler(this.cbVoltageFilterType_SelectedIndexChanged);
            // 
            // cbCurrentFilterType
            // 
            this.cbCurrentFilterType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbCurrentFilterType.FormattingEnabled = true;
            this.cbCurrentFilterType.Location = new System.Drawing.Point(178, 19);
            this.cbCurrentFilterType.Name = "cbCurrentFilterType";
            this.cbCurrentFilterType.Size = new System.Drawing.Size(114, 21);
            this.cbCurrentFilterType.TabIndex = 9;
            this.cbCurrentFilterType.SelectedIndexChanged += new System.EventHandler(this.cbCurrentFilterType_SelectedIndexChanged);
            // 
            // cbAuxFilterType
            // 
            this.cbAuxFilterType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbAuxFilterType.FormattingEnabled = true;
            this.cbAuxFilterType.Location = new System.Drawing.Point(178, 46);
            this.cbAuxFilterType.Name = "cbAuxFilterType";
            this.cbAuxFilterType.Size = new System.Drawing.Size(114, 21);
            this.cbAuxFilterType.TabIndex = 10;
            this.cbAuxFilterType.SelectedIndexChanged += new System.EventHandler(this.cbAuxFilterType_SelectedIndexChanged);
            // 
            // cbPgoodConfig
            // 
            this.cbPgoodConfig.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPgoodConfig.FormattingEnabled = true;
            this.cbPgoodConfig.Location = new System.Drawing.Point(162, 73);
            this.cbPgoodConfig.Name = "cbPgoodConfig";
            this.cbPgoodConfig.Size = new System.Drawing.Size(114, 21);
            this.cbPgoodConfig.TabIndex = 13;
            this.cbPgoodConfig.SelectedIndexChanged += new System.EventHandler(this.cbPgoodConfig_SelectedIndexChanged);
            // 
            // gbFaultSources
            // 
            this.gbFaultSources.Controls.Add(this.chbFaultOc);
            this.gbFaultSources.Controls.Add(this.chbFaultUv);
            this.gbFaultSources.Controls.Add(this.chbFaultOv);
            this.gbFaultSources.Location = new System.Drawing.Point(3, 184);
            this.gbFaultSources.Name = "gbFaultSources";
            this.gbFaultSources.Size = new System.Drawing.Size(149, 88);
            this.gbFaultSources.TabIndex = 14;
            this.gbFaultSources.TabStop = false;
            this.gbFaultSources.Text = "Fault sources";
            // 
            // chbFaultOc
            // 
            this.chbFaultOc.AutoSize = true;
            this.chbFaultOc.Location = new System.Drawing.Point(6, 65);
            this.chbFaultOc.Name = "chbFaultOc";
            this.chbFaultOc.Size = new System.Drawing.Size(110, 17);
            this.chbFaultOc.TabIndex = 2;
            this.chbFaultOc.Text = "Over Current (OC)";
            this.chbFaultOc.UseVisualStyleBackColor = true;
            this.chbFaultOc.CheckedChanged += new System.EventHandler(this.chbFaultOc_CheckedChanged);
            // 
            // chbFaultUv
            // 
            this.chbFaultUv.AutoSize = true;
            this.chbFaultUv.Location = new System.Drawing.Point(6, 42);
            this.chbFaultUv.Name = "chbFaultUv";
            this.chbFaultUv.Size = new System.Drawing.Size(118, 17);
            this.chbFaultUv.TabIndex = 1;
            this.chbFaultUv.Text = "Under Voltage (UV)";
            this.chbFaultUv.UseVisualStyleBackColor = true;
            this.chbFaultUv.CheckedChanged += new System.EventHandler(this.chbFaultUv_CheckedChanged);
            // 
            // chbFaultOv
            // 
            this.chbFaultOv.AutoSize = true;
            this.chbFaultOv.Location = new System.Drawing.Point(6, 19);
            this.chbFaultOv.Name = "chbFaultOv";
            this.chbFaultOv.Size = new System.Drawing.Size(112, 17);
            this.chbFaultOv.TabIndex = 0;
            this.chbFaultOv.Text = "Over Voltage (OV)";
            this.chbFaultOv.UseVisualStyleBackColor = true;
            this.chbFaultOv.CheckedChanged += new System.EventHandler(this.chbFaultOv_CheckedChanged);
            // 
            // gbWarningSources
            // 
            this.gbWarningSources.Controls.Add(this.chbWarningOc);
            this.gbWarningSources.Controls.Add(this.chbWarningUv);
            this.gbWarningSources.Controls.Add(this.chbWarningOv);
            this.gbWarningSources.Location = new System.Drawing.Point(159, 184);
            this.gbWarningSources.Name = "gbWarningSources";
            this.gbWarningSources.Size = new System.Drawing.Size(149, 88);
            this.gbWarningSources.TabIndex = 15;
            this.gbWarningSources.TabStop = false;
            this.gbWarningSources.Text = "Warning sources";
            // 
            // chbWarningOc
            // 
            this.chbWarningOc.AutoSize = true;
            this.chbWarningOc.Location = new System.Drawing.Point(6, 65);
            this.chbWarningOc.Name = "chbWarningOc";
            this.chbWarningOc.Size = new System.Drawing.Size(110, 17);
            this.chbWarningOc.TabIndex = 2;
            this.chbWarningOc.Text = "Over Current (OC)";
            this.chbWarningOc.UseVisualStyleBackColor = true;
            this.chbWarningOc.CheckedChanged += new System.EventHandler(this.chbWarningOc_CheckedChanged);
            // 
            // chbWarningUv
            // 
            this.chbWarningUv.AutoSize = true;
            this.chbWarningUv.Location = new System.Drawing.Point(6, 42);
            this.chbWarningUv.Name = "chbWarningUv";
            this.chbWarningUv.Size = new System.Drawing.Size(118, 17);
            this.chbWarningUv.TabIndex = 1;
            this.chbWarningUv.Text = "Under Voltage (UV)";
            this.chbWarningUv.UseVisualStyleBackColor = true;
            this.chbWarningUv.CheckedChanged += new System.EventHandler(this.chbWarningUv_CheckedChanged);
            // 
            // chbWarningOv
            // 
            this.chbWarningOv.AutoSize = true;
            this.chbWarningOv.Location = new System.Drawing.Point(6, 19);
            this.chbWarningOv.Name = "chbWarningOv";
            this.chbWarningOv.Size = new System.Drawing.Size(112, 17);
            this.chbWarningOv.TabIndex = 0;
            this.chbWarningOv.Text = "Over Voltage (OV)";
            this.chbWarningOv.UseVisualStyleBackColor = true;
            this.chbWarningOv.CheckedChanged += new System.EventHandler(this.chbWarningOv_CheckedChanged);
            // 
            // cbDiffCurrentRange
            // 
            this.cbDiffCurrentRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDiffCurrentRange.FormattingEnabled = true;
            this.cbDiffCurrentRange.Location = new System.Drawing.Point(178, 46);
            this.cbDiffCurrentRange.Name = "cbDiffCurrentRange";
            this.cbDiffCurrentRange.Size = new System.Drawing.Size(114, 21);
            this.cbDiffCurrentRange.TabIndex = 11;
            this.cbDiffCurrentRange.SelectedIndexChanged += new System.EventHandler(this.cbDiffCurrentRange_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 49);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(138, 13);
            this.label7.TabIndex = 16;
            this.label7.Text = "Current sensing ADC range:";
            // 
            // chbExposeCalibration
            // 
            this.chbExposeCalibration.AutoSize = true;
            this.chbExposeCalibration.Location = new System.Drawing.Point(6, 128);
            this.chbExposeCalibration.Name = "chbExposeCalibration";
            this.chbExposeCalibration.Size = new System.Drawing.Size(112, 17);
            this.chbExposeCalibration.TabIndex = 12;
            this.chbExposeCalibration.Text = "Expose calibration";
            this.chbExposeCalibration.UseVisualStyleBackColor = true;
            this.chbExposeCalibration.CheckedChanged += new System.EventHandler(this.chbExposeCalibration_CheckedChanged);
            // 
            // lblLowVoltageMode
            // 
            this.lblLowVoltageMode.AutoSize = true;
            this.lblLowVoltageMode.Location = new System.Drawing.Point(6, 76);
            this.lblLowVoltageMode.Name = "lblLowVoltageMode";
            this.lblLowVoltageMode.Size = new System.Drawing.Size(140, 13);
            this.lblLowVoltageMode.TabIndex = 17;
            this.lblLowVoltageMode.Text = "Voltage sensing ADC range:";
            // 
            // cbLowVoltageMode
            // 
            this.cbLowVoltageMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbLowVoltageMode.FormattingEnabled = true;
            this.cbLowVoltageMode.Location = new System.Drawing.Point(178, 73);
            this.cbLowVoltageMode.Name = "cbLowVoltageMode";
            this.cbLowVoltageMode.Size = new System.Drawing.Size(114, 21);
            this.cbLowVoltageMode.TabIndex = 18;
            // 
            // m_lblAdcBufferMode
            // 
            this.m_lblAdcBufferMode.AutoSize = true;
            this.m_lblAdcBufferMode.Location = new System.Drawing.Point(6, 103);
            this.m_lblAdcBufferMode.Name = "m_lblAdcBufferMode";
            this.m_lblAdcBufferMode.Size = new System.Drawing.Size(169, 13);
            this.m_lblAdcBufferMode.TabIndex = 20;
            this.m_lblAdcBufferMode.Text = "Voltage sensing ADC buffer mode:";
            // 
            // m_cbAdcBufferMode
            // 
            this.m_cbAdcBufferMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbAdcBufferMode.FormattingEnabled = true;
            this.m_cbAdcBufferMode.Location = new System.Drawing.Point(178, 100);
            this.m_cbAdcBufferMode.Name = "m_cbAdcBufferMode";
            this.m_cbAdcBufferMode.Size = new System.Drawing.Size(114, 21);
            this.m_cbAdcBufferMode.TabIndex = 21;
            // 
            // m_lblEocConfig
            // 
            this.m_lblEocConfig.AutoSize = true;
            this.m_lblEocConfig.Location = new System.Drawing.Point(6, 103);
            this.m_lblEocConfig.Name = "m_lblEocConfig";
            this.m_lblEocConfig.Size = new System.Drawing.Size(96, 13);
            this.m_lblEocConfig.TabIndex = 22;
            this.m_lblEocConfig.Text = "EOC configuration:";
            // 
            // m_cbEocConfig
            // 
            this.m_cbEocConfig.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbEocConfig.FormattingEnabled = true;
            this.m_cbEocConfig.Location = new System.Drawing.Point(162, 100);
            this.m_cbEocConfig.Name = "m_cbEocConfig";
            this.m_cbEocConfig.Size = new System.Drawing.Size(114, 21);
            this.m_cbEocConfig.TabIndex = 23;
            // 
            // gbGeneral
            // 
            this.gbGeneral.Controls.Add(this.label1);
            this.gbGeneral.Controls.Add(this.m_cbEocConfig);
            this.gbGeneral.Controls.Add(this.label2);
            this.gbGeneral.Controls.Add(this.m_lblEocConfig);
            this.gbGeneral.Controls.Add(this.numNumConverters);
            this.gbGeneral.Controls.Add(this.chbExposeCalibration);
            this.gbGeneral.Controls.Add(this.numAuxChannels);
            this.gbGeneral.Controls.Add(this.cbPgoodConfig);
            this.gbGeneral.Controls.Add(this.label6);
            this.gbGeneral.Location = new System.Drawing.Point(3, 28);
            this.gbGeneral.Name = "gbGeneral";
            this.gbGeneral.Size = new System.Drawing.Size(305, 150);
            this.gbGeneral.TabIndex = 24;
            this.gbGeneral.TabStop = false;
            this.gbGeneral.Text = "General settings";
            // 
            // gbVoltageMeasurement
            // 
            this.gbVoltageMeasurement.Controls.Add(this.cbVoltageFilterType);
            this.gbVoltageMeasurement.Controls.Add(this.label3);
            this.gbVoltageMeasurement.Controls.Add(this.cbLowVoltageMode);
            this.gbVoltageMeasurement.Controls.Add(this.label5);
            this.gbVoltageMeasurement.Controls.Add(this.lblLowVoltageMode);
            this.gbVoltageMeasurement.Controls.Add(this.cbAuxFilterType);
            this.gbVoltageMeasurement.Controls.Add(this.m_lblAdcBufferMode);
            this.gbVoltageMeasurement.Controls.Add(this.m_cbAdcBufferMode);
            this.gbVoltageMeasurement.Location = new System.Drawing.Point(314, 28);
            this.gbVoltageMeasurement.Name = "gbVoltageMeasurement";
            this.gbVoltageMeasurement.Size = new System.Drawing.Size(304, 150);
            this.gbVoltageMeasurement.TabIndex = 25;
            this.gbVoltageMeasurement.TabStop = false;
            this.gbVoltageMeasurement.Text = "Voltage measurement";
            // 
            // gbCurrentMeasurement
            // 
            this.gbCurrentMeasurement.Controls.Add(this.cbCurrentFilterType);
            this.gbCurrentMeasurement.Controls.Add(this.label4);
            this.gbCurrentMeasurement.Controls.Add(this.cbDiffCurrentRange);
            this.gbCurrentMeasurement.Controls.Add(this.label7);
            this.gbCurrentMeasurement.Location = new System.Drawing.Point(314, 184);
            this.gbCurrentMeasurement.Name = "gbCurrentMeasurement";
            this.gbCurrentMeasurement.Size = new System.Drawing.Size(304, 88);
            this.gbCurrentMeasurement.TabIndex = 26;
            this.gbCurrentMeasurement.TabStop = false;
            this.gbCurrentMeasurement.Text = "Current measurement";
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbLoadConfig,
            this.tsbSaveConfig});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(632, 25);
            this.toolStrip1.TabIndex = 27;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbLoadConfig
            // 
            this.tsbLoadConfig.Image = global::PowerMonitor_v1_60.Resources.Open;
            this.tsbLoadConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbLoadConfig.Name = "tsbLoadConfig";
            this.tsbLoadConfig.Size = new System.Drawing.Size(128, 22);
            this.tsbLoadConfig.Text = "Load configuration";
            this.tsbLoadConfig.Click += new System.EventHandler(this.LoadConfig);
            // 
            // tsbSaveConfig
            // 
            this.tsbSaveConfig.Image = global::PowerMonitor_v1_60.Resources.Save;
            this.tsbSaveConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSaveConfig.Name = "tsbSaveConfig";
            this.tsbSaveConfig.Size = new System.Drawing.Size(126, 22);
            this.tsbSaveConfig.Text = "Save configuration";
            this.tsbSaveConfig.Click += new System.EventHandler(this.SaveConfig);
            // 
            // CyGeneralTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.gbCurrentMeasurement);
            this.Controls.Add(this.gbVoltageMeasurement);
            this.Controls.Add(this.gbGeneral);
            this.Controls.Add(this.gbWarningSources);
            this.Controls.Add(this.gbFaultSources);
            this.Name = "CyGeneralTab";
            this.Size = new System.Drawing.Size(632, 285);
            this.Load += new System.EventHandler(this.CyBasicTab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numNumConverters)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAuxChannels)).EndInit();
            this.gbFaultSources.ResumeLayout(false);
            this.gbFaultSources.PerformLayout();
            this.gbWarningSources.ResumeLayout(false);
            this.gbWarningSources.PerformLayout();
            this.gbGeneral.ResumeLayout(false);
            this.gbGeneral.PerformLayout();
            this.gbVoltageMeasurement.ResumeLayout(false);
            this.gbVoltageMeasurement.PerformLayout();
            this.gbCurrentMeasurement.ResumeLayout(false);
            this.gbCurrentMeasurement.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown numNumConverters;
        private System.Windows.Forms.NumericUpDown numAuxChannels;
        private System.Windows.Forms.ComboBox cbVoltageFilterType;
        private System.Windows.Forms.ComboBox cbCurrentFilterType;
        private System.Windows.Forms.ComboBox cbAuxFilterType;
        private System.Windows.Forms.ComboBox cbPgoodConfig;
        private System.Windows.Forms.GroupBox gbFaultSources;
        private System.Windows.Forms.CheckBox chbFaultOc;
        private System.Windows.Forms.CheckBox chbFaultUv;
        private System.Windows.Forms.CheckBox chbFaultOv;
        private System.Windows.Forms.GroupBox gbWarningSources;
        private System.Windows.Forms.CheckBox chbWarningOc;
        private System.Windows.Forms.CheckBox chbWarningUv;
        private System.Windows.Forms.CheckBox chbWarningOv;
        private System.Windows.Forms.ComboBox cbDiffCurrentRange;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox chbExposeCalibration;
        private System.Windows.Forms.Label lblLowVoltageMode;
        private System.Windows.Forms.ComboBox cbLowVoltageMode;
        private System.Windows.Forms.Label m_lblAdcBufferMode;
        private System.Windows.Forms.ComboBox m_cbAdcBufferMode;
        private System.Windows.Forms.Label m_lblEocConfig;
        private System.Windows.Forms.ComboBox m_cbEocConfig;
        private System.Windows.Forms.GroupBox gbGeneral;
        private System.Windows.Forms.GroupBox gbVoltageMeasurement;
        private System.Windows.Forms.GroupBox gbCurrentMeasurement;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsbLoadConfig;
        private System.Windows.Forms.ToolStripButton tsbSaveConfig;
    }
}
