namespace DVDAC_v2_10
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyConfigureTab));
            this.gbValue = new System.Windows.Forms.GroupBox();
            this.labelNote = new System.Windows.Forms.Label();
            this.numHexValue = new System.Windows.Forms.NumericUpDown();
            this.numVoltageValue = new System.Windows.Forms.NumericUpDown();
            this.lblHex = new System.Windows.Forms.Label();
            this.lblmV = new System.Windows.Forms.Label();
            this.gbResolution = new System.Windows.Forms.GroupBox();
            this.rb12Bit = new System.Windows.Forms.RadioButton();
            this.rb11Bit = new System.Windows.Forms.RadioButton();
            this.rb10Bit = new System.Windows.Forms.RadioButton();
            this.rb9Bit = new System.Windows.Forms.RadioButton();
            this.gbRange = new System.Windows.Forms.GroupBox();
            this.rb4VRange = new System.Windows.Forms.RadioButton();
            this.rb1VRange = new System.Windows.Forms.RadioButton();
            this.labelCapacity = new System.Windows.Forms.Label();
            this.pbSymbol = new System.Windows.Forms.PictureBox();
            this.labelClock = new System.Windows.Forms.Label();
            this.numClock = new System.Windows.Forms.NumericUpDown();
            this.labelC = new System.Windows.Forms.Label();
            this.gbClockSource = new System.Windows.Forms.GroupBox();
            this.lblUnknownFreq = new System.Windows.Forms.Label();
            this.rbExternal = new System.Windows.Forms.RadioButton();
            this.rbInternal = new System.Windows.Forms.RadioButton();
            this.warningProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.gbPicture = new System.Windows.Forms.GroupBox();
            this.gbValue.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numHexValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numVoltageValue)).BeginInit();
            this.gbResolution.SuspendLayout();
            this.gbRange.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numClock)).BeginInit();
            this.gbClockSource.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.warningProvider)).BeginInit();
            this.gbPicture.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbValue
            // 
            this.gbValue.Controls.Add(this.labelNote);
            this.gbValue.Controls.Add(this.numHexValue);
            this.gbValue.Controls.Add(this.numVoltageValue);
            this.gbValue.Controls.Add(this.lblHex);
            this.gbValue.Controls.Add(this.lblmV);
            this.gbValue.Location = new System.Drawing.Point(3, 147);
            this.gbValue.Name = "gbValue";
            this.gbValue.Size = new System.Drawing.Size(174, 112);
            this.gbValue.TabIndex = 2;
            this.gbValue.TabStop = false;
            this.gbValue.Text = "Initial value";
            // 
            // labelNote
            // 
            this.labelNote.AutoSize = true;
            this.labelNote.Location = new System.Drawing.Point(3, 76);
            this.labelNote.Name = "labelNote";
            this.labelNote.Size = new System.Drawing.Size(152, 26);
            this.labelNote.TabIndex = 4;
            this.labelNote.Text = "Note: Changing any value field\r\nrecalculates the other.";
            // 
            // numHexValue
            // 
            this.numHexValue.Hexadecimal = true;
            this.numHexValue.Location = new System.Drawing.Point(59, 45);
            this.numHexValue.Maximum = new decimal(new int[] {
            251,
            0,
            0,
            0});
            this.numHexValue.Name = "numHexValue";
            this.numHexValue.Size = new System.Drawing.Size(81, 20);
            this.numHexValue.TabIndex = 1;
            // 
            // numVoltageValue
            // 
            this.numVoltageValue.Increment = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numVoltageValue.Location = new System.Drawing.Point(59, 19);
            this.numVoltageValue.Maximum = new decimal(new int[] {
            1020,
            0,
            0,
            0});
            this.numVoltageValue.Name = "numVoltageValue";
            this.numVoltageValue.Size = new System.Drawing.Size(81, 20);
            this.numVoltageValue.TabIndex = 0;
            this.numVoltageValue.ValueChanged += new System.EventHandler(this.numVoltageValue_ValueChanged);
            // 
            // lblHex
            // 
            this.lblHex.AutoSize = true;
            this.lblHex.Location = new System.Drawing.Point(6, 47);
            this.lblHex.Name = "lblHex";
            this.lblHex.Size = new System.Drawing.Size(29, 13);
            this.lblHex.TabIndex = 1;
            this.lblHex.Text = "Hex:";
            // 
            // lblmV
            // 
            this.lblmV.AutoSize = true;
            this.lblmV.Location = new System.Drawing.Point(6, 21);
            this.lblmV.Name = "lblmV";
            this.lblmV.Size = new System.Drawing.Size(25, 13);
            this.lblmV.TabIndex = 0;
            this.lblmV.Text = "mV:";
            // 
            // gbResolution
            // 
            this.gbResolution.Controls.Add(this.rb12Bit);
            this.gbResolution.Controls.Add(this.rb11Bit);
            this.gbResolution.Controls.Add(this.rb10Bit);
            this.gbResolution.Controls.Add(this.rb9Bit);
            this.gbResolution.Location = new System.Drawing.Point(3, 75);
            this.gbResolution.Name = "gbResolution";
            this.gbResolution.Size = new System.Drawing.Size(174, 66);
            this.gbResolution.TabIndex = 1;
            this.gbResolution.TabStop = false;
            this.gbResolution.Text = "Resolution";
            // 
            // rb12Bit
            // 
            this.rb12Bit.AutoSize = true;
            this.rb12Bit.Location = new System.Drawing.Point(89, 42);
            this.rb12Bit.Name = "rb12Bit";
            this.rb12Bit.Size = new System.Drawing.Size(51, 17);
            this.rb12Bit.TabIndex = 3;
            this.rb12Bit.TabStop = true;
            this.rb12Bit.Text = "12-bit";
            this.rb12Bit.UseVisualStyleBackColor = true;
            this.rb12Bit.CheckedChanged += new System.EventHandler(this.rbResolution_CheckedChanged);
            // 
            // rb11Bit
            // 
            this.rb11Bit.AutoSize = true;
            this.rb11Bit.Location = new System.Drawing.Point(89, 19);
            this.rb11Bit.Name = "rb11Bit";
            this.rb11Bit.Size = new System.Drawing.Size(51, 17);
            this.rb11Bit.TabIndex = 2;
            this.rb11Bit.TabStop = true;
            this.rb11Bit.Text = "11-bit";
            this.rb11Bit.UseVisualStyleBackColor = true;
            this.rb11Bit.CheckedChanged += new System.EventHandler(this.rbResolution_CheckedChanged);
            // 
            // rb10Bit
            // 
            this.rb10Bit.AutoSize = true;
            this.rb10Bit.Location = new System.Drawing.Point(6, 42);
            this.rb10Bit.Name = "rb10Bit";
            this.rb10Bit.Size = new System.Drawing.Size(51, 17);
            this.rb10Bit.TabIndex = 1;
            this.rb10Bit.TabStop = true;
            this.rb10Bit.Text = "10-bit";
            this.rb10Bit.UseVisualStyleBackColor = true;
            this.rb10Bit.CheckedChanged += new System.EventHandler(this.rbResolution_CheckedChanged);
            // 
            // rb9Bit
            // 
            this.rb9Bit.AutoSize = true;
            this.rb9Bit.Location = new System.Drawing.Point(6, 19);
            this.rb9Bit.Name = "rb9Bit";
            this.rb9Bit.Size = new System.Drawing.Size(45, 17);
            this.rb9Bit.TabIndex = 0;
            this.rb9Bit.TabStop = true;
            this.rb9Bit.Text = "9-bit";
            this.rb9Bit.UseVisualStyleBackColor = true;
            this.rb9Bit.CheckedChanged += new System.EventHandler(this.rbResolution_CheckedChanged);
            // 
            // gbRange
            // 
            this.gbRange.Controls.Add(this.rb4VRange);
            this.gbRange.Controls.Add(this.rb1VRange);
            this.gbRange.Location = new System.Drawing.Point(3, 3);
            this.gbRange.Name = "gbRange";
            this.gbRange.Size = new System.Drawing.Size(174, 66);
            this.gbRange.TabIndex = 0;
            this.gbRange.TabStop = false;
            this.gbRange.Text = "Voltage range";
            // 
            // rb4VRange
            // 
            this.rb4VRange.AutoSize = true;
            this.rb4VRange.Location = new System.Drawing.Point(6, 42);
            this.rb4VRange.Name = "rb4VRange";
            this.rb4VRange.Size = new System.Drawing.Size(132, 17);
            this.rb4VRange.TabIndex = 1;
            this.rb4VRange.TabStop = true;
            this.rb4VRange.Text = "0 - 4.080 V (16 mV/bit)";
            this.rb4VRange.UseVisualStyleBackColor = true;
            this.rb4VRange.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // rb1VRange
            // 
            this.rb1VRange.AutoSize = true;
            this.rb1VRange.Location = new System.Drawing.Point(6, 19);
            this.rb1VRange.Name = "rb1VRange";
            this.rb1VRange.Size = new System.Drawing.Size(126, 17);
            this.rb1VRange.TabIndex = 0;
            this.rb1VRange.TabStop = true;
            this.rb1VRange.Text = "0 - 1.020 V (4 mV/bit)";
            this.rb1VRange.UseVisualStyleBackColor = true;
            this.rb1VRange.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // labelCapacity
            // 
            this.labelCapacity.AutoSize = true;
            this.labelCapacity.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.labelCapacity.Location = new System.Drawing.Point(146, 105);
            this.labelCapacity.Name = "labelCapacity";
            this.labelCapacity.Size = new System.Drawing.Size(28, 13);
            this.labelCapacity.TabIndex = 3;
            this.labelCapacity.Text = "0 pF";
            // 
            // pbSymbol
            // 
            this.pbSymbol.Location = new System.Drawing.Point(13, 17);
            this.pbSymbol.Name = "pbSymbol";
            this.pbSymbol.Size = new System.Drawing.Size(180, 137);
            this.pbSymbol.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbSymbol.TabIndex = 4;
            this.pbSymbol.TabStop = false;
            // 
            // labelClock
            // 
            this.labelClock.AutoSize = true;
            this.labelClock.Location = new System.Drawing.Point(3, 68);
            this.labelClock.Name = "labelClock";
            this.labelClock.Size = new System.Drawing.Size(115, 13);
            this.labelClock.TabIndex = 5;
            this.labelClock.Text = "Clock frequency (kHz):";
            // 
            // numClock
            // 
            this.numClock.DecimalPlaces = 3;
            this.numClock.Location = new System.Drawing.Point(124, 66);
            this.numClock.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numClock.Name = "numClock";
            this.numClock.Size = new System.Drawing.Size(81, 20);
            this.numClock.TabIndex = 3;
            this.numClock.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            // 
            // labelC
            // 
            this.labelC.AutoSize = true;
            this.labelC.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.labelC.Location = new System.Drawing.Point(151, 90);
            this.labelC.Name = "labelC";
            this.labelC.Size = new System.Drawing.Size(14, 13);
            this.labelC.TabIndex = 6;
            this.labelC.Text = "C";
            // 
            // gbClockSource
            // 
            this.gbClockSource.Controls.Add(this.lblUnknownFreq);
            this.gbClockSource.Controls.Add(this.rbExternal);
            this.gbClockSource.Controls.Add(this.rbInternal);
            this.gbClockSource.Controls.Add(this.numClock);
            this.gbClockSource.Controls.Add(this.labelClock);
            this.gbClockSource.Location = new System.Drawing.Point(196, 3);
            this.gbClockSource.Name = "gbClockSource";
            this.gbClockSource.Size = new System.Drawing.Size(230, 91);
            this.gbClockSource.TabIndex = 7;
            this.gbClockSource.TabStop = false;
            this.gbClockSource.Text = "Timing";
            // 
            // lblUnknownFreq
            // 
            this.lblUnknownFreq.AutoSize = true;
            this.lblUnknownFreq.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblUnknownFreq.Location = new System.Drawing.Point(124, 68);
            this.lblUnknownFreq.Name = "lblUnknownFreq";
            this.lblUnknownFreq.Size = new System.Drawing.Size(65, 13);
            this.lblUnknownFreq.TabIndex = 16;
            this.lblUnknownFreq.Text = "UNKNOWN";
            // 
            // rbExternal
            // 
            this.rbExternal.AutoSize = true;
            this.rbExternal.Location = new System.Drawing.Point(6, 42);
            this.rbExternal.Name = "rbExternal";
            this.rbExternal.Size = new System.Drawing.Size(92, 17);
            this.rbExternal.TabIndex = 1;
            this.rbExternal.TabStop = true;
            this.rbExternal.Text = "External clock";
            this.rbExternal.UseVisualStyleBackColor = true;
            this.rbExternal.CheckedChanged += new System.EventHandler(this.rbClockSource_CheckedChanged);
            // 
            // rbInternal
            // 
            this.rbInternal.AutoSize = true;
            this.rbInternal.Location = new System.Drawing.Point(6, 19);
            this.rbInternal.Name = "rbInternal";
            this.rbInternal.Size = new System.Drawing.Size(89, 17);
            this.rbInternal.TabIndex = 0;
            this.rbInternal.TabStop = true;
            this.rbInternal.Text = "Internal clock";
            this.rbInternal.UseVisualStyleBackColor = true;
            this.rbInternal.CheckedChanged += new System.EventHandler(this.rbClockSource_CheckedChanged);
            // 
            // warningProvider
            // 
            this.warningProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.warningProvider.ContainerControl = this;
            this.warningProvider.Icon = ((System.Drawing.Icon)(resources.GetObject("warningProvider.Icon")));
            // 
            // gbPicture
            // 
            this.gbPicture.Controls.Add(this.labelCapacity);
            this.gbPicture.Controls.Add(this.labelC);
            this.gbPicture.Controls.Add(this.pbSymbol);
            this.gbPicture.Location = new System.Drawing.Point(196, 100);
            this.gbPicture.Name = "gbPicture";
            this.gbPicture.Size = new System.Drawing.Size(230, 159);
            this.gbPicture.TabIndex = 8;
            this.gbPicture.TabStop = false;
            this.gbPicture.Text = "Recommended external capacitor";
            // 
            // CyConfigureTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.gbPicture);
            this.Controls.Add(this.gbClockSource);
            this.Controls.Add(this.gbRange);
            this.Controls.Add(this.gbResolution);
            this.Controls.Add(this.gbValue);
            this.Name = "CyConfigureTab";
            this.Size = new System.Drawing.Size(436, 287);
            this.Load += new System.EventHandler(this.CyConfigureTab_Load);
            this.gbValue.ResumeLayout(false);
            this.gbValue.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numHexValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numVoltageValue)).EndInit();
            this.gbResolution.ResumeLayout(false);
            this.gbResolution.PerformLayout();
            this.gbRange.ResumeLayout(false);
            this.gbRange.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numClock)).EndInit();
            this.gbClockSource.ResumeLayout(false);
            this.gbClockSource.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.warningProvider)).EndInit();
            this.gbPicture.ResumeLayout(false);
            this.gbPicture.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbValue;
        private System.Windows.Forms.Label labelNote;
        private System.Windows.Forms.NumericUpDown numHexValue;
        private System.Windows.Forms.NumericUpDown numVoltageValue;
        private System.Windows.Forms.Label lblHex;
        private System.Windows.Forms.Label lblmV;
        private System.Windows.Forms.GroupBox gbResolution;
        private System.Windows.Forms.RadioButton rb10Bit;
        private System.Windows.Forms.RadioButton rb9Bit;
        private System.Windows.Forms.GroupBox gbRange;
        private System.Windows.Forms.RadioButton rb4VRange;
        private System.Windows.Forms.RadioButton rb1VRange;
        private System.Windows.Forms.RadioButton rb12Bit;
        private System.Windows.Forms.RadioButton rb11Bit;
        private System.Windows.Forms.Label labelCapacity;
        private System.Windows.Forms.PictureBox pbSymbol;
        private System.Windows.Forms.Label labelClock;
        private System.Windows.Forms.NumericUpDown numClock;
        private System.Windows.Forms.Label labelC;
        private System.Windows.Forms.GroupBox gbClockSource;
        private System.Windows.Forms.RadioButton rbExternal;
        private System.Windows.Forms.RadioButton rbInternal;
        private System.Windows.Forms.Label lblUnknownFreq;
        private System.Windows.Forms.ErrorProvider warningProvider;
        private System.Windows.Forms.GroupBox gbPicture;
    }
}
