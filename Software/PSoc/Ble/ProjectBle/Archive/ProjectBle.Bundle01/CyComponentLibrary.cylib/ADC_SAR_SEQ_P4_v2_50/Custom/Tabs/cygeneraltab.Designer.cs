/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace ADC_SAR_SEQ_P4_v2_50.Tabs
{
    partial class CyGeneralTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyGeneralTab));
            this.m_groupBoxSampleMode = new System.Windows.Forms.GroupBox();
            this.m_rbHardwareSOC = new System.Windows.Forms.RadioButton();
            this.m_rbFreeRun = new System.Windows.Forms.RadioButton();
            this.m_groupBoxClkSrc = new System.Windows.Forms.GroupBox();
            this.m_rbExternal = new System.Windows.Forms.RadioButton();
            this.m_rbInternal = new System.Windows.Forms.RadioButton();
            this.m_groupBoxInputRange = new System.Windows.Forms.GroupBox();
            this.m_labelSingleEndModeRangeValue = new System.Windows.Forms.Label();
            this.m_labelDiffModeRangeValue = new System.Windows.Forms.Label();
            this.m_cbSingleEndNegInput = new System.Windows.Forms.ComboBox();
            this.m_numVrefVal = new System.Windows.Forms.NumericUpDown();
            this.m_cbVrefSel = new System.Windows.Forms.ComboBox();
            this.m_labelSingleEndModeRange = new System.Windows.Forms.Label();
            this.m_labelDiffModeRange = new System.Windows.Forms.Label();
            this.m_labelSingleEndNegInput = new System.Windows.Forms.Label();
            this.m_labelVrefVal = new System.Windows.Forms.Label();
            this.m_labelVrefSel = new System.Windows.Forms.Label();
            this.m_groupBoxResultDataFormat = new System.Windows.Forms.GroupBox();
            this.m_cbSampleAveraged = new System.Windows.Forms.ComboBox();
            this.m_cbAverageMode = new System.Windows.Forms.ComboBox();
            this.m_cbAlterResolution = new System.Windows.Forms.ComboBox();
            this.m_cbDataFormatJustify = new System.Windows.Forms.ComboBox();
            this.m_cbSingleEndResultFormat = new System.Windows.Forms.ComboBox();
            this.m_cbDiffResultFormat = new System.Windows.Forms.ComboBox();
            this.m_labelDiffResultFormat = new System.Windows.Forms.Label();
            this.m_labelSingleEndResultFormat = new System.Windows.Forms.Label();
            this.m_labelDataFormatJustify = new System.Windows.Forms.Label();
            this.m_labelSampleAveraged = new System.Windows.Forms.Label();
            this.m_labelAlterResolution = new System.Windows.Forms.Label();
            this.m_labelAverageMode = new System.Windows.Forms.Label();
            this.m_rbSampleRate = new System.Windows.Forms.RadioButton();
            this.m_rbClkFreq = new System.Windows.Forms.RadioButton();
            this.m_lblActualSRText = new System.Windows.Forms.Label();
            this.m_numScanRate = new System.Windows.Forms.NumericUpDown();
            this.m_numClkFreq = new System.Windows.Forms.NumericUpDown();
            this.m_lblUnknownRate = new System.Windows.Forms.Label();
            this.m_lblUnknownFreq = new System.Windows.Forms.Label();
            this.m_lblActualSampleRate = new System.Windows.Forms.Label();
            this.m_lblUnknownActualRate = new System.Windows.Forms.Label();
            this.m_lblFrequencyRange = new System.Windows.Forms.Label();
            this.m_lblSPSRange = new System.Windows.Forms.Label();
            this.m_groupBoxTiming = new System.Windows.Forms.GroupBox();
            this.m_lblUnknownActualFrequency = new System.Windows.Forms.Label();
            this.m_lblActualClockFrequency = new System.Windows.Forms.Label();
            this.m_lblActualCFText = new System.Windows.Forms.Label();
            this.m_groupBoxLimits = new System.Windows.Forms.GroupBox();
            this.m_cbCompareMode = new System.Windows.Forms.ComboBox();
            this.m_numHighLimit = new System.Windows.Forms.NumericUpDown();
            this.m_numLowLimit = new System.Windows.Forms.NumericUpDown();
            this.m_labelLowLimit = new System.Windows.Forms.Label();
            this.m_labelHighLimit = new System.Windows.Forms.Label();
            this.m_labelCompareMode = new System.Windows.Forms.Label();
            this.errorProviderNotCreator = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_groupBoxSampleMode.SuspendLayout();
            this.m_groupBoxClkSrc.SuspendLayout();
            this.m_groupBoxInputRange.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numVrefVal)).BeginInit();
            this.m_groupBoxResultDataFormat.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numScanRate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClkFreq)).BeginInit();
            this.m_groupBoxTiming.SuspendLayout();
            this.m_groupBoxLimits.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numHighLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numLowLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProviderNotCreator)).BeginInit();
            this.SuspendLayout();
            // 
            // m_groupBoxSampleMode
            // 
            this.m_groupBoxSampleMode.Controls.Add(this.m_rbHardwareSOC);
            this.m_groupBoxSampleMode.Controls.Add(this.m_rbFreeRun);
            resources.ApplyResources(this.m_groupBoxSampleMode, "m_groupBoxSampleMode");
            this.m_groupBoxSampleMode.Name = "m_groupBoxSampleMode";
            this.m_groupBoxSampleMode.TabStop = false;
            // 
            // m_rbHardwareSOC
            // 
            resources.ApplyResources(this.m_rbHardwareSOC, "m_rbHardwareSOC");
            this.m_rbHardwareSOC.Name = "m_rbHardwareSOC";
            this.m_rbHardwareSOC.TabStop = true;
            this.m_rbHardwareSOC.UseVisualStyleBackColor = true;
            this.m_rbHardwareSOC.CheckedChanged += new System.EventHandler(this.rbSampleMode_CheckedChanged);
            // 
            // m_rbFreeRun
            // 
            resources.ApplyResources(this.m_rbFreeRun, "m_rbFreeRun");
            this.m_rbFreeRun.Name = "m_rbFreeRun";
            this.m_rbFreeRun.TabStop = true;
            this.m_rbFreeRun.UseVisualStyleBackColor = true;
            this.m_rbFreeRun.CheckedChanged += new System.EventHandler(this.rbSampleMode_CheckedChanged);
            // 
            // m_groupBoxClkSrc
            // 
            this.m_groupBoxClkSrc.Controls.Add(this.m_rbExternal);
            this.m_groupBoxClkSrc.Controls.Add(this.m_rbInternal);
            resources.ApplyResources(this.m_groupBoxClkSrc, "m_groupBoxClkSrc");
            this.m_groupBoxClkSrc.Name = "m_groupBoxClkSrc";
            this.m_groupBoxClkSrc.TabStop = false;
            // 
            // m_rbExternal
            // 
            resources.ApplyResources(this.m_rbExternal, "m_rbExternal");
            this.m_rbExternal.Name = "m_rbExternal";
            this.m_rbExternal.TabStop = true;
            this.m_rbExternal.UseVisualStyleBackColor = true;
            this.m_rbExternal.CheckedChanged += new System.EventHandler(this.rbInternal_CheckedChanged);
            // 
            // m_rbInternal
            // 
            resources.ApplyResources(this.m_rbInternal, "m_rbInternal");
            this.m_rbInternal.Name = "m_rbInternal";
            this.m_rbInternal.TabStop = true;
            this.m_rbInternal.UseVisualStyleBackColor = true;
            this.m_rbInternal.CheckedChanged += new System.EventHandler(this.rbInternal_CheckedChanged);
            // 
            // m_groupBoxInputRange
            // 
            this.m_groupBoxInputRange.Controls.Add(this.m_labelSingleEndModeRangeValue);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelDiffModeRangeValue);
            this.m_groupBoxInputRange.Controls.Add(this.m_cbSingleEndNegInput);
            this.m_groupBoxInputRange.Controls.Add(this.m_numVrefVal);
            this.m_groupBoxInputRange.Controls.Add(this.m_cbVrefSel);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelSingleEndModeRange);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelDiffModeRange);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelSingleEndNegInput);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelVrefVal);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelVrefSel);
            resources.ApplyResources(this.m_groupBoxInputRange, "m_groupBoxInputRange");
            this.m_groupBoxInputRange.Name = "m_groupBoxInputRange";
            this.m_groupBoxInputRange.TabStop = false;
            // 
            // m_labelSingleEndModeRangeValue
            // 
            resources.ApplyResources(this.m_labelSingleEndModeRangeValue, "m_labelSingleEndModeRangeValue");
            this.m_labelSingleEndModeRangeValue.Name = "m_labelSingleEndModeRangeValue";
            // 
            // m_labelDiffModeRangeValue
            // 
            resources.ApplyResources(this.m_labelDiffModeRangeValue, "m_labelDiffModeRangeValue");
            this.m_labelDiffModeRangeValue.Name = "m_labelDiffModeRangeValue";
            // 
            // m_cbSingleEndNegInput
            // 
            this.m_cbSingleEndNegInput.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSingleEndNegInput.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbSingleEndNegInput, "m_cbSingleEndNegInput");
            this.m_cbSingleEndNegInput.Name = "m_cbSingleEndNegInput";
            this.m_cbSingleEndNegInput.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_numVrefVal
            // 
            this.m_numVrefVal.DecimalPlaces = 3;
            this.m_numVrefVal.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            resources.ApplyResources(this.m_numVrefVal, "m_numVrefVal");
            this.m_numVrefVal.Name = "m_numVrefVal";
            // 
            // m_cbVrefSel
            // 
            this.m_cbVrefSel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbVrefSel.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbVrefSel, "m_cbVrefSel");
            this.m_cbVrefSel.Name = "m_cbVrefSel";
            this.m_cbVrefSel.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelSingleEndModeRange
            // 
            resources.ApplyResources(this.m_labelSingleEndModeRange, "m_labelSingleEndModeRange");
            this.m_labelSingleEndModeRange.Name = "m_labelSingleEndModeRange";
            // 
            // m_labelDiffModeRange
            // 
            resources.ApplyResources(this.m_labelDiffModeRange, "m_labelDiffModeRange");
            this.m_labelDiffModeRange.Name = "m_labelDiffModeRange";
            // 
            // m_labelSingleEndNegInput
            // 
            resources.ApplyResources(this.m_labelSingleEndNegInput, "m_labelSingleEndNegInput");
            this.m_labelSingleEndNegInput.Name = "m_labelSingleEndNegInput";
            // 
            // m_labelVrefVal
            // 
            resources.ApplyResources(this.m_labelVrefVal, "m_labelVrefVal");
            this.m_labelVrefVal.Name = "m_labelVrefVal";
            // 
            // m_labelVrefSel
            // 
            resources.ApplyResources(this.m_labelVrefSel, "m_labelVrefSel");
            this.m_labelVrefSel.Name = "m_labelVrefSel";
            // 
            // m_groupBoxResultDataFormat
            // 
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbSampleAveraged);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbAverageMode);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbAlterResolution);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbDataFormatJustify);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbSingleEndResultFormat);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbDiffResultFormat);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelDiffResultFormat);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelSingleEndResultFormat);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelDataFormatJustify);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelSampleAveraged);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelAlterResolution);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelAverageMode);
            resources.ApplyResources(this.m_groupBoxResultDataFormat, "m_groupBoxResultDataFormat");
            this.m_groupBoxResultDataFormat.Name = "m_groupBoxResultDataFormat";
            this.m_groupBoxResultDataFormat.TabStop = false;
            // 
            // m_cbSampleAveraged
            // 
            this.m_cbSampleAveraged.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSampleAveraged.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbSampleAveraged, "m_cbSampleAveraged");
            this.m_cbSampleAveraged.Name = "m_cbSampleAveraged";
            this.m_cbSampleAveraged.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbAverageMode
            // 
            this.m_cbAverageMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbAverageMode.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbAverageMode, "m_cbAverageMode");
            this.m_cbAverageMode.Name = "m_cbAverageMode";
            this.m_cbAverageMode.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbAlterResolution
            // 
            this.m_cbAlterResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbAlterResolution.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbAlterResolution, "m_cbAlterResolution");
            this.m_cbAlterResolution.Name = "m_cbAlterResolution";
            this.m_cbAlterResolution.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbDataFormatJustify
            // 
            this.m_cbDataFormatJustify.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbDataFormatJustify.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbDataFormatJustify, "m_cbDataFormatJustify");
            this.m_cbDataFormatJustify.Name = "m_cbDataFormatJustify";
            this.m_cbDataFormatJustify.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbSingleEndResultFormat
            // 
            this.m_cbSingleEndResultFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSingleEndResultFormat.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbSingleEndResultFormat, "m_cbSingleEndResultFormat");
            this.m_cbSingleEndResultFormat.Name = "m_cbSingleEndResultFormat";
            this.m_cbSingleEndResultFormat.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbDiffResultFormat
            // 
            this.m_cbDiffResultFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbDiffResultFormat.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbDiffResultFormat, "m_cbDiffResultFormat");
            this.m_cbDiffResultFormat.Name = "m_cbDiffResultFormat";
            this.m_cbDiffResultFormat.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelDiffResultFormat
            // 
            resources.ApplyResources(this.m_labelDiffResultFormat, "m_labelDiffResultFormat");
            this.m_labelDiffResultFormat.Name = "m_labelDiffResultFormat";
            // 
            // m_labelSingleEndResultFormat
            // 
            resources.ApplyResources(this.m_labelSingleEndResultFormat, "m_labelSingleEndResultFormat");
            this.m_labelSingleEndResultFormat.Name = "m_labelSingleEndResultFormat";
            // 
            // m_labelDataFormatJustify
            // 
            resources.ApplyResources(this.m_labelDataFormatJustify, "m_labelDataFormatJustify");
            this.m_labelDataFormatJustify.Name = "m_labelDataFormatJustify";
            // 
            // m_labelSampleAveraged
            // 
            resources.ApplyResources(this.m_labelSampleAveraged, "m_labelSampleAveraged");
            this.m_labelSampleAveraged.Name = "m_labelSampleAveraged";
            // 
            // m_labelAlterResolution
            // 
            resources.ApplyResources(this.m_labelAlterResolution, "m_labelAlterResolution");
            this.m_labelAlterResolution.Name = "m_labelAlterResolution";
            // 
            // m_labelAverageMode
            // 
            resources.ApplyResources(this.m_labelAverageMode, "m_labelAverageMode");
            this.m_labelAverageMode.Name = "m_labelAverageMode";
            // 
            // m_rbSampleRate
            // 
            resources.ApplyResources(this.m_rbSampleRate, "m_rbSampleRate");
            this.m_rbSampleRate.Name = "m_rbSampleRate";
            this.m_rbSampleRate.TabStop = true;
            this.m_rbSampleRate.UseVisualStyleBackColor = true;
            this.m_rbSampleRate.CheckedChanged += new System.EventHandler(this.rbScanRate_CheckedChanged);
            // 
            // m_rbClkFreq
            // 
            resources.ApplyResources(this.m_rbClkFreq, "m_rbClkFreq");
            this.m_rbClkFreq.Name = "m_rbClkFreq";
            this.m_rbClkFreq.TabStop = true;
            this.m_rbClkFreq.UseVisualStyleBackColor = true;
            // 
            // m_lblActualSRText
            // 
            resources.ApplyResources(this.m_lblActualSRText, "m_lblActualSRText");
            this.m_lblActualSRText.Name = "m_lblActualSRText";
            // 
            // m_numScanRate
            // 
            resources.ApplyResources(this.m_numScanRate, "m_numScanRate");
            this.m_numScanRate.Name = "m_numScanRate";
            // 
            // m_numClkFreq
            // 
            this.m_numClkFreq.DecimalPlaces = 3;
            resources.ApplyResources(this.m_numClkFreq, "m_numClkFreq");
            this.m_numClkFreq.Name = "m_numClkFreq";
            // 
            // m_lblUnknownRate
            // 
            resources.ApplyResources(this.m_lblUnknownRate, "m_lblUnknownRate");
            this.m_lblUnknownRate.Name = "m_lblUnknownRate";
            // 
            // m_lblUnknownFreq
            // 
            resources.ApplyResources(this.m_lblUnknownFreq, "m_lblUnknownFreq");
            this.m_lblUnknownFreq.Name = "m_lblUnknownFreq";
            // 
            // m_lblActualSampleRate
            // 
            resources.ApplyResources(this.m_lblActualSampleRate, "m_lblActualSampleRate");
            this.m_lblActualSampleRate.Name = "m_lblActualSampleRate";
            // 
            // m_lblUnknownActualRate
            // 
            resources.ApplyResources(this.m_lblUnknownActualRate, "m_lblUnknownActualRate");
            this.m_lblUnknownActualRate.Name = "m_lblUnknownActualRate";
            // 
            // m_lblFrequencyRange
            // 
            resources.ApplyResources(this.m_lblFrequencyRange, "m_lblFrequencyRange");
            this.m_lblFrequencyRange.Name = "m_lblFrequencyRange";
            // 
            // m_lblSPSRange
            // 
            resources.ApplyResources(this.m_lblSPSRange, "m_lblSPSRange");
            this.m_lblSPSRange.Name = "m_lblSPSRange";
            // 
            // m_groupBoxTiming
            // 
            this.m_groupBoxTiming.Controls.Add(this.m_lblUnknownActualFrequency);
            this.m_groupBoxTiming.Controls.Add(this.m_lblActualClockFrequency);
            this.m_groupBoxTiming.Controls.Add(this.m_lblActualCFText);
            this.m_groupBoxTiming.Controls.Add(this.m_lblSPSRange);
            this.m_groupBoxTiming.Controls.Add(this.m_lblFrequencyRange);
            this.m_groupBoxTiming.Controls.Add(this.m_lblUnknownActualRate);
            this.m_groupBoxTiming.Controls.Add(this.m_lblActualSampleRate);
            this.m_groupBoxTiming.Controls.Add(this.m_lblUnknownFreq);
            this.m_groupBoxTiming.Controls.Add(this.m_lblUnknownRate);
            this.m_groupBoxTiming.Controls.Add(this.m_numClkFreq);
            this.m_groupBoxTiming.Controls.Add(this.m_numScanRate);
            this.m_groupBoxTiming.Controls.Add(this.m_lblActualSRText);
            this.m_groupBoxTiming.Controls.Add(this.m_rbClkFreq);
            this.m_groupBoxTiming.Controls.Add(this.m_rbSampleRate);
            resources.ApplyResources(this.m_groupBoxTiming, "m_groupBoxTiming");
            this.m_groupBoxTiming.Name = "m_groupBoxTiming";
            this.m_groupBoxTiming.TabStop = false;
            // 
            // m_lblUnknownActualFrequency
            // 
            resources.ApplyResources(this.m_lblUnknownActualFrequency, "m_lblUnknownActualFrequency");
            this.m_lblUnknownActualFrequency.Name = "m_lblUnknownActualFrequency";
            // 
            // m_lblActualClockFrequency
            // 
            resources.ApplyResources(this.m_lblActualClockFrequency, "m_lblActualClockFrequency");
            this.m_lblActualClockFrequency.Name = "m_lblActualClockFrequency";
            // 
            // m_lblActualCFText
            // 
            resources.ApplyResources(this.m_lblActualCFText, "m_lblActualCFText");
            this.m_lblActualCFText.Name = "m_lblActualCFText";
            // 
            // m_groupBoxLimits
            // 
            this.m_groupBoxLimits.Controls.Add(this.m_cbCompareMode);
            this.m_groupBoxLimits.Controls.Add(this.m_numHighLimit);
            this.m_groupBoxLimits.Controls.Add(this.m_numLowLimit);
            this.m_groupBoxLimits.Controls.Add(this.m_labelLowLimit);
            this.m_groupBoxLimits.Controls.Add(this.m_labelHighLimit);
            this.m_groupBoxLimits.Controls.Add(this.m_labelCompareMode);
            resources.ApplyResources(this.m_groupBoxLimits, "m_groupBoxLimits");
            this.m_groupBoxLimits.Name = "m_groupBoxLimits";
            this.m_groupBoxLimits.TabStop = false;
            // 
            // m_cbCompareMode
            // 
            this.m_cbCompareMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbCompareMode.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbCompareMode, "m_cbCompareMode");
            this.m_cbCompareMode.Name = "m_cbCompareMode";
            this.m_cbCompareMode.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_numHighLimit
            // 
            this.m_numHighLimit.Hexadecimal = true;
            resources.ApplyResources(this.m_numHighLimit, "m_numHighLimit");
            this.m_numHighLimit.Maximum = new decimal(new int[] {
            70000,
            0,
            0,
            0});
            this.m_numHighLimit.Name = "m_numHighLimit";
            // 
            // m_numLowLimit
            // 
            this.m_numLowLimit.Hexadecimal = true;
            resources.ApplyResources(this.m_numLowLimit, "m_numLowLimit");
            this.m_numLowLimit.Maximum = new decimal(new int[] {
            70000,
            0,
            0,
            0});
            this.m_numLowLimit.Name = "m_numLowLimit";
            // 
            // m_labelLowLimit
            // 
            resources.ApplyResources(this.m_labelLowLimit, "m_labelLowLimit");
            this.m_labelLowLimit.Name = "m_labelLowLimit";
            // 
            // m_labelHighLimit
            // 
            resources.ApplyResources(this.m_labelHighLimit, "m_labelHighLimit");
            this.m_labelHighLimit.Name = "m_labelHighLimit";
            // 
            // m_labelCompareMode
            // 
            resources.ApplyResources(this.m_labelCompareMode, "m_labelCompareMode");
            this.m_labelCompareMode.Name = "m_labelCompareMode";
            // 
            // errorProviderNotCreator
            // 
            this.errorProviderNotCreator.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProviderNotCreator.ContainerControl = this;
            // 
            // CyGeneralTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_groupBoxLimits);
            this.Controls.Add(this.m_groupBoxResultDataFormat);
            this.Controls.Add(this.m_groupBoxInputRange);
            this.Controls.Add(this.m_groupBoxClkSrc);
            this.Controls.Add(this.m_groupBoxSampleMode);
            this.Controls.Add(this.m_groupBoxTiming);
            this.Name = "CyGeneralTab";
            this.m_groupBoxSampleMode.ResumeLayout(false);
            this.m_groupBoxSampleMode.PerformLayout();
            this.m_groupBoxClkSrc.ResumeLayout(false);
            this.m_groupBoxClkSrc.PerformLayout();
            this.m_groupBoxInputRange.ResumeLayout(false);
            this.m_groupBoxInputRange.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numVrefVal)).EndInit();
            this.m_groupBoxResultDataFormat.ResumeLayout(false);
            this.m_groupBoxResultDataFormat.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numScanRate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClkFreq)).EndInit();
            this.m_groupBoxTiming.ResumeLayout(false);
            this.m_groupBoxTiming.PerformLayout();
            this.m_groupBoxLimits.ResumeLayout(false);
            this.m_groupBoxLimits.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numHighLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numLowLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProviderNotCreator)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_groupBoxSampleMode;
        private System.Windows.Forms.RadioButton m_rbHardwareSOC;
        private System.Windows.Forms.RadioButton m_rbFreeRun;
        private System.Windows.Forms.GroupBox m_groupBoxClkSrc;
        private System.Windows.Forms.RadioButton m_rbExternal;
        private System.Windows.Forms.RadioButton m_rbInternal;
        private System.Windows.Forms.GroupBox m_groupBoxInputRange;
        private System.Windows.Forms.ComboBox m_cbVrefSel;
        private System.Windows.Forms.Label m_labelVrefSel;
        private System.Windows.Forms.NumericUpDown m_numVrefVal;
        private System.Windows.Forms.Label m_labelVrefVal;
        private System.Windows.Forms.ComboBox m_cbSingleEndNegInput;
        private System.Windows.Forms.Label m_labelSingleEndNegInput;
        private System.Windows.Forms.Label m_labelSingleEndModeRange;
        private System.Windows.Forms.Label m_labelDiffModeRange;
        private System.Windows.Forms.Label m_labelSingleEndModeRangeValue;
        private System.Windows.Forms.Label m_labelDiffModeRangeValue;
        private System.Windows.Forms.GroupBox m_groupBoxResultDataFormat;
        private System.Windows.Forms.ComboBox m_cbSampleAveraged;
        private System.Windows.Forms.ComboBox m_cbAverageMode;
        private System.Windows.Forms.ComboBox m_cbAlterResolution;
        private System.Windows.Forms.Label m_labelAlterResolution;
        private System.Windows.Forms.Label m_labelAverageMode;
        private System.Windows.Forms.Label m_labelSampleAveraged;
        private System.Windows.Forms.Label m_labelDataFormatJustify;
        private System.Windows.Forms.ComboBox m_cbDataFormatJustify;
        private System.Windows.Forms.ComboBox m_cbSingleEndResultFormat;
        private System.Windows.Forms.Label m_labelSingleEndResultFormat;
        private System.Windows.Forms.ComboBox m_cbDiffResultFormat;
        private System.Windows.Forms.Label m_labelDiffResultFormat;
        private System.Windows.Forms.RadioButton m_rbSampleRate;
        private System.Windows.Forms.RadioButton m_rbClkFreq;

        private System.Windows.Forms.Label m_lblActualSRText;
        private System.Windows.Forms.NumericUpDown m_numScanRate;
        private System.Windows.Forms.NumericUpDown m_numClkFreq;
        private System.Windows.Forms.Label m_lblUnknownRate;
        private System.Windows.Forms.Label m_lblUnknownFreq;
        private System.Windows.Forms.Label m_lblActualSampleRate;
        private System.Windows.Forms.Label m_lblUnknownActualRate;
        private System.Windows.Forms.Label m_lblFrequencyRange;
        private System.Windows.Forms.Label m_lblSPSRange;
        private System.Windows.Forms.GroupBox m_groupBoxTiming;
        private System.Windows.Forms.Label m_lblUnknownActualFrequency;
        private System.Windows.Forms.Label m_lblActualClockFrequency;
        private System.Windows.Forms.Label m_lblActualCFText;
        private System.Windows.Forms.GroupBox m_groupBoxLimits;
        private System.Windows.Forms.ComboBox m_cbCompareMode;
        private System.Windows.Forms.NumericUpDown m_numHighLimit;
        private System.Windows.Forms.NumericUpDown m_numLowLimit;
        private System.Windows.Forms.Label m_labelLowLimit;
        private System.Windows.Forms.Label m_labelHighLimit;
        private System.Windows.Forms.Label m_labelCompareMode;
        private System.Windows.Forms.ErrorProvider errorProviderNotCreator;

    }
}
