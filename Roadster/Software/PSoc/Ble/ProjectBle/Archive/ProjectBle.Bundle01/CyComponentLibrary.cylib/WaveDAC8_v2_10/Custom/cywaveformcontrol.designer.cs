namespace WaveDAC8_v2_10
{
    partial class CyWaveformControl
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyWaveformControl));
            this.m_gbWaveform = new System.Windows.Forms.GroupBox();
            this.m_btnBrowse = new System.Windows.Forms.Button();
            this.m_pnlGraph = new System.Windows.Forms.Panel();
            this.m_lblDegreeShift = new System.Windows.Forms.Label();
            this.m_nudDegreeShift = new System.Windows.Forms.NumericUpDown();
            this.m_lblWaveType = new System.Windows.Forms.Label();
            this.m_cbWaveType = new System.Windows.Forms.ComboBox();
            this.m_nudAmplitude = new System.Windows.Forms.NumericUpDown();
            this.m_nudDCOffset = new System.Windows.Forms.NumericUpDown();
            this.m_nudNumSamples = new System.Windows.Forms.NumericUpDown();
            this.m_lblAmp = new System.Windows.Forms.Label();
            this.m_lblNumSamp = new System.Windows.Forms.Label();
            this.m_lblDCOff = new System.Windows.Forms.Label();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_gbWaveform.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDegreeShift)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudAmplitude)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDCOffset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumSamples)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // m_gbWaveform
            // 
            this.m_gbWaveform.Controls.Add(this.m_btnBrowse);
            this.m_gbWaveform.Controls.Add(this.m_pnlGraph);
            this.m_gbWaveform.Controls.Add(this.m_lblDegreeShift);
            this.m_gbWaveform.Controls.Add(this.m_nudDegreeShift);
            this.m_gbWaveform.Controls.Add(this.m_lblWaveType);
            this.m_gbWaveform.Controls.Add(this.m_cbWaveType);
            this.m_gbWaveform.Controls.Add(this.m_nudAmplitude);
            this.m_gbWaveform.Controls.Add(this.m_nudDCOffset);
            this.m_gbWaveform.Controls.Add(this.m_nudNumSamples);
            this.m_gbWaveform.Controls.Add(this.m_lblAmp);
            this.m_gbWaveform.Controls.Add(this.m_lblNumSamp);
            this.m_gbWaveform.Controls.Add(this.m_lblDCOff);
            resources.ApplyResources(this.m_gbWaveform, "m_gbWaveform");
            this.m_gbWaveform.Name = "m_gbWaveform";
            this.m_gbWaveform.TabStop = false;
            // 
            // m_btnBrowse
            // 
            resources.ApplyResources(this.m_btnBrowse, "m_btnBrowse");
            this.m_btnBrowse.Name = "m_btnBrowse";
            this.m_btnBrowse.UseVisualStyleBackColor = true;
            this.m_btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // m_pnlGraph
            // 
            resources.ApplyResources(this.m_pnlGraph, "m_pnlGraph");
            this.m_pnlGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_pnlGraph.Name = "m_pnlGraph";
            // 
            // m_lblDegreeShift
            // 
            resources.ApplyResources(this.m_lblDegreeShift, "m_lblDegreeShift");
            this.m_lblDegreeShift.Name = "m_lblDegreeShift";
            // 
            // m_nudDegreeShift
            // 
            resources.ApplyResources(this.m_nudDegreeShift, "m_nudDegreeShift");
            this.m_nudDegreeShift.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
            this.m_nudDegreeShift.Name = "m_nudDegreeShift";
            // 
            // m_lblWaveType
            // 
            resources.ApplyResources(this.m_lblWaveType, "m_lblWaveType");
            this.m_lblWaveType.Name = "m_lblWaveType";
            // 
            // m_cbWaveType
            // 
            resources.ApplyResources(this.m_cbWaveType, "m_cbWaveType");
            this.m_cbWaveType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbWaveType.FormattingEnabled = true;
            this.m_cbWaveType.Name = "m_cbWaveType";
            this.m_cbWaveType.SelectedIndexChanged += new System.EventHandler(this.cbWaveType_SelectedIndexChanged);
            // 
            // m_nudAmplitude
            // 
            resources.ApplyResources(this.m_nudAmplitude, "m_nudAmplitude");
            this.m_nudAmplitude.DecimalPlaces = 3;
            this.m_nudAmplitude.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudAmplitude.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.m_nudAmplitude.Name = "m_nudAmplitude";
            this.m_nudAmplitude.Value = new decimal(new int[] {
            40,
            0,
            0,
            65536});
            // 
            // m_nudDCOffset
            // 
            resources.ApplyResources(this.m_nudDCOffset, "m_nudDCOffset");
            this.m_nudDCOffset.DecimalPlaces = 3;
            this.m_nudDCOffset.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudDCOffset.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nudDCOffset.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            -2147483648});
            this.m_nudDCOffset.Name = "m_nudDCOffset";
            this.m_nudDCOffset.ValueChanged += new System.EventHandler(this.nudDCOffset_ValueChanged);
            // 
            // m_nudNumSamples
            // 
            resources.ApplyResources(this.m_nudNumSamples, "m_nudNumSamples");
            this.m_nudNumSamples.Maximum = new decimal(new int[] {
            4000,
            0,
            0,
            0});
            this.m_nudNumSamples.Minimum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.m_nudNumSamples.Name = "m_nudNumSamples";
            this.m_nudNumSamples.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // m_lblAmp
            // 
            resources.ApplyResources(this.m_lblAmp, "m_lblAmp");
            this.m_lblAmp.Name = "m_lblAmp";
            // 
            // m_lblNumSamp
            // 
            resources.ApplyResources(this.m_lblNumSamp, "m_lblNumSamp");
            this.m_lblNumSamp.Name = "m_lblNumSamp";
            // 
            // m_lblDCOff
            // 
            resources.ApplyResources(this.m_lblDCOff, "m_lblDCOff");
            this.m_lblDCOff.Name = "m_lblDCOff";
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // CyWaveformControl
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_gbWaveform);
            this.Name = "CyWaveformControl";
            this.m_gbWaveform.ResumeLayout(false);
            this.m_gbWaveform.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDegreeShift)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudAmplitude)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDCOffset)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumSamples)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_gbWaveform;
        private System.Windows.Forms.Label m_lblWaveType;
        private System.Windows.Forms.ComboBox m_cbWaveType;
        private System.Windows.Forms.NumericUpDown m_nudAmplitude;
        private System.Windows.Forms.NumericUpDown m_nudDCOffset;
        private System.Windows.Forms.NumericUpDown m_nudNumSamples;
        private System.Windows.Forms.Label m_lblAmp;
        private System.Windows.Forms.Label m_lblNumSamp;
        private System.Windows.Forms.Label m_lblDCOff;
        private System.Windows.Forms.Label m_lblDegreeShift;
        private System.Windows.Forms.NumericUpDown m_nudDegreeShift;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Panel m_pnlGraph;
        private System.Windows.Forms.Button m_btnBrowse;
    }
}
