namespace VoltageFaultDetector_v3_0
{
    partial class CyBasicTab
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
            this.label1 = new System.Windows.Forms.Label();
            this.numNumVoltages = new System.Windows.Forms.NumericUpDown();
            this.labelCompareType = new System.Windows.Forms.Label();
            this.comboBoxCompareType = new System.Windows.Forms.ComboBox();
            this.labelGFLength = new System.Windows.Forms.Label();
            this.numGFLength = new System.Windows.Forms.NumericUpDown();
            this.m_chbExtRef = new System.Windows.Forms.CheckBox();
            this.comboBoxDACRange = new System.Windows.Forms.ComboBox();
            this.labelDACRange = new System.Windows.Forms.Label();
            this.labelPhysicalPlasement = new System.Windows.Forms.Label();
            this.comboBoxPhysicalPlacement = new System.Windows.Forms.ComboBox();
            this.labelAnalogBus = new System.Windows.Forms.Label();
            this.comboBoxAnalogBus = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxSpeedMode = new System.Windows.Forms.ComboBox();
            this.errProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_chbVinMuxEn = new System.Windows.Forms.CheckBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbLoadConfig = new System.Windows.Forms.ToolStripButton();
            this.tsbSaveConfig = new System.Windows.Forms.ToolStripButton();
            this.gbGeneral = new System.Windows.Forms.GroupBox();
            this.lbScanPerVoltage = new System.Windows.Forms.Label();
            this.lbTotalScanRate = new System.Windows.Forms.Label();
            this.labelScanPerVoltage = new System.Windows.Forms.Label();
            this.labelTotalScanRate = new System.Windows.Forms.Label();
            this.numSettlingDelay = new System.Windows.Forms.NumericUpDown();
            this.labelVinSettingDelay = new System.Windows.Forms.Label();
            this.gbAnalog = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.numNumVoltages)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numGFLength)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.gbGeneral.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSettlingDelay)).BeginInit();
            this.gbAnalog.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(102, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Number of voltages:";
            // 
            // numNumVoltages
            // 
            this.numNumVoltages.Location = new System.Drawing.Point(148, 14);
            this.numNumVoltages.Maximum = new decimal(new int[] {
            32,
            0,
            0,
            0});
            this.numNumVoltages.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numNumVoltages.Name = "numNumVoltages";
            this.numNumVoltages.Size = new System.Drawing.Size(54, 20);
            this.numNumVoltages.TabIndex = 0;
            this.numNumVoltages.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // labelCompareType
            // 
            this.labelCompareType.AutoSize = true;
            this.labelCompareType.Location = new System.Drawing.Point(6, 16);
            this.labelCompareType.Name = "labelCompareType";
            this.labelCompareType.Size = new System.Drawing.Size(75, 13);
            this.labelCompareType.TabIndex = 7;
            this.labelCompareType.Text = "Compare type:";
            // 
            // comboBoxCompareType
            // 
            this.comboBoxCompareType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxCompareType.FormattingEnabled = true;
            this.comboBoxCompareType.Items.AddRange(new object[] {
            "OV/UV",
            "OV only",
            "UV only"});
            this.comboBoxCompareType.Location = new System.Drawing.Point(111, 13);
            this.comboBoxCompareType.Name = "comboBoxCompareType";
            this.comboBoxCompareType.Size = new System.Drawing.Size(95, 21);
            this.comboBoxCompareType.TabIndex = 4;
            this.comboBoxCompareType.SelectedIndexChanged += new System.EventHandler(this.comboBoxCompareType_SelectedIndexChanged);
            // 
            // labelGFLength
            // 
            this.labelGFLength.AutoSize = true;
            this.labelGFLength.Location = new System.Drawing.Point(6, 42);
            this.labelGFLength.Name = "labelGFLength";
            this.labelGFLength.Size = new System.Drawing.Size(130, 13);
            this.labelGFLength.TabIndex = 9;
            this.labelGFLength.Text = "Glitch filter length (cycles):";
            // 
            // numGFLength
            // 
            this.numGFLength.Location = new System.Drawing.Point(148, 40);
            this.numGFLength.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numGFLength.Name = "numGFLength";
            this.numGFLength.Size = new System.Drawing.Size(54, 20);
            this.numGFLength.TabIndex = 1;
            this.numGFLength.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // m_chbExtRef
            // 
            this.m_chbExtRef.AutoSize = true;
            this.m_chbExtRef.Location = new System.Drawing.Point(3, 184);
            this.m_chbExtRef.Name = "m_chbExtRef";
            this.m_chbExtRef.Size = new System.Drawing.Size(147, 17);
            this.m_chbExtRef.TabIndex = 9;
            this.m_chbExtRef.Text = "Enable external reference";
            this.m_chbExtRef.UseVisualStyleBackColor = true;
            // 
            // comboBoxDACRange
            // 
            this.comboBoxDACRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDACRange.FormattingEnabled = true;
            this.comboBoxDACRange.Items.AddRange(new object[] {
            "1V",
            "4V"});
            this.comboBoxDACRange.Location = new System.Drawing.Point(111, 92);
            this.comboBoxDACRange.Name = "comboBoxDACRange";
            this.comboBoxDACRange.Size = new System.Drawing.Size(95, 21);
            this.comboBoxDACRange.TabIndex = 7;
            this.comboBoxDACRange.SelectedIndexChanged += new System.EventHandler(this.comboBoxDACRange_SelectedIndexChanged);
            // 
            // labelDACRange
            // 
            this.labelDACRange.AutoSize = true;
            this.labelDACRange.Location = new System.Drawing.Point(6, 95);
            this.labelDACRange.Name = "labelDACRange";
            this.labelDACRange.Size = new System.Drawing.Size(62, 13);
            this.labelDACRange.TabIndex = 13;
            this.labelDACRange.Text = "DAC range:";
            // 
            // labelPhysicalPlasement
            // 
            this.labelPhysicalPlasement.AutoSize = true;
            this.labelPhysicalPlasement.Location = new System.Drawing.Point(6, 68);
            this.labelPhysicalPlasement.Name = "labelPhysicalPlasement";
            this.labelPhysicalPlasement.Size = new System.Drawing.Size(101, 13);
            this.labelPhysicalPlasement.TabIndex = 14;
            this.labelPhysicalPlasement.Text = "Physical placement:";
            // 
            // comboBoxPhysicalPlacement
            // 
            this.comboBoxPhysicalPlacement.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxPhysicalPlacement.FormattingEnabled = true;
            this.comboBoxPhysicalPlacement.Location = new System.Drawing.Point(111, 65);
            this.comboBoxPhysicalPlacement.Name = "comboBoxPhysicalPlacement";
            this.comboBoxPhysicalPlacement.Size = new System.Drawing.Size(95, 21);
            this.comboBoxPhysicalPlacement.TabIndex = 6;
            this.comboBoxPhysicalPlacement.SelectedIndexChanged += new System.EventHandler(this.comboBoxPhysicalPlacement_SelectedIndexChanged);
            // 
            // labelAnalogBus
            // 
            this.labelAnalogBus.AutoSize = true;
            this.labelAnalogBus.Location = new System.Drawing.Point(6, 42);
            this.labelAnalogBus.Name = "labelAnalogBus";
            this.labelAnalogBus.Size = new System.Drawing.Size(63, 13);
            this.labelAnalogBus.TabIndex = 16;
            this.labelAnalogBus.Text = "Analog bus:";
            // 
            // comboBoxAnalogBus
            // 
            this.comboBoxAnalogBus.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxAnalogBus.FormattingEnabled = true;
            this.comboBoxAnalogBus.Items.AddRange(new object[] {
            "AMXUBUSL",
            "AMXUBUSR"});
            this.comboBoxAnalogBus.Location = new System.Drawing.Point(111, 39);
            this.comboBoxAnalogBus.Name = "comboBoxAnalogBus";
            this.comboBoxAnalogBus.Size = new System.Drawing.Size(95, 21);
            this.comboBoxAnalogBus.TabIndex = 5;
            this.comboBoxAnalogBus.SelectedIndexChanged += new System.EventHandler(this.comboBoxAnalogBus_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 122);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 13);
            this.label2.TabIndex = 19;
            this.label2.Text = "Speed mode:";
            // 
            // comboBoxSpeedMode
            // 
            this.comboBoxSpeedMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSpeedMode.FormattingEnabled = true;
            this.comboBoxSpeedMode.Items.AddRange(new object[] {
            "Low speed",
            "High speed"});
            this.comboBoxSpeedMode.Location = new System.Drawing.Point(111, 119);
            this.comboBoxSpeedMode.Name = "comboBoxSpeedMode";
            this.comboBoxSpeedMode.Size = new System.Drawing.Size(95, 21);
            this.comboBoxSpeedMode.TabIndex = 8;
            this.comboBoxSpeedMode.SelectedIndexChanged += new System.EventHandler(this.comboBoxSpeedMode_SelectedIndexChanged);
            // 
            // errProvider
            // 
            this.errProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errProvider.ContainerControl = this;
            // 
            // m_chbVinMuxEn
            // 
            this.m_chbVinMuxEn.AutoSize = true;
            this.m_chbVinMuxEn.Location = new System.Drawing.Point(3, 207);
            this.m_chbVinMuxEn.Name = "m_chbVinMuxEn";
            this.m_chbVinMuxEn.Size = new System.Drawing.Size(131, 17);
            this.m_chbVinMuxEn.TabIndex = 10;
            this.m_chbVinMuxEn.Text = "Enable vin mux output";
            this.m_chbVinMuxEn.UseVisualStyleBackColor = true;
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbLoadConfig,
            this.tsbSaveConfig});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(449, 25);
            this.toolStrip1.TabIndex = 28;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbLoadConfig
            // 
            this.tsbLoadConfig.Image = global::VoltageFaultDetector_v3_0.Resources.Open;
            this.tsbLoadConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbLoadConfig.Name = "tsbLoadConfig";
            this.tsbLoadConfig.Size = new System.Drawing.Size(116, 22);
            this.tsbLoadConfig.Text = "Load configuration";
            this.tsbLoadConfig.Click += new System.EventHandler(this.LoadConfig);
            // 
            // tsbSaveConfig
            // 
            this.tsbSaveConfig.Image = global::VoltageFaultDetector_v3_0.Resources.Save;
            this.tsbSaveConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSaveConfig.Name = "tsbSaveConfig";
            this.tsbSaveConfig.Size = new System.Drawing.Size(117, 22);
            this.tsbSaveConfig.Text = "Save configuration";
            this.tsbSaveConfig.Click += new System.EventHandler(this.SaveConfig);
            // 
            // gbGeneral
            // 
            this.gbGeneral.Controls.Add(this.lbScanPerVoltage);
            this.gbGeneral.Controls.Add(this.lbTotalScanRate);
            this.gbGeneral.Controls.Add(this.labelScanPerVoltage);
            this.gbGeneral.Controls.Add(this.labelTotalScanRate);
            this.gbGeneral.Controls.Add(this.labelGFLength);
            this.gbGeneral.Controls.Add(this.numNumVoltages);
            this.gbGeneral.Controls.Add(this.numSettlingDelay);
            this.gbGeneral.Controls.Add(this.labelVinSettingDelay);
            this.gbGeneral.Controls.Add(this.label1);
            this.gbGeneral.Controls.Add(this.numGFLength);
            this.gbGeneral.Location = new System.Drawing.Point(3, 28);
            this.gbGeneral.Name = "gbGeneral";
            this.gbGeneral.Size = new System.Drawing.Size(226, 150);
            this.gbGeneral.TabIndex = 0;
            this.gbGeneral.TabStop = false;
            this.gbGeneral.Text = "General settings";
            // 
            // lbScanPerVoltage
            // 
            this.lbScanPerVoltage.AutoSize = true;
            this.lbScanPerVoltage.Location = new System.Drawing.Point(145, 122);
            this.lbScanPerVoltage.Name = "lbScanPerVoltage";
            this.lbScanPerVoltage.Size = new System.Drawing.Size(57, 13);
            this.lbScanPerVoltage.TabIndex = 24;
            this.lbScanPerVoltage.Text = "(unknown)";
            // 
            // lbTotalScanRate
            // 
            this.lbTotalScanRate.AutoSize = true;
            this.lbTotalScanRate.Location = new System.Drawing.Point(145, 95);
            this.lbTotalScanRate.Name = "lbTotalScanRate";
            this.lbTotalScanRate.Size = new System.Drawing.Size(57, 13);
            this.lbTotalScanRate.TabIndex = 23;
            this.lbTotalScanRate.Text = "(unknown)";
            // 
            // labelScanPerVoltage
            // 
            this.labelScanPerVoltage.AutoSize = true;
            this.labelScanPerVoltage.Location = new System.Drawing.Point(6, 122);
            this.labelScanPerVoltage.Name = "labelScanPerVoltage";
            this.labelScanPerVoltage.Size = new System.Drawing.Size(133, 13);
            this.labelScanPerVoltage.TabIndex = 22;
            this.labelScanPerVoltage.Text = "Scanning time per voltage:";
            // 
            // labelTotalScanRate
            // 
            this.labelTotalScanRate.AutoSize = true;
            this.labelTotalScanRate.Location = new System.Drawing.Point(6, 95);
            this.labelTotalScanRate.Name = "labelTotalScanRate";
            this.labelTotalScanRate.Size = new System.Drawing.Size(80, 13);
            this.labelTotalScanRate.TabIndex = 21;
            this.labelTotalScanRate.Text = "Response time:";
            // 
            // numSettlingDelay
            // 
            this.numSettlingDelay.Location = new System.Drawing.Point(148, 66);
            this.numSettlingDelay.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numSettlingDelay.Name = "numSettlingDelay";
            this.numSettlingDelay.Size = new System.Drawing.Size(54, 20);
            this.numSettlingDelay.TabIndex = 3;
            this.numSettlingDelay.Value = new decimal(new int[] {
            64,
            0,
            0,
            0});
            // 
            // labelVinSettingDelay
            // 
            this.labelVinSettingDelay.AutoSize = true;
            this.labelVinSettingDelay.Location = new System.Drawing.Point(6, 68);
            this.labelVinSettingDelay.Name = "labelVinSettingDelay";
            this.labelVinSettingDelay.Size = new System.Drawing.Size(130, 13);
            this.labelVinSettingDelay.TabIndex = 19;
            this.labelVinSettingDelay.Text = "Vin settling delay (counts):";
            // 
            // gbAnalog
            // 
            this.gbAnalog.Controls.Add(this.labelCompareType);
            this.gbAnalog.Controls.Add(this.comboBoxCompareType);
            this.gbAnalog.Controls.Add(this.labelPhysicalPlasement);
            this.gbAnalog.Controls.Add(this.comboBoxPhysicalPlacement);
            this.gbAnalog.Controls.Add(this.comboBoxSpeedMode);
            this.gbAnalog.Controls.Add(this.labelAnalogBus);
            this.gbAnalog.Controls.Add(this.label2);
            this.gbAnalog.Controls.Add(this.labelDACRange);
            this.gbAnalog.Controls.Add(this.comboBoxDACRange);
            this.gbAnalog.Controls.Add(this.comboBoxAnalogBus);
            this.gbAnalog.Location = new System.Drawing.Point(235, 28);
            this.gbAnalog.Name = "gbAnalog";
            this.gbAnalog.Size = new System.Drawing.Size(212, 150);
            this.gbAnalog.TabIndex = 1;
            this.gbAnalog.TabStop = false;
            this.gbAnalog.Text = "Analog settings";
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_chbVinMuxEn);
            this.Controls.Add(this.m_chbExtRef);
            this.Controls.Add(this.gbAnalog);
            this.Controls.Add(this.gbGeneral);
            this.Controls.Add(this.toolStrip1);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(449, 231);
            this.Load += new System.EventHandler(this.CyBasicTab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numNumVoltages)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numGFLength)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.gbGeneral.ResumeLayout(false);
            this.gbGeneral.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSettlingDelay)).EndInit();
            this.gbAnalog.ResumeLayout(false);
            this.gbAnalog.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numNumVoltages;
        private System.Windows.Forms.Label labelCompareType;
        private System.Windows.Forms.ComboBox comboBoxCompareType;
        private System.Windows.Forms.Label labelGFLength;
        private System.Windows.Forms.NumericUpDown numGFLength;
        private System.Windows.Forms.CheckBox m_chbExtRef;
        private System.Windows.Forms.ComboBox comboBoxDACRange;
        private System.Windows.Forms.Label labelDACRange;
        private System.Windows.Forms.Label labelPhysicalPlasement;
        private System.Windows.Forms.ComboBox comboBoxPhysicalPlacement;
        private System.Windows.Forms.Label labelAnalogBus;
        private System.Windows.Forms.ComboBox comboBoxAnalogBus;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxSpeedMode;
        private System.Windows.Forms.ErrorProvider errProvider;
        private System.Windows.Forms.CheckBox m_chbVinMuxEn;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsbLoadConfig;
        private System.Windows.Forms.ToolStripButton tsbSaveConfig;
        private System.Windows.Forms.GroupBox gbAnalog;
        private System.Windows.Forms.GroupBox gbGeneral;
        private System.Windows.Forms.Label labelVinSettingDelay;
        private System.Windows.Forms.NumericUpDown numSettlingDelay;
        private System.Windows.Forms.Label labelScanPerVoltage;
        private System.Windows.Forms.Label labelTotalScanRate;
        private System.Windows.Forms.Label lbTotalScanRate;
        private System.Windows.Forms.Label lbScanPerVoltage;
    }
}
