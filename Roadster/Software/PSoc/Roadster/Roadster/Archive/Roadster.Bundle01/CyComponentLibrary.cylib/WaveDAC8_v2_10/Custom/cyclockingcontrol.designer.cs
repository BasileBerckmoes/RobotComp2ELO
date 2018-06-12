namespace WaveDAC8_v2_10
{
    partial class CyClockingControl
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyClockingControl));
            this.m_gbWaveform = new System.Windows.Forms.GroupBox();
            this.m_lblActual = new System.Windows.Forms.Label();
            this.m_tbActualSampleRate = new System.Windows.Forms.Label();
            this.m_rbExternal = new System.Windows.Forms.RadioButton();
            this.m_rbInternal = new System.Windows.Forms.RadioButton();
            this.m_nudSampleRate = new System.Windows.Forms.NumericUpDown();
            this.m_lblSampleRate = new System.Windows.Forms.Label();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_gbWaveform.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSampleRate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // m_gbWaveform
            // 
            this.m_gbWaveform.Controls.Add(this.m_lblActual);
            this.m_gbWaveform.Controls.Add(this.m_tbActualSampleRate);
            this.m_gbWaveform.Controls.Add(this.m_rbExternal);
            this.m_gbWaveform.Controls.Add(this.m_rbInternal);
            this.m_gbWaveform.Controls.Add(this.m_nudSampleRate);
            this.m_gbWaveform.Controls.Add(this.m_lblSampleRate);
            resources.ApplyResources(this.m_gbWaveform, "m_gbWaveform");
            this.m_gbWaveform.Name = "m_gbWaveform";
            this.m_gbWaveform.TabStop = false;
            // 
            // m_lblActual
            // 
            resources.ApplyResources(this.m_lblActual, "m_lblActual");
            this.m_lblActual.Name = "m_lblActual";
            // 
            // m_tbActualSampleRate
            // 
            resources.ApplyResources(this.m_tbActualSampleRate, "m_tbActualSampleRate");
            this.m_tbActualSampleRate.Name = "m_tbActualSampleRate";
            // 
            // m_rbExternal
            // 
            resources.ApplyResources(this.m_rbExternal, "m_rbExternal");
            this.m_rbExternal.Name = "m_rbExternal";
            this.m_rbExternal.TabStop = true;
            this.m_rbExternal.UseVisualStyleBackColor = true;
            this.m_rbExternal.CheckedChanged += new System.EventHandler(this.rbClockSource_CheckedChanged);
            // 
            // m_rbInternal
            // 
            resources.ApplyResources(this.m_rbInternal, "m_rbInternal");
            this.m_rbInternal.Name = "m_rbInternal";
            this.m_rbInternal.TabStop = true;
            this.m_rbInternal.UseVisualStyleBackColor = true;
            this.m_rbInternal.CheckedChanged += new System.EventHandler(this.rbClockSource_CheckedChanged);
            // 
            // m_nudSampleRate
            // 
            resources.ApplyResources(this.m_nudSampleRate, "m_nudSampleRate");
            this.m_nudSampleRate.Maximum = new decimal(new int[] {
            10000000,
            0,
            0,
            0});
            this.m_nudSampleRate.Name = "m_nudSampleRate";
            this.m_nudSampleRate.ValueChanged += new System.EventHandler(this.nudSampleRate_ValueChanged);
            // 
            // m_lblSampleRate
            // 
            resources.ApplyResources(this.m_lblSampleRate, "m_lblSampleRate");
            this.m_lblSampleRate.Name = "m_lblSampleRate";
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // CyClockingControl
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_gbWaveform);
            this.Name = "CyClockingControl";
            this.m_gbWaveform.ResumeLayout(false);
            this.m_gbWaveform.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSampleRate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_gbWaveform;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Label m_tbActualSampleRate;
        private System.Windows.Forms.RadioButton m_rbExternal;
        private System.Windows.Forms.RadioButton m_rbInternal;
        private System.Windows.Forms.NumericUpDown m_nudSampleRate;
        private System.Windows.Forms.Label m_lblSampleRate;
        private System.Windows.Forms.Label m_lblActual;
    }
}
