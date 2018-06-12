namespace FanController_v4_10
{
    partial class CyPidTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyPidTab));
            this.m_nudProportional = new System.Windows.Forms.NumericUpDown();
            this.m_nudIntegral = new System.Windows.Forms.NumericUpDown();
            this.m_nudDerivative = new System.Windows.Forms.NumericUpDown();
            this.m_nudUpperLimit = new System.Windows.Forms.NumericUpDown();
            this.m_nudLowerLimit = new System.Windows.Forms.NumericUpDown();
            this.m_cbOutputAttenuation = new System.Windows.Forms.ComboBox();
            this.m_lblProportional = new System.Windows.Forms.Label();
            this.m_lblIntegral = new System.Windows.Forms.Label();
            this.m_lblDerivative = new System.Windows.Forms.Label();
            this.m_lblUpperLimit = new System.Windows.Forms.Label();
            this.m_lblLowerLimit = new System.Windows.Forms.Label();
            this.m_lblAttenuation = new System.Windows.Forms.Label();
            this.m_gbOutputSaturation = new System.Windows.Forms.GroupBox();
            this.m_gbPidCoefficients = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudProportional)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudIntegral)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDerivative)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudUpperLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudLowerLimit)).BeginInit();
            this.m_gbOutputSaturation.SuspendLayout();
            this.m_gbPidCoefficients.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_nudProportional
            // 
            this.m_nudProportional.DecimalPlaces = 2;
            resources.ApplyResources(this.m_nudProportional, "m_nudProportional");
            this.m_nudProportional.Name = "m_nudProportional";
            // 
            // m_nudIntegral
            // 
            this.m_nudIntegral.DecimalPlaces = 2;
            resources.ApplyResources(this.m_nudIntegral, "m_nudIntegral");
            this.m_nudIntegral.Name = "m_nudIntegral";
            // 
            // m_nudDerivative
            // 
            this.m_nudDerivative.DecimalPlaces = 2;
            resources.ApplyResources(this.m_nudDerivative, "m_nudDerivative");
            this.m_nudDerivative.Name = "m_nudDerivative";
            // 
            // m_nudUpperLimit
            // 
            this.m_nudUpperLimit.DecimalPlaces = 2;
            resources.ApplyResources(this.m_nudUpperLimit, "m_nudUpperLimit");
            this.m_nudUpperLimit.Name = "m_nudUpperLimit";
            // 
            // m_nudLowerLimit
            // 
            this.m_nudLowerLimit.DecimalPlaces = 2;
            resources.ApplyResources(this.m_nudLowerLimit, "m_nudLowerLimit");
            this.m_nudLowerLimit.Name = "m_nudLowerLimit";
            // 
            // m_cbOutputAttenuation
            // 
            this.m_cbOutputAttenuation.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.m_cbOutputAttenuation.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbOutputAttenuation.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbOutputAttenuation, "m_cbOutputAttenuation");
            this.m_cbOutputAttenuation.Name = "m_cbOutputAttenuation";
            this.m_cbOutputAttenuation.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.cbOutputAttenuation_DrawItem);
            this.m_cbOutputAttenuation.SelectedIndexChanged += new System.EventHandler(this.cbOutputAttenuation_SelectedIndexChanged);
            // 
            // m_lblProportional
            // 
            resources.ApplyResources(this.m_lblProportional, "m_lblProportional");
            this.m_lblProportional.Name = "m_lblProportional";
            // 
            // m_lblIntegral
            // 
            resources.ApplyResources(this.m_lblIntegral, "m_lblIntegral");
            this.m_lblIntegral.Name = "m_lblIntegral";
            // 
            // m_lblDerivative
            // 
            resources.ApplyResources(this.m_lblDerivative, "m_lblDerivative");
            this.m_lblDerivative.Name = "m_lblDerivative";
            // 
            // m_lblUpperLimit
            // 
            resources.ApplyResources(this.m_lblUpperLimit, "m_lblUpperLimit");
            this.m_lblUpperLimit.Name = "m_lblUpperLimit";
            // 
            // m_lblLowerLimit
            // 
            resources.ApplyResources(this.m_lblLowerLimit, "m_lblLowerLimit");
            this.m_lblLowerLimit.Name = "m_lblLowerLimit";
            // 
            // m_lblAttenuation
            // 
            resources.ApplyResources(this.m_lblAttenuation, "m_lblAttenuation");
            this.m_lblAttenuation.Name = "m_lblAttenuation";
            // 
            // m_gbOutputSaturation
            // 
            this.m_gbOutputSaturation.Controls.Add(this.m_lblUpperLimit);
            this.m_gbOutputSaturation.Controls.Add(this.m_nudUpperLimit);
            this.m_gbOutputSaturation.Controls.Add(this.m_nudLowerLimit);
            this.m_gbOutputSaturation.Controls.Add(this.m_lblLowerLimit);
            resources.ApplyResources(this.m_gbOutputSaturation, "m_gbOutputSaturation");
            this.m_gbOutputSaturation.Name = "m_gbOutputSaturation";
            this.m_gbOutputSaturation.TabStop = false;
            // 
            // m_gbPidCoefficients
            // 
            this.m_gbPidCoefficients.Controls.Add(this.m_lblProportional);
            this.m_gbPidCoefficients.Controls.Add(this.m_nudProportional);
            this.m_gbPidCoefficients.Controls.Add(this.m_nudIntegral);
            this.m_gbPidCoefficients.Controls.Add(this.m_nudDerivative);
            this.m_gbPidCoefficients.Controls.Add(this.m_lblIntegral);
            this.m_gbPidCoefficients.Controls.Add(this.m_lblDerivative);
            resources.ApplyResources(this.m_gbPidCoefficients, "m_gbPidCoefficients");
            this.m_gbPidCoefficients.Name = "m_gbPidCoefficients";
            this.m_gbPidCoefficients.TabStop = false;
            // 
            // CyPidTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_gbPidCoefficients);
            this.Controls.Add(this.m_gbOutputSaturation);
            this.Controls.Add(this.m_lblAttenuation);
            this.Controls.Add(this.m_cbOutputAttenuation);
            this.Name = "CyPidTab";
            ((System.ComponentModel.ISupportInitialize)(this.m_nudProportional)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudIntegral)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDerivative)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudUpperLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudLowerLimit)).EndInit();
            this.m_gbOutputSaturation.ResumeLayout(false);
            this.m_gbOutputSaturation.PerformLayout();
            this.m_gbPidCoefficients.ResumeLayout(false);
            this.m_gbPidCoefficients.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown m_nudProportional;
        private System.Windows.Forms.ComboBox m_cbOutputAttenuation;
        private System.Windows.Forms.NumericUpDown m_nudLowerLimit;
        private System.Windows.Forms.NumericUpDown m_nudUpperLimit;
        private System.Windows.Forms.NumericUpDown m_nudDerivative;
        private System.Windows.Forms.NumericUpDown m_nudIntegral;
        private System.Windows.Forms.Label m_lblProportional;
        private System.Windows.Forms.Label m_lblAttenuation;
        private System.Windows.Forms.Label m_lblLowerLimit;
        private System.Windows.Forms.Label m_lblUpperLimit;
        private System.Windows.Forms.Label m_lblDerivative;
        private System.Windows.Forms.Label m_lblIntegral;
        private System.Windows.Forms.GroupBox m_gbOutputSaturation;
        private System.Windows.Forms.GroupBox m_gbPidCoefficients;
    }
}
