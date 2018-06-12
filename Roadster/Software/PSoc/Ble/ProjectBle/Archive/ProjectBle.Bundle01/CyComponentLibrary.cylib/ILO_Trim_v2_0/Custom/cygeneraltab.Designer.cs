namespace ILO_Trim_v2_0
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
            this.components = new System.ComponentModel.Container();
            this.m_grpImplementation = new System.Windows.Forms.GroupBox();
            this.m_rbUDB = new System.Windows.Forms.RadioButton();
            this.m_rbFixedFunction = new System.Windows.Forms.RadioButton();
            this.m_grpClkInfo = new System.Windows.Forms.GroupBox();
            this.m_lblWarningMsg = new System.Windows.Forms.Label();
            this.m_lblRatio = new System.Windows.Forms.Label();
            this.m_lblILOFreq = new System.Windows.Forms.Label();
            this.m_lblRefClkFreq = new System.Windows.Forms.Label();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_grpImplementation.SuspendLayout();
            this.m_grpClkInfo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // m_grpImplementation
            // 
            this.m_grpImplementation.Controls.Add(this.m_rbUDB);
            this.m_grpImplementation.Controls.Add(this.m_rbFixedFunction);
            this.m_grpImplementation.Location = new System.Drawing.Point(3, 3);
            this.m_grpImplementation.Name = "m_grpImplementation";
            this.m_grpImplementation.Size = new System.Drawing.Size(305, 65);
            this.m_grpImplementation.TabIndex = 0;
            this.m_grpImplementation.TabStop = false;
            this.m_grpImplementation.Text = "Implementation";
            // 
            // m_rbUDB
            // 
            this.m_rbUDB.AutoSize = true;
            this.m_rbUDB.Location = new System.Drawing.Point(6, 42);
            this.m_rbUDB.Name = "m_rbUDB";
            this.m_rbUDB.Size = new System.Drawing.Size(48, 17);
            this.m_rbUDB.TabIndex = 1;
            this.m_rbUDB.TabStop = true;
            this.m_rbUDB.Text = "UDB";
            this.m_rbUDB.UseVisualStyleBackColor = true;
            // 
            // m_rbFixedFunction
            // 
            this.m_rbFixedFunction.AutoSize = true;
            this.m_rbFixedFunction.Location = new System.Drawing.Point(6, 19);
            this.m_rbFixedFunction.Name = "m_rbFixedFunction";
            this.m_rbFixedFunction.Size = new System.Drawing.Size(94, 17);
            this.m_rbFixedFunction.TabIndex = 0;
            this.m_rbFixedFunction.TabStop = true;
            this.m_rbFixedFunction.Text = "Fixed Function";
            this.m_rbFixedFunction.UseVisualStyleBackColor = true;
            // 
            // m_grpClkInfo
            // 
            this.m_grpClkInfo.Controls.Add(this.m_lblWarningMsg);
            this.m_grpClkInfo.Controls.Add(this.m_lblRatio);
            this.m_grpClkInfo.Controls.Add(this.m_lblILOFreq);
            this.m_grpClkInfo.Controls.Add(this.m_lblRefClkFreq);
            this.m_grpClkInfo.Location = new System.Drawing.Point(3, 74);
            this.m_grpClkInfo.Name = "m_grpClkInfo";
            this.m_grpClkInfo.Size = new System.Drawing.Size(305, 97);
            this.m_grpClkInfo.TabIndex = 1;
            this.m_grpClkInfo.TabStop = false;
            this.m_grpClkInfo.Text = "Clocking Information";
            // 
            // m_lblWarningMsg
            // 
            this.m_lblWarningMsg.AutoSize = true;
            this.m_lblWarningMsg.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_errorProvider.SetIconAlignment(this.m_lblWarningMsg, System.Windows.Forms.ErrorIconAlignment.MiddleLeft);
            this.m_lblWarningMsg.Location = new System.Drawing.Point(40, 100);
            this.m_lblWarningMsg.MaximumSize = new System.Drawing.Size(256, 0);
            this.m_lblWarningMsg.Name = "m_lblWarningMsg";
            this.m_lblWarningMsg.Size = new System.Drawing.Size(0, 13);
            this.m_lblWarningMsg.TabIndex = 5;
            // 
            // m_lblRatio
            // 
            this.m_lblRatio.AutoSize = true;
            this.m_lblRatio.Location = new System.Drawing.Point(6, 74);
            this.m_lblRatio.Name = "m_lblRatio";
            this.m_lblRatio.Size = new System.Drawing.Size(35, 13);
            this.m_lblRatio.TabIndex = 2;
            this.m_lblRatio.Text = "Ratio:";
            // 
            // m_lblILOFreq
            // 
            this.m_lblILOFreq.AutoSize = true;
            this.m_lblILOFreq.Location = new System.Drawing.Point(6, 48);
            this.m_lblILOFreq.Name = "m_lblILOFreq";
            this.m_lblILOFreq.Size = new System.Drawing.Size(145, 13);
            this.m_lblILOFreq.TabIndex = 1;
            this.m_lblILOFreq.Text = "ILO clock nominal frequency:";
            // 
            // m_lblRefClkFreq
            // 
            this.m_lblRefClkFreq.AutoSize = true;
            this.m_lblRefClkFreq.Location = new System.Drawing.Point(6, 22);
            this.m_lblRefClkFreq.Name = "m_lblRefClkFreq";
            this.m_lblRefClkFreq.Size = new System.Drawing.Size(178, 13);
            this.m_lblRefClkFreq.TabIndex = 0;
            this.m_lblRefClkFreq.Text = "Reference clock nominal frequency:";
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // CyGeneralTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_grpClkInfo);
            this.Controls.Add(this.m_grpImplementation);
            this.Name = "CyGeneralTab";
            this.Size = new System.Drawing.Size(312, 175);
            this.m_grpImplementation.ResumeLayout(false);
            this.m_grpImplementation.PerformLayout();
            this.m_grpClkInfo.ResumeLayout(false);
            this.m_grpClkInfo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_grpImplementation;
        private System.Windows.Forms.RadioButton m_rbUDB;
        private System.Windows.Forms.RadioButton m_rbFixedFunction;
        private System.Windows.Forms.GroupBox m_grpClkInfo;
        private System.Windows.Forms.Label m_lblILOFreq;
        private System.Windows.Forms.Label m_lblRefClkFreq;
        private System.Windows.Forms.Label m_lblRatio;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.Label m_lblWarningMsg;
    }
}
