namespace SCB_P4_v3_20.Tabs.EZI2C
{
    partial class CyEZI2CTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyEZI2CTab));
            this.m_lblSubAddrSize = new System.Windows.Forms.Label();
            this.m_cbSubAddressSize = new System.Windows.Forms.ComboBox();
            this.m_chbClockStretching = new System.Windows.Forms.CheckBox();
            this.m_lblPrimarySlaveAddress = new System.Windows.Forms.Label();
            this.m_txtPrimarySlaveAddress = new System.Windows.Forms.TextBox();
            this.m_lblSeparator1 = new System.Windows.Forms.Label();
            this.m_chbEnableWakeup = new System.Windows.Forms.CheckBox();
            this.m_lblDataRateUnknown = new System.Windows.Forms.Label();
            this.m_lblSecondarySlaveAddress = new System.Windows.Forms.Label();
            this.m_txtSecondarySlaveAddress = new System.Windows.Forms.TextBox();
            this.m_chbClockFromTerminal = new System.Windows.Forms.CheckBox();
            this.m_lblDataRate = new System.Windows.Forms.Label();
            this.m_cbDataRate = new System.Windows.Forms.ComboBox();
            this.m_lblActualDataRate = new System.Windows.Forms.Label();
            this.m_cbNumberOfAddresses = new System.Windows.Forms.ComboBox();
            this.m_lblNumberOfAddresses = new System.Windows.Forms.Label();
            this.m_chbByteMode = new System.Windows.Forms.CheckBox();
            this.m_backPanel = new System.Windows.Forms.Panel();
            this.m_lblSlaveAddressInfo = new System.Windows.Forms.Label();
            this.m_lblSlaveAddressInfoIcon = new System.Windows.Forms.Label();
            this.m_backPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_lblSubAddrSize
            // 
            this.m_lblSubAddrSize.AutoSize = true;
            this.m_lblSubAddrSize.Location = new System.Drawing.Point(-2, 125);
            this.m_lblSubAddrSize.Name = "m_lblSubAddrSize";
            this.m_lblSubAddrSize.Size = new System.Drawing.Size(115, 13);
            this.m_lblSubAddrSize.TabIndex = 10;
            this.m_lblSubAddrSize.Text = "Sub-address size (bits):";
            // 
            // m_cbSubAddressSize
            // 
            this.m_cbSubAddressSize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSubAddressSize.FormattingEnabled = true;
            this.m_cbSubAddressSize.Items.AddRange(new object[] {
            "8",
            "16"});
            this.m_cbSubAddressSize.Location = new System.Drawing.Point(196, 122);
            this.m_cbSubAddressSize.Name = "m_cbSubAddressSize";
            this.m_cbSubAddressSize.Size = new System.Drawing.Size(59, 21);
            this.m_cbSubAddressSize.TabIndex = 8;
            // 
            // m_chbClockStretching
            // 
            this.m_chbClockStretching.AutoSize = true;
            this.m_chbClockStretching.Location = new System.Drawing.Point(0, 0);
            this.m_chbClockStretching.Name = "m_chbClockStretching";
            this.m_chbClockStretching.Size = new System.Drawing.Size(102, 17);
            this.m_chbClockStretching.TabIndex = 0;
            this.m_chbClockStretching.Text = "Clock stretching";
            this.m_chbClockStretching.UseVisualStyleBackColor = true;
            // 
            // m_lblPrimarySlaveAddress
            // 
            this.m_lblPrimarySlaveAddress.AutoSize = true;
            this.m_lblPrimarySlaveAddress.Location = new System.Drawing.Point(-2, 75);
            this.m_lblPrimarySlaveAddress.Name = "m_lblPrimarySlaveAddress";
            this.m_lblPrimarySlaveAddress.Size = new System.Drawing.Size(146, 13);
            this.m_lblPrimarySlaveAddress.TabIndex = 16;
            this.m_lblPrimarySlaveAddress.Text = "Primary slave address (7-bits):";
            // 
            // m_txtPrimarySlaveAddress
            // 
            this.m_txtPrimarySlaveAddress.Location = new System.Drawing.Point(196, 72);
            this.m_txtPrimarySlaveAddress.Name = "m_txtPrimarySlaveAddress";
            this.m_txtPrimarySlaveAddress.Size = new System.Drawing.Size(59, 20);
            this.m_txtPrimarySlaveAddress.TabIndex = 6;
            // 
            // m_lblSeparator1
            // 
            this.m_lblSeparator1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblSeparator1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_lblSeparator1.Location = new System.Drawing.Point(0, 42);
            this.m_lblSeparator1.Name = "m_lblSeparator1";
            this.m_lblSeparator1.Size = new System.Drawing.Size(342, 2);
            this.m_lblSeparator1.TabIndex = 14;
            // 
            // m_chbEnableWakeup
            // 
            this.m_chbEnableWakeup.AutoSize = true;
            this.m_chbEnableWakeup.Location = new System.Drawing.Point(0, 147);
            this.m_chbEnableWakeup.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbEnableWakeup.Name = "m_chbEnableWakeup";
            this.m_chbEnableWakeup.Size = new System.Drawing.Size(212, 17);
            this.m_chbEnableWakeup.TabIndex = 9;
            this.m_chbEnableWakeup.Text = "Enable wakeup from Deep Sleep Mode";
            this.m_chbEnableWakeup.UseVisualStyleBackColor = true;
            // 
            // m_lblDataRateUnknown
            // 
            this.m_lblDataRateUnknown.AutoSize = true;
            this.m_lblDataRateUnknown.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.m_lblDataRateUnknown.Location = new System.Drawing.Point(113, 5);
            this.m_lblDataRateUnknown.Name = "m_lblDataRateUnknown";
            this.m_lblDataRateUnknown.Size = new System.Drawing.Size(65, 13);
            this.m_lblDataRateUnknown.TabIndex = 13;
            this.m_lblDataRateUnknown.Text = "UNKNOWN";
            this.m_lblDataRateUnknown.Visible = false;
            // 
            // m_lblSecondarySlaveAddress
            // 
            this.m_lblSecondarySlaveAddress.AutoSize = true;
            this.m_lblSecondarySlaveAddress.Location = new System.Drawing.Point(-2, 100);
            this.m_lblSecondarySlaveAddress.Name = "m_lblSecondarySlaveAddress";
            this.m_lblSecondarySlaveAddress.Size = new System.Drawing.Size(163, 13);
            this.m_lblSecondarySlaveAddress.TabIndex = 15;
            this.m_lblSecondarySlaveAddress.Text = "Secondary slave address (7-bits):";
            // 
            // m_txtSecondarySlaveAddress
            // 
            this.m_txtSecondarySlaveAddress.Location = new System.Drawing.Point(196, 97);
            this.m_txtSecondarySlaveAddress.MaxLength = 5;
            this.m_txtSecondarySlaveAddress.Name = "m_txtSecondarySlaveAddress";
            this.m_txtSecondarySlaveAddress.Size = new System.Drawing.Size(59, 20);
            this.m_txtSecondarySlaveAddress.TabIndex = 7;
            // 
            // m_chbClockFromTerminal
            // 
            this.m_chbClockFromTerminal.AutoSize = true;
            this.m_chbClockFromTerminal.Location = new System.Drawing.Point(4, 28);
            this.m_chbClockFromTerminal.Name = "m_chbClockFromTerminal";
            this.m_chbClockFromTerminal.Size = new System.Drawing.Size(115, 17);
            this.m_chbClockFromTerminal.TabIndex = 2;
            this.m_chbClockFromTerminal.Text = "Clock from terminal";
            this.m_chbClockFromTerminal.UseVisualStyleBackColor = false;
            // 
            // m_lblDataRate
            // 
            this.m_lblDataRate.AutoSize = true;
            this.m_lblDataRate.Location = new System.Drawing.Point(1, 5);
            this.m_lblDataRate.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblDataRate.Name = "m_lblDataRate";
            this.m_lblDataRate.Size = new System.Drawing.Size(86, 13);
            this.m_lblDataRate.TabIndex = 12;
            this.m_lblDataRate.Text = "Data rate (kbps):";
            // 
            // m_cbDataRate
            // 
            this.m_cbDataRate.FormattingEnabled = true;
            this.m_cbDataRate.Items.AddRange(new object[] {
            "50",
            "100",
            "400",
            "1000"});
            this.m_cbDataRate.Location = new System.Drawing.Point(116, 2);
            this.m_cbDataRate.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbDataRate.MaxLength = 10;
            this.m_cbDataRate.Name = "m_cbDataRate";
            this.m_cbDataRate.Size = new System.Drawing.Size(50, 21);
            this.m_cbDataRate.TabIndex = 0;
            // 
            // m_lblActualDataRate
            // 
            this.m_lblActualDataRate.AutoSize = true;
            this.m_lblActualDataRate.Location = new System.Drawing.Point(191, 5);
            this.m_lblActualDataRate.Name = "m_lblActualDataRate";
            this.m_lblActualDataRate.Size = new System.Drawing.Size(117, 13);
            this.m_lblActualDataRate.TabIndex = 17;
            this.m_lblActualDataRate.Text = "Actual data rate (kbps):";
            // 
            // m_cbNumberOfAddresses
            // 
            this.m_cbNumberOfAddresses.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbNumberOfAddresses.FormattingEnabled = true;
            this.m_cbNumberOfAddresses.Items.AddRange(new object[] {
            "1",
            "2"});
            this.m_cbNumberOfAddresses.Location = new System.Drawing.Point(196, 46);
            this.m_cbNumberOfAddresses.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbNumberOfAddresses.Name = "m_cbNumberOfAddresses";
            this.m_cbNumberOfAddresses.Size = new System.Drawing.Size(59, 21);
            this.m_cbNumberOfAddresses.TabIndex = 5;
            // 
            // m_lblNumberOfAddresses
            // 
            this.m_lblNumberOfAddresses.AutoSize = true;
            this.m_lblNumberOfAddresses.Location = new System.Drawing.Point(-2, 49);
            this.m_lblNumberOfAddresses.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblNumberOfAddresses.Name = "m_lblNumberOfAddresses";
            this.m_lblNumberOfAddresses.Size = new System.Drawing.Size(110, 13);
            this.m_lblNumberOfAddresses.TabIndex = 28;
            this.m_lblNumberOfAddresses.Text = "Number of addresses:";
            // 
            // m_chbByteMode
            // 
            this.m_chbByteMode.AutoSize = true;
            this.m_chbByteMode.Location = new System.Drawing.Point(0, 23);
            this.m_chbByteMode.Name = "m_chbByteMode";
            this.m_chbByteMode.Size = new System.Drawing.Size(76, 17);
            this.m_chbByteMode.TabIndex = 1;
            this.m_chbByteMode.Text = "Byte mode";
            this.m_chbByteMode.UseVisualStyleBackColor = true;
            // 
            // m_backPanel
            // 
            this.m_backPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_backPanel.Controls.Add(this.m_txtSecondarySlaveAddress);
            this.m_backPanel.Controls.Add(this.m_txtPrimarySlaveAddress);
            this.m_backPanel.Controls.Add(this.m_cbNumberOfAddresses);
            this.m_backPanel.Controls.Add(this.m_cbSubAddressSize);
            this.m_backPanel.Controls.Add(this.m_lblSlaveAddressInfo);
            this.m_backPanel.Controls.Add(this.m_lblSlaveAddressInfoIcon);
            this.m_backPanel.Controls.Add(this.m_chbClockStretching);
            this.m_backPanel.Controls.Add(this.m_chbByteMode);
            this.m_backPanel.Controls.Add(this.m_lblSecondarySlaveAddress);
            this.m_backPanel.Controls.Add(this.m_chbEnableWakeup);
            this.m_backPanel.Controls.Add(this.m_lblSeparator1);
            this.m_backPanel.Controls.Add(this.m_lblPrimarySlaveAddress);
            this.m_backPanel.Controls.Add(this.m_lblNumberOfAddresses);
            this.m_backPanel.Controls.Add(this.m_lblSubAddrSize);
            this.m_backPanel.Location = new System.Drawing.Point(4, 50);
            this.m_backPanel.Name = "m_backPanel";
            this.m_backPanel.Size = new System.Drawing.Size(347, 259);
            this.m_backPanel.TabIndex = 3;
            // 
            // m_lblSlaveAddressInfo
            // 
            this.m_lblSlaveAddressInfo.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblSlaveAddressInfo.Location = new System.Drawing.Point(23, 177);
            this.m_lblSlaveAddressInfo.Name = "m_lblSlaveAddressInfo";
            this.m_lblSlaveAddressInfo.Size = new System.Drawing.Size(319, 68);
            this.m_lblSlaveAddressInfo.TabIndex = 29;
            this.m_lblSlaveAddressInfo.Text = resources.GetString("m_lblSlaveAddressInfo.Text");
            // 
            // m_lblSlaveAddressInfoIcon
            // 
            this.m_lblSlaveAddressInfoIcon.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.m_lblSlaveAddressInfoIcon.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.m_lblSlaveAddressInfoIcon.Location = new System.Drawing.Point(-2, 175);
            this.m_lblSlaveAddressInfoIcon.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblSlaveAddressInfoIcon.Name = "m_lblSlaveAddressInfoIcon";
            this.m_lblSlaveAddressInfoIcon.Size = new System.Drawing.Size(18, 18);
            this.m_lblSlaveAddressInfoIcon.TabIndex = 30;
            this.m_lblSlaveAddressInfoIcon.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // CyEZI2CBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_backPanel);
            this.Controls.Add(this.m_chbClockFromTerminal);
            this.Controls.Add(this.m_lblActualDataRate);
            this.Controls.Add(this.m_lblDataRate);
            this.Controls.Add(this.m_lblDataRateUnknown);
            this.Controls.Add(this.m_cbDataRate);
            this.Name = "CyEZI2CBasicTab";
            this.Size = new System.Drawing.Size(350, 313);
            this.m_backPanel.ResumeLayout(false);
            this.m_backPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblSubAddrSize;
        private System.Windows.Forms.ComboBox m_cbSubAddressSize;
        private System.Windows.Forms.CheckBox m_chbClockStretching;
        private System.Windows.Forms.Label m_lblPrimarySlaveAddress;
        private System.Windows.Forms.TextBox m_txtPrimarySlaveAddress;
        private System.Windows.Forms.Label m_lblSeparator1;
        private System.Windows.Forms.CheckBox m_chbEnableWakeup;
        private System.Windows.Forms.Label m_lblDataRateUnknown;
        private System.Windows.Forms.Label m_lblSecondarySlaveAddress;
        private System.Windows.Forms.TextBox m_txtSecondarySlaveAddress;
        private System.Windows.Forms.CheckBox m_chbClockFromTerminal;
        private System.Windows.Forms.Label m_lblDataRate;
        private System.Windows.Forms.ComboBox m_cbDataRate;
        private System.Windows.Forms.Label m_lblActualDataRate;
        private System.Windows.Forms.ComboBox m_cbNumberOfAddresses;
        private System.Windows.Forms.Label m_lblNumberOfAddresses;
private System.Windows.Forms.CheckBox m_chbByteMode;
private System.Windows.Forms.Panel m_backPanel;
private System.Windows.Forms.Label m_lblSlaveAddressInfo;
private System.Windows.Forms.Label m_lblSlaveAddressInfoIcon;
    }
}
