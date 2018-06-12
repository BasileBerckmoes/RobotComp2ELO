namespace TMP05Intf_v1_10
{
    partial class CyGeneralTab
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
            this.rbContinuousMode = new System.Windows.Forms.RadioButton();
            this.rbOneShotMode = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.cbNumSensors = new System.Windows.Forms.ComboBox();
            this.gbMode = new System.Windows.Forms.GroupBox();
            this.gbMode.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbContinuousMode
            // 
            this.rbContinuousMode.AutoSize = true;
            this.rbContinuousMode.Location = new System.Drawing.Point(6, 19);
            this.rbContinuousMode.Name = "rbContinuousMode";
            this.rbContinuousMode.Size = new System.Drawing.Size(78, 17);
            this.rbContinuousMode.TabIndex = 0;
            this.rbContinuousMode.TabStop = true;
            this.rbContinuousMode.Text = "Continuous";
            this.rbContinuousMode.UseVisualStyleBackColor = true;
            this.rbContinuousMode.Click += new System.EventHandler(this.rbMode_Click);
            // 
            // rbOneShotMode
            // 
            this.rbOneShotMode.AutoSize = true;
            this.rbOneShotMode.Location = new System.Drawing.Point(6, 42);
            this.rbOneShotMode.Name = "rbOneShotMode";
            this.rbOneShotMode.Size = new System.Drawing.Size(68, 17);
            this.rbOneShotMode.TabIndex = 1;
            this.rbOneShotMode.TabStop = true;
            this.rbOneShotMode.Text = "One-shot";
            this.rbOneShotMode.UseVisualStyleBackColor = true;
            this.rbOneShotMode.Click += new System.EventHandler(this.rbMode_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 90);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Number of sensors:";
            // 
            // cbNumSensors
            // 
            this.cbNumSensors.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbNumSensors.FormattingEnabled = true;
            this.cbNumSensors.Location = new System.Drawing.Point(110, 87);
            this.cbNumSensors.Name = "cbNumSensors";
            this.cbNumSensors.Size = new System.Drawing.Size(51, 21);
            this.cbNumSensors.TabIndex = 1;
            this.cbNumSensors.SelectedIndexChanged += new System.EventHandler(this.cbNumSensors_SelectedIndexChanged);
            // 
            // gbMode
            // 
            this.gbMode.Controls.Add(this.rbContinuousMode);
            this.gbMode.Controls.Add(this.rbOneShotMode);
            this.gbMode.Location = new System.Drawing.Point(3, 3);
            this.gbMode.Name = "gbMode";
            this.gbMode.Size = new System.Drawing.Size(158, 75);
            this.gbMode.TabIndex = 0;
            this.gbMode.TabStop = false;
            this.gbMode.Text = "Mode";
            // 
            // CyGeneralTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.gbMode);
            this.Controls.Add(this.cbNumSensors);
            this.Controls.Add(this.label1);
            this.Name = "CyGeneralTab";
            this.Size = new System.Drawing.Size(514, 233);
            this.gbMode.ResumeLayout(false);
            this.gbMode.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbContinuousMode;
        private System.Windows.Forms.RadioButton rbOneShotMode;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbNumSensors;
        private System.Windows.Forms.GroupBox gbMode;
    }
}
