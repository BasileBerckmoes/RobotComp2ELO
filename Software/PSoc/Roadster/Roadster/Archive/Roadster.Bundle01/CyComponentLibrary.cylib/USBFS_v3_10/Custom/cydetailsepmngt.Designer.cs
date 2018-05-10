namespace USBFS_v3_10
{
    partial class CyDetailsEPMngt
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
            this.groupBoxBufferMgmt = new System.Windows.Forms.GroupBox();
            this.rbManualDynamicAlloc = new System.Windows.Forms.RadioButton();
            this.rbDMAAutomatic = new System.Windows.Forms.RadioButton();
            this.rbDMAManual = new System.Windows.Forms.RadioButton();
            this.rbManualStaticAlloc = new System.Windows.Forms.RadioButton();
            this.groupBoxBufferMgmt.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxBufferMgmt
            // 
            this.groupBoxBufferMgmt.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxBufferMgmt.Controls.Add(this.rbManualDynamicAlloc);
            this.groupBoxBufferMgmt.Controls.Add(this.rbDMAAutomatic);
            this.groupBoxBufferMgmt.Controls.Add(this.rbDMAManual);
            this.groupBoxBufferMgmt.Controls.Add(this.rbManualStaticAlloc);
            this.groupBoxBufferMgmt.Location = new System.Drawing.Point(4, 11);
            this.groupBoxBufferMgmt.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxBufferMgmt.Name = "groupBoxBufferMgmt";
            this.groupBoxBufferMgmt.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxBufferMgmt.Size = new System.Drawing.Size(440, 147);
            this.groupBoxBufferMgmt.TabIndex = 6;
            this.groupBoxBufferMgmt.TabStop = false;
            this.groupBoxBufferMgmt.Text = "Endpoint Buffer Management";
            // 
            // rbManualDynamicAlloc
            // 
            this.rbManualDynamicAlloc.AutoSize = true;
            this.rbManualDynamicAlloc.Location = new System.Drawing.Point(8, 53);
            this.rbManualDynamicAlloc.Name = "rbManualDynamicAlloc";
            this.rbManualDynamicAlloc.Size = new System.Drawing.Size(208, 21);
            this.rbManualDynamicAlloc.TabIndex = 1;
            this.rbManualDynamicAlloc.TabStop = true;
            this.rbManualDynamicAlloc.Text = "Manual (Dynamic Allocation)";
            this.rbManualDynamicAlloc.UseVisualStyleBackColor = true;
            // 
            // rbDMAAutomatic
            // 
            this.rbDMAAutomatic.AutoSize = true;
            this.rbDMAAutomatic.Location = new System.Drawing.Point(8, 110);
            this.rbDMAAutomatic.Margin = new System.Windows.Forms.Padding(4);
            this.rbDMAAutomatic.Name = "rbDMAAutomatic";
            this.rbDMAAutomatic.Size = new System.Drawing.Size(281, 21);
            this.rbDMAAutomatic.TabIndex = 3;
            this.rbDMAAutomatic.Text = "DMA with Automatic Buffer Management";
            this.rbDMAAutomatic.UseVisualStyleBackColor = true;
            // 
            // rbDMAManual
            // 
            this.rbDMAManual.AutoSize = true;
            this.rbDMAManual.Location = new System.Drawing.Point(8, 81);
            this.rbDMAManual.Margin = new System.Windows.Forms.Padding(4);
            this.rbDMAManual.Name = "rbDMAManual";
            this.rbDMAManual.Size = new System.Drawing.Size(379, 21);
            this.rbDMAManual.TabIndex = 2;
            this.rbDMAManual.Text = "DMA with Manual Buffer Management (Static Allocation)";
            this.rbDMAManual.UseVisualStyleBackColor = true;
            // 
            // rbManualStaticAlloc
            // 
            this.rbManualStaticAlloc.AutoSize = true;
            this.rbManualStaticAlloc.Checked = true;
            this.rbManualStaticAlloc.Location = new System.Drawing.Point(8, 25);
            this.rbManualStaticAlloc.Margin = new System.Windows.Forms.Padding(4);
            this.rbManualStaticAlloc.Name = "rbManualStaticAlloc";
            this.rbManualStaticAlloc.Size = new System.Drawing.Size(189, 21);
            this.rbManualStaticAlloc.TabIndex = 0;
            this.rbManualStaticAlloc.TabStop = true;
            this.rbManualStaticAlloc.Text = "Manual (Static Allocation)";
            this.rbManualStaticAlloc.UseVisualStyleBackColor = true;
            // 
            // CyDetailsEPMngt
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.groupBoxBufferMgmt);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyDetailsEPMngt";
            this.Size = new System.Drawing.Size(448, 431);
            this.groupBoxBufferMgmt.ResumeLayout(false);
            this.groupBoxBufferMgmt.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxBufferMgmt;
        private System.Windows.Forms.RadioButton rbDMAAutomatic;
        private System.Windows.Forms.RadioButton rbDMAManual;
        private System.Windows.Forms.RadioButton rbManualStaticAlloc;
        private System.Windows.Forms.RadioButton rbManualDynamicAlloc;
    }
}
