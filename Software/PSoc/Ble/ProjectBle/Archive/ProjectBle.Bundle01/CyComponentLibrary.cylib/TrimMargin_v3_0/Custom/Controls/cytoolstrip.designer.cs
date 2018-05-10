namespace TrimMargin_v3_0.Controls
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyToolStrip));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbCopy = new System.Windows.Forms.ToolStripButton();
            this.tsbPaste = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbOpenConfig = new System.Windows.Forms.ToolStripButton();
            this.tsbSaveConfig = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbAddConverter = new System.Windows.Forms.ToolStripButton();
            this.tsbDeleteConverter = new System.Windows.Forms.ToolStripButton();
            this.tsbConfigure = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbHideShowColumn = new System.Windows.Forms.ToolStripButton();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.BackColor = System.Drawing.SystemColors.Control;
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbCopy,
            this.tsbPaste,
            this.toolStripSeparator1,
            this.tsbOpenConfig,
            this.tsbSaveConfig,
            this.toolStripSeparator3,
            this.tsbAddConverter,
            this.tsbDeleteConverter,
            this.tsbConfigure,
            this.toolStripSeparator2,
            this.tsbHideShowColumn});
            resources.ApplyResources(this.toolStrip1, "toolStrip1");
            this.toolStrip1.Name = "toolStrip1";
            // 
            // tsbCopy
            // 
            this.tsbCopy.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbCopy.Image = global::TrimMargin_v3_0.Resources.Copy;
            resources.ApplyResources(this.tsbCopy, "tsbCopy");
            this.tsbCopy.Name = "tsbCopy";
            this.tsbCopy.Click += new System.EventHandler(this.tsbCopy_Click);
            // 
            // tsbPaste
            // 
            this.tsbPaste.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbPaste.Image = global::TrimMargin_v3_0.Resources.Paste;
            resources.ApplyResources(this.tsbPaste, "tsbPaste");
            this.tsbPaste.Name = "tsbPaste";
            this.tsbPaste.Click += new System.EventHandler(this.tsbPaste_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            resources.ApplyResources(this.toolStripSeparator1, "toolStripSeparator1");
            // 
            // tsbOpenConfig
            // 
            this.tsbOpenConfig.Image = global::TrimMargin_v3_0.Resources.Open;
            resources.ApplyResources(this.tsbOpenConfig, "tsbOpenConfig");
            this.tsbOpenConfig.Name = "tsbOpenConfig";
            this.tsbOpenConfig.Click += new System.EventHandler(this.tsbOpenConfig_Click);
            // 
            // tsbSaveConfig
            // 
            this.tsbSaveConfig.Image = global::TrimMargin_v3_0.Resources.Save;
            resources.ApplyResources(this.tsbSaveConfig, "tsbSaveConfig");
            this.tsbSaveConfig.Name = "tsbSaveConfig";
            this.tsbSaveConfig.Click += new System.EventHandler(this.tsbSaveConfig_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            resources.ApplyResources(this.toolStripSeparator3, "toolStripSeparator3");
            // 
            // tsbAddConverter
            // 
            this.tsbAddConverter.BackColor = System.Drawing.SystemColors.Control;
            this.tsbAddConverter.Image = global::TrimMargin_v3_0.Resources.imadd;
            resources.ApplyResources(this.tsbAddConverter, "tsbAddConverter");
            this.tsbAddConverter.Name = "tsbAddConverter";
            this.tsbAddConverter.Click += new System.EventHandler(this.tsbAddConverter_Click);
            // 
            // tsbDeleteConverter
            // 
            resources.ApplyResources(this.tsbDeleteConverter, "tsbDeleteConverter");
            this.tsbDeleteConverter.Name = "tsbDeleteConverter";
            this.tsbDeleteConverter.Click += new System.EventHandler(this.tsbDelete_Click);
            // 
            // tsbConfigure
            // 
            this.tsbConfigure.Image = global::TrimMargin_v3_0.Resources.Configure;
            resources.ApplyResources(this.tsbConfigure, "tsbConfigure");
            this.tsbConfigure.Name = "tsbConfigure";
            this.tsbConfigure.Click += new System.EventHandler(this.tsbConfigure_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            resources.ApplyResources(this.toolStripSeparator2, "toolStripSeparator2");
            // 
            // tsbHideShowColumn
            // 
            this.tsbHideShowColumn.Image = global::TrimMargin_v3_0.Resources.show_hide_columns;
            resources.ApplyResources(this.tsbHideShowColumn, "tsbHideShowColumn");
            this.tsbHideShowColumn.Name = "tsbHideShowColumn";
            this.tsbHideShowColumn.Click += new System.EventHandler(this.tsbHideShowColumn_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            // 
            // CyToolStrip
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.toolStrip1);
            this.Name = "CyToolStrip";
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
        private System.Windows.Forms.ToolStripButton tsbAddConverter;
        private System.Windows.Forms.ToolStripButton tsbDeleteConverter;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.ToolStripButton tsbHideShowColumn;
        private System.Windows.Forms.ToolStripButton tsbConfigure;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton tsbOpenConfig;
        private System.Windows.Forms.ToolStripButton tsbSaveConfig;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
    }
}
