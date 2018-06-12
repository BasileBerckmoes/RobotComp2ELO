namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
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
            this.m_hysteresisCheckBox = new System.Windows.Forms.CheckBox();
            this.m_hotSwapCheckBox = new System.Windows.Forms.CheckBox();
            this.m_inputBufferEnabledCheckBox = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.m_interruptComboBox = new System.Windows.Forms.ComboBox();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_inputSyncComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(2, 5);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Threshold:";
            // 
            // m_thresholdComboBox
            // 
            this.m_thresholdComboBox.FormattingEnabled = true;
            this.m_thresholdComboBox.Location = new System.Drawing.Point(71, 2);
            this.m_thresholdComboBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_thresholdComboBox.Name = "m_thresholdComboBox";
            this.m_thresholdComboBox.Size = new System.Drawing.Size(107, 21);
            this.m_thresholdComboBox.TabIndex = 0;
            // 
            // m_hysteresisCheckBox
            // 
            this.m_hysteresisCheckBox.AutoSize = true;
            this.m_hysteresisCheckBox.Location = new System.Drawing.Point(182, 5);
            this.m_hysteresisCheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_hysteresisCheckBox.Name = "m_hysteresisCheckBox";
            this.m_hysteresisCheckBox.Size = new System.Drawing.Size(74, 17);
            this.m_hysteresisCheckBox.TabIndex = 1;
            this.m_hysteresisCheckBox.Text = "Hysteresis";
            this.m_hysteresisCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_hotSwapCheckBox
            // 
            this.m_hotSwapCheckBox.AutoSize = true;
            this.m_hotSwapCheckBox.Location = new System.Drawing.Point(71, 52);
            this.m_hotSwapCheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_hotSwapCheckBox.Name = "m_hotSwapCheckBox";
            this.m_hotSwapCheckBox.Size = new System.Drawing.Size(73, 17);
            this.m_hotSwapCheckBox.TabIndex = 3;
            this.m_hotSwapCheckBox.Text = "Hot Swap";
            this.m_hotSwapCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_inputBufferEnabledCheckBox
            // 
            this.m_inputBufferEnabledCheckBox.AutoSize = true;
            this.m_inputBufferEnabledCheckBox.Location = new System.Drawing.Point(71, 73);
            this.m_inputBufferEnabledCheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_inputBufferEnabledCheckBox.Name = "m_inputBufferEnabledCheckBox";
            this.m_inputBufferEnabledCheckBox.Size = new System.Drawing.Size(123, 17);
            this.m_inputBufferEnabledCheckBox.TabIndex = 4;
            this.m_inputBufferEnabledCheckBox.Text = "Input Buffer Enabled";
            this.m_inputBufferEnabledCheckBox.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(2, 30);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Interrupt:";
            // 
            // m_interruptComboBox
            // 
            this.m_interruptComboBox.FormattingEnabled = true;
            this.m_interruptComboBox.Location = new System.Drawing.Point(71, 27);
            this.m_interruptComboBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_interruptComboBox.Name = "m_interruptComboBox";
            this.m_interruptComboBox.Size = new System.Drawing.Size(107, 21);
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
            this.m_inputSyncComboBox.Location = new System.Drawing.Point(71, 95);
            this.m_inputSyncComboBox.Name = "m_inputSyncComboBox";
            this.m_inputSyncComboBox.Size = new System.Drawing.Size(107, 21);
            this.m_inputSyncComboBox.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(2, 98);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Sync Mode:";
            // 
            // CyInputControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.Controls.Add(this.label3);
            this.Controls.Add(this.m_inputSyncComboBox);
            this.Controls.Add(this.m_interruptComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.m_inputBufferEnabledCheckBox);
            this.Controls.Add(this.m_hotSwapCheckBox);
            this.Controls.Add(this.m_hysteresisCheckBox);
            this.Controls.Add(this.m_thresholdComboBox);
            this.Controls.Add(this.label1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "CyInputControl";
            this.Size = new System.Drawing.Size(313, 216);
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox m_thresholdComboBox;
        private System.Windows.Forms.CheckBox m_hysteresisCheckBox;
        private System.Windows.Forms.CheckBox m_hotSwapCheckBox;
        private System.Windows.Forms.CheckBox m_inputBufferEnabledCheckBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox m_interruptComboBox;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.ComboBox m_inputSyncComboBox;
        private System.Windows.Forms.Label label3;
    }
}
