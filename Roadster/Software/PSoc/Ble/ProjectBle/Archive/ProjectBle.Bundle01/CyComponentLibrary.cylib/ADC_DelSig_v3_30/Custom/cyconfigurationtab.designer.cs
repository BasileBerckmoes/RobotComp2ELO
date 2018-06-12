/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


namespace ADC_DelSig_v3_30
{
    partial class CyConfigurationTab
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
            this.m_lblComment = new System.Windows.Forms.Label();
            this.m_tbComment = new System.Windows.Forms.TextBox();
            this.m_lblConfigName = new System.Windows.Forms.Label();
            this.m_tbConfigName = new System.Windows.Forms.TextBox();
            this.m_lblFullConfigName = new System.Windows.Forms.Label();
            this.m_grpModes = new System.Windows.Forms.GroupBox();
            this.m_lblUnknownActRate = new System.Windows.Forms.Label();
            this.m_tbActualRate = new System.Windows.Forms.Label();
            this.m_lblActualRate = new System.Windows.Forms.Label();
            this.panelGlobalIntWarning = new System.Windows.Forms.Panel();
            this.lblGlobalIntWarning = new System.Windows.Forms.Label();
            this.pbInfoImage = new System.Windows.Forms.PictureBox();
            this.m_lblUnknownFreq = new System.Windows.Forms.Label();
            this.m_lblUnknownRate = new System.Windows.Forms.Label();
            this.m_tbClockFreq = new System.Windows.Forms.Label();
            this.m_cbResolution = new System.Windows.Forms.ComboBox();
            this.m_lblRateRange = new System.Windows.Forms.Label();
            this.m_numConvRate = new System.Windows.Forms.NumericUpDown();
            this.m_cbConvMode = new System.Windows.Forms.ComboBox();
            this.m_lblClockFreq = new System.Windows.Forms.Label();
            this.m_lblConvRate = new System.Windows.Forms.Label();
            this.m_lblResolution = new System.Windows.Forms.Label();
            this.m_lblConvMode = new System.Windows.Forms.Label();
            this.m_grpInputMode = new System.Windows.Forms.GroupBox();
            this.m_cbBufferMode = new System.Windows.Forms.ComboBox();
            this.m_lblBufferMode = new System.Windows.Forms.Label();
            this.m_cbBufferGain = new System.Windows.Forms.ComboBox();
            this.m_lblBufferGain = new System.Windows.Forms.Label();
            this.m_cbInputRange = new System.Windows.Forms.ComboBox();
            this.m_lblInputRange = new System.Windows.Forms.Label();
            this.m_grpReference = new System.Windows.Forms.GroupBox();
            this.m_numRefValue = new System.Windows.Forms.NumericUpDown();
            this.m_lblRefValue = new System.Windows.Forms.Label();
            this.m_cbRef = new System.Windows.Forms.ComboBox();
            this.m_lblRef = new System.Windows.Forms.Label();
            this.m_grpAlignment = new System.Windows.Forms.GroupBox();
            this.labelDecCoher = new System.Windows.Forms.Label();
            this.m_cbLeftAlign = new System.Windows.Forms.ComboBox();
            this.m_rbLeft = new System.Windows.Forms.RadioButton();
            this.m_rbRight = new System.Windows.Forms.RadioButton();
            this.m_grpInputRange = new System.Windows.Forms.GroupBox();
            this.m_pictInputRange = new System.Windows.Forms.PictureBox();
            this.errProviderExtClock = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_grpModes.SuspendLayout();
            this.panelGlobalIntWarning.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbInfoImage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numConvRate)).BeginInit();
            this.m_grpInputMode.SuspendLayout();
            this.m_grpReference.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRefValue)).BeginInit();
            this.m_grpAlignment.SuspendLayout();
            this.m_grpInputRange.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_pictInputRange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errProviderExtClock)).BeginInit();
            this.SuspendLayout();
            // 
            // m_lblComment
            // 
            this.m_lblComment.AutoSize = true;
            this.m_lblComment.Location = new System.Drawing.Point(3, 6);
            this.m_lblComment.Name = "m_lblComment";
            this.m_lblComment.Size = new System.Drawing.Size(54, 13);
            this.m_lblComment.TabIndex = 0;
            this.m_lblComment.Text = "Comment:";
            // 
            // m_tbComment
            // 
            this.m_tbComment.Location = new System.Drawing.Point(110, 3);
            this.m_tbComment.MaxLength = 1000;
            this.m_tbComment.Name = "m_tbComment";
            this.m_tbComment.Size = new System.Drawing.Size(434, 20);
            this.m_tbComment.TabIndex = 1;
            // 
            // m_lblConfigName
            // 
            this.m_lblConfigName.AutoSize = true;
            this.m_lblConfigName.Location = new System.Drawing.Point(3, 32);
            this.m_lblConfigName.Name = "m_lblConfigName";
            this.m_lblConfigName.Size = new System.Drawing.Size(101, 13);
            this.m_lblConfigName.TabIndex = 2;
            this.m_lblConfigName.Text = "Configuration name:";
            // 
            // m_tbConfigName
            // 
            this.m_tbConfigName.Location = new System.Drawing.Point(110, 29);
            this.m_tbConfigName.MaxLength = 1000;
            this.m_tbConfigName.Name = "m_tbConfigName";
            this.m_tbConfigName.Size = new System.Drawing.Size(163, 20);
            this.m_tbConfigName.TabIndex = 3;
            // 
            // m_lblFullConfigName
            // 
            this.m_lblFullConfigName.AutoSize = true;
            this.m_lblFullConfigName.Location = new System.Drawing.Point(292, 32);
            this.m_lblFullConfigName.Name = "m_lblFullConfigName";
            this.m_lblFullConfigName.Size = new System.Drawing.Size(120, 13);
            this.m_lblFullConfigName.TabIndex = 4;
            this.m_lblFullConfigName.Text = "ADC_DelSig_1_Config1";
            // 
            // m_grpModes
            // 
            this.m_grpModes.Controls.Add(this.m_lblUnknownActRate);
            this.m_grpModes.Controls.Add(this.m_tbActualRate);
            this.m_grpModes.Controls.Add(this.m_lblActualRate);
            this.m_grpModes.Controls.Add(this.panelGlobalIntWarning);
            this.m_grpModes.Controls.Add(this.m_lblUnknownFreq);
            this.m_grpModes.Controls.Add(this.m_lblUnknownRate);
            this.m_grpModes.Controls.Add(this.m_tbClockFreq);
            this.m_grpModes.Controls.Add(this.m_cbResolution);
            this.m_grpModes.Controls.Add(this.m_lblRateRange);
            this.m_grpModes.Controls.Add(this.m_numConvRate);
            this.m_grpModes.Controls.Add(this.m_cbConvMode);
            this.m_grpModes.Controls.Add(this.m_lblClockFreq);
            this.m_grpModes.Controls.Add(this.m_lblConvRate);
            this.m_grpModes.Controls.Add(this.m_lblResolution);
            this.m_grpModes.Controls.Add(this.m_lblConvMode);
            this.m_grpModes.Location = new System.Drawing.Point(3, 55);
            this.m_grpModes.Name = "m_grpModes";
            this.m_grpModes.Size = new System.Drawing.Size(541, 148);
            this.m_grpModes.TabIndex = 5;
            this.m_grpModes.TabStop = false;
            this.m_grpModes.Text = "Modes";
            // 
            // m_lblUnknownActRate
            // 
            this.m_lblUnknownActRate.AutoSize = true;
            this.m_lblUnknownActRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownActRate.Location = new System.Drawing.Point(133, 100);
            this.m_lblUnknownActRate.Name = "m_lblUnknownActRate";
            this.m_lblUnknownActRate.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownActRate.TabIndex = 15;
            this.m_lblUnknownActRate.Text = "UNKNOWN RATE";
            // 
            // m_tbActualRate
            // 
            this.m_tbActualRate.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_tbActualRate.Location = new System.Drawing.Point(134, 96);
            this.m_tbActualRate.Name = "m_tbActualRate";
            this.m_tbActualRate.Size = new System.Drawing.Size(77, 20);
            this.m_tbActualRate.TabIndex = 14;
            this.m_tbActualRate.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_lblActualRate
            // 
            this.m_lblActualRate.AutoSize = true;
            this.m_lblActualRate.Location = new System.Drawing.Point(6, 100);
            this.m_lblActualRate.Name = "m_lblActualRate";
            this.m_lblActualRate.Size = new System.Drawing.Size(121, 13);
            this.m_lblActualRate.TabIndex = 13;
            this.m_lblActualRate.Text = "Actual conv. rate (SPS):";
            // 
            // panelGlobalIntWarning
            // 
            this.panelGlobalIntWarning.Controls.Add(this.lblGlobalIntWarning);
            this.panelGlobalIntWarning.Controls.Add(this.pbInfoImage);
            this.panelGlobalIntWarning.Location = new System.Drawing.Point(276, 9);
            this.panelGlobalIntWarning.Name = "panelGlobalIntWarning";
            this.panelGlobalIntWarning.Size = new System.Drawing.Size(261, 47);
            this.panelGlobalIntWarning.TabIndex = 12;
            // 
            // lblGlobalIntWarning
            // 
            this.lblGlobalIntWarning.BackColor = System.Drawing.SystemColors.Control;
            this.lblGlobalIntWarning.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.lblGlobalIntWarning.Location = new System.Drawing.Point(21, 6);
            this.lblGlobalIntWarning.Name = "lblGlobalIntWarning";
            this.lblGlobalIntWarning.Size = new System.Drawing.Size(239, 33);
            this.lblGlobalIntWarning.TabIndex = 10;
            this.lblGlobalIntWarning.Text = "You must enable the Global Interrupts in the application (main.c) for this config" +
    "uration to work.";
            // 
            // pbInfoImage
            // 
            this.pbInfoImage.Image = global::ADC_DelSig_v3_30.Resource.Symbol_Information;
            this.pbInfoImage.Location = new System.Drawing.Point(3, 11);
            this.pbInfoImage.Name = "pbInfoImage";
            this.pbInfoImage.Size = new System.Drawing.Size(16, 16);
            this.pbInfoImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbInfoImage.TabIndex = 11;
            this.pbInfoImage.TabStop = false;
            // 
            // m_lblUnknownFreq
            // 
            this.m_lblUnknownFreq.AutoSize = true;
            this.m_lblUnknownFreq.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownFreq.Location = new System.Drawing.Point(133, 126);
            this.m_lblUnknownFreq.Name = "m_lblUnknownFreq";
            this.m_lblUnknownFreq.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownFreq.TabIndex = 12;
            this.m_lblUnknownFreq.Text = "UNKNOWN FREQ";
            // 
            // m_lblUnknownRate
            // 
            this.m_lblUnknownRate.AutoSize = true;
            this.m_lblUnknownRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownRate.Location = new System.Drawing.Point(133, 74);
            this.m_lblUnknownRate.Name = "m_lblUnknownRate";
            this.m_lblUnknownRate.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownRate.TabIndex = 11;
            this.m_lblUnknownRate.Text = "UNKNOWN RATE";
            // 
            // m_tbClockFreq
            // 
            this.m_tbClockFreq.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_tbClockFreq.Location = new System.Drawing.Point(134, 122);
            this.m_tbClockFreq.Name = "m_tbClockFreq";
            this.m_tbClockFreq.Size = new System.Drawing.Size(96, 20);
            this.m_tbClockFreq.TabIndex = 10;
            this.m_tbClockFreq.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_cbResolution
            // 
            this.m_cbResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbResolution.FormattingEnabled = true;
            this.m_cbResolution.Location = new System.Drawing.Point(134, 46);
            this.m_cbResolution.Name = "m_cbResolution";
            this.m_cbResolution.Size = new System.Drawing.Size(51, 21);
            this.m_cbResolution.TabIndex = 5;
            // 
            // m_lblRateRange
            // 
            this.m_lblRateRange.AutoSize = true;
            this.m_lblRateRange.Location = new System.Drawing.Point(228, 74);
            this.m_lblRateRange.Name = "m_lblRateRange";
            this.m_lblRateRange.Size = new System.Drawing.Size(39, 13);
            this.m_lblRateRange.TabIndex = 8;
            this.m_lblRateRange.Text = "Range";
            // 
            // m_numConvRate
            // 
            this.m_numConvRate.Location = new System.Drawing.Point(134, 72);
            this.m_numConvRate.Name = "m_numConvRate";
            this.m_numConvRate.Size = new System.Drawing.Size(77, 20);
            this.m_numConvRate.TabIndex = 6;
            // 
            // m_cbConvMode
            // 
            this.m_cbConvMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbConvMode.FormattingEnabled = true;
            this.m_cbConvMode.Location = new System.Drawing.Point(134, 19);
            this.m_cbConvMode.Name = "m_cbConvMode";
            this.m_cbConvMode.Size = new System.Drawing.Size(136, 21);
            this.m_cbConvMode.TabIndex = 4;
            // 
            // m_lblClockFreq
            // 
            this.m_lblClockFreq.AutoSize = true;
            this.m_lblClockFreq.Location = new System.Drawing.Point(6, 126);
            this.m_lblClockFreq.Name = "m_lblClockFreq";
            this.m_lblClockFreq.Size = new System.Drawing.Size(115, 13);
            this.m_lblClockFreq.TabIndex = 3;
            this.m_lblClockFreq.Text = "Clock frequency (kHz):";
            // 
            // m_lblConvRate
            // 
            this.m_lblConvRate.AutoSize = true;
            this.m_lblConvRate.Location = new System.Drawing.Point(6, 74);
            this.m_lblConvRate.Name = "m_lblConvRate";
            this.m_lblConvRate.Size = new System.Drawing.Size(114, 13);
            this.m_lblConvRate.TabIndex = 2;
            this.m_lblConvRate.Text = "Conversion rate (SPS):";
            // 
            // m_lblResolution
            // 
            this.m_lblResolution.AutoSize = true;
            this.m_lblResolution.Location = new System.Drawing.Point(7, 48);
            this.m_lblResolution.Name = "m_lblResolution";
            this.m_lblResolution.Size = new System.Drawing.Size(85, 13);
            this.m_lblResolution.TabIndex = 1;
            this.m_lblResolution.Text = "Resolution (bits):";
            // 
            // m_lblConvMode
            // 
            this.m_lblConvMode.AutoSize = true;
            this.m_lblConvMode.Location = new System.Drawing.Point(7, 22);
            this.m_lblConvMode.Name = "m_lblConvMode";
            this.m_lblConvMode.Size = new System.Drawing.Size(92, 13);
            this.m_lblConvMode.TabIndex = 0;
            this.m_lblConvMode.Text = "Conversion mode:";
            // 
            // m_grpInputMode
            // 
            this.m_grpInputMode.Controls.Add(this.m_cbBufferMode);
            this.m_grpInputMode.Controls.Add(this.m_lblBufferMode);
            this.m_grpInputMode.Controls.Add(this.m_cbBufferGain);
            this.m_grpInputMode.Controls.Add(this.m_lblBufferGain);
            this.m_grpInputMode.Controls.Add(this.m_cbInputRange);
            this.m_grpInputMode.Controls.Add(this.m_lblInputRange);
            this.m_grpInputMode.Location = new System.Drawing.Point(3, 209);
            this.m_grpInputMode.Name = "m_grpInputMode";
            this.m_grpInputMode.Size = new System.Drawing.Size(286, 102);
            this.m_grpInputMode.TabIndex = 6;
            this.m_grpInputMode.TabStop = false;
            this.m_grpInputMode.Text = "Input options";
            // 
            // m_cbBufferMode
            // 
            this.m_cbBufferMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbBufferMode.FormattingEnabled = true;
            this.m_cbBufferMode.Location = new System.Drawing.Point(79, 73);
            this.m_cbBufferMode.Name = "m_cbBufferMode";
            this.m_cbBufferMode.Size = new System.Drawing.Size(90, 21);
            this.m_cbBufferMode.TabIndex = 18;
            // 
            // m_lblBufferMode
            // 
            this.m_lblBufferMode.AutoSize = true;
            this.m_lblBufferMode.Location = new System.Drawing.Point(6, 76);
            this.m_lblBufferMode.Name = "m_lblBufferMode";
            this.m_lblBufferMode.Size = new System.Drawing.Size(67, 13);
            this.m_lblBufferMode.TabIndex = 17;
            this.m_lblBufferMode.Text = "Buffer mode:";
            // 
            // m_cbBufferGain
            // 
            this.m_cbBufferGain.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbBufferGain.FormattingEnabled = true;
            this.m_cbBufferGain.Location = new System.Drawing.Point(79, 46);
            this.m_cbBufferGain.Name = "m_cbBufferGain";
            this.m_cbBufferGain.Size = new System.Drawing.Size(51, 21);
            this.m_cbBufferGain.TabIndex = 16;
            // 
            // m_lblBufferGain
            // 
            this.m_lblBufferGain.AutoSize = true;
            this.m_lblBufferGain.Location = new System.Drawing.Point(6, 49);
            this.m_lblBufferGain.Name = "m_lblBufferGain";
            this.m_lblBufferGain.Size = new System.Drawing.Size(61, 13);
            this.m_lblBufferGain.TabIndex = 15;
            this.m_lblBufferGain.Text = "Buffer gain:";
            // 
            // m_cbInputRange
            // 
            this.m_cbInputRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbInputRange.FormattingEnabled = true;
            this.m_cbInputRange.Location = new System.Drawing.Point(79, 19);
            this.m_cbInputRange.Name = "m_cbInputRange";
            this.m_cbInputRange.Size = new System.Drawing.Size(191, 21);
            this.m_cbInputRange.TabIndex = 14;
            this.m_cbInputRange.Format += new System.Windows.Forms.ListControlConvertEventHandler(this.m_cbInputRange_Format);
            // 
            // m_lblInputRange
            // 
            this.m_lblInputRange.AutoSize = true;
            this.m_lblInputRange.Location = new System.Drawing.Point(6, 22);
            this.m_lblInputRange.Name = "m_lblInputRange";
            this.m_lblInputRange.Size = new System.Drawing.Size(64, 13);
            this.m_lblInputRange.TabIndex = 13;
            this.m_lblInputRange.Text = "Input range:";
            // 
            // m_grpReference
            // 
            this.m_grpReference.Controls.Add(this.m_numRefValue);
            this.m_grpReference.Controls.Add(this.m_lblRefValue);
            this.m_grpReference.Controls.Add(this.m_cbRef);
            this.m_grpReference.Controls.Add(this.m_lblRef);
            this.m_grpReference.Location = new System.Drawing.Point(3, 317);
            this.m_grpReference.Name = "m_grpReference";
            this.m_grpReference.Size = new System.Drawing.Size(286, 76);
            this.m_grpReference.TabIndex = 7;
            this.m_grpReference.TabStop = false;
            this.m_grpReference.Text = "Reference";
            // 
            // m_numRefValue
            // 
            this.m_numRefValue.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.m_numRefValue.Location = new System.Drawing.Point(72, 47);
            this.m_numRefValue.Name = "m_numRefValue";
            this.m_numRefValue.Size = new System.Drawing.Size(68, 20);
            this.m_numRefValue.TabIndex = 3;
            // 
            // m_lblRefValue
            // 
            this.m_lblRefValue.AutoSize = true;
            this.m_lblRefValue.Location = new System.Drawing.Point(6, 49);
            this.m_lblRefValue.Name = "m_lblRefValue";
            this.m_lblRefValue.Size = new System.Drawing.Size(45, 13);
            this.m_lblRefValue.TabIndex = 2;
            this.m_lblRefValue.Text = "Vref (V):";
            // 
            // m_cbRef
            // 
            this.m_cbRef.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRef.FormattingEnabled = true;
            this.m_cbRef.Location = new System.Drawing.Point(72, 19);
            this.m_cbRef.Name = "m_cbRef";
            this.m_cbRef.Size = new System.Drawing.Size(198, 21);
            this.m_cbRef.TabIndex = 1;
            // 
            // m_lblRef
            // 
            this.m_lblRef.AutoSize = true;
            this.m_lblRef.Location = new System.Drawing.Point(6, 22);
            this.m_lblRef.Name = "m_lblRef";
            this.m_lblRef.Size = new System.Drawing.Size(60, 13);
            this.m_lblRef.TabIndex = 0;
            this.m_lblRef.Text = "Reference:";
            // 
            // m_grpAlignment
            // 
            this.m_grpAlignment.Controls.Add(this.labelDecCoher);
            this.m_grpAlignment.Controls.Add(this.m_cbLeftAlign);
            this.m_grpAlignment.Controls.Add(this.m_rbLeft);
            this.m_grpAlignment.Controls.Add(this.m_rbRight);
            this.m_grpAlignment.Location = new System.Drawing.Point(3, 399);
            this.m_grpAlignment.Name = "m_grpAlignment";
            this.m_grpAlignment.Size = new System.Drawing.Size(286, 71);
            this.m_grpAlignment.TabIndex = 8;
            this.m_grpAlignment.TabStop = false;
            this.m_grpAlignment.Text = "Alignment";
            // 
            // labelDecCoher
            // 
            this.labelDecCoher.AutoSize = true;
            this.labelDecCoher.Location = new System.Drawing.Point(175, 21);
            this.labelDecCoher.Name = "labelDecCoher";
            this.labelDecCoher.Size = new System.Drawing.Size(95, 13);
            this.labelDecCoher.TabIndex = 14;
            this.labelDecCoher.Text = "Coherency = LOW";
            // 
            // m_cbLeftAlign
            // 
            this.m_cbLeftAlign.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbLeftAlign.FormattingEnabled = true;
            this.m_cbLeftAlign.Items.AddRange(new object[] {
            "24 bits (OVF Protected)",
            "16 bits (Not OVF Protected)"});
            this.m_cbLeftAlign.Location = new System.Drawing.Point(69, 41);
            this.m_cbLeftAlign.Name = "m_cbLeftAlign";
            this.m_cbLeftAlign.Size = new System.Drawing.Size(198, 21);
            this.m_cbLeftAlign.TabIndex = 2;
            // 
            // m_rbLeft
            // 
            this.m_rbLeft.AutoSize = true;
            this.m_rbLeft.Location = new System.Drawing.Point(6, 42);
            this.m_rbLeft.Name = "m_rbLeft";
            this.m_rbLeft.Size = new System.Drawing.Size(43, 17);
            this.m_rbLeft.TabIndex = 1;
            this.m_rbLeft.TabStop = true;
            this.m_rbLeft.Text = "Left";
            this.m_rbLeft.UseVisualStyleBackColor = true;
            // 
            // m_rbRight
            // 
            this.m_rbRight.AutoSize = true;
            this.m_rbRight.Location = new System.Drawing.Point(6, 19);
            this.m_rbRight.Name = "m_rbRight";
            this.m_rbRight.Size = new System.Drawing.Size(50, 17);
            this.m_rbRight.TabIndex = 0;
            this.m_rbRight.TabStop = true;
            this.m_rbRight.Text = "Right";
            this.m_rbRight.UseVisualStyleBackColor = true;
            // 
            // m_grpInputRange
            // 
            this.m_grpInputRange.Controls.Add(this.m_pictInputRange);
            this.m_grpInputRange.Location = new System.Drawing.Point(295, 209);
            this.m_grpInputRange.Name = "m_grpInputRange";
            this.m_grpInputRange.Size = new System.Drawing.Size(249, 261);
            this.m_grpInputRange.TabIndex = 9;
            this.m_grpInputRange.TabStop = false;
            this.m_grpInputRange.Text = "Input range";
            // 
            // m_pictInputRange
            // 
            this.m_pictInputRange.Image = global::ADC_DelSig_v3_30.Resource.BypassBuffer;
            this.m_pictInputRange.Location = new System.Drawing.Point(8, 16);
            this.m_pictInputRange.Name = "m_pictInputRange";
            this.m_pictInputRange.Size = new System.Drawing.Size(212, 224);
            this.m_pictInputRange.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.m_pictInputRange.TabIndex = 0;
            this.m_pictInputRange.TabStop = false;
            // 
            // errProviderExtClock
            // 
            this.errProviderExtClock.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errProviderExtClock.ContainerControl = this;
            // 
            // CyConfigurationTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_grpInputRange);
            this.Controls.Add(this.m_grpAlignment);
            this.Controls.Add(this.m_grpReference);
            this.Controls.Add(this.m_grpInputMode);
            this.Controls.Add(this.m_grpModes);
            this.Controls.Add(this.m_lblFullConfigName);
            this.Controls.Add(this.m_tbConfigName);
            this.Controls.Add(this.m_lblConfigName);
            this.Controls.Add(this.m_tbComment);
            this.Controls.Add(this.m_lblComment);
            this.Name = "CyConfigurationTab";
            this.Size = new System.Drawing.Size(574, 532);
            this.m_grpModes.ResumeLayout(false);
            this.m_grpModes.PerformLayout();
            this.panelGlobalIntWarning.ResumeLayout(false);
            this.panelGlobalIntWarning.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbInfoImage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numConvRate)).EndInit();
            this.m_grpInputMode.ResumeLayout(false);
            this.m_grpInputMode.PerformLayout();
            this.m_grpReference.ResumeLayout(false);
            this.m_grpReference.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRefValue)).EndInit();
            this.m_grpAlignment.ResumeLayout(false);
            this.m_grpAlignment.PerformLayout();
            this.m_grpInputRange.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_pictInputRange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errProviderExtClock)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblComment;
        private System.Windows.Forms.TextBox m_tbComment;
        private System.Windows.Forms.Label m_lblConfigName;
        private System.Windows.Forms.TextBox m_tbConfigName;
        private System.Windows.Forms.Label m_lblFullConfigName;
        private System.Windows.Forms.GroupBox m_grpModes;
        private System.Windows.Forms.ComboBox m_cbConvMode;
        private System.Windows.Forms.Label m_lblClockFreq;
        private System.Windows.Forms.Label m_lblConvRate;
        private System.Windows.Forms.Label m_lblResolution;
        private System.Windows.Forms.Label m_lblConvMode;
        private System.Windows.Forms.NumericUpDown m_numConvRate;
        private System.Windows.Forms.Label m_lblRateRange;
        private System.Windows.Forms.GroupBox m_grpInputMode;
        private System.Windows.Forms.Label m_lblInputRange;
        private System.Windows.Forms.ComboBox m_cbInputRange;
        private System.Windows.Forms.ComboBox m_cbBufferMode;
        private System.Windows.Forms.Label m_lblBufferMode;
        private System.Windows.Forms.ComboBox m_cbBufferGain;
        private System.Windows.Forms.Label m_lblBufferGain;
        private System.Windows.Forms.GroupBox m_grpReference;
        private System.Windows.Forms.ComboBox m_cbRef;
        private System.Windows.Forms.Label m_lblRef;
        private System.Windows.Forms.Label m_lblRefValue;
        private System.Windows.Forms.NumericUpDown m_numRefValue;
        private System.Windows.Forms.GroupBox m_grpAlignment;
        private System.Windows.Forms.ComboBox m_cbLeftAlign;
        private System.Windows.Forms.RadioButton m_rbLeft;
        private System.Windows.Forms.RadioButton m_rbRight;
        private System.Windows.Forms.GroupBox m_grpInputRange;
        private System.Windows.Forms.PictureBox m_pictInputRange;
        private System.Windows.Forms.ComboBox m_cbResolution;
        private System.Windows.Forms.Label m_tbClockFreq;
        private System.Windows.Forms.Label m_lblUnknownFreq;
        private System.Windows.Forms.Label m_lblUnknownRate;
        private System.Windows.Forms.Label lblGlobalIntWarning;
        private System.Windows.Forms.PictureBox pbInfoImage;
        private System.Windows.Forms.Panel panelGlobalIntWarning;
        private System.Windows.Forms.ErrorProvider errProviderExtClock;
        private System.Windows.Forms.Label m_lblUnknownActRate;
        private System.Windows.Forms.Label m_tbActualRate;
        private System.Windows.Forms.Label m_lblActualRate;
        private System.Windows.Forms.Label labelDecCoher;
    }
}
