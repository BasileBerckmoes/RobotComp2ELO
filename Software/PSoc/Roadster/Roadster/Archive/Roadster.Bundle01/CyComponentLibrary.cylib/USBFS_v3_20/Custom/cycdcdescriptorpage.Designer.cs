namespace USBFS_v3_20
{
    partial class CyCDCDescriptorPage
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
            this.checkBoxEnableCDCApi = new System.Windows.Forms.CheckBox();
            this.panelCb.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelCb
            // 
            this.panelCb.Controls.Add(this.checkBoxEnableCDCApi);
            this.panelCb.Location = new System.Drawing.Point(0, 320);
            this.panelCb.Size = new System.Drawing.Size(236, 39);
            // 
            // checkBoxEnableCDCApi
            // 
            this.checkBoxEnableCDCApi.AutoSize = true;
            this.checkBoxEnableCDCApi.Location = new System.Drawing.Point(16, 14);
            this.checkBoxEnableCDCApi.Name = "checkBoxEnableCDCApi";
            this.checkBoxEnableCDCApi.Size = new System.Drawing.Size(132, 17);
            this.checkBoxEnableCDCApi.TabIndex = 1;
            this.checkBoxEnableCDCApi.Text = "Enable CDC API";
            this.checkBoxEnableCDCApi.UseVisualStyleBackColor = true;
            this.checkBoxEnableCDCApi.CheckedChanged += new System.EventHandler(this.checkBoxEnableCDCApi_CheckedChanged);
            // 
            // CyCDCDescriptorPage2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Name = "CyCDCDescriptorPage2";
            this.panelCb.ResumeLayout(false);
            this.panelCb.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBoxEnableCDCApi;
    }
}
