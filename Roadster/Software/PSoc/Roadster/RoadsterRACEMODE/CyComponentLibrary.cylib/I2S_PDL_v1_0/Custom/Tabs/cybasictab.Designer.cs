namespace I2S_PDL_v1_0.Tabs
{
    partial class CyBasicTab
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
            this.m_gbTx = new System.Windows.Forms.GroupBox();
            this.m_panelTx = new System.Windows.Forms.Panel();
            this.m_lblTxChannelLength = new System.Windows.Forms.Label();
            this.m_cbTxChannelLength = new System.Windows.Forms.ComboBox();
            this.m_cbTxWordLength = new System.Windows.Forms.ComboBox();
            this.m_lblTxFrameRateText = new System.Windows.Forms.Label();
            this.m_numTxFifoTriggerLevel = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
            this.m_lblTxInterrupts = new System.Windows.Forms.Label();
            this.m_lblTxWordLength = new System.Windows.Forms.Label();
            this.m_chbTxUnderflowInt = new System.Windows.Forms.CheckBox();
            this.m_lblTxOverheadValue = new System.Windows.Forms.Label();
            this.m_lblTxFifoTriggerLevel = new System.Windows.Forms.Label();
            this.m_chbTxNotFullInt = new System.Windows.Forms.CheckBox();
            this.m_chbTxOverflowInt = new System.Windows.Forms.CheckBox();
            this.m_lblTxFrameRateValue = new System.Windows.Forms.Label();
            this.m_chbTxDmaTrigger = new System.Windows.Forms.CheckBox();
            this.m_chbTxTriggerInt = new System.Windows.Forms.CheckBox();
            this.m_cbTxOverheadValue = new System.Windows.Forms.ComboBox();
            this.m_chbTxEmptyInt = new System.Windows.Forms.CheckBox();
            this.m_chbEnableTx = new System.Windows.Forms.CheckBox();
            this.m_chbClockFromTerminal = new System.Windows.Forms.CheckBox();
            this.m_lblInputClockText = new System.Windows.Forms.Label();
            this.m_lblInputClockValue = new System.Windows.Forms.Label();
            this.m_lblClockDivider = new System.Windows.Forms.Label();
            this.m_numClockDivider = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
            this.m_gbRx = new System.Windows.Forms.GroupBox();
            this.m_panelRx = new System.Windows.Forms.Panel();
            this.m_lblRxBitExtension = new System.Windows.Forms.Label();
            this.m_chbRxUnderflowInt = new System.Windows.Forms.CheckBox();
            this.m_lblRxInterrupts = new System.Windows.Forms.Label();
            this.m_cbRxBitExtension = new System.Windows.Forms.ComboBox();
            this.m_chbRxOverflowInt = new System.Windows.Forms.CheckBox();
            this.m_chbRxFullInt = new System.Windows.Forms.CheckBox();
            this.m_lblRxFrameRateText = new System.Windows.Forms.Label();
            this.m_lblRxFrameRateValue = new System.Windows.Forms.Label();
            this.m_chbRxTriggerInt = new System.Windows.Forms.CheckBox();
            this.m_chbRxNotEmptyInt = new System.Windows.Forms.CheckBox();
            this.m_lblRxChannelLength = new System.Windows.Forms.Label();
            this.m_cbRxChannelLength = new System.Windows.Forms.ComboBox();
            this.m_chbRxDmaTrigger = new System.Windows.Forms.CheckBox();
            this.m_cbRxWordLength = new System.Windows.Forms.ComboBox();
            this.m_lblRxFifoTriggerLevel = new System.Windows.Forms.Label();
            this.m_numRxFifoTriggerLevel = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
            this.m_lblRxWordLength = new System.Windows.Forms.Label();
            this.m_chbEnableRx = new System.Windows.Forms.CheckBox();
            this.m_lblBitRateValue = new System.Windows.Forms.Label();
            this.m_lblBitRateText = new System.Windows.Forms.Label();
            this.m_gbTx.SuspendLayout();
            this.m_panelTx.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTxFifoTriggerLevel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClockDivider)).BeginInit();
            this.m_gbRx.SuspendLayout();
            this.m_panelRx.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRxFifoTriggerLevel)).BeginInit();
            this.SuspendLayout();
            // 
            // m_gbTx
            // 
            this.m_gbTx.Controls.Add(this.m_chbEnableTx);
            this.m_gbTx.Controls.Add(this.m_panelTx);
            this.m_gbTx.Location = new System.Drawing.Point(3, 60);
            this.m_gbTx.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_gbTx.Name = "m_gbTx";
            this.m_gbTx.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_gbTx.Size = new System.Drawing.Size(322, 348);
            this.m_gbTx.TabIndex = 2;
            this.m_gbTx.TabStop = false;
            // 
            // m_panelTx
            // 
            this.m_panelTx.Controls.Add(this.m_lblTxChannelLength);
            this.m_panelTx.Controls.Add(this.m_cbTxChannelLength);
            this.m_panelTx.Controls.Add(this.m_cbTxWordLength);
            this.m_panelTx.Controls.Add(this.m_lblTxFrameRateText);
            this.m_panelTx.Controls.Add(this.m_numTxFifoTriggerLevel);
            this.m_panelTx.Controls.Add(this.m_lblTxInterrupts);
            this.m_panelTx.Controls.Add(this.m_lblTxWordLength);
            this.m_panelTx.Controls.Add(this.m_chbTxUnderflowInt);
            this.m_panelTx.Controls.Add(this.m_lblTxOverheadValue);
            this.m_panelTx.Controls.Add(this.m_lblTxFifoTriggerLevel);
            this.m_panelTx.Controls.Add(this.m_chbTxNotFullInt);
            this.m_panelTx.Controls.Add(this.m_chbTxOverflowInt);
            this.m_panelTx.Controls.Add(this.m_lblTxFrameRateValue);
            this.m_panelTx.Controls.Add(this.m_chbTxDmaTrigger);
            this.m_panelTx.Controls.Add(this.m_chbTxTriggerInt);
            this.m_panelTx.Controls.Add(this.m_cbTxOverheadValue);
            this.m_panelTx.Controls.Add(this.m_chbTxEmptyInt);
            this.m_panelTx.Location = new System.Drawing.Point(5, 23);
            this.m_panelTx.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_panelTx.Name = "m_panelTx";
            this.m_panelTx.Size = new System.Drawing.Size(311, 321);
            this.m_panelTx.TabIndex = 1;
            // 
            // m_lblTxChannelLength
            // 
            this.m_lblTxChannelLength.AutoSize = true;
            this.m_lblTxChannelLength.Location = new System.Drawing.Point(3, 6);
            this.m_lblTxChannelLength.Name = "m_lblTxChannelLength";
            this.m_lblTxChannelLength.Size = new System.Drawing.Size(107, 17);
            this.m_lblTxChannelLength.TabIndex = 61;
            this.m_lblTxChannelLength.Text = "Channel length:";
            // 
            // m_cbTxChannelLength
            // 
            this.m_cbTxChannelLength.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxChannelLength.FormattingEnabled = true;
            this.m_cbTxChannelLength.Items.AddRange(new object[] {
            "8",
            "16",
            "18",
            "20",
            "24",
            "32"});
            this.m_cbTxChannelLength.Location = new System.Drawing.Point(146, 3);
            this.m_cbTxChannelLength.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_cbTxChannelLength.Name = "m_cbTxChannelLength";
            this.m_cbTxChannelLength.Size = new System.Drawing.Size(124, 24);
            this.m_cbTxChannelLength.TabIndex = 2;
            // 
            // m_cbTxWordLength
            // 
            this.m_cbTxWordLength.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxWordLength.FormattingEnabled = true;
            this.m_cbTxWordLength.Items.AddRange(new object[] {
            "8",
            "16",
            "18",
            "20",
            "24",
            "32"});
            this.m_cbTxWordLength.Location = new System.Drawing.Point(146, 31);
            this.m_cbTxWordLength.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_cbTxWordLength.Name = "m_cbTxWordLength";
            this.m_cbTxWordLength.Size = new System.Drawing.Size(124, 24);
            this.m_cbTxWordLength.TabIndex = 3;
            // 
            // m_lblTxFrameRateText
            // 
            this.m_lblTxFrameRateText.AutoSize = true;
            this.m_lblTxFrameRateText.Location = new System.Drawing.Point(3, 58);
            this.m_lblTxFrameRateText.Name = "m_lblTxFrameRateText";
            this.m_lblTxFrameRateText.Size = new System.Drawing.Size(124, 17);
            this.m_lblTxFrameRateText.TabIndex = 84;
            this.m_lblTxFrameRateText.Text = "Frame rate (ksps):";
            // 
            // m_numTxFifoTriggerLevel
            // 
            this.m_numTxFifoTriggerLevel.Location = new System.Drawing.Point(146, 108);
            this.m_numTxFifoTriggerLevel.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_numTxFifoTriggerLevel.Name = "m_numTxFifoTriggerLevel";
            this.m_numTxFifoTriggerLevel.Size = new System.Drawing.Size(124, 22);
            this.m_numTxFifoTriggerLevel.TabIndex = 9;
            this.m_numTxFifoTriggerLevel.UserMaximum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.m_numTxFifoTriggerLevel.UserMinimum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            // 
            // m_lblTxInterrupts
            // 
            this.m_lblTxInterrupts.AutoSize = true;
            this.m_lblTxInterrupts.Location = new System.Drawing.Point(3, 166);
            this.m_lblTxInterrupts.Name = "m_lblTxInterrupts";
            this.m_lblTxInterrupts.Size = new System.Drawing.Size(72, 17);
            this.m_lblTxInterrupts.TabIndex = 79;
            this.m_lblTxInterrupts.Text = "Interrupts:";
            // 
            // m_lblTxWordLength
            // 
            this.m_lblTxWordLength.AutoSize = true;
            this.m_lblTxWordLength.Location = new System.Drawing.Point(3, 32);
            this.m_lblTxWordLength.Name = "m_lblTxWordLength";
            this.m_lblTxWordLength.Size = new System.Drawing.Size(89, 17);
            this.m_lblTxWordLength.TabIndex = 63;
            this.m_lblTxWordLength.Text = "Word length:";
            // 
            // m_chbTxUnderflowInt
            // 
            this.m_chbTxUnderflowInt.AutoSize = true;
            this.m_chbTxUnderflowInt.Location = new System.Drawing.Point(16, 289);
            this.m_chbTxUnderflowInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbTxUnderflowInt.Name = "m_chbTxUnderflowInt";
            this.m_chbTxUnderflowInt.Size = new System.Drawing.Size(93, 21);
            this.m_chbTxUnderflowInt.TabIndex = 15;
            this.m_chbTxUnderflowInt.Text = "Underflow";
            this.m_chbTxUnderflowInt.UseVisualStyleBackColor = true;
            // 
            // m_lblTxOverheadValue
            // 
            this.m_lblTxOverheadValue.AutoSize = true;
            this.m_lblTxOverheadValue.Location = new System.Drawing.Point(3, 84);
            this.m_lblTxOverheadValue.Name = "m_lblTxOverheadValue";
            this.m_lblTxOverheadValue.Size = new System.Drawing.Size(113, 17);
            this.m_lblTxOverheadValue.TabIndex = 89;
            this.m_lblTxOverheadValue.Text = "Overhead value:";
            // 
            // m_lblTxFifoTriggerLevel
            // 
            this.m_lblTxFifoTriggerLevel.AutoSize = true;
            this.m_lblTxFifoTriggerLevel.Location = new System.Drawing.Point(3, 110);
            this.m_lblTxFifoTriggerLevel.Name = "m_lblTxFifoTriggerLevel";
            this.m_lblTxFifoTriggerLevel.Size = new System.Drawing.Size(120, 17);
            this.m_lblTxFifoTriggerLevel.TabIndex = 77;
            this.m_lblTxFifoTriggerLevel.Text = "FIFO trigger level:";
            // 
            // m_chbTxNotFullInt
            // 
            this.m_chbTxNotFullInt.AutoSize = true;
            this.m_chbTxNotFullInt.Location = new System.Drawing.Point(16, 214);
            this.m_chbTxNotFullInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbTxNotFullInt.Name = "m_chbTxNotFullInt";
            this.m_chbTxNotFullInt.Size = new System.Drawing.Size(74, 21);
            this.m_chbTxNotFullInt.TabIndex = 12;
            this.m_chbTxNotFullInt.Text = "Not full";
            this.m_chbTxNotFullInt.UseVisualStyleBackColor = true;
            // 
            // m_chbTxOverflowInt
            // 
            this.m_chbTxOverflowInt.AutoSize = true;
            this.m_chbTxOverflowInt.Location = new System.Drawing.Point(16, 264);
            this.m_chbTxOverflowInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbTxOverflowInt.Name = "m_chbTxOverflowInt";
            this.m_chbTxOverflowInt.Size = new System.Drawing.Size(85, 21);
            this.m_chbTxOverflowInt.TabIndex = 14;
            this.m_chbTxOverflowInt.Text = "Overflow";
            this.m_chbTxOverflowInt.UseVisualStyleBackColor = true;
            // 
            // m_lblTxFrameRateValue
            // 
            this.m_lblTxFrameRateValue.AutoSize = true;
            this.m_lblTxFrameRateValue.Location = new System.Drawing.Point(143, 59);
            this.m_lblTxFrameRateValue.Name = "m_lblTxFrameRateValue";
            this.m_lblTxFrameRateValue.Size = new System.Drawing.Size(66, 17);
            this.m_lblTxFrameRateValue.TabIndex = 95;
            this.m_lblTxFrameRateValue.Text = "Unknown";
            // 
            // m_chbTxDmaTrigger
            // 
            this.m_chbTxDmaTrigger.AutoSize = true;
            this.m_chbTxDmaTrigger.Location = new System.Drawing.Point(6, 136);
            this.m_chbTxDmaTrigger.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbTxDmaTrigger.Name = "m_chbTxDmaTrigger";
            this.m_chbTxDmaTrigger.Size = new System.Drawing.Size(105, 21);
            this.m_chbTxDmaTrigger.TabIndex = 10;
            this.m_chbTxDmaTrigger.Text = "DMA trigger";
            this.m_chbTxDmaTrigger.UseVisualStyleBackColor = true;
            // 
            // m_chbTxTriggerInt
            // 
            this.m_chbTxTriggerInt.AutoSize = true;
            this.m_chbTxTriggerInt.Location = new System.Drawing.Point(16, 189);
            this.m_chbTxTriggerInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbTxTriggerInt.Name = "m_chbTxTriggerInt";
            this.m_chbTxTriggerInt.Size = new System.Drawing.Size(76, 21);
            this.m_chbTxTriggerInt.TabIndex = 11;
            this.m_chbTxTriggerInt.Text = "Trigger";
            this.m_chbTxTriggerInt.UseVisualStyleBackColor = true;
            // 
            // m_cbTxOverheadValue
            // 
            this.m_cbTxOverheadValue.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxOverheadValue.FormattingEnabled = true;
            this.m_cbTxOverheadValue.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbTxOverheadValue.Location = new System.Drawing.Point(146, 80);
            this.m_cbTxOverheadValue.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_cbTxOverheadValue.Name = "m_cbTxOverheadValue";
            this.m_cbTxOverheadValue.Size = new System.Drawing.Size(124, 24);
            this.m_cbTxOverheadValue.TabIndex = 4;
            // 
            // m_chbTxEmptyInt
            // 
            this.m_chbTxEmptyInt.AutoSize = true;
            this.m_chbTxEmptyInt.Location = new System.Drawing.Point(16, 239);
            this.m_chbTxEmptyInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbTxEmptyInt.Name = "m_chbTxEmptyInt";
            this.m_chbTxEmptyInt.Size = new System.Drawing.Size(69, 21);
            this.m_chbTxEmptyInt.TabIndex = 13;
            this.m_chbTxEmptyInt.Text = "Empty";
            this.m_chbTxEmptyInt.UseVisualStyleBackColor = true;
            // 
            // m_chbEnableTx
            // 
            this.m_chbEnableTx.AutoSize = true;
            this.m_chbEnableTx.Location = new System.Drawing.Point(11, 0);
            this.m_chbEnableTx.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbEnableTx.Name = "m_chbEnableTx";
            this.m_chbEnableTx.Size = new System.Drawing.Size(48, 21);
            this.m_chbEnableTx.TabIndex = 0;
            this.m_chbEnableTx.Text = "TX";
            this.m_chbEnableTx.UseVisualStyleBackColor = true;
            // 
            // m_chbClockFromTerminal
            // 
            this.m_chbClockFromTerminal.AutoSize = true;
            this.m_chbClockFromTerminal.Location = new System.Drawing.Point(3, 5);
            this.m_chbClockFromTerminal.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbClockFromTerminal.Name = "m_chbClockFromTerminal";
            this.m_chbClockFromTerminal.Size = new System.Drawing.Size(150, 21);
            this.m_chbClockFromTerminal.TabIndex = 0;
            this.m_chbClockFromTerminal.Text = "Clock from terminal";
            this.m_chbClockFromTerminal.UseVisualStyleBackColor = true;
            // 
            // m_lblInputClockText
            // 
            this.m_lblInputClockText.AutoSize = true;
            this.m_lblInputClockText.Location = new System.Drawing.Point(189, 6);
            this.m_lblInputClockText.Name = "m_lblInputClockText";
            this.m_lblInputClockText.Size = new System.Drawing.Size(184, 17);
            this.m_lblInputClockText.TabIndex = 89;
            this.m_lblInputClockText.Text = "Input clock frequency (kHz):";
            // 
            // m_lblInputClockValue
            // 
            this.m_lblInputClockValue.AutoSize = true;
            this.m_lblInputClockValue.Location = new System.Drawing.Point(376, 6);
            this.m_lblInputClockValue.Name = "m_lblInputClockValue";
            this.m_lblInputClockValue.Size = new System.Drawing.Size(66, 17);
            this.m_lblInputClockValue.TabIndex = 90;
            this.m_lblInputClockValue.Text = "Unknown";
            // 
            // m_lblClockDivider
            // 
            this.m_lblClockDivider.AutoSize = true;
            this.m_lblClockDivider.Location = new System.Drawing.Point(0, 34);
            this.m_lblClockDivider.Name = "m_lblClockDivider";
            this.m_lblClockDivider.Size = new System.Drawing.Size(92, 17);
            this.m_lblClockDivider.TabIndex = 91;
            this.m_lblClockDivider.Text = "Clock divider:";
            // 
            // m_numClockDivider
            // 
            this.m_numClockDivider.Location = new System.Drawing.Point(99, 31);
            this.m_numClockDivider.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_numClockDivider.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.m_numClockDivider.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_numClockDivider.Name = "m_numClockDivider";
            this.m_numClockDivider.Size = new System.Drawing.Size(59, 22);
            this.m_numClockDivider.TabIndex = 1;
            this.m_numClockDivider.UserMaximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.m_numClockDivider.UserMinimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_numClockDivider.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // m_gbRx
            // 
            this.m_gbRx.Controls.Add(this.m_chbEnableRx);
            this.m_gbRx.Controls.Add(this.m_panelRx);
            this.m_gbRx.Location = new System.Drawing.Point(326, 60);
            this.m_gbRx.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_gbRx.Name = "m_gbRx";
            this.m_gbRx.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_gbRx.Size = new System.Drawing.Size(322, 348);
            this.m_gbRx.TabIndex = 3;
            this.m_gbRx.TabStop = false;
            // 
            // m_panelRx
            // 
            this.m_panelRx.Controls.Add(this.m_lblRxBitExtension);
            this.m_panelRx.Controls.Add(this.m_chbRxUnderflowInt);
            this.m_panelRx.Controls.Add(this.m_lblRxInterrupts);
            this.m_panelRx.Controls.Add(this.m_cbRxBitExtension);
            this.m_panelRx.Controls.Add(this.m_chbRxOverflowInt);
            this.m_panelRx.Controls.Add(this.m_chbRxFullInt);
            this.m_panelRx.Controls.Add(this.m_lblRxFrameRateText);
            this.m_panelRx.Controls.Add(this.m_lblRxFrameRateValue);
            this.m_panelRx.Controls.Add(this.m_chbRxTriggerInt);
            this.m_panelRx.Controls.Add(this.m_chbRxNotEmptyInt);
            this.m_panelRx.Controls.Add(this.m_lblRxChannelLength);
            this.m_panelRx.Controls.Add(this.m_cbRxChannelLength);
            this.m_panelRx.Controls.Add(this.m_chbRxDmaTrigger);
            this.m_panelRx.Controls.Add(this.m_cbRxWordLength);
            this.m_panelRx.Controls.Add(this.m_lblRxFifoTriggerLevel);
            this.m_panelRx.Controls.Add(this.m_numRxFifoTriggerLevel);
            this.m_panelRx.Controls.Add(this.m_lblRxWordLength);
            this.m_panelRx.Location = new System.Drawing.Point(5, 23);
            this.m_panelRx.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_panelRx.Name = "m_panelRx";
            this.m_panelRx.Size = new System.Drawing.Size(311, 321);
            this.m_panelRx.TabIndex = 2;
            // 
            // m_lblRxBitExtension
            // 
            this.m_lblRxBitExtension.AutoSize = true;
            this.m_lblRxBitExtension.Location = new System.Drawing.Point(3, 84);
            this.m_lblRxBitExtension.Name = "m_lblRxBitExtension";
            this.m_lblRxBitExtension.Size = new System.Drawing.Size(92, 17);
            this.m_lblRxBitExtension.TabIndex = 89;
            this.m_lblRxBitExtension.Text = "Bit extension:";
            // 
            // m_chbRxUnderflowInt
            // 
            this.m_chbRxUnderflowInt.AutoSize = true;
            this.m_chbRxUnderflowInt.Location = new System.Drawing.Point(16, 289);
            this.m_chbRxUnderflowInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbRxUnderflowInt.Name = "m_chbRxUnderflowInt";
            this.m_chbRxUnderflowInt.Size = new System.Drawing.Size(93, 21);
            this.m_chbRxUnderflowInt.TabIndex = 15;
            this.m_chbRxUnderflowInt.Text = "Underflow";
            this.m_chbRxUnderflowInt.UseVisualStyleBackColor = true;
            // 
            // m_lblRxInterrupts
            // 
            this.m_lblRxInterrupts.AutoSize = true;
            this.m_lblRxInterrupts.Location = new System.Drawing.Point(3, 166);
            this.m_lblRxInterrupts.Name = "m_lblRxInterrupts";
            this.m_lblRxInterrupts.Size = new System.Drawing.Size(72, 17);
            this.m_lblRxInterrupts.TabIndex = 79;
            this.m_lblRxInterrupts.Text = "Interrupts:";
            // 
            // m_cbRxBitExtension
            // 
            this.m_cbRxBitExtension.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxBitExtension.FormattingEnabled = true;
            this.m_cbRxBitExtension.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxBitExtension.Location = new System.Drawing.Point(146, 80);
            this.m_cbRxBitExtension.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_cbRxBitExtension.Name = "m_cbRxBitExtension";
            this.m_cbRxBitExtension.Size = new System.Drawing.Size(124, 24);
            this.m_cbRxBitExtension.TabIndex = 4;
            // 
            // m_chbRxOverflowInt
            // 
            this.m_chbRxOverflowInt.AutoSize = true;
            this.m_chbRxOverflowInt.Location = new System.Drawing.Point(16, 264);
            this.m_chbRxOverflowInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbRxOverflowInt.Name = "m_chbRxOverflowInt";
            this.m_chbRxOverflowInt.Size = new System.Drawing.Size(85, 21);
            this.m_chbRxOverflowInt.TabIndex = 14;
            this.m_chbRxOverflowInt.Text = "Overflow";
            this.m_chbRxOverflowInt.UseVisualStyleBackColor = true;
            // 
            // m_chbRxFullInt
            // 
            this.m_chbRxFullInt.AutoSize = true;
            this.m_chbRxFullInt.Location = new System.Drawing.Point(16, 239);
            this.m_chbRxFullInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbRxFullInt.Name = "m_chbRxFullInt";
            this.m_chbRxFullInt.Size = new System.Drawing.Size(52, 21);
            this.m_chbRxFullInt.TabIndex = 13;
            this.m_chbRxFullInt.Text = "Full";
            this.m_chbRxFullInt.UseVisualStyleBackColor = true;
            // 
            // m_lblRxFrameRateText
            // 
            this.m_lblRxFrameRateText.AutoSize = true;
            this.m_lblRxFrameRateText.Location = new System.Drawing.Point(3, 58);
            this.m_lblRxFrameRateText.Name = "m_lblRxFrameRateText";
            this.m_lblRxFrameRateText.Size = new System.Drawing.Size(124, 17);
            this.m_lblRxFrameRateText.TabIndex = 84;
            this.m_lblRxFrameRateText.Text = "Frame rate (ksps):";
            // 
            // m_lblRxFrameRateValue
            // 
            this.m_lblRxFrameRateValue.AutoSize = true;
            this.m_lblRxFrameRateValue.Location = new System.Drawing.Point(143, 59);
            this.m_lblRxFrameRateValue.Name = "m_lblRxFrameRateValue";
            this.m_lblRxFrameRateValue.Size = new System.Drawing.Size(66, 17);
            this.m_lblRxFrameRateValue.TabIndex = 95;
            this.m_lblRxFrameRateValue.Text = "Unknown";
            // 
            // m_chbRxTriggerInt
            // 
            this.m_chbRxTriggerInt.AutoSize = true;
            this.m_chbRxTriggerInt.Location = new System.Drawing.Point(16, 189);
            this.m_chbRxTriggerInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbRxTriggerInt.Name = "m_chbRxTriggerInt";
            this.m_chbRxTriggerInt.Size = new System.Drawing.Size(76, 21);
            this.m_chbRxTriggerInt.TabIndex = 11;
            this.m_chbRxTriggerInt.Text = "Trigger";
            this.m_chbRxTriggerInt.UseVisualStyleBackColor = true;
            // 
            // m_chbRxNotEmptyInt
            // 
            this.m_chbRxNotEmptyInt.AutoSize = true;
            this.m_chbRxNotEmptyInt.Location = new System.Drawing.Point(16, 214);
            this.m_chbRxNotEmptyInt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbRxNotEmptyInt.Name = "m_chbRxNotEmptyInt";
            this.m_chbRxNotEmptyInt.Size = new System.Drawing.Size(94, 21);
            this.m_chbRxNotEmptyInt.TabIndex = 12;
            this.m_chbRxNotEmptyInt.Text = "Not empty";
            this.m_chbRxNotEmptyInt.UseVisualStyleBackColor = true;
            // 
            // m_lblRxChannelLength
            // 
            this.m_lblRxChannelLength.AutoSize = true;
            this.m_lblRxChannelLength.Location = new System.Drawing.Point(3, 6);
            this.m_lblRxChannelLength.Name = "m_lblRxChannelLength";
            this.m_lblRxChannelLength.Size = new System.Drawing.Size(107, 17);
            this.m_lblRxChannelLength.TabIndex = 61;
            this.m_lblRxChannelLength.Text = "Channel length:";
            // 
            // m_cbRxChannelLength
            // 
            this.m_cbRxChannelLength.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxChannelLength.FormattingEnabled = true;
            this.m_cbRxChannelLength.Items.AddRange(new object[] {
            "8",
            "16",
            "18",
            "20",
            "24",
            "32"});
            this.m_cbRxChannelLength.Location = new System.Drawing.Point(146, 3);
            this.m_cbRxChannelLength.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_cbRxChannelLength.Name = "m_cbRxChannelLength";
            this.m_cbRxChannelLength.Size = new System.Drawing.Size(124, 24);
            this.m_cbRxChannelLength.TabIndex = 2;
            // 
            // m_chbRxDmaTrigger
            // 
            this.m_chbRxDmaTrigger.AutoSize = true;
            this.m_chbRxDmaTrigger.Location = new System.Drawing.Point(6, 136);
            this.m_chbRxDmaTrigger.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbRxDmaTrigger.Name = "m_chbRxDmaTrigger";
            this.m_chbRxDmaTrigger.Size = new System.Drawing.Size(105, 21);
            this.m_chbRxDmaTrigger.TabIndex = 10;
            this.m_chbRxDmaTrigger.Text = "DMA trigger";
            this.m_chbRxDmaTrigger.UseVisualStyleBackColor = true;
            // 
            // m_cbRxWordLength
            // 
            this.m_cbRxWordLength.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxWordLength.FormattingEnabled = true;
            this.m_cbRxWordLength.Items.AddRange(new object[] {
            "8",
            "16",
            "18",
            "20",
            "24",
            "32"});
            this.m_cbRxWordLength.Location = new System.Drawing.Point(146, 31);
            this.m_cbRxWordLength.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_cbRxWordLength.Name = "m_cbRxWordLength";
            this.m_cbRxWordLength.Size = new System.Drawing.Size(124, 24);
            this.m_cbRxWordLength.TabIndex = 3;
            // 
            // m_lblRxFifoTriggerLevel
            // 
            this.m_lblRxFifoTriggerLevel.AutoSize = true;
            this.m_lblRxFifoTriggerLevel.Location = new System.Drawing.Point(3, 110);
            this.m_lblRxFifoTriggerLevel.Name = "m_lblRxFifoTriggerLevel";
            this.m_lblRxFifoTriggerLevel.Size = new System.Drawing.Size(120, 17);
            this.m_lblRxFifoTriggerLevel.TabIndex = 77;
            this.m_lblRxFifoTriggerLevel.Text = "FIFO trigger level:";
            // 
            // m_numRxFifoTriggerLevel
            // 
            this.m_numRxFifoTriggerLevel.Location = new System.Drawing.Point(146, 108);
            this.m_numRxFifoTriggerLevel.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_numRxFifoTriggerLevel.Name = "m_numRxFifoTriggerLevel";
            this.m_numRxFifoTriggerLevel.Size = new System.Drawing.Size(124, 22);
            this.m_numRxFifoTriggerLevel.TabIndex = 9;
            this.m_numRxFifoTriggerLevel.UserMaximum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.m_numRxFifoTriggerLevel.UserMinimum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            // 
            // m_lblRxWordLength
            // 
            this.m_lblRxWordLength.AutoSize = true;
            this.m_lblRxWordLength.Location = new System.Drawing.Point(3, 32);
            this.m_lblRxWordLength.Name = "m_lblRxWordLength";
            this.m_lblRxWordLength.Size = new System.Drawing.Size(89, 17);
            this.m_lblRxWordLength.TabIndex = 63;
            this.m_lblRxWordLength.Text = "Word length:";
            // 
            // m_chbEnableRx
            // 
            this.m_chbEnableRx.AutoSize = true;
            this.m_chbEnableRx.Location = new System.Drawing.Point(11, 0);
            this.m_chbEnableRx.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbEnableRx.Name = "m_chbEnableRx";
            this.m_chbEnableRx.Size = new System.Drawing.Size(49, 21);
            this.m_chbEnableRx.TabIndex = 0;
            this.m_chbEnableRx.Text = "RX";
            this.m_chbEnableRx.UseVisualStyleBackColor = true;
            // 
            // m_lblBitRateValue
            // 
            this.m_lblBitRateValue.AutoSize = true;
            this.m_lblBitRateValue.Location = new System.Drawing.Point(376, 34);
            this.m_lblBitRateValue.Name = "m_lblBitRateValue";
            this.m_lblBitRateValue.Size = new System.Drawing.Size(66, 17);
            this.m_lblBitRateValue.TabIndex = 115;
            this.m_lblBitRateValue.Text = "Unknown";
            // 
            // m_lblBitRateText
            // 
            this.m_lblBitRateText.AutoSize = true;
            this.m_lblBitRateText.Location = new System.Drawing.Point(189, 34);
            this.m_lblBitRateText.Name = "m_lblBitRateText";
            this.m_lblBitRateText.Size = new System.Drawing.Size(101, 17);
            this.m_lblBitRateText.TabIndex = 114;
            this.m_lblBitRateText.Text = "Bit rate (kbps):";
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_lblBitRateValue);
            this.Controls.Add(this.m_lblBitRateText);
            this.Controls.Add(this.m_gbRx);
            this.Controls.Add(this.m_lblClockDivider);
            this.Controls.Add(this.m_numClockDivider);
            this.Controls.Add(this.m_lblInputClockValue);
            this.Controls.Add(this.m_lblInputClockText);
            this.Controls.Add(this.m_chbClockFromTerminal);
            this.Controls.Add(this.m_gbTx);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(651, 408);
            this.m_gbTx.ResumeLayout(false);
            this.m_gbTx.PerformLayout();
            this.m_panelTx.ResumeLayout(false);
            this.m_panelTx.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTxFifoTriggerLevel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClockDivider)).EndInit();
            this.m_gbRx.ResumeLayout(false);
            this.m_gbRx.PerformLayout();
            this.m_panelRx.ResumeLayout(false);
            this.m_panelRx.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRxFifoTriggerLevel)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.GroupBox m_gbTx;
        private System.Windows.Forms.Label m_lblTxInterrupts;
        private System.Windows.Forms.Label m_lblTxChannelLength;
        private System.Windows.Forms.ComboBox m_cbTxChannelLength;
        private System.Windows.Forms.ComboBox m_cbTxWordLength;
        private CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numTxFifoTriggerLevel;
        private System.Windows.Forms.Label m_lblTxWordLength;
        private System.Windows.Forms.CheckBox m_chbTxUnderflowInt;
        private System.Windows.Forms.Label m_lblTxFifoTriggerLevel;
        private System.Windows.Forms.CheckBox m_chbTxOverflowInt;
        private System.Windows.Forms.CheckBox m_chbTxDmaTrigger;
        private System.Windows.Forms.CheckBox m_chbTxEmptyInt;
        private System.Windows.Forms.CheckBox m_chbTxTriggerInt;
        private System.Windows.Forms.CheckBox m_chbTxNotFullInt;
        private System.Windows.Forms.Label m_lblTxFrameRateText;
        private System.Windows.Forms.ComboBox m_cbTxOverheadValue;
        private System.Windows.Forms.Label m_lblTxOverheadValue;
        private System.Windows.Forms.CheckBox m_chbClockFromTerminal;
        private System.Windows.Forms.Label m_lblInputClockText;
        private System.Windows.Forms.Label m_lblInputClockValue;
        private System.Windows.Forms.Label m_lblTxFrameRateValue;
        private System.Windows.Forms.Label m_lblClockDivider;
        CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numClockDivider;
        private System.Windows.Forms.GroupBox m_gbRx;
        private System.Windows.Forms.CheckBox m_chbRxUnderflowInt;
        private System.Windows.Forms.CheckBox m_chbRxOverflowInt;
        private System.Windows.Forms.CheckBox m_chbRxFullInt;
        private System.Windows.Forms.CheckBox m_chbRxTriggerInt;
        private System.Windows.Forms.CheckBox m_chbRxNotEmptyInt;
        private System.Windows.Forms.Label m_lblRxFrameRateValue;
        private System.Windows.Forms.ComboBox m_cbRxBitExtension;
        private System.Windows.Forms.Label m_lblRxBitExtension;
        private System.Windows.Forms.Label m_lblRxInterrupts;
        private System.Windows.Forms.Label m_lblRxFrameRateText;
        private System.Windows.Forms.Label m_lblRxChannelLength;
        private System.Windows.Forms.ComboBox m_cbRxChannelLength;
        private System.Windows.Forms.ComboBox m_cbRxWordLength;
        private CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numRxFifoTriggerLevel;
        private System.Windows.Forms.Label m_lblRxWordLength;
        private System.Windows.Forms.Label m_lblRxFifoTriggerLevel;
        private System.Windows.Forms.CheckBox m_chbRxDmaTrigger;
        private System.Windows.Forms.CheckBox m_chbEnableTx;
        private System.Windows.Forms.CheckBox m_chbEnableRx;
        private System.Windows.Forms.Panel m_panelTx;
        private System.Windows.Forms.Panel m_panelRx;
        private System.Windows.Forms.Label m_lblBitRateValue;
        private System.Windows.Forms.Label m_lblBitRateText;
    }
}
