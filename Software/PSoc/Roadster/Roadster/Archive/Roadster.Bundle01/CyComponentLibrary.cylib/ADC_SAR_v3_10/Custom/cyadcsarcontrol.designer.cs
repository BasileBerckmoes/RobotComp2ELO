namespace ADC_SAR_v3_10
{
    partial class CyConfigureTab
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
            this.gbModes = new System.Windows.Forms.GroupBox();
            this.lblActualClockFrequency = new System.Windows.Forms.Label();
            this.lblActualFrequencyLabel = new System.Windows.Forms.Label();
            this.lblActualConversionRate = new System.Windows.Forms.Label();
            this.lblConversionRateLabel = new System.Windows.Forms.Label();
            this.lblNoRate = new System.Windows.Forms.Label();
            this.numSampleRate = new System.Windows.Forms.NumericUpDown();
            this.Convertsion_label = new System.Windows.Forms.Label();
            this.cbResolution = new System.Windows.Forms.ComboBox();
            this.ADC_Resolution_label = new System.Windows.Forms.Label();
            this.m_gbClockSource = new System.Windows.Forms.GroupBox();
            this.rbExternal = new System.Windows.Forms.RadioButton();
            this.rbInternal = new System.Windows.Forms.RadioButton();
            this.m_gbSOC = new System.Windows.Forms.GroupBox();
            this.m_rbHardwareTrigerr = new System.Windows.Forms.RadioButton();
            this.rbSoftwareTrigerr = new System.Windows.Forms.RadioButton();
            this.rbFreeRunning = new System.Windows.Forms.RadioButton();
            this.cbReference = new System.Windows.Forms.ComboBox();
            this.cbInputRange = new System.Windows.Forms.ComboBox();
            this.gbInput = new System.Windows.Forms.GroupBox();
            this.numRefVoltage = new System.Windows.Forms.NumericUpDown();
            this.External_Ref_label = new System.Windows.Forms.Label();
            this.Reference_label = new System.Windows.Forms.Label();
            this.ADC_Input_Range_label = new System.Windows.Forms.Label();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.chbNextOut = new System.Windows.Forms.CheckBox();
            this.lblNoFreq = new System.Windows.Forms.Label();
            this.tbClockFreq = new System.Windows.Forms.TextBox();
            this.Clock_label = new System.Windows.Forms.Label();
            this.gbModes.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSampleRate)).BeginInit();
            this.m_gbClockSource.SuspendLayout();
            this.m_gbSOC.SuspendLayout();
            this.gbInput.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numRefVoltage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // gbModes
            // 
            this.gbModes.Controls.Add(this.lblNoFreq);
            this.gbModes.Controls.Add(this.tbClockFreq);
            this.gbModes.Controls.Add(this.Clock_label);
            this.gbModes.Controls.Add(this.lblActualClockFrequency);
            this.gbModes.Controls.Add(this.lblActualFrequencyLabel);
            this.gbModes.Controls.Add(this.lblActualConversionRate);
            this.gbModes.Controls.Add(this.lblConversionRateLabel);
            this.gbModes.Controls.Add(this.lblNoRate);
            this.gbModes.Controls.Add(this.numSampleRate);
            this.gbModes.Controls.Add(this.Convertsion_label);
            this.gbModes.Controls.Add(this.cbResolution);
            this.gbModes.Controls.Add(this.ADC_Resolution_label);
            this.gbModes.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbModes.Location = new System.Drawing.Point(13, 3);
            this.gbModes.Name = "gbModes";
            this.gbModes.Size = new System.Drawing.Size(276, 159);
            this.gbModes.TabIndex = 0;
            this.gbModes.TabStop = false;
            this.gbModes.Text = "Modes";
            // 
            // lblActualClockFrequency
            // 
            this.lblActualClockFrequency.AutoSize = true;
            this.lblActualClockFrequency.Location = new System.Drawing.Point(162, 134);
            this.lblActualClockFrequency.Name = "lblActualClockFrequency";
            this.lblActualClockFrequency.Size = new System.Drawing.Size(97, 13);
            this.lblActualClockFrequency.TabIndex = 21;
            this.lblActualClockFrequency.Text = "UNKNOWN FREQ";
            // 
            // lblActualFrequencyLabel
            // 
            this.lblActualFrequencyLabel.AutoSize = true;
            this.lblActualFrequencyLabel.Location = new System.Drawing.Point(6, 134);
            this.lblActualFrequencyLabel.Name = "lblActualFrequencyLabel";
            this.lblActualFrequencyLabel.Size = new System.Drawing.Size(147, 13);
            this.lblActualFrequencyLabel.TabIndex = 20;
            this.lblActualFrequencyLabel.Text = "Actual clock frequency (kHz):";
            // 
            // lblActualConversionRate
            // 
            this.lblActualConversionRate.AutoSize = true;
            this.lblActualConversionRate.Location = new System.Drawing.Point(162, 106);
            this.lblActualConversionRate.Name = "lblActualConversionRate";
            this.lblActualConversionRate.Size = new System.Drawing.Size(97, 13);
            this.lblActualConversionRate.TabIndex = 19;
            this.lblActualConversionRate.Text = "UNKNOWN RATE";
            // 
            // lblConversionRateLabel
            // 
            this.lblConversionRateLabel.AutoSize = true;
            this.lblConversionRateLabel.Location = new System.Drawing.Point(6, 106);
            this.lblConversionRateLabel.Name = "lblConversionRateLabel";
            this.lblConversionRateLabel.Size = new System.Drawing.Size(146, 13);
            this.lblConversionRateLabel.TabIndex = 18;
            this.lblConversionRateLabel.Text = "Actual conversion rate (SPS):";
            // 
            // lblNoRate
            // 
            this.lblNoRate.AutoSize = true;
            this.lblNoRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblNoRate.Location = new System.Drawing.Point(162, 50);
            this.lblNoRate.Name = "lblNoRate";
            this.lblNoRate.Size = new System.Drawing.Size(97, 13);
            this.lblNoRate.TabIndex = 17;
            this.lblNoRate.Text = "UNKNOWN RATE";
            // 
            // numSampleRate
            // 
            this.numSampleRate.Location = new System.Drawing.Point(163, 47);
            this.numSampleRate.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numSampleRate.Name = "numSampleRate";
            this.numSampleRate.Size = new System.Drawing.Size(85, 20);
            this.numSampleRate.TabIndex = 2;
            this.numSampleRate.Value = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            // 
            // Convertsion_label
            // 
            this.Convertsion_label.AutoSize = true;
            this.Convertsion_label.Location = new System.Drawing.Point(6, 50);
            this.Convertsion_label.Name = "Convertsion_label";
            this.Convertsion_label.Size = new System.Drawing.Size(114, 13);
            this.Convertsion_label.TabIndex = 12;
            this.Convertsion_label.Text = "Conversion rate (SPS):";
            // 
            // cbResolution
            // 
            this.cbResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbResolution.FormattingEnabled = true;
            this.cbResolution.Location = new System.Drawing.Point(164, 19);
            this.cbResolution.Name = "cbResolution";
            this.cbResolution.Size = new System.Drawing.Size(86, 21);
            this.cbResolution.TabIndex = 1;
            this.cbResolution.SelectedIndexChanged += new System.EventHandler(this.cbResolution_SelectedIndexChanged);
            // 
            // ADC_Resolution_label
            // 
            this.ADC_Resolution_label.AutoSize = true;
            this.ADC_Resolution_label.Location = new System.Drawing.Point(6, 22);
            this.ADC_Resolution_label.Name = "ADC_Resolution_label";
            this.ADC_Resolution_label.Size = new System.Drawing.Size(85, 13);
            this.ADC_Resolution_label.TabIndex = 7;
            this.ADC_Resolution_label.Text = "Resolution (bits):";
            // 
            // m_gbClockSource
            // 
            this.m_gbClockSource.Controls.Add(this.rbExternal);
            this.m_gbClockSource.Controls.Add(this.rbInternal);
            this.m_gbClockSource.ForeColor = System.Drawing.SystemColors.ControlText;
            this.m_gbClockSource.Location = new System.Drawing.Point(295, 98);
            this.m_gbClockSource.Name = "m_gbClockSource";
            this.m_gbClockSource.Size = new System.Drawing.Size(120, 64);
            this.m_gbClockSource.TabIndex = 3;
            this.m_gbClockSource.TabStop = false;
            this.m_gbClockSource.Text = "Clock source";
            // 
            // rbExternal
            // 
            this.rbExternal.AutoSize = true;
            this.rbExternal.Location = new System.Drawing.Point(6, 42);
            this.rbExternal.Name = "rbExternal";
            this.rbExternal.Size = new System.Drawing.Size(63, 17);
            this.rbExternal.TabIndex = 1;
            this.rbExternal.Text = "External";
            this.rbExternal.UseVisualStyleBackColor = true;
            // 
            // rbInternal
            // 
            this.rbInternal.AutoSize = true;
            this.rbInternal.Location = new System.Drawing.Point(6, 19);
            this.rbInternal.Name = "rbInternal";
            this.rbInternal.Size = new System.Drawing.Size(60, 17);
            this.rbInternal.TabIndex = 0;
            this.rbInternal.Text = "Internal";
            this.rbInternal.UseVisualStyleBackColor = true;
            this.rbInternal.CheckedChanged += new System.EventHandler(this.rbInternal_CheckedChanged);
            // 
            // m_gbSOC
            // 
            this.m_gbSOC.Controls.Add(this.m_rbHardwareTrigerr);
            this.m_gbSOC.Controls.Add(this.rbSoftwareTrigerr);
            this.m_gbSOC.Controls.Add(this.rbFreeRunning);
            this.m_gbSOC.ForeColor = System.Drawing.SystemColors.ControlText;
            this.m_gbSOC.Location = new System.Drawing.Point(295, 3);
            this.m_gbSOC.Name = "m_gbSOC";
            this.m_gbSOC.Size = new System.Drawing.Size(120, 89);
            this.m_gbSOC.TabIndex = 2;
            this.m_gbSOC.TabStop = false;
            this.m_gbSOC.Text = "Sample mode";
            // 
            // m_rbHardwareTrigerr
            // 
            this.m_rbHardwareTrigerr.AutoSize = true;
            this.m_rbHardwareTrigerr.Location = new System.Drawing.Point(6, 65);
            this.m_rbHardwareTrigerr.Name = "m_rbHardwareTrigerr";
            this.m_rbHardwareTrigerr.Size = new System.Drawing.Size(103, 17);
            this.m_rbHardwareTrigerr.TabIndex = 2;
            this.m_rbHardwareTrigerr.TabStop = true;
            this.m_rbHardwareTrigerr.Text = "Hardware trigger";
            this.m_rbHardwareTrigerr.UseVisualStyleBackColor = true;
            this.m_rbHardwareTrigerr.CheckedChanged += new System.EventHandler(this.rbSampleMode_CheckedChanged);
            // 
            // rbSoftwareTrigerr
            // 
            this.rbSoftwareTrigerr.AutoSize = true;
            this.rbSoftwareTrigerr.Location = new System.Drawing.Point(6, 42);
            this.rbSoftwareTrigerr.Name = "rbSoftwareTrigerr";
            this.rbSoftwareTrigerr.Size = new System.Drawing.Size(99, 17);
            this.rbSoftwareTrigerr.TabIndex = 1;
            this.rbSoftwareTrigerr.Text = "Software trigger";
            this.rbSoftwareTrigerr.UseVisualStyleBackColor = true;
            this.rbSoftwareTrigerr.CheckedChanged += new System.EventHandler(this.rbSampleMode_CheckedChanged);
            // 
            // rbFreeRunning
            // 
            this.rbFreeRunning.AutoSize = true;
            this.rbFreeRunning.Location = new System.Drawing.Point(6, 19);
            this.rbFreeRunning.Name = "rbFreeRunning";
            this.rbFreeRunning.Size = new System.Drawing.Size(84, 17);
            this.rbFreeRunning.TabIndex = 0;
            this.rbFreeRunning.Text = "Free running";
            this.rbFreeRunning.UseVisualStyleBackColor = true;
            this.rbFreeRunning.CheckedChanged += new System.EventHandler(this.rbSampleMode_CheckedChanged);
            // 
            // cbReference
            // 
            this.cbReference.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbReference.FormattingEnabled = true;
            this.cbReference.Location = new System.Drawing.Point(122, 46);
            this.cbReference.Name = "cbReference";
            this.cbReference.Size = new System.Drawing.Size(262, 21);
            this.cbReference.TabIndex = 1;
            this.cbReference.SelectedIndexChanged += new System.EventHandler(this.cbReference_SelectedIndexChanged);
            // 
            // cbInputRange
            // 
            this.cbInputRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbInputRange.FormattingEnabled = true;
            this.cbInputRange.Location = new System.Drawing.Point(122, 19);
            this.cbInputRange.Name = "cbInputRange";
            this.cbInputRange.Size = new System.Drawing.Size(262, 21);
            this.cbInputRange.TabIndex = 0;
            this.cbInputRange.SelectedIndexChanged += new System.EventHandler(this.cbInputRange_SelectedIndexChanged);
            // 
            // gbInput
            // 
            this.gbInput.Controls.Add(this.numRefVoltage);
            this.gbInput.Controls.Add(this.External_Ref_label);
            this.gbInput.Controls.Add(this.cbReference);
            this.gbInput.Controls.Add(this.cbInputRange);
            this.gbInput.Controls.Add(this.Reference_label);
            this.gbInput.Controls.Add(this.ADC_Input_Range_label);
            this.gbInput.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbInput.Location = new System.Drawing.Point(13, 168);
            this.gbInput.Name = "gbInput";
            this.gbInput.Size = new System.Drawing.Size(402, 106);
            this.gbInput.TabIndex = 4;
            this.gbInput.TabStop = false;
            this.gbInput.Text = "Input";
            // 
            // numRefVoltage
            // 
            this.numRefVoltage.DecimalPlaces = 4;
            this.numRefVoltage.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numRefVoltage.Location = new System.Drawing.Point(122, 73);
            this.numRefVoltage.Maximum = new decimal(new int[] {
            1500,
            0,
            0,
            196608});
            this.numRefVoltage.Name = "numRefVoltage";
            this.numRefVoltage.Size = new System.Drawing.Size(84, 20);
            this.numRefVoltage.TabIndex = 2;
            this.numRefVoltage.Value = new decimal(new int[] {
            1024,
            0,
            0,
            196608});
            // 
            // External_Ref_label
            // 
            this.External_Ref_label.AutoSize = true;
            this.External_Ref_label.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.External_Ref_label.Location = new System.Drawing.Point(6, 75);
            this.External_Ref_label.Name = "External_Ref_label";
            this.External_Ref_label.Size = new System.Drawing.Size(110, 13);
            this.External_Ref_label.TabIndex = 14;
            this.External_Ref_label.Text = "Voltage reference (V):";
            // 
            // Reference_label
            // 
            this.Reference_label.AutoSize = true;
            this.Reference_label.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.Reference_label.Location = new System.Drawing.Point(6, 49);
            this.Reference_label.Name = "Reference_label";
            this.Reference_label.Size = new System.Drawing.Size(60, 13);
            this.Reference_label.TabIndex = 4;
            this.Reference_label.Text = "Reference:";
            // 
            // ADC_Input_Range_label
            // 
            this.ADC_Input_Range_label.AutoSize = true;
            this.ADC_Input_Range_label.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.ADC_Input_Range_label.Location = new System.Drawing.Point(6, 22);
            this.ADC_Input_Range_label.Name = "ADC_Input_Range_label";
            this.ADC_Input_Range_label.Size = new System.Drawing.Size(64, 13);
            this.ADC_Input_Range_label.TabIndex = 9;
            this.ADC_Input_Range_label.Text = "Input range:";
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // chbNextOut
            // 
            this.chbNextOut.AutoSize = true;
            this.chbNextOut.Location = new System.Drawing.Point(22, 280);
            this.chbNextOut.Name = "chbNextOut";
            this.chbNextOut.Size = new System.Drawing.Size(117, 17);
            this.chbNextOut.TabIndex = 5;
            this.chbNextOut.Text = "Enable EOS output";
            this.chbNextOut.UseVisualStyleBackColor = true;
            this.chbNextOut.CheckedChanged += new System.EventHandler(this.chbNextOut_CheckedChanged);
            // 
            // lblNoFreq
            // 
            this.lblNoFreq.AutoSize = true;
            this.lblNoFreq.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblNoFreq.Location = new System.Drawing.Point(162, 78);
            this.lblNoFreq.Name = "lblNoFreq";
            this.lblNoFreq.Size = new System.Drawing.Size(97, 13);
            this.lblNoFreq.TabIndex = 24;
            this.lblNoFreq.Text = "UNKNOWN FREQ";
            // 
            // tbClockFreq
            // 
            this.tbClockFreq.Location = new System.Drawing.Point(165, 75);
            this.tbClockFreq.Name = "tbClockFreq";
            this.tbClockFreq.ReadOnly = true;
            this.tbClockFreq.Size = new System.Drawing.Size(85, 20);
            this.tbClockFreq.TabIndex = 22;
            this.tbClockFreq.TabStop = false;
            this.tbClockFreq.Visible = false;
            // 
            // Clock_label
            // 
            this.Clock_label.AutoSize = true;
            this.Clock_label.Location = new System.Drawing.Point(6, 78);
            this.Clock_label.Name = "Clock_label";
            this.Clock_label.Size = new System.Drawing.Size(115, 13);
            this.Clock_label.TabIndex = 23;
            this.Clock_label.Text = "Clock frequency (kHz):";
            // 
            // CyConfigureTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.chbNextOut);
            this.Controls.Add(this.gbInput);
            this.Controls.Add(this.m_gbSOC);
            this.Controls.Add(this.m_gbClockSource);
            this.Controls.Add(this.gbModes);
            this.Name = "CyConfigureTab";
            this.Size = new System.Drawing.Size(485, 318);
            this.Load += new System.EventHandler(this.CyConfigureTab_Load);
            this.gbModes.ResumeLayout(false);
            this.gbModes.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSampleRate)).EndInit();
            this.m_gbClockSource.ResumeLayout(false);
            this.m_gbClockSource.PerformLayout();
            this.m_gbSOC.ResumeLayout(false);
            this.m_gbSOC.PerformLayout();
            this.gbInput.ResumeLayout(false);
            this.gbInput.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numRefVoltage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbModes;
        private System.Windows.Forms.Label ADC_Resolution_label;
        private System.Windows.Forms.ComboBox cbResolution;
        private System.Windows.Forms.GroupBox m_gbClockSource;
        private System.Windows.Forms.RadioButton rbExternal;
        private System.Windows.Forms.RadioButton rbInternal;
        private System.Windows.Forms.GroupBox m_gbSOC;
        private System.Windows.Forms.RadioButton rbFreeRunning;
        private System.Windows.Forms.RadioButton rbSoftwareTrigerr;
        private System.Windows.Forms.Label Convertsion_label;
        private System.Windows.Forms.ComboBox cbReference;
        private System.Windows.Forms.ComboBox cbInputRange;
        private System.Windows.Forms.GroupBox gbInput;
        private System.Windows.Forms.Label External_Ref_label;
        private System.Windows.Forms.Label Reference_label;
        private System.Windows.Forms.Label ADC_Input_Range_label;
        private System.Windows.Forms.NumericUpDown numSampleRate;
        private System.Windows.Forms.NumericUpDown numRefVoltage;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Label lblNoRate;
        private System.Windows.Forms.CheckBox chbNextOut;
        private System.Windows.Forms.Label lblActualConversionRate;
        private System.Windows.Forms.Label lblConversionRateLabel;
        private System.Windows.Forms.RadioButton m_rbHardwareTrigerr;
        private System.Windows.Forms.Label lblActualClockFrequency;
        private System.Windows.Forms.Label lblActualFrequencyLabel;
        private System.Windows.Forms.Label lblNoFreq;
        private System.Windows.Forms.TextBox tbClockFreq;
        private System.Windows.Forms.Label Clock_label;
    }
}
