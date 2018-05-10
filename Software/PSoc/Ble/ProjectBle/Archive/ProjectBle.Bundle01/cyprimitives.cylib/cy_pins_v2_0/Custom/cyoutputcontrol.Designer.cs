namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    partial class CyOutputControl
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.m_slewRateComboBox = new System.Windows.Forms.ComboBox();
            this.m_driveLevelComboBox = new System.Windows.Forms.ComboBox();
            this.m_currentComboBox = new System.Windows.Forms.ComboBox();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_oeSyncCheckBox = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.m_outputModeComboBox = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(2, 5);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Slew Rate:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(2, 30);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Drive Level:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(2, 55);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Current:";
            // 
            // m_slewRateComboBox
            // 
            this.m_slewRateComboBox.FormattingEnabled = true;
            this.m_slewRateComboBox.Location = new System.Drawing.Point(79, 2);
            this.m_slewRateComboBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_slewRateComboBox.Name = "m_slewRateComboBox";
            this.m_slewRateComboBox.Size = new System.Drawing.Size(92, 21);
            this.m_slewRateComboBox.TabIndex = 1;
            // 
            // m_driveLevelComboBox
            // 
            this.m_driveLevelComboBox.FormattingEnabled = true;
            this.m_driveLevelComboBox.Location = new System.Drawing.Point(79, 27);
            this.m_driveLevelComboBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_driveLevelComboBox.Name = "m_driveLevelComboBox";
            this.m_driveLevelComboBox.Size = new System.Drawing.Size(92, 21);
            this.m_driveLevelComboBox.TabIndex = 2;
            // 
            // m_currentComboBox
            // 
            this.m_currentComboBox.FormattingEnabled = true;
            this.m_currentComboBox.Location = new System.Drawing.Point(79, 52);
            this.m_currentComboBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_currentComboBox.Name = "m_currentComboBox";
            this.m_currentComboBox.Size = new System.Drawing.Size(167, 21);
            this.m_currentComboBox.TabIndex = 3;
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // m_oeSyncCheckBox
            // 
            this.m_oeSyncCheckBox.AutoSize = true;
            this.m_oeSyncCheckBox.Location = new System.Drawing.Point(176, 82);
            this.m_oeSyncCheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_oeSyncCheckBox.Name = "m_oeSyncCheckBox";
            this.m_oeSyncCheckBox.Size = new System.Drawing.Size(108, 17);
            this.m_oeSyncCheckBox.TabIndex = 7;
            this.m_oeSyncCheckBox.Text = "OE Synchronized";
            this.m_oeSyncCheckBox.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(2, 81);
            this.label7.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(72, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Output Mode:";
            // 
            // m_outputModeComboBox
            // 
            this.m_outputModeComboBox.FormattingEnabled = true;
            this.m_outputModeComboBox.Location = new System.Drawing.Point(79, 78);
            this.m_outputModeComboBox.Name = "m_outputModeComboBox";
            this.m_outputModeComboBox.Size = new System.Drawing.Size(92, 21);
            this.m_outputModeComboBox.TabIndex = 12;
            // 
            // CyOutputControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.label7);
            this.Controls.Add(this.m_outputModeComboBox);
            this.Controls.Add(this.m_oeSyncCheckBox);
            this.Controls.Add(this.m_currentComboBox);
            this.Controls.Add(this.m_driveLevelComboBox);
            this.Controls.Add(this.m_slewRateComboBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "CyOutputControl";
            this.Size = new System.Drawing.Size(309, 224);
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox m_slewRateComboBox;
        private System.Windows.Forms.ComboBox m_driveLevelComboBox;
        private System.Windows.Forms.ComboBox m_currentComboBox;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.CheckBox m_oeSyncCheckBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox m_outputModeComboBox;
    }
}
