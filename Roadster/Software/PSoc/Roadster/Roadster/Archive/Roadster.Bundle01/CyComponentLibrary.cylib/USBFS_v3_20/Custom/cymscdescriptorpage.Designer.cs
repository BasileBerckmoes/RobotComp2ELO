namespace USBFS_v3_20
{
    partial class CyMassStoragePage
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
            this.m_chbHandleMscRequests = new System.Windows.Forms.CheckBox();
            this.m_lblNumLun = new System.Windows.Forms.Label();
            this.m_numericLun = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panelCb.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numericLun)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelCb
            // 
            this.panelCb.Controls.Add(this.m_chbHandleMscRequests);
            this.panelCb.Controls.Add(this.groupBox1);
            this.panelCb.Location = new System.Drawing.Point(0, 264);
            // 
            // m_chbHandleMscRequests
            // 
            this.m_chbHandleMscRequests.AutoSize = true;
            this.m_chbHandleMscRequests.Location = new System.Drawing.Point(21, 7);
            this.m_chbHandleMscRequests.Name = "m_chbHandleMscRequests";
            this.m_chbHandleMscRequests.Size = new System.Drawing.Size(172, 21);
            this.m_chbHandleMscRequests.TabIndex = 0;
            this.m_chbHandleMscRequests.Text = "Handle MSC Requests";
            this.m_chbHandleMscRequests.UseVisualStyleBackColor = true;
            this.m_chbHandleMscRequests.CheckedChanged += new System.EventHandler(this.m_chbEnMscRequests_CheckedChanged);
            // 
            // m_lblNumLun
            // 
            this.m_lblNumLun.AutoSize = true;
            this.m_lblNumLun.Location = new System.Drawing.Point(6, 22);
            this.m_lblNumLun.Name = "m_lblNumLun";
            this.m_lblNumLun.Size = new System.Drawing.Size(205, 17);
            this.m_lblNumLun.TabIndex = 1;
            this.m_lblNumLun.Text = "Number of Logical Units (LUN):";
            // 
            // m_numericLun
            // 
            this.m_numericLun.Location = new System.Drawing.Point(217, 20);
            this.m_numericLun.Maximum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.m_numericLun.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.m_numericLun.Name = "m_numericLun";
            this.m_numericLun.Size = new System.Drawing.Size(54, 22);
            this.m_numericLun.TabIndex = 2;
            this.m_numericLun.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.m_numericLun.ValueChanged += new System.EventHandler(this.m_numericLun_ValueChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.m_numericLun);
            this.groupBox1.Controls.Add(this.m_lblNumLun);
            this.groupBox1.Location = new System.Drawing.Point(12, 10);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(289, 50);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            // 
            // CyMassStoragePage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Name = "CyMassStoragePage";
            this.Size = new System.Drawing.Size(775, 331);
            this.panelCb.ResumeLayout(false);
            this.panelCb.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numericLun)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.CheckBox m_chbHandleMscRequests;
        private System.Windows.Forms.NumericUpDown m_numericLun;
        private System.Windows.Forms.Label m_lblNumLun;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}
