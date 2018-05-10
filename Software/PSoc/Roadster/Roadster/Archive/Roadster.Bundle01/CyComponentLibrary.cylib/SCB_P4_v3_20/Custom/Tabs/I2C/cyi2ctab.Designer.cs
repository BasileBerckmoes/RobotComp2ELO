namespace SCB_P4_v3_20
{
    partial class CyI2CBasicTab
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
            this.m_lblMode = new System.Windows.Forms.Label();
            this.m_lblDataRate = new System.Windows.Forms.Label();
            this.m_numOversamplingFactor = new System.Windows.Forms.NumericUpDown();
            this.m_lblOversamplingFactorHigh = new System.Windows.Forms.Label();
            this.m_cbDataRate = new System.Windows.Forms.ComboBox();
            this.m_lblSlaveAddress = new System.Windows.Forms.Label();
            this.m_numOversamplingFactorHigh = new System.Windows.Forms.NumericUpDown();
            this.m_lblActualDataRate = new System.Windows.Forms.Label();
            this.m_panelModes = new System.Windows.Forms.Panel();
            this.m_chbManualOversampleControl = new System.Windows.Forms.CheckBox();
            this.m_lblDataRateUnknown = new System.Windows.Forms.Label();
            this.m_cbMode = new System.Windows.Forms.ComboBox();
            this.m_numOversamplingFactorLow = new System.Windows.Forms.NumericUpDown();
            this.m_chbByteMode = new System.Windows.Forms.CheckBox();
            this.m_chbClockFromTerminal = new System.Windows.Forms.CheckBox();
            this.m_lblOversamplingFactorLow = new System.Windows.Forms.Label();
            this.m_lblOversamplingFactor = new System.Windows.Forms.Label();
            this.m_lblSeparator1 = new System.Windows.Forms.Label();
            this.m_txtSlaveAddress = new System.Windows.Forms.TextBox();
            this.m_chbEnableWakeup = new System.Windows.Forms.CheckBox();
            this.m_panelSlaveConf = new System.Windows.Forms.Panel();
            this.m_tlpSlaveAddress = new System.Windows.Forms.TableLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.m_gbBitGrid = new System.Windows.Forms.GroupBox();
            this.m_lblSeparator = new System.Windows.Forms.Label();
            this.m_binaryGridSlaveAddressMask = new SCB_P4_v3_20.CyBinaryGrid();
            this.m_binaryGridSlaveAddress = new SCB_P4_v3_20.CyBinaryGrid();
            this.m_lblMsb = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.m_lblLsb = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.m_lblRw = new System.Windows.Forms.Label();
            this.m_lblAddress = new System.Windows.Forms.Label();
            this.m_chbAcceptGeneralCallAddress = new System.Windows.Forms.CheckBox();
            this.m_txtSlaveAddressMask = new System.Windows.Forms.TextBox();
            this.m_lblSlaveAddrMask = new System.Windows.Forms.Label();
            this.m_chbAcceptAddress = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactorHigh)).BeginInit();
            this.m_panelModes.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactorLow)).BeginInit();
            this.m_panelSlaveConf.SuspendLayout();
            this.m_tlpSlaveAddress.SuspendLayout();
            this.panel1.SuspendLayout();
            this.m_gbBitGrid.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_lblMode
            // 
            this.m_lblMode.AutoSize = true;
            this.m_lblMode.Location = new System.Drawing.Point(3, 5);
            this.m_lblMode.Name = "m_lblMode";
            this.m_lblMode.Size = new System.Drawing.Size(37, 13);
            this.m_lblMode.TabIndex = 0;
            this.m_lblMode.Text = "Mode:";
            // 
            // m_lblDataRate
            // 
            this.m_lblDataRate.AutoSize = true;
            this.m_lblDataRate.Location = new System.Drawing.Point(3, 31);
            this.m_lblDataRate.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblDataRate.Name = "m_lblDataRate";
            this.m_lblDataRate.Size = new System.Drawing.Size(86, 13);
            this.m_lblDataRate.TabIndex = 0;
            this.m_lblDataRate.Text = "Data rate (kbps):";
            // 
            // m_numOversamplingFactor
            // 
            this.m_numOversamplingFactor.Location = new System.Drawing.Point(140, 54);
            this.m_numOversamplingFactor.Name = "m_numOversamplingFactor";
            this.m_numOversamplingFactor.Size = new System.Drawing.Size(50, 20);
            this.m_numOversamplingFactor.TabIndex = 2;
            // 
            // m_lblOversamplingFactorHigh
            // 
            this.m_lblOversamplingFactorHigh.AutoSize = true;
            this.m_lblOversamplingFactorHigh.Location = new System.Drawing.Point(302, 56);
            this.m_lblOversamplingFactorHigh.Name = "m_lblOversamplingFactorHigh";
            this.m_lblOversamplingFactorHigh.Size = new System.Drawing.Size(32, 13);
            this.m_lblOversamplingFactorHigh.TabIndex = 0;
            this.m_lblOversamplingFactorHigh.Text = "High:";
            // 
            // m_cbDataRate
            // 
            this.m_cbDataRate.FormattingEnabled = true;
            this.m_cbDataRate.Items.AddRange(new object[] {
            "50",
            "100",
            "400",
            "1000"});
            this.m_cbDataRate.Location = new System.Drawing.Point(140, 28);
            this.m_cbDataRate.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbDataRate.MaxLength = 10;
            this.m_cbDataRate.Name = "m_cbDataRate";
            this.m_cbDataRate.Size = new System.Drawing.Size(50, 21);
            this.m_cbDataRate.TabIndex = 1;
            // 
            // m_lblSlaveAddress
            // 
            this.m_lblSlaveAddress.AutoSize = true;
            this.m_lblSlaveAddress.Location = new System.Drawing.Point(3, 30);
            this.m_lblSlaveAddress.Name = "m_lblSlaveAddress";
            this.m_lblSlaveAddress.Size = new System.Drawing.Size(111, 13);
            this.m_lblSlaveAddress.TabIndex = 0;
            this.m_lblSlaveAddress.Text = "Slave address (7-bits):";
            // 
            // m_numOversamplingFactorHigh
            // 
            this.m_numOversamplingFactorHigh.BackColor = System.Drawing.SystemColors.Window;
            this.m_numOversamplingFactorHigh.Location = new System.Drawing.Point(340, 54);
            this.m_numOversamplingFactorHigh.Name = "m_numOversamplingFactorHigh";
            this.m_numOversamplingFactorHigh.Size = new System.Drawing.Size(42, 20);
            this.m_numOversamplingFactorHigh.TabIndex = 4;
            this.m_numOversamplingFactorHigh.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            // 
            // m_lblActualDataRate
            // 
            this.m_lblActualDataRate.AutoSize = true;
            this.m_lblActualDataRate.Location = new System.Drawing.Point(206, 32);
            this.m_lblActualDataRate.Name = "m_lblActualDataRate";
            this.m_lblActualDataRate.Size = new System.Drawing.Size(117, 13);
            this.m_lblActualDataRate.TabIndex = 0;
            this.m_lblActualDataRate.Text = "Actual data rate (kbps):";
            // 
            // m_panelModes
            // 
            this.m_panelModes.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_panelModes.Controls.Add(this.m_chbManualOversampleControl);
            this.m_panelModes.Controls.Add(this.m_lblDataRateUnknown);
            this.m_panelModes.Controls.Add(this.m_numOversamplingFactor);
            this.m_panelModes.Controls.Add(this.m_cbDataRate);
            this.m_panelModes.Controls.Add(this.m_lblSeparator1);
            this.m_panelModes.Controls.Add(this.m_numOversamplingFactorHigh);
            this.m_panelModes.Controls.Add(this.m_cbMode);
            this.m_panelModes.Controls.Add(this.m_numOversamplingFactorLow);
            this.m_panelModes.Controls.Add(this.m_chbByteMode);
            this.m_panelModes.Controls.Add(this.m_chbClockFromTerminal);
            this.m_panelModes.Controls.Add(this.m_lblMode);
            this.m_panelModes.Controls.Add(this.m_lblDataRate);
            this.m_panelModes.Controls.Add(this.m_lblOversamplingFactorHigh);
            this.m_panelModes.Controls.Add(this.m_lblActualDataRate);
            this.m_panelModes.Controls.Add(this.m_lblOversamplingFactorLow);
            this.m_panelModes.Controls.Add(this.m_lblOversamplingFactor);
            this.m_panelModes.Location = new System.Drawing.Point(1, 3);
            this.m_panelModes.Name = "m_panelModes";
            this.m_panelModes.Size = new System.Drawing.Size(481, 147);
            this.m_panelModes.TabIndex = 0;
            // 
            // m_chbManualOversampleControl
            // 
            this.m_chbManualOversampleControl.AutoSize = true;
            this.m_chbManualOversampleControl.Location = new System.Drawing.Point(6, 80);
            this.m_chbManualOversampleControl.Name = "m_chbManualOversampleControl";
            this.m_chbManualOversampleControl.Size = new System.Drawing.Size(153, 17);
            this.m_chbManualOversampleControl.TabIndex = 5;
            this.m_chbManualOversampleControl.Text = "Manual oversample control";
            this.m_chbManualOversampleControl.UseVisualStyleBackColor = true;
            // 
            // m_lblDataRateUnknown
            // 
            this.m_lblDataRateUnknown.AutoSize = true;
            this.m_lblDataRateUnknown.Location = new System.Drawing.Point(137, 32);
            this.m_lblDataRateUnknown.Name = "m_lblDataRateUnknown";
            this.m_lblDataRateUnknown.Size = new System.Drawing.Size(65, 13);
            this.m_lblDataRateUnknown.TabIndex = 0;
            this.m_lblDataRateUnknown.Text = "UNKNOWN";
            this.m_lblDataRateUnknown.Visible = false;
            // 
            // m_cbMode
            // 
            this.m_cbMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbMode.FormattingEnabled = true;
            this.m_cbMode.Location = new System.Drawing.Point(140, 2);
            this.m_cbMode.Name = "m_cbMode";
            this.m_cbMode.Size = new System.Drawing.Size(134, 21);
            this.m_cbMode.TabIndex = 0;
            // 
            // m_numOversamplingFactorLow
            // 
            this.m_numOversamplingFactorLow.BackColor = System.Drawing.SystemColors.Window;
            this.m_numOversamplingFactorLow.Location = new System.Drawing.Point(242, 54);
            this.m_numOversamplingFactorLow.Name = "m_numOversamplingFactorLow";
            this.m_numOversamplingFactorLow.Size = new System.Drawing.Size(42, 20);
            this.m_numOversamplingFactorLow.TabIndex = 3;
            this.m_numOversamplingFactorLow.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            // 
            // m_chbByteMode
            // 
            this.m_chbByteMode.AutoSize = true;
            this.m_chbByteMode.Location = new System.Drawing.Point(6, 126);
            this.m_chbByteMode.Name = "m_chbByteMode";
            this.m_chbByteMode.Size = new System.Drawing.Size(76, 17);
            this.m_chbByteMode.TabIndex = 7;
            this.m_chbByteMode.Text = "Byte mode";
            this.m_chbByteMode.UseVisualStyleBackColor = true;
            // 
            // m_chbClockFromTerminal
            // 
            this.m_chbClockFromTerminal.AutoSize = true;
            this.m_chbClockFromTerminal.Location = new System.Drawing.Point(6, 103);
            this.m_chbClockFromTerminal.Name = "m_chbClockFromTerminal";
            this.m_chbClockFromTerminal.Size = new System.Drawing.Size(115, 17);
            this.m_chbClockFromTerminal.TabIndex = 6;
            this.m_chbClockFromTerminal.Text = "Clock from terminal";
            this.m_chbClockFromTerminal.UseVisualStyleBackColor = false;
            // 
            // m_lblOversamplingFactorLow
            // 
            this.m_lblOversamplingFactorLow.AutoSize = true;
            this.m_lblOversamplingFactorLow.Location = new System.Drawing.Point(206, 56);
            this.m_lblOversamplingFactorLow.Name = "m_lblOversamplingFactorLow";
            this.m_lblOversamplingFactorLow.Size = new System.Drawing.Size(30, 13);
            this.m_lblOversamplingFactorLow.TabIndex = 0;
            this.m_lblOversamplingFactorLow.Text = "Low:";
            // 
            // m_lblOversamplingFactor
            // 
            this.m_lblOversamplingFactor.AutoSize = true;
            this.m_lblOversamplingFactor.Location = new System.Drawing.Point(3, 56);
            this.m_lblOversamplingFactor.Name = "m_lblOversamplingFactor";
            this.m_lblOversamplingFactor.Size = new System.Drawing.Size(104, 13);
            this.m_lblOversamplingFactor.TabIndex = 0;
            this.m_lblOversamplingFactor.Text = "Oversampling factor:";
            // 
            // m_lblSeparator1
            // 
            this.m_lblSeparator1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblSeparator1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_lblSeparator1.Location = new System.Drawing.Point(3, 146);
            this.m_lblSeparator1.Name = "m_lblSeparator1";
            this.m_lblSeparator1.Size = new System.Drawing.Size(480, 2);
            this.m_lblSeparator1.TabIndex = 1;
            // 
            // m_txtSlaveAddress
            // 
            this.m_txtSlaveAddress.Location = new System.Drawing.Point(140, 27);
            this.m_txtSlaveAddress.Name = "m_txtSlaveAddress";
            this.m_txtSlaveAddress.Size = new System.Drawing.Size(50, 20);
            this.m_txtSlaveAddress.TabIndex = 0;
            // 
            // m_chbEnableWakeup
            // 
            this.m_chbEnableWakeup.AutoSize = true;
            this.m_chbEnableWakeup.Location = new System.Drawing.Point(6, 129);
            this.m_chbEnableWakeup.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbEnableWakeup.Name = "m_chbEnableWakeup";
            this.m_chbEnableWakeup.Size = new System.Drawing.Size(212, 17);
            this.m_chbEnableWakeup.TabIndex = 4;
            this.m_chbEnableWakeup.Text = "Enable wakeup from Deep Sleep Mode";
            this.m_chbEnableWakeup.UseVisualStyleBackColor = true;
            // 
            // m_panelSlaveConf
            // 
            this.m_panelSlaveConf.Controls.Add(this.m_tlpSlaveAddress);
            this.m_panelSlaveConf.Controls.Add(this.m_chbAcceptGeneralCallAddress);
            this.m_panelSlaveConf.Controls.Add(this.m_txtSlaveAddressMask);
            this.m_panelSlaveConf.Controls.Add(this.m_txtSlaveAddress);
            this.m_panelSlaveConf.Controls.Add(this.m_lblSlaveAddress);
            this.m_panelSlaveConf.Controls.Add(this.m_chbEnableWakeup);
            this.m_panelSlaveConf.Controls.Add(this.m_lblSlaveAddrMask);
            this.m_panelSlaveConf.Controls.Add(this.m_chbAcceptAddress);
            this.m_panelSlaveConf.Location = new System.Drawing.Point(1, 152);
            this.m_panelSlaveConf.Name = "m_panelSlaveConf";
            this.m_panelSlaveConf.Size = new System.Drawing.Size(481, 158);
            this.m_panelSlaveConf.TabIndex = 1;
            // 
            // m_tlpSlaveAddress
            // 
            this.m_tlpSlaveAddress.AutoSize = true;
            this.m_tlpSlaveAddress.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_tlpSlaveAddress.ColumnCount = 2;
            this.m_tlpSlaveAddress.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpSlaveAddress.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpSlaveAddress.Controls.Add(this.panel1, 0, 1);
            this.m_tlpSlaveAddress.Controls.Add(this.panel2, 1, 1);
            this.m_tlpSlaveAddress.Controls.Add(this.panel3, 0, 0);
            this.m_tlpSlaveAddress.Location = new System.Drawing.Point(213, 5);
            this.m_tlpSlaveAddress.Margin = new System.Windows.Forms.Padding(0);
            this.m_tlpSlaveAddress.Name = "m_tlpSlaveAddress";
            this.m_tlpSlaveAddress.RowCount = 2;
            this.m_tlpSlaveAddress.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpSlaveAddress.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpSlaveAddress.Size = new System.Drawing.Size(258, 83);
            this.m_tlpSlaveAddress.TabIndex = 13;
            // 
            // panel1
            // 
            this.panel1.AutoSize = true;
            this.panel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel1.Controls.Add(this.m_gbBitGrid);
            this.panel1.Controls.Add(this.m_lblMsb);
            this.panel1.Location = new System.Drawing.Point(0, 17);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(215, 64);
            this.panel1.TabIndex = 13;
            // 
            // m_gbBitGrid
            // 
            this.m_gbBitGrid.AutoSize = true;
            this.m_gbBitGrid.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_gbBitGrid.Controls.Add(this.m_lblSeparator);
            this.m_gbBitGrid.Controls.Add(this.m_binaryGridSlaveAddressMask);
            this.m_gbBitGrid.Controls.Add(this.m_binaryGridSlaveAddress);
            this.m_gbBitGrid.Location = new System.Drawing.Point(36, -5);
            this.m_gbBitGrid.MaximumSize = new System.Drawing.Size(250, 66);
            this.m_gbBitGrid.Name = "m_gbBitGrid";
            this.m_gbBitGrid.Size = new System.Drawing.Size(176, 66);
            this.m_gbBitGrid.TabIndex = 7;
            this.m_gbBitGrid.TabStop = false;
            // 
            // m_lblSeparator
            // 
            this.m_lblSeparator.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_lblSeparator.Location = new System.Drawing.Point(151, 7);
            this.m_lblSeparator.Name = "m_lblSeparator";
            this.m_lblSeparator.Size = new System.Drawing.Size(2, 56);
            this.m_lblSeparator.TabIndex = 8;
            // 
            // m_binaryGridSlaveAddressMask
            // 
            this.m_binaryGridSlaveAddressMask.AutoSize = true;
            this.m_binaryGridSlaveAddressMask.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_binaryGridSlaveAddressMask.Bits = new string[] {
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0"};
            this.m_binaryGridSlaveAddressMask.Location = new System.Drawing.Point(7, 39);
            this.m_binaryGridSlaveAddressMask.Margin = new System.Windows.Forms.Padding(4);
            this.m_binaryGridSlaveAddressMask.Name = "m_binaryGridSlaveAddressMask";
            this.m_binaryGridSlaveAddressMask.NumberOfBits = 8;
            this.m_binaryGridSlaveAddressMask.Size = new System.Drawing.Size(162, 20);
            this.m_binaryGridSlaveAddressMask.TabIndex = 3;
            this.m_binaryGridSlaveAddressMask.TabStop = false;
            // 
            // m_binaryGridSlaveAddress
            // 
            this.m_binaryGridSlaveAddress.AutoSize = true;
            this.m_binaryGridSlaveAddress.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_binaryGridSlaveAddress.Bits = new string[] {
        "1",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "X"};
            this.m_binaryGridSlaveAddress.Location = new System.Drawing.Point(7, 10);
            this.m_binaryGridSlaveAddress.Margin = new System.Windows.Forms.Padding(4);
            this.m_binaryGridSlaveAddress.Name = "m_binaryGridSlaveAddress";
            this.m_binaryGridSlaveAddress.NumberOfBits = 8;
            this.m_binaryGridSlaveAddress.Size = new System.Drawing.Size(162, 20);
            this.m_binaryGridSlaveAddress.TabIndex = 1;
            this.m_binaryGridSlaveAddress.TabStop = false;
            // 
            // m_lblMsb
            // 
            this.m_lblMsb.AutoSize = true;
            this.m_lblMsb.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblMsb.Location = new System.Drawing.Point(7, 25);
            this.m_lblMsb.Name = "m_lblMsb";
            this.m_lblMsb.Size = new System.Drawing.Size(26, 12);
            this.m_lblMsb.TabIndex = 11;
            this.m_lblMsb.Text = "MSB";
            // 
            // panel2
            // 
            this.panel2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel2.Controls.Add(this.m_lblLsb);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(218, 20);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(37, 60);
            this.panel2.TabIndex = 14;
            // 
            // m_lblLsb
            // 
            this.m_lblLsb.AutoSize = true;
            this.m_lblLsb.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblLsb.Location = new System.Drawing.Point(-2, 22);
            this.m_lblLsb.Name = "m_lblLsb";
            this.m_lblLsb.Size = new System.Drawing.Size(22, 12);
            this.m_lblLsb.TabIndex = 10;
            this.m_lblLsb.Text = "LSB";
            // 
            // panel3
            // 
            this.panel3.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel3.Controls.Add(this.m_lblRw);
            this.panel3.Controls.Add(this.m_lblAddress);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(0, 0);
            this.panel3.Margin = new System.Windows.Forms.Padding(0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(215, 17);
            this.panel3.TabIndex = 15;
            // 
            // m_lblRw
            // 
            this.m_lblRw.AutoSize = true;
            this.m_lblRw.BackColor = System.Drawing.SystemColors.Control;
            this.m_lblRw.Dock = System.Windows.Forms.DockStyle.Right;
            this.m_lblRw.Location = new System.Drawing.Point(184, 0);
            this.m_lblRw.Margin = new System.Windows.Forms.Padding(0);
            this.m_lblRw.Name = "m_lblRw";
            this.m_lblRw.Size = new System.Drawing.Size(31, 13);
            this.m_lblRw.TabIndex = 9;
            this.m_lblRw.Text = "R/W";
            this.m_lblRw.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // m_lblAddress
            // 
            this.m_lblAddress.AutoSize = true;
            this.m_lblAddress.Location = new System.Drawing.Point(91, 0);
            this.m_lblAddress.Name = "m_lblAddress";
            this.m_lblAddress.Size = new System.Drawing.Size(45, 13);
            this.m_lblAddress.TabIndex = 8;
            this.m_lblAddress.Text = "Address";
            // 
            // m_chbAcceptGeneralCallAddress
            // 
            this.m_chbAcceptGeneralCallAddress.AutoSize = true;
            this.m_chbAcceptGeneralCallAddress.Location = new System.Drawing.Point(6, 107);
            this.m_chbAcceptGeneralCallAddress.Name = "m_chbAcceptGeneralCallAddress";
            this.m_chbAcceptGeneralCallAddress.Size = new System.Drawing.Size(157, 17);
            this.m_chbAcceptGeneralCallAddress.TabIndex = 3;
            this.m_chbAcceptGeneralCallAddress.Text = "Accept general call address";
            this.m_chbAcceptGeneralCallAddress.UseVisualStyleBackColor = true;
            // 
            // m_txtSlaveAddressMask
            // 
            this.m_txtSlaveAddressMask.Location = new System.Drawing.Point(140, 56);
            this.m_txtSlaveAddressMask.MaxLength = 5;
            this.m_txtSlaveAddressMask.Name = "m_txtSlaveAddressMask";
            this.m_txtSlaveAddressMask.Size = new System.Drawing.Size(50, 20);
            this.m_txtSlaveAddressMask.TabIndex = 1;
            // 
            // m_lblSlaveAddrMask
            // 
            this.m_lblSlaveAddrMask.AutoSize = true;
            this.m_lblSlaveAddrMask.Location = new System.Drawing.Point(3, 59);
            this.m_lblSlaveAddrMask.Name = "m_lblSlaveAddrMask";
            this.m_lblSlaveAddrMask.Size = new System.Drawing.Size(105, 13);
            this.m_lblSlaveAddrMask.TabIndex = 0;
            this.m_lblSlaveAddrMask.Text = "Slave address mask:";
            // 
            // m_chbAcceptAddress
            // 
            this.m_chbAcceptAddress.AutoSize = true;
            this.m_chbAcceptAddress.Location = new System.Drawing.Point(6, 84);
            this.m_chbAcceptAddress.Name = "m_chbAcceptAddress";
            this.m_chbAcceptAddress.Size = new System.Drawing.Size(201, 17);
            this.m_chbAcceptAddress.TabIndex = 2;
            this.m_chbAcceptAddress.Text = "Accept matching address in RX FIFO";
            this.m_chbAcceptAddress.UseVisualStyleBackColor = true;
            // 
            // CyI2CBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.Controls.Add(this.m_panelModes);
            this.Controls.Add(this.m_panelSlaveConf);
            this.Name = "CyI2CBasicTab";
            this.Size = new System.Drawing.Size(482, 313);
            this.Load += new System.EventHandler(this.CyI2CTab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactorHigh)).EndInit();
            this.m_panelModes.ResumeLayout(false);
            this.m_panelModes.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactorLow)).EndInit();
            this.m_panelSlaveConf.ResumeLayout(false);
            this.m_panelSlaveConf.PerformLayout();
            this.m_tlpSlaveAddress.ResumeLayout(false);
            this.m_tlpSlaveAddress.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.m_gbBitGrid.ResumeLayout(false);
            this.m_gbBitGrid.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label m_lblMode;
        private System.Windows.Forms.Label m_lblDataRate;
        private System.Windows.Forms.NumericUpDown m_numOversamplingFactor;
        private System.Windows.Forms.Label m_lblOversamplingFactorHigh;
        private System.Windows.Forms.ComboBox m_cbDataRate;
        private System.Windows.Forms.Label m_lblSlaveAddress;
        private System.Windows.Forms.NumericUpDown m_numOversamplingFactorHigh;
        private System.Windows.Forms.Label m_lblActualDataRate;
        private System.Windows.Forms.Panel m_panelModes;
        private System.Windows.Forms.ComboBox m_cbMode;
        private System.Windows.Forms.NumericUpDown m_numOversamplingFactorLow;
        private System.Windows.Forms.Label m_lblOversamplingFactorLow;
        private System.Windows.Forms.Label m_lblOversamplingFactor;
        private System.Windows.Forms.Label m_lblSeparator1;
        private System.Windows.Forms.Panel m_panelSlaveConf;
        private System.Windows.Forms.TextBox m_txtSlaveAddress;
        private System.Windows.Forms.CheckBox m_chbEnableWakeup;
        private System.Windows.Forms.Label m_lblSlaveAddrMask;
        private System.Windows.Forms.TextBox m_txtSlaveAddressMask;
        private System.Windows.Forms.CheckBox m_chbAcceptAddress;
        private System.Windows.Forms.CheckBox m_chbClockFromTerminal;
        private System.Windows.Forms.Label m_lblDataRateUnknown;
        private System.Windows.Forms.CheckBox m_chbByteMode;
        private System.Windows.Forms.GroupBox m_gbBitGrid;
        private System.Windows.Forms.Label m_lblSeparator;
        private System.Windows.Forms.Label m_lblMsb;
        private System.Windows.Forms.Label m_lblLsb;
        private System.Windows.Forms.Label m_lblRw;
        private System.Windows.Forms.Label m_lblAddress;
        private System.Windows.Forms.CheckBox m_chbManualOversampleControl;
        private System.Windows.Forms.CheckBox m_chbAcceptGeneralCallAddress;
        private CyBinaryGrid m_binaryGridSlaveAddressMask;
        private CyBinaryGrid m_binaryGridSlaveAddress;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TableLayoutPanel m_tlpSlaveAddress;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
    }
}
