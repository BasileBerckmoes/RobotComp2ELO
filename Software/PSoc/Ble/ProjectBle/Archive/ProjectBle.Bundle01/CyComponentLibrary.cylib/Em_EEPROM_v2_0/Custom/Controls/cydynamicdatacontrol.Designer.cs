namespace Em_EEPROM_v2_0.Controls
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
            this.m_lblActualSizeValue = new System.Windows.Forms.Label();
            this.m_lblActualSizeTitle = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // m_lblActualSizeValue
            // 
            this.m_lblActualSizeValue.AutoSize = true;
            this.m_lblActualSizeValue.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualSizeValue.Location = new System.Drawing.Point(145, 2);
            this.m_lblActualSizeValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblActualSizeValue.Name = "m_lblActualSizeValue";
            this.m_lblActualSizeValue.Size = new System.Drawing.Size(37, 13);
            this.m_lblActualSizeValue.TabIndex = 9;
            this.m_lblActualSizeValue.Text = "UNKN";
            // 
            // m_lblActualSizeTitle
            // 
            this.m_lblActualSizeTitle.AutoSize = true;
            this.m_lblActualSizeTitle.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.m_lblActualSizeTitle.Location = new System.Drawing.Point(-2, 2);
            this.m_lblActualSizeTitle.Name = "m_lblActualSizeTitle";
            this.m_lblActualSizeTitle.Size = new System.Drawing.Size(147, 13);
            this.m_lblActualSizeTitle.TabIndex = 26;
            this.m_lblActualSizeTitle.Text = "Actual EEPROM size (bytes):";
            // 
            // CyDynamicDataControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.m_lblActualSizeTitle);
            this.Controls.Add(this.m_lblActualSizeValue);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "CyDynamicDataControl";
            this.Size = new System.Drawing.Size(203, 110);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblActualSizeValue;
        private System.Windows.Forms.Label m_lblActualSizeTitle;
    }
}
