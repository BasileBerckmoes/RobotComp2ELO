namespace I2S_v2_70
{
    partial class CyI2SBasicTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyI2SBasicTab));
            this.panelTop = new System.Windows.Forms.Panel();
            this.m_gbByteSwap = new System.Windows.Forms.GroupBox();
            this.m_chbRxByteSwap = new System.Windows.Forms.CheckBox();
            this.m_chbTxByteSwap = new System.Windows.Forms.CheckBox();
            this.m_gbAudioSampleConfig = new System.Windows.Forms.GroupBox();
            this.m_lblBitResolution = new System.Windows.Forms.Label();
            this.m_lblWordSelectPeriod = new System.Windows.Forms.Label();
            this.m_cbBitResolution = new System.Windows.Forms.ComboBox();
            this.m_cbWordSelectPeriod = new System.Windows.Forms.ComboBox();
            this.m_cbDataBits = new System.Windows.Forms.ComboBox();
            this.m_lblDataBits = new System.Windows.Forms.Label();
            this.m_gbDirection = new System.Windows.Forms.GroupBox();
            this.m_rbDirectionRx = new System.Windows.Forms.RadioButton();
            this.m_rbDirectionTx = new System.Windows.Forms.RadioButton();
            this.m_rbDirectionRxTx = new System.Windows.Forms.RadioButton();
            this.panelBottom = new System.Windows.Forms.Panel();
            this.m_pbGraph = new System.Windows.Forms.PictureBox();
            this.panelTop.SuspendLayout();
            this.m_gbByteSwap.SuspendLayout();
            this.m_gbAudioSampleConfig.SuspendLayout();
            this.m_gbDirection.SuspendLayout();
            this.panelBottom.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbGraph)).BeginInit();
            this.SuspendLayout();
            // 
            // panelTop
            // 
            this.panelTop.Controls.Add(this.m_gbByteSwap);
            this.panelTop.Controls.Add(this.m_gbAudioSampleConfig);
            this.panelTop.Controls.Add(this.m_gbDirection);
            resources.ApplyResources(this.panelTop, "panelTop");
            this.panelTop.Name = "panelTop";
            // 
            // m_gbByteSwap
            // 
            this.m_gbByteSwap.Controls.Add(this.m_chbRxByteSwap);
            this.m_gbByteSwap.Controls.Add(this.m_chbTxByteSwap);
            resources.ApplyResources(this.m_gbByteSwap, "m_gbByteSwap");
            this.m_gbByteSwap.Name = "m_gbByteSwap";
            this.m_gbByteSwap.TabStop = false;
            // 
            // m_chbRxByteSwap
            // 
            resources.ApplyResources(this.m_chbRxByteSwap, "m_chbRxByteSwap");
            this.m_chbRxByteSwap.Name = "m_chbRxByteSwap";
            this.m_chbRxByteSwap.UseVisualStyleBackColor = true;
            this.m_chbRxByteSwap.CheckedChanged += new System.EventHandler(this.m_chbByteSwap_CheckedChanged);
            // 
            // m_chbTxByteSwap
            // 
            resources.ApplyResources(this.m_chbTxByteSwap, "m_chbTxByteSwap");
            this.m_chbTxByteSwap.Name = "m_chbTxByteSwap";
            this.m_chbTxByteSwap.UseVisualStyleBackColor = true;
            this.m_chbTxByteSwap.CheckedChanged += new System.EventHandler(this.m_chbByteSwap_CheckedChanged);
            // 
            // m_gbAudioSampleConfig
            // 
            this.m_gbAudioSampleConfig.Controls.Add(this.m_lblBitResolution);
            this.m_gbAudioSampleConfig.Controls.Add(this.m_lblWordSelectPeriod);
            this.m_gbAudioSampleConfig.Controls.Add(this.m_cbBitResolution);
            this.m_gbAudioSampleConfig.Controls.Add(this.m_cbWordSelectPeriod);
            this.m_gbAudioSampleConfig.Controls.Add(this.m_cbDataBits);
            this.m_gbAudioSampleConfig.Controls.Add(this.m_lblDataBits);
            resources.ApplyResources(this.m_gbAudioSampleConfig, "m_gbAudioSampleConfig");
            this.m_gbAudioSampleConfig.Name = "m_gbAudioSampleConfig";
            this.m_gbAudioSampleConfig.TabStop = false;
            // 
            // m_lblBitResolution
            // 
            resources.ApplyResources(this.m_lblBitResolution, "m_lblBitResolution");
            this.m_lblBitResolution.Name = "m_lblBitResolution";
            // 
            // m_lblWordSelectPeriod
            // 
            resources.ApplyResources(this.m_lblWordSelectPeriod, "m_lblWordSelectPeriod");
            this.m_lblWordSelectPeriod.Name = "m_lblWordSelectPeriod";
            // 
            // m_cbBitResolution
            // 
            this.m_cbBitResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbBitResolution.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbBitResolution, "m_cbBitResolution");
            this.m_cbBitResolution.Name = "m_cbBitResolution";
            this.m_cbBitResolution.SelectedIndexChanged += new System.EventHandler(this.m_cbBitResolution_SelectedIndexChanged);
            // 
            // m_cbWordSelectPeriod
            // 
            this.m_cbWordSelectPeriod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbWordSelectPeriod.FormattingEnabled = true;
            this.m_cbWordSelectPeriod.Items.AddRange(new object[] {
            resources.GetString("m_cbWordSelectPeriod.Items"),
            resources.GetString("m_cbWordSelectPeriod.Items1"),
            resources.GetString("m_cbWordSelectPeriod.Items2"),
            resources.GetString("m_cbWordSelectPeriod.Items3")});
            resources.ApplyResources(this.m_cbWordSelectPeriod, "m_cbWordSelectPeriod");
            this.m_cbWordSelectPeriod.Name = "m_cbWordSelectPeriod";
            this.m_cbWordSelectPeriod.SelectedIndexChanged += new System.EventHandler(this.comboBoxWordSelectPeriod_SelectedIndexChanged);
            // 
            // m_cbDataBits
            // 
            this.m_cbDataBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbDataBits.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbDataBits, "m_cbDataBits");
            this.m_cbDataBits.Name = "m_cbDataBits";
            this.m_cbDataBits.SelectedIndexChanged += new System.EventHandler(this.comboBoxDataBits_SelectedIndexChanged);
            // 
            // m_lblDataBits
            // 
            resources.ApplyResources(this.m_lblDataBits, "m_lblDataBits");
            this.m_lblDataBits.Name = "m_lblDataBits";
            // 
            // m_gbDirection
            // 
            this.m_gbDirection.Controls.Add(this.m_rbDirectionRx);
            this.m_gbDirection.Controls.Add(this.m_rbDirectionTx);
            this.m_gbDirection.Controls.Add(this.m_rbDirectionRxTx);
            resources.ApplyResources(this.m_gbDirection, "m_gbDirection");
            this.m_gbDirection.Name = "m_gbDirection";
            this.m_gbDirection.TabStop = false;
            // 
            // m_rbDirectionRx
            // 
            resources.ApplyResources(this.m_rbDirectionRx, "m_rbDirectionRx");
            this.m_rbDirectionRx.Name = "m_rbDirectionRx";
            this.m_rbDirectionRx.TabStop = true;
            this.m_rbDirectionRx.UseVisualStyleBackColor = true;
            this.m_rbDirectionRx.CheckedChanged += new System.EventHandler(this.radioButtonDirection_CheckedChanged);
            // 
            // m_rbDirectionTx
            // 
            resources.ApplyResources(this.m_rbDirectionTx, "m_rbDirectionTx");
            this.m_rbDirectionTx.Name = "m_rbDirectionTx";
            this.m_rbDirectionTx.TabStop = true;
            this.m_rbDirectionTx.UseVisualStyleBackColor = true;
            this.m_rbDirectionTx.CheckedChanged += new System.EventHandler(this.radioButtonDirection_CheckedChanged);
            // 
            // m_rbDirectionRxTx
            // 
            resources.ApplyResources(this.m_rbDirectionRxTx, "m_rbDirectionRxTx");
            this.m_rbDirectionRxTx.Name = "m_rbDirectionRxTx";
            this.m_rbDirectionRxTx.TabStop = true;
            this.m_rbDirectionRxTx.UseVisualStyleBackColor = true;
            this.m_rbDirectionRxTx.CheckedChanged += new System.EventHandler(this.radioButtonDirection_CheckedChanged);
            // 
            // panelBottom
            // 
            this.panelBottom.Controls.Add(this.m_pbGraph);
            resources.ApplyResources(this.panelBottom, "panelBottom");
            this.panelBottom.Name = "panelBottom";
            // 
            // m_pbGraph
            // 
            this.m_pbGraph.BackColor = System.Drawing.SystemColors.Window;
            this.m_pbGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.m_pbGraph, "m_pbGraph");
            this.m_pbGraph.Name = "m_pbGraph";
            this.m_pbGraph.TabStop = false;
            this.m_pbGraph.SizeChanged += new System.EventHandler(this.m_pbGraph_SizeChanged);
            // 
            // CyI2SBasicTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panelBottom);
            this.Controls.Add(this.panelTop);
            this.Name = "CyI2SBasicTab";
            this.panelTop.ResumeLayout(false);
            this.m_gbByteSwap.ResumeLayout(false);
            this.m_gbByteSwap.PerformLayout();
            this.m_gbAudioSampleConfig.ResumeLayout(false);
            this.m_gbAudioSampleConfig.PerformLayout();
            this.m_gbDirection.ResumeLayout(false);
            this.m_gbDirection.PerformLayout();
            this.panelBottom.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_pbGraph)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelTop;
        public System.Windows.Forms.ComboBox m_cbWordSelectPeriod;
        private System.Windows.Forms.Label m_lblWordSelectPeriod;
        private System.Windows.Forms.Label m_lblDataBits;
        public System.Windows.Forms.RadioButton m_rbDirectionRxTx;
        public System.Windows.Forms.RadioButton m_rbDirectionTx;
        public System.Windows.Forms.RadioButton m_rbDirectionRx;
        private System.Windows.Forms.Panel panelBottom;
        private System.Windows.Forms.PictureBox m_pbGraph;
        private System.Windows.Forms.CheckBox m_chbTxByteSwap;
        private System.Windows.Forms.CheckBox m_chbRxByteSwap;
        private System.Windows.Forms.Label m_lblBitResolution;
        private System.Windows.Forms.ComboBox m_cbDataBits;
        private System.Windows.Forms.ComboBox m_cbBitResolution;
        private System.Windows.Forms.GroupBox m_gbByteSwap;
        private System.Windows.Forms.GroupBox m_gbAudioSampleConfig;
        private System.Windows.Forms.GroupBox m_gbDirection;

    }
}
