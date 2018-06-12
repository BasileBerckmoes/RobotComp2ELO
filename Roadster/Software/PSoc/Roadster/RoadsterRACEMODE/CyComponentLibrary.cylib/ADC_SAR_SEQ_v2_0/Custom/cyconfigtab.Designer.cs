namespace ADC_SAR_SEQ_v2_0
{
    partial class CyConfigTab
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
            this.m_grpTiming = new System.Windows.Forms.GroupBox();
            this.m_lblUnknownFreq = new System.Windows.Forms.Label();
            this.m_lblActualSampleRate = new System.Windows.Forms.Label();
            this.m_rbClockFreq = new System.Windows.Forms.RadioButton();
            this.m_lblUnknownRate = new System.Windows.Forms.Label();
            this.m_rbSampleRate = new System.Windows.Forms.RadioButton();
            this.m_numClockFreq = new System.Windows.Forms.NumericUpDown();
            this.m_numSampleRate = new System.Windows.Forms.NumericUpDown();
            this.m_cbResolution = new System.Windows.Forms.ComboBox();
            this.m_lblResolution = new System.Windows.Forms.Label();
            this.m_grpInput = new System.Windows.Forms.GroupBox();
            this.m_numChannels = new System.Windows.Forms.NumericUpDown();
            this.m_numVrefValue = new System.Windows.Forms.NumericUpDown();
            this.m_cbReference = new System.Windows.Forms.ComboBox();
            this.m_cbInputRange = new System.Windows.Forms.ComboBox();
            this.m_lblChannelsSampleRate = new System.Windows.Forms.Label();
            this.m_lblChannels = new System.Windows.Forms.Label();
            this.m_lblVref = new System.Windows.Forms.Label();
            this.m_lblReference = new System.Windows.Forms.Label();
            this.m_lblInputRange = new System.Windows.Forms.Label();
            this.m_grpSampleMode = new System.Windows.Forms.GroupBox();
            this.m_rbHardwareTrigger = new System.Windows.Forms.RadioButton();
            this.m_rbSoftwareTrigger = new System.Windows.Forms.RadioButton();
            this.m_rbFreeRunning = new System.Windows.Forms.RadioButton();
            this.m_grpClockSrc = new System.Windows.Forms.GroupBox();
            this.m_rbExternal = new System.Windows.Forms.RadioButton();
            this.m_rbInternal = new System.Windows.Forms.RadioButton();
            this.m_grpTiming.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClockFreq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numSampleRate)).BeginInit();
            this.m_grpInput.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numChannels)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numVrefValue)).BeginInit();
            this.m_grpSampleMode.SuspendLayout();
            this.m_grpClockSrc.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_grpTiming
            // 
            this.m_grpTiming.Controls.Add(this.m_lblUnknownFreq);
            this.m_grpTiming.Controls.Add(this.m_lblActualSampleRate);
            this.m_grpTiming.Controls.Add(this.m_rbClockFreq);
            this.m_grpTiming.Controls.Add(this.m_lblUnknownRate);
            this.m_grpTiming.Controls.Add(this.m_rbSampleRate);
            this.m_grpTiming.Controls.Add(this.m_numClockFreq);
            this.m_grpTiming.Controls.Add(this.m_numSampleRate);
            this.m_grpTiming.Controls.Add(this.m_cbResolution);
            this.m_grpTiming.Controls.Add(this.m_lblResolution);
            this.m_grpTiming.Location = new System.Drawing.Point(3, 3);
            this.m_grpTiming.Name = "m_grpTiming";
            this.m_grpTiming.Size = new System.Drawing.Size(331, 98);
            this.m_grpTiming.TabIndex = 0;
            this.m_grpTiming.TabStop = false;
            this.m_grpTiming.Text = "Timing";
            // 
            // m_lblUnknownFreq
            // 
            this.m_lblUnknownFreq.AutoSize = true;
            this.m_lblUnknownFreq.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownFreq.Location = new System.Drawing.Point(137, 74);
            this.m_lblUnknownFreq.Name = "m_lblUnknownFreq";
            this.m_lblUnknownFreq.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownFreq.TabIndex = 5;
            this.m_lblUnknownFreq.Text = "UNKNOWN FREQ";
            // 
            // m_lblActualSampleRate
            // 
            this.m_lblActualSampleRate.AutoSize = true;
            this.m_lblActualSampleRate.Location = new System.Drawing.Point(223, 48);
            this.m_lblActualSampleRate.Name = "m_lblActualSampleRate";
            this.m_lblActualSampleRate.Size = new System.Drawing.Size(97, 13);
            this.m_lblActualSampleRate.TabIndex = 4;
            this.m_lblActualSampleRate.Text = "Actual sample rate:";
            // 
            // m_rbClockFreq
            // 
            this.m_rbClockFreq.AutoSize = true;
            this.m_rbClockFreq.Location = new System.Drawing.Point(6, 72);
            this.m_rbClockFreq.Name = "m_rbClockFreq";
            this.m_rbClockFreq.Size = new System.Drawing.Size(133, 17);
            this.m_rbClockFreq.TabIndex = 7;
            this.m_rbClockFreq.TabStop = true;
            this.m_rbClockFreq.Text = "Clock frequency (kHz):";
            this.m_rbClockFreq.UseVisualStyleBackColor = true;
            // 
            // m_lblUnknownRate
            // 
            this.m_lblUnknownRate.AutoSize = true;
            this.m_lblUnknownRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownRate.Location = new System.Drawing.Point(137, 48);
            this.m_lblUnknownRate.Name = "m_lblUnknownRate";
            this.m_lblUnknownRate.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownRate.TabIndex = 4;
            this.m_lblUnknownRate.Text = "UNKNOWN RATE";
            // 
            // m_rbSampleRate
            // 
            this.m_rbSampleRate.AutoSize = true;
            this.m_rbSampleRate.Location = new System.Drawing.Point(6, 46);
            this.m_rbSampleRate.Name = "m_rbSampleRate";
            this.m_rbSampleRate.Size = new System.Drawing.Size(114, 17);
            this.m_rbSampleRate.TabIndex = 6;
            this.m_rbSampleRate.TabStop = true;
            this.m_rbSampleRate.Text = "Sample rate (SPS):";
            this.m_rbSampleRate.UseVisualStyleBackColor = true;
            // 
            // m_numClockFreq
            // 
            this.m_numClockFreq.Location = new System.Drawing.Point(145, 72);
            this.m_numClockFreq.Name = "m_numClockFreq";
            this.m_numClockFreq.Size = new System.Drawing.Size(71, 20);
            this.m_numClockFreq.TabIndex = 4;
            // 
            // m_numSampleRate
            // 
            this.m_numSampleRate.Location = new System.Drawing.Point(145, 46);
            this.m_numSampleRate.Name = "m_numSampleRate";
            this.m_numSampleRate.Size = new System.Drawing.Size(71, 20);
            this.m_numSampleRate.TabIndex = 2;
            // 
            // m_cbResolution
            // 
            this.m_cbResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbResolution.FormattingEnabled = true;
            this.m_cbResolution.Location = new System.Drawing.Point(145, 19);
            this.m_cbResolution.Name = "m_cbResolution";
            this.m_cbResolution.Size = new System.Drawing.Size(72, 21);
            this.m_cbResolution.TabIndex = 1;
            // 
            // m_lblResolution
            // 
            this.m_lblResolution.AutoSize = true;
            this.m_lblResolution.Location = new System.Drawing.Point(6, 22);
            this.m_lblResolution.Name = "m_lblResolution";
            this.m_lblResolution.Size = new System.Drawing.Size(85, 13);
            this.m_lblResolution.TabIndex = 0;
            this.m_lblResolution.Text = "Resolution (bits):";
            // 
            // m_grpInput
            // 
            this.m_grpInput.Controls.Add(this.m_numChannels);
            this.m_grpInput.Controls.Add(this.m_numVrefValue);
            this.m_grpInput.Controls.Add(this.m_cbReference);
            this.m_grpInput.Controls.Add(this.m_cbInputRange);
            this.m_grpInput.Controls.Add(this.m_lblChannelsSampleRate);
            this.m_grpInput.Controls.Add(this.m_lblChannels);
            this.m_grpInput.Controls.Add(this.m_lblVref);
            this.m_grpInput.Controls.Add(this.m_lblReference);
            this.m_grpInput.Controls.Add(this.m_lblInputRange);
            this.m_grpInput.Location = new System.Drawing.Point(3, 107);
            this.m_grpInput.Name = "m_grpInput";
            this.m_grpInput.Size = new System.Drawing.Size(331, 125);
            this.m_grpInput.TabIndex = 1;
            this.m_grpInput.TabStop = false;
            this.m_grpInput.Text = "Input";
            // 
            // m_numChannels
            // 
            this.m_numChannels.Location = new System.Drawing.Point(86, 99);
            this.m_numChannels.Name = "m_numChannels";
            this.m_numChannels.Size = new System.Drawing.Size(53, 20);
            this.m_numChannels.TabIndex = 8;
            // 
            // m_numVrefValue
            // 
            this.m_numVrefValue.Location = new System.Drawing.Point(86, 73);
            this.m_numVrefValue.Name = "m_numVrefValue";
            this.m_numVrefValue.Size = new System.Drawing.Size(62, 20);
            this.m_numVrefValue.TabIndex = 7;
            // 
            // m_cbReference
            // 
            this.m_cbReference.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbReference.FormattingEnabled = true;
            this.m_cbReference.Location = new System.Drawing.Point(86, 46);
            this.m_cbReference.Name = "m_cbReference";
            this.m_cbReference.Size = new System.Drawing.Size(167, 21);
            this.m_cbReference.TabIndex = 6;
            // 
            // m_cbInputRange
            // 
            this.m_cbInputRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbInputRange.FormattingEnabled = true;
            this.m_cbInputRange.Location = new System.Drawing.Point(86, 19);
            this.m_cbInputRange.Name = "m_cbInputRange";
            this.m_cbInputRange.Size = new System.Drawing.Size(240, 21);
            this.m_cbInputRange.TabIndex = 5;
            // 
            // m_lblChannelsSampleRate
            // 
            this.m_lblChannelsSampleRate.AutoSize = true;
            this.m_lblChannelsSampleRate.Location = new System.Drawing.Point(145, 101);
            this.m_lblChannelsSampleRate.Name = "m_lblChannelsSampleRate";
            this.m_lblChannelsSampleRate.Size = new System.Drawing.Size(136, 13);
            this.m_lblChannelsSampleRate.TabIndex = 4;
            this.m_lblChannelsSampleRate.Text = "Channel sample rate (SPS):";
            // 
            // m_lblChannels
            // 
            this.m_lblChannels.AutoSize = true;
            this.m_lblChannels.Location = new System.Drawing.Point(6, 101);
            this.m_lblChannels.Name = "m_lblChannels";
            this.m_lblChannels.Size = new System.Drawing.Size(54, 13);
            this.m_lblChannels.TabIndex = 3;
            this.m_lblChannels.Text = "Channels:";
            // 
            // m_lblVref
            // 
            this.m_lblVref.AutoSize = true;
            this.m_lblVref.Location = new System.Drawing.Point(6, 75);
            this.m_lblVref.Name = "m_lblVref";
            this.m_lblVref.Size = new System.Drawing.Size(74, 13);
            this.m_lblVref.TabIndex = 2;
            this.m_lblVref.Text = "Vref value (V):";
            // 
            // m_lblReference
            // 
            this.m_lblReference.AutoSize = true;
            this.m_lblReference.Location = new System.Drawing.Point(6, 49);
            this.m_lblReference.Name = "m_lblReference";
            this.m_lblReference.Size = new System.Drawing.Size(60, 13);
            this.m_lblReference.TabIndex = 1;
            this.m_lblReference.Text = "Reference:";
            // 
            // m_lblInputRange
            // 
            this.m_lblInputRange.AutoSize = true;
            this.m_lblInputRange.Location = new System.Drawing.Point(6, 22);
            this.m_lblInputRange.Name = "m_lblInputRange";
            this.m_lblInputRange.Size = new System.Drawing.Size(64, 13);
            this.m_lblInputRange.TabIndex = 0;
            this.m_lblInputRange.Text = "Input range:";
            // 
            // m_grpSampleMode
            // 
            this.m_grpSampleMode.Controls.Add(this.m_rbHardwareTrigger);
            this.m_grpSampleMode.Controls.Add(this.m_rbSoftwareTrigger);
            this.m_grpSampleMode.Controls.Add(this.m_rbFreeRunning);
            this.m_grpSampleMode.Location = new System.Drawing.Point(340, 3);
            this.m_grpSampleMode.Name = "m_grpSampleMode";
            this.m_grpSampleMode.Size = new System.Drawing.Size(110, 98);
            this.m_grpSampleMode.TabIndex = 2;
            this.m_grpSampleMode.TabStop = false;
            this.m_grpSampleMode.Text = "Sample mode";
            // 
            // m_rbHardwareTrigger
            // 
            this.m_rbHardwareTrigger.AutoSize = true;
            this.m_rbHardwareTrigger.Location = new System.Drawing.Point(6, 64);
            this.m_rbHardwareTrigger.Name = "m_rbHardwareTrigger";
            this.m_rbHardwareTrigger.Size = new System.Drawing.Size(103, 17);
            this.m_rbHardwareTrigger.TabIndex = 2;
            this.m_rbHardwareTrigger.TabStop = true;
            this.m_rbHardwareTrigger.Text = "Hardware trigger";
            this.m_rbHardwareTrigger.UseVisualStyleBackColor = true;
            // 
            // m_rbSoftwareTrigger
            // 
            this.m_rbSoftwareTrigger.AutoSize = true;
            this.m_rbSoftwareTrigger.Location = new System.Drawing.Point(6, 41);
            this.m_rbSoftwareTrigger.Name = "m_rbSoftwareTrigger";
            this.m_rbSoftwareTrigger.Size = new System.Drawing.Size(99, 17);
            this.m_rbSoftwareTrigger.TabIndex = 1;
            this.m_rbSoftwareTrigger.TabStop = true;
            this.m_rbSoftwareTrigger.Text = "Software trigger";
            this.m_rbSoftwareTrigger.UseVisualStyleBackColor = true;
            // 
            // m_rbFreeRunning
            // 
            this.m_rbFreeRunning.AutoSize = true;
            this.m_rbFreeRunning.Location = new System.Drawing.Point(6, 18);
            this.m_rbFreeRunning.Name = "m_rbFreeRunning";
            this.m_rbFreeRunning.Size = new System.Drawing.Size(84, 17);
            this.m_rbFreeRunning.TabIndex = 0;
            this.m_rbFreeRunning.TabStop = true;
            this.m_rbFreeRunning.Text = "Free running";
            this.m_rbFreeRunning.UseVisualStyleBackColor = true;
            // 
            // m_grpClockSrc
            // 
            this.m_grpClockSrc.Controls.Add(this.m_rbExternal);
            this.m_grpClockSrc.Controls.Add(this.m_rbInternal);
            this.m_grpClockSrc.Location = new System.Drawing.Point(339, 107);
            this.m_grpClockSrc.Name = "m_grpClockSrc";
            this.m_grpClockSrc.Size = new System.Drawing.Size(111, 67);
            this.m_grpClockSrc.TabIndex = 3;
            this.m_grpClockSrc.TabStop = false;
            this.m_grpClockSrc.Text = "Clock source";
            // 
            // m_rbExternal
            // 
            this.m_rbExternal.AutoSize = true;
            this.m_rbExternal.Location = new System.Drawing.Point(6, 42);
            this.m_rbExternal.Name = "m_rbExternal";
            this.m_rbExternal.Size = new System.Drawing.Size(63, 17);
            this.m_rbExternal.TabIndex = 1;
            this.m_rbExternal.TabStop = true;
            this.m_rbExternal.Text = "External";
            this.m_rbExternal.UseVisualStyleBackColor = true;
            // 
            // m_rbInternal
            // 
            this.m_rbInternal.AutoSize = true;
            this.m_rbInternal.Location = new System.Drawing.Point(6, 19);
            this.m_rbInternal.Name = "m_rbInternal";
            this.m_rbInternal.Size = new System.Drawing.Size(60, 17);
            this.m_rbInternal.TabIndex = 0;
            this.m_rbInternal.TabStop = true;
            this.m_rbInternal.Text = "Internal";
            this.m_rbInternal.UseVisualStyleBackColor = true;
            // 
            // CyConfigTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_grpClockSrc);
            this.Controls.Add(this.m_grpSampleMode);
            this.Controls.Add(this.m_grpInput);
            this.Controls.Add(this.m_grpTiming);
            this.Name = "CyConfigTab";
            this.Size = new System.Drawing.Size(458, 234);
            this.m_grpTiming.ResumeLayout(false);
            this.m_grpTiming.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClockFreq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numSampleRate)).EndInit();
            this.m_grpInput.ResumeLayout(false);
            this.m_grpInput.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numChannels)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numVrefValue)).EndInit();
            this.m_grpSampleMode.ResumeLayout(false);
            this.m_grpSampleMode.PerformLayout();
            this.m_grpClockSrc.ResumeLayout(false);
            this.m_grpClockSrc.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_grpTiming;
        private System.Windows.Forms.ComboBox m_cbResolution;
        private System.Windows.Forms.Label m_lblResolution;
        private System.Windows.Forms.RadioButton m_rbClockFreq;
        private System.Windows.Forms.RadioButton m_rbSampleRate;
        private System.Windows.Forms.NumericUpDown m_numClockFreq;
        private System.Windows.Forms.NumericUpDown m_numSampleRate;
        private System.Windows.Forms.GroupBox m_grpInput;
        private System.Windows.Forms.ComboBox m_cbInputRange;
        private System.Windows.Forms.Label m_lblChannelsSampleRate;
        private System.Windows.Forms.Label m_lblChannels;
        private System.Windows.Forms.Label m_lblVref;
        private System.Windows.Forms.Label m_lblReference;
        private System.Windows.Forms.Label m_lblInputRange;
        private System.Windows.Forms.ComboBox m_cbReference;
        private System.Windows.Forms.NumericUpDown m_numVrefValue;
        private System.Windows.Forms.NumericUpDown m_numChannels;
        private System.Windows.Forms.GroupBox m_grpSampleMode;
        private System.Windows.Forms.RadioButton m_rbSoftwareTrigger;
        private System.Windows.Forms.RadioButton m_rbFreeRunning;
        private System.Windows.Forms.GroupBox m_grpClockSrc;
        private System.Windows.Forms.RadioButton m_rbExternal;
        private System.Windows.Forms.RadioButton m_rbInternal;
        private System.Windows.Forms.Label m_lblUnknownFreq;
        private System.Windows.Forms.Label m_lblUnknownRate;
        private System.Windows.Forms.Label m_lblActualSampleRate;
        private System.Windows.Forms.RadioButton m_rbHardwareTrigger;
    }
}
