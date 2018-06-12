namespace SCB_EZI2C_PDL_v2_0.Controls
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
            if (disposing)
            {
                m_params.DesignUpdated -= m_params_DesignUpdated;

                if (m_errorProvider != null)
                    m_errorProvider.Dispose();
                if (m_warningProvider != null)
                    m_warningProvider.Dispose();
                if (m_noteProvider != null)
                    m_noteProvider.Dispose();
            }

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
            this.m_lblActualDataRateText = new System.Windows.Forms.Label();
            this.m_lblActualDataRateValue = new System.Windows.Forms.Label();
            this.m_lblScbClockValue = new System.Windows.Forms.Label();
            this.m_lblScbClockText = new System.Windows.Forms.Label();
            this.m_lblApply = new System.Windows.Forms.Label();
            this.SuspendLayout();
            //
            // m_lblActualDataRateText
            //
            this.m_lblActualDataRateText.AutoSize = true;
            this.m_lblActualDataRateText.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualDataRateText.Location = new System.Drawing.Point(-2, 3);
            this.m_lblActualDataRateText.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblActualDataRateText.Name = "m_lblActualDataRateText";
            this.m_lblActualDataRateText.Size = new System.Drawing.Size(125, 13);
            this.m_lblActualDataRateText.TabIndex = 0;
            this.m_lblActualDataRateText.Text = "Actual data rate (kbps):";
            //
            // m_lblActualDataRateValue
            //
            this.m_lblActualDataRateValue.AutoSize = true;
            this.m_lblActualDataRateValue.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualDataRateValue.Location = new System.Drawing.Point(121, 3);
            this.m_lblActualDataRateValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblActualDataRateValue.Name = "m_lblActualDataRateValue";
            this.m_lblActualDataRateValue.Size = new System.Drawing.Size(37, 13);
            this.m_lblActualDataRateValue.TabIndex = 1;
            this.m_lblActualDataRateValue.Text = "UNKN";
            //
            // m_lblScbClockValue
            //
            this.m_lblScbClockValue.AutoSize = true;
            this.m_lblScbClockValue.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblScbClockValue.Location = new System.Drawing.Point(83, 22);
            this.m_lblScbClockValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblScbClockValue.Name = "m_lblScbClockValue";
            this.m_lblScbClockValue.Size = new System.Drawing.Size(37, 13);
            this.m_lblScbClockValue.TabIndex = 3;
            this.m_lblScbClockValue.Text = "UNKN";
            //
            // m_lblScbClockText
            //
            this.m_lblScbClockText.AutoSize = true;
            this.m_lblScbClockText.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblScbClockText.Location = new System.Drawing.Point(-2, 22);
            this.m_lblScbClockText.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblScbClockText.Name = "m_lblScbClockText";
            this.m_lblScbClockText.Size = new System.Drawing.Size(87, 13);
            this.m_lblScbClockText.TabIndex = 2;
            this.m_lblScbClockText.Text = "SCB clock (kHz):";
            //
            // m_lblApply
            //
            this.m_lblApply.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.m_lblApply.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.m_lblApply.ForeColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.m_lblApply.Location = new System.Drawing.Point(0, 168);
            this.m_lblApply.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblApply.Name = "m_lblApply";
            this.m_lblApply.Size = new System.Drawing.Size(225, 16);
            this.m_lblApply.TabIndex = 8;
            this.m_lblApply.Text = "Apply the configuration";
            this.m_lblApply.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            //
            // CyDynamicDataControl
            //
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.m_lblApply);
            this.Controls.Add(this.m_lblScbClockValue);
            this.Controls.Add(this.m_lblScbClockText);
            this.Controls.Add(this.m_lblActualDataRateValue);
            this.Controls.Add(this.m_lblActualDataRateText);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "CyDynamicDataControl";
            this.Size = new System.Drawing.Size(225, 184);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblActualDataRateText;
        private System.Windows.Forms.Label m_lblActualDataRateValue;
        private System.Windows.Forms.Label m_lblScbClockValue;
        private System.Windows.Forms.Label m_lblScbClockText;
        private System.Windows.Forms.Label m_lblApply;
    }
}
