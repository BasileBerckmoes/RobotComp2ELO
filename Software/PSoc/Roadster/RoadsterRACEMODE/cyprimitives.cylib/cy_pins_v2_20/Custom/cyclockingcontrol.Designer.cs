using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_20
{
    partial class CyClockingControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private IContainer components = null;

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
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_inputclockingGroupBox = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.m_inEnableModeComboBox = new System.Windows.Forms.ComboBox();
            this.m_inClockComboBox = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.m_inClockEnComboBox = new System.Windows.Forms.ComboBox();
            this.m_inResetComboBox = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.m_clockingGroupBox = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.m_outEnableModeComboBox = new System.Windows.Forms.ComboBox();
            this.m_outClockComboBox = new System.Windows.Forms.ComboBox();
            this.m_oeResetCheckBox = new System.Windows.Forms.CheckBox();
            this.m_outClockEnComboBox = new System.Windows.Forms.ComboBox();
            this.m_outputResetCheckBox = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.m_outResetComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.m_inputclockingGroupBox.SuspendLayout();
            this.m_clockingGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // m_inputclockingGroupBox
            // 
            this.m_inputclockingGroupBox.Controls.Add(this.label4);
            this.m_inputclockingGroupBox.Controls.Add(this.m_inEnableModeComboBox);
            this.m_inputclockingGroupBox.Controls.Add(this.m_inClockComboBox);
            this.m_inputclockingGroupBox.Controls.Add(this.label6);
            this.m_inputclockingGroupBox.Controls.Add(this.m_inClockEnComboBox);
            this.m_inputclockingGroupBox.Controls.Add(this.m_inResetComboBox);
            this.m_inputclockingGroupBox.Controls.Add(this.label5);
            this.m_inputclockingGroupBox.Location = new System.Drawing.Point(5, 4);
            this.m_inputclockingGroupBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_inputclockingGroupBox.Name = "m_inputclockingGroupBox";
            this.m_inputclockingGroupBox.Padding = new System.Windows.Forms.Padding(4);
            this.m_inputclockingGroupBox.Size = new System.Drawing.Size(441, 126);
            this.m_inputclockingGroupBox.TabIndex = 0;
            this.m_inputclockingGroupBox.TabStop = false;
            this.m_inputclockingGroupBox.Text = "Input clocking";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 27);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 17);
            this.label4.TabIndex = 10;
            this.label4.Text = "In clock:";
            // 
            // m_inEnableModeComboBox
            // 
            this.m_inEnableModeComboBox.FormattingEnabled = true;
            this.m_inEnableModeComboBox.Location = new System.Drawing.Point(299, 57);
            this.m_inEnableModeComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_inEnableModeComboBox.Name = "m_inEnableModeComboBox";
            this.m_inEnableModeComboBox.Size = new System.Drawing.Size(105, 24);
            this.m_inEnableModeComboBox.TabIndex = 2;
            // 
            // m_inClockComboBox
            // 
            this.m_inClockComboBox.FormattingEnabled = true;
            this.m_inClockComboBox.Location = new System.Drawing.Point(107, 23);
            this.m_inClockComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_inClockComboBox.Name = "m_inClockComboBox";
            this.m_inClockComboBox.Size = new System.Drawing.Size(183, 24);
            this.m_inClockComboBox.TabIndex = 0;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(7, 94);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 17);
            this.label6.TabIndex = 14;
            this.label6.Text = "In reset:";
            // 
            // m_inClockEnComboBox
            // 
            this.m_inClockEnComboBox.FormattingEnabled = true;
            this.m_inClockEnComboBox.Location = new System.Drawing.Point(107, 57);
            this.m_inClockEnComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_inClockEnComboBox.Name = "m_inClockEnComboBox";
            this.m_inClockEnComboBox.Size = new System.Drawing.Size(183, 24);
            this.m_inClockEnComboBox.TabIndex = 1;
            // 
            // m_inResetComboBox
            // 
            this.m_inResetComboBox.FormattingEnabled = true;
            this.m_inResetComboBox.Location = new System.Drawing.Point(107, 90);
            this.m_inResetComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_inResetComboBox.Name = "m_inResetComboBox";
            this.m_inResetComboBox.Size = new System.Drawing.Size(183, 24);
            this.m_inResetComboBox.TabIndex = 3;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(7, 60);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(64, 17);
            this.label5.TabIndex = 12;
            this.label5.Text = "In clk en:";
            // 
            // m_clockingGroupBox
            // 
            this.m_clockingGroupBox.Controls.Add(this.label1);
            this.m_clockingGroupBox.Controls.Add(this.m_outEnableModeComboBox);
            this.m_clockingGroupBox.Controls.Add(this.m_outClockComboBox);
            this.m_clockingGroupBox.Controls.Add(this.m_oeResetCheckBox);
            this.m_clockingGroupBox.Controls.Add(this.m_outClockEnComboBox);
            this.m_clockingGroupBox.Controls.Add(this.m_outputResetCheckBox);
            this.m_clockingGroupBox.Controls.Add(this.label2);
            this.m_clockingGroupBox.Controls.Add(this.m_outResetComboBox);
            this.m_clockingGroupBox.Controls.Add(this.label3);
            this.m_clockingGroupBox.Location = new System.Drawing.Point(5, 137);
            this.m_clockingGroupBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_clockingGroupBox.Name = "m_clockingGroupBox";
            this.m_clockingGroupBox.Padding = new System.Windows.Forms.Padding(4);
            this.m_clockingGroupBox.Size = new System.Drawing.Size(441, 154);
            this.m_clockingGroupBox.TabIndex = 1;
            this.m_clockingGroupBox.TabStop = false;
            this.m_clockingGroupBox.Text = "Output clocking";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 17);
            this.label1.TabIndex = 6;
            this.label1.Text = "Out clock:";
            // 
            // m_outEnableModeComboBox
            // 
            this.m_outEnableModeComboBox.FormattingEnabled = true;
            this.m_outEnableModeComboBox.Location = new System.Drawing.Point(299, 57);
            this.m_outEnableModeComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_outEnableModeComboBox.Name = "m_outEnableModeComboBox";
            this.m_outEnableModeComboBox.Size = new System.Drawing.Size(105, 24);
            this.m_outEnableModeComboBox.TabIndex = 2;
            // 
            // m_outClockComboBox
            // 
            this.m_outClockComboBox.FormattingEnabled = true;
            this.m_outClockComboBox.Location = new System.Drawing.Point(107, 23);
            this.m_outClockComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_outClockComboBox.Name = "m_outClockComboBox";
            this.m_outClockComboBox.Size = new System.Drawing.Size(183, 24);
            this.m_outClockComboBox.TabIndex = 0;
            // 
            // m_oeResetCheckBox
            // 
            this.m_oeResetCheckBox.AutoSize = true;
            this.m_oeResetCheckBox.Location = new System.Drawing.Point(135, 89);
            this.m_oeResetCheckBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_oeResetCheckBox.Name = "m_oeResetCheckBox";
            this.m_oeResetCheckBox.Size = new System.Drawing.Size(86, 21);
            this.m_oeResetCheckBox.TabIndex = 4;
            this.m_oeResetCheckBox.Text = "OE reset";
            this.m_oeResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_outClockEnComboBox
            // 
            this.m_outClockEnComboBox.FormattingEnabled = true;
            this.m_outClockEnComboBox.Location = new System.Drawing.Point(107, 57);
            this.m_outClockEnComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_outClockEnComboBox.Name = "m_outClockEnComboBox";
            this.m_outClockEnComboBox.Size = new System.Drawing.Size(183, 24);
            this.m_outClockEnComboBox.TabIndex = 1;
            // 
            // m_outputResetCheckBox
            // 
            this.m_outputResetCheckBox.AutoSize = true;
            this.m_outputResetCheckBox.Location = new System.Drawing.Point(11, 89);
            this.m_outputResetCheckBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_outputResetCheckBox.Name = "m_outputResetCheckBox";
            this.m_outputResetCheckBox.Size = new System.Drawing.Size(109, 21);
            this.m_outputResetCheckBox.TabIndex = 3;
            this.m_outputResetCheckBox.Text = "Output reset";
            this.m_outputResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 17);
            this.label2.TabIndex = 9;
            this.label2.Text = "Out clk en:";
            // 
            // m_outResetComboBox
            // 
            this.m_outResetComboBox.FormattingEnabled = true;
            this.m_outResetComboBox.Location = new System.Drawing.Point(107, 116);
            this.m_outResetComboBox.Margin = new System.Windows.Forms.Padding(4);
            this.m_outResetComboBox.Name = "m_outResetComboBox";
            this.m_outResetComboBox.Size = new System.Drawing.Size(183, 24);
            this.m_outResetComboBox.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 119);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 17);
            this.label3.TabIndex = 11;
            this.label3.Text = "Reset signal:";
            // 
            // CyClockingControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.m_clockingGroupBox);
            this.Controls.Add(this.m_inputclockingGroupBox);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "CyClockingControl";
            this.Size = new System.Drawing.Size(457, 299);
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.m_inputclockingGroupBox.ResumeLayout(false);
            this.m_inputclockingGroupBox.PerformLayout();
            this.m_clockingGroupBox.ResumeLayout(false);
            this.m_clockingGroupBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private ErrorProvider m_errorProvider;
        private GroupBox m_inputclockingGroupBox;
        private Label label4;
        private ComboBox m_inEnableModeComboBox;
        private ComboBox m_inClockComboBox;
        private Label label6;
        private ComboBox m_inClockEnComboBox;
        private ComboBox m_inResetComboBox;
        private Label label5;
        private GroupBox m_clockingGroupBox;
        private Label label1;
        private ComboBox m_outEnableModeComboBox;
        private ComboBox m_outClockComboBox;
        private CheckBox m_oeResetCheckBox;
        private ComboBox m_outClockEnComboBox;
        private CheckBox m_outputResetCheckBox;
        private Label label2;
        private ComboBox m_outResetComboBox;
        private Label label3;
    }
}
