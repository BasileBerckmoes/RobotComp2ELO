namespace IDAC_P4_v1_10
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
            this.gbPolarity = new System.Windows.Forms.GroupBox();
            this.rbNegative = new System.Windows.Forms.RadioButton();
            this.rbPositive = new System.Windows.Forms.RadioButton();
            this.gbValue = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.numConvertedValue = new System.Windows.Forms.NumericUpDown();
            this.numCurrentValue = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.gbResolution = new System.Windows.Forms.GroupBox();
            this.rb7Bit = new System.Windows.Forms.RadioButton();
            this.rb8Bit = new System.Windows.Forms.RadioButton();
            this.gbRange = new System.Windows.Forms.GroupBox();
            this.rbHighRange = new System.Windows.Forms.RadioButton();
            this.rbLowRange = new System.Windows.Forms.RadioButton();
            this.gbPolarity.SuspendLayout();
            this.gbValue.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numConvertedValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCurrentValue)).BeginInit();
            this.gbResolution.SuspendLayout();
            this.gbRange.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbPolarity
            // 
            this.gbPolarity.Controls.Add(this.rbNegative);
            this.gbPolarity.Controls.Add(this.rbPositive);
            this.gbPolarity.Location = new System.Drawing.Point(3, 3);
            this.gbPolarity.Name = "gbPolarity";
            this.gbPolarity.Size = new System.Drawing.Size(174, 72);
            this.gbPolarity.TabIndex = 0;
            this.gbPolarity.TabStop = false;
            this.gbPolarity.Text = "Polarity";
            // 
            // rbNegative
            // 
            this.rbNegative.AutoSize = true;
            this.rbNegative.Location = new System.Drawing.Point(6, 42);
            this.rbNegative.Name = "rbNegative";
            this.rbNegative.Size = new System.Drawing.Size(98, 17);
            this.rbNegative.TabIndex = 1;
            this.rbNegative.TabStop = true;
            this.rbNegative.Text = "Negative (Sink)";
            this.rbNegative.UseVisualStyleBackColor = true;
            // 
            // rbPositive
            // 
            this.rbPositive.AutoSize = true;
            this.rbPositive.Location = new System.Drawing.Point(6, 19);
            this.rbPositive.Name = "rbPositive";
            this.rbPositive.Size = new System.Drawing.Size(105, 17);
            this.rbPositive.TabIndex = 0;
            this.rbPositive.TabStop = true;
            this.rbPositive.Text = "Positive (Source)";
            this.rbPositive.UseVisualStyleBackColor = true;
            this.rbPositive.CheckedChanged += new System.EventHandler(this.rbPositive_CheckedChanged);
            // 
            // gbValue
            // 
            this.gbValue.Controls.Add(this.label3);
            this.gbValue.Controls.Add(this.numConvertedValue);
            this.gbValue.Controls.Add(this.numCurrentValue);
            this.gbValue.Controls.Add(this.label2);
            this.gbValue.Controls.Add(this.label1);
            this.gbValue.Location = new System.Drawing.Point(3, 81);
            this.gbValue.Name = "gbValue";
            this.gbValue.Size = new System.Drawing.Size(174, 109);
            this.gbValue.TabIndex = 1;
            this.gbValue.TabStop = false;
            this.gbValue.Text = "Value";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(139, 26);
            this.label3.TabIndex = 4;
            this.label3.Text = "Note: changing any value\r\n field recalculates the others";
            // 
            // numConvertedValue
            // 
            this.numConvertedValue.Hexadecimal = true;
            this.numConvertedValue.Location = new System.Drawing.Point(59, 45);
            this.numConvertedValue.Maximum = new decimal(new int[] {
            251,
            0,
            0,
            0});
            this.numConvertedValue.Name = "numConvertedValue";
            this.numConvertedValue.Size = new System.Drawing.Size(81, 20);
            this.numConvertedValue.TabIndex = 3;
            // 
            // numCurrentValue
            // 
            this.numCurrentValue.DecimalPlaces = 1;
            this.numCurrentValue.Increment = new decimal(new int[] {
            24,
            0,
            0,
            65536});
            this.numCurrentValue.Location = new System.Drawing.Point(59, 19);
            this.numCurrentValue.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numCurrentValue.Name = "numCurrentValue";
            this.numCurrentValue.Size = new System.Drawing.Size(81, 20);
            this.numCurrentValue.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "8 bit hex:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "uA:";
            // 
            // gbResolution
            // 
            this.gbResolution.Controls.Add(this.rb7Bit);
            this.gbResolution.Controls.Add(this.rb8Bit);
            this.gbResolution.Location = new System.Drawing.Point(183, 3);
            this.gbResolution.Name = "gbResolution";
            this.gbResolution.Size = new System.Drawing.Size(200, 72);
            this.gbResolution.TabIndex = 2;
            this.gbResolution.TabStop = false;
            this.gbResolution.Text = "Resolution";
            // 
            // rb7Bit
            // 
            this.rb7Bit.AutoSize = true;
            this.rb7Bit.Location = new System.Drawing.Point(6, 42);
            this.rb7Bit.Name = "rb7Bit";
            this.rb7Bit.Size = new System.Drawing.Size(45, 17);
            this.rb7Bit.TabIndex = 1;
            this.rb7Bit.TabStop = true;
            this.rb7Bit.Text = "7-bit";
            this.rb7Bit.UseVisualStyleBackColor = true;
            // 
            // rb8Bit
            // 
            this.rb8Bit.AutoSize = true;
            this.rb8Bit.Location = new System.Drawing.Point(6, 19);
            this.rb8Bit.Name = "rb8Bit";
            this.rb8Bit.Size = new System.Drawing.Size(45, 17);
            this.rb8Bit.TabIndex = 0;
            this.rb8Bit.TabStop = true;
            this.rb8Bit.Text = "8-bit";
            this.rb8Bit.UseVisualStyleBackColor = true;
            this.rb8Bit.CheckedChanged += new System.EventHandler(this.rb8Bit_CheckedChanged);
            // 
            // gbRange
            // 
            this.gbRange.Controls.Add(this.rbHighRange);
            this.gbRange.Controls.Add(this.rbLowRange);
            this.gbRange.Location = new System.Drawing.Point(183, 81);
            this.gbRange.Name = "gbRange";
            this.gbRange.Size = new System.Drawing.Size(200, 72);
            this.gbRange.TabIndex = 3;
            this.gbRange.TabStop = false;
            this.gbRange.Text = "Range";
            // 
            // rbHighRange
            // 
            this.rbHighRange.AutoSize = true;
            this.rbHighRange.Location = new System.Drawing.Point(6, 42);
            this.rbHighRange.Name = "rbHighRange";
            this.rbHighRange.Size = new System.Drawing.Size(124, 17);
            this.rbHighRange.TabIndex = 1;
            this.rbHighRange.TabStop = true;
            this.rbHighRange.Text = "0-600 uA (2.4 uA/bit)";
            this.rbHighRange.UseVisualStyleBackColor = true;
            // 
            // rbLowRange
            // 
            this.rbLowRange.AutoSize = true;
            this.rbLowRange.Location = new System.Drawing.Point(6, 19);
            this.rbLowRange.Name = "rbLowRange";
            this.rbLowRange.Size = new System.Drawing.Size(124, 17);
            this.rbLowRange.TabIndex = 0;
            this.rbLowRange.TabStop = true;
            this.rbLowRange.Text = "0-300 uA (1.2 uA/bit)";
            this.rbLowRange.UseVisualStyleBackColor = true;
            this.rbLowRange.CheckedChanged += new System.EventHandler(this.rbLowRange_CheckedChanged);
            // 
            // CyConfigureTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.gbRange);
            this.Controls.Add(this.gbResolution);
            this.Controls.Add(this.gbValue);
            this.Controls.Add(this.gbPolarity);
            this.Name = "CyConfigureTab";
            this.Size = new System.Drawing.Size(466, 284);
            this.gbPolarity.ResumeLayout(false);
            this.gbPolarity.PerformLayout();
            this.gbValue.ResumeLayout(false);
            this.gbValue.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numConvertedValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCurrentValue)).EndInit();
            this.gbResolution.ResumeLayout(false);
            this.gbResolution.PerformLayout();
            this.gbRange.ResumeLayout(false);
            this.gbRange.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbPolarity;
        private System.Windows.Forms.RadioButton rbNegative;
        private System.Windows.Forms.RadioButton rbPositive;
        private System.Windows.Forms.GroupBox gbValue;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numConvertedValue;
        private System.Windows.Forms.NumericUpDown numCurrentValue;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox gbResolution;
        private System.Windows.Forms.RadioButton rb7Bit;
        private System.Windows.Forms.RadioButton rb8Bit;
        private System.Windows.Forms.GroupBox gbRange;
        private System.Windows.Forms.RadioButton rbHighRange;
        private System.Windows.Forms.RadioButton rbLowRange;
    }
}
