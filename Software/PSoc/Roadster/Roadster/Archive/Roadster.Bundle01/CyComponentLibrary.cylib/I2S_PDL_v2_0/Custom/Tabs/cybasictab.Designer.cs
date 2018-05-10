namespace I2S_PDL_v2_0.Tabs
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
            if (disposing)
            {
               UnsubscribeEvents();
            }
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
            this.m_cbTxOutputClockPolarity = new System.Windows.Forms.ComboBox();
            this.m_lblTxOutputClockPolarity = new System.Windows.Forms.Label();
            this.m_cbTxInputClockPolarity = new System.Windows.Forms.ComboBox();
            this.m_lblTxInputClockPolarity = new System.Windows.Forms.Label();
            this.m_lblTxBitRateValue = new System.Windows.Forms.Label();
            this.m_lblTxBitRateText = new System.Windows.Forms.Label();
            this.m_cbTxSdo = new System.Windows.Forms.ComboBox();
            this.m_lblTxChannelLength = new System.Windows.Forms.Label();
            this.m_cbTxChannelLength = new System.Windows.Forms.ComboBox();
            this.m_lblTxSdo = new System.Windows.Forms.Label();
            this.m_lblTxChannels = new System.Windows.Forms.Label();
            this.m_cbTxWordLength = new System.Windows.Forms.ComboBox();
            this.m_cbTxWsPulseWidth = new System.Windows.Forms.ComboBox();
            this.m_lblTxFrameRateText = new System.Windows.Forms.Label();
            this.m_numTxFifoTriggerLevel = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
            this.m_lblTxWsPulseWidth = new System.Windows.Forms.Label();
            this.m_cbTxChannels = new System.Windows.Forms.ComboBox();
            this.m_chbTxWatchdogInt = new System.Windows.Forms.CheckBox();
            this.m_cbTxAlignment = new System.Windows.Forms.ComboBox();
            this.m_lblTxInterrupts = new System.Windows.Forms.Label();
            this.m_lblTxWordLength = new System.Windows.Forms.Label();
            this.m_lblTxAlignment = new System.Windows.Forms.Label();
            this.m_chbTxUnderflowInt = new System.Windows.Forms.CheckBox();
            this.m_cbTxMode = new System.Windows.Forms.ComboBox();
            this.m_lblTxOverheadValue = new System.Windows.Forms.Label();
            this.m_lblTxFifoTriggerLevel = new System.Windows.Forms.Label();
            this.m_lblTxMode = new System.Windows.Forms.Label();
            this.m_numTxWatchdogValue = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
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
            this.m_cbRxOutputClockPolarity = new System.Windows.Forms.ComboBox();
            this.m_lblRxOutputClockPolarity = new System.Windows.Forms.Label();
            this.m_cbRxInputClockPolarity = new System.Windows.Forms.ComboBox();
            this.m_lblRxInputClockPolarity = new System.Windows.Forms.Label();
            this.m_lblRxBitRateValue = new System.Windows.Forms.Label();
            this.m_lblRxBitRateText = new System.Windows.Forms.Label();
            this.m_lblRxSignExtension = new System.Windows.Forms.Label();
            this.m_chbRxWatchdogInt = new System.Windows.Forms.CheckBox();
            this.m_numRxWatchdogValue = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
            this.m_chbRxUnderflowInt = new System.Windows.Forms.CheckBox();
            this.m_lblRxInterrupts = new System.Windows.Forms.Label();
            this.m_cbRxSignExtension = new System.Windows.Forms.ComboBox();
            this.m_chbRxOverflowInt = new System.Windows.Forms.CheckBox();
            this.m_cbRxChannels = new System.Windows.Forms.ComboBox();
            this.m_chbRxFullInt = new System.Windows.Forms.CheckBox();
            this.m_lblRxFrameRateText = new System.Windows.Forms.Label();
            this.m_lblRxFrameRateValue = new System.Windows.Forms.Label();
            this.m_chbRxTriggerInt = new System.Windows.Forms.CheckBox();
            this.m_lblRxChannels = new System.Windows.Forms.Label();
            this.m_lblRxMode = new System.Windows.Forms.Label();
            this.m_chbRxNotEmptyInt = new System.Windows.Forms.CheckBox();
            this.m_lblRxChannelLength = new System.Windows.Forms.Label();
            this.m_cbRxMode = new System.Windows.Forms.ComboBox();
            this.m_cbRxSdi = new System.Windows.Forms.ComboBox();
            this.m_cbRxChannelLength = new System.Windows.Forms.ComboBox();
            this.m_chbRxDmaTrigger = new System.Windows.Forms.CheckBox();
            this.m_lblRxAlignment = new System.Windows.Forms.Label();
            this.m_lblRxSdi = new System.Windows.Forms.Label();
            this.m_cbRxWordLength = new System.Windows.Forms.ComboBox();
            this.m_lblRxFifoTriggerLevel = new System.Windows.Forms.Label();
            this.m_cbRxAlignment = new System.Windows.Forms.ComboBox();
            this.m_cbRxWsPulseWidth = new System.Windows.Forms.ComboBox();
            this.m_numRxFifoTriggerLevel = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
            this.m_lblRxWordLength = new System.Windows.Forms.Label();
            this.m_lblRxWsPulseWidth = new System.Windows.Forms.Label();
            this.m_chbEnableRx = new System.Windows.Forms.CheckBox();
            this.m_gbTx.SuspendLayout();
            this.m_panelTx.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTxFifoTriggerLevel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTxWatchdogValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClockDivider)).BeginInit();
            this.m_gbRx.SuspendLayout();
            this.m_panelRx.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRxWatchdogValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRxFifoTriggerLevel)).BeginInit();
            this.SuspendLayout();
            // 
            // m_gbTx
            // 
            this.m_gbTx.Controls.Add(this.m_panelTx);
            this.m_gbTx.Controls.Add(this.m_chbEnableTx);
            this.m_gbTx.Location = new System.Drawing.Point(2, 49);
            this.m_gbTx.Margin = new System.Windows.Forms.Padding(2);
            this.m_gbTx.Name = "m_gbTx";
            this.m_gbTx.Padding = new System.Windows.Forms.Padding(2);
            this.m_gbTx.Size = new System.Drawing.Size(266, 491);
            this.m_gbTx.TabIndex = 2;
            this.m_gbTx.TabStop = false;
            this.m_gbTx.Text = "           ";
            // 
            // m_panelTx
            // 
            this.m_panelTx.Controls.Add(this.m_cbTxOutputClockPolarity);
            this.m_panelTx.Controls.Add(this.m_lblTxOutputClockPolarity);
            this.m_panelTx.Controls.Add(this.m_cbTxInputClockPolarity);
            this.m_panelTx.Controls.Add(this.m_lblTxInputClockPolarity);
            this.m_panelTx.Controls.Add(this.m_lblTxBitRateValue);
            this.m_panelTx.Controls.Add(this.m_lblTxBitRateText);
            this.m_panelTx.Controls.Add(this.m_cbTxSdo);
            this.m_panelTx.Controls.Add(this.m_lblTxChannelLength);
            this.m_panelTx.Controls.Add(this.m_cbTxChannelLength);
            this.m_panelTx.Controls.Add(this.m_lblTxSdo);
            this.m_panelTx.Controls.Add(this.m_lblTxChannels);
            this.m_panelTx.Controls.Add(this.m_cbTxWordLength);
            this.m_panelTx.Controls.Add(this.m_cbTxWsPulseWidth);
            this.m_panelTx.Controls.Add(this.m_lblTxFrameRateText);
            this.m_panelTx.Controls.Add(this.m_numTxFifoTriggerLevel);
            this.m_panelTx.Controls.Add(this.m_lblTxWsPulseWidth);
            this.m_panelTx.Controls.Add(this.m_cbTxChannels);
            this.m_panelTx.Controls.Add(this.m_chbTxWatchdogInt);
            this.m_panelTx.Controls.Add(this.m_cbTxAlignment);
            this.m_panelTx.Controls.Add(this.m_lblTxInterrupts);
            this.m_panelTx.Controls.Add(this.m_lblTxWordLength);
            this.m_panelTx.Controls.Add(this.m_lblTxAlignment);
            this.m_panelTx.Controls.Add(this.m_chbTxUnderflowInt);
            this.m_panelTx.Controls.Add(this.m_cbTxMode);
            this.m_panelTx.Controls.Add(this.m_lblTxOverheadValue);
            this.m_panelTx.Controls.Add(this.m_lblTxFifoTriggerLevel);
            this.m_panelTx.Controls.Add(this.m_lblTxMode);
            this.m_panelTx.Controls.Add(this.m_numTxWatchdogValue);
            this.m_panelTx.Controls.Add(this.m_chbTxNotFullInt);
            this.m_panelTx.Controls.Add(this.m_chbTxOverflowInt);
            this.m_panelTx.Controls.Add(this.m_lblTxFrameRateValue);
            this.m_panelTx.Controls.Add(this.m_chbTxDmaTrigger);
            this.m_panelTx.Controls.Add(this.m_chbTxTriggerInt);
            this.m_panelTx.Controls.Add(this.m_cbTxOverheadValue);
            this.m_panelTx.Controls.Add(this.m_chbTxEmptyInt);
            this.m_panelTx.Location = new System.Drawing.Point(4, 19);
            this.m_panelTx.Margin = new System.Windows.Forms.Padding(2);
            this.m_panelTx.Name = "m_panelTx";
            this.m_panelTx.Size = new System.Drawing.Size(259, 469);
            this.m_panelTx.TabIndex = 1;
            // 
            // m_cbTxOutputClockPolarity
            // 
            this.m_cbTxOutputClockPolarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxOutputClockPolarity.FormattingEnabled = true;
            this.m_cbTxOutputClockPolarity.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbTxOutputClockPolarity.Location = new System.Drawing.Point(116, 243);
            this.m_cbTxOutputClockPolarity.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxOutputClockPolarity.Name = "m_cbTxOutputClockPolarity";
            this.m_cbTxOutputClockPolarity.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxOutputClockPolarity.TabIndex = 8;
            // 
            // m_lblTxOutputClockPolarity
            // 
            this.m_lblTxOutputClockPolarity.AutoSize = true;
            this.m_lblTxOutputClockPolarity.Location = new System.Drawing.Point(3, 245);
            this.m_lblTxOutputClockPolarity.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxOutputClockPolarity.Name = "m_lblTxOutputClockPolarity";
            this.m_lblTxOutputClockPolarity.Size = new System.Drawing.Size(107, 13);
            this.m_lblTxOutputClockPolarity.TabIndex = 120;
            this.m_lblTxOutputClockPolarity.Text = "Output clock polarity:";
            // 
            // m_cbTxInputClockPolarity
            // 
            this.m_cbTxInputClockPolarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxInputClockPolarity.FormattingEnabled = true;
            this.m_cbTxInputClockPolarity.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbTxInputClockPolarity.Location = new System.Drawing.Point(116, 243);
            this.m_cbTxInputClockPolarity.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxInputClockPolarity.Name = "m_cbTxInputClockPolarity";
            this.m_cbTxInputClockPolarity.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxInputClockPolarity.TabIndex = 8;
            // 
            // m_lblTxInputClockPolarity
            // 
            this.m_lblTxInputClockPolarity.AutoSize = true;
            this.m_lblTxInputClockPolarity.Location = new System.Drawing.Point(3, 245);
            this.m_lblTxInputClockPolarity.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxInputClockPolarity.Name = "m_lblTxInputClockPolarity";
            this.m_lblTxInputClockPolarity.Size = new System.Drawing.Size(99, 13);
            this.m_lblTxInputClockPolarity.TabIndex = 118;
            this.m_lblTxInputClockPolarity.Text = "Input clock polarity:";
            // 
            // m_lblTxBitRateValue
            // 
            this.m_lblTxBitRateValue.AutoSize = true;
            this.m_lblTxBitRateValue.Location = new System.Drawing.Point(113, 29);
            this.m_lblTxBitRateValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxBitRateValue.Name = "m_lblTxBitRateValue";
            this.m_lblTxBitRateValue.Size = new System.Drawing.Size(65, 13);
            this.m_lblTxBitRateValue.TabIndex = 113;
            this.m_lblTxBitRateValue.Text = "UNKNOWN";
            // 
            // m_lblTxBitRateText
            // 
            this.m_lblTxBitRateText.AutoSize = true;
            this.m_lblTxBitRateText.Location = new System.Drawing.Point(2, 29);
            this.m_lblTxBitRateText.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxBitRateText.Name = "m_lblTxBitRateText";
            this.m_lblTxBitRateText.Size = new System.Drawing.Size(75, 13);
            this.m_lblTxBitRateText.TabIndex = 112;
            this.m_lblTxBitRateText.Text = "Bit rate (kbps):";
            // 
            // m_cbTxSdo
            // 
            this.m_cbTxSdo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxSdo.FormattingEnabled = true;
            this.m_cbTxSdo.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbTxSdo.Location = new System.Drawing.Point(116, 219);
            this.m_cbTxSdo.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxSdo.Name = "m_cbTxSdo";
            this.m_cbTxSdo.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxSdo.TabIndex = 7;
            // 
            // m_lblTxChannelLength
            // 
            this.m_lblTxChannelLength.AutoSize = true;
            this.m_lblTxChannelLength.Location = new System.Drawing.Point(2, 102);
            this.m_lblTxChannelLength.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxChannelLength.Name = "m_lblTxChannelLength";
            this.m_lblTxChannelLength.Size = new System.Drawing.Size(81, 13);
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
            this.m_cbTxChannelLength.Location = new System.Drawing.Point(115, 99);
            this.m_cbTxChannelLength.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxChannelLength.Name = "m_cbTxChannelLength";
            this.m_cbTxChannelLength.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxChannelLength.TabIndex = 3;
            // 
            // m_lblTxSdo
            // 
            this.m_lblTxSdo.AutoSize = true;
            this.m_lblTxSdo.Location = new System.Drawing.Point(3, 221);
            this.m_lblTxSdo.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxSdo.Name = "m_lblTxSdo";
            this.m_lblTxSdo.Size = new System.Drawing.Size(95, 13);
            this.m_lblTxSdo.TabIndex = 103;
            this.m_lblTxSdo.Text = "SDO latching time:";
            // 
            // m_lblTxChannels
            // 
            this.m_lblTxChannels.AutoSize = true;
            this.m_lblTxChannels.Location = new System.Drawing.Point(2, 77);
            this.m_lblTxChannels.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxChannels.Name = "m_lblTxChannels";
            this.m_lblTxChannels.Size = new System.Drawing.Size(54, 13);
            this.m_lblTxChannels.TabIndex = 55;
            this.m_lblTxChannels.Text = "Channels:";
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
            this.m_cbTxWordLength.Location = new System.Drawing.Point(115, 124);
            this.m_cbTxWordLength.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxWordLength.Name = "m_cbTxWordLength";
            this.m_cbTxWordLength.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxWordLength.TabIndex = 4;
            // 
            // m_cbTxWsPulseWidth
            // 
            this.m_cbTxWsPulseWidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxWsPulseWidth.FormattingEnabled = true;
            this.m_cbTxWsPulseWidth.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbTxWsPulseWidth.Location = new System.Drawing.Point(116, 194);
            this.m_cbTxWsPulseWidth.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxWsPulseWidth.Name = "m_cbTxWsPulseWidth";
            this.m_cbTxWsPulseWidth.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxWsPulseWidth.TabIndex = 6;
            // 
            // m_lblTxFrameRateText
            // 
            this.m_lblTxFrameRateText.AutoSize = true;
            this.m_lblTxFrameRateText.Location = new System.Drawing.Point(2, 150);
            this.m_lblTxFrameRateText.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxFrameRateText.Name = "m_lblTxFrameRateText";
            this.m_lblTxFrameRateText.Size = new System.Drawing.Size(91, 13);
            this.m_lblTxFrameRateText.TabIndex = 84;
            this.m_lblTxFrameRateText.Text = "Frame rate (ksps):";
            // 
            // m_numTxFifoTriggerLevel
            // 
            this.m_numTxFifoTriggerLevel.Location = new System.Drawing.Point(115, 268);
            this.m_numTxFifoTriggerLevel.Margin = new System.Windows.Forms.Padding(2);
            this.m_numTxFifoTriggerLevel.Name = "m_numTxFifoTriggerLevel";
            this.m_numTxFifoTriggerLevel.Size = new System.Drawing.Size(122, 20);
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
            // m_lblTxWsPulseWidth
            // 
            this.m_lblTxWsPulseWidth.AutoSize = true;
            this.m_lblTxWsPulseWidth.Location = new System.Drawing.Point(3, 197);
            this.m_lblTxWsPulseWidth.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxWsPulseWidth.Name = "m_lblTxWsPulseWidth";
            this.m_lblTxWsPulseWidth.Size = new System.Drawing.Size(84, 13);
            this.m_lblTxWsPulseWidth.TabIndex = 101;
            this.m_lblTxWsPulseWidth.Text = "WS pulse width:";
            // 
            // m_cbTxChannels
            // 
            this.m_cbTxChannels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxChannels.FormattingEnabled = true;
            this.m_cbTxChannels.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"});
            this.m_cbTxChannels.Location = new System.Drawing.Point(115, 75);
            this.m_cbTxChannels.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxChannels.Name = "m_cbTxChannels";
            this.m_cbTxChannels.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxChannels.TabIndex = 2;
            // 
            // m_chbTxWatchdogInt
            // 
            this.m_chbTxWatchdogInt.AutoSize = true;
            this.m_chbTxWatchdogInt.Location = new System.Drawing.Point(12, 443);
            this.m_chbTxWatchdogInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbTxWatchdogInt.Name = "m_chbTxWatchdogInt";
            this.m_chbTxWatchdogInt.Size = new System.Drawing.Size(79, 17);
            this.m_chbTxWatchdogInt.TabIndex = 16;
            this.m_chbTxWatchdogInt.Text = "Watchdog:";
            this.m_chbTxWatchdogInt.UseVisualStyleBackColor = true;
            // 
            // m_cbTxAlignment
            // 
            this.m_cbTxAlignment.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxAlignment.FormattingEnabled = true;
            this.m_cbTxAlignment.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbTxAlignment.Location = new System.Drawing.Point(115, 51);
            this.m_cbTxAlignment.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxAlignment.Name = "m_cbTxAlignment";
            this.m_cbTxAlignment.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxAlignment.TabIndex = 1;
            // 
            // m_lblTxInterrupts
            // 
            this.m_lblTxInterrupts.AutoSize = true;
            this.m_lblTxInterrupts.Location = new System.Drawing.Point(2, 315);
            this.m_lblTxInterrupts.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxInterrupts.Name = "m_lblTxInterrupts";
            this.m_lblTxInterrupts.Size = new System.Drawing.Size(54, 13);
            this.m_lblTxInterrupts.TabIndex = 79;
            this.m_lblTxInterrupts.Text = "Interrupts:";
            // 
            // m_lblTxWordLength
            // 
            this.m_lblTxWordLength.AutoSize = true;
            this.m_lblTxWordLength.Location = new System.Drawing.Point(2, 126);
            this.m_lblTxWordLength.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxWordLength.Name = "m_lblTxWordLength";
            this.m_lblTxWordLength.Size = new System.Drawing.Size(68, 13);
            this.m_lblTxWordLength.TabIndex = 63;
            this.m_lblTxWordLength.Text = "Word length:";
            // 
            // m_lblTxAlignment
            // 
            this.m_lblTxAlignment.AutoSize = true;
            this.m_lblTxAlignment.Location = new System.Drawing.Point(2, 53);
            this.m_lblTxAlignment.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxAlignment.Name = "m_lblTxAlignment";
            this.m_lblTxAlignment.Size = new System.Drawing.Size(56, 13);
            this.m_lblTxAlignment.TabIndex = 99;
            this.m_lblTxAlignment.Text = "Alignment:";
            // 
            // m_chbTxUnderflowInt
            // 
            this.m_chbTxUnderflowInt.AutoSize = true;
            this.m_chbTxUnderflowInt.Location = new System.Drawing.Point(12, 421);
            this.m_chbTxUnderflowInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbTxUnderflowInt.Name = "m_chbTxUnderflowInt";
            this.m_chbTxUnderflowInt.Size = new System.Drawing.Size(74, 17);
            this.m_chbTxUnderflowInt.TabIndex = 15;
            this.m_chbTxUnderflowInt.Text = "Underflow";
            this.m_chbTxUnderflowInt.UseVisualStyleBackColor = true;
            // 
            // m_cbTxMode
            // 
            this.m_cbTxMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxMode.FormattingEnabled = true;
            this.m_cbTxMode.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbTxMode.Location = new System.Drawing.Point(115, 2);
            this.m_cbTxMode.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxMode.Name = "m_cbTxMode";
            this.m_cbTxMode.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxMode.TabIndex = 0;
            // 
            // m_lblTxOverheadValue
            // 
            this.m_lblTxOverheadValue.AutoSize = true;
            this.m_lblTxOverheadValue.Location = new System.Drawing.Point(2, 172);
            this.m_lblTxOverheadValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxOverheadValue.Name = "m_lblTxOverheadValue";
            this.m_lblTxOverheadValue.Size = new System.Drawing.Size(86, 13);
            this.m_lblTxOverheadValue.TabIndex = 89;
            this.m_lblTxOverheadValue.Text = "Overhead value:";
            // 
            // m_lblTxFifoTriggerLevel
            // 
            this.m_lblTxFifoTriggerLevel.AutoSize = true;
            this.m_lblTxFifoTriggerLevel.Location = new System.Drawing.Point(2, 270);
            this.m_lblTxFifoTriggerLevel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxFifoTriggerLevel.Name = "m_lblTxFifoTriggerLevel";
            this.m_lblTxFifoTriggerLevel.Size = new System.Drawing.Size(90, 13);
            this.m_lblTxFifoTriggerLevel.TabIndex = 77;
            this.m_lblTxFifoTriggerLevel.Text = "FIFO trigger level:";
            // 
            // m_lblTxMode
            // 
            this.m_lblTxMode.AutoSize = true;
            this.m_lblTxMode.Location = new System.Drawing.Point(2, 5);
            this.m_lblTxMode.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxMode.Name = "m_lblTxMode";
            this.m_lblTxMode.Size = new System.Drawing.Size(37, 13);
            this.m_lblTxMode.TabIndex = 97;
            this.m_lblTxMode.Text = "Mode:";
            // 
            // m_numTxWatchdogValue
            // 
            this.m_numTxWatchdogValue.Hexadecimal = true;
            this.m_numTxWatchdogValue.Location = new System.Drawing.Point(115, 443);
            this.m_numTxWatchdogValue.Margin = new System.Windows.Forms.Padding(2);
            this.m_numTxWatchdogValue.Name = "m_numTxWatchdogValue";
            this.m_numTxWatchdogValue.Size = new System.Drawing.Size(122, 20);
            this.m_numTxWatchdogValue.TabIndex = 17;
            this.m_numTxWatchdogValue.UserMaximum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.m_numTxWatchdogValue.UserMinimum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            // 
            // m_chbTxNotFullInt
            // 
            this.m_chbTxNotFullInt.AutoSize = true;
            this.m_chbTxNotFullInt.Location = new System.Drawing.Point(12, 355);
            this.m_chbTxNotFullInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbTxNotFullInt.Name = "m_chbTxNotFullInt";
            this.m_chbTxNotFullInt.Size = new System.Drawing.Size(59, 17);
            this.m_chbTxNotFullInt.TabIndex = 12;
            this.m_chbTxNotFullInt.Text = "Not full";
            this.m_chbTxNotFullInt.UseVisualStyleBackColor = true;
            // 
            // m_chbTxOverflowInt
            // 
            this.m_chbTxOverflowInt.AutoSize = true;
            this.m_chbTxOverflowInt.Location = new System.Drawing.Point(12, 399);
            this.m_chbTxOverflowInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbTxOverflowInt.Name = "m_chbTxOverflowInt";
            this.m_chbTxOverflowInt.Size = new System.Drawing.Size(68, 17);
            this.m_chbTxOverflowInt.TabIndex = 14;
            this.m_chbTxOverflowInt.Text = "Overflow";
            this.m_chbTxOverflowInt.UseVisualStyleBackColor = true;
            // 
            // m_lblTxFrameRateValue
            // 
            this.m_lblTxFrameRateValue.AutoSize = true;
            this.m_lblTxFrameRateValue.Location = new System.Drawing.Point(113, 150);
            this.m_lblTxFrameRateValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblTxFrameRateValue.Name = "m_lblTxFrameRateValue";
            this.m_lblTxFrameRateValue.Size = new System.Drawing.Size(65, 13);
            this.m_lblTxFrameRateValue.TabIndex = 95;
            this.m_lblTxFrameRateValue.Text = "UNKNOWN";
            // 
            // m_chbTxDmaTrigger
            // 
            this.m_chbTxDmaTrigger.AutoSize = true;
            this.m_chbTxDmaTrigger.Location = new System.Drawing.Point(4, 291);
            this.m_chbTxDmaTrigger.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbTxDmaTrigger.Name = "m_chbTxDmaTrigger";
            this.m_chbTxDmaTrigger.Size = new System.Drawing.Size(82, 17);
            this.m_chbTxDmaTrigger.TabIndex = 10;
            this.m_chbTxDmaTrigger.Text = "DMA trigger";
            this.m_chbTxDmaTrigger.UseVisualStyleBackColor = true;
            // 
            // m_chbTxTriggerInt
            // 
            this.m_chbTxTriggerInt.AutoSize = true;
            this.m_chbTxTriggerInt.Location = new System.Drawing.Point(12, 333);
            this.m_chbTxTriggerInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbTxTriggerInt.Name = "m_chbTxTriggerInt";
            this.m_chbTxTriggerInt.Size = new System.Drawing.Size(59, 17);
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
            this.m_cbTxOverheadValue.Location = new System.Drawing.Point(115, 169);
            this.m_cbTxOverheadValue.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbTxOverheadValue.Name = "m_cbTxOverheadValue";
            this.m_cbTxOverheadValue.Size = new System.Drawing.Size(122, 21);
            this.m_cbTxOverheadValue.TabIndex = 5;
            // 
            // m_chbTxEmptyInt
            // 
            this.m_chbTxEmptyInt.AutoSize = true;
            this.m_chbTxEmptyInt.Location = new System.Drawing.Point(12, 377);
            this.m_chbTxEmptyInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbTxEmptyInt.Name = "m_chbTxEmptyInt";
            this.m_chbTxEmptyInt.Size = new System.Drawing.Size(55, 17);
            this.m_chbTxEmptyInt.TabIndex = 13;
            this.m_chbTxEmptyInt.Text = "Empty";
            this.m_chbTxEmptyInt.UseVisualStyleBackColor = true;
            // 
            // m_chbEnableTx
            // 
            this.m_chbEnableTx.AutoSize = true;
            this.m_chbEnableTx.Location = new System.Drawing.Point(8, 0);
            this.m_chbEnableTx.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbEnableTx.Name = "m_chbEnableTx";
            this.m_chbEnableTx.Size = new System.Drawing.Size(40, 17);
            this.m_chbEnableTx.TabIndex = 0;
            this.m_chbEnableTx.Text = "TX";
            this.m_chbEnableTx.UseVisualStyleBackColor = true;
            // 
            // m_chbClockFromTerminal
            // 
            this.m_chbClockFromTerminal.AutoSize = true;
            this.m_chbClockFromTerminal.Location = new System.Drawing.Point(2, 4);
            this.m_chbClockFromTerminal.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbClockFromTerminal.Name = "m_chbClockFromTerminal";
            this.m_chbClockFromTerminal.Size = new System.Drawing.Size(115, 17);
            this.m_chbClockFromTerminal.TabIndex = 0;
            this.m_chbClockFromTerminal.Text = "Clock from terminal";
            this.m_chbClockFromTerminal.UseVisualStyleBackColor = true;
            // 
            // m_lblInputClockText
            // 
            this.m_lblInputClockText.AutoSize = true;
            this.m_lblInputClockText.Location = new System.Drawing.Point(142, 5);
            this.m_lblInputClockText.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblInputClockText.Name = "m_lblInputClockText";
            this.m_lblInputClockText.Size = new System.Drawing.Size(141, 13);
            this.m_lblInputClockText.TabIndex = 89;
            this.m_lblInputClockText.Text = "Input clock frequency (kHz):";
            // 
            // m_lblInputClockValue
            // 
            this.m_lblInputClockValue.AutoSize = true;
            this.m_lblInputClockValue.Location = new System.Drawing.Point(282, 5);
            this.m_lblInputClockValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblInputClockValue.Name = "m_lblInputClockValue";
            this.m_lblInputClockValue.Size = new System.Drawing.Size(53, 13);
            this.m_lblInputClockValue.TabIndex = 90;
            this.m_lblInputClockValue.Text = "Unknown";
            // 
            // m_lblClockDivider
            // 
            this.m_lblClockDivider.AutoSize = true;
            this.m_lblClockDivider.Location = new System.Drawing.Point(0, 28);
            this.m_lblClockDivider.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblClockDivider.Name = "m_lblClockDivider";
            this.m_lblClockDivider.Size = new System.Drawing.Size(71, 13);
            this.m_lblClockDivider.TabIndex = 91;
            this.m_lblClockDivider.Text = "Clock divider:";
            // 
            // m_numClockDivider
            // 
            this.m_numClockDivider.Location = new System.Drawing.Point(74, 26);
            this.m_numClockDivider.Margin = new System.Windows.Forms.Padding(2);
            this.m_numClockDivider.Name = "m_numClockDivider";
            this.m_numClockDivider.Size = new System.Drawing.Size(44, 20);
            this.m_numClockDivider.TabIndex = 1;
            this.m_numClockDivider.UserMaximum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.m_numClockDivider.UserMinimum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.m_numClockDivider.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // m_gbRx
            // 
            this.m_gbRx.Controls.Add(this.m_panelRx);
            this.m_gbRx.Controls.Add(this.m_chbEnableRx);
            this.m_gbRx.Location = new System.Drawing.Point(272, 49);
            this.m_gbRx.Margin = new System.Windows.Forms.Padding(2);
            this.m_gbRx.Name = "m_gbRx";
            this.m_gbRx.Padding = new System.Windows.Forms.Padding(2);
            this.m_gbRx.Size = new System.Drawing.Size(266, 491);
            this.m_gbRx.TabIndex = 3;
            this.m_gbRx.TabStop = false;
            this.m_gbRx.Text = "           ";
            // 
            // m_panelRx
            // 
            this.m_panelRx.Controls.Add(this.m_cbRxOutputClockPolarity);
            this.m_panelRx.Controls.Add(this.m_lblRxOutputClockPolarity);
            this.m_panelRx.Controls.Add(this.m_cbRxInputClockPolarity);
            this.m_panelRx.Controls.Add(this.m_lblRxInputClockPolarity);
            this.m_panelRx.Controls.Add(this.m_lblRxBitRateValue);
            this.m_panelRx.Controls.Add(this.m_lblRxBitRateText);
            this.m_panelRx.Controls.Add(this.m_lblRxSignExtension);
            this.m_panelRx.Controls.Add(this.m_chbRxWatchdogInt);
            this.m_panelRx.Controls.Add(this.m_numRxWatchdogValue);
            this.m_panelRx.Controls.Add(this.m_chbRxUnderflowInt);
            this.m_panelRx.Controls.Add(this.m_lblRxInterrupts);
            this.m_panelRx.Controls.Add(this.m_cbRxSignExtension);
            this.m_panelRx.Controls.Add(this.m_chbRxOverflowInt);
            this.m_panelRx.Controls.Add(this.m_cbRxChannels);
            this.m_panelRx.Controls.Add(this.m_chbRxFullInt);
            this.m_panelRx.Controls.Add(this.m_lblRxFrameRateText);
            this.m_panelRx.Controls.Add(this.m_lblRxFrameRateValue);
            this.m_panelRx.Controls.Add(this.m_chbRxTriggerInt);
            this.m_panelRx.Controls.Add(this.m_lblRxChannels);
            this.m_panelRx.Controls.Add(this.m_lblRxMode);
            this.m_panelRx.Controls.Add(this.m_chbRxNotEmptyInt);
            this.m_panelRx.Controls.Add(this.m_lblRxChannelLength);
            this.m_panelRx.Controls.Add(this.m_cbRxMode);
            this.m_panelRx.Controls.Add(this.m_cbRxSdi);
            this.m_panelRx.Controls.Add(this.m_cbRxChannelLength);
            this.m_panelRx.Controls.Add(this.m_chbRxDmaTrigger);
            this.m_panelRx.Controls.Add(this.m_lblRxAlignment);
            this.m_panelRx.Controls.Add(this.m_lblRxSdi);
            this.m_panelRx.Controls.Add(this.m_cbRxWordLength);
            this.m_panelRx.Controls.Add(this.m_lblRxFifoTriggerLevel);
            this.m_panelRx.Controls.Add(this.m_cbRxAlignment);
            this.m_panelRx.Controls.Add(this.m_cbRxWsPulseWidth);
            this.m_panelRx.Controls.Add(this.m_numRxFifoTriggerLevel);
            this.m_panelRx.Controls.Add(this.m_lblRxWordLength);
            this.m_panelRx.Controls.Add(this.m_lblRxWsPulseWidth);
            this.m_panelRx.Location = new System.Drawing.Point(4, 19);
            this.m_panelRx.Margin = new System.Windows.Forms.Padding(2);
            this.m_panelRx.Name = "m_panelRx";
            this.m_panelRx.Size = new System.Drawing.Size(259, 469);
            this.m_panelRx.TabIndex = 2;
            // 
            // m_cbRxOutputClockPolarity
            // 
            this.m_cbRxOutputClockPolarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxOutputClockPolarity.FormattingEnabled = true;
            this.m_cbRxOutputClockPolarity.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxOutputClockPolarity.Location = new System.Drawing.Point(115, 243);
            this.m_cbRxOutputClockPolarity.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxOutputClockPolarity.Name = "m_cbRxOutputClockPolarity";
            this.m_cbRxOutputClockPolarity.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxOutputClockPolarity.TabIndex = 8;
            // 
            // m_lblRxOutputClockPolarity
            // 
            this.m_lblRxOutputClockPolarity.AutoSize = true;
            this.m_lblRxOutputClockPolarity.Location = new System.Drawing.Point(2, 245);
            this.m_lblRxOutputClockPolarity.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxOutputClockPolarity.Name = "m_lblRxOutputClockPolarity";
            this.m_lblRxOutputClockPolarity.Size = new System.Drawing.Size(107, 13);
            this.m_lblRxOutputClockPolarity.TabIndex = 118;
            this.m_lblRxOutputClockPolarity.Text = "Output clock polarity:";
            // 
            // m_cbRxInputClockPolarity
            // 
            this.m_cbRxInputClockPolarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxInputClockPolarity.FormattingEnabled = true;
            this.m_cbRxInputClockPolarity.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxInputClockPolarity.Location = new System.Drawing.Point(115, 243);
            this.m_cbRxInputClockPolarity.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxInputClockPolarity.Name = "m_cbRxInputClockPolarity";
            this.m_cbRxInputClockPolarity.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxInputClockPolarity.TabIndex = 115;
            // 
            // m_lblRxInputClockPolarity
            // 
            this.m_lblRxInputClockPolarity.AutoSize = true;
            this.m_lblRxInputClockPolarity.Location = new System.Drawing.Point(2, 245);
            this.m_lblRxInputClockPolarity.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxInputClockPolarity.Name = "m_lblRxInputClockPolarity";
            this.m_lblRxInputClockPolarity.Size = new System.Drawing.Size(99, 13);
            this.m_lblRxInputClockPolarity.TabIndex = 116;
            this.m_lblRxInputClockPolarity.Text = "Input clock polarity:";
            // 
            // m_lblRxBitRateValue
            // 
            this.m_lblRxBitRateValue.AutoSize = true;
            this.m_lblRxBitRateValue.Location = new System.Drawing.Point(113, 29);
            this.m_lblRxBitRateValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxBitRateValue.Name = "m_lblRxBitRateValue";
            this.m_lblRxBitRateValue.Size = new System.Drawing.Size(65, 13);
            this.m_lblRxBitRateValue.TabIndex = 114;
            this.m_lblRxBitRateValue.Text = "UNKNOWN";
            // 
            // m_lblRxBitRateText
            // 
            this.m_lblRxBitRateText.AutoSize = true;
            this.m_lblRxBitRateText.Location = new System.Drawing.Point(2, 29);
            this.m_lblRxBitRateText.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxBitRateText.Name = "m_lblRxBitRateText";
            this.m_lblRxBitRateText.Size = new System.Drawing.Size(75, 13);
            this.m_lblRxBitRateText.TabIndex = 113;
            this.m_lblRxBitRateText.Text = "Bit rate (kbps):";
            // 
            // m_lblRxSignExtension
            // 
            this.m_lblRxSignExtension.AutoSize = true;
            this.m_lblRxSignExtension.Location = new System.Drawing.Point(2, 172);
            this.m_lblRxSignExtension.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxSignExtension.Name = "m_lblRxSignExtension";
            this.m_lblRxSignExtension.Size = new System.Drawing.Size(79, 13);
            this.m_lblRxSignExtension.TabIndex = 89;
            this.m_lblRxSignExtension.Text = "Sign extension:";
            // 
            // m_chbRxWatchdogInt
            // 
            this.m_chbRxWatchdogInt.AutoSize = true;
            this.m_chbRxWatchdogInt.Location = new System.Drawing.Point(12, 443);
            this.m_chbRxWatchdogInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbRxWatchdogInt.Name = "m_chbRxWatchdogInt";
            this.m_chbRxWatchdogInt.Size = new System.Drawing.Size(79, 17);
            this.m_chbRxWatchdogInt.TabIndex = 16;
            this.m_chbRxWatchdogInt.Text = "Watchdog:";
            this.m_chbRxWatchdogInt.UseVisualStyleBackColor = true;
            // 
            // m_numRxWatchdogValue
            // 
            this.m_numRxWatchdogValue.Hexadecimal = true;
            this.m_numRxWatchdogValue.Location = new System.Drawing.Point(115, 443);
            this.m_numRxWatchdogValue.Margin = new System.Windows.Forms.Padding(2);
            this.m_numRxWatchdogValue.Name = "m_numRxWatchdogValue";
            this.m_numRxWatchdogValue.Size = new System.Drawing.Size(122, 20);
            this.m_numRxWatchdogValue.TabIndex = 17;
            this.m_numRxWatchdogValue.UserMaximum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.m_numRxWatchdogValue.UserMinimum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            // 
            // m_chbRxUnderflowInt
            // 
            this.m_chbRxUnderflowInt.AutoSize = true;
            this.m_chbRxUnderflowInt.Location = new System.Drawing.Point(12, 421);
            this.m_chbRxUnderflowInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbRxUnderflowInt.Name = "m_chbRxUnderflowInt";
            this.m_chbRxUnderflowInt.Size = new System.Drawing.Size(74, 17);
            this.m_chbRxUnderflowInt.TabIndex = 15;
            this.m_chbRxUnderflowInt.Text = "Underflow";
            this.m_chbRxUnderflowInt.UseVisualStyleBackColor = true;
            // 
            // m_lblRxInterrupts
            // 
            this.m_lblRxInterrupts.AutoSize = true;
            this.m_lblRxInterrupts.Location = new System.Drawing.Point(2, 315);
            this.m_lblRxInterrupts.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxInterrupts.Name = "m_lblRxInterrupts";
            this.m_lblRxInterrupts.Size = new System.Drawing.Size(54, 13);
            this.m_lblRxInterrupts.TabIndex = 79;
            this.m_lblRxInterrupts.Text = "Interrupts:";
            // 
            // m_cbRxSignExtension
            // 
            this.m_cbRxSignExtension.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxSignExtension.FormattingEnabled = true;
            this.m_cbRxSignExtension.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxSignExtension.Location = new System.Drawing.Point(115, 169);
            this.m_cbRxSignExtension.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxSignExtension.Name = "m_cbRxSignExtension";
            this.m_cbRxSignExtension.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxSignExtension.TabIndex = 5;
            // 
            // m_chbRxOverflowInt
            // 
            this.m_chbRxOverflowInt.AutoSize = true;
            this.m_chbRxOverflowInt.Location = new System.Drawing.Point(12, 399);
            this.m_chbRxOverflowInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbRxOverflowInt.Name = "m_chbRxOverflowInt";
            this.m_chbRxOverflowInt.Size = new System.Drawing.Size(68, 17);
            this.m_chbRxOverflowInt.TabIndex = 14;
            this.m_chbRxOverflowInt.Text = "Overflow";
            this.m_chbRxOverflowInt.UseVisualStyleBackColor = true;
            // 
            // m_cbRxChannels
            // 
            this.m_cbRxChannels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxChannels.FormattingEnabled = true;
            this.m_cbRxChannels.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"});
            this.m_cbRxChannels.Location = new System.Drawing.Point(115, 75);
            this.m_cbRxChannels.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxChannels.Name = "m_cbRxChannels";
            this.m_cbRxChannels.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxChannels.TabIndex = 2;
            // 
            // m_chbRxFullInt
            // 
            this.m_chbRxFullInt.AutoSize = true;
            this.m_chbRxFullInt.Location = new System.Drawing.Point(12, 377);
            this.m_chbRxFullInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbRxFullInt.Name = "m_chbRxFullInt";
            this.m_chbRxFullInt.Size = new System.Drawing.Size(42, 17);
            this.m_chbRxFullInt.TabIndex = 13;
            this.m_chbRxFullInt.Text = "Full";
            this.m_chbRxFullInt.UseVisualStyleBackColor = true;
            // 
            // m_lblRxFrameRateText
            // 
            this.m_lblRxFrameRateText.AutoSize = true;
            this.m_lblRxFrameRateText.Location = new System.Drawing.Point(2, 150);
            this.m_lblRxFrameRateText.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxFrameRateText.Name = "m_lblRxFrameRateText";
            this.m_lblRxFrameRateText.Size = new System.Drawing.Size(91, 13);
            this.m_lblRxFrameRateText.TabIndex = 84;
            this.m_lblRxFrameRateText.Text = "Frame rate (ksps):";
            // 
            // m_lblRxFrameRateValue
            // 
            this.m_lblRxFrameRateValue.AutoSize = true;
            this.m_lblRxFrameRateValue.Location = new System.Drawing.Point(113, 150);
            this.m_lblRxFrameRateValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxFrameRateValue.Name = "m_lblRxFrameRateValue";
            this.m_lblRxFrameRateValue.Size = new System.Drawing.Size(65, 13);
            this.m_lblRxFrameRateValue.TabIndex = 95;
            this.m_lblRxFrameRateValue.Text = "UNKNOWN";
            // 
            // m_chbRxTriggerInt
            // 
            this.m_chbRxTriggerInt.AutoSize = true;
            this.m_chbRxTriggerInt.Location = new System.Drawing.Point(12, 333);
            this.m_chbRxTriggerInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbRxTriggerInt.Name = "m_chbRxTriggerInt";
            this.m_chbRxTriggerInt.Size = new System.Drawing.Size(59, 17);
            this.m_chbRxTriggerInt.TabIndex = 11;
            this.m_chbRxTriggerInt.Text = "Trigger";
            this.m_chbRxTriggerInt.UseVisualStyleBackColor = true;
            // 
            // m_lblRxChannels
            // 
            this.m_lblRxChannels.AutoSize = true;
            this.m_lblRxChannels.Location = new System.Drawing.Point(2, 77);
            this.m_lblRxChannels.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxChannels.Name = "m_lblRxChannels";
            this.m_lblRxChannels.Size = new System.Drawing.Size(54, 13);
            this.m_lblRxChannels.TabIndex = 55;
            this.m_lblRxChannels.Text = "Channels:";
            // 
            // m_lblRxMode
            // 
            this.m_lblRxMode.AutoSize = true;
            this.m_lblRxMode.Location = new System.Drawing.Point(2, 5);
            this.m_lblRxMode.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxMode.Name = "m_lblRxMode";
            this.m_lblRxMode.Size = new System.Drawing.Size(37, 13);
            this.m_lblRxMode.TabIndex = 97;
            this.m_lblRxMode.Text = "Mode:";
            // 
            // m_chbRxNotEmptyInt
            // 
            this.m_chbRxNotEmptyInt.AutoSize = true;
            this.m_chbRxNotEmptyInt.Location = new System.Drawing.Point(12, 355);
            this.m_chbRxNotEmptyInt.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbRxNotEmptyInt.Name = "m_chbRxNotEmptyInt";
            this.m_chbRxNotEmptyInt.Size = new System.Drawing.Size(74, 17);
            this.m_chbRxNotEmptyInt.TabIndex = 12;
            this.m_chbRxNotEmptyInt.Text = "Not empty";
            this.m_chbRxNotEmptyInt.UseVisualStyleBackColor = true;
            // 
            // m_lblRxChannelLength
            // 
            this.m_lblRxChannelLength.AutoSize = true;
            this.m_lblRxChannelLength.Location = new System.Drawing.Point(2, 102);
            this.m_lblRxChannelLength.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxChannelLength.Name = "m_lblRxChannelLength";
            this.m_lblRxChannelLength.Size = new System.Drawing.Size(81, 13);
            this.m_lblRxChannelLength.TabIndex = 61;
            this.m_lblRxChannelLength.Text = "Channel length:";
            // 
            // m_cbRxMode
            // 
            this.m_cbRxMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxMode.FormattingEnabled = true;
            this.m_cbRxMode.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxMode.Location = new System.Drawing.Point(115, 2);
            this.m_cbRxMode.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxMode.Name = "m_cbRxMode";
            this.m_cbRxMode.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxMode.TabIndex = 0;
            // 
            // m_cbRxSdi
            // 
            this.m_cbRxSdi.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxSdi.FormattingEnabled = true;
            this.m_cbRxSdi.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxSdi.Location = new System.Drawing.Point(115, 219);
            this.m_cbRxSdi.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxSdi.Name = "m_cbRxSdi";
            this.m_cbRxSdi.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxSdi.TabIndex = 7;
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
            this.m_cbRxChannelLength.Location = new System.Drawing.Point(115, 99);
            this.m_cbRxChannelLength.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxChannelLength.Name = "m_cbRxChannelLength";
            this.m_cbRxChannelLength.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxChannelLength.TabIndex = 3;
            // 
            // m_chbRxDmaTrigger
            // 
            this.m_chbRxDmaTrigger.AutoSize = true;
            this.m_chbRxDmaTrigger.Location = new System.Drawing.Point(4, 291);
            this.m_chbRxDmaTrigger.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbRxDmaTrigger.Name = "m_chbRxDmaTrigger";
            this.m_chbRxDmaTrigger.Size = new System.Drawing.Size(82, 17);
            this.m_chbRxDmaTrigger.TabIndex = 10;
            this.m_chbRxDmaTrigger.Text = "DMA trigger";
            this.m_chbRxDmaTrigger.UseVisualStyleBackColor = true;
            // 
            // m_lblRxAlignment
            // 
            this.m_lblRxAlignment.AutoSize = true;
            this.m_lblRxAlignment.Location = new System.Drawing.Point(2, 53);
            this.m_lblRxAlignment.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxAlignment.Name = "m_lblRxAlignment";
            this.m_lblRxAlignment.Size = new System.Drawing.Size(56, 13);
            this.m_lblRxAlignment.TabIndex = 99;
            this.m_lblRxAlignment.Text = "Alignment:";
            // 
            // m_lblRxSdi
            // 
            this.m_lblRxSdi.AutoSize = true;
            this.m_lblRxSdi.Location = new System.Drawing.Point(2, 221);
            this.m_lblRxSdi.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxSdi.Name = "m_lblRxSdi";
            this.m_lblRxSdi.Size = new System.Drawing.Size(90, 13);
            this.m_lblRxSdi.TabIndex = 103;
            this.m_lblRxSdi.Text = "SDI latching time:";
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
            this.m_cbRxWordLength.Location = new System.Drawing.Point(115, 124);
            this.m_cbRxWordLength.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxWordLength.Name = "m_cbRxWordLength";
            this.m_cbRxWordLength.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxWordLength.TabIndex = 4;
            // 
            // m_lblRxFifoTriggerLevel
            // 
            this.m_lblRxFifoTriggerLevel.AutoSize = true;
            this.m_lblRxFifoTriggerLevel.Location = new System.Drawing.Point(2, 270);
            this.m_lblRxFifoTriggerLevel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxFifoTriggerLevel.Name = "m_lblRxFifoTriggerLevel";
            this.m_lblRxFifoTriggerLevel.Size = new System.Drawing.Size(90, 13);
            this.m_lblRxFifoTriggerLevel.TabIndex = 77;
            this.m_lblRxFifoTriggerLevel.Text = "FIFO trigger level:";
            // 
            // m_cbRxAlignment
            // 
            this.m_cbRxAlignment.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxAlignment.FormattingEnabled = true;
            this.m_cbRxAlignment.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxAlignment.Location = new System.Drawing.Point(115, 51);
            this.m_cbRxAlignment.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxAlignment.Name = "m_cbRxAlignment";
            this.m_cbRxAlignment.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxAlignment.TabIndex = 1;
            // 
            // m_cbRxWsPulseWidth
            // 
            this.m_cbRxWsPulseWidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxWsPulseWidth.FormattingEnabled = true;
            this.m_cbRxWsPulseWidth.Items.AddRange(new object[] {
            "0",
            "1"});
            this.m_cbRxWsPulseWidth.Location = new System.Drawing.Point(115, 194);
            this.m_cbRxWsPulseWidth.Margin = new System.Windows.Forms.Padding(2);
            this.m_cbRxWsPulseWidth.Name = "m_cbRxWsPulseWidth";
            this.m_cbRxWsPulseWidth.Size = new System.Drawing.Size(122, 21);
            this.m_cbRxWsPulseWidth.TabIndex = 6;
            // 
            // m_numRxFifoTriggerLevel
            // 
            this.m_numRxFifoTriggerLevel.Location = new System.Drawing.Point(115, 268);
            this.m_numRxFifoTriggerLevel.Margin = new System.Windows.Forms.Padding(2);
            this.m_numRxFifoTriggerLevel.Name = "m_numRxFifoTriggerLevel";
            this.m_numRxFifoTriggerLevel.Size = new System.Drawing.Size(122, 20);
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
            this.m_lblRxWordLength.Location = new System.Drawing.Point(2, 126);
            this.m_lblRxWordLength.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxWordLength.Name = "m_lblRxWordLength";
            this.m_lblRxWordLength.Size = new System.Drawing.Size(68, 13);
            this.m_lblRxWordLength.TabIndex = 63;
            this.m_lblRxWordLength.Text = "Word length:";
            // 
            // m_lblRxWsPulseWidth
            // 
            this.m_lblRxWsPulseWidth.AutoSize = true;
            this.m_lblRxWsPulseWidth.Location = new System.Drawing.Point(2, 197);
            this.m_lblRxWsPulseWidth.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblRxWsPulseWidth.Name = "m_lblRxWsPulseWidth";
            this.m_lblRxWsPulseWidth.Size = new System.Drawing.Size(84, 13);
            this.m_lblRxWsPulseWidth.TabIndex = 101;
            this.m_lblRxWsPulseWidth.Text = "WS pulse width:";
            // 
            // m_chbEnableRx
            // 
            this.m_chbEnableRx.AutoSize = true;
            this.m_chbEnableRx.Location = new System.Drawing.Point(8, 0);
            this.m_chbEnableRx.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbEnableRx.Name = "m_chbEnableRx";
            this.m_chbEnableRx.Size = new System.Drawing.Size(41, 17);
            this.m_chbEnableRx.TabIndex = 0;
            this.m_chbEnableRx.Text = "RX";
            this.m_chbEnableRx.UseVisualStyleBackColor = true;
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_gbRx);
            this.Controls.Add(this.m_lblClockDivider);
            this.Controls.Add(this.m_numClockDivider);
            this.Controls.Add(this.m_lblInputClockValue);
            this.Controls.Add(this.m_lblInputClockText);
            this.Controls.Add(this.m_chbClockFromTerminal);
            this.Controls.Add(this.m_gbTx);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(559, 543);
            this.m_gbTx.ResumeLayout(false);
            this.m_gbTx.PerformLayout();
            this.m_panelTx.ResumeLayout(false);
            this.m_panelTx.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTxFifoTriggerLevel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTxWatchdogValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClockDivider)).EndInit();
            this.m_gbRx.ResumeLayout(false);
            this.m_gbRx.PerformLayout();
            this.m_panelRx.ResumeLayout(false);
            this.m_panelRx.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRxWatchdogValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRxFifoTriggerLevel)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.GroupBox m_gbTx;
        private CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numTxWatchdogValue;
        private System.Windows.Forms.Label m_lblTxInterrupts;
        private System.Windows.Forms.ComboBox m_cbTxChannels;
        private System.Windows.Forms.Label m_lblTxChannels;
        private System.Windows.Forms.Label m_lblTxChannelLength;
        private System.Windows.Forms.ComboBox m_cbTxChannelLength;
        private System.Windows.Forms.ComboBox m_cbTxWordLength;
        private CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numTxFifoTriggerLevel;
        private System.Windows.Forms.CheckBox m_chbTxWatchdogInt;
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
        private System.Windows.Forms.ComboBox m_cbTxWsPulseWidth;
        private System.Windows.Forms.Label m_lblTxWsPulseWidth;
        private System.Windows.Forms.ComboBox m_cbTxAlignment;
        private System.Windows.Forms.Label m_lblTxAlignment;
        private System.Windows.Forms.ComboBox m_cbTxMode;
        private System.Windows.Forms.Label m_lblTxMode;
        private System.Windows.Forms.Label m_lblTxFrameRateValue;
        private System.Windows.Forms.Label m_lblClockDivider;
        CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numClockDivider;
        private System.Windows.Forms.ComboBox m_cbTxSdo;
        private System.Windows.Forms.Label m_lblTxSdo;
        private System.Windows.Forms.GroupBox m_gbRx;
        private System.Windows.Forms.CheckBox m_chbRxWatchdogInt;
        private System.Windows.Forms.CheckBox m_chbRxUnderflowInt;
        private System.Windows.Forms.CheckBox m_chbRxOverflowInt;
        private System.Windows.Forms.CheckBox m_chbRxFullInt;
        private System.Windows.Forms.CheckBox m_chbRxTriggerInt;
        private System.Windows.Forms.CheckBox m_chbRxNotEmptyInt;
        private System.Windows.Forms.ComboBox m_cbRxSdi;
        private System.Windows.Forms.Label m_lblRxSdi;
        private System.Windows.Forms.ComboBox m_cbRxWsPulseWidth;
        private System.Windows.Forms.Label m_lblRxWsPulseWidth;
        private System.Windows.Forms.ComboBox m_cbRxAlignment;
        private System.Windows.Forms.Label m_lblRxAlignment;
        private System.Windows.Forms.ComboBox m_cbRxMode;
        private System.Windows.Forms.Label m_lblRxMode;
        private System.Windows.Forms.Label m_lblRxFrameRateValue;
        private System.Windows.Forms.ComboBox m_cbRxSignExtension;
        private CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numRxWatchdogValue;
        private System.Windows.Forms.Label m_lblRxSignExtension;
        private System.Windows.Forms.Label m_lblRxInterrupts;
        private System.Windows.Forms.ComboBox m_cbRxChannels;
        private System.Windows.Forms.Label m_lblRxFrameRateText;
        private System.Windows.Forms.Label m_lblRxChannels;
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
        private System.Windows.Forms.Label m_lblTxBitRateText;
        private System.Windows.Forms.Label m_lblRxBitRateText;
        private System.Windows.Forms.Label m_lblTxBitRateValue;
        private System.Windows.Forms.Label m_lblRxBitRateValue;
        private System.Windows.Forms.ComboBox m_cbRxInputClockPolarity;
        private System.Windows.Forms.Label m_lblRxInputClockPolarity;
        private System.Windows.Forms.ComboBox m_cbTxInputClockPolarity;
        private System.Windows.Forms.Label m_lblTxInputClockPolarity;
        private System.Windows.Forms.ComboBox m_cbRxOutputClockPolarity;
        private System.Windows.Forms.Label m_lblRxOutputClockPolarity;
        private System.Windows.Forms.ComboBox m_cbTxOutputClockPolarity;
        private System.Windows.Forms.Label m_lblTxOutputClockPolarity;
    }
}
