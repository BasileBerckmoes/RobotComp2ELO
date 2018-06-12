namespace USBFS_v3_10
{
    partial class CyDetailsEndpoint
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyDetailsEndpoint));
            this.groupBoxParams = new System.Windows.Forms.GroupBox();
            this.numUpDownbInterval = new System.Windows.Forms.NumericUpDown();
            this.comboBoxIsocInterval = new System.Windows.Forms.ComboBox();
            this.numUpDownMaxPacketSize = new System.Windows.Forms.NumericUpDown();
            this.comboBoxUsageType = new System.Windows.Forms.ComboBox();
            this.labelUsageType = new System.Windows.Forms.Label();
            this.comboBoxSynchType = new System.Windows.Forms.ComboBox();
            this.labelSynchType = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxEndpointNum = new System.Windows.Forms.ComboBox();
            this.comboBoxTransferType = new System.Windows.Forms.ComboBox();
            this.comboBoxDirection = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBoxDoubleBuffer = new System.Windows.Forms.CheckBox();
            this.errProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.warnProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.groupBoxParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownbInterval)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownMaxPacketSize)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.warnProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxParams
            // 
            this.groupBoxParams.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxParams.Controls.Add(this.numUpDownbInterval);
            this.groupBoxParams.Controls.Add(this.comboBoxIsocInterval);
            this.groupBoxParams.Controls.Add(this.numUpDownMaxPacketSize);
            this.groupBoxParams.Controls.Add(this.comboBoxUsageType);
            this.groupBoxParams.Controls.Add(this.labelUsageType);
            this.groupBoxParams.Controls.Add(this.comboBoxSynchType);
            this.groupBoxParams.Controls.Add(this.labelSynchType);
            this.groupBoxParams.Controls.Add(this.label5);
            this.groupBoxParams.Controls.Add(this.label2);
            this.groupBoxParams.Controls.Add(this.comboBoxEndpointNum);
            this.groupBoxParams.Controls.Add(this.comboBoxTransferType);
            this.groupBoxParams.Controls.Add(this.comboBoxDirection);
            this.groupBoxParams.Controls.Add(this.label4);
            this.groupBoxParams.Controls.Add(this.label3);
            this.groupBoxParams.Controls.Add(this.label1);
            this.groupBoxParams.Location = new System.Drawing.Point(4, 11);
            this.groupBoxParams.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Name = "groupBoxParams";
            this.groupBoxParams.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Size = new System.Drawing.Size(401, 260);
            this.groupBoxParams.TabIndex = 2;
            this.groupBoxParams.TabStop = false;
            this.groupBoxParams.Text = "Endpoint Attributes";
            // 
            // numUpDownbInterval
            // 
            this.numUpDownbInterval.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.numUpDownbInterval.Location = new System.Drawing.Point(159, 192);
            this.numUpDownbInterval.Margin = new System.Windows.Forms.Padding(4);
            this.numUpDownbInterval.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numUpDownbInterval.Name = "numUpDownbInterval";
            this.numUpDownbInterval.Size = new System.Drawing.Size(160, 22);
            this.numUpDownbInterval.TabIndex = 5;
            this.numUpDownbInterval.ValueChanged += new System.EventHandler(this.numUpDownInterval_Validated);
            this.numUpDownbInterval.KeyUp += new System.Windows.Forms.KeyEventHandler(this.numUpDownInterval_Validated);
            this.numUpDownbInterval.Validated += new System.EventHandler(this.numUpDownInterval_Validated);
            // 
            // comboBoxIsocInterval
            // 
            this.comboBoxIsocInterval.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.comboBoxIsocInterval.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxIsocInterval.FormattingEnabled = true;
            this.comboBoxIsocInterval.Items.AddRange(new object[] {
            "1",
            "2",
            "4",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512",
            "1024",
            "2048",
            "4096",
            "8192",
            "16384",
            "32768"});
            this.comboBoxIsocInterval.Location = new System.Drawing.Point(159, 191);
            this.comboBoxIsocInterval.Name = "comboBoxIsocInterval";
            this.comboBoxIsocInterval.Size = new System.Drawing.Size(160, 24);
            this.comboBoxIsocInterval.TabIndex = 6;
            this.comboBoxIsocInterval.Visible = false;
            this.comboBoxIsocInterval.SelectedIndexChanged += new System.EventHandler(this.comboBoxIsocInterval_Validated);
            this.comboBoxIsocInterval.Validated += new System.EventHandler(this.comboBoxIsocInterval_Validated);
            // 
            // numUpDownMaxPacketSize
            // 
            this.numUpDownMaxPacketSize.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.numUpDownMaxPacketSize.Location = new System.Drawing.Point(159, 224);
            this.numUpDownMaxPacketSize.Margin = new System.Windows.Forms.Padding(4);
            this.numUpDownMaxPacketSize.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.numUpDownMaxPacketSize.Name = "numUpDownMaxPacketSize";
            this.numUpDownMaxPacketSize.Size = new System.Drawing.Size(160, 22);
            this.numUpDownMaxPacketSize.TabIndex = 7;
            this.numUpDownMaxPacketSize.ValueChanged += new System.EventHandler(this.numUpDownMaxPacketSize_Validated);
            this.numUpDownMaxPacketSize.KeyUp += new System.Windows.Forms.KeyEventHandler(this.numUpDownMaxPacketSize_Validated);
            this.numUpDownMaxPacketSize.Validated += new System.EventHandler(this.numUpDownMaxPacketSize_Validated);
            // 
            // comboBoxUsageType
            // 
            this.comboBoxUsageType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxUsageType.DropDownWidth = 160;
            this.comboBoxUsageType.FormattingEnabled = true;
            this.comboBoxUsageType.Items.AddRange(new object[] {
            "Data endpoint",
            "Feedback endpoint",
            "Implicit feedback Data endpoint"});
            this.comboBoxUsageType.Location = new System.Drawing.Point(159, 156);
            this.comboBoxUsageType.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxUsageType.Name = "comboBoxUsageType";
            this.comboBoxUsageType.Size = new System.Drawing.Size(160, 24);
            this.comboBoxUsageType.TabIndex = 4;
            this.comboBoxUsageType.Validated += new System.EventHandler(this.comboBoxTransferType_Validated);
            // 
            // labelUsageType
            // 
            this.labelUsageType.AutoSize = true;
            this.labelUsageType.Location = new System.Drawing.Point(8, 160);
            this.labelUsageType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelUsageType.Name = "labelUsageType";
            this.labelUsageType.Size = new System.Drawing.Size(89, 17);
            this.labelUsageType.TabIndex = 16;
            this.labelUsageType.Text = "Usage Type:";
            // 
            // comboBoxSynchType
            // 
            this.comboBoxSynchType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSynchType.FormattingEnabled = true;
            this.comboBoxSynchType.Items.AddRange(new object[] {
            "No synchronization",
            "Asynchronous",
            "Adaptive",
            "Synchronous"});
            this.comboBoxSynchType.Location = new System.Drawing.Point(159, 123);
            this.comboBoxSynchType.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxSynchType.Name = "comboBoxSynchType";
            this.comboBoxSynchType.Size = new System.Drawing.Size(160, 24);
            this.comboBoxSynchType.TabIndex = 3;
            this.comboBoxSynchType.Validated += new System.EventHandler(this.comboBoxTransferType_Validated);
            // 
            // labelSynchType
            // 
            this.labelSynchType.AutoSize = true;
            this.labelSynchType.Location = new System.Drawing.Point(8, 127);
            this.labelSynchType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelSynchType.Name = "labelSynchType";
            this.labelSynchType.Size = new System.Drawing.Size(87, 17);
            this.labelSynchType.TabIndex = 14;
            this.labelSynchType.Text = "Synch Type:";
            // 
            // label5
            // 
            this.label5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 194);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(90, 17);
            this.label5.TabIndex = 11;
            this.label5.Text = "Interval (ms):";
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 226);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(115, 17);
            this.label2.TabIndex = 9;
            this.label2.Text = "Max Packet Size:";
            // 
            // comboBoxEndpointNum
            // 
            this.comboBoxEndpointNum.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxEndpointNum.FormattingEnabled = true;
            this.comboBoxEndpointNum.Location = new System.Drawing.Point(159, 23);
            this.comboBoxEndpointNum.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxEndpointNum.Name = "comboBoxEndpointNum";
            this.comboBoxEndpointNum.Size = new System.Drawing.Size(160, 24);
            this.comboBoxEndpointNum.TabIndex = 0;
            this.comboBoxEndpointNum.SelectedIndexChanged += new System.EventHandler(this.comboBoxEndpointNum_Validated);
            this.comboBoxEndpointNum.Validated += new System.EventHandler(this.comboBoxEndpointNum_Validated);
            // 
            // comboBoxTransferType
            // 
            this.comboBoxTransferType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTransferType.FormattingEnabled = true;
            this.comboBoxTransferType.Items.AddRange(new object[] {
            "CONT",
            "INT",
            "BULK",
            "ISOC"});
            this.comboBoxTransferType.Location = new System.Drawing.Point(159, 90);
            this.comboBoxTransferType.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxTransferType.Name = "comboBoxTransferType";
            this.comboBoxTransferType.Size = new System.Drawing.Size(160, 24);
            this.comboBoxTransferType.TabIndex = 2;
            this.comboBoxTransferType.SelectedIndexChanged += new System.EventHandler(this.comboBoxTransferType_SelectedIndexChanged);
            this.comboBoxTransferType.Validated += new System.EventHandler(this.comboBoxTransferType_Validated);
            // 
            // comboBoxDirection
            // 
            this.comboBoxDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDirection.FormattingEnabled = true;
            this.comboBoxDirection.Items.AddRange(new object[] {
            "IN",
            "OUT"});
            this.comboBoxDirection.Location = new System.Drawing.Point(159, 57);
            this.comboBoxDirection.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxDirection.Name = "comboBoxDirection";
            this.comboBoxDirection.Size = new System.Drawing.Size(160, 24);
            this.comboBoxDirection.TabIndex = 1;
            this.comboBoxDirection.SelectedIndexChanged += new System.EventHandler(this.comboBoxEndpointNum_Validated);
            this.comboBoxDirection.Validated += new System.EventHandler(this.comboBoxEndpointNum_Validated);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 94);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(102, 17);
            this.label4.TabIndex = 3;
            this.label4.Text = "Transfer Type:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 60);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(68, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Direction:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 27);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Endpoint Number:";
            // 
            // checkBoxDoubleBuffer
            // 
            this.checkBoxDoubleBuffer.AutoSize = true;
            this.checkBoxDoubleBuffer.Location = new System.Drawing.Point(8, 278);
            this.checkBoxDoubleBuffer.Margin = new System.Windows.Forms.Padding(4);
            this.checkBoxDoubleBuffer.Name = "checkBoxDoubleBuffer";
            this.checkBoxDoubleBuffer.Size = new System.Drawing.Size(117, 21);
            this.checkBoxDoubleBuffer.TabIndex = 7;
            this.checkBoxDoubleBuffer.Text = "Double Buffer";
            this.checkBoxDoubleBuffer.UseVisualStyleBackColor = true;
            this.checkBoxDoubleBuffer.Visible = false;
            this.checkBoxDoubleBuffer.CheckedChanged += new System.EventHandler(this.checkBoxDoubleBuffer_CheckedChanged);
            // 
            // errProvider
            // 
            this.errProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errProvider.ContainerControl = this;
            // 
            // warnProvider
            // 
            this.warnProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.warnProvider.ContainerControl = this;
            this.warnProvider.Icon = ((System.Drawing.Icon)(resources.GetObject("warnProvider.Icon")));
            // 
            // CyDetailsEndpoint
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.checkBoxDoubleBuffer);
            this.Controls.Add(this.groupBoxParams);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyDetailsEndpoint";
            this.Size = new System.Drawing.Size(409, 318);
            this.groupBoxParams.ResumeLayout(false);
            this.groupBoxParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownbInterval)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownMaxPacketSize)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.warnProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxParams;
        private System.Windows.Forms.ComboBox comboBoxEndpointNum;
        private System.Windows.Forms.ComboBox comboBoxTransferType;
        private System.Windows.Forms.ComboBox comboBoxDirection;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxUsageType;
        private System.Windows.Forms.Label labelUsageType;
        private System.Windows.Forms.ComboBox comboBoxSynchType;
        private System.Windows.Forms.Label labelSynchType;
        private System.Windows.Forms.CheckBox checkBoxDoubleBuffer;
        private System.Windows.Forms.NumericUpDown numUpDownbInterval;
        private System.Windows.Forms.NumericUpDown numUpDownMaxPacketSize;
        private System.Windows.Forms.ErrorProvider errProvider;
        private System.Windows.Forms.ErrorProvider warnProvider;
        private System.Windows.Forms.ComboBox comboBoxIsocInterval;
    }
}
