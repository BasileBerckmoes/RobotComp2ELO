namespace USBFS_v3_10
{
    partial class CyMidiDescriptorPage
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
            this.checkBoxMode = new System.Windows.Forms.CheckBox();
            this.checkBoxEnableMIDIApi = new System.Windows.Forms.CheckBox();
            this.panelCb.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelCb
            // 
            this.panelCb.Controls.Add(this.checkBoxMode);
            this.panelCb.Controls.Add(this.checkBoxEnableMIDIApi);
            // 
            // checkBoxMode
            // 
            this.checkBoxMode.AutoSize = true;
            this.checkBoxMode.Location = new System.Drawing.Point(16, 29);
            this.checkBoxMode.Name = "checkBoxMode";
            this.checkBoxMode.Size = new System.Drawing.Size(94, 17);
            this.checkBoxMode.TabIndex = 3;
            this.checkBoxMode.Text = "External Mode";
            this.checkBoxMode.UseVisualStyleBackColor = true;
            this.checkBoxMode.CheckedChanged += new System.EventHandler(this.checkBoxMode_CheckedChanged);
            // 
            // checkBoxEnableMIDIApi
            // 
            this.checkBoxEnableMIDIApi.AutoSize = true;
            this.checkBoxEnableMIDIApi.Location = new System.Drawing.Point(16, 6);
            this.checkBoxEnableMIDIApi.Name = "checkBoxEnableMIDIApi";
            this.checkBoxEnableMIDIApi.Size = new System.Drawing.Size(133, 17);
            this.checkBoxEnableMIDIApi.TabIndex = 2;
            this.checkBoxEnableMIDIApi.Text = "Enable MIDI Class API";
            this.checkBoxEnableMIDIApi.UseVisualStyleBackColor = true;
            this.checkBoxEnableMIDIApi.CheckedChanged += new System.EventHandler(this.checkBoxEnableMIDIApi_CheckedChanged);
            // 
            // CyMidiDescriptorPage2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Name = "CyMidiDescriptorPage2";
            this.panelCb.ResumeLayout(false);
            this.panelCb.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBoxMode;
        private System.Windows.Forms.CheckBox checkBoxEnableMIDIApi;
    }
}
