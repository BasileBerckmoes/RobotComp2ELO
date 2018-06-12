namespace USBFS_v3_10
{
    partial class CyDetailsInterface
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
            this.label6 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label0x = new System.Windows.Forms.Label();
            this.numUpDownProtocol = new System.Windows.Forms.NumericUpDown();
            this.labelAlternateSettings = new System.Windows.Forms.Label();
            this.labelInterfaceNumber = new System.Windows.Forms.Label();
            this.labelProtocol = new System.Windows.Forms.Label();
            this.comboBoxInterfaceString = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBoxSubclass = new System.Windows.Forms.ComboBox();
            this.comboBoxClass = new System.Windows.Forms.ComboBox();
            this.labelClass = new System.Windows.Forms.Label();
            this.labelSubClass = new System.Windows.Forms.Label();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.groupBoxParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownProtocol)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxParams
            // 
            this.groupBoxParams.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxParams.Controls.Add(this.label6);
            this.groupBoxParams.Controls.Add(this.label2);
            this.groupBoxParams.Controls.Add(this.label0x);
            this.groupBoxParams.Controls.Add(this.numUpDownProtocol);
            this.groupBoxParams.Controls.Add(this.labelAlternateSettings);
            this.groupBoxParams.Controls.Add(this.labelInterfaceNumber);
            this.groupBoxParams.Controls.Add(this.labelProtocol);
            this.groupBoxParams.Controls.Add(this.comboBoxInterfaceString);
            this.groupBoxParams.Controls.Add(this.label5);
            this.groupBoxParams.Controls.Add(this.label9);
            this.groupBoxParams.Controls.Add(this.label4);
            this.groupBoxParams.Controls.Add(this.label3);
            this.groupBoxParams.Controls.Add(this.label1);
            this.groupBoxParams.Controls.Add(this.comboBoxSubclass);
            this.groupBoxParams.Controls.Add(this.comboBoxClass);
            this.groupBoxParams.Controls.Add(this.labelClass);
            this.groupBoxParams.Controls.Add(this.labelSubClass);
            this.groupBoxParams.Location = new System.Drawing.Point(4, 11);
            this.groupBoxParams.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Name = "groupBoxParams";
            this.groupBoxParams.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Size = new System.Drawing.Size(408, 226);
            this.groupBoxParams.TabIndex = 1;
            this.groupBoxParams.TabStop = false;
            this.groupBoxParams.Text = "Interface Attributes";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(133, 155);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(22, 17);
            this.label6.TabIndex = 18;
            this.label6.Text = "0x";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(133, 123);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(22, 17);
            this.label2.TabIndex = 17;
            this.label2.Text = "0x";
            // 
            // label0x
            // 
            this.label0x.AutoSize = true;
            this.label0x.Location = new System.Drawing.Point(133, 187);
            this.label0x.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label0x.Name = "label0x";
            this.label0x.Size = new System.Drawing.Size(22, 17);
            this.label0x.TabIndex = 16;
            this.label0x.Text = "0x";
            // 
            // numUpDownProtocol
            // 
            this.numUpDownProtocol.Hexadecimal = true;
            this.numUpDownProtocol.Location = new System.Drawing.Point(159, 184);
            this.numUpDownProtocol.Margin = new System.Windows.Forms.Padding(4);
            this.numUpDownProtocol.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownProtocol.Name = "numUpDownProtocol";
            this.numUpDownProtocol.Size = new System.Drawing.Size(161, 22);
            this.numUpDownProtocol.TabIndex = 15;
            this.numUpDownProtocol.ValueChanged += new System.EventHandler(this.numUpDownProtocol_ValueChanged);
            // 
            // labelAlternateSettings
            // 
            this.labelAlternateSettings.AutoSize = true;
            this.labelAlternateSettings.BackColor = System.Drawing.Color.Transparent;
            this.labelAlternateSettings.Location = new System.Drawing.Point(159, 91);
            this.labelAlternateSettings.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelAlternateSettings.Name = "labelAlternateSettings";
            this.labelAlternateSettings.Size = new System.Drawing.Size(16, 17);
            this.labelAlternateSettings.TabIndex = 14;
            this.labelAlternateSettings.Text = "0";
            this.labelAlternateSettings.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // labelInterfaceNumber
            // 
            this.labelInterfaceNumber.AutoSize = true;
            this.labelInterfaceNumber.BackColor = System.Drawing.Color.Transparent;
            this.labelInterfaceNumber.Location = new System.Drawing.Point(159, 59);
            this.labelInterfaceNumber.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelInterfaceNumber.Name = "labelInterfaceNumber";
            this.labelInterfaceNumber.Size = new System.Drawing.Size(16, 17);
            this.labelInterfaceNumber.TabIndex = 13;
            this.labelInterfaceNumber.Text = "0";
            this.labelInterfaceNumber.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // labelProtocol
            // 
            this.labelProtocol.AutoSize = true;
            this.labelProtocol.Location = new System.Drawing.Point(8, 187);
            this.labelProtocol.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelProtocol.Name = "labelProtocol";
            this.labelProtocol.Size = new System.Drawing.Size(64, 17);
            this.labelProtocol.TabIndex = 9;
            this.labelProtocol.Text = "Protocol:";
            // 
            // comboBoxInterfaceString
            // 
            this.comboBoxInterfaceString.FormattingEnabled = true;
            this.comboBoxInterfaceString.Location = new System.Drawing.Point(159, 24);
            this.comboBoxInterfaceString.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxInterfaceString.Name = "comboBoxInterfaceString";
            this.comboBoxInterfaceString.Size = new System.Drawing.Size(160, 24);
            this.comboBoxInterfaceString.TabIndex = 1;
            this.comboBoxInterfaceString.Validated += new System.EventHandler(this.comboBoxInterfaceString_Validated);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 91);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(124, 17);
            this.label5.TabIndex = 12;
            this.label5.Text = "Alternate Settings:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(8, 59);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(121, 17);
            this.label9.TabIndex = 11;
            this.label9.Text = "Interface Number:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 155);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 17);
            this.label4.TabIndex = 3;
            this.label4.Text = "Subclass:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 123);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Class:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 27);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(108, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Interface String:";
            // 
            // comboBoxSubclass
            // 
            this.comboBoxSubclass.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
            this.comboBoxSubclass.DropDownWidth = 170;
            this.comboBoxSubclass.FormattingEnabled = true;
            this.comboBoxSubclass.Items.AddRange(new object[] {
            "00 (No subclass)"});
            this.comboBoxSubclass.Location = new System.Drawing.Point(159, 151);
            this.comboBoxSubclass.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxSubclass.Name = "comboBoxSubclass";
            this.comboBoxSubclass.Size = new System.Drawing.Size(160, 24);
            this.comboBoxSubclass.TabIndex = 5;
            this.comboBoxSubclass.SelectedIndexChanged += new System.EventHandler(this.comboBoxSubclass_SelectedIndexChanged);
            this.comboBoxSubclass.TextChanged += new System.EventHandler(this.comboBox_TextChanged);
            this.comboBoxSubclass.Validating += new System.ComponentModel.CancelEventHandler(this.comboBox_Validating);
            // 
            // comboBoxClass
            // 
            this.comboBoxClass.FormattingEnabled = true;
            this.comboBoxClass.Items.AddRange(new object[] {
            "00 (Undefined)",
            "03 (HID)",
            "FF (Vendor-Specific)"});
            this.comboBoxClass.Location = new System.Drawing.Point(159, 119);
            this.comboBoxClass.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxClass.Name = "comboBoxClass";
            this.comboBoxClass.Size = new System.Drawing.Size(160, 24);
            this.comboBoxClass.TabIndex = 4;
            this.comboBoxClass.SelectedIndexChanged += new System.EventHandler(this.comboBoxClass_SelectedIndexChanged);
            this.comboBoxClass.TextChanged += new System.EventHandler(this.comboBox_TextChanged);
            this.comboBoxClass.Validating += new System.ComponentModel.CancelEventHandler(this.comboBox_Validating);
            // 
            // labelClass
            // 
            this.labelClass.AutoEllipsis = true;
            this.labelClass.BackColor = System.Drawing.Color.Transparent;
            this.labelClass.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labelClass.Location = new System.Drawing.Point(159, 118);
            this.labelClass.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelClass.Name = "labelClass";
            this.labelClass.Size = new System.Drawing.Size(161, 26);
            this.labelClass.TabIndex = 21;
            this.labelClass.Text = "0";
            this.labelClass.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.labelClass.Visible = false;
            // 
            // labelSubClass
            // 
            this.labelSubClass.AutoEllipsis = true;
            this.labelSubClass.BackColor = System.Drawing.Color.Transparent;
            this.labelSubClass.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labelSubClass.Location = new System.Drawing.Point(159, 150);
            this.labelSubClass.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelSubClass.Name = "labelSubClass";
            this.labelSubClass.Size = new System.Drawing.Size(161, 26);
            this.labelSubClass.TabIndex = 22;
            this.labelSubClass.Text = "0";
            this.labelSubClass.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.labelSubClass.Visible = false;
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // CyDetailsInterface
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxParams);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyDetailsInterface";
            this.Size = new System.Drawing.Size(416, 246);
            this.groupBoxParams.ResumeLayout(false);
            this.groupBoxParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownProtocol)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxParams;
        private System.Windows.Forms.ComboBox comboBoxClass;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxInterfaceString;
        private System.Windows.Forms.Label labelProtocol;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label labelInterfaceNumber;
        private System.Windows.Forms.Label labelAlternateSettings;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Label label0x;
        private System.Windows.Forms.NumericUpDown numUpDownProtocol;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelClass;
        private System.Windows.Forms.Label labelSubClass;
        private System.Windows.Forms.ComboBox comboBoxSubclass;
    }
}
