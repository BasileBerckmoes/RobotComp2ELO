namespace USBFS_v3_10
{
    partial class CyDetailsIntAssociation
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
            this.groupBoxParams = new System.Windows.Forms.GroupBox();
            this.numUpDownProtocol = new System.Windows.Forms.NumericUpDown();
            this.numUpDownSubclass = new System.Windows.Forms.NumericUpDown();
            this.numUpDownClass = new System.Windows.Forms.NumericUpDown();
            this.numUpDownInterfaceCount = new System.Windows.Forms.NumericUpDown();
            this.numUpDownFirstInterface = new System.Windows.Forms.NumericUpDown();
            this.labelProtocol = new System.Windows.Forms.Label();
            this.comboBoxInterfaceString = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBoxParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownProtocol)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownSubclass)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownClass)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownInterfaceCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownFirstInterface)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxParams
            // 
            this.groupBoxParams.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxParams.Controls.Add(this.label7);
            this.groupBoxParams.Controls.Add(this.label6);
            this.groupBoxParams.Controls.Add(this.label2);
            this.groupBoxParams.Controls.Add(this.numUpDownProtocol);
            this.groupBoxParams.Controls.Add(this.numUpDownSubclass);
            this.groupBoxParams.Controls.Add(this.numUpDownClass);
            this.groupBoxParams.Controls.Add(this.numUpDownInterfaceCount);
            this.groupBoxParams.Controls.Add(this.numUpDownFirstInterface);
            this.groupBoxParams.Controls.Add(this.labelProtocol);
            this.groupBoxParams.Controls.Add(this.comboBoxInterfaceString);
            this.groupBoxParams.Controls.Add(this.label5);
            this.groupBoxParams.Controls.Add(this.label9);
            this.groupBoxParams.Controls.Add(this.label4);
            this.groupBoxParams.Controls.Add(this.label3);
            this.groupBoxParams.Controls.Add(this.label1);
            this.groupBoxParams.Location = new System.Drawing.Point(3, 9);
            this.groupBoxParams.Name = "groupBoxParams";
            this.groupBoxParams.Size = new System.Drawing.Size(306, 184);
            this.groupBoxParams.TabIndex = 1;
            this.groupBoxParams.TabStop = false;
            this.groupBoxParams.Text = "Interface Association Attributes";
            // 
            // numUpDownProtocol
            // 
            this.numUpDownProtocol.Hexadecimal = true;
            this.numUpDownProtocol.Location = new System.Drawing.Point(122, 153);
            this.numUpDownProtocol.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownProtocol.Name = "numUpDownProtocol";
            this.numUpDownProtocol.Size = new System.Drawing.Size(120, 20);
            this.numUpDownProtocol.TabIndex = 15;
            this.numUpDownProtocol.ValueChanged += new System.EventHandler(this.numUpDown_ValueChanged);
            // 
            // numUpDownSubclass
            // 
            this.numUpDownSubclass.Hexadecimal = true;
            this.numUpDownSubclass.Location = new System.Drawing.Point(122, 126);
            this.numUpDownSubclass.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownSubclass.Name = "numUpDownSubclass";
            this.numUpDownSubclass.Size = new System.Drawing.Size(120, 20);
            this.numUpDownSubclass.TabIndex = 14;
            this.numUpDownSubclass.ValueChanged += new System.EventHandler(this.numUpDown_ValueChanged);
            // 
            // numUpDownClass
            // 
            this.numUpDownClass.Hexadecimal = true;
            this.numUpDownClass.Location = new System.Drawing.Point(122, 99);
            this.numUpDownClass.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownClass.Name = "numUpDownClass";
            this.numUpDownClass.Size = new System.Drawing.Size(120, 20);
            this.numUpDownClass.TabIndex = 13;
            this.numUpDownClass.ValueChanged += new System.EventHandler(this.numUpDown_ValueChanged);
            // 
            // numUpDownInterfaceCount
            // 
            this.numUpDownInterfaceCount.Location = new System.Drawing.Point(122, 72);
            this.numUpDownInterfaceCount.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownInterfaceCount.Name = "numUpDownInterfaceCount";
            this.numUpDownInterfaceCount.Size = new System.Drawing.Size(120, 20);
            this.numUpDownInterfaceCount.TabIndex = 3;
            this.numUpDownInterfaceCount.ValueChanged += new System.EventHandler(this.numUpDown_ValueChanged);
            // 
            // numUpDownFirstInterface
            // 
            this.numUpDownFirstInterface.Location = new System.Drawing.Point(122, 46);
            this.numUpDownFirstInterface.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownFirstInterface.Name = "numUpDownFirstInterface";
            this.numUpDownFirstInterface.Size = new System.Drawing.Size(120, 20);
            this.numUpDownFirstInterface.TabIndex = 2;
            this.numUpDownFirstInterface.ValueChanged += new System.EventHandler(this.numUpDown_ValueChanged);
            // 
            // labelProtocol
            // 
            this.labelProtocol.AutoSize = true;
            this.labelProtocol.Location = new System.Drawing.Point(6, 155);
            this.labelProtocol.Name = "labelProtocol";
            this.labelProtocol.Size = new System.Drawing.Size(49, 13);
            this.labelProtocol.TabIndex = 9;
            this.labelProtocol.Text = "Protocol:";
            // 
            // comboBoxInterfaceString
            // 
            this.comboBoxInterfaceString.FormattingEnabled = true;
            this.comboBoxInterfaceString.Location = new System.Drawing.Point(122, 19);
            this.comboBoxInterfaceString.Name = "comboBoxInterfaceString";
            this.comboBoxInterfaceString.Size = new System.Drawing.Size(121, 21);
            this.comboBoxInterfaceString.TabIndex = 1;
            this.comboBoxInterfaceString.Validated += new System.EventHandler(this.comboBoxInterfaceString_Validated);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 74);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(83, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "Interface Count:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 48);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(74, 13);
            this.label9.TabIndex = 11;
            this.label9.Text = "First Interface:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 128);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(97, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Function Subclass:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 101);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Function Class:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Interface String:";
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(102, 101);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(18, 13);
            this.label2.TabIndex = 16;
            this.label2.Text = "0x";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(102, 128);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(18, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "0x";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(102, 155);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(18, 13);
            this.label7.TabIndex = 18;
            this.label7.Text = "0x";
            // 
            // CyDetailsIntAssociation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxParams);
            this.Name = "CyDetailsIntAssociation";
            this.Size = new System.Drawing.Size(312, 200);
            this.groupBoxParams.ResumeLayout(false);
            this.groupBoxParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownProtocol)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownSubclass)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownClass)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownInterfaceCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownFirstInterface)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxParams;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxInterfaceString;
        private System.Windows.Forms.Label labelProtocol;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.NumericUpDown numUpDownInterfaceCount;
        private System.Windows.Forms.NumericUpDown numUpDownFirstInterface;
        private System.Windows.Forms.NumericUpDown numUpDownProtocol;
        private System.Windows.Forms.NumericUpDown numUpDownSubclass;
        private System.Windows.Forms.NumericUpDown numUpDownClass;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label2;
    }
}
