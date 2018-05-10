namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    partial class CyInputControl
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
            this.m_labelInputThreshold = new System.Windows.Forms.Label();
            this.m_thresholdComboBox = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.m_interruptComboBox = new System.Windows.Forms.ComboBox();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_inputSyncComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.m_inputMultiplierComboBox = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // m_labelInputThreshold
            // 
            this.m_labelInputThreshold.AutoSize = true;
            this.m_labelInputThreshold.Location = new System.Drawing.Point(3, 6);
            this.m_labelInputThreshold.Name = "m_labelInputThreshold";
            this.m_labelInputThreshold.Size = new System.Drawing.Size(76, 17);
            this.m_labelInputThreshold.TabIndex = 0;
            this.m_labelInputThreshold.Text = "Threshold:";
            // 
            // m_thresholdComboBox
            // 
            this.m_thresholdComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_thresholdComboBox.FormattingEnabled = true;
            this.m_thresholdComboBox.Location = new System.Drawing.Point(95, 3);
            this.m_thresholdComboBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_thresholdComboBox.Name = "m_thresholdComboBox";
            this.m_thresholdComboBox.Size = new System.Drawing.Size(160, 24);
            this.m_thresholdComboBox.TabIndex = 0;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "Interrupt:";
            // 
            // m_interruptComboBox
            // 
            this.m_interruptComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_interruptComboBox.FormattingEnabled = true;
            this.m_interruptComboBox.Location = new System.Drawing.Point(95, 32);
            this.m_interruptComboBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_interruptComboBox.Name = "m_interruptComboBox";
            this.m_interruptComboBox.Size = new System.Drawing.Size(160, 24);
            this.m_interruptComboBox.TabIndex = 3;
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // m_inputSyncComboBox
            // 
            this.m_inputSyncComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_inputSyncComboBox.FormattingEnabled = true;
            this.m_inputSyncComboBox.Location = new System.Drawing.Point(95, 64);
            this.m_inputSyncComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_inputSyncComboBox.Name = "m_inputSyncComboBox";
            this.m_inputSyncComboBox.Size = new System.Drawing.Size(160, 24);
            this.m_inputSyncComboBox.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 66);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 17);
            this.label3.TabIndex = 8;
            this.label3.Text = "Sync mode:";
            // 
            // m_inputMultiplierComboBox
            // 
            this.m_inputMultiplierComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_inputMultiplierComboBox.FormattingEnabled = true;
            this.m_inputMultiplierComboBox.Location = new System.Drawing.Point(261, 2);
            this.m_inputMultiplierComboBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_inputMultiplierComboBox.Name = "m_inputMultiplierComboBox";
            this.m_inputMultiplierComboBox.Size = new System.Drawing.Size(96, 24);
            this.m_inputMultiplierComboBox.TabIndex = 1;
            // 
            // CyInputControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.m_inputMultiplierComboBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.m_inputSyncComboBox);
            this.Controls.Add(this.m_interruptComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.m_thresholdComboBox);
            this.Controls.Add(this.m_labelInputThreshold);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "CyInputControl";
            this.Size = new System.Drawing.Size(468, 266);
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_labelInputThreshold;
        private System.Windows.Forms.ComboBox m_thresholdComboBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox m_interruptComboBox;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.ComboBox m_inputSyncComboBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox m_inputMultiplierComboBox;
    }
}
