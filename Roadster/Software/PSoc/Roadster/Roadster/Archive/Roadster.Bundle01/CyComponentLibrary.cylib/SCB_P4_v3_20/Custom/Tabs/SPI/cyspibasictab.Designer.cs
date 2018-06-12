namespace SCB_P4_v3_20
{
    partial class CySPIBasicTab
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
            this.m_cbBitRate = new System.Windows.Forms.ComboBox();
            this.m_numOversamplingFactor = new System.Windows.Forms.NumericUpDown();
            this.m_gbTransferSeparation = new System.Windows.Forms.GroupBox();
            this.m_rbTransferSeparated = new System.Windows.Forms.RadioButton();
            this.m_rbTransferContinuous = new System.Windows.Forms.RadioButton();
            this.m_numTXDataBits = new System.Windows.Forms.NumericUpDown();
            this.m_lblTxDataBits = new System.Windows.Forms.Label();
            this.m_lblActualBitRate = new System.Windows.Forms.Label();
            this.m_chbEnableLateMISOSample = new System.Windows.Forms.CheckBox();
            this.m_chbEnableMedianFilter = new System.Windows.Forms.CheckBox();
            this.m_numRXDataBits = new System.Windows.Forms.NumericUpDown();
            this.m_cbBitRateUnits = new System.Windows.Forms.ComboBox();
            this.m_cbBitOrder = new System.Windows.Forms.ComboBox();
            this.m_cbSSNumber = new System.Windows.Forms.ComboBox();
            this.m_lblBitOrder = new System.Windows.Forms.Label();
            this.m_lblSSNumber = new System.Windows.Forms.Label();
            this.m_lblOversample = new System.Windows.Forms.Label();
            this.m_lblDataRate = new System.Windows.Forms.Label();
            this.m_cbSubMode = new System.Windows.Forms.ComboBox();
            this.m_lblRxDataBits = new System.Windows.Forms.Label();
            this.m_lblSclkMode = new System.Windows.Forms.Label();
            this.m_lblSubMode = new System.Windows.Forms.Label();
            this.m_pictDrawing = new System.Windows.Forms.PictureBox();
            this.m_chbEnableWakeup = new System.Windows.Forms.CheckBox();
            this.m_lblMode = new System.Windows.Forms.Label();
            this.m_cbMode = new System.Windows.Forms.ComboBox();
            this.m_panelBitProperties = new System.Windows.Forms.Panel();
            this.m_lblSeparator = new System.Windows.Forms.Label();
            this.m_chbClockFromTerminal = new System.Windows.Forms.CheckBox();
            this.m_chbEnableSclkFreeRunning = new System.Windows.Forms.CheckBox();
            this.m_gbSlaveSelectSettings = new System.Windows.Forms.GroupBox();
            this.m_panelSSSettings = new System.Windows.Forms.Panel();
            this.m_cbSS2Polarity = new System.Windows.Forms.ComboBox();
            this.m_cbSS3Polarity = new System.Windows.Forms.ComboBox();
            this.m_cbSS1Polarity = new System.Windows.Forms.ComboBox();
            this.m_cbSS0Polarity = new System.Windows.Forms.ComboBox();
            this.m_lblSS3Polarity = new System.Windows.Forms.Label();
            this.m_lblSS2Polarity = new System.Windows.Forms.Label();
            this.m_lblSS0Polarity = new System.Windows.Forms.Label();
            this.m_lblSS1Polarity = new System.Windows.Forms.Label();
            this.m_backPanel = new System.Windows.Forms.Panel();
            this.m_gbPinRemoveOptions = new System.Windows.Forms.GroupBox();
            this.m_chbRemoveMiso = new System.Windows.Forms.CheckBox();
            this.m_chbRemoveMosi = new System.Windows.Forms.CheckBox();
            this.m_chbRemoveSclk = new System.Windows.Forms.CheckBox();
            this.m_lblPressApply = new System.Windows.Forms.Label();
            this.m_cbSCLKMode = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactor)).BeginInit();
            this.m_gbTransferSeparation.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTXDataBits)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRXDataBits)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_pictDrawing)).BeginInit();
            this.m_panelBitProperties.SuspendLayout();
            this.m_gbSlaveSelectSettings.SuspendLayout();
            this.m_panelSSSettings.SuspendLayout();
            this.m_backPanel.SuspendLayout();
            this.m_gbPinRemoveOptions.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_cbBitRate
            // 
            this.m_cbBitRate.FormattingEnabled = true;
            this.m_cbBitRate.Location = new System.Drawing.Point(111, 265);
            this.m_cbBitRate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbBitRate.Name = "m_cbBitRate";
            this.m_cbBitRate.Size = new System.Drawing.Size(99, 24);
            this.m_cbBitRate.TabIndex = 3;
            // 
            // m_numOversamplingFactor
            // 
            this.m_numOversamplingFactor.Location = new System.Drawing.Point(111, 298);
            this.m_numOversamplingFactor.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_numOversamplingFactor.Maximum = new decimal(new int[] {
            320000,
            0,
            0,
            0});
            this.m_numOversamplingFactor.Name = "m_numOversamplingFactor";
            this.m_numOversamplingFactor.Size = new System.Drawing.Size(80, 22);
            this.m_numOversamplingFactor.TabIndex = 5;
            this.m_numOversamplingFactor.Validating += new System.ComponentModel.CancelEventHandler(this.m_num_Validating);
            // 
            // m_gbTransferSeparation
            // 
            this.m_gbTransferSeparation.Controls.Add(this.m_rbTransferSeparated);
            this.m_gbTransferSeparation.Controls.Add(this.m_rbTransferContinuous);
            this.m_gbTransferSeparation.Location = new System.Drawing.Point(291, 113);
            this.m_gbTransferSeparation.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_gbTransferSeparation.Name = "m_gbTransferSeparation";
            this.m_gbTransferSeparation.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_gbTransferSeparation.Size = new System.Drawing.Size(155, 89);
            this.m_gbTransferSeparation.TabIndex = 13;
            this.m_gbTransferSeparation.TabStop = false;
            this.m_gbTransferSeparation.Text = "Transfer separation";
            // 
            // m_rbTransferSeparated
            // 
            this.m_rbTransferSeparated.AutoSize = true;
            this.m_rbTransferSeparated.Location = new System.Drawing.Point(8, 52);
            this.m_rbTransferSeparated.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_rbTransferSeparated.Name = "m_rbTransferSeparated";
            this.m_rbTransferSeparated.Size = new System.Drawing.Size(95, 21);
            this.m_rbTransferSeparated.TabIndex = 1;
            this.m_rbTransferSeparated.Text = "Separated";
            this.m_rbTransferSeparated.UseVisualStyleBackColor = true;
            this.m_rbTransferSeparated.CheckedChanged += new System.EventHandler(this.m_rbTransfer_CheckedChanged);
            // 
            // m_rbTransferContinuous
            // 
            this.m_rbTransferContinuous.AutoSize = true;
            this.m_rbTransferContinuous.Checked = true;
            this.m_rbTransferContinuous.Location = new System.Drawing.Point(8, 23);
            this.m_rbTransferContinuous.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_rbTransferContinuous.Name = "m_rbTransferContinuous";
            this.m_rbTransferContinuous.Size = new System.Drawing.Size(100, 21);
            this.m_rbTransferContinuous.TabIndex = 0;
            this.m_rbTransferContinuous.TabStop = true;
            this.m_rbTransferContinuous.Text = "Continuous";
            this.m_rbTransferContinuous.UseVisualStyleBackColor = true;
            this.m_rbTransferContinuous.CheckedChanged += new System.EventHandler(this.m_rbTransfer_CheckedChanged);
            // 
            // m_numTXDataBits
            // 
            this.m_numTXDataBits.Location = new System.Drawing.Point(115, 36);
            this.m_numTXDataBits.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_numTXDataBits.Maximum = new decimal(new int[] {
            3200000,
            0,
            0,
            0});
            this.m_numTXDataBits.Name = "m_numTXDataBits";
            this.m_numTXDataBits.Size = new System.Drawing.Size(131, 22);
            this.m_numTXDataBits.TabIndex = 1;
            this.m_numTXDataBits.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.m_numTXDataBits.Validating += new System.ComponentModel.CancelEventHandler(this.m_num_Validating);
            // 
            // m_lblTxDataBits
            // 
            this.m_lblTxDataBits.AutoSize = true;
            this.m_lblTxDataBits.Location = new System.Drawing.Point(4, 38);
            this.m_lblTxDataBits.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblTxDataBits.Name = "m_lblTxDataBits";
            this.m_lblTxDataBits.Size = new System.Drawing.Size(88, 17);
            this.m_lblTxDataBits.TabIndex = 0;
            this.m_lblTxDataBits.Text = "TX data bits:";
            // 
            // m_lblActualBitRate
            // 
            this.m_lblActualBitRate.AutoSize = true;
            this.m_lblActualBitRate.Location = new System.Drawing.Point(317, 268);
            this.m_lblActualBitRate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblActualBitRate.Name = "m_lblActualBitRate";
            this.m_lblActualBitRate.Size = new System.Drawing.Size(216, 17);
            this.m_lblActualBitRate.TabIndex = 0;
            this.m_lblActualBitRate.Text = "Actual data rate (kbps): unknown";
            // 
            // m_chbEnableLateMISOSample
            // 
            this.m_chbEnableLateMISOSample.AutoSize = true;
            this.m_chbEnableLateMISOSample.Location = new System.Drawing.Point(0, 57);
            this.m_chbEnableLateMISOSample.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_chbEnableLateMISOSample.Name = "m_chbEnableLateMISOSample";
            this.m_chbEnableLateMISOSample.Size = new System.Drawing.Size(151, 21);
            this.m_chbEnableLateMISOSample.TabIndex = 9;
            this.m_chbEnableLateMISOSample.Text = "MISO late sampling";
            this.m_chbEnableLateMISOSample.UseVisualStyleBackColor = true;
            // 
            // m_chbEnableMedianFilter
            // 
            this.m_chbEnableMedianFilter.AutoSize = true;
            this.m_chbEnableMedianFilter.Location = new System.Drawing.Point(0, 0);
            this.m_chbEnableMedianFilter.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_chbEnableMedianFilter.Name = "m_chbEnableMedianFilter";
            this.m_chbEnableMedianFilter.Size = new System.Drawing.Size(107, 21);
            this.m_chbEnableMedianFilter.TabIndex = 7;
            this.m_chbEnableMedianFilter.Text = "Median filter";
            this.m_chbEnableMedianFilter.UseVisualStyleBackColor = true;
            // 
            // m_numRXDataBits
            // 
            this.m_numRXDataBits.Location = new System.Drawing.Point(115, 4);
            this.m_numRXDataBits.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_numRXDataBits.Maximum = new decimal(new int[] {
            3200000,
            0,
            0,
            0});
            this.m_numRXDataBits.Name = "m_numRXDataBits";
            this.m_numRXDataBits.Size = new System.Drawing.Size(131, 22);
            this.m_numRXDataBits.TabIndex = 0;
            this.m_numRXDataBits.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.m_numRXDataBits.Validating += new System.ComponentModel.CancelEventHandler(this.m_num_Validating);
            // 
            // m_cbBitRateUnits
            // 
            this.m_cbBitRateUnits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbBitRateUnits.FormattingEnabled = true;
            this.m_cbBitRateUnits.Items.AddRange(new object[] {
            "kbps",
            "Mbps"});
            this.m_cbBitRateUnits.Location = new System.Drawing.Point(235, 265);
            this.m_cbBitRateUnits.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbBitRateUnits.Name = "m_cbBitRateUnits";
            this.m_cbBitRateUnits.Size = new System.Drawing.Size(73, 24);
            this.m_cbBitRateUnits.TabIndex = 4;
            // 
            // m_cbBitOrder
            // 
            this.m_cbBitOrder.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbBitOrder.FormattingEnabled = true;
            this.m_cbBitOrder.Location = new System.Drawing.Point(115, 68);
            this.m_cbBitOrder.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbBitOrder.Name = "m_cbBitOrder";
            this.m_cbBitOrder.Size = new System.Drawing.Size(129, 24);
            this.m_cbBitOrder.TabIndex = 2;
            // 
            // m_cbSSNumber
            // 
            this.m_cbSSNumber.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSSNumber.FormattingEnabled = true;
            this.m_cbSSNumber.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4"});
            this.m_cbSSNumber.Location = new System.Drawing.Point(115, 4);
            this.m_cbSSNumber.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSSNumber.Name = "m_cbSSNumber";
            this.m_cbSSNumber.Size = new System.Drawing.Size(125, 24);
            this.m_cbSSNumber.TabIndex = 0;
            // 
            // m_lblBitOrder
            // 
            this.m_lblBitOrder.AutoSize = true;
            this.m_lblBitOrder.Location = new System.Drawing.Point(4, 71);
            this.m_lblBitOrder.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBitOrder.Name = "m_lblBitOrder";
            this.m_lblBitOrder.Size = new System.Drawing.Size(66, 17);
            this.m_lblBitOrder.TabIndex = 0;
            this.m_lblBitOrder.Text = "Bit order:";
            // 
            // m_lblSSNumber
            // 
            this.m_lblSSNumber.AutoSize = true;
            this.m_lblSSNumber.Location = new System.Drawing.Point(4, 7);
            this.m_lblSSNumber.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSSNumber.Name = "m_lblSSNumber";
            this.m_lblSSNumber.Size = new System.Drawing.Size(100, 17);
            this.m_lblSSNumber.TabIndex = 0;
            this.m_lblSSNumber.Text = "Number of SS:";
            // 
            // m_lblOversample
            // 
            this.m_lblOversample.AutoSize = true;
            this.m_lblOversample.Location = new System.Drawing.Point(4, 300);
            this.m_lblOversample.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblOversample.Name = "m_lblOversample";
            this.m_lblOversample.Size = new System.Drawing.Size(99, 17);
            this.m_lblOversample.TabIndex = 0;
            this.m_lblOversample.Text = "Oversampling:";
            // 
            // m_lblDataRate
            // 
            this.m_lblDataRate.AutoSize = true;
            this.m_lblDataRate.Location = new System.Drawing.Point(4, 268);
            this.m_lblDataRate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblDataRate.Name = "m_lblDataRate";
            this.m_lblDataRate.Size = new System.Drawing.Size(71, 17);
            this.m_lblDataRate.TabIndex = 0;
            this.m_lblDataRate.Text = "Data rate:";
            // 
            // m_cbSubMode
            // 
            this.m_cbSubMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSubMode.FormattingEnabled = true;
            this.m_cbSubMode.Location = new System.Drawing.Point(111, 198);
            this.m_cbSubMode.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSubMode.Name = "m_cbSubMode";
            this.m_cbSubMode.Size = new System.Drawing.Size(277, 24);
            this.m_cbSubMode.TabIndex = 1;
            // 
            // m_lblRxDataBits
            // 
            this.m_lblRxDataBits.AutoSize = true;
            this.m_lblRxDataBits.Location = new System.Drawing.Point(4, 6);
            this.m_lblRxDataBits.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblRxDataBits.Name = "m_lblRxDataBits";
            this.m_lblRxDataBits.Size = new System.Drawing.Size(89, 17);
            this.m_lblRxDataBits.TabIndex = 0;
            this.m_lblRxDataBits.Text = "RX data bits:";
            // 
            // m_lblSclkMode
            // 
            this.m_lblSclkMode.AutoSize = true;
            this.m_lblSclkMode.Location = new System.Drawing.Point(4, 235);
            this.m_lblSclkMode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSclkMode.Name = "m_lblSclkMode";
            this.m_lblSclkMode.Size = new System.Drawing.Size(86, 17);
            this.m_lblSclkMode.TabIndex = 0;
            this.m_lblSclkMode.Text = "SCLK mode:";
            // 
            // m_lblSubMode
            // 
            this.m_lblSubMode.AutoSize = true;
            this.m_lblSubMode.Location = new System.Drawing.Point(4, 202);
            this.m_lblSubMode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSubMode.Name = "m_lblSubMode";
            this.m_lblSubMode.Size = new System.Drawing.Size(76, 17);
            this.m_lblSubMode.TabIndex = 0;
            this.m_lblSubMode.Text = "Sub mode:";
            // 
            // m_pictDrawing
            // 
            this.m_pictDrawing.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_pictDrawing.BackColor = System.Drawing.Color.White;
            this.m_pictDrawing.Location = new System.Drawing.Point(0, 0);
            this.m_pictDrawing.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_pictDrawing.Name = "m_pictDrawing";
            this.m_pictDrawing.Size = new System.Drawing.Size(605, 158);
            this.m_pictDrawing.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.m_pictDrawing.TabIndex = 75;
            this.m_pictDrawing.TabStop = false;
            // 
            // m_chbEnableWakeup
            // 
            this.m_chbEnableWakeup.AutoSize = true;
            this.m_chbEnableWakeup.Location = new System.Drawing.Point(0, 84);
            this.m_chbEnableWakeup.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbEnableWakeup.Name = "m_chbEnableWakeup";
            this.m_chbEnableWakeup.Size = new System.Drawing.Size(275, 21);
            this.m_chbEnableWakeup.TabIndex = 10;
            this.m_chbEnableWakeup.Text = "Enable wakeup from Deep Sleep Mode";
            this.m_chbEnableWakeup.UseVisualStyleBackColor = true;
            // 
            // m_lblMode
            // 
            this.m_lblMode.AutoSize = true;
            this.m_lblMode.Location = new System.Drawing.Point(4, 169);
            this.m_lblMode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblMode.Name = "m_lblMode";
            this.m_lblMode.Size = new System.Drawing.Size(47, 17);
            this.m_lblMode.TabIndex = 0;
            this.m_lblMode.Text = "Mode:";
            // 
            // m_cbMode
            // 
            this.m_cbMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbMode.FormattingEnabled = true;
            this.m_cbMode.Location = new System.Drawing.Point(111, 165);
            this.m_cbMode.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbMode.Name = "m_cbMode";
            this.m_cbMode.Size = new System.Drawing.Size(277, 24);
            this.m_cbMode.TabIndex = 0;
            // 
            // m_panelBitProperties
            // 
            this.m_panelBitProperties.Controls.Add(this.m_cbBitOrder);
            this.m_panelBitProperties.Controls.Add(this.m_numRXDataBits);
            this.m_panelBitProperties.Controls.Add(this.m_numTXDataBits);
            this.m_panelBitProperties.Controls.Add(this.m_lblTxDataBits);
            this.m_panelBitProperties.Controls.Add(this.m_lblRxDataBits);
            this.m_panelBitProperties.Controls.Add(this.m_lblBitOrder);
            this.m_panelBitProperties.Location = new System.Drawing.Point(0, 113);
            this.m_panelBitProperties.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_panelBitProperties.Name = "m_panelBitProperties";
            this.m_panelBitProperties.Size = new System.Drawing.Size(276, 98);
            this.m_panelBitProperties.TabIndex = 11;
            // 
            // m_lblSeparator
            // 
            this.m_lblSeparator.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblSeparator.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_lblSeparator.Location = new System.Drawing.Point(1, 107);
            this.m_lblSeparator.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSeparator.Name = "m_lblSeparator";
            this.m_lblSeparator.Size = new System.Drawing.Size(600, 2);
            this.m_lblSeparator.TabIndex = 0;
            // 
            // m_chbClockFromTerminal
            // 
            this.m_chbClockFromTerminal.AutoSize = true;
            this.m_chbClockFromTerminal.Location = new System.Drawing.Point(4, 330);
            this.m_chbClockFromTerminal.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_chbClockFromTerminal.Name = "m_chbClockFromTerminal";
            this.m_chbClockFromTerminal.Size = new System.Drawing.Size(150, 21);
            this.m_chbClockFromTerminal.TabIndex = 6;
            this.m_chbClockFromTerminal.Text = "Clock from terminal";
            this.m_chbClockFromTerminal.UseVisualStyleBackColor = false;
            // 
            // m_chbEnableSclkFreeRunning
            // 
            this.m_chbEnableSclkFreeRunning.AutoSize = true;
            this.m_chbEnableSclkFreeRunning.Location = new System.Drawing.Point(0, 28);
            this.m_chbEnableSclkFreeRunning.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_chbEnableSclkFreeRunning.Name = "m_chbEnableSclkFreeRunning";
            this.m_chbEnableSclkFreeRunning.Size = new System.Drawing.Size(146, 21);
            this.m_chbEnableSclkFreeRunning.TabIndex = 8;
            this.m_chbEnableSclkFreeRunning.Text = "SCLK free running";
            this.m_chbEnableSclkFreeRunning.UseVisualStyleBackColor = true;
            this.m_chbEnableSclkFreeRunning.CheckedChanged += new System.EventHandler(this.m_chb_CheckedChanged);
            // 
            // m_gbSlaveSelectSettings
            // 
            this.m_gbSlaveSelectSettings.Controls.Add(this.m_panelSSSettings);
            this.m_gbSlaveSelectSettings.Location = new System.Drawing.Point(0, 219);
            this.m_gbSlaveSelectSettings.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_gbSlaveSelectSettings.Name = "m_gbSlaveSelectSettings";
            this.m_gbSlaveSelectSettings.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_gbSlaveSelectSettings.Size = new System.Drawing.Size(283, 197);
            this.m_gbSlaveSelectSettings.TabIndex = 12;
            this.m_gbSlaveSelectSettings.TabStop = false;
            this.m_gbSlaveSelectSettings.Text = "Slave select settings";
            // 
            // m_panelSSSettings
            // 
            this.m_panelSSSettings.Controls.Add(this.m_cbSS2Polarity);
            this.m_panelSSSettings.Controls.Add(this.m_cbSS3Polarity);
            this.m_panelSSSettings.Controls.Add(this.m_cbSSNumber);
            this.m_panelSSSettings.Controls.Add(this.m_cbSS1Polarity);
            this.m_panelSSSettings.Controls.Add(this.m_cbSS0Polarity);
            this.m_panelSSSettings.Controls.Add(this.m_lblSSNumber);
            this.m_panelSSSettings.Controls.Add(this.m_lblSS3Polarity);
            this.m_panelSSSettings.Controls.Add(this.m_lblSS2Polarity);
            this.m_panelSSSettings.Controls.Add(this.m_lblSS0Polarity);
            this.m_panelSSSettings.Controls.Add(this.m_lblSS1Polarity);
            this.m_panelSSSettings.Location = new System.Drawing.Point(4, 23);
            this.m_panelSSSettings.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_panelSSSettings.Name = "m_panelSSSettings";
            this.m_panelSSSettings.Size = new System.Drawing.Size(272, 170);
            this.m_panelSSSettings.TabIndex = 0;
            // 
            // m_cbSS2Polarity
            // 
            this.m_cbSS2Polarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSS2Polarity.FormattingEnabled = true;
            this.m_cbSS2Polarity.Location = new System.Drawing.Point(115, 103);
            this.m_cbSS2Polarity.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSS2Polarity.Name = "m_cbSS2Polarity";
            this.m_cbSS2Polarity.Size = new System.Drawing.Size(125, 24);
            this.m_cbSS2Polarity.TabIndex = 3;
            // 
            // m_cbSS3Polarity
            // 
            this.m_cbSS3Polarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSS3Polarity.FormattingEnabled = true;
            this.m_cbSS3Polarity.Location = new System.Drawing.Point(115, 137);
            this.m_cbSS3Polarity.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSS3Polarity.Name = "m_cbSS3Polarity";
            this.m_cbSS3Polarity.Size = new System.Drawing.Size(125, 24);
            this.m_cbSS3Polarity.TabIndex = 4;
            // 
            // m_cbSS1Polarity
            // 
            this.m_cbSS1Polarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSS1Polarity.FormattingEnabled = true;
            this.m_cbSS1Polarity.Location = new System.Drawing.Point(115, 70);
            this.m_cbSS1Polarity.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSS1Polarity.Name = "m_cbSS1Polarity";
            this.m_cbSS1Polarity.Size = new System.Drawing.Size(125, 24);
            this.m_cbSS1Polarity.TabIndex = 2;
            // 
            // m_cbSS0Polarity
            // 
            this.m_cbSS0Polarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSS0Polarity.FormattingEnabled = true;
            this.m_cbSS0Polarity.Location = new System.Drawing.Point(115, 37);
            this.m_cbSS0Polarity.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSS0Polarity.Name = "m_cbSS0Polarity";
            this.m_cbSS0Polarity.Size = new System.Drawing.Size(125, 24);
            this.m_cbSS0Polarity.TabIndex = 1;
            // 
            // m_lblSS3Polarity
            // 
            this.m_lblSS3Polarity.AutoSize = true;
            this.m_lblSS3Polarity.Location = new System.Drawing.Point(4, 140);
            this.m_lblSS3Polarity.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSS3Polarity.Name = "m_lblSS3Polarity";
            this.m_lblSS3Polarity.Size = new System.Drawing.Size(88, 17);
            this.m_lblSS3Polarity.TabIndex = 11;
            this.m_lblSS3Polarity.Text = "SS3 polarity:";
            // 
            // m_lblSS2Polarity
            // 
            this.m_lblSS2Polarity.AutoSize = true;
            this.m_lblSS2Polarity.Location = new System.Drawing.Point(4, 107);
            this.m_lblSS2Polarity.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSS2Polarity.Name = "m_lblSS2Polarity";
            this.m_lblSS2Polarity.Size = new System.Drawing.Size(88, 17);
            this.m_lblSS2Polarity.TabIndex = 9;
            this.m_lblSS2Polarity.Text = "SS2 polarity:";
            // 
            // m_lblSS0Polarity
            // 
            this.m_lblSS0Polarity.AutoSize = true;
            this.m_lblSS0Polarity.Location = new System.Drawing.Point(4, 41);
            this.m_lblSS0Polarity.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSS0Polarity.Name = "m_lblSS0Polarity";
            this.m_lblSS0Polarity.Size = new System.Drawing.Size(88, 17);
            this.m_lblSS0Polarity.TabIndex = 5;
            this.m_lblSS0Polarity.Text = "SS0 polarity:";
            // 
            // m_lblSS1Polarity
            // 
            this.m_lblSS1Polarity.AutoSize = true;
            this.m_lblSS1Polarity.Location = new System.Drawing.Point(4, 74);
            this.m_lblSS1Polarity.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSS1Polarity.Name = "m_lblSS1Polarity";
            this.m_lblSS1Polarity.Size = new System.Drawing.Size(88, 17);
            this.m_lblSS1Polarity.TabIndex = 7;
            this.m_lblSS1Polarity.Text = "SS1 polarity:";
            // 
            // m_backPanel
            // 
            this.m_backPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_backPanel.Controls.Add(this.m_gbPinRemoveOptions);
            this.m_backPanel.Controls.Add(this.m_chbEnableMedianFilter);
            this.m_backPanel.Controls.Add(this.m_gbSlaveSelectSettings);
            this.m_backPanel.Controls.Add(this.m_chbEnableLateMISOSample);
            this.m_backPanel.Controls.Add(this.m_chbEnableSclkFreeRunning);
            this.m_backPanel.Controls.Add(this.m_gbTransferSeparation);
            this.m_backPanel.Controls.Add(this.m_chbEnableWakeup);
            this.m_backPanel.Controls.Add(this.m_lblSeparator);
            this.m_backPanel.Controls.Add(this.m_panelBitProperties);
            this.m_backPanel.Location = new System.Drawing.Point(4, 358);
            this.m_backPanel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_backPanel.Name = "m_backPanel";
            this.m_backPanel.Size = new System.Drawing.Size(604, 418);
            this.m_backPanel.TabIndex = 78;
            // 
            // m_gbPinRemoveOptions
            // 
            this.m_gbPinRemoveOptions.Controls.Add(this.m_chbRemoveMiso);
            this.m_gbPinRemoveOptions.Controls.Add(this.m_chbRemoveMosi);
            this.m_gbPinRemoveOptions.Controls.Add(this.m_chbRemoveSclk);
            this.m_gbPinRemoveOptions.Location = new System.Drawing.Point(291, 219);
            this.m_gbPinRemoveOptions.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_gbPinRemoveOptions.Name = "m_gbPinRemoveOptions";
            this.m_gbPinRemoveOptions.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_gbPinRemoveOptions.Size = new System.Drawing.Size(155, 116);
            this.m_gbPinRemoveOptions.TabIndex = 14;
            this.m_gbPinRemoveOptions.TabStop = false;
            this.m_gbPinRemoveOptions.Text = "Pin remove options";
            // 
            // m_chbRemoveMiso
            // 
            this.m_chbRemoveMiso.AutoSize = true;
            this.m_chbRemoveMiso.Location = new System.Drawing.Point(9, 81);
            this.m_chbRemoveMiso.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_chbRemoveMiso.Name = "m_chbRemoveMiso";
            this.m_chbRemoveMiso.Size = new System.Drawing.Size(120, 21);
            this.m_chbRemoveMiso.TabIndex = 2;
            this.m_chbRemoveMiso.Text = "Remove MISO";
            this.m_chbRemoveMiso.UseVisualStyleBackColor = true;
            // 
            // m_chbRemoveMosi
            // 
            this.m_chbRemoveMosi.AutoSize = true;
            this.m_chbRemoveMosi.Location = new System.Drawing.Point(9, 53);
            this.m_chbRemoveMosi.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_chbRemoveMosi.Name = "m_chbRemoveMosi";
            this.m_chbRemoveMosi.Size = new System.Drawing.Size(120, 21);
            this.m_chbRemoveMosi.TabIndex = 1;
            this.m_chbRemoveMosi.Text = "Remove MOSI";
            this.m_chbRemoveMosi.UseVisualStyleBackColor = true;
            // 
            // m_chbRemoveSclk
            // 
            this.m_chbRemoveSclk.AutoSize = true;
            this.m_chbRemoveSclk.Location = new System.Drawing.Point(9, 25);
            this.m_chbRemoveSclk.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_chbRemoveSclk.Name = "m_chbRemoveSclk";
            this.m_chbRemoveSclk.Size = new System.Drawing.Size(121, 21);
            this.m_chbRemoveSclk.TabIndex = 0;
            this.m_chbRemoveSclk.Text = "Remove SCLK";
            this.m_chbRemoveSclk.UseVisualStyleBackColor = true;
            // 
            // m_lblPressApply
            // 
            this.m_lblPressApply.AutoSize = true;
            this.m_lblPressApply.Location = new System.Drawing.Point(465, 287);
            this.m_lblPressApply.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblPressApply.Name = "m_lblPressApply";
            this.m_lblPressApply.Size = new System.Drawing.Size(103, 17);
            this.m_lblPressApply.TabIndex = 79;
            this.m_lblPressApply.Text = "(Press \"Apply\")";
            this.m_lblPressApply.Visible = false;
            // 
            // m_cbSCLKMode
            // 
            this.m_cbSCLKMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSCLKMode.FormattingEnabled = true;
            this.m_cbSCLKMode.Location = new System.Drawing.Point(111, 231);
            this.m_cbSCLKMode.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSCLKMode.Name = "m_cbSCLKMode";
            this.m_cbSCLKMode.Size = new System.Drawing.Size(277, 24);
            this.m_cbSCLKMode.TabIndex = 2;
            // 
            // CySPIBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_cbBitRateUnits);
            this.Controls.Add(this.m_cbMode);
            this.Controls.Add(this.m_cbBitRate);
            this.Controls.Add(this.m_numOversamplingFactor);
            this.Controls.Add(this.m_cbSCLKMode);
            this.Controls.Add(this.m_cbSubMode);
            this.Controls.Add(this.m_lblPressApply);
            this.Controls.Add(this.m_backPanel);
            this.Controls.Add(this.m_chbClockFromTerminal);
            this.Controls.Add(this.m_lblMode);
            this.Controls.Add(this.m_lblActualBitRate);
            this.Controls.Add(this.m_lblOversample);
            this.Controls.Add(this.m_lblDataRate);
            this.Controls.Add(this.m_lblSclkMode);
            this.Controls.Add(this.m_lblSubMode);
            this.Controls.Add(this.m_pictDrawing);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "CySPIBasicTab";
            this.Size = new System.Drawing.Size(609, 778);
            ((System.ComponentModel.ISupportInitialize)(this.m_numOversamplingFactor)).EndInit();
            this.m_gbTransferSeparation.ResumeLayout(false);
            this.m_gbTransferSeparation.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTXDataBits)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRXDataBits)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_pictDrawing)).EndInit();
            this.m_panelBitProperties.ResumeLayout(false);
            this.m_panelBitProperties.PerformLayout();
            this.m_gbSlaveSelectSettings.ResumeLayout(false);
            this.m_panelSSSettings.ResumeLayout(false);
            this.m_panelSSSettings.PerformLayout();
            this.m_backPanel.ResumeLayout(false);
            this.m_backPanel.PerformLayout();
            this.m_gbPinRemoveOptions.ResumeLayout(false);
            this.m_gbPinRemoveOptions.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox m_cbBitRate;
        private System.Windows.Forms.NumericUpDown m_numOversamplingFactor;
        private System.Windows.Forms.GroupBox m_gbTransferSeparation;
        private System.Windows.Forms.RadioButton m_rbTransferSeparated;
        private System.Windows.Forms.RadioButton m_rbTransferContinuous;
        private System.Windows.Forms.NumericUpDown m_numTXDataBits;
        private System.Windows.Forms.Label m_lblTxDataBits;
        private System.Windows.Forms.Label m_lblActualBitRate;
        private System.Windows.Forms.CheckBox m_chbEnableLateMISOSample;
        private System.Windows.Forms.CheckBox m_chbEnableMedianFilter;
        private System.Windows.Forms.NumericUpDown m_numRXDataBits;
        private System.Windows.Forms.ComboBox m_cbBitRateUnits;
        private System.Windows.Forms.ComboBox m_cbBitOrder;
        private System.Windows.Forms.ComboBox m_cbSSNumber;
        private System.Windows.Forms.Label m_lblBitOrder;
        private System.Windows.Forms.Label m_lblSSNumber;
        private System.Windows.Forms.Label m_lblOversample;
        private System.Windows.Forms.Label m_lblDataRate;
        private System.Windows.Forms.ComboBox m_cbSubMode;
        private System.Windows.Forms.Label m_lblRxDataBits;
        private System.Windows.Forms.Label m_lblSclkMode;
        private System.Windows.Forms.Label m_lblSubMode;
        private System.Windows.Forms.PictureBox m_pictDrawing;
        public System.Windows.Forms.CheckBox m_chbEnableWakeup;
        private System.Windows.Forms.Label m_lblMode;
        private System.Windows.Forms.ComboBox m_cbMode;
        private System.Windows.Forms.Panel m_panelBitProperties;
        private System.Windows.Forms.Label m_lblSeparator;
        private System.Windows.Forms.CheckBox m_chbClockFromTerminal;
        private System.Windows.Forms.CheckBox m_chbEnableSclkFreeRunning;
        private System.Windows.Forms.GroupBox m_gbSlaveSelectSettings;
        private System.Windows.Forms.ComboBox m_cbSS2Polarity;
        private System.Windows.Forms.Label m_lblSS2Polarity;
        private System.Windows.Forms.ComboBox m_cbSS1Polarity;
        private System.Windows.Forms.Label m_lblSS1Polarity;
        private System.Windows.Forms.ComboBox m_cbSS0Polarity;
        private System.Windows.Forms.Label m_lblSS0Polarity;
        private System.Windows.Forms.ComboBox m_cbSS3Polarity;
        private System.Windows.Forms.Label m_lblSS3Polarity;
        private System.Windows.Forms.Panel m_panelSSSettings;
        private System.Windows.Forms.Panel m_backPanel;
        private System.Windows.Forms.Label m_lblPressApply;
        private System.Windows.Forms.ComboBox m_cbSCLKMode;
        private System.Windows.Forms.GroupBox m_gbPinRemoveOptions;
        private System.Windows.Forms.CheckBox m_chbRemoveMiso;
        private System.Windows.Forms.CheckBox m_chbRemoveMosi;
        private System.Windows.Forms.CheckBox m_chbRemoveSclk;

    }
}
