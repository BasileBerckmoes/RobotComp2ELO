namespace ScanComp_v1_10
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
            this.components = new System.ComponentModel.Container();
            this.rbInternal = new System.Windows.Forms.RadioButton();
            this.rbExternal = new System.Windows.Forms.RadioButton();
            this.gbClockSource = new System.Windows.Forms.GroupBox();
            this.gbScanTiming = new System.Windows.Forms.GroupBox();
            this.numClockFreq = new System.Windows.Forms.NumericUpDown();
            this.numScanRate = new System.Windows.Forms.NumericUpDown();
            this.rbScanRate = new System.Windows.Forms.RadioButton();
            this.rbClockFreq = new System.Windows.Forms.RadioButton();
            this.chbHwOutEnabled = new System.Windows.Forms.CheckBox();
            this.gbNegativeInput = new System.Windows.Forms.GroupBox();
            this.rbInternalVdac = new System.Windows.Forms.RadioButton();
            this.rbCommon = new System.Windows.Forms.RadioButton();
            this.rbUnique = new System.Windows.Forms.RadioButton();
            this.gbVdacVoltage = new System.Windows.Forms.GroupBox();
            this.numVdacVoltage = new ScanComp_v1_10.CyNumericUpDown();
            this.rbPerChannel = new System.Windows.Forms.RadioButton();
            this.rbFixed = new System.Windows.Forms.RadioButton();
            this.gbVdacRange = new System.Windows.Forms.GroupBox();
            this.rbRange4_80V = new System.Windows.Forms.RadioButton();
            this.rbRange1_20V = new System.Windows.Forms.RadioButton();
            this.epExtClock = new System.Windows.Forms.ErrorProvider(this.components);
            this.gbClockSource.SuspendLayout();
            this.gbScanTiming.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numClockFreq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numScanRate)).BeginInit();
            this.gbNegativeInput.SuspendLayout();
            this.gbVdacVoltage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numVdacVoltage)).BeginInit();
            this.gbVdacRange.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.epExtClock)).BeginInit();
            this.SuspendLayout();
            // 
            // rbInternal
            // 
            this.rbInternal.AutoSize = true;
            this.rbInternal.Location = new System.Drawing.Point(9, 19);
            this.rbInternal.Name = "rbInternal";
            this.rbInternal.Size = new System.Drawing.Size(60, 17);
            this.rbInternal.TabIndex = 0;
            this.rbInternal.TabStop = true;
            this.rbInternal.Text = "Internal";
            this.rbInternal.UseVisualStyleBackColor = true;
            this.rbInternal.CheckedChanged += new System.EventHandler(this.rbClockSource_CheckedChanged);
            // 
            // rbExternal
            // 
            this.rbExternal.AutoSize = true;
            this.rbExternal.Location = new System.Drawing.Point(9, 42);
            this.rbExternal.Name = "rbExternal";
            this.rbExternal.Size = new System.Drawing.Size(63, 17);
            this.rbExternal.TabIndex = 1;
            this.rbExternal.TabStop = true;
            this.rbExternal.Text = "External";
            this.rbExternal.UseVisualStyleBackColor = true;
            this.rbExternal.CheckedChanged += new System.EventHandler(this.rbClockSource_CheckedChanged);
            // 
            // gbClockSource
            // 
            this.gbClockSource.Controls.Add(this.rbInternal);
            this.gbClockSource.Controls.Add(this.rbExternal);
            this.gbClockSource.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbClockSource.Location = new System.Drawing.Point(3, 3);
            this.gbClockSource.Name = "gbClockSource";
            this.gbClockSource.Size = new System.Drawing.Size(242, 70);
            this.gbClockSource.TabIndex = 0;
            this.gbClockSource.TabStop = false;
            this.gbClockSource.Text = "Clock source";
            // 
            // gbScanTiming
            // 
            this.gbScanTiming.Controls.Add(this.numClockFreq);
            this.gbScanTiming.Controls.Add(this.numScanRate);
            this.gbScanTiming.Controls.Add(this.rbScanRate);
            this.gbScanTiming.Controls.Add(this.rbClockFreq);
            this.gbScanTiming.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbScanTiming.Location = new System.Drawing.Point(3, 79);
            this.gbScanTiming.Name = "gbScanTiming";
            this.gbScanTiming.Size = new System.Drawing.Size(242, 73);
            this.gbScanTiming.TabIndex = 1;
            this.gbScanTiming.TabStop = false;
            this.gbScanTiming.Text = "Scan timing";
            // 
            // numClockFreq
            // 
            this.numClockFreq.DecimalPlaces = 3;
            this.numClockFreq.Location = new System.Drawing.Point(148, 42);
            this.numClockFreq.Name = "numClockFreq";
            this.numClockFreq.Size = new System.Drawing.Size(77, 20);
            this.numClockFreq.TabIndex = 3;
            // 
            // numScanRate
            // 
            this.numScanRate.DecimalPlaces = 3;
            this.numScanRate.Location = new System.Drawing.Point(148, 19);
            this.numScanRate.Name = "numScanRate";
            this.numScanRate.Size = new System.Drawing.Size(77, 20);
            this.numScanRate.TabIndex = 2;
            // 
            // rbScanRate
            // 
            this.rbScanRate.AutoSize = true;
            this.rbScanRate.Location = new System.Drawing.Point(9, 19);
            this.rbScanRate.Name = "rbScanRate";
            this.rbScanRate.Size = new System.Drawing.Size(102, 17);
            this.rbScanRate.TabIndex = 0;
            this.rbScanRate.TabStop = true;
            this.rbScanRate.Text = "Scan rate (kHz):";
            this.rbScanRate.UseVisualStyleBackColor = true;
            this.rbScanRate.CheckedChanged += new System.EventHandler(this.rbTiming_CheckedChanged);
            // 
            // rbClockFreq
            // 
            this.rbClockFreq.AutoSize = true;
            this.rbClockFreq.Location = new System.Drawing.Point(9, 42);
            this.rbClockFreq.Name = "rbClockFreq";
            this.rbClockFreq.Size = new System.Drawing.Size(133, 17);
            this.rbClockFreq.TabIndex = 1;
            this.rbClockFreq.TabStop = true;
            this.rbClockFreq.Text = "Clock frequency (kHz):";
            this.rbClockFreq.UseVisualStyleBackColor = true;
            this.rbClockFreq.CheckedChanged += new System.EventHandler(this.rbTiming_CheckedChanged);
            // 
            // chbHwOutEnabled
            // 
            this.chbHwOutEnabled.AutoSize = true;
            this.chbHwOutEnabled.Location = new System.Drawing.Point(251, 158);
            this.chbHwOutEnabled.Name = "chbHwOutEnabled";
            this.chbHwOutEnabled.Size = new System.Drawing.Size(151, 17);
            this.chbHwOutEnabled.TabIndex = 5;
            this.chbHwOutEnabled.Text = "Hardware outputs enabled";
            this.chbHwOutEnabled.UseVisualStyleBackColor = true;
            this.chbHwOutEnabled.CheckedChanged += new System.EventHandler(this.chbHwOutEnabled_CheckedChanged);
            // 
            // gbNegativeInput
            // 
            this.gbNegativeInput.Controls.Add(this.rbInternalVdac);
            this.gbNegativeInput.Controls.Add(this.rbCommon);
            this.gbNegativeInput.Controls.Add(this.rbUnique);
            this.gbNegativeInput.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbNegativeInput.Location = new System.Drawing.Point(3, 158);
            this.gbNegativeInput.Name = "gbNegativeInput";
            this.gbNegativeInput.Size = new System.Drawing.Size(242, 94);
            this.gbNegativeInput.TabIndex = 2;
            this.gbNegativeInput.TabStop = false;
            this.gbNegativeInput.Text = "Negative input";
            // 
            // rbInternalVdac
            // 
            this.rbInternalVdac.AutoSize = true;
            this.rbInternalVdac.Location = new System.Drawing.Point(8, 66);
            this.rbInternalVdac.Name = "rbInternalVdac";
            this.rbInternalVdac.Size = new System.Drawing.Size(92, 17);
            this.rbInternalVdac.TabIndex = 2;
            this.rbInternalVdac.TabStop = true;
            this.rbInternalVdac.Text = "Internal VDAC";
            this.rbInternalVdac.UseVisualStyleBackColor = true;
            this.rbInternalVdac.CheckedChanged += new System.EventHandler(this.rbNegativeInput_CheckedChanged);
            // 
            // rbCommon
            // 
            this.rbCommon.AutoSize = true;
            this.rbCommon.Location = new System.Drawing.Point(8, 43);
            this.rbCommon.Name = "rbCommon";
            this.rbCommon.Size = new System.Drawing.Size(66, 17);
            this.rbCommon.TabIndex = 1;
            this.rbCommon.TabStop = true;
            this.rbCommon.Text = "Common";
            this.rbCommon.UseVisualStyleBackColor = true;
            this.rbCommon.CheckedChanged += new System.EventHandler(this.rbNegativeInput_CheckedChanged);
            // 
            // rbUnique
            // 
            this.rbUnique.AutoSize = true;
            this.rbUnique.Location = new System.Drawing.Point(8, 20);
            this.rbUnique.Name = "rbUnique";
            this.rbUnique.Size = new System.Drawing.Size(59, 17);
            this.rbUnique.TabIndex = 0;
            this.rbUnique.TabStop = true;
            this.rbUnique.Text = "Unique";
            this.rbUnique.UseVisualStyleBackColor = true;
            this.rbUnique.CheckedChanged += new System.EventHandler(this.rbNegativeInput_CheckedChanged);
            // 
            // gbVdacVoltage
            // 
            this.gbVdacVoltage.Controls.Add(this.numVdacVoltage);
            this.gbVdacVoltage.Controls.Add(this.rbPerChannel);
            this.gbVdacVoltage.Controls.Add(this.rbFixed);
            this.gbVdacVoltage.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbVdacVoltage.Location = new System.Drawing.Point(251, 79);
            this.gbVdacVoltage.Name = "gbVdacVoltage";
            this.gbVdacVoltage.Size = new System.Drawing.Size(196, 73);
            this.gbVdacVoltage.TabIndex = 4;
            this.gbVdacVoltage.TabStop = false;
            this.gbVdacVoltage.Text = "VDAC voltage";
            // 
            // numVdacVoltage
            // 
            this.numVdacVoltage.Location = new System.Drawing.Point(89, 19);
            this.numVdacVoltage.Name = "numVdacVoltage";
            this.numVdacVoltage.Size = new System.Drawing.Size(60, 20);
            this.numVdacVoltage.TabIndex = 6;
            this.numVdacVoltage.UpButtonClicked += new System.EventHandler(this.numVdacVoltage_UpButtonClicked);
            this.numVdacVoltage.DownButtonClicked += new System.EventHandler(this.numVdacVoltage_DownButtonClicked);
            // 
            // rbPerChannel
            // 
            this.rbPerChannel.AutoSize = true;
            this.rbPerChannel.Location = new System.Drawing.Point(6, 42);
            this.rbPerChannel.Name = "rbPerChannel";
            this.rbPerChannel.Size = new System.Drawing.Size(82, 17);
            this.rbPerChannel.TabIndex = 1;
            this.rbPerChannel.TabStop = true;
            this.rbPerChannel.Text = "Per channel";
            this.rbPerChannel.UseVisualStyleBackColor = true;
            this.rbPerChannel.CheckedChanged += new System.EventHandler(this.rbVdacVoltageMode_CheckedChanged);
            // 
            // rbFixed
            // 
            this.rbFixed.AutoSize = true;
            this.rbFixed.Location = new System.Drawing.Point(6, 19);
            this.rbFixed.Name = "rbFixed";
            this.rbFixed.Size = new System.Drawing.Size(77, 17);
            this.rbFixed.TabIndex = 0;
            this.rbFixed.TabStop = true;
            this.rbFixed.Text = "Fixed (mV):";
            this.rbFixed.UseVisualStyleBackColor = true;
            this.rbFixed.CheckedChanged += new System.EventHandler(this.rbVdacVoltageMode_CheckedChanged);
            // 
            // gbVdacRange
            // 
            this.gbVdacRange.Controls.Add(this.rbRange4_80V);
            this.gbVdacRange.Controls.Add(this.rbRange1_20V);
            this.gbVdacRange.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbVdacRange.Location = new System.Drawing.Point(251, 3);
            this.gbVdacRange.Name = "gbVdacRange";
            this.gbVdacRange.Size = new System.Drawing.Size(196, 70);
            this.gbVdacRange.TabIndex = 3;
            this.gbVdacRange.TabStop = false;
            this.gbVdacRange.Text = "VDAC range";
            // 
            // rbRange4_80V
            // 
            this.rbRange4_80V.AutoSize = true;
            this.rbRange4_80V.Location = new System.Drawing.Point(6, 42);
            this.rbRange4_80V.Name = "rbRange4_80V";
            this.rbRange4_80V.Size = new System.Drawing.Size(132, 17);
            this.rbRange4_80V.TabIndex = 1;
            this.rbRange4_80V.TabStop = true;
            this.rbRange4_80V.Text = "0 - 4.080 V (16 mV/bit)";
            this.rbRange4_80V.UseVisualStyleBackColor = true;
            this.rbRange4_80V.CheckedChanged += new System.EventHandler(this.rbVdacRange_CheckedChanged);
            // 
            // rbRange1_20V
            // 
            this.rbRange1_20V.AutoSize = true;
            this.rbRange1_20V.Location = new System.Drawing.Point(6, 19);
            this.rbRange1_20V.Name = "rbRange1_20V";
            this.rbRange1_20V.Size = new System.Drawing.Size(126, 17);
            this.rbRange1_20V.TabIndex = 0;
            this.rbRange1_20V.TabStop = true;
            this.rbRange1_20V.Text = "0 - 1.020 V (4 mV/bit)";
            this.rbRange1_20V.UseVisualStyleBackColor = true;
            this.rbRange1_20V.CheckedChanged += new System.EventHandler(this.rbVdacRange_CheckedChanged);
            // 
            // epExtClock
            // 
            this.epExtClock.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.epExtClock.ContainerControl = this;
            // 
            // CyGeneralTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.gbVdacVoltage);
            this.Controls.Add(this.gbVdacRange);
            this.Controls.Add(this.gbNegativeInput);
            this.Controls.Add(this.chbHwOutEnabled);
            this.Controls.Add(this.gbScanTiming);
            this.Controls.Add(this.gbClockSource);
            this.Name = "CyGeneralTab";
            this.Size = new System.Drawing.Size(454, 261);
            this.VisibleChanged += new System.EventHandler(this.CyGeneralTab_VisibleChanged);
            this.gbClockSource.ResumeLayout(false);
            this.gbClockSource.PerformLayout();
            this.gbScanTiming.ResumeLayout(false);
            this.gbScanTiming.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numClockFreq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numScanRate)).EndInit();
            this.gbNegativeInput.ResumeLayout(false);
            this.gbNegativeInput.PerformLayout();
            this.gbVdacVoltage.ResumeLayout(false);
            this.gbVdacVoltage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numVdacVoltage)).EndInit();
            this.gbVdacRange.ResumeLayout(false);
            this.gbVdacRange.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.epExtClock)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbInternal;
        private System.Windows.Forms.RadioButton rbExternal;
        private System.Windows.Forms.GroupBox gbClockSource;
        private System.Windows.Forms.GroupBox gbScanTiming;
        private System.Windows.Forms.RadioButton rbScanRate;
        private System.Windows.Forms.RadioButton rbClockFreq;
        private System.Windows.Forms.CheckBox chbHwOutEnabled;
        private System.Windows.Forms.NumericUpDown numClockFreq;
        private System.Windows.Forms.NumericUpDown numScanRate;
        private System.Windows.Forms.GroupBox gbNegativeInput;
        private System.Windows.Forms.RadioButton rbInternalVdac;
        private System.Windows.Forms.RadioButton rbCommon;
        private System.Windows.Forms.RadioButton rbUnique;
        private System.Windows.Forms.GroupBox gbVdacVoltage;
        private System.Windows.Forms.RadioButton rbPerChannel;
        private System.Windows.Forms.RadioButton rbFixed;
        private System.Windows.Forms.GroupBox gbVdacRange;
        private System.Windows.Forms.RadioButton rbRange4_80V;
        private System.Windows.Forms.RadioButton rbRange1_20V;
        private CyNumericUpDown numVdacVoltage;
        private System.Windows.Forms.ErrorProvider epExtClock;
    }
}
