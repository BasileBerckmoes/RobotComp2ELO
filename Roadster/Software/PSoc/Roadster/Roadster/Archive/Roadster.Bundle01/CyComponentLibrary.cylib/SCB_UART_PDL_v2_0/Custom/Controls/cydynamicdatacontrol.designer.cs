namespace SCB_UART_PDL_v2_0.Controls
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
            this.m_lblActualBaudRateValue = new System.Windows.Forms.Label();
            this.m_lblActualBaudRateText = new System.Windows.Forms.Label();
            this.m_lblApply = new System.Windows.Forms.Label();
            this.SuspendLayout();
            //
            // m_lblActualBaudRateValue
            //
            this.m_lblActualBaudRateValue.AutoSize = true;
            this.m_lblActualBaudRateValue.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualBaudRateValue.Location = new System.Drawing.Point(118, 2);
            this.m_lblActualBaudRateValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblActualBaudRateValue.Name = "m_lblActualBaudRateValue";
            this.m_lblActualBaudRateValue.Size = new System.Drawing.Size(37, 13);
            this.m_lblActualBaudRateValue.TabIndex = 9;
            this.m_lblActualBaudRateValue.Text = "UNKN";
            //
            // m_lblActualBaudRateText
            //
            this.m_lblActualBaudRateText.AutoSize = true;
            this.m_lblActualBaudRateText.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualBaudRateText.Location = new System.Drawing.Point(-2, 2);
            this.m_lblActualBaudRateText.Name = "m_lblActualBaudRateText";
            this.m_lblActualBaudRateText.Size = new System.Drawing.Size(123, 13);
            this.m_lblActualBaudRateText.TabIndex = 26;
            this.m_lblActualBaudRateText.Text = "Actual baud rate (bps):";
            //
            // m_lblApply
            //
            this.m_lblApply.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.m_lblApply.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.m_lblApply.ForeColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.m_lblApply.Location = new System.Drawing.Point(0, 94);
            this.m_lblApply.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblApply.Name = "m_lblApply";
            this.m_lblApply.Size = new System.Drawing.Size(203, 16);
            this.m_lblApply.TabIndex = 27;
            this.m_lblApply.Text = "Apply the configuration";
            this.m_lblApply.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            //
            // CyDynamicDataControl
            //
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.m_lblApply);
            this.Controls.Add(this.m_lblActualBaudRateText);
            this.Controls.Add(this.m_lblActualBaudRateValue);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "CyDynamicDataControl";
            this.Size = new System.Drawing.Size(203, 110);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblActualBaudRateValue;
        private System.Windows.Forms.Label m_lblActualBaudRateText;
        private System.Windows.Forms.Label m_lblApply;
    }
}
