namespace USBFS_v3_10
{
    partial class CyHidDescriptorPage
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyHidDescriptorPage));
            this.splitContainerReport = new System.Windows.Forms.SplitContainer();
            this.treeViewReport = new System.Windows.Forms.TreeView();
            this.contextMenuStripTree = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.renameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButtonAdd = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonRemove = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSplitButtonImport = new System.Windows.Forms.ToolStripSplitButton();
            this.fromFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemImportSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonSave = new System.Windows.Forms.ToolStripButton();
            this.splitContainerDetails = new System.Windows.Forms.SplitContainer();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.listBoxItems = new System.Windows.Forms.ListBox();
            this.panelItemValue = new System.Windows.Forms.Panel();
            this.labelItemSettings = new System.Windows.Forms.Label();
            this.panelDetails = new System.Windows.Forms.Panel();
            this.panelApply = new System.Windows.Forms.Panel();
            this.buttonApply = new System.Windows.Forms.Button();
            this.toolTipList = new System.Windows.Forms.ToolTip(this.components);
            this.splitContainerReport.Panel1.SuspendLayout();
            this.splitContainerReport.Panel2.SuspendLayout();
            this.splitContainerReport.SuspendLayout();
            this.contextMenuStripTree.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.splitContainerDetails.Panel1.SuspendLayout();
            this.splitContainerDetails.Panel2.SuspendLayout();
            this.splitContainerDetails.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.panelItemValue.SuspendLayout();
            this.panelApply.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainerReport
            // 
            this.splitContainerReport.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainerReport.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerReport.Location = new System.Drawing.Point(0, 0);
            this.splitContainerReport.Margin = new System.Windows.Forms.Padding(4);
            this.splitContainerReport.Name = "splitContainerReport";
            // 
            // splitContainerReport.Panel1
            // 
            this.splitContainerReport.Panel1.Controls.Add(this.treeViewReport);
            this.splitContainerReport.Panel1.Controls.Add(this.toolStrip1);
            // 
            // splitContainerReport.Panel2
            // 
            this.splitContainerReport.Panel2.Controls.Add(this.splitContainerDetails);
            this.splitContainerReport.Size = new System.Drawing.Size(800, 279);
            this.splitContainerReport.SplitterDistance = 320;
            this.splitContainerReport.SplitterWidth = 5;
            this.splitContainerReport.TabIndex = 0;
            // 
            // treeViewReport
            // 
            this.treeViewReport.AllowDrop = true;
            this.treeViewReport.ContextMenuStrip = this.contextMenuStripTree;
            this.treeViewReport.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeViewReport.HideSelection = false;
            this.treeViewReport.ImageIndex = 0;
            this.treeViewReport.ImageList = this.imageList;
            this.treeViewReport.LabelEdit = true;
            this.treeViewReport.Location = new System.Drawing.Point(0, 27);
            this.treeViewReport.Margin = new System.Windows.Forms.Padding(4);
            this.treeViewReport.Name = "treeViewReport";
            this.treeViewReport.SelectedImageIndex = 0;
            this.treeViewReport.Size = new System.Drawing.Size(316, 248);
            this.treeViewReport.TabIndex = 2;
            this.treeViewReport.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.treeViewReport_BeforeLabelEdit);
            this.treeViewReport.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.treeViewReport_AfterLabelEdit);
            this.treeViewReport.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.treeViewReport_ItemDrag);
            this.treeViewReport.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewReport_AfterSelect);
            this.treeViewReport.DragDrop += new System.Windows.Forms.DragEventHandler(this.treeViewReport_DragDrop);
            this.treeViewReport.DragEnter += new System.Windows.Forms.DragEventHandler(this.treeViewReport_DragEnter);
            this.treeViewReport.DragOver += new System.Windows.Forms.DragEventHandler(this.treeViewReport_DragOver);
            this.treeViewReport.DragLeave += new System.EventHandler(this.treeViewReport_DragLeave);
            this.treeViewReport.Enter += new System.EventHandler(this.treeViewReport_Enter);
            this.treeViewReport.KeyDown += new System.Windows.Forms.KeyEventHandler(this.treeViewReport_KeyDown);
            this.treeViewReport.MouseDown += new System.Windows.Forms.MouseEventHandler(this.treeViewReport_MouseDown);
            // 
            // contextMenuStripTree
            // 
            this.contextMenuStripTree.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.renameToolStripMenuItem});
            this.contextMenuStripTree.Name = "contextMenuStripTree";
            this.contextMenuStripTree.Size = new System.Drawing.Size(133, 28);
            this.contextMenuStripTree.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStripTree_Opening);
            // 
            // renameToolStripMenuItem
            // 
            this.renameToolStripMenuItem.Name = "renameToolStripMenuItem";
            this.renameToolStripMenuItem.Size = new System.Drawing.Size(132, 24);
            this.renameToolStripMenuItem.Text = "Rename";
            this.renameToolStripMenuItem.Click += new System.EventHandler(this.renameToolStripMenuItem_Click);
            // 
            // imageList
            // 
            this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
            this.imageList.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList.Images.SetKeyName(0, "Folder.png");
            this.imageList.Images.SetKeyName(1, "USB Drive.png");
            this.imageList.Images.SetKeyName(2, "Configuration.png");
            this.imageList.Images.SetKeyName(3, "Script.png");
            this.imageList.Images.SetKeyName(4, "Save.png");
            this.imageList.Images.SetKeyName(5, "Component.png");
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonAdd,
            this.toolStripButtonRemove,
            this.toolStripSeparator1,
            this.toolStripSplitButtonImport,
            this.toolStripButtonSave});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(316, 27);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip";
            // 
            // toolStripButtonAdd
            // 
            this.toolStripButtonAdd.Image = global::USBFS_v3_10.Properties.Resources.imadd;
            this.toolStripButtonAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonAdd.Name = "toolStripButtonAdd";
            this.toolStripButtonAdd.Size = new System.Drawing.Size(106, 24);
            this.toolStripButtonAdd.Text = "Add Report";
            this.toolStripButtonAdd.Click += new System.EventHandler(this.toolStripButtonAdd_Click);
            // 
            // toolStripButtonRemove
            // 
            this.toolStripButtonRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonRemove.Enabled = false;
            this.toolStripButtonRemove.Image = global::USBFS_v3_10.Properties.Resources.imdelete;
            this.toolStripButtonRemove.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonRemove.Name = "toolStripButtonRemove";
            this.toolStripButtonRemove.Size = new System.Drawing.Size(23, 24);
            this.toolStripButtonRemove.Text = "Delete";
            this.toolStripButtonRemove.Click += new System.EventHandler(this.toolStripButtonRemove_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // toolStripSplitButtonImport
            // 
            this.toolStripSplitButtonImport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripSplitButtonImport.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fromFileToolStripMenuItem,
            this.toolStripMenuItemImportSeparator});
            this.toolStripSplitButtonImport.Image = global::USBFS_v3_10.Properties.Resources.imimport;
            this.toolStripSplitButtonImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripSplitButtonImport.Name = "toolStripSplitButtonImport";
            this.toolStripSplitButtonImport.Size = new System.Drawing.Size(32, 24);
            this.toolStripSplitButtonImport.Text = "Import Report";
            this.toolStripSplitButtonImport.ButtonClick += new System.EventHandler(this.toolStripSplitButtonImport_ButtonClick);
            // 
            // fromFileToolStripMenuItem
            // 
            this.fromFileToolStripMenuItem.Name = "fromFileToolStripMenuItem";
            this.fromFileToolStripMenuItem.Size = new System.Drawing.Size(146, 24);
            this.fromFileToolStripMenuItem.Text = "From file...";
            this.fromFileToolStripMenuItem.Click += new System.EventHandler(this.toolStripButtonImportFromFile_Click);
            // 
            // toolStripMenuItemImportSeparator
            // 
            this.toolStripMenuItemImportSeparator.Name = "toolStripMenuItemImportSeparator";
            this.toolStripMenuItemImportSeparator.Size = new System.Drawing.Size(143, 6);
            // 
            // toolStripButtonSave
            // 
            this.toolStripButtonSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonSave.Image = global::USBFS_v3_10.Properties.Resources.imsave;
            this.toolStripButtonSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonSave.Name = "toolStripButtonSave";
            this.toolStripButtonSave.Size = new System.Drawing.Size(23, 24);
            this.toolStripButtonSave.Text = "Save Report";
            this.toolStripButtonSave.Click += new System.EventHandler(this.toolStripButtonSave_Click);
            // 
            // splitContainerDetails
            // 
            this.splitContainerDetails.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainerDetails.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerDetails.Location = new System.Drawing.Point(0, 0);
            this.splitContainerDetails.Margin = new System.Windows.Forms.Padding(4);
            this.splitContainerDetails.Name = "splitContainerDetails";
            this.splitContainerDetails.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerDetails.Panel1
            // 
            this.splitContainerDetails.Panel1.BackColor = System.Drawing.Color.LightSteelBlue;
            this.splitContainerDetails.Panel1.Controls.Add(this.pictureBox1);
            this.splitContainerDetails.Panel1.Controls.Add(this.label1);
            this.splitContainerDetails.Panel1.Controls.Add(this.listBoxItems);
            // 
            // splitContainerDetails.Panel2
            // 
            this.splitContainerDetails.Panel2.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainerDetails.Panel2.Controls.Add(this.panelItemValue);
            this.splitContainerDetails.Panel2.Controls.Add(this.panelApply);
            this.splitContainerDetails.Size = new System.Drawing.Size(475, 279);
            this.splitContainerDetails.SplitterDistance = 119;
            this.splitContainerDetails.SplitterWidth = 5;
            this.splitContainerDetails.TabIndex = 0;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::USBFS_v3_10.Properties.Resources.imcomponentadd;
            this.pictureBox1.Location = new System.Drawing.Point(8, 7);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(16, 16);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 10;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label1.Location = new System.Drawing.Point(37, 7);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(118, 21);
            this.label1.TabIndex = 8;
            this.label1.Text = "HID Items List";
            // 
            // listBoxItems
            // 
            this.listBoxItems.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxItems.FormattingEnabled = true;
            this.listBoxItems.ItemHeight = 16;
            this.listBoxItems.Location = new System.Drawing.Point(3, 31);
            this.listBoxItems.Margin = new System.Windows.Forms.Padding(4);
            this.listBoxItems.Name = "listBoxItems";
            this.listBoxItems.Size = new System.Drawing.Size(463, 68);
            this.listBoxItems.TabIndex = 6;
            this.listBoxItems.SelectedIndexChanged += new System.EventHandler(this.listBoxItems_SelectedIndexChanged);
            this.listBoxItems.SizeChanged += new System.EventHandler(this.listBoxItems_SizeChanged);
            // 
            // panelItemValue
            // 
            this.panelItemValue.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelItemValue.BackColor = System.Drawing.Color.LightSteelBlue;
            this.panelItemValue.Controls.Add(this.labelItemSettings);
            this.panelItemValue.Controls.Add(this.panelDetails);
            this.panelItemValue.Location = new System.Drawing.Point(0, 4);
            this.panelItemValue.Margin = new System.Windows.Forms.Padding(4);
            this.panelItemValue.Name = "panelItemValue";
            this.panelItemValue.Size = new System.Drawing.Size(471, 108);
            this.panelItemValue.TabIndex = 3;
            // 
            // labelItemSettings
            // 
            this.labelItemSettings.AutoSize = true;
            this.labelItemSettings.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelItemSettings.ForeColor = System.Drawing.SystemColors.ControlText;
            this.labelItemSettings.Location = new System.Drawing.Point(4, 4);
            this.labelItemSettings.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelItemSettings.Name = "labelItemSettings";
            this.labelItemSettings.Size = new System.Drawing.Size(91, 21);
            this.labelItemSettings.TabIndex = 9;
            this.labelItemSettings.Text = "Item Value";
            // 
            // panelDetails
            // 
            this.panelDetails.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelDetails.BackColor = System.Drawing.Color.Transparent;
            this.panelDetails.Location = new System.Drawing.Point(4, 27);
            this.panelDetails.Margin = new System.Windows.Forms.Padding(4);
            this.panelDetails.Name = "panelDetails";
            this.panelDetails.Size = new System.Drawing.Size(463, 73);
            this.panelDetails.TabIndex = 1;
            // 
            // panelApply
            // 
            this.panelApply.Controls.Add(this.buttonApply);
            this.panelApply.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelApply.Location = new System.Drawing.Point(0, 109);
            this.panelApply.Margin = new System.Windows.Forms.Padding(4);
            this.panelApply.Name = "panelApply";
            this.panelApply.Size = new System.Drawing.Size(471, 42);
            this.panelApply.TabIndex = 0;
            // 
            // buttonApply
            // 
            this.buttonApply.BackColor = System.Drawing.Color.Transparent;
            this.buttonApply.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonApply.ForeColor = System.Drawing.SystemColors.ControlText;
            this.buttonApply.Location = new System.Drawing.Point(8, 6);
            this.buttonApply.Margin = new System.Windows.Forms.Padding(4);
            this.buttonApply.Name = "buttonApply";
            this.buttonApply.Size = new System.Drawing.Size(132, 31);
            this.buttonApply.TabIndex = 7;
            this.buttonApply.Text = "Add";
            this.buttonApply.UseVisualStyleBackColor = false;
            this.buttonApply.Click += new System.EventHandler(this.buttonApply_Click);
            // 
            // CyHidDescriptorPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainerReport);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyHidDescriptorPage";
            this.Size = new System.Drawing.Size(800, 279);
            this.VisibleChanged += new System.EventHandler(this.CyHIDDescriptor_VisibleChanged);
            this.splitContainerReport.Panel1.ResumeLayout(false);
            this.splitContainerReport.Panel1.PerformLayout();
            this.splitContainerReport.Panel2.ResumeLayout(false);
            this.splitContainerReport.ResumeLayout(false);
            this.contextMenuStripTree.ResumeLayout(false);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.splitContainerDetails.Panel1.ResumeLayout(false);
            this.splitContainerDetails.Panel1.PerformLayout();
            this.splitContainerDetails.Panel2.ResumeLayout(false);
            this.splitContainerDetails.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panelItemValue.ResumeLayout(false);
            this.panelItemValue.PerformLayout();
            this.panelApply.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainerReport;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.SplitContainer splitContainerDetails;
        private System.Windows.Forms.ToolStripButton toolStripButtonAdd;
        private System.Windows.Forms.ImageList imageList;
        private System.Windows.Forms.TreeView treeViewReport;
        private System.Windows.Forms.Button buttonApply;
        private System.Windows.Forms.ListBox listBoxItems;
        private System.Windows.Forms.Panel panelDetails;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ToolStripButton toolStripButtonRemove;
        private System.Windows.Forms.ToolStripButton toolStripButtonSave;
        private System.Windows.Forms.Label labelItemSettings;
        private System.Windows.Forms.ToolTip toolTipList;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.Panel panelItemValue;
        private System.Windows.Forms.Panel panelApply;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripTree;
        private System.Windows.Forms.ToolStripMenuItem renameToolStripMenuItem;
        private System.Windows.Forms.ToolStripSplitButton toolStripSplitButtonImport;
        private System.Windows.Forms.ToolStripMenuItem fromFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItemImportSeparator;
    }
}
