namespace USBFS_v3_20
{
    partial class CyDetailsConfig
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyDetailsConfig));
            this.groupBoxParams = new System.Windows.Forms.GroupBox();
            this.numUpDownMaxPower = new System.Windows.Forms.NumericUpDown();
            this.comboBoxConfigString = new System.Windows.Forms.ComboBox();
            this.comboBoxRemoteWakeup = new System.Windows.Forms.ComboBox();
            this.comboBoxDevicePower = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.warningProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.groupBoxParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownMaxPower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.warningProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxParams
            // 
            this.groupBoxParams.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxParams.Controls.Add(this.numUpDownMaxPower);
            this.groupBoxParams.Controls.Add(this.comboBoxConfigString);
            this.groupBoxParams.Controls.Add(this.comboBoxRemoteWakeup);
            this.groupBoxParams.Controls.Add(this.comboBoxDevicePower);
            this.groupBoxParams.Controls.Add(this.label4);
            this.groupBoxParams.Controls.Add(this.label3);
            this.groupBoxParams.Controls.Add(this.label2);
            this.groupBoxParams.Controls.Add(this.label1);
            this.groupBoxParams.Location = new System.Drawing.Point(4, 11);
            this.groupBoxParams.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Name = "groupBoxParams";
            this.groupBoxParams.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Size = new System.Drawing.Size(352, 162);
            this.groupBoxParams.TabIndex = 1;
            this.groupBoxParams.TabStop = false;
            this.groupBoxParams.Text = "Configuration Attributes";
            // 
            // numUpDownMaxPower
            // 
            this.numUpDownMaxPower.Increment = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numUpDownMaxPower.Location = new System.Drawing.Point(160, 58);
            this.numUpDownMaxPower.Margin = new System.Windows.Forms.Padding(4);
            this.numUpDownMaxPower.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.numUpDownMaxPower.Name = "numUpDownMaxPower";
            this.numUpDownMaxPower.Size = new System.Drawing.Size(160, 22);
            this.numUpDownMaxPower.TabIndex = 2;
            this.numUpDownMaxPower.ValueChanged += new System.EventHandler(this.numUpDownMaxPower_ValueChanged);
            // 
            // comboBoxConfigString
            // 
            this.comboBoxConfigString.FormattingEnabled = true;
            this.comboBoxConfigString.Location = new System.Drawing.Point(159, 23);
            this.comboBoxConfigString.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxConfigString.Name = "comboBoxConfigString";
            this.comboBoxConfigString.Size = new System.Drawing.Size(160, 24);
            this.comboBoxConfigString.TabIndex = 1;
            this.comboBoxConfigString.DropDown += new System.EventHandler(this.comboBoxConfigString_DropDown);
            this.comboBoxConfigString.Validated += new System.EventHandler(this.comboBoxConfigString_Validated);
            // 
            // comboBoxRemoteWakeup
            // 
            this.comboBoxRemoteWakeup.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxRemoteWakeup.FormattingEnabled = true;
            this.comboBoxRemoteWakeup.Items.AddRange(new object[] {
            "Disabled",
            "Enabled"});
            this.comboBoxRemoteWakeup.Location = new System.Drawing.Point(159, 122);
            this.comboBoxRemoteWakeup.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxRemoteWakeup.Name = "comboBoxRemoteWakeup";
            this.comboBoxRemoteWakeup.Size = new System.Drawing.Size(160, 24);
            this.comboBoxRemoteWakeup.TabIndex = 4;
            this.comboBoxRemoteWakeup.SelectedIndexChanged += new System.EventHandler(this.comboBoxDevicePower_SelectedIndexChanged);
            // 
            // comboBoxDevicePower
            // 
            this.comboBoxDevicePower.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDevicePower.FormattingEnabled = true;
            this.comboBoxDevicePower.Items.AddRange(new object[] {
            "Bus Powered",
            "Self Powered"});
            this.comboBoxDevicePower.Location = new System.Drawing.Point(159, 89);
            this.comboBoxDevicePower.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxDevicePower.Name = "comboBoxDevicePower";
            this.comboBoxDevicePower.Size = new System.Drawing.Size(160, 24);
            this.comboBoxDevicePower.TabIndex = 3;
            this.comboBoxDevicePower.SelectedIndexChanged += new System.EventHandler(this.comboBoxDevicePower_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(4, 126);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(117, 17);
            this.label4.TabIndex = 3;
            this.label4.Text = "Remote Wakeup:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(4, 92);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(98, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Device Power:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(4, 60);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(114, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Max Power (mA):";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 27);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(137, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Configuration String:";
            // 
            // warningProvider
            // 
            this.warningProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.warningProvider.ContainerControl = this;
            this.warningProvider.Icon = ((System.Drawing.Icon)(resources.GetObject("warningProvider.Icon")));
            // 
            // CyDetailsConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.groupBoxParams);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyDetailsConfig";
            this.Size = new System.Drawing.Size(360, 182);
            this.groupBoxParams.ResumeLayout(false);
            this.groupBoxParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownMaxPower)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.warningProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxParams;
        private System.Windows.Forms.ComboBox comboBoxRemoteWakeup;
        private System.Windows.Forms.ComboBox comboBoxDevicePower;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxConfigString;
        private System.Windows.Forms.NumericUpDown numUpDownMaxPower;
        private System.Windows.Forms.ErrorProvider warningProvider;
    }
}
