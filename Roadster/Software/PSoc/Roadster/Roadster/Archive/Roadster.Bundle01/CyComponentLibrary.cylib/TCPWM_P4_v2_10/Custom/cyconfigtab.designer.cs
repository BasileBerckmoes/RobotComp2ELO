namespace TCPWM_P4_v2_10
{
    partial class CyConfigTab
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
            this.rbUnconfigured = new System.Windows.Forms.RadioButton();
            this.rbTimerCounter = new System.Windows.Forms.RadioButton();
            this.rbPWM = new System.Windows.Forms.RadioButton();
            this.rbQuadDec = new System.Windows.Forms.RadioButton();
            this.SuspendLayout();
            // 
            // rbUnconfigured
            // 
            this.rbUnconfigured.AutoSize = true;
            this.rbUnconfigured.Checked = true;
            this.rbUnconfigured.Location = new System.Drawing.Point(3, 6);
            this.rbUnconfigured.Name = "rbUnconfigured";
            this.rbUnconfigured.Size = new System.Drawing.Size(133, 17);
            this.rbUnconfigured.TabIndex = 0;
            this.rbUnconfigured.TabStop = true;
            this.rbUnconfigured.Text = "Unconfigured TCPWM";
            this.rbUnconfigured.UseVisualStyleBackColor = true;
            this.rbUnconfigured.CheckedChanged += new System.EventHandler(this.rbconfig_CheckedChanged);
            // 
            // rbTimerCounter
            // 
            this.rbTimerCounter.AutoSize = true;
            this.rbTimerCounter.Location = new System.Drawing.Point(3, 29);
            this.rbTimerCounter.Name = "rbTimerCounter";
            this.rbTimerCounter.Size = new System.Drawing.Size(99, 17);
            this.rbTimerCounter.TabIndex = 1;
            this.rbTimerCounter.TabStop = true;
            this.rbTimerCounter.Text = "Timer / Counter";
            this.rbTimerCounter.UseVisualStyleBackColor = true;
            this.rbTimerCounter.CheckedChanged += new System.EventHandler(this.rbconfig_CheckedChanged);
            // 
            // rbPWM
            // 
            this.rbPWM.AutoSize = true;
            this.rbPWM.Location = new System.Drawing.Point(3, 52);
            this.rbPWM.Name = "rbPWM";
            this.rbPWM.Size = new System.Drawing.Size(52, 17);
            this.rbPWM.TabIndex = 2;
            this.rbPWM.TabStop = true;
            this.rbPWM.Text = "PWM";
            this.rbPWM.UseVisualStyleBackColor = true;
            this.rbPWM.CheckedChanged += new System.EventHandler(this.rbconfig_CheckedChanged);
            // 
            // rbQuadDec
            // 
            this.rbQuadDec.AutoSize = true;
            this.rbQuadDec.Location = new System.Drawing.Point(3, 75);
            this.rbQuadDec.Name = "rbQuadDec";
            this.rbQuadDec.Size = new System.Drawing.Size(122, 17);
            this.rbQuadDec.TabIndex = 3;
            this.rbQuadDec.TabStop = true;
            this.rbQuadDec.Text = "Quadrature Decoder";
            this.rbQuadDec.UseVisualStyleBackColor = true;
            this.rbQuadDec.CheckedChanged += new System.EventHandler(this.rbconfig_CheckedChanged);
            // 
            // CyConfigTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.rbQuadDec);
            this.Controls.Add(this.rbPWM);
            this.Controls.Add(this.rbTimerCounter);
            this.Controls.Add(this.rbUnconfigured);
            this.Name = "CyConfigTab";
            this.Size = new System.Drawing.Size(275, 245);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbUnconfigured;
        private System.Windows.Forms.RadioButton rbTimerCounter;
        private System.Windows.Forms.RadioButton rbPWM;
        private System.Windows.Forms.RadioButton rbQuadDec;
    }
}
