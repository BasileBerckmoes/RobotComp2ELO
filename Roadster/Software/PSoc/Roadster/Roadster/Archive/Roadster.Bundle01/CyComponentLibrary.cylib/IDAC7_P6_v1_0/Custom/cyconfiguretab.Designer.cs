namespace IDAC7_P6_v1_0
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyConfigureTab));
            this.gbPolarity = new System.Windows.Forms.GroupBox();
            this.rbNegative = new System.Windows.Forms.RadioButton();
            this.rbPositive = new System.Windows.Forms.RadioButton();
            this.gbValue = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.numConvertedValue = new System.Windows.Forms.NumericUpDown();
            this.numCurrentValue = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.gbRange = new System.Windows.Forms.GroupBox();
            this.rbRange_635_0 = new System.Windows.Forms.RadioButton();
            this.rbRange_317_5 = new System.Windows.Forms.RadioButton();
            this.rbRange_79_38 = new System.Windows.Forms.RadioButton();
            this.rbRange_39_69 = new System.Windows.Forms.RadioButton();
            this.rbRange_9_92 = new System.Windows.Forms.RadioButton();
            this.rbRange_4_96 = new System.Windows.Forms.RadioButton();
            this.gbPolarity.SuspendLayout();
            this.gbValue.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numConvertedValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCurrentValue)).BeginInit();
            this.gbRange.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbPolarity
            // 
            this.gbPolarity.Controls.Add(this.rbNegative);
            this.gbPolarity.Controls.Add(this.rbPositive);
            resources.ApplyResources(this.gbPolarity, "gbPolarity");
            this.gbPolarity.Name = "gbPolarity";
            this.gbPolarity.TabStop = false;
            // 
            // rbNegative
            // 
            resources.ApplyResources(this.rbNegative, "rbNegative");
            this.rbNegative.Name = "rbNegative";
            this.rbNegative.TabStop = true;
            this.rbNegative.UseVisualStyleBackColor = true;
            // 
            // rbPositive
            // 
            resources.ApplyResources(this.rbPositive, "rbPositive");
            this.rbPositive.Name = "rbPositive";
            this.rbPositive.TabStop = true;
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
            resources.ApplyResources(this.gbValue, "gbValue");
            this.gbValue.Name = "gbValue";
            this.gbValue.TabStop = false;
            // 
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
            // 
            // numConvertedValue
            // 
            this.numConvertedValue.Hexadecimal = true;
            resources.ApplyResources(this.numConvertedValue, "numConvertedValue");
            this.numConvertedValue.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.numConvertedValue.Name = "numConvertedValue";
            // 
            // numCurrentValue
            // 
            this.numCurrentValue.DecimalPlaces = 2;
            this.numCurrentValue.Increment = new decimal(new int[] {
            24,
            0,
            0,
            65536});
            resources.ApplyResources(this.numCurrentValue, "numCurrentValue");
            this.numCurrentValue.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numCurrentValue.Name = "numCurrentValue";
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
            // gbRange
            // 
            this.gbRange.Controls.Add(this.rbRange_635_0);
            this.gbRange.Controls.Add(this.rbRange_317_5);
            this.gbRange.Controls.Add(this.rbRange_79_38);
            this.gbRange.Controls.Add(this.rbRange_39_69);
            this.gbRange.Controls.Add(this.rbRange_9_92);
            this.gbRange.Controls.Add(this.rbRange_4_96);
            resources.ApplyResources(this.gbRange, "gbRange");
            this.gbRange.Name = "gbRange";
            this.gbRange.TabStop = false;
            // 
            // rbRange_635_0
            // 
            resources.ApplyResources(this.rbRange_635_0, "rbRange_635_0");
            this.rbRange_635_0.Name = "rbRange_635_0";
            this.rbRange_635_0.TabStop = true;
            this.rbRange_635_0.UseVisualStyleBackColor = true;
            this.rbRange_635_0.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // rbRange_317_5
            // 
            resources.ApplyResources(this.rbRange_317_5, "rbRange_317_5");
            this.rbRange_317_5.Name = "rbRange_317_5";
            this.rbRange_317_5.TabStop = true;
            this.rbRange_317_5.UseVisualStyleBackColor = true;
            this.rbRange_317_5.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // rbRange_79_38
            // 
            resources.ApplyResources(this.rbRange_79_38, "rbRange_79_38");
            this.rbRange_79_38.Name = "rbRange_79_38";
            this.rbRange_79_38.TabStop = true;
            this.rbRange_79_38.UseVisualStyleBackColor = true;
            this.rbRange_79_38.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // rbRange_39_69
            // 
            resources.ApplyResources(this.rbRange_39_69, "rbRange_39_69");
            this.rbRange_39_69.Name = "rbRange_39_69";
            this.rbRange_39_69.TabStop = true;
            this.rbRange_39_69.UseVisualStyleBackColor = true;
            this.rbRange_39_69.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // rbRange_9_92
            // 
            resources.ApplyResources(this.rbRange_9_92, "rbRange_9_92");
            this.rbRange_9_92.Name = "rbRange_9_92";
            this.rbRange_9_92.TabStop = true;
            this.rbRange_9_92.UseVisualStyleBackColor = true;
            this.rbRange_9_92.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // rbRange_4_96
            // 
            resources.ApplyResources(this.rbRange_4_96, "rbRange_4_96");
            this.rbRange_4_96.Name = "rbRange_4_96";
            this.rbRange_4_96.TabStop = true;
            this.rbRange_4_96.UseVisualStyleBackColor = true;
            this.rbRange_4_96.CheckedChanged += new System.EventHandler(this.rbRange_CheckedChanged);
            // 
            // CyConfigureTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.gbRange);
            this.Controls.Add(this.gbValue);
            this.Controls.Add(this.gbPolarity);
            this.Name = "CyConfigureTab";
            this.gbPolarity.ResumeLayout(false);
            this.gbPolarity.PerformLayout();
            this.gbValue.ResumeLayout(false);
            this.gbValue.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numConvertedValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCurrentValue)).EndInit();
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
        private System.Windows.Forms.GroupBox gbRange;
        private System.Windows.Forms.RadioButton rbRange_9_92;
        private System.Windows.Forms.RadioButton rbRange_4_96;
        private System.Windows.Forms.RadioButton rbRange_635_0;
        private System.Windows.Forms.RadioButton rbRange_317_5;
        private System.Windows.Forms.RadioButton rbRange_79_38;
        private System.Windows.Forms.RadioButton rbRange_39_69;
    }
}
