namespace SCB_P4_v3_20
{
    partial class CyEZI2CAdvancedTab
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
            this.m_numBusVoltage = new System.Windows.Forms.NumericUpDown();
            this.m_lblBusVoltage = new System.Windows.Forms.Label();
            this.m_panelSlewRate = new System.Windows.Forms.Panel();
            this.m_cbSlewRate = new System.Windows.Forms.ComboBox();
            this.m_lblSlewRate = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_numBusVoltage)).BeginInit();
            this.m_panelSlewRate.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_numBusVoltage
            // 
            this.m_numBusVoltage.Location = new System.Drawing.Point(153, 37);
            this.m_numBusVoltage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_numBusVoltage.Name = "m_numBusVoltage";
            this.m_numBusVoltage.Size = new System.Drawing.Size(156, 22);
            this.m_numBusVoltage.TabIndex = 1;
            // 
            // m_lblBusVoltage
            // 
            this.m_lblBusVoltage.AutoSize = true;
            this.m_lblBusVoltage.Location = new System.Drawing.Point(4, 39);
            this.m_lblBusVoltage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBusVoltage.Name = "m_lblBusVoltage";
            this.m_lblBusVoltage.Size = new System.Drawing.Size(132, 17);
            this.m_lblBusVoltage.TabIndex = 2;
            this.m_lblBusVoltage.Text = "I2C bus voltage (V):";
            // 
            // m_panelSlewRate
            // 
            this.m_panelSlewRate.Controls.Add(this.m_numBusVoltage);
            this.m_panelSlewRate.Controls.Add(this.m_cbSlewRate);
            this.m_panelSlewRate.Controls.Add(this.m_lblSlewRate);
            this.m_panelSlewRate.Controls.Add(this.m_lblBusVoltage);
            this.m_panelSlewRate.Location = new System.Drawing.Point(1, 4);
            this.m_panelSlewRate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_panelSlewRate.Name = "m_panelSlewRate";
            this.m_panelSlewRate.Size = new System.Drawing.Size(350, 74);
            this.m_panelSlewRate.TabIndex = 4;
            // 
            // m_cbSlewRate
            // 
            this.m_cbSlewRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSlewRate.FormattingEnabled = true;
            this.m_cbSlewRate.Location = new System.Drawing.Point(153, 4);
            this.m_cbSlewRate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_cbSlewRate.Name = "m_cbSlewRate";
            this.m_cbSlewRate.Size = new System.Drawing.Size(155, 24);
            this.m_cbSlewRate.TabIndex = 5;
            // 
            // m_lblSlewRate
            // 
            this.m_lblSlewRate.AutoSize = true;
            this.m_lblSlewRate.Location = new System.Drawing.Point(4, 7);
            this.m_lblSlewRate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSlewRate.Name = "m_lblSlewRate";
            this.m_lblSlewRate.Size = new System.Drawing.Size(70, 17);
            this.m_lblSlewRate.TabIndex = 6;
            this.m_lblSlewRate.Text = "Slew rate:";
            // 
            // CyEZI2CAdvancedTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_panelSlewRate);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "CyEZI2CAdvancedTab";
            this.Size = new System.Drawing.Size(592, 395);
            ((System.ComponentModel.ISupportInitialize)(this.m_numBusVoltage)).EndInit();
            this.m_panelSlewRate.ResumeLayout(false);
            this.m_panelSlewRate.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NumericUpDown m_numBusVoltage;
        private System.Windows.Forms.Label m_lblBusVoltage;
        private System.Windows.Forms.Panel m_panelSlewRate;
        private System.Windows.Forms.Label m_lblSlewRate;
        private System.Windows.Forms.ComboBox m_cbSlewRate;
    }
}
