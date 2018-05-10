namespace TCPWM_Counter_PDL_v1_0.Controls
{
    partial class CyDynamicDataControl
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
            this.m_lblCountingClockValue = new System.Windows.Forms.Label();
            this.m_lblCountingClock = new System.Windows.Forms.Label();
            this.m_lblPeriodClockValue = new System.Windows.Forms.Label();
            this.m_lblPeriod = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // m_lblCountingClockValue
            // 
            this.m_lblCountingClockValue.AutoSize = true;
            this.m_lblCountingClockValue.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lblCountingClockValue.Location = new System.Drawing.Point(117, 2);
            this.m_lblCountingClockValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblCountingClockValue.Name = "m_lblCountingClockValue";
            this.m_lblCountingClockValue.Size = new System.Drawing.Size(40, 15);
            this.m_lblCountingClockValue.TabIndex = 9;
            this.m_lblCountingClockValue.Text = "UNKN";
            // 
            // m_lblCountingClock
            // 
            this.m_lblCountingClock.AutoSize = true;
            this.m_lblCountingClock.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lblCountingClock.Location = new System.Drawing.Point(-2, 2);
            this.m_lblCountingClock.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblCountingClock.Name = "m_lblCountingClock";
            this.m_lblCountingClock.Size = new System.Drawing.Size(122, 15);
            this.m_lblCountingClock.TabIndex = 8;
            this.m_lblCountingClock.Text = "Counting clock (kHz):";
            // 
            // m_lblPeriodClockValue
            // 
            this.m_lblPeriodClockValue.AutoSize = true;
            this.m_lblPeriodClockValue.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lblPeriodClockValue.Location = new System.Drawing.Point(117, 22);
            this.m_lblPeriodClockValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblPeriodClockValue.Name = "m_lblPeriodClockValue";
            this.m_lblPeriodClockValue.Size = new System.Drawing.Size(40, 15);
            this.m_lblPeriodClockValue.TabIndex = 25;
            this.m_lblPeriodClockValue.Text = "UNKN";
            // 
            // m_lblPeriod
            // 
            this.m_lblPeriod.AutoSize = true;
            this.m_lblPeriod.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lblPeriod.Location = new System.Drawing.Point(-2, 22);
            this.m_lblPeriod.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblPeriod.Name = "m_lblPeriod";
            this.m_lblPeriod.Size = new System.Drawing.Size(75, 15);
            this.m_lblPeriod.TabIndex = 23;
            this.m_lblPeriod.Text = "Period (kHz):";
            // 
            // CyDynamicDataControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.m_lblPeriodClockValue);
            this.Controls.Add(this.m_lblPeriod);
            this.Controls.Add(this.m_lblCountingClockValue);
            this.Controls.Add(this.m_lblCountingClock);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "CyDynamicDataControl";
            this.Size = new System.Drawing.Size(316, 203);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblCountingClockValue;
        private System.Windows.Forms.Label m_lblCountingClock;
        private System.Windows.Forms.Label m_lblPeriodClockValue;
        private System.Windows.Forms.Label m_lblPeriod;
    }
}
