namespace CSD_Comp_v1_0
{
    partial class CyConfigureTab
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
            this.m_gbSpeed = new System.Windows.Forms.GroupBox();
            this.m_rbFast = new System.Windows.Forms.RadioButton();
            this.m_rbSlow = new System.Windows.Forms.RadioButton();
            this.m_pbDiagram = new System.Windows.Forms.PictureBox();
            this.m_pbSymbol = new System.Windows.Forms.PictureBox();
            this.m_gbSpeed.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbDiagram)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbSymbol)).BeginInit();
            this.SuspendLayout();
            // 
            // m_gbSpeed
            // 
            this.m_gbSpeed.Controls.Add(this.m_rbFast);
            this.m_gbSpeed.Controls.Add(this.m_rbSlow);
            this.m_gbSpeed.Location = new System.Drawing.Point(3, 4);
            this.m_gbSpeed.Name = "m_gbSpeed";
            this.m_gbSpeed.Size = new System.Drawing.Size(112, 70);
            this.m_gbSpeed.TabIndex = 1;
            this.m_gbSpeed.TabStop = false;
            this.m_gbSpeed.Text = "Speed/Power";
            // 
            // m_rbFast
            // 
            this.m_rbFast.AutoSize = true;
            this.m_rbFast.Location = new System.Drawing.Point(6, 42);
            this.m_rbFast.Name = "m_rbFast";
            this.m_rbFast.Size = new System.Drawing.Size(72, 17);
            this.m_rbFast.TabIndex = 1;
            this.m_rbFast.TabStop = true;
            this.m_rbFast.Text = "Fast/High";
            this.m_rbFast.UseVisualStyleBackColor = true;
            // 
            // m_rbSlow
            // 
            this.m_rbSlow.AutoSize = true;
            this.m_rbSlow.Location = new System.Drawing.Point(6, 19);
            this.m_rbSlow.Name = "m_rbSlow";
            this.m_rbSlow.Size = new System.Drawing.Size(73, 17);
            this.m_rbSlow.TabIndex = 0;
            this.m_rbSlow.TabStop = true;
            this.m_rbSlow.Text = "Slow/Low";
            this.m_rbSlow.UseVisualStyleBackColor = true;
            // 
            // m_pbDiagram
            // 
            this.m_pbDiagram.BackColor = System.Drawing.Color.White;
            this.m_pbDiagram.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_pbDiagram.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.m_pbDiagram.Location = new System.Drawing.Point(3, 80);
            this.m_pbDiagram.Name = "m_pbDiagram";
            this.m_pbDiagram.Size = new System.Drawing.Size(444, 152);
            this.m_pbDiagram.TabIndex = 17;
            this.m_pbDiagram.TabStop = false;
            // 
            // m_pbSymbol
            // 
            this.m_pbSymbol.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_pbSymbol.Location = new System.Drawing.Point(379, 4);
            this.m_pbSymbol.Name = "m_pbSymbol";
            this.m_pbSymbol.Size = new System.Drawing.Size(68, 70);
            this.m_pbSymbol.TabIndex = 2;
            this.m_pbSymbol.TabStop = false;
            // 
            // CyConfigureTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_pbDiagram);
            this.Controls.Add(this.m_pbSymbol);
            this.Controls.Add(this.m_gbSpeed);
            this.Name = "CyConfigureTab";
            this.Size = new System.Drawing.Size(450, 236);
            this.m_gbSpeed.ResumeLayout(false);
            this.m_gbSpeed.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbDiagram)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbSymbol)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_gbSpeed;
        private System.Windows.Forms.RadioButton m_rbFast;
        private System.Windows.Forms.RadioButton m_rbSlow;
        private System.Windows.Forms.PictureBox m_pbDiagram;
        private System.Windows.Forms.PictureBox m_pbSymbol;
    }
}
