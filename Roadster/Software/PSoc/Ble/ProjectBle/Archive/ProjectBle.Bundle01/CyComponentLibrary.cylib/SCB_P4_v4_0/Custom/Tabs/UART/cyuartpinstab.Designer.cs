namespace SCB_P4_v4_0
{
    partial class CyUARTPinsTab
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
            this.SuspendLayout();
            // 
            // m_chbShowTerminals
            // 
            this.m_chbShowTerminals.AutoSize = true;
            this.m_chbShowTerminals.Location = new System.Drawing.Point(7, 4);
            this.m_chbShowTerminals.Name = "m_chbShowTerminals";
            this.m_chbShowTerminals.Size = new System.Drawing.Size(130, 17);
            this.m_chbShowTerminals.TabIndex = 4;
            this.m_chbShowTerminals.Text = "Show UART terminals";
            this.m_chbShowTerminals.UseVisualStyleBackColor = true;
            this.m_chbShowTerminals.CheckedChanged += new System.EventHandler(this.m_chbShowTerminals_CheckedChanged);
            // 
            // CyUARTPinsTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_chbShowTerminals);
            this.Name = "CyUARTPinsTab";
            this.Size = new System.Drawing.Size(449, 319);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox m_chbShowTerminals;
    }
}
