namespace LPComp_P4_v2_20
{
    partial class CyAdvancedTab
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
                if (m_symbol != null)
                {
                    m_symbol.Dispose();
                }
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
            this.chB_OutPosition = new System.Windows.Forms.CheckBox();
            this.pbSymbol = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).BeginInit();
            this.SuspendLayout();
            // 
            // chB_OutPosition
            // 
            this.chB_OutPosition.AutoSize = true;
            this.chB_OutPosition.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.chB_OutPosition.Location = new System.Drawing.Point(3, 3);
            this.chB_OutPosition.Name = "chB_OutPosition";
            this.chB_OutPosition.Size = new System.Drawing.Size(133, 17);
            this.chB_OutPosition.TabIndex = 0;
            this.chB_OutPosition.Text = "Legacy output position";
            this.chB_OutPosition.UseVisualStyleBackColor = true;
            // 
            // pbSymbol
            // 
            this.pbSymbol.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbSymbol.Location = new System.Drawing.Point(3, 26);
            this.pbSymbol.Name = "pbSymbol";
            this.pbSymbol.Size = new System.Drawing.Size(100, 100);
            this.pbSymbol.TabIndex = 5;
            this.pbSymbol.TabStop = false;
            // 
            // CyAdvancedTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pbSymbol);
            this.Controls.Add(this.chB_OutPosition);
            this.Name = "CyAdvancedTab";
            this.Size = new System.Drawing.Size(447, 457);
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox chB_OutPosition;
        private System.Windows.Forms.PictureBox pbSymbol;
    }
}
