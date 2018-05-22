namespace PowerMonitor_P4_v2_10
{
    partial class CyToolStrip
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
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbCopy = new System.Windows.Forms.ToolStripButton();
            this.tsbPaste = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbImport = new System.Windows.Forms.ToolStripButton();
            this.tsbExport = new System.Windows.Forms.ToolStripButton();
            this.tsbExportAll = new System.Windows.Forms.ToolStripButton();
            this.tsbImportAll = new System.Windows.Forms.ToolStripButton();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbCopy,
            this.tsbPaste,
            this.toolStripSeparator1,
            this.tsbImport,
            this.tsbExport,
            this.tsbExportAll,
            this.tsbImportAll});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(736, 27);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbCopy
            // 
            this.tsbCopy.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbCopy.Image = global::PowerMonitor_P4_v2_10.Resources.Copy;
            this.tsbCopy.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbCopy.Name = "tsbCopy";
            this.tsbCopy.Size = new System.Drawing.Size(24, 24);
            this.tsbCopy.Text = "Copy Rows";
            this.tsbCopy.ToolTipText = "Copy rows (Ctrl + C)";
            this.tsbCopy.Click += new System.EventHandler(this.tsbCopy_Click);
            // 
            // tsbPaste
            // 
            this.tsbPaste.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbPaste.Image = global::PowerMonitor_P4_v2_10.Resources.Paste;
            this.tsbPaste.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbPaste.Name = "tsbPaste";
            this.tsbPaste.Size = new System.Drawing.Size(24, 24);
            this.tsbPaste.Text = "Paste Rows";
            this.tsbPaste.ToolTipText = "Paste rows (Ctrl + V)";
            this.tsbPaste.Click += new System.EventHandler(this.tsbPaste_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // tsbImport
            // 
            this.tsbImport.Image = global::PowerMonitor_P4_v2_10.Resources.Import;
            this.tsbImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbImport.Name = "tsbImport";
            this.tsbImport.Size = new System.Drawing.Size(116, 24);
            this.tsbImport.Text = "Import Table";
            this.tsbImport.ToolTipText = "Import Table (Ctrl + M)";
            this.tsbImport.Click += new System.EventHandler(this.tsbImport_Click);
            // 
            // tsbExport
            // 
            this.tsbExport.Image = global::PowerMonitor_P4_v2_10.Resources.Export;
            this.tsbExport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExport.Name = "tsbExport";
            this.tsbExport.Size = new System.Drawing.Size(114, 24);
            this.tsbExport.Text = "Export Table";
            this.tsbExport.ToolTipText = "Export Table (Ctrl + R)";
            this.tsbExport.Click += new System.EventHandler(this.tsbExport_Click);
            // 
            // tsbExportAll
            // 
            this.tsbExportAll.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.tsbExportAll.Image = global::PowerMonitor_P4_v2_10.Resources.Export;
            this.tsbExportAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExportAll.Name = "tsbExportAll";
            this.tsbExportAll.Size = new System.Drawing.Size(96, 24);
            this.tsbExportAll.Text = "Export all";
            this.tsbExportAll.ToolTipText = "Export all (Ctrl + Alt + R)";
            this.tsbExportAll.Visible = false;
            this.tsbExportAll.Click += new System.EventHandler(this.tsbExportAll_Click);
            // 
            // tsbImportAll
            // 
            this.tsbImportAll.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.tsbImportAll.Image = global::PowerMonitor_P4_v2_10.Resources.Import;
            this.tsbImportAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbImportAll.Name = "tsbImportAll";
            this.tsbImportAll.Size = new System.Drawing.Size(98, 24);
            this.tsbImportAll.Text = "Import all";
            this.tsbImportAll.ToolTipText = "Import all (Ctrl + Alt + M)";
            this.tsbImportAll.Visible = false;
            this.tsbImportAll.Click += new System.EventHandler(this.tsbImportAll_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            // 
            // CyToolStrip
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.toolStrip1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "CyToolStrip";
            this.Size = new System.Drawing.Size(736, 31);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsbCopy;
        private System.Windows.Forms.ToolStripButton tsbPaste;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton tsbImport;
        private System.Windows.Forms.ToolStripButton tsbExport;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.ToolStripButton tsbExportAll;
        private System.Windows.Forms.ToolStripButton tsbImportAll;
    }
}
