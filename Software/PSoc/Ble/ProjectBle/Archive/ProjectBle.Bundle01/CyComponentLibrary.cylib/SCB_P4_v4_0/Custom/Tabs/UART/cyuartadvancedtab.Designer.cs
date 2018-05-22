namespace SCB_P4_v4_0
{
    partial class CyUARTAdvancedTab
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
            this.m_cbTXTriggerLevel = new System.Windows.Forms.ComboBox();
            this.m_chbInterruptRXNotEmpty = new System.Windows.Forms.CheckBox();
            this.m_cbRXTriggerLevel = new System.Windows.Forms.ComboBox();
            this.m_chbInterruptRXFull = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptTXTrigger = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptUARTDone = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptRXOverflow = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptTXUnderflow = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptRXUnderflow = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptTXOverflow = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptRXTrigger = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptTXEmpty = new System.Windows.Forms.CheckBox();
            this.m_grpIntrSources = new System.Windows.Forms.GroupBox();
            this.m_numRXBreakWidth = new System.Windows.Forms.NumericUpDown();
            this.m_chbInterruptRXBreakDetected = new System.Windows.Forms.CheckBox();
            this.m_lblRXBreakWidth = new System.Windows.Forms.Label();
            this.m_chbInterruptRXParityErr = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptTXNotFull = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptTXLostArb = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptRXFrameErr = new System.Windows.Forms.CheckBox();
            this.m_chbInterruptTxNack = new System.Windows.Forms.CheckBox();
            this.m_rbExternal = new System.Windows.Forms.RadioButton();
            this.m_rbInternal = new System.Windows.Forms.RadioButton();
            this.m_rbNone = new System.Windows.Forms.RadioButton();
            this.m_numTXBufferSize = new System.Windows.Forms.NumericUpDown();
            this.m_lblTXBufferSize = new System.Windows.Forms.Label();
            this.m_numRXBufferSize = new System.Windows.Forms.NumericUpDown();
            this.m_lblRXBufferSize = new System.Windows.Forms.Label();
            this.m_grpBuffSizes = new System.Windows.Forms.GroupBox();
            this.m_chbByteMode = new System.Windows.Forms.CheckBox();
            this.m_grpMultiProcessMode = new System.Windows.Forms.GroupBox();
            this.m_chbAcceptAddress = new System.Windows.Forms.CheckBox();
            this.m_numAddressMask = new System.Windows.Forms.NumericUpDown();
            this.m_chbEnMultiProcMode = new System.Windows.Forms.CheckBox();
            this.m_numAddress = new System.Windows.Forms.NumericUpDown();
            this.m_lblAddress = new System.Windows.Forms.Label();
            this.m_lblMask = new System.Windows.Forms.Label();
            this.m_grpIntrConn = new System.Windows.Forms.GroupBox();
            this.m_grpRxFifoDrop = new System.Windows.Forms.GroupBox();
            this.m_chbDropOnFrameError = new System.Windows.Forms.CheckBox();
            this.m_chbDropOnParityError = new System.Windows.Forms.CheckBox();
            this.m_grpControlFlow = new System.Windows.Forms.GroupBox();
            this.m_chbCts = new System.Windows.Forms.CheckBox();
            this.m_chbRts = new System.Windows.Forms.CheckBox();
            this.m_panelCtsControlFlow = new System.Windows.Forms.Panel();
            this.m_cbCtsPolarity = new System.Windows.Forms.ComboBox();
            this.m_lblCtsPolarity = new System.Windows.Forms.Label();
            this.m_panelRtsControlFlow = new System.Windows.Forms.Panel();
            this.m_cbRtsPolarity = new System.Windows.Forms.ComboBox();
            this.m_numRtsRxFifoTrigger = new System.Windows.Forms.NumericUpDown();
            this.m_lblRxFifoTrigger = new System.Windows.Forms.Label();
            this.m_lblRtsPolarity = new System.Windows.Forms.Label();
            this.m_gbDma = new System.Windows.Forms.GroupBox();
            this.m_chbRxOutput = new System.Windows.Forms.CheckBox();
            this.m_chbTxOutput = new System.Windows.Forms.CheckBox();
            this.m_gbFifoLevels = new System.Windows.Forms.GroupBox();
            this.m_panelRxFifoLevel = new System.Windows.Forms.Panel();
            this.m_lblRxFifo = new System.Windows.Forms.Label();
            this.m_panelTxFifoLevel = new System.Windows.Forms.Panel();
            this.m_lblTxFifo = new System.Windows.Forms.Label();
            this.m_grpIntrSources.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRXBreakWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTXBufferSize)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRXBufferSize)).BeginInit();
            this.m_grpBuffSizes.SuspendLayout();
            this.m_grpMultiProcessMode.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numAddressMask)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numAddress)).BeginInit();
            this.m_grpIntrConn.SuspendLayout();
            this.m_grpRxFifoDrop.SuspendLayout();
            this.m_grpControlFlow.SuspendLayout();
            this.m_panelCtsControlFlow.SuspendLayout();
            this.m_panelRtsControlFlow.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRtsRxFifoTrigger)).BeginInit();
            this.m_gbDma.SuspendLayout();
            this.m_gbFifoLevels.SuspendLayout();
            this.m_panelRxFifoLevel.SuspendLayout();
            this.m_panelTxFifoLevel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_cbTXTriggerLevel
            // 
            this.m_cbTXTriggerLevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTXTriggerLevel.FormattingEnabled = true;
            this.m_cbTXTriggerLevel.Location = new System.Drawing.Point(74, 0);
            this.m_cbTXTriggerLevel.Name = "m_cbTXTriggerLevel";
            this.m_cbTXTriggerLevel.Size = new System.Drawing.Size(62, 21);
            this.m_cbTXTriggerLevel.TabIndex = 0;
            // 
            // m_chbInterruptRXNotEmpty
            // 
            this.m_chbInterruptRXNotEmpty.AutoSize = true;
            this.m_chbInterruptRXNotEmpty.Location = new System.Drawing.Point(193, 18);
            this.m_chbInterruptRXNotEmpty.Name = "m_chbInterruptRXNotEmpty";
            this.m_chbInterruptRXNotEmpty.Size = new System.Drawing.Size(116, 17);
            this.m_chbInterruptRXNotEmpty.TabIndex = 9;
            this.m_chbInterruptRXNotEmpty.Text = "RX FIFO not empty";
            this.m_chbInterruptRXNotEmpty.UseVisualStyleBackColor = true;
            // 
            // m_cbRXTriggerLevel
            // 
            this.m_cbRXTriggerLevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRXTriggerLevel.FormattingEnabled = true;
            this.m_cbRXTriggerLevel.Location = new System.Drawing.Point(75, 0);
            this.m_cbRXTriggerLevel.Name = "m_cbRXTriggerLevel";
            this.m_cbRXTriggerLevel.Size = new System.Drawing.Size(62, 21);
            this.m_cbRXTriggerLevel.TabIndex = 0;
            // 
            // m_chbInterruptRXFull
            // 
            this.m_chbInterruptRXFull.AutoSize = true;
            this.m_chbInterruptRXFull.Location = new System.Drawing.Point(193, 42);
            this.m_chbInterruptRXFull.Name = "m_chbInterruptRXFull";
            this.m_chbInterruptRXFull.Size = new System.Drawing.Size(83, 17);
            this.m_chbInterruptRXFull.TabIndex = 10;
            this.m_chbInterruptRXFull.Text = "RX FIFO full";
            this.m_chbInterruptRXFull.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptTXTrigger
            // 
            this.m_chbInterruptTXTrigger.AutoSize = true;
            this.m_chbInterruptTXTrigger.Location = new System.Drawing.Point(6, 177);
            this.m_chbInterruptTXTrigger.Name = "m_chbInterruptTXTrigger";
            this.m_chbInterruptTXTrigger.Size = new System.Drawing.Size(91, 17);
            this.m_chbInterruptTXTrigger.TabIndex = 7;
            this.m_chbInterruptTXTrigger.Text = "TX FIFO level";
            this.m_chbInterruptTXTrigger.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptUARTDone
            // 
            this.m_chbInterruptUARTDone.AutoSize = true;
            this.m_chbInterruptUARTDone.Location = new System.Drawing.Point(6, 18);
            this.m_chbInterruptUARTDone.Name = "m_chbInterruptUARTDone";
            this.m_chbInterruptUARTDone.Size = new System.Drawing.Size(83, 17);
            this.m_chbInterruptUARTDone.TabIndex = 0;
            this.m_chbInterruptUARTDone.Text = "UART done";
            this.m_chbInterruptUARTDone.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptRXOverflow
            // 
            this.m_chbInterruptRXOverflow.AutoSize = true;
            this.m_chbInterruptRXOverflow.Location = new System.Drawing.Point(193, 64);
            this.m_chbInterruptRXOverflow.Name = "m_chbInterruptRXOverflow";
            this.m_chbInterruptRXOverflow.Size = new System.Drawing.Size(110, 17);
            this.m_chbInterruptRXOverflow.TabIndex = 11;
            this.m_chbInterruptRXOverflow.Text = "RX FIFO overflow";
            this.m_chbInterruptRXOverflow.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptTXUnderflow
            // 
            this.m_chbInterruptTXUnderflow.AutoSize = true;
            this.m_chbInterruptTXUnderflow.Location = new System.Drawing.Point(6, 110);
            this.m_chbInterruptTXUnderflow.Name = "m_chbInterruptTXUnderflow";
            this.m_chbInterruptTXUnderflow.Size = new System.Drawing.Size(115, 17);
            this.m_chbInterruptTXUnderflow.TabIndex = 4;
            this.m_chbInterruptTXUnderflow.Text = "TX FIFO underflow";
            this.m_chbInterruptTXUnderflow.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptRXUnderflow
            // 
            this.m_chbInterruptRXUnderflow.AutoSize = true;
            this.m_chbInterruptRXUnderflow.Location = new System.Drawing.Point(193, 86);
            this.m_chbInterruptRXUnderflow.Name = "m_chbInterruptRXUnderflow";
            this.m_chbInterruptRXUnderflow.Size = new System.Drawing.Size(116, 17);
            this.m_chbInterruptRXUnderflow.TabIndex = 12;
            this.m_chbInterruptRXUnderflow.Text = "RX FIFO underflow";
            this.m_chbInterruptRXUnderflow.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptTXOverflow
            // 
            this.m_chbInterruptTXOverflow.AutoSize = true;
            this.m_chbInterruptTXOverflow.Location = new System.Drawing.Point(6, 86);
            this.m_chbInterruptTXOverflow.Name = "m_chbInterruptTXOverflow";
            this.m_chbInterruptTXOverflow.Size = new System.Drawing.Size(109, 17);
            this.m_chbInterruptTXOverflow.TabIndex = 3;
            this.m_chbInterruptTXOverflow.Text = "TX FIFO overflow";
            this.m_chbInterruptTXOverflow.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptRXTrigger
            // 
            this.m_chbInterruptRXTrigger.AutoSize = true;
            this.m_chbInterruptRXTrigger.Location = new System.Drawing.Point(193, 155);
            this.m_chbInterruptRXTrigger.Name = "m_chbInterruptRXTrigger";
            this.m_chbInterruptRXTrigger.Size = new System.Drawing.Size(92, 17);
            this.m_chbInterruptRXTrigger.TabIndex = 15;
            this.m_chbInterruptRXTrigger.Text = "RX FIFO level";
            this.m_chbInterruptRXTrigger.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptTXEmpty
            // 
            this.m_chbInterruptTXEmpty.AutoSize = true;
            this.m_chbInterruptTXEmpty.Location = new System.Drawing.Point(6, 64);
            this.m_chbInterruptTXEmpty.Name = "m_chbInterruptTXEmpty";
            this.m_chbInterruptTXEmpty.Size = new System.Drawing.Size(97, 17);
            this.m_chbInterruptTXEmpty.TabIndex = 2;
            this.m_chbInterruptTXEmpty.Text = "TX FIFO empty";
            this.m_chbInterruptTXEmpty.UseVisualStyleBackColor = true;
            // 
            // m_grpIntrSources
            // 
            this.m_grpIntrSources.Controls.Add(this.m_numRXBreakWidth);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXBreakDetected);
            this.m_grpIntrSources.Controls.Add(this.m_lblRXBreakWidth);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptTXTrigger);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXTrigger);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptUARTDone);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXParityErr);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptTXNotFull);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptTXLostArb);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXFrameErr);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXNotEmpty);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptTXEmpty);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXFull);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptTxNack);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptTXOverflow);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXOverflow);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptRXUnderflow);
            this.m_grpIntrSources.Controls.Add(this.m_chbInterruptTXUnderflow);
            this.m_grpIntrSources.Location = new System.Drawing.Point(3, 100);
            this.m_grpIntrSources.Name = "m_grpIntrSources";
            this.m_grpIntrSources.Size = new System.Drawing.Size(442, 205);
            this.m_grpIntrSources.TabIndex = 3;
            this.m_grpIntrSources.TabStop = false;
            this.m_grpIntrSources.Text = "Interrupt sources";
            // 
            // m_numRXBreakWidth
            // 
            this.m_numRXBreakWidth.Enabled = false;
            this.m_numRXBreakWidth.Location = new System.Drawing.Point(373, 176);
            this.m_numRXBreakWidth.Name = "m_numRXBreakWidth";
            this.m_numRXBreakWidth.Size = new System.Drawing.Size(54, 20);
            this.m_numRXBreakWidth.TabIndex = 7;
            // 
            // m_chbInterruptRXBreakDetected
            // 
            this.m_chbInterruptRXBreakDetected.AutoSize = true;
            this.m_chbInterruptRXBreakDetected.Location = new System.Drawing.Point(193, 177);
            this.m_chbInterruptRXBreakDetected.Name = "m_chbInterruptRXBreakDetected";
            this.m_chbInterruptRXBreakDetected.Size = new System.Drawing.Size(99, 17);
            this.m_chbInterruptRXBreakDetected.TabIndex = 16;
            this.m_chbInterruptRXBreakDetected.Text = "Break detected";
            this.m_chbInterruptRXBreakDetected.UseVisualStyleBackColor = true;
            // 
            // m_lblRXBreakWidth
            // 
            this.m_lblRXBreakWidth.AutoSize = true;
            this.m_lblRXBreakWidth.Enabled = false;
            this.m_lblRXBreakWidth.Location = new System.Drawing.Point(306, 178);
            this.m_lblRXBreakWidth.Name = "m_lblRXBreakWidth";
            this.m_lblRXBreakWidth.Size = new System.Drawing.Size(66, 13);
            this.m_lblRXBreakWidth.TabIndex = 8;
            this.m_lblRXBreakWidth.Text = "Break width:";
            // 
            // m_chbInterruptRXParityErr
            // 
            this.m_chbInterruptRXParityErr.AutoSize = true;
            this.m_chbInterruptRXParityErr.Location = new System.Drawing.Point(193, 132);
            this.m_chbInterruptRXParityErr.Name = "m_chbInterruptRXParityErr";
            this.m_chbInterruptRXParityErr.Size = new System.Drawing.Size(93, 17);
            this.m_chbInterruptRXParityErr.TabIndex = 14;
            this.m_chbInterruptRXParityErr.Text = "RX parity error";
            this.m_chbInterruptRXParityErr.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptTXNotFull
            // 
            this.m_chbInterruptTXNotFull.AutoSize = true;
            this.m_chbInterruptTXNotFull.Location = new System.Drawing.Point(6, 42);
            this.m_chbInterruptTXNotFull.Name = "m_chbInterruptTXNotFull";
            this.m_chbInterruptTXNotFull.Size = new System.Drawing.Size(100, 17);
            this.m_chbInterruptTXNotFull.TabIndex = 1;
            this.m_chbInterruptTXNotFull.Text = "TX FIFO not full";
            this.m_chbInterruptTXNotFull.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptTXLostArb
            // 
            this.m_chbInterruptTXLostArb.AutoSize = true;
            this.m_chbInterruptTXLostArb.Location = new System.Drawing.Point(6, 132);
            this.m_chbInterruptTXLostArb.Name = "m_chbInterruptTXLostArb";
            this.m_chbInterruptTXLostArb.Size = new System.Drawing.Size(108, 17);
            this.m_chbInterruptTXLostArb.TabIndex = 5;
            this.m_chbInterruptTXLostArb.Text = "TX lost arbitration";
            this.m_chbInterruptTXLostArb.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptRXFrameErr
            // 
            this.m_chbInterruptRXFrameErr.AutoSize = true;
            this.m_chbInterruptRXFrameErr.Location = new System.Drawing.Point(193, 110);
            this.m_chbInterruptRXFrameErr.Name = "m_chbInterruptRXFrameErr";
            this.m_chbInterruptRXFrameErr.Size = new System.Drawing.Size(94, 17);
            this.m_chbInterruptRXFrameErr.TabIndex = 13;
            this.m_chbInterruptRXFrameErr.Text = "RX frame error";
            this.m_chbInterruptRXFrameErr.UseVisualStyleBackColor = true;
            // 
            // m_chbInterruptTxNack
            // 
            this.m_chbInterruptTxNack.AutoSize = true;
            this.m_chbInterruptTxNack.Location = new System.Drawing.Point(6, 154);
            this.m_chbInterruptTxNack.Name = "m_chbInterruptTxNack";
            this.m_chbInterruptTxNack.Size = new System.Drawing.Size(72, 17);
            this.m_chbInterruptTxNack.TabIndex = 6;
            this.m_chbInterruptTxNack.Text = "TX NACK";
            this.m_chbInterruptTxNack.UseVisualStyleBackColor = true;
            // 
            // m_rbExternal
            // 
            this.m_rbExternal.AutoSize = true;
            this.m_rbExternal.Location = new System.Drawing.Point(6, 65);
            this.m_rbExternal.Name = "m_rbExternal";
            this.m_rbExternal.Size = new System.Drawing.Size(63, 17);
            this.m_rbExternal.TabIndex = 2;
            this.m_rbExternal.TabStop = true;
            this.m_rbExternal.Text = "External";
            this.m_rbExternal.UseVisualStyleBackColor = true;
            // 
            // m_rbInternal
            // 
            this.m_rbInternal.AutoSize = true;
            this.m_rbInternal.Location = new System.Drawing.Point(6, 42);
            this.m_rbInternal.Name = "m_rbInternal";
            this.m_rbInternal.Size = new System.Drawing.Size(60, 17);
            this.m_rbInternal.TabIndex = 1;
            this.m_rbInternal.TabStop = true;
            this.m_rbInternal.Text = "Internal";
            this.m_rbInternal.UseVisualStyleBackColor = true;
            // 
            // m_rbNone
            // 
            this.m_rbNone.AutoSize = true;
            this.m_rbNone.Location = new System.Drawing.Point(6, 19);
            this.m_rbNone.Name = "m_rbNone";
            this.m_rbNone.Size = new System.Drawing.Size(51, 17);
            this.m_rbNone.TabIndex = 0;
            this.m_rbNone.TabStop = true;
            this.m_rbNone.Text = "None";
            this.m_rbNone.UseVisualStyleBackColor = true;
            // 
            // m_numTXBufferSize
            // 
            this.m_numTXBufferSize.Location = new System.Drawing.Point(96, 44);
            this.m_numTXBufferSize.Name = "m_numTXBufferSize";
            this.m_numTXBufferSize.Size = new System.Drawing.Size(68, 20);
            this.m_numTXBufferSize.TabIndex = 1;
            this.m_numTXBufferSize.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // m_lblTXBufferSize
            // 
            this.m_lblTXBufferSize.AutoSize = true;
            this.m_lblTXBufferSize.Location = new System.Drawing.Point(6, 46);
            this.m_lblTXBufferSize.Name = "m_lblTXBufferSize";
            this.m_lblTXBufferSize.Size = new System.Drawing.Size(75, 13);
            this.m_lblTXBufferSize.TabIndex = 0;
            this.m_lblTXBufferSize.Text = "TX buffer size:";
            // 
            // m_numRXBufferSize
            // 
            this.m_numRXBufferSize.Location = new System.Drawing.Point(96, 18);
            this.m_numRXBufferSize.Name = "m_numRXBufferSize";
            this.m_numRXBufferSize.Size = new System.Drawing.Size(68, 20);
            this.m_numRXBufferSize.TabIndex = 0;
            this.m_numRXBufferSize.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // m_lblRXBufferSize
            // 
            this.m_lblRXBufferSize.AutoSize = true;
            this.m_lblRXBufferSize.Location = new System.Drawing.Point(6, 20);
            this.m_lblRXBufferSize.Name = "m_lblRXBufferSize";
            this.m_lblRXBufferSize.Size = new System.Drawing.Size(76, 13);
            this.m_lblRXBufferSize.TabIndex = 0;
            this.m_lblRXBufferSize.Text = "RX buffer size:";
            // 
            // m_grpBuffSizes
            // 
            this.m_grpBuffSizes.Controls.Add(this.m_chbByteMode);
            this.m_grpBuffSizes.Controls.Add(this.m_numTXBufferSize);
            this.m_grpBuffSizes.Controls.Add(this.m_lblTXBufferSize);
            this.m_grpBuffSizes.Controls.Add(this.m_numRXBufferSize);
            this.m_grpBuffSizes.Controls.Add(this.m_lblRXBufferSize);
            this.m_grpBuffSizes.Location = new System.Drawing.Point(3, 3);
            this.m_grpBuffSizes.Name = "m_grpBuffSizes";
            this.m_grpBuffSizes.Size = new System.Drawing.Size(181, 91);
            this.m_grpBuffSizes.TabIndex = 0;
            this.m_grpBuffSizes.TabStop = false;
            this.m_grpBuffSizes.Text = "Buffers size";
            // 
            // m_chbByteMode
            // 
            this.m_chbByteMode.AutoSize = true;
            this.m_chbByteMode.Location = new System.Drawing.Point(11, 70);
            this.m_chbByteMode.Name = "m_chbByteMode";
            this.m_chbByteMode.Size = new System.Drawing.Size(76, 17);
            this.m_chbByteMode.TabIndex = 2;
            this.m_chbByteMode.Text = "Byte mode";
            this.m_chbByteMode.UseVisualStyleBackColor = true;
            // 
            // m_grpMultiProcessMode
            // 
            this.m_grpMultiProcessMode.Controls.Add(this.m_chbAcceptAddress);
            this.m_grpMultiProcessMode.Controls.Add(this.m_numAddressMask);
            this.m_grpMultiProcessMode.Controls.Add(this.m_chbEnMultiProcMode);
            this.m_grpMultiProcessMode.Controls.Add(this.m_numAddress);
            this.m_grpMultiProcessMode.Controls.Add(this.m_lblAddress);
            this.m_grpMultiProcessMode.Controls.Add(this.m_lblMask);
            this.m_grpMultiProcessMode.Location = new System.Drawing.Point(3, 366);
            this.m_grpMultiProcessMode.Name = "m_grpMultiProcessMode";
            this.m_grpMultiProcessMode.Size = new System.Drawing.Size(250, 91);
            this.m_grpMultiProcessMode.TabIndex = 6;
            this.m_grpMultiProcessMode.TabStop = false;
            // 
            // m_chbAcceptAddress
            // 
            this.m_chbAcceptAddress.AutoSize = true;
            this.m_chbAcceptAddress.Location = new System.Drawing.Point(6, 70);
            this.m_chbAcceptAddress.Name = "m_chbAcceptAddress";
            this.m_chbAcceptAddress.Size = new System.Drawing.Size(201, 17);
            this.m_chbAcceptAddress.TabIndex = 2;
            this.m_chbAcceptAddress.Text = "Accept matching address in RX FIFO";
            this.m_chbAcceptAddress.UseVisualStyleBackColor = true;
            // 
            // m_numAddressMask
            // 
            this.m_numAddressMask.Hexadecimal = true;
            this.m_numAddressMask.Location = new System.Drawing.Point(92, 44);
            this.m_numAddressMask.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.m_numAddressMask.Name = "m_numAddressMask";
            this.m_numAddressMask.Size = new System.Drawing.Size(54, 20);
            this.m_numAddressMask.TabIndex = 1;
            // 
            // m_chbEnMultiProcMode
            // 
            this.m_chbEnMultiProcMode.AutoSize = true;
            this.m_chbEnMultiProcMode.Location = new System.Drawing.Point(6, 0);
            this.m_chbEnMultiProcMode.Name = "m_chbEnMultiProcMode";
            this.m_chbEnMultiProcMode.Size = new System.Drawing.Size(123, 17);
            this.m_chbEnMultiProcMode.TabIndex = 5;
            this.m_chbEnMultiProcMode.Text = "Multiprocessor mode";
            this.m_chbEnMultiProcMode.UseVisualStyleBackColor = true;
            // 
            // m_numAddress
            // 
            this.m_numAddress.Hexadecimal = true;
            this.m_numAddress.Location = new System.Drawing.Point(92, 18);
            this.m_numAddress.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.m_numAddress.Name = "m_numAddress";
            this.m_numAddress.Size = new System.Drawing.Size(54, 20);
            this.m_numAddress.TabIndex = 0;
            // 
            // m_lblAddress
            // 
            this.m_lblAddress.AutoSize = true;
            this.m_lblAddress.Location = new System.Drawing.Point(6, 21);
            this.m_lblAddress.Name = "m_lblAddress";
            this.m_lblAddress.Size = new System.Drawing.Size(74, 13);
            this.m_lblAddress.TabIndex = 0;
            this.m_lblAddress.Text = "Address (hex):";
            // 
            // m_lblMask
            // 
            this.m_lblMask.AutoSize = true;
            this.m_lblMask.Location = new System.Drawing.Point(6, 46);
            this.m_lblMask.Name = "m_lblMask";
            this.m_lblMask.Size = new System.Drawing.Size(62, 13);
            this.m_lblMask.TabIndex = 0;
            this.m_lblMask.Text = "Mask (hex):";
            // 
            // m_grpIntrConn
            // 
            this.m_grpIntrConn.Controls.Add(this.m_rbExternal);
            this.m_grpIntrConn.Controls.Add(this.m_rbNone);
            this.m_grpIntrConn.Controls.Add(this.m_rbInternal);
            this.m_grpIntrConn.Location = new System.Drawing.Point(190, 3);
            this.m_grpIntrConn.Name = "m_grpIntrConn";
            this.m_grpIntrConn.Size = new System.Drawing.Size(132, 91);
            this.m_grpIntrConn.TabIndex = 1;
            this.m_grpIntrConn.TabStop = false;
            this.m_grpIntrConn.Text = "Interrupt";
            // 
            // m_grpRxFifoDrop
            // 
            this.m_grpRxFifoDrop.Controls.Add(this.m_chbDropOnFrameError);
            this.m_grpRxFifoDrop.Controls.Add(this.m_chbDropOnParityError);
            this.m_grpRxFifoDrop.Location = new System.Drawing.Point(259, 366);
            this.m_grpRxFifoDrop.Name = "m_grpRxFifoDrop";
            this.m_grpRxFifoDrop.Size = new System.Drawing.Size(186, 64);
            this.m_grpRxFifoDrop.TabIndex = 7;
            this.m_grpRxFifoDrop.TabStop = false;
            this.m_grpRxFifoDrop.Text = "RX FIFO drop";
            // 
            // m_chbDropOnFrameError
            // 
            this.m_chbDropOnFrameError.AutoSize = true;
            this.m_chbDropOnFrameError.Location = new System.Drawing.Point(6, 42);
            this.m_chbDropOnFrameError.Name = "m_chbDropOnFrameError";
            this.m_chbDropOnFrameError.Size = new System.Drawing.Size(93, 17);
            this.m_chbDropOnFrameError.TabIndex = 1;
            this.m_chbDropOnFrameError.Text = "On frame error";
            this.m_chbDropOnFrameError.UseVisualStyleBackColor = true;
            // 
            // m_chbDropOnParityError
            // 
            this.m_chbDropOnParityError.AutoSize = true;
            this.m_chbDropOnParityError.Location = new System.Drawing.Point(6, 18);
            this.m_chbDropOnParityError.Name = "m_chbDropOnParityError";
            this.m_chbDropOnParityError.Size = new System.Drawing.Size(92, 17);
            this.m_chbDropOnParityError.TabIndex = 0;
            this.m_chbDropOnParityError.Text = "On parity error";
            this.m_chbDropOnParityError.UseVisualStyleBackColor = true;
            // 
            // m_grpControlFlow
            // 
            this.m_grpControlFlow.Controls.Add(this.m_chbCts);
            this.m_grpControlFlow.Controls.Add(this.m_chbRts);
            this.m_grpControlFlow.Controls.Add(this.m_panelCtsControlFlow);
            this.m_grpControlFlow.Controls.Add(this.m_panelRtsControlFlow);
            this.m_grpControlFlow.Location = new System.Drawing.Point(3, 463);
            this.m_grpControlFlow.Name = "m_grpControlFlow";
            this.m_grpControlFlow.Size = new System.Drawing.Size(442, 78);
            this.m_grpControlFlow.TabIndex = 8;
            this.m_grpControlFlow.TabStop = false;
            this.m_grpControlFlow.Text = "Flow control";
            // 
            // m_chbCts
            // 
            this.m_chbCts.AutoSize = true;
            this.m_chbCts.Location = new System.Drawing.Point(6, 48);
            this.m_chbCts.Name = "m_chbCts";
            this.m_chbCts.Size = new System.Drawing.Size(47, 17);
            this.m_chbCts.TabIndex = 2;
            this.m_chbCts.Text = "CTS";
            this.m_chbCts.UseVisualStyleBackColor = true;
            // 
            // m_chbRts
            // 
            this.m_chbRts.AutoSize = true;
            this.m_chbRts.Location = new System.Drawing.Point(6, 21);
            this.m_chbRts.Name = "m_chbRts";
            this.m_chbRts.Size = new System.Drawing.Size(48, 17);
            this.m_chbRts.TabIndex = 0;
            this.m_chbRts.Text = "RTS";
            this.m_chbRts.UseVisualStyleBackColor = true;
            // 
            // m_panelCtsControlFlow
            // 
            this.m_panelCtsControlFlow.Controls.Add(this.m_cbCtsPolarity);
            this.m_panelCtsControlFlow.Controls.Add(this.m_lblCtsPolarity);
            this.m_panelCtsControlFlow.Location = new System.Drawing.Point(65, 44);
            this.m_panelCtsControlFlow.Name = "m_panelCtsControlFlow";
            this.m_panelCtsControlFlow.Size = new System.Drawing.Size(368, 26);
            this.m_panelCtsControlFlow.TabIndex = 3;
            // 
            // m_cbCtsPolarity
            // 
            this.m_cbCtsPolarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbCtsPolarity.FormattingEnabled = true;
            this.m_cbCtsPolarity.Location = new System.Drawing.Point(65, 2);
            this.m_cbCtsPolarity.Name = "m_cbCtsPolarity";
            this.m_cbCtsPolarity.Size = new System.Drawing.Size(106, 21);
            this.m_cbCtsPolarity.TabIndex = 0;
            // 
            // m_lblCtsPolarity
            // 
            this.m_lblCtsPolarity.AutoSize = true;
            this.m_lblCtsPolarity.Location = new System.Drawing.Point(10, 5);
            this.m_lblCtsPolarity.Name = "m_lblCtsPolarity";
            this.m_lblCtsPolarity.Size = new System.Drawing.Size(44, 13);
            this.m_lblCtsPolarity.TabIndex = 5;
            this.m_lblCtsPolarity.Text = "Polarity:";
            // 
            // m_panelRtsControlFlow
            // 
            this.m_panelRtsControlFlow.Controls.Add(this.m_cbRtsPolarity);
            this.m_panelRtsControlFlow.Controls.Add(this.m_numRtsRxFifoTrigger);
            this.m_panelRtsControlFlow.Controls.Add(this.m_lblRxFifoTrigger);
            this.m_panelRtsControlFlow.Controls.Add(this.m_lblRtsPolarity);
            this.m_panelRtsControlFlow.Location = new System.Drawing.Point(65, 16);
            this.m_panelRtsControlFlow.Name = "m_panelRtsControlFlow";
            this.m_panelRtsControlFlow.Size = new System.Drawing.Size(368, 27);
            this.m_panelRtsControlFlow.TabIndex = 1;
            // 
            // m_cbRtsPolarity
            // 
            this.m_cbRtsPolarity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRtsPolarity.FormattingEnabled = true;
            this.m_cbRtsPolarity.Location = new System.Drawing.Point(65, 3);
            this.m_cbRtsPolarity.Name = "m_cbRtsPolarity";
            this.m_cbRtsPolarity.Size = new System.Drawing.Size(106, 21);
            this.m_cbRtsPolarity.TabIndex = 0;
            // 
            // m_numRtsRxFifoTrigger
            // 
            this.m_numRtsRxFifoTrigger.Location = new System.Drawing.Point(297, 4);
            this.m_numRtsRxFifoTrigger.Name = "m_numRtsRxFifoTrigger";
            this.m_numRtsRxFifoTrigger.Size = new System.Drawing.Size(54, 20);
            this.m_numRtsRxFifoTrigger.TabIndex = 1;
            // 
            // m_lblRxFifoTrigger
            // 
            this.m_lblRxFifoTrigger.AutoSize = true;
            this.m_lblRxFifoTrigger.Location = new System.Drawing.Point(208, 6);
            this.m_lblRxFifoTrigger.Name = "m_lblRxFifoTrigger";
            this.m_lblRxFifoTrigger.Size = new System.Drawing.Size(83, 13);
            this.m_lblRxFifoTrigger.TabIndex = 6;
            this.m_lblRxFifoTrigger.Text = "RTS FIFO level:";
            // 
            // m_lblRtsPolarity
            // 
            this.m_lblRtsPolarity.AutoSize = true;
            this.m_lblRtsPolarity.Location = new System.Drawing.Point(10, 6);
            this.m_lblRtsPolarity.Name = "m_lblRtsPolarity";
            this.m_lblRtsPolarity.Size = new System.Drawing.Size(44, 13);
            this.m_lblRtsPolarity.TabIndex = 4;
            this.m_lblRtsPolarity.Text = "Polarity:";
            // 
            // m_gbDma
            // 
            this.m_gbDma.Controls.Add(this.m_chbRxOutput);
            this.m_gbDma.Controls.Add(this.m_chbTxOutput);
            this.m_gbDma.Location = new System.Drawing.Point(328, 3);
            this.m_gbDma.Name = "m_gbDma";
            this.m_gbDma.Size = new System.Drawing.Size(117, 91);
            this.m_gbDma.TabIndex = 2;
            this.m_gbDma.TabStop = false;
            this.m_gbDma.Text = "DMA";
            // 
            // m_chbRxOutput
            // 
            this.m_chbRxOutput.AutoSize = true;
            this.m_chbRxOutput.Location = new System.Drawing.Point(11, 19);
            this.m_chbRxOutput.Name = "m_chbRxOutput";
            this.m_chbRxOutput.Size = new System.Drawing.Size(74, 17);
            this.m_chbRxOutput.TabIndex = 0;
            this.m_chbRxOutput.Text = "RX output";
            this.m_chbRxOutput.UseVisualStyleBackColor = true;
            // 
            // m_chbTxOutput
            // 
            this.m_chbTxOutput.AutoSize = true;
            this.m_chbTxOutput.Location = new System.Drawing.Point(11, 42);
            this.m_chbTxOutput.Name = "m_chbTxOutput";
            this.m_chbTxOutput.Size = new System.Drawing.Size(73, 17);
            this.m_chbTxOutput.TabIndex = 1;
            this.m_chbTxOutput.Text = "TX output";
            this.m_chbTxOutput.UseVisualStyleBackColor = true;
            // 
            // m_gbFifoLevels
            // 
            this.m_gbFifoLevels.Controls.Add(this.m_panelRxFifoLevel);
            this.m_gbFifoLevels.Controls.Add(this.m_panelTxFifoLevel);
            this.m_gbFifoLevels.Location = new System.Drawing.Point(3, 311);
            this.m_gbFifoLevels.Name = "m_gbFifoLevels";
            this.m_gbFifoLevels.Size = new System.Drawing.Size(442, 49);
            this.m_gbFifoLevels.TabIndex = 4;
            this.m_gbFifoLevels.TabStop = false;
            this.m_gbFifoLevels.Text = "FIFO levels";
            // 
            // m_panelRxFifoLevel
            // 
            this.m_panelRxFifoLevel.Controls.Add(this.m_lblRxFifo);
            this.m_panelRxFifoLevel.Controls.Add(this.m_cbRXTriggerLevel);
            this.m_panelRxFifoLevel.Enabled = false;
            this.m_panelRxFifoLevel.Location = new System.Drawing.Point(191, 16);
            this.m_panelRxFifoLevel.Name = "m_panelRxFifoLevel";
            this.m_panelRxFifoLevel.Size = new System.Drawing.Size(170, 24);
            this.m_panelRxFifoLevel.TabIndex = 1;
            // 
            // m_lblRxFifo
            // 
            this.m_lblRxFifo.AutoSize = true;
            this.m_lblRxFifo.Location = new System.Drawing.Point(3, 3);
            this.m_lblRxFifo.Name = "m_lblRxFifo";
            this.m_lblRxFifo.Size = new System.Drawing.Size(51, 13);
            this.m_lblRxFifo.TabIndex = 18;
            this.m_lblRxFifo.Text = "RX FIFO:";
            // 
            // m_panelTxFifoLevel
            // 
            this.m_panelTxFifoLevel.Controls.Add(this.m_lblTxFifo);
            this.m_panelTxFifoLevel.Controls.Add(this.m_cbTXTriggerLevel);
            this.m_panelTxFifoLevel.Enabled = false;
            this.m_panelTxFifoLevel.Location = new System.Drawing.Point(3, 16);
            this.m_panelTxFifoLevel.Name = "m_panelTxFifoLevel";
            this.m_panelTxFifoLevel.Size = new System.Drawing.Size(170, 24);
            this.m_panelTxFifoLevel.TabIndex = 0;
            // 
            // m_lblTxFifo
            // 
            this.m_lblTxFifo.AutoSize = true;
            this.m_lblTxFifo.Location = new System.Drawing.Point(3, 3);
            this.m_lblTxFifo.Name = "m_lblTxFifo";
            this.m_lblTxFifo.Size = new System.Drawing.Size(50, 13);
            this.m_lblTxFifo.TabIndex = 17;
            this.m_lblTxFifo.Text = "TX FIFO:";
            // 
            // CyUARTAdvancedTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.Controls.Add(this.m_gbFifoLevels);
            this.Controls.Add(this.m_gbDma);
            this.Controls.Add(this.m_grpControlFlow);
            this.Controls.Add(this.m_grpRxFifoDrop);
            this.Controls.Add(this.m_grpIntrConn);
            this.Controls.Add(this.m_grpMultiProcessMode);
            this.Controls.Add(this.m_grpIntrSources);
            this.Controls.Add(this.m_grpBuffSizes);
            this.Name = "CyUARTAdvancedTab";
            this.Size = new System.Drawing.Size(455, 574);
            this.m_grpIntrSources.ResumeLayout(false);
            this.m_grpIntrSources.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRXBreakWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numTXBufferSize)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRXBufferSize)).EndInit();
            this.m_grpBuffSizes.ResumeLayout(false);
            this.m_grpBuffSizes.PerformLayout();
            this.m_grpMultiProcessMode.ResumeLayout(false);
            this.m_grpMultiProcessMode.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numAddressMask)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numAddress)).EndInit();
            this.m_grpIntrConn.ResumeLayout(false);
            this.m_grpIntrConn.PerformLayout();
            this.m_grpRxFifoDrop.ResumeLayout(false);
            this.m_grpRxFifoDrop.PerformLayout();
            this.m_grpControlFlow.ResumeLayout(false);
            this.m_grpControlFlow.PerformLayout();
            this.m_panelCtsControlFlow.ResumeLayout(false);
            this.m_panelCtsControlFlow.PerformLayout();
            this.m_panelRtsControlFlow.ResumeLayout(false);
            this.m_panelRtsControlFlow.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRtsRxFifoTrigger)).EndInit();
            this.m_gbDma.ResumeLayout(false);
            this.m_gbDma.PerformLayout();
            this.m_gbFifoLevels.ResumeLayout(false);
            this.m_panelRxFifoLevel.ResumeLayout(false);
            this.m_panelRxFifoLevel.PerformLayout();
            this.m_panelTxFifoLevel.ResumeLayout(false);
            this.m_panelTxFifoLevel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox m_cbTXTriggerLevel;
        private System.Windows.Forms.CheckBox m_chbInterruptRXNotEmpty;
        private System.Windows.Forms.ComboBox m_cbRXTriggerLevel;
        private System.Windows.Forms.CheckBox m_chbInterruptRXFull;
        private System.Windows.Forms.CheckBox m_chbInterruptTXTrigger;
        private System.Windows.Forms.CheckBox m_chbInterruptUARTDone;
        private System.Windows.Forms.CheckBox m_chbInterruptRXOverflow;
        private System.Windows.Forms.CheckBox m_chbInterruptTXUnderflow;
        private System.Windows.Forms.CheckBox m_chbInterruptRXUnderflow;
        private System.Windows.Forms.CheckBox m_chbInterruptTXOverflow;
        private System.Windows.Forms.CheckBox m_chbInterruptRXTrigger;
        private System.Windows.Forms.CheckBox m_chbInterruptTXEmpty;
        private System.Windows.Forms.GroupBox m_grpIntrSources;
        private System.Windows.Forms.CheckBox m_chbInterruptTXNotFull;
        private System.Windows.Forms.NumericUpDown m_numTXBufferSize;
        private System.Windows.Forms.Label m_lblTXBufferSize;
        private System.Windows.Forms.NumericUpDown m_numRXBufferSize;
        private System.Windows.Forms.Label m_lblRXBufferSize;
        private System.Windows.Forms.GroupBox m_grpBuffSizes;
        private System.Windows.Forms.CheckBox m_chbInterruptRXParityErr;
        private System.Windows.Forms.CheckBox m_chbInterruptRXFrameErr;
        private System.Windows.Forms.CheckBox m_chbInterruptTxNack;
        private System.Windows.Forms.CheckBox m_chbInterruptTXLostArb;
        private System.Windows.Forms.GroupBox m_grpMultiProcessMode;
        private System.Windows.Forms.Label m_lblMask;
        private System.Windows.Forms.Label m_lblAddress;
        private System.Windows.Forms.CheckBox m_chbEnMultiProcMode;
        private System.Windows.Forms.RadioButton m_rbExternal;
        private System.Windows.Forms.RadioButton m_rbInternal;
        private System.Windows.Forms.RadioButton m_rbNone;
        private System.Windows.Forms.NumericUpDown m_numAddressMask;
        private System.Windows.Forms.NumericUpDown m_numAddress;
        private System.Windows.Forms.GroupBox m_grpIntrConn;
        private System.Windows.Forms.GroupBox m_grpRxFifoDrop;
        private System.Windows.Forms.CheckBox m_chbDropOnFrameError;
        private System.Windows.Forms.CheckBox m_chbDropOnParityError;
        private System.Windows.Forms.CheckBox m_chbAcceptAddress;
        private System.Windows.Forms.GroupBox m_grpControlFlow;
        private System.Windows.Forms.NumericUpDown m_numRtsRxFifoTrigger;
        private System.Windows.Forms.Label m_lblRxFifoTrigger;
        private System.Windows.Forms.Label m_lblCtsPolarity;
        private System.Windows.Forms.Label m_lblRtsPolarity;
        private System.Windows.Forms.ComboBox m_cbRtsPolarity;
        private System.Windows.Forms.ComboBox m_cbCtsPolarity;
        private System.Windows.Forms.CheckBox m_chbCts;
        private System.Windows.Forms.CheckBox m_chbRts;
        private System.Windows.Forms.Panel m_panelRtsControlFlow;
        private System.Windows.Forms.Panel m_panelCtsControlFlow;
        private System.Windows.Forms.CheckBox m_chbByteMode;
        private System.Windows.Forms.GroupBox m_gbDma;
        private System.Windows.Forms.CheckBox m_chbRxOutput;
        private System.Windows.Forms.CheckBox m_chbTxOutput;
        private System.Windows.Forms.GroupBox m_gbFifoLevels;
        private System.Windows.Forms.Label m_lblRxFifo;
        private System.Windows.Forms.Label m_lblTxFifo;
        private System.Windows.Forms.Panel m_panelTxFifoLevel;
        private System.Windows.Forms.Panel m_panelRxFifoLevel;
        private System.Windows.Forms.NumericUpDown m_numRXBreakWidth;
        private System.Windows.Forms.CheckBox m_chbInterruptRXBreakDetected;
        private System.Windows.Forms.Label m_lblRXBreakWidth;

    }
}
