namespace USBFS_v3_10
{
    partial class CyDetailsUsb20Extension
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
            this.groupBoxProerties = new System.Windows.Forms.GroupBox();
            this.label0xBaselineBESL = new System.Windows.Forms.Label();
            this.label0xDeepBESL = new System.Windows.Forms.Label();
            this.numDeepBESL = new System.Windows.Forms.NumericUpDown();
            this.numBaselineBESL = new System.Windows.Forms.NumericUpDown();
            this.checkBoxDeepBESL = new System.Windows.Forms.CheckBox();
            this.checkBoxBaselineBESL = new System.Windows.Forms.CheckBox();
            this.checkBoxEnableLPM = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.labelDescType = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBoxProerties.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numDeepBESL)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numBaselineBESL)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxProerties
            // 
            this.groupBoxProerties.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxProerties.Controls.Add(this.label0xBaselineBESL);
            this.groupBoxProerties.Controls.Add(this.label0xDeepBESL);
            this.groupBoxProerties.Controls.Add(this.numDeepBESL);
            this.groupBoxProerties.Controls.Add(this.numBaselineBESL);
            this.groupBoxProerties.Controls.Add(this.checkBoxDeepBESL);
            this.groupBoxProerties.Controls.Add(this.checkBoxBaselineBESL);
            this.groupBoxProerties.Controls.Add(this.checkBoxEnableLPM);
            this.groupBoxProerties.Controls.Add(this.label2);
            this.groupBoxProerties.Controls.Add(this.label3);
            this.groupBoxProerties.Controls.Add(this.labelDescType);
            this.groupBoxProerties.Controls.Add(this.label1);
            this.groupBoxProerties.Location = new System.Drawing.Point(4, 11);
            this.groupBoxProerties.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxProerties.Name = "groupBoxProerties";
            this.groupBoxProerties.Size = new System.Drawing.Size(464, 189);
            this.groupBoxProerties.TabIndex = 0;
            this.groupBoxProerties.TabStop = false;
            this.groupBoxProerties.Text = "USB 2.0 Extension Attributes";
            // 
            // label0xBaselineBESL
            // 
            this.label0xBaselineBESL.AutoSize = true;
            this.label0xBaselineBESL.Location = new System.Drawing.Point(170, 125);
            this.label0xBaselineBESL.Margin = new System.Windows.Forms.Padding(0);
            this.label0xBaselineBESL.Name = "label0xBaselineBESL";
            this.label0xBaselineBESL.Size = new System.Drawing.Size(22, 17);
            this.label0xBaselineBESL.TabIndex = 29;
            this.label0xBaselineBESL.Text = "0x";
            // 
            // label0xDeepBESL
            // 
            this.label0xDeepBESL.AutoSize = true;
            this.label0xDeepBESL.Location = new System.Drawing.Point(170, 155);
            this.label0xDeepBESL.Margin = new System.Windows.Forms.Padding(0);
            this.label0xDeepBESL.Name = "label0xDeepBESL";
            this.label0xDeepBESL.Size = new System.Drawing.Size(22, 17);
            this.label0xDeepBESL.TabIndex = 28;
            this.label0xDeepBESL.Text = "0x";
            // 
            // numDeepBESL
            // 
            this.numDeepBESL.Hexadecimal = true;
            this.numDeepBESL.Location = new System.Drawing.Point(195, 153);
            this.numDeepBESL.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.numDeepBESL.Name = "numDeepBESL";
            this.numDeepBESL.Size = new System.Drawing.Size(88, 22);
            this.numDeepBESL.TabIndex = 24;
            // 
            // numBaselineBESL
            // 
            this.numBaselineBESL.Hexadecimal = true;
            this.numBaselineBESL.Location = new System.Drawing.Point(195, 123);
            this.numBaselineBESL.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.numBaselineBESL.Name = "numBaselineBESL";
            this.numBaselineBESL.Size = new System.Drawing.Size(88, 22);
            this.numBaselineBESL.TabIndex = 22;
            // 
            // checkBoxDeepBESL
            // 
            this.checkBoxDeepBESL.AutoSize = true;
            this.checkBoxDeepBESL.Location = new System.Drawing.Point(34, 154);
            this.checkBoxDeepBESL.Name = "checkBoxDeepBESL";
            this.checkBoxDeepBESL.Size = new System.Drawing.Size(107, 21);
            this.checkBoxDeepBESL.TabIndex = 23;
            this.checkBoxDeepBESL.Text = "Deep BESL:";
            this.checkBoxDeepBESL.UseVisualStyleBackColor = true;
            // 
            // checkBoxBaselineBESL
            // 
            this.checkBoxBaselineBESL.AutoSize = true;
            this.checkBoxBaselineBESL.Location = new System.Drawing.Point(34, 124);
            this.checkBoxBaselineBESL.Name = "checkBoxBaselineBESL";
            this.checkBoxBaselineBESL.Size = new System.Drawing.Size(127, 21);
            this.checkBoxBaselineBESL.TabIndex = 21;
            this.checkBoxBaselineBESL.Text = "Baseline BESL:";
            this.checkBoxBaselineBESL.UseVisualStyleBackColor = true;
            // 
            // checkBoxEnableLPM
            // 
            this.checkBoxEnableLPM.AutoSize = true;
            this.checkBoxEnableLPM.Location = new System.Drawing.Point(9, 94);
            this.checkBoxEnableLPM.Name = "checkBoxEnableLPM";
            this.checkBoxEnableLPM.Size = new System.Drawing.Size(106, 21);
            this.checkBoxEnableLPM.TabIndex = 20;
            this.checkBoxEnableLPM.Text = "Enable LPM";
            this.checkBoxEnableLPM.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label2.Location = new System.Drawing.Point(195, 56);
            this.label2.Margin = new System.Windows.Forms.Padding(4);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(214, 26);
            this.label2.TabIndex = 19;
            this.label2.Text = "USB 2.0 Extension";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 61);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(156, 17);
            this.label3.TabIndex = 18;
            this.label3.Text = "Device Capability Type:";
            // 
            // labelDescType
            // 
            this.labelDescType.BackColor = System.Drawing.Color.Transparent;
            this.labelDescType.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labelDescType.Location = new System.Drawing.Point(195, 23);
            this.labelDescType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelDescType.Name = "labelDescType";
            this.labelDescType.Size = new System.Drawing.Size(214, 26);
            this.labelDescType.TabIndex = 17;
            this.labelDescType.Text = "Device Capability";
            this.labelDescType.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(113, 17);
            this.label1.TabIndex = 16;
            this.label1.Text = "Descriptor Type:";
            // 
            // CyDetailsUsb20Extension
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.groupBoxProerties);
            this.Name = "CyDetailsUsb20Extension";
            this.Size = new System.Drawing.Size(472, 209);
            this.groupBoxProerties.ResumeLayout(false);
            this.groupBoxProerties.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numDeepBESL)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numBaselineBESL)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxProerties;
        private System.Windows.Forms.Label labelDescType;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBoxEnableLPM;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label0xBaselineBESL;
        private System.Windows.Forms.Label label0xDeepBESL;
        private System.Windows.Forms.NumericUpDown numDeepBESL;
        private System.Windows.Forms.NumericUpDown numBaselineBESL;
        private System.Windows.Forms.CheckBox checkBoxDeepBESL;
        private System.Windows.Forms.CheckBox checkBoxBaselineBESL;
    }
}
