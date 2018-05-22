namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_10
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
            this.label1 = new System.Windows.Forms.Label();
            this.m_thresholdComboBox = new System.Windows.Forms.ComboBox();
            this.m_inputBufferEnabledCheckBox = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.m_interruptComboBox = new System.Windows.Forms.ComboBox();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_inputSyncComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.m_hysteresisCheckBox = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(76, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Threshold:";
            // 
            // m_thresholdComboBox
            // 
            this.m_thresholdComboBox.FormattingEnabled = true;
            this.m_thresholdComboBox.Location = new System.Drawing.Point(95, 2);
            this.m_thresholdComboBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_thresholdComboBox.Name = "m_thresholdComboBox";
            this.m_thresholdComboBox.Size = new System.Drawing.Size(141, 24);
            this.m_thresholdComboBox.TabIndex = 0;
            // 
            // m_inputBufferEnabledCheckBox
            // 
            this.m_inputBufferEnabledCheckBox.AutoSize = true;
            this.m_inputBufferEnabledCheckBox.Location = new System.Drawing.Point(95, 118);
            this.m_inputBufferEnabledCheckBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_inputBufferEnabledCheckBox.Name = "m_inputBufferEnabledCheckBox";
            this.m_inputBufferEnabledCheckBox.Size = new System.Drawing.Size(157, 21);
            this.m_inputBufferEnabledCheckBox.TabIndex = 4;
            this.m_inputBufferEnabledCheckBox.Text = "Input buffer enabled";
            this.m_inputBufferEnabledCheckBox.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "Interrupt:";
            // 
            // m_interruptComboBox
            // 
            this.m_interruptComboBox.FormattingEnabled = true;
            this.m_interruptComboBox.Location = new System.Drawing.Point(95, 58);
            this.m_interruptComboBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_interruptComboBox.Name = "m_interruptComboBox";
            this.m_interruptComboBox.Size = new System.Drawing.Size(141, 24);
            this.m_interruptComboBox.TabIndex = 2;
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // m_inputSyncComboBox
            // 
            this.m_inputSyncComboBox.FormattingEnabled = true;
            this.m_inputSyncComboBox.Location = new System.Drawing.Point(95, 88);
            this.m_inputSyncComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_inputSyncComboBox.Name = "m_inputSyncComboBox";
            this.m_inputSyncComboBox.Size = new System.Drawing.Size(141, 24);
            this.m_inputSyncComboBox.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 91);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 17);
            this.label3.TabIndex = 8;
            this.label3.Text = "Sync mode:";
            // 
            // m_hysteresisCheckBox
            // 
            this.m_hysteresisCheckBox.Location = new System.Drawing.Point(95, 30);
            this.m_hysteresisCheckBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_hysteresisCheckBox.Name = "m_hysteresisCheckBox";
            this.m_hysteresisCheckBox.Size = new System.Drawing.Size(141, 24);
            this.m_hysteresisCheckBox.TabIndex = 1;
            this.m_hysteresisCheckBox.Text = "Hysteresis";
            // 
            // CyInputControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.m_hysteresisCheckBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.m_inputSyncComboBox);
            this.Controls.Add(this.m_interruptComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.m_inputBufferEnabledCheckBox);
            this.Controls.Add(this.m_thresholdComboBox);
            this.Controls.Add(this.label1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "CyInputControl";
            this.Size = new System.Drawing.Size(417, 266);
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox m_thresholdComboBox;
        private System.Windows.Forms.CheckBox m_inputBufferEnabledCheckBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox m_interruptComboBox;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.ComboBox m_inputSyncComboBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox m_hysteresisCheckBox;
    }
}
