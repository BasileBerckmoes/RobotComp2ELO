namespace SCB_SPI_PDL_v2_0.Controls
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
            this.m_lblActualDataRateValue = new System.Windows.Forms.Label();
            this.m_lblActualBitRateText = new System.Windows.Forms.Label();
            this.m_lblApply = new System.Windows.Forms.Label();
            this.SuspendLayout();
            //
            // m_lblActualDataRateValue
            //
            this.m_lblActualDataRateValue.AutoSize = true;
            this.m_lblActualDataRateValue.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualDataRateValue.Location = new System.Drawing.Point(121, 2);
            this.m_lblActualDataRateValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblActualDataRateValue.Name = "m_lblActualDataRateValue";
            this.m_lblActualDataRateValue.Size = new System.Drawing.Size(37, 13);
            this.m_lblActualDataRateValue.TabIndex = 9;
            this.m_lblActualDataRateValue.Text = "UNKN";
            //
            // m_lblActualBitRateText
            //
            this.m_lblActualBitRateText.AutoSize = true;
            this.m_lblActualBitRateText.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualBitRateText.Location = new System.Drawing.Point(-2, 2);
            this.m_lblActualBitRateText.Name = "m_lblActualBitRateText";
            this.m_lblActualBitRateText.Size = new System.Drawing.Size(125, 13);
            this.m_lblActualBitRateText.TabIndex = 26;
            this.m_lblActualBitRateText.Text = "Actual data rate (kbps):";
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
            this.Controls.Add(this.m_lblActualBitRateText);
            this.Controls.Add(this.m_lblActualDataRateValue);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "CyDynamicDataControl";
            this.Size = new System.Drawing.Size(203, 110);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblActualDataRateValue;
        private System.Windows.Forms.Label m_lblActualBitRateText;
        private System.Windows.Forms.Label m_lblApply;
    }
}
