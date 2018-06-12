namespace DMA_PDL_v2_0.Tabs
{
    partial class CyBasicTab
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer m_components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (m_components != null))
            {
                m_components.Dispose();
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
            this.m_numberOfDescriptorsNumericUpDown = new CyDesigner.Toolkit.TableView_v1.CyNumericUpDown();
            this.m_preemptableComboBox = new System.Windows.Forms.ComboBox();
            this.m_channelPriorityComboBox = new System.Windows.Forms.ComboBox();
            this.m_triggerInputComboBox = new System.Windows.Forms.ComboBox();
            this.m_preemptableLabel = new System.Windows.Forms.Label();
            this.m_numberOfDescriptorsLabel = new System.Windows.Forms.Label();
            this.m_channelPriorityLabel = new System.Windows.Forms.Label();
            this.m_triggerInputLabel = new System.Windows.Forms.Label();
            this.m_triggerOutputComboBox = new System.Windows.Forms.ComboBox();
            this.m_triggerOutputLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_numberOfDescriptorsNumericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // m_numberOfDescriptorsNumericUpDown
            // 
            this.m_numberOfDescriptorsNumericUpDown.Location = new System.Drawing.Point(132, 89);
            this.m_numberOfDescriptorsNumericUpDown.Name = "m_numberOfDescriptorsNumericUpDown";
            this.m_numberOfDescriptorsNumericUpDown.Size = new System.Drawing.Size(120, 20);
            this.m_numberOfDescriptorsNumericUpDown.TabIndex = 2;
            this.m_numberOfDescriptorsNumericUpDown.ValueChanged += new System.EventHandler(this.m_numberOfDescriptorsNumericUpDown_ValueChanged);
            // 
            // m_preemptableComboBox
            // 
            this.m_preemptableComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_preemptableComboBox.FormattingEnabled = true;
            this.m_preemptableComboBox.Items.AddRange(new object[] {
            "Disable",
            "Enable"});
            this.m_preemptableComboBox.Location = new System.Drawing.Point(132, 115);
            this.m_preemptableComboBox.Name = "m_preemptableComboBox";
            this.m_preemptableComboBox.Size = new System.Drawing.Size(121, 21);
            this.m_preemptableComboBox.TabIndex = 3;
            this.m_preemptableComboBox.SelectedIndexChanged += new System.EventHandler(this.m_preemptableComboBox_SelectedIndexChanged);
            // 
            // m_channelPriorityComboBox
            // 
            this.m_channelPriorityComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_channelPriorityComboBox.FormattingEnabled = true;
            this.m_channelPriorityComboBox.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3"});
            this.m_channelPriorityComboBox.Location = new System.Drawing.Point(131, 62);
            this.m_channelPriorityComboBox.Name = "m_channelPriorityComboBox";
            this.m_channelPriorityComboBox.Size = new System.Drawing.Size(121, 21);
            this.m_channelPriorityComboBox.TabIndex = 1;
            this.m_channelPriorityComboBox.SelectedIndexChanged += new System.EventHandler(this.m_channelPriorityComboBox_SelectedIndexChanged);
            // 
            // m_triggerInputComboBox
            // 
            this.m_triggerInputComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_triggerInputComboBox.FormattingEnabled = true;
            this.m_triggerInputComboBox.Items.AddRange(new object[] {
            "Disable",
            "Enable"});
            this.m_triggerInputComboBox.Location = new System.Drawing.Point(131, 8);
            this.m_triggerInputComboBox.Name = "m_triggerInputComboBox";
            this.m_triggerInputComboBox.Size = new System.Drawing.Size(121, 21);
            this.m_triggerInputComboBox.TabIndex = 0;
            this.m_triggerInputComboBox.SelectedIndexChanged += new System.EventHandler(this.m_triggerInputComboBox_SelectedIndexChanged);
            // 
            // m_preemptableLabel
            // 
            this.m_preemptableLabel.AutoSize = true;
            this.m_preemptableLabel.Location = new System.Drawing.Point(13, 118);
            this.m_preemptableLabel.Name = "m_preemptableLabel";
            this.m_preemptableLabel.Size = new System.Drawing.Size(69, 13);
            this.m_preemptableLabel.TabIndex = 3;
            this.m_preemptableLabel.Text = "Preemptable:";
            // 
            // m_numberOfDescriptorsLabel
            // 
            this.m_numberOfDescriptorsLabel.AutoSize = true;
            this.m_numberOfDescriptorsLabel.Location = new System.Drawing.Point(13, 91);
            this.m_numberOfDescriptorsLabel.Name = "m_numberOfDescriptorsLabel";
            this.m_numberOfDescriptorsLabel.Size = new System.Drawing.Size(113, 13);
            this.m_numberOfDescriptorsLabel.TabIndex = 2;
            this.m_numberOfDescriptorsLabel.Text = "Number of descriptors:";
            // 
            // m_channelPriorityLabel
            // 
            this.m_channelPriorityLabel.AutoSize = true;
            this.m_channelPriorityLabel.Location = new System.Drawing.Point(13, 65);
            this.m_channelPriorityLabel.Name = "m_channelPriorityLabel";
            this.m_channelPriorityLabel.Size = new System.Drawing.Size(82, 13);
            this.m_channelPriorityLabel.TabIndex = 1;
            this.m_channelPriorityLabel.Text = "Channel priority:";
            // 
            // m_triggerInputLabel
            // 
            this.m_triggerInputLabel.AutoSize = true;
            this.m_triggerInputLabel.Location = new System.Drawing.Point(12, 11);
            this.m_triggerInputLabel.Name = "m_triggerInputLabel";
            this.m_triggerInputLabel.Size = new System.Drawing.Size(69, 13);
            this.m_triggerInputLabel.TabIndex = 0;
            this.m_triggerInputLabel.Text = "Trigger input:";
            // 
            // m_triggerOutputComboBox
            // 
            this.m_triggerOutputComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_triggerOutputComboBox.FormattingEnabled = true;
            this.m_triggerOutputComboBox.Items.AddRange(new object[] {
            "Disable",
            "Enable"});
            this.m_triggerOutputComboBox.Location = new System.Drawing.Point(131, 35);
            this.m_triggerOutputComboBox.Name = "m_triggerOutputComboBox";
            this.m_triggerOutputComboBox.Size = new System.Drawing.Size(121, 21);
            this.m_triggerOutputComboBox.TabIndex = 4;
            this.m_triggerOutputComboBox.SelectedIndexChanged += new System.EventHandler(this.m_triggerOutputComboBox_SelectedIndexChanged);
            // 
            // m_triggerOutputLabel
            // 
            this.m_triggerOutputLabel.AutoSize = true;
            this.m_triggerOutputLabel.Location = new System.Drawing.Point(12, 38);
            this.m_triggerOutputLabel.Name = "m_triggerOutputLabel";
            this.m_triggerOutputLabel.Size = new System.Drawing.Size(76, 13);
            this.m_triggerOutputLabel.TabIndex = 5;
            this.m_triggerOutputLabel.Text = "Trigger output:";
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_triggerOutputComboBox);
            this.Controls.Add(this.m_triggerOutputLabel);
            this.Controls.Add(this.m_numberOfDescriptorsNumericUpDown);
            this.Controls.Add(this.m_preemptableComboBox);
            this.Controls.Add(this.m_triggerInputComboBox);
            this.Controls.Add(this.m_channelPriorityComboBox);
            this.Controls.Add(this.m_triggerInputLabel);
            this.Controls.Add(this.m_channelPriorityLabel);
            this.Controls.Add(this.m_preemptableLabel);
            this.Controls.Add(this.m_numberOfDescriptorsLabel);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(573, 355);
            ((System.ComponentModel.ISupportInitialize)(this.m_numberOfDescriptorsNumericUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }



        #endregion

        private CyDesigner.Toolkit.TableView_v1.CyNumericUpDown m_numberOfDescriptorsNumericUpDown;
        private System.Windows.Forms.ComboBox m_preemptableComboBox;
        private System.Windows.Forms.ComboBox m_channelPriorityComboBox;
        private System.Windows.Forms.ComboBox m_triggerInputComboBox;
        private System.Windows.Forms.Label m_preemptableLabel;
        private System.Windows.Forms.Label m_numberOfDescriptorsLabel;
        private System.Windows.Forms.Label m_channelPriorityLabel;
        private System.Windows.Forms.Label m_triggerInputLabel;
        private System.Windows.Forms.ComboBox m_triggerOutputComboBox;
        private System.Windows.Forms.Label m_triggerOutputLabel;
    }
}
