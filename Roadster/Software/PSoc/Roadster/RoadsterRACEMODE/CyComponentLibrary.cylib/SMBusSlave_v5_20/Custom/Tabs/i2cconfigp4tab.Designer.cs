namespace SMBusSlave_v5_20
{
    partial class CyI2cConfigP4Tab
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
            this.chbClockFromTerminal = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // chbClockFromTerminal
            // 
            this.chbClockFromTerminal.AutoSize = true;
            this.chbClockFromTerminal.Location = new System.Drawing.Point(3, 14);
            this.chbClockFromTerminal.Name = "chbClockFromTerminal";
            this.chbClockFromTerminal.Size = new System.Drawing.Size(115, 17);
            this.chbClockFromTerminal.TabIndex = 1;
            this.chbClockFromTerminal.Text = "Clock from terminal";
            this.chbClockFromTerminal.UseVisualStyleBackColor = true;
            this.chbClockFromTerminal.CheckedChanged += new System.EventHandler(this.chbClockFromTerminal_CheckedChanged);
            // 
            // CyI2cConfigP4Tab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.chbClockFromTerminal);
            this.Name = "CyI2cConfigP4Tab";
            this.Size = new System.Drawing.Size(311, 286);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox chbClockFromTerminal;
    }
}
