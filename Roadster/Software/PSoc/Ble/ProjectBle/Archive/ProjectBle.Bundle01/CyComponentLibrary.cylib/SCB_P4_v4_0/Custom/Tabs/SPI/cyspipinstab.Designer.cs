namespace SCB_P4_v4_0
{
    partial class CySPIPinsTab
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
            this.m_chbShowTerminals = new System.Windows.Forms.CheckBox();
            this.m_gbPinRemoveOptions = new System.Windows.Forms.GroupBox();
            this.m_chbRemoveMiso = new System.Windows.Forms.CheckBox();
            this.m_chbRemoveMosi = new System.Windows.Forms.CheckBox();
            this.m_chbRemoveSclk = new System.Windows.Forms.CheckBox();
            this.m_gbPinRemoveOptions.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_chbShowTerminals
            // 
            this.m_chbShowTerminals.AutoSize = true;
            this.m_chbShowTerminals.Location = new System.Drawing.Point(7, 4);
            this.m_chbShowTerminals.Name = "m_chbShowTerminals";
            this.m_chbShowTerminals.Size = new System.Drawing.Size(117, 17);
            this.m_chbShowTerminals.TabIndex = 4;
            this.m_chbShowTerminals.Text = "Show SPI terminals";
            this.m_chbShowTerminals.UseVisualStyleBackColor = true;
            // 
            // m_gbPinRemoveOptions
            // 
            this.m_gbPinRemoveOptions.Controls.Add(this.m_chbRemoveMiso);
            this.m_gbPinRemoveOptions.Controls.Add(this.m_chbRemoveMosi);
            this.m_gbPinRemoveOptions.Controls.Add(this.m_chbRemoveSclk);
            this.m_gbPinRemoveOptions.Location = new System.Drawing.Point(7, 32);
            this.m_gbPinRemoveOptions.Name = "m_gbPinRemoveOptions";
            this.m_gbPinRemoveOptions.Size = new System.Drawing.Size(116, 94);
            this.m_gbPinRemoveOptions.TabIndex = 15;
            this.m_gbPinRemoveOptions.TabStop = false;
            this.m_gbPinRemoveOptions.Text = "Pin remove options";
            // 
            // m_chbRemoveMiso
            // 
            this.m_chbRemoveMiso.AutoSize = true;
            this.m_chbRemoveMiso.Location = new System.Drawing.Point(7, 66);
            this.m_chbRemoveMiso.Name = "m_chbRemoveMiso";
            this.m_chbRemoveMiso.Size = new System.Drawing.Size(96, 17);
            this.m_chbRemoveMiso.TabIndex = 2;
            this.m_chbRemoveMiso.Text = "Remove MISO";
            this.m_chbRemoveMiso.UseVisualStyleBackColor = true;
            // 
            // m_chbRemoveMosi
            // 
            this.m_chbRemoveMosi.AutoSize = true;
            this.m_chbRemoveMosi.Location = new System.Drawing.Point(7, 43);
            this.m_chbRemoveMosi.Name = "m_chbRemoveMosi";
            this.m_chbRemoveMosi.Size = new System.Drawing.Size(96, 17);
            this.m_chbRemoveMosi.TabIndex = 1;
            this.m_chbRemoveMosi.Text = "Remove MOSI";
            this.m_chbRemoveMosi.UseVisualStyleBackColor = true;
            // 
            // m_chbRemoveSclk
            // 
            this.m_chbRemoveSclk.AutoSize = true;
            this.m_chbRemoveSclk.Location = new System.Drawing.Point(7, 20);
            this.m_chbRemoveSclk.Name = "m_chbRemoveSclk";
            this.m_chbRemoveSclk.Size = new System.Drawing.Size(96, 17);
            this.m_chbRemoveSclk.TabIndex = 0;
            this.m_chbRemoveSclk.Text = "Remove SCLK";
            this.m_chbRemoveSclk.UseVisualStyleBackColor = true;
            // 
            // CySPIPinsTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_gbPinRemoveOptions);
            this.Controls.Add(this.m_chbShowTerminals);
            this.Name = "CySPIPinsTab";
            this.Size = new System.Drawing.Size(449, 319);
            this.m_gbPinRemoveOptions.ResumeLayout(false);
            this.m_gbPinRemoveOptions.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox m_chbShowTerminals;
        private System.Windows.Forms.GroupBox m_gbPinRemoveOptions;
        private System.Windows.Forms.CheckBox m_chbRemoveMiso;
        private System.Windows.Forms.CheckBox m_chbRemoveMosi;
        private System.Windows.Forms.CheckBox m_chbRemoveSclk;
    }
}
