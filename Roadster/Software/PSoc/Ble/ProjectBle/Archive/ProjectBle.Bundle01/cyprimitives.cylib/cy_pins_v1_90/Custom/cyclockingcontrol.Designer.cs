using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v1_90
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
            this.components = new Container();
            this.textBox1 = new TextBox();
            this.m_errorProvider = new ErrorProvider(this.components);
            this.m_inputclockingGroupBox = new GroupBox();
            this.label4 = new Label();
            this.m_inEnableModeComboBox = new ComboBox();
            this.m_inClockComboBox = new ComboBox();
            this.label6 = new Label();
            this.m_inClockEnComboBox = new ComboBox();
            this.m_inResetComboBox = new ComboBox();
            this.label5 = new Label();
            this.m_clockingGroupBox = new GroupBox();
            this.label1 = new Label();
            this.m_outEnableModeComboBox = new ComboBox();
            this.m_outClockComboBox = new ComboBox();
            this.m_oeResetCheckBox = new CheckBox();
            this.m_outClockEnComboBox = new ComboBox();
            this.m_outputResetCheckBox = new CheckBox();
            this.label2 = new Label();
            this.m_outResetComboBox = new ComboBox();
            this.label3 = new Label();
            ((ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.m_inputclockingGroupBox.SuspendLayout();
            this.m_clockingGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((AnchorStyles)((((AnchorStyles.Top | AnchorStyles.Bottom)
                        | AnchorStyles.Left)
                        | AnchorStyles.Right)));
            this.textBox1.BorderStyle = BorderStyle.None;
            this.textBox1.Location = new Point(4, 37);
            this.textBox1.Margin = new Padding(2);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new Size(372, 290);
            this.textBox1.TabIndex = 2;
            this.textBox1.TabStop = false;
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
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
            this.m_inputclockingGroupBox.Location = new Point(4, 3);
            this.m_inputclockingGroupBox.Name = "m_inputclockingGroupBox";
            this.m_inputclockingGroupBox.Size = new Size(331, 102);
            this.m_inputclockingGroupBox.TabIndex = 22;
            this.m_inputclockingGroupBox.TabStop = false;
            this.m_inputclockingGroupBox.Text = "Input Clocking";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new Point(5, 22);
            this.label4.Margin = new Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new Size(49, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "In Clock:";
            // 
            // m_inEnableModeComboBox
            // 
            this.m_inEnableModeComboBox.FormattingEnabled = true;
            this.m_inEnableModeComboBox.Location = new Point(224, 46);
            this.m_inEnableModeComboBox.Name = "m_inEnableModeComboBox";
            this.m_inEnableModeComboBox.Size = new Size(80, 21);
            this.m_inEnableModeComboBox.TabIndex = 20;
            // 
            // m_inClockComboBox
            // 
            this.m_inClockComboBox.FormattingEnabled = true;
            this.m_inClockComboBox.Location = new Point(80, 19);
            this.m_inClockComboBox.Name = "m_inClockComboBox";
            this.m_inClockComboBox.Size = new Size(138, 21);
            this.m_inClockComboBox.TabIndex = 9;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new Point(5, 76);
            this.label6.Margin = new Padding(2, 0, 2, 0);
            this.label6.Name = "label6";
            this.label6.Size = new Size(50, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "In Reset:";
            // 
            // m_inClockEnComboBox
            // 
            this.m_inClockEnComboBox.FormattingEnabled = true;
            this.m_inClockEnComboBox.Location = new Point(80, 46);
            this.m_inClockEnComboBox.Name = "m_inClockEnComboBox";
            this.m_inClockEnComboBox.Size = new Size(138, 21);
            this.m_inClockEnComboBox.TabIndex = 11;
            // 
            // m_inResetComboBox
            // 
            this.m_inResetComboBox.FormattingEnabled = true;
            this.m_inResetComboBox.Location = new Point(80, 73);
            this.m_inResetComboBox.Name = "m_inResetComboBox";
            this.m_inResetComboBox.Size = new Size(138, 21);
            this.m_inResetComboBox.TabIndex = 13;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new Point(5, 49);
            this.label5.Margin = new Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new Size(53, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "In Clk En:";
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
            this.m_clockingGroupBox.Location = new Point(4, 111);
            this.m_clockingGroupBox.Name = "m_clockingGroupBox";
            this.m_clockingGroupBox.Size = new Size(331, 125);
            this.m_clockingGroupBox.TabIndex = 21;
            this.m_clockingGroupBox.TabStop = false;
            this.m_clockingGroupBox.Text = "Output Clocking";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new Point(5, 22);
            this.label1.Margin = new Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new Size(57, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Out Clock:";
            // 
            // m_outEnableModeComboBox
            // 
            this.m_outEnableModeComboBox.FormattingEnabled = true;
            this.m_outEnableModeComboBox.Location = new Point(224, 46);
            this.m_outEnableModeComboBox.Name = "m_outEnableModeComboBox";
            this.m_outEnableModeComboBox.Size = new Size(80, 21);
            this.m_outEnableModeComboBox.TabIndex = 19;
            // 
            // m_outClockComboBox
            // 
            this.m_outClockComboBox.FormattingEnabled = true;
            this.m_outClockComboBox.Location = new Point(80, 19);
            this.m_outClockComboBox.Name = "m_outClockComboBox";
            this.m_outClockComboBox.Size = new Size(138, 21);
            this.m_outClockComboBox.TabIndex = 5;
            // 
            // m_oeResetCheckBox
            // 
            this.m_oeResetCheckBox.AutoSize = true;
            this.m_oeResetCheckBox.Location = new Point(101, 72);
            this.m_oeResetCheckBox.Margin = new Padding(2);
            this.m_oeResetCheckBox.Name = "m_oeResetCheckBox";
            this.m_oeResetCheckBox.Size = new Size(72, 17);
            this.m_oeResetCheckBox.TabIndex = 18;
            this.m_oeResetCheckBox.Text = "OE Reset";
            this.m_oeResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_outClockEnComboBox
            // 
            this.m_outClockEnComboBox.FormattingEnabled = true;
            this.m_outClockEnComboBox.Location = new Point(80, 46);
            this.m_outClockEnComboBox.Name = "m_outClockEnComboBox";
            this.m_outClockEnComboBox.Size = new Size(138, 21);
            this.m_outClockEnComboBox.TabIndex = 8;
            // 
            // m_outputResetCheckBox
            // 
            this.m_outputResetCheckBox.AutoSize = true;
            this.m_outputResetCheckBox.Location = new Point(8, 72);
            this.m_outputResetCheckBox.Margin = new Padding(2);
            this.m_outputResetCheckBox.Name = "m_outputResetCheckBox";
            this.m_outputResetCheckBox.Size = new Size(89, 17);
            this.m_outputResetCheckBox.TabIndex = 17;
            this.m_outputResetCheckBox.Text = "Output Reset";
            this.m_outputResetCheckBox.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new Point(5, 49);
            this.label2.Margin = new Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new Size(61, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Out Clk En:";
            // 
            // m_outResetComboBox
            // 
            this.m_outResetComboBox.FormattingEnabled = true;
            this.m_outResetComboBox.Location = new Point(80, 94);
            this.m_outResetComboBox.Name = "m_outResetComboBox";
            this.m_outResetComboBox.Size = new Size(138, 21);
            this.m_outResetComboBox.TabIndex = 10;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new Point(5, 97);
            this.label3.Margin = new Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new Size(70, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Reset Signal:";
            // 
            // CyClockingControl
            // 
            this.AutoScaleDimensions = new SizeF(6F, 13F);
            this.AutoScaleMode = AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.m_clockingGroupBox);
            this.Controls.Add(this.m_inputclockingGroupBox);
            this.Controls.Add(this.textBox1);
            this.Margin = new Padding(2);
            this.Name = "CyClockingControl";
            this.Size = new Size(379, 327);
            ((ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.m_inputclockingGroupBox.ResumeLayout(false);
            this.m_inputclockingGroupBox.PerformLayout();
            this.m_clockingGroupBox.ResumeLayout(false);
            this.m_clockingGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private TextBox textBox1;
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
