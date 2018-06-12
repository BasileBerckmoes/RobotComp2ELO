namespace I2S_v2_70
{
    partial class CyI2SAdvancedTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyI2SAdvancedTab));
            this.m_chbTxInterruptFifo1 = new System.Windows.Forms.CheckBox();
            this.m_chbTxInterruptFifo0 = new System.Windows.Forms.CheckBox();
            this.m_chbTxInterruptUnderflow = new System.Windows.Forms.CheckBox();
            this.m_chbRxInterruptFifo1 = new System.Windows.Forms.CheckBox();
            this.m_chbRxInterruptFifo0 = new System.Windows.Forms.CheckBox();
            this.m_chbRxInterruptOverflow = new System.Windows.Forms.CheckBox();
            this.m_lblRxInterruptSource = new System.Windows.Forms.Label();
            this.m_chbRxDMA = new System.Windows.Forms.CheckBox();
            this.m_lblRxDataInterleaving = new System.Windows.Forms.Label();
            this.m_gbRx = new System.Windows.Forms.GroupBox();
            this.m_cbRxDataInterleaving = new System.Windows.Forms.ComboBox();
            this.m_lblRxDmaRequest = new System.Windows.Forms.Label();
            this.m_cbRxNumChannels = new System.Windows.Forms.ComboBox();
            this.m_lblRxNumChannels = new System.Windows.Forms.Label();
            this.m_gbTx = new System.Windows.Forms.GroupBox();
            this.m_cbTxDataInterleaving = new System.Windows.Forms.ComboBox();
            this.m_lblTxDmaRequest = new System.Windows.Forms.Label();
            this.m_chbTxDMA = new System.Windows.Forms.CheckBox();
            this.m_lblTxInterruptSource = new System.Windows.Forms.Label();
            this.m_cbTxNumChannels = new System.Windows.Forms.ComboBox();
            this.m_lblTxNumChannels = new System.Windows.Forms.Label();
            this.m_lblTxDataInterleaving = new System.Windows.Forms.Label();
            this.m_gbClipDetection = new System.Windows.Forms.GroupBox();
            this.m_lblStereo4 = new System.Windows.Forms.Label();
            this.m_lblStereo3 = new System.Windows.Forms.Label();
            this.m_lblStereo2 = new System.Windows.Forms.Label();
            this.m_lblStereo1 = new System.Windows.Forms.Label();
            this.m_lblStereo0 = new System.Windows.Forms.Label();
            this.m_numNeg4 = new System.Windows.Forms.NumericUpDown();
            this.m_numNeg3 = new System.Windows.Forms.NumericUpDown();
            this.m_numNeg2 = new System.Windows.Forms.NumericUpDown();
            this.m_numNeg1 = new System.Windows.Forms.NumericUpDown();
            this.m_numNeg0 = new System.Windows.Forms.NumericUpDown();
            this.m_numPos4 = new System.Windows.Forms.NumericUpDown();
            this.m_numPos3 = new System.Windows.Forms.NumericUpDown();
            this.m_numPos2 = new System.Windows.Forms.NumericUpDown();
            this.m_numPos1 = new System.Windows.Forms.NumericUpDown();
            this.m_numPos0 = new System.Windows.Forms.NumericUpDown();
            this.m_lblNegThreshold = new System.Windows.Forms.Label();
            this.m_lblPosThreshold = new System.Windows.Forms.Label();
            this.m_chbCommonThresholds = new System.Windows.Forms.CheckBox();
            this.m_chbRxClipDetection = new System.Windows.Forms.CheckBox();
            this.m_gbClockSynch = new System.Windows.Forms.GroupBox();
            this.m_rbAsynch = new System.Windows.Forms.RadioButton();
            this.m_rbSynch = new System.Windows.Forms.RadioButton();
            this.m_gbRx.SuspendLayout();
            this.m_gbTx.SuspendLayout();
            this.m_gbClipDetection.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg0)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos0)).BeginInit();
            this.m_gbClockSynch.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_chbTxInterruptFifo1
            // 
            resources.ApplyResources(this.m_chbTxInterruptFifo1, "m_chbTxInterruptFifo1");
            this.m_chbTxInterruptFifo1.Name = "m_chbTxInterruptFifo1";
            this.m_chbTxInterruptFifo1.UseVisualStyleBackColor = true;
            this.m_chbTxInterruptFifo1.CheckedChanged += new System.EventHandler(this.checkBoxInterruptSource_CheckedChanged);
            // 
            // m_chbTxInterruptFifo0
            // 
            resources.ApplyResources(this.m_chbTxInterruptFifo0, "m_chbTxInterruptFifo0");
            this.m_chbTxInterruptFifo0.Name = "m_chbTxInterruptFifo0";
            this.m_chbTxInterruptFifo0.UseVisualStyleBackColor = true;
            this.m_chbTxInterruptFifo0.CheckedChanged += new System.EventHandler(this.checkBoxInterruptSource_CheckedChanged);
            // 
            // m_chbTxInterruptUnderflow
            // 
            resources.ApplyResources(this.m_chbTxInterruptUnderflow, "m_chbTxInterruptUnderflow");
            this.m_chbTxInterruptUnderflow.Name = "m_chbTxInterruptUnderflow";
            this.m_chbTxInterruptUnderflow.UseVisualStyleBackColor = true;
            this.m_chbTxInterruptUnderflow.CheckedChanged += new System.EventHandler(this.checkBoxInterruptSource_CheckedChanged);
            // 
            // m_chbRxInterruptFifo1
            // 
            resources.ApplyResources(this.m_chbRxInterruptFifo1, "m_chbRxInterruptFifo1");
            this.m_chbRxInterruptFifo1.Name = "m_chbRxInterruptFifo1";
            this.m_chbRxInterruptFifo1.UseVisualStyleBackColor = true;
            this.m_chbRxInterruptFifo1.CheckedChanged += new System.EventHandler(this.checkBoxInterruptSource_CheckedChanged);
            // 
            // m_chbRxInterruptFifo0
            // 
            resources.ApplyResources(this.m_chbRxInterruptFifo0, "m_chbRxInterruptFifo0");
            this.m_chbRxInterruptFifo0.Name = "m_chbRxInterruptFifo0";
            this.m_chbRxInterruptFifo0.UseVisualStyleBackColor = true;
            this.m_chbRxInterruptFifo0.CheckedChanged += new System.EventHandler(this.checkBoxInterruptSource_CheckedChanged);
            // 
            // m_chbRxInterruptOverflow
            // 
            resources.ApplyResources(this.m_chbRxInterruptOverflow, "m_chbRxInterruptOverflow");
            this.m_chbRxInterruptOverflow.Name = "m_chbRxInterruptOverflow";
            this.m_chbRxInterruptOverflow.UseVisualStyleBackColor = true;
            this.m_chbRxInterruptOverflow.CheckedChanged += new System.EventHandler(this.checkBoxInterruptSource_CheckedChanged);
            // 
            // m_lblRxInterruptSource
            // 
            resources.ApplyResources(this.m_lblRxInterruptSource, "m_lblRxInterruptSource");
            this.m_lblRxInterruptSource.Name = "m_lblRxInterruptSource";
            // 
            // m_chbRxDMA
            // 
            resources.ApplyResources(this.m_chbRxDMA, "m_chbRxDMA");
            this.m_chbRxDMA.Name = "m_chbRxDMA";
            this.m_chbRxDMA.UseVisualStyleBackColor = true;
            this.m_chbRxDMA.CheckedChanged += new System.EventHandler(this.checkBoxRxDMA_CheckedChanged);
            // 
            // m_lblRxDataInterleaving
            // 
            resources.ApplyResources(this.m_lblRxDataInterleaving, "m_lblRxDataInterleaving");
            this.m_lblRxDataInterleaving.Name = "m_lblRxDataInterleaving";
            // 
            // m_gbRx
            // 
            this.m_gbRx.Controls.Add(this.m_cbRxDataInterleaving);
            this.m_gbRx.Controls.Add(this.m_chbRxInterruptFifo1);
            this.m_gbRx.Controls.Add(this.m_lblRxDmaRequest);
            this.m_gbRx.Controls.Add(this.m_chbRxInterruptFifo0);
            this.m_gbRx.Controls.Add(this.m_chbRxDMA);
            this.m_gbRx.Controls.Add(this.m_chbRxInterruptOverflow);
            this.m_gbRx.Controls.Add(this.m_lblRxInterruptSource);
            this.m_gbRx.Controls.Add(this.m_cbRxNumChannels);
            this.m_gbRx.Controls.Add(this.m_lblRxNumChannels);
            this.m_gbRx.Controls.Add(this.m_lblRxDataInterleaving);
            resources.ApplyResources(this.m_gbRx, "m_gbRx");
            this.m_gbRx.Name = "m_gbRx";
            this.m_gbRx.TabStop = false;
            // 
            // m_cbRxDataInterleaving
            // 
            this.m_cbRxDataInterleaving.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxDataInterleaving.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbRxDataInterleaving, "m_cbRxDataInterleaving");
            this.m_cbRxDataInterleaving.Name = "m_cbRxDataInterleaving";
            this.m_cbRxDataInterleaving.SelectedIndexChanged += new System.EventHandler(this.m_cbRxDataInterleaving_SelectedIndexChanged);
            // 
            // m_lblRxDmaRequest
            // 
            resources.ApplyResources(this.m_lblRxDmaRequest, "m_lblRxDmaRequest");
            this.m_lblRxDmaRequest.Name = "m_lblRxDmaRequest";
            // 
            // m_cbRxNumChannels
            // 
            this.m_cbRxNumChannels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbRxNumChannels.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbRxNumChannels, "m_cbRxNumChannels");
            this.m_cbRxNumChannels.Name = "m_cbRxNumChannels";
            this.m_cbRxNumChannels.SelectedIndexChanged += new System.EventHandler(this.m_cbRxNumChannels_SelectedIndexChanged);
            // 
            // m_lblRxNumChannels
            // 
            resources.ApplyResources(this.m_lblRxNumChannels, "m_lblRxNumChannels");
            this.m_lblRxNumChannels.Name = "m_lblRxNumChannels";
            // 
            // m_gbTx
            // 
            this.m_gbTx.Controls.Add(this.m_cbTxDataInterleaving);
            this.m_gbTx.Controls.Add(this.m_chbTxInterruptFifo1);
            this.m_gbTx.Controls.Add(this.m_lblTxDmaRequest);
            this.m_gbTx.Controls.Add(this.m_chbTxInterruptFifo0);
            this.m_gbTx.Controls.Add(this.m_chbTxDMA);
            this.m_gbTx.Controls.Add(this.m_chbTxInterruptUnderflow);
            this.m_gbTx.Controls.Add(this.m_lblTxInterruptSource);
            this.m_gbTx.Controls.Add(this.m_cbTxNumChannels);
            this.m_gbTx.Controls.Add(this.m_lblTxNumChannels);
            this.m_gbTx.Controls.Add(this.m_lblTxDataInterleaving);
            resources.ApplyResources(this.m_gbTx, "m_gbTx");
            this.m_gbTx.Name = "m_gbTx";
            this.m_gbTx.TabStop = false;
            // 
            // m_cbTxDataInterleaving
            // 
            this.m_cbTxDataInterleaving.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxDataInterleaving.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbTxDataInterleaving, "m_cbTxDataInterleaving");
            this.m_cbTxDataInterleaving.Name = "m_cbTxDataInterleaving";
            this.m_cbTxDataInterleaving.SelectedIndexChanged += new System.EventHandler(this.m_cbTxDataInterleaving_SelectedIndexChanged);
            // 
            // m_lblTxDmaRequest
            // 
            resources.ApplyResources(this.m_lblTxDmaRequest, "m_lblTxDmaRequest");
            this.m_lblTxDmaRequest.Name = "m_lblTxDmaRequest";
            // 
            // m_chbTxDMA
            // 
            resources.ApplyResources(this.m_chbTxDMA, "m_chbTxDMA");
            this.m_chbTxDMA.Name = "m_chbTxDMA";
            this.m_chbTxDMA.UseVisualStyleBackColor = true;
            this.m_chbTxDMA.CheckedChanged += new System.EventHandler(this.checkBoxTxDMA_CheckedChanged);
            // 
            // m_lblTxInterruptSource
            // 
            resources.ApplyResources(this.m_lblTxInterruptSource, "m_lblTxInterruptSource");
            this.m_lblTxInterruptSource.Name = "m_lblTxInterruptSource";
            // 
            // m_cbTxNumChannels
            // 
            this.m_cbTxNumChannels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbTxNumChannels.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbTxNumChannels, "m_cbTxNumChannels");
            this.m_cbTxNumChannels.Name = "m_cbTxNumChannels";
            this.m_cbTxNumChannels.SelectedIndexChanged += new System.EventHandler(this.m_cbTxNumChannels_SelectedIndexChanged);
            // 
            // m_lblTxNumChannels
            // 
            resources.ApplyResources(this.m_lblTxNumChannels, "m_lblTxNumChannels");
            this.m_lblTxNumChannels.Name = "m_lblTxNumChannels";
            // 
            // m_lblTxDataInterleaving
            // 
            resources.ApplyResources(this.m_lblTxDataInterleaving, "m_lblTxDataInterleaving");
            this.m_lblTxDataInterleaving.Name = "m_lblTxDataInterleaving";
            // 
            // m_gbClipDetection
            // 
            this.m_gbClipDetection.Controls.Add(this.m_lblStereo4);
            this.m_gbClipDetection.Controls.Add(this.m_lblStereo3);
            this.m_gbClipDetection.Controls.Add(this.m_lblStereo2);
            this.m_gbClipDetection.Controls.Add(this.m_lblStereo1);
            this.m_gbClipDetection.Controls.Add(this.m_lblStereo0);
            this.m_gbClipDetection.Controls.Add(this.m_numNeg4);
            this.m_gbClipDetection.Controls.Add(this.m_numNeg3);
            this.m_gbClipDetection.Controls.Add(this.m_numNeg2);
            this.m_gbClipDetection.Controls.Add(this.m_numNeg1);
            this.m_gbClipDetection.Controls.Add(this.m_numNeg0);
            this.m_gbClipDetection.Controls.Add(this.m_numPos4);
            this.m_gbClipDetection.Controls.Add(this.m_numPos3);
            this.m_gbClipDetection.Controls.Add(this.m_numPos2);
            this.m_gbClipDetection.Controls.Add(this.m_numPos1);
            this.m_gbClipDetection.Controls.Add(this.m_numPos0);
            this.m_gbClipDetection.Controls.Add(this.m_lblNegThreshold);
            this.m_gbClipDetection.Controls.Add(this.m_lblPosThreshold);
            this.m_gbClipDetection.Controls.Add(this.m_chbCommonThresholds);
            resources.ApplyResources(this.m_gbClipDetection, "m_gbClipDetection");
            this.m_gbClipDetection.Name = "m_gbClipDetection";
            this.m_gbClipDetection.TabStop = false;
            // 
            // m_lblStereo4
            // 
            resources.ApplyResources(this.m_lblStereo4, "m_lblStereo4");
            this.m_lblStereo4.Name = "m_lblStereo4";
            // 
            // m_lblStereo3
            // 
            resources.ApplyResources(this.m_lblStereo3, "m_lblStereo3");
            this.m_lblStereo3.Name = "m_lblStereo3";
            // 
            // m_lblStereo2
            // 
            resources.ApplyResources(this.m_lblStereo2, "m_lblStereo2");
            this.m_lblStereo2.Name = "m_lblStereo2";
            // 
            // m_lblStereo1
            // 
            resources.ApplyResources(this.m_lblStereo1, "m_lblStereo1");
            this.m_lblStereo1.Name = "m_lblStereo1";
            // 
            // m_lblStereo0
            // 
            resources.ApplyResources(this.m_lblStereo0, "m_lblStereo0");
            this.m_lblStereo0.Name = "m_lblStereo0";
            // 
            // m_numNeg4
            // 
            resources.ApplyResources(this.m_numNeg4, "m_numNeg4");
            this.m_numNeg4.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.m_numNeg4.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.m_numNeg4.Name = "m_numNeg4";
            this.m_numNeg4.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // m_numNeg3
            // 
            resources.ApplyResources(this.m_numNeg3, "m_numNeg3");
            this.m_numNeg3.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.m_numNeg3.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.m_numNeg3.Name = "m_numNeg3";
            this.m_numNeg3.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // m_numNeg2
            // 
            resources.ApplyResources(this.m_numNeg2, "m_numNeg2");
            this.m_numNeg2.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.m_numNeg2.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.m_numNeg2.Name = "m_numNeg2";
            this.m_numNeg2.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // m_numNeg1
            // 
            resources.ApplyResources(this.m_numNeg1, "m_numNeg1");
            this.m_numNeg1.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.m_numNeg1.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.m_numNeg1.Name = "m_numNeg1";
            this.m_numNeg1.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // m_numNeg0
            // 
            resources.ApplyResources(this.m_numNeg0, "m_numNeg0");
            this.m_numNeg0.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.m_numNeg0.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            -2147483648});
            this.m_numNeg0.Name = "m_numNeg0";
            this.m_numNeg0.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // m_numPos4
            // 
            resources.ApplyResources(this.m_numPos4, "m_numPos4");
            this.m_numPos4.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.m_numPos4.Name = "m_numPos4";
            // 
            // m_numPos3
            // 
            resources.ApplyResources(this.m_numPos3, "m_numPos3");
            this.m_numPos3.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.m_numPos3.Name = "m_numPos3";
            // 
            // m_numPos2
            // 
            resources.ApplyResources(this.m_numPos2, "m_numPos2");
            this.m_numPos2.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.m_numPos2.Name = "m_numPos2";
            // 
            // m_numPos1
            // 
            resources.ApplyResources(this.m_numPos1, "m_numPos1");
            this.m_numPos1.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.m_numPos1.Name = "m_numPos1";
            // 
            // m_numPos0
            // 
            resources.ApplyResources(this.m_numPos0, "m_numPos0");
            this.m_numPos0.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.m_numPos0.Name = "m_numPos0";
            // 
            // m_lblNegThreshold
            // 
            resources.ApplyResources(this.m_lblNegThreshold, "m_lblNegThreshold");
            this.m_lblNegThreshold.Name = "m_lblNegThreshold";
            // 
            // m_lblPosThreshold
            // 
            resources.ApplyResources(this.m_lblPosThreshold, "m_lblPosThreshold");
            this.m_lblPosThreshold.Name = "m_lblPosThreshold";
            // 
            // m_chbCommonThresholds
            // 
            resources.ApplyResources(this.m_chbCommonThresholds, "m_chbCommonThresholds");
            this.m_chbCommonThresholds.Name = "m_chbCommonThresholds";
            this.m_chbCommonThresholds.UseVisualStyleBackColor = true;
            this.m_chbCommonThresholds.CheckedChanged += new System.EventHandler(this.m_chbCommonThresholds_CheckedChanged);
            // 
            // m_chbRxClipDetection
            // 
            resources.ApplyResources(this.m_chbRxClipDetection, "m_chbRxClipDetection");
            this.m_chbRxClipDetection.Name = "m_chbRxClipDetection";
            this.m_chbRxClipDetection.UseVisualStyleBackColor = true;
            this.m_chbRxClipDetection.CheckedChanged += new System.EventHandler(this.m_chbRxClipDetection_CheckedChanged);
            // 
            // m_gbClockSynch
            // 
            this.m_gbClockSynch.Controls.Add(this.m_rbAsynch);
            this.m_gbClockSynch.Controls.Add(this.m_rbSynch);
            resources.ApplyResources(this.m_gbClockSynch, "m_gbClockSynch");
            this.m_gbClockSynch.Name = "m_gbClockSynch";
            this.m_gbClockSynch.TabStop = false;
            // 
            // m_rbAsynch
            // 
            resources.ApplyResources(this.m_rbAsynch, "m_rbAsynch");
            this.m_rbAsynch.Name = "m_rbAsynch";
            this.m_rbAsynch.TabStop = true;
            this.m_rbAsynch.UseVisualStyleBackColor = true;
            this.m_rbAsynch.CheckedChanged += new System.EventHandler(this.m_rbSynchCheckedChanged);
            // 
            // m_rbSynch
            // 
            resources.ApplyResources(this.m_rbSynch, "m_rbSynch");
            this.m_rbSynch.Name = "m_rbSynch";
            this.m_rbSynch.TabStop = true;
            this.m_rbSynch.UseVisualStyleBackColor = true;
            this.m_rbSynch.CheckedChanged += new System.EventHandler(this.m_rbSynchCheckedChanged);
            // 
            // CyI2SAdvancedTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_gbClockSynch);
            this.Controls.Add(this.m_chbRxClipDetection);
            this.Controls.Add(this.m_gbClipDetection);
            this.Controls.Add(this.m_gbTx);
            this.Controls.Add(this.m_gbRx);
            this.Name = "CyI2SAdvancedTab";
            this.m_gbRx.ResumeLayout(false);
            this.m_gbRx.PerformLayout();
            this.m_gbTx.ResumeLayout(false);
            this.m_gbTx.PerformLayout();
            this.m_gbClipDetection.ResumeLayout(false);
            this.m_gbClipDetection.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numNeg0)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numPos0)).EndInit();
            this.m_gbClockSynch.ResumeLayout(false);
            this.m_gbClockSynch.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.CheckBox m_chbTxInterruptFifo1;
        public System.Windows.Forms.CheckBox m_chbTxInterruptFifo0;
        public System.Windows.Forms.CheckBox m_chbTxInterruptUnderflow;
        public System.Windows.Forms.CheckBox m_chbRxInterruptFifo1;
        public System.Windows.Forms.CheckBox m_chbRxInterruptFifo0;
        public System.Windows.Forms.CheckBox m_chbRxInterruptOverflow;
        private System.Windows.Forms.Label m_lblRxInterruptSource;
        public System.Windows.Forms.CheckBox m_chbRxDMA;
        private System.Windows.Forms.Label m_lblRxDataInterleaving;
        private System.Windows.Forms.GroupBox m_gbRx;
        private System.Windows.Forms.Label m_lblRxDmaRequest;
        private System.Windows.Forms.ComboBox m_cbRxNumChannels;
        private System.Windows.Forms.Label m_lblRxNumChannels;
        private System.Windows.Forms.GroupBox m_gbTx;
        private System.Windows.Forms.Label m_lblTxDmaRequest;
        public System.Windows.Forms.CheckBox m_chbTxDMA;
        private System.Windows.Forms.Label m_lblTxInterruptSource;
        private System.Windows.Forms.ComboBox m_cbTxNumChannels;
        private System.Windows.Forms.Label m_lblTxNumChannels;
        private System.Windows.Forms.Label m_lblTxDataInterleaving;
        private System.Windows.Forms.GroupBox m_gbClipDetection;
        private System.Windows.Forms.Label m_lblNegThreshold;
        private System.Windows.Forms.Label m_lblPosThreshold;
        private System.Windows.Forms.CheckBox m_chbCommonThresholds;
        private System.Windows.Forms.NumericUpDown m_numNeg4;
        private System.Windows.Forms.NumericUpDown m_numNeg3;
        private System.Windows.Forms.NumericUpDown m_numNeg2;
        private System.Windows.Forms.NumericUpDown m_numNeg1;
        private System.Windows.Forms.NumericUpDown m_numNeg0;
        private System.Windows.Forms.NumericUpDown m_numPos4;
        private System.Windows.Forms.NumericUpDown m_numPos3;
        private System.Windows.Forms.NumericUpDown m_numPos2;
        private System.Windows.Forms.NumericUpDown m_numPos1;
        private System.Windows.Forms.NumericUpDown m_numPos0;
        private System.Windows.Forms.Label m_lblStereo4;
        private System.Windows.Forms.Label m_lblStereo3;
        private System.Windows.Forms.Label m_lblStereo2;
        private System.Windows.Forms.Label m_lblStereo1;
        private System.Windows.Forms.Label m_lblStereo0;
        private System.Windows.Forms.CheckBox m_chbRxClipDetection;
        private System.Windows.Forms.ComboBox m_cbRxDataInterleaving;
        private System.Windows.Forms.ComboBox m_cbTxDataInterleaving;
        private System.Windows.Forms.GroupBox m_gbClockSynch;
        private System.Windows.Forms.RadioButton m_rbAsynch;
        private System.Windows.Forms.RadioButton m_rbSynch;
    }
}
